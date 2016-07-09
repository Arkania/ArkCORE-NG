/*
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

#include "ScriptPCH.h"
#include "Unit.h"
#include "ScriptedEscortAI.h"
#include "ScriptedFollowerAI.h"
#include "Vehicle.h"
#include "GameObjectAI.h"
#include "CreatureGroups.h"

 // 38553
class npc_krennan_aranas_38553 : public CreatureScript
{
public:
	npc_krennan_aranas_38553() : CreatureScript("npc_krennan_aranas_38553") { }

	enum eNpc
	{
		QUEST_PUSH_THEM_OUT = 24676,
		QUEST_THE_BATTLE_FOR_GILNEAS_CITY = 24904,
		NPC_PRINCE_LIAM_GREYMANE_BATTLE = 38218,
		ACTION_START_EVENT = 101,
		EVENT_BATTLE_IS_STARTED=102,
		EVENT_CHECK_PLAYER_FOR_PHASE = 103,
	};

	bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
	{
		player->PlayerTalkClass->ClearMenus();
		switch (uiAction)
		{
		case GOSSIP_ACTION_INFO_DEF + 1:
		{
			player->CLOSE_GOSSIP_MENU();
			CAST_AI(npc_krennan_aranas_38553::npc_krennan_aranas_38553AI, creature->AI())->StartBattle(player);
			break;
		}
		case GOSSIP_ACTION_INFO_DEF + 2:
		{
			player->CLOSE_GOSSIP_MENU();
			break;
		}
		}
		return true;
	}

	bool OnGossipHello(Player* player, Creature* creature)
	{
		if (creature->IsQuestGiver())
			player->PrepareQuestMenu(creature->GetGUID());

		if (player->GetQuestStatus(QUEST_THE_BATTLE_FOR_GILNEAS_CITY) == QUEST_STATUS_INCOMPLETE)
			if (Creature* liam = creature->FindNearestCreature(NPC_PRINCE_LIAM_GREYMANE_BATTLE, 50.0f))
				player->ADD_GOSSIP_ITEM_DB(11061, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
			else
				player->ADD_GOSSIP_ITEM_DB(11061, 1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

		player->SEND_GOSSIP_MENU(2474, creature->GetGUID());

		return true;
	}

	struct npc_krennan_aranas_38553AI : public ScriptedAI
	{
		npc_krennan_aranas_38553AI(Creature *c) : ScriptedAI(c) {}

		EventMap m_events;
		uint64   m_princeGUID;
		bool	 m_battleIsStarted;

		void Reset()
		{
			m_events.Reset();
			m_events.ScheduleEvent(EVENT_CHECK_PLAYER_FOR_PHASE, 2500);
			m_princeGUID = 0;
			m_battleIsStarted = false;
		}

		void StartBattle(Player* player)
		{
			if (!m_princeGUID)
				if (Creature* prince = me->FindNearestCreature(NPC_PRINCE_LIAM_GREYMANE_BATTLE, 50.0f))
					m_princeGUID = prince->GetGUID();

			if (Creature* prince = ObjectAccessor::GetCreature(*me, m_princeGUID))
				if (prince->IsAlive())
					if (m_battleIsStarted || me->GetDistance2d(prince->GetPositionX(), prince->GetPositionY()) > 50)
						Talk(1);
					else
					{
						m_battleIsStarted = true;
						m_events.ScheduleEvent(EVENT_BATTLE_IS_STARTED, 180000);
						prince->AI()->DoAction(ACTION_START_EVENT);
						Talk(0, player);
					}
		}

		void UpdateAI(uint32 diff) override
		{
			m_events.Update(diff);

			while (uint32 eventId = m_events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_BATTLE_IS_STARTED:
				{
					m_battleIsStarted = false;
					break;
				}
				case EVENT_CHECK_PLAYER_FOR_PHASE:
				{
					std::list<Player*> playerList = me->FindNearestPlayers(200.0f, true);
					for (std::list<Player*>::const_iterator itr = playerList.begin(); itr != playerList.end(); ++itr)
						if ((*itr)->GetQuestStatus(QUEST_PUSH_THEM_OUT) == QUEST_STATUS_REWARDED)
							if ((*itr)->GetPhaseMask() != 262144)
								(*itr)->SetPhaseMask(262144, true);

					m_events.ScheduleEvent(EVENT_CHECK_PLAYER_FOR_PHASE, 2500);
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

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_krennan_aranas_38553AI(pCreature);
	}
};

// 37803
class npc_marcus_37803 : public CreatureScript
{
public:
	npc_marcus_37803() : CreatureScript("npc_marcus_37803") { }

	enum eNPC
	{
		EVENTS_SAY_TEXT = 101,
	};

	struct npc_marcus_37803AI : public ScriptedAI
	{
		npc_marcus_37803AI(Creature* creature) : ScriptedAI(creature) { }

		EventMap m_events;

		void Reset() override
		{
			m_events.Reset();
			m_events.ScheduleEvent(EVENTS_SAY_TEXT, 60000);
		}

		void UpdateAI(uint32 diff) override
		{
			m_events.Update(diff);

			while (uint32 eventId = m_events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENTS_SAY_TEXT:
				{
					Talk(urand(0, 1));
					m_events.ScheduleEvent(EVENTS_SAY_TEXT, urand(50000, 120000));
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
		return new npc_marcus_37803AI(creature);
	}
};

// 38218 group mid
class npc_prince_liam_greymane_38218 : public CreatureScript
{
public:
	npc_prince_liam_greymane_38218() : CreatureScript("npc_prince_liam_greymane_38218") { }

	enum eNPC
	{
		QUEST_PUSH_THEM_OUT = 24676,
		ACTION_START_EVENT = 101,
		EVENT_CHECK_PLAYER_FOR_PHASE = 101,
		EVENT_GLOBAL_RESET = 102,
		EVENT_START_FIRST_EVENT = 103,
	};

	struct npc_prince_liam_greymane_38218AI : public ScriptedAI
	{
		npc_prince_liam_greymane_38218AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

		EventMap m_events;
		bool     m_event_is_started;

		void Initialize()
		{
			m_events.Reset();
			m_events.ScheduleEvent(EVENT_CHECK_PLAYER_FOR_PHASE, 2500);
			m_event_is_started=false;
		}

		void Reset() override
		{
			if (!me->HasAura(458))
				me->AddAura(458, me);
			if (!me->HasAura(72069))
				me->AddAura(72069, me);
		}

		void DoAction(int32 param) override
		{
			if (param == ACTION_START_EVENT && !m_event_is_started)
			{
				m_event_is_started = true;
				m_events.ScheduleEvent(EVENT_GLOBAL_RESET, 180000);
				m_events.ScheduleEvent(EVENT_START_FIRST_EVENT , 1000);
			}
		}

		void EnterEvadeMode() override { }

		void UpdateAI(uint32 diff) override
		{
			m_events.Update(diff);

			while (uint32 eventId = m_events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_CHECK_PLAYER_FOR_PHASE:
				{
					std::list<Player*> playerList = me->FindNearestPlayers(200.0f, true);
					for (std::list<Player*>::const_iterator itr = playerList.begin(); itr != playerList.end(); ++itr)
						if ((*itr)->GetQuestStatus(QUEST_PUSH_THEM_OUT) == QUEST_STATUS_REWARDED)
							if ((*itr)->GetPhaseMask() != 262144)
								(*itr)->SetPhaseMask(262144, true);

					m_events.ScheduleEvent(EVENT_CHECK_PLAYER_FOR_PHASE, 2500);
					break;
				}
				case EVENT_GLOBAL_RESET:
				{
					m_event_is_started = false;
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
		return new npc_prince_liam_greymane_38218AI(creature);
	}
};

// 38465 group right
class npc_myriam_spellwaker_38465 : public CreatureScript
{
public:
	npc_myriam_spellwaker_38465() : CreatureScript("npc_myriam_spellwaker_38465") { }

	enum eNPC
	{
		
	};

	struct npc_myriam_spellwaker_38465AI : public ScriptedAI
	{
		npc_myriam_spellwaker_38465AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

		EventMap m_events;

		void Initialize()
		{
			m_events.Reset();
		}

		void Reset() override
		{
		}

		void DoAction(int32 param) override
		{
		}

		void EnterEvadeMode() override { }

		void UpdateAI(uint32 diff) override
		{
			m_events.Update(diff);

			while (uint32 eventId = m_events.ExecuteEvent())
			{
				switch (eventId)
				{
				case 1:
				{
					
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
		return new npc_myriam_spellwaker_38465AI(creature);
	}
};

// 38466 group left
class npc_sister_almyra_38466 : public CreatureScript
{
public:
	npc_sister_almyra_38466() : CreatureScript("npc_sister_almyra_38466") { }

	enum eNPC
	{

	};

	struct npc_sister_almyra_38466AI : public ScriptedAI
	{
		npc_sister_almyra_38466AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

		EventMap m_events;

		void Initialize()
		{
			m_events.Reset();
		}

		void Reset() override
		{
		}

		void DoAction(int32 param) override
		{
		}

		void EnterEvadeMode() override { }

		void UpdateAI(uint32 diff) override
		{
			m_events.Update(diff);

			while (uint32 eventId = m_events.ExecuteEvent())
			{
				switch (eventId)
				{
				case 1:
				{

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
		return new npc_sister_almyra_38466AI(creature);
	}
};


// old contend

// 38221
class npc_gilnean_militia_38221 : public CreatureScript
{
public:
	npc_gilnean_militia_38221() : CreatureScript("npc_gilnean_militia_38221") { }

	enum eNpc
	{
		DATA_GROUP = 101,
		GROUP_1,
	};

	struct npc_gilnean_militia_38221AI : public ScriptedAI
	{
		npc_gilnean_militia_38221AI(Creature* pCreature) : ScriptedAI(pCreature) { }

		void Reset()
		{
			mui_spell1 = urand(1200, 5100);
			mui_spell2 = urand(2100, 5400);
			me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
		}

		void AttackStart(Unit* who)
		{
			if (me->Attack(who, true))
				DoStartNoMovement(who);
		}

		void SetData(uint32 uiType, uint32 uiData)
		{
			if (uiType == DATA_GROUP)
				group = uiData;
		}

		uint32 GetData(uint32 uiType) const
		{
			if (uiType == DATA_GROUP)
				return group;
			return 0;
		}

		void JustReachedHome()
		{
			if (group == GROUP_1)
				if (!UpdateVictim())
					if (me->ToTempSummon())
						if (Unit *p = me->ToTempSummon()->GetSummoner())
						{
							float distance = urand(7, 15);
							float angle = frand(-3 * M_PI / 4, 3 * M_PI / 2);
							float x, y, z;
							me->GetNearPoint(p, x, y, z, p->GetObjectSize(), distance, angle);
							me->GetMotionMaster()->MoveFollow(p, distance, angle, MOTION_SLOT_ACTIVE);
						}
		}

		void UpdateAI(uint32 diff)
		{
			if (!UpdateVictim())
				return;
			if (mui_spell1 <= diff)
			{
				// 15572 Rüstung zerreißen. Hackt auf die Rüstung des Gegners ein und verringert sie pro Einsatz von 'Rüstung zerreißen'. 
				// Kann bis zu 5-mal angewendet werden. Hält $d lang an.
				DoCastVictim(15572); 
				mui_spell1 = 10000 + urand(1200, 5100);
			}
			else
				mui_spell1 -= diff;

			if (mui_spell2 <= diff)
			{
				// 47168 Verbessertes Zurechtstutzen. Description: Macht das Ziel $d lang bewegungsunfähig.
				DoCastVictim(47168);
				mui_spell2 = 10000 + urand(2100, 5400);
			}
			else
				mui_spell2 -= diff;

			// 3te fähigkeit: 6660 Schießen.  Description: Schießt auf den Feind und fügt körperlichen Schaden zu
			victim = me->GetVictim();
			if (victim && me->GetDistance2d(victim->GetPositionX(), victim->GetPositionY()) > 7)
				DoSpellAttackIfReady(6660);
			else
				DoMeleeAttackIfReady();
		}

	private:
		uint32 mui_spell1;
		uint32 mui_spell2;
		Unit *victim;
		uint32 group;
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_gilnean_militia_38221AI(pCreature);
	}
};

// 38348
class npc_worgen_warrior_38348 : public CreatureScript
{
public:
	npc_worgen_warrior_38348() : CreatureScript("npc_worgen_warrior_38348") { }

	struct npc_worgen_warrior_38348AI : public ScriptedAI
	{
		npc_worgen_warrior_38348AI(Creature* pCreature) : ScriptedAI(pCreature) { }

		void EnterCombat(Unit* pWho)
		{
			if (pWho->GetEntry() == 38348)
			{
				me->CastSpell(pWho, 71921, true);
			}
		}

		void UpdateAI(uint32 diff)
		{
			if (!UpdateVictim())
				return;

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_worgen_warrior_38348AI(pCreature);
	}
};


void AddSC_zone_gilneas_city3()
{
	new npc_krennan_aranas_38553();
	new npc_marcus_37803();
	new npc_prince_liam_greymane_38218();
	new npc_myriam_spellwaker_38465();
	new npc_sister_almyra_38466();
	new npc_gilnean_militia_38221();
	new npc_worgen_warrior_38348();
}

