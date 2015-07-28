/*
NpcBot System by Graff (onlysuffering@gmail.com)
Original patch from: LordPsyan https://bitbucket.org/lordpsyan/trinitycore-patches/src/3b8b9072280e/Individual/11185-BOTS-NPCBots.patch
TODO:
Convert doCast events (CD etc.) into SpellHit()- and SpellHitTarget()-based
Implement heal/tank/DD modes
Implement Racial Abilities
I NEED MORE
*/

#include "bot_ai.h"
#include "bot_GridNotifiers.h"
#include "CellImpl.h"
#include "Chat.h"
#include "Config.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "ScriptedGossip.h"
#include "SpellAuraEffects.h"

const uint8 GroupIconsFlags[TARGETICONCOUNT] =
{
    /*STAR        = */0x001,
    /*CIRCLE      = */0x002,
    /*DIAMOND     = */0x004,
    /*TRIANGLE    = */0x008,
    /*MOON        = */0x010,
    /*SQUARE      = */0x020,
    /*CROSS       = */0x040,
    /*SKULL       = */0x080
};

BotClassLevelInfo classinfo;

bot_minion_ai::bot_minion_ai(Creature* creature): bot_ai(creature)
{
    Potion_cd = 0;
    pvpTrinket_cd = 30000;
    rezz_cd = 0;
    evade_cd = 0;
    myangle = 0.f;
    mana_cd = uint32(-1);
    health_cd = uint32(-1);
    for (uint8 i = 0; i != BOT_INVENTORY_SIZE; ++i)
        for (uint8 j = 0; j != MAX_BOT_ITEM_MOD; ++j)
            _stats[i][j] = 0;
    for (uint8 i = 0; i != MAX_BOT_CTC_SPELLS; ++i)
    {
        _ctc[i].first = 0;
        _ctc[i].second = 0;
    }
}
bot_minion_ai::~bot_minion_ai() {}

bot_pet_ai::bot_pet_ai(Creature* creature): bot_ai(creature)
{
    m_creatureOwner = me->GetCreatureOwner();
    basearmor = 0;
}
bot_pet_ai::~bot_pet_ai(){}

bot_ai::bot_ai(Creature* creature) : ScriptedAI(creature)
{
    master = me->GetBotOwner();
    m_spellpower = 0;
    m_block = 1;
    haste = 0;
    hit = 0.f;
    regen_mp5 = 0.f;
    m_TankGuid = 0;
    tank = NULL;
    extank = NULL;
    info = NULL;
    clear_cd = 2;
    temptimer = 0;
    wait = 15;
    GC_Timer = 0;
    checkAurasTimer = 20;
    cost = 0;
    doHealth = false;
    doMana = false;
    //shouldUpdateStats = true;
    pos.m_positionX = 0.f;
    pos.m_positionY = 0.f;
    pos.m_positionZ = 0.f;
    aftercastTargetGuid = 0;
    currentSpell = 0;
    tempMana = 0;
    dmgmult_melee = sConfigMgr->GetFloatDefault("Bot.DamageMult.Melee", 1.0);
    dmgmult_spell = sConfigMgr->GetFloatDefault("Bot.DamageMult.Spell", 1.0) * 0.75f;
    dmgmult_melee = std::max(dmgmult_melee, 0.01f);
    dmgmult_spell = std::max(dmgmult_spell, 0.01f);
    dmgmult_melee = std::min(dmgmult_melee, 10.f);
    dmgmult_spell = std::min(dmgmult_spell, 10.f);
    dmgmod_melee = Creature::_GetDamageMod(me->GetCreatureTemplate()->rank);
    dmgmod_spell = me->GetSpellDamageMod(me->GetCreatureTemplate()->rank);
    healTargetIconFlags = sConfigMgr->GetIntDefault("Bot.HealTargetIconsMask", 8);
    PvP = sConfigMgr->GetIntDefault("Bot.PvP", 1);
}
bot_ai::~bot_ai(){}

SpellCastResult bot_ai::checkBotCast(Unit* victim, uint32 spellId, uint8 botclass) const
{
    if (spellId == 0)
        return SPELL_FAILED_DONT_REPORT;

    if (InDuel(victim))
        return SPELL_FAILED_DONT_REPORT;

    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
    if (!spellInfo)
        return SPELL_FAILED_DONT_REPORT;

    if (!CheckImmunities(spellId, victim))
        return SPELL_FAILED_DONT_REPORT;

    if (Powers(spellInfo->PowerType) == me->getPowerType() &&
        (int32)me->GetPower(me->getPowerType()) < spellInfo->CalcPowerCost(me, spellInfo->GetSchoolMask()))
        return SPELL_FAILED_DONT_REPORT;

    switch (botclass)
    {
        case CLASS_PALADIN:
        case CLASS_MAGE:
        case CLASS_PRIEST:
        case CLASS_DRUID:
        case CLASS_WARLOCK:
        case CLASS_SHAMAN:
            if (Feasting() && !master->IsInCombat() && !master->HasAuraType(SPELL_AURA_PERIODIC_DAMAGE))
                return SPELL_FAILED_DONT_REPORT;
            break;
        case CLASS_WARRIOR:
            //BladeStorm
            if (me->HasAura(46924/*67541*/))
                return SPELL_FAILED_DONT_REPORT;
            break;
        case CLASS_ROGUE:
        case CLASS_HUNTER:
        case CLASS_DEATH_KNIGHT:
        default:
            break;
    }

    return SPELL_CAST_OK;
}

bool bot_ai::doCast(Unit* victim, uint32 spellId, bool triggered, uint64 originalCaster)
{
    if (spellId == 0) return false;
    if (me->IsMounted()) return false;
    if (IsCasting()) return false;
    if (!victim || !victim->IsInWorld() || me->GetMap() != victim->FindMap()) return false;

    info = sSpellMgr->GetSpellInfo(spellId);
    if (!info)
        return false;

    if (spellId == MANAPOTION)
    {
        value = urand(me->GetMaxPower(POWER_MANA)/4, me->GetMaxPower(POWER_MANA)/2);
        me->CastCustomSpell(victim, spellId, &value, 0, 0, true);
        return true;
    }

    //remove shapeshifts manually to restore powers/stats
    if (me->GetShapeshiftForm() != FORM_NONE)
    {
        if (info->CheckShapeshift(me->GetShapeshiftForm()) != SPELL_CAST_OK)
            removeFeralForm(true);
    }

    if (spellId != HEALINGPOTION && spellId != MANAPOTION)
        me->SetStandState(UNIT_STAND_STATE_STAND);

    if (!victim->IsWithinLOSInMap(me) && IsInBotParty(victim))
    {
        //std::ostringstream msg;
        //msg << "casting " << spellInfo->SpellName[0] << " on " << victim->GetName();
        //me->MonsterWhisper(msg.str().c_str(), master->GetGUID());
        me->Relocate(victim);
    }

    TriggerCastFlags flags = triggered ? TRIGGERED_FULL_MASK : TRIGGERED_NONE;
    SpellCastTargets targets;
    targets.SetUnitTarget(victim);
    Spell* spell = new Spell(me, info, flags, originalCaster);
    spell->prepare(&targets); //sets current spell if succeed

    bool casted = triggered; //triggered casts are casted immediately
    for (uint8 i = 0; i != CURRENT_MAX_SPELL; ++i)
    {
        if (me->GetCurrentSpell(i) == spell)
        {
            casted = true;
            break;
        }
    }

    if (!casted)
    {
        //failed to cast
        //delete spell; //crash due to invalid event added to master's eventmap
        return false;
    }

    currentSpell = spellId;

    if (me->GetBotClass() == CLASS_ROGUE || GetBotStance() == DRUID_CAT_FORM || GetBotStance() == DEATH_KNIGHT_UNHOLY_PRESENCE)
        value = int32(1000.f - 1000.f*(float(haste) / 100.f));
    else
        value = int32(1500.f - 1500.f*(float(haste) / 100.f));

    GC_Timer = std::max<uint32>(value, 500);

    return true;
}
//Follow point calculation
void bot_minion_ai::CalculatePos(Position & pos)
{
    uint8 followdist = master->GetBotFollowDist();
    Unit* followTarget = master;
    float mydist, angle;
    if (master->GetBotTankGuid() == me->GetGUID())
    {
        mydist = frand(3.5f, 6.5f); //stand a bit farther
        angle = (M_PI/2.f) / 16.f * frand(-3.f, 3.f); //in front +-pi/5
    }
    else
    {
        switch (me->GetBotClass())
        {
            case CLASS_WARRIOR: case CLASS_DEATH_KNIGHT: case CLASS_PALADIN:
                mydist = frand(0.2f, 1.f);
                angle = (M_PI/2.f) / 8.f * RAND(frand(5.f, 10.f), frand(-10.f, -5.f)); //to the sides +-(pi/3 to pi/1.6)
                break;
            case CLASS_WARLOCK: case CLASS_PRIEST: case CLASS_MAGE:
                mydist = frand(0.15f, 0.8f);
                angle = (M_PI/2.f) / 6.f * frand(10.5f, 13.5f); //behind pi+-pi/4.5
                break;
            case CLASS_SHAMAN:
                if (isTwoHander())
                {
                    mydist = frand(0.2f, 1.f);
                    angle = (M_PI/2.f) / 8.f * RAND(frand(5.f, 10.f), frand(-10.f, -5.f)); //to the sides +-(pi/3 to pi/1.6)
                }
                else
                {
                    mydist = frand(0.15f, 0.8f);
                    angle = (M_PI/2.f) / 6.f * frand(10.5f, 13.5f); //behind pi+-pi/4.5
                }
                break;
            default:
                mydist = frand(0.3f, 1.2f);
                angle = (M_PI/2.f) / 6.f * frand(9.f, 15.f); //behind pi+-pi/3
                break;
        }
    }
    //myangle = angle used last time
    //if difference between last angle and cur angle is too big, use new angle
    //else use last angle (prevent constant struggling)
    if (abs(abs(myangle) - abs(angle)) > M_PI/3.f)
        myangle = angle;
    else
        angle = myangle;
    mydist += followdist > 10 ? float(followdist - 10)/4.f : 0.f; //distance from 10+ is reduced
    mydist = std::min<float>(mydist, 35.f); //do not spread bots too much
    angle += followTarget->GetOrientation();
    float x(0),y(0),z(0);
    float size = me->GetObjectSize()/3.f;
    bool over = false;
    for (uint8 i = 0; i != 5 + over; ++i)
    {
        if (over)
        {
            mydist *= 0.2f;
            break;
        }
        followTarget->GetNearPoint(me, x, y, z, size, mydist, angle);
        if (!master->IsWithinLOS(x,y,z)) //try to get much closer to master
        {
            mydist *= 0.4f - float(i*0.07f);
            size *= 0.1f;
            if (size < 0.1)
                size = 0.f;
            if (size == 0.f && me->GetPositionZ() < followTarget->GetPositionZ())
                z += 0.25f; //prevent going underground
        }
        else
            over = true;
    }
    pos.m_positionX = x;
    pos.m_positionY = y;
    pos.m_positionZ = z;

    //            T
    //           TTT
    //    mmmmmmmm mmmmmmmm
    //   mmmmmmm MMM mmmmmmm
    //   mmmmm rrrrrrr mmmmm
    //    ddd rrrrrrrrr ddd
    //     ddddddddddddddd
    //       ddddddddddd
    //
    //MMM - player
    //TTT - bot tank
    //m - melee (warrior, paladin, deathknight, ench shaman)
    //d - default (druid, rogue, hunter)
    //r - ranged/support (priest, warlock, mage, elem shaman)
}
// Movement set
void bot_minion_ai::SetBotCommandState(CommandStates st, bool force, Position* newpos)
{
    if (me->IsDead() || IAmDead())
        return;
    if (st == COMMAND_FOLLOW && ((!me->isMoving() && !IsCasting() && master->IsAlive()) || force))
    {
        if (CCed(me, true)/* || master->HasUnitState(UNIT_STATE_FLEEING)*/) return;
        if (me->isMoving() && Rand() > 25) return;
        if (!newpos)
            CalculatePos(pos);
        else
        {
            pos.m_positionX = newpos->m_positionX;
            pos.m_positionY = newpos->m_positionY;
            pos.m_positionZ = newpos->m_positionZ;
        }
        if (me->getStandState() == UNIT_STAND_STATE_SIT && !Feasting())
            me->SetStandState(UNIT_STAND_STATE_STAND);
        me->GetMotionMaster()->MovePoint(master->GetMapId(), pos);
        //me->GetMotionMaster()->MoveFollow(master, mydist, angle);
    }
    else if (st == COMMAND_STAY)
    {
        me->StopMoving();
        me->GetMotionMaster()->Clear();
        me->GetMotionMaster()->MoveIdle();
    }
    else if (st == COMMAND_ATTACK)
    { 
        if (Unit* victim = master->GetSelectedUnit())
        {
            if (InDuel(victim))
                return;

            victim->Attack(me, true);
            me->Attack(victim, true);
        }
    }
    m_botCommandState = st;
    if (Creature* m_botsPet = me->GetBotsPet())
        m_botsPet->SetBotCommandState(st, force);
}

void bot_pet_ai::SetBotCommandState(CommandStates st, bool force, Position* /*newpos*/)
{
    if (me->IsDead() || IAmDead())
        return;
    if (st == COMMAND_FOLLOW && ((!me->isMoving() && !IsCasting() && master->IsAlive()) || force))
    {
        if (CCed(me, true)) return;
        if (me->isMoving() && Rand() > 25) return;
        Unit* followtarget = m_creatureOwner;
        if (CCed(m_creatureOwner))
            followtarget = master;
        if (followtarget == m_creatureOwner)
        {
            if (!me->HasUnitState(UNIT_STATE_FOLLOW) || me->GetDistance(master)*0.75f < me->GetDistance(m_creatureOwner))
                me->GetMotionMaster()->MoveFollow(m_creatureOwner, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);
        }
        else
            if (!me->HasUnitState(UNIT_STATE_FOLLOW) || me->GetDistance(m_creatureOwner)*0.75f < me->GetDistance(master))
                me->GetMotionMaster()->MoveFollow(master, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);
    }
    else if (st == COMMAND_STAY)//NUY
    {
        me->StopMoving();
        me->GetMotionMaster()->Clear();
        me->GetMotionMaster()->MoveIdle();
    }
    else if (st == COMMAND_ATTACK)
    { 
        
    }
    m_botCommandState = st;
}
// Get Maintank
void bot_ai::FindTank()
{
    if (tank == me)
        extank = me;
    //check group flags in DB
    tank = _GetBotGroupMainTank(master->GetGroup());
    //check if master has set tank
    if (!tank)
        tank = master->GetBotTankGuid() != 0 ? sObjectAccessor->GetObjectInWorld(master->GetBotTankGuid(), (Unit*)NULL) : NULL;
    //check if we have tank flag in master's motmap
    if (!tank)
        tank = master->GetBotTank(me->GetEntry());
    //at last try to find tank by class if master is too lazy to set it
    if (!tank)
    {
        Player* owner = master;
        uint8 Class = owner->getClass();
        if (owner->IsAlive() &&
            (Class == CLASS_WARRIOR || Class == CLASS_PALADIN || Class == CLASS_DEATH_KNIGHT))
            tank = owner;
        else if (owner != master && master->IsAlive())
        {
            Class = master->getClass();
            if (Class == CLASS_WARRIOR || Class == CLASS_PALADIN || Class == CLASS_DEATH_KNIGHT)
                tank = master;
        }
    }
    //it happens to every bot so they all will know who the tank is
    if (tank != extank)
        me->SetBotTank(tank);
    if (tank == me)
    {
        //if tank set by entry let master get right guid and set tank in botmap
        if (master->GetBotTankGuid() != me->GetGUID())
            master->SetBotTank(me->GetGUID());
    }
}
//Get Group maintank
Unit* bot_ai::_GetBotGroupMainTank(Group* group)
{
    if (!group)
        return NULL;

    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_MAINTANK);
    stmt->setUInt32(0, group->GetGUID());
    PreparedQueryResult result = CharacterDatabase.Query(stmt);
    //QueryResult result = CharacterDatabase.PQuery("SELECT memberGuid, memberFlags FROM `group_member` WHERE `guid`='%u'", group->GetGUID());
    if (!result)
        return NULL;
    Unit* unit = NULL;
    do
    {
        Field* field = result->Fetch();
        uint32 lowGuid = field[0].GetInt32();
        uint8 flags = field[1].GetInt8();
        if (flags & MEMBER_FLAG_MAINTANK)
        {
            Group::MemberSlotList const &members = group->GetMemberSlots();
            for (Group::MemberSlotList::const_iterator itr = members.begin(); itr != members.end(); ++itr)
                if (GUID_LOPART(itr->guid) == lowGuid)
                    unit = ObjectAccessor::FindUnit(itr->guid);
        }
    } while (result->NextRow() && !unit);
    return unit;
}
// Buffs And Heal (really)
void bot_minion_ai::BuffAndHealGroup(Player* gPlayer, uint32 diff)
{
    if (GC_Timer > diff) return;
    if (me->IsMounted()) return;
    if (IsCasting() || Feasting()) return;

    Group* pGroup = gPlayer->GetGroup();
    if (!pGroup)
    {
        if (!master->IsInWorld() || master->IsBeingTeleported())
            return;
        if (HealTarget(master, GetHealthPCT(master), diff))
            return;
        if (BuffTarget(master, diff))
            return;
        for (Unit::ControlList::const_iterator itr = master->m_Controlled.begin(); itr != master->m_Controlled.end(); ++itr)
        {
            Unit* u = *itr;
            if (!u || !u->IsInWorld() || me->GetMap() != u->FindMap() || !u->IsAlive()) continue;
            if (HealTarget(u, GetHealthPCT(u), diff))
                return;
            if (Creature* cre = u->ToCreature())
                if (cre->GetIAmABot() || cre->IsPet())
                    if (BuffTarget(u, diff))
                        return;
        }
        return;
    }
    bool Bots = false;
    for (GroupReference* itr = pGroup->GetFirstMember(); itr != NULL; itr = itr->next())
    {
        Player* tPlayer = itr->GetSource();
        if (tPlayer == NULL) continue;
        if (me->GetMap() != tPlayer->FindMap()) continue;
        if (!tPlayer->m_Controlled.empty())
            Bots = true;
        if (!tPlayer->IsAlive()) continue;
        if (HealTarget(tPlayer, GetHealthPCT(tPlayer), diff))
            return;
        if (BuffTarget(tPlayer, diff))
            return;
    }
    if (Bots)
    {
        for (GroupReference* itr = pGroup->GetFirstMember(); itr != NULL; itr = itr->next())
        {
            Player* tPlayer = itr->GetSource();
            if (tPlayer == NULL || tPlayer->m_Controlled.empty()) continue;
            if (me->GetMap() != tPlayer->FindMap()) continue;
            for (Unit::ControlList::const_iterator itr = tPlayer->m_Controlled.begin(); itr != tPlayer->m_Controlled.end(); ++itr)
            {
                Unit* u = *itr;
                if (!u || !u->IsInWorld() || me->GetMap() != u->FindMap() || !u->IsAlive()) continue;
                if (HealTarget(u, GetHealthPCT(u), diff))
                    return;
                if (Creature* cre = u->ToCreature())
                    if (cre->GetIAmABot() || cre->IsPet())
                        if (BuffTarget(u, diff))
                            return;
            }
        }
    }
    //check if we have pointed heal target
    for (uint8 i = 0; i != TARGETICONCOUNT; ++i)
    {
        if (healTargetIconFlags & GroupIconsFlags[i])
        {
            if (uint64 guid = pGroup->GetTargetIcons()[i])//check this one
            {
                if (Unit* unit = sObjectAccessor->FindUnit(guid))
                {
                    if (unit->IsAlive() && me->GetMap() == unit->FindMap() &&
                        master->GetVictim() != unit && unit->GetVictim() != master &&
                        unit->GetReactionTo(master) >= REP_NEUTRAL)
                    {
                        HealTarget(unit, GetHealthPCT(unit), diff);
                        //CureTarget(unit, getCureSpell(), diff);
                    }
                }
            }
        }
    }
}
// Attempt to resurrect dead players using class spells
// Target is either player or its corpse
void bot_minion_ai::RezGroup(uint32 REZZ, Player* gPlayer)
{
    if (!REZZ || !gPlayer || me->IsMounted()) return;
    if (IsCasting()) return;
    if (rezz_cd > 0) return;

    //sLog->outBasic("RezGroup by %s", me->GetName().c_str());
    Group* pGroup = gPlayer->GetGroup();
    if (!pGroup)
    {
        Unit* target = master;
        if (master->IsAlive()) return;
        if (master->IsRessurectRequested()) return; //resurrected
        if (master->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST))
            target = (Unit*)master->GetCorpse();
        if (!target || !target->IsInWorld()) return;
        if (me->GetMap() != target->FindMap()) return;
        if (me->GetDistance(target) > 30)
        {
            me->GetMotionMaster()->MovePoint(master->GetMapId(), *target);
            rezz_cd = 3;//6-9 sec reset
            return;
        }
        else if (!target->IsWithinLOSInMap(me))
            me->Relocate(*target);

        if (doCast(target, REZZ))//rezzing it
        {
            me->MonsterWhisper( "Rezzing You", master);
            rezz_cd = 60;
        }
        return;
    }
    for (GroupReference* itr = pGroup->GetFirstMember(); itr != NULL; itr = itr->next())
    {
        Player* tPlayer = itr->GetSource();
        Unit* target = tPlayer;
        if (!tPlayer || tPlayer->IsAlive()) continue;
        if (tPlayer->IsRessurectRequested()) continue; //resurrected
        if (Rand() > 5) continue;
        if (tPlayer->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST))
            target = (Unit*)tPlayer->GetCorpse();
        if (!target || !target->IsInWorld()) continue;
        if (master->GetMap() != target->FindMap()) continue;
        if (me->GetDistance(target) > 30)
        {
            me->GetMotionMaster()->MovePoint(master->GetMapId(), *target);
            rezz_cd = 3;//6-9 sec reset
            return;
        }
        else if (!target->IsWithinLOSInMap(me))
            me->Relocate(*target);

        if (doCast(target, REZZ))//rezzing it
        {
            me->MonsterWhisper("Rezzing You", tPlayer);
            if (tPlayer != master)
            {
                std::string rezstr = "Rezzing ";
                rezstr += tPlayer->GetName();
                me->MonsterWhisper(rezstr.c_str(), master);
            }
            rezz_cd = 60;
            return;
        }
    }
}
// CURES
//cycle through the group sending members for cure
void bot_minion_ai::CureGroup(Player* pTarget, uint32 cureSpell, uint32 diff)
{
    if (!cureSpell || GC_Timer > diff) return;
    if (me->getLevel() < 10 || pTarget->getLevel() < 10) return;
    if (me->IsMounted()) return;
    if (IsCasting() || Feasting()) return;
    if (!master->GetMap()->IsRaid() && Rand() > 75) return;
    //sLog->outBasic("%s: CureGroup() on %s", me->GetName().c_str(), pTarget->GetName().c_str());
    Group* pGroup = pTarget->GetGroup();
    if (!pGroup)
    {
        if (CureTarget(master, cureSpell, diff))
            return;
        for (uint8 i = 0; i != master->GetMaxNpcBots(); ++i)
        {
            Creature* cre = master->GetBotMap(i)->_Cre();
            if (!cre || !cre->IsInWorld() || me->GetDistance(cre) > 30) continue;
            if (CureTarget(cre, cureSpell, diff))
                return;
        }
    }
    else
    {
        bool Bots = false;
        for (GroupReference* itr = pGroup->GetFirstMember(); itr != NULL; itr = itr->next())
        {
            Player* tPlayer = itr->GetSource();
            if (!tPlayer || (tPlayer->IsDead() && !tPlayer->HaveBot())) continue;
            if (!Bots && tPlayer->HaveBot())
                Bots = true;
            if (!tPlayer->IsInWorld() || tPlayer->IsBeingTeleported()) continue;
            if (me->GetMap() != tPlayer->FindMap()) continue;
            if (me->GetDistance(tPlayer) > 30) continue;
            if (CureTarget(tPlayer, cureSpell, diff))
                return;
        }
        if (!Bots) return;
        for (GroupReference* itr = pGroup->GetFirstMember(); itr != NULL; itr = itr->next())
        {
            Player* tPlayer = itr->GetSource();
            if (tPlayer == NULL || !tPlayer->HaveBot()) continue;
            if (!tPlayer->IsInWorld() || tPlayer->IsBeingTeleported()) continue;
            if (me->GetMap() != tPlayer->FindMap()) continue;
            for (uint8 i = 0; i != tPlayer->GetMaxNpcBots(); ++i)
            {
                Creature* cre = tPlayer->GetBotMap(i)->_Cre();
                if (!cre || !cre->IsInWorld() || me->GetDistance(cre) > 30) continue;
                if (CureTarget(cre, cureSpell, diff))
                    return;
            }
        }
    }
}

bool bot_minion_ai::CureTarget(Unit* target, uint32 cureSpell, uint32 diff)
{
    return CanCureTarget(target, cureSpell, diff) ? doCast(target, cureSpell) : false;
}
// determines if unit has something to cure
bool bot_minion_ai::CanCureTarget(Unit* target, uint32 cureSpell, uint32 diff) const
{
    if (!cureSpell || GC_Timer > diff) return false;
    if (!target || !target->IsAlive()) return false;
    if (me->getLevel() < 10 || target->getLevel() < 10) return false;
    if (me->IsMounted()) return false;
    if (IsCasting() || Feasting()) return false;
    if (me->GetDistance(target) > 30) return false;
    if (!IsInBotParty(target)) return false;

    SpellInfo const* info = sSpellMgr->GetSpellInfo(cureSpell);
    if (!info)
        return false;

    uint32 dispelMask = 0;
    for (uint8 i = 0; i != MAX_SPELL_EFFECTS; ++i)
        if (info->Effects[i].Effect == SPELL_EFFECT_DISPEL)
            dispelMask |= SpellInfo::GetDispelMask(DispelType(info->Effects[i].MiscValue));

    //debug - fix Remove Corruption: prevent from trying to dispel magic
    if (cureSpell == 2782)
        dispelMask &= ~(1 << DISPEL_MAGIC);

    if (dispelMask == 0)
        return false;

    DispelChargesList dispel_list;
    GetBotDispellableAuraList(target, me, dispelMask, dispel_list);

    return !(dispel_list.empty());
}

