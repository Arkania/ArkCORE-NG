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
SDName: Duskwood
SD%Complete: 0
SDComment: Quest Support:
SDCategory: Coldridge Valley
EndScriptData */

/* ContentData

EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Player.h"

enum zone_coldridge_valley
{
	NPC_ROCKSAW_INVADER									= 37070,
	NPC_WOUNDED_COLDRIDGE_MOUNTAINEER_KILL_CREDIT		= 37079,
	NPC_WOUNDED_COLDRIDGE_MOUNTAINEER					= 37080,
	NPC_COLDRIDGE_DEFENDER								= 37177,
	NPC_SOOTHSAYER_SHIKALA								= 37108,
	NPC_SOOTHSAYER_RIKKARI  							= 37173,
	NPC_SOOTHSAYER_MIRIMKOA								= 37174,
	NPC_TROLLING_FOR_INFORMATION_KILL_CREDIT_BUNNY_SE	= 37109,
	NPC_TROLLING_FOR_INFORMATION_KILL_CREDIT_BUNNY_SW	= 37110,
	NPC_TROLLING_FOR_INFORMATION_KILL_CREDIT_BUNNY_W	= 37111,

	SPELL_HEAL_WOUNDED_MOUNTAINEER						= 69855,

	QUEST_AID_FOR_THE_WOUNDED							= 24471,
	QUEST_TROLLING_FOR_INFORMATION						= 24489,


};

/*######
## npc_rockjaw_invader
######*/

class npc_rockjaw_invader : public CreatureScript
{
public:
    npc_rockjaw_invader() : CreatureScript("npc_rockjaw_invader") { }

    struct npc_rockjaw_invaderAI : public ScriptedAI
    {
        npc_rockjaw_invaderAI(Creature сreature) : ScriptedAI(сreature) {}

        uint32 Attack1HTimer;        	

        void Reset()  
        {
            Attack1HTimer = urand(1800,2200);           			
        }

        void UpdateAI(const uint32 diff) 
        {						
            if (!UpdateVictim())
			{
				if (Creature* infantry = me->FindNearestCreature (NPC_COLDRIDGE_DEFENDER, 3.0f)) 
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
				DoMeleeAttackIfReady();
			
        }
    };

       CreatureAI* GetAI(Creature* сreature) const  
    {
        return new npc_rockjaw_invaderAI (сreature);
    }
};

/*######
## npc_coldridge_defender
######*/

class npc_coldridge_defender : public CreatureScript
{
public:
    npc_coldridge_defender() : CreatureScript("npc_coldridge_defender") { }

    struct npc_coldridge_defenderAI : public ScriptedAI
    {
        npc_coldridge_defenderAI(Creature creature) : ScriptedAI(creature) {}

        uint32 Attack1HTimer;        	

        void Reset()  
        {
            Attack1HTimer = urand(1800,2200);           			
        }

        void UpdateAI(const uint32 diff) 
        {						
            if (!UpdateVictim())
			{
				if (Creature* infantry = me->FindNearestCreature (NPC_ROCKSAW_INVADER, 3.0f)) 
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
				DoMeleeAttackIfReady();
			
        }
    };

       CreatureAI* GetAI(Creature* creature) const  
    {
        return new npc_coldridge_defenderAI (creature);
    }
};

/*######
## npc_wounded_coldridge_mountaineer
######*/

class npc_wounded_coldridge_mountaineer : public CreatureScript
{
public:
    npc_wounded_coldridge_mountaineer() : CreatureScript("npc_wounded_coldridge_mountaineer") { }
	
	bool OnGossipHello(Player* player, Creature* creature) 
    {
        player->PlayerTalkClass->SendCloseGossip();		

		if (player->HasUnitState(UNIT_STATE_CASTING)) 
				return true;
		
        if (player->GetQuestStatus(QUEST_AID_FOR_THE_WOUNDED) == QUEST_STATUS_INCOMPLETE)
        {  			
			creature->CastSpell(creature, SPELL_HEAL_WOUNDED_MOUNTAINEER, false);
			player->KilledMonsterCredit(NPC_WOUNDED_COLDRIDGE_MOUNTAINEER_KILL_CREDIT, NULL);
        }
        return true;
    }

    struct npc_wounded_coldridge_mountaineerAI : public ScriptedAI
    {
		npc_wounded_coldridge_mountaineerAI(Creature *creature) : ScriptedAI(creature) 
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
		
