/*
 * Copyright (C) 2011-2014 ArkCORE <http://www.arkania.net/>
 *
 * This file is NOT free software. Third-party users can NOT redistribute 
 * it or modify it. If you find it, you are either hacking something, or very 
 * lucky (presuming someone else managed to hack it).
 */

/* ScriptData
SDName: boss_unsleeping
SD%Complete: 85%
SDComment:
SDCategory: Boss Unsleeping
EndScriptData
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "dragon_soul.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

enum Events
{
    EVENT_DEEP_CORRUPTION = 1,
    EVENT_BLOOD_SUMMON,
    EVENT_COID_BOLT,
    EVENT_SEARING_BLOOD,
    EVENT_MANA_VOID,
    EVENT_PSYCHIC_SLICE,
    EVENT_FORGOTTEN_ONE,
    EVENT_DIGESTIVE_ACID,
};

enum Spells
{
        // Unsleeping Spells
        SPELL_COID_BOLT      = 104849,
        SPELL_SEARING_BLOOD  = 105033,
        SPELL_MANA_VOID      = 108223,
        SPELL_MANA_DIFFUSION = 105539,
        SPELL_PSYCHIC_SLICE  = 105671,
        SPELL_DIGESTIVE_ACID = 105573,

        // Blood spells
        SPELL_FUSING_VAPORS           = 108235,
        SPELL_BLACK_BLOOD_OF_SHUMA    = 104894,
        SPELL_COBALT_BLOOD_OF_SHUMA   = 105027,
        SPELL_CRIMSON_BLOOD_OF_SHUMA  = 104897,
        SPELL_GLOWING_BLOOD_OF_SHUMA  = 104901,
        SPELL_ACIDIC_BLOOD_OF_SHUMA   = 104898,
        SPELL_SHADOWED_BLOOD_OF_SHUMA = 104896,
};

Position const SummonPositions[6] =
{
    {-1808.229f, -3136.739f, -173.479f, 0.0f},
    {-1722.599f, -3137.159f, -173.389f, 0.0f},
    {-1662.959f, -2992.280f, -173.514f, 0.0f},
    {-1863.989f, -2993.09f, -174.110f, 0.0f},
    {-1723.76f, -2935.33f, -174.029f, 0.0f},
    {-1663.89f, -3077.129f, -174.479f, 0.0f},
};

Position const SummonMvPositions[6] =
{
    {-1796.594f, -3024.409f, -182.306f, 0.0f},
    {-1783.245f, -3059.68f, -182.314f, 0.0f},
    {-1755.26f, -3064.184f, -182.333f, 0.0f},
    {-1734.958f, -3035.269f, -182.309f, 0.0f},
    {-1750.737f, -3007.436f, -182.33f, 0.0f},
    {-1776.138f, -3006.868f, -182.352f, 0.0f},
};

enum Npc
{
    NPC_BLACK_BLOOD    = 55867,
    NPC_COBLAT_BLOOD   = 55866,
    NPC_CRIMSON_BLOOD  = 55865,
    NPC_GLOWING_BLOOD  = 55864,
    NPC_ACIDIC_BLOOD   = 55862,
    NPC_SHADOWED_BLOOD = 55863,
    NPC_MANA_VOID      = 38068,
    NPC_FORGOTTEN_ONE  = 56265,
};

enum Says
{
        YELL             = 0,
        WHISPER_DEATH    = 1,
        WHISPER_KILL_ALL = 2,
        WHISPER_KILL     = 3,
        WHISPER_AGGRO    = 4
};

class boss_unsleeping : public CreatureScript
{
public:
    boss_unsleeping() : CreatureScript("boss_unsleeping") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<boss_unsleepingAI>(creature);
    }

    struct boss_unsleepingAI: public BossAI
    {
        boss_unsleepingAI(Creature* creature) : BossAI(creature, BOSS_UNSLEEPING)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();

            instance->SetBossState(DATA_PORTALS_ON_OFF, DONE);
            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_BLOOD_SUMMON, 60000);
            events.ScheduleEvent(EVENT_COID_BOLT, urand(15000,30000));
            events.ScheduleEvent(EVENT_SEARING_BLOOD, 1);
            events.ScheduleEvent(EVENT_MANA_VOID, 1);
            events.ScheduleEvent(EVENT_FORGOTTEN_ONE, 1);
            events.ScheduleEvent(EVENT_DIGESTIVE_ACID, 1);
            instance->SetBossState(BOSS_UNSLEEPING, IN_PROGRESS);
            instance->SetBossState(DATA_PORTALS_ON_OFF, IN_PROGRESS);
            Talk(WHISPER_AGGRO);
            _EnterCombat();
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_BLOOD_SUMMON:
                switch (urand(0, 1))
                {
                  case 0:
                     me->SummonCreature(NPC_BLACK_BLOOD, SummonPositions[0], TEMPSUMMON_MANUAL_DESPAWN);
                     me->SummonCreature(NPC_BLACK_BLOOD, SummonPositions[0], TEMPSUMMON_MANUAL_DESPAWN);
                     me->SummonCreature(NPC_COBLAT_BLOOD, SummonPositions[1], TEMPSUMMON_MANUAL_DESPAWN);
                     me->SummonCreature(NPC_CRIMSON_BLOOD, SummonPositions[2], TEMPSUMMON_MANUAL_DESPAWN);
                  if(IsHeroic())
                     me->SummonCreature(NPC_GLOWING_BLOOD, SummonPositions[3], TEMPSUMMON_MANUAL_DESPAWN);
                     Talk(YELL);
                     break;
                  case 1:
                     me->SummonCreature(NPC_GLOWING_BLOOD, SummonPositions[3], TEMPSUMMON_MANUAL_DESPAWN);
                     me->SummonCreature(NPC_ACIDIC_BLOOD, SummonPositions[4], TEMPSUMMON_MANUAL_DESPAWN);
                     me->SummonCreature(NPC_SHADOWED_BLOOD, SummonPositions[5], TEMPSUMMON_MANUAL_DESPAWN);
                  if(IsHeroic())
                     me->SummonCreature(NPC_CRIMSON_BLOOD, SummonPositions[2], TEMPSUMMON_MANUAL_DESPAWN);
                     Talk(YELL);
                     break;
                  }
                     events.ScheduleEvent(EVENT_BLOOD_SUMMON, urand(60000, 180000));
                     break;

                 case EVENT_COID_BOLT:
                 if (me->HasAura(SPELL_GLOWING_BLOOD_OF_SHUMA))
                 {
                    if (Unit* target = me->FindNearestPlayer(100.0f))
                       DoCast(target, SPELL_COID_BOLT);
                    }
                    else if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                             DoCast(target, SPELL_COID_BOLT);

                     if (me->HasAura(SPELL_GLOWING_BLOOD_OF_SHUMA))
                         events.ScheduleEvent(EVENT_COID_BOLT, urand(2500, 15000));
                     else
                         events.ScheduleEvent(EVENT_COID_BOLT, urand(5000, 30000));
                     break;

                     case EVENT_SEARING_BLOOD:
                     if (me->HasAura(SPELL_CRIMSON_BLOOD_OF_SHUMA))
                     {
                         if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                             DoCast(target, SPELL_SEARING_BLOOD);
                             events.ScheduleEvent(EVENT_SEARING_BLOOD, urand(5000,30000));
                      }
                      else
                              events.ScheduleEvent(EVENT_SEARING_BLOOD, 1000);
                              break;

                       case EVENT_MANA_VOID:
                       if (me->HasAura(SPELL_COBALT_BLOOD_OF_SHUMA))
                       {
                           if (SelectTarget(SELECT_TARGET_RANDOM))
                               me->SummonCreature(NPC_MANA_VOID, SummonMvPositions[urand(0,5)], TEMPSUMMON_MANUAL_DESPAWN);
                               events.ScheduleEvent(EVENT_MANA_VOID, urand(3500,20000));
                        }
                        else
                               events.ScheduleEvent(EVENT_MANA_VOID, 1000);
                               break;

                        case EVENT_FORGOTTEN_ONE:
                        if (me->HasAura(SPELL_BLACK_BLOOD_OF_SHUMA))
                        {
                            if (SelectTarget(SELECT_TARGET_RANDOM))
                                me->SummonCreature(NPC_FORGOTTEN_ONE, me->GetPositionX()+5, me->GetPositionY()+5, me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 60000);
                                events.ScheduleEvent(EVENT_FORGOTTEN_ONE, urand(5000,30000));
                        }
                        else
                                events.ScheduleEvent(EVENT_FORGOTTEN_ONE, 1000);
                                break;

                        case EVENT_DIGESTIVE_ACID:
                        if (me->HasAura(SPELL_ACIDIC_BLOOD_OF_SHUMA))
                        {
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                                DoCast(target, SPELL_DIGESTIVE_ACID);
                                events.ScheduleEvent(EVENT_DIGESTIVE_ACID, urand(5000,30000));
                        }
                        else
                                events.ScheduleEvent(EVENT_DIGESTIVE_ACID, 1000);
                                break;
                default:
                    break;
                }
            }           

            DoMeleeAttackIfReady();
        }

        void JustReachedHome()
        {
            _JustReachedHome();
            instance->SetBossState(BOSS_UNSLEEPING, FAIL);
            Talk(WHISPER_KILL_ALL);
        }

       void KilledUnit(Unit* /*victim*/)
       {
            Talk(WHISPER_KILL);
       }

        void JustDied(Unit* /*killer*/)
        {
            instance->SetBossState(BOSS_UNSLEEPING, DONE);
            instance->SetBossState(DATA_PORTALS_ON_OFF, DONE);
            Talk(WHISPER_DEATH);
            _JustDied();
        }
    };
};

