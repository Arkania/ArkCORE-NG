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

class boss_azil : public CreatureScript
{
public:
    boss_azil() : CreatureScript("boss_azil") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_azilAI (creature);
    }

    struct boss_azilAI : public ScriptedAI
    {
        boss_azilAI(Creature* creature) : ScriptedAI(creature)
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

void AddSC_boss_azil()
{
    new boss_azil();
}