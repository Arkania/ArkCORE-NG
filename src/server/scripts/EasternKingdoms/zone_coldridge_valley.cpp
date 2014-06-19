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
SDName: Duskwood
SD%Complete: 0
SDComment: Quest Support:
SDCategory: Coldridge Valley
EndScriptData */

/* ContentData

EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "ScriptedGossip.h"
#include "Player.h"

enum zone_coldridge_valley
{
	NPC_ROCKSAW_INVADER									= 37070,
	NPC_WOUNDED_COLDRIDGE_MOUNTAINEER_KILL_CREDIT		= 37079,
	NPC_WOUNDED_COLDRIDGE_MOUNTAINEER					= 37080,
	NPC_COLDRIDGE_DEFENDER								= 37177,
    NPC_ROCKJAW_SCAVENGER                               = 37105,
	NPC_SOOTHSAYER_SHIKALA								= 37108,
	NPC_SOOTHSAYER_RIKKARI  							= 37173,
	NPC_SOOTHSAYER_MIRIMKOA								= 37174,
	NPC_TROLLING_FOR_INFORMATION_KILL_CREDIT_BUNNY_SE	= 37109,
	NPC_TROLLING_FOR_INFORMATION_KILL_CREDIT_BUNNY_SW	= 37110,
	NPC_TROLLING_FOR_INFORMATION_KILL_CREDIT_BUNNY_W	= 37111,

	SPELL_HEAL_WOUNDED_MOUNTAINEER						= 69855,
    SPELL_THROW_PRICELESS_ARTIFACT                      = 69897,

	QUEST_AID_FOR_THE_WOUNDED							= 24471,
	QUEST_TROLLING_FOR_INFORMATION						= 24489,
    QUEST_MAKE_HAY_WHILE_THE_SUN_SHINES                 = 24486,
    ITEM_PRICELESS_ROCKJAW_ARTIFACT                     = 49751,

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
        npc_rockjaw_invaderAI(Creature *c) : ScriptedAI(c) { }

        uint32 Attack1HTimer;            

        void Reset()  
        {
            Attack1HTimer = urand(1800,2200);                       
        }

        void UpdateAI(uint32 diff) 
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

       CreatureAI* GetAI(Creature* creature) const  
    {
        return new npc_rockjaw_invaderAI (creature);
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
        npc_coldridge_defenderAI(Creature *c) : ScriptedAI(c) { }

        uint32 Attack1HTimer;            

        void Reset()  
        {
            Attack1HTimer = urand(1800,2200);                       
        }

        void UpdateAI(uint32 diff) 
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
## ToDo:  spell is wrong implemented in core
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
            player->KilledMonsterCredit(NPC_WOUNDED_COLDRIDGE_MOUNTAINEER_KILL_CREDIT, 0);
        }
        return true;
    }

    struct npc_wounded_coldridge_mountaineerAI : public ScriptedAI
    {
		npc_wounded_coldridge_mountaineerAI(Creature *creature) : ScriptedAI(creature) 
		{
            timer = 0; phase = 0;
		} 
				
		uint32 phase;
		uint32 timer;
				
	    void SpellHit(Unit* Hitter, SpellInfo const* spell) 
        {	
            if (Player* player = Hitter->ToPlayer())
                if (player->GetQuestStatus(QUEST_AID_FOR_THE_WOUNDED) == QUEST_STATUS_INCOMPLETE)
                    if (me->GetDistance(player) < 5.0f)
                        if (spell->Id == SPELL_HEAL_WOUNDED_MOUNTAINEER)
                        {
                            phase = 1;
                            timer = 1000;
                            DoCast(Hitter, NPC_WOUNDED_COLDRIDGE_MOUNTAINEER_KILL_CREDIT);				                
                        }
        }

		void UpdateAI(uint32 diff) 
        {   
			if (timer <= diff)	
			{
                switch (phase)
                {
                case 1:
                    Talk(0);
                    timer = 5000;
                    phase = 2;
                    break;
                case 2:
                    me->GetMotionMaster()->MovePoint(0, me->GetNearPosition(25.0f, me->GetFollowAngle()));
                    timer = 10000;
                    phase = 3;
                    break;
                case 3:
                    me->DisappearAndDie();
                    phase = 0;
                    break;
                }               
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
## npc_rockjaw_scavenger
######*/

class npc_rockjaw_scavenger : public CreatureScript
{
public:
    npc_rockjaw_scavenger() : CreatureScript("npc_rockjaw_scavenger") { }

    struct npc_rockjaw_scavengerAI : public ScriptedAI
    {
        npc_rockjaw_scavengerAI(Creature *creature) : ScriptedAI(creature)  
        { 
            _hasCasted = false;
        }
       
        bool _hasCasted;