void bot_minion_ai::GetBotDispellableAuraList(Unit* target, Unit* caster, uint32 dispelMask, DispelChargesList& dispelList) const
{
    if (dispelMask & (1 << DISPEL_DISEASE) && target->HasAura(50536))
        dispelMask &= ~(1 << DISPEL_DISEASE);

    Unit::AuraMap const& auras = target->GetOwnedAuras();
    for (Unit::AuraMap::const_iterator itr = auras.begin(); itr != auras.end(); ++itr)
    {
        Aura* aura = itr->second;

        if (aura->IsPassive())
            continue;

        AuraApplication* aurApp = aura->GetApplicationOfTarget(target->GetGUID());
        if (!aurApp)
            continue;

        if (aura->GetSpellInfo()->GetDispelMask() & dispelMask)
        {
            //do not dispel positive auras from enemies and negative ones from friends
            if (aurApp->IsPositive() == target->IsFriendlyTo(caster))
                continue;

            //skip Vampiric Touch to prevent being CCed just heal it out
            if (aura->GetId() == 34914)
                continue;

            uint8 charges = (aura->GetSpellInfo()->AttributesEx7 & SPELL_ATTR7_DISPEL_CHARGES) ? aura->GetCharges() : aura->GetStackAmount();
            if (charges > 0)
                dispelList.push_back(std::make_pair(aura, charges));
        }
    }
}

bool bot_ai::HasAuraName(Unit* unit, uint32 spellId, uint64 casterGuid, bool exclude) const
{
    if (!spellId) return false;
    SpellInfo const* pSpellInfo = sSpellMgr->GetSpellInfo(spellId);
    if (!pSpellInfo) return false;

    const std::string name = pSpellInfo->SpellName;
    if (name.length() == 0) return false;

    return HasAuraName(unit, name, casterGuid, exclude);
}

