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
    PLAYER_GUID = 99991,
    QUEST_DONT_GO_INTO_THE_LIGHT = 14239,
    QUEST_GOBLIN_ESCAPE_PODS_F = 14001,
    QUEST_GOBLIN_ESCAPE_PODS_M = 14474,
    QUEST_MEET_ME_UP_TOP = 14326,
    SPELL_QUEST_PHASE_01 = 67851,
    SPELL_QUEST_PHASE_02 = 67852,
    SPELL_QUEST_PHASE_03 = 67853,
    SPELL_QUEST_PHASE_04 = 67854,
    SPELL_QUEST_PHASE_05 = 68750,
    SPELL_QUEST_PHASE_06 = 72157,
    SPELL_QUEST_PHASE_07 = 72676,
    SPELL_QUEST_PHASE_08 = 73065,
    SPELL_QUEST_PHASE_09 = 73756,
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
    EVENT_SHOW_FIGHT,
    EVENT_CHECK_FIGHT,
    EVENT_CHECK_PLAYER,
    EVENT_CHECK_FIRE,
    EVENT_CHECK_BOAT,
    EVENT_CAST_SPELL_00,
    EVENT_CAST_SPELL_01,
    EVENT_CAST_COOLDOWN_01,
    EVENT_CAST_COOLDOWN_02,
    EVENT_START_WALK,
    EVENT_START_FLYING,
    EVENT_COOLDOWN_00,
    EVENT_COOLDOWN_01,
};

/*  phase 170  */

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
            m_activePlayerForWelcome = 0;
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
            m_events.RescheduleEvent(EVENT_CHECK_PLAYER_WELCOME, 1000);
            m_events.RescheduleEvent(EVENT_CHECK_PLAYER, 2500);
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (Player* player = who->ToPlayer())
                if (CheckFirstPlayerArrival(player))
                        if (playerList.find(player->GetGUID()) == playerList.end())
                            playerList.insert(player->GetGUID());
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
                case EVENT_CHECK_PLAYER:
                {
                    std::list<Player*> pList = me->FindNearestPlayers(35.0f);
                    for (std::list<Player*>::const_iterator itr = pList.begin(); itr != pList.end(); ++itr)
                        CheckFirstPlayerArrival(*itr);

                    m_events.ScheduleEvent(EVENT_CHECK_PLAYER, 2500);
                    break;
                }
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
                        if (player->GetQuestStatus(QUEST_DONT_GO_INTO_THE_LIGHT) == QUEST_STATE_NONE)
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
                        player->RemoveAura(SPELL_COSMETIC_STATE_DEATH);
                        player->ClearUnitState(UNIT_STATE_STUNNED);
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

        bool CheckFirstPlayerArrival(Player* player)
        {
            if (!player->hasQuest(QUEST_DONT_GO_INTO_THE_LIGHT))
                if (player->GetQuestStatus(QUEST_DONT_GO_INTO_THE_LIGHT) == QUEST_STATE_NONE)
                    if (!player->HasUnitState(UNIT_STATE_STUNNED))
                    {
                        player->NearTeleportTo(533.97f, 3274.55f, 0.21f, 5.015f);
                        player->AddUnitState(UNIT_STATE_STUNNED);
                        player->CastSpell(player, SPELL_QUEST_PHASE_01, true);
                        player->CastSpell(player, SPELL_COSMETIC_STATE_DEATH, true);
                        return true;
                    }
            return false;
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

// 35650
class npc_sassy_hardwrench_35650 : public CreatureScript
{
public:
    npc_sassy_hardwrench_35650() : CreatureScript("npc_sassy_hardwrench_35650") { }

    enum eNPC
    {        
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case 14014:
            creature->AI()->Talk(1, player);
            break;
        case 14234:
            creature->AI()->Talk(2, player);
            break;
        case 14248:
            creature->AI()->Talk(0, player);
            player->RemoveAura(68256);
            player->RemoveAura(68258);
            break;
        }
        return false;
    }
};

// 38738
class npc_coach_crosscheck_38738 : public CreatureScript
{
public:
    npc_coach_crosscheck_38738() : CreatureScript("npc_coach_crosscheck_38738") { }

    struct npc_coach_crosscheck_38738AI : public ScriptedAI
    {
        npc_coach_crosscheck_38738AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset()
        {
            m_events.RescheduleEvent(EVENT_TALK_PART_00, urand(45000, 60000));
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
                    if (Player* player = me->FindNearestPlayer(25.0f))
                        Talk(1, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_00, urand(45000, 60000));
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
        return new npc_coach_crosscheck_38738AI(creature);
    }
};

// 35786
class npc_maxx_avalanche_35786 : public CreatureScript
{
public:
    npc_maxx_avalanche_35786() : CreatureScript("npc_maxx_avalanche_35786") { }

