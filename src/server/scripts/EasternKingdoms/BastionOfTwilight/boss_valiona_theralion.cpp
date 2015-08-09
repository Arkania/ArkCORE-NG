/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * Script complete: 99%. ToDo: Nothin'.
 *
 * This file is NOT free software. Third-party users can NOT redistribute 
 * it or modify it. If you find it, you are either hacking something, or very 
 * lucky (presuming someone else managed to hack it).
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ObjectMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"
#include "MapManager.h"
#include "Spell.h"
#include "Vehicle.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "CreatureTextMgr.h"

#include "bastion_of_twilight.h"

#define MAX_DAZZLING_DESTRUCTION_CASTS 3

enum ValionaYells
{
    SAY_VA_DEATH = 2,
    SAY_VA_KILL  = 3,
    SAY_VA_BOUT  = 4,

    SAY_VA_DB    = 5,
    SAY_VA_LAND  = 6
};

enum TheralionYells
{
    SAY_TH_DEATH = 2,
    SAY_TH_KILL  = 3,
    SAY_TH_ENGF  = 4,

    SAY_TH_DAZZ  = 5,
    SAY_TH_LAND  = 6
};

enum Spells
{
    /***** GENERAL *****/

    SPELL_SELF_ROOT         = 42716,
    SPELL_BERSERK           = 47008, // 10 min.

    // Heroic / Twilight Realm stuff.
    SPELL_TWILIGHT_SHIFT_A  = 93053, // Melee trigger aura for both dragons. 5 stacks get next in one min! HEROIC ONLY!
    SPELL_TWILIGHT_SHIFT    = 93051, // Spell, 5 stacks get next in one min! HEROIC ONLY!

    SPELL_SHIFTING_REALITY  = 93055, // Sends you to Twilight Realm (see next spell).
    SPELL_TWILIGHT_REALM    = 74807, // Actual shift aura - Phase 32.
    // Portals
    SPELL_COLLAPSING_PORTAL = 86291, // Every minute, grows larger.
    SPELL_LEAVE_T_REALM     = 74812, // Does not work, need manual removal of above.

    /***** VALIONA *****/

    // Ground
    SPELL_DEVOURING_FLAMES  = 86840,
    SPELL_BLACKOUT          = 86788,

    // Air
    SPELL_TW_METEOR_TARGET  = 88518,
    SPELL_TW_METEOR         = 86013,

    SPELL_DEEP_BREATH_DUMMY = 78954, // See Valiona doing magical things with her tongue!
    SPELL_DEEP_BREATH       = 86059, // Does nothing, script effect. Valiona should trigger Twilight Flames three times and fill 1/3 of a room with this before landing.
    SPELL_SUM_TWIL_FLAMES   = 75931, // Summon mob. 75932.
    SPELL_TWILIGHT_FLAMES   = 86199, // Actual damage and effect(86202 for screen eff and 86214 for damage taken in twilight zone, trig by 86210), trig by 86194.
    // This and 86228 need 8 y radius.
    SPELL_TW_FLAMES_TRIGGER = 86194, // Trigger for tw flames every sec.
    SPELL_TWILIGHT_ZONE     = 86202, // Screen eff, phase and make obj visible. - WRONG.
    SPELL_TWILIGHT_ZONE_AUR = 86210, // Aura triggers 86214 every 2 sec for 5k damage and shadow incr 10% in T.R. HEROIC ONLY!

    /***** THERALION *****/

    // Ground
    SPELL_ENGULFING_MAGIC   = 86622,
    SPELL_FABULOUS_FLAMES   = 86497,

    // Air
    SPELL_TWILIGHT_BLAST    = 86369,
    SPELL_DAZZ_DESTRUCTION_DUMMY    = 86408,
    SPELL_DAZZ_DESTRUCTION_MISSILE  = 86386,
    SPELL_DAZZ_DESTRUCTION_SUMMON   = 86385,

    /***** MISC *****/
    SPELL_TWIL_PROTECT_BUFF = 86415, // Connected somehow to 86199 (tw flames).

    // Twilight Sentry
    SPELL_TWILIGHT_RIFT     = 93010, // Trigg 93019 dmg spell every 3 secs. - 93019 needs 30 yard radius.
    SPELL_SUM_TW_RIFT_ORBS  = 93017, // Summon some weird orbs.

    // Unstable Twilight
    SPELL_VISUAL_UT         = 103766,
    SPELL_UNSTABLE_TWILIGHT = 86305, // Needs 8 y radius.

    // Dazzling Destruction Stalker
    SPELL_DAZZLING_VISUAL   = 86383,

    // Fabulous Flames
   SPELL_FABULOUS_VISUAL    = 86506
};

enum Events
{
    /***** GENERAL *****/
    EVENT_BERSERK = 1,

    /***** VALIONA *****/
    EVENT_DEVOURING_FLAMES,
    EVENT_BLACKOUT,

    EVENT_TWILIGHT_METEOR,
    EVENT_SEND_TWILIGHT,
    EVENT_DEEP_BREATH, // Move 10 sec
    EVENT_BREATH_DUMMY, // Spit flames!

    EVENT_BREATH_1, // Dummy, move, place the shit. 3 times.
    EVENT_BREATH_2,
    EVENT_BREATH_3,

    EVENT_MOVE_BREATH_1,
    EVENT_MOVE_BREATH_2,

    EVENT_SUMMON_MOBS_1,
    EVENT_SUMMON_MOBS_2,
    EVENT_SUMMON_MOBS_3,

    /***** THERALION *****/
    EVENT_ENGULFING_MAGIC,
    EVENT_FABULOUS_FLAMES,

    EVENT_TWILIGHT_BLAST,
    EVENT_DAZZLING_DESTRUCTION,

    /***** HEROIC *****/
    EVENT_TWILIGHT_SHIFT,

