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
SDName: Gilneas
SD%Complete: 0
SDComment: Quest support: 0
SDCategory: Gilneas
EndScriptData */

/* ContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "Player.h"


enum eGilneas
{
	NPC_PANICKED_CITIZEN_PHASE1						= 34851,
	NPC_GILNEAS_CITY_GUARD_PHASE1					= 34864,
	NPC_PANICKED_CITIZEN_GATE_PHASE1				= 44086,

	NPC_RAMPAGING_WORGEN_CW_PHASE2					= 34884,
	NPC_PRINCE_LIAM_GREYMANE_PHASE_2				= 34913,
    NPC_GILNEAS_CITY_GUARD_PHASE_2					= 34916,
	NPC_FRIGHTENED_CITIZEN_J_PHASE2					= 34981,
	NPC_RAMPAGING_WORGEN_PHASE_2					= 35660,
	NPC_GILNEAS_EVACUATION_FACING_MARKER			= 35830,
	NPC_FRIGHTENED_CITIZEN_CW_PHASE2				= 35836,

	QUEST_LOCKDOWN									= 14078,
	QUEST_ALL_HELL_BREAKS_LOOSE						= 14093,
	QUEST_EVACUATE_THE_MERCHANT_SQUARE				= 14098,
	QUEST_ROYAL_ORDERS								= 14099,

	SPELL_INVISIBILITY_DETECTION_2					= 49417,
	SPELL_GENERIC_QUEST_INVISIBILITY_DERECTION_1	= 49416,
	SPELL_ENRAGE									= 56646,
    SPELL_SET_PHASE_02								= 59073, 



};

const uint16 PanickedCitizenRandomEmote[5] =
{
	EMOTE_STATE_COWER,
	EMOTE_STATE_TALK,
	EMOTE_ONESHOT_CRY, 
	EMOTE_STATE_SPELL_PRECAST,
	EMOTE_STATE_EXCLAIM,
};


/*######
## npc_panicked_citizen_phase1
######*/

class npc_panicked_citizen_phase1 : public CreatureScript
{
public:
    npc_panicked_citizen_phase1() : CreatureScript("npc_panicked_citizen_phase1") { }

    struct npc_panicked_citizen_phase1AI : public ScriptedAI
    {
        npc_panicked_citizen_phase1AI(Creature* creature) : ScriptedAI(creature)  { }     

        void UpdateAI(const uint32 /*diff*/)
        {           
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

	CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_panicked_citizen_phase1AI (creature);
    }

};

/*######
## npc_gilneas_city_guard_phase1
######*/

class npc_gilneas_city_guard_phase1 : public CreatureScript
{
public:
    npc_gilneas_city_guard_phase1() : CreatureScript("npc_gilneas_city_guard_phase1") { }

    struct npc_gilneas_city_guard_phase1AI : public ScriptedAI
    {
        npc_gilneas_city_guard_phase1AI(Creature* creature) : ScriptedAI(creature)  { }

        uint32		_timer;
        uint8		_phase;
        bool		_nearGate;
		uint8		_say;
		uint8		_emote; 
		Creature*	_citizen;
		
		void Reset()
		{
			_timer = urand(10000, 30000);
            _phase = 0;			 
			_nearGate = false;

			if (me->GetDistance2d(-1430.47f, 1345.55f) < 10.0f)
				_nearGate = true;                           
		}

        void UpdateAI(const uint32 diff)
        {
            if (_nearGate)
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
			 switch (_phase)
             {
				case 0:
                {
					std::list<Creature*> listOfCitizen;
                    me->GetCreatureListWithEntryInGrid(listOfCitizen, NPC_PANICKED_CITIZEN_GATE_PHASE1, 35.0f);

                    if (!listOfCitizen.empty())
					{
						uint8 id = urand(0, listOfCitizen.size() - 1);
                        std::list<Creature*>::iterator itr = listOfCitizen.begin();
                        std::advance(itr, id);                                    

                        if (_citizen = *itr)
                        {							
                            _timer = urand(1000,2000);
                            _emote=urand(0, 4);  
							_say=urand(0,2);
							_citizen->HandleEmoteCommand(PanickedCitizenRandomEmote[_emote]);
							_phase=1;
                            return;
                        }
                     }                     
					 break;
                }
				case 1:
				{
					if (_citizen)
					{
						_citizen->AI()->Talk(_say, me->GetGUID());									
						_timer = urand(4000,7000);
						_phase=2;						
					}
					break;
				}			 
				case 2:
				{
					if (_citizen)
					{						
						Talk(_say , me->GetGUID());						
						_timer = 6000;                            
						_phase=3;				        
					}
					break;
				}
				case 3:
				{
					if (_citizen)
					{						
						_citizen->HandleEmoteCommand(EMOTE_ONESHOT_NONE);				
						_timer = urand(10000, 20000);                            
						_phase=0;				        
					}
					break;
				}
            }			
		}
    };

	CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gilneas_city_guard_phase1AI (creature);
    }
};

/*######
## npc_prince_liam_greymane_phase1
######*/

class npc_prince_liam_greymane_phase1 : public CreatureScript
{
public:
    npc_prince_liam_greymane_phase1() : CreatureScript("npc_prince_liam_greymane_phase1") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_LOCKDOWN)
            if (Creature* citizen = creature->FindNearestCreature(NPC_PANICKED_CITIZEN_PHASE1, 20.0f))
             citizen->AI()->Talk(0);

        return true;
    }

    struct npc_prince_liam_greymane_phase1AI : public ScriptedAI
    {
        npc_prince_liam_greymane_phase1AI(Creature *c) : ScriptedAI(c) {}

        uint32 uiSayTimer;
        uint8 uiSayCount;

        void Reset()
        {
            uiSayTimer = 1000;
            uiSayCount = 0;
        }

        void UpdateAI(const uint32 diff)
        {
            if (uiSayTimer <= diff)
            {
                ++uiSayCount;

                switch (uiSayCount)
                {
                    case 1:
                        Talk(0, me->GetGUID());
                        uiSayTimer = 15000;
                        break;
                    case 2:
                        Talk(1, me->GetGUID());
                        uiSayTimer = 18000;
                        break;
                    case 3:
                        Talk(2, me->GetGUID());
                        uiSayTimer = 25000;
                        uiSayCount = 0;
                        break;
                }
            }
            else
                uiSayTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_prince_liam_greymane_phase1AI (creature);
    }


};

/*######
## npc_lieutenant_walden_phase1
######*/

class npc_lieutenant_walden_phase1 : public CreatureScript
{
public:
    npc_lieutenant_walden_phase1() : CreatureScript("npc_lieutenant_walden_phase1") { }

    bool OnQuestComplete(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_LOCKDOWN)
        {
            player->AddAura(SPELL_GENERIC_QUEST_INVISIBILITY_DERECTION_1, player);
            player->SaveToDB();
        }

        return true;
    }
};

/*######
## npc_rampaging_worgen_phase_2
######*/

class npc_rampaging_worgen_phase_2 : public CreatureScript
{
public:
    npc_rampaging_worgen_phase_2() : CreatureScript("npc_rampaging_worgen_phase_2") { }

    struct npc_rampaging_worgen_phase_2AI : public ScriptedAI
    {
        npc_rampaging_worgen_phase_2AI(Creature *c) : ScriptedAI(c) {_fightWithPrinceLiam=false; _prince_liam=NULL;}

	public:
		bool		_fightWithPrinceLiam;
		uint32		_timer;
		Creature*	_prince_liam;
		
        void Reset()
        {		
			printf("Trigger Reset \n");
			_timer = urand(1800,2200); 
        }
       
		void StartFightWithPrinceLiam(Creature* liam)
		{			
			_prince_liam=liam;
			_fightWithPrinceLiam=true;
			Position pos;
			liam->GetPosition(&pos);
			me->GetMotionMaster()->MoveChase(_prince_liam,1.5f);			
		}
		
        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
               if(_fightWithPrinceLiam)
				   DoFightWithPrinceLiam(diff);
			   else
				   DoShowFight(diff);
			else
				DoMeleeAttackIfReady();
        }

		void DoFightWithPrinceLiam(uint32 diff)
		{
			if (Creature* prince = me->FindNearestCreature (NPC_PRINCE_LIAM_GREYMANE_PHASE_2, 3.0f)) 
             {
				if (_timer <= diff)
				{
					me->SetInCombatWith (_prince_liam);
					_prince_liam->SetInCombatWith (me);			
					me->Attack(_prince_liam, true); 
					//AttackStart(_prince_liam);
					//me->Attack(_prince_liam, true);
					//me->SetFacingTo (me->GetAngle(prince));
					//me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK1H);
					//_timer = urand(1800,2200);
				}
				else 
					_timer -= diff;
			}			
		}

		void DoShowFight(uint32 diff)
		{			
			 if (Creature* guard = me->FindNearestCreature (NPC_GILNEAS_CITY_GUARD_PHASE_2, 3.0f)) 
             {
				if (_timer <= diff)
				{
					me->SetFacingTo (me->GetAngle(guard));
					me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK1H);
					_timer = urand(1800,2200);
				}
				else 
					_timer -= diff;
			}
		}
    };

	CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_rampaging_worgen_phase_2AI (creature);
    }
};

