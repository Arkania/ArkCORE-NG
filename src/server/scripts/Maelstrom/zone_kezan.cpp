/*
 * Copyright (C) 2011-2014 ArkCORE <http://www.arkania.net/>
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
#include "SpellMgr.h"
#include "Player.h"
#include "Creature.h"
 

enum TrollSpells
{
    // Tiki Target
    SPELL_TIKI_TARGET_VISUAL_1    = 71064,
    SPELL_TIKI_TARGET_VISUAL_2    = 71065,
    SPELL_TIKI_TARGET_VISUAL_3    = 71066,
    SPELL_TIKI_TARGET_VISUAL_DIE  = 71240,
};

Position const TrollwayPos[4] =
{
    // Darkspear Jailor.
    // guid 239679
    {-1137.437f, -5430.574f, 13.64f, 0.0f},
    {-1136.318f, -5417.105f, 13.27f, 0.0f},
    // guid 3905256
    {-1159.222f, -5519.436f, 12.128f, 0.0f},
    {-1152.798f, -5519.026f, 11.984f, 0.0f},
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

enum Action
{
    ACTION_MOVE_CAGE,
};

enum TrollQuests
{
    // Proving Pit
    QUEST_PROVING_PIT_ROGU  = 24774,
    QUEST_PROVING_PIT_MAGE  = 24754,
    QUEST_PROVING_PIT_SHAM  = 24762,
    QUEST_PROVING_PIT_HUNT  = 24780,
    QUEST_PROVING_PIT_PRIE  = 24786,
    QUEST_PROVING_PIT_WARR  = 24642,
    QUEST_PROVING_PIT_DRUI  = 24768,
    QUEST_PROVING_PIT_WARL  = 26276,
};

enum TrollCreatures
{
    NPC_SPITESCALE_SCOUT = 38142,
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
            npc_tiki_targetAI(Creature* creature) : ScriptedAI(creature) {}

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

class npc_darkspear_jailor : public CreatureScript
{
public:
    npc_darkspear_jailor() : CreatureScript("npc_darkspear_jailor"){}

        bool OnGossipHello(Player* pPlayer, Creature* creature)
        {
            if (pPlayer->GetQuestStatus(QUEST_PROVING_PIT_ROGU) == QUEST_STATUS_INCOMPLETE ||
                pPlayer->GetQuestStatus(QUEST_PROVING_PIT_MAGE) == QUEST_STATUS_INCOMPLETE ||
                pPlayer->GetQuestStatus(QUEST_PROVING_PIT_SHAM) == QUEST_STATUS_INCOMPLETE ||
                pPlayer->GetQuestStatus(QUEST_PROVING_PIT_HUNT) == QUEST_STATUS_INCOMPLETE ||
                pPlayer->GetQuestStatus(QUEST_PROVING_PIT_PRIE) == QUEST_STATUS_INCOMPLETE ||
                pPlayer->GetQuestStatus(QUEST_PROVING_PIT_WARR) == QUEST_STATUS_INCOMPLETE ||
                pPlayer->GetQuestStatus(QUEST_PROVING_PIT_DRUI) == QUEST_STATUS_INCOMPLETE ||
                pPlayer->GetQuestStatus(QUEST_PROVING_PIT_WARL) == QUEST_STATUS_INCOMPLETE) // This is a fucking huge "if".
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I'm ready to face my challenge.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                pPlayer->SEND_GOSSIP_MENU(15251, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect (Player* pPlayer, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
        {
            if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
            {
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->CLOSE_GOSSIP_MENU();
                creature->GetAI()->DoAction(ACTION_MOVE_CAGE);
            }

            return true;
        }

        struct npc_darkspear_jailorAI : public ScriptedAI
        {
            npc_darkspear_jailorAI(Creature* creature) : ScriptedAI(creature) {}

            InstanceScript* instance;
            bool activated;
            bool Starting;
            EventMap events;

            void Reset()
            {
                activated = false;
                Starting = false;
            }

            void UpdateAI(uint32 diff)
            {
                if (!activated)
                    return;

                if (activated && !Starting)
                {
                    events.ScheduleEvent(EVENT_MOVE_TO_CAGE_1, 100);
                    Starting = true;
                }

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_MOVE_TO_CAGE_1:
                            if(me->FindNearestCreature(50402, 40.0f)) // Jailor 1 - We use a spawned bunny near, so we can differ between them as guid is useless.
                                me->GetMotionMaster()->MovePoint(0, TrollwayPos[0]);
                            else // Jailor 2
                                me->GetMotionMaster()->MovePoint(0, TrollwayPos[2]);
                            events.ScheduleEvent(EVENT_MOVE_TO_CAGE_2, 4000);
                            break;
                        case EVENT_MOVE_TO_CAGE_2:
                            if(me->FindNearestCreature(50402, 40.0f)) // Jailor 1
                                me->GetMotionMaster()->MovePoint(0, TrollwayPos[1]);
                            else // Jailor 2
                                me->GetMotionMaster()->MovePoint(0, TrollwayPos[3]);
                            events.ScheduleEvent(EVENT_OPEN_CAGE, 6000);
                            break;
                        case EVENT_OPEN_CAGE:
                            if (GameObject* cage = me->FindNearestGameObject(201968, 10.0f))
                                cage->UseDoorOrButton();
                            events.ScheduleEvent(EVENT_SUMMON_SPITESCALE_SCOUT, 500);
                            events.ScheduleEvent(EVENT_MOVE_BACK_1, 2500);
                            break;
                        case EVENT_MOVE_BACK_1:
                            if(me->FindNearestCreature(50402, 40.0f)) // Jailor 1
                                me->GetMotionMaster()->MovePoint(0, TrollwayPos[0]);
                            else // Jailor 2
                                me->GetMotionMaster()->MovePoint(0, TrollwayPos[2]);
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
                            if(me->FindNearestCreature(50402, 40.0f)) // Jailor 1
                                me->SummonCreature(NPC_SPITESCALE_SCOUT, -1137.858f, -5414.610f, 13.038f, 3.252f, TEMPSUMMON_CORPSE_DESPAWN);
                            else // Jailor 2
                                me->SummonCreature(NPC_SPITESCALE_SCOUT, -1150.308f, -5521.526f, 11.307f, 4.76f, TEMPSUMMON_CORPSE_DESPAWN);
                            break;
                    }
                }
            }

            void DoAction(const int32 action)
            {
                switch(action)
                {
                    case ACTION_MOVE_CAGE:
                        Talk(0); // Say the line.
                        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        activated = true;
                        break;
                }
            }

        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_darkspear_jailorAI(creature);
        }
};

void AddSC_kezan()
{
    new npc_tiki_target();
    new npc_darkspear_jailor();
}