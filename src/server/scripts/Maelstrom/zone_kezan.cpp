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
    QUEST_MEGS_IN_MARKETING = 28349,
    QUEST_THE_REPLACEMENTS = 24488,
    QUEST_NECCASSARY_ROUGHNESS = 24502,
    NPC_HOT_ROD_34840 = 34840,
    NPC_ACE_34957 = 34957,
    NPC_GOBBER_34958 = 34958,
    NPC_IZZY_34959 = 34959,
    NPC_KEZAN_CITIZEN_35063 = 35063,
    NPC_KEZAN_CITIZEN_35075 = 35075,
    NPC_BRUNO_FLAMERETARDANT = 34835,
    NPC_FRANKIE_GEARSLIPPER = 34876,
    NPC_JACK_THE_HAMMER = 34877,
    NPC_SUDSY_MAGEE = 34878,
    NPC_STEAMWHEEDLE_SHARK = 37114,
    NPC_BILGEWATER_BUCCANEER = 37179,
    NPC_NECESSARY_ROUGHNESS_KILL_CREDIT = 48271,
    SPELL_BORE_32738 = 32738,
    SPELL_PERMANENT_FEIGN_DEATH = 29266,
    PLAYER_GUID = 99991,
    ACTION_ENTER_CAR = 101,
    ACTION_HELP_PLAYER,
    ACTION_STOP_HELP_PLAYER,
    EVENT_ENTER_CAR,
    EVENT_TALK_PERIODIC,
    EVENT_GIVE_UP,
    EVENT_COMBAT_STOP,
    EVENT_RESET_TARGET,
    EVENT_OWNER_IS_ATTACKED,
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
        EVENT_SPELLCAST = 1,
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
        EVENT_SPELLCAST = 1,
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

// 37804
class npc_kaja_cola_balloon_37804 : public CreatureScript
{
public:
    npc_kaja_cola_balloon_37804() : CreatureScript("npc_kaja_cola_balloon_37804") { }

    enum eNPC
    {
        EVENTS_BALLON_MESSAGE = 201,
    };

    struct npc_kaja_cola_balloon_37804AI : public ScriptedAI
    {
        npc_kaja_cola_balloon_37804AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset() override
        {
            m_events.ScheduleEvent(EVENTS_BALLON_MESSAGE, 10000);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENTS_BALLON_MESSAGE:
                {
                    Talk(0);
                    m_events.ScheduleEvent(EVENTS_BALLON_MESSAGE, urand(30000, 45000));
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

    enum eNPC
    {
        QUEST_KAJA_COLA
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_TAKING_CARE_OF_BUSINESS)
            creature->AI()->Talk(0, player);
        else if (quest->GetQuestId() == QUEST_ROLLING_WITH_MY_HOMIES)
            creature->AI()->Talk(1, player);
        else if (quest->GetQuestId() == QUEST_LIFE_SAVINGS)
            creature->AI()->Talk(2, player);
        return false;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        if (quest->GetQuestId() == QUEST_TAKING_CARE_OF_BUSINESS)
            creature->AI()->Talk(3, player);

        return false;
    }

    struct npc_sassy_hardwrench_34668AI : public ScriptedAI
    {
        npc_sassy_hardwrench_34668AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

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

        ACTION_DELIVER_BUMM_PACKET = 201,
        EVENT_START_ANIM_BUMM_PACKET,
        EVENT_MASTER_RESET,
        EVENT_PACKET_EXPLODE,
        EVENT_SAY_OUTCH,
        EVENT_SAY_HAVE_UNDERSTAND,
    };

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        if (quest->GetQuestId() == QUEST_TAKING_CARE_OF_BUSINESS)
            creature->GetAI()->DoAction(ACTION_DELIVER_BUMM_PACKET);

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
        }

