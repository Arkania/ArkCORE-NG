/*
 * Copyright (C) 2011-2017 ArkCORE <http://www.arkania.net/>
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
#include "MovementGenerator.h"
#include "TargetedMovementGenerator.h"

enum Zone_zone_lost_isles
{
    NPC_GEARGRINDER_GIZMO = 36600,
    NPC_DOC_ZAPNOZZLE = 36608,
    NPC_GOBLIN_SURVIVOR = 34748,
    NPC_MONKEY_BUSINESS_KILL_CREDIT = 35760,
    NPC_RAPTOR_38187 = 38187,
    NPC_WILD_CLUCKER_EGG_38195 = 38195,
    NPC_ACE_38455 = 38455,
    NPC_NAGA_HATCHLING_KILL_CREDIT = 38413,
    NPC_NAGA_HATCHLING_44578 = 44578,
    NPC_NAGA_HATCHLING_44579 = 44579,
    NPC_NAGA_HATCHLING_44580 = 44580,
    NPC_NAGA_HATCHLING_44588 = 44588,
    NPC_NAGA_HATCHLING_44589 = 44589,
    NPC_NAGA_HATCHLING_44590 = 44590,
    NPC_NAGA_HATCHLING_44591 = 44591,
    NPC_VASHJ_ELAN_SIREN_38360 = 38360,
    NPC_OOMLOT_WARRIOR_38531 = 38531,
    NPC_BC_ELIMINATOR_38526 = 38526,
    NPC_GAAHL_38808 = 38808,
    NPC_MALMO_38809 = 38809,
    NPC_TELOCH_38810 = 38810,
    NPC_ZOMBIE_KILL_CREDIT_38807 = 38807,
    GO_TRAP_201972 = 201972,
    QUEST_DONT_GO_INTO_THE_LIGHT = 14239,
    QUEST_GOBLIN_ESCAPE_PODS_F = 14001,
    QUEST_GOBLIN_ESCAPE_PODS_M = 14474,
    QUEST_MEET_ME_UP_TOP = 14326,
    QUEST_BILGEWATER_CARTEL_REPRESENT = 24858,
    QUEST_IRRESISTIBLE_POOL_PONY = 24864,
    QUEST_SURRENDER_OR_ELSE = 24868,
    QUEST_GET_BACK_TO_TOWN = 24897,
    QUEST_UNDER_ATTACK = 24901,
    QUEST_OOMLOT_VILLAGE = 24924,
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
    SPELL_PROXIMITY_CONTROL_MASTER = 71917, // trigger unknown spell 71920
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
    SPELL_FROST_NOVA = 11831,
    SPELL_FROST_BOLD = 9672,
    SPELL_ROCKETS_BOOTS_DAMAGE_EFFECT_72886 = 72886,
};

Creature* FindNearestTarget(std::list<Creature*>cList, Unit* source)
{

    float dist = 1000;
    Creature* cDist = nullptr;
    if (Creature* attacker = source->ToCreature())
        for (auto npc : cList)
            if (npc->IsInCombat() == false)
                if (attacker->CanStartAttack(npc, false))
                {
                    float d1 = source->GetExactDist(npc);
                    if (d1 < dist)
                    {
                        dist = d1;
                        cDist = npc;
                    }
                }
    return cDist;
}

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
                    std::list<Player*> pList = me->FindNearestPlayers(10.0f);
                    for (std::list<Player*>::const_iterator itr = pList.begin(); itr != pList.end(); ++itr)
                        if (CheckFirstPlayerArrival(*itr))
                            if (playerList.find((*itr)->GetGUID()) == playerList.end())
                                playerList.insert((*itr)->GetGUID());

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
                        player->SetControlled(false, UNIT_STATE_STUNNED);
                        player->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_STUNNED | UNIT_FLAG_PACIFIED);
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
            if (player->GetQuestStatus(QUEST_DONT_GO_INTO_THE_LIGHT) != QUEST_STATUS_REWARDED)
                if (!player->HasUnitState(UNIT_STATE_STUNNED))
                {
                    player->NearTeleportTo(533.97f, 3274.55f, 0.21f, 5.015f);
                    player->AddAura(SPELL_COSMETIC_STATE_DEATH, player);
                    player->SetControlled(true, UNIT_STATE_STUNNED);
                    player->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_STUNNED | UNIT_FLAG_PACIFIED);
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

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case 24942:
            creature->AI()->Talk(0, player);
            break;
        case 24952:
            creature->AI()->Talk(2, player);
            break;
        }
        return false;
    }

    struct npc_coach_crosscheck_38738AI : public ScriptedAI
    {
        npc_coach_crosscheck_38738AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset()
        {
            DoStartNoMovement(me);
            me->SetReactState(REACT_DEFENSIVE);
            if (me->HasInPhaseList(181))
                m_events.RescheduleEvent(EVENT_TALK_PART_00, urand(45000, 60000));
                
        }

        void CreatureMoveInLineOfSight(Unit* who)
        {
            if (CheckHomePosition())
                if (who->HasInPhaseList(181))
                    if (who->GetEntry() == NPC_OOMLOT_WARRIOR_38531)
                        if (who->GetDistance(me) < 10.0f)
                            AttackStart(who);
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

        bool CheckHomePosition()
        {
            float dist = me->GetDistance(me->GetHomePosition());
            if (dist > 10.0f)
            {
                me->AttackStop();
                me->GetMotionMaster()->MovePoint(2016, me->GetHomePosition());
                return false;
            }
            else
                return true;
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
            player->CastSpell(player, 68421, true);
            creature->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
            creature->AI()->DoAction(101);            
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

    struct npc_thrall_36145AI : public ScriptedAI
    {
        npc_thrall_36145AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;

        void Reset() override
        {
            m_playerGUID = 0;
        }

        void DoAction(int32 /*param*/) override 
        { 
            m_events.ScheduleEvent(EVENT_SPAWN_OBJECT_00, 100);
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
                case EVENT_SPAWN_OBJECT_00:
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        player->CastSpell(993.1458f, 3852.019f, 3.2269f, 69079, true);
                    break;
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
        return new npc_thrall_36145AI(creature);
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
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
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

// 23837
class npc_elm_general_purpose_bunny_23837 : public CreatureScript
{
public:
    npc_elm_general_purpose_bunny_23837() : CreatureScript("npc_elm_general_purpose_bunny_23837") { }

    struct npc_elm_general_purpose_bunny_23837AI : public ScriptedAI
    {
        npc_elm_general_purpose_bunny_23837AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap  m_events;
        std::set<uint64> m_zombieList;

        void Reset() override
        {
            if (abs(me->GetPositionX() - 876.2f) < 5 && abs(me->GetPositionY() - 2747.1f) < 5)
                m_events.RescheduleEvent(EVENT_PLAY_PERIODIC_SOUND, 7250);
            else if (me->GetAreaId() == 4886)
                m_events.RescheduleEvent(EVENT_CAST_SPELL_00, 1000);
            else if (me->GetAreaId() == 4899)
                m_events.RescheduleEvent(EVENT_SPAWN_OBJECT_00, 1000);
        }

        void JustSummoned(Creature* summon) override
        {
            if (m_zombieList.find(summon->GetGUID()) == m_zombieList.end())
                m_zombieList.insert(summon->GetGUID());
        }

        void SummonedCreatureDespawn(Creature* summon) override
        {
            m_zombieList.erase(summon->GetGUID());
        }

        void SummonedCreatureDies(Creature* summon, Unit* killer) override
        {
            m_zombieList.erase(summon->GetGUID());
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_PLAY_PERIODIC_SOUND:
                {
                    me->PlayDirectSound(16459);
                    m_events.ScheduleEvent(EVENT_PLAY_PERIODIC_SOUND, 7250);
                    break;
                }
                case EVENT_CAST_SPELL_00:
                {
                    me->CastSpell(me, 72382, true);
                        m_events.ScheduleEvent(EVENT_CAST_SPELL_00, 15500);
                    break;
                }
                case EVENT_SPAWN_OBJECT_00:
                {
                    if (m_zombieList.size() < 4)
                    {
                        Position pos = Position(frand(1471.4f, 1479.4f), frand(1971.5f, 1979.5f), 238.076904f, 1.490936f);
                        me->SummonCreature(RAND(38813, 38816), pos, TEMPSUMMON_TIMED_DESPAWN, 180000);
                    }
                    m_events.ScheduleEvent(EVENT_SPAWN_OBJECT_00, urand(10000, 15000));
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_elm_general_purpose_bunny_23837AI(creature);
    }
};

// 36525
class npc_warrior_matic_nx__36525 : public CreatureScript
{
public:
    npc_warrior_matic_nx__36525() : CreatureScript("npc_warrior_matic_nx__36525") { }

    struct npc_warrior_matic_nx__36525AI : public ScriptedAI
    {
        npc_warrior_matic_nx__36525AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap  m_events;

        void Reset() override
        {
            m_events.RescheduleEvent(EVENT_PLAY_PERIODIC_SOUND, 30000);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_PLAY_PERIODIC_SOUND:
                {
                    me->PlayDirectSound(2304);
                    me->HandleEmote(33);
                    m_events.ScheduleEvent(EVENT_PLAY_PERIODIC_SOUND, 30000);
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_warrior_matic_nx__36525AI(creature);
    }
};

// 36425 
class npc_sassy_hardwrench_36425 : public CreatureScript
{
public:
    npc_sassy_hardwrench_36425() : CreatureScript("npc_sassy_hardwrench_36425") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case 14244:
            creature->AI()->Talk(0, player);
            player->CastSpell(player, 68815, true);
            break;
        }
        return false;
    }
};

// 36421 
class npc_orc_survivor_36421 : public CreatureScript
{
public:
    npc_orc_survivor_36421() : CreatureScript("npc_orc_survivor_36421") { }

    struct npc_orc_survivor_36421AI : public ScriptedAI
    {
        npc_orc_survivor_36421AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap  m_events;

        void Reset() override
        {
            m_events.RescheduleEvent(EVENT_PLAY_PERIODIC_EMOTE, 5000);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_PLAY_PERIODIC_SOUND:
                {
                    me->HandleEmote(1);
                    m_events.ScheduleEvent(EVENT_PLAY_PERIODIC_EMOTE, urand(5000, 10000));
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_orc_survivor_36421AI(creature);
    }
};

// 36513 
class npc_trade_prince_gallywix_36513 : public CreatureScript
{
public:
    npc_trade_prince_gallywix_36513() : CreatureScript("npc_trade_prince_gallywix_36513") { }

    struct npc_trade_prince_gallywix_36513AI : public ScriptedAI
    {
        npc_trade_prince_gallywix_36513AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap  m_events;
        uint64    m_playerGUID;
        bool      m_talkIsStarted;

        void Reset() override
        {           
            m_playerGUID = 0;
            m_talkIsStarted = false;
            m_events.RescheduleEvent(EVENT_MASTER_RESET, 120000);
            m_events.RescheduleEvent(EVENT_PLAY_PERIODIC_EMOTE, 1000);
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                me->SetFacingToObject(player);
                if (player->GetQuestStatus(14244) == QUEST_STATUS_INCOMPLETE)
                    if (player->GetPosition().GetExactDist2d(me) < 15.0f)
                    {
                        m_talkIsStarted = true;
                        m_playerGUID = player->GetGUID();
                        m_events.ScheduleEvent(EVENT_TALK_PART_00, 3000);
                        m_events.RescheduleEvent(EVENT_MASTER_RESET, 120000);
                    }
            }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == POINT_MOTION_TYPE)
                if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    switch (id)
                    {
                    case 1025:
                    {
                        me->CastSpell(player, 68819, true);
                        me->DespawnOrUnsummon(100);
                        m_playerGUID = 0;
                        m_talkIsStarted = false;
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
                case EVENT_MASTER_RESET:
                    me->DespawnOrUnsummon(10);
                    break;
                case EVENT_PLAY_PERIODIC_EMOTE:
                {
                    if (!m_talkIsStarted)
                        me->HandleEmote(RAND(5, 14, 15));

                    m_events.RescheduleEvent(EVENT_PLAY_PERIODIC_EMOTE, urand(4000, 8000));
                    break;
                }
                case EVENT_TALK_PART_00:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        me->SetFacingToObject(player);
                        Talk(0, player);
                    }
                    m_events.ScheduleEvent(EVENT_TALK_PART_01, 10000);
                    break;
                }
                case EVENT_TALK_PART_01:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        Talk(1, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_02, 12000);
                    break;
                }
                case EVENT_TALK_PART_02:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        Talk(2, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_03, 5000);
                    break;
                }
                case EVENT_TALK_PART_03:
                {
                    me->SetWalk(true);
                    me->GetMotionMaster()->MovePoint(1025, 872.27f, 2743.14f, 122.82f);
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_trade_prince_gallywix_36513AI(creature);
    }
};

// 36514
class npc_sling_rocket_36514 : public CreatureScript
{
public:
    npc_sling_rocket_36514() : CreatureScript("npc_sling_rocket_36514") { }

    struct npc_sling_rocket_36514AI : public VehicleAI
    {
        npc_sling_rocket_36514AI(Creature* creature) : VehicleAI(creature) { }

        EventMap  m_events;
        uint64    m_playerGUID;

        void Reset() override
        {
            m_playerGUID = 0;
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                me->CastSpell(me, 66110); //  Rocket Scouting: Rocket Blast
                me->SetDisableGravity(true);
                me->SetCanFly(true);
                me->SetSpeed(MOVE_RUN, 3.0f);
                me->GetMotionMaster()->MovePath(3651401, true);
            }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == WAYPOINT_MOTION_TYPE && id == 2)
                me->DespawnOrUnsummon(2000);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_sling_rocket_36514AI(creature);
    }
};

// 196439  
class go_rocket_sling_196439 : public GameObjectScript
{
public:
    go_rocket_sling_196439() : GameObjectScript("go_rocket_sling_196439") { }

    bool OnGossipSelect(Player* player, GameObject* go, uint32 sender, uint32 action) override
    {
        if (player->GetQuestStatus(14244) == QUEST_STATUS_INCOMPLETE)
        {
            player->CastSpell(player, 68806, true); // Up, Up & Away!: Force Cast from Rocket Sling
            player->CLOSE_GOSSIP_MENU();
            return true;
        }
        
        return false;
    }
};

// 36505
class npc_sling_rocket_36505 : public CreatureScript
{
public:
    npc_sling_rocket_36505() : CreatureScript("npc_sling_rocket_36505") { }

    enum eNPC
    {
    };

    struct npc_sling_rocket_36505AI : public VehicleAI
    {
        npc_sling_rocket_36505AI(Creature* creature) : VehicleAI(creature) { Initialize(); }

        EventMap  m_events;
        uint64    m_playerGUID;

        void Initialize()
        {
            m_playerGUID = 0;
        }

        void Reset() override
        {
            me->SetCanFly(true);
            me->SetDisableGravity(true);
            me->SetSpeed(MOVE_FLIGHT, 3.5f);
            me->SetSpeed(MOVE_RUN, 3.5f);
            me->SetSpeed(MOVE_WALK, 3.5f);
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                me->CastSpell(me, 66110, true); //  Rocket Scouting: Rocket Blast
            }
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override
        {
            if (Player* player = passenger->ToPlayer())
                if (apply)
                {
                    m_events.ScheduleEvent(EVENT_START_FLYING, 1000);
                }
                else
                {
                    me->CastSpell(player, 68813, true); // Up, Up & Away!: Force Cast + trigger 66127: Kill Credit + Explosion
                    me->DespawnOrUnsummon(10);
                }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == WAYPOINT_MOTION_TYPE && id == 8)
                if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    me->CastSpell(player, 68576); // passenger exit 
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_FLYING:
                    me->GetMotionMaster()->MovePath(3650501, false);
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_sling_rocket_36505AI(creature);
    }
};

// 36470
class npc_foreman_dampwick_36470 : public CreatureScript
{
public:
    npc_foreman_dampwick_36470() : CreatureScript("npc_foreman_dampwick_36470") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case 14245:
        {           
            creature->AI()->Talk(0, player);
            break;
        }
        }
        return false;
    }
};

