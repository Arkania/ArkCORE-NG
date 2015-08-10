/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 * (start by PlayBoy Buli)
 *
 * If you have found this script on the internet feel free to use it as I can do fuck to stop you.
 * But do leave an email to thank me, telling me where you found so I can fist fuck the anal wart that put it there.
 *
 * Script 80 % done.
 *
 * ToDo:
 * - Heroic Visuals need some research.
 * - Finish Heroic part.
 *
 * Issues:
 * Issue 1: heroic part implemented 80% - platform destroy todo - summons sunshine and a black baby jesus on a unicorn - have no clue if spells are cast properly.
 * Issue 2: not blizzlike execution: Dreadflames should cast a dreadflame spell that spawns dreadflame spawns (Dawg !) and spawns become the dreadflame...
 * rather than dreadflame spawn becoming dreadflame from the targeted stalker, but overall it has the same result. So I don't care.
 * Issue 3: Visuals - for what malfurion does at first.
 * Issue 4: Proper Dialogue Sequence for cenarius and malfurion
 * Issue 5: This script... IS NOT LONG ENOUGH!
 *
 * This file is NOT free software; Third-party users can NOT redistribute it or modify it. :)
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
#include "MoveSplineInit.h"
#include "firelands.h"

#define QUEST_HEART_FLAME     29307 // Heart of Flame quest.
#define NPC_SMASH             53266 // Sulfuras Smash main NPC trigger.
#define NPC_PLATFORM_STALKER  53952 // For Dreadflames.
#define ENGULFING_FLAME_COUNT 9     // Engulfing Flames count.
#define GO_CACHE_OF_THE_FIRELORD 208967 // Loot chest
#define GO_RAGNAROS_DOOR         209073 // Door

enum Yells
{
    SAY_AGGRO = 0,
    SAY_DEATH = 1,
    SAY_KILL = 2,
    SAY_ENRAGE_TEXT = 3,
    SAY_INTERMISSION2 = 4,
    SAY_INTERMISSION1 = 5,
    SAY_PHASE_2 = 6,
    SAY_PHASE_3 = 7,
    SAY_PURGE = 8,
    SAY_DEATH_H = 9,
    SAY_SULFURAS_SMASH = 10,
    SAY_PHASE_HEROIC_TEXT = 11,
    SAY_ENGULFING_FLAMES_TEXT = 12,

    // boss raid announces
    SAY_ENRAGE = 13,
    SAY_SMASH = 14,
    SAY_SPLITTING = 15,
    SAY_SONS = 16,
    SAY_NEW_PHASE = 17,
    SAY_ENGULFING = 18,
    SAY_WORLD = 19,
    SAY_METEOR = 20,
    SAY_HEROIC_PHASE = 21,
    SAY_AID = 22,
};

enum Spells
{
    /*** RAGNAROS ***/

    SPELL_SUBMERGE_SELF = 100312, // Intro
    SPELL_RAGE_OF_RAGNAROS = 101110, // Quest check all phases.
    SPELL_MOLTEN_HEART = 101125, // Quest - when dead, targets player with quest and gives him heart.
    SPELL_BASE_VISUAL = 98860,  // Base for ragnaros belly-down (fire circle puffy stuff)

    // Phase 1
    SPELL_WRATH_OF_RAGNAROS = 98263,
    SPELL_HAND_OF_RAGNAROS = 98237,
    SPELL_MAGMA_TRAP = 98164,  // triggers 98170 which summons npc (53086).
    SPELL_MAGMA_TRAP_VISUAL = 98179,
    SPELL_MAGMA_TRAP_ERUPTION = 98175,
    SPELL_MAGMA_TRAP_VULNERABILITY = 100238, // Add with AddAura!
    SPELL_BURNING_WOUND = 99401,  // demands tank rotation - you don't say?!
    SPELL_MAGMA_BLAST = 98313,  // enrage no range all p1
    SPELL_SULFURAS_SMASH_RAG_SELF = 98710,  // Visual smash
    SPELL_SULFURAS_SMASH_VISUAL = 98712,
    SPELL_TARGET_SULFURAS = 98706,  // summons 53268 for 10 seconds - NOT NEEDED, manual summon @locations.

    // Intermissions
    SPELL_SPLITTING_BLOW_NORTH = 98953,  // 98953 and 98951 - are same visual, trigger 99012 (which triggers 99056 summon Sons periodic).
    SPELL_SPLITTING_BLOW_MID = 98952,
    SPELL_SPLITTING_BLOW_SOUTH = 98951,
    SPELL_SUBMERGE = 98982,  // in transition phases, w/ lava bolt casts
    SPELL_DISABLE_ANIM = 16245,  // hack to prevent him getting up from the lava again.
    SPELL_LAVA_BOLTS = 98981,
    SPELL_SULFURAS_AURA = 100456, // Warning marker + periodic damage

    // Phase 2
    SPELL_ENGULFING_FLAMES = 99171,  // p2 3 w 100185 damage - Requires Visuals 99216 Near / 99217 Middle / 99218 Far
    SPELL_VISUAL_ENGULFING = 99216,
    SPELL_DAMAGE_ENGULFING = 100185,
    SPELL_WORLD_IN_FLAMES = 100190, // p2 3 engulfing flames cast 2 sec- heroic
    SPELL_MOLTEN_SEED_VISUAL = 98520,  // just the visual.
    SPELL_MOLTEN_SEED_MISSILE = 98495,  // the actual damage of the 98520
    SPELL_MOLTEN_SEED_DAMAGE = 98498,

    // Phase 3
    SPELL_LIVING_METEOR = 99268,  // phase 3-99317 spell summon
    SPELL_SUMMON_LIVING_METEOR = 99317,

    // Heroic
    SPELL_SUPERHEATED = 100593, // Heroic - stacks spell soft enrage
    SPELL_EMPOWER = 100604, // Heroic - very violent spell to check spell 100605 for other effects
    SPELL_DELUGE = 100758,
    SPELL_CLOUDBURST = 100757,
    SPELL_CAST_CLOUDBURST = 100714,
    SPELL_ENTRAPPING = 100653,
    SPELL_DREADFLAME = 100675, // http://www.wowhead.com/spell=100675 ragnaros cast on random target on the ground. it targets mob called dreadflame, hits it and spawns dreadflame spawn, new mob that does the actual work 
    SPELL_DREADFLAME_SUMMON = 100679,
    SPELL_DREADFLAME_DAMAGE = 100941,
    SPELL_DREADFLAME_VISUAL = 100691, // or a funky dummy = funky visual 100692
    SPELL_METEOR_OF_FROST = 100567,
    SPELL_VISUAL_BREATH = 100478,
    SPELL_PROTECT_SUPERHEAT = 100503, // protects from Superheated
    SPELL_WATER_VISUAL = 69657,  // totally wrong but will announce dreadflame end
    SPELL_NATURE = 34770,  // totally wrong, but visual for roots
    SPELL_VISUAL_ROOTS = 96527,

    /*** Creatures & Summons ****/

    // Splitting Blow 53393
    SPELL_SUMMON_SULFURAS = 99056,  // then summon sons of flame 53140

    // Sulfuras Smash 53268
    SPELL_SULFURAS_SMASH_DAMAGE = 98708,  // on self when spawned by 98706

    // Engulfing Flames 53485
    SPELL_ENGULFING_FLAMES_DAMAGE = 100185, // on self

    // Molten Seed 53186
    SPELL_MOLTEN_INFERNO = 100252, // after 10 secs and spawns molten elemental

    // Living Meteor 53500
    SPELL_IMPACT = 99287,  // triggered by distance
    SPELL_COMBUSTIBLE = 99296,  // + aura knockb to dmg
    SPELL_COMBUSTION = 100249, // on hit
    SPELL_INCR_RUN = 100278, // triggers periodic 10% speed
    SPELL_LAVALOGGED = 101088, // near lava wave
    SPELL_FLAMING_FIXATE = 99849,  //  visual on chased player

    // Son of Flame 53140 p5 6
    SPELL_BURNING_SPEED = 99414,  // aura speed
    SPELL_SUPERNOVA = 99112,  // if reaches hammer
    SPELL_VISUAL_PRESPAWN = 98983,  // fire beam.
    SPELL_HIT_ME = 100446, // dodge, hit chance.

    // Lava Scion 53231 p6 only intermission 2
    SPELL_BLAZING_HEAT = 100460, // trail - !Needs script!

    // Molten Elemental 53189 summ by molten inferno p2
    SPELL_ELEMENTAL_FIXATE = 82850,
    SPELL_MOLTEN_POWER = 100157, // empower other elementals 6y periodic

    // Lava Wave 53363 summ by sulf smash
    SPELL_LAVA_WAVE = 98873, // 3 summoned by sulf smash

    SPELL_BERSERK = 47008
};

enum Points
{
    POINT_SIDE = 1,
};

