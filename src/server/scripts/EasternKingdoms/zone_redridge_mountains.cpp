/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2014 ArkCORE <http://www.arkania.net/>
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

/* Script Data Start
SDName: Redridge Mountains
SD%Complete: 0
SDComment:
Script Data End */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "Player.h"

enum eAnimRedridgeCity
{
    NPC_DUMPY = 43249,
    NPC_BIG_EARL = 43248,
    NPC_MAGISTRATE_SOLOMON = 344,
    NPC_COLONEL_TROTEMAN_43221 = 43221,
    NPC_JOHN_J_KEESHAN_43184 = 43184,
    SPELL_DRINK_ALCOHOL = 58952,
    SPELL_APPLY_QUEST_INVIS_1 = 80895,
    SPELL_APPLY_QUEST_INVIS_2 = 80699,
    SPELL_APPLY_QUEST_INVIS_3 = 80815,
    SPELL_APPLY_QUEST_INVIS_4 = 80816,
    SPELL_APPLY_QUEST_INVIS_5 = 81003,
    SPELL_DETECT_QUEST_INVIS_4 = 80818,
    QUEST_JOHN_J_KEESHAN = 26567,
    QUEST_TUNING_THE_GNOMECORDER = 26512,

};

class npc_marshal_marris : public CreatureScript
{
public:
    npc_marshal_marris() : CreatureScript("npc_marshal_marris") { }

    struct npc_marshal_marrisAI : public ScriptedAI
    {
        npc_marshal_marrisAI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;

        void Reset() override
        {
            m_timer = urand(6000, 10000); 
            m_phase = 0;
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_timer <= diff)
            {
                m_timer = urand(6000, 10000);
                me->CastSpell(me, SPELL_DRINK_ALCOHOL);
            }
            else
                m_timer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_marshal_marrisAI(creature);
    }
};

class npc_dumpy_43249 : public CreatureScript
{
public:
    npc_dumpy_43249() : CreatureScript("npc_dumpy_43249") { }

    struct npc_dumpy_43249AI : public ScriptedAI
    {
        npc_dumpy_43249AI(Creature *c) : ScriptedAI(c) { }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (attacker->GetEntry() == NPC_BIG_EARL)
                damage = 0;
        }
      
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_dumpy_43249AI(creature);
    }
};

class npc_big_earl_43248 : public CreatureScript
{
public:
    npc_big_earl_43248() : CreatureScript("npc_big_earl_43248") { }

    struct npc_big_earl_43248AI : public ScriptedAI
    {
        npc_big_earl_43248AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;
        Creature* m_dumpy;
        Creature* m_keeshan;
        int32 m_questCooldown;

        void Reset() override
        {
            m_timer = 1000;
            m_phase = 0;
            m_dumpy = NULL;
            m_keeshan = NULL;
            m_questCooldown = 0;
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (attacker->GetEntry() == NPC_DUMPY)
                damage = 0;
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_questCooldown>0)
                m_questCooldown -= diff;

            if (m_timer <= diff)
            {
                m_timer = 1000;
                DoWork();
            }
            else
                m_timer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }


        void DoWork()
        {
            Player* player = me->FindNearestPlayer(20.0f);
            m_dumpy = me->FindNearestCreature(NPC_DUMPY, 5.0f);
            m_keeshan = me->FindNearestCreature(NPC_JOHN_J_KEESHAN_43184, 5.0f);
            switch (m_phase)
            {
            case 0: 
                if (player && player->m_positionZ < 65.0f)
                    if (player->GetQuestStatus(QUEST_JOHN_J_KEESHAN) == QUEST_STATUS_INCOMPLETE)
                    {
                        if (m_dumpy)
                            m_dumpy->DespawnOrUnsummon();

                        if (!m_keeshan)
                            m_keeshan = me->SummonCreature(NPC_JOHN_J_KEESHAN_43184, -9203.84f, -2155.79f, 57.187f, 3.565f, TEMPSUMMON_TIMED_DESPAWN, 600000);

                        if (!m_keeshan->IsInCombat())
                        {
                            m_keeshan->Attack(me, true);
                            me->Attack(m_keeshan, true);
                        }
                        m_phase = 2; m_timer = 100;
                    }
                    else
                    {
                        if (m_keeshan)
                            m_keeshan->DespawnOrUnsummon();

                        if (!m_dumpy)
                            m_dumpy = me->SummonCreature(NPC_DUMPY, -2101.98f, -2154.78f, 57.19f, 1.659f);

                        if (m_dumpy && !m_dumpy->IsInCombat())
                        {
                            m_dumpy->Attack(me, true);
                            me->Attack(m_dumpy, true);
                        }
                    }
                break;
            case 1: 
                break;
            case 2: // fighting against john until player is gone
                if (!player)
                {
                    m_phase = 3; m_timer = 100;
                }
                else if (player->m_positionZ > 65.0f)
                {
                    m_phase = 3; m_timer = 100;
                }
                break;
            case 3:
                if (m_keeshan)
                    m_keeshan->DespawnOrUnsummon();

                if (!m_dumpy)
                    m_dumpy = me->SummonCreature(NPC_DUMPY, -2101.98f, -2154.78f, 57.19f, 1.659f);

                if (m_dumpy && !m_dumpy->IsInCombat())
                {
                    m_dumpy->Attack(me, true);
                    me->Attack(m_dumpy, true);
                }

                m_phase = 0;
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_big_earl_43248AI(creature);
    }
};

class npc_redrige_citizen_43247 : public CreatureScript
{
public:
    npc_redrige_citizen_43247() : CreatureScript("npc_redrige_citizen_43247") { }

    struct npc_redrige_citizen_43247AI : public ScriptedAI
    {
        npc_redrige_citizen_43247AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;

        void Reset() override
        {
            m_timer = 1000;
        }


        void UpdateAI(uint32 diff) override
        {
            if (m_timer <= diff)
            {
                m_timer = 1000;
                DoWork();
            }
            else
                m_timer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }


        void DoWork()
        {
            if (uint32 r = urand(0, 500) < 11)
            {
                Talk(0); m_timer = 5000;
                switch (r)
                {
                case 0:
                    me->HandleEmote(1);
                    break;
                case 1:
                    me->HandleEmote(4);
                    break;
                case 2:
                    me->HandleEmote(5);
                    break;
                case 3:
                    me->HandleEmote(6);
                    break;
                case 4:
                    me->HandleEmote(14);
                    break;
                case 5:
                    me->HandleEmote(15);
                    break;
                case 6:
                    me->HandleEmote(20);
                    break;
                case 7:
                    me->HandleEmote(22);
                    break;
                case 8:
                    me->HandleEmote(25);
                    break;
                case 9:
                    me->HandleEmote(53);
                    break;
                case 10:
                    me->HandleEmote(274);
                    break;
                }
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_redrige_citizen_43247AI(creature);
    }
}; 

class at_lakeshire_graveyard : public AreaTriggerScript
{
public:
    at_lakeshire_graveyard() : AreaTriggerScript("at_lakeshire_graveyard") { }

    bool OnTrigger(Player* player, const AreaTriggerEntry* at) override
    {
        if ((player->GetQuestStatus(QUEST_TUNING_THE_GNOMECORDER) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_TUNING_THE_GNOMECORDER) == QUEST_STATUS_COMPLETE) && at->id == 6034)
        {
            player->SendPlaySound(18125, true);
            player->CastSpell(player, 81769, true);
            player->CompleteQuest(QUEST_TUNING_THE_GNOMECORDER);
        }

