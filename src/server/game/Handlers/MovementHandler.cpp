/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2014 ArkCORE <http://www.arkania.net/> 
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Common.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "Opcodes.h"
#include "Log.h"
#include "Corpse.h"
#include "Player.h"
#include "SpellAuras.h"
#include "MapManager.h"
#include "Transport.h"
#include "Battleground.h"
#include "WaypointMovementGenerator.h"
#include "InstanceSaveMgr.h"
#include "ObjectMgr.h"
#include "MovementStructures.h"

void WorldSession::HandleSummonResponseOpcode(WorldPacket& recvData)
{
    if (!_player->IsAlive() || _player->IsInCombat())
        return;

    uint64 summonerGuid;
    bool agree;
    recvData >> summonerGuid;
    recvData >> agree;

    _player->SummonIfPossible(agree);
}

void WorldSession::HandleSetActiveMoverOpcode(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received CMSG_SET_ACTIVE_MOVER");

    ObjectGuid guid;

    guid[7] = recvPacket.ReadBit();
    guid[2] = recvPacket.ReadBit();
    guid[1] = recvPacket.ReadBit();
    guid[0] = recvPacket.ReadBit();
    guid[4] = recvPacket.ReadBit();
    guid[5] = recvPacket.ReadBit();
    guid[6] = recvPacket.ReadBit();
    guid[3] = recvPacket.ReadBit();

    recvPacket.ReadByteSeq(guid[3]);
    recvPacket.ReadByteSeq(guid[2]);
    recvPacket.ReadByteSeq(guid[4]);
    recvPacket.ReadByteSeq(guid[0]);
    recvPacket.ReadByteSeq(guid[5]);
    recvPacket.ReadByteSeq(guid[1]);
    recvPacket.ReadByteSeq(guid[6]);
    recvPacket.ReadByteSeq(guid[7]);

    if (GetPlayer()->IsInWorld())
    {
        if (_player->m_mover->GetGUID() != guid)
            sLog->outError("HandleSetActiveMoverOpcode: incorrect mover guid: mover is " UI64FMTD " (%s - Entry: %u) and should be " UI64FMTD, uint64(guid), GetLogNameForGuid(guid), GUID_ENPART(guid), _player->m_mover->GetGUID());
    }
}

void WorldSession::HandleMoveNotActiveMover(WorldPacket &recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received CMSG_MOVE_NOT_ACTIVE_MOVER");

    MovementInfo mi;
    ReadMovementInfo(recvData, &mi);

    _player->m_movementInfo = mi;
}

void WorldSession::HandleMountSpecialAnimOpcode(WorldPacket& /*recvData*/)
{
    WorldPacket data(SMSG_MOUNTSPECIAL_ANIM, 8);
    data << uint64(GetPlayer()->GetGUID());

    GetPlayer()->SendMessageToSet(&data, false);
}

void WorldSession::HandleMoveWorldportAckOpcode(WorldPacket& /*recvPacket*/)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received MSG_MOVE_WORLDPORT_ACK.");
    HandleMoveWorldportAckOpcode();
}

void WorldSession::HandleMoveWorldportAckOpcode()
{
    // ignore unexpected far teleports
    if (!GetPlayer()->IsBeingTeleportedFar())
        return;

    GetPlayer()->SetSemaphoreTeleportFar(false);

    // get the teleport destination
    WorldLocation const& loc = GetPlayer()->GetTeleportDest();

    // possible errors in the coordinate validity check
    if (!MapManager::IsValidMapCoord(loc))
    {
        LogoutPlayer(false);
        return;
    }

    // get the destination map entry, not the current one, this will fix homebind and reset greeting
    MapEntry const* mEntry = sMapStore.LookupEntry(loc.GetMapId());
    InstanceTemplate const* mInstance = sObjectMgr->GetInstanceTemplate(loc.GetMapId());

    // reset instance validity, except if going to an instance inside an instance
    if (GetPlayer()->m_InstanceValid == false && !mInstance)
        GetPlayer()->m_InstanceValid = true;

    Map* oldMap = GetPlayer()->GetMap();
    if (GetPlayer()->IsInWorld())
    {
        sLog->outError("Player (Name %s) is still in world when teleported from map %u to new map %u", GetPlayer()->GetName(), oldMap->GetId(), loc.GetMapId());
        oldMap->RemovePlayerFromMap(GetPlayer(), false);
    }

    // relocate the player to the teleport destination
    Map* newMap = sMapMgr->CreateMap(loc.GetMapId(), GetPlayer());
    // the CanEnter checks are done in TeleporTo but conditions may change
    // while the player is in transit, for example the map may get full
    if (!newMap || !newMap->CanEnter(GetPlayer()))
    {
        sLog->outError("Map %d could not be created for player %d, porting player to homebind", loc.GetMapId(), GetPlayer()->GetGUIDLow());
        GetPlayer()->TeleportTo(GetPlayer()->m_homebindMapId, GetPlayer()->m_homebindX, GetPlayer()->m_homebindY, GetPlayer()->m_homebindZ, GetPlayer()->GetOrientation());
        return;
    }
    else
        GetPlayer()->Relocate(&loc);

    GetPlayer()->ResetMap();
    GetPlayer()->SetMap(newMap);

    GetPlayer()->SendInitialPacketsBeforeAddToMap();
    if (!GetPlayer()->GetMap()->AddPlayerToMap(GetPlayer()))
    {
        sLog->outError("WORLD: failed to teleport player %s (%d) to map %d because of unknown reason!", GetPlayer()->GetName(), GetPlayer()->GetGUIDLow(), loc.GetMapId());
        GetPlayer()->ResetMap();
        GetPlayer()->SetMap(oldMap);
        GetPlayer()->TeleportTo(GetPlayer()->m_homebindMapId, GetPlayer()->m_homebindX, GetPlayer()->m_homebindY, GetPlayer()->m_homebindZ, GetPlayer()->GetOrientation());
        return;
    }

    // battleground state prepare (in case join to BG), at relogin/tele player not invited
    // only add to bg group and object, if the player was invited (else he entered through command)
    if (_player->InBattleground())
    {
        // cleanup setting if outdated
        if (!mEntry->IsBattlegroundOrArena())
        {
            // We're not in BG
            _player->SetBattlegroundId(0, BATTLEGROUND_TYPE_NONE);
            // reset destination bg team
            _player->SetBGTeam(0);
        }
        // join to bg case
        else if (Battleground* bg = _player->GetBattleground())
        {
            if (_player->IsInvitedForBattlegroundInstance(_player->GetBattlegroundId()))
                bg->AddPlayer(_player);
        }
    }

    GetPlayer()->SendInitialPacketsAfterAddToMap();

    // flight fast teleport case
    if (GetPlayer()->GetMotionMaster()->GetCurrentMovementGeneratorType() == FLIGHT_MOTION_TYPE)
    {
        if (!_player->InBattleground())
        {
            // short preparations to continue flight
            FlightPathMovementGenerator* flight = (FlightPathMovementGenerator*)(GetPlayer()->GetMotionMaster()->top());
            flight->Initialize(*GetPlayer());
            return;
        }

        // battleground state prepare, stop flight
        GetPlayer()->GetMotionMaster()->MovementExpired();
        GetPlayer()->CleanupAfterTaxiFlight();
    }

    // resurrect character at enter into instance where his corpse exist after add to map
    Corpse* corpse = GetPlayer()->GetCorpse();
    if (corpse && corpse->GetType() != CORPSE_BONES && corpse->GetMapId() == GetPlayer()->GetMapId())
    {
        if (mEntry->IsDungeon())
        {
            GetPlayer()->ResurrectPlayer(0.5f, false);
            GetPlayer()->SpawnCorpseBones();
        }
    }

    bool allowMount = !mEntry->IsDungeon() || mEntry->IsBattlegroundOrArena();
    if (mInstance)
    {
        Difficulty diff = GetPlayer()->GetDifficulty(mEntry->IsRaid());
        if (MapDifficulty const* mapDiff = GetMapDifficultyData(mEntry->MapID, diff))
        {
            if (mapDiff->resetTime)
            {
                if (time_t timeReset = sInstanceSaveMgr->GetResetTimeFor(mEntry->MapID, diff))
                {
                    uint32 timeleft = uint32(timeReset - time(NULL));
                    GetPlayer()->SendInstanceResetWarning(mEntry->MapID, diff, timeleft);
                }
            }
        }
        allowMount = mInstance->AllowMount;
    }

    // mount allow check
    if (!allowMount)
        _player->RemoveAurasByType(SPELL_AURA_MOUNTED);

    // update zone immediately, otherwise leave channel will cause crash in mtmap
    uint32 newzone, newarea;
    GetPlayer()->GetZoneAndAreaId(newzone, newarea);
    GetPlayer()->UpdateZone(newzone, newarea);

    // honorless target
    if (GetPlayer()->pvpInfo.inHostileArea)
        GetPlayer()->CastSpell(GetPlayer(), 2479, true);

    // in friendly area
    else if (GetPlayer()->IsPvP() && !GetPlayer()->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_IN_PVP))
        GetPlayer()->UpdatePvP(false, false);

    // resummon pet
    GetPlayer()->ResummonPetTemporaryUnSummonedIfAny();

    //lets process all delayed operations on successful teleport
    GetPlayer()->ProcessDelayedOperations();

    MovementInfo movementInfo = GetPlayer()->m_movementInfo;
    ExtraMovementInfo extraMovementInfo;

    movementInfo.time = getMSTime();
    movementInfo.guid = GetPlayer()->GetGUID();
    extraMovementInfo.flySpeed = GetPlayer()->GetSpeed(MOVE_FLIGHT);
    extraMovementInfo.flyBackSpeed = GetPlayer()->GetSpeed(MOVE_FLIGHT_BACK);

    WorldPacket teleUpdate(SMSG_MOVE_UPDATE_TELEPORT);
    WriteMovementInfo(teleUpdate, &movementInfo);

    WorldPacket speedUpdate(SMSG_MOVE_UPDATE_FLIGHT_SPEED);
    WriteMovementInfo(speedUpdate, &movementInfo, &extraMovementInfo);

    packetBlock packets;
    packets.push_back(&teleUpdate);
    packets.push_back(&speedUpdate);

    WorldPacket data = BuildMultiplePackets(packets);

    GetPlayer()->SendMessageToSet(&data,true);
}

