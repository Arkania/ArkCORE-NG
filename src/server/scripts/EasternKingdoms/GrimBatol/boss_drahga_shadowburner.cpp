/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
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

#include "grim_batol.h"
#include "Spell.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "Vehicle.h"

enum ScriptTexts
{
    //drahga
    SAY_AGGRO    = 0,
    SAY_KILL     = 2,
    SAY_DEATH    = 3,
    SAY_ADDS     = 4,
    SAY_VALIONA  = 5,
    //valiona
    SAY_ENTER    = 0,
    SAY_LEAVE    = 1
};

enum Spells
{
    SPELL_BURNING_SHADOWBOLT      = 75245,
    SPELL_BURNING_SHADOWBOLT_H    = 90915,
    SPELL_INVOCATION_OF_FLAME     = 75222,
    SPELL_FLAMING_FIXATE          = 82850,
    SPELL_INVOKED_FLAME           = 75235,
    SPELL_SUPERNOVA               = 75238,
    SPELL_SUPERNOVA_H             = 90972,
    SPELL_TWILIGHT_PROTECTION     = 76303,
    SPELL_TWILIGHT_SHIFT          = 75328,
    SPELL_SHREDDING_SWIPE         = 75271,
    SPELL_SHREDDING_SWIPE_H       = 40365,
    SPELL_SEEPING_TWILIGHT_DUMMY  = 75318,
    SPELL_SEEPING_TWILIGHT        = 75274,
    SPELL_SEEPING_TWILIGHT_H      = 90965,
    SPELL_SEEPING_TWILIGHT_DMG    = 75317,
    SPELL_SEEPING_TWILIGHT_DMG_H  = 90964,
    SPELL_VALIONAS_FLAME          = 75321,
    SPELL_VALIONAS_FLAME_H        = 90973,
    SPELL_DEVOURING_FLAMES        = 90950
};

enum Adds
{
    NPC_INVOCATION_OF_FLAME_STALKER  = 40355,
    NPC_INVOKED_FLAMING_SPIRIT       = 40357,
    NPC_VALIONA                      = 40320,
    NPC_SEEPING_TWILIGHT             = 40365,
    NPC_DEVOURING_FLAMES             = 48798
};

enum Events
{
    EVENT_BURNING_SHADOWBOLT     = 1,
    EVENT_INVOCATION_OF_FLAME    = 2,
    EVENT_SELECT_TARGET          = 3,
    EVENT_VALIONAS_FLAME         = 4,
    EVENT_SHREDDING_SWIPE        = 5
};

const Position drahgavalionaPos[2] =
{
    {-391.38f, -678.52f, 275.56f, 3.68f},
    {-431.79f, -697.17f, 268.62f, 3.45f}
};

// 40319
class boss_drahga_shadowburner : public CreatureScript
{
    public:
        boss_drahga_shadowburner() : CreatureScript("boss_drahga_shadowburner") { }

        struct boss_drahga_shadowburnerAI : public ScriptedAI
        {
            boss_drahga_shadowburnerAI(Creature* creature) : ScriptedAI(creature), summons(me)
            {
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_STUN, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FEAR, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_ROOT, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FREEZE, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_POLYMORPH, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_HORROR, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_SAPPED, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_CHARM, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_DISORIENTED, true);
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;
            SummonList summons;
            uint8 stage;

            void Reset()
            {
                me->ExitVehicle();
                summons.DespawnAll();
                events.Reset();
                stage = 0;
                if (instance)
                    instance->SetData(DATA_DRAHGA_SHADOWBURNER, NOT_STARTED);
            }

