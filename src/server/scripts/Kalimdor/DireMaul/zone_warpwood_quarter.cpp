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
#include "GameObjectAI.h"
#include "GameObject.h"
#include "ScriptedEscortAI.h"
#include "ScriptedGossip.h"
#include "MoveSplineInit.h"
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

    bool OnGossipHello(Player* player, Creature* creature) override
    { 
        uint8 rol = CAST_AI(npc_pusillin_14354AI, creature->AI())->m_home_pos_counter;
        switch (rol)
        {
            case 0:
                player->ADD_GOSSIP_ITEM_DB(5709, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(6877, creature->GetGUID());
                break;
            case 1:
                player->ADD_GOSSIP_ITEM_DB(5710, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU(6878, creature->GetGUID());
                break;
            case 2:
                player->ADD_GOSSIP_ITEM_DB(5711, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->SEND_GOSSIP_MENU(6879, creature->GetGUID());
                break;
            case 3:
                player->ADD_GOSSIP_ITEM_DB(5712, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->SEND_GOSSIP_MENU(6880, creature->GetGUID());
                break;
            case 4:
                player->ADD_GOSSIP_ITEM_DB(5713, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->SEND_GOSSIP_MENU(6881, creature->GetGUID());
                break;
        }

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        CAST_AI(npc_pusillin_14354AI, creature->AI())->RunAway(player, action);
        return false;
    }

    struct npc_pusillin_14354AI : public ScriptedAI
    {
        npc_pusillin_14354AI(Creature* creature) : ScriptedAI(creature) { m_instance = creature->GetInstanceScript(); }

        InstanceScript* m_instance;
        uint32 m_home_pos_counter;
        uint32 m_phase;
        uint32 m_timer;
        uint32 m_max_waypoints;

        void Reset() override
        {
            m_home_pos_counter = 0;
            m_phase = 0;
            m_timer = 1000;
            m_max_waypoints = 0;
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == WAYPOINT_MOTION_TYPE && id == m_max_waypoints)
            {
                me->SetHomePosition(me->GetPosition());
                m_home_pos_counter++;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_timer < diff)
            {
                m_timer = 1000;
                if (m_phase)
                    DoWork();
            }
            else
                m_timer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

        void DoWork()
        {
            switch (m_phase)
            {
                case 1001:
                {                    
                    me->GetMotionMaster()->MovePath(me->GetDBTableGUIDLow() * 10 + 1, false);
                    m_max_waypoints = 7;
                    m_phase = 1;
                    m_timer = 400;
                    break;
                }
                case 1002:
                {
                    me->GetMotionMaster()->MovePath(me->GetDBTableGUIDLow() * 10 + 2, false);
                    m_max_waypoints = 7;
                    m_phase = 2;
                    m_timer = 400;
                    break;
                }
                case 1003:
                {
                    me->GetMotionMaster()->MovePath(me->GetDBTableGUIDLow() * 10 + 3, false);
                    m_max_waypoints = 8;
                    m_phase = 3;
                    m_timer = 400;
                    break;
                }
                case 1004:
                {
                    me->GetMotionMaster()->MovePath(me->GetDBTableGUIDLow() * 10 + 4, false);
                    m_max_waypoints = 2;
                    m_phase = 4;
                    m_timer = 400;
                    break;
                }
                case 1005:
                {
                    Talk(5);
                    m_phase = 1006;
                    m_timer = 400;
                    break;
                }
                case 1006:                   
                    me->setFaction(14);
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->CastSpell(me, 22735);
                    m_phase = 6;
                    if (Player* player = me->FindNearestPlayer(10.0f))
                    {
                        me->Attack(player, true);
                        if (Creature* npc = me->SummonCreature(13276, me->GetNearPosition(4, frand(3.0f, 6.2f))))
                            npc->Attack(player, true);
                        if (Creature* npc = me->SummonCreature(13276, me->GetNearPosition(4, frand(3.0f, 6.2f))))
                            npc->Attack(player, true);
                        if (Creature* npc = me->SummonCreature(13276, me->GetNearPosition(4, frand(3.0f, 6.2f))))
                            npc->Attack(player, true);
                        if (Creature* npc = me->SummonCreature(13276, me->GetNearPosition(4, frand(3.0f, 6.2f))))
                            npc->Attack(player, true);
                    }
                    break;
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                    Talk(m_phase);
                    m_phase = 6;
                    break;
            }
        }

        void RunAway(Player* player, uint32 action)
        {
            m_phase = action;
            m_timer = 100;
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