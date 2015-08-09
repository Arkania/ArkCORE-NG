/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
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
#include "blackrock_caverns.h"


enum actions
{
    ACTION_BEAUTY_BERSEK,
};

enum Spells
{
    SPELL_BERSEK = 82395,
    SPELL_CHARGE = 76030,
    SPELL_FLAMEBREAK = 76032,
    SPELL_MAGMA_SPIT = 76031,
    SPELL_TERRIFYNG_ROAR = 76028,
};

enum events
{
    EVENT_NONE,
    EVENT_BERSEK,
    EVENT_BERSEKER_CHARGE,
    EVENT_FLAMEBREAK,
    EVENT_MAGMA_SPIT,
    EVENT_TERRIFYNG_ROAR,
};

// 39700
class boss_beauty : public CreatureScript
{
public:
    boss_beauty() : CreatureScript("boss_beauty") { }

    struct boss_beautyAI : public BossAI
    {
        boss_beautyAI(Creature* creature) : BossAI(creature, DATA_BEAUTY_EVENT)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset() override
        {
            events.Reset();
        }

        void EnterCombat(Unit* who) override
        {
            events.ScheduleEvent(EVENT_BERSEKER_CHARGE, urand(15000, 24000), 0, 0);
            events.ScheduleEvent(EVENT_FLAMEBREAK, urand(10000, 21000), 0, 0);
            events.ScheduleEvent(EVENT_MAGMA_SPIT, urand(9000, 13000), 0, 0);
            events.ScheduleEvent(EVENT_TERRIFYNG_ROAR, urand(15000, 22000), 0, 0);
        }

        void DoAction(int32 action) override
        {
            switch (action)
            {
            case ACTION_BEAUTY_BERSEK:
                events.ScheduleEvent(EVENT_BERSEK, 1000, 0, 0);
                break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_BERSEKER_CHARGE:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                    {
                        me->CastSpell(target, SPELL_CHARGE, true);
                        events.ScheduleEvent(EVENT_BERSEKER_CHARGE, urand(12000, 20000), 0, 0);
                    }
                    break;
                case EVENT_FLAMEBREAK:
                    DoCastAOE(SPELL_FLAMEBREAK);
                    events.ScheduleEvent(EVENT_FLAMEBREAK, urand(5000, 9000), 0, 0);
                    break;
                case EVENT_MAGMA_SPIT:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                    {
                        me->CastSpell(target, SPELL_MAGMA_SPIT, true);
                        events.ScheduleEvent(EVENT_MAGMA_SPIT, urand(9000, 13000), 0, 0);
                    }
                    break;
                case SPELL_TERRIFYNG_ROAR:
                    DoCastAOE(SPELL_TERRIFYNG_ROAR);
                    events.ScheduleEvent(EVENT_TERRIFYNG_ROAR, urand(15000, 22000), 0, 0);
                    break;
                case EVENT_BERSEK:
                    DoCast(me, SPELL_BERSEK);
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }

    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_beautyAI(creature);
    }
};

// 40015
class npc_runty : public CreatureScript
{
public:
    npc_runty() : CreatureScript("npc_runty") { }

    struct npc_runtyAI : public ScriptedAI
    {
        npc_runtyAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;

        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
        }

        void JustDied(Unit* killer) override
        {
            if (instance)
            {
                if (Creature* beauty = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_BEAUTY)))
                {
                    beauty->Attack(killer, true);
                    beauty->GetMotionMaster()->MoveChase(killer, 2.0f, 0.0f);
                    beauty->AddThreat(killer, 1000.0f, SPELL_SCHOOL_MASK_NORMAL, 0);
                    beauty->AI()->DoAction(ACTION_BEAUTY_BERSEK);
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_runtyAI(creature);
    }
};

// 40008, 40011, 40013  children lucky, spot, buster
class npc_beauty_family : public CreatureScript
{
public:
    npc_beauty_family() : CreatureScript("npc_beauty_family") { }

    enum minionsEvents
    {
        EVENT_LAVA_DROOL = 1,
        EVENT_LITTLE_BREATH = 2,
    };

    enum minionsSpell
    {
        SPELL_LAVA_DROOL = 76628,
        SPELL_LITTLE_BREATH = 76665,
    };

    struct npc_beauty_familyAI : public ScriptedAI
    {
        npc_beauty_familyAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset() override
        {
            events.Reset();
        }

        void EnterCombat(Unit* who) override
        {
            if (instance)
            {
                if (me->GetMap()->IsHeroic())
                {
                    if (Creature* beauty = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_BEAUTY)))
                    {
                        beauty->Attack(me->GetVictim(), true);
                        beauty->GetMotionMaster()->MoveChase(me->GetVictim(), 2.0f, 0.0f);
                    }
                }
            }

            events.ScheduleEvent(EVENT_LAVA_DROOL, urand(10000, 20000), 0, 0);
            events.ScheduleEvent(EVENT_LITTLE_BREATH, urand(6000, 12000), 0, 0);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_LAVA_DROOL:
                    DoCast(me, SPELL_LAVA_DROOL);
                    events.ScheduleEvent(EVENT_LAVA_DROOL, urand(10000, 20000), 0, 0);
                    break;
                case EVENT_LITTLE_BREATH:
                    DoCast(me->GetVictim(), SPELL_LITTLE_BREATH);
                    events.ScheduleEvent(EVENT_LITTLE_BREATH, urand(6000, 12000), 0, 0);
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_beauty_familyAI(creature);
    }
};

void AddSC_boss_beauty()
{
    new boss_beauty();
    new npc_runty();
    new npc_beauty_family();
}