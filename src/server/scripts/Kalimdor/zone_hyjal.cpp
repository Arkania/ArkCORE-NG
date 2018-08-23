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
#include "Player.h"
#include "WorldSession.h"
#include "Vehicle.h"

#include "ScriptedEscortAI.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "CombatAI.h"
#include "PassiveAI.h"
#include "ObjectMgr.h"
#include "SpellInfo.h"
#include "SpellScript.h"
#include "VehicleDefines.h"
#include "Spell.h"

// spell 75935 75943
class spell_mount_75935 : public SpellScriptLoader
{
public:
    spell_mount_75935() : SpellScriptLoader("spell_mount_75935") { }

    class spell_mount_75935_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mount_75935_SpellScript);

        enum eSpell
        {
            QUEST_FLIGHT_IN_THE_FIRELANDS = 25523,
            QUEST_WAVE_ONE = 25525,
            QUEST_WAVE_TWO = 25544,
            QUEST_EGG_WAVE = 25560,
            QUEST_VIGILANCE_ON_WINGS = 29177,
            ITEM_TWILIGHT_FIRELANCE = 52716,
        };

        SpellCastResult CheckCast()
        {
            Player* player = nullptr;
            player = GetCaster()->ToPlayer();
            if (!player)
                player = GetOriginalCaster()->ToPlayer();
            if (player)
            {
                if (player->GetQuestStatus(QUEST_FLIGHT_IN_THE_FIRELANDS) == QUEST_STATUS_INCOMPLETE ||
                    player->GetQuestStatus(QUEST_WAVE_ONE) == QUEST_STATUS_INCOMPLETE ||
                    player->GetQuestStatus(QUEST_WAVE_TWO) == QUEST_STATUS_INCOMPLETE ||
                    player->GetQuestStatus(QUEST_EGG_WAVE) == QUEST_STATUS_INCOMPLETE ||
                    player->GetQuestStatus(QUEST_VIGILANCE_ON_WINGS) == QUEST_STATUS_INCOMPLETE)
                    if (Item* item = player->GetWeaponForAttack(BASE_ATTACK, true))
                        if (item->GetEntry() == ITEM_TWILIGHT_FIRELANCE)
                            return SPELL_CAST_OK;
            }

            return SPELL_FAILED_CUSTOM_ERROR;
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_mount_75935_SpellScript::CheckCast);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_mount_75935_SpellScript();
    }
};

// 40578 questgeber.. 
class npc_farden_talonshrike_40578 : public CreatureScript
{
public:
    npc_farden_talonshrike_40578() : CreatureScript("npc_farden_talonshrike_40578") { }

    enum eNPC
    {
        QUEST_FLIGHT_IN_THE_FIRELANDS = 25523,
        ITEM_TWILIGHT_FIRELANCE = 52716,
        PLAYER_GUID = 99999,
        ACTION_START_ANIM = 1,
        EVENT_ANIM_TIMER = 1,
        EVENT_ANIM_TIMEOUT = 2,
        SAY_GRAB = 0,
        SAY_EQUIP = 1,
        SAY_MOUNT = 2,
        SAY_REPLACE = 3,
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) 
    {
        if (quest->GetQuestId() == QUEST_FLIGHT_IN_THE_FIRELANDS)
        {
            creature->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
            creature->AI()->DoAction(ACTION_START_ANIM);
        }

        return false; 
    }

    struct npc_farden_talonshrike_40578AI : public ScriptedAI
    {
        npc_farden_talonshrike_40578AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64 m_playerGUID;
        uint32 m_phase;
        bool m_isAnimStarted;

        void InitializeAI()
        {
            m_isAnimStarted = false;
        }

        void Reset() override
        {
            if (!m_isAnimStarted)
            {
                m_events.Reset();
                m_playerGUID = 0;
                m_phase = 0;
            }
        }

        void SetGUID(uint64 guid, int32 id)
        {
            switch (id)
            {
                case PLAYER_GUID:
                    m_playerGUID = guid;
                    break;
                default:
                    break;
            }
        }

        void DoAction(int32 action) override
        {
            switch (action)
            {
            case ACTION_START_ANIM:
                m_phase = 1;
                m_isAnimStarted = true;
                m_events.ScheduleEvent(EVENT_ANIM_TIMER, 100);
                m_events.ScheduleEvent(EVENT_ANIM_TIMEOUT, 120000);
                break;
            default:
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
                case EVENT_ANIM_TIMER:
                    if (m_phase) DoAnim();
                    break;
                case EVENT_ANIM_TIMEOUT:
                    m_isAnimStarted = false;
                    Reset();
                    break;
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void DoAnim()
        {
            switch (m_phase)
            {
            case 1:
                if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    Talk(SAY_GRAB, player);
                m_phase = 2;
                m_events.ScheduleEvent(EVENT_ANIM_TIMER, 500);
                break;
            case 2:
                if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    Talk(SAY_EQUIP, player);
                m_phase = 3;
                m_events.ScheduleEvent(EVENT_ANIM_TIMER, 500);
                break;
            case 3: // wait until item equipped
                if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    if (Item* item = player->GetWeaponForAttack(BASE_ATTACK, true))
                        if (item->GetEntry() == ITEM_TWILIGHT_FIRELANCE)
                        {
                            Talk(SAY_MOUNT, player);
                            m_isAnimStarted = false;
                            Reset();
                            return;
                        }
                m_events.ScheduleEvent(EVENT_ANIM_TIMER, 200);
                break;
            default:
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_farden_talonshrike_40578AI(creature);
    }
};

// 39710 40719 Aviana's Guardian
class vehicle_avianas_guardian_39710 : public VehicleScript
{
public:
    vehicle_avianas_guardian_39710() : VehicleScript("vehicle_avianas_guardian_39710") { }

    void OnAddPassenger(Vehicle* veh, Unit* passenger, int8 seatId) override
    {
        if (Player* player = passenger->ToPlayer())
            if (seatId == 0)
            {
                
            }
    }

    void OnRemovePassenger(Vehicle* veh, Unit* passenger)
    {
        if (Unit* unit = veh->GetBase())
            if (Creature* npc = unit->ToCreature())
                npc->DespawnOrUnsummon();
    }
};


void AddSC_zone_hyjal()
{
    new spell_mount_75935();
    new npc_farden_talonshrike_40578();
    new vehicle_avianas_guardian_39710();

}


