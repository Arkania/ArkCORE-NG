/* ScriptData
SDName: boss_warlord
SD%Complete: 40%
SDComment:
SDCategory: Boss Warlord
EndScriptData
*/

#include "ScriptPCH.h"
#include "dragon_soul.h"

enum Events
{
     EVENT_FOCUSEF_ANGER = 1,
     EVENT_PSYCHIC_DRAIN,
     EVENT_DISRUPTING_SHADOWS,
};

enum Spells
{
     SPELL_FOCUSED_ANGER      = 104543,
     SPELL_PSYCHIC_DRAIN      = 104322,
     SPELL_DISRUPTING_SHADOWS = 103434,
};

class boss_warlord : public CreatureScript
{
public:
    boss_warlord() : CreatureScript("boss_warlord") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<boss_warlordAI>(creature);
    }

    struct boss_warlordAI: public BossAI
    {
        boss_warlordAI(Creature* creature) : BossAI(creature, BOSS_WARLORD)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();

            instance->SetBossState(DATA_PORTALS_ON_OFF, DONE);
            me->RemoveAura(EVENT_FOCUSEF_ANGER);
            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_FOCUSEF_ANGER, urand(30000,30000));
            events.ScheduleEvent(EVENT_PSYCHIC_DRAIN, urand(70000,70000));
            events.ScheduleEvent(EVENT_DISRUPTING_SHADOWS, urand(25000,25000));
            instance->SetBossState(BOSS_WARLORD, IN_PROGRESS);
            instance->SetBossState(DATA_PORTALS_ON_OFF, IN_PROGRESS);
            _EnterCombat();
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_FOCUSEF_ANGER:
		            DoCast(me, SPELL_FOCUSED_ANGER);
                    events.ScheduleEvent(EVENT_FOCUSEF_ANGER, urand(60000,60000));
                    break;

                case EVENT_PSYCHIC_DRAIN:
		            DoCastVictim(SPELL_PSYCHIC_DRAIN);
                    events.ScheduleEvent(EVENT_PSYCHIC_DRAIN, urand(150000,150000));
                    break;

                case EVENT_DISRUPTING_SHADOWS:
					if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                       DoCast(target, SPELL_DISRUPTING_SHADOWS);
                    events.ScheduleEvent(EVENT_DISRUPTING_SHADOWS, urand(40000,80000));
                    break;
                default:
                    break;
                }
            }		

            DoMeleeAttackIfReady();
        }

        void JustReachedHome()
        {
            _JustReachedHome();
            instance->SetBossState(BOSS_WARLORD, FAIL);
        }

        void JustDied(Unit* /*killer*/)
        {
            instance->SetBossState(BOSS_WARLORD, DONE);
            instance->SetBossState(DATA_PORTALS_ON_OFF, DONE);
        }
    };
};

void AddSC_boss_warlord()
{
    new boss_warlord();
}