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
#include "Vehicle.h"

enum eAnimRedridgeCity
{
    NPC_DUMPY = 43249,
    NPC_BIG_EARL = 43248,
    NPC_MAGISTRATE_SOLOMON = 344,
    NPC_COLONEL_TROTEMAN_43221 = 43221,
    NPC_JOHN_J_KEESHAN_43184 = 43184,
    NPC_KRAKAUER_43434 = 43434,
    NPC_DANFORTH_43435 = 43435,
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
    SPELL_KEESHANS_HEADBAND = 81234,
    QUEST_JOHN_J_KEESHAN = 26567,
    QUEST_THIS_AINT_MY_WAR = 26568,
    QUEST_TUNING_THE_GNOMECORDER = 26512,
    QUEST_BREAKING_OUT_IS_HARD_TO_DO = 26587,
    QUEST_JORGENSEN = 26560,
    QUEST_RETURN_OF_THE_BRAVO_COMPANY = 26563,
    QUEST_THEY_DREW_FIRST_BLOOD = 26607,
    QUEST_ITS_NEVER_OVER = 26616,
    AREA_CAMP_EVERSTILL = 5326,
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
        if (quest->GetQuestId() == QUEST_THEY_DREW_FIRST_BLOOD)
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

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_ITS_NEVER_OVER)
        {
            player->AddAura(SPELL_DETECT_QUEST_INVIS_10, player);
            creature->AI()->Talk(0);

            if (Creature* krakauer = creature->FindNearestCreature(NPC_KRAKAUER_43434, 10.0f))
                krakauer->AI()->Talk(0);

            if (Creature* danforth = creature->FindNearestCreature(NPC_DANFORTH_43435, 10.0f))
                danforth->AI()->Talk(0);

            player->RemoveAura(SPELL_GNOMECORDER);
        }
        return false;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        if (quest->GetQuestId() == QUEST_THEY_DREW_FIRST_BLOOD)
        {
            creature->CastSpell(creature, SPELL_KEESHANS_HEADBAND);
        }
        return false;
    }

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
        if (quest->GetQuestId() == QUEST_BREAKING_OUT_IS_HARD_TO_DO)
        {
            CAST_AI(npc_messner_43270AI, creature->AI())->StartAnim(player);
        }
        return false;
    }

    struct npc_messner_43270AI : public ScriptedAI
    {
        npc_messner_43270AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;
        Player* m_player;

        void Reset() override
        {
            m_timer = 0;
            m_phase = 0;
            m_player = NULL;
        }

        void StartAnim(Player* player)
        {            
            m_player = player;
            m_timer =250; m_phase = 1;
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
                Talk(0);
                m_timer = 2000; m_phase = 2;
                break;
            case 2:
                if (m_player)
                    m_player->CastSpell(m_player, SPELL_SUMMON_MESSNER);

                m_timer = 5000; m_phase = 3;
                break;
            case 3:
                m_timer = 0; m_phase = 0;
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_messner_43270AI(creature);
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
        CAST_AI(npc_jorgensen_43272AI, creature->AI())->StartAnim(player);
        return false;
    }

    struct npc_jorgensen_43272AI : public ScriptedAI
    {
        npc_jorgensen_43272AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;
        Player* m_player;

        void Reset() override
        {
            m_timer = 0;
            m_phase = 0;
            m_player = NULL;
        }

        void StartAnim(Player* player)
        {
            m_player = player;
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
                Talk(0);
                m_timer = 2000; m_phase = 2;
                break;
            case 2:
                if (m_player)
                    m_player->CastSpell(m_player, SPELL_SUMMON_JORGENSEN);

                m_timer = 5000; m_phase = 3;
                break;
            case 3:
                Reset();
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_jorgensen_43272AI(creature);
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
                    Talk(6);
                }
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

        void Register() override
        {
            OnEffectLaunch += SpellEffectFn(spell_freeing_danforth_SpellScript::OpenLock, EFFECT_0, SPELL_EFFECT_OPEN_LOCK);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_freeing_danforth_SpellScript();
    }
};

//###################################### Start Quest 26616 It's never over: riverboat ride to other beach..

enum eAnimBoot
{
    NPC_KEESHANS_RIVERBOAT_43450 = 43450,
    NPN_JOHN_J_KEESHAN_43449 = 43449,
    NPC_MESSNER_43448 = 43448,
    NPC_JORGENSEN_43447 = 43447,
    NPC_KRAKAUER_43446 = 43446,
    NPN_DANFORTH_43445 = 43445,
    NPN_JOHN_J_KEESHAN_43457 = 43457,
    NPC_MESSNER_43432 = 43432,
    NPC_JORGENSEN_43433 = 43433,
    // NPC_KRAKAUER_43434 = 43434,
    NPN_DANFORTH_43435 = 43435,
    SPELL_RIDE_VEHICLE_HARDCODED = 46598,
    SPELL_RIVERBOAT_TRIGGER_01 = 81257,
    SPELL_RIVERBOAT_TRIGGER_02 = 81258,
    SPELL_RIVERBOAT_TRIGGER_03 = 81263,
    SPELL_RIVERBOAT_TRIGGER_04 = 81254,
    SPELL_MESSNER_BOAT_ENGINE = 81260,
    SPELL_DETECT_QUEST_INVIS_11 = 81267,
    SPELL_DETECT_QUEST_INVIS_12 = 81497,
    SPELL_APPLY_QUEST_INVIS_11 = 81266,
    SPELL_APPLY_QUEST_INVIS_12 = 81496,
    SPELL_RIVERBOAT_QUEST_CREDIT = 81265,
};

class npc_john_j_keeshan_43449 : public CreatureScript
{
public:
    npc_john_j_keeshan_43449() : CreatureScript("npc_john_j_keeshan_43449") { }

    struct npc_john_j_keeshan_43449AI : public ScriptedAI
    {
        npc_john_j_keeshan_43449AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;

        void Reset() override
        {
            m_timer = 0;
            m_phase = 0;
        }

        void StartAnim()
        {
            if (m_phase == 0)
            {
                m_timer = 1000;
                m_phase = 1;
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
                if (Creature* vehicle = me->FindNearestCreature(NPC_KEESHANS_RIVERBOAT_43450, 25.0f))
                {
                    vehicle->SetFacingTo(3.57f);

                    me->SetWaterWalking(true);
                    me->GetMotionMaster()->MovePoint(0, vehicle->GetPosition());

                    if (Player* player = vehicle->GetCharmerOrOwnerOrSelf()->ToPlayer())
                        player->RemoveAura(SPELL_DETECT_QUEST_INVIS_3);

                    if (Creature* npc = me->FindNearestCreature(NPC_MESSNER_43448, 25.0f))
                    {
                        npc->GetMotionMaster()->MovePoint(0, vehicle->GetPosition());
                        npc->SetWaterWalking(true);
                    }

                    if (Creature* npc = me->FindNearestCreature(NPC_JORGENSEN_43447, 25.0f))
                    {
                        npc->GetMotionMaster()->MovePoint(0, vehicle->GetPosition());
                        npc->SetWaterWalking(true);
                    }

                    if (Creature* npc = me->FindNearestCreature(NPC_KRAKAUER_43446, 25.0f))
                    {
                        npc->GetMotionMaster()->MovePoint(0, vehicle->GetPosition());
                        npc->SetWaterWalking(true);
                    }

                    if (Creature* npc = me->FindNearestCreature(NPN_DANFORTH_43445, 25.0f))
                    {
                        npc->GetMotionMaster()->MovePoint(0, vehicle->GetPosition());
                        npc->SetWaterWalking(true);
                    }
                }

                m_timer = 2000; m_phase = 2;
                break;
            case 2:
                if (Creature* vehicle = me->FindNearestCreature(NPC_KEESHANS_RIVERBOAT_43450, 25.0f))
                {
                    if (Player* player = vehicle->GetCharmerOrOwnerOrSelf()->ToPlayer())
                    {
                        player->RemoveAura(SPELL_DETECT_QUEST_INVIS_9);
                        player->AddAura(SPELL_DETECT_QUEST_INVIS_10, player);

                        if (Creature* npc = player->SummonCreature(NPN_JOHN_J_KEESHAN_43457, vehicle->GetNearPosition(2.0f, frand(0.0f, 6.28f))))
                        {
                            npc->EnterVehicle(vehicle, 1);
                            npc->AddAura(SPELL_APPLY_QUEST_INVIS_10, npc);
                            npc->AI()->Talk(0);
                        }

                        if (Creature* npc = player->SummonCreature(NPC_JORGENSEN_43433, vehicle->GetNearPosition(2.0f, frand(0.0f, 6.28f))))
                        {
                            npc->EnterVehicle(vehicle, 2);
                            npc->AddAura(SPELL_APPLY_QUEST_INVIS_10, npc);
                        }

                        if (Creature* npc = player->SummonCreature(NPC_KRAKAUER_43434, vehicle->GetNearPosition(2.0f, frand(0.0f, 6.28f))))
                        {
                            npc->EnterVehicle(vehicle, 3);
                            npc->AddAura(SPELL_APPLY_QUEST_INVIS_10, npc);
                        }

                        if (Creature* npc = player->SummonCreature(NPN_DANFORTH_43435, vehicle->GetNearPosition(2.0f, frand(0.0f, 6.28f))))
                        {
                            npc->EnterVehicle(vehicle, 4);
                            npc->AddAura(SPELL_APPLY_QUEST_INVIS_10, npc);
                        }

                        if (Creature* npc = player->SummonCreature(NPC_MESSNER_43432, vehicle->GetNearPosition(2.0f, frand(0.0f, 6.28f))))
                        {
                            npc->EnterVehicle(vehicle, 0);
                            npc->AddAura(SPELL_APPLY_QUEST_INVIS_10, npc);
                        }
                    }
                }
                m_timer = 1000; m_phase = 3;
                break;
            case 3:
                if (Creature* npc = me->FindNearestCreature(NPN_JOHN_J_KEESHAN_43449, 25.0f))
                    npc->GetMotionMaster()->MoveTargetedHome();

                if (Creature* npc = me->FindNearestCreature(NPC_MESSNER_43448, 25.0f))
                    npc->GetMotionMaster()->MoveTargetedHome();

                if (Creature* npc = me->FindNearestCreature(NPC_JORGENSEN_43447, 25.0f))
                    npc->GetMotionMaster()->MoveTargetedHome();

                if (Creature* npc = me->FindNearestCreature(NPC_KRAKAUER_43446, 25.0f))
                    npc->GetMotionMaster()->MoveTargetedHome();

                if (Creature* npc = me->FindNearestCreature(NPN_DANFORTH_43445, 25.0f))
                    npc->GetMotionMaster()->MoveTargetedHome();
                
                m_timer = 0; m_phase = 0;
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_john_j_keeshan_43449AI(creature);
    }
};

class vehicle_keeshans_riverboat_43450 : public VehicleScript
{
public:
    vehicle_keeshans_riverboat_43450() : VehicleScript("vehicle_keeshans_riverboat_43450") { }

    void OnAddPassenger(Vehicle* veh, Unit* passenger, int8 seatId) override
    { 
        if (passenger->ToPlayer() && seatId == 0)
        {
            if (Creature* john = passenger->FindNearestCreature(NPN_JOHN_J_KEESHAN_43449, 25.0f))
                CAST_AI(npc_john_j_keeshan_43449::npc_john_j_keeshan_43449AI, john->AI())->StartAnim();
        }
    }
};

class npc_john_j_keeshan_43457 : public CreatureScript
{
public:
    npc_john_j_keeshan_43457() : CreatureScript("npc_john_j_keeshan_43457") { }

    struct npc_john_j_keeshan_43457AI : public ScriptedAI
    {
        npc_john_j_keeshan_43457AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;

        void Reset() override
        {
            m_timer = 3000;
            m_phase = 1;
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
                if (Creature* messner = me->FindNearestCreature(NPC_MESSNER_43432, 25.0f))
                {
                    messner->CastSpell(messner, SPELL_MESSNER_BOAT_ENGINE);
                    messner->AI()->Talk(0);
                }
                if (Creature* vehicle = me->FindNearestCreature(NPC_KEESHANS_RIVERBOAT_43450, 25.0f))
                {
                    vehicle->SetSpeed(MOVE_WALK, 3.5f, true);
                    vehicle->GetMotionMaster()->MovePath(43450, false);
                }
                m_timer = 10000; m_phase = 2;
                break;
            case 2:
                if (me->GetAreaId() == AREA_CAMP_EVERSTILL)
                {
                    m_timer = 3000;  m_phase = 3;
                }
                break;
            case 3:
                if (Creature* messner = me->FindNearestCreature(NPC_MESSNER_43432, 25.0f))
                    messner->RemoveAura(SPELL_MESSNER_BOAT_ENGINE);

                me->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
                Talk(1);
                m_timer = 5000; m_phase = 4;
                break;
            case 4:
                if (Creature* vehicle = me->FindNearestCreature(NPC_KEESHANS_RIVERBOAT_43450, 25.0f))
                    if (Player* player = vehicle->GetCharmerOrOwnerOrSelf()->ToPlayer())
                    {
                        player->CastSpell(player, SPELL_RIVERBOAT_QUEST_CREDIT);
                        player->SetQuestStatus(QUEST_ITS_NEVER_OVER, QUEST_STATUS_COMPLETE, true);
                        player->AddAura(SPELL_DETECT_QUEST_INVIS_11, player);
                        player->AddAura(SPELL_DETECT_QUEST_INVIS_12, player);
                    }
                m_timer = 500; m_phase = 5;
                break;
            case 5:
                if (Creature* npc = me->FindNearestCreature(NPC_MESSNER_43432, 25.0f))
                    npc->DespawnOrUnsummon();
                if (Creature* npc = me->FindNearestCreature(NPC_JORGENSEN_43433, 25.0f))
                    npc->DespawnOrUnsummon();
                if (Creature* npc = me->FindNearestCreature(NPC_KRAKAUER_43434, 25.0f))
                    npc->DespawnOrUnsummon();
                if (Creature* npc = me->FindNearestCreature(NPN_DANFORTH_43435, 25.0f))
                    npc->DespawnOrUnsummon();
                if (Creature* npc = me->FindNearestCreature(NPC_KEESHANS_RIVERBOAT_43450, 25.0f))
                    npc->DespawnOrUnsummon();

                m_timer = 500; m_phase = 6;
                break;
            case 6:
                me->DespawnOrUnsummon();
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_john_j_keeshan_43457AI(creature);
    }
};

//###################################### End Quest 26616 It's never over: on other beach..

enum eCompanieBravo
{
    NPN_JOHN_J_KEESHAN_43458 = 43458,
    NPC_MESSNER_43459 = 43459,
    NPC_JORGENSEN_43460 = 43460,
    NPC_JORGENSEN_43546 = 43546,
    NPC_KRAKAUER_43461 = 43461,
    NPN_DANFORTH_43462 = 43462,
    NPC_KIDNAPPED_REDRIGE_CITIZEN = 43571,
    NPC_PRISONER_OF_WAR_KILL_CREDIT = 43574,
    NPC_MUNITION_DUMP = 43589,
    NPC_BLACKROCK_TOWER = 43590,
    NPC_BLACKROCK_GUARD = 7013,
    NPC_BRAVO_COMPANY_TRIGGER = 43594,
    NPC_WILD_RAT = 43518,
    GO_BLACKROCK_EXPLOSIVE_DEVICE_1 = 204444,
    GO_BLACKROCK_EXPLOSIVE_DEVICE_2 = 204445,
    GO_BLACKROCK_EXPLOSIVE_DEVICE_3 = 204446,
    GO_BLACKROCK_TOWER_OR_MUNITIONS_HUT = 301069,
    ITEM_BRAVO_COMPANY_FIELD_KIT_1 = 60384,
    ITEM_BRAVO_COMPANY_FIELD_KIT_2 = 60385,
    QUEST_PRISONERS_OF_WAR = 26646,
    QUEST_TO_WIN_A_WAR_YOU_GOTTA_BECOME_WAR = 26651,
    QUEST_DETONATION = 26668,
    SPELL_SUMMON_JORGENSEN_43546 = 81447,
    SPELL_SEAL_OF_RIGHTEOUSNESS_43546 = 81454,
    SPELL_CONCENTRATION_AURA_43546 = 81455,
    SPELL_STATIC_SOUND = 81769,
    SPELL_DISTRACTION = 82578,
    SPELL_CHLOROFORM = 82579,
    SPELL_BRAVO_COMPANY_FIELD_KIT_1_60384 = 82580,
    SPELL_BRAVO_COMPANY_FIELD_KIT_2_60385 = 82587,
    SPELL_DISTRACTION_VISUAL = 81370,
    SPELL_DEADLY_POISEN = 10022,
    SPELL_CAMOUFLAGE = 82577,
    SPELL_DETECT_QUEST_INVIS_13 = 81581,
};

class npc_john_j_keeshan_43458 : public CreatureScript
{
public:
    npc_john_j_keeshan_43458() : CreatureScript("npc_john_j_keeshan_43458") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)  override
    {
        Creature* npc = creature->FindNearestCreature(NPC_JORGENSEN_43546, 100.0f);

        if (quest->GetQuestId() == QUEST_PRISONERS_OF_WAR)
        {
           if (!npc)
              player->CastSpell(player, SPELL_SUMMON_JORGENSEN_43546);
        }
        else if (quest->GetQuestId() == QUEST_TO_WIN_A_WAR_YOU_GOTTA_BECOME_WAR)
        {
          if (!npc)
              player->CastSpell(player, SPELL_SUMMON_JORGENSEN_43546);
        }

        return false;
    }

    bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* /*quest*/, uint32 /*opt*/)  override
    { 
        Creature* npc = player->FindNearestCreature(NPC_JORGENSEN_43546, 100.0f);

        if (npc)
            npc->DespawnOrUnsummon();

        return false; 
    }

    struct npc_john_j_keeshan_43458AI : public ScriptedAI
    {
        npc_john_j_keeshan_43458AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;

        void Reset() override
        {
            m_timer = 0;
            m_phase = 0;
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (Player* player = who->ToPlayer())
                if (player->HasAura(SPELL_DETECT_QUEST_INVIS_10) && m_phase == 0 && me->GetDistance2d(player) < 10.0f)
                {
                    m_timer = 1000; m_phase = 1;
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
                Talk(0);
                m_timer = 5000; m_phase = 2;
                break;
            case 2:
                if (Creature* npc = me->FindNearestCreature(NPN_DANFORTH_43462, 15.0f))
                    npc->AI()->Talk(0);

                m_timer = 5000; m_phase = 3;
                break;
            case 3:
                Talk(1);
                m_timer = 5000; m_phase = 4;
                break;
            case 4:
                if (Creature* npc = me->FindNearestCreature(NPC_KRAKAUER_43461, 15.0f))
                    npc->AI()->Talk(0);

                m_timer = 5000; m_phase = 5;
                break;
            case 5:
                if (Creature* npc = me->FindNearestCreature(NPC_KRAKAUER_43461, 15.0f))
                    npc->AI()->Talk(1);

                m_timer = 5000; m_phase = 6;
                break;
            case 6:
                Talk(2);
                m_timer = 5000; m_phase = 7;
                break;
            case 7:
                if (Creature* npc = me->FindNearestCreature(NPC_JORGENSEN_43460, 15.0f))
                    npc->AI()->Talk(0);

                m_timer = 5000; m_phase = 8;
                break;
            case 8:
                Talk(3);
                m_timer = 5000; m_phase = 9;
                break;
            case 9:
                if (Creature* npc = me->FindNearestCreature(NPC_MESSNER_43459, 15.0f))
                    npc->AI()->Talk(0);

                m_timer = 5000; m_phase = 10;
                break;
            case 10:
                Talk(4);
                m_timer = 5000; m_phase = 11;
                break;
            case 11:
                Talk(5);
                m_timer = 5000; m_phase = 12;
                break;
            case 12:
                m_timer = 90000; m_phase = 13;
                break;
            case 13:
                m_timer = 0; m_phase = 0;
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_john_j_keeshan_43458AI(creature);
    }
};

class npc_jorgensen_43546 : public CreatureScript
{
public:
    npc_jorgensen_43546() : CreatureScript("npc_jorgensen_43546") { }

    struct npc_jorgensen_43546AI : public ScriptedAI
    {
        npc_jorgensen_43546AI(Creature *c) : ScriptedAI(c) 
        {
            ShownActive = false;
            ShownTip1 = false;
            ShownTip2 = false;
            ShownTip3 = false;
            CoolDownTimer = 0;
        }

        uint32 m_timer;
        uint32 m_phase;

        bool ShownActive;
        bool ShownTip1;
        bool ShownTip2;
        bool ShownTip3;
        uint32 CoolDownTimer;

        void Reset() override
        {
            m_timer = 1000;
            m_phase = 0;            
            me->AddAura(SPELL_SEAL_OF_RIGHTEOUSNESS_43546, me);
            me->AddAura(SPELL_CONCENTRATION_AURA_43546, me);
            me->SetReactState(REACT_DEFENSIVE);
        }

        void AttackStart(Unit* target) override
        {
            if (target->HasAura(SPELL_CHLOROFORM))
                return; 
               
            if (Creature* npc = me->GetCharmerOrOwner()->ToPlayer()->getAttackerForHelper()->ToCreature())
            {
                me->Attack(npc, true);
                me->GetMotionMaster()->MoveChase(npc);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (CoolDownTimer <= diff)
                CoolDownTimer = 0;
            else
                CoolDownTimer -= diff;

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
        return new npc_jorgensen_43546AI(creature);
    }
};

class npc_bravo_company_trigger : public CreatureScript
{
public:
    npc_bravo_company_trigger() : CreatureScript("npc_bravo_company_trigger") { }

    struct npc_bravo_company_triggerAI : public ScriptedAI
    {
        npc_bravo_company_triggerAI(Creature *c) : ScriptedAI(c) { }

        uint32 m_position;

        void Reset() override
        {
            CheckPosition();
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (m_position == 0)
            {
                CheckPosition();
                if (m_position == 0)
                    return;
            }

            Player* player = who->ToPlayer();
            if (!player)
                return;

            if (player->GetQuestStatus(QUEST_PRISONERS_OF_WAR) != QUEST_STATUS_INCOMPLETE && player->GetQuestStatus(QUEST_PRISONERS_OF_WAR) != QUEST_STATUS_INCOMPLETE)
                return;

            uint32 InstalledKitCount = player->GetItemCount(ITEM_BRAVO_COMPANY_FIELD_KIT_1) + player->GetItemCount(ITEM_BRAVO_COMPANY_FIELD_KIT_2);
            if (InstalledKitCount == 0)
                return;

            Creature* jorgensen = GetCharmedJorgensen(player);
             
            npc_jorgensen_43546::npc_jorgensen_43546AI* jorgensenAI = CAST_AI(npc_jorgensen_43546::npc_jorgensen_43546AI, jorgensen->AI());

            bool IsKitActive = player->HasSpell(SPELL_CAMOUFLAGE);
            bool IsCamouflageActiv = player->HasAura(SPELL_CAMOUFLAGE);
            uint64 guid = player->GetGUID();

            if (!IsKitActive)
            {
                if (jorgensenAI->CoolDownTimer == 0)
                {
                    Talk(0, player);
                    jorgensenAI->CoolDownTimer = 6000;
                    jorgensenAI->ShownActive = false;
                }
                return;
            }

            if (!jorgensenAI->ShownActive)
            {
                if (jorgensenAI->CoolDownTimer == 0)
                {
                    Talk(4, player);
                    jorgensenAI->CoolDownTimer = 6000;
                    jorgensenAI->ShownActive = true;
                }
                return;
            }
            if (jorgensenAI->CoolDownTimer == 0)
            {
                if (!IsCamouflageActiv)
                {
                    Talk(1, player); // Tip Enable Camourflage 1
                    jorgensenAI->CoolDownTimer = 6000;
                    jorgensenAI->ShownTip1 = true;
                    return;
                }
                if (m_position == 3 && !jorgensenAI->ShownTip3)
                {
                    Talk(3, player); // Tip chloroform 3
                    jorgensenAI->CoolDownTimer = 6000;
                    jorgensenAI->ShownTip3 = true;
                    return;
                }
                if (m_position == 2 && !jorgensenAI->ShownTip2)
                {
                    Talk(2, player); // Tip Distraction 2
                    jorgensenAI->CoolDownTimer = 6000;
                    jorgensenAI->ShownTip2 = true;
                    return;
                }
            }
        }
 
        void CheckPosition()
        {
            if (me->GetPositionX() > -9600.0f)
                m_position = 1;
            else if (me->GetPositionX() > -9700.0f && me->GetPositionX() < -9600.0f)
                m_position = 2;
            else if (me->GetPositionX() < -9700.0f)
                m_position = 3;
            else
                m_position = 0;
        }

        Creature* GetCharmedJorgensen(Player* player)
        {
            Creature* jorgensen = FindCharmedJorgensen(player);

            if (!jorgensen)
            {
                player->CastSpell(player, SPELL_SUMMON_JORGENSEN_43546);
                jorgensen = FindCharmedJorgensen(player);
            }

            return jorgensen;
        }

        Creature* FindCharmedJorgensen(Player* player)
        {
            std::list<Creature*> creatureList = me->FindNearestCreatures(NPC_JORGENSEN_43546, 100.0f);
            for (std::list<Creature*>::iterator itr = creatureList.begin(); itr != creatureList.end(); ++itr)
                if (player->GetGUID() == (*itr)->GetCharmerOrOwnerOrSelf()->GetGUID())
                    return *itr;

            return NULL;
        }

    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bravo_company_triggerAI(creature);
    }
};

class npc_blackrock_grunt : public CreatureScript
{
public:
    npc_blackrock_grunt() : CreatureScript("npc_blackrock_grunt") { }

    struct npc_blackrock_gruntAI : public ScriptedAI
    {
        npc_blackrock_gruntAI(Creature *c) : ScriptedAI(c) { }

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
                if (Creature* rat = me->FindNearestCreature(NPC_WILD_RAT, 15.0f))
                {
                    me->GetMotionMaster()->MoveIdle();
                    m_timer = 500; m_phase = 1;
                }
                break;
            case 1:
                if (Creature* rat = me->FindNearestCreature(NPC_WILD_RAT, 15.0f))
                    me->GetMotionMaster()->MovePoint(0, rat->GetNearPosition(1.0f, frand(0, 6.24f)));

                m_timer = 2000; m_phase = 2;
                break;
            case 2:
                if (Creature* rat = me->FindNearestCreature(NPC_WILD_RAT, 15.0f))
                    me->SetFacingToObject(rat);

                m_timer = 27000; m_phase = 3;
                break;
            case 3:
                me->GetMotionMaster()->MoveTargetedHome();
                m_timer = 2000; m_phase = 4;
                break;
            case 4:
                me->GetMotionMaster()->Initialize();

                m_timer = 1000; m_phase = 0;
                break;
            case 5:
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_blackrock_gruntAI(creature);
    }
};

class npc_blackrock_outrunner : public CreatureScript
{
public:
    npc_blackrock_outrunner() : CreatureScript("npc_blackrock_outrunner") { }

    struct npc_blackrock_outrunnerAI : public ScriptedAI
    {
        npc_blackrock_outrunnerAI(Creature *c) : ScriptedAI(c) { }

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
                if (Creature* rat = me->FindNearestCreature(NPC_WILD_RAT, 15.0f))
                {
                    me->GetMotionMaster()->MoveIdle();
                    m_timer = 500; m_phase = 1;
                }
                break;
            case 1:
                if (Creature* rat = me->FindNearestCreature(NPC_WILD_RAT, 15.0f))
                    me->GetMotionMaster()->MovePoint(0, rat->GetNearPosition(1.0f, frand(0, 6.24f)));

                m_timer = 2000; m_phase = 2;
                break;
            case 2:
                if (Creature* rat = me->FindNearestCreature(NPC_WILD_RAT, 15.0f))
                    me->SetFacingToObject(rat);

                m_timer = 27000; m_phase = 3;
                break;
            case 3:
                me->GetMotionMaster()->MoveTargetedHome();
                m_timer = 2000; m_phase = 4;
                break;
            case 4:
                me->GetMotionMaster()->Initialize();

                m_timer = 1000; m_phase = 0;
                break;
            case 5:
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_blackrock_outrunnerAI(creature);
    }
};

class npc_blackrock_guard : public CreatureScript
{
public:
    npc_blackrock_guard() : CreatureScript("npc_blackrock_guard") { }

    struct npc_blackrock_guardAI : public ScriptedAI
    {
        npc_blackrock_guardAI(Creature *c) : ScriptedAI(c) { }

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
                if (Creature* rat = me->FindNearestCreature(NPC_WILD_RAT, 15.0f))
                {
                    me->GetMotionMaster()->MoveIdle();
                    m_timer = 500; m_phase = 1;
                }
                break;
            case 1:
                if (Creature* rat = me->FindNearestCreature(NPC_WILD_RAT, 15.0f))
                    me->GetMotionMaster()->MovePoint(0, rat->GetNearPosition(1.0f, frand(0, 6.24f)));

                m_timer = 2000; m_phase = 2;
                break;
            case 2:
                if (Creature* rat = me->FindNearestCreature(NPC_WILD_RAT, 15.0f))
                    me->SetFacingToObject(rat);

                m_timer = 27000; m_phase = 3;
                break;
            case 3:
                me->GetMotionMaster()->MoveTargetedHome();
                m_timer = 2000; m_phase = 4;
                break;
            case 4:
                me->GetMotionMaster()->Initialize();

                m_timer = 1000; m_phase = 0;
                break;
            case 5:
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_blackrock_guardAI(creature);
    }
};

class npc_blackrock_drake_rider : public CreatureScript
{
public:
    npc_blackrock_drake_rider() : CreatureScript("npc_blackrock_drake_rider") { }

    struct npc_blackrock_drake_riderAI : public ScriptedAI
    {
        npc_blackrock_drake_riderAI(Creature *c) : ScriptedAI(c) { }

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
                if (Creature* rat = me->FindNearestCreature(NPC_WILD_RAT, 15.0f))
                {
                    me->GetMotionMaster()->MoveIdle();
                    m_timer = 500; m_phase = 1;
                }
                break;
            case 1:
                if (Creature* rat = me->FindNearestCreature(NPC_WILD_RAT, 15.0f))
                    me->GetMotionMaster()->MovePoint(0, rat->GetNearPosition(1.0f, frand(0, 6.24f)));

                m_timer = 2000; m_phase = 2;
                break;
            case 2:
                if (Creature* rat = me->FindNearestCreature(NPC_WILD_RAT, 15.0f))
                    me->SetFacingToObject(rat);

                m_timer = 27000; m_phase = 3;
                break;
            case 3:
                me->GetMotionMaster()->MoveTargetedHome();
                m_timer = 2000; m_phase = 4;
                break;
            case 4:
                me->GetMotionMaster()->Initialize();

                m_timer = 1000; m_phase = 0;
                break;
            case 5:
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_blackrock_drake_riderAI(creature);
    }
};

class npc_blackrock_warden : public CreatureScript
{
public:
    npc_blackrock_warden() : CreatureScript("npc_blackrock_warden") { }

    struct npc_blackrock_wardenAI : public ScriptedAI
    {
        npc_blackrock_wardenAI(Creature *c) : ScriptedAI(c) { }

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
                if (Creature* rat = me->FindNearestCreature(NPC_WILD_RAT, 15.0f))
                {
                    me->GetMotionMaster()->MoveIdle();
                    m_timer = 500; m_phase = 1;
                }
                break;
            case 1:
                if (Creature* rat = me->FindNearestCreature(NPC_WILD_RAT, 15.0f))
                    me->GetMotionMaster()->MovePoint(0, rat->GetNearPosition(1.0f, frand(0, 6.24f)));

                m_timer = 2000; m_phase = 2;
                break;
            case 2:
                if (Creature* rat = me->FindNearestCreature(NPC_WILD_RAT, 15.0f))
                    me->SetFacingToObject(rat);

                m_timer = 27000; m_phase = 3;
                break;
            case 3:
                me->GetMotionMaster()->MoveTargetedHome();
                m_timer = 2000; m_phase = 4;
                break;
            case 4:
                me->GetMotionMaster()->Initialize();

                m_timer = 1000; m_phase = 0;
                break;
            case 5:
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_blackrock_wardenAI(creature);
    }
};

class go_blackrock_holding_pen : public GameObjectScript
{
public:
    go_blackrock_holding_pen() : GameObjectScript("go_blackrock_holding_pen") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/) override
    {
        if (player->GetQuestStatus(QUEST_PRISONERS_OF_WAR) == QUEST_STATUS_INCOMPLETE)
        {
            if (Creature* npc = player->FindNearestCreature(NPC_KIDNAPPED_REDRIGE_CITIZEN, 25.0f))
                npc->AI()->Talk(0);

            player->CastSpell(player, SPELL_STATIC_SOUND);
            player->KilledMonsterCredit(NPC_PRISONER_OF_WAR_KILL_CREDIT);
        }
        return true;
    }
};

class spell_plant_seaforium : public SpellScriptLoader
{
public:
    spell_plant_seaforium() : SpellScriptLoader("spell_plant_seaforium") { }

    class spell_plant_seaforium_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_plant_seaforium_SpellScript);

        void CheckCastOnPlace()
        {
            if (Player* player = GetCaster()->ToPlayer())
                if (GameObject* go = player->FindNearestGameObject(GO_BLACKROCK_TOWER_OR_MUNITIONS_HUT, 5.0f))
                    if (Creature* npc = player->FindNearestCreature(NPC_MUNITION_DUMP, 15.0f))
                        player->KilledMonsterCredit(NPC_MUNITION_DUMP);
                    else if (Creature* npc = player->FindNearestCreature(NPC_BLACKROCK_TOWER, 15.0f))
                        player->KilledMonsterCredit(NPC_BLACKROCK_TOWER);
        }

        void Register() override
        {
            OnCast += SpellCastFn(spell_plant_seaforium_SpellScript::CheckCastOnPlace);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_plant_seaforium_SpellScript();
    }
};

//###################################### Quest

enum eJohnKeeshan
{
    NPN_DANFORTH_43607 = 43607,
    NPC_KRAKAUER_43608 = 43608,
    NPC_JORGENSEN_43609 = 43609,
    NPC_MESSNER_43610 = 43610,
    NPN_JOHN_J_KEESHAN_43611 = 43611,
    NPC_COLONEL_TROTEMAN_43728 = 43728,
    NPC_COLONEL_TROTEMAN_43733 = 43733,
    NPC_COMPANY_BRAVO_SIEGE_TANK = 43714,
    NPC_GRAND_MAGE_DOANE = 397,
    GO_BLACKROCK_KEY_POUCH = 204437,
    SPELL_BRAVO_COMPANY_FIELD_KIT_VISUAL = 81462,
    QUEST_THE_GRAND_MAGUS_DOANE = 26694,
    SPELL_RENDERS_VALLEY_CAMERA = 81607,
    SPELL_PARACHUTE_81793 = 81793,
    SPELL_APPLY_QUEST_INVIS_16 = 81805,
    SPELL_DETECT_QUEST_INVIS_16 = 81804, // duration 30 sec 
    SAY_PAYLOAD = 1,
    SAY_DANFORTH_DEVEL = 0,
    SAY_JOHN_TROTEMAN = 2,
    SAY_DANFORTH_TROTEMAN = 1,
    SAY_DOANE_PATHWAY = 0,
    SAY_DOANE_ERROR = 1,
    SAY_DOANE_MINION = 2,
    SAY_DOANE_BRAVO = 4,
    SAY_DOANE_MATTER = 5,
};

enum eGrandMagus
{
    NPC_GRAND_MAGUS_DOANE = 397,
    NPC_MINION_OF_DOANE = 2531,
    NPC_TROTEMANN_43728 = 43728,
    ITEM_KEY_OF_ILGALAR = 59522,
    SPELL_MINION_OF_DOANE = 3611,
    SPELL_UNLOCKING_WARD_OF_ILGALAR = 81776,
    SPELL_DOANE_CREDIT = 81791,
    SPELL_APPLY_QUEST_INVIS_15 = 81795,
    SPELL_DETECT_QUEST_INVIS_15 = 81794,
    SPELL_EJECT_PASSENGER_1 = 80743,
    SAY_DAN_WHERE = 0,
    SAY_JOHN_TROTE = 2,
    SAY_DAN_TROTE = 1,
    SAY_SERVICE = 0, 
};

class npc_john_j_keeshan_43611 : public CreatureScript
{
public:
    npc_john_j_keeshan_43611() : CreatureScript("npc_john_j_keeshan_43611") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)  override
    {
        player->RemoveAura(SPELL_DETECT_QUEST_INVIS_10);
        player->RemoveAura(SPELL_DETECT_QUEST_INVIS_11);
        player->RemoveAura(SPELL_DETECT_QUEST_INVIS_12);
        player->RemoveAura(SPELL_SUMMON_JORGENSEN_43546);
        player->AddAura(SPELL_DETECT_QUEST_INVIS_13, player);

        if (quest->GetQuestId() == QUEST_DETONATION)
        {
            player->CastSpell(player, SPELL_RENDERS_VALLEY_CAMERA, true);
            player->CastSpell(player, 81462, true);
        }   

        return false;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)  override
    {
        Creature* npc = player->FindNearestCreature(NPC_JORGENSEN_43546, 100.0f);

        if (npc)
            npc->DespawnOrUnsummon();

        if (quest->GetQuestId() == QUEST_THE_GRAND_MAGUS_DOANE)
        {
            player->AddAura(SPELL_DETECT_QUEST_INVIS_16, player); // duration 30 sec. for see siege tank animation
            CAST_AI(npc_john_j_keeshan_43611AI, creature->AI())->StartAnimTrotman(player);
        }

        return false;
    }

    struct npc_john_j_keeshan_43611AI : public ScriptedAI
    {
        npc_john_j_keeshan_43611AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;
        Player* m_player;

        void Reset() override
        {
            m_timer = 0;
            m_phase = 0;
            m_player = NULL;
        }

        void StartAnimTrotman(Player* player)
        {
            m_timer = 1000; m_phase = 1; m_player = player;
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
            case 1: // bravo group: moves some meter forward
                if (Creature* npc = me->FindNearestCreature(NPN_DANFORTH_43607, 25.0f))
                    npc->GetMotionMaster()->MovePoint(0, -9635.3f, -3470.72f, 121.1892f);
                if (Creature* npc = me->FindNearestCreature(NPC_KRAKAUER_43608, 25.0f))
                    npc->GetMotionMaster()->MovePoint(0, -9643.22f, -3475.18f, 120.9651f);
                if (Creature* npc = me->FindNearestCreature(NPC_JORGENSEN_43609, 25.0f))
                    npc->GetMotionMaster()->MovePoint(0, -9633.14f, -3468.32f, 121.1628f);
                if (Creature* npc = me->FindNearestCreature(NPC_MESSNER_43610, 25.0f))
                    npc->GetMotionMaster()->MovePoint(0, -9640.22f, -3474.26f, 121.2151f);
                if (Creature* npc = me->FindNearestCreature(NPN_JOHN_J_KEESHAN_43611, 25.0f))
                    npc->GetMotionMaster()->MovePoint(0, -9637.62f, -3471.96f, 121.2151f);
                m_timer = 3000; m_phase = 2;
                break;
            case 2: 
                me->HandleEmote(EMOTE_ONESHOT_EXCLAMATION);
                Talk(SAY_PAYLOAD);
                m_timer = 1000; m_phase = 3;
                break;
            case 3: // spawn tank with parachute and set troteman inside
                if (Creature* tank = me->SummonCreature(NPC_COMPANY_BRAVO_SIEGE_TANK, -9645.827f, -3459.116f, 157.2119f, 1.937315f, TEMPSUMMON_TIMED_DESPAWN, 22000))
                {
                    tank->SetDisableGravity(true);
                    tank->SetSpeed(MOVE_WALK, 2.0f);
                    tank->GetMotionMaster()->MovePath(NPC_COMPANY_BRAVO_SIEGE_TANK, false);
                }
                m_timer = 1000; m_phase = 4;
                break;
            case 4:
                m_timer = 3000; m_phase = 5;
                break;
            case 5:
                if (Creature* npc = me->FindNearestCreature(NPN_DANFORTH_43607, 25.0f))
                    npc->AI()->Talk(SAY_DAN_WHERE);
                m_timer = 2000; m_phase = 6;
                break;
            case 6:
                Talk(SAY_JOHN_TROTE);
                m_timer = 2000; m_phase = 7;
                break;
            case 7:
                me->PlayDirectSound(18203);
                if (Creature* tank = me->FindNearestCreature(NPC_COMPANY_BRAVO_SIEGE_TANK, 60.0f))
                    tank->SetDisableGravity(false);
                m_timer = 1000; m_phase = 8;
                break;
            case 8: 
                if (Creature* tank = me->FindNearestCreature(NPC_COMPANY_BRAVO_SIEGE_TANK, 25.0f))
                {
                    tank->HandleEmote(EMOTE_ONESHOT_ATTACK_THROWN);
                    tank->CastSpell(tank, SPELL_EJECT_PASSENGER_1);
                }
                if (Creature* npc = me->SummonCreature(NPC_COLONEL_TROTEMAN_43728, -9645.827f, -3459.116f, 121.61f, 1.937315f, TEMPSUMMON_TIMED_DESPAWN, 8000))
                {
                    npc->GetMotionMaster()->MovePoint(0, -9641.50f, -3466.29f, 120.4420f);
                }
                m_timer = 1000; m_phase = 9;
                break;
            case 9:
                if (Creature* npc = me->FindNearestCreature(NPN_DANFORTH_43607, 25.0f))
                    npc->AI()->Talk(SAY_DAN_TROTE);

                m_timer = 3000; m_phase = 10;
                break;
            case 10:
                if (Creature* npc = me->FindNearestCreature(NPC_TROTEMANN_43728, 25.0f))
                    npc->AI()->Talk(SAY_SERVICE); 
                m_timer = 3000; m_phase = 11;
                break;
            case 11:
                if (m_player)
                    m_player->AddAura(SPELL_DETECT_QUEST_INVIS_15, m_player);
                m_timer = 0; m_phase = 0;
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_john_j_keeshan_43611AI(creature);
    }
};

class npc_grand_magus_doane : public CreatureScript
{
public:
    npc_grand_magus_doane() : CreatureScript("npc_grand_magus_doane") { }

    struct npc_grand_magus_doaneAI : public ScriptedAI
    {
        npc_grand_magus_doaneAI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;
        bool m_teleport;
        bool m_summonMinion;
        bool m_talk;

        void Reset() override
        {
            m_timer = 0;
            m_phase = 0;
            m_teleport = false;
            m_summonMinion = false;
            m_talk = false;
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        { 
            if (me->GetHealthPct() < 25.0f)
                damage = 0;

            if (!m_talk)
            {
                Talk(0);
                m_talk = true;
                return;
            }
            else if (me->GetHealthPct() < 30.0f && !m_teleport)
            {
                Talk(1);
                me->DespawnOrUnsummon(3000);                
                m_teleport = true;
                if (Player* player = me->FindNearestPlayer(30.0f))
                {
                    me->CastSpell(player, SPELL_DOANE_CREDIT);
                    player->KilledMonsterCredit(NPC_GRAND_MAGUS_DOANE);
                }
                return;
            }
            else if (me->GetHealthPct() < 60.0f && !m_summonMinion)
            {
                Talk(2);
                if (Creature* minion = me->SummonCreature(NPC_MINION_OF_DOANE, me->GetNearPosition(2.0f, 0.0f), TEMPSUMMON_TIMED_DESPAWN, 600000))
                {
                    if (Player* player = me->FindNearestPlayer(20.0f))
                    {
                        minion->Attack(player, true);
                        m_summonMinion = true;
                    }
                }
                return;
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
           
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_grand_magus_doaneAI(creature);
    }
};

//###################################### End Quest 26651 and starting Quest 26668 Detonation

enum eRendersValley
{
    NPC_RENDERS_VALLEY_CAMERA_INVISIBLE_MODELID = 11686,
    NPC_RENDERS_VALLEY_CAMERA = 43618,
    NPC_EXPLOSIONS_TRIGGER = 43639,
    SPELL_QUEST_DETONATION_COMPLETE = 81620,
    SPELL_DETONATION_BIG = 81631,
    SPELL_DETONATION_NUKE = 81639,
};

class npc_renders_valley_camera : public CreatureScript
{
public:
    npc_renders_valley_camera() : CreatureScript("npc_renders_valley_camera") { }

    struct npc_renders_valley_cameraAI : public ScriptedAI
    {
        npc_renders_valley_cameraAI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;

        void Reset() override
        {
            m_timer = 0;
            m_phase = 0;
            me->SetDisplayId(NPC_RENDERS_VALLEY_CAMERA_INVISIBLE_MODELID);
            me->SetSpeed(MOVE_WALK, 5.0f);
            me->GetMotionMaster()->MovePath(NPC_RENDERS_VALLEY_CAMERA, false);
        }

        void DamageTaken(Unit* /*attacker*/, uint32& damage) override
        { 
            damage = 0;
        }

        void MovementInform(uint32 type, uint32 id) override
        { 
            if (type != 2)
                return;
           
            switch (id)
            {
            case 13:
                m_phase = 0; m_timer = 1000;
                break;
            case 14:
                m_phase = 1;
                break;
            case 17:
                m_phase = 2;
                break;
            case 25:
                if (Player* player = me->GetCharmerOrOwnerOrSelf()->ToPlayer())
                {
                    player->ExitVehicle();
                    me->DespawnOrUnsummon(1000);
                    player->CastSpell(player, SPELL_QUEST_DETONATION_COMPLETE);
                    player->CompleteQuest(QUEST_DETONATION);
                }
                break;
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
                DoDetonation(60, false);
                break;
            case 2:
                DoDetonation(200, true);
                break;
            case 3:
                break;
            }
        }

        void DoDetonation(float range, bool IsNuke)
        {
            std::list<Creature*> creatureList = me->FindNearestCreatures(NPC_EXPLOSIONS_TRIGGER, range);
            if (creatureList.empty())
                return;

            for (std::list<Creature*>::iterator itr = creatureList.begin(); itr != creatureList.end(); ++itr)
            {
                Creature* npc = (*itr);
                if (IsNuke)
                {
                    uint32 r = urand(0, 100);
                    if (r < 5)
                        npc->CastSpell(npc, SPELL_DETONATION_BIG);
                }
                else
                    npc->CastSpell(npc, SPELL_DETONATION_NUKE);
            }
                
                
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_renders_valley_cameraAI(creature);
    }
};

//######################################  Quest 26708

enum eQuest26708
{
    NPC_TROTEMANN_43733 = 43733,
    NPC_BRAVO_COMPANY_SIEGE_TANK_43734 = 43734,
    NPN_JOHN_J_KEESHAN_43744 = 43744,
    NPC_KEESHANS_GUN = 43745,
    SPELL_SUMMON_BRAVO_COMPANY_SIEGE_TANK = 81808,
    SPELL_APPLY_QUEST_INVIS_17 = 81897,
    SPELL_DETECT_QUEST_INVIS_17 = 81898,
    SPELL_APPLY_QUEST_INVIS_18 = 82059,
    SPELL_DETECT_QUEST_INVIS_18 = 82060,
    SPELL_SUMMON_PERSONAL_GUARDIAN_KEESHAN = 82002,
    SPELL_SUMMON_PERSONAL_GUARDIAN_MESSNER = 82004,
    SPELL_SUMMON_PERSONAL_GUARDIAN_JORGENSEN = 82005,
    SPELL_SUMMON_PERSONAL_GUARDIAN_DANFORTH = 82007,
    SPELL_SUMMON_PERSONAL_GUARDIAN_KRAKAUER = 82008,
    SPELL_COMMANDING_SHOUT = 82061,
    QUEST_AHHHHHHHHHHHHH = 26708,
    QUEST_SHOWDOWN_AT_STONEWATCH = 26713,
    QUEST_DARKBLAZE_BROOD_OF_THE_WORLDBREAKER = 26714,
    QUEST_TRIUMPHANT_RETURN = 26726,
};

class npc_colonel_troteman_43733 : public CreatureScript
{
public:
    npc_colonel_troteman_43733() : CreatureScript("npc_colonel_troteman_43733") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) 
    { 
        if (quest->GetQuestId() == QUEST_AHHHHHHHHHHHHH)
        {
            player->CastSpell(player, SPELL_SUMMON_BRAVO_COMPANY_SIEGE_TANK, true);
        }
        if (quest->GetQuestId() == QUEST_SHOWDOWN_AT_STONEWATCH)
        {
            // missing change map ??
            SummonLevel17(creature);
            player->CastSpell(player, SPELL_SUMMON_PERSONAL_GUARDIAN_KEESHAN, true);
            player->CastSpell(player, SPELL_SUMMON_PERSONAL_GUARDIAN_MESSNER, true);
            player->CastSpell(player, SPELL_SUMMON_PERSONAL_GUARDIAN_JORGENSEN, true);
            player->CastSpell(player, SPELL_SUMMON_PERSONAL_GUARDIAN_DANFORTH, true);
            player->CastSpell(player, SPELL_SUMMON_PERSONAL_GUARDIAN_KRAKAUER, true);
            if (Creature* npc = player->FindNearestCreature(43812, 10.0f))
            {
                npc->AddAura(79849, npc);
                npc->SetByteValue(UNIT_FIELD_BYTES_2, 0, SHEATH_STATE_MELEE);
                npc->SetHomePosition(player->GetNearPosition(2.0f, frand(0, 6.24f)));
            }
            if (Creature* npc = player->FindNearestCreature(43826, 10.0f))
            {
                npc->SetByteValue(UNIT_FIELD_BYTES_2, 0, SHEATH_STATE_MELEE);
                npc->SetHomePosition(player->GetNearPosition(2.0f, frand(0, 6.24f)));
            }
            if (Creature* npc = player->FindNearestCreature(43827, 10.0f))
            {
                npc->AddAura(79962, npc);
                npc->AddAura(79963, npc);
                npc->SetByteValue(UNIT_FIELD_BYTES_2, 0, SHEATH_STATE_MELEE);
                npc->SetHomePosition(player->GetNearPosition(2.0f, frand(0, 6.24f)));
            }
            if (Creature* npc = player->FindNearestCreature(43828, 10.0f))
            {
                npc->SetByteValue(UNIT_FIELD_BYTES_2, 0, SHEATH_STATE_MELEE);
                npc->SetHomePosition(player->GetNearPosition(2.0f, frand(0, 6.24f)));
            }
            if (Creature* npc = player->FindNearestCreature(43829, 10.0f))
            {
                npc->SetByteValue(UNIT_FIELD_BYTES_2, 0, SHEATH_STATE_MELEE);
                npc->SetHomePosition(player->GetNearPosition(2.0f, frand(0, 6.24f)));
            }
        }
        if (quest->GetQuestId() == QUEST_DARKBLAZE_BROOD_OF_THE_WORLDBREAKER)
        {

        }
        return false; 
    }

    bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* quest, uint32 /*opt*/) 
    {
        if (quest->GetQuestId() == QUEST_AHHHHHHHHHHHHH) // this quest has buggy spell 81808 and is set to autocomplete
        {                                                // on end you should stay at "keeshans posten" and have aura "see invis 17"
            player->NearTeleportTo(-9143.38f, -3047.55f, 108.72f, 1.1947f);
            player->RemoveAura(SPELL_DETECT_QUEST_INVIS_13);
            player->RemoveAura(SPELL_DETECT_QUEST_INVIS_15);
            player->AddAura(SPELL_DETECT_QUEST_INVIS_17, player);
            player->AddAura(SPELL_DETECT_QUEST_INVIS_18, player);
        }
        if (quest->GetQuestId() == QUEST_SHOWDOWN_AT_STONEWATCH)
        {

        }
        if (quest->GetQuestId() == QUEST_DARKBLAZE_BROOD_OF_THE_WORLDBREAKER)
        {

        }
        return false; 
    }

    void SummonLevel17(Creature* npc)
    {
        if (Creature* target = npc->SummonCreature(4065, -9213.125f, -2982.141f, 100.0157f, 1.34429f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(4065, -9221.188f, -3056.101f, 100.8075f, 5.019916f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(4065, -9280.388f, -3025.233f, 119.9484f, 5.664678f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(4065, -9228.95f, -2929.91f, 112.9479f, 4.54403f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(4065, -9367.44f, -3070.87f, 149.3803f, 3.246312f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(4065, -9368.97f, -3087.17f, 149.3813f, 1.134464f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(4065, -9378.33f, -3084.07f, 140.5583f, 1.518436f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(4065, -9408.18f, -3060.87f, 140.5583f, 6.248279f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(4065, -9405.49f, -3065.58f, 164.6403f, 3.01942f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(4464, -9229.501f, -3011.467f, 101.0967f, 2.823587f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(4464, -9184.64f, -2931.53f, 107.8983f, 5.096361f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(4464, -9255.83f, -3024.38f, 115.2133f, 0.6806784f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(4464, -9317.43f, -2973.58f, 122.7913f, 4.29351f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(4464, -9291.47f, -2983.71f, 122.7743f, 4.34587f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(4464, -9274.663f, -2924.293f, 128.3869f, 2.20241f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(4464, -9305.78f, -2931.928f, 128.4665f, 4.234417f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(435, -9339.04f, -3041.75f, 135.9023f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(435, -9329.43f, -3025.18f, 134.1063f, 0.06981317f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(435, -9329.04f, -3032.32f, 133.8183f, 0.3665192f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(435, -9326.25f, -3015.28f, 135.6453f, 5.742133f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(435, -9385.44f, -3057.84f, 139.0983f, 1.64061f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(435, -9329.04f, -3032.32f, 133.8183f, 0.3665192f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(436, -9295.988f, -3045.026f, 124.1195f, 5.920075f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(436, -9266.205f, -2909.046f, 127.5425f, 3.558032f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(436, -9362.214f, -3016.605f, 136.7716f, 5.912722f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(436, -9362.97f, -3063.06f, 164.6403f, 0.2094395f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(436, -9382.58f, -3070.72f, 140.5583f, 3.211406f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(436, -9392.08f, -3053.25f, 156.6613f, 0.05235988f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(436, -9405.61f, -3087.89f, 139.6563f, 1.623156f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(436, -9415.86f, -3075.78f, 136.7763f, 2.443461f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(436, -9412.826f, -3030.809f, 136.7576f, 6.269172f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(436, -9440.95f, -3076.3f, 136.7703f, 0.715585f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(334, -9478.62f, -2963.11f, 129.3833f, 2.146755f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
        if (Creature* target = npc->SummonCreature(486, -9326.42f, -3028.35f, 133.1993f, 6.213372f, TEMPSUMMON_TIMED_DESPAWN, 900000))
            target->AddAura(SPELL_APPLY_QUEST_INVIS_17, target);
    }


    struct npc_colonel_troteman_43733AI : public ScriptedAI
    {
        npc_colonel_troteman_43733AI(Creature *c) : ScriptedAI(c) { }

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

        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_colonel_troteman_43733AI(creature);
    }
};

class npc_bravo_company_siege_tank : public CreatureScript
{
public:
    npc_bravo_company_siege_tank() : CreatureScript("npc_bravo_company_siege_tank") { }

    struct npc_bravo_company_siege_tankAI : public ScriptedAI
    {
        npc_bravo_company_siege_tankAI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;

        void Reset() override
        {
            m_timer = 1000;
            if (Creature* gun = me->SummonCreature(43745, me->GetPosition()))
                if (Creature* john = me->SummonCreature(43744, me->GetPosition()))
                {
                    gun->EnterVehicle(me, 1);
                    john->EnterVehicle(gun, 0);
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

        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bravo_company_siege_tankAI(creature);
    }
};

//######################################  Quest 26713 26714 26726

enum eQuest26713
{
    NPN_JOHN_J_KEESHAN_43812 = 43812, // hunter
    NPC_MESSNER_43826 = 43826,        // mage
    NPC_JORGENSEN_43827 = 43827,      // paladin
    NPN_DANFORTH_43828 = 43828,       // warrior
    NPC_KRAKAUER_43829 = 43829,       // warrior
    SPELL_SUMMON_DARKBLAZE = 81953,
    SPELL_DARKBLAZE_TRANSFORM = 82067,
    SPELL_CLEAR_DARKBLAZE_AURA = 82092,
    SPELL_DARKBLAZE_KILL_CREDIT = 82096,
    SPELL_SHOWDOWN_82010 = 82010,
    SPELL_SHOWDOWN_82086 = 82086,
    SPELL_MARK_MASTER_AS_DESUMMONED = 80929,
    SPELL_CANCEL_CAMOUFLAGE = 81554,
    SPELL_PERMANENT_FEIGN_DEATH = 29266,
    SPELL_SPARKLE = 99495,
    SPELL_SUMMON_PERSONAL_GUARDIAN_KEESHAN_82091 = 82091,
    SPELL_SUMMON_PERSONAL_GUARDIAN_MESSNER_82090 = 82090,
    SPELL_SUMMON_PERSONAL_GUARDIAN_JORGENSEN_82089 = 82089,
    SPELL_SUMMON_PERSONAL_GUARDIAN_DANFORTH_82088 = 82088,
    SPELL_SUMMON_PERSONAL_GUARDIAN_KRAKAUER_82087 = 82087,
};

class npc_john_j_keeshan_43812 : public CreatureScript
{
public:
    npc_john_j_keeshan_43812() : CreatureScript("npc_john_j_keeshan_43812") { }

    enum eKeeshan
    {
        Bloodthirst = 79878,
        CommandingShout = 82061,
        Immolation = 35935,
        ImmolationArrow = 82064,
        Rend = 11977,
        ShatteringThrow = 79883,
        Slam = 79881,
    };

    struct npc_john_j_keeshan_43812AI : public ScriptedAI
    {
        npc_john_j_keeshan_43812AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;

        void Reset() override
        {
            m_timer = 0;
            
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {

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
        return new npc_john_j_keeshan_43812AI(creature);
    }
};

class npc_messner_43826 : public CreatureScript
{
public:
    npc_messner_43826() : CreatureScript("npc_messner_43826") { }

    enum eMessner
    {
        BlastWave = 81996,
        Fireball = 79854,
        Flamestrike = 81995,
        MoltenArmor1 = 79849,
        MoltenArmor2 = 79848,
    };

    struct npc_messner_43826AI : public ScriptedAI
    {
        npc_messner_43826AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;

        void Reset() override
        {
            m_timer = 1000;
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {

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
        return new npc_messner_43826AI(creature);
    }
};

class npc_jorgensen_43827 : public CreatureScript
{
public:
    npc_jorgensen_43827() : CreatureScript("npc_jorgensen_43827") { }

    enum eJorgensen
    {
        ConcentrationAura = 79963,
        Exorcism = 79964,
        HolyLight = 79960,
        HolyShock = 79961,
        SealOfRighteousness = 79962,
    };

    struct npc_jorgensen_43827AI : public ScriptedAI
    {
        npc_jorgensen_43827AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;

        void Reset() override
        {
            m_timer = 1000;
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {

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
        return new npc_jorgensen_43827AI(creature);
    }
};

class npc_danforth_43828 : public CreatureScript
{
public:
    npc_danforth_43828() : CreatureScript("npc_danforth_43828") { }

    enum eDanforth
    {
        BattleShout = 81219,
        Charge = 22120,
        SunderArmor = 11971,
        Thunderclap = 8078,
    };

    struct npc_danforth_43828AI : public ScriptedAI
    {
        npc_danforth_43828AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;

        void Reset() override
        {
            m_timer = 1000;
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {

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
        return new npc_danforth_43828AI(creature);
    }
};

class npc_krakauer_43829 : public CreatureScript
{
public:
    npc_krakauer_43829() : CreatureScript("npc_krakauer_43829") { }

    enum eKrakauer
    {
        BattleShout = 32064,
        Bloodthirst = 79878,
        Rend = 11977,
        ShatteringThrow = 79883,
        Slam = 79881,
    };

    struct npc_krakauer_43829AI : public ScriptedAI
    {
        npc_krakauer_43829AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;

        void Reset() override
        {
            m_timer = 1000;
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {

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
        return new npc_krakauer_43829AI(creature);
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
    new vehicle_keeshans_riverboat_43450();
    new npc_john_j_keeshan_43449();
    new npc_john_j_keeshan_43457();
    new npc_john_j_keeshan_43458();
    new npc_jorgensen_43546();
    new npc_bravo_company_trigger();
    new npc_blackrock_grunt();
    new npc_blackrock_outrunner();
    new npc_blackrock_guard();
    new npc_blackrock_drake_rider();
    new npc_blackrock_warden();
    new go_blackrock_holding_pen();
    new spell_plant_seaforium();
    new npc_john_j_keeshan_43611();
    new npc_renders_valley_camera();
    new npc_grand_magus_doane();
    new npc_colonel_troteman_43733();
    new npc_bravo_company_siege_tank();
    new npc_john_j_keeshan_43812();
    new npc_messner_43826();
    new npc_jorgensen_43827();
    new npc_danforth_43828();
    new npc_krakauer_43829();
}

