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

#include "Creature.h"
#include "GameObjectAI.h"
#include "GameObject.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "SpellMgr.h"
#include "Vehicle.h"

enum Zone_zone_lost_isles
{
    NPC_GEARGRINDER_GIZMO = 36600,
    NPC_DOC_ZAPNOZZLE = 36608,
    NPC_GOBLIN_SURVIVOR = 34748,
    NPC_MONKEY_BUSINESS_KILL_CREDIT = 35760,
    QUEST_DONT_GO_INTO_THE_LIGHT = 14239,
    QUEST_GOBLIN_ESCAPE_PODS_F = 14001,
    QUEST_GOBLIN_ESCAPE_PODS_M = 14474,
    SPELL_QUEST_PHASE_01 = 67851,
    SPELL_COSMETIC_STATE_DEATH = 81238,
    SPELL_THERMOHYDRAULIC_FLIPPERS_VISUAL = 68256,
    SPELL_THERMOHYDRAULIC_FLIPPERS = 68258,
    SPELL_QUEST_14239_COMPLETE = 69013,
    SPELL_JUMPER_CABLES = 69022,
    SPELL_TRADE_PRINCE_CONTROLLER_AURA = 67433,
    SPELL_SUMMON_TRADE_PRINCE_GALLYWIX = 67845,
    SPELL_SUMMON_LIVE_GOBLIN_SURVIVOR = 66137,
    SPELL_SUMMONS_CONTROLLER = 66136,
    SPELL_SWIM = 37744,
    SPELL_COSMETIC_THROW_BOMB = 66142,
    SPELL_NITRO_POTASSIUM_BANANAS = 67917,
    SPELL_EXPLODING_BANANAS = 67919,
    EVENT_MASTER_RESET = 101,
    EVENT_TALK_PART_00,
    EVENT_TALK_PART_01,
    EVENT_TALK_PART_02,
    EVENT_TALK_PART_03,
    EVENT_TALK_PART_04,
    EVENT_TALK_PART_05,
    EVENT_TALK_PART_06,
    EVENT_TALK_PART_07,
    EVENT_TALK_PART_08,
    EVENT_TALK_PART_09,
    EVENT_TALK_PART_10,
};

// 36608
class npc_doc_zapnozzle_36608 : public CreatureScript
{
public:
    npc_doc_zapnozzle_36608() : CreatureScript("npc_doc_zapnozzle_36608") { }

