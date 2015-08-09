/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * Script 95% done. TODO:
 * - Live Testing needed.
 *
 * THIS particular file is NOT free software; third-party users 
 * should NOT have access to it, redistribute it or modify it. :)
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "end_time.h"
#include "Vehicle.h"
#include "Unit.h"
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
#include "SpellAuraEffects.h"
#include "SpellAuras.h"
#include "CreatureTextMgr.h"
#include "Vehicle.h"
#include "VehicleDefines.h"
#include "Spell.h"
#include "Player.h"
#include "Map.h"
#include "InstanceScript.h"

enum Yells
{
};

enum Spells
{
};

enum Events
{
};

// 54123
class boss_echo_of_sylvanas : public CreatureScript
{
    public:
        boss_echo_of_sylvanas() : CreatureScript("boss_echo_of_sylvanas") { }

        struct boss_echo_of_sylvanasAI : public BossAI
        {
            boss_echo_of_sylvanasAI(Creature* creature) : BossAI(creature, BOSS_ECHO_OF_SYLVANAS)
            {
                instance = me->GetInstanceScript();
            }

            InstanceScript* instance;

            void Reset()
            {
                events.Reset();
                if (instance)
                    instance->SetBossState(BOSS_ECHO_OF_SYLVANAS, NOT_STARTED);
            }

            void JustDied(Unit* /*killer*/)
            {
                if (instance)
                {
                    if (instance->GetData(DATA_FIRST_ENCOUNTER) == IN_PROGRESS)
                        instance->SetData(DATA_FIRST_ENCOUNTER, DONE);
                    else  
                        instance->SetData(DATA_SECOND_ENCOUNTER, DONE);
                }
            }

            void EnterCombat(Unit* /*who*/)
            {
                if (instance)
                    instance->SetBossState(BOSS_ECHO_OF_SYLVANAS, IN_PROGRESS);

              //  events.ScheduleEvent(EVENT_ROCK_SHARDS, 15000);
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (/*uint32 eventId = */events.ExecuteEvent())
                {
                    // switch (eventId)
                    // {
                    //    case EVENT_ROCK_SHARDS:
                    //        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    //            DoCast(target, SPELL_ROCK_SHARDS);
                    //        events.ScheduleEvent(EVENT_ROCK_SHARDS, 15000);
                    //        break;

                    //    default:
                    //        break;
                    // }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_echo_of_sylvanasAI(creature);
        }
};

void AddSC_boss_echo_of_sylvanas()
{
    new boss_echo_of_sylvanas;
}
