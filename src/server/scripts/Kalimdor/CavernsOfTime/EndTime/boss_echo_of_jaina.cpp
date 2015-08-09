/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * Script 99% done. TODO:
 * - Live Testing needed.
 *
 * THIS particular file is NOT free software; third-party users 
 * should NOT have access to it, redistribute it or modify it. :)
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "end_time.h"
#include "Vehicle.h"
#include "Unit.h"
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
#include "SpellAuraEffects.h"
#include "SpellAuras.h"
#include "CreatureTextMgr.h"
#include "Vehicle.h"
#include "VehicleDefines.h"
#include "Spell.h"
#include "Player.h"
#include "Map.h"
#include "InstanceScript.h"

enum Yells
{
    SAY_AGGRO_1 = 1,
    SAY_AGGRO_2,
    SAY_FROST_BLADES, // Spell 1
    SAY_FROSTBOLT_VOLLEY, // Spell 2
    SAY_BLINK, // Spell 3
    SAY_SLAY_1,
    SAY_SLAY_2,
    SAY_SLAY_3,
    SAY_DEATH
};

enum Spells
{
    SPELL_BLINK = 101812,

    SPELL_FLARECORE_MISSILE = 101927,
    SPELL_UNSTABLE_FLARE = 101980, // When touched. Needs radius 5y.
    SPELL_TIME_EXPIRE_FLARE = 101587, // If not exploded in 10s. Needs radius 200y.
    SPELL_CHECK_PLAYER_DIST = 101588, // Periodic dummy on npc, check 500 ms.

    SPELL_FROSTBOLT_VOLLEY = 101810, // Needs radius 65y.
    SPELL_PYROBLAST = 101809,

    SPELL_FROST_BLADES = 101339, // Summon Frost Blades spell. Use with JustSummoned to send them away in a straight line, otherwise npc works ok.
};

enum Events
{
    EVENT_FLARECORE = 1, // 20 sec cd
    EVENT_BLINK, // Every 30 sec.
    EVENT_FROSTBOLT_VOLLEY, // 3 times in succession after blink.
    EVENT_PYROBLAST, // Constantly, no melee. Every 5 to 6 sec.
    EVENT_FROST_BLADES, // 25 sec cd, just after blink.

    // FlareCore
    EVENT_CHECK_PLAYER,
    EVENT_EXPLODE
};

enum Creatures
{
    NPC_FLARECORE   = 54446,
    NPC_FROSTBLADES = 54494,
    NPC_BLINK_TARGT = 54542,
    NPC_CIRCLE_VIS  = 54639,
};

uint32 FragmentsCount = 1;
#define MAX_FRAGMENTS_COUNT 16

static const Position JainaSummonPos = {3051.510f, 510.032f, 21.562f, 3.02f};

class boss_echo_of_jaina : public CreatureScript
{
    public:
        boss_echo_of_jaina() : CreatureScript("boss_echo_of_jaina") { }

        struct boss_echo_of_jainaAI : public BossAI
        {
            boss_echo_of_jainaAI(Creature* creature) : BossAI(creature, BOSS_ECHO_OF_JAINA), summons(me)
            {
                instance = me->GetInstanceScript();
            }

            InstanceScript* instance;
            uint32 VolleyCount;
            SummonList summons;
            EventMap events;

            void Reset()
            {
                events.Reset();
                if (instance)
                    instance->SetBossState(BOSS_ECHO_OF_JAINA, NOT_STARTED);

                VolleyCount = 0;
            }

            void EnterEvadeMode()
            {
                me->GetMotionMaster()->MoveTargetedHome();
                Reset();

                me->SetHealth(me->GetMaxHealth());

                if (instance)
                {
                    instance->SetBossState(BOSS_ECHO_OF_JAINA, FAIL);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
                }
            }

            void JustDied(Unit* /*killer*/)
            {
                Talk(SAY_DEATH);

                if (instance)
                {
                    if (instance->GetData(DATA_FIRST_ENCOUNTER) == IN_PROGRESS)
                        instance->SetData(DATA_FIRST_ENCOUNTER, DONE);
                    else  
                        instance->SetData(DATA_SECOND_ENCOUNTER, DONE);
                    
                    instance->SetBossState(BOSS_ECHO_OF_JAINA, DONE);
                    instance->SetData(DATA_JAINA_PICKED_STATE, DONE);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
                }
            }

            void KilledUnit(Unit * /*victim*/)
            {
                Talk(RAND(SAY_SLAY_1, SAY_SLAY_2, SAY_SLAY_3));
            }

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);
                summon->setActive(true);

                if(me->IsInCombat())
                summon->AI()->DoZoneInCombat();

