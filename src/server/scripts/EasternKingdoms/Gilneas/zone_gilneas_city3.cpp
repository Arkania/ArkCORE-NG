/*
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
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

#include "script_helper.h"
#include "ScriptPCH.h"
#include "Unit.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "ScriptedFollowerAI.h"
#include "Vehicle.h"
#include "GameObject.h"
#include "GameObjectAI.h"
#include "CreatureGroups.h"
#include "Transport.h"
#include "TransportMgr.h"

#include "ObjectMgr.h"
#include "ScriptMgr.h"

enum eBattleForGilneas
{
    QUEST_RUTTHERAN = 14434,
    QUEST_ENDGAME = 26706,

    NPC_FORSAKEN_CROSSBOWMAN = 38210,
    NPC_LORNA_CROWLEY = 38426,
    NPC_DARK_RANGER_ELITE = 38464,
    NPC_LADY_SYLVANAS_WINDRUNNER = 38469,
    NPC_TOBIAS_MISTMANTLE = 38507,
    NPC_LADY_SYLVANAS_WINDRUNNER_38530 = 38530,
    NPC_GENERAL_WARHOWL = 38533,
    NPC_HIGH_EXECUTOR_CRENSHAW = 38537,
    NPC_KRENNAN_ARANAS = 38553,
    NPC_FORSAKEN_GENERAL = 38617,
    NPC_FORSAKEN_SERGANT = 38618,
    NPC_GUNSHIP_GRUNT = 42141,
    NPC_LORNA_CRAWLEY_43566 = 43566,
    NPC_WORGEN_WARRIOR = 43651,
    NPC_GILNEAN_SHARPSHOOTER = 43703,
    NPC_HIPPOGRYPH = 43747,
    NPC_TOBIAS_MISTMANTLE_43749 = 43749,
    NPC_GILNEAS_VEHICLE_ROPE = 43793,

    GO_WORGEN_GUNSHIP = 203428,
    GO_ROPE = 204428,

    SPELL_GILNEAS_MILITIA_SHOOT = 6660,
    SPELL_CLEAVE = 15496,
    SPELL_FOR_GILNEAS = 81790,
};

// phase 262144 ending with quest 24904, then phase 190 (2097152) is active.. starting with quest 24902 

enum eQuest24902
{
    ACTION_SYLVANAS_START = 501,
};

// 38507
class npc_tobias_mistmantle_38507 : public CreatureScript
{
public:
    npc_tobias_mistmantle_38507() : CreatureScript("npc_tobias_mistmantle_38507") { }

    enum eNpc
    {
        EVENT_MOVEMENT_START_PATH_1 = 301,
        EVENT_MOVEMENT_START_PATH_2,
        EVENT_MOVEMENT_START_PATH_3,
        EVENT_MOVEMENT_START_PATH_4,
        EVENT_MOVEMENT_START_PATH_5,
        EVENT_MOVEMENT_START_PATH_6,
        EVENT_MOVEMENT_START_SYLVANAS_AI,
        EVENT_WAIT_FOR_PLAYER_1,
        EVENT_WAIT_FOR_PLAYER_2,
        EVENT_WAIT_FOR_PLAYER_3,
        EVENT_WAIT_FOR_PLAYER_4,
        EVENT_WAIT_FOR_OUTSIDE_EVENT,
        EVENT_WAIT_FOR_OUTSIDE_EVENT1,
    };

    struct npc_tobias_mistmantle_38507AI : public ScriptedAI
    {
        npc_tobias_mistmantle_38507AI(Creature* pCreature) : ScriptedAI(pCreature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_sylvanasGUID;
        uint64   m_warhowlGUID;
        uint64   m_crenshawGUID;
        uint32   m_eventPhase;

        void Reset() override
        {
            m_playerGUID = 0;
            m_eventPhase = 0;
            m_sylvanasGUID = 0;
            m_warhowlGUID = 0;
            m_crenshawGUID = 0;
        }

        void IsSummonedBy(Unit* summoner) override
        {
            m_playerGUID = summoner->GetGUID();
            m_eventPhase = 1;
            m_events.ScheduleEvent(EVENT_WAIT_FOR_PLAYER_1, 3000);
        }

        void JustSummoned(Creature* summon) override
        {
            summon->SetWalk(true);
            switch (summon->GetEntry())
            {
            case NPC_LADY_SYLVANAS_WINDRUNNER_38530:
                m_sylvanasGUID = summon->GetGUID();
                me->SetFacingToObject(summon);
                summon->AI()->SetGUID(me->GetGUID(), me->GetEntry());
                summon->AI()->SetGUID(m_playerGUID, PLAYER_GUID);
                summon->AI()->DoAction(ACTION_SYLVANAS_START);
                summon->GetMotionMaster()->MovePoint(2005, -1600.11f, 1518.04f, 29.24f);
                break;
            case NPC_GENERAL_WARHOWL:
                m_warhowlGUID = summon->GetGUID();
                summon->GetMotionMaster()->MovePoint(2006, -1593.35f, 1531.32f, 29.24f);
                break;
            case NPC_HIGH_EXECUTOR_CRENSHAW:
                m_crenshawGUID = summon->GetGUID();
                summon->GetMotionMaster()->MovePoint(2007, -1587.55f, 1519.32f, 29.24f);
                break;
            }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            switch (type)
            {
            case WAYPOINT_MOTION_TYPE:
            {
                if (m_eventPhase == 1 && id == 0)
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(0, player);
                }
                else if (m_eventPhase == 1 && id == 1)
                    m_events.ScheduleEvent(EVENT_MOVEMENT_START_PATH_1, 1000);
                else if (m_eventPhase == 2 && id == 0)
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(1, player);
                }
                else if (m_eventPhase == 2 && id == 1)
                    m_events.ScheduleEvent(EVENT_WAIT_FOR_PLAYER_2, 1000); // on open gate
                else if (m_eventPhase == 3 && id == 3)
                    m_events.ScheduleEvent(EVENT_WAIT_FOR_PLAYER_3, 1000); // on wall 1
                else if (m_eventPhase == 4 && id == 5)
                    m_events.ScheduleEvent(EVENT_WAIT_FOR_OUTSIDE_EVENT, 1000);
                else if (m_eventPhase == 5 && id == 23)
                    m_events.ScheduleEvent(EVENT_WAIT_FOR_PLAYER_4, 1000); // inside water
                break;
            }
            case EFFECT_MOTION_TYPE: // jump
            {
                if (m_eventPhase == 1 && id == 2001)
                    m_events.ScheduleEvent(EVENT_MOVEMENT_START_PATH_2, 1000);
                else if (m_eventPhase == 3 && id == 2003)
                    m_events.ScheduleEvent(EVENT_MOVEMENT_START_PATH_4, 1000);
                else if (m_eventPhase == 5 && id == 2004)
                {
                    me->SetFacingTo(5.6f);
                    m_events.ScheduleEvent(EVENT_MOVEMENT_START_PATH_6, 10);
                    m_events.ScheduleEvent(EVENT_MOVEMENT_START_SYLVANAS_AI, 1000);
                }
                break;
            }
            }
        }

        void EnterEvadeMode() {};

        uint64 GetGUID(int32 id) const override
        {
            switch (id)
            {
            case NPC_TOBIAS_MISTMANTLE:
                return me->GetGUID();
            case NPC_LADY_SYLVANAS_WINDRUNNER_38530:
                return m_sylvanasGUID;
            case NPC_GENERAL_WARHOWL:
                return m_warhowlGUID;
            case NPC_HIGH_EXECUTOR_CRENSHAW:
                return m_crenshawGUID;
            case PLAYER_GUID:
                return m_playerGUID;
            }
            return 0;
        }

        void UpdateAI(uint32 diff)
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_WAIT_FOR_PLAYER_1:
                {
                    if (IsPlayerNear(20.0f))
                        me->GetMotionMaster()->MovePath(3850701, false);
                    else
                        m_events.ScheduleEvent(EVENT_WAIT_FOR_PLAYER_1, 1000);
                    break;
                }
                case EVENT_MOVEMENT_START_PATH_1:
                {
                    me->GetMotionMaster()->MoveJump(-1601.925f, 1607.654f, 20.11606f, 20.0f, 20.0f, 2001);
                    break;
                }
                case EVENT_MOVEMENT_START_PATH_2:
                {
                    m_eventPhase = 2;
                    me->GetMotionMaster()->MovePath(3850702, false);
                    break;
                }
                case EVENT_WAIT_FOR_PLAYER_2:
                {
                    if (IsPlayerNear(8.0f))
                    {
                        m_eventPhase = 3;
                        me->GetMotionMaster()->MovePath(3850703, false);
                    }
                    else
                        m_events.ScheduleEvent(EVENT_WAIT_FOR_PLAYER_2, 1000);
                    break;
                }
                case EVENT_WAIT_FOR_PLAYER_3:
                {
                    if (IsPlayerNear(8.0f))
                        me->GetMotionMaster()->MoveJump(-1548.65f, 1618.41f, 23.1788f, 20.0f, 5.0f, 2003);
                    else
                        m_events.ScheduleEvent(EVENT_WAIT_FOR_PLAYER_3, 1000);
                    break;
                }
                case EVENT_MOVEMENT_START_PATH_4:
                {
                    m_eventPhase = 4;
                    me->GetMotionMaster()->MovePath(3850704, false);
                    break;
                }
                case EVENT_WAIT_FOR_OUTSIDE_EVENT:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        if (Creature* general = me->FindNearestCreature(NPC_FORSAKEN_GENERAL, 25.0f))
                            general->AI()->Talk(0, player);
                    m_events.ScheduleEvent(EVENT_WAIT_FOR_OUTSIDE_EVENT1, 6000);
                    break;
                }
                case EVENT_WAIT_FOR_OUTSIDE_EVENT1:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(2, player);
                    m_events.ScheduleEvent(EVENT_MOVEMENT_START_PATH_5, 6000);
                    break;
                }
                case EVENT_MOVEMENT_START_PATH_5:
                {
                    m_eventPhase = 5;
                    me->GetMotionMaster()->MovePath(3850705, false);
                    break;
                }
                case EVENT_WAIT_FOR_PLAYER_4:
                {
                    if (IsPlayerNear(8.0f))
                    {
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                            Talk(3, player);
                        me->GetMotionMaster()->MoveJump(-1614.5f, 1533.9f, 27.26f, 20.0f, 5.0f, 2004);
                    }
                    else
                        m_events.ScheduleEvent(EVENT_WAIT_FOR_PLAYER_4, 1000);
                    break;
                }
                case EVENT_MOVEMENT_START_PATH_6:
                {
                    me->SetSwim(true);
                    me->GetMotionMaster()->MovePoint(2008, -1613.95f, 1536.012f, 27.4f);
                    break;
                }
                case EVENT_MOVEMENT_START_SYLVANAS_AI:
                {
                    // there are several summon spell, but all have the summoner position as spawnpoint.. 72476, 72239, 72236, 72238, 72245
                    me->SummonCreature(NPC_GENERAL_WARHOWL, -1566.053f, 1557.191f, 29.36808f, 4.273f, TEMPSUMMON_TIMED_DESPAWN, 180000);
                    me->SummonCreature(NPC_LADY_SYLVANAS_WINDRUNNER_38530, -1567.477f, 1554.569f, 29.36808f, 0.88f, TEMPSUMMON_TIMED_DESPAWN, 180000);
                    me->SummonCreature(NPC_HIGH_EXECUTOR_CRENSHAW, -1566.795f, 1555.300f, 29.36808f, 3.275f, TEMPSUMMON_TIMED_DESPAWN, 180000);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

        bool IsPlayerNear(float range)
        {
            if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                if (player->GetDistance2d(me) < range)
                    return true;
            return false;
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_tobias_mistmantle_38507AI(pCreature);
    }
};

// 38530
class npc_lady_sylvanas_windrunner_38530 : public CreatureScript
{
public:
    npc_lady_sylvanas_windrunner_38530() : CreatureScript("npc_lady_sylvanas_windrunner_38530") { }

    enum eNpc
    {
        EVENT_START_TALK = 401,
        EVENT_TALK_2,
        EVENT_TALK_3,
        EVENT_TALK_4,
        EVENT_TALK_5,
        EVENT_TALK_6,
        EVENT_TALK_7,
        EVENT_TALK_8,
        EVENT_END,
        EVENT_DESPAWN_WARHOWL,
        EVENT_DESPAWN,
    };

    struct npc_lady_sylvanas_windrunner_38530AI : public ScriptedAI
    {
        npc_lady_sylvanas_windrunner_38530AI(Creature* pCreature) : ScriptedAI(pCreature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_tobiasGUID;
        uint64   m_sylvanasGUID;
        uint64   m_warhowlGUID;
        uint64   m_crenshawGUID;

        void Reset() override
        {
            m_playerGUID = 0;
            m_tobiasGUID = 0;
            m_sylvanasGUID = 0;
            m_warhowlGUID = 0;
            m_crenshawGUID = 0;
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (summoner->GetEntry() == NPC_TOBIAS_MISTMANTLE)
                m_tobiasGUID = summoner->GetGUID();
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == POINT_MOTION_TYPE)
                if (id == 2005)
                {
                    me->SetFacingTo(5.6f);
                    m_events.ScheduleEvent(EVENT_START_TALK, 1000);
                }
        }

        void EnterEvadeMode() {};

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case PLAYER_GUID:
                m_playerGUID = guid;
                break;
            case NPC_TOBIAS_MISTMANTLE:
                m_tobiasGUID = guid;
                break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_TALK:
                {
                    if (Creature* tobias = sObjectAccessor->GetCreature(*me, m_tobiasGUID))
                    {
                        m_playerGUID = tobias->AI()->GetGUID(PLAYER_GUID);
                        m_warhowlGUID = tobias->AI()->GetGUID(NPC_GENERAL_WARHOWL);
                        m_crenshawGUID = tobias->AI()->GetGUID(NPC_HIGH_EXECUTOR_CRENSHAW);
                    }
                    if (Creature* warhowl = sObjectAccessor->GetCreature(*me, m_warhowlGUID))
                        warhowl->AI()->Talk(0);
                    m_events.ScheduleEvent(EVENT_TALK_2, 10000);
                    break;
                }
                case EVENT_TALK_2:
                {
                    if (Creature* warhowl = sObjectAccessor->GetCreature(*me, m_warhowlGUID))
                        me->SetFacingToObject(warhowl);
                    Talk(0);
                    m_events.ScheduleEvent(EVENT_TALK_3, 8000);
                    break;
                }
                case EVENT_TALK_3:
                {
                    if (Creature* warhowl = sObjectAccessor->GetCreature(*me, m_warhowlGUID))
                        warhowl->AI()->Talk(1);
                    m_events.ScheduleEvent(EVENT_TALK_4, 11000);
                    break;
                }
                case EVENT_TALK_4:
                {
                    Talk(1);
                    m_events.ScheduleEvent(EVENT_TALK_5, 14000);
                    break;
                }
                case EVENT_TALK_5:
                {
                    if (Creature* warhowl = sObjectAccessor->GetCreature(*me, m_warhowlGUID))
                        warhowl->AI()->Talk(2);
                    m_events.ScheduleEvent(EVENT_TALK_6, 8000);
                    break;
                }
                case EVENT_TALK_6:
                {
                    if (Creature* warhowl = sObjectAccessor->GetCreature(*me, m_warhowlGUID))
                        warhowl->GetMotionMaster()->MovePoint(2010, -1566.053f, 1557.191f, 29.36808f);
                    Talk(2);
                    m_events.ScheduleEvent(EVENT_DESPAWN_WARHOWL, 8000);
                    m_events.ScheduleEvent(EVENT_TALK_7, 5000);
                    break;
                }
                case EVENT_TALK_7:
                {
                    if (Creature* crenshaw = sObjectAccessor->GetCreature(*me, m_crenshawGUID))
                    {
                        crenshaw->AI()->Talk(0);
                        me->SetFacingToObject(crenshaw);
                    }
                    m_events.ScheduleEvent(EVENT_TALK_8, 10000);
                    break;
                }
                case EVENT_TALK_8:
                {
                    Talk(3);
                    m_events.ScheduleEvent(EVENT_END, 8000);
                    break;
                }
                case EVENT_END:
                {
                    if (Creature* crenshaw = sObjectAccessor->GetCreature(*me, m_crenshawGUID))
                        crenshaw->GetMotionMaster()->MovePoint(2010, -1566.053f, 1557.191f, 29.36808f);
                    me->GetMotionMaster()->MovePoint(2010, -1566.053f, 1557.191f, 29.36808f);
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        player->KilledMonsterCredit(38530);
                    m_events.ScheduleEvent(EVENT_DESPAWN, 8000);
                    break;
                }
                case EVENT_DESPAWN_WARHOWL:
                {
                    if (Creature* warhowl = sObjectAccessor->GetCreature(*me, m_warhowlGUID))
                        warhowl->DespawnOrUnsummon(10);
                    break;
                }
                case EVENT_DESPAWN:
                {
                    if (Creature* crenshaw = sObjectAccessor->GetCreature(*me, m_crenshawGUID))
                        crenshaw->DespawnOrUnsummon(10);
                    if (Creature* tobias = sObjectAccessor->GetCreature(*me, m_tobiasGUID))
                        tobias->DespawnOrUnsummon(10);
                    me->DespawnOrUnsummon(10);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_lady_sylvanas_windrunner_38530AI(pCreature);
    }
};

// phase 2097152 is only for quest 24902, now the phase 524288 is active, startig with quest 24903

class npc_captured_riding_bat_38540 : public CreatureScript
{
public:
    npc_captured_riding_bat_38540() : CreatureScript("npc_captured_riding_bat_38540") { }

    enum eNpc
    {
        EVENT_START_WORK_AREA = 201,
        EVENT_TIMEOUT,
    };

    struct npc_captured_riding_bat_38540AI : public VehicleAI
    {
        npc_captured_riding_bat_38540AI(Creature* creature) : VehicleAI(creature) {}

        EventMap m_events;
        uint8    m_gamePhase;

        void AttackStart(Unit* /*who*/) {}
        void EnterCombat(Unit* /*who*/) {}
        void EnterEvadeMode() {}

        void Reset()
        {
            m_events.Reset();
            m_gamePhase = 0;
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == WAYPOINT_MOTION_TYPE)
                if (m_gamePhase == 1 && id == 3)
                {
                    m_events.ScheduleEvent(EVENT_START_WORK_AREA, 10);
                    m_events.ScheduleEvent(EVENT_TIMEOUT, 120000);
                }
                else if (m_gamePhase == 3 && id == 3)
                {
                    if (Vehicle* bat = me->GetVehicleKit())
                        bat->RemoveAllPassengers();
                    me->DespawnOrUnsummon(10);
                }
        }

        void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply)
        {
            if (apply)
            {
                if (who->GetTypeId() == TYPEID_PLAYER)
                    if (who->ToPlayer()->GetQuestStatus(24920) != QUEST_STATUS_INCOMPLETE)
                    {
                        me->GetVehicleKit()->RemoveAllPassengers();
                        return;
                    }
                me->SetCanFly(true);
                me->SetDisableGravity(true);
                me->SetSpeed(MOVE_FLIGHT, 6.0f);
                me->GetMotionMaster()->MovePath(3854001, false);
                m_gamePhase = 1;
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
                case EVENT_START_WORK_AREA:
                {
                    me->SetSpeed(MOVE_FLIGHT, 4.0f);
                    m_gamePhase = 2;
                    me->GetMotionMaster()->MovePath(3854002, true);
                    break;
                }
                case EVENT_TIMEOUT:
                {
                    m_gamePhase = 3;
                    me->SetSpeed(MOVE_FLIGHT, 6.0f);
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MovePath(3854003, false);
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_captured_riding_bat_38540AI(creature);
    }
};

// 72849
class spell_fly_back_72849 : public SpellScriptLoader
{
public:
    spell_fly_back_72849() : SpellScriptLoader("spell_fly_back_72849") { }

    class spell_fly_back_72849_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_fly_back_72849_SpellScript);

        void HandleDummy(SpellEffIndex /*effindex*/)
        {
            if (Unit* caster = GetCaster())
                if (Creature* bat = caster->ToCreature())
                {
                    bat->SetSpeed(MOVE_FLIGHT, 6.0f);
                    bat->GetMotionMaster()->MovePath(3854003, false);
                }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_fly_back_72849_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_fly_back_72849_SpellScript();
    }
};