void WorldSession::HandleMoveTeleportAck(WorldPacket& recvPacket)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_MOVE_TELEPORT_ACK");

    ObjectGuid guid;
    uint32 flags, time;
    recvPacket >> flags >> time;

    guid[5] = recvPacket.ReadBit();
    guid[0] = recvPacket.ReadBit();
    guid[1] = recvPacket.ReadBit();
    guid[6] = recvPacket.ReadBit();
    guid[3] = recvPacket.ReadBit();
    guid[7] = recvPacket.ReadBit();
    guid[2] = recvPacket.ReadBit();
    guid[4] = recvPacket.ReadBit();

    recvPacket.ReadByteSeq(guid[4]);
    recvPacket.ReadByteSeq(guid[2]);
    recvPacket.ReadByteSeq(guid[7]);
    recvPacket.ReadByteSeq(guid[6]);
    recvPacket.ReadByteSeq(guid[5]);
    recvPacket.ReadByteSeq(guid[1]);
    recvPacket.ReadByteSeq(guid[3]);
    recvPacket.ReadByteSeq(guid[0]);

    sLog->outStaticDebug("Guid " UI64FMTD, uint64(guid));
    sLog->outStaticDebug("Flags %u, time %u", flags, time/IN_MILLISECONDS);

    Player* plMover = _player->m_mover->ToPlayer();

    if (!plMover || !plMover->IsBeingTeleportedNear())
        return;

    if (guid != plMover->GetGUID())
        return;

    plMover->SetSemaphoreTeleportNear(false);

    uint32 old_zone = plMover->GetZoneId();

    WorldLocation const& dest = plMover->GetTeleportDest();

    plMover->UpdatePosition(dest, true);

    uint32 newzone, newarea;
    plMover->GetZoneAndAreaId(newzone, newarea);
    plMover->UpdateZone(newzone, newarea);

    // new zone
    if (old_zone != newzone)
    {
        // honorless target
        if (plMover->pvpInfo.inHostileArea)
            plMover->CastSpell(plMover, 2479, true);

        // in friendly area
        else if (plMover->IsPvP() && !plMover->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_IN_PVP))
            plMover->UpdatePvP(false, false);
    }

    // resummon pet
    GetPlayer()->ResummonPetTemporaryUnSummonedIfAny();

    //lets process all delayed operations on successful teleport
    GetPlayer()->ProcessDelayedOperations();
}

void WorldSession::HandleMoveSetCanFlyAckOpcode(WorldPacket& recvData)
{
    // fly mode on/off
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received CMSG_MOVE_SET_CAN_FLY_ACK");

    MovementInfo movementInfo;
    ExtraMovementInfo extraMovementInfo;
    ReadMovementInfo(recvData, &movementInfo, &extraMovementInfo);

    _player->m_mover->m_movementInfo.flags = movementInfo.GetMovementFlags();
}

void WorldSession::HandleMoveKnockBackAck(WorldPacket & recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_MOVE_KNOCK_BACK_ACK");

    MovementInfo movementInfo;
    ExtraMovementInfo extraInfo;
    ReadMovementInfo(recvData, &movementInfo,&extraInfo);

    if (_player->m_mover->GetGUID() != movementInfo.guid)
        return;

    _player->m_movementInfo = movementInfo;

    WorldPacket data(SMSG_MOVE_UPDATE_KNOCK_BACK);
    WriteMovementInfo(data,&movementInfo,&extraInfo);

    _player->SendMessageToSet(&data, false);
}

void WorldSession::HandleMoveHoverAck(WorldPacket& recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_MOVE_HOVER_ACK");

    uint64 guid;                                            // guid - unused
    recvData.readPackGUID(guid);

    recvData.read_skip<uint32>();                          // unk

    MovementInfo movementInfo;
    GetPlayer()->ReadMovementInfo(recvData, &movementInfo);

    recvData.read_skip<uint32>();                          // unk2
}

