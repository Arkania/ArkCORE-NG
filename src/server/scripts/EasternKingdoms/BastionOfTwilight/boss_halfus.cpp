/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * - Script complete: 99%. ToDo: Behemoth flight positions for Flame Barrage.
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

enum Yells
{
   SAY_AGGRO      = 0,
   SAY_KILL       = 1,
   SAY_DIE        = 2,
   SAY_DRAGON_1   = 3,
   SAY_DRAGON_2   = 4,
   SAY_DRAGON_3   = 5,

   SAY_ROAR       = 6
};

enum Spells
{
    // Proto-Behemoth 
    SPELL_ROOT                               = 42716,
    SPELL_FIREBALL                           = 86058, // Basic spell. 1.5s cast.
    SPELL_FIREBALL_TD                        = 83862, // Time Dilation. 3s cast.

    SPELL_SCORCHING_BREATH                   = 83707,  // Triggers 83855 which needs radius.
    SPELL_FIREBALL_BARRAGE                   = 83706,  // This is channel aura, trigger 83719.
    SPELL_FIREBALL_BARRAGE_DAMAGE            = 83721,  // This with 83719 which has dummy script.
    SPELL_FIREBALL_BARRAGE_DAMAGE_TD         = 83733,  // This with 83719 which has dummy script.

    SPELL_DANCING_FLAMES                     = 84106,  // Activates Fireball Barrage, aura on activating Time Warden.
    SPELL_SUPERHEATED_BREATH                 = 83956,  // Activates Scorching Breath, aura on activating Orphaned Emerald Whelps.

    // Halfus Wyrmbreaker
    SPELL_FURIOUS_ROAR                       = 83710,  // Three times in a row. Needs radius 100 y.

    SPELL_MALEVOLENT_STRIKES                 = 39171,  // Slate Dragon awakes.
    SPELL_FRENZIED_ASSAULT                   = 83693,  // Nether Scion awakes.

    SPELL_SHADOW_WRAPPED                     = 83952,  // Gains aura when Storm Rider awakes.
    SPELL_SHADOW_NOVA                        = 83703,  // Every other 30 - 40 seconds.

    SPELL_BERSERK                            = 26662,  // 6 min enrage timer.
    SPELL_BIND_WILL                          = 83432,  // On drakes at aggro.

    // Dragon debuffs on Halfus
    SPELL_NETHER_BLINDNESS                   = 83611, // From Nether Scion.
    SPELL_CYCLONE_WINDS                      = 84092, // From Storm Rider.
    SPELL_ATROPHIC_POISON                    = 83609, // Eight stacks, from whelps.
    SPELL_TIME_DILATION                      = 83601, // From Time Warden.
    SPELL_STONE_TOUCH_NORMAL                 = 83603,
    SPELL_STONE_TOUCH_HEROIC                 = 84593, // Stone Grip, from Slate Dragon.

    SPELL_DRAGONS_VENGEANCE                  = 87683, // Debuff on Halfus by dragons when they die.

    //  Dragons
    SPELL_UNRESPONSIVE_DRAGON                = 86003, // Dragons.
    SPELL_UNRESPONSIVE_WHELP                 = 86022  // Whelps.
};

enum Events
{
    // Halfus
    EVENT_SHADOW_NOVA = 1,
    EVENT_FURIOUS_ROAR,
    EVENT_FURIOUS_ROAR_CAST,

    EVENT_BERSERK, // 6 min.

    // Behemoth
    EVENT_MOVE_UP,
    EVENT_ROOT,
    EVENT_FIREBALL,
    EVENT_SCORCHING_BREATH,
    EVENT_FIREBALL_BARRAGE
};

enum Creatures
{
    NPC_PROTO_BEHEMOTH                       = 44687,

    NPC_SLATE_DRAGON                         = 44652,
    NPC_NETHER_SCION                         = 44645,
    NPC_STORM_RIDER                          = 44650,
    NPC_TIME_RIDER                           = 44797,
    NPC_ORPHANED_WHELP                       = 44641
};

