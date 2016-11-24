/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

/*Copyright (C) Arkania Project 2014.
* 
* Script 90% done. TODO:
* 
* - Insert yells and texts.
* - Complete rhyolith for other 10 ppl modes
* - Complete loot and achievement
* - Fix crash on killing rhyolith(dependet on vehicle)
* This file is NOT intended as open-source software. You may NOT redistribute it or modify it.
*/

/* ==- Notes on Bar -==
For this fight, your UI displays a Direction Gauge. The default UI shows a horizontal energy bar that fills and depletes. Some addons display it as a percentage bar. 
The value indicated/displayed by the bar shows where Rhyolith is currently steering:

    the closer to the left (or 0%), the more Rhyolith is steering left;
    the median value (or 50%) represents Rhyolith moving in a straight line;
    the closer to the right (or 100%), the more Rhyolith is steering right.

When attacking the left foot to make Rhyolith turn left, or the right foot to make him turn right, there seems to be a delay (about 1 second) before Rhyolith starts ch. direction.
It looks as if Rhyolith has some inertia. When the damage done to both his feet is no longer unequal, the Direction Gauge will have a tendency to go back to the middle.
*/

// Orientation info : 
// Q : Where is + and where is -, to right or left? 
// A : Left is +, right is -. ( Circle: lowest orientation 0.00f minus something = to right = 6.28f, highest orientation).

#include "ScriptPCH.h"
#include "WorldPacket.h"
#include "firelands.h"
#include "SpellAuraEffects.h"  
#include "Vehicle.h"
#include "Unit.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
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

enum KarEvents
{
    EVENT_MOVE_NEXT_POS = 1,
};

enum KarSpells
{
    SUMMON_ELEMENTALS = 99601,
};

class npc_kar_the_everburning : public CreatureScript
{
public:
    npc_kar_the_everburning() : CreatureScript("npc_kar_the_everburning") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_kar_the_everburningAI(creature);
    }

    struct npc_kar_the_everburningAI : public ScriptedAI
    {
        npc_kar_the_everburningAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            phase = 0;
            timerElem = 1700;
            me->SetReactState(REACT_PASSIVE);
        }

        EventMap events;
        uint8 phase;
        uint32 timerMove, timerElem;
        InstanceScript* instance;

        void Reset() { }

        void EnterCombat(Unit* /*who*/) { }

        void UpdateAI(uint32 diff)
        {
            if (phase == 2 && UpdateVictim())
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_MOVE_NEXT_POS:
                        break;
                    }
                }
            }

            if (phase == 0)
            {
                if (me->FindNearestPlayer(5.0, true))
                {
                    phase = 1;
                    timerMove = 7000;
                }

                if (timerElem <= diff)
                {
                    me->CastSpell(me->GetPositionX() + irand(0, 10) + irand(-10, 0), me->GetPositionY() + irand(0, 10) + irand(-10, 0), me->GetPositionZ(), SUMMON_ELEMENTALS, true);
                    timerElem = 1200;
                }
                else timerElem -= diff;
            }

            if (phase == 1)
            {
                if (timerMove <= diff)
                {
                    phase = 2;
                    me->SetFacingTo(0.931584f);
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->SetHomePosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());
                    me->AI()->Reset();
                }
                else timerMove -= diff;
            }

            if (phase == 1)
                me->GetMotionMaster()->MovePoint(0, -316.224f, -435.897f, 102.951f);

            DoMeleeAttackIfReady();
        }
    };
};

class npc_unstable_pyrelord : public CreatureScript
{
public:
    npc_unstable_pyrelord() : CreatureScript("npc_unstable_pyrelord") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_unstable_pyrelordAI (creature);
    }

    struct npc_unstable_pyrelordAI : public ScriptedAI
    {
        npc_unstable_pyrelordAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            start = false;
            falltimer = 5000;
        }

        bool start;
        uint32 falltimer;
        InstanceScript* instance;

        void Reset() { }

        void EnterCombat(Unit* /*who*/) { }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->SetReactState(REACT_AGGRESSIVE);
            start = true;
        }


        void UpdateAI(uint32 diff)
        {
            if (!start) return;

            if (falltimer <= diff)
            {
                me->GetMotionMaster()->MoveFall();
                falltimer = 5000;
            }
            else falltimer -= diff;

            if (!UpdateVictim())
                me->GetMotionMaster()->MovePoint(1,-167.431f,-307.385f,me->GetPositionZMinusOffset());

            if (!GetKar())
                me->DespawnOrUnsummon();

            if (UpdateVictim())
                DoMeleeAttackIfReady();
        }

        
        Creature* GetKar()
        {
            return me->FindNearestCreature(53616, 125.0f, true);
        }
    };
};

enum Yells
{
/*
    Lord Rhyolith yells: Augh - smooshy little pests, look what you've done!
    Lord Rhyolith yells: Broken. Mnngghhh... broken...
    Lord Rhyolith yells: Buuurrrnn!
    Lord Rhyolith yells: Eons I have slept undisturbed... Now this... Creatures of flesh, now you will BURN!
    Lord Rhyolith yells: Finished.
    Lord Rhyolith yells: Graaahh!
    Lord Rhyolith yells: Hah? Hruumph? Soft little fleshy-things? Here? Nuisances, nuisances!
    Lord Rhyolith yells: I'll crush you underfoot!
    Lord Rhyolith yells: Oh you little beasts...
    Lord Rhyolith yells: Oww now hey.
    Lord Rhyolith yells: Sear the flesh from their tiny frames.
    Lord Rhyolith yells: So soft!
    Lord Rhyolith yells: Squeak, little pest.
    Lord Rhyolith yells: Stomp now.
    Lord Rhyolith yells: Succumb to living flame.
    Lord Rhyolith yells: Uurrghh now you... you infuriate me!
*/

