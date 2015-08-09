/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * Script done: 95%. ToDo: 
 * - Script remaining spells. See each boss notes on ToDo.
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

#define EMOTE_ARION_THUNDERSHOCK       "The air around you crackles with energy..."
#define EMOTE_TERRASTRA_QUAKE          "The ground beneath you rumbles ominously..."

/*
Merge order Elementium Monstrosity + talks:
Arion_P3                "An impressive display..."
TERRASTRA_P3            "...to have made it this far."
Feludius_P3             "But now witness true power..."
IGNACIOUS_P3            "The fury of the elements! "
*/

enum FeludiusYells
{
  SAY_F_AGGRO = 1,
  SAY_F_KILL,
  SAY_F_GLACIATE,
  SAY_F_MONSTROSITY
};

enum IgnaciousYells
{
  SAY_I_AGGRO = 1,
  SAY_I_KILL,
  SAY_I_RISING_FLAMES,
  SAY_I_MONSTROSITY
};

enum TerrastraYells
{
  SAY_T_AGGRO = 1,
  SAY_T_KILL,
  SAY_T_GRAVITY_WELL,
  SAY_T_MONSTROSITY
};

enum ArionYells
{
  SAY_A_AGGRO = 1,
  SAY_A_KILL,
  SAY_A_CALL_WINDS,
  SAY_A_MONSTROSITY
};

enum MonstrosityYells
{
  SAY_M_AGGRO = 1,
  SAY_M_KILL,
  SAY_M_LAVA_SEEDS,
  SAY_M_GRAVITY_CRUSH,
  SAY_M_DIE
};

enum Spells // Non-commented spells work completely. 88919 to 88922 visuals before encounter.
{
    /***** GENERAL *****/
    SPELL_SELF_ROOT                          = 42716,
    SPELL_PACIFY_SELF                        = 63726,

    SPELL_TELEPORT_VISUAL                    = 87459,
    SPELL_SUMMON_MONSTROSITY_EXPLODE         = 84207,
    SPELL_ELEMENTAL_STASIS                   = 82285, // With AddAura.

    /***** FELUDIUS *****/ 
    // ATTACK PHASE.
    SPELL_HYDRO_LANCE                        = 82752,

    SPELL_WATER_BOMB                         = 82699, // See next spell, is the dummy effect spell on EFFECT_0. Script: Summon npc under target.
    SPELL_WATER_BOMB_DMG                     = 82700, // Npc casts this on self. Causes Waterlogged on targets.
    SPELL_WATERLOGGED                        = 82762, // Only cast on spot, no radius.

    SPELL_FROZEN                             = 82772, // Feludius's Glaciate causes all Waterlogged enemies to become Frozen
    SPELL_GLACIATE                           = 82746, // Script to decrease damage with distance. 
    // Above spell has the extra script effect: Players afflicted by Waterlogged when Feludius uses Glaciate become Frozen and suffer additional damage. 

    SPELL_HEART_OF_ICE                       = 82665, // Triggers 82667 damage spell. 
    //Script: Deals increasing Frost damage every 2 sec, but also causes nearby players within 10 yards to become Frost Imbued.
    SPELL_FROST_IMBUED                       = 82666, // Has dummy aura, needs script to increase damage done to Ignacious.

    // CAST PHASE
    SPELL_FROZEN_ORB_SUMMON                 = 92269, // Summons orb after 5 sec.
    SPELL_FROZEN_ORB_VISUAL_AURA            = 92302, // Mob on self.
    SPELL_INCREASE_RUN_SPEED                = 99250, // Increase by 2%. Needed every sec. Mob on self.
    SPELL_FROST_BEACON                      = 92307, // Aura cast by npc on Frozen Orb target. HEROIC!

    /***** IGNACIOUS *****/
    // ATTACK PHASE.
    SPELL_FLAME_TORRENT                      = 82777,

    SPELL_BURNING_BLOOD                      = 82660, // Script: Deals increasing Fire damage every 2 sec, but also causes nearby players within 10 yards to become Flame Imbued. 
    SPELL_FLAME_IMBUED                       = 82663, // Has dummy aura, needs script to increase damage done to Feludius.

    SPELL_INFERNO_RUSH_CHARGE                = 82856, // Jump and missile with damage and knockback.
    SPELL_INFERNO_RUSH_AURA                  = 88579, // Aura for the npc. Triggers 82860 - damage spell every 0.5 sec. Npc is defined, summoned on jump and then follows Ignacious.
    //Ignacious leaps to a distant target, knocking away all enemies within 10 yards of the point of impact and inflicting 23125 to 26875 Fire damage. 
    //Ignacious then rushes back to his last target, leaving a trail of fire in his wake. Standing within this fire inflicts 13875 to 16125 Fire damage every 0.5 sec. 

    SPELL_AEGIS_OF_FLAME                     = 82631,
    SPELL_RISING_FLAMES                      = 82636, // Aura with trigger every 2 sec. for damage spell 82643. Works.
    SPELL_RISING_FLAMES_INC_DMG              = 82639, // Each time Rising Flames pulses, Ignacious increases his damage dealt by 3/5% for 15 sec.

    // CAST PHASE
    SPELL_FLAME_STRIKE_DAMAGE                = 92215, // HEROIC!
    SPELL_FLAME_STRIKE_PERIODIC              = 92214, // Triggered by above.
    SPELL_FLAME_STRIKE_TARGET                = 92212, // Visual dummy for hit area.

    /***** ARION *****/
    // ATTACK PHASE - ToDo: DONE.
    SPELL_CALL_WINDS                         = 83491, // Summons 44747 Violent Cyclone.
    SPELL_LASHING_WINDS_VISUAL               = 83472, // Visual dummy for npc.
    SPELL_SWIRLING_WINDS                     = 83500, // Inflicted by Violent Cyclone to players it touches. Makes them levitate 2 mins.
    // The Grounded effect cancels the Swirling Winds effect. 

    SPELL_LIGHTNING_ROD                      = 83099, // Dummy for marking Chain Lightning target. 25-player raid -> 3 players affected.
    SPELL_CHAIN_LIGHTNING                    = 83282,
    SPELL_THUNDERSHOCK                       = 83067, // Players with the Grounded effect take greatly reduced damage.

    SPELL_DISPERSE                           = 83087, // Has Script Effect for 83078.
    SPELL_DISPERSE_TELEPORT                  = 83078, // Actual teleport within 5 yards of target. Cast on random raid member in room through above.
    SPELL_LIGHTNING_BLAST                    = 83070, // Cast on Arion's tank immediately after Disperse.

    // CAST PHASE
    SPELL_STATIC_OVERLOAD                    = 92067, // On a target, HEROIC!
    SPELL_STATIC_OVERLOAD_DMG_AURA           = 92068, // Triggered by above on allies within 10 y. Adds this 10s aura to them.

    /***** TERRASTRA *****/
    // ATTACK PHASE - ToDo: Script Harden Skin.
    SPELL_GRAVITY_WELL_DECR_MOVEMENT         = 83587, // Works completely.
    AURA_GRAVITY_WELL_PULL                   = 79333,
    AURA_GRAVITY_WELL_DMG_GROUNDED           = 83579,
    SPELL_GRAVITY_WELL_PULL                  = 79332, // Trigg by aura, 10y.
    SPELL_GRAVITY_WELL_DMG_GROUNDED          = 83578, // Trigg by aura, works properly.
    SPELL_GRAVITY_WELL_VISUAL                = 79245, // Mob on self. - 10y vis.
    SPELL_GRAV_WELL_MOB_VISUAL               = 95760, // Mob on self. - self vis.
    SPELL_GROUNDED                           = 83581, // The Swirling Winds effect cancels the Grounded effect.

    SPELL_ERUPTION                           = 83692, // Damage spell, works completely.
    SPELL_ERUPTION_SUMMON_MOB                = 83661, // Summon mob who casts this on self.
    SPELL_ERUPTION_VISUAL                    = 83662, // Visual mob aura.

    SPELL_HARDEN_SKIN                        = 83718, // Eff 3 needs script for dummy to return on remove 50% damage received.
    SPELL_QUAKE                              = 83565, // Players with the Swirling Winds effect take no damage. 

    // CAST PHASE
    SPELL_GRAVITY_CORE                       = 92075, // On a target, HEROIC!
    SPELL_GRAVITY_CORE_SLOW                  = 92076, // Triggered by above on allies within 10 y. Adds this 10s aura to them.

    /***** ELEMENTIUM MONSTROSITY *****/
    // ToDo: Script Gravity Crush Npc to pass spell handling to proper vehicle.
    SPELL_LAVA_SEED                          = 84913, // Dummy cast by boss. Needs script.
    AURA_LAVA_SEED_VISUAL                    = 84911, // Npc on self.
    SPELL_LAVA_EXPLODE                       = 84912, // Works properly.
    SPELL_LAVA_ERRUPT_EMOTE                  = 79461, // Visual explode.

    SPELL_GRAVITY_CRUSH                      = 84948, // This is damage spell. In 10 player 1 target, 25 player three targets trapped.
    SPELL_GRAVITY_CRUSH_CONTROL_VEHICLE      = 84952, // This is control vehicle spell. Need monstrosity vehicleid and SCRIPT. This is what boss casts!

    SPELL_ELECTRIC_INSTABILITY_TARGET        = 84529, // On a single player, handled through dummy script for spell.
    SPELL_ELECTRIC_INSTABILITY_AURA          = 84526, // Triggers dummy spell every sec.
    SPELL_ELECTRIC_INSTABILITY_DUMMY         = 84527, // Dummy spell, casts target spell on each player.

