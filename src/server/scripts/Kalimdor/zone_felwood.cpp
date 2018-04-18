/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

/* ScriptData
SDName: Felwood
SD%Complete: 95
SDComment: Quest support:
SDCategory: Felwood
EndScriptData */

/* ContentData
EndContentData */

#include "ScriptMgr.h"
#include "script_helper.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Player.h"

class npc_impsy_47365 : public CreatureScript
{
public:
    npc_impsy_47365() : CreatureScript("npc_impsy_47365") {}

    enum script_enums
    {
        ENCHANTED_IMP_SAC = 88354,
        QUEST_CREDIT = 47365
    };

    struct npc_impsy_47365AI : public ScriptedAI
    {
        npc_impsy_47365AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap  _events;
        Position  _spawn_position;

        void Initialize()
        {
        }

        void Reset() override
        {
            float x, y, z;
            me->GetRespawnPosition(x, y, z);
            _spawn_position = Position(x, y, z);
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (Player* player = caster->ToPlayer())
                if (spell->Id == ENCHANTED_IMP_SAC)
                {
                    player->KilledMonsterCredit(QUEST_CREDIT);
                    me->DespawnOrUnsummon(0);
                }
        }

        void EnterCombat(Unit* who) override
        {
            _events.ScheduleEvent(EVENT_CHECK_FOR_PLAYER, 1000);
        }


        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_FOR_PLAYER:
                {
                    if (me->IsAlive())
                    {
                        if (me->GetDistance(_spawn_position) > 50)
                        {
                            me->CombatStop();
                            me->GetMotionMaster()->MovePoint(0, _spawn_position);
                        }
                        else
                        {
                            me->AI()->DoMeleeAttackIfReady();
                            _events.ScheduleEvent(EVENT_CHECK_FOR_PLAYER, 1000);
                        }
                    }

                }
                }
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_impsy_47365AI(creature);
    }
};

void AddSC_felwood()
{
    new npc_impsy_47365();
}