bool bot_ai::HasAuraName(Unit* unit, const std::string spell, uint64 casterGuid, bool exclude) const
{
    if (spell.length() == 0) return false;

    if (!unit || unit->IsDead()) return false;

    Unit::AuraMap const& vAuras = unit->GetOwnedAuras();
    for (Unit::AuraMap::const_iterator itr = vAuras.begin(); itr != vAuras.end(); ++itr)
    {
        SpellInfo const* spellInfo = itr->second->GetSpellInfo();
        const std::string name = spellInfo->SpellName;
        if (spell == name)
            if (casterGuid == 0 || (casterGuid != 0 && exclude == (casterGuid != itr->second->GetCasterGUID())))
                return true;
    }
    return false;
}
//LIST AURAS
// Debug: Returns bot's info to called player
void bot_ai::listAuras(Player* player, Unit* unit) const
{
    if (!IsInBotParty(player)) return;
    if (!IsInBotParty(unit)) return;
    ChatHandler ch(player->GetSession());
    std::ostringstream botstring;
    if (unit->GetTypeId() == TYPEID_PLAYER)
        botstring << "player";
    else if (unit->GetTypeId() == TYPEID_UNIT)
    {
        if (unit->ToCreature()->GetIAmABot())
        {
            botstring << "minion bot, master: ";
            std::string const& ownername = unit->ToCreature()->GetBotOwner()->GetName();
            botstring << ownername;
        }
        else if (unit->ToCreature()->GetIAmABotsPet())
        {
            Player* owner = unit->ToCreature()->GetBotOwner();
            Creature* creowner = unit->ToCreature()->GetBotPetAI()->GetCreatureOwner();
            std::string const& ownername = owner ? owner->GetName() : "none";
            std::string const& creownername = creowner ? creowner->GetName() : "none";
            botstring << "pet bot, master: ";
            botstring << ownername;
            botstring << ", creature owner: ";
            botstring << creownername;
            if (creowner)
                botstring << " (" << creowner->GetGUIDLow() << ')';
        }
    }
    ch.PSendSysMessage("ListAuras for %s, %s", unit->GetName().c_str(), botstring.str().c_str());
    uint8 locale = player->GetSession()->GetSessionDbcLocale();
    Unit::AuraMap const &vAuras = unit->GetOwnedAuras();
    for (Unit::AuraMap::const_iterator itr = vAuras.begin(); itr != vAuras.end(); ++itr)
    {
        SpellInfo const* spellInfo = itr->second->GetSpellInfo();
        if (!spellInfo)
            continue;
        uint32 id = spellInfo->Id;
        SpellInfo const* learnSpellInfo = sSpellMgr->GetSpellInfo(spellInfo->Effects[0].TriggerSpell);
        const std::string name = spellInfo->SpellName;
        std::ostringstream spellmsg;
        spellmsg << id << " - |cffffffff|Hspell:" << id << "|h[" << name;
        spellmsg << ' ' << localeNames[locale] << "]|h|r";
        uint32 talentcost = GetTalentSpellCost(id);
        uint32 rank = 0;
        if (talentcost > 0 && spellInfo->GetNextRankSpell())
            rank = talentcost;
        else if (learnSpellInfo && learnSpellInfo->GetNextRankSpell())
            rank = spellInfo->GetRank();
        if (rank > 0)
            spellmsg << " Rank " << rank;
        if (talentcost > 0)
            spellmsg << " [talent]";
        if (spellInfo->IsPassive())
            spellmsg << " [passive]";
        if (unit->GetTypeId() == TYPEID_PLAYER && unit->ToPlayer()->HasSpell(id))
            spellmsg << " [known]";

        ch.PSendSysMessage(spellmsg.str().c_str());
    }
    for (uint8 i = STAT_STRENGTH; i != MAX_STATS; ++i)
    {
        std::string mystat;
        switch (i)
        {
            case STAT_STRENGTH: mystat = "str"; break;
            case STAT_AGILITY: mystat = "agi"; break;
            case STAT_STAMINA: mystat = "sta"; break;
            case STAT_INTELLECT: mystat = "int"; break;
            case STAT_SPIRIT: mystat = "spi"; break;
            default: mystat = "unk stat"; break;
        }
        ch.PSendSysMessage("%s: %f", mystat.c_str(), unit->GetTotalStatValue(Stats(i)));
    }
    ch.PSendSysMessage("Melee AP: %f", unit->GetTotalAttackPowerValue(BASE_ATTACK));
    ch.PSendSysMessage("Ranged AP: %f", unit->GetTotalAttackPowerValue(RANGED_ATTACK));
    ch.PSendSysMessage("armor: %u", unit->GetArmor());
    ch.PSendSysMessage("crit: %f pct", unit->GetUnitCriticalChance(BASE_ATTACK, me));
    ch.PSendSysMessage("dodge: %f pct", unit->GetUnitDodgeChance());
    ch.PSendSysMessage("parry: %f pct", unit->GetUnitParryChance());
    ch.PSendSysMessage("block: %f pct", unit->GetUnitBlockChance());
    ch.PSendSysMessage("block pct value: %f", float(unit->GetBlockPercent()));
    ch.PSendSysMessage("Damage taken melee: %f", unit->GetTotalAuraMultiplierByMiscMask(SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, SPELL_SCHOOL_MASK_NORMAL));
    ch.PSendSysMessage("Damage taken spell: %f", unit->GetTotalAuraMultiplierByMiscMask(SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, SPELL_SCHOOL_MASK_MAGIC));
    ch.PSendSysMessage("Damage range mainhand: min: %f, max: %f", unit->GetFloatValue(UNIT_FIELD_MINDAMAGE), unit->GetFloatValue(UNIT_FIELD_MAXDAMAGE));
    ch.PSendSysMessage("Damage range offhand: min: %f, max: %f", unit->GetFloatValue(UNIT_FIELD_MINOFFHANDDAMAGE), unit->GetFloatValue(UNIT_FIELD_MAXOFFHANDDAMAGE));
    ch.PSendSysMessage("Damage range ranged: min: %f, max: %f", unit->GetFloatValue(UNIT_FIELD_MINRANGEDDAMAGE), unit->GetFloatValue(UNIT_FIELD_MAXRANGEDDAMAGE));
    ch.PSendSysMessage("Damage mult mainhand: %f", unit->GetModifierValue(UNIT_MOD_DAMAGE_MAINHAND, BASE_PCT)*unit->GetModifierValue(UNIT_MOD_DAMAGE_MAINHAND, TOTAL_PCT));
    ch.PSendSysMessage("Damage mult offhand: %f", unit->GetModifierValue(UNIT_MOD_DAMAGE_OFFHAND, BASE_PCT)*unit->GetModifierValue(UNIT_MOD_DAMAGE_OFFHAND, TOTAL_PCT));
    ch.PSendSysMessage("Damage mult ranged: %f", unit->GetModifierValue(UNIT_MOD_DAMAGE_RANGED, BASE_PCT)*unit->GetModifierValue(UNIT_MOD_DAMAGE_RANGED, TOTAL_PCT));
    ch.PSendSysMessage("Attack time mainhand: %f", float(unit->GetAttackTime(BASE_ATTACK))/1000.f);
    ch.PSendSysMessage("Attack time offhand: %f", float(unit->GetAttackTime(OFF_ATTACK))/1000.f);
    ch.PSendSysMessage("Attack time ranged: %f", float(unit->GetAttackTime(RANGED_ATTACK))/1000.f);
    if (unit == me)
        ch.PSendSysMessage("melee damage mult: %f", dmgmult_melee);
    ch.PSendSysMessage("base hp: %u", unit->GetCreateHealth());
    ch.PSendSysMessage("total hp: %u", unit->GetMaxHealth());
    ch.PSendSysMessage("base mana: %u", unit->GetCreateMana());
    ch.PSendSysMessage("total mana: %u", unit->GetMaxPower(POWER_MANA));
    //DEBUG1
    //ch.PSendSysMessage("STATS: ");
    //ch.PSendSysMessage("Health");
    //ch.PSendSysMessage("base value: %f", unit->GetModifierValue(UNIT_MOD_HEALTH, BASE_VALUE));
    //ch.PSendSysMessage("base pct: %f", unit->GetModifierValue(UNIT_MOD_HEALTH, BASE_PCT));
    //ch.PSendSysMessage("total value: %f", unit->GetModifierValue(UNIT_MOD_HEALTH, TOTAL_VALUE));
    //ch.PSendSysMessage("total pct: %f", unit->GetModifierValue(UNIT_MOD_HEALTH, TOTAL_PCT));
    //ch.PSendSysMessage("Mana");
    //ch.PSendSysMessage("base value: %f", unit->GetModifierValue(UNIT_MOD_MANA, BASE_VALUE));
    //ch.PSendSysMessage("base pct: %f", unit->GetModifierValue(UNIT_MOD_MANA, BASE_PCT));
    //ch.PSendSysMessage("total value: %f", unit->GetModifierValue(UNIT_MOD_MANA, TOTAL_VALUE));
    //ch.PSendSysMessage("total pct: %f", unit->GetModifierValue(UNIT_MOD_MANA, TOTAL_PCT));
    //ch.PSendSysMessage("Stamina");
    //ch.PSendSysMessage("base value: %f", unit->GetModifierValue(UNIT_MOD_STAT_STAMINA, BASE_VALUE));
    //ch.PSendSysMessage("base pct: %f", unit->GetModifierValue(UNIT_MOD_STAT_STAMINA, BASE_PCT));
    //ch.PSendSysMessage("total value: %f", unit->GetModifierValue(UNIT_MOD_STAT_STAMINA, TOTAL_VALUE));
    //ch.PSendSysMessage("total pct: %f", unit->GetModifierValue(UNIT_MOD_STAT_STAMINA, TOTAL_PCT));
    //ch.PSendSysMessage("Intellect");
    //ch.PSendSysMessage("base value: %f", unit->GetModifierValue(UNIT_MOD_STAT_INTELLECT, BASE_VALUE));
    //ch.PSendSysMessage("base pct: %f", unit->GetModifierValue(UNIT_MOD_STAT_INTELLECT, BASE_PCT));
    //ch.PSendSysMessage("total value: %f", unit->GetModifierValue(UNIT_MOD_STAT_INTELLECT, TOTAL_VALUE));
    //ch.PSendSysMessage("total pct: %f", unit->GetModifierValue(UNIT_MOD_STAT_INTELLECT, TOTAL_PCT));
    //ch.PSendSysMessage("Spirit");
    //ch.PSendSysMessage("base value: %f", unit->GetModifierValue(UNIT_MOD_STAT_SPIRIT, BASE_VALUE));
    //ch.PSendSysMessage("base pct: %f", unit->GetModifierValue(UNIT_MOD_STAT_SPIRIT, BASE_PCT));
    //ch.PSendSysMessage("total value: %f", unit->GetModifierValue(UNIT_MOD_STAT_SPIRIT, TOTAL_VALUE));
    //ch.PSendSysMessage("total pct: %f", unit->GetModifierValue(UNIT_MOD_STAT_SPIRIT, TOTAL_PCT));
    //END DEBUG1
    if (unit == me)
    {
        ch.PSendSysMessage("spellpower: %u", m_spellpower/* - m_spellpower % 50*/);
        ch.PSendSysMessage("spell damage mult: %f", dmgmult_spell);
        ch.PSendSysMessage("mana regen: %f", regen_mp5/* - (int32(regen_mp5) % 45)*/);
        ch.PSendSysMessage("haste: %u *10 pct", haste);
        for (uint8 i = SPELL_SCHOOL_HOLY; i != MAX_SPELL_SCHOOL; ++i)
        {
            const char* resist = NULL;
            switch (i)
            {
                case 1: resist = "holy";   break;
                case 2: resist = "fire";   break;
                case 3: resist = "nature"; break;
                case 4: resist = "frost";  break;
                case 5: resist = "shadow"; break;
                case 6: resist = "arcane"; break;
            }
            ch.PSendSysMessage("Resistance %s: %u", resist, me->GetResistance(SpellSchools(i)));
        }
        ch.PSendSysMessage("BotCommandState: %s", m_botCommandState == COMMAND_FOLLOW ? "Follow" : m_botCommandState == COMMAND_ATTACK ? "Attack" : m_botCommandState == COMMAND_STAY ? "Stay" : m_botCommandState == COMMAND_ABANDON ? "Reset" : "none");
        ch.PSendSysMessage("Follow distance: %u", master->GetBotFollowDist());
        //ch.PSendSysMessage("healTargetIconFlags: %u", healTargetIconFlags);
        if (tank != NULL && tank->IsInWorld())
        {
            if (tank == me)
                ch.PSendSysMessage("Is a MainTank!");
            else
                ch.PSendSysMessage("Maintank is %s", tank->GetName().c_str());
        }

        ch.PSendSysMessage("Stat bonuses:");
        for (uint8 i = 0; i != MAX_BOT_ITEM_MOD; ++i)
        {
            int32 val = 0;
            uint32 const a = i;
            for (uint8 j = 0; j != BOT_INVENTORY_SIZE; ++j)
                val += static_cast<BotStat>(_stats[j])[a];

            if (val != 0)
                ch.PSendSysMessage("Item mod %u: bonus = %i", i, val);
        }

        ch.PSendSysMessage("CTCs:");
        for (uint8 i = 0; i != MAX_BOT_CTC_SPELLS; ++i)
        {
            if (!_ctc[i].first)
                continue;

            if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(_ctc[i].first))
            {
                std::ostringstream msg;
                msg << uint32(CalcCTC(_ctc[i].first)) << " pct to cast ";
                _AddSpellLink(player, spellInfo, msg);
                msg << " on damage deal";
                ch.PSendSysMessage(msg.str().c_str());
            }
        }

        //debug
        //if (IsPetAI()) GetPetAI()->ListSpells(&ch);
    }
}
//SETSTATS
// Health, Armor, Powers, Combat Ratings, and global update setup
void bot_minion_ai::setStats(uint8 myclass, uint8 myrace, uint8 mylevel, bool force, bool shapeshift)
{
    if (myrace == 0 || myclass == 0) return;
    if (myclass != DRUID_BEAR_FORM && myclass != DRUID_CAT_FORM && (master->IsDead() || (!shouldUpdateStats && !force))) return;
    /*sLog->outBasic("setStats(): Updating bot %s, class: %u, race: %u, level %u, master: %s",
        me->GetName().c_str(), myclass, myrace, mylevel, master->GetName().c_str());*/

    mylevel = std::min<uint8>(mylevel, 85);

    //Do not remove this code under any circumstances! You've been warned.
    if (myclass == CLASS_DEATH_KNIGHT)
        mylevel = std::max<uint8>(mylevel, 55);

    //LEVEL
    if (me->getLevel() != mylevel)
    {
        me->SetLevel(mylevel);
        force = true; //restore powers on lvl update
    }
    if (force)
    {
        InitPowers();
        InitSpells();
        //ApplyPassives(me->GetBotClass());

        //need to find a way to remove all passives before reapply (except levelups)
        //!!!this is only for gm's (players are not supposed to lower their level)
        ApplyClassPassives();
    }

    //PHASE
    if (master->GetPhaseMask() != me->GetPhaseMask())
        me->SetPhaseMask(master->GetPhaseMask(), true);
    //INIT STATS
    //partially receive master's stats and get base class stats, we'll need all this later
    uint8 tempclass = myclass == DRUID_BEAR_FORM || myclass == DRUID_CAT_FORM ? CLASS_DRUID : myclass;
    sObjectMgr->GetPlayerClassLevelInfo(tempclass, mylevel, classinfo.basehealth, classinfo.basemana);
    const CreatureBaseStats* const classstats = sObjectMgr->GetCreatureBaseStats(mylevel, me->getClass());//use creature class
    float value;
    if (force)
        for (uint8 i = STAT_STAMINA; i < MAX_STATS; i++)
            me->SetCreateStat(Stats(i), master->GetCreateStat(Stats(i)));

    //MAXSTAT
    for (uint8 i = 0; i < MAX_STATS; ++i)
    {
        value = master->GetTotalStatValue(Stats(i));
        if (i == 0 || value > stat)
            stat = value; //Get Hightest stat (on first cycle just set base value)
    }
    stat = std::max(stat - 18.f, 0.f); //base value for all stats is 18 (isn't counted in any way)

    //INIT CLASS MODIFIERS
    switch (myclass)
    {
        case CLASS_WARRIOR:      ap_mod = 1.3f; spp_mod = 0.0f; armor_mod = 1.4f;  crit_mod = 1.0f; haste_mod = 0.75f; dodge_mod = 0.75f; parry_mod = 1.75f; break;
        case CLASS_DEATH_KNIGHT: ap_mod = 1.2f; spp_mod = 0.0f; armor_mod = 1.05f; crit_mod = 1.1f; haste_mod = 1.05f; dodge_mod = 0.6f;  parry_mod = 1.95f;  break;
        case CLASS_PALADIN:      ap_mod = 1.0f; spp_mod = 0.8f; armor_mod = 1.2f;  crit_mod = 0.8f; haste_mod = 0.85f; dodge_mod = 0.7f;  parry_mod = 1.5f;  break;
        case CLASS_ROGUE:        ap_mod = 1.5f; spp_mod = 0.0f; armor_mod = 0.7f;  crit_mod = 1.5f; haste_mod = 1.35f; dodge_mod = 1.5f;  parry_mod = 0.8f;  break;
        case CLASS_HUNTER:       ap_mod = 1.7f; spp_mod = 0.2f; armor_mod = 1.0f;  crit_mod = 1.2f; haste_mod = 1.85f; dodge_mod = 1.3f;  parry_mod = 1.2f;  break;
        case CLASS_SHAMAN:       ap_mod = 1.1f; spp_mod = 0.5f; armor_mod = 1.1f;  crit_mod = 1.1f; haste_mod = 1.45f; dodge_mod = 1.1f;  parry_mod = 1.4f;  break;
        case CLASS_DRUID:        ap_mod = 0.0f; spp_mod = 1.3f; armor_mod = 0.7f;  crit_mod = 0.7f; haste_mod = 1.95f; dodge_mod = 0.5f;  parry_mod = 0.0f;  break;
        case CLASS_MAGE:         ap_mod = 0.0f; spp_mod = 0.8f; armor_mod = 0.5f;  crit_mod = 0.7f; haste_mod = 1.75f; dodge_mod = 0.5f;  parry_mod = 0.0f;  break;
        case CLASS_PRIEST:       ap_mod = 0.0f; spp_mod = 1.2f; armor_mod = 0.5f;  crit_mod = 0.7f; haste_mod = 1.75f; dodge_mod = 0.5f;  parry_mod = 0.0f;  break;
        case CLASS_WARLOCK:      ap_mod = 0.0f; spp_mod = 1.0f; armor_mod = 0.5f;  crit_mod = 0.7f; haste_mod = 1.75f; dodge_mod = 0.5f;  parry_mod = 0.0f;  break;
        case DRUID_BEAR_FORM:    ap_mod = 2.0f; spp_mod = 1.3f; armor_mod = 2.25f; crit_mod = 1.0f; haste_mod = 0.75f; dodge_mod = 2.5f;  parry_mod = 0.0f;  break;
        case DRUID_CAT_FORM:     ap_mod = 1.5f; spp_mod = 1.3f; armor_mod = 1.1f;  crit_mod = 1.5f; haste_mod = 2.25f; dodge_mod = 1.35f; parry_mod = 0.0f;  break;
        default:                 ap_mod = 0.0f; spp_mod = 0.0f; armor_mod = 0.0f;  crit_mod = 0.0f; haste_mod = 0.00f; dodge_mod = 0.0f;  parry_mod = 0.0f;  break;
    }
    if (spp_mod != 0.f && mylevel > 24)
        spp_mod *= (float(mylevel - 24))/61.f;// gain spell power slowly

    //DAMAGE
    _OnMeleeDamageUpdate(myclass);

    //ARMOR
    //sLog->outBasic("Unpdating %s's ARMOR: ", me->GetName().c_str());
    //sLog->outBasic("armor mod: %f", armor_mod);
    armor_mod *= (master->GetModifierValue(UNIT_MOD_ARMOR, BASE_PCT) + master->GetModifierValue(UNIT_MOD_ARMOR, TOTAL_PCT))/2.f;
    //sLog->outBasic("armor mod * master's modifier: %f", armor_mod);
    value = float(classstats->GenerateArmor(me->GetCreatureTemplate()) / 2);
    //sLog->outBasic("base armor: %f", value);
    value += float(master->GetArmor())/5.f;
    //sLog->outBasic("base armor + 1/5 of master's armor: %f", value);

    for (uint8 i = 0; i != BOT_INVENTORY_SIZE; ++i)
        value += _stats[i][BOT_ITEM_MOD_ARMOR];

    if (tank == me)
        armor_mod += 0.5f;
    if (GetBotStance() == DEATH_KNIGHT_FROST_PRESENCE)
        armor_mod += 0.6f;

    value *= armor_mod;
    //sLog->outBasic("multiplied by armor mod (total base armor): %f", value);
    me->SetModifierValue(UNIT_MOD_ARMOR, BASE_VALUE, value);
    me->UpdateArmor();//buffs will be took in consideration here

    //RESISTANCES
    //sLog->outBasic("Unpdating %s's RESISTANCES: ", me->GetName().c_str());
    for (uint8 i = SPELL_SCHOOL_HOLY; i != MAX_SPELL_SCHOOL; ++i)
    {
        value = float(master->GetResistance(SpellSchools(i)));

        uint8 mod = i == SPELL_SCHOOL_HOLY ? ITEM_MOD_HOLY_RESISTANCE :
            i == SPELL_SCHOOL_FIRE  ? ITEM_MOD_FIRE_RESISTANCE :
            i == SPELL_SCHOOL_NATURE  ? ITEM_MOD_NATURE_RESISTANCE :
            i == SPELL_SCHOOL_FROST  ? ITEM_MOD_FROST_RESISTANCE :
            i == SPELL_SCHOOL_SHADOW  ? ITEM_MOD_SHADOW_RESISTANCE : ITEM_MOD_SHADOW_RESISTANCE;

        for (uint8 j = 0; j != BOT_INVENTORY_SIZE; ++j)
            value += 2.5f * (_stats[j][mod]);

        //sLog->outBasic("master's resistance %u: %f, setting %f (triple) to bot", uint32(UNIT_MOD_RESISTANCE_START + i), value, value*3);
        me->SetModifierValue(UnitMods(UNIT_MOD_RESISTANCE_START + i), BASE_VALUE, value * 2.f + float(mylevel * 2));
        //me->SetModifierValue(UnitMods(UNIT_MOD_RESISTANCE_START + i), BASE_PCT, 1.f);
        me->UpdateResistances(i);
    }
    //DAMAGE TAKEN
    float directReduction = master->GetTotalAuraMultiplierByMiscMask(SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, SPELL_SCHOOL_MASK_NORMAL);
    float magicReduction = master->GetTotalAuraMultiplierByMiscMask(SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, SPELL_SCHOOL_MASK_MAGIC);
    value = (directReduction + magicReduction)/2.f; // average
    if (value > 1.f)
        value -= 1.f;
    else
        value = 1.f - value; //get reduction even if master's is 1.0+
    value = std::min(0.5f, value);
    value *= 100.f; //here we get percent like 0.5 * 100 = 50%
    if (mylevel > 81)
        value += float(mylevel - 81)*5.f;// + 3 stacks for high level
    RefreshAura(DMG_TAKEN, int8(value/10.f));//so max aura count = 10

    //HEALTH
    _OnHealthUpdate(myclass, mylevel);

    //HASTE
    value = 0.f;
    for (uint8 i = CR_HASTE_MELEE; i != CR_HASTE_SPELL + 1; ++i)
        if (float rating = master->GetRatingBonusValue(CombatRating(i)))
            if (rating > value) //master got some haste
                value = rating; //get hightest pct
    for (uint8 i = EQUIPMENT_SLOT_BACK; i < EQUIPMENT_SLOT_END; ++i)
        if (Item* item = master->GetItemByPos(0, i)) //inventory weapons
            if (item->GetTemplate()->ItemLevel >= 277) //bears ICC 25H LK items or Wrathful items
                value += 9.f; //only weapons so we can add 1 to 3 stacks (rogue, warr, sham...)

    if (mylevel >= 70)
    {
        for (uint8 i = 0; i != BOT_INVENTORY_SIZE; ++i)
        {
            //25.5 HR = 1% haste at 80 (12.75 for bot)
            float tempval = _stats[i][ITEM_MOD_HASTE_MELEE_RATING] + _stats[i][ITEM_MOD_HASTE_RANGED_RATING] + _stats[i][ITEM_MOD_HASTE_SPELL_RATING] + _stats[i][ITEM_MOD_HASTE_RATING];
            value += 3.f * (tempval / (25.5f * (float(mylevel - 40) / 40.f)));
        }
    }

    value *= haste_mod;
    if (isMeleeClass(myclass))
        value *= 0.67f; //nerf melee haste by 1/3
    value = value/3.f + float(mylevel/42);//get bonus at 84
    if (myclass == DRUID_CAT_FORM) //give cat lots of haste
        value += float(mylevel/17); //or 20 (+ 4-5 stacks);
    RefreshAura(HASTE,  uint8(value) + uint8(myclass == CLASS_SHAMAN) * 2); //spell haste
    RefreshAura(HASTE2, uint8(value) + uint8(myclass == CLASS_ROGUE)); //melee haste
    if (myclass == CLASS_ROGUE || myclass == CLASS_HUNTER)
        RefreshAura(HASTE3, uint8(value) + uint8(myclass == CLASS_HUNTER) * 2); //ranged haste
    haste = uint8(value); //for show only

    //HIT
    int32 melee_hit = master->GetTotalAuraModifier(SPELL_AURA_MOD_HIT_CHANCE) + master->GetTotalAuraModifier(SPELL_AURA_MOD_ATTACKER_MELEE_HIT_CHANCE);
    int32 spell_hit = master->GetTotalAuraModifier(SPELL_AURA_MOD_HIT_CHANCE) + master->GetTotalAuraModifier(SPELL_AURA_MOD_SPELL_HIT_CHANCE);
    value = float(melee_hit > spell_hit ? melee_hit : spell_hit) * 1.5f;//hightest, buff hit chance for bots

    if (mylevel >= 20)
    {
        for (uint8 i = 0; i != BOT_INVENTORY_SIZE; ++i)
        {
            //32.5 HR = 1% hit at 80
            float tempval = _stats[i][ITEM_MOD_HIT_MELEE_RATING] + _stats[i][ITEM_MOD_HIT_RANGED_RATING] + _stats[i][ITEM_MOD_HIT_SPELL_RATING] + _stats[i][ITEM_MOD_HIT_RATING];
            value += 5.f * (tempval / (32.5f * (float(mylevel - 10) / 70.f)));
        }
    }

    hit = value / 3.f;
    //RefreshAura(PRECISION,  int8(hit) + mylevel / 42); //melee
    RefreshAura(PRECISION);
    RefreshAura(PRECISION2, int8(hit) + mylevel / 42); //spell

    //CRIT
    //chose melee or ranged cuz crit rating increases melee/spell, and hunter benefits from agility
    value = master->GetUnitCriticalChance((master->getClass() == CLASS_HUNTER ? RANGED_ATTACK : BASE_ATTACK), me);
    value = value > 5.f ? value - 5.f : 0.f; //remove base chance if can

    if (mylevel >= 10)
    {
        for (uint8 i = 0; i != BOT_INVENTORY_SIZE; ++i)
        {
            //45 CR = 1% crit at 80
            float tempval = _stats[i][ITEM_MOD_CRIT_MELEE_RATING] + _stats[i][ITEM_MOD_CRIT_RANGED_RATING] + _stats[i][ITEM_MOD_CRIT_SPELL_RATING] + _stats[i][ITEM_MOD_CRIT_RATING];
            value += 1.5f * (tempval / (45.f * (float(mylevel - 5) / 75.f)));
        }
    }

    value *= crit_mod;
    RefreshAura(CRITS, int8(value / 3.f) + 1);
    if (myclass == CLASS_PRIEST)
        RefreshAura(HOLYCRIT, int8(value / 6.f)); //add holy crit to healers

    //PARRY
    value = 0.5f * master->GetFloatValue(PLAYER_PARRY_PERCENTAGE);
    value = value > 5.f ? value - 5.f : 0.f; //remove base chance if possible

    if (mylevel >= 30)
    {
        for (uint8 i = 0; i != BOT_INVENTORY_SIZE; ++i)
        {
            //67 PR = 1% parry at 80
            float tempval = _stats[i][ITEM_MOD_PARRY_RATING];
            value += 1.5f * (tempval / (67.f * (float(mylevel - 20) / 60.f)));
            //125 DR = 1% block/parry/dodge at 80
            tempval = _stats[i][ITEM_MOD_DEFENSE_SKILL_RATING];
            value += 1.5f * (tempval / (125.f * (float(mylevel - 20) / 60.f)));
        }
    }

    value *= parry_mod;
    if (master->GetBotTankGuid() == me->GetGUID() && myclass != DRUID_CAT_FORM && myclass != DRUID_BEAR_FORM) //feral cannot parry so let it be base 5%
        value += 10.f;
    //Forceful Deflection: 12.5% (half of base 25%) of strength (use max stat) goes to parry rating (~1% parry per 67 rating at 80)
    if (myclass == CLASS_DEATH_KNIGHT/* && mylevel >= 55*/)
        value += (stat / 8.f) / (float(mylevel) - (13.f / (float(mylevel - 40) / 40.f))); //~20 at 55, ~34 at 60 and 67 at 80
    if (value > 35.f)
        value = 35.f;
    float parryAndDodge = value; //set temp value, this is needed to keep total avoidance within 40%
    RefreshAura(PARRY, int8(value/6.f)); //6% per stack aplied

    //DODGE
    value = 0.5f * master->GetUnitDodgeChance();
    value = value > 5.f ? value - 5.f : 0.f; //remove base chance if possible

    if (mylevel >= 20)
    {
        for (uint8 i = 0; i != BOT_INVENTORY_SIZE; ++i)
        {
            //53 DR = 1% dodge at 80
            float tempval = _stats[i][ITEM_MOD_DODGE_RATING];
            value += 1.5f * (tempval / (53.f * (float(mylevel - 10) / 70.f)));
            //125 DR = 1% block/parry/dodge at 80
            tempval = _stats[i][ITEM_MOD_DEFENSE_SKILL_RATING];
            value += 1.5f * (tempval / (125.f * (float(mylevel - 10) / 70.f)));
        }
    }

    value *= dodge_mod;
    if (master->GetBotTankGuid() == me->GetGUID())
        value += 10.f;
    if (value > 35.f)
        value = 35.f;
    if (parryAndDodge + value > 35.f)
        value = 35.f - parryAndDodge; //do not allow avoidance to be more than 40% (base 5+5)
    RefreshAura(DODGE, int8(value / 5.f));

    //BLOCK
    if (!(me->GetCreatureTemplate()->flags_extra & CREATURE_FLAG_EXTRA_NO_BLOCK))
    {
        value = master->GetFloatValue(PLAYER_BLOCK_PERCENTAGE);
        if (mylevel >= 10)
        {
            for (uint8 i = 0; i != BOT_INVENTORY_SIZE; ++i)
            {
                //16.5 BR = 1% block at 80
                float tempval = _stats[i][ITEM_MOD_BLOCK_RATING];
                value += 1.5f * (tempval / (16.5f * (float(mylevel - 5) / 75.f)));
                //125 DR = 1% block/parry/dodge at 80
                tempval = _stats[i][ITEM_MOD_DEFENSE_SKILL_RATING];
                value += 2.5f * (tempval / (125.f * (float(mylevel - 5) / 75.f)));
            }
        }

        if (tank == me)
            value += 15.f;
        RefreshAura(BLOCK, int8(value / 5.f));

        //BLOCK VALUE
        float tempval = float(mylevel + mylevel / 4);
        //tempval += master->GetShieldBlockValue();
        for (uint8 i = 0; i != BOT_INVENTORY_SIZE; ++i)
        {
            tempval += 0.75f * (_stats[i][ITEM_MOD_STRENGTH]);
            tempval += 1.25f * (_stats[i][ITEM_MOD_BLOCK_VALUE]);
        }

        //Shield Mastery
        if (mylevel >= 20 && myclass == CLASS_WARRIOR)
            tempval *= 1.3f;

        tempval = std::max<float>(tempval - 10.f, 1.f);

        m_block = uint32(tempval);
    }
    else
        m_block = 1;

    //MANA
    _OnManaUpdate(myclass, mylevel, shapeshift);

    //MANA REGEN
    if (mylevel >= 24 && (me->getPowerType() == POWER_MANA || me->getPowerType() == POWER_RUNIC_POWER))
    {
        regen_mp5 = 0.5f * master->GetFloatValue(UNIT_FIELD_POWER_REGEN_FLAT_MODIFIER);
        //TOO COMPLICATED
        //regen_mp5 = (master->GetTotalAuraModifierByMiscValue(SPELL_AURA_MOD_POWER_REGEN, POWER_MANA) + sqrt(master->GetStat(STAT_INTELLECT)) * master->OCTRegenMPPerSpirit()) / 5.f;
        //Unit::AuraEffectList const& regenAura = master->GetAuraEffectsByType(SPELL_AURA_MOD_MANA_REGEN_FROM_STAT);
        //for (Unit::AuraEffectList::const_iterator i = regenAura.begin(); i != regenAura.end(); ++i)
        //    regen_mp5 += master->GetStat(Stats((*i)->GetMiscValue())) * (*i)->GetAmount() / 500.f;
        //regen_mp5 *= 0.8f;//custom modifier
        float regen_mp5_a = stat * 0.2f;
        //regen_mp5 += master->GetTotalStatValue(STAT_SPIRIT) * 0.1f;
        regen_mp5 = regen_mp5 > regen_mp5_a ? regen_mp5 : regen_mp5_a;

        //unknown values
        for (uint8 i = 0; i != BOT_INVENTORY_SIZE; ++i)
        {
            regen_mp5 += 2.f * (_stats[i][ITEM_MOD_MANA_REGENERATION]);
            regen_mp5 += 1.f * (_stats[i][ITEM_MOD_SPIRIT]);
        }

        if (myclass == CLASS_HUNTER && mylevel > 20)
            regen_mp5 += 45.f * ((mylevel - 20) / 15 + 1);
        if (regen_mp5 >= 45.f)
        {
            me->RemoveAurasDueToSpell(MANAREGEN100);
            me->RemoveAurasDueToSpell(MANAREGEN45);
            if      (regen_mp5 > 200.f)   RefreshAura(MANAREGEN100,int8(regen_mp5/100.f) + mylevel / 21);
            else/*if (regen_mp5 > 150.f)*/RefreshAura(MANAREGEN45, int8(regen_mp5/45.f)  + mylevel / 21);
        }
    }

    //SPELL POWER
    if (mylevel >= 25 && spp_mod > 0.f)
    {
        //sLog->outBasic("Updating spellpower for %s:", me->GetName().c_str());
        //sLog->outBasic("spp_mod: %f", spp_mod);
        for (uint8 i = SPELL_SCHOOL_HOLY; i != MAX_SPELL_SCHOOL; ++i)
        {
            int32 power = master->SpellBaseDamageBonusDone(SpellSchoolMask(1 << i));
            if (power > sppower || i == SPELL_SCHOOL_HOLY)
                sppower = power;
        }
        //sLog->outBasic("Master's spell power: %i", sppower);
        atpower = master->GetTotalAttackPowerValue(master->getClass() == CLASS_HUNTER ? RANGED_ATTACK : BASE_ATTACK);
        atpower *= 0.67f;
        //sLog->outBasic("Master's 2/3 of attack power: %f", atpower);
        m_spellpower = sppower > atpower ? sppower : atpower;
        //sLog->outBasic("Chosen stat value: %i", m_spellpower);

        m_spellpower /= 3; //reduce spellpower since we have items

        for (uint8 i = 0; i != BOT_INVENTORY_SIZE; ++i)
            m_spellpower += 2 * (_stats[i][ITEM_MOD_SPELL_POWER]);

        m_spellpower = int32(float(m_spellpower) * spp_mod);
        //sLog->outBasic("spellpower * mod: %i", m_spellpower);

        if (myclass == CLASS_MAGE)
            RefreshAura(FIREDAM_86, (m_spellpower / 4) / 86 + (mylevel >= 78) * 2); //(86,172,258,344,430,516,602,688...) // fire spp, do not touch this
        me->RemoveAurasDueToSpell(SPELL_BONUS_250);
        me->RemoveAurasDueToSpell(SPELL_BONUS_150);
        me->RemoveAurasDueToSpell(SPELL_BONUS_50);
        if      (mylevel < 60) RefreshAura(SPELL_BONUS_50,  m_spellpower / 50);
        else if (mylevel < 80) RefreshAura(SPELL_BONUS_150, m_spellpower / 150 + 1);
        else                   RefreshAura(SPELL_BONUS_250, m_spellpower / 250 + 2);
    }

    if (force)
    {
        me->SetFullHealth();
        me->SetPower(POWER_MANA, me->GetMaxPower(POWER_MANA));
    }

    //SetStats for pet
    if (Creature* pet = me->GetBotsPet())
        if (bot_pet_ai* petai = pet->GetBotPetAI())
            petai->setStats(mylevel, bot_pet_ai::GetPetType(pet), force);

    shouldUpdateStats = false;
}
void bot_pet_ai::setStats(uint8 mylevel, uint8 petType, bool force)
{
    if (petType == PET_TYPE_NONE || petType >= MAX_PET_TYPES) return;
    if (!shouldUpdateStats && !force) return;
    //TC_LOG_ERROR("entities.player", "setStats(): Updating pet bot %s, type: %u, level %u, owner: %s, master: %s", me->GetName().c_str(), petType, mylevel, m_creatureOwner->GetName().c_str(), master->GetName().c_str());

    //LEVEL
    if (me->getLevel() != mylevel)
    {
        me->SetLevel(mylevel);
        force = true; //restore powers on lvl update
    }
    if (force)
        InitSpells();

    //PHASE
    if (master->GetPhaseMask() != me->GetPhaseMask())
        me->SetPhaseMask(master->GetPhaseMask(), true);

    ////INIT STATS
    //uint8 botclass = m_creatureOwner->GetBotClass();
    //sObjectMgr->GetPlayerClassLevelInfo(botclass, m_creatureOwner->getLevel(), &classinfo);
    //const CreatureBaseStats* const classstats = sObjectMgr->GetCreatureBaseStats(mylevel, me->GetBotClass());//use creature class
    //if (force)
    //    for (uint8 i = STAT_STRENGTH; i < MAX_STATS; i++)
    //        me->SetCreateStat(Stats(i), master->GetCreateStat(Stats(i))*0.5f);

    //MAXSTAT
    float value;
    for (uint8 i = 0; i < MAX_STATS; ++i)
    {
        value = master->GetTotalStatValue(Stats(i));
        if (i == 0 || value > stat)
            stat = value;//Get Hightest stat (on first cycle just set base value)
    }
    stat = std::max(stat - 18.f, 0.f);//remove base

    //INIT CLASS MODIFIERS
    //STAT -- 'mod' -- used stat values to apply
    //WARLOCK
    //Stamina x0.3  -- health
    //Armor   x0.35 -- armor
    //Int     x0.3  -- crit/mana
    //Spd     x0.15 -- spd (if has mana)
    //AP      x0.57 -- attack power (if melee pet)
    //Resist  x0.4  -- resistances
    //MAGE
    //
    //SHAMAN
    //
    //HUNTER
    //Other   x1.0  -- use as default
    switch (petType)
    {
        case PET_TYPE_VOIDWALKER:       ap_mod = 0.57f; spp_mod = 0.15f; crit_mod = 1.0f; break;
        //case PET_TYPE_FELHUNTER:        ap_mod = 0.57f; spp_mod = 0.15f; crit_mod = 1.0f; break;//NYI
        //case PET_TYPE_FELGUARD:         ap_mod = 0.57f; spp_mod = 0.15f; crit_mod = 1.0f; break;//NYI
        //case PET_TYPE_SUCCUBUS:         ap_mod = 0.57f; spp_mod = 0.15f; crit_mod = 1.0f; break;//NYI
        //case PET_TYPE_IMP:              ap_mod = 0.f;   spp_mod = 0.15f; crit_mod = 1.0f; break;//NYI

        //case PET_TYPE_WATER_ELEMENTAL:  ap_mod = 0.0f;  spp_mod = 0.0f; crit_mod = 0.0f; break;//NYI

        //case PET_TYPE_FIRE_ELEMENTAL:   ap_mod = 0.0f;  spp_mod = 0.0f; crit_mod = 0.0f; break;//NYI
        //case PET_TYPE_EARTH_ELEMENTAL:  ap_mod = 0.0f;  spp_mod = 0.0f; crit_mod = 0.0f; break;//NYI

        //case PET_TYPE_VULTURE:          ap_mod = 0.9f;  spp_mod = 1.0f; crit_mod = 1.2f; break;//NYI
        default:                        ap_mod = 0.0f;  spp_mod = 0.0f; crit_mod = 0.0f; break;
    }
    //case CLASS_WARRIOR:      ap_mod = 1.3f;  spp_mod = 0.0f; armor_mod = 1.4f;  crit_mod = 1.0f; haste_mod = 0.75f; dodge_mod = 0.75f; parry_mod = 1.75f; break;
    //case CLASS_DEATH_KNIGHT: ap_mod = 1.2f;  spp_mod = 1.0f; armor_mod = 1.15f; crit_mod = 0.9f; haste_mod = 0.65f; dodge_mod = 0.8f;  parry_mod = 2.0f;  break;//NYI
    //case CLASS_PALADIN:      ap_mod = 1.0f;  spp_mod = 0.8f; armor_mod = 1.2f;  crit_mod = 0.8f; haste_mod = 0.85f; dodge_mod = 0.7f;  parry_mod = 1.5f;  break;
    //case CLASS_ROGUE:        ap_mod = 1.5f;  spp_mod = 0.0f; armor_mod = 0.7f;  crit_mod = 1.5f; haste_mod = 1.35f; dodge_mod = 1.5f;  parry_mod = 0.8f;  break;//NYI
    //case CLASS_HUNTER:       ap_mod = 1.15f; spp_mod = 0.0f; armor_mod = 0.85f; crit_mod = 1.2f; haste_mod = 1.25f; dodge_mod = 1.2f;  parry_mod = 1.2f;  break;//NYI
    //case CLASS_SHAMAN:       ap_mod = 0.9f;  spp_mod = 1.0f; armor_mod = 0.9f;  crit_mod = 1.2f; haste_mod = 1.65f; dodge_mod = 0.8f;  parry_mod = 0.5f;  break;//NYI
    //case CLASS_DRUID:        ap_mod = 0.0f;  spp_mod = 1.3f; armor_mod = 0.7f;  crit_mod = 0.7f; haste_mod = 1.95f; dodge_mod = 0.5f;  parry_mod = 0.0f;  break;
    //case CLASS_MAGE:         ap_mod = 0.0f;  spp_mod = 0.8f; armor_mod = 0.5f;  crit_mod = 0.7f; haste_mod = 1.75f; dodge_mod = 0.5f;  parry_mod = 0.0f;  break;
    //case CLASS_PRIEST:       ap_mod = 0.0f;  spp_mod = 1.2f; armor_mod = 0.5f;  crit_mod = 0.7f; haste_mod = 1.75f; dodge_mod = 0.5f;  parry_mod = 0.0f;  break;
    //case CLASS_WARLOCK:      ap_mod = 0.0f;  spp_mod = 1.0f; armor_mod = 0.5f;  crit_mod = 0.7f; haste_mod = 1.75f; dodge_mod = 0.5f;  parry_mod = 0.0f;  break;
    //case BEAR:               ap_mod = 2.0f;  spp_mod = 1.3f; armor_mod = 2.25f; crit_mod = 1.0f; haste_mod = 0.75f; dodge_mod = 2.5f;  parry_mod = 0.0f;  break;
    //case CAT:                ap_mod = 1.5f;  spp_mod = 1.3f; armor_mod = 1.1f;  crit_mod = 1.5f; haste_mod = 2.25f; dodge_mod = 1.35f; parry_mod = 0.0f;  break;

    if (spp_mod != 0.f && mylevel > 24)
        spp_mod *= (float(mylevel - 24)) / 61.f;// gain spell power slowly

    //DAMAGE
    if (ap_mod > 0.f)//do not bother casters
    {
        switch (m_creatureOwner->GetBotClass())
        {
            case CLASS_WARLOCK:
                value = float(m_creatureOwner->GetBotAI()->GetSpellPower());
                break;
            case CLASS_DEATH_KNIGHT:
                value = m_creatureOwner->GetTotalAttackPowerValue(BASE_ATTACK);
                break;
            case CLASS_HUNTER:
                value = m_creatureOwner->GetTotalAttackPowerValue(RANGED_ATTACK);
                break;
            default: //some weird class or NYI
                value = 0.f;
                break;
        }
        //Calculate ap
        //set base strength
        me->SetModifierValue(UNIT_MOD_STAT_STRENGTH, BASE_VALUE, me->GetCreateStat(STAT_STRENGTH) - 9.f);
        //calc attack power (strength and minion's spd)
        atpower = me->GetTotalAuraModValue(UNIT_MOD_STAT_STRENGTH) * 2.f + value * ap_mod;
        //set value
        me->SetModifierValue(UNIT_MOD_ATTACK_POWER, BASE_VALUE, atpower);
        me->UpdateAttackPowerAndDamage();
    }

    //ARMOR
    value = float(basearmor);
    //get minion's armor and give 35% to pet (just as for real pets)
    value += m_creatureOwner->GetModifierValue(UNIT_MOD_ARMOR, BASE_VALUE) * 0.35f;
    me->SetModifierValue(UNIT_MOD_ARMOR, BASE_VALUE, value);
    me->UpdateArmor();//buffs will be took in consideration here

    //RESISTANCES
    //based on minion's resistances gain x0.4
    for (uint8 i = SPELL_SCHOOL_HOLY; i != MAX_SPELL_SCHOOL; ++i)
    {
        value = float(master->GetResistance(SpellSchools(i)));
        me->SetModifierValue(UnitMods(UNIT_MOD_RESISTANCE_START + i), BASE_VALUE, 0.4f * (value * 2.5f + float(mylevel * 2)));
        me->UpdateResistances(i);
    }

    //DAMAGE TAKEN
    //just get minion's reduction and apply to pet
    value = m_creatureOwner->GetTotalAuraMultiplierByMiscMask(SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, SPELL_SCHOOL_MASK_NORMAL);
    if (value > 1.f)
        value -= 1.f;
    else
        value = 1.f - value; //get reduction even if owner's is 1.0+
    value = std::min(0.5f, value);
    value *= 100.f; //here we get percent like 0.5 * 100 = 50%
    RefreshAura(DMG_TAKEN, int8(value / 10.f)); //so max aura count = 10

    //HEALTH
    _OnHealthUpdate(petType, mylevel);

//////RATINGS//////
    //ok now, pet receives 100% of its master's ratings

    //HASTE
    haste = m_creatureOwner->GetBotAI()->GetHaste();
    RefreshAura(HASTE,  haste);//spell haste
    RefreshAura(HASTE2, haste);//melee haste

    //HIT
    hit = m_creatureOwner->GetBotAI()->GetHitRating();
    //RefreshAura(PRECISION,  int8(hit) + mylevel/42);//melee
    RefreshAura(PRECISION);
    RefreshAura(PRECISION2, int8(hit) + mylevel / 42);//spell

    //CRIT
    //chose melee or ranged cuz crit rating increases melee/spell, and hunter benefits from agility
    value = master->GetUnitCriticalChance((master->getClass() == CLASS_HUNTER ? RANGED_ATTACK : BASE_ATTACK), me);
    if (crit_mod != 1.0f)
        value *= crit_mod;
    RefreshAura(CRITS, int8(value / 3.f) + mylevel / 42);

    //PARRY
    value = master->GetFloatValue(PLAYER_PARRY_PERCENTAGE);
    if (master->GetBotTankGuid() == me->GetGUID())
        value += 10.f;
    if (value > 65.f)
        value = 65.f;
    float parryAndDodge = value; //set temp value, this is needed to keep total avoidance within 75%
    RefreshAura(PARRY, int8(value / 6.f));

    //DODGE
    value = master->GetUnitDodgeChance();
    value = value > 5.f ? value - 5.f : 0.f; //remove base chance if possible
    if (master->GetBotTankGuid() == me->GetGUID())
        value += 10.f;
    if (value > 65.f)
        value = 65.f;
    if (parryAndDodge + value > 65.f)
        value = 65.f - parryAndDodge; //do not allow avoidance to be more than 75% (base 5+5)
    RefreshAura(DODGE, int8(value / 5.f));

    //MANA
    _OnManaUpdate(petType, mylevel, false);

    //MANA REGEN
    if (mylevel >= 24 && me->getPowerType() == POWER_MANA)
    {
        //let regen rate be same as stats rate x0.3
        regen_mp5 = m_creatureOwner->GetBotAI()->GetManaRegen() * 0.3f;
        if (regen_mp5 >= 45.f)
        {
            me->RemoveAurasDueToSpell(MANAREGEN100);
            me->RemoveAurasDueToSpell(MANAREGEN45);
            if      (regen_mp5 > 200.f)   RefreshAura(MANAREGEN100,int8(regen_mp5 / 100.f) + mylevel / 20);
            else/*if (regen_mp5 > 150.f)*/RefreshAura(MANAREGEN45, int8(regen_mp5 / 45.f)  + mylevel / 20);
        }
    }

    //SPELL POWER
    if (mylevel >= 24 && spp_mod != 0.f)
    {
        switch (m_creatureOwner->GetBotClass())
        {
            case CLASS_WARLOCK:
                value = float(m_creatureOwner->GetBotAI()->GetSpellPower());
                break;
            case CLASS_DEATH_KNIGHT:
                value = m_creatureOwner->GetTotalAttackPowerValue(BASE_ATTACK);
                break;
            case CLASS_HUNTER:
                value = m_creatureOwner->GetTotalAttackPowerValue(RANGED_ATTACK);
                break;
            default: //some weird class or NYI
                value = 0.f;
                break;
        }
        m_spellpower = int32(value * spp_mod);
        me->RemoveAurasDueToSpell(SPELL_BONUS_250);
        me->RemoveAurasDueToSpell(SPELL_BONUS_150);
        me->RemoveAurasDueToSpell(SPELL_BONUS_50);
        if      (mylevel < 60) RefreshAura(SPELL_BONUS_50,  m_spellpower / 50);
        else if (mylevel < 80) RefreshAura(SPELL_BONUS_150, m_spellpower / 150 + 1);
        else                   RefreshAura(SPELL_BONUS_250, m_spellpower / 250 + 2);
    }

    if (force)
    {
        me->SetFullHealth();
        me->SetPower(POWER_MANA, me->GetMaxPower(POWER_MANA));
    }

    shouldUpdateStats = false;
}
//Emotion-based action
void bot_ai::ReceiveEmote(Player* player, uint32 emote)
{
    switch (emote)
    {
        case TEXT_EMOTE_BONK:
            listAuras(player, me);
            break;
        case TEXT_EMOTE_SALUTE:
            listAuras(player, player);
            break;
        case TEXT_EMOTE_STAND:
            if (!IsMinionAI())
                return;
            if (master != player)
            {
                me->HandleEmoteCommand(EMOTE_ONESHOT_RUDE);
                return;
            }
            SetBotCommandState(COMMAND_STAY);
            me->MonsterWhisper("Standing Still.", player);
            break;
        case TEXT_EMOTE_WAVE:
            if (!IsMinionAI())
                return;
            if (master != player)
            {
                me->HandleEmoteCommand(EMOTE_ONESHOT_RUDE);
                return;
            }
            SetBotCommandState(COMMAND_FOLLOW, true);
            me->MonsterWhisper("Following!", player);
            break;
        default:
            break;
    }
}

