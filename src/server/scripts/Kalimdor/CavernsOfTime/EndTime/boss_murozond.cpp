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

// 54432
class boss_murozond : public CreatureScript
{
    public:
        boss_murozond() : CreatureScript("boss_murozond") { }

        struct boss_murozondAI : public BossAI
        {
            boss_murozondAI(Creature* creature) : BossAI(creature, BOSS_MUROZOND)
            {
                instance = me->GetInstanceScript();
            }

            InstanceScript* instance;

            void Reset()
            {
                events.Reset();
                if (instance)
                    instance->SetData(DATA_LAST_ENCOUNTER, NOT_STARTED);
            }

            void JustDied(Unit* /*killer*/)
            {
                if (instance)
                    instance->SetData(DATA_LAST_ENCOUNTER, DONE);
            }

            void EnterCombat(Unit* /*who*/)
            {
                if (instance)
                    instance->SetData(DATA_LAST_ENCOUNTER, IN_PROGRESS);

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
                    //switch (eventId)
                    //{
                    //    case EVENT_ROCK_SHARDS:
                    //        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    //            DoCast(target, SPELL_ROCK_SHARDS);
                    //        events.ScheduleEvent(EVENT_ROCK_SHARDS, 15000);
                    //        break;

                    //    default:
                    //        break;
                    //}
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_murozondAI(creature);
        }
};

void AddSC_boss_murozond()
{
    new boss_murozond;
}
