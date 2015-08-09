/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * THIS particular file is NOT free software; third-party users should 
 * NOT have access to it, redistribute it or modify it.
 * We need to think up a better copyright than this. Who's your third party
 * on the net dude, dude? Should NOT? Er must nicht!
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "stonecore.h"

class boss_corborus : public CreatureScript
{
public:
    boss_corborus() : CreatureScript("boss_corborus") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_corborusAI (creature);
    }

    struct boss_corborusAI : public ScriptedAI
    {
        boss_corborusAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        void Reset() { }

        void EnterCombat(Unit* /*who*/) { }

        void UpdateAI(uint32 /*diff*/)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_corborus()
{
    new boss_corborus();
}