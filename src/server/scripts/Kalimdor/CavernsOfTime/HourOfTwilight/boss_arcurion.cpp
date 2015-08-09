/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "hour_of_twilight.h"

enum Spells
{
    // Frozen Servitor
    SPELL_SUMMON_VISUAL     = 103595,
    SPELL_ICE_THROW         = 105433,

    // Crystal Elementar
    SPELL_DRILL             = 104019,
};

enum Texts
{
    // Arcurion Inro
    SAY_SUMMON_1    = 0,
    SAY_SUMMON_2    = 1,
    SAY_SUMMON_3    = 2,

    // Thrall Gauntlet
    SAY_INTRO_1     = 0,
    SAY_INTRO_2     = 1,
    SAY_INTRO_3     = 2,
    SAY_INTRO_4     = 3,
};

enum Events
{
    //Thrall Gauntlet
    EVENT_MOVE_THRALL_1     = 1,
    EVENT_TALK_SUMMON_1     = 2,
    EVENT_MOVE_THRALL_2     = 3,
    EVENT_ARCURION_SPEAK_1  = 4,

    //Frozen Servitor
    EVENT_THROW_ICE         = 10,

    //Crytsal Elementar
    EVENT_DRILL             = 11,
};

enum Actions
{
    ACTION_START_GAUNTLET   = 1,
    ACTION_SUMMON_WAVE_1    = 2,
    ACTION_SUMMON_WAVE_2    = 3,
    ACTION_SUMMON_WAVE_3    = 4,
};

enum MovePoints
{
    POINT_SUMMON_1      = 1,
    POINT_2             = 2,
    POINT_SUMMON_2      = 3,
    POINT_SUMMON_3      = 4,
};

class boss_arcurion : public CreatureScript
{
public:
    boss_arcurion() : CreatureScript("boss_arcurion") { }

    struct boss_arcurionAI : public BossAI
    {
        boss_arcurionAI(Creature* creature) : BossAI(creature, DATA_ARCURION)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_NPC);
            me->SetReactState(REACT_PASSIVE);
            me->setActive(true);
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_SUMMON_WAVE_1:
                    Talk(SAY_SUMMON_1);
                    break;
                case ACTION_SUMMON_WAVE_2:
                    Talk(SAY_SUMMON_2);
                    break;
                case ACTION_SUMMON_WAVE_3:
                    Talk(SAY_SUMMON_3);
                    break;
            }
        }

        void Reset()
        {
            events.Reset();
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_arcurionAI(creature);
    }
};

Position const ThrallPoint1     = {4927.879f, 288.885f, 96.859f, 0.0f};
Position const ThrallPoint2     = {4926.836f, 260.515f, 97.087f, 0.0f};
Position const ThrallPoint3     = {4901.766f, 217.124f, 99.228f, 0.0f};
Position const ThrallPoint4     = {4878.831f, 180.001f, 99.175f, 0.0f};

const Position Gauntlet1[] =
{
    {4921.772f, 267.9514f, 97.37627f, 1.500983f},
    {4936.924f, 267.9323f, 97.67499f, 1.815142f},
};

Position const CrystalSpawn1 = {4888.479f, 198.4549f, 99.99197f, 0.9948376f};
const Position Gauntlet2[] =
{
    {4911.641f, 226.0347f, 99.13889f, 3.577925f},
    {4905.202f, 230.7309f, 99.15278f, 4.520403f},
};


class boss_thrall_1 : public CreatureScript
{
public:
    boss_thrall_1() : CreatureScript("boss_thrall_1") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Yes, Thrall.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        player->SEND_GOSSIP_MENU(45000, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 /*uiAction*/)
    {
        player->PlayerTalkClass->ClearMenus();
        player->CLOSE_GOSSIP_MENU();
        creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        creature->AI()->DoAction(ACTION_START_GAUNTLET);
        return true;
    }

    struct boss_thrall_1AI : public BossAI
    {
        boss_thrall_1AI(Creature* creature) : BossAI(creature, DATA_THRALL_1)
        {
            me->SetReactState(REACT_PASSIVE);
            killcounter = 0;
            check1 = false;
            check2 = true;
            check3 = true;
        }

        uint8 killcounter;
        bool check1;
        bool check2;
        bool check3;

        void JustSummoned(Creature* summon)
        {
            switch (summon->GetEntry())
            {
                case NPC_CRYSTAL_ELEMENTAR:
                    if (Creature* trigger = summon->FindNearestCreature(55389, 1.5f))
                        trigger->CastSpell(trigger, SPELL_SUMMON_VISUAL);
                    if (Creature* trigger = summon->FindNearestCreature(55384, 1.5f))
                        trigger->CastSpell(trigger, SPELL_SUMMON_VISUAL);
                    if (Creature* trigger = summon->FindNearestCreature(55385, 1.5f))
                        trigger->CastSpell(trigger, SPELL_SUMMON_VISUAL);
                    break;
                case NPC_FROZEN_SERVITOR:
                    if (Creature* trigger = summon->FindNearestCreature(55389, 1.5f))
                        trigger->CastSpell(trigger, SPELL_SUMMON_VISUAL);
                    if (Creature* trigger = summon->FindNearestCreature(55384, 1.5f))
                        trigger->CastSpell(trigger, SPELL_SUMMON_VISUAL);
                    if (Creature* trigger = summon->FindNearestCreature(55385, 1.5f))
                        trigger->CastSpell(trigger, SPELL_SUMMON_VISUAL);
                    break;
            }
        }

