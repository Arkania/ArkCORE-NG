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
#include "SpellScript.h"
#include "SpellAuraEffects.h"


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
    NPC_GILNEAS_MASTIFF_PHASE8                     = 35631,
    NPC_BLOODFANG_LURKER_PHASE8                    = 35463,
    NPC_GILNEAS_CITY_GUARD_PHASE8                  = 50474,

    NPC_GENN_HORSE_PHASE8                          = 35905,
    NPC_KRENNAN_ARANAS_PHASE8                      = 35753,
    NPC_KRENNAN_ARANAS_SAVE_PHASE8                 = 35907,
    NPC_LORD_GOLDFREY_PHASE8                       = 35906,    
    NPC_GUARD_QSKA_PHASE8                          = 35509,
    NPC_WORGEN_QSKA_PHASE8                         = 35505,
    NPC_COMMANDEERED_CANNON_PHASE8                 = 35914,
    NPC_BLOODFANG_RIPPER_QSKA_PHASE8               = 35916,
    NPC_GILNEAS_CANNON_CAMERA_PHASE8               = 50420,
    
    QUEST_LOCKDOWN                                 = 14078,
    QUEST_SOMETHINGS_AMISS                         = 14091,
    QUEST_ALL_HELL_BREAKS_LOOSE                    = 14093,
    QUEST_EVACUATE_THE_MERCHANT_SQUARE             = 14098,
    QUEST_ROYAL_ORDERS                             = 14099,
    QUEST_BY_THE_SKIN_OF_HIS_TEETH                 = 14154,
    QUEST_THE_REBEL_LORD_ARSENAL                   = 14159,
    QUEST_FROM_THE_SHADOWS                         = 14204,
    QUEST_SAVE_KRENNAN_ARANAS                      = 14293,

    ITEM_GILNEAN_MASTIFF_COLLAR                    = 48707,

    SPELL_GENERIC_QUEST_INVISIBILITY_DETECTION_1   = 49416,
    SPELL_GENERIC_QUEST_INVISIBILITY_DETECTION_2   = 49417,
    SPELL_ENRAGE                                   = 56646,
    SPELL_SET_PHASE_02                             = 59073, // set phase 2
    SPELL_SET_PHASE_04                             = 59074, // set phase 4
    // SPELL_SET_PHASE_08                             = 67853, // 59087, // set phase 8  // all wrong zone

    SPELL_GILNEAS_PRISON_PERIODIC_FORCECAST        = 66914,
    SPELL_PULL_TO                                  = 67357, // not work
    SPELL_WORGEN_BITE                              = 72870, // gilneas phase 4 aura
    SPELL_INFECTED_BITE                            = 72872, // gilneas phase 8 aura
    SPELL_FAKE_SHOT                                = 7105,

    SPELL_ATTACK_LURKER                            = 67805,
    SPELL_SUMMON_MASTIFF                           = 67807,

    SPELL_SHADOWSTALKER_STEALTH                    = 5916,
    SPELL_LURKER_ENRAGE                            = 8599,
    SPELL_UNDYING_FRENZY_INSTANT                   = 80514,
    SPELL_UNDYING_FRENZY_CHANNELED                 = 80515,

    SPELL_RESCUE_KRENNAN                           = 68219,
    SPELL_CANNON_FIRE                              = 68235,
    SPELL_SHOOT_QSKA                               = 48424,
    SPELL_CANNON_CAMERA                            = 93522,
    SPELL_FORECAST_CANNON_CAMERA                   = 93555,
    SPELL_CROWLEY_SUMMON_INITIALIZE                = 67002,    

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
            
            if (_timer <= diff)
            {
                if (_nearGate)
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
							_say=urand(0,2);							
                            switch(urand(0,4))
                            {
                            case 0:
                                _citizen->HandleEmoteCommand(EMOTE_STATE_COWER);
                                break;
                            case 1:
                                _citizen->HandleEmoteCommand(EMOTE_STATE_TALK);
                                break;
                            case 2:
                                _citizen->HandleEmoteCommand(EMOTE_ONESHOT_CRY);
                                break;
                            case 3:
                                _citizen->HandleEmoteCommand(EMOTE_STATE_SPELL_PRECAST);
                                break;
                            case 4:
                                _citizen->HandleEmoteCommand(EMOTE_STATE_EXCLAIM);
                                break;
                            }
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
            player->AddAura(SPELL_GENERIC_QUEST_INVISIBILITY_DETECTION_1, player);
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
        uint32 _health;

        void Reset()
        {
            _timer = urand(1800,2200);
            _health = urand(65,95);
        }

        void DamageTaken(Unit* attacker, uint32 &damage)
        {
            if (attacker->GetEntry() == NPC_BLOODFANG_WORGEN_PHASE4)
                if (me->HealthBelowPct(_health))
                    damage = 0;
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
            player->RemoveAura(SPELL_GENERIC_QUEST_INVISIBILITY_DETECTION_1);
            player->AddAura(SPELL_GENERIC_QUEST_INVISIBILITY_DETECTION_2, player);
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
	
        uint32  _timer;
        uint32  _health;
		
        void Reset()
        {		
			_timer = urand(1800,2200);
            _health = urand(65,95);
        }
       
        void DamageTaken(Unit* attacker, uint32 &damage)
        {
            if (attacker->GetEntry() == NPC_GILNEAS_CITY_GUARD_PHASE2)
                if (me->HealthBelowPct(_health))
                    damage = 0;
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

        void AttackStart(Unit* target)
        {
            if (!target)
                return;

            if (me->Attack(target, true))
                DoStartNoMovement(target); // prepare for no move on attack
        }

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

/*######
## npc_josiah_avery_worgen_phase8
######*/

class npc_josiah_avery_worgen_phase8 : public CreatureScript
{
public:
    npc_josiah_avery_worgen_phase8() : CreatureScript("npc_josiah_avery_worgen_phase8") { }

    struct npc_josiah_avery_worgen_phase8AI : public ScriptedAI
    {
        npc_josiah_avery_worgen_phase8AI(Creature* creature) : ScriptedAI(creature) { }

        Player* _player;
        uint32  _timer;
        uint8   _phase;
        
        void Reset()
        {
            _player=NULL;
            _timer=0;
            _phase=0;
        }

        void StartAnim(Player* player)
        {
            _player=player;
            _phase=1;
            _timer=1000;
            me->SetPhaseMask(8, true);
        }

        void SpellHit(Unit* /*caster*/, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_FAKE_SHOT)
                me->Kill(me);
        }

        void UpdateAI(uint32 diff)
        {           
                if (_timer <= diff)
                {                    
                    if (Creature* lorna = me->FindNearestCreature(NPC_LORNA_CROWLEY_PHASE8, 30.0f))
                    {
                        switch (_phase)
                        {
                            case 1:
                                _phase=2;
                                _timer = 1000;
                                if (_player)
                                {   
                                    float x, y, z;
                                    lorna->GetPosition(x, y, z);
                                    DoCast(_player, 91074, true); // unknown spell on wowhead
                                    _player->RemoveAura(SPELL_WORGEN_BITE);
                                    _player->CastSpell(me, SPELL_INFECTED_BITE, true);
                                    _player->GetMotionMaster()->MoveJump(x, y, z, 25.0f, 5.0f);
                                    _player->SaveToDB();
                                    _player->SetPhaseMask(8, true);
                                }
                                break;
                            case 2:     
                                _phase=0;
                                _player->SetFacingTo (me->GetAngle(_player->GetPositionX(), _player->GetPositionY()));
                                lorna->CastSpell(me, SPELL_FAKE_SHOT, false);
                                break;
                        }
                    } 
                }
                else
                    _timer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
    
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_josiah_avery_worgen_phase8AI (creature);
    }
};

/*######
## npc_josiah_avery_human_phase4
######*/

class npc_josiah_avery_human_phase4 : public CreatureScript
{
public:
    npc_josiah_avery_human_phase4() : CreatureScript("npc_josiah_avery_human_phase4") { }

    bool OnQuestComplete(Player* player, Creature* creature, const Quest* quest)
    {
        if (quest->GetQuestId() == QUEST_THE_REBEL_LORD_ARSENAL)
        {
            player->CastSpell(player, SPELL_WORGEN_BITE, false);
        }
        return true;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt) 
    {
        if (quest->GetQuestId() == QUEST_THE_REBEL_LORD_ARSENAL)
        {
            player->RemoveAura(SPELL_SET_PHASE_02);
            player->RemoveAura(SPELL_SET_PHASE_04);
            player->RemoveAura(SPELL_GENERIC_QUEST_INVISIBILITY_DETECTION_2);  
            float p_x, p_y;
            player->GetPosition(p_x, p_y);
            float x, y, z, o = creature->GetAngle(p_x, p_y);
            creature->GetPosition(x, y, z);
            player->SetPhaseMask(8, true);
            if (Creature* josiah = player->SummonCreature(NPC_JOSIAH_AVERY_WORGEN_PHASE8, x, y, z, o, TEMPSUMMON_TIMED_DESPAWN, 10000))
            {        
                CAST_AI(npc_josiah_avery_worgen_phase8::npc_josiah_avery_worgen_phase8AI, josiah->AI())->StartAnim(player);
            }
        }
        return true; 
    }

    struct npc_josiah_avery_human_phase4AI : public ScriptedAI
    {
        npc_josiah_avery_human_phase4AI(Creature* creature) : ScriptedAI(creature)
        {
            uiRandomSpeachTimer = urand(5000, 15000);
        }

        uint32 uiRandomSpeachTimer;

        void UpdateAI(uint32 diff)
        {
            if (uiRandomSpeachTimer <= diff)
            {
                uiRandomSpeachTimer = urand(5000, 15000);
                uint8 roll = urand(0, 5);
                Map::PlayerList const &PlList = me->GetMap()->GetPlayers();

                if (PlList.isEmpty())
                    return;

                float z = me->GetPositionZ();
                uint32 uiPhase = me->GetPhaseMask();

                for (Map::PlayerList::const_iterator i = PlList.begin(); i != PlList.end(); ++i)
                    if (Player* player = i->GetSource())
                        if (uiPhase == player->GetPhaseMask())
                            if (me->GetDistance(player) < 35.0f)
                                if (abs(z - player->GetPositionZ()) < 5.0f)
                                   Talk(0, player->GetGUID());
            }
            else
                uiRandomSpeachTimer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
    
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_josiah_avery_human_phase4AI (creature);
    }
};

/*######
## npc_lorna_crowley_phase8
######*/

class npc_lorna_crowley_phase8 : public CreatureScript
{
public:
    npc_lorna_crowley_phase8() : CreatureScript("npc_lorna_crowley_phase8") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_FROM_THE_SHADOWS)
        {
            if (Pet* pet = player->GetPet()) // first remove all normal pets, as for hunter and warlock
                pet->UnSummon();
            
            Creature* mastiff = player->GetPartyMember(NPC_GILNEAS_MASTIFF_PHASE8);
            if (!mastiff)
                player->CastSpell(player, SPELL_SUMMON_MASTIFF, false);

            creature->AI()->Talk(0);
        }
        return true;
    }

    bool OnQuestComplete(Player* player, Creature* creature, const Quest* quest)
    {
        if (quest->GetQuestId() == QUEST_FROM_THE_SHADOWS)
            if (Creature* mastiff = player->GetPartyMember(NPC_GILNEAS_MASTIFF_PHASE8))
                mastiff->DespawnOrUnsummon();
        
        return true;
    }

    struct npc_lorna_crowley_phase8AI : public ScriptedAI
    {
        npc_lorna_crowley_phase8AI(Creature* creature) : ScriptedAI(creature)
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lorna_crowley_phase8AI (creature);
    }
};

/*######
## npc_gilneas_mastiff_phase8
######*/

class npc_gilneas_mastiff_phase8 : public CreatureScript
{
public:
    npc_gilneas_mastiff_phase8() : CreatureScript("npc_gilneas_mastiff_phase8") { }

    struct npc_gilneas_mastiff_phase8AI : public ScriptedAI
    {
        npc_gilneas_mastiff_phase8AI(Creature* creature) : ScriptedAI(creature)
        {
            if (CharmInfo* charm = me->GetCharmInfo())
            {                
                SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_ATTACK_LURKER);
                charm->InitEmptyActionBar(true);
                // ToDo: the spell is shown in bar, but has wrong effect
                charm->AddSpellToActionBar(spellInfo, ACT_ENABLED);
                me->SetReactState(REACT_DEFENSIVE);
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
        return new npc_gilneas_mastiff_phase8AI(creature);
    }
};

/*######
## npc_bloodfang_lurker_phase8
######*/

class npc_bloodfang_lurker_phase8 : public CreatureScript
{
public:
    npc_bloodfang_lurker_phase8() : CreatureScript("npc_bloodfang_lurker_phase8") { }

    struct npc_bloodfang_lurker_phase8AI : public ScriptedAI
    {
        npc_bloodfang_lurker_phase8AI(Creature* creature) : ScriptedAI(creature){}

        bool    _enrage;
        bool    _frenzy;
        uint32  _health;

        void Reset()
        {
            _enrage = false;
            _frenzy = false;
            DoCast(SPELL_SHADOWSTALKER_STEALTH);
            me->SetReactState(REACT_PASSIVE);
            _health = urand(65,95);
        }

        void StartAttack(Unit* who)
        {
            me->SetReactState(REACT_AGGRESSIVE);
            me->SetInCombatWith(who);
            who->SetInCombatWith(me);
            me->AddThreat(who, 100500);
        }

        void DamageTaken(Unit* attacker, uint32 &damage)
        {
            if (attacker->GetEntry() == NPC_GILNEAS_CITY_GUARD_PHASE8)
                if (me->HealthBelowPct(_health))
                    damage = 0;

            if (me->HasReactState(REACT_PASSIVE))
                StartAttack(attacker);

            if (!_frenzy && me->HealthBelowPct(45))
            {
                _frenzy = true;
                DoCast(SPELL_UNDYING_FRENZY_CHANNELED);
            }
            else if (!_enrage && me->HealthBelowPct(30))
            {
                _enrage = true;
                DoCast(SPELL_ENRAGE);
            }
        }

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_ATTACK_LURKER)
                StartAttack(caster);
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
        return new npc_bloodfang_lurker_phase8AI (creature);
    }
};

/*######
## npc_gilneas_city_guard_phase8
######*/

class npc_gilneas_city_guard_phase8 : public CreatureScript
{
public:
    npc_gilneas_city_guard_phase8() : CreatureScript("npc_gilneas_city_guard_phase8") { }

    struct npc_gilneas_city_guard_phase8AI : public ScriptedAI
    {
        npc_gilneas_city_guard_phase8AI(Creature* creature) : ScriptedAI(creature) { }

        uint32  _health;

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            _health = urand(65,95);
        }

        void StartAttack(Unit* who)
        {
            me->SetReactState(REACT_AGGRESSIVE);
            me->SetInCombatWith(who);
            who->SetInCombatWith(me);
            me->AddThreat(who, 100500);
        }

        void DamageTaken(Unit* attacker, uint32 &damage)
        {
            if (attacker->GetEntry() == NPC_BLOODFANG_LURKER_PHASE8) 
                if (me->HealthBelowPct(_health))
                    damage = 0;

            if (me->HasReactState(REACT_PASSIVE))
                StartAttack(attacker);
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
        return new npc_gilneas_city_guard_phase8AI (creature);
    }
};

/*######
## npc_krennan_aranas_phase8
######*/

class npc_krennan_aranas_phase8 : public CreatureScript
{
public:
    npc_krennan_aranas_phase8() : CreatureScript("npc_krennan_aranas_phase8") { }

    struct npc_krennan_aranas_phase8AI : public ScriptedAI
    {
        npc_krennan_aranas_phase8AI(Creature* creature) : ScriptedAI(creature)
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);              
        }

        void UpdateAI(uint32 diff)
        {
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_krennan_aranas_phase8AI(creature);
    }
};

/*######
## npc_krennan_aranas_saved_phase8
######*/

class npc_krennan_aranas_saved_phase8 : public CreatureScript
{
public:
    npc_krennan_aranas_saved_phase8() : CreatureScript("npc_krennan_aranas_saved_phase8") { }

    struct npc_krennan_aranas_saved_phase8AI : public ScriptedAI
    {
        npc_krennan_aranas_saved_phase8AI(Creature* creature) : ScriptedAI(creature)
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

            if (me->IsSummon())
                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                    if (Vehicle* vehicle = summoner->GetVehicle())
                        if (vehicle->HasEmptySeat(1))
                            me->EnterVehicle(vehicle->GetBase(), 1);
                        else
                            me->DespawnOrUnsummon();
        }

        void UpdateAI(uint32 diff)
        {
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_krennan_aranas_saved_phase8AI (creature);
    }
};

/*######
## npc_vehicle_genn_horse_phase8
######*/

class npc_vehicle_glenn_greymane_horse_phase8 : public CreatureScript
{
public:
    npc_vehicle_glenn_greymane_horse_phase8() : CreatureScript("npc_vehicle_glenn_greymane_horse_phase8") {}

    struct npc_vehicle_glenn_greymane_horse_phase8AI : public npc_escortAI
    {
        npc_vehicle_glenn_greymane_horse_phase8AI(Creature* creature) : npc_escortAI(creature)
        {
            creature->SetReactState(REACT_PASSIVE);
            AranasIsSave = false;
        }

        bool          AranasIsSave;
        Player*       _player;
        Quest const*  _quest;



        void StartAnim(Player* player, Creature* creature, Quest const* quest)
        {
            _player=player; _quest=quest;                       
            AddWaypoint(1, -1799.37f, 1400.21f, 19.8951f);
            AddWaypoint(2, -1798.23f, 1396.9f, 19.8993f);
            AddWaypoint(3, -1795.03f, 1388.01f, 19.8898f);
            AddWaypoint(4, -1790.16f, 1378.7f, 19.8016f);
            AddWaypoint(5, -1786.41f, 1372.97f, 19.8406f);
            AddWaypoint(6, -1779.72f, 1364.88f, 19.8131f);
            AddWaypoint(7, -1774.43f, 1359.87f, 19.7021f);
            AddWaypoint(8, -1769.0f, 1356.76f, 19.7439f);
            AddWaypoint(9, -1762.64f, 1356.02f, 19.7979f);
            AddWaypoint(10, -1758.91f, 1356.08f, 19.8635f);
            AddWaypoint(11, -1751.95f, 1356.8f, 19.8273f);
            AddWaypoint(12, -1745.66f, 1357.21f, 19.7993f);
            AddWaypoint(13, -1738.7f, 1356.64f, 19.7822f);
            AddWaypoint(14, -1731.79f, 1355.51f, 19.7149f);
            AddWaypoint(15, -1724.89f, 1354.29f, 19.8661f);
            AddWaypoint(16, -1718.03f, 1352.93f, 19.7824f);
            AddWaypoint(17, -1707.68f, 1351.16f, 19.7811f);
            AddWaypoint(18, -1673.04f, 1344.91f, 15.1353f);
            AddWaypoint(19, -1673.04f, 1344.91f, 15.1353f);
            AddWaypoint(20, -1669.32f, 1346.55f, 15.1353f);
            AddWaypoint(21, -1666.45f, 1349.89f, 15.1353f);
            AddWaypoint(22, -1665.61f, 1353.85f, 15.1353f);
            AddWaypoint(23, -1666.04f, 1358.01f, 15.1353f);
            AddWaypoint(24, -1669.79f, 1360.71f, 15.1353f);
            AddWaypoint(25, -1673.1f, 1362.11f, 15.1353f);
            AddWaypoint(26, -1677.12f, 1361.57f, 15.1353f);
            AddWaypoint(27, -1679.9f, 1360.1f, 15.1353f);
            AddWaypoint(28, -1682.79f, 1357.56f, 15.1353f);
            AddWaypoint(29, -1682.79f, 1357.56f, 15.1353f);
            AddWaypoint(30, -1689.07f, 1352.39f, 15.1353f);
            AddWaypoint(31, -1691.91f, 1351.83f, 15.1353f);
            AddWaypoint(32, -1703.81f, 1351.82f, 19.7604f);
            AddWaypoint(33, -1707.26f, 1352.38f, 19.7826f);
            AddWaypoint(34, -1712.25f, 1353.55f, 19.7826f);
            AddWaypoint(35, -1718.2f, 1356.51f, 19.7164f);
            AddWaypoint(36, -1741.5f, 1372.04f, 19.9569f);
            AddWaypoint(37, -1746.23f, 1375.8f, 19.9817f);
            AddWaypoint(38, -1751.06f, 1380.53f, 19.8424f);
            AddWaypoint(39, -1754.97f, 1386.34f, 19.8474f);
            AddWaypoint(40, -1760.77f, 1394.37f, 19.9282f);
            AddWaypoint(41, -1765.11f, 1402.07f, 19.8816f);
            AddWaypoint(42, -1768.24f, 1410.2f, 19.7833f);
            AddWaypoint(43, -1772.26f, 1420.48f, 19.9029f);
            AddWaypoint(44, -1776.26f, 1430.48f, 19.9029f);
            SetDespawnAtEnd(true);
            //player->CastSpell(player, SPELL_GENERIC_QUEST_INVISIBILITY_DETECTION_1, false);
            player->EnterVehicle(me, 0);
            me->EnableAI();
        }

        void PassengerBoarded(Unit* who, int8 seatId, bool apply)
        {
            if (!apply)
                return;

            if (seatId == 0)
            {
                me->m_ControlledByPlayer=false;               
                Start(true, true);                
            }
            else if (seatId == 1)
            {
                SetEscortPaused(false);
                AranasIsSave = true;
                me->m_ControlledByPlayer=false;
            }
        }

        void WaypointReached(uint32 point)
        {
            switch(point)
            {
                case 17:
                    if (Unit* passenger = me->GetVehicleKit()->GetPassenger(0))
                    {
                        if (Creature* aranas = passenger->FindNearestCreature(NPC_KRENNAN_ARANAS_PHASE8, 50.0f))
                            if (Vehicle* vehicle = me->GetVehicleKit())
                                if (Unit* unit = vehicle->GetPassenger(0))
                                    if (Player* player = unit->ToPlayer())
                                           aranas->AI()->Talk(0, player->GetGUID()); // ARANAS_SAY_SAVE_ME
                      
                    Talk(0, passenger->GetGUID()); // HORSE_SAY_SAVE_ARANAS
                    }
                    break;
                case 18:
                    if (!AranasIsSave)
                    {
                        SetEscortPaused(true);
                        me->m_ControlledByPlayer=true;
                    }
                    break;
                case 40:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(0))
                            if (Player* player = passenger->ToPlayer())
                            {
                                std::list<Creature*> lGuards;
                                me->GetCreatureListWithEntryInGrid(lGuards, NPC_GUARD_QSKA_PHASE8, 90.0f);

                                if (!lGuards.empty())
                                    for (std::list<Creature*>::const_iterator itr = lGuards.begin(); itr != lGuards.end(); ++itr)
                                        if ((*itr)->IsAlive())
                                            if (Creature* worgen = (*itr)->FindNearestCreature(NPC_WORGEN_QSKA_PHASE8, 90.0f))
                                                (*itr)->CastSpell(worgen, SPELL_SHOOT_QSKA, false);
                            }
                    break;
                case 41:
                    me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
                    me->CombatStop();
                    break;
                case 42:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(0))
                            if (Player* player = passenger->ToPlayer())
                            {
                                player->KilledMonsterCredit(NPC_KRENNAN_ARANAS_SAVE_PHASE8, 0);

                                if (Unit* passenger_2 = vehicle->GetPassenger(1))
                                    if (Creature* aranas = passenger_2->ToCreature())
                                        aranas->AI()->Talk(0, player->GetGUID()); // DoScriptText(ARANAS_THANK, player);
                            }
                    break;
                case 44:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                    {
                        if (Unit* passenger = vehicle->GetPassenger(1))
                            if (Creature* aranas = passenger->ToCreature())
                                aranas->DespawnOrUnsummon();

                        vehicle->RemoveAllPassengers();
                    }

                    me->DespawnOrUnsummon();
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
        return new npc_vehicle_glenn_greymane_horse_phase8AI(creature);
    }
};

/*######
## npc_king_glenn_greymane_phase8
######*/

class npc_king_glenn_greymane_phase8 : public CreatureScript
{
public:
    npc_king_glenn_greymane_phase8() : CreatureScript("npc_king_glenn_greymane_phase8") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_SAVE_KRENNAN_ARANAS)
        {            
            float x, y;
            creature->GetNearPoint2D(x, y, 2.0f, player->GetOrientation() + M_PI / 2);
             
            if (Creature* horse = player->SummonCreature(NPC_GENN_HORSE_PHASE8, x, y, creature->GetPositionZ(), creature->GetOrientation()))
                CAST_AI(npc_vehicle_glenn_greymane_horse_phase8::npc_vehicle_glenn_greymane_horse_phase8AI, horse->AI())->StartAnim(player, creature, quest);                
        }

        return true;
    }

    struct npc_king_glenn_greymane_phase8AI : public ScriptedAI
    {
        npc_king_glenn_greymane_phase8AI(Creature* creature) : ScriptedAI(creature)
        {
            uiRandomYellTimer = urand(15000, 35000);
        }

        uint32 uiRandomYellTimer;
       
        void UpdateAI(uint32 diff)
        {
            if (uiRandomYellTimer <= diff)
            {
                uiRandomYellTimer = urand(15000, 35000);                
                Talk(0); 
            }
            else
                uiRandomYellTimer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
    
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_king_glenn_greymane_phase8AI (creature);
    }
};

