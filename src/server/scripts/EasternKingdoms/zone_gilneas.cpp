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
    NPC_PANICKED_CITIZEN_PHASE1                    = 34851,
    NPC_GILNEAS_CITY_GUARD_PHASE1                  = 34864,
    NPC_PANICKED_CITIZEN_GATE_PHASE1               = 44086,
    NPC_PRINCE_LIAM_GREYMANE_PHASE1                = 34850,
    NPC_LIEUTNANT_WALDEN_PHASE1                    = 34863,

    NPC_RAMPAGING_WORGEN_CW_PHASE2                 = 34884,
    NPC_PRINCE_LIAM_GREYMANE_PHASE2                = 34913,
    NPC_GILNEAS_CITY_GUARD_PHASE2                  = 34916,
    NPC_FRIGHTENED_CITIZEN_J_PHASE2                = 34981,
    NPC_RAMPAGING_WORGEN_PHASE2                    = 35660,
    NPC_GILNEAS_EVACUATION_FACING_MARKER           = 35830,
    NPC_FRIGHTENED_CITIZEN_CW_PHASE2               = 35836,

    NPC_GWEN_ARMSTEAD_PHASE4                       = 35840,
    NPC_LORD_DARIUS_CROWLEY_PHASE4                 = 35077,
    NPC_BLOODFANG_WORGEN_PHASE4                    = 35118,
    NPC_TOBIAS_MISTMANTLE_PHASE4                   = 35124,
    NPC_WORGEN_RUNT_PHASE4                         = 35456,

    NPC_JOSIAH_AVERY_HUMAN_PHASE4                  = 35369,
    NPC_JOSIAH_AVERY_WORGEN_PHASE8                 = 35370,
    NPC_LORNA_CROWLEY_PHASE8                       = 35378,

    QUEST_LOCKDOWN                                 = 14078,
    QUEST_SOMETHINGS_AMISS                         = 14091,
    QUEST_ALL_HELL_BREAKS_LOOSE                    = 14093,
    QUEST_EVACUATE_THE_MERCHANT_SQUARE             = 14098,
    QUEST_ROYAL_ORDERS                             = 14099,
    QUEST_BY_THE_SKIN_OF_HIS_TEETH                 = 14154,
    QUEST_THE_REBEL_LORD_ARSENAL                   = 14159,

    SPELL_INVISIBILITY_DETECTION_2                 = 49417,
    SPELL_GENERIC_QUEST_INVISIBILITY_DERECTION_1   = 49416,
    SPELL_ENRAGE                                   = 56646,
    SPELL_SET_PHASE_02                             = 59073, // set phase 2
    SPELL_SET_PHASE_04                             = 59074, // set phase 4
    SPELL_SET_PHASE_08                             = 59087, // set phase 8

    SPELL_GILNEAS_PRISON_PERIODIC_FORCECAST        = 66914,


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

        void UpdateAI(uint32 diff)
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
        uint8       _emote;
		Creature*	_citizen;
		
		void Reset()
		{
			_timer = urand(10000, 30000);
            _phase = 0;			 
			_nearGate = false;

			if (me->GetDistance2d(-1430.47f, 1345.55f) < 10.0f)
				_nearGate = true;                           
		}

        void UpdateAI(uint32 diff)
        {
            if (_nearGate)
                if (_timer <= diff)
                {
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
        npc_prince_liam_greymane_phase1AI(Creature* creature) : ScriptedAI(creature) {}

        uint32  _timer;        
        uint8   _phase;

        void Reset()
        {
            _timer = 1000;            
            _phase=0;
        }

        void UpdateAI(uint32 diff)
        {
            Player* player = me->FindNearestPlayer(30,true);

            if (_timer <= diff)
                DoWork(player);
            else
                _timer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();

        }
         

        void DoWork(Player* player)
        {
            _timer=5000;
            switch(_phase)
            {
                case 0:
                    if (player)
                    { 
                        _phase=1; 
                        _timer=75000;                    
                    }
                    break;
                case 1:
                     Talk(0);
                    _timer = 15000;
                    _phase=2;
                    break;
                case 2:
                     Talk(1);
                    _timer = 18000;
                    _phase=3;
                    break;
                case 3:
                     Talk(2);
                    _timer = 25000;
                    _phase=4;
                    break;
                case 4:
                    _timer = 30000;
                    _phase=1;
                    if (!player)
                        _phase=0;
            }
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

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_SOMETHINGS_AMISS)
        {
            player->AddAura(SPELL_GENERIC_QUEST_INVISIBILITY_DERECTION_1, player);
            player->CastSpell(player, SPELL_SET_PHASE_02, false);
            player->SaveToDB();
        }
        return true;
    }
};

