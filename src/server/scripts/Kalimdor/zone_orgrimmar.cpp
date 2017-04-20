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


enum eOrgrimmar
{
    QUEST_A_PERSONAL_SUMMONS = 28790,
};


// 52514 
class item_thonks_spyglass_52514 : public ItemScript
{
public:
    item_thonks_spyglass_52514() : ItemScript("item_thonks_spyglass_52514") { }

    bool OnUse(Player* player, Item* item, SpellCastTargets const& targets) override
    {
        if (player->GetQuestStatus(25187) == QUEST_STATUS_INCOMPLETE)
        {
            if (!player->GetReqKillOrCastCurrentCount(25187, 39357))
                player->CastSpell(player, 73741, TRIGGERED_NONE);
            else if (!player->GetReqKillOrCastCurrentCount(25187, 39358))
                player->CastSpell(player, 73763, TRIGGERED_NONE);
            else if (!player->GetReqKillOrCastCurrentCount(25187, 39359))
                player->CastSpell(player, 73764, TRIGGERED_NONE);
            else if (!player->GetReqKillOrCastCurrentCount(25187, 39360))
                player->CastSpell(player, 73765, TRIGGERED_NONE);
        }

        return false;
    }
};

// 39320 Raggan
class npc_durotar_watershed_telescope_39320 : public CreatureScript
{
public:
    npc_durotar_watershed_telescope_39320() : CreatureScript("npc_durotar_watershed_telescope_39320") { }

    enum eQuest
    {
        EVENT_TIMEOUT = 1,
        EVENT_EMOTE = 2,
        EVENT_FINALE = 3,
    };

    struct npc_durotar_watershed_telescope_39320AI : public ScriptedAI
    {
        npc_durotar_watershed_telescope_39320AI(Creature* creature) : ScriptedAI(creature) { }

        uint64 m_playerGUID;
        uint64 m_homeGUID;
        EventMap m_events;
        Position pos;

        void InitializeAI() override
        {
            m_playerGUID = me->GetCharmerOrOwnerOrOwnGUID();
            m_events.ScheduleEvent(EVENT_TIMEOUT, 60000);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                if (GameObject* gobject = player->FindNearestGameObject(301050, 10.0f))
                {
                    pos = player->GetPosition();
                    m_homeGUID = gobject->GetGUID();
                }
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override
        {
            me->SetSpeed(MOVE_RUN, 12.0f);
            me->GetMotionMaster()->MovePath(3932001, false);
        }

        void MovementInform(uint32 type, uint32 pointId) override
        {
            if (type == WAYPOINT_MOTION_TYPE)
                if (pointId == 2)
                    m_events.ScheduleEvent(EVENT_EMOTE, 4000);
                else if (pointId == 3)
                    m_events.ScheduleEvent(EVENT_FINALE, 1000);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TIMEOUT:
                    {
                        me->DespawnOrUnsummon(100);
                        break;
                    }
                    case EVENT_EMOTE:
                    {
                        if (Creature* npc = me->FindNearestCreature(39326, 30.0f))
                            npc->HandleEmote(EMOTE_ONESHOT_ROAR);
                        break;
                    }
                    case EVENT_FINALE:
                    {
                        if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                            if (GameObject* go = ObjectAccessor::GetGameObject(*me, m_homeGUID))
                            {
                                player->KilledMonsterCredit(39357);
                                player->ExitVehicle();
                                player->NearTeleportTo(go->GetPositionX(), go->GetPositionY(), go->GetPositionZ(), go->GetOrientation());
                                me->DespawnOrUnsummon(100);
                            }
                        break;
                    }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_durotar_watershed_telescope_39320AI(creature);
    }
};

// 39345 Tekla
class npc_durotar_watershed_telescope_39345 : public CreatureScript
{
public:
    npc_durotar_watershed_telescope_39345() : CreatureScript("npc_durotar_watershed_telescope_39345") { }

    enum eQuest
    {
        EVENT_TIMEOUT = 1,
        EVENT_FINALE = 2,
    };

    struct npc_durotar_watershed_telescope_39345AI : public ScriptedAI
    {
        npc_durotar_watershed_telescope_39345AI(Creature* creature) : ScriptedAI(creature) { }

        uint64 m_playerGUID;
        uint64 m_homeGUID;
        EventMap m_events;
        Position pos;

