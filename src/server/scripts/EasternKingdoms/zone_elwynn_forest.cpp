
/*
 *
 * Copyright (C) 2011-2014 ArkCORE <http://www.arkania.net/>
 *
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 *
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
#include "ScriptPCH.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "Player.h"


enum Northshire
{
    NPC_BROTHER_PAXTON          = 951,
	NPC_BLACKROCK_SPY           = 49874,
    NPC_BLACKROCK_INVADER       = 42937,
    NPC_STORMWIND_INFANTRY      = 49869,
    NPC_BLACKROCK_BATTLE_WORG   = 49871,
	NPC_GOBLIN_ASSASSIN			= 50039,
    NPC_INJURED_SOLDIER         = 50047,
    NPC_INJURED_SOLDIER_DUMMY   = 50378,
	NPC_MARSHAL_MC_BRIDE		= 197,

    SAY_INFANTRY_NORMAL			= 0,
    SAY_INFANTRY_COMBAT			= 1,
    SAY_PAXTON_NORMAL			= 0,
    SAY_BLACKROCK_COMBAT		= 0,
    SAY_ASSASSIN_COMBAT			= 0,
	SAY_INJURED_SOLDIER			= 0,
	SAY_HEAL					= 0,
   
	SPELL_REVIVE			  = 93799, 
    SPELL_RENEW               = 93094,  
    SPELL_PRAYER_OF_HEALING   = 93091,  
    SPELL_FORTITUDE           = 13864, 
    SPELL_PENANCE             = 47750,  
    SPELL_FLASH_HEAL          = 17843,  
    SPELL_SPYING              = 92857,
    SPELL_SNEAKING            = 93046,
    SPELL_SPYGLASS            = 80676,
	SPELL_RENEWEDLIFE         = 93097,
	SPELL_CONVERSATIONS_TRIGGER_01 = 84076,
};

/*######
## npc_blackrock_battle_worg
######*/

class npc_blackrock_battle_worg : public CreatureScript
{
public:
    npc_blackrock_battle_worg() : CreatureScript("npc_blackrock_battle_worg") { }

    struct npc_blackrock_battle_worgAI : public ScriptedAI
    {
        npc_blackrock_battle_worgAI(Creature *c) : ScriptedAI(c) {}

        uint32 Attack1HTimer;        	

        void Reset()  
        {
            Attack1HTimer = urand(1800,2200);           			
        }

        void UpdateAI(const uint32 diff) 
        {						
            if (!UpdateVictim())
			{
				if (Creature* infantry = me->FindNearestCreature (NPC_STORMWIND_INFANTRY, 3.0f)) 
				{
					if (Attack1HTimer <= diff)
					{
						me->SetFacingTo (me->GetAngle(infantry));
						me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK1H);
						Attack1HTimer = urand(1800,2200);
					}
					else Attack1HTimer -= diff;
				}
			} else
			{
				DoMeleeAttackIfReady();
			}
        }
    };

       CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_blackrock_battle_worgAI (creature);
    }
};

/*######
## npc_stormwind_infantry
######*/

class npc_stormwind_infantry : public CreatureScript
{
public:
    npc_stormwind_infantry() : CreatureScript("npc_stormwind_infantry") { }

    struct npc_stormwind_infantryAI : public ScriptedAI
    {
        npc_stormwind_infantryAI(Creature *c) : ScriptedAI(c) {}

        uint32 uiSayTimer;
        uint32 Attack1HTimer;

        void Reset()  
        {
            uiSayTimer = urand(	10000, 300000);
            Attack1HTimer = urand(1800,2200);
        }

        void UpdateAI(const uint32 diff) 
        {
			if (!UpdateVictim())
			{
				Creature* worg; 
				Creature* paxton; 
				if ( worg = me->FindNearestCreature (NPC_BLACKROCK_BATTLE_WORG, 3.0f) )
				{
					me->SetFacingTo (me->GetAngle(worg));
					if (!worg->IsAttackingPlayer()) 
					{
						if (Attack1HTimer <= diff)
						{						
							me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK1H);
							Attack1HTimer = urand(1800,2200);
						}
						else Attack1HTimer -= diff;		

						if (paxton = me->FindNearestCreature (NPC_BROTHER_PAXTON,25.0f))
						{
						
							if (uiSayTimer <= diff)
							{
								Talk(SAY_INFANTRY_COMBAT);
								DoCast(paxton,SPELL_CONVERSATIONS_TRIGGER_01);
								uiSayTimer = urand(30000, 120000);
							}else uiSayTimer -= diff;

							return;
						}
					}
					if (uiSayTimer <= diff)
					{
						Talk(SAY_INFANTRY_NORMAL);
						uiSayTimer = urand(45000, 300000);
					}else uiSayTimer -= diff;
				} 
			}
		}
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_stormwind_infantryAI (creature);
    }
};

