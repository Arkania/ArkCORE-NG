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
#include "GameObjectAI.h"

enum eAnimRedridgeCity
{
    NPC_DUMPY = 43249,
    NPC_BIG_EARL = 43248,
    NPC_MAGISTRATE_SOLOMON = 344,
    NPC_COLONEL_TROTEMAN_43221 = 43221,
    NPC_JOHN_J_KEESHAN_43184 = 43184,
    NPC_CAT = 8963,
    NPC_AREA_TRIGGER_BUNNY = 47971,
    NPC_MESSNER_43270 = 43270,
    NPC_MESSNER_43300 = 43300,
    NPC_JORGENSEN_43272 = 43272,
    NPC_JORGENSEN_43305 = 43305,
    NPC_KRAKAUER_43274 = 43274,
    NPC_KRAKAUER_43303 = 43303,
    NPC_DANFORTH_43275 = 43275,
    NPC_DANFORTH_43302 = 43302,
    NPC_DANFORT_INVISIBLE_DUMMY = 43366,
    GO_CHAIN_LEVER = 204403,
    SPELL_DRINK_ALCOHOL = 58952,
    SPELL_APPLY_QUEST_INVIS_1 = 80895,
    SPELL_APPLY_QUEST_INVIS_2 = 80699,
    SPELL_APPLY_QUEST_INVIS_3 = 80815,
    SPELL_APPLY_QUEST_INVIS_4 = 80816,
    SPELL_APPLY_QUEST_INVIS_5 = 81003,
    SPELL_APPLY_QUEST_INVIS_9 = 81201,
    SPELL_APPLY_QUEST_INVIS_10 = 81240,
    SPELL_DETECT_QUEST_INVIS_1 = 80695,
    SPELL_DETECT_QUEST_INVIS_2 = 80696,
    SPELL_DETECT_QUEST_INVIS_3 = 80817,
    SPELL_DETECT_QUEST_INVIS_4 = 80818,
    SPELL_DETECT_QUEST_INVIS_5 = 81004,
    SPELL_DETECT_QUEST_INVIS_6 = 81010,
    SPELL_DETECT_QUEST_INVIS_7 = 81019,
    SPELL_DETECT_QUEST_INVIS_8 = 81080,
    SPELL_DETECT_QUEST_INVIS_9 = 81202,
    SPELL_DETECT_QUEST_INVIS_10 = 81241,
    SPELL_SUMMON_MESSNER = 80893,
    SPELL_SUMMON_JORGENSEN = 80940,
    SPELL_SUMMON_KRAKAUER = 80941,
    SPELL_SUMMON_DANFORTH = 80943,
    SPELL_CONCENTRATION_AURA = 79963,
    SPELL_SEAL_OF_RIGHTEOUSNESS = 79962,
    SPELL_MOLTEN_ARMOR = 79849,
    SPELL_REDRIDGE_TEAM_AURA = 80925,
    // SPELL_ZONE_RESTICTION = 132108, spell is from 548
    SPELL_GNOMECORDER = 80689,
    SPELL_FREEING_DANFORT = 80887,
    SPELL_BAKER_TEAM_BROADCAST = 81155,
    SPELL_CHAINS_OF_CRUELTY_1 = 81081,
    SPELL_CHAINS_OF_CRUELTY_2 = 81085,
    QUEST_JOHN_J_KEESHAN = 26567,
    QUEST_THIS_AINT_MY_WAR = 26568,
    QUEST_TUNING_THE_GNOMECORDER = 26512,
    QUEST_JORGENSEN = 26560,
    QUEST_RETURN_OF_THE_BRAVO_COMPANY = 26563,
    QUEST_THEY_DREW_FIRST_BLOOD = 26607,
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

    enum eFightStatus
    {
        None,
        Dumpy,
        Keeshan
    };

    struct npc_big_earl_43248AI : public ScriptedAI
    {
        npc_big_earl_43248AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        Creature* m_dumpy;
        Creature* m_keeshan;
        eFightStatus m_FightStatus;
        eFightStatus m_FightStatusOld;