void WorldSession::HandleMoveWaterWalkAck(WorldPacket& recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_MOVE_WATER_WALK_ACK");

    MovementInfo movementInfo;
    ReadMovementInfo(recvData, &movementInfo);

    GetPlayer()->m_movementInfo = movementInfo;
}


void WorldSession::HandleForceSpeedChangeAck(WorldPacket &recvData)
{
    uint32 opcode = recvData.GetOpcode();
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Recvd %s (%u, 0x%X) opcode", LookupOpcodeName(Opcodes(opcode)), opcode, opcode);

    float newspeed = 0.0f;
    MovementInfo movementInfo;
    ExtraMovementInfo extraInfo;
    ReadMovementInfo(recvData, &movementInfo,&extraInfo);
    /*----------------*/

    // client ACK send one packet for mounted/run case and need skip all except last from its
    // in other cases anti-cheat check can be fail in false case
    UnitMoveType move_type;
    UnitMoveType force_move_type;

    static char const* move_type_name[MAX_MOVE_TYPE] = {  "Walk", "Run", "RunBack", "Swim", "SwimBack", "TurnRate", "Flight", "FlightBack", "PitchRate" };

    switch (opcode)
    {
        case CMSG_MOVE_FORCE_WALK_SPEED_CHANGE_ACK:          
            move_type = MOVE_WALK;          
            force_move_type = MOVE_WALK;
            newspeed = extraInfo.walkSpeed;
            break;
        case CMSG_MOVE_FORCE_RUN_SPEED_CHANGE_ACK:           
            move_type = MOVE_RUN;           
            force_move_type = MOVE_RUN;   
            newspeed = extraInfo.runSpeed;
            break;
        case CMSG_MOVE_FORCE_RUN_BACK_SPEED_CHANGE_ACK:      
            move_type = MOVE_RUN_BACK;      
            force_move_type = MOVE_RUN_BACK;
            newspeed = extraInfo.runBackSpeed;
            break;
        case CMSG_MOVE_FORCE_SWIM_SPEED_CHANGE_ACK:          
            move_type = MOVE_SWIM;          
            force_move_type = MOVE_SWIM;   
            newspeed = extraInfo.swimSpeed;
            break;
        case CMSG_MOVE_FORCE_SWIM_BACK_SPEED_CHANGE_ACK:     
            move_type = MOVE_SWIM_BACK;     
            force_move_type = MOVE_SWIM_BACK;
            newspeed = extraInfo.swimBackSpeed;
            break;
        case CMSG_MOVE_FORCE_TURN_RATE_CHANGE_ACK:           
            move_type = MOVE_TURN_RATE;     
            force_move_type = MOVE_TURN_RATE;
            newspeed = extraInfo.turnRate;
            break;
        case CMSG_MOVE_FORCE_FLIGHT_SPEED_CHANGE_ACK:        
            move_type = MOVE_FLIGHT;        
            force_move_type = MOVE_FLIGHT;
            newspeed = extraInfo.flySpeed;
            break;
        case CMSG_MOVE_FORCE_FLIGHT_BACK_SPEED_CHANGE_ACK:   
            move_type = MOVE_FLIGHT_BACK;   
            force_move_type = MOVE_FLIGHT_BACK;
            newspeed = extraInfo.flyBackSpeed;
            break;
        case CMSG_MOVE_FORCE_PITCH_RATE_CHANGE_ACK:          
            move_type = MOVE_PITCH_RATE;    
            force_move_type = MOVE_PITCH_RATE;
            newspeed = extraInfo.pitchRate;
            break;
        default:
            sLog->outError("WorldSession::HandleForceSpeedChangeAck: Unknown move type opcode: %u", opcode);
            return;
    }

    // skip all forced speed changes except last and unexpected
    // in run/mounted case used one ACK and it must be skipped.m_forced_speed_changes[MOVE_RUN} store both.
    /*if (_player->m_forced_speed_changes[force_move_type] > 0)
    {
        --_player->m_forced_speed_changes[force_move_type];
        if (_player->m_forced_speed_changes[force_move_type] > 0)
            return;
    }

    if (!_player->GetTransport() && fabs(_player->GetSpeed(move_type) - newspeed) > 0.01f)
    {
        if (_player->GetSpeed(move_type) > newspeed)         // must be greater - just correct
        {
            sLog->outError("%sSpeedChange player %s is NOT correct (must be %f instead %f), force set to correct value",
                move_type_name[move_type], _player->GetName(), _player->GetSpeed(move_type), newspeed);
            _player->SetSpeed(move_type, _player->GetSpeedRate(move_type), true);
        }
        else                                                // must be lesser - cheating
        {
            sLog->outBasic("Player %s from account id %u kicked for incorrect speed (must be %f instead %f)",
                _player->GetName(), _player->GetSession()->GetAccountId(), _player->GetSpeed(move_type), newspeed);
            _player->GetSession()->KickPlayer();
        }
    }*/
}

void WorldSession::HandleSetCollisionHeightAck(WorldPacket& recvData)
{
    MovementInfo movementInfo;
    ExtraMovementInfo extraMovementInfo;

    ReadMovementInfo(recvData,&movementInfo,&extraMovementInfo);

    sLog->outDebug(LOG_FILTER_NETWORKIO, "Received CMSG_MOVE_SET_COLLISION_HEIGHT_ACK");

    //GetPlayer()->SetColl
}

