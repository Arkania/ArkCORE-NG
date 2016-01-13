/*
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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "uldaman.h"

//  7228  boss_ironaya
class boss_ironaya : public CreatureScript
{
public:
    boss_ironaya() : CreatureScript("boss_ironaya") { }
    
    enum eTalk
    {
        SAY_AGGRO,
    };

    struct boss_ironayaAI : public BossAI
    {
        boss_ironayaAI(Creature* creature) : BossAI(creature, ENC_IRONAYA) { m_instance = creature->GetInstanceScript(); }

        InstanceScript* m_instance;
        EventMap m_events;
        uint32 m_phase;

        void Reset() override
        {
            m_events.Reset();
            m_phase = 0;

            if (m_instance)
            {
                m_instance->SetData(ENC_IRONAYA, NOT_STARTED);
                if (GameObject* door = ObjectAccessor::GetGameObject(*me, m_instance->GetData64(DATA_IRONAYA_SEAL_DOOR)))
                    if (me->IsAlive())
                        door->SetGoState(GO_STATE_READY);
                    else
                        door->SetGoState(GO_STATE_ACTIVE);
            }
        }

        void EnterCombat(Unit* /*who*/) override
        {
            m_instance->SetData(ENC_IRONAYA, IN_PROGRESS);
            Talk(SAY_AGGRO);
        }

        void JustDied(Unit* Killer) override
        {
            m_instance->SetData(ENC_IRONAYA, DONE);
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
        return GetUldamanAI<boss_ironayaAI>(creature);
    }
};

void AddSC_boss_ironaya()
{
    new boss_ironaya();
}