    /***** MISC *****/
    // Ground phase
    EVENT_LIFTOFF,
    EVENT_FLIGHT, // unused solo
    EVENT_AIR, // unused solo

    // Air phase
    EVENT_LAND,
    EVENT_RETURN,
    EVENT_GROUND,

    // Mobs
    EVENT_DESPAWN,
    EVENT_TWILIGHT_RIFT_SUMMON,
    EVENT_TWILIGHT_RIFT,
    EVENT_UNSTABLE_TWILIGHT,
    EVENT_COLLAPSING_PORTAL
};

/*
Valiona Phase: Valiona is on the ground and Theralion is in the air.
Theralion Phase: Theralion is on the ground, and Valiona is in the air.
Valiona Phase lasts 100 seconds, Theralion Phase lasts 140 seconds.
*/

enum Phases
{
    PHASE_NULL = 0,
    PHASE_GROUND,
    PHASE_FLIGHT
};

enum Creatures
{
    NPC_TWILIGHT_SENTRY          = 50008, // T. Realm, HEROIC ONLY!
    NPC_DAZZ_DESTRUCTION_STALKER = 46374,
    NPC_UNSTABLE_TWILIGHT        = 46304,
    NPC_TWILIGHT_RIFT            = 50014,
    NPC_COLLAPSING_TW_PORTAL     = 46301,
    NPC_TWILIGHT_FLAME           = 40718
};

enum Actions
{
    ACTION_THERALION_TAKEOFF     = 1,
    ACTION_THERALION_LAND
};

Position const TwilFlamePos[90] = // 15 per row, 2 rows per side, 3 sides.
{
// 1-30 for entrance, first breath.
{-726.185f, -768.217f, 836.6880f},
{-712.927f, -759.297f, 836.688f},
{-729.71f, -750.193f, 836.693f},
{-718.571f, -735.144f, 836.696f},
{-731.519f, -729.622f, 835.106f},
{-720.204f, -715.33f, 832.281f},
{-718.553f, -702.101f, 831.897f},
{-718.308f, -688.416f, 831.891f},
{-719.734f, -676.143f, 831.892f},
{-721.456f, -661.333f, 831.897f},
{-722.821f, -649.582f, 833.176f},
{-719.32f, -637.6f, 836.699f},
{-723.196f, -622.605f, 836.692f},
{-716.657f, -611.672f, 836.688f},
{-715.665f, -600.11f, 836.685f},
{-722.079f, -618.628f, 836.69f},
{-709.057f, -668.355f, 831.899f},
{-707.799f, -701.244f, 831.899f},
{-711.942f, -719.573f, 834.601f},
{-730.262f, -715.065f, 831.901f},
{-731.211f, -703.507f, 831.896f},
{-731.271f, -696.279f, 831.893f},
{-731.779f, -684.027f, 831.889f},
{-730.221f, -670.001f, 831.894f},
{-731.618f, -660.124f, 831.897f},
{-733.132f, -649.415f, 832.364f},
{-733.703f, -636.535f, 835.993f},
{-729.895f, -622.403f, 836.696f},
{-727.821f, -609.092f, 836.692f},
{-725.244f, -632.255f, 836.699f},
// 30-60 for mid
{-738.228f, -774.297f, 836.687f},
{-747.187f, -711.44f, 831.897f},
{-746.532f, -691.806f, 831.891f},
{-746.461f, -681.971f, 831.89f},
{-746.909f, -771.366f, 836.687f},
{-746.978f, -668.307f, 831.893f},
{-746.207f, -646.622f, 833.052f},
{-750.661f, -735.852f, 836.699f},
{-744.774f, -629.426f, 836.697f},
{-740.922f, -601.492f, 836.688f},
{-734.556f, -756.46f, 836.693f},
{-749.818f, -751.318f, 836.694f},
{-742.449f, -759.696f, 836.692f},
{-741.821f, -746.749f, 836.698f},
{-742.275f, -735.698f, 836.699f},
{-739.995f, -725.004f, 833.588f},
{-741.421f, -713.62f, 831.898f},
{-740.577f, -702.188f, 831.893f},
{-739.815f, -691.874f, 831.891f},
{-739.103f, -682.223f, 831.89f},
{-738.46f, -673.514f, 831.893f},
{-737.876f, -665.608f, 831.896f},
{-737.234f, -656.916f, 831.899f},
{-736.475f, -646.637f, 833.048f},
{-735.778f, -637.195f, 835.802f},
{-735.17f, -628.958f, 836.697f},
{-734.6f, -621.244f, 836.695f},
{-749.068f, -724.66f, 833.581f},
{-732.867f, -608.092f, 836.691f},
{-732.764f, -596.374f, 836.687f},
// 60-90 for exit
{-766.844f, -614.003f, 836.689f},
{-751.849f, -608.325f, 836.689f},
{-755.589f, -627.736f, 836.695f},
{-765.266f, -635.142f, 836.698f},
{-755.655f, -640.214f, 835.515f},
{-763.859f, -648.017f, 834.242f},
{-774.417f, -650.346f, 835.237f},
{-767.926f, -656.699f, 832.59f},
{-756.128f, -657.912f, 831.899f},
{-749.862f, -670.31f, 831.896f},
{-759.005f, -666.729f, 831.897f},
{-768.303f, -664.93f, 831.897f},
{-767.196f, -675.072f, 831.892f},
{-754.611f, -678.247f, 831.891f},
{-754.229f, -690.564f, 831.891f},
{-760.611f, -683.775f, 831.889f},
{-774.04f, -682.983f, 831.89f},
{-781.804f, -686.498f, 831.898f},
{-770.858f, -691.417f, 831.893f},
{-761.664f, -694.862f, 831.893f},
{-752.508f, -699.213f, 831.894f},
{-760.785f, -706.285f, 831.898f},
{-771.937f, -701.638f, 831.899f},
{-770.358f, -714.257f, 833.268f},
{-756.803f, -721.699f, 833.392f},
{-773.318f, -730.829f, 836.696f},
{-756.708f, -737.369f, 836.696f},
{-756.39f, -753.955f, 836.691f},
{-759.558f, -765.119f, 836.686f},
{-768.016f, -756.87f, 836.686f}
};