    enum eNPC
    {
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case 14473:
            creature->AI()->Talk(0, player);
            break;       
        }
        return false;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        switch (quest->GetQuestId())
        {
        case 14473:
            creature->AI()->Talk(1, player);
            break;
        }
        return false;
    }


};

// 35758
class npc_bamm_megabomb_35758 : public CreatureScript
{
public:
    npc_bamm_megabomb_35758() : CreatureScript("npc_bamm_megabomb_35758") { }

    enum eNPC
    {
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case 14019:
            creature->AI()->Talk(0, player);
            break;
        }
        return false;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        switch (quest->GetQuestId())
        {
        case 14019:
            creature->AI()->Talk(1, player);
            break;
        }
        return false;
    }


};

// 36403
class npc_trade_prince_gallywix_36403 : public CreatureScript
{
public:
    npc_trade_prince_gallywix_36403() : CreatureScript("npc_trade_prince_gallywix_36403") { }

    struct npc_trade_prince_gallywix_36403AI : public ScriptedAI
    {
        npc_trade_prince_gallywix_36403AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        
        void Reset()
        {
            m_events.RescheduleEvent(EVENT_TALK_PART_00, urand(45000, 60000));
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
                    if (Player* player = me->FindNearestPlayer(25.0f))
                        Talk(0, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_00, urand(45000, 60000));
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
        return new npc_trade_prince_gallywix_36403AI(creature);
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
            break;
        }
        }
        return false;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        switch (quest->GetQuestId())
        {
        case 14021:
            creature->AI()->Talk(1, player);
            player->RemoveAura(SPELL_FRIGHTENED_MINER_CONTROLLER_AURA);
            break;
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
            if (Creature* cart = summon->ToCreature())
            {
                m_cartGUID = cart->GetGUID();
                cart->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                cart->SetReactState(REACT_PASSIVE);
            }
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
                            player->CastSpell(player, 68920, true);
                            player->CastSpell(player, 70661, true);
                            player->CastSpell(player, 70678, true);
                            player->CastSpell(player, 70680, true);
                            player->CastSpell(player, 70681, true);
                            Talk(1, player);
                            m_events.ScheduleEvent(EVENT_START_TO_NEXT_ORE, 10000);
                        }
            }
            else if (type == WAYPOINT_MOTION_TYPE && m_move == 2 && id == 5)
            {
                me->HandleEmote(EMOTE_STATE_WORK_MINING);
                m_events.ScheduleEvent(EVENT_START_TO_NEXT_ORE, 8000);
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
                            m_move += 1;
                            if (m_move < 6)
                                Talk(2, player);
                            else if (m_move == 6)
                            {
                                Talk(3, player);
                                player->KilledMonsterCredit(35816);
                            }
                            me->HandleEmote(EMOTE_ONESHOT_NONE);
                            me->GetMotionMaster()->MovePath(3581300 + m_move, false);
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

    struct npc_capturing_the_unknown_bunnyAI : public ScriptedAI
    {
        npc_capturing_the_unknown_bunnyAI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_bunnyGUID;

        void Initialize()
        {
            m_playerGUID = 0;
            m_bunnyGUID = 0;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (!m_bunnyGUID)
                if (Creature* bunny = me->FindNearestCreature(23837, 10.0f))
                    m_bunnyGUID = bunny->GetGUID();
            if (!m_playerGUID)
                if (Player* player = caster->ToPlayer())
                    m_playerGUID = player->GetGUID();

            if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                switch (spell->Id)
                {
                case 68281:
                {
                    m_events.ScheduleEvent(EVENT_CAST_SPELL_00, 200);
                    m_events.RescheduleEvent(EVENT_MASTER_RESET, 5000);
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        me->CastSpell(player, 68279, true);
                        if (Creature* bunny = ObjectAccessor::GetCreature(*me, m_bunnyGUID))
                            player->CastSpell(bunny, 70641, true);
                    }
                    break;
                }
                case 68296:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
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
                    }
                    m_events.ScheduleEvent(EVENT_CAST_SPELL_01, 2000);
                    break;
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
                case EVENT_CAST_SPELL_00:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        player->CastSpell(player, 70641, true);
                        player->CastSpell(player, 70649, true);
                    }
                    break;
                }
                case EVENT_CAST_SPELL_01:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        me->CastSpell(player, 68936, true);
                        player->KilledMonsterCredit(me->GetEntry());
                        m_events.CancelEvent(EVENT_MASTER_RESET);
                    }
                    /* no break here */
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

// 35838
class npc_pygmy_witchdoctor_35838 : public CreatureScript
{
public:
    npc_pygmy_witchdoctor_35838() : CreatureScript("npc_pygmy_witchdoctor_35838") { }