    enum eNPC
    {
        EVENT_CHECK_PLAYER_WELCOME=901,
        EVENT_START_NEW_WELCOME,
        ACTION_PLAYER_LIFE,
    };

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/) 
    { 
        switch (quest->GetQuestId())
        {
        case QUEST_DONT_GO_INTO_THE_LIGHT:
        {
            player->RemoveAura(SPELL_COSMETIC_STATE_DEATH);
            creature->AI()->Talk(5, player);
            creature->AI()->DoAction(ACTION_PLAYER_LIFE);
            break;
        }
        }
        return false; 
    }

    struct npc_doc_zapnozzle_36608AI : public ScriptedAI
    {
        npc_doc_zapnozzle_36608AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        std::set<uint64> playerList;
        uint64 m_activePlayerForWelcome;
        uint64 m_gizmoGUID;


        void Initialize()
        {
            m_gizmoGUID=0;
        }

        void Reset() override
        {
            m_activePlayerForWelcome=0;
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
            m_events.RescheduleEvent (EVENT_CHECK_PLAYER_WELCOME, 1000);
        }

        void MoveInLineOfSight(Unit* who) override
        {
        if (Player* player = who->ToPlayer())
            if (!player->hasQuest(QUEST_DONT_GO_INTO_THE_LIGHT))
                if (player->GetQuestStatus(QUEST_DONT_GO_INTO_THE_LIGHT) == QUEST_STATE_NONE)
                {
                    if (!player->HasAura(SPELL_QUEST_PHASE_01))
                        player->CastSpell(player, SPELL_QUEST_PHASE_01, true);
                    if (!player->HasAura(SPELL_COSMETIC_STATE_DEATH))
                        player->CastSpell(player, SPELL_COSMETIC_STATE_DEATH, true);
                    if (playerList.find(player->GetGUID()) == playerList.end())
                        playerList.insert(player->GetGUID());
                }
        }

        void DoAction(int32 param) override
        {
            if (param == ACTION_PLAYER_LIFE)
            {
                m_events.ScheduleEvent(EVENT_TALK_PART_09, 5000);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_PLAYER_WELCOME:
                {
                    if (!m_activePlayerForWelcome)
                        if (playerList.size() > 0)
                        {
                            m_activePlayerForWelcome = *playerList.begin();
                            playerList.erase(m_activePlayerForWelcome);
                            m_events.ScheduleEvent(EVENT_START_NEW_WELCOME, 500);
                            m_events.ScheduleEvent(EVENT_MASTER_RESET, 120000);
                        }
                    m_events.ScheduleEvent(EVENT_CHECK_PLAYER_WELCOME, 1000);
                    break;
                }
                case EVENT_MASTER_RESET:
                {
                    m_activePlayerForWelcome = 0;
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                    break;
                }
                case EVENT_START_NEW_WELCOME:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_activePlayerForWelcome))
                        Talk(0, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_01, 5000);
                    break;
                }
                case EVENT_TALK_PART_01:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_activePlayerForWelcome))
                        Talk(1, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_02, 5000);
                    break;
                }
                case EVENT_TALK_PART_02:
                {
                    if (!m_gizmoGUID)
                        if (Creature* gizmo = me->FindNearestCreature(NPC_GEARGRINDER_GIZMO, 15.0f))
                            m_gizmoGUID = gizmo->GetGUID();

                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_activePlayerForWelcome))
                        if (Creature* gizmo = ObjectAccessor::GetCreature(*me, m_gizmoGUID))
                            gizmo->AI()->Talk(0, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_03, 5000);
                    break;
                }
                case EVENT_TALK_PART_03:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_activePlayerForWelcome))
                        Talk(2, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_04, 2000);
                    break;
                }
                case EVENT_TALK_PART_04:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_activePlayerForWelcome))
                        me->CastSpell(player, SPELL_JUMPER_CABLES, true);
                    m_events.ScheduleEvent(EVENT_TALK_PART_05, 5000);
                    break;
                }
                case EVENT_TALK_PART_05:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_activePlayerForWelcome))
                    {
                        Talk(3, player);
                        me->CastSpell(player, SPELL_JUMPER_CABLES, true);
                    }
                    m_events.ScheduleEvent(EVENT_TALK_PART_06, 5000);
                    break;
                }
                case EVENT_TALK_PART_06:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_activePlayerForWelcome))
                        me->CastSpell(player, SPELL_JUMPER_CABLES, true);
                    m_events.ScheduleEvent(EVENT_TALK_PART_07, 5000);
                    break;
                }
                case EVENT_TALK_PART_07:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_activePlayerForWelcome))
                        Talk(4, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_08, 5000);
                    break;
                }
                case EVENT_TALK_PART_08:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_activePlayerForWelcome))
                    {
                        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                        if (Quest const* quest = sObjectMgr->GetQuestTemplate(QUEST_DONT_GO_INTO_THE_LIGHT))
                            player->AddQuestAndCheckCompletion(quest, me);
                    }
                    break;
                }
                case EVENT_TALK_PART_09:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_activePlayerForWelcome))
                        Talk(6, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_10, 5000);
                    break;
                }
                case EVENT_TALK_PART_10:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_activePlayerForWelcome))
                    {
                        me->RemoveAura(SPELL_COSMETIC_STATE_DEATH);
                    }
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                    m_activePlayerForWelcome = 0;
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_doc_zapnozzle_36608AI(creature);
    }
};

