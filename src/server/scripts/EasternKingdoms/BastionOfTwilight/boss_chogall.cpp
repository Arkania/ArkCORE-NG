/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * Script 99% done. TODO:
 * - Fix falling through floor.
 * - Wrong spells for orders on heroic? to check no visuals etc.
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

enum Yells
{
    SAY_AGGRO     = 0,
    SAY_CONV_1    = 1,
    SAY_CONV_2    = 2,
    SAY_CONV_3    = 3,
    SAY_ADHER_1   = 4,
    SAY_ADHER_2   = 5,
    SAY_ADHER_3   = 6,
    SAY_COG       = 7,
    SAY_DARKCR_1  = 8,
    SAY_DARKCR_2  = 9,
    SAY_DARKCR_3  = 10,
    SAY_DARKCR_4  = 11,
    SAY_DARKCR_5  = 12,
    SAY_KILL_1    = 13,
    SAY_KILL_2    = 14,
    SAY_KILL_3    = 15,
    SAY_KILL_4    = 16,
    SAY_EVADE     = 17,
    SAY_DEATH     = 18,
    SAY_DEATH_H   = 19,

    SAY_ADHERENT  = 20,
    SAY_PHASE2    = 21
};

enum Spells
{
    /***** CHO'GALL *****/

    // Corruption Bar
    SPELL_CORRUPTION_AURA = 93103,

    // Phase 1 - 100 to 26 %.

    /** Cho'gall causes random players to Worship him, granting him one application of Twisted Devotion every 3 sec. **/
    SPELL_CONVERSION     = 91303, // Script effect for 25 player only (add below spell to multiple targets?).
    SPELL_WORSHIPPING    = 91317, // "Worshipping Cho'gall" aura - triggers 91331 on cho'gall, needs condition.

    /** Fury of Cho'gall – Cho'gall blasts his current target, 34125 to 35875 Shadow and 34125 to 35875 Physical damage, ++ Physical and Shadow damage taken by 20% for 1 min. **/
    SPELL_FURY_OF_CHOGALL = 82524, // On tank only.

    /** Flame's Orders – Cho'gall calls forth a Fire elemental and absorbs the elemental into his Twilight Hammer, empowering it with Flaming Destruction. **/
    // On Heroic difficulty Cho'gall gains one additional stack of Flaming Destruction for each 10% health remaining on the elemental when it is absorbed.
    SPELL_FLAME_ORDERS   = 87579, // Summons 47020 - Fire Portal in 15 yards.
    SPELL_F_O_PERIODIC   = 87581, // Trigger above every 50 seconds. - NEED THIS!!!
    SPELL_FO_SUMMON_1    = 87582, // Summons Fire Elemental big, 47017.

    SPELL_ABSORB_FIRE    = 81196, // Triggers Flaming Destruction (81194) plus visual after 3 sec. Summ Blaze. Has a ride vehicle script eff (for elemental going into hammer??).
    SPELL_BLAZE_PERIODIC = 81536, // Blaze npc on self.

    // SPELL_FLAME_ORDERS_2  = 81171, // Summons 43393 - Fire Portal in 15 yards, has no periodic trigger ??! - WTF IS THIS? Not needed...
    // SPELL_FO_SUMMON_2     = 81186, // Summons Fire Elemental very SMALL, 43406 ?! - WTF IS THIS? Not needed...

    /** Shadow's Orders – Cho'gall calls forth a Shadow elemental and absorbs the elemental into his Twilight Hammer, imbuing it with Empowered Shadows. **/
    // On Heroic Difficulty Cho'gall gains one stack of Empowered Shadows for each 10% health remaining on the elemental when it is absorbed.
    SPELL_SHADOW_ORDERS  = 87575, // Summons 47019 - Shadow Portal in 15 yards.
    SPELL_S_O_PERIODIC   = 87576, // Trigger above every 50 seconds. - NEED THIS!!!
    SPELL_SO_SUMMON_1    = 87583, // Summons Shadow Lord big, 47016.

    // SPELL_SHADOW_ORDERS_2  = 81556, // Summons 43603 - Shadow Portal in 15 yards, has no periodic trigger ??! - WTF IS THIS? Not needed...
    // SPELL_SO_SUMMON_2     = 81558, // Summons Shadow Lord very SMALL, 43592 ?! - WTF IS THIS? Not needed...

    SPELL_ABSORB_SHADOW  = 81566, // Triggers Empowered Shadows (81194) plus visual after 3 sec (!3x3 81571 RADIUS 50k). Has a ride vehicle script eff (for lord going into hammer??).

    /** Summon Corrupting Adherent – Cho'gall summons a Corrupting Adherent from one of twilight portals at the sides of the room. **/
    // Why two summon spells for this script effect? Here: On 25-player Heroic difficulty, Cho'gall activates both portals, summoning two Corrupting Adherents simultaneously.
    SPELL_SUM_ADHER_SE   = 81628, // Script effect with cast time - NEEDS SCRIPT!! Npc 43622 - Corrupting Adherent.
    SPELL_SUMM_ADH_1     = 81611, // First.
    SPELL_SUMM_ADH_2     = 81618, // Second.