    YELL_AGGRO                             = 0,
    YELL_KILLED                            = 1,
    YELL_DIED                              = 2,
    YELL_PHASE2                            = 3
};

enum Spells
{
    /*** Boss spells ***/
    SPELL_ORIENTATION_BAR                       = 98226, // On self at beginning.

    SPELL_OBSIDIAN_ARMOR                        = 98632,
    SPELL_CONCUSSIVE_STOMP                      = 97282,  //link w/ volcanic birth 98010 makes vulcanoes in 15y.
    SPELL_DRINK_MAGMA                           = 98034,
    SPELL_MOLTEN_SPEW                           = 98043,
    SPELL_SUPERHEATED                           = 101304, //enrage 8/10 min.
    SPELL_IMMOLATION                            = 99846,
    SPELL_TURNING_FLAME                         = 98837,
    SPELL_UNLEASHED_FLAME                       = 100974, //only hc.
    SPELL_HEATED_VOLCANO                        = 98493,  //kill volcanoes, makes lava line and they despawn.
    SPELL_LAVA_LINE                             = 100650, //'line' of lava from crater after stepping on volcano.
    SPELL_THERMAL_IGNITION                      = 98135,  //summ fragment of rhyolith
    SPELL_THERMAL_IGNITION2                     = 98553,  //summ spark of rhyolith
    SPELL_VOLCANIC_BIRTH                        = 98045,  //summ volcanoes
    SPELL_LAVA_TUBE                             = 98265,

    /*** Minion spells ***/
    SPELL_FUSE                                  = 99875, // liq obsidian
    SPELL_MELTDOWN                              = 98646, // fragm of rhyolith
    SPELL_IMOLATION                             = 98597, // spark of rhyolith
    SPELL_INFERNAL_RAGE                         = 98596, // spark
    SPELL_ERUPTION                              = 98264, // volcano before erupt
    SPELL_ERRUPTION                             = 80800, // volcano erupt
    SPELL_MAGMA                                 = 98472, // periodic volcano cast on spawn
    SPELL_MAGMA_FLOW                            = 97225, // cosmetic lava
    SPELL_MOLTEN_ARMOR                          = 101157,// increase damage made by rhyolith, debuff on boss
    SPELL_LAVA_STRIKE                           = 98492,
    SPELL_SMOKE_VOLCAN                          = 97699,
    SPELL_VISUAL_VOLCAN                         = 98250,
    SPELL_VOLCAN_CHECK_ACTIVE                   = 98400,
    SPELL_LAVA_FLOW                             = 97230,
    SPELL_LAVA_FLOW_CHECK                       = 97225
};

enum Events
{
    /*** Rhyolith ***/
    EVENT_PHASE_1 = 1,
    EVENT_PHASE_2,
    EVENT_SUPERHEATED,
    
    // Phase 1
    EVENT_CONCUSSIVE_STOMP,
    EVENT_CONCUSSIVE_STOMP_VOLCAN,
    EVENT_THERMAL_IGNITION,
    EVENT_THERMAL_IGNITION2,
    
    // Phase 2
    EVENT_UNLEASHED_FLAME,
    EVENT_IMMOLATION,
    EVENT_CONCUSSIVE_STOMP2,

    /*** Volcano ***/
    EVENT_ERRUPTION_START,
    EVENT_ERRUPTION_END,
    EVENT_CRATER,
    EVENT_LAVA_STRIKE,
    
    /*** Crater ***/
    EVENT_ACTIVATE_CRATER,
    EVENT_LAVA_LINE,
    EVENT_LAVA_LINES_BLOW,
    EVENT_DESPAWN_CRATER,
    EVENT_CHECK_NEAR_PLAYER,
    EVENT_DESPAWN_LINE,
    
    /*** Spark of Rhyolith ***/
    EVENT_INFERNAL_RAGE,
    EVENT_IMOLATION,

    /*** Combat ***/
    EVENT_ZONE_COMBAT
};

enum Phases
{    
    PHASE_0       = 0,
    PHASE_1       = 1,
    PHASE_2       = 2
};

enum Misc
{
    MODEL_DEFAULT = 38414, 
    MODEL_PHASE2  = 38594
};

const Position CenterPlatform[1] =
{
    {-368.220f, -322.986f, 100.281f, 0}
};

// Speed
const float speedRateLow         = 0.2f;
const float speedRateNormal      = 1.0f;

// Timers

// phase 1
const int  timerConcussiveStomp  = 30000;
const int  timerSuperheated      = 10000;
const int  timerThermalIgnition  = 35000;
const int  timerThermalIgnition2 = 35000;

// phase 2
const int  timerUnleashedFlame   = urand(15000,20000);
const int  timerConcussiveStomp2 = urand(35000,45000);

// Spark of Rhyolith
const int timerInfernalRage      = 5000;

