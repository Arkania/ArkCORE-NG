/*
* Copyright (C) 2011-2012 ProjectStudioMirage <http://www.studio-mirage.fr/>
* Copyright (C) 2011-2012 https://github.com/Asardial
*/

#include "ScriptMgr.h"
#include "grimbatol.h"
#include "Vehicle.h"

// ToDo Move this hardocoded Yells to the DB and add Sound Data to it
#define SAY_AGGRO "I will burn you from the inside out!"
#define SAY_SUMMON "BY FIRE BE... BURNED!"
#define SAY_SUMMON_2 "INCINERATE THEM, MINIONS!"
#define SAY_JUMP_DOWN "Dragon, you will do as I command! Catch me!"
#define SAY_DEAD "Valiona, finish them! Avenge me!"
#define SAY_VALIONA "If they do not kill you, I will do it myself!"

enum Spells
{
    // Drahgas Spells
    SPELL_BURNING_SHADOWBOLT	= 75245,
    SPELL_BURNING_SHADOWBOLT_H	= 90915,

    SPELL_INVOCATION_OF_FLAME	= 75218, // Summons Trigger at Random Location
    SPELL_INVOCATION_TRIGGER	= 75222, // Summons & Visual is casted by the Trigger

    SPELL_TWILIGHT_PROTECTION	= 76303,

    // Valionas Spells
    SPELL_VALIONAS_FLAME		= 75321,
    SPELL_SHREDDING_SWIPE		= 75271,
    SPELL_SEEPING_TWILIGHT		= 75318, // wowhead says 75317 but this spell gives the visual aura
    SPELL_DEVOURING_FLAMES_H	= 90950,
    SPELL_TWILIGHT_SHIFT		= 75328,

    // Invoked Flame Spirits Spells
    SPELL_SUPERNOVA				= 75238,
    SPELL_SUPERNOVA_H			= 90972,
};

enum Phase
{
    PHASE_CASTER_PHASE	= 1,
    PHASE_DRAGON_PHASE	= 2,
    PHASE_FINAL_PHASE	= 3,
    PHASE_NON			= 4,
};

enum Events
{
    EVENT_BURNING_SHADOWBOLT			= 1,
    EVENT_SUMMON_INVOKED_FLAME_SPIRIT	= 2,
    EVENT_VALIONAS_FLAME				= 3,
    EVENT_SHREDDING_SWIPE				= 4,
    EVENT_SEEPING_TWILIGHT				= 5,
    EVENT_DEVOURING_FLAMES				= 6,
    EVENT_DRAGAH_ENTER_VEHICLE			= 7,
};

enum Actions
{
    ACTION_DRAGAH_CALLS_VALIONA_FOR_HELP	= 1,
    ACTION_VALIONA_SHOULD_FLY_AWAY			= 2,
    ACTION_DRAGAH_IS_ON_THE_GROUND			= 3,
};

enum Points
{
    POINT_VALIONA_FLY_IN_THE_AIR	= 1,
    POINT_VALIONA_LAND				= 2,
    POINT_VALIONA_FLY_AWAY			= 3,
    POINT_VALIONA_IS_AWAY			= 4,
    POINT_DRAHGA_GO_TO_THE_LAVA		= 5,
};

Position const position[5] =
{
    {-400.613f, -671.578f, 265.896f, 0.102f},	// Drahga Point from who he jump down
    {-388.189f, -668.078f, 280.316f, 3.470f},	// Valionas Way to the Platform
    {-435.54f, -695.072f, 280.316f, 3.4010f},
    {-435.54f, -695.072f, 268.687f, 3.4010f},	// Valiona first land Position
    {-375.742f, -519.749f, 300.663f, 0.0f}		// Valionas End Position
};