    SPELL_CRYOGENIC_AURA                     = 84918,
    SPELL_LIQUID_ICE_GROW                    = 84917, // Increase size 40%. Periodically cast by npc.
    SPELL_LIQUID_ICE_PERIODIC                = 84914, // Npc on self.
    SPELL_LIQUID_ICE_DAMAGE                  = 84915  // Damage spell triggered by above. Needs 6y radius.
};

enum Creatures
{
    // Controller
    NPC_ASCENDANT_CONTROLLER = 43691,
    // Bosses
    NPC_WATER_BOMB    = 44201, // Scripted.
    NPC_INFERNO_RUSH  = 47501, // Scripted on Ignacious boss script.
    NPC_CALL_WINDS    = 44747, // Scripted.
    NPC_GRAVITY_WELL  = 44824, // Scripted.
    NPC_ERUPTION_TGT  = 44845, // Scripted on Terrastra boss script.
    // Heroic
    NPC_FROZEN_ORB    = 49518, // Gets a target, goes to it casting beacon on it, casts Glaciate if reaches. // Scripted.
    NPC_FLAME_STRIKE  = 49432, // Summ by boss on random target. Puts visual on self then after 5 secs comes damage spell. // Scripted.
    // Monstrosity
    NPC_LIQUID_ICE    = 45452, // Scripted.
    NPC_LAVA_SEED     = 48538, // Scripted.
    NPC_GRAVITY_CRUSH = 45476  // vehicle.
};

enum Models
{
    MODEL_FELUDIUS                           = 34822,
    MODEL_IGNACIOUS                          = 34821,
    MODEL_ARION                              = 34823,
    MODEL_TERRASTRA                          = 34824,
    MODEL_INVISIBLE                          = 11686,
};

enum Events
{
    /***** Controller *****/
    EVENT_MOVE_AND_INVISIBLE = 1, // Switch to p3 and wait for last phase.
    EVENT_TIME_TO_SPAWN_MONSTROSITY,

    EVENT_COUNCIL_DISPLAY_VISUAL,
    EVENT_FELUDIUS_MOVE_CENTER,
    EVENT_IGNACIOUS_MOVE_CENTER,
    EVENT_ARION_MOVE_CENTER,
    EVENT_TERRASTRA_MOVE_CENTER,
    EVENT_SUMMON_MONSTROSITY,

    EVENT_CAST_STASIS,
    EVENT_REMOVE_STASIS,

    /***** Bosses *****/
    // Feludius
    EVENT_HYDRO_LANCE,
    EVENT_WATER_BOMB,
    EVENT_GLACIATE,
    EVENT_HEART_OF_ICE,

    EVENT_FROST_ORB, // Heroic.

    // Ignacious
    EVENT_SAY_I_AGGRO,
    EVENT_FLAME_TORRENT,
    EVENT_BURNING_BLOOD,
    EVENT_INFERNO_RUSH,
    EVENT_SUMMON_INFERNO_RUSH_NPC,
    EVENT_AEGIS_OF_FLAME,
    EVENT_RISING_FLAMES,

    EVENT_FLAME_STRIKE, // Heroic.

    // Arion
    EVENT_SAY_A_AGGRO,
    EVENT_CALL_WINDS,
    EVENT_LIGHTNING_ROD,
    EVENT_CHAIN_LIGHTNING,
    EVENT_THUNDERSHOCK,
    EVENT_DISPERSE,
    EVENT_LIGHTNING_BLAST,

    EVENT_STATIC_OVERLOAD, // Heroic.

    // Terrastra
    EVENT_GRAVITY_WELL,
    EVENT_ERUPTION,
    EVENT_HARDEN_SKIN,
    EVENT_QUAKE,

    EVENT_GRAVITY_CORE, // Heroic.

    // Elementium Monstrosity - Cryogenic Aura and Electric Instability aura are added as passives on boss summon.
    EVENT_SUMMON_LIQUID_ICE,
    EVENT_ELECTRIC_INSTABILITY,
    EVENT_LAVA_SEED,
    EVENT_LAVA_SEED_SUMMON,
    EVENT_GRAVITY_CRUSH,

    /***** Npc's *****/
    EVENT_WATER_BOMB_EXPLODE,
    EVENT_CHECK_WINDS_PLAYER,
    EVENT_SEED_EXPLODE,
    EVENT_LIQUID_ICE_GROW,
    EVENT_FLAME_STRIKE_DAMAGE,
    EVENT_ATTACK_FROZEN_TARGET,
    EVENT_CHECK_FROZEN_TARGET,
    EVENT_FROZEN_DESPAWN
};

enum Actions // Controller Actions.
{
    ACTION_COUNCIL_MOVE_AND_INVISIBLE,
    ACTION_COUNCIL_SPAWN_MONSTROSITY
};

enum Phases // Boss Phases.
{
    PHASE_NULL    = 0,
    PHASE_COMBAT,
    PHASE_BALCONY
};

#define healthController RAID_MODE<uint32>(23190840, 73008200, 42430648, 125058752) // Controller health on different diffs.