        void DoAction(int32 param) override
        {
            if (!m_anim_is_started)
                if (param == ACTION_DELIVER_BUMM_PACKET)
                {
                    m_events.ScheduleEvent(EVENT_START_ANIM_BUMM_PACKET, 500);
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
                case EVENT_START_ANIM_BUMM_PACKET:
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
                    m_events.RescheduleEvent(EVENT_MASTER_RESET, 5000);
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
        EVENTS_TALK_COOLDOWN = 201,
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
                        m_events.ScheduleEvent(EVENTS_TALK_COOLDOWN, 6000);
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
                case EVENTS_TALK_COOLDOWN:
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
        EVENT_SHOOT_ON_DUMMY = 201,
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

    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_ROLLING_WITH_MY_HOMIES)
            player->ToUnit()->Talk(BROADCASTTEXT_USE_KEY_FOR_HOT_RED, CHAT_MSG_RAID_BOSS_WHISPER, 25.0f, player);
        return false;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        if (quest->GetQuestId() == QUEST_MEGS_IN_MARKETING)
            creature->AI()->Talk(0, player);

        return false;
    }
};

// 35053
class npc_candy_cane_35053 : public CreatureScript
{
public:
    npc_candy_cane_35053() : CreatureScript("npc_candy_cane_35053") { }

    enum eNPC
    {
    };

    struct npc_candy_cane_35053AI : public ScriptedAI
    {
        npc_candy_cane_35053AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

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
        return new npc_candy_cane_35053AI(creature);
    }
};

// 48494
class npc_hobart_grapplehammer_48494 : public CreatureScript
{
public:
    npc_hobart_grapplehammer_48494() : CreatureScript("npc_hobart_grapplehammer_48494") { }

    enum eNPC
    {
    };

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
                switch (eventId)
                {
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
        return new npc_hobart_grapplehammer_48494AI(creature);
    }
};

// 49150
class npc_subject_nine_49150 : public CreatureScript
{
public:
    npc_subject_nine_49150() : CreatureScript("npc_subject_nine_49150") { }

    enum eNPC
    {
        SPELL_GIZMO_HELMET = 91603,

        EVENT_ANIM_SUBJECT_NINE = 201,
    };