/*  phase 180  */

// 36471
class npc_foreman_dampwick_36471 : public CreatureScript
{
public:
    npc_foreman_dampwick_36471() : CreatureScript("npc_foreman_dampwick_36471") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case 27139:
        {
            creature->AI()->Talk(0, player);
            break;
        }
        case 24945:
        {
            creature->AI()->Talk(1, player);
            break;
        }
        }
        return false;
    }

    bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* quest, uint32 /*opt*/) 
    { 
        switch (quest->GetQuestId())
        {
        case 27245:
        {
            player->SetInPhase(179, false, false);
            break;
        }
        }
        return false; 
    }

    struct npc_foreman_dampwick_36471AI : public ScriptedAI
    {
        npc_foreman_dampwick_36471AI(Creature* creature) : ScriptedAI(creature) { }

        void Reset()
        {
            DoStartNoMovement(me);
            me->SetReactState(REACT_DEFENSIVE);
        }

        void CreatureMoveInLineOfSight(Unit* who) override
        {
            if (CheckHomePosition())
                if (who->HasInPhaseList(181))
                    if (who->GetEntry() == NPC_OOMLOT_WARRIOR_38531)
                        if (who->GetDistance(me) < 10.0f)
                            AttackStart(who);
        }

        bool CheckHomePosition()
        {
            float dist = me->GetDistance(me->GetHomePosition());
            if (dist > 10.0f)
            {
                me->AttackStop();
                me->GetMotionMaster()->MovePoint(2016, me->GetHomePosition());
                return false;
            }
            else
            {
                return true;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_foreman_dampwick_36471AI(creature);
    }
};

// 38511
class npc_sally_salvager_sandscrew_38511 : public CreatureScript
{
public:
    npc_sally_salvager_sandscrew_38511() : CreatureScript("npc_sally_salvager_sandscrew_38511") { }

    struct npc_sally_salvager_sandscrew_38511AI : public ScriptedAI
    {
        npc_sally_salvager_sandscrew_38511AI(Creature* creature) : ScriptedAI(creature) { }

        void Reset()
        {
            if (me->GetAreaId() == 4909)
            {

            }
            else
            {
                DoStartNoMovement(me);
                me->SetReactState(REACT_DEFENSIVE);
            }
        }

        void CreatureMoveInLineOfSight(Unit* who) override
        {
            if (CheckHomePosition())
                if (who->HasInPhaseList(181))
                    if (who->GetEntry() == NPC_OOMLOT_WARRIOR_38531)
                        if (who->GetDistance(me) < 10.0f)
                            AttackStart(who);
        }

        bool CheckHomePosition()
        {
            float dist = me->GetDistance(me->GetHomePosition());
            if (dist > 10.0f)
            {
                me->AttackStop();
                me->GetMotionMaster()->MovePoint(2016, me->GetHomePosition());
                return false;
            }
            else
            {
                return true;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_sally_salvager_sandscrew_38511AI(creature);
    }
};

// 38513
class npc_evol_fingers_38513 : public CreatureScript
{
public:
    npc_evol_fingers_38513() : CreatureScript("npc_evol_fingers_38513") { }

    struct npc_evol_fingers_38513AI : public ScriptedAI
    {
        npc_evol_fingers_38513AI(Creature* creature) : ScriptedAI(creature) { }

        void Reset()
        {
            DoStartNoMovement(me);
            me->SetReactState(REACT_DEFENSIVE);
            me->CastSpell(me, 44163);            
        }

        void CreatureMoveInLineOfSight(Unit* who) override
        {
            if (CheckHomePosition())
                if (who->HasInPhaseList(181))
                    if (who->GetEntry() == NPC_OOMLOT_WARRIOR_38531)
                        if (who->GetDistance(me) < 10.0f)
                            AttackStart(who);
        }

        bool CheckHomePosition()
        {
            float dist = me->GetDistance(me->GetHomePosition());
            if (dist > 10.0f)
            {
                me->AttackStop();
                me->GetMotionMaster()->MovePoint(2016, me->GetHomePosition());
                return false;
            }
            else
            {
                return true;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_evol_fingers_38513AI(creature);
    }
};

// 38120
class npc_hobart_grapplehammer_38120 : public CreatureScript
{
public:
    npc_hobart_grapplehammer_38120() : CreatureScript("npc_hobart_grapplehammer_38120") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case 24671:
        {
            creature->AI()->Talk(3, player);
            break;
        }
        case 24744:
        {
            creature->AI()->Talk(4, player);
            break;
        }
        case 24958:
        {
            creature->AI()->Talk(7, player);
            break;
        }
        }
        return false;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/) 
    { 
        switch (quest->GetQuestId())
        {
        case 24671:
        {
            if (Creature* bamm = creature->FindNearestCreature(38122, 30.0f))
                bamm->AI()->Talk(0, player);
            break;
        }
        case 24744:
        {
            creature->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
            creature->AI()->DoAction(1);
            break;
        }
        }
        return false; 
    }

    struct npc_hobart_grapplehammer_38120AI : public ScriptedAI
    {
        npc_hobart_grapplehammer_38120AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap  m_events;
        uint64    m_playerGUID;
        uint64    m_greelyGUID;
        uint64    m_bunnyGUID;

        void Reset() override
        {
            m_playerGUID = 0;
            m_greelyGUID = 0;
            m_bunnyGUID = 0;
            DoStartNoMovement(me);
            me->SetReactState(REACT_DEFENSIVE);
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case 1:
                m_events.RescheduleEvent(EVENT_START_TALK, 2000);
                break;
            }
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case PLAYER_GUID:
                m_playerGUID = guid;
                break;
            }
        }

        void CreatureMoveInLineOfSight(Unit* who) override
        {
            if (CheckHomePosition())
                if (who->HasInPhaseList(181))
                    if (who->GetEntry() == NPC_OOMLOT_WARRIOR_38531)
                        if (who->GetDistance(me) < 10.0f)
                            AttackStart(who);
        }

        bool CheckHomePosition()
        {
            float dist = me->GetDistance(me->GetHomePosition());
            if (dist > 10.0f)
            {
                me->AttackStop();
                me->GetMotionMaster()->MovePoint(2016, me->GetHomePosition());
                return false;
            }
            else
                return true;
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_TALK:
                {
                    if (!m_greelyGUID)
                        if (Creature* greely = me->FindNearestCreature(38124, 30.0f))
                            m_greelyGUID = greely->GetGUID();

                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        Talk(0, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_01, 2000);
                    break;
                }
                case EVENT_TALK_PART_01:
                {
                    if (Creature* greely = ObjectAccessor::GetCreature(*me, m_greelyGUID))
                        if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                            greely->AI()->Talk(0, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_02, 7000);
                    break;
                }
                case EVENT_TALK_PART_02:
                {
                    if (Creature* greely = ObjectAccessor::GetCreature(*me, m_greelyGUID))
                        if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                            greely->AI()->Talk(1, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_03, 7000);
                    break;
                }
                case EVENT_TALK_PART_03:
                {
                    if (Creature* greely = ObjectAccessor::GetCreature(*me, m_greelyGUID))
                        if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                            greely->AI()->Talk(2, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_04, 3000);
                    break;
                }
                case EVENT_TALK_PART_04:
                {
                    if (!m_bunnyGUID)
                        if (Creature* greely = ObjectAccessor::GetCreature(*me, m_greelyGUID))
                            if (Creature* bunny = greely->FindNearestCreature(24021, 15.0f))
                                m_bunnyGUID = bunny->GetGUID();

                    if (Creature* bunny = ObjectAccessor::GetCreature(*me, m_bunnyGUID))
                    {
                        bunny->CastSpell(bunny, 71608);
                        bunny->CastSpell(bunny, 71608);
                        bunny->CastSpell(bunny, 71608);
                        bunny->CastSpell(bunny, 71608);
                        bunny->CastSpell(bunny, 71608);
                    }
                    m_events.ScheduleEvent(EVENT_TALK_PART_05, 1000);
                    break;
                }
                case EVENT_TALK_PART_05:
                {
                    if (Creature* bunny = ObjectAccessor::GetCreature(*me, m_bunnyGUID))
                    {
                        bunny->CastSpell(bunny, 71608);
                        bunny->CastSpell(bunny, 71608);
                        bunny->CastSpell(bunny, 71608);
                    }

                    m_events.ScheduleEvent(EVENT_TALK_PART_06, 1000);
                    break;
                }
                case EVENT_TALK_PART_06:
                {
                    if (Creature* bunny = ObjectAccessor::GetCreature(*me, m_bunnyGUID))
                    {
                        bunny->CastSpell(bunny, 71608);
                        bunny->CastSpell(bunny, 71608);
                        bunny->CastSpell(bunny, 71608);
                    }

                    m_events.ScheduleEvent(EVENT_TALK_PART_07, 1000);
                    break;
                }
                case EVENT_TALK_PART_07:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        Talk(1, player);
                    if (Creature* bunny = ObjectAccessor::GetCreature(*me, m_bunnyGUID))
                    {
                        bunny->CastSpell(bunny, 71608);
                        bunny->CastSpell(bunny, 71608);
                        bunny->CastSpell(bunny, 71608);
                    }

                    m_events.ScheduleEvent(EVENT_TALK_PART_08, 1000);
                    break;
                }
                case EVENT_TALK_PART_08:
                {
                    if (Creature* bunny = ObjectAccessor::GetCreature(*me, m_bunnyGUID))
                    {
                        bunny->CastSpell(bunny, 71608);
                        bunny->CastSpell(bunny, 71608);
                    }
                    m_events.ScheduleEvent(EVENT_TALK_PART_09, 1000);
                    break;
                }
                case EVENT_TALK_PART_09:
                {
                    if (Creature* bunny = ObjectAccessor::GetCreature(*me, m_bunnyGUID))
                    {
                        bunny->CastSpell(bunny, 71608);
                        bunny->CastSpell(bunny, 71608);
                    }

                    m_events.ScheduleEvent(EVENT_TALK_PART_10, 1000);
                    break;
                }
                case EVENT_TALK_PART_10:
                {
                    if (Creature* bunny = ObjectAccessor::GetCreature(*me, m_bunnyGUID))
                        bunny->CastSpell(bunny, 71608);

                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_hobart_grapplehammer_38120AI(creature);
    }
};

// 38122
class npc_bamm_megabomb_38122 : public CreatureScript
{
public:
    npc_bamm_megabomb_38122() : CreatureScript("npc_bamm_megabomb_38122") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case 24741:
        {
            creature->AI()->Talk(1, player);
            break;
        }
        }
        return false;
    }

    bool OnQuestObjectiveComplete(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case 24741:
        {
            if (Creature* hobart = creature->FindNearestCreature(38120, 30.0f))
                hobart->AI()->Talk(2, player);
            break;
        }
        }
        return false;
    }

    struct npc_bamm_megabomb_38122AI : public ScriptedAI
    {
        npc_bamm_megabomb_38122AI(Creature* creature) : ScriptedAI(creature) { }

        void Reset()
        {
            DoStartNoMovement(me);
            me->SetReactState(REACT_DEFENSIVE);
        }

        void CreatureMoveInLineOfSight(Unit* who) override
        {
            if (CheckHomePosition())
                if (who->HasInPhaseList(181))
                    if (who->GetEntry() == NPC_OOMLOT_WARRIOR_38531)
                        if (who->GetDistance(me) < 10.0f)
                            AttackStart(who);
        }

        bool CheckHomePosition()
        {
            float dist = me->GetDistance(me->GetHomePosition());
            if (dist > 10.0f)
            {
                me->AttackStop();
                me->GetMotionMaster()->MovePoint(2016, me->GetHomePosition());
                return false;
            }
            else
                return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_bamm_megabomb_38122AI(creature);
    }
};

// 38746
class npc_gobber_38746 : public CreatureScript
{
public:
    npc_gobber_38746() : CreatureScript("npc_gobber_38746") { }

    struct npc_gobber_38746AI : public ScriptedAI
    {
        npc_gobber_38746AI(Creature* creature) : ScriptedAI(creature) { }