// 43691
class npc_ascendant_council_controller : public CreatureScript // 43691
{
public:
    npc_ascendant_council_controller() : CreatureScript("npc_ascendant_council_controller") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ascendant_council_controllerAI (creature);
    }

    struct npc_ascendant_council_controllerAI : public ScriptedAI
    {
        npc_ascendant_council_controllerAI(Creature* creature) : ScriptedAI(creature), summons(me)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        SummonList summons;
        EventMap events;
        bool started;

        void Reset()
        {
            started = false;
            me->SetMaxHealth(healthController);
            me->SetHealth(healthController);

            Creature* feludius = me->FindNearestCreature(NPC_FELUDIUS, 500.0f, true); 
            Creature* ignacious = me->FindNearestCreature(NPC_IGNACIOUS, 500.0f, true); 
            Creature* arion = me->FindNearestCreature(NPC_ARION, 500.0f, true); 
            Creature* terrastra = me->FindNearestCreature(NPC_TERRASTRA, 500.0f, true);  

            if (feludius && ignacious && arion && terrastra) // Check to prevent any damn crashes.
            {
                // Set correct boss health on any diff.
                feludius->SetMaxHealth(healthController / 4);
                feludius->SetHealth(healthController / 4);
                ignacious->SetMaxHealth(healthController / 4);
                ignacious->SetHealth(healthController / 4);
                arion->SetMaxHealth(healthController / 4);
                arion->SetHealth(healthController / 4);
                terrastra->SetMaxHealth(healthController / 4);
                terrastra->SetHealth(healthController / 4);
            }

            summons.DespawnAll(); // Despawn Monstrosity if exists.

            if (instance)
                instance->SetData(DATA_ASCENDANT_COUNCIL, NOT_STARTED);
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
            summon->setActive(true);
 
            switch(summon->GetEntry())
            {
                case NPC_ELEMENTIUM_MONSTROSITY:
                    summon->AddAura(SPELL_CRYOGENIC_AURA, summon);
                    summon->AddAura(SPELL_ELECTRIC_INSTABILITY_AURA, summon);
                    summon->SetMaxHealth(me->GetMaxHealth());
                    summon->SetHealth(me->GetHealth());

                    if (me->IsInCombat())
                        summon->AI()->DoZoneInCombat(summon, 150.0f);
                    break;

                default:
                    if (me->IsInCombat())
                        summon->AI()->DoZoneInCombat(summon, 150.0f);
                    break;
            }
        }

        void JustDied(Unit * /*victim*/)
        {
            if (instance)
                instance->SetData(DATA_ASCENDANT_COUNCIL, DONE);
        }

        void EnterEvadeMode()
        {
            Reset();
        
            if (instance)
                instance->SetData(DATA_ASCENDANT_COUNCIL, FAIL);
        }

        void EnterCombat(Unit* /*who*/)
        {
            //DoCast(me, SPELL_PACIFY_SELF);
            started = false;

            if (instance)
                instance->SetData(DATA_ASCENDANT_COUNCIL,IN_PROGRESS);
        }

        void DoAction(int32 action)
        {
            switch(action)
            {
                case ACTION_COUNCIL_MOVE_AND_INVISIBLE:
                    events.ScheduleEvent(EVENT_MOVE_AND_INVISIBLE, 100);
                    events.ScheduleEvent(EVENT_TIME_TO_SPAWN_MONSTROSITY, 1000);
                    started = true;
                    break;

                case ACTION_COUNCIL_SPAWN_MONSTROSITY:
                    events.ScheduleEvent(EVENT_COUNCIL_DISPLAY_VISUAL, 100);
                    events.ScheduleEvent(EVENT_ARION_MOVE_CENTER, 500);
                    events.ScheduleEvent(EVENT_TERRASTRA_MOVE_CENTER, 4500);
                    events.ScheduleEvent(EVENT_FELUDIUS_MOVE_CENTER, 8500);
                    events.ScheduleEvent(EVENT_IGNACIOUS_MOVE_CENTER, 12500);
                    events.ScheduleEvent(EVENT_SUMMON_MONSTROSITY, 16500);

                    events.ScheduleEvent(EVENT_CAST_STASIS, 10); // Has 17 seconds duration.
                    break;

                default:
                    break;
            }
        }

        void CastElementalStasis()
        {
            Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();

            if (!PlayerList.isEmpty())
              for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                if (Player* playr = i->GetSource())
                    playr->AddAura(SPELL_ELEMENTAL_STASIS, playr); // Trap all players while Monstrosity spawns.
        }

        void UpdateAI(uint32 diff)
        {
            if (!instance)
                return;

            // At this point, before Monstrosity spawns, they have invisible models.
            Creature* feludius = me->FindNearestCreature(NPC_FELUDIUS, 500.0f, true); 
            Creature* ignacious = me->FindNearestCreature(NPC_IGNACIOUS, 500.0f, true); 
            Creature* arion = me->FindNearestCreature(NPC_ARION, 500.0f, true); 
            Creature* terrastra = me->FindNearestCreature(NPC_TERRASTRA, 500.0f, true);  

            events.Update(diff);

            if (feludius && ignacious && arion && terrastra) // Check to prevent any damn crashes.
            {
                if ((feludius->HealthBelowPct(26) || ignacious->HealthBelowPct(26)) && (arion->HealthBelowPct(26) || terrastra->HealthBelowPct(26)) && !started) // Check for final phase.
                    DoAction(ACTION_COUNCIL_MOVE_AND_INVISIBLE);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_MOVE_AND_INVISIBLE:
                            feludius->RemoveAllAuras();
                            ignacious->RemoveAllAuras();
                            arion->RemoveAllAuras();
                            terrastra->RemoveAllAuras();
                            feludius->SetDisplayId(MODEL_INVISIBLE);
                            feludius->NearTeleportTo(-982.346f, -567.829f, 831.902f, 3.703f);
                            feludius->GetMotionMaster()->Clear();
                            ignacious->SetDisplayId(MODEL_INVISIBLE);
                            ignacious->NearTeleportTo(-1009.081f, -552.791f, 831.902f, 4.742f);
                            ignacious->GetMotionMaster()->Clear();
                            arion->SetDisplayId(MODEL_INVISIBLE);
                            arion->NearTeleportTo(-1008.595f, -612.496f, 831.902f, 1.594f);
                            arion->GetMotionMaster()->Clear();
                            terrastra->SetDisplayId(MODEL_INVISIBLE);
                            terrastra->NearTeleportTo(-982.904f, -597.649f, 831.902f, 2.643f);
                            terrastra->GetMotionMaster()->Clear();
                            feludius->SetReactState(REACT_PASSIVE);
                            ignacious->SetReactState(REACT_PASSIVE);
                            arion->SetReactState(REACT_PASSIVE);
                            terrastra->SetReactState(REACT_PASSIVE);
                            feludius->IsAIEnabled = false;
                            ignacious->IsAIEnabled = false;
                            arion->IsAIEnabled = false;
                            terrastra->IsAIEnabled = false;
                            break;

                        case EVENT_TIME_TO_SPAWN_MONSTROSITY:
                            DoAction(ACTION_COUNCIL_SPAWN_MONSTROSITY);
                            break;

                        case EVENT_COUNCIL_DISPLAY_VISUAL:
                            feludius->SetDisplayId(MODEL_FELUDIUS);
                            feludius->CastSpell(feludius, SPELL_TELEPORT_VISUAL, true);
                            ignacious->SetDisplayId(MODEL_IGNACIOUS);
                            ignacious->CastSpell(ignacious, SPELL_TELEPORT_VISUAL, true);
                            arion->SetDisplayId(MODEL_ARION);
                            arion->CastSpell(arion, SPELL_TELEPORT_VISUAL, true);
                            terrastra->SetDisplayId(MODEL_TERRASTRA);
                            terrastra->CastSpell(terrastra, SPELL_TELEPORT_VISUAL, true);
                            break;

                        case EVENT_FELUDIUS_MOVE_CENTER:
                            feludius->AI()->Talk(SAY_F_MONSTROSITY);
                            feludius->GetMotionMaster()->MovePoint(1, -1003.328f, -580.054f, 831.902f);
                            break;

                        case EVENT_TERRASTRA_MOVE_CENTER:
                            terrastra->AI()->Talk(SAY_T_MONSTROSITY);
                            terrastra->GetMotionMaster()->MovePoint(1, -1003.397f, -586.494f, 831.902f);
                            break;

                        case EVENT_ARION_MOVE_CENTER:
                            arion->AI()->Talk(SAY_A_MONSTROSITY);
                            arion->GetMotionMaster()->MovePoint(1, -1009.291f, -588.784f, 831.902f);
                            break;
 
                        case EVENT_IGNACIOUS_MOVE_CENTER:
                            ignacious->AI()->Talk(SAY_I_MONSTROSITY);
                            ignacious->GetMotionMaster()->MovePoint(1, -1008.654f, -576.558f, 831.902f);
                            break;
                
                        case EVENT_SUMMON_MONSTROSITY:
                            if (instance)
                            {
                                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, feludius); // Remove
                                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, ignacious); // Remove
                                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, arion); // Remove
                                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, terrastra); // Remove
                            }

                            feludius->SetDisplayId(MODEL_INVISIBLE);
                            terrastra->SetDisplayId(MODEL_INVISIBLE);
                            arion->SetDisplayId(MODEL_INVISIBLE);
                            ignacious->CastSpell(ignacious, SPELL_SUMMON_MONSTROSITY_EXPLODE, true); // Visual Explode to create the Monstrosity.
                            ignacious->SetDisplayId(MODEL_INVISIBLE);
                            me->SummonCreature(NPC_ELEMENTIUM_MONSTROSITY, -1008.824f, -582.617f, 831.902f, 0.026f, TEMPSUMMON_MANUAL_DESPAWN);
                            break;

                        case EVENT_CAST_STASIS:
                            CastElementalStasis();
                            break;

                        default:
                            break;
                    }
                }
            }
        }
    };
};

/*** ! On NORMAL, bosses only have one phase, they watch the other pair from the balcony, without intervening in the fight ! ***/
/*** ! Each boss has two situations on HEROIC: sit on balcony and cast spells while other pair attacks players and attack players while other pair casts spells from balcony. ! ***/

/*
Move positions for bosses at start phase monstrosity:
Feludius:
-982.346f, -567.829f, 831.902f, 3.703f start. - Boss at hp < 26%.
-1003.328f, -580.054f, 831.902f, 3.703f end. - Controller event. - DONE.
Terrastra:
-982.904f, -597.649f, 831.902f, 2.643f start. - Boss at hp < 26%.
-1003.397f, -586.494f, 831.902f, 2.643f end. - Controller event. - DONE.
Arion:
-1008.595f, -612.496f, 831.902f, 1.594f start. - Boss at hp < 26%.
-1009.291f, -588.784f, 831.902f, 1.594f end. - Controller event. - DONE.
Ignacious:
-1009.081f, -552.791f, 831.902f, 4.742f start. - Boss at hp < 26%.
-1008.654f, -576.558f, 831.902f, 4.742f end. - Controller event. - DONE.

Monstrosity Summon Pos:
-1008.824f, -582.617f, 831.902f, 0.026f. - Controller event. - DONE.
*/

// 43687
class boss_feludius : public CreatureScript
{
    public:
        boss_feludius() : CreatureScript("boss_feludius") { }

        struct boss_feludiusAI : public BossAI
        {
            boss_feludiusAI(Creature* creature) : BossAI(creature, DATA_ASCENDANT_COUNCIL), summons(me)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            Phases phase;
            SummonList summons;
            bool wentUp;

            void InitializeAI()
            {
                if (!instance)
                    me->IsAIEnabled = false;
                else if (!me->IsDead())
                    Reset();
            }

            void Reset()
            {
                me->RemoveAllAuras();
                phase = PHASE_NULL;
                summons.DespawnAll();
                wentUp = false;
                _Reset();
            }

            void EnterEvadeMode()
            {
                Reset();            
                me->GetMotionMaster()->MoveTargetedHome();   
                me->SetReactState(REACT_AGGRESSIVE);

                if (instance)
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove

                _EnterEvadeMode();
            }

            void EnterCombat(Unit* /*who*/)
            {
                // Being first, Feludius/Ignacious set all bosses in combat. This is how it's done on off, by pull, not through controller.
                Creature* controller = me->FindNearestCreature(NPC_ASCENDANT_CONTROLLER, 500.0f, true); // Check controller too. 
                Creature* ignacious = me->FindNearestCreature(NPC_IGNACIOUS, 500.0f, true); 
                Creature* arion = me->FindNearestCreature(NPC_ARION, 500.0f, true); 
                Creature* terrastra = me->FindNearestCreature(NPC_TERRASTRA, 500.0f, true);  

                wentUp = false;

                if (controller && ignacious && arion && terrastra) // Check to prevent any damn crashes.
                {
                    if (!controller->IsInCombat())
                        controller->AI()->AttackStart(me->GetVictim());
                    if (!ignacious->IsInCombat())
                        ignacious->AI()->AttackStart(me->GetVictim());
                    if (!arion->IsInCombat())
                        arion->AI()->AttackStart(me->GetVictim());
                    if (!terrastra->IsInCombat())
                        terrastra->AI()->AttackStart(me->GetVictim());
                }

                Talk(SAY_F_AGGRO);
                EnterPhaseCombat();

                if (instance)
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add

                _EnterCombat();
            }

            void EnterPhaseCombat()
            {
                me->RemoveAllAuras();
                phase = PHASE_COMBAT;
                me->SetReactState(REACT_AGGRESSIVE);
                events.SetPhase(PHASE_COMBAT);
                initEvents(true);
            }

            void EnterPhaseBalcony()
            {
                DoCast(me, SPELL_TELEPORT_VISUAL);
                me->NearTeleportTo(-1057.930f, -533.382f, 877.684f, 5.478f);
                DoCast(me, SPELL_SELF_ROOT);
                phase = PHASE_BALCONY;
                events.SetPhase(PHASE_BALCONY);
                initEvents(false);
            }

