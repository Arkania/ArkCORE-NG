/*
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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "GameObjectAI.h"
#include "GameObject.h"
#include "Player.h"
#include "Vehicle.h"
#include "VehicleDefines.h"
#include "Transport.h"
#include "TransportMgr.h"

// 34634
class npc_gorgal_angerscar_34634 : public CreatureScript
{
public:
    npc_gorgal_angerscar_34634() : CreatureScript("npc_gorgal_angerscar_34634") { }

    enum eGorgal
    {
        QUEST_KING_OF_CENTAUR_MOUNTAIN = 13995,
        NPC_GORGAL = 34634,
        NPC_KURAK = 34635,
        NPC_KOLKAR = 3275,
        EVENT_START_ANIM = 1,
        EVENT_CHECK_KOLKAR,
        EVENT_CHECK_KURAK,
        EVENT_TALK_FINISH,
        EVENT_RESET,
        SPELL_RAISE_BANNER = 65804,
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) 
    { 
        if (quest->GetQuestId() == QUEST_KING_OF_CENTAUR_MOUNTAIN)
        {
            creature->AI()->DoAction(1);
            CAST_AI(npc_gorgal_angerscar_34634AI, creature->GetAI())->m_playerGUID = player->GetGUID();
        }

        return false; 
    }

    struct npc_gorgal_angerscar_34634AI : public ScriptedAI
    {
        npc_gorgal_angerscar_34634AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64 m_kolkarGUID;
        uint64 m_kurakGUID;
        uint64 m_playerGUID;
        uint32 m_killCount;
        bool m_isAnimStarted;

        void Initialize()
        {
            m_isAnimStarted = false;           
        }

        void Reset() override
        {
            if (!m_isAnimStarted)
            {
                m_events.Reset();
                m_killCount = 0;
                m_kolkarGUID = 0;
                m_kurakGUID = 0;
                m_playerGUID = 0;
            }
        }

        void MovementInform(uint32 type, uint32 id) 
        { 
            if (type == 2 && id == 7)
            {
                me->CastSpell(me, SPELL_RAISE_BANNER);
                m_events.ScheduleEvent(EVENT_CHECK_KOLKAR, 1000);
            }
        }

        void DamageTaken(Unit* attacker, uint32& damage) 
        { 
            if (attacker->GetEntry() == NPC_KOLKAR || attacker->GetEntry() == NPC_KURAK)
                damage = 0;
        }

        void JustDied(Unit* /*killer*/) 
        { 
            m_isAnimStarted = false;
            me->DespawnOrUnsummon();
        }

        void DoAction(int32 param) 
        { 
            if (param == 1 && !m_isAnimStarted)
            {
                m_isAnimStarted = true;
                m_events.ScheduleEvent(EVENT_START_ANIM, 100);
                m_events.ScheduleEvent(EVENT_RESET, 300000);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_START_ANIM:
                        Talk(0);
                        me->GetMotionMaster()->MovePath(1389261, false);
                        break;
                    case EVENT_RESET:
                        m_isAnimStarted = false;
                        me->DespawnOrUnsummon();
                        break;
                    case EVENT_CHECK_KOLKAR:
                    {
                        Creature* kolkar = ObjectAccessor::GetCreature(*me, m_kolkarGUID);
                        if (!IsAlive(kolkar))
                        {
                            if (m_kolkarGUID)
                                m_killCount++;
                            if (m_killCount < 3)
                            {
                                if (kolkar = me->SummonCreature(NPC_KOLKAR, -1158.43f, -2954.45f, 93.689f, 2.61691f))
                                {
                                    if (m_killCount == 0)
                                        Talk(1);
                                    else
                                        Talk(2);
                                    m_kolkarGUID = kolkar->GetGUID();
                                    kolkar->GetMotionMaster()->MoveChase(me);
                                }
                            }
                            else
                            {
                                if (Creature* kurak = me->SummonCreature(NPC_KURAK, -1158.43f, -2954.45f, 93.689f, 2.61691f))
                                {
                                    Talk(3);
                                    m_kurakGUID = kurak->GetGUID();
                                    kurak->GetMotionMaster()->MoveChase(me);
                                    m_events.ScheduleEvent(EVENT_CHECK_KURAK, 1000);
                                    break;
                                }
                            }
                        }
                        m_events.ScheduleEvent(EVENT_CHECK_KOLKAR, 1000);
                        break;
                    }
                    case EVENT_CHECK_KURAK:
                    {
                        Creature* kurak = ObjectAccessor::GetCreature(*me, m_kurakGUID);
                        if (IsAlive(kurak))
                            m_events.ScheduleEvent(EVENT_CHECK_KURAK, 1000);
                        else
                        {
                            Talk(4);
                            if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                                player->KilledMonsterCredit(NPC_KURAK);
                            m_events.ScheduleEvent(EVENT_TALK_FINISH, 5000);
                        }
                        break;
                    }
                    case EVENT_TALK_FINISH:
                    {
                        Talk(6);
                        me->DespawnOrUnsummon(5000);
                        m_isAnimStarted = false;
                        break;
                    }
                    default:
                        break;
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        bool IsAlive(Creature* npc)
        {
            if (!npc)
                return false;
            return npc->IsAlive();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_gorgal_angerscar_34634AI(creature);
    }
};

// 34638
class npc_shoe_34638 : public CreatureScript
{
public:
    npc_shoe_34638() : CreatureScript("npc_shoe_34638") { }

    struct npc_shoe_34638AI : public ScriptedAI
    {
        npc_shoe_34638AI(Creature* creature) : ScriptedAI(creature) { }

        uint32 m_phase;
        uint32 m_timer;
        uint32 m_playerPresentCounter;

        void Reset() override
        {
            m_phase = 1;
            m_timer = 1000;
            m_playerPresentCounter = 0;
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_timer < diff)
            {
                m_timer = 1000;
                if (m_phase) DoWork();
            }
            else
                m_timer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

        void DoWork()
        {
            Creature* gorgal = me->FindNearestCreature(34634, 15.0f);
            if (!gorgal)
            {
                m_playerPresentCounter = 0;
                return;
            }

            switch (m_phase)
            {
            case 1:                
                if (Player* player = me->FindNearestPlayer(25.0f))
                {
                    ++m_playerPresentCounter;
                    if (m_playerPresentCounter >= 30)
                        m_phase = 2;
                }
                else
                    m_playerPresentCounter = 0;

                break;
            case 2:
                Talk(0);
                m_timer = 5000;
                m_phase = 3;
                break;
            case 3:
                gorgal->AI()->Talk(5);
                m_timer = 5000;
                m_phase = 4;
                break;
            case 4:
                Talk(1);
                m_playerPresentCounter = 0;
                m_timer = 120000;
                m_phase = 0;
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_shoe_34638AI(creature);
    }
};

// 6906
class go_red_raptor_nest_6906 : public GameObjectScript
{
public:
    go_red_raptor_nest_6906() : GameObjectScript("go_red_raptor_nest_6906") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/) 
    { 
        if (player->GetQuestStatus(905) == QUEST_STATUS_INCOMPLETE)
        {
            player->KilledMonsterCredit(34964);
            return true;
        }

        return false; 
    }
};

// 6907
class go_blue_raptor_nest_6907 : public GameObjectScript
{
public:
    go_blue_raptor_nest_6907() : GameObjectScript("go_blue_raptor_nest_6907") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/)
    {
        if (player->GetQuestStatus(905) == QUEST_STATUS_INCOMPLETE)
        {
            player->KilledMonsterCredit(34963);
            return true;
        }

        return false;
    }
};

// 6908
class go_yellow_raptor_nest_6908 : public GameObjectScript
{
public:
    go_yellow_raptor_nest_6908() : GameObjectScript("go_yellow_raptor_nest_6908") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/)
    {
        if (player->GetQuestStatus(905) == QUEST_STATUS_INCOMPLETE)
        {
            player->KilledMonsterCredit(34962);
            return true;
        }

        return false;
    }


};

// 34846
class npc_wyneth_34846 : public CreatureScript
{
public:
    npc_wyneth_34846() : CreatureScript("npc_wyneth_34846") { }

    struct npc_wyneth_34846AI : public ScriptedAI
    {
        npc_wyneth_34846AI(Creature* creature) : ScriptedAI(creature) { }