		// ToDo
	    void SpellHit(Unit * Hitter, SpellInfo const* spell) 
        {
			printf("zauber ist eingetroffen %d \n", spell->Id );
            if (spell->Id == SPELL_HEAL_WOUNDED_MOUNTAINEER )
            {
				isHealed=true;
				DoCast(Hitter, NPC_WOUNDED_COLDRIDGE_MOUNTAINEER_KILL_CREDIT);
				printf("Jo, ich wurde geheilt \n");
            }
        }
		
		void UpdateAI(const uint32 diff) 
        {   

			if (!isHealed) return;

			if (timer <= diff)	
			{
			

			}	
			else 
				timer -= diff;	
		}
    };
	 
	CreatureAI* GetAI(Creature* creature) const  
    {
        return new npc_wounded_coldridge_mountaineerAI (creature);
    }
};

/*######
## npc_soothsayer_shikala
######*/

class npc_soothsayer_shikala : public CreatureScript
{
public:
    npc_soothsayer_shikala() : CreatureScript("npc_soothsayer_shikala") { }

    struct npc_soothsayer_shikalaAI : public ScriptedAI
    {
        npc_soothsayer_shikalaAI(Creature creature) : ScriptedAI(creature) {}

        uint32 timer;  
		uint32 phase;
		bool TalkSequenceIsStarted;
		Player* player;
		
        void Reset()  
        {
              timer=0; TalkSequenceIsStarted=false; phase=0;       			
        }

		void MoveInLineOfSight(Unit* who) 
        {
            if (!who || !who->IsAlive() || TalkSequenceIsStarted)
                return;

            if (who->GetTypeId() == TYPEID_PLAYER && me->IsWithinDistInMap(who, 10.0f))
			{
				player = who->ToPlayer();
				if (player)
				{
                    if (player->GetQuestStatus(QUEST_TROLLING_FOR_INFORMATION) == QUEST_STATUS_INCOMPLETE)
                    {                   
                        TalkSequenceIsStarted = true;
						timer = 2000; phase++;
                    }
				}
			}                
        }

        void UpdateAI(const uint32 diff) 
        {						
            if (!UpdateVictim())
			{
				if (TalkSequenceIsStarted)
				{
					if (!player)
					{
						timer=0; phase=0; TalkSequenceIsStarted=false;
						return;
					}
					if (timer<=diff)
					{						
						switch (phase)
						{
						case 1:
							{ 
								Talk(0); timer=5000; phase++;
								break;
							}
						case 2:
							{ 
								Talk(1); timer=5000; phase++;
								break;
							}
						case 3:
							{ 
								Talk(2); timer=5000; phase++;
								break;
							}
						case 4:
							{																																						
								player->KilledMonsterCredit(NPC_TROLLING_FOR_INFORMATION_KILL_CREDIT_BUNNY_SE, NULL);	
								timer=120000; phase++; // cooldown
								break;
							}
						case 5:
							{																																																
								timer=0; phase=0; TalkSequenceIsStarted=false;																			  								
								break;
							}
						}				
					}
					else
						timer-=diff;

					if (!me->IsInRange (player, 0.0f, 15.0F)) 
					{ 
						timer=0; phase=0; TalkSequenceIsStarted=false; // if player gone away, delete cooldown
					}
				}

			} else 
				DoMeleeAttackIfReady();
			
        }
    };

    CreatureAI* GetAI(Creature* creature) const  
    {
        return new npc_soothsayer_shikalaAI (creature);
    }
};

/*######
## npc_soothsayer_rikkari
######*/

class npc_soothsayer_rikkari : public CreatureScript
{
public:
    npc_soothsayer_rikkari() : CreatureScript("npc_soothsayer_rikkari") { }

    struct npc_soothsayer_rikkariAI : public ScriptedAI
    {
        npc_soothsayer_rikkariAI(Creature сreature) : ScriptedAI(сreature) {}

        uint32 timer;  
		uint32 phase;
		bool TalkSequenceIsStarted;
		Player* player;
		
        void Reset()  
        {
              timer=0; TalkSequenceIsStarted=false; phase=0;       			
        }

		void MoveInLineOfSight(Unit* who) 
        {
            if (!who || !who->IsAlive() || TalkSequenceIsStarted)
                return;

            if (who->GetTypeId() == TYPEID_PLAYER && me->IsWithinDistInMap(who, 10.0f))
			{				
				player = who->ToPlayer();
				if (player)
				{
                    if (player->GetQuestStatus(QUEST_TROLLING_FOR_INFORMATION) == QUEST_STATUS_INCOMPLETE)
                    {                       
                        TalkSequenceIsStarted = true;
						timer = 2000; phase++;
                    }
				}
			}                
        }