enum Events
{
    // Ragnaros
    EVENT_SULFURAS_SMASH = 1, // P1 - 3 fire pools on the ground - 93824 visual, after 4 secs comes the drop.
    // Npc 53266 is summoned in front where hammer will hit (boss summons npc in one of 5 designated locations), it casts damage spell 98608 @self after 4s (Boss casts 98710 on self after 1.5s), 
    // and summons three 53268 npc's, one on each side, which summon the waves and the waves go forward.
    EVENT_SUL_SMASH,
    EVENT_LAVA_WAVE,
    EVENT_WRATH_OF_RAGNAROS,   // P1 - 25p 3 targets, damage, knockback - 98263
    EVENT_HAND_OF_RAGNAROS,    // P1 - damage to all melee, knockback - 98237
    EVENT_MAGMA_TRAP,          // P1 - missile, persists till someone detonates it. who does is blown into air, and 80k damage -> whole raid.
    // missile is 98164 (triggers 98170 which summons npc 53086), npc visual is 98179, damage on trigger is 98175, vulnerability is 100238 (add with addaura).
    EVENT_MAGMA_BLAST,         // P1 enrage out of range - 98313

    EVENT_EMPOWER,
    EVENT_DREADFLAME,
    EVENT_SUBMERGE,
    EVENT_SONS_OF_FLAME,
    EVENT_MOLTEN_SEED,
    EVENT_RAGE_OF_RAGNAROS,     // Check items and quest.
    EVENT_ENFULGING_FLAMES,
    EVENT_WORLD_FLAMES1,
    EVENT_WORLD_FLAMES2,
    EVENT_WORLD_FLAMES3,
    EVENT_METEORITE,

    EVENT_SUPERHEATED,
    EVENT_BREATH_OF_FROST,
    EVENT_ENRAGE,               // 18 minutes.

    EVENT_DIE,

    // Sulfuras, Hand of Ragnaros
    EVENT_HEROIC_DANCE,

    // Molten Seed
    EVENT_CHECK_SPELL,

    // Molten Elemental
    EVENT_CHECK_ELEMENTALS_RANGE,

    // Sulfuras Smash
    EVENT_SMASH,

    // Event Phase Chain
    EVENT_PHASE_ONE,
    EVENT_PHASE_TWO,
    EVENT_PHASE_THREE,
    EVENT_PHASE_FOUR,
    EVENT_INTERMISSION_1,
    EVENT_INTERMISSION_2
};

enum Actions
{
    ACTION_START_DANCE = 1,
};

/*** Engulfing Flames ***/

Position const EngulfingPos[ENGULFING_FLAME_COUNT] =
{
    { 1072.441f, -103.039f, 55.785f, 3.379f },
    { 1038.027f, -93.194f, 55.923f, 0.393f },
    { 1037.907f, -75.963f, 55.923f, 0.847f },
    { 1025.552f, -57.613f, 55.779f, 6.175f },
    { 1029.401f, -38.686f, 55.790f, 5.747f },
    { 1040.756f, -23.403f, 55.924f, 5.343f },
    { 1057.850f, -15.040f, 55.782f, 4.963f },
    { 1074.199f, -14.966f, 55.789f, 4.663f },
    { 1057.500f, -55.968f, 53.238f, 3.172f },
};
Position const EngulfingPos2[ENGULFING_FLAME_COUNT] =
{
    { 1046.256f, -110.471f, 55.804f, 4.893f },
    { 1053.341f, -7.916f, 55.781f, 6.141f },
    { 1030.295f, -9.514f, 55.803f, 5.601f },
    { 1017.908f, -23.645f, 55.791f, 5.766f },
    { 1009.825f, -40.884f, 55.774f, 5.984f },
    { 1003.884f, -59.484f, 55.765f, 0.018f },
    { 1009.150f, -78.064f, 55.770f, 0.147f },
    { 1019.707f, -95.570f, 55.809f, 0.300f },
    { 1029.262f, -113.527f, 55.802f, 0.756f },
};

Position const EngulfingPos3[ENGULFING_FLAME_COUNT] =
{
    { 1013.335f, -105.794f, 55.802f, 0.615f },
    { 1020.382f, -124.228f, 55.803f, 1.361f },
    { 997.749f, -93.560f, 55.796f, 0.409f },
    { 986.682f, -76.356f, 55.786f, 0.271f },
    { 984.630f, -57.194f, 55.797f, 6.228f },
    { 987.328f, -38.069f, 55.790f, 5.989f },
    { 1000.162f, -22.790f, 55.794f, 5.679f },
    { 1015.802f, -10.481f, 55.802f, 5.635f },
    { 1025.504f, 2.655f, 55.802f, 5.391f },
};

/*** Sons of Flame ***/

const Position HammerMiddleSummons[] =
{
    //West Side
    { 1008.976f, -87.395f, 55.452f, 1.030f },
    { 1037.130f, -101.037f, 55.544f, 2.130f },
    { 1057.177f, -103.765f, 55.342f, 2.330f },
    { 1076.355f, -101.017f, 55.342f, 2.677f },
    //East Side
    { 1012.901f, -26.540f, 55.482f, 4.874f },
    { 1037.587f, -13.490f, 55.555f, 4.658f },
    { 1055.858f, -11.348f, 55.346f, 3.927f },
    { 1074.467f, -12.893f, 55.342f, 3.715f },
};

const Position HammerWestSummons[] =
{
    //West Side
    { 999.768f, -69.833f, 55.485f, 5.887f },
    { 1057.177f, -103.765f, 55.342f, 2.330f },
    { 1076.355f, -101.017f, 55.342f, 2.677f },
    //East Side
    { 999.505f, -45.725f, 55.476f, 5.435f },
    { 1012.901f, -26.540f, 55.482f, 4.874f },
    { 1037.587f, -13.490f, 55.555f, 4.658f },
    { 1055.858f, -11.348f, 55.346f, 3.927f },
    { 1074.467f, -12.893f, 55.342f, 3.715f },
};

const Position HammerEastSummons[] =
{
    //West Side
    { 999.768f, -69.833f, 55.485f, 5.887f },
    { 1008.976f, -87.395f, 55.452f, 1.030f },
    { 1037.130f, -101.037f, 55.544f, 2.130f },
    { 1057.177f, -103.765f, 55.342f, 2.330f },
    { 1076.355f, -101.017f, 55.342f, 2.677f },
    //East Side
    { 999.505f, -45.725f, 55.476f, 5.435f },
    { 1055.858f, -11.348f, 55.346f, 3.927f },
    { 1074.467f, -12.893f, 55.342f, 3.715f },
};

/*** Splitting Blow ***/
Position const SummonPositions[3] =
{
    { 1039.866f, -28.044f, 55.781f, 2.21f },  // 1 Top
    { 1028.017f, -58.241f, 55.781f, 3.12f },  // 2 Middle for Sulfuras
    { 1039.649f, -88.337f, 55.781f, 4.18f },  // 3 Bottom    
};

/*** Lava Scion ***/
Position const SpawnPos[2] =
{
    { 980.100f, -30.100f, 55.100f, 4.57f },   // spawnpos1
    { 980.100f, -80.100f, 55.100f, 1.42f },   // spawnpos2
};

/*** Heroic Npc's ***/
Position const HeroPos[3] =
{
    { 985.100f, -59.000f, 55.800f, 6.20f },   // Malfurion
    { 990.000f, -78.000f, 55.800f, 0.15f },   // Cenarius
    { 975.000f, -40.000f, 55.800f, 5.40f },   // Hamuul
};

/*####################
# RAGNAROS FIRELANDS #
####################*/

// 52409
class boss_ragnaros_firelands : public CreatureScript
{
public:
    boss_ragnaros_firelands() : CreatureScript("boss_ragnaros_firelands"){ }

    struct boss_ragnaros_firelandsAI : public BossAI
    {
        boss_ragnaros_firelandsAI(Creature* creature) : BossAI(creature, DATA_RAGNAROS), summons(me)
        {
            instance = me->GetInstanceScript();
            introDone = false;
        }

        InstanceScript* instance;
        EventMap events;
        SummonList summons;
        Creature* smash;
        Creature* splitting;
        bool HeartCheck, introDone, intermission1, intermission2, phase3, inMeleeRange, heroicPhase, died;

        void Reset()
        {
            if (instance)
                instance->SetData(DATA_RAGNAROS, NOT_STARTED);

            if (!me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE))
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);

            if (!introDone)
                me->AddAura(SPELL_SUBMERGE_SELF, me);

            events.Reset();
            summons.DespawnAll();
            intermission1 = false;
            intermission2 = false;
            HeartCheck = false;
            phase3 = false;
            inMeleeRange = false;
            heroicPhase = false;
            died = false;
            events.ScheduleEvent(EVENT_PHASE_ONE, 100);