// 45992
class boss_valiona_bot : public CreatureScript
{
public:
    boss_valiona_bot() : CreatureScript("boss_valiona_bot") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_valiona_botAI(creature);
    }

    struct boss_valiona_botAI : public BossAI
    {
        boss_valiona_botAI(Creature* creature) : BossAI(creature, DATA_VALIONA_THERALION), summons(me)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        Phases phase;
        SummonList summons;
        bool castBlackout;
        Unit* meteorTarget;

        void Reset()
        {
            phase = PHASE_NULL;

            if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == POINT_MOTION_TYPE)
                me->GetMotionMaster()->MovementExpired();

            if (instance)
                instance->SetBossState(DATA_VALIONA_THERALION, NOT_STARTED);

            castBlackout = false;

            me->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
            me->RemoveUnitMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);
            me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_TWILIGHT_ZONE, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_TWILIGHT_REALM, true);

            summons.DespawnAll();

            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            EnterPhaseGround();

            if (instance)
            {
                instance->SetBossState(DATA_VALIONA_THERALION, IN_PROGRESS);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add
            }

            castBlackout = false;

            if (Creature* Theralion = me->FindNearestCreature(NPC_THERALION_BOT, 500.0f, true))
                if (Theralion && !Theralion->IsInCombat())
                    Theralion->AI()->AttackStart(me->GetVictim());

            if (me->GetMap()->IsHeroic())
                SetSentriesInCombat();

            events.ScheduleEvent(EVENT_BERSERK, 600000);

            SetUnstableInCombat();

            _EnterCombat();
        }

        void SetSentriesInCombat()
        {
            std::list<Creature*> creatures;
            me->GetCreatureListWithEntryInGrid(creatures, NPC_TWILIGHT_SENTRY, 1000.0f);

            if (creatures.empty())
               return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->SetInCombatWithZone(); // Set Twilight Realm sentries in combat.
        }

        void SetUnstableInCombat()
        {
            std::list<Creature*> creatures;
            me->GetCreatureListWithEntryInGrid(creatures, NPC_UNSTABLE_TWILIGHT, 1000.0f);

            if (creatures.empty())
               return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->SetInCombatWithZone(); // Set Unstable Twilight orbs in combat.
        }

        void initEvents(bool onGround = true)
        {
            events.Reset();

            if(onGround)
            {
                events.ScheduleEvent(EVENT_BLACKOUT, 5000, PHASE_GROUND); // 40 sec cd
                events.ScheduleEvent(EVENT_DEVOURING_FLAMES, 30000, PHASE_GROUND); // 40 sec cd
                events.ScheduleEvent(EVENT_LIFTOFF, 100000, PHASE_GROUND);
                if(me->GetMap()->IsHeroic())
                    events.ScheduleEvent(EVENT_TWILIGHT_SHIFT, 20000, PHASE_GROUND);
            }else
            {
                events.ScheduleEvent(EVENT_TWILIGHT_METEOR, 12000, PHASE_FLIGHT); // 15 times, every 6 secs.
                events.ScheduleEvent(EVENT_DEEP_BREATH, 85000, PHASE_FLIGHT); // 10 sec to get there, lasts 45 seconds, 15 per flight on a part, 3 parts : entrance, middle, exit.
                events.ScheduleEvent(EVENT_LAND, 140000, PHASE_FLIGHT);
            }
        }

        void EnterEvadeMode()
        {
            Reset();

            me->GetMotionMaster()->MoveTargetedHome();

            if (instance)
            {
                instance->SetBossState(DATA_VALIONA_THERALION, FAIL);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            _EnterEvadeMode();
        }

        void EnterPhaseGround()
        {
            phase = PHASE_GROUND;
            me->SetReactState(REACT_AGGRESSIVE);
            me->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
            me->RemoveUnitMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);
            events.SetPhase(PHASE_GROUND);
            initEvents(true);
        }

        void EnterPhaseAir()
        {
            phase = PHASE_FLIGHT;
            me->SetReactState(REACT_PASSIVE);
            me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
            me->AddUnitMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);
            events.SetPhase(PHASE_FLIGHT);
            initEvents(false);
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
            summon->setActive(true);

            if(me->IsInCombat())
            summon->AI()->DoZoneInCombat();
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_VA_DEATH);

            if (instance)
            {
                instance->SetBossState(DATA_VALIONA_THERALION, DONE);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_SHIFT_A);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_SHIFT);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_SHIFTING_REALITY);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_ZONE);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_REALM);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_ZONE_AUR);
            }

            if (Creature* theralion = me->FindNearestCreature(NPC_THERALION_BOT, 500.0f, true))
                theralion->Kill(theralion);

            _JustDied();
        }

        void KilledUnit(Unit* /*victim*/)
        {
            Talk(SAY_VA_KILL);
        }

        void DamageTaken(Unit* /*who*/, uint32& damage)
        {
            if(Creature* theralion = me->FindNearestCreature(NPC_THERALION_BOT, 500.0f, true))
                theralion->SetHealth(theralion->GetHealth() - damage);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING) || !phase)
                return;

            events.Update(diff);

            if (phase == PHASE_GROUND) // Ground phase
            {
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_BERSERK:
                            DoCast(me, SPELL_BERSERK);
                            break;
                        case EVENT_LIFTOFF:
                            me->HandleEmote(EMOTE_ONESHOT_LIFTOFF);
                            me->SetDisableGravity(true);
                            if (Creature* Theralion = me->FindNearestCreature(NPC_THERALION_BOT, 500.0f, true))
                                Theralion->AI()->DoAction(ACTION_THERALION_LAND);
                            events.ScheduleEvent(EVENT_FLIGHT, 1500);
                            events.ScheduleEvent(EVENT_AIR, 2000);
                            break;
                        case EVENT_FLIGHT:
                            me->SetReactState(REACT_PASSIVE);
                            me->AttackStop();
                            me->GetMotionMaster()->MovePoint(1, -741.065f, -684.987f, me->GetPositionZ() + 25.0f);
                            break;
                        case EVENT_AIR:
                            EnterPhaseAir();
                            break;
                        case EVENT_BLACKOUT:
                            if (!castBlackout)
                                castBlackout = true;
                            else if (castBlackout)
                            {
                                 if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.0f, true))
                                    DoCast(target, SPELL_BLACKOUT);
                                    Talk(SAY_VA_BOUT);
                            }
                            events.ScheduleEvent(EVENT_BLACKOUT, 40000, PHASE_GROUND);
                            break;
                        case EVENT_DEVOURING_FLAMES:
                            DoCast(me, SPELL_DEVOURING_FLAMES);
                            events.ScheduleEvent(EVENT_DEVOURING_FLAMES, 40000, PHASE_GROUND);
                            break;
                        case EVENT_TWILIGHT_SHIFT:
                            if (!me->GetVictim()->HasAura(SPELL_TWILIGHT_SHIFT))
                                DoCastVictim(SPELL_TWILIGHT_SHIFT);
                            else
                            if (Aura * aura = me->GetVictim()->GetAura(SPELL_TWILIGHT_SHIFT))
                            {
                                if (aura->GetStackAmount() < 5)
                                    DoCastVictim(SPELL_TWILIGHT_SHIFT);
                                else
                                {
                                    me->GetVictim()->RemoveAura(SPELL_TWILIGHT_SHIFT);
                                    me->AddAura(SPELL_TWILIGHT_ZONE, me->GetVictim()); // Send target to Twilight Realm.
                                    me->AddAura(SPELL_TWILIGHT_REALM, me->GetVictim()); // Send target to Twilight Realm.

                                    if (me->GetMap()->IsHeroic())
                                        me->AddAura(SPELL_TWILIGHT_ZONE_AUR, me->GetVictim()); // Twilight Realm damage debuff.
                                }
                            }
                            events.ScheduleEvent(EVENT_TWILIGHT_SHIFT, 20000, PHASE_GROUND);
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
            else if (phase == PHASE_FLIGHT) // Air phase
            {
                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_LAND:
                            Talk(SAY_VA_LAND);
                            me->SetSpeed(MOVE_WALK, 1.0f, true);
                            me->SetSpeed(MOVE_RUN, 1.0f, true);
                            me->SetSpeed(MOVE_FLIGHT, 1.0f, true);
                            events.CancelEvent(EVENT_BREATH_DUMMY); // Cancel the breaths.
                            me->HandleEmote(EMOTE_ONESHOT_LAND);
                            me->SetDisableGravity(false);
                            if (Creature* Theralion = me->FindNearestCreature(NPC_THERALION_BOT, 500.0f, true))
                                Theralion->AI()->DoAction(ACTION_THERALION_TAKEOFF);
                            events.ScheduleEvent(EVENT_RETURN, 1000);
                            events.ScheduleEvent(EVENT_GROUND, 1500);
                            break;
                        case EVENT_RETURN:
                            me->SetReactState(REACT_PASSIVE);
                            me->AttackStop();
                            me->GetMotionMaster()->MovePoint(1, -741.065f, -684.987f, me->GetPositionZ() - 25.0f);
                            break;
                        case EVENT_GROUND:
                            EnterPhaseGround();
                            break;
                        case EVENT_TWILIGHT_METEOR:
                             if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.0f, true))
                            {
                                me->AddAura(SPELL_TW_METEOR_TARGET, target);
                                DoCast(target, SPELL_TW_METEOR);
                                meteorTarget = target;
                            }
                            events.ScheduleEvent(EVENT_TWILIGHT_METEOR, 6100, PHASE_FLIGHT);
                            events.ScheduleEvent(EVENT_SEND_TWILIGHT, 6100, PHASE_FLIGHT);
                            break;
                        case EVENT_SEND_TWILIGHT:
                            if (meteorTarget)
                            {
                                me->AddAura(SPELL_TWILIGHT_ZONE, meteorTarget); // Send target to Twilight Realm.
                                me->AddAura(SPELL_TWILIGHT_REALM, meteorTarget); // Send target to Twilight Realm.

                                if (me->GetMap()->IsHeroic())
                                    me->AddAura(SPELL_TWILIGHT_ZONE_AUR, meteorTarget); // Twilight Realm damage debuff.
                            }
                            break;
                        case EVENT_DEEP_BREATH:
                            Talk(SAY_VA_DB);
                            me->SetSpeed(MOVE_WALK, 2.7f, true);
                            me->SetSpeed(MOVE_RUN, 2.7f, true);
                            me->SetSpeed(MOVE_FLIGHT, 2.7f, true);
                            events.CancelEvent(EVENT_TWILIGHT_METEOR);
                            me->GetMotionMaster()->MovePoint(1, -723.525f, -769.260f, me->GetPositionZ());
                            events.ScheduleEvent(EVENT_BREATH_1, 10000, PHASE_FLIGHT);
                            break;
                        case EVENT_BREATH_1:
                            me->GetMotionMaster()->MovePoint(1, -725.077f, -613.762f, me->GetPositionZ());
                            events.ScheduleEvent(EVENT_BREATH_DUMMY, 3000, PHASE_FLIGHT); // lasts 3 sec.
                            events.ScheduleEvent(EVENT_SUMMON_MOBS_1, 11000, PHASE_FLIGHT); // lasts 3 sec.
                            events.ScheduleEvent(EVENT_MOVE_BREATH_1, 13000, PHASE_FLIGHT); // must move in 13000 long side-side.
                            break;
                        case EVENT_SUMMON_MOBS_1:
                            for(int i=1; i<31; i++)
                            me->SummonCreature(NPC_TWILIGHT_FLAME,TwilFlamePos[i].GetPositionX()
                                ,TwilFlamePos[i].GetPositionY(),TwilFlamePos[i].GetPositionZ(),TEMPSUMMON_CORPSE_DESPAWN);
                            break;
                        case EVENT_MOVE_BREATH_1:
                            me->GetMotionMaster()->MovePoint(1, -740.447f, -612.804f, me->GetPositionZ());
                            events.ScheduleEvent(EVENT_BREATH_2, 2000, PHASE_FLIGHT);
                            break;
                        case EVENT_BREATH_2:
                            me->GetMotionMaster()->MovePoint(1, -738.849f, -769.072f, me->GetPositionZ());
                            events.ScheduleEvent(EVENT_SUMMON_MOBS_2, 11000, PHASE_FLIGHT); // lasts 3 sec.
                            events.ScheduleEvent(EVENT_MOVE_BREATH_2, 13000, PHASE_FLIGHT); // must move in 13000 long side-side.
                            break;
                        case EVENT_SUMMON_MOBS_2:
                            for(int i=31; i<61; i++)
                            me->SummonCreature(NPC_TWILIGHT_FLAME,TwilFlamePos[i].GetPositionX()
                                ,TwilFlamePos[i].GetPositionY(),TwilFlamePos[i].GetPositionZ(),TEMPSUMMON_CORPSE_DESPAWN);
                            break;
                        case EVENT_MOVE_BREATH_2:
                            me->GetMotionMaster()->MovePoint(1, -757.691f, -766.305f, me->GetPositionZ());
                            events.ScheduleEvent(EVENT_BREATH_3, 2000, PHASE_FLIGHT);
                            break;
                        case EVENT_BREATH_3:
                            me->GetMotionMaster()->MovePoint(1, -763.181f, -626.995f, me->GetPositionZ());
                            events.ScheduleEvent(EVENT_SUMMON_MOBS_3, 11000, PHASE_FLIGHT); // lasts 3 sec.
                            break;
                        case EVENT_SUMMON_MOBS_3:
                            for(int i=61; i<91; i++)
                            me->SummonCreature(NPC_TWILIGHT_FLAME,TwilFlamePos[i].GetPositionX()
                                ,TwilFlamePos[i].GetPositionY(),TwilFlamePos[i].GetPositionZ(),TEMPSUMMON_CORPSE_DESPAWN);
                            break;
                        case EVENT_BREATH_DUMMY:
                            DoCast(me, SPELL_DEEP_BREATH_DUMMY);
                            events.ScheduleEvent(EVENT_BREATH_DUMMY, 3000, PHASE_FLIGHT);
                            break;
                    }
                }
            }
        }
    };
};