                switch(summon->GetEntry())
                {
                    case NPC_FROSTBLADES:
                        summon->SetReactState(REACT_PASSIVE);
                        float x, y, z;
                        summon->GetClosePoint(x, y, z, me->GetObjectSize() / 3, 100.0f);
                        summon->GetMotionMaster()->MovePoint(1, x, y, z);
                        summon->DespawnOrUnsummon(10000);
                        break;

                    default:
                        break;
                }
            }

            void EnterCombat(Unit* /*who*/)
            {
                Talk(RAND(SAY_AGGRO_1, SAY_AGGRO_2));

                if (instance)
                {
                    instance->SetBossState(BOSS_ECHO_OF_JAINA, IN_PROGRESS);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add
                }

                events.ScheduleEvent(EVENT_PYROBLAST, urand(2000, 3000));
                events.ScheduleEvent(EVENT_BLINK, urand(28000, 31000));
                events.ScheduleEvent(EVENT_FLARECORE, urand(14000, 17000));
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_PYROBLAST:
                            DoCastVictim(SPELL_PYROBLAST);
                            events.ScheduleEvent(EVENT_PYROBLAST, urand(3500, 4500));
                            break;

                        case EVENT_FLARECORE:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(target, SPELL_FLARECORE_MISSILE);
                            events.ScheduleEvent(EVENT_FLARECORE, urand(19000, 21000));
                            break;

                        case EVENT_BLINK:
                            Talk(SAY_BLINK);
                            DoCast(me, SPELL_BLINK);
                            if (Creature* blink = me->FindNearestCreature(NPC_BLINK_TARGT, 200.0f, true))
                                me->NearTeleportTo(blink->GetPositionX(), blink->GetPositionY(), blink->GetPositionZ(), blink->GetOrientation());
                            events.CancelEvent(EVENT_PYROBLAST);
                            events.CancelEvent(EVENT_FLARECORE);
                            events.ScheduleEvent(EVENT_FROST_BLADES, 1500);
                            events.ScheduleEvent(EVENT_FROSTBOLT_VOLLEY, 2000);
                            events.ScheduleEvent(EVENT_BLINK, 31500);
                            break;

                        case EVENT_FROSTBOLT_VOLLEY:
                            if(VolleyCount < 3)
                            {
                                DoCast(me, SPELL_FROSTBOLT_VOLLEY);
                                events.ScheduleEvent(EVENT_FROSTBOLT_VOLLEY, 2200);
                                VolleyCount++;
                            }
                            else
                            {
                                Talk(SAY_FROSTBOLT_VOLLEY);
                                DoCast(me, SPELL_FROSTBOLT_VOLLEY);
                                events.CancelEvent(EVENT_FROSTBOLT_VOLLEY);
                                VolleyCount = 0;
                                events.ScheduleEvent(EVENT_PYROBLAST, urand(3000, 3500));
                                events.ScheduleEvent(EVENT_FLARECORE, urand (7500, 8500));
                            }
                            break;

                        case EVENT_FROST_BLADES:
                            Talk(SAY_FROST_BLADES);
                            me->SummonCreature(NPC_FROSTBLADES, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation() - 0.1f, TEMPSUMMON_TIMED_DESPAWN, 10000);
                            me->SummonCreature(NPC_FROSTBLADES, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 10000);
                            me->SummonCreature(NPC_FROSTBLADES, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation() + 0.1f, TEMPSUMMON_TIMED_DESPAWN, 10000);
                            break;
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_echo_of_jainaAI(creature);
        }
};

class npc_flarecore : public CreatureScript
{
    public:
        npc_flarecore() : CreatureScript("npc_flarecore") { }

        struct npc_flarecoreAI : public ScriptedAI
        {
            npc_flarecoreAI(Creature* creature) : ScriptedAI(creature) 
            {
                instance = me->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;

            void Reset()
            {
                if (!me->HasAura(SPELL_CHECK_PLAYER_DIST))
                    me->AddAura(SPELL_CHECK_PLAYER_DIST, me);
            }

            void EnterCombat(Unit* /*who*/)
            {
                me->SetReactState(REACT_PASSIVE);

                events.ScheduleEvent(EVENT_CHECK_PLAYER, 500);
                events.ScheduleEvent(EVENT_EXPLODE, 10000);
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CHECK_PLAYER:
                        if(me->FindNearestPlayer(5.0f, true))
                        {
                            DoCast(me, SPELL_UNSTABLE_FLARE);
                            me->DespawnOrUnsummon(100);
                        }
                        events.ScheduleEvent(EVENT_CHECK_PLAYER, 500);
                        break;

                        case EVENT_EXPLODE:
                        DoCast(me, SPELL_TIME_EXPIRE_FLARE);
                        me->DespawnOrUnsummon(100);
                        break;
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_flarecoreAI(creature);
        }
};

class go_jaina_staff_fragment : public GameObjectScript
{
    public:
        go_jaina_staff_fragment() : GameObjectScript("go_jaina_staff_fragment") { }

        bool OnGossipHello(Player* player, GameObject* go)
        {
            InstanceScript* instance = go->GetInstanceScript();

            if (FragmentsCount < MAX_FRAGMENTS_COUNT)
            {
                instance->DoUpdateWorldState(WORLDSTATE_FRAGMENTS_COLLECTED, FragmentsCount);
                FragmentsCount++;
                go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_IN_USE);
                player->PlayerTalkClass->ClearMenus();
            }
            else // Fragments reach 16.
            {
                instance->DoUpdateWorldState(WORLDSTATE_FRAGMENTS_COLLECTED, MAX_FRAGMENTS_COUNT);
                instance->instance->SummonCreature(NPC_ECHO_OF_JAINA, JainaSummonPos);
                instance->instance->SummonCreature(NPC_CIRCLE_VIS, JainaSummonPos);
                go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_IN_USE);
            }

            return true;
        }
};

void AddSC_boss_echo_of_jaina()
{
    new boss_echo_of_jaina();
    new npc_flarecore();
    new go_jaina_staff_fragment();
}
