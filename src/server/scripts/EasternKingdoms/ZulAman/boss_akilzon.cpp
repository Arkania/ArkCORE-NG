 /*
 * Copyright (C) 2014 Arkania Project
 *
 * This file is NOT free software. You may NOT copy, redistribute it or modify it.
 */

/* ScriptData
SDName: Boss_Akil'zon 4.1
SD%Complete: 100
SDComment:
SDCategory: Zul'Aman 5 Hc
EndScriptData */

#include "ScriptPCH.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
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
#include "Weather.h"

#include "zulaman.h"

enum Yells
{
    SAY_AGGRO                  = 0,
    SAY_SUMMON_EAGLE           = 1,
    SAY_INTRO                  = 2,
    SAY_BERSERK                = 3,
    SAY_SLAY                   = 4,
    SAY_DEATH                  = 5,

    ANN_STORM                  = 6
};

enum Spells
{
    // Boss
    SPELL_STATIC_DISRUPTION    = 43622,
    SPELL_STATIC_VISUAL        = 45265,
    SPELL_CALL_LIGHTNING       = 43661,
    SPELL_SUMMON_KIDNAPPER     = 43621,
    SPELL_ELECTRICAL_STORM     = 43648,
    SPELL_ELECTRICAL_STORM_VIS = 44007, // Cloud above.
    SPELL_BERSERK              = 45078,
    SPELL_ELECTRICAL_OVERLOAD  = 43658,

    // Eagles & Kidnapper
    SPELL_EAGLE_SWOOP          = 44732,
    SPELL_PLUCKED              = 97318,

    SPELL_ENTER_VEHICLE        = 46598
};

enum Mobs
{
    MOB_SOARING_EAGLE          = 24858,
    MOB_AMANI_KIDNAPPER        = 52648
};

enum EagleLocations
{
    SE_LOC_X_MAX               = 400,
    SE_LOC_X_MIN               = 335,
    SE_LOC_Y_MAX               = 1435,
    SE_LOC_Y_MIN               = 1370
};

enum Events
{
    EVENT_STATIC_DISRUPTION    = 1,
    EVENT_CALL_LIGHTNING,
    EVENT_ELECTRICAL_STORM,
    EVENT_SUMMON_EAGLES,
    EVENT_SUMMON_KIDNAPPER,
    EVENT_RELEASE_PLAYER,
    EVENT_BERSERK
};

