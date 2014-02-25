/*Copyright (C) 2014 Arkania Project.
*
* THIS particular file is NOT free software; third-party users should NOT have access to it, redistribute it or modify it. :)
*/

#include "ScriptPCH.h"
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

        void Reset() {}

        void EnterCombat(Unit* /*who*/) {}

        void UpdateAI(const uint32 Diff)
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