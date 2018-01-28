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

#include "script_helper.h"
#include "Creature.h"
#include "GameObjectAI.h"
#include "GameObject.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "ScriptMgr.h"
#include "SpellMgr.h"
#include "Transport.h"
#include "TransportMgr.h"
#include "Vehicle.h"

enum eStormwind
{    
    NPC_SHIP_TO_VASHJIR_197195 = 197195,
    NPC_CAPTAIN_TAYLOR = 42103,
    NPC_STORMWIND_SOLDIER = 99980,
    NPC_STORMWIND_SOLDIER_42021 = 42021,
    NPC_STORMWIND_SOLDIER_42022 = 42022,
    NPC_STORMWIND_RECRUIT_42059 = 42059,
    NPC_STORMWIND_RECRUIT_42095 = 42095,
    NPC_STORMWIND_RECRUIT_42096 = 42096,

    SPELL_QUEST_GENERIC_ZONE_SPECIFIC_02 = 59074,
    SPELL_QUEST_ZONE_SPECIFIC_02 = 78318,
    QUEST_CALL_OF_DUTY_ALLIANCE = 14482,
    QUEST_A_PERSONAL_SUMMONS = 28825,
};

enum eNpcStormwindSoldier /* List of database guids of all creature involved bridge/ship to vashjir : Alliance*/
{
    eStormSoldAA = 51753,
    eStormSoldAB = 51756,
    eStormSoldBA = 51758,
    eStormSoldBB = 51755,
    eStormSoldBC = 51751,
    eStormSoldCA = 51757,
    eStormSoldCB = 51752,
    eStormSoldDA = 51722,
    eStormSoldTay = 117111,
};


// player
class player_zone_stormwind_city : public PlayerScript
{
public:
    player_zone_stormwind_city() : PlayerScript("player_zone_stormwind_city") { }

    void OnQuestRemove(Player* player, uint32 questId) override
    {
        switch (questId)
        {
        case QUEST_CALL_OF_DUTY_ALLIANCE:
            player->RemoveAura(SPELL_QUEST_GENERIC_ZONE_SPECIFIC_02);
            break;
        }
    }
};

 // 2708
class npc_archmage_malin_2708 : public CreatureScript
{
public:
    npc_archmage_malin_2708() : CreatureScript("npc_archmage_malin_2708") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == 1)
        {
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -3752.51f, -4456.33f, 64.97f, 0.7286f);
            return true;
        }
        return false;
    }
};

// 2746
class at_stormwind_command_board : public AreaTriggerScript
{
public:
    at_stormwind_command_board() : AreaTriggerScript("at_stormwind_command_board") { }

    bool OnTrigger(Player* player, const AreaTriggerEntry* at) override
    {
        if (player->getLevel() < 80 || player->GetTeamId() != TEAM_ALLIANCE)
            return false;

        if (player->GetQuestStatus(28825) != QUEST_STATUS_NONE)
            return false;

        if (Quest const* quest = sObjectMgr->GetQuestTemplate(QUEST_A_PERSONAL_SUMMONS))
            if (GameObject* go = player->FindNearestGameObject(206111, 50.0f))
                if (player->CanTakeQuest(quest, false))
                {
                    player->AddQuest(quest, go);
                    return true;
                }

        return false;
    }
};

// 7350
class at_stormwind_teleport_area : public AreaTriggerScript
{
public:
    at_stormwind_teleport_area() : AreaTriggerScript("at_stormwind_teleport_area") { }

    bool OnTrigger(Player* player, const AreaTriggerEntry* at) override
    {
        if (player->getLevel() < 80 || player->GetTeamId() != TEAM_ALLIANCE)
            return false;

        if (player->GetQuestStatus(28825) != QUEST_STATUS_NONE)
            return false;

        if (Quest const* quest = sObjectMgr->GetQuestTemplate(QUEST_A_PERSONAL_SUMMONS))
            if (Creature* npc = player->FindNearestCreature(45226, 50.0f))
                if (player->CanTakeQuest(quest, false))
                {
                    player->AddQuest(quest, npc);
                    return true;
                }

        return false;
    }
};

