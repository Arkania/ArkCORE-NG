/*
 * Copyright (C) 2011-2017 ArkCORE <http://www.arkania.net/>
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
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "SpellMgr.h"
#include "Transport.h"
#include "Vehicle.h"

enum eKezanEnumerate
{
    QUEST_TAKING_CARE_OF_BUSINESS = 14138,
    QUEST_GOOD_HELP_IS_HARD_TO_FIND = 14069,
    QUEST_TROUBLE_IN_THE_MINES = 14075,
    QUEST_KAJA_COLA = 25473,
    QUEST_ROLLING_WITH_MY_HOMIES = 14071,
    QUEST_LIFE_SAVINGS = 14126,
    QUEST_SASSY_447 = 14125,
    QUEST_MEGS_IN_MARKETING = 28349,
    QUEST_THE_REPLACEMENTS = 24488,
    QUEST_NECCASSARY_ROUGHNESS = 24502,
    QUEST_FOURTH_AND_GOAL = 24503,
    QUEST_REPORT_FOR_TRYOUTS = 24567,
    QUEST_GIVE_SASSY_THE_NEWS = 24520,
    QUEST_LIFE_OF_THE_PARTY_M = 14153,
    QUEST_LIFE_OF_THE_PARTY_F = 14113,
    QUEST_THE_NEW_YOU_M = 14110,
    QUEST_THE_NEW_YOU_F = 14109,
    QUEST_PIRATE_PARTY_CRASHERS = 14115,
    QUEST_ROBBING_HOODS = 14121,
    QUEST_LEARNING_THE_WORD = 14009, 
    ITEMS_STACK_OF_MACAROONS = 47044,
    ITEM_KEY_OF_HOT_ROD = 46856,
    NPC_CANDY_CANE = 35053,
    NPC_CHIP_ENDALE = 35054,
    NPC_HOT_ROD_34840 = 34840,
    NPC_ACE_34957 = 34957,
    NPC_GOBBER_34958 = 34958,
    NPC_IZZY_34959 = 34959,
    NPC_KEZAN_CITIZEN_35063 = 35063,
    NPC_KEZAN_CITIZEN_35075 = 35075,
    NPC_HIRED_LOOTER_35234 = 35234,
    NPC_BRUNO_FLAMERETARDANT = 34835,
    NPC_FRANKIE_GEARSLIPPER = 34876,
    NPC_JACK_THE_HAMMER = 34877,
    NPC_SUDSY_MAGEE = 34878,
    NPC_STEAMWHEEDLE_SHARK = 37114,
    NPC_BILGEWATER_BUCCANEER = 37179,
    NPC_NECESSARY_ROUGHNESS_KILL_CREDIT = 48271,
    NPC_FOURTH_AND_GOAL_TARGET = 37203,
    NPC_KEZAN_PARTYGOER_35175 = 35175,
    NPC_KEZAN_PARTYGOER_35186 = 35186,
    SPELL_BORE_32738 = 32738,
    SPELL_PERMANENT_FEIGN_DEATH = 29266,
    SPELL_INVISIBILITY_DETECTION_1 = 49416,
    SPELL_INVISIBILITY_DETECTION_4 = 90161,
    SPELL_INVISIBILITY_DETECTION_5 = 94566,
    SPELL_INVISIBILITY_DETECTION_6 = 94567,
    SPELL_INVISIBILITY_DETECTION_7 = 94568,
    SPELL_QUEST_INVISIBILITY_5 = 88195,
    SPELL_QUEST_INVISIBILITY_6 = 82358,
    SPELL_QUEST_INVISIBILITY_7 = 85096,
    SPELL_SIGNAL_BACK_TO_SHREDDER = 70062,
    SPELL_INCREASED_MOD_DETECTED_RANGE = 76651,
    SPELL_DEATHWINGS_ATTACK = 66858,
    SPELL_DEATHWING_SOUND_4 = 69988,
    SPELL_OUTFIT_FEMALE = 66927,
    SPELL_OUTFIT_MALE = 66928,
    SPELL_OUTFIT_SECONDARY = 66985,
    SPELL_AWESOME_PARTY_ENSEMBLE = 66908,
    SPELL_LOTP_HAPPY_PARTYGOER = 66916,
    SPELL_TORCH_TOSS = 6257,
    SPELL_HOT_ROD_KNOCKBACK_1 = 66301,
    SPELL_HOT_ROD_KNOCKBACK_2 = 70330,
    SPELL_CREATE_STOLEN_LOOT = 67041,
    SPELL_EARTHQUAKE_CAMERA_SHAKE = 96274,
    SPELL_FLASH_HEAL_2061 = 2061,
    SPELL_SUMMON_HOT_ROD_37676 = 70321,
 
};

void SetCombatAllowed(Creature* npc)
{
    npc->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
}

void SetCombatNotAllowed(Player* player, Creature* npc)
{
    npc->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
    npc->AttackStop();
    npc->ClearInCombat();
    player->AttackStop();
    player->ClearInCombat();
}

// 34689 Mage Trainer, 
class npc_fizz_lighter_34689 : public CreatureScript
{
public:
    npc_fizz_lighter_34689() : CreatureScript("npc_fizz_lighter_34689") { }

    enum eNpc
    {
        SPELL_SHADOW_BOLD = 69607,
        SPELL_FIREBALL = 69608,
        NPC_EVOL_FINGERS = 34696,
    };

    struct npc_fizz_lighter_34689AI : public ScriptedAI
    {
        npc_fizz_lighter_34689AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64 m_targetGuid;

        void Reset() override
        {
            m_events.Reset();
            m_events.ScheduleEvent(EVENT_SPELLCAST, urand(10000, 30000));
            m_targetGuid = 0;
        }

        // Called when hit by a spell
        void SpellHit(Unit* caster, SpellInfo const* /*spell*/) override
        {
            if (urand(0, 100) < 5)
                Talk(1, caster);
            m_events.RescheduleEvent(EVENT_SPELLCAST, 3000);
        }

        // Called when spell hits a target
        void SpellHitTarget(Unit* target, SpellInfo const* spell) override
        {
            if (spell->Id == SPELL_FIREBALL)
                if (urand(0, 100) < 5)
                    Talk(0, target);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_SPELLCAST:
                {
                    if (!m_targetGuid)
                        if (Creature* npc = me->FindNearestCreature(NPC_EVOL_FINGERS, 30.0f))
                            m_targetGuid = npc->GetGUID();

                    if (Creature* evol = ObjectAccessor::GetCreature(*me, m_targetGuid))
                        me->CastSpell(evol, SPELL_FIREBALL, true);

                    m_events.ScheduleEvent(EVENT_SPELLCAST, 30000);

                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_fizz_lighter_34689AI(creature);
    }
};

// 34696 Warlock Trainer
class npc_evol_fingers_34696 : public CreatureScript
{
public:
    npc_evol_fingers_34696() : CreatureScript("npc_evol_fingers_34696") { }

    enum eNpc
    {
        SPELL_SHADOW_BOLD = 69607,
        SPELL_FIREBALL = 69608,
        NPC_FIZZ_LIGHTER = 34689,
    };

    struct npc_evol_fingers_34696AI : public ScriptedAI
    {
        npc_evol_fingers_34696AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64 m_targetGuid;

        void Reset() override
        {
            m_events.Reset();
            m_targetGuid = 0;
            me->CastSpell(me, 11939); // me->SummonCreature(12922, -8396.887f, 1347.801f, 102.5915f, 5.183628f);
        }

        // Called when hit by a spell
        void SpellHit(Unit* caster, SpellInfo const* /*spell*/) override
        {
            if (urand(0, 100) < 5)
                Talk(0, caster);

            m_events.RescheduleEvent(EVENT_SPELLCAST, 3000);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_SPELLCAST:
                {
                    if (!m_targetGuid)
                        if (Creature* npc = me->FindNearestCreature(NPC_FIZZ_LIGHTER, 30.0f))
                            m_targetGuid = npc->GetGUID();

                    if (Creature* fizz = ObjectAccessor::GetCreature(*me, m_targetGuid))
                        me->CastSpell(fizz, SPELL_SHADOW_BOLD, true);

                    m_events.ScheduleEvent(EVENT_SPELLCAST, 30000);

                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_evol_fingers_34696AI(creature);
    }
};

// 37761 
class npc_sally_salvager_sandscrew_37761 : public CreatureScript
{
public:
    npc_sally_salvager_sandscrew_37761() : CreatureScript("npc_sally_salvager_sandscrew_37761") { }


    struct npc_sally_salvager_sandscrew_37761AI : public ScriptedAI
    {
        npc_sally_salvager_sandscrew_37761AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset() override
        {
            m_events.RescheduleEvent(EVENT_RANDOM_EMOTE, urand(5000, 10000));
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_RANDOM_EMOTE:
                    me->HandleEmote(RAND(1, 5, 6, 25, 273, 274));
                    m_events.ScheduleEvent(EVENT_RANDOM_EMOTE, urand(6000, 10000));
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_sally_salvager_sandscrew_37761AI(creature);
    }
};

// 37762  
class npc_brett_coins_mcquid_37762 : public CreatureScript
{
public:
    npc_brett_coins_mcquid_37762() : CreatureScript("npc_brett_coins_mcquid_37762") { }

    struct npc_brett_coins_mcquid_37762AI : public ScriptedAI
    {
        npc_brett_coins_mcquid_37762AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset() override
        {
            m_events.RescheduleEvent(EVENT_RANDOM_EMOTE, urand(5000, 10000));
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_RANDOM_EMOTE:
                    me->HandleEmote(RAND(1, 5, 6, 25, 273, 274));
                    m_events.ScheduleEvent(EVENT_RANDOM_EMOTE, urand(5000, 9000));
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_brett_coins_mcquid_37762AI(creature);
    }
};

// 48305 
class npc_injured_employee_48305 : public CreatureScript
{
public:
    npc_injured_employee_48305() : CreatureScript("npc_injured_employee_48305") { }

    struct npc_injured_employee_48305AI : public ScriptedAI
    {
        npc_injured_employee_48305AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        // Called when hit by a spell
        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (Player* player = caster->ToPlayer())
                if (player->GetQuestStatus(QUEST_LEARNING_THE_WORD) == QUEST_STATUS_INCOMPLETE)
                    if (spell->Id == SPELL_FLASH_HEAL_2061)
                    {
                        player->KilledMonsterCredit(44175);
                        me->DespawnOrUnsummon(500);
                    }
        }
};

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_injured_employee_48305AI(creature);
    }
};

// 37804
class npc_kaja_cola_balloon_37804 : public CreatureScript
{
public:
    npc_kaja_cola_balloon_37804() : CreatureScript("npc_kaja_cola_balloon_37804") { }

    struct npc_kaja_cola_balloon_37804AI : public ScriptedAI
    {
        npc_kaja_cola_balloon_37804AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset() override
        {
            m_events.ScheduleEvent(EVENT_BALLON_MESSAGE, 10000);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_BALLON_MESSAGE:
                {
                    Talk(0);
                    m_events.ScheduleEvent(EVENT_BALLON_MESSAGE, urand(30000, 45000));
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
        return new npc_kaja_cola_balloon_37804AI(creature);
    }
};

// 34668
class npc_sassy_hardwrench_34668 : public CreatureScript
{
public:
    npc_sassy_hardwrench_34668() : CreatureScript("npc_sassy_hardwrench_34668") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case QUEST_TAKING_CARE_OF_BUSINESS:
            creature->AI()->Talk(0, player);
            break;
        case QUEST_ROLLING_WITH_MY_HOMIES:
            creature->AI()->Talk(1, player);
            break;
        case QUEST_LIFE_SAVINGS:
            creature->AI()->Talk(2, player);
            creature->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
            creature->AI()->DoAction(992);
            break;
        case QUEST_PIRATE_PARTY_CRASHERS:
            player->CastSpell(player, SPELL_EARTHQUAKE_CAMERA_SHAKE, true);
            break;
        }

        return false;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        switch (quest->GetQuestId())
        {
        case QUEST_TAKING_CARE_OF_BUSINESS:
            creature->AI()->Talk(3, player);
            break;
        case QUEST_GIVE_SASSY_THE_NEWS:
            player->RemoveAura(SPELL_INVISIBILITY_DETECTION_4);
            break;
        case QUEST_LIFE_OF_THE_PARTY_M:
            player->RemoveAura(SPELL_OUTFIT_MALE);
            player->RemoveAura(SPELL_AWESOME_PARTY_ENSEMBLE);
            player->RemoveAura(SPELL_LOTP_HAPPY_PARTYGOER);
            player->RemoveAura(SPELL_OUTFIT_SECONDARY);
            break;
        case QUEST_LIFE_OF_THE_PARTY_F:
            player->RemoveAura(SPELL_OUTFIT_FEMALE);
            player->RemoveAura(SPELL_AWESOME_PARTY_ENSEMBLE);
            player->RemoveAura(SPELL_LOTP_HAPPY_PARTYGOER);
            player->RemoveAura(SPELL_OUTFIT_SECONDARY);
            break;        
        }
        return false;
    }

    struct npc_sassy_hardwrench_34668AI : public ScriptedAI
    {
        npc_sassy_hardwrench_34668AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_playerGUID;

        void Initialize()
        {
            m_playerGUID=0;
        }

        void Reset() override
        {
        }

        void DoAction(int32 param) override
        {
            if (param == 992)
            {
                m_events.ScheduleEvent (EVENT_START_RESCUE_LIVE, 100);
            }
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case PLAYER_GUID:
            {
                m_playerGUID = guid;
                break;
            }
            }
        }
        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_RESCUE_LIVE:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        player->DestroyItemCount(ITEM_KEY_OF_HOT_ROD, 1, true);
                        player->CastSpell(player, SPELL_SUMMON_HOT_ROD_37676, true);  // Summon the Hot Rod 37676, trigger spell 66724 Sassy fährt
                    }
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
        return new npc_sassy_hardwrench_34668AI(creature);
    }
};

// 34872
class npc_foreman_dampwick_34872 : public CreatureScript
{
public:
    npc_foreman_dampwick_34872() : CreatureScript("npc_foreman_dampwick_34872") { }

    enum eNPC
    {
        SPELL_SASSYS_INCENTIVE = 82025,
    };

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        if (quest->GetQuestId() == QUEST_TAKING_CARE_OF_BUSINESS)
            creature->GetAI()->DoAction(ACTION_DELIVER_PACKET);

        if (player->GetQuestStatus(QUEST_GOOD_HELP_IS_HARD_TO_FIND) == QUEST_STATUS_REWARDED && player->GetQuestStatus(QUEST_TROUBLE_IN_THE_MINES) == QUEST_STATUS_REWARDED)
            creature->AI()->Talk(5, player);