    /** Fester Blood – Cho'gall festers the blood of dead Corrupting Adherents, causing pools of Spilled Blood of the Old God to form into animated oozes (blood of the old god). 
        Fester Blood also causes the dark blood of any living Corrupting Adherents to boil, causing the Festering Blood effect. **/
    SPELL_FESTER_BLOOD   = 82299, // Cast by boss -> after 3 sec 82337 with script eff for Festered Blood (82333) which summons Blood of the Old God oozes - npc 43707 (from dead adh).
    SPELL_FESTERIN_BLOOD = 82914, // Living adherents use this - damage spell, triggers 82919 which is actual damage spell needs radius and script eff for applying corruption.

    //Phase 2 - 25 to 0 %. !! Boss retains only Fury of Cho'gall spell. !!
    SPELL_CORR_OLD_GOD   = 82361, // Visual, trigger for damage spell 82363 which needs radius and script eff to apply corruption.

    /** Darkened Creations – Darkened Creations, tentacles spawned by Cho'gall, continually try to channel Debilitating Beam  (82411, H: + corruption) on a random player. **/
    SPELL_DARK_CREAT_VIS = 82414, // Some visual dummy shit.
    SPELL_SUMM_DARK_CREA = 82433, // Actual summon spell. Npc Darkened Creation 44045.

    // Misc
    SPELL_BERSERK        = 47008, // 10 min enrage all diffs. Maybe wrong and spell = 65126?

    /***** MOBS *****/
    // Adherent
    SPELL_DEPRAVITY      = 81713, // Needs script eff for corruption.
    SPELL_CORRUPT_CRASH  = 81685, // Needs script eff for corruption.
    SPELL_SPILLED_VISUAL = 81771, // Dummy visual.
    SPELL_SPILLED_POOL   = 81757, // When they "die".

    // Darkened Creations
    SPELL_DEBILIT_BEAM   = 82411, // !Add corruption for heroic version.
    SPELL_TENTACLE_VIS   = 82451,

    // Portal visuals
    SPELL_VIS_FLAMEP     = 81172,
    SPELL_VIS_SHADOWP    = 81559,

    SPELL_CONSUME_BLOOD  = 82630,

    SPELL_MALFORMATION_SHADOWBOLT = 85544 // 82151 - ex target aura worshipping, this is weird.
};

enum Events
{
    /*** CHO'GALL ***/
    EVENT_CONVERSION = 1,
    EVENT_FURY_OF_CHOGALL, // P 1 + 2
    EVENT_FLAME_ORDERS,
    EVENT_SHADOW_ORDERS,
    EVENT_SUMMON_ADHERENT,
    EVENT_FESTER_BLOOD,
    EVENT_DARK_CREATIONS, // P 2
    EVENT_CORR_OLD_GOD, // P 2
    EVENT_SUMMON_TENTACLES, // Heroic

    /***** MOBS *****/
    // Portals
    EVENT_SUMMON_FLAME_LORD,
    EVENT_SUMMON_SHADOW_LORD,
    // Darkened Creations + Blood of the Old God
    EVENT_DEBILITATING_BEAM,
    EVENT_FIXATE,
    EVENT_MELEE_INCR_CORRUPTION,
    // Corrupting Adherent
    EVENT_DEPRAVITY,
    EVENT_CORRUPTING_CRASH
};

enum Phases
{
    PHASE_NULL    = 0,
    PHASE_ONE,
    PHASE_TWO
};

enum Npc
{
    NPC_CORRUPTING_ADHERENT  = 43622,
    NPC_SHADOW_PORTAL        = 47019,
    NPC_FIRE_PORTAL          = 47020,
    NPC_SHADOW_LORD          = 47016, // Heroic phase : 248,982 10H - 746,946 25H
    NPC_FIRE_LORD            = 47017, // Heroic phase : 207,485 10H - 746,946 25H
    NPC_BLAZE                = 43585, // Blaze from Flaming Destruction.
    NPC_SPIKED_TENTACLE      = 50264, // Heroic phase : 4,149,700 HP All mode - P2 spawns. Only melee -> target.
    NPC_BLOOD_OF_THE_OLD_GOD = 43707, // P2 spawns.
    NPC_DARKENED_CREATION    = 44045, // P2 spawns.
    NPC_CHOGALL_COG_TRIGGER  = 43999, // Called Corruption. Trigger spawned in middle of room.

    GO_CHOGALL_FLOOR = 205898         // Floor Chogall -> Sinestra
};

const Position TentacleLocations[4] = // Spiked tentacle summonings for last phase.
{
    {-1187.333f, -790.100f, 835.041f, 0.00f},
    {-1180.054f, -814.735f, 835.038f, 0.00f},
    {-1145.520f, -812.276f, 835.027f, 0.00f},
    {-1142.907f, -789.644f, 835.027f, 0.00f}
};

