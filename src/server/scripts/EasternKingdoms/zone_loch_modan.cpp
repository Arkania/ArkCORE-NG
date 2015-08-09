/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
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
SDName: Loch_Modan
SD%Complete: 0
SDComment:
SDCategory: Loch Modan
EndScriptData */

/* ContentData
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Player.h"

enum eQuest26131
{
	QUEST_REINFORCEMENTS_FOR_LOCH_MODAN = 26131,
	NPC_PILOT_HAMMERFOOT = 1960,
};

class npc_pilot_hammerfoot : public CreatureScript
{
public:
	npc_pilot_hammerfoot() : CreatureScript("npc_pilot_hammerfoot") { }

	bool OnGossipHello(Player* player, Creature* creature) override
	{
		if (player->GetQuestStatus(QUEST_REINFORCEMENTS_FOR_LOCH_MODAN) == QUEST_STATUS_INCOMPLETE)
		{
			// player->PlayerTalkClass->SendCloseGossip();
			player->KilledMonsterCredit(NPC_PILOT_HAMMERFOOT);
		}
		
		return false;
	}
};


void AddSC_loch_modan()
{
	new npc_pilot_hammerfoot();
}