        return false;
    }

    struct npc_foreman_dampwick_34872AI : public ScriptedAI
    {
        npc_foreman_dampwick_34872AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        bool     m_anim_is_started;

        void Reset() override
        {
            m_events.Reset();
            m_anim_is_started = false;
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        }

        void DoAction(int32 param) override
        {
            if (!m_anim_is_started)
                if (param == ACTION_DELIVER_PACKET)
                {
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                    m_events.ScheduleEvent(EVENT_START_ANIMATION_PACKET, 500);
                    m_events.ScheduleEvent(EVENT_MASTER_RESET, 30000);
                }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_MASTER_RESET:
                {
                    Reset();
                    break;
                }
                case EVENT_START_ANIMATION_PACKET:
                {
                    Talk(0);
                    m_events.ScheduleEvent(EVENT_PACKET_EXPLODE, 4000);
                    break;
                }
                case EVENT_PACKET_EXPLODE:
                {
                    Position p = me->GetPosition();
                    me->CastSpell(p.m_positionX, p.m_positionY, p.m_positionZ, SPELL_SASSYS_INCENTIVE, true);
                    m_events.ScheduleEvent(EVENT_SAY_OUTCH, 1000);
                    break;
                }
                case EVENT_SAY_OUTCH:
                {
                    Talk(1);
                    m_events.ScheduleEvent(EVENT_SAY_HAVE_UNDERSTAND, 5000);
                    break;
                }
                case EVENT_SAY_HAVE_UNDERSTAND:
                {
                    Talk(2);
                    m_events.RescheduleEvent(EVENT_COOLDOWN_00, 3000);
                    break;
                }
                case EVENT_COOLDOWN_00:
                {
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                    m_events.RescheduleEvent(EVENT_MASTER_RESET, 2000);
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
        return new npc_foreman_dampwick_34872AI(creature);
    }
};

// 34692
class npc_sister_goldskimmer_34692 : public CreatureScript
{
public:
    npc_sister_goldskimmer_34692() : CreatureScript("npc_sister_goldskimmer_34692") { }

    enum eNPC
    {
        SPELL_POWER_WORD_FORTITUDE = 74973,
    };

    struct npc_sister_goldskimmer_34692AI : public ScriptedAI
    {
        npc_sister_goldskimmer_34692AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        bool     m_talk_cd_active;

        void Reset() override
        {
            m_talk_cd_active = false;
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (Player* player = who->ToPlayer())
                if (!player->HasAura(SPELL_POWER_WORD_FORTITUDE))
                {
                    me->AddAura(SPELL_POWER_WORD_FORTITUDE, player);
                    if (!m_talk_cd_active)
                    {
                        Talk(0, who);
                        m_talk_cd_active = true;
                        m_events.ScheduleEvent(EVENT_TALK_COOLDOWN, 6000);
                    }
                }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_TALK_COOLDOWN:
                {
                    m_talk_cd_active = false;
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
        return new npc_sister_goldskimmer_34692AI(creature);
    }
};

// 34673
class npc_bamm_megabomb_34673 : public CreatureScript
{
public:
    npc_bamm_megabomb_34673() : CreatureScript("npc_bamm_megabomb_34673") { }

    enum eNPC
    {
        NPC_TRAININGS_DUMMY = 48304,
        SPELL_SHOOT_GUN = 69509,
    };

    struct npc_bamm_megabomb_34673AI : public ScriptedAI
    {
        npc_bamm_megabomb_34673AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_dummy;

        void Reset() override
        {
            m_events.Reset();
            m_events.ScheduleEvent(EVENT_SHOOT_ON_DUMMY, 5000);
            m_dummy = 0;
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_SHOOT_ON_DUMMY:
                {
                    if (Creature* dummy = me->FindRandomCreatureInRange(NPC_TRAININGS_DUMMY, 15.0f, true))
                    {
                        m_dummy = dummy->GetGUID();
                        me->SetFacingToObject(dummy);
                    }
                    m_events.ScheduleEvent(EVENT_SHOOT_ON_DUMMY + 1, 1000);
                    break;
                }
                case EVENT_SHOOT_ON_DUMMY + 1:
                {
                    if (Creature* dummy = sObjectAccessor->GetCreature(*me, m_dummy))
                        me->CastSpell(dummy, SPELL_SHOOT_GUN);
                    m_events.ScheduleEvent(EVENT_SHOOT_ON_DUMMY, urand(7000, 10000));
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
        return new npc_bamm_megabomb_34673AI(creature);
    }
};

// 34874
class npc_megs_dreadshredder_34874 : public CreatureScript
{
public:
    npc_megs_dreadshredder_34874() : CreatureScript("npc_megs_dreadshredder_34874") { }

    enum eNPC
    {
        BROADCASTTEXT_USE_KEY_FOR_HOT_RED = 48504,
    };

    bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 sender, uint32 action) 
    { 
        uint32 amount = player->GetItemCount(ITEM_KEY_OF_HOT_ROD);
        if (player->GetQuestStatus(QUEST_ROLLING_WITH_MY_HOMIES) == QUEST_STATUS_REWARDED)
            if (!amount)
                player->AddItem(ITEM_KEY_OF_HOT_ROD, 1);
        return false; 
    }

    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case QUEST_ROLLING_WITH_MY_HOMIES:
        {
            player->ToUnit()->Talk(BROADCASTTEXT_USE_KEY_FOR_HOT_RED, CHAT_MSG_RAID_BOSS_WHISPER, 25.0f, player);
            player->AddAura(SPELL_INVISIBILITY_DETECTION_4, player);
            break;
        }
        case QUEST_REPORT_FOR_TRYOUTS:
        {
            player->AddAura(SPELL_INVISIBILITY_DETECTION_4, player);
            break;
        }
        }
        return false;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        switch (quest->GetQuestId())
        {
        case QUEST_MEGS_IN_MARKETING:
            creature->AI()->Talk(0, player);
            break;
        case QUEST_ROLLING_WITH_MY_HOMIES:
            player->AddAura(SPELL_INVISIBILITY_DETECTION_4, player);
        }
        return false;
    }
};

// 35053
class npc_candy_cane_35053 : public CreatureScript
{
public:
    npc_candy_cane_35053() : CreatureScript("npc_candy_cane_35053") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case QUEST_LIFE_OF_THE_PARTY_F:
            player->RemoveAura(SPELL_AWESOME_PARTY_ENSEMBLE);
            player->CastSpell(player, SPELL_OUTFIT_FEMALE);
            player->CastSpell(player, SPELL_AWESOME_PARTY_ENSEMBLE);
            player->ToUnit()->Talk(35444, CHAT_MSG_RAID_BOSS_EMOTE, 25.0f, player);
            creature->AI()->Talk(1, player);
            break;
        }
        return false;
    }
};

// 35054
class npc_chip_endale_35054 : public CreatureScript
{
public:
    npc_chip_endale_35054() : CreatureScript("npc_chip_endale_35054") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case QUEST_LIFE_OF_THE_PARTY_M:
            player->RemoveAura(SPELL_AWESOME_PARTY_ENSEMBLE);
            player->CastSpell(player, SPELL_OUTFIT_MALE);
            player->CastSpell(player, SPELL_AWESOME_PARTY_ENSEMBLE);
            player->ToUnit()->Talk(35444, CHAT_MSG_RAID_BOSS_EMOTE, 25.0f, player);
            creature->AI()->Talk(1, player);
            break;
        }
        return false;
    }
};

// 48494
class npc_hobart_grapplehammer_48494 : public CreatureScript
{
public:
    npc_hobart_grapplehammer_48494() : CreatureScript("npc_hobart_grapplehammer_48494") { }

    struct npc_hobart_grapplehammer_48494AI : public ScriptedAI
    {
        npc_hobart_grapplehammer_48494AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

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
               /* switch (eventId)
                {
                }*/
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_hobart_grapplehammer_48494AI(creature);
    }
};

// 49150
class npc_subject_nine_49150 : public CreatureScript
{
public:
    npc_subject_nine_49150() : CreatureScript("npc_subject_nine_49150") { }

    struct npc_subject_nine_49150AI : public ScriptedAI
    {
        npc_subject_nine_49150AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset() override
        {
            m_events.ScheduleEvent(EVENT_ANIMATION_SUBJECT, 10000);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_ANIMATION_SUBJECT:
                {
                    me->SendPlaySound(18178, false);
                    me->HandleEmoteCommand(RAND(33, 35, 377));
                    m_events.ScheduleEvent(EVENT_ANIMATION_SUBJECT, urand(15000, 18000));
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
        return new npc_subject_nine_49150AI(creature);
    }
};

// 70478
class spell_kaja_cola_70478 : public SpellScriptLoader
{
public:
    spell_kaja_cola_70478() : SpellScriptLoader("spell_kaja_cola_70478") { }

    class spell_kaja_cola_70478_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_kaja_cola_70478_AuraScript);

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* owner = GetOwner()->ToUnit())
                if (Unit* target = GetTarget())
                    target->Talk(urand(37326, 37365), CHAT_MSG_MONSTER_SAY, 15.0f, target);
        }

        void Register() override
        {
            OnEffectApply += AuraEffectApplyFn(spell_kaja_cola_70478_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_kaja_cola_70478_AuraScript();
    }
};

// 35304
class npc_brute_enforcer_35304 : public CreatureScript
{
public:
    npc_brute_enforcer_35304() : CreatureScript("npc_brute_enforcer_35304") { }

    struct npc_brute_enforcer_35304AI : public ScriptedAI
    {
        npc_brute_enforcer_35304AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        bool     m_talk_cd_active;

        void Reset() override
        {
            m_talk_cd_active = false;
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (!m_talk_cd_active)
                if (Player* player = who->ToPlayer())
                    if (player->GetQuestStatus(QUEST_ROLLING_WITH_MY_HOMIES) != QUEST_STATUS_REWARDED)
                        if (urand(0, 100) < 25)
                        {
                            Talk(0, who);
                            m_talk_cd_active = true;
                            m_events.ScheduleEvent(EVENT_TALK_COOLDOWN, urand(10000, 15000));
                        }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_TALK_COOLDOWN:
                {
                    m_talk_cd_active = false;
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
        return new npc_brute_enforcer_35304AI(creature);
    }
};

// 5497
class at_kezan_ace_5497 : public AreaTriggerScript
{
public:
    at_kezan_ace_5497() : AreaTriggerScript("at_kezan_ace_5497") { }

    enum npc
    {
        SPELL_SUMMON_ACE = 66597,
    };

    bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
    {
        if (player->GetQuestStatus(QUEST_ROLLING_WITH_MY_HOMIES) == QUEST_STATUS_INCOMPLETE)
            if (player->GetReqKillOrCastCurrentCount(QUEST_ROLLING_WITH_MY_HOMIES, NPC_ACE_34957) == 0)
            {
                player->CastSpell(player, SPELL_SUMMON_ACE, true);
                player->KilledMonsterCredit(NPC_ACE_34957);
            }

        return true;
    }
};

// 5498
class at_kezan_gobber_5498 : public AreaTriggerScript
{
public:
    at_kezan_gobber_5498() : AreaTriggerScript("at_kezan_gobber_5498") { }

    enum npc
    {
        SPELL_SUMMON_GOBBER = 66599,
    };

    bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
    {
        if (player->GetQuestStatus(QUEST_ROLLING_WITH_MY_HOMIES) == QUEST_STATUS_INCOMPLETE)
            if (player->GetReqKillOrCastCurrentCount(QUEST_ROLLING_WITH_MY_HOMIES, NPC_GOBBER_34958) == 0)
            {
                player->CastSpell(player, SPELL_SUMMON_GOBBER, true);
                player->KilledMonsterCredit(NPC_GOBBER_34958);
            }

        return true;
    }
};

// 5499
class at_kezan_izzy_5499 : public AreaTriggerScript
{
public:
    at_kezan_izzy_5499() : AreaTriggerScript("at_kezan_izzy_5499") { }
    enum npc
    {
        SPELL_SUMMON_IZZY = 66600,
    };

    bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
    {
        if (player->GetQuestStatus(QUEST_ROLLING_WITH_MY_HOMIES) == QUEST_STATUS_INCOMPLETE)
            if (player->GetReqKillOrCastCurrentCount(QUEST_ROLLING_WITH_MY_HOMIES, NPC_IZZY_34959) == 0)
            {
                player->CastSpell(player, SPELL_SUMMON_IZZY, true);
                player->KilledMonsterCredit(NPC_IZZY_34959);
            }
            
        return true;
    }
};

// 34840
class npc_hot_rod_34840 : public CreatureScript
{
public:
    npc_hot_rod_34840() : CreatureScript("npc_hot_rod_34840") { }

    enum eNPC
    {
        SPELL_RESUMMON_IZZY = 66646,
        SPELL_RESUMMON_GOBBER = 66645,
        SPELL_RESUMMON_ACE = 66644,
        EVENT_IZZY_ENTER_THE_CAR = 901,
        EVENT_GOBBER_ENTER_THE_CAR,
        EVENT_ACE_ENTER_THE_CAR,
        EVENT_GOBBER_EMOTE,
        EVENT_IZZY_EMOTE,
        EVENT_ACE_EMOTE,
    };

    class IfNotInRange
    {
    public:
        explicit IfNotInRange(Unit* _caster) : caster(_caster) { }

        bool operator() (WorldObject* unit)
        {
            Position pos = caster->GetPosition();
            if (unit->GetPosition().GetExactDist(&pos) > 10.0f)
                return true;
            if (unit->GetEntry() != NPC_KEZAN_CITIZEN_35063 && unit->GetEntry() != NPC_KEZAN_CITIZEN_35075 && unit->GetEntry() != NPC_HIRED_LOOTER_35234)
                return true;
            if (Creature* npc = unit->ToCreature())
                if (!npc->IsAlive())
                    return true; 
            if (unit->GetPosition().GetExactDist(&pos) < 3.0f)
                return false;
            if (caster->isInFront(unit))
                return false;

            return true;
        }
        Unit* caster;
    };

    struct npc_hot_rod_34840AI : public VehicleAI
    {
        npc_hot_rod_34840AI(Creature* creature) : VehicleAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_izzyGUID;
        uint64   m_gobberGUID;
        uint64   m_aceGUID;

