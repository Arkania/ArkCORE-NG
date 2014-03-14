 /*
 * Copyright (C) 2014 Arkania Project
 *
 * This file is NOT free software. You may NOT copy, redistribute it or modify it.
 */

/* ScriptData
SDName: Boss_Nalorakk 4.1
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

#include "zulaman.h"

// Trash Waves
float NalorakkWay[8][3] =
{
    { 18.569f, 1414.512f, 11.42f}, // waypoint 1
    {-17.264f, 1419.551f, 12.62f},
    {-52.642f, 1419.357f, 27.31f}, // waypoint 2
    {-69.908f, 1419.721f, 27.31f},
    {-79.929f, 1395.958f, 27.31f},
    {-80.072f, 1374.555f, 40.87f}, // waypoint 3
    {-80.072f, 1314.398f, 40.87f},
    {-80.072f, 1295.775f, 48.60f} // waypoint 4
};

enum Yells
{
    // Intro
    SAY_NALORAKK_WAVE1    = 0,
    SAY_NALORAKK_WAVE2    = 1,
    SAY_NALORAKK_WAVE3    = 2,
    SAY_NALORAKK_WAVE4    = 3,

    SAY_NALORAKK_RANGE    = 10,

    // Fight
    SAY_AGGRO             = 5,
    SAY_KILL_1            = 7,
    SAY_KILL_2            = 9,
    SAY_DEATH             = 8,
    SAY_BERSERK           = 12,

    SAY_BEAR              = 6,
    SAY_TROLL             = 11,

    SAY_SURGE             = 4,

    // Announces
    ANN_SURGE             = 13,
    ANN_BEAR              = 14
};

enum Spells
{
    // Troll
    SPELL_BRUTAL_STRIKE   = 42384,
    SPELL_SURGE           = 42402,
    SPELL_TRANSFORM_BEAR  = 42594,

    // Bear
    SPELL_REND_FLESH      = 42397,
    SPELL_LACERATE_SLASH  = 42395,
    SPELL_DEAF_ROAR       = 49721,

    SPELL_BERSERK         = 45078,
};

enum Events
{
    EVENT_BRUTAL_SWIPE    = 1,
    EVENT_SURGE,

    EVENT_REND_FLESH,
    EVENT_LACERATING_SLASH,
    EVENT_DEAFENING_ROAR,

    EVENT_TRANSFORM_BEAR,
    EVENT_TRANSFORM_TROLL,

    EVENT_GUARDS_1,
    EVENT_GUARDS_2,
    EVENT_GUARDS_3,
    EVENT_GUARDS_4,

    EVENT_CHECK_GUARDS_2,
    EVENT_CHECK_GUARDS_3,
    EVENT_CHECK_GUARDS_4,

    EVENT_BERSERK,
};

enum NalorakkGuards
{
    AMANISHI_AXE_THROWER   = 23542,
    AMANISHI_MEDICINE_MAN  = 23581,
    AMANISHI_TRIBESMAN     = 23582,
    AMANISHI_WARBRINGER    = 23580
};

class boss_nalorakk : public CreatureScript
{
public:
    boss_nalorakk() : CreatureScript("boss_nalorakk") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_nalorakkAI(creature);
    }

    struct boss_nalorakkAI : public BossAI
    {
        boss_nalorakkAI(Creature* creature) : BossAI(creature, DATA_NALORAKKEVENT)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;
        bool guards1, guards2, guards3, guards4, rangeTalk, MoveEvent, inCombat, inMove;
        Unit* introTarget;
        uint32 MovePhase;
        uint32 waitTimer;

        void Reset()
        {
            events.Reset();

            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_AGGRESSIVE);

            MoveEvent = true;
            guards1 = false;
            guards2 = false;
            guards3 = false;
            guards4 = false;
            rangeTalk = false;
            inCombat = false;
            inMove = false;
            MovePhase = 0;
            waitTimer = 0;

            me->SetSpeed(MOVE_RUN, 2);
            me->SetWalk(false);

            if (instance)
                instance->SetData(DATA_NALORAKKEVENT, NOT_STARTED);

            _Reset();
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (MoveEvent && me->IsWithinDistInMap(who, 50) && who->GetTypeId() == TYPEID_PLAYER)
            {
                if (instance)
                {
                    instance->SetData(DATA_NALORAKKEVENT, IN_PROGRESS);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add
                }

                me->SetReactState(REACT_PASSIVE);
                events.ScheduleEvent(EVENT_GUARDS_1, 100);
                introTarget = who;
            }
        }

        void DamageTaken(Unit* who, uint32& damage)
        {
            if (!inCombat) 
            {
                Talk(SAY_AGGRO);
                me->AI()->AttackStart(who);
                inCombat = true;
                
                events.ScheduleEvent(EVENT_BRUTAL_SWIPE, urand(7000, 12000));
                events.ScheduleEvent(EVENT_SURGE, urand(15000, 20000));
                events.ScheduleEvent(EVENT_TRANSFORM_BEAR, urand(28000, 32000));
                
                events.ScheduleEvent(EVENT_BERSERK, 10 * MINUTE * IN_MILLISECONDS);
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_DEATH);

            if (instance)
            {
                instance->SetData(DATA_NALORAKKEVENT, DONE);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            _JustDied();
        }

        void KilledUnit(Unit* /*victim*/)
        {
            Talk(RAND(SAY_KILL_1, SAY_KILL_2));
        }

        void EnterEvadeMode()
        {
            if (!MoveEvent)
            {
                events.Reset();
                me->GetMotionMaster()->MoveTargetedHome();
                me->SetReactState(REACT_DEFENSIVE);
                inCombat = false;
                if (me->HasAura(SPELL_TRANSFORM_BEAR))
                    me->RemoveAura(SPELL_TRANSFORM_BEAR);
            }

            if (instance)
            {
                instance->SetData(DATA_NALORAKKEVENT, FAIL);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            _EnterEvadeMode();
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (MoveEvent)
            {
                if (!inMove)
                    return;

                switch(MovePhase)
                {
                    case 2:
                        me->SetFacingTo(3.1415f*2);
                        inMove = false;
                        return;
                    case 1:
                    case 3:
                    case 4:
                    case 6:
                        MovePhase ++;
                        waitTimer = 1;
                        inMove = true;
                        return;
                    case 5:
                    case 7:
                        me->SetFacingTo(3.1415f*0.5f);
                        inMove = false;
                        return;
                }
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim() && inCombat || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (waitTimer && inMove)
            {
                if (waitTimer <= diff)
                {
                    me->GetMotionMaster()->MovementExpired();
                    me->GetMotionMaster()->MovePoint(MovePhase,NalorakkWay[MovePhase][0],NalorakkWay[MovePhase][1],NalorakkWay[MovePhase][2]);
                    waitTimer = 0;
                } else waitTimer -= diff;
            }

            if (!MoveEvent && !rangeTalk && me->IsWithinDistInMap(introTarget, 30))
            {
                Talk(SAY_NALORAKK_RANGE);
                rangeTalk = true;

                me->SetReactState(REACT_DEFENSIVE);
                me->SetHomePosition(me->GetPositionX(),me->GetPositionY(),me->GetPositionZ(),me->GetOrientation());

                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    /*** Intro ***/
                    case EVENT_GUARDS_1: // Where he is
                        Talk(SAY_NALORAKK_WAVE1);
                        SendAttacker(AMANISHI_TRIBESMAN, introTarget);
                        SendAttacker(AMANISHI_AXE_THROWER, introTarget);
                        me->GetMotionMaster()->MovePoint(1, NalorakkWay[1][0], NalorakkWay[1][1], NalorakkWay[1][2]);
                        MovePhase ++;
                        guards1 = true;
                        inMove = true;
                        events.ScheduleEvent(EVENT_CHECK_GUARDS_2, 6000);
                        break;

                    case EVENT_GUARDS_2: // Up the big ladder
                        Talk(SAY_NALORAKK_WAVE2);
                        SendAttacker(AMANISHI_TRIBESMAN, introTarget);
                        SendAttacker(AMANISHI_AXE_THROWER, introTarget);
                        SendAttacker(AMANISHI_MEDICINE_MAN, introTarget);
                        me->GetMotionMaster()->MovePoint(3,NalorakkWay[3][0],NalorakkWay[3][1],NalorakkWay[3][2]);
                        MovePhase ++;
                        inMove = true;
                        events.ScheduleEvent(EVENT_CHECK_GUARDS_3, 6000);
                        break;

                    case EVENT_GUARDS_3: // Top of small ladder
                        Talk(SAY_NALORAKK_WAVE3);
                        SendAttacker(AMANISHI_WARBRINGER, introTarget);
                        me->GetMotionMaster()->MovePoint(6,NalorakkWay[6][0],NalorakkWay[6][1],NalorakkWay[6][2]);
                        MovePhase ++;
                        inMove = true;
                        events.ScheduleEvent(EVENT_CHECK_GUARDS_4, 9000);
                        break;

                    case EVENT_GUARDS_4: // At his place
                        SendAttacker(AMANISHI_WARBRINGER, introTarget);
                        SendAttacker(AMANISHI_AXE_THROWER, introTarget);
                        SendAttacker(AMANISHI_MEDICINE_MAN, introTarget);
                        Talk(SAY_NALORAKK_WAVE4);
                        MoveEvent = false;
                        break;

                    /** Check times ***/
                    case EVENT_CHECK_GUARDS_2:
                    if (guards1 && !guards2 && me->IsWithinDistInMap(introTarget, 25.0))
                    {
                        events.ScheduleEvent(EVENT_GUARDS_2, 100);
                        guards2 = true;
                        events.CancelEvent(EVENT_CHECK_GUARDS_2);
                    }
                    else
                    events.ScheduleEvent(EVENT_CHECK_GUARDS_2, 100);
                    break;

                    case EVENT_CHECK_GUARDS_3:
                    if (guards2 && !guards3 && me->IsWithinDistInMap(introTarget, 25.0))
                    {
                        events.ScheduleEvent(EVENT_GUARDS_3, 100);
                        guards3 = true;
                        events.CancelEvent(EVENT_CHECK_GUARDS_3);
                    }
                    else
                    events.ScheduleEvent(EVENT_CHECK_GUARDS_3, 100);
                    break;

                    case EVENT_CHECK_GUARDS_4:
                    if (guards3 && !guards4 && me->IsWithinDistInMap(introTarget, 50.0))
                    {
                        events.ScheduleEvent(EVENT_GUARDS_4, 100);
                        guards4 = true;
                        events.CancelEvent(EVENT_CHECK_GUARDS_4);
                    }
                    else
                    events.ScheduleEvent(EVENT_CHECK_GUARDS_4, 100);
                    break;

                    /*** Fight ***/
                    case EVENT_BRUTAL_SWIPE:
                        DoCastVictim(SPELL_BRUTAL_STRIKE);
                        events.ScheduleEvent(EVENT_BRUTAL_SWIPE, urand(7000, 12000));
                        break;

                    case EVENT_SURGE:
                        Talk(SAY_SURGE);
                        Talk(ANN_SURGE);
                        if (Unit* target = SelectTarget(SELECT_TARGET_FARTHEST, 0, 80.0f, true)) // Try to select farthest target.
                            DoCast(target, SPELL_SURGE);
                        events.ScheduleEvent(EVENT_SURGE, urand(15000, 20000));
                        break;

                    case EVENT_TRANSFORM_BEAR:
                        Talk(SAY_BEAR);
                        Talk(ANN_BEAR);
                        DoCast(me, SPELL_TRANSFORM_BEAR);

                        events.CancelEvent(EVENT_SURGE);
                        events.CancelEvent(EVENT_BRUTAL_SWIPE);

                        events.ScheduleEvent(EVENT_REND_FLESH, urand(12500, 14000));
                        events.ScheduleEvent(EVENT_LACERATING_SLASH, 2000); // 24 sec duration.
                        events.ScheduleEvent(EVENT_DEAFENING_ROAR, urand(10500, 11500));
                        events.ScheduleEvent(EVENT_TRANSFORM_TROLL, urand(25000, 30000));
                        break;

                    case EVENT_TRANSFORM_TROLL:
                        Talk(SAY_TROLL);
                        me->RemoveAura(SPELL_TRANSFORM_BEAR);

                        events.CancelEvent(EVENT_REND_FLESH);
                        events.CancelEvent(EVENT_LACERATING_SLASH);
                        events.CancelEvent(EVENT_DEAFENING_ROAR);

                        events.ScheduleEvent(EVENT_BRUTAL_SWIPE, urand(7000, 12000));
                        events.ScheduleEvent(EVENT_SURGE, urand(15000, 20000));
                        events.ScheduleEvent(EVENT_TRANSFORM_BEAR, urand(28000, 32000));
                        break;

                    case EVENT_REND_FLESH:
                        DoCastVictim(SPELL_REND_FLESH);
                        events.ScheduleEvent(EVENT_REND_FLESH, urand(10000, 12000));
                        break;

                    case EVENT_LACERATING_SLASH:
                        DoCastVictim(SPELL_LACERATE_SLASH);
                        break;

                    case EVENT_DEAFENING_ROAR:
                        DoCastVictim(SPELL_DEAF_ROAR);
                        events.ScheduleEvent(EVENT_DEAFENING_ROAR, urand(8000, 10000));
                        break;

                    case EVENT_BERSERK:
                        Talk(SAY_BERSERK);
                        DoCast(me, SPELL_BERSERK);
                        break;

                    default:
                        break;
                }
            }

            if (inCombat)
            DoMeleeAttackIfReady();
        }

        void SendAttacker(uint32 entry, Unit* target)
        {
            std::list<Creature*> creatures;
               GetCreatureListWithEntryInGrid(creatures, me, entry, 20.0f);

            if (creatures.empty())
               return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
            {
                (*iter)->SetNoCallAssistance(true);
                (*iter)->AI()->AttackStart(target);
            }
        }
    };
};

void AddSC_boss_nalorakk()
{
    new boss_nalorakk();
}