/*######
## phase 2
######*/

/*######
## npc_rampaging_worgen_phase2
## ToDo: The fight with Prince Liam is not realy finish.. 
######*/

class npc_rampaging_worgen_phase2 : public CreatureScript
{
public:
    npc_rampaging_worgen_phase2() : CreatureScript("npc_rampaging_worgen_phase2") { }

    struct npc_rampaging_worgen_phase2AI : public ScriptedAI
    {
        npc_rampaging_worgen_phase2AI(Creature* creature) : ScriptedAI(creature) {_fightWithPrinceLiam=false; _liam=NULL;}

	public:
		bool		_fightWithPrinceLiam;
        bool        _enrage;
		uint32		_timer;
		Creature*	_liam;
		
        void Reset()
        {					
			_timer = urand(1800,2200); 
            _enrage = false;
        }
       
		void StartFightWithPrinceLiam(Creature* liam)
		{				
			_liam=liam;
			_fightWithPrinceLiam=true;
			Position pos;			
			liam->GetNearPosition(pos, 1.5f, 0.0f);
			me->GetMotionMaster()->MovePoint(1005, pos);			
		}
		
        void MovementInform(uint32 /*type*/, uint32 id) 
		{ 
			if (_fightWithPrinceLiam && id==1005)
			{								
                me->setFaction(2179);
                me->CombatStart(_liam);
			}		
		}

        void DamageTaken(Unit* /*pDone_by*/, uint32& /*uiDamage*/) 
        { 
            if (me->GetHealthPct() < 30 && !_enrage)
            { 
                me->CastSpell(me,SPELL_ENRAGE);
                _enrage = true;
            }
        }

        void UpdateAI(uint32 diff)
        {            
            if (!UpdateVictim())
                DoShowFight(diff);
			else
				DoMeleeAttackIfReady();
        }

		void DoShowFight(uint32 diff)
		{			
           
				if (_timer <= diff)
				{
                    if (Creature* guard = me->FindNearestCreature (NPC_GILNEAS_CITY_GUARD_PHASE2, 3.0f))
                    {
					    me->SetFacingTo (me->GetAngle(guard));
					    me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK1H);	                       
                    }
                    _timer = urand(1500,2500);
				}
                else
					_timer -= diff;			
		}
    };

	CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_rampaging_worgen_phase2AI (creature);
    }
};

/*######
## npc_gilneas_city_guard_phase2
######*/

class npc_gilneas_city_guard_phase2 : public CreatureScript
{
public:
    npc_gilneas_city_guard_phase2() : CreatureScript("npc_gilneas_city_guard_phase2") { }

    struct npc_gilneas_city_guard_phase2AI : public ScriptedAI
    {
        npc_gilneas_city_guard_phase2AI(Creature* creature) : ScriptedAI(creature) { }

		uint32 _timer;   

        void Reset()
        {
            _timer = urand(1800,2200);       
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                DoShowFight(diff);
			else
				DoMeleeAttackIfReady();
        }

		void DoShowFight(uint32 diff)
		{
            if (Creature* worgen = me->FindNearestCreature (NPC_RAMPAGING_WORGEN_PHASE2, 3.0f))
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
			if (Creature* worgen = me->FindNearestCreature (NPC_BLOODFANG_WORGEN_PHASE4, 3.0f)) 
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
        return new npc_gilneas_city_guard_phase2AI (creature);
    }
};

/*######
## npc_prince_liam_greymane_phase2
######*/

class npc_prince_liam_greymane_phase2 : public CreatureScript
{
public:
    npc_prince_liam_greymane_phase2() : CreatureScript("npc_prince_liam_greymane_phase2") { }

	bool OnGossipHello(Player* player, Creature* creature) 
	{ 		
		if (npc_prince_liam_greymane_phase2AI* prince = CAST_AI(npc_prince_liam_greymane_phase2AI, creature->AI()))
            prince->StartEvent(player);

		return false; 	
	}

