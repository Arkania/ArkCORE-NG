/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * Script complete: 99%. ToDo:
 * - Intro not working properly
 * - Slicers despawn after summon nothing happens
 * - Calen no fire shield.
 * - Calen visual on orb sinestra not (and no stuff said) -> p3 not possible.
 * - Spell links wrong.
 *
 * This file is NOT free software. Third-party users can NOT redistribute 
 * it or modify it. If you find it, you are either hacking something, or very 
 * lucky (presuming someone else managed to hack it).
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "Vehicle.h"
#include "Unit.h"
#include "ScriptedGossip.h"
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
#include "Vehicle.h"
#include "VehicleDefines.h"
#include "Spell.h"
#include "Player.h"
#include "Map.h"
#include "InstanceScript.h"

#include "bastion_of_twilight.h"

#define GO_CACHE_OF_THE_BROODMOTHER 208044 // loot chest

enum Yells
{
    /***** SINESTRA *****/
    SAY_AGGRO      = 0,  // We were fools to entrust an imbecile like Cho'gall with such a sacred duty. I will deal with you intruders myself!
    SAY_ADDS       = 1,  // Feed, children! Take your fill from their meaty husks!
    SAY_KILL_1     = 2,  // My brood will feed on your bones!
    SAY_KILL_2     = 3,  // Powerless...
    SAY_SPECIAL_1  = 4,  // The energy infused within my clutch is mine to reclaim!
    SAY_SPECIAL_2  = 5,  // SUFFER! / FEEL MY HATRED!
    SAY_PHASE_2    = 6,  // I tire of this. Do you see this clutch amidst which you stand? I have nurtured the spark within them, but that life-force is and always will be mine. Behold, power beyond your comprehension!
    SAY_PHASE_3    = 7,  // Enough! Drawing upon this source will set us back months. You should feel honored to be worthy of its expenditure. Now... die!
    SAY_FIGHT_W    = 8,  // You mistake this for weakness? Fool! 
    SAY_FIGHT_N    = 9,  // This will be your tomb as well as theirs!
    SAY_FIGHT_L    = 10, // My brood will feast upon your essence!
    SAY_DEATH      = 11, // Deathwing! I have fallen.... The brood... is lost.
    SAY_DRAKE      = 12, // Come forth, children of Twilight!
    SAY_SPITECALL  = 13, // YOUR MOTHER CALLS!
    SAY_SLICER     = 14  // Twilight Slicers are active!
};

enum CalenYells
{
    SAY_ENTRANCE   = 0, // Heroes! You are not alone in this dark place!
    SAY_CALEN_W    = 1, // You are weakening, Sintharia! Accept the inevitable!
    SAY_CALEN_N    = 2, // Sintharia! Your master owes me a great debt... one that I intend to extract from his consort's hide! 
    SAY_CALEN_L    = 3, // Heroes! My power wanes....
    SAY_PREMATURE  = 4, // All is lost.... Forgive me, my Queen....
    SAY_RECHARGE   = 5, // Flame of life, burn within me and renew my vigor!
    SAY_CALEN_P3   = 6, // After Sinestra he says - The fires dim, champions.... Take this, the last of my power. Succeed where I have failed. Avenge me. Avenge the world...
};

enum Spells
{
    /***** SINESTRA *****/
    SPELL_SUBMERGED      = 66936,
    SPELL_SUBMERGED_INTR = 96725,

    // Phase 1 - Starts at 60% till 40%.

    /** Drained - Sinestra deals 40% less damage in phase 1 **/
    SPELL_DRAINED        = 89350, // Initial spell with warning

    /** Flame breath **/
    SPELL_FLAME_BREATH   = 90125,

    /** Wrack - Sinestra casts this spell every 30 seconds. Can appear multiple times on target as there are 2 spells, as separate stacks with separate timers.**/
    SPELL_WRACK          = 89421, // Spell + dummy
    SPELL_WRACK_JUMP     = 89435, // Spell with editable damage and changeable timer - to be spell scripted.

    /** Twilight Blast -  Cast when no players are in melee range **/
    SPELL_TWILIGHT_BLAST = 89280, // Repeatedly blasts target until dead then switches to the next one.
    SPELL_TWILIGHT_DUMMY = 87947, // Cast by Sinestra as the dummy spell for the damage 86371

    /** Twilight Slicer Mobs start following individual players. Cast line in between that deals damage to players **/

    /** Mana Barrier - Requires Visual + Spell Script **/
    SPELL_MANA_BARRIER   = 87299,

    /** Channel Spell - Phase 2 **/
    SPELL_TWILIGHT_POWA  = 87220, // Other 78198, in cast first fails

    /** Egg Siphon **/
    SPELL_SIPHON_EGG     = 82354, //definitely not the right visual.

    /** Phase 2 **/
    SPELL_TWI_EXTINCTION = 87945, //Bum-bum motherfucker!
    SPELL_EXTINCT_DUMMY  = 86227, /**Requires spell link to 86226**/

    // Misc
    SPELL_BERSERK        = 47008, // Sinestra has only soft enrage?

    /***** MOBS *****/

    // Shadow Orb
    SPELL_SLICER_DUMMY   = 92851, // The actual spell
    SPELL_SLICER_DAMAGE  = 92852, // 92854 possible alternative. Deals about 54000 in 100 yds. Needs to deal that damage per 0.3 second.
    SPELL_SLICER_PULSE   = 78861, // Cast by the shadow orb on itself

    // Twilight Pulsating Eggs
    SPELL_TWI_CARAPACE   = 87654, // Removed by Sinestra when Siphoning the egg.

    // Twilight Whelps
    SPELL_TWI_SPIT       = 89299, // !Stacks

    // Twilight Essence
    SPELL_TWI_ESSENCE    = 89284, // On death spawns mob, revives whelps on essence. 88146 is spellscripted. 89284 triggers it every 2 seconds.
    SPELL_TWI_INCREASE   = 89288, // Spell that makes essence bigger 15% at a time. 

    // Twilight Drake
    SPELL_TWI_BREATH     = 76817, // Basic spell
    SPELL_ABSORB_ESSENCE = 90107, // !Stacks