// 72247
class spell_iron_bomb_72247 : public SpellScriptLoader
{
public:
    spell_iron_bomb_72247() : SpellScriptLoader("spell_iron_bomb_72247") { }

    class IsFriendly
    {
    public:
        IsFriendly(Unit* caster) : _caster(caster) { }

        bool operator()(WorldObject* object) const
        {
            if (Unit* unit = object->ToUnit())
                return _caster->IsFriendlyTo(unit);
            return true;
        }

    private:
        Unit* _caster;
    };

    class spell_iron_bomb_72247_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_iron_bomb_72247_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if(IsFriendly(GetCaster()));
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_iron_bomb_72247_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_iron_bomb_72247_SpellScript();
    }
};

// the endgame is in phase 4194304

enum eEndGame
{
    ACTION_30_SEC_BEFORE_FIGHT = 25663,
    ACTION_15_SEC_BEFORE_FIGHT = 25727,
    ACTION_SHIP_ON_THE_WAY = 25664,
    ACTION_START_FEIGHTING_180_SEC = 25670,
    ACTION_START_LORNA_TALK = 401,

    EVENT_MAKE_SHOWFIGHT = 301,
    EVENT_START_SHOWFIGHT,
    EVENT_IS_BRIDGE_CLEAN,
    EVENT_START_ROPE_PART,
};