            void initEvents(bool combatPhase = true)
            {
                events.Reset();
            
                if(combatPhase)
                {
                    events.ScheduleEvent(EVENT_HYDRO_LANCE, urand(6000, 10000), PHASE_COMBAT);
                    events.ScheduleEvent(EVENT_WATER_BOMB, urand(14000, 16000), PHASE_COMBAT);
                    events.ScheduleEvent(EVENT_GLACIATE, urand(29000, 31000), PHASE_COMBAT);
                    events.ScheduleEvent(EVENT_HEART_OF_ICE, urand(58000, 62000), PHASE_COMBAT); // Then 22 sec.
                }else
                {
                    if (me->GetMap()->IsHeroic())
                         events.ScheduleEvent(EVENT_FROST_ORB, 20000, PHASE_BALCONY);
                }
            }

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);
                summon->setActive(true);

                if (me->IsInCombat())
                    summon->AI()->DoZoneInCombat();
            }

            void KilledUnit(Unit* /*victim*/)
            {
                Talk(SAY_F_KILL);
            }

            void DamageTaken(Unit* attacker, uint32& damage)
            {
                if (damage > ((me->GetHealth() / 4) * 3)) // Check needed for correct split.
                    damage = (me->GetHealth() / 4) * 3;

                if (attacker->HasAura(SPELL_FLAME_IMBUED))
                    damage += damage / 5; // Extra 20% damage on Flame Imbued.

                if (Creature* controller = me->FindNearestCreature(NPC_ASCENDANT_CONTROLLER, 500.0f, true))
                    controller->SetHealth(controller->GetHealth() - damage);
            }

            void JustDied(Unit* /*killer*/)
            {    
                _JustDied();
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING) || !phase)
                    return;

                Creature* ignacious = me->FindNearestCreature(NPC_IGNACIOUS, 500.0f, true);

                    if (ignacious)
                        if ((me->HealthBelowPct(26) || ignacious->HealthBelowPct(26)) && !wentUp)
                        {
                            EnterPhaseBalcony();
                            wentUp = true;
                        }

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_HYDRO_LANCE:
                            if(Unit* victim = SelectTarget(SELECT_TARGET_RANDOM, 0, 500.0f, true))
                                DoCast(victim, SPELL_HYDRO_LANCE);
                            events.ScheduleEvent(EVENT_HYDRO_LANCE, urand(12000, 14000), PHASE_COMBAT);
                            break;

                        case EVENT_WATER_BOMB:
                            DoCast(me, SPELL_WATER_BOMB);
                            events.ScheduleEvent(EVENT_WATER_BOMB, urand(30000, 34000), PHASE_COMBAT);
                            break;

                        case EVENT_GLACIATE:
                            Talk(SAY_F_GLACIATE);
                            DoCast(me, SPELL_GLACIATE);
                            events.ScheduleEvent(EVENT_GLACIATE, urand(36000, 40000), PHASE_COMBAT);
                            break;

                        case EVENT_HEART_OF_ICE:
                            if(Unit* victim = SelectTarget(SELECT_TARGET_RANDOM, 0, 500.0f, true))
                                DoCast(victim, SPELL_HEART_OF_ICE);
                            events.ScheduleEvent(EVENT_HEART_OF_ICE, urand(21000, 23000), PHASE_COMBAT);
                            break;

                        case EVENT_FROST_ORB:
                            if (Creature* controller = me->FindNearestCreature(NPC_ASCENDANT_CONTROLLER, 500.0f, true)) // Summon it down, at the controller.
                                controller->AddAura(SPELL_FROZEN_ORB_SUMMON, controller);
                            events.ScheduleEvent(EVENT_FROST_ORB, urand(19000, 21000), PHASE_BALCONY);
                            break;

                        default:
                            break;
                    }
                }

                if (phase == PHASE_COMBAT && !me->HealthBelowPct(26))
                    DoMeleeAttackIfReady();
            }

    private:
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_feludiusAI(creature);
    }
};

// 43686
class boss_ignacious : public CreatureScript
{
    public:
        boss_ignacious() : CreatureScript("boss_ignacious") { }

        struct boss_ignaciousAI : public BossAI
        {
            boss_ignaciousAI(Creature* creature) : BossAI(creature, DATA_ASCENDANT_COUNCIL), summons(me)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            Phases phase;
            SummonList summons;
            uint32 infernoSummoned;
            bool wentUp;

            void InitializeAI()
            {
                if (!instance)
                    me->IsAIEnabled = false;
                else if (!me->IsDead())
                    Reset();
            }

            void Reset()
            {
                wentUp = false;
                me->RemoveAllAuras();
                phase = PHASE_NULL;
                summons.DespawnAll();
                infernoSummoned = 0;

                _Reset();
            }

            void EnterEvadeMode()
            {
                Reset();            
                me->GetMotionMaster()->MoveTargetedHome();   
                me->SetReactState(REACT_AGGRESSIVE);

                if (instance)
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove

                _EnterEvadeMode();
            }

            void EnterCombat(Unit* /*who*/)
            {
                // Being first, Feludius/Ignacious set all bosses in combat. This is how it's done on off, by pull, not through controller.
                Creature* feludius = me->FindNearestCreature(NPC_FELUDIUS, 500.0f, true);
                Creature* arion = me->FindNearestCreature(NPC_ARION, 500.0f, true); 
                Creature* terrastra = me->FindNearestCreature(NPC_TERRASTRA, 500.0f, true);

                wentUp = false;

                if (feludius && arion && terrastra) // Check to prevent any damn crashes.
                {
                    if (!feludius->IsInCombat())
                        feludius->AI()->AttackStart(me->GetVictim());
                    if (!arion->IsInCombat())
                        arion->AI()->AttackStart(me->GetVictim());
                    if (!terrastra->IsInCombat())
                        terrastra->AI()->AttackStart(me->GetVictim());
                }

                infernoSummoned = 0;
                EnterPhaseCombat();

                if (instance)
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add

                _EnterCombat();
            }

            void EnterPhaseCombat()
            {
                me->RemoveAllAuras();
                phase = PHASE_COMBAT;
                me->SetReactState(REACT_AGGRESSIVE);
                events.SetPhase(PHASE_COMBAT);
                initEvents(true);
            }

            void EnterPhaseBalcony()
            {
                DoCast(me, SPELL_TELEPORT_VISUAL);
                me->NearTeleportTo(-1057.890f, -631.515f, 877.682f, 0.797f);
                DoCast(me, SPELL_SELF_ROOT);
                phase = PHASE_BALCONY;
                events.SetPhase(PHASE_BALCONY);
                initEvents(false);
            }

            void initEvents(bool combatPhase = true)
            {
                events.Reset();
            
                if(combatPhase)
                {
                    events.ScheduleEvent(EVENT_SAY_I_AGGRO, 4500, PHASE_COMBAT); // Delay this so does not come in conflict with Feludius aggro say.
                    
                    events.ScheduleEvent(EVENT_FLAME_TORRENT, urand(6000, 10000), PHASE_COMBAT);
                    events.ScheduleEvent(EVENT_INFERNO_RUSH, urand(14000, 16000), PHASE_COMBAT);
                    events.ScheduleEvent(EVENT_AEGIS_OF_FLAME, urand(31000, 33000), PHASE_COMBAT); // Then 60;
                    events.ScheduleEvent(EVENT_BURNING_BLOOD, urand(58000, 62000), PHASE_COMBAT); // Then 22 sec.
                }else
                {
                    if (me->GetMap()->IsHeroic())
                         events.ScheduleEvent(EVENT_FLAME_STRIKE, 20000, PHASE_BALCONY);
                }
            }

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);
                summon->setActive(true);
            
