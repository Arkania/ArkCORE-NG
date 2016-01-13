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

// http://www.wowhead.com/npc=11486/prince-tortheldrin
// prince_tortheldrin
// PRINCE_TORTHELDRIN

// 11486
class boss_prince_tortheldrin : public CreatureScript
{
public:
    boss_prince_tortheldrin() : CreatureScript("boss_prince_tortheldrin") { }

    struct boss_prince_tortheldrinAI : public BossAI
    {
        boss_prince_tortheldrinAI(Creature* creature) : BossAI(creature, ENC_PRINCE_TORTHELDRIN) { m_instance = creature->GetInstanceScript(); }

        InstanceScript* m_instance;
        EventMap m_events;
        uint32 m_phase;

        void Reset()
        {
            m_instance->SetData(ENC_PRINCE_TORTHELDRIN, NOT_STARTED);
            m_events.Reset();
            m_phase = 0;
        }

        void EnterCombat(Unit* /*who*/)
        {
            m_instance->SetData(ENC_PRINCE_TORTHELDRIN, IN_PROGRESS);
        }

        void JustDied(Unit* /*Killer*/)
        {
            m_instance->SetData(ENC_PRINCE_TORTHELDRIN, DONE);
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
        return GetDireMaulAI<boss_prince_tortheldrinAI>(creature);
    }
};

void AddSC_boss_prince_tortheldrin()
{
    new boss_prince_tortheldrin();
}



