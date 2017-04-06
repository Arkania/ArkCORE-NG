/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2017 ArkCORE <http://www.arkania.net/>
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
SDName: Gnomeregan
SD%Complete: 0
SDComment: Quest Support:
SDCategory: Gnomeregan
EndScriptData */

/* ContentData

EndContentData */

#include "script_helper.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "Vehicle.h"


class npc_nevin_twistwrench_45966 : public CreatureScript
{
public:
	npc_nevin_twistwrench_45966() : CreatureScript("npc_nevin_twistwrench_45966") { }
	
	enum eNpc
	{
		SPELL_IRRADIATE = 80653,
		QUEST_DECONTAMINATION = 27635
	};
	
	struct npc_nevin_twistwrench_45966AI : public ScriptedAI
	{
		npc_nevin_twistwrench_45966AI(Creature* creature) : ScriptedAI(creature) { }
		
		uint32 uiTimer;
		
		void Reset()
        {
            uiTimer = 0;
        }
		
		void UpdateAI(const uint32 diff)
        {
			if(uiTimer <= diff)
			{
				std::list<Player*> playerList = me->FindNearestPlayers(10.0f, true);
                    for (std::list<Player*>::const_iterator itr = playerList.begin(); itr != playerList.end(); ++itr)
                        if (((*itr)->GetQuestStatus(QUEST_DECONTAMINATION) == QUEST_STATUS_NONE) && (!(*itr)->HasAura(SPELL_IRRADIATE)))
							(*itr)->CastSpell((*itr), SPELL_IRRADIATE, true);
							
				uiTimer = 100;
			}
			else uiTimer -= diff;
		}
		
	};
	
	CreatureAI *GetAI(Creature *Creature) const
    {
        return new npc_nevin_twistwrench_45966AI(Creature);
    }
	
};




class npc_carvo_blastbolt_47250 : public CreatureScript
{
public:
    npc_carvo_blastbolt_47250() : CreatureScript("npc_carvo_blastbolt_47250") { }
	
	enum eNpc
	{
		QUEST_WITHDRAW_TO_THE_LOADING_ROOM =  28169,
		NPC_IMUN_AGENT                     =  47836,
		MOVE_IMUN_AGENT					   =  15459904	
	};
	
    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_WITHDRAW_TO_THE_LOADING_ROOM)
		{
			player->SummonCreature(NPC_IMUN_AGENT, -4981.25f, 780.992f, 288.485f, 3.316f, TEMPSUMMON_MANUAL_DESPAWN, 0);
			if (Creature* agent = creature->FindNearestCreature(NPC_IMUN_AGENT, 5.0f))
            {
				agent->SetSpeed(MOVE_RUN, 1.0f);
				agent->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_NOT_SELECTABLE);
				agent->SetReactState(REACT_PASSIVE);
                agent->AI()->Talk(0, player);
				agent->GetMotionMaster()->MovePath(MOVE_IMUN_AGENT, false);
			}
		}
  
        return true;
    }
};





class npc_sanitron_500_46185 : public CreatureScript
{
public:
	npc_sanitron_500_46185() : CreatureScript("npc_sanitron_500_46185") { }
	
	enum eNpc
	{

		SPELL_CANNON_BURST = 86080,
		SPELL_DECONTAMINATE_STAGE_1 = 86075,
		SPELL_DECONTAMINATE_STAGE_2 = 86086,
		SPELL_IRRADIATE = 80653,

		SPELL_EXPLOSION = 30934,

		QUEST_DECONTAMINATION = 27635,

		NPC_DECONTAMINATION_BUNNY = 46165,
		NPC_CLEAN_CANNON = 46208,
		NPC_SAFE_TECHNICAN = 46230
	};
	
	bool OnGossipHello(Player* player, Creature* creature)
	{
		if(player->GetQuestStatus(QUEST_DECONTAMINATION) == QUEST_STATUS_INCOMPLETE)
		{
			player->HandleEmoteCommand(0);
            Vehicle *vehicle = creature->GetVehicleKit();
            player->EnterVehicle(creature->ToUnit(), 0);
			creature->AI()->Talk(0);
		}
		return true;
	}
	
	struct npc_sanitron_500_46185AI : public ScriptedAI
    {
        npc_sanitron_500_46185AI(Creature* pCreature) : ScriptedAI(pCreature), vehicle(pCreature->GetVehicleKit())
        {
            assert(vehicle);
        }
		
        Vehicle *vehicle;
        Creature* Technician;
        Creature::Unit* Bunny[4];
        Creature::Unit* Cannon[4];
        std::list<Unit*> targets;
        uint32 uiTimer;
        uint32 uiRespawnTimer;
        uint8 uiPhase;

        void Reset()
        {
            uiTimer = 0;
            uiRespawnTimer = 6000;
            uiPhase = 0;
        }

        Unit* unit(uint32 entry, uint32 range, bool alive)
        {
            if (Unit* unit = me->FindNearestCreature(entry, float(range), alive))
                if (Unit* unit2 = sObjectAccessor->GetCreature(*me, unit->GetGUID()))
                    return unit2;
        }