/*
NOTES:

1. CORRUPTION:

    Corruption bar is scripted separately. TODO - For each point of Corruption they have, players suffer 3% additional damage from Cho'gall's Corruption of the Old God ability.
    
    Corruption causes and amounts:

        BAR:
        Accelerated Corruption - 2 per second - 81943 !!
        Corruption - Dark Sickness - 5 corr, 81831!!
        Corruption - Malformation - aura player veh id (82125) + malformation cast 46598 on player!!

        BOSS / MOBS:
        Sprayed Corruption - 5 per 2 seconds.
        Spilled Blood of the Old God - +5 per second of standing in it.
        Congealed Blood of the Old God melee - 10 per hit.
        Corrupting Crash - 10
        Depravity - 10
        Debilitating Beam - 2 per second.
        Corruption of the Old God - 1 per tick. 

2. PHASES:
    
    Flame / Shadow Orders rotation is made through different time of periodic trigger application. Phase 2 hits -> triggers are removed.
*/

// 43324
class boss_chogall : public CreatureScript
{
public:
    boss_chogall() : CreatureScript("boss_chogall") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_chogallAI(creature);
    }

    struct boss_chogallAI : public BossAI
    {
        boss_chogallAI(Creature* creature) : BossAI(creature, DATA_CHOGALL), summons(me)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        SummonList summons;
        Phases phase;
        uint32 m_uiPowerTimer;
        uint32 m_berserkTimer;
        bool phaseTwo, movedMid;

        void Reset()
        {
            phase = PHASE_NULL;
            summons.DespawnAll();
            phaseTwo = false;
            movedMid = false;
            if (instance)
                instance->SetBossState(DATA_CHOGALL, NOT_STARTED);
            me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_FESTERIN_BLOOD, true);

            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            applyCorruption();

            Talk(SAY_AGGRO);
            EnterPhaseOne();

            if (instance)
            {
                instance->SetBossState(DATA_CHOGALL, IN_PROGRESS);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add
            }

            m_uiPowerTimer = 1000; // Refresh power.
            m_berserkTimer = 600000; // 10 min enrage.

            _EnterCombat();
        }

        void initEvents(bool phaseOne = true)
        {
            events.Reset();

            if(phaseOne)
            {
                events.ScheduleEvent(EVENT_CONVERSION, 10000, PHASE_ONE); // then 30-35 sec.
                events.ScheduleEvent(EVENT_FLAME_ORDERS, 5000, PHASE_ONE); // uses normal spell and adds trigger aura. 10 sec this->flaming.
                events.ScheduleEvent(EVENT_SHADOW_ORDERS, 15000, PHASE_ONE); // uses normal spell and adds trigger aura. 9 sec this->empowered.
                events.ScheduleEvent(EVENT_FURY_OF_CHOGALL, 21000, PHASE_ONE); // then 45-49 sec.
                events.ScheduleEvent(EVENT_SUMMON_ADHERENT, 92000, PHASE_ONE); // then 90 sec. Need distinct on heroic to summon 2 at a time.
                events.ScheduleEvent(EVENT_FESTER_BLOOD, 132000, PHASE_ONE); // 40 sec after adherent is summoned.
            }else
            {
                events.ScheduleEvent(EVENT_FURY_OF_CHOGALL, 7000, PHASE_TWO); // then 45-49 sec.
                events.ScheduleEvent(EVENT_DARK_CREATIONS, 30000, PHASE_TWO); // then 30 sec.
                events.ScheduleEvent(EVENT_CORR_OLD_GOD, 1000, PHASE_TWO); // Apply to trigger.

                if(IsHeroic())
                    events.ScheduleEvent(EVENT_SUMMON_TENTACLES, 2000, PHASE_TWO);
            }
        }

        void EnterEvadeMode()
        {
            Reset();
            removeCorruption();
            Talk(SAY_EVADE);
            me->GetMotionMaster()->MoveTargetedHome();

            if (Creature* trigger = me->FindNearestCreature(NPC_CHOGALL_COG_TRIGGER, 200.0f, true))
                if(trigger->HasAura(SPELL_CORR_OLD_GOD))
                    trigger->RemoveAurasDueToSpell(SPELL_CORR_OLD_GOD);

            if (instance)
            {
                instance->SetBossState(DATA_CHOGALL, FAIL);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            _EnterEvadeMode();
        }

        void EnterPhaseOne()
        {
            phase = PHASE_ONE;
            events.SetPhase(PHASE_ONE);
            initEvents(true);
        }

        void EnterPhaseTwo()
        {
            Talk(SAY_COG);
            Talk(SAY_PHASE2);
            phase = PHASE_TWO;
            events.SetPhase(PHASE_TWO);
            initEvents(false);
            if (me->HasAura(SPELL_F_O_PERIODIC) && me->HasAura(SPELL_S_O_PERIODIC)) // Remove P1 Orders triggers.
            {
                me->RemoveAurasDueToSpell(SPELL_F_O_PERIODIC);
                me->RemoveAurasDueToSpell(SPELL_S_O_PERIODIC);
            }
            // DoCast(me, SPELL_CONSUME_BLOOD);
        }

        void applyCorruption()
        {
            if(instance)
               instance->DoAddAuraOnPlayers(SPELL_CORRUPTION_AURA);
        }

        void removeCorruption()
        {
            if(instance)
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_CORRUPTION_AURA);
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
            summon->setActive(true);

            summon->AI()->DoZoneInCombat();
        }

        void JustDied(Unit* /*killer*/)
        {
            if(!IsHeroic())
                Talk(SAY_DEATH);
            else
                Talk(SAY_DEATH_H);
            removeCorruption();
            summons.DespawnAll();

            if (instance)
            {
                instance->SetBossState(DATA_CHOGALL, DONE);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            if(Creature* trigger = me->FindNearestCreature(NPC_CHOGALL_COG_TRIGGER, 200.0f, true))
                trigger->DisappearAndDie();

            if (me->GetMap()->IsHeroic())
                if (GameObject* sinestraDoor = me->FindNearestGameObject(GO_CHOGALL_FLOOR, 200.0f))
                    sinestraDoor->SetGoState(GO_STATE_ACTIVE);

            _JustDied();
        }

        void KilledUnit(Unit* /*victim*/)
        {
            Talk(RAND(SAY_KILL_1, SAY_KILL_2, SAY_KILL_3, SAY_KILL_4));
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING) || !phase)
                return;

            if (m_uiPowerTimer <= diff)
            {
               instance->NormaliseAltPower();
            }
            else m_uiPowerTimer -= diff;

            if (m_berserkTimer <= diff)
            {
               DoCast(me, SPELL_BERSERK);
               m_berserkTimer = 600000;
            }
            else m_berserkTimer -= diff;

            if (Creature* firelord = me->FindNearestCreature(NPC_FIRE_LORD, 5.0f, true)) // Flame Lord near.
            {
                DoCast(me, SPELL_ABSORB_FIRE);
                firelord->DespawnOrUnsummon();
            }

            if (Creature* shadowlord = me->FindNearestCreature(NPC_SHADOW_LORD, 5.0f, true)) // Shadow Lord near.
            {
                DoCast(me, SPELL_ABSORB_SHADOW);
                shadowlord->DespawnOrUnsummon();
            }

            if (me->HealthBelowPct(26) && !phaseTwo) // Switch phase.
            {
                EnterPhaseTwo();
                phaseTwo = true;
            }

            if (me->HealthBelowPct(3) && IsHeroic()&& !movedMid) // Heroic move mid before platform breaks.
            {
                movedMid = true;
                events.CancelEvent(EVENT_FURY_OF_CHOGALL);
                events.CancelEvent(EVENT_DARK_CREATIONS);
                events.CancelEvent(EVENT_CORR_OLD_GOD);
                events.CancelEvent(EVENT_SUMMON_TENTACLES);
                me->GetMotionMaster()->MovePoint(1, -1162.254f, -798.731f, 835.844f);
            }

            events.Update(diff);

            if (phase == PHASE_ONE) // First phase
            {
                std::list<Unit*> targets;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CONVERSION:
                            Talk(RAND(SAY_CONV_1, SAY_CONV_2, SAY_CONV_3));
                            SelectTargetList(targets, NonTankTargetSelector(me), RAID_MODE(1, 2, 2, 4), SELECT_TARGET_RANDOM);
                            if (!targets.empty())
                                for (std::list<Unit*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                                    (*itr)->CastSpell(me, SPELL_WORSHIPPING, true);
                            events.ScheduleEvent(EVENT_CONVERSION, urand(30000, 35000), PHASE_ONE);
                            break;

                        case EVENT_FLAME_ORDERS:
                            DoCast(me, SPELL_FLAME_ORDERS); // just once.
                            DoCast(me, SPELL_F_O_PERIODIC); // every 50 sec.
                            break;

                        case EVENT_SHADOW_ORDERS:
                            DoCast(me, SPELL_SHADOW_ORDERS); // just once.
                            DoCast(me, SPELL_S_O_PERIODIC);  // every 50 sec.
                            break;

                        case EVENT_FURY_OF_CHOGALL:
                            DoCastVictim(SPELL_FURY_OF_CHOGALL);
                            events.ScheduleEvent(EVENT_FURY_OF_CHOGALL, urand(45000, 49000), PHASE_ONE);
                            break;

                        case EVENT_SUMMON_ADHERENT:
                            Talk(SAY_ADHERENT);
                            Talk(RAND(SAY_ADHER_1, SAY_ADHER_2, SAY_ADHER_3));
                            DoCast(me, SPELL_SUM_ADHER_SE); // Needs script.
                            events.ScheduleEvent(EVENT_SUMMON_ADHERENT, 90000, PHASE_ONE);
                            break;

                        case EVENT_FESTER_BLOOD:
                            DoCast(me, SPELL_FESTER_BLOOD); // Needs script.
                            events.ScheduleEvent(EVENT_FESTER_BLOOD, 130000, PHASE_ONE);
                            break;
                    }
                }
            }
            else if (phase == PHASE_TWO) // Second phase
            {
                std::list<Unit*> targets;

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_FURY_OF_CHOGALL:
                            DoCastVictim(SPELL_FURY_OF_CHOGALL);
                            events.ScheduleEvent(EVENT_FURY_OF_CHOGALL, urand(45000, 49000), PHASE_TWO);
                            break;

                        case EVENT_DARK_CREATIONS:
                            Talk(RAND(SAY_DARKCR_1, SAY_DARKCR_2, SAY_DARKCR_3, SAY_DARKCR_4, SAY_DARKCR_5));
                            DoCast(me, SPELL_DARK_CREAT_VIS);
                            for (int i = 0; i < 4; i++)
                                me->SummonCreature(NPC_DARKENED_CREATION, TentacleLocations[i].GetPositionX(), TentacleLocations[i].GetPositionY(), TentacleLocations[i].GetPositionZ(), TEMPSUMMON_CORPSE_DESPAWN);
                            events.ScheduleEvent(EVENT_DARK_CREATIONS, urand(28000, 34000), PHASE_TWO);
                            break;

                        case EVENT_CORR_OLD_GOD: // Needs script.
                            if(Creature* trigger = me->FindNearestCreature(NPC_CHOGALL_COG_TRIGGER, 200.0f, true))
                                trigger->CastSpell(trigger, SPELL_CORR_OLD_GOD, true);
                            break;

                        case EVENT_SUMMON_TENTACLES:
                            if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
                                me->SummonCreature(NPC_SPIKED_TENTACLE, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0.0f, TEMPSUMMON_MANUAL_DESPAWN);
                            events.ScheduleEvent(EVENT_SUMMON_TENTACLES, urand(30000, 35000), PHASE_TWO);
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
** NPC Blaze (43585) - Flaming Destruction.
**********************/
class npc_blaze_chogall : public CreatureScript 
{
public:

    npc_blaze_chogall() : CreatureScript("npc_blaze_chogall") { }

    CreatureAI* GetAI(Creature* creature) const 
    {
        return new npc_blaze_chogallAI(creature);
    }

    struct npc_blaze_chogallAI : public ScriptedAI 
    {

        npc_blaze_chogallAI(Creature * creature) : ScriptedAI(creature) 
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->AddAura(SPELL_BLAZE_PERIODIC, me);
            me->DespawnOrUnsummon(25000);
        }

        void UpdateAI(uint32 /*diff*/) { }
    };
};