        void Reset()
        {
            DoStartNoMovement(me);
            me->SetReactState(REACT_DEFENSIVE);
        }

        void CreatureMoveInLineOfSight(Unit* who) override
        {
            if (CheckHomePosition())
                if (who->HasInPhaseList(181))
                    if (who->GetEntry() == NPC_OOMLOT_WARRIOR_38531)
                        if (who->GetDistance(me) < 10.0f)
                            AttackStart(who);
        }

        bool CheckHomePosition()
        {
            float dist = me->GetDistance(me->GetHomePosition());
            if (dist > 10.0f)
            {
                me->AttackStop();
                me->GetMotionMaster()->MovePoint(2016, me->GetHomePosition());
                return false;
            }
            else
            {
                return true;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_gobber_38746AI(creature);
    }
};

// 38111
class npc_wild_clucker_38111 : public CreatureScript
{
public:
    npc_wild_clucker_38111() : CreatureScript("npc_wild_clucker_38111") { }

    struct npc_wild_clucker_38111AI : public ScriptedAI
    {
        npc_wild_clucker_38111AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap  m_events;
        uint64    m_playerGUID;
        bool      m_isFinished;

        void Reset() override
        {
            me->RemoveAllAuras();
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
            m_playerGUID = 0;
            m_isFinished = false;
        }

        void CreatureMoveInLineOfSight(Unit* who) override
        {
            if (!me->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK) && !m_isFinished)
                if (Player* player = who->ToPlayer())
                    if (player->GetQuestStatus(24671) == QUEST_STATUS_INCOMPLETE)
                    {
                        m_playerGUID = player->GetGUID();
                        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                        m_events.RescheduleEvent(EVENT_MASTER_RESET, 10000);
                        return;
                    }
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override 
        { 
            if (Player* player = caster->ToPlayer())
                if (player->GetQuestStatus(24671) == QUEST_STATUS_INCOMPLETE)
                {
                    m_playerGUID = player->GetGUID();
                    m_isFinished = true;
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                    player->KilledMonsterCredit(38117);
                    m_events.RescheduleEvent(EVENT_DESPAWN_PART_00, 10000);
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
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        if (player->GetQuestStatus(24671) != QUEST_STATUS_INCOMPLETE)
                        {
                            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                            break;
                        }
                    m_events.RescheduleEvent(EVENT_MASTER_RESET, 10000);
                    break;
                case EVENT_DESPAWN_PART_00:
                    me->DespawnOrUnsummon();
                    break;
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
        return new npc_wild_clucker_38111AI(creature);
    }
};

// 201972  
class go_raptor_trap_201972 : public GameObjectScript
{
public:
    go_raptor_trap_201972() : GameObjectScript("go_raptor_trap_201972") { }

    struct go_raptor_trap_201972AI : public GameObjectAI
    {
        go_raptor_trap_201972AI(GameObject* go) : GameObjectAI(go) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_raptorGUID;

        void Reset() override
        {
            m_playerGUID = 0;
            m_raptorGUID = 0;
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
            case NPC_RAPTOR_38187:
            {
                m_raptorGUID = guid;
                break;
            }
            }
        }

        void OnStateChanged(uint32 state, Unit* unit) override
        {
            switch (state)
            {
            case GO_STATE_ACTIVE_ALTERNATIVE:
            {
                if (Player* player = ObjectAccessor::GetPlayer(*go, m_playerGUID))
                    if (Creature* raptor = ObjectAccessor::GetCreature(*go, m_raptorGUID))
                    {
                        raptor->CastSpell(raptor, 35309, true);
                        raptor->CastSpell(raptor, 29266, true);
                        raptor->AddUnitState(UNIT_STATE_STUNNED);
                        raptor->CastSpell(raptor, 66723, true);
                        m_events.ScheduleEvent(EVENT_CAST_COOLDOWN_01, 30000);
                    }
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
                case EVENT_CAST_COOLDOWN_01:
                {
                    if (Creature* raptor = ObjectAccessor::GetCreature(*go, m_raptorGUID))
                        raptor->DealDamage(raptor, raptor->GetHealth() + 1);
                    go->ResetDoorOrButton();
                    break;
                }
                }
            }
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_raptor_trap_201972AI(go);
    }
};

// 38195
class npc_wild_clucker_egg_38195 : public CreatureScript
{
public:
    npc_wild_clucker_egg_38195() : CreatureScript("npc_wild_clucker_egg_38195") { }

    struct npc_wild_clucker_egg_38195AI : public ScriptedAI
    {
        npc_wild_clucker_egg_38195AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap  m_events;
        uint64    m_playerGUID;
        uint64    m_raptorGUID;
        uint64    m_trapGUID;

        void Reset() override
        {
            m_playerGUID = me->GetOwnerGUID();
            me->AddUnitState(UNIT_STATE_STUNNED);
            m_events.ScheduleEvent(EVENT_FIND_TARGET, 500);
        }

        void DoAction(int32 param) override
        {
            if (param)
                m_events.ScheduleEvent(EVENT_SPAWN_OBJECT_00, 500);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);            

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_FIND_TARGET:
                {
                    GetOrCreateRaptorTarget();
                    GetTrapTarget();
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        if (Creature* raptor = ObjectAccessor::GetCreature(*me, m_raptorGUID))
                            if (GameObject* trap = ObjectAccessor::GetGameObject(*me, m_trapGUID))
                            {
                                raptor->AI()->SetGUID(m_playerGUID, PLAYER_GUID);
                                raptor->AI()->SetGUID(m_trapGUID, GO_TRAP_201972);
                                raptor->AI()->SetGUID(me->GetGUID(), me->GetEntry());
                                raptor->AI()->DoAction(1);
                                trap->AI()->SetGUID(m_playerGUID, PLAYER_GUID);
                                trap->AI()->SetGUID(m_raptorGUID, NPC_RAPTOR_38187);
                            }

                    break;
                }
                case EVENT_SPAWN_OBJECT_00:
                {
                    me->CastSpell(me, 66726, true);
                    m_events.ScheduleEvent(EVENT_DESPAWN_PART_00, 100);
                    break;
                }
                case EVENT_DESPAWN_PART_00:
                {
                    me->DespawnOrUnsummon();
                    break;
                }
                }
            }
        }

        void GetOrCreateRaptorTarget()
        {
            m_raptorGUID = 0;
            Creature* raptor = me->FindNearestCreature(38187, 30.0f);
            if (!raptor)
                if (raptor = me->FindNearestCreature(38187, 30.0f, false))
                    raptor->Respawn();
            if (raptor)
            {
                m_raptorGUID = raptor->GetGUID();
                raptor->RemoveAllAuras();
                raptor->ClearUnitState(UNIT_STATE_STUNNED);
            }
        }

        void GetTrapTarget()
        {
            m_trapGUID = 0;
            if (GameObject* trap = me->FindNearestGameObject(201972, 3.0f))
                m_trapGUID = trap->GetGUID();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_wild_clucker_egg_38195AI(creature);
    }
};

// 38187
class npc_spiny_raptor_38187 : public CreatureScript
{
public:
    npc_spiny_raptor_38187() : CreatureScript("npc_spiny_raptor_38187") { }

    struct npc_spiny_raptor_38187AI : public ScriptedAI
    {
        npc_spiny_raptor_38187AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap  m_events;
        uint64    m_playerGUID;
        uint64    m_trapGUID;
        uint64    m_cluckEggGUID;

        void Initialize()
        {
            m_playerGUID = 0;
            m_trapGUID = 0;
            m_cluckEggGUID = 0;
        }

        void Reset() override
        {
            me->ClearUnitState(UNIT_STATE_STUNNED);
            me->RemoveAura(29266);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
            me->SetReactState(REACT_AGGRESSIVE);
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case PLAYER_GUID:
                m_playerGUID = guid;
                break;
            case GO_TRAP_201972:
                m_trapGUID = guid;
                break;
            case NPC_WILD_CLUCKER_EGG_38195:
                m_cluckEggGUID = guid;
                break;
            }
        }

        void DoAction(int32 param) override 
        { 
            if (m_playerGUID && m_trapGUID && param)
            {
                m_events.ScheduleEvent(EVENT_START_WALK, 100);
                m_events.ScheduleEvent(EVENT_MASTER_RESET, 15000);
            }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == POINT_MOTION_TYPE && id == 1027)
                if (GameObject* trap = ObjectAccessor::GetGameObject(*me, m_trapGUID))
                    trap->UseDoorOrButton();
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (spell->Id == 66723)
                m_events.ScheduleEvent(EVENT_TRIGGER_TRAP, 2500);
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
                    Reset();
                    me->GetMotionMaster()->MoveTargetedHome();
                    break;
                }
                case EVENT_START_WALK:
                {
                    me->SetReactState(REACT_PASSIVE);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
                    if (GameObject* trap = ObjectAccessor::GetGameObject(*me, m_trapGUID))
                        me->GetMotionMaster()->MovePoint(1027, trap->GetPosition());
                    break;
                }
                case EVENT_TRIGGER_TRAP:
                {
                    if (Creature* egg = ObjectAccessor::GetCreature(*me, m_cluckEggGUID))
                        egg->AI()->DoAction(2);
                    m_events.ScheduleEvent(EVENT_DESPAWN_PART_00, 500);
                    break;
                }
                case EVENT_DESPAWN_PART_00:
                {
                    m_events.Reset();
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
        return new npc_spiny_raptor_38187AI(creature);
    }
};

// 38224
class npc_mechachicken_38224 : public CreatureScript
{
public:
    npc_mechachicken_38224() : CreatureScript("npc_mechachicken_38224") { }

    struct npc_mechachicken_38224AI : public ScriptedAI
    {
        npc_mechachicken_38224AI(Creature* creature) : ScriptedAI(creature) { }

        void JustDied(Unit* killer) override 
        { 
            if (Player* player = killer->ToPlayer())
                if (player->GetQuestStatus(24744) == QUEST_STATUS_INCOMPLETE)
                    me->CastSpell(me, 71422, true);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_mechachicken_38224AI(creature);
    }
};

// 38227
class npc_the_biggest_egg_ever_spell_visual_38227 : public CreatureScript
{
public:
    npc_the_biggest_egg_ever_spell_visual_38227() : CreatureScript("npc_the_biggest_egg_ever_spell_visual_38227") { }

    struct npc_the_biggest_egg_ever_spell_visual_38227AI : public ScriptedAI
    {
        npc_the_biggest_egg_ever_spell_visual_38227AI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            me->SummonGameObject(201977, me->m_positionX, me->m_positionY, me->m_positionZ, me->m_orientation, 0, 0, 0, 0, 0);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_the_biggest_egg_ever_spell_visual_38227AI(creature);
    }
};

// 38124
class npc_assistant_greely_38124 : public CreatureScript
{
public:
    npc_assistant_greely_38124() : CreatureScript("npc_assistant_greely_38124") { }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (creature->HasInPhaseList(182))
        {
            player->PrepareQuestMenu(creature->GetGUID());
            player->ADD_GOSSIP_ITEM_DB(11082, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->SEND_GOSSIP_MENU(15419, creature->GetGUID());
            return true;
        }

        return false;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        if (creature->HasInPhaseList(182))
            switch (action)
            {
            case 1001:
                player->PlayerTalkClass->ClearMenus();
                player->SEND_GOSSIP_MENU(15428, creature->GetGUID());
                return true;
                break;
            }

        return false;
    }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case 24817:
        {
            creature->AI()->Talk(3, player);
            break;
        }
        case 24946:
        {
            creature->AI()->Talk(4, player);
            break;
        }
        }
        return false;
    }

    struct npc_assistant_greely_38124AI : public ScriptedAI
    {
        npc_assistant_greely_38124AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset()
        {
            DoStartNoMovement(me);
            me->SetReactState(REACT_DEFENSIVE);
        }

        void CreatureMoveInLineOfSight(Unit* who) override
        {
            if (CheckHomePosition())
                if (who->HasInPhaseList(181))
                    if (who->GetEntry() == NPC_OOMLOT_WARRIOR_38531)
                        if (who->GetDistance(me) < 10.0f)
                            AttackStart(who);
        }

        bool CheckHomePosition()
        {
            float dist = me->GetDistance(me->GetHomePosition());
            if (dist > 10.0f)
            {
                me->AttackStop();
                me->GetMotionMaster()->MovePoint(2016, me->GetHomePosition());
                return false;
            }
            else
                return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_assistant_greely_38124AI(creature);
    }
};

// 38118
class npc_warrior_matic_nx__38518 : public CreatureScript
{
public:
    npc_warrior_matic_nx__38518() : CreatureScript("npc_warrior_matic_nx__38518") { }

    struct npc_warrior_matic_nx__38518AI : public ScriptedAI
    {
        npc_warrior_matic_nx__38518AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset()
        {
            DoStartNoMovement(me);
            me->SetReactState(REACT_DEFENSIVE);
        }

        void CreatureMoveInLineOfSight(Unit* who) override
        {
            if (CheckHomePosition())
                if (who->HasInPhaseList(181))
                    if (who->GetEntry() == NPC_OOMLOT_WARRIOR_38531)
                        if (who->GetDistance(me) < 10.0f)
                            AttackStart(who);
        }

        bool CheckHomePosition()
        {
            float dist = me->GetDistance(me->GetHomePosition());
            if (dist > 10.0f)
            {
                me->AttackStop();
                me->GetMotionMaster()->MovePoint(2016, me->GetHomePosition());
                return false;
            }
            else
                return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_warrior_matic_nx__38518AI(creature);
    }
};

// 38432
class npc_megs_dreadshredder_38432 : public CreatureScript
{
public:
    npc_megs_dreadshredder_38432() : CreatureScript("npc_megs_dreadshredder_38432") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case 24858:
        {
            creature->AI()->Talk(0, player);
            break;
        }
        case QUEST_IRRESISTIBLE_POOL_PONY:
        {
            creature->AI()->Talk(1, player);
            break;
        }
        case QUEST_SURRENDER_OR_ELSE:
        {
            player->CastSpell(player, 72001, true);
            break;
        }
        case QUEST_GET_BACK_TO_TOWN:
        {
            player->RemoveAura(SPELL_QUEST_PHASE_05);
            player->CastSpell(player, 66987, true);
            creature->AI()->Talk(2, player);
            break;
        }
        }
        return false;
    }