#define EMOTE_SUPERHEATED       "Lord Rhyolith grows impatient and becomes Superheated!"
#define EMOTE_VOLCANO           "Lord Rhyolith extinguishes a nearby volcano!"
#define EMOTE_MAGMA             "Lord Rhyolith reaches towards the magma beyond his platform!"
#define EMOTE_PHASE2            "Lord Rhyolith loses his Obsidian Armor and is now exposed!"

class boss_lord_rhyolith : public CreatureScript
{
    public:
        boss_lord_rhyolith() : CreatureScript("boss_lord_rhyolith") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_lord_rhyolithAI(creature);
        }
        
        struct boss_lord_rhyolithAI : public BossAI
        {
            boss_lord_rhyolithAI(Creature* creature) : BossAI(creature, DATA_LORD_RHYOLITH), vehicle(creature->GetVehicleKit()), summons(me)
            {
                instance = me->GetInstanceScript();
                LeftSet = false;
                RightSet = false;
                Initialize();
            }
 
            InstanceScript* instance;
            Vehicle* vehicle;
            Phases Phase;
            EventMap events;
            SummonList summons;

            bool phaseTwo, LeftSet, RightSet, lavaFlow, drinkMagma;

            void Initialize()
            {
                events.Reset();
                Phase = PHASE_0;
                phaseTwo = false;
                lavaFlow = false;
                drinkMagma = false;
            }

            void Reset()
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetDisplayId(MODEL_DEFAULT);
                me->SetReactState(REACT_PASSIVE);
                instance->SetBossState(DATA_LORD_RHYOLITH, NOT_STARTED);

                _Reset();
            }

            void RemoveEncounterAuras()
            {
                Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
                if (!PlayerList.isEmpty())
                    for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    {
                        if (i->GetSource()->HasAura(SPELL_ORIENTATION_BAR))
                            i->GetSource()->RemoveAura(SPELL_ORIENTATION_BAR);
                    }
            }

            void EnterCombat(Unit* /*who*/)
            {
                instance->NormaliseAltPower();
                Phase = PHASE_0;
                events.SetPhase(PHASE_0);

                DoCast(me, SPELL_ORIENTATION_BAR);

                me->SetSpeed(MOVE_RUN, speedRateLow);    

                Talk(YELL_AGGRO);            
                instance->SetBossState(DATA_LORD_RHYOLITH,IN_PROGRESS);

                Phase = PHASE_1;
                
                events.ScheduleEvent(EVENT_CONCUSSIVE_STOMP, 15000);
                events.ScheduleEvent(EVENT_THERMAL_IGNITION, 18000);    

                if (me->GetMap()->IsHeroic())
                    events.ScheduleEvent(EVENT_SUPERHEATED, 600000); // 10 min Enrage.
                else 
                    events.ScheduleEvent(EVENT_SUPERHEATED, 480000); // 8 min Enrage.

                if (GetLeftLeg())
                    GetLeftLeg()->AI()->DoZoneInCombat();

                if (GetRightLeg())
                    GetRightLeg()->AI()->DoZoneInCombat();

                events.ScheduleEvent(EVENT_ZONE_COMBAT, 1000);

                _EnterCombat();
            }

            void KilledUnit(Unit* /*who*/)
            {
                Talk(YELL_KILLED);
            }

            void JustDied(Unit* /*killer*/)
            {
                instance->SetBossState(DATA_LORD_RHYOLITH, DONE);
                
                Talk(YELL_DIED);
                summons.DespawnAll();

                if (GetLeftLeg())
                    GetLeftLeg()->DisappearAndDie();

                if (GetRightLeg())
                    GetRightLeg()->DisappearAndDie();

                _JustDied();                
            }

            void EnterEvadeMode()
            {
                DespawnCreatures(53585);

                RemoveEncounterAuras();

                me->SetSpeed(MOVE_RUN,speedRateNormal);

                instance->SetBossState(DATA_LORD_RHYOLITH, FAIL);

                me->GetMotionMaster()->MoveTargetedHome();

                if (GetLeftLeg())
                    GetLeftLeg()->AI()->EnterEvadeMode();

                if (GetRightLeg())
                    GetRightLeg()->AI()->EnterEvadeMode();

                _EnterEvadeMode();
            }

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);

                switch (summon->GetEntry())
                {
                    case NPC_RHYOLITH_VOLCANO:
                        summon->SetInCombatWithZone();
                        break;

                    case NPC_LIQUID_OBSIDIAN:
                        summon->SetReactState(REACT_PASSIVE);                      
                        break;

                    case NPC_RHYOLITH_CRATER:
                        summon->SetInCombatWithZone();
                        break;

                    case NPC_FRAGMENT_OF_RHYOLITH:                  
                        summon->AI()->DoZoneInCombat();
                        summon->AI()->DoCast(summon, SPELL_MELTDOWN);
                        break;

                    case NPC_SPARK_OF_RHYOLITH:
                        summon->SetReactState(REACT_AGGRESSIVE);                       
                        summon->AI()->DoZoneInCombat();
                        break;

                    default:
                        break;
                }
            }

            void DespawnCreatures(uint32 entry)
            {
                std::list<Creature*> creatures;
                   GetCreatureListWithEntryInGrid(creatures, me, entry, 1000.0f);

                if (creatures.empty())
                   return;

                for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                    (*iter)->DespawnOrUnsummon();
            }

            void SetPlayersInCombat(bool evade)
            {
                uint8 players = 0;
                Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
                if (!PlayerList.isEmpty())
                    for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                        if (Player *player = i->GetSource())
                            if (player->IsAlive() && player->GetDistance(me) <= 150.0f)
                            {
                                ++players;
                                player->SetInCombatWith(me->ToUnit());
                            }

                if (players == 0 && evade == true)
                    EnterEvadeMode();
            }

            void UpdateAI(uint32 diff)
            {
                if (!RightSet || !LeftSet)
                    SummonAndSetLegsInBoss();

                if (!me->HasAura(SPELL_OBSIDIAN_ARMOR) && Phase != PHASE_2)
                {
                    DoCast(me,SPELL_OBSIDIAN_ARMOR);
                    me->SetAuraStack(SPELL_OBSIDIAN_ARMOR, me, 80);
                }

                if (me->HasAura(SPELL_OBSIDIAN_ARMOR) && Phase != PHASE_2)
                {
                    if (GetLeftLeg() && GetLeftLeg()->IsAlive())
                    {
                        if (!GetLeftLeg()->HasAura(SPELL_OBSIDIAN_ARMOR))
                            GetLeftLeg()->CastSpell(GetLeftLeg(), SPELL_OBSIDIAN_ARMOR, true);
                        else if (GetLeftLeg()->GetAura(SPELL_OBSIDIAN_ARMOR)->GetStackAmount() != me->GetAura(SPELL_OBSIDIAN_ARMOR)->GetStackAmount())
                            GetLeftLeg()->SetAuraStack(SPELL_OBSIDIAN_ARMOR, GetLeftLeg(), me->GetAura(SPELL_OBSIDIAN_ARMOR)->GetStackAmount());
                    }
                    if (GetRightLeg() && GetRightLeg()->IsAlive())
                    {
                        if (!GetRightLeg()->HasAura(SPELL_OBSIDIAN_ARMOR))
                            GetRightLeg()->CastSpell(GetRightLeg(), SPELL_OBSIDIAN_ARMOR, true);
                        else if (GetRightLeg()->GetAura(SPELL_OBSIDIAN_ARMOR)->GetStackAmount() != me->GetAura(SPELL_OBSIDIAN_ARMOR)->GetStackAmount())
                            GetRightLeg()->SetAuraStack(SPELL_OBSIDIAN_ARMOR, GetRightLeg(), me->GetAura(SPELL_OBSIDIAN_ARMOR)->GetStackAmount());
                    }
                }

                if (!UpdateVictim())
                    if (me->SelectNearestPlayer(70.0f))
                    {
                        if (GetLeftLeg())
                            GetLeftLeg()->AI()->DoZoneInCombat();

                        if (GetRightLeg())
                            GetRightLeg()->AI()->DoZoneInCombat();

                        me->AI()->DoZoneInCombat();
                    }

                if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (Phase == PHASE_1)
                {
                    if (HealthBelowPct(26) && !phaseTwo)
                    {
                        Phase = PHASE_2;

                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

                        events.CancelEvent(EVENT_CONCUSSIVE_STOMP);
                        events.CancelEvent(EVENT_THERMAL_IGNITION);
                        events.CancelEvent(EVENT_THERMAL_IGNITION2);
                        events.CancelEvent(EVENT_CONCUSSIVE_STOMP_VOLCAN);

                        Talk(YELL_PHASE2);

                        me->SetDisplayId(MODEL_PHASE2);
                        me->SetSpeed(MOVE_RUN, speedRateNormal);

                        me->SetReactState(REACT_AGGRESSIVE);
                        DoZoneInCombat();

                        me->RemoveAurasDueToSpell(SPELL_OBSIDIAN_ARMOR);
                        DespawnCreatures(53585);
                        summons.DespawnAll();

                        if (GetRightLeg())
                        {
                            GetRightLeg()->RemoveAurasDueToSpell(SPELL_OBSIDIAN_ARMOR);
                            GetRightLeg()->DisappearAndDie();
                        }
                        if (GetLeftLeg())
                        {    
                            GetLeftLeg()->RemoveAurasDueToSpell(SPELL_OBSIDIAN_ARMOR);
                            GetLeftLeg()->DisappearAndDie();
                        }
                        
                        events.ScheduleEvent(EVENT_UNLEASHED_FLAME, timerUnleashedFlame);
                        events.ScheduleEvent(EVENT_IMMOLATION, 100);
                        events.ScheduleEvent(EVENT_CONCUSSIVE_STOMP2, timerConcussiveStomp2);
                        phaseTwo = true;
                    }

                    if (me->GetPositionZ() <= 100.0f && lavaFlow == false)
                    {
                        me->MonsterTextEmote(EMOTE_MAGMA, 0, true);
                        lavaFlow = true;
                    }

                    if (lavaFlow == true)
                    {
                        if (drinkMagma == false)
                        {
                            drinkMagma = true;
                            DoCast(me, SPELL_DRINK_MAGMA);
                        }
                        else
                            DoCast(me, SPELL_MOLTEN_SPEW);
                    }

                    if (lavaFlow == false)
                    {
                        float x, y, z;
                        me->GetClosePoint(x, y, z, me->GetObjectSize() / 3);
                        me->GetMotionMaster()->MovePoint(0, x, y, z);
                    }
                }

                events.Update(diff);

                   while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {                
                        case EVENT_ZONE_COMBAT:
                            SetPlayersInCombat(true);
                            events.ScheduleEvent(EVENT_ZONE_COMBAT, 1000);
                        break;

                        case EVENT_SUPERHEATED:
                            me->MonsterTextEmote(EMOTE_SUPERHEATED, 0, true);
                            DoCast(me, SPELL_SUPERHEATED);
                        
                            events.ScheduleEvent(EVENT_SUPERHEATED, timerSuperheated);
                        break;

                        case EVENT_CONCUSSIVE_STOMP:
                            DoCast(me, SPELL_CONCUSSIVE_STOMP);
                            events.ScheduleEvent(EVENT_CONCUSSIVE_STOMP_VOLCAN, 1000);
                        break;

                        case EVENT_CONCUSSIVE_STOMP_VOLCAN:
                            for (int32 i = 0;  i < RAID_MODE(2, 3, 2, 3); ++i)
                            {
                                Position pos = me->GetRandomNearPosition(urand(10,90));
                                while (pos.GetPositionZ() < 100.0f || pos.GetPositionZ() > 101.0f || me->GetDistance(pos) < 15.0f || CenterPlatform[0].GetExactDist(pos.GetPositionX(),pos.GetPositionY(),pos.GetPositionZ()) > 50.0f)
                                    me->GetRandomNearPosition(90);
                                me->CastSpell(pos.GetPositionX(),pos.GetPositionY(),pos.GetPositionZ(),SPELL_VOLCANIC_BIRTH,true);
                            }
                            events.ScheduleEvent(EVENT_CONCUSSIVE_STOMP, timerConcussiveStomp);
                        break;

                        case EVENT_THERMAL_IGNITION:
                            for (int32 i = 0;  i < RAID_MODE(5, 10, 5, 10); ++i)
                                DoCast(me, SPELL_THERMAL_IGNITION);    
                            events.ScheduleEvent(EVENT_THERMAL_IGNITION2, 33000);
                        break;

                        case EVENT_THERMAL_IGNITION2:
                            DoCast(me, SPELL_THERMAL_IGNITION2);
                            events.ScheduleEvent(EVENT_THERMAL_IGNITION, 33000);
                        break;              

                        case EVENT_UNLEASHED_FLAME:
                            DoCast(me, SPELL_UNLEASHED_FLAME);                        
                            events.ScheduleEvent(EVENT_UNLEASHED_FLAME, timerUnleashedFlame);
                        break;

                        case EVENT_IMMOLATION:
                            DoCast(me, SPELL_IMMOLATION);
                        break;

                        case EVENT_CONCUSSIVE_STOMP2:                        
                            DoCast(me, SPELL_CONCUSSIVE_STOMP);                        
                            events.ScheduleEvent(EVENT_CONCUSSIVE_STOMP2, timerConcussiveStomp2);
                        break;
                    }
                }

            if (Phase == PHASE_2)
                DoMeleeAttackIfReady();
            }    

            Creature* GetLeftLeg()
            {
                return (me->FindNearestCreature(52577, 5000.0f, true) == NULL) ? me->FindNearestCreature(52577, 5000.0f, false) : me->FindNearestCreature(52577, 5000.0f, true);
            }

            Creature* GetRightLeg()
            {
                return (me->FindNearestCreature(53087, 5000.0f, true)  == NULL) ? me->FindNearestCreature(53087, 5000.0f, false) : me->FindNearestCreature(53087, 5000.0f, true);
            }

            void SummonAndSetLegsInBoss()
            {
                if (!me || !me->IsAlive())
                    return;

                if (GetRightLeg())
                {
                    if (!GetRightLeg()->IsAlive())
                        GetRightLeg()->Respawn(true);

                    if (Vehicle* pVehicle = me->GetVehicleKit())
                        if (!pVehicle->GetPassenger(1))
                        {
                            RightSet = true;
                            GetRightLeg()->EnterVehicle(me, 1);
                            GetLeftLeg()->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        }
                }

                if (GetLeftLeg())
                {
                    if (!GetLeftLeg()->IsAlive())
                        GetLeftLeg()->Respawn(true);

                    if (Vehicle* pVehicle = me->GetVehicleKit())
                        if (!pVehicle->GetPassenger(0))
                        {
                            LeftSet = true;
                            GetLeftLeg()->EnterVehicle(me, 0);
                            GetLeftLeg()->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        }
                }
            }

        };
};

