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

// 6906
class boss_baelog : public CreatureScript
{
public:
    boss_baelog() : CreatureScript("boss_baelog") { }

    struct boss_baelogAI : public ScriptedAI
    {
        boss_baelogAI(Creature* creature) : ScriptedAI(creature)
        {
            m_instance = creature->GetInstanceScript();
        }

        InstanceScript* m_instance;
        EventMap m_events;
        uint32 m_phase;

        void Reset()
        {
            m_instance->SetData(ENC_THE_LOST_DWARVES, NOT_STARTED);           
            m_events.Reset();
            m_phase = 0;
        }

        void EnterCombat(Unit* /*who*/)
        {
            m_instance->SetData(ENC_THE_LOST_DWARVES, IN_PROGRESS);
        }

        void JustDied(Unit* /*Killer*/)
        {
            m_instance->SetData(ENC_THE_LOST_DWARVES, DONE);
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
        return GetUldamanAI<boss_baelogAI>(creature);
    }
};

// 6907
class boss_eric : public CreatureScript
{
public:
    boss_eric() : CreatureScript("boss_eric") { }

    struct boss_ericAI : public ScriptedAI
    {
        boss_ericAI(Creature* creature) : ScriptedAI(creature)
        {
            m_instance = creature->GetInstanceScript();
        }

        InstanceScript* m_instance;
        EventMap m_events;
        uint32 m_phase;

        void Reset()
        {
            //m_instance->SetData(BOSS_ERIC, NOT_STARTED);
            m_events.Reset();
            m_phase = 0;
        }

        void EnterCombat(Unit* /*who*/)
        {
            //m_instance->SetData(BOSS_ERIC, IN_PROGRESS);
        }

        void JustDied(Unit* /*Killer*/)
        {
            //m_instance->SetData(BOSS_ERIC, DONE);
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
        return GetUldamanAI<boss_ericAI>(creature);
    }
};

// 6908
class boss_olav : public CreatureScript
{
public:
    boss_olav() : CreatureScript("boss_olav") { }

    struct boss_olavAI : public ScriptedAI
    {
        boss_olavAI(Creature* creature) : ScriptedAI(creature)
        {
            m_instance = creature->GetInstanceScript();
        }

        InstanceScript* m_instance;
        EventMap m_events;
        uint32 m_phase;

        void Reset()
        {
            //m_instance->SetData(BOSS_OLAV, NOT_STARTED);
            m_events.Reset();
            m_phase = 0;
        }

        void EnterCombat(Unit* /*who*/)
        {
            //m_instance->SetData(BOSS_OLAV, IN_PROGRESS);
        }

        void JustDied(Unit* /*Killer*/)
        {
            //m_instance->SetData(BOSS_OLAV, DONE);
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
        return GetUldamanAI<boss_olavAI>(creature);
    }
};

void AddSC_boss_the_lost_dwarves()
{
    new boss_baelog();
    new boss_eric();
    new boss_olav();    
}