// 44600
class boss_halfus : public CreatureScript
{
    public:
        boss_halfus() : CreatureScript("boss_halfus") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_halfusAI(creature);
        }
            
        struct boss_halfusAI : public BossAI
        {
            boss_halfusAI(Creature* creature) : BossAI(creature, DATA_HALFUS)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;

            bool roarPhase, canNova, dragonsPicked, whelpsActive, roarSaid;
            uint8 RoarCasts;

            void Reset()
            {
                RoarCasts = 3;
                summons.DespawnAll();
                events.Reset();

                roarPhase     = false;
                canNova       = false;
                dragonsPicked = false;
                whelpsActive  = false;
                roarSaid      = false;

                if(instance)
                {
                    instance->SetBossState(DATA_HALFUS, NOT_STARTED);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
                }

                me->RemoveAllAuras();

                _Reset();
            }

            void InitializeAI()
            {
              if(!me->IsDead())
                Reset();
            }

            void EnterEvadeMode()
            {
                RemoveUnresponsiveWhelps();
                RemoveUnresponsiveSlate();
                RemoveUnresponsiveNether();
                RemoveUnresponsiveStorm();
                RemoveUnresponsiveTime();

                Reset();

                me->GetMotionMaster()->MoveTargetedHome();

                if (instance)
                    instance->SetBossState(DATA_HALFUS, FAIL);
            
                _EnterEvadeMode();
            }

            void JustDied(Unit* /*killer*/)
            {
                Talk(SAY_DIE);
                summons.DespawnAll();

                if (Creature* behemoth = me->FindNearestCreature(NPC_PROTO_BEHEMOTH, 500.0f, true))
                    behemoth->DisappearAndDie();

                if(instance)
                {
                    instance->SetBossState(DATA_HALFUS, DONE);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
                }

                _JustDied();
            }

            void KilledUnit(Unit * /*victim*/)
            {
                Talk(SAY_KILL);
            }

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);
                summon->setActive(true);
            
                if(me->IsInCombat())
                summon->AI()->DoZoneInCombat();
            }

            void MoveInLineOfSight(Unit* who)
            {
                if (!dragonsPicked && who->IsWithinDistInMap(me, 100.0f))
                {
                    PickDragons();
                    dragonsPicked = true;
                }
            }

            void EnterCombat(Unit* /*who*/)
            {
                Talk(SAY_AGGRO);

                if (Creature* behemoth = me->FindNearestCreature(NPC_PROTO_BEHEMOTH, 500.0f, true))
                    behemoth->AI()->AttackStart(me->GetVictim());

                if(instance)
                {
                    instance->SetBossState(DATA_HALFUS, IN_PROGRESS);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add
                }

                events.ScheduleEvent(EVENT_BERSERK, 6 * MINUTE * IN_MILLISECONDS);

                _EnterCombat();
            }

            void CastUnresponsiveWhelps()
            {
                std::list<Creature*> creatures;

                GetCreatureListWithEntryInGrid(creatures, me, NPC_ORPHANED_WHELP, 1000.0f);
                
                if (creatures.empty())
                   return;
                
                for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                    me->AddAura(SPELL_UNRESPONSIVE_WHELP, (*iter));
            }

            void RemoveUnresponsiveWhelps()
            {
                std::list<Creature*> creatures;

                GetCreatureListWithEntryInGrid(creatures, me, NPC_ORPHANED_WHELP, 1000.0f);

                if (creatures.empty())
                   return;
                
                for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                    (*iter)->AI()->EnterEvadeMode();
            }

            void RemoveUnresponsiveSlate()
            {
                std::list<Creature*> creatures;
                GetCreatureListWithEntryInGrid(creatures, me, NPC_SLATE_DRAGON, 1000.0f);
                if (creatures.empty())
                   return;
                
                for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                    (*iter)->AI()->EnterEvadeMode();
            }

            void RemoveUnresponsiveNether()
            {
                std::list<Creature*> creatures;
                GetCreatureListWithEntryInGrid(creatures, me, NPC_NETHER_SCION, 1000.0f);
                if (creatures.empty())
                   return;
                
                for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                    (*iter)->AI()->EnterEvadeMode();
            }

            void RemoveUnresponsiveStorm()
            {
                std::list<Creature*> creatures;
                GetCreatureListWithEntryInGrid(creatures, me, NPC_STORM_RIDER, 1000.0f);
                if (creatures.empty())
                   return;
                
                for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                    (*iter)->AI()->EnterEvadeMode();
            }

            void RemoveUnresponsiveTime()
            {
                std::list<Creature*> creatures;
                GetCreatureListWithEntryInGrid(creatures, me, NPC_TIME_RIDER, 1000.0f);
                if (creatures.empty())
                   return;
                
                for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                    (*iter)->AI()->EnterEvadeMode();
            }

            void PickDragons()
            {
                // Checks for reset / hack attempts :)

                if (!me->FindNearestCreature(NPC_PROTO_BEHEMOTH, 500.0f, true))
                    me->SummonCreature(NPC_PROTO_BEHEMOTH, -281.0f, -715.5f, 911.34f, 2.61f, TEMPSUMMON_CORPSE_DESPAWN, 1000);

                if (!me->FindNearestCreature(NPC_SLATE_DRAGON, 500.0f, true))
                    me->SummonCreature(NPC_SLATE_DRAGON, -281.8f, -693.8f, 888.09f, 2.93f, TEMPSUMMON_CORPSE_DESPAWN, 1000);

                if (!me->FindNearestCreature(NPC_NETHER_SCION, 500.0f, true))
                    me->SummonCreature(NPC_NETHER_SCION, -283.22f, -672.14f, 888.09f, 3.37f, TEMPSUMMON_CORPSE_DESPAWN, 1000);

                if (!me->FindNearestCreature(NPC_STORM_RIDER, 500.0f, true))
                    me->SummonCreature(NPC_STORM_RIDER, -319.0f, -723.35f, 888.08f, 1.59f, TEMPSUMMON_CORPSE_DESPAWN, 1000);

                if (!me->FindNearestCreature(NPC_TIME_RIDER, 500.0f, true))
                    me->SummonCreature(NPC_TIME_RIDER, -353.01f, -697.08f, 888.1f, 5.42f, TEMPSUMMON_CORPSE_DESPAWN, 1000);

                // Function

                Creature* behemoth = me->FindNearestCreature(NPC_PROTO_BEHEMOTH, 500.0f, true);

                Creature* slateDragon  = me->FindNearestCreature(NPC_SLATE_DRAGON, 500.0f, true);
                Creature* netherScion  = me->FindNearestCreature(NPC_NETHER_SCION, 500.0f, true);
                Creature* stormRider   = me->FindNearestCreature(NPC_STORM_RIDER, 500.0f, true);
                Creature* timeRider    = me->FindNearestCreature(NPC_TIME_RIDER, 500.0f, true);
                //Creature* orphanWhelp  = me->FindNearestCreature(NPC_ORPHANED_WHELP, 500.0f, true);

                if (!me->GetMap()->IsHeroic()) // 10 possible combinations, 3 drakes randomly selected available.
                {
                    uint32 drakeCombination = urand(1, 10);

                    switch(drakeCombination)
                    {
                        case 1:  // Slate, Storm, Whelps.
                        me->AddAura(SPELL_UNRESPONSIVE_DRAGON, netherScion);
                        me->AddAura(SPELL_UNRESPONSIVE_DRAGON, timeRider);
                        me->AddAura(SPELL_MALEVOLENT_STRIKES, me);
                        me->AddAura(SPELL_SHADOW_WRAPPED, me);
                        me->AddAura(SPELL_SUPERHEATED_BREATH, behemoth);
                        whelpsActive = true;
                        break;
                        case 2:  // Slate, Nether, Time.
                        CastUnresponsiveWhelps();
                        me->AddAura(SPELL_UNRESPONSIVE_DRAGON, stormRider);
                        me->AddAura(SPELL_MALEVOLENT_STRIKES, me);
                        me->AddAura(SPELL_FRENZIED_ASSAULT, me);
                        me->AddAura(SPELL_DANCING_FLAMES, behemoth);
                        break;
                        case 3:  // Slate, Storm, Time.
                        CastUnresponsiveWhelps();
                        me->AddAura(SPELL_UNRESPONSIVE_DRAGON, netherScion);
                        me->AddAura(SPELL_MALEVOLENT_STRIKES, me);
                        me->AddAura(SPELL_SHADOW_WRAPPED, me);
                        me->AddAura(SPELL_DANCING_FLAMES, behemoth);
                        break;
                        case 4:  // Storm, Nether, Time.
                        CastUnresponsiveWhelps();
                        me->AddAura(SPELL_UNRESPONSIVE_DRAGON, slateDragon);
                        me->AddAura(SPELL_FRENZIED_ASSAULT, me);
                        me->AddAura(SPELL_SHADOW_WRAPPED, me);
                        me->AddAura(SPELL_DANCING_FLAMES, behemoth);
                        break;
                        case 5:  // Slate, Storm, Nether.
                        CastUnresponsiveWhelps();
                        me->AddAura(SPELL_UNRESPONSIVE_DRAGON, timeRider);
                        me->AddAura(SPELL_MALEVOLENT_STRIKES, me);
                        me->AddAura(SPELL_FRENZIED_ASSAULT, me);
                        me->AddAura(SPELL_SHADOW_WRAPPED, me);
                        break;
                        case 6:  // Slate, Whelps, Time.
                        me->AddAura(SPELL_UNRESPONSIVE_DRAGON, netherScion);
                        me->AddAura(SPELL_UNRESPONSIVE_DRAGON, stormRider);
                        me->AddAura(SPELL_MALEVOLENT_STRIKES, me);
                        me->AddAura(SPELL_SUPERHEATED_BREATH, behemoth);
                        me->AddAura(SPELL_DANCING_FLAMES, behemoth);
                        whelpsActive = true;
                        break;
                        case 7:  // Whelps, Nether, Time.
                        me->AddAura(SPELL_UNRESPONSIVE_DRAGON, slateDragon);
                        me->AddAura(SPELL_UNRESPONSIVE_DRAGON, stormRider);
                        me->AddAura(SPELL_FRENZIED_ASSAULT, me);
                        me->AddAura(SPELL_SUPERHEATED_BREATH, behemoth);
                        me->AddAura(SPELL_DANCING_FLAMES, behemoth);
                        whelpsActive = true;
                        break;
                        case 8:  // Storm, Whelps, Time.
                        me->AddAura(SPELL_UNRESPONSIVE_DRAGON, netherScion);
                        me->AddAura(SPELL_UNRESPONSIVE_DRAGON, slateDragon);
                        me->AddAura(SPELL_SHADOW_WRAPPED, me);
                        me->AddAura(SPELL_SUPERHEATED_BREATH, behemoth);
                        me->AddAura(SPELL_DANCING_FLAMES, behemoth);
                        whelpsActive = true;
                        break;
                        case 9:  // Storm, Whelps, Nether.
                        me->AddAura(SPELL_UNRESPONSIVE_DRAGON, timeRider);
                        me->AddAura(SPELL_UNRESPONSIVE_DRAGON, slateDragon);
                        me->AddAura(SPELL_FRENZIED_ASSAULT, me);
                        me->AddAura(SPELL_SHADOW_WRAPPED, me);
                        me->AddAura(SPELL_SUPERHEATED_BREATH, behemoth);
                        whelpsActive = true;
                        break;
                        case 10: // Slate, Whelps, Nether.
                        me->AddAura(SPELL_UNRESPONSIVE_DRAGON, timeRider);
                        me->AddAura(SPELL_UNRESPONSIVE_DRAGON, stormRider);
                        me->AddAura(SPELL_MALEVOLENT_STRIKES, me);
                        me->AddAura(SPELL_FRENZIED_ASSAULT, me);
                        me->AddAura(SPELL_SUPERHEATED_BREATH, behemoth);
                        whelpsActive = true;
                        break;
                    }
                }
                else // All drakes + abilities available on Heroic mode.
                {
                    me->AddAura(SPELL_FRENZIED_ASSAULT, me);
                    me->AddAura(SPELL_SHADOW_WRAPPED, me);
                    me->AddAura(SPELL_MALEVOLENT_STRIKES, me);
                    me->AddAura(SPELL_DANCING_FLAMES, behemoth);
                    me->AddAura(SPELL_SUPERHEATED_BREATH, behemoth);
                }
            }

            void UpdateAI(uint32 uiDiff)
            {
                if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (me->HasAura(SPELL_SHADOW_WRAPPED) && !canNova)
                {
                    events.ScheduleEvent(EVENT_SHADOW_NOVA, urand(7000, 10000));
                    canNova = true;
                }

                if (HealthBelowPct(51) && !roarPhase)
                {
                    events.ScheduleEvent(EVENT_FURIOUS_ROAR, 2000);
                    roarPhase = true;
                }

                if (whelpsActive && !me->FindNearestCreature(NPC_ORPHANED_WHELP, 200.0f, true))
                {
                    me->AddAura(SPELL_DRAGONS_VENGEANCE, me);
                    whelpsActive = false;
                }

                events.Update(uiDiff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_SHADOW_NOVA:
                        DoCast(me, SPELL_SHADOW_NOVA);
                        events.ScheduleEvent(EVENT_SHADOW_NOVA, urand(7000, 10000));
                        break;

                        case EVENT_FURIOUS_ROAR:
                        me->AttackStop();
                        RoarCasts = 3;

                        if(!me->HasAura(SPELL_CYCLONE_WINDS))
                            events.ScheduleEvent(EVENT_FURIOUS_ROAR_CAST, 2100);
                        else
                            events.ScheduleEvent(EVENT_FURIOUS_ROAR_CAST, 10100);
                        break;
                        
                        case EVENT_FURIOUS_ROAR_CAST:
                        if (!roarSaid)
                        {
                            Talk(SAY_ROAR);
                            roarSaid = true;
                        }
                        DoCast(me, SPELL_FURIOUS_ROAR);
                        if (RoarCasts > 0)
                        {
                            --RoarCasts;

                            if(!me->HasAura(SPELL_CYCLONE_WINDS))
                                events.ScheduleEvent(EVENT_FURIOUS_ROAR_CAST, 2100);
                            else
                                events.ScheduleEvent(EVENT_FURIOUS_ROAR_CAST, 10100);
                        }
                        else return;
                        break;

                        case EVENT_BERSERK:
                        DoCast(me, SPELL_BERSERK);
                        break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

// 44687
class npc_proto_behemoth : public CreatureScript
{
    public:
        npc_proto_behemoth() : CreatureScript("npc_proto_behemoth") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_proto_behemothAI(creature);
        }
            
        struct npc_proto_behemothAI : public ScriptedAI
        {
            npc_proto_behemothAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;
            bool canBarrage, canBreath;

            void Reset()
            {
                events.Reset();

                if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == POINT_MOTION_TYPE)
                    me->GetMotionMaster()->MovementExpired();

                canBarrage = false;
                canBreath  = false;

                me->GetMotionMaster()->MoveTargetedHome();

                me->SetMaxPower(POWER_MANA, 179000);
                me->SetPower(POWER_MANA, 179000);
                me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
                me->AddUnitMovementFlag(MOVEMENTFLAG_DISABLE_GRAVITY | MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);
            }

            void EnterEvadeMode()
            {
                me->RemoveAllAuras();
                Reset();
            }

            void EnterCombat(Unit* /*who*/)
            {
                canBarrage = false;
                canBreath  = false;

                me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
                me->AddUnitMovementFlag(MOVEMENTFLAG_DISABLE_GRAVITY | MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);

                events.ScheduleEvent(EVENT_MOVE_UP, 500);
                events.ScheduleEvent(EVENT_ROOT, 13000);
                events.ScheduleEvent(EVENT_FIREBALL, 16000);
            }

            void UpdateAI(uint32 uiDiff)
            {
                if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (Creature* Halfus = me->FindNearestCreature(NPC_HALFUS_WORMBREAKER, 500.0f, true))
                    if (!Halfus->IsInCombat())
                        me->AI()->EnterEvadeMode();

                if (me->HasAura(SPELL_DANCING_FLAMES) && !canBarrage)
                {
                    events.ScheduleEvent(EVENT_FIREBALL_BARRAGE, urand(3000, 7000));
                    canBarrage = true;
                }

                if (me->HasAura(SPELL_SUPERHEATED_BREATH) && !canBreath)
                {
                    events.ScheduleEvent(EVENT_SCORCHING_BREATH, urand(3000, 7000));
                    canBreath = true;
                }

                events.Update(uiDiff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_MOVE_UP:
                        me->SetReactState(REACT_PASSIVE);
                        me->GetMotionMaster()->MovePoint(1, -322.578f, -680.321f, 925.3f);
                        break;

                        case EVENT_ROOT:
                        DoCast(me, SPELL_ROOT);
                        break;

                        case EVENT_FIREBALL:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.0f, true))
                        {
                            if (!me->HasAura(SPELL_TIME_DILATION))
                                DoCast(target, SPELL_FIREBALL);
                            else
                                DoCast(target, SPELL_FIREBALL_TD);
                        }

                        if (me->HasAura(SPELL_TIME_DILATION))
                            events.ScheduleEvent(EVENT_FIREBALL, urand(18000, 25000));
                        else                            
                            events.ScheduleEvent(EVENT_FIREBALL, urand(4000, 7000));
                        break;

                        case EVENT_SCORCHING_BREATH:
                        DoCast(me, SPELL_SCORCHING_BREATH);
                        if (me->GetMap()->IsHeroic())
                            events.ScheduleEvent(EVENT_SCORCHING_BREATH, urand(5000, 7000));
                        else
                            events.ScheduleEvent(EVENT_SCORCHING_BREATH, urand(7000, 9000));
                        break;

                        case EVENT_FIREBALL_BARRAGE:
                        DoCast(me, SPELL_FIREBALL_BARRAGE);
                        if (me->GetMap()->IsHeroic())
                            events.ScheduleEvent(EVENT_FIREBALL_BARRAGE, urand(26000, 30000));
                        else
                            events.ScheduleEvent(EVENT_FIREBALL_BARRAGE, urand(30000, 34000));
                        break;
                    }
                }
            }
        };
};

