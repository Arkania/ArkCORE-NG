/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "throne_of_the_four_winds.h"

enum Spells
{
    SPELL_TORNADO_VISUAL = 87856
};

class npc_tornado_moving : public CreatureScript
{
    public:
        npc_tornado_moving() :  CreatureScript("npc_tornado_moving") { }

        struct npc_tornado_movingAI : public ScriptedAI
        {
            npc_tornado_movingAI(Creature* creature) : ScriptedAI(creature)
            {

            }

            bool MoveSide; // true = right, false = left
            float defaultDistX;
            float defaultDistY;

            void IsSummonedBy(Unit* /*summoner*/)
            {
                //me->AddAura(SPELL_TORNADO_VISUAL,me);

                defaultDistX = GetAlakir()->GetPositionX() > me->GetPositionX() ? GetAlakir()->GetPositionX() - me->GetPositionX() : me->GetPositionX() - GetAlakir()->GetPositionX();
                defaultDistY = GetAlakir()->GetPositionY() > me->GetPositionY() ? GetAlakir()->GetPositionY() - me->GetPositionY() : me->GetPositionY() - GetAlakir()->GetPositionY();

                std::list<Creature*> tornados;
                GetCreatureListWithEntryInGrid(tornados, me, me->GetEntry(), 40.0f);

                //if (!tornados.empty() && tornados.size() < 4)
                    //me->SummonCreature(me->GetEntry(),me->GetPositionX() - (std::cos(me->GetOrientation())*2),me->GetPositionY() - (std::sin(me->GetOrientation())*2),me->GetPositionZ());

                if (me->GetEntry() == 48854)
                    MoveSide = true; // west
                else
                    MoveSide = false; // east
            }

            void UpdateAI(uint32 /*diff*/)
            {
                if (GetAlakir() && GetAlakir()->IsAlive())
                {
                    float distanceX = GetAlakir()->GetPositionX() > me->GetPositionX() ? GetAlakir()->GetPositionX() - me->GetPositionX() : me->GetPositionX() - GetAlakir()->GetPositionX();
                    float distanceY = GetAlakir()->GetPositionY() > me->GetPositionY() ? GetAlakir()->GetPositionY() - me->GetPositionY() : me->GetPositionY() - GetAlakir()->GetPositionY();
                    me->GetMotionMaster()->MovePoint(0, (distanceX < defaultDistX) ? me->GetPositionX() + MoveSide ? 1 : - 1 : me->GetPositionX(),(distanceY < defaultDistY) ? me->GetPositionY() + MoveSide ? 1 : - 1 : me->GetPositionY(),me->GetPositionZ());
                }
            }

            Creature* GetAlakir()
            {
                return me->FindNearestCreature(BOSS_ALAKIR, 5000.0f, true);
            }

        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_tornado_movingAI(creature);
        }
};

void AddSC_boss_alakir()
{
    //new boss_alakir();
    new npc_tornado_moving();
}