    // Twilight Spitecaller
    SPELL_INDOMITABLE    = 90045, // on a check timer of a few minutes
    SPELL_UNLEASH_ESENCE = 90028,

    //Calen
    SPELL_FIRESHIELD     = 95791, // is a 0.4 second cast that requires a spell link to 87229 to be casted at end of cast. - 96431 Visual? spell linked to be cast same time by 87229.
    SPELL_ESSENCE_CALEN  = 87496, // cast on death
    SPELL_PYRRHIC_FOCUS  = 87323,
    SPELL_FIRE_CHANNEL   = 87221, // 78192, In case it fails - magic battle
    //SPELL_BARRIER_CHANNEL        = 76221,

    //Fiery Barrier
    SPELL_FIREBARRIER    = 95791, // Visual + cast time
    SPELL_FIRE_BARRIER   = 87229  // Dmg reduct.
};

enum Events
{
    /*** SINESTRA ***/
    EVENT_INTRO = 1,
    EVENT_FLAME_BREATH, // P1
    EVENT_WRACK, // P1
    EVENT_TWILIGHT_SLICER, // P1
    EVENT_TWILIGHT_BLAST, // P1
    EVENT_SUMMON_WHELPS, // P1
    EVENT_MAGIC_BATTLE, //P2
    EVENT_WIPE, //P2
    EVENT_VISUAL_SINESTRA, // P2
    EVENT_TWILIGHT_DRAKE, // P2
    EVENT_TWILIGHT_SPITECALLER, // P2
    EVENT_SIPHON_EGG, //P2
    EVENT_INTRO_2,

    EVENT_BATTLE_CHECK,

    /***** MOBS *****/
    // Twilight Whelp
    EVENT_SPIT,
    // Twilight Essence
    EVENT_INCREASE,
    // Twilight Drake
    EVENT_TWILIGHT_BREATH,
    // Twilight Spite Caller
    EVENT_UNLEASE_ESSENCE,
    EVENT_INDOMITABLE,
    // Twilight Slicer
    EVENT_TARGET,
    EVENT_DESPAWN,
    // Calen
    EVENT_VISUAL_CALEN,
    EVENT_PYRRHIC_FOCUS,
    EVENT_ESSENCE_OF_THE_RED,
    EVENT_FIRESHIELD,

    EVENT_BERSERK
};

enum Phases
{
    PHASE_NULL = 0,
    PHASE_ONE,
    PHASE_TWO
};

enum Npc
{
    BOSS_SINESTRA            = 45213,
    NPC_SHADOW_ORB           = 49863, // Responsible for twilight slicer
    NPC_PULSATING_EGG        = 46842,
    NPC_TWILIGHT_ESSENCE     = 48018, // Spawned by twilight drake on death
    NPC_TWILIGHT_WHELPS      = 47265,
    NPC_TWILIGHT_SPITE       = 48415, // No target, casts one spell only
    NPC_TWILIGHT_DRAKE       = 48436, // Summoned from Eggs - Targets Calen
    NPC_CALEN                = 46277, // Phase 2. He casts 51744 on himself

    NPC_SINESTRA_BAT_TRIGGER = 46834, // Some trigger, mainly used for magic battle.

    GO_SINESTRA_DOOR         = 000000 // Sinestra flame wall
};

const Position WhelpsLocations[] = // Whelp summonings for last phase. 5 drakes - 5 pos - right
{
    {-953.1688f, -804.14f, 438.593f, 1.938f},
    {-967.1657f, -812.9177f, 438.593f, 1.549f},
    {-983.1641f, -819.3153f, 438.593f, 1.568f},
    {-937.5960f, -779.9398f, 438.692f, 2.136f},
    {-932.6f, -770.813f, 439.661f, 3.361f}
};

const Position WhelpsLocations2[] = // Whelp summonings for last phase. 5 drakes - 5 pos - left
{
    {-995.192f, -734.541f, 438.248f, 5.49f},
    {-1010.919f, -750.47f, 438.593f, 6.28f},
    {-1023.351f, -761.299f, 438.592f, 0.38f},
    {-1031.798f, -774.779f, 438.592f, 0.24f},
    {-1001.364f, -741.629f, 438.577f, 6.04f}
};

const Position EggLocations[] = // Done
{
    {-908.521f, -768.867f, 440.643f, 3.42f},
    {-1000.362f, -692.421f, 440.782f, 4.76f}
};

const Position OrbLocation[] = // Done
{
    {-967.704f, -737.485f, 438.593f, 4.2f},
    {-949.995f, -752.59f, 438.593f, 3.97f}
};

const Position MagicBattlePos[] = // Done
{
    {-969.0499f, -763.2743f, 438.593f, 0.919f}, // Sinestra
    {-981.9046f, -780.1267f, 438.593f, 0.919f}, // Between
    {-993.4172f, -795.2197f, 438.593f, 0.919f} // Calen
};

