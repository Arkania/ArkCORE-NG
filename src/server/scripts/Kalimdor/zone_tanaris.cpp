/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

/* ScriptData
SDName: Tanaris
SD%Complete: 80
SDComment: Quest support: 648, 10277, 10279(Special flight path).
SDCategory: Tanaris
EndScriptData */

/* ContentData
npc_custodian_of_time
npc_steward_of_time
npc_OOX17
EndContentData */

#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "ScriptedFollowerAI.h"
#include "Vehicle.h"
#include "WorldSession.h"

// 9453
class npc_aquementas_9453 : public CreatureScript
{
public:
    npc_aquementas_9453() : CreatureScript("npc_aquementas_9453") { }

    enum Aquementas
    {
        AGGRO_YELL_AQUE = 0,

        SPELL_AQUA_JET = 13586,
        SPELL_FROST_SHOCK = 15089
    };

    struct npc_aquementas_9453AI : public ScriptedAI
    {
        npc_aquementas_9453AI(Creature* creature) : ScriptedAI(creature) { }

        uint32 SendItemTimer;
        uint32 SwitchFactionTimer;
        bool isFriendly;

        uint32 FrostShockTimer;
        uint32 AquaJetTimer;

        void Reset() override
        {
            SendItemTimer = 0;
            SwitchFactionTimer = 10000;
            me->setFaction(35);
            isFriendly = true;

            AquaJetTimer = 5000;
            FrostShockTimer = 1000;
        }

        void SendItem(Unit* receiver)
        {
            Player* player = receiver->ToPlayer();

            if (player && player->HasItemCount(11169, 1, false) &&
                player->HasItemCount(11172, 11, false) &&
                player->HasItemCount(11173, 1, false) &&
                !player->HasItemCount(11522, 1, true))
            {
                ItemPosCountVec dest;
                uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 11522, 1, NULL);
                if (msg == EQUIP_ERR_OK)
                    player->StoreNewItem(dest, 11522, 1, true);
            }
        }

        void EnterCombat(Unit* who)
        {
            Talk(AGGRO_YELL_AQUE, who);
        }

        void UpdateAI(uint32 diff) override
        {
            if (isFriendly)
            {
                if (SwitchFactionTimer <= diff)
                {
                    me->setFaction(91);
                    isFriendly = false;
                } else SwitchFactionTimer -= diff;
            }

            if (!UpdateVictim())
                return;

            if (!isFriendly)
            {
                if (SendItemTimer <= diff)
                {
                    if (me->GetVictim() && me->EnsureVictim()->GetTypeId() == TYPEID_PLAYER)
                        SendItem(me->GetVictim());
                    SendItemTimer = 5000;
                } else SendItemTimer -= diff;
            }

            if (FrostShockTimer <= diff)
            {
                DoCastVictim(SPELL_FROST_SHOCK);
                FrostShockTimer = 15000;
            } else FrostShockTimer -= diff;

            if (AquaJetTimer <= diff)
            {
                DoCast(me, SPELL_AQUA_JET);
                AquaJetTimer = 15000;
            } else AquaJetTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_aquementas_9453AI(creature);
    }
};

// 19950
class npc_custodian_of_time_19950 : public CreatureScript
{
public:
    npc_custodian_of_time_19950() : CreatureScript("npc_custodian_of_time_19950") { }

    enum CustodianOfTime
    {
        WHISPER_CUSTODIAN_1 = 0,
        WHISPER_CUSTODIAN_2 = 1,
        WHISPER_CUSTODIAN_3 = 2,
        WHISPER_CUSTODIAN_4 = 3,
        WHISPER_CUSTODIAN_5 = 4,
        WHISPER_CUSTODIAN_6 = 5,
        WHISPER_CUSTODIAN_7 = 6,
        WHISPER_CUSTODIAN_8 = 7,
        WHISPER_CUSTODIAN_9 = 8,
        WHISPER_CUSTODIAN_10 = 9,
        WHISPER_CUSTODIAN_11 = 10,
        WHISPER_CUSTODIAN_12 = 11,
        WHISPER_CUSTODIAN_13 = 12,
        WHISPER_CUSTODIAN_14 = 13
    };

