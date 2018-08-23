/*
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
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

#include "script_helper.h"
#include "Creature.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "Vehicle.h"

enum eZone_TheMaelstrom
{
    NPC_WYVERN_45004 = 45004,
    NPC_WYVERN_45024 = 45024,
    NPC_AGGRA_45027 = 45027,
    NPC_AGGRA_45028 = 45028,

    QUEST_MAELSTROM = 27123,

    SPELL_NATURE_CHANNELING = 28892,
    SPELL_EJECT_PASSENGER_2 = 62539,
    SPELL_FORCECAST_TELEPORT_DEEPHOLM = 84093,
    SPELL_CAMERA_1 = 84364,
    SPELL_DEEPHOLM_INTRO_TAXI = 84101, // modus is never ending?? player can't move anywhere if taxifly ending..
    SPELL_FORCECAST_AGGRA_PING_INTERNAL = 96123,
    
    SPELL_SEE_QUEST_INVIS_1 = 84021,
    SPELL_SEE_QUEST_INVIS_2 = 83821,
    SPELL_SEE_QUEST_INVIS_10A = 80852,
    SPELL_SEE_QUEST_INVIS_10B = 81032,
    SPELL_SEE_QUEST_INVIS_11 = 83322,
    SPELL_SEE_QUEST_INVIS_12 = 83322,
    SPELL_SEE_QUEST_INVIS_13A = 83364,
    SPELL_SEE_QUEST_INVIS_13B = 84019,
    SPELL_SEE_QUEST_INVIS_14 = 84035,
    SPELL_SEE_QUEST_INVIS_15 = 83671,
    SPELL_SEE_QUEST_INVIS_16 = 84117,
    SPELL_SEE_QUEST_INVIS_17 = 84704,
    SPELL_SEE_QUEST_INVIS_18 = 84707,
    SPELL_SEE_QUEST_INVIS_19 = 84955,
};

// player
class player_zone_maelstrom : public PlayerScript
{
public:
    player_zone_maelstrom() : PlayerScript("player_zone_maelstrom") { }

    void OnQuestRemove(Player* player, uint32 questId) override
    {
        switch (questId)
        {
        case 0:
            break;
        }
    }

    void OnQuestStatusChange(Player* player, uint32 questId, QuestStatus status) override
    {
        switch (questId)
        {
        case 0:
            break;
        }
    }

    void OnMapChanged(Player* player) 
    { 
        if (player->GetMapId() == 646 && player->GetZoneId() == 5042 && player->GetAreaId() == 5303)
            if (player->GetQuestStatus(QUEST_MAELSTROM) == QUEST_STATUS_COMPLETE)
                if (player->GetPositionZ() > 675.0F)
                {
                    player->SetDisableGravity(true);
                    player->AddAura(SPELL_SEE_QUEST_INVIS_12, player);
                    player->AddAura(SPELL_SEE_QUEST_INVIS_16, player);
                    player->AddAura(SPELL_SEE_QUEST_INVIS_19, player);
                    if (Creature* wyvern = player->SummonCreature(NPC_WYVERN_45024, 1040.91f, 544.69f, 681.94f, 3.98f))
                    {
                        player->EnterVehicle(wyvern, 1);
                        if (Creature* aggra = player->SummonCreature(NPC_AGGRA_45027, wyvern->GetPosition(), TEMPSUMMON_MANUAL_DESPAWN, 0))
                            aggra->EnterVehicle(wyvern, 0);
                    }
                }
    }
};

// 45042
class npc_thrall_45042 : public CreatureScript
{
public:
    npc_thrall_45042() : CreatureScript("npc_thrall_45042") { }

    struct npc_thrall_45042AI : public ScriptedAI
    {
        npc_thrall_45042AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset() override
        {
            me->CastSpell(me, 28892, true);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_thrall_45042AI(creature);
    }
};

// 45004
class npc_wyvern_45004 : public CreatureScript
{
public:
    npc_wyvern_45004() : CreatureScript("npc_wyvern_45004") { }

    struct npc_wyvern_45004AI : public VehicleAI
    {
        npc_wyvern_45004AI(Creature* creature) : VehicleAI(creature) {}

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_aggraGUID;
        uint64   m_wyvernGUID;

        void EnterEvadeMode() {}

        void Reset()
        {
            m_playerGUID = 0;
            m_aggraGUID = 0;
            m_wyvernGUID = 0;
            if (Creature* wyv = me->FindNearestCreature(45005, 25.0f))
            {
                m_wyvernGUID = wyv->GetGUID();
                me->SetOrientation(wyv->GetOrientation());
                wyv->DespawnOrUnsummon(100);
            }
        }

        void PassengerBoarded(Unit* who, int8 seatId, bool apply)
        {
            if (apply)
            {
                if (Player* player = who->ToPlayer())
                {
                    m_playerGUID = player->GetGUID();
                    if (seatId == 0)
                    {
                        player->ChangeSeat(2);
                    }
                    else if (seatId == 2)
                    {
                        if (Creature* aggra = player->SummonCreature(NPC_AGGRA_45028, me->GetPosition(), TEMPSUMMON_MANUAL_DESPAWN, 0))
                            aggra->EnterVehicle(me, 0);
                    }
                }
                else if (Creature* aggra = who->ToCreature())
                {
                    m_aggraGUID = aggra->GetGUID();
                    m_events.ScheduleEvent(EVENT_MOVEMENT_START, 200);
                }
            }
            else
            {
                if (Creature* aggra = who->ToCreature())
                    aggra->DespawnOrUnsummon();
                else if (Player* player = who->ToPlayer())
                    if (seatId == 2)
                        me->DespawnOrUnsummon(10);
            }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == WAYPOINT_MOTION_TYPE)
                switch (id)
                {
                case 2:
                    if (Creature* aggra = sObjectAccessor->GetCreature(*me, m_aggraGUID))
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                            aggra->AI()->Talk(0, player);
                    break;
                case 4:
                    if (Creature* aggra = sObjectAccessor->GetCreature(*me, m_aggraGUID))
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                            aggra->AI()->Talk(1, player);
                    break;
                case 7:
                    if (Creature* aggra = sObjectAccessor->GetCreature(*me, m_aggraGUID))
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                            aggra->AI()->Talk(2, player);
                    break;
                case 10:
                    if (Creature* aggra = sObjectAccessor->GetCreature(*me, m_aggraGUID))
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                            aggra->AI()->Talk(3, player);
                    break;
                case 11:
                    me->CastSpell(me, SPELL_FORCECAST_TELEPORT_DEEPHOLM, true); // teleport passenger 2
                    break;
                }
        }

        void UpdateAI(uint32 diff) override
        {
            VehicleAI::UpdateAI(diff);
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_MOVEMENT_START:
                    me->CastSpell(me, SPELL_CAMERA_1, true);
                    me->SetSpeed(MOVE_RUN, 3.2f);
                    me->GetMotionMaster()->MovePath(4500401, false);
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_wyvern_45004AI(creature);
    }
};

// 45024
class npc_wyvern_45024 : public CreatureScript
{
public:
    npc_wyvern_45024() : CreatureScript("npc_wyvern_45024") { }

    struct npc_wyvern_45024AI : public VehicleAI
    {
        npc_wyvern_45024AI(Creature* creature) : VehicleAI(creature) {}

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_aggraGUID;
        uint64   m_wyvernGUID;
        bool     m_waypointStarted;

        void EnterEvadeMode() {}

        void Reset()
        {
            m_playerGUID = 0;
            m_aggraGUID = 0;
            m_wyvernGUID = 0;
            m_waypointStarted = false;
        }

        void IsSummonedBy(Unit* summoner) override 
        { 
            if (Player* player = summoner->ToPlayer())
                m_playerGUID = player->GetGUID();
        }

        void PassengerBoarded(Unit* who, int8 seatId, bool apply)
        {
            if (apply)
            {
                if (Player* player = who->ToPlayer())
                    m_playerGUID = player->GetGUID();
                else if (Creature* aggra = who->ToCreature())
                {
                    m_aggraGUID = aggra->GetGUID();
                    m_events.ScheduleEvent(EVENT_MOVEMENT_START, 200);
                }
            }
            else
            {
                if (Player* player = who->ToPlayer())
                    m_events.ScheduleEvent(EVENT_EXIT_VEHICLE, 7000);
                else if (Creature* aggra = who->ToCreature())
                    aggra->DespawnOrUnsummon();
            }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == WAYPOINT_MOTION_TYPE)
                switch (id)
                {
                case 1:
                    if (Creature* aggra = sObjectAccessor->GetCreature(*me, m_aggraGUID))
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                            aggra->AI()->Talk(1, player);
                    break;
                case 2:
                    if (Creature* aggra = sObjectAccessor->GetCreature(*me, m_aggraGUID))
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                            aggra->AI()->Talk(2, player);
                    break;
                case 3:
                    if (Creature* aggra = sObjectAccessor->GetCreature(*me, m_aggraGUID))
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                            aggra->AI()->Talk(3, player);
                    break;
                case 4:
                    if (Creature* aggra = sObjectAccessor->GetCreature(*me, m_aggraGUID))
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                            aggra->AI()->Talk(4, player);
                    break;
                case 5:
                    if (Creature* aggra = sObjectAccessor->GetCreature(*me, m_aggraGUID))
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                            aggra->AI()->Talk(5, player);
                    break;
                case 6:
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                    {

                        player->SetDisableGravity(false);
                        player->ExitVehicle();
                    }
                    break;
                }
        }

        void UpdateAI(uint32 diff) override
        {
            VehicleAI::UpdateAI(diff);
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_MOVEMENT_START:
                {
                    if (Vehicle* wyvern = me->GetVehicleKit())
                        if (wyvern->GetAvailableSeatCount())
                        {
                            me->DespawnOrUnsummon(10);
                            break;
                        }

                    if (Creature* aggra = sObjectAccessor->GetCreature(*me, m_aggraGUID))
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                            aggra->AI()->Talk(0, player);

                    m_waypointStarted = true;
                    me->SetSpeed(MOVE_RUN, 2.5f);
                    me->SetSpeed(MOVE_WALK, 2.5f);
                    me->GetMotionMaster()->MovePath(4502401, false);
                    break;
                }
                case EVENT_EXIT_VEHICLE:
                {
                    if (Creature* aggra = sObjectAccessor->GetCreature(*me, m_aggraGUID))
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                            aggra->AI()->Talk(6, player);
                    m_events.ScheduleEvent(EVENT_DESPAWN_PART_00, 7000);
                    break;
                }
                case EVENT_DESPAWN_PART_00:
                {
                    if (Creature* aggra = sObjectAccessor->GetCreature(*me, m_aggraGUID))
                        aggra->ExitVehicle();
                    me->DespawnOrUnsummon(10);
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_wyvern_45024AI(creature);
    }
};


void AddSC_zone_the_maelstrom()
{
    new player_zone_maelstrom();
    new npc_thrall_45042();
    new npc_wyvern_45004();
    new npc_wyvern_45024();


}