            if (GameObject* door = me->FindNearestGameObject(GO_RAGNAROS_DOOR, 200.0f))
                door->SetGoState(GO_STATE_ACTIVE);

            me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_LAVALOGGED, true);

            _Reset();
        }

        void EnterEvadeMode()
        {
            Reset();

            me->GetMotionMaster()->MoveTargetedHome();
            me->SetHealth(me->GetMaxHealth());
            me->AddAura(SPELL_BASE_VISUAL, me);
            if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

            if (instance)
            {
                instance->SetData(DATA_RAGNAROS, FAIL);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            _EnterEvadeMode();
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (!introDone && who->IsWithinDistInMap(me, 30.0f))
            {
                Talk(SAY_AGGRO);
                introDone = true;
                me->AddAura(SPELL_BASE_VISUAL, me);
                me->SetByteValue(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_HOVER);
                me->RemoveAura(SPELL_SUBMERGE_SELF);
            }
        }

        void KilledUnit(Unit * /*victim*/)
        {
            Talk(SAY_KILL);
        }

        void JustDied(Unit * /*victim*/)
        {
            if (IsHeroic())
                Talk(SAY_DEATH_H);

            if (HeartCheck)
                me->SummonCreature(NPC_HEART_OF_RAGNAROS, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000);

            if (instance)
            {
                instance->SetData(DATA_RAGNAROS, DONE);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            if (GameObject* door = me->FindNearestGameObject(GO_RAGNAROS_DOOR, 200.0f))
                door->SetGoState(GO_STATE_ACTIVE);

            _JustDied();
        }

        void EnterCombat(Unit* /*who*/)
        {
            me->setActive(true);

            if (instance)
            {
                instance->SetData(DATA_RAGNAROS, IN_PROGRESS);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add
            }

            events.ScheduleEvent(EVENT_ENRAGE, 18 * MINUTE * IN_MILLISECONDS);

            if (GameObject* door = me->FindNearestGameObject(GO_RAGNAROS_DOOR, 200.0f))
                door->SetGoState(GO_STATE_READY);

            _EnterCombat();
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
            case ACTION_START_DANCE:
            {
                me->SetFlag(UNIT_FIELD_FLAGS_2, 0x20);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                me->SetDisableGravity(true);
                Movement::MoveSplineInit init(me);
                init.SetOrientationFixed(true);
                init.Launch();
                break;
            }
            }
        }

        void JustSummoned(Creature *summon)
        {
            summons.Summon(summon);
            summon->setActive(true);

            if (me->IsInCombat())
                summon->AI()->DoZoneInCombat();

            switch (summon->GetEntry())
            {
            case NPC_ENGULFING_FLAMES:
                summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                summon->CastSpell(summon, SPELL_VISUAL_ENGULFING, false);
                break;

            case NPC_MOLTEN_SEED:
                summon->CastSpell(summon, SPELL_MOLTEN_SEED_VISUAL, false);
                break;

            case NPC_PLATFORM_STALKER:
                summon->SetInCombatWithZone();
                summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                if (Creature* ragnaros = me->FindNearestCreature(NPC_RAGNAROS_CATA, 40.0f, true))
                    ragnaros->CastSpell(summon, SPELL_DREADFLAME, true);
                summon->SetReactState(REACT_PASSIVE);
                break;

            case NPC_DREADFLAME_SPAWN:
                summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                summon->CastSpell(summon, SPELL_DREADFLAME_SUMMON, false);
                summon->SetReactState(REACT_PASSIVE);
                break;

            case NPC_DREADFLAME:
                summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                summon->CastSpell(summon, SPELL_DREADFLAME_VISUAL, false);
                summon->CastSpell(summon, SPELL_DREADFLAME_DAMAGE, false);
                summon->SetReactState(REACT_PASSIVE);
                break;

            case NPC_CENARIUS:
            case NPC_MALFURION:
            case NPC_HAMUUL:
                summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE);
                break;

            default:
                break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (HealthBelowPct(71) && !intermission1)
            {
                Talk(SAY_INTERMISSION1);
                events.ScheduleEvent(EVENT_INTERMISSION_1, 1000);
                intermission1 = true;
            }

            if (HealthBelowPct(41) && !intermission2)
            {
                Talk(SAY_INTERMISSION2);
                events.ScheduleEvent(EVENT_INTERMISSION_2, 1000);
                intermission2 = true;
            }

            if (HealthBelowPct(11) && !IsHeroic() && !died)
            {
                Talk(SAY_DEATH);

                me->AttackStop();
                me->CastStop();
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                me->RemoveAllAuras();
                me->SummonGameObject(GO_CACHE_OF_THE_FIRELORD, 1016.043f, -57.436f, 55.333f, 3.151f, 0, 0, 0, 0, 30000);
                if (HeartCheck)
                    me->SummonCreature(NPC_HEART_OF_RAGNAROS, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000);

                if (instance)
                {
                    instance->SetData(DATA_RAGNAROS, DONE);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
                }

                events.ScheduleEvent(EVENT_DIE, 2000);
                me->HandleEmoteCommand(EMOTE_ONESHOT_SUBMERGE);
                died = true;

                if (GameObject* door = me->FindNearestGameObject(GO_RAGNAROS_DOOR, 200.0f))
                    door->SetGoState(GO_STATE_ACTIVE);
            }
            else if (HealthBelowPct(11) && IsHeroic() && !heroicPhase)
            {
                Talk(SAY_PHASE_HEROIC_TEXT);
                Talk(SAY_HEROIC_PHASE);
                events.ScheduleEvent(EVENT_PHASE_FOUR, 1000);
                heroicPhase = true;
            }

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_DIE:
                    me->Kill(me);
                    break;

                case EVENT_ENRAGE:
                    DoCast(me, SPELL_BERSERK);
                    break;

                    /**** STAGE 1 : By Fire Be Purged! ****/

                case EVENT_PHASE_ONE:
                    Talk(SAY_PURGE);
                    DoCast(me, SPELL_BURNING_WOUND);
                    events.ScheduleEvent(EVENT_SULFURAS_SMASH, 30000);
                    events.ScheduleEvent(EVENT_WRATH_OF_RAGNAROS, urand(4500, 6000));
                    events.ScheduleEvent(EVENT_HAND_OF_RAGNAROS, 24000);
                    events.ScheduleEvent(EVENT_MAGMA_TRAP, 16000);
                    events.ScheduleEvent(EVENT_MAGMA_BLAST, 5000);
                    events.ScheduleEvent(EVENT_RAGE_OF_RAGNAROS, 2500);
                    break;

                case EVENT_RAGE_OF_RAGNAROS:
                    if (!IsHeroic()) // Only on normal.
                    {
                        ThreatContainer::StorageType const & threatList = me->getThreatManager().getThreatList();

                        for (ThreatContainer::StorageType::const_iterator itr = threatList.begin(); itr != threatList.end(); ++itr)
                        {
                            if (Unit* unit = Unit::GetUnit(*me, (*itr)->getUnitGuid()))
                                if (unit->GetTypeId() == TYPEID_PLAYER)
                                    if (Player* player = unit->ToPlayer())
                                        if (player->hasQuest(QUEST_HEART_FLAME))
                                            if (player->GetQuestStatus(QUEST_HEART_FLAME) == QUEST_STATUS_INCOMPLETE)
                                            {
                                                if (!player->HasAura(SPELL_RAGE_OF_RAGNAROS))
                                                    player->CastSpell(player, SPELL_RAGE_OF_RAGNAROS, true);
                                                HeartCheck = true;
                                            }
                        }
                    }
                    break;

                case EVENT_SULFURAS_SMASH:
                {
                    Talk(SAY_SULFURAS_SMASH);
                    me->GetMotionMaster()->Clear();
                    me->AttackStop();
                    float x, y, z;
                    me->GetClosePoint(x, y, z, me->GetObjectSize() / 3, -12.0f);
                    smash = me->SummonCreature(NPC_SMASH, x, y, 55.8f, me->GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000);
                    events.ScheduleEvent(EVENT_SUL_SMASH, 1500);

                    events.ScheduleEvent(EVENT_SULFURAS_SMASH, urand(26000, 34000));
                }
                break;

                case EVENT_SUL_SMASH:
                    Talk(SAY_SMASH);
                    me->SetFacingToObject(smash);
                    DoCast(me, SPELL_SULFURAS_SMASH_RAG_SELF);
                    if (Unit* target = SelectTarget(SELECT_TARGET_NEAREST, 0, 80.0f, true))
                        me->AI()->AttackStart(target);
                    break;

                case EVENT_MAGMA_TRAP: // Not on tank!
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.0f, true)) // SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me))
                        me->CastSpell(target, SPELL_MAGMA_TRAP, true);
                    events.ScheduleEvent(EVENT_MAGMA_TRAP, urand(23000, 29000));
                    break;

                case EVENT_WRATH_OF_RAGNAROS: // Not on tank!
                {
                    std::list<Unit*> targets;
                    SelectTargetList(targets, RAID_MODE<int32>(1, 3, 1, 3), SELECT_TARGET_RANDOM, 200.0f, true);
                    if (!targets.empty())
                        for (std::list<Unit*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            DoCast(*itr, SPELL_WRATH_OF_RAGNAROS);
                    events.ScheduleEvent(EVENT_WRATH_OF_RAGNAROS, urand(27000, 33000));
                }
                break;

                case EVENT_HAND_OF_RAGNAROS:
                    DoCast(me, SPELL_HAND_OF_RAGNAROS);
                    events.ScheduleEvent(EVENT_HAND_OF_RAGNAROS, urand(23000, 28000));
                    break;

                case EVENT_MAGMA_BLAST:
                    if (Unit* target = me->GetVictim())
                    {
                        if (target->IsWithinDistInMap(me, 1.0f)) // check if tank is in melee range.
                            inMeleeRange = true;
                        else // Killing tank softly with his song.
                        {
                            inMeleeRange = false;
                            Talk(SAY_ENRAGE);
                            DoCast(target, SPELL_MAGMA_BLAST);
                        }
                    }
                    events.ScheduleEvent(EVENT_MAGMA_BLAST, urand(4000, 5000));
                    break;

                    // ====== INTERMISSION 1 : Minions of Fire! ====== //

                case EVENT_INTERMISSION_1:
                    me->RemoveAurasDueToSpell(SPELL_BASE_VISUAL);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->GetMotionMaster()->Clear();
                    me->AttackStop();
                    me->SetReactState(REACT_PASSIVE);
                    Talk(SAY_SPLITTING);

                    switch (urand(0, 2))
                    {
                    case 0: // Top
                    {
                        splitting = me->SummonCreature(NPC_SPLITTING_BLOW, SummonPositions[0].GetPositionX(), SummonPositions[0].GetPositionY(), SummonPositions[0].GetPositionZ(), SummonPositions[0].GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000);
                        for (uint32 x = 0; x < 8; ++x)
                            me->SummonCreature(NPC_SON_OF_FLAME, HammerEastSummons[x], TEMPSUMMON_TIMED_DESPAWN, 57500);
                        me->SetFacingToObject(splitting);
                        Movement::MoveSplineInit init(me);
                        init.SetOrientationFixed(true);
                        init.Launch();
                        DoCast(me, SPELL_SPLITTING_BLOW_NORTH);
                    }
                    break;

                    case 1: // Mid
                    {
                        splitting = me->SummonCreature(NPC_SPLITTING_BLOW, SummonPositions[1].GetPositionX(), SummonPositions[1].GetPositionY(), SummonPositions[1].GetPositionZ(), SummonPositions[1].GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000);
                        for (uint32 x = 0; x < 8; ++x)
                            me->SummonCreature(NPC_SON_OF_FLAME, HammerMiddleSummons[x], TEMPSUMMON_TIMED_DESPAWN, 57500);
                        me->SetFacingToObject(splitting);
                        Movement::MoveSplineInit init(me);
                        init.SetOrientationFixed(true);
                        init.Launch();
                        DoCast(me, SPELL_SPLITTING_BLOW_MID);
                    }
                    break;

                    case 2: // Bottom
                    {
                        splitting = me->SummonCreature(NPC_SPLITTING_BLOW, SummonPositions[2].GetPositionX(), SummonPositions[2].GetPositionY(), SummonPositions[2].GetPositionZ(), SummonPositions[2].GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000);
                        for (uint32 x = 0; x < 8; ++x)
                            me->SummonCreature(NPC_SON_OF_FLAME, HammerWestSummons[x], TEMPSUMMON_TIMED_DESPAWN, 57500);
                        me->SetFacingToObject(splitting);
                        Movement::MoveSplineInit init(me);
                        init.SetOrientationFixed(true);
                        init.Launch();
                        DoCast(me, SPELL_SPLITTING_BLOW_SOUTH);
                    }
                    break;
                    }

                    events.CancelEvent(EVENT_SULFURAS_SMASH);
                    events.CancelEvent(EVENT_WRATH_OF_RAGNAROS);
                    events.CancelEvent(EVENT_HAND_OF_RAGNAROS);
                    events.CancelEvent(EVENT_MAGMA_TRAP);
                    events.CancelEvent(EVENT_MAGMA_BLAST);
                    events.ScheduleEvent(EVENT_SUBMERGE, 8000);
                    events.ScheduleEvent(EVENT_PHASE_TWO, 45000);
                    break;

                case EVENT_SUBMERGE:
                    me->AddAura(SPELL_SUBMERGE, me);
                    break;

                    /**** STAGE 2 : Sulfuras Will Be Your End! ****/

                case EVENT_PHASE_TWO:
                {
                    Talk(SAY_PHASE_2);
                    Movement::MoveSplineInit init(me);
                    init.SetOrientationFixed(false);
                    init.Launch();
                    me->RemoveAurasDueToSpell(SPELL_DISABLE_ANIM);
                    me->RemoveAurasDueToSpell(SPELL_SUBMERGE);
                    me->AddAura(SPELL_BASE_VISUAL, me);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    Talk(SAY_NEW_PHASE);
                    if (Unit* target = SelectTarget(SELECT_TARGET_NEAREST, 0, 80.0f, true))
                        me->AI()->AttackStart(target);

                    if (IsHeroic())
                    {
                        events.ScheduleEvent(EVENT_SULFURAS_SMASH, 6000);
                        events.ScheduleEvent(EVENT_WORLD_FLAMES1, 60000); // 30 in p3
                    }
                    else
                    {
                        events.ScheduleEvent(EVENT_SULFURAS_SMASH, 15500);
                        events.ScheduleEvent(EVENT_ENFULGING_FLAMES, 40000);
                    }
                    events.ScheduleEvent(EVENT_MOLTEN_SEED, urand(18500, 24000));
                    events.ScheduleEvent(EVENT_MAGMA_BLAST, 5000);
                }
                break;

                case EVENT_MOLTEN_SEED:
                {
                    std::list<Unit*> targets;
                    SelectTargetList(targets, RAID_MODE<int32>(10, 20, 10, 20), SELECT_TARGET_RANDOM, 200.0f, true);
                    if (!targets.empty())
                        for (std::list<Unit*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        {
                            DoCast((*itr), SPELL_MOLTEN_SEED_MISSILE);
                            me->SummonCreature(NPC_MOLTEN_SEED, (*itr)->GetPositionX(), (*itr)->GetPositionY(), (*itr)->GetPositionZ(), (*itr)->GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000);
                        }

                    events.ScheduleEvent(EVENT_MOLTEN_SEED, 60000);
                }
                break;

                case EVENT_ENFULGING_FLAMES:
                    Talk(SAY_ENGULFING);
                    Talk(SAY_ENGULFING_FLAMES_TEXT);
                    DoCast(me, SPELL_ENGULFING_FLAMES);

                    switch (urand(0, 2))
                    {
                    case 0:
                        for (uint32 i = 0; i < ENGULFING_FLAME_COUNT; ++i)
                            me->SummonCreature(NPC_ENGULFING_FLAMES, EngulfingPos[i], TEMPSUMMON_CORPSE_DESPAWN, 1000);
                        break;

                    case 1:
                        for (uint32 i = 0; i < ENGULFING_FLAME_COUNT; ++i)
                            me->SummonCreature(NPC_ENGULFING_FLAMES, EngulfingPos2[i], TEMPSUMMON_CORPSE_DESPAWN, 1000);
                        break;

                    case 2:
                        for (uint32 i = 0; i < ENGULFING_FLAME_COUNT; ++i)
                            me->SummonCreature(NPC_ENGULFING_FLAMES, EngulfingPos3[i], TEMPSUMMON_CORPSE_DESPAWN, 1000);
                        break;
                    }

                    events.ScheduleEvent(EVENT_ENFULGING_FLAMES, phase3 ? 30000 : 40000); // 30 in p3
                    break;

                case EVENT_WORLD_FLAMES1:
                    DoCast(me, SPELL_WORLD_IN_FLAMES);
                    Talk(SAY_WORLD);

                    for (uint32 i = 0; i < ENGULFING_FLAME_COUNT; ++i)
                        me->SummonCreature(NPC_ENGULFING_FLAMES, EngulfingPos[i], TEMPSUMMON_CORPSE_DESPAWN, 1000);
                    events.ScheduleEvent(EVENT_WORLD_FLAMES2, 3500);
                    events.ScheduleEvent(EVENT_WORLD_FLAMES3, 7000);

                    events.ScheduleEvent(EVENT_WORLD_FLAMES1, phase3 ? 30000 : 60000); // 30 in p3
                    break;

                case EVENT_WORLD_FLAMES2:
                    for (uint32 i = 0; i < ENGULFING_FLAME_COUNT; ++i)
                        me->SummonCreature(NPC_ENGULFING_FLAMES, EngulfingPos2[i], TEMPSUMMON_CORPSE_DESPAWN, 1000);
                    break;

                case EVENT_WORLD_FLAMES3:
                    for (uint32 i = 0; i < ENGULFING_FLAME_COUNT; ++i)
                        me->SummonCreature(NPC_ENGULFING_FLAMES, EngulfingPos3[i], TEMPSUMMON_CORPSE_DESPAWN, 1000);
                    break;

                    // =====  INTERMISSION 2 : Denizens of Flame! ====== //

                case EVENT_INTERMISSION_2:
                    me->RemoveAurasDueToSpell(SPELL_BASE_VISUAL);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->GetMotionMaster()->Clear();
                    me->AttackStop();
                    me->SetReactState(REACT_PASSIVE);
                    Talk(SAY_SPLITTING);

                    switch (urand(0, 2))
                    {
                    case 0: // Top
                    {
                        splitting = me->SummonCreature(NPC_SPLITTING_BLOW, SummonPositions[0].GetPositionX(), SummonPositions[0].GetPositionY(), SummonPositions[0].GetPositionZ(), SummonPositions[0].GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000);
                        for (uint32 x = 0; x < 8; ++x)
                            me->SummonCreature(NPC_SON_OF_FLAME, HammerEastSummons[x], TEMPSUMMON_TIMED_DESPAWN, 57500);
                        me->SetFacingToObject(splitting);
                        Movement::MoveSplineInit init(me);
                        init.SetOrientationFixed(true);
                        init.Launch();
                        DoCast(me, SPELL_SPLITTING_BLOW_NORTH);
                    }
                    break;

                    case 1: // Mid
                    {
                        splitting = me->SummonCreature(NPC_SPLITTING_BLOW, SummonPositions[1].GetPositionX(), SummonPositions[1].GetPositionY(), SummonPositions[1].GetPositionZ(), SummonPositions[1].GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000);
                        for (uint32 x = 0; x < 8; ++x)
                            me->SummonCreature(NPC_SON_OF_FLAME, HammerMiddleSummons[x], TEMPSUMMON_TIMED_DESPAWN, 57500);
                        me->SetFacingToObject(splitting);
                        Movement::MoveSplineInit init(me);
                        init.SetOrientationFixed(true);
                        init.Launch();
                        DoCast(me, SPELL_SPLITTING_BLOW_MID);
                    }
                    break;

                    case 2: // Bottom
                    {
                        splitting = me->SummonCreature(NPC_SPLITTING_BLOW, SummonPositions[2].GetPositionX(), SummonPositions[2].GetPositionY(), SummonPositions[2].GetPositionZ(), SummonPositions[2].GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000);
                        for (uint32 x = 0; x < 8; ++x)
                            me->SummonCreature(NPC_SON_OF_FLAME, HammerWestSummons[x], TEMPSUMMON_TIMED_DESPAWN, 57500);
                        me->SetFacingToObject(splitting);
                        Movement::MoveSplineInit init(me);
                        init.SetOrientationFixed(true);
                        init.Launch();
                        DoCast(me, SPELL_SPLITTING_BLOW_SOUTH);
                    }
                    break;
                    }

                    for (uint8 i = 0; i < 2; i++)
                        me->SummonCreature(NPC_LAVA_SCION, SpawnPos[i], TEMPSUMMON_CORPSE_DESPAWN, 1000);

                    events.CancelEvent(EVENT_SULFURAS_SMASH);
                    events.CancelEvent(EVENT_MOLTEN_SEED);
                    events.CancelEvent(EVENT_MAGMA_BLAST);
                    if (IsHeroic())
                        events.CancelEvent(EVENT_WORLD_FLAMES1);
                    else
                        events.CancelEvent(EVENT_ENFULGING_FLAMES);

                    events.ScheduleEvent(EVENT_SUBMERGE, 8000);
                    events.ScheduleEvent(EVENT_PHASE_THREE, 45000);
                    break;

                    /**** STAGE 3 : Begone From My Realm! ****/

                case EVENT_PHASE_THREE:
                {
                    Talk(SAY_PHASE_3);
                    Movement::MoveSplineInit init(me);
                    init.SetOrientationFixed(false);
                    init.Launch();
                    me->RemoveAurasDueToSpell(SPELL_DISABLE_ANIM);
                    me->RemoveAurasDueToSpell(SPELL_SUBMERGE);
                    me->AddAura(SPELL_BASE_VISUAL, me);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    Talk(SAY_NEW_PHASE);
                    if (Unit* target = SelectTarget(SELECT_TARGET_NEAREST, 0, 80.0f, true))
                        me->AI()->AttackStart(target);
                    phase3 = true;

                    if (IsHeroic())
                    {
                        events.ScheduleEvent(EVENT_SULFURAS_SMASH, 15500);
                        events.ScheduleEvent(EVENT_WORLD_FLAMES1, 30000);
                    }
                    else
                    {
                        events.ScheduleEvent(EVENT_SULFURAS_SMASH, 15500);
                        events.ScheduleEvent(EVENT_ENFULGING_FLAMES, 40000);
                    }
                    events.ScheduleEvent(EVENT_METEORITE, 45000);
                    events.ScheduleEvent(EVENT_MAGMA_BLAST, 5000);
                }
                break;

                case EVENT_METEORITE:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.0f, true))
                        DoCast(target, SPELL_LIVING_METEOR);
                    events.ScheduleEvent(EVENT_METEORITE, 45000);
                    break;

                    /**** STAGE 4 : The True Power of the Firelord! ****/

                case EVENT_PHASE_FOUR:
                    Talk(SAY_AID);
                    Talk(SAY_PHASE_HEROIC_TEXT);
                    me->RemoveAurasDueToSpell(SPELL_BASE_VISUAL);
                    me->SetHealth(me->GetMaxHealth() / 2);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                    events.ScheduleEvent(EVENT_SUPERHEATED, 10000);
                    events.ScheduleEvent(EVENT_EMPOWER, 12000);
                    events.ScheduleEvent(EVENT_HEROIC_DANCE, 2000);
                    break;

                case EVENT_HEROIC_DANCE:
                    if (Creature* malfurion = me->SummonCreature(NPC_MALFURION, HeroPos[0].GetPositionX(), HeroPos[0].GetPositionY(), HeroPos[0].GetPositionZ(), HeroPos[0].GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000))
                        malfurion->AI()->DoAction(ACTION_START_DANCE);
                    if (Creature* cenarius = me->SummonCreature(NPC_CENARIUS, HeroPos[1].GetPositionX(), HeroPos[1].GetPositionY(), HeroPos[1].GetPositionZ(), HeroPos[1].GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000))
                        cenarius->AI()->DoAction(ACTION_START_DANCE);
                    if (Creature* hamuul = me->SummonCreature(NPC_HAMUUL, HeroPos[2].GetPositionX(), HeroPos[2].GetPositionY(), HeroPos[2].GetPositionZ(), HeroPos[2].GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000))
                        hamuul->AI()->DoAction(ACTION_START_DANCE);
                    break;

                case EVENT_SUPERHEATED:
                    DoCast(me, SPELL_SUPERHEATED);
                    events.ScheduleEvent(EVENT_SUPERHEATED, 10000);
                    break;

                case EVENT_EMPOWER:
                    DoCast(me, SPELL_EMPOWER);
                    events.ScheduleEvent(EVENT_EMPOWER, 10000);
                    break;

                case EVENT_DREADFLAME:
                    for (uint32 i = 0; i < RAID_MODE<uint8>(2, 2, 2, 5); ++i)
                        me->SummonCreature(NPC_PLATFORM_STALKER, me->GetPositionX() + urand(-20, 20), me->GetPositionY() + urand(-20, 20), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000);
                    //http://www.wowhead.com/npc=53952 - Ragnaros platform stalkers... can't imagine a different use for the bitches
                    events.ScheduleEvent(EVENT_DREADFLAME, 12000);
                    break;
                }
            }

            if (!me->HasAura(SPELL_SUBMERGE))
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_ragnaros_firelandsAI(creature);
    }

};