        void Reset() override
        {
            m_playerGUID = 0;
            m_izzyGUID = 0;
            m_gobberGUID = 0;
            m_aceGUID = 0;
            m_events.RescheduleEvent (EVENT_CHECK_FOR_CREATURE, 1000);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                for (std::set<Unit*>::iterator itr = player->m_Controlled.begin(); itr != player->m_Controlled.end(); ++itr)
                    if ((*itr)->GetEntry() == NPC_IZZY_34959)
                        m_izzyGUID = (*itr)->GetGUID();
                    else if ((*itr)->GetEntry() == NPC_GOBBER_34958)
                        m_gobberGUID = (*itr)->GetGUID();
                    else if ((*itr)->GetEntry() == NPC_ACE_34957)
                        m_aceGUID = (*itr)->GetGUID();

                if (player->GetQuestStatus(QUEST_ROLLING_WITH_MY_HOMIES) == QUEST_STATUS_INCOMPLETE)
                {
                    if (!m_izzyGUID)
                        if (player->GetReqKillOrCastCurrentCount(QUEST_ROLLING_WITH_MY_HOMIES, NPC_IZZY_34959) > 0)
                            player->CastSpell(player, SPELL_RESUMMON_IZZY);
                    if (!m_gobberGUID)
                        if (player->GetReqKillOrCastCurrentCount(QUEST_ROLLING_WITH_MY_HOMIES, NPC_GOBBER_34958) > 0)
                            player->CastSpell(player, SPELL_RESUMMON_GOBBER);
                    if (!m_aceGUID)
                        if (player->GetReqKillOrCastCurrentCount(QUEST_ROLLING_WITH_MY_HOMIES, NPC_ACE_34957) > 0)
                            player->CastSpell(player, SPELL_RESUMMON_ACE);
                    if (m_izzyGUID)
                        if (player->GetReqKillOrCastCurrentCount(QUEST_ROLLING_WITH_MY_HOMIES, NPC_IZZY_34959) == 0)
                            player->KilledMonsterCredit(NPC_IZZY_34959);
                    if (m_gobberGUID)
                        if (player->GetReqKillOrCastCurrentCount(QUEST_ROLLING_WITH_MY_HOMIES, NPC_GOBBER_34958) == 0)
                            player->KilledMonsterCredit(NPC_GOBBER_34958);
                    if (m_aceGUID)
                        if (player->GetReqKillOrCastCurrentCount(QUEST_ROLLING_WITH_MY_HOMIES, NPC_ACE_34957) == 0)
                            player->KilledMonsterCredit(NPC_ACE_34957);
                }
                else if (player->GetQuestStatus(QUEST_ROLLING_WITH_MY_HOMIES) == QUEST_STATUS_COMPLETE || player->GetQuestStatus(QUEST_ROLLING_WITH_MY_HOMIES) == QUEST_STATUS_REWARDED)
                {
                    if (!m_izzyGUID)
                        player->CastSpell(player, SPELL_RESUMMON_IZZY);
                    if (!m_gobberGUID)
                        player->CastSpell(player, SPELL_RESUMMON_GOBBER);
                    if (!m_aceGUID)
                        player->CastSpell(player, SPELL_RESUMMON_ACE);
                }

                if (Vehicle* car = me->GetVehicleKit())
                    for (std::set<Unit*>::iterator itr = player->m_Controlled.begin(); itr != player->m_Controlled.end(); ++itr)
                        if ((*itr)->GetEntry() == NPC_IZZY_34959)
                            m_events.ScheduleEvent(EVENT_IZZY_ENTER_THE_CAR, 500);
                        else if ((*itr)->GetEntry() == NPC_GOBBER_34958)
                            m_events.ScheduleEvent(EVENT_GOBBER_ENTER_THE_CAR, 500);
                        else if ((*itr)->GetEntry() == NPC_ACE_34957)
                            m_events.ScheduleEvent(EVENT_ACE_ENTER_THE_CAR, 500);
            }
        }

        void PassengerBoarded(Unit* unit, int8 /*seat*/, bool apply) override
        {
            if (apply)
            {
                if (Player* player = unit->ToPlayer())
                {
                    if (!m_playerGUID)
                        m_playerGUID = player->GetGUID();
                }
                else if (Creature* npc = unit->ToCreature())
                {
                    unit->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                    npc->SetReactState(REACT_PASSIVE);
                    if (!m_izzyGUID)
                        if (npc->GetEntry() == NPC_IZZY_34959)
                        {
                            m_izzyGUID = npc->GetGUID();
                            m_events.RescheduleEvent(EVENT_IZZY_EMOTE, urand(2000, 10000));
                        }
                    if (!m_gobberGUID)
                        if (npc->GetEntry() == NPC_GOBBER_34958)
                        {
                            m_gobberGUID = npc->GetGUID();
                            m_events.RescheduleEvent(EVENT_GOBBER_EMOTE, urand(2000, 10000));
                        }
                    if (!m_aceGUID)
                        if (npc->GetEntry() == NPC_ACE_34957)
                        {
                            m_aceGUID = npc->GetGUID();
                            m_events.RescheduleEvent(EVENT_ACE_EMOTE, urand(2000, 10000));
                        }
                }
            }
            else
            {
                if (Creature* npc = unit->ToCreature())
                {
                    npc->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                    npc->SetReactState(REACT_DEFENSIVE);
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        npc->GetMotionMaster()->MoveChase(player, frand(3.0f, 5.0f), frand(2.0f, 4.2f));
                }
            }
        }

       // void EnterCombat(Unit* /*who*/) override  {  }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);
            VehicleAI::UpdateAI(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_IZZY_ENTER_THE_CAR:
                {
                    if (!m_izzyGUID)
                        if (Creature* npc = me->FindNearestCreature(NPC_IZZY_34959, 15.0f))
                            m_izzyGUID = npc->GetGUID();
                    if (Creature* npc = ObjectAccessor::GetCreature(*me, m_izzyGUID))
                    {
                        npc->AI()->SetGUID(m_playerGUID, PLAYER_GUID);
                        npc->AI()->SetGUID(me->GetGUID(), me->GetEntry());
                        npc->AI()->DoAction(ACTION_ENTER_CAR);
                    }
                    break;
                }
                case EVENT_GOBBER_ENTER_THE_CAR:
                {
                    if (!m_gobberGUID)
                        if (Creature* npc = me->FindNearestCreature(NPC_GOBBER_34958, 15.0f))
                            m_gobberGUID = npc->GetGUID();
                    if (Creature* npc = ObjectAccessor::GetCreature(*me, m_gobberGUID))
                    {
                        npc->AI()->SetGUID(m_playerGUID, PLAYER_GUID);
                        npc->AI()->SetGUID(me->GetGUID(), me->GetEntry());
                        npc->AI()->DoAction(ACTION_ENTER_CAR);
                    }
                    break;
                }
                case EVENT_ACE_ENTER_THE_CAR:
                {
                    if (!m_aceGUID)
                        if (Creature* npc = me->FindNearestCreature(NPC_ACE_34957, 15.0f))
                            m_aceGUID = npc->GetGUID();
                    if (Creature* npc = ObjectAccessor::GetCreature(*me, m_aceGUID))
                    {
                        npc->AI()->SetGUID(m_playerGUID, PLAYER_GUID);
                        npc->AI()->SetGUID(me->GetGUID(), me->GetEntry());
                        npc->AI()->DoAction(ACTION_ENTER_CAR);
                    }
                    break;
                }
                case EVENT_IZZY_EMOTE:
                {
                    if (Creature* npc = ObjectAccessor::GetCreature(*me, m_izzyGUID))
                        npc->HandleEmote(RAND(1, 5, 6, 11, 25, 273, 274));
                    m_events.ScheduleEvent(EVENT_IZZY_EMOTE, urand(6000, 11000));
                    break;
                }
                case EVENT_GOBBER_EMOTE:
                {
                    if (Creature* npc = ObjectAccessor::GetCreature(*me, m_gobberGUID))
                        npc->HandleEmote(RAND(1, 3, 11, 15, 20, 94, 440, 463));
                    m_events.ScheduleEvent(EVENT_GOBBER_EMOTE, urand(8000, 13000));
                    break;
                }
                case EVENT_ACE_EMOTE:
                {
                    if (Creature* npc = ObjectAccessor::GetCreature(*me, m_aceGUID))
                        npc->HandleEmote(RAND(1, 5, 6, 11, 25, 273, 274));
                    m_events.ScheduleEvent(EVENT_ACE_EMOTE, urand(7000, 12000));
                    break;
                }
                case EVENT_CHECK_FOR_CREATURE:
                {
                    std::list<Creature*> cList = me->FindAllCreaturesInRange(10.0f);
                    cList.remove_if(IfNotInRange(me));
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        for (auto npc : cList)
                            player->CastSpell(npc, SPELL_HOT_ROD_KNOCKBACK_1);

                    m_events.ScheduleEvent(EVENT_CHECK_FOR_CREATURE, 250);
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
        return new npc_hot_rod_34840AI(creature);
    }
};

// 34959
class npc_izzy_34959 : public CreatureScript
{
public:
    npc_izzy_34959() : CreatureScript("npc_izzy_34959") { }

    struct npc_izzy_34959AI : public ScriptedAI
    {
        npc_izzy_34959AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_hotrodGUID;
        uint64   m_targetGUID;

        void Initialize()
        {
            m_playerGUID = 0;
            m_hotrodGUID = 0;
            m_targetGUID = 0;
            me->SetOrientation(6.265732f);
        }

        void Reset() override
        {

        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                if (Creature* car = player->GetVehicleCreatureBase())
                    if (car->GetEntry() == NPC_HOT_ROD_34840)
                    {
                        m_hotrodGUID = car->GetGUID();
                        m_events.ScheduleEvent(EVENT_ENTER_CAR, 500);
                    }
            }
        }

        void EnterCombat(Unit* victim) override
        {
            if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                if (urand(0, 100) < 60)
                    Talk(0, player);
            m_targetGUID = victim->GetGUID();
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case PLAYER_GUID:
            {
                m_playerGUID = guid;
                break;
            }
            case NPC_HOT_ROD_34840:
            {
                m_hotrodGUID = guid;
                break;
            }
            case NPC_BRUNO_FLAMERETARDANT:
            case NPC_FRANKIE_GEARSLIPPER:
            case NPC_JACK_THE_HAMMER:
            case NPC_SUDSY_MAGEE:
            {
                m_targetGUID = guid;
                break;
            }
            }
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case ACTION_ENTER_CAR:
                m_events.ScheduleEvent(EVENT_ENTER_CAR, 500);
                break;
            }
        }

        void EnterEvadeMode() override
        {
            if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                me->GetMotionMaster()->MoveChase(player, frand(3.0f, 5.0f), frand(2.0f, 4.2f));
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_ENTER_CAR:
                {
                    if (Creature* car = ObjectAccessor::GetCreature(*me, m_hotrodGUID))
                        if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                            if (Vehicle* hotrod = car->GetVehicleKit())
                                if (!hotrod->HasEmptySeat(0))    // player is passenger
                                    if (hotrod->HasEmptySeat(3)) // my seat is free
                                        me->EnterVehicle(car, 3); //hotrod->AddPassenger(me, 3);
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
        return new npc_izzy_34959AI(creature);
    }
};

// 34958
class npc_gobber_34958 : public CreatureScript
{
public:
    npc_gobber_34958() : CreatureScript("npc_gobber_34958") { }

    struct npc_gobber_34958AI : public ScriptedAI
    {
        npc_gobber_34958AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_hotrodGUID;
        uint64   m_targetGUID;

        void Initialize()
        {
            m_playerGUID = 0;
            m_hotrodGUID = 0;
            m_targetGUID = 0;
            me->SetOrientation(4.120008f);
        }

        void Reset() override
        {

        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                if (Creature* car = player->GetVehicleCreatureBase())
                    if (car->GetEntry() == NPC_HOT_ROD_34840)
                    {
                        m_hotrodGUID = car->GetGUID();
                        m_events.ScheduleEvent(EVENT_ENTER_CAR, 500);
                    }
            }
        }

        void EnterCombat(Unit* victim) override
        {
            m_targetGUID = victim->GetGUID();
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case PLAYER_GUID:
            {
                m_playerGUID = guid;
                break;
            }
            case NPC_HOT_ROD_34840:
            {
                m_hotrodGUID = guid;
                break;
            }
            case NPC_BRUNO_FLAMERETARDANT:
            case NPC_FRANKIE_GEARSLIPPER:
            case NPC_JACK_THE_HAMMER:
            case NPC_SUDSY_MAGEE:
            {
                m_targetGUID = guid;
                break;
            }
            }
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case ACTION_ENTER_CAR:
                m_events.ScheduleEvent(EVENT_ENTER_CAR, 500);
                break;
            }
        }

        void EnterEvadeMode() override
        {
            if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                me->GetMotionMaster()->MoveChase(player, frand(3.0f, 5.0f), frand(2.0f, 4.2f));
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_ENTER_CAR:
                {
                    if (Creature* car = ObjectAccessor::GetCreature(*me, m_hotrodGUID))
                        if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                            if (Vehicle* hotrod = car->GetVehicleKit())
                                if (!hotrod->HasEmptySeat(0))    // player is passenger
                                    if (hotrod->HasEmptySeat(2)) // my seat is free
                                       me->EnterVehicle(car, 2); //  hotrod->AddPassenger(me, 2);
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
        return new npc_gobber_34958AI(creature);
    }
};

// 34957
class npc_ace_34957 : public CreatureScript
{
public:
    npc_ace_34957() : CreatureScript("npc_ace_34957") { }

    struct npc_ace_34957AI : public ScriptedAI
    {
        npc_ace_34957AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_hotrodGUID;
        uint64   m_targetGUID;

        void Initialize()
        {
            m_playerGUID = 0;
            m_hotrodGUID = 0;
            m_targetGUID = 0;
            me->SetOrientation(3.819579f);
        }

        void Reset() override
        {

        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                if (Creature* car = player->GetVehicleCreatureBase())
                    if (car->GetEntry() == NPC_HOT_ROD_34840)
                    {
                        m_hotrodGUID = car->GetGUID();
                        m_events.ScheduleEvent(EVENT_ENTER_CAR, 500);
                    }
            }
        }

