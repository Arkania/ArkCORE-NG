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

// 42548
class npc_muddy_crawfish_42548 : public CreatureScript
{
public:
    npc_muddy_crawfish_42548() : CreatureScript("npc_muddy_crawfish_42548") { }

    struct npc_muddy_crawfish_42548AI : public ScriptedAI
    {
        npc_muddy_crawfish_42548AI(Creature* creature) : ScriptedAI(creature) { }

        void OnSpellClick(Unit* clicker, bool& /*result*/)  override
        { 
            if (Player* player = clicker->ToPlayer())
                if (player->GetQuestStatus(26226) == QUEST_STATUS_INCOMPLETE)
                    me->DespawnOrUnsummon(500);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_muddy_crawfish_42548AI(creature);
    }
};



void AddSC_orgrimmar()
{
    new npc_muddy_crawfish_42548();

}
