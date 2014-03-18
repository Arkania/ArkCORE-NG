/*Copyright (C) 2014 Arkania Project.
*
* THIS particular file is NOT free software; third-party users should NOT have access to it, redistribute it or modify it. :)
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

void AddSC_boss_corborus()
{
    new boss_corborus();
}