/*
* Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
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
#include "GameObjectAI.h"
#include "GameObject.h"
#include "dire_maul.h"


// https://cata-twinhead.twinstar.cz/?object=176907 is the door to the last boss. 
// It should be opened for players by Ironbark the redeemed npc = 14241.
// http://www.wowhead.com/npc=11490/zevrim-thornhoof Kill him then ironbark the redeemed (14241) spawns.
// http://www.wowhead.com/npc=11491/old-ironbark  removes when zevrim is killed
// http://www.wowhead.com/npc=14241/ironbark-the-redeemed he spawns in same room as old ironbark near the door, after Zevrim is dead.

// "Old Ironbark becomes Ironbark the Redeemed after Zevrim Thornhoof is killed. He will then be able to break open the door leading to the final part of the instance."
// Players click on his Gossip (Gossip_menu_id = 5602) and he then moves to door and activates it, then dies.

// This object 177220 GUID: 189132 Crumble Wall is closed at instance start(East Wing)
// It should open after last boss of East Wing(Warpwood) is killed.
// boss http://www.wowhead.com/npc=11492/alzzin-the-wildshaper
// The door opens like a rock slide and reveals a passage leading to exit back to The Commons.
// North wing doors, as far as I remember no locked or boss activated doors in the Northwing.
// back in wotlk you had to have the crescent key to enter the front door of the northwing,
// not sure if that was depreciated after the Catalysm.

// http://www.wowhead.com/npc=14354/pusillin does not drop the key like he used to soo...  maybe some research on that.

// Other objects Crystal Pylons Crystal Generator : id = 177259, 177257, 177258, 179504, 179505
// Additionally, you need to shut down the five pylons scattered throughout Dire Maul West to
// eliminate the forcefield surrounding Immol'thar's prison : Pylons are shutdown by killing
// the mana mobs powering the Crystals.mobs should be in group of five surround each pylon.
// http://www.wowhead.com/?npc=11483  http://www.wowhead.com/npc=11480
// can't find the invisible wall the stops you getting to Immol'thar

// 14354
class npc_pusillin_14354 : public CreatureScript
{
public:
    npc_pusillin_14354() : CreatureScript("npc_pusillin_14354") { }

    struct npc_pusillin_14354AI : public ScriptedAI
    {
        npc_pusillin_14354AI(Creature* creature) : ScriptedAI(creature) { m_instance = creature->GetInstanceScript(); }

        InstanceScript* m_instance;

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDireMaulAI<npc_pusillin_14354AI>(creature);
    }
};

// 11491
class npc_old_ironbark_11491 : public CreatureScript
{
public:
    npc_old_ironbark_11491() : CreatureScript("npc_old_ironbark_11491") { }

    struct npc_old_ironbark_11491AI : public ScriptedAI
    {
        npc_old_ironbark_11491AI(Creature* creature) : ScriptedAI(creature) { m_instance = creature->GetInstanceScript(); }

        InstanceScript* m_instance;

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDireMaulAI<npc_old_ironbark_11491AI>(creature);
    }
};

// 14241 ironbark-the-redeemed
class npc_ironbark_the_redeemed_14241 : public CreatureScript
{
public:
    npc_ironbark_the_redeemed_14241() : CreatureScript("npc_ironbark_the_redeemed_14241") { }

    struct npc_ironbark_the_redeemed_14241AI : public ScriptedAI
    {
        npc_ironbark_the_redeemed_14241AI(Creature* creature) : ScriptedAI(creature) { m_instance = creature->GetInstanceScript(); }

        InstanceScript* m_instance;

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDireMaulAI<npc_ironbark_the_redeemed_14241AI>(creature);
    }
};

// 176907
class go_conservatory_door_176907 : public GameObjectScript
{
public:
    go_conservatory_door_176907() : GameObjectScript("go_conservatory_door_176907") { }

    struct go_conservatory_door_176907AI : public GameObjectAI
    {
        go_conservatory_door_176907AI(GameObject* go) : GameObjectAI(go) { _instance = go->GetInstanceScript(); }

        InstanceScript* _instance;

        void OnStateChanged(uint32 state, Unit* unit)
        {
          
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return GetDireMaulAI<go_conservatory_door_176907AI>(go);
    }
};

    
void AddSC_warpwood_quarter()
{
    new npc_pusillin_14354();
    new npc_old_ironbark_11491();
    new npc_ironbark_the_redeemed_14241();
    new go_conservatory_door_176907();

}