class npc_blood : public CreatureScript
{
    public:
        npc_blood() : CreatureScript("npc_blood") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<npc_bloodAI>(creature);
    }

    struct npc_bloodAI : public ScriptedAI
    {
        npc_bloodAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        bool blood;

        void Reset()
        {
            me->SetInCombatWithZone();
            //me->AddAura(SPELL_FUSING_VAPORS, me);
            me->SetSpeed(MOVE_RUN, 0.5f);
            blood = true;

            events.Reset();
        }

        void UpdateAI(const uint32 /*diff*/)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (Creature* u = me->FindNearestCreature(NPC_UNSLEEPING, 100.0f, true))
            {
                me->GetMotionMaster()->MovePoint(0, u->GetPositionX(), u->GetPositionY(), u->GetPositionZ());

                if (blood == true && me->FindNearestCreature(NPC_UNSLEEPING, 1.5f, true))
                {
                    blood = false;
                    if (me->GetEntry() == NPC_BLACK_BLOOD)
                        u->CastSpell(u, SPELL_BLACK_BLOOD_OF_SHUMA);

                    if (me->GetEntry() == NPC_COBLAT_BLOOD)
                        u->CastSpell(u, SPELL_COBALT_BLOOD_OF_SHUMA);

                    if (me->GetEntry() == NPC_CRIMSON_BLOOD)
                        u->CastSpell(u, SPELL_CRIMSON_BLOOD_OF_SHUMA);

                    if (me->GetEntry() == NPC_GLOWING_BLOOD)
                        u->CastSpell(u, SPELL_GLOWING_BLOOD_OF_SHUMA);

                    if (me->GetEntry() == NPC_ACIDIC_BLOOD)
                        u->CastSpell(u, SPELL_ACIDIC_BLOOD_OF_SHUMA);

                    if (me->GetEntry() == NPC_SHADOWED_BLOOD)
                        u->CastSpell(u, SPELL_SHADOWED_BLOOD_OF_SHUMA);

                    me->Kill(me);
                    me->DespawnOrUnsummon(5000);
                }
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            me->DespawnOrUnsummon(5000);
        }
    };
};