// 45993
class boss_theralion_bot : public CreatureScript
{
public:
    boss_theralion_bot() : CreatureScript("boss_theralion_bot") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_theralion_botAI(creature);
    }

    struct boss_theralion_botAI : public BossAI
    {
        boss_theralion_botAI(Creature* creature) : BossAI(creature, DATA_VALIONA_THERALION), summons(me)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        Phases phase;
        SummonList summons;
        uint32 uiDazzlingDestructionCount;

        void Reset()
        {
            phase = PHASE_NULL;

            if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == POINT_MOTION_TYPE)
                me->GetMotionMaster()->MovementExpired();

            me->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
            me->RemoveUnitMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);
            me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_TWILIGHT_ZONE, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_TWILIGHT_REALM, true);

            uiDazzlingDestructionCount = 0;

            summons.DespawnAll();

            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add

            uiDazzlingDestructionCount = 0;

            if (Creature* Valiona = me->FindNearestCreature(NPC_VALIONA_BOT, 500.0f, true))
                if(Valiona && !Valiona->IsInCombat())
                    Valiona->AI()->AttackStart(me->GetVictim());

            phase = PHASE_GROUND;
            events.SetPhase(PHASE_GROUND);
            events.ScheduleEvent(EVENT_LIFTOFF, 1000, PHASE_GROUND);

            events.ScheduleEvent(EVENT_BERSERK, 600000);

            _EnterCombat();
        }

		void DoAction(int32 action) override
        {
            switch(action)
            {
                case ACTION_THERALION_TAKEOFF:
                    events.ScheduleEvent(EVENT_LIFTOFF, 100, PHASE_GROUND);
                    break;

                case ACTION_THERALION_LAND:
                    events.ScheduleEvent(EVENT_LAND, 100, PHASE_FLIGHT);
                    break;

                default:
                    break;
            }
        }

        void initEvents(bool onGround = true)
        {
            events.Reset();

            if(onGround)
            {
                events.ScheduleEvent(EVENT_ENGULFING_MAGIC, 10000, PHASE_GROUND); // 30 sec cooldown
                events.ScheduleEvent(EVENT_FABULOUS_FLAMES, 15000, PHASE_GROUND); // every 15 sec
                if(me->GetMap()->IsHeroic())
                    events.ScheduleEvent(EVENT_TWILIGHT_SHIFT, 20000, PHASE_GROUND);
            }else
            {
                events.ScheduleEvent(EVENT_TWILIGHT_BLAST, 10000, PHASE_FLIGHT);
                events.ScheduleEvent(EVENT_DAZZLING_DESTRUCTION, 73000, PHASE_FLIGHT);
            }
        }

        void EnterEvadeMode()
        {
            Reset();

            me->GetMotionMaster()->MoveTargetedHome();

            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove

            _EnterEvadeMode();
        }

        void EnterPhaseGround()
        {
            phase = PHASE_GROUND;
            me->SetReactState(REACT_AGGRESSIVE);
            me->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
            me->RemoveUnitMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);
            events.SetPhase(PHASE_GROUND);
            initEvents(true);
        }

        void EnterPhaseAir()
        {
            phase = PHASE_FLIGHT;
            me->SetReactState(REACT_PASSIVE);
            me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
            me->AddUnitMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);
            events.SetPhase(PHASE_FLIGHT);
            initEvents(false);
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
            summon->setActive(true);

            if(me->IsInCombat())
            summon->AI()->DoZoneInCombat();
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_TH_DEATH);

            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove

            if (Creature* Valiona = me->FindNearestCreature(NPC_VALIONA_BOT, 500.0f, true))
                Valiona->Kill(Valiona);

            _JustDied();
        }

        void KilledUnit(Unit* /*victim*/)
        {
            Talk(SAY_TH_KILL);
        }

        void DamageTaken(Unit* /*who*/, uint32& damage)
        {
            if(Creature* valiona = me->FindNearestCreature(NPC_VALIONA_BOT, 500.0f, true))
                valiona->SetHealth(valiona->GetHealth() - damage);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (!phase)
                return;

            events.Update(diff);

            if (phase == PHASE_GROUND) // Ground phase
            {
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_BERSERK:
                            DoCast(me, SPELL_BERSERK);
                            break;

                        case EVENT_LIFTOFF:
                            me->HandleEmote(EMOTE_ONESHOT_LIFTOFF);
                            me->SetDisableGravity(true);
                            events.ScheduleEvent(EVENT_FLIGHT, 1500);
                            events.ScheduleEvent(EVENT_AIR, 2000);
                            break;

                        case EVENT_FLIGHT:
                            me->SetReactState(REACT_PASSIVE);
                            me->AttackStop();
                            me->GetMotionMaster()->MovePoint(1, -741.065f, -684.987f, me->GetPositionZ() + 25.0f);
                            break;

                        case EVENT_AIR:
                            EnterPhaseAir();
                            break;

                        case EVENT_ENGULFING_MAGIC:
                            Talk(SAY_TH_ENGF);
                            if (me->GetMap()->IsHeroic())
                            {
                                std::list<Unit*> targets;
                                SelectTargetList(targets, NonTankTargetSelector(me), RAID_MODE(1, 3, 1, 3), SELECT_TARGET_RANDOM);
                                if (!targets.empty())
                                    for (std::list<Unit*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                                        me->AddAura(SPELL_ENGULFING_MAGIC, (*itr));
                            }
                            else if (!me->GetMap()->IsHeroic())
                                 if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.0f, true))
                                    me->AddAura(SPELL_ENGULFING_MAGIC, target);
                            events.ScheduleEvent(EVENT_ENGULFING_MAGIC, 30000, PHASE_GROUND);
                            break;

                        case EVENT_FABULOUS_FLAMES:
                             if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.0f, true))
                                DoCast(target, SPELL_FABULOUS_FLAMES);
                            events.ScheduleEvent(EVENT_FABULOUS_FLAMES, 15000, PHASE_GROUND);
                            break;

                        case EVENT_TWILIGHT_SHIFT:
                            if (!me->GetVictim()->HasAura(SPELL_TWILIGHT_SHIFT))
                                DoCastVictim(SPELL_TWILIGHT_SHIFT);
                            else
                            if (Aura * aura = me->GetVictim()->GetAura(SPELL_TWILIGHT_SHIFT))
                            {
                                if (aura->GetStackAmount() < 5)
                                    DoCastVictim(SPELL_TWILIGHT_SHIFT);
                                else
                                {
                                    me->GetVictim()->RemoveAura(SPELL_TWILIGHT_SHIFT);
                                    me->AddAura(SPELL_TWILIGHT_ZONE, me->GetVictim()); // Send target to Twilight Realm.
                                    me->AddAura(SPELL_TWILIGHT_REALM, me->GetVictim()); // Send target to Twilight Realm.

                                    if (me->GetMap()->IsHeroic())
                                        me->AddAura(SPELL_TWILIGHT_ZONE_AUR, me->GetVictim()); // Twilight Realm damage debuff.
                                }
                            }
                            events.ScheduleEvent(EVENT_TWILIGHT_SHIFT, 20000, PHASE_GROUND);
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
            else if (phase == PHASE_FLIGHT) // Air phase
            {
                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_LAND:
                            Talk(SAY_TH_LAND);
                            me->HandleEmote(EMOTE_ONESHOT_LAND);
                            me->SetDisableGravity(false);
                            events.ScheduleEvent(EVENT_RETURN, 1000);
                            events.ScheduleEvent(EVENT_GROUND, 1500);
                            break;

                        case EVENT_RETURN:
                            me->SetReactState(REACT_PASSIVE);
                            me->AttackStop();
                            me->GetMotionMaster()->MovePoint(1, -741.065f, -684.987f, me->GetPositionZ() - 25.0f);
                            break;

                        case EVENT_GROUND:
                            EnterPhaseGround();
                            break;

                        case EVENT_TWILIGHT_BLAST:
                             if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.0f, true))
                                DoCast(target, SPELL_TWILIGHT_BLAST);
                            events.ScheduleEvent(EVENT_TWILIGHT_BLAST, 5000, PHASE_FLIGHT);
                            break;

                        case EVENT_DAZZLING_DESTRUCTION: // 2 sec timer, summon 6 then cast.
                        {
                            Talk(SAY_TH_DAZZ);
                            events.CancelEvent(EVENT_TWILIGHT_BLAST);

                            if (uiDazzlingDestructionCount < MAX_DAZZLING_DESTRUCTION_CASTS)
                            {
                                Unit* Target1 = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.0f, true);
                                Unit* Target2 = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.0f, true);

                                if (!Target1 || !Target2)
                                    return;

                                if (Target1 == Target2)
                                    Target2 = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.0f, true);

                                me->CastSpell(Target1->GetPositionX(), Target1->GetPositionY(), Target1->GetPositionZ(), SPELL_DAZZ_DESTRUCTION_SUMMON, false);
                                me->CastSpell(Target2->GetPositionX(), Target2->GetPositionY(), Target2->GetPositionZ(), SPELL_DAZZ_DESTRUCTION_SUMMON, false);

                                DoCast(me, SPELL_DAZZ_DESTRUCTION_DUMMY);
                                uiDazzlingDestructionCount++;

                                events.ScheduleEvent(EVENT_DAZZLING_DESTRUCTION, 3100, PHASE_FLIGHT);
                            }
                            else
                            {
                                events.CancelEvent(EVENT_DAZZLING_DESTRUCTION);
                                uiDazzlingDestructionCount = 0; // Revert to initial count for next phase.
                            }
                        }
                        break;
                    }
                }
            }
        }

    private:
    };
};

