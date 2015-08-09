/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
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
SDName: Elwynn_Forest
SD%Complete: 50
SDComment: Quest support: 1786
SDCategory: Elwynn Forest
EndScriptData */

/* ContentData
    npc_henze_faulk entry=6172
    npc_stormwind_infantry
    npc_brother_paxton
    npc_blackrock_battle_worg
    npc_blackrock_spy
    npc_blackrock_invader
    npc_goblin_assassin
    npc_injured_soldier
    npc_injured_soldier_dummy
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "Player.h"

/*################################## showfight in startarea between blackrock_battle_worg and stormwind_infantry
#################################### class quest series 'Beating Them Back!'*/

enum eShowfight
{
    NPC_STORMWIND_INFANTRY = 49869,
    NPC_BLACKROCK_BATTLE_WORG = 49871,
    NPC_BROTHER_PAXTON = 951,
    SPELL_CONVERSATIONS_TRIGGER_01 = 84076,
    SPELL_REVIVE = 93799,
    SPELL_PRAYER_OF_HEALING = 93091,
	SPELL_FLASH_HEAL = 17843,
	SPELL_PENANCE = 47750,
	SPELL_FORTITUDE = 13864,

};

class npc_blackrock_battle_worg : public CreatureScript
{
public:
    npc_blackrock_battle_worg() : CreatureScript("npc_blackrock_battle_worg") { }

    struct npc_blackrock_battle_worgAI : public ScriptedAI
    {
        npc_blackrock_battle_worgAI(Creature *c) : ScriptedAI(c) { }

        uint32 m_minHealth;

        void Reset() override
        {
            m_minHealth = urand(60, 85);
        }

        void DamageTaken(Unit* hitter, uint32& uiDamage) override
        {
            if (Creature* npc = hitter->ToCreature())
                if (npc->GetEntry() == NPC_STORMWIND_INFANTRY && me->GetHealthPct() < m_minHealth)
                    uiDamage = 0;
        }

        void UpdateAI(uint32 diff) override
        {
            DoAttack();

            if (!UpdateVictim())
               return;

            DoMeleeAttackIfReady();
        }

        void DoAttack()
        {
            if (!me->IsInCombat())
                if (Creature* infantrist = me->FindNearestCreature(NPC_STORMWIND_INFANTRY, 7, true))
                {
                    me->Attack(infantrist, true);
                    if (!infantrist->IsInCombat())
                    {
                        infantrist->Attack(me, true);
                        DoStartMovement(infantrist->GetVictim());
                    }
                }
        }
    };

       CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_blackrock_battle_worgAI (creature);
    }
};

class npc_brother_paxton : public CreatureScript
{
public:
    npc_brother_paxton() : CreatureScript("npc_brother_paxton") { }

    struct npc_brother_paxtonAI : public ScriptedAI
    {
        npc_brother_paxtonAI(Creature *c) : ScriptedAI(c) { }

		uint32 _phase;
		uint32 _coolDown;
		float  _angle;

        void Reset() override
        {
            me->GetMotionMaster()->MovePath(951, true);
			_coolDown = 0;
			_phase = 0;
			_angle = 0;
        }

        void CastHeal(Creature* infantry)
        {   
			if (_phase == 0)
			{
				uint8 c = urand(0, 3);
				switch (c)
				{
				case  0:
					DoCast(infantry, SPELL_FORTITUDE);
					break;
				case  1:
					DoCast(infantry, SPELL_FLASH_HEAL);
					break;
				case  2:
					DoCast(infantry, SPELL_PENANCE);
					break;
				case  3:
					DoCast(infantry, SPELL_PRAYER_OF_HEALING);
					break;
				}
				_coolDown = 5000;
				_phase = 1;
			}
        }

        void UpdateAI(uint32 diff) override
        {
			if (_phase == 1)
				if (_coolDown <= diff)
				{
					_phase = 0;
				}
				else
					_coolDown -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
		}
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_brother_paxtonAI(creature);
    }
};

class npc_stormwind_infantry : public CreatureScript
{
public:
    npc_stormwind_infantry() : CreatureScript("npc_stormwind_infantry") { }

    struct npc_stormwind_infantryAI : public ScriptedAI
    {
        npc_stormwind_infantryAI(Creature *c) : ScriptedAI(c) { }

        uint32 m_SayWorgTimer;
        uint32 m_SayPaxtonCooldownTimer;
        uint32 m_minHealth;

        void Reset() override
        {
            m_SayWorgTimer = urand(30000, 60000);
            m_SayPaxtonCooldownTimer = 0;
            m_minHealth = urand(60, 85);
        }