class boss_sinestra : public CreatureScript
{
public:
    boss_sinestra() : CreatureScript("boss_sinestra") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_sinestraAI(creature);
    }

    struct boss_sinestraAI : public BossAI
    {
        boss_sinestraAI(Creature* creature) : BossAI(creature, DATA_SINESTRA), summons(me)
        {
            instance = creature->GetInstanceScript();
            introDone = false;
        }

        InstanceScript* instance;
        SummonList summons;
        Phases phase;
        bool phaseTwo, drainOff, Side, left, inMeleeRange, introDone, phase3;

        void Reset()
        {
            phase = PHASE_NULL;
            summons.DespawnAll();

            drainOff = false;
            phaseTwo = false;
            Side = false;
            left = false;
            inMeleeRange = false;
            phase3 = false;

            if (!introDone)
            {
                me->AddAura(SPELL_SUBMERGED, me);
                me->AddAura(SPELL_SUBMERGED_INTR, me);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }

            me->AddAura(SPELL_DRAINED, me);
            me->SetHealth(me->GetMaxHealth() / 5 * 3);
            me->setRegeneratingHealth(false);
            me->SetMaxPower(POWER_MANA, 0);
            me->SetPower(POWER_MANA, 0);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);

            for (int i = 0; i < 2; i++)
            {
                Creature* egg = me->SummonCreature(NPC_PULSATING_EGG, EggLocations[i].GetPositionX(), EggLocations[i].GetPositionY(), EggLocations[i].GetPositionZ(), EggLocations[i].GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000);
                egg->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                egg->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                egg->AddAura(SPELL_TWI_CARAPACE, egg);
                egg->CastSpell(egg,63726,true);
                egg->SetInCombatWithZone();
            }

            if (instance) instance->SetBossState(DATA_SINESTRA, NOT_STARTED);

            me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_WRACK, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_WRACK_JUMP, true);

            _Reset();
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (!introDone && who->IsWithinDistInMap(me, 40.0f))
            {
                Talk(SAY_AGGRO);
                introDone = true;
                me->RemoveAurasDueToSpell(SPELL_SUBMERGED);
                me->RemoveAurasDueToSpell(SPELL_SUBMERGED_INTR);
                // me->SetByteValue(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_HOVER);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            EnterPhaseOne();
            DoStartNoMovement(me);
            DoCast(me, SPELL_DRAINED);

            if (instance)
            {
                instance->SetBossState(DATA_SINESTRA, IN_PROGRESS);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add
            }

            events.ScheduleEvent(EVENT_BERSERK, 10 * MINUTE * IN_MILLISECONDS); // 10 min enrage.

            _EnterCombat();
        }

        void initEvents(bool phaseOne = true)
        {
            events.Reset();

            if(phaseOne)
            {
                events.ScheduleEvent(EVENT_WRACK, 15000, PHASE_ONE); // jumps from one player to another two
                events.ScheduleEvent(EVENT_FLAME_BREATH, 29000, PHASE_ONE); // used at every 30 seconds.
                events.ScheduleEvent(EVENT_TWILIGHT_BLAST, 10000, PHASE_ONE); // when target not in melee range
                events.ScheduleEvent(EVENT_TWILIGHT_SLICER, 29000, PHASE_ONE); // two orbs summon beneath her arms, choose two random targets
                events.ScheduleEvent(EVENT_SUMMON_WHELPS, 16000, PHASE_ONE); // every 50 seconds summoned. Soft enrage mechanic.
            }else
            {
                events.ScheduleEvent(EVENT_INTRO_2, 4000, PHASE_TWO);
                events.ScheduleEvent(EVENT_TWILIGHT_DRAKE, 10000, PHASE_TWO); // then 45-49 sec.
                events.ScheduleEvent(EVENT_TWILIGHT_SPITECALLER, 15000, PHASE_TWO); // then 30 sec.
                events.ScheduleEvent(EVENT_SIPHON_EGG, 9000, PHASE_TWO); // Apply to trigger.
                events.ScheduleEvent(EVENT_MAGIC_BATTLE, 7000, PHASE_TWO); // This event checks the life % of bosses and damage done overall.
                events.ScheduleEvent(EVENT_WIPE, 10000, PHASE_TWO);
            }
        }

        void EnterEvadeMode()
        {
            Talk(SAY_FIGHT_L);

            Reset();
            DoCast(me, SPELL_DRAINED);
            me->GetMotionMaster()->MoveTargetedHome();

            if (instance)
            {
                instance->SetBossState(DATA_SINESTRA, FAIL);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            _EnterEvadeMode();
        }

        void EnterPhaseOne()
        {
            phase = PHASE_ONE;
            events.SetPhase(PHASE_ONE);
            me->RemoveAurasDueToSpell(SPELL_MANA_BARRIER);
            initEvents(true);

            if (me->HasAura(SPELL_DRAINED) && drainOff)
            {
                me->RemoveAurasDueToSpell(SPELL_DRAINED);
                me->SetHealth(me->GetMaxHealth());
                me->SetMaxPower(POWER_MANA, 0);
                me->SetPower(POWER_MANA, 0);
                Talk(SAY_PHASE_3);
                drainOff = false;
            }
        }

        void EnterPhaseTwo()
        {
            Talk(SAY_PHASE_2);
            phase = PHASE_TWO;
            events.SetPhase(PHASE_TWO);
            initEvents(false);
            me->SetMaxPower(POWER_MANA, 2012000);
            me->SetPower(POWER_MANA, 2012000);
            me->SummonCreature(NPC_SINESTRA_BAT_TRIGGER, MagicBattlePos[1].GetPositionX(), MagicBattlePos[1].GetPositionY(), MagicBattlePos[1].GetPositionZ(), MagicBattlePos[1].GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN);
            me->SummonCreature(NPC_CALEN, -1004.784f, -810.12f, 438.593f, 0.91f, TEMPSUMMON_CORPSE_DESPAWN, 1000);
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
            summon->setActive(true);

            summon->AI()->DoZoneInCombat();
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
            summons.DespawnAll();

            if (instance)
            {
                instance->SetBossState(DATA_SINESTRA, DONE);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            if(Creature* trigger = me->FindNearestCreature(NPC_SINESTRA_BAT_TRIGGER, 200.0f, true))
                trigger->DisappearAndDie();

            if (me->GetMap()->IsHeroic())
                if (GameObject* sinestraDoor = me->FindNearestGameObject(GO_SINESTRA_DOOR, 200.0f))
                    sinestraDoor->SetGoState(GO_STATE_ACTIVE);

            me->SummonGameObject(GO_CACHE_OF_THE_BROODMOTHER, -960.0f, -750.0f, 55.333f, 438.593f, 4.38f, 0, 0, 0, 300000);

            _JustDied();
        }

        void KilledUnit(Unit* /*victim*/)
        {
            Talk(RAND(SAY_KILL_1, SAY_KILL_2));
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING) || !phase)
                return;

            if (me->HealthBelowPct(30) && !phaseTwo && me->HasAura(SPELL_DRAINED)) // Switch phase.
            {
                EnterPhaseTwo();
                phaseTwo = true;
            }

            events.Update(diff);

            if (phase == PHASE_ONE) // First phase
            {
                std::list<Unit*> targets;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_BERSERK:
                           DoCast(me, SPELL_BERSERK);
                           break;

                        case EVENT_WRACK:
                            Talk(SAY_SPECIAL_2);
                            SelectTargetList(targets, NonTankTargetSelector(me), RAID_MODE(1, 1, 1, 2), SELECT_TARGET_RANDOM);
                            if (!targets.empty())
                                for (std::list<Unit*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                                    (*itr)->CastSpell(me, SPELL_WRACK, true);
                            events.ScheduleEvent(EVENT_WRACK, urand(30000, 32000), PHASE_ONE);
                            break;

                        case EVENT_FLAME_BREATH:
                            DoCastVictim(SPELL_FLAME_BREATH);
                            events.ScheduleEvent(EVENT_FLAME_BREATH, 28000, PHASE_ONE);
                            break;

                        case EVENT_SUMMON_WHELPS:
                            Talk(SAY_ADDS);
                            if (!Side)
                            {
                                for (int i = 0; i < 5; i++)
                                    me->SummonCreature(NPC_TWILIGHT_WHELPS, WhelpsLocations[i].GetPositionX(), WhelpsLocations[i].GetPositionY(), WhelpsLocations[i].GetPositionZ(), WhelpsLocations[i].GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000);
                                Side = true;
                            } else
                            {
                                for (int i = 0; i < 5; i++)
                                    me->SummonCreature(NPC_TWILIGHT_WHELPS, WhelpsLocations2[i].GetPositionX(), WhelpsLocations2[i].GetPositionY(), WhelpsLocations2[i].GetPositionZ(), WhelpsLocations2[i].GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000);
                                Side = false;
                            }                            
                            events.ScheduleEvent(EVENT_SUMMON_WHELPS, 50000, PHASE_ONE);
                            break;

                        case EVENT_TWILIGHT_SLICER:
                            if (Creature* orb1 = me->SummonCreature(NPC_SHADOW_ORB, OrbLocation[0].GetPositionX(), OrbLocation[0].GetPositionY(), OrbLocation[0].GetPositionZ(), OrbLocation[0].GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000))
                            if (Creature* orb2 = me->SummonCreature(NPC_SHADOW_ORB, OrbLocation[1].GetPositionX(), OrbLocation[1].GetPositionY(), OrbLocation[1].GetPositionZ(), OrbLocation[1].GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000))
                                orb2->CastSpell(orb1, SPELL_SLICER_DUMMY, false);
                            events.ScheduleEvent(EVENT_TWILIGHT_SLICER, 28000, PHASE_ONE);
                            break;
                            
                        case EVENT_TWILIGHT_BLAST:
                            if (Unit* target = me->GetVictim())
                            {
                                if (target->IsWithinDistInMap(me, 1.0f)) // check if tank is in melee range.
                                    inMeleeRange = true;
                                else // Blast the shit
                                {
                                    inMeleeRange = false;
                                    DoCast(target, SPELL_TWILIGHT_BLAST);
                                }
                            }
                            events.ScheduleEvent(EVENT_TWILIGHT_BLAST, urand(1500, 2000)); 
                            break;
                    }
                }
            }
            else if (phase == PHASE_TWO) // Second phase
            {
                // Check Phase 3.
                if (!me->FindNearestCreature(NPC_PULSATING_EGG, 200.0f, true) && !drainOff && !phase3)
                {
                    drainOff = true;
                    phase3 = true;
                    EnterPhaseOne();
                }

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_TWILIGHT_DRAKE:
                            Talk(SAY_DRAKE);
                            if(!left)
                            {
                                me->SummonCreature(NPC_TWILIGHT_DRAKE, WhelpsLocations[0].GetPositionX(), WhelpsLocations[0].GetPositionY(), WhelpsLocations[0].GetPositionZ(), WhelpsLocations[0].GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000);
                                left = true;
                            }
                            else
                            {
                                me->SummonCreature(NPC_TWILIGHT_DRAKE, WhelpsLocations2[0].GetPositionX(), WhelpsLocations2[0].GetPositionY(), WhelpsLocations2[0].GetPositionZ(), WhelpsLocations2[0].GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000);
                                left = false;
                            }
                            events.ScheduleEvent(EVENT_TWILIGHT_DRAKE, urand(28000, 34000), PHASE_TWO);
                            break;

                        case EVENT_TWILIGHT_SPITECALLER:
                            Talk(SAY_SPITECALL);
                            me->SummonCreature(NPC_TWILIGHT_SPITE, me->GetPositionX()-15, me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN, 1000);
                            events.ScheduleEvent(EVENT_TWILIGHT_SPITECALLER, urand(28000, 34000), PHASE_TWO);
                            break;

                        case EVENT_SIPHON_EGG:
                            if (Creature* eggnog = me->FindNearestCreature(NPC_PULSATING_EGG, 200.0f, true))
                                if(eggnog->HasAura(SPELL_TWI_CARAPACE))
                                {
                                    eggnog->RemoveAurasDueToSpell(SPELL_TWI_CARAPACE);
                                    eggnog->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                    me->CastSpell(eggnog, SPELL_SIPHON_EGG, true);
                                    Talk(SAY_SPECIAL_1);
                                }
                            events.ScheduleEvent(EVENT_SIPHON_EGG, 90000, PHASE_TWO);
                            break;

                        case EVENT_MAGIC_BATTLE: // Insert dramatic music!!!
                            if(Creature* trigger = me->FindNearestCreature(NPC_SINESTRA_BAT_TRIGGER, 200.0f, true))
                                me->CastSpell(trigger, SPELL_TWILIGHT_POWA, true);
                            break;

                        case EVENT_WIPE: // BLAST THE BITCHES!
                            if (!me->FindNearestCreature(NPC_CALEN, 200.0f, true))
                                DoCast(me, SPELL_TWI_EXTINCTION);
                            break;

                        case EVENT_INTRO_2: // BLAST THE BITCHES!
                            DoCast(me, SPELL_EXTINCT_DUMMY);
                            break;
                    }
                }
            }

            DoMeleeAttackIfReady();
        }

    private:
    };
};

