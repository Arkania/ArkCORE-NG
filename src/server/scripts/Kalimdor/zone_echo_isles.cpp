/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "ScriptedFollowerAI.h"
#include "Vehicle.h"
#include "Player.h"
#include "GameObjectAI.h"

// #########################################################  fight novice vs tiki_target

class npc_novice_darkspear_warrior : public CreatureScript
{
public:
    npc_novice_darkspear_warrior() : CreatureScript("npc_novice_darkspear_warrior") { }

    enum eFightVersusTikiTarget
    {
        NPC_NOVICE_DARKSPEAR_WARRIOR = 38268,
        NPC_TIKI_TARGET = 38038,
    };

    struct npc_novice_darkspear_warriorAI : public ScriptedAI
    {
        npc_novice_darkspear_warriorAI(Creature* creature) : ScriptedAI(creature) { }

        uint32 _timer;

        void Reset()
        {
            _timer = urand(1800, 2200);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
            {
                if (Creature* tiki = me->FindNearestCreature(NPC_TIKI_TARGET, 3.0f))
                {
                    if (_timer <= diff)
                    {
                        me->SetFacingTo(me->GetAngle(tiki));
                        me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK1H);
                        _timer = urand(1800, 2200);
                    }
                    else
                        _timer -= diff;
                }
            }
            else
                DoMeleeAttackIfReady();

        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_novice_darkspear_warriorAI(creature);
    }
};

// #########################################################  Quest Class Chain: A Rough Start

enum eQuestChainStart
{
    NPC_DOCILE_ISLAND_BOAR      = 38141,
    NPC_WILDMANE_CAT            = 38046,
    SPELL_LEAPING_RUSH          = 75002,
    SPELL_WILD_POUNCE           = 71232,
    SPELL_PERMANENT_FEIGN_DEATH = 29266,
    SPELL_FEIGN_DEATH           = 71598,
    SPELL_SWIPE                 = 31279,
};

class npc_docile_island_boar : public CreatureScript
{
public:
    npc_docile_island_boar() : CreatureScript("npc_docile_island_boar") { }

    bool OnDummyEffect(Unit* caster, uint32 spellId, SpellEffIndex effIndex, Creature* target)
    {
        if (spellId == SPELL_WILD_POUNCE && effIndex == 1)
        {
            CAST_AI(npc_docile_island_boarAI, target->AI())->StartAnim(caster->GetGUID());
            return true;
        }
        return false;
    }


    struct npc_docile_island_boarAI : public ScriptedAI
    {
        npc_docile_island_boarAI(Creature* creature) : ScriptedAI(creature) { }

        uint32 m_timer;
        uint32 m_phase;

        void Reset() override
        {
            m_timer = 0;
            m_phase = 0;
        }

