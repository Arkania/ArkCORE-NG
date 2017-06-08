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
#include "ScriptedEscortAI.h"
#include "SpellMgr.h"
#include "Player.h"
#include "Creature.h"

enum Zone_zone_deepholm
{

};

// player
class player_zone_maelstrom : public PlayerScript
{
public:
    player_zone_maelstrom() : PlayerScript("player_zone_maelstrom") { }

    void OnQuestRemove(Player* player, uint32 questId) override
    {
        switch (questId)
        {
        case 0:
            break;
        }
    }

    void OnQuestStatusChange(Player* player, uint32 questId, QuestStatus status) override
    {
        switch (questId)
        {
        case 0:
            break;
        }
    }

};


void AddSC_zone_deepholm()
{
    new player_zone_maelstrom();

}

