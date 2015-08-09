/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * This file is NOT free software. Third-party users can NOT redistribute
 * it or modify it. If you find it, you are either hacking something, or very
 * lucky (presuming someone else managed to hack it).
 */

/* ScriptData
SDName: boss_warmaster_blackhorm
SD%Complete: 40%
SDComment:
SDCategory: Boss Warmaster Blackhorm
EndScriptData
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "dragon_soul.h"

enum Events
{
    EVENT_PHASE_1 = 1, //no work
    EVENT_PHASE_2,

    EVENT_ATTACK_PHASE1_1, //no work
    EVENT_ATTACK_PHASE1_2, //no work
    EVENT_ATTACK_PHASE1_3, //no work
    EVENT_ATTACK_PHASE1_4, //no work
    EVENT_ATTACK_PHASE1_5, //no work
    EVENT_ATTACK_PHASE1_6, //no work

    EVENT_ATTACK_PHASE2_1,
    EVENT_ATTACK_PHASE2_2,
    EVENT_ATTACK_PHASE2_3,
    EVENT_ATTACK_PHASE2_4,
    EVENT_ATTACK_PHASE2_5, //no work
};

enum Spells
{
    SPELL_DEVASTATE = 108042,
    SPELL_DISRUPTING_ROAR = 108044,
    SPELL_SHOCKWAVE = 108046,
    SPELL_SIPHON_VITALITY = 110313, //no work
    SPELL_SUNDER_ARMOR = 108043, // no work
    SPELL_VENGEANCE = 108045,
};

class boss_warmaster_blackhorn : public CreatureScript
{
public:
    boss_warmaster_blackhorn() : CreatureScript("boss_warmaster_blackhorn") { }

    struct boss_warmaster_blackhornAI : public BossAI
    {
        boss_warmaster_blackhornAI(Creature* creature) : BossAI(creature, BOSS_WARMASTER)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();

            me->RemoveAllAuras();
            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_PHASE_2, 1);
            DoCast(me, SPELL_VENGEANCE);
            _EnterCombat();
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
                case EVENT_PHASE_2:
                    events.ScheduleEvent(EVENT_ATTACK_PHASE2_1, urand(2500, 3500));
                    events.ScheduleEvent(EVENT_ATTACK_PHASE2_2, urand(5500, 15000));
                    events.ScheduleEvent(EVENT_ATTACK_PHASE2_3, urand(60000, 80000));
                    events.ScheduleEvent(EVENT_ATTACK_PHASE2_4, urand(50000, 70000));
                    break;

                case EVENT_ATTACK_PHASE2_1:
                    DoCastVictim(SPELL_DEVASTATE, true);
                    events.ScheduleEvent(EVENT_ATTACK_PHASE2_1, urand(9500, 14000));
                    break;
                case EVENT_ATTACK_PHASE2_2:
                    DoCastVictim(SPELL_SHOCKWAVE);
                    events.ScheduleEvent(EVENT_ATTACK_PHASE2_2, urand(16000, 30000));
                    break;
                case EVENT_ATTACK_PHASE2_3:
                    DoCastVictim(SPELL_DISRUPTING_ROAR);
                    events.ScheduleEvent(EVENT_ATTACK_PHASE2_3, urand(100000, 130000));
                    break;
                case EVENT_ATTACK_PHASE2_4:
                    switch (urand(0, 1))
                    {
                    case 0:
                        me->SummonCreature(NPC_TWILIGHT_ELITE_SLAYER, 13424.7f, -12149.9f, 150.797f, 1.478f, TEMPSUMMON_CORPSE_DESPAWN, 600000);
                        me->SummonCreature(NPC_TWILIGHT_ELITE_SLAYER, 13426.8f, -12113.1f, 151.503f, 4.746f, TEMPSUMMON_CORPSE_DESPAWN, 600000);
                        me->SummonCreature(NPC_TWILIGHT_ELITE_DREADBLADE, 13430.574f, -12151.136f, 151.067f, 1.513f, TEMPSUMMON_CORPSE_DESPAWN, 600000);
                        break;
                    case 1:
                        me->SummonCreature(NPC_TWILIGHT_ELITE_SLAYER, 13450.2f, -12112.2f, 151.971f, 4.746f, TEMPSUMMON_CORPSE_DESPAWN, 600000);
                        me->SummonCreature(NPC_TWILIGHT_ELITE_SLAYER, 13448.9f, -12153.3f, 151.457f, 1.47f, TEMPSUMMON_CORPSE_DESPAWN, 600000);
                        me->SummonCreature(NPC_TWILIGHT_ELITE_DREADBLADE, 13432.279f, -12113.684f, 151.2567f, 4.705f, TEMPSUMMON_CORPSE_DESPAWN, 600000);
                        break;
                    }
                    events.ScheduleEvent(EVENT_ATTACK_PHASE2_3, urand(120000, 140000));
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* killer)
        {
            instance->SetBossState(BOSS_WARMASTER, DONE);
            killer->SummonCreature(NPC_TRAVEL_TO_THE_MAELSTROM, 13405.485f, -12131.544f, 150.971f, 6.213f, TEMPSUMMON_CORPSE_DESPAWN, 600000);
            _JustDied();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<boss_warmaster_blackhornAI>(creature);
    }
};

void AddSC_boss_warmaster_blackhorn()
{
    new boss_warmaster_blackhorn();
}