        void EnterCombat(Unit* victim) override
        {
            if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                if (urand(0, 100) < 60)
                    Talk(0, player);
            m_targetGUID = victim->GetGUID();
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case PLAYER_GUID:
            {
                m_playerGUID = guid;
                break;
            }
            case NPC_HOT_ROD_34840:
            {
                m_hotrodGUID = guid;
                break;
            }
            case NPC_BRUNO_FLAMERETARDANT:
            case NPC_FRANKIE_GEARSLIPPER:
            case NPC_JACK_THE_HAMMER:
            case NPC_SUDSY_MAGEE:
            {
                m_targetGUID = guid;
                break;
            }
            }
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case ACTION_ENTER_CAR:
                m_events.ScheduleEvent(EVENT_ENTER_CAR, 500);
                break;
            }
        }

        void EnterEvadeMode() override 
        { 
            if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                me->GetMotionMaster()->MoveChase(player, frand(3.0f, 5.0f), frand(2.0f, 4.2f));
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_ENTER_CAR:
                {
                    if (Creature* car = ObjectAccessor::GetCreature(*me, m_hotrodGUID))
                        if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                            if (Vehicle* hotrod = car->GetVehicleKit())
                                if (!hotrod->HasEmptySeat(0))    // player is passenger
                                    if (hotrod->HasEmptySeat(1)) // my seat is free
                                        me->EnterVehicle(car, 1); //hotrod->AddPassenger(me, 1);
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
        return new npc_ace_34957AI(creature);
    }
};

// 35120
class npc_fbok_bank_teller_35120 : public CreatureScript
{
public:
    npc_fbok_bank_teller_35120() : CreatureScript("npc_fbok_bank_teller_35120") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case QUEST_THE_NEW_YOU_M:
        case QUEST_THE_NEW_YOU_F:
        {
            uint32 amount = 10 - player->GetItemCount(ITEMS_STACK_OF_MACAROONS);
            if (amount > 0)
                player->AddItem(ITEMS_STACK_OF_MACAROONS, amount);
            break;
        }
        }
        return false;
    }
};

// 201591
class go_disco_ball_201591 : public GameObjectScript
{
public:
    go_disco_ball_201591() : GameObjectScript("go_disco_ball_201591") { }

    struct go_disco_ball_201591AI : public GameObjectAI
    {
        go_disco_ball_201591AI(GameObject* go) : GameObjectAI(go) { }

        EventMap m_events;

        void Reset() override
        {
           m_events.RescheduleEvent(EVENT_TALK_PERIODIC, 3000);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);
            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_TALK_PERIODIC:
                {
                    go->PlayDirectSound(12924);
                    m_events.ScheduleEvent(EVENT_TALK_PERIODIC, urand(2600,5200));
                    break;
                }
                }
            }
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_disco_ball_201591AI(go);
    }
};

// 34865
class npc_tunneling_worm_34865 : public CreatureScript
{
public:
    npc_tunneling_worm_34865() : CreatureScript("npc_tunneling_worm_34865") { }

    struct npc_tunneling_worm_34865AI : public ScriptedAI
    {
        npc_tunneling_worm_34865AI(Creature* creature) : ScriptedAI(creature) { }

        void EnterCombat(Unit* victim) override
        {
            me->CastSpell(victim, SPELL_BORE_32738);
            me->PlayDirectSound(5038);
            me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK_UNARMED);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_tunneling_worm_34865AI(creature);
    }
};

// 34697
class npc_warrior_matic_nx__34697 : public CreatureScript
{
public:
    npc_warrior_matic_nx__34697() : CreatureScript("npc_warrior_matic_nx__34697") { }

    struct npc_warrior_matic_nx__34697AI : public ScriptedAI
    {
        npc_warrior_matic_nx__34697AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset() override
        {
            m_events.RescheduleEvent(EVENT_TALK_PERIODIC, 3000);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_TALK_PERIODIC:
                {
                    me->PlayDirectSound(2304);
                    m_events.ScheduleEvent(EVENT_TALK_PERIODIC, urand(25000, 35000));
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
        return new npc_warrior_matic_nx__34697AI(creature);
    }
};

// 34835
class npc_bruno_flameretardant_34835 : public CreatureScript
{
public:
    npc_bruno_flameretardant_34835() : CreatureScript("npc_bruno_flameretardant_34835") { }

    enum eNpc
    {
        SPELL_THROW_GEARS = 75775,
    };

    struct npc_bruno_flameretardant_34835AI : public ScriptedAI
    {
        npc_bruno_flameretardant_34835AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_playerGUID;
        bool     m_give_up;

        void Initialize() 
        {
            m_playerGUID = 0;
            m_give_up = false;
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
        }

        void JustDied(Unit* killer) override
        {
            Initialize();
        }

        void DamageTaken(Unit* attacker, uint32& damage) override 
        { 
            if (!m_give_up)
            {
                if (me->GetHealthPct() < 50.0f)
                    m_events.ScheduleEvent(EVENT_GIVE_UP, 100);
            }
            else
                me->AttackStop();
        }

        void EnterCombat(Unit* victim) override 
        { 
            if (Player* player = victim->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                Talk(0, player);
                m_events.ScheduleEvent(EVENT_TALK_PERIODIC, 5000);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_TALK_PERIODIC:
                {
                    if (me->GetHealthPct() > 70.0f)
                        Talk(1);
                    break;
                }
                case EVENT_GIVE_UP:
                {
                    if (!m_give_up)
                        if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        {
                            player->KilledMonsterCredit(NPC_BRUNO_FLAMERETARDANT);
                            Talk(2, player);                            
                            SetCombatNotAllowed(player, me);
                            m_give_up = true;
                            m_events.ScheduleEvent(EVENT_COMBAT_STOP, 6000);
                        }
                    
                    break;
                }
                case EVENT_COMBAT_STOP:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        SetCombatNotAllowed(player, me);
                    me->AI()->EnterEvadeMode();
                    m_events.ScheduleEvent(EVENT_RESET_TARGET, 4000);
                    break;
                }
                case EVENT_RESET_TARGET:
                {
                    me->AI()->EnterEvadeMode();
                    Initialize();
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
        return new npc_bruno_flameretardant_34835AI(creature);
    }
};

// 34876
class npc_frankie_gearslipper_34876 : public CreatureScript
{
public:
    npc_frankie_gearslipper_34876() : CreatureScript("npc_frankie_gearslipper_34876") { }

    enum eNpc
    {
        SPELL_THROW_GEARS = 75775,
    };

    struct npc_frankie_gearslipper_34876AI : public ScriptedAI
    {
        npc_frankie_gearslipper_34876AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_playerGUID;
        bool     m_give_up;

        void Initialize()
        {
            m_playerGUID = 0;
            m_give_up = false;
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
        }

        void JustDied(Unit* killer) override
        {
            Initialize();
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (!m_give_up)
            {
                if (me->GetHealthPct() < 50.0f)
                    m_events.ScheduleEvent(EVENT_GIVE_UP, 100);
            }
            else
                me->AttackStop();
        }

        void EnterCombat(Unit* victim) override
        {
            if (Player* player = victim->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                Talk(0, player);
                m_events.ScheduleEvent(EVENT_TALK_PERIODIC, 5000);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_TALK_PERIODIC:
                {
                    if (me->GetHealthPct() > 70.0f)
                        Talk(1);
                    break;
                }
                case EVENT_GIVE_UP:
                {
                    if (!m_give_up)
                        if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        {
                            player->KilledMonsterCredit(NPC_FRANKIE_GEARSLIPPER);
                            Talk(2, player);
                            SetCombatNotAllowed(player, me);
                            m_give_up = true;
                            m_events.ScheduleEvent(EVENT_COMBAT_STOP, 6000);
                        }

                    break;
                }
                case EVENT_COMBAT_STOP:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        SetCombatNotAllowed(player, me);
                    me->AI()->EnterEvadeMode();
                    m_events.ScheduleEvent(EVENT_RESET_TARGET, 4000);
                    break;
                }
                case EVENT_RESET_TARGET:
                {
                    me->AI()->EnterEvadeMode();
                    Initialize();
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
        return new npc_frankie_gearslipper_34876AI(creature);
    }
};

// 34877
class npc_jack_the_hammer_34877 : public CreatureScript
{
public:
    npc_jack_the_hammer_34877() : CreatureScript("npc_jack_the_hammer_34877") { }

    enum eNpc
    {
        SPELL_KNOCKBACK = 75986,
        SPELL_ACIDIC_SWEAT = 76136,
    };

    struct npc_jack_the_hammer_34877AI : public ScriptedAI
    {
        npc_jack_the_hammer_34877AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_playerGUID;
        bool     m_give_up;

        void Initialize()
        {
            m_playerGUID = 0;
            m_give_up = false;
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
        }

        void JustDied(Unit* killer) override
        {
            Initialize();
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (!m_give_up)
            {
                if (me->GetHealthPct() < 50.0f)
                    m_events.ScheduleEvent(EVENT_GIVE_UP, 100);
            }
            else
                me->AttackStop();
        }

        void EnterCombat(Unit* victim) override
        {
            if (Player* player = victim->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                Talk(0, player);
                m_events.ScheduleEvent(EVENT_TALK_PERIODIC, 5000);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_TALK_PERIODIC:
                {
                    if (me->GetHealthPct() > 70.0f)
                        Talk(1);
                    break;
                }
                case EVENT_GIVE_UP:
                {
                    if (!m_give_up)
                        if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        {
                            player->KilledMonsterCredit(NPC_JACK_THE_HAMMER);
                            Talk(2, player);
                            SetCombatNotAllowed(player, me);
                            m_give_up = true;
                            m_events.ScheduleEvent(EVENT_COMBAT_STOP, 6000);
                        }

                    break;
                }
                case EVENT_COMBAT_STOP:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        SetCombatNotAllowed(player, me);
                    me->AI()->EnterEvadeMode();
                    m_events.ScheduleEvent(EVENT_RESET_TARGET, 4000);
                    break;
                }
                case EVENT_RESET_TARGET:
                {
                    me->AI()->EnterEvadeMode();
                    Initialize();
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
        return new npc_jack_the_hammer_34877AI(creature);
    }
};

// 34878
class npc_sudsy_magee_34878 : public CreatureScript
{
public:
    npc_sudsy_magee_34878() : CreatureScript("npc_sudsy_magee_34878") { }

    enum eNpc
    {
        SPELL_BUBBLE_BLAST = 75761,
        SPELL_FROSTBOLT = 9672,
    };

    struct npc_sudsy_magee_34878AI : public ScriptedAI
    {
        npc_sudsy_magee_34878AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_playerGUID;
        bool     m_give_up;

        void Initialize()
        {
            m_playerGUID = 0;
            m_give_up = false;
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
        }

        void JustDied(Unit* killer) override 
        {
            Initialize();
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (!m_give_up)
            {
                if (me->GetHealthPct() < 50.0f)
                    m_events.ScheduleEvent(EVENT_GIVE_UP, 100);
            }
            else
                me->AttackStop();
        }

        void EnterCombat(Unit* victim) override
        {
            if (Player* player = victim->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                Talk(0, player);
                m_events.ScheduleEvent(EVENT_TALK_PERIODIC, 5000);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_TALK_PERIODIC:
                {
                    if (me->GetHealthPct() > 70.0f)
                        Talk(1);
                    break;
                }
                case EVENT_GIVE_UP:
                {
                    if (!m_give_up)
                        if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        {
                            player->KilledMonsterCredit(NPC_SUDSY_MAGEE);
                            Talk(2, player);
                            SetCombatNotAllowed(player, me);
                            m_give_up = true;
                            m_events.ScheduleEvent(EVENT_COMBAT_STOP, 6000);
                        }

                    break;
                }
                case EVENT_COMBAT_STOP:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        SetCombatNotAllowed(player, me);
                    me->AI()->EnterEvadeMode();
                    m_events.ScheduleEvent(EVENT_RESET_TARGET, 4000);
                    break;
                }
                case EVENT_RESET_TARGET:
                {
                    me->AI()->EnterEvadeMode();
                    Initialize();
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
        return new npc_sudsy_magee_34878AI(creature);
    }
};

// 37106
class npc_coach_crosscheck_37106 : public CreatureScript
{
public:
    npc_coach_crosscheck_37106() : CreatureScript("npc_coach_crosscheck_37106") { }

    struct npc_coach_crosscheck_37106AI : public ScriptedAI
    {
        npc_coach_crosscheck_37106AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap  m_events;
        uint64    m_playerGUID;
        uint64    m_firstBuccaneerGUID;

        void Reset() override
        {
            m_playerGUID = 0;
            m_firstBuccaneerGUID = 0;
        }

        bool sQuestAccept(Player* player, Quest const* quest) 
        { 
            player->AddAura(SPELL_INVISIBILITY_DETECTION_4, player);
            m_playerGUID = player->GetGUID();
            switch (quest->GetQuestId())
            {
            case QUEST_THE_REPLACEMENTS:
                Talk(0, player);
                break;
            case QUEST_NECCASSARY_ROUGHNESS:
                player->RemoveAura(SPELL_INVISIBILITY_DETECTION_6);
                player->RemoveAura(SPELL_INVISIBILITY_DETECTION_7);
                Talk(1, player);
                InitBuccaneer();
                break;
            case QUEST_FOURTH_AND_GOAL:
                player->RemoveAura(SPELL_INVISIBILITY_DETECTION_5);
                player->RemoveAura(SPELL_INVISIBILITY_DETECTION_6);
                player->RemoveAura(SPELL_INVISIBILITY_DETECTION_7);
                break;
            case QUEST_GIVE_SASSY_THE_NEWS:
                player->RemoveAura(SPELL_INVISIBILITY_DETECTION_6);
                player->RemoveAura(SPELL_INVISIBILITY_DETECTION_7);
                break;
            }
            return false; 
        }

        bool sQuestReward(Player* player, Quest const* quest, uint32 /*opt*/)
        {
            switch (quest->GetQuestId())
            {
            case QUEST_NECCASSARY_ROUGHNESS:
            {
                player->ExitVehicle();
                player->AddAura(SPELL_INVISIBILITY_DETECTION_4, player);
                return true;
            }
            case QUEST_REPORT_FOR_TRYOUTS:
            case QUEST_THE_REPLACEMENTS:
            case QUEST_FOURTH_AND_GOAL:
                player->AddAura(SPELL_INVISIBILITY_DETECTION_4, player);
                break;
            }
            return false;
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
        }

        void FindFirstBuccaneer()
        {
            if (Creature* buccaneer = sObjectAccessor->GetCreature(*me, m_firstBuccaneerGUID))
                return;

            if (Creature* buccaneer = me->FindNearestCreature(48526, 30.0f))
                m_firstBuccaneerGUID = buccaneer->GetGUID();
        }

        void InitBuccaneer()
        {
            FindFirstBuccaneer();
            if (Creature* buccaneer = sObjectAccessor->GetCreature(*me, m_firstBuccaneerGUID))
                buccaneer->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_coach_crosscheck_37106AI(creature);
    }
};

// 48526
class npc_bilgewater_buccaneer_48526 : public CreatureScript
{
public:
    npc_bilgewater_buccaneer_48526() : CreatureScript("npc_bilgewater_buccaneer_48526") { }