//ISINBOTPARTY
//Returns group members (and their npcbots too)
//For now all your puppets are in your group automatically
bool bot_ai::IsInBotParty(Unit* unit) const
{
    if (!unit) return false;
    if (unit == me || unit == master) return true;

    //cheap check
    if (Group* gr = master->GetGroup())
    {
        //group member case
        if (gr->IsMember(unit->GetGUID()))
            return true;
        //pointed target case
        for (uint8 i = 0; i != TARGETICONCOUNT; ++i)
            if (healTargetIconFlags & GroupIconsFlags[i])
                if (uint64 guid = gr->GetTargetIcons()[i])//check this one
                    if (guid == unit->GetGUID())
                        if (unit->GetReactionTo(master) >= REP_NEUTRAL &&
                            master->GetVictim() != unit &&
                            unit->GetVictim() != master)
                            return true;
    }

    //Player-controlled creature case
    if (Creature* cre = unit->ToCreature())
    {
        //npcbot/npcbot's pet case
        if (Player* owner = cre->GetBotOwner())
        {
            if (owner == master)
                return true;
        }
        //pets, minions, guardians etc.
        else
        {
            uint64 ownerGuid = unit->GetOwnerGUID();
            //controlled by group member
            if (Group* gr = master->GetGroup())
                if (gr->IsMember(ownerGuid))
                    return true;
        }
    }

    return false;
}

//REFRESHAURA
//Applies/reapplies aura stacks
bool bot_ai::RefreshAura(uint32 spell, int8 count, Unit* target) const
{
    if (!spell)
        return false;
    if (!target)
        target = me;
    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spell);
    if (!spellInfo)
        return false;
    //if (!spellInfo->IsPassive())
    //{
    //    TC_LOG_ERROR("entities.player", "bot_ai::RefreshAura(): %s received spell %u (%s) which is not a passive spell!", target->GetName().c_str(), spell, spellInfo->SpellName[0]);
    //    //return false;
    //}
    if (target->HasAura(spell))
        target->RemoveAurasDueToSpell(spell);

    //if (count > 15)
    //    TC_LOG_ERROR("entities.player", "bot_ai::RefreshAura(): %s's aura count for spell %u (%s) is greater than 15... (%i)", target->GetName().c_str(), spell, spellInfo->SpellName, count);

    for (uint8 i = 0; i < count; ++i)
        target->AddAura(spellInfo, MAX_EFFECT_MASK, target);
    return true;
}
//CHECKAURAS
//Updates bot's condition once a while
void bot_minion_ai::CheckAuras(bool force)
{
    opponent = me->GetVictim(); //safe

    if (!force)
        UpdateRations(); //safe

    if (checkAurasTimer == 0)
    {
        checkAurasTimer = 10 + master->GetNpcBotsCount()/2;

        if (m_botCommandState != COMMAND_FOLLOW && m_botCommandState != COMMAND_STAY)
        {
            if (opponent && !CCed(me, true))
            {
                switch (me->GetBotClass())
                {
                    case CLASS_SHAMAN:
                        if (isTwoHander())
                        {
                            if (me->GetDistance(opponent) > 1.5f)
                                GetInPosition(true, false);
                        }
                        else
                        {
                            CalculateAttackPos(opponent, attackpos);
                            if (me->GetDistance(attackpos) > 8)
                                GetInPosition(true, true, opponent, &attackpos);
                        }
                        break;
                    case CLASS_MAGE: case CLASS_DRUID: case CLASS_WARLOCK: case CLASS_PRIEST: case CLASS_HUNTER:
                        CalculateAttackPos(opponent, attackpos);
                        if (me->GetDistance(attackpos) > 8)
                            GetInPosition(true, true, opponent, &attackpos);
                        break;
                    default:
                        if (me->GetDistance(opponent) > 1.5f)
                            GetInPosition(true, false);
                        break;
                }
            }
        }
        if (shouldUpdateStats)
            setStats(me->GetBotClass(), me->getRace(), master->getLevel());
        else
        {
            UpdateHealth();
            UpdateMana();
        }
        if (rezz_cd > 0)
            --rezz_cd;
        if (clear_cd > 0)
            --clear_cd;
        else
        {
            FindTank();
            clear_cd = 15;
        }
        return;
    }
    else if (force)
    {
        if (!opponent)
        {
            if (master->IsDead())
            {
                //If ghost move to corpse, else move to dead player
                if (master->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST))
                {
                    Corpse* corpse = master->GetCorpse();
                    if (corpse && me->GetMap() == corpse->FindMap() && !me->IsInCombat() && !me->HasUnitState(UNIT_STATE_MOVING) && !IsCasting() && !CCed(me) && me->GetDistance(corpse) > 5)
                        me->GetMotionMaster()->MovePoint(corpse->GetMapId(), *corpse);
                }
                else
                {
                    if (m_botCommandState != COMMAND_FOLLOW || me->GetDistance(master) > 30 - 20 * (!me->IsWithinLOSInMap(master)))
                        Follow(true);
                }
            }
            else if (m_botCommandState != COMMAND_STAY && !IsCasting())
            {
                CalculatePos(pos);
                uint8 followdist = master->GetBotFollowDist();
                if (me->GetExactDist(&pos) > (followdist > 8 ? 4 + followdist/2*(!master->isMoving()) : 8))
                    Follow(true, &pos); //check if doing nothing
            }
        }
        if (!IsCasting())
        {
            if (me->IsInCombat())
            {
                if (me->GetBotClass() == CLASS_HUNTER)
                {
                    if (me->GetSheath() != SHEATH_STATE_RANGED)
                        me->SetSheath(SHEATH_STATE_RANGED);
                }
                else if (me->GetSheath() != SHEATH_STATE_MELEE)
                    me->SetSheath(SHEATH_STATE_MELEE);
            }
            else if (me->IsStandState() && me->GetSheath() != SHEATH_STATE_UNARMED && Rand() < 50)
                me->SetSheath(SHEATH_STATE_UNARMED);
        }
        UpdateMountedState();
        UpdateStandState();
    }
}
void bot_pet_ai::CheckAuras(bool /*force*/)
{
    if (checkAurasTimer > 0) return;
    checkAurasTimer = 10 + master->GetNpcBotsCount()/2;
    if (m_botCommandState != COMMAND_FOLLOW && m_botCommandState != COMMAND_STAY)
    {
        opponent = me->GetVictim();
        if (opponent)
        {
            switch (GetPetType(me))
            {
                case PET_TYPE_IMP:
                    CalculateAttackPos(opponent, attackpos);
                    if (me->GetDistance(attackpos) > 8)
                        GetInPosition(true, true, opponent, &attackpos);
                    break;
                default:
                    if (me->GetDistance(opponent) > 1.5f)
                        GetInPosition(true, false);
                    break;
            }
        }
    }
    if (clear_cd > 0)
        --clear_cd;
    else
    {
        FindTank();
        clear_cd = 15;
    }
    return;
}

bool bot_ai::CanBotAttack(Unit* target, int8 byspell) const
{
    if (!target) return false;
    if (!PvP && (target->ToPlayer() || (target->ToCreature() && target->ToCreature()->GetBotAI())))
        return false;
    uint8 followdist = master->GetBotFollowDist();
    float foldist = _getAttackDistance(float(followdist));
    return
       (target->IsAlive() &&
       target->IsVisible() &&
       (master->IsDead() || target->GetTypeId() == TYPEID_PLAYER || target->IsPet() ||
       (target->GetDistance(master) < foldist && me->GetDistance(master) < followdist)) &&//if master is killed pursue to the end
        target->isTargetableForAttack() &&
        !IsInBotParty(target) &&
        (target->IsHostileTo(master) ||
        (target->GetReactionTo(master) < REP_FRIENDLY && master->GetVictim() == target && (master->IsInCombat() || target->IsInCombat())) ||//master has pointed this target
        target->IsHostileTo(me)) &&//if master is controlled
        //target->IsWithinLOSInMap(me) &&
        (byspell == -1 || !target->IsImmunedToDamage(byspell ? SPELL_SCHOOL_MASK_MAGIC : SPELL_SCHOOL_MASK_NORMAL)));
}
//GETTARGET
//Returns attack target or 'no target'
//uses follow distance if range isn't set
Unit* bot_ai::getTarget(bool byspell, bool ranged, bool &reset) const
{
    //check if no need to change target
    Unit* u = master->GetVictim();
    Unit* mytar = me->GetVictim();
    if (!mytar && IsMinionAI())
        if (Creature* pet = me->GetBotsPet())
            mytar = pet->GetVictim();

    //TC_LOG_ERROR("entities.player", "bot_ai::getTarget(): bot: %s, PvP = %u", me->GetName().c_str(), PvP);

    if (u && u == mytar)
    {
        //TC_LOG_ERROR("entities.player", "bot %s continues attack common target %s", me->GetName().c_str(), u->GetName().c_str());
        return u;//forced
    }
    //Follow if...
    uint8 followdist = master->GetBotFollowDist();
    float foldist = _getAttackDistance(float(followdist));
    if (!u && master->IsAlive() && (me->GetDistance(master) > foldist || (mytar && master->GetDistance(mytar) > foldist && me->GetDistance(master) > foldist)))
    {
        //TC_LOG_ERROR("entities.player", "bot %s cannot attack target %s, too far away", me->GetName().c_str(), mytar ? mytar->GetName().c_str() : "");
        return NULL;
    }

    if (u && (master->IsInCombat() || u->IsInCombat()) && !InDuel(u) && !IsInBotParty(u) && !(!PvP && (u->ToPlayer() || (u->ToCreature() && u->ToCreature()->GetBotAI()))))
    {
        //TC_LOG_ERROR("entities.player", "bot %s starts attack master's target %s", me->GetName().c_str(), u->GetName().c_str());
        return u;
    }

    if (CanBotAttack(mytar, byspell) && !InDuel(mytar))
    {
        //TC_LOG_ERROR("entities.player", "bot %s continues attack its target %s", me->GetName().c_str(), mytar->GetName().c_str());
        if (me->GetDistance(mytar) > (ranged ? 20.f : 5.f) && m_botCommandState != COMMAND_STAY && m_botCommandState != COMMAND_FOLLOW)
            reset = true;
        return mytar;
    }

    if (followdist == 0 && master->IsAlive())
        return NULL; //do not bother

    //check group
    Group* gr = master->GetGroup();
    if (!gr)
    {
        for (uint8 i = 0; i != master->GetMaxNpcBots(); ++i)
        {
            Creature* bot = master->GetBotMap(i)->_Cre();
            if (!bot || !bot->InSamePhase(me) || bot == me) continue;
            u = bot->GetVictim();
            if (u && CanBotAttack(u, byspell) &&
                (bot->IsInCombat() || u->IsInCombat()) &&
                (master->IsDead() || master->GetDistance(u) < foldist))
            {
                //TC_LOG_ERROR("entities.player", "bot %s hooked %s's victim %s", me->GetName().c_str(), bot->GetName().c_str(), u->GetName().c_str());
                return u;
            }
            Creature* pet = bot->GetIAmABot() ? bot->GetBotsPet() : NULL;
            if (!pet || !pet->InSamePhase(me)) continue;
            u = pet->GetVictim();
            if (u && CanBotAttack(u, byspell) &&
                (pet->IsInCombat() || u->IsInCombat()) &&
                (master->IsDead() || master->GetDistance(u) < foldist))
            {
                //TC_LOG_ERROR("entities.player", "bot %s hooked %s's victim %s", me->GetName().c_str(), pet->GetName().c_str(), u->GetName().c_str());
                return u;
            }
        }
    }
    else
    {
        for (GroupReference* ref = gr->GetFirstMember(); ref != NULL; ref = ref->next())
        {
            Player* pl = ref->GetSource();
            if (!pl || !pl->IsInWorld() || pl->IsBeingTeleported()) continue;
            if (me->GetMap() != pl->FindMap() || !pl->InSamePhase(me)) continue;
            u = pl->GetVictim();
            if (u && pl != master && CanBotAttack(u, byspell) &&
                (pl->IsInCombat() || u->IsInCombat()) &&
                (master->IsDead() || master->GetDistance(u) < foldist))
            {
                //TC_LOG_ERROR("entities.player", "bot %s hooked %s's victim %s", me->GetName().c_str(), pl->GetName().c_str(), u->GetName().c_str());
                return u;
            }
            if (!pl->HaveBot()) continue;
            for (uint8 i = 0; i != pl->GetMaxNpcBots(); ++i)
            {
                Creature* bot = pl->GetBotMap(i)->_Cre();
                if (!bot || !bot->InSamePhase(me) || bot == me) continue;
                if (!bot->IsInWorld()) continue;
                if (me->GetMap() != bot->FindMap()) continue;
                u = bot->GetVictim();
                if (u && CanBotAttack(u, byspell) &&
                    (bot->IsInCombat() || u->IsInCombat()) &&
                    (master->IsDead() || master->GetDistance(u) < foldist))
                {
                    //TC_LOG_ERROR("entities.player", "bot %s hooked %s's victim %s", me->GetName().c_str(), bot->GetName().c_str(), u->GetName().c_str());
                    return u;
                }
                Creature* pet = bot->GetIAmABot() ? bot->GetBotsPet() : NULL;
                if (!pet || !pet->InSamePhase(me)) continue;
                if (!pet->IsInWorld()) continue;
                if (me->GetMap() != pet->FindMap()) continue;
                u = pet->GetVictim();
                if (u && CanBotAttack(u, byspell) &&
                    (pet->IsInCombat() || u->IsInCombat()) &&
                    (master->IsDead() || master->GetDistance(u) < foldist))
                {
                    //TC_LOG_ERROR("entities.player", "bot %s hooked %s's victim %s", me->GetName().c_str(), pet->GetName().c_str(), u->GetName().c_str());
                    return u;
                }
            }
        }
    }

    //check targets around
    Unit* t = NULL;
    float maxdist = InitAttackRange(float(followdist), ranged);
    //first cycle we search non-cced target, then, if not found, check all
    for (uint8 i = 0; i != 2; ++i)
    {
        if (!t)
        {
            bool attackCC = i;

            CellCoord p(Trinity::ComputeCellCoord(me->GetPositionX(), me->GetPositionY()));
            Cell cell(p);
            cell.SetNoCreate();

            NearestHostileUnitCheck check(me, maxdist, byspell, this, attackCC);
            Trinity::UnitLastSearcher <NearestHostileUnitCheck> searcher(master, t, check);
            me->VisitNearbyObject(maxdist, searcher);
        }
    }

    if (t && opponent && t != opponent)
    {
        //TC_LOG_ERROR("entities.player", "bot %s has Found new target %s", me->GetName().c_str(), t->GetName().c_str());
        reset = true;
    }
    return t;
}
//'CanAttack' function
bool bot_ai::CheckAttackTarget(uint8 botOrPetType)
{
    bool byspell = false, ranged = false, reset = false;
    if (IsMinionAI())
    {
        switch (botOrPetType)
        {
            case CLASS_DRUID:
                byspell = me->GetShapeshiftForm() == FORM_NONE ||
                    me->GetShapeshiftForm() == FORM_TREE ||
                    me->GetShapeshiftForm() == FORM_MOONKIN;
                ranged = byspell;
                break;
            case CLASS_PRIEST:
            case CLASS_MAGE:
            case CLASS_WARLOCK:
                byspell = true;
                ranged = true;
                break;
            case CLASS_SHAMAN:
                byspell = true;
                ranged = !isTwoHander();
                break;
            case CLASS_HUNTER:
                ranged = true;
                break;
            default:
                break;
        }
    }
    else
    {
        switch (botOrPetType)
        {
            case PET_TYPE_IMP:
                byspell = true;
                ranged = true;
                break;
            default:
                break;
        }
    }

    opponent = getTarget(byspell, ranged, reset);
    if (!opponent)
    {
        me->AttackStop();
        return false;
    }

    if (reset)
        m_botCommandState = COMMAND_ABANDON;//reset AttackStart()

    if (opponent != me->GetVictim())
        me->Attack(opponent, !ranged);
    return true;
}
//POSITION
void bot_ai::CalculateAttackPos(Unit* target, Position& pos) const
{
    uint8 followdist = master->GetBotFollowDist();
    float x(0),y(0),z(0),
        dist = float(6 + urand(followdist/4, followdist/3)),
        angle = target->GetAngle(me);
    dist = std::min(dist, 20.f);
    if (me->GetIAmABotsPet())
        dist *= 0.5f;
    float clockwise = RAND(1.f,-1.f);
    for (uint8 i = 0; i != 5; ++i)
    {
        target->GetNearPoint(me, x, y, z, me->GetObjectSize()/2.f, dist, angle);
        bool toofaraway = master->GetDistance(x,y,z) > (followdist > 30 ? 30.f : followdist < 20 ? 20.f : float(followdist));
        bool outoflos = !target->IsWithinLOS(x,y,z);
        if (toofaraway || outoflos)
        {
            if (toofaraway)
                angle = target->GetAngle(master) + frand(0.f, M_PI*0.5f) * clockwise;
            if (outoflos)
                dist *= 0.5f;
        }
        else
        {
            dist *= 0.75f;
            break;
        }
    }
    pos.m_positionX = x;
    pos.m_positionY = y;
    pos.m_positionZ = z;
}
// Forces bot to chase opponent (if ranged then distance depends on follow distance)
void bot_ai::GetInPosition(bool force, bool ranged, Unit* newtarget, Position* mypos)
{
    if (me->HasUnitState(UNIT_STATE_ROOT)) return;
    if (!newtarget)
        newtarget = me->GetVictim();
    if (!newtarget)
        return;
    if ((!newtarget->IsInCombat() || m_botCommandState == COMMAND_STAY) && !force)
        return;
    if (IsCasting())
        return;
    uint8 followdist = master->GetBotFollowDist();
    if (ranged)
    {
        if (newtarget->GetTypeId() == TYPEID_PLAYER &&
            me->GetDistance(newtarget) < 6 + urand(followdist/4, followdist/3)) return;//do not allow constant runaway from player
        if (!mypos)
            CalculateAttackPos(newtarget, attackpos);
        else
        {
            attackpos.m_positionX = mypos->m_positionX;
            attackpos.m_positionY = mypos->m_positionY;
            attackpos.m_positionZ = mypos->m_positionZ;
        }
        if (me->GetDistance(attackpos) > (me->GetBotClass() == CLASS_HUNTER ? 4 : 8))
            me->GetMotionMaster()->MovePoint(newtarget->GetMapId(), attackpos);
    }
    else if (!me->HasUnitState(UNIT_STATE_CHASE) || !me->HasUnitState(UNIT_STATE_CHASE_MOVE))
        me->GetMotionMaster()->MoveChase(newtarget);

    if (newtarget != me->GetVictim())
        me->Attack(newtarget, !ranged);
}