// 53266
class npc_sulfuras_smash_trigger : public CreatureScript
{
public:
    npc_sulfuras_smash_trigger() : CreatureScript("npc_sulfuras_smash_trigger") { }

    struct npc_sulfuras_smash_triggerAI : public ScriptedAI
    {
        npc_sulfuras_smash_triggerAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        uint32 m_uiSummonTimer; // Summon the three npc's.
        uint32 m_uiDamageTimer; // Damage.
        uint32 m_uiDespawnTimer;

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            me->AddAura(SPELL_SULFURAS_SMASH_VISUAL, me);
            me->SetReactState(REACT_PASSIVE);
            Movement::MoveSplineInit init(me);
            init.SetOrientationFixed(true);
            init.Launch();
            m_uiSummonTimer = 100;
            m_uiDamageTimer = 4000;
            m_uiDespawnTimer = 5000;
        }

        void EnterCombat(Unit* /*who*/) { }

        void UpdateAI(uint32 diff)
        {
            if (m_uiSummonTimer <= diff)
            {
                if (Creature* smash1 = me->SummonCreature(NPC_SULFURAS_SMASH, me->GetPositionX() - 5, me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN))
                {
                    smash1->SetReactState(REACT_PASSIVE);
                    smash1->SetFacingTo(3.22f);
                    Movement::MoveSplineInit init(smash1);
                    init.SetOrientationFixed(true);
                    init.Launch();
                }
                if (Creature* smash2 = me->SummonCreature(NPC_SULFURAS_SMASH, me->GetPositionX(), me->GetPositionY() + 5, me->GetPositionZ(), me->GetOrientation() + 3, TEMPSUMMON_MANUAL_DESPAWN))
                {
                    smash2->SetReactState(REACT_PASSIVE);
                    smash2->SetFacingTo(1.49f);
                    Movement::MoveSplineInit init(smash2);
                    init.SetOrientationFixed(true);
                    init.Launch();
                }
                if (Creature* smash3 = me->SummonCreature(NPC_SULFURAS_SMASH, me->GetPositionX(), me->GetPositionY() - 5, me->GetPositionZ(), me->GetOrientation() - 3, TEMPSUMMON_MANUAL_DESPAWN))
                {
                    smash3->SetReactState(REACT_PASSIVE);
                    smash3->SetFacingTo(4.89f);
                    Movement::MoveSplineInit init(smash3);
                    init.SetOrientationFixed(true);
                    init.Launch();
                }
                m_uiSummonTimer = -1;
            }
            else
                m_uiSummonTimer -= diff;

            if (m_uiDamageTimer <= diff)
            {
                DoCast(me, SPELL_SULFURAS_SMASH_DAMAGE);
                m_uiDamageTimer = -1;
            }
            else
                m_uiDamageTimer -= diff;

            if (m_uiDespawnTimer <= diff)
            {
                me->DespawnOrUnsummon();
                m_uiDespawnTimer = -1;
            }
            else
                m_uiDespawnTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_sulfuras_smash_triggerAI(creature);
    }

};