    bool OnQuestAccept(Player* player, Creature* creature, const Quest* quest)
    {
        if (quest->GetQuestId() == QUEST_ROYAL_ORDERS)
        {
            player->RemoveAura(SPELL_GENERIC_QUEST_INVISIBILITY_DERECTION_1);
            player->AddAura(SPELL_INVISIBILITY_DETECTION_2, player);
            player->CastSpell(player, SPELL_SET_PHASE_04, false);
            player->SaveToDB();
        }
		
        return true;
    }
 
    struct npc_prince_liam_greymane_phase2AI : public ScriptedAI // ScriptedAI
    {
        npc_prince_liam_greymane_phase2AI(Creature* creature) : ScriptedAI(creature) { }

        uint32 _timer;
        uint32 _phase;
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

        void UpdateAI(uint32 diff)
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
			if (_worgen = me->SummonCreature(NPC_RAMPAGING_WORGEN_PHASE2, -1474.3f, 1396.6f, 35.556f, 0.27f, TEMPSUMMON_TIMED_DESPAWN, 20000))
            {
				CAST_AI(npc_rampaging_worgen_phase2::npc_rampaging_worgen_phase2AI, _worgen->AI())->StartFightWithPrinceLiam(me);
            }
        }
    };

	CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_prince_liam_greymane_phase2AI (creature);
    }

};

/*######
## npc_frightened_citizen_j_phase2
######*/

class npc_frightened_citizen_j_phase2 : public CreatureScript
{
public:
    npc_frightened_citizen_j_phase2() : CreatureScript("npc_frightened_citizen_j_phase2") {}

    struct npc_frightened_citizen_j_phase2AI : public npc_escortAI
    {
        npc_frightened_citizen_j_phase2AI(Creature *c) : npc_escortAI(c) { }

        uint32  _timer;
        bool	_pause;

        void WaypointReached(uint32 point)
        {			
            if (point == 2)
            {
                if (me->IsSummon())
                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        if (Player* player = summoner->ToPlayer())
						{							
                            player->KilledMonsterCredit(NPC_GILNEAS_EVACUATION_FACING_MARKER, 0);							
							SetEscortPaused(true);
							_pause = true;
							_timer=4000;
							me->SetFacingTo(me->GetAngle(player));							
							Talk(0);     
						}                                               
            }
        }

        void UpdateAI(uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (_pause)
                if (_timer <= diff)
                {
                    _pause = false;
                    SetEscortPaused(false);
                }
                else
                    _timer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_frightened_citizen_j_phase2AI(creature);
    }
};

/*######
## npc_frightened_citizen_cw_phase2
######*/

class npc_frightened_citizen_cw_phase2 : public CreatureScript
{
public:
    npc_frightened_citizen_cw_phase2() : CreatureScript("npc_frightened_citizen_cw_phase2") {}

    struct npc_frightened_citizen_cw_phase2AI : public npc_escortAI
    {
        npc_frightened_citizen_cw_phase2AI(Creature *c) : npc_escortAI(c) { }

        uint32  _timer;
        bool	_pause;	

        void WaypointReached(uint32 point)
        {			
            if (point == 2)
            {
                if (me->IsSummon())
                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        if (Player* player = summoner->ToPlayer())
						{							
                            player->KilledMonsterCredit(NPC_GILNEAS_EVACUATION_FACING_MARKER, 0);							
							SetEscortPaused(true);				
							_pause = true;
							_timer=1000;
							me->SetFacingTo(me->GetAngle(player));	
                            Talk(0);
						}                                                  
            }
        }

        void UpdateAI(uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (_pause)
                if (_timer <= diff)
                {
                    _pause = false;
                    SetEscortPaused(false);
                }
                else
                    _timer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_frightened_citizen_cw_phase2AI(creature);
    }
};

/*######
## npc_rampaging_worgen_cw_phase2
######*/

class npc_rampaging_worgen_cw_phase2 : public CreatureScript
{
public:
    npc_rampaging_worgen_cw_phase2() : CreatureScript("npc_rampaging_worgen_cw_phase2") {}

    struct npc_rampaging_worgen_cw_phase2AI : public npc_escortAI
    {
        npc_rampaging_worgen_cw_phase2AI(Creature* creature) : npc_escortAI(creature)
        {
            creature->SetReactState(REACT_PASSIVE);
            uiPauseTimer = 4000;
            enrage = false;
            pause = true;
        }