    struct npc_bilgewater_buccaneer_48526AI : public ScriptedAI
    {
        npc_bilgewater_buccaneer_48526AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset() override
        {
            m_events.RescheduleEvent(EVENT_CHECK_PLAYER_NEAR, 1000);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_PLAYER_NEAR:
                {
                    std::list<Player*> pList = me->FindNearestPlayers(30.0f);
                    bool ok = false;
                    for (auto player : pList)
                        if (player->GetQuestStatus(QUEST_NECCASSARY_ROUGHNESS) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_FOURTH_AND_GOAL) == QUEST_STATUS_INCOMPLETE)
                            ok = true;
                    if (ok)
                        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                    else
                        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);

                    m_events.ScheduleEvent(EVENT_CHECK_PLAYER_NEAR, 2500);
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
        return new npc_bilgewater_buccaneer_48526AI(creature);
    }
};

// 37179
class npc_bilgewater_buccaneer_37179 : public CreatureScript
{
public:
    npc_bilgewater_buccaneer_37179() : CreatureScript("npc_bilgewater_buccaneer_37179") { }

    enum eNpc
    {
        SPELL_SUMMON_STEAMWHEEDLE_SHARK = 69971,
    };

    struct npc_bilgewater_buccaneer_37179AI : public VehicleAI
    {
        npc_bilgewater_buccaneer_37179AI(Creature* creature) : VehicleAI(creature) { }

        EventMap m_events;
        uint64 m_playerGUID;
        std::list<uint64> sList;
        std::list<uint64> zList;

        void Reset() override
        {
            m_playerGUID = 0;
            me->AddAura(SPELL_QUEST_INVISIBILITY_5, me);
            me->SetOrientation(3.19f);
        }

        void JustSummoned(Creature* summon) override
        {
            if (summon->GetEntry() == NPC_STEAMWHEEDLE_SHARK)
            {
                sList.push_back(summon->GetGUID());
                summon->AI()->SetGUID(m_playerGUID, PLAYER_GUID);
            }
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case PLAYER_GUID:
            {
                m_playerGUID = guid;
                break;
            }
            }
        }

        void DoAction(int32 param) 
        { 
            switch (param)
            {
            case 0:
                break;
            }
        }

        void PassengerBoarded(Unit* unit, int8 /*seat*/, bool apply) override
        {
            if (apply)
            {
                if (Player* player = unit->ToPlayer())
                {
                    me->SetOrientation(3.14f);
                    m_playerGUID = player->GetGUID();
                    player->RemoveAura(SPELL_INVISIBILITY_DETECTION_4);
                    player->AddAura(SPELL_INVISIBILITY_DETECTION_5, player);
                    if (player->GetQuestStatus(QUEST_NECCASSARY_ROUGHNESS) == QUEST_STATUS_INCOMPLETE)
                    {
                        player->KilledMonsterCredit(NPC_NECESSARY_ROUGHNESS_KILL_CREDIT);
                        m_events.ScheduleEvent(EVENT_PLAY_SOUND1, 1000);
                        m_events.ScheduleEvent(EVENT_START_PLAY_GAME, 4000);
                        m_events.ScheduleEvent(EVENT_PERIODIC_CHEERING, 250);
                    }
                }
            }
            else
            {
                if (Player* player = unit->ToPlayer())
                {
                    player->RemoveAura(SPELL_INVISIBILITY_DETECTION_5);
                    player->AddAura(SPELL_INVISIBILITY_DETECTION_4, player);
                }
                StopPlayGame();
            }
        }

        void CreatureMoveInLineOfSight(Unit* who) override
        {
            if (who->GetEntry() == NPC_STEAMWHEEDLE_SHARK)
                if (who->GetDistance2d(me) < 3.0f)
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        player->SetQuestStatus(QUEST_NECCASSARY_ROUGHNESS, QUEST_STATUS_FAILED);
                        if (Vehicle* vehicle = me->GetVehicleKit())
                            vehicle->RemoveAllPassengers();
                    }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);
            VehicleAI::UpdateAI(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_PLAY_SOUND1:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        player->PlayDirectSound(17466, player);
                        m_events.ScheduleEvent(EVENT_PLAY_SOUND1, 1000);
                    }
                    break;
                }
                case EVENT_START_PLAY_GAME:
                {
                    StartPlayGame();
                    break;
                }
                case EVENT_PERIODIC_CHEERING:
                {
                    for (uint32 i = 0; i < urand(3, 10); i++)
                        if (Creature* npc = GetRandomObserver())
                            npc->HandleEmoteCommand(GetRandomEmote());

                    m_events.ScheduleEvent(EVENT_PERIODIC_CHEERING, 500);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void StartPlayGame()
        {
            me->CastSpell(-8291.62f, 1479.97f, 43.8908f, SPELL_SUMMON_STEAMWHEEDLE_SHARK + 0, true);
            me->CastSpell(-8285.75f, 1484.46f, 42.9395f, SPELL_SUMMON_STEAMWHEEDLE_SHARK + 5, true);
            me->CastSpell(-8291.08f, 1487.72f, 43.8463f, SPELL_SUMMON_STEAMWHEEDLE_SHARK + 6, true);
            me->CastSpell(-8288.04f, 1477.49f, 43.3046f, SPELL_SUMMON_STEAMWHEEDLE_SHARK + 7, true);
            me->CastSpell(-8288.33f, 1490.41f, 43.4756f, SPELL_SUMMON_STEAMWHEEDLE_SHARK + 8, true);
            me->CastSpell(-8295.10f, 1484.91f, 44.3231f, SPELL_SUMMON_STEAMWHEEDLE_SHARK + 9, true);
            me->CastSpell(-8294.66f, 1474.68f, 44.2946f, SPELL_SUMMON_STEAMWHEEDLE_SHARK + 10, true);
            me->CastSpell(-8294.61f, 1493.67f, 44.6239f, SPELL_SUMMON_STEAMWHEEDLE_SHARK + 11, true);
        }

        void StopPlayGame()
        {
            for (auto guid : sList)
                if (Creature* shark = ObjectAccessor::GetCreature(*me, guid))
                    shark->DespawnOrUnsummon(1);
            m_playerGUID = 0;
            m_events.Reset();
            sList.clear();
        }

        void LoadObserver()
        {
            std::list<Creature*> crList = me->FindNearestCreatures(NPC_KEZAN_CITIZEN_35063, 50.0f);
            for (auto npc : crList)
                zList.push_back(npc->GetGUID());
        }

        uint32 GetRandomEmote()
        {
            return RAND(1, 4, 5, 6, 11, 14, 15, 25, 92, 94, 274);
        }

        Creature* GetRandomObserver()
        {
            if (zList.size() == 0)
                LoadObserver();
            else
            {
                uint32 rol2 = urand(0, zList.size() - 1);
                std::list<uint64>::iterator itr = zList.begin();
                std::advance(itr, rol2);
                return ObjectAccessor::GetCreature(*me, *itr);
            }
            return nullptr;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_bilgewater_buccaneer_37179AI(creature);
    }
};

// 37114
class npc_steamwheedle_shark_37114 : public CreatureScript
{
public:
    npc_steamwheedle_shark_37114() : CreatureScript("npc_steamwheedle_shark_37114") { }

    struct npc_steamwheedle_shark_37114AI : public ScriptedAI
    {
        npc_steamwheedle_shark_37114AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_buccaneerGUID;

        void Reset() override
        {
            m_playerGUID = 0;
            m_buccaneerGUID = 0;
        }

        void IsSummonedBy(Unit* summoner) override 
        { 
            if (Creature* npc = summoner->ToCreature())
                if (npc->GetEntry() == NPC_BILGEWATER_BUCCANEER)
                    m_buccaneerGUID = npc->GetGUID();
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override 
        { 
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveIdle();
            m_events.ScheduleEvent(EVENT_WE_ARE_KILLED, 10);
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case PLAYER_GUID:
                m_playerGUID = guid;
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
                case EVENT_WE_ARE_KILLED:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        player->Kill(me);
                        me->AddAura(SPELL_PERMANENT_FEIGN_DEATH, me);
                        player->KilledMonsterCredit(NPC_STEAMWHEEDLE_SHARK);
                    }
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
        return new npc_steamwheedle_shark_37114AI(creature);
    }
};

// 37213
class npc_bilgewater_buccaneer_37213 : public CreatureScript
{
public:
    npc_bilgewater_buccaneer_37213() : CreatureScript("npc_bilgewater_buccaneer_37213") { }

    enum eNpc
    {
        SPELL_SUMMON_DEATHWING = 66322,
    };

    struct npc_bilgewater_buccaneer_37213AI : public VehicleAI
    {
        npc_bilgewater_buccaneer_37213AI(Creature* creature) : VehicleAI(creature) { }

        EventMap m_events;
        uint64 m_playerGUID;
        bool   m_DeathwingSummoned;
        uint32 m_counter;

        void Reset() override
        {
            m_DeathwingSummoned = false;
            m_playerGUID = 0;
            m_counter=0;
            me->AddAura(SPELL_QUEST_INVISIBILITY_6, me);
            me->AddAura(SPELL_QUEST_INVISIBILITY_7, me);
            me->SetOrientation(3.14f);
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                player->RemoveAura(SPELL_INVISIBILITY_DETECTION_4);
                player->AddAura(SPELL_INVISIBILITY_DETECTION_7, player);
                player->EnterVehicle(me, 0);
                m_events.ScheduleEvent(EVENT_PLAY_SOUND1, 1000);
            }
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (!m_DeathwingSummoned)
                if (spell->Id == SPELL_SIGNAL_BACK_TO_SHREDDER)
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        player->PlayDirectSound(8574, player);
                        m_events.ScheduleEvent(EVENT_SUMMON_DEATHWING, 100);
                    }
        }

        void PassengerBoarded(Unit* unit, int8 /*seat*/, bool apply) override
        {
            if (apply)
            {
                me->CastSpell(me, SPELL_INCREASED_MOD_DETECTED_RANGE, true);
                if (Player* player = unit->ToPlayer())
                    if (Creature* npc = me->FindNearestCreature(NPC_FOURTH_AND_GOAL_TARGET, 50.0f))
                        player->ToUnit()->Talk(37050, CHAT_MSG_RAID_BOSS_WHISPER, 50.0f, player);
            }
            else
            {
                if (Player* player = unit->ToPlayer())
                {
                    player->RemoveAura(SPELL_INVISIBILITY_DETECTION_7);
                    player->AddAura(SPELL_INVISIBILITY_DETECTION_4, player);
                }
                me->RemoveAura(SPELL_INCREASED_MOD_DETECTED_RANGE);
                me->DespawnOrUnsummon(100);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);
            VehicleAI::UpdateAI(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_PLAY_SOUND1:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        player->PlayDirectSound(17466, player);
                    m_events.ScheduleEvent(EVENT_PLAY_SOUND1, 1000);
                    break;
                }
                case EVENT_PLAY_SOUND2:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        player->PlayDirectSound(RAND(14556, 14557, 14558), player);
                    m_counter += 1;
                    if (m_counter < 3)
                        m_events.ScheduleEvent(EVENT_PLAY_SOUND2, 3000);
                    break;
                }
                case EVENT_SUMMON_DEATHWING:
                {
                    if (!m_DeathwingSummoned)
                        if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        {
                            m_DeathwingSummoned = true;
                            player->RemoveAura(SPELL_INVISIBILITY_DETECTION_7);
                            player->AddAura(SPELL_INVISIBILITY_DETECTION_6, player);
                            player->SummonCreature(48572, -8230.59f, 1482.14f, 110.9156f, TEMPSUMMON_MANUAL_DESPAWN);
                            player->KilledMonsterCredit(NPC_FOURTH_AND_GOAL_TARGET);
                            m_events.CancelEvent(EVENT_PLAY_SOUND1);
                            player->PlayDirectSound(17467, player);
                            m_events.ScheduleEvent(EVENT_PLAY_SOUND2, 3000);
                        }
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
        return new npc_bilgewater_buccaneer_37213AI(creature);
    }
};

// 37203
class npc_fourth_and_goal_target_37203 : public CreatureScript
{
public:
    npc_fourth_and_goal_target_37203() : CreatureScript("npc_fourth_and_goal_target_37203") { }

    struct npc_fourth_and_goal_target_37203AI : public ScriptedAI
    {
        npc_fourth_and_goal_target_37203AI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            me->CastSpell(me, 70086, true);
            me->AddAura(SPELL_QUEST_INVISIBILITY_7, me);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_fourth_and_goal_target_37203AI(creature);
    }
};

// 70052
class spell_kick_footbomb_70052 : public SpellScriptLoader
{
public:
    spell_kick_footbomb_70052() : SpellScriptLoader("spell_kick_footbomb_70052") { }

    class spell_kick_footbomb_70052_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_kick_footbomb_70052_SpellScript);

        void SelectDest()
        {
            if (Position* dest = const_cast<WorldLocation*>(GetExplTargetDest()))
            {
                if (dest->GetPositionY() > 1450.0f && dest->GetPositionY() < 1525.0f)
                    if (dest->GetPositionZ() > 100.0f && dest->GetPositionZ() < 300.0f)
                        GetCaster()->CastSpell(GetCaster(), SPELL_SIGNAL_BACK_TO_SHREDDER);
            }
        }

        void Register() override
        {
            BeforeCast += SpellCastFn(spell_kick_footbomb_70052_SpellScript::SelectDest);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_kick_footbomb_70052_SpellScript();
    }
};

// 48572
class npc_deathwing_48572 : public CreatureScript
{
public:
    npc_deathwing_48572() : CreatureScript("npc_deathwing_48572") { }

    struct npc_deathwing_48572AI : public ScriptedAI
    {
        npc_deathwing_48572AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64 m_playerGUID;
        uint32 m_nextPoint;
        float  m_newSpeed;

        void Reset() override
        {
            me->AddAura(SPELL_QUEST_INVISIBILITY_6, me);
            me->SetDisableGravity(true);
            me->SetObjectScale(0.6f);
            me->GetMotionMaster()->MovePoint(2001, -8320.0f, 1473.0f, 110.0f);
            m_nextPoint=0;
            m_newSpeed=0;
        }

        void IsSummonedBy(Unit* summoner) override 
        { 
            if (Player* player = summoner->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                player->PlayDirectSound(8574, player);
            }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type != POINT_MOTION_TYPE)
                return;