/*********************
** NPC Twilight Essence (43585) - Soft Enrage. Ever Growing Pools.
**********************/
class npc_twilight_essence : public CreatureScript 
{
public:

    npc_twilight_essence() : CreatureScript("npc_twilight_essence") { }

    CreatureAI* GetAI(Creature* creature) const 
    {
        return new npc_twilight_essenceAI(creature);
    }

    struct npc_twilight_essenceAI : public ScriptedAI 
    {

        npc_twilight_essenceAI(Creature * creature) : ScriptedAI(creature) 
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->AddAura(SPELL_TWI_ESSENCE, me);
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            events.ScheduleEvent(EVENT_INCREASE, 15000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_INCREASE:
                    DoCast(me, SPELL_TWI_INCREASE);
                    events.ScheduleEvent(EVENT_INCREASE, 15000);
                    return;
                }
            }
        }
    };
};

/*********************
** NPC Twilight Drake (55636) - P2.
**********************/
class npc_twilight_drake : public CreatureScript 
{
public:

    npc_twilight_drake() : CreatureScript("npc_twilight_drake") { }

    CreatureAI* GetAI(Creature* creature) const 
    {
        return new npc_twilight_drakeAI(creature);
    }

    struct npc_twilight_drakeAI : public ScriptedAI 
    {