// 36799
class npc_recruiter_burns_36799 : public CreatureScript
{
public:
    npc_recruiter_burns_36799() : CreatureScript("npc_recruiter_burns_36799") { }

    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest) 
    { 
        switch (quest->GetQuestId())
        {
        case QUEST_CALL_OF_DUTY_ALLIANCE:
            player->CastSpell(player, SPELL_QUEST_GENERIC_ZONE_SPECIFIC_02, true);
            break;
        }
        return false; 
    }
};

// 42103
class  npc_captain_taylor_42103 : public CreatureScript
{
public:
    npc_captain_taylor_42103() : CreatureScript("npc_captain_taylor_42103") { }

    struct npc_captain_taylor_42103AI : public ScriptedAI
    {
        npc_captain_taylor_42103AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;

        void Initialize()
        {
        }

        void Reset() override
        {
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case 0:
                    break;
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_captain_taylor_42103AI(creature);
    }
};

// 42021 42022
class  npc_stormwind_soldier_42021 : public CreatureScript
{
public:
    npc_stormwind_soldier_42021() : CreatureScript("npc_stormwind_soldier_42021") { }

    struct npc_stormwind_soldier_42021AI : public ScriptedAI
    {
        npc_stormwind_soldier_42021AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;

        void Initialize()
        {
        }

        void Reset() override
        {
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case 0:
                    break;
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_stormwind_soldier_42021AI(creature);
    }
};

// 197195 ally
class go_ship_to_vashjir_197195 : public GameObjectScript
{
public:
    go_ship_to_vashjir_197195() : GameObjectScript("go_ship_to_vashjir_197195") {}

    struct go_ship_to_vashjir_197195AI : public GameObjectAI
    {
        go_ship_to_vashjir_197195AI(GameObject* go) : GameObjectAI(go) { InitializeShip(); }

        EventMap m_events;
        uint64   m_bunnyBridgeGUID;
        uint64   m_commanderShipGUID;
        std::map<uint32, uint64> m_soldierShipGUID;

        void InitializeShip()
        {
            m_commanderShipGUID = 0;
            m_soldierShipGUID.clear();
        }

        void Reset()
        {
            m_bunnyBridgeGUID = 0;
            InitializeShip();
        }

        void EventInform(uint32 eventId)
        {
            if (m_bunnyBridgeGUID)
                if (Creature* bunny = sObjectAccessor->GetCreature(*go, m_bunnyBridgeGUID))
                    bunny->AI()->DoAction(eventId);

            switch (eventId)
            {
            case 25769:
                m_events.ScheduleEvent(EVENT_DESPAWN_PART_00, 2000);
                break;
            case 24015:
                printf("");
                break;
            case 24986:
                printf("");
                break;
            case 24009:
                printf("");
                break;
            case 25075:
                printf("");
                break;
            case 24014:
                printf("");
                break;
            case 22520:
                printf("");
                break;
            case 24036:
                printf("");
                break;
            }
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case 32520: // alliance bunny controller outside ship
                m_bunnyBridgeGUID = guid;
                break;
            case eStormSoldTay:
            case NPC_CAPTAIN_TAYLOR:
                printf("");
                break;
            case eStormSoldAA:
            case eStormSoldAB:
            case eStormSoldBA:
            case eStormSoldBB:
            case eStormSoldBC:
            case eStormSoldCA:
            case eStormSoldCB:
            case eStormSoldDA:
            case NPC_STORMWIND_SOLDIER:
                printf("");
                break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_DESPAWN_PART_00:
                    if (Transport* transport = go->ToTransport())
                    {
                        if (Creature* npc = sObjectAccessor->GetCreature(*go, m_commanderShipGUID))
                        {
                            transport->RemovePassenger(npc);
                            npc->DespawnOrUnsummon(100);
                            m_commanderShipGUID = 0;
                        }
                        for (auto guid : m_soldierShipGUID)
                            if (Creature* npc = sObjectAccessor->GetCreature(*go, guid.second))
                            {
                                transport->RemovePassenger(npc);
                                npc->DespawnOrUnsummon(100);
                                m_soldierShipGUID[npc->GetDBTableGUIDLow()] = 0;
                            }
                    }
                    break;
                }
            }
        }