/*********************
** NPC Flame Portal (47020) - Flame's Orders.
**********************/
class npc_fire_portal : public CreatureScript 
{
public:

    npc_fire_portal() : CreatureScript("npc_fire_portal") { }

    CreatureAI* GetAI(Creature* creature) const 
    {
        return new npc_fire_portalAI(creature);
    }

    struct npc_fire_portalAI : public ScriptedAI 
    {

        npc_fire_portalAI(Creature * creature) : ScriptedAI(creature) 
        {
            instance = creature->GetInstanceScript();
            creature->CastSpell(creature, SPELL_VIS_FLAMEP, true);
        }

        InstanceScript* instance;
        EventMap events;

        void JustSummoned(Creature* summon)
        {
            summon->AI()->DoZoneInCombat();

            if(summon->GetEntry() == NPC_FIRE_LORD)
            {
                summon->SetSpeed(MOVE_WALK, 0.75f, true);
                summon->SetSpeed(MOVE_RUN, 0.75f, true);
                summon->SetReactState(REACT_PASSIVE);
                if(Unit* chogall = summon->FindNearestCreature(NPC_CHOGALL, 200.0f, true))
                    summon->GetMotionMaster()->MoveChase(chogall);
            }
        }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            events.ScheduleEvent(EVENT_SUMMON_FLAME_LORD, 5500);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SUMMON_FLAME_LORD:
                    DoCast(me, SPELL_FO_SUMMON_1);
                    me->DespawnOrUnsummon();
                    return;
                }
            }
        }
    };
};