class boss_drahga_shadowburner : public CreatureScript
{
public:
    boss_drahga_shadowburner() : CreatureScript("boss_drahga_shadowburner") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_drahga_shadowburnerAI (creature);
    }

    struct boss_drahga_shadowburnerAI : public ScriptedAI
    {
        boss_drahga_shadowburnerAI(Creature* creature) : ScriptedAI(creature), summons(creature), pValiona(NULL)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        Phase phase;
        EventMap events;
        SummonList summons;

        Creature* pValiona;

        void Reset()
        {
			if (instance)
            //me->GetMotionMaster()->Clear();

            pValiona = NULL;

            SaveDespawnCreatures();

            phase = PHASE_NON;
        }

        void EnterCombat(Unit* /*pWho*/)
        {
			if (instance)if (instance)
            phase = PHASE_CASTER_PHASE;

            me->SetReactState(REACT_AGGRESSIVE);

            me->MonsterYell(SAY_AGGRO, LANG_UNIVERSAL, NULL);

            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveChase(me->GetVictim());

            events.ScheduleEvent(EVENT_BURNING_SHADOWBOLT, 4000);
            events.ScheduleEvent(EVENT_SUMMON_INVOKED_FLAME_SPIRIT, 10000);
        }

        void JustSummoned(Creature* summon)
        {
            if(summon->GetEntry() == NPC_INVOCATION_OF_THE_FLAME_STALKER)
            {
                summon->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE);

                summon->GetAI()->DoCast(SPELL_INVOCATION_TRIGGER);
            }

            DoZoneInCombat(summon);
        }

        void JustDied(Unit * /*victim*/)
        {
			if (instance)
            events.Reset();

            me->MonsterYell(SAY_DEAD, LANG_UNIVERSAL, NULL);

            SaveDespawnCreatures();
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type == POINT_MOTION_TYPE)
            {
                switch (id)
                {
                case POINT_DRAHGA_GO_TO_THE_LAVA:

                    me->MonsterYell(SAY_JUMP_DOWN, LANG_UNIVERSAL, NULL);

                    pValiona->GetAI()->DoAction(ACTION_DRAGAH_CALLS_VALIONA_FOR_HELP);
                    me->SetSpeed(MOVE_RUN, 1.0f);

                    me->GetMotionMaster()->Clear();
                    me->JumpTo(pValiona,2);

                    events.ScheduleEvent(EVENT_DRAGAH_ENTER_VEHICLE,2000);

                    break;

                default:
                    break;
                }
            }
        }

        void DoAction(const int32 action)
        {
            switch(action)
            {
            case ACTION_DRAGAH_IS_ON_THE_GROUND:

                //me->ExitVehicle();

                me->SetReactState(REACT_AGGRESSIVE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

                events.ScheduleEvent(EVENT_BURNING_SHADOWBOLT, 4000);
                events.ScheduleEvent(EVENT_SUMMON_INVOKED_FLAME_SPIRIT, 10000);

                break;

            default:
                break;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if(phase == PHASE_CASTER_PHASE && !HealthAbovePct(30))
            {
                phase = PHASE_DRAGON_PHASE;
                me->SetSpeed(MOVE_RUN, 1.5f);
                me->SetReactState(REACT_PASSIVE);

                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->RemoveAllAuras(); // He should not die when he is jumping down...

                DoCast(me, SPELL_TWILIGHT_PROTECTION, true);

                events.Reset(); // He Should not cast while he is flying
                me->GetMotionMaster()->MovePoint(POINT_DRAHGA_GO_TO_THE_LAVA, position[0]);

                pValiona = me->SummonCreature(NPC_VALIONA,-375.33f,-667.291f,270.0f,3.29545f, TEMPSUMMON_CORPSE_DESPAWN);
            }

            if(phase == PHASE_DRAGON_PHASE && !HealthAbovePct(10))
            {
                phase = PHASE_FINAL_PHASE;

                me->SetReactState(REACT_AGGRESSIVE);
                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MoveChase(me->GetVictim());

				me->RemoveAllAuras();
				
                //pValiona->GetAI()->DoAction(ACTION_VALIONA_SHOULD_FLY_AWAY);

                //pValiona = NULL;
            }

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_BURNING_SHADOWBOLT:

                    if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        DoCast(pTarget, RAID_MODE(SPELL_BURNING_SHADOWBOLT,SPELL_BURNING_SHADOWBOLT_H));

                    events.ScheduleEvent(EVENT_BURNING_SHADOWBOLT,4000);
                    break;
                case EVENT_SUMMON_INVOKED_FLAME_SPIRIT:

                    me->MonsterYell(SAY_SUMMON, LANG_UNIVERSAL, NULL);

                    DoCast(SPELL_INVOCATION_OF_FLAME);

                    events.ScheduleEvent(EVENT_SUMMON_INVOKED_FLAME_SPIRIT,20000);
                    break;

                case EVENT_DRAGAH_ENTER_VEHICLE:
                    me->GetMotionMaster()->Clear();

                    // me->EnterVehicle(pValiona, 1);
                    break;

                default:
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }

    private:

        void DespawnCreatures(uint32 entry, float distance)
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, entry, distance);

            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->DespawnOrUnsummon();
        }

        void SaveDespawnCreatures()
        {
            DespawnCreatures(NPC_INVOCATION_OF_THE_FLAME_STALKER,500.0f); // Maybe the Core crashes on unload the Trigger
            DespawnCreatures(NPC_INVOKED_FLAMING_SPIRIT,500.0f);
            DespawnCreatures(NPC_SEEPING_TWILIGHT_TRIGGER,500.0f);
            DespawnCreatures(NPC_VALIONA,500.0f);
        }
    };
};