// 44645 44650 44652 44797
class npc_halfus_dragon: public CreatureScript
{
public:
    npc_halfus_dragon () : CreatureScript("npc_halfus_dragon") { }

    struct npc_halfus_dragonAI: public ScriptedAI
    {
        npc_halfus_dragonAI (Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        void Reset ()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            me->DeleteThreatList();
            me->CombatStop(true);
            me->setFaction(35);
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        void EnterCombat(Unit* /*who*/)
        {
            Creature* Halfus = me->FindNearestCreature(NPC_HALFUS_WORMBREAKER, 500.0f, true);

            switch(me->GetEntry())
            {
                case NPC_SLATE_DRAGON:
                Halfus->AI()->Talk(3);
                break;
                case NPC_NETHER_SCION:
                Halfus->AI()->Talk(4);
                break;
                case NPC_STORM_RIDER:
                case NPC_TIME_RIDER:
                Halfus->AI()->Talk(5);
                break;
            }
        }

        void EnterEvadeMode ()
        {
            Reset();
            me->RemoveAllAuras();
            me->GetMotionMaster()->MoveTargetedHome();
        }

        void JustDied(Unit* /*killer*/)
        {
            if (Creature* Halfus = me->FindNearestCreature(NPC_HALFUS_WORMBREAKER, 500.0f, true))
                Halfus->AddAura(SPELL_DRAGONS_VENGEANCE, Halfus);
        }

        void UpdateAI (uint32 /*diff*/)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (me->HasAura(SPELL_UNRESPONSIVE_DRAGON))
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_NPC_FLAG_GOSSIP);