                switch(summon->GetEntry())
                {
                    case NPC_INFERNO_RUSH:
                        summon->SetInCombatWithZone();
                        summon->AddAura(SPELL_INFERNO_RUSH_AURA, summon);
                        summon->DespawnOrUnsummon(10000);
                        break;

                    default:
                        if (me->IsInCombat())
                            summon->AI()->DoZoneInCombat(summon, 150.0f);
                        break;
                }
            }

            void KilledUnit(Unit* /*victim*/)
            {
                Talk(SAY_I_KILL);
            }

            void DamageTaken(Unit* attacker, uint32& damage)
            {
                if (damage > ((me->GetHealth() / 4) * 3)) // Check needed for correct split.
                    damage = (me->GetHealth() / 4) * 3;

                if (attacker->HasAura(SPELL_FROST_IMBUED))
                    damage += damage / 5; // Extra 20% damage on Frost Imbued.

                if (Creature* controller = me->FindNearestCreature(NPC_ASCENDANT_CONTROLLER, 500.0f, true))
                    controller->SetHealth(controller->GetHealth() - damage);
            }

            void JustDied(Unit* /*killer*/)
            {
                _JustDied();
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING) || !phase)
                    return;

                Creature* feludius = me->FindNearestCreature(NPC_FELUDIUS, 500.0f, true);

                    if (feludius)
                        if ((me->HealthBelowPct(26) || feludius->HealthBelowPct(26)) && !wentUp)
                        {
                            EnterPhaseBalcony();
                            wentUp = true;
                        }

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SAY_I_AGGRO:
                            Talk(SAY_I_AGGRO);
                            break;

                        case EVENT_FLAME_TORRENT:
                            DoCast(me, SPELL_FLAME_TORRENT);
                            events.ScheduleEvent(EVENT_FLAME_TORRENT, urand(12000, 14000), PHASE_COMBAT);
                            break;

                        case EVENT_INFERNO_RUSH:
                            if (Unit* victim = SelectTarget(SELECT_TARGET_RANDOM, 0, 500.0f, true))
                            {
                                DoCast(victim, SPELL_INFERNO_RUSH_CHARGE);
                                events.ScheduleEvent(EVENT_SUMMON_INFERNO_RUSH_NPC, 100);
                            }
                            events.ScheduleEvent(EVENT_INFERNO_RUSH, urand(30000, 34000), PHASE_COMBAT);
                            break;

                        case EVENT_SUMMON_INFERNO_RUSH_NPC:
                            if (infernoSummoned <= 5) // How can we calculate the ammount summoned in relation with distance to target?
                            {
                                me->SummonCreature(NPC_INFERNO_RUSH, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 10000);
                                infernoSummoned++;
                                events.ScheduleEvent(EVENT_SUMMON_INFERNO_RUSH_NPC, 1000, PHASE_COMBAT);
                            }
                            else
                            {
                                events.CancelEvent(EVENT_SUMMON_INFERNO_RUSH_NPC);
                                infernoSummoned = 0;
                            }
                            break;

                        case EVENT_AEGIS_OF_FLAME:
                            DoCast(me, SPELL_AEGIS_OF_FLAME);
                            events.ScheduleEvent(EVENT_RISING_FLAMES, 3000, PHASE_COMBAT);
                            events.ScheduleEvent(EVENT_AEGIS_OF_FLAME, urand(58000, 62000), PHASE_COMBAT);
                            break;

                        case EVENT_RISING_FLAMES:
                            Talk(SAY_I_RISING_FLAMES);
                            DoCast(me, SPELL_RISING_FLAMES);
                            break;

                        case EVENT_BURNING_BLOOD:
                            if (Unit* victim = SelectTarget(SELECT_TARGET_RANDOM, 0, 500.0f, true))
                                DoCast(victim, SPELL_BURNING_BLOOD);
                            events.ScheduleEvent(EVENT_BURNING_BLOOD, urand(21000, 23000), PHASE_COMBAT);
                            break;

                        case EVENT_FLAME_STRIKE:
                            if (Unit* victim = SelectTarget(SELECT_TARGET_RANDOM, 0, 500.0f, true))
                                me->SummonCreature(NPC_FLAME_STRIKE, victim->GetPositionX(), victim->GetPositionY(), victim->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN);
                            events.ScheduleEvent(EVENT_FLAME_STRIKE, urand(19000, 21000), PHASE_BALCONY);
                            break;

                        default:
                            break;
                    }
                }

                if (phase == PHASE_COMBAT && !me->HealthBelowPct(26))
                    DoMeleeAttackIfReady();
            }

    private:
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_ignaciousAI(creature);
    }
};

// 43688
class boss_arion : public CreatureScript
{
    public:
        boss_arion() : CreatureScript("boss_arion") { }

        struct boss_arionAI : public BossAI
        {
            boss_arionAI(Creature* creature) : BossAI(creature, DATA_ASCENDANT_COUNCIL), summons(me)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            Phases phase;
            SummonList summons;
            Unit* lightningVictim;
            uint32 lightningCasts;
            bool wentDown;

            void InitializeAI()
            {
                if (!instance)
                    me->IsAIEnabled = false;
                else if (!me->IsDead())
                    Reset();
            }

            void Reset()
            {
                me->RemoveAllAuras();
                phase = PHASE_NULL;
                summons.DespawnAll();
                lightningCasts = 0;
                wentDown = false;

                _Reset();
            }

            void EnterEvadeMode()
            {
                Reset();            
                me->GetMotionMaster()->MoveTargetedHome();   
                me->SetReactState(REACT_AGGRESSIVE);

                if (instance)
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove

                _EnterEvadeMode();
            }

            void EnterCombat(Unit* /*who*/)
            {
                EnterPhaseBalcony();
                lightningCasts = 0;
                wentDown = false;

                if (instance)
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add

                _EnterCombat();
            }

            void EnterPhaseCombat()
            {
                me->RemoveAllAuras();
                DoCast(me, SPELL_TELEPORT_VISUAL);
                me->NearTeleportTo(-1051.869f, -599.499f, 835.193f, 0.496f);
                phase = PHASE_COMBAT;
                me->SetReactState(REACT_AGGRESSIVE);
                events.SetPhase(PHASE_COMBAT);
                initEvents(true);
            }

            void EnterPhaseBalcony()
            {
                DoCast(me, SPELL_SELF_ROOT);
                phase = PHASE_BALCONY;
                events.SetPhase(PHASE_BALCONY);
                initEvents(false);
            }

            void initEvents(bool combatPhase = true)
            {
                events.Reset();
            
                if(combatPhase)
                {
                    events.ScheduleEvent(EVENT_SAY_A_AGGRO, 4500, PHASE_COMBAT); // Delay this so does not come in conflict with Terrastra aggro say.
                    
                    events.ScheduleEvent(EVENT_LIGHTNING_ROD, urand(6000, 10000), PHASE_COMBAT); // 15 sec.
                    events.ScheduleEvent(EVENT_DISPERSE, urand(14000, 16000), PHASE_COMBAT); // 30 sec repeat.
                    events.ScheduleEvent(EVENT_CALL_WINDS, urand(31000, 33000), PHASE_COMBAT);
                    events.ScheduleEvent(EVENT_THUNDERSHOCK, urand(58000, 62000), PHASE_COMBAT); // Then 33 sec.
                }else
                {
                    if (me->GetMap()->IsHeroic())
                         events.ScheduleEvent(EVENT_STATIC_OVERLOAD, 20000, PHASE_BALCONY);
                }
            }

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);
                summon->setActive(true);

                if (me->IsInCombat())
                    summon->AI()->DoZoneInCombat();
            }

            void KilledUnit(Unit* /*victim*/)
            {
                Talk(SAY_A_KILL);
            }

            void DamageTaken(Unit* /*who*/, uint32& damage)
            {
                if (damage > ((me->GetHealth() / 4) * 3)) // Check needed for correct split.
                    damage = (me->GetHealth() / 4) * 3;

                if (Creature* controller = me->FindNearestCreature(NPC_ASCENDANT_CONTROLLER, 500.0f, true))
                    controller->SetHealth(controller->GetHealth() - damage);
            }

            void JustDied(Unit* /*killer*/)
            {    
                _JustDied();
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING) || !phase)
                    return;

                // Check for last phase is made by controller npc, so it's not needed here. Only this check for balcony->ground phase is needed.
                Creature* feludius = me->FindNearestCreature(NPC_FELUDIUS, 500.0f, true); 
                Creature* ignacious = me->FindNearestCreature(NPC_IGNACIOUS, 500.0f, true);

                if (feludius && ignacious) // Check to prevent any damn crashes.
                    if ((feludius->HealthBelowPct(26) || ignacious->HealthBelowPct(26)) && !wentDown) // Check for Combat phase.
                    {
                        EnterPhaseCombat();
                        wentDown = true;
                    }

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SAY_A_AGGRO:
                            Talk(SAY_A_AGGRO);
                            break;

                        case EVENT_LIGHTNING_ROD:
                            if (Unit* victim = SelectTarget(SELECT_TARGET_RANDOM, 0, 500.0f, true))
                            {
                                victim->AddAura(SPELL_LIGHTNING_ROD, victim);
                                lightningVictim = victim;
                            }
                            events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, 3000, PHASE_COMBAT);
                            events.ScheduleEvent(EVENT_LIGHTNING_ROD, urand(24000, 28000), PHASE_COMBAT);
                            break;

                        case EVENT_CHAIN_LIGHTNING:
                            if (lightningVictim)
                            {
                                if (lightningCasts <= 5) // Cast Chain Lightning while victim has Rod.
                                {
                                    DoCast(lightningVictim, SPELL_CHAIN_LIGHTNING);
                                    lightningCasts++;
                                    events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, 3000, PHASE_COMBAT);
                                }
                                else
                                {
                                    events.CancelEvent(EVENT_CHAIN_LIGHTNING);
                                    lightningCasts = 0;
                                }
                            }
                            break;

                        case EVENT_DISPERSE:
                            if (Unit* victim = SelectTarget(SELECT_TARGET_RANDOM, 0, 500.0f, true))
                                DoCast(victim, SPELL_DISPERSE);
                            events.ScheduleEvent(EVENT_LIGHTNING_BLAST, 3000, PHASE_COMBAT);
                            events.ScheduleEvent(EVENT_DISPERSE, urand(29000, 31000), PHASE_COMBAT);
                            break;

                        case EVENT_LIGHTNING_BLAST:
                            DoCastVictim(SPELL_LIGHTNING_BLAST);
                            break;

                        case EVENT_THUNDERSHOCK:
                            me->MonsterTextEmote(EMOTE_ARION_THUNDERSHOCK, NULL, false);
                            DoCast(me, SPELL_THUNDERSHOCK);
                            events.ScheduleEvent(EVENT_THUNDERSHOCK, urand(32000, 34000), PHASE_COMBAT);
                            break;

                        case EVENT_CALL_WINDS:
                            Talk(SAY_A_CALL_WINDS);
                            if (Unit* victim = SelectTarget(SELECT_TARGET_RANDOM, 0, 500.0f, true))
                                DoCast(victim, SPELL_CALL_WINDS);
                            events.ScheduleEvent(EVENT_CALL_WINDS, urand(58000, 62000), PHASE_COMBAT);
                            break;

                        case EVENT_STATIC_OVERLOAD:
                            if (Unit* victim = SelectTarget(SELECT_TARGET_RANDOM, 0, 500.0f, true))
                                DoCast(victim, SPELL_STATIC_OVERLOAD);
                            events.ScheduleEvent(EVENT_STATIC_OVERLOAD, urand(19000, 21000), PHASE_BALCONY);
                            break;

                        default:
                            break;
                    }
                }

                if (phase == PHASE_COMBAT && !me->HealthBelowPct(26))
                    DoMeleeAttackIfReady();
            }

    private:
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_arionAI(creature);
    }
};

