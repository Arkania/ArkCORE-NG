/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
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
#include "bastion_of_twilight.h"

class boss_elementiu_monstrosity : public CreatureScript
{
public:
    boss_elementiu_monstrosity() : CreatureScript("boss_elementiu_monstrosity") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_elementium_monstrosityAI (creature);
    }

    struct boss_elementium_monstrosityAI : public ScriptedAI
    {
        boss_elementium_monstrosityAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        void Reset()
        {
            if (instance)
            instance->SetData(DATA_ASCENDANT_COUNCIL, NOT_STARTED);
        }

        void EnterCombat(Unit* /*who*/)
        {
            if (instance)
            instance->SetData(DATA_ASCENDANT_COUNCIL, IN_PROGRESS);
        }

        void JustDied(Unit* /*Killer*/)
        {
            if (instance)
            instance->SetData(DATA_ASCENDANT_COUNCIL, DONE);
        }

        void UpdateAI(uint32 /*diff*/)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_assembly_of_ascendents()
{
    new boss_elementiu_monstrosity();
}