            DoMeleeAttackIfReady();
        }
    };

    bool OnGossipHello(Player* pPlayer, Creature* creature)
    {
        if (!creature->HasAura(SPELL_UNRESPONSIVE_DRAGON))
        if (Creature* Halfus = creature->FindNearestCreature(NPC_HALFUS_WORMBREAKER, 500.0f, true))
        {
            InstanceScript* instance;
            instance = creature->GetInstanceScript();

            if (!instance)
                return false;

            pPlayer->PlayerTalkClass->ClearMenus();
            pPlayer->CLOSE_GOSSIP_MENU();
            creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_NPC_FLAG_GOSSIP);

            switch (creature->GetEntry())
            {
                case NPC_SLATE_DRAGON:
                    if (instance->instance->IsHeroic())
                        creature->AddAura(SPELL_STONE_TOUCH_HEROIC, Halfus);
                    else
                        creature->AddAura(SPELL_STONE_TOUCH_NORMAL, Halfus);
                    break;
                case NPC_NETHER_SCION:
                    creature->AddAura(SPELL_NETHER_BLINDNESS, Halfus);
                    break;
                case NPC_STORM_RIDER:
                    creature->AddAura(SPELL_CYCLONE_WINDS, Halfus);
                    break;
                case NPC_TIME_RIDER:
                    if (Creature* behemoth = creature->FindNearestCreature(NPC_PROTO_BEHEMOTH, 500.0f, true))
                        creature->AddAura(SPELL_TIME_DILATION, behemoth);
                    break;
            }

            Halfus->AI()->DoZoneInCombat(Halfus, 150.0f);
            Halfus->AddAura(SPELL_BIND_WILL, creature);
            creature->SetReactState(REACT_AGGRESSIVE);
            creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

            creature->AI()->DoZoneInCombat(creature);

        return true;
        }

        return false;
    }

    CreatureAI* GetAI (Creature* creature) const
    {
        return new npc_halfus_dragonAI(creature);
    }
};

