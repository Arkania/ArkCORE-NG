/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * This file is NOT free software. Third-party users can NOT redistribute 
 * it or modify it. If you find it, you are either hacking something, or very 
 * lucky (presuming someone else managed to hack it).
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ObjectMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "WorldPacket.h"

enum Spells
{
 SPELL_GAZE_OF_OCCUTHAR = 97028,
 SPELL_EYE_EXPLODE      = 101008,
 SPELL_WHIRL_OF_BLADES  = 105855,
 SPELL_RUN_THROUGH      = 105859
};

#define SPELL_REPELLENT_RAY                   RAID_MODE(89348, 95178)

class npc_containment_unit : public CreatureScript
{
    public:
        npc_containment_unit() : CreatureScript("npc_containment_unit") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_containment_unitAI(creature);
        }
            
        struct npc_containment_unitAI : public ScriptedAI
        {
            npc_containment_unitAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            uint32 RepellentRayTimer;

            void Reset()
            {
                RepellentRayTimer = 10000;
            }

            void EnterCombat(Unit* /*who*/)
            {
                RepellentRayTimer = 10000;
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (RepellentRayTimer <= diff)
                {
                    DoCastAOE(SPELL_REPELLENT_RAY);
                    RepellentRayTimer = urand(10000, 20000);
                }
                else
                    RepellentRayTimer -= diff;

                DoMeleeAttackIfReady();
            }
        };
};

class npc_disciple_of_hate : public CreatureScript
{
    public:
        npc_disciple_of_hate() : CreatureScript("npc_disciple_of_hate") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_disciple_of_hateAI(creature);
        }
            
        struct npc_disciple_of_hateAI : public ScriptedAI
        {
            npc_disciple_of_hateAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            uint32 WhirlingBladesTimer;
            uint32 RunThroughTimer;

            void Reset()
            {
                WhirlingBladesTimer = urand(5000, 15000);
            }

            void EnterCombat(Unit* /*who*/)
            {
                WhirlingBladesTimer = urand(5000, 15000);
                RunThroughTimer = urand(2000, 4000);
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (WhirlingBladesTimer <= diff)
                {
                    DoCast(me, SPELL_WHIRL_OF_BLADES);
                    WhirlingBladesTimer = urand(25000, 35000);
                }
                else
                    WhirlingBladesTimer -= diff;

                if (RunThroughTimer <= diff)
                {
                    DoCastVictim(SPELL_RUN_THROUGH);
                    RunThroughTimer = urand(9000, 12000);
                }
                else
                    RunThroughTimer -= diff;

                DoMeleeAttackIfReady();
            }
        };
};

class npc_eye_of_occuthar : public CreatureScript
{
    public:
        npc_eye_of_occuthar() : CreatureScript("npc_eye_of_occuthar") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_eye_of_occutharAI(creature);
        }
            
        struct npc_eye_of_occutharAI : public ScriptedAI
        {
            npc_eye_of_occutharAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            uint32 GazeTimer;
            uint32 ExplodeTimer;

            void Reset()
            {
                GazeTimer = 1000;
            }

            void EnterCombat(Unit* /*who*/)
            {
                GazeTimer = 1000;
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (GazeTimer <= diff)
                {
                    DoCast(me, SPELL_GAZE_OF_OCCUTHAR);
                    ExplodeTimer = 10100;
                }
                else
                    GazeTimer -= diff;

                if (ExplodeTimer <= diff)
                {
                    DoCast(me, SPELL_EYE_EXPLODE);
                    me->DespawnOrUnsummon(100);
                }
            }
        };
};

void AddSC_bh_trash()
{
    new npc_containment_unit();
    new npc_eye_of_occuthar();
    new npc_disciple_of_hate();
}