        return false;
    }
};

class npc_canyon_ettin_43197 : public CreatureScript
{
    enum eTest
    {
        NPC_HUGE_BOULDER = 43196,
        NPC_BRIDGE_WORKER_TRENT = 648,
        NPC_BRIDGE_WORKER_DMITRI = 649,
        NPC_BRIDGE_WORKER_JESS = 650,
        NPC_BRIDGE_WORKER_DANIEL = 651,
        NPC_BRIDGE_WORKER_MATTHEW = 652,
        NPC_BRIDGE_WORKER_ALEX = 653,
        NPC_FOREMAN_OSLOW = 341,
        SPELL_LIFT_HUGE_BOULDER = 80739,
        SPELL_KILL_CREDIT_ETTIN_QUEST = 80744,
        SPELL_EJECT_PASSENGER_1 = 80743,
        QUEST_SAVING_FOREMAN_OSLOW = 26520,
        PATH_GO_BACK_TO_MOUNTAIN = 431972,
        PATH_GO_TO_BRIDGE = 431971,
        SAY_OSLOW_JUST_REPAIR_BRIDGE = 0,
        SAY_OSLOW_THANKS = 1,
    };

public:
    npc_canyon_ettin_43197() : CreatureScript("npc_canyon_ettin_43197") { }

    struct npc_canyon_ettin_43197_AI : public ScriptedAI
    {
        npc_canyon_ettin_43197_AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;

        void Reset() override
        {
            m_timer = 1000;
            m_phase = 0;
        }

        void MovementInform(uint32 type, uint32 id) override
        { 
            if (type != 2)
                return;

            if (m_phase < 10)
            {
                switch (id)
                {
                case 1:
                    if (Creature* oslow = me->FindNearestCreature(NPC_FOREMAN_OSLOW, 200.0f))
                        oslow->AI()->Talk(SAY_OSLOW_THANKS);

                    break;
                case 4:
                        if (Creature* oslow = me->FindNearestCreature(NPC_FOREMAN_OSLOW, 200.0f))
                            oslow->DespawnOrUnsummon();

                    break;
                case 5: // last point in path 1
                    m_phase = 7; m_timer = 500;
                    break;
                }
            }
            else if (m_phase > 10)
            {
                switch (id)
                {
                case 3:
                    Talk(3);
                    break;
                case 5: // last point in path 2
                    m_phase = 12; m_timer = 500;
                    break;
                }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_timer <= diff)
            {
                m_timer = 1000;
                DoWork();
            }
            else
                m_timer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }


        void DoWork()
        {
            switch (m_phase)
            {
            case 0:
            {
                Player* player = NULL;
                if (Unit* unit = me->GetOwner())
                    if (player = unit->ToPlayer())
                        if (player->IsInCombat())
                            if (Unit* target = player->GetSelectedUnit())
                                if (Creature* victim = target->ToCreature())
                                    if (me->IsInCombat())
                                    {
                                        if (!me->IsHostileTo(target))
                                            me->Attack(victim, true);
                                    }
                                    else
                                        me->Attack(victim, true);

                if (Creature* boulder = me->FindNearestCreature(NPC_HUGE_BOULDER, 8.0f))
                {
                    me->GetMotionMaster()->MoveIdle();
                    me->GetMotionMaster()->Initialize();
                    m_phase = 1;
                }
                m_timer = 100;
                break;
            }
            case 1:
                if (Creature* boulder = me->FindNearestCreature(NPC_HUGE_BOULDER, 15.0f))
                    me->CastSpell(boulder, SPELL_LIFT_HUGE_BOULDER, true);
                if (Creature* trent = me->FindNearestCreature(NPC_BRIDGE_WORKER_TRENT, 50.0f))
                    trent->HandleEmoteState(EMOTE_STATE_STAND);
                if (Creature* dmitri = me->FindNearestCreature(NPC_BRIDGE_WORKER_DMITRI, 50.0f))
                    dmitri->HandleEmoteState(EMOTE_STATE_STAND);
                if (Creature* jess = me->FindNearestCreature(NPC_BRIDGE_WORKER_JESS, 50.0f))
                    jess->HandleEmoteState(EMOTE_STATE_STAND);
                if (Creature* daniel = me->FindNearestCreature(NPC_BRIDGE_WORKER_DANIEL, 50.0f))
                    daniel->HandleEmoteState(EMOTE_STATE_STAND);
                if (Creature* matthew = me->FindNearestCreature(NPC_BRIDGE_WORKER_MATTHEW, 50.0f))
                    matthew->HandleEmoteState(EMOTE_STATE_STAND);
                if (Creature* alex = me->FindNearestCreature(NPC_BRIDGE_WORKER_ALEX, 50.0f))
                    alex->HandleEmoteState(EMOTE_STATE_STAND);

                Talk(0);
                m_phase = 2; m_timer = 2000;
                break;
            case 2:
                if (Creature* oslow = me->FindNearestCreature(NPC_FOREMAN_OSLOW, 100.0f))
                {
                    oslow->SetUInt32Value(UNIT_FIELD_BYTES_1, UNIT_STAND_STATE_KNEEL);
                    oslow->SetWalk(true);
                    oslow->SetSpeed(MOVE_WALK, 1.0f, true);
                }

                m_phase = 3; m_timer = 2000;
                break;
            case 3:
                Talk(1);
                m_phase = 4; m_timer = 4000;
                break;
            case 4:
                if (Creature* trent = me->FindNearestCreature(NPC_BRIDGE_WORKER_TRENT, 50.0f))
                    trent->AI()->Talk(1);
                if (Creature* daniel = me->FindNearestCreature(NPC_BRIDGE_WORKER_DANIEL, 50.0f))
                    daniel->AI()->Talk(1);
                if (Creature* oslow = me->FindNearestCreature(NPC_FOREMAN_OSLOW, 100.0f))
                    oslow->HandleEmoteState(EMOTE_STATE_STAND);

                m_phase = 5; m_timer = 1500;
                break;
            case 5:
                if (Creature* oslow = me->FindNearestCreature(NPC_FOREMAN_OSLOW, 100.0f))
                {
                    oslow->SetWalk(true);
                    oslow->GetMotionMaster()->MovePoint(22, -9273.9f, -2185.4f, 64.09f);
                }

                m_phase = 6; m_timer = 1500;
                break;
            case 6:

                if (Creature* oslow = me->FindNearestCreature(NPC_FOREMAN_OSLOW, 100.0f))
                    oslow->AI()->Talk(SAY_OSLOW_JUST_REPAIR_BRIDGE);

                Talk(2);
                me->SetWalk(true);
                me->SetSpeed(MOVE_WALK, 1.2f, true);
                me->GetMotionMaster()->MovePath(PATH_GO_TO_BRIDGE, false);
                m_phase = 9; m_timer = 120000;
                break;           
            case 7:
                me->CastSpell(me, SPELL_EJECT_PASSENGER_1);

               // if (Creature* boulder = me->FindNearestCreature(NPC_HUGE_BOULDER, 15.0f))
                 //   boulder->GetMotionMaster()->MoveJumpTo(me->GetOrientation(), 150.0f, 4.0f);

                m_phase = 8; m_timer = 2000;
                break;
            case 8:
                me->GetMotionMaster()->InitDefault();
                m_phase = 11; m_timer = 2000;
                break;
            case 9: // cooldown phase
                m_phase = 13; m_timer = 100;
                break;            
            case 11:
               // if (Creature* boulder = me->FindNearestCreature(NPC_HUGE_BOULDER, 30.0f))
                 //   boulder->DespawnOrUnsummon(1000);

                me->SetWalk(true);
                me->GetMotionMaster()->MovePath(PATH_GO_BACK_TO_MOUNTAIN, false);  // path 2

                m_phase = 13; m_timer = 120000;
                break;
            case 12:
                if (Unit* unit = me->GetOwner())
                    if (Player* player = unit->ToPlayer())
                    {
                        player->CastSpell(player, SPELL_KILL_CREDIT_ETTIN_QUEST);
                        player->KilledMonsterCredit(341);
                    }

                m_phase = 13; m_timer = 1000;
                break;
            case 13:
                if (Creature* boulder = me->FindNearestCreature(NPC_HUGE_BOULDER, 200.0f))
                    boulder->DespawnOrUnsummon();
                if (Creature* trent = me->FindNearestCreature(NPC_BRIDGE_WORKER_TRENT, 100.0f))
                    trent->DespawnOrUnsummon();
                if (Creature* dmitri = me->FindNearestCreature(NPC_BRIDGE_WORKER_DMITRI, 100.0f))
                    dmitri->DespawnOrUnsummon();
                if (Creature* jess = me->FindNearestCreature(NPC_BRIDGE_WORKER_JESS, 100.0f))
                    jess->DespawnOrUnsummon();
                if (Creature* daniel = me->FindNearestCreature(NPC_BRIDGE_WORKER_DANIEL, 100.0f))
                    daniel->DespawnOrUnsummon();
                if (Creature* matthew = me->FindNearestCreature(NPC_BRIDGE_WORKER_MATTHEW, 100.0f))
                    matthew->DespawnOrUnsummon();
                if (Creature* alex = me->FindNearestCreature(NPC_BRIDGE_WORKER_ALEX, 100.0f))
                    alex->DespawnOrUnsummon();
                
                me->DespawnOrUnsummon();

                m_phase = 0; m_timer = 1000;
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_canyon_ettin_43197_AI(creature);
    }
   
};

class npc_colonel_troteman_43221 : public CreatureScript
{
public:
    npc_colonel_troteman_43221() : CreatureScript("npc_colonel_troteman_43221") { }