/*######
## npc_blackrock_spy
######*/

class npc_blackrock_spy : public CreatureScript
{
public:
    npc_blackrock_spy() : CreatureScript("npc_blackrock_spy") { }
	
    struct npc_blackrock_spyAI : public ScriptedAI
    {		
        npc_blackrock_spyAI(Creature *c) : ScriptedAI(c) {}
       	
		uint32 Phase;
		uint32 Emote;
		uint32 Aura;
		uint32 Timer;
		
		void Reset()  
			{ CreateNewPhase(); }    
       
		void EnterCombat(Unit* /*who*/)  
		{ 
			Talk(0);
		}

		void UpdateAI(const uint32 diff) 
        {      
			if (!UpdateVictim())
			{					
				if (Timer <= diff)           
					CreateNewPhase();             
				else
					Timer -= diff;            
			} else
			{
				if (me->HasAura(SPELL_SPYGLASS)) me->RemoveAurasDueToSpell(SPELL_SPYGLASS);
				if (me->HasAura(SPELL_SNEAKING)) me->RemoveAurasDueToSpell(SPELL_SNEAKING);
				if (me->HasAura(SPELL_SPYING)) me->RemoveAurasDueToSpell(SPELL_SPYING);
				DoMeleeAttackIfReady();
			}
        }

		void CreateNewPhase()
		{
			Phase = urand(0, 2);
            Emote = urand(0, 1);
            Aura = urand(0, 2);
            Timer = urand(10000, 30000);  
			switch(Phase)
			{				
                case 0: // stand 2H
					me->GetMotionMaster()->MoveRandom(0.0f);
					if (me->HasAura(SPELL_SPYGLASS)) me->RemoveAurasDueToSpell(SPELL_SPYGLASS);
					if (me->HasAura(SPELL_SNEAKING)) me->RemoveAurasDueToSpell(SPELL_SNEAKING);
					if (me->HasAura(SPELL_SPYING)) me->RemoveAurasDueToSpell(SPELL_SPYING);
                    me->HandleEmoteCommand(EMOTE_STATE_READY2H);
					break;
				case 1: // sneaking and spying
					me->HandleEmoteCommand(EMOTE_STATE_NONE);					
					if (me->HasAura(SPELL_SPYGLASS)) me->RemoveAurasDueToSpell(SPELL_SPYGLASS);
					if (!me->HasAura(SPELL_SNEAKING)) DoCast(me, SPELL_SNEAKING);
					if (!me->HasAura(SPELL_SPYING)) DoCast(me, SPELL_SPYING);
					me->GetMotionMaster()->MoveRandom(4.0f);
					break;
				case 2: // spyglass
					me->GetMotionMaster()->MoveRandom(0.0f);					
					me->HandleEmoteCommand(EMOTE_STATE_NONE);
					if (me->HasAura(SPELL_SNEAKING)) me->RemoveAurasDueToSpell(SPELL_SNEAKING);
					if (me->HasAura(SPELL_SPYING)) me->RemoveAurasDueToSpell(SPELL_SPYING);
                    if (!me->HasAura(SPELL_SPYGLASS)) DoCast(me, SPELL_SPYGLASS);
					break;				
			 } 
		}
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_blackrock_spyAI (creature);
    }
};

/*######
## npc_goblin_assassin
######*/

class npc_goblin_assassin : public CreatureScript
{
public:
    npc_goblin_assassin() : CreatureScript("npc_goblin_assassin") { }

    struct npc_goblin_assassinAI : public ScriptedAI
    {
        npc_goblin_assassinAI(Creature *c) : ScriptedAI(c)
        {
            if (!me->IsInCombat() && !me->HasAura(SPELL_SPYING))
                DoCast(SPELL_SNEAKING);
		}

        void EnterCombat(Unit * who)  
        {
            Talk(0);
        }

        void UpdateAI(const uint32 diff) 
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

/*######
## npc_injured_soldier
######*/

class npc_injured_soldier : public CreatureScript
{
public:
    npc_injured_soldier() : CreatureScript("npc_injured_soldier") { }
	
	bool OnGossipHello(Player* player, Creature* creature) 
    {
        player->PlayerTalkClass->SendCloseGossip();		

		if (player->HasUnitState(UNIT_STATE_CASTING)) 
				return true;

        if (IsHealingQuestActiv(player))
        {  			
			creature->CastSpell(creature, SPELL_RENEWEDLIFE, false);
			player->KilledMonsterCredit(creature->GetEntry(), NULL);
        }
        return true;
    }