// 46374
class npc_dazzling_visual : public CreatureScript // 46374
{
public:
    npc_dazzling_visual() : CreatureScript("npc_dazzling_visual") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_dazzling_visualAI (creature);
    }

    struct npc_dazzling_visualAI : public ScriptedAI
    {
        npc_dazzling_visualAI(Creature* creature) : ScriptedAI(creature)
        {
            creature->SetReactState(REACT_PASSIVE);
            instance = creature->GetInstanceScript();
            creature->CastSpell(creature, SPELL_DAZZLING_VISUAL, true);
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.ScheduleEvent(EVENT_DESPAWN, 12000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_DESPAWN:
                        me->DespawnOrUnsummon();
                        return;
                }
            }
        }
    };
};

// 46448
class npc_fabulous_flames : public CreatureScript // 46448
{
public:
    npc_fabulous_flames() : CreatureScript("npc_fabulous_flames") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_fabulous_flamesAI (creature);
    }

    struct npc_fabulous_flamesAI : public ScriptedAI
    {
        npc_fabulous_flamesAI(Creature* creature) : ScriptedAI(creature)
        {
            creature->SetReactState(REACT_PASSIVE);
            instance = creature->GetInstanceScript();
            creature->CastSpell(creature, SPELL_FABULOUS_VISUAL, true);
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.ScheduleEvent(EVENT_DESPAWN, 45000); // Last 45 sec.
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_DESPAWN:
                        me->DespawnOrUnsummon();
                        return;
                }
            }
        }
    };
};

