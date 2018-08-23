/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
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

#include "script_helper.h"
#include "Creature.h"
#include "GameObjectAI.h"
#include "GameObject.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "SpellMgr.h"
#include "Vehicle.h"

enum eAnimRedridgeCity
{
    AREA_CAMP_EVERSTILL = 5326,
    GO_CHAIN_LEVER = 204403,
    GO_BLACKROCK_EXPLOSIVE_DEVICE_1 = 204444,
    GO_BLACKROCK_EXPLOSIVE_DEVICE_2 = 204445,
    GO_BLACKROCK_EXPLOSIVE_DEVICE_3 = 204446,
    GO_BLACKROCK_TOWER_OR_MUNITIONS_HUT = 301069,
    ITEM_BRAVO_COMPANY_FIELD_KIT_1 = 60384,
    ITEM_BRAVO_COMPANY_FIELD_KIT_2 = 60385,
    NPC_MAGISTRATE_SOLOMON = 344,
    NPC_CAT = 8963,
    NPC_JOHN_J_KEESHAN_43184 = 43184,
    NPC_COLONEL_TROTEMAN_43221 = 43221,
    NPC_BIG_EARL = 43248,
    NPC_DUMPY = 43249,
    NPC_MESSNER_43270 = 43270,
    NPC_JORGENSEN_43272 = 43272,
    NPC_KRAKAUER_43274 = 43274,
    NPC_DANFORTH_43275 = 43275,
    NPC_MESSNER_43300 = 43300,
    NPC_DANFORTH_43302 = 43302,
    NPC_KRAKAUER_43303 = 43303,
    NPC_JORGENSEN_43305 = 43305,
    NPC_DANFORT_INVISIBLE_DUMMY = 43366,
    NPC_MESSNER_43432 = 43432,
    NPC_JORGENSEN_43433 = 43433,
    NPC_KRAKAUER_43434 = 43434,
    NPC_DANFORTH_43435 = 43435,
    NPN_DANFORTH_43445 = 43445,
    NPC_KRAKAUER_43446 = 43446,
    NPC_JORGENSEN_43447 = 43447,
    NPC_MESSNER_43448 = 43448,
    NPN_JOHN_J_KEESHAN_43449 = 43449,
    NPC_KEESHANS_RIVERBOAT_43450 = 43450,
    NPN_JOHN_J_KEESHAN_43457 = 43457,
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
    NPC_AREA_TRIGGER_BUNNY = 47971,
    SPELL_DRINK_ALCOHOL = 58952,
    SPELL_APPLY_QUEST_INVIS_1 = 80895,
    SPELL_APPLY_QUEST_INVIS_2 = 80699,
    SPELL_APPLY_QUEST_INVIS_3 = 80815,
    SPELL_APPLY_QUEST_INVIS_4 = 80816,
    SPELL_APPLY_QUEST_INVIS_5 = 81003,
    SPELL_APPLY_QUEST_INVIS_9 = 81201,
    SPELL_APPLY_QUEST_INVIS_10 = 81240,
    SPELL_APPLY_QUEST_INVIS_11 = 81266,
    SPELL_APPLY_QUEST_INVIS_12 = 81496,
    SPELL_APPLY_QUEST_INVIS_13 = 81580,
    SPELL_APPLY_QUEST_INVIS_14 = 81583,
    SPELL_APPLY_QUEST_INVIS_15 = 81795,
    SPELL_APPLY_QUEST_INVIS_16 = 81805,
    SPELL_APPLY_QUEST_INVIS_17 = 81897,
    SPELL_APPLY_QUEST_INVIS_18 = 82059,
    SPELL_APPLY_QUEST_INVIS_19 = 82099,
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
    SPELL_DETECT_QUEST_INVIS_11 = 81267,
    SPELL_DETECT_QUEST_INVIS_12 = 81497,
    SPELL_DETECT_QUEST_INVIS_13 = 81581,
    SPELL_DETECT_QUEST_INVIS_14 = 81584,
    SPELL_DETECT_QUEST_INVIS_15 = 81794,
    SPELL_DETECT_QUEST_INVIS_16 = 81804,
    SPELL_DETECT_QUEST_INVIS_17 = 81898,
    SPELL_DETECT_QUEST_INVIS_18 = 82060,
    SPELL_DETECT_QUEST_INVIS_19 = 82100,
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
    SPELL_CHAINS_OF_CRUELTY_1 = 81081,
    SPELL_CHAINS_OF_CRUELTY_2 = 81085,
    SPELL_BAKER_TEAM_BROADCAST = 81155,
    SPELL_KEESHANS_HEADBAND = 81234,
    SPELL_LOG_SMASH = 88421,
    SPELL_MESSNER_BOAT_ENGINE = 81260,
    SPELL_RIVERBOAT_QUEST_CREDIT = 81265,
    SPELL_SUMMON_JORGENSEN_43546_81477 = 81447,
    SPELL_SEAL_OF_RIGHTEOUSNESS_81454 = 81454,
    SPELL_CONCENTRATION_AURA_81455 = 81455,
    SPELL_STATIC_SOUND = 81769,
    SPELL_DISTRACTION = 82578,
    SPELL_CHLOROFORM = 82579,
    SPELL_BRAVO_COMPANY_FIELD_KIT_1_60384 = 82580,
    SPELL_BRAVO_COMPANY_FIELD_KIT_2_60385 = 82587,
    SPELL_DISTRACTION_VISUAL = 81370,
    SPELL_DEADLY_POISEN = 10022,
    SPELL_CAMOUFLAGE = 82577,
    QUEST_JOHN_J_KEESHAN = 26567,
    QUEST_THIS_AINT_MY_WAR = 26568,
    QUEST_IN_SEARCH_OF_BRAVO_COMPANY = 26586,
    QUEST_WE_MUST_PREPARE = 26510,
    QUEST_TUNING_THE_GNOMECORDER = 26512,
    QUEST_CANYON_ROMP = 26514,
    QUEST_SAVING_FOREMAN_OSLOW = 26520,
    QUEST_YOWLER_MUST_DIE = 26545,
    QUEST_BREAKING_OUT_IS_HARD_TO_DO = 26587,
    QUEST_JORGENSEN = 26560,
    QUEST_KRAKAUER = 26561,
    QUEST_AND_LAST_BUT_NOT_LEAST_DANFORD = 26562,
    QUEST_RETURN_OF_THE_BRAVO_COMPANY = 26563,
    QUEST_THEY_DREW_FIRST_BLOOD = 26607,
    QUEST_ITS_NEVER_OVER = 26616,
    QUEST_PRISONERS_OF_WAR = 26646,
    QUEST_TO_WIN_A_WAR_YOU_GOTTA_BECOME_WAR = 26651,
    QUEST_DETONATION = 26668,
};