/*######
##Ryolith leg
######*/

class npc_left_leg : public CreatureScript
{
public:

    npc_left_leg() : CreatureScript("npc_left_leg"){ }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_left_legAI(creature);
    }

    struct npc_left_legAI : public ScriptedAI
    {
        npc_left_legAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            Reset();
        }

        InstanceScript* instance;
        uint32 side;

        void JustDied(Unit* /*killer*/) { }

        void SetAltPowerForPlayers(int32 power)
        {
            Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
            if (!PlayerList.isEmpty())
                for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    if (Player* player = i->GetSource())
                        if (player->IsAlive() && GetRhyo() && player->GetDistance(GetRhyo()) <= 150.0f)
                            player->SetPower(POWER_ALTERNATE_POWER, player->GetPower(POWER_ALTERNATE_POWER) + power);
        }

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            me->AddUnitTypeMask(UNIT_MASK_ACCESSORY);
            side = 0;
        }

        void EnterCombat(Unit* /*who*/)
        {
            me->SetInCombatWithZone();
            if (GetRhyo() && GetRhyo()->IsAlive())
                GetRhyo()->AI()->DoZoneInCombat();
        }

        void UpdateAI(uint32 /*diff*/) { }

        void DamageTaken(Unit* /*who*/, uint32& damage)
        {
            side += damage;

            if (side >= me->GetMaxHealth() * 0.024)
                if (GetRhyo())
                {
                    SetAltPowerForPlayers(float(side / (me->GetMaxHealth() * 0.024)));
                    GetRhyo()->StopMoving();
                    GetRhyo()->SetFacingTo(GetRhyo()->GetOrientation() + ((side / (me->GetMaxHealth() * 0.024)) * 0.1f));
                    side /= me->GetMaxHealth() * 0.024;
                }

            if (damage && GetRhyo() && GetRight())
            {
                uint32 health = me->GetHealth() + GetRight()->GetHealth();
                me->SetHealth(health/2);
                GetRight()->SetHealth(health/2);
                GetRhyo()->SetHealth(health);
            }
        }

        Creature* GetRhyo()
        {
            return (me->FindNearestCreature(52558, 5000.0f, true) == NULL) ? me->FindNearestCreature(52558, 5000.0f, false) : me->FindNearestCreature(52558, 5000.0f, true);
        }

        Creature* GetRight()
        {
            return (me->FindNearestCreature(53087, 5000.0f, true) == NULL) ? me->FindNearestCreature(53087, 5000.0f, false) : me->FindNearestCreature(53087, 5000.0f, true);
        }
    };
};