class boss_akilzon : public CreatureScript
{
public:
    boss_akilzon() : CreatureScript("boss_akilzon") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_akilzonAI(creature);
    }

    struct boss_akilzonAI : public BossAI
    {
        boss_akilzonAI(Creature* creature) : BossAI(creature, DATA_AKILZONEVENT), summons(me)
        {
            instance = creature->GetInstanceScript();
            introDone = false;
        }
		
        InstanceScript* instance;
        EventMap events;
        SummonList summons;

        bool introDone;
        Unit* stormTarget;
        Unit* stormVehicle;

        void Reset()
        {
			events.Reset();
			summons.DespawnAll();

            if (instance)
                instance->SetData(DATA_AKILZONEVENT, NOT_STARTED);

            SetWeather(WEATHER_STATE_FINE);

            _Reset();
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (!introDone && me->IsWithinDistInMap(who, 30) && who->GetTypeId() == TYPEID_PLAYER)
            {
                Talk(SAY_INTRO);
                introDone = true;
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_AGGRO);

            if (instance)
            {
                instance->SetData(DATA_AKILZONEVENT, IN_PROGRESS);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add
            }

            events.ScheduleEvent(EVENT_STATIC_DISRUPTION, urand(10000, 20000));
            events.ScheduleEvent(EVENT_ELECTRICAL_STORM, 60000);
            events.ScheduleEvent(EVENT_SUMMON_EAGLES, 30000);
            events.ScheduleEvent(EVENT_SUMMON_KIDNAPPER, urand(20000, 30000));

            events.ScheduleEvent(EVENT_BERSERK, 10 * MINUTE * IN_MILLISECONDS);

			_EnterCombat();
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
            Talk(SAY_SLAY);
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);
			summons.DespawnAll();

            if (instance)
            {
                instance->SetData(DATA_AKILZONEVENT, DONE);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            _JustDied();
        }

        void EnterEvadeMode()
        {
            Reset();
			me->GetMotionMaster()->MoveTargetedHome();
			me->RemoveAllAuras();

            if (instance)
            {
                instance->SetBossState(DATA_AKILZONEVENT, FAIL);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            _EnterEvadeMode();
        }

        void SetWeather(uint32 weather)
        {
            Map* map = me->GetMap();
            if (!map->IsDungeon())
                return;

            WorldPacket data(SMSG_WEATHER, 9);
            data << uint32(weather) << float(0.5f) << uint8(0);
            map->SendToPlayers(&data);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_BERSERK:
                        Talk(SAY_BERSERK);
                        DoCast(me, SPELL_BERSERK);
                        break;

                    case EVENT_STATIC_DISRUPTION:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                            DoCast(target, SPELL_STATIC_DISRUPTION);
                        events.ScheduleEvent(EVENT_STATIC_DISRUPTION, urand(10000, 20000));
                        events.ScheduleEvent(EVENT_CALL_LIGHTNING, urand(2000, 5000));
                        break;

                    case EVENT_CALL_LIGHTNING:
                        DoCastVictim(SPELL_CALL_LIGHTNING);
                        break;

                    case EVENT_ELECTRICAL_STORM:
                        Talk(ANN_STORM);
                        SetWeather(WEATHER_STATE_HEAVY_RAIN);
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true))
                        {
                            target->CastSpell(target, SPELL_ELECTRICAL_STORM_VIS, true); // Cloud visual.

                            target->SetUnitMovementFlags(MOVEMENTFLAG_DISABLE_GRAVITY);
                            target->SetCanFly(true);
                            target->MonsterMoveWithSpeed(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ()+15, 2);

                            DoCast(target, SPELL_ELECTRICAL_STORM, false); // Real spell.
                            stormTarget = target;
                        }
                        events.ScheduleEvent(EVENT_ELECTRICAL_STORM, 60000);
                        events.ScheduleEvent(EVENT_RELEASE_PLAYER, 8100);
                        break;

                    case EVENT_SUMMON_EAGLES:
                        Talk(SAY_SUMMON_EAGLE);

                        float x, y, z;
                        me->GetPosition(x, y, z);
                        
                        for (uint8 i = 0; i < 8; ++i)
                        {
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                            {
                                x = target->GetPositionX() + irand(-10, 10);
                                y = target->GetPositionY() + irand(-10, 10);
                                z = target->GetPositionZ() + urand(16, 20);
                                if (z > 95)
                                    z = 95.0f - urand(0, 5);
                            }
                            Creature* creature = me->SummonCreature(MOB_SOARING_EAGLE, x, y, z, 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
                            if (creature)
                            {
                                creature->AddThreat(me->GetVictim(), 1.0f);
                                creature->AI()->AttackStart(me->GetVictim());
                            }
                        }
                        events.ScheduleEvent(EVENT_SUMMON_EAGLES, urand(50000, 60000));
                        events.ScheduleEvent(EVENT_SUMMON_KIDNAPPER, urand(5000, 8000));
                        break;

                    case EVENT_SUMMON_KIDNAPPER:
                        me->CastSpell(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()+15, SPELL_SUMMON_KIDNAPPER, true);
                        break;

                    case EVENT_RELEASE_PLAYER:
                        SetWeather(WEATHER_STATE_FINE);
                        if (stormTarget)
                        {
                            stormTarget->SetUnitMovementFlags(MOVEMENTFLAG_NONE);
				            stormTarget->SetCanFly(false);
                        }
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

class npc_akilzon_eagle : public CreatureScript
{
public:
    npc_akilzon_eagle() : CreatureScript("npc_akilzon_eagle") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_akilzon_eagleAI(creature);
    }

    struct npc_akilzon_eagleAI : public ScriptedAI
    {
        npc_akilzon_eagleAI(Creature* creature) : ScriptedAI(creature) { }

        uint32 EagleSwoop_Timer;
        bool arrived;
        uint64 TargetGUID;

        void Reset()
        {
            EagleSwoop_Timer = urand(5000, 10000);
            arrived = true;
            TargetGUID = 0;
            me->SetUnitMovementFlags(MOVEMENTFLAG_DISABLE_GRAVITY);
        }

        void MovementInform(uint32, uint32)
        {
            arrived = true;
            if (TargetGUID)
            {
                if (Unit* target = Unit::GetUnit(*me, TargetGUID))
                    DoCast(target, SPELL_EAGLE_SWOOP);
                TargetGUID = 0;
                me->SetSpeed(MOVE_RUN, 1.2f);
                EagleSwoop_Timer = urand(5000, 10000);
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (EagleSwoop_Timer <= diff)
                EagleSwoop_Timer = 0;
            else
                EagleSwoop_Timer -= diff;

            if (arrived)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                {
                    float x, y, z;
                    if (EagleSwoop_Timer)
                    {
                        x = target->GetPositionX() + irand(-10, 10);
                        y = target->GetPositionY() + irand(-10, 10);
                        z = target->GetPositionZ() + urand(10, 15);
                        if (z > 95)
                            z = 95.0f - urand(0, 5);
                    }
                    else
                    {
                        target->GetContactPoint(me, x, y, z);
                        z += 2;
                        me->SetSpeed(MOVE_RUN, 5.0f);
                        TargetGUID = target->GetGUID();
                    }
                    me->GetMotionMaster()->MovePoint(0, x, y, z);
                    arrived = false;
                }
            }
        }
    };
};

class npc_amani_kidnapper : public CreatureScript
{
public:
    npc_amani_kidnapper() : CreatureScript("npc_amani_kidnapper") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_amani_kidnapperAI(creature);
    }

    struct npc_amani_kidnapperAI : public ScriptedAI
    {
        npc_amani_kidnapperAI(Creature* creature) : ScriptedAI(creature) { }

        bool arrived;
        uint64 TargetGUID;
        uint8 numb;

        void Reset()
        {
            arrived = true;
            TargetGUID = 0;
            me->SetUnitMovementFlags(MOVEMENTFLAG_DISABLE_GRAVITY);

			numb = 0;
        }

        void EnterCombat(Unit* /*who*/)
        {
            Map::PlayerList const& players = me->GetMap()->GetPlayers();
            for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
            	if (Player* player = itr->GetSource())
            		++numb;
        }

        void MovementInform(uint32, uint32)
        {
            if (TargetGUID)
            {
                if (Unit* target = Unit::GetUnit(*me, TargetGUID))
                {
                    me->AddAura(SPELL_PLUCKED, target);
                    target->CastSpell(me, SPELL_ENTER_VEHICLE, true);
                }
                TargetGUID = 0;
                me->SetSpeed(MOVE_RUN, 1.2f);
                me->GetMotionMaster()->MoveRandom(30.0f);
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (arrived && numb > 1)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                {
                    float x, y, z;

                    target->GetContactPoint(me, x, y, z);
                    z += 3;
                    me->SetSpeed(MOVE_RUN, 5.0f);
                    TargetGUID = target->GetGUID();

                    me->GetMotionMaster()->MovePoint(0, x, y, z);
                    arrived = false;
                }
            }
            else
                DoMeleeAttackIfReady();
        }
    };
};

class spell_electrical_storm_dmg : public SpellScriptLoader // 43657, 97300
{
    public:
        spell_electrical_storm_dmg() : SpellScriptLoader("spell_electrical_storm_dmg") { }

        class spell_electrical_storm_dmg_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_electrical_storm_dmg_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                if (targets.empty())
                    return;

                if (Unit* owner = GetCaster())
                    targets.remove(owner);

                // Check target distance.
                targets.sort(Trinity::ObjectDistanceOrderPred(GetCaster(), false));

                // Set targets.
                for (std::list<WorldObject*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                {
                    if ((*itr)->GetDistance(GetCaster()) < 20.0f)
                        targets.remove(*itr);
                }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_electrical_storm_dmg_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_electrical_storm_dmg_SpellScript();
        }
};

void AddSC_boss_akilzon()
{
    new boss_akilzon();
    new npc_akilzon_eagle();
    new npc_amani_kidnapper();
    new spell_electrical_storm_dmg();
}