class npc_valiona_gb : public CreatureScript
{
public:
    npc_valiona_gb() : CreatureScript("npc_valiona_gb") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_valiona_gbAI (creature);
    }

    struct npc_valiona_gbAI : public ScriptedAI
    {
        npc_valiona_gbAI(Creature* creature) : ScriptedAI(creature), summons(creature)//, vehicle(creature->GetVehicleKit())
        {
            //instance = creature->GetInstanceScript();

            //ASSERT(vehicle);
        }

        //InstanceScript* instance;
        EventMap events;
        uint8 currentWaypoint;
        SummonList summons;
        Unit* pDragah;

        // Vehicle* vehicle;

        void Reset()
        {
            me->SetSpeed(MOVE_WALK, 3.0f);

            me->SetCanFly(true);

            events.Reset();

            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            //me->GetMotionMaster()->MoveTargetedHome();
        }

        void EnterCombat(Unit* /*pWho*/) {}

        void JustSummoned(Creature* summon)
        {
            summon->setActive(true);

            if(summon->GetEntry() == NPC_SEEPING_TWILIGHT_TRIGGER)
            {
                summon->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE);
                summon->GetAI()->DoCast(SPELL_SEEPING_TWILIGHT);
            }

            if(me->IsInCombat())
                summon->AI()->DoZoneInCombat();
        }

        void IsSummonedBy(Unit* summoner)
        {
            pDragah = summoner;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim() || me-> HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.GetEvent())
            {
                switch (eventId)
                {
                case EVENT_VALIONAS_FLAME:
                    if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        DoCast(pTarget, SPELL_VALIONAS_FLAME);
                    events.RepeatEvent(urand(15000,25000));
                    break;

                case EVENT_SHREDDING_SWIPE:

                    if(me->GetVictim())
                        DoCastVictim(SPELL_SHREDDING_SWIPE);

                    events.RepeatEvent(urand(21000,30000));
                    break;

                case EVENT_DEVOURING_FLAMES:
                    DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), SPELL_DEVOURING_FLAMES_H);
                    events.RepeatEvent(urand(30000,35000));
                    break;

                default:
                    events.PopEvent();
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void DoAction(const int32 action)
        {
            switch(action)
            {
            case ACTION_DRAGAH_CALLS_VALIONA_FOR_HELP:
                DoZoneInCombat();

                me->MonsterYell(SAY_VALIONA, LANG_UNIVERSAL, NULL);

                currentWaypoint = 1;
                me->GetMotionMaster()->MovePoint(POINT_VALIONA_FLY_IN_THE_AIR, position[1]);
                break;

            case ACTION_VALIONA_SHOULD_FLY_AWAY:
                events.Reset();

                me->RemoveAllAuras();
                DoCast(me, SPELL_TWILIGHT_SHIFT, true);

                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

                me->SetCanFly(true);

                me->GetMotionMaster()->MovePoint(POINT_VALIONA_FLY_AWAY, position[1]);

                break;

            default:
                break;
            }
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type != POINT_MOTION_TYPE)
                return;

            switch (id)
            {
            case POINT_VALIONA_FLY_IN_THE_AIR:
                currentWaypoint++;

                if(currentWaypoint < 3) // You can extend the Waypoints by yourself if you want
                {
                    me->GetMotionMaster()->MovePoint(POINT_VALIONA_FLY_IN_THE_AIR, position[currentWaypoint]);
                }else
                    me->GetMotionMaster()->MovePoint(POINT_VALIONA_LAND, position[3]);

                break;

            case POINT_VALIONA_LAND:
                pDragah->GetAI()->DoAction(ACTION_DRAGAH_IS_ON_THE_GROUND);

                me->SetSpeed(MOVE_WALK, 1.0f);

                me->SetCanFly(false);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_AGGRESSIVE);

                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MoveChase(me->GetVictim());

                events.ScheduleEvent(EVENT_VALIONAS_FLAME, urand(4000,7000));
                events.ScheduleEvent(EVENT_SHREDDING_SWIPE, urand(10000,13000));

                if(/*me->GetMap()->IsHeroic()*/ true) // To test it on non heroic difficulty
                    events.ScheduleEvent(EVENT_DEVOURING_FLAMES, urand(15000,17000));
                break;

            case POINT_VALIONA_FLY_AWAY:
                DespawnCreatures(NPC_SEEPING_TWILIGHT_TRIGGER,500.0f);
                me->GetMotionMaster()->MovePoint(POINT_VALIONA_IS_AWAY, position[4]);
                break;

            case POINT_VALIONA_IS_AWAY:
                me->DespawnOrUnsummon();
                break;

            default:
                break;
            }
        }

    private:
        void DespawnCreatures(uint32 entry, float distance)
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, entry, distance);

            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->DespawnOrUnsummon();
        }
    };
};