/*######
## npc_cannon_camera_phase8
######*/

class npc_cannon_camera_phase8 : public CreatureScript
{
public:
    npc_cannon_camera_phase8() : CreatureScript("npc_cannon_camera_phase8") { }

    struct npc_cannon_camera_phase8AI : public ScriptedAI
    {
        npc_cannon_camera_phase8AI(Creature* creature) : ScriptedAI(creature)
        {
            uiEventTimer = 1000;
            uiPhase = 0;
            Event = false;
            lSummons.clear();
        }

        std::list<Creature*> lSummons;
        uint32 uiEventTimer;
        uint8 uiPhase;
        bool Event;
                
        void PassengerBoarded(Unit* /*who*/, int8 /*seatId*/, bool apply)
        {
            if (apply)
                Event = true;
            else
            {
                if (Creature* cannon = me->FindNearestCreature(NPC_COMMANDEERED_CANNON_PHASE8, 40.0f))
                    cannon->CastSpell(cannon, SPELL_CANNON_FIRE, false);

                for (std::list<Creature*>::iterator itr = lSummons.begin(); itr != lSummons.end(); ++itr)
                    if ((*itr)->IsAlive())
                        (*itr)->Kill(*itr);

                lSummons.clear();
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (Event)
                if (uiEventTimer <= diff)
                {
                    ++uiPhase;

                    switch (uiPhase)
                    {
                        case 1:
                            uiEventTimer = 1500;
                            SummonWorgen(-1715.219f, 1352.839f, 19.8645f, 2.72649f);
                            SummonWorgen(-1721.182f, 1350.429f, 19.8656f, 2.48614f);
                            SummonWorgen(-1746.523f, 1361.108f, 19.8681f, 1.85957f);
                            SummonWorgen(-1724.385f, 1348.462f, 19.6781f, 2.10692f);
                            SummonWorgen(-1734.542f, 1344.554f, 19.8769f, 1.65637f);
                            SummonWorgen(-1732.773f, 1367.837f, 19.9010f, 1.10063f);
                            SummonWorgen(-1744.358f, 1363.382f, 19.8996f, 2.06127f);
                            SummonWorgen(-1719.358f, 1357.512f, 19.7791f, 2.91488f);
                            SummonWorgen(-1728.276f, 1353.201f, 19.6823f, 2.25370f);
                            SummonWorgen(-1726.747f, 1364.599f, 19.9263f, 2.71766f);
                            SummonWorgen(-1737.693f, 1352.986f, 19.8711f, 1.96818f);
                            SummonWorgen(-1734.391f, 1359.887f, 19.9064f, 2.48052f);
                            SummonWorgen(-1730.286f, 1390.384f, 20.7707f, 4.35712f);                           
                            break;
                        case 2:
                            uiEventTimer = 2000;
                            if (Creature* cannon = me->FindNearestCreature(NPC_COMMANDEERED_CANNON_PHASE8, 40.0f))
                                cannon->CastSpell(cannon, SPELL_CANNON_FIRE, false);
                            break;
                        case 3:
                            Event = false;
                            if (Creature* cannon = me->FindNearestCreature(NPC_COMMANDEERED_CANNON_PHASE8, 40.0f))
                                cannon->CastSpell(cannon, SPELL_CANNON_FIRE, false);
                            break;
                    }
                }
                else
                    uiEventTimer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

        void SummonWorgen(float x, float y, float z, float o)
        {
            if (Creature* worgen = me->SummonCreature(NPC_BLOODFANG_RIPPER_QSKA_PHASE8, x, y, z, o))
            {
                lSummons.push_back(worgen);
                worgen->GetMotionMaster()->MovePoint(0, -1751.874f + irand(-3, 3), 1377.457f + irand(-3, 3), 19.930f);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_cannon_camera_phase8AI(creature);
    }
};

/*######
## npc_lord_godfrey_phase8
######*/

class npc_lord_godfrey_phase8 : public CreatureScript
{
public:
    npc_lord_godfrey_phase8() : CreatureScript("npc_lord_godfrey_phase8") { }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt)
    {
        if (quest->GetQuestId() == QUEST_SAVE_KRENNAN_ARANAS)
        {
            creature->AI()->Talk(0,player->GetGUID()); //  DoScriptText(GOLDFREY_SAY_ARANAS_WITH_US, player);            
            player->CastSpell(player, SPELL_CANNON_CAMERA, false);
            player->CastSpell(player, SPELL_GENERIC_QUEST_INVISIBILITY_DETECTION_2, false);
            player->SaveToDB();
        }

        return true;
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

    new npc_josiah_avery_worgen_phase8();
    new npc_josiah_avery_human_phase4();
    new npc_lorna_crowley_phase8();
    new npc_gilneas_mastiff_phase8();
    new npc_bloodfang_lurker_phase8();
    new npc_gilneas_city_guard_phase8();

    new npc_krennan_aranas_phase8();
    new npc_krennan_aranas_saved_phase8();
    new npc_vehicle_glenn_greymane_horse_phase8();
    new npc_king_glenn_greymane_phase8();
    new npc_cannon_camera_phase8();
    new npc_lord_godfrey_phase8();

};