class npc_right_leg : public CreatureScript
{
public:
    npc_right_leg() : CreatureScript("npc_right_leg"){ }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_right_legAI(creature);
    }

    struct npc_right_legAI : public ScriptedAI
    {
        npc_right_legAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            Reset();
        }

        InstanceScript* instance;
        uint32 side;

        void JustDied(Unit* /*killer*/) { }

        void SetAltPowerForPlayers(int32 power)
        {
            Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
            if (!PlayerList.isEmpty())
                for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    if (Player* player = i->GetSource())
                        if (player->IsAlive() && GetRhyo() && player->GetDistance(GetRhyo()) <= 150.0f)
                            player->SetPower(POWER_ALTERNATE_POWER, player->GetPower(POWER_ALTERNATE_POWER) + power);
        }
        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            me->AddUnitTypeMask(UNIT_MASK_ACCESSORY);
            side = 0;
        }

        void EnterCombat(Unit* /*who*/)
        {
            me->SetInCombatWithZone();
            if (GetRhyo() && GetRhyo()->IsAlive())
                GetRhyo()->AI()->DoZoneInCombat();
        }

        void UpdateAI(uint32 /*diff*/) { }

        void DamageTaken(Unit* /*who*/, uint32& damage)
        {
            side += damage;

            if (side >= me->GetMaxHealth() * 0.024)
                if (GetRhyo())
                {
                    SetAltPowerForPlayers(float(-1*(side / (me->GetMaxHealth() * 0.024))));
                    GetRhyo()->StopMoving();
                    GetRhyo()->SetFacingTo(GetRhyo()->GetOrientation() - ((side / (me->GetMaxHealth() * 0.024)) * 0.1f));
                    side /= me->GetMaxHealth() * 0.024;
                }

            if (damage && GetRhyo() && GetLeft())
            {
                int32 health = me->GetHealth() + GetLeft()->GetHealth();
                me->SetHealth(health/2);
                GetLeft()->SetHealth(health/2);
                GetRhyo()->SetHealth(health);
            }
        }

        Creature* GetRhyo()
        {
            return (me->FindNearestCreature(52558, 5000.0f, true) == NULL) ? me->FindNearestCreature(52558, 5000.0f, false) : me->FindNearestCreature(52558, 5000.0f, true);
        }

        Creature* GetLeft()
        {
            return (me->FindNearestCreature(52577, 5000.0f, true) == NULL) ? me->FindNearestCreature(52577, 5000.0f, false) : me->FindNearestCreature(52577, 5000.0f, true);
        }

    };
};