    struct npc_custodian_of_time_19950AI : public npc_escortAI
    {
        npc_custodian_of_time_19950AI(Creature* creature) : npc_escortAI(creature) { }

        void WaypointReached(uint32 waypointId)
        {
            if (Player* player = GetPlayerForEscort())
            {
                switch (waypointId)
                {
                    case 0:
                        Talk(WHISPER_CUSTODIAN_1, player);
                        break;
                    case 1:
                        Talk(WHISPER_CUSTODIAN_2, player);
                        break;
                    case 2:
                        Talk(WHISPER_CUSTODIAN_3, player);
                        break;
                    case 3:
                        Talk(WHISPER_CUSTODIAN_4, player);
                        break;
                    case 5:
                        Talk(WHISPER_CUSTODIAN_5, player);
                        break;
                    case 6:
                        Talk(WHISPER_CUSTODIAN_6, player);
                        break;
                    case 7:
                        Talk(WHISPER_CUSTODIAN_7, player);
                        break;
                    case 8:
                        Talk(WHISPER_CUSTODIAN_8, player);
                        break;
                    case 9:
                        Talk(WHISPER_CUSTODIAN_9, player);
                        break;
                    case 10:
                        Talk(WHISPER_CUSTODIAN_4, player);
                        break;
                    case 13:
                        Talk(WHISPER_CUSTODIAN_10, player);
                        break;
                    case 14:
                        Talk(WHISPER_CUSTODIAN_4, player);
                        break;
                    case 16:
                        Talk(WHISPER_CUSTODIAN_11, player);
                        break;
                    case 17:
                        Talk(WHISPER_CUSTODIAN_12, player);
                        break;
                    case 18:
                        Talk(WHISPER_CUSTODIAN_4, player);
                        break;
                    case 22:
                        Talk(WHISPER_CUSTODIAN_13, player);
                        break;
                    case 23:
                        Talk(WHISPER_CUSTODIAN_4, player);
                        break;
                    case 24:
                        Talk(WHISPER_CUSTODIAN_14, player);
                        DoCast(player, 34883);
                        // below here is temporary workaround, to be removed when spell works properly
                        player->AreaExploredOrEventHappens(10277);
                        break;
                }
            }
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (HasEscortState(STATE_ESCORT_ESCORTING))
                return;

            if (Player* player = who->ToPlayer())
            {
                if (who->HasAura(34877) && player->GetQuestStatus(10277) == QUEST_STATUS_INCOMPLETE)
                {
                    float Radius = 10.0f;
                    if (me->IsWithinDistInMap(who, Radius))
                    {
                        Start(false, false, who->GetGUID());
                    }
                }
            }
        }

        void EnterCombat(Unit* /*who*/) override { }
        void Reset() override { }

        void UpdateAI(uint32 diff) override
        {
            npc_escortAI::UpdateAI(diff);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_custodian_of_time_19950AI(creature);
    }
};

// 20142
class npc_steward_of_time_20142 : public CreatureScript
{
public:
    npc_steward_of_time_20142() : CreatureScript("npc_steward_of_time_20142") { }

    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == 10279)                      //Quest: To The Master's Lair
            player->CastSpell(player, 34891, true);               //(Flight through Caverns)

        return false;
    }

    bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF + 1)
            player->CastSpell(player, 34891, true);               //(Flight through Caverns)

        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(10279) == QUEST_STATUS_INCOMPLETE || player->GetQuestRewardStatus(10279))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Please take me to the master's lair.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->SEND_GOSSIP_MENU(9978, creature->GetGUID());
        }
        else
            player->SEND_GOSSIP_MENU(9977, creature->GetGUID());

        return true;
    }
};

// 7784
class npc_OOX17_7784 : public CreatureScript
{
public:
    npc_OOX17_7784() : CreatureScript("npc_OOX17_7784") { }

    enum Npc00X17
    {
        SAY_OOX_START = 0,
        SAY_OOX_AGGRO = 1,
        SAY_OOX_AMBUSH = 2,
        SAY_OOX17_AMBUSH_REPLY = 0,
        SAY_OOX_END = 3,