// 53268
class npc_sulfuras_smash : public CreatureScript
{
public:
    npc_sulfuras_smash() : CreatureScript("npc_sulfuras_smash") { }

    struct npc_sulfuras_smashAI : public ScriptedAI
    {
        npc_sulfuras_smashAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;
        Creature* wave;
        uint32 m_uiDespawnTimer;

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            events.Reset();
            events.ScheduleEvent(EVENT_SMASH, 3900);
            m_uiDespawnTimer = 4900;
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_SMASH:
                    wave = me->SummonCreature(NPC_LAVA_WAVE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN);
                    wave->SetFacingTo(me->GetOrientation());
                    break;
                }
            }

            if (m_uiDespawnTimer <= diff)
            {
                me->DespawnOrUnsummon();
                m_uiDespawnTimer = -1;
            }
            else
                m_uiDespawnTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_sulfuras_smashAI(creature);
    }
};

// 53086
class npc_magma_trap : public CreatureScript
{
public:
    npc_magma_trap() : CreatureScript("npc_magma_trap") { }

    struct npc_magma_trapAI : public ScriptedAI
    {
        npc_magma_trapAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        uint32 m_uiDespawnTimer;
        uint32 m_uiCheckTimer;

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            me->AddAura(SPELL_MAGMA_TRAP_VISUAL, me);
            me->SetReactState(REACT_PASSIVE);
            Movement::MoveSplineInit init(me);
            init.SetOrientationFixed(true);
            init.Launch();
            m_uiDespawnTimer = 70000;
            m_uiCheckTimer = 1000;
        }