        void JustDied(Unit* killer) override
        { 
            if (Player* player = killer->ToPlayer())
                if (player->GetQuestStatus(851) == QUEST_STATUS_INCOMPLETE)
                {
                    Talk(0);
                    me->SummonCreature(3395, -1201.7f, -2763.1f, 95.97f, 1.73f);
                }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_wyneth_34846AI(creature);
    }
};

// 3395
class npc_verog_the_dervish_3395 : public CreatureScript
{
public:
    npc_verog_the_dervish_3395() : CreatureScript("npc_verog_the_dervish_3395") { }

    struct npc_verog_the_dervish_3395AI : public ScriptedAI
    {
        npc_verog_the_dervish_3395AI(Creature* creature) : ScriptedAI(creature) { }

        uint32 m_phase;
        uint32 m_timer;

        void Reset() override
        {
            m_phase = 1;
            m_timer = 1000;
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_timer < diff)
            {
                m_timer = 1000;
                if (m_phase) DoWork();
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
            case 1:
                Talk(0);
                m_timer = 5000;
                m_phase = 2;
                break;
            case 2:
                if (Player* player = me->FindNearestPlayer(50.0f))
                {
                    me->GetMotionMaster()->MoveChase(player, 2.0f);
                    me->Attack(player, true);
                    m_phase = 3;
                }
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_verog_the_dervish_3395AI(creature);
    }
};

// 34285
class npc_trapped_wolf_34285 : public CreatureScript
{
public:
    npc_trapped_wolf_34285() : CreatureScript("npc_trapped_wolf_34285") { }

    struct npc_trapped_wolf_34285AI : public ScriptedAI
    {
        npc_trapped_wolf_34285AI(Creature* creature) : ScriptedAI(creature) { }

        uint32 m_phase;

        void Reset() override
        {
            m_phase = 0;
            if (Creature* chain = me->FindNearestCreature(34287, 6.0f))
                chain->CastSpell(me, 65072);
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type == 2 && id == 2)
                me->DespawnOrUnsummon(100);
        }

        void DoAction(int32 param)
        {
            if (param == 1 && m_phase == 0)
            {
                m_phase = 1;
                me->RemoveAura(65072);
                me->GetMotionMaster()->MovePath(1165501, false);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_trapped_wolf_34285AI(creature);
    }
};

// 34287
class npc_chain_origin_34287 : public CreatureScript
{
public:
    npc_chain_origin_34287() : CreatureScript("npc_chain_origin_34287") { }

    struct npc_chain_origin_34287AI : public ScriptedAI
    {
        npc_chain_origin_34287AI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            if (Creature* wolf = me->FindNearestCreature(34285, 6.0f))
            {
                me->CastSpell(wolf, 65072);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_chain_origin_34287AI(creature);
    }
};

// 195001, 195003, 195004
class go_wolf_chains : public GameObjectScript
{
public:
    go_wolf_chains() : GameObjectScript("go_wolf_chains") { }

    struct go_wolf_chainsAI : public GameObjectAI
    {
        go_wolf_chainsAI(GameObject* go) : GameObjectAI(go) { }

        void OnStateChanged(uint32 state, Unit* unit) 
        { 
            if (unit)
                if (Player* player = unit->ToPlayer())
                    if (player->GetQuestStatus(13878) == QUEST_STATUS_INCOMPLETE)
                        if (Creature* wolf = go->FindNearestCreature(34285, 7.0f))
                        {
                            wolf->AI()->DoAction(1);
                            player->KilledMonsterCredit(34285);
                        }
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_wolf_chainsAI(go);
    }
};

/* ################################################# */

// 34487
class npc_razormane_raider_34487 : public CreatureScript
{
public:
    npc_razormane_raider_34487() : CreatureScript("npc_razormane_raider_34487") { }

    struct npc_razormane_raider_34487AI : public ScriptedAI
    {
        npc_razormane_raider_34487AI(Creature* creature) : ScriptedAI(creature) { }

        uint32 m_phase;
        uint32 m_timer;
        float m_target;
        bool m_isRiding;
        uint64 m_kodoPackGUID;

        void Reset() override
        {
            m_phase = 0;
            m_timer = 0;
            m_isRiding = false;
            m_kodoPackGUID = 0;
            me->SetUInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
        }

