/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2014 ArkCORE <http://www.arkania.net/>
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
SDName: Westfall
SD%Complete: 90
SDComment: Quest support: 1651
SDCategory: Westfall
EndScriptData */

/* ContentData
npc_daphne_stilwell
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "Player.h"

// #############################################  quest 26209: Murder Was The Case That They Gave Me

enum eQuest26209
{
	NPC_INVESTIGATOR_42309 = 42309,
	NPC_HORATIO_LANE_42308 = 42308,
	NPC_WEST_PLAINS_DRIFTERS = 42391,
	NPC_HOMELESS_STORMWIND_CITZEN = 42386,
	NPC_TRANSIENT = 42383,
	NPC_RAGMUFFIN = 42413,
	NPC_WESTFALL_STEW_PROXY = 42625,
	NPC_FURLBROW_MURDER_INFO_001 = 42414,
	NPC_FURLBROW_MURDER_INFO_002 = 42415,
	NPC_FURLBROW_MURDER_INFO_003 = 42416,
	NPC_FURLBROW_MURDER_INFO_004 = 42417,
	NPC_VERNA_FURLBROW = 238,
	NPC_OLD_BLANCHY = 582,
	QUEST_HEROS_CALL_WESTFALL1 = 26378,
	QUEST_HEROS_CALL_WESTFALL2 = 28562,
	QUEST_MURDER_WAS_THE_CASE_THAT_THEY_GAVE_ME = 26209,
	QUEST_MEET_TWO_SHOED_LOE = 26215,
	SPELL_DETECT_QUEST_INVIS_0 = 79489,
	SPELL_DETECT_QUEST_INVIS_1 = 79229,
	SPELL_DETECT_QUEST_INVIS_2 = 79341,
	SPELL_DETECT_QUEST_INVIS_3 = 79498,
	SPELL_COSMETIC_SLEEP_ZZZ = 78677,
};

class npc_horatio_lane_42308 : public CreatureScript
{
public:
	npc_horatio_lane_42308() : CreatureScript("npc_horatio_lane_42308") { }

	struct npc_horatio_lane_42308AI : public ScriptedAI
	{
		npc_horatio_lane_42308AI(Creature* creature) : ScriptedAI(creature)
		{
			m_homePosition = Position(-9850.017578f, 916.479980f, 30.302572f, 0.0f);
			m_investigationPosition = Position(-9852.655273f, 910.777222f, 29.948130f, 0.0f);
		}

		uint32  m_timer;
		uint32  m_phase;
		uint32  m_cooldown;
		Position m_homePosition, m_investigationPosition;

		void Reset() override
		{
			m_timer = 1000; m_phase = 0; m_cooldown = 0;
			me->SetWalk(true);
			me->GetMotionMaster()->MovePoint(0, m_homePosition);
			me->SetFacingTo(3.95f);
		}

		void MoveInLineOfSight(Unit* who) override
		{
			if (Player* player = who->ToPlayer())
				if (player->HasAura(SPELL_DETECT_QUEST_INVIS_0))
					if (me->GetDistance2d(player) < 5 && m_phase == 0)
					{
						m_phase = 1; m_timer = 2000; m_cooldown = 180000;
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

			if (m_cooldown > 0)
			{
				if (m_cooldown <= diff)
				{
					m_phase = 8; m_timer = 1000; m_cooldown = 0;
				}
				else
					m_cooldown -= diff;
			}

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
				if (Creature* npc = me->FindNearestCreature(NPC_VERNA_FURLBROW, 15.0f))
					if (Creature* invest = npc->FindNearestCreature(NPC_INVESTIGATOR_42309, 3.0f))
						invest->AI()->Talk(0);

				m_phase = 2; m_timer = 5000;
				break;
			case 2:
				if (Creature* npc = me->FindNearestCreature(NPC_VERNA_FURLBROW, 15.0f))
					if (Creature* invest = npc->FindNearestCreature(NPC_INVESTIGATOR_42309, 3.0f))
						invest->AI()->Talk(1);

				m_phase = 3; m_timer = 5000;
				break;
			case 3:
				if (Creature* horse = me->FindNearestCreature(NPC_OLD_BLANCHY, 15.0f))
					if (Creature* invest = horse->FindNearestCreature(NPC_INVESTIGATOR_42309, 3.0f))
						invest->AI()->Talk(2);

				m_phase = 4; m_timer = 7000;
				break;
			case 4:
				Talk(0);
				me->GetMotionMaster()->MovePoint(0, m_investigationPosition);
				m_phase = 5; m_timer = 5000;
				break;
			case 5:
				Talk(1);
				me->SetFacingTo(5.083f);
				me->HandleEmoteCommand(EMOTE_ONESHOT_KNEEL);
				m_phase = 6; m_timer = 5000;
				break;
			case 6:
				Talk(2);
				m_phase = 7; m_timer = 5000;
				break;
			case 7:
				m_phase = 8; m_timer = 5000;
				break;
			case 8:
				me->GetMotionMaster()->MovePoint(0, m_homePosition);
				m_phase = 9; m_timer = 3000;
				break;
			case 9:
				me->HandleEmoteCommand(EMOTE_STATE_STAND);
				me->SetFacingTo(3.95f);
				m_phase = 10; m_timer = 60000;
				break;
			case 10:
				m_phase = 0; m_timer = 0; m_cooldown = 0;
				break;
			}
		}
	};

	CreatureAI* GetAI(Creature* creature) const override
	{
		return new npc_horatio_lane_42308AI(creature);
	}
};

class npc_west_plains_drifters : public CreatureScript
{
public:
	npc_west_plains_drifters() : CreatureScript("npc_west_plains_drifters") { }

	bool OnGossipHello(Player* player, Creature* creature) override
	{
		if (!creature->IsInCombat())
			if (player->GetQuestStatus(QUEST_MURDER_WAS_THE_CASE_THAT_THEY_GAVE_ME) == QUEST_STATUS_INCOMPLETE)
			{
				player->ADD_GOSSIP_ITEM_DB(87, 0, GOSSIP_SENDER_MAIN, 1001);
				player->ADD_GOSSIP_ITEM_DB(87, 1, GOSSIP_SENDER_MAIN, 1002);
				player->SEND_GOSSIP_MENU(urand(70, 74), creature->GetGUID());
			}
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
	{
		switch (action)
		{
		case 1001:
			creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
			creature->Attack(player, true);
			player->Attack(creature, true);
			creature->AI()->Talk(0);
			break;
		case 1002:
			if (urand(0, 1) == 0)
			{
				creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
				creature->Attack(player, true);
				player->Attack(creature, true);
				creature->AI()->Talk(0);
				break;
			}
			uint32 a1 = player->GetReqKillOrCastCurrentCount(QUEST_MURDER_WAS_THE_CASE_THAT_THEY_GAVE_ME, 42414);
			uint32 a2 = player->GetReqKillOrCastCurrentCount(QUEST_MURDER_WAS_THE_CASE_THAT_THEY_GAVE_ME, 42415);
			uint32 a3 = player->GetReqKillOrCastCurrentCount(QUEST_MURDER_WAS_THE_CASE_THAT_THEY_GAVE_ME, 42416);
			uint32 a4 = player->GetReqKillOrCastCurrentCount(QUEST_MURDER_WAS_THE_CASE_THAT_THEY_GAVE_ME, 42417);
			if (a1 == 0)
			{
				player->KilledMonsterCredit(42414);
				creature->AI()->Talk(1);
			}
			else if (a2 == 0)
			{
				player->KilledMonsterCredit(42415);
				creature->AI()->Talk(2);
			}
			else if (a3 == 0)
			{
				player->KilledMonsterCredit(42416);
				creature->AI()->Talk(3);
			}
			else if (a4 == 0)
			{
				player->KilledMonsterCredit(42417);
				creature->AI()->Talk(4);
			}
			creature->GetMotionMaster()->MoveRandom(10);
			break;
		}
		player->CLOSE_GOSSIP_MENU();

		return true;
	}

	struct npc_west_plains_driftersAI : public ScriptedAI
	{
		npc_west_plains_driftersAI(Creature *c) : ScriptedAI(c) { }

		void JustDied(Unit* killer) override
		{
			Position pos = me->GetNearPosition(1.5f, 0);
			me->SummonCreature(NPC_RAGMUFFIN, pos, TEMPSUMMON_TIMED_DESPAWN, 20000);
			pos = me->GetNearPosition(1.5f, 2);
			me->SummonCreature(NPC_RAGMUFFIN, pos, TEMPSUMMON_TIMED_DESPAWN, 20000);
			pos = me->GetNearPosition(1.5f, 4);
			me->SummonCreature(NPC_RAGMUFFIN, pos, TEMPSUMMON_TIMED_DESPAWN, 20000);
		}

		void UpdateAI(uint32 diff) override
		{
			if (!UpdateVictim())
				return;

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_west_plains_driftersAI(creature);
	}
};

class npc_transient : public CreatureScript
{
public:
	npc_transient() : CreatureScript("npc_transient") { }

	bool OnGossipHello(Player* player, Creature* creature) override
	{
		if (!creature->IsInCombat())
			if (player->GetQuestStatus(QUEST_MURDER_WAS_THE_CASE_THAT_THEY_GAVE_ME) == QUEST_STATUS_INCOMPLETE)
			{
				player->ADD_GOSSIP_ITEM_DB(87, 0, GOSSIP_SENDER_MAIN, 1001);
				player->ADD_GOSSIP_ITEM_DB(87, 1, GOSSIP_SENDER_MAIN, 1002);
				player->SEND_GOSSIP_MENU(urand(70, 74), creature->GetGUID());
			}
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
	{
		switch (action)
		{
		case 1001:
			creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
			creature->Attack(player, true);
			player->Attack(creature, true);
			creature->AI()->Talk(0);
			break;
		case 1002:
			if (urand(0, 1) == 0)
			{
				creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
				creature->Attack(player, true);
				player->Attack(creature, true);
				creature->AI()->Talk(0);
				break;
			}
			uint32 a1 = player->GetReqKillOrCastCurrentCount(QUEST_MURDER_WAS_THE_CASE_THAT_THEY_GAVE_ME, 42414);
			uint32 a2 = player->GetReqKillOrCastCurrentCount(QUEST_MURDER_WAS_THE_CASE_THAT_THEY_GAVE_ME, 42415);
			uint32 a3 = player->GetReqKillOrCastCurrentCount(QUEST_MURDER_WAS_THE_CASE_THAT_THEY_GAVE_ME, 42416);
			uint32 a4 = player->GetReqKillOrCastCurrentCount(QUEST_MURDER_WAS_THE_CASE_THAT_THEY_GAVE_ME, 42417);
			if (a1 == 0)
			{
				player->KilledMonsterCredit(42414);
				creature->AI()->Talk(1);
			}
			else if (a2 == 0)
			{
				player->KilledMonsterCredit(42415);
				creature->AI()->Talk(2);
			}
			else if (a3 == 0)
			{
				player->KilledMonsterCredit(42416);
				creature->AI()->Talk(3);
			}
			else if (a4 == 0)
			{
				player->KilledMonsterCredit(42417);
				creature->AI()->Talk(4);
			}
			creature->GetMotionMaster()->MoveRandom(10);
			break;
		}
		player->CLOSE_GOSSIP_MENU();

		return true;
	}

	struct npc_transientAI : public ScriptedAI
	{
		npc_transientAI(Creature *c) : ScriptedAI(c) { }

		void JustDied(Unit* killer) override
		{
			Position pos = me->GetNearPosition(1.5f, 0);
			me->SummonCreature(NPC_RAGMUFFIN, pos, TEMPSUMMON_TIMED_DESPAWN, 20000);
			pos = me->GetNearPosition(1.5f, 2);
			me->SummonCreature(NPC_RAGMUFFIN, pos, TEMPSUMMON_TIMED_DESPAWN, 20000);
			pos = me->GetNearPosition(1.5f, 4);
			me->SummonCreature(NPC_RAGMUFFIN, pos, TEMPSUMMON_TIMED_DESPAWN, 20000);
		}

		void UpdateAI(uint32 diff) override
		{
			if (!UpdateVictim())
				return;

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_transientAI(creature);
	}
};

class npc_homeless_stormwind_citizen : public CreatureScript
{
public:
	npc_homeless_stormwind_citizen() : CreatureScript("npc_homeless_stormwind_citizen") { }

	bool OnGossipHello(Player* player, Creature* creature) override
	{
		if (!creature->HasAura(SPELL_COSMETIC_SLEEP_ZZZ))
			if (!creature->IsInCombat())
				if (player->GetQuestStatus(QUEST_MURDER_WAS_THE_CASE_THAT_THEY_GAVE_ME) == QUEST_STATUS_INCOMPLETE)
				{
					player->ADD_GOSSIP_ITEM_DB(87, 0, GOSSIP_SENDER_MAIN, 1001);
					player->ADD_GOSSIP_ITEM_DB(87, 1, GOSSIP_SENDER_MAIN, 1002);
					player->SEND_GOSSIP_MENU(urand(70, 74), creature->GetGUID());
				}

		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
	{
		switch (action)
		{
		case 1001:
			creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
			creature->Attack(player, true);
			player->Attack(creature, true);
			creature->AI()->Talk(0);
			break;
		case 1002:
			if (urand(0, 1) == 0)
			{
				creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
				creature->Attack(player, true);
				player->Attack(creature, true);
				creature->AI()->Talk(0);
				break;
			}
			uint32 a1 = player->GetReqKillOrCastCurrentCount(QUEST_MURDER_WAS_THE_CASE_THAT_THEY_GAVE_ME, 42414);
			uint32 a2 = player->GetReqKillOrCastCurrentCount(QUEST_MURDER_WAS_THE_CASE_THAT_THEY_GAVE_ME, 42415);
			uint32 a3 = player->GetReqKillOrCastCurrentCount(QUEST_MURDER_WAS_THE_CASE_THAT_THEY_GAVE_ME, 42416);
			uint32 a4 = player->GetReqKillOrCastCurrentCount(QUEST_MURDER_WAS_THE_CASE_THAT_THEY_GAVE_ME, 42417);
			if (a1 == 0)
			{
				player->KilledMonsterCredit(42414);
				creature->AI()->Talk(1);
			}
			else if (a2 == 0)
			{
				player->KilledMonsterCredit(42415);
				creature->AI()->Talk(2);
			}
			else if (a3 == 0)
			{
				player->KilledMonsterCredit(42416);
				creature->AI()->Talk(3);
			}
			else if (a4 == 0)
			{
				player->KilledMonsterCredit(42417);
				creature->AI()->Talk(4);
			}
			creature->GetMotionMaster()->MoveRandom(10);
			break;
		}

		player->CLOSE_GOSSIP_MENU();

		return true;
	}

	struct npc_homeless_stormwind_citizenAI : public ScriptedAI
	{
		npc_homeless_stormwind_citizenAI(Creature *c) : ScriptedAI(c) { }

		void JustDied(Unit* killer) override
		{
			Position pos = me->GetNearPosition(1.5f, 0);
			me->SummonCreature(NPC_RAGMUFFIN, pos, TEMPSUMMON_TIMED_DESPAWN, 20000);
			pos = me->GetNearPosition(1.5f, 2);
			me->SummonCreature(NPC_RAGMUFFIN, pos, TEMPSUMMON_TIMED_DESPAWN, 20000);
			pos = me->GetNearPosition(1.5f, 4);
			me->SummonCreature(NPC_RAGMUFFIN, pos, TEMPSUMMON_TIMED_DESPAWN, 20000);
		}

		void UpdateAI(uint32 diff) override
		{
			if (!UpdateVictim())
				return;

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_homeless_stormwind_citizenAI(creature);
	}
};

class npc_ragamuffin : public CreatureScript
{
public:
	npc_ragamuffin() : CreatureScript("npc_ragamuffin") { }

	struct npc_ragamuffinAI : public ScriptedAI
	{
		npc_ragamuffinAI(Creature *c) : ScriptedAI(c) { }

		uint32 m_timer;
		uint32 m_phase;
		Creature* npc;

		void Reset() override
		{
			me->GetMotionMaster()->MoveRandom(2.0f);
			m_timer = urand(2000, 8000); m_phase = 0; npc = NULL;
		}

		void IsSummonedBy(Unit* summoner) override
		{
			npc = summoner->ToCreature();
		}

		void UpdateAI(uint32 diff) override
		{
			if (m_timer <= diff)
			{
				m_phase++;
				m_timer = 1000;
				if (m_phase == 1)
					me->AI()->Talk(0, npc);
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
		return new npc_ragamuffinAI(creature);
	}
};

// #############################################  quest 26215 Meet Two-Shoed Lou

enum eQuest26215
{
	NPC_INVESTIGATOR_42559 = 42559,
	NPC_HORATIO_LANE_42558 = 42558,
	NPC_TWO_SHOED_LOU_ALIVE = 42405,
	NPC_TWO_SHOED_LOU_DEATH = 42560,
};

// #############################################  quest = 26228  Livin' the Life

enum eQuest26228
{
	NPC_GLUBTOK_THE_FOREMAN = 42492,
	NPC_SHADOWY_FIGURE = 42515,
	NPC_TWO_SHOED_LOUS_OLD_HOUSE = 42500,
	QUEST_LIVIN_THE_LIFE = 26228,
	SPELL_SHROUD_OF_SHADOWS = 79192, // used by old script
	SPELL_VANISH_VISUAL = 24222, // used by old script
	SPELL_SUMMON_GLUBTOK = 79263,
	SPELL_SUMMON_SHADOWY_FIGURE = 79265,
	SPELL_SUMMON_LOUS_HOUSE = 79262,
};

class npc_lues_old_house : public CreatureScript
{
public:
	npc_lues_old_house() : CreatureScript("npc_lues_old_house") { }

	struct npc_lues_old_houseAI : public ScriptedAI
	{
		npc_lues_old_houseAI(Creature *c) : ScriptedAI(c) { }

		uint32 _timer;
		uint32 _phase;

		void Reset() override
		{
			_timer = 0;
			_phase = 0;
		}

		void IsSummonedBy(Unit* summoner) override
		{
			if (Player* player = summoner->ToPlayer())
			{
				player->CastSpell(player, SPELL_SUMMON_GLUBTOK);
				player->CastSpell(player, SPELL_SUMMON_SHADOWY_FIGURE);
				_phase = 1; _timer = 1000;
			}
		}

		void UpdateAI(uint32 diff) override
		{
			if (_timer <= diff)
			{
				_timer = 1000;
				DoWork();
			}
			else
				_timer -= diff;

			if (!UpdateVictim())
				return;

			DoMeleeAttackIfReady();
		}

		void DoWork()
		{
			if (_phase == 1)
			{
				if (Creature* grubtok = me->FindNearestCreature(NPC_GLUBTOK_THE_FOREMAN, 40.0f))
					return;
				else
					me->DespawnOrUnsummon();
			}
		}
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_lues_old_houseAI(creature);
	}
};

class npc_shadowy_figure : public CreatureScript
{
public:
	npc_shadowy_figure() : CreatureScript("npc_shadowy_figure") { }

	struct npc_shadowy_figureAI : public ScriptedAI
	{
		npc_shadowy_figureAI(Creature *c) : ScriptedAI(c) { }

		uint32		_timer;
		uint32		_phase;
		Player*		_player;

		void Reset() override
		{
			_timer = 0;
			_phase = 0;
			_player = NULL;
		}

		void IsSummonedBy(Unit* summoner) override
		{
			if (Player* player = summoner->ToPlayer())
			{
				_player = player;
				_timer = 1000;
				_phase = 1;
			}
		}

		void UpdateAI(uint32 diff) override
		{
			if (_timer <= diff)
			{
				_timer = 1000;
				DoWork();
			}
			else
				_timer -= diff;

			if (!UpdateVictim())
				return;

			DoMeleeAttackIfReady();
		}

		void DoWork()
		{
			Creature* _glubtok = me->FindNearestCreature(NPC_GLUBTOK_THE_FOREMAN, 40.0f, true);

			if (!_glubtok)
				return;

			switch (_phase)
			{
			case 1:
				_phase++; _timer = 7000;
				me->SetWalk(true);
				me->GetMotionMaster()->MovePoint(0, -9841.677f, 1400.042f, 37.129f);
				break;
			case 2:
				_phase++; _timer = 5000;
				_glubtok->AI()->Talk(0);
				break;
			case 3:
				_phase++; _timer = 8500;
				me->AI()->Talk(0);
				break;
			case 4:
				_phase++; _timer = 4000;
				_glubtok->AI()->Talk(1);
				break;
			case 5:
				_phase++; _timer = 6500;
				me->AI()->Talk(1);
				break;
			case 6:
				_phase++; _timer = 6500;
				me->AI()->Talk(2);
				break;
			case 7:
				_phase++; _timer = 4000;
				_glubtok->AI()->Talk(2);
				break;
			case 8:
				_phase++; _timer = 7000;
				me->AI()->Talk(3);
				break;
			case 9:
				_phase++; _timer = 7000;
				_glubtok->AI()->Talk(3);
				break;
			case 10:
				_phase++; _timer = 6000;
				_glubtok->AI()->Talk(4);
				break;
			case 11:
				_phase++; _timer = 6000;
				me->AI()->Talk(4);
				break;
			case 12:
				_phase++; _timer = 6000;
				me->AI()->Talk(5);
				break;
			case 13:
				_phase++; _timer = 2000;
				if (_player && _player->IsAlive())
				{
					_player->KilledMonsterCredit(NPC_GLUBTOK_THE_FOREMAN);
					_player->CompleteQuest(QUEST_LIVIN_THE_LIFE);
				}
				me->DespawnOrUnsummon(1000);
				_glubtok->DespawnOrUnsummon(1000);
				break;
			case 14:
				_phase = 0; _timer = 0;
				if (_player && _player->IsAlive())
				{
					_player->ExitVehicle();
				}
				break;
			}
		}
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_shadowy_figureAI(creature);
	}
};

// #############################################  quest = 26232  Lou's Parting Thoughts

enum eQuest26232
{
	NPC_THUG = 42387,
	NPC_JIMB = 42498,
	NPC_HOMELESS_STORMWIND_CITZEN_42384 = 42384,
	QUEST_LOUS_PARTING_THOUGHTS = 26232,
	SOUND_WOMAN_SCREAM = 17852,
};

class npc_thug : public CreatureScript
{
public:
	npc_thug() : CreatureScript("npc_thug") { }

	struct npc_thugAI : public ScriptedAI
	{
		npc_thugAI(Creature *c) : ScriptedAI(c) { }

		uint32      m_timer;
		uint32      m_event;
		uint32      m_phase;
		Player*     m_player;
		Creature*   m_thug1;
		Creature*   m_thug2;
		Creature*   m_thug3;

		void Reset() override
		{
			m_timer = 0; m_phase = 0; m_event = 1000;
			m_player = NULL; m_thug1 = NULL; m_thug2 = NULL; m_thug3 = NULL;
		}

		void JustDied(Unit* killer)
		{
			if (!m_player)
				return;

			if (m_phase > 8)
			{
				m_player->KilledMonsterCredit(NPC_FURLBROW_MURDER_INFO_004);
				//m_player->RemoveAura(SPELL_DETECT_QUEST_INVIS_0);
				//m_player->RemoveAura(SPELL_DETECT_QUEST_INVIS_1);
				//m_player->AddAura(SPELL_DETECT_QUEST_INVIS_2, m_player);
				m_player->PlayDistanceSound(SOUND_WOMAN_SCREAM);
			}
		}

		void UpdateAI(uint32 diff) override
		{
			if (m_event <= diff)
			{
				m_event = 1000;
				if (m_phase == 0 && !me->IsInCombat())
					if (Player* player = me->FindNearestPlayer(8))
						if (player->GetQuestStatus(QUEST_LOUS_PARTING_THOUGHTS) == QUEST_STATUS_INCOMPLETE)
							if (HaveHighestGuid())
							{
								m_phase = 1; m_timer = 1000; m_player = player;
							}
			}
			else
				m_event -= diff;

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
			case 1:
				m_phase++; m_timer = 7000;
				m_thug1->AI()->Talk(0);
				break;
			case 2:
				m_phase++; m_timer = 5000;
				m_thug2->AI()->Talk(1);
				break;
			case 3:
				m_phase++; m_timer = 8000;
				m_thug2->AI()->Talk(2);
				break;
			case 4:
				m_phase++; m_timer = 8000;
				m_thug3->AI()->Talk(3);
				break;
			case 5:
				m_phase++; m_timer = 5000;
				m_thug1->AI()->Talk(4);
				break;
			case 6:
				m_phase++; m_timer = 3000;
				m_thug1->AI()->Talk(5);
				break;
			case 7:
				m_phase++; m_timer = 3000;
				m_thug1->AI()->Talk(6);
				break;
			case 8:
				m_phase++; m_timer = 0;
				me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
				m_thug1->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
				m_thug2->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
				m_thug3->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
				m_player->Attack(me, true);
				me->Attack(m_player, true);
				m_thug1->Attack(m_player, true);
				m_thug2->Attack(m_player, true);
				m_thug3->Attack(m_player, true);
				break;
			}
		}

		bool HaveHighestGuid()
		{
			std::list<Creature*> list;
			me->GetCreatureListWithEntryInGrid(list, NPC_THUG, 15.0f);

			if (list.empty())
				return false;

			if (list.size() != 4)
				return false;

			Creature* target = NULL;
			uint32 tmpGuid = 0;
			for (std::list<Creature*>::iterator itr = list.begin(); itr != list.end(); ++itr)
			{
				target = *itr;
				if (target->GetGUIDLow() > tmpGuid)
					tmpGuid = target->GetGUIDLow();
			}

			uint8 i = 0;
			for (std::list<Creature*>::iterator itr = list.begin(); itr != list.end(); ++itr)
			{
				target = *itr;
				if (target->GetGUIDLow() != tmpGuid)
				{
					i++;
					switch (i)
					{
					case 1:
						m_thug1 = target;
						break;
					case 2:
						m_thug2 = target;
						break;
					case 3:
						m_thug3 = target;
						break;
					}
				}
			}

			if (me->GetGUIDLow() == tmpGuid)
				return true;

			return false;
		}

	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_thugAI(creature);
	}
};

class npc_horatio_lane_42558 : public CreatureScript
{
public:
	npc_horatio_lane_42558() : CreatureScript("npc_horatio_lane_42558") { }

	struct npc_horatio_lane_42558AI : public ScriptedAI
	{
		npc_horatio_lane_42558AI(Creature* creature) : ScriptedAI(creature) { }

		uint32  m_timer;
		uint32  m_phase;
		uint32  m_cooldown;
		Player* m_player;

		void Reset() override
		{
			m_timer = 0; m_phase = 0; m_cooldown = 0;
			m_player = NULL;
		}

		void MoveInLineOfSight(Unit* who) override
		{
			if (Player* player = who->ToPlayer())
				if (m_phase == 0)
					if (player->GetQuestStatus(QUEST_LOUS_PARTING_THOUGHTS) == QUEST_STATUS_COMPLETE)
						if (player->HasAura(SPELL_DETECT_QUEST_INVIS_2))
							if (me->GetDistance2d(player) < 15)
							{
								m_phase = 1; m_timer = 1000; m_cooldown = 180000;
								m_player = player;
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

			if (m_cooldown > 0)
			{
				if (m_cooldown <= diff)
				{
					Reset();
				}
				else
					m_cooldown -= diff;
			}

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
				m_phase++; m_timer = 6000;
				if (Creature* jimb = me->FindNearestCreature(NPC_JIMB, 10))
					if (Creature* invest = jimb->FindNearestCreature(NPC_INVESTIGATOR_42559, 10))
						invest->AI()->Talk(0);
				break;
			case 2:
				m_phase++; m_timer = 6000;
				if (Creature* jimb = me->FindNearestCreature(NPC_JIMB, 10))
					if (Creature* invest = jimb->FindNearestCreature(NPC_INVESTIGATOR_42559, 10))
						if (Creature* homeless = invest->FindNearestCreature(NPC_HOMELESS_STORMWIND_CITZEN_42384, 10))
							homeless->AI()->Talk(0);
				break;
			case 3:
				m_phase++; m_timer = 6000;
				if (Creature* jimb = me->FindNearestCreature(NPC_JIMB, 10))
					if (Creature* invest = jimb->FindNearestCreature(NPC_INVESTIGATOR_42559, 10))
						invest->AI()->Talk(1);
				break;
			case 4:
				m_phase++; m_timer = 6000;
				Talk(0);
				break;
			case 5:
				m_phase++; m_timer = 6000;
				Talk(1);
				break;
			case 6:
				m_phase++; m_timer = 6000;
				Talk(2);
				break;
			case 7:
				m_phase++; m_timer = 6000;
				Talk(3);
				break;
			case 8:
				m_phase++; m_timer = 6000;
				Talk(4);
				break;
			case 9:
				Reset();
				break;
			}
		}
	};

	CreatureAI* GetAI(Creature* creature) const override
	{
		return new npc_horatio_lane_42558AI(creature);
	}
};

// #############################################  quest = 26236  Shakedown at the Saldean's

enum eQuest26236
{
	NPC_FARMER_SALDEAN = 233,
	QUEST_SHAKEDOWN_AT_THE_SALDEANS = 26236,
};

// #############################################  

// ToDo: is not checked:  npc_daphne_stilwell

enum DaphneStilwell
{
	SAY_DS_START = 0,
	SAY_DS_DOWN_1 = 1,
	SAY_DS_DOWN_2 = 2,
	SAY_DS_DOWN_3 = 3,
	SAY_DS_PROLOGUE = 4,

	SPELL_SHOOT = 6660,
	QUEST_TOME_VALOR = 1651,
	NPC_DEFIAS_RAIDER = 6180,
	EQUIP_ID_RIFLE = 2511
};

class npc_daphne_stilwell : public CreatureScript
{
public:
	npc_daphne_stilwell() : CreatureScript("npc_daphne_stilwell") { }

	bool OnQuestAccept(Player* player, Creature* creature, const Quest* quest) OVERRIDE
	{
		if (quest->GetQuestId() == QUEST_TOME_VALOR)
		{
			creature->AI()->Talk(SAY_DS_START);

			if (npc_escortAI* pEscortAI = CAST_AI(npc_daphne_stilwell::npc_daphne_stilwellAI, creature->AI()))
				pEscortAI->Start(true, true, player->GetGUID());
		}

		return true;
	}

		CreatureAI* GetAI(Creature* creature) const OVERRIDE
	{
		return new npc_daphne_stilwellAI(creature);
	}

	struct npc_daphne_stilwellAI : public npc_escortAI
	{
		npc_daphne_stilwellAI(Creature* creature) : npc_escortAI(creature) { }

		uint32 uiWPHolder;
		uint32 uiShootTimer;

		void Reset() OVERRIDE
		{
			if (HasEscortState(STATE_ESCORT_ESCORTING))
			{
				switch (uiWPHolder)
				{
				case 7:
					Talk(SAY_DS_DOWN_1);
					break;
				case 8:
					Talk(SAY_DS_DOWN_2);
					break;
				case 9:
					Talk(SAY_DS_DOWN_3);
					break;
				}
			}
			else
				uiWPHolder = 0;

			uiShootTimer = 0;
		}

			void WaypointReached(uint32 waypointId) OVERRIDE
		{
			Player* player = GetPlayerForEscort();
			if (!player)
				return;

			uiWPHolder = waypointId;

			switch (waypointId)
			{
			case 4:
				SetEquipmentSlots(false, EQUIP_NO_CHANGE, EQUIP_NO_CHANGE, EQUIP_ID_RIFLE);
				me->SetSheath(SHEATH_STATE_RANGED);
				me->HandleEmoteCommand(EMOTE_STATE_USE_STANDING_NO_SHEATHE);
				break;
			case 7:
				me->SummonCreature(NPC_DEFIAS_RAIDER, -11450.836f, 1569.755f, 54.267f, 4.230f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
				me->SummonCreature(NPC_DEFIAS_RAIDER, -11449.697f, 1569.124f, 54.421f, 4.206f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
				me->SummonCreature(NPC_DEFIAS_RAIDER, -11448.237f, 1568.307f, 54.620f, 4.206f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
				break;
			case 8:
				me->SetSheath(SHEATH_STATE_RANGED);
				me->SummonCreature(NPC_DEFIAS_RAIDER, -11450.836f, 1569.755f, 54.267f, 4.230f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
				me->SummonCreature(NPC_DEFIAS_RAIDER, -11449.697f, 1569.124f, 54.421f, 4.206f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
				me->SummonCreature(NPC_DEFIAS_RAIDER, -11448.237f, 1568.307f, 54.620f, 4.206f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
				me->SummonCreature(NPC_DEFIAS_RAIDER, -11448.037f, 1570.213f, 54.961f, 4.283f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
				break;
			case 9:
				me->SetSheath(SHEATH_STATE_RANGED);
				me->SummonCreature(NPC_DEFIAS_RAIDER, -11450.836f, 1569.755f, 54.267f, 4.230f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
				me->SummonCreature(NPC_DEFIAS_RAIDER, -11449.697f, 1569.124f, 54.421f, 4.206f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
				me->SummonCreature(NPC_DEFIAS_RAIDER, -11448.237f, 1568.307f, 54.620f, 4.206f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
				me->SummonCreature(NPC_DEFIAS_RAIDER, -11448.037f, 1570.213f, 54.961f, 4.283f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
				me->SummonCreature(NPC_DEFIAS_RAIDER, -11449.018f, 1570.738f, 54.828f, 4.220f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
				break;
			case 10:
				SetRun(false);
				break;
			case 11:
				Talk(SAY_DS_PROLOGUE);
				break;
			case 13:
				SetEquipmentSlots(true);
				me->SetSheath(SHEATH_STATE_UNARMED);
				me->HandleEmoteCommand(EMOTE_STATE_USE_STANDING_NO_SHEATHE);
				break;
			case 17:
				player->GroupEventHappens(QUEST_TOME_VALOR, me);
				break;
			}
		}

			void AttackStart(Unit* who) OVERRIDE
		{
			if (!who)
			return;

			if (me->Attack(who, false))
			{
				me->AddThreat(who, 0.0f);
				me->SetInCombatWith(who);
				who->SetInCombatWith(me);

				me->GetMotionMaster()->MoveChase(who, 30.0f);
			}
		}

			void JustSummoned(Creature* summoned) OVERRIDE
		{
			summoned->AI()->AttackStart(me);
		}

			void Update(const uint32 diff)
		{
			npc_escortAI::UpdateAI(diff);

			if (!UpdateVictim())
				return;

			if (uiShootTimer <= diff)
			{
				uiShootTimer = 1500;

				if (!me->IsWithinDist(me->GetVictim(), ATTACK_DISTANCE))
					DoCastVictim(SPELL_SHOOT);
			}
			else uiShootTimer -= diff;
		}
	};
};


void AddSC_westfall()
{
    new npc_daphne_stilwell();
	new npc_horatio_lane_42308();
	new npc_west_plains_drifters();
	new npc_transient();
	new npc_homeless_stormwind_citizen();
	new npc_ragamuffin();
	new npc_lues_old_house();
	new npc_shadowy_figure();
	new npc_thug();
	new npc_horatio_lane_42558();

}