// 36600
class npc_geargrinder_gizmo_36600 : public CreatureScript
{
public:
    npc_geargrinder_gizmo_36600() : CreatureScript("npc_geargrinder_gizmo_36600") { }

    enum eNPC
    {
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case QUEST_GOBLIN_ESCAPE_PODS_F:
        case QUEST_GOBLIN_ESCAPE_PODS_M:
        {
            player->CastSpell(player, SPELL_THERMOHYDRAULIC_FLIPPERS_VISUAL, true);
            player->CastSpell(player, SPELL_THERMOHYDRAULIC_FLIPPERS, true);
            player->CastSpell(player, SPELL_TRADE_PRINCE_CONTROLLER_AURA, true);
            creature->AI()->Talk(1, player);
            break;
        }
        }
        return false;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        switch (quest->GetQuestId())
        {
        case QUEST_GOBLIN_ESCAPE_PODS_F:
        case QUEST_GOBLIN_ESCAPE_PODS_M:
        {
            break;
        }
        }
        return false;
    }
};

// 195188
class go_goblin_escape_pod_195188 : public GameObjectScript
{
public:
    go_goblin_escape_pod_195188() : GameObjectScript("go_goblin_escape_pod_195188") { }

    struct go_goblin_escape_pod_195188AI : public GameObjectAI
    {
        go_goblin_escape_pod_195188AI(GameObject* go) : GameObjectAI(go) { }

        EventMap m_events;

        void OnStateChanged(uint32 state, Unit* unit) override
        {
            if (unit)
                if (Player* player = unit->ToPlayer())
                    if (player->GetQuestStatus(QUEST_GOBLIN_ESCAPE_PODS_M) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_GOBLIN_ESCAPE_PODS_F) == QUEST_STATUS_INCOMPLETE)
                    {
                        Position p = go->GetNearPosition(1, frand(0, 6.28f));
                        if (player->HasAura(SPELL_TRADE_PRINCE_CONTROLLER_AURA))
                        {
                            player->RemoveAura(SPELL_TRADE_PRINCE_CONTROLLER_AURA);
                            player->CastSpell(player, SPELL_SUMMON_TRADE_PRINCE_GALLYWIX, true);
                        }
                        else
                            player->CastSpell(player, SPELL_SUMMON_LIVE_GOBLIN_SURVIVOR, true);

                        player->CastSpell(player, SPELL_SUMMONS_CONTROLLER, true);
                        player->KilledMonsterCredit(NPC_GOBLIN_SURVIVOR);
                        go->Delete();
                    }
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_goblin_escape_pod_195188AI(go);
    }
};

// 35649
class npc_trade_prince_gallywix_35649 : public CreatureScript
{
public:
    npc_trade_prince_gallywix_35649() : CreatureScript("npc_trade_prince_gallywix_35649") { }

    struct npc_trade_prince_gallywix_35649AI : public ScriptedAI
    {
        npc_trade_prince_gallywix_35649AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;

        void Reset()
        {
            me->SetDisableGravity(true);
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
            {
                me->CastSpell(me, SPELL_SWIM, true);
                m_playerGUID = player->GetGUID();
                m_events.ScheduleEvent(EVENT_TALK_PART_00, 2000);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_TALK_PART_00:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        Talk(0, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_01, 2000);
                    break;
                }
                case EVENT_TALK_PART_01:
                {
                    me->GetMotionMaster()->MovePoint(1001, 600, 3125, -1, false);
                    m_events.ScheduleEvent(EVENT_TALK_PART_02, 7000);
                    break;
                }
                case EVENT_TALK_PART_02:
                {
                    me->DespawnOrUnsummon(10);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_trade_prince_gallywix_35649AI(creature);
    }
};

// 34748
class npc_goblin_survivor_34748 : public CreatureScript
{
public:
    npc_goblin_survivor_34748() : CreatureScript("npc_goblin_survivor_34748") { }