        uint32  uiPauseTimer;
        bool    pause;
        bool    enrage;

        void WaypointReached(uint32 point)
        {
            if (point == 1)
            {
                me->SetReactState(REACT_AGGRESSIVE);
                me->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
                if (me->IsSummon())
                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        AttackStart(summoner);
                    else
                        me->DespawnOrUnsummon();
            }
        }

        void UpdateAI(uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (pause)
                if (uiPauseTimer <= diff)
                {
                    pause = false;
                    SetEscortPaused(false);
                }
                else
                    uiPauseTimer -= diff;

            if (!UpdateVictim())
                return;

            if (!enrage && me->HealthBelowPct(30))
            {
                DoCast(SPELL_ENRAGE);
                enrage = true;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_rampaging_worgen_cw_phase2AI(creature);
    }
};

/*######
## go_merchant_square_door_phase2
######*/

class go_merchant_square_door_phase2 : public GameObjectScript
{
public:
    go_merchant_square_door_phase2() : GameObjectScript("go_merchant_square_door_phase2") { }

	enum eGo_merchant_square_door_phase2
	{   
        ACTION_JUST_CITIZEN = 1,
        ACTION_CITIZEN_AND_WORGEN = 2,
	};

    void SummonQuestCreature(uint32 entry, bool IsCitizen, GameObject* go, Player* player)
    {
        if (!player)
            return;

        float x, y;
        go->GetNearPoint2D(x, y, 2.8f, go->GetOrientation() + M_PI * 0.75f);

        if (Creature* creature = player->SummonCreature(entry, x, y, go->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 18000))
        {
            creature->SetPhaseMask(2, true);
            creature->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
            npc_escortAI* npc_escort = NULL;
			
			switch (creature->GetEntry())
			{
            case NPC_FRIGHTENED_CITIZEN_J_PHASE2:
                npc_escort = CAST_AI(npc_frightened_citizen_j_phase2::npc_frightened_citizen_j_phase2AI, creature->AI());
                break;
            case NPC_FRIGHTENED_CITIZEN_CW_PHASE2:
                npc_escort = CAST_AI(npc_frightened_citizen_cw_phase2::npc_frightened_citizen_cw_phase2AI, creature->AI());
                break;
            case NPC_RAMPAGING_WORGEN_CW_PHASE2:
                npc_escort = CAST_AI(npc_rampaging_worgen_cw_phase2::npc_rampaging_worgen_cw_phase2AI, creature->AI());
                break;
			}
           
            if (!npc_escort)			
			    return;
			            
            float x, y, z = creature->GetPositionZ(), o = go->GetOrientation();
            go->GetNearPoint2D(x, y, 1.0f, o + M_PI);
            npc_escort->AddWaypoint(0, x, y, z);
            go->GetNearPoint2D(x, y, 3.0f, o);
            npc_escort->AddWaypoint(1, x, y, z);

            if (IsCitizen)
            {
				go->GetNearPoint2D(x, y, 5.0f, o);
				npc_escort->AddWaypoint(2, x, y, z); 				
				go->GetNearPoint2D(x, y, 15.0f, o);
				npc_escort->AddWaypoint(3, x, y, z);               
            }

            npc_escort->Start(false, true);
            npc_escort->SetDespawnAtEnd(IsCitizen);
            npc_escort->SetEscortPaused(!IsCitizen);
        }
    }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        uint8 roll = urand(ACTION_JUST_CITIZEN, ACTION_CITIZEN_AND_WORGEN);

        switch (roll)
        {
        case ACTION_JUST_CITIZEN:
            SummonQuestCreature(NPC_FRIGHTENED_CITIZEN_J_PHASE2, true, go, player);
            break;
        case ACTION_CITIZEN_AND_WORGEN:
            SummonQuestCreature(NPC_FRIGHTENED_CITIZEN_CW_PHASE2, true, go, player);
            SummonQuestCreature(NPC_RAMPAGING_WORGEN_CW_PHASE2, false, go, player);
            break;
        }

        return false;
    }

};

/*######
## phase 4
######*/

/*######
## npc_bloodfang_worgen_phase4
######*/

class npc_bloodfang_worgen_phase4 : public CreatureScript
{
public:
    npc_bloodfang_worgen_phase4() : CreatureScript("npc_bloodfang_worgen_phase4") { }