// player
class player_zone_redridge_mountains : public PlayerScript
{
public:
    player_zone_redridge_mountains() : PlayerScript("player_zone_redridge_mountains") { }

    void OnLogin(Player* player) 
    { 
        if ((player->GetQuestStatus(QUEST_JORGENSEN) == QUEST_STATUS_INCOMPLETE) || (player->GetQuestStatus(QUEST_JORGENSEN) == QUEST_STATUS_COMPLETE))
        {
            player->CastSpell(player, SPELL_SUMMON_MESSNER);
        }
        else if ((player->GetQuestStatus(QUEST_KRAKAUER) == QUEST_STATUS_INCOMPLETE) || (player->GetQuestStatus(QUEST_KRAKAUER) == QUEST_STATUS_COMPLETE))
        {
            player->CastSpell(player, SPELL_SUMMON_MESSNER); 
            player->CastSpell(player, SPELL_SUMMON_JORGENSEN);
        }
        else if ((player->GetQuestStatus(QUEST_AND_LAST_BUT_NOT_LEAST_DANFORD) == QUEST_STATUS_INCOMPLETE) || (player->GetQuestStatus(QUEST_AND_LAST_BUT_NOT_LEAST_DANFORD) == QUEST_STATUS_COMPLETE))
        {
            player->CastSpell(player, SPELL_SUMMON_MESSNER);
            player->CastSpell(player, SPELL_SUMMON_JORGENSEN);
            player->CastSpell(player, SPELL_SUMMON_KRAKAUER);
        }
        else if ((player->GetQuestStatus(QUEST_RETURN_OF_THE_BRAVO_COMPANY) == QUEST_STATUS_INCOMPLETE) || (player->GetQuestStatus(QUEST_RETURN_OF_THE_BRAVO_COMPANY) == QUEST_STATUS_COMPLETE))
        {
            player->CastSpell(player, SPELL_SUMMON_MESSNER);
            player->CastSpell(player, SPELL_SUMMON_JORGENSEN);
            player->CastSpell(player, SPELL_SUMMON_KRAKAUER);
            player->CastSpell(player, SPELL_SUMMON_DANFORTH);
        }
        else if ((player->GetQuestStatus(QUEST_ITS_NEVER_OVER) == QUEST_STATUS_INCOMPLETE) || (player->GetQuestStatus(QUEST_ITS_NEVER_OVER) == QUEST_STATUS_COMPLETE))
        {
           
        }
        else if (player->GetQuestStatus(QUEST_PRISONERS_OF_WAR) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_TO_WIN_A_WAR_YOU_GOTTA_BECOME_WAR) == QUEST_STATUS_INCOMPLETE)
        {
            Unit* unit = player->GetFirstControlled();
            if (!unit)
                player->CastSpell(player, SPELL_SUMMON_JORGENSEN_43546_81477, true);
        }



    }

    void OnQuestRemove(Player* player, uint32 questId) override
    {
       
    }
};

// 344
class npc_magistrate_solomon_344 : public CreatureScript
{
public:
    npc_magistrate_solomon_344() : CreatureScript("npc_magistrate_solomon_344") { }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        switch (quest->GetQuestId())
        {
        case QUEST_WE_MUST_PREPARE:
        case QUEST_TUNING_THE_GNOMECORDER:
        {
            player->AddAura(SPELL_GNOMECORDER, player);
            player->AddAura(SPELL_DETECT_QUEST_INVIS_1, player);
            player->AddAura(SPELL_DETECT_QUEST_INVIS_3, player);
            break;
        }
        }
        return false;
    }
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

// 43249
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

// 43248
class npc_big_earl_43248 : public CreatureScript
{
public:
    npc_big_earl_43248() : CreatureScript("npc_big_earl_43248") { }

    struct npc_big_earl_43248AI : public ScriptedAI
    {
        npc_big_earl_43248AI(Creature *c) : ScriptedAI(c) { }

        EventMap m_events;
        uint64 m_targetGUID;
        FakeAttackMembers m_showFight;

        void Reset() override
        {
            m_events.RescheduleEvent(EVENT_INIT_TARGET, 1000);
            m_targetGUID = 0;
            m_showFight = FakeAttackMembers(me);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            damage = 0;
        }

        void AttackStart(Unit* who) override
        {
            AttackStartNoMove(who);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_INIT_TARGET:
                {
                    if (!m_showFight.m_hasInit)
                    {
                        std::list<uint32> asList;
                        if (Creature* npc = me->FindNearestCreature(NPC_DUMPY, 15.0f))
                        {
                            asList.push_back(npc->GetEntry());
                            m_targetGUID = npc->GetGUID();
                        }
                        if (Creature* npc = me->FindNearestCreature(NPC_BIG_EARL, 15.0f))
                        {
                            asList.push_back(npc->GetEntry());
                            m_targetGUID = npc->GetGUID();
                        }
                        m_showFight.Initialize(asList);
                    }
                    m_events.ScheduleEvent(EVENT_CHECK_FIGHT, 1000);
                    break;
                }
                case EVENT_CHECK_FIGHT:
                {
                    if (Creature* creature = m_showFight.GetSparringPartner())
                    {
                        if (!me->IsInCombat())
                            me->Attack(creature, true);
                    }
                    else if (Creature* creature = m_showFight.GetRangedPartner())
                    {
                        me->SetFacingToObject(creature);
                        if (uint32 spellId = m_showFight.GetRangedSpellId())
                            me->CastSpell(creature, spellId, true);
                        me->GetMotionMaster()->MoveIdle();
                    }

                    m_events.ScheduleEvent(EVENT_CHECK_FIGHT, urand(900, 1200));
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_big_earl_43248AI(creature);
    }
};

// 43247
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

// 6034
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

// 43094
class npc_canyon_ettin_43094 : public CreatureScript
{

public:
    npc_canyon_ettin_43094() : CreatureScript("npc_canyon_ettin_43094") { }

    struct npc_canyon_ettin_43094_AI : public ScriptedAI
    {
        npc_canyon_ettin_43094_AI(Creature *c) : ScriptedAI(c) { }

        EventMap m_events;

