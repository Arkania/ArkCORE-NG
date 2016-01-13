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

// http://www.wowhead.com/npc=11492/alzzin-the-wildshaper
// alzzin_the_wildshaper
// ALZZIN_THE_WILDAHAPER

// 11492
class boss_alzzin_the_wildshaper : public CreatureScript
{
public:
    boss_alzzin_the_wildshaper() : CreatureScript("boss_alzzin_the_wildshaper") { }

    struct boss_alzzin_the_wildshaperAI : public BossAI
    {
        boss_alzzin_the_wildshaperAI(Creature* creature) : BossAI(creature, ENC_ALZZIN_THE_WILDAHAPER) { m_instance = creature->GetInstanceScript(); }

        InstanceScript* m_instance;
        EventMap m_events;
        uint32 m_phase;

        void Reset()
        {
            m_instance->SetData(ENC_ALZZIN_THE_WILDAHAPER, NOT_STARTED);
            m_events.Reset();
            m_phase = 0;
        }

        void EnterCombat(Unit* /*who*/)
        {
            m_instance->SetData(ENC_ALZZIN_THE_WILDAHAPER, IN_PROGRESS);
        }

        void JustDied(Unit* /*Killer*/)
        {
            m_instance->SetData(ENC_ALZZIN_THE_WILDAHAPER, DONE);
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
        return GetDireMaulAI<boss_alzzin_the_wildshaperAI>(creature);
    }
};

void AddSC_boss_alzzin_the_wildshaper()
{
    new boss_alzzin_the_wildshaper();
}