        npc_twilight_drakeAI(Creature * creature) : ScriptedAI(creature) 
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            events.ScheduleEvent(EVENT_TWILIGHT_BREATH, 9000);
            if(Creature* caly = me->FindNearestCreature(NPC_CALEN, 200.0f, true))
            {
                me->SetInCombatWith(caly);
                me->AddThreat(caly, 250.0f);
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (Creature* essence = me->FindNearestCreature(NPC_TWILIGHT_ESSENCE, 4.0f, true)) // Eat that essence
            {
                DoCast(me, SPELL_ABSORB_ESSENCE);
                essence->DespawnOrUnsummon();
            }

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TWILIGHT_BREATH:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                        DoCast(target, SPELL_TWI_BREATH);
                    events.ScheduleEvent(EVENT_TWILIGHT_BREATH, urand(14000, 15000));
                    break;
                }
            }
            
            DoMeleeAttackIfReady();
        }
    };
};

/*********************
** NPC Twilight Whelp (47265) - Phase 1 Adds.
**********************/
class npc_twilight_whelp_phas1 : public CreatureScript 
{
public:

    npc_twilight_whelp_phas1() : CreatureScript("npc_twilight_whelp_phas1") { }

    CreatureAI* GetAI(Creature* creature) const 
    {
        return new npc_twilight_whelp_phas1AI(creature);
    }

    struct npc_twilight_whelp_phas1AI : public ScriptedAI 
    {

        npc_twilight_whelp_phas1AI(Creature * creature) : ScriptedAI(creature) 
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;
        bool Revived, died;
        Unit* myEssence;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->AddUnitMovementFlag(MOVEMENTFLAG_FLYING);
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 150.0f, true))
                AttackStart(target);
                Revived = false;
                died = false;
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_SPIT, 4000);
        }

        void JustDied(Unit* /*killer*/) { }

        void DamageTaken(Unit* /*who*/, uint32& damage)
        {
            if (damage > me->GetHealth() && !Revived)
                damage = me->GetHealth() - 1;
        }

        void UpdateAI(uint32 diff)
        {
            if (me->HealthBelowPct(3) && !Revived) // Buli knows a better way... me I can't remember what I know
            {
                // "Die".
                if (!died)
                {
                    me->RemoveAllAuras();
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    me->SetFlag(UNIT_NPC_EMOTESTATE, EMOTE_STATE_DEAD);
                    me->SetUInt32Value(UNIT_FIELD_BYTES_1, UNIT_STAND_STATE_DEAD);
                    me->SetReactState(REACT_PASSIVE);
                    myEssence = me->SummonCreature(NPC_TWILIGHT_ESSENCE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_MANUAL_DESPAWN);
                    died = true;
                }

                if(Unit* swamp = me->FindNearestCreature(NPC_TWILIGHT_ESSENCE, 4.0f, true))
                    if(swamp && swamp->GetGUID() != myEssence->GetGUID())
                    {
                        me->SetHealth(me->GetMaxHealth());
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        me->RemoveFlag(UNIT_NPC_EMOTESTATE, EMOTE_STATE_DEAD);
                        me->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
                        me->SetReactState(REACT_AGGRESSIVE);
                        Revived = true;
                    }
            }

            events.Update(diff);

            if(Creature* sinestra = me->FindNearestCreature(NPC_SINESTRA, 200.0f, true))
                if(!sinestra || !sinestra->IsInCombat()) // Is dead / evaded.
                    me->DespawnOrUnsummon();

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SPIT:
                        DoCastVictim(SPELL_TWI_SPIT);
                        events.ScheduleEvent(EVENT_SPIT, urand(9000, 12000));
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

/*********************
** NPC Twilight Spite Caller (43707) - P2.
**********************/
class npc_twilight_spite : public CreatureScript 
{
public:

    npc_twilight_spite() : CreatureScript("npc_twilight_spite") { }

    CreatureAI* GetAI(Creature* creature) const 
    {
        return new npc_twilight_spiteAI(creature);
    }

    struct npc_twilight_spiteAI : public ScriptedAI 
    {

        npc_twilight_spiteAI(Creature * creature) : ScriptedAI(creature) 
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 150.0f, true))
                AttackStart(target);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_INDOMITABLE, 100);
            events.ScheduleEvent(EVENT_UNLEASE_ESSENCE, 3000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            if(Creature* sinestra = me->FindNearestCreature(NPC_SINESTRA, 200.0f, true))
                if(!sinestra || !sinestra->IsInCombat()) // Is dead / evaded.
                    me->DespawnOrUnsummon();

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_INDOMITABLE:
                    if (me->HasUnitState(UNIT_STATE_STUNNED) || me->HasUnitState(UNIT_STATE_ROOT))
                    {
                        DoCast(me, SPELL_INDOMITABLE);
                        events.ScheduleEvent(EVENT_INDOMITABLE, 1000);
                    }
                    break;

                    case EVENT_UNLEASE_ESSENCE:
                    DoCastAOE(SPELL_UNLEASH_ESENCE);
                    events.ScheduleEvent(EVENT_UNLEASE_ESSENCE, urand(19000, 25000));
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

/*********************
** NPC Shadow Orbs (43622).
**********************/
class npc_twilight_slicer : public CreatureScript 
{
public:

    npc_twilight_slicer() : CreatureScript("npc_twilight_slicer") { }

    CreatureAI* GetAI(Creature* creature) const 
    {
        return new npc_twilight_slicerAI(creature);
    }

    struct npc_twilight_slicerAI : public ScriptedAI 
    {

        npc_twilight_slicerAI(Creature * creature) : ScriptedAI(creature) 
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;
        bool dead;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            dead = false;
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            events.ScheduleEvent(EVENT_TARGET, 3000);
            events.ScheduleEvent(EVENT_DESPAWN, 8000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_TARGET:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                        {
                            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
                            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, true);
                            me->SetSpeed(MOVE_WALK, 0.85f, true);
                            me->SetSpeed(MOVE_RUN, 0.85f, true);
                            me->AddThreat(target, 5000000.0f);
                            DoCast(me, SPELL_SLICER_PULSE);
                            me->GetMotionMaster()->MoveChase(target, 4.0f);
                            if (Creature* Sinestra = me->FindNearestCreature(BOSS_SINESTRA, 200.0f, true))
                                Sinestra->AI()->Talk(SAY_SLICER);
                        }
                    
                    case EVENT_DESPAWN:
                        if(me->FindNearestCreature(NPC_SHADOW_ORB, 4.0f, true))
                        {
                            me->DisappearAndDie();
                            events.ScheduleEvent(EVENT_DESPAWN, 1000);
                        }
                        break;
                }
            }
        }
    };
};