    struct npc_megs_dreadshredder_38432AI : public ScriptedAI
    {
        npc_megs_dreadshredder_38432AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset()
        {
            DoStartNoMovement(me);
            me->SetReactState(REACT_DEFENSIVE);
        }

        void CreatureMoveInLineOfSight(Unit* who)
        {
            if (CheckHomePosition())
                if (who->HasInPhaseList(181))
                    if (who->GetEntry() == NPC_OOMLOT_WARRIOR_38531)
                        if (who->GetDistance(me) < 10.0f)
                            AttackStart(who);
        }

        bool CheckHomePosition()
        {
            float dist = me->GetDistance(me->GetHomePosition());
            if (dist > 10.0f)
            {
                me->AttackStop();
                me->GetMotionMaster()->MovePoint(2016, me->GetHomePosition());
                return false;
            }
            else
                return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_megs_dreadshredder_38432AI(creature);
    }
};

// 38381
class npc_brett_coins_mcquid_38381 : public CreatureScript
{
public:
    npc_brett_coins_mcquid_38381() : CreatureScript("npc_brett_coins_mcquid_38381") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case 24859:
        {
            creature->AI()->Talk(0, player);
            break;
        }
        }
        return false;
    }

    struct npc_brett_coins_mcquid_38381AI : public ScriptedAI
    {
        npc_brett_coins_mcquid_38381AI(Creature* creature) : ScriptedAI(creature) { }

        void Reset()
        {
            DoStartNoMovement(me);
            me->SetReactState(REACT_DEFENSIVE);
        }

        void CreatureMoveInLineOfSight(Unit* who)
        {
            if (CheckHomePosition())
                if (who->HasInPhaseList(181))
                    if (who->GetEntry() == NPC_OOMLOT_WARRIOR_38531)
                        if (who->GetDistance(me) < 10.0f)
                            AttackStart(who);
        }

        bool CheckHomePosition()
        {
            float dist = me->GetDistance(me->GetHomePosition());
            if (dist > 10.0f)
            {
                me->AttackStop();
                me->GetMotionMaster()->MovePoint(2016, me->GetHomePosition());
                return false;
            }
            else
                return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_brett_coins_mcquid_38381AI(creature);
    }
};

// 38387 
class npc_sassy_hardwrench_38387 : public CreatureScript
{
public:
    npc_sassy_hardwrench_38387() : CreatureScript("npc_sassy_hardwrench_38387") { }

    struct npc_sassy_hardwrench_38387AI : public ScriptedAI
    {
        npc_sassy_hardwrench_38387AI(Creature* creature) : ScriptedAI(creature) { }

        void Reset()
        {
            DoStartNoMovement(me);
            me->SetReactState(REACT_PASSIVE);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_sassy_hardwrench_38387AI(creature);
    }
};

// 38116
class npc_sister_goldskimmer_38516 : public CreatureScript
{
public:
    npc_sister_goldskimmer_38516() : CreatureScript("npc_sister_goldskimmer_38516") { }

    struct npc_sister_goldskimmer_38516AI : public ScriptedAI
    {
        npc_sister_goldskimmer_38516AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset()
        {
            DoStartNoMovement(me);
            me->SetReactState(REACT_DEFENSIVE);
        }

        void CreatureMoveInLineOfSight(Unit* who)
        {
            if (CheckHomePosition())
                if (who->HasInPhaseList(181))
                    if (who->GetEntry() == NPC_OOMLOT_WARRIOR_38531)
                        if (who->GetDistance(me) < 10.0f)
                            AttackStart(who);
        }

        bool CheckHomePosition()
        {
            float dist = me->GetDistance(me->GetHomePosition());
            if (dist > 10.0f)
            {
                me->AttackStop();
                me->GetMotionMaster()->MovePoint(2016, me->GetHomePosition());
                return false;
            }
            else
                return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_sister_goldskimmer_38516AI(creature);
    }
};

// 38117
class npc_slinky_sharpshiv_38517 : public CreatureScript
{
public:
    npc_slinky_sharpshiv_38517() : CreatureScript("npc_slinky_sharpshiv_38517") { }

    struct npc_slinky_sharpshiv_38517AI : public ScriptedAI
    {
        npc_slinky_sharpshiv_38517AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset()
        {
            DoStartNoMovement(me);
            me->SetReactState(REACT_DEFENSIVE);
        }

        void CreatureMoveInLineOfSight(Unit* who)
        {
            if (CheckHomePosition())
                if (who->HasInPhaseList(181))
                    if (who->GetEntry() == NPC_OOMLOT_WARRIOR_38531)
                        if (who->GetDistance(me) < 10.0f)
                            AttackStart(who);
        }

        bool CheckHomePosition()
        {
            float dist = me->GetDistance(me->GetHomePosition());
            if (dist > 10.0f)
            {
                me->AttackStop();
                me->GetMotionMaster()->MovePoint(2016, me->GetHomePosition());
                return false;
            }
            else
                return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_slinky_sharpshiv_38517AI(creature);
    }
};

// 38114
class npc_fizz_lighter_38514 : public CreatureScript
{
public:
    npc_fizz_lighter_38514() : CreatureScript("npc_fizz_lighter_38514") { }

    struct npc_fizz_lighter_38514AI : public ScriptedAI
    {
        npc_fizz_lighter_38514AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset()
        {
            DoStartNoMovement(me);
            me->SetReactState(REACT_DEFENSIVE);
        }

        void CreatureMoveInLineOfSight(Unit* who)
        {
            if (CheckHomePosition())
                if (who->HasInPhaseList(181))
                    if (who->GetEntry() == NPC_OOMLOT_WARRIOR_38531)
                        if (who->GetDistance(me) < 10.0f)
                            AttackStart(who);
        }

        bool CheckHomePosition()
        {
            float dist = me->GetDistance(me->GetHomePosition());
            if (dist > 10.0f)
            {
                me->AttackStop();
                me->GetMotionMaster()->MovePoint(2016, me->GetHomePosition());
                return false;
            }
            else
                return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_fizz_lighter_38514AI(creature);
    }
};

// 202133  
class go_naga_banner_202133 : public GameObjectScript
{
public:
    go_naga_banner_202133() : GameObjectScript("go_naga_banner_202133") { }

    struct go_naga_banner_202133AI : public GameObjectAI
    {
        go_naga_banner_202133AI(GameObject* go) : GameObjectAI(go) { }

        void OnStateChanged(uint32 state, Unit* unit) override
        {
            switch (state)
            {
            case GO_STATE_ACTIVE_ALTERNATIVE:
            {
                //if (Player* player = unit->ToPlayer())
                //    player->CastSpell(go->m_positionX, go->m_positionY, go->m_positionZ, 71855, true, 0, 0, player->GetGUID());
                break;
            }
            }
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_naga_banner_202133AI(go);
    }
};

// 38359
class npc_vashj_elan_warrior_38359 : public CreatureScript
{
public:
    npc_vashj_elan_warrior_38359() : CreatureScript("npc_vashj_elan_warrior_38359") { }

    struct npc_vashj_elan_warrior_38359AI : public ScriptedAI
    {
        npc_vashj_elan_warrior_38359AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        bool m_spellCast_EnrageCD;

        void Reset()
        {
            m_spellCast_EnrageCD = false;
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (Player* player = who->ToPlayer())
                if (player->GetQuestStatus(QUEST_SURRENDER_OR_ELSE) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_SURRENDER_OR_ELSE) == QUEST_STATUS_COMPLETE)
                    me->AttackStop();
                else
                    if (me->CanStartAttack(who, false))
                        AttackStart(who);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override 
        { 
            if (!m_spellCast_EnrageCD)
                if (me->GetHealthPct() < 40.0f)
                {
                    m_spellCast_EnrageCD = true;
                    m_events.ScheduleEvent(EVENT_CAST_COOLDOWN_01, 120000);
                    Talk(0, attacker);
                    me->CastSpell(me, 8599, true);
                }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CAST_COOLDOWN_01:
                    m_spellCast_EnrageCD = false;
                    break;
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
        return new npc_vashj_elan_warrior_38359AI(creature);
    }
};

// 38360
class npc_vashj_elan_siren_38360 : public CreatureScript
{
public:
    npc_vashj_elan_siren_38360() : CreatureScript("npc_vashj_elan_siren_38360") { }
    /*  
        all hatchling are spawned by naga_siren, urand(3, 6)
        each siren store all spawned hatchlings. when siren die's, send message to following hatchling's  
    */
    struct npc_vashj_elan_siren_38360AI : public ScriptedAI
    {
        npc_vashj_elan_siren_38360AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        bool  m_spellCast_FrostNova_CD;
        bool  m_spellCast_FrostBolt_CD;
        uint8 m_max;
        std::set<uint64> followerList;

        void Reset()
        {
            m_spellCast_FrostNova_CD = false;
            m_spellCast_FrostBolt_CD = false;
            m_max = urand(3, 6);
            followerList.clear();

            if (me->GetAreaId() != 4877 || me->m_positionZ > -5.0f)
                return;

            for (uint32 i = 0; i < m_max; i++)
                Creature* naga = me->SummonCreature(NPC_NAGA_HATCHLING_44578, me->GetPosition(), TEMPSUMMON_MANUAL_DESPAWN); // RAND(NPC_NAGA_HATCHLING_44578, NPC_NAGA_HATCHLING_44579, NPC_NAGA_HATCHLING_44580)
        }

        void JustSummoned(Creature* summon) override
        {
            if (followerList.find(summon->GetGUID()) == followerList.end())
                followerList.insert(summon->GetGUID());
        }

        void SummonedCreatureDespawn(Creature* summon) override 
        { 
            followerList.erase(summon->GetGUID());
        }

        void SummonedCreatureDies(Creature* summon, Unit* killer) override 
        { 
            followerList.erase(summon->GetGUID());
        }

        void EnterCombat(Unit* victim) override
        {
            if (!m_spellCast_FrostNova_CD)
                if (urand(0, 100) < 30)
                {
                    me->CastSpell(victim, 11831);
                    m_spellCast_FrostNova_CD = true;
                    m_events.ScheduleEvent(EVENT_CAST_COOLDOWN_01, 8000);
                }
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (!m_spellCast_FrostNova_CD)
                if (urand(0, 100) < 30)
                {
                    me->CastSpell(attacker, SPELL_FROST_NOVA);
                    m_spellCast_FrostNova_CD = true;
                    m_events.ScheduleEvent(EVENT_CAST_COOLDOWN_01, 8000);
                    return;
                }
            if (!m_spellCast_FrostBolt_CD)
                if (urand(0, 100) < 50)
                {
                    me->CastSpell(attacker, SPELL_FROST_BOLD);
                    m_spellCast_FrostBolt_CD = true;
                    m_events.ScheduleEvent(EVENT_CAST_COOLDOWN_02, 10000);
                    return;
                }
        }

        void JustDied(Unit* killer) override
        {
            uint64 pGuid = 0;
            if (Player* player = killer->ToPlayer())
                if (player->GetQuestStatus(QUEST_IRRESISTIBLE_POOL_PONY) == QUEST_STATUS_INCOMPLETE)
                    pGuid = player->GetGUID();

            for (auto fGuid : followerList)
                if (Creature* follower = ObjectAccessor::GetCreature(*killer, fGuid))
                {
                    follower->AI()->SetGUID(pGuid, PLAYER_GUID);
                    follower->GetAI()->DoAction(ACTION_MASTER_KILLED);
                }
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (Player* player = who->ToPlayer())
                if (player->GetQuestStatus(QUEST_SURRENDER_OR_ELSE) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_SURRENDER_OR_ELSE) == QUEST_STATUS_COMPLETE)
                    me->AttackStop();
                else
                    if (me->CanStartAttack(who, false))
                        AttackStart(who);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CAST_COOLDOWN_01:
                    m_spellCast_FrostNova_CD = false;
                    break;
                case EVENT_CAST_COOLDOWN_02:
                    m_spellCast_FrostBolt_CD = false;
                    break;
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
        return new npc_vashj_elan_siren_38360AI(creature);
    }
};

// 44578 44579 44580
class npc_naga_hatchling_44579 : public CreatureScript
{
public:
    npc_naga_hatchling_44579() : CreatureScript("npc_naga_hatchling_44579") { }
    /*
        
    */
    struct npc_naga_hatchling_44579AI : public ScriptedAI
    {
        npc_naga_hatchling_44579AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_masterGUID;

        void Initialize()
        {
            m_playerGUID = 0;
            m_masterGUID = 0;
        }

        void Reset()
        {
            m_events.RescheduleEvent(EVENT_CHECK_FOLLOWING, 2000);
        }

        void IsSummonedBy(Unit* summoner) override 
        { 
            m_masterGUID = summoner->GetGUID();
            Position pos = me->GetNearPosition(frand(3.0f, 5.0f), frand(0, 6.28f));
            me->GetMotionMaster()->MovePoint(1024, pos);
        }

        void OnSpellClick(Unit* clicker, bool& result) override
        {
            if (Player* player = clicker->ToPlayer())
                if (player->GetQuestStatus(QUEST_IRRESISTIBLE_POOL_PONY) == QUEST_STATUS_INCOMPLETE)
                {
                    m_playerGUID = player->GetGUID();
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                    me->setFaction(35);
                    me->PlayDirectSound(3437);
                    player->CastSpell(me->m_positionX, me->m_positionY, me->m_positionZ, RAND(71918, 71919, 83115, 83116), true); 
                    me->DespawnOrUnsummon(10);
                }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == POINT_MOTION_TYPE)
                if (id == 1024)
                    m_events.ScheduleEvent(EVENT_START_FOLLOW, 10);
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case ACTION_MASTER_KILLED:
            {
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                me->setFaction(35);

                if (m_playerGUID)
                    m_events.RescheduleEvent(EVENT_CHECK_PLAYER, 1000);
                else
                    me->DespawnOrUnsummon(10);

                break;
            }
            }
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case PLAYER_GUID:
                m_playerGUID = guid;
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
                case EVENT_CHECK_FOLLOWING:
                {
                    if (!me->HasUnitState(UNIT_STATE_FOLLOW) || !m_masterGUID)
                        me->DespawnOrUnsummon(10);

                    break;
                }
                case EVENT_CHECK_PLAYER:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        if (player->GetQuestStatus(QUEST_IRRESISTIBLE_POOL_PONY) != QUEST_STATUS_INCOMPLETE)
                            me->DespawnOrUnsummon(10);
                    }
                    else
                        me->DespawnOrUnsummon(10);