void WorldSession::HandleMovementOpcodes(WorldPacket& recvPacket)
{
    Unit* mover;
    /* extract packet */
    MovementInfo movementInfo;
    ReadMovementInfo(recvPacket, &movementInfo);

    if(movementInfo.guid == GetPlayer()->GetGUID())
        mover = GetPlayer()->ToUnit();
    else
        mover = GetPlayer()->m_mover;

    if (movementInfo.bits.hasTransportData && movementInfo.pos.m_positionX != movementInfo.t_pos.m_positionX)
       if (mover->GetTransport())
           mover->GetTransport()->UpdatePosition(&movementInfo);

    //! Anti-cheat checks. Please keep them in seperate if() blocks to maintain a clear overview.
    //! Might be subject to latency, so just remove improper flags.
    #ifdef TRINITY_DEBUG
    #define REMOVE_VIOLATING_FLAGS(check, maskToRemove) \
    { \
        if (check) \
        { \
            sLog->outDebug(LOG_FILTER_UNITS, "WorldSession::ReadMovementInfo: Violation of MovementFlags found (%s). " \
                "MovementFlags: %u, MovementFlags2: %u for player GUID: %u. Mask %u will be removed.", \
                STRINGIZE(check), movementInfo.GetMovementFlags(), movementInfo.GetExtraMovementFlags(), mover->GetGUIDLow(), maskToRemove); \
            movementInfo.RemoveMovementFlag((maskToRemove)); \
        } \
    }
    #else
    #define REMOVE_VIOLATING_FLAGS(check, maskToRemove) \
        if (check) \
            movementInfo.RemoveMovementFlag((maskToRemove));
    #endif


    /*! This must be a packet spoofing attempt. MOVEMENTFLAG_ROOT sent from the client is not valid
        in conjunction with any of the moving movement flags such as MOVEMENTFLAG_FORWARD.
        It will freeze clients that receive this player's movement info.
    */
    REMOVE_VIOLATING_FLAGS(movementInfo.HasMovementFlag(MOVEMENTFLAG_ROOT),
        MOVEMENTFLAG_ROOT);

    //! Cannot hover without SPELL_AURA_HOVER
    REMOVE_VIOLATING_FLAGS(movementInfo.HasMovementFlag(MOVEMENTFLAG_HOVER) && !GetPlayer()->HasAuraType(SPELL_AURA_HOVER),
        MOVEMENTFLAG_HOVER);

    //! Cannot ascend and descend at the same time
    REMOVE_VIOLATING_FLAGS(movementInfo.HasMovementFlag(MOVEMENTFLAG_ASCENDING) && movementInfo.HasMovementFlag(MOVEMENTFLAG_DESCENDING),
        MOVEMENTFLAG_ASCENDING | MOVEMENTFLAG_DESCENDING);

    //! Cannot move left and right at the same time
    REMOVE_VIOLATING_FLAGS(movementInfo.HasMovementFlag(MOVEMENTFLAG_LEFT) && movementInfo.HasMovementFlag(MOVEMENTFLAG_RIGHT),
        MOVEMENTFLAG_LEFT | MOVEMENTFLAG_RIGHT);

    //! Cannot strafe left and right at the same time
    REMOVE_VIOLATING_FLAGS(movementInfo.HasMovementFlag(MOVEMENTFLAG_STRAFE_LEFT) && movementInfo.HasMovementFlag(MOVEMENTFLAG_STRAFE_RIGHT),
        MOVEMENTFLAG_STRAFE_LEFT | MOVEMENTFLAG_STRAFE_RIGHT);

    //! Cannot pitch up and down at the same time
    REMOVE_VIOLATING_FLAGS(movementInfo.HasMovementFlag(MOVEMENTFLAG_PITCH_UP) && movementInfo.HasMovementFlag(MOVEMENTFLAG_PITCH_DOWN),
        MOVEMENTFLAG_PITCH_UP | MOVEMENTFLAG_PITCH_DOWN);

    //! Cannot move forwards and backwards at the same time
    REMOVE_VIOLATING_FLAGS(movementInfo.HasMovementFlag(MOVEMENTFLAG_FORWARD) && movementInfo.HasMovementFlag(MOVEMENTFLAG_BACKWARD),
        MOVEMENTFLAG_FORWARD | MOVEMENTFLAG_BACKWARD);

    //! Cannot walk on water without SPELL_AURA_WATER_WALK
    REMOVE_VIOLATING_FLAGS(movementInfo.HasMovementFlag(MOVEMENTFLAG_WATERWALKING) && !mover->HasAuraType(SPELL_AURA_WATER_WALK),
        MOVEMENTFLAG_WATERWALKING);

    //! Cannot feather fall without SPELL_AURA_FEATHER_FALL
    REMOVE_VIOLATING_FLAGS(movementInfo.HasMovementFlag(MOVEMENTFLAG_FALLING_SLOW) && !mover->HasAuraType(SPELL_AURA_FEATHER_FALL),
        MOVEMENTFLAG_FALLING_SLOW);

    /*! Cannot fly if no fly auras present. Exception is being a GM.
        Note that we check for account level instead of Player::IsGameMaster() because in some
        situations it may be feasable to use .gm fly on as a GM without having .gm on,
        e.g. aerial combat.
    */

    REMOVE_VIOLATING_FLAGS(movementInfo.HasMovementFlag(MOVEMENTFLAG_FLYING | MOVEMENTFLAG_CAN_FLY) && GetSecurity() == SEC_PLAYER &&
        !mover->HasAuraType(SPELL_AURA_FLY) &&
        !mover->HasAuraType(SPELL_AURA_MOD_INCREASE_MOUNTED_FLIGHT_SPEED),
        MOVEMENTFLAG_FLYING | MOVEMENTFLAG_CAN_FLY);

    #undef REMOVE_VIOLATING_FLAGS

    mover->HandleBasicMovement(movementInfo,recvPacket.GetOpcode());

    /* process position-change */
    /*WorldPacket data(SMSG_PLAYER_MOVE);
    mover->m_movementInfo.time = getMSTime();
    mover->m_movementInfo.guid = mover->GetGUID();
    WorldSession::WriteMovementInfo(data, &mover->m_movementInfo);
    mover->SendMessageToSet(&data, GetPlayer());*/
    SendPlayerMove(&mover->m_movementInfo);
}