    struct npc_subject_nine_49150AI : public ScriptedAI
    {
        npc_subject_nine_49150AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset() override
        {
            m_events.ScheduleEvent(EVENT_ANIM_SUBJECT_NINE, 10000);
            if (!me->HasAura(SPELL_GIZMO_HELMET))
                me->CastSpell(me, SPELL_GIZMO_HELMET, true);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_ANIM_SUBJECT_NINE:
                {
                    me->SendPlaySound(18178, false);
                    me->HandleEmoteCommand(RAND(33, 35, 377));
                    m_events.ScheduleEvent(EVENT_ANIM_SUBJECT_NINE, urand(15000, 18000));
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

    enum eNPC
    {
        EVENTS_TALK_COOLDOWN = 201,
    };

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
                            m_events.ScheduleEvent(EVENTS_TALK_COOLDOWN, urand(10000, 15000));
                        }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENTS_TALK_COOLDOWN:
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
class npc_rod_hot_34840 : public CreatureScript
{
public:
    npc_rod_hot_34840() : CreatureScript("npc_rod_hot_34840") { }

    enum eNPC
    {
        SPELL_RESUMMON_IZZY = 66646,
        SPELL_RESUMMON_GOBBER = 66645,
        SPELL_RESUMMON_ACE = 66644,
        EVENT_IZZY_ENTER_THE_CAR = 901,
        EVENT_GOBBER_ENTER_THE_CAR,
        EVENT_ACE_ENTER_THE_CAR,
        EVENT_GOBBER_COOLDOWN,
    };

    struct npc_rod_hot_34840AI : public VehicleAI
    {
        npc_rod_hot_34840AI(Creature* creature) : VehicleAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_izzyGUID;
        uint64   m_gobberGUID;
        uint64   m_aceGUID;
        bool     m_gobberEmoteCD;

        void Reset() override
        {
            m_playerGUID = 0;
            m_izzyGUID = 0;
            m_gobberGUID = 0;
            m_aceGUID = 0;
            m_gobberEmoteCD = false;
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
                    if (!m_izzyGUID)
                        if (npc->GetEntry() == NPC_IZZY_34959)
                            m_izzyGUID = npc->GetGUID();
                    if (!m_gobberGUID)
                        if (npc->GetEntry() == NPC_GOBBER_34958)
                            m_gobberGUID = npc->GetGUID();
                    if (!m_aceGUID)
                        if (npc->GetEntry() == NPC_ACE_34957)
                            m_aceGUID = npc->GetGUID();
                }
            }
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (!m_gobberEmoteCD)
                if (Vehicle* vehicle = me->GetVehicleKit())
                    if (Unit* gobber = vehicle->GetPassenger(2))
                        if (who->GetEntry() == NPC_KEZAN_CITIZEN_35063 || who->GetEntry() == NPC_KEZAN_CITIZEN_35075)
                            if (who->GetDistance2d(me) < 15.0f)
                                if (urand(0, 100) < 25)
                                {
                                    gobber->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
                                    m_gobberEmoteCD = true;
                                    m_events.ScheduleEvent(EVENT_GOBBER_COOLDOWN, 5000);
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
                case EVENT_GOBBER_COOLDOWN:
                {
                    m_gobberEmoteCD = false;
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
        return new npc_rod_hot_34840AI(creature);
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
        bool     m_IsAttackingTarget;

        void Initialize()
        {
            m_playerGUID = 0;
            m_hotrodGUID = 0;
            m_targetGUID = 0;
            m_IsAttackingTarget = false;
            me->SetOrientation(6.265732f);
        }

        void Reset() override
        {
            m_targetGUID = 0;
            m_IsAttackingTarget = false;
            me->setFaction(2204);
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
            case ACTION_HELP_PLAYER:
                if (!m_IsAttackingTarget)
                    m_events.ScheduleEvent(EVENT_OWNER_IS_ATTACKED, 100);
                break;
            case ACTION_STOP_HELP_PLAYER:
                me->AttackStop();
                me->GetMotionMaster()->MoveIdle();
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
                case EVENT_OWNER_IS_ATTACKED:
                {
                    if (Creature* target = ObjectAccessor::GetCreature(*me, m_targetGUID))
                    {
                        m_IsAttackingTarget = true;
                        me->SetReactState(REACT_AGGRESSIVE); //            
                        AttackStart(target);
                        me->GetMotionMaster()->MoveChase(target, 3.0f);
                    }
                    if (uint32 rol = urand(0, 100) < 60)
                        Talk(1, me->GetOwner());
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
        bool     m_IsAttackingTarget;

        void Initialize()
        {
            m_playerGUID = 0;
            m_hotrodGUID = 0;
            m_targetGUID = 0;
            m_IsAttackingTarget = false;
            me->SetOrientation(4.120008f);
        }

        void Reset() override
        {
            m_targetGUID = 0;
            m_IsAttackingTarget = false;
            me->setFaction(2204);
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
            case ACTION_HELP_PLAYER:
                if (!m_IsAttackingTarget)
                    m_events.ScheduleEvent(EVENT_OWNER_IS_ATTACKED, 100);
                break;
            case ACTION_STOP_HELP_PLAYER:
                me->AttackStop();
                me->GetMotionMaster()->MoveIdle();
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
                case EVENT_ENTER_CAR:
                {
                    if (Creature* car = ObjectAccessor::GetCreature(*me, m_hotrodGUID))
                        if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                            if (Vehicle* hotrod = car->GetVehicleKit())
                                if (!hotrod->HasEmptySeat(0))    // player is passenger
                                    if (hotrod->HasEmptySeat(2)) // my seat is free
                                       me->EnterVehicle(car, 2); //  hotrod->AddPassenger(me, 2);
                }
                case EVENT_OWNER_IS_ATTACKED:
                {
                    if (Creature* target = ObjectAccessor::GetCreature(*me, m_targetGUID))
                    {
                        m_IsAttackingTarget = true;
                        me->SetReactState(REACT_AGGRESSIVE); //            
                        AttackStart(target);
                        me->GetMotionMaster()->MoveChase(target, 3.0f);
                    }
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
        bool     m_IsAttackingTarget;

        void Initialize()
        {
            m_playerGUID = 0;
            m_hotrodGUID = 0;
            m_targetGUID = 0;
            m_IsAttackingTarget = false;
            me->SetOrientation(3.819579f);
        }

        void Reset() override
        {
            m_targetGUID = 0;
            m_IsAttackingTarget = false;
            me->setFaction(2204);
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
            case ACTION_HELP_PLAYER:
                if (!m_IsAttackingTarget)
                    m_events.ScheduleEvent(EVENT_OWNER_IS_ATTACKED, 100);
                break;
            case ACTION_STOP_HELP_PLAYER:
                me->AttackStop();
                me->GetMotionMaster()->MoveIdle();
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
                case EVENT_ENTER_CAR:
                {
                    if (Creature* car = ObjectAccessor::GetCreature(*me, m_hotrodGUID))
                        if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                            if (Vehicle* hotrod = car->GetVehicleKit())
                                if (!hotrod->HasEmptySeat(0))    // player is passenger
                                    if (hotrod->HasEmptySeat(1)) // my seat is free
                                        me->EnterVehicle(car, 1); //hotrod->AddPassenger(me, 1);
                }
                case EVENT_OWNER_IS_ATTACKED:
                {
                    if (Creature* target = ObjectAccessor::GetCreature(*me, m_targetGUID))
                    {
                        m_IsAttackingTarget = true;
                        me->SetReactState(REACT_AGGRESSIVE); //            
                        AttackStart(target);
                        me->GetMotionMaster()->MoveChase(target, 3.0f);
                    }
                    if (uint32 rol = urand(0, 100) < 60)
                        Talk(1, me->GetOwner());
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
        std::list<uint64> tList;
        uint64   m_playerGUID;
        bool     m_give_up;

        void Initialize() 
        {
            tList.clear();
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
            tList.clear();
            if (Player* player = victim->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                Talk(0, player);
                m_events.ScheduleEvent(EVENT_TALK_PERIODIC, 5000);
                if (!player->m_Controlled.empty())
                    for (auto minion : player->m_Controlled)
                    {
                        tList.push_back(minion->GetGUID());
                        minion->GetAI()->SetGUID(me->GetGUID(), me->GetEntry());
                        minion->GetAI()->DoAction(ACTION_HELP_PLAYER);
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
                            if (!player->m_Controlled.empty())
                                for (auto minion : player->m_Controlled)
                                    minion->GetAI()->DoAction(ACTION_STOP_HELP_PLAYER);
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
        std::list<uint64> tList;
        uint64   m_playerGUID;
        bool     m_give_up;

        void Initialize()
        {
            tList.clear();
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
            tList.clear();
            if (Player* player = victim->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                Talk(0, player);
                m_events.ScheduleEvent(EVENT_TALK_PERIODIC, 5000);
                if (!player->m_Controlled.empty())
                    for (auto minion : player->m_Controlled)
                    {
                        tList.push_back(minion->GetGUID());
                        minion->GetAI()->SetGUID(me->GetGUID(), me->GetEntry());
                        minion->GetAI()->DoAction(ACTION_HELP_PLAYER);
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
                            if (!player->m_Controlled.empty())
                                for (auto minion : player->m_Controlled)
                                    minion->GetAI()->DoAction(ACTION_STOP_HELP_PLAYER);
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
        std::list<uint64> tList;
        uint64   m_playerGUID;
        bool     m_give_up;

        void Initialize()
        {
            tList.clear();
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
            tList.clear();
            if (Player* player = victim->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                Talk(0, player);
                m_events.ScheduleEvent(EVENT_TALK_PERIODIC, 5000);
                if (!player->m_Controlled.empty())
                    for (auto minion : player->m_Controlled)
                    {
                        tList.push_back(minion->GetGUID());
                        minion->GetAI()->SetGUID(me->GetGUID(), me->GetEntry());
                        minion->GetAI()->DoAction(ACTION_HELP_PLAYER);
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
                            if (!player->m_Controlled.empty())
                                for (auto minion : player->m_Controlled)
                                    minion->GetAI()->DoAction(ACTION_STOP_HELP_PLAYER);
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
        std::list<uint64> tList;
        uint64   m_playerGUID;
        bool     m_give_up;

        void Initialize()
        {
            tList.clear();
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
            tList.clear();
            if (Player* player = victim->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                Talk(0, player);
                m_events.ScheduleEvent(EVENT_TALK_PERIODIC, 5000);
                if (!player->m_Controlled.empty())
                    for (auto minion : player->m_Controlled)
                    {
                        tList.push_back(minion->GetGUID());
                        minion->GetAI()->SetGUID(me->GetGUID(), me->GetEntry());
                        minion->GetAI()->DoAction(ACTION_HELP_PLAYER);
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
                            if (!player->m_Controlled.empty())
                                for (auto minion : player->m_Controlled)
                                    minion->GetAI()->DoAction(ACTION_STOP_HELP_PLAYER);
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

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
       if (quest->GetQuestId() == QUEST_THE_REPLACEMENTS)
           creature->AI()->Talk(0, player);
       else if (quest->GetQuestId() == QUEST_NECCASSARY_ROUGHNESS)
           creature->AI()->Talk(1, player);
        return false;
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
        EVENT_PLAY_SOUND = 901,
        EVENT_START_PLAY_GAME,
        EVENT_OBSERVER_CHEERING,
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
        }

        void JustSummoned(Creature* summon) override
        {
            if (summon->GetEntry() == NPC_STEAMWHEEDLE_SHARK)
            {
                sList.push_back(summon->GetGUID());
                summon->AI()->SetGUID(m_playerGUID, PLAYER_GUID);
            }
        }

        void PassengerBoarded(Unit* unit, int8 /*seat*/, bool apply) override
        {
            if (apply)
            {
                if (Player* player = unit->ToPlayer())
                {
                    m_playerGUID = player->GetGUID();
                    player->KilledMonsterCredit(NPC_NECESSARY_ROUGHNESS_KILL_CREDIT);
                    m_events.ScheduleEvent(EVENT_PLAY_SOUND, 1000);
                    m_events.ScheduleEvent(EVENT_START_PLAY_GAME, 4000);
                    m_events.ScheduleEvent(EVENT_OBSERVER_CHEERING, 250);
                }
            }
            else
            {
                StopPlayGame();
            }
        }

        void MoveInLineOfSight_Safe(Unit* who)
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
                case EVENT_PLAY_SOUND:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        player->PlayDirectSound(17466, player);
                        m_events.ScheduleEvent(EVENT_PLAY_SOUND, 1000);
                    }
                    break;
                }
                case EVENT_START_PLAY_GAME:
                {
                    StartPlayGame();
                    break;
                }
                case EVENT_OBSERVER_CHEERING:
                {
                    for (uint32 i = 0; i < urand(3, 10); i++)
                        if (Creature* npc = GetRandomObserver())
                            npc->HandleEmoteCommand(GetRandomEmote());

                    m_events.ScheduleEvent(EVENT_OBSERVER_CHEERING, 500);
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

    enum eNpc
    {
        EVENT_WE_ARE_KILLED = 901,
    };

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



void AddSC_zone_kezan()
{
    new npc_fizz_lighter_34689();
    new npc_evol_fingers_34696();
    new npc_kaja_cola_balloon_37804();
    new npc_sassy_hardwrench_34668();
    new npc_foreman_dampwick_34872();
    new npc_sister_goldskimmer_34692();
    new npc_bamm_megabomb_34673();
    new npc_megs_dreadshredder_34874();
    new npc_candy_cane_35053();
    new npc_hobart_grapplehammer_48494();
    new npc_subject_nine_49150();
    new spell_kaja_cola_70478();
    new npc_brute_enforcer_35304();
    new at_kezan_ace_5497();
    new at_kezan_gobber_5498();
    new at_kezan_izzy_5499();
    new npc_rod_hot_34840();
    new npc_ace_34957();
    new npc_gobber_34958();
    new npc_izzy_34959();
    new go_disco_ball_201591();
    new npc_tunneling_worm_34865();
    new npc_warrior_matic_nx__34697();
    new npc_bruno_flameretardant_34835();
    new npc_frankie_gearslipper_34876();
    new npc_jack_the_hammer_34877();
    new npc_sudsy_magee_34878();
    new npc_coach_crosscheck_37106();
    new npc_bilgewater_buccaneer_37179();
    new npc_steamwheedle_shark_37114();
}