        void UpdateAI(const uint32 diff) 
        {						
            if (!UpdateVictim())
			{
				if (TalkSequenceIsStarted)
				{					
					if (!player)
					{
						timer=0; phase=0; TalkSequenceIsStarted=false;
						return;
					}
					if (timer<=diff)
					{						
						switch (phase)
						{
						case 1:
							{ 
								Talk(0); timer=5000; phase++;
								break;
							}
						case 2:
							{ 
								Talk(1); timer=5000; phase++;
								break;
							}
						case 3:
							{ 
								Talk(2); timer=5000; phase++;
								break;
							}
						case 4:
							{																																								
								player->KilledMonsterCredit(NPC_TROLLING_FOR_INFORMATION_KILL_CREDIT_BUNNY_SW, NULL);	
								timer=120000; phase++; // cooldown																		  								
								break;
							}
						case 5:
							{																																																
								timer=0; phase=0; TalkSequenceIsStarted=false;																			  								
								break;
							}
						}				
					}
					else
						timer-=diff;

					if (!me->IsInRange (player, 0.0f, 15.0F)) 
					{ 
						timer=0; phase=0; TalkSequenceIsStarted=false; // if player gone away, delete cooldown
					}
				}

			} else 
				DoMeleeAttackIfReady();
			
        }
    };

    CreatureAI* GetAI(Creature* сreature) const  
    {
        return new npc_soothsayer_rikkariAI (creature);
    }
};

/*######
## npc_soothsayer_mirimkoa
######*/

class npc_soothsayer_mirimkoa : public CreatureScript
{
public:
    npc_soothsayer_mirimkoa() : CreatureScript("npc_soothsayer_mirimkoa") { }

    struct npc_soothsayer_mirimkoaAI : public ScriptedAI
    {
        npc_soothsayer_mirimkoaAI(Creature сreature) : ScriptedAI(сreature) {}

        uint32 timer;  
		uint32 phase;
		bool TalkSequenceIsStarted;
		Player* player;
		
        void Reset()  
        {
              timer=0; TalkSequenceIsStarted=false; phase=0;       			
        }

		void MoveInLineOfSight(Unit* who) 
        {
            if (!who || !who->IsAlive() || TalkSequenceIsStarted)
                return;

            if (who->GetTypeId() == TYPEID_PLAYER && me->IsWithinDistInMap(who, 10.0f))
			{
				player = who->ToPlayer();
				if (player)
				{
                    if (player->GetQuestStatus(QUEST_TROLLING_FOR_INFORMATION) == QUEST_STATUS_INCOMPLETE)
                    {                        
                        TalkSequenceIsStarted = true;
						timer = 2000; phase++;
                    }
				}
			}                
        }

        void UpdateAI(const uint32 diff) 
        {						
            if (!UpdateVictim())
			{
				if (TalkSequenceIsStarted)
				{
					if (!player)
					{
						timer=0; phase=0; TalkSequenceIsStarted=false;
						return;
					}
					if (timer<=diff)
					{						
						switch (phase)
						{
						case 1:
							{ 
								Talk(0); timer=5000; phase++;
								break;
							}
						case 2:
							{ 
								Talk(1); timer=5000; phase++;
								break;
							}
						case 3:
							{ 
								Talk(2); timer=5000; phase++;
								break;
							}
						case 4:
							{																																										
								player->KilledMonsterCredit(NPC_TROLLING_FOR_INFORMATION_KILL_CREDIT_BUNNY_W, NULL);	
								timer=120000; phase++; // cooldown													  								
								break;
							}
						case 5:
							{																																																
								timer=0; phase=0; TalkSequenceIsStarted=false;																			  								
								break;
							}
						}				
					}
					else
						timer-=diff;

					if (!me->IsInRange (player, 0.0f, 15.0F)) 
					{ 
						timer=0; phase=0; TalkSequenceIsStarted=false; // if player gone away, delete cooldown
					}
				}

			} else 
				DoMeleeAttackIfReady();
			
        }
    };

    CreatureAI* GetAI(Creature* creature) const  
    {
        return new npc_soothsayer_mirimkoaAI (creature);
    }
};

/*######
## AddSC
######*/

void AddSC_coldridge_valley()
{
    new npc_rockjaw_invader();
	new npc_coldridge_defender();
	new npc_wounded_coldridge_mountaineer();
	new npc_soothsayer_shikala(); 
	new npc_soothsayer_rikkari();
	new npc_soothsayer_mirimkoa();

}