                    m_events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
                    break;
                }
                case EVENT_START_FOLLOW:
                {
                    if (Creature* naga = ObjectAccessor::GetCreature(*me, m_masterGUID))
                        me->GetMotionMaster()->MoveFollow(naga, frand(3.0f, 4.5f), frand(1.65f, 4.63f));

                    break;
                }
                }

                if (!UpdateVictim())
                    return;
                else
                    DoMeleeAttackIfReady();
            }
        };
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_naga_hatchling_44579AI(creature);
    }
};

// 44588, 44589, 44590, 44591
class npc_naga_hatchling_44588 : public CreatureScript
{
public:
    npc_naga_hatchling_44588() : CreatureScript("npc_naga_hatchling_44588") { }

    struct npc_naga_hatchling_44588AI : public ScriptedAI
    {
        npc_naga_hatchling_44588AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_playerGUID;

        void Initialize()
        {
            m_playerGUID = 0;
        }

        void Reset()
        {
            m_events.RescheduleEvent(EVENT_CHECK_PLAYER, 3000);
        }

        void IsSummonedBy(Unit* summoner) override 
        { 
            me->CastSpell(me, SPELL_PROXIMITY_CONTROL_MASTER, true);
            if (Player* player = summoner->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                me->setFaction(35);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
                player->KilledMonsterCredit(NPC_NAGA_HATCHLING_KILL_CREDIT);
            }
            Position pos = me->GetNearPosition(frand(2.0f, 4.0f), frand(0, 6.28f));
            me->GetMotionMaster()->MovePoint(1024,pos);
        }

        void MovementInform(uint32 type, uint32 id) override 
        { 
            if (type == POINT_MOTION_TYPE)
                if (id==1024)
                    m_events.ScheduleEvent(EVENT_START_FOLLOW, 10);
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
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        if (player->GetQuestStatus(QUEST_IRRESISTIBLE_POOL_PONY) == QUEST_STATUS_REWARDED)
                            me->DespawnOrUnsummon();

                    m_events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
                    break;
                }
                case EVENT_START_FOLLOW:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        me->GetMotionMaster()->MoveFollow(player, frand(3.0f, 4.5f), frand(1.65f, 4.63f));

                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_naga_hatchling_44588AI(creature);
    }
};

// 38457
class npc_naga_hatchling_38457 : public CreatureScript
{
public:
    npc_naga_hatchling_38457() : CreatureScript("npc_naga_hatchling_38457") { }

    struct npc_naga_hatchling_38457AI : public ScriptedAI
    {
        npc_naga_hatchling_38457AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_playerGUID;

        void Initialize()
        {
            m_playerGUID = 0;
        }

        void Reset()
        {
            m_events.RescheduleEvent(EVENT_CHECK_PLAYER, 3000);
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
                m_playerGUID = player->GetGUID();
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
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        if (player->GetQuestStatus(QUEST_SURRENDER_OR_ELSE) != QUEST_STATUS_INCOMPLETE)
                            me->DespawnOrUnsummon();

                    m_events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_naga_hatchling_38457AI(creature);
    }
};

// 38455
class npc_ace_38455 : public CreatureScript
{
public:
    npc_ace_38455() : CreatureScript("npc_ace_38455") { }

    struct npc_ace_38455AI : public ScriptedAI
    {
        npc_ace_38455AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint32   m_movePart;

        void Reset()
        {
            m_movePart = 0;
            m_playerGUID = 0;
            me->CastSpell(me, 72077, true);
            m_events.RescheduleEvent(EVENT_MASTER_RESET, 250000);
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                m_movePart = 1;
                me->GetMotionMaster()->MovePath(3845501, false);
                m_events.ScheduleEvent(EVENT_TALK_PART_00, 1000);
            }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type==WAYPOINT_MOTION_TYPE)
                switch (m_movePart)
                {
                case 2:
                    if (id == 7)
                        m_events.ScheduleEvent(EVENT_TALK_PART_02, 100);
                    break;
                case 3:
                    if (id == 1)
                        me->DespawnOrUnsummon(10);
                    break;
                }
        }

        void DoAction(int32 param) override
        {
            if (m_playerGUID && param == ACTION_RUN_AWAY)
                m_events.ScheduleEvent(EVENT_TALK_PART_04, 1000);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_MASTER_RESET:
                    me->DespawnOrUnsummon(10);
                    break;
                case EVENT_TALK_PART_00:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        Talk(0, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_01, 5000);
                    break;
                }
                case EVENT_TALK_PART_01:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        Talk(1, player);
                    m_movePart=2;
                    me->GetMotionMaster()->MovePath(3845502, false);
                    break;
                }                
                case EVENT_TALK_PART_02: // wait until faceless and player are present and near together..
                {
                    if (Creature* face = me->FindNearestCreature(38448, 50.0f))
                        if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                            if (player->GetPosition().GetExactDist2d(face) < 47.0f)
                            {
                                face->AI()->SetGUID(me->GetGUID(), me->GetEntry());
                                face->AI()->DoAction(ACTION_START_TALK);
                                m_events.ScheduleEvent(EVENT_TALK_PART_03, 100);
                                break;
                            }
                    m_events.ScheduleEvent(EVENT_TALK_PART_02, 1000);
                    break;
                }
                case EVENT_TALK_PART_03:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        Talk(4, player);
                    break;
                }
                case EVENT_TALK_PART_04:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        Talk(5, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_05, 2000);
                    break;
                }
                case EVENT_TALK_PART_05:
                {
                    m_movePart = 3;
                    me->GetMotionMaster()->MovePath(3845503, false);
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_ace_38455AI(creature);
    }
};

// 38448 
class npc_faceless_of_the_deep_38448 : public CreatureScript
{
public:
    npc_faceless_of_the_deep_38448() : CreatureScript("npc_faceless_of_the_deep_38448") { }

    enum eNpc
    {
        EVENT_PLAYER_IS_NEAR_COOLDOWN = 901,
        EVENT_CHECK_MY_POSITION,
    };

    struct npc_faceless_of_the_deep_38448AI : public ScriptedAI
    {
        npc_faceless_of_the_deep_38448AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_aceGUID;
        bool     m_playerIsNear;
        bool     m_fight;
        float    m_maxDistance;
        float    m_hoover;

        void Reset()
        {
            m_hoover = 9;
            m_maxDistance = 47.0f;
            m_playerGUID = 0;
            m_aceGUID = 0;
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            m_playerIsNear = false;
            m_fight = false;
            me->SetSpeed(MOVE_WALK, 0.15f);
            m_events.RescheduleEvent(EVENT_CHECK_MY_POSITION, 1000);
        }

        void JustDied(Unit* killer) override 
        { 
            me->CastSpell(me, 72035, true);
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case NPC_ACE_38455:
                m_aceGUID = guid;
                break;
            }
        }

        void DoAction(int32 param) override
        {
            if (m_playerGUID && param == ACTION_START_TALK)
            {
                m_events.ScheduleEvent(EVENT_START_TALK, 100);
                m_events.RescheduleEvent(EVENT_MASTER_RESET, 75000);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            CastBarricade();

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_MASTER_RESET:
                    me->DespawnOrUnsummon(10);
                    break;
                case EVENT_PLAYER_IS_NEAR_COOLDOWN:
                    m_playerIsNear = false;
                    break;
                case EVENT_CHECK_MY_POSITION:
                    CheckPlayerNear();
                    m_events.ScheduleEvent(EVENT_CHECK_MY_POSITION, 100);
                    break;
                case EVENT_START_TALK:
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        Talk(1, player);
                        m_events.ScheduleEvent(EVENT_TALK_PART_02, 6000);
                    }
                    break;
                case EVENT_TALK_PART_02:
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        Talk(2, player);
                        m_events.ScheduleEvent(EVENT_TALK_PART_03, 6000);
                    }
                    break;
                case EVENT_TALK_PART_03:
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        Talk(3, player);
                        m_events.ScheduleEvent(EVENT_TALK_PART_04, 6000);
                    }
                    break;
                case EVENT_TALK_PART_04:
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        if (Creature* ace = ObjectAccessor::GetCreature(*me, m_aceGUID))
                        {
                            Talk(4, player);
                            ace->AI()->DoAction(ACTION_RUN_AWAY);

                            for (Unit::ControlList::iterator itr = player->m_Controlled.begin(); itr != player->m_Controlled.end(); ++itr)
                                if ((*itr)->GetEntry() == 38457)
                                    (*itr)->ToCreature()->DespawnOrUnsummon(100);

                            m_events.ScheduleEvent(EVENT_TALK_PART_05, 4000);
                        }
                    break;
                case EVENT_TALK_PART_05:
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        me->RemoveAllAuras();
                        me->SetHover(false);
                        me->SetFloatValue(UNIT_FIELD_HOVERHEIGHT, 0);
                        me->SetSpeed(MOVE_WALK, 1.0f);
                        me->JumpTo(player, 10.0f);
                        m_fight = true;
                    }
                    m_events.ScheduleEvent(EVENT_TALK_PART_06, 500);
                    break;
                case EVENT_TALK_PART_06:
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                    me->SetReactState(REACT_AGGRESSIVE);
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        me->Attack(player, true);
                    break;
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void CastBarricade()
        {
            if (!m_playerIsNear || m_fight)
                return;

            Position p = me->GetNearPosition(frand(9.5f, 11.0f), frand(0.0f, 6.28f));
            me->CastSpell(p.m_positionX, p.m_positionY, p.m_positionZ, 72076, true);
            p = me->GetNearPosition(frand(9.5f, 10.5f), frand(0.0f, 6.28f));
            me->CastSpell(p.m_positionX, p.m_positionY, p.m_positionZ, 72076, true);
        }

        void CheckPlayerNear()
        {
            if (m_fight)
                return;

            bool pNear = false;
            if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                if (player->GetQuestStatus(QUEST_SURRENDER_OR_ELSE) == QUEST_STATUS_INCOMPLETE)
                    if (player->GetPosition().GetExactDist2d(me) < m_maxDistance)
                        pNear = true;
                   
            if (!pNear)
            {
                std::list<Player*> pList = me->FindNearestPlayers(m_maxDistance * 0.85f);
                for (std::list<Player*>::const_iterator itr = pList.begin(); itr != pList.end(); ++itr)
                    if ((*itr)->GetQuestStatus(QUEST_SURRENDER_OR_ELSE) == QUEST_STATUS_INCOMPLETE)
                    {
                        m_playerGUID = (*itr)->GetGUID();
                        pNear = true;
                    }
            }

            m_playerIsNear = pNear;
            me->SetHover(pNear);

            if (pNear)
            {
                me->SetFloatValue(UNIT_FIELD_HOVERHEIGHT, m_hoover);
                m_events.RescheduleEvent(EVENT_PLAYER_IS_NEAR_COOLDOWN, 30000);
            }
            else
            {
                m_playerGUID = 0;
                me->SetFloatValue(UNIT_FIELD_HOVERHEIGHT, 0);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_faceless_of_the_deep_38448AI(creature);
    }
};

/*  phase 181  */

// 24110 is stored in zone_kezan.cpp

// 38526
class npc_bc_eliminator_38526 : public CreatureScript
{
public:
    npc_bc_eliminator_38526() : CreatureScript("npc_bc_eliminator_38526") { }

    enum eNPC
    {
    };

    struct npc_bc_eliminator_38526AI : public VehicleAI
    {
        npc_bc_eliminator_38526AI(Creature* creature) : VehicleAI(creature) { Initialize(); }

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
               
            }
            else
            {
               
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case 0:
                {
                    
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_bc_eliminator_38526AI(creature);
    }
};

// 38531
class npc_oomlot_warrior_38531 : public CreatureScript
{
public:
    npc_oomlot_warrior_38531() : CreatureScript("npc_oomlot_warrior_38531") { }

    enum eNPC
    {
    };

    struct npc_oomlot_warrior_38531AI : public ScriptedAI
    {
        npc_oomlot_warrior_38531AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap  m_events;
        uint64    m_summonedGuid;
        bool      m_allowShowFight;


        void Initialize()
        {
            m_summonedGuid = 0;
            m_allowShowFight = false;
        }

        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
            if (me->HasInPhaseList(182))
            {
                DoStartNoMovement(me);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
            }
        }

        void IsSummonedBy(Unit* summoner) override
        {
            m_summonedGuid = summoner->GetGUIDLow();
            me->GetMotionMaster()->MovePath(m_summonedGuid, false);
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (m_summonedGuid)
                if (type == WAYPOINT_MOTION_TYPE)
                    switch (m_summonedGuid)
                    {
                    case 286851:
                        if (id == 25)
                            m_events.ScheduleEvent(EVENT_MOVE_ATTACK, 10);
                    case 285584:
                        if (id == 15)
                            m_events.ScheduleEvent(EVENT_MOVE_ATTACK, 10);
                    case 285598:
                        if (id == 7)
                            m_events.ScheduleEvent(EVENT_MOVE_ATTACK, 10);
                    case 285600:
                        if (id == 5)
                            m_events.ScheduleEvent(EVENT_MOVE_ATTACK, 10);
                    case 285592:
                        if (id == 5)
                            m_events.ScheduleEvent(EVENT_MOVE_ATTACK, 10);
                    case 285588:
                        if (id == 5)
                            m_events.ScheduleEvent(EVENT_MOVE_ATTACK, 10);
                    case 285591:
                        if (id == 3)
                            m_events.ScheduleEvent(EVENT_MOVE_ATTACK, 10);
                    }
        }