/*********************
** NPC Shadow Portal (47019) - Shadow's Orders.
**********************/
class npc_shadow_portal : public CreatureScript 
{
public:

    npc_shadow_portal() : CreatureScript("npc_shadow_portal") { }

    CreatureAI* GetAI(Creature* creature) const 
    {
        return new npc_shadow_portalAI(creature);
    }

    struct npc_shadow_portalAI : public ScriptedAI 
    {

        npc_shadow_portalAI(Creature * creature) : ScriptedAI(creature) 
        {
            instance = creature->GetInstanceScript();
            creature->CastSpell(creature, SPELL_VIS_SHADOWP, true);
        }

        InstanceScript* instance;
        EventMap events;

        void JustSummoned(Creature* summon)
        {
            summon->AI()->DoZoneInCombat();

            if(summon->GetEntry() == NPC_SHADOW_LORD)
            {
                summon->SetSpeed(MOVE_WALK, 0.75f, true);
                summon->SetSpeed(MOVE_RUN, 0.75f, true);
                summon->SetReactState(REACT_PASSIVE);
                if(Unit* chogall = summon->FindNearestCreature(NPC_CHOGALL, 200.0f, true))
                    summon->GetMotionMaster()->MoveChase(chogall);
            }
        }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            events.ScheduleEvent(EVENT_SUMMON_SHADOW_LORD, 5500);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SUMMON_SHADOW_LORD:
                    DoCast(me, SPELL_SO_SUMMON_1);
                    me->DespawnOrUnsummon();
                    return;
                }
            }
        }
    };
};

/*********************
** NPC Darkened Creation (44045) - P2.
**********************/
class npc_darkened_creation : public CreatureScript 
{
public:

    npc_darkened_creation() : CreatureScript("npc_darkened_creation") { }

    CreatureAI* GetAI(Creature* creature) const 
    {
        return new npc_darkened_creationAI(creature);
    }

    struct npc_darkened_creationAI : public ScriptedAI 
    {