        void UpdateAI(uint32 diff)
        {
            if (m_uiCheckTimer <= diff)
            {
                if (Unit* who = me->FindNearestPlayer(4.0f, true))
                    if (who->IsWithinDistInMap(me, 4.0f))
                    {
                        DoCast(me, SPELL_MAGMA_TRAP_ERUPTION);
                        me->AddAura(SPELL_MAGMA_TRAP_VULNERABILITY, who);
                        me->DespawnOrUnsummon(900);
                    }

                m_uiCheckTimer = 1000;
            }
            else
                m_uiCheckTimer -= diff;

            if (m_uiDespawnTimer <= diff)
            {
                me->DespawnOrUnsummon();
                m_uiDespawnTimer = -1;
            }
            else
                m_uiDespawnTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_magma_trapAI(creature);
    }
};

// 53393
class npc_splitting_blow : public CreatureScript
{
public:
    npc_splitting_blow() : CreatureScript("npc_splitting_blow") { }

    struct npc_splitting_blowAI : public ScriptedAI
    {
        npc_splitting_blowAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        uint32 m_uiDespawnTimer;

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            me->SetReactState(REACT_PASSIVE);
            Movement::MoveSplineInit init(me);
            init.SetOrientationFixed(true);
            init.Launch();
            m_uiDespawnTimer = 8000;
        }

        void UpdateAI(uint32 diff)
        {
            if (m_uiDespawnTimer <= diff)
            {
                me->SummonCreature(NPC_SULFURAS, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN);
                me->DespawnOrUnsummon(100);
                m_uiDespawnTimer = -1;
            }
            else
                m_uiDespawnTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_splitting_blowAI(creature);
    }
};

// 53420
class npc_sulfuras : public CreatureScript
{
public:
    npc_sulfuras() : CreatureScript("npc_sulfuras") { }

    struct npc_sulfurasAI : public ScriptedAI
    {
        npc_sulfurasAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        uint32 m_uiDespawnTimer;

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            me->AddAura(SPELL_SULFURAS_AURA, me);
            me->AI()->Talk(SAY_SONS);
            me->SetReactState(REACT_PASSIVE);
            Movement::MoveSplineInit init(me);
            init.SetOrientationFixed(true);
            init.Launch();
            m_uiDespawnTimer = 44900;
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (m_uiDespawnTimer <= diff)
            {
                me->DespawnOrUnsummon();
                m_uiDespawnTimer = -1;
            }
            else
                m_uiDespawnTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_sulfurasAI(creature);
    }
};

// 12143 53140
class npc_son_of_flame : public CreatureScript
{
public:
    npc_son_of_flame() : CreatureScript("npc_son_of_flame") { }

    struct npc_son_of_flameAI : public ScriptedAI
    {
        npc_son_of_flameAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        uint32 m_uiEmergeTimer;
        uint32 m_uiSulfurasCheckTimer;

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            me->SetSpeed(MOVE_RUN, 0.1f);
            me->SetSpeed(MOVE_WALK, 0.1f);
            me->SetWalk(true);
            me->AddAura(SPELL_VISUAL_PRESPAWN, me);
            m_uiEmergeTimer = urand(9000, 40000);
            m_uiSulfurasCheckTimer = 9500;
        }

        void DamageTaken(Unit* /*who*/, uint32& /*damage*/)
        {
            if (me->HasAura(SPELL_BURNING_SPEED))
                if (Aura * aura = me->GetAura(SPELL_BURNING_SPEED))
                {
                    if (aura->GetStackAmount() > 1)
                        me->SetAuraStack(SPELL_BURNING_SPEED, me, aura->GetStackAmount() - 1);
                    else
                        me->RemoveAurasDueToSpell(SPELL_BURNING_SPEED);
                }
        }

        void UpdateAI(uint32 diff)
        {
            if (HealthBelowPct(50))
                me->RemoveAurasDueToSpell(SPELL_BURNING_SPEED);

            if (m_uiEmergeTimer <= diff)
            {
                me->RemoveAurasDueToSpell(SPELL_VISUAL_PRESPAWN);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                me->AddAura(SPELL_BURNING_SPEED, me);
                me->SetAuraStack(SPELL_BURNING_SPEED, me, 10);
                me->AddAura(SPELL_HIT_ME, me);
                me->SetSpeed(MOVE_RUN, 0.5f);
                me->SetSpeed(MOVE_WALK, 0.5f);
                if (Creature* sulfuras = me->FindNearestCreature(NPC_SULFURAS, 100.0f, true))
                    me->GetMotionMaster()->MoveChase(sulfuras);
                me->SetReactState(REACT_PASSIVE);
                m_uiEmergeTimer = -1;
            }
            else
                m_uiEmergeTimer -= diff;

            if (m_uiSulfurasCheckTimer <= diff)
            {
                if (Creature* sulfuras = me->FindNearestCreature(NPC_SULFURAS, 2.0f, true))
                {
                    sulfuras->CastSpell(sulfuras, SPELL_SUPERNOVA, false);
                    me->DespawnOrUnsummon(100);
                }
                m_uiSulfurasCheckTimer = 1500;
            }
            else
                m_uiSulfurasCheckTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_son_of_flameAI(creature);
    }
};

