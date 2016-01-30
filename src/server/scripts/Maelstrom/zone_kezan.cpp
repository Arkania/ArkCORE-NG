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
 
// 349689
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
            m_events.RescheduleEvent(EVENT_SPELLCAST, 3000);
        }

        // Called when spell hits a target
        void SpellHitTarget(Unit* /*target*/, SpellInfo const* spell) override
        { 
            if (spell->Id == SPELL_SHADOW_BOLD)
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

// 349696
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
            m_events.ScheduleEvent(EVENT_SPELLCAST, urand(10000, 30000));
            m_targetGuid = 0;
        }

        // Called when hit by a spell
        void SpellHit(Unit* /*caster*/, SpellInfo const* /*spell*/) override
        {
            m_events.RescheduleEvent(EVENT_SPELLCAST, 3000);
        }

        // Called when spell hits a target
        void SpellHitTarget(Unit* /*target*/, SpellInfo const* spell) override
        {
            if (spell->Id == SPELL_FIREBALL)
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

void AddSC_zone_kezan()
{
    new npc_fizz_lighter_34689();
    new npc_evol_fingers_34696();
}