        void DamageDealt(Unit* victim, uint32& damage, DamageEffectType /*damageType*/) override
        {
            damage = 0;
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            switch (attacker->GetEntry())
            {
            case NPC_BC_ELIMINATOR_38526:
                damage = me->GetMaxHealth() + 1;
                break;
            default:
            {
                uint32 max = (me->GetMaxHealth() / 2) + 1;
                damage = max;
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
                case EVENT_MOVE_ATTACK:
                {
                    me->SetHomePosition(me->GetPosition());
                    me->SetReactState(REACT_AGGRESSIVE);
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_oomlot_warrior_38531AI(creature);
    }
};

// 38647
class npc_izzy_38647 : public CreatureScript
{
public:
    npc_izzy_38647() : CreatureScript("npc_izzy_38647") { }

    bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* quest, uint32 /*opt*/)
    {
        switch (quest->GetQuestId())
        {
        case QUEST_OOMLOT_VILLAGE:
        {
            player->RemoveAura(66987);
            break;
        }
        }
        return false;
    }

    struct npc_izzy_38647AI : public ScriptedAI
    {
        npc_izzy_38647AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;

        void Initialize()
        {
        }

        void Reset() override
        {
            if (me->GetAreaId() == 4909)
            {
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                me->SetReactState(REACT_AGGRESSIVE);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case 0:
                {
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_izzy_38647AI(creature);
    }
};

// 38696 
class npc_yngwie_38696 : public CreatureScript
{
public:
    npc_yngwie_38696() : CreatureScript("npc_yngwie_38696") { }

    struct npc_yngwie_38696AI : public ScriptedAI
    {
        npc_yngwie_38696AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        bool     m_illusionSpawned;

        void Reset() override
        {
            m_illusionSpawned = false;
        }

        void EnterCombat(Unit* victim) override 
        { 
            Talk(0);
            AttackStart(victim);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override 
        { 
            if (Player* player = attacker->ToPlayer())
                if (!m_illusionSpawned)
                    if (me->GetHealthPct() < 30)
                    {
                        m_illusionSpawned = true;
                        me->CastSpell(me, 75942, true);
                    }
        }

        void EnterEvadeMode() override { }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case 0:
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
        return new npc_yngwie_38696AI(creature);
    }
};

// 38643
class npc_goblin_captive_38643 : public CreatureScript
{
public:
    npc_goblin_captive_38643() : CreatureScript("npc_goblin_captive_38643") { }

    struct npc_goblin_captive_38643AI : public ScriptedAI
    {
        npc_goblin_captive_38643AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;

        void Reset() override
        {
            m_playerGUID = 0;
            me->CastSpell(me, 72243, true);
            me->CastSpell(me, 72522, true);
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

        void DoAction(int32 param) override 
        { 
            switch (param)
            {
            case 1: // enter combat
            {
                me->RemoveAura(72522);
                me->RemoveAura(72518);
                break;
            }
            case 2: // just killed
            {
                me->RemoveAura(72243);
                if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    Talk(0, player);
                me->DespawnOrUnsummon(3000);
                break;
            }
            case 3: // shamane has despawned
            {
                Reset();
                break;
            }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_goblin_captive_38643AI(creature);
    }
};

// 38644
class npc_oomlot_shaman_38644 : public CreatureScript
{
public:
    npc_oomlot_shaman_38644() : CreatureScript("npc_oomlot_shaman_38644") { }

    struct npc_oomlot_shaman_38644AI : public ScriptedAI
    {
        npc_oomlot_shaman_38644AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_goblinGUID;
        uint64   m_playerGUID;

        void Reset() override
        {
            m_goblinGUID = 0;
            m_playerGUID = 0;
        }

        void IsSummonedBy(Unit* summoner) override 
        { 
            m_goblinGUID = summoner->GetGUID();
            me->SetFacingToObject(summoner);
            me->CastSpell(me, 72518, true);
        }

        void EnterCombat(Unit* victim) override 
        { 
            if (Player* player = victim->ToPlayer())
                if (Creature* goblin = ObjectAccessor::GetCreature(*me, m_goblinGUID))
                {
                    m_playerGUID = player->GetGUID();
                    me->RemoveAura(72518);
                    goblin->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
                    goblin->AI()->DoAction(1);
                }
            AttackStart(victim);
        }

        void EnterEvadeMode() override 
        { 
            if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                if (Creature* goblin = ObjectAccessor::GetCreature(*me, m_goblinGUID))
                    goblin->AI()->DoAction(3);
            me->DespawnOrUnsummon();
        }

        void JustDied(Unit* killer) override 
        { 
            if (Player* player = killer->ToPlayer())
                if (Creature* goblin = ObjectAccessor::GetCreature(*me, m_goblinGUID))
                {
                    goblin->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
                    goblin->AI()->DoAction(2);
                }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_oomlot_shaman_38644AI(creature);
    }
};

/*  phase 182  */ 

// 38808
class npc_gaahl_38808 : public CreatureScript
{
public:
    npc_gaahl_38808() : CreatureScript("npc_gaahl_38808") { }

    struct npc_gaahl_38808AI : public ScriptedAI
    {
        npc_gaahl_38808AI(Creature* creature) : ScriptedAI(creature) { }

        uint64   m_captiveGUID;

        void Reset() override
        {
            m_captiveGUID = 0;
        }

        void EnterCombat(Unit* victim) override 
        { 
            if (Player* player = victim->ToPlayer())
                if (Creature* captive = ObjectAccessor::GetCreature(*me, m_captiveGUID))
                {
                    captive->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
                    captive->AI()->DoAction(2);
                }

            ScriptedAI::EnterCombat(victim);
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case 38812:
            {
                m_captiveGUID = guid;
                break;
            }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_gaahl_38808AI(creature);
    }
};

// 38812
class npc_goblin_captive_38812 : public CreatureScript
{
public:
    npc_goblin_captive_38812() : CreatureScript("npc_goblin_captive_38812") { }

    struct npc_goblin_captive_38812AI : public ScriptedAI
    {
        npc_goblin_captive_38812AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_gaahlGUID;

        void Reset() override
        {
            m_playerGUID = 0;
            m_gaahlGUID = 0;
            m_events.RescheduleEvent(EVENT_CHECK_PLAYER, 1000);
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (caster->GetEntry() == NPC_GAAHL_38808 && spell->Id == 72935)
                caster->GetAI()->SetGUID(me->GetGUID(), me->GetEntry());
        }

        void JustSummoned(Creature* summon) override 
        { 
            if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                if (Creature* gaahl = ObjectAccessor::GetCreature(*me, m_gaahlGUID))
                {
                    summon->AI()->SetGUID(gaahl->GetGUID(), gaahl->GetEntry());
                    summon->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
                }

            me->DespawnOrUnsummon(100);
        }

        void DoAction(int32 param) override 
        { 
            switch (param)
            {
            case 2:
            {
                if (me->HasAura(72935))
                    me->RemoveAura(72935);

                me->CastSpell(me, 72936, true);
                break;
            }
            }
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
                case EVENT_CHECK_PLAYER:
                {
                    if (!m_gaahlGUID)
                        if (Creature* npc = me->FindNearestCreature(NPC_GAAHL_38808, 10.0f))
                            if (!npc->IsInCombat())
                                m_gaahlGUID = npc->GetGUID();

                    if (!me->HasAura(72935))
                        if (Creature* gaahl = ObjectAccessor::GetCreature(*me, m_gaahlGUID))
                        {
                            gaahl->CastSpell(me, 72935, true);
                        }
                        
                    m_events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_goblin_captive_38812AI(creature);
    }
};

// 38813
class npc_goblin_zombie_38813 : public CreatureScript
{
public:
    npc_goblin_zombie_38813() : CreatureScript("npc_goblin_zombie_38813") { }

    struct npc_goblin_zombie_38813AI : public ScriptedAI
    {
        npc_goblin_zombie_38813AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_gaahlGUID;

        void Reset() override
        {
            m_playerGUID = 0;
            m_gaahlGUID = 0;
            me->SetSpeed(MOVE_WALK, 0.3f);
            me->SetSpeed(MOVE_RUN, 0.3f);
            me->CastSpell(me, 72866, true);
            me->CastSpell(me, 72778, true);
            if (me->GetAreaId() == 4899)
            { // show world live: 
                m_events.RescheduleEvent(EVENT_SHOW_FIGHT, 1000);
            }
            else
            { // part of quest: three little pygmies
                m_events.RescheduleEvent(EVENT_START_WALK, 1000);
                m_events.RescheduleEvent(EVENT_COOLDOWN_00, 30000);
            }
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (spell->Id == SPELL_ROCKETS_BOOTS_DAMAGE_EFFECT_72886)
                if (Player* player = caster->ToPlayer())
                    player->KilledMonsterCredit(NPC_ZOMBIE_KILL_CREDIT_38807);
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case PLAYER_GUID:
                m_playerGUID = guid;
                break;
            case NPC_GAAHL_38808:
                m_gaahlGUID = guid;
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
                case EVENT_START_WALK:
                {
                    if (Creature* gaahl = ObjectAccessor::GetCreature(*me, m_gaahlGUID))
                        me->setFaction(gaahl->getFaction());
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        DoStartMovement(player, 3.0);
                    }

                    break;
                }
                case EVENT_COOLDOWN_00:
                    if (me->IsInCombat())
                        m_events.ScheduleEvent(EVENT_COOLDOWN_00, 30000);
                    else
                        me->DespawnOrUnsummon(10);

                    break;
                case EVENT_SHOW_FIGHT:
                {
                    me->GetMotionMaster()->MovePath(2383701, true);
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
        return new npc_goblin_zombie_38813AI(creature);
    }
};

// 38809
class npc_malmo_38809 : public CreatureScript
{
public:
    npc_malmo_38809() : CreatureScript("npc_malmo_38809") { }

    struct npc_malmo_38809AI : public ScriptedAI
    {
        npc_malmo_38809AI(Creature* creature) : ScriptedAI(creature) { }

        uint64   m_captiveGUID;

        void Reset() override
        {
            m_captiveGUID = 0;
        }

        void EnterCombat(Unit* victim) override
        {
            if (Player* player = victim->ToPlayer())
                if (Creature* captive = ObjectAccessor::GetCreature(*me, m_captiveGUID))
                {
                    captive->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
                    captive->AI()->DoAction(2);
                }

            ScriptedAI::EnterCombat(victim);
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case 50311:
            {
                m_captiveGUID = guid;
                break;
            }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_malmo_38809AI(creature);
    }
};

// 50311
class npc_goblin_captive_50311 : public CreatureScript
{
public:
    npc_goblin_captive_50311() : CreatureScript("npc_goblin_captive_50311") { }

    struct npc_goblin_captive_50311AI : public ScriptedAI
    {
        npc_goblin_captive_50311AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_malmoGUID;

        void Reset() override
        {
            m_playerGUID = 0;
            m_malmoGUID = 0;
            m_events.RescheduleEvent(EVENT_CHECK_PLAYER, 1000);
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (caster->GetEntry() == NPC_MALMO_38809 && spell->Id == 72935)
                caster->GetAI()->SetGUID(me->GetGUID(), me->GetEntry());
        }

        void JustSummoned(Creature* summon) override
        {
            if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                if (Creature* malmo = ObjectAccessor::GetCreature(*me, m_malmoGUID))
                {
                    summon->AI()->SetGUID(malmo->GetGUID(), malmo->GetEntry());
                    summon->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
                }

            me->DespawnOrUnsummon(100);
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case 2:
            {
                if (me->HasAura(72935))
                    me->RemoveAura(72935);

                me->CastSpell(me, 72938, true);
                break;
            }
            }
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
                case EVENT_CHECK_PLAYER:
                {
                    if (!m_malmoGUID)
                        if (Creature* npc = me->FindNearestCreature(NPC_MALMO_38809, 10.0f))
                            m_malmoGUID = npc->GetGUID();

                    if (!me->HasAura(72935))
                        if (Creature* malmo = ObjectAccessor::GetCreature(*me, m_malmoGUID))
                            malmo->CastSpell(me, 72935, true);

                    m_events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_goblin_captive_50311AI(creature);
    }
};

// 38816
class npc_goblin_zombie_38816 : public CreatureScript
{
public:
    npc_goblin_zombie_38816() : CreatureScript("npc_goblin_zombie_38816") { }

    struct npc_goblin_zombie_38816AI : public ScriptedAI
    {
        npc_goblin_zombie_38816AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_malmoGUID;

        void Reset() override
        {
            m_playerGUID = 0;
            m_malmoGUID = 0;
            me->SetSpeed(MOVE_WALK, 0.3f);
            me->SetSpeed(MOVE_RUN, 0.3f);
            me->CastSpell(me, 72866, true);
            me->CastSpell(me, 72778, true);
            if (me->GetAreaId() == 4899)
            { // show world live: 
                m_events.RescheduleEvent(EVENT_SHOW_FIGHT, 1000);
            }
            else
            { // part of quest: three little pygmies
                m_events.RescheduleEvent(EVENT_START_WALK, 1000);
                m_events.RescheduleEvent(EVENT_COOLDOWN_00, 30000);
            }
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case PLAYER_GUID:
                m_playerGUID = guid;
                break;
            case NPC_MALMO_38809:
                m_malmoGUID = guid;
                break;
            }
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (spell->Id == SPELL_ROCKETS_BOOTS_DAMAGE_EFFECT_72886)
                if (Player* player = caster->ToPlayer())
                    player->KilledMonsterCredit(NPC_ZOMBIE_KILL_CREDIT_38807);
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
                    if (Creature* malmo = ObjectAccessor::GetCreature(*me, m_malmoGUID))
                        me->setFaction(malmo->getFaction());
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        DoStartMovement(player, 3.0);
                    }

                    break;
                }
                case EVENT_COOLDOWN_00:
                    if (me->IsInCombat())
                        m_events.ScheduleEvent(EVENT_COOLDOWN_00, 30000);
                    else
                        me->DespawnOrUnsummon(10);

                    break;
                case EVENT_SHOW_FIGHT:
                {
                    me->GetMotionMaster()->MovePath(2383701, true);
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
        return new npc_goblin_zombie_38816AI(creature);
    }
};

// 38810
class npc_teloch_38810 : public CreatureScript
{
public:
    npc_teloch_38810() : CreatureScript("npc_teloch_38810") { }

    struct npc_teloch_38810AI : public ScriptedAI
    {
        npc_teloch_38810AI(Creature* creature) : ScriptedAI(creature) { }

        uint64   m_captiveGUID;

        void Reset() override
        {
            m_captiveGUID = 0;
        }

        void EnterCombat(Unit* victim) override
        {
            if (Player* player = victim->ToPlayer())
                if (Creature* captive = ObjectAccessor::GetCreature(*me, m_captiveGUID))
                {
                    captive->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
                    captive->AI()->DoAction(2);
                }

            ScriptedAI::EnterCombat(victim);
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case 50310:
            {
                m_captiveGUID = guid;
                break;
            }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_teloch_38810AI(creature);
    }
};

// 50310
class npc_goblin_captive_50310 : public CreatureScript
{
public:
    npc_goblin_captive_50310() : CreatureScript("npc_goblin_captive_50310") { }

    struct npc_goblin_captive_50310AI : public ScriptedAI
    {
        npc_goblin_captive_50310AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_telochGUID;

        void Reset() override
        {
            m_playerGUID = 0;
            m_telochGUID = 0;
            m_events.RescheduleEvent(EVENT_CHECK_PLAYER, 1000);
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (caster->GetEntry() == NPC_TELOCH_38810 && spell->Id == 72935)
                caster->GetAI()->SetGUID(me->GetGUID(), me->GetEntry());
        }

        void JustSummoned(Creature* summon) override
        {
            if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                if (Creature* teloch = ObjectAccessor::GetCreature(*me, m_telochGUID))
                {
                    summon->AI()->SetGUID(teloch->GetGUID(), teloch->GetEntry());
                    summon->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
                }

            me->DespawnOrUnsummon(100);
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case 2:
            {
                if (me->HasAura(72935))
                    me->RemoveAura(72935);

                me->CastSpell(me, 72937, true);
                break;
            }
            }
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
                case EVENT_CHECK_PLAYER:
                {
                    if (!m_telochGUID)
                        if (Creature* npc = me->FindNearestCreature(NPC_TELOCH_38810, 10.0f))
                            m_telochGUID = npc->GetGUID();

                    if (!me->HasAura(72935))
                        if (Creature* teloch = ObjectAccessor::GetCreature(*me, m_telochGUID))
                            teloch->CastSpell(me, 72935, true);

                    m_events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_goblin_captive_50310AI(creature);
    }
};

// 38815
class npc_goblin_zombie_38815 : public CreatureScript
{
public:
    npc_goblin_zombie_38815() : CreatureScript("npc_goblin_zombie_38815") { }

    struct npc_goblin_zombie_38815AI : public ScriptedAI
    {
        npc_goblin_zombie_38815AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_telochGUID;

        void Reset() override
        {
            m_playerGUID = 0;
            m_telochGUID = 0;
            me->SetSpeed(MOVE_WALK, 0.3f);
            me->SetSpeed(MOVE_RUN, 0.3f);
            me->CastSpell(me, 72866, true);
            me->CastSpell(me, 72778, true);
            m_events.RescheduleEvent(EVENT_START_WALK, 1000);
            m_events.RescheduleEvent(EVENT_COOLDOWN_00, 30000);
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case PLAYER_GUID:
                m_playerGUID = guid;
                break;
            case NPC_TELOCH_38810:
                m_telochGUID = guid;
                break;
            }
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (spell->Id == SPELL_ROCKETS_BOOTS_DAMAGE_EFFECT_72886)
                if (Player* player = caster->ToPlayer())
                    player->KilledMonsterCredit(NPC_ZOMBIE_KILL_CREDIT_38807);
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
                    if (Creature* teloch = ObjectAccessor::GetCreature(*me, m_telochGUID))
                        me->setFaction(teloch->getFaction());
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        DoStartMovement(player, 3.0);

                    break;
                }
                case EVENT_COOLDOWN_00:
                    if (me->IsInCombat())
                        m_events.ScheduleEvent(EVENT_COOLDOWN_00, 30000);
                    else
                        me->DespawnOrUnsummon(10);

                    break;
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
        return new npc_goblin_zombie_38815AI(creature);
    }
};

// 72886
class spell_rocket_boots_damage_effect_72886 : public SpellScriptLoader
{
public:
    spell_rocket_boots_damage_effect_72886() : SpellScriptLoader("spell_rocket_boots_damage_effect_72886") { }

    class ZombieCheck
    {
    public:
        bool operator()(const WorldObject* target) const
        {
            switch (target->GetEntry())
            {
            case 38753:
            case 38813:
            case 38815:
            case 38816:
                return false;
            }

            return true;
        }
    };

    class spell_rocket_boots_damage_effect_72886_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rocket_boots_damage_effect_72886_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
           targets.remove_if(ZombieCheck());
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_rocket_boots_damage_effect_72886_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_rocket_boots_damage_effect_72886_SpellScript();
    }
};

// 38753
class npc_goblin_zombie_38753 : public CreatureScript
{
public:
    npc_goblin_zombie_38753() : CreatureScript("npc_goblin_zombie_38753") { }

    struct npc_goblin_zombie_38753AI : public ScriptedAI
    {
        npc_goblin_zombie_38753AI(Creature* creature) : ScriptedAI(creature) { }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (spell->Id == SPELL_ROCKETS_BOOTS_DAMAGE_EFFECT_72886)
                if (Player* player = caster->ToPlayer())
                    player->KilledMonsterCredit(NPC_ZOMBIE_KILL_CREDIT_38807);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_goblin_zombie_38753AI(creature);
    }
};

// 38409
class npc_goblin_survivor_38409 : public CreatureScript
{
public:
    npc_goblin_survivor_38409() : CreatureScript("npc_goblin_survivor_38409") { }

    struct npc_goblin_survivor_38409AI : public ScriptedAI
    {
        npc_goblin_survivor_38409AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;

        void Initialize() 
        {
            switch (me->GetAreaId())
            {
            case 4899:
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                me->SetReactState(REACT_PASSIVE);
                break;
            case 4909:
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                me->SetReactState(REACT_AGGRESSIVE);
                break;
            }
        }

        void CreatureMoveInLineOfSight(Unit* who) override
        {
            if (who->GetEntry() == 38813 || who->GetEntry() == 38816 || who->GetEntry() == 38753)
                if (who->GetDistance2d(me) < 15.0f)
                    me->CastSpell(who, 72944, true);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_goblin_survivor_38409AI(creature);
    }
};

// 38745
class npc_kezan_citizen_38745 : public CreatureScript
{
public:
    npc_kezan_citizen_38745() : CreatureScript("npc_kezan_citizen_38745") { }

    struct npc_kezan_citizen_38745AI : public ScriptedAI
    {
        npc_kezan_citizen_38745AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;

        void Initialize()
        {
            switch (me->GetAreaId())
            {
            case 4899:
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                me->SetReactState(REACT_PASSIVE);
                break;
            case 4909:
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                me->SetReactState(REACT_AGGRESSIVE);
                break;
            }
        }

        void CreatureMoveInLineOfSight(Unit* who) override
        {
            if (who->GetEntry() == 38813 || who->GetEntry() == 38816 || who->GetEntry() == 38753)
                if (who->GetDistance2d(me) < 15.0f)
                    me->CastSpell(who, 72944, true);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_kezan_citizen_38745AI(creature);
    }
};

// 72944
class spell_shoot_72944 : public SpellScriptLoader
{
public:
    spell_shoot_72944() : SpellScriptLoader("spell_shoot_72944") { }

    class ZombieCheck
    {
    public:
        bool operator()(const WorldObject* target) const
        {
            switch (target->GetEntry())
            {
            case 38753:
            case 38813:
            case 38815:
            case 38816:
                return false;
            }

            return true;
        }
    };

    class spell_shoot_72944_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_shoot_72944_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if(ZombieCheck());
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_shoot_72944_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_shoot_72944_SpellScript();
    }
};

// 38850
class npc_volcanoth_champion_38850 : public CreatureScript
{
public:
    npc_volcanoth_champion_38850() : CreatureScript("npc_volcanoth_champion_38850") { }

    struct npc_volcanoth_champion_38850AI : public ScriptedAI
    {
        npc_volcanoth_champion_38850AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset() override
        {
            m_events.RescheduleEvent(EVENT_CHECK_FIGHT, urand(1000, 2000));
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_FIGHT:
                {
                    Position pos = me->GetHomePosition();
                    if (pos.GetExactDist(me) > 15.0f)
                    {
                        me->CombatStop();
                        me->GetMotionMaster()->MoveTargetedHome();
                    }
                    else if (!me->IsInCombat())
                        if (Creature* target = FindNewTarget())
                        {
                            DoStartMovement(target);
                            me->Attack(target, true);
                            target->Attack(me, true);
                        }

                    m_events.ScheduleEvent(EVENT_CHECK_FIGHT, urand(9000, 10000));
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        Creature* FindNewTarget()
        {
            std::list<Creature*> cList = me->FindAllUnfriendlyCreaturesInRange(10.0f);
            GetCreatureListWithEntryInGrid(cList, me, 38409, 10.0f);
            GetCreatureListWithEntryInGrid(cList, me, 38745, 10.0f);

           return FindNearestTarget(cList, me);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_volcanoth_champion_38850AI(creature);
    }
};

// 36615
class npc_doc_zapnozzle_36615 : public CreatureScript
{
public:
    npc_doc_zapnozzle_36615() : CreatureScript("npc_doc_zapnozzle_36615") { }

    struct npc_doc_zapnozzle_36615AI : public ScriptedAI
    {
        npc_doc_zapnozzle_36615AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset() override
        {

        }

        void MovementInform(uint32 type, uint32 id) override 
        { 
            if (type == WAYPOINT_MOTION_TYPE)
                switch (id)
                {
                case 0:
                case 8:
                {
                    std::list<Creature*> cList = me->FindAllFriendlyCreaturesInRange(15.0f);
                    for (auto npc : cList)
                        if (npc->GetHealthPct() < 50.0f)
                        {
                            me->CastSpell(npc, 72996, true);
                            break;
                        }
                    break;
                }
                }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_doc_zapnozzle_36615AI(creature);
    }
};

// 38855
class npc_volcanoth_38855 : public CreatureScript
{
public:
    npc_volcanoth_38855() : CreatureScript("npc_volcanoth_38855") { }

    struct npc_volcanoth_38855AI : public ScriptedAI
    {
        npc_volcanoth_38855AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset() override
        {
            if (me->IsInPhase(182))
            {
                m_events.RescheduleEvent(EVENT_CAST_SPELL_00, 5000);
                m_events.RescheduleEvent(EVENT_CAST_SPELL_01, 40000);
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
                    me->CastSpell(me, 73016, true);
                    m_events.ScheduleEvent(EVENT_CAST_SPELL_00, urand(35000, 45000));
                    break;
                }
                case EVENT_CAST_SPELL_01:
                {
                    me->CastSpell(me, 73097, true);
                    m_events.ScheduleEvent(EVENT_CAST_SPELL_01, urand(4100, 7000));
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
        return new npc_volcanoth_38855AI(creature);
    }
};

/*  phase 183  */

// 38928
class npc_sassy_hardwrench_38928 : public CreatureScript
{
public:
    npc_sassy_hardwrench_38928() : CreatureScript("npc_sassy_hardwrench_38928") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case 25023:
        {
            creature->CastSpell(player, 73135, true);
            player->CastSpell(player, 72993, true);
            creature->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
            creature->AI()->DoAction(73105);
            break;
        }
        }
        return false;
    }

    struct npc_sassy_hardwrench_38928AI : public ScriptedAI
    {
        npc_sassy_hardwrench_38928AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;

        void Reset() override
        {
            m_playerGUID = 0;
        }

        void DoAction(int32 param) override 
        { 
            switch (param)
            {
            case 73105:
            {
                if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                {
                    player->CastSpell(player, 73105);
                    player->PlayDirectSound(73722);
                }
                break;
            }
            case 73156:
            {
                m_events.RescheduleEvent(EVENT_START_TALK, 10);
                break; 
            }
            }
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
                case EVENT_START_TALK:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        if (player->GetDistance(me) > 30.0f)
                        {
                            Talk(1, player);
                            m_events.ScheduleEvent(EVENT_START_TALK, 8000);
                        }
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_sassy_hardwrench_38928AI(creature);
    }
};

// player
class player_lost_isles : public PlayerScript
{
public:
    player_lost_isles() : PlayerScript("player_lost_isles") { }

    void OnQuestStatusChange(Player* player, uint32 questId, QuestStatus status) override
    {
        switch (questId)
        {
        case 24958:
        {
            if (!player->IsQuestRewarded(24958))
                if (status == QUEST_STATUS_COMPLETE)
                {
                    player->CastSpell(player, 73156, true); // Volcanoth!: Dummy to Sassy Hardwrench
                    player->CastSpell(player, 73090, true); // Imminent Death! The volcano is blowing! Get to Sassy and get the heck out of here!!!
                    player->CastSpell(player, 73194, true); // Volcanoth!: Summon Volcanoth Dead Explosion Bunny: summon 38985
                }
            break;
        }
        }
    }
};

// 38985
class npc_volcanoth_dead_explosion_bunny_38985 : public CreatureScript
{
public:
    npc_volcanoth_dead_explosion_bunny_38985() : CreatureScript("npc_volcanoth_dead_explosion_bunny_38985") { }

    struct npc_volcanoth_dead_explosion_bunny_38985AI : public ScriptedAI
    {
        npc_volcanoth_dead_explosion_bunny_38985AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset() override
        {
            m_events.RescheduleEvent(EVENT_CAST_SPELL_00, 500);
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
                    me->CastSpell(me, 73193, true);
                    break;
                }               
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_volcanoth_dead_explosion_bunny_38985AI(creature);
    }
};

// 38918
class npc_flying_bomber_38918 : public CreatureScript
{
public:
    npc_flying_bomber_38918() : CreatureScript("npc_flying_bomber_38918") { }

    struct npc_flying_bomber_38918AI : public VehicleAI
    {
        npc_flying_bomber_38918AI(Creature* creature) : VehicleAI(creature) { Initialize(); }

        EventMap  m_events;
        uint64    m_playerGUID;
        uint64    m_sassyGUID;
        uint64    m_bunnyGUID;
        uint32    m_sound;

        void Initialize()
        {
            m_playerGUID = 0;
            m_sassyGUID = 0;
            m_bunnyGUID = 0;
            m_sound = 23722;
        }

        void Reset() override
        {
            if (!me->HasAura(73149))
                me->CastSpell(me, 73149, true);
            m_events.RescheduleEvent(EVENT_START_FLY, 2000);
        }

        void JustSummoned(Creature* summon) override 
        { 
            if (Creature* bunny = summon->ToCreature())
                m_bunnyGUID = bunny->GetGUID();
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                m_events.RescheduleEvent(EVENT_PLAY_SOUND1, 1000);
            }
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override
        {
                if (apply)
                {
                    if (Creature* sassy = passenger->ToCreature())
                        m_sassyGUID = sassy->GetGUID();
                    if (Player* player = passenger->ToPlayer())
                        m_playerGUID = player->GetGUID();
                }
                else
                {
                    me->DespawnOrUnsummon(10);
                }
        }
     
        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == WAYPOINT_MOTION_TYPE)
                switch (id)
                {
                case 2:
                    break;
                case 4:
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        if (Creature* sassy = ObjectAccessor::GetCreature(*me, m_sassyGUID))
                        {
                            me->CastSpell(1072.83f, 1174.958f, 141.9254f, 73127, true);
                            player->CastSpell(player, 73112, true);
                            sassy->AI()->Talk(1, player);
                            m_sound = 23723;
                            m_events.ScheduleEvent(EVENT_PLAY_PERIODIC_SOUND, 1000);
                        }
                    break;
                case 8:
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        if (Creature* sassy = ObjectAccessor::GetCreature(*me, m_sassyGUID))
                        {
                            player->CastSpell(player, 73185, true);
                            player->CastSpell(player, 73191, true);
                            sassy->AI()->Talk(2, player);
                            m_sound = 23725;
                        }
                    break;
                case 22:
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        if (Creature* sassy = ObjectAccessor::GetCreature(*me, m_sassyGUID))
                        {
                            player->CastSpell(player, 73201, true); // trigger 73200 73202 73203
                            sassy->AI()->Talk(3, player);
                            m_sound = 23724;
                        }
                    break;
                case 26:
                    m_sound = 0;                    
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        me->PlayDirectSound(m_sound, player);
                        player->CastSpell(player, 90247);
                        m_events.CancelEvent(EVENT_PLAY_PERIODIC_SOUND);
                    }
                    me->DespawnOrUnsummon(10);
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
                case EVENT_START_FLY:
                {
                    if (Creature* sassy = ObjectAccessor::GetCreature(*me, m_sassyGUID))
                        if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        {
                            sassy->AI()->Talk(0, player);
                            me->SetSpeed(MOVE_RUN, 3.5f);
                            me->GetMotionMaster()->MovePath(3891800, false);
                        }
                    break;
                }
                case EVENT_PLAY_SOUND1:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        me->PlayDirectSound(m_sound, player);

                    break;
                }
                case EVENT_PLAY_PERIODIC_SOUND:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        me->PlayDirectSound(m_sound, player);

                    if (m_sound)
                        m_events.ScheduleEvent(EVENT_PLAY_PERIODIC_SOUND, 1000);
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_flying_bomber_38918AI(creature);
    }
};

// 43359
class npc_elm_general_purpose_bunny_infinite_hide_body_43359 : public CreatureScript
{
public:
    npc_elm_general_purpose_bunny_infinite_hide_body_43359() : CreatureScript("npc_elm_general_purpose_bunny_infinite_hide_body_43359") { }

    struct npc_elm_general_purpose_bunny_infinite_hide_body_43359AI : public ScriptedAI
    {
        npc_elm_general_purpose_bunny_infinite_hide_body_43359AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        std::list<Position> pList;

        void Initialize()
        {
            // our core can not handle this bunny_43359. it's to far away from player. 
            // i delete no data, maybe it's usefull for future use..
            //InsertTargetPositions();  
        }

        void Reset() override
        {
            //m_events.RescheduleEvent(EVENT_RANDOM_CAST, 1000);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_RANDOM_CAST:
                {
                    //if (urand(0, 100) < 50)
                    //    me->CastSpell(me, RAND(74070, 74072, 74076, 74085));
                    
                    Position pos = GetRandomTargetPosition();
                    uint32 spellId = RAND(74070, 74072, 74076, 74085);
                    me->CastSpell(pos.m_positionX, pos.m_positionY, pos.m_positionZ, spellId, true);

                    m_events.ScheduleEvent(EVENT_RANDOM_CAST, urand(4000, 5000));
                    break;
                }
                }
            }
        }

        Position GetRandomTargetPosition()
        {
            if (pList.empty())
                return Position(0, 0, 0);
           
            int32 rol = urand(0, pList.size() - 1);
            std::list<Position>::const_iterator itr = pList.begin();
            std::advance(itr, rol);
            return *itr;
        }

        void InsertTargetPositions()
        {
            pList.clear();
            pList.push_back(Position(1394.021f, 265.211f, -24.82532f));
                pList.push_back(Position(1746.308f, 2750.487f, 72.70672f));
                pList.push_back(Position(1127.153f, 445.2521f, 95.34599f));
                pList.push_back(Position(1375.492f, 540.5469f, 142.1257f));
                pList.push_back(Position(2580.765f, 2320.996f, -7.52829f));
                pList.push_back(Position(1008.834f, 1243.877f, 222.115f));
                pList.push_back(Position(2040.008f, 2053.955f, 110.8633f));
                pList.push_back(Position(1268.849f, 2600.016f, 48.51329f));
                pList.push_back(Position(833.9003f, 993.89f, 137.3346f));
                pList.push_back(Position(656.973f, 1746.658f, 107.0542f));
                pList.push_back(Position(2186.604f, 2061.612f, 40.88118f));
                pList.push_back(Position(991.3453f, 182.1427f, -10.96202f));
                pList.push_back(Position(1736.114f, 2748.587f, 73.51421f));
                pList.push_back(Position(1432.881f, 3017.047f, -33.88331f));
                pList.push_back(Position(1371.48f, 464.8078f, 112.1118f));
                pList.push_back(Position(1665.023f, 2363.871f, 182.496f));
                pList.push_back(Position(2249.08f, 2569.786f, -0.7347901f));
                pList.push_back(Position(1847.685f, 2620.169f, 84.2216f));
                pList.push_back(Position(2574.388f, 2307.996f, -8.2883f));
                pList.push_back(Position(2275.37f, 2269.22f, 27.88316f));
                pList.push_back(Position(486.7486f, 1675.822f, -16.46047f));
                pList.push_back(Position(2483.624f, 1921.613f, 0.4846237f));
                pList.push_back(Position(2139.563f, 601.3396f, 148.2256f));
                pList.push_back(Position(756.5989f, 1164.384f, 42.36192f));
                pList.push_back(Position(421.3554f, 2077.722f, -0.09303093f));
                pList.push_back(Position(2003.873f, 1795.207f, 171.0459f));
                pList.push_back(Position(1950.905f, 1968.725f, 175.1599f));
                pList.push_back(Position(762.4387f, 1117.865f, 126.1768f));
                pList.push_back(Position(826.5689f, 1093.372f, 118.7464f));
                pList.push_back(Position(1251.501f, 484.3697f, 101.8722f));
                pList.push_back(Position(1399.815f, 440.8916f, 118.4765f));
                pList.push_back(Position(404.7482f, 1448.357f, -27.65089f));
                pList.push_back(Position(2369.986f, 2144.816f, 5.248497f));
                pList.push_back(Position(1412.05f, 427.0219f, 118.4765f));
                pList.push_back(Position(1711.007f, 487.3984f, 115.8521f));
                pList.push_back(Position(1565.919f, 142.0312f, -10.96202f));
                pList.push_back(Position(1176.379f, 283.5713f, -24.80992f));
                pList.push_back(Position(1757.383f, 2622.928f, 91.35134f));
                pList.push_back(Position(2412.076f, 2618.906f, -21.38659f));
                pList.push_back(Position(804.0764f, 1597.448f, 152.8327f));
                pList.push_back(Position(2183.344f, 1945.925f, 82.07567f));
                pList.push_back(Position(1947.221f, 2202.213f, 118.3656f));
                pList.push_back(Position(533.3586f, 1925.779f, 32.45287f));
                pList.push_back(Position(828.9863f, 2216.282f, 61.32046f));
                pList.push_back(Position(1038.639f, 1981.718f, 181.4062f));
                pList.push_back(Position(226.0688f, 1991.825f, -0.2057024f));
                pList.push_back(Position(586.1387f, 729.2018f, -10.87155f));
                pList.push_back(Position(2385.209f, 454.3485f, -10.96195f));
                pList.push_back(Position(318.7612f, 2238.885f, -10.01094f));
                pList.push_back(Position(880.2772f, 1399.718f, 208.9504f));
                pList.push_back(Position(2513.989f, 2495.113f, -18.40865f));
                pList.push_back(Position(895.8293f, 855.7269f, 160.9014f));
                pList.push_back(Position(1750.542f, 2619.87f, 92.66262f));
                pList.push_back(Position(1300.08f, 2859.218f, -32.98334f));
                pList.push_back(Position(1696.898f, 2632.841f, 94.16725f));
                pList.push_back(Position(2354.573f, 2542.292f, 1.150147f));
                pList.push_back(Position(2230.84f, 1466.899f, 163.4754f));
                pList.push_back(Position(2535.257f, 1088.405f, 126.7964f));
                pList.push_back(Position(1693.448f, 2235.815f, 206.9441f));
                pList.push_back(Position(1849.298f, 2078.572f, 173.4192f));
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_elm_general_purpose_bunny_infinite_hide_body_43359AI(creature);
    }
};

// 38979
class npc_giant_fireball_bunny_38979 : public CreatureScript
{
public:
    npc_giant_fireball_bunny_38979() : CreatureScript("npc_giant_fireball_bunny_38979") { }

    struct npc_giant_fireball_bunny_38979AI : public ScriptedAI
    {
        npc_giant_fireball_bunny_38979AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset() override
        {
            me->SetSpeed(MOVE_RUN, 3.5f);
            me->GetMotionMaster()->MovePath(3897900, false);
        }

        void DoAction(int32 param) override 
        { 
            switch (param)
            {
            case 1:
                me->CastSpell(me, 73111, true); // trigger 73181
                break;
            case 2:
                me->CastSpell(me, 73182, true);
                break;
            }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == WAYPOINT_MOTION_TYPE)
                switch (id)
                {
                case 1:
                    me->CastSpell(me, 73111, true); 
                    me->CastSpell(me, 73182, true);
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
                case EVENT_RANDOM_CAST:
                {
                    
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_giant_fireball_bunny_38979AI(creature);
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
    new npc_elm_general_purpose_bunny_23837();
    new npc_warrior_matic_nx__36525();
    new npc_sassy_hardwrench_36425();
    new npc_orc_survivor_36421();
    new npc_trade_prince_gallywix_36513();
    new go_rocket_sling_196439();
    new npc_sling_rocket_36514();
    new npc_sling_rocket_36505();
    new npc_foreman_dampwick_36470();
    /*  phase 180  */
    new npc_foreman_dampwick_36471();
    new npc_hobart_grapplehammer_38120();
    new npc_bamm_megabomb_38122();
    new npc_sally_salvager_sandscrew_38511();
    new npc_evol_fingers_38513();
    new npc_warrior_matic_nx__38518();
    new npc_fizz_lighter_38514();
    new npc_sister_goldskimmer_38516();
    new npc_slinky_sharpshiv_38517();
    new npc_sassy_hardwrench_38387();
    new npc_wild_clucker_38111();
    new go_raptor_trap_201972();
    new npc_wild_clucker_egg_38195();
    new npc_spiny_raptor_38187();
    new npc_mechachicken_38224();
    new npc_the_biggest_egg_ever_spell_visual_38227();
    new npc_assistant_greely_38124();
    new npc_megs_dreadshredder_38432();
    new npc_brett_coins_mcquid_38381();
    new go_naga_banner_202133();
    new npc_vashj_elan_warrior_38359();
    new npc_vashj_elan_siren_38360();
    new npc_naga_hatchling_44579();
    new npc_naga_hatchling_44588();
    new npc_naga_hatchling_38457();
    new npc_ace_38455();
    new npc_faceless_of_the_deep_38448();
    /*  phase 181  */
    new npc_bc_eliminator_38526();
    new npc_oomlot_warrior_38531();
    new npc_izzy_38647();
    new npc_yngwie_38696();
    new npc_goblin_captive_38643();
    new npc_oomlot_shaman_38644();
    /*  phase 182  */
    new npc_gaahl_38808();
    new npc_goblin_captive_38812();
    new npc_goblin_zombie_38813();
    new npc_malmo_38809();
    new npc_goblin_captive_50311();
    new npc_goblin_zombie_38816();
    new npc_teloch_38810();
    new npc_goblin_captive_50310();
    new npc_goblin_zombie_38815();
    new spell_rocket_boots_damage_effect_72886();
    new npc_goblin_zombie_38753();
    new npc_goblin_survivor_38409();
    new npc_kezan_citizen_38745();
    new spell_shoot_72944();
    new npc_volcanoth_champion_38850();
    new npc_doc_zapnozzle_36615();
    new npc_volcanoth_38855();
    /*  phase 183  */
    new npc_sassy_hardwrench_38928();
    new player_lost_isles();
    new npc_volcanoth_dead_explosion_bunny_38985();
    new npc_flying_bomber_38918();
    new npc_elm_general_purpose_bunny_infinite_hide_body_43359();
    new npc_giant_fireball_bunny_38979();
}