        npc_darkened_creationAI(Creature * creature) : ScriptedAI(creature) 
        {
            instance = creature->GetInstanceScript();
            creature->CastSpell(creature, SPELL_TENTACLE_VIS, true);
        }

        InstanceScript* instance;
        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            events.ScheduleEvent(EVENT_DEBILITATING_BEAM, 1000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_DEBILITATING_BEAM:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                        DoCast(target, SPELL_DEBILIT_BEAM);
                    events.ScheduleEvent(EVENT_DEBILITATING_BEAM, 10500);
                    break;
                }
            }
        }
    };
};

/*********************
** NPC Blood of the Old God (43707) - P2.
**********************/
class npc_blood_old_god : public CreatureScript 
{
public:

    npc_blood_old_god() : CreatureScript("npc_blood_old_god") { }

    CreatureAI* GetAI(Creature* creature) const 
    {
        return new npc_blood_old_godAI(creature);
    }

    struct npc_blood_old_godAI : public ScriptedAI 
    {

        npc_blood_old_godAI(Creature * creature) : ScriptedAI(creature) 
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
            events.ScheduleEvent(EVENT_FIXATE, 100);
            events.ScheduleEvent(EVENT_MELEE_INCR_CORRUPTION, 2100);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            if (!me->FindNearestCreature(NPC_CHOGALL, 200.0f, true))
                me->DespawnOrUnsummon(); // Is dead.

            if(Unit* chogall = me->FindNearestCreature(NPC_CHOGALL, 200.0f, true))
                if(!chogall->IsInCombat()) // evaded.
                    me->DespawnOrUnsummon();

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_FIXATE:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                    {
                        me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
                        me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, true);
                        me->SetSpeed(MOVE_WALK, 0.85f, true);
                        me->SetSpeed(MOVE_RUN, 0.85f, true);
                        AttackStart(target);
                        me->AddThreat(target, 5000000.0f);
                    }
                    break;

                    case EVENT_MELEE_INCR_CORRUPTION:
                    if (Unit* target = me->GetVictim())
                        if (me->IsWithinMeleeRange(target))
                            target->SetPower(POWER_ALTERNATE_POWER, target->GetPower(POWER_ALTERNATE_POWER) + 10);
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

/*********************
** NPC Corrupting Adherent (43622).
**********************/
class npc_corrupting_adherent : public CreatureScript 
{
public:

    npc_corrupting_adherent() : CreatureScript("npc_corrupting_adherent") { }

    CreatureAI* GetAI(Creature* creature) const 
    {
        return new npc_corrupting_adherentAI(creature);
    }

    struct npc_corrupting_adherentAI : public ScriptedAI 
    {

        npc_corrupting_adherentAI(Creature * creature) : ScriptedAI(creature) 
        {
            instance = creature->GetInstanceScript();
            dead = false;
        }

        InstanceScript* instance;
        EventMap events;
        bool dead;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            events.ScheduleEvent(EVENT_DEPRAVITY, urand(3000, 9000));
            events.ScheduleEvent(EVENT_CORRUPTING_CRASH, urand(11000, 17000));
        }

        void UpdateAI(uint32 diff)
        {
            if (me->HealthBelowPct(6) && !dead) // Make them look dead.
            {
                // Stop Fighting - Despawn and summon is made from spell script.
                me->RemoveAllAuras();
                DoCast(me, 42716); // root.
                DoCast(me, SPELL_SPILLED_VISUAL);
                DoCast(me, SPELL_SPILLED_POOL);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetFlag(UNIT_NPC_EMOTESTATE, EMOTE_STATE_DEAD);
                me->SetUInt32Value(UNIT_FIELD_BYTES_1, UNIT_STAND_STATE_DEAD);
                me->SetReactState(REACT_PASSIVE);
                dead = true;
            }

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_DEPRAVITY:
                    DoCast(me, SPELL_DEPRAVITY);
                    events.ScheduleEvent(EVENT_DEPRAVITY, (Is25ManRaid() ? 12000 : 6000));
                    break;

                    case EVENT_CORRUPTING_CRASH:                    
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                        DoCast(target, SPELL_CORRUPT_CRASH);
                    events.ScheduleEvent(EVENT_CORRUPTING_CRASH, urand(9500, 16500));
                    break;
                }
            }

            if(!dead)
            DoMeleeAttackIfReady();
        }
    };
};

/* SPELL SCRIPTS */

/*** BOSS ***/

class spell_summon_adherents: public SpellScriptLoader // 81628
{
public:
    spell_summon_adherents () :
            SpellScriptLoader("spell_summon_adherents") { }

    class spell_summon_adherentsSpellScript: public SpellScript
    {
        PrepareSpellScript(spell_summon_adherentsSpellScript);

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
            if (GetCaster()->GetMap()->IsHeroic() && GetCaster()->GetMap()->Is25ManRaid()) // Summon 2
            {
                GetCaster()->SummonCreature(NPC_CORRUPTING_ADHERENT, -1233.778f, -799.120f, 835.842f, 0.069f, TEMPSUMMON_MANUAL_DESPAWN);
                GetCaster()->SummonCreature(NPC_CORRUPTING_ADHERENT, -1093.083f, -798.656f, 835.842f, 3.226f, TEMPSUMMON_MANUAL_DESPAWN);
            }
            else // Summon 1
            {
                uint32 position = urand(1,2); // one of the two places
                switch(position)
                {
                    case 1:
                    GetCaster()->SummonCreature(NPC_CORRUPTING_ADHERENT, -1233.778f, -799.120f, 835.842f, 0.069f, TEMPSUMMON_MANUAL_DESPAWN);
                    break;
                    case 2:
                    GetCaster()->SummonCreature(NPC_CORRUPTING_ADHERENT, -1093.083f, -798.656f, 835.842f, 3.226f, TEMPSUMMON_MANUAL_DESPAWN);
                    break;
                }
            }
        }