        void Reset() override
        {
            DoAction(1);
            m_events.RescheduleEvent(EVENT_CHECK_FOR_PLAYER, 1000);
        }

        void EnterCombat(Unit* victim) override 
        { 
            me->CastSpell(victim, SPELL_LOG_SMASH, true);
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case 1:
            {
                m_events.RescheduleEvent(EVENT_CAST_COOLDOWN, 30 * 60 * 1000); // 30 minutes
                if (!me->isActiveObject())
                    me->setActive(true);
                break;
            }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CAST_COOLDOWN:
                {
                    me->setActive(false);
                    break;
                }
                case EVENT_CHECK_FOR_PLAYER:
                {
                    std::list<Player*> pList = me->FindNearestPlayers(100.0f);
                    for (auto player : pList)
                        if (player->GetQuestStatus(QUEST_SAVING_FOREMAN_OSLOW) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_CANYON_ROMP) == QUEST_STATUS_INCOMPLETE)
                            DoAction(1);

                    m_events.RescheduleEvent(EVENT_CHECK_FOR_PLAYER, 1000);
                    break;
                }
                }
            }
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_canyon_ettin_43094_AI(creature);
    }

};

// 43197
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
        PATH_GO_BACK_TO_MOUNTAIN = 431972,
        PATH_GO_TO_BRIDGE = 431971,
        SAY_OSLOW_JUST_REPAIR_BRIDGE = 0,
        SAY_OSLOW_THANKS = 1,
    };