        Q_OOX17 = 648,
        SPAWN_FIRST = 7803,
        SPAWN_SECOND_1 = 5617,
        SPAWN_SECOND_2 = 7805
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == Q_OOX17)
        {
            creature->setFaction(113);
            creature->SetFullHealth();
            creature->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
            creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            creature->AI()->Talk(SAY_OOX_START);

            if (npc_escortAI* pEscortAI = CAST_AI(npc_OOX17_7784::npc_OOX17_7784AI, creature->AI()))
                pEscortAI->Start(true, false, player->GetGUID());
        }
        return true;
    }

    struct npc_OOX17_7784AI : public npc_escortAI
    {
        npc_OOX17_7784AI(Creature* creature) : npc_escortAI(creature) { }

        void WaypointReached(uint32 waypointId)
        {
            if (Player* player = GetPlayerForEscort())
            {
                switch (waypointId)
                {
                    case 23:
                        me->SummonCreature(SPAWN_FIRST, -8350.96f, -4445.79f, 10.10f, 6.20f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                        me->SummonCreature(SPAWN_FIRST, -8355.96f, -4447.79f, 10.10f, 6.27f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                        me->SummonCreature(SPAWN_FIRST, -8353.96f, -4442.79f, 10.10f, 6.08f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                        Talk(SAY_OOX_AMBUSH);
                        break;
                    case 56:
                        me->SummonCreature(SPAWN_SECOND_1, -7510.07f, -4795.50f, 9.35f, 6.06f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                        me->SummonCreature(SPAWN_SECOND_2, -7515.07f, -4797.50f, 9.35f, 6.22f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                        me->SummonCreature(SPAWN_SECOND_2, -7518.07f, -4792.50f, 9.35f, 6.22f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                        Talk(SAY_OOX_AMBUSH);
                        if (Creature* scoff = me->FindNearestCreature(SPAWN_SECOND_2, 30))
                            scoff->AI()->Talk(SAY_OOX17_AMBUSH_REPLY);
                        break;
                    case 86:
                        Talk(SAY_OOX_END);
                        player->GroupEventHappens(Q_OOX17, me);
                        break;
                }
            }
        }

        void Reset() override { }

        void EnterCombat(Unit* /*who*/) override
        {
            Talk(SAY_OOX_AGGRO);
        }

        void JustSummoned(Creature* summoned) override
        {
            summoned->AI()->AttackStart(me);
        }
    };
    
    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_OOX17_7784AI(creature);
    }
};

// 5955
class npc_tooga_5955 : public CreatureScript
{
public:
    npc_tooga_5955() : CreatureScript("npc_tooga_5955") { }

    enum Tooga
    {
        SAY_TOOG_WORRIED = 0,
        SAY_TOOG_POST_1 = 1,
        SAY_TORT_POST_2 = 0,
        SAY_TOOG_POST_3 = 2,
        SAY_TORT_POST_4 = 1,
        SAY_TOOG_POST_5 = 3,
        SAY_TORT_POST_6 = 2,

        QUEST_TOOGA = 1560,
        NPC_TORTA = 6015,

        POINT_ID_TO_WATER = 1,
        FACTION_TOOG_ESCORTEE = 113
    };

    bool OnQuestAccept(Player* player, Creature* creature, const Quest* quest)
    {
        if (quest->GetQuestId() == QUEST_TOOGA)
        {
            if (npc_tooga_5955AI* pToogaAI = CAST_AI(npc_tooga_5955::npc_tooga_5955AI, creature->AI()))
                pToogaAI->StartFollow(player, FACTION_TOOG_ESCORTEE, quest);
        }

        return true;
    }
    
    struct npc_tooga_5955AI : public FollowerAI
    {
        npc_tooga_5955AI(Creature* creature) : FollowerAI(creature) { }

        uint32 CheckSpeechTimer;
        uint32 PostEventTimer;
        uint32 PhasePostEvent;

        uint64 TortaGUID;

        void Reset() override
        {
            CheckSpeechTimer = 2500;
            PostEventTimer = 1000;
            PhasePostEvent = 0;

            TortaGUID = 0;
        }

        void MoveInLineOfSight(Unit* who)
        {
            FollowerAI::MoveInLineOfSight(who);

            if (!me->GetVictim() && !HasFollowState(STATE_FOLLOW_COMPLETE | STATE_FOLLOW_POSTEVENT) && who->GetEntry() == NPC_TORTA)
            {
                if (me->IsWithinDistInMap(who, INTERACTION_DISTANCE))
                {
                    Player* player = GetLeaderForFollower();
                    if (player && player->GetQuestStatus(QUEST_TOOGA) == QUEST_STATUS_INCOMPLETE)
                        player->GroupEventHappens(QUEST_TOOGA, me);

                    TortaGUID = who->GetGUID();
                    SetFollowComplete(true);
                }
            }
        }

        void MovementInform(uint32 MotionType, uint32 PointId)
        {
            FollowerAI::MovementInform(MotionType, PointId);

            if (MotionType != POINT_MOTION_TYPE)
                return;

            if (PointId == POINT_ID_TO_WATER)
                SetFollowComplete();
        }

        void UpdateFollowerAI(uint32 Diff)
        {
            if (!UpdateVictim())
            {
                //we are doing the post-event, or...
                if (HasFollowState(STATE_FOLLOW_POSTEVENT))
                {
                    if (PostEventTimer <= Diff)
                    {
                        PostEventTimer = 5000;

                        Creature* torta = ObjectAccessor::GetCreature(*me, TortaGUID);
                        if (!torta || !torta->IsAlive())
                        {
                            //something happened, so just complete
                            SetFollowComplete();
                            return;
                        }

                        switch (PhasePostEvent)
                        {
                            case 1:
                                Talk(SAY_TOOG_POST_1);
                                break;
                            case 2:
                                torta->AI()->Talk(SAY_TORT_POST_2);
                                break;
                            case 3:
                                Talk(SAY_TOOG_POST_3);
                                break;
                            case 4:
                                torta->AI()->Talk(SAY_TORT_POST_4);
                                break;
                            case 5:
                                Talk(SAY_TOOG_POST_5);
                                break;
                            case 6:
                                torta->AI()->Talk(SAY_TORT_POST_6);
                                me->GetMotionMaster()->MovePoint(POINT_ID_TO_WATER, -7032.664551f, -4906.199219f, -1.606446f);
                                break;
                        }

                        ++PhasePostEvent;
                    }
                    else
                        PostEventTimer -= Diff;
                }
                //...we are doing regular speech check
                else if (HasFollowState(STATE_FOLLOW_INPROGRESS))
                {
                    if (CheckSpeechTimer <= Diff)
                    {
                        CheckSpeechTimer = 5000;

                        if (urand(0, 9) > 8)
                            Talk(SAY_TOOG_WORRIED);
                    }
                    else
                        CheckSpeechTimer -= Diff;
                }

                return;
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_tooga_5955AI(creature);
    }
};

// 46516
class npc_uldum_caravan_harness_46516 : public CreatureScript
{
public:
    npc_uldum_caravan_harness_46516() : CreatureScript("npc_uldum_caravan_harness_46516") { }

    enum eNpc
    {
        EVENT_CHECK_PASSENGER = 1,
        NPC_KODO = 46514,
        NPC_KURZEL = 46529,
        NPC_HARKOR = 46530,
        NPC_TURGORE = 46525,
        NPC_TANZAR = 46528,
        DRIVER_LEFT = 1,
        DRIVER_RIGHT = 0,
        DRIVER_KODO = 4,
        PASSENGER_MID = 2,
        PASSENGER_LAST = 3,
    };

    struct npc_uldum_caravan_harness_46516AI : public ScriptedAI
    {
        npc_uldum_caravan_harness_46516AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64 kodoGUID;
        uint64 kurzelGUID;
        uint64 harkorGUID;
        uint64 turgoreGUID;
        uint64 tanzarGUID;

        void Reset() override
        {
            kodoGUID = NULL;
            kurzelGUID = NULL;
            harkorGUID = NULL;
            turgoreGUID = NULL;
            tanzarGUID = NULL;
            m_events.ScheduleEvent(EVENT_CHECK_PASSENGER, 1000);
        }

        void JustSummoned(Creature* summon) override
        { 
            summon->AddAura(46598, summon);
            summon->AddAura(46598, me);
            summon->SetDisableGravity(true);
            if (Vehicle* caravan = me->GetVehicleKit())
            {
                switch (summon->GetEntry())
                {
                case NPC_KODO:
                    kodoGUID = summon->GetGUID();
                    summon->EnterVehicle(me, DRIVER_KODO);
                    break;
                case NPC_TURGORE:
                    turgoreGUID = summon->GetGUID();
                    summon->EnterVehicle(me, DRIVER_RIGHT);
                    break;
                case NPC_TANZAR:
                    tanzarGUID = summon->GetGUID();
                    summon->EnterVehicle(me, PASSENGER_LAST);
                    break;
                case NPC_KURZEL:
                    kurzelGUID = summon->GetGUID();
                    summon->EnterVehicle(me, PASSENGER_MID);
                    break;
                case NPC_HARKOR:
                    harkorGUID = summon->GetGUID();
                    summon->EnterVehicle(me, DRIVER_LEFT);
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
                    case EVENT_CHECK_PASSENGER:
                    {
                        if (Vehicle* caravan = me->GetVehicleKit())
                        {
                            if (!kurzelGUID)
                                me->SummonCreature(NPC_KURZEL, me->GetNearPosition(5.0f, 0.0f), TEMPSUMMON_MANUAL_DESPAWN);
                            else if (!turgoreGUID)
                                me->SummonCreature(NPC_TURGORE, me->GetNearPosition(5.0f, 0.0f), TEMPSUMMON_MANUAL_DESPAWN);
                            else if (!tanzarGUID)
                                me->SummonCreature(NPC_TANZAR, me->GetNearPosition(5.0f, 0.0f), TEMPSUMMON_MANUAL_DESPAWN);
                            else if (!kodoGUID)
                                me->SummonCreature(NPC_KODO, me->GetNearPosition(5.0f, 0.0f), TEMPSUMMON_MANUAL_DESPAWN);
                            else if (!harkorGUID)
                            {
                                me->SummonCreature(NPC_HARKOR, me->GetNearPosition(5.0f, 0.0f), TEMPSUMMON_MANUAL_DESPAWN);
                                return;
                            }
                        }
                        m_events.ScheduleEvent(EVENT_CHECK_PASSENGER, 50);

                        break;
                    }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_uldum_caravan_harness_46516AI(creature);
    }
};

// 44833
class npc_adarrah_44833 : public CreatureScript
{
public:
    npc_adarrah_44833() : CreatureScript("npc_adarrah_44833") { }

    enum eNpc
    {
        EVENT_CHECK_PASSENGER = 1,       
    };

    struct npc_adarrah_44833AI : public ScriptedAI
    {
        npc_adarrah_44833AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset() override
        {            
            m_events.Reset();
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case 0:               
                        break;                
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_adarrah_44833AI(creature);
    }
};

// 46517
class npc_lady_humps_46517 : public CreatureScript
{
public:
    npc_lady_humps_46517() : CreatureScript("npc_lady_humps_46517") { }

    enum eNpc
    {
        EVENT_CHECK_PASSENGER = 1,
    };

    struct npc_lady_humps_46517AI : public ScriptedAI
    {
        npc_lady_humps_46517AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset() override
        {
            m_events.Reset();
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case 0:
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_lady_humps_46517AI(creature);
    }
};


void AddSC_tanaris()
{
    new npc_aquementas_9453();
    new npc_custodian_of_time_19950();
    new npc_steward_of_time_20142();
    new npc_OOX17_7784();
    new npc_tooga_5955();
    new npc_uldum_caravan_harness_46516();
    new npc_adarrah_44833();
    new npc_lady_humps_46517();
}
