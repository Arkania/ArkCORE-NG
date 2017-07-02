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
    SPELL_QUEST_GENERIC_ZONE_SPECIFIC_02 = 59074,
    SPELL_QUEST_ZONE_SPECIFIC_02 = 78318,
    QUEST_CALL_OF_DUTY = 14482,
    QUEST_A_PERSONAL_SUMMONS = 28825,
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
        case QUEST_CALL_OF_DUTY:
            player->CastSpell(player, SPELL_QUEST_GENERIC_ZONE_SPECIFIC_02, true);
            break;
        }
        return false; 
    }
};

// 40559  bunny, inside ship, as commander for quest "call of duty" Alliance
class npc_ship_to_vashjir_phase_caster_bunny_40559 : public CreatureScript
{
public:
    npc_ship_to_vashjir_phase_caster_bunny_40559() : CreatureScript("npc_ship_to_vashjir_phase_caster_bunny_40559") { }

    enum eNPC
    {
    };

    struct npc_ship_to_vashjir_phase_caster_bunny_40559AI : public ScriptedAI
    {
        npc_ship_to_vashjir_phase_caster_bunny_40559AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

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
                {
                    break; 
                }
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
        return new npc_ship_to_vashjir_phase_caster_bunny_40559AI(creature);
    }
};

void AddSC_stormwind_city()
{
    new npc_archmage_malin_2708();
    new at_stormwind_command_board();
    new at_stormwind_teleport_area();
    new npc_recruiter_burns_36799();
    new npc_ship_to_vashjir_phase_caster_bunny_40559();
}
