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
#include "dire_maul.h"

// http://www.wowhead.com/npc=11489/tendris-warpwood
// tendris_warpwood
// TENDRIS_WARPWOOD

// 11489
class boss_tendris_warpwood : public CreatureScript
{
public:
    boss_tendris_warpwood() : CreatureScript("boss_tendris_warpwood") { }

    struct boss_tendris_warpwoodAI : public BossAI
    {
        boss_tendris_warpwoodAI(Creature* creature) : BossAI(creature, ENC_TENDRIS_WARPWOOD) { m_instance = creature->GetInstanceScript(); }

        InstanceScript* m_instance;
        EventMap m_events;
        uint32 m_phase;

        void Reset()
        {
            m_instance->SetData(ENC_TENDRIS_WARPWOOD, NOT_STARTED);
            m_events.Reset();
            m_phase = 0;
        }

        void EnterCombat(Unit* /*who*/)
        {
            m_instance->SetData(ENC_TENDRIS_WARPWOOD, IN_PROGRESS);
        }

        void JustDied(Unit* /*Killer*/)
        {
            m_instance->SetData(ENC_TENDRIS_WARPWOOD, DONE);
        }

        void UpdateAI(uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDireMaulAI<boss_tendris_warpwoodAI>(creature);
    }
};

void AddSC_boss_tendris_warpwood()
{
    new boss_tendris_warpwood();
}