    struct npc_bloodfang_worgen_phase4AI : public ScriptedAI
    {
        npc_bloodfang_worgen_phase4AI(Creature *c) : ScriptedAI(c) {}
	
        uint32 _timer;
		
        void Reset()
        {		
            //printf("Trigger reset \n");
			_timer = urand(1800,2200); 
        }
       

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
				DoShowFight(diff);
			else
				DoMeleeAttackIfReady();
        }

		void DoShowFight(uint32 diff)
		{			
            if (Creature* guard = me->FindNearestCreature (NPC_GILNEAS_CITY_GUARD_PHASE2, 3.0f))
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
        return new npc_bloodfang_worgen_phase4AI (creature);
    }
};

/*######
## npc_gwen_armstead_phase4
######*/

class npc_gwen_armstead_phase4 : public CreatureScript
{
public:
    npc_gwen_armstead_phase4() : CreatureScript("npc_gwen_armstead_phase4") { }

    struct npc_gwen_armstead_phase4AI : public ScriptedAI
    {
        npc_gwen_armstead_phase4AI(Creature* creature) : ScriptedAI(creature) { }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gwen_armstead_phase4AI (creature);
    }
};

/*######
## npc_tobias_mistmantle_phase4
######*/

class npc_tobias_mistmantle_phase4 : public CreatureScript
{
public:
    npc_tobias_mistmantle_phase4() : CreatureScript("npc_tobias_mistmantle_phase4") { }

    struct npc_tobias_mistmantle_phase4AI : public ScriptedAI
    {
        npc_tobias_mistmantle_phase4AI(Creature* creature) : ScriptedAI(creature)  { }     

        void UpdateAI(uint32 diff)
        {           
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

	CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tobias_mistmantle_phase4AI (creature);
    }
};

/*######
## npc_worgen_runt_phase4
######*/

class npc_worgen_runt_phase4 : public CreatureScript
{
public:
    npc_worgen_runt_phase4() : CreatureScript("npc_worgen_runt_phase4") { }

    struct npc_worgen_runt_phase4AI : public npc_escortAI
    {
        npc_worgen_runt_phase4AI(Creature* creature) : npc_escortAI(creature)  { }     

		void WaypointReached(uint32 point)
        {			
			switch (point)
			{
			case 0:
				me->SetCanFly(true);
			case 1:
				me->SetCanFly(false);
			case 2:
				me->SetReactState(REACT_AGGRESSIVE);
				me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
				if (me->IsSummon())
					if (Unit* summoner = me->ToTempSummon()->GetSummoner())
					{
						me->CombatStart(summoner);
						me->AddThreat(summoner, 100500);
					}
			}
		}

	    void UpdateAI(uint32 diff)
        {   
			npc_escortAI::UpdateAI(diff);

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

	CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_worgen_runt_phase4AI (creature);
    }
};

/*######
## npc_lord_darius_crowley_phase4
######*/

class npc_lord_darius_crowley_phase4 : public CreatureScript
{
public:
    npc_lord_darius_crowley_phase4() : CreatureScript("npc_lord_darius_crowley_phase4") { }

	bool OnQuestAccept(Player* player, Creature* creature, const Quest* quest)
    {		
        if (quest->GetQuestId() == QUEST_BY_THE_SKIN_OF_HIS_TEETH)
        {
			creature->CastSpell(player, SPELL_GILNEAS_PRISON_PERIODIC_FORCECAST, true);
            CAST_AI(npc_lord_darius_crowley_phase4AI, creature->AI())->StartWorgenFight(player);
        }		
        return true;
    }

    struct npc_lord_darius_crowley_phase4AI : public ScriptedAI
    {
        npc_lord_darius_crowley_phase4AI(Creature* creature) : ScriptedAI(creature)  
		{ 
			_eventTimer=0; _phase=0; _timer=0; _count=0; _wave=0;
		}     

        uint32  _eventTimer;
        uint32  _timer;
        uint32  _phase;
        uint32  _count;
        uint32  _wave;
        Player* _player;

		void StartWorgenFight(Player* player)
		{						
			_eventTimer=120000;				
			_timer=1000;
			_player=player;
			_phase=1;
			_count=0; 
			_wave=0;
		}