bool bot_ai::MoveBehind(Unit &target) const
{
    if (me->HasUnitState(UNIT_STATE_ROOT)) return false;
    if (target.IsWithinCombatRange(me, ATTACK_DISTANCE) &&
        target.HasInArc(M_PI, me)                       &&
        tank != me &&
        (me->GetBotClass() == CLASS_ROGUE ? target.GetVictim() != me || CCed(&target) : target.GetVictim() != me && !CCed(&target)))
    {
        float x(0),y(0),z(0);
        target.GetNearPoint(me, x, y, z, me->GetObjectSize()/3, 0.1f, me->GetAngle(&target));
        me->GetMotionMaster()->MovePoint(target.GetMapId(), x, y, z);
        return true;
    }
    return false;
}
//MOUNT SUPPORT
void bot_minion_ai::UpdateMountedState()
{
    if (GetBotCommandState() != COMMAND_FOLLOW)
        return;

    bool aura = me->HasAuraType(SPELL_AURA_MOUNTED);
    bool mounted = me->IsMounted();
    if ((!master->IsMounted() || aura != mounted || (me->IsInCombat() && opponent)) && (aura || mounted))
    {
        const_cast<CreatureTemplate*>(me->GetCreatureTemplate())->InhabitType &= ~INHABIT_AIR;
        me->RemoveAurasByType(SPELL_AURA_MOUNTED);
        //me->RemoveUnitMovementFlag(MOVEMENTFLAG_HOVER);
        me->SetCanFly(false);
        me->SetDisableGravity(false);
        me->RemoveUnitMovementFlag(MOVEMENTFLAG_FALLING);
        me->Dismount();
        return;
    }
    //END DEBUG
    if (me->IsInCombat() || IsCasting() || me->HasUnitMovementFlag(MOVEMENTFLAG_SWIMMING)) //IsInWater() is too much calculations
        return;
    //fly
    //if ((master->IsMounted() && master->HasAuraType(SPELL_AURA_FLY))/* || master->HasUnitMovementFlag(MOVEMENTFLAG_CAN_FLY) || master->HasUnitMovementFlag(MOVEMENTFLAG_FLYING)*/)
    //{
    //    if (!me->IsMounted() || !me->HasAuraType(SPELL_AURA_FLY))
    //    {
    //        //if (me->GetBotClass() == CLASS_DRUID && InitSpell(FLY_FORM))//TODO
    //        //{
    //        //}
    //        //else
    //        {
    //            uint32 mount = 0;
    //            Unit::AuraEffectList const &mounts = master->GetAuraEffectsByType(SPELL_AURA_MOUNTED);
    //            if (!mounts.empty())
    //                mount = mounts.front()->GetId();
    //            if (mount)
    //            {
    //                if (me->HasAuraType(SPELL_AURA_MOUNTED))
    //                        me->RemoveAurasByType(SPELL_AURA_MOUNTED);
    //                if (doCast(me, mount))
    //                {
    //                    if (Feasting())
    //                    {
    //                        me->RemoveAurasDueToSpell(DRINK);
    //                        me->RemoveAurasDueToSpell(EAT);
    //                    }
    //                }
    //            }
    //        }
    //    }
    //}
    ////ground
    /*else */
    if (master->IsMounted() && !me->IsMounted() && !master->IsInCombat() && !me->IsInCombat() && !me->GetVictim())
    {
        uint32 mount = 0;
        Unit::AuraEffectList const &mounts = master->GetAuraEffectsByType(SPELL_AURA_MOUNTED);
        if (!mounts.empty())
            mount = mounts.front()->GetId();
        if (mount)
        {
            if (me->HasAuraType(SPELL_AURA_MOUNTED))
                me->RemoveAurasByType(SPELL_AURA_MOUNTED);
            if (Feasting())
            {
                me->RemoveAurasDueToSpell(DRINK);
                me->RemoveAurasDueToSpell(EAT);
            }
            if (doCast(me, mount))
            {
                return;
            }
        }
    }
}
//STANDSTATE
void bot_minion_ai::UpdateStandState() const
{
    if (master->getStandState() == UNIT_STAND_STATE_STAND &&
        me->getStandState() == UNIT_STAND_STATE_SIT &&
        !(me->GetInterruptMask() & AURA_INTERRUPT_FLAG_NOT_SEATED))
        me->SetStandState(UNIT_STAND_STATE_STAND);
    if ((master->getStandState() == UNIT_STAND_STATE_SIT || Feasting()) && !me->IsInCombat() && !me->isMoving() &&
        me->getStandState() == UNIT_STAND_STATE_STAND)
        me->SetStandState(UNIT_STAND_STATE_SIT);

}
//RATIONS
void bot_minion_ai::UpdateRations()
{
    if (mana_cd > RATIONS_CD)
        mana_cd = uint32(-1);
    if (health_cd > RATIONS_CD)
        health_cd = uint32(-1);

    if (me->IsInCombat() || CCed(me))
    {
        if (health_cd <= RATIONS_CD && me->HasAura(EAT))
        {
            health_cd = uint32(-1);
            me->RemoveAurasDueToSpell(EAT);
        }
        if (mana_cd <= RATIONS_CD && me->HasAura(DRINK))
        {
            mana_cd = uint32(-1);
            me->RemoveAurasDueToSpell(DRINK);
        }

        return;
    }

    //drink
    if (me->getPowerType() == POWER_MANA && !me->IsMounted() && !me->isMoving() &&
        !me->IsInCombat() && !IsCasting() && urand(0, 100) < 20 && GetManaPCT(me) < 80 &&
        !me->HasAura(DRINK))
    {
        mana_cd = RATIONS_CD;
        me->CastSpell(me, DRINK);
        me->SetStandState(UNIT_STAND_STATE_SIT);
    }
    if (mana_cd == 0 && me->getPowerType() == POWER_MANA && me->GetPower(POWER_MANA) < me->GetMaxPower(POWER_MANA))
    {
        mana_cd = RATIONS_CD;
        me->ModifyPower(POWER_MANA, me->GetMaxPower(POWER_MANA) / (RATIONS_CD / 40)/*1000/40=25*/); //4% per second
    }

    //eat
    if (!me->IsMounted() && !me->isMoving() && !me->IsInCombat() && !IsCasting() &&
        urand(0, 100) < 20 && GetHealthPCT(me) < 80 &&
        !me->HasAura(EAT))
    {
        health_cd = RATIONS_CD;
        me->CastSpell(me, EAT);
        me->SetStandState(UNIT_STAND_STATE_SIT);
    }
    if (health_cd == 0 && me->GetHealth() < me->GetMaxHealth() && me->HasAura(EAT))
    {
        health_cd = RATIONS_CD;
        me->SetHealth(me->GetHealth() + me->GetMaxHealth() / (RATIONS_CD / 50)/*1000/50=20*/); //5% per second
    }

    //check
    if (health_cd <= RATIONS_CD && me->GetHealth() >= me->GetMaxHealth() && me->HasAura(EAT))
    {
        health_cd = uint32(-1);
        me->RemoveAurasDueToSpell(EAT);
    }

    if (mana_cd <= RATIONS_CD && me->getPowerType() == POWER_MANA &&
        me->GetPower(POWER_MANA) >= me->GetMaxPower(POWER_MANA) &&
        me->HasAura(DRINK))
    {
        mana_cd = uint32(-1);
        me->RemoveAurasDueToSpell(DRINK);
    }
}
//PASSIVES
// Used to apply common passives (run once)
void bot_ai::ApplyPassives(uint8 botOrPetType) const
{
    //me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
    //me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, true);

    //if (IsMinionAI() && botOrPetType != CLASS_MAGE)
    //    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

    //movement speed
    if (master->HasAuraType(SPELL_AURA_MOD_SPEED_ALWAYS) ||
        master->HasAuraType(SPELL_AURA_MOD_SPEED_NOT_STACK) ||
        master->HasAuraType(SPELL_AURA_MOD_INCREASE_SPEED))
        RefreshAura(BOAR);

    //apply +healing taken
    if (master->getLevel() >= 40)
        RefreshAura(BOR);//+40%

    if (IsPetAI())
    {
        switch (botOrPetType)
        {
            case PET_TYPE_VOIDWALKER:
                RefreshAura(DEFENSIVE_STANCE_PASSIVE,2);
                break;
            default:
                break;
        }
    }
}
//check if our party players are in duel. if so - ignore them, their opponents and any bots they have
bool bot_ai::InDuel(Unit* target) const
{
    if (!target) return false;
    bool isbot = target->GetTypeId() == TYPEID_UNIT && (target->ToCreature()->GetIAmABot() || target->ToCreature()->GetIAmABotsPet());
    Player* player = target->GetTypeId() == TYPEID_PLAYER ? target->ToPlayer() : isbot ? target->ToCreature()->GetBotOwner() : NULL;
    if (!player)
    {
        if (!target->IsControlledByPlayer())
            return false;
        player = target->GetCharmerOrOwnerPlayerOrPlayerItself();
    }

    return (player && player->duel && (IsInBotParty(player) || IsInBotParty(player->duel->opponent)));
}
//Used to find target for priest's dispels and mage's spellsteal (also shaman's purge in future)
//Returns dispellable/stealable 'Any Hostile Unit Attacking BotParty'
Unit* bot_minion_ai::FindHostileDispelTarget(float dist, bool stealable) const
{
    CellCoord p(Trinity::ComputeCellCoord(me->GetPositionX(), me->GetPositionY()));
    Cell cell(p);
    cell.SetNoCreate();

    Unit* unit = NULL;

    HostileDispelTargetCheck check(me, dist, stealable, this);
    Trinity::UnitLastSearcher <HostileDispelTargetCheck> searcher(me, unit, check);

    TypeContainerVisitor<Trinity::UnitLastSearcher <HostileDispelTargetCheck>, WorldTypeMapContainer > world_unit_searcher(searcher);
    TypeContainerVisitor<Trinity::UnitLastSearcher <HostileDispelTargetCheck>, GridTypeMapContainer >  grid_unit_searcher(searcher);

    cell.Visit(p, world_unit_searcher, *me->GetMap(), *me, dist);
    cell.Visit(p, grid_unit_searcher, *me->GetMap(), *me, dist);

    return unit;
}
//Finds single target affected by given spell (and given caster if is)
//Can check:
//    hostile targets  (hostile = 0) <default>
//    our party players (hostile = 1)
//    our party members  (hostile = 2)
//    any friendly target (hostile = 3)
//    any target in range  (hostile = any other value)
Unit* bot_minion_ai::FindAffectedTarget(uint32 spellId, uint64 caster, float dist, uint8 hostile) const
{
    if (master->GetMap()->Instanceable())
        dist = DEFAULT_VISIBILITY_INSTANCE;

    CellCoord p(Trinity::ComputeCellCoord(master->GetPositionX(), master->GetPositionY()));
    Cell cell(p);
    cell.SetNoCreate();

    Unit* unit = NULL;

    AffectedTargetCheck check(caster, dist, spellId, master, hostile);
    Trinity::UnitLastSearcher <AffectedTargetCheck> searcher(master, unit, check);

    TypeContainerVisitor<Trinity::UnitLastSearcher <AffectedTargetCheck>, WorldTypeMapContainer > world_unit_searcher(searcher);
    TypeContainerVisitor<Trinity::UnitLastSearcher <AffectedTargetCheck>, GridTypeMapContainer >  grid_unit_searcher(searcher);

    cell.Visit(p, world_unit_searcher, *master->GetMap(), *master, dist);
    cell.Visit(p, grid_unit_searcher, *master->GetMap(), *master, dist);

    return unit;
}
//Finds target for mage's polymorph or shaman's hex
Unit* bot_minion_ai::FindPolyTarget(float dist, Unit* currTarget) const
{
    if (!currTarget)
        return NULL;

    CellCoord p(Trinity::ComputeCellCoord(me->GetPositionX(), me->GetPositionY()));
    Cell cell(p);
    cell.SetNoCreate();

    Unit* unit = NULL;

    PolyUnitCheck check(me, dist, currTarget);
    Trinity::UnitLastSearcher <PolyUnitCheck> searcher(me, unit, check);

    TypeContainerVisitor<Trinity::UnitLastSearcher <PolyUnitCheck>, WorldTypeMapContainer > world_unit_searcher(searcher);
    TypeContainerVisitor<Trinity::UnitLastSearcher <PolyUnitCheck>, GridTypeMapContainer >  grid_unit_searcher(searcher);

    cell.Visit(p, world_unit_searcher, *me->GetMap(), *me, dist);
    cell.Visit(p, grid_unit_searcher, *me->GetMap(), *me, dist);

    return unit;
}
//Finds target for direct fear (warlock)
Unit* bot_minion_ai::FindFearTarget(float dist) const
{
    CellCoord p(Trinity::ComputeCellCoord(me->GetPositionX(), me->GetPositionY()));
    Cell cell(p);
    cell.SetNoCreate();

    Unit* unit = NULL;

    FearUnitCheck check(me, dist);
    Trinity::UnitLastSearcher <FearUnitCheck> searcher(me, unit, check);

    TypeContainerVisitor<Trinity::UnitLastSearcher <FearUnitCheck>, WorldTypeMapContainer > world_unit_searcher(searcher);
    TypeContainerVisitor<Trinity::UnitLastSearcher <FearUnitCheck>, GridTypeMapContainer >  grid_unit_searcher(searcher);

    cell.Visit(p, world_unit_searcher, *me->GetMap(), *me, dist);
    cell.Visit(p, grid_unit_searcher, *me->GetMap(), *me, dist);

    return unit;
}
//Finds target for paladin's repentance
Unit* bot_minion_ai::FindStunTarget(float dist) const
{
    CellCoord p(Trinity::ComputeCellCoord(me->GetPositionX(), me->GetPositionY()));
    Cell cell(p);
    cell.SetNoCreate();

    Unit* unit = NULL;

    StunUnitCheck check(me, dist);
    Trinity::UnitLastSearcher <StunUnitCheck> searcher(me, unit, check);

    TypeContainerVisitor<Trinity::UnitLastSearcher <StunUnitCheck>, WorldTypeMapContainer > world_unit_searcher(searcher);
    TypeContainerVisitor<Trinity::UnitLastSearcher <StunUnitCheck>, GridTypeMapContainer >  grid_unit_searcher(searcher);

    cell.Visit(p, world_unit_searcher, *me->GetMap(), *me, dist);
    cell.Visit(p, grid_unit_searcher, *me->GetMap(), *me, dist);

    return unit;
}
//Finds target for priest's shackles
Unit* bot_minion_ai::FindUndeadCCTarget(float dist, uint32 spellId/* = 0*/) const
{
    CellCoord p(Trinity::ComputeCellCoord(me->GetPositionX(), me->GetPositionY()));
    Cell cell(p);
    cell.SetNoCreate();

    Unit* unit = NULL;

    UndeadCCUnitCheck check(me, dist, spellId);
    Trinity::UnitLastSearcher <UndeadCCUnitCheck> searcher(me, unit, check);

    TypeContainerVisitor<Trinity::UnitLastSearcher <UndeadCCUnitCheck>, WorldTypeMapContainer > world_unit_searcher(searcher);
    TypeContainerVisitor<Trinity::UnitLastSearcher <UndeadCCUnitCheck>, GridTypeMapContainer >  grid_unit_searcher(searcher);

    cell.Visit(p, world_unit_searcher, *me->GetMap(), *me, dist);
    cell.Visit(p, grid_unit_searcher, *me->GetMap(), *me, dist);

    return unit;
}
//Finds target for druid's Entangling Roots
Unit* bot_minion_ai::FindRootTarget(float dist, uint32 spellId) const
{
    CellCoord p(Trinity::ComputeCellCoord(me->GetPositionX(), me->GetPositionY()));
    Cell cell(p);
    cell.SetNoCreate();

    Unit* unit = NULL;

    RootUnitCheck check(me, me->GetVictim(), dist, spellId);
    Trinity::UnitLastSearcher <RootUnitCheck> searcher(me, unit, check);

    TypeContainerVisitor<Trinity::UnitLastSearcher <RootUnitCheck>, WorldTypeMapContainer > world_unit_searcher(searcher);
    TypeContainerVisitor<Trinity::UnitLastSearcher <RootUnitCheck>, GridTypeMapContainer >  grid_unit_searcher(searcher);

    cell.Visit(p, world_unit_searcher, *me->GetMap(), *me, dist);
    cell.Visit(p, grid_unit_searcher, *me->GetMap(), *me, dist);

    return unit;
}
//Finds casting target (friend or enemy)
Unit* bot_minion_ai::FindCastingTarget(float maxdist, float mindist, bool isFriend, uint32 spellId) const
{
    CellCoord p(Trinity::ComputeCellCoord(me->GetPositionX(), me->GetPositionY()));
    Cell cell(p);
    cell.SetNoCreate();

    Unit* unit = NULL;

    CastingUnitCheck check(me, mindist, maxdist, isFriend, spellId);
    Trinity::UnitLastSearcher <CastingUnitCheck> searcher(me, unit, check);

    TypeContainerVisitor<Trinity::UnitLastSearcher <CastingUnitCheck>, WorldTypeMapContainer > world_unit_searcher(searcher);
    TypeContainerVisitor<Trinity::UnitLastSearcher <CastingUnitCheck>, GridTypeMapContainer >  grid_unit_searcher(searcher);

    cell.Visit(p, world_unit_searcher, *me->GetMap(), *me, maxdist);
    cell.Visit(p, grid_unit_searcher, *me->GetMap(), *me, maxdist);

    return unit;
}
// Returns target for AOE spell (blizzard, hurricane etc.) based on attackers count
// Cycles through BotParty, first checks player and, if checked, npcbots
// If checked, can return friendly target as target for AOE spell
Unit* bot_minion_ai::FindAOETarget(float dist, bool checkbots, bool targetfriend) const
{
    if (IsCasting())
        return NULL;

    Unit* unit = NULL;
    Group* pGroup = master->GetGroup();
    if (!pGroup)
    {
        AttackerSet m_attackers = master->getAttackers();
        if (m_attackers.size() > 1)
        {
            uint32 mCount = 0;
            for(AttackerSet::iterator iter = m_attackers.begin(); iter != m_attackers.end(); ++iter)
            {
                if (!(*iter) || !(*iter)->IsAlive()) continue;
                if ((*iter)->isMoving()) continue;
                if ((*iter)->HasBreakableByDamageCrowdControlAura())
                    continue;
                if (me->GetDistance(*iter) < dist)
                    ++mCount;
            }
            if (mCount > 1)
            {
                Unit* u = master->GetVictim();
                if (mCount > 3 && targetfriend == true)
                    unit = master;
                else if (u && FindSplashTarget(dist + 8, u))
                    unit = u;
            }//end if
        }//end if
        if (!checkbots)
            return unit;
        for (uint8 i = 0; i != master->GetMaxNpcBots(); ++i)
        {
            Creature* bot = master->GetBotMap(i)->_Cre();
            if (!bot || !bot->IsAlive() || !bot->IsInWorld() || me->GetDistance(bot) > dist) continue;

            AttackerSet b_attackers = bot->getAttackers();
            if (b_attackers.size() > 1)
            {
                uint32 mCount = 0;
                for(AttackerSet::iterator iter = b_attackers.begin(); iter != b_attackers.end(); ++iter)
                {
                    if (!(*iter) || !(*iter)->IsAlive()) continue;
                    if ((*iter)->isMoving()) continue;
                    if ((*iter)->HasBreakableByDamageCrowdControlAura())
                        continue;
                    if (me->GetDistance(*iter) < dist)
                        ++mCount;
                }
                if (mCount > 1)
                {
                    Unit* u = bot->GetVictim();
                    if (mCount > 3 && targetfriend == true)
                        unit = bot;
                    else if (u && FindSplashTarget(dist + 8, u))
                        unit = u;
                }//end if
            }//end if
            if (unit) return unit;
        }//end for
        return unit;
    }
    bool Bots = false;
    for (GroupReference* itr = pGroup->GetFirstMember(); itr != NULL; itr = itr->next())
    {
        Player* tPlayer = itr->GetSource();
        if (!tPlayer) continue;
        if (checkbots && tPlayer->HaveBot())
            Bots = true;
        if (!tPlayer->IsInWorld() || tPlayer->IsBeingTeleported()) continue;
        if (!tPlayer->IsAlive() || me->GetMap() != tPlayer->FindMap()) continue;
        if (me->GetDistance(tPlayer) > 40) continue;

        AttackerSet m_attackers = tPlayer->getAttackers();
        if (m_attackers.size() > 1)
        {
            uint32 mCount = 0;
            for (AttackerSet::iterator iter = m_attackers.begin(); iter != m_attackers.end(); ++iter)
            {
                if (!(*iter) || !(*iter)->IsAlive()) continue;
                if ((*iter)->isMoving()) continue;
                if (me->GetDistance(*iter) < dist)
                    ++mCount;
            }
            if (mCount > 1)
            {
                Unit* u = tPlayer->GetVictim();
                if (mCount > 3 && targetfriend == true)
                    unit = tPlayer;
                else if (u && FindSplashTarget(dist + 8, u))
                    unit = u;
            }//end if
        }//end if
        if (unit) return unit;
    }//end for
    if (!Bots) return NULL;
    for (GroupReference* itr = pGroup->GetFirstMember(); itr != NULL; itr = itr->next())
    {
        Player* tPlayer = itr->GetSource();
        if (tPlayer == NULL || !tPlayer->HaveBot()) continue;
        if (!tPlayer->IsInWorld() || tPlayer->IsBeingTeleported()) continue;
        if (me->GetMap() != tPlayer->FindMap()) continue;
        for (uint8 i = 0; i != tPlayer->GetMaxNpcBots(); ++i)
        {
            Creature* bot = tPlayer->GetBotMap(i)->_Cre();
            if (!bot || !bot->IsAlive() || me->GetMap() != bot->FindMap()) continue;
            if (!bot->IsInWorld()) continue;
            if (me->GetDistance(bot) > 40) continue;

            AttackerSet b_attackers = bot->getAttackers();
            if (b_attackers.size() > 1)
            {
                uint32 mCount = 0;
                for(AttackerSet::iterator iter = b_attackers.begin(); iter != b_attackers.end(); ++iter)
                {
                    if (!(*iter) || !(*iter)->IsAlive()) continue;
                    if ((*iter)->isMoving()) continue;
                    if (me->GetDistance(*iter) < dist)
                        ++mCount;
                }
                if (mCount > 1)
                {
                    Unit* u = bot->GetVictim();
                    if (mCount > 3 && targetfriend == true)
                        unit = bot;
                    else if (u && FindSplashTarget(dist + 8, u))
                        unit = u;
                }//end if
            }//end if
        }//end for
        if (unit) return unit;
    }//end for
    return unit;
}
// Finds secondary target for spells like Cleave, Swipe, Mind Sear etc.
Unit* bot_minion_ai::FindSplashTarget(float dist, Unit* To, float splashdist) const
{
    if (!To)
        To = me->GetVictim();
    if (!To)
        return NULL;

    if (me->GetDistance(To) > dist)
        return NULL;

    CellCoord p(Trinity::ComputeCellCoord(me->GetPositionX(), me->GetPositionY()));
    Cell cell(p);
    cell.SetNoCreate();

    Unit* unit = NULL;

    SecondEnemyCheck check(me, dist, splashdist, To, this);
    Trinity::UnitLastSearcher <SecondEnemyCheck> searcher(me, unit, check);

    TypeContainerVisitor<Trinity::UnitLastSearcher <SecondEnemyCheck>, WorldTypeMapContainer > world_unit_searcher(searcher);
    TypeContainerVisitor<Trinity::UnitLastSearcher <SecondEnemyCheck>, GridTypeMapContainer >  grid_unit_searcher(searcher);

    cell.Visit(p, world_unit_searcher, *me->GetMap(), *me, dist);
    cell.Visit(p, grid_unit_searcher, *me->GetMap(), *me, dist);

    return unit;
}

Unit* bot_minion_ai::FindTranquilTarget(float mindist, float maxdist) const
{
    CellCoord p(Trinity::ComputeCellCoord(me->GetPositionX(), me->GetPositionY()));
    Cell cell(p);
    cell.SetNoCreate();

    Unit* unit = NULL;

    TranquilTargetCheck check(me, mindist, maxdist, this);
    Trinity::UnitLastSearcher <TranquilTargetCheck> searcher(me, unit, check);

    TypeContainerVisitor<Trinity::UnitLastSearcher <TranquilTargetCheck>, WorldTypeMapContainer > world_unit_searcher(searcher);
    TypeContainerVisitor<Trinity::UnitLastSearcher <TranquilTargetCheck>, GridTypeMapContainer >  grid_unit_searcher(searcher);

    cell.Visit(p, world_unit_searcher, *me->GetMap(), *me, maxdist);
    cell.Visit(p, grid_unit_searcher, *me->GetMap(), *me, maxdist);

    return unit;
}

void bot_minion_ai::GetNearbyTargetsList(std::list<Unit*> &targets, float maxdist, float mindist, bool forCC) const
{
    CellCoord p(Trinity::ComputeCellCoord(me->GetPositionX(), me->GetPositionY()));
    Cell cell(p);
    cell.SetNoCreate();

    NearbyHostileUnitCheck check(me, maxdist, mindist, this, forCC);
    Trinity::UnitListSearcher <NearbyHostileUnitCheck> searcher(me, targets, check);

    TypeContainerVisitor<Trinity::UnitListSearcher <NearbyHostileUnitCheck>, WorldTypeMapContainer > world_unit_searcher(searcher);
    TypeContainerVisitor<Trinity::UnitListSearcher <NearbyHostileUnitCheck>, GridTypeMapContainer >  grid_unit_searcher(searcher);

    cell.Visit(p, world_unit_searcher, *me->GetMap(), *me, maxdist);
    cell.Visit(p, grid_unit_searcher, *me->GetMap(), *me, maxdist);
}

//////////
//Internal
//////////

