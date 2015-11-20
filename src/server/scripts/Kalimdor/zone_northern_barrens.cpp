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
}