void WorldSession::ReadMovementInfo(WorldPacket& data, MovementInfo* mi, ExtraMovementInfo *emi)
{
    bool hasMovementFlags = false;
    bool hasMovementFlags2 = false;
    bool hasOrientation = false;
    bool hasTransportTime2 = false;
    bool hasTransportTime3 = false;

    MovementSequence result = GetMovementStatusElementsSequence(data.GetOpcode());
    
    MovementStatusElements* sequence = result.first;
    size_t size = result.second + 1;

    if (sequence == NULL)
    {
        sLog->outError("WorldSession::ReadMovementInfo: No movement sequence found for opcode 0x%04X", uint32(data.GetOpcode()));
        return;
    }

    ObjectGuid guid;
    ObjectGuid tguid;

    for (uint32 i = 0; i < size; ++i)
    {
        MovementStatusElements element = sequence[i];

        if(element == MSEEnd)
            break;

        if (element >= MSEHasGuidByte0 && element <= MSEHasGuidByte7)
        {
            guid[element - MSEHasGuidByte0] = data.ReadBit();
            continue;
        }

        if (element >= MSEHasTransportGuidByte0 &&
            element <= MSEHasTransportGuidByte7)
        {
            if (mi->bits.hasTransportData)
                tguid[element - MSEHasTransportGuidByte0] = data.ReadBit();
            continue;
        }

        if (element >= MSEGuidByte0 && element <= MSEGuidByte7)
        {
            data.ReadByteSeq(guid[element - MSEGuidByte0]);
            continue;
        }

        if (element >= MSETransportGuidByte0 &&
            element <= MSETransportGuidByte7)
        {
            if (mi->bits.hasTransportData)
                data.ReadByteSeq(tguid[element - MSETransportGuidByte0]);
            continue;
        }

        switch (element)
        {
            case MSEHasMovementFlags:
                hasMovementFlags = !data.ReadBit();
                break;
            case MSEHasMovementFlags2:
                hasMovementFlags2 = !data.ReadBit();
                break;
            case MSEHasTimestamp:
                mi->bits.hasTimestamp = !data.ReadBit();
                break;
            case MSEHasOrientation:
                hasOrientation = !data.ReadBit();
                break;
            case MSEHasTransportData:
                mi->bits.hasTransportData = data.ReadBit();
                break;
            case MSEHasTransportTime2:
                if (mi->bits.hasTransportData)
                    hasTransportTime2 = data.ReadBit();
                break;
            case MSEHasTransportTime3:
                if (mi->bits.hasTransportData)
                    hasTransportTime3 = data.ReadBit();
                break;
            case MSEHasPitch:
                mi->bits.hasPitch = !data.ReadBit();
                break;
            case MSEHasFallData:
                mi->bits.hasFallData = data.ReadBit();
                break;
            case MSEHasFallDirection:
                if (mi->bits.hasFallData)
                    mi->bits.hasFallDirection = data.ReadBit();
                break;
            case MSEHasSplineElevation:
                mi->bits.hasSplineElev = !data.ReadBit();
                break;
            case MSEHasSpline:
                mi->bits.hasSpline = data.ReadBit();
                break;
            case MSEMovementFlags:
                if (hasMovementFlags)
                    mi->flags = data.ReadBits(30);
                break;
            case MSEMovementFlags2:
                if (hasMovementFlags2)
                    mi->flags2 = data.ReadBits(12);
                break;
            case MSETimestamp:
                if (mi->bits.hasTimestamp)
                    data >> mi->time;
                break;
            case MSEPositionX:
                data >> mi->pos.m_positionX;
                break;
            case MSEPositionY:
                data >> mi->pos.m_positionY;
                break;
            case MSEPositionZ:
                data >> mi->pos.m_positionZ;
                break;
            case MSEOrientation:
                if (hasOrientation)
                    mi->pos.SetOrientation(data.read<float>());
                break;
            case MSETransportPositionX:
                if (mi->bits.hasTransportData)
                    data >> mi->t_pos.m_positionX;
                break;
            case MSETransportPositionY:
                if (mi->bits.hasTransportData)
                    data >> mi->t_pos.m_positionY;
                break;
            case MSETransportPositionZ:
                if (mi->bits.hasTransportData)
                    data >> mi->t_pos.m_positionZ;
                break;
            case MSETransportOrientation:
                if (mi->bits.hasTransportData)
                    mi->t_pos.SetOrientation(data.read<float>());
                break;
            case MSETransportSeat:
                if (mi->bits.hasTransportData)
                    data >> mi->t_seat;
                break;
            case MSETransportTime:
                if (mi->bits.hasTransportData)
                    data >> mi->t_time;
                break;
            case MSETransportTime2:
                if (mi->bits.hasTransportData && hasTransportTime2)
                    data >> mi->t_time2;
                break;
            case MSETransportTime3:
                if (mi->bits.hasTransportData && hasTransportTime3)
                    data >> mi->t_time3;
                break;
            case MSEPitch:
                if (mi->bits.hasPitch)
                    data >> mi->pitch;
                break;
            case MSEFallTime:
                if (mi->bits.hasFallData)
                    data >> mi->fallTime;
                break;
            case MSEFallVerticalSpeed:
                if (mi->bits.hasFallData)
                    data >> mi->j_zspeed;
                break;
            case MSEFallCosAngle:
                if (mi->bits.hasFallData && mi->bits.hasFallDirection)
                    data >> mi->j_cosAngle;
                break;
            case MSEFallSinAngle:
                if (mi->bits.hasFallData && mi->bits.hasFallDirection)
                    data >> mi->j_sinAngle;
                break;
            case MSEFallHorizontalSpeed:
                if (mi->bits.hasFallData && mi->bits.hasFallDirection)
                    data >> mi->j_xyspeed;
                break;
            case MSESplineElevation:
                if (mi->bits.hasSplineElev)
                    data >> mi->splineElevation;
                break;
            case MSEZeroBit:
            case MSEOneBit:
                data.ReadBit();
                break;
            case MSEUnknownByte:
                data.read_skip<uint8>();
                break;
            case MSEUnknownDword:
                if(emi)
                    data >> emi->UnkDword;
                break;
            case MSEUnknownFloat:
                data.read_skip<float>();
                break;
            case MSEFlySpeed:
                if(emi)
                    data >> emi->flySpeed;
                break;
            case MSEFlyBackSpeed:
                if(emi)
                    data >> emi->flyBackSpeed;
                break;
            case MSERunSpeed:
                if(emi)
                    data >> emi->runSpeed;
                break;
            case MSERunBackSpeed:
                if(emi)
                    data >> emi->runBackSpeed;
                break;
            case MSEWalkSpeed:
                if(emi)
                    data >> emi->walkSpeed;
                break;
            case MSESwimSpeed:
                if(emi)
                    data >> emi->swimSpeed;
                break;
            case MSESwimBackSpeed:
                if(emi)
                    data >> emi->swimBackSpeed;
                break;
            case MSEPitchRate:
                if(emi)
                    data >> emi->pitchRate;
                break;
            case MSETurnRate:
                if(emi)
                    data >> emi->turnRate;
                break;
            case MSECollisionHeight:
                if(emi)
                    data >> emi->collisionHeight;
                break;
            case MSEMovementCounter:
                data >> mi->movementCounter;
                break;
            default:
                ASSERT(false && "Incorrect sequence element detected at ReadMovementInfo");
                break;
        }
    }

    mi->guid = guid;
    mi->t_guid = tguid;
}