        void DamageTaken(Unit* hitter, uint32& uiDamage) override
        {
            if (Creature* npc = hitter->ToCreature())
            {
                if (npc->GetEntry() == NPC_BLACKROCK_BATTLE_WORG && me->GetHealthPct() < m_minHealth)
					if (Creature* paxton = me->FindNearestCreature(NPC_BROTHER_PAXTON, 15.0f, true))
					{
						if (m_SayPaxtonCooldownTimer == 0)
						{
							Talk(1);

							if (npc_brother_paxton::npc_brother_paxtonAI* paxtonAI = CAST_AI(npc_brother_paxton::npc_brother_paxtonAI, paxton->AI()))
								paxtonAI->CastHeal(me);

							m_SayPaxtonCooldownTimer = 10000;
						}
					}
                    else
                        uiDamage = 0;

                if (!me->IsInCombat())
                {
                    me->Attack(npc, true);
                }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            DoWorg(diff);
            DoPaxton(diff);

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

        void DoWorg(uint32 diff)
        {
            if (m_SayWorgTimer <= diff)
            {
                if (me->IsInCombat() && me->FindNearestPlayer(15.0f, true))
                    Talk(0);

                m_SayWorgTimer = urand(30000, 60000);
            }
            else
                m_SayWorgTimer -= diff;
        }

        void DoPaxton(uint32 diff)
        {
            if (m_SayPaxtonCooldownTimer <= diff)
                m_SayPaxtonCooldownTimer = 0;
            else
                m_SayPaxtonCooldownTimer -= diff;
        }

    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_stormwind_infantryAI (creature);
    }
};

//######################################### class quest series 'Lions for Lambs'

enum eQuestSerieLfL
{
    SAY_BLACKROCK_COMBAT = 0,

	SPELL_SPYING = 92857,   // standing
    SPELL_SPYGLASS = 80676, // standing
    SPELL_SNEAKING = 93046, // walking		 
    NPC_BLACKROCK_SPY = 49874,
};

class npc_blackrock_spy : public CreatureScript
{
public:
    npc_blackrock_spy() : CreatureScript("npc_blackrock_spy") { }

    struct npc_blackrock_spyAI : public ScriptedAI
    {
		npc_blackrock_spyAI(Creature *c) : ScriptedAI(c) { }

        uint32 _phase;
        uint32 _timer;

		void Reset() override
		{
			_phase = 0;
			_timer = 0;
		}

        void EnterCombat(Unit* who) override
        { 
            Talk(SAY_BLACKROCK_COMBAT);
			me->RemoveAllAuras();
			_phase = 0;
			_timer = 0;
        }

		void MovementInform(uint32 type, uint32 id) override
		{
			if (me->IsInCombat())
				return;

			if (id == 0 || id == 3)
			{
				uint8 r1 = urand(0, 100); // Spyglass yes/no
				uint8 r2 = urand(0, 100); // Kneel while spying
				uint8 r3 = urand(0, 100);
				if (r1 < 33)
				{
					me->CastSpell(me, SPELL_SPYGLASS);
					_phase = 1;
					_timer = 4800;
				}
				if (r2 < 50)
				{
					me->HandleEmote(EMOTE_STATE_KNEEL);
				}
				if (r3 < 50)
					me->CastSpell(me, SPELL_SPYING);
				else
					me->CastSpell(me, SPELL_SNEAKING);
			}
		}

        void UpdateAI(uint32 diff) override
        {
			if (_timer <= diff)
				DoWork();
			else
				_timer -= diff;

			if (!UpdateVictim())
				return;

			DoMeleeAttackIfReady();
        }

		void DoWork()
        {
			if (me->IsInCombat())
				return;

			switch (_phase)
			{
			case 1:
				me->RemoveAllAuras();
				_phase = 0;
				_timer = 0;
				break;
			case 2:
				break;
			}
           
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_blackrock_spyAI (creature);
    }
};

//######################################### class quest series, own quest for each class

enum eQuest26919
{
	NPC_WOUNDET_TRAINEE = 44564,
	SPELL_FLASH_HEAL_2061 = 2061,
	NPC_KILLCREDIT= 44175,
};

class npc_woundet_trainee : public CreatureScript
{
public:
	npc_woundet_trainee() : CreatureScript("npc_woundet_trainee") { }

	struct npc_woundet_traineeAI : public ScriptedAI
	{
		npc_woundet_traineeAI(Creature *c) : ScriptedAI(c) { }