        void Counter()
        {
            killcounter++;

            if (killcounter == 2 && !check1)
            {
                me->GetMotionMaster()->MovePoint(POINT_2, ThrallPoint2);
                Talk(SAY_INTRO_3);
                check1 = true;
                killcounter = 0;
                check2 = false;
            }

            if (killcounter == 3 && !check2)
            {
                me->GetMotionMaster()->MovePoint(POINT_SUMMON_3, ThrallPoint4);
                check2 = true;
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
                case ACTION_START_GAUNTLET:
                    Talk(SAY_INTRO_1);
                    events.ScheduleEvent(EVENT_MOVE_THRALL_1, 10000);
                    break;
            }
        }

        void MovementInform(uint32 /*type*/, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_SUMMON_1:
                    break;
                case POINT_2:
                    events.ScheduleEvent(EVENT_MOVE_THRALL_2, 1);
                    break;
                case POINT_SUMMON_2:
                    for (uint32 x = 0; x<2; ++x)
                        me->SummonCreature(NPC_FROZEN_SERVITOR, Gauntlet2[x], TEMPSUMMON_MANUAL_DESPAWN, 20000);
                    me->SummonCreature(NPC_CRYSTAL_ELEMENTAR, CrystalSpawn1, TEMPSUMMON_MANUAL_DESPAWN, 20000);
                    events.ScheduleEvent(EVENT_ARCURION_SPEAK_1, 5000);
                    Talk(SAY_INTRO_4);
                    break;
                case POINT_SUMMON_3:
                    if (Creature* arcurion = me->FindNearestCreature(BOSS_ARCURION, 1000.0f))
                        arcurion->AI()->DoAction(ACTION_SUMMON_WAVE_3);
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while(uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_MOVE_THRALL_1:
                        if (Creature* arcurion = me->FindNearestCreature(BOSS_ARCURION, 1000.0f))
                            arcurion->AI()->DoAction(ACTION_SUMMON_WAVE_1);
                        for (uint32 x = 0; x<2; ++x)
                            me->SummonCreature(NPC_FROZEN_SERVITOR, Gauntlet1[x], TEMPSUMMON_MANUAL_DESPAWN, 20000);
                        events.ScheduleEvent(EVENT_TALK_SUMMON_1, 22000);
                        break;
                    case EVENT_TALK_SUMMON_1:
                        Talk(SAY_INTRO_2);
                        break;
                    case EVENT_MOVE_THRALL_2:
                        me->GetMotionMaster()->MovePoint(POINT_SUMMON_2, ThrallPoint3);
                        break;
                    case EVENT_ARCURION_SPEAK_1:
                        if (Creature* arcurion = me->FindNearestCreature(BOSS_ARCURION, 1000.0f))
                            arcurion->AI()->DoAction(ACTION_SUMMON_WAVE_2);
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_thrall_1AI(creature);
    }
};

class npc_frozen_servitor : public CreatureScript
{
public:
    npc_frozen_servitor() : CreatureScript("npc_frozen_servitor") { }

    struct npc_frozen_servitorAI : public CreatureAI
    {
        npc_frozen_servitorAI(Creature* creature) : CreatureAI(creature)
        {
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void IsSummonedBy(Unit* /*summoner*/)
        {
            Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_THROW_ICE, urand(5000, 10000));
        }

        void UpdateAI(uint32 /*diff*/)
        {
            if (!UpdateVictim())
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_THROW_ICE:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            DoCast(target, SPELL_ICE_THROW);
                        events.ScheduleEvent(EVENT_THROW_ICE, urand(8000, 12000));
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*who*/)
        {
            if (Creature* thrall = me->FindNearestCreature(NPC_THRALL_1, 1000.0f, true))
                if (boss_thrall_1::boss_thrall_1AI* _AI = CAST_AI(boss_thrall_1::boss_thrall_1AI, thrall->AI()))
                    _AI->Counter();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_frozen_servitorAI(creature);
    }
};

class npc_crystal_elementar : public CreatureScript
{
public:
    npc_crystal_elementar() : CreatureScript("npc_crystal_elementar") { }

    struct npc_crystal_elementarAI : public CreatureAI
    {
        npc_crystal_elementarAI(Creature* creature) : CreatureAI(creature)
        {
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_DRILL, urand(5000, 10000));
        }

        void UpdateAI(uint32 /*diff*/)
        {
            if (!UpdateVictim())
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_DRILL:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true, 0))
                            DoCast(target, SPELL_DRILL);
                        events.ScheduleEvent(EVENT_DRILL, urand(8000, 12000));
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*who*/)
        {
            if (Creature* thrall = me->FindNearestCreature(NPC_THRALL_1, 1000.0f, true))
                if (boss_thrall_1::boss_thrall_1AI* _AI = CAST_AI(boss_thrall_1::boss_thrall_1AI, thrall->AI()))
                    _AI->Counter();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_crystal_elementarAI(creature);
    }
};

void AddSC_boss_arcurion()
{
    new boss_arcurion();
    new boss_thrall_1();
    new npc_frozen_servitor();
    new npc_crystal_elementar();
}