        void StartAnim(uint64 guid)
        {
            m_phase = 5; m_timer = 100;
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (spell->Id == SPELL_LEAPING_RUSH)
            {
                caster->GetMotionMaster()->MoveIdle();
                m_phase = 2; m_timer = 5000;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_timer <= diff)
            {
                m_timer = 1000;
                DoWork();
            }
            else
                m_timer -= diff;

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void DoWork()
        {
            switch (m_phase)
            {
            case 0:
                break;
            case 1:
            {
                // me->RemoveAura(SPELL_FEIGN_DEATH);
            }
            case 2:
            {
                UpdateVictim();
                m_phase = 0; m_timer = 0;
                break;
            }
            // here start phase for spell 71232, bunch boar down
            case 5:
                me->GetMotionMaster()->MoveIdle();
                me->HandleEmoteState(EMOTE_STATE_SLEEP);
                m_phase = 6; m_timer = 10000;
                break;
            case 6:
                UpdateVictim();
                m_phase = 0; m_timer = 0;
                break;
            default:
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_docile_island_boarAI(creature);
    }
};

class npc_wildmane_cat : public CreatureScript
{
public:
    npc_wildmane_cat() : CreatureScript("npc_wildmane_cat") { }

    struct npc_wildmane_catAI : public ScriptedAI
    {
        npc_wildmane_catAI(Creature* creature) : ScriptedAI(creature) { }

        uint32 m_timer;
        uint32 m_phase;

        void Reset() override
        {
            m_timer = urand(10000, 60000);
            m_phase = 0;
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_timer <= diff)
            {
                m_timer = urand(10000, 60000);
                DoWork();
            }
            else
                m_timer -= diff;

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void DoWork()
        {
            switch (m_phase)
            {
            case 0:
            {
                if (Creature* boar = me->FindNearestCreature(NPC_DOCILE_ISLAND_BOAR, 45.0f))
                {
                    if (!boar->HasAura(SPELL_PERMANENT_FEIGN_DEATH))
                    {
                        uint8 rn = urand(0, 100);
                        if (me->IsWithinDist2d(boar->GetPosition(), 40.0f) && !me->IsWithinDist2d(boar->GetPosition(), 8.0f) && (rn < 50))
                        {
                            me->CastSpell(boar, SPELL_WILD_POUNCE, true); // Pinning a boar to the ground.
                            m_phase = 1; m_timer = 5000;
                        }
                        else if (!me->IsWithinDist2d(boar->GetPosition(), 5.0f) && (rn >= 50))
                        {
                            me->CastSpell(boar, SPELL_LEAPING_RUSH, true); // inflicting 100% weapon damage.
                            m_phase = 1; m_timer = 5000;
                        }
                    }
                }

                break;
            }
            case 1:
            {
                UpdateVictim();
                m_phase = 0; m_timer = 0;
                break;
            }
            default:
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_wildmane_catAI(creature);
    }
};

// #########################################################  Quest Class Chain: The Basics: Hitting Things

enum TrollSpells
{
    // Tiki Target
    SPELL_TIKI_TARGET_VISUAL_1      = 71064,
    SPELL_TIKI_TARGET_VISUAL_2      = 71065,
    SPELL_TIKI_TARGET_VISUAL_3      = 71066,
    SPELL_TIKI_TARGET_VISUAL_DIE    = 71240,
};

class npc_tiki_target : public CreatureScript
{
public:
    npc_tiki_target() : CreatureScript("npc_tiki_target") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tiki_targetAI(creature);
    }

    struct npc_tiki_targetAI : public ScriptedAI
    {
        npc_tiki_targetAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset()
        {
            if (!me->HasAura(SPELL_TIKI_TARGET_VISUAL_1) && !me->HasAura(SPELL_TIKI_TARGET_VISUAL_2) && !me->HasAura(SPELL_TIKI_TARGET_VISUAL_3))
                DoCast(me, RAND(SPELL_TIKI_TARGET_VISUAL_1, SPELL_TIKI_TARGET_VISUAL_2, SPELL_TIKI_TARGET_VISUAL_3));
        }

        void EnterCombat(Unit* /*who*/)
        {
            if (!me->HasAura(SPELL_TIKI_TARGET_VISUAL_1) && !me->HasAura(SPELL_TIKI_TARGET_VISUAL_2) && !me->HasAura(SPELL_TIKI_TARGET_VISUAL_3))
                DoCast(me, RAND(SPELL_TIKI_TARGET_VISUAL_1, SPELL_TIKI_TARGET_VISUAL_2, SPELL_TIKI_TARGET_VISUAL_3));
        }

        void UpdateAI(uint32 /*diff*/)
        {
            if (me->HealthBelowPct(30))
                DoCast(me, SPELL_TIKI_TARGET_VISUAL_DIE);
        }
    };
};

// #########################################################   Quest Class Chain: Proving Pit


enum TrollCreatures
{
    NPC_SPITESCALE_SCOUT        = 38142,
    NPC_DARKSPEAR_JAILOR        = 39062,
    NPC_CAPTIVE_SPIESCALE_SCOUT = 38142,
    NPC_LEGATI_ROGUE_TRAINER    = 38244,
};

Position const TrollwayPos[8] =
{
    // First Darkspear Jailor 
    { -1159.222f, -5519.436f, 12.128f, 0.000f }, // pos on side
    { -1152.798f, -5519.026f, 11.984f, 0.000f }, // pos on cage
    { -1150.308f, -5521.526f, 11.307f, 4.760f }, // pos summit scout
    { -1146.754f, -5530.905f, 08.106f, 2.982f }, // pos center place
    // Second Darkspear Jailor 
    { -1137.437f, -5430.574f, 13.640f, 0.000f }, // pos on side
    { -1136.318f, -5417.105f, 13.270f, 0.000f }, // pos on cage
    { -1137.858f, -5414.610f, 13.038f, 3.252f }, // pos summit scout
    { -1148.483f, -5417.083f, 10.598f, 5.067f }, // pos center place
};

class npc_captive_spitescale_scout : public CreatureScript
{
public:
    npc_captive_spitescale_scout() : CreatureScript("npc_captive_spitescale_scout") { }

    enum Events
    {
        EVENT_GO_TO_CENTER      = 1,
        EVENT_WAIT_ON_FIGHT     = 2,
        EVENT_FIGHT_UNTIL_DEATH = 3,
    };

    struct npc_captive_spitescale_scoutAI : public ScriptedAI
    {
        npc_captive_spitescale_scoutAI(Creature* creature) : ScriptedAI(creature) { }

        uint8 m_ScoutIndex;
        EventMap events;

        void Reset() override
        {
            m_ScoutIndex = 0;
        }

        void StartEvents(uint8 index)
        {
            m_ScoutIndex = index;
            events.ScheduleEvent(EVENT_GO_TO_CENTER, 100);
        }

        void JustDied(Unit* killer) override
        {
            Talk(1, killer);
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);
            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_GO_TO_CENTER:
                {
                    Talk(0);
                    me->GetMotionMaster()->MovePoint(7, TrollwayPos[m_ScoutIndex + 3]);
                    events.ScheduleEvent(EVENT_WAIT_ON_FIGHT, 6000);
                    break;
                }
                case EVENT_WAIT_ON_FIGHT:
                {
                    if (me->IsInCombat())
                    {
                        events.ScheduleEvent(EVENT_FIGHT_UNTIL_DEATH, 1000);
                        return;
                    }
                    if (Player* player = me->FindNearestPlayer(25.0f))
                    {
                        Talk(0, player);
                        me->setFaction(2224);
                        me->Attack(player, true);
                        player->Attack(me, true);
                        events.ScheduleEvent(EVENT_WAIT_ON_FIGHT, 8000);
                        return;
                    }
                    me->DespawnOrUnsummon();
                    break;
                }
                case EVENT_FIGHT_UNTIL_DEATH:
                {
                    if (me->GetDistance2d(TrollwayPos[m_ScoutIndex + 3].m_positionX, TrollwayPos[m_ScoutIndex + 3].m_positionY) > 20.0f)
                        me->DespawnOrUnsummon();

                    if (!me->IsInCombat())
                        me->DespawnOrUnsummon();

                    if (Unit* unit = me->GetVictim())
                        if (Player* player = unit->ToPlayer())
                        {
                            events.ScheduleEvent(EVENT_FIGHT_UNTIL_DEATH, 1000);
                            return;
                        }
                    break;
                }
                default:
                    printf("Event default %u \n", eventId);
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_captive_spitescale_scoutAI(creature);
    }
};

class npc_darkspear_jailor : public CreatureScript
{
public:
    npc_darkspear_jailor() : CreatureScript("npc_darkspear_jailor"){ }

    enum TrollQuests
    {
        // Proving Pit
        QUEST_PROVING_PIT_ROGU = 24774,
        QUEST_PROVING_PIT_MAGE = 24754,
        QUEST_PROVING_PIT_SHAM = 24762,
        QUEST_PROVING_PIT_HUNT = 24780,
        QUEST_PROVING_PIT_PRIE = 24786,
        QUEST_PROVING_PIT_WARR = 24642,
        QUEST_PROVING_PIT_DRUI = 24768,
        QUEST_PROVING_PIT_WARL = 26276,
    };

    enum Events
    {
        // Darkspear Jailor
        EVENT_MOVE_TO_CAGE_1 = 1,
        EVENT_MOVE_TO_CAGE_2,
        EVENT_OPEN_CAGE,
        EVENT_MOVE_BACK_1,
        EVENT_MOVE_BACK_2,
        EVENT_SUMMON_SPITESCALE_SCOUT,
        EVENT_RESET_POS,
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_PROVING_PIT_ROGU) == QUEST_STATUS_INCOMPLETE ||
            player->GetQuestStatus(QUEST_PROVING_PIT_MAGE) == QUEST_STATUS_INCOMPLETE ||
            player->GetQuestStatus(QUEST_PROVING_PIT_SHAM) == QUEST_STATUS_INCOMPLETE ||
            player->GetQuestStatus(QUEST_PROVING_PIT_HUNT) == QUEST_STATUS_INCOMPLETE ||
            player->GetQuestStatus(QUEST_PROVING_PIT_PRIE) == QUEST_STATUS_INCOMPLETE ||
            player->GetQuestStatus(QUEST_PROVING_PIT_WARR) == QUEST_STATUS_INCOMPLETE ||
            player->GetQuestStatus(QUEST_PROVING_PIT_DRUI) == QUEST_STATUS_INCOMPLETE ||
            player->GetQuestStatus(QUEST_PROVING_PIT_WARL) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM_DB(10974, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        }
        player->SEND_GOSSIP_MENU(15251, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        printf("OnGossipSelect: action %u \n", action);
        if (action == GOSSIP_ACTION_INFO_DEF + 1)
        {
            player->PlayerTalkClass->ClearMenus();
            player->CLOSE_GOSSIP_MENU();
            player->KilledMonsterCredit(NPC_DARKSPEAR_JAILOR);
            CAST_AI(npc_darkspear_jailorAI, creature->GetAI())->StartEvents();
        }

        return true;
    }

    struct npc_darkspear_jailorAI : public ScriptedAI
    {
        npc_darkspear_jailorAI(Creature* creature) : ScriptedAI(creature) { }

        uint8 m_JailorIndex;
        bool m_activated;
        EventMap events;

        void Reset() override
        {
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            m_JailorIndex = 0;
            m_activated = false;
        }

        void StartEvents()
        {
            if (Creature* npc = me->FindNearestCreature(NPC_LEGATI_ROGUE_TRAINER, 30.0f, true))
                m_JailorIndex = 4;

            if (!m_activated)
            {
                Talk(0);
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                m_activated = true;
                events.ScheduleEvent(EVENT_MOVE_TO_CAGE_1, 100);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);
            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_MOVE_TO_CAGE_1:
                    me->GetMotionMaster()->MovePoint(20, TrollwayPos[m_JailorIndex + 0]);
                    events.ScheduleEvent(EVENT_MOVE_TO_CAGE_2, 4000);
                    break;
                case EVENT_MOVE_TO_CAGE_2:
                    me->GetMotionMaster()->MovePoint(21, TrollwayPos[m_JailorIndex + 1]);
                    events.ScheduleEvent(EVENT_OPEN_CAGE, 6000);
                    break;
                case EVENT_OPEN_CAGE:
                    if (GameObject* cage = me->FindNearestGameObject(201968, 10.0f))
                        cage->UseDoorOrButton();
                    events.ScheduleEvent(EVENT_SUMMON_SPITESCALE_SCOUT, 500);
                    events.ScheduleEvent(EVENT_MOVE_BACK_1, 2500);
                    break;
                case EVENT_MOVE_BACK_1:
                    me->GetMotionMaster()->MovePoint(22, TrollwayPos[m_JailorIndex + 0]);
                    events.ScheduleEvent(EVENT_MOVE_BACK_2, 6000);
                    break;
                case EVENT_MOVE_BACK_2:
                    me->GetMotionMaster()->MoveTargetedHome();
                    events.ScheduleEvent(EVENT_RESET_POS, 3000);
                    break;
                case EVENT_RESET_POS:
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    Reset();
                    break;
                case EVENT_SUMMON_SPITESCALE_SCOUT:
                    if (Creature* creature = me->SummonCreature(NPC_SPITESCALE_SCOUT, TrollwayPos[m_JailorIndex + 2], TEMPSUMMON_CORPSE_DESPAWN))
                    {
                        CAST_AI(npc_captive_spitescale_scout::npc_captive_spitescale_scoutAI, creature->AI())->StartEvents(m_JailorIndex);
                    }
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_darkspear_jailorAI(creature);
    }
};

// #########################################################  Quest Class Chain: The Arts of a <class>

class npc_wounded_darkspear_watcher : public CreatureScript
{
public:
    npc_wounded_darkspear_watcher() : CreatureScript("npc_wounded_darkspear_watcher"){ }

    enum eQuest
    {
        NPC_WOUNDET_DARKSPEAR_WATCHER   = 47057,
        QUEST_THE_ART_OF_A_PRIEST       = 24784,
        SPELL_FLASH_HEAL                = 2061,
    };

    struct npc_wounded_darkspear_watcherAI : public ScriptedAI
    {
        npc_wounded_darkspear_watcherAI(Creature* creature) : ScriptedAI(creature) { }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (Player* player = caster->ToPlayer())
                if (player->GetQuestStatus(QUEST_THE_ART_OF_A_PRIEST) == QUEST_STATUS_INCOMPLETE)
                    if (spell->Id == SPELL_FLASH_HEAL)
                    {
                        player->KilledMonsterCredit(NPC_WOUNDET_DARKSPEAR_WATCHER);
                        me->DespawnOrUnsummon();
                    }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_wounded_darkspear_watcherAI(creature);
    }
};

// #########################################################  Quest 24623 Save the Young:

class npc_lost_bloodtalon_hatchling : public CreatureScript
{
public:
    npc_lost_bloodtalon_hatchling() : CreatureScript("npc_lost_bloodtalon_hatchling") { }

    enum eHatchling
    {
        NPC_BLOODTALON_HATCHLING    = 39157,
        QUEST_SAVING_THE_YOUNG      = 24623,
        SPELL_BLOODTALON_WHISTLE    = 70874,
    };

    struct npc_lost_bloodtalon_hatchlingAI : public ScriptedAI
    {
        npc_lost_bloodtalon_hatchlingAI(Creature* creature) : ScriptedAI(creature) { }

        uint32 m_timer;
        uint32 m_phase;
        Player* m_player;

        void Reset() override
        {
            m_timer = 0;
            m_phase = 0;
            m_player = NULL;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            if (spell->Id == SPELL_BLOODTALON_WHISTLE && m_phase == 0)
                if (m_player = caster->ToPlayer())
                    if (m_player->GetQuestStatus(QUEST_SAVING_THE_YOUNG) == QUEST_STATUS_INCOMPLETE)
                        if (me->GetDistance2d(m_player) < 15.0f)
                        {
                            me->GetMotionMaster()->MoveFollow(m_player, 2.0f, frand(0.0f, 6.28f));
                            m_player->KilledMonsterCredit(NPC_BLOODTALON_HATCHLING);
                            m_timer = 1000;
                            m_phase = 1;
                        }
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_timer <= diff)
            {
                m_timer = 1000;
                DoWork();
            }
            else
                m_timer -= diff;

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void DoWork()
        {
            switch (m_phase)
            {
            case 1:
            {
                if (!m_player)
                    me->DespawnOrUnsummon();
                if (m_player->IsDead() || m_player->GetQuestStatus(QUEST_SAVING_THE_YOUNG) == QUEST_STATUS_REWARDED)
                    me->DespawnOrUnsummon();
                break;
            }
            default:
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lost_bloodtalon_hatchlingAI(creature);
    }
};

// #########################################################  Quest 24626 Young and Vicious

class npc_swiftclaw_38002 : public CreatureScript
{
public:
    npc_swiftclaw_38002() : CreatureScript("npc_swiftclaw_38002") { }

    struct npc_swiftclaw_38002AI : public ScriptedAI
    {
        npc_swiftclaw_38002AI(Creature* creature) : ScriptedAI(creature) { }

        void StartAnim(Player* player, Creature* raptor)
        {
            player->EnterVehicle(me, 1);
            me->SetSpeed(MOVE_RUN, 1.2f, true);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_swiftclaw_38002AI(creature);
    }
};

class at_raptor_pens : public AreaTriggerScript
{
public:
    at_raptor_pens() : AreaTriggerScript("at_raptor_pens") { }

    enum eAreaTrigger
    {
        QUEST_YOUNG_AND_VICIOUS     = 24626,
        NPC_SWIFTCLAW               = 38002,
    };

    bool OnTrigger(Player* player, const AreaTriggerEntry* at) override
    {
        if (player && player->GetQuestStatus(QUEST_YOUNG_AND_VICIOUS) == QUEST_STATUS_INCOMPLETE)
        if (Vehicle* vehicle = player->GetVehicle())
            if (Unit* base = vehicle->GetBase())
                if (Creature* raptor = base->ToCreature())
                {
                    player->Dismount();
                    player->KilledMonsterCredit(NPC_SWIFTCLAW);
                    raptor->DespawnOrUnsummon();
                }

        return false;
    }
};

class npc_swiftclaw_37989 : public CreatureScript
{
public:
    npc_swiftclaw_37989() : CreatureScript("npc_swiftclaw_37989") { }

    enum eAreaTrigger
    {
        QUEST_YOUNG_AND_VICIOUS = 24626,
        NPC_SWIFTCLAW = 37989,
        NPC_SWIFTCLAW_SUMMON = 38002,
        SPELL_RAPTOR_ROPE = 70927,
    };

    struct npc_swiftclaw_37989AI : public ScriptedAI
    {
        npc_swiftclaw_37989AI(Creature* creature) : ScriptedAI(creature) { }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (spell->Id == SPELL_RAPTOR_ROPE)
                if (Player* player = caster->ToPlayer())
                    if (player->GetQuestStatus(QUEST_YOUNG_AND_VICIOUS) == QUEST_STATUS_INCOMPLETE)
                        if (me->GetDistance2d(player) < 2.0f)
                        {
                            player->KilledMonsterCredit(NPC_SWIFTCLAW);
                            if (Creature* npc = player->SummonCreature(NPC_SWIFTCLAW_SUMMON, me->GetNearPosition(1.0f, 0.0f)))
                                CAST_AI(npc_swiftclaw_38002::npc_swiftclaw_38002AI, npc->AI())->StartAnim(player, npc);

                            me->SetPhaseMask(2, true);
                            me->DespawnOrUnsummon();
                        }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_swiftclaw_37989AI(creature);
    }
};

// #########################################################  showfight between darkspear and spitescale 

class npc_spitescale_showfight : public CreatureScript // 38300, 38301, 38302
{
public:
    npc_spitescale_showfight() : CreatureScript("npc_spitescale_showfight") { }

    struct npc_spitescale_showfightAI : public ScriptedAI
    {
        npc_spitescale_showfightAI(Creature* creature) : ScriptedAI(creature) { }

        float m_health;

        void Reset() override
        {
            m_health = frand(40.0f, 75.0f);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            bool sf = false;
            if (attacker->GetEntry() == 38324) sf = true;
            if (attacker->GetEntry() == 38326) sf = true;
            if (sf)
            {
                if (me->GetHealthPct() < m_health)
                    damage = 0;
                else
                    damage /= 10;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_spitescale_showfightAI(creature);
    }
};

class npc_darkspear_showfight : public CreatureScript // 38324, 38326
{
public:
    npc_darkspear_showfight() : CreatureScript("npc_darkspear_showfight") { }

    struct npc_darkspear_showfightAI : public ScriptedAI
    {
        npc_darkspear_showfightAI(Creature* creature) : ScriptedAI(creature) { }

        float m_health;

        void Reset() override
        {
            m_health = frand(40.0f, 75.0f);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            bool sf = false;
            if (attacker->GetEntry() == 38300) sf = true;
            if (attacker->GetEntry() == 38301) sf = true;
            if (attacker->GetEntry() == 38302) sf = true;
            if (sf)
            {
                if (me->GetHealthPct() < m_health)
                    damage = 0;
                else
                    damage /= 10;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_darkspear_showfightAI(creature);
    }
};

// ######################################################### quest 25035 break the lines

class npc_jornun_38989 : public CreatureScript
{
public:
    npc_jornun_38989() : CreatureScript("npc_jornun_38989"){ }

    enum eQuest25035
    {
        npc_jornun = 38989,
        npc_morakki = 38442,
        quest_break_the_lines = 25035,
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player && player->GetQuestStatus(quest_break_the_lines) == QUEST_STATUS_INCOMPLETE)
        {
            player->KilledMonsterCredit(npc_jornun);
            creature->AI()->Talk(0);
        }
        return false;
    }

};

class npc_morakki_38442 : public CreatureScript
{
public:
    npc_morakki_38442() : CreatureScript("npc_morakki_38442"){ }

    enum eQuest25035
    {
        npc_jornun              = 38989,
        npc_morakki             = 38442,
        quest_break_the_lines   = 25035,
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player && player->GetQuestStatus(quest_break_the_lines) == QUEST_STATUS_INCOMPLETE)
        {
            player->KilledMonsterCredit(npc_morakki);
        }
        return true;
    }

};

// ######################################################### 


void AddSC_zone_echo_isles()
{
    new npc_novice_darkspear_warrior();
    new npc_tiki_target();
    new npc_docile_island_boar();
    new npc_wildmane_cat();
    new npc_darkspear_jailor();
    new npc_captive_spitescale_scout();
    new npc_wounded_darkspear_watcher();
    new npc_lost_bloodtalon_hatchling();
    new npc_swiftclaw_37989();
    new npc_swiftclaw_38002();
    new at_raptor_pens();
    new npc_spitescale_showfight();
    new npc_darkspear_showfight();
    new npc_jornun_38989();
    new npc_morakki_38442();
};