//Using rist-rank spell as source, returns spell of max rank allowed for given caster
uint32 bot_ai::InitSpell(Unit* caster, uint32 spell)
{
    SpellInfo const* info = sSpellMgr->GetSpellInfo(spell);
    if (!info)
        return 0;//weird spell with no info, disable it

    uint8 lvl = caster->getLevel();
    if (lvl < info->BaseLevel)//only 1st rank spells check
        return 0;//cannot use this spell

    if (SpellInfo const* spInfo = info->GetNextRankSpell())
    {
        if (lvl < spInfo->BaseLevel)
            return spell;//cannot use next rank, use this one
        else
            return InitSpell(caster, spInfo->Id);//can use next rank, forward check
    }

    return spell;//max rank, use this
}
//Health magement for minions
//Including health calcs, set and regeneration
void bot_minion_ai::_OnHealthUpdate(uint8 myclass, uint8 mylevel) const
{
    //TC_LOG_ERROR("entities.player", "_OnHealthUpdate(): updating bot %s", me->GetName().c_str());
    float pct = me->GetHealthPct();// needs for regeneration
    uint32 m_basehp = classinfo.basehealth;
    //TC_LOG_ERROR("entities.player", "class base health: %u", m_basehp);
    me->SetCreateHealth(m_basehp);
    float stammod;
    switch (myclass)
    {
        case CLASS_WARRIOR: case CLASS_DEATH_KNIGHT: case DRUID_BEAR_FORM:
            switch (master->getClass())
            {
                case CLASS_PRIEST: case CLASS_MAGE: case CLASS_WARLOCK:
                    stammod = 16.f;
                    break;
                case CLASS_DRUID: case CLASS_SHAMAN: case CLASS_HUNTER: case CLASS_ROGUE:
                    stammod = 13.f;
                    break;
                default: stammod = 9.8f; break;
            }
            break;
        case CLASS_PALADIN:
            switch (master->getClass())
            {
                case CLASS_PRIEST: case CLASS_MAGE: case CLASS_WARLOCK:
                    stammod = 15.5f;
                    break;
                case CLASS_DRUID: case CLASS_SHAMAN: case CLASS_HUNTER: case CLASS_ROGUE:
                    stammod = 12.5f;
                    break;
                case CLASS_PALADIN:
                    stammod = 9.8f;
                    break;
                default: stammod = 9.f; break;
            }
            break;
        case CLASS_PRIEST: case CLASS_MAGE: case CLASS_WARLOCK:
            switch (master->getClass())
            {
                case CLASS_PRIEST: case CLASS_MAGE: case CLASS_WARLOCK:
                    stammod = 9.8f;
                    break;
                case CLASS_DRUID: case CLASS_SHAMAN: case CLASS_HUNTER: case CLASS_ROGUE:
                    stammod = 8.f;
                    break;
                default: stammod = 5.f; break;
            }
            break;
        case CLASS_DRUID: case DRUID_CAT_FORM: case CLASS_SHAMAN: case CLASS_HUNTER: case CLASS_ROGUE:
            switch (master->getClass())
            {
                case CLASS_PRIEST: case CLASS_MAGE: case CLASS_WARLOCK:
                    stammod = 12.f;
                    break;
                case CLASS_DRUID: case CLASS_SHAMAN: case CLASS_HUNTER: case CLASS_ROGUE:
                    stammod = 9.8f;
                    break;
                default: stammod = 8.f; break;
            }
            break;
        default: stammod = 10.f;
            break;
    }
    stammod -= 0.3f;
    stammod *= 0.75f;
    //TC_LOG_ERROR("entities.player", "stammod: %f", stammod);

    //manually pick up stamina from bot's buffs
    float stamValue = me->GetTotalStatValue(STAT_STAMINA);
    stamValue = std::max(stamValue - 16.f, 1.f); //remove base stamina (not calculated into health)

    for (uint8 i = 0; i != BOT_INVENTORY_SIZE; ++i)
        stamValue += 1.f * (static_cast<BotStat>(_stats[i])[ITEM_MOD_STAMINA]);

    //TC_LOG_ERROR("entities.player", "bot's stats to health add: Stamina (%f), value: %f", stamValue, stamValue * 10.f);
    int32 hp_add = int32(stamValue * 10.f);

    for (uint8 i = 0; i != BOT_INVENTORY_SIZE; ++i)
        hp_add += 3.f * (static_cast<BotStat>(_stats[i])[ITEM_MOD_HEALTH]);

    //pick up master's stamina from items
    float total_pct = std::max((master->GetModifierValue(UNIT_MOD_STAT_STAMINA, TOTAL_PCT) - 0.1f), 1.f);
    float base_stam = master->GetModifierValue(UNIT_MOD_STAT_STAMINA, BASE_VALUE);
    base_stam = std::max(base_stam - 18.f, 0.f); //remove base stamina (not calculated into health)
    stamValue = base_stam * master->GetModifierValue(UNIT_MOD_STAT_STAMINA, BASE_PCT) * total_pct;
    //TC_LOG_ERROR("entities.player", "stat to health add: Stamina (%f), value: %f", stamValue, stamValue*stammod);
    hp_add += int32(stamValue * stammod);
    //float stamstat = stat * 0.5f;
    //if (stamValue > stamstat)
    //{
    //    //sLog->outBasic("selected stat to health add: Stamina (%f), value: %f", stamValue, stamValue*stammod);
    //    hp_add += int32(stamValue * stammod);
    //}
    //else
    //{
    //    //sLog->outBasic("selected stat to health add: stamStat (%f), value: %f", stamstat, stamstat*stammod);
    //    hp_add += int32(stamstat * stammod);
    //}
    //sLog->outBasic("health to add after master's stat mod: %i", hp_add);
    int32 miscVal = me->getGender() * mylevel;
    //TC_LOG_ERROR("entities.player", "health to remove from gender mod: %i", -miscVal);
    hp_add -= miscVal;//less hp for females lol
    //TC_LOG_ERROR("entities.player", "health to add after gender mod: %i", hp_add);
    //miscVal = myrace*(mylevel/5);
    //TC_LOG_ERROR("entities.player", "health to add from race mod: %i", miscVal);
    //hp_add += miscVal;//draenei tanks lol
    //TC_LOG_ERROR("entities.player", "health to add after race mod: %i", hp_add);
    miscVal = master->GetNpcBotSlot(me->GetGUID()) * (mylevel / 5);
    //TC_LOG_ERROR("entities.player", "health to remove from slot mod: %i", -miscVal);
    hp_add -= miscVal;
    //TC_LOG_ERROR("entities.player", "health to add after slot mod: %i", hp_add);
    uint32 m_totalhp = m_basehp + hp_add; //m_totalhp = uint32(float(m_basehp + hp_add) * stammod);
    //TC_LOG_ERROR("entities.player", "total base health: %u", m_totalhp);
    uint32 bonuspct = 0;
    bonuspct += 35 * (master->GetBotTankGuid() == me->GetGUID());
    bonuspct += 8 * (GetBotStance() == DEATH_KNIGHT_FROST_PRESENCE);
    if (bonuspct)
        m_totalhp = (m_totalhp * (100 + bonuspct)) / 100;
    me->SetModifierValue(UNIT_MOD_HEALTH, BASE_VALUE, float(m_totalhp)); //replaces base hp at max lvl
    me->UpdateMaxHealth();//will use our values we just set (update base health and buffs)
    //TC_LOG_ERROR("entities.player", "overall hp: %u", me->GetMaxHealth());
    me->SetHealth(uint32(0.5f + float(me->GetMaxHealth()) * pct / 100.f)); //restore pct
    if (!me->IsInCombat())
        me->SetHealth(me->GetHealth() + m_basehp / 100 + me->getLevel() / 2); //regenerate
}
//Mana management for minions
//Including calcs and set
void bot_minion_ai::_OnManaUpdate(uint8 myclass, uint8 mylevel, bool shapeshift)
{
    if (me->getPowerType() != POWER_MANA)
        return;
    //TC_LOG_ERROR("entities.player", "_OnManaUpdate(): updating bot %s", me->GetName().c_str());
    float pct = (float(me->GetPower(POWER_MANA)) * 100.f) / float(me->GetMaxPower(POWER_MANA));
    float m_basemana = classinfo.basemana > 0 ? classinfo.basemana : me->GetCreateMana();
    //TC_LOG_ERROR("entities.player", "classinfo base mana = %f", m_basemana);
    me->SetCreateMana(m_basemana); //set base mana, critical
    float manamod = 15.f; //here we set mana multiplier from intellect as we gain mana from MASTER's stats mostly
    switch (myclass)
    {
        case CLASS_HUNTER:                     manamod =  8.5f; break;
        case CLASS_PALADIN:                    manamod =  4.5f; break;
        case CLASS_SHAMAN:                     manamod = 13.5f; break;
        case CLASS_DRUID:                      manamod = 12.5f; break;
        case CLASS_PRIEST:                     manamod = 16.5f; break;
        case CLASS_MAGE: case CLASS_WARLOCK:   manamod = 10.5f; break;
        default:                                                break;
    }

    manamod *= 0.75f; //custom

    //TC_LOG_ERROR("entities.player", "Manamod: %f", manamod);
    float intValue = me->GetTotalStatValue(STAT_INTELLECT);
    intValue = std::max(intValue - 18.f, 1.f); //remove base int (not calculated into mana)

    for (uint8 i = 0; i != BOT_INVENTORY_SIZE; ++i)
    {
        intValue += 1.f * (static_cast<BotStat>(_stats[i])[ITEM_MOD_INTELLECT]);
        m_basemana += 3.f * (static_cast<BotStat>(_stats[i])[ITEM_MOD_MANA]);
    }

    //TC_LOG_ERROR("entities.player", "bot's stats to mana add: Int (%f), value: %f", intValue, intValue * manamod);
    m_basemana += intValue * 15.f;
    //pick up master's intellect from items if master has mana
    if (master->getPowerType() == POWER_MANA)
    {
        float total_pct = std::max((master->GetModifierValue(UNIT_MOD_STAT_INTELLECT, TOTAL_PCT) - 0.1f), 1.f);
        intValue = std::max(master->GetModifierValue(UNIT_MOD_STAT_INTELLECT, BASE_VALUE) - 18.f, 1.f); //remove base int (not calculated into mana)
        intValue = intValue * master->GetModifierValue(UNIT_MOD_STAT_INTELLECT, BASE_PCT) * total_pct;
    }
    else // pick up maxstat
        intValue = stat * 0.5f;
    //TC_LOG_ERROR("entities.player", "mana add from master's stat: %f", intValue * manamod);
    m_basemana += intValue * manamod;
    //TC_LOG_ERROR("entities.player", "base mana + mana from master's intellect or stat: %f", m_basemana);
    //intValue = me->GetTotalAuraModValue(UNIT_MOD_STAT_INTELLECT);
    //sLog->outBasic("Intellect from buffs: %f", intValue);
    //m_basemana += uint32(intValue) * manamod;
    //sLog->outBasic("base mana + mana from intellect + mana from buffs: %u", m_basemana);
    uint8 otherVal = me->getGender() * 3 * mylevel;
    //TC_LOG_ERROR("entities.player", "mana to add from gender mod: %u", otherVal);
    m_basemana += float(otherVal); //more mana for females lol
    //TC_LOG_ERROR("entities.player", "base mana after gender mod: %f", m_basemana);
    otherVal = master->GetNpcBotSlot(me->GetGUID()) * (mylevel / 5); //only to make mana unique
    //TC_LOG_ERROR("entities.player", "mana to remove from slot mod: %i", -int8(otherVal));
    m_basemana -= otherVal;
    //TC_LOG_ERROR("entities.player", "base mana after slot mod: %f", m_basemana);
    float m_totalmana = m_basemana;
    //TC_LOG_ERROR("entities.player", "total mana to set: %f", m_totalmana);
    me->SetModifierValue(UNIT_MOD_MANA, BASE_VALUE, m_totalmana);
    me->UpdateMaxPower(POWER_MANA);
    //TC_LOG_ERROR("entities.player", "Overall mana to set: %u", me->GetMaxPower(POWER_MANA));
    if (tempMana)
    {
        me->SetPower(POWER_MANA, tempMana);
        if (shapeshift == false)
            tempMana = 0;
    }
    else
        me->SetPower(POWER_MANA, uint32(0.5f + float(me->GetMaxPower(POWER_MANA)) * pct / 100.f)); //restore pct
    //No Regen
}
//Melee damage for minions (melee classes only)
//Calculation is based on master's attack power if melee/hunter or spellpower
void bot_minion_ai::_OnMeleeDamageUpdate(uint8 myclass) const
{
    if (ap_mod < 0.1f) return; //do not bother casters
    //sLog->outBasic("_OnMeleeDamageUpdate: Updating bot %s", me->GetName().c_str());
    float my_ap_mod = ap_mod;
    float mod = master->getClass() == CLASS_HUNTER ? (master->GetModifierValue(UNIT_MOD_DAMAGE_RANGED, BASE_PCT) + master->GetModifierValue(UNIT_MOD_DAMAGE_RANGED, TOTAL_PCT))/2.f :
        (master->GetModifierValue(UNIT_MOD_DAMAGE_MAINHAND, BASE_PCT) + master->GetModifierValue(UNIT_MOD_DAMAGE_MAINHAND, TOTAL_PCT))/2.f;
    mod = std::max(mod, 1.f); // x1 is Minimum
    mod = std::min(mod, 2.5f); // x2.5 is Maximum
    //sLog->outBasic("got base damage modifier: %f", mod);
    mod -= (mod - 1.f)*0.33f;//reduce bonus by 33%
    //sLog->outBasic("damage modifier truencated to %f, applying", mod);

    for (uint8 i = 0; i != MAX_EQUIPMENT_ITEMS; ++i)
        me->SetModifierValue(UnitMods(UNIT_MOD_DAMAGE_MAINHAND + i), BASE_VALUE, static_cast<BotStat>(_stats[i])[BOT_ITEM_MOD_DAMAGE]);

    me->SetModifierValue(UNIT_MOD_DAMAGE_MAINHAND, BASE_PCT, mod);
    me->SetModifierValue(UNIT_MOD_DAMAGE_OFFHAND, BASE_PCT, mod);
    me->SetModifierValue(UNIT_MOD_DAMAGE_RANGED, BASE_PCT, mod);
    //me->SetModifierValue(UNIT_MOD_DAMAGE_RANGED, BASE_PCT, mod);//NUY
    mod = (mod - 1.f)*0.5f;
    //sLog->outBasic("reduced damage modifier to gain bonus: %f", mod);
    //sLog->outBasic("base ap modifier is %f", my_ap_mod);
    my_ap_mod *= 0.5f;
    //sLog->outBasic("ap modifier multiplied to %f", my_ap_mod);
    my_ap_mod += my_ap_mod > 0.f ? mod : 0.f; //add reduced master's multiplier if can have damage
    //sLog->outBasic("ap modifier + mod = %f", my_ap_mod);
    me->SetModifierValue(UNIT_MOD_ATTACK_POWER, BASE_PCT, my_ap_mod);
    me->SetModifierValue(UNIT_MOD_ATTACK_POWER_RANGED, BASE_PCT, my_ap_mod);

    int32 sppower = 0;
    for (uint8 i = SPELL_SCHOOL_HOLY; i != MAX_SPELL_SCHOOL; ++i)
    {
        int32 power = master->SpellBaseDamageBonusDone(SpellSchoolMask(1 << i));
        if (power > sppower)
            sppower = power;
    }
    //sLog->outBasic("master's spellpower is %i, multiplying...", sppower);
    sppower *= 1.5f;
    //sLog->outBasic("got spellpower of %i", sppower);
    //atpower = float(master->GetInt32Value(master->getClass() == CLASS_HUNTER ? UNIT_FIELD_RANGED_ATTACK_POWER : UNIT_FIELD_ATTACK_POWER));
    float atpower = master->GetTotalAttackPowerValue(master->getClass() == CLASS_HUNTER ? RANGED_ATTACK : BASE_ATTACK);
    //sLog->outBasic("master's base attack power is %f", atpower);
    atpower = sppower > atpower ? sppower : atpower; //highest stat is used (either 1.5x spellpower or attack power)
    //sLog->outBasic("chosen attack power stat value: %f", atpower);
    //sLog->outBasic("expected attack power: %f", atpower*ap_mod);
    atpower *= 0.333f; //reduce damage since we can have weapons

    for (uint8 i = 0; i != BOT_INVENTORY_SIZE; ++i)
    {
        atpower += static_cast<BotStat>(_stats[i])[ITEM_MOD_ATTACK_POWER] + static_cast<BotStat>(_stats[i])[ITEM_MOD_RANGED_ATTACK_POWER] +
            static_cast<BotStat>(_stats[i])[ITEM_MOD_STRENGTH] * 2 + static_cast<BotStat>(_stats[i])[ITEM_MOD_AGILITY] * 2;
    }

    me->SetModifierValue(UNIT_MOD_ATTACK_POWER, BASE_VALUE, atpower);
    if (myclass == CLASS_HUNTER || myclass == CLASS_ROGUE)
    {
        me->SetModifierValue(UNIT_MOD_ATTACK_POWER_RANGED, BASE_VALUE, atpower);
        me->UpdateAttackPowerAndDamage(true);
    }
    me->UpdateAttackPowerAndDamage();
    //sLog->outBasic("listing stats: ");
    //sLog->outBasic("attack power main hand: %f", me->GetTotalAttackPowerValue(BASE_ATTACK));
    //sLog->outBasic("attack power off hand: %f", me->GetTotalAttackPowerValue(OFF_ATTACK));
    //sLog->outBasic("attack power ranged: %f", me->GetTotalAttackPowerValue(RANGED_ATTACK));
    //sLog->outBasic("damage multiplier main hand: %f", me->GetModifierValue(UNIT_MOD_DAMAGE_MAINHAND, BASE_PCT) * me->GetModifierValue(UNIT_MOD_DAMAGE_MAINHAND, TOTAL_PCT));
    //sLog->outBasic("damage multiplier off hand: %f", me->GetModifierValue(UNIT_MOD_DAMAGE_OFFHAND, BASE_PCT) * me->GetModifierValue(UNIT_MOD_DAMAGE_OFFHAND, TOTAL_PCT));
    //sLog->outBasic("damage multiplier ranged: %f", me->GetModifierValue(UNIT_MOD_DAMAGE_RANGED, BASE_PCT) * me->GetModifierValue(UNIT_MOD_DAMAGE_RANGED, TOTAL_PCT));
    //sLog->outBasic("Damage range main hand: min: %f, max: %f", me->GetFloatValue(UNIT_FIELD_MINDAMAGE), me->GetFloatValue(UNIT_FIELD_MAXDAMAGE));
    //sLog->outBasic("Damage range off hand: min: %f, max: %f", me->GetFloatValue(UNIT_FIELD_MINOFFHANDDAMAGE), me->GetFloatValue(UNIT_FIELD_MAXOFFHANDDAMAGE));
    //sLog->outBasic("Damage range ranged: min: %f, max: %f", me->GetFloatValue(UNIT_FIELD_MINRANGEDDAMAGE), me->GetFloatValue(UNIT_FIELD_MAXRANGEDDAMAGE));
}
//Health for pets
//Same as for minions just simplified (modified to match real pets' values)
void bot_pet_ai::_OnHealthUpdate(uint8 /*petType*/, uint8 mylevel) const
{
    float hp_mult = 10.f;
    switch (GetPetType(me))
    {
        case PET_TYPE_VOIDWALKER:
            hp_mult = 11.f;
            break;
        default:
            break;
    }
    float pct = me->GetHealthPct();// needs for regeneration
    //Use simple checks and calcs
    //0.3 hp for bots (inaccurate but cheap)
    uint32 m_basehp = me->GetCreateHealth() / 2;
    //pick up stamina from buffs
    float stamValue = me->GetTotalStatValue(STAT_STAMINA);
    stamValue = std::max(stamValue - 18.f, 1.f); //remove base stamina (not calculated into health)
    uint32 hp_add = uint32(stamValue * hp_mult);
    hp_add += (m_creatureOwner->GetMaxHealth() - m_creatureOwner->GetCreateHealth()) * 0.3f;
    uint8 miscVal = GetPetType(me)*mylevel;
    hp_add -= miscVal;
    uint32 m_totalhp = m_basehp + hp_add;
    if (master->GetBotTankGuid() == me->GetGUID())
        m_totalhp = (m_totalhp * 135) / 100; //35% hp bonus for tanks
    me->SetModifierValue(UNIT_MOD_HEALTH, BASE_VALUE, float(m_totalhp));
    me->UpdateMaxHealth(); //will use values set (update base health and buffs)
    me->SetHealth(uint32(0.5f + float(me->GetMaxHealth()) * pct / 100.f)); //restore pct
    if (!me->IsInCombat())
        me->SetHealth(me->GetHealth() + m_basehp / 100 + me->getLevel() / 2); //regenerate
}
//Mana for pets
//Same as for minions just simplified (modified to match real pets' values)
void bot_pet_ai::_OnManaUpdate(uint8 /*petType*/, uint8 mylevel, bool /*shapeshift*/)
{
    if (me->getPowerType() != POWER_MANA)
        return;

    float mana_mult = 15.f;
    switch (GetPetType(me))
    {
        case PET_TYPE_VOIDWALKER:
            mana_mult = 11.5f;
            break;
        default:
            break;
    }
    float pct = (float(me->GetPower(POWER_MANA)) * 100.f) / float(me->GetMaxPower(POWER_MANA));
    //Use simple checks and calcs
    //0.3 mana for bots (inaccurate but cheap)
    float m_basemana = float(me->GetCreateMana());
    m_basemana += (std::max<float>(me->GetTotalStatValue(STAT_INTELLECT) - 18.f, 1.f))*mana_mult; //remove base stamina (not calculated into mana)
    m_basemana += float(m_creatureOwner->GetMaxPower(POWER_MANA) - m_creatureOwner->GetCreateMana())*0.3f;
    m_basemana -= float(GetPetType(me)*mylevel);
    me->SetModifierValue(UNIT_MOD_MANA, BASE_VALUE, m_basemana);
    me->UpdateMaxPower(POWER_MANA);
    me->SetPower(POWER_MANA, uint32(0.5f + float(me->GetMaxPower(POWER_MANA))*pct / 100.f));//restore pct
}
//Sends all master's bots a message to not try to evade for a certain period of time
void bot_ai::SendPartyEvadeAbort() const
{
    for (uint8 i = 0; i != master->GetMaxNpcBots(); ++i)
        if (Creature* bot = master->GetBotMap(i)->_Cre())
            if (bot_minion_ai* ai = bot->GetBotMinionAI())
                ai->SetEvadeTimer(50);
}
//Removes buggy bots' threat from party, so no 'stuck in combat' bugs form bot mod
//optionally interrupts casted spell if target is dead for bot and it's pet
void bot_minion_ai::_OnEvade()
{
    if (me->HasUnitState(UNIT_STATE_CASTING))
        for (uint8 i = CURRENT_FIRST_NON_MELEE_SPELL; i != CURRENT_AUTOREPEAT_SPELL; ++i)
            if (Spell* spell = me->GetCurrentSpell(CurrentSpellTypes(i)))
                if (!spell->GetSpellInfo()->IsChanneled())
                    if (Unit* u = spell->m_targets.GetUnitTarget())
                        if (!u->IsAlive() && !IsInBotParty(u))
                            me->InterruptSpell(CurrentSpellTypes(i), false, false);

    Creature* m_botsPet = me->GetBotsPet();
    if (m_botsPet && m_botsPet->HasUnitState(UNIT_STATE_CASTING))
        for (uint8 i = CURRENT_FIRST_NON_MELEE_SPELL; i != CURRENT_AUTOREPEAT_SPELL; ++i)
            if (Spell* spell = m_botsPet->GetCurrentSpell(CurrentSpellTypes(i)))
                if (!spell->GetSpellInfo()->IsChanneled())
                    if (Unit* u = spell->m_targets.GetUnitTarget())
                        if (!u->IsAlive() && !IsInBotParty(u))
                            m_botsPet->InterruptSpell(CurrentSpellTypes(i), false, false);

    if (Rand() > 10) return;
    if (!master->IsInCombat() && !me->IsInCombat() && (!m_botsPet || !m_botsPet->IsInCombat())) return;
    if (CheckAttackTarget(GetBotClassForCreature(me)))
        return;
    //ChatHandler ch(master);
    //ch.PSendSysMessage("_OnEvade() by bot %s", me->GetName().c_str());
    if (master->IsInCombat())
    {
        HostileRefManager& mgr = master->getHostileRefManager();
        if (!mgr.isEmpty())
        {
            std::set<Unit*> Set;
            HostileReference* ref = mgr.getFirst();
            while (ref)
            {
                if (ref->GetSource() && ref->GetSource()->GetOwner())
                    Set.insert(ref->GetSource()->GetOwner());
                ref = ref->next();
            }
            for (std::set<Unit*>::const_iterator i = Set.begin(); i != Set.end(); ++i)
            {
                Unit* unit = (*i);
                if (/*unit->IsFriendlyTo(master)*/IsInBotParty(unit) || !unit->IsInCombat())
                {
                    //ch.PSendSysMessage("_OnEvade(): %s's hostile reference is removed from %s!", unit->GetName().c_str(), master->GetName().c_str());
                    mgr.deleteReference(unit);
                }
            }
        }
    }
    else
    {
        SendPartyEvadeAbort();
        for (uint8 i = 0; i != master->GetMaxNpcBots(); ++i)
        {
            Creature* cre = master->GetBotMap(i)->_Cre();
            if (!cre) continue;
            if (cre->IsInCombat())
            {
                cre->DeleteThreatList();
                HostileRefManager& mgr = cre->getHostileRefManager();
                if (!mgr.isEmpty())
                {
                    std::set<Unit*> Set;
                    HostileReference* ref = mgr.getFirst();
                    while (ref)
                    {
                        if (ref->GetSource() && ref->GetSource()->GetOwner())
                            Set.insert(ref->GetSource()->GetOwner());
                        ref = ref->next();
                    }
                    for (std::set<Unit*>::const_iterator i = Set.begin(); i != Set.end(); ++i)
                    {
                        Unit* unit = (*i);
                        if (!unit->InSamePhase(me)) continue;
                        if (/*unit->IsFriendlyTo(master)*/IsInBotParty(unit) || !unit->IsInCombat())
                        {
                            //ch.PSendSysMessage("_OnEvade(): %s's hostile reference is removed from %s!", unit->GetName().c_str(), cre->GetName().c_str());
                            mgr.deleteReference(unit);
                        }
                    }
                }
                //if (mgr.isEmpty())// has empty threat list and no hostile refs - we have all rights to stop combat
                //{
                //    if (cre->IsInCombat())
                //    {
                //        //ch.PSendSysMessage("_OnEvade(): %s's HostileRef is empty! Combatstop!", cre->GetName().c_str());
                //        cre->ClearInCombat();
                //    }
                //}
            }

            Creature* m_botsPet = cre->GetBotsPet();
            if (!m_botsPet || !m_botsPet->IsInCombat()) continue;
            m_botsPet->DeleteThreatList();
            HostileRefManager& mgr = m_botsPet->getHostileRefManager();
            if (!mgr.isEmpty())
            {
                std::set<Unit*> Set;
                HostileReference* ref = mgr.getFirst();
                while (ref)
                {
                    if (ref->GetSource() && ref->GetSource()->GetOwner())
                        Set.insert(ref->GetSource()->GetOwner());
                    ref = ref->next();
                }
                for (std::set<Unit*>::const_iterator i = Set.begin(); i != Set.end(); ++i)
                {
                    Unit* unit = (*i);
                    if (!unit->InSamePhase(me)) continue;
                    if (/*unit->IsFriendlyTo(master)*/IsInBotParty(unit) || !unit->IsInCombat())
                    {
                        //ch.PSendSysMessage("_OnEvade(): %s's hostile reference is removed from %s!", unit->GetName().c_str(), m_botsPet->GetName().c_str());
                        mgr.deleteReference(unit);
                    }
                }
            }
            //if (mgr.isEmpty())// has empty threat list and no hostile refs - we have all rights to stop combat
            //{
            //    if (m_botsPet->IsInCombat())
            //    {
            //        //ch.PSendSysMessage("_OnEvade(): %s's HostileRef is empty! Combatstop!", pet->GetName().c_str());
            //        m_botsPet->ClearInCombat();
            //    }
            //}
        }
    }
}
//SpellHit()... OnSpellHit()
void bot_ai::OnSpellHit(Unit* /*caster*/, SpellInfo const* spell)
{
    for (uint8 i = 0; i != MAX_SPELL_EFFECTS; ++i)
    {
        uint32 auraname = spell->Effects[i].ApplyAuraName;
        //remove pet on mount
        if (auraname == SPELL_AURA_MOUNTED)
        {
            me->SetBotsPetDied();
            if (master->HasAuraType(SPELL_AURA_MOD_INCREASE_VEHICLE_FLIGHT_SPEED) ||
                master->HasAuraType(SPELL_AURA_MOD_INCREASE_MOUNTED_FLIGHT_SPEED))
            {
                const_cast<CreatureTemplate*>(me->GetCreatureTemplate())->InhabitType |= INHABIT_AIR;
                //me->AddUnitMovementFlag(MOVEMENTFLAG_HOVER);
                me->SetCanFly(true);
                me->SetDisableGravity(true);
                me->SetSpeed(MOVE_FLIGHT, master->GetSpeedRate(MOVE_FLIGHT) * 1.37f);
                me->SetSpeed(MOVE_RUN, master->GetSpeedRate(MOVE_FLIGHT) * 1.37f);
            }
            else
                me->SetSpeed(MOVE_RUN, master->GetSpeedRate(MOVE_RUN) * 1.25f);
        }

        //update stats
        if (auraname == SPELL_AURA_MOD_STAT)
        {
            shouldUpdateStats = true;
        }
        else
        {
            if (auraname == SPELL_AURA_MOD_INCREASE_HEALTH ||
                auraname == SPELL_AURA_MOD_INCREASE_HEALTH_2 ||
                auraname == SPELL_AURA_MOD_MAX_HEALTH ||//SPELL_AURA_MOD_INCREASE_HEALTH_2,SPELL_AURA_230
                auraname == SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT)
                doHealth = true;
            else if (auraname == SPELL_AURA_MOD_INCREASE_ENERGY ||
                auraname == SPELL_AURA_MOD_INCREASE_ENERGY_PERCENT)
                doMana = true;
        }
    }
}
//Messed up
//Hp + Mana update
//target update
//returns fake wait time between overall AI updates (if it is even understandable)
uint8 bot_ai::GetWait()
{
    if (doHealth)
    {
        doHealth = false;
        _OnHealthUpdate(me->GetBotClass(), master->getLevel());
    }
    if (doMana)
    {
        doMana = false;
        _OnManaUpdate(me->GetBotClass(), master->getLevel());
    }
    CheckAuras(true);
    //0 to 2 plus 1 for every 3 bots except first one
    return (1 + (master->GetNpcBotsCount() - 1)/3 + (irand(0,100) <= 50)*int8(RAND(-1,1)));
}
//Damage Mods
//1) Apply class-specified damage/crit chance/crit damage bonuses
//2) Apply bot damage multiplier
//3) Remove Creature damage multiplier (make independent from original config)
//Bug with config reload (creatures do not update their damage on reload) is not bot-related but still annoying
void bot_ai::ApplyBotDamageMultiplierMelee(uint32& damage, CalcDamageInfo& /*damageinfo*/) const
{
    //ApplyClassDamageMultiplierMelee(damage, damageinfo);
    damage = int32(float(damage)*dmgmult_melee/dmgmod_melee);
}
void bot_ai::ApplyBotDamageMultiplierMelee(int32& damage, SpellNonMeleeDamage& damageinfo, SpellInfo const* spellInfo, WeaponAttackType attackType, bool& crit) const
{
    ApplyClassDamageMultiplierMelee(damage, damageinfo, spellInfo, attackType, crit);
    damage = int32(float(damage)*dmgmult_melee/dmgmod_melee);
}
void bot_ai::ApplyBotDamageMultiplierSpell(int32& damage, SpellNonMeleeDamage& damageinfo, SpellInfo const* spellInfo, WeaponAttackType attackType, bool& crit) const
{
    ApplyClassDamageMultiplierSpell(damage, damageinfo, spellInfo, attackType, crit);
    damage = int32(float(damage)*dmgmult_spell/dmgmod_spell);
}
void bot_ai::ApplyBotDamageMultiplierEffect(SpellInfo const* spellInfo, uint8 effect_index, float &value) const
{
    //Only for damage effects which can scale (TC check)
    bool canEffectScale = false;
    switch (spellInfo->Effects[effect_index].Effect)
    {
        case SPELL_EFFECT_SCHOOL_DAMAGE:
        //case SPELL_EFFECT_DUMMY:
        //case SPELL_EFFECT_POWER_DRAIN:
        //case SPELL_EFFECT_HEALTH_LEECH:
        case SPELL_EFFECT_HEAL:
        case SPELL_EFFECT_WEAPON_DAMAGE:
        //case SPELL_EFFECT_POWER_BURN:
        //case SPELL_EFFECT_SCRIPT_EFFECT:
        case SPELL_EFFECT_NORMALIZED_WEAPON_DMG:
        //case SPELL_EFFECT_FORCE_CAST_WITH_VALUE:
        //case SPELL_EFFECT_TRIGGER_SPELL_WITH_VALUE:
        //case SPELL_EFFECT_TRIGGER_MISSILE_SPELL_WITH_VALUE:
            canEffectScale = true;
            break;
        default:
            break;
    }
    switch (spellInfo->Effects[effect_index].ApplyAuraName)
    {
        case SPELL_AURA_PERIODIC_DAMAGE:
        //case SPELL_AURA_DUMMY:
        //case SPELL_AURA_PERIODIC_HEAL:
        //case SPELL_AURA_DAMAGE_SHIELD:
        case SPELL_AURA_PROC_TRIGGER_DAMAGE:
        //case SPELL_AURA_PERIODIC_LEECH:
        //case SPELL_AURA_PERIODIC_MANA_LEECH:
        //case SPELL_AURA_SCHOOL_ABSORB:
        //case SPELL_AURA_PERIODIC_TRIGGER_SPELL_WITH_VALUE:
            canEffectScale = true;
            break;
        default:
            break;
    }

    if (!canEffectScale)
        return;

    ApplyClassDamageMultiplierEffect(spellInfo, effect_index, value);

    if (spellInfo->DmgClass == SPELL_DAMAGE_CLASS_MELEE || spellInfo->DmgClass == SPELL_DAMAGE_CLASS_RANGED)
        value = value*dmgmult_melee/dmgmod_melee;
    else if (spellInfo->DmgClass == SPELL_DAMAGE_CLASS_NONE || spellInfo->DmgClass == SPELL_DAMAGE_CLASS_MAGIC)
        value = value*dmgmult_spell/dmgmod_spell;
}
//////////
//GOSSIP//
//////////
//GossipHello
bool bot_minion_ai::OnGossipHello(Player* player, Creature* creature)
{
    if (creature->IsInCombat())
    {
        player->CLOSE_GOSSIP_MENU();
        return true;
    }

    if (player == creature->GetBotOwner())
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Manage equipment...", 6100, GOSSIP_ACTION_INFO_DEF + 1);

    switch (creature->GetBotClass())
    {
        case CLASS_MAGE:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I need food", 6001, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I need drink", 6001, GOSSIP_ACTION_INFO_DEF + 2);
            break;
        default:
            break;
    }

    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Nevermind", 0, GOSSIP_ACTION_INFO_DEF + 1);
    player->PlayerTalkClass->SendGossipMenu(GOSSIP_SERVE_MASTER, creature->GetGUID());
    return true;
}

