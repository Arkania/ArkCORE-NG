/*
 * Copyright (C) 2014 Arkania Project
 *
 * The ALL-IN-ONE WonderScript for Goblin, Worgen and Troll work zones. Works miracles for unfinished starting zones. Have something to comment?....
 *
 * If you do, please just STFU, we need nothing more than one script to contain what's missing. Blame da laziness, mon.
 *
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "SpellMgr.h"
#include "Player.h"
#include "Creature.h"
 
/******* GOBLIN SHIT ****/

// DEFIANT TROLL - at mines, where you start, doesn't do shit and this is not needed, at least for now. Needs rewrite, when i get there.

enum NPC_DefiantTroll
{
    DEFFIANT_KILL_CREDIT              = 34830,
    SPELL_LIGHTNING_VISUAL            = 45870,
    QUEST_GOOD_HELP_IS_HARD_TO_FIND   = 14069,
    GO_DEPOSIT                        = 195488,
};
 
#define SAY_WORK_1 "Oops, break's over."
#define SAY_WORK_2 "Don't tase me, mon!"
#define SAY_WORK_3 "I report you to HR!"
#define SAY_WORK_4 "Work was bettah in da Undermine!"
#define SAY_WORK_5 "I'm going. I'm going!"
#define SAY_WORK_6 "Sorry, mon. It won't happen again."
#define SAY_WORK_7 "What I doin' wrong? Don't I get a lunch and two breaks a day, mon?"
#define SAY_WORK_8 "Ouch! Dat hurt!"
 
// Why the FUCK are these yells defined and like this? Note to self: Must pass to db. Need sound id's.
 
class npc_defiant_troll : public CreatureScript
{
    public:
    npc_defiant_troll() : CreatureScript("npc_defiant_troll") { }
 
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_defiant_trollAI(creature);
    }
 
    struct npc_defiant_trollAI : public ScriptedAI
    {
        npc_defiant_trollAI(Creature* creature) : ScriptedAI(creature) {}
 
        uint32 rebuffTimer;
        uint32 auraTimer;
        bool work;
 
        void Reset ()
        {
            rebuffTimer = 0;
            work = false;
            auraTimer = 0;
        }
 
        //void MovementInform(uint32 /*type*/, uint32 id)
        //{
        //    if (id == 1)
        //        work = true;
        //}
 
        void SpellHit(Unit* caster, const SpellEntry* spell)
        {                   
            // Remove Aura from Player
            caster->RemoveAurasDueToSpell(SPELL_LIGHTNING_VISUAL);
 
            if (spell->Id == SPELL_LIGHTNING_VISUAL && caster->GetTypeId() == TYPEID_PLAYER
                && caster->ToPlayer()->GetQuestStatus(QUEST_GOOD_HELP_IS_HARD_TO_FIND) == QUEST_STATUS_INCOMPLETE && work == false)
            {
                caster->ToPlayer()->KilledMonsterCredit(DEFFIANT_KILL_CREDIT, me->GetGUID());
 
                switch (urand(0, 7))
                {
                    case 0:
                        me->MonsterYell(SAY_WORK_1, LANG_UNIVERSAL, 0);
                        break;
                    case 1:
                        me->MonsterYell(SAY_WORK_2, LANG_UNIVERSAL, 0);
                        break;
                    case 2:
                        me->MonsterYell(SAY_WORK_3, LANG_UNIVERSAL, 0);
                        break;
                    case 3:
                        me->MonsterYell(SAY_WORK_4, LANG_UNIVERSAL, 0);
                        break;
                    case 4:
                        me->MonsterYell(SAY_WORK_5, LANG_UNIVERSAL, 0);
                        break;
                    case 5:
                        me->MonsterYell(SAY_WORK_6, LANG_UNIVERSAL, 0);
                        break;
                    case 6:
                        me->MonsterYell(SAY_WORK_7, LANG_UNIVERSAL, 0);
                        break;
                    case 7:
                        me->MonsterYell(SAY_WORK_8, LANG_UNIVERSAL, 0);
                        break;
                }
                me->RemoveAllAuras();
                // Add Aura to Troll
                me->AddAura(SPELL_LIGHTNING_VISUAL, me);
                // set work here so you can't gossip npc while they are walking to ore
                work = true;
                if (GameObject* Deposit = me->FindNearestGameObject(GO_DEPOSIT, 20))
                    me->GetMotionMaster()->MovePoint(1, Deposit->GetPositionX()-1, Deposit->GetPositionY(), Deposit->GetPositionZ());
                // Set timer here so he despawns in 2 minutes, set 2 sec aura timer
                rebuffTimer = 120000;
                auraTimer = rebuffTimer - 2000;
 
                //work = true;
            }
        }
 
        void UpdateAI(const uint32 diff)
        {       
            if (work == true)
            {
                me->HandleEmote(467);
                if (rebuffTimer <= auraTimer)
                    me->RemoveAurasDueToSpell(SPELL_LIGHTNING_VISUAL);
            }
            if (rebuffTimer <= diff)
            {
                // If working and timer hits 2 minutes, despawn
                if (work == true)
                    {
                    me->DespawnOrUnsummon();
                    }
                switch (urand(0, 2))
                {
                    case 0:
                        me->HandleEmote(412);
                        break;
                    case 1:
                        me->HandleEmote(10);
                        break;
                    case 2:
                        me->HandleEmote(0);
                        break;
                }
                rebuffTimer = 120000; //Rebuff again in 2 minutes
            }
            else
                rebuffTimer -= diff;
 
            if (!UpdateVictim())
                return;
 
            DoMeleeAttackIfReady();
        }
    };
 
    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_GOOD_HELP_IS_HARD_TO_FIND) == QUEST_STATUS_INCOMPLETE) // && work == false)
        {
            player->CastSpell(creature, SPELL_LIGHTNING_VISUAL, true);
            SpellEntry const* spell = sSpellStore.LookupEntry(SPELL_LIGHTNING_VISUAL);
            CAST_AI(npc_defiant_troll::npc_defiant_trollAI, creature->AI())->SpellHit(player, spell);
            return true;
        }
        return false;
    }
};


/***** WORGEN SHIT ******/




/******* TROLL SHIT ******/

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
    {-1137.437f, -5430.574f, 13.64f},
    {-1136.318f, -5417.105f, 13.27f},
    // guid 3905256
    {-1159.222f, -5519.436f, 12.128f},
    {-1152.798f, -5519.026f, 11.984f},
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

            void UpdateAI(const uint32 diff)
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

            void UpdateAI(const uint32 diff)
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
    new npc_defiant_troll();
    new npc_tiki_target();
    new npc_darkspear_jailor();
}