            switch (id)
            {
            case 2001:
                m_events.ScheduleEvent(EVENT_MOVE_PART1, 10);
                break;
            case 2002:
                m_events.ScheduleEvent(EVENT_MOVE_PART2, 10);
                break;
            case 2003:
                m_events.ScheduleEvent(EVENT_MOVE_PART3, 10);
                break;
            case 2004:
                m_events.ScheduleEvent(EVENT_MOVE_PART4, 10);
                break;
            case 2005:
                m_events.ScheduleEvent(EVENT_MOVE_PART5, 10);
                break;
            case 2006:
                m_events.ScheduleEvent(EVENT_MOVE_PART6, 10);
                break;
            case 2007:
                m_events.ScheduleEvent(EVENT_MOVE_PART7, 10);
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
                case EVENT_WAIT_TO_MOVE:
                {
                    if (m_newSpeed)
                        me->SetSpeed(MOVE_RUN, m_newSpeed);
                    switch (m_nextPoint)
                    {
                    case 2004:
                        me->GetMotionMaster()->MovePoint(2004, -8330.0f, 1460.0f, 110.0f);
                        break;
                    }
                    m_nextPoint = 0;
                    m_newSpeed = 0;
                    break;
                }
                case EVENT_WAIT_FOR_NEW_SPEED:
                    if (m_newSpeed)
                        me->SetSpeed(MOVE_RUN, m_newSpeed);
                    m_newSpeed = 0;
                    break;
                case EVENT_MOVE_PART1:
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        player->PlayDirectSound(23227, player);
                    me->SetObjectScale(0.4f);
                    me->GetMotionMaster()->MovePoint(2002, -8320.0f, 1480.0f, 110.0f);
                    break;
                case EVENT_MOVE_PART2:
                    me->SetSpeed(MOVE_RUN, 0.2f);
                    m_events.ScheduleEvent(EVENT_TALK, 2000);
                    me->GetMotionMaster()->MovePoint(2003, -8330.0f, 1500.0f, 110.0f);
                    break;
                case EVENT_MOVE_PART3:                    
                    m_events.ScheduleEvent(EVENT_ATTACK_SPELL, 3000);
                    m_nextPoint = 2004;
                    m_newSpeed = 1.0f;
                    m_events.ScheduleEvent(EVENT_WAIT_TO_MOVE, 6500);
                    break;
                case EVENT_MOVE_PART4:
                    me->GetMotionMaster()->MovePoint(2005, -8320.0f, 1500.0f, 110.0f);
                    break;
                case EVENT_MOVE_PART5:
                    m_events.ScheduleEvent(EVENT_PLAY_SOUND1, 2000);
                    me->SetObjectScale(0.6f);
                    me->GetMotionMaster()->MovePoint(2006, -8250.0f, 1480.0f, 90.0f);
                    break;
                case EVENT_MOVE_PART6:
                    me->SetObjectScale(0.8f);
                    m_events.ScheduleEvent(EVENT_EXIT_VEHICLE, 2000);
                    m_events.ScheduleEvent(EVENT_EARTHQUAKE, 6000);
                    me->GetMotionMaster()->MovePoint(2007, -7900.0f, 1460.0f, 90.0f);
                    break;
                case EVENT_MOVE_PART7:
                    me->GetMotionMaster()->MovePoint(2008, -7900.0f, 1460.0f, 90.0f);
                    break;
                case EVENT_TALK:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        Talk(0, player);
                        player->PlayDirectSound(23228, player);
                    }
                    break;
                }
                case EVENT_ATTACK_SPELL:
                {
                    if (Creature* target = me->FindNearestCreature(42196, 250.0f))
                    {
                        me->SetFacingToObject(target);
                        me->CastSpell(target, SPELL_DEATHWINGS_ATTACK, true);
                    }
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        player->PlayDirectSound(23229, player);
                    break;
                }
                case EVENT_PLAY_SOUND1:
                {
                    me->CastSpell(me, SPELL_DEATHWING_SOUND_4, true);
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        player->PlayDirectSound(23230, player);
                        player->ToUnit()->Talk(37041, CHAT_MSG_RAID_BOSS_WHISPER, 25.0f, player);
                    }
                    break;
                }
                case EVENT_EXIT_VEHICLE:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        player->ExitVehicle();
                        player->PlayDirectSound(14559, player);
                    }
                    break;
                }
                case EVENT_EARTHQUAKE:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        // player->CastSpell(player, 90615, true); // Earthquake used many unknown quest..
                        player->CastSpell(player, 68707, true); // This Earthquake is taken drom Duskhaven..
                    }
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_deathwing_48572AI(creature);
    }
};

// 24110
class npc_elm_general_purpose_bunny_large_24110 : public CreatureScript
{
public:
    npc_elm_general_purpose_bunny_large_24110() : CreatureScript("npc_elm_general_purpose_bunny_large_24110") { }

    enum eNpc
    {
        NPC_OOMLOT_WARRIER_38531 = 38531,
    };

    struct npc_elm_general_purpose_bunny_large_24110AI : public ScriptedAI
    {
        npc_elm_general_purpose_bunny_large_24110AI(Creature* creature) : ScriptedAI(creature) {  }

        EventMap m_events;
        uint64   m_playerGUID;
        uint32   m_oomlot_counter;
        uint32   m_chain_position;
        uint64   m_nearestChainGUID;
        bool     m_validPlayerNear;

        void Reset() override
        {
            m_oomlot_counter = 0;
            m_chain_position = 0;
            m_nearestChainGUID = 0;
            m_validPlayerNear = false;
            if (me->GetMapId() == 648)
                if (me->HasInPhaseList(379)) // kezan, play musik on party
                    m_events.ScheduleEvent(EVENT_MUSIC_PERIODIC, 2500);
                else if (me->HasInPhaseList(181)) // lost isles.. create oomlot warrier..
                    m_events.RescheduleEvent(EVENT_CHECK_POSITION, 1000);
        }

        void JustSummoned(Creature* summon) override
        {
            switch (summon->GetEntry())
            {
            case NPC_OOMLOT_WARRIER_38531:
                m_oomlot_counter += 1;
                break;
            }
        }

        void SummonedCreatureDies(Creature* summon, Unit* killer) override
        {
            switch (summon->GetEntry())
            {
            case NPC_OOMLOT_WARRIER_38531:
                if (m_oomlot_counter > 0)
                    m_oomlot_counter -= 1;
                break;
            }
        }

        void SummonedCreatureDespawn(Creature* summon) override
        {
            switch (summon->GetEntry())
            {
            case NPC_OOMLOT_WARRIER_38531:
                if (m_oomlot_counter > 0)
                    m_oomlot_counter -= 1;
                break;
            }
        }

        void DoAction(int32 param) override 
        { 
            switch (param)
            {
            case 5:
                m_validPlayerNear = true;
                m_events.RescheduleEvent(EVENT_COOLDOWN_PLAYER_NEAR, 150000);
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
                case EVENT_MUSIC_PERIODIC:
                {
                    std::list<Player*> pList = me->FindNearestPlayers(50.0f);
                    for (auto player : pList)
                        if (player->GetQuestStatus(QUEST_LIFE_OF_THE_PARTY_M) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_LIFE_OF_THE_PARTY_F) == QUEST_STATUS_INCOMPLETE)
                            player->PlayDirectSound(15978, player);

                    m_events.ScheduleEvent(EVENT_MUSIC_PERIODIC, 2500);
                    break;
                }
                case EVENT_CHECK_POSITION:
                {
                    if (m_chain_position == 0)
                    {
                        if (Creature* sassy = me->FindNearestCreature(38387, 90.0f))
                        {
                            float dist = me->GetDistance(sassy);
                            if (dist < 40.0f)
                                m_chain_position = 1; // to near.. no spawn of oomlot warrier
                            else
                                m_chain_position = 2; // cannon area.. spawn of oomlot warrier: if player has entered cannon
                            m_events.RescheduleEvent(EVENT_CHECK_POSITION, 1000);
                        }
                        else
                        {
                            m_chain_position = 3; // far spawn of oomlot warrier  to populate the way..
                            m_events.RescheduleEvent(EVENT_CHECK_POSITION, 1000);
                            m_events.RescheduleEvent(EVENT_CREATE_WARRIER, 2500);
                        }
                    }
                    break;
                }
                case EVENT_CREATE_WARRIER:
                {
                    if (m_validPlayerNear == false)
                        m_events.RescheduleEvent(EVENT_COOLDOWN_PLAYER_NEAR, 1000);
                    else if (m_oomlot_counter < 2)
                    {
                        Position pos = me->GetNearPosition(3.0f, frand(0, 6.28f));
                        me->SummonCreature(38531, pos, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 250000);
                    }

                    m_events.RescheduleEvent(EVENT_CREATE_WARRIER, 2500);
                    break;
                }
                case EVENT_COOLDOWN_PLAYER_NEAR:
                {
                    bool check = false;
                    std::list<Player*> pList = me->FindNearestPlayers(100.0f);
                    for (auto player : pList)
                        if (player->HasInPhaseList(181))
                            check = true;
                    if (check)
                    {
                        std::list<Creature*> cList = me->FindNearestCreatures(24110, 100.0f);
                        for (auto npc : cList)
                            npc->AI()->DoAction(5);
                    }

                    m_validPlayerNear = check;
                    m_events.RescheduleEvent(EVENT_COOLDOWN_PLAYER_NEAR, 150000);
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_elm_general_purpose_bunny_large_24110AI(creature);
    }
};

// 35175, 35186
class npc_kezan_partygoer_35175_86 : public CreatureScript
{
public:
    npc_kezan_partygoer_35175_86() : CreatureScript("npc_kezan_partygoer_35175_86") { }

    enum eNpc
    {
        TYPE_BUBBLY = 1,
        TYPE_BUCKET = 2,
        TYPE_DANCE = 3,
        TYPE_FIREWORKS = 4,
        TYPE_HORS_DOEUVRES = 5,
        SPELL_BUBBLY = 75042,
        SPELL_BUCKET = 75044,
        SPELL_DANCE = 75046,
        SPELL_FIREWORKS = 75048,
        SPELL_HORS_DOEUVRES = 75050,
        SPELL_COSMETIC_STUN = 46957,
        SPELL_COSMETIC_DRUNKEN_INTOXICATION = 55664,
        SPELL_LOTP_BUBBLY = 75122,
        SPELL_LOTP_BUCKET = 66931,
        SPELL_LOTP_DANCE = 75123,
        SPELL_LOTP_FIREWORKS_BLUE = 66917,
        SPELL_LOTP_FIREWORKS_GREEN = 66918,
        SPELL_LOTP_FIREWORKS_RED = 66919,
        SPELL_LOTP_HORS_DOEUVRES = 75124,
        SPELL_LOTP_PAPARAZZI = 66929,
        SPELL_LOTP_SUMMON_DISCO_BALL = 66930,
        SPELL_LOTP_SUMMON_BUCKET = 75044,
        SPELL_LOTP_VOMIT = 43391,
        SPELL_PLAYER_BUBBLY = 66909,
        SPELL_PLAYER_BUCKET = 66910,
        SPELL_PLAYER_DANCE = 66911,
        SPELL_PLAYER_FIREWORKS = 66912,
        SPELL_PLAYER_HORS_DOEUVRES = 66913,
    };

    struct npc_kezan_partygoer_35175_86AI : public ScriptedAI
    {
        npc_kezan_partygoer_35175_86AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_playerGUID;
        uint32   m_partyTyp;
        bool     m_doing;
        bool     m_cooldown;

        void Initialize()
        {
            m_partyTyp = urand(1, 5);
            m_doing = false;
            m_cooldown = false;
        }

        void Reset() override
        {
            switch (m_partyTyp)
            {
            case 0:
                me->AddAura(SPELL_BUBBLY, me);
                break;
            case 1:
                me->AddAura(SPELL_BUCKET, me);
                me->AddAura(SPELL_COSMETIC_STUN, me);
                me->AddAura(SPELL_COSMETIC_DRUNKEN_INTOXICATION, me);
                break;
            case 2:
                me->AddAura(SPELL_DANCE, me);
                break;
            case 3:
                me->AddAura(SPELL_FIREWORKS, me);
                break;
            case 4:
                me->AddAura(SPELL_HORS_DOEUVRES, me);
                break;
            }
            m_events.RescheduleEvent(EVENT_CHECK_START_PARTY, 1000);
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            uint32 m_playerQuest = 0;
            if (Player* player = caster->ToPlayer())
            {
                if (player->GetQuestStatus(QUEST_LIFE_OF_THE_PARTY_F) == QUEST_STATUS_INCOMPLETE)
                    m_playerQuest = QUEST_LIFE_OF_THE_PARTY_F;
                else if (player->GetQuestStatus(QUEST_LIFE_OF_THE_PARTY_M) == QUEST_STATUS_INCOMPLETE)
                    m_playerQuest = QUEST_LIFE_OF_THE_PARTY_M;

                if (m_playerQuest > 0)
                    if (m_partyTyp = 1 && spell->Id == SPELL_PLAYER_BUBBLY)
                    {
                        me->CastSpell(me, SPELL_LOTP_BUBBLY);
                        player->KilledMonsterCredit(35175);
                    }
                    else if (m_partyTyp = 2 && spell->Id == SPELL_PLAYER_BUCKET)
                    {
                        me->CastSpell(me, SPELL_LOTP_BUCKET);
                        me->CastSpell(me, SPELL_LOTP_SUMMON_BUCKET);
                        player->KilledMonsterCredit(35175);
                    }
                    else if (m_partyTyp = 3 && spell->Id == SPELL_PLAYER_DANCE)
                    {
                        me->CastSpell(me, SPELL_LOTP_DANCE);
                        me->CastSpell(me, SPELL_LOTP_SUMMON_DISCO_BALL);
                        player->KilledMonsterCredit(35175);
                    }
                    else if (m_partyTyp = 4 && spell->Id == SPELL_PLAYER_FIREWORKS)
                    {
                        switch (urand(1, 3))
                        {
                        case 1:
                            me->CastSpell(me, SPELL_LOTP_FIREWORKS_BLUE);
                            break;
                        case 2:
                            me->CastSpell(me, SPELL_LOTP_FIREWORKS_GREEN);
                            break;
                        case 3:
                            me->CastSpell(me, SPELL_LOTP_FIREWORKS_RED);
                            break;
                        }
                        player->KilledMonsterCredit(35175);
                    }
                    else if (m_partyTyp = 5 && spell->Id == SPELL_PLAYER_HORS_DOEUVRES)
                    {
                        me->CastSpell(me, SPELL_LOTP_HORS_DOEUVRES);
                        player->KilledMonsterCredit(35175);
                    }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_START_PARTY:
                {
                    if (!m_doing && !m_cooldown)
                        if (Player* player = me->FindNearestPlayer(15.0f))
                        {
                            uint32 m_playerQuest = 0;
                            if (player->GetQuestStatus(QUEST_LIFE_OF_THE_PARTY_F) == QUEST_STATUS_INCOMPLETE)
                                m_playerQuest = QUEST_LIFE_OF_THE_PARTY_F;
                            else if (player->GetQuestStatus(QUEST_LIFE_OF_THE_PARTY_M) == QUEST_STATUS_INCOMPLETE)
                                m_playerQuest = QUEST_LIFE_OF_THE_PARTY_M;
                            if (urand(0, 100) < 30 && m_playerQuest)
                            {
                                m_playerGUID = player->GetGUID();
                                Talk(m_partyTyp, player);
                                m_doing = true;
                                m_cooldown = true;
                                m_events.ScheduleEvent(EVENT_PARTY_COOLDOWN, 120000);
                            }
                            else
                            {
                                m_cooldown = true;
                                m_events.ScheduleEvent(EVENT_PARTY_COOLDOWN, urand(30000, 60000));
                            }
                        }

                    m_events.ScheduleEvent(EVENT_CHECK_START_PARTY, 1000);
                    break;
                }
                case EVENT_PARTY_COOLDOWN:
                {
                    m_doing = false;
                    m_cooldown = false;
                    me->RemoveAura(SPELL_LOTP_HAPPY_PARTYGOER);
                    break;
                }
                case EVENT_START_PARTY:
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
        return new npc_kezan_partygoer_35175_86AI(creature);
    }
};

// 195488
class go_kajamite_deposit_195488 : public GameObjectScript
{
public:
    go_kajamite_deposit_195488() : GameObjectScript("go_kajamite_deposit_195488") { }