//GossipSelect
bool bot_minion_ai::OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
{
    if (!IsInBotParty(player))
    {
        player->CLOSE_GOSSIP_MENU();
        return true;
    }

    player->PlayerTalkClass->ClearMenus();
    bool subMenu = false;

    switch (sender)
    {
        case 0: //any kind of fail
        {
            me->MonsterSay("...", LANG_UNIVERSAL, player);
            break;
        }
        case 1: //return to main menu
        {
            return bot_minion_ai::OnGossipHello(player, creature);
        }
        case 6001: //food/drink (classes: MAGE)
        {
            //Prevent high-leveled consumables for low-level characters
            Unit* checker;
            if (player->getLevel() < me->getLevel())
                checker = player;
            else
                checker = me;

            // Conjure Refreshment rank 1
            uint32 food = InitSpell(checker, 42955);
            bool iswater = (action == GOSSIP_ACTION_INFO_DEF + 2);
            if (!food)
            {
                if (!iswater)// Conjure Food rank 1
                    food = InitSpell(checker, 587);
                else// Conjure Water rank 1
                    food = InitSpell(checker, 5504);
            }
            if (!food)
            {
                std::string errorstr = "I can't conjure ";
                errorstr += iswater ? "water" : "food";
                errorstr += " yet";
                me->MonsterWhisper(errorstr.c_str(), player);
                //player->PlayerTalkClass->ClearMenus();
                //return OnGossipHello(player, me);
                break;
            }
            SpellInfo const* Info = sSpellMgr->GetSpellInfo(food);
            Spell* foodspell = new Spell(me, Info, TRIGGERED_NONE, player->GetGUID());
            SpellCastTargets targets;
            targets.SetUnitTarget(player);
            //TODO implement checkcast for bots
            SpellCastResult result = me->IsMounted() || CCed(me) ? SPELL_FAILED_CUSTOM_ERROR : foodspell->CheckPetCast(player);
            if (result != SPELL_CAST_OK)
            {
                foodspell->finish(false);
                delete foodspell;
                me->MonsterWhisper("I can't do it right now", player);
            }
            else
            {
                aftercastTargetGuid = player->GetGUID();
                foodspell->prepare(&targets);
                me->MonsterWhisper("Here you go...", player);
            }
            break;
        }
        case 6100: //equips change s1: send what slots we can use
        {
            subMenu = true;

            //general
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Show me your inventory", 6101, GOSSIP_ACTION_INFO_DEF + 1);
            //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Create itemset", 6101, GOSSIP_ACTION_INFO_DEF + 1);

            //weapons
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Main hand...", 6102, GOSSIP_ACTION_INFO_DEF + BOT_SLOT_MAINHAND);
            if (CanUseOffHand())
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Off-hand...", 6102, GOSSIP_ACTION_INFO_DEF + BOT_SLOT_OFFHAND);
            if (CanUseRanged())
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Ranged...", 6102, GOSSIP_ACTION_INFO_DEF + BOT_SLOT_RANGED);

            //armor
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Head...", 6102, GOSSIP_ACTION_INFO_DEF + BOT_SLOT_HEAD);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Shoulders...", 6102, GOSSIP_ACTION_INFO_DEF + BOT_SLOT_SHOULDERS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Chest...", 6102, GOSSIP_ACTION_INFO_DEF + BOT_SLOT_CHEST);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Waist...", 6102, GOSSIP_ACTION_INFO_DEF + BOT_SLOT_WAIST);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Legs...", 6102, GOSSIP_ACTION_INFO_DEF + BOT_SLOT_LEGS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Feet...", 6102, GOSSIP_ACTION_INFO_DEF + BOT_SLOT_FEET);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Wrist...", 6102, GOSSIP_ACTION_INFO_DEF + BOT_SLOT_WRIST);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Hands...", 6102, GOSSIP_ACTION_INFO_DEF + BOT_SLOT_HANDS);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Back...", 6102, GOSSIP_ACTION_INFO_DEF + BOT_SLOT_BACK);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Shirt...", 6102, GOSSIP_ACTION_INFO_DEF + BOT_SLOT_BODY);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Finger1...", 6102, GOSSIP_ACTION_INFO_DEF + BOT_SLOT_FINGER1);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Finger2...", 6102, GOSSIP_ACTION_INFO_DEF + BOT_SLOT_FINGER2);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Trinket1...", 6102, GOSSIP_ACTION_INFO_DEF + BOT_SLOT_TRINKET1);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Trinket2...", 6102, GOSSIP_ACTION_INFO_DEF + BOT_SLOT_TRINKET2);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Neck...", 6102, GOSSIP_ACTION_INFO_DEF + BOT_SLOT_NECK);

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "BACK.", 1, GOSSIP_ACTION_INFO_DEF + 1);

            break;
        }
        case 6101: //list inventory
        {
            //if (action - GOSSIP_ACTION_INFO_DEF != BOT_SLOT_NONE)
            //    break;

            int8 id = 1;
            EquipmentInfo const* einfo = sObjectMgr->GetEquipmentInfo(me->GetEntry(), id);

            for (uint8 i = 0; i != BOT_INVENTORY_SIZE; ++i)
            {
                if (uint32 itemId = master->GetBotEquip(me, i))
                {
                    std::ostringstream msg;
                    if (ItemTemplate const* proto = sObjectMgr->GetItemTemplate(itemId))
                        _AddItemTemplateLink(master, proto, msg);
                    else
                        msg << "Unknown item";
                    msg << " in slot " << uint32(i) << " (" << _GetNameForSlot(i + 1) << ')';
                    if (i < BOT_SLOT_RANGED && einfo && einfo->ItemEntry[i] == itemId)
                        msg << " |cffe6cc80|h[!standard item!]|h|r";
                    me->MonsterWhisper(msg.str().c_str(), master);
                }
            }

            break;
        }
        case 6151: //request equip item info
        {
            //GOSSIP ITEMS RESTRICTED
            //subMenu = true; //needed for return

            uint8 slot = action - (GOSSIP_ACTION_INFO_DEF + 1);
            if (uint32 itemId = master->GetBotEquip(me, slot))
            {
                std::ostringstream msg;
                if (ItemTemplate const* proto = sObjectMgr->GetItemTemplate(itemId))
                    _AddItemTemplateLink(master, proto, msg);
                else
                    msg << "Unknown";

                int8 id = 1;
                EquipmentInfo const* einfo = sObjectMgr->GetEquipmentInfo(me->GetEntry(), id);
                if (slot < BOT_SLOT_RANGED && einfo && einfo->ItemEntry[slot] == itemId)
                    msg << " |cffe6cc80|h[!standard item!]|h|r";

                me->MonsterWhisper(msg.str().c_str(), master);
            }

            //break; //no break here - return to menu
        }
        case 6102: //equips change s2: send list of equippable items
        {
            subMenu = true;

            std::set<uint32> itemList;

            //s2.1: build list
            //s2.1.1: backpack
            for (uint8 i = INVENTORY_SLOT_ITEM_START; i != INVENTORY_SLOT_ITEM_END; i++)
                if (Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
                    if (CanEquip(pItem->GetTemplate(), action - GOSSIP_ACTION_INFO_DEF) && itemList.find(pItem->GetEntry()) == itemList.end())
                        itemList.insert(pItem->GetEntry());

            //s2.1.2: other bags
            for (uint8 i = INVENTORY_SLOT_BAG_START; i != INVENTORY_SLOT_BAG_END; i++)
                if (Bag* pBag = player->GetBagByPos(i))
                    for (uint32 j = 0; j != pBag->GetBagSize(); j++)
                        if (Item* pItem = player->GetItemByPos(i, j))
                            if (CanEquip(pItem->GetTemplate(), action - GOSSIP_ACTION_INFO_DEF) && itemList.find(pItem->GetEntry()) == itemList.end())
                                itemList.insert(pItem->GetEntry());

            //s2.2: add gossips

            //s2.2.0 add current item (with return)
            uint8 slot = action - (GOSSIP_ACTION_INFO_DEF + 1);
            std::ostringstream str;
            str << "Equipped: ";
            if (uint32 itemId = master->GetBotEquip(me, slot))
            {
                if (ItemTemplate const* proto = sObjectMgr->GetItemTemplate(itemId))
                    _AddItemTemplateLink(master, proto, str);
                else
                    str << "unknown item";

                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, str.str().c_str(), 6151, action);
            }
            else
            {
                str << "nothing";
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, str.str().c_str(), 6102, action);
            }

            //s2.2.1 add unequip option if have weapon
            if (action - GOSSIP_ACTION_INFO_DEF <= BOT_SLOT_RANGED)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Use your old equipment", 6104, action);

            //s2.2.2 add unequip option if have weapon
            if (master->GetBotEquip(me, action - (GOSSIP_ACTION_INFO_DEF + 1)))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Unequip it", 6103, action);

            //s2.2.3a: add an empty submenu with info if no items are found
            if (itemList.empty())
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Hm... I have nothing to give you", 0, GOSSIP_ACTION_INFO_DEF + 1);
            }
            else
            {
                ItemTemplate const* weap;
                uint32 counter = 0;
                uint32 maxcounter = GOSSIP_MAX_MENU_ITEMS - 4; //unequip, reset, current, back
                uint32 slot = action - GOSSIP_ACTION_INFO_DEF;
                //s2.2.3b: add items as gossip options
                for (std::set<uint32>::const_iterator itr = itemList.begin(); itr != itemList.end() && counter < maxcounter; ++itr)
                {
                    weap = sObjectMgr->GetItemTemplate(*itr);
                    if (weap)
                    {
                        std::ostringstream name;
                        _AddItemTemplateLink(master, weap, name);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, name.str().c_str(), 6104 + slot, GOSSIP_ACTION_INFO_DEF + weap->ItemId);
                        ++counter;
                    }
                }
            }

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "BACK", 6100, GOSSIP_ACTION_INFO_DEF + 2);

            //TC_LOG_ERROR("entities.player", "OnGossipSelect(bot): added %u item(s) to list of %s (requester: %s)",
            //    counter, me->GetName().c_str(), player->GetName().c_str());

            break;
        }
        case 6103: //equips change s3: Unequip
        {
            if (action - GOSSIP_ACTION_INFO_DEF == BOT_SLOT_MAINHAND)
            {
                if (me->GetBotClass() == CLASS_WARRIOR || me->GetBotClass() == CLASS_DEATH_KNIGHT ||
                    me->GetBotClass() == CLASS_ROGUE || (me->GetBotClass() == CLASS_SHAMAN && isTwoHander()) ||
                    me->GetBotClass() == CLASS_PALADIN || me->GetBotClass() == CLASS_HUNTER)
                {
                    me->MonsterSay("What, with my bare hands? No way", LANG_UNIVERSAL, player);
                    break;
                }
            }
            else if (action - GOSSIP_ACTION_INFO_DEF == BOT_SLOT_OFFHAND)
            {
                if (me->GetBotClass() == CLASS_ROGUE)
                {
                    me->MonsterSay("No. Never", LANG_UNIVERSAL, player);
                    break;
                }
            }
            else if (action - GOSSIP_ACTION_INFO_DEF == BOT_SLOT_RANGED)
            {
                if (me->GetBotClass() == CLASS_HUNTER)
                {
                    me->MonsterSay("Yeah, very funny...", LANG_UNIVERSAL, player);
                    break;
                }
            }

            if (Unequip(action - (GOSSIP_ACTION_INFO_DEF + 1)))
                me->MonsterSay("Hm...", LANG_UNIVERSAL, player);
            break;
        }
        case 6104: //equips change s4a: reset equipment
        {
            if (ResetEquipment(action - (GOSSIP_ACTION_INFO_DEF + 1)))
                me->MonsterSay(RAND<char*>("Fine", "Very well", "Alright", "Yeah"), LANG_UNIVERSAL, player);
            break;
        }
        //equips change s4b: Equip item
        case 6105: //1 - 1 main hand
        case 6106: //2 - 1 off hand
        case 6107: //3 - 1 main hand
        case 6108: //4 - 1 head
        case 6109: //5 - 1 shoulders
        case 6110: //6 - 1 chest
        case 6111: //7 - 1 waist
        case 6112: //8 - 1 legs
        case 6113: //9 - 1 feet
        case 6114: //10 - 1 wrist
        case 6115: //11 - 1 hands
        case 6116: //12 - 1 back
        case 6117: //13 - 1 body
        case 6118: //14 - 1 finger
        case 6119: //15 - 1 finger
        case 6120: //16 - 1 trinket
        case 6121: //17 - 1 trinket
        case 6122: //18 - 1 neck
        //6105-6150 for items
        {
            if (Equip(action - GOSSIP_ACTION_INFO_DEF, sender - 6105))
                me->MonsterSay(RAND<char*>("Fine", "Very well", "Alright", "Yeah", "Good", "Okay"), LANG_UNIVERSAL, player);
            break;
        }
        default:
        {
            break;
        }
    }

    //if we add submenus send them else we should return
    if (subMenu)
        player->PlayerTalkClass->SendGossipMenu(GOSSIP_SERVE_MASTER, me->GetGUID());
    else
        player->CLOSE_GOSSIP_MENU();

    return true;
}
//Summons pet for bot
void bot_minion_ai::SummonBotsPet(uint32 entry)
{
    Creature* m_botsPet = me->GetBotsPet();
    if (m_botsPet)
        me->SetBotsPetDied();

    uint8 mylevel = std::min<uint8>(master->getLevel(), 85);
    uint32 originalentry = bot_pet_ai::GetPetOriginalEntry(entry);
    if (!originalentry)
    {
        //annoy master
        me->MonsterWhisper("Why am I trying to summon unknown pet!?", master);
        return;
    }
    uint32 armor = 0;
    float x(0),y(0),z(0);
    me->GetClosePoint(x, y, z, me->GetObjectSize());
    m_botsPet = me->SummonCreature(entry, x, y, z, 0, TEMPSUMMON_DEAD_DESPAWN);

    if (!m_botsPet)
    {
        me->MonsterWhisper("Failed to summon pet!", master);
        return;
    }

    //std::string name = sObjectMgr->GeneratePetName(originalentry);//voidwalker
    //if (!name.empty())
    //    m_botsPet->SetName(name);

    PreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_NPCBOT_PET_LEVELSTATS);
    stmt->setUInt32(0, originalentry);
    stmt->setUInt8(1, mylevel);
    PreparedQueryResult result = WorldDatabase.Query(stmt);
    //QueryResult result = WorldDatabase.PQuery("SELECT hp, mana, armor, str, agi, sta, inte, spi FROM `pet_levelstats` WHERE `creature_entry` = '%u' AND `level` = '%u'", originalentry, mylevel);

    if (result)
    {
        Field* fields = result->Fetch();
        uint32 hp = fields[0].GetUInt16();
        uint32 mana = fields[1].GetUInt16();
        armor = fields[2].GetUInt32();
        uint32 str = fields[3].GetUInt16();
        uint32 agi = fields[4].GetUInt16();
        uint32 sta = fields[5].GetUInt16();
        uint32 inte = fields[6].GetUInt16();
        uint32 spi = fields[7].GetUInt16();

        m_botsPet->SetCreateHealth(hp);
        m_botsPet->SetMaxHealth(hp);
        m_botsPet->SetCreateMana(mana);
        m_botsPet->SetMaxPower(POWER_MANA, mana);

        m_botsPet->SetCreateStat(STAT_STRENGTH, str);
        m_botsPet->SetCreateStat(STAT_AGILITY, agi);
        m_botsPet->SetCreateStat(STAT_STAMINA, sta);
        m_botsPet->SetCreateStat(STAT_INTELLECT, inte);
        m_botsPet->SetCreateStat(STAT_SPIRIT, spi);
    }

    m_botsPet->SetBotOwner(master);
    m_botsPet->SetCreatureOwner(me);
    m_botsPet->SetBotClass(bot_pet_ai::GetPetClass(m_botsPet));
    master->SetMinion((Minion*)m_botsPet, true);
    m_botsPet->SetUInt64Value(UNIT_FIELD_CREATEDBY, me->GetGUID());
    m_botsPet->DeleteThreatList();
    m_botsPet->AddUnitTypeMask(UNIT_MASK_MINION);
    //m_botsPet->SetLevel(master->getLevel());
    m_botsPet->AIM_Initialize();
    m_botsPet->InitBotAI(true);
    m_botsPet->setFaction(master->getFaction());
    //bot_pet_ai* petai = m_botsPet->GetBotPetAI();
    //petai->SetCreatureOwner(me);
    //petai->SetBaseArmor(armor);
    //petai->setStats(mylevel, bot_pet_ai::GetPetType(m_botsPet), true);
    m_botsPet->SetBotCommandState(COMMAND_FOLLOW, true);

    me->SetBotsPet(m_botsPet);
    m_botsPet->SendUpdateToPlayer(master);
}

uint16 bot_ai::Rand() const
{
    return urand(0, 100 + (master->GetNpcBotsCount() - 1) * 10);
}
//Used for outside checks for druid
uint8 bot_minion_ai::GetBotClassForCreature(Creature* bot)
{
    uint8 botClass = bot->GetBotClass();
    switch (botClass)
    {
        case DRUID_CAT_FORM: case DRUID_BEAR_FORM:
            return CLASS_DRUID;
        default:
            return botClass;
    }
}
//Returns pet type (maybe unneeded)
uint8 bot_pet_ai::GetPetType(Creature* pet)
{
    switch (pet->GetEntry())
    {
        case PET_VOIDWALKER:
            return PET_TYPE_VOIDWALKER;
    }
    return PET_TYPE_NONE;
}
//Returns pet's class
uint8 bot_pet_ai::GetPetClass(Creature* pet)
{
    switch (GetPetType(pet))
    {
        case PET_TYPE_IMP:
            return CLASS_MAGE;
        default:
            return CLASS_PALADIN;
    }
}
//Return entry used to summon real pets
uint32 bot_pet_ai::GetPetOriginalEntry(uint32 entry)
{
    switch (entry)
    {
        case PET_VOIDWALKER:
            return ORIGINAL_ENTRY_VOIDWALKER;
        default:
            return 0;
    }
}
//PvP trinket for minions
void bot_minion_ai::BreakCC(uint32 diff)
{
    if (pvpTrinket_cd <= diff && CCed(me, true) && (me->GetVictim() || !me->getAttackers().empty()))
    {
        temptimer = GC_Timer;
        if (doCast(me, PVPTRINKET))
        {
            pvpTrinket_cd = PVPTRINKET_CD;
            GC_Timer = temptimer;
            return;
        }
    }
}
//Returns attack range based on given range
//If mounted: 20%
//If ranged: 125%
//If master is dead: max range
float bot_ai::InitAttackRange(float origRange, bool ranged) const
{
    if (me->IsMounted())
        origRange *= 0.2f;
    else
    {
        if (ranged)
            origRange *= 1.25f;
        if (master->IsDead())
            origRange += sWorld->GetMaxVisibleDistanceOnContinents();
    }
    return origRange;
}
//Force bots to start attack anyone who tries to DAMAGE me or master
//This means that anyone who attacks party will be attacked by whole bot party (see GetTarget())
void bot_minion_ai::OnOwnerDamagedBy(Unit* attacker)
{
    if (me->GetVictim())
        return;
    if (InDuel(attacker))
        return;
    bool byspell = false, ranged = false;
    switch (GetBotClassForCreature(me))
    {
        case CLASS_DRUID:
            byspell = me->GetShapeshiftForm() == FORM_NONE ||
                me->GetShapeshiftForm() == FORM_TREE ||
                me->GetShapeshiftForm() == FORM_MOONKIN;
            ranged = byspell;
            break;
        case CLASS_PRIEST:
        case CLASS_MAGE:
        case CLASS_WARLOCK:
            byspell = true;
            ranged = true;
            break;
        case CLASS_SHAMAN:
            byspell = true;
            ranged = !isTwoHander();
            break;
        case CLASS_HUNTER:
            ranged = true;
            break;
        default:
            break;
    }
    float maxdist = InitAttackRange(float(master->GetBotFollowDist()), ranged);//use increased range
    if (!attacker->IsWithinDist(me, maxdist))
        return;
    if (!CanBotAttack(attacker, byspell))
        return;

    m_botCommandState = COMMAND_ABANDON;//reset AttackStart()
    me->Attack(attacker, !ranged);
}

bool bot_minion_ai::CanUseOffHand() const
{
    //warriot can wield any offhand with titan's grip
    if (me->GetBotClass() == CLASS_WARRIOR && me->getLevel() >= 60)
        return true;

    //no offhand: check we are using one-handed weapon in main hand
    if (!me->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 1))
    {
        if (ItemTemplate const* proto = sObjectMgr->GetItemTemplate(me->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 0)))
            if (proto->Class == ITEM_CLASS_WEAPON &&
                (proto->SubClass == ITEM_SUBCLASS_WEAPON_AXE ||
                proto->SubClass == ITEM_SUBCLASS_WEAPON_DAGGER ||
                proto->SubClass == ITEM_SUBCLASS_WEAPON_FIST_WEAPON ||
                proto->SubClass == ITEM_SUBCLASS_WEAPON_MACE ||
                proto->SubClass == ITEM_SUBCLASS_WEAPON_SWORD))
                return true;
    }
    else if (ItemTemplate const* proto = sObjectMgr->GetItemTemplate(me->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 1)))
    {
        //Now we have something in off-hand
        //1 check if it is one-handed weapon
        if (proto->Class == ITEM_CLASS_WEAPON &&
            (proto->SubClass == ITEM_SUBCLASS_WEAPON_AXE ||
            proto->SubClass == ITEM_SUBCLASS_WEAPON_DAGGER ||
            proto->SubClass == ITEM_SUBCLASS_WEAPON_FIST_WEAPON ||
            proto->SubClass == ITEM_SUBCLASS_WEAPON_MACE ||
            proto->SubClass == ITEM_SUBCLASS_WEAPON_SWORD))
            return true;
        //2 check of it is a shield
        if (proto->Class == ITEM_CLASS_ARMOR && proto->SubClass == ITEM_SUBCLASS_ARMOR_SHIELD)
            return true;
        //3 check of it is a 'held in off-hand' item
        if (proto->InventoryType == INVTYPE_HOLDABLE)
            return true;
    }

    //NO
    return false;   
}

bool bot_minion_ai::CanUseRanged() const
{
    return (me->GetBotClass() == CLASS_HUNTER/* || me->GetBotClass() == CLASS_ROGUE*/);
    //return (me->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 2) != 0);
}