        void SetGUID(uint64 guid, int32 id = 0)
        {
            switch (id)
            {
            case 34432:
                m_kodoPackGUID = guid;
                if (Creature* kodo2 = ObjectAccessor::GetCreature(*me, m_kodoPackGUID))
                {
                    m_target = RAND(frand(4.0f, 5.2f), frand(0.9f, 2.1f));
                    me->SetSpeed(MOVE_WALK, 4.1f);
                    me->SetSpeed(MOVE_RUN, 4.2f);
                    me->SetWalk(false);
                    me->GetMotionMaster()->MoveFollow(kodo2, frand(0.1f, 1.5f), m_target);
                    m_phase = 1;
                    m_timer = 100;
                }
                break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_timer < diff)
            {
                m_timer = 1000;
                if (m_phase) DoWork();
            }
            else
                m_timer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

        void DoWork()
        {
            Creature* kodo2 = ObjectAccessor::GetCreature(*me, m_kodoPackGUID);
            if (!kodo2)
            {
                me->DespawnOrUnsummon(100);
                return;
            }

            m_phase++;

            if (m_phase > 7 && !m_isRiding)
            {
                me->CastSpell(kodo2, 63316);
                m_isRiding = true;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_razormane_raider_34487AI(creature);
    }
};

// 34258
class npc_halga_bloodeye_34258 : public CreatureScript
{
public:
    npc_halga_bloodeye_34258() : CreatureScript("npc_halga_bloodeye_34258") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 /*action*/) 
    { 
        Creature* kodo = creature->FindNearestCreature(34430, 200.0f);
        if (player->GetQuestStatus(13949) == QUEST_STATUS_INCOMPLETE)
            if (!kodo)
            {
                creature->CastSpell(player, 65486, true);
                creature->CastSpell(player, 61286);
                creature->GetAI()->SetGUID(player->GetGUID(), 99999);
                return true;
            }
        return false;	
    }

    struct npc_halga_bloodeye_34258AI : public ScriptedAI
    {
        npc_halga_bloodeye_34258AI(Creature* creature) : ScriptedAI(creature) { }

        uint32 m_phase;
        uint32 m_timer;
        uint64 m_playerGUID;

        void Reset() override
        {
            m_phase = 0;
            m_timer = 0;
            m_playerGUID = 0;
        }

        void JustSummoned(Creature* summon) override
        {
            switch (summon->GetEntry())
            {
            case 34430:
                summon->AI()->SetGUID(me->GetGUID(), me->GetEntry());
                summon->AI()->SetGUID(m_playerGUID, 99999);
                break;
            }
        }

        void SetGUID(uint64 guid, int32 id = 0)
        {
            switch (id)
            {
                case 99999:
                    if (!m_playerGUID)
                        m_playerGUID = guid;
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_halga_bloodeye_34258AI(creature);
    }
};

// 34430
class npc_lead_caravan_kodo_34430 : public CreatureScript
{
public:
    npc_lead_caravan_kodo_34430() : CreatureScript("npc_lead_caravan_kodo_34430") { }

    struct npc_lead_caravan_kodo_34430AI : public ScriptedAI
    {
        npc_lead_caravan_kodo_34430AI(Creature* creature) : ScriptedAI(creature) { }

        uint32 m_phase;
        uint32 m_timer;
        bool m_IsArrived;
        uint64 m_halgaGUID;
        uint64 m_playerGUID;
        uint64 m_gunnerGUID;
        uint64 m_balgorGUID;
        uint64 m_kodoPackGUID;

        void Reset() override
        {
            m_phase = 1;
            m_timer = 1000;
            m_IsArrived = false;
            m_halgaGUID = 0;
            m_playerGUID = 0;
            m_gunnerGUID = 0;
            m_balgorGUID = 0;
            m_kodoPackGUID = 0;
            me->SetUInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == 8 && id == 21)
                me->CastSpell(me, 65494);
            else if (type == 8 && id == 22)
            {
                me->DespawnOrUnsummon(100);
                if (Creature* gunner = ObjectAccessor::GetCreature(*me, m_gunnerGUID))
                    gunner->DespawnOrUnsummon(100);
                if (Creature* balgor = ObjectAccessor::GetCreature(*me, m_balgorGUID))
                {
                    me->CastSpell(balgor, 65557);
                    balgor->DespawnOrUnsummon(100);
                }
            }
            else if (type == 2 && id == 2)
            {
                Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID);
                Creature* gunner = ObjectAccessor::GetCreature(*me, m_gunnerGUID);
                if (player && gunner)
                    gunner->AI()->Talk(0, player);
            }
            else if (type == 2 && id > 4 && id < 17)
                CreateAttack();
            else if (type == 2 && id == 19)
                TargetArrived();
        }

        void JustSummoned(Creature* summon) override
        { 
            switch (summon->GetEntry())
            {
                case 34431:
                    m_balgorGUID = summon->GetGUID();
                    summon->AI()->SetGUID(me->GetGUID(), me->GetEntry());
                    break;
                case 34432:
                    m_kodoPackGUID = summon->GetGUID();
                    summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                    break;
                case 34438:
                    m_gunnerGUID = summon->GetGUID();
                    summon->AI()->SetGUID(me->GetGUID(), me->GetEntry());
                    break;
                case 34487:
                    summon->AI()->SetGUID(m_kodoPackGUID, 34432);
                    break;
            }
        }

        void SetGUID(uint64 guid, int32 id = 0)
        {
            switch (id)
            {
                case 34258:
                    m_halgaGUID = guid;
                    break;
                case 99999:
                    if (!m_playerGUID)
                        m_playerGUID = guid;
                    break;
                default:
                    break;
            }
        }

        uint64 GetGUID(int32 id = 0) const
        {
            switch (id)
            {
                case 34431:
                    return m_balgorGUID;
                case 34432:
                    return m_kodoPackGUID;
                case 34438:
                    return m_gunnerGUID;
                default:
                    return 0;                
            }
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) 
        { 
            if (apply)
            {
                if (passenger->GetEntry() == 34438)
                {
                    Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID);
                    Creature* kodo2 = ObjectAccessor::GetCreature(*me, m_kodoPackGUID);
                    if (player && kodo2)
                    {
                        player->CastSpell(passenger, 65466, true);
                        kodo2->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                        kodo2->SetUInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                        kodo2->GetMotionMaster()->MoveFollow(me, 15.0f, M_PI);
                        kodo2->SetWalk(true);
                        me->GetMotionMaster()->MovePath(3443001, false);
                    }
                }
            }
            else
            {
                if (!m_IsArrived)
                    if (passenger->GetEntry() == 34438) 
                    {
                        me->CastSpell(me, 65557);
                        me->DespawnOrUnsummon(200);
                        if (Creature* kodo2 = ObjectAccessor::GetCreature(*me, m_kodoPackGUID))
                            kodo2->DespawnOrUnsummon(200);
                        if (Creature* balgor = ObjectAccessor::GetCreature(*me, m_balgorGUID))
                            balgor->DespawnOrUnsummon(200);
                    }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_timer < diff)
            {
                m_timer = 1000;
                if (m_phase) DoWork();
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
            case 1:
            {
                if (Creature* halga = me->FindNearestCreature(34258, 30.0f))
                {
                    halga->AI()->Talk(0);
                    me->SummonCreature(34431, 321.8f, -3699.1f, 27.03f);
                    me->SummonCreature(34438, 323.8f, -3697.1f, 27.03f);
                    me->GetMotionMaster()->MovePoint(21, 318.54f, -3670.49f, 27.18f);
                    m_phase = 2;
                }
                break;
            }
            case 2:
                break;
            case 3:
                me->GetMotionMaster()->MovePoint(22, 199.76f, -2979.85f, 91.67f);
                m_phase = 4;
                break;
            case 4:
                break;
            }
        }

        void CreateAttack()
        {
            if (Creature* gunner = ObjectAccessor::GetCreature(*me, m_gunnerGUID))
            {
                std::list<Creature*> cList = me->FindNearestCreatures(34487, 40.0f);
                for (uint32 i = cList.size(); i < urand(3, 5); i++)
                    me->CastSpell(gunner, 65496, true);
            }
        }

        void TargetArrived()
        {
            m_IsArrived = true;
            if (Creature* balgor = ObjectAccessor::GetCreature(*me, m_balgorGUID))
                balgor->AI()->Talk(0);
            if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
            {
                player->KilledMonsterCredit(53613);
                player->CastSpell(player, 65561);
                player->ExitVehicle();
                player->CompleteQuest(13949);
            }
            m_phase = 3;
            m_timer = 3000;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lead_caravan_kodo_34430AI(creature);
    }
};

// 34431
class npc_balgor_whipshank_34431 : public CreatureScript
{
public:
    npc_balgor_whipshank_34431() : CreatureScript("npc_balgor_whipshank_34431") { }

    struct npc_balgor_whipshank_34431AI : public ScriptedAI
    {
        npc_balgor_whipshank_34431AI(Creature* creature) : ScriptedAI(creature) { }

        uint64 m_kodoLeaderGUID;

        void Reset() override
        {
            m_kodoLeaderGUID = 0;
        }

        void SetGUID(uint64 guid, int32 id = 0) 
        { 
            switch (id)
            {
                case 34430:
                    m_kodoLeaderGUID = guid;
                    if (Creature* kodo = ObjectAccessor::GetCreature(*me, guid))
                        me->EnterVehicle(kodo, 0);
                    break;
                case 34577:
                {
                    m_kodoLeaderGUID = guid;
                    if (Creature* kodo = ObjectAccessor::GetCreature(*me, guid))
                        me->EnterVehicle(kodo, 0);
                    break;
                }
            }
        }

        uint64 GetGUID(int32 id = 0) const 
        { 
            switch (id)
            {
                case 34430:
                    return m_kodoLeaderGUID;
                case 34577:
                    return m_kodoLeaderGUID;
                default:
                    return 0;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_balgor_whipshank_34431AI(creature);
    }
};

// 34438
class vehicle_riding_shotgun_34438 : public VehicleScript
{
public:
    vehicle_riding_shotgun_34438() : VehicleScript("npc_riding_shotgun_34438") { }

    void OnAddPassenger(Vehicle* veh, Unit* passenger, int8 /*seatId*/)
    {
        passenger->SetFacingTo(M_PI);
        veh->RelocatePassengers();
    }

    void OnRemovePassenger(Vehicle* veh, Unit* passenger)
    {
        if (Creature* gunner = veh->GetBase()->ToCreature())
            gunner->DespawnOrUnsummon(100);
    }
};

// 65485
class spell_mount_caravan_kodo_cue_65485 : public SpellScriptLoader
{
public:
    spell_mount_caravan_kodo_cue_65485() : SpellScriptLoader("spell_mount_caravan_kodo_cue_65485") { }

    class spell_mount_caravan_kodo_cue_65485_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mount_caravan_kodo_cue_65485_SpellScript);

        void SetMount(SpellEffIndex effIndex)
        {
            if (Unit* unit = GetCaster())
                if (Player* player = unit->ToPlayer())
                    if (Creature* kodo1 = player->FindNearestCreature(34430, 6.0f)) //  how to find kodo as spell target?? GetCaster and GetHitUnit are both player
                        if (Creature* gunner = ObjectAccessor::GetCreature(*unit, kodo1->AI()->GetGUID(34438)))
                        {
                            kodo1->AI()->SetGUID(player->GetGUID(), 99999);
                            gunner->EnterVehicle(kodo1, 1);
                        }
        }

        void Register()
        {
            OnEffectHit += SpellEffectFn(spell_mount_caravan_kodo_cue_65485_SpellScript::SetMount, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_mount_caravan_kodo_cue_65485_SpellScript();
    }
};

/* ################################################# */

// 34305
class npc_razormane_pillager_34503 : public CreatureScript
{
public:
    npc_razormane_pillager_34503() : CreatureScript("npc_razormane_pillager_34503") { }