// 44641
class npc_orphaned_whelp : public CreatureScript
{
public:
    npc_orphaned_whelp() : CreatureScript("npc_orphaned_whelp") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_orphaned_whelpAI(creature);
    }

    struct npc_orphaned_whelpAI : public ScriptedAI
    {
        npc_orphaned_whelpAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        void Reset ()
        {
            me->DeleteThreatList();
            me->CombatStop(true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        void EnterCombat(Unit* /*pWho*/)
        {
            if (Creature* Halfus = me->FindNearestCreature(NPC_HALFUS_WORMBREAKER, 500.0f, true))
            {
                if (!me->HasAura(SPELL_UNRESPONSIVE_WHELP))
                {
                    Creature* behemoth = me->FindNearestCreature(NPC_PROTO_BEHEMOTH, 500.0f, true);

                    me->AddAura(SPELL_ATROPHIC_POISON, behemoth);
                    behemoth->SetAuraStack(SPELL_ATROPHIC_POISON, behemoth, 8);

                    if (!Halfus->IsInCombat())
                        Halfus->AI()->DoZoneInCombat(Halfus, 150.0f);
                    Halfus->AddAura(SPELL_BIND_WILL, me);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                }
            }
        }

        void EnterEvadeMode ()
        {
            Reset();
            me->RemoveAllAuras();
            me->GetMotionMaster()->MoveTargetedHome();
        }

        void JustDied(Unit* /*killer*/) { }

        void UpdateAI(uint32 /*diff*/) 
        {
            DoMeleeAttackIfReady();
        }
    };
};

// 83862 86058
class spell_proto_fireball : public SpellScriptLoader // 86058, 83862
{
public:
    spell_proto_fireball() : SpellScriptLoader("spell_proto_fireball") { }

    class spell_proto_fireballSpellScript : public SpellScript
    {
        PrepareSpellScript(spell_proto_fireballSpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            return true;
        }

        bool Load()
        {
            return true;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (GetCaster()->HasAura(SPELL_TIME_DILATION))
            {
                if (Unit* victim = GetCaster()->GetVictim())
                    GetCaster()->CastSpell(victim, SPELL_FIREBALL_BARRAGE_DAMAGE_TD, false);
            }
            else
            {
                if (Unit* victim = GetCaster()->GetVictim())
                    GetCaster()->CastSpell(victim, SPELL_FIREBALL_BARRAGE_DAMAGE, false);
            }
        }

        void Register()
        {
            OnEffectHit += SpellEffectFn(spell_proto_fireballSpellScript::HandleDummy,EFFECT_0,SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript *GetSpellScript() const
    {
        return new spell_proto_fireballSpellScript();
    }
};

// 83719
class spell_proto_fireball_barrage : public SpellScriptLoader // 83719.
{
public:
    spell_proto_fireball_barrage() : SpellScriptLoader("spell_proto_fireball_barrage") { }

    class spell_proto_fireball_barrageSpellScript : public SpellScript
    {
        PrepareSpellScript(spell_proto_fireball_barrageSpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            return true;
        }

        bool Load()
        {
            return true;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            GetCaster()->CastSpell(GetCaster()->GetVictim(), SPELL_FIREBALL_BARRAGE_DAMAGE_TD, false);
        }

        void Register()
        {
            OnEffectHit += SpellEffectFn(spell_proto_fireball_barrageSpellScript::HandleDummy,EFFECT_0,SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript *GetSpellScript() const
    {
        return new spell_proto_fireball_barrageSpellScript();
    }
};

// 83603 84593
class spell_halfus_stone_touch: public SpellScriptLoader { // 84593.
public:
    spell_halfus_stone_touch() : SpellScriptLoader("spell_halfus_stone_touch") { }

    class spell_halfus_stone_touch_AuraScript: public AuraScript 
    {
        PrepareAuraScript(spell_halfus_stone_touch_AuraScript)

        void HandleEffectPeriodic(AuraEffect const * /*aurEff*/) 
        {
            if (GetId() == 83603)
                GetTarget()->CastSpell(GetTarget(),84030,true);
            else if (GetId() == 84593)
                GetTarget()->CastSpell(GetTarget(),84591,true);
        }

        void Register() 
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_halfus_stone_touch_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript *GetAuraScript() const 
    {
        return new spell_halfus_stone_touch_AuraScript();
    }
};

// 205087
class go_halfus_whelp_cage : public GameObjectScript
{
    public:
        go_halfus_whelp_cage() : GameObjectScript("go_halfus_whelp_cage") { }

        bool OnGossipHello(Player* player, GameObject* go)
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, go, NPC_ORPHANED_WHELP, 1000.0f);

            if (creatures.empty())
            {
                for (uint8 i = 0; i < 8; i++)
                {
                    if (Creature* whelp = go->SummonCreature(NPC_ORPHANED_WHELP, -346.0f, -724.0f, 890.08f, 0, TEMPSUMMON_CORPSE_DESPAWN, 1000))
                        whelp->AI()->AttackStart(player);
                }
            }
            
            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->AI()->AttackStart(player);

            go->UseDoorOrButton();
            player->PlayerTalkClass->ClearMenus();

            return true;
        }
};

void AddSC_boss_halfus()
{
    new boss_halfus();
    new npc_proto_behemoth();
    new npc_halfus_dragon();
    new npc_orphaned_whelp();
    new spell_proto_fireball();
    new spell_proto_fireball_barrage();
    new spell_halfus_stone_touch();
    new go_halfus_whelp_cage();
}