class npc_invoked_flame_spirit : public CreatureScript
{
public:
    npc_invoked_flame_spirit() : CreatureScript("npc_invoked_flame_spirit") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_invoked_flame_spiritAI (creature);
    }

    struct npc_invoked_flame_spiritAI : public ScriptedAI
    {
        npc_invoked_flame_spiritAI(Creature* creature) : ScriptedAI(creature), pTarget(NULL) {}

        Unit* pTarget;

        void IsSummonedBy(Unit* summoner)
        {
            DoZoneInCombat();

            /*uint8 p = urand(0, me->GetMap()->GetPlayers().getSize());

            Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();

            if (!PlayerList.isEmpty())
            {
            for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
            {
            if(i == p)
            pTarget = i->GetSource();
            }
            }*/

            me->GetMotionMaster()->MoveChase(GetPlayerAtMinimumRange(1.0f));

            me->SetReactState(REACT_PASSIVE);
        }

        void UpdateAI(const uint32 Diff)
        {
            if (!UpdateVictim())
                return;

            if(me->GetDistance(me->GetVictim()) < 1.0f )
            {
                DoCastVictim(RAID_MODE(SPELL_SUPERNOVA,	SPELL_SUPERNOVA_H));
                me -> DespawnOrUnsummon();
            }
        }
    };
};

void AddSC_boss_drahga_shadowburner()
{
    new boss_drahga_shadowburner();
    new npc_valiona_gb();
    new npc_invoked_flame_spirit();
}