/*######
## npc_gilneas_city_guard_phase_2
######*/

class npc_gilneas_city_guard_phase_2 : public CreatureScript
{
public:
    npc_gilneas_city_guard_phase_2() : CreatureScript("npc_gilneas_city_guard_phase_2") { }

    struct npc_gilneas_city_guard_phase_2AI : public Scripted_NoMovementAI
    {
        npc_gilneas_city_guard_phase_2AI(Creature *c) : Scripted_NoMovementAI(c) { }

		uint32 _timer;   

        void Reset()
        {
            _timer = urand(1800,2200);       
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                DoShowFight(diff);
			else
				DoMeleeAttackIfReady();
        }

		void DoShowFight(uint32 diff)
		{
			 if (Creature* worgen = me->FindNearestCreature (NPC_RAMPAGING_WORGEN_PHASE_2, 3.0f)) 
             {
				if (_timer <= diff)
				{
					me->SetFacingTo (me->GetAngle(worgen));
					me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK1H);
					_timer = urand(1800,2200);
				}
				else 
					_timer -= diff;
			}
		}
    };

	CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gilneas_city_guard_phase_2AI (creature);
    }
};

/*######
## npc_prince_liam_greymane_phase_2
######*/

class npc_prince_liam_greymane_phase_2 : public CreatureScript
{
public:
    npc_prince_liam_greymane_phase_2() : CreatureScript("npc_prince_liam_greymane_phase_2") { }

	bool OnGossipHello(Player* player, Creature* creature) 
	{ 		
		if (npc_prince_liam_greymane_phase_2AI* prince = CAST_AI(npc_prince_liam_greymane_phase_2AI, creature->AI()))
                prince->StartEvent(player);

		return false; 	
	}

    bool OnQuestAccept(Player* player, Creature* creature, const Quest* quest)
    {		
        if (quest->GetQuestId() ==  QUEST_ROYAL_ORDERS)
        {
            player->RemoveAura(SPELL_GENERIC_QUEST_INVISIBILITY_DERECTION_1);
            player->CastSpell(player, SPELL_INVISIBILITY_DETECTION_2, false);
            player->SaveToDB();
        }
		
        return true;
    }
 
    struct npc_prince_liam_greymane_phase_2AI : public ScriptedAI // Scripted_NoMovementAI
    {
        npc_prince_liam_greymane_phase_2AI(Creature *c) : ScriptedAI(c) { }

		uint32	_timer;
		uint32	_phase;
		Player* _player;
		Creature* _worgen;

        void Reset()
        {			
            _timer=0; _phase=0; _player=NULL; _worgen=NULL;
        }

		void StartEvent(Player* player)
		{			
			_player=player;
			if (_phase==0)
			{
				_timer=1000; _phase=1;			
			}
		}

        void UpdateAI(const uint32 diff)
        {

			if (_timer <= diff)
            {
               DoWork();
			   _timer=1000;
            }
            else
                _timer -= diff;

            if (!UpdateVictim())
               return;
			
			DoMeleeAttackIfReady();
        }

		void DoWork()
		{
			if (!_player) return;
			if (me->GetDistance(_player) > 35.0f)			
				return;
			
			if (_player->GetQuestStatus(QUEST_ALL_HELL_BREAKS_LOOSE) != QUEST_STATUS_INCOMPLETE)			
				return;
			
			if (_worgen)
			{
				if (_worgen->IsAlive()) return;
				if (_worgen->IsDead()) 
				{
					_worgen->DespawnOrUnsummon();
					_worgen=NULL;
					return;
				}
			}
			if (_worgen = me->SummonCreature(NPC_RAMPAGING_WORGEN_PHASE_2, -1474.3f, 1396.6f, 35.556f, 0.27f, TEMPSUMMON_TIMED_DESPAWN, 20000))
			{					
				CAST_AI(npc_rampaging_worgen_phase_2::npc_rampaging_worgen_phase_2AI, _worgen->AI())->StartFightWithPrinceLiam(me);
			}			
		}
    };

	CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_prince_liam_greymane_phase_2AI (creature);
    }

};




void AddSC_gilneas_city()
{
	new npc_gilneas_city_guard_phase1();
    new npc_panicked_citizen_phase1();
    new npc_prince_liam_greymane_phase1();
    new npc_lieutenant_walden_phase1();
	new npc_rampaging_worgen_phase_2();
	new npc_gilneas_city_guard_phase_2();
	new npc_prince_liam_greymane_phase_2();
	//new npc_frightened_citizen_j();
	//new npc_frightened_citizen_cw();
	//new npc_rampaging_worgen_cw();
	//new go_merchant_square_door_phase2();
};