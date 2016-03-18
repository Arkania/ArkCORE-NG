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
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "GameObjectAI.h"
#include "GameObject.h"
#include "Player.h"
#include "Vehicle.h"
#include "VehicleDefines.h"
#include "Transport.h"
#include "TransportMgr.h"


// 204828
class go_kurzen_cage_204828 : public GameObjectScript
{
public:
    go_kurzen_cage_204828() : GameObjectScript("go_kurzen_cage_204828") { }

    enum eDoor
    {
        QUEST_SPARED_FROM_MADNESS = 26736,
        NPC_OSBORN_OBNOTICUS = 43919,
        NPC_EMERINE_JUNIS = 43920,
        NPC_BERRIN_BURNQUILL = 43921
    };

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (player->GetQuestStatus(QUEST_SPARED_FROM_MADNESS) == QUEST_STATUS_INCOMPLETE)
        {
            if (Creature* osborn = go->FindNearestCreature(NPC_OSBORN_OBNOTICUS, 10.0f))
            {
                osborn->SetSpeed(MOVE_WALK, 0.8f);
                osborn->SetWalk(true);
                osborn->GetMotionMaster()->MovePoint(101, -11569.4f, -587.7f, 33.7f);
                osborn->AI()->Talk(0);
                osborn->DespawnOrUnsummon(7000);
                player->KilledMonsterCredit(NPC_OSBORN_OBNOTICUS);
            }
            if (Creature* emerine = go->FindNearestCreature(NPC_EMERINE_JUNIS, 10.0f))
            {
                emerine->SetSpeed(MOVE_WALK, 0.7f);
                emerine->SetWalk(true);
                emerine->GetMotionMaster()->MovePoint(102, -11569.4f, -587.7f, 33.7f);
                emerine->DespawnOrUnsummon(7000);
                player->KilledMonsterCredit(NPC_EMERINE_JUNIS);
            }
            if (Creature* berinn = go->FindNearestCreature(NPC_BERRIN_BURNQUILL, 10.0f))
            {
                berinn->SetSpeed(MOVE_WALK, 0.9f);
                berinn->SetWalk(true);
                berinn->GetMotionMaster()->MovePoint(103, -11569.4f, -587.7f, 33.7f);
                berinn->AI()->Talk(0);
                berinn->DespawnOrUnsummon(7000);
                player->KilledMonsterCredit(NPC_BERRIN_BURNQUILL);
            }
        }
        return false;
    }
};


void AddSC_zone_northern_stranglethorn()
{
    new go_kurzen_cage_204828();


}