void WorldSession::WriteMovementInfo(WorldPacket &data, MovementInfo* mi, ExtraMovementInfo *emi)
{
    bool hasMovementFlags = mi->GetMovementFlags() != 0;
    bool hasMovementFlags2 = mi->GetExtraMovementFlags() != 0;
    bool hasTimestamp = mi->time != 0;
    bool hasOrientation = !G3D::fuzzyEq(mi->pos.GetOrientation(), 0.0f);
    bool hasTransportData = mi->t_guid != 0;
    bool hasTransportTime2 = mi->HasExtraMovementFlag(MOVEMENTFLAG2_INTERPOLATED_MOVEMENT);
    bool hasTransportTime3 = false;
    bool hasPitch = mi->HasMovementFlag(MovementFlags(MOVEMENTFLAG_SWIMMING | MOVEMENTFLAG_FLYING)) || mi->HasExtraMovementFlag(MOVEMENTFLAG2_ALWAYS_ALLOW_PITCHING);
    bool hasFallData = mi->HasExtraMovementFlag(MOVEMENTFLAG2_INTERPOLATED_TURNING);
    bool hasFallDirection = mi->HasMovementFlag(MOVEMENTFLAG_FALLING);
    bool hasSplineElevation = mi->HasMovementFlag(MOVEMENTFLAG_SPLINE_ELEVATION);
    bool hasSpline = false;

    MovementSequence result = GetMovementStatusElementsSequence(data.GetOpcode());
    
    MovementStatusElements* sequence = result.first;
    size_t size = result.second + 1;

    if (!sequence)
    {
        sLog->outError("WorldSession::WriteMovementInfo: No movement sequence found for opcode 0x%04X", uint32(data.GetOpcode()));
        return;
    }

    ObjectGuid guid = mi->guid;
    ObjectGuid tguid = mi->t_guid;

    for(uint32 i = 0; i < size; ++i)
    {
        MovementStatusElements element = sequence[i];

        if (element == MSEEnd)
            break;

        if (element >= MSEHasGuidByte0 && element <= MSEHasGuidByte7)
        {
            data.WriteBit(guid[element - MSEHasGuidByte0]);
            continue;
        }

        if (element >= MSEHasTransportGuidByte0 &&
            element <= MSEHasTransportGuidByte7)
        {
            if (mi->bits.hasTransportData)
                data.WriteBit(tguid[element - MSEHasTransportGuidByte0]);
            continue;
        }

        if (element >= MSEGuidByte0 && element <= MSEGuidByte7)
        {
            data.WriteByteSeq(guid[element - MSEGuidByte0]);
            continue;
        }

        if (element >= MSETransportGuidByte0 &&
            element <= MSETransportGuidByte7)
        {
            if (mi->bits.hasTransportData)
                data.WriteByteSeq(tguid[element - MSETransportGuidByte0]);
            continue;
        }

        switch (element)
        {
            case MSEHasMovementFlags:
                data.WriteBit(!hasMovementFlags);
                break;
            case MSEHasMovementFlags2:
                data.WriteBit(!hasMovementFlags2);
                break;
            case MSEHasTimestamp:
                data.WriteBit(!hasTimestamp);
                break;
            case MSEHasOrientation:
                data.WriteBit(!hasOrientation);
                break;
            case MSEHasTransportData:
                data.WriteBit(mi->bits.hasTransportData);
                break;
            case MSEHasTransportTime2:
                if (mi->bits.hasTransportData)
                    data.WriteBit(hasTransportTime2);
                break;
            case MSEHasTransportTime3:
                if (mi->bits.hasTransportData)
                    data.WriteBit(hasTransportTime3);
                break;
            case MSEHasPitch:
                data.WriteBit(!mi->bits.hasPitch);
                break;
            case MSEHasFallData:
                data.WriteBit(mi->bits.hasFallData);
                break;
            case MSEHasFallDirection:
                if (hasFallData)
                    data.WriteBit(mi->bits.hasFallDirection);
                break;
            case MSEHasSplineElevation:
                data.WriteBit(!mi->bits.hasSplineElev);
                break;
            case MSEHasSpline:
                data.WriteBit(mi->bits.hasSpline);
                break;
            case MSEMovementFlags:
                if (hasMovementFlags)
                    data.WriteBits(mi->flags, 30);
                break;
            case MSEMovementFlags2:
                if (hasMovementFlags2)
                    data.WriteBits(mi->flags2, 12);
                break;
            case MSETimestamp:
                if (hasTimestamp)
                    data << mi->time;
                break;
            case MSEPositionX:
                data << mi->pos.m_positionX;
                break;
            case MSEPositionY:
                data << mi->pos.m_positionY;
                break;
            case MSEPositionZ:
                data << mi->pos.m_positionZ;
                break;
            case MSEOrientation:
                if (hasOrientation)
                    data << mi->pos.GetOrientation();
                break;
            case MSETransportPositionX:
                if (mi->bits.hasTransportData)
                    data << mi->t_pos.m_positionX;
                break;
            case MSETransportPositionY:
                if (mi->bits.hasTransportData)
                    data << mi->t_pos.m_positionY;
                break;
            case MSETransportPositionZ:
                if (mi->bits.hasTransportData)
                    data << mi->t_pos.m_positionZ;
                break;
            case MSETransportOrientation:
                if (mi->bits.hasTransportData)
                    data << mi->t_pos.GetOrientation();
                break;
            case MSETransportSeat:
                if (mi->bits.hasTransportData)
                    data << mi->t_seat;
                break;
            case MSETransportTime:
                if (mi->bits.hasTransportData)
                    data << mi->t_time;
                break;
            case MSETransportTime2:
                if (mi->bits.hasTransportData && hasTransportTime2)
                    data << mi->t_time2;
                break;
            case MSETransportTime3:
                if (mi->bits.hasTransportData && hasTransportTime3)
                    data << mi->t_time3;
                break;
            case MSEPitch:
                if (mi->bits.hasPitch)
                    data << mi->pitch;
                break;
            case MSEFallTime:
                if (mi->bits.hasFallData)
                    data << mi->fallTime;
                break;
            case MSEFallVerticalSpeed:
                if (mi->bits.hasFallData)
                    data << mi->j_zspeed;
                break;
            case MSEFallCosAngle:
                if (mi->bits.hasFallData && mi->bits.hasFallDirection)
                    data << mi->j_cosAngle;
                break;
            case MSEFallSinAngle:
                if (mi->bits.hasFallData && mi->bits.hasFallDirection)
                    data << mi->j_sinAngle;
                break;
            case MSEFallHorizontalSpeed:
                if (mi->bits.hasFallData && mi->bits.hasFallDirection)
                    data << mi->j_xyspeed;
                break;
            case MSESplineElevation:
                if (mi->bits.hasSplineElev)
                    data << mi->splineElevation;
                break;
            case MSEZeroBit:
                data.WriteBit(0);
                break;
            case MSEOneBit:
                data.WriteBit(1);
                break;
            case MSEFlySpeed:
                if(emi)
                    data << emi->flySpeed;
                break;
            case MSEFlyBackSpeed:
                if(emi)
                    data << emi->flyBackSpeed;
                break;
            case MSERunSpeed:
                if(emi)
                    data << emi->runSpeed;
                break;
            case MSERunBackSpeed:
                if(emi)
                    data << emi->runBackSpeed;
                break;
            case MSEWalkSpeed:
                if(emi)
                    data << emi->walkSpeed;
                break;
            case MSESwimSpeed:
                if(emi)
                    data << emi->swimSpeed;
                break;
            case MSESwimBackSpeed:
                if(emi)
                    data << emi->swimBackSpeed;
                break;
            case MSEPitchRate:
                if(emi)
                    data << emi->pitchRate;
                break;
            case MSETurnRate:
                if(emi)
                    data << emi->turnRate;
                break;
            case MSECollisionHeight:
                if(emi)
                    data << emi->collisionHeight;
                break;
            case MSEMovementCounter:
                data << mi->movementCounter;
                break;
            default:
                ASSERT(false && "Incorrect sequence element detected at ReadMovementInfo");
                break;
        }
    }
}