        void InitializeAI() override
        {
            m_playerGUID = me->GetCharmerOrOwnerOrOwnGUID();
            m_events.ScheduleEvent(EVENT_TIMEOUT, 60000);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                if (GameObject* gobject = player->FindNearestGameObject(301050, 10.0f))
                {
                    pos = player->GetPosition();
                    m_homeGUID = gobject->GetGUID();
                }
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override
        {
            me->SetSpeed(MOVE_RUN, 12.0f);
            me->GetMotionMaster()->MovePath(3934501, false);
        }

        void MovementInform(uint32 type, uint32 pointId) override
        {
            if (type == WAYPOINT_MOTION_TYPE && pointId == 3)
                m_events.ScheduleEvent(EVENT_FINALE, 1000);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TIMEOUT:
                    {
                        me->DespawnOrUnsummon(100);
                        break;
                    }
                    case EVENT_FINALE:
                    {
                        if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                            if (GameObject* go = ObjectAccessor::GetGameObject(*me, m_homeGUID))
                            {
                                player->KilledMonsterCredit(39358);
                                player->ExitVehicle();
                                player->NearTeleportTo(go->GetPositionX(), go->GetPositionY(), go->GetPositionZ(), go->GetOrientation());
                                me->DespawnOrUnsummon(100);
                            }
                        break;
                    }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_durotar_watershed_telescope_39345AI(creature);
    }
};

// 39346 Misha
class npc_durotar_watershed_telescope_39346 : public CreatureScript
{
public:
    npc_durotar_watershed_telescope_39346() : CreatureScript("npc_durotar_watershed_telescope_39346") { }

    enum eQuest
    {
        EVENT_TIMEOUT = 1,
        EVENT_FINALE = 2,
    };

    struct npc_durotar_watershed_telescope_39346AI : public ScriptedAI
    {
        npc_durotar_watershed_telescope_39346AI(Creature* creature) : ScriptedAI(creature) { }

        uint64 m_playerGUID;
        uint64 m_homeGUID;
        EventMap m_events;
        Position pos;

        void InitializeAI() override
        {
            m_playerGUID = me->GetCharmerOrOwnerOrOwnGUID();
            m_events.ScheduleEvent(EVENT_TIMEOUT, 60000);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                if (GameObject* gobject = player->FindNearestGameObject(301050, 10.0f))
                {
                    pos = player->GetPosition();
                    m_homeGUID = gobject->GetGUID();
                }
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override
        {
            me->SetSpeed(MOVE_RUN, 12.0f);
            me->GetMotionMaster()->MovePath(3934601, false);
        }

        void MovementInform(uint32 type, uint32 pointId) override
        {
            if (type == WAYPOINT_MOTION_TYPE && pointId == 3)
                m_events.ScheduleEvent(EVENT_FINALE, 1000);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TIMEOUT:
                    {
                        me->DespawnOrUnsummon(100);
                        break;
                    }
                    case EVENT_FINALE:
                    {
                        if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                            if (GameObject* go = ObjectAccessor::GetGameObject(*me, m_homeGUID))
                            {
                                player->KilledMonsterCredit(39359);
                                player->ExitVehicle();
                                player->NearTeleportTo(go->GetPositionX(), go->GetPositionY(), go->GetPositionZ(), go->GetOrientation());
                                me->DespawnOrUnsummon(100);
                            }
                        break;
                    }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_durotar_watershed_telescope_39346AI(creature);
    }
};

// 39347 Zen'Taji
class npc_durotar_watershed_telescope_39347 : public CreatureScript
{
public:
    npc_durotar_watershed_telescope_39347() : CreatureScript("npc_durotar_watershed_telescope_39347") { }

    enum eQuest
    {
        EVENT_TIMEOUT = 1,
        EVENT_FINALE = 2,
    };

    struct npc_durotar_watershed_telescope_39347AI : public ScriptedAI
    {
        npc_durotar_watershed_telescope_39347AI(Creature* creature) : ScriptedAI(creature) { }

        uint64 m_playerGUID;
        uint64 m_homeGUID;
        EventMap m_events;
        Position pos;

        void InitializeAI() override
        {
            m_playerGUID = me->GetCharmerOrOwnerOrOwnGUID();
            m_events.ScheduleEvent(EVENT_TIMEOUT, 60000);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                if (GameObject* gobject = player->FindNearestGameObject(301050, 10.0f))
                {
                    pos = player->GetPosition();
                    m_homeGUID = gobject->GetGUID();
                }
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override
        {
            me->SetSpeed(MOVE_RUN, 12.0f);
            me->GetMotionMaster()->MovePath(3934701, false);
        }

        void MovementInform(uint32 type, uint32 pointId) override
        {
            if (type == WAYPOINT_MOTION_TYPE && pointId == 3)
                m_events.ScheduleEvent(EVENT_FINALE, 1000);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TIMEOUT:
                    {
                        me->DespawnOrUnsummon(100);
                        break;
                    }
                    case EVENT_FINALE:
                    {
                        if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                            if (GameObject* go = ObjectAccessor::GetGameObject(*me, m_homeGUID))
                            {
                                player->KilledMonsterCredit(39360);
                                player->ExitVehicle();
                                player->NearTeleportTo(go->GetPositionX(), go->GetPositionY(), go->GetPositionZ(), go->GetOrientation());
                                me->DespawnOrUnsummon(100);
                            }
                        break;
                    }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_durotar_watershed_telescope_39347AI(creature);
    }
};

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

// spell 94687
class spell_waters_of_farseeing_94687 : public SpellScriptLoader
{
public:
    spell_waters_of_farseeing_94687() : SpellScriptLoader("spell_waters_of_farseeing_94687") { }