bool bot_minion_ai::CanEquip(ItemTemplate const* item, uint8 slot) const
{
    //prevent reequipping same items
    if (item->ItemId == master->GetBotEquip(me, slot - 1))
        return false;

    //prevent equipping items with random properties (temp)
    if (item->RandomProperty > 0 || item->RandomSuffix > 0)
        //if (item->Quality >= ITEM_QUALITY_RARE)
            return false;

    //level requirements
    if (me->getLevel() < item->RequiredLevel)
        return false;

    //class requirements
    if (!(item->AllowableClass & (1<<(me->GetBotClass()-1))))
        return false;

    //skip race requirements

    if (item->Class == ITEM_CLASS_WEAPON)
    {
        if (slot > BOT_SLOT_RANGED)
            return false;

        if (slot == BOT_SLOT_OFFHAND && item->SubClass == ITEM_SUBCLASS_WEAPON_POLEARM)
            return false;

        if (slot == BOT_SLOT_OFFHAND && me->GetBotClass() != CLASS_WARRIOR &&
            me->GetBotClass() != CLASS_ROGUE && me->GetBotClass() != CLASS_HUNTER &&
            me->GetBotClass() != CLASS_SHAMAN && me->GetBotClass() != CLASS_DEATH_KNIGHT)
            return false;

        if (slot == BOT_SLOT_MAINHAND && item->SubClass != ITEM_SUBCLASS_WEAPON_DAGGER &&
            me->GetBotClass() == CLASS_ROGUE)
            return false;

        if (/*proto->InventoryType == INVTYPE_THROWN ||*/
            item->InventoryType == INVTYPE_RANGED ||
            item->InventoryType == INVTYPE_RANGEDRIGHT)
        {
            return (slot == BOT_SLOT_RANGED && CanUseRanged());
        }
        else if (item->InventoryType == INVTYPE_2HWEAPON)
        {
            if (me->GetBotClass() == CLASS_WARRIOR && me->getLevel() >= 60)
                return true;

            if ((me->GetBotClass() == CLASS_MAGE || me->GetBotClass() == CLASS_PRIEST ||
                me->GetBotClass() == CLASS_WARLOCK || me->GetBotClass() == CLASS_DRUID) &&
                item->SubClass != ITEM_SUBCLASS_WEAPON_STAFF)
                return false;

            return (slot == BOT_SLOT_MAINHAND);
        }
        else if (item->InventoryType == INVTYPE_WEAPON ||
            item->InventoryType == INVTYPE_WEAPONMAINHAND ||
            item->InventoryType == INVTYPE_WEAPONOFFHAND)
        {
            return (slot == BOT_SLOT_MAINHAND ||
                (slot == BOT_SLOT_OFFHAND && me->GetBotClass() != CLASS_PALADIN && CanUseOffHand()));
        }
    }
    else if (item->Class == ITEM_CLASS_ARMOR)
    {
        switch (item->InventoryType)
        {
            case INVTYPE_HEAD:
                if (slot != BOT_SLOT_HEAD)
                    return false;
                break;
            case INVTYPE_SHOULDERS:
                if (slot != BOT_SLOT_SHOULDERS)
                    return false;
                break;
            case INVTYPE_BODY:
                if (slot != BOT_SLOT_BODY)
                    return false;
                break;
            case INVTYPE_CHEST:
            case INVTYPE_ROBE:
                if (slot != BOT_SLOT_CHEST)
                    return false;
                break;
            case INVTYPE_WAIST:
                if (slot != BOT_SLOT_WAIST)
                    return false;
                break;
            case INVTYPE_LEGS:
                if (slot != BOT_SLOT_LEGS)
                    return false;
                break;
            case INVTYPE_FEET:
                if (slot != BOT_SLOT_FEET)
                    return false;
                break;
            case INVTYPE_WRISTS:
                if (slot != BOT_SLOT_WRIST)
                    return false;
                break;
            case INVTYPE_HANDS:
                if (slot != BOT_SLOT_HANDS)
                    return false;
                break;
            case INVTYPE_FINGER:
                if (slot != BOT_SLOT_FINGER1 && slot != BOT_SLOT_FINGER2)
                    return false;
                break;
            case INVTYPE_TRINKET:
                if (slot != BOT_SLOT_TRINKET1 && slot != BOT_SLOT_TRINKET2)
                    return false;
                break;
            case INVTYPE_NECK:
                if (slot != BOT_SLOT_NECK)
                    return false;
                break;
            case INVTYPE_CLOAK:
                if (slot != BOT_SLOT_BACK)
                    return false;
                break;
            case INVTYPE_HOLDABLE:
            case INVTYPE_SHIELD:
                if (slot != BOT_SLOT_OFFHAND)
                    return false;
                break;
            case INVTYPE_RELIC:
                if (slot != BOT_SLOT_RANGED)
                    return false;
                break;
            default:
                break;
        }

        if (item->SubClass == ITEM_SUBCLASS_ARMOR_SHIELD)
        {
            if (slot == BOT_SLOT_OFFHAND)
            {
                return CanUseOffHand() &&
                    (me->GetBotClass() == CLASS_WARRIOR ||
                    me->GetBotClass() == CLASS_PALADIN ||
                    me->GetBotClass() == CLASS_SHAMAN);
            }
        }
        else if (item->SubClass == ITEM_SUBCLASS_ARMOR_PLATE)
        {
            return (me->getLevel() >= 40 &&
                (me->GetBotClass() == CLASS_WARRIOR ||
                me->GetBotClass() == CLASS_DEATH_KNIGHT ||
                me->GetBotClass() == CLASS_PALADIN));
        }
        else if (item->SubClass == ITEM_SUBCLASS_ARMOR_MAIL)
        {
            if (me->GetBotClass() == CLASS_WARRIOR ||
                me->GetBotClass() == CLASS_DEATH_KNIGHT ||
                me->GetBotClass() == CLASS_PALADIN)
                return true;

            return (me->getLevel() >= 40 &&
                (me->GetBotClass() == CLASS_SHAMAN ||
                me->GetBotClass() == CLASS_HUNTER));
        }
        else if (item->SubClass == ITEM_SUBCLASS_ARMOR_LEATHER)
        {
            return (me->GetBotClass() != CLASS_WARLOCK &&
                me->GetBotClass() != CLASS_MAGE &&
                me->GetBotClass() != CLASS_PRIEST);
        }
        else if (item->SubClass == ITEM_SUBCLASS_ARMOR_CLOTH)
        {
            return true;
        }
        else if (item->SubClass == ITEM_SUBCLASS_ARMOR_MISCELLANEOUS)
        {
            if (item->InventoryType == INVTYPE_FEET && slot == BOT_SLOT_FEET)
                return true;
            if (item->InventoryType == INVTYPE_BODY && slot == BOT_SLOT_BODY)
                return true;
            if (item->InventoryType == INVTYPE_FINGER &&
                (slot == BOT_SLOT_FINGER1 || slot == BOT_SLOT_FINGER2))
                return true;
            if (item->InventoryType == INVTYPE_TRINKET &&
                (slot == BOT_SLOT_TRINKET1 || slot == BOT_SLOT_TRINKET2))
                return true;
            if (item->InventoryType == INVTYPE_NECK && slot == BOT_SLOT_NECK)
                return true;
            if (item->InventoryType == INVTYPE_HOLDABLE && slot == BOT_SLOT_OFFHAND)
                return true;
        }
        else if (item->SubClass == ITEM_SUBCLASS_ARMOR_LIBRAM)
            return me->GetBotClass() == CLASS_PALADIN && slot == BOT_SLOT_RANGED;
        else if (item->SubClass == ITEM_SUBCLASS_ARMOR_IDOL)
            return me->GetBotClass() == CLASS_DRUID && slot == BOT_SLOT_RANGED;
        else if (item->SubClass == ITEM_SUBCLASS_ARMOR_TOTEM)
            return me->GetBotClass() == CLASS_SHAMAN && slot == BOT_SLOT_RANGED;
        else if (item->SubClass == ITEM_SUBCLASS_ARMOR_SIGIL)
            return me->GetBotClass() == CLASS_DEATH_KNIGHT && slot == BOT_SLOT_RANGED;
    }

    return false;
}

bool bot_minion_ai::Unequip(uint8 slot)
{
    if (slot < BOT_SLOT_RANGED)
    {
        int8 id = 1;
        EquipmentInfo const* einfo = sObjectMgr->GetEquipmentInfo(me->GetEntry(), id);
        uint32 itemId = me->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + slot);
        if (!einfo || einfo->ItemEntry[slot] != me->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + slot))
        {
            ItemPosCountVec dest;
            uint32 no_space = 0;
            InventoryResult msg = master->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itemId, 1, &no_space);
            if (msg != EQUIP_ERR_OK)
            {
                master->SendEquipError(msg, NULL, NULL, itemId);
                return false;
            }
            Item* pItem = master->StoreNewItem(dest, itemId, true, 0);
            if (!pItem)
            {
                master->SendEquipError(EQUIP_ERR_ITEM_NOT_FOUND, NULL, NULL);
                return false;
            }
            master->SendNewItem(pItem, 1, true, false, false);
        }

        //only for non-standard items
        if (!(einfo && einfo->ItemEntry[slot] == itemId))
            RemoveItemBonuses(slot);

        me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + slot, 0);
        me->SetAttackTime(WeaponAttackType(slot), 2000); //without weapon
        master->UpdateBotEquips(me, slot, 0);

        if (slot + 1 == BOT_SLOT_OFFHAND)
        {
            if (me->CanDualWield())
                me->SetCanDualWield(false);
            if (!(me->GetCreatureTemplate()->flags_extra & CREATURE_FLAG_EXTRA_NO_BLOCK))
                const_cast<CreatureTemplate*>(me->GetCreatureTemplate())->flags_extra |= CREATURE_FLAG_EXTRA_NO_BLOCK;
        }
    }
    else
    {
        uint32 itemId = master->GetBotEquip(me, slot);
        if (itemId == 0)
            return true; //nothing to unequip

        ItemPosCountVec dest;
        uint32 no_space = 0;
        InventoryResult msg = master->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itemId, 1, &no_space);
        if (msg != EQUIP_ERR_OK)
        {
            master->SendEquipError(msg, NULL, NULL, itemId);
            return false;
        }
        Item* pItem = master->StoreNewItem(dest, itemId, true, 0);
        if (!pItem)
        {
            master->SendEquipError(EQUIP_ERR_ITEM_NOT_FOUND, NULL, NULL);
            return false;
        }
        master->SendNewItem(pItem, 1, true, false, false);

        RemoveItemBonuses(slot);

        master->UpdateBotEquips(me, slot, 0);
    }

    return true;
}

bool bot_minion_ai::Equip(uint32 itemId, uint8 slot)
{
    if (master->GetBotEquip(me, slot) == itemId)
        return false;

    if (!itemId)
        return false;

    ItemTemplate const* proto = sObjectMgr->GetItemTemplate(itemId);
    if (!proto)
        return false;

    if (slot < BOT_SLOT_RANGED)
    {
        int8 id = 1;
        EquipmentInfo const* einfo = sObjectMgr->GetEquipmentInfo(me->GetEntry(), id);

        if (me->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + slot))
        {
            if (!Unequip(slot))
            {
                me->MonsterSay("You have no space for my current item", LANG_UNIVERSAL, master);
                return false;
            }
        }

        if (!einfo || einfo->ItemEntry[slot] != itemId)
        {
            if (!master->HasItemCount(itemId, 1))
            {
                
                std::ostringstream msg;
                msg << "Cannot find ";
                _AddItemTemplateLink(master, proto, msg);
                msg << " (id: " << uint32(itemId) << ")!";
                me->MonsterWhisper(msg.str().c_str(), master);
                return false;
            }

            master->DestroyItemCount(itemId, 1, true);
        }

        me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + slot, itemId);
        me->SetAttackTime(WeaponAttackType(slot), einfo && einfo->ItemEntry[slot] == itemId ? me->GetCreatureTemplate()->baseattacktime : proto->Delay); //set attack speed
        master->UpdateBotEquips(me, slot, itemId);

        //only for non-standard items
        if (!(einfo && einfo->ItemEntry[slot] == itemId))
            ApplyItemBonuses(slot);

        if (slot + 1 == BOT_SLOT_OFFHAND)
        {
            if (proto->Class == ITEM_CLASS_WEAPON)
            {
                if (!me->CanDualWield())
                    me->SetCanDualWield(true);
            }
            else if (proto->Class == ITEM_CLASS_ARMOR && proto->SubClass == ITEM_SUBCLASS_ARMOR_SHIELD)
            {
                if (me->GetCreatureTemplate()->flags_extra & CREATURE_FLAG_EXTRA_NO_BLOCK)
                    const_cast<CreatureTemplate*>(me->GetCreatureTemplate())->flags_extra &= ~CREATURE_FLAG_EXTRA_NO_BLOCK;
            }
        }
        else if (slot + 1 == BOT_SLOT_MAINHAND && proto->InventoryType == INVTYPE_2HWEAPON &&
            !(me->GetBotClass() == CLASS_WARRIOR && me->getLevel() >= 60))
        {
            //if have offhand unequip it
            if (me->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 1))
                Unequip(BOT_SLOT_OFFHAND - 1);
        }
    }
    else
    {
        if (!Unequip(slot))
        {
            me->MonsterSay("You have no space for my current item", LANG_UNIVERSAL, master);
            return false;
        }

        if (!master->HasItemCount(itemId, 1))
        {
            std::ostringstream msg;
            msg << "Cannot find ";
            _AddItemTemplateLink(master, proto, msg);
            msg << " (id: " << uint32(itemId) << ")!";
            me->MonsterWhisper(msg.str().c_str(), master);
            return false;
        }

        master->DestroyItemCount(itemId, 1, true);

        master->UpdateBotEquips(me, slot, itemId);
        ApplyItemBonuses(slot);
    }

    return true;
}

bool bot_minion_ai::ResetEquipment(uint8 slot)
{
    if (slot < BOT_SLOT_RANGED)
    {
        int8 id = 1;
        EquipmentInfo const* einfo = sObjectMgr->GetEquipmentInfo(me->GetEntry(), id);
        if (!einfo || !einfo->ItemEntry[slot])
            return Unequip(slot);

        if (slot + 1 == BOT_SLOT_MAINHAND && !(me->GetBotClass() == CLASS_WARRIOR && me->getLevel() >= 60))
        {
            if (ItemTemplate const* proto = sObjectMgr->GetItemTemplate(einfo->ItemEntry[slot]))
            {
                if (proto->Class == ITEM_CLASS_WEAPON &&
                    (proto->SubClass == ITEM_SUBCLASS_WEAPON_AXE2 || proto->SubClass == ITEM_SUBCLASS_WEAPON_MACE2 ||
                    proto->SubClass == ITEM_SUBCLASS_WEAPON_SWORD2 || proto->SubClass == ITEM_SUBCLASS_WEAPON_POLEARM ||
                    proto->SubClass == ITEM_SUBCLASS_WEAPON_STAFF || proto->SubClass == ITEM_SUBCLASS_WEAPON_SPEAR))
                {
                    if (!Unequip(BOT_SLOT_OFFHAND - 1))
                        return false;
                }
            }
        }

        return Equip(einfo->ItemEntry[slot], slot);
    }

    return Unequip(slot);
}

void bot_minion_ai::ApplyItemBonuses(uint8 slot)
{
    //ensurance to set zeros
    RemoveItemBonuses(slot);

    uint32 itemId = master->GetBotEquip(me, slot);
    if (!itemId)
        return;

    ItemTemplate const* proto = sObjectMgr->GetItemTemplate(itemId);
    if (!proto)
        return;

    ScalingStatDistributionEntry const* ssd = proto->ScalingStatDistribution ? sScalingStatDistributionStore.LookupEntry(proto->ScalingStatDistribution) : NULL;

    uint32 ssd_level = me->getLevel();
    if (ssd && ssd_level > ssd->MaxLevel)
        ssd_level = ssd->MaxLevel;

    ScalingStatValuesEntry const* ssv = ssd ? sScalingStatValuesStore.LookupEntry(ssd_level) : NULL;

    for (uint8 i = 0; i != MAX_ITEM_PROTO_STATS; ++i)
    {
        uint32 statType = 0;
        int32  val = 0;
        if (ssd && ssv)
        {
            if (ssd->StatMod[i] < 0)
                continue;
            statType = ssd->StatMod[i];
            val = (ssv->GetStatMultiplier(proto->InventoryType) * ssd->Modifier[i]) / 10000;
        }
        else
        {
            statType = proto->ItemStat[i].ItemStatType;
            val = proto->ItemStat[i].ItemStatValue;
        }

        if (val == 0)
            continue;

        _stats[slot][statType] += val;
    }

    for (uint8 i = 0; i != MAX_ITEM_SPELLS; ++i)
    {
        _Spell const& spellData = proto->Spells[i];
        if (!spellData.SpellId)
            continue;
        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellData.SpellId);
        if (!spellInfo)
            continue;

        if (spellInfo->HasEffect(SPELL_EFFECT_ADD_EXTRA_ATTACKS))
            continue;

        for (uint8 j = 0; j != MAX_SPELL_EFFECTS; ++j)
        {
            if (spellInfo->Effects[j].ApplyAuraName == SPELL_AURA_MOD_SHIELD_BLOCKVALUE)
                _stats[slot][ITEM_MOD_BLOCK_VALUE] += spellInfo->Effects[j].CalcValue();
        }

        if (spellData.SpellTrigger != ITEM_SPELLTRIGGER_CHANCE_ON_HIT)
            continue;

        bool exists = false;
        for (uint8 j = 0; j != MAX_BOT_CTC_SPELLS; ++j)
        {
            if (_ctc[j].first == spellInfo->Id)
            {
                exists = true;
                break;
            }
        }
        if (exists)
            continue;

        for (uint8 j = 0; j != MAX_BOT_CTC_SPELLS; ++j)
        {
            if (_ctc[j].first == 0)
            {
                _ctc[j].first = spellInfo->Id;
                _ctc[j].second = 0; //reset cd
                break;
            }
        }
    }

    if (proto->Class == ITEM_CLASS_WEAPON)
        _stats[slot][BOT_ITEM_MOD_DAMAGE] = proto->DamageMin;
    else if (proto->Class == ITEM_CLASS_ARMOR)
        _stats[slot][BOT_ITEM_MOD_ARMOR] = proto->Armor;

    shouldUpdateStats = true;
}

void bot_minion_ai::RemoveItemBonuses(uint8 slot)
{
    uint32 itemId = master->GetBotEquip(me, slot);
    if (!itemId)
        return;

    ItemTemplate const* proto = sObjectMgr->GetItemTemplate(itemId);
    if (!proto)
        return;

    for (uint8 i = 0; i != MAX_BOT_ITEM_MOD; ++i)
        _stats[slot][i] = 0;

    for (uint8 i = 0; i != MAX_ITEM_SPELLS; ++i)
    {
        if (uint32 spellId = proto->Spells[i].SpellId)
        {
            for (uint8 j = 0; j != MAX_BOT_CTC_SPELLS; ++j)
            {
                if (_ctc[j].first == spellId)
                {
                    _ctc[j].first = 0;
                    break;
                }
            }
        }
    }

    if (proto->Class == ITEM_CLASS_WEAPON)
        _stats[slot][BOT_ITEM_MOD_DAMAGE] = 0;
    else if (proto->Class == ITEM_CLASS_ARMOR)
        _stats[slot][BOT_ITEM_MOD_ARMOR] = 0;

    shouldUpdateStats = true;
}

char const* bot_minion_ai::_GetNameForSlot(uint8 slot) const
{
    switch (slot)
    {
        case BOT_SLOT_MAINHAND:
            return "Main Hand Weapon";
        case BOT_SLOT_OFFHAND:
            return "Offhand Weapon";
        case BOT_SLOT_RANGED:
            return "Ranged Weapon";
        case BOT_SLOT_HEAD:
            return "Head";
        case BOT_SLOT_SHOULDERS:
            return "Shoulders";
        case BOT_SLOT_CHEST:
            return "Chest";
        case BOT_SLOT_WAIST:
            return "Waist";
        case BOT_SLOT_LEGS:
            return "Legs";
        case BOT_SLOT_FEET:
            return "Feet";
        case BOT_SLOT_WRIST:
            return "Wrist";
        case BOT_SLOT_HANDS:
            return "Hands";
        case BOT_SLOT_BACK:
            return "Back";
        case BOT_SLOT_BODY:
            return "Body";
        case BOT_SLOT_FINGER1:
            return "Finger1";
        case BOT_SLOT_FINGER2:
            return "Finger2";
        case BOT_SLOT_TRINKET1:
            return "Trinket1";
        case BOT_SLOT_TRINKET2:
            return "Trinket2";
        case BOT_SLOT_NECK:
            return "Neck";
        default:
            return "Unknown";
    }
}

void bot_ai::_AddItemTemplateLink(Player* forPlayer, ItemTemplate const* item, std::ostringstream &str) const
{
    //color
    str << "|c";
    switch (item->Quality)
    {
        case ITEM_QUALITY_POOR:     str << "ff9d9d9d"; break;  //GREY
        case ITEM_QUALITY_NORMAL:   str << "ffffffff"; break;  //WHITE
        case ITEM_QUALITY_UNCOMMON: str << "ff1eff00"; break;  //GREEN
        case ITEM_QUALITY_RARE:     str << "ff0070dd"; break;  //BLUE
        case ITEM_QUALITY_EPIC:     str << "ffa335ee"; break;  //PURPLE
        case ITEM_QUALITY_LEGENDARY:str << "ffff8000"; break;  //ORANGE
        case ITEM_QUALITY_ARTIFACT: str << "ffe6cc80"; break;  //LIGHT YELLOW
        case ITEM_QUALITY_HEIRLOOM: str << "ffe6cc80"; break;  //LIGHT YELLOW
        default:                    str << "ff000000"; break;  //UNK BLACK
    }
    str << "|Hitem:" << uint32(item->ItemId) << ":";

    //permanent enchantment, 3 gems, 4 unknowns, reporter_level (9)
    str << "0:0:0:0:0:0:0:0:0";

    //name
    std::string name = item->Name1;
    _LocalizeItem(forPlayer, name, item->ItemId);
    str << "|h[" << name << "]|h|r";

    //max in stack
    if (item->BuyCount > 1)
        str<< "|cff009900x" << item->BuyCount << ".|r";
    else
        str << "|cff009900.|r";
}

void bot_ai::_AddItemLink(Player* forPlayer, Item const* item, std::ostringstream &str) const
{
    ItemTemplate const* proto = item->GetTemplate();

    //color
    str << "|c";
    switch (proto->Quality)
    {
        case ITEM_QUALITY_POOR:     str << "ff9d9d9d"; break;  //GREY
        case ITEM_QUALITY_NORMAL:   str << "ffffffff"; break;  //WHITE
        case ITEM_QUALITY_UNCOMMON: str << "ff1eff00"; break;  //GREEN
        case ITEM_QUALITY_RARE:     str << "ff0070dd"; break;  //BLUE
        case ITEM_QUALITY_EPIC:     str << "ffa335ee"; break;  //PURPLE
        case ITEM_QUALITY_LEGENDARY:str << "ffff8000"; break;  //ORANGE
        case ITEM_QUALITY_ARTIFACT: str << "ffe6cc80"; break;  //LIGHT YELLOW
        case ITEM_QUALITY_HEIRLOOM: str << "ffe6cc80"; break;  //LIGHT YELLOW
        default:                    str << "ff000000"; break;  //UNK BLACK
    }
    str << "|Hitem:" << proto->ItemId << ":";

    //permanent enchantment
    str << item->GetEnchantmentId(PERM_ENCHANTMENT_SLOT) << ":";

    //gems (3)
    uint32 g1 = 0, g2 = 0, g3 = 0;
    for (uint32 slot = SOCK_ENCHANTMENT_SLOT; slot != SOCK_ENCHANTMENT_SLOT + MAX_GEM_SOCKETS; ++slot)
    {
        uint32 eId = item->GetEnchantmentId(EnchantmentSlot(slot));
        if (!eId)
            continue;

        SpellItemEnchantmentEntry const* enchant = sSpellItemEnchantmentStore.LookupEntry(eId);
        if (!enchant) continue;

        switch (slot - SOCK_ENCHANTMENT_SLOT)
        {
            case 1: g1 = enchant->GemID;    break;
            case 2: g2 = enchant->GemID;    break;
            case 3: g3 = enchant->GemID;    break;
        }
    }
    str << g1 << ":" << g2 << ":" << g3 << ":";

    //temp enchantment, bonus enchantment and prismatic enchantment (3 + 1 unk)
    str << "0:0:0:0:";

    //reporter level
    str << "0";

    //name
    std::string name = proto->Name1;
    _LocalizeItem(forPlayer, name, proto->ItemId);
    str << "|h[" << name << "]|h|r";

    //quantity
    if (item->GetCount() > 1)
        str << "x" << item->GetCount() << ' ';
}

void bot_ai::_AddQuestLink(Player* forPlayer, Quest const* quest, std::ostringstream &str) const
{
    std::string questTitle = quest->GetTitle();
    _LocalizeQuest(forPlayer, questTitle, quest->GetQuestId());
    str << "|cFFEFFD00|Hquest:" << quest->GetQuestId() << ':' << quest->GetQuestLevel() << "|h[" << questTitle << "]|h|r";
}

void bot_ai::_AddWeaponSkillLink(Player* forPlayer, SpellInfo const* spellInfo, std::ostringstream &str, uint32 skillid) const
{
    uint32 loc = forPlayer->GetSession()->GetSessionDbcLocale();
    str << "|cff00ffff|Hspell:" << spellInfo->Id << "|h[" << spellInfo->SpellName[loc] << " : " << master->GetSkillValue(skillid) << " /" << master->GetMaxSkillValue(skillid) << "]|h|r";
}

void bot_ai::_AddSpellLink(Player* forPlayer, SpellInfo const* spellInfo, std::ostringstream &str) const
{
    uint32 loc = forPlayer->GetSession()->GetSessionDbcLocale();
    str << "|cffffffff|Hspell:" << spellInfo->Id << "|h[" << spellInfo->SpellName[loc] << "]|h|r";
}

void bot_ai::_AddProfessionLink(Player* forPlayer, SpellInfo const* spellInfo, std::ostringstream &str, uint32 skillId) const
{
    ASSERT(master->HasSkill(skillId));
    // |cffffd000|Htrade:4037:1:150:1:6AAAAAAAAAAAAAAAAAAAAAAOAADAAAAAAAAAAAAAAAAIAAAAAAAAA|h[Engineering]|h|r
    uint32 loc = forPlayer->GetSession()->GetSessionDbcLocale();
    SkillLineEntry const* skillInfo = sSkillLineStore.LookupEntry(skillId);
    if (skillInfo)
    {
        uint32 curValue = master->GetPureSkillValue(skillId);
        uint32 maxValue  = master->GetPureMaxSkillValue(skillId);
        str << "|cffffd000|Htrade:" << spellInfo->Id << ':' << curValue << ':' << maxValue << ':' << master->GetGUIDLow() << ":6AAAAAAAAAAAAAAAAAAAAAAOAADAAAAAAAAAAAAAAAAIAAAAAAAAA" << "|h[" << skillInfo->name[loc] << "]|h|r";
    }
}
//Localization
void bot_ai::_LocalizeItem(Player* forPlayer, std::string &itemName, uint32 entry) const
{
    uint32 loc = forPlayer->GetSession()->GetSessionDbLocaleIndex();
    std::wstring wnamepart;

    ItemLocale const* itemInfo = sObjectMgr->GetItemLocale(entry);
    if (!itemInfo)
        return;

    if (itemInfo->Name.size() > loc && !itemInfo->Name[loc].empty())
    {
        const std::string name = itemInfo->Name[loc];
        if (Utf8FitTo(name, wnamepart))
            itemName = name;
    }
}

void bot_ai::_LocalizeQuest(Player* forPlayer, std::string &questTitle, uint32 entry) const
{
    uint32 loc = forPlayer->GetSession()->GetSessionDbLocaleIndex();
    std::wstring wnamepart;

    QuestLocale const* questInfo = sObjectMgr->GetQuestLocale(entry);
    if (!questInfo)
        return;

    if (questInfo->Title.size() > loc && !questInfo->Title[loc].empty())
    {
        const std::string title = questInfo->Title[loc];
        if (Utf8FitTo(title, wnamepart))
            questTitle = title;
    }
}

void bot_ai::_LocalizeCreature(Player* forPlayer, std::string &creatureName, uint32 entry) const
{
    uint32 loc = forPlayer->GetSession()->GetSessionDbLocaleIndex();
    std::wstring wnamepart;

    CreatureLocale const* creatureInfo = sObjectMgr->GetCreatureLocale(entry);
    if (!creatureInfo)
        return;

    if (creatureInfo->Name.size() > loc && !creatureInfo->Name[loc].empty())
    {
        const std::string title = creatureInfo->Name[loc];
        if (Utf8FitTo(title, wnamepart))
            creatureName = title;
    }
}

void bot_ai::_LocalizeGameObject(Player* forPlayer, std::string &gameobjectName, uint32 entry) const
{
    uint32 loc = forPlayer->GetSession()->GetSessionDbLocaleIndex();
    std::wstring wnamepart;

    GameObjectLocale const* gameObjectInfo = sObjectMgr->GetGameObjectLocale(entry);
    if (!gameObjectInfo)
        return;

    if (gameObjectInfo->Name.size() > loc && !gameObjectInfo->Name[loc].empty())
    {
        const std::string title = gameObjectInfo->Name[loc];
        if (Utf8FitTo(title, wnamepart))
            gameobjectName = title;
    }
}