// 43689
class boss_terrastra : public CreatureScript
{
    public:
        boss_terrastra() : CreatureScript("boss_terrastra") { }

        struct boss_terrastraAI : public BossAI
        {
            boss_terrastraAI(Creature* creature) : BossAI(creature, DATA_ASCENDANT_COUNCIL), summons(me)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            Phases phase;
            SummonList summons;
            bool wentDown;

            void InitializeAI()
            {
                if (!instance)
                    me->IsAIEnabled = false;
                else if (!me->IsDead())
                    Reset();
            }

            void Reset()
            {
                me->RemoveAllAuras();
                phase = PHASE_NULL;
                summons.DespawnAll();
                wentDown = false;
                _Reset();
            }

            void EnterEvadeMode()
            {
                Reset();            
                me->GetMotionMaster()->MoveTargetedHome();   
                me->SetReactState(REACT_AGGRESSIVE);

                if (instance)
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove

                _EnterEvadeMode();
            }

            void EnterCombat(Unit* /*who*/)
            {
                EnterPhaseBalcony();
                wentDown = false;
                if (instance)
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add

                _EnterCombat();
            }
    
            void EnterPhaseCombat()
            {
                me->RemoveAllAuras();
                Talk(SAY_T_AGGRO);
                DoCast(me, SPELL_TELEPORT_VISUAL);
                me->NearTeleportTo(-1050.369f, -565.689f, 835.221f, 5.946f);
                phase = PHASE_COMBAT;
                me->SetReactState(REACT_AGGRESSIVE);
                events.SetPhase(PHASE_COMBAT);
                initEvents(true);
            }

            void EnterPhaseBalcony()
            {
                DoCast(me, SPELL_SELF_ROOT);
                phase = PHASE_BALCONY;
                events.SetPhase(PHASE_BALCONY);
                initEvents(false);
            }

            void initEvents(bool combatPhase = true)
            {
                events.Reset();
            
                if(combatPhase)
                {
                events.ScheduleEvent(EVENT_ERUPTION, urand(6000, 10000), PHASE_COMBAT); // 15 sec.
                events.ScheduleEvent(EVENT_QUAKE, urand(14000, 16000), PHASE_COMBAT); // 33 sec repeat.
                events.ScheduleEvent(EVENT_HARDEN_SKIN, urand(31000, 33000), PHASE_COMBAT); // 42 sec repeat
                events.ScheduleEvent(EVENT_GRAVITY_WELL, urand(58000, 62000), PHASE_COMBAT); //  every 60 sec.
                }else
                {
                    if (me->GetMap()->IsHeroic())
                         events.ScheduleEvent(EVENT_GRAVITY_CORE, 20000, PHASE_BALCONY);
                }
            }

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);
                summon->setActive(true);
            
                switch(summon->GetEntry())
                {
                    case NPC_ERUPTION_TGT:
                        summon->CastSpell(summon, SPELL_ERUPTION, false);
                        summon->AddAura(SPELL_ERUPTION_VISUAL, summon);
                        summon->DespawnOrUnsummon(5000);
                        break;

                    default:
                        if (me->IsInCombat())
                            summon->AI()->DoZoneInCombat(summon, 150.0f);
                        break;
                }
            }

            void KilledUnit(Unit* /*victim*/)
            {
                Talk(SAY_T_KILL);
            }

            void DamageTaken(Unit* /*who*/, uint32& damage)
            {
                if (damage > ((me->GetHealth() / 4) * 3)) // Check needed for correct split.
                    damage = (me->GetHealth() / 4) * 3;

                if (Creature* controller = me->FindNearestCreature(NPC_ASCENDANT_CONTROLLER, 500.0f, true))
                    controller->SetHealth(controller->GetHealth() - damage);
            }

            void JustDied(Unit* /*killer*/)
            {    
                _JustDied();
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING) || !phase)
                    return;

                // Check for last phase is made by controller npc, so it's not needed here. Only this check for balcony->ground phase is needed.
                Creature* feludius = me->FindNearestCreature(NPC_FELUDIUS, 500.0f, true); 
                Creature* ignacious = me->FindNearestCreature(NPC_IGNACIOUS, 500.0f, true);

                if (feludius && ignacious) // Check to prevent any damn crashes.
                    if ((feludius->HealthBelowPct(26) || ignacious->HealthBelowPct(26)) && !wentDown) // Check for Combat phase.
                    {
                        EnterPhaseCombat();
                        wentDown = true;
                    }

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_QUAKE:
                            me->MonsterTextEmote(EMOTE_TERRASTRA_QUAKE, NULL, false);
                            DoCast(me, SPELL_QUAKE);
                            events.ScheduleEvent(EVENT_QUAKE, urand(32000, 34000), PHASE_COMBAT);
                            break;

                        case EVENT_ERUPTION:
                            if (Unit* victim = SelectTarget(SELECT_TARGET_RANDOM, 0, 500.0f, true))
                                DoCast(victim, SPELL_ERUPTION_SUMMON_MOB);
                            events.ScheduleEvent(EVENT_ERUPTION, urand(14000, 16000), PHASE_COMBAT);
                            break;

                        case EVENT_HARDEN_SKIN:
                            DoCast(me, SPELL_HARDEN_SKIN);
                            events.ScheduleEvent(EVENT_HARDEN_SKIN, urand(41000, 43000), PHASE_COMBAT);
                            break;

                        case EVENT_GRAVITY_WELL:
                            Talk(SAY_T_GRAVITY_WELL);
                            if (Unit* victim = SelectTarget(SELECT_TARGET_RANDOM, 0, 500.0f, true))
                                me->SummonCreature(NPC_GRAVITY_WELL, victim->GetPositionX(), victim->GetPositionY(), victim->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 30000);
                            events.ScheduleEvent(EVENT_GRAVITY_WELL, urand(58000, 62000), PHASE_COMBAT);
                            break;

                        case EVENT_GRAVITY_CORE:
                            if (Unit* victim = SelectTarget(SELECT_TARGET_RANDOM, 0, 500.0f, true))
                                DoCast(victim, SPELL_GRAVITY_CORE);
                            events.ScheduleEvent(EVENT_GRAVITY_CORE, urand(19000, 21000), PHASE_BALCONY);
                            break;

                        default:
                            break;
                    }
                }

                if (phase == PHASE_COMBAT && !me->HealthBelowPct(26))
                    DoMeleeAttackIfReady();
            }

    private:
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_terrastraAI(creature);
    }
};

// 43735
class boss_monstrosity : public CreatureScript
{
    public:
        boss_monstrosity() : CreatureScript("boss_monstrosity") { }

        struct boss_monstrosityAI : public BossAI
        {
            boss_monstrosityAI(Creature* creature) : BossAI(creature, DATA_ASCENDANT_COUNCIL), summons(me)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            SummonList summons;
            uint8 count, mode;

            void InitializeAI()
            {
                if (!instance)
                    me->IsAIEnabled = false;
                else if (!me->IsDead())
                    Reset();
            }

            void Reset()
            {
                summons.DespawnAll();

                _Reset();
            }

            void EnterEvadeMode()
            {
                summons.DespawnAll();
                Creature* feludius = me->FindNearestCreature(NPC_FELUDIUS, 500.0f, true); 
                Creature* ignacious = me->FindNearestCreature(NPC_IGNACIOUS, 500.0f, true); 
                Creature* arion = me->FindNearestCreature(NPC_ARION, 500.0f, true); 
                Creature* terrastra = me->FindNearestCreature(NPC_TERRASTRA, 500.0f, true);   
  
                if (feludius && ignacious && arion && terrastra) // Check to prevent any damn crashes.
                {
                    feludius->SetDisplayId(MODEL_FELUDIUS);
                    terrastra->SetDisplayId(MODEL_TERRASTRA);
                    arion->SetDisplayId(MODEL_ARION);
                    ignacious->SetDisplayId(MODEL_IGNACIOUS);
                    feludius->IsAIEnabled = true;
                    ignacious->IsAIEnabled = true;
                    arion->IsAIEnabled = true;
                    terrastra->IsAIEnabled = true;
                    feludius->AI()->EnterEvadeMode();
                    terrastra->AI()->EnterEvadeMode();
                    arion->AI()->EnterEvadeMode();
                    ignacious->AI()->EnterEvadeMode();
                    me->DespawnOrUnsummon();
                }

                if (instance)
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove

                _EnterEvadeMode();
            }

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);
                summon->setActive(true);
            
