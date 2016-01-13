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

// http://www.wowhead.com/npc=11490/zevrim-thornhoof
// zevrim_thornhoof
// ZEVRIM_THORNHOOF

// 11490
class boss_zevrim_thornhoof : public CreatureScript
{
public:
    boss_zevrim_thornhoof() : CreatureScript("boss_zevrim_thornhoof") { }

    struct boss_zevrim_thornhoofAI : public BossAI
    {
        boss_zevrim_thornhoofAI(Creature* creature) : BossAI(creature, ENC_ZEVRIM_THORNHOOF) { m_instance = creature->GetInstanceScript(); }

        InstanceScript* m_instance;
        EventMap m_events;
        uint32 m_phase;

        void Reset()
        {
            m_instance->SetData(ENC_ZEVRIM_THORNHOOF, NOT_STARTED);
            m_events.Reset();
            m_phase = 0;
        }

        void EnterCombat(Unit* /*who*/)
        {
            m_instance->SetData(ENC_ZEVRIM_THORNHOOF, IN_PROGRESS);
        }

        void JustDied(Unit* /*Killer*/)
        {
            m_instance->SetData(ENC_ZEVRIM_THORNHOOF, DONE);
            Creature* oldIron = ObjectAccessor::GetCreature(*me, m_instance->GetData64(DATA_OLD_IRONBARK));
            me->SummonCreature(NPC_IRONBARK_THE_REDEEMED, oldIron->GetPosition());
            oldIron->DespawnOrUnsummon();
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
        return GetDireMaulAI<boss_zevrim_thornhoofAI>(creature);
    }
};

void AddSC_boss_zevrim_thornhoof()
{
    new boss_zevrim_thornhoof();
}