/*********************
** NPC Calen (46277).
**********************/
class npc_calen : public CreatureScript 
{
public:

    npc_calen() : CreatureScript("npc_calen") { }

    CreatureAI* GetAI(Creature* creature) const 
    {
        return new npc_calenAI(creature);
    }

    struct npc_calenAI : public ScriptedAI 
    {

        npc_calenAI(Creature * creature) : ScriptedAI(creature) 
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;
        bool premature;

        void IsSummonedBy(Unit* summoner)
        {
            premature = false;
            me->SetInCombatWith(summoner);
            me->AddThreat(summoner, 250.0f);
            events.ScheduleEvent(EVENT_FIRESHIELD, 2000);
            events.ScheduleEvent(EVENT_VISUAL_CALEN, 1000);
            events.ScheduleEvent(EVENT_PYRRHIC_FOCUS, 500);
            events.ScheduleEvent(EVENT_ESSENCE_OF_THE_RED, 3000);
            Talk(SAY_ENTRANCE);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_FIRESHIELD:
                        DoCast(me, SPELL_FIRESHIELD);
                        break;

                    case EVENT_VISUAL_CALEN:
                        if(Creature* trigger = me->FindNearestCreature(NPC_SINESTRA_BAT_TRIGGER, 200.0f, true))
                        {
                            me->CastSpell(trigger, SPELL_FIRE_CHANNEL, false);
                            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
                            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, true);
                            me->AddThreat(trigger, 5000000.0f);
                        }
                        break;
                        
                    case EVENT_PYRRHIC_FOCUS:
                        if(me->GetPower(POWER_MANA) < (me->GetMaxPower(POWER_MANA) * 30 / 100) && !me->HasAura(SPELL_PYRRHIC_FOCUS))
                        {
                            DoCast(me, SPELL_PYRRHIC_FOCUS);
                            Talk(SAY_RECHARGE);
                        }
                        events.ScheduleEvent(EVENT_PYRRHIC_FOCUS, 1000);
                        break;

                    case EVENT_ESSENCE_OF_THE_RED:
                        if(!me->FindNearestCreature(NPC_PULSATING_EGG, 200.0f, true))
                            {
                                    premature = true;
                                    Talk(SAY_CALEN_P3);
                                    std::list<Unit*> TargetList;
                                    Trinity::AnyFriendlyUnitInObjectRangeCheck checker(me, me, 200.0f);
                                    Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(me, TargetList, checker);
                                    me->VisitNearbyObject(200.0f, searcher);
                                    for (std::list<Unit*>::iterator itr = TargetList.begin(); itr != TargetList.end(); ++itr)
                                        DoCast(*itr, SPELL_ESSENCE_CALEN, true); //Have a little Calen Essence - Night elf White Sauce version.
                                    me->DespawnOrUnsummon(3000);
                            }
                        events.ScheduleEvent(EVENT_ESSENCE_OF_THE_RED, 4000);
                        break;
                }
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            if(!premature)
            Talk(SAY_PREMATURE);

            if(Creature* trigger = me->FindNearestCreature(NPC_SINESTRA_BAT_TRIGGER, 200.0f, true))
                trigger->DisappearAndDie();
        }
    };
};

/*********************
** NPC Controller (46277).
**********************/
class npc_controller : public CreatureScript 
{
public:

    npc_controller() : CreatureScript("npc_controller") { }

    CreatureAI* GetAI(Creature* creature) const 
    {
        return new npc_controllerAI(creature);
    }

    struct npc_controllerAI : public ScriptedAI 
    {

        npc_controllerAI(Creature * creature) : ScriptedAI(creature) 
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;
        uint8 talkcount;

