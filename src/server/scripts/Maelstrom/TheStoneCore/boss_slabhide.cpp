/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * THIS particular file is NOT free software; third-party users should 
 * NOT have access to it, redistribute it or modify it.
 * We need to think up a better copyright than this. Who's your third party
 * on the net dude, dude? Should NOT? Er must nicht!
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "stonecore.h"
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

enum Spells
{    
    SPELL_SANDBLAST   = 80807,  //Sandblast spell
    SPELL_LAVA_FISS   = 80803,  //cast on target - on our server it might already be DB scripted and it works fine. Spell Range needs to be added to damage spells 80800 + 80801 - 5yds.
    SPELL_CRYSTAL     = 92565,  //Crystal breath - 2.5 sec cast time + 6 seconds.
    
    SPELL_STALACTITE  = 80656,  //Trigger Multiple Summon Spell
    SPELL_STALAC_VIS  = 80643,  //Multiple effects - triger spell 80647(DMG)
    SPELL_STALAC_WAR  = 80654,  //Warning for where it falls.
    
    SPELL_ERUPTION    = 80800,  //Cast by lava on self. - 80798 might be visual dummy and 80801 periodic
};

enum Events
{
    EVENT_LAVA_FISS = 1,
    EVENT_SANDBLAST,
    EVENT_AIR_PHASE,
    EVENT_FLIGHT,
    EVENT_CRYSTAL,
    EVENT_GROUND,
    EVENT_LAND,
    EVENT_STALACTITE
};

enum Creatures
{
    NPC_LAVA_FISSURE = 43242,
    NPC_STALACTITE   = 43159
};

enum Phases
{
    PHASE_NULL,
    PHASE_GROUND,
    PHASE_AIR
};

/*** Note: Doors are rock stalactites. Starting position is flying outside of platform. Cast AOE stalactite on Line of Sight. ***/

class boss_slabhide : public CreatureScript
{
    public:
        boss_slabhide() : CreatureScript("boss_slabhide") { }

        struct boss_slabhideAI : public BossAI
        {
            boss_slabhideAI(Creature* creature) : BossAI(creature, BOSS_SLABHIDE), summons(me)
            {
                instance = me->GetInstanceScript();
            }

            InstanceScript* instance;
            Phases phase;
            SummonList summons;
            bool introDone, inCombat, introFinished;
            uint32 m_introTimer;
            EventMap events;

            void Reset()
            {
                events.Reset();

                if (instance)
                    instance->SetBossState(BOSS_SLABHIDE, NOT_STARTED);

                introDone = false;
                phase = PHASE_NULL;
                events.SetPhase(PHASE_NULL);
                inCombat = false;
                introFinished = false;
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_PASSIVE);
                me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
                me->AddUnitMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);

                summons.DespawnAll();
            }

            void EnterEvadeMode()
            {
                summons.DespawnAll();
                me->GetMotionMaster()->MoveTargetedHome();
                events.Reset();
                inCombat = false;
                phase = PHASE_NULL;
                events.SetPhase(PHASE_NULL);

                if (instance)
                {
                    instance->SetBossState(BOSS_SLABHIDE, FAIL);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove

                    instance->HandleGameObject(0000000, true); // Open the doors.
                    instance->HandleGameObject(0000000, true);
                }
            }