    struct go_kajamite_deposit_195488AI : public GameObjectAI
    {
        go_kajamite_deposit_195488AI(GameObject* go) : GameObjectAI(go) { }

        void OnStateChanged(uint32 state, Unit* unit) override
        {
            if (unit)
                if (Player* player = unit->ToPlayer())
                    if (player->GetQuestStatus(14124) == QUEST_STATUS_INCOMPLETE)
                    {
                        uint8 rol = urand(2, 3);
                        for (uint8 i = 0; i < rol; i++)
                        {
                            Position pos = go->GetNearPosition(0.4f, frand(0, 6.24f));
                            go->SummonGameObject(195492, pos.m_positionX, pos.m_positionY, pos.m_positionZ + 0.3f, pos.m_orientation, 0, 0, 0, 0, 60000);
                        }
                        go->Delete();
                    }
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_kajamite_deposit_195488AI(go);
    }

};

// 35234
class npc_hired_looter_35234 : public CreatureScript
{
public:
    npc_hired_looter_35234() : CreatureScript("npc_hired_looter_35234") { }

    struct npc_hired_looter_35234AI : public ScriptedAI
    {
        npc_hired_looter_35234AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_playerGUID;
        bool     m_torchCoolDown;
        bool     m_markToKill;

        void Initialize()
        {
            m_torchCoolDown=false;
            m_markToKill=false;
        }

        void Reset() override
        {
           m_playerGUID = 0;
           me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
           me->ClearUnitState(UNIT_STATE_STUNNED);
        }

        void EnterCombat(Unit* victim) override
        {
            if (!m_markToKill)
                if (!m_torchCoolDown)
                {
                    me->CastSpell(victim, SPELL_TORCH_TOSS);
                    m_torchCoolDown = true;
                    m_events.ScheduleEvent(EVENT_TORCH_COOLDOWN, urand(7800, 21300));
                }
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (!m_markToKill)
                if (spell->Id == SPELL_HOT_ROD_KNOCKBACK_1)
                    if (Player* player = GetPlayer(caster))
                    {
                        me->AddUnitState(UNIT_STATE_STUNNED);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                        m_playerGUID = player->GetGUID();                        
                        m_markToKill = true;
                        m_events.ScheduleEvent(EVENT_KILL_TARGET, 1000);
                    }
        }

        void EnterEvadeMode() override { }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_TORCH_COOLDOWN:
                {
                    m_torchCoolDown = false;
                    break;
                }
                case EVENT_KILL_TARGET:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        if (player->GetQuestStatus(QUEST_ROBBING_HOODS) == QUEST_STATUS_INCOMPLETE)
                            me->CastSpell(player, SPELL_CREATE_STOLEN_LOOT, true);
                        player->Kill(me);
                    }
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        Player* GetPlayer(Unit* caster)
        {
            if (Player* player = caster->ToPlayer())
                return player;
            else if (Vehicle* hot = caster->GetVehicleKit())
                if (Unit* pass = hot->GetPassenger(0))
                    if (Player* player = pass->ToPlayer())
                        return player;
            return nullptr;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_hired_looter_35234AI(creature);
    }
};

// 35063 35073
class npc_kezan_citizen_35063 : public CreatureScript
{
public:
    npc_kezan_citizen_35063() : CreatureScript("npc_kezan_citizen_35063_35075") { }

    struct npc_kezan_citizen_35063AI : public ScriptedAI
    {
        npc_kezan_citizen_35063AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        bool m_talkCoolDown;

        void Reset()
        {
            m_talkCoolDown = false;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (!m_talkCoolDown)
                if (spell->Id == SPELL_HOT_ROD_KNOCKBACK_1 || spell->Id == SPELL_HOT_ROD_KNOCKBACK_2)
                    if (Player* player = GetPlayer(caster))
                    {
                        Talk(0, player); // 1411, 18500 (5)
                        m_talkCoolDown = true;
                        m_events.ScheduleEvent(EVENT_TALK_COOLDOWN, 20000);
                        m_events.ScheduleEvent(EVENT_MOVE_HOME, 10000);
                    }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_TALK_COOLDOWN:
                {
                    m_talkCoolDown = false;
                    break;
                }
                case EVENT_MOVE_HOME:
                {
                    me->GetMotionMaster()->MoveTargetedHome();
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        Player* GetPlayer(Unit* caster)
        {
            if (Player* player = caster->ToPlayer())
                return player;
            else if (Vehicle* hot = caster->GetVehicleKit())
                if (Unit* pass = hot->GetPassenger(0))
                    if (Player* player = pass->ToPlayer())
                        return player;
            return nullptr;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_kezan_citizen_35063AI(creature);
    }
};

// 35486
class npc_first_bank_of_kezan_vault_35486 : public CreatureScript
{
public:
    npc_first_bank_of_kezan_vault_35486() : CreatureScript("npc_first_bank_of_kezan_vault_35486") { }

    enum eNpc
    {
        SPELL_SUMMON_BUNNY_VEHICLE = 67488,
        SPELL_POWER_CORRECT = 67493,
        SPELL_POWER_INCORRECT = 67494,
        SPELL_DRILL_AURA = 67495,
        SPELL_EXPLOSIV_AURA = 67496,
        SPELL_LISTEN_AURA = 67497,
        SPELL_LOCKPICK_AURA = 67498,
        SPELL_G_RAY_AURA = 67499,
        SPELL_VAULT_INTERACT = 67555,
        SPELL_VAULT_CRACKING_TOOLSET = 67476,
        SPELL_VEHICLE_EXIT_SPELL = 67579,
        SPELL_VAULT_CRACKED = 67492,
    };

    struct npc_first_bank_of_kezan_vault_35486AI : public VehicleAI
    {
        npc_first_bank_of_kezan_vault_35486AI(Creature* creature) : VehicleAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_playerGUID;
        uint32   m_count;
        int32    m_playRol;
        int32    m_playSpell;

        void Initialize()
        {
            m_playerGUID = 0;
            m_count = 0;
            m_playRol = 0;
            m_playSpell = 0;
        }

        void Reset() override
        {
            me->SetMaxPower(POWER_MANA, 100);
            me->SetPower(POWER_MANA, 0);
            m_events.ScheduleEvent(EVENT_MASTER_RESET, 120000);
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (Player* player = who->ToPlayer())
                if (who->GetUInt32Value(UNIT_NPC_EMOTESTATE))
                    player->HandleEmoteState(0);
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override
        {
            if (apply)
            {
                if (Player* player = passenger->ToPlayer())
                {
                    m_playerGUID = player->GetGUID();
                    player->KilledMonsterCredit(me->GetEntry());
                    m_events.ScheduleEvent(EVENT_START_PLAY, 100);
                }
            }
            else
            {
                Initialize();
                if (passenger->HasAura(SPELL_VAULT_CRACKING_TOOLSET))
                    passenger->RemoveAura(SPELL_VAULT_CRACKING_TOOLSET);
            }
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            bool good = false;
            bool bad = false;
            switch (spell->Id)
            {
            case 67526:
                if (m_playSpell == SPELL_G_RAY_AURA) good = true; else bad = true;
                break;
            case 67525:
                if (m_playSpell == SPELL_LOCKPICK_AURA) good = true; else bad = true;
                break;
            case 67524:
                if (m_playSpell == SPELL_LISTEN_AURA) good = true; else bad = true;
                break;
            case 67508:
                if (m_playSpell == SPELL_EXPLOSIV_AURA) good = true; else bad = true;
                break;
            case 67522:
                if (m_playSpell == SPELL_DRILL_AURA) good = true; else bad = true;
                break;
            }
            if (good || bad)
                if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                {
                    if (good)
                    {
                        me->PlayDirectSound(11595, player);
                        me->CastSpell(me, SPELL_POWER_CORRECT, true);
                        Talk(9, player);
                    }
                    else 
                    {
                        me->PlayDirectSound(11596, player);
                        me->CastSpell(me, SPELL_POWER_INCORRECT, true);
                        Talk(10, player);
                    }
                    Talk(12, player);
                    m_events.RescheduleEvent(EVENT_PLAYING, 1000);
                }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_PLAY:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        Talk(m_count, player);
                        Talk(12, player);
                    }
                    m_count += 1;
                    if (m_count < 4)
                        m_events.ScheduleEvent(EVENT_START_PLAY, 6000);
                    else
                    {
                        m_events.ScheduleEvent(EVENT_PLAYING, 6000);
                        m_events.RescheduleEvent(EVENT_MASTER_RESET, 60000);
                    }
                    break;
                }
                case EVENT_PLAYING:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        if (me->GetPower(POWER_MANA) < 100.0f)
                        {
                            m_playRol = urand(0, 4);
                            m_playSpell = SPELL_DRILL_AURA + m_playRol;
                            me->CastSpell(me, m_playSpell, true);
                            me->CastSpell(me, 67502), true;
                            me->AddAura(67502, player);
                            Talk(m_playRol + 4, player);
                            Talk(12, player);
                        }
                        else
                        {
                            Talk(11, player);
                            Talk(12, player);
                            player->CastSpell(player, SPELL_VAULT_CRACKED, true);
                            player->CastSpell(player, SPELL_VEHICLE_EXIT_SPELL, true);
                            m_events.ScheduleEvent(EVENT_PLAYER_EXIT, 2000);
                            player->ExitVehicle();
                            break;
                        }
                    m_events.ScheduleEvent(EVENT_CHECK_TIMEOUT, 2000);
                    break;
                }
                case EVENT_CHECK_TIMEOUT:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        if (player->HasAura(67502))
                            m_events.ScheduleEvent(EVENT_CHECK_TIMEOUT, 250);
                        else
                        {
                            me->PlayDirectSound(11596, player);
                            me->CastSpell(me, SPELL_POWER_INCORRECT, true);
                            m_events.ScheduleEvent(EVENT_PLAYING, 1000);
                        }
                    break;
                }
                case EVENT_MASTER_RESET:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        player->CastSpell(player, SPELL_VEHICLE_EXIT_SPELL, true);
                    // nobreak;
                }
                case EVENT_PLAYER_EXIT:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        player->ExitVehicle();
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
        return new npc_first_bank_of_kezan_vault_35486AI(creature);
    }
};

// 35200
class npc_pirate_party_crasher_35200 : public CreatureScript
{
public:
    npc_pirate_party_crasher_35200() : CreatureScript("npc_pirate_party_crasher_35200") { }

    struct npc_pirate_party_crasher_35200AI : public ScriptedAI
    {
        npc_pirate_party_crasher_35200AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        bool m_castCooldown;

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
            m_castCooldown = false;
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (!m_castCooldown)
            {
                m_castCooldown = true;
                m_events.ScheduleEvent(EVENT_CAST_COOLDOWN, urand(11000, 17800));
                me->CastSpell(attacker, 75361);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CAST_COOLDOWN:
                    m_castCooldown = false;
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
        return new npc_pirate_party_crasher_35200AI(creature);
    }
};

// 35202
class npc_kezan_partygoer_35202 : public CreatureScript
{
public:
    npc_kezan_partygoer_35202() : CreatureScript("npc_kezan_partygoer_35202") { }

    struct npc_kezan_partygoer_35202AI : public ScriptedAI
    {
        npc_kezan_partygoer_35202AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        bool m_castCooldown;

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (attacker->GetEntry() == 35200)
                me->SetReactState(REACT_AGGRESSIVE);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_kezan_partygoer_35202AI(creature);
    }
};

// 37598
class npc_gasbot_37598 : public CreatureScript
{
public:
    npc_gasbot_37598() : CreatureScript("npc_gasbot_37598") { }

    struct npc_gasbot_37598AI : public VehicleAI
    {
        npc_gasbot_37598AI(Creature* creature) : VehicleAI(creature) { }

        EventMap m_events;
        uint32   m_count;
        uint64   m_consoleGUID;