        void Reset() override
        {
            m_timer = 1000;
            m_dumpy = NULL;
            m_keeshan = NULL;
            m_FightStatus = eFightStatus::None;
            m_FightStatusOld = eFightStatus::None;
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (attacker->GetEntry() == NPC_DUMPY)
                damage = 0;
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (Player* player = who->ToPlayer())
                if (player->HasAura(SPELL_DETECT_QUEST_INVIS_9))
                {
                    m_FightStatus = eFightStatus::None;
                }
                else if (player->HasAura(SPELL_DETECT_QUEST_INVIS_4))
                {
                    m_FightStatus = eFightStatus::Keeshan;
                }
                else if (player->HasAura(SPELL_DETECT_QUEST_INVIS_3))
                {
                    m_FightStatus = eFightStatus::Dumpy;
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
            Player* player = me->FindNearestPlayer(20.0f); 

            if (!player)
                m_FightStatus = eFightStatus::None;

            if (m_FightStatus == m_FightStatusOld)
                return;

            printf("m_FightStatus= %u \n", m_FightStatus);

            m_dumpy = me->FindNearestCreature(NPC_DUMPY, 5.0f);
            m_keeshan = me->FindNearestCreature(NPC_JOHN_J_KEESHAN_43184, 5.0f);
                      

            switch (m_FightStatus)
            {
            case eFightStatus::None:
                me->RemoveAura(SPELL_APPLY_QUEST_INVIS_1);
                me->RemoveAura(SPELL_APPLY_QUEST_INVIS_4);
                me->RemoveAura(SPELL_APPLY_QUEST_INVIS_9);
                me->AttackStop();
                if (m_dumpy)
                {
                    m_dumpy->RemoveAura(SPELL_APPLY_QUEST_INVIS_3);
                    m_dumpy->AttackStop();
                }
                if (m_keeshan)
                {
                    m_keeshan->RemoveAura(SPELL_APPLY_QUEST_INVIS_4);
                    m_keeshan->AttackStop();
                }
                break;
            case eFightStatus::Dumpy:
                if (m_keeshan && m_FightStatusOld == eFightStatus::Keeshan)
                {
                    m_keeshan->RemoveAura(SPELL_APPLY_QUEST_INVIS_4);
                    me->RemoveAura(SPELL_APPLY_QUEST_INVIS_4);
                    m_keeshan->AttackStop();
                    me->AttackStop();
                }
                if (m_dumpy)
                {
                    m_dumpy->AddAura(SPELL_APPLY_QUEST_INVIS_3, m_dumpy);
                    me->AddAura(SPELL_APPLY_QUEST_INVIS_3, me);
                    m_dumpy->Attack(me, true);
                    me->Attack(m_dumpy, true);
                }
                break;
            case eFightStatus::Keeshan:
                if (m_dumpy && m_FightStatusOld == eFightStatus::Dumpy)
                {
                    m_dumpy->RemoveAura(SPELL_APPLY_QUEST_INVIS_3);
                    m_dumpy->AttackStop();
                    me->AttackStop();
                }
                if (m_keeshan)
                {
                    me->AddAura(SPELL_APPLY_QUEST_INVIS_4, me);
                    m_keeshan->AddAura(SPELL_APPLY_QUEST_INVIS_4, m_keeshan);
                    m_keeshan->Attack(me, true);
                    me->Attack(m_keeshan, true);
                }
                break;
            }
            
            m_FightStatusOld = m_FightStatus;
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
            player->KilledMonsterCredit(NPC_AREA_TRIGGER_BUNNY);
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

    bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* quest, uint32 /*opt*/) 
    { 
        if (quest->GetQuestId() == QUEST_THIS_AINT_MY_WAR)
        {
            player->RemoveAura(SPELL_DETECT_QUEST_INVIS_4);
        }
        if (quest->GetQuestId() == QUEST_RETURN_OF_THE_BRAVO_COMPANY)
        {
            if (Creature* messner = player->FindNearestCreature(NPC_MESSNER_43300, 300.0f))
                messner->DespawnOrUnsummon();

            if (Creature* jorgensen = player->FindNearestCreature(NPC_JORGENSEN_43305, 300.0f))
                jorgensen->DespawnOrUnsummon();

            if (Creature* krakauer = player->FindNearestCreature(NPC_KRAKAUER_43303, 300.0f))
                krakauer->DespawnOrUnsummon();

            if (Creature* danforth = player->FindNearestCreature(NPC_DANFORTH_43302, 300.0f))
                danforth->DespawnOrUnsummon();

            player->RemoveAura(SPELL_SUMMON_MESSNER);
            player->RemoveAura(SPELL_SUMMON_JORGENSEN);
            player->RemoveAura(SPELL_SUMMON_KRAKAUER);
            player->RemoveAura(SPELL_SUMMON_DANFORTH);
            player->RemoveAura(SPELL_DETECT_QUEST_INVIS_5);
            player->RemoveAura(SPELL_DETECT_QUEST_INVIS_6);
            player->RemoveAura(SPELL_DETECT_QUEST_INVIS_7);
            player->RemoveAura(SPELL_DETECT_QUEST_INVIS_8);
        }
        return false; 
    }

    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest) 
    { 
        if (quest->GetQuestId() == QUEST_RETURN_OF_THE_BRAVO_COMPANY)
        {
            player->AddAura(SPELL_DETECT_QUEST_INVIS_9, player);
        }
        return false; 
    }

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

