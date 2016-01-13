/*
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
 *
 * This file is NOT free software. Third-party users can NOT redistribute
 * it or modify it. If you find it, you are either hacking something, or very
 * lucky (presuming someone else managed to hack it).
 */

/* ScriptData
SDName: boss_hagara_the_stormbinder
SD%Complete: 70%
SDComment:
SDCategory: Boss Hagara
EndScriptData
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "dragon_soul.h"

enum Events
{
    EVENT_ICE_SPEAR = 1,
    EVENT_ICE_TOMB, // No Work
    EVENT_SHATTERED_ICE,
    EVENT_FOCUSED_ASSAULT, // No Work

    EVENT_DAMAGE_PHASE2_1,
    EVENT_DAMAGE_PHASE2_3,
    EVENT_REMOVE_PHASE_2,
    HAS_ICE_SPEAR_DEATH,

    EVENT_DAMAGE_PHASE3_1,
    EVENT_DAMAGE_PHASE3_2,
    EVENT_SUMMON_CRYSTAL,
    EVENT_DAMAGE_PHASE3_4,
    EVENT_REMOVE_PHASE_3,
    HAS_ARRESTER_RELOAD,

    EVENT_CAST_CRYSTAL,
    EVENT_DESTROY_CRISTAL,

    EVENT_PHASE_1,
    EVENT_PHASE_2,
    EVENT_PHASE_3,
};

enum Spells
{
    SPELL_FEEDBACK = 108934,
    SPELL_FOCUSED_ASSAULT = 107850,
    SPELL_FROSTFLAKE = 109325,
    SPELL_FROZEN_TEMPEST = 105256,
    SPELL_ICE_TOMB = 104448,
    SPELL_LIGHTNING_CONDUIT = 105369,
    SPELL_LIGHTNING_STORM = 105465,
    SPELL_SHATTERED_ICE = 105289,
    SPELL_STORM_PILLAR = 109541,
    SPELL_WATER_SHIELD = 105409,
    SPELL_ICE_SHIELD = 105256,
    SPELL_ICE_SPEAR = 105313,
    SPELL_ICE_WAVE = 105265,
    SPELL_ICICLE = 109315,

    SPELL_AURA_CRYSTAL = 105482,
};

enum Spells_other
{
    SPELL_CRYSTALLINE_TETHER = 105312,
    SPELL_CRYSTALLINE_OVERLOAD = 105311,
};

enum Say
{
    SAY_AGGRO = 0,
    SAY_KILL = 1,
    SAY_DEAD = 2,
};

class boss_hagara : public CreatureScript
{
public:
    boss_hagara() : CreatureScript("boss_hagara") { }

    struct boss_hagaraAI : public BossAI
    {
        boss_hagaraAI(Creature* creature) : BossAI(creature, BOSS_HAGARA)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;
        uint8 phase;

        void Reset()
        {
            events.Reset();

            instance->SetBossState(DATA_PORTALS_ON_OFF, DONE);
            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();
            events.ScheduleEvent(EVENT_PHASE_1, 150, 150);
            instance->SetBossState(DATA_PORTALS_ON_OFF, IN_PROGRESS);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    // Phase 1
                case EVENT_PHASE_1:
                    events.ScheduleEvent(EVENT_ICE_SPEAR, urand(5000, 14000));
                    events.ScheduleEvent(EVENT_SHATTERED_ICE, urand(15000, 30000));
                    switch (urand(0, 1))
                    {
                    case 0:
                        events.ScheduleEvent(EVENT_PHASE_2, urand(200000, 340000));
                        break;
                    case 1:
                        events.ScheduleEvent(EVENT_PHASE_3, 200000, 340000);
                        break;
                    }
                    break;

                case EVENT_ICE_SPEAR:
                    DoCastVictim(SPELL_ICE_SPEAR);
                    events.ScheduleEvent(EVENT_ICE_SPEAR, urand(5000, 14000));
                    break;

                case EVENT_SHATTERED_ICE:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                        DoCast(target, SPELL_SHATTERED_ICE);
                    events.ScheduleEvent(EVENT_SHATTERED_ICE, urand(20000, 40000));
                    break;

                    //phase 2
                case EVENT_PHASE_2:
                    events.CancelEvent(EVENT_PHASE_1);
                    events.CancelEvent(EVENT_ICE_SPEAR);
                    events.CancelEvent(EVENT_SHATTERED_ICE);
                    events.ScheduleEvent(HAS_ICE_SPEAR_DEATH, 5000);
                    events.ScheduleEvent(EVENT_DAMAGE_PHASE2_1, 1);
                    events.ScheduleEvent(EVENT_REMOVE_PHASE_2, 310000);
                    if (IsHeroic())
                        events.ScheduleEvent(EVENT_DAMAGE_PHASE2_3, urand(15000, 30000));
                    instance->SetBossState(DATA_WAVE, IN_PROGRESS);
                    DoCast(SPELL_ICE_SHIELD);
                    break;

                case HAS_ICE_SPEAR_DEATH:
                    if (me->HasAura(SPELL_AURA_CRYSTAL))
                    {
                        events.ScheduleEvent(HAS_ICE_SPEAR_DEATH, 1000);
                    }
                    else
                    {
                        events.CancelEvent(EVENT_PHASE_2);
                        events.CancelEvent(EVENT_REMOVE_PHASE_2);
                        events.CancelEvent(EVENT_DAMAGE_PHASE2_3);
                        events.CancelEvent(HAS_ICE_SPEAR_DEATH);
                        events.ScheduleEvent(EVENT_PHASE_1, 1);
                        me->RemoveAurasDueToSpell(SPELL_ICE_SHIELD);
                        instance->SetBossState(DATA_WAVE, DONE);
                    }
                    break;

                case EVENT_REMOVE_PHASE_2:
                    events.CancelEvent(EVENT_PHASE_2);
                    events.CancelEvent(EVENT_DAMAGE_PHASE2_3);
                    events.ScheduleEvent(EVENT_PHASE_1, 1);
                    break;

                case EVENT_DAMAGE_PHASE2_1:
                    me->SummonCreature(NPC_ICE_WAVE, 13587.398f, 13581.050f, 123.483f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 340000);
                    me->SummonCreature(NPC_ICE_WAVE, 13587.754f, 13571.093f, 123.483f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 340000);
                    me->SummonCreature(NPC_ICE_WAVE, 13587.528f, 13563.034f, 124.480f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 340000);
                    me->SummonCreature(NPC_ICE_WAVE, 13587.476f, 13559.762f, 124.480f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 340000);

                    me->SummonCreature(NPC_ICE_WAVE, 13555.149f, 13612.340f, 123.483f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 340000);
                    me->SummonCreature(NPC_ICE_WAVE, 13551.117f, 13612.680f, 123.483f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 340000);
                    me->SummonCreature(NPC_ICE_WAVE, 13544.259f, 13612.964f, 123.483f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 340000);
                    me->SummonCreature(NPC_ICE_WAVE, 13537.617f, 13612.762f, 123.479f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 340000);

                    me->SummonCreature(NPC_ICE_WAVE, 13592.307f, 13643.856f, 123.484f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 340000);
                    me->SummonCreature(NPC_ICE_WAVE, 13593.133f, 13649.511f, 123.484f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 340000);
                    me->SummonCreature(NPC_ICE_WAVE, 13594.512f, 13655.144f, 123.484f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 340000);
                    me->SummonCreature(NPC_ICE_WAVE, 13596.036f, 13661.617f, 124.480f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 340000);

                    me->SummonCreature(NPC_ICE_WAVE, 13617.921f, 13612.467f, 123.483f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 340000);
                    me->SummonCreature(NPC_ICE_WAVE, 13622.455f, 13612.219f, 123.483f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 340000);
                    me->SummonCreature(NPC_ICE_WAVE, 13628.173f, 13612.303f, 124.483f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 340000);
                    me->SummonCreature(NPC_ICE_WAVE, 13635.879f, 13612.416f, 124.480f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 340000);

                    me->SummonCreature(NPC_ICICLE, 13585.291f, 13610.428f, 122.420f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 340000);

                    me->SummonCreature(NPC_FORZEN_BINDIG_CRYSTAL, 13617.5f, 13580.9f, 123.567f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 310000);
                    me->SummonCreature(NPC_FORZEN_BINDIG_CRYSTAL, 13557.4f, 13643.1f, 123.567f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 310000);
                    me->SummonCreature(NPC_FORZEN_BINDIG_CRYSTAL, 13557.7f, 13580.7f, 123.567f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 310000);
                    me->SummonCreature(NPC_FORZEN_BINDIG_CRYSTAL, 13617.3f, 13643.5f, 123.567f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 310000);
                    break;

                case EVENT_DAMAGE_PHASE2_3:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                        me->AddAura(SPELL_FROSTFLAKE, target);
                    events.ScheduleEvent(EVENT_DAMAGE_PHASE2_3, urand(5000, 35000));
                    break;

                    //Phase 3
                case EVENT_PHASE_3:
                    events.CancelEvent(EVENT_ICE_SPEAR);
                    events.CancelEvent(EVENT_SHATTERED_ICE);
                    events.ScheduleEvent(EVENT_REMOVE_PHASE_3, 310000);
                    events.ScheduleEvent(EVENT_DAMAGE_PHASE3_1, 10000);
                    events.ScheduleEvent(HAS_ARRESTER_RELOAD, 5000);
                    events.ScheduleEvent(EVENT_SUMMON_CRYSTAL, 1);
                    DoCast(SPELL_WATER_SHIELD);
                    break;

                case HAS_ARRESTER_RELOAD:
                    if (me->HasAura(SPELL_AURA_CRYSTAL))
                    {
                        events.ScheduleEvent(HAS_ARRESTER_RELOAD, 1000);
                    }
                    else
                    {
                        events.CancelEvent(EVENT_PHASE_3);
                        events.CancelEvent(EVENT_REMOVE_PHASE_3);
                        events.CancelEvent(EVENT_DAMAGE_PHASE3_1);
                        events.CancelEvent(HAS_ARRESTER_RELOAD);
                        events.ScheduleEvent(EVENT_PHASE_1, 1);
                        me->RemoveAurasDueToSpell(SPELL_WATER_SHIELD);
                    }
                    break;

                case EVENT_REMOVE_PHASE_3:
                    events.CancelEvent(EVENT_PHASE_3);
                    events.CancelEvent(EVENT_DAMAGE_PHASE3_1);
                    events.ScheduleEvent(EVENT_PHASE_1, 1);
                    break;

                case EVENT_DAMAGE_PHASE3_1:
                    me->SummonCreature(NPC_BOUND_LIGHTNING_ELEMENTAL, 13587.624f, 13653.375f, 123.483f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 130000);
                    me->SummonCreature(NPC_BOUND_LIGHTNING_ELEMENTAL, 13621.863f, 13621.847f, 123.483f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 130000);
                    me->SummonCreature(NPC_BOUND_LIGHTNING_ELEMENTAL, 13623.250f, 13606.621f, 123.483f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 130000);
                    me->SummonCreature(NPC_BOUND_LIGHTNING_ELEMENTAL, 13587.191f, 13570.221f, 123.483f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 130000);
                    events.ScheduleEvent(EVENT_DAMAGE_PHASE3_1, urand(60000, 90000));
                    break;

                case EVENT_SUMMON_CRYSTAL:
                    me->SummonCreature(NPC_CRYSTAL_CONDUCTOR, 13617.5f, 13580.9f, 123.567f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 310000);
                    me->SummonCreature(NPC_CRYSTAL_CONDUCTOR, 13557.4f, 13643.1f, 123.567f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 310000);
                    me->SummonCreature(NPC_CRYSTAL_CONDUCTOR, 13557.7f, 13580.7f, 123.567f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 310000);
                    me->SummonCreature(NPC_CRYSTAL_CONDUCTOR, 13617.3f, 13643.5f, 123.567f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 310000);
                    break;
                default:
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/)
        {
            instance->SetBossState(BOSS_HAGARA, DONE);
            instance->SetBossState(DATA_PORTALS_ON_OFF, DONE);
            instance->SetBossState(DATA_TRALL_VS_ULTRAXION, IN_PROGRESS);
            _JustDied();

            Unit * portal = me->FindNearestCreature(NPC_PORTAL_SKYFIRE, 20.0f);

            if (!portal)
                portal = me->SummonCreature(NPC_PORTAL_SKYFIRE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 3, 1.5f, TEMPSUMMON_TIMED_DESPAWN, 5 * MINUTE*IN_MILLISECONDS);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<boss_hagaraAI>(creature);
    }
};

class npc_ice_wave : public CreatureScript
{
public:
    npc_ice_wave() : CreatureScript("npc_ice_wave") { }

    struct npc_ice_waveAI : public ScriptedAI
    {
        npc_ice_waveAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.ScheduleEvent(EVENT_DESTROY_CRISTAL, 1);
            me->DespawnOrUnsummon(340000);
            me->AddAura(105265, me);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_DESTROY_CRISTAL:
                    if (instance->GetBossState(DATA_WAVE) == DONE)
                        me->DespawnOrUnsummon(1);
                    events.ScheduleEvent(EVENT_DESTROY_CRISTAL, 1);
                    break;
                default:
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }


        void JustDied(Unit* /*killer*/)
        {
            DoCast(SPELL_CRYSTALLINE_OVERLOAD);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<npc_ice_waveAI>(creature);
    }
};

class npc_crystal_conductor : public CreatureScript
{
public:
    npc_crystal_conductor() : CreatureScript("npc_crystal_conductor") { }

    struct npc_crystal_conductorAI : public ScriptedAI
    {
        npc_crystal_conductorAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void EnterCombat(Unit* /*who*/)
        {
            if (Unit* target = me->FindNearestCreature(NPC_HAGARA, 100.0f))
                DoCast(target, SPELL_CRYSTALLINE_TETHER);

            events.ScheduleEvent(EVENT_CAST_CRYSTAL, urand(5000, 10000));
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CAST_CRYSTAL:
                    DoCastVictim(SPELL_LIGHTNING_CONDUIT);
                    break;
                }
            }
        }

        void JustDied(Unit* /*killer*/)
        {
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<npc_crystal_conductorAI>(creature);
    }
};

void AddSC_boss_hagara()
{
    new boss_hagara();
    new npc_ice_wave();
    new npc_crystal_conductor();
}