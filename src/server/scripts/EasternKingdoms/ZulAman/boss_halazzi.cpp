 /*
 * Copyright (C) 2014 Arkania Project
 *
 * This file is NOT free software. You may NOT copy, redistribute it or modify it.
 */

/* ScriptData
SDName: Boss_Halazzi 4.1
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

enum Yells
{
    YELL_AGGRO              = 0,
    YELL_SPLIT              = 1,
    YELL_MERGE              = 2,
    YELL_KILL_ONE           = 3,
    YELL_KILL_TWO           = 4,
    YELL_BERSERK            = 5,
    YELL_DEATH              = 6,
    YELL_INTRO1             = 7,
    YELL_INTRO2             = 8,

    ANN_SPLIT               = 9,
    ANN_MERGE               = 10
};

enum Spells
{
    // Boss
    SPELL_DUAL_WIELD         = 86629,
    SPELL_ENRAGE             = 43139,
    SPELL_FLAMESHOCK         = 43303,
    SPELL_EARTHSHOCK         = 43305,
    SPELL_SUMM_WATER_TOTEM   = 97499,

    SPELL_TRANSFORM_SPLIT    = 43142,
    SPELL_TRANSFORM_SPLIT2   = 43573,

    SPELL_TRANSFORM_MERGE    = 43271,
    SPELL_TRANSF_MERGE_DMG   = 44054,

    SPELL_SUMMON_LYNX        = 43143,
    SPELL_SUMMON_LIGHT_TOTEM = 43302,

    SPELL_BERSERK            = 45078,

    // Lynx mob
    SPELL_LYNX_FRENZY        = 43290,
    SPELL_SHRED_ARMOR        = 43243,
    SPELL_SPIRIT_VISUAL      = 42466, // White dust visual and stuff, can have many uses :D
    SPELL_FIXATE             = 97486
};

enum Npc
{
    MOB_SPIRIT_LYNX          = 24143
};

enum PhaseHalazzi
{
    PHASE_NONE               = 0,
    PHASE_LYNX               = 1,
    PHASE_HUMAN              = 2,
};

enum Events
{
    /*** Halazzi ***/
    // Lynx Avatar form
    EVENT_ENRAGE             = 1,
    EVENT_WATER_TOTEM,

    // Worshipper form
    EVENT_LIGHTNING_TOTEM,
    EVENT_SHOCK,

    EVENT_BERSERK,

    /*** Lynx Spirit ***/
    EVENT_SELECT_TARGET,
    EVENT_SHRED_ARMOR,
    EVENT_LYNX_FRENZY,
    EVENT_FIXATE
};

enum Health
{
    MAX_HEALTH  = 4149700,
    LYNX_HEALTH = 2074850
};