class npc_mana_void : public CreatureScript
{
    public:
        npc_mana_void() : CreatureScript("npc_mana_void") { }

                CreatureAI* GetAI(Creature* creature) const
                {
                    return GetDragonSoulAI<npc_mana_voidAI>(creature);
                }

                struct npc_mana_voidAI : public ScriptedAI
                {
                    npc_mana_voidAI(Creature* creature) : ScriptedAI(creature)
                    {
                        instance = creature->GetInstanceScript();
                    }

                        InstanceScript* instance;
                        EventMap events;

                        void Reset()
                        {
                            me->SetInCombatWithZone();
                            me->AddAura(SPELL_MANA_VOID, me);
                            events.Reset();
                        }

                        void JustDied(Unit* /*killer*/)
                        {
                            DoCast(me, SPELL_MANA_DIFFUSION, true);
                            me->DespawnOrUnsummon(5000);
                        }
                };
};

class npc_forgotten_one : public CreatureScript
{
    public:
        npc_forgotten_one() : CreatureScript("npc_forgotten_one") { }

                CreatureAI* GetAI(Creature* creature) const
                {
                    return GetDragonSoulAI<npc_forgotten_oneAI>(creature);
                }

                struct npc_forgotten_oneAI : public ScriptedAI
                {
                    npc_forgotten_oneAI(Creature* creature) : ScriptedAI(creature)
                    {
                        instance = creature->GetInstanceScript();
                    }

                        InstanceScript* instance;
                        EventMap events;

                        void Reset()
                        {
                            events.Reset();
                            me->SetInCombatWithZone();
                        }

                        void EnterCombat(Unit* /*who*/)
                       {
                        events.ScheduleEvent(EVENT_PSYCHIC_SLICE, urand(5000,15000));
            }

               void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                    events.Update(diff);

                     while (uint32 eventId = events.ExecuteEvent())
                     {
                      switch (eventId)
                      {
                          case EVENT_PSYCHIC_SLICE:
                          DoCastVictim(SPELL_PSYCHIC_SLICE);
                          events.ScheduleEvent(EVENT_PSYCHIC_SLICE, urand(5000,30000));
                          break;
                          }
                      }
                 }

               void JustDied(Unit* /*killer*/)
               {
                me->DespawnOrUnsummon(5000);
           }
      };
};

void AddSC_boss_unsleeping()
{
    new boss_unsleeping();
    new npc_blood();
    new npc_mana_void();
    new npc_forgotten_one();
}