// 50008
class npc_twilight_sentry : public CreatureScript // 50008 - Heroic. Summons Rift every 15 seconds.
{
public:
    npc_twilight_sentry() : CreatureScript("npc_twilight_sentry") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_twilight_sentryAI (creature);
    }

    struct npc_twilight_sentryAI : public ScriptedAI
    {
        npc_twilight_sentryAI(Creature* creature) : ScriptedAI(creature), summons(me)
        {
            instance = creature->GetInstanceScript();
            creature->SetReactState(REACT_PASSIVE);
        }

        InstanceScript* instance;
        EventMap events;
        SummonList summons;

        void Reset()
        {
            events.ScheduleEvent(EVENT_TWILIGHT_RIFT_SUMMON, 1000);
        }

        void JustDied(Unit* /*killer*/)
        {
            summons.DespawnAll();
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TWILIGHT_RIFT_SUMMON:
                        if (Creature* Valiona = me->FindNearestCreature(NPC_VALIONA_BOT, 500.0f, true))
                            if (Valiona && Valiona->IsInCombat())
                            {
                                if (!me->HasAura(SPELL_SUM_TW_RIFT_ORBS))
                                    me->AddAura(SPELL_SUM_TW_RIFT_ORBS, me);
                                me->SummonCreature(NPC_TWILIGHT_RIFT, me->GetPositionX() + frand(1.0f, 20.0f), me->GetPositionY() + frand(1.0f, 20.0f), me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN);
                            }

                        events.ScheduleEvent(EVENT_TWILIGHT_RIFT_SUMMON, 15100);
                        break;
                }
            }
        }
    };
};