        void MoveInLineOfSight(Unit* who) override
        {
            if (Player* player = who->ToPlayer())
                if (!HasPlayerSeenVideo(player->GetGUID()))
                    if (player->HasAura(SPELL_DETECT_QUEST_INVIS_3))
                        {
                            m_phase = 1;
                            m_playerList.push_back(player->GetGUID());
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

                break;
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
                m_timer = 60000; m_phase = 12;
                break;
            case 12:
                m_phase = 0;
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

class npc_john_j_keeshan_43184 : public CreatureScript
{
public:
    npc_john_j_keeshan_43184() : CreatureScript("npc_john_j_keeshan_43184") { }

    struct npc_john_j_keeshan_43184AI : public ScriptedAI
    {
        npc_john_j_keeshan_43184AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;

        void Reset() override
        {
            m_timer = 1000;
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (attacker->GetEntry() == NPC_DUMPY)
                damage = 0;

            if (attacker->GetEntry() == NPC_BIG_EARL)
                damage = 0;
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
          
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_john_j_keeshan_43184AI(creature);
    }
};

class npc_hilary_8962 : public CreatureScript
{
public:
    npc_hilary_8962() : CreatureScript("npc_hilary_8962") { }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        if (Creature* cat = creature->FindNearestCreature(NPC_CAT, 5.0f))
            cat->AI()->Talk(0);

        creature->AI()->Talk(0);
        return false;
    }
};

class npc_messner_43270 : public CreatureScript
{
public:
    npc_messner_43270() : CreatureScript("npc_messner_43270") { }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        creature->AI()->Talk(0);
        player->CastSpell(player, SPELL_SUMMON_MESSNER);
        return false;
    }
};

class npc_messner_43300 : public CreatureScript
{
public:
    npc_messner_43300() : CreatureScript("npc_messner_43300") { }

    struct npc_messner_43300AI : public ScriptedAI
    {
        npc_messner_43300AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;
        uint32 m_joke;

        void Reset() override
        {
            if (Player* player = me->GetCharmerOrOwnerOrSelf()->ToPlayer())
            {
                player->RemoveAura(SPELL_DETECT_QUEST_INVIS_5);
                player->AddAura(SPELL_DETECT_QUEST_INVIS_6, player);
                player->CastSpell(player, SPELL_GNOMECORDER);
            }
            
            me->CastSpell(me, SPELL_MOLTEN_ARMOR);
            me->SetReactState(REACT_DEFENSIVE);
            m_timer = 1000; 
            m_phase = 0;
            m_joke = urand(30, 60);
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
            if (me->IsInCombat())
            {
                m_joke = 45;
                return;
            }
            Player* player = me->GetCharmerOrOwnerOrSelf()->ToPlayer();
            switch (m_phase)
            {
            case 0:
                if (m_joke > 0)
                    m_joke -= 1;

                if (m_joke == 0)
                    switch (urand(1, 11))
                    {
                    case 1:
                        Talk(1);
                        m_joke = urand(30, 60);
                        break;
                    case 2:
                        Talk(2);
                        m_phase = 1;
                        m_timer = 5000;
                        break;
                    case 7:
                        Talk(7);
                        m_joke = urand(30, 60);
                        break;
                    case 8:
                        Talk(8);
                        m_joke = urand(30, 60);
                        break;
                    case 9:
                        Talk(9);
                        m_joke = urand(30, 60);
                        break;
                    case 10:
                        Talk(10);
                        m_joke = urand(30, 60);
                        break;
                    }
                break;
            case 1:
                Talk(3);
                m_phase = 0;
                m_joke = urand(30, 60);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            }

        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_messner_43300AI(creature);
    }
};

class npc_jorgensen_43272 : public CreatureScript
{
public:
    npc_jorgensen_43272() : CreatureScript("npc_jorgensen_43272") { }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        creature->AI()->Talk(0);
        
        player->CastSpell(player, SPELL_SUMMON_JORGENSEN);
        return false;
    }
};

class npc_jorgensen_43305 : public CreatureScript
{
public:
    npc_jorgensen_43305() : CreatureScript("npc_jorgensen_43305") { }

    struct npc_jorgensen_43305AI : public ScriptedAI
    {
        npc_jorgensen_43305AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;

        void Reset() override
        {
            if (Player* player = me->GetCharmerOrOwnerOrSelf()->ToPlayer())
            {
                player->RemoveAura(SPELL_DETECT_QUEST_INVIS_6);
                player->AddAura(SPELL_DETECT_QUEST_INVIS_7, player);
                player->AddAura(SPELL_REDRIDGE_TEAM_AURA, player);
                player->CastSpell(player, SPELL_GNOMECORDER);
            }

            me->AddAura(SPELL_CONCENTRATION_AURA, me);
            me->CastSpell(me, SPELL_SEAL_OF_RIGHTEOUSNESS);
            me->SetReactState(REACT_DEFENSIVE);
            m_timer = 1000; m_phase = 1;
        }

        void KilledUnit(Unit* victim) 
        { 
            Talk(1);
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

        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_jorgensen_43305AI(creature);
    }
};

class npc_krakauer_43274 : public CreatureScript
{
public:
    npc_krakauer_43274() : CreatureScript("npc_krakauer_43274") { }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        creature->AI()->Talk(0);
        
        player->CastSpell(player, SPELL_SUMMON_KRAKAUER);
        return false;
    }
};

class npc_krakauer_43303 : public CreatureScript
{
public:
    npc_krakauer_43303() : CreatureScript("npc_krakauer_43303") { }

    struct npc_krakauer_43303AI : public ScriptedAI
    {
        npc_krakauer_43303AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;

        void Reset() override
        {
            if (Player* player = me->GetCharmerOrOwnerOrSelf()->ToPlayer())
            {
                player->RemoveAura(SPELL_DETECT_QUEST_INVIS_7);
                player->AddAura(SPELL_DETECT_QUEST_INVIS_8, player);
                player->AddAura(SPELL_REDRIDGE_TEAM_AURA, player);
                player->CastSpell(player, SPELL_GNOMECORDER);
            }

            me->SetReactState(REACT_DEFENSIVE);
            m_timer = 1000; m_phase = 1;
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

        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_krakauer_43303AI(creature);
    }
};

class npc_danforth_43275 : public CreatureScript
{
public:
    npc_danforth_43275() : CreatureScript("npc_danforth_43275") { }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        player->CastSpell(player, SPELL_SUMMON_DANFORTH);
        return false;
    }

    struct npc_danforth_43275AI : public ScriptedAI
    {
        npc_danforth_43275AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;
        
        void Reset() override
        {
            me->SetDisableGravity(true);
            me->GetMotionMaster()->MoveIdle();
            me->SetFacingTo(2.3f);
            m_timer = 1000; 
            m_phase = 2;
        }

        void FreeingDanforth()
        {
            m_timer = 250; m_phase = 1;
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
                break;
            case 1:
                me->GetMotionMaster()->MoveJump(-8805.83f, -2206.83f, 130.9454f, 10.0f, 5.0f);
                m_timer = 120000; m_phase = 2;
                break;
            case 2:
                me->GetMotionMaster()->MoveJump(-8805.83f, -2206.83f, 144.3343f, 10.0f, 5.0f);
                me->HandleEmoteState(EMOTE_ONESHOT_NONE);
                me->SetFacingTo(2.3f);
               // me->GetMotionMaster()->MoveIdle();
                m_timer = 0; m_phase = 0;
                break;
            case 3:
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_danforth_43275AI(creature);
    }
};

class npc_danforth_43302 : public CreatureScript
{
public:
    npc_danforth_43302() : CreatureScript("npc_danforth_43302") { }

    struct npc_danforth_43302AI : public ScriptedAI
    {
        npc_danforth_43302AI(Creature *c) : ScriptedAI(c) { m_NewSpawned = true; }

        uint32 m_timer;
        uint32 m_phase;
        bool m_NewSpawned;

        void Reset() override
        {
            if (Player* player = me->GetCharmerOrOwnerOrSelf()->ToPlayer())
            {
                player->RemoveAura(SPELL_DETECT_QUEST_INVIS_8);
                player->AddAura(SPELL_REDRIDGE_TEAM_AURA, player);
                player->AddAura(SPELL_REDRIDGE_TEAM_AURA, me);
                player->CastSpell(player, SPELL_GNOMECORDER);
            }

            me->SetReactState(REACT_DEFENSIVE);
            m_timer = 1000; m_phase = 1;
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
                break;
            case 1:
                if (m_NewSpawned)
                {
                    // Danforth is only swimming.. he walk not upto land.. so i teleport him.. 
                    me->NearTeleportTo(-8819.81f, -2188.81f, 138.765f, 2.3f);
                    m_NewSpawned = false;
                }
                Talk(6);
                m_timer = 0; m_phase = 0;
                break;
            case 2:
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_danforth_43302AI(creature);
    }
};

class spell_freeing_danforth : public SpellScriptLoader
{
public:
    spell_freeing_danforth() : SpellScriptLoader("spell_freeing_danforth") { }

    class spell_freeing_danforth_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_freeing_danforth_SpellScript);

        void OpenLock(SpellEffIndex effIndex)
        {
            if (Unit* unit = this->GetCaster())
                if (Creature* danforth = unit->FindNearestCreature(NPC_DANFORTH_43275, 100.0f))
                    CAST_AI(npc_danforth_43275::npc_danforth_43275AI, danforth->AI())->FreeingDanforth();
        }

        void Register() OVERRIDE
        {
            OnEffectLaunch += SpellEffectFn(spell_freeing_danforth_SpellScript::OpenLock, EFFECT_0, SPELL_EFFECT_OPEN_LOCK);
        }
    };

    SpellScript* GetSpellScript() const OVERRIDE
    {
        return new spell_freeing_danforth_SpellScript();
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
    new npc_john_j_keeshan_43184();
    new npc_hilary_8962();
    new npc_messner_43270();
    new npc_messner_43300();
    new npc_jorgensen_43272();
    new npc_jorgensen_43305();
    new npc_krakauer_43274();
    new npc_krakauer_43303();
    new npc_danforth_43275();
    new npc_danforth_43302();
    new spell_freeing_danforth();

}