public:
    npc_canyon_ettin_43197() : CreatureScript("npc_canyon_ettin_43197") { }

    struct npc_canyon_ettin_43197_AI : public VehicleAI
    {
        npc_canyon_ettin_43197_AI(Creature *c) : VehicleAI(c) { Initialize(); }

        EventMap m_events;
        uint64 m_playerGUID;
        uint64 m_oslowGUID;
        uint64 m_boulderGUID;
        uint64 m_trentGUID;
        uint64 m_dmitriGUID;
        uint64 m_jessGUID;
        uint64 m_danielGUID;
        uint64 m_matthewGUID;
        uint64 m_alexGUID;
        uint32 m_state;

        void Initialize()
        {
            m_playerGUID = 0;
            m_oslowGUID = 0;
            m_boulderGUID = 0;
            m_trentGUID = 0;
            m_dmitriGUID = 0;
            m_jessGUID = 0;
            m_danielGUID = 0;
            m_matthewGUID = 0;
            m_alexGUID = 0;
            m_state = 0;
        }

        void Reset() override
        {
            me->SetReactState(REACT_DEFENSIVE);
            m_events.RescheduleEvent(EVENT_CHECK_FOLLOWING, 1000);
        }

        void IsSummonedBy(Unit* summoner) override 
        {
            if (Player* player = summoner->ToPlayer())
            {
                m_playerGUID = summoner->GetGUID();
                me->GetMotionMaster()->MoveFollow(player, 8.0f, 3.14f);
            }
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override 
        { 
            if (apply)
            {
                if (Player* player = GetPlayer())
                    Talk(0, player);
                m_events.ScheduleEvent(EVENT_TALK_PART_01, 2000);
            }
            else
            {
                me->HandleEmote(EMOTE_STATE_NONE);
                m_events.ScheduleEvent(EVENT_TALK_PART_07, 2000);
            }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == WAYPOINT_MOTION_TYPE)
                switch (m_state)
                {
                case 3:
                    switch (id)
                    {
                    case 1:
                        if (Player* player = GetPlayer())
                            if (Creature* oslow = sObjectAccessor->GetCreature(*me, m_oslowGUID))
                                oslow->AI()->Talk(SAY_OSLOW_THANKS, player);
                        break;
                    case 4:
                        if (Creature* oslow = sObjectAccessor->GetCreature(*me, m_oslowGUID))
                            oslow->DespawnOrUnsummon();
                        break;
                    case 5: // last point in path 1
                        m_events.ScheduleEvent(EVENT_TALK_PART_06, 10);
                        break;
                    }
                    break;
                case 4:
                    switch (id)
                    {
                    case 3:
                        if (Player* player = GetPlayer())
                            Talk(3, player);
                        break;
                    case 5: // last point in path 2
                        m_events.ScheduleEvent(EVENT_TALK_PART_09, 10);
                        break;
                    }
                    break;
                case 5:
                    break;
                }
              
        }

        void EnterEvadeMode() override 
        { 
            if (m_state == 0)
            {
                me->SetReactState(REACT_DEFENSIVE);
                if (Player* player = GetPlayer())
                    me->GetMotionMaster()->MoveFollow(player, 8.0f, 3.14f);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            VehicleAI::UpdateAI(diff);
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_FOLLOWING:
                {
                    if (!me->IsInCombat())
                    if (Player* player = GetPlayer())
                        if (player->IsInCombat())
                            if (Unit* target = player->GetSelectedUnit())
                                if (Creature* victim = target->ToCreature())
                                {
                                    me->GetMotionMaster()->Clear(false);
                                    me->GetMotionMaster()->MoveIdle();
                                    me->SetReactState(REACT_AGGRESSIVE);
                                    me->Attack(victim, true);
                                }

                    if (CheckAllGuids())
                        if (Creature* boulder = sObjectAccessor->GetCreature(*me, m_boulderGUID))
                            if (me->GetDistance(boulder) < 8.0f)
                            {
                                me->GetMotionMaster()->Clear(false);
                                me->GetMotionMaster()->MoveIdle();
                                m_state = 1;
                                m_events.ScheduleEvent(EVENT_TALK_PART_00, 1000);
                                break;
                            }

                    m_events.RescheduleEvent(EVENT_CHECK_FOLLOWING, 500);
                    break;
                }
                case EVENT_TALK_PART_00:
                {
                    if (Creature* boulder = sObjectAccessor->GetCreature(*me, m_boulderGUID))
                        me->CastSpell(boulder, SPELL_LIFT_HUGE_BOULDER, true);
                    if (Creature* trent = sObjectAccessor->GetCreature(*me, m_trentGUID))
                        trent->HandleEmoteState(EMOTE_STATE_STAND);
                    if (Creature* dmitri = sObjectAccessor->GetCreature(*me, m_dmitriGUID))
                        dmitri->HandleEmoteState(EMOTE_STATE_STAND);
                    if (Creature* jess = sObjectAccessor->GetCreature(*me, m_jessGUID))
                        jess->HandleEmoteState(EMOTE_STATE_STAND);
                    if (Creature* daniel = sObjectAccessor->GetCreature(*me, m_danielGUID))
                        daniel->HandleEmoteState(EMOTE_STATE_STAND);
                    if (Creature* matthew = sObjectAccessor->GetCreature(*me, m_matthewGUID))
                        matthew->HandleEmoteState(EMOTE_STATE_STAND);
                    if (Creature* alex = sObjectAccessor->GetCreature(*me, m_alexGUID))
                        alex->HandleEmoteState(EMOTE_STATE_STAND);
                    
                    break;
                }
                case EVENT_TALK_PART_01:
                {
                    if (Creature* oslow = sObjectAccessor->GetCreature(*me, m_oslowGUID))
                    {
                        oslow->SetUInt32Value(UNIT_FIELD_BYTES_1, UNIT_STAND_STATE_KNEEL);
                        oslow->SetWalk(true);
                        oslow->SetSpeed(MOVE_WALK, 1.0f, true);
                    }
                    m_events.ScheduleEvent(EVENT_TALK_PART_02, 2000);
                    break;
                }
                case EVENT_TALK_PART_02:
                {
                    if (Player* player = GetPlayer())
                        Talk(1, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_03, 4000);
                    break;
                }
                case EVENT_TALK_PART_03:
                {
                    if (Player* player = GetPlayer())
                    {
                        if (Creature* trent = sObjectAccessor->GetCreature(*me, m_trentGUID))
                            trent->AI()->Talk(1, player);
                        if (Creature* daniel = sObjectAccessor->GetCreature(*me, m_danielGUID))
                            daniel->AI()->Talk(1, player);
                        if (Creature* oslow = sObjectAccessor->GetCreature(*me, m_oslowGUID))
                            oslow->HandleEmoteState(EMOTE_STATE_STAND);
                    }
                    m_events.ScheduleEvent(EVENT_TALK_PART_04, 1500);
                    break;
                }
                case EVENT_TALK_PART_04:
                {
                    if (Creature* oslow = sObjectAccessor->GetCreature(*me, m_oslowGUID))
                    {
                        m_state = 2;
                        oslow->SetWalk(true);
                        oslow->GetMotionMaster()->MovePoint(1020, -9273.9f, -2185.4f, 64.09f);
                    }
                    m_events.ScheduleEvent(EVENT_TALK_PART_05, 2000);
                    break;
                }
                case EVENT_TALK_PART_05:
                {
                    if (Creature* oslow = sObjectAccessor->GetCreature(*me, m_oslowGUID))
                        oslow->AI()->Talk(SAY_OSLOW_JUST_REPAIR_BRIDGE);

                    if (Player* player = GetPlayer())
                        Talk(2, player);

                    m_state = 3;
                    me->SetWalk(true);
                    me->SetSpeed(MOVE_WALK, 1.2f, true);
                    me->GetMotionMaster()->MovePath(PATH_GO_TO_BRIDGE, false);  // start path 1
                    break;
                }
                case EVENT_TALK_PART_06:
                {
                    me->CastSpell(me, SPELL_EJECT_PASSENGER_1);
                    break;
                }
                case EVENT_TALK_PART_07:
                {
                    if (Creature* boulder = sObjectAccessor->GetCreature(*me, m_boulderGUID))
                        boulder->DespawnOrUnsummon(10);
                    me->GetMotionMaster()->InitDefault();
                    me->HandleEmote(EMOTE_STATE_NONE);
                    m_events.ScheduleEvent(EVENT_TALK_PART_08, 2000);
                    break;
                }
                case EVENT_TALK_PART_08:
                {
                    m_state = 4;
                    me->SetWalk(true);
                    me->GetMotionMaster()->MovePath(PATH_GO_BACK_TO_MOUNTAIN, false);  // start path 2
                    break;
                }
                case EVENT_TALK_PART_09:
                {
                    m_state = 5;
                    if (Unit* unit = me->GetOwner())
                        if (Player* player = unit->ToPlayer())
                        {
                            player->CastSpell(player, SPELL_KILL_CREDIT_ETTIN_QUEST);
                            player->KilledMonsterCredit(341);
                        }
                    m_events.ScheduleEvent(EVENT_TALK_PART_10, 1000);
                    break;
                }
                case EVENT_TALK_PART_10:
                {
                    if (Creature* trent = sObjectAccessor->GetCreature(*me, m_trentGUID))
                        trent->DespawnOrUnsummon(10);
                    if (Creature* dmitri = sObjectAccessor->GetCreature(*me, m_dmitriGUID))
                        dmitri->DespawnOrUnsummon(10);
                    if (Creature* jess = sObjectAccessor->GetCreature(*me, m_jessGUID))
                        jess->DespawnOrUnsummon(10);
                    if (Creature* daniel = sObjectAccessor->GetCreature(*me, m_danielGUID))
                        daniel->DespawnOrUnsummon(10);
                    if (Creature* matthew = sObjectAccessor->GetCreature(*me, m_matthewGUID))
                        matthew->DespawnOrUnsummon(10);
                    if (Creature* alex = sObjectAccessor->GetCreature(*me, m_alexGUID))
                        alex->DespawnOrUnsummon();

                    me->DespawnOrUnsummon(10);
                    break;
                }                
                }
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

        Player* GetPlayer()
        {
            if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                return player;

            return nullptr;
        }

        bool CheckAllGuids()
        {
            if (!m_oslowGUID)
                if (Creature* oslow = me->FindNearestCreature(NPC_FOREMAN_OSLOW, 100.0f))
                    m_oslowGUID = oslow->GetGUID();
            if (!m_boulderGUID)
                if (Creature* boulder = me->FindNearestCreature(NPC_HUGE_BOULDER, 50.0f))
                    m_boulderGUID = boulder->GetGUID();
            if (!m_trentGUID)
                if (Creature* trent = me->FindNearestCreature(NPC_BRIDGE_WORKER_TRENT, 50.0f))
                    m_trentGUID = trent->GetGUID();
            if (!m_dmitriGUID)
                if (Creature* dmitri = me->FindNearestCreature(NPC_BRIDGE_WORKER_DMITRI, 50.0f))
                    m_dmitriGUID = dmitri->GetGUID();
            if (!m_jessGUID)
                if (Creature* jess = me->FindNearestCreature(NPC_BRIDGE_WORKER_JESS, 50.0f))
                    m_jessGUID = jess->GetGUID();
            if (!m_danielGUID)
                if (Creature* daniel = me->FindNearestCreature(NPC_BRIDGE_WORKER_DANIEL, 50.0f))
                    m_danielGUID = daniel->GetGUID();
            if (!m_matthewGUID)
                if (Creature* matthew = me->FindNearestCreature(NPC_BRIDGE_WORKER_MATTHEW, 50.0f))
                    m_matthewGUID = matthew->GetGUID();
            if (!m_alexGUID)
                if (Creature* alex = me->FindNearestCreature(NPC_BRIDGE_WORKER_ALEX, 50.0f))
                    m_alexGUID = alex->GetGUID();

            if (m_oslowGUID)
                if (m_boulderGUID)
                    if (m_trentGUID)
                        if (m_dmitriGUID)
                            if (m_jessGUID)
                                if (m_danielGUID)
                                    if (m_matthewGUID)
                                        if (m_alexGUID)
                                            return true;

            return false;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_canyon_ettin_43197_AI(creature);
    }
   
};

// 43221
class npc_colonel_troteman_43221 : public CreatureScript
{
public:
    npc_colonel_troteman_43221() : CreatureScript("npc_colonel_troteman_43221") { }
    
    bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* quest, uint32 /*opt*/) 
    { 
        switch (quest->GetQuestId())
        {
        case QUEST_THIS_AINT_MY_WAR:
        {
            player->RemoveAura(SPELL_DETECT_QUEST_INVIS_4);
            break;
        }
        case QUEST_RETURN_OF_THE_BRAVO_COMPANY:
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
            break;
        }
        }
        return false; 
    }

    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest) 
    { 
        switch (quest->GetQuestId())
        {
        case QUEST_JOHN_J_KEESHAN:
        case QUEST_IN_SEARCH_OF_BRAVO_COMPANY:
        {
            player->AddAura(SPELL_GNOMECORDER, player);
            player->AddAura(SPELL_DETECT_QUEST_INVIS_1, player);
            player->AddAura(SPELL_DETECT_QUEST_INVIS_3, player);
            break;
        }
        case QUEST_THEY_DREW_FIRST_BLOOD:
        {
            player->AddAura(SPELL_DETECT_QUEST_INVIS_9, player);
            break;
        }
        }
        return false; 
    }

    struct npc_colonel_troteman_43221AI : public ScriptedAI
    {
        npc_colonel_troteman_43221AI(Creature *c) : ScriptedAI(c) { }

        EventMap m_events;
        std::set<uint64> pList;
        uint64 m_playerGUID;
        uint64 m_solomonGUID;
        bool   m_showVideo;

        void Reset() override
        {
            m_playerGUID = 0;
            m_solomonGUID = 0;
            m_showVideo = false;
            m_events.RescheduleEvent(EVENT_CHECK_PLAYER_NEAR, 1000);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_MASTER_RESET:
                {
                    m_playerGUID = 0;
                    m_showVideo = false;
                    m_events.Reset();
                    m_events.ScheduleEvent(EVENT_CHECK_PLAYER_NEAR, 1000);
                    break;
                }
                case EVENT_CHECK_PLAYER_NEAR:
                {
                    if (!m_showVideo)
                        if (Player* player = CheckForPlayer())
                        {
                            m_playerGUID = player->GetGUID();
                            m_showVideo = true;
                            m_events.ScheduleEvent(EVENT_TALK_PART_00, 1000);
                            m_events.RescheduleEvent(EVENT_MASTER_RESET, 75000);                            
                            break;
                        }

                    m_events.ScheduleEvent(EVENT_CHECK_PLAYER_NEAR, 1000);
                    break;
                }
                case EVENT_TALK_PART_00:
                {
                    if (Player* player = GetPlayer())
                        if (Creature* solomon = GetSolomon())
                            solomon->AI()->Talk(0, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_01, 6000);
                    break;
                }
                case EVENT_TALK_PART_01:
                {
                    if (Player* player = GetPlayer())
                        if (Creature* solomon = GetSolomon())
                            solomon->AI()->Talk(1, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_02, 8000);
                    break;
                }
                case EVENT_TALK_PART_02:
                {
                    if (Player* player = GetPlayer())
                        Talk(0, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_03, 5000);
                    break;
                }
                case EVENT_TALK_PART_03:
                {
                    if (Player* player = GetPlayer())
                        if (Creature* solomon = GetSolomon())
                            solomon->AI()->Talk(2, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_04, 5000);
                    break;
                }
                case EVENT_TALK_PART_04:
                {
                    if (Player* player = GetPlayer())
                        Talk(1, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_05, 5000);
                    break;
                }
                case EVENT_TALK_PART_05:
                {
                    if (Player* player = GetPlayer())
                        Talk(2, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_06, 7000);
                    break;
                }
                case EVENT_TALK_PART_06:
                {
                    if (Player* player = GetPlayer())
                        Talk(3, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_07, 5000);
                    break;
                }
                case EVENT_TALK_PART_07:
                {
                    if (Player* player = GetPlayer())
                        Talk(4, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_08, 5000);
                    break;
                }
                case EVENT_TALK_PART_08:
                {
                    if (Player* player = GetPlayer())
                        if (Creature* solomon = GetSolomon())
                            solomon->AI()->Talk(3, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_09, 7000);
                    break;
                }
                case EVENT_TALK_PART_09:
                {
                    if (Player* player = GetPlayer())
                        Talk(5, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_10, 7000);
                    break;
                }
                case EVENT_TALK_PART_10:
                {
                    AddPlayer();
                    m_showVideo = false;
                    m_playerGUID = 0;
                    m_events.CancelEvent(EVENT_MASTER_RESET);
                    m_events.ScheduleEvent(EVENT_CHECK_PLAYER_NEAR, 1000);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

        void AddPlayer()
        {
            if (!HasPlayer())
                pList.insert(m_playerGUID);
        }

        bool HasPlayer()
        {
            return (pList.find(m_playerGUID) != pList.end());
        }

        bool HasPlayer(uint64 guid)
        {
            return (pList.find(guid) != pList.end());
        }

        Player* GetPlayer()
        {
            return ObjectAccessor::GetPlayer(*me, m_playerGUID);
        }

        Creature* GetSolomon()
        {
            if (Creature* solomon = sObjectAccessor->GetCreature(*me, m_solomonGUID))
                return solomon;

            if (Creature* solomon = me->FindNearestCreature(NPC_MAGISTRATE_SOLOMON, 10.0f))
            {
                m_solomonGUID = solomon->GetGUID();
                return solomon;
            }

            return nullptr;
        }

        Player* CheckForPlayer()
        {
            std::list<Player*> cpList = me->FindNearestPlayers(15.0f, true);
            for (auto player : cpList)
                if (!HasPlayer(player->GetGUID()))
                    if (player->GetQuestStatus(QUEST_JOHN_J_KEESHAN) == QUEST_STATUS_NONE && player->GetQuestStatus(QUEST_YOWLER_MUST_DIE) == QUEST_STATUS_REWARDED)
                        return player;

            return nullptr;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_colonel_troteman_43221AI(creature);
    }
};

// 43184
class npc_john_j_keeshan_43184 : public CreatureScript
{
public:
    npc_john_j_keeshan_43184() : CreatureScript("npc_john_j_keeshan_43184") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_ITS_NEVER_OVER)
        {
            player->AddAura(SPELL_DETECT_QUEST_INVIS_10, player);
            creature->AI()->Talk(0, player);

            if (Creature* krakauer = creature->FindNearestCreature(NPC_KRAKAUER_43434, 10.0f))
                krakauer->AI()->Talk(0, player);

            if (Creature* danforth = creature->FindNearestCreature(NPC_DANFORTH_43435, 10.0f))
                danforth->AI()->Talk(0, player);

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
            if (me->HasAura(81201))
                me->setFaction(35);
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

// 8962
class npc_hilary_8962 : public CreatureScript
{
public:
    npc_hilary_8962() : CreatureScript("npc_hilary_8962") { }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        if (Creature* cat = creature->FindNearestCreature(NPC_CAT, 5.0f))
            cat->AI()->Talk(0, player);

        creature->AI()->Talk(0, player);
        return false;
    }
};

// 43270
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
        uint64 m_playerGUID;

        void Reset() override
        {
            m_timer = 0;
            m_phase = 0;
            m_playerGUID = 0;
        }

        void StartAnim(Player* player)
        {            
            m_playerGUID = player->GetGUID();
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
                if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                    Talk(0, player);
                m_timer = 2000; m_phase = 2;
                break;
            case 2:
                if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                    player->CastSpell(player, SPELL_SUMMON_MESSNER);

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

// 43300
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

// 43272
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
        uint64 m_playerGUID;

        void Reset() override
        {
            m_timer = 0;
            m_phase = 0;
            m_playerGUID = 0;
        }

        void StartAnim(Player* player)
        {
            m_playerGUID = player->GetGUID();
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
                if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                    Talk(0, player);
                m_timer = 2000; m_phase = 2;
                break;
            case 2:
                if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                    player->CastSpell(player, SPELL_SUMMON_JORGENSEN);

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

// 43305
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

// 43274
class npc_krakauer_43274 : public CreatureScript
{
public:
    npc_krakauer_43274() : CreatureScript("npc_krakauer_43274") { }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        creature->AI()->Talk(0, player);
        
        player->CastSpell(player, SPELL_SUMMON_KRAKAUER);
        return false;
    }
};

// 43303
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

// 43275
class npc_danforth_43275 : public CreatureScript
{
public:
    npc_danforth_43275() : CreatureScript("npc_danforth_43275") { }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        creature->DespawnOrUnsummon(10);
        player->CastSpell(player, SPELL_SUMMON_DANFORTH);
        return true;
    }

    struct npc_danforth_43275AI : public ScriptedAI
    {
        npc_danforth_43275AI(Creature *c) : ScriptedAI(c) { }

        EventMap m_events;
        uint64   m_leftDummyGUID, m_rightDummyGUID;
        
        void Reset() override
        {
            m_leftDummyGUID = 0;
            m_rightDummyGUID = 0;
            me->SetDisableGravity(true);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP & UNIT_NPC_FLAG_QUESTGIVER);
            m_events.RescheduleEvent(EVENT_INIT_TARGET, 500);
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case 1:
            {
                m_events.ScheduleEvent(EVENT_FINISH, 100);
                break;
            }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_INIT_TARGET:
                {
                    std::list<Creature*> cList = me->FindNearestCreatures(43366, 20.0f);
                    for (auto creature : cList)
                        if (creature->m_positionX > -8806.0f)
                        {
                            me->AddAura(81081, creature);
                            m_leftDummyGUID = creature->GetGUID();
                        }
                        else
                        {
                            me->AddAura(81085, creature);
                            m_rightDummyGUID = creature->GetGUID();
                        }
                    break;
                }
                case EVENT_FINISH:
                {
                    if (Creature* dummy = ObjectAccessor::GetCreature(*me, m_leftDummyGUID))
                        dummy->RemoveAura(81081);
                    if (Creature* dummy = ObjectAccessor::GetCreature(*me, m_rightDummyGUID))
                        dummy->RemoveAura(81085);
                    me->SetDisableGravity(false);
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP & UNIT_NPC_FLAG_QUESTGIVER);
                    break;
                }
                }
            }
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_danforth_43275AI(creature);
    }
};