// 50014
class npc_twilight_rift : public CreatureScript // 50014 - Heroic. Spawned in Twilight Realm every 15 seconds.
{
public:
    npc_twilight_rift() : CreatureScript("npc_twilight_rift") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_twilight_riftAI (creature);
    }

    struct npc_twilight_riftAI : public ScriptedAI
    {
        npc_twilight_riftAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            creature->SetReactState(REACT_PASSIVE);
            creature->GetMotionMaster()->MoveRandom(50.0f);
            creature->DespawnOrUnsummon(30000);
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.ScheduleEvent(EVENT_TWILIGHT_RIFT, 100);
        }

        void UpdateAI(uint32 diff)
        {
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TWILIGHT_RIFT:
                        DoCast(me, SPELL_TWILIGHT_RIFT);
                        break;
                }
            }
        }
    };
};

// 46304
class npc_unstable_twilight : public CreatureScript // 46304 - Spawned in Twilight Realm explodes on player in 8 yards.
{
public:
    npc_unstable_twilight() : CreatureScript("npc_unstable_twilight") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_unstable_twilightAI (creature);
    }

    struct npc_unstable_twilightAI : public ScriptedAI
    {
        npc_unstable_twilightAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            creature->SetReactState(REACT_PASSIVE);
            creature->SetByteValue(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_HOVER);
            creature->CastSpell(creature, SPELL_VISUAL_UT, true);
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.ScheduleEvent(EVENT_UNSTABLE_TWILIGHT, 1000);
        }

        void UpdateAI(uint32 diff)
        {
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_UNSTABLE_TWILIGHT:
                        if (Player* player = me->FindNearestPlayer(8.0f, true))
                        if(player->IsWithinDistInMap(me, 8.0f))
                        {
                            DoCast(me, SPELL_UNSTABLE_TWILIGHT);
                            me->DespawnOrUnsummon();
                        }
                        events.ScheduleEvent(EVENT_UNSTABLE_TWILIGHT, 1000);
                        break;
                }
            }
        }
    };
};