	bool IsHealingQuestActiv(Unit* who)
	{
		Player* player = who->ToPlayer();

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
		npc_injured_soldierAI(Creature *creature) : ScriptedAI(creature) 
		{
			isHealed=false; phase=3;
		} 
		
		bool isHealed;
		uint32 phase;
		uint32 timer;
				
		void Reset()  
		{ 
			isHealed=false;
			phase=0;
			timer=1000;
		}
			
	    void SpellHit(Unit * Hitter, SpellInfo const* spell) 
        {
            if (spell->Id == SPELL_RENEWEDLIFE )
            {
				isHealed=true;				
            }
        }
		
		void UpdateAI(const uint32 diff) 
        {   

			if (!isHealed) return;

			if (timer <= diff)	
			{
				phase ++;
			    timer=1000;

				switch (phase)
				{
				case 1:
					{							
						me->SummonCreature(NPC_INJURED_SOLDIER_DUMMY, me->GetPositionX() ,me->GetPositionY() ,me->GetPositionZ() + .5F , 0.0f, TEMPSUMMON_TIMED_DESPAWN, 10000);		
						break;
					}
				case 2:
					{
						me->DespawnOrUnsummon(0);
						isHealed=false;
						break;
					}								
				}           						
			}	
			else 
				timer -= diff;	
		}
    };
	 
	CreatureAI* GetAI(Creature* creature) const  
    {
        return new npc_injured_soldierAI (creature);
    }
};

/*######
## npc_injured_soldier_dummy
######*/

class npc_injured_soldier_dummy : public CreatureScript
{
public:
    npc_injured_soldier_dummy() : CreatureScript("npc_injured_soldier_dummy") { }
	
    struct npc_injured_soldier_dummyAI : public ScriptedAI
    {
        npc_injured_soldier_dummyAI(Creature *creature) : ScriptedAI(creature) { }
		  
		uint32 phase;
		uint32 timer;

		void Reset() 
        {
            phase=0;
			timer=1000;
        }
			       
		void UpdateAI(const uint32 diff) 
        {
			if (!me->IsAlive()) return;
			
			if (timer <= diff)	
			{
				phase ++;
			    timer=1000;

				switch(phase)
				{
					case 1:
					{
						if (Player* player = me->FindNearestPlayer(10.0f,true)) 												
						    me->SetFacingTo (me->GetAngle(player));
						break;
					}
					case 2:
					{
						Talk(1);
						timer=2500;					
						break;
					}
					case 3:
					{
						Creature* McBride = me->FindNearestCreature (NPC_MARSHAL_MC_BRIDE,300.0f,true);		
						me->GetMotionMaster()->MovePoint(0, McBride->GetPositionX(), McBride->GetPositionY(), McBride->GetPositionZ() );
						timer=10000;					
						break;
					}				
				}
			}
			 else 
				timer -= diff;			
					
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_injured_soldier_dummyAI (creature);
    }
};

/*######
## npc_brother_paxton
######*/

class npc_brother_paxton : public CreatureScript
{
public:
    npc_brother_paxton() : CreatureScript("npc_brother_paxton") { }

    struct npc_brother_paxtonAI : public ScriptedAI
    {
        npc_brother_paxtonAI(Creature *c) : ScriptedAI(c)
        {
            me->GetMotionMaster()->MovePath(951, true);
			// if (!me->HasAura(SPELL_REVIVE)) DoCast(me, SPELL_REVIVE);
		}
	
		bool isHealingNow;
		uint32 timer;

		void SpellHit(Unit * Hitter, SpellInfo const* spell) 
        {					
            if (!Hitter || isHealingNow) return;
			if (Hitter->GetEntry() != NPC_STORMWIND_INFANTRY || spell->Id != SPELL_CONVERSATIONS_TRIGGER_01) return;				
								
			me->CastSpell(Hitter,SPELL_PRAYER_OF_HEALING);
			me->SetFacingTo (me->GetAngle(Hitter));
			timer=3000;
			isHealingNow=true;
        }

		void UpdateAI(const uint32 diff) 
		{			
			if (isHealingNow)
			{
				if (timer <= diff)	
				{
					// me->GetMotionMaster()->MovePath (951,true);		
					isHealingNow=false;
				}
				else 
					timer -= diff;			
			}
			
            if (!UpdateVictim())
			   return;
				
			DoMeleeAttackIfReady();
		}		
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_brother_paxtonAI (creature);
    }
};



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

        npc_henze_faulkAI(Creature *c) : ScriptedAI(c) {}

        void Reset()  
        {
            lifeTimer = 120000;
            me->SetUInt32Value(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
            me->SetStandState(UNIT_STAND_STATE_DEAD);   // lay down
            spellHit = false;
        }

        void EnterCombat(Unit * /*who*/)  
        {
        }

        void MoveInLineOfSight(Unit * /*who*/)  
        {
        }

        void UpdateAI(const uint32 diff) 
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
                Talk(SAY_HEAL);
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
}