class boss_halazzi : public CreatureScript
{
public:
    boss_halazzi() : CreatureScript("boss_halazzi") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_halazziAI(creature);
    }

    struct boss_halazziAI : public BossAI
    {
        boss_halazziAI(Creature* creature) : BossAI(creature, DATA_HALAZZIEVENT), summons(me)
        {
            instance = creature->GetInstanceScript();
            introDone = false;
        }

        InstanceScript* instance;
        EventMap events;
        SummonList summons;

        bool introDone;
        PhaseHalazzi Phase;
        uint64 LynxGUID;
        uint32 TransformCount;

        void Reset()
        {
			events.Reset();
			summons.DespawnAll();

            if (instance)
                instance->SetData(DATA_HALAZZIEVENT, NOT_STARTED);

            LynxGUID = 0;
            TransformCount = 0;
            DoCast(me, SPELL_DUAL_WIELD, true);
            me->SetFloatValue(UNIT_FIELD_MINOFFHANDDAMAGE, me->GetFloatValue(UNIT_FIELD_MINDAMAGE));
            me->SetFloatValue(UNIT_FIELD_MAXOFFHANDDAMAGE, me->GetFloatValue(UNIT_FIELD_MAXDAMAGE));

            Phase = PHASE_NONE;

            _Reset();
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (!introDone && me->IsWithinDistInMap(who, 50) && who->GetTypeId() == TYPEID_PLAYER)
            {
                Talk(RAND(YELL_INTRO1, YELL_INTRO2));
                introDone = true;
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(YELL_AGGRO);

            if (instance)
            {
                instance->SetData(DATA_HALAZZIEVENT, IN_PROGRESS);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add
            }

            EnterPhase(PHASE_LYNX);
            events.ScheduleEvent(EVENT_BERSERK, 10 * MINUTE * IN_MILLISECONDS);

			_EnterCombat();
        }

        void JustSummoned(Creature* summon)
        {
			summons.Summon(summon);
			summon->setActive(true);
 
			if (me->IsInCombat())
			    summon->AI()->DoZoneInCombat();

            if (summon->GetEntry() == MOB_SPIRIT_LYNX)
                LynxGUID = summon->GetGUID();
        }

        void EnterEvadeMode()
        {
            Reset();
			me->GetMotionMaster()->MoveTargetedHome();
			me->RemoveAllAuras();

            if (instance)
            {
                instance->SetBossState(DATA_HALAZZIEVENT, FAIL);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            _EnterEvadeMode();
        }

        void SpellHit(Unit*, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_TRANSFORM_SPLIT2)
                EnterPhase(PHASE_HUMAN);

            if (spell->Id == SPELL_TRANSFORM_MERGE)
                EnterPhase(PHASE_LYNX);
        }

        void KilledUnit(Unit* /*victim*/)
        {
            Talk(RAND(YELL_KILL_ONE, YELL_KILL_TWO));
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(YELL_DEATH);
			summons.DespawnAll();

            if (instance)
            {
                instance->SetData(DATA_HALAZZIEVENT, DONE);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            _JustDied();
        }

        void EnterPhase(PhaseHalazzi NextPhase)
        {
            switch (NextPhase)
            {
                case PHASE_LYNX:
                    if (Creature* Lynx = Unit::GetCreature(*me, LynxGUID))
                        Lynx->DisappearAndDie();
                    me->SetMaxHealth(MAX_HEALTH);
                    me->SetHealth(MAX_HEALTH - ((MAX_HEALTH / 3) * TransformCount));

                    events.CancelEvent(EVENT_SHOCK);
                    if (TransformCount != 2)
                        events.CancelEvent(EVENT_LIGHTNING_TOTEM); // Leave Lightning Totem in final Lynx phase.

                    events.ScheduleEvent(EVENT_ENRAGE, 16000);
                    events.ScheduleEvent(EVENT_WATER_TOTEM, 12000);
                    break;

                case PHASE_HUMAN:
                    DoCast(me, SPELL_SUMMON_LYNX, true);
                    me->SetMaxHealth(LYNX_HEALTH);
                    me->SetHealth(LYNX_HEALTH);

                    events.CancelEvent(EVENT_ENRAGE);
                    events.CancelEvent(EVENT_WATER_TOTEM);

                    events.ScheduleEvent(EVENT_LIGHTNING_TOTEM, 12000);
                    events.ScheduleEvent(EVENT_SHOCK, 15000);
                    break;

                default:
                    break;
            }
            Phase = NextPhase;
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (Phase == PHASE_LYNX)
            if (me->HealthBelowPct(61) && TransformCount == 0 || me->HealthBelowPct(31) && TransformCount == 1)
            {
                me->RemoveAura(SPELL_TRANSFORM_MERGE);
                Talk(YELL_SPLIT);
                Talk(ANN_SPLIT);
                DoCast(me, SPELL_TRANSFORM_SPLIT);
                TransformCount++;
            }

            if (Phase == PHASE_HUMAN)
            if (Creature* Lynx = Unit::GetCreature(*me, LynxGUID))
                if (Lynx->HealthBelowPct(21) || me->HealthBelowPct(21))
                {
                    me->RemoveAura(SPELL_TRANSFORM_SPLIT2);
                    Talk(YELL_MERGE);
                    Talk(ANN_MERGE);
                    DoCast(me, SPELL_TRANSF_MERGE_DMG);
                    DoCast(me, SPELL_TRANSFORM_MERGE);
                }

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_BERSERK:
                        Talk(YELL_BERSERK);
                        DoCast(me, SPELL_BERSERK);
                        break;

                    case EVENT_ENRAGE:
                        DoCast(me, SPELL_ENRAGE);
                        events.ScheduleEvent(EVENT_ENRAGE, urand(10000, 15000));
                        break;

                    case EVENT_LIGHTNING_TOTEM:
                        DoCast(me, SPELL_SUMMON_LIGHT_TOTEM);
                        events.ScheduleEvent(EVENT_LIGHTNING_TOTEM, 20000);
                        break;

                    case EVENT_WATER_TOTEM:
                        DoCast(me, SPELL_SUMM_WATER_TOTEM);
                        events.ScheduleEvent(EVENT_WATER_TOTEM, urand(35000, 45000));
                        break;

                    case EVENT_SHOCK:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        {
                            if (target->IsNonMeleeSpellCasted(false))
                                DoCast(target, SPELL_EARTHSHOCK);
                            else
                                DoCast(target, SPELL_FLAMESHOCK);
                        }
                        events.ScheduleEvent(EVENT_SHOCK, urand(10000, 15000));
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

// Spirit of the Lynx.
class npc_halazzi_lynx : public CreatureScript
{
public:
   npc_halazzi_lynx() : CreatureScript("npc_halazzi_lynx") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_halazzi_lynxAI(creature);
    }

    struct npc_halazzi_lynxAI : public ScriptedAI
    {
        npc_halazzi_lynxAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            DoCast(creature, SPELL_SPIRIT_VISUAL);
        }

        InstanceScript* instance;
        EventMap events;

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_SELECT_TARGET, 100);
            events.ScheduleEvent(EVENT_LYNX_FRENZY, 20000);
            events.ScheduleEvent(EVENT_SHRED_ARMOR, 4000);
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
                    case EVENT_SELECT_TARGET:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        {
                            DoModifyThreatPercent(me->GetVictim(), -100);
                            AttackStart(target);
                            DoCast(target, SPELL_FIXATE);
                            DoModifyThreatPercent(target, 100);
                            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
                            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, true);
                        }
                        events.ScheduleEvent(EVENT_SELECT_TARGET, urand(30000, 40000));
	                    break;

                    case EVENT_LYNX_FRENZY:
                        DoCast(me, SPELL_LYNX_FRENZY);
                        events.ScheduleEvent(EVENT_LYNX_FRENZY, urand(30000, 50000));
                        break;

                    case EVENT_SHRED_ARMOR:
                        DoCastVictim(SPELL_SHRED_ARMOR);
                        events.ScheduleEvent(EVENT_SHRED_ARMOR, urand(30000, 50000));
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_halazzi()
{
    new boss_halazzi();
    new npc_halazzi_lynx();
}