            void SpellHit(Unit* /*caster*/, SpellInfo const* spell)
            {
                if (me->GetCurrentSpell(CURRENT_GENERIC_SPELL))
                    if ((me->GetCurrentSpell(CURRENT_GENERIC_SPELL)->m_spellInfo->Id == SPELL_BURNING_SHADOWBOLT) ||
                        (me->GetCurrentSpell(CURRENT_GENERIC_SPELL)->m_spellInfo->Id == SPELL_BURNING_SHADOWBOLT_H))
                        for (uint8 i = 0; i < 3; ++i)
                            if (spell->Effects[i].Effect == SPELL_EFFECT_INTERRUPT_CAST)
                                me->InterruptSpell(CURRENT_GENERIC_SPELL);
            }

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);
            }

            void DamageTaken(Unit* /*attacker*/, uint32 &damage)
            {
                if (me->GetVehicle())
                    damage = 0;
            }

            void SummonedCreatureDespawn(Creature* summon)
            {
                summons.Despawn(summon);
            }

            void EnterCombat(Unit* /*who*/)
            {
                Talk(SAY_AGGRO);
                events.ScheduleEvent(EVENT_BURNING_SHADOWBOLT, urand(2000, 5000));
                events.ScheduleEvent(EVENT_INVOCATION_OF_FLAME, 10000);
                if (instance)
                    instance->SetData(DATA_DRAHGA_SHADOWBURNER, IN_PROGRESS);
            }
            
            void JustDied(Unit* /*killer*/)
            {
                Talk(SAY_DEATH);
                summons.DespawnAll();
                if (instance)
                    instance->SetData(DATA_DRAHGA_SHADOWBURNER, DONE);
            }

            void KilledUnit(Unit* /*victim*/)
            {                
                Talk(SAY_KILL);
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->GetDistance(me->GetHomePosition()) > 60.0f)
                {
                    EnterEvadeMode();
                    return;
                }

                if (me->HealthBelowPct(30) && stage == 0)
                {
                    stage = 1;
                    DoCast(me, SPELL_TWILIGHT_PROTECTION);
                    if (Creature* valiona = me->SummonCreature(NPC_VALIONA, drahgavalionaPos[0]))
                    {
                        Talk(SAY_VALIONA);
                        valiona->SetReactState(REACT_PASSIVE);
                        valiona->SetCanFly(true);
                        valiona->GetMotionMaster()->MovePoint(1001, drahgavalionaPos[1]);
                    }
                    return;
                }

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_BURNING_SHADOWBOLT:
                        me->CastCustomSpell(SPELL_BURNING_SHADOWBOLT, SPELLVALUE_MAX_TARGETS, 1, 0, false);
                        events.ScheduleEvent(EVENT_BURNING_SHADOWBOLT, urand(8000, 15000));
                        break;
                    case EVENT_INVOCATION_OF_FLAME:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 0.0f, true))
                        {
                            me->SummonCreature(NPC_INVOCATION_OF_FLAME_STALKER,
                            target->GetPositionX(),
                            target->GetPositionY(),
                            target->GetPositionZ(),
                            0.0f, TEMPSUMMON_TIMED_DESPAWN, 6000);
                            Talk(SAY_ADDS);
                        }
                        events.ScheduleEvent(EVENT_INVOCATION_OF_FLAME, 20000);
                        break;
                    }
                }
                if (!me->GetVehicle())
                    DoMeleeAttackIfReady();
            }

        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_drahga_shadowburnerAI(creature);
        }
};

// 40320
class npc_drahga_valiona : public CreatureScript
{
    public:
        npc_drahga_valiona() : CreatureScript("npc_drahga_valiona") { }

        struct npc_drahga_valionaAI : public ScriptedAI
        {
            npc_drahga_valionaAI(Creature* creature) : ScriptedAI(creature), summons(me)
            {
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_STUN, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FEAR, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_ROOT, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FREEZE, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_POLYMORPH, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_HORROR, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_SAPPED, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_CHARM, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_DISORIENTED, true);
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;
            SummonList summons;
            uint8 stage;

            void Reset()
            {
                summons.DespawnAll();
                events.Reset();
                stage = 0;
            }

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);
            }

            void SummonedCreatureDespawn(Creature* summon)
            {
                summons.Despawn(summon);
            }

            void EnterCombat(Unit* /*who*/)
            {
                events.ScheduleEvent(EVENT_VALIONAS_FLAME, urand(10000, 15000));
                events.ScheduleEvent(EVENT_SHREDDING_SWIPE, urand(8000, 10000));
            }

            void MovementInform(uint32 type, uint32 id)
            {
                if (type == POINT_MOTION_TYPE)
                {
                    switch (id)
                    {
                    case 1001:
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->SetCanFly(false);
                        Talk(SAY_ENTER);
                        break;
                    case 1002:
                        me->DespawnOrUnsummon();
                        break;
                    }
                }
            }

            void EnterEvadeMode()
            {
                if (me->GetVehicleKit())
                    me->GetVehicleKit()->RemoveAllPassengers();
                me->DespawnOrUnsummon();
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HealthBelowPct(30) && stage == 0)
                {
                    stage = 1;
                    events.Reset();
                    DoCast(me, SPELL_TWILIGHT_SHIFT);
                    me->SetReactState(REACT_PASSIVE);
                    if (me->GetVehicleKit())
                        me->GetVehicleKit()->RemoveAllPassengers();
                    me->SetCanFly(true);
                    me->GetMotionMaster()->MovePoint(1002, drahgavalionaPos[0]);
                    if (Creature* drahga = Unit::GetCreature(*me, instance->GetData64(DATA_DRAHGA_SHADOWBURNER)))
                        drahga->RemoveAurasDueToSpell(SPELL_TWILIGHT_PROTECTION);
                    Talk(SAY_LEAVE);
                    return;
                }

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_VALIONAS_FLAME:
                        if (IsHeroic())
                            DoCast(me, SPELL_DEVOURING_FLAMES);
                        else
                            DoCast(me, SPELL_VALIONAS_FLAME);
                        events.ScheduleEvent(EVENT_VALIONAS_FLAME, urand(15000, 22000));
                        break;
                    case EVENT_SHREDDING_SWIPE:
                        DoCastVictim(SPELL_SHREDDING_SWIPE);
                        events.ScheduleEvent(EVENT_SHREDDING_SWIPE, urand(20000, 22000));
                        break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_drahga_valionaAI(creature);
        }
};