// 40718
class npc_twilight_flame : public CreatureScript // 40718. Summ by Valiona on deep breaths.
{
public:
    npc_twilight_flame() : CreatureScript("npc_twilight_flame") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_twilight_flameAI (creature);
    }

    struct npc_twilight_flameAI : public ScriptedAI
    {
        npc_twilight_flameAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            creature->SetReactState(REACT_PASSIVE);
            creature->CastSpell(creature, SPELL_TW_FLAMES_TRIGGER, true);
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.ScheduleEvent(EVENT_DESPAWN, 10000);
        }

        void UpdateAI(uint32 diff)
        {
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_DESPAWN:
                        me->DespawnOrUnsummon();
                        return;
                }
            }
        }
    };
};

// 46301
class npc_collapsing_tw_portal : public CreatureScript // 46301
{
public:
    npc_collapsing_tw_portal() : CreatureScript("npc_collapsing_tw_portal") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_collapsing_tw_portalAI (creature);
    }

    struct npc_collapsing_tw_portalAI : public ScriptedAI
    {
        npc_collapsing_tw_portalAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            creature->SetReactState(REACT_PASSIVE);
            creature->CastSpell(creature, SPELL_COLLAPSING_PORTAL, true);
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.ScheduleEvent(EVENT_COLLAPSING_PORTAL, 60000);
        }

        void UpdateAI(uint32 diff)
        {
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_COLLAPSING_PORTAL:
                        DoCast(me, SPELL_COLLAPSING_PORTAL);
                        events.ScheduleEvent(EVENT_COLLAPSING_PORTAL, 60000);
                        break;
                }
            }
        }
    };
};

// 86844 92872 92873 92874
class spell_devouring_flames : public SpellScriptLoader // 92051
{
    public:
        spell_devouring_flames() : SpellScriptLoader("spell_devouring_flames") { }

        class spell_devouring_flames_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_devouring_flames_SpellScript);

            void CalculateDamage(SpellEffIndex /*effIndex*/)
            {
                if (!GetHitUnit())
                    return;

                float distance = GetCaster()->GetDistance2d(GetHitUnit());

                if (!GetHitUnit()->isInFrontInMap(GetCaster(), 100.0f))
                    SetHitDamage(0);

                if (distance > 1.0f)
                    SetHitDamage(int32(GetHitDamage() - (2000 * distance))); // Drops by 2000 for every yard the player is away.

                if (GetHitDamage() < 0) // Don't let it go lower then 0.
                    SetHitDamage(0);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_devouring_flames_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_devouring_flames_SpellScript();
        }
};

// 86408
class spell_dazzling_destruction: public SpellScriptLoader // 86408
{
public:
    spell_dazzling_destruction () :
            SpellScriptLoader("spell_dazzling_destruction") { }

    class spell_dazzling_destructionSpellScript: public SpellScript
    {
        PrepareSpellScript(spell_dazzling_destructionSpellScript);

        bool Validate (SpellInfo const* spellEntry)
        {
            if (!sSpellMgr->GetSpellInfo(spellEntry->Id))
                return false;

            return true;
        }

        bool Load ()
        {
            return true;
        }

        void HandleDummy (SpellEffIndex /*effIndex*/)
        {
            std::list<Creature*> creatures;
            GetCaster()->GetCreatureListWithEntryInGrid(creatures, NPC_DAZZ_DESTRUCTION_STALKER, 1000.0f);

            if (creatures.empty())
               return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                GetCaster()->CastSpell((*iter), 86386, true); // Missile is 86386. Damage spell is 86406 which needs own script to send target to twilight realm.
        }

        void Register ()
        {
            OnEffectHitTarget += SpellEffectFn(spell_dazzling_destructionSpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript * GetSpellScript () const
    {
        return new spell_dazzling_destructionSpellScript();
    }
};

// 86406 92926 92927 92928
class spell_dazzling_missile: public SpellScriptLoader // 86406
{
public:
    spell_dazzling_missile () :
            SpellScriptLoader("spell_dazzling_missile") { }

    class spell_dazzling_missileSpellScript: public SpellScript
    {
        PrepareSpellScript(spell_dazzling_missileSpellScript);

        bool Validate (SpellInfo const* spellEntry)
        {
            if (!sSpellMgr->GetSpellInfo(spellEntry->Id))
                return false;

            return true;
        }

        bool Load ()
        {
            return true;
        }

        void EffectScriptEffect(SpellEffIndex /*effIndex*/)
        {
            GetCaster()->AddAura(SPELL_TWILIGHT_ZONE, GetHitUnit()); // Send target to Twilight Realm.
            GetCaster()->AddAura(SPELL_TWILIGHT_REALM, GetHitUnit()); // Send target to Twilight Realm.

            if (GetCaster()->GetMap()->IsHeroic())
                GetCaster()->AddAura(SPELL_TWILIGHT_ZONE_AUR, GetHitUnit()); // Twilight Realm damage debuff.
        }

        void Register ()
        {
            OnEffectHitTarget += SpellEffectFn(spell_dazzling_missileSpellScript::EffectScriptEffect, EFFECT_2, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript * GetSpellScript () const
    {
        return new spell_dazzling_missileSpellScript();
    }
};

void AddSC_boss_valiona_theralion()
{
    new boss_valiona_bot();
    new boss_theralion_bot();
    new npc_fabulous_flames();
    new npc_dazzling_visual();
    new npc_twilight_sentry();
    new npc_twilight_rift();
    new npc_unstable_twilight();
    new npc_twilight_flame();
    new npc_collapsing_tw_portal();
    new spell_devouring_flames();
    new spell_dazzling_destruction();
    new spell_dazzling_missile();
}