/*######
##volcano
######*/

class npc_rhyolith_volcano : public CreatureScript
{
public:
    npc_rhyolith_volcano() : CreatureScript("npc_rhyolith_volcano"){ }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_rhyolith_volcanoAI(creature);
    }

    struct npc_rhyolith_volcanoAI : public ScriptedAI
    {
        npc_rhyolith_volcanoAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            me->SetReactState(REACT_PASSIVE);
            blow = false;
        }

        InstanceScript* instance;
        EventMap events;
        bool blow;

        void JustDied(Unit* /*killer*/) { }
        
        void IsSummonedBy(Unit* /*summoner*/)
        {
            me->AddAura(SPELL_VISUAL_VOLCAN,me);
            me->AddAura(SPELL_SMOKE_VOLCAN,me);

            std::list<Creature*> unitList;
            me->GetCreatureListWithEntryInGrid(unitList, 52582, 200.0f);
            bool activated = false;
            for (std::list<Creature*>::const_iterator itr = unitList.begin(); itr != unitList.end(); ++itr)
                if ((*itr)->HasAura(SPELL_VOLCAN_CHECK_ACTIVE))
                    activated = true;

            if (activated == false)
            {
                me->AddAura(SPELL_VOLCAN_CHECK_ACTIVE,me);
                events.ScheduleEvent(EVENT_ERRUPTION_START, 1000);
            }
        }

        void Reset()
        {
            events.Reset();
        }
        
        void UpdateAI(uint32 diff) 
        {
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (blow == false && GetRhyo()) // blow ? :)))) had to redo this just for fun, see comment below.
            {
                GetRhyo()->AddAura(SPELL_MOLTEN_ARMOR,GetRhyo()); // GetRhyo()->GetTarget->IsBitch() ? payForBlowJob : findWhore; There, this suits the blow bool.

                blow = true;

                if (Aura* aura = GetRhyo()->GetAura(SPELL_OBSIDIAN_ARMOR))
                {
                    int32 stack = aura->GetStackAmount() - 10;

                    if (stack >= 0) /// @todo warning: comparison of unsigned expression >= 0 is always true
                    {
                        GetRhyo()->SetAuraStack(SPELL_OBSIDIAN_ARMOR, GetRhyo(), stack);
                        //GetRhyo()->SetSpeed(MOVE_RUN, GetRhyo()->GetSpeed(MOVE_RUN) + 0.1f);
                        //GetRhyo()->SetSpeed(MOVE_WALK, GetRhyo()->GetSpeed(MOVE_WALK) + 0.1f);
                    }
                }

                if (Creature* rhyolith = GetClosestCreatureWithEntry(me, NPC_RHYOLITH , 150.0f))    
                {
                    rhyolith->MonsterTextEmote(EMOTE_VOLCANO, 0, true);
                    rhyolith->SummonCreature(NPC_RHYOLITH_CRATER, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN);
                    me->DespawnOrUnsummon();
                }
            }

            events.Update(diff);
            
            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_ERRUPTION_START:
                    me->AddAura(SPELL_ERUPTION,me);
                    me->RemoveAurasDueToSpell(SPELL_SMOKE_VOLCAN);
                    events.ScheduleEvent(EVENT_LAVA_STRIKE, 3000);
                    events.ScheduleEvent(EVENT_ERRUPTION_END, 20000);
                break;

                case EVENT_ERRUPTION_END:
                    me->RemoveAurasDueToSpell(SPELL_ERUPTION);
                    me->AddAura(SPELL_SMOKE_VOLCAN,me);
                break;

                case EVENT_LAVA_STRIKE:
                        for (int32 i = 0;  i < RAID_MODE(3, 3, 6, 6); ++i)
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 500, true))
                                DoCast(target, SPELL_LAVA_STRIKE);


                    events.ScheduleEvent(EVENT_LAVA_STRIKE, 3000);
                break;
                
                default:
                break;
                }
            }
        }

        Creature* GetRhyo()
        {
            return (me->FindNearestCreature(52558, 8.0f, true) == NULL) ? me->FindNearestCreature(52558, 8.0f, false) : me->FindNearestCreature(52558, 8.0f, true);
        }
            
    };
};