/*** Note: www.wowhead.com/npc=43357 - This npc might be a trigger for the AOE in the gauntlet. Need to check sniffs. ***/
            void MoveInLineOfSight(Unit* who)
            {
                if (introDone || !me->IsWithinDistInMap(who, 30.0f, false))
                    return;

                if (instance) // Open the doors.
                {
                    instance->HandleGameObject(0000000, true);
                    instance->HandleGameObject(0000000, true);
                }

                DoCastAOE(SPELL_STALACTITE);
                me->GetMotionMaster()->MovePoint(1, 1286.771f, 1237.231f, 247.032f);

                m_introTimer = 15000;
                introDone = true;
            }

            void JustDied(Unit* /*killer*/)
            {
                if (instance)
                {
                    instance->SetBossState(BOSS_SLABHIDE, DONE);

                    instance->HandleGameObject(0000000, true); // Open the doors.
                    instance->HandleGameObject(0000000, true);

                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
                }
            }

            void EnterCombat(Unit* /*who*/)
            {
                if (instance)
                {
                    instance->SetBossState(BOSS_SLABHIDE, IN_PROGRESS);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add

                    instance->HandleGameObject(0000000, false); // Close doors.
                    instance->HandleGameObject(0000000, false);
                }

                phase = PHASE_GROUND;
                events.SetPhase(PHASE_GROUND);
                inCombat = true;

                events.ScheduleEvent(EVENT_SANDBLAST, 4000, PHASE_GROUND);
                events.ScheduleEvent(EVENT_LAVA_FISS, 6000, PHASE_GROUND);
                events.ScheduleEvent(EVENT_AIR_PHASE, 20000, PHASE_GROUND);
            }

            void UpdateAI(uint32 diff)
            {
                if ((!UpdateVictim() && inCombat) || me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (m_introTimer <= diff && !introFinished)
                {
                    introFinished = true;

                    me->SetOrientation(3.864f);
                    me->SetDisableGravity(false);
                    me->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
                    me->RemoveUnitMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->SetReactState(REACT_AGGRESSIVE);
                }
                else
                    m_introTimer -= diff;

                events.Update(diff);

                if (phase == PHASE_GROUND) // Ground phase
                {
                    while (uint32 eventId = events.ExecuteEvent())
                    {
                        switch (eventId)
                        {                   
                            case EVENT_AIR_PHASE:
                                me->HandleEmote(EMOTE_ONESHOT_LIFTOFF);
                                me->SetDisableGravity(true);
                                events.ScheduleEvent(EVENT_FLIGHT, 2000);
                                return;
                                
                            case EVENT_FLIGHT:
                                me->SetReactState(REACT_PASSIVE);
                                me->AttackStop();
                                me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
                                me->AddUnitMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);
                                me->GetMotionMaster()->MovePoint(1, 1275.519f, 1217.723f, me->GetPositionZ() + 15.0f);
                                events.SetPhase(PHASE_AIR);
                                events.ScheduleEvent(EVENT_STALACTITE, 2500, PHASE_AIR);
                                events.ScheduleEvent(EVENT_LAND, 8000, PHASE_AIR);
                                return;

                            case EVENT_SANDBLAST:
                                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
                                        DoCast(target, SPELL_SANDBLAST);
                                events.ScheduleEvent(EVENT_SANDBLAST, urand(6000, 8000), PHASE_GROUND);
                                break;

                            case EVENT_LAVA_FISS:
                                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.0f, true))
                                    DoCast(target, SPELL_LAVA_FISS);
                                events.ScheduleEvent(EVENT_LAVA_FISS, urand(8000, 12000), PHASE_GROUND);
                                break;
                                
                            case EVENT_CRYSTAL:
                                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.0f, true))
                                    DoCast(target, SPELL_CRYSTAL);
                                break;
                        }
                    }

                    DoMeleeAttackIfReady();
                }
                else if (phase == PHASE_AIR) // Air phase
                {
                    if (uint32 eventId = events.ExecuteEvent())
                    {
                        switch (eventId)
                        {
                            case EVENT_LAND:
                                me->HandleEmote(EMOTE_ONESHOT_LAND);
                                me->SetDisableGravity(false);
                                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.0f, true))
                                    me->GetMotionMaster()->MoveChase(target);
                                events.ScheduleEvent(EVENT_GROUND, 2000);
                                return;

                            case EVENT_GROUND:
                                events.SetPhase(PHASE_GROUND);
                                me->SetReactState(REACT_AGGRESSIVE);
                                me->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
                                me->RemoveUnitMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);
                                events.ScheduleEvent(EVENT_SANDBLAST, 6000, PHASE_GROUND);
                                events.ScheduleEvent(EVENT_LAVA_FISS, urand(8000, 12000), PHASE_GROUND);
                                events.ScheduleEvent(EVENT_AIR_PHASE, 30000, PHASE_GROUND);
                                if(IsHeroic())
                                    events.ScheduleEvent(EVENT_CRYSTAL, 1000, PHASE_GROUND);
                                return;

                            case EVENT_STALACTITE:
                                DoCastAOE(SPELL_STALACTITE);
                                break;
                        }
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_slabhideAI(creature);
        }
};

class npc_stalactite : public CreatureScript // 43159
{
public:
    npc_stalactite() : CreatureScript("npc_stalactite") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_stalactiteAI (creature);
    }

    struct npc_stalactiteAI : public ScriptedAI
    {
        npc_stalactiteAI(Creature* creature) : ScriptedAI(creature)
        {
            timerAura    = 100;
            timerImpact  = 4000;
            timerDespawn = 30000;
            vis = false;
            creature->SetReactState(REACT_PASSIVE);
        }

        uint32 timerAura;
        uint32 timerDespawn;
        uint32 timerImpact;
        bool vis;

        void UpdateAI(uint32 diff)
        {
            if (timerAura <= diff)
            {
                DoCast(me, SPELL_STALAC_WAR);
            } else timerAura -= diff;
            
            if (timerImpact <= diff && !vis)
            {
                DoCast(me, SPELL_STALAC_VIS);
                vis = true;
            } else timerImpact -= diff;

            if (timerDespawn <= diff)
            {
                me->DespawnOrUnsummon();
            } else timerDespawn -= diff;
        }
    };
};
    
void AddSC_boss_slabhide()
{
    new boss_slabhide();
    new npc_stalactite();
}