// 40355
class npc_invocation_of_flame_stalker : public CreatureScript
{
    public:

        npc_invocation_of_flame_stalker() : CreatureScript("npc_invocation_of_flame_stalker"){ }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_invocation_of_flame_stalkerAI(creature);
        }

        struct npc_invocation_of_flame_stalkerAI : public ScriptedAI
        {
            npc_invocation_of_flame_stalkerAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }
            
            InstanceScript* instance;
            
            void JustSummoned(Creature* summon)
            {
                switch (summon->GetEntry())
                {
                case NPC_INVOKED_FLAMING_SPIRIT:
                    if (Creature* drahga = Unit::GetCreature(*me, instance->GetData64(DATA_DRAHGA_SHADOWBURNER)))
                        if (Unit* target = drahga->GetAI()->SelectTarget(SELECT_TARGET_RANDOM))
                            summon->AI()->AttackStart(target);
                    break;
                }
            }

            void Reset()
            {
                DoCast(me, SPELL_INVOCATION_OF_FLAME);
            }
        };
};

// 40357
class npc_invoked_flaming_spirit : public CreatureScript
{
    public:

        npc_invoked_flaming_spirit() : CreatureScript("npc_invoked_flaming_spirit"){ }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_invoked_flaming_spiritAI(creature);
        }

        struct npc_invoked_flaming_spiritAI : public ScriptedAI
        {
            npc_invoked_flaming_spiritAI(Creature* creature) : ScriptedAI(creature)
            {
                me->SetSpeed(MOVE_RUN, 0.8f);
                me->SetSpeed(MOVE_WALK, 0.8f);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FEAR, true);
                me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
                instance = creature->GetInstanceScript();
            }
            
            InstanceScript* instance;

            void Reset()
            {
                DoCast(me, SPELL_INVOKED_FLAME);
            }

            void JustDied(Unit* /*target*/)
            {
                me->DespawnOrUnsummon();
            }

            void UpdateAI(uint32 /*diff*/)
            {
                if (!instance)
                    return;

                if (instance->GetData(DATA_DRAHGA_SHADOWBURNER) != IN_PROGRESS)
                    me->DespawnOrUnsummon();

                DoMeleeAttackIfReady();
            }
        };
};

// 40365
class npc_seeping_twilight : public CreatureScript
{
    public:

        npc_seeping_twilight() : CreatureScript("npc_seeping_twilight"){ }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_seeping_twilightAI(creature);
        }

        struct npc_seeping_twilightAI : public ScriptedAI
        {
            npc_seeping_twilightAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void Reset()
            {
                DoCast(me, SPELL_SEEPING_TWILIGHT_DUMMY);
                DoCast(me, DUNGEON_MODE(SPELL_SEEPING_TWILIGHT, SPELL_SEEPING_TWILIGHT_H));
            }
        };
};

// 75238
class spell_drahga_supernova : public SpellScriptLoader
{
    public:
        spell_drahga_supernova() : SpellScriptLoader("spell_drahga_supernova") { }

        class spell_drahga_supernova_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_drahga_supernova_SpellScript);

            void HandleScriptEffect(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                if (!GetCaster())
                    return;

                GetCaster()->ToCreature()->DespawnOrUnsummon(500);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_drahga_supernova_SpellScript::HandleScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_drahga_supernova_SpellScript();
        }
};

void AddSC_boss_drahga_shadowburner()
{
    new boss_drahga_shadowburner();
    new npc_invocation_of_flame_stalker();
    new npc_invoked_flaming_spirit();
    new npc_drahga_valiona();
    new npc_seeping_twilight();
    new spell_drahga_supernova();
}