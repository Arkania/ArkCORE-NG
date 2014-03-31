/*
 * Copyright (C) 2011-2014 ArkCORE <http://www.arkania.net/>
 *
 * This file is NOT free software. Third-party users can NOT redistribute 
 * it or modify it. If you find it, you are either hacking something, or very 
 * lucky (presuming someone else managed to hack it).
 */

/* ScriptData
SDName: dragon_soul_teleport_and_transport
SD%Complete: 50%
SDComment:
SDCategory: Teleport and Transport
EndScriptData
*/

#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "dragon_soul.h"

class npc_eiendormi : public CreatureScript
{
    public:
        npc_eiendormi() : CreatureScript("npc_eiendormi") { }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (InstanceScript* instance = creature->GetInstanceScript())
            {
                if (instance->GetBossState(BOSS_MORCHOK) == DONE)
                    player->TeleportTo(967, -1870.114f, -3077.727f, -176.308f, 0.390f);
            }

            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            return true;
        }
};

class npc_valeera_tele : public CreatureScript
{
    public:
        npc_valeera_tele() : CreatureScript("npc_valeera_tele") { }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (InstanceScript* instance = creature->GetInstanceScript())
            {
                if (instance->GetBossState(BOSS_MORCHOK) == DONE)
                    player->TeleportTo(967, -1735.930f, -1818.239f, -219.328f, 0.0f);
            }

            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            return true;
        }
};

class npc_nethestrasz : public CreatureScript
{
    public:
        npc_nethestrasz() : CreatureScript("npc_nethestrasz") { }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (InstanceScript* instance = creature->GetInstanceScript())
            {
                if (instance->GetBossState(BOSS_UNSLEEPING) == DONE && instance->GetBossState(BOSS_WARLORD) == DONE)
                    player->TeleportTo(967, -1786.69f, -2393.67f, 341.355f, 0.16f);
            }

            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            return true;
        }
};

class travel_to_wyrmrest_base : public CreatureScript
{
    public:
        travel_to_wyrmrest_base() : CreatureScript("travel_to_wyrmrest_base") { }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (InstanceScript* instance = creature->GetInstanceScript())
            {
                if (instance->GetBossState(DATA_PORTALS_ON_OFF) == DONE)
                {
                    player->TeleportTo(967, -1793.22f, -2391.78f, 45.604f, 5.871f);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }
            }

            player->CLOSE_GOSSIP_MENU();
            return true;
        }
};

class travel_to_wyrmrest_summit : public CreatureScript
{
    public:
        travel_to_wyrmrest_summit() : CreatureScript("travel_to_wyrmrest_summit") { }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (InstanceScript* instance = creature->GetInstanceScript())
            {
                if (instance->GetBossState(DATA_PORTALS_ON_OFF) == DONE)
                {
                    player->TeleportTo(967, -1786.92f, -2393.18f, 341.355f, 6.141f);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }
            }

            player->CLOSE_GOSSIP_MENU();
            return true;
        }
};

class travel_to_the_eye_of_eternity : public CreatureScript
{
    public:
        travel_to_the_eye_of_eternity() : CreatureScript("travel_to_the_eye_of_eternity") { }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (InstanceScript* instance = creature->GetInstanceScript())
            {
                if (instance->GetBossState(BOSS_UNSLEEPING) == DONE && instance->GetBossState(BOSS_WARLORD) == DONE)
                {
                    player->TeleportTo(967, 13629.7f, 13611.9f, 123.482f, 3.468f);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }
            }

            player->CLOSE_GOSSIP_MENU();
            return true;
        }
};

class travel_to_the_deck_of_the_skyfire : public CreatureScript
{
    public:
        travel_to_the_deck_of_the_skyfire() : CreatureScript("travel_to_the_deck_of_the_skyfire") { }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (InstanceScript* instance = creature->GetInstanceScript())
            {
                if (instance->GetBossState(BOSS_ULTRAXION) == DONE)
                {
                    player->TeleportTo(967, 13397.298f, -12131.405f, 153.8732f, 3.152f);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                }
            }

            player->CLOSE_GOSSIP_MENU();
            return true;
        }
};

void AddSC_dragon_soul_teleport_and_transport()
{
    new npc_eiendormi();
    new npc_valeera_tele();
    new npc_nethestrasz();
    new travel_to_wyrmrest_base;
    new travel_to_wyrmrest_summit;
    new travel_to_the_eye_of_eternity;
    new travel_to_the_deck_of_the_skyfire;
}