// 53186
class npc_molten_seed : public CreatureScript
{
public:
    npc_molten_seed() : CreatureScript("npc_molten_seed") { }

    struct npc_molten_seedAI : public ScriptedAI
    {
        npc_molten_seedAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        uint32 m_uiDespawnTimer;
        uint32 m_uiMoltenInfernoTimer;

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            me->SetReactState(REACT_PASSIVE);
            Movement::MoveSplineInit init(me);
            init.SetOrientationFixed(true);
            init.Launch();
            m_uiMoltenInfernoTimer = 10000;
            m_uiDespawnTimer = 15000;
        }
           
        void UpdateAI(uint32 diff)
        {
            if (m_uiMoltenInfernoTimer <= diff)
            {
                DoCast(me, SPELL_MOLTEN_INFERNO);
                DoCastAOE(SPELL_MOLTEN_SEED_MISSILE);
                me->SummonCreature(NPC_MOLTEN_ELEMENTAL, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000);
                m_uiMoltenInfernoTimer = 10000;
            }
            else
                m_uiMoltenInfernoTimer -= diff;

            if (m_uiDespawnTimer <= diff)
            {
                me->DespawnOrUnsummon();
                m_uiDespawnTimer = -1;
            }
            else
                m_uiDespawnTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_molten_seedAI(creature);
    }
};

// 53231
class npc_lava_scion : public CreatureScript
{
public:
    npc_lava_scion() : CreatureScript("npc_lava_scion") { }

    struct npc_lava_scionAI : public ScriptedAI
    {
        npc_lava_scionAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        uint32 m_uiBlazingHeatTimer;

        void Reset()
        {
            m_uiBlazingHeatTimer = 15000;
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (m_uiBlazingHeatTimer <= diff)
            {
                if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    DoCast(target, SPELL_BLAZING_HEAT);
                m_uiBlazingHeatTimer = urand(15000, 25000);
            }
            else
                m_uiBlazingHeatTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lava_scionAI(creature);
    }
};

// 53189
class npc_molten_elemental : public CreatureScript
{
public:
    npc_molten_elemental() : CreatureScript("npc_molten_elemental") { }

    struct npc_molten_elementalAI : public ScriptedAI
    {
        npc_molten_elementalAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        uint32 m_uiMoltenPowerCheckTimer;

        void Reset()
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
            {
                me->AI()->AttackStart(target);
                me->AddThreat(target, 1000.0f);
                me->CastSpell(target, SPELL_ELEMENTAL_FIXATE, false);
                // Not tauntable.
                me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, true);
            }

            m_uiMoltenPowerCheckTimer = 3000;
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (m_uiMoltenPowerCheckTimer <= diff && IsHeroic())
            {
                if (GetClosestCreatureWithEntry(me, NPC_MOLTEN_ELEMENTAL, 6.0f))
                    DoCast(me, SPELL_MOLTEN_POWER);
                m_uiMoltenPowerCheckTimer = 3000;
            }
            else
                m_uiMoltenPowerCheckTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_molten_elementalAI(creature);
    }
};

// 53485
class npc_engulfing_flames : public CreatureScript
{
public:
    npc_engulfing_flames() : CreatureScript("npc_engulfing_flames") { }

    struct npc_engulfing_flamesAI : public ScriptedAI
    {
        npc_engulfing_flamesAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        uint32 m_uiDespawnTimer;


        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            me->CastSpell(me, SPELL_ENGULFING_FLAMES_DAMAGE, false);
            me->SetReactState(REACT_PASSIVE);
            Movement::MoveSplineInit init(me);
            init.SetOrientationFixed(true);
            init.Launch();
            m_uiDespawnTimer = 4000;
        }

        void UpdateAI(uint32 diff)
        {
            if (m_uiDespawnTimer <= diff)
            {
                me->DespawnOrUnsummon();
            }
            else
                m_uiDespawnTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_engulfing_flamesAI(creature);
    }
};

// 54127
class npc_dreadflame : public CreatureScript
{
public:
    npc_dreadflame() : CreatureScript("npc_dreadflame") { }

    struct npc_dreadflameAI : public ScriptedAI
    {
        npc_dreadflameAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        uint32 m_uiDreadTimer;
        uint32 m_uiCheckDeluge;

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_PASSIVE);
            me->DespawnOrUnsummon(60000);
            m_uiDreadTimer = 3000;
        }

        void UpdateAI(uint32 diff)
        {
            if (m_uiCheckDeluge <= diff)
            {
                if (Player* player = me->FindNearestPlayer(2.5f, true))
                    if (player->IsWithinDistInMap(me, 2.5f) && player->HasAura(SPELL_DELUGE))
                    {
                        DoCast(me, SPELL_WATER_VISUAL);
                        me->DespawnOrUnsummon();
                    }

                m_uiCheckDeluge = 250;
            }
            else
                m_uiCheckDeluge -= diff;

            if (m_uiDreadTimer <= diff)
            {
                me->SummonCreature(NPC_DREADFLAME_SPAWN, me->GetPositionX() + 3, me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000);
                me->SummonCreature(NPC_DREADFLAME_SPAWN, me->GetPositionX() - 3, me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000);
                me->SummonCreature(NPC_DREADFLAME_SPAWN, me->GetPositionX(), me->GetPositionY() + 3, me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000);
                me->SummonCreature(NPC_DREADFLAME_SPAWN, me->GetPositionX(), me->GetPositionY() - 3, me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000);
                m_uiDreadTimer = 3500;
            }
            else
                m_uiDreadTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_dreadflameAI(creature);
    }
};

// 53500
class npc_living_meteor : public CreatureScript
{
public:
    npc_living_meteor() : CreatureScript("npc_living_meteor") { }

    struct npc_living_meteorAI : public ScriptedAI
    {
        npc_living_meteorAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        uint32 m_uiRangeCheckTimer;
        uint32 m_uiTargetChangeTimer;
        uint32 m_uiLavalogedCheckTimer;

        void Reset()
        {
            me->SetSpeed(MOVE_RUN, 0.25f);
            me->SetSpeed(MOVE_WALK, 0.25f);
            DoCast(me, SPELL_INCR_RUN);
            DoCast(me, SPELL_COMBUSTIBLE);

            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
            {
                if (me->Attack(target, true))
                    me->GetMotionMaster()->MoveChase(target);

                me->AddThreat(target, 1000.0f);
                me->CastSpell(target, SPELL_FLAMING_FIXATE, false);
                // Not tauntable.
                me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, true);
            }

            me->SetReactState(REACT_PASSIVE);
            m_uiRangeCheckTimer = 2000;
            m_uiTargetChangeTimer = 20000;
            m_uiLavalogedCheckTimer = 3000;
        }

        void DamageTaken(Unit* /*who*/, uint32& /*damage*/)
        {
            DoCast(me, SPELL_COMBUSTION);
        }

        void UpdateAI(uint32 diff)
        {
            if (m_uiRangeCheckTimer <= diff)
            {
                if (me->IsWithinDistInMap(me->GetVictim(), 2.0f))
                {
                    DoCast(me, SPELL_IMPACT);
                    me->GetVictim()->RemoveAurasDueToSpell(SPELL_FLAMING_FIXATE);
                    me->DespawnOrUnsummon();
                }

                m_uiRangeCheckTimer = 2000;
            }
            else
                m_uiRangeCheckTimer -= diff;

            if (m_uiTargetChangeTimer <= diff)
            {
                me->GetVictim()->RemoveAurasDueToSpell(SPELL_FLAMING_FIXATE);
                me->AddThreat(me->GetVictim(), -1000.0f);

                if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
                {
                    me->GetMotionMaster()->MoveChase(target);
                    me->AddThreat(target, 1000.0f);
                    me->CastSpell(target, SPELL_FLAMING_FIXATE, false);
                }

                m_uiTargetChangeTimer = urand(20000, 30000);
            }
            else
                m_uiTargetChangeTimer -= diff;

            if (m_uiLavalogedCheckTimer <= diff && IsHeroic())
            {
                if (GetClosestCreatureWithEntry(me, NPC_LAVA_WAVE, 3.0f))
                    DoCast(me, SPELL_LAVALOGGED);

                if (GetClosestCreatureWithEntry(me, NPC_BREATH_OF_FROST, 3.0f))
                {
                    me->RemoveAllAuras();
                    me->AddAura(SPELL_METEOR_OF_FROST, me);
                }

                m_uiLavalogedCheckTimer = 500;
            }
            else
                m_uiLavalogedCheckTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_living_meteorAI(creature);
    }
};

// 54074
class npc_entrapping_roots : public CreatureScript
{
public:
    npc_entrapping_roots() : CreatureScript("npc_entrapping_roots") { }

