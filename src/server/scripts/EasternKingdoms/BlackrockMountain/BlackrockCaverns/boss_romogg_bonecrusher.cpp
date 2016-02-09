/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
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

enum Spells
{
    SPELL_CALL_FOR_HELP = 82137,
    SPELL_QUAKE = 75272,
    SPELL_CHAINS_OF_WOE = 75539,
    SPELL_CHAINS_OF_WOE_VISUAL = 75441,
    SPELL_CHAINS_OF_WOE_AURA = 82192,
    SPELL_THE_SKULLCRACKER = 75543,
    SPELL_WOUNDING_STRIKE = 75571,
};

enum events
{
    EVENT_NONE,
    EVENT_QUAKE,
    EVENT_SKULLCRAKER_P1,
    EVENT_SKULLCRAKER_P2,
    EVENT_WOUNDING_STRIKE,
};

// 39665
class boss_romogg_bonecrusher : public CreatureScript
{
public:
    boss_romogg_bonecrusher() : CreatureScript("boss_romogg_bonecrusher") { }

    struct boss_romogg_bonecrusherAI : public BossAI
    {
        boss_romogg_bonecrusherAI(Creature* creature) : BossAI(creature, DATA_ROMOGG_BONECRUSHER_EVENT), summons(me)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;
        SummonList summons;
        bool firstSkull;
        bool secondSkull;
        uint8 count;
        Position chainPos;

        void Reset() override
        {
            events.Reset();
            summons.DespawnAll();
            firstSkull = false;
            secondSkull = false;
            chainPos = me->GetPosition();
        }

        void EnterCombat(Unit* who) override
        {
            DoCast(me, SPELL_CALL_FOR_HELP);
            events.ScheduleEvent(EVENT_QUAKE, urand(40000, 60000), 0, 0);
            events.ScheduleEvent(EVENT_WOUNDING_STRIKE, urand(2000, 4000), 0, 0);
        }

        void JustDied(Unit* killer) override
        {
            summons.DespawnAll();
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (me->HealthBelowPct(66) && !firstSkull)
            {
                events.ScheduleEvent(EVENT_SKULLCRAKER_P1, 1000, 0, 0);
                firstSkull = true;
            }
            if (me->HealthBelowPct(33) && !secondSkull)
            {
                events.ScheduleEvent(EVENT_SKULLCRAKER_P1, 1000, 0, 0);
                secondSkull = true;
            }

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_QUAKE:
                    DoCast(me, SPELL_QUAKE);
                    if (!me->GetMap()->GetPlayers().isEmpty())
                    {
                        for (Map::PlayerList::const_iterator i = me->GetMap()->GetPlayers().begin(); i != me->GetMap()->GetPlayers().end(); ++i)
                        {
                            uint8 count = 0;
                            if (!i->GetSource()->HasAura(SPELL_QUAKE))
                            {
                                if (i->GetSource()->IsAlive())
                                {
                                    me->AddAura(SPELL_QUAKE, i->GetSource());
                                    if ((count / 2) == 0 && me->GetMap()->IsHeroic())
                                    {
                                        Position pos = i->GetSource()->GetPosition();
                                        me->SummonCreature(NPC_ANGERED_EARTH, pos, TEMPSUMMON_CORPSE_DESPAWN);
                                    }
                                }
                            }
                            ++count;
                        }
                    }
                    events.ScheduleEvent(EVENT_QUAKE, urand(40000, 60000), 0, 0);
                    break;
                case EVENT_SKULLCRAKER_P1:
                    Talk(1);
                    DoCast(SPELL_CHAINS_OF_WOE);
                    events.ScheduleEvent(EVENT_SKULLCRAKER_P2, 1500, 0, 0);
                    break;
                case EVENT_SKULLCRAKER_P2:
                    if (!me->GetMap()->GetPlayers().isEmpty())
                    {
                        for (Map::PlayerList::const_iterator i = me->GetMap()->GetPlayers().begin(); i != me->GetMap()->GetPlayers().end(); ++i)
                        {
                            ++count;
                            if (i->GetSource()->IsAlive())
                            {
                                i->GetSource()->TeleportTo(me->GetMapId(), chainPos.m_positionX, chainPos.m_positionY, chainPos.m_positionZ, chainPos.m_orientation, 0);
                            }
                        }
                    }
                    DoCastAOE(SPELL_THE_SKULLCRACKER);
                    break;
                case EVENT_WOUNDING_STRIKE:
                    DoCast(SPELL_WOUNDING_STRIKE);
                    events.ScheduleEvent(EVENT_WOUNDING_STRIKE, urand(2000, 4000), 0, 0);
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void JustSummoned(Creature* summoned) override
        {
            summons.Summon(summoned);
            if (summoned->GetEntry() == NPC_CHAINS_OF_WOE)
            {
                chainPos = summoned->GetPosition();
                summoned->CastSpell(summoned, SPELL_CHAINS_OF_WOE_VISUAL, true);
            }
        }

        void SummonedCreatureDespawn(Creature* summon)
        {
            if (summon->GetEntry() == NPC_CHAINS_OF_WOE)
            {
                if (!me->GetMap()->GetPlayers().isEmpty())
                {
                    for (Map::PlayerList::const_iterator i = me->GetMap()->GetPlayers().begin(); i != me->GetMap()->GetPlayers().end(); ++i)
                    {
                        if (i->GetSource())
                        {
                            if (i->GetSource()->HasAura(SPELL_CHAINS_OF_WOE_AURA))
                            {
                                i->GetSource()->RemoveAura(SPELL_CHAINS_OF_WOE_AURA);
                            }
                        }
                    }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_romogg_bonecrusherAI(creature);
    }
};

// 75539
class spell_chains_of_woe : public SpellScriptLoader
{
public:
    spell_chains_of_woe() : SpellScriptLoader("spell_chains_of_woe") { }

    class spell_chains_of_woe_SpellScript : public AuraScript
    {
        PrepareAuraScript(spell_chains_of_woe_SpellScript);

        void PeriodicTick(AuraEffect const* /*aurEff*/)
        {
            if (Unit *caster = GetCaster())
            {
                if (caster->GetMap()->IsDungeon())
                {
                    if (!caster->GetMap()->GetPlayers().isEmpty())
                    {
                        for (Map::PlayerList::const_iterator i = caster->GetMap()->GetPlayers().begin(); i != caster->GetMap()->GetPlayers().end(); ++i)
                        {
                            if (i->GetSource()->IsAlive())
                                i->GetSource()->CastSpell(i->GetSource(), SPELL_CHAINS_OF_WOE_AURA, true);
                        }
                    }
                }
            }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_chains_of_woe_SpellScript::PeriodicTick, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_chains_of_woe_SpellScript();
    }
};

void AddSC_boss_romogg_bonecrusher()
{
    new boss_romogg_bonecrusher();
    // new spell_chains_of_woe(); // wrong spell implemets
}