    struct npc_colonel_troteman_43221AI : public ScriptedAI
    {
        npc_colonel_troteman_43221AI(Creature *c) : ScriptedAI(c) { }

        std::list<uint64> m_playerList;
        uint32 m_timer;
        uint32 m_phase;

        void Reset() override
        {
            m_timer = 1000;
            m_phase = 0;
        }


        void UpdateAI(uint32 diff) override
        {
            if (m_timer <= diff)
            {
                m_timer = 1000;
                DoWork();
            }
            else
                m_timer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }


        void DoWork()
        {
            switch (m_phase)
            {
            case 0:
                if (Player* player = me->FindNearestPlayer(15.0))
                    if (!HasPlayerSeenVideo(player->GetGUID()) && !player->HasAura(SPELL_DETECT_QUEST_INVIS_4))
                    {
                        m_phase = 1;
                        m_playerList.push_back(player->GetGUID());
                    }
            case 1:
                if (Creature* solomon = me->FindNearestCreature(NPC_MAGISTRATE_SOLOMON, 10.0f))
                    solomon->AI()->Talk(0);

                m_timer = 5000; m_phase = 2;
                break;
            case 2:
                if (Creature* solomon = me->FindNearestCreature(NPC_MAGISTRATE_SOLOMON, 10.0f))
                    solomon->AI()->Talk(1);

                m_timer = 5000; m_phase = 3;
                break;
            case 3:
                Talk(0);
                m_timer = 5000; m_phase = 4;
                break;
            case 4:
                if (Creature* solomon = me->FindNearestCreature(NPC_MAGISTRATE_SOLOMON, 10.0f))
                    solomon->AI()->Talk(2);

                m_timer = 5000; m_phase = 5;
                break;
            case 5:
                Talk(1);
                m_timer = 5000; m_phase = 6;
                break;
            case 6:
                Talk(2);
                m_timer = 5000; m_phase = 7;
                break;
            case 7:
                Talk(3);
                m_timer = 5000; m_phase = 8;
                break;
            case 8:
                Talk(4);
                m_timer = 5000; m_phase = 9;
                break;
            case 9:
                if (Creature* solomon = me->FindNearestCreature(NPC_MAGISTRATE_SOLOMON, 10.0f))
                    solomon->AI()->Talk(3);

                m_timer = 5000; m_phase = 10;
                break;
            case 10:
                Talk(5);
                m_timer = 5000; m_phase = 11;
                break;
            case 11:
                m_phase = 0; 
                break;
            case 12:
                break;
            }
        }

        bool HasPlayerSeenVideo(uint64 guid)
        {
            for (std::list<uint64>::iterator itr = m_playerList.begin(); itr != m_playerList.end(); ++itr)
                if (guid == *itr)
                    return true;

            return false;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_colonel_troteman_43221AI(creature);
    }
};

void AddSC_redridge_mountains()
{
    new npc_marshal_marris();
    new npc_dumpy_43249();
    new npc_big_earl_43248();
    new npc_redrige_citizen_43247();
    new at_lakeshire_graveyard();
    new npc_canyon_ettin_43197();
    new npc_colonel_troteman_43221();
}