        void Register ()
        {
            OnEffectHitTarget += SpellEffectFn(spell_summon_adherentsSpellScript::EffectScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript * GetSpellScript () const
    {
        return new spell_summon_adherentsSpellScript();
    }
};

class spell_fester_blood: public SpellScriptLoader // 82337
{
public:
    spell_fester_blood () :
            SpellScriptLoader("spell_fester_blood") { }

    class spell_fester_bloodSpellScript: public SpellScript
    {
        PrepareSpellScript(spell_fester_bloodSpellScript);

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
            std::list<Creature*> adherents;
            GetCaster()->GetCreatureListWithEntryInGrid(adherents, NPC_CORRUPTING_ADHERENT, 300.0f);
            for (std::list<Creature*>::iterator itr = adherents.begin(); itr != adherents.end(); ++itr)
                if (!(*itr)->HealthBelowPct(6)) // they are alive!
                    (*itr)->CastSpell(*itr, SPELL_FESTERIN_BLOOD, true);
                else // they are dead! - summon 5 oozes for each.
                {
                    for (int8 i = 0; i < 5; i++)
                        (*itr)->SummonCreature(NPC_BLOOD_OF_THE_OLD_GOD, (*itr)->GetPositionX(), (*itr)->GetPositionY(), (*itr)->GetPositionZ(), (*itr)->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN);
                }
        }

        void Register ()
        {
            OnEffectHitTarget += SpellEffectFn(spell_fester_bloodSpellScript::EffectScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript * GetSpellScript () const
    {
        return new spell_fester_bloodSpellScript();
    }
};

/*** MOBS ***/

class spell_depravity: public SpellScriptLoader // 81713
{
public:
    spell_depravity () :
            SpellScriptLoader("spell_depravity") { }

    class spell_depravitySpellScript: public SpellScript
    {
        PrepareSpellScript(spell_depravitySpellScript);

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
            if (!GetHitUnit())
                return;

            GetHitUnit()->SetPower(POWER_ALTERNATE_POWER, GetHitUnit()->GetPower(POWER_ALTERNATE_POWER) + 10);
        }

        void Register ()
        {
            OnEffectHitTarget += SpellEffectFn(spell_depravitySpellScript::EffectScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript * GetSpellScript () const
    {
        return new spell_depravitySpellScript();
    }
};

class spell_corrupting_crash: public SpellScriptLoader // 81689
{
public:
    spell_corrupting_crash () :
            SpellScriptLoader("spell_corrupting_crash") { }

    class spell_corrupting_crashSpellScript: public SpellScript
    {
        PrepareSpellScript(spell_corrupting_crashSpellScript);

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
            if (!GetHitUnit())
                return;

            GetHitUnit()->SetPower(POWER_ALTERNATE_POWER, GetHitUnit()->GetPower(POWER_ALTERNATE_POWER) + 10);
        }

        void Register ()
        {
            OnEffectHitTarget += SpellEffectFn(spell_corrupting_crashSpellScript::EffectScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript * GetSpellScript () const
    {
        return new spell_corrupting_crashSpellScript();
    }
};

class spell_sprayed_corruption: public SpellScriptLoader // 82919
{
public:
    spell_sprayed_corruption () :
            SpellScriptLoader("spell_sprayed_corruption") { }

    class spell_sprayed_corruptionSpellScript: public SpellScript
    {
        PrepareSpellScript(spell_sprayed_corruptionSpellScript);

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
            if (!GetHitUnit())
                return;

            GetHitUnit()->SetPower(POWER_ALTERNATE_POWER, GetHitUnit()->GetPower(POWER_ALTERNATE_POWER) + 5);
        }

        void Register ()
        {
            OnEffectHitTarget += SpellEffectFn(spell_sprayed_corruptionSpellScript::EffectScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript * GetSpellScript () const
    {
        return new spell_sprayed_corruptionSpellScript();
    }
};

class spell_spilled_blood_of_the_old_god: public SpellScriptLoader // 81761
{
public:
    spell_spilled_blood_of_the_old_god () :
            SpellScriptLoader("spell_spilled_blood_of_the_old_god") { }

    class spell_spilled_blood_of_the_old_godSpellScript: public SpellScript
    {
        PrepareSpellScript(spell_spilled_blood_of_the_old_godSpellScript);

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
            if (!GetHitUnit())
                return;

            GetHitUnit()->SetPower(POWER_ALTERNATE_POWER, GetHitUnit()->GetPower(POWER_ALTERNATE_POWER) + 5);
        }

        void Register ()
        {
            OnEffectHitTarget += SpellEffectFn(spell_spilled_blood_of_the_old_godSpellScript::EffectScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript * GetSpellScript () const
    {
        return new spell_spilled_blood_of_the_old_godSpellScript();
    }
};

class spell_debilitating_beam : public SpellScriptLoader // 82411
{
    public:
        spell_debilitating_beam() : SpellScriptLoader("spell_debilitating_beam") { }

        class spell_debilitating_beam_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_debilitating_beam_AuraScript);

            void PeriodicTick(AuraEffect const* /*aurEff*/)
            {
                if (!GetTarget())
                    return;

                GetTarget()->SetPower(POWER_ALTERNATE_POWER, GetTarget()->GetPower(POWER_ALTERNATE_POWER) + 2);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_debilitating_beam_AuraScript::PeriodicTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_debilitating_beam_AuraScript();
        }
};

class spell_corruption_old_god: public SpellScriptLoader // 82363
{
public:
    spell_corruption_old_god () :
            SpellScriptLoader("spell_corruption_old_god") { }

    class spell_corruption_old_godSpellScript: public SpellScript
    {
        PrepareSpellScript(spell_corruption_old_godSpellScript);

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

        void CalculateDamage(SpellEffIndex /*effIndex*/)
        {
            if (!GetHitUnit())
                return;

            if (GetHitUnit()->GetPower(POWER_ALTERNATE_POWER) > 0)
                SetHitDamage(int32(GetHitDamage() + (((GetHitDamage() / 100) * 3) * GetHitUnit()->GetPower(POWER_ALTERNATE_POWER)))); // Damage plus 3% for each 1 Corruption.
        }

        void EffectScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (!GetHitUnit())
                return;

            GetHitUnit()->SetPower(POWER_ALTERNATE_POWER, GetHitUnit()->GetPower(POWER_ALTERNATE_POWER) + 1);
        }

        void Register ()
        {
            OnEffectHitTarget += SpellEffectFn(spell_corruption_old_godSpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            OnEffectHitTarget += SpellEffectFn(spell_corruption_old_godSpellScript::EffectScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript * GetSpellScript () const
    {
        return new spell_corruption_old_godSpellScript();
    }
};

/*** MISC - CORRUPTION BAR ***/

class spell_corruption_accelerated: public SpellScriptLoader // 81943
{
public:
    spell_corruption_accelerated () :
            SpellScriptLoader("spell_corruption_accelerated") { }

    class spell_corruption_acceleratedSpellScript: public SpellScript
    {
        PrepareSpellScript(spell_corruption_acceleratedSpellScript);

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
            GetCaster()->SetPower(POWER_ALTERNATE_POWER, GetCaster()->GetPower(POWER_ALTERNATE_POWER) + 2);
        }

        void Register ()
        {
            OnEffectHitTarget += SpellEffectFn(spell_corruption_acceleratedSpellScript::EffectScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript * GetSpellScript () const
    {
        return new spell_corruption_acceleratedSpellScript();
    }
};

class spell_corruption_sickness: public SpellScriptLoader // 81831
{
public:
    spell_corruption_sickness () :
            SpellScriptLoader("spell_corruption_sickness") { }

    class spell_corruption_sicknessSpellScript: public SpellScript
    {
        PrepareSpellScript(spell_corruption_sicknessSpellScript);

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
            GetCaster()->SetPower(POWER_ALTERNATE_POWER, GetCaster()->GetPower(POWER_ALTERNATE_POWER) + 5);
        }

        void Register ()
        {
            OnEffectHitTarget += SpellEffectFn(spell_corruption_sicknessSpellScript::EffectScriptEffect, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript * GetSpellScript () const
    {
        return new spell_corruption_sicknessSpellScript();
    }
};

/*********************
** NPC Malformation (43888) - 75% Corruption.
**********************/
class npc_malformation_chogall : public CreatureScript 
{
public:

    npc_malformation_chogall() : CreatureScript("npc_malformation_chogall") { }

    CreatureAI* GetAI(Creature* creature) const 
    {
        return new npc_malformation_chogallAI(creature);
    }

    struct npc_malformation_chogallAI : public ScriptedAI 
    {

        npc_malformation_chogallAI(Creature * creature) : ScriptedAI(creature) 
        {
            instance = creature->GetInstanceScript();
            boltTimer = 3000;
        }

        InstanceScript* instance;
        uint32 boltTimer;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        void UpdateAI(uint32 diff) 
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (boltTimer <= diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                    DoCast(target, SPELL_MALFORMATION_SHADOWBOLT);
                boltTimer = urand(7000, 14000);
            }
            else boltTimer -= diff;
        }
    };
};

void AddSC_boss_chogall()
{
    new boss_chogall();
    new npc_blaze_chogall();
    new npc_fire_portal();
    new npc_shadow_portal();
    new npc_darkened_creation();
    new npc_blood_old_god();
    new npc_corrupting_adherent();
    new spell_summon_adherents();
    new spell_fester_blood();
    new spell_depravity();
    new spell_corrupting_crash();
    new spell_sprayed_corruption();
    new spell_spilled_blood_of_the_old_god();
    new spell_debilitating_beam();
    new spell_corruption_old_god();
    new spell_corruption_accelerated();
    new spell_corruption_sickness();
    new npc_malformation_chogall();
}