// 43749
class npc_tobias_mistmantle_43749 : public CreatureScript
{
public:
    npc_tobias_mistmantle_43749() : CreatureScript("npc_tobias_mistmantle_43749") { }

    enum eNPC
    {
        EVENTS_CHECK_TALKING_WAIT = 201,
        EVENTS_CHECK_TALKING_HIPPO,
        EVENTS_GET_INITIAL_VALUES,
    };

    struct npc_tobias_mistmantle_43749AI : public ScriptedAI
    {
        npc_tobias_mistmantle_43749AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_gunshipGUID;
        uint32   m_gunshipEventId;
        std::list<uint64> m_hippoList;

        void Initialize()
        {
            m_gunshipGUID = 0;
            m_gunshipEventId = 0;
            m_events.ScheduleEvent(EVENTS_GET_INITIAL_VALUES, 1000);
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case ACTION_30_SEC_BEFORE_FIGHT:
            case ACTION_15_SEC_BEFORE_FIGHT:
                m_events.ScheduleEvent(EVENTS_CHECK_TALKING_HIPPO, 10);
                break;
            case ACTION_SHIP_ON_THE_WAY:
            case ACTION_START_FEIGHTING_180_SEC:
                m_events.ScheduleEvent(EVENTS_CHECK_TALKING_WAIT, 10);
                break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENTS_GET_INITIAL_VALUES:
                {
                    if (!m_gunshipGUID)
                        FindWorgenGunshipWorldwide();

                    if (GameObject* ship = sObjectAccessor->GetGameObject(*me, m_gunshipGUID))
                    {
                        m_gunshipGUID = ship->GetGUID();
                        ship->AI()->SetGUID(me->GetGUID(), me->GetEntry());
                        break;
                    }
                    m_events.ScheduleEvent(EVENTS_GET_INITIAL_VALUES, 1000);
                    break;
                }
                case EVENTS_CHECK_TALKING_WAIT:
                {
                    Talk(1);
                    SetHippoSpellClick(false);
                    break;
                }
                case EVENTS_CHECK_TALKING_HIPPO:
                {
                    if (CheckPlayerForQuest() && CheckIsGunshipReady())
                    {
                        SetHippoSpellClick(true);
                        Talk(0);
                    }
                    else
                    {
                        SetHippoSpellClick(false);
                        Talk(1);
                    }
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void FindNearestHippogryphs()
        {
            m_hippoList.clear();
            std::list<Creature*> hippoList = me->FindNearestCreatures(NPC_HIPPOGRYPH, 25.0f);
            for (std::list<Creature*>::iterator itr = hippoList.begin(); itr != hippoList.end(); ++itr)
                m_hippoList.push_back((*itr)->GetGUID());
        }

        void SetHippoSpellClick(bool value)
        {
            if (m_hippoList.empty())
            {
                std::list<Creature*> hippoList = me->FindNearestCreatures(NPC_HIPPOGRYPH, 15.0f);
                for (std::list<Creature*>::const_iterator itr = hippoList.begin(); itr != hippoList.end(); ++itr)
                    if (Creature* hippo = (*itr))
                        m_hippoList.push_back(hippo->GetGUID());
            }

            for (std::list<uint64>::iterator itr = m_hippoList.begin(); itr != m_hippoList.end(); ++itr)
                if (Creature* hippo = sObjectAccessor->GetCreature(*me, (*itr)))
                {
                    if (value)
                        hippo->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                    else
                        hippo->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                }
        }

        bool CheckPlayerForQuest()
        {
            std::list<Player*> playerList = me->FindNearestPlayers(25.0f);
            for (std::list<Player*>::iterator itr = playerList.begin(); itr != playerList.end(); ++itr)
                if ((*itr)->GetQuestStatus(QUEST_ENDGAME) == QUEST_STATUS_INCOMPLETE)
                    return true;
            return false;
        }

        void FindWorgenGunshipWorldwide()
        {
            TRINITY_READ_GUARD(HashMapHolder<GameObject>::LockType, *HashMapHolder<GameObject>::GetLock());
            HashMapHolder<GameObject>::MapType const& m = ObjectAccessor::GetGameObjects();
            for (HashMapHolder<GameObject>::MapType::const_iterator iter = m.begin(); iter != m.end(); ++iter)
                if (iter->second->IsInWorld() && iter->second->GetEntry() == GO_WORGEN_GUNSHIP)
                    m_gunshipGUID = iter->second->GetGUID();
        }

        bool CheckIsGunshipReady()
        {
            if (GameObject* ship = sObjectAccessor->GetGameObject(*me, m_gunshipGUID))
                if (Transport* transport = ship->ToTransport())
                {
                    uint32 count = transport->GetStaticPassengers().size();
                    return (count >= 39) ? true : false;
                }

            return false;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_tobias_mistmantle_43749AI(creature);
    }
};

// 43751
class npc_hippogryph_43751 : public CreatureScript
{
public:
    npc_hippogryph_43751() : CreatureScript("npc_hippogryph_43751") { }

    enum eNpc
    {
        EVENT_MOVEMENT_START = 201,
        EVENT_MOVE_LAST_POINT,
        EVENT_EJECT_ALL_PASSENGER,
        EVENT_JUMP_TO_LORNA,
    };

    struct npc_hippogryph_43751AI : public VehicleAI
    {
        npc_hippogryph_43751AI(Creature* creature) : VehicleAI(creature) {}

        EventMap m_events;
        uint64 m_playerGUID;
        uint64 m_lornaGUID;
        float  m_maxSpeed;

        void EnterEvadeMode() {}

        void Reset()
        {
            m_events.Reset();
            m_playerGUID = 0;
            m_lornaGUID = 0;
            m_maxSpeed = 4.9f;
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            switch (type)
            {
            case WAYPOINT_MOTION_TYPE:
            {
                if (id == 2)
                    me->SetSpeed(MOVE_RUN, m_maxSpeed);
                else if (id == 6)
                    me->SetSpeed(MOVE_RUN, 2);
                else if (id == 7)
                    m_events.ScheduleEvent(EVENT_MOVE_LAST_POINT, 10);
                break;
            }
            case POINT_MOTION_TYPE:
            {
                if (id == 1002)
                {
                    m_events.ScheduleEvent(EVENT_EJECT_ALL_PASSENGER, 10);
                }
                break;
            }
            }
        }

        void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply)
        {
            if (apply)
            {
                if (Player* player = who->ToPlayer())
                    if (player->GetQuestStatus(QUEST_ENDGAME) == QUEST_STATUS_INCOMPLETE)
                    {
                        m_events.ScheduleEvent(EVENT_MOVEMENT_START, 2500);
                        m_playerGUID = who->GetGUID();
                        return;
                    }

                m_playerGUID = 0;
                if (Vehicle* hippo = me->GetVehicleKit())
                    hippo->RemoveAllPassengers();
            }
            else
                me->DespawnOrUnsummon(1000);
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
                    me->SetCanFly(true);
                    me->SetDisableGravity(true);
                    me->SetSpeed(MOVE_RUN, 3);
                    me->GetMotionMaster()->MovePath(4375101, false);
                    break;
                }
                case EVENT_MOVE_LAST_POINT:
                {
                    FindLornaGuid();
                    if (Creature* lorna = sObjectAccessor->GetCreature(*me, m_lornaGUID))
                    {
                        Position pos = lorna->GetPosition();
                        pos.m_positionZ = me->GetPositionZ();
                        me->GetMotionMaster()->MovePoint(1002, pos);
                    }
                    break;
                }
                case EVENT_EJECT_ALL_PASSENGER:
                {
                    //if (Vehicle* hippo = me->GetVehicleKit())
                    //    hippo->RemoveAllPassengers();

                    m_events.ScheduleEvent(EVENT_JUMP_TO_LORNA, 10);
                    break;
                }
                case EVENT_JUMP_TO_LORNA:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        if (Creature* lorna = sObjectAccessor->GetCreature(*me, m_lornaGUID))
                        {
                            lorna->AI()->DoAction(ACTION_START_LORNA_TALK);
                            player->JumpTo(lorna, 0.5f);
                        }
                        else
                        {
                            player->GetMotionMaster()->MoveJump(-1472.0f, 3250.0f, 180.0f, 20.0f, 0.4f);
                        }

                    m_playerGUID = 0;
                    me->DespawnOrUnsummon(2000);
                    break;
                }
                }
            }
        }

        void FindLornaGuid()
        {
            if (Creature* lorna = sObjectAccessor->GetCreature(*me, m_lornaGUID))
                if (lorna->GetDistance2d(me) > 50.0f)
                    m_lornaGUID = 0;

            if (!m_lornaGUID)
                if (Creature* lorna = me->FindNearestCreature(NPC_LORNA_CRAWLEY_43566, 25.0f))
                    m_lornaGUID = lorna->GetGUID();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hippogryph_43751AI(creature);
    }
};

// GO 203428
class go_worgen_gunship_203428 : public GameObjectScript
{
public:
    go_worgen_gunship_203428() : GameObjectScript("go_worgen_gunship_203428") { }

    enum eObject
    {
        EVENT_CHECK_POSITIONS = 201,
    };

    struct go_worgen_gunship_203428AI : public GameObjectAI
    {
        go_worgen_gunship_203428AI(GameObject* gameobject) : GameObjectAI(gameobject) { }

        EventMap m_events;
        uint64   m_tobiasGUID;
        uint64   m_playerGUID;

        void Reset() override
        {
            m_tobiasGUID = 0;
            m_playerGUID = 0;
            m_events.RescheduleEvent(EVENT_CHECK_POSITIONS, 2500);
        }

        void EventInform(uint32 eventId)
        {
            if (Creature* tobias = sObjectAccessor->GetCreature(*go, m_tobiasGUID))
                tobias->AI()->DoAction(eventId);
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case NPC_TOBIAS_MISTMANTLE_43749:
                m_tobiasGUID = guid;
                break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_POSITIONS:
                {
                    if (!m_playerGUID)
                        if (Player* player = go->FindNearestPlayer(100.0f))
                            m_playerGUID = player->GetGUID();

                     m_events.ScheduleEvent(EVENT_CHECK_POSITIONS, 2500);
                    break;
                }
                }
            }
        }
    };

    GameObjectAI* GetAI(GameObject* gameobject) const override
    {
        return new go_worgen_gunship_203428AI(gameobject);
    }
};

// 43566
class npc_lorna_crowley_43566 : public CreatureScript
{
public:
    npc_lorna_crowley_43566() : CreatureScript("npc_lorna_crowley_43566") { }

    struct npc_lorna_crowley_43566AI : public ScriptedAI
    {
        npc_lorna_crowley_43566AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap  m_events;
        uint64    m_targetGUID;
        bool      m_doneA;
        bool      m_anim_is_started;
        std::list<Creature*>victimList;

        void Initialize()
        {
            m_anim_is_started = false;
            m_targetGUID = 0;
        }

        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
            m_doneA = false;
            if (!me->HasAura(SPELL_FOR_GILNEAS))
                me->AddAura(SPELL_FOR_GILNEAS, me);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (attacker->GetGUID() != m_targetGUID)
                m_targetGUID = attacker->GetGUID();

            switch (attacker->GetEntry())
            {
            case NPC_GUNSHIP_GRUNT:
                damage = 0;
                break;
            }
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case ACTION_START_LORNA_TALK:
                Talk(2);
                m_anim_is_started = true;
                SetRopeNotSelectableFlag(true);
                if (Transport* transport = me->GetTransport())
                    transport->EnableMovement(false);
                m_events.ScheduleEvent(EVENT_IS_BRIDGE_CLEAN, 2500);
                m_events.ScheduleEvent(EVENT_MASTER_RESET, 180000);
                break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_MASTER_RESET:
                {
                    Initialize();
                    me->DespawnOrUnsummon(10);
                    break;
                }
                case EVENT_IS_BRIDGE_CLEAN:
                {
                    uint32 count = IsBridgeClean();
                    if (count < 2 && !m_doneA)
                    {
                        m_doneA = true;
                        Talk(3);
                        m_events.ScheduleEvent(EVENT_IS_BRIDGE_CLEAN, 5000);
                        break;
                    }
                    else if (!count)
                    {
                        Talk(4);
                        SetRopeNotSelectableFlag(false);
                        m_events.ScheduleEvent(EVENT_START_ROPE_PART, 7000);
                        break;
                    }

                    m_events.ScheduleEvent(EVENT_IS_BRIDGE_CLEAN, 2500);
                    break;
                }
                case EVENT_START_ROPE_PART:
                {
                    SpawnGunshipOrcsWave2();
                    std::vector<Creature*> friendsList = FindFriendlyCreatureList();
                    std::vector<Creature*> jumpTargetList = FindJumpTargetPositions();
                    for (uint32 i = 0; i < friendsList.size(); i++)
                        friendsList[i]->JumpTo(jumpTargetList[i], 0.4f);

                    m_events.ScheduleEvent(11, 2000);
                    break;
                }
                case 11:
                {

                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        bool FindTarget()
        {
            m_targetGUID = 0;
            if (!IsPlayerInRange())
                return false;
            std::list<Creature*>m_targetList = me->FindAllUnfriendlyCreaturesInRange(40.0f);
            if (!m_targetList.empty())
            {
                Creature* m_nearestTarget = *m_targetList.begin();
                float m_nearestDistance = m_nearestTarget->GetDistance(me);
                for (std::list<Creature*>::const_iterator itr = m_targetList.begin(); itr != m_targetList.end(); ++itr)
                    if (isInSameHeight((*itr)->GetPosition()))
                    {
                        float dist2 = (*itr)->GetDistance(me);
                        if (dist2 < m_nearestDistance)
                        {
                            m_nearestTarget = (*itr);
                            m_nearestDistance = dist2;
                        }
                    }
                m_targetGUID = m_nearestTarget->GetGUID();
            }

            return (m_targetGUID) ? true : false;
        }

        bool IsPlayerInRange()
        {
            Player* player = me->FindNearestPlayer(50.0f);
            return player ? true : false;
        }

        bool isInSameHeight(Position pos)
        {
            float diff = abs(me->GetPositionZ() - pos.GetPositionZ());
            return (diff < 5) ? true : false;
        }

        uint32 IsBridgeClean()
        {
            uint32 count = 0;
            std::list<Creature*>m_targetList = me->FindAllUnfriendlyCreaturesInRange(75.0f);
            for (std::list<Creature*>::iterator itr = m_targetList.begin(); itr != m_targetList.end(); ++itr)
                if ((*itr)->GetTransOffsetZ() > 75.0f)
                    count += 1;

            return count;
        }

        void SetRopeNotSelectableFlag(bool value)
        {
            std::list<GameObject*> goList = me->FindNearestGameObjects(GO_ROPE, 30.0f); // there are 2 rope on bridge
            for (std::list<GameObject*>::const_iterator itr = goList.begin(); itr != goList.end(); ++itr)
                if (value)
                    (*itr)->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                else
                    (*itr)->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
        }

        std::vector<Creature*> FindFriendlyCreatureList()
        {
            std::vector<Creature*> rList;
            std::list<Creature*> tList = me->FindAllCreaturesInRange(12.0f);
            for (std::list<Creature*>::iterator itr = tList.begin(); itr != tList.end(); ++itr)
                if (Creature* target = (*itr))
                    if (isInSameHeight(target->GetPosition()) && target->IsAlive())
                        rList.push_back(target);

            return rList;
        }

        std::vector<Creature*> FindJumpTargetPositions()
        {
            std::vector<Creature*> rList;
            std::list<Creature*> tList = me->FindNearestCreatures(NPC_GILNEAS_VEHICLE_ROPE, 50.0f);
            for (std::list<Creature*>::iterator itr = tList.begin(); itr != tList.end(); ++itr)
                if (Creature* target = (*itr))
                    if (!isInSameHeight(target->GetPosition()))
                        rList.push_back(target);
            return rList;
        }

        void SpawnGunshipOrcsWave2()
        {
            // AddPassenger(42141, );
        }

        void AddPassenger(uint32 entry, float x, float y, float z, float o)
        {
            uint32 guid = sObjectMgr->GenerateLowGuid(HIGHGUID_UNIT);
            CreatureData& data = sObjectMgr->NewOrExistCreatureData(guid);
            data.id = entry;
            data.phaseId = 191;
            data.posX = x;
            data.posY = y;
            data.posZ = z;
            data.orientation = o;
            data.mapid = 749;

            if (Transport* transport = me->GetTransport())
                if (Creature* creature = transport->CreateNPCPassenger(guid, &data))
                {
                    creature->SetReactState(REACT_AGGRESSIVE);
                }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_lorna_crowley_43566AI(creature);
    }
};

// 43651
class npc_worgen_warrior_43651 : public CreatureScript
{
public:
    npc_worgen_warrior_43651() : CreatureScript("npc_worgen_warrior_43651") { }

    struct npc_worgen_warrior_43651AI : public ScriptedAI
    {
        npc_worgen_warrior_43651AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap  m_events;
        uint64    m_targetGUID;
        float     m_targetDistance;
        uint64    m_playerGUID;

        void Initialize()
        {
            me->SetReactState(REACT_PASSIVE);
            m_playerGUID = 0;
            m_targetGUID = 0;
            m_targetDistance = 0;
            m_events.ScheduleEvent(EVENT_START_SHOWFIGHT, 5000);
        }

        void Reset() override
        {
            DoStartNoMovement(me);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            damage = 0;
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_SHOWFIGHT:
                {
                    m_events.ScheduleEvent(EVENT_MAKE_SHOWFIGHT, 1000);
                    break;
                }
                case EVENT_MAKE_SHOWFIGHT:
                {
                    if (me->IsInCombat())
                    {
                        if (Creature* target = sObjectAccessor->GetCreature(*me, m_targetGUID))
                            if (m_targetDistance < 5.0f)
                                me->CastSpell(target, SPELL_CLEAVE);
                    }
                    else if (FindTarget())
                        if (Creature* target = sObjectAccessor->GetCreature(*me, m_targetGUID))
                            if (m_targetDistance < 5.0f)
                                me->CastSpell(target, SPELL_CLEAVE);

                    m_events.ScheduleEvent(EVENT_MAKE_SHOWFIGHT, urand(900, 1200));
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        bool FindTarget()
        {
            m_targetGUID = 0;
            if (!IsPlayerInRange())
                return false;
            std::list<Creature*>m_targetList = me->FindAllUnfriendlyCreaturesInRange(5.0f);
            if (!m_targetList.empty())
            {
                Creature* m_nearestTarget = *m_targetList.begin();
                float m_nearestDistance = m_nearestTarget->GetDistance2d(me);
                for (std::list<Creature*>::const_iterator itr = m_targetList.begin(); itr != m_targetList.end(); ++itr)
                {
                    float dist2 = (*itr)->GetDistance2d(me);
                    if (dist2 < m_nearestDistance)
                    {
                        m_nearestTarget = (*itr);
                        m_nearestDistance = dist2;
                    }
                }
                if (m_nearestDistance < 5.0f)
                    m_targetGUID = m_nearestTarget->GetGUID();
            }

            return (m_targetGUID) ? true : false;
        }

        bool IsPlayerInRange()
        {
            Player* player = me->FindNearestPlayer(50.0f);
            return player ? true : false;
        }

        bool CheckPlayer()
        {
            if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                if (player->GetDistance(me) > 20.0f)
                    m_playerGUID = 0;
            if (!m_playerGUID)
                if (Player* player = me->FindNearestPlayer(20.0f))
                    m_playerGUID = player->GetGUID();
            return (m_playerGUID) ? true : false;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_worgen_warrior_43651AI(creature);
    }
};

// 43703
class npc_gilnean_sharpshooter_43703 : public CreatureScript
{
public:
    npc_gilnean_sharpshooter_43703() : CreatureScript("npc_gilnean_sharpshooter_43703") { }

    struct npc_gilnean_sharpshooter_43703AI : public ScriptedAI
    {
        npc_gilnean_sharpshooter_43703AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap  m_events;
        uint64    m_targetGUID;
        float     m_targetDistance;
        uint64    m_playerGUID;

        void Initialize()
        {

            m_playerGUID = 0;
            m_targetGUID = 0;
            m_targetDistance = 0;
            m_events.ScheduleEvent(EVENT_START_SHOWFIGHT, 5000);
        }

        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
            DoStartNoMovement(me);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            damage = 0;
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_SHOWFIGHT:
                {
                    m_events.ScheduleEvent(EVENT_MAKE_SHOWFIGHT, 1000);
                    break;
                }
                case EVENT_MAKE_SHOWFIGHT:
                {
                    if (me->IsInCombat())
                    {
                        if (Creature* target = sObjectAccessor->GetCreature(*me, m_targetGUID))
                            if (m_targetDistance > 5.0f)
                                me->CastSpell(target, SPELL_GILNEAS_MILITIA_SHOOT);
                            else
                            {
                                me->CastSpell(target, SPELL_CLEAVE);
                                if (!target->IsInCombat())
                                    target->Attack(me, true);
                            }
                    }
                    else
                        if (FindTarget())
                            if (Creature* target = sObjectAccessor->GetCreature(*me, m_targetGUID))
                                if (m_targetDistance > 5.0f)
                                    me->CastSpell(target, SPELL_GILNEAS_MILITIA_SHOOT);
                                else
                                {
                                    me->SetReactState(REACT_AGGRESSIVE);
                                    me->CastSpell(target, SPELL_CLEAVE);
                                    if (!target->IsInCombat())
                                        target->Attack(me, true);
                                }

                    m_events.ScheduleEvent(EVENT_MAKE_SHOWFIGHT, urand(900, 1200));
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        bool FindTarget()
        {
            m_targetGUID = 0;
            if (!IsPlayerInRange())
                return false;
            std::list<Creature*>m_targetList = me->FindAllUnfriendlyCreaturesInRange(40.0f);
            if (!m_targetList.empty())
            {
                Creature* m_nearestTarget = *m_targetList.begin();
                float m_nearestDistance = m_nearestTarget->GetDistance(me);
                for (std::list<Creature*>::const_iterator itr = m_targetList.begin(); itr != m_targetList.end(); ++itr)
                    if (isInSameHeight((*itr)->GetPosition()))
                    {
                        float dist2 = (*itr)->GetDistance(me);
                        if (dist2 < m_nearestDistance)
                        {
                            m_nearestTarget = (*itr);
                            m_nearestDistance = dist2;
                        }
                    }
                if (m_nearestDistance < 40.0f)
                {
                    m_targetGUID = m_nearestTarget->GetGUID();
                    m_targetDistance = m_nearestDistance;
                }
            }

            return (m_targetGUID) ? true : false;
        }

        bool IsPlayerInRange()
        {
            Player* player = me->FindNearestPlayer(50.0f);
            return player ? true : false;
        }

        bool isInSameHeight(Position pos)
        {
            float diff = abs(me->GetPositionZ() - pos.GetPositionZ());
            return (diff < 5) ? true : false;
        }

        bool CheckPlayer()
        {
            if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                if (player->GetDistance(me) > 20.0f)
                    m_playerGUID = 0;
            if (!m_playerGUID)
                if (Player* player = me->FindNearestPlayer(20.0f))
                    m_playerGUID = player->GetGUID();
            return (m_playerGUID) ? true : false;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_gilnean_sharpshooter_43703AI(creature);
    }
};

// 42141
class npc_gunship_grunt_42141 : public CreatureScript
{
public:
    npc_gunship_grunt_42141() : CreatureScript("npc_gunship_grunt_42141") { }

    struct npc_gunship_grunt_42141AI : public ScriptedAI
    {
        npc_gunship_grunt_42141AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        Unit* m_target;
        uint64 m_playerGUID;

        void Initialize()
        {
            m_playerGUID = 0;
        }

        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
            m_target = nullptr;
            DoStartNoMovement(me);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (IsPlayerInRange() && me->GetReactState() != REACT_AGGRESSIVE)
                me->SetReactState(REACT_AGGRESSIVE);
            damage *= 2;
        }

        bool IsPlayerInRange()
        {
            Player* player = me->FindNearestPlayer(50.0f);
            return player ? true : false;
        }

        void CheckPlayer()
        {
            if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                if (player->GetDistance(me) > 20.0f)
                    m_playerGUID = 0;
            if (!m_playerGUID)
                if (Player* player = me->FindNearestPlayer(20.0f))
                    m_playerGUID = player->GetGUID();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_gunship_grunt_42141AI(creature);
    }
};

// GO 204428
class go_rope_204428 : public GameObjectScript
{
public:
    go_rope_204428() : GameObjectScript("go_rope_204428") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (Creature* target = FindRandomJumpTargetPosition(player))
            player->JumpTo(target, 0.4f); 

        return true;
    }

    Creature* FindRandomJumpTargetPosition(Player* player)
    {
        float zHeight = player->GetPositionZ() - 10.0f;
        std::vector<Creature*> rList;
        std::list<Creature*> tList = player->FindNearestCreatures(NPC_GILNEAS_VEHICLE_ROPE, 50.0f);
        for (std::list<Creature*>::iterator itr = tList.begin(); itr != tList.end(); ++itr)
            if (Creature* target = (*itr))
                if (target->GetPositionZ() < zHeight)
                    rList.push_back(target);

        return (!rList.empty()) ? rList[urand(0, rList.size() - 1)] : nullptr;
    }
};

// 43727
class npc_lorna_crowley_43727 : public CreatureScript
{
public:
    npc_lorna_crowley_43727() : CreatureScript("npc_lorna_crowley_43727") { }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        if (quest->GetQuestId() == QUEST_ENDGAME)
        {
            creature->AI()->Talk(0);
        }
        return true;
    }
};

// 36616
class npc_admiral_nightwind_36616 : public CreatureScript
{
public:
    npc_admiral_nightwind_36616() : CreatureScript("npc_admiral_nightwind_36616") { }

    bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* quest, uint32 /*opt*/)
    {
        if (quest->GetQuestId() == QUEST_RUTTHERAN)
        {
            player->RemoveAllAuras();
            player->TeleportTo(1, 8343, 801, 4, 4.19f);
        }
        return true;
    }
};

void AddSC_zone_gilneas_city3()
{
    new npc_tobias_mistmantle_38507();
    new npc_lady_sylvanas_windrunner_38530();
    new npc_captured_riding_bat_38540();
    new spell_fly_back_72849();
    new spell_iron_bomb_72247();
    new npc_tobias_mistmantle_43749();
    new npc_hippogryph_43751();
    new go_worgen_gunship_203428();
    new npc_lorna_crowley_43566();
    new npc_worgen_warrior_43651();
    new npc_gilnean_sharpshooter_43703();
    new npc_gunship_grunt_42141();
    new go_rope_204428();
    new npc_lorna_crowley_43727();
    new npc_admiral_nightwind_36616();
}