		void SpellHit(Unit* caster, SpellInfo const* spell) 
		{
			if (Player* player = caster->ToPlayer())
				if (spell->Id == SPELL_FLASH_HEAL_2061)
				{
					player->KilledMonsterCredit(NPC_KILLCREDIT, 0);
					me->DespawnOrUnsummon();
				}
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
		return new npc_woundet_traineeAI(creature);
	}
};


//#########################################  class quest 'They Sent Assassins'

enum eQuest28794
{
    NPC_GOBLIN_ASSASSIN = 50039,

    QUEST_THEY_SEND_ASSASSINS = 28794,

    SAY_ASSASSIN_COMBAT = 0,

};

class npc_goblin_assassin : public CreatureScript
{
public:
    npc_goblin_assassin() : CreatureScript("npc_goblin_assassin") { }

    struct npc_goblin_assassinAI : public ScriptedAI
    {
        npc_goblin_assassinAI(Creature *c) : ScriptedAI(c) { }

        void EnterCombat(Unit * /*who*/) override
        {
            Talk(SAY_ASSASSIN_COMBAT);
        }

        void UpdateAI(uint32 /*diff*/) override
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

     CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_goblin_assassinAI (creature);
    }
};

//#########################################  class quest 'Fear No Evil'

enum eQuest28806
{
    ITEM_PAXTONS_PRAYER_BOOK = 65733,

    NPC_INJURED_SOLDIER = 50047,
    NPC_INJURED_SOLDIER_DUMMY = 50378,
    NPC_MARSHAL_MC_BRIDE = 197,

    SPELL_RENEWEDLIFE = 93097,

    SAY_INJURED_SOLDIER = 1,
};

class npc_injured_soldier_dummy : public CreatureScript
{
public:
	npc_injured_soldier_dummy() : CreatureScript("npc_injured_soldier_dummy") { }

	struct npc_injured_soldier_dummyAI : public ScriptedAI
	{
		npc_injured_soldier_dummyAI(Creature *creature) : ScriptedAI(creature) { }

		uint32 _phase;
		uint32 _timer;

		void Reset() override
		{
			_phase = 0;
			_timer = 1000;
		}

		void UpdateAI(uint32 diff) override
		{
			if (_timer <= diff)
				DoWork();
			else
				_timer -= diff;
		}

		void DoWork()
		{
			_timer = 1000;

			switch (_phase)
			{
			case 1:
				if (Player* player = me->FindNearestPlayer(10.0f, true))
					me->SetFacingTo(me->GetAngle(player));
				_phase = 2;
				break;
			case 2:
				Talk(SAY_INJURED_SOLDIER);
				_timer = 2500;
				_phase = 3;
				break;
			case 3:
				me->GetMotionMaster()->MovePoint(0, -8830.69f, -151.335f, 80.256f);
				_phase = 0;
				break;
			}
		}
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_injured_soldier_dummyAI(creature);
	}
};

class npc_injured_soldier : public CreatureScript
{
public:
    npc_injured_soldier() : CreatureScript("npc_injured_soldier") { }
    
    bool OnGossipHello(Player* player, Creature* creature) override
    {
        player->PlayerTalkClass->SendCloseGossip();

        if (player->HasUnitState(UNIT_STATE_CASTING))
                return true;

        if (IsHealingQuestActiv(player) && player->HasItemCount(ITEM_PAXTONS_PRAYER_BOOK, 1))
        {
            creature->CastSpell(creature, SPELL_RENEWEDLIFE);
            player->KilledMonsterCredit(creature->GetEntry());
        }
        return true;
    }

    bool IsHealingQuestActiv(Player* player)
    {
        if (!player)
            return false;

        bool b = false;
        if (player->GetQuestStatus(28806) == QUEST_STATUS_INCOMPLETE) b=true;
        if (player->GetQuestStatus(28808) == QUEST_STATUS_INCOMPLETE) b=true;
        if (player->GetQuestStatus(28809) == QUEST_STATUS_INCOMPLETE) b=true;
        if (player->GetQuestStatus(28810) == QUEST_STATUS_INCOMPLETE) b=true;
        if (player->GetQuestStatus(28811) == QUEST_STATUS_INCOMPLETE) b=true;
        if (player->GetQuestStatus(28812) == QUEST_STATUS_INCOMPLETE) b=true;
        if (player->GetQuestStatus(28813) == QUEST_STATUS_INCOMPLETE) b=true;
        if (player->GetQuestStatus(29082) == QUEST_STATUS_INCOMPLETE) b=true;
        return b;
    }

    struct npc_injured_soldierAI : public ScriptedAI
    {
		npc_injured_soldierAI(Creature *creature) : ScriptedAI(creature) { m_phase = 0; }

        uint32 m_phase;
        uint32 m_timer;