// 43302
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
        uint64 m_playerGUID;

        void Reset() override
        {
            me->SetReactState(REACT_DEFENSIVE);
            m_timer = 1000; m_phase = 1;
        }

        void IsSummonedBy(Unit* summoner) override 
        { 
            if (Player* player = summoner->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                player->RemoveAura(SPELL_DETECT_QUEST_INVIS_8);
                player->AddAura(SPELL_REDRIDGE_TEAM_AURA, player);
                player->AddAura(SPELL_REDRIDGE_TEAM_AURA, me);
                player->CastSpell(player, SPELL_GNOMECORDER);
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
                if (m_NewSpawned)
                {
                    // Danforth is only swimming.. he walk not upto land.. so i teleport him.. 
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                    {
                        me->NearTeleportTo(-8819.81f, -2188.81f, 138.765f, 2.3f);
                        m_NewSpawned = false;
                        Talk(6, player);
                    }
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

// 80887
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
                    danforth->AI()->DoAction(1);
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

// 43450
class vehicle_keeshans_riverboat_43450 : public CreatureScript
{
public:
    vehicle_keeshans_riverboat_43450() : CreatureScript("vehicle_keeshans_riverboat_43450") { }

    struct vehicle_keeshans_riverboat_43450AI : public VehicleAI
    {
        vehicle_keeshans_riverboat_43450AI(Creature* creature) : VehicleAI(creature) {}

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_danforthGUID;
        uint64   m_krakauerGUID;
        uint64   m_jorgensenGUID;
        uint64   m_messnerGUID;
        uint64   m_keeshanGUID;

        void AttackStart(Unit* /*who*/) {}
        void EnterCombat(Unit* /*who*/) {}
        void EnterEvadeMode() {}

        void Reset()
        {
            m_playerGUID = 0;
            m_danforthGUID = 0;
            m_krakauerGUID = 0;
            m_jorgensenGUID = 0;
            m_messnerGUID = 0;
            m_keeshanGUID = 0;
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == WAYPOINT_MOTION_TYPE)
                switch (id)
                {
                case 10:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        if (Creature* keeshan = sObjectAccessor->GetCreature(*me, m_keeshanGUID))
                        {
                            keeshan->AI()->Talk(1, player);
                            player->AddAura(SPELL_DETECT_QUEST_INVIS_10, player);
                        }
                    break;
                }
                case 11:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        if (Quest const* qInfo = sObjectMgr->GetQuestTemplate(QUEST_ITS_NEVER_OVER))
                            me->CastSpell(me, SPELL_RIVERBOAT_QUEST_CREDIT, true);

                    m_events.ScheduleEvent(EVENT_TALK_PART_04, 500);
                    break;
                }
                }
        }

        void PassengerBoarded(Unit* who, int8 seatId, bool apply) override
        {
            if (apply)
            {
                if (Player* player = who->ToPlayer())
                {
                    m_playerGUID = player->GetGUID();
                    player->RemoveAura(SPELL_GNOMECORDER);
                    m_events.RescheduleEvent(EVENT_ANIMATION_START, 500);
                }
                else if (Creature* npc = who->ToCreature())
                {
                    switch (npc->GetEntry())
                    {
                    case 43432: 
                        m_messnerGUID = npc->GetGUID();
                        break;
                    case 43433:
                        m_jorgensenGUID = npc->GetGUID();
                        break;
                    case 43434:
                        m_krakauerGUID = npc->GetGUID();
                        break;
                    case 43435:
                        m_danforthGUID = npc->GetGUID();
                        break;
                    case 43457:
                        m_keeshanGUID = npc->GetGUID();
                        break;
                    }
                }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            VehicleAI::UpdateAI(diff);
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_ANIMATION_START:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        if (Creature* keeshan = sObjectAccessor->GetCreature(*me, m_keeshanGUID))
                            keeshan->AI()->Talk(0, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_01, 1000);
                    break;
                }
                case EVENT_TALK_PART_01:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        if (Creature* krakauer = sObjectAccessor->GetCreature(*me, m_krakauerGUID))
                            krakauer->AI()->Talk(0, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_02, 1000);
                    break;
                }
                case EVENT_TALK_PART_02:
                {
                    if (Creature* messner = sObjectAccessor->GetCreature(*me, m_messnerGUID))
                        if (Vehicle* boat = me->GetVehicleKit())
                            if (const VehicleSeatEntry* seat = boat->GetSeatForPassenger(messner))
                            {
                                Position pos = messner->GetTransportPosition();
                                pos.m_orientation = M_PI;

                                Movement::MoveSplineInit init(messner);
                                init.DisableTransportPathTransformations();
                                init.MoveTo(pos.m_positionX, pos.m_positionY, pos.m_positionZ, false, true);
                                init.SetFacing(pos.m_orientation);
                                init.SetTransportEnter();
                                init.Launch();

                                messner->CastSpell(messner, SPELL_MESSNER_BOAT_ENGINE, true);
                            }
                    me->SetSpeed(MOVE_WALK, 3.5f, true);
                    m_events.ScheduleEvent(EVENT_TALK_PART_03, 500);
                    break;
                }
                case EVENT_TALK_PART_03:
                {
                    me->GetMotionMaster()->MovePath(43450, false);
                    break;
                }
                case EVENT_TALK_PART_04:
                {
                    if (Vehicle* boat = me->GetVehicleKit())
                        boat->RemoveAllPassengers();
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new vehicle_keeshans_riverboat_43450AI(creature);
    }
};

// 43458
class npc_john_j_keeshan_43458 : public CreatureScript
{
public:
    npc_john_j_keeshan_43458() : CreatureScript("npc_john_j_keeshan_43458") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)  override
    {
        Creature* npc = creature->FindNearestCreature(NPC_JORGENSEN_43546, 100.0f);

        switch (quest->GetQuestId())
        {
        case QUEST_PRISONERS_OF_WAR:
        {
            if (!npc)
                player->CastSpell(player, SPELL_SUMMON_JORGENSEN_43546_81477);
            player->CastSpell(player, 81462, true);
            break;
        }
        case QUEST_TO_WIN_A_WAR_YOU_GOTTA_BECOME_WAR:
        {
            if (!npc)
                player->CastSpell(player, SPELL_SUMMON_JORGENSEN_43546_81477);
            player->CastSpell(player, 81462, true);
            break;
        }
        }

        return false;
    }

    bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* quest, uint32 /*opt*/)  override
    { 
        switch (quest->GetQuestId())
        {
        case QUEST_PRISONERS_OF_WAR:
        {
            if (player->HasAura(82580))
                player->CastSpell(player, 82591, true);
            player->RemoveAurasDueToSpell(82580);
            player->DestroyItemCount(60384, 1, true);
            break;
        }
        case QUEST_TO_WIN_A_WAR_YOU_GOTTA_BECOME_WAR:
        {
            if (Creature* npc = player->FindNearestCreature(NPC_JORGENSEN_43546, 100.0f))
                npc->DespawnOrUnsummon();
            if (player->HasAura(82587))
                player->CastSpell(player, 82592, true);
            player->RemoveAura(82577);
            player->DestroyItemCount(60385, 1, true);
            break;
        }
        }

        player->RemoveAura(81457);
        player->RemoveAura(81519);
        player->RemoveAura(81462);
        player->RemoveAura(82580);
        player->RemoveAura(82587);

        return false; 
    }

    struct npc_john_j_keeshan_43458AI : public ScriptedAI
    {
        npc_john_j_keeshan_43458AI(Creature *c) : ScriptedAI(c) { }

        EventMap m_events;
        bool     m_animIsStarted;
        uint64   m_playerGUID;
        uint64   m_danforthGUID;
        uint64   m_krakauerGUID;
        uint64   m_jorgensenGUID;
        uint64   m_messnerGUID;

        void Reset() override
        {
            m_playerGUID = 0;
            m_danforthGUID = 0;
            m_krakauerGUID = 0;
            m_jorgensenGUID = 0;
            m_messnerGUID = 0;
            m_animIsStarted = false;
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (Player* player = who->ToPlayer())
                if (player->HasAura(SPELL_DETECT_QUEST_INVIS_10) && !m_animIsStarted && me->GetDistance2d(player) < 10.0f)
                    if (player->GetQuestStatus(QUEST_THEY_DREW_FIRST_BLOOD) == QUEST_STATUS_INCOMPLETE)
                    {
                        m_playerGUID = player->GetGUID();
                        m_animIsStarted = true;
                        m_events.RescheduleEvent(EVENT_TALK_PART_00, 500);
                        if (!m_danforthGUID)
                            if (Creature* npc = me->FindNearestCreature(NPN_DANFORTH_43462, 15.0f))
                                m_danforthGUID = npc->GetGUID();
                        if (!m_krakauerGUID)
                            if (Creature* npc = me->FindNearestCreature(NPC_KRAKAUER_43461, 15.0f))
                                m_krakauerGUID = npc->GetGUID();
                        if (!m_jorgensenGUID)
                            if (Creature* npc = me->FindNearestCreature(NPC_JORGENSEN_43460, 15.0f))
                                m_jorgensenGUID = npc->GetGUID();
                        if (!m_messnerGUID)
                            if (Creature* npc = me->FindNearestCreature(NPC_MESSNER_43459, 15.0f))
                                m_messnerGUID = npc->GetGUID();
                    }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_TALK_PART_00:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(0, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_01, 5000);
                    break;
                }
                case EVENT_TALK_PART_01:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        if (Creature* danforth = sObjectAccessor->GetCreature(*me, m_danforthGUID))
                            danforth->AI()->Talk(0, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_02, 5000);
                    break;
                }
                case EVENT_TALK_PART_02:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(1, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_03, 5000);
                    break;
                }
                case EVENT_TALK_PART_03:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        if (Creature* krakauer = sObjectAccessor->GetCreature(*me, m_krakauerGUID))
                            krakauer->AI()->Talk(0, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_04, 5000);
                    break;
                }
                case EVENT_TALK_PART_04:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        if (Creature* krakauer = sObjectAccessor->GetCreature(*me, m_krakauerGUID))
                            krakauer->AI()->Talk(1, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_05, 5000);
                    break;
                }
                case EVENT_TALK_PART_05:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(2, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_06, 5000);
                    break;
                }
                case EVENT_TALK_PART_06:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        if (Creature* jorgensen = sObjectAccessor->GetCreature(*me, m_jorgensenGUID))
                            jorgensen->AI()->Talk(0, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_07, 5000);
                    break;
                }
                case EVENT_TALK_PART_07:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(3, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_08, 5000);
                    break;
                }
                case EVENT_TALK_PART_08:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        if (Creature* messner = sObjectAccessor->GetCreature(*me, m_messnerGUID))
                            messner->AI()->Talk(0, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_09, 5000);
                    break;
                }
                case EVENT_TALK_PART_09:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(4, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_10, 5000);
                    break;
                }
                case EVENT_TALK_PART_10:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(5, player);

                    m_events.ScheduleEvent(EVENT_TALK_PART_11, 5000);
                    break;
                }
                case EVENT_TALK_PART_11:
                {
                    m_playerGUID = 0;
                    m_animIsStarted = false;
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_john_j_keeshan_43458AI(creature);
    }
};