                if(me->IsInCombat())
                summon->AI()->DoZoneInCombat();
            }

            void KilledUnit(Unit* /*victim*/)
            {
                Talk(SAY_M_KILL);
            }

            void JustDied(Unit* /*killer*/)
            {
                Talk(SAY_M_DIE);
                summons.DespawnAll();

                Creature* controller = me->FindNearestCreature(NPC_ASCENDANT_CONTROLLER, 500.0f, true);
                Creature* feludius = me->FindNearestCreature(NPC_FELUDIUS, 500.0f, true); 
                Creature* ignacious = me->FindNearestCreature(NPC_IGNACIOUS, 500.0f, true); 
                Creature* arion = me->FindNearestCreature(NPC_ARION, 500.0f, true); 
                Creature* terrastra = me->FindNearestCreature(NPC_TERRASTRA, 500.0f, true);  
                
                if (controller && feludius && ignacious && arion && terrastra) // Check to prevent any damn crashes.
                {
                    feludius->Kill(feludius); // To count as killed on addons. No Killed talk since AI is disabled :D.
                    terrastra->Kill(terrastra);
                    arion->Kill(arion);
                    ignacious->Kill(ignacious);
                    controller->DisappearAndDie();
                }

                if (instance)
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove

                _JustDied();
            }

            void EnterCombat(Unit* /*who*/)
            {
                Talk(SAY_M_AGGRO);

                if (instance)
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add

                events.ScheduleEvent(EVENT_ELECTRIC_INSTABILITY, 1500); // every 1-2 sec, targets increase.
                events.ScheduleEvent(EVENT_SUMMON_LIQUID_ICE, urand(33000, 37000)); // every 35 sec.
                events.ScheduleEvent(EVENT_LAVA_SEED, urand(9000, 12000)); // every 23 sec.
                events.ScheduleEvent(EVENT_GRAVITY_CRUSH, urand(17000, 20000)); // every 24 sec.

                _EnterCombat();
            }

            void DamageTaken(Unit* /*who*/, uint32& damage)
            {
                if (Creature* controller = me->FindNearestCreature(NPC_ASCENDANT_CONTROLLER, 500.0f, true))
                    controller->SetHealth(controller->GetHealth() - damage);
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
                        case EVENT_ELECTRIC_INSTABILITY:
                        {
                            if (count > 40)
                                mode = RAID_MODE(7, 8, 15, 20);
                            else if (count > 28)
                                mode = RAID_MODE(5, 6, 11, 15);
                            else if (count > 20)
                                mode = RAID_MODE(4, 5, 8, 10);
                            else if (count > 15)
                                mode = RAID_MODE(4, 5, 7, 8);
                            else if (count > 9)
                                mode = RAID_MODE(3, 4, 6, 7);
                            else if (count > 4)
                                mode = RAID_MODE(3, 4, 5, 6);
                            else
                                mode = RAID_MODE(2, 3, 4, 5);
                            
                            std::list<Unit*> targets;
                            SelectTargetList(targets, mode, SELECT_TARGET_RANDOM, 200.0f, true);
                            if (!targets.empty())
                                for (std::list<Unit*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                                    DoCast(*itr, SPELL_ELECTRIC_INSTABILITY_TARGET);

                            count++;
                            events.ScheduleEvent(EVENT_ELECTRIC_INSTABILITY, urand(1000,2000)); // every 1-2 sec, targets increase.
                        }
                            break;

                        case EVENT_SUMMON_LIQUID_ICE:
                            me->SummonCreature(NPC_LIQUID_ICE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 120000);
                            events.ScheduleEvent(EVENT_SUMMON_LIQUID_ICE, urand(33000, 37000));
                            break;

                        case EVENT_LAVA_SEED:
                            Talk(SAY_M_LAVA_SEEDS);
                            DoCast(me, SPELL_LAVA_SEED);
                            events.ScheduleEvent(EVENT_LAVA_SEED_SUMMON, 2000);
                            events.ScheduleEvent(EVENT_LAVA_SEED, urand(22000, 24000));
                            break;

                        case EVENT_LAVA_SEED_SUMMON: // They explode after 5n / 4h seconds.
                        {
                            std::list<Unit*> targets;
                            SelectTargetList(targets, RAID_MODE(5, 10, 8, 15), SELECT_TARGET_RANDOM, 500.0f, true);
                            if (!targets.empty())
                            for (std::list<Unit*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            if (Unit* raider = Unit::GetUnit(*me, (*itr)->GetGUID()))
                            if (raider->GetTypeId() == TYPEID_PLAYER)
                                me->SummonCreature(NPC_LAVA_SEED, raider->GetPositionX(), raider->GetPositionY(), raider->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, RAID_MODE(6000, 5000, 6000, 5000));
                        }
                            break;

                        case EVENT_GRAVITY_CRUSH:
                        {
                            Talk(SAY_M_GRAVITY_CRUSH);
                            DoCast(me, SPELL_GRAVITY_CRUSH); // Fake cast look.

                            std::list<Unit*> targets; // Actual effect.
                            SelectTargetList(targets, RAID_MODE(1, 3, 1, 3), SELECT_TARGET_RANDOM, 500.0f, true);
                            if (!targets.empty())
                                for (std::list<Unit*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            if (Unit* raider = Unit::GetUnit(*me, (*itr)->GetGUID()))
                            if (raider->GetTypeId() == TYPEID_PLAYER)
                                //me->SummonCreature(NPC_GRAVITY_CRUSH, raider->GetPositionX(), raider->GetPositionY(), raider->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 6500);
                                me->AddAura(SPELL_GRAVITY_CRUSH, raider);

                            events.ScheduleEvent(EVENT_GRAVITY_CRUSH, urand(23000, 25000));
                        }
                            break;

                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }

    private:
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_monstrosityAI(creature);
    }
};

// 44201
class npc_feludius_waterbomb : public CreatureScript // 44201
{
    public:
        npc_feludius_waterbomb() : CreatureScript("npc_feludius_waterbomb") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_feludius_waterbombAI(creature);
        }
            
        struct npc_feludius_waterbombAI : public ScriptedAI
        {
            npc_feludius_waterbombAI(Creature* creature) : ScriptedAI(creature) 
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;

            void Reset()
            {
                events.ScheduleEvent(EVENT_WATER_BOMB_EXPLODE, 100);
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
                        case EVENT_WATER_BOMB_EXPLODE:
                            DoCast(me, SPELL_WATER_BOMB_DMG);
                            me->DisappearAndDie();
                            break;
                    }
                }
            }
        };
};

// 44747
class npc_arion_callwinds : public CreatureScript // 44747
{
    public:
        npc_arion_callwinds() : CreatureScript("npc_arion_callwinds") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_arion_callwindsAI(creature);
        }
            
        struct npc_arion_callwindsAI : public ScriptedAI
        {
            npc_arion_callwindsAI(Creature* creature) : ScriptedAI(creature) 
            {
                instance = creature->GetInstanceScript();
                creature->SetReactState(REACT_PASSIVE);
                creature->CastSpell(creature, SPELL_LASHING_WINDS_VISUAL, true);
                creature->GetMotionMaster()->MoveRandom(100.0f);
            }

            InstanceScript* instance;
            EventMap events;

            void Reset()
            {
                events.ScheduleEvent(EVENT_CHECK_WINDS_PLAYER, 1000);
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
                        case EVENT_CHECK_WINDS_PLAYER:
                            if(Unit* victim = me->FindNearestPlayer(3.0f, true))
                                me->CastSpell(victim, SPELL_SWIRLING_WINDS, false);

                            events.ScheduleEvent(EVENT_CHECK_WINDS_PLAYER, 500);
                            break;
                    }
                }
            }
        };
};

// 44824
class npc_terrastra_gravitywell : public CreatureScript // 44824
{
    public:
        npc_terrastra_gravitywell() : CreatureScript("npc_terrastra_gravitywell") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_terrastra_gravitywellAI(creature);
        }
            
        struct npc_terrastra_gravitywellAI : public ScriptedAI
        {
            npc_terrastra_gravitywellAI(Creature* creature) : ScriptedAI(creature) 
            {
                instance = creature->GetInstanceScript();
                creature->SetReactState(REACT_PASSIVE);
                creature->CastSpell(creature, SPELL_GRAV_WELL_MOB_VISUAL, true);
                creature->CastSpell(creature, SPELL_GRAVITY_WELL_VISUAL, true);
                creature->CastSpell(creature, AURA_GRAVITY_WELL_PULL, true); // Pull players.
                creature->CastSpell(creature, AURA_GRAVITY_WELL_DMG_GROUNDED, true); // Deal damage.    
            }

            InstanceScript* instance;

            void Reset() { }

            void UpdateAI(uint32 /*diff*/) { }
        };
};

// 45452
class npc_monstrosity_liquid_ice : public CreatureScript // 45452
{
    public:
        npc_monstrosity_liquid_ice() : CreatureScript("npc_monstrosity_liquid_ice") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_monstrosity_liquid_iceAI(creature);
        }
            
        struct npc_monstrosity_liquid_iceAI : public ScriptedAI
        {
            npc_monstrosity_liquid_iceAI(Creature* creature) : ScriptedAI(creature) 
            {
                instance = creature->GetInstanceScript();
                creature->SetReactState(REACT_PASSIVE);
                creature->CastSpell(creature, SPELL_LIQUID_ICE_PERIODIC, true);
            }

            InstanceScript* instance;
            EventMap events;

            void Reset()
            {
                events.ScheduleEvent(EVENT_LIQUID_ICE_GROW, 3000);
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
                        case EVENT_LIQUID_ICE_GROW:
                            if (me->FindNearestCreature(NPC_ELEMENTIUM_MONSTROSITY, 10.0f, true))
                                DoCast(me, SPELL_LIQUID_ICE_GROW);

                            events.ScheduleEvent(EVENT_LIQUID_ICE_GROW, 3000);
                            break;
                    }
                }
            }
        };
};

// 48538
class npc_monstrosity_lava_seed : public CreatureScript // 48538
{
    public:
        npc_monstrosity_lava_seed() : CreatureScript("npc_monstrosity_lava_seed") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_monstrosity_lava_seedAI(creature);
        }
            
        struct npc_monstrosity_lava_seedAI : public ScriptedAI
        {
            npc_monstrosity_lava_seedAI(Creature* creature) : ScriptedAI(creature) 
            {
                instance = creature->GetInstanceScript();
                creature->SetReactState(REACT_PASSIVE);
                creature->CastSpell(creature, AURA_LAVA_SEED_VISUAL, true);
            }

            InstanceScript* instance;
            EventMap events;

            void Reset()
            {
                events.ScheduleEvent(EVENT_SEED_EXPLODE, 4000);
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
                        case EVENT_SEED_EXPLODE:
                            DoCast(me, SPELL_LAVA_EXPLODE);
                            DoCast(me, SPELL_LAVA_ERRUPT_EMOTE);
                            me->DespawnOrUnsummon(1000);
                            break;
                    }
                }
            }
        };
};