        void DamageTaken(Unit* Hitter, uint32& Damage)
        {
            if (Player* player = Hitter->ToPlayer())
                if (player->GetQuestStatus(QUEST_MAKE_HAY_WHILE_THE_SUN_SHINES) == QUEST_STATUS_INCOMPLETE)
                    if (!_hasCasted)
                        if (me->GetDistance(player) >= 5.0f && me->GetDistance(player) <= 15.0f)
                            switch (urand(0, 3))
                            {
                            case 2:
                                me->CastSpell(player, SPELL_THROW_PRICELESS_ARTIFACT, true);
                                player->AddItem(ITEM_PRICELESS_ROCKJAW_ARTIFACT, 1);
                                _hasCasted = true;
                            }
        
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();           
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_rockjaw_scavengerAI(creature);
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
        npc_soothsayer_shikalaAI(Creature *c) : ScriptedAI(c) { }

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

        void UpdateAI(uint32 diff) 
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
                                player->KilledMonsterCredit(NPC_TROLLING_FOR_INFORMATION_KILL_CREDIT_BUNNY_SE, 0);    
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
        npc_soothsayer_rikkariAI(Creature *c) : ScriptedAI(c) { }

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

        void UpdateAI(uint32 diff) 
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
                                player->KilledMonsterCredit(NPC_TROLLING_FOR_INFORMATION_KILL_CREDIT_BUNNY_SW, 0);    
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
        npc_soothsayer_mirimkoaAI(Creature *c) : ScriptedAI(c) { }

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

        void UpdateAI(uint32 diff) 
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
                                player->KilledMonsterCredit(NPC_TROLLING_FOR_INFORMATION_KILL_CREDIT_BUNNY_W, 0);    
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

// ################################################ Quest: Follow that Gyro-Copter! 24491

enum eQuest24491
{
    QUEST_FOLLOW_THAT_GYRO_COPTER = 24491,

    NPC_HANDS_SPRINGSPROCKET = 6782,

    SPELL_SEE_COLDRIGE_TUNNEL_ROCKS_SEE_QUEST_INVIS_1 = 70042,
    SPELL_SEE_MILO_GEARTWINGE_SEE_QUEST_INVIS_2 = 70044,
    SPELL_MILO_GEARTWINGE_INVISIBILITY_QUEST_INVIS_2 = 70045,
};

class npc_hands_springsprocket : public CreatureScript
{
public:
    npc_hands_springsprocket() : CreatureScript("npc_hands_springsprocket") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) 
    { 
        if (quest->GetQuestId() == QUEST_FOLLOW_THAT_GYRO_COPTER)
            if (!player->HasAura(SPELL_SEE_MILO_GEARTWINGE_SEE_QUEST_INVIS_2))
            {                
                player->CastSpell(player, SPELL_SEE_COLDRIGE_TUNNEL_ROCKS_SEE_QUEST_INVIS_1, true);
                player->CastSpell(player, SPELL_SEE_MILO_GEARTWINGE_SEE_QUEST_INVIS_2, true);               
            }         

        return true; 
    }
};


// ################################################ Quest: Pack Your Bags 24492

enum eQuest24492
{    
    QUEST_PACK_YOUR_BAGS = 24492,

    NPC_MILO_GEARTWINGE = 37113,
    NPC_MILO_GEARTWINGE_SPAWNED = 37518,
    NPC_MILOS_GYRO = 37169,
    NPC_MILOS_GYRO_SPAWNED = 37198,

    SPELL_SUMMON_MILOS_GYROCOPTER = 70035,
    SPELL_RIDING_MILOS_GYRO = 70036,
};

class npc_milos_gyro_spawned : public CreatureScript
{
public:
    npc_milos_gyro_spawned() : CreatureScript("npc_milos_gyro_spawned") { }

    struct npc_milos_gyro_spawnedAI : public npc_escortAI
    {
        npc_milos_gyro_spawnedAI(Creature* creature) : npc_escortAI(creature) 
        {             
            AddWaypoint(1, -6220.035645f, 296.816772f, 409.775787f);
            AddWaypoint(2, -6180.738281f, 271.849091f, 435.231506f);
            AddWaypoint(3, -6167.073730f, 213.735809f, 470.028137f);
            AddWaypoint(4, -6134.929688f, 124.723755f, 507.195953f);
            AddWaypoint(5, -6075.491699f, 73.982384f, 510.407410f);
            AddWaypoint(6, -5984.715820f, -9.166074f, 470.231415f);
            AddWaypoint(7, -5908.320313f, -225.218124f, 490.649323f);
            AddWaypoint(8, -5727.785156f, -416.732208f, 466.876831f);
            AddWaypoint(9, -5647.638672f, -482.040649f, 399.289917f);
            AddWaypoint(10, -5629.615234f, -484.758545f, 396.980530f);
            AddWaypoint(11, -5618.415527f, -484.724670f, 396.980530f);

            SetDespawnAtEnd(true);
            me->EnableAI();
            _phase = 0;
        }

        uint32 _phase;

        void PassengerBoarded(Unit* who, int8 seatId, bool apply)
        {
            if (!apply)
                return;

            if (seatId == 0)
            {
                me->SetSpeed(MOVE_FLIGHT, 2.0f, true);
                Start();                
            }
        }

        void WaypointReached(uint32 point)
        {
            _phase++;
            switch (_phase)
            {
            case 1:
                Talk(0);
                break;
            case 3:
                Talk(1);
                break;
            case 4:
                Talk(2);
                break;
            case 5:
                Talk(3);
                break;
            case 6:
                Talk(4);
                break;
            case 7:
                Talk(5);
                break;
            case 8:
                Talk(6);
                break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_milos_gyro_spawnedAI(creature);
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
    new npc_rockjaw_scavenger();
    new npc_hands_springsprocket();
    new npc_milos_gyro_spawned();
}