        void IsSummonedBy(Unit* summoner)
        {
            me->SetInCombatWith(summoner);
            me->AddThreat(summoner, 250.0f);
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            events.ScheduleEvent(EVENT_BATTLE_CHECK, 25000);
            talkcount = 0;
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_BATTLE_CHECK:
                        if(Creature* egg = me->FindNearestCreature(NPC_PULSATING_EGG, 200.0f, true))
                            if(!egg->HasAura(SPELL_TWI_CARAPACE))
                            {
                                if(egg->HealthAbovePct(75) && talkcount == 0)
                                {
                                    if(Creature* calen = me->FindNearestCreature(NPC_CALEN, 200.0f, true))
                                        calen->AI()->Talk(SAY_CALEN_N);
                                    if(Creature* sinestra = me->FindNearestCreature(BOSS_SINESTRA, 200.0f, true))
                                        sinestra->AI()->Talk(SAY_FIGHT_N);
                                    me->GetMotionMaster()->MovePoint(1, MagicBattlePos[1].GetPositionX(), MagicBattlePos[1].GetPositionY(), MagicBattlePos[1].GetPositionZ());
                                    talkcount++;
                                }
                                if(egg->HealthBelowPct(75) && talkcount == 0)
                                {
                                    if(Creature* calen = me->FindNearestCreature(NPC_CALEN, 200.0f, true))
                                        calen->AI()->Talk(SAY_CALEN_W);
                                    if(Creature* sinestra = me->FindNearestCreature(BOSS_SINESTRA, 200.0f, true))
                                        sinestra->AI()->Talk(SAY_FIGHT_W);
                                    me->GetMotionMaster()->MovePoint(1, MagicBattlePos[0].GetPositionX(), MagicBattlePos[0].GetPositionY(), MagicBattlePos[0].GetPositionZ());
                                    talkcount++;
                                }
                                if(egg->HealthAbovePct(65) && talkcount == 1)
                                {
                                    if(Creature* calen = me->FindNearestCreature(NPC_CALEN, 200.0f, true))
                                        calen->AI()->Talk(SAY_CALEN_L);
                                    if(Creature* sinestra = me->FindNearestCreature(BOSS_SINESTRA, 200.0f, true))
                                        sinestra->AI()->Talk(SAY_FIGHT_L);
                                    me->GetMotionMaster()->MovePoint(1, MagicBattlePos[2].GetPositionX(), MagicBattlePos[2].GetPositionY(), MagicBattlePos[2].GetPositionZ());
                                    talkcount++;

                                    if(egg->HealthAbovePct(75))
                                        if(Creature* calen = me->FindNearestCreature(NPC_CALEN, 200.0f, true))
                                        {
                                            calen->AI()->Talk(SAY_PREMATURE);
                                            me->Kill(calen);
                                        }
                                }
                                if(egg->HealthBelowPct(75) && egg->HealthAbovePct(50) && talkcount == 1)
                                {
                                    if(Creature* calen = me->FindNearestCreature(NPC_CALEN, 200.0f, true))
                                        calen->AI()->Talk(SAY_CALEN_N);
                                    if(Creature* sinestra = me->FindNearestCreature(BOSS_SINESTRA, 200.0f, true))
                                        sinestra->AI()->Talk(SAY_FIGHT_N);
                                    me->GetMotionMaster()->MovePoint(1, MagicBattlePos[1].GetPositionX(), MagicBattlePos[1].GetPositionY(), MagicBattlePos[1].GetPositionZ());
                                    talkcount++;
                                }
                                if(egg->HealthBelowPct(50) && talkcount == 1)
                                {
                                    if(Creature* calen = me->FindNearestCreature(NPC_CALEN, 200.0f, true))
                                        calen->AI()->Talk(SAY_CALEN_W);
                                    if(Creature* sinestra = me->FindNearestCreature(BOSS_SINESTRA, 200.0f, true))
                                        sinestra->AI()->Talk(SAY_FIGHT_W);
                                    me->GetMotionMaster()->MovePoint(1, MagicBattlePos[0].GetPositionX(), MagicBattlePos[0].GetPositionY(), MagicBattlePos[0].GetPositionZ());
                                    talkcount++;
                                }
                                if(egg->HealthAbovePct(40) && talkcount == 2)
                                {
                                    if(Creature* calen = me->FindNearestCreature(NPC_CALEN, 200.0f, true))
                                        calen->AI()->Talk(SAY_CALEN_L);
                                    if(Creature* sinestra = me->FindNearestCreature(BOSS_SINESTRA, 200.0f, true))
                                        sinestra->AI()->Talk(SAY_FIGHT_L);
                                    me->GetMotionMaster()->MovePoint(1, MagicBattlePos[2].GetPositionX(), MagicBattlePos[2].GetPositionY(), MagicBattlePos[2].GetPositionZ());
                                    talkcount = 0;
                                    if(egg->HealthAbovePct(50))
                                        if(Creature* calen = me->FindNearestCreature(NPC_CALEN, 200.0f, true))
                                        {
                                            calen->AI()->Talk(SAY_PREMATURE);
                                            me->Kill(calen);
                                        }
                                }
                                if(egg->HealthBelowPct(50) && egg->HealthAbovePct(25) && talkcount == 2)
                                {
                                    if(Creature* calen = me->FindNearestCreature(NPC_CALEN, 200.0f, true))
                                        calen->AI()->Talk(SAY_CALEN_N);
                                    if(Creature* sinestra = me->FindNearestCreature(BOSS_SINESTRA, 200.0f, true))
                                        sinestra->AI()->Talk(SAY_FIGHT_N);
                                    me->GetMotionMaster()->MovePoint(1, MagicBattlePos[1].GetPositionX(), MagicBattlePos[1].GetPositionY(), MagicBattlePos[1].GetPositionZ());
                                    talkcount = 0;
                                }
                                if(egg->HealthBelowPct(25) && talkcount == 2)
                                {
                                    if(Creature* calen = me->FindNearestCreature(NPC_CALEN, 200.0f, true))
                                        calen->AI()->Talk(SAY_CALEN_W);
                                    if(Creature* sinestra = me->FindNearestCreature(BOSS_SINESTRA, 200.0f, true))
                                        sinestra->AI()->Talk(SAY_FIGHT_W);
                                    me->GetMotionMaster()->MovePoint(1, MagicBattlePos[0].GetPositionX(), MagicBattlePos[0].GetPositionY(), MagicBattlePos[0].GetPositionZ());
                                    talkcount = 0;
                                }
                                events.ScheduleEvent(EVENT_BATTLE_CHECK, 25000);
                            }
                        break;
                }
            }
        }
    };
};

