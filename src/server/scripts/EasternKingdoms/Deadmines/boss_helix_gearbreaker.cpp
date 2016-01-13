/*
* Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
* Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
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

#include "ScriptPCH.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "deadmines.h"
#include "Vehicle.h"

// 47296 boss_helix_gearbreaker
class boss_helix_gearbreaker : public CreatureScript
{
public:
    boss_helix_gearbreaker() : CreatureScript("boss_helix_gearbreaker") { }

    struct boss_helix_gearbreakerAI : public BossAI
    {
        boss_helix_gearbreakerAI(Creature* creature) : BossAI(creature, BOSS_HELIX_GEARBREAKER) 
        { 
            m_instance = creature->GetInstanceScript(); 
        }

        InstanceScript* m_instance;
        EventMap m_events;
        uint32 m_phase;

        void Reset() override
        {
            m_instance->SetData(BOSS_HELIX_GEARBREAKER, NOT_STARTED);
            m_events.Reset();
            m_phase = 0;
        }

        void EnterCombat(Unit* /*who*/) override
        {
            m_instance->SetData(BOSS_HELIX_GEARBREAKER, IN_PROGRESS);
        }

        void JustDied(Unit* /*killer*/) override
        {
            if (GameObject* door = ObjectAccessor::GetGameObject(*me, m_instance->GetData64(DATA_MASTROOM_DOOR)))
                door->ResetDoorOrButton();
            m_instance->SetData(BOSS_HELIX_GEARBREAKER, DONE);
        }

        void UpdateAI(uint32 uiDiff) override
        {
            if (!UpdateVictim())
            return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetDeadminesAI<boss_helix_gearbreakerAI>(creature);
    }
};

// 47297 boss_lumbering_oaf
class boss_lumbering_oaf : public CreatureScript
{
public:
    boss_lumbering_oaf() : CreatureScript("boss_lumbering_oaf") { }

    struct boss_lumbering_oaf_AI : public ScriptedAI
    {
        boss_lumbering_oaf_AI(Creature* creature) : ScriptedAI(creature)
        { 
            m_instance = creature->GetInstanceScript(); 
        }

        InstanceScript* m_instance;
        EventMap m_events;
        uint32 m_phase;

        void Reset() override
        {
            m_events.Reset();
            m_phase = 0;
        }

        void EnterCombat(Unit* /*who*/)
        {

        }

        void JustDied(Unit* /*killer*/) override
        { 
            if (GameObject* door = ObjectAccessor::GetGameObject(*me, m_instance->GetData64(DATA_MASTROOM_DOOR)))
            {
                door->ResetDoorOrButton();
                door->SummonCreature(NPC_HELIX_GEARBREAKER, me->GetNearPosition(2.0f, 0.1316f));
            }
        }

        void UpdateAI(uint32 uiDiff) override
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetDeadminesAI<boss_lumbering_oaf_AI>(creature);
    }
 
};



void AddSC_boss_helix_gearbreaker()
{
    new boss_helix_gearbreaker();
    new boss_lumbering_oaf();
}