        void Reset() override
        {
            m_count = 0;
            m_consoleGUID = 0;
            me->SetWalk(true);
            if (GameObject* go = me->FindNearestGameObject(201736, 25.0f))
                m_consoleGUID = go->GetGUID();
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override
        {
            if (apply)
            {
               m_count += 1;
               if (m_count == 4)
                   m_events.ScheduleEvent(2000, 100);
            }         
        }

        void MovementInform(uint32 type, uint32 id) override 
        { 
            if (type == POINT_MOTION_TYPE)
                switch (id)
                {               
                case 2001:
                    m_events.ScheduleEvent(2001, 100);
                    break;
                case 2002:
                    m_events.ScheduleEvent(2002, 100);
                    break;
                case 2003:
                    m_events.ScheduleEvent(2003, 100);
                    break;
                case 2004:
                    me->DespawnOrUnsummon(10);
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
                case 2000:
                    me->CastSpell(me, 70256, true);
                    me->GetMotionMaster()->MovePoint(2001, -8424.21f, 1342.95f, 102.41f);
                    break;
                case 2001:
                    me->GetMotionMaster()->MovePoint(2002, -8424.27f, 1346.94f, 104.66f);
                    break;
                case 2002:
                    me->GetMotionMaster()->MovePoint(2003, -8423.88f, 1365.72f, 104.68f);
                    break;
                case 2003:
                    if (GameObject* go = ObjectAccessor::GetGameObject(*me, m_consoleGUID))
                        go->AI()->DoAction(998);
                    me->GetMotionMaster()->MovePoint(2004, -8412.07f, 1364.56f, 104.71f);
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
        return new npc_gasbot_37598AI(creature);
    }
};

// 201745
class go_447_fire_201745 : public GameObjectScript
{
public:
    go_447_fire_201745() : GameObjectScript("go_447_fire_201745") { }

    struct go_447_fire_201745AI : public GameObjectAI
    {
        go_447_fire_201745AI(GameObject* go) : GameObjectAI(go) { }

        EventMap m_events;

        void Reset() override
        {
            m_events.RescheduleEvent(EVENT_CHECK_FOR_PLAYER, 2500);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);
            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_FOR_PLAYER:
                {
                    bool fire = false;
                    std::list<Player*> pList = go->FindNearestPlayers(50.0f);
                    for (std::list<Player*>::iterator itr = pList.begin(); itr != pList.end(); ++itr)
                        if ((*itr)->GetQuestStatus(QUEST_SASSY_447) || (*itr)->GetQuestStatus(QUEST_LIFE_SAVINGS))
                            fire = true;

                    if (!fire)
                        go->Delete();
                    m_events.ScheduleEvent(EVENT_CHECK_FOR_PLAYER, 2500);
                    break;
                }
                }
            }
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_447_fire_201745AI(go);
    }
};

// 201736
class go_gasbot_control_panel_201736 : public GameObjectScript
{
public:
    go_gasbot_control_panel_201736() : GameObjectScript("go_gasbot_control_panel_201736") { }

    struct go_gasbot_control_panel_201736AI : public GameObjectAI
    {
        go_gasbot_control_panel_201736AI(GameObject* go) : GameObjectAI(go) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_glitterGUID;

        void Reset() override
        {
            m_playerGUID = 0;
            m_glitterGUID = 0;
        }

        bool GossipHello(Player* player) override
        {
            if (m_playerGUID == player->GetGUID())
                if (GameObject* con = sObjectAccessor->GetGameObject(*go, m_glitterGUID))
                {
                    con->RemoveFromWorld();
                    m_glitterGUID = 0;
                }
                else if (GameObject* con = go->FindNearestGameObject(202850, 2.0f))
                    con->RemoveFromWorld();

            return false;
        }

        void SetGUID(uint64 guid, int32 id = 0)
        {
            switch (id)
            {
            case PLAYER_GUID:
                m_playerGUID = guid;
                break;
            case 202850:
                m_glitterGUID = guid;
                break;
            }
        }

        void DoAction(int32 param = 0) 
        { 
            if (param == 998)
                SpawnAllFireBunnys();
        }

        void SpawnAllFireBunnys()
        {
            go->SummonGameObject(201745, -8406.05f, 1363.66f, 117.270f, 0, 0, 0, 0, 0, 0);
            go->SummonGameObject(201745, -8424.22f, 1352.51f, 131.307f, 0, 0, 0, 0, 0, 0);
            go->SummonGameObject(201745, -8405.66f, 1362.58f, 129.059f, 0, 0, 0, 0, 0, 0);
            go->SummonGameObject(201745, -8425.50f, 1372.17f, 114.000f, 0, 0, 0, 0, 0, 0);
            go->SummonGameObject(201745, -8423.73f, 1359.31f, 117.705f, 0, 0, 0, 0, 0, 0);
            go->SummonGameObject(201745, -8407.38f, 1364.28f, 104.021f, 0, 0, 0, 0, 0, 0);
            go->SummonGameObject(201745, -8434.33f, 1357.26f, 112.397f, 0, 0, 0, 0, 0, 0);
            go->SummonGameObject(201745, -8423.97f, 1365.49f, 104.676f, 0, 0, 0, 0, 0, 0);
            go->SummonGameObject(201745, -8423.71f, 1374.99f, 125.630f, 0, 0, 0, 0, 0, 0);
            go->SummonGameObject(201745, -8425.45f, 1348.56f, 114.783f, 0, 0, 0, 0, 0, 0);
            go->SummonGameObject(201745, -8431.05f, 1356.36f, 133.902f, 0, 0, 0, 0, 0, 0);
            go->SummonGameObject(201745, -8424.32f, 1350.47f, 104.663f, 0, 0, 0, 0, 0, 0);
            go->SummonGameObject(201745, -8399.95f, 1364.21f, 124.004f, 0, 0, 0, 0, 0, 0);
            go->SummonGameObject(201745, -8435.67f, 1355.82f, 104.663f, 0, 0, 0, 0, 0, 0);
            go->SummonGameObject(201745, -8417.77f, 1374.51f, 134.562f, 0, 0, 0, 0, 0, 0);
            go->SummonGameObject(201745, -8410.71f, 1352.56f, 108.080f, 0, 0, 0, 0, 0, 0);
            go->SummonGameObject(201745, -8427.00f, 1377.48f, 148.793f, 0, 0, 0, 0, 0, 0);
            go->SummonGameObject(201745, -8404.12f, 1374.84f, 108.255f, 0, 0, 0, 0, 0, 0);
            go->SummonGameObject(201745, -8417.58f, 1356.24f, 134.550f, 0, 0, 0, 0, 0, 0);
            go->SummonGameObject(201745, -8428.97f, 1380.37f, 112.364f, 0, 0, 0, 0, 0, 0);
            go->SummonGameObject(201745, -8424.03f, 1358.39f, 125.108f, 0, 0, 0, 0, 0, 0);
            go->SummonGameObject(201745, -8419.53f, 1364.07f, 116.869f, 0, 0, 0, 0, 0, 0);
            go->SummonGameObject(201745, -8423.84f, 1376.50f, 130.335f, 0, 0, 0, 0, 0, 0);
            
            std::list<Player*> pList = go->FindNearestPlayers(50.0f);
            for (std::list<Player*>::iterator itr = pList.begin(); itr != pList.end(); ++itr)
                if ((*itr)->GetQuestStatus(QUEST_SASSY_447) == QUEST_STATUS_COMPLETE)
                    (*itr)->AddAura(SPELL_INVISIBILITY_DETECTION_1, (*itr));
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_gasbot_control_panel_201736AI(go);
    }
};

// 201734
class go_flammable_bed_201734 : public GameObjectScript
{
public:
    go_flammable_bed_201734() : GameObjectScript("go_flammable_bed_201734") { }

    struct go_flammable_bed_201734AI : public GameObjectAI
    {
        go_flammable_bed_201734AI(GameObject* go) : GameObjectAI(go) { }

        EventMap m_events;

        void OnStateChanged(uint32 state, Unit* unit)
        {
            if (state == GO_STATE_ACTIVE_ALTERNATIVE)
                if (Player* player = unit->ToPlayer())
                    if (GameObject* con = go->FindNearestGameObject(201736, 50.0f))
                        if (GameObject* glitter = con->SummonGameObject(202850, con->GetPositionX(), con->GetPositionY(), con->GetPositionZ(), con->GetOrientation(), 0, 0, 0, 0, 300000))
                        {
                            con->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
                            con->AI()->SetGUID(glitter->GetGUID(), glitter->GetEntry());
                        }
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_flammable_bed_201734AI(go);
    }
};

// 37676
class npc_hot_rod_37676 : public CreatureScript
{
public:
    npc_hot_rod_37676() : CreatureScript("npc_hot_rod_37676") { }

    enum eNpc
    {
        SPELL_SASSYS_DRIVING = 66724,
        SPELL_HAND_OVER_THE_KEYS = 70318,
        SPELL_KNOCKBACK_TRIGGER = 70329,
        PATH_WAYPOINT_HOT_ROD = 37676,
    };

    struct npc_hot_rod_37676AI : public VehicleAI
    {
        npc_hot_rod_37676AI(Creature* creature) : VehicleAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_sassyGUID;

        void Reset() override
        {
            m_playerGUID = 0;
            m_sassyGUID = 0;
            me->SetSpeed(MOVE_RUN, 2.4f);
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override
        {
            if (apply)
            {
                if (Player* player = passenger->ToPlayer())
                {
                    m_playerGUID = passenger->GetGUID();
                    player->CastSpell(me, SPELL_SASSYS_DRIVING, true);          // player receive aura, player cast to car, hit player and car..
                    player->CastSpell(player, SPELL_HAND_OVER_THE_KEYS, true);  // player cast to self
                    player->CastSpell(me, SPELL_KNOCKBACK_TRIGGER, true);       // player receive aura, player cast to self
                }
                else if (Creature* npc = passenger->ToCreature())
                    if (npc->GetEntry() == 37680)
                        m_sassyGUID = npc->GetGUID();

                if (m_playerGUID && m_sassyGUID)
                    me->GetMotionMaster()->MovePath(PATH_WAYPOINT_HOT_ROD, false);
            }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == WAYPOINT_MOTION_TYPE)
                switch (id)
                {
                case 30:
                    me->RemoveAura(SPELL_KNOCKBACK_TRIGGER);
                    break;
                case 31:
                    me->SetSpeed(MOVE_FLIGHT, 6.0f);
                    me->SetCanFly(true);
                    me->SetDisableGravity(true);
                    break;
                case 32:
                    m_events.ScheduleEvent(EVENT_TALK_PART_00, 2000);
                    break;
                case 34:
                    m_events.ScheduleEvent(EVENT_TALK_PART_01, 3500);
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
                case EVENT_TALK_PART_00:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        if (Creature* sassy = ObjectAccessor::GetCreature(*me, m_sassyGUID))
                            sassy->AI()->Talk(2, player);
                    break;
                }
                case EVENT_TALK_PART_01:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        if (player->getGender() == GENDER_MALE)
                        {
                            if (Creature* candy = me->FindNearestCreature(NPC_CANDY_CANE, 25.0f))
                                candy->AI()->Talk(2, player);
                        }
                        else
                            if (Creature* chip = me->FindNearestCreature(NPC_CHIP_ENDALE, 25.0f))
                                chip->AI()->Talk(2, player);

                    me->DespawnOrUnsummon(1000);
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_hot_rod_37676AI(creature);
    }
};

// 70330
class spell_knock_back_70330 : public SpellScriptLoader
{
public:
    spell_knock_back_70330() : SpellScriptLoader("spell_knock_back_70330") { }

    class IsNotInEntryList
    {
    public:
        explicit IsNotInEntryList(std::list<uint32>entrys) : _entrys(entrys) { }

        bool operator()(WorldObject* obj) const
        {
            if (Creature* target = obj->ToCreature())
                for (std::list<uint32>::const_iterator itr = _entrys.begin(); itr != _entrys.end(); ++itr)
                    if (target->GetEntry() == *itr)
                        return false;

            return true;
        }

    private:
        std::list<uint32> _entrys;
    };

    class TargetNotInRangeCheck
    {
    public:
        explicit TargetNotInRangeCheck(Unit* _caster) : caster(_caster) { }

        bool operator() (WorldObject* unit)
        {
            Position pos = caster->GetPosition();
            if (unit->GetPosition().GetExactDist(&pos) < 5.0f)
                return false;

            return true;
        }
        Unit* caster;
    };

    class spell_knock_back_70330_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_knock_back_70330_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            std::list<uint32>entrys;
            entrys.push_back(NPC_HOT_ROD_34840); // wrong.. shold only be: 37676
            entrys.push_back(NPC_HIRED_LOOTER_35234);
            entrys.push_back(NPC_KEZAN_CITIZEN_35063);
            entrys.push_back(NPC_KEZAN_CITIZEN_35075);
            targets.remove_if(IsNotInEntryList(entrys));
            targets.remove_if(TargetNotInRangeCheck(GetCaster()));
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_knock_back_70330_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_CONE_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_knock_back_70330_SpellScript();
    }
};

// 35222
class npc_trade_prince_gallywix_35222 : public CreatureScript
{
public:
    npc_trade_prince_gallywix_35222() : CreatureScript("npc_trade_prince_gallywix_35222") { }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/) override 
    {
        switch (quest->GetQuestId())
        {
        case QUEST_LIFE_SAVINGS:
            // player->CastSpell(player, 91847, true); video 22 is not avaible
            WorldLocation wloc(648, 534.835f, 3272.92f, 0.171872f, 0);
            player->TeleportTo(wloc);
            player->SetHomebind(wloc, 4721);
            player->SaveToDB();
            break;
        }
        return false;     
    }
};


void AddSC_zone_kezan()
{
    new npc_fizz_lighter_34689();
    new npc_evol_fingers_34696();
    new npc_sally_salvager_sandscrew_37761();
    new npc_brett_coins_mcquid_37762();
    new npc_injured_employee_48305();
    new npc_kaja_cola_balloon_37804();
    new npc_sassy_hardwrench_34668();
    new npc_foreman_dampwick_34872();
    new npc_sister_goldskimmer_34692();
    new npc_bamm_megabomb_34673();
    new npc_megs_dreadshredder_34874();
    new npc_candy_cane_35053();
    new npc_chip_endale_35054();
    new npc_hobart_grapplehammer_48494();
    new npc_subject_nine_49150();
    new spell_kaja_cola_70478();
    new npc_brute_enforcer_35304();
    new at_kezan_ace_5497();
    new at_kezan_gobber_5498();
    new at_kezan_izzy_5499();
    new npc_hot_rod_34840();
    new npc_ace_34957();
    new npc_gobber_34958();
    new npc_izzy_34959();
    new npc_fbok_bank_teller_35120();
    new go_disco_ball_201591();
    new npc_tunneling_worm_34865();
    new npc_warrior_matic_nx__34697();
    new npc_bruno_flameretardant_34835();
    new npc_frankie_gearslipper_34876();
    new npc_jack_the_hammer_34877();
    new npc_sudsy_magee_34878();
    new npc_coach_crosscheck_37106();
    new npc_bilgewater_buccaneer_48526();
    new npc_bilgewater_buccaneer_37179();
    new npc_steamwheedle_shark_37114();
    new npc_bilgewater_buccaneer_37213();
    new npc_fourth_and_goal_target_37203();
    new spell_kick_footbomb_70052();
    new npc_deathwing_48572();
    new npc_elm_general_purpose_bunny_large_24110();
    new go_kajamite_deposit_195488();
    new npc_kezan_partygoer_35175_86();
    new npc_hired_looter_35234();
    new npc_kezan_citizen_35063();
    new npc_first_bank_of_kezan_vault_35486();
    new npc_pirate_party_crasher_35200();
    new npc_kezan_partygoer_35202();
    new npc_gasbot_37598();
    new go_447_fire_201745();
    new go_gasbot_control_panel_201736();
    new go_flammable_bed_201734();
    new npc_hot_rod_37676();
    new spell_knock_back_70330();
    new npc_trade_prince_gallywix_35222();
}

