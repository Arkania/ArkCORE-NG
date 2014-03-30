/* ScriptData
SDName: boss_morchok
SD%Complete: 70%
SDComment:
SDCategory: Boss Morchok
EndScriptData
*/

#include "ScriptPCH.h"
#include "dragon_soul.h"

enum Yells
{
    SAY_AGGRO   = 0,
    SAY_DEATH   = 1,
    SAY_EVENT1  = 2, // No work
    SAY_EVENT2  = 3, // No work
    SAY_EVENT3  = 4,
    SAY_EVENT4  = 5,
    SAY_GROUNT1 = 6,
    SAY_GROUNT2 = 7,
    SAY_INTRO   = 8,
    SAY_ORB     = 9, // No work
    SAY_SLAY    = 10,
    SAY_SPLIT   = 11
};

enum Events
{
    EVENT_CRUSH_ARMOR = 1,
    EVENT_STOMP,
    EVENT_BLACK_BLOOD_OF_THE_EARTH,
    EVENT_FURIOUS,
    EVENT_EARTHER_VORTEX,
	EVENT_SUMMON_KOHCROM,
	EVENT_SAY
};

enum Spells
{
    SPELL_FURIOUS                  = 103846,
    SPELL_CRUSH_ARMOR              = 103687,
    SPELL_STOMP                    = 103414,
    SPELL_BLACK_BLOOD_OF_THE_EARTH = 103851,
    SPELL_EARTHER_VORTEX           = 103821,
    SPELL_SUMMON_KOHCROM           = 109017
};

class boss_morchok : public CreatureScript
{
public:
    boss_morchok() : CreatureScript("boss_morchok") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<boss_morchokAI>(creature);
    }

    struct boss_morchokAI: public BossAI
    {
        boss_morchokAI(Creature* creature) : BossAI(creature, BOSS_MORCHOK)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();

            me->RemoveAura(SPELL_FURIOUS);
            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_CRUSH_ARMOR, 1500);
            events.ScheduleEvent(EVENT_STOMP, 60000);
            events.ScheduleEvent(EVENT_FURIOUS, 3000);
            events.ScheduleEvent(EVENT_BLACK_BLOOD_OF_THE_EARTH, 340000);
			if(Is25ManRaid())
				events.ScheduleEvent(EVENT_SUMMON_KOHCROM, 3000);
			events.ScheduleEvent(EVENT_SAY, 30000);

            Talk(SAY_AGGRO);
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
                case EVENT_CRUSH_ARMOR:
		            DoCastVictim(SPELL_CRUSH_ARMOR);
                    events.ScheduleEvent(EVENT_CRUSH_ARMOR, urand(5000,15000));
                    break;

                case EVENT_STOMP:
		            DoCast(SPELL_STOMP);
                    Talk(SAY_GROUNT1);
                    events.ScheduleEvent(EVENT_STOMP, urand(60000,120000));
                    break;

                case EVENT_BLACK_BLOOD_OF_THE_EARTH:
                    DoCast(me, SPELL_BLACK_BLOOD_OF_THE_EARTH);
					Talk(SAY_GROUNT2);
                    events.ScheduleEvent(EVENT_BLACK_BLOOD_OF_THE_EARTH, urand(120000,240000));
                    break;

                case EVENT_FURIOUS:
                    if(me->GetHealthPct() < 20)
                    {
                        DoCast(me, SPELL_FURIOUS);
                        events.CancelEvent(EVENT_FURIOUS);
                    }
                    else
                        events.ScheduleEvent(EVENT_FURIOUS, 15000);
                    break;

				case EVENT_SAY:
					switch (urand(0, 1))
					{
					case 0:
						Talk(SAY_EVENT3);
						break;
					case 1:
						Talk(SAY_EVENT4);
						break;
					}
					break;

                case EVENT_SUMMON_KOHCROM:
                    if(me->GetHealthPct() < 90)
                    {
                        DoCastVictim(SPELL_SUMMON_KOHCROM);
                        events.CancelEvent(EVENT_FURIOUS);
						Talk(SAY_SPLIT);
                    }
                    else
                        events.ScheduleEvent(EVENT_SUMMON_KOHCROM, 15000);
                    break;
                default:
                    break;
                }
            }		

            DoMeleeAttackIfReady();
        }

        void KilledUnit(Unit* victim)
		{

            Talk(SAY_SLAY);
		}

        void JustDied(Unit* /*killer*/)
        {
            instance->SetBossState(BOSS_MORCHOK, DONE);
            instance->SetBossState(DATA_PORTALS_ON_OFF, DONE);
            Talk(SAY_DEATH);
            _JustDied();
        }
    };
};

class npc_kohcrom : public CreatureScript
{
public:
    npc_kohcrom() : CreatureScript("npc_kohcrom") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<npc_kohcromAI>(creature);
    }

    struct npc_kohcromAI: public ScriptedAI
    {
        npc_kohcromAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_CRUSH_ARMOR, 3000);
            events.ScheduleEvent(EVENT_STOMP, 120000);
            events.ScheduleEvent(EVENT_FURIOUS, 3000);
            events.ScheduleEvent(EVENT_BLACK_BLOOD_OF_THE_EARTH, 400000);
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
                case EVENT_CRUSH_ARMOR:
		            DoCastVictim(SPELL_CRUSH_ARMOR);
                    events.ScheduleEvent(EVENT_CRUSH_ARMOR, urand(15000,30000));
                    break;

                case EVENT_STOMP:
		            DoCast(SPELL_STOMP);
                    events.ScheduleEvent(EVENT_STOMP, urand(120000,180000));
                    break;

                case EVENT_BLACK_BLOOD_OF_THE_EARTH:
                    DoCast(me, SPELL_BLACK_BLOOD_OF_THE_EARTH);
                    events.ScheduleEvent(EVENT_BLACK_BLOOD_OF_THE_EARTH, urand(240000,360000));
                    break;

                case EVENT_FURIOUS:
                    if(me->GetHealthPct() < 20)
                    {
                        DoCast(me, SPELL_FURIOUS);
                        events.CancelEvent(EVENT_FURIOUS);
                    }
                    else
                        events.ScheduleEvent(EVENT_FURIOUS, 15000);
                    break;
                default:
                    break;
                }
            }		

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_morchok()
{
    new boss_morchok();
    new npc_kohcrom();
}