        void Reset() override
        { 
            m_phase=0;
            m_timer=0;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override 
        {
			if (Creature* creature = caster->ToCreature())
				if (spell->Id == SPELL_RENEWEDLIFE  && m_phase == 0 && creature->GetEntry() == NPC_INJURED_SOLDIER)
				{
					m_phase = 1;
					m_timer = 1000;
				}
        }

		void JustSummoned(Creature* summon) override
		{ 
			CAST_AI(npc_injured_soldier_dummy::npc_injured_soldier_dummyAI, summon->AI())->_phase = 1;
		}

        void UpdateAI(uint32 diff) override
        {
            
            if (m_timer <= diff)
                DoWork();
            else
                m_timer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

        void DoWork()
        {
            m_timer = 1000;
            switch (m_phase)
            {
            case 1:
                me->SummonCreature(NPC_INJURED_SOLDIER_DUMMY, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + .5F, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 10000);
                m_phase = 2;
                break;
            case 2:
                me->DespawnOrUnsummon();
				m_phase = 0;
				m_timer = 0;
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_injured_soldierAI (creature);
    }
};

enum ePrinzess
{
	NPC_PRINCESS = 330,
	NPC_PORCINE_ENCOURAGE = 390,
	SPELL_RUSHING_CHARGE = 6268,
};

class npc_porcine_encourage : public CreatureScript
{
public:
	npc_porcine_encourage() : CreatureScript("npc_porcine_encourage") { }

	struct npc_porcine_encourageAI : public ScriptedAI
	{
		npc_porcine_encourageAI(Creature *creature) : ScriptedAI(creature) { }

		void StartAnim(Player* player) // start attack anim from princess
		{
			if (me->IsInCombat())
				return;

			me->CastSpell(me, SPELL_RUSHING_CHARGE);
			me->Attack(player,true);
		}
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_porcine_encourageAI(creature);
	}
};

class npc_princess : public CreatureScript
{
public:
	npc_princess() : CreatureScript("npc_princess") { }

	struct npc_princessAI : public ScriptedAI
	{
		npc_princessAI(Creature *creature) : ScriptedAI(creature) { }

		void EnterCombat(Unit* victim) override
		{ 
			std::list<Creature*> creatureList = me->FindNearestCreatures(NPC_PORCINE_ENCOURAGE, 20.0f);
			Player* player = victim->ToPlayer();

			if ((!player) || creatureList.empty())
				return;

			for (std::list<Creature*>::iterator itr = creatureList.begin(); itr != creatureList.end(); ++itr)
			{
				if (Creature* porcine = (*itr))
				{
					CAST_AI(npc_porcine_encourage::npc_porcine_encourageAI, porcine->AI())->StartAnim(player);
				}
			}
		}
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_princessAI(creature);
	}
};
//#########################################  quest ''


//#########################################  quest ''

// ToDo

/*######
## npc_henze_faulk
######*/

class npc_henze_faulk : public CreatureScript
{
public:
    npc_henze_faulk() : CreatureScript("npc_henze_faulk") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_henze_faulkAI (creature);
    }

    struct npc_henze_faulkAI : public ScriptedAI
    {
        uint32 lifeTimer;
        bool spellHit;

        npc_henze_faulkAI(Creature *c) : ScriptedAI(c) { }

        void Reset()
        {
            lifeTimer = 120000;
            me->SetUInt32Value(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
            me->SetStandState(UNIT_STAND_STATE_DEAD);   // lay down
            spellHit = false;
        }

        void EnterCombat(Unit * /*who*/) { }
        void MoveInLineOfSight(Unit * /*who*/) { }

        void UpdateAI(uint32 diff)
        {
            if (me->IsStandState())
            {
                if (lifeTimer <= diff)
                {
                    EnterEvadeMode();
                    return;
                }
                else
                    lifeTimer -= diff;
            }
        }

        void SpellHit(Unit * /*Hitter*/, SpellInfo const* spell)
        {
            if (spell->Id == 8593 && !spellHit)
            {
                DoCast(me, 32343);
                me->SetStandState(UNIT_STAND_STATE_STAND);
                me->SetUInt32Value(UNIT_DYNAMIC_FLAGS, 0);
                //me->RemoveAllAuras();
                Talk(0);
                spellHit = true;
            }
        }
    };
};

void AddSC_elwynn_forest()
{
    // new npc_henze_faulk();
    new npc_injured_soldier();
    new npc_injured_soldier_dummy();
    new npc_stormwind_infantry();
    new npc_brother_paxton();
    new npc_blackrock_battle_worg();
    new npc_blackrock_spy(); 
    new npc_goblin_assassin();
	new npc_woundet_trainee();
	new npc_porcine_encourage();
	new npc_princess();
}