    enum eRazormane
    {
        QUEST_DRAG_IT_OUT_OF_THEM = 13961,
        SPELL_GROLDOM_NET = 65580,
        SPELL_SNARED_IN_NET = 65581,
        SPELL_GET_A_HOGTIED_RAZORMANE = 65599,
        SPELL_PERMANENT_FEIGN_DEATH = 29266,
        SPELL_SUMMON_HOGTIED_RAZORMANE = 65595,
        PLAYER_GUID = 99999,
    };

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) 
    { 
        if (player->GetQuestStatus(QUEST_DRAG_IT_OUT_OF_THEM) == QUEST_STATUS_INCOMPLETE)
            if (action == 1)
            {
                creature->SetHomePosition(creature->GetPosition());
                player->CastSpell(creature, SPELL_GET_A_HOGTIED_RAZORMANE);
                creature->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
                creature->AI()->DoAction(1);
                return true;
            }

        return false; 
    }

    struct npc_razormane_pillager_34503AI : public ScriptedAI
    {
        npc_razormane_pillager_34503AI(Creature* creature) : ScriptedAI(creature) { }

        uint32 m_timer;
        uint32 m_phase;
        uint64 m_playerGUID;

        void Reset() override
        {
            m_timer = 0;
            m_phase = 0;
            m_playerGUID = 0;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        { 
            if (spell->Id == SPELL_GROLDOM_NET)
            {
                me->setFaction(1933);
                me->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAGS);
                me->SetUInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_RENAME || UNIT_FLAG_STUNNED || UNIT_FLAG_IN_COMBAT || UNIT_FLAG_DISABLE_MOVE);
                me->CastSpell(me, SPELL_SNARED_IN_NET, true);
                me->SetDisplayId(1344);
                Talk(1);
            }
        }

        void SetGUID(uint64 guid, int32 id = 0) override
        {
            switch (id)
            {
            case 99999:
                if (!m_playerGUID)
                    m_playerGUID = guid;
                break;
            }
        }

        uint64 GetGUID(int32 id = 0) const override
        {
            switch (id)
            {
            case 99999:
                return m_playerGUID;
            default:
                return 0;
            }
        }