    struct npc_pygmy_witchdoctor_35838AI : public ScriptedAI
    {
        npc_pygmy_witchdoctor_35838AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset()
        {
            m_events.RescheduleEvent(EVENT_TALK_PART_00, urand(15000, 20000));
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
                    if (Player* player = me->FindNearestPlayer(25.0f))
                        Talk(0, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_00, urand(15000, 20000));
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
        return new npc_pygmy_witchdoctor_35838AI(creature);
    }
};

// 35875
class npc_aggra_35875 : public CreatureScript
{
public:
    npc_aggra_35875() : CreatureScript("npc_aggra_35875") { }

    enum eNPC
    {
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case 14235:
            creature->AI()->Talk(0, player);
            break;
        case 14237:
            creature->AI()->Talk(1, player);
            break;
        }
        return false;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        switch (quest->GetQuestId())
        {
        case 14303:           
            player->RemoveAura(SPELL_QUEST_PHASE_01);
            player->CastSpell(player, SPELL_QUEST_PHASE_02);
            break;
        }
        return false;
    }
};

// 35894
class npc_orc_scout_35894 : public CreatureScript
{
public:
    npc_orc_scout_35894() : CreatureScript("npc_orc_scout_35894") { }

    enum eNPC
    {
    };

    struct npc_orc_scout_35894AI : public ScriptedAI
    {
        npc_orc_scout_35894AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap  m_events;
        Creature* m_target;

        void Initialize()
        {
            m_target=nullptr;
        }

        void Reset() override
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            me->SetReactState(REACT_PASSIVE);
            m_events.RescheduleEvent(EVENT_SHOW_FIGHT, urand(20000, 60000));
        }