        void UpdateAI(uint32 diff)
        {    				
			if (_phase > 0)
			{				
				if (_timer <= diff)
				{
                    _timer=1000;
					SummonWorgen();					
				}
				else
					_timer -= diff;				

				if (_eventTimer <= diff)
					EndOfEvent();
				else
					_eventTimer -= diff;
			}

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

		void SummonWorgen()
		{																
			_count++;
			if (_count > 2 && _eventTimer > 30000)
			{
				_count=0;				
				if (urand(0,1) == 0)
					SummonWorgenPosA();
				else
					SummonWorgenPosB();
			}

			switch (_phase)
			{
            case 1: // first wave
                _wave++;
                SummonWorgenPosA();
                if (_wave>=8) _phase=2;
                break;
            case 2:
                if (_eventTimer < 70000)
                {_phase=3; _wave=0; }
            case 3: // second wave
                _wave++;
                SummonWorgenPosB();
                if (_wave>=7) _phase=4;
                break;
            case 4:
                break;
			}

		}	

		void EndOfEvent()
		{
			_phase=0; _wave=0; _count=0;
			std::list<Creature*> listOfWorgen;
            me->GetCreatureListWithEntryInGrid(listOfWorgen, NPC_WORGEN_RUNT_PHASE4, 35.0f);

            for (std::list<Creature*>::const_iterator itr = listOfWorgen.begin(); itr != listOfWorgen.end(); ++itr )
			{				
                if ((*itr)->IsAlive())
					(*itr)->DisappearAndDie();			
			}			          
		}

		float RandomFloat(float min, float max)
		{
			assert(max > min); 
			float random = ((float) rand()) / (float) RAND_MAX;

			float range = max - min;  
			return (random * range) + min;
		}

		void SummonWorgenPosA()
		{
			float x = RandomFloat(-3.0f, 1.0f);
			float y = RandomFloat(-3.0f, 1.0f);

			if (Creature* worgen = me->SummonCreature(NPC_WORGEN_RUNT_PHASE4, -1626.2f, 1491.5f, 73.3f))
            {
				if (npc_escortAI* npc_escort = CAST_AI(npc_worgen_runt_phase4::npc_worgen_runt_phase4AI, worgen->AI()))
				{
					npc_escort->AddWaypoint (0, -1642.8f, 1476.8f, 61.35f);
					npc_escort->AddWaypoint (1, -1671.9f + x, 1448.4f + y, 52.52f);
					npc_escort->AddWaypoint (2, -1676.3f + x, 1444.5f + y, 52.29f);
					npc_escort->Start(false, true);
				}												
			}			
		}
		void SummonWorgenPosB()
		{
			float x = RandomFloat(-3.0f, 1.0f);
			float y = RandomFloat(-3.0f, 1.0f);

			if (Creature* worgen = me->SummonCreature(NPC_WORGEN_RUNT_PHASE4, -1718.1f, 1505.3f, 56.1f))
			{
				if (npc_escortAI* npc_escort = CAST_AI(npc_worgen_runt_phase4::npc_worgen_runt_phase4AI, worgen->AI()))
				{
					npc_escort->AddWaypoint (0, -1717.7f, 1486.2f, 57.41f);
					npc_escort->AddWaypoint (1, -1704.3f + x, 1472.8f + y, 52.32f);
					npc_escort->AddWaypoint (2, -1680.4f + x, 1447.5f + y, 52.29f);
					npc_escort->Start(false, true);
				}
			}
		}
	};

	CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lord_darius_crowley_phase4AI (creature);
    }

};


void AddSC_gilneas_city()
{
	new npc_gilneas_city_guard_phase1();
    new npc_panicked_citizen_phase1();
    new npc_prince_liam_greymane_phase1();
    new npc_lieutenant_walden_phase1();

	new npc_rampaging_worgen_phase2();
	new npc_gilneas_city_guard_phase2();
	new npc_prince_liam_greymane_phase2();
	new npc_frightened_citizen_j_phase2();
	new npc_frightened_citizen_cw_phase2();
	new npc_rampaging_worgen_cw_phase2();
	new go_merchant_square_door_phase2();

    new npc_gwen_armstead_phase4();
	new npc_bloodfang_worgen_phase4();
	new npc_tobias_mistmantle_phase4();
	new npc_worgen_runt_phase4();
	new npc_lord_darius_crowley_phase4();

};