        void DoAction(int32 param) override
        { 
            switch (param)
            {
            case 1:
                m_phase = 1;
                m_timer = 1000;
                break;
            default:
                break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (m_timer < diff)
            {
                m_timer = 1000;
                if (m_phase) 
                    DoWork();
            }
            else
                m_timer -= diff;

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void DoWork()
        {
            switch (m_phase)
            {
                case 1:
                {
                    me->CastSpell(me, SPELL_PERMANENT_FEIGN_DEATH);
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        player->CastSpell(player, SPELL_SUMMON_HOGTIED_RAZORMANE);

                    }
                    m_phase = 2;
                    m_timer = 50;
                    break;
                }
                case 2:
                {
                    if (Creature* raz = me->FindNearestCreature(34514, 10.0f))
                        raz->AI()->SetGUID(m_playerGUID, PLAYER_GUID);
                    me->DespawnOrUnsummon(200);
                    m_phase = 0;
                    m_timer = 0;
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_razormane_pillager_34503AI(creature);
    }
};

// 34514
class npc_hogtied_razormane_34514 : public CreatureScript
{
public:
    npc_hogtied_razormane_34514() : CreatureScript("npc_hogtied_razormane_34514") { }

    enum eRazormane
    {
        NPC_TOGRIK_34513 = 34513,
        QUEST_DRAG_IT_OUT_OF_THEM = 13961,
        SPELL_DEAD_SOLDIER = 45801,
        SPELL_HOGTIED_RAZORMANE_ROPE = 65596,
        SPELL_DRAGGING_A_RAZORMANE = 65601,
        SPELL_RAZORMANE_DRAGGING_AURA = 65608,
        SPELL_SUMMON_HOGTIED_RAZORMANE = 65595,
        SPELL_RAZORMANE_DRAGGING_TRIGGER = 65610,
        PLAYER_GUID = 99999,
    };

    struct npc_hogtied_razormane_34514AI : public ScriptedAI
    {
        npc_hogtied_razormane_34514AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        uint32 m_timer;
        uint32 m_phase;
        uint64 m_playerGUID;

        void Initialize()
        {
            m_timer = 0;
            m_phase = 0;
            m_playerGUID = 0;
        }

        void IsSummonedBy(Unit* summoner) override
        { 
            if (Player* player = summoner->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                me->CastSpell(me, SPELL_DEAD_SOLDIER);
                me->CastSpell(player, SPELL_DRAGGING_A_RAZORMANE);
                me->CastSpell(me, SPELL_RAZORMANE_DRAGGING_AURA, true);                
                player->AddAura(SPELL_DRAGGING_A_RAZORMANE, me);
                player->AddAura(SPELL_RAZORMANE_DRAGGING_AURA, me);
                player->CastSpell(me, SPELL_HOGTIED_RAZORMANE_ROPE);
                m_phase = 1;
                m_timer = 1000;
            }
        }

        void SetGUID(uint64 guid, int32 id = 0) override
        {
            switch (id)
            {
            case PLAYER_GUID:
                if (!m_playerGUID)
                    m_playerGUID = guid;
                break;
            }
        }

        uint64 GetGUID(int32 id = 0) const override
        {
            switch (id)
            {
            case PLAYER_GUID:
                return m_playerGUID;
            default:
                return 0;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (m_timer < diff)
            {
                m_timer = 1000;
                if (m_phase)
                    DoWork();
            }
            else
                m_timer -= diff;

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void DoWork()
        {
            switch (m_phase)
            {
                case 1:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        if (player->GetQuestStatus(QUEST_DRAG_IT_OUT_OF_THEM) == QUEST_STATUS_COMPLETE)
                        {
                            player->RemoveAura(SPELL_HOGTIED_RAZORMANE_ROPE);
                            player->RemoveAura(SPELL_DRAGGING_A_RAZORMANE);
                            me->DespawnOrUnsummon(0);
                            m_phase = 0;
                            m_timer = 0;
                        }
                        else
                        {
                            if (!me->HasAura(SPELL_HOGTIED_RAZORMANE_ROPE))
                                player->CastSpell(me, SPELL_HOGTIED_RAZORMANE_ROPE);
                            me->CastSpell(me, SPELL_RAZORMANE_DRAGGING_TRIGGER);
                        }
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_hogtied_razormane_34514AI(creature);
    }
};

// 5465 AreaTrigger
class at_groldoms_farm_5465 : public AreaTriggerScript
{
public:
    at_groldoms_farm_5465() : AreaTriggerScript("at_groldoms_farm_5465") { }

    enum eRazormane
    {
        QUEST_DRAG_IT_OUT_OF_THEM = 13961,
        AT_GROLDOMS_FARM = 5465,
        SPELL_DELIVER_HOGTIED_RAZORMANE = 65603,
        SPELL_SUMMON_HOGTIED_RAZORMANE = 65595,
        PLAYER_GUID = 99999,
    };

    bool OnTrigger(Player* player, const AreaTriggerEntry* at) override
    {
        if (at->id == AT_GROLDOMS_FARM)
            if ((player->GetQuestStatus(QUEST_DRAG_IT_OUT_OF_THEM) == QUEST_STATUS_INCOMPLETE))
            {
                player->CompleteQuest(QUEST_DRAG_IT_OUT_OF_THEM);
                player->CastSpell(player, SPELL_DELIVER_HOGTIED_RAZORMANE);

            }

        return false;
    }
};

/* ################################################# */

// 34513
class npc_togrik_34513 : public CreatureScript
{
public:
    npc_togrik_34513() : CreatureScript("npc_togrik_34513") { }

    enum eRazormane
    {
        QUEST_BY_HOOK_OR_BY_CROOK = 13963,
        NPC_CAPTURED_RAZORMANE = 34523,
        NPC_TOGRIK = 34513,
        EVENT_MAX_TIME = 1,
        DATA_MENU_ID = 99980,
        PLAYER_GUID = 99999,
        DOACTION_CREATE_CHAIN = 1,
        DOACTION_RESET = 3,
        DOACTION_GOSSIP_HELLO = 10,
        DOACTION_GOSSIP_SELECT = 11,
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_BY_HOOK_OR_BY_CROOK) == QUEST_STATUS_INCOMPLETE)
        {
            creature->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
            creature->AI()->DoAction(DOACTION_GOSSIP_HELLO);
            return true;
        }
        else
        {
            player->SEND_GOSSIP_MENU(14554, creature->GetGUID());
        }

        return false;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action >= 1000)
        {
            creature->AI()->SetData(DATA_MENU_ID, action);
            creature->AI()->DoAction(DOACTION_GOSSIP_SELECT);
            return true;
        }

        return false;
    }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) 
    {
        if (quest->GetQuestId() == QUEST_BY_HOOK_OR_BY_CROOK)
        {
            if (creature->AI()->GetData(NPC_TOGRIK) == 0)
            {
                creature->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
                creature->AI()->DoAction(1);
            }
            else
            {
                creature->AI()->DoAction(2);
            }
        }

        return false; 
    }

    struct npc_togrik_34513AI : public ScriptedAI
    {
        npc_togrik_34513AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint32   m_phase;
        uint32   m_action_id;
        uint64   m_playerGUID;
        uint64   m_razorGUID;
        uint8    m_encounter;

        void Initialize()
        {           
            m_encounter = 0;
        }

        void Reset() override
        {
            m_events.Reset();
            m_phase = 0;
            m_action_id = 0;
            m_playerGUID = 0;
            m_razorGUID = 0;
        }

        void SetData(uint32 id, uint32 value)
        {
            switch (id)
            {
            case DATA_MENU_ID:
                m_action_id = value;
                break;
            }
        }

        uint32 GetData(uint32 id) const override
        {
            switch (id)
            {
            case NPC_TOGRIK:
                return m_encounter;
            default:
                return 0;
            }
        }

        void SetGUID(uint64 guid, int32 id = 0) override
        {
            switch (id)
            {
            case PLAYER_GUID:
                if (!m_playerGUID)
                    m_playerGUID = guid;
                break;
            }
        }

        uint64 GetGUID(int32 id = 0) const override
        {
            switch (id)
            {
            case PLAYER_GUID:
                return m_playerGUID;
            default:
                return 0;
            }
        }

        void DoAction(int32 param) 
        { 
            switch (param)
            {
                case DOACTION_CREATE_CHAIN:
                {
                    CreateRazor();
                    break;
                }
                case DOACTION_RESET:
                {
                    Initialize();
                    Reset();
                    break;
                }
                case DOACTION_GOSSIP_HELLO:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        player->ADD_GOSSIP_ITEM_DB(10520, 0, GOSSIP_SENDER_MAIN, 1002);
                        player->SEND_GOSSIP_MENU(14554, me->GetGUID());
                    }
                    break;
                }
                case DOACTION_GOSSIP_SELECT:
                {
                    switch (m_action_id)
                    {
                        case 1002:
                        {
                            Creature* razor = ObjectAccessor::GetCreature(*me, m_razorGUID);
                            if (!razor)
                            {
                                CreateRazor();
                            }
                            break;
                        }
                    }
                    break;
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_MAX_TIME:
                    if (Creature* razor = ObjectAccessor::GetCreature(*me, m_razorGUID))
                        razor->DespawnOrUnsummon();
                    Initialize();
                    Reset();
                    break;
                default:
                    break;
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void CreateRazor()
        {
            m_encounter = 1;
            m_events.ScheduleEvent(EVENT_MAX_TIME, 600000);
            if (Creature* razor = me->SummonCreature(NPC_CAPTURED_RAZORMANE, 283.4774f, -3050.653f, 95.93713f, 3.490659f, TEMPSUMMON_TIMED_DESPAWN, 600000))
            {
                m_razorGUID = razor->GetGUID();
                razor->AI()->SetGUID(m_playerGUID);
                razor->AI()->DoAction(DOACTION_CREATE_CHAIN);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_togrik_34513AI(creature);
    }
};

// 34523
class npc_captured_razormane_34523 : public CreatureScript
{
public:
    npc_captured_razormane_34523() : CreatureScript("npc_captured_razormane_34523") { }

    enum eRazormane
    {
        QUEST_BY_HOOK_OR_BY_CROOK = 13963,
        NPC_DAVES_INDUSTRIAL_LIGHT_AND_MAGIC_BUNNY = 34527,
        NPC_TOGRIK = 34513,
        SPELL_COSMETIC_CHAINS = 65612,
        PLAYER_GUID = 99999,
        DATA_ACTION_ID = 99980,
        PATH_RAZORMANE = 3452301,
        DOACTION_CREATE_CHAIN = 1,
        DOACTION_RESET = 3,
        DOACTION_GOSSIP_HELLO = 10,
        DOACTION_GOSSIP_SELECT = 11,
        EVENT_SAY_END = 1,
    };

    bool OnGossipHello(Player* player, Creature* creature) 
    { 
        creature->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
        creature->AI()->DoAction(DOACTION_GOSSIP_HELLO);
        return true; 
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        creature->AI()->SetData(DATA_ACTION_ID, action);
        creature->AI()->DoAction(DOACTION_GOSSIP_SELECT);
        return true;
    }

    struct npc_captured_razormane_34523AI : public ScriptedAI
    {
        npc_captured_razormane_34523AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint32   m_phase;
        uint32   m_action_id;
        uint64   m_playerGUID;
        uint64   m_bunnyGUID;
        uint64   m_togrikGUID;
        
        void Reset() override
        {
            m_events.Reset();
            m_phase = 0;
            m_action_id = 0;
            m_playerGUID = 0;
            m_togrikGUID = 0;

            if (Creature* bunny = me->FindNearestCreature(NPC_DAVES_INDUSTRIAL_LIGHT_AND_MAGIC_BUNNY, 25.0f))
                m_bunnyGUID = bunny->GetGUID();
            else
                m_bunnyGUID = 0;
        }

        void JustDied(Unit* /*killer*/) 
        { 
            if (Creature* togrik = ObjectAccessor::GetCreature(*me, m_togrikGUID))
                togrik->AI()->DoAction(DOACTION_RESET);
        }

        void SetData(uint32 id, uint32 value) 
        { 
            switch (id)
            {
                case DATA_ACTION_ID:
                    m_action_id = value;
                    break;
                }
        }

        void SetGUID(uint64 guid, int32 id = 0) override
        {
            switch (id)
            {
                case NPC_DAVES_INDUSTRIAL_LIGHT_AND_MAGIC_BUNNY:
                    m_bunnyGUID = guid;
                    break;
                case NPC_TOGRIK:
                    m_togrikGUID = guid;
                    break;
                case PLAYER_GUID:
                    if (!m_playerGUID)
                        m_playerGUID = guid;
                    break;
            }
        }

        uint64 GetGUID(int32 id = 0) const override
        {
            switch (id)
            {
                case NPC_DAVES_INDUSTRIAL_LIGHT_AND_MAGIC_BUNNY:
                    return m_bunnyGUID;
                case NPC_TOGRIK:
                    return m_togrikGUID;
                case PLAYER_GUID:
                    return m_playerGUID;
                default:
                    return 0;
            }
        }

        void DoAction(int32 param)
        {
            switch (param)
            {
                case DOACTION_CREATE_CHAIN:
                {
                    me->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    if (Creature* bunny = ObjectAccessor::GetCreature(*me, m_bunnyGUID))
                    {
                        bunny->CastSpell(me, SPELL_COSMETIC_CHAINS);
                        me->SetSpeed(MOVE_WALK, 0.5f);
                        me->GetMotionMaster()->MovePath(PATH_RAZORMANE, true);
                    }
                    break;
                }
                case DOACTION_GOSSIP_HELLO:
                {
                    Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID);
                    if (!player)
                        return;

                    switch (m_phase)
                    {
                        case 0:
                        {
                            player->ADD_GOSSIP_ITEM_DB(10521, 0, GOSSIP_SENDER_MAIN, 1010);
                            player->ADD_GOSSIP_ITEM_DB(10521, 1, GOSSIP_SENDER_MAIN, 1011);
                            player->ADD_GOSSIP_ITEM_DB(10521, 2, GOSSIP_SENDER_MAIN, 1012);
                            player->ADD_GOSSIP_ITEM_DB(10521, 3, GOSSIP_SENDER_MAIN, 1013);
                            player->ADD_GOSSIP_ITEM_DB(10521, 4, GOSSIP_SENDER_MAIN, 1014);
                            player->SEND_GOSSIP_MENU(14555, me->GetGUID());
                            break;
                        }
                        case 1:
                        case 2:
                        case 3:
                        case 4:
                        case 5:
                        {
                            player->ADD_GOSSIP_ITEM_DB(10521, 0, GOSSIP_SENDER_MAIN, 1010);
                            player->ADD_GOSSIP_ITEM_DB(10521, 1, GOSSIP_SENDER_MAIN, 1011);
                            player->ADD_GOSSIP_ITEM_DB(10521, 2, GOSSIP_SENDER_MAIN, 1012);
                            player->SEND_GOSSIP_MENU(14555, me->GetGUID());
                            break;
                        }
                    }
                    break;
                }
                case DOACTION_GOSSIP_SELECT:
                {
                    Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID);
                    if (!player)
                        return;

                    switch (m_action_id)
                    {
                    case 1010:
                        player->CastSpell(me, 65618);
                        break;
                    case 1011:
                        player->CastSpell(me, 65620);
                        break;
                    case 1012:
                        player->CastSpell(me, 65619);
                        break;
                    case 1013:
                        player->CastSpell(me, 65618);
                        break;
                    case 1014:
                        player->CastSpell(me, 65621);
                        break;
                    }

                    Talk(m_phase);
                    me->HandleEmoteCommand(34);
                    player->PlayerTalkClass->SendCloseGossip();
                    m_phase++;
                
                    if (m_phase >= 5)
                    {
                        player->KilledMonsterCredit(34529);
                        m_events.RescheduleEvent(EVENT_SAY_END, 5000);
                    }
                    break;
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_SAY_END:
                    {
                        Talk(m_phase);
                        me->DespawnOrUnsummon(10000);
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

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_captured_razormane_34523AI(creature);
    }
};

/* ################################################# */

// 34547
class npc_groldom_kodo_34547 : public CreatureScript
{
public:
    npc_groldom_kodo_34547() : CreatureScript("npc_groldom_kodo_34547") { }

    enum eRazormane
    {
        QUEST_THE_KODOS_RETURN = 13971,
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_THE_KODOS_RETURN)
        {
            creature->RemoveAura(54852);
            creature->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
            creature->SetUInt32Value(UNIT_FIELD_BYTES_2, 0);
            creature->GetMotionMaster()->MovePoint(1, 50.17f, -3129.29f, 96.67f, true);
            creature->DespawnOrUnsummon(10000);
            return true;
        }

        return false;
    }
};

// 34543
class npc_fez_34543 : public CreatureScript
{
public:
    npc_fez_34543() : CreatureScript("npc_fez_34543") { }

    enum eFez
    {
       
    };

    struct npc_fez_34543AI : public ScriptedAI
    {
        npc_fez_34543AI(Creature* creature) : ScriptedAI(creature) {  }

        EventMap m_events;
       
        void Reset() override
        {
            m_events.Reset();
            m_events.ScheduleEvent(1, 2500);
        }

        void UpdateAI(uint32 diff)
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case 1:
                    m_events.ScheduleEvent(1, 2500);
                    if (!me->IsInCombat())
                        if (Vehicle* fez = me->GetVehicleKit())
                            if (!fez->IsVehicleInUse())
                                if (Creature* tortusk = me->FindNearestCreature(34544, 50.0f))
                                    if (!tortusk->IsInCombat())
                                        tortusk->EnterVehicle(me, 0);
                    break;
                default:
                    break;
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_fez_34543AI(creature);
    }
};

/* ################################################# */

// 34578
class npc_rocco_whipshank_34578 : public CreatureScript
{
public:
    npc_rocco_whipshank_34578() : CreatureScript("npc_rocco_whipshank_34578") { }

    enum eRocco
    {
        QUEST_CROSSROADS_CARAVAN_DELIVERY = 13975,
        NPC_HEAD_CARAVAN_KODO = 34577,
        NPN_BALGOR_WHIPSHANK = 34431,
        SPELL_SUMMON_KODO_PART2 = 65662,
        SPELL_WORLD_GENERIC_DISMOUNT_CANCEL_SHAPESHIFT = 61286,
        PLAYER_GUID = 99999,
        DATA_IS_ANUM_STARTED = 99998,
        DOACTION_RESET = 3,
        DOACTION_GOSSIP_HELLO = 10,
        DOACTION_GOSSIP_SELECT = 11,
        EVENT_MAX_TIME = 1,
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_CROSSROADS_CARAVAN_DELIVERY) == QUEST_STATUS_INCOMPLETE)
        {
            creature->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
            creature->AI()->DoAction(DOACTION_GOSSIP_HELLO);
            return true;
        }

        return false;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (action == 1002)
        {
            creature->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
            creature->AI()->DoAction(DOACTION_GOSSIP_SELECT);
            player->PlayerTalkClass->SendCloseGossip();
            return true;
        }

        return false;
    }

    struct npc_rocco_whipshank_34578AI : public ScriptedAI
    {
        npc_rocco_whipshank_34578AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint32   m_phase;
        uint32   m_is_anim_started;
        uint64   m_playerGUID;
        uint64   m_kodoLeader;
        uint64   m_kodoPack;

        void Reset() override
        {
            m_events.Reset();
            m_phase = 0;
            m_is_anim_started = false;
            m_playerGUID = 0;
            m_kodoLeader = 0;
            m_kodoPack = 0;
        }

        void JustSummoned(Creature* summon) 
        { 
            switch (summon->GetEntry())
            {
            case NPC_HEAD_CARAVAN_KODO:
                m_kodoLeader = summon->GetGUID();
                summon->AI()->SetGUID(m_playerGUID, PLAYER_GUID);
                summon->AI()->SetGUID(me->GetGUID(), me->GetEntry());
                summon->SummonCreature(NPN_BALGOR_WHIPSHANK, 220.5f, -2964.5f, 91.82f);
                break;
            default:
                printf("JustSummoned rocco: %u \n", summon->GetEntry());
                break;
            }
        }

        void SetData(uint32 id, uint32 value)
        {
            switch (id)
            {
            case DATA_IS_ANUM_STARTED:
                m_is_anim_started = value;
                break;
            }
        }

        uint32 GetData(uint32 id) const override
        {
            switch (id)
            {
            case DATA_IS_ANUM_STARTED:
                return m_is_anim_started;
            default:
                return 0;
            }
        }

        void SetGUID(uint64 guid, int32 id = 0) override
        {
            switch (id)
            {
            case PLAYER_GUID:
                if (!m_playerGUID)
                    m_playerGUID = guid;
                break;
            }
        }

        uint64 GetGUID(int32 id = 0) const override
        {
            switch (id)
            {
            case PLAYER_GUID:
                return m_playerGUID;
            default:
                return 0;
            }
        }

        void DoAction(int32 param)
        {
            switch (param)
            {
                case DOACTION_RESET:
                {
                    Reset();
                    break;
                }
                case DOACTION_GOSSIP_HELLO:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        if (!m_is_anim_started)
                        {
                            player->ADD_GOSSIP_ITEM_DB(10528, 0, GOSSIP_SENDER_MAIN, 1002);
                            player->SEND_GOSSIP_MENU(14566, me->GetGUID());
                        }
                    break;
                }
                case DOACTION_GOSSIP_SELECT:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        m_is_anim_started = true;
                        m_events.ScheduleEvent(EVENT_MAX_TIME, 600000);
                        me->CastSpell(player, SPELL_SUMMON_KODO_PART2);
                        me->CastSpell(player, SPELL_WORLD_GENERIC_DISMOUNT_CANCEL_SHAPESHIFT);
                    }
                    break;
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_MAX_TIME:
                        // delete kodoleader mm
                        Reset();
                        break;
                    default:
                        break;
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void CreateKodo()
        {
            
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_rocco_whipshank_34578AI(creature);
    }
};

// 34577
class npc_head_caravan_kodo_34577 : public CreatureScript
{
public:
    npc_head_caravan_kodo_34577() : CreatureScript("npc_head_caravan_kodo_34577") { }

    enum eKodo
    {
        QUEST_CROSSROADS_CARAVAN_DELIVERY = 13975,
        PLAYER_GUID = 99999,
        NPC_ROCCO_WHIPSHANK = 34578,
        NPC_THE_HOTSEAT = 34582,
        NPC_CROSSROADS_CARAVAN_KODO = 34576,
        NPN_BALGOR_WHIPSHANK = 34431,
        NPC_BURNING_BLADE_MOUNT = 34593,
        NPC_BURNING_BLADE_RAIDER = 34594,
        SPELL_CALL_A_PACK_KODO2 = 65663,
        SPELL_MOUNT_UP = 65671,
        SPELL_RIDE_CARAVAN_KODO = 65466,
        EVENT_SUMMON_CARAVAN = 1,
        EVENT_RIDE_KODO = 2,
        EVENT_START_CARAVAN = 3,
        DOACTION_RESET=3,
    };

    struct npc_head_caravan_kodo_34577AI : public ScriptedAI
    {
        npc_head_caravan_kodo_34577AI(Creature* creature) : ScriptedAI(creature) { }

        uint32 m_phase;
        EventMap m_events;
        bool m_IsArrived;
        uint64 m_playerGUID;
        uint64 m_roccoGUID;
        uint64 m_balgorGUID;
        uint64 m_kodo2GUID;
        uint64 m_hotseatGUID;

        void Reset() override
        {
            m_phase = 1;
            m_events.Reset();
            m_IsArrived = false;
            m_playerGUID = 0;
            m_roccoGUID = 0;
            m_balgorGUID = 0;
            m_kodo2GUID = 0;
            m_hotseatGUID = 0;
            me->SetUInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == 8 && id == 21)
                m_events.ScheduleEvent(EVENT_SUMMON_CARAVAN, 100);
            else if (type == 2)
            {
                if (id == 1)
                    Greetings();
                else if (id == 3)
                    Warning1();
                else if (id == 5)
                    Warning2();
                else if (id == 26)
                    MadeIt();
                else if (id == 27)
                    CaravanArrived();
                else if (id > 7 && id < 25)
                    CreateAttack();
            }
        }

        void JustSummoned(Creature* summon) override
        {
            switch (summon->GetEntry())
            {
            case NPN_BALGOR_WHIPSHANK:
                m_balgorGUID = summon->GetGUID();
                summon->EnterVehicle(me, 0);
                summon->SetUInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                me->GetMotionMaster()->MovePoint(21, 205.1f, -2935.985f, 92.66f, true);
                break;
            case NPC_CROSSROADS_CARAVAN_KODO:
                m_kodo2GUID = summon->GetGUID();
                summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE || UNIT_FLAG_IMMUNE_TO_NPC);
                summon->SetWalk(false);
                break;
            case NPC_THE_HOTSEAT:
                m_hotseatGUID = summon->GetGUID();
                summon->SetUInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                break;
            case NPC_BURNING_BLADE_MOUNT:
                if (Creature* raider = me->SummonCreature(NPC_BURNING_BLADE_RAIDER, summon->GetPosition(), TEMPSUMMON_TIMED_DESPAWN, 300000))
                {
                    raider->SetSpeed(MOVE_WALK, 3.0f, true);
                    summon->SetSpeed(MOVE_WALK, 3.0f, true);
                    raider->EnterVehicle(summon);
                    raider->AI()->SetGUID(m_playerGUID, PLAYER_GUID);
                    raider->AI()->SetGUID(m_kodo2GUID, NPC_CROSSROADS_CARAVAN_KODO);
                }
                break;
            default:
                break;
            }
        }

        void SetGUID(uint64 guid, int32 id = 0)
        {
            switch (id)
            {
                case NPC_ROCCO_WHIPSHANK:
                    m_roccoGUID = guid;
                    break;
                case PLAYER_GUID:
                    m_playerGUID = guid;
                    break;
                default:
                    break;
            }
        }

        uint64 GetGUID(int32 id = 0) const
        {
            switch (id)
            {
            case NPC_ROCCO_WHIPSHANK:
                return m_roccoGUID;
            case PLAYER_GUID:
                return m_playerGUID;
            case NPC_THE_HOTSEAT:
                return m_hotseatGUID;
            default:
                return 0;
            }
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply)
        {
            if (apply)
            {
                if (passenger->GetEntry() == NPC_THE_HOTSEAT)
                {
                    Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID);
                    Creature* hotseat = ObjectAccessor::GetCreature(*me, m_hotseatGUID);
                    if (player && hotseat)
                    {
                        hotseat->CastSpell(player, SPELL_MOUNT_UP);
                        m_events.ScheduleEvent(EVENT_RIDE_KODO, 250); 
                        m_events.ScheduleEvent(EVENT_START_CARAVAN, 500);
                    }
                }
            }
            else
            {
                if (!m_IsArrived)
                    if (passenger->GetEntry() == NPC_THE_HOTSEAT)
                    {
                        if (Creature* balgor = ObjectAccessor::GetCreature(*me, m_balgorGUID))
                            balgor->DespawnOrUnsummon(100);
                        if (Creature* rocco = ObjectAccessor::GetCreature(*me, m_roccoGUID))
                            rocco->AI()->DoAction(DOACTION_RESET);
                        me->DespawnOrUnsummon(100);
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
                case EVENT_SUMMON_CARAVAN:
                    me->CastSpell(me, SPELL_CALL_A_PACK_KODO2);
                    me->SummonCreature(NPC_THE_HOTSEAT, me->GetPosition());                    
                    if (Creature* rocco = ObjectAccessor::GetCreature(*me, m_roccoGUID))
                        rocco->AI()->Talk(0);
                    break;
                case EVENT_RIDE_KODO:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        if (Creature* hotseat = ObjectAccessor::GetCreature(*me, m_hotseatGUID))
                            player->CastSpell(hotseat, SPELL_RIDE_CARAVAN_KODO);

                    break;
                }
                case EVENT_START_CARAVAN:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        if (Creature* rocco = ObjectAccessor::GetCreature(*me, m_roccoGUID))
                            if (Creature* kodo2 = ObjectAccessor::GetCreature(*me, m_kodo2GUID))
                            {
                                kodo2->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                                kodo2->SetUInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                                kodo2->GetMotionMaster()->MoveFollow(me, 15.0f, M_PI);
                                kodo2->SetWalk(true);
                                me->GetMotionMaster()->MovePath(3457701, false);
                                rocco->AI()->Talk(1);
                            }
                    break;
                }
                default:
                    break;
                }
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

        void Greetings()
        {            
            // Music ID : 24676
            if (Creature* rocco = ObjectAccessor::GetCreature(*me, m_roccoGUID))
                rocco->AI()->Talk(1);           
        }

        void Warning1()
        {
            if (Creature* balgor = ObjectAccessor::GetCreature(*me, m_balgorGUID))
                balgor->AI()->Talk(1);
        }

        void Warning2()
        {
            if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                if (Creature* hotseat = ObjectAccessor::GetCreature(*me, m_hotseatGUID))
                    hotseat->AI()->Talk(0, player);
        }

        void CreateAttack()
        {
            std::list<Creature*> cList = me->FindNearestCreatures(34594, 50.0f);
            for (uint32 i = cList.size(); i < 5; i++)
                me->CastSpell(me, 65692);
        }

        void MadeIt()
        {
            if (Creature* balgor = ObjectAccessor::GetCreature(*me, m_balgorGUID))
                balgor->AI()->Talk(2, me);
        }

        void CaravanArrived()
        {
            m_IsArrived = true;
            if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
            {
                player->ExitVehicle();
                player->KilledMonsterCredit(53572);
                player->RemoveAura(65466);
                player->CompleteQuest(QUEST_CROSSROADS_CARAVAN_DELIVERY);
            }
            if (Creature* balgor = ObjectAccessor::GetCreature(*me, m_balgorGUID))
            {
                me->CastSpell(balgor, 65695);
                balgor->DespawnOrUnsummon(100);
            }
            if (Creature* hotseat = ObjectAccessor::GetCreature(*me, m_hotseatGUID))
            {
                hotseat->CastSpell(hotseat, 50630);
                hotseat->DespawnOrUnsummon(100);
            }
            if (Creature* rocco = ObjectAccessor::GetCreature(*me, m_roccoGUID))
                rocco->AI()->DoAction(DOACTION_RESET);
            if (Creature* kodo2 = ObjectAccessor::GetCreature(*me, m_kodo2GUID))
                kodo2->CastSpell(kodo2, 50630);
            // ServerToClient: SMSG_PET_DISMISS_SOUND(0x1ABB) Length : 16 ConnIdx : 0 Time : 09 / 07 / 2014 07 : 27 : 46.000 Number : 392240
            // Sound ID : 1731
            me->DespawnOrUnsummon(100);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_head_caravan_kodo_34577AI(creature);
    }
};

// 34582
class vehicle_hotseat_34582 : public VehicleScript
{
public:
    vehicle_hotseat_34582() : VehicleScript("vehicle_hotseat_34582") { }

    void OnAddPassenger(Vehicle* veh, Unit* passenger, int8 /*seatId*/)
    {
        passenger->SetFacingTo(5.14f);
        veh->RelocatePassengers();
    }

    void OnRemovePassenger(Vehicle* veh, Unit* passenger)
    {
        passenger->RemoveAura(65466);
        if (Creature* gunner = veh->GetBase()->ToCreature())
            gunner->DespawnOrUnsummon(100);
    }
};

// 65669
class spell_mount_caravan_kodo_cue_part2_65669 : public SpellScriptLoader
{
public:
    spell_mount_caravan_kodo_cue_part2_65669() : SpellScriptLoader("spell_mount_caravan_kodo_cue_part2_65669") { }

    enum eSpell
    {
        NPC_HEAD_CARAVAN_KODO = 34577,
        NPC_THE_HOTSEAT = 34582,
    };

    class spell_mount_caravan_kodo_cue_part2_65669_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mount_caravan_kodo_cue_part2_65669_SpellScript);

        void SetMount(SpellEffIndex effIndex)
        {
            if (Unit* unit = GetCaster())
                if (Player* player = unit->ToPlayer())
                    if (Creature* kodo1 = player->FindNearestCreature(NPC_HEAD_CARAVAN_KODO, 6.0f)) //  how to find kodo as spell target?? GetCaster and GetHitUnit are both player
                        if (Creature* hotseat = ObjectAccessor::GetCreature(*unit, kodo1->AI()->GetGUID(NPC_THE_HOTSEAT)))
                            hotseat->EnterVehicle(kodo1, 1);
        }

        void Register()
        {
            OnEffectHit += SpellEffectFn(spell_mount_caravan_kodo_cue_part2_65669_SpellScript::SetMount, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_mount_caravan_kodo_cue_part2_65669_SpellScript();
    }
};

// 34593
class vehicle_burning_blade_mount_34593 : public VehicleScript
{
public:
    vehicle_burning_blade_mount_34593() : VehicleScript("vehicle_burning_blade_mount_34593") { }

    enum eVehicle
    {
        NPC_CROSSROADS_CARAVAN_KODO = 34576,
    };

    void OnAddPassenger(Vehicle* veh, Unit* passenger, int8 /*seatId*/)
    {
        if (Creature* mount = veh->GetBase()->ToCreature())
            if (Creature* kodo2 = mount->FindNearestCreature(NPC_CROSSROADS_CARAVAN_KODO, 50.0f))
                mount->GetMotionMaster()->MoveFollow(kodo2, frand(0.5f, 2.0f), frand(0.0f, 6.28f));
    }

    void OnRemovePassenger(Vehicle* veh, Unit* passenger)
    {
        if (Creature* mount = veh->GetBase()->ToCreature())
        {
            mount->SetSpeed(MOVE_WALK, 0.4f, true);
            mount->GetMotionMaster()->MoveConfused();
            mount->DespawnOrUnsummon(30000);
        }
    }
};

// 34594
class npc_burning_blade_raider_34594 : public CreatureScript
{
public:
    npc_burning_blade_raider_34594() : CreatureScript("npc_burning_blade_raider_34594") { }

    enum eRaider
    {
        QUEST_CROSSROADS_CARAVAN_DELIVERY = 13975,
        PLAYER_GUID = 99999,
        NPC_CROSSROADS_CARAVAN_KODO = 34576,
    };

    struct npc_burning_blade_raider_34594AI : public ScriptedAI
    {
        npc_burning_blade_raider_34594AI(Creature* creature) : ScriptedAI(creature) { }

        uint32 m_timer;
        uint64 m_playerGUID;
        uint64 m_kodo2GUID;

        void Reset()
        {
            m_timer = 3000;
            m_playerGUID = 0;
        }

        void SetGUID(uint64 guid, int32 id = 0)
        {
            switch (id)
            {
            case PLAYER_GUID:
                m_playerGUID = guid;
                break;
            case NPC_CROSSROADS_CARAVAN_KODO:
                m_kodo2GUID = guid;
                break;
            default:
                break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_timer < diff)
            {
                m_timer = 1000;
                if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    if (player->GetQuestStatus(QUEST_CROSSROADS_CARAVAN_DELIVERY) == QUEST_STATUS_COMPLETE)
                        me->DespawnOrUnsummon(1000);
                if (!me->IsMounted())
                {
                    m_timer = 10000;
                    me->SetSpeed(MOVE_WALK, 3.0f, true);
                    if (Creature* kodo2 = ObjectAccessor::GetCreature(*me, m_kodo2GUID))
                        me->GetMotionMaster()->MoveFollow(kodo2, 1, frand(0.0f, 6.28f));
                }
            }
            else
                m_timer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_burning_blade_raider_34594AI(creature);
    }
};

/* ################################################# */

// 5482 AreaTrigger - quest 14066
class at_caravan_scene_5482 : public AreaTriggerScript
{
public:
    at_caravan_scene_5482() : AreaTriggerScript("at_caravan_scene_5482") { }

    enum eQuest
    {
        QUEST_INVESTIGATE_THE_WRECKAGE = 14066,
        NPC_QUESTGIVER = 3464,
    };

    bool OnTrigger(Player* player, const AreaTriggerEntry* at) override
    {
        if ((player->GetQuestStatus(QUEST_INVESTIGATE_THE_WRECKAGE) == QUEST_STATUS_INCOMPLETE))
        {
            player->KilledMonsterCredit(NPC_QUESTGIVER);
        }

        return false;
    }
};

// 5483 AreaTrigger - quest 869
class at_follow_the_tracks_5483 : public AreaTriggerScript
{
public:
    at_follow_the_tracks_5483() : AreaTriggerScript("at_follow_the_tracks_5483") { }

    enum eQuest
    {
        QUEST_TO_TRACK_A_THIEF = 869,
        NPC_QUESTGIVER = 3464,
    };

    bool OnTrigger(Player* player, const AreaTriggerEntry* at) override
    {
        if ((player->GetQuestStatus(QUEST_TO_TRACK_A_THIEF) == QUEST_STATUS_INCOMPLETE))
        {
            player->KilledMonsterCredit(NPC_QUESTGIVER);
        }

        return false;
    }
};

void AddSC_zone_northern_barrens()
{
    new npc_gorgal_angerscar_34634();
    new npc_shoe_34638();
    new go_red_raptor_nest_6906();
    new go_blue_raptor_nest_6907();
    new go_yellow_raptor_nest_6908();
    new npc_wyneth_34846();
    new npc_verog_the_dervish_3395();
    new npc_trapped_wolf_34285();
    new npc_chain_origin_34287();
    new go_wolf_chains();
    new npc_halga_bloodeye_34258();
    new npc_lead_caravan_kodo_34430();
    new npc_balgor_whipshank_34431();
    new vehicle_riding_shotgun_34438();
    new spell_mount_caravan_kodo_cue_65485();
    new npc_razormane_raider_34487();
    new npc_razormane_pillager_34503();
    new npc_hogtied_razormane_34514();
    new at_groldoms_farm_5465();
    new npc_togrik_34513();
    new npc_captured_razormane_34523();
    new npc_groldom_kodo_34547();
    new npc_fez_34543();
    new npc_rocco_whipshank_34578();
    new npc_head_caravan_kodo_34577();
    new vehicle_hotseat_34582();
    new spell_mount_caravan_kodo_cue_part2_65669();
    new vehicle_burning_blade_mount_34593();
    new npc_burning_blade_raider_34594();
    new at_caravan_scene_5482();
    new at_follow_the_tracks_5483();

}