/*######
##crater
######*/

class npc_rhyolith_crater : public CreatureScript
{
public:

    npc_rhyolith_crater() : CreatureScript("npc_rhyolith_crater"){ }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_rhyolith_craterAI(creature);
    }

    struct npc_rhyolith_craterAI : public ScriptedAI
    {
        npc_rhyolith_craterAI(Creature* creature) : ScriptedAI(creature) , summons(me)
        {
            instance = me->GetInstanceScript();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            me->SetReactState(REACT_PASSIVE);
        }

        InstanceScript* instance;
        EventMap events;
        uint32 number;
        SummonList summons;

        void JustDied(Unit* /*killer*/) { }
        
        void Reset()
        {
            events.Reset();
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);

            switch (summon->GetEntry())
            {
                case 53585: // this hack for lava tube, because if add it to crater nothing changed(dont know why)
                    if (me->GetDistance(summon) < 0.5f)
                    {
                        summon->SetObjectScale(2.0f);
                        summon->CastSpell(summon,SPELL_LAVA_TUBE,true);
                    }
                    else
                        summon->CastSpell(summon,SPELL_LAVA_FLOW,true);
                    break;
                default:
                    break;
            }
        }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            number = 10;
            events.ScheduleEvent(EVENT_ACTIVATE_CRATER, urand(5000,20000));
            DoCast(me, SPELL_MAGMA);
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

                case EVENT_ACTIVATE_CRATER:
                    me->SummonCreature(53585,me->GetPositionX(),me->GetPositionY(),me->GetPositionZMinusOffset());
                    events.ScheduleEvent(EVENT_LAVA_LINE, 5000);
                    events.ScheduleEvent(EVENT_LAVA_LINES_BLOW, 17000);
                    events.ScheduleEvent(EVENT_DESPAWN_CRATER, 45000);    
                    break;

                case EVENT_LAVA_LINE:
                    if (number <= 45)
                    {
                        me->SummonCreature(53585,me->GetPositionX(),me->GetPositionY() - float(number),me->GetPositionZMinusOffset());
                        me->SummonCreature(53585,me->GetPositionX() + float(number),me->GetPositionY(),me->GetPositionZMinusOffset());
                        me->SummonCreature(53585,me->GetPositionX(),me->GetPositionY() + float(number),me->GetPositionZMinusOffset());
                        me->SummonCreature(53585,me->GetPositionX() - float(number),me->GetPositionY(),me->GetPositionZMinusOffset());
                        me->SummonCreature(53585,me->GetPositionX() + float(number),me->GetPositionY() - float(number),me->GetPositionZMinusOffset());
                        me->SummonCreature(53585,me->GetPositionX() - float(number),me->GetPositionY() + float(number),me->GetPositionZMinusOffset());
                        number += 1;
                        events.ScheduleEvent(EVENT_LAVA_LINE, 100);
                    }
                    break;

                case EVENT_DESPAWN_CRATER:
                    summons.DespawnAll();
                    me->DespawnOrUnsummon();
                break;

                case EVENT_LAVA_LINES_BLOW:
                    std::list<Creature*> creatures;
                    GetCreatureListWithEntryInGrid(creatures, me, 53585, 1000.0f);

                    if (creatures.empty())
                       return;

                    for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                        if ((*iter)->IsSummon() && (*iter)->ToTempSummon()->GetSummonerGUID() == me->GetGUID())
                        {
                            (*iter)->CastSpell((*iter),97234,true);
                            (*iter)->DespawnOrUnsummon(1000);
                        }
                    break;
                }
            }
        }

        Creature* GetRhyo()
        {
            return (me->FindNearestCreature(52558, 5000.0f, true) == NULL) ? me->FindNearestCreature(52558, 5000.0f, false) : me->FindNearestCreature(52558, 5000.0f, true);
        }

    };
};