        void EnterCombat(Unit* victim) override 
        { 
            if (victim->GetEntry() == 35896 || victim->GetEntry() == 35897)
                me->SetReactState(REACT_PASSIVE);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (attacker->GetEntry() == 35896 || attacker->GetEntry() == 35897)
                damage = 0;
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_SHOW_FIGHT:
                {
                    FillTargetList();
                    if (m_target)
                        me->CastSpell(m_target, 15620);

                    m_events.ScheduleEvent(EVENT_SHOW_FIGHT, urand(20000, 60000));
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void FillTargetList()
        {
            m_target=nullptr;
            std::list<Creature*> tList = me->FindNearestCreatures(RAND(35896, 35897, 35995), 25.0f);
            if (tList.size() > 0)
            {
                uint32 rol = urand(0, tList.size() - 1);
                std::list<Creature*>::const_iterator itr = tList.begin();
                std::advance(itr, rol);
                m_target = (*itr);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_orc_scout_35894AI(creature);
    }
};

// 35893
class npc_kilag_gorefang_35893 : public CreatureScript
{
public:
    npc_kilag_gorefang_35893() : CreatureScript("npc_kilag_gorefang_35893") { }

    enum eNPC
    {
    };

    bool OnGossipHello(Player* player, Creature* creature) 
    { 
        creature->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
        if (player->HasAura(68212))
        {
            player->RemoveAura(68212);
            player->RemoveAura(68824);
        }
        return false; 
    }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case 14303:
            creature->AI()->Talk(1, player);
            break;
        }
        return false;
    }

    struct npc_kilag_gorefang_35893AI : public ScriptedAI
    {
        npc_kilag_gorefang_35893AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap  m_events;
        Creature* m_target;
        uint64    m_playerGUID;

        void Initialize()
        {
            m_target = nullptr;
            m_playerGUID = 0;
        }

        void Reset() override
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            me->SetReactState(REACT_PASSIVE);
            m_events.RescheduleEvent(EVENT_SHOW_FIGHT, urand(20000, 60000));
        }

        void EnterCombat(Unit* victim) override
        {
            if (victim->GetEntry() == 35896 || victim->GetEntry() == 35897)
                me->SetReactState(REACT_PASSIVE);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (attacker->GetEntry() == 35896 || attacker->GetEntry() == 35897)
                damage = 0;
        }

        void JustSummoned(Creature* summon) override 
        { 
            if (summon->GetEntry() == 35918)
                summon->AI()->SetGUID(m_playerGUID, PLAYER_GUID);
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case PLAYER_GUID:
            {
                m_playerGUID = guid;
                break;
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
                case EVENT_SHOW_FIGHT:
                {
                    FillTargetList();
                    if (m_target)
                        me->CastSpell(m_target, 15620);

                    m_events.ScheduleEvent(EVENT_SHOW_FIGHT, urand(20000, 60000));
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void FillTargetList()
        {
            m_target = nullptr;
            std::list<Creature*> tList = me->FindNearestCreatures(RAND(35896, 35897, 35995), 25.0f);
            if (tList.size() > 0)
            {
                uint32 rol = urand(0, tList.size() - 1);
                std::list<Creature*>::const_iterator itr = tList.begin();
                std::advance(itr, rol);
                m_target = (*itr);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_kilag_gorefang_35893AI(creature);
    }
};

// 35896
class npc_poison_spitter_35896 : public CreatureScript
{
public:
    npc_poison_spitter_35896() : CreatureScript("npc_poison_spitter_35896") { }

    enum eNPC
    {
    };

    struct npc_poison_spitter_35896AI : public ScriptedAI
    {
        npc_poison_spitter_35896AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap  m_events;
        Creature* m_target;
        bool      m_castCD;

        void Initialize()
        {
            m_target = nullptr;
            m_castCD = false;
        }

        void Reset() override
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            me->SetReactState(REACT_PASSIVE);
            m_events.RescheduleEvent(EVENT_SHOW_FIGHT, urand(20000, 120000));
        }

        void EnterCombat(Unit* victim) override
        {
            if (victim->GetEntry() == 35893 || victim->GetEntry() == 35894)
                me->SetReactState(REACT_PASSIVE);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (attacker->GetEntry() == 35893 || attacker->GetEntry() == 35894)
                damage = 0;
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (!m_castCD)
                if (Player* player = who->ToPlayer())
                    if (player->GetQuestStatus(14235) == QUEST_STATUS_NONE || player->GetQuestStatus(14303) == QUEST_STATUS_REWARDED)
                    {
                        me->CastSpell(player, RAND(68207, 68208));
                        m_castCD = true;
                        m_events.ScheduleEvent(EVENT_CAST_COOLDOWN_01, urand(45000, 90000));
                    }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_SHOW_FIGHT:
                {
                    FillTargetList();
                    if (m_target)
                        me->CastSpell(m_target, RAND(68207, 68208));

                    m_events.ScheduleEvent(EVENT_SHOW_FIGHT, urand(40000, 180000));
                    break;
                }
                case EVENT_CAST_COOLDOWN_01:
                    m_castCD = false;
                    break;
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void FillTargetList()
        {
            m_target = nullptr;
            std::list<Creature*> tList = me->FindNearestCreatures(RAND(35893, 35894), 25.0f);
            if (tList.size() > 0)
            {
                uint32 rol = urand(0, tList.size() - 1);
                std::list<Creature*>::const_iterator itr = tList.begin();
                std::advance(itr, rol);
                m_target = (*itr);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_poison_spitter_35896AI(creature);
    }
};

// 35897
class npc_freezya_35897 : public CreatureScript
{
public:
    npc_freezya_35897() : CreatureScript("npc_freezya_35897") { }

    enum eNPC
    {
    };

    struct npc_freezya_35897AI : public ScriptedAI
    {
        npc_freezya_35897AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap  m_events;
        Creature* m_target;
        bool      m_castCD;

        void Initialize()
        {
            m_target = nullptr;
            m_castCD = false;
        }

        void Reset() override
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            me->SetReactState(REACT_PASSIVE);
            m_events.RescheduleEvent(EVENT_SHOW_FIGHT, urand(20000, 120000));
        }

        void EnterCombat(Unit* victim) override
        {
            if (victim->GetEntry() == 35893 || victim->GetEntry() == 35894)
                me->SetReactState(REACT_PASSIVE);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override 
        { 
            if (attacker->GetEntry() == 35893 || attacker->GetEntry() == 35894)
                damage=0;
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (!m_castCD)
                if (Player* player = who->ToPlayer())
                    if (player->GetQuestStatus(14235) == QUEST_STATUS_NONE || player->GetQuestStatus(14303) == QUEST_STATUS_REWARDED)
                    {
                        me->CastSpell(player, 68209);
                        m_castCD = true;
                        m_events.ScheduleEvent(EVENT_CAST_COOLDOWN_01, urand(45000, 90000));
                    }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_SHOW_FIGHT:
                {
                    FillTargetList();
                    if (m_target)
                        me->CastSpell(m_target, 68209);

                    m_events.ScheduleEvent(EVENT_SHOW_FIGHT, urand(40000, 180000));
                    break;
                }
                case EVENT_CAST_COOLDOWN_01:
                    m_castCD = false;
                    break;
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void FillTargetList()
        {
            m_target = nullptr;
            std::list<Creature*> tList = me->FindNearestCreatures(RAND(35893, 35894), 25.0f);
            if (tList.size() > 0)
            {
                uint32 rol = urand(0, tList.size() - 1);
                std::list<Creature*>::const_iterator itr = tList.begin();
                std::advance(itr, rol);
                m_target = (*itr);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_freezya_35897AI(creature);
    }
};

// 35995
class npc_strangle_vine_35995 : public CreatureScript
{
public:
    npc_strangle_vine_35995() : CreatureScript("npc_strangle_vine_35995") { }

    enum eNPC
    {
    };

    struct npc_strangle_vine_35995AI : public VehicleAI
    {
        npc_strangle_vine_35995AI(Creature* creature) : VehicleAI(creature) { Initialize(); }

        EventMap  m_events;
        uint64    m_playerGUID;

        void Initialize()
        {
            m_playerGUID = 0;
        }

        void Reset() override
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            me->SetReactState(REACT_PASSIVE);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override 
        { 
            if (Player* player = attacker->ToPlayer())
            {
                me->CastSpell(me, 60603);
                m_playerGUID = player->GetGUID();
            }
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override 
        { 
            if (!apply)
                if (Creature* orc = passenger->ToCreature())
                    if (orc->GetEntry() == 36042)
                        if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        {
                            orc->AI()->Talk(0, player);
                            orc->GetMotionMaster()->MovePoint(1005, 662.74f, 2844.35f, 85.899f);
                            orc->DespawnOrUnsummon(8000);
                        }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_strangle_vine_35995AI(creature);
    }
};

// 35918
class npc_orc_scout_35918 : public CreatureScript
{
public:
    npc_orc_scout_35918() : CreatureScript("npc_orc_scout_35918") { }

    enum eNPC
    {
    };

    struct npc_orc_scout_35918AI : public ScriptedAI
    {
        npc_orc_scout_35918AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap  m_events;
        uint64    m_playerGUID;
        Position  m_position;

        void Initialize()
        {
            m_playerGUID = 0;
            m_position = Position(656.1f, 2819.3f, 84.96f);
        }

        void Reset() override
        {
            m_events.RescheduleEvent(EVENT_TALK_PART_00, 1000);
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case PLAYER_GUID:
            {
                m_playerGUID = guid;
                break;
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
                case EVENT_TALK_PART_00:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        Talk(urand(0, 3), player);
                    me->GetMotionMaster()->MovePoint(1004, 661.02f, 2824.89f, 84.90f);
                    me->DespawnOrUnsummon(10000);
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_orc_scout_35918AI(creature);
    }
};

// 49108
class item_weed_whacker_49108 : public ItemScript
{
public:
    item_weed_whacker_49108() : ItemScript("item_weed_whacker_49108") { }

    bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& targets) override
    {
        if (player->HasAura(68212))
        {
            player->RemoveAura(68212);
            player->RemoveAura(68824);
            return true;
        }

        return false;
    }
};

/*  phase 171  */

// 49611
class item_infrared_heat_focals_49611 : public ItemScript
{
public:
    item_infrared_heat_focals_49611() : ItemScript("item_infrared_heat_focals_49611") { }

    bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& targets) override
    {
        if (player->HasAura(69303))
        {
            player->RemoveAura(69303);
            player->RemoveAura(68376);
            return true;
        }
        else
        {
            Creature* orc = player->FindNearestCreature(36100, 25.0f);
            if (!orc)
                player->CastSpell(player, 68338);
        }

        return false;
    }
};

// 35917
class npc_kilag_gorefang_35917 : public CreatureScript
{
public:
    npc_kilag_gorefang_35917() : CreatureScript("npc_kilag_gorefang_35917") { }

    enum eNPC
    {
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->HasAura(69303))
            if (player->GetQuestStatus(14238) != QUEST_STATUS_INCOMPLETE)
            {
                player->RemoveAura(69303);
                player->RemoveAura(68376);
            }
        return false;
    }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case 14238:
            creature->AI()->Talk(0, player);
            creature->CastSpell(player, 68344);
            break;
        case 14240:
            creature->AI()->Talk(1, player);
            player->CastSpell(player, 68973);
            break;
        }
        return false;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        switch (quest->GetQuestId())
        {
        case 14238:
            player->CastSpell(player, 68337);
            player->CastSpell(player, 68371);
            player->RemoveAura(68338);
            break;
        }
        return false;
    }
};

// 36100
class npc_orc_scout_36100 : public CreatureScript
{
public:
    npc_orc_scout_36100() : CreatureScript("npc_orc_scout_36100") { }

    struct npc_orc_scout_36100AI : public ScriptedAI
    {
        npc_orc_scout_36100AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap  m_events;
        uint64    m_playerGUID;

        void Initialize()
        {
            m_playerGUID = 0;
        }

        void Reset() override
        {
            if (!m_playerGUID)
            {
                m_playerGUID = me->GetOwnerGUID();
                m_events.RescheduleEvent(EVENT_TALK_PART_00, 1000);
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
        return new npc_orc_scout_36100AI(creature);
    }
};

// 36585
class npc_bastia_36585 : public CreatureScript
{
public:
    npc_bastia_36585() : CreatureScript("npc_bastia_36585") { }

    enum eNPC
    {
    };

    struct npc_bastia_36585AI : public VehicleAI
    {
        npc_bastia_36585AI(Creature* creature) : VehicleAI(creature) { Initialize(); }

        EventMap  m_events;
        uint64    m_playerGUID;

        void Initialize()
        {
            m_playerGUID = 0;
        }

        void Reset() override
        {
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override
        {
            if (apply)
            {
                if (Player* player = passenger->ToPlayer())
                {
                    m_playerGUID = player->GetGUID();
                    m_events.ScheduleEvent(EVENT_START_WALK, 3000);
                }
            }
        }

        void MovementInform(uint32 type, uint32 id) override 
        { 
            if (type == WAYPOINT_MOTION_TYPE)
                if (id == 27)
                    me->DespawnOrUnsummon(10);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_WALK:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        player->SetClientControl(me, false);
                    me->GetMotionMaster()->MovePath(3658500, false);
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
        return new npc_bastia_36585AI(creature);
    }
};

/*  phase 172  */

// 36112
class npc_scout_brax_36112 : public CreatureScript
{
public:
    npc_scout_brax_36112() : CreatureScript("npc_scout_brax_36112") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case 14241:
        {
            creature->AI()->Talk(0, player);
            break;
        }
        }
        return false;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        switch (quest->GetQuestId())
        {
        case 14240:
            player->RemoveAura(SPELL_QUEST_PHASE_02);
            player->CastSpell(player, SPELL_QUEST_PHASE_03);
            break;
        }
        return false;
    }
};

// 36129
class npc_gyrochoppa_pilot_36129 : public CreatureScript
{
public:
    npc_gyrochoppa_pilot_36129() : CreatureScript("npc_gyrochoppa_pilot_36129") { }

    enum eNPC
    {
    };

    struct npc_gyrochoppa_pilot_36129AI : public ScriptedAI
    {
        npc_gyrochoppa_pilot_36129AI(Creature* creature) : ScriptedAI(creature) { }

        void EnterCombat(Unit* victim) override 
        { 
            if (Player* player = victim->ToPlayer())
                Talk(0, player);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_gyrochoppa_pilot_36129AI(creature);
    }
};

// 36127
class npc_gyrochoppa_36127 : public CreatureScript
{
public:
    npc_gyrochoppa_36127() : CreatureScript("npc_gyrochoppa_36127") { }

    enum eNPC
    {
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case 14242:
            player->PlayDirectSound(16422, player);
            player->CastSpell(player, 68386, true);
            break;
        }
        return false;
    }
};

// 36143
class npc_gyrochoppa_36143 : public CreatureScript
{
public:
    npc_gyrochoppa_36143() : CreatureScript("npc_gyrochoppa_36143") { }

    enum eNPC
    {
    };

    struct npc_gyrochoppa_36143AI : public VehicleAI
    {
        npc_gyrochoppa_36143AI(Creature* creature) : VehicleAI(creature) { Initialize(); }

        EventMap  m_events;
        uint64    m_playerGUID;

        void Initialize()
        {
            m_playerGUID = 0;
        }

        void Reset() override
        {
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override
        {
            if (apply)
            {
                if (Player* player = passenger->ToPlayer())
                {
                    m_playerGUID = player->GetGUID();
                    m_events.ScheduleEvent(EVENT_START_FLYING, 3000);
                }
            }
            else
                if (Player* player = passenger->ToPlayer())
                    Talk(0, player);
        }

        void MovementInform(uint32 type, uint32 id) override 
        { 
            if (type == WAYPOINT_MOTION_TYPE)
                switch (id)
                {
                case 5:
                    me->CastSpell(me, 68576, true);
                    me->CastSpell(me, 66127, true);
                    me->DespawnOrUnsummon(100);
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
                case EVENT_START_FLYING:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        player->SetClientControl(me, false);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
                    me->SetSpeed(MOVE_RUN, 2.5f);
                    me->SetDisableGravity(true);
                    me->SetCanFly(true);
                    me->GetMotionMaster()->MovePath(3614300, false);
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
        return new npc_gyrochoppa_36143AI(creature);
    }
};

// 36145
class npc_thrall_36145 : public CreatureScript
{
public:
    npc_thrall_36145() : CreatureScript("npc_thrall_36145") { }

    enum eNPC
    {
    };

    bool OnGossipHello(Player* player, Creature* creature) 
    { 
        if (player->GetQuestStatus(14242) == QUEST_STATUS_INCOMPLETE)
        {
            player->KilledMonsterCredit(36145);
            if (GameObject* go = creature->FindNearestGameObject(195704, 10.0f))
            {
                go->UseDoorOrButton();
                player->CLOSE_GOSSIP_MENU();
                return true;
            }
        }

        return false; 
    }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case 14326:
            player->RemoveAura(SPELL_QUEST_PHASE_03);
            player->CastSpell(player, SPELL_QUEST_PHASE_04);
            player->CastSpell(993.1458f, 3852.019f, 3.2269f, 69079, true);
            player->CastSpell(player, 68421, true);
            break;
        }
        return false;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        switch (quest->GetQuestId())
        {
        case 14242:
            player->PlayDirectSound(16423, player);
            break;
        }
        return false;
    }
};

/*  phase 179  */

// 36622
class npc_thrall_36622 : public CreatureScript
{
public:
    npc_thrall_36622() : CreatureScript("npc_thrall_36622") { }

    enum eNPC
    {
    };

    struct npc_thrall_36622AI : public ScriptedAI
    {
        npc_thrall_36622AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap  m_events;
        uint64   m_playerGUID;

        void Initialize()
        {
            m_playerGUID = 0;
        }

        void Reset() override
        {
            m_events.RescheduleEvent(EVENT_START_WALK, 2000);
        }

        void IsSummonedBy(Unit* summoner) override 
        { 
            if (Player* player = summoner->ToPlayer())
                m_playerGUID = player->GetGUID();
        }

        void MovementInform(uint32 type, uint32 id) override 
        { 
            if (type == WAYPOINT_MOTION_TYPE && id == 8)
                me->DespawnOrUnsummon(10);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_WALK:
                {
                    me->GetMotionMaster()->MovePath(3662200, false);
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        Talk(0, player);
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
        return new npc_thrall_36622AI(creature);
    }
};

// 36161
class npc_thrall_36161 : public CreatureScript
{
public:
    npc_thrall_36161() : CreatureScript("npc_thrall_36161") { }

    enum eNPC
    {
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case 14243:
            creature->PlayDirectSound(16424, player);
            player->CastSpell(player, 68408, true);
            break;
        }
        return false;
    }

    struct npc_thrall_36161AI : public ScriptedAI
    {
        npc_thrall_36161AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap  m_events;
        uint64   m_playerGUID;
        bool     m_startTalkCD;
        uint8    m_rolTalk;

        void Initialize()
        {
            m_playerGUID = 0;
            m_startTalkCD = false;
            m_rolTalk = 0;
        }

        void Reset() override
        {
        }
         
        void MoveInLineOfSight(Unit* who) override
        {
            if (!m_startTalkCD)
                if (Player* player = who->ToPlayer())
                    if (player->GetQuestStatus(QUEST_MEET_ME_UP_TOP) == QUEST_STATUS_COMPLETE)
                    {
                        m_startTalkCD = true;
                        m_playerGUID = player->GetGUID();
                        m_events.ScheduleEvent(EVENT_COOLDOWN_00, 90000);
                        m_events.ScheduleEvent(EVENT_TALK_PART_01, 100);
                    }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_COOLDOWN_00:
                    m_startTalkCD = false;
                    break;
                case EVENT_TALK_PART_01:
                {
                    m_rolTalk += 1;
                    if (m_rolTalk > 2)
                        m_rolTalk = 0;

                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        Talk(m_rolTalk * 2 + 1, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_02, 8000);
                    break;
                }
                case EVENT_TALK_PART_02:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        Talk(m_rolTalk * 2 + 2, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_03, 8000);
                    break;
                }
                case EVENT_TALK_PART_03:
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
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_thrall_36161AI(creature);
    }
};

// 36177
class npc_invisible_stalker_quest_phase4_36177 : public CreatureScript
{
public:
    npc_invisible_stalker_quest_phase4_36177() : CreatureScript("npc_invisible_stalker_quest_phase4_36177") { }

    enum eNPC
    {
    };

    struct npc_invisible_stalker_quest_phase4_36177AI : public ScriptedAI
    {
        npc_invisible_stalker_quest_phase4_36177AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap  m_events;

        void Reset() override
        {
            m_events.RescheduleEvent(EVENT_CHECK_FIRE, 1000);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_FIRE:
                    if (urand(0, 100) < 15)
                        me->CastSpell(me, 42345);
                    m_events.ScheduleEvent(EVENT_CHECK_FIRE, urand(80000, 100000));
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_invisible_stalker_quest_phase4_36177AI(creature);
    }
};

// 36176
class npc_alliance_sailor_36176 : public CreatureScript
{
public:
    npc_alliance_sailor_36176() : CreatureScript("npc_alliance_sailor_36176") { }

    enum eNPC
    {
    };

    struct npc_alliance_sailor_36176AI : public ScriptedAI
    {
        npc_alliance_sailor_36176AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap  m_events;

        void Reset() override
        {
            m_events.RescheduleEvent(EVENT_CHECK_BOAT, 2000);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_BOAT:
                    if (me->GetPositionZ() < me->GetHomePosition().GetPositionZ() + 0.2f)
                        me->GetMotionMaster()->MoveTargetedHome();
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_alliance_sailor_36176AI(creature);
    }
};

// 36178
class npc_cyclone_of_the_elements_36178 : public CreatureScript
{
public:
    npc_cyclone_of_the_elements_36178() : CreatureScript("npc_cyclone_of_the_elements_36178") { }

    enum eNPC
    {
    };

    struct npc_cyclone_of_the_elements_36178AI : public VehicleAI
    {
        npc_cyclone_of_the_elements_36178AI(Creature* creature) : VehicleAI(creature) { Initialize(); }

        EventMap  m_events;
        uint64    m_playerGUID;
        bool      m_backToLostIsland;

        void Initialize()
        {
            m_playerGUID = 0;
            m_backToLostIsland = false;
        }

        void Reset() override
        {
            
        }

        void IsSummonedBy(Unit* summoner) override 
        { 
            if (Player* player = summoner->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                player->CastSpell(me, 68436, true);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
                me->SetDisableGravity(true);
                me->SetCanFly(true);
            }
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override
        {
            if (Player* player = passenger->ToPlayer())
                if (apply)
                {
                    me->GetMotionMaster()->MovePath(3617801, true);
                }
                else
                {
                    player->RemoveAura(68436);
                    player->RemoveAura(68421);
                }
        }

        void KilledUnit(Unit* victim) override 
        { 
            if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                if (player->GetReqKillOrCastCurrentCount(14243, 36176) >= 50)
                {
                    me->GetMotionMaster()->MoveIdle();
                    me->SetSpeed(MOVE_RUN, 3.5f);
                    m_backToLostIsland = true;
                    me->GetMotionMaster()->MovePath(3617802, false);
                }
        }

        void MovementInform(uint32 type, uint32 id) override 
        { 
            if (m_backToLostIsland && type==WAYPOINT_MOTION_TYPE && id == 11)
                me->DespawnOrUnsummon(10);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_cyclone_of_the_elements_36178AI(creature);
    }
};

// 68445
class spell_lightning_strike_68445 : public SpellScriptLoader
{
public:
    spell_lightning_strike_68445() : SpellScriptLoader("spell_lightning_strike_68445") { }

    class spell_lightning_strike_68445_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_lightning_strike_68445_SpellScript);

        void FilterTargets(std::list<WorldObject*>& unitList)
        {
            float range = 5.0f;
            const WorldLocation* pos = GetExplTargetDest();
            uint32 typeMask = GRID_MAP_TYPE_MASK_PLAYER | GRID_MAP_TYPE_MASK_CREATURE;
            Trinity::WorldObjectSpellAreaTargetCheck check(range, pos, GetCaster(), GetCaster(), GetSpellInfo(), TARGET_CHECK_DEFAULT, NULL);
            Trinity::WorldObjectListSearcher<Trinity::WorldObjectSpellAreaTargetCheck> searcher(GetCaster(), unitList, check, typeMask);
            GetCaster()->GetMap()->VisitAll(pos->m_positionX, pos->m_positionY, range, searcher);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_lightning_strike_68445_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_lightning_strike_68445_SpellScript();
    }
};


void AddSC_zone_lost_isles()
{
    /*  phase 170  */
    new npc_doc_zapnozzle_36608();
    new npc_geargrinder_gizmo_36600();
    new go_goblin_escape_pod_195188();
    new npc_trade_prince_gallywix_35649();
    new npc_goblin_survivor_34748();
    new npc_sassy_hardwrench_35650();
    new npc_coach_crosscheck_38738();
    new npc_maxx_avalanche_35786();
    new npc_bamm_megabomb_35758();
    new npc_trade_prince_gallywix_36403();
    new npc_bomb_throwing_monkey_34699();
    new npc_foreman_dampwick_35769();
    new npc_frightened_miner_35813();
    new npc_capturing_the_unknown_bunny();
    new npc_pygmy_witchdoctor_35838();
    new npc_aggra_35875();
    new npc_orc_scout_35894();
    new npc_kilag_gorefang_35893();
    new npc_poison_spitter_35896();
    new npc_freezya_35897();
    new npc_strangle_vine_35995();
    new npc_orc_scout_35918();
    new item_weed_whacker_49108();
    /*  phase 171  */
    new item_infrared_heat_focals_49611();
    new npc_kilag_gorefang_35917();
    new npc_orc_scout_36100();
    new npc_bastia_36585();
    /*  phase 172  */
    new npc_scout_brax_36112();
    new npc_gyrochoppa_pilot_36129();
    new npc_gyrochoppa_36127();
    new npc_gyrochoppa_36143();
    new npc_thrall_36145();
    /*  phase 179  */
    new npc_thrall_36161();
    new npc_thrall_36622();
    new npc_invisible_stalker_quest_phase4_36177();
    new npc_alliance_sailor_36176();
    new npc_cyclone_of_the_elements_36178();
    new spell_lightning_strike_68445();

}
