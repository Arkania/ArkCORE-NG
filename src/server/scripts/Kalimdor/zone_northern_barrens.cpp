/*
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

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) 
    { 
        if (quest->GetQuestId() == 13995)
        {
            creature->AI()->DoAction(1);
            CAST_AI(npc_gorgal_angerscar_34634AI, creature->GetAI())->m_playerGUID = player->GetGUID();
        }

        return false; 
    }

    struct npc_gorgal_angerscar_34634AI : public ScriptedAI
    {
        npc_gorgal_angerscar_34634AI(Creature* creature) : ScriptedAI(creature) { }

        uint32 m_phase;
        uint32 m_timer;
        uint64 m_kolkarGUID;
        uint64 m_kurakGUID;
        uint64 m_playerGUID;

        void Reset() override
        {
            m_phase = 0;
            m_timer = 0;
            m_kolkarGUID = NULL;
            m_kurakGUID = NULL;
            m_playerGUID = NULL;
        }

        void KilledUnit(Unit* victim) 
        {
            if (victim->GetEntry() == 3275)
                m_phase = 5;
            else if (victim->GetEntry() == 34635)
                m_phase = 7;
        }

        void MovementInform(uint32 type, uint32 id) 
        { 
            if (type == 2 && id == 7)
            {
                Talk(1);
                m_phase = 3;
                m_timer = 2000;
            }
        }

        void DoAction(int32 param) 
        { 
            if (param == 1 && m_phase == 0)
            {
                m_phase = 1;
                m_timer = 100;
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
                Talk(0);
                me->GetMotionMaster()->MovePath(1389261, false);
                m_phase = 2;
                break;
            case 2:
                // do nothing.. waiting on MovementInform
                break;
            case 3:
            {
                if (Creature* kolkar = me->SummonCreature(3275, -1158.43f, -2954.45f, 93.689f, 2.61691f))
                {
                    m_kolkarGUID = kolkar->GetGUID();
                    kolkar->GetMotionMaster()->MoveChase(me);
                }

                m_phase = 4;
                break;
            }
            case 4:
            {
                // do nothing.. waiting on KilledUnit kolkar 
                Creature* kolkar = ObjectAccessor::GetCreature(*me, m_kolkarGUID);
                if (kolkar && !kolkar->IsAlive())
                    m_phase = 5;

                break;
            }
            case 5:
            {
                Talk(2);
                if (Creature* kolkar = me->SummonCreature(3275, -1158.43f, -2954.45f, 93.689f, 2.61691f))
                {
                    m_kolkarGUID = kolkar->GetGUID();
                    kolkar->GetMotionMaster()->MoveChase(me);
                }
                m_phase = 6;
                m_timer = 3000;
                break;
            }               
            case 6:
            {
                if (Creature* kurak = me->SummonCreature(3275, -1158.43f, -2954.45f, 93.689f, 2.61691f))
                {
                    m_kurakGUID = kurak->GetGUID();
                    kurak->GetMotionMaster()->MoveChase(me);
                }

                Talk(3);
                m_phase = 7;
                break;
            }
            case 7:
            {
                // do nothing.. waiting on KilledUnit kurak    
                Creature* kurak = ObjectAccessor::GetCreature(*me, m_kurakGUID);
                Creature* kolkar = ObjectAccessor::GetCreature(*me, m_kolkarGUID);
                if (kurak && kolkar && !kurak->IsAlive() && !kolkar->IsAlive())
                    m_phase = 8;

                break;
            }
            case 8:
            {
                Talk(4);
                if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    player->KilledMonsterCredit(34635);

                m_phase = 9;
                m_timer = 5000;
                break;
            }
            case 9:
                Talk(6);
                m_phase = 10;
                m_timer = 5000;
                break;
            case 10:
                me->DespawnOrUnsummon();
                break;
            }
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
            m_kodoPackGUID = NULL;
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
            m_playerGUID = NULL;
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
            m_halgaGUID = NULL;
            m_playerGUID = NULL;
            m_gunnerGUID = NULL;
            m_balgorGUID = NULL;
            m_kodoPackGUID = NULL;
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
            m_kodoLeaderGUID = NULL;
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
            }
        }

        uint64 GetGUID(int32 id = 0) const 
        { 
            switch (id)
            {
                case 34430:
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
}