/* SPELL SCRIPTS */

/*** BOSS ***/

class spell_sinestra_barrier : public SpellScriptLoader
{
    public:
        spell_sinestra_barrier() : SpellScriptLoader("spell_sinestra_barrier") { }

        class spell_sinestra_barrier_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sinestra_barrier_AuraScript);

            void HandlePeriodicTick(AuraEffect const* /*aurEff*/)
            {
                PreventDefaultAction();
                if (Unit* caster = GetCaster())
                {
                    int32 missingHealth = int32(caster->GetMaxHealth() - caster->GetHealth());
                    caster->ModifyHealth(missingHealth);
                    caster->ModifyPower(POWER_MANA, -missingHealth);
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_sinestra_barrier_AuraScript::HandlePeriodicTick, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sinestra_barrier_AuraScript();
        }
};

/*** MOBS ***/

class ExactDistanceCheck
{
    public:
        ExactDistanceCheck(Unit* source, float dist) : _source(source), _dist(dist) { }

        bool operator()(WorldObject* unit) const
        {
            return _source->GetExactDist2d(unit) > _dist;
        }

    private:
        Unit* _source;
        float _dist;
};

// Spell - 88146
class spell_twilight_essence : public SpellScriptLoader
{
    public:
        spell_twilight_essence() : SpellScriptLoader("spell_twilight_essence") { }

        class spell_twilight_essence_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_twilight_essence_SpellScript);

            void ScaleRange(std::list<WorldObject*>& targets)
            {
                targets.remove_if(ExactDistanceCheck(GetCaster(), 2.5f * GetCaster()->GetFloatValue(OBJECT_FIELD_SCALE_X)));
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_twilight_essence_SpellScript::ScaleRange, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_twilight_essence_SpellScript::ScaleRange, EFFECT_1, TARGET_UNIT_DEST_AREA_ENTRY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_twilight_essence_SpellScript();
        }
};

class TwilightSlicerSelector
{
    public:
        TwilightSlicerSelector(Unit* caster, Unit* cutterCaster) : _caster(caster), _slicerActive(cutterCaster) { }

        bool operator()(WorldObject* unit)
        {
            return !unit->IsInBetween(_caster, _slicerActive, 4.0f);
        }

    private:
        Unit* _caster;
        Unit* _slicerActive;
};

// 78862
class spell_twilight_slicer : public SpellScriptLoader
{
    public:
        spell_twilight_slicer() : SpellScriptLoader("spell_twilight_slicer") { }

        class spell_twilight_slicer_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_twilight_slicer_SpellScript);

            void RemoveNotBetween(std::list<WorldObject*>& unitList)
            {
                if (unitList.empty())
                    return;

                Unit* caster = GetCaster();
                if (Aura* cutter = caster->GetAura(SPELL_SLICER_DUMMY))
                {
                    if (Unit* cutterCaster = cutter->GetCaster())
                    {
                        unitList.remove_if(TwilightSlicerSelector(caster, cutterCaster));
                        return;
                    }
                }

                // In case cutter caster werent found for some reason
                unitList.clear();
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_twilight_slicer_SpellScript::RemoveNotBetween, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_twilight_slicer_SpellScript();
        }
};

// 87323  92941
class spell_pyrrhic_focus : public SpellScriptLoader
{
    public:
        spell_pyrrhic_focus() : SpellScriptLoader("spell_pyrrhic_focus") { }

        class spell_pyrrhic_focus_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pyrrhic_focus_AuraScript);

            void HandlePeriodicTick(AuraEffect const* /*aurEff*/)
            {
                PreventDefaultAction();
                if (Unit* caster = GetCaster())
                {
                    int32 missingMana = int32(caster->GetMaxPower(POWER_MANA) - caster->GetPower(POWER_MANA));
                    caster->ModifyPower(POWER_MANA, missingMana);
                    caster->ModifyHealth(-missingMana);
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_pyrrhic_focus_AuraScript::HandlePeriodicTick, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_pyrrhic_focus_AuraScript();
        }
};

// 89421
class spell_wrack : public SpellScriptLoader 
{
    public:
        spell_wrack() : SpellScriptLoader("spell_wrack") { }

        class spell_wrack_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_wrack_AuraScript);

            Unit* target;

            void HandleAfterEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                target = GetTarget();
            }

            void HandleAfterDispel(DispelInfo* /*dispelInfo*/)
            {
                Unit* caster = GetCaster();

                if (!caster || !target)
                    return;
                if (AuraEffect* wrackDOT = GetEffect(EFFECT_0))
                {
                    std::list<Unit*> allies;
                    int32 count = 0;

                    Trinity::AnyGroupedUnitInObjectRangeCheck checker(target, target, 40.0f, true);
                    Trinity::UnitListSearcher<Trinity::AnyGroupedUnitInObjectRangeCheck> searcher(target, allies, checker);
                    caster->VisitNearbyObject(40.0f, searcher);

                    if (!allies.empty())
                        for (std::list<Unit*>::const_iterator itr = allies.begin(); (itr != allies.end() && count <= 2); ++itr)
                            if ((*itr)->GetTypeId() == TYPEID_PLAYER && (*itr)->GetGUID() != target->GetGUID())
                            {
                                caster->CastSpell((*itr), SPELL_WRACK, true);
                                (*itr)->GetAura(SPELL_WRACK)->SetDuration(wrackDOT->GetBase()->GetDuration());
                                count++;
                            }
                }
            }

            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_wrack_AuraScript::HandleAfterEffectApply, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                AfterDispel += AuraDispelFn(spell_wrack_AuraScript::HandleAfterDispel);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_wrack_AuraScript();
        }
};

void AddSC_boss_sinestra()
{
    new boss_sinestra();
    new npc_twilight_essence();
    new npc_twilight_slicer();
    new npc_twilight_drake();
    new npc_twilight_whelp_phas1();
    new npc_twilight_spite();
    new npc_calen();
    new npc_controller();
    new spell_sinestra_barrier();
    new spell_twilight_essence();
    new spell_twilight_slicer();
    new spell_pyrrhic_focus();
    new spell_wrack();
}