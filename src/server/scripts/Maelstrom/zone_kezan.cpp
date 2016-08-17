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
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "SpellMgr.h"

enum eKezanEnumerate
{
    QUEST_TAKING_CARE_OF_BUSINESS = 14138,
    QUEST_GOOD_HELP_IS_HARD_TO_FIND = 14069,
    QUEST_TROUBLE_IN_THE_MINES = 14075,
    QUEST_KAJA_COLA = 25473,
    QUEST_ROLLING_WITH_MY_HOMIES = 14071,
    QUEST_LIFE_SAVINGS = 14126,
};

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
        void SpellHit(Unit* /*caster*/, SpellInfo const* /*spell*/) override
        {
            if (urand(0, 100) < 5)
                Talk(1);
            m_events.RescheduleEvent(EVENT_SPELLCAST, 3000);
        }

        // Called when spell hits a target
        void SpellHitTarget(Unit* /*target*/, SpellInfo const* spell) override
        {
            if (spell->Id == SPELL_FIREBALL)
                if (urand(0, 100) < 5)
                    Talk(0);
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
        void SpellHit(Unit* /*caster*/, SpellInfo const* /*spell*/) override
        {
            if (urand(0, 100) < 5)
                Talk(0);
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
            creature->AI()->Talk(0);
        else if (quest->GetQuestId() == QUEST_ROLLING_WITH_MY_HOMIES)
            creature->AI()->Talk(1);
        else if (quest->GetQuestId() == QUEST_LIFE_SAVINGS)
            creature->AI()->Talk(2);
        return false;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        if (quest->GetQuestId() == QUEST_TAKING_CARE_OF_BUSINESS)
            creature->AI()->Talk(3);

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
            creature->AI()->Talk(5);

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
                        Talk(0);
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
                            Talk(0);
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



void AddSC_zone_kezan()
{
    new npc_fizz_lighter_34689();
    new npc_evol_fingers_34696();
    new npc_kaja_cola_balloon_37804();
    new npc_sassy_hardwrench_34668();
    new npc_foreman_dampwick_34872();
    new npc_sister_goldskimmer_34692();
    new npc_candy_cane_35053();
    new npc_hobart_grapplehammer_48494();
    new npc_subject_nine_49150();
    new spell_kaja_cola_70478();
    new npc_brute_enforcer_35304();
}