        void GetTargets()
        {
			std::list<Creature*> targets = me->FindAllCreaturesInRange(100.0f);
            if (!targets.empty())
                for (std::list<Creature*>::const_iterator iter = targets.begin(); iter != targets.end(); ++iter)
                {
                    if ((*iter)->GetTypeId() != TYPEID_PLAYER)
                    {
                        switch ((*iter)->GetEntry())
                        {
                        case 46230:
                            if ((*iter)->GetDistance2d(-5165.209961f, 713.809021f) <= 1)
                                Technician = (*iter);
                            break;
                        case 46165:
                            if ((*iter)->GetDistance2d(-5164.919922f, 723.890991f) <= 1)
                                Bunny[0] = (*iter);
                            if ((*iter)->GetDistance2d(-5182.560059f, 726.656982f) <= 1)
                                Bunny[1] = (*iter);
                            if ((*iter)->GetDistance2d(-5166.350098f, 706.336975f) <= 1)
                                Bunny[2] = (*iter);
                            if ((*iter)->GetDistance2d(-5184.040039f, 708.405029f) <= 1)
                                Bunny[3] = (*iter);
                            break;
                        case 46208:
                            if ((*iter)->GetDistance2d(-5164.209961f, 719.267029f) <= 1)
                                Cannon[0] = (*iter);
                            if ((*iter)->GetDistance2d(-5165.000000f, 709.453979f) <= 1)
                                Cannon[1] = (*iter);
                            if ((*iter)->GetDistance2d(-5183.830078f, 722.093994f) <= 1)
                                Cannon[2] = (*iter);
                            if ((*iter)->GetDistance2d(-5184.470215f, 712.554993f) <= 1)
                                Cannon[3] = (*iter);
                            break;
                        }
                    }
                }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!vehicle->HasEmptySeat(0))
                if (uiTimer <= diff)
                {
					if (Player* player = vehicle->GetPassenger(0)->ToPlayer())
					{
						switch (uiPhase)
						{
						case 0:
							++uiPhase;
							uiTimer = 2500;
							break;
						case 1:
							me->GetMotionMaster()->MovePoint(1, -5173.34f, 730.11f, 294.25f);
							GetTargets();
							++uiPhase;			
							uiTimer = 3000;
							break;
						case 2:
							if (Bunny[0] && Bunny[1])
							{
								Bunny[0]->CastSpell(player, SPELL_DECONTAMINATE_STAGE_1, true);
								Bunny[1]->CastSpell(player, SPELL_DECONTAMINATE_STAGE_1, true);
							} 
							++uiPhase;
							uiTimer = 1500;
							break;
						case 3:
							me->GetMotionMaster()->MovePoint(2, -5173.72f, 725.7f, 294.03f); 
							++uiPhase;
							uiTimer = 500;
							break;
						case 4:
							me->GetMotionMaster()->MovePoint(3, -5174.57f, 716.45f, 289.53f); 
							++uiPhase;
							uiTimer = 3000;
							break;
						case 5:
							if (Cannon[0] && Cannon[1] && Cannon[2] && Cannon[3])
							{
								Cannon[0]->CastSpell(player, SPELL_CANNON_BURST, true);
								Cannon[1]->CastSpell(player, SPELL_CANNON_BURST, true);
								Cannon[2]->CastSpell(player, SPELL_CANNON_BURST, true);
								Cannon[3]->CastSpell(player, SPELL_CANNON_BURST, true);
							} 
							++uiPhase;
							uiTimer = 4000;
							break;
						case 6:
							if (Technician)
							Technician->AI()->Talk(0);
							me->GetMotionMaster()->MovePoint(4, -5175.04f, 707.2f, 294.4f);
							++uiPhase;
							uiTimer = 4000;
							break;
						case 7:
							if (Bunny[2] && Bunny[3])
							{   
								Bunny[2]->CastSpell(player, SPELL_DECONTAMINATE_STAGE_2, true);
								Bunny[3]->CastSpell(player, SPELL_DECONTAMINATE_STAGE_2, true);
							}
							player->RemoveAurasDueToSpell(SPELL_IRRADIATE);
							++uiPhase;
							uiTimer = 1000;
							break;
						case 8:
							player->CompleteQuest(QUEST_DECONTAMINATION);
							Talk(1);
							me->GetMotionMaster()->MovePoint(5, -5175.61f, 700.38f, 290.89f);
							++uiPhase;
							uiTimer = 3000;
							break;
						case 9:
							Talk(2);
							me->CastSpell(me, SPELL_EXPLOSION);
							++uiPhase;
							uiTimer = 1000;
							break;
						case 10:
							vehicle->RemoveAllPassengers();
							me->SetDeathState(JUST_DIED);
							++uiPhase;
							uiTimer = 0;
							break;
						}
					}
					
                }
                else uiTimer -= diff;
        }
    };

    CreatureAI *GetAI(Creature *creature) const
    {
        return new npc_sanitron_500_46185AI(creature);
    }
	
};


class npc_gnomeregan_torben_46293 : public CreatureScript
{
public:
    npc_gnomeregan_torben_46293() : CreatureScript("npc_gnomeregan_torben_46293") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->ADD_GOSSIP_ITEM_DB(12104, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF + 1)
        {
            player->TeleportTo(0, -5201.58f, 477.98f, 388.47f, 5.13f);
            player->PlayerTalkClass->SendCloseGossip();
        }
        return true;
    }
};




void AddSC_zone_gnomeregan()
{
	new npc_nevin_twistwrench_45966();
	new npc_carvo_blastbolt_47250();
	new npc_sanitron_500_46185();
	new npc_gnomeregan_torben_46293();
}