    class spell_waters_of_farseeing_94687_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_waters_of_farseeing_94687_AuraScript);

        void OnApply(AuraEffect const* aurEff, AuraEffectHandleModes mode)
        {
            if (aurEff->GetMiscValue() == 807)
                if (Unit* caster = GetCaster())                
                    if (Player* player = caster->ToPlayer())
                        if (player->GetQuestStatus(28805) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(28826) == QUEST_STATUS_INCOMPLETE)
                            player->KilledMonsterCredit(50054);
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_waters_of_farseeing_94687_AuraScript::OnApply, EFFECT_0, SPELL_AURA_SCREEN_EFFECT, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_waters_of_farseeing_94687_AuraScript();
    }
};

// 4801
class at_orgrimmar_command_board_1 : public AreaTriggerScript
{
public:
    at_orgrimmar_command_board_1() : AreaTriggerScript("at_orgrimmar_command_board_1") { }

    bool OnTrigger(Player* player, const AreaTriggerEntry* at) override
    {
        if (player->getLevel() < 80 || player->GetTeamId() != TEAM_HORDE)
            return false;

        if (player->GetQuestStatus(28790) != QUEST_STATUS_NONE)
            return false;

        if (Quest const* quest = sObjectMgr->GetQuestTemplate(QUEST_A_PERSONAL_SUMMONS))
            if (GameObject* go = player->FindNearestGameObject(206109, 50.0f))
                if (player->CanTakeQuest(quest, false))
                {
                    player->AddQuestAndCheckCompletion(quest, go);
                    return true;
                }

        return false;
    }
};

// 4802
class at_orgrimmar_command_board_2 : public AreaTriggerScript
{
public:
    at_orgrimmar_command_board_2() : AreaTriggerScript("at_orgrimmar_command_board_2") { }

    bool OnTrigger(Player* player, const AreaTriggerEntry* at) override
    {
        if (player->getLevel() < 80 || player->GetTeamId() != TEAM_HORDE)
            return false;

        if (player->GetQuestStatus(28790) != QUEST_STATUS_NONE)
            return false;

        if (Quest const* quest = sObjectMgr->GetQuestTemplate(QUEST_A_PERSONAL_SUMMONS))
            if (GameObject* go = player->FindNearestGameObject(206116, 50.0f))
                if (player->CanTakeQuest(quest, false))
                {
                    player->AddQuestAndCheckCompletion(quest, go);
                    return true;
                }

        return false;
    }
};

// 7354
class at_orgrimmar_teleport_area : public AreaTriggerScript
{
public:
    at_orgrimmar_teleport_area() : AreaTriggerScript("at_orgrimmar_teleport_area") { }

    bool OnTrigger(Player* player, const AreaTriggerEntry* at) override
    {
        if (player->getLevel() < 80 || player->GetTeamId() != TEAM_HORDE)
            return false;

        if (player->GetQuestStatus(28790) != QUEST_STATUS_NONE)
            return false;

        if (Quest const* quest = sObjectMgr->GetQuestTemplate(QUEST_A_PERSONAL_SUMMONS))
            if (Creature* npc = player->FindNearestCreature(45244, 50.0f))
                if (player->CanTakeQuest(quest, false))
                {
                    player->AddQuestAndCheckCompletion(quest, npc);
                    return true;
                }

        return false;
    }
};


void AddSC_orgrimmar()
{
    new npc_muddy_crawfish_42548();
    new spell_waters_of_farseeing_94687();
    new item_thonks_spyglass_52514();
    new npc_durotar_watershed_telescope_39320();
    new npc_durotar_watershed_telescope_39345();
    new npc_durotar_watershed_telescope_39346();
    new npc_durotar_watershed_telescope_39347();
    new at_orgrimmar_command_board_1();
    new at_orgrimmar_command_board_2();
    new at_orgrimmar_teleport_area();
}