        void SetShipVisibleState(bool isVisible)
        {
            bool _visible = isVisible | IsPassengerPlayerBoarded();
            if (Transport* transport = go->ToTransport())
            {
                if (_visible)
                {
                    go->m_invisibility.SetValue(INVISIBILITY_GENERAL, 0);
                    go->m_invisibility.DelFlag(INVISIBILITY_GENERAL);
                }
                else
                    go->m_invisibility.AddFlag(INVISIBILITY_GENERAL);
                go->m_invisibility.SetValue(INVISIBILITY_GENERAL, 10000);
            }
        }

        Creature* FindCreatureWorldwide(uint64 guid)
        {
            if (Creature* cr = HashMapHolder<Creature>::Find(guid))
                return cr;

            return nullptr;
        }

        bool IsPassengerPlayerBoarded()
        {
            if (Transport* transport = go->ToTransport())
            {
                std::set<WorldObject*> pList = transport->GetPassengers();
                if (!pList.empty())
                    return true;
            }
            return false;
        }

        uint32 GetPassengerCrewCount()
        {
            if (Transport* transport = go->ToTransport())
            {
                std::set<WorldObject*> pList = transport->GetStaticPassengers();
                return pList.size();
            }
            return 0;
        }

        GameObject* CreateGameObjectAsPassenger(uint32 entry, uint32 map, float x, float y, float z, float o)
        {
            if (Transport* transport = go->ToTransport())
                if (uint32 guid = sObjectMgr->GenerateLowGuid(HIGHGUID_GAMEOBJECT))
                {
                    GameObjectData& data = sObjectMgr->NewGOData(guid);
                    data.id = entry;
                    data.mapid = map;
                    data.phaseMask = 1;
                    data.spawnMask = 1;
                    data.posX = x;
                    data.posY = y;
                    data.posZ = z;
                    data.orientation = o;
                    GameObject* g = transport->CreateGOPassenger(guid, &data);
                    sObjectMgr->AddGameobjectToGrid(guid, &data);
                    return g;
                }
        }

        Creature* CreateCreatureAsPassenger(uint32 entry, uint32 map, float x, float y, float z, float o)
        {
            if (Transport* transport = go->ToTransport())
                if (uint32 guid = sObjectMgr->GenerateLowGuid(HIGHGUID_UNIT))
                {
                    CreatureData& data = sObjectMgr->NewOrExistCreatureData(guid);
                    data.id = entry;
                    data.mapid = map;
                    data.phaseMask = 1;
                    data.spawnMask = 1;
                    data.posX = x;
                    data.posY = y;
                    data.posZ = z;
                    data.orientation = o;
                    Creature* c = transport->CreateNPCPassenger(guid, &data);
                    sObjectMgr->AddCreatureToGrid(guid, &data);
                    return c;
                }
            return nullptr;
        }

        Creature* GetStaticPassenger(uint32 entry)
        {
            if (Transport* transport = go->ToTransport())
            {
                const std::set<WorldObject*> spList = transport->GetStaticPassengers();
                for (auto wo : spList)
                    if (Creature* npc = wo->ToCreature())
                        if (npc->GetEntry() == entry)
                            return npc;
            }
            return nullptr;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return new go_ship_to_vashjir_197195AI(go);
    }
};

void AddSC_stormwind_city()
{
    new player_zone_stormwind_city();
    new npc_archmage_malin_2708();
    new at_stormwind_command_board();
    new at_stormwind_teleport_area();
    new npc_recruiter_burns_36799();
    new npc_captain_taylor_42103();
    new npc_stormwind_soldier_42021();
    new go_ship_to_vashjir_197195();

}