void WorldSession::SendSplineFlags(uint32 flag, Unit* mover)
{
    bool hasFlag = mover->HasUnitMovementFlag(flag);
    ObjectGuid playerGuid = mover->GetGUID();

    switch(flag)
    {
        case MOVEMENTFLAG_CAN_FLY:
        {
            if(hasFlag)
            {
                WorldPacket data(SMSG_SPLINE_MOVE_SET_FLYING);
                data.WriteBit(playerGuid[0]);
                data.WriteBit(playerGuid[4]);
                data.WriteBit(playerGuid[1]);
                data.WriteBit(playerGuid[6]);
                data.WriteBit(playerGuid[2]);
                data.WriteBit(playerGuid[7]);
                data.WriteBit(playerGuid[3]);
                data.WriteBit(playerGuid[5]);
                data.FlushBits();
                data.WriteByteSeq(playerGuid[7]);
                data.WriteByteSeq(playerGuid[0]);
                data.WriteByteSeq(playerGuid[5]);
                data.WriteByteSeq(playerGuid[6]);
                data.WriteByteSeq(playerGuid[4]);
                data.WriteByteSeq(playerGuid[1]);
                data.WriteByteSeq(playerGuid[3]);
                data.WriteByteSeq(playerGuid[2]);
                mover->SendMessageToSet(&data,false);
            }
            else
            {
                WorldPacket data(SMSG_SPLINE_MOVE_UNSET_FLYING);
                data.WriteBit(playerGuid[5]);
                data.WriteBit(playerGuid[0]);
                data.WriteBit(playerGuid[4]);
                data.WriteBit(playerGuid[2]);
                data.WriteBit(playerGuid[3]);
                data.WriteBit(playerGuid[7]);
                data.WriteBit(playerGuid[1]);
                data.WriteBit(playerGuid[6]);
                data.FlushBits();
                data.WriteByteSeq(playerGuid[7]);
                data.WriteByteSeq(playerGuid[2]);
                data.WriteByteSeq(playerGuid[3]);
                data.WriteByteSeq(playerGuid[4]);
                data.WriteByteSeq(playerGuid[5]);
                data.WriteByteSeq(playerGuid[1]);
                data.WriteByteSeq(playerGuid[6]);
                data.WriteByteSeq(playerGuid[0]);
                mover->SendMessageToSet(&data,false);
            }
            break;
        }
        case MOVEMENTFLAG_HOVER:
        {
            if(hasFlag)
            {
                WorldPacket data(SMSG_SPLINE_MOVE_SET_HOVER);
                data.WriteBit(playerGuid[3]);
                data.WriteBit(playerGuid[7]);
                data.WriteBit(playerGuid[0]);
                data.WriteBit(playerGuid[1]);
                data.WriteBit(playerGuid[4]);
                data.WriteBit(playerGuid[6]);
                data.WriteBit(playerGuid[2]);
                data.WriteBit(playerGuid[5]);
                data.FlushBits();
                data.WriteByteSeq(playerGuid[2]);
                data.WriteByteSeq(playerGuid[4]);
                data.WriteByteSeq(playerGuid[3]);
                data.WriteByteSeq(playerGuid[1]);
                data.WriteByteSeq(playerGuid[7]);
                data.WriteByteSeq(playerGuid[0]);
                data.WriteByteSeq(playerGuid[5]);
                data.WriteByteSeq(playerGuid[6]);
                mover->SendMessageToSet(&data,false);
            }
            else
            {
                WorldPacket data(SMSG_SPLINE_MOVE_UNSET_HOVER);
                data.WriteBit(playerGuid[6]);
                data.WriteBit(playerGuid[7]);
                data.WriteBit(playerGuid[0]);
                data.WriteBit(playerGuid[3]);
                data.WriteBit(playerGuid[1]);
                data.WriteBit(playerGuid[4]);
                data.WriteBit(playerGuid[5]);
                data.WriteBit(playerGuid[2]);
                data.FlushBits();
                data.WriteByteSeq(playerGuid[4]);
                data.WriteByteSeq(playerGuid[5]);
                data.WriteByteSeq(playerGuid[3]);
                data.WriteByteSeq(playerGuid[0]);
                data.WriteByteSeq(playerGuid[2]);
                data.WriteByteSeq(playerGuid[7]);
                data.WriteByteSeq(playerGuid[6]);
                data.WriteByteSeq(playerGuid[1]);
                mover->SendMessageToSet(&data,false);
            }
            break;
        }
        case MOVEMENTFLAG_WATERWALKING:
        {
            if(hasFlag)
            {
                WorldPacket data(SMSG_SPLINE_MOVE_WATER_WALK);
                data.WriteBit(playerGuid[6]);
                data.WriteBit(playerGuid[1]);
                data.WriteBit(playerGuid[4]);
                data.WriteBit(playerGuid[2]);
                data.WriteBit(playerGuid[3]);
                data.WriteBit(playerGuid[7]);
                data.WriteBit(playerGuid[5]);
                data.WriteBit(playerGuid[0]);
                data.FlushBits();
                data.WriteByteSeq(playerGuid[0]);
                data.WriteByteSeq(playerGuid[6]);
                data.WriteByteSeq(playerGuid[3]);
                data.WriteByteSeq(playerGuid[7]);
                data.WriteByteSeq(playerGuid[4]);
                data.WriteByteSeq(playerGuid[2]);
                data.WriteByteSeq(playerGuid[5]);
                data.WriteByteSeq(playerGuid[1]);
                mover->SendMessageToSet(&data,false);
            }
            else
            {
                WorldPacket data(SMSG_SPLINE_MOVE_SET_LAND_WALK);
                data.WriteBit(playerGuid[0]);
                data.WriteBit(playerGuid[4]);
                data.WriteBit(playerGuid[6]);
                data.WriteBit(playerGuid[7]);
                data.WriteBit(playerGuid[2]);
                data.WriteBit(playerGuid[5]);
                data.WriteBit(playerGuid[3]);
                data.WriteBit(playerGuid[1]);
                data.FlushBits();
                data.WriteByteSeq(playerGuid[5]);
                data.WriteByteSeq(playerGuid[7]);
                data.WriteByteSeq(playerGuid[3]);
                data.WriteByteSeq(playerGuid[4]);
                data.WriteByteSeq(playerGuid[2]);
                data.WriteByteSeq(playerGuid[1]);
                data.WriteByteSeq(playerGuid[0]);
                data.WriteByteSeq(playerGuid[6]);
                mover->SendMessageToSet(&data,false);
            }
            break;
        }
        case MOVEMENTFLAG_SWIMMING:
        {
            if(hasFlag)
            {
                WorldPacket data(SMSG_SPLINE_MOVE_START_SWIM);
                data.WriteBit(playerGuid[1]);
                data.WriteBit(playerGuid[6]);
                data.WriteBit(playerGuid[0]);
                data.WriteBit(playerGuid[7]);
                data.WriteBit(playerGuid[5]);
                data.WriteBit(playerGuid[3]);
                data.WriteBit(playerGuid[2]);
                data.WriteBit(playerGuid[4]);
                data.FlushBits();
                data.WriteByteSeq(playerGuid[3]);
                data.WriteByteSeq(playerGuid[7]);
                data.WriteByteSeq(playerGuid[2]);
                data.WriteByteSeq(playerGuid[5]);
                data.WriteByteSeq(playerGuid[6]);
                data.WriteByteSeq(playerGuid[4]);
                data.WriteByteSeq(playerGuid[1]);
                data.WriteByteSeq(playerGuid[0]);
                mover->SendMessageToSet(&data,false);
            }
            else
            {
                WorldPacket data(SMSG_SPLINE_MOVE_STOP_SWIM);
                data.WriteBit(playerGuid[4]);
                data.WriteBit(playerGuid[1]);
                data.WriteBit(playerGuid[5]);
                data.WriteBit(playerGuid[3]);
                data.WriteBit(playerGuid[0]);
                data.WriteBit(playerGuid[7]);
                data.WriteBit(playerGuid[2]);
                data.WriteBit(playerGuid[6]);
                data.FlushBits();
                data.WriteByteSeq(playerGuid[6]);
                data.WriteByteSeq(playerGuid[7]);
                data.WriteByteSeq(playerGuid[0]);
                data.WriteByteSeq(playerGuid[2]);
                data.WriteByteSeq(playerGuid[3]);
                data.WriteByteSeq(playerGuid[1]);
                data.WriteByteSeq(playerGuid[5]);
                data.WriteByteSeq(playerGuid[4]);
                mover->SendMessageToSet(&data,false);
            }
            break;
        }
        case MOVEMENTFLAG_FALLING_SLOW:
        {
            if(hasFlag)
            {
                WorldPacket data(SMSG_SPLINE_MOVE_SET_FEATHER_FALL);
                data.WriteBit(playerGuid[3]);
                data.WriteBit(playerGuid[2]);
                data.WriteBit(playerGuid[7]);
                data.WriteBit(playerGuid[5]);
                data.WriteBit(playerGuid[4]);
                data.WriteBit(playerGuid[6]);
                data.WriteBit(playerGuid[1]);
                data.WriteBit(playerGuid[0]);
                data.FlushBits();
                data.WriteByteSeq(playerGuid[1]);
                data.WriteByteSeq(playerGuid[4]);
                data.WriteByteSeq(playerGuid[7]);
                data.WriteByteSeq(playerGuid[6]);
                data.WriteByteSeq(playerGuid[2]);
                data.WriteByteSeq(playerGuid[0]);
                data.WriteByteSeq(playerGuid[5]);
                data.WriteByteSeq(playerGuid[3]);
                mover->SendMessageToSet(&data,false);
            }
            else
            {
                WorldPacket data(SMSG_SPLINE_MOVE_SET_NORMAL_FALL);
                data.WriteBit(playerGuid[3]);
                data.WriteBit(playerGuid[5]);
                data.WriteBit(playerGuid[1]);
                data.WriteBit(playerGuid[0]);
                data.WriteBit(playerGuid[6]);
                data.WriteBit(playerGuid[7]);
                data.WriteBit(playerGuid[2]);
                data.WriteBit(playerGuid[4]);
                data.FlushBits();
                data.WriteByteSeq(playerGuid[7]);
                data.WriteByteSeq(playerGuid[6]);
                data.WriteByteSeq(playerGuid[2]);
                data.WriteByteSeq(playerGuid[0]);
                data.WriteByteSeq(playerGuid[5]);
                data.WriteByteSeq(playerGuid[4]);
                data.WriteByteSeq(playerGuid[3]);
                data.WriteByteSeq(playerGuid[1]);
                mover->SendMessageToSet(&data,false);
            }
        }
    }
}

