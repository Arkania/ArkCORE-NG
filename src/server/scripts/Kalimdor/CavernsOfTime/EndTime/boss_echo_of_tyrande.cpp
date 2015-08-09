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
#include "SpellInfo.h"

enum Yells
{
};

enum Spells
{
};

enum Events
{
};

// 54544
class boss_echo_of_tyrande : public CreatureScript
{
    public:
        boss_echo_of_tyrande() : CreatureScript("boss_echo_of_tyrande") { }

        struct boss_echo_of_tyrandeAI : public BossAI
        {
            boss_echo_of_tyrandeAI(Creature* creature) : BossAI(creature, BOSS_ECHO_OF_TYRANDE)
            {
                instance = me->GetInstanceScript();
            }

            InstanceScript* instance;

            void Reset()
            {
                events.Reset();
                if (instance)
                    instance->SetBossState(BOSS_ECHO_OF_TYRANDE, NOT_STARTED);
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
                    instance->SetBossState(BOSS_ECHO_OF_TYRANDE, IN_PROGRESS);

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
            return new boss_echo_of_tyrandeAI(creature);
        }
};

void AddSC_boss_echo_of_tyrande()
{
    new boss_echo_of_tyrande;
}