// 43546
class npc_jorgensen_43546 : public CreatureScript
{
public:
    npc_jorgensen_43546() : CreatureScript("npc_jorgensen_43546") { }

    struct npc_jorgensen_43546AI : public ScriptedAI
    {
        npc_jorgensen_43546AI(Creature *c) : ScriptedAI(c) { Initialize(); }

        bool ShownActive;
        bool ShownTip1;
        bool ShownTip2;
        bool ShownTip3;
        uint32 CoolDownTimer;

        void Initialize()
        {
            ShownActive = false;
            ShownTip1 = false;
            ShownTip2 = false;
            ShownTip3 = false;
            CoolDownTimer = 0;
        }

        void Reset() override
        {
            me->AddAura(SPELL_SEAL_OF_RIGHTEOUSNESS_81454, me);
            me->AddAura(SPELL_CONCENTRATION_AURA_81455, me);
            me->SetReactState(REACT_DEFENSIVE);
        }

        void AttackStart(Unit* target) override
        {
            if (target->HasAura(SPELL_CHLOROFORM))
                return;

            me->Attack(target, true);
            me->GetMotionMaster()->MoveChase(target);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_jorgensen_43546AI(creature);
    }
};

// 43594
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

            if (player->GetQuestStatus(QUEST_PRISONERS_OF_WAR) != QUEST_STATUS_INCOMPLETE && player->GetQuestStatus(QUEST_TO_WIN_A_WAR_YOU_GOTTA_BECOME_WAR) != QUEST_STATUS_INCOMPLETE)
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
                player->CastSpell(player, SPELL_SUMMON_JORGENSEN_43546_81477);
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

// 440
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

// 485
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

// 7013
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

// 43533
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

// 43535
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

// 204441  204442  204435
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

// 82585
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
    SPELL_EJECT_PASSENGER_1 = 80743,
    SAY_DAN_WHERE = 0,
    SAY_JOHN_TROTE = 2,
    SAY_DAN_TROTE = 1,
    SAY_SERVICE = 0, 
};

// 43611
class npc_john_j_keeshan_43611 : public CreatureScript
{
public:
    npc_john_j_keeshan_43611() : CreatureScript("npc_john_j_keeshan_43611") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)  override
    {
        player->RemoveAura(SPELL_DETECT_QUEST_INVIS_10);
        player->RemoveAura(SPELL_DETECT_QUEST_INVIS_11);
        player->RemoveAura(SPELL_DETECT_QUEST_INVIS_12);
        player->RemoveAura(SPELL_SUMMON_JORGENSEN_43546_81477);
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
            m_player = nullptr;
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

// 397
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

// 43618
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

// 43733
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

// 43734
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

// 43812
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

// 43826
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

// 43827
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

// 43828
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

// 43829
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
    new player_zone_redridge_mountains();
    new npc_magistrate_solomon_344();
    new npc_marshal_marris();
    new npc_dumpy_43249();
    new npc_big_earl_43248();
    new npc_redrige_citizen_43247();
    new at_lakeshire_graveyard();
    new npc_canyon_ettin_43094();
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