void WorldSession::SendPlayerMove(MovementInfo *mi)
{
    bool hasOrientation = !G3D::fuzzyEq(mi->pos.GetOrientation(), 0.0f);
    WorldPacket data(SMSG_PLAYER_MOVE);
    ObjectGuid playerGuid = mi->guid;
    ObjectGuid transportGuid = mi->t_guid;

    mi->time = getMSTime();
    
    data.WriteBit(mi->bits.hasFallData);
    data.WriteBit(playerGuid[3]);
    data.WriteBit(playerGuid[6]);
    data.WriteBit(!mi->flags2 != 0);
    data.WriteBit(mi->bits.hasSpline);
    data.WriteBit(!mi->time != 0);
    data.WriteBit(playerGuid[0]);
    data.WriteBit(playerGuid[1]);
    if(mi->flags2 != 0)
        data.WriteBits(mi->flags2,12);
    data.WriteBit(playerGuid[7]);
    data.WriteBit(!mi->flags != 0);
    data.WriteBit(!hasOrientation);
    data.WriteBit(playerGuid[2]);
    data.WriteBit(!mi->bits.hasSplineElev);
    data.WriteBit(true);
    data.WriteBit(playerGuid[4]);
    if(mi->bits.hasFallData)
        data.WriteBit(mi->bits.hasFallDirection);
    data.WriteBit(playerGuid[5]);
    data.WriteBit(mi->bits.hasTransportData);
    if(mi->flags != 0)
        data.WriteBits(mi->flags,30);
    if(mi->bits.hasTransportData)
    {
        data.WriteBit(transportGuid[3]);
        data.WriteBit(mi->t_time3 != 0);
        data.WriteBit(transportGuid[6]);
        data.WriteBit(transportGuid[1]);
        data.WriteBit(transportGuid[7]);
        data.WriteBit(transportGuid[0]);
        data.WriteBit(transportGuid[4]);
        data.WriteBit(mi->t_time2 != 0);
        data.WriteBit(transportGuid[5]);
        data.WriteBit(transportGuid[2]);
    }
    data.WriteBit(!mi->bits.hasPitch);
    data.FlushBits();
    if(playerGuid[5])
        data.WriteByteSeq(playerGuid[5]);
    if(mi->bits.hasFallData)
    {
        if(mi->bits.hasFallDirection)
        {
            data << mi->j_xyspeed << mi->j_cosAngle << mi->j_sinAngle;
        }
        data << mi->j_zspeed << mi->fallTime;
    }
    if(mi->bits.hasSplineElev)
        data << mi->splineElevation;
    if(playerGuid[7])
        data.WriteByteSeq(playerGuid[7]);
    data << mi->pos.GetPositionY();
    if(playerGuid[3])
        data.WriteByteSeq(playerGuid[3]);
    if(mi->bits.hasTransportData)
    {
        if(mi->t_time3 != 0)
            data << mi->t_time3;
        if(transportGuid[6])
            data.WriteByteSeq(transportGuid[6]);
        data << mi->t_seat;
        if(transportGuid[5])
            data.WriteByteSeq(transportGuid[5]);
        data << mi->t_pos.GetPositionX();
        if(transportGuid[1])
            data.WriteByteSeq(transportGuid[1]);
        data << mi->t_pos.GetOrientation();
        if(transportGuid[2])
            data.WriteByteSeq(transportGuid[2]);
        if(mi->t_time2 != 0)
            data << mi->t_time2;
        if(transportGuid[0])
            data.WriteByteSeq(transportGuid[0]);
        data << mi->t_pos.GetPositionZ();
        if(transportGuid[7])
            data.WriteByteSeq(transportGuid[7]);
        if(transportGuid[4])
            data.WriteByteSeq(transportGuid[4]);
        if(transportGuid[3])
            data.WriteByteSeq(transportGuid[3]);
        data << mi->t_pos.GetPositionY() << mi->t_time;
    }
    if(playerGuid[4])
        data.WriteByteSeq(playerGuid[4]);
    data << mi->pos.GetPositionX();
    if(playerGuid[6])
        data.WriteByteSeq(playerGuid[6]);
    data << mi->pos.GetPositionZ();
    if(mi->bits.hasTimestamp)
        data << mi->time;
    if(playerGuid[2])
        data.WriteByteSeq(playerGuid[2]);
    if(mi->bits.hasPitch)
        data << mi->pitch;
    if(playerGuid[0])
        data.WriteByteSeq(playerGuid[0]);
    if(hasOrientation)
        data << mi->pos.GetOrientation();
    if(playerGuid[1])
        data.WriteByteSeq(playerGuid[1]);

    GetPlayer()->SendMessageToSet(&data, GetPlayer());
}