/*######
##lava_line
######*/

class npc_lava_line : public CreatureScript
{
public:

    npc_lava_line() : CreatureScript("npc_lava_line"){ }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lava_lineAI(creature);
    }

    struct npc_lava_lineAI : public ScriptedAI
    {
        npc_lava_lineAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetReactState(REACT_PASSIVE);
        }

        InstanceScript* instance;
        EventMap events;

        void JustDied(Unit* /*killer*/) { }
        
        void Reset()
        {
            events.Reset();
        }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            events.ScheduleEvent(EVENT_CHECK_NEAR_PLAYER, 4000);
            events.ScheduleEvent(EVENT_DESPAWN_LINE, 30000);
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
                case EVENT_CHECK_NEAR_PLAYER:
                    if (!me->HasAura(SPELL_LAVA_TUBE))
                    {
                        if (me->SelectNearestPlayer(0))
                        {
                            me->CastSpell(me,97234,true);
                            events.ScheduleEvent(EVENT_CHECK_NEAR_PLAYER, 2500);
                        }
                        else
                            events.ScheduleEvent(EVENT_CHECK_NEAR_PLAYER, 300);
                    }
                    break;

                case EVENT_DESPAWN_LINE:
                    me->DespawnOrUnsummon();
                    break;

                default:
                break;
                }
            }
        }

        Creature* GetRhyo()
        {
            return (me->FindNearestCreature(52558, 5000.0f, true) == NULL) ? me->FindNearestCreature(52558, 5000.0f, false) : me->FindNearestCreature(52558, 5000.0f, true);
        }
    };
};

// 52619
class npc_liquid_obsidian_52619 : public CreatureScript
{
public:
    npc_liquid_obsidian_52619() : CreatureScript("npc_liquid_obsidian_52619"){ }

    struct npc_liquid_obsidian_52619AI : public ScriptedAI
    {
        npc_liquid_obsidian_52619AI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;

        void Reset() { }
        void JustDied(Unit* /*killer*/) { }

        void EnterCombat(Unit* /*who*/)
        {
            me->SetInCombatWithZone();
            me->AttackStop();
            me->SetReactState(REACT_PASSIVE);

            if (Creature* rhyolith = GetClosestCreatureWithEntry(me, NPC_RHYOLITH , 100.0f))    
                me->GetMotionMaster()->MoveChase(rhyolith);
        }

        void UpdateAI(uint32 /*diff*/) 
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;
        
            if (GetClosestCreatureWithEntry(me, NPC_RHYOLITH, 3.0f))
            {
                DoCast(me, SPELL_FUSE);
                if (Creature* rhyolith = GetClosestCreatureWithEntry(me, NPC_RHYOLITH , 50.0f))    
                if (Aura* aura = rhyolith->GetAura(SPELL_OBSIDIAN_ARMOR))
                {
                    uint32 stack = aura->GetStackAmount();
                    uint32 stack2 = aura->GetStackAmount() + 1;
                    rhyolith->SetAuraStack(SPELL_OBSIDIAN_ARMOR, rhyolith, stack2);
                
                    if (stack == 0)
                        return;
                }

                me->DisappearAndDie();
            } 
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_liquid_obsidian_52619AI(creature);
    }
};

/*######
##spark
######*/

class npc_spark_of_rhyolith : public CreatureScript
{
public:
    npc_spark_of_rhyolith() : CreatureScript("npc_spark_of_rhyolith"){ }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_spark_of_rhyolithAI(creature);
    }


    struct npc_spark_of_rhyolithAI : public ScriptedAI
    {
        npc_spark_of_rhyolithAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void JustDied(Unit* /*killer*/) { }

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoCast(me, SPELL_IMOLATION);

            events.ScheduleEvent(EVENT_INFERNAL_RAGE, 1000);
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
                        case EVENT_INFERNAL_RAGE:
                            DoCast(me, SPELL_INFERNAL_RAGE);
                            events.ScheduleEvent(EVENT_INFERNAL_RAGE, timerInfernalRage);
                        break;

                        default:
                        break;
                    }
            }

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_lord_rhyolith()
{
    new npc_kar_the_everburning();
    new npc_unstable_pyrelord();
    new boss_lord_rhyolith();
    new npc_left_leg();
    new npc_right_leg();
    new npc_liquid_obsidian_52619();
    new npc_rhyolith_volcano();
    new npc_rhyolith_crater();
    new npc_spark_of_rhyolith();
    new npc_lava_line();
}