    struct npc_entrapping_rootsAI : public ScriptedAI
    {
        npc_entrapping_rootsAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        uint32 searchragnaros;

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->DespawnOrUnsummon(60000);
            searchragnaros = 1000;
            DoStartNoMovement(me);
            DoCast(me, SPELL_VISUAL_ROOTS);
            me->SetInCombatWithZone();
            me->SetReactState(REACT_PASSIVE);
        }

        void UpdateAI(uint32 uiDiff)
        {
            if (searchragnaros <= uiDiff)
            {
                if (Creature* Ragnaros = me->FindNearestCreature(NPC_RAGNAROS_CATA, 10.0f, true)) //remember NPC_RAGNAROS_FIRELANDS = 52409
                {
                    DoCast(Ragnaros, SPELL_ENTRAPPING);
                    me->DespawnOrUnsummon(100);
                }
            }
            else
                searchragnaros -= uiDiff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_entrapping_rootsAI(creature);
    }
};

// 54147
class npc_cloudburst : public CreatureScript
{
public:
    npc_cloudburst() : CreatureScript("npc_cloudburst") { }

    struct npc_cloudburstAI : public ScriptedAI
    {
        npc_cloudburstAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        uint8 _cloudburstCounter;

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            me->SetReactState(REACT_PASSIVE);
            me->DespawnOrUnsummon(60000);
            _cloudburstCounter = 0;
        }

        void UpdateAI(uint32 /*diff*/)
        {
            _cloudburstCounter = RAID_MODE<uint8>(1, 1, 1, 3);

            if (Player* player = me->FindNearestPlayer(6.0f, true))
                if (player->IsWithinDistInMap(me, 6.0f))
                {
                    --_cloudburstCounter;
                    if (!player->HasAura(SPELL_DELUGE) && _cloudburstCounter == 0)
                    {
                        DoCast(player, SPELL_DELUGE);
                        me->DespawnOrUnsummon(100);
                    }
                }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_cloudburstAI(creature);
    }
};

// 53953
class npc_breathoffrost : public CreatureScript
{
public:
    npc_breathoffrost() : CreatureScript("npc_breathoffrost") { }

    struct npc_breathoffrostAI : public ScriptedAI
    {
        npc_breathoffrostAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            me->SetReactState(REACT_PASSIVE);
            me->DespawnOrUnsummon(20000);
        }

        void UpdateAI(uint32 /*diff*/)
        {
            if (Player* player = me->FindNearestPlayer(6.0f, true))
                if (player->IsWithinDistInMap(me, 6.0f))
                {
                    if (!player->HasAura(SPELL_PROTECT_SUPERHEAT))
                    {
                        player->RemoveAura(SPELL_SUPERHEATED);
                        player->CastSpell(player, SPELL_MOLTEN_HEART, true);
                    }
                    //else player->ApplySpellImmune(0, IMMUNITY_ID, SPELL_SUPERHEATED, true);
                }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_breathoffrostAI(creature);
    }
};

// 54110
class npc_malfurion : public CreatureScript
{
public:
    npc_malfurion() : CreatureScript("npc_malfurion") { }

    struct npc_malfurionAI : public ScriptedAI
    {
        npc_malfurionAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        uint32 m_uiCloudTimer;

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            DoStartNoMovement(me);
            me->SetInCombatWithZone();
            me->SetReactState(REACT_PASSIVE);
        }

        void EnterCombat(Unit* /*who*/)
        {
            m_uiCloudTimer = 9000;
        }

        void UpdateAI(uint32 uiDiff)
        {
            if (m_uiCloudTimer <= uiDiff)
            {
                if (Unit* that = me->FindNearestPlayer(60.0f))
                    me->SummonCreature(NPC_CLOUDBURST, that->GetPositionX() + urand(10, 15), that->GetPositionY() + urand(10, 15), that->GetPositionZ(), that->GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000);
                DoCast(me, SPELL_CAST_CLOUDBURST);
                m_uiCloudTimer = 22000;
            }
            else
                m_uiCloudTimer -= uiDiff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_malfurionAI(creature);
    }
};

// 53872
class npc_cenarius : public CreatureScript
{
public:
    npc_cenarius() : CreatureScript("npc_cenarius") { }

    struct npc_cenariusAI : public ScriptedAI
    {
        npc_cenariusAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        uint32 m_uiFrostyTimer;

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            DoStartNoMovement(me);
            me->SetInCombatWithZone();
            me->SetReactState(REACT_PASSIVE);
        }

        void EnterCombat(Unit* /*who*/)
        {
            m_uiFrostyTimer = 12000;
        }

        void UpdateAI(uint32 uiDiff)
        {
            if (m_uiFrostyTimer <= uiDiff)
            {
                if (Unit* that = me->FindNearestPlayer(60.0f))//why like this? Because fuck knows how blizz did it, and it's already a 1700 word script. If you correct this shit and go "Fuck this guy for not doing it properly." suck the shit out of my ass cause you are already full of it.
                    me->SummonCreature(NPC_BREATH_OF_FROST, that->GetPositionX() + urand(5, 12), that->GetPositionY() + urand(5, 12), that->GetPositionZ(), that->GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000);
                DoCast(me, SPELL_VISUAL_BREATH);
                m_uiFrostyTimer = 30000;
            }
            else
                m_uiFrostyTimer -= uiDiff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_cenariusAI(creature);
    }
};

// 54293
class npc_heartofragnaros : public CreatureScript
{
public:
    npc_heartofragnaros() : CreatureScript("npc_heartofragnaros") { }

    struct npc_heartofragnarosAI : public ScriptedAI
    {
        npc_heartofragnarosAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        uint32 m_uiHeartBeat;

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->DespawnOrUnsummon(150000);
            DoStartNoMovement(me);
            me->SetReactState(REACT_PASSIVE);
            m_uiHeartBeat = 1000;//timer is here if you need it so just copy paste. To remove if script works without it.
        }

        void EnterCombat(Unit* /*who*/) { }

        void UpdateAI(uint32 /*diff*/)
        {
            Player* player = me->FindNearestPlayer(6.0f, true);
            if (player)
            {
                if (player->HasAura(SPELL_RAGE_OF_RAGNAROS) && !IsHeroic())
                {
                    player->RemoveAura(SPELL_RAGE_OF_RAGNAROS);
                    player->CastSpell(player, SPELL_MOLTEN_HEART, true);
                    me->DespawnOrUnsummon(100);
                }
                else if (IsHeroic()) //&& player->HasItemCount(ITEM_SMOULDERING_ESSENCE, 250))
                {
                    me->CastSpell(player, SPELL_MOLTEN_HEART, true);
                    me->DespawnOrUnsummon(100);
                }
                return;//this might be very incorect and this whole thing may need a timer.
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_heartofragnarosAI(creature);
    }
};

// 54109
class npc_hamuul : public CreatureScript
{
public:
    npc_hamuul() : CreatureScript("npc_hamuul") { }

    struct npc_hamuulAI : public ScriptedAI
    {
        npc_hamuulAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        uint32 m_uiRootTimer;

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            DoStartNoMovement(me);
            me->SetInCombatWithZone();
            me->SetReactState(REACT_PASSIVE);
        }

        void EnterCombat(Unit* /*who*/)
        {
            m_uiRootTimer = 9000;
        }


        void UpdateAI(uint32 uiDiff)
        {
            if (m_uiRootTimer <= uiDiff)
            {
                if (Unit* that = me->FindNearestPlayer(60.0f))
                    me->SummonCreature(NPC_ENTRAPPING_ROOTS, that->GetPositionX() + urand(10, 15), that->GetPositionY() + urand(10, 15), that->GetPositionZ(), that->GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 1000);
                DoCast(me, SPELL_NATURE);
                m_uiRootTimer = 22000;
            }
            else
                m_uiRootTimer -= uiDiff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hamuulAI(creature);
    }
};

void AddSC_boss_ragnaros_firelands()
{
    new boss_ragnaros_firelands();
    new npc_sulfuras_smash_trigger();
    new npc_sulfuras_smash();
    new npc_magma_trap();
    new npc_splitting_blow();
    new npc_sulfuras();
    new npc_engulfing_flames();
    new npc_molten_seed();
    new npc_living_meteor();
    new npc_son_of_flame();
    new npc_lava_scion();
    new npc_molten_elemental();
    new npc_entrapping_roots();
    new npc_dreadflame();
    new npc_cloudburst();
    new npc_breathoffrost();
    new npc_hamuul();
    new npc_malfurion();
    new npc_cenarius();
    new npc_heartofragnaros();
}

/* SQL:
NEEDED STUFF (Kept for future reference) :

Deathwing has prepared me to face the vessel of Tarecgosa, your fools journey ends here! - Required for when player has 250 smoldering essence
The realm of fire will consume you! - He also says this when casting Heroic World of flames 32 31 29 26 25 24 33 22 21 20 15 16 18 19 17 - sounds missing: 24523, 24527, 24528, 24530 and 24534
*/