// HEROIC NPC-s.

// 49432
class npc_ignacious_flame_strike : public CreatureScript // 49432
{
    public:
        npc_ignacious_flame_strike() : CreatureScript("npc_ignacious_flame_strike") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_ignacious_flame_strikeAI(creature);
        }
            
        struct npc_ignacious_flame_strikeAI : public ScriptedAI
        {
            npc_ignacious_flame_strikeAI(Creature* creature) : ScriptedAI(creature) 
            {
                instance = creature->GetInstanceScript();
                creature->SetReactState(REACT_PASSIVE);
                creature->CastSpell(creature, SPELL_FLAME_STRIKE_TARGET, true);
            }

            InstanceScript* instance;
            EventMap events;

            void Reset()
            {
                events.ScheduleEvent(EVENT_FLAME_STRIKE_DAMAGE, 5000);
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
                        case EVENT_FLAME_STRIKE_DAMAGE:
                            DoCast(me, SPELL_FLAME_STRIKE_DAMAGE);
                            me->DespawnOrUnsummon(2000);
                            break;
                    }
                }
            }
        };
};

// 49518
class npc_feludius_frozen_orb : public CreatureScript // 49518
{
    public:
        npc_feludius_frozen_orb() : CreatureScript("npc_feludius_frozen_orb") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_feludius_frozen_orbAI(creature);
        }
            
        struct npc_feludius_frozen_orbAI : public ScriptedAI
        {
            npc_feludius_frozen_orbAI(Creature* creature) : ScriptedAI(creature) 
            {
                instance = creature->GetInstanceScript();
                creature->CastSpell(creature, SPELL_FROZEN_ORB_VISUAL_AURA, true);
            }

            InstanceScript* instance;
            EventMap events;
    
            void Reset()
            {
                me->SetSpeed(MOVE_WALK, 0.2f, true);
                me->SetSpeed(MOVE_RUN, 0.2f, true);
                events.ScheduleEvent(EVENT_ATTACK_FROZEN_TARGET, 100);
                events.ScheduleEvent(EVENT_CHECK_FROZEN_TARGET, 1000);
                events.ScheduleEvent(EVENT_FROZEN_DESPAWN, 35000);
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
                        case EVENT_ATTACK_FROZEN_TARGET:
                            if(Unit* victim = SelectTarget(SELECT_TARGET_RANDOM, 0, 500.0f, true))
                                if(victim)
                                {
                                    SetGazeOn(victim);
                                    me->AddAura(SPELL_FROST_BEACON, victim);
                                }
                            break;

                        case EVENT_CHECK_FROZEN_TARGET:
                            DoCast(me, SPELL_INCREASE_RUN_SPEED);
                            if(me->GetDistance2d(me->GetVictim()) < 3.0f)
                            {
                                DoCast(me, SPELL_GLACIATE);
                                me->DespawnOrUnsummon();
                            }
                            events.ScheduleEvent(EVENT_CHECK_FROZEN_TARGET, 1000);
                            break;

                        case EVENT_FROZEN_DESPAWN:
                            me->DespawnOrUnsummon();
                            break;
                    }
                }
            }
        };
};

// 82699
class spell_feludius_waterbomb : public SpellScriptLoader // 82699.
{
public:
    spell_feludius_waterbomb() : SpellScriptLoader("spell_feludius_waterbomb") { }

    class spell_feludius_waterbombSpellScript : public SpellScript
    {
        PrepareSpellScript(spell_feludius_waterbombSpellScript);

        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            return true;
        }

        bool Load()
        {
            return true;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            std::list<Unit*> targets;
            GetCaster()->GetAI()->SelectTargetList(targets, GetCaster()->GetInstanceScript()->instance->Is25ManRaid() ? 5 : 2, SELECT_TARGET_RANDOM, 150.0f, true);
            if (!targets.empty())
                for (std::list<Unit*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    if (Unit* temp = Unit::GetUnit(*GetCaster(), (*itr)->GetGUID()))
                        if (temp->GetTypeId() == TYPEID_PLAYER)
                            GetCaster()->SummonCreature(NPC_WATER_BOMB, temp->GetPositionX(), temp->GetPositionY(), temp->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 500);
        }

        void Register()
        {
            OnEffectHit += SpellEffectFn(spell_feludius_waterbombSpellScript::HandleDummy,EFFECT_0,SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript *GetSpellScript() const
    {
        return new spell_feludius_waterbombSpellScript();
    }
};

// 82746 92506 92507 92508
class spell_feludius_glaciate: public SpellScriptLoader // 82746
{
public:
    spell_feludius_glaciate () :
            SpellScriptLoader("spell_feludius_glaciate") { }

    class spell_feludius_glaciateSpellScript: public SpellScript
    {
        PrepareSpellScript(spell_feludius_glaciateSpellScript);

        void CalculateDamage(SpellEffIndex /*effIndex*/)
        {
            if (!GetHitUnit())
                return;

            float distance = GetCaster()->GetDistance2d(GetHitUnit());

            if (distance > 1.0f)
                SetHitDamage(int32(GetHitDamage() - ((GetCaster()->GetInstanceScript()->instance->Is25ManRaid() ? 10000 : 4000) * distance))); // Drops to 10k after 50 yards.

            if (GetHitDamage() < 10000) // Don't let it go lower then 10k. This is min you can get.
                SetHitDamage(10000);
        }

        void EffectScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (GetHitUnit()->HasAura(SPELL_WATERLOGGED))
                GetCaster()->AddAura(SPELL_FROZEN, GetHitUnit()); // Special info.
        }

        void Register ()
        {
            OnEffectHitTarget += SpellEffectFn(spell_feludius_glaciateSpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            OnEffectHitTarget += SpellEffectFn(spell_feludius_glaciateSpellScript::EffectScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript * GetSpellScript () const
    {
        return new spell_feludius_glaciateSpellScript();
    }
};

// 83087
class spell_arion_disperse: public SpellScriptLoader // 83087
{
public:
    spell_arion_disperse () :
            SpellScriptLoader("spell_arion_disperse") { }

    class spell_arion_disperseSpellScript: public SpellScript
    {
        PrepareSpellScript(spell_arion_disperseSpellScript);

        void EffectScriptEffect(SpellEffIndex /*effIndex*/)
        {
                GetCaster()->CastSpell(GetHitUnit(), SPELL_DISPERSE_TELEPORT, true); // Teleport.
        }

        void Register ()
        {
            OnEffectHitTarget += SpellEffectFn(spell_arion_disperseSpellScript::EffectScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript * GetSpellScript () const
    {
        return new spell_arion_disperseSpellScript();
    }
};

// 83067 92469 92470 92471
class spell_arion_thundershock: public SpellScriptLoader // 83067
{
public:
    spell_arion_thundershock () :
            SpellScriptLoader("spell_arion_thundershock") { }

    class spell_arion_thundershockSpellScript: public SpellScript
    {
        PrepareSpellScript(spell_arion_thundershockSpellScript);

        void CalculateDamage(SpellEffIndex /*effIndex*/)
        {
            if (!GetHitUnit())
                return;

            float distance = GetCaster()->GetDistance2d(GetHitUnit());

            if (distance > 1.0f)
                SetHitDamage(int32(GetHitDamage() - ((GetCaster()->GetInstanceScript()->instance->Is25ManRaid() ? 3000 : 1500) * distance))); // Depends on distance from caster.

            if (GetHitUnit()->HasAura(SPELL_GROUNDED))
                SetHitDamage(int32(GetHitDamage() / 3));

            if (GetHitDamage() < 5000) // Don't let it go lower then 5k. This is min you can get.
                SetHitDamage(5000);
        }

        void Register ()
        {
            OnEffectHitTarget += SpellEffectFn(spell_arion_thundershockSpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript * GetSpellScript () const
    {
        return new spell_arion_thundershockSpellScript();
    }
};

// 83565 92544 92545 92546
class spell_terrastra_quake: public SpellScriptLoader // 83565
{
public:
    spell_terrastra_quake () :
            SpellScriptLoader("spell_terrastra_quake") { }

    class spell_terrastra_quakeSpellScript: public SpellScript
    {
        PrepareSpellScript(spell_terrastra_quakeSpellScript);

        void CalculateDamage(SpellEffIndex /*effIndex*/)
        {
            if (!GetHitUnit())
                return;

            if (GetHitUnit()->HasAura(SPELL_SWIRLING_WINDS))
                SetHitDamage(0);
        }

        void Register ()
        {
            OnEffectHitTarget += SpellEffectFn(spell_terrastra_quakeSpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript * GetSpellScript () const
    {
        return new spell_terrastra_quakeSpellScript();
    }
};

void AddSC_boss_ascendant_council()
{
    new npc_ascendant_council_controller();
    new boss_feludius();
    new boss_ignacious();
    new boss_arion();
    new boss_terrastra();
    new boss_monstrosity();
    new npc_feludius_waterbomb();
    new npc_arion_callwinds();
    new npc_terrastra_gravitywell();
    new npc_ignacious_flame_strike();
    new npc_feludius_frozen_orb();
    new npc_monstrosity_liquid_ice();
    new npc_monstrosity_lava_seed();
    new spell_feludius_waterbomb();
    new spell_feludius_glaciate();
    new spell_arion_disperse();
    new spell_arion_thundershock();
    new spell_terrastra_quake();
}