    struct npc_goblin_survivor_34748AI : public ScriptedAI
    {
        npc_goblin_survivor_34748AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;

        void Reset()
        {
            me->SetDisableGravity(true);
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
            {
                me->CastSpell(me, SPELL_SWIM, true);
                m_playerGUID = player->GetGUID();
                m_events.ScheduleEvent(EVENT_TALK_PART_00, 2000);               
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_TALK_PART_00:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        Talk(0, player);   
                    m_events.ScheduleEvent(EVENT_TALK_PART_01, 2000);
                    break;
                }
                case EVENT_TALK_PART_01:
                {
                    me->GetMotionMaster()->MovePoint(1001, 600, 3125, -1, false);
                    m_events.ScheduleEvent(EVENT_TALK_PART_02, 7000);
                    break;
                }
                case EVENT_TALK_PART_02:
                {
                    me->DespawnOrUnsummon(10);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_goblin_survivor_34748AI(creature);
    }
};

// 34699
class npc_bomb_throwing_monkey_34699 : public CreatureScript
{
public:
    npc_bomb_throwing_monkey_34699() : CreatureScript("npc_bomb_throwing_monkey_34699") { }

    enum eNpc
    {
        EVENT_CAST_BOMB = 901,
        EVENT_ROCKET_MONKEY,
        EVENT_MONKEY_FALLING,
        EVENT_MONKEY_DIE,
    };

    struct npc_bomb_throwing_monkey_34699AI : public ScriptedAI
    {
        npc_bomb_throwing_monkey_34699AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset()
        {
            me->RemoveAura(29266);
            me->RemoveFlag(UNIT_NPC_EMOTESTATE, EMOTE_STATE_SLEEP);
            m_events.RescheduleEvent(EVENT_CAST_BOMB, urand(30000, 45000));
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override 
        { 
            if (spell->Id == SPELL_NITRO_POTASSIUM_BANANAS)
            {
                me->HandleEmote(EMOTE_ONESHOT_EAT);
                m_events.ScheduleEvent(EVENT_ROCKET_MONKEY, 1000);
                if (Player* player = caster->ToPlayer())
                    player->KilledMonsterCredit(NPC_MONKEY_BUSINESS_KILL_CREDIT);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CAST_BOMB:
                {
                    if (Player* player = me->FindNearestPlayer(frand(10.0, 25.0f)))
                        me->CastSpell(me, SPELL_COSMETIC_THROW_BOMB);
                    m_events.ScheduleEvent(EVENT_CAST_BOMB, urand(30000, 45000));
                    break;
                }
                case EVENT_ROCKET_MONKEY:
                {
                    me->CastSpell(me, SPELL_EXPLODING_BANANAS, true);
                    m_events.ScheduleEvent(EVENT_MONKEY_FALLING, 8000);
                    break;
                }
                case EVENT_MONKEY_FALLING:
                {
                    me->SetFlag(UNIT_NPC_EMOTESTATE, EMOTE_STATE_SLEEP);
                    m_events.ScheduleEvent(EVENT_MONKEY_DIE, 2000);
                    break;
                }
                case EVENT_MONKEY_DIE:
                {
                    me->AddAura(29266, me);
                    me->DespawnOrUnsummon(15000);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_bomb_throwing_monkey_34699AI(creature);
    }
};

// 35769
class npc_foreman_dampwick_35769 : public CreatureScript
{
public:
    npc_foreman_dampwick_35769() : CreatureScript("npc_foreman_dampwick_35769") { }

    enum eNPC
    {
        SPELL_FRIGHTENED_MINER_CONTROLLER_AURA = 68062, // Trigger: spell 68059 Summon Frightened Miner 35813 
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) 
    { 
        switch (quest->GetQuestId())
        {
        case 14021:
        {
            creature->AI()->Talk(0, player);
            player->CastSpell(player, SPELL_FRIGHTENED_MINER_CONTROLLER_AURA, true);
            break;
        }
        case 14031:
        {
            player->CastSpell(player, 70661, true);
            player->CastSpell(player, 70678, true);
            player->CastSpell(player, 70680, true);
            player->CastSpell(player, 70681, true);
            break;
        }
        }
        return false; 
    }


    };

// 35813
class npc_frightened_miner_35813 : public CreatureScript
{
public:
    npc_frightened_miner_35813() : CreatureScript("npc_frightened_miner_35813") { }

    enum eNPC
    {
        NPC_ORE_CART_35814 = 35814,
        SPELL_SUMMON_ORE_CART = 68064,
        SPELL_ORE_CART_TRANSFORM = 68065,
        SPELL_ORE_CART_CHAIN = 68122,        
        EVENT_SPAWN_POINT = 901,
        EVENT_SPAWN_CHAIN,
        EVENT_START_FOLLOWING,
        EVENT_START_TO_NEXT_ORE,
    };

    struct npc_frightened_miner_35813AI : public ScriptedAI
    {
        npc_frightened_miner_35813AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_cartGUID;
        uint64   m_dampwickGUID;
        uint32   m_move;

        void Reset() override
        {
            m_move = 0;
            m_playerGUID = me->GetOwnerGUID();
            m_dampwickGUID = 0;
            me->SetWalk(true);
            me->GetMotionMaster()->MovePoint(1001, 492.4184f, 2976.321f, 8.040207f);
            m_events.RescheduleEvent(EVENT_SPAWN_POINT, 3000);
            if (Creature* npc = me->FindNearestCreature(35769, 10.0f))
                m_dampwickGUID = npc->GetGUID();
        }

        void JustSummoned(Creature* summon) override 
        { 
            m_cartGUID = summon->GetGUID();
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == WAYPOINT_MOTION_TYPE && m_move == 1 && id == 3)
            {
                if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    if (Creature* dampwick = ObjectAccessor::GetCreature(*me, m_dampwickGUID))
                        if (Quest const* quest = sObjectMgr->GetQuestTemplate(14031))
                        {
                            player->AddQuest(quest, dampwick);
                            m_events.ScheduleEvent(EVENT_START_TO_NEXT_ORE, 8000);
                        }
            }
            else if (type == WAYPOINT_MOTION_TYPE && m_move == 2 && id == 5)
            {
                me->HandleEmote(EMOTE_STATE_WORK_MINING);
                m_events.ScheduleEvent(EVENT_START_TO_NEXT_ORE, 5000);
            }
            else if (type == WAYPOINT_MOTION_TYPE && m_move == 3 && id == 4)
            {
                me->HandleEmote(EMOTE_STATE_WORK_MINING);
                m_events.ScheduleEvent(EVENT_START_TO_NEXT_ORE, 5000);
            }
            else if (type == WAYPOINT_MOTION_TYPE && m_move == 4 && id == 6)
            {
                me->HandleEmote(EMOTE_STATE_WORK_MINING);
                m_events.ScheduleEvent(EVENT_START_TO_NEXT_ORE, 5000);
            }
            else if (type == WAYPOINT_MOTION_TYPE && m_move == 5 && id == 4)
            {
                me->HandleEmote(EMOTE_STATE_WORK_MINING);
                m_events.ScheduleEvent(EVENT_START_TO_NEXT_ORE, 5000);
            }
            else if (type == WAYPOINT_MOTION_TYPE && m_move == 6 && id == 15)
                m_events.ScheduleEvent(EVENT_START_TO_NEXT_ORE, 1000);
        }

        void EnterEvadeMode() override { }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_SPAWN_POINT:
                {
                    me->CastSpell(me, SPELL_SUMMON_ORE_CART, true);
                    m_events.ScheduleEvent(EVENT_SPAWN_CHAIN, 100);
                    break;
                }
                case EVENT_SPAWN_CHAIN:
                {
                    if (Creature* car = ObjectAccessor::GetCreature(*me, m_cartGUID))
                    {
                        car->CastSpell(car, SPELL_ORE_CART_TRANSFORM, true);
                        me->CastSpell(car, SPELL_ORE_CART_CHAIN, true);
                        m_events.ScheduleEvent(EVENT_START_FOLLOWING, 100);
                    }
                    break;
                }
                case EVENT_START_FOLLOWING:
                {
                    if (Creature* car = ObjectAccessor::GetCreature(*me, m_cartGUID))
                        if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        {
                            Talk(0, player);
                            m_move = 1;
                            car->GetMotionMaster()->MoveFollow(me, 1.5f, 3.14f);
                            me->GetMotionMaster()->MovePath(3581301, false);
                        }
                    break;
                }
                case EVENT_START_TO_NEXT_ORE:
                {
                    if (m_move < 6)
                    {
                        if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        {
                            Talk(m_move, player);
                            m_move += 1;
                            me->HandleEmote(EMOTE_ONESHOT_NONE);
                            me->GetMotionMaster()->MovePath(3581300 + m_move, false);
                            if (m_move == 6)
                                player->KilledMonsterCredit(35816);
                        }
                    }
                    else
                        me->DespawnOrUnsummon(10);
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_frightened_miner_35813AI(creature);
    }
};

// bunny 1-4
class npc_capturing_the_unknown_bunny : public CreatureScript
{
public:
    npc_capturing_the_unknown_bunny() : CreatureScript("npc_capturing_the_unknown_bunny") { }

    enum eNPC
    {
        EVENT_CAST_SPELL = 901,
    };

    struct npc_capturing_the_unknown_bunnyAI : public ScriptedAI
    {
        npc_capturing_the_unknown_bunnyAI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_playerGUID;

        void Initialize()
        {
            m_playerGUID=0;
        }

        void Reset() override
        {
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (!m_playerGUID)
            {
                m_events.RescheduleEvent(EVENT_MASTER_RESET, 5000);
                if (spell->Id == 68280)
                {
                    if (Player* player = caster->ToPlayer())
                    {
                        m_playerGUID = player->GetGUID();
                        me->CastSpell(caster, 68279, true);
                        m_events.RescheduleEvent(EVENT_CAST_SPELL, 400);
                    }
                }
            }
            else
            {
                switch (spell->Id)
                {
                case 68281:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        player->CastSpell(player, 70641, true);
                    }
                    break;
                }
                case 68296:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        player->RemoveAura(70649);
                        switch (me->GetEntry())
                        {
                        case 37872:
                            player->RemoveAura(70661);
                            break;
                        case 37895:
                            player->RemoveAura(70678);
                            break;
                        case 37896:
                            player->RemoveAura(70680);
                            break;
                        case 37897:
                            player->RemoveAura(70681);
                            break;
                        }
                        me->CastSpell(player, 68936, true);
                        player->KilledMonsterCredit(me->GetEntry());
                    }
                    m_playerGUID = 0;
                    break;
                }
                }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CAST_SPELL:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        player->CastSpell(player, 70649, true);
                        player->CastSpell(player, 70641, true);
                        player->CastSpell(me, 68281, true);
                    }
                    break;
                }
                case EVENT_MASTER_RESET:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        player->RemoveAura(70649);
                    m_playerGUID = 0;
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_capturing_the_unknown_bunnyAI(creature);
    }
};

void AddSC_zone_lost_isles()
{
    new npc_doc_zapnozzle_36608();
    new npc_geargrinder_gizmo_36600();
    new go_goblin_escape_pod_195188();
    new npc_trade_prince_gallywix_35649();
    new npc_goblin_survivor_34748();
    new npc_bomb_throwing_monkey_34699();
    new npc_foreman_dampwick_35769();
    new npc_frightened_miner_35813();
    new npc_capturing_the_unknown_bunny();

}
