/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2014 ArkCORE <http://www.arkania.net/>
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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "gilneas.h"
#include "ScriptedEscortAI.h"
#include "ScriptedFollowerAI.h"
///#include "ScriptedVehicleEscortAI.h"
#include "ObjectMgr.h"
#include "Creature.h"
#include "CreatureAI.h"
#include "SpellScript.h"
#include "Object.h"
#include "ObjectMgr.h"
#include "SpellInfo.h"
#include "Vehicle.h"
#include "Language.h"
#include <math.h>
#include "Player.h"

enum eGilneas
{
    // phase 1
    NPC_PANICKED_CITIZEN_GATE                       = 44086,
    NPC_GILNEAS_CITY_GUARD_GATE                     = 34864,
    QUEST_LOCKDOWN                                  = 14078,
    SPELL_SET_PHASE_02                              = 59073,
    SPELL_GENERIC_QUEST_INVISIBILITY_DERECTION_1    = 49416,
    // phase 2
    NPC_RAMPAGING_WORGEN_1                          = 35660,
    NPC_RAMPAGING_WORGEN_2                          = 34884,
    NPC_GILNEAS_CITY_GUARD                          = 34916,

    QUEST_ROYAL_ORDERS                              = 14099,

    SPELL_INVISIBILITY_DETECTION_2                  = 49417,

    // old
    SPELL_ENRAGE                          = 8599,
    SPELL_SHOOT                           = 20463,
    SPELL_CATACLYSM_TYPE_1                = 80133,
    SPELL_CATACLYSM_TYPE_2                = 68953,
    SPELL_CATACLYSM_TYPE_3                = 80134,

    PHASE_ONE                             = 6,

    NPC_AFFLICTED_GILNEAN                 = 50471,
    NPC_BLOODFANG_WORGEN                  = 35118,
    NPC_GILNEAN_ROYAL_GUARD               = 35232,
    NPC_FRENZIED_STALKER                  = 35627,
    NPC_NORTHGATE_REBEL                   = 41015,
    NPC_GILNEAS_CITY_GUARD_PHASE_4        = 50474,
    NPC_NORTHGATE_REBEL_PHASE_5           = 36057,
    NPC_BLOODFANG_STALKER_PHASE_5         = 35229,
    NPC_FORSAKEN_INVADER                  = 34511,
    NPC_FORSAKEN_FOOTSOLDIER              = 36236
};

/*######
## phase 1
######*/

/*######
## communication between npc_panicked_citizen_gate  and  npc_gilneas_city_guard_gate
######*/

const uint16 PanickedCitizenRandomEmote[5] =
{
    EMOTE_STATE_COWER,
    EMOTE_STATE_TALK,
    EMOTE_ONESHOT_CRY, 
    EMOTE_STATE_SPELL_PRECAST, // EMOTE_ONESHOT_BEG,
    EMOTE_STATE_EXCLAIM,
};

/*######
## npc_panicked_citizen_gate
######*/
class npc_panicked_citizen_gate : public CreatureScript
{
public:
    npc_panicked_citizen_gate() : CreatureScript("npc_panicked_citizen_gate") { }

    struct npc_panicked_citizen_gateAI : public ScriptedAI
    {
        npc_panicked_citizen_gateAI(Creature* creature) : ScriptedAI(creature)  { }

        void UpdateAI(const uint32 /*diff*/)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_panicked_citizen_gateAI (creature);
    }
};

/*######
## npc_gilneas_city_guard_gate
######*/

class npc_gilneas_city_guard_gate : public CreatureScript
{
public:
    npc_gilneas_city_guard_gate() : CreatureScript("npc_gilneas_city_guard_gate") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gilneas_city_guard_gateAI (creature);
    }

    struct npc_gilneas_city_guard_gateAI : public ScriptedAI
    {
        npc_gilneas_city_guard_gateAI(Creature* creature) : ScriptedAI(creature) { }

        uint32       _timer;
        uint8        _phase;
        bool         _nearGate;
        uint8        _say;
        uint8        _emote;
        Creature*    _citizen;

        void Reset()
        {
            _timer = urand(10000, 40000);
            _phase = 0;

            if (me->GetDistance2d(-1430.47f, 1345.55f) < 10.0f)
                _nearGate = true;
            else
                _nearGate = false;
        }

        void UpdateAI(const uint32 diff)
        {
            if (_nearGate)
            {
                if (_timer <= diff)
                {
                   DoWork();
                }
                else
                    _timer -= diff;
            }

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
                    me->GetCreatureListWithEntryInGrid(listOfCitizen, NPC_PANICKED_CITIZEN_GATE, 35.0f);

                    if (!listOfCitizen.empty())
                    {
                        std::list<Creature*>::iterator itr = listOfCitizen.begin();
                        std::advance(itr, urand(0, (listOfCitizen.size() - 1)));

                        if (Creature* _citizen = *itr)
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
                        _citizen->AI()->Talk(_say);
                        _timer = urand(4000,7000);
                        _phase=2;
                    }
                    break;
                }
                case 2:
                {
                    if (_citizen)
                    {
                        Talk(_say);
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
                        _timer = urand(20000, 40000);
                        _phase=0;
                    }
                    break;
                }
            }
        }
    };
};

/*######
## npc_gilnean_crow
######*/

struct Coord
{
    float x;
    float y;
    float z;
};

struct CrowFlyPosition
{
    Coord FirstCoord;
    Coord SecondCoord;
};

const CrowFlyPosition CrowFlyPos[12]=
{
    {{-1398.24f, 1455.26f, 39.6586f},{-1403.93f, 1464.87f, 47.7066f}},
    {{-1628.58f, 1320.29f, 27.7544f},{-1626.90f, 1306.58f, 34.9702f}},
    {{-1799.76f, 1564.33f, 34.9408f},{-1788.64f, 1561.74f, 38.4683f}},
    {{-1840.45f, 2299.17f, 50.2894f},{-1850.23f, 2302.62f, 52.4776f}},
    {{-1978.48f, 2319.58f, 36.5107f},{-1979.80f, 2329.24f, 38.8598f}},
    {{-1914.39f, 2406.48f, 37.4498f},{-1916.48f, 2416.10f, 39.2891f}},
    {{-1844.85f, 2328.28f, 47.8401f},{-1836.64f, 2327.05f, 50.0315f}},
    {{-1845.20f, 2502.86f, 6.67603f},{-1839.71f, 2508.70f, 9.67311f}},
    {{-2031.81f, 2280.29f, 28.7353f},{-2043.98f, 2286.43f, 32.0705f}},
    {{-2164.61f, 2213.12f, 27.4170f},{-2169.48f, 2224.64f, 29.1592f}},
    {{-1775.46f, 2380.44f, 51.9086f},{-1767.75f, 2385.99f, 55.8622f}},
    {{-1650.79f, 2507.28f, 109.893f},{-1645.28f, 2506.02f, 115.819f}},
};

class npc_gilnean_crow : public CreatureScript
{
public:
    npc_gilnean_crow() : CreatureScript("npc_gilnean_crow") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gilnean_crowAI (creature);
    }

    struct npc_gilnean_crowAI : public npc_escortAI
    {
        npc_gilnean_crowAI(Creature* creature) : npc_escortAI(creature)
        {
            me->SetCanFly(true);
            me->SetSpeed(MOVE_FLIGHT, 2.0f, true);
            CheckFly();
            Flying = false;
        }

        uint8 point_id;
        bool Flying;

        bool CheckFly()
        {
            float dist = 100500;
            float check_dist;
            int i = -1;

            for (int j = 0; j < 12; ++j)
            {
                check_dist = me->GetDistance2d(CrowFlyPos[j].FirstCoord.x, CrowFlyPos[j].FirstCoord.y);

                if (dist > check_dist && check_dist < 50.0f)
                {
                    dist = check_dist;
                    i = j;
                }
            }

            if (i == -1)
                return false;

            point_id = i;
            return true;
        }

        void FlyAway()
        {
            Flying = true;
            me->SetCanFly(true);
            AddWaypoint(0,
                    CrowFlyPos[point_id].FirstCoord.x + irand(-4, 4),
                    CrowFlyPos[point_id].FirstCoord.y + irand(-4, 4),
                    CrowFlyPos[point_id].FirstCoord.z + irand(-4, 4));
            AddWaypoint(0,
                    CrowFlyPos[point_id].SecondCoord.x + irand(-4, 4),
                    CrowFlyPos[point_id].SecondCoord.y + irand(-4, 4),
                    CrowFlyPos[point_id].SecondCoord.z + irand(-4, 4));
            Start();
        }

        void JustRespawned()
        {
            me->RemoveAura(68560);
            me->SetCanFly(true);
        }

        void FinishEscort()
        {
            Flying = false;
            me->AddAura(68560, me);
            me->SetCanFly(false);
            me->DespawnOrUnsummon();
        }

        void WaypointReached(uint32 /*point*/) { }

        void MoveInLineOfSight(Unit* who)
        {
            if (who->GetTypeId() == TYPEID_PLAYER)
                if (me->IsWithinDistInMap(who, 15.0f))
                    if (!Flying)
                        FlyAway();
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);
        }
    };
};

/*######
## npc_prince_liam_greymane_intro
######*/

class npc_prince_liam_greymane_intro : public CreatureScript
{
public:
    npc_prince_liam_greymane_intro() : CreatureScript("npc_prince_liam_greymane_intro") { }

    bool OnQuestAccept(Player* /*player*/, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == 14078)
            if (Creature* citizen = creature->FindNearestCreature(34851, 20.0f))
             citizen->AI()->Talk(0);

        return true;
    }

    struct npc_prince_liam_greymane_introAI : public ScriptedAI
    {
        npc_prince_liam_greymane_introAI(Creature* creature) : ScriptedAI(creature) {}

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
                        Talk(0);
                        uiSayTimer = 15000;
                        break;
                    case 2:
                        Talk(1);
                        uiSayTimer = 18000;
                        break;
                    case 3:
                        Talk(2);
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
        return new npc_prince_liam_greymane_introAI (creature);
    }
};

/*######
## npc_lieutenant_walden
######*/

class npc_lieutenant_walden : public CreatureScript
{
public:
    npc_lieutenant_walden() : CreatureScript("npc_lieutenant_walden") { }

    bool OnQuestComplete(Player* player, Creature* /*creature*/, Quest const* quest)
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
## phase 2
######*/

/*######
## npc_prince_liam_greymane_phase_1
######*/

class npc_prince_liam_greymane_phase_1 : public CreatureScript
{
public:
    npc_prince_liam_greymane_phase_1() : CreatureScript("npc_prince_liam_greymane_phase_1") { }

    bool OnQuestAccept(Player* player, Creature* /*creature*/, const Quest* quest)
    {
        if (quest->GetQuestId() ==  QUEST_ROYAL_ORDERS)
        {
            player->RemoveAura(SPELL_GENERIC_QUEST_INVISIBILITY_DERECTION_1);
            player->CastSpell(player, SPELL_INVISIBILITY_DETECTION_2, false);
            player->SaveToDB();
        }

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_prince_liam_greymane_phase_1AI (creature);
    }

    struct npc_prince_liam_greymane_phase_1AI : public ScriptedAI
    {
        npc_prince_liam_greymane_phase_1AI(Creature* creature) : ScriptedAI(creature)
        {
            SetCombatMovement(false);
            me->_ReactDistance = 10.0f;
        }

        uint32 uiSayTimer;
        uint32 uiShootTimer;
        bool miss;

        void Reset()
        {
            uiSayTimer = urand(5000, 10000);
            uiShootTimer = 1500;
            miss = false;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (uiShootTimer <= diff)
            {
                uiShootTimer = 1500;

                if (Unit* target = me->FindNearestCreature(NPC_RAMPAGING_WORGEN_1, 40.0f))
                    if (target != me->GetVictim())
                    {
                        me->getThreatManager().modifyThreatPercent(me->GetVictim(), -100);
                        me->CombatStart(target);
                        me->AddThreat(target, 1000);
                    }
                if (!me->IsWithinMeleeRange(me->GetVictim(), 0.0f))
                {
                    me->Attack(me->GetVictim(), false);
                    me->CastSpell(me->GetVictim(), SPELL_SHOOT, false);
                }
                else
                    me->Attack(me->GetVictim(), true);
            }
            else
                uiShootTimer -= diff;

            if (uiSayTimer <= diff)
            {
                uiSayTimer = urand(30000, 120000);
               // uint8 id = urand(0, 4);
                Talk(0);
            }
            else
                uiSayTimer -= diff;

            if (me->GetVictim()->GetTypeId() == TYPEID_UNIT)
            {
                if (me->GetVictim()->GetHealthPct() < 90)
                    miss = true;
                else
                    miss = false;
            }

            DoMeleeAttackIfReady();
        }
    };
};

/*######
## npc_rampaging_worgen
######*/

class npc_rampaging_worgen : public CreatureScript
{
public:
    npc_rampaging_worgen() : CreatureScript("npc_rampaging_worgen") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_rampaging_worgenAI (creature);
    }

    struct npc_rampaging_worgenAI : public ScriptedAI
    {
        npc_rampaging_worgenAI(Creature* creature) : ScriptedAI(creature) { }

        uint32 uiEnemyEntry;
        bool enrage;
        bool miss;

        void Reset()
        {
            enrage = false;
            miss = false;

            if (me->GetEntry() == NPC_AFFLICTED_GILNEAN)
                me->_ReactDistance = 3.0f;
            else
                me->_ReactDistance = 10.0f;

            switch(me->GetEntry())
            {
                case NPC_RAMPAGING_WORGEN_2:
                    uiEnemyEntry = NPC_GILNEAS_CITY_GUARD;
                    break;
                case NPC_BLOODFANG_WORGEN:
                    uiEnemyEntry = NPC_GILNEAN_ROYAL_GUARD;
                    break;
                case NPC_FRENZIED_STALKER:
                    uiEnemyEntry = NPC_NORTHGATE_REBEL;
                    break;
                default:
                    uiEnemyEntry = 0;
                    break;
            }
        }

        void DamageTaken(Unit* attacker, uint32 &/*damage*/)
        {
            if (attacker->GetTypeId() != TYPEID_PLAYER)
                return;

            Unit* victim = NULL;

            if (me->GetVictim())
                if (victim->GetTypeId() == TYPEID_PLAYER)
                    return;

            if (victim)
                me->getThreatManager().modifyThreatPercent(victim, -100);

            AttackStart(attacker);
            me->AddThreat(attacker, 10005000);
        }

        void UpdateAI(const uint32 /*diff*/)
        {
            if (!UpdateVictim())
                return;

            if (!enrage && me->HealthBelowPct(30))
            {
                DoCast(me, SPELL_ENRAGE);
                enrage = true;
            }

            if (me->GetVictim()->GetTypeId() == TYPEID_UNIT)
            {
                if (me->GetVictim()->GetHealthPct() < 90)
                    miss = true;
                else
                    miss = false;
            }

            DoMeleeAttackIfReady();
        }
    };
};

/*######
## npc_gilneas_city_guard
######*/

class npc_gilneas_city_guard : public CreatureScript
{
public:
    npc_gilneas_city_guard() : CreatureScript("npc_gilneas_city_guard") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gilneas_city_guardAI (creature);
    }

    struct npc_gilneas_city_guardAI : public ScriptedAI
    {
        npc_gilneas_city_guardAI(Creature* creature) : ScriptedAI(creature)
        {
            uiEmoteState = me->GetUInt32Value(UNIT_NPC_EMOTESTATE);
        }

        uint32 uiYellTimer;
        uint32 uiEnemyEntry;
        uint32 uiShootTimer;
        uint32 uiEmoteState;
        bool miss;
        bool CanSay;

        void Reset()
        {
            uiYellTimer = urand(25000, 75000);
            uiShootTimer = 1000;
            miss = false;
            CanSay = false;
            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, uiEmoteState);

            switch(me->GetEntry())
            {
                case NPC_GILNEAS_CITY_GUARD:
                    uiEnemyEntry = NPC_RAMPAGING_WORGEN_2;
                    break;
                case NPC_GILNEAN_ROYAL_GUARD:
                    uiEnemyEntry = NPC_BLOODFANG_WORGEN;
                    break;
                case NPC_GILNEAS_CITY_GUARD_PHASE_4:
                    CanSay = true;
                    uiEnemyEntry = NPC_AFFLICTED_GILNEAN;
                    break;
                case NPC_NORTHGATE_REBEL_PHASE_5:
                    uiEnemyEntry = NPC_BLOODFANG_STALKER_PHASE_5;
                    break;
                case NPC_NORTHGATE_REBEL:
                    uiEnemyEntry = NPC_FRENZIED_STALKER;
                    break;
                default:
                    uiEnemyEntry = 0;
                    break;
            }

            if (me->GetEntry() == NPC_GILNEAS_CITY_GUARD_PHASE_4)
            {
                me->_ReactDistance = 3.0f;
                SetCombatMovement(false);
            }
            else
                me->_ReactDistance = 10.0f;

            if (me->GetDistance2d(-1770.2f, 1343.78f) < 25.0f)
            {
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }

            if (Unit* target = me->FindNearestCreature(uiEnemyEntry, 40.0f))
                AttackStart(target);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (me->GetVictim()->GetTypeId() == TYPEID_UNIT)
            {
                if (me->GetVictim()->GetHealthPct() < 90)
                    miss = true;
                else
                    miss = false;
            }

            if (uiShootTimer <= diff)
            {
                uiShootTimer = 2500;

                if (!me->IsWithinMeleeRange(me->GetVictim(), 0.0f))
                    if (uiEnemyEntry)
                        if (Unit* target = me->FindNearestCreature(uiEnemyEntry, 40.0f))
                            if (target != me->GetVictim())
                            {
                                me->getThreatManager().modifyThreatPercent(me->GetVictim(), -100);
                                me->CombatStart(target);
                                me->AddThreat(target, 1000);
                            }

                if (!me->IsWithinMeleeRange(me->GetVictim(), 0.0f))
                {
                    if (me->HasUnitState(UNIT_STATE_MELEE_ATTACKING))
                    {
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                        me->ClearUnitState(UNIT_STATE_MELEE_ATTACKING);
                        me->SendMeleeAttackStop(me->GetVictim());
                    }

                    me->CastSpell(me->GetVictim(), SPELL_SHOOT, false);
                }
                else
                    if (!me->HasUnitState(UNIT_STATE_MELEE_ATTACKING))
                    {
                        me->AddUnitState(UNIT_STATE_MELEE_ATTACKING);
                        me->SendMeleeAttackStart(me->GetVictim());
                    }
            }
            else
                uiShootTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

///////////
// Quest Evacuate the Merchant Square 14098
///////////

enum qEMS
{
    NPC_J_CITIZEN                = 34981,
    NPC_CW_WORGEN                = 35660,
    NPC_CW_CITIZEN               = 35836,
    NPC_QEMS_KILL_CREDIT         = 35830,

    NPC_J_CITIZEN_RANDOM_SAY     = 0,
    NPC_CW_CITIZEN_RANDOM_SAY    = 0,

    SPELL_CW_WORGEN_ENRAGE       = 56646,

    ACTION_JUST_CITIZEN          = 1,
    ACTION_CITIZEN_AND_WORGEN    = 2,
};

class npc_qems_citizen : public CreatureScript
{
public:
    npc_qems_citizen() : CreatureScript("npc_qems_citizen") {}

    struct npc_qems_citizenAI : public npc_escortAI
    {
        npc_qems_citizenAI(Creature* creature) : npc_escortAI(creature)
        {
            me->SetReactState(REACT_PASSIVE);
            uiEventTimer = 1000;
            pause = false;
        }

        uint32 uiEventTimer;
        bool pause;

        void WaypointReached(uint32 point)
        {
            if (point == 1)
            {
                if (me->IsSummon())
                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        if (Player* player = summoner->ToPlayer())
                            player->KilledMonsterCredit(NPC_QEMS_KILL_CREDIT, 0);

                SetEscortPaused(true);
                pause = true;

                if (me->GetEntry() == NPC_J_CITIZEN)
                {
                    Talk(NPC_J_CITIZEN_RANDOM_SAY);
                }
                else
                {
                    Talk(NPC_CW_CITIZEN_RANDOM_SAY);
                    me->HandleEmoteCommand(EMOTE_ONESHOT_COWER);
                }
            }
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (pause)
            {
                if (uiEventTimer <= diff)
                {
                    pause = false;
                    SetEscortPaused(false);
                }
                else
                    uiEventTimer -= diff;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_qems_citizenAI(creature);
    }
};

class npc_qems_worgen : public CreatureScript
{
public:
    npc_qems_worgen() : CreatureScript("npc_qems_worgen") {}

    struct npc_qems_worgenAI : public npc_escortAI
    {
        npc_qems_worgenAI(Creature* creature) : npc_escortAI(creature)
        {
            creature->SetReactState(REACT_PASSIVE);
            uiPauseTimer = 4000;
            enrage = false;
            pause = true;
        }

        uint32 uiPauseTimer;
        bool pause;
        bool enrage;

        void WaypointReached(uint32 point)
        {
            if (point == 1)
            {
                me->SetReactState(REACT_AGGRESSIVE);
                me->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
                if (me->IsSummon())
                {
                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        AttackStart(summoner);
                    else
                        me->DespawnOrUnsummon();
                }
            }
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (pause)
            {
                if (uiPauseTimer <= diff)
                {
                    pause = false;
                    SetEscortPaused(false);
                }
                else
                    uiPauseTimer -= diff;
            }

            if (!UpdateVictim())
                return;

            if (!enrage && me->HealthBelowPct(30))
            {
                DoCast(SPELL_CW_WORGEN_ENRAGE);
                enrage = true;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_qems_worgenAI(creature);
    }
};

class go_merchant_square_door : public GameObjectScript
{
public:
    go_merchant_square_door() : GameObjectScript("go_merchant_square_door") { }

    void SummonQuestCreature(uint32 entry, bool IsCitizen, GameObject* go, Player* player)
    {
        if (!player)
            return;

        float x, y;
        go->GetNearPoint2D(x, y, 2.8f, go->GetOrientation() + M_PI * 0.75f);

        if (Creature* creature = player->SummonCreature(entry, x, y, go->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 15000))
        {
            creature->SetPhaseMask(PHASE_ONE, true);
            creature->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
            npc_escortAI* npc_escort = NULL;

            if (IsCitizen)
                npc_escort = CAST_AI(npc_qems_citizen::npc_qems_citizenAI, creature->AI());
            else
                npc_escort = CAST_AI(npc_qems_worgen::npc_qems_worgenAI, creature->AI());

            if (!npc_escort)
                return;

            float x, y, z = creature->GetPositionZ();
            go->GetNearPoint2D(x, y, 1.0f, go->GetOrientation() + M_PI);
            npc_escort->AddWaypoint(0, x, y, z);
            go->GetNearPoint2D(x, y, 3.0f, go->GetOrientation());
            npc_escort->AddWaypoint(1, x, y, z);

            if (IsCitizen)
            {
                float x, y;
                go->GetNearPoint2D(x, y, 10.0f, go->GetOrientation());
                const Position src = {x, y, go->GetPositionZ(), 0};
                Position dst;
                go->GetRandomPoint(src, 5.0f, dst);
                npc_escort->AddWaypoint(2, dst.GetPositionX(), dst.GetPositionY(), z);
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
                SummonQuestCreature(NPC_J_CITIZEN, true, go, player);
                break;
            case ACTION_CITIZEN_AND_WORGEN:
                SummonQuestCreature(NPC_CW_CITIZEN, true, go, player);
                SummonQuestCreature(NPC_CW_WORGEN, false, go, player);
                break;
        }

        return false;
    }
};

///////////
// Quest Old Divisions 14157
///////////

enum eQOD
{
    QUEST_OLD_DIVISIONS               = 14157,

    NPC_LORD_GODFREY_QOD              = 35115,
    NPC_KING_GENN_GREYMANE_QOD        = 35112,

    NPC_LORD_GODFREY_QOD_SAY          = 0,
    NPC_KING_GENN_GREYMANE_QOD_SAY    = 0,
};

struct Psc
{
    uint64 uiPlayerGUID;
    uint32 uiPersonalTimer;
};

class npc_king_genn_greymane_qod : public CreatureScript
{
public:
    npc_king_genn_greymane_qod() : CreatureScript("npc_king_genn_greymane_qod") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_king_genn_greymane_qodAI (creature);
    }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_OLD_DIVISIONS)
            if (creature->FindNearestCreature(NPC_LORD_GODFREY_QOD, 20.0f))
            {
                creature->AI()->Talk(NPC_LORD_GODFREY_QOD_SAY, player->GetGUID());
                Psc new_psc;
                new_psc.uiPersonalTimer = 5000;
                new_psc.uiPlayerGUID = player->GetGUID();
                CAST_AI(npc_king_genn_greymane_qodAI, creature->AI())->lPlayerList.push_back(new_psc);
            }

        return true;
    }

    struct npc_king_genn_greymane_qodAI : public ScriptedAI
    {
        npc_king_genn_greymane_qodAI(Creature* creature) : ScriptedAI(creature) {}

        std::list<Psc> lPlayerList;

        void UpdateAI(const uint32 diff)
        {
            if (lPlayerList.empty())
                return;

            for (std::list<Psc>::iterator itr = lPlayerList.begin(); itr != lPlayerList.end(); )
                if ((*itr).uiPersonalTimer <= diff)
                {
                    if (Player* player = Unit::GetPlayer(*me, (*itr).uiPlayerGUID))
                        Talk(NPC_KING_GENN_GREYMANE_QOD_SAY, player->GetGUID());

                    itr = lPlayerList.erase(itr);
                }
                else
                {
                    (*itr).uiPersonalTimer -= diff;
                    ++itr;
                }
        }
    };
};

///////////
// Quest By the Skin of His Teeth 14154
///////////

static float WorgenPosT1[4][4] =
{
    {-1718.18f,1526.45f,55.9076f,4.74478f},
    {-1718.06f,1515.83f,55.3631f,4.73569f},
    {-1718.02f,1487.10f,57.0588f,4.64537f},
    {-1701.28f,1470.35f,52.2872f,5.55485f},
};

static float WorgenPosT2[8][4] =
{
    {-1634.06f,1486.73f,73.3780f,0.76234f},
    {-1635.34f,1487.13f,72.2655f,0.89272f},
    {-1635.80f,1488.80f,71.0234f,0.79533f},
    {-1630.88f,1483.50f,72.9698f,0.75763f},
    {-1629.91f,1482.39f,71.7020f,0.71836f},
    {-1628.88f,1481.65f,70.6151f,0.69480f},
    {-1633.23f,1484.80f,74.9893f,0.77727f},
    {-1672.09f,1448.92f,52.2870f,0.78175f},
};

enum eQPR
{
    QUEST_BY_THE_SKIN_OF_HIS_TEETH             = 14154,

    NPC_WORGEN_RUNT_FW                         = 35456,
    NPC_WORGEN_RUNT_SW                         = 35188,
    NPC_WORGEN_ALPHA_FW                        = 35170,
    NPC_WORGEN_ALPHA_SW                        = 35167,

    SPELL_HORRIFYING_HOWL                      = 75355,
    SPELL_DEMORALIZING_SHOUT                   = 61044,
    SPELL_GILNEAS_PRISON_PERIODIC_FORCECAST    = 66914,

    TYPE_FIRST_WAVE                            = 0,
    TYPE_SECOND_WAVE                           = 1,

    ACTION_START_EVENT                         = 3,
};

class npc_worgen_attacker : public CreatureScript
{
public:
    npc_worgen_attacker() : CreatureScript("npc_worgen_attacker") {}

    struct npc_worgen_attackerAI : public npc_escortAI
    {
        npc_worgen_attackerAI(Creature* creature) : npc_escortAI(creature)
        {
            creature->SetReactState(REACT_PASSIVE);
            creature->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
            enrage = false;
            uiHorrifyingHowlTimer = 3000;
        }

        bool enrage;
        uint32 uiHorrifyingHowlTimer;

        void StartAttack()
        {
            me->SetReactState(REACT_AGGRESSIVE);
            me->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);

            if (me->IsSummon())
                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                {
                    me->CombatStart(summoner);
                    me->AddThreat(summoner, 100500);
                }
        }

        void WaypointReached(uint32 point)
        {
            if (point == 2)
                if (me->GetEntry() == NPC_WORGEN_ALPHA_SW || NPC_WORGEN_RUNT_SW)
                    StartAttack();

            if (point == 5)
                StartAttack();
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (!UpdateVictim())
                return;

            if (!enrage && me->HealthBelowPct(30))
            {
                enrage = true;
                DoCast(SPELL_ENRAGE);
            }

            if (uiHorrifyingHowlTimer <= diff)
            {
                uiHorrifyingHowlTimer = 15000;
                DoCast(SPELL_HORRIFYING_HOWL);
            }
            else
                uiHorrifyingHowlTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_worgen_attackerAI(creature);
    }
};

class npc_lord_darius_crowley : public CreatureScript
{
public:
    npc_lord_darius_crowley() : CreatureScript("npc_lord_darius_crowley") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_BY_THE_SKIN_OF_HIS_TEETH)
        {
            creature->CastSpell(player, SPELL_GILNEAS_PRISON_PERIODIC_FORCECAST, true);
            creature->AI()->DoAction(ACTION_START_EVENT);
        }

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lord_darius_crowleyAI (creature);
    }

    struct npc_lord_darius_crowleyAI : public ScriptedAI
    {
        npc_lord_darius_crowleyAI(Creature* creature) : ScriptedAI(creature)
        {
            Event = false;
            uiEventTimer = 120000;
            uiSummonTimer = 3000;
            uiDShoutTimer = 15000;
            uiType = TYPE_FIRST_WAVE;
            SetCombatMovement(false);
        }

        uint32 uiDShoutTimer;
        uint32 uiSummonTimer;
        uint32 uiEventTimer;
        uint8 uiType;
        bool Event;

        void DoAction(const int32 action)
        {
            if (action == ACTION_START_EVENT)
            {
                Event = true;
                uiEventTimer = 120000;
            }
        }

        void GetNearPoint2D(float src_x, float src_y, float &dst_x, float &dst_y, float distance2d, float absAngle) const
        {
            dst_x = src_x + distance2d * std::cos(absAngle);
            dst_y = src_y + distance2d * std::sin(absAngle);

            Trinity::NormalizeMapCoord(dst_x);
            Trinity::NormalizeMapCoord(dst_y);
        }

        void SummonWorgen(uint32 entry, uint8 id)
        {
            float x, y;
            GetNearPoint2D(WorgenPosT2[id][0], WorgenPosT2[id][1], x, y, 3.0f + rand()%90, WorgenPosT2[id][3]);

            if (Creature* worgen = me->SummonCreature(entry, x, y, WorgenPosT2[id][2] + 2.0f, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000))
                if (npc_escortAI* npc_escort = CAST_AI(npc_worgen_attacker::npc_worgen_attackerAI, worgen->AI()))
                {
                    npc_escort->AddWaypoint(0, WorgenPosT2[id][0], WorgenPosT2[id][1], WorgenPosT2[id][2], 0/*, true*/);
                    const Position src = {WorgenPosT2[7][0], WorgenPosT2[7][1], WorgenPosT2[7][2], WorgenPosT2[7][3]};
                    Position dst;
                    worgen->GetRandomPoint(src, 5.0f, dst);
                    npc_escort->AddWaypoint(1, dst.GetPositionX(), dst.GetPositionY(), dst.GetPositionZ());
                    npc_escort->AddWaypoint(2, -1679.73f,1442.12f,52.3705f);
                    npc_escort->Start(true, true);
                    npc_escort->SetDespawnAtEnd(false);
                }
        }

        void SummonFirstWave()
        {
            if (Creature* worgen = me->SummonCreature(NPC_WORGEN_ALPHA_FW, WorgenPosT1[0][0], WorgenPosT1[0][1], WorgenPosT1[0][2], WorgenPosT1[0][3], TEMPSUMMON_DEAD_DESPAWN, 500))
                for (int i = 0; i < 2; ++i)
                {
                    float x, y;
                    worgen->GetNearPoint2D(x, y, urand(1, 4), WorgenPosT1[0][3] + M_PI / 2);
                    me->SummonCreature(NPC_WORGEN_RUNT_FW, x, y, WorgenPosT1[0][2], WorgenPosT1[0][3], TEMPSUMMON_DEAD_DESPAWN, 500);
                    worgen->GetNearPoint2D(x, y, urand(1, 5), WorgenPosT1[0][3] - M_PI / 2);
                    me->SummonCreature(NPC_WORGEN_RUNT_FW, x, y, WorgenPosT1[0][2], WorgenPosT1[0][3], TEMPSUMMON_DEAD_DESPAWN, 500);
                }
        }

        void SummonSecondWave()
        {
            SummonWorgen(NPC_WORGEN_ALPHA_SW, 6);

            for (int i = 0; i < 4; ++i)
            {
                uint8 roll = urand(0, 5);
                SummonWorgen(NPC_WORGEN_RUNT_SW, roll);
            }
        }

        void JustSummoned(Creature* summoned)
        {
            if (summoned->GetEntry() == NPC_WORGEN_ALPHA_FW || summoned->GetEntry() == NPC_WORGEN_RUNT_FW)
                if (npc_escortAI* worgen = CAST_AI(npc_worgen_attacker::npc_worgen_attackerAI, summoned->AI()))
                {
                    worgen->AddWaypoint(1, WorgenPosT1[0][0], WorgenPosT1[0][1], WorgenPosT1[0][2]);
                    worgen->AddWaypoint(2, WorgenPosT1[1][0], WorgenPosT1[1][1], WorgenPosT1[1][2]);
                    worgen->AddWaypoint(3, WorgenPosT1[2][0], WorgenPosT1[2][1], WorgenPosT1[2][2], 0/*, true*/);
                    worgen->AddWaypoint(4, WorgenPosT1[3][0], WorgenPosT1[3][1], WorgenPosT1[3][2]);
                    worgen->AddWaypoint(5, -1679.73f,1442.12f,52.3705f);
                    worgen->Start(true, true);
                    worgen->SetDespawnAtEnd(false);
                }
        }

        void UpdateAI(const uint32 diff)
        {
            if (Event)
            {
                if (uiSummonTimer <= diff)
                {
                    uiSummonTimer = 15000;

                    switch (uiType)
                    {
                        case TYPE_FIRST_WAVE:
                            uiType = TYPE_SECOND_WAVE;
                            SummonFirstWave();
                            break;
                        case TYPE_SECOND_WAVE:
                            uiType = TYPE_FIRST_WAVE;
                            SummonSecondWave();
                            break;
                    }
                }
                else
                    uiSummonTimer -= diff;

                if (uiEventTimer <= diff)
                    Event = false;
                else
                    uiEventTimer -= diff;
            }

            if (!UpdateVictim())
                return;

            if (uiDShoutTimer <= diff)
            {
                uiDShoutTimer = 15000;
                DoCast(SPELL_DEMORALIZING_SHOUT);
            }
            else
                uiDShoutTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

///////////
// Quest The Rebel Lord's Arsenal 14159
///////////

enum qTRLA
{
    QUEST_THE_REBEL_LORD_ARSENAL    = 14159,

    NPC_LORNA_CROWLEY               = 35378,
    NPC_JOSIAH_AVERY_WORGEN         = 35370,

    RANDOM_JOSIAH_YELL              = 0,
    SAY_WORGEN_BITE                 = 1,

    SPELL_ZONE_SPECIFIC_01          = 59073,
    SPELL_WORGEN_BITE               = 72870,
    SPELL_PULL_TO                   = 67357,// not work
};

class npc_josiah_avery_worgen : public CreatureScript
{
public:
    npc_josiah_avery_worgen() : CreatureScript("npc_josiah_avery_worgen") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_josiah_avery_worgenAI (creature);
    }

    struct npc_josiah_avery_worgenAI : public ScriptedAI
    {
        npc_josiah_avery_worgenAI(Creature* creature) : ScriptedAI(creature)
        {
            uiEventTimer = 500;
            uiPase = 1;
            uiPlayerGUID = 0;
            me->SetReactState(REACT_PASSIVE);

            if (me->IsSummon())
                Event = true;
            else
                Event = false;
        }

        uint64 uiPlayerGUID;
        uint32 uiEventTimer;
        uint8 uiPase;
        bool Event;

        void SpellHit(Unit* /*caster*/, const SpellInfo* spell)
        {
            if (spell->Id == 7105)
                me->Kill(me);
        }

        void UpdateAI(const uint32 diff)
        {
            if (Event)
            {
                if (uiEventTimer <= diff)
                {
                    if (Creature* creature = me->FindNearestCreature(NPC_LORNA_CROWLEY, 30.0f))
                        switch (uiPase)
                        {
                            case 1:
                                ++uiPase;
                                uiEventTimer = 1000;
                                if (Player* player = Unit::GetPlayer(*me, uiPlayerGUID))
                                {
                                    float x, y, z;
                                    creature->GetPosition(x, y, z);
                                    me->CastSpell(player, 91074, false);
                                    player->GetMotionMaster()->MoveJump(x, y, z, 25.0f, 5.0f);
                                    creature->Whisper(SAY_WORGEN_BITE, player->GetGUID(), true);
                                }
                                break;
                            case 2:
                                Event = false;
                                uiEventTimer = 1000;
                                float x, y, z;
                                creature->GetPosition(x, y, z);
                                me->GetMotionMaster()->MoveJump(x, y, z, 25.0f, 10.0f);
                                creature->CastSpell(me, 7105, false);
                                break;
                        }
                }
                else
                    uiEventTimer -= diff;
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

class npc_josiah_avery_human : public CreatureScript
{
public:
    npc_josiah_avery_human() : CreatureScript("npc_josiah_avery_human") { }

    bool OnQuestComplete(Player* player, Creature* creature, const Quest* quest)
    {
        if (quest->GetQuestId() == QUEST_THE_REBEL_LORD_ARSENAL)
        {
            player->RemoveAura(SPELL_ZONE_SPECIFIC_01);
            player->RemoveAura(SPELL_INVISIBILITY_DETECTION_2);
            player->CastSpell(player, SPELL_WORGEN_BITE, true);
            float p_x, p_y;
            player->GetPosition(p_x, p_y);
            float x, y, z, o = creature->GetAngle(p_x, p_y);
            creature->GetPosition(x, y, z);
            player->SaveToDB();

            if (Creature* josiah = player->SummonCreature(NPC_JOSIAH_AVERY_WORGEN, x, y, z, o, TEMPSUMMON_CORPSE_DESPAWN, 10000))
            {
                CAST_AI(npc_josiah_avery_worgen::npc_josiah_avery_worgenAI, josiah->AI())->uiPlayerGUID = player->GetGUID();
                josiah->SetSeerGUID(player->GetGUID());
                josiah->SetVisible(false);
            }
        }

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_josiah_avery_humanAI (creature);
    }

    struct npc_josiah_avery_humanAI : public ScriptedAI
    {
        npc_josiah_avery_humanAI(Creature* creature) : ScriptedAI(creature)
        {
            uiRandomSpeachTimer = urand(5000, 15000);
        }

        uint32 uiRandomSpeachTimer;

        void UpdateAI(const uint32 diff)
        {
            if (uiRandomSpeachTimer <= diff)
            {
                uiRandomSpeachTimer = urand(5000, 15000);
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
                                    Talk(RANDOM_JOSIAH_YELL, player->GetGUID());
            }
            else
                uiRandomSpeachTimer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

///////////
// Quest From the Shadows 14204
///////////

enum qFS
{
    SAY_MASTIFF                    = -1977030,

    QUEST_FROM_THE_SHADOWS         = 14204,

    NPC_GILNEAS_MASTIFF            = 35631,

    SPELL_SUMMON_MASTIFF           = 67807,
    SPELL_ATTACK_LURKER            = 67805,
    SPELL_SHADOWSTALKER_STEALTH    = 5916,
    SPELL_UNDYING_FRENZY           = 80515,
};

class npc_lorna_crowley_qfs : public CreatureScript
{
public:
    npc_lorna_crowley_qfs() : CreatureScript("npc_lorna_crowley_qfs") { }

    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_FROM_THE_SHADOWS)
        {
            player->CastSpell(player, SPELL_SUMMON_MASTIFF, false);
            DoScriptText(SAY_MASTIFF, player);
        }
        return true;
    }

    bool OnQuestComplete(Player* player, Creature* creature, const Quest* quest)
    {
        if (quest->GetQuestId() == QUEST_FROM_THE_SHADOWS)
            if (Unit* charm = Unit::GetCreature(*creature, player->GetMinionGUID()))
                if (charm->GetEntry() == NPC_GILNEAS_MASTIFF)
                    if (Creature* mastiff = charm->ToCreature())
                        mastiff->DespawnOrUnsummon();

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lorna_crowley_qfsAI (creature);
    }

    struct npc_lorna_crowley_qfsAI : public ScriptedAI
    {
        npc_lorna_crowley_qfsAI(Creature* creature) : ScriptedAI(creature)
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
        }

        void UpdateAI(const uint32 /*diff*/)
        {
            if (!UpdateVictim())
                return;
        }
    };
};

class npc_gilneas_mastiff : public CreatureScript
{
public:
    npc_gilneas_mastiff() : CreatureScript("npc_gilneas_mastiff") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gilneas_mastiffAI(creature);
    }

    struct npc_gilneas_mastiffAI : public ScriptedAI
    {
        npc_gilneas_mastiffAI(Creature* creature) : ScriptedAI(creature)
        {
            if (CharmInfo* charm = me->GetCharmInfo())
            {
                SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_ATTACK_LURKER);
                charm->InitEmptyActionBar();
                charm->AddSpellToActionBar(spellInfo);
                me->SetReactState(REACT_DEFENSIVE);
            }
        }

        void UpdateAI(const uint32 /*diff*/)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

class npc_bloodfang_lurker : public CreatureScript
{
public:
    npc_bloodfang_lurker() : CreatureScript("npc_bloodfang_lurker") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bloodfang_lurkerAI (creature);
    }

    struct npc_bloodfang_lurkerAI : public ScriptedAI
    {
        npc_bloodfang_lurkerAI(Creature* creature) : ScriptedAI(creature){}

        bool enrage;
        bool frenzy;

        void Reset()
        {
            enrage = false;
            frenzy = false;
            DoCast(SPELL_SHADOWSTALKER_STEALTH);
            me->SetReactState(REACT_PASSIVE);
        }

        void StartAttack(Unit* who)
        {
            me->SetReactState(REACT_AGGRESSIVE);
            me->SetInCombatWith(who);
            who->SetInCombatWith(me);
            me->AddThreat(who, 100500);
        }

        void DamageTaken(Unit* attacker, uint32 &/*damage*/)
        {
            if (me->HasReactState(REACT_PASSIVE))
                StartAttack(attacker);
        }

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_ATTACK_LURKER)
                StartAttack(caster);
        }

        void UpdateAI(const uint32 /*diff*/)
        {
            if (!UpdateVictim())
                return;

            if (!frenzy && me->HealthBelowPct(45))
            {
                frenzy = true;
                DoCast(SPELL_UNDYING_FRENZY);
            }

            if (!enrage && me->HealthBelowPct(30))
            {
                enrage = true;
                DoCast(SPELL_ENRAGE);
            }

            DoMeleeAttackIfReady();
        }
    };
};

///////////
// Quest Save Krennan Aranas 14293
///////////

enum qSKA
{
    QUEST_SAVE_KRENNAN_ARANAS      = 14293,

    NPC_GENN_HORSE                 = 35905,
    NPC_KRENNAN_ARANAS             = 35753,
    NPC_KRENNAN_ARANAS_SAVE        = 35907,
    NPC_LORD_GOLDFREY              = 35906,
    NPC_QSKA_KILL_CREDIT           = 35753,
    NPC_GUARD_QSKA                 = 35509,
    NPC_WORGEN_QSKA                = 35505,
    NPC_COMMANDEERED_CANNON        = 35914,
    NPC_BLOODFANG_RIPPER_QSKA      = 35916,

    SPELL_CANNON_FIRE              = 68235,
    SPELL_SHOOT_QSKA               = 48424,
    SPELL_CANNON_CAMERA            = 93522,

    HORSE_SAY_SAVE_ARANAS          = -1977026,
    ARANAS_SAY_SAVE_ME             = -1977027,
    ARANAS_THANK                   = -1977028,
    GOLDFREY_SAY_ARANAS_WITH_US    = -1977029,
    ARANAS_SAY_GENN_HORSE          = -1977140,
    GREYMANE_RANDOM_YELL           = -1977158,   // -1977158 to -1977160
};

const float WorgenSummonPos[13][4]=
{
    {-1715.219f, 1352.839f, 19.8645f, 2.72649f},
    {-1721.182f, 1350.429f, 19.8656f, 2.48614f},
    {-1746.523f, 1361.108f, 19.8681f, 1.85957f},
    {-1724.385f, 1348.462f, 19.6781f, 2.10692f},
    {-1734.542f, 1344.554f, 19.8769f, 1.65637f},
    {-1732.773f, 1367.837f, 19.9010f, 1.10063f},
    {-1744.358f, 1363.382f, 19.8996f, 2.06127f},
    {-1719.358f, 1357.512f, 19.7791f, 2.91488f},
    {-1728.276f, 1353.201f, 19.6823f, 2.25370f},
    {-1726.747f, 1364.599f, 19.9263f, 2.71766f},
    {-1737.693f, 1352.986f, 19.8711f, 1.96818f},
    {-1734.391f, 1359.887f, 19.9064f, 2.48052f},
    {-1730.286f, 1390.384f, 20.7707f, 4.35712f},
};

class npc_saved_aranas : public CreatureScript
{
public:
    npc_saved_aranas() : CreatureScript("npc_saved_aranas") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_saved_aranasAI (creature);
    }

    struct npc_saved_aranasAI : public ScriptedAI
    {
        npc_saved_aranasAI(Creature* creature) : ScriptedAI(creature)
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

            if (me->IsSummon())
                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                    if (Vehicle* vehicle = summoner->GetVehicle())
                    {
                        if (vehicle->HasEmptySeat(1))
                            me->EnterVehicle(vehicle->GetBase(), 1);
                        else
                            me->DespawnOrUnsummon();
                    }
        }

        void UpdateAI(const uint32 /*diff*/)
        {
        }
    };
};

class npc_vehicle_genn_horse : public CreatureScript
{
public:
    npc_vehicle_genn_horse() : CreatureScript("npc_vehicle_genn_horse") {}

    struct npc_vehicle_genn_horseAI : public npc_escortAI
    {
        npc_vehicle_genn_horseAI(Creature* creature) : npc_escortAI(creature)
        {
            creature->SetReactState(REACT_PASSIVE);
            AranasIsSave = false;
        }

        bool AranasIsSave;

        void PassengerBoarded(Unit* /*who*/, int8 seatId, bool apply)
        {
            if (!apply)
                return;

            if (seatId != 1)
                return;

            if (Vehicle* vehicle = me->GetVehicleKit())
                if (Unit* passenger = vehicle->GetPassenger(0))
                    if (Player* player = passenger->ToPlayer())
                            DoScriptText(ARANAS_SAY_GENN_HORSE, player);

            SetEscortPaused(false);
            AranasIsSave = true;
            me->SetSpeed(MOVE_WALK, 1.0f, true);
            me->SetSpeed(MOVE_RUN, 1.3f, true);
        }

        void WaypointReached(uint32 point)
        {
            switch(point)
            {
                case 17:
                    if (Unit* passenger = me->GetVehicleKit()->GetPassenger(0))
                    {
                        if (passenger->FindNearestCreature(NPC_KRENNAN_ARANAS, 50.0f))
                            if (Vehicle* vehicle = me->GetVehicleKit())
                                if (Unit* passenger = vehicle->GetPassenger(0))
                                    if (Player* player = passenger->ToPlayer())
                                            DoScriptText(ARANAS_SAY_SAVE_ME, player);

                        me->Whisper(HORSE_SAY_SAVE_ARANAS, passenger->GetGUID(), true);
                    }
                    break;
                case 18:
                    if (!AranasIsSave)
                    {
                        SetEscortPaused(true);
                        me->SetSpeed(MOVE_WALK, 0, true);
                        me->SetSpeed(MOVE_RUN, 0, true);
                    }
                    break;
                case 40:
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(0))
                            if (passenger->ToPlayer())
                            {
                                std::list<Creature*> lGuards;
                                me->GetCreatureListWithEntryInGrid(lGuards, NPC_GUARD_QSKA, 90.0f);

                                if (!lGuards.empty())
                                    for (std::list<Creature*>::const_iterator itr = lGuards.begin(); itr != lGuards.end(); ++itr)
                                        if ((*itr)->IsAlive())
                                            if (Creature* worgen = (*itr)->FindNearestCreature(NPC_WORGEN_QSKA, 90.0f))
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
                                player->KilledMonsterCredit(NPC_QSKA_KILL_CREDIT, 0);

                                if (Unit* passenger_2 = vehicle->GetPassenger(1))
                                    if (passenger_2->ToCreature())
                                        DoScriptText(ARANAS_THANK, player);
                            }
                    break;
                case 43:
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

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_vehicle_genn_horseAI(creature);
    }
};

class npc_king_genn_greymane : public CreatureScript
{
public:
    npc_king_genn_greymane() : CreatureScript("npc_king_genn_greymane") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_SAVE_KRENNAN_ARANAS)
        {
            float x, y;
            creature->GetNearPoint2D(x, y, 2.0f, player->GetOrientation() + M_PI / 2);

            if (Creature* horse = player->SummonCreature(NPC_GENN_HORSE, x, y, creature->GetPositionZ(), creature->GetOrientation()))
                if (npc_escortAI* escort = CAST_AI(npc_escortAI, horse->AI()))
                {
                    escort->AddWaypoint(1, -1799.37f, 1400.21f, 19.8951f);
                    escort->AddWaypoint(2, -1798.23f, 1396.9f, 19.8993f);
                    escort->AddWaypoint(3, -1795.03f, 1388.01f, 19.8898f);
                    escort->AddWaypoint(4, -1790.16f, 1378.7f, 19.8016f);
                    escort->AddWaypoint(5, -1786.41f, 1372.97f, 19.8406f);
                    escort->AddWaypoint(6, -1779.72f, 1364.88f, 19.8131f);
                    escort->AddWaypoint(7, -1774.43f, 1359.87f, 19.7021f);
                    escort->AddWaypoint(8, -1769.0f, 1356.76f, 19.7439f);
                    escort->AddWaypoint(9, -1762.64f, 1356.02f, 19.7979f);
                    escort->AddWaypoint(10, -1758.91f, 1356.08f, 19.8635f);
                    escort->AddWaypoint(11, -1751.95f, 1356.8f, 19.8273f);
                    escort->AddWaypoint(12, -1745.66f, 1357.21f, 19.7993f);
                    escort->AddWaypoint(13, -1738.7f, 1356.64f, 19.7822f);
                    escort->AddWaypoint(14, -1731.79f, 1355.51f, 19.7149f);
                    escort->AddWaypoint(15, -1724.89f, 1354.29f, 19.8661f);
                    escort->AddWaypoint(16, -1718.03f, 1352.93f, 19.7824f);
                    escort->AddWaypoint(17, -1707.68f, 1351.16f, 19.7811f);
                    escort->AddWaypoint(18, -1673.04f, 1344.91f, 15.1353f, 0);
                    escort->AddWaypoint(19, -1673.04f, 1344.91f, 15.1353f);
                    escort->AddWaypoint(20, -1669.32f, 1346.55f, 15.1353f);
                    escort->AddWaypoint(21, -1666.45f, 1349.89f, 15.1353f);
                    escort->AddWaypoint(22, -1665.61f, 1353.85f, 15.1353f);
                    escort->AddWaypoint(23, -1666.04f, 1358.01f, 15.1353f);
                    escort->AddWaypoint(24, -1669.79f, 1360.71f, 15.1353f);
                    escort->AddWaypoint(25, -1673.1f, 1362.11f, 15.1353f);
                    escort->AddWaypoint(26, -1677.12f, 1361.57f, 15.1353f);
                    escort->AddWaypoint(27, -1679.9f, 1360.1f, 15.1353f);
                    escort->AddWaypoint(28, -1682.79f, 1357.56f, 15.1353f);
                    escort->AddWaypoint(29, -1682.79f, 1357.56f, 15.1353f);
                    escort->AddWaypoint(30, -1689.07f, 1352.39f, 15.1353f);
                    escort->AddWaypoint(31, -1691.91f, 1351.83f, 15.1353f);
                    escort->AddWaypoint(32, -1703.81f, 1351.82f, 19.7604f);
                    escort->AddWaypoint(33, -1707.26f, 1352.38f, 19.7826f);
                    escort->AddWaypoint(34, -1712.25f, 1353.55f, 19.7826f);
                    escort->AddWaypoint(35, -1718.2f, 1356.51f, 19.7164f);
                    escort->AddWaypoint(36, -1741.5f, 1372.04f, 19.9569f);
                    escort->AddWaypoint(37, -1746.23f, 1375.8f, 19.9817f);
                    escort->AddWaypoint(38, -1751.06f, 1380.53f, 19.8424f);
                    escort->AddWaypoint(39, -1754.97f, 1386.34f, 19.8474f);
                    escort->AddWaypoint(40, -1760.77f, 1394.37f, 19.9282f);
                    escort->AddWaypoint(41, -1765.11f, 1402.07f, 19.8816f);
                    escort->AddWaypoint(42, -1768.24f, 1410.2f, 19.7833f);
                    escort->AddWaypoint(43, -1772.26f, 1420.48f, 19.9029f);
                    escort->Start(true);
                    player->CastSpell(player, SPELL_GENERIC_QUEST_INVISIBILITY_DERECTION_1, false);
                    player->EnterVehicle(horse, 0);
                    horse->EnableAI();
                }
        }

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_king_genn_greymaneAI (creature);
    }

    struct npc_king_genn_greymaneAI : public ScriptedAI
    {
        npc_king_genn_greymaneAI(Creature* creature) : ScriptedAI(creature)
        {
            uiRandomYellTimer = urand(15000, 35000);
        }

        uint32 uiRandomYellTimer;

        void UpdateAI(const uint32 diff)
        {
            if (uiRandomYellTimer <= diff)
            {
                uiRandomYellTimer = urand(15000, 35000);
                uint8 roll = urand(0, 2);
                DoScriptText(GREYMANE_RANDOM_YELL - roll, me);
            }
            else
                uiRandomYellTimer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

class npc_cannon_camera : public CreatureScript
{
public:
    npc_cannon_camera() : CreatureScript("npc_cannon_camera") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_cannon_cameraAI (creature);
    }

    struct npc_cannon_cameraAI : public ScriptedAI
    {
        npc_cannon_cameraAI(Creature* creature) : ScriptedAI(creature)
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
                if (Creature* cannon = me->FindNearestCreature(NPC_COMMANDEERED_CANNON, 40.0f))
                    cannon->CastSpell(cannon, SPELL_CANNON_FIRE, false);

                for (std::list<Creature*>::iterator itr = lSummons.begin(); itr != lSummons.end(); ++itr)
                    if ((*itr)->IsAlive())
                        (*itr)->Kill(*itr);

                lSummons.clear();
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (Event)
            {
                if (uiEventTimer <= diff)
                {
                    ++uiPhase;

                    switch (uiPhase)
                    {
                        case 1:
                            uiEventTimer = 1500;

                            for (int i = 0; i < 13; ++i)
                                if (Creature* worgen = me->SummonCreature(NPC_BLOODFANG_RIPPER_QSKA, WorgenSummonPos[i][0], WorgenSummonPos[i][1], WorgenSummonPos[i][2], WorgenSummonPos[i][3]))
                                {
                                    lSummons.push_back(worgen);
                                    worgen->GetMotionMaster()->MovePoint(0, -1751.874f + irand(-3, 3), 1377.457f + irand(-3, 3), 19.930f);
                                }
                            break;
                        case 2:
                            uiEventTimer = 2000;
                            if (Creature* cannon = me->FindNearestCreature(NPC_COMMANDEERED_CANNON, 40.0f))
                                cannon->CastSpell(cannon, SPELL_CANNON_FIRE, false);
                            break;
                        case 3:
                            Event = false;
                            if (Creature* cannon = me->FindNearestCreature(NPC_COMMANDEERED_CANNON, 40.0f))
                                cannon->CastSpell(cannon, SPELL_CANNON_FIRE, false);
                            break;
                    }
                }
                else
                    uiEventTimer -= diff;
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

class npc_lord_godfrey_qska : public CreatureScript
{
public:
    npc_lord_godfrey_qska() : CreatureScript("npc_lord_godfrey_qska") { }

    bool OnQuestComplete(Player* player, Creature* /*creature*/, const Quest* quest)
    {
        if (quest->GetQuestId() == QUEST_SAVE_KRENNAN_ARANAS)
        {
            DoScriptText(GOLDFREY_SAY_ARANAS_WITH_US, player);
            player->CastSpell(player, SPELL_CANNON_CAMERA, false);
            player->CastSpell(player, SPELL_INVISIBILITY_DETECTION_2, false);
            player->SaveToDB();
        }

        return true;
    }
};

///////////
// Quest Time to Regroup 14294
///////////

enum qTR
{
    QUEST_TIME_TO_REGROUP     = 14294,

    GENN_SAY_IF               = -1977031,
    CROWLEY_SAY_NEED          = -1977032,
    LIAM_SAY_STAY             = -1977033,
    CROWLEY_SAY_NO_CHANCE     = -1977034,
    CROWLEY_SAY_MY_MEN        = -1977035,
    GENN_SAY_WE_FOOLS         = -1977036,

    NPC_LORD_CROWLEY_QTR      = 35552,
    NPC_PRINCE_LIAM_QTR       = 35551,
};

struct Psc_qtr
{
    uint64 uiPlayerGUID;
    uint32 uiPersonalTimer;
    uint32 uiSpeachId;
};

class npc_king_genn_greymane_qtr : public CreatureScript
{
public:
    npc_king_genn_greymane_qtr() : CreatureScript("npc_king_genn_greymane_qtr") { }

    bool OnQuestComplete(Player* player, Creature* creature, const Quest* quest)
    {
        if (quest->GetQuestId() == QUEST_TIME_TO_REGROUP)
        {
            DoScriptText(GENN_SAY_IF, player);
            Psc_qtr new_psc;
            new_psc.uiSpeachId = 0;
            new_psc.uiPersonalTimer = 7000;
            new_psc.uiPlayerGUID = player->GetGUID();
            CAST_AI(npc_king_genn_greymane_qtrAI, creature->AI())->lPlayerList.push_back(new_psc);
        }

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_king_genn_greymane_qtrAI (creature);
    }

    struct npc_king_genn_greymane_qtrAI : public ScriptedAI
    {
        npc_king_genn_greymane_qtrAI(Creature* creature) : ScriptedAI(creature)
        {
            lPlayerList.clear();
        }

        std::list<Psc_qtr> lPlayerList;

        void DeletePlayer(uint64 uiPlayerGUID)
        {
            for (std::list<Psc_qtr>::iterator itr = lPlayerList.begin(); itr != lPlayerList.end(); )
                if (itr->uiPlayerGUID == uiPlayerGUID)
                    itr = lPlayerList.erase(itr);
                else
                    ++itr;
        }

        void UpdateAI(const uint32 diff)
        {
            if (lPlayerList.empty())
                return;

            for (std::list<Psc_qtr>::iterator itr = lPlayerList.begin(); itr != lPlayerList.end(); )
                if ((*itr).uiPersonalTimer <= diff)
                {
                    ++(*itr).uiSpeachId;

                    if (Player* player = Unit::GetPlayer(*me, (*itr).uiPlayerGUID))
                    {
                        switch ((*itr).uiSpeachId)
                        {
                            case 1:
                                (*itr).uiPersonalTimer = 7000;
                                if (me->FindNearestCreature(NPC_LORD_CROWLEY_QTR, 30.0f))
                                    DoScriptText(CROWLEY_SAY_NEED, player);
                                break;
                            case 2:
                                (*itr).uiPersonalTimer = 4000;
                                if (me->FindNearestCreature(NPC_PRINCE_LIAM_QTR, 30.0f))
                                    DoScriptText(LIAM_SAY_STAY, player);
                                break;
                            case 3:
                                (*itr).uiPersonalTimer = 9000;
                                if (me->FindNearestCreature(NPC_LORD_CROWLEY_QTR, 30.0f))
                                    DoScriptText(CROWLEY_SAY_NO_CHANCE, player);
                                break;
                            case 4:
                                (*itr).uiPersonalTimer = 8000;
                                if (me->FindNearestCreature(NPC_LORD_CROWLEY_QTR, 30.0f))
                                    DoScriptText(CROWLEY_SAY_MY_MEN, player);
                                break;
                            case 5:
                                DoScriptText(GENN_SAY_WE_FOOLS, player);
                                itr = lPlayerList.erase(itr);
                                break;
                        }
                    }
                }
                else
                {
                    (*itr).uiPersonalTimer -= diff;
                    ++itr;
                }
        }
    };
};

///////////
// Quest Sacrifices 14212
///////////

enum qS
{
    QUEST_SACRIFICES                  = 14212,

    NPC_CROWLEYS_HORSE                = 44428,
    NPC_CROWLEYS_HORSE_S_R            = 35231,
    NPC_KING_GENN_GREYMANE_TTR        = 35911,

    SPELL_THROW_TORCH                 = 67063,

    CROWLEY_SAY_START                 = -1977037,
    CROWLEY_RANDOM_SAY                = -1977038, // (-1977038 -1977040)
};

const float SecondRoundWP[90][3]=
{
    {-1537.78f, 1571.12f, 29.207f}, {-1533.40f, 1570.51f, 28.250f}, {-1530.03f, 1570.12f, 27.192f},
    {-1520.44f, 1568.08f, 26.536f}, {-1514.90f, 1567.33f, 24.815f}, {-1508.30f, 1566.47f, 21.499f},
    {-1504.83f, 1566.05f, 20.485f}, {-1500.33f, 1564.15f, 20.485f}, {-1496.13f, 1560.47f, 20.487f},
    {-1493.69f, 1557.95f, 20.496f}, {-1489.17f, 1552.62f, 20.548f}, {-1484.62f, 1547.30f, 20.537f},
    {-1475.44f, 1536.72f, 20.486f}, {-1472.40f, 1533.84f, 20.557f}, {-1466.43f, 1530.20f, 20.568f},
    {-1462.22f, 1528.52f, 20.490f}, {-1456.87f, 1528.10f, 20.521f}, {-1452.68f, 1528.32f, 20.520f},
    {-1450.72f, 1529.05f, 20.491f}, {-1441.65f, 1534.30f, 20.486f}, {-1436.88f, 1539.17f, 20.486f},
    {-1429.22f, 1548.88f, 20.780f}, {-1421.11f, 1560.26f, 20.483f}, {-1417.00f, 1567.17f, 20.481f},
    {-1415.29f, 1575.15f, 20.481f}, {-1416.18f, 1585.83f, 20.482f}, {-1420.30f, 1595.49f, 20.483f},
    {-1425.69f, 1608.41f, 20.483f}, {-1430.94f, 1617.50f, 20.483f}, {-1438.97f, 1627.24f, 20.483f},
    {-1449.65f, 1627.17f, 20.483f}, {-1459.95f, 1625.12f, 20.483f}, {-1473.70f, 1622.50f, 20.483f},
    {-1484.10f, 1621.03f, 20.483f}, {-1498.98f, 1621.02f, 20.483f}, {-1515.94f, 1625.35f, 20.483f},
    {-1526.11f, 1627.95f, 20.483f}, {-1532.26f, 1630.36f, 20.483f}, {-1541.54f, 1635.26f, 21.221f},
    {-1553.93f, 1641.79f, 20.485f}, {-1563.23f, 1646.65f, 20.485f}, {-1568.20f, 1652.36f, 20.485f},
    {-1568.86f, 1656.04f, 20.485f}, {-1567.76f, 1660.69f, 20.485f}, {-1564.39f, 1665.54f, 20.485f},
    {-1559.28f, 1670.33f, 20.485f}, {-1551.64f, 1677.52f, 20.485f}, {-1541.45f, 1687.11f, 20.542f},
    {-1531.94f, 1696.07f, 20.485f}, {-1527.52f, 1697.55f, 20.485f}, {-1522.81f, 1697.94f, 20.485f},
    {-1517.89f, 1696.54f, 20.485f}, {-1512.67f, 1693.46f, 20.485f}, {-1506.65f, 1689.89f, 20.485f},
    {-1500.63f, 1686.32f, 20.485f}, {-1491.86f, 1680.55f, 20.485f}, {-1483.49f, 1674.21f, 20.485f},
    {-1478.02f, 1669.84f, 20.485f}, {-1469.92f, 1663.16f, 20.485f}, {-1463.61f, 1656.18f, 20.485f},
    {-1455.17f, 1646.96f, 20.485f}, {-1450.85f, 1641.46f, 20.485f}, {-1445.68f, 1634.26f, 20.485f},
    {-1441.69f, 1628.50f, 20.485f}, {-1435.71f, 1619.88f, 20.485f}, {-1429.73f, 1611.25f, 20.485f},
    {-1425.96f, 1605.36f, 20.485f}, {-1422.86f, 1599.09f, 20.485f}, {-1420.26f, 1592.59f, 20.485f},
    {-1418.18f, 1585.91f, 20.485f}, {-1418.93f, 1580.32f, 20.485f}, {-1421.21f, 1575.11f, 20.494f},
    {-1424.48f, 1568.92f, 20.485f}, {-1437.43f, 1543.18f, 20.485f}, {-1439.98f, 1540.78f, 20.485f},
    {-1444.94f, 1536.17f, 20.485f}, {-1450.01f, 1533.64f, 20.485f}, {-1456.70f, 1532.84f, 20.485f},
    {-1461.44f, 1533.95f, 20.485f}, {-1466.03f, 1536.72f, 20.485f}, {-1479.46f, 1547.95f, 20.816f},
    {-1484.96f, 1552.27f, 20.781f}, {-1498.70f, 1562.71f, 20.488f}, {-1503.01f, 1566.29f, 20.485f},
    {-1505.76f, 1568.03f, 20.485f}, {-1510.27f, 1569.94f, 22.966f}, {-1514.79f, 1571.84f, 25.271f},
    {-1517.16f, 1572.83f, 26.209f}, {-1525.59f, 1576.24f, 26.537f}, {-1532.30f, 1578.97f, 26.871f},
};


class npc_crowley_horse : public CreatureScript
{
public:
    npc_crowley_horse() : CreatureScript("npc_crowley_horse") {}

    struct npc_crowley_horseAI : public npc_escortAI
    {
        npc_crowley_horseAI(Creature* creature) : npc_escortAI(creature)
        {
            uiRandomSpeachTimer = urand(15000, 25000);
            me->SetReactState(REACT_PASSIVE);
        }

        uint32 uiRandomSpeachTimer;
        Creature* horse;
        Player* passenger;
        Creature* creature;

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 1:
     //               if (Vehicle* pVehicle = me->GetVehicleKit())
                    //    if(!pVehicle->GetPassenger(0))
                    //        passenger->Rio_EnterVehicle(pVehicle,0);
                    //if (Vehicle* pVehicle = me->GetVehicleKit())
                    //        if(!pVehicle->GetPassenger(1))
                    //            creature->Rio_EnterVehicle(pVehicle,1);
                    DoScriptText(CROWLEY_SAY_START, passenger);
                    break;
                case 26:
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    break;
                case 29:
                    if (Vehicle* pVehicle = me->GetVehicleKit())
                    {
                        if (Player* passenger = pVehicle->GetPassenger(0)->ToPlayer())
                            passenger->ExitVehicle();

                        if (Player* passenger = pVehicle->GetPassenger(1)->ToPlayer())
                            passenger->ToCreature()->DespawnOrUnsummon();
                    }
                    me->DespawnOrUnsummon();
                    break;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (uiRandomSpeachTimer <= diff)
            {
                uiRandomSpeachTimer = urand(10000, 20000);
                uint8 roll = urand(0, 2);

    //            if (Vehicle* pVehicle = me->GetVehicleKit())
                //    if(!pVehicle->GetPassenger(0))
                //        passenger->Rio_EnterVehicle(pVehicle,0);
                //if (Vehicle* pVehicle = me->GetVehicleKit())
                //    if(!pVehicle->GetPassenger(1))
                //        creature->Rio_EnterVehicle(pVehicle,1);
                //if (Vehicle* pVehicle = me->GetVehicleKit())
                //    if(pVehicle->GetPassenger(0))
                //        passenger->ExitVehicle();
                //if (Vehicle* pVehicle = me->GetVehicleKit())
                //    if(pVehicle->GetPassenger(1))
                //        creature->ExitVehicle();

                DoScriptText(CROWLEY_RANDOM_SAY - roll, passenger);
            }
            else
                uiRandomSpeachTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_crowley_horseAI(creature);
    }
};

class npc_bloodfang_stalker : public CreatureScript
{
public:
    npc_bloodfang_stalker() : CreatureScript("npc_bloodfang_stalker") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bloodfang_stalkerAI (creature);
    }

    struct npc_bloodfang_stalkerAI : public ScriptedAI
    {
        npc_bloodfang_stalkerAI(Creature* creature) : ScriptedAI(creature) {}

        Player* player;
        uint32 tEnrage;
        uint32 tAnimate;
        uint32 BurningReset;
        bool Miss, willCastEnrage, Burning;

        void Reset()
        {
            tEnrage    = 0;
            tAnimate   = 2000;
            Miss  = false;
            willCastEnrage = urand(0, 1);
            BurningReset = 3000;
            Burning = false;
        }

        void UpdateAI(const uint32 diff)
        {
            if(me->HasAura(SPELL_THROW_TORCH))
            {
                Burning = true;
            }
            else
                Burning = false;

            if (Burning && BurningReset <=diff)
            {
                me->RemoveAllAuras();
                BurningReset = 5000;
                Burning = false;
            }
            else
                BurningReset -= diff;

            if (!UpdateVictim())
            {
                return;
            }

            if (tEnrage <= diff && willCastEnrage)
            {
                if (me->GetHealthPct() <= 30)
                {
                    me->MonsterTextEmote(-106, 0);
                    DoCast(me, SPELL_ENRAGE);
                    tEnrage = 30000;
                }
            }
            else tEnrage -= diff;

            if (me->GetVictim()->GetTypeId() == TYPEID_PLAYER)
            {
                Miss = false;
            }
            else if (me->GetVictim()->IsPet())
            {
                Miss = false;
            }
            else if (me->GetVictim()->GetEntry() == 36057)
            {
                if (me->GetVictim()->GetHealthPct() < 90)
                {
                    Miss = true;
                }
            }

            if (Miss && tAnimate <= diff)
            {
                me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK_UNARMED);
                me->PlayDistanceSound(558);
                tAnimate = 2000;
            }
            else
                tAnimate -= diff;

            if (!Miss)
            {
                DoMeleeAttackIfReady();
            }
        }

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            Creature *horse = me->FindNearestCreature(NPC_CROWLEYS_HORSE, 100, true);
            if (horse && spell->Id == SPELL_THROW_TORCH)
            {
                Burning = true;

                if(me->GetVictim()->GetTypeId() == TYPEID_PLAYER)
                {
                    me->getThreatManager().resetAllAggro();
                    horse->AddThreat(me, 1.0f);
                    me->AddThreat(horse, 1.0f);
                    me->AI()->AttackStart(horse);
                }

                if (caster->GetTypeId() == TYPEID_PLAYER && caster->ToPlayer()->GetQuestStatus(QUEST_SACRIFICES) == QUEST_STATUS_INCOMPLETE)
                {
                    caster->ToPlayer()->KilledMonsterCredit(35582, 0);
                }
            }
        }
    };
};


class npc_crowley_horse_second_round : public CreatureScript
{
public:
    npc_crowley_horse_second_round() : CreatureScript("npc_crowley_horse_second_round") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_crowley_horse_second_roundAI(creature);
    }

    struct npc_crowley_horse_second_roundAI : public npc_escortAI
    {
        npc_crowley_horse_second_roundAI(Creature* creature) : npc_escortAI(creature)
        {
            me->SetReactState(REACT_PASSIVE);
        }

        void FinishEscort()
        {
            me->DespawnOrUnsummon();
        }

        void WaypointReached(uint32 point)
        {
            if (point == 84)
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);
        }
    };
};


class spell_summon_crowley_horse : public SpellScriptLoader
{
    public:
        spell_summon_crowley_horse() : SpellScriptLoader("spell_summon_crowley_horse") { }

        class spell_summon_crowley_horse_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_summon_crowley_horse_SpellScript)

            void OnSummon(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                Player* player = NULL;

                if (Unit* caster = GetCaster())
                    player = caster->ToPlayer();

                if (!player)
                    return;

                //Vehicle* vehicle = NULL;
                Creature* horse = NULL;
                //Creature* crowley = NULL;
                horse = player->SummonCreature(NPC_CROWLEYS_HORSE, -1737.68f, 1655.11f, 20.56283f, 1.64061f);

                if (!horse)
                    return;

                if (npc_escortAI* escort = CAST_AI(npc_escortAI, horse->AI()))
                {
                    if (Creature* greymane = player->FindNearestCreature(NPC_KING_GENN_GREYMANE_TTR, 30.0f))
                        CAST_AI(npc_king_genn_greymane_qtr::npc_king_genn_greymane_qtrAI, greymane->AI())->DeletePlayer(player->GetGUID());

                    //if (Creature* crowley = player->SummonCreature(35230, x, y, z))
                    //    crowley->EnterVehicle(horse, 1, true);

                    //if (Vehicle* pVehicle = horse->GetVehicleKit())
                    //    if (!pVehicle->GetPassenger(0))
                        //{
                        //    player->Rio_EnterVehicle(pVehicle, 0);
                        //    player->ClearUnitState(UNIT_STATE_ONVEHICLE);
                        //}
                    //if (Vehicle* pVehicle = horse->GetVehicleKit())
                    //     if (!pVehicle->GetPassenger(1))
                    //     {
                    //         crowley->Rio_EnterVehicle(pVehicle, 1);
                    //         crowley->ClearUnitState(UNIT_STATE_ONVEHICLE);
                    //     }
                    player->RemoveAura(SPELL_INVISIBILITY_DETECTION_2);
                    horse->EnableAI();
                    escort->AddWaypoint(0, -1737.09f,1663.36f,20.4791f);
                    escort->AddWaypoint(1, -1722.70f,1677.69f,20.3930f,0);
                    escort->AddWaypoint(2, -1700.89f,1653.31f,20.4907f);
                    escort->AddWaypoint(3, -1672.69f,1664.77f,20.4884f);
                    escort->AddWaypoint(4, -1667.30f,1651.55f,20.4884f);
                    escort->AddWaypoint(5, -1666.10f,1626.02f,20.4884f);
                    escort->AddWaypoint(6, -1680.09f,1601.27f,20.4869f);
                    escort->AddWaypoint(7, -1688.33f,1591.46f,20.4869f);
                    escort->AddWaypoint(8, -1733.32f,1592.11f,20.4869f);
                    escort->AddWaypoint(9, -1713.33f,1633.47f,20.4869f);
                    escort->AddWaypoint(10,-1709.09f,1690.63f,20.1549f);
                    escort->AddWaypoint(11,-1678.91f,1704.73f,20.4792f);
                    escort->AddWaypoint(12,-1631.35f,1710.25f,20.4881f);
                    escort->AddWaypoint(13,-1613.85f,1710.41f,22.6797f);
                    escort->AddWaypoint(14,-1590.98f,1710.63f,20.4849f);
                    escort->AddWaypoint(15,-1569.10f,1709.55f,20.4848f,0);
                    escort->AddWaypoint(16,-1553.84f,1701.86f,20.4862f);
                    escort->AddWaypoint(17,-1542.33f,1639.14f,21.1955f);
                    escort->AddWaypoint(18,-1518.09f,1615.94f,20.4865f);
                    escort->AddWaypoint(19,-1475.35f,1626.09f,20.4865f);
                    escort->AddWaypoint(20,-1439.23f,1625.94f,20.4865f);
                    escort->AddWaypoint(21,-1424.39f,1608.56f,20.4867f);
                    escort->AddWaypoint(22,-1415.99f,1581.91f,20.4835f);
                    escort->AddWaypoint(23,-1430.42f,1549.91f,20.7399f);
                    escort->AddWaypoint(24,-1440.54f,1538.35f,20.4858f);
                    escort->AddWaypoint(25,-1473.94f,1536.39f,20.4857f);
                    escort->AddWaypoint(26,-1505.65f,1567.46f,20.4857f);
                    escort->AddWaypoint(27,-1519.51f,1571.06f,26.5095f);
                    escort->AddWaypoint(28,-1531.39f,1581.60f,26.5376f);
                    escort->AddWaypoint(29,-1540.11f,1575.89f,29.209f);
                    escort->SetSpeedZ(18.0f);
                    escort->Start(true);
                    horse->SetInCombatWith(player);
                    horse->AddThreat(player, 100500.0f);
                    float x, y, z;
                    horse->GetPosition(x, y, z);


                }
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_summon_crowley_horse_SpellScript::OnSummon, EFFECT_0, SPELL_EFFECT_SUMMON);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_summon_crowley_horse_SpellScript();
        }
};

class spell_summon_crowley_horse_second_round : public SpellScriptLoader
{
    public:
        spell_summon_crowley_horse_second_round() : SpellScriptLoader("spell_summon_crowley_horse_second_round") { }

        class spell_summon_crowley_horse_second_round_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_summon_crowley_horse_second_round_SpellScript)

            void OnSummon(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                Player* player = NULL;

                if (Unit* caster = GetCaster())
                    player = caster->ToPlayer();

                if (!player)
                    return;

                Creature* horse = NULL;
                horse = player->SummonCreature(NPC_CROWLEYS_HORSE_S_R, -1539.03f, 1570.91f, 29.28873f);

                if (!horse)
                    return;

                if (npc_escortAI* escort = CAST_AI(npc_escortAI, horse->AI()))
                {
                    player->EnterVehicle(horse, 0);
                    horse->EnableAI();

                    for (int i = 0; i < 90; ++i)
                        escort->AddWaypoint(i, SecondRoundWP[i][0], SecondRoundWP[i][1], SecondRoundWP[i][2]);

                    escort->Start(true);
                    horse->SetInCombatWith(player);
                    horse->AddThreat(player, 100500.0f);
                }
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_summon_crowley_horse_second_round_SpellScript::OnSummon, EFFECT_0, SPELL_EFFECT_SUMMON);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_summon_crowley_horse_second_round_SpellScript();
        }
};

///////////
// Quest Last Stand 14222 && Last Chance at Humanity 14375
///////////

enum qLS
{
    QUEST_LAST_STAND                 = 14222,
    QUEST_LAST_CHANCE_AT_HUMANITY    = 14375,

    MOVIE_WORGEN_FORM                = 21,

    NPC_LORD_GODFREY_QLS             = 36330,
    NPC_KRENNAN_ARANAS_QLS           = 36331,
    NPC_KING_GENN_GREYMANE_QLS       = 36332,

    SPELL_PLAY_MOVIE                 = 93477,
    SPELL_HIDEOUS_BITE_WOUND         = 76642,
    SPELL_CURSE_OF_THE_WORGEN        = 68630,
    SPELL_LAST_STAND_COMPLETE        = 72788,
    SPELL_QUEST_ZONE_SPECIFIC        = 68481,

    ARANAS_SAY_YOU_CAN_CONTROL       = -1977070,
    GODFREY_SAY_PUT_DOWN             = -1977071,
    GREYMANE_SAY_TELL_ME_GODFREY     = -1977072,
    GREYMANE_SAY_DIDNT_THINK_SO      = -1977073,

    ACTION_EVENT_DONE                = 1,
};

class npc_lord_darius_crowley_qls : public CreatureScript
{
public:
    npc_lord_darius_crowley_qls() : CreatureScript("npc_lord_darius_crowley_qls") { }

    bool OnQuestComplete(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_LAST_STAND)
        {
            player->setInWorgenForm(UNIT_FLAG2_WORGEN_TRANSFORM3);
            player->SendMovieStart(MOVIE_WORGEN_FORM);
            player->CastSpell(player, SPELL_PLAY_MOVIE, true);
            player->RemoveAura(SPELL_WORGEN_BITE);
            player->CastSpell(player, SPELL_HIDEOUS_BITE_WOUND, true);
            player->CastSpell(player, SPELL_CURSE_OF_THE_WORGEN, true);
            player->CastSpell(player, SPELL_LAST_STAND_COMPLETE, true);
            WorldLocation loc ;
            loc.m_mapId       = 654;
            loc.m_positionX   = -1818.4f;
            loc.m_positionY   = 2294.25f;
            loc.m_positionZ   = 42.2135f;
            player->SetHomebind(loc, 4786);
            player->SaveToDB();
        }
        return true;
    }
};

class npc_king_genn_greymane_qls : public CreatureScript
{
public:
    npc_king_genn_greymane_qls() : CreatureScript("npc_king_genn_greymane_qls") { }

    bool OnQuestComplete(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_LAST_CHANCE_AT_HUMANITY)
        {
            player->RemoveAura(SPELL_CURSE_OF_THE_WORGEN);
            player->RemoveAura(SPELL_HIDEOUS_BITE_WOUND);
            player->CastSpell(player, SPELL_QUEST_ZONE_SPECIFIC, true);
            player->CastSpell(player, 94053, true);
            player->RemoveAura(99488);
            player->RemoveAura(69484);
            player->RemoveAura(68243);
            player->RemoveAura(59087);
            player->RemoveAura(59074);
            player->RemoveAura(59073);
            player->SaveToDB();

            if (creature->IsSummon())
                if (Unit* summoner = creature->ToTempSummon()->GetSummoner())
                    if (Creature* krennan = summoner->ToCreature())
                        krennan->AI()->DoAction(ACTION_EVENT_DONE);
        }
        return true;
    }
};

class npc_krennan_aranas_qls : public CreatureScript
{
public:
    npc_krennan_aranas_qls() : CreatureScript("npc_krennan_aranas_qls") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_krennan_aranas_qlsAI (creature);
    }

    struct npc_krennan_aranas_qlsAI : public ScriptedAI
    {
        npc_krennan_aranas_qlsAI(Creature* creature) : ScriptedAI(creature), lSummons(me)
        {
            Event = false;

            if (!creature->IsSummon())
                creature->DespawnOrUnsummon();
            else
            {
                lSummons.DespawnAll();
                Event = true;
                uiPhase = 1;
                uiGodfreyGUID = 0;
                uiGreymaneGUID = 0;
                uiEventTimer = 5000;
                creature->setActive(true);
            }
        }

        SummonList lSummons;
        uint64 uiGodfreyGUID;
        uint64 uiGreymaneGUID;
        uint32 uiEventTimer;
        uint8 uiPhase;
        bool Event;

        void JustSummoned(Creature* summoned)
        {
            lSummons.Summon(summoned);
            summoned->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
        }

        void DoAction(const int32 action)
        {
            if (action == ACTION_EVENT_DONE)
            {
                lSummons.DespawnAll();
                me->DespawnOrUnsummon();
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (Event)
            {
                if (!me->ToTempSummon()->GetSummoner())
                {
                    lSummons.DespawnAll();
                    me->DespawnOrUnsummon();
                }

                if (uiEventTimer <= diff)
                {
                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        if (Player* player = summoner->ToPlayer())
                            switch (uiPhase)
                            {
                                case 1:
                                    uiEventTimer = 2000;
                                    //if (!(player->GetExtraFlags() & PLAYER_EXTRA_WATCHING_MOVIE))
                                    //    ++uiPhase;
                                    break;
                                case 2:
                                    ++uiPhase;
                                    uiEventTimer = 500;
                                    DoScriptText(ARANAS_SAY_YOU_CAN_CONTROL, player);
                                    if (Creature* godfrey = me->SummonCreature(NPC_LORD_GODFREY_QLS, -1844.92f, 2291.69f, 42.2967f))
                                    {
                                        godfrey->SetSeerGUID(player->GetGUID());
                                        godfrey->SetVisible(false);
                                        uiGodfreyGUID = godfrey->GetGUID();
                                    }
                                    break;
                                case 3:
                                    ++uiPhase;
                                    uiEventTimer = 4500;
                                    if (Creature* godfrey = Unit::GetCreature(*me, uiGodfreyGUID))
                                        godfrey->GetMotionMaster()->MovePoint(0, -1822.22f, 2296.55f, 42.1670f);
                                    break;
                                case 4:
                                    ++uiPhase;
                                    uiEventTimer = 5000;
                                    if (Creature* greymane = me->SummonCreature(NPC_KING_GENN_GREYMANE_QLS, -1844.51f, 2289.50f, 42.3237f))
                                    {
                                        greymane->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                                        greymane->SetSeerGUID(player->GetGUID());
                                        greymane->SetVisible(false);
                                        greymane->GetMotionMaster()->MovePoint(0,-1821.82f, 2293.69f, 42.0869f);
                                        uiGreymaneGUID = greymane->GetGUID();
                                    }
                                    break;
                                case 5:
                                    ++uiPhase;
                                    uiEventTimer = 7000;
                                    if (Creature* godfrey = Unit::GetCreature(*me, uiGodfreyGUID))
                                    {
                                        godfrey->SetFacingToObject(player);
                                        DoScriptText(GODFREY_SAY_PUT_DOWN, player);
                                    }
                                    break;
                                case 6:
                                    ++uiPhase;
                                    uiEventTimer = 9000;
                                    if (Creature* greymane = Unit::GetCreature(*me, uiGreymaneGUID))
                                    {
                                        if (Creature* godfrey = Unit::GetCreature(*me, uiGodfreyGUID))
                                            greymane->SetFacingToObject(godfrey);

                                        DoScriptText(GREYMANE_SAY_TELL_ME_GODFREY, player);
                                        greymane->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
                                    }
                                    break;
                                case 7:
                                    ++uiPhase;
                                    uiEventTimer = 8000;
                                    if (Creature* greymane = Unit::GetCreature(*me, uiGreymaneGUID))
                                    {
                                        greymane->SetFacingToObject(me);
                                        DoScriptText(GREYMANE_SAY_DIDNT_THINK_SO, player);
                                        greymane->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
                                    }
                                    break;
                                case 8:
                                    Event = false;
                                    if (Creature* greymane = Unit::GetCreature(*me, uiGreymaneGUID))
                                    {
                                        greymane->SetFacingToObject(player);
                                        greymane->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                                    }
                                    break;
                            }
                }
                else
                    uiEventTimer -= diff;
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

class spell_curse_of_the_worgen_summon : public SpellScriptLoader
{
    public:
        spell_curse_of_the_worgen_summon() : SpellScriptLoader("spell_curse_of_the_worgen_summon") { }

    class spell_curse_of_the_worgen_summon_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_curse_of_the_worgen_summon_AuraScript);

        void ApplyEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Player* player = GetTarget()->ToPlayer();

            if (!player)
                return;

            if (Creature* krennan = player->SummonCreature(NPC_KRENNAN_ARANAS_QLS, -1819.01f, 2291.30f, 42.1981f, 1.99f))
            {
                krennan->SetSeerGUID(player->GetGUID());
                krennan->SetVisible(false);
                krennan->SetPhaseMask(1024, true);
            }
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_curse_of_the_worgen_summon_AuraScript::ApplyEffect, EFFECT_1, SPELL_AURA_LINKED, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_curse_of_the_worgen_summon_AuraScript();
    }
};

class spell_curse_of_the_worgen_invis : public SpellScriptLoader
{
    public:
        spell_curse_of_the_worgen_invis() : SpellScriptLoader("spell_curse_of_the_worgen_invis") { }

    class spell_curse_of_the_worgen_invis_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_curse_of_the_worgen_invis_AuraScript);

        void ApplyEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            PreventDefaultAction();

            if (Player* player = GetTarget()->ToPlayer())
                player->SetVisible(false);
        }

        void RemoveEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            PreventDefaultAction();

            if (Player* player = GetTarget()->ToPlayer())
                player->SetVisible(true);
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_curse_of_the_worgen_invis_AuraScript::ApplyEffect, EFFECT_0, SPELL_AURA_MOD_INVISIBILITY, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectRemoveFn(spell_curse_of_the_worgen_invis_AuraScript::RemoveEffect, EFFECT_0, SPELL_AURA_MOD_INVISIBILITY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_curse_of_the_worgen_invis_AuraScript();
    }
};

///////////
// Quest In Need of Ingredients 14320
///////////

enum qINI
{
    QUEST_IN_NEED_OF_INGR        = 14320,
    CINEMATIC_FORSAKEN           = 168,
};

class go_crate_of_mandrake_essence : public GameObjectScript
{
public:
    go_crate_of_mandrake_essence() : GameObjectScript("go_crate_of_mandrake_essence"){}

    bool OnQuestComplete(Player* player, GameObject* /*go*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_IN_NEED_OF_INGR)
            player->SendCinematicStart(CINEMATIC_FORSAKEN);

        return true;
    }
};

///////////
// Quest Invasion 14321
///////////

enum qI
{
    QUEST_INVASION               = 14321,

    NPC_FORSAKEN_ASSASSIN        = 36207,

    SPELL_BACKSTAB               = 75360,

    NPC_FORSAKEN_ASSASSIN_SAY    = -1977041,
};

class npc_slain_watchman : public CreatureScript
{
public:
    npc_slain_watchman() : CreatureScript("npc_slain_watchman") { }

    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_INVASION)
        {
            float x, y;
            player->GetNearPoint2D(x, y, 2.0f, player->GetOrientation() + M_PI);

            if (Creature* forsaken = player->SummonCreature(NPC_FORSAKEN_ASSASSIN, x, y, player->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 6000))
            {
                forsaken->AI()->AttackStart(player);
                forsaken->CastSpell(player, SPELL_BACKSTAB, false);
                DoScriptText(NPC_FORSAKEN_ASSASSIN_SAY, player);
            }
        }

        return true;
    }
};

class npc_gwen_armstead_qi : public CreatureScript
{
public:
    npc_gwen_armstead_qi() : CreatureScript("npc_gwen_armstead_qi") { }

    bool OnQuestComplete(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_INVASION)
        {
            player->CastSpell(player, 68482, false);
            player->SaveToDB();
        }

        return true;
    }
};

///////////
// Quest You Can't Take 'Em Alone 14348
///////////

enum qYCTEA
{
    NPC_HORRID_ABOMINATION_KILL_CREDIT    = 36233,
    NPC_PRINCE_LIAM_GREYMANE_QYCTEA       = 36140,

    NPC_HORRID_ABOMINATION_RANDOM_SAY     = -1977042,

    SPELL_KEG_PLACED                      = 68555,
    SPELL_SHOOT_QYCTEA                    = 68559,   // 68559 - а б?а»а¬аќа… а¬а»а«б?ајаЋб?аЌб?а… б?б?б?а≈а б?
    SPELL_RESTITCHING                     = 68864,
    SPELL_EXPLOSION                       = 68560,
    SPELL_EXPLOSION_POISON                = 42266,
    SPELL_EXPLOSION_BONE_TYPE_ONE         = 42267,
    SPELL_EXPLOSION_BONE_TYPE_TWO         = 42274,
};

class npc_horrid_abomination : public CreatureScript
{
public:
    npc_horrid_abomination() : CreatureScript("npc_horrid_abomination") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_horrid_abominationAI (creature);
    }

    struct npc_horrid_abominationAI : public ScriptedAI
    {
        npc_horrid_abominationAI(Creature* creature) : ScriptedAI(creature)
        {
            uiRestitchingTimer = 3000;
            uiShootTimer = 3000;
            uiPlayerGUID = 0;
            shoot = false;
            miss = false;
            me->_ReactDistance = 10.0f;
        }

        uint64 uiPlayerGUID;
        uint32 uiShootTimer;
        uint32 uiRestitchingTimer;
        bool shoot;
        bool miss;

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_KEG_PLACED)
            {
                uint8 roll = urand(0, 5);
                DoScriptText(NPC_HORRID_ABOMINATION_RANDOM_SAY - roll, me);
                shoot = true;
                uiPlayerGUID = caster->GetGUID();
                me->SetReactState(REACT_PASSIVE);
                me->GetMotionMaster()->MoveRandom(5.0f);
                me->CombatStop();

            }

            if (spell->Id == SPELL_SHOOT_QYCTEA)
                ShootEvent();
        }

        void ShootEvent()
        {
            me->RemoveAura(SPELL_KEG_PLACED);

            for (int i = 0; i < 11; ++i)
                DoCast(SPELL_EXPLOSION_POISON);

            for (int i = 0; i < 6; ++i)
                DoCast(SPELL_EXPLOSION_BONE_TYPE_ONE);

            for (int i = 0; i < 4; ++i)
                DoCast(SPELL_EXPLOSION_BONE_TYPE_TWO);

            DoCast(SPELL_EXPLOSION);

            if (Player* player = Unit::GetPlayer(*me, uiPlayerGUID))
                player->KilledMonsterCredit(NPC_HORRID_ABOMINATION_KILL_CREDIT, 0);

            me->DespawnOrUnsummon(1000);
        }

        void DamageTaken(Unit* attacker, uint32 &/*damage*/)
        {
            if (attacker->GetTypeId() != TYPEID_PLAYER)
                return;

            Unit* victim = NULL;

            if (Unit* victim = me->GetVictim())
                if (victim->GetTypeId() == TYPEID_PLAYER)
                    return;

            if (victim)
                me->getThreatManager().modifyThreatPercent(victim, -100);

            AttackStart(attacker);
            me->AddThreat(attacker, 10005000);
        }

        void UpdateAI(const uint32 diff)
        {
            if (shoot)
            {
                if (uiShootTimer <= diff)
                {
                    shoot = false;
                    uiShootTimer = 3000;
                    std::list<Creature*> liamList;
                    GetCreatureListWithEntryInGrid(liamList, me, NPC_PRINCE_LIAM_GREYMANE_QYCTEA, 50.0f);

                    if (liamList.empty())
                        ShootEvent();
                    else
                        (*liamList.begin())->CastSpell(me, SPELL_SHOOT_QYCTEA, false);
                }
                else
                    uiShootTimer -= diff;
            }

            if (!UpdateVictim())
                return;

            if (me->GetVictim() && me->GetVictim()->GetTypeId() == TYPEID_UNIT)
            {
                if (me->GetVictim()->GetHealthPct() < 90)
                    miss = true;
                else
                    miss = false;
            }

            if (uiRestitchingTimer <= diff)
            {
                uiRestitchingTimer = 8000;
                DoCast(SPELL_RESTITCHING);
            }
            else
                uiRestitchingTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

///////////
// Quest Two By Sea 14382
///////////

enum qTBS
{
    NPC_FORSACEN_CATAPILT    = 36283,

    SPELL_LAUNCH             = 66251,
};

class npc_forsaken_catapult_qtbs : public CreatureScript
{
public:
    npc_forsaken_catapult_qtbs() : CreatureScript("npc_forsaken_catapult_qtbs") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_forsaken_catapult_qtbsAI (creature);
    }

    struct npc_forsaken_catapult_qtbsAI : public ScriptedAI
    {
        npc_forsaken_catapult_qtbsAI(Creature* creature) : ScriptedAI(creature)
        {
            me->setActive(true);
            speedXY = 10.0f;
            speedZ = 10.0f;
            creature->GetPosition(x, y, z);
            uiJumpTimer = 2000;
            uiCastTimer = urand(1000, 5000);
            uiRespawnTimer = 10000;
            CanCast = true;
            jump = false;
            respawn = false;
        }

        float speedXY, speedZ, x, y, z;
        uint32 uiCastTimer;
        uint32 uiJumpTimer;
        uint32 uiRespawnTimer;
        bool CanCast;
        bool jump;
        bool respawn;

        void PassengerBoarded(Unit* who, int8 seatId, bool apply)
        {
            if (!apply)
            {
                respawn = true;
                CanCast = false;

                if (seatId == 2)
                    me->setFaction(35);
            }
            else
            {
                respawn = false;

                if (seatId == 2)
                {
                    who->ClearUnitState(UNIT_STATE_ONVEHICLE);
                    CanCast = true;
                }
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (respawn)
            {
                if (uiRespawnTimer <= diff)
                {
                    respawn = false;
                    uiRespawnTimer = 10000;
                    me->DespawnOrUnsummon();
                }
                else
                    uiRespawnTimer -= diff;
            }

            if (CanCast)
            {
                if (uiCastTimer <= diff)
                {
                    uiCastTimer = urand(5000, 20000);
                    float x, y, z;
                    me->GetNearPoint2D(x, y, urand(100, 150), me->GetOrientation());
                    z = me->GetBaseMap()->GetHeight(x, y, MAX_HEIGHT);
                    me->CastSpell(x, y, z, 68591, false);
                }
                else
                    uiCastTimer -= diff;
            }

            if (jump)
            {
                if (uiJumpTimer <= diff)
                {
                    jump = false;
                    uiJumpTimer = 2000;

                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (Unit* passenger = vehicle->GetPassenger(1))
                            if (Player* player = passenger->ToPlayer())
                            {
                                me->AddAura(SPELL_LAUNCH, player);
                                player->ExitVehicle();
                                player->GetMotionMaster()->MoveJump(x, y, z, speedXY, speedZ);
                            }
                }
                else
                    uiJumpTimer -= diff;
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

const float CheckSpellPos[16][3]=
{
    {-2119.36f, 2663.58f, 8.25703f},
    {-2132.94f, 2665.22f, 8.25549f},
    {-2135.20f, 2658.72f, 19.1616f},
    {-2113.73f, 2677.08f, 14.1064f},
    {-2124.71f, 2677.31f, 13.6799f},
    {-2128.56f, 2665.52f, 15.2329f},
    {-2115.82f, 2668.72f, 13.6927f},
    {-2106.92f, 2686.66f, 18.2360f},
    {-2098.44f, 2694.41f, 20.4828f},
    {-2197.74f, 2594.95f, 20.9434f},
    {-2206.71f, 2587.34f, 18.6410f},
    {-2229.45f, 2568.61f, 15.6442f},
    {-2236.70f, 2560.28f, 19.7311f},
    {-2215.77f, 2568.64f, 14.0592f},
    {-2224.96f, 2579.85f, 14.0884f},
    {-2216.07f, 2578.79f, 14.5102f},
};

class spell_launch_qtbs : public SpellScriptLoader
{
    public:
        spell_launch_qtbs() : SpellScriptLoader("spell_launch_qtbs") { }

        class spell_launch_qtbs_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_launch_qtbs_SpellScript)

            void Function(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                bool CheckCast = false;
                float x, y, z;
                x = GetExplTargetDest()->GetPositionX();
                y = GetExplTargetDest()->GetPositionY();
                z = GetExplTargetDest()->GetPositionZ();

                for (int i = 0; i < 16; ++i)
                    if (sqrt(pow(x - CheckSpellPos[i][0], 2) + pow(y - CheckSpellPos[i][1], 2) + pow(z - CheckSpellPos[i][2], 2)) < 10.0f)
                    {
                        CheckCast = true;
                        break;
                    }

                if (!CheckCast)
                    return;

                if (Vehicle* vehicle = caster->GetVehicleKit())
                    if (Unit* passenger = vehicle->GetPassenger(0))
                        if (passenger->GetTypeId() == TYPEID_PLAYER)
                        {
                            passenger->ChangeSeat(1);
                            caster->EnableAI();
                            float speedXY = 10.0f, speedZ = 10.0f;
                            GetTargetSpeedXYZ(speedXY, speedZ);
                            CAST_AI(npc_forsaken_catapult_qtbs::npc_forsaken_catapult_qtbsAI, caster->ToCreature()->AI())->speedXY = speedXY;
                            CAST_AI(npc_forsaken_catapult_qtbs::npc_forsaken_catapult_qtbsAI, caster->ToCreature()->AI())->speedZ = speedZ;
                            CAST_AI(npc_forsaken_catapult_qtbs::npc_forsaken_catapult_qtbsAI, caster->ToCreature()->AI())->x = x;
                            CAST_AI(npc_forsaken_catapult_qtbs::npc_forsaken_catapult_qtbsAI, caster->ToCreature()->AI())->y = y;
                            CAST_AI(npc_forsaken_catapult_qtbs::npc_forsaken_catapult_qtbsAI, caster->ToCreature()->AI())->z = z;
                            CAST_AI(npc_forsaken_catapult_qtbs::npc_forsaken_catapult_qtbsAI, caster->ToCreature()->AI())->jump = true;
                        }
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_launch_qtbs_SpellScript::Function, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_launch_qtbs_SpellScript();
        }
};

///////////
// Quest Save the Children! 14368
///////////

enum qSTC
{
    QUEST_SAVE_THE_CHILDREN    = 14368,

    NPC_CYNTHIA                = 36287,
    NPC_ASHLEY                 = 36288,
    NPC_JAMES                  = 36289,

    NPC_CYNTHIA_SAY            = -1977144,
    NPC_ASHLEY_SAY             = -1977145,
    NPC_JAMES_SAY              = -1977146,

    SPELL_SAVE_CYNTHIA         = 68597,
    SPELL_SAVE_ASHLEY          = 68598,
    SPELL_SAVE_JAMES           = 68596,

    GO_DOOR_TO_THE_BASEMENT    = 196404,
};

#define    PLAYER_SAY_CYNTHIA    "«десь небезопасно. —пустись в подвал фермы јлленов."
#define    PLAYER_SAY_ASHLEY     "Ѕыстрее, беги к остальным в подвал!"
#define    PLAYER_SAY_JAMES      "“во€ мать уже вс€ извелась! Ѕыстрее, беги к ней в подвал!"

class npc_james : public CreatureScript
{
public:
    npc_james() : CreatureScript("npc_james") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_jamesAI (creature);
    }

    struct npc_jamesAI : public npc_escortAI
    {
        npc_jamesAI(Creature* creature) : npc_escortAI(creature)
        {
            uiEventTimer = 3500;
            uiPlayerGUID = 0;
            Event = false;
        }

        uint64 uiPlayerGUID;
        uint32 uiEventTimer;
        bool Event;

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_SAVE_JAMES)
                if (Player* player = caster->ToPlayer())
                {
                    Event = true;
                    uiPlayerGUID = player->GetGUID();
                    player->Say(PLAYER_SAY_JAMES, LANG_UNIVERSAL);
                }
        }

        void WaypointReached(uint32 point)
        {
            if (point == 7)
                if (GameObject* door = me->FindNearestGameObject(GO_DOOR_TO_THE_BASEMENT, 10.0f))
                    door->UseDoorOrButton();
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (Event)
            {
                if (uiEventTimer <= diff)
                {
                    Event = false;
                    uiEventTimer = 3500;

                    if (Player* player = Unit::GetPlayer(*me, uiPlayerGUID))
                    {
                        Start(false, true);
                        DoScriptText(NPC_JAMES_SAY, me, player);
                    }
                }
                else
                    uiEventTimer -= diff;
            }
        }
    };
};

class npc_ashley : public CreatureScript
{
public:
    npc_ashley() : CreatureScript("npc_ashley") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ashleyAI(creature);
    }

    struct npc_ashleyAI : public npc_escortAI
    {
        npc_ashleyAI(Creature* creature) : npc_escortAI(creature)
        {
            uiEventTimer = 3500;
            uiPlayerGUID = 0;
            Event = false;
        }

        uint64 uiPlayerGUID;
        uint32 uiEventTimer;
        bool Event;

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_SAVE_ASHLEY)
                if (Player* player = caster->ToPlayer())
                {
                    Event = true;
                    uiPlayerGUID = player->GetGUID();
                    player->Say(PLAYER_SAY_ASHLEY, LANG_UNIVERSAL);
                }
        }

        void WaypointReached(uint32 point)
        {
            if (point == 16)
                if (GameObject* door = me->FindNearestGameObject(GO_DOOR_TO_THE_BASEMENT, 10.0f))
                    door->UseDoorOrButton();
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (Event)
            {
                if (uiEventTimer <= diff)
                {
                    Event = false;
                    uiEventTimer = 3500;

                    if (Player* player = Unit::GetPlayer(*me, uiPlayerGUID))
                    {
                        Start(false, true);
                        DoScriptText(NPC_ASHLEY_SAY, me, player);
                    }
                }
                else
                    uiEventTimer -= diff;
            }
        }
    };
};

class npc_cynthia : public CreatureScript
{
public:
    npc_cynthia() : CreatureScript("npc_cynthia") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_cynthiaAI(creature);
    }

    struct npc_cynthiaAI : public npc_escortAI
    {
        npc_cynthiaAI(Creature* creature) : npc_escortAI(creature)
        {
            uiEventTimer = 3500;
            uiPlayerGUID = 0;
            Event = false;
        }

        uint64 uiPlayerGUID;
        uint32 uiEventTimer;
        bool Event;

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_SAVE_CYNTHIA)
                if (Player* player = caster->ToPlayer())
                {
                    Event = true;
                    uiPlayerGUID = player->GetGUID();
                    player->Say(PLAYER_SAY_CYNTHIA, LANG_UNIVERSAL);
                }
        }

        void WaypointReached(uint32 point)
        {
            if (point == 8)
                if (GameObject* door = me->FindNearestGameObject(GO_DOOR_TO_THE_BASEMENT, 10.0f))
                    door->UseDoorOrButton();
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (Event)
            {
                if (uiEventTimer <= diff)
                {
                    Event = false;
                    uiEventTimer = 3500;

                    if (Player* player = Unit::GetPlayer(*me, uiPlayerGUID))
                    {
                        Start(false, true);
                        DoScriptText(NPC_CYNTHIA_SAY, me, player);
                    }
                }
                else
                    uiEventTimer -= diff;
            }
        }
    };
};

class npc_lord_godfrey_qatls : public CreatureScript
{
public:
    npc_lord_godfrey_qatls() : CreatureScript("npc_lord_godfrey_qatls") { }

    bool OnQuestComplete(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == 14396)
        {
            player->CastSpell(player, 68483, false);
            player->SaveToDB();
        }

        return false;
    }
};

///////////
// Quest Gasping for Breath 14395
///////////

enum qGFB
{
    QUEST_GASPING_FOR_BREATH          = 14395,

    NPC_QGFB_KILL_CREDIT              = 36450,
    NPC_DROWNING_WATCHMAN             = 36440,

    SPELL_RESCUE_DROWNING_WATCHMAN    = 68735,
    SPELL_SUMMON_SPARKLES             = 69253,
    SPELL_DROWNING                    = 68730,

    GO_SPARKLES                       = 197333,

    DROWNING_WATCHMAN_RANDOM_SAY      = -1977141    // -1977141 to -1977143
};

class npc_drowning_watchman : public CreatureScript
{
public:
    npc_drowning_watchman() : CreatureScript("npc_drowning_watchman") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_drowning_watchmanAI (creature);
    }

    struct npc_drowning_watchmanAI : public ScriptedAI
    {
        npc_drowning_watchmanAI(Creature* creature) : ScriptedAI(creature)
        {
            reset = true;
            despawn = false;
            exit = false;
            uiDespawnTimer = 10000;
        }

        uint32 uiDespawnTimer;
        bool reset;
        bool despawn;
        bool exit;

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_RESCUE_DROWNING_WATCHMAN)
            {
                despawn = false;
                uiDespawnTimer = 10000;
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                me->RemoveAura(SPELL_DROWNING);
                me->EnterVehicle(caster);

                if (GameObject* go = me->FindNearestGameObject(GO_SPARKLES, 10.0f))
                    go->Delete();
            }
        }

        void OnExitVehicle(Unit* /*vehicle*/, uint32 /*seatId*/)
        {
            if (!exit)
            {
                float x, y, z, o;
                me->GetPosition(x, y, z, o);
                me->SetHomePosition(x, y, z, o);
                me->Relocate(x, y, z, o);
                reset = true;
                despawn = true;
                Reset();
            }
        }

        void Reset()
        {
            exit = false;

            if (reset)
            {
                DoCast(SPELL_DROWNING);
                DoCast(SPELL_SUMMON_SPARKLES);
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                reset = false;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (despawn)
            {
                if (uiDespawnTimer <= diff)
                {
                    if (GameObject* go = me->FindNearestGameObject(GO_SPARKLES, 10.0f))
                        go->Delete();

                    reset = true;
                    despawn = false;
                    uiDespawnTimer = 10000;
                    me->DespawnOrUnsummon();
                }
                else
                    uiDespawnTimer -= diff;
            }
        }
    };
};

class npc_prince_liam_greymane : public CreatureScript
{
public:
    npc_prince_liam_greymane() : CreatureScript("npc_prince_liam_greymane") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_prince_liam_greymaneAI (creature);
    }

    struct npc_prince_liam_greymaneAI : public ScriptedAI
    {
        npc_prince_liam_greymaneAI(Creature* creature) : ScriptedAI(creature){}

        void MoveInLineOfSight(Unit* who)
        {
            if (who->GetEntry() == NPC_DROWNING_WATCHMAN)
            {
                if (who->IsInWater() || !who->GetVehicle())
                    return;

                if (who->GetDistance(-1897.0f, 2519.97f, 1.50667f) < 5.0f)
                    if (Unit* unit = who->GetVehicleBase())
                    {
                        if (Creature* watchman = who->ToCreature())
                        {
                            uint8 roll = urand(0, 2);
                            DoScriptText(DROWNING_WATCHMAN_RANDOM_SAY - roll, watchman);
                            watchman->DespawnOrUnsummon(15000);
                            watchman->SetStandState(UNIT_STAND_STATE_KNEEL);
                            CAST_AI(npc_drowning_watchman::npc_drowning_watchmanAI, watchman->AI())->exit = true;
                            CAST_AI(npc_drowning_watchman::npc_drowning_watchmanAI, watchman->AI())->reset = true;
                            who->ExitVehicle();
                            unit->RemoveAura(SPELL_RESCUE_DROWNING_WATCHMAN);
                        }

                        if (Player* player = unit->ToPlayer())
                            player->KilledMonsterCredit(NPC_QGFB_KILL_CREDIT, 0);
                    }
            }
        }

        void UpdateAI(const uint32 /*diff*/)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

///////////
// Quest Grandma's Cat 14401
///////////

enum qGC
{
    NPC_WAHL                 = 36458,
    NPC_WAHL_WORGEN          = 36462,
    NPC_LUCIUS_THE_CRUEL     = 36461,

    SPELL_CATCH_CAT          = 68743,

    SAY_THIS_CAT_IS_MINE     = -1977048,
    YELL_DONT_MESS           = -1977049,

    QUEST_GRANDMAS_CAT       = 14401,

    ACTION_SUMMON_LUCIUS     = 1,
    ACTION_CATCH_CHANCE      = 2,
    ACTION_CHANCE_DESPAWN    = 3,
    POINT_CATCH_CHANCE       = 4,
};

class npc_wahl : public CreatureScript
{
public:
    npc_wahl() : CreatureScript("npc_wahl") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_wahlAI(creature);
    }

    struct npc_wahlAI : public npc_escortAI
    {
        npc_wahlAI(Creature* creature) : npc_escortAI(creature)
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
        }

        void WaypointReached(uint32 point)
        {
            if (point == 1)
                if (me->IsSummon())
                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        {
                            me->UpdateEntry(NPC_WAHL_WORGEN);
                            me->SetReactState(REACT_AGGRESSIVE);
                            me->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
                            AttackStart(summoner);
                        }
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);
        }
    };
};

class npc_lucius_the_cruel : public CreatureScript
{
public:
    npc_lucius_the_cruel() : CreatureScript("npc_lucius_the_cruel") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lucius_the_cruelAI (creature);
    }

    struct npc_lucius_the_cruelAI : public ScriptedAI
    {
        npc_lucius_the_cruelAI(Creature* creature) : ScriptedAI(creature)
        {
            SetCombatMovement(false);
            Catch = false;
            Summon = false;
            uiCatchTimer = 1000;
            uiShootTimer = 500;
            uiPlayerGUID = 0;
            uiSummonTimer = 1500;
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
        }

        uint64 uiPlayerGUID;
        uint32 uiCatchTimer;
        uint32 uiShootTimer;
        uint32 uiSummonTimer;
        bool Catch;
        bool Summon;

        void EnterEvadeMode()
        {
            me->DespawnOrUnsummon();
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type != POINT_MOTION_TYPE)
                return;

            if (id == POINT_CATCH_CHANCE)
            {
                me->HandleEmoteCommand(EMOTE_ONESHOT_KNEEL);
                if (me->IsSummon())
                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        if (Creature* chance = summoner->ToCreature())
                        {
                            Catch = true;
                            Summon = true;
                            chance->AI()->DoAction(ACTION_CHANCE_DESPAWN);
                        }
            }
        }

        void DoAction(const int32 action)
        {
            if (action == ACTION_SUMMON_LUCIUS)
            {
                me->GetMotionMaster()->MovePoint(POINT_CATCH_CHANCE, -2106.372f, 2331.106f, 7.360674f);
                DoScriptText(SAY_THIS_CAT_IS_MINE, me);
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (Catch)
            {
                if (uiCatchTimer <= diff)
                {
                    Catch = false;
                    uiCatchTimer = 1000;
                    me->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
                    me->SetReactState(REACT_AGGRESSIVE);

                    if (Player* player = Unit::GetPlayer(*me, uiPlayerGUID))
                        AttackStart(player);
                }
                else
                    uiCatchTimer -= diff;
            }

            if (Summon)
            {
                if (uiSummonTimer <= diff)
                {
                    Summon = false;
                    uiSummonTimer = 1500;

                    if (Creature* wahl = me->SummonCreature(NPC_WAHL, -2098.366f, 2352.075f, 7.160643f))
                    {
                        DoScriptText(YELL_DONT_MESS, wahl);

                        if (npc_escortAI* npc_escort = CAST_AI(npc_wahl::npc_wahlAI, wahl->AI()))
                        {
                            npc_escort->AddWaypoint(0, -2106.54f,2342.69f,6.93668f);
                            npc_escort->AddWaypoint(1, -2106.12f,2334.90f,7.36691f);
                            npc_escort->AddWaypoint(2, -2117.80f,2357.15f,5.88139f);
                            npc_escort->AddWaypoint(3, -2111.46f,2366.22f,7.17151f);
                            npc_escort->Start(false, true);
                        }
                    }

                }
                else
                    uiSummonTimer -= diff;
            }

            if (!UpdateVictim())
                return;

            if (uiShootTimer <= diff)
            {
                uiShootTimer = 1000;

                if (me->GetDistance(me->GetVictim()) > 2.0f)
                    DoCast(me->GetVictim(), 41440);
            }
            else
                uiShootTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

class npc_chance_the_cat : public CreatureScript
{
public:
    npc_chance_the_cat() : CreatureScript("npc_chance_the_cat") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_chance_the_catAI (creature);
    }

    struct npc_chance_the_catAI : public ScriptedAI
    {
        npc_chance_the_catAI(Creature* creature) : ScriptedAI(creature)
        {
            Despawn = false;
            uiDespawnTimer = 500;
        }

        uint32 uiDespawnTimer;
        bool Despawn;

        void DoAction(const int32 action)
        {
            if (action == ACTION_CHANCE_DESPAWN)
                Despawn = true;
        }

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_CATCH_CAT && caster->GetTypeId() == TYPEID_PLAYER)
            {
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);

                if (Creature* lucius = me->SummonCreature(NPC_LUCIUS_THE_CRUEL, -2111.533f, 2329.95f, 7.390349f))
                {
                    lucius->AI()->DoAction(ACTION_SUMMON_LUCIUS);
                    CAST_AI(npc_lucius_the_cruel::npc_lucius_the_cruelAI, lucius->AI())->uiPlayerGUID = caster->GetGUID();
                }
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (Despawn)
            {
                if (uiDespawnTimer <= diff)
                {
                    uiDespawnTimer = 500;
                    Despawn = false;
                    me->DespawnOrUnsummon();
                }
                else
                    uiDespawnTimer -= diff;
            }
        }
    };
};

///////////
// Quest The Hungry Ettin 14416
///////////

enum qTHE
{
    NPC_MOUNTAIN_HORSE_VEHICLE        = 36540,
    NPC_MOUNTAIN_HORSE_FOLLOWER       = 36555,
    NPC_MOUNTAIN_HORSE_KILL_CREDIT    = 36560,

    QUEST_THE_HUNGRY_ETTIN            = 14416,

    SPELL_ROPE_CHANNEL                = 68940,
    SPELL_ROPE_IN_HORSE               = 68908,

    ACTION_RESCUED_HORSE              = 1,
};

class npc_mountain_horse_vehicle : public CreatureScript
{
public:
    npc_mountain_horse_vehicle() : CreatureScript("npc_mountain_horse_vehicle") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_mountain_horse_vehicleAI (creature);
    }

    struct npc_mountain_horse_vehicleAI : public ScriptedAI
    {
        npc_mountain_horse_vehicleAI(Creature* creature) : ScriptedAI(creature)
        {
            creature->SetReactState(REACT_PASSIVE);
            lSummons.clear();
            uiDespawnTimer = 10000;
            despawn = false;
        }

        std::vector<Creature*> lSummons;
        uint32 uiDespawnTimer;
        bool despawn;

        void OnCharmed(bool /*charm*/)
        {
            me->EnableAI();
        }

        void SpellHit(Unit* /*caster*/, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_ROPE_IN_HORSE)
                me->DespawnOrUnsummon();
        }

        void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply)
        {
            if (apply)
            {
                despawn = false;

                if (lSummons.empty())
                    return;

                for (std::vector<Creature*>::const_iterator itr = lSummons.begin(); itr != lSummons.end(); ++itr)
                    if (*itr)
                        (*itr)->DespawnOrUnsummon();

                lSummons.clear();
            }
            else
            {
                uiDespawnTimer = 10000;
                despawn = true;

                if (me->FindNearestCreature(36457, 30.0f))
                {
                    if (lSummons.empty())
                        return;

                    Player* player = who->ToPlayer();

                    if (!player)
                        return;

                    for (std::vector<Creature*>::const_iterator itr = lSummons.begin(); itr != lSummons.end(); ++itr)
                        if (*itr)
                        {
                            player->KilledMonsterCredit(NPC_MOUNTAIN_HORSE_KILL_CREDIT, 0);
                            (*itr)->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT, 0);
                            (*itr)->SetUInt32Value(UNIT_CHANNEL_SPELL, 0);
                            (*itr)->DespawnOrUnsummon();
                        }

                    lSummons.clear();
                }
                else
                {
                    if (lSummons.empty())
                        return;

                    for (std::vector<Creature*>::const_iterator itr = lSummons.begin(); itr != lSummons.end(); ++itr)
                        if (*itr)
                            (*itr)->DespawnOrUnsummon();

                    lSummons.clear();
                }
            }
        }

        void JustSummoned(Creature* summoned)
        {
            if (summoned->GetEntry() == NPC_MOUNTAIN_HORSE_FOLLOWER)
                lSummons.push_back(summoned);
        }

        void UpdateAI(const uint32 diff)
        {
            if (despawn)
            {
                if (uiDespawnTimer <= diff)
                {
                    despawn = false;
                    uiDespawnTimer = 10000;
                    me->DespawnOrUnsummon();
                }
                else
                    uiDespawnTimer -= diff;
            }
        }
    };
};

class npc_mountain_horse_follower : public CreatureScript
{
public:
    npc_mountain_horse_follower() : CreatureScript("npc_mountain_horse_follower") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_mountain_horse_followerAI(creature);
    }

    struct npc_mountain_horse_followerAI : public FollowerAI
    {
        npc_mountain_horse_followerAI(Creature* creature) : FollowerAI(creature)
        {
            me->SetReactState(REACT_PASSIVE);

            if (me->IsSummon())
                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                    if (Player* player = summoner->ToPlayer())
                    {
                        StartFollow(player);
                        me->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT, player->GetGUID());
                        me->SetUInt32Value(UNIT_CHANNEL_SPELL, SPELL_ROPE_CHANNEL);

                        if (Creature* horse = player->GetVehicleCreatureBase())
                            horse->AI()->JustSummoned(me);
                    }
        }
    };
};

class spell_round_up_horse : public SpellScriptLoader
{
    public:
        spell_round_up_horse() : SpellScriptLoader("spell_round_up_horse") { }

        class spell_round_up_horse_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_round_up_horse_SpellScript)

            void Trigger(SpellEffIndex effIndex)
            {
                Unit* target = GetExplTargetUnit();

                if (Creature* horse = target->ToCreature())
                    if (horse->GetEntry() == NPC_MOUNTAIN_HORSE_VEHICLE)
                        if (Vehicle* vehicle = target->GetVehicleKit())
                            if (vehicle->HasEmptySeat(0))
                                return;

                PreventHitDefaultEffect(effIndex);
            }

            void Register()
            {
                OnEffectLaunch += SpellEffectFn(spell_round_up_horse_SpellScript::Trigger, EFFECT_0, SPELL_EFFECT_TRIGGER_SPELL);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_round_up_horse_SpellScript();
        }
};

///////////
// Quest To Greymane Manor 14465
///////////

enum qTGM
{
    QUEST_TO_GREYMANE_MANOR     = 14465,

    NPC_SWIFT_MOUNTAIN_HORSE    = 36741,

    GO_FIRST_GATE               = 196863,
    GO_SECOND_GATE              = 196864,
};


class npc_swift_mountain_horse : public CreatureScript
{
public:
    npc_swift_mountain_horse() : CreatureScript("npc_swift_mountain_horse") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_swift_mountain_horseAI(creature);
    }

    struct npc_swift_mountain_horseAI : public npc_escortAI
    {
        npc_swift_mountain_horseAI(Creature* creature) : npc_escortAI(creature)
        {
            me->SetReactState(REACT_PASSIVE);
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 3:
                    if (GameObject* go = me->FindNearestGameObject(GO_FIRST_GATE, 30.0f))
                        go->UseDoorOrButton();
                    break;
                case 11:
                    if (GameObject* go = me->FindNearestGameObject(GO_SECOND_GATE, 30.0f))
                        go->UseDoorOrButton();
                    break;
                case 12:
                    if (me->IsSummon())
                        if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                            if (Player* player = summoner->ToPlayer())
                            {
                                WorldLocation loc ;
                                loc.m_mapId       = 654;
                                loc.m_positionX   = -1586.57f;
                                loc.m_positionY   = 2551.24f;
                                loc.m_positionZ   = 130.218f;
                                player->SetHomebind(loc, 817);
                                player->CompleteQuest(14465);
                                player->SaveToDB();
                                //player->SetPhaseMask(0x01, true);
                            }
                    me->DespawnOrUnsummon();
                    break;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);
        }
    };
};

class npc_gwen_armstead : public CreatureScript
{
public:
    npc_gwen_armstead() : CreatureScript("npc_gwen_armstead") { }

    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_TO_GREYMANE_MANOR)
            player->SetPhaseMask(0x01, true);
        {
            float x, y;
            player->GetNearPoint2D(x, y, 2.0f, player->GetOrientation() + M_PI / 4);

            if (Creature* horse = player->SummonCreature(NPC_SWIFT_MOUNTAIN_HORSE, x, y, player->GetPositionZ(), player->GetOrientation()))
                if (npc_escortAI* escort = CAST_AI(npc_escortAI, horse->AI()))
                {
                    player->EnterVehicle(horse, 0);
                    horse->EnableAI();
                    escort->AddWaypoint(0, -1902.86f, 2263.62f, 42.3231f);
                    escort->AddWaypoint(1, -1875.48f, 2292.34f, 42.2551f);
                    escort->AddWaypoint(2, -1852.71f, 2302.98f, 41.8658f);
                    escort->AddWaypoint(3, -1832.20f, 2321.67f, 37.9518f, 2000);
                    escort->AddWaypoint(4, -1799.26f, 2345.02f, 35.7393f);
                    escort->AddWaypoint(5, -1784.89f, 2365.27f, 39.1875f);
                    escort->AddWaypoint(6, -1777.29f, 2413.63f, 52.9219f);
                    escort->AddWaypoint(7, -1767.03f, 2449.39f, 63.1745f);
                    escort->AddWaypoint(8, -1751.81f, 2463.86f, 69.9014f);
                    escort->AddWaypoint(9, -1718.04f, 2465.80f, 80.5825f);
                    escort->AddWaypoint(10, -1705.98f, 2469.33f, 84.9378f);
                    escort->AddWaypoint(11, -1691.09f, 2494.77f, 95.5378f, 2000);
                    escort->AddWaypoint(12, -1672.92f, 2515.75f, 97.8955f);
                    escort->Start(true);
                }
        }
        return true;
    }
};

///////////
// Quest The King's Observatory 14466, Alas, Gilneas! 14467
///////////

enum qTKO_AG
{
    QUEST_THE_KINGS_OBSERVATORY    = 14466,
    QUEST_ALAS_GILNEAS             = 14467,
    QUEST_EXODUS                   = 24438,

    SPELL_ZONE_SPECIFIC_19         = 74096,
    SPELL_ZONE_SPECIFIC_11         = 69484,

    CINEMATIC_TELESCOPE            = 167,
};

class npc_king_genn_greymane_c3 : public CreatureScript
{
public:
    npc_king_genn_greymane_c3() : CreatureScript("npc_king_genn_greymane_c3") { }

    bool OnQuestComplete(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_THE_KINGS_OBSERVATORY)
        {
            player->CastSpell(player, SPELL_CATACLYSM_TYPE_3, false);
            player->CastSpell(player, SPELL_ZONE_SPECIFIC_11, false);
            player->SaveToDB();
        }

        if (quest->GetQuestId() == QUEST_ALAS_GILNEAS)
            player->SendCinematicStart(CINEMATIC_TELESCOPE);

        return true;
    }

    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_EXODUS)
        {
            player->RemoveAura(SPELL_ZONE_SPECIFIC_19);
            player->RemoveAura(99488);
            player->RemoveAura(69484);
            player->RemoveAura(68481);
            player->RemoveAura(68243);
            player->RemoveAura(59087);
            player->RemoveAura(59074);
            player->RemoveAura(59073);
            player->CastSpell(player, SPELL_ZONE_SPECIFIC_11, false);
            player->SaveToDB();
        }

        return true;
    }
};

///////////
// Quest Exodus 24438
///////////

enum qE
{
    NPC_QE_MARIE_ALLEN               = 38853,
    NPC_QE_GWEN_ARMSTEAD             = 44460,
    NPC_QE_KRENNAN_ARANAS            = 36138,
    NPC_QE_DUSKHAVEN_WATCHMAN        = 43907,
    NPC_QE_DUSKHAVEN_WATCHMAN_GUN    = 37946,
    NPC_QE_LORNA_CROWLEY             = 51409,
    NPC_QE_YOUNG_MASTIFF             = 42722,
    NPC_QE_OGRE_AMBUSHER             = 38762,

    GO_GREYMANE_GATE                 = 196401,
    GO_KINGS_GATE                    = 196412,

    LORNA_YELL_CARRIAGE              = -1977050,

    SPELL_THROW_BOULDER              = 72768,

    EXODUS_PHASE_MASK                = 33685504,
};

const float HarnessWP[198][3]=
{
    {-1672.86f, 2516.55f, 97.8940f},{-1679.42f, 2510.07f, 97.8836f},{-1680.65f, 2508.83f, 97.8603f},
    {-1682.52f, 2506.88f, 97.7850f},{-1683.74f, 2505.62f, 97.7018f},{-1685.97f, 2502.77f, 97.4225f},
    {-1687.54f, 2500.73f, 97.0150f},{-1689.60f, 2497.77f, 96.3618f},{-1691.56f, 2494.33f, 95.3775f},
    {-1693.19f, 2491.63f, 94.4497f},{-1700.21f, 2480.20f, 89.6461f},{-1700.21f, 2480.20f, 89.6461f},
    {-1701.82f, 2477.10f, 88.3208f},{-1703.74f, 2472.21f, 86.3349f},{-1704.93f, 2468.06f, 84.8038f},
    {-1704.84f, 2464.45f, 83.8521f},{-1703.79f, 2460.39f, 83.1022f},{-1700.58f, 2452.06f, 81.6085f},
    {-1699.17f, 2447.38f, 80.6009f},{-1698.72f, 2443.68f, 79.6616f},{-1698.72f, 2439.83f, 78.5806f},
    {-1699.03f, 2435.89f, 77.3782f},{-1699.89f, 2431.95f, 76.0359f},{-1701.14f, 2428.75f, 74.8227f},
    {-1703.10f, 2424.78f, 73.0883f},{-1705.94f, 2420.79f, 71.0919f},{-1714.40f, 2409.30f, 65.7187f},
    {-1722.15f, 2398.06f, 62.1128f},{-1724.34f, 2394.89f, 61.4252f},{-1726.05f, 2392.11f, 60.9496f},
    {-1727.84f, 2388.56f, 60.5629f},{-1729.32f, 2384.89f, 60.3927f},{-1730.61f, 2380.17f, 60.3907f},
    {-1731.72f, 2376.48f, 60.6323f},{-1734.81f, 2367.06f, 62.1949f},{-1736.12f, 2363.44f, 63.0386f},
    {-1737.71f, 2359.56f, 63.9578f},{-1739.30f, 2356.05f, 64.7262f},{-1741.02f, 2352.60f, 65.5823f},
    {-1743.04f, 2347.89f, 66.4771f},{-1744.94f, 2342.87f, 67.4789f},{-1745.71f, 2339.46f, 68.1087f},
    {-1746.41f, 2334.04f, 68.9845f},{-1747.39f, 2329.95f, 69.6796f},{-1749.05f, 2324.61f, 70.6220f},
    {-1750.63f, 2319.84f, 71.4891f},{-1752.79f, 2314.18f, 72.6934f},{-1755.33f, 2308.29f, 74.1239f},
    {-1757.75f, 2303.24f, 75.3545f},{-1760.74f, 2297.82f, 76.6115f},{-1763.27f, 2293.36f, 77.5786f},
    {-1765.84f, 2288.51f, 78.6195f},{-1768.73f, 2283.31f, 79.7442f},{-1771.96f, 2279.18f, 80.5957f},
    {-1775.49f, 2274.83f, 81.5637f},{-1778.19f, 2271.45f, 82.3589f},{-1781.42f, 2267.77f, 83.2574f},
    {-1785.36f, 2263.79f, 84.2335f},{-1788.89f, 2260.24f, 85.1407f},{-1792.43f, 2256.86f, 86.0662f},
    {-1795.10f, 2254.78f, 86.7011f},{-1797.38f, 2253.36f, 87.1831f},{-1800.51f, 2251.78f, 87.7887f},
    {-1803.51f, 2250.49f, 88.2882f},{-1806.86f, 2249.12f, 88.7494f},{-1810.80f, 2247.67f, 89.1012f},
    {-1815.26f, 2245.94f, 89.2768f},{-1819.50f, 2243.74f, 89.3141f},{-1823.01f, 2241.15f, 89.3152f},
    {-1827.05f, 2237.52f, 89.3152f},{-1829.64f, 2234.24f, 89.3152f},{-1832.17f, 2230.31f, 89.3152f},
    {-1834.04f, 2227.36f, 89.3152f},{-1847.04f, 2207.00f, 89.3152f},{-1849.34f, 2203.49f, 89.3152f},
    {-1852.05f, 2199.83f, 89.3152f},{-1854.51f, 2196.88f, 89.3152f},{-1857.23f, 2193.82f, 89.3152f},
    {-1860.41f, 2190.41f, 89.3152f},{-1863.10f, 2187.34f, 89.3152f},{-1865.37f, 2183.95f, 89.3152f},
    {-1867.30f, 2180.23f, 89.3152f},{-1869.10f, 2176.31f, 89.3152f},{-1870.31f, 2172.17f, 89.3152f},
    {-1870.89f, 2167.54f, 89.3152f},{-1871.25f, 2162.77f, 89.3152f},{-1871.65f, 2157.78f, 89.3152f},
    {-1872.13f, 2151.85f, 89.3152f},{-1872.48f, 2146.26f, 89.3152f},{-1872.56f, 2140.54f, 89.3152f},
    {-1872.73f, 2134.82f, 89.3152f},{-1872.89f, 2129.81f, 89.3152f},{-1873.05f, 2124.45f, 89.3152f},
    {-1873.13f, 2090.28f, 89.3152f},{-1872.86f, 2085.45f, 89.3152f},{-1872.56f, 2081.02f, 89.3152f},
    {-1872.78f, 2076.59f, 89.3152f},{-1873.25f, 2072.27f, 89.3180f},{-1873.69f, 2068.15f, 89.3180f},
    {-1874.60f, 2064.66f, 89.3180f},{-1876.12f, 2060.87f, 89.3180f},{-1881.88f, 2047.09f, 89.3180f},
    {-1883.68f, 2042.54f, 89.3180f},{-1885.03f, 2038.56f, 89.3180f},{-1885.82f, 2035.27f, 89.3180f},
    {-1886.43f, 2030.41f, 89.3180f},{-1886.48f, 2025.63f, 89.3180f},{-1886.04f, 2008.03f, 89.3180f},
    {-1885.73f, 2004.31f, 89.3180f},{-1884.86f, 1999.37f, 89.3180f},{-1883.38f, 1993.25f, 89.3180f},
    {-1881.41f, 1987.39f, 89.3180f},{-1879.74f, 1982.54f, 89.3180f},{-1878.41f, 1976.86f, 89.3180f},
    {-1877.40f, 1970.76f, 89.1784f},{-1876.46f, 1964.89f, 89.1753f},{-1876.09f, 1959.19f, 89.1462f},
    {-1875.95f, 1944.25f, 89.1361f},{-1876.19f, 1936.32f, 89.1361f},{-1877.17f, 1931.75f, 89.1370f},
    {-1878.18f, 1927.44f, 89.1357f},{-1879.19f, 1923.12f, 89.1357f},{-1880.41f, 1918.98f, 89.1464f},
    {-1881.69f, 1915.72f, 89.1504f},{-1883.60f, 1912.25f, 89.1504f},{-1885.76f, 1909.50f, 89.1504f},
    {-1888.09f, 1907.39f, 89.1504f},{-1891.11f, 1905.41f, 89.1504f},{-1893.98f, 1904.40f, 89.1504f},
    {-1897.16f, 1903.79f, 89.2858f},{-1900.89f, 1903.62f, 89.2858f},{-1989.27f, 1901.26f, 89.2858f},
    {-1992.73f, 1901.72f, 89.2858f},{-1996.43f, 1902.81f, 89.2858f},{-2000.06f, 1904.07f, 89.3037f},
    {-2004.22f, 1905.61f, 88.6846f},{-2017.88f, 1910.70f, 87.2574f},{-2021.90f, 1911.90f, 86.6607f},
    {-2026.83f, 1912.84f, 85.7119f},{-2031.60f, 1913.18f, 84.5859f},{-2037.07f, 1912.87f, 83.0551f},
    {-2042.77f, 1912.41f, 81.2983f},{-2047.88f, 1911.23f, 79.5770f},{-2052.35f, 1909.89f, 77.9273f},
    {-2057.29f, 1908.11f, 75.8834f},{-2061.05f, 1906.53f, 74.1705f},{-2064.73f, 1904.76f, 72.3419f},
    {-2068.25f, 1902.93f, 70.4748f},{-2070.72f, 1901.40f, 69.0681f},{-2073.34f, 1899.65f, 67.5201f},
    {-2076.22f, 1897.46f, 65.7030f},{-2079.34f, 1895.00f, 63.6801f},{-2082.45f, 1892.54f, 61.6431f},
    {-2085.66f, 1889.83f, 59.4803f},{-2099.73f, 1876.36f, 49.4650f},{-2103.91f, 1871.35f, 46.4651f},
    {-2105.24f, 1868.12f, 45.0425f},{-2106.48f, 1863.99f, 43.3699f},{-2107.32f, 1860.36f, 41.9599f},
    {-2108.37f, 1856.66f, 40.4503f},{-2109.77f, 1852.58f, 38.7254f},{-2111.57f, 1848.53f, 36.9247f},
    {-2114.09f, 1843.80f, 34.7661f},{-2116.31f, 1840.10f, 33.0838f},{-2118.76f, 1836.69f, 31.4792f},
    {-2122.27f, 1832.33f, 29.3811f},{-2125.37f, 1829.00f, 27.6824f},{-2129.17f, 1825.38f, 25.7498f},
    {-2133.01f, 1822.33f, 23.9862f},{-2136.39f, 1819.85f, 22.5346f},{-2140.01f, 1817.73f, 21.1382f},
    {-2144.40f, 1815.56f, 19.6024f},{-2148.64f, 1813.93f, 18.3443f},{-2153.52f, 1812.32f, 17.0885f},
    {-2157.99f, 1810.99f, 16.0627f},{-2163.95f, 1809.84f, 14.7597f},{-2169.38f, 1809.12f, 13.6626f},
    {-2173.67f, 1808.70f, 13.0417f},{-2179.26f, 1808.29f, 12.5947f},{-2214.60f, 1807.81f, 11.7800f},
    {-2222.59f, 1805.70f, 11.6520f},{-2227.72f, 1803.75f, 11.6930f},{-2232.96f, 1801.84f, 11.7494f},
    {-2240.47f, 1799.69f, 11.8492f},{-2247.15f, 1798.05f, 11.9347f},{-2252.60f, 1796.76f, 11.9457f},
    {-2257.29f, 1795.35f, 11.8931f},{-2263.04f, 1793.44f, 11.7971f},{-2269.95f, 1790.94f, 11.6187f},
    {-2273.97f, 1789.73f, 11.4691f},{-2278.09f, 1788.93f, 11.3426f},{-2281.56f, 1788.42f, 11.2754f},
    {-2291.59f, 1786.91f, 11.2732f},{-2296.98f, 1784.70f, 11.2823f},{-2302.69f, 1781.34f, 11.2281f},
    {-2307.05f, 1776.95f, 11.1321f},{-2310.64f, 1772.97f, 11.0177f},{-2319.35f, 1762.46f, 11.0401f},
};

class npc_stagecoach_harness_summoner : public CreatureScript
{
public:
    npc_stagecoach_harness_summoner() : CreatureScript("npc_stagecoach_harness_summoner") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_stagecoach_harness_summonerAI (creature);
    }

    struct npc_stagecoach_harness_summonerAI : public ScriptedAI
    {
        npc_stagecoach_harness_summonerAI(Creature* creature) : ScriptedAI(creature)
        {
            me->setActive(true);
            uiEventTimer = 1000;
            Event = true;
        }

        uint32 uiEventTimer;
        bool Event;

        void Reset()
        {
        }

        void OnCharmed(bool /*charm*/)
        {
            me->EnableAI();
        }

        void UpdateAI(const uint32 diff)
        {
            if (Event)
            {
                if (uiEventTimer <= diff)
                {
                    Event = false;

                    if (Unit* carriage = me->GetVehicleKit()->GetPassenger(2))
                    {
                        carriage->SetPhaseMask(EXODUS_PHASE_MASK, false);
                        float x, y, z, o;
                        me->GetPosition(x, y, z, o);

                        if (Creature* marie = me->SummonCreature(NPC_QE_MARIE_ALLEN, x, y, z, o))
                            marie->EnterVehicle(carriage, 1);

                        if (Creature* gwen = me->SummonCreature(NPC_QE_GWEN_ARMSTEAD, x, y, z, o))
                        {
                            gwen->EnterVehicle(carriage, 4);
                            gwen->m_movementInfo.t_pos.m_orientation = M_PI;
                        }

                        if (Creature* krennan = me->SummonCreature(NPC_QE_KRENNAN_ARANAS, x, y, z, o))
                        {
                            krennan->EnterVehicle(carriage, 3);
                            krennan->m_movementInfo.t_pos.m_orientation = M_PI;
                        }

                        if (Creature* watchman = me->SummonCreature(NPC_QE_DUSKHAVEN_WATCHMAN, x, y, z, o))
                        {
                            watchman->EnterVehicle(carriage, 2);
                            watchman->m_movementInfo.t_pos.m_orientation = M_PI;
                        }

                        if (Creature* watchman = me->SummonCreature(NPC_QE_DUSKHAVEN_WATCHMAN_GUN, x, y, z, o))
                            watchman->EnterVehicle(carriage, 5);

                        if (Creature* lorna = me->SummonCreature(NPC_QE_LORNA_CROWLEY, x, y, z, o))
                            lorna->EnterVehicle(carriage, 6);
                    }
                }
                else
                    uiEventTimer -= diff;
            }
        }
    };
};


class npc_stagecoach_harness : public CreatureScript
{
public:
    npc_stagecoach_harness() : CreatureScript("npc_stagecoach_harness") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_stagecoach_harnessAI(creature);
    }

    struct npc_stagecoach_harnessAI : public npc_escortAI
    {
        npc_stagecoach_harnessAI(Creature* creature) : npc_escortAI(creature)
        {
            me->SetReactState(REACT_PASSIVE);
            Event = false;
            uiCarriageGUID = 0;
            uiEventPhase = 0;
            uiEventTimer = 1500;
            SummonList.clear();

            if (creature->IsSummon())
                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                    if (Player* player = summoner->ToPlayer())
                    {
                        me->SetPhaseMask(EXODUS_PHASE_MASK, false);
                        me->SetSeerGUID(player->GetGUID());
                        me->SetVisible(false);
                        player->CompleteQuest(QUEST_EXODUS);
                        Event = true;
                    }
        }

        uint64 uiCarriageGUID;
        uint32 uiEventTimer;
        uint8 uiEventPhase;
        std::list<Creature*> SummonList;
        std::list<Creature*> OrgeList;
        bool Event;

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 93:
                    if (GameObject* go = me->FindNearestGameObject(GO_KINGS_GATE, 30.0f))
                        go->UseDoorOrButton();
                    break;
                case 155:
                    Event = true;
                    GetCreatureListWithEntryInGrid(OrgeList, me, NPC_QE_OGRE_AMBUSHER, 50.0f);
                    if (Unit* carriage = me->GetVehicleKit()->GetPassenger(2))
                        if (carriage->GetVehicleKit()->GetPassenger(6))
                            if (Unit* passenger = carriage->GetVehicleKit()->GetPassenger(0))
                                if (Player* player = passenger->ToPlayer())
                                    DoScriptText(LORNA_YELL_CARRIAGE, player);
                    break;
                case 180:
                    if (me->IsSummon())
                        if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        {
                            summoner->ExitVehicle();
                            summoner->RemoveAura(SPELL_ZONE_SPECIFIC_19);
                            summoner->CastSpell(summoner, SPELL_ZONE_SPECIFIC_11, false);

                            if (Player* player = summoner->ToPlayer())
                                player->SaveToDB();
                        }
                    break;
                case 197:
                    for (std::list<Creature*>::const_iterator itr = SummonList.begin(); itr != SummonList.end(); ++itr)
                        if (*itr)
                        {
                            (*itr)->ExitVehicle();
                            (*itr)->DespawnOrUnsummon();
                        }

                    SummonList.clear();
                    me->DespawnOrUnsummon();
                    break;
            }
        }

        void JustSummoned(Creature* summoned)
        {
            SummonList.push_back(summoned);
        }

        void OgreCast()
        {
            if (OrgeList.empty())
                return;

            for (std::list<Creature*>::const_iterator itr = OrgeList.begin(); itr != OrgeList.end(); ++itr)
            {
                if (!(*itr)->IsAlive())
                    (*itr)->setDeathState(ALIVE);

                float x, y, z;
                me->GetPosition(x, y, z);
                (*itr)->CastSpell(x, y, z, SPELL_THROW_BOULDER, false);
            }
        }

        void StartEvent()
        {
            if (!me->IsVehicle())
                return;

            if (Unit* horse = me->GetVehicleKit()->GetPassenger(0))
                horse->SetPhaseMask(EXODUS_PHASE_MASK, false);

            if (Unit* horse = me->GetVehicleKit()->GetPassenger(1))
                horse->SetPhaseMask(EXODUS_PHASE_MASK, false);

            if (me->IsSummon())
                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                    if (Unit* carriage = me->GetVehicleKit()->GetPassenger(2))
                    {
                        carriage->SetPhaseMask(EXODUS_PHASE_MASK, false);
                        float x, y, z, o;
                        me->GetPosition(x, y, z, o);

                        if (Creature* marie = me->SummonCreature(NPC_QE_MARIE_ALLEN, x, y, z, o))
                        {
                            marie->SetSeerGUID(summoner->GetGUID());
                            marie->SetVisible(false);
                            marie->EnterVehicle(carriage, 1);
                        }

                        if (Creature* gwen = me->SummonCreature(NPC_QE_GWEN_ARMSTEAD, x, y, z, o))
                        {
                            gwen->SetSeerGUID(summoner->GetGUID());
                            gwen->SetVisible(false);
                            gwen->EnterVehicle(carriage, 4);
                            gwen->m_movementInfo.t_pos.m_orientation = M_PI;
                        }

                        if (Creature* krennan = me->SummonCreature(NPC_QE_KRENNAN_ARANAS, x, y, z, o))
                        {
                            krennan->SetSeerGUID(summoner->GetGUID());
                            krennan->SetVisible(false);
                            krennan->EnterVehicle(carriage, 3);
                            krennan->m_movementInfo.t_pos.m_orientation = M_PI;
                        }

                        if (Creature* watchman = me->SummonCreature(NPC_QE_DUSKHAVEN_WATCHMAN, x, y, z, o))
                        {
                            watchman->SetSeerGUID(summoner->GetGUID());
                            watchman->SetVisible(false);
                            watchman->EnterVehicle(carriage, 2);
                            watchman->m_movementInfo.t_pos.m_orientation = M_PI;
                        }

                        if (Creature* watchman = me->SummonCreature(NPC_QE_DUSKHAVEN_WATCHMAN_GUN, x, y, z, o))
                        {
                            watchman->SetSeerGUID(summoner->GetGUID());
                            watchman->SetVisible(false);
                            watchman->EnterVehicle(carriage, 5);
                        }

                        if (Creature* lorna = me->SummonCreature(NPC_QE_LORNA_CROWLEY, x, y, z, o))
                        {
                            lorna->SetSeerGUID(summoner->GetGUID());
                            lorna->SetVisible(false);
                            lorna->EnterVehicle(carriage, 6);
                        }

                        summoner->RemoveAura(SPELL_ZONE_SPECIFIC_11);
                        summoner->CastSpell(summoner, SPELL_ZONE_SPECIFIC_19, false);
                        summoner->EnterVehicle(carriage, 0);

                        if (Creature* mastiff = me->FindNearestCreature(NPC_QE_YOUNG_MASTIFF, 30.0f))
                        {
                            float x, y, z, o;
                            mastiff->GetPosition(x, y, z, o);

                            if (Creature* summon_mastiff = me->SummonCreature(NPC_QE_YOUNG_MASTIFF, x, y, z, o))
                            {
                                summon_mastiff->SetSeerGUID(summoner->GetGUID());
                                summon_mastiff->SetVisible(false);
                                summon_mastiff->GetMotionMaster()->Clear();
                                summon_mastiff->GetMotionMaster()->MoveFollow(me, 1.0f, M_PI / 2, MOTION_SLOT_CONTROLLED);
                            }
                        }

                        for (int i = 0; i < 198; ++i)
                            AddWaypoint(i, HarnessWP[i][0], HarnessWP[i][1], HarnessWP[i][2]);

                        Start(true);

                        if (GameObject* go = me->FindNearestGameObject(GO_GREYMANE_GATE, 30.0f))
                            go->UseDoorOrButton();
                    }
        }

        void UpdateAI(const uint32 diff)
        {
            if (Event)
            {
                if (uiEventTimer <= diff)
                {
                    switch (uiEventPhase)
                    {
                    case 0:
                        Event = false;
                        StartEvent();
                        break;
                    case 1:
                        uiEventTimer = 1000;
                        OgreCast();
                        break;
                    case 2:
                        OgreCast();
                        Event = false;
                        OrgeList.clear();
                        break;
                    }
                    ++uiEventPhase;
                }
                else
                    uiEventTimer -= diff;
            }

            npc_escortAI::UpdateAI(diff);
        }
    };
};

class spell_summon_carriage : public SpellScriptLoader
{
    public:
        spell_summon_carriage() : SpellScriptLoader("spell_summon_carriage") { }

        class spell_summon_carriage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_summon_carriage_SpellScript)

            void SummonHarness(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                if (Unit* caster = GetCaster())
                    caster->SummonCreature(43336, -1665.08f, 2524.78f, 97.9892f, 4.5123f);
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_summon_carriage_SpellScript::SummonHarness, EFFECT_0, SPELL_EFFECT_SUMMON);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_summon_carriage_SpellScript();
        }
};

///////////
// Quest Stranded at the Marsh 24468
///////////

enum qSATM
{
    NPC_SWAMP_CROCOLISK    = 37078,
    SURVIVOR_RANDOM_SAY    = -1977051,    // -1977051 to -1977054
};

class npc_crash_survivor : public CreatureScript
{
public:
    npc_crash_survivor() : CreatureScript("npc_crash_survivor") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_crash_survivorAI (creature);
    }

    struct npc_crash_survivorAI : public ScriptedAI
    {
        npc_crash_survivorAI(Creature* creature) : ScriptedAI(creature)
        {
            summon = false;
            despawn = false;
            uiDespawnTimer= 2000;
        }

        uint32 uiDespawnTimer;
        bool miss;
        bool summon;
        bool despawn;

        void Reset()
        {
            miss = false;

            if (!summon)
            {
                summon = true;
                float x, y;
                me->GetNearPoint2D(x, y, 3.0f, me->GetOrientation());
                me->SummonCreature(NPC_SWAMP_CROCOLISK, x, y, me->GetPositionZ());
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (despawn)
            {
                if (uiDespawnTimer <= diff)
                {
                    despawn = false;
                    summon = false;
                    uiDespawnTimer = 2000;
                    me->DespawnOrUnsummon();
                }
                else
                    uiDespawnTimer -= diff;
            }

            if (!UpdateVictim())
                return;

            if (me->GetVictim()->GetTypeId() == TYPEID_UNIT)
            {
                if (me->GetVictim()->GetHealthPct() < 90)
                    miss = true;
                else
                    miss = false;
            }

            DoMeleeAttackIfReady();
        }
    };
};

class npc_swamp_crocolisk : public CreatureScript
{
public:
    npc_swamp_crocolisk() : CreatureScript("npc_swamp_crocolisk") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_swamp_crocoliskAI (creature);
    }

    struct npc_swamp_crocoliskAI : public ScriptedAI
    {
        npc_swamp_crocoliskAI(Creature* creature) : ScriptedAI(creature){}

        bool miss;

        void Reset()
        {
            miss = false;

            if (me->IsSummon())
                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                {
                    summoner->getThreatManager().resetAllAggro();
                    me->getThreatManager().resetAllAggro();
                    me->CombatStart(summoner);
                    summoner->CombatStart(me);
                }
        }

        void DamageTaken(Unit* attacker, uint32 &/*damage*/)
        {
            if (attacker->GetTypeId() != TYPEID_PLAYER)
                return;

            Unit* victim = NULL;

            if (Unit* victim = me->GetVictim())
                if (victim->GetTypeId() == TYPEID_PLAYER)
                    return;

            if (victim)
                me->getThreatManager().modifyThreatPercent(victim, -100);

            AttackStart(attacker);
            me->AddThreat(attacker, 10005000);
        }

        void JustDied(Unit* /*who*/)
        {
            if (me->IsSummon())
                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                {
                    uint8 roll = urand(0, 3);
                    DoScriptText(SURVIVOR_RANDOM_SAY - roll, summoner);

                    if (Creature* surv = summoner->ToCreature())
                        CAST_AI(npc_crash_survivor::npc_crash_survivorAI, surv->AI())->despawn = true;
                }
        }

        void UpdateAI(const uint32 /*diff*/)
        {
            if (!UpdateVictim())
                return;

            if (me->GetVictim()->GetTypeId() == TYPEID_UNIT)
            {
                if (me->GetVictim()->GetHealthPct() < 90)
                    miss = true;
                else
                    miss = false;
            }

            DoMeleeAttackIfReady();
        }
    };
};

///////////
// Quest Introductions Are in Order 24472
///////////

enum qIAO
{
    QUEST_INTRODUCTIONS_ARE_IN_ORDER          = 24472,

    NPC_KOROTH_THE_HILLBREAKER_QIAO           = 36294,
    NPC_KOROTH_THE_HILLBREAKER_QIAO_FRIEND    = 37808,
    NPC_CAPTAIN_ASTHER_QIAO                   = 37806,
    NPC_FORSAKEN_SOLDIER_QIAO                 = 37805,
    NPC_FORSAKEN_CATAPULT_QIAO                = 37807,

    KOROTH_YELL_WHO_STEAL_BANNER              = -1977085,
    KOROTH_YELL_FIND_YOU                      = -1977086,
    LIAN_SAY_HERE_FORSAKEN                    = -1977087,
    LIAM_YELL_YOU_CANT                        = -1977088,
    CAPITAN_YELL_WILL_ORDER                   = -1977089,
    KOROTH_YELL_MY_BANNER                     = -1977090,

    SPELL_PUSH_BANNER                         = 70511,
    SPELL_CLEAVE                              = 16044,
    SPELL_DEMORALIZING_SHOUT_QIAO             = 16244,

    POINT_BANNER                              = 1,
    ACTION_KOROTH_ATTACK                      = 2,
};

struct Psc_qiao
{
    uint64 uiPlayerGUID;
    uint64 uiCapitanGUID;
    uint32 uiEventTimer;
    uint8 uiPhase;
};

struct sSoldier
{
    Creature* soldier;
    float follow_angle;
    float follow_dist;
};

const float AstherWP[18][3]=
{
    {-2129.99f, 1824.12f, 25.234f},{-2132.93f, 1822.23f, 23.984f},{-2135.81f, 1820.23f, 22.770f},
    {-2138.72f, 1818.29f, 21.595f},{-2141.77f, 1816.57f, 20.445f},{-2144.88f, 1814.96f, 19.380f},
    {-2147.19f, 1813.85f, 18.645f},{-2150.51f, 1812.73f, 17.760f},{-2153.88f, 1811.80f, 16.954f},
    {-2157.28f, 1810.95f, 16.194f},{-2160.69f, 1810.20f, 15.432f},{-2164.12f, 1809.46f, 14.688f},
    {-2167.55f, 1808.81f, 13.961f},{-2171.01f, 1808.27f, 13.316f},{-2174.32f, 1808.00f, 12.935f},
    {-2177.11f, 1807.75f, 12.717f},{-2179.79f, 1807.67f, 12.573f},{-2183.06f, 1807.59f, 12.504f},
};

const float KorothWP[14][3]=
{
    {-2213.64f, 1863.51f, 15.404f},{-2212.69f, 1860.14f, 15.302f},{-2211.15f, 1853.31f, 15.078f},
    {-2210.39f, 1849.90f, 15.070f},{-2209.11f, 1845.65f, 15.377f},{-2206.19f, 1839.29f, 15.147f},
    {-2204.92f, 1836.03f, 14.420f},{-2203.76f, 1832.73f, 13.432f},{-2201.68f, 1826.04f, 12.296f},
    {-2200.68f, 1822.69f, 12.194f},{-2199.22f, 1818.77f, 12.175f},{-2196.29f, 1813.86f, 12.253f},
    {-2192.46f, 1811.06f, 12.445f},{-2186.79f, 1808.90f, 12.513f},
};


class npc_koroth_the_hillbreaker_qiao_friend : public CreatureScript
{
public:
    npc_koroth_the_hillbreaker_qiao_friend() : CreatureScript("npc_koroth_the_hillbreaker_qiao_friend") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_koroth_the_hillbreaker_qiao_friendAI (creature);
    }

    struct npc_koroth_the_hillbreaker_qiao_friendAI : public npc_escortAI
    {
        npc_koroth_the_hillbreaker_qiao_friendAI(Creature* creature) : npc_escortAI(creature)
        {
            me->setActive(true);
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            uiCleaveTimer = 250;
            uiDemoralizingShoutTimer = 500;

            if (me->IsSummon())
            {
                for (int i = 0; i < 14; ++i)
                    AddWaypoint(i, KorothWP[i][0], KorothWP[i][1], KorothWP[i][2]);

                Start();
                SetRun(true);
            }
        }

        uint32 uiCleaveTimer;
        uint32 uiDemoralizingShoutTimer;

        void FinishEscort()
        {
            if (me->IsSummon())
                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                {
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

                    if (Creature* capitan = summoner->ToCreature())
                        capitan->AI()->DoAction(ACTION_KOROTH_ATTACK);

                    if (summoner->IsSummon())
                        if (Unit* _summoner = summoner->ToTempSummon()->GetSummoner())
                            if (Player* player = _summoner->ToPlayer())
                                DoScriptText(KOROTH_YELL_MY_BANNER, player/*, true*/);
                }
        }
        void WaypointReached(uint32 /*point*/) { }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (!UpdateVictim())
                return;

            if (uiCleaveTimer <= diff)
            {
                uiCleaveTimer = urand(2500, 15000);
                DoCast(me->GetVictim(), SPELL_CLEAVE);
            }
            else
                uiCleaveTimer -= diff;

            if (uiDemoralizingShoutTimer <= diff)
            {
                uiDemoralizingShoutTimer = 5000;
                DoCast(SPELL_DEMORALIZING_SHOUT_QIAO);
            }
            else
                uiDemoralizingShoutTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

class npc_captain_asther_qiao : public CreatureScript
{
public:
    npc_captain_asther_qiao() : CreatureScript("npc_captain_asther_qiao") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_captain_asther_qiaoAI (creature);
    }

    struct npc_captain_asther_qiaoAI : public npc_escortAI
    {
        npc_captain_asther_qiaoAI(Creature* creature) : npc_escortAI(creature)
        {
            me->setActive(true);
            uiKorothGUID = 0;
            lSoldiers.clear();
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

            if (me->IsSummon())
                StartEvent();
        }

        std::list<sSoldier> lSoldiers;
        uint64 uiKorothGUID;

        void JustDied(Unit* /*who*/)
        {
            me->DespawnOrUnsummon(15000);

            if (Creature* koroth = Unit::GetCreature(*me, uiKorothGUID))
                koroth->DespawnOrUnsummon(15000);

            if (lSoldiers.empty())
                return;

            for (std::list<sSoldier>::iterator itr = lSoldiers.begin(); itr != lSoldiers.end(); ++itr)
            {
                Creature* soldier = itr->soldier;
                soldier->DespawnOrUnsummon(15000);
            }
        }

        void DoAction(const int32 action)
        {
            if (action == ACTION_KOROTH_ATTACK)
                if (Creature* koroth = Unit::GetCreature(*me, uiKorothGUID))
                {
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    AttackStart(koroth);
                    me->AddThreat(koroth, 100500);
                    koroth->AddThreat(me, 100500);
                    float x, y, z;
                    koroth->GetNearPoint(koroth, x, y, z, 0.0f, 1.0f, koroth->GetOrientation() + M_PI);
                    me->GetMotionMaster()->MoveCharge(x, y, z);

                    if (lSoldiers.empty())
                        return;

                    for (std::list<sSoldier>::iterator itr = lSoldiers.begin(); itr != lSoldiers.end(); ++itr)
                    {
                        Creature* soldier = itr->soldier;
                        soldier->SetReactState(REACT_AGGRESSIVE);
                        soldier->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        soldier->AI()->AttackStart(koroth);
                        soldier->AddThreat(koroth, 100500);

                        if (soldier->GetEntry() == NPC_FORSAKEN_CATAPULT_QIAO)
                        {
                            koroth->AddThreat(soldier, 200500);
                            koroth->AI()->AttackStart(soldier);
                            continue;
                        }

                        koroth->AddThreat(soldier, 10000);
                        soldier->GetMotionMaster()->MoveCharge(x, y, z);
                    }
                }
        }

        void StartMoveTo(float x, float y, float z)
        {
            if (lSoldiers.empty())
                return;

            float pathangle = atan2(me->GetPositionY() - y, me->GetPositionX() - x);

            for (std::list<sSoldier>::iterator itr = lSoldiers.begin(); itr != lSoldiers.end(); ++itr)
            {
                Creature* member = itr->soldier;

                if (!member->IsAlive() || member->GetVictim())
                    continue;

                float angle = itr->follow_angle;
                float dist = itr->follow_dist;

                float dx = x - std::cos(angle + pathangle) * dist;
                float dy = y - std::sin(angle + pathangle) * dist;
                float dz = z;

                Trinity::NormalizeMapCoord(dx);
                Trinity::NormalizeMapCoord(dy);

                member->UpdateGroundPositionZ(dx, dy, dz);

                if (member->IsWithinDist(me, dist + 5.0f))
                    member->SetUnitMovementFlags(me->GetUnitMovementFlags());
                else
                    member->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);

                member->GetMotionMaster()->MovePoint(0, dx, dy, dz);
                member->SetHomePosition(dx, dy, dz, pathangle);
            }
        }

        void SummonSoldier(uint64 guid, uint32 SoldierEntry, float dist, float angle)
        {
            float x, y;
            me->GetNearPoint2D(x, y, dist, me->GetOrientation() + angle);
            float z = me->GetBaseMap()->GetHeight(x, y, MAX_HEIGHT);

            if (Creature* soldier = me->SummonCreature(SoldierEntry, x, y, z))
            {
                soldier->SetReactState(REACT_PASSIVE);
                soldier->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                soldier->SetSeerGUID(guid);
                soldier->SetVisible(false);
                soldier->setActive(true);
                sSoldier new_soldier;
                new_soldier.soldier = soldier;
                new_soldier.follow_angle = angle;
                new_soldier.follow_dist = dist;
                lSoldiers.push_back(new_soldier);
            }
        }

        void StartEvent()
        {
            if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                if (Player* player = summoner->ToPlayer())
                {
                    uint64 uiPlayerGUID = player->GetGUID();

                    for (int i = 1; i < 4; ++i)
                    {
                        SummonSoldier(uiPlayerGUID, NPC_FORSAKEN_SOLDIER_QIAO, i * 2, M_PI);
                        SummonSoldier(uiPlayerGUID, NPC_FORSAKEN_SOLDIER_QIAO, i * 2, M_PI -  M_PI / (2 * i));
                        SummonSoldier(uiPlayerGUID, NPC_FORSAKEN_SOLDIER_QIAO, i * 2, M_PI +  M_PI / (2 * i));
                    }

                    SummonSoldier(uiPlayerGUID, NPC_FORSAKEN_CATAPULT_QIAO, 8.0f, M_PI);

                    for (int i = 0; i < 18; ++i)
                        AddWaypoint(i, AstherWP[i][0], AstherWP[i][1], AstherWP[i][2]);

                    Start();
                }
        }

        void WaypointReached(uint32 point)
        {
            if (point == 15)
                if (Creature* koroth = me->SummonCreature(NPC_KOROTH_THE_HILLBREAKER_QIAO_FRIEND, -2213.64f, 1863.51f, 15.404f))
                    uiKorothGUID = koroth->GetGUID();
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

class npc_prince_liam_greymane_qiao : public CreatureScript
{
public:
    npc_prince_liam_greymane_qiao() : CreatureScript("npc_prince_liam_greymane_qiao") { }

    bool OnQuestComplete(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_INTRODUCTIONS_ARE_IN_ORDER)
            CAST_AI(npc_prince_liam_greymane_qiaoAI, creature->AI())->StartEvent(player);

        if (quest->GetQuestId() == QUEST_EXODUS)
        {
            WorldLocation loc ;
            loc.m_mapId       = 654;
            loc.m_positionX   = -245.84f;
            loc.m_positionY   = 1550.56f;
            loc.m_positionZ   = 18.6917f;
            player->SetHomebind(loc, 4731);
            player->SaveToDB();
        }

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_prince_liam_greymane_qiaoAI (creature);
    }

    struct npc_prince_liam_greymane_qiaoAI : public ScriptedAI
    {
        npc_prince_liam_greymane_qiaoAI(Creature* creature) : ScriptedAI(creature)
        {
            lPlayerList.clear();
        }

        std::list<Psc_qiao> lPlayerList;

        void StartEvent(Player* player)
        {
            if (!player)
                return;

            uint64 uiPlayerGUID = player->GetGUID();
            Psc_qiao new_player;
            new_player.uiPlayerGUID = uiPlayerGUID;
            new_player.uiCapitanGUID = 0;
            new_player.uiEventTimer = 0;
            new_player.uiPhase = 0;
            Creature* capitan = NULL;

            if (Creature* capitan = player->SummonCreature(NPC_CAPTAIN_ASTHER_QIAO, -2120.19f, 1833.06f, 30.1510f,  3.87363f))
            {
                capitan->SetSeerGUID(player->GetGUID());
                capitan->SetVisible(false);
                new_player.uiCapitanGUID = capitan->GetGUID();
            }

            if (!capitan)
                return;

            lPlayerList.push_back(new_player);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!lPlayerList.empty())
                for (std::list<Psc_qiao>::iterator itr = lPlayerList.begin(); itr != lPlayerList.end(); )
                {
                    if (itr->uiEventTimer <= diff)
                    {
                        ++itr->uiPhase;

                        if (Player* player = Unit::GetPlayer(*me, itr->uiPlayerGUID))
                            switch (itr->uiPhase)
                            {
                                case 1:
                                    itr->uiEventTimer = 8000;
                                    DoScriptText(LIAN_SAY_HERE_FORSAKEN, player/*, true*/);
                                    break;
                                case 2:
                                    itr->uiEventTimer = 5000;
                                    me->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
                                    DoScriptText(LIAM_YELL_YOU_CANT, player/*, true*/);
                                    break;
                                case 3:
                                    itr->uiEventTimer = 3000;
                                    me->CastSpell(me, SPELL_PUSH_BANNER/*, false*/);
                                    break;
                                case 4:
                                    if (Unit::GetCreature(*me, itr->uiCapitanGUID))
                                        DoScriptText(CAPITAN_YELL_WILL_ORDER, player/*, true*/);
                                    itr = lPlayerList.erase(itr);
                                    break;
                            }
                    }
                    else
                    {
                        itr->uiEventTimer -= diff;
                        ++itr;
                    }
                }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

class npc_koroth_the_hillbreaker_qiao : public CreatureScript
{
public:
    npc_koroth_the_hillbreaker_qiao() : CreatureScript("npc_koroth_the_hillbreaker_qiao") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_koroth_the_hillbreaker_qiaoAI(creature);
    }

    struct npc_koroth_the_hillbreaker_qiaoAI : public ScriptedAI
    {
        npc_koroth_the_hillbreaker_qiaoAI(Creature* creature) : ScriptedAI(creature)
        {
            uiEventTimer = 5000;
            Event = false;
        }

        uint32 uiEventTimer;
        bool Event;

        void MovementInform(uint32 type, uint32 id)
        {
            if (type != POINT_MOTION_TYPE)
                return;

            if (id == POINT_BANNER)
                me->GetMotionMaster()->MoveTargetedHome();
        }

        void UpdateAI(const uint32 diff)
        {
            if (Event)
            {
                if (uiEventTimer <=  diff)
                {
                    Event = false;
                    uiEventTimer = 5000;
                    DoScriptText(KOROTH_YELL_FIND_YOU, me);
                }
                else
                    uiEventTimer -= diff;
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

class go_koroth_banner : public GameObjectScript
{
public:
    go_koroth_banner() : GameObjectScript("go_koroth_banner") {}

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_INTRODUCTIONS_ARE_IN_ORDER) == QUEST_STATUS_INCOMPLETE)
            if (Creature* koroth = go->FindNearestCreature(NPC_KOROTH_THE_HILLBREAKER_QIAO, 30.0f))
            {
                DoScriptText(KOROTH_YELL_WHO_STEAL_BANNER, koroth);
                float x, y;
                go->GetNearPoint2D(x, y, 5.0f, go->GetOrientation() + M_PI / 2);
                koroth->GetMotionMaster()->MovePoint(POINT_BANNER, x, y, go->GetPositionZ());
                CAST_AI(npc_koroth_the_hillbreaker_qiao::npc_koroth_the_hillbreaker_qiaoAI, koroth->AI())->Event = true;
            }

        return false;
    }
};

class npc_koroth_the_hillbreaker : public CreatureScript
{
public:
    npc_koroth_the_hillbreaker() : CreatureScript("npc_koroth_the_hillbreaker") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_koroth_the_hillbreakerAI (creature);
    }

    struct npc_koroth_the_hillbreakerAI : public ScriptedAI
    {
        npc_koroth_the_hillbreakerAI(Creature* creature) : ScriptedAI(creature){}

        void UpdateAI(const uint32 /*diff*/)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

///////////
// Quest Losing Your Tail 24616
///////////

enum qLYT
{
    QUEST_LOSING_YOUR_TAIL      = 24616,

    NPC_DARK_SCOUT              = 37953,

    NPC_DARK_SCOUT_SAY_CATCH    = -1977055,
    NPC_DARK_SCOUT_SAY_FREE     = -1977056,
    NPC_DARK_SCOUT_SAY_HOW      = -1977057,

    SPELL_AIMED_SHOT            = 15620,
    SPELL_FREEZING_TRAP         = 70794,

    ACTION_PLAYER_IS_FREE       = 1,
};

class npc_dark_scout_summoner : public CreatureScript
{
public:
    npc_dark_scout_summoner() : CreatureScript("npc_dark_scout_summoner") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_dark_scout_summonerAI (creature);
    }

    struct npc_dark_scout_summonerAI : public ScriptedAI
    {
        npc_dark_scout_summonerAI(Creature* creature) : ScriptedAI(creature){}

        void MoveInLineOfSight(Unit* who)
        {
            if (Player* player = who->ToPlayer())
                if (me->IsWithinDistInMap(player, 20.0f) && player->GetQuestStatus(QUEST_LOSING_YOUR_TAIL) == QUEST_STATUS_INCOMPLETE)
                {
                    if (player->IsInCombat())
                        return;

                    if (Creature* scout = me->SummonCreature(NPC_DARK_SCOUT, -2239.28f, 1429.67f, -22.86f))
                    {
                        scout->AddAura(SPELL_FREEZING_TRAP, player);
                        DoScriptText(NPC_DARK_SCOUT_SAY_CATCH, scout);
                        scout->Whisper(NPC_DARK_SCOUT_SAY_FREE, player->GetGUID(), true);
                        scout->AI()->AttackStart(player);
                        scout->CastSpell(who, SPELL_AIMED_SHOT, false);
                    }
                }
        }

        void UpdateAI(const uint32 /*diff*/)
        {
            if (!UpdateVictim())
                return;
        }
    };
};

class npc_dark_scout : public CreatureScript
{
public:
    npc_dark_scout() : CreatureScript("npc_dark_scout") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_dark_scoutAI (creature);
    }

    struct npc_dark_scoutAI : public ScriptedAI
    {
        npc_dark_scoutAI(Creature* creature) : ScriptedAI(creature)
        {
            me->AddUnitState(UNIT_STATE_ROOT);
            me->AddUnitMovementFlag(MOVEMENTFLAG_ROOT);
        }

        void Reset()
        {
            shot = true;
            uiShotTimer = 2000;
        }

        uint32 uiShotTimer;
        bool shot;

        void EnterEvadeMode()
        {
            me->DespawnOrUnsummon();
        }

        void DoAction(const int32 action)
        {
            if (action == ACTION_PLAYER_IS_FREE)
            {
                DoScriptText(NPC_DARK_SCOUT_SAY_HOW, me);
                shot = false;
                me->CastStop();
                me->ClearUnitState(UNIT_STATE_ROOT);
                me->RemoveUnitMovementFlag(MOVEMENTFLAG_ROOT);
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (shot)
            {
                if (uiShotTimer <= diff)
                {
                    uiShotTimer = 2000;
                    DoCast(me->GetVictim(), SPELL_AIMED_SHOT);
                }
                else
                    uiShotTimer -= diff;
            }

            DoMeleeAttackIfReady();
        }
    };
};

class spell_belysras_talisman : public SpellScriptLoader
{
    public:
        spell_belysras_talisman() : SpellScriptLoader("spell_belysras_talisman") { }

        class spell_belysras_talisman_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_belysras_talisman_SpellScript)

            void DispellStun(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                Unit* target = GetExplTargetUnit();
                Unit* caster = GetCaster();

                if (!target || !caster)
                    return;

                if (Aura* aur = caster->GetAura(SPELL_FREEZING_TRAP))
                {
                    if (Unit* owner = aur->GetCaster())
                        if (Creature* scout = owner->ToCreature())
                            scout->AI()->DoAction(ACTION_PLAYER_IS_FREE);

                    caster->RemoveAura(SPELL_FREEZING_TRAP);
                }
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_belysras_talisman_SpellScript::DispellStun, EFFECT_1, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_belysras_talisman_SpellScript();
        }
};

///////////
// Quest Take Back What's Ours 24646
///////////

enum qTBWO
{
    QUEST_TAKE_BACK_WHATS_OURS     = 24646,

    NPC_TOBIAS_MISTMANTLE_QTBWO    = 38029,
    NPC_TALDOREN_TRACKER           = 38027,
    NPC_VETERAN_DARK_RANGER        = 38022,

    TOBIAS_SAY_DISTRACT_RANGERS    = -1977061,
    TOBIAS_SAY_FALL_BACK           = -1977062,

    SPELL_WAR_STOMP                = 71019,

    ACTION_BACK                    = 2,
};

static float WorgensBackPos[8][3] =
{
    {-2148.38f,1606.51f,-43.7285f},
    {-2131.82f,1588.68f,-48.6709f},
    {-2124.88f,1575.87f,-49.9036f},
    {-2114.25f,1538.97f,-14.2722f},
    {-2124.04f,1601.32f,-43.8004f},
    {-2115.53f,1595.73f,-46.1633f},
    {-2107.05f,1590.90f,-47.7032f},
    {-2092.86f,1584.43f,-20.3403f}
};

class npc_taldoren_tracker : public CreatureScript
{
public:
    npc_taldoren_tracker() : CreatureScript("npc_taldoren_tracker") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_taldoren_trackerAI(creature);
    }

    struct npc_taldoren_trackerAI : public npc_escortAI
    {
        npc_taldoren_trackerAI(Creature* creature) : npc_escortAI(creature)
        {
            creature->SetReactState(REACT_PASSIVE);
            creature->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
        }

        void DoAction(const int32 action)
        {
            if (action == ACTION_BACK)
            {
                DoCast(SPELL_WAR_STOMP);
                me->SetReactState(REACT_PASSIVE);
                me->CombatStop();
                SetEscortPaused(false);
            }
        }

        void WaypointReached(uint32 point)
        {
            if (point == 2)
                me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);
        }
    };
};

class npc_tobias_mistmantle_qtbwo : public CreatureScript
{
public:
    npc_tobias_mistmantle_qtbwo() : CreatureScript("npc_tobias_mistmantle_qtbwo") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tobias_mistmantle_qtbwoAI (creature);
    }

    struct npc_tobias_mistmantle_qtbwoAI : public ScriptedAI
    {
        npc_tobias_mistmantle_qtbwoAI(Creature* creature) : ScriptedAI(creature), lSummons(me)
        {
            uiEventTimer = 25000;
            Event = true;
            creature->SetReactState(REACT_PASSIVE);
            creature->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);

            if (creature->IsSummon())
                SummonTrackers();
        }

        SummonList lSummons;
        uint32 uiEventTimer;
        bool Event;

        void SummonTrackers()
        {
            std::list<Creature*> RangerList;
            me->GetCreatureListWithEntryInGrid(RangerList, NPC_VETERAN_DARK_RANGER, 80.0f);

            if (RangerList.empty())
                return;

            DoScriptText(TOBIAS_SAY_DISTRACT_RANGERS, me, me->ToTempSummon()->GetSummoner());

            for (std::list<Creature*>::const_iterator itr = RangerList.begin(); itr != RangerList.end(); ++itr)
            {
                if ((*itr)->IsAlive())
                {
                    Position pos;
                    (*itr)->GetNearPosition(pos, 2.0f, (*itr)->GetOrientation());

                    if (Creature* tracker = me->SummonCreature(NPC_TALDOREN_TRACKER, pos))
                    {
                        lSummons.Summon(tracker);

                        if (npc_escortAI* npc_escort = CAST_AI(npc_taldoren_tracker::npc_taldoren_trackerAI, tracker->AI()))
                        {
                            float dist_1 = pos.GetExactDist2d(WorgensBackPos[0][0], WorgensBackPos[0][1]);
                            float dist_2 = pos.GetExactDist2d(WorgensBackPos[4][0], WorgensBackPos[4][1]);

                            int j = (dist_1 < dist_2) ? 0 : 4;

                            npc_escort->AddWaypoint(0, pos.m_positionX, pos.m_positionY, pos.m_positionZ, 0/*, true*/);

                            for (int i = 0; i < 4; ++i)
                            {
                                const Position src = {WorgensBackPos[j + i][0], WorgensBackPos[j + i][1], WorgensBackPos[j + i][2], 0};
                                Position dst;
                                me->GetRandomPoint(src, 5.0f, dst);
                                npc_escort->AddWaypoint(i + 1, dst.m_positionX, dst.m_positionY, dst.m_positionZ, 0);
                            }

                            npc_escort->SetEscortPaused(true);
                            npc_escort->Start(true, true);
                            tracker->SetReactState(REACT_AGGRESSIVE);
                            tracker->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
                            tracker->CombatStart((*itr));
                            (*itr)->CombatStart(tracker);
                        }
                    }
                }
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (Event)
            {
                if (uiEventTimer <= diff)
                {
                    Event = false;
                    DoScriptText(TOBIAS_SAY_FALL_BACK, me);
                    //lSummons.DoAction(NPC_TALDOREN_TRACKER, ACTION_BACK);
                    me->DespawnOrUnsummon(2000);
                }
                else
                    uiEventTimer -= diff;
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

class spell_horn_of_taldoren : public SpellScriptLoader
{
    public:
        spell_horn_of_taldoren() : SpellScriptLoader("spell_horn_of_taldoren") { }

        class spell_horn_of_taldoren_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_horn_of_taldoren_SpellScript)

            void SummonWorgens(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                Unit* caster = GetCaster();
                if (!caster || caster->GetTypeId() != TYPEID_PLAYER)
                    return;

                float x = -2146.12f, y = 1583.35f;
                float d = caster->GetExactDist2d(x, y);

                if (d > 30.0f)
                    return;

                if (caster->FindNearestCreature(NPC_TOBIAS_MISTMANTLE_QTBWO, 40.0f))
                    return;

                if (caster->ToPlayer()->GetQuestStatus(QUEST_TAKE_BACK_WHATS_OURS) == QUEST_STATUS_INCOMPLETE)
                    caster->SummonCreature(NPC_TOBIAS_MISTMANTLE_QTBWO, -2146.12f, 1583.35f, -48.8068f, 1.239184f);
            }

            void Register()
            {
                OnEffectLaunch += SpellEffectFn(spell_horn_of_taldoren_SpellScript::SummonWorgens, EFFECT_0, SPELL_EFFECT_SEND_EVENT);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_horn_of_taldoren_SpellScript();
        }
};

///////////
// Quest Neither Human Nor Beast 24593
///////////

enum qNHNB
{
    // quest
    NPC_TRIGGER                         = 35374,
    NPC_LYROS_SWIFTWIND                 = 37870,

    QUEST_NEITHER_HUMAN_NOR_BEAST       = 24593,

    GO_WELL_OF_FURY                     = 201950,
    GO_WELL_OF_TRANQUILITY              = 201951,
    GO_WELL_OF_BALANCE                  = 201952,

    SPELL_TALDOREN_WELL                 = 71200,

    LYROS_SAY_WELL_OF_FURY              = -1977074,
    VASSANDRA_SAY_WELL_OF_TRANQUILITY   = -1977075,
    TALRAN_SAY_WELL_OF_BALANCE          = -1977076,

    // cutscene after quest
    NPC_KING_GENN_GREYMANE_WORGEN       = 31177,
    NPC_KING_GENN_GREYMANE_HUMAN        = 38767,
    NPC_LORD_DARIUS_CROWLEY_QNHNB       = 37195,
    NPC_LORNA_CROWLEY_QNHNB             = 38768,
    NPC_LORD_GODFREY_QNHNB              = 38766,

    LORNA_YELL_FATHER                   = -1977077,
    CROWLEY_YELL_LORNA                  = -1977078,
    GODFREY_SAY_LOW                     = -1977079,
    CROWLEY_YELL_FROG                   = -1977080,
    GREYMANE_SAY_NO_FRIEND              = -1977081,
    GODFREY_YELL_CANT_BE                = -1977082,
    CROWLEY_SAY_YES_GENN                = -1977083,
    CREYMANE_SAY_HELD                   = -1977084,

    SPELL_WORGEN_COMBAT_TRANSFORM_FX    = 81768,
};

class go_qnhnb_well : public GameObjectScript
{
public:
    go_qnhnb_well() : GameObjectScript("go_qnhnb_well"){}

    void SummonPersonalTrigger(Player* player, GameObject* go)
    {
        float x, y, z;
        go->GetPosition(x, y, z);

        if (Creature* trigger = player->SummonCreature(NPC_TRIGGER, x, y, z, 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 15000))
        {
            trigger->SetSeerGUID(player->GetGUID());
            trigger->SetVisible(false);
            trigger->AddAura(SPELL_TALDOREN_WELL, trigger);
        }
    }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_NEITHER_HUMAN_NOR_BEAST) == QUEST_STATUS_INCOMPLETE)
        {
            QuestStatusMap::iterator itr = player->getQuestStatusMap().find(QUEST_NEITHER_HUMAN_NOR_BEAST);

            switch (go->GetEntry())
            {
                case GO_WELL_OF_FURY:
                    if (itr->second.CreatureOrGOCount[0] == 0)
                    {
                        player->CastedCreatureOrGO(go->GetEntry(), go->GetGUID(), 0);
                        SummonPersonalTrigger(player, go);

                        if (go->FindNearestCreature(NPC_LYROS_SWIFTWIND, 30.0f))
                            DoScriptText(LYROS_SAY_WELL_OF_FURY, player);
                    }
                    break;
                case GO_WELL_OF_TRANQUILITY:
                    if (itr->second.CreatureOrGOCount[1] == 0)
                    {
                        player->CastedCreatureOrGO(go->GetEntry(), go->GetGUID(), 0);
                        SummonPersonalTrigger(player, go);

                        if (go->FindNearestCreature(37873, 30.0f))
                            DoScriptText(VASSANDRA_SAY_WELL_OF_TRANQUILITY, player);
                    }
                    break;
                case GO_WELL_OF_BALANCE:
                    if (itr->second.CreatureOrGOCount[2] == 0)
                    {
                        player->CastedCreatureOrGO(go->GetEntry(), go->GetGUID(), 0);
                        SummonPersonalTrigger(player, go);

                        if (go->FindNearestCreature(36814, 30.0f))
                            DoScriptText(TALRAN_SAY_WELL_OF_BALANCE, player);
                    }
                    break;
            }
        }
        return true;
    }
};

class npc_lord_godfrey_qnhnb : public CreatureScript
{
public:
    npc_lord_godfrey_qnhnb() : CreatureScript("npc_lord_godfrey_qnhnb") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lord_godfrey_qnhnbAI(creature);
    }

    struct npc_lord_godfrey_qnhnbAI : public npc_escortAI
    {
        npc_lord_godfrey_qnhnbAI(Creature* creature) : npc_escortAI(creature) {}

        void WaypointReached(uint32 point)
        {
            if (point == 2)
                if (Creature* crowley = me->FindNearestCreature(NPC_LORD_DARIUS_CROWLEY_QNHNB, 30.0f))
                    me->SetFacingToObject(crowley);
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);
        }
    };
};

class npc_lorna_crowley_qnhnb : public CreatureScript
{
public:
    npc_lorna_crowley_qnhnb() : CreatureScript("npc_lorna_crowley_qnhnb") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lorna_crowley_qnhnbAI(creature);
    }

    struct npc_lorna_crowley_qnhnbAI : public npc_escortAI
    {
        npc_lorna_crowley_qnhnbAI(Creature* creature) : npc_escortAI(creature)
        {
            uiSayTimer = 1000;
            say = false;
        }

        uint32 uiSayTimer;
        bool say;

        void WaypointReached(uint32 point)
        {
            if (point == 1)
                if (me->IsSummon())
                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        if (Player* player = summoner->ToPlayer())
                        {
                            SetRun(false);
                            say = true;
                            DoScriptText(LORNA_YELL_FATHER, player);
                        }

            if (point == 2)
                if (Creature* crowley = me->FindNearestCreature(NPC_LORD_DARIUS_CROWLEY_QNHNB, 30.0f))
                    me->SetFacingToObject(crowley);
        }

        void UpdateAI(const uint32 diff)
        {
            if (say)
            {
                if (uiSayTimer <= diff)
                {
                    say = false;

                    if (me->FindNearestCreature(NPC_LORD_DARIUS_CROWLEY_QNHNB, 30.0f))
                        if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                            if (Player* player = summoner->ToPlayer())
                                DoScriptText(CROWLEY_YELL_LORNA , player);
                }
                else
                    uiSayTimer -= diff;
            }

            npc_escortAI::UpdateAI(diff);
        }
    };
};

class npc_king_genn_greymane_qnhnb : public CreatureScript
{
public:
    npc_king_genn_greymane_qnhnb() : CreatureScript("npc_king_genn_greymane_qnhnb") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_king_genn_greymane_qnhnbAI(creature);
    }

    struct npc_king_genn_greymane_qnhnbAI : public npc_escortAI
    {
        npc_king_genn_greymane_qnhnbAI(Creature* creature) : npc_escortAI(creature)
        {
            uiLornaGUID = 0;
            uiGodfreyGUID = 0;
            uiEventTimer = 0;
            uiPhase = 0;
            Event= false;
            StartEvent();
        }

        uint64 uiLornaGUID;
        uint64 uiGodfreyGUID;
        uint32 uiEventTimer;
        uint8 uiPhase;
        bool Event;

        void StartEvent()
        {
            if (!me->IsSummon())
            {
                me->DespawnOrUnsummon();
                return;
            }

            if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                if (Player* player = summoner->ToPlayer())
                {
                    Start(false);
                    SetDespawnAtEnd(false);
                    me->setActive(true);

                    if (Creature* lorna = player->SummonCreature(NPC_LORNA_CROWLEY_QNHNB, -2104.00f, 1282.00f, -83.7271f))
                    {
                        uiLornaGUID = lorna->GetGUID();
                        lorna->SetSeerGUID(player->GetGUID());
                        lorna->SetVisible(false);
                        CAST_AI(npc_lorna_crowley_qnhnb::npc_lorna_crowley_qnhnbAI, lorna->AI())->Start(false, true);
                        CAST_AI(npc_lorna_crowley_qnhnb::npc_lorna_crowley_qnhnbAI, lorna->AI())->SetDespawnAtEnd(false);
                    }

                    if (Creature* godfrey = player->SummonCreature(NPC_LORD_GODFREY_QNHNB, -2110.44f, 1288.52f, -83.5184f))
                    {
                        uiGodfreyGUID = godfrey->GetGUID();
                        godfrey->SetSeerGUID(player->GetGUID());
                        godfrey->SetVisible(false);
                        CAST_AI(npc_lord_godfrey_qnhnb::npc_lord_godfrey_qnhnbAI, godfrey->AI())->Start(false);
                        CAST_AI(npc_lord_godfrey_qnhnb::npc_lord_godfrey_qnhnbAI, godfrey->AI())->SetDespawnAtEnd(false);
                    }
                }
        }

        void WaypointReached(uint32 point)
        {
            if (point == 2)
            {
                Event = true;

                if (Creature* crowley = me->FindNearestCreature(NPC_LORD_DARIUS_CROWLEY_QNHNB, 30.0f))
                    me->SetFacingToObject(crowley);
            }
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (Event)
            {
                if (uiEventTimer <= diff)
                {
                    ++uiPhase;

                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        if (Player* player = summoner->ToPlayer())
                            switch (uiPhase)
                            {
                                case 1:
                                    uiEventTimer= 13000;
                                    if (Creature* godfrey = Unit::GetCreature(*me, uiGodfreyGUID))
                                    {
                                        godfrey->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                                        DoScriptText(GODFREY_SAY_LOW, player);
                                    }
                                    break;
                                case 2:
                                    uiEventTimer= 8000;
                                    if (me->FindNearestCreature(NPC_LORD_DARIUS_CROWLEY_QNHNB, 30.0f))
                                        DoScriptText(CROWLEY_YELL_FROG, player);
                                    break;
                                case 3:
                                    uiEventTimer= 4000;
                                    DoCast(SPELL_WORGEN_COMBAT_TRANSFORM_FX);
                                    DoScriptText(GREYMANE_SAY_NO_FRIEND, player);
                                    break;
                                case 4:
                                    uiEventTimer= 2000;
                                    if (Unit::GetCreature(*me, uiGodfreyGUID))
                                        DoScriptText(GODFREY_YELL_CANT_BE, player);
                                    break;
                                case 5:
                                    uiEventTimer= 11000;
                                    if (Creature* crowley = me->FindNearestCreature(NPC_LORD_DARIUS_CROWLEY_QNHNB, 30.0f))
                                    {
                                        crowley->HandleEmoteCommand(EMOTE_ONESHOT_YES);
                                        DoScriptText(CROWLEY_SAY_YES_GENN, player);
                                    }
                                    break;
                                case 6:
                                    uiEventTimer= 15000;
                                    DoScriptText(CREYMANE_SAY_HELD, player);
                                    break;
                                case 7:
                                    Event = false;
                                    if (Creature* godfrey = Unit::GetCreature(*me, uiGodfreyGUID))
                                        godfrey->DespawnOrUnsummon();
                                    if (Creature* lorna = Unit::GetCreature(*me, uiLornaGUID))
                                        lorna->DespawnOrUnsummon();
                                    me->DespawnOrUnsummon();
                                    break;
                            }
                }
                else
                    uiEventTimer -= diff;
            }
        }
    };
};

class spell_worgen_combat_transform_fx : public SpellScriptLoader
{
    public:
        spell_worgen_combat_transform_fx() : SpellScriptLoader("spell_worgen_combat_transform_fx") { }

        class spell_worgen_combat_transform_fx_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_worgen_combat_transform_fx_SpellScript)

            void Transform(SpellEffIndex /*effIndex*/)
            {
                Unit* target = GetCaster();

                if (!target)
                    return;

                if (Creature* greymane = target->ToCreature())
                    if (greymane->GetEntry() == NPC_KING_GENN_GREYMANE_HUMAN)
                        greymane->SetDisplayId(NPC_KING_GENN_GREYMANE_WORGEN);
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_worgen_combat_transform_fx_SpellScript::Transform, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_worgen_combat_transform_fx_SpellScript();
        }
};


///////////
// Quest At Our Doorstep 24627
///////////

enum qAOD
{
    QUEST_AT_OUR_DOORSTEP           = 24627,

    NPC_TOBIAS_MISTMANTLE_QAOD      = 38051,
    NPC_LORD_DARIUS_CROWLEY_QAOD    = 37195,

    TOBIAS_SAY_FORSAKEN             = -1977058,
    CROWLEY_SAY_IMMEDIATELY         = -1977059,
    TOBIAS_SAY_OK                   = -1977060,

    POINT_NEAR_CROWLEY              = 1,
};

const float TobiasWP[4][3]=
{
    {-2073.85f, 1295.89f, -84.1445f},
    {-2071.12f, 1283.95f, -85.7678f},
    {-2073.66f, 1293.04f, -84.5568f},
    {-2073.56f, 1308.08f, -83.2562f},
};

class npc_tobias_mistmantle_qaod : public CreatureScript
{
public:
    npc_tobias_mistmantle_qaod() : CreatureScript("npc_tobias_mistmantle_qaod") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tobias_mistmantle_qaodAI (creature);
    }

    struct npc_tobias_mistmantle_qaodAI : public npc_escortAI
    {
        npc_tobias_mistmantle_qaodAI(Creature* creature) : npc_escortAI(creature)
        {
            uiSpeachTimer = 5000;
            uiSpeachId = 0;
            InPosition = false;
        }

        uint32 uiSpeachTimer;
        uint8 uiSpeachId;
        bool InPosition;

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
            case 1:
                if (me->IsSummon())
                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        if (Player* player = summoner->ToPlayer())
                        {
                            DoScriptText(TOBIAS_SAY_FORSAKEN, player);
                            InPosition = true;
                            SetEscortPaused(true);
                        }
                break;
            case 3:
                me->DespawnOrUnsummon();
                break;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (InPosition)
            {
                if (uiSpeachTimer <= diff)
                {
                    ++uiSpeachId;

                    if (me->IsSummon())
                        if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                            if (Player* player = summoner->ToPlayer())
                                switch (uiSpeachId)
                                {
                                    case 1:
                                        uiSpeachTimer = 7000;
                                        if (me->FindNearestCreature(NPC_LORD_DARIUS_CROWLEY_QAOD, 30.0f))
                                            DoScriptText(CROWLEY_SAY_IMMEDIATELY, player);
                                        break;
                                    case 2:
                                        DoScriptText(TOBIAS_SAY_OK, player);
                                        uiSpeachTimer = 3000;
                                        break;
                                    case 3:
                                        SetEscortPaused(false);
                                        break;
                                }
                }
                else
                    uiSpeachTimer -= diff;
            }
        }
    };
};

class npc_lord_darius_crowley_qaod : public CreatureScript
{
public:
    npc_lord_darius_crowley_qaod() : CreatureScript("npc_lord_darius_crowley_qaod") { }

    bool OnQuestComplete(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_AT_OUR_DOORSTEP)
            if (Creature* tobias = player->SummonCreature(NPC_TOBIAS_MISTMANTLE_QAOD, -2079.345f, 1327.531f, -83.0644f))
            {
                tobias->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                tobias->SetSeerGUID(player->GetGUID());
                tobias->SetVisible(false);

                if (npc_escortAI* escort = CAST_AI(npc_escortAI, tobias->AI()))
                {
                    for (int i = 0; i < 4; ++i)
                        escort->AddWaypoint(i, TobiasWP[i][0], TobiasWP[i][1], TobiasWP[i][2]);

                    escort->Start(true);
                }
            }

        if (quest->GetQuestId() == QUEST_NEITHER_HUMAN_NOR_BEAST)
        {
            player->CastSpell(player, 72857, false);

            if (Creature* greymane = player->SummonCreature(NPC_KING_GENN_GREYMANE_HUMAN, -2111.09f, 1286.12f, -83.1804f))
            {
                greymane->SetSeerGUID(player->GetGUID());
                greymane->SetVisible(false);
            }
        }

        return true;
    }
};

///////////
// Quest Betrayal at Tempest's Reach 24592
///////////

enum qBATR
{
    QUEST_BETRAYAL_AT_TEMPESTS_REACH    = 24592,

    NPC_LORD_GODFREY_QBATR              = 37875,
    NPC_KING_GENN_GREYMANE_QBATR        = 37876,

    SPELL_AI_REACTION                   = 61899,
    SPELL_INVISIBILITY_DETECTION_3      = 60922,

    GENN_SAY_ALL_IS_DONE                = -1977091,
    GODFREY_SAY_BETTER_DIED             = -1977092,
};

class npc_krennan_aranas_qbatr : public CreatureScript
{
public:
    npc_krennan_aranas_qbatr() : CreatureScript("npc_krennan_aranas_qbatr") { }

    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_BETRAYAL_AT_TEMPESTS_REACH)
        {
            player->AddAura(SPELL_INVISIBILITY_DETECTION_2, player);
            player->AddAura(SPELL_INVISIBILITY_DETECTION_3, player);
        }

        return true;
    }
};

class npc_lord_godfrey_qbatr : public CreatureScript
{
public:
    npc_lord_godfrey_qbatr() : CreatureScript("npc_lord_godfrey_qbatr") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lord_godfrey_qbatrAI(creature);
    }

    struct npc_lord_godfrey_qbatrAI : public npc_escortAI
    {
        npc_lord_godfrey_qbatrAI(Creature* creature) : npc_escortAI(creature)
        {
            AddWaypoint(0, -2055.98f, 937.692f,  69.9569f, 0);
            AddWaypoint(1, -2080.73f, 889.893f, -43.8015f);
            uiEventTimer = 4000;
            uiPhase = 0;
            Event = false;
            start = false;
        }

        uint32 uiEventTimer;
        uint8 uiPhase;
        bool Event;
        bool start;

        void StartEvent()
        {
            if (!(Event && start))
            {
                Event = true;

                if (Creature* greymane = me->FindNearestCreature(NPC_KING_GENN_GREYMANE_QBATR, 30.0f))
                    DoScriptText(GENN_SAY_ALL_IS_DONE, greymane);
            }
        }

        void WaypointReached(uint32 point)
        {
            if (point == 1)
                start = false;
        }

        void UpdateAI(const uint32 diff)
        {
            if (Event)
            {
                if (uiEventTimer <= diff)
                    switch (uiPhase)
                    {
                        case 0:
                            uiPhase = 1;
                            uiEventTimer = 1500;
                            DoScriptText(GODFREY_SAY_BETTER_DIED, me);
                            break;
                        case 1:
                            uiPhase = 0;
                            start = true;
                            Event = false;
                            uiEventTimer = 4000;
                            Start(false, true, 0, NULL, true);
                            SetSpeedZ(25.0f);
                            break;
                    }
                else
                    uiEventTimer -= diff;
            }

            npc_escortAI::UpdateAI(diff);
        }
    };
};

class npc_king_genn_greymane_qbatr : public CreatureScript
{
public:
    npc_king_genn_greymane_qbatr() : CreatureScript("npc_king_genn_greymane_qbatr") { }

    bool OnQuestComplete(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_BETRAYAL_AT_TEMPESTS_REACH)
        {
            player->AddAura(SPELL_AI_REACTION, player);
            player->RemoveAura(SPELL_INVISIBILITY_DETECTION_2);
            player->RemoveAura(SPELL_INVISIBILITY_DETECTION_3);
            player->SaveToDB();

            if (Creature* godfrey = creature->FindNearestCreature(NPC_LORD_GODFREY_QBATR, 30.0f))
                CAST_AI(npc_lord_godfrey_qbatr::npc_lord_godfrey_qbatrAI, godfrey->AI())->StartEvent();
        }

        return true;
    }
};

///////////
// Quest Liberation Day 24575
///////////

enum qLD
{
    QUEST_LIBERATION_DAY         = 24575,

    NPC_ENSLAVED_VILLAGER_QLD    = 37694,
    VILLAGER_RANDOM_SAY          = -1977093,    // (-1977093 to -1977095)
};

class go_ball_and_chain_qld : public GameObjectScript
{
public:
    go_ball_and_chain_qld() : GameObjectScript("go_ball_and_chain_qld"){}

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_LIBERATION_DAY) == QUEST_STATUS_INCOMPLETE)
        {
            if (Creature* villager = go->FindNearestCreature(NPC_ENSLAVED_VILLAGER_QLD, 5.0f))
            {
                uint8 roll = urand(0, 2);
                DoScriptText(VILLAGER_RANDOM_SAY - roll, villager);
                villager->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                villager->DespawnOrUnsummon(3000);
                player->CastedCreatureOrGO(go->GetEntry(), go->GetGUID(), 0);
            }
        }

        return true;
    }
};

///////////
// Quest The Battle for Gilneas City QUEST_THE_BATTLE_FOR_GILNEAS_CITY
///////////

static float MilSumPos[5][4] =
{
    {-1417.38f,1268.43f,36.4288f,1.79838f},{-1405.55f,1271.08f,36.4288f,1.79838f},{-1407.71f,1270.60f,36.4288f,1.79838f},
    {-1414.01f,1269.18f,36.4288f,1.79838f},{-1410.82f,1269.88f,36.4288f,1.79838f},
};

static float FWaveWP[96][3] =
{
    {-1413.55f,1280.21f,36.4288f},{-1416.87f,1293.56f,36.4288f},{-1420.47f,1308.52f,36.4288f},
    {-1423.92f,1321.51f,34.7850f},{-1428.06f,1337.45f,35.0664f},{-1430.56f,1351.07f,35.5555f},
    {-1432.38f,1359.40f,35.5555f},{-1437.86f,1371.31f,35.5555f},{-1441.41f,1384.88f,35.5555f},
    {-1448.19f,1391.53f,35.5555f},{-1459.86f,1393.28f,35.5555f},{-1473.94f,1393.60f,35.5555f},
    {-1481.17f,1399.55f,35.5555f},{-1487.36f,1404.91f,35.5555f},{-1490.94f,1412.63f,35.5555f},
    {-1496.62f,1419.40f,35.5555f},{-1505.01f,1426.68f,35.5555f},{-1518.00f,1428.23f,35.5555f},
    {-1527.14f,1427.80f,35.5555f},{-1536.65f,1427.62f,35.5555f},{-1542.92f,1420.95f,35.5555f},
    {-1548.23f,1413.49f,35.5555f},{-1550.40f,1402.23f,35.5555f},{-1552.52f,1388.96f,35.5668f},
    {-1553.37f,1378.18f,35.5867f},{-1553.83f,1368.68f,35.6061f},{-1556.94f,1358.32f,35.5574f},
    {-1557.53f,1350.16f,35.5574f},{-1559.71f,1341.59f,35.5574f},{-1562.41f,1331.79f,35.5574f},
    {-1565.47f,1323.50f,35.5574f},{-1574.10f,1317.31f,35.5561f},{-1581.09f,1316.72f,32.4373f},
    {-1589.80f,1315.95f,26.8717f},{-1601.94f,1314.38f,19.2131f},{-1612.36f,1313.10f,18.4492f},
    {-1626.31f,1309.77f,20.3373f},{-1634.95f,1306.97f,19.6632f},{-1645.84f,1304.63f,19.7690f},
    {-1657.72f,1304.68f,19.7826f},{-1666.91f,1306.79f,19.7826f},{-1673.02f,1309.37f,19.7826f},
    {-1682.11f,1309.02f,19.7826f},{-1692.83f,1307.45f,19.7826f},{-1702.07f,1308.50f,19.7826f},
    {-1710.78f,1310.87f,19.7826f},{-1720.07f,1313.75f,19.7826f},{-1729.48f,1316.44f,19.7826f},
    {-1738.53f,1319.14f,19.7827f},{-1744.64f,1325.33f,19.7910f},{-1743.33f,1332.14f,19.7600f},
    {-1739.08f,1339.84f,19.7900f},{-1735.41f,1346.33f,19.8821f},{-1737.87f,1355.13f,19.7836f},
    {-1742.57f,1366.28f,19.7368f},{-1742.55f,1378.77f,19.7637f},{-1738.08f,1383.00f,19.8238f},
    {-1731.88f,1389.21f,20.2902f},{-1725.81f,1395.97f,21.6685f},{-1708.44f,1393.12f,21.6687f},
    {-1725.65f,1396.38f,21.6688f},{-1731.76f,1389.38f,20.3340f},{-1739.26f,1381.20f,19.9172f},
    {-1748.73f,1378.62f,19.8574f},{-1755.88f,1386.24f,19.8921f},{-1762.23f,1389.28f,19.8999f},
    {-1771.95f,1385.38f,19.6324f},{-1783.07f,1381.10f,19.6560f},{-1789.69f,1378.86f,19.7935f},
    {-1793.91f,1388.03f,19.8703f},{-1797.87f,1396.60f,19.9024f},{-1802.12f,1406.22f,19.8385f},
    {-1803.79f,1416.60f,19.9540f},{-1803.84f,1428.15f,19.7620f},{-1803.67f,1436.52f,19.5282f},
    {-1803.33f,1450.17f,18.9785f},{-1804.19f,1463.43f,18.9459f},{-1805.42f,1475.28f,19.3649f},
    {-1804.10f,1489.54f,19.6081f},{-1802.48f,1506.96f,19.7809f},{-1801.51f,1517.42f,19.7809f},
    {-1800.07f,1533.10f,20.3703f},{-1798.80f,1546.33f,22.6018f},{-1796.41f,1566.48f,20.6045f},
    {-1791.83f,1578.21f,20.5046f},{-1785.51f,1590.68f,20.5046f},{-1778.93f,1601.81f,20.4943f},
    {-1770.99f,1613.75f,20.4806f},{-1763.55f,1624.02f,20.4549f},{-1756.86f,1632.89f,20.4574f},
    {-1749.70f,1642.31f,20.4742f},{-1741.83f,1650.73f,20.4769f},{-1729.43f,1649.46f,20.5003f},
    {-1718.56f,1643.08f,20.4859f},{-1709.44f,1635.46f,20.4868f},{-1703.89f,1621.66f,20.488f},
};

static float SWaveWP[96][3] =
{
    {-1414.28f,1281.94f,36.4280f},{-1416.92f,1294.20f,36.4280f},{-1419.48f,1305.69f,36.4280f},
    {-1423.35f,1320.92f,34.9943f},{-1428.30f,1340.61f,35.2325f},{-1431.12f,1352.39f,35.5555f},
    {-1428.25f,1363.49f,35.5555f},{-1415.41f,1367.46f,35.5555f},{-1404.02f,1368.76f,35.5555f},
    {-1402.89f,1381.81f,35.5555f},{-1403.01f,1395.25f,35.5555f},{-1403.17f,1410.33f,35.5555f},
    {-1403.29f,1419.51f,35.5555f},{-1415.19f,1420.97f,35.5555f},{-1425.01f,1420.85f,35.5555f},
    {-1440.90f,1415.44f,35.5555f},{-1449.79f,1417.30f,35.5555f},{-1460.94f,1422.83f,35.5555f},
    {-1471.50f,1421.22f,35.5561f},{-1483.56f,1416.41f,35.5561f},{-1491.02f,1408.94f,35.5526f},
    {-1497.86f,1401.01f,35.5544f},{-1503.09f,1390.99f,35.5544f},{-1503.35f,1380.46f,35.5559f},
    {-1503.22f,1366.37f,35.5559f},{-1503.67f,1353.95f,35.5559f},{-1502.12f,1343.28f,35.5559f},
    {-1514.94f,1339.25f,35.5559f},{-1527.78f,1335.34f,35.5559f},{-1541.24f,1331.24f,35.5559f},
    {-1553.27f,1327.01f,35.5559f},{-1575.15f,1317.28f,35.6661f},{-1592.38f,1315.01f,25.1970f},
    {-1603.89f,1313.98f,18.2722f},{-1618.07f,1311.27f,19.5098f},{-1630.88f,1307.71f,19.6631f},
    {-1635.25f,1316.63f,19.7302f},{-1633.90f,1330.20f,20.0334f},{-1634.21f,1342.10f,20.0680f},
    {-1634.19f,1354.70f,20.0336f},{-1633.62f,1367.65f,20.0763f},{-1633.01f,1380.93f,19.9831f},
    {-1635.32f,1391.15f,20.0172f},{-1640.15f,1398.41f,19.9265f},{-1648.97f,1394.12f,19.7717f},
    {-1658.94f,1384.64f,15.1348f},{-1664.69f,1379.02f,15.1348f},{-1666.38f,1367.59f,15.1348f},
    {-1679.83f,1357.66f,15.1350f},{-1685.89f,1348.24f,15.0921f},{-1693.74f,1345.67f,15.1352f},
    {-1705.31f,1347.81f,19.8963f},{-1720.84f,1349.75f,19.7692f},{-1732.15f,1357.35f,19.7361f},
    {-1747.93f,1371.39f,20.0557f},{-1742.55f,1378.77f,19.7637f},{-1738.08f,1383.00f,19.8238f},
    {-1731.88f,1389.21f,20.2902f},{-1725.81f,1395.97f,21.6685f},{-1728.80f,1415.51f,21.6690f},
    {-1721.26f,1399.50f,21.6688f},{-1728.82f,1392.81f,21.2507f},{-1736.99f,1385.54f,19.8094f},
    {-1745.34f,1383.50f,19.4523f},{-1754.56f,1384.33f,19.8305f},{-1759.61f,1393.94f,19.4199f},
    {-1765.72f,1405.63f,19.7639f},{-1770.79f,1417.34f,19.7827f},{-1770.45f,1427.12f,19.8364f},
    {-1769.89f,1438.66f,19.9248f},{-1769.39f,1446.68f,19.9417f},{-1777.06f,1452.54f,19.3633f},
    {-1786.10f,1453.36f,19.3591f},{-1796.93f,1453.80f,19.2225f},{-1802.89f,1454.04f,18.9536f},
    {-1804.83f,1461.50f,18.8724f},{-1805.31f,1472.68f,19.3047f},{-1806.14f,1482.08f,19.4244f},
    {-1807.22f,1492.52f,19.6339f},{-1804.81f,1503.11f,19.7793f},{-1801.64f,1514.61f,19.7814f},
    {-1799.94f,1527.42f,20.1764f},{-1800.05f,1535.51f,20.4954f},{-1798.68f,1550.11f,22.7365f},
    {-1796.03f,1568.14f,20.4859f},{-1793.33f,1575.31f,20.5061f},{-1787.77f,1588.54f,20.5061f},
    {-1783.55f,1598.15f,20.4917f},{-1773.91f,1612.26f,20.4835f},{-1767.50f,1620.57f,20.4691f},
    {-1754.33f,1636.88f,20.4678f},{-1746.97f,1644.35f,20.4766f},{-1732.60f,1651.56f,20.4996f},
    {-1723.52f,1646.36f,20.4860f},{-1714.70f,1640.66f,20.4860f},{-1701.76f,1629.37f,20.4883f},
};

static float TWaveWP[87][3] =
{
    {-1412.03f,1273.98f,36.4282f},{-1414.81f,1285.10f,36.4282f},{-1418.16f,1299.11f,36.4282f},
    {-1421.74f,1313.09f,36.4282f},{-1424.13f,1321.95f,34.7826f},{-1428.55f,1339.75f,35.1950f},
    {-1433.06f,1356.87f,35.5555f},{-1443.26f,1362.80f,35.5555f},{-1457.30f,1356.49f,35.5555f},
    {-1467.95f,1351.41f,35.5555f},{-1479.48f,1348.99f,35.5555f},{-1489.47f,1345.82f,35.5555f},
    {-1502.09f,1342.30f,35.5563f},{-1514.73f,1338.77f,35.5563f},{-1524.50f,1336.05f,35.5563f},
    {-1536.50f,1332.70f,35.5563f},{-1549.44f,1329.09f,35.5563f},{-1566.80f,1322.35f,35.5563f},
    {-1575.15f,1317.28f,35.6661f},{-1592.38f,1315.01f,25.1970f},{-1603.89f,1313.98f,18.2722f},
    {-1618.07f,1311.27f,19.5098f},{-1630.88f,1307.71f,19.6631f},{-1635.25f,1316.63f,19.7302f},
    {-1633.90f,1330.20f,20.0334f},{-1634.21f,1342.10f,20.0680f},{-1634.19f,1354.70f,20.0336f},
    {-1633.62f,1367.65f,20.0763f},{-1633.01f,1380.93f,19.9831f},{-1635.32f,1391.15f,20.0172f},
    {-1640.15f,1398.41f,19.9265f},{-1648.97f,1394.12f,19.7717f},{-1658.94f,1384.64f,15.1348f},
    {-1664.69f,1379.02f,15.1348f},{-1666.38f,1367.59f,15.1348f},{-1679.83f,1357.66f,15.1350f},
    {-1685.89f,1348.24f,15.0921f},{-1693.74f,1345.67f,15.1352f},{-1705.31f,1347.81f,19.8963f},
    {-1720.84f,1349.75f,19.7692f},{-1732.15f,1357.35f,19.7361f},{-1747.93f,1371.39f,20.0557f},
    {-1742.55f,1378.77f,19.7637f},{-1738.08f,1383.00f,19.8238f},{-1731.88f,1389.21f,20.2902f},
    {-1725.81f,1395.97f,21.6685f},{-1702.28f,1418.09f,21.6690f},{-1721.26f,1399.50f,21.6688f},
    {-1728.82f,1392.81f,21.2507f},{-1736.99f,1385.54f,19.8094f},{-1745.34f,1383.50f,19.4523f},
    {-1754.56f,1384.33f,19.8305f},{-1759.61f,1393.94f,19.4199f},{-1765.72f,1405.63f,19.7639f},
    {-1770.79f,1417.34f,19.7827f},{-1770.45f,1427.12f,19.8364f},{-1769.89f,1438.66f,19.9248f},
    {-1769.39f,1446.68f,19.9417f},{-1764.81f,1453.63f,20.2949f},{-1761.72f,1458.27f,20.4706f},
    {-1761.05f,1464.88f,20.9578f},{-1759.51f,1472.06f,22.2850f},{-1761.05f,1479.98f,23.8829f},
    {-1761.02f,1487.69f,25.4303f},{-1760.98f,1496.08f,26.2232f},{-1761.44f,1506.22f,26.2232f},
    {-1761.94f,1510.83f,26.2229f},{-1768.24f,1510.83f,26.4891f},{-1784.71f,1510.93f,19.8397f},
    {-1794.80f,1511.92f,19.7824f},{-1800.90f,1514.54f,19.7824f},{-1800.16f,1526.06f,19.9329f},
    {-1799.62f,1535.14f,20.4793f},{-1798.86f,1546.31f,22.5989f},{-1796.76f,1564.72f,21.1471f},
    {-1793.73f,1574.39f,20.5042f},{-1788.02f,1587.81f,20.5056f},{-1781.75f,1601.10f,20.4851f},
    {-1773.87f,1612.23f,20.4828f},{-1764.28f,1625.17f,20.3991f},{-1755.13f,1635.73f,20.4639f},
    {-1746.64f,1645.04f,20.4758f},{-1734.06f,1651.90f,20.4941f},{-1724.22f,1646.66f,20.4858f},
    {-1715.14f,1640.71f,20.4858f},{-1701.02f,1635.61f,20.4884f},{-1692.68f,1633.03f,20.4884f},
};

static float LornaWP[78][3] =
{
    {-1551.90f,1284.75f,13.992f}, {-1561.35f,1282.32f,21.372f}, {-1581.19f,1277.05f,35.878f},
    {-1587.59f,1275.81f,35.880f}, {-1591.07f,1284.64f,35.878f}, {-1591.32f,1291.64f,35.981f},
    {-1579.00f,1296.02f,35.879f}, {-1569.90f,1303.33f,35.879f}, {-1568.92f,1315.40f,35.556f},
    {-1565.98f,1319.25f,35.556f}, {-1572.58f,1318.18f,35.556f}, {-1574.10f,1317.31f,35.556f},
    {-1581.09f,1316.72f,32.437f}, {-1589.80f,1315.95f,26.871f}, {-1601.94f,1314.38f,19.213f},
    {-1612.36f,1313.10f,18.449f}, {-1626.31f,1309.77f,20.337f}, {-1634.95f,1306.97f,19.663f},
    {-1645.84f,1304.63f,19.769f}, {-1657.72f,1304.68f,19.782f}, {-1666.91f,1306.79f,19.782f},
    {-1673.02f,1309.37f,19.782f}, {-1682.11f,1309.02f,19.782f}, {-1692.83f,1307.45f,19.782f},
    {-1702.07f,1308.50f,19.782f}, {-1710.78f,1310.87f,19.782f}, {-1720.07f,1313.75f,19.782f},
    {-1729.48f,1316.44f,19.782f}, {-1738.53f,1319.14f,19.782f}, {-1744.64f,1325.33f,19.791f},
    {-1743.33f,1332.14f,19.760f}, {-1739.08f,1339.84f,19.790f}, {-1735.41f,1346.33f,19.882f},
    {-1737.87f,1355.13f,19.783f}, {-1742.57f,1366.28f,19.736f}, {-1742.55f,1378.77f,19.763f},
    {-1738.08f,1383.00f,19.823f}, {-1731.88f,1389.21f,20.290f}, {-1725.81f,1395.97f,21.668f},
    {-1731.88f,1389.21f,20.290f}, {-1725.81f,1395.97f,21.668f}, {-1708.44f,1393.12f,21.668f},
    {-1725.65f,1396.38f,21.668f}, {-1731.76f,1389.38f,20.334f}, {-1739.26f,1381.20f,19.917f},
    {-1748.73f,1378.62f,19.857f}, {-1755.88f,1386.24f,19.892f}, {-1762.23f,1389.28f,19.899f},
    {-1771.95f,1385.38f,19.632f}, {-1783.07f,1381.10f,19.656f}, {-1789.69f,1378.86f,19.793f},
    {-1793.91f,1388.03f,19.870f}, {-1797.87f,1396.60f,19.902f}, {-1802.12f,1406.22f,19.838f},
    {-1803.79f,1416.60f,19.954f}, {-1803.84f,1428.15f,19.762f}, {-1803.67f,1436.52f,19.528f},
    {-1803.33f,1450.17f,18.978f}, {-1804.19f,1463.43f,18.945f}, {-1805.42f,1475.28f,19.364f},
    {-1804.10f,1489.54f,19.608f}, {-1802.48f,1506.96f,19.780f}, {-1801.51f,1517.42f,19.780f},
    {-1800.07f,1533.10f,20.370f}, {-1798.80f,1546.33f,22.601f}, {-1796.41f,1566.48f,20.604f},
    {-1791.83f,1578.21f,20.504f}, {-1785.51f,1590.68f,20.504f}, {-1778.93f,1601.81f,20.494f},
    {-1770.99f,1613.75f,20.480f}, {-1763.55f,1624.02f,20.454f}, {-1756.86f,1632.89f,20.457f},
    {-1749.70f,1642.31f,20.474f}, {-1741.83f,1650.73f,20.476f}, {-1729.43f,1649.46f,20.500f},
    {-1718.56f,1643.08f,20.485f}, {-1709.44f,1635.46f,20.486f}, {-1703.89f,1621.66f,20.488f},
};

static float FDarkRangerWP[31][3] =
{
    {-1572.91f,1319.44f,35.556f}, {-1546.53f,1328.34f,35.556f}, {-1531.53f,1333.13f,35.556f},
    {-1518.78f,1335.67f,35.556f}, {-1507.45f,1338.38f,35.556f}, {-1503.32f,1347.66f,35.556f},
    {-1503.03f,1358.11f,35.556f}, {-1503.48f,1374.93f,35.556f}, {-1503.04f,1391.36f,35.556f},
    {-1491.28f,1393.23f,35.556f}, {-1477.47f,1393.06f,35.556f}, {-1463.66f,1393.34f,35.556f},
    {-1445.90f,1394.58f,35.556f}, {-1440.95f,1407.66f,35.556f}, {-1441.15f,1413.96f,35.556f},
    {-1445.75f,1421.83f,35.556f}, {-1455.19f,1427.97f,35.556f}, {-1463.82f,1429.19f,35.556f},
    {-1472.95f,1423.35f,35.556f}, {-1484.01f,1414.69f,35.556f}, {-1494.87f,1406.82f,35.556f},
    {-1500.12f,1394.48f,35.556f}, {-1502.17f,1383.12f,35.556f}, {-1502.36f,1367.71f,35.556f},
    {-1502.69f,1350.91f,35.556f}, {-1509.18f,1344.53f,35.556f}, {-1517.96f,1338.98f,35.556f},
    {-1529.58f,1336.49f,35.556f}, {-1543.75f,1332.65f,35.556f}, {-1559.08f,1328.04f,35.556f},
    {-1565.85f,1321.06f,35.556f},
};

static float SDarkRangerWP[31][3] =
{
    {-1570.32f,1318.69f,35.556f}, {-1561.46f,1322.08f,35.556f}, {-1558.38f,1334.64f,35.556f},
    {-1556.23f,1352.71f,35.556f}, {-1554.95f,1368.66f,35.656f}, {-1554.41f,1380.55f,35.596f},
    {-1555.58f,1388.50f,35.621f}, {-1548.59f,1401.41f,35.557f}, {-1548.38f,1409.81f,35.557f},
    {-1548.21f,1420.64f,35.557f}, {-1539.33f,1425.07f,35.557f}, {-1527.78f,1425.25f,35.557f},
    {-1515.68f,1420.99f,35.557f}, {-1505.62f,1411.56f,35.556f}, {-1493.82f,1400.40f,35.556f},
    {-1486.97f,1394.43f,35.556f}, {-1473.41f,1390.72f,35.555f}, {-1461.84f,1390.88f,35.555f},
    {-1449.61f,1390.36f,35.555f}, {-1442.35f,1385.61f,35.555f}, {-1438.42f,1371.34f,35.555f},
    {-1444.42f,1363.58f,35.555f}, {-1456.25f,1358.35f,35.555f}, {-1469.77f,1351.00f,35.555f},
    {-1485.67f,1346.50f,35.555f}, {-1499.77f,1342.79f,35.556f}, {-1516.27f,1338.11f,35.556f},
    {-1532.80f,1333.51f,35.556f}, {-1548.94f,1328.85f,35.556f}, {-1568.00f,1322.04f,35.556f},
};

static float SummonCannonPos[3][4] =
{
    {-1542.55f,1290.96f,6.23982f,3.49002f},{-1541.04f,1283.65f,6.35803f,3.34331f},{-1543.06f,1287.44f,7.07661f,3.44634f},
};

static float CannonWP[11][3] =
{
    {-1551.90f,1284.75f,13.992f}, {-1561.35f,1282.32f,21.372f}, {-1581.19f,1277.05f,35.878f},
    {-1587.59f,1275.81f,35.880f}, {-1591.07f,1284.64f,35.878f}, {-1591.32f,1291.64f,35.981f},
    {-1579.00f,1296.02f,35.879f}, {-1569.90f,1303.33f,35.879f}, {-1568.92f,1315.40f,35.556f},
    {-1565.98f,1319.25f,35.556f}, {-1572.58f,1318.18f,35.556f},
};

static float WorgenSummPos[12][3] =
{
    {-1805.18f,1313.98f,19.9797f},{-1802.93f,1311.73f,19.9736f},{-1799.92f,1310.26f,19.9844f},
    {-1799.59f,1317.28f,19.9762f},{-1795.82f,1313.91f,19.9859f},{-1799.38f,1321.75f,19.9737f},
    {-1794.08f,1320.83f,19.8059f},{-1791.56f,1317.74f,19.7885f},{-1796.55f,1308.39f,19.9725f},
    {-1799.02f,1314.42f,19.9754f},{-1803.21f,1317.87f,19.9814f},{-1795.42f,1317.05f,19.9774f},
};

static float FWorgenWP[46][3] =
{
    {-1787.53f,1325.74f,19.8783f},{-1779.44f,1333.76f,19.9688f},{-1770.88f,1341.79f,19.7133f},
    {-1764.44f,1348.68f,19.4973f},{-1753.58f,1355.86f,19.7710f},{-1746.08f,1365.29f,19.7652f},
    {-1742.12f,1376.55f,19.9143f},{-1735.84f,1383.94f,19.8177f},{-1727.33f,1393.39f,21.5739f},
    {-1713.13f,1406.73f,21.6684f},{-1721.26f,1399.50f,21.6688f},{-1728.82f,1392.81f,21.2507f},
    {-1736.99f,1385.54f,19.8094f},{-1745.34f,1383.50f,19.4523f},{-1754.56f,1384.33f,19.8305f},
    {-1759.61f,1393.94f,19.4199f},{-1765.72f,1405.63f,19.7639f},{-1770.79f,1417.34f,19.7827f},
    {-1770.45f,1427.12f,19.8364f},{-1769.89f,1438.66f,19.9248f},{-1769.39f,1446.68f,19.9417f},
    {-1777.06f,1452.54f,19.3633f},{-1786.10f,1453.36f,19.3591f},{-1796.93f,1453.80f,19.2225f},
    {-1802.89f,1454.04f,18.9536f},{-1804.83f,1461.50f,18.8724f},{-1805.31f,1472.68f,19.3047f},
    {-1806.14f,1482.08f,19.4244f},{-1807.22f,1492.52f,19.6339f},{-1804.81f,1503.11f,19.7793f},
    {-1801.64f,1514.61f,19.7814f},{-1799.94f,1527.42f,20.1764f},{-1800.05f,1535.51f,20.4954f},
    {-1798.68f,1550.11f,22.7365f},{-1796.03f,1568.14f,20.4859f},{-1793.33f,1575.31f,20.5061f},
    {-1787.77f,1588.54f,20.5061f},{-1783.55f,1598.15f,20.4917f},{-1773.91f,1612.26f,20.4835f},
    {-1767.50f,1620.57f,20.4691f},{-1754.33f,1636.88f,20.4678f},{-1746.97f,1644.35f,20.4766f},
    {-1732.60f,1651.56f,20.4996f},{-1723.52f,1646.36f,20.4860f},{-1714.70f,1640.66f,20.4860f},
    {-1701.76f,1629.37f,20.4883f},
};

static float GreymaneWP[12][3] =
{
    {-1797.62f,1709.17f,22.1583f},{-1786.33f,1700.06f,22.1583f},{-1774.75f,1690.42f,22.1583f},
    {-1763.11f,1680.88f,22.1583f},{-1751.00f,1670.80f,22.1583f},{-1743.49f,1664.47f,20.4806f},
    {-1734.04f,1656.68f,20.4838f},{-1724.69f,1648.78f,20.4952f},{-1713.05f,1639.43f,20.4859f},
    {-1704.06f,1632.17f,20.4883f},{-1691.19f,1626.66f,20.4883f},{-1680.21f,1629.98f,20.4883f},
};

enum qTBFGC
{
    QUEST_THE_BATTLE_FOR_GILNEAS_CITY     = 24904,

    NPC_PRINCE_LIAM_GREYMANE              = 38218,
    NPC_MYRIAM_SPELLWAKER                 = 38465,
    NPC_SISTER_ALMYRA                     = 38466,
    NPC_GILNEAN_MILITIA                   = 38221,
    NPC_DARK_RANGER_ELITE                 = 38464,
    NPC_LORNA_CROWLEY_TBFGC               = 38426,
    NPC_FREED_EMBERSTONE_VILLAGER         = 38425,
    NPC_EMBERSTONE_CANNON                 = 38424,
    NPC_WORGEN_WARRIOR                    = 38348,
    NPC_LORD_DARIUS_CROWLEY_TBFGC         = 38415,
    NPC_GOREROT                           = 38331,
    NPC_KING_GENN_GREYMANE_TBFGC          = 38470,
    NPC_LADY_SYLVANAS_WINDRUNNER_TBFGC    = 38469,
    NPC_SOULTETHERED_BANSHEE              = 38473,
    NPC_KRENNAN_ARANAS_TBFGC              = 38553,

    SPELL_SOLDIER_OF_TBFGC                = 72069,
    SPELL_CHALLENGING_SHOUT               = 1161,
    SPELL_MULTI_SHOT                      = 31942,
    SPELL_SHOOT_TBFGC                     = 6660,
    SPELL_IMPROVED_WING_CLIP              = 47168,
    SPELL_SUNDER_ARMOR                    = 15572,
    SPELL_FLASH_HEAL                      = 17843,
    SPELL_HOLY_NOVA                       = 85965,
    SPELL_ARCANE_INTELLECT                = 13326,
    SPELL_BLIZZARD                        = 33418,
    SPELL_FIRE_BLAST                      = 20795,
    SPELL_FROSTBOLT                       = 20792,
    SPELL_KNOCKBACK                       = 68683,
    SPELL_THUNDERCLAP                     = 8078,
    SPELL_SMASH                           = 71774,
    SPELL_GOREROT_THREAT                  = 72135,
    SPELL_SLICE_AND_DICE                  = 6434,
    SPELL_TAUNT                           = 37548,
    SPELL_FERAL_LEAP                      = 71921,
    SPELL_INTERCEPT                       = 58769,
    SPELL_GREYMANE_TRANSFORM              = 86141,
    SPELL_GREYMANE_JUMP                   = 72107,
    SPELL_BANSHEE_QUEENS_WAIL             = 72113,
    SPELL_SHOOT_LIAM                      = 61, // 72116 кривой визуальный эффект
    SPELL_BFGC_COMPLETE                   = 72349,

    LIAM_BATTLE_SPEACH_1                  = -1977096,
    LIAM_BATTLE_SPEACH_2                  = -1977097,
    LIAM_BATTLE_SPEACH_3                  = -1977098,
    LIAM_BATTLE_SPEACH_4                  = -1977099,
    LIAM_BATTLE_SPEACH_5                  = -1977100,
    LIAM_BATTLE_SPEACH_6                  = -1977101,
    LIAM_BATTLE_FOR_GILNEAS               = -1977102,
    LIAM_RANDOM_BATTLE_SPEACH             = -1977103,    // -1977103 to -1977106
    LIAM_BATTLE_BATTLE_1                  = -1977107,
    LIAM_BATTLE_BATTLE_2                  = -1977108,
    LIAM_BATTLE_BATTLE_3                  = -1977109,
    LIAM_BATTLE_DEATH_1                   = -1977110,
    LIAM_BATTLE_DEATH_2                   = -1977111,
    LIAM_BATTLE_DEATH_3                   = -1977112,
    LORNA_BATTLE_BATTLE_1                 = -1977113,
    LORNA_BATTLE_BATTLE_2                 = -1977114,
    GOREROT_YELL_CRUSH                    = -1977115,
    CROWLEY_BATTLE_BATTLE_1               = -1977116,
    CROWLEY_BATTLE_BATTLE_2               = -1977117,
    GREYMANE_BATTLE_BATTLE_1              = -1977118,
    GREYMANE_BATTLE_BATTLE_2              = -1977119,
    GREYMANE_YELL_LIAM                    = -1977120,
    SYLVANAS_YELL_ENOUGH                  = -1977121,
    SYLVANAS_KILL_LIAM                    = -1977122,

    PHASE_NONE                            = 0,
    PHASE_INTRO                           = 1,
    PHASE_MERCHANT_SQUARE                 = 2,
    PHASE_MILITARY_DISTRICT               = 3,
    PHASE_GREYMANE_COURT                  = 4,

    DATA_WP_PAUSE                         = 5,
    DATA_CURRENT_PHASE                    = 6,

    ACTION_CANNON_AT_POSITION             = 7,
    ACTION_GOREROT_FIGHT                  = 8,
    ACTION_GOREROT_DIED                   = 9,
    ACTION_ATTACK_SYLVANAS                = 10,
    ACTION_FINISH_TBFGC                   = 11,
    ACTION_BATTLE_COMPLETE                = 12,
    ACTION_CAN_ATTACK                     = 13,

    MENU_START_BATTLE                     = 50710,
};


class npc_prince_liam_greymane_tbfgc : public CreatureScript
{
public:
    npc_prince_liam_greymane_tbfgc() : CreatureScript("npc_prince_liam_greymane_tbfgc") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_prince_liam_greymane_tbfgcAI(creature);
    }

    struct npc_prince_liam_greymane_tbfgcAI : public npc_escortAI
    {
        npc_prince_liam_greymane_tbfgcAI(Creature* creature) : npc_escortAI(creature)
        {
            me->SetPhaseMask(262144, true);
            FirstWave.clear();
            SecondWave.clear();
            ThirdWave.clear();
            CannonList.clear();
            WorgenList.clear();
            GreymaneMilitia.clear();
            creature->setActive(true);
            SetCombatMovement(false);
            SetDespawnAtEnd(false);
            SetDespawnAtFar(false);
            uiMyriamGUID = 0;
            uiAlmyraGUID = 0;
            uiLornaGUID = 0;
            uiCrowleyGUID = 0;
            uiGreymaneGUID = 0;
            uiSylvanasGUID = 0;
            uiEventTimer = 0;
            uiDeadBossCount = 2;
            uiShootTimer = 1500;
            uiMultiShotTimer = 3000;
            uiChallengingShoutTimer = urand(10000, 30000);
            uiRandomSpechTimer = urand(10000, 30000);
            uiFailTimer = 900000;
            uiSubPhase = 0;
            Event = false;
            EscortFinished = false;
            Finish = false;
            Aura = true;
            Fail = false;
            uiBattlePhase = PHASE_NONE;
            DoCast(SPELL_SOLDIER_OF_TBFGC);
            SummonEventCreatures();
            me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_BANSHEE_QUEENS_WAIL, true);
        }

        std::list<uint64> FirstWave;
        std::list<uint64> SecondWave;
        std::list<uint64> ThirdWave;
        std::list<uint64> CannonList;
        std::list<uint64> WorgenList;
        std::list<uint64> GreymaneMilitia;
        uint64 uiMyriamGUID;
        uint64 uiAlmyraGUID;
        uint64 uiLornaGUID;
        uint64 uiCrowleyGUID;
        uint64 uiGreymaneGUID;
        uint64 uiSylvanasGUID;
        uint32 uiEventTimer;
        uint32 uiShootTimer;
        uint32 uiMultiShotTimer;
        uint32 uiChallengingShoutTimer;
        uint32 uiRandomSpechTimer;
        uint32 uiFailTimer;
        uint8 uiSubPhase;
        uint8 uiBattlePhase;
        uint8 uiDeadBossCount;
        bool Event;
        bool EscortFinished;
        bool Finish;
        bool Aura;
        bool Fail;

        void SetFacingToLiam()
        {
            if (Creature* myriam = Unit::GetCreature(*me, uiMyriamGUID))
                myriam->SetFacingToObject(me);

            if (Creature* almyra = Unit::GetCreature(*me, uiAlmyraGUID))
                almyra->SetFacingToObject(me);

            if (Creature* lorna = Unit::GetCreature(*me, uiLornaGUID))
                lorna->SetFacingToObject(me);

            if (Creature* crowley = Unit::GetCreature(*me, uiCrowleyGUID))
                crowley->SetFacingToObject(me);

            if (Creature* greymane = Unit::GetCreature(*me, uiGreymaneGUID))
                greymane->SetFacingToObject(me);

            if (!FirstWave.empty())
            {
                for (std::list<uint64>::const_iterator itr = FirstWave.begin(); itr != FirstWave.end(); )
                {
                    Creature* militia = Unit::GetCreature(*me, *itr);
                    ++itr;

                    if (militia)
                        militia->SetFacingToObject(me);
                }
            }

            if (!SecondWave.empty())
            {
                for (std::list<uint64>::const_iterator itr = SecondWave.begin(); itr != SecondWave.end(); )
                {
                    Creature* militia = Unit::GetCreature(*me, *itr);
                    ++itr;

                    if (militia)
                        militia->SetFacingToObject(me);
                }
            }

            if (!ThirdWave.empty())
            {
                for (std::list<uint64>::const_iterator itr = ThirdWave.begin(); itr != ThirdWave.end(); )
                {
                    Creature* militia = Unit::GetCreature(*me, *itr);
                    ++itr;

                    if (militia)
                        militia->SetFacingToObject(me);
                }
            }

            if (!WorgenList.empty())
            {
                for (std::list<uint64>::const_iterator itr = WorgenList.begin(); itr != WorgenList.end(); )
                {
                    Creature* worgen = Unit::GetCreature(*me, *itr);
                    ++itr;

                    if (worgen)
                        worgen->SetFacingToObject(me);
                }
            }

            if (!GreymaneMilitia.empty())
            {
                for (std::list<uint64>::const_iterator itr = GreymaneMilitia.begin(); itr != GreymaneMilitia.end(); )
                {
                    Creature* militia = Unit::GetCreature(*me, *itr);
                    ++itr;

                    if (militia)
                        militia->SetFacingToObject(me);
                }
            }
        }

        void SpellHit(Unit* /*caster*/, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_SHOOT_LIAM)
            {
                me->AddUnitState(UNIT_STATE_ROOT);
                me->AddUnitMovementFlag(MOVEMENTFLAG_ROOT);
                me->CombatStop();
                me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
            }
        }

        void DespawnEvent(uint32 time)
        {
            if (Creature* myriam = Unit::GetCreature(*me, uiMyriamGUID))
                myriam->DespawnOrUnsummon(time);

            if (Creature* almyra = Unit::GetCreature(*me, uiAlmyraGUID))
                almyra->DespawnOrUnsummon(time);

            if (Creature* lorna = Unit::GetCreature(*me, uiLornaGUID))
                lorna->DespawnOrUnsummon(time);

            if (Creature* crowley = Unit::GetCreature(*me, uiCrowleyGUID))
                crowley->DespawnOrUnsummon(time);

            if (Creature* greymane = Unit::GetCreature(*me, uiGreymaneGUID))
                greymane->DespawnOrUnsummon(time);

            if (!FirstWave.empty())
            {
                for (std::list<uint64>::const_iterator itr = FirstWave.begin(); itr != FirstWave.end(); )
                {
                    Creature* militia = Unit::GetCreature(*me, *itr);
                    ++itr;

                    if (militia)
                        militia->DespawnOrUnsummon(time);
                }
            }

            if (!SecondWave.empty())
            {
                for (std::list<uint64>::const_iterator itr = SecondWave.begin(); itr != SecondWave.end(); )
                {
                    Creature* militia = Unit::GetCreature(*me, *itr);
                    ++itr;

                    if (militia)
                        militia->DespawnOrUnsummon(time);
                }
            }

            if (!ThirdWave.empty())
            {
                for (std::list<uint64>::const_iterator itr = ThirdWave.begin(); itr != ThirdWave.end(); )
                {
                    Creature* militia = Unit::GetCreature(*me, *itr);
                    ++itr;

                    if (militia)
                        militia->DespawnOrUnsummon(time);
                }
            }

            if (!WorgenList.empty())
            {
                for (std::list<uint64>::const_iterator itr = WorgenList.begin(); itr != WorgenList.end(); )
                {
                    Creature* worgen = Unit::GetCreature(*me, *itr);
                    ++itr;

                    if (worgen)
                        worgen->DespawnOrUnsummon(time);
                }
            }

            if (!GreymaneMilitia.empty())
            {
                for (std::list<uint64>::const_iterator itr = GreymaneMilitia.begin(); itr != GreymaneMilitia.end(); )
                {
                    Creature* militia = Unit::GetCreature(*me, *itr);
                    ++itr;

                    if (militia)
                        militia->DespawnOrUnsummon(time);
                }
            }

            me->DespawnOrUnsummon(time);
        }

        void SummonKingCreaymane()
        {
            if (Creature* sylvanas = me->SummonCreature(NPC_LADY_SYLVANAS_WINDRUNNER_TBFGC, -1684.79f,1616.47f,20.4894f,2.50855f))
                uiSylvanasGUID = sylvanas->GetGUID();

            if (Creature* greymane = me->SummonCreature(NPC_KING_GENN_GREYMANE_TBFGC, -1797.62f, 1709.17f, 22.1583f))
            {
                uiGreymaneGUID = greymane->GetGUID();

                if (npc_escortAI* escort = CAST_AI(npc_escortAI, greymane->AI()))
                {
                    for (int j = 0; j < 12; ++j)
                        escort->AddWaypoint(j, GreymaneWP[j][0], GreymaneWP[j][1], GreymaneWP[j][2]);

                    escort->Start(true, true);
                }
            }

            for (int i = 0; i < 15; ++i)
                if (Creature* militia = me->SummonCreature(NPC_GILNEAN_MILITIA, -1797.62f, 1709.17f, 22.1583f))
                {
                    GreymaneMilitia.push_back(militia->GetGUID());

                    if (npc_escortAI* escort = CAST_AI(npc_escortAI, militia->AI()))
                    {
                        int roll_x = irand(-3, 3);
                        int roll_y = irand(-3, 3);

                        for (int j = 0; j < 12; ++j)
                            escort->AddWaypoint(j, GreymaneWP[j][0] + roll_x, GreymaneWP[j][1] + roll_y, GreymaneWP[j][2]);

                        escort->Start(true, true);
                    }
                }
        }

        void SummonCrowley()
        {
            if (Creature* crowley = me->SummonCreature(NPC_LORD_DARIUS_CROWLEY_TBFGC, -1791.19f, 1323.6f, 19.8029f))
            {
                uiCrowleyGUID = crowley->GetGUID();

                if (npc_escortAI* escort = CAST_AI(npc_escortAI, crowley->AI()))
                {
                    for (int j = 0; j < 46; ++j)
                        escort->AddWaypoint(j, FWorgenWP[j][0], FWorgenWP[j][1], FWorgenWP[j][2]);

                    escort->Start(true, true);
                }
            }

            for (int i = 0; i < 12; ++i)
                if (Creature* worgen = me->SummonCreature(NPC_WORGEN_WARRIOR, WorgenSummPos[i][0], WorgenSummPos[i][1], WorgenSummPos[i][2]))
                {
                    WorgenList.push_back(worgen->GetGUID());

                    if (npc_escortAI* escort = CAST_AI(npc_escortAI, worgen->AI()))
                    {
                        int roll_x = irand(-3, 3);
                        int roll_y = irand(-3, 3);

                        for (int j = 0; j < 46; ++j)
                            escort->AddWaypoint(j, FWorgenWP[j][0] + roll_x, FWorgenWP[j][1] + roll_y, FWorgenWP[j][2]);

                        escort->Start(true, true);
                    }
                }
        }

        void DoAction(const int32 action)
        {
            switch (action)
            {
                case ACTION_CANNON_AT_POSITION:
                    if (uiBattlePhase == PHASE_MILITARY_DISTRICT)
                        Event = true;
                    break;
                case ACTION_GOREROT_DIED:
                    if (Creature* crowley = Unit::GetCreature(*me, uiCrowleyGUID))
                        crowley->AI()->DoAction(ACTION_GOREROT_DIED);
                    uiBattlePhase = PHASE_GREYMANE_COURT;
                    BreakEscortPaused();
                    break;
                case ACTION_FINISH_TBFGC:
                    Event = false;
                    Finish = true;
                    break;
            }
        }

        uint32 GetData(uint32 type) const
        {
            if (type == DATA_CURRENT_PHASE)
                return uiBattlePhase;

            return 0;
        }

        void SummonLorna()
        {
            if (Creature* lorna = me->SummonCreature(NPC_LORNA_CROWLEY_TBFGC, -1551.90f,1284.75f,13.992f))
            {
                uiLornaGUID = lorna->GetGUID();

                if (npc_escortAI* escort = CAST_AI(npc_escortAI, lorna->AI()))
                {
                    for (int i = 0; i < 78; ++i)
                        escort->AddWaypoint(i, LornaWP[i][0], LornaWP[i][1], LornaWP[i][2]);

                    escort->Start(false, true);
                }
            }

            for (int i = 0; i < 3; ++i)
                if (Creature* cannon = me->SummonCreature(NPC_EMBERSTONE_CANNON, SummonCannonPos[i][0],
                    SummonCannonPos[i][1], SummonCannonPos[i][2], SummonCannonPos[i][3]))
                {
                    CannonList.push_back(cannon->GetGUID());
                    float x, y, z, o;
                    cannon->GetPosition(x, y, z, o);

                    if (Creature* villager = cannon->SummonCreature(NPC_FREED_EMBERSTONE_VILLAGER, x, y, z, o))
                    {
                        villager->EnterVehicle(cannon);
                        cannon->EnableAI();
                    }

                    if (npc_escortAI* escort = CAST_AI(npc_escortAI, cannon->AI()))
                    {
                        int roll_x = irand(-3, 3);
                        int roll_y = irand(-3, 3);

                        for (int j = 0; j < 11; ++j)
                            escort->AddWaypoint(j, CannonWP[j][0] + roll_x, CannonWP[j][1] + roll_y, CannonWP[j][2]);

                        escort->Start(false, true);
                    }
                }
        }

        void DamageTaken(Unit* /*damager*/, uint32 &damage)
        {
            if (damage >= me->GetHealth())
                damage = 0;
        }

        void StartEvent()
        {
            if (!Event && uiBattlePhase == PHASE_NONE)
            {
                Event = true;
                Fail = true;
                uiSubPhase= 0;
                uiEventTimer = 10000;
                uiFailTimer = 900000;
                uiBattlePhase = PHASE_INTRO;
                uiDeadBossCount = 2;
            }
        }

        void KilledBoss()
        {
            --uiDeadBossCount;
        }

        void BreakEscortPaused()
        {
            SetEscortPaused(false);

            if (Creature* myriam = Unit::GetCreature(*me, uiMyriamGUID))
                if (npc_escortAI* escort = CAST_AI(npc_escortAI, myriam->AI()))
                    escort->SetEscortPaused(false);

            if (Creature* almyra = Unit::GetCreature(*me, uiAlmyraGUID))
                if (npc_escortAI* escort = CAST_AI(npc_escortAI, almyra->AI()))
                    escort->SetEscortPaused(false);

            if (Creature* lorna = Unit::GetCreature(*me, uiLornaGUID))
                if (npc_escortAI* escort = CAST_AI(npc_escortAI, lorna->AI()))
                    escort->SetEscortPaused(false);

            if (Creature* crowley = Unit::GetCreature(*me, uiCrowleyGUID))
                if (npc_escortAI* escort = CAST_AI(npc_escortAI, crowley->AI()))
                    escort->SetEscortPaused(false);

            if (!FirstWave.empty())
            {
                for (std::list<uint64>::const_iterator itr = FirstWave.begin(); itr != FirstWave.end(); )
                {
                    Creature* militia = Unit::GetCreature(*me, *itr);
                    ++itr;

                    if (militia)
                        if (npc_escortAI* escort = CAST_AI(npc_escortAI, militia->AI()))
                            escort->SetEscortPaused(false);
                }
            }

            if (!SecondWave.empty())
            {
                for (std::list<uint64>::const_iterator itr = SecondWave.begin(); itr != SecondWave.end(); )
                {
                    Creature* militia = Unit::GetCreature(*me, *itr);
                    ++itr;

                    if (militia)
                        if (npc_escortAI* escort = CAST_AI(npc_escortAI, militia->AI()))
                            escort->SetEscortPaused(false);
                }
            }

            if (!ThirdWave.empty())
            {
                for (std::list<uint64>::const_iterator itr = ThirdWave.begin(); itr != ThirdWave.end(); )
                {
                    Creature* militia = Unit::GetCreature(*me, *itr);
                    ++itr;

                    if (militia)
                        if (npc_escortAI* escort = CAST_AI(npc_escortAI, militia->AI()))
                            escort->SetEscortPaused(false);
                }
            }

            if (!WorgenList.empty())
            {
                for (std::list<uint64>::const_iterator itr = WorgenList.begin(); itr != WorgenList.end(); )
                {
                    Creature* worgen = Unit::GetCreature(*me, *itr);
                    ++itr;

                    if (worgen)
                        if (npc_escortAI* escort = CAST_AI(npc_escortAI,worgen->AI()))
                            escort->SetEscortPaused(false);
                }
            }
        }

        void StartBattle()
        {
            for (int i = 0; i < 96; ++i)
                AddWaypoint(i, FWaveWP[i][0], FWaveWP[i][1], FWaveWP[i][2]);

            Start(true, true);

            if (Creature* myriam = Unit::GetCreature(*me, uiMyriamGUID))
                if (npc_escortAI* escort = CAST_AI(npc_escortAI, myriam->AI()))
                {
                    for (int i = 0; i < 96; ++i)
                        escort->AddWaypoint(i, SWaveWP[i][0], SWaveWP[i][1], SWaveWP[i][2]);

                    escort->Start(true, true);
                }

            if (Creature* almyra = Unit::GetCreature(*me, uiAlmyraGUID))
                if (npc_escortAI* escort = CAST_AI(npc_escortAI, almyra->AI()))
                {
                    for (int i = 0; i < 87; ++i)
                        escort->AddWaypoint(i, TWaveWP[i][0], TWaveWP[i][1], TWaveWP[i][2]);

                    escort->Start(true, true);
                }

            for (std::list<uint64>::const_iterator itr = FirstWave.begin(); itr != FirstWave.end(); )
            {
                Creature* militia = Unit::GetCreature(*me, *itr);
                ++itr;

                if (militia)
                {
                    militia->AI()->SetData(DATA_WP_PAUSE, 30);

                    if (npc_escortAI* escort = CAST_AI(npc_escortAI, militia->AI()))
                    {
                        int32 roll_x = irand(-3, 3);
                        int32 roll_y = irand(-3, 3);

                        for (int i = 0; i < 96; ++i)
                            escort->AddWaypoint(i, FWaveWP[i][0] + roll_x, FWaveWP[i][1] + roll_y, FWaveWP[i][2]);

                        escort->Start(true, true);
                    }
                }
            }

            for (std::list<uint64>::const_iterator itr = SecondWave.begin(); itr != SecondWave.end(); )
            {
                Creature* militia = Unit::GetCreature(*me, *itr);
                ++itr;

                if (militia)
                {
                    militia->AI()->SetData(DATA_WP_PAUSE, 30);

                    if (npc_escortAI* escort = CAST_AI(npc_escortAI, militia->AI()))
                    {
                        int32 roll_x = irand(-3, 3);
                        int32 roll_y = irand(-3, 3);

                        for (int i = 0; i < 96; ++i)
                            escort->AddWaypoint(i, SWaveWP[i][0] + roll_x, SWaveWP[i][1] + roll_y, SWaveWP[i][2]);

                        escort->Start(true, true);
                    }
                }
            }

            for (std::list<uint64>::const_iterator itr = ThirdWave.begin(); itr != ThirdWave.end(); )
            {
                Creature* militia = Unit::GetCreature(*me, *itr);
                ++itr;

                if (militia)
                {
                    militia->AI()->SetData(DATA_WP_PAUSE, 17);

                    if (npc_escortAI* escort = CAST_AI(npc_escortAI, militia->AI()))
                    {
                        int32 roll_x = irand(-3, 3);
                        int32 roll_y = irand(-3, 3);

                        for (int i = 0; i < 87; ++i)
                            escort->AddWaypoint(i, TWaveWP[i][0] + roll_x, TWaveWP[i][1] + roll_y, TWaveWP[i][2]);

                        escort->Start(true, true);
                    }
                }
            }
        }

        void EnterEvadeMode()
        {
            npc_escortAI::EnterEvadeMode();

            if (Aura)
                DoCast(SPELL_SOLDIER_OF_TBFGC);
        }

        void SummonEventCreatures()
        {
            if (Creature* myriam = me->SummonCreature(NPC_MYRIAM_SPELLWAKER, -1412.95f, 1248.7f, 36.5112f, 1.76278f))
                uiMyriamGUID = myriam->GetGUID();

            if (Creature* almyra = me->SummonCreature(NPC_SISTER_ALMYRA, -1401.31f, 1251.91f, 36.5112f, 2.02458f))
                uiAlmyraGUID = almyra->GetGUID();

            for (int i = 0; i < 5; ++i)
            {
                if (Creature* militia = me->SummonCreature(NPC_GILNEAN_MILITIA, MilSumPos[i][0], MilSumPos[i][1], MilSumPos[i][2], MilSumPos[i][3]))
                {
                    FirstWave.push_back(militia->GetGUID());
                    float x, y, z = militia->GetPositionZ(), o = militia->GetOrientation();

                    for (int j = 1; j < 3; ++j)
                    {
                        militia->GetNearPoint2D(x, y, 2 * j, o + M_PI);

                        if (Creature* new_militia = me->SummonCreature(NPC_GILNEAN_MILITIA, x, y, z, o))
                            FirstWave.push_back(new_militia->GetGUID());
                    }

                    for (int j = 3; j < 6; ++j)
                    {
                        militia->GetNearPoint2D(x, y, j * 2, o + M_PI);

                        if (Creature* new_militia = me->SummonCreature(NPC_GILNEAN_MILITIA, x, y, z, o))
                            SecondWave.push_back(new_militia->GetGUID());
                    }

                    for (int j = 6; j < 9; ++j)
                    {
                        militia->GetNearPoint2D(x, y, j * 2, o + M_PI);

                        if (Creature* new_militia = me->SummonCreature(NPC_GILNEAN_MILITIA, x, y, z, o))
                            if (CAST_AI(npc_escortAI, new_militia->AI()))
                                ThirdWave.push_back(new_militia->GetGUID());
                    }
                }
            }
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 30:
                    SetEscortPaused(true);
                    SetFacingToLiam();
                    if (uiBattlePhase == PHASE_MERCHANT_SQUARE)
                    {
                        if (uiDeadBossCount <= 0)
                            Event = true;
                        else
                            EscortFinished = true;
                    }
                    break;
                case 44:
                    DoScriptText(LIAM_BATTLE_BATTLE_3, me);
                    SummonCrowley();
                    break;
                case 58:
                    Event = true;
                    break;
                case 59:
                    SetEscortPaused(true);
                    break;
                case 61:
                    if (Creature* crowley = Unit::GetCreature(*me, uiCrowleyGUID))
                        DoScriptText(CROWLEY_BATTLE_BATTLE_2, crowley);
                    break;
                case 80:
                    Event = true;
                    SummonKingCreaymane();
                    break;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (!Finish && Fail)
            {
                if (uiFailTimer <= diff)
                {
                    Fail = false;
                    uiFailTimer = 900000;
                    DespawnEvent(0);
                }
                else
                    uiFailTimer -= diff;
            }

            if (EscortFinished)
                if (uiDeadBossCount <= 0)
                {
                    uiSubPhase = 0;
                    uiEventTimer = 0;
                    EscortFinished = false;
                    Event = true;
                }

            if (Event)
            {
                if (uiEventTimer <= diff)
                    switch (uiBattlePhase)
                    {
                        case PHASE_INTRO:
                            ++uiSubPhase;
                            switch (uiSubPhase)
                            {
                                case 1:
                                    uiEventTimer = 7500;
                                    DoScriptText(LIAM_BATTLE_SPEACH_1, me);
                                    break;
                                case 2:
                                    uiEventTimer = 8500;
                                    DoScriptText(LIAM_BATTLE_SPEACH_2, me);
                                    break;
                                case 3:
                                    uiEventTimer = 10500;
                                    DoScriptText(LIAM_BATTLE_SPEACH_3, me);
                                    break;
                                case 4:
                                    uiEventTimer = 8500;
                                    DoScriptText(LIAM_BATTLE_SPEACH_4, me);
                                    break;
                                case 5:
                                    uiEventTimer = 10500;
                                    DoScriptText(LIAM_BATTLE_SPEACH_5, me);
                                    break;
                                case 6:
                                    uiEventTimer = 4500;
                                    DoScriptText(LIAM_BATTLE_SPEACH_6, me);
                                    break;
                                case 7:
                                    Event = false;
                                    StartBattle();
                                    uiSubPhase = 0;
                                    uiBattlePhase = PHASE_MERCHANT_SQUARE;
                                    me->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                                    DoScriptText(LIAM_BATTLE_FOR_GILNEAS, me);
                                    break;
                            }
                            break;
                        case PHASE_MERCHANT_SQUARE:
                            ++uiSubPhase;
                            switch (uiSubPhase)
                            {
                                case 1:
                                    uiEventTimer = 6500;
                                    SummonLorna();
                                    DoScriptText(LIAM_BATTLE_BATTLE_1, me);
                                    break;
                                case 2:
                                    uiSubPhase = 0;
                                    Event = false;
                                    uiEventTimer = 7000;
                                    BreakEscortPaused();
                                    uiBattlePhase = PHASE_MILITARY_DISTRICT;
                                    break;
                            }
                            break;
                        case PHASE_MILITARY_DISTRICT:
                            ++uiSubPhase;
                            switch (uiSubPhase)
                            {
                                case 1:
                                    uiEventTimer = 8000;
                                    DoScriptText(LIAM_BATTLE_BATTLE_2, me);
                                    break;
                                case 2:
                                    Event = false;
                                    uiEventTimer = 7000;
                                    if (Creature* lorna = Unit::GetCreature(*me, uiLornaGUID))
                                        DoScriptText(LORNA_BATTLE_BATTLE_2, lorna);
                                    break;
                                case 3:
                                    uiEventTimer = 25000;
                                    me->SummonCreature(NPC_GOREROT, -1671.78f,1449.64f,52.287f);
                                    if (Creature* crowley = Unit::GetCreature(*me, uiCrowleyGUID))
                                        crowley->AI()->DoAction(ACTION_GOREROT_FIGHT);
                                    break;
                                case 4:
                                    Event = false;
                                    uiSubPhase = 0;
                                    uiEventTimer = 10000;
                                    if (Creature* crowley = Unit::GetCreature(*me, uiCrowleyGUID))
                                        DoScriptText(CROWLEY_BATTLE_BATTLE_1, crowley);
                                    break;
                            }
                            break;
                        case PHASE_GREYMANE_COURT:
                            ++uiSubPhase;
                            switch (uiSubPhase)
                            {
                                case 1:
                                    uiEventTimer = 21000;
                                    if (Creature* greymane = Unit::GetCreature(*me, uiGreymaneGUID))
                                        DoScriptText(GREYMANE_BATTLE_BATTLE_1, greymane);
                                    break;
                                case 2:
                                    Event = false;
                                    uiSubPhase = 0;
                                    uiEventTimer = 2000;
                                    if (Creature* greymane = Unit::GetCreature(*me, uiGreymaneGUID))
                                        greymane->AI()->DoAction(ACTION_CAN_ATTACK);
                                    break;
                            }
                            break;
                    }
                else
                    uiEventTimer -= diff;
            }

            if (Finish)
            {
                if (uiEventTimer <= diff)
                {
                    ++uiSubPhase;
                    switch (uiSubPhase)
                    {
                        case 1:
                            uiEventTimer = 3000;
                            if (Creature* sylvanas = Unit::GetCreature(*me, uiSylvanasGUID))
                                DoScriptText(SYLVANAS_KILL_LIAM, sylvanas);
                            Aura = false;
                            me->Dismount();
                            me->RemoveAllAuras();
                            break;
                        case 2:
                            uiEventTimer = 4000;
                            if (Creature* greymane = Unit::GetCreature(*me, uiGreymaneGUID))
                            {
                                SetRun(true);
                                DoScriptText(LIAM_BATTLE_DEATH_1, me);
                                float x, y;
                                greymane->GetNearPoint2D(x, y, 0.5f, greymane->GetOrientation());
                                if (Creature* sylvanas = Unit::GetCreature(*me, uiSylvanasGUID))
                                    DoStartMovement(sylvanas, 1.0f);
                            }
                            break;
                        case 3:
                            uiEventTimer = 3000;
                            if (Creature* sylvanas = Unit::GetCreature(*me, uiSylvanasGUID))
                            {
                                sylvanas->CastSpell(me, SPELL_SHOOT_LIAM, false);
                                DoCast(SPELL_BFGC_COMPLETE);
                                if (me->IsSummon())
                                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                                        if (Creature* krennan = summoner->ToCreature())
                                            krennan->AI()->DoAction(ACTION_BATTLE_COMPLETE);
                                sylvanas->GetMotionMaster()->MovePoint(0, -1628.85f, 1626.61f, 20.4884f);
                                sylvanas->DespawnOrUnsummon(2000);
                                if (Creature* greymane = Unit::GetCreature(*me, uiGreymaneGUID))
                                    DoScriptText(GREYMANE_YELL_LIAM, greymane);
                            }
                            break;
                        case 4:
                            uiEventTimer = 5000;
                            if (Creature* greymane = Unit::GetCreature(*me, uiGreymaneGUID))
                                greymane->SetStandState(UNIT_STAND_STATE_KNEEL);
                            SetFacingToLiam();
                            break;
                        case 5:
                            uiEventTimer = 3000;
                            DoScriptText(LIAM_BATTLE_DEATH_2, me);
                            break;
                        case 6:
                            DespawnEvent(30000);
                            Finish = false;
                            DoScriptText(LIAM_BATTLE_DEATH_3, me);
                            break;
                    }
                }
                else
                    uiEventTimer -= diff;
            }

            if (!UpdateVictim())
                return;

            if (uiRandomSpechTimer <= diff)
            {
                uiRandomSpechTimer = urand(10000, 30000);
                uint8 roll = urand(0, 3);
                DoScriptText(LIAM_RANDOM_BATTLE_SPEACH - roll, me);
            }
            else
                uiRandomSpechTimer -= diff;

            if (uiShootTimer <= diff)
            {
                uiShootTimer = 1500;
                DoCast(me->GetVictim(), SPELL_SHOOT);
            }
            else
                uiShootTimer -= diff;

            if (uiMultiShotTimer <= diff)
            {
                uiMultiShotTimer = 3000;
                DoCast(me->GetVictim(), SPELL_MULTI_SHOT);
            }
            else
                uiMultiShotTimer -= diff;

            if (uiChallengingShoutTimer <= diff)
            {
                uiChallengingShoutTimer = urand(10000, 30000);
                DoCast(SPELL_CHALLENGING_SHOUT);
            }
            else
                uiChallengingShoutTimer -= diff;
        }
    };
};

class npc_gilnean_militia_tbfgc : public CreatureScript
{
public:
    npc_gilnean_militia_tbfgc() : CreatureScript("npc_gilnean_militia_tbfgc") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gilnean_militia_tbfgcAI(creature);
    }

    struct npc_gilnean_militia_tbfgcAI : public npc_escortAI
    {
        npc_gilnean_militia_tbfgcAI(Creature* creature) : npc_escortAI(creature)
        {
            creature->setActive(true);
            SetCombatMovement(false);
            SetDespawnAtEnd(false);
            SetDespawnAtFar(false);
            uiShotTimer = 2000;
            uiIWingClipTimer = urand(30000, 60000);
            uiSunderArmorTimer = 12000;
            uiPausePoint = 100500;
        }

        uint32 uiShotTimer;
        uint32 uiIWingClipTimer;
        uint32 uiSunderArmorTimer;
        uint32 uiPausePoint;

        void SetData(uint32 data, uint32 value)
        {
            if (data == DATA_WP_PAUSE)
                uiPausePoint = value;
        }

        void SpellHit(Unit* /*caster*/, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_BANSHEE_QUEENS_WAIL)
            {
                me->AddUnitState(UNIT_STATE_ROOT);
                me->AddUnitMovementFlag(MOVEMENTFLAG_ROOT);
                me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_PASSIVE);
            }
        }

        void WaypointReached(uint32 point)
        {
            if (point == uiPausePoint)
                if (me->IsSummon())
                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        if (Creature* liam = summoner->ToCreature())
                        {
                            if (point == 17)
                            {
                                if (liam->AI()->GetData(DATA_CURRENT_PHASE) == PHASE_MERCHANT_SQUARE)
                                    SetEscortPaused(true);

                                uiPausePoint = 46;
                            }

                            if (point == 30)
                            {
                                if (liam->AI()->GetData(DATA_CURRENT_PHASE) == PHASE_MERCHANT_SQUARE)
                                    SetEscortPaused(true);

                                uiPausePoint = 59;
                            }

                            if (point == 46 || point == 59)
                                if (liam->AI()->GetData(DATA_CURRENT_PHASE) == PHASE_MILITARY_DISTRICT)
                                    SetEscortPaused(true);
                        }
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (!UpdateVictim())
                return;

            if (uiShotTimer <= diff)
            {
                uiShotTimer = 2000;

                if (me->GetVictim() && me->IsInRange(me->GetVictim(), 2.0f, 25.0f, false))
                    DoCast(me->GetVictim(), SPELL_SHOOT_TBFGC);
            }
            else
                uiShotTimer -= diff;

            if (uiIWingClipTimer <= diff)
            {
                uiIWingClipTimer = urand(30000, 60000);
                DoCast(me->GetVictim(), SPELL_IMPROVED_WING_CLIP);
            }
            else
                uiIWingClipTimer -= diff;

            if (uiSunderArmorTimer <= diff)
            {
                uiSunderArmorTimer = 12000;
                DoCast(me->GetVictim(), SPELL_SUNDER_ARMOR);
            }
            else
                uiSunderArmorTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

class npc_myriam_spellwaker_tbfgc : public CreatureScript
{
public:
    npc_myriam_spellwaker_tbfgc() : CreatureScript("npc_myriam_spellwaker_tbfgc"){}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_myriam_spellwaker_tbfgcAI(creature);
    }

    struct npc_myriam_spellwaker_tbfgcAI : public npc_escortAI
    {
        npc_myriam_spellwaker_tbfgcAI(Creature* creature) : npc_escortAI(creature)
        {
            creature->setActive(true);
            SetCombatMovement(false);
            SetDespawnAtEnd(false);
            SetDespawnAtFar(false);
            uiBlizzardTimer = urand(10000, 25000);
            uiFireBlastTimer = urand(5000, 15000);
            uiFrostboltTimer = urand(5000, 15000);
        }

        uint32 uiBlizzardTimer;
        uint32 uiFireBlastTimer;
        uint32 uiFrostboltTimer;

        void EnterEvadeMode()
        {
            npc_escortAI::EnterEvadeMode();
            me->AddAura(SPELL_ARCANE_INTELLECT, me);
        }

        void SpellHit(Unit* /*caster*/, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_BANSHEE_QUEENS_WAIL)
            {
                me->AddUnitState(UNIT_STATE_ROOT);
                me->AddUnitMovementFlag(MOVEMENTFLAG_ROOT);
                me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_PASSIVE);
            }
        }

        void DamageTaken(Unit* /*damager*/, uint32 &damage)
        {
            if (me->GetHealthPct() < 10)
                damage = 0;
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 30:
                    if (me->IsSummon())
                        if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                            if (Creature* liam = summoner->ToCreature())
                                if (liam->AI()->GetData(DATA_CURRENT_PHASE) == PHASE_MERCHANT_SQUARE)
                                    SetEscortPaused(true);
                    break;
                case 59:
                    if (me->IsSummon())
                        if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                            if (Creature* liam = summoner->ToCreature())
                                if (liam->AI()->GetData(DATA_CURRENT_PHASE) == PHASE_MILITARY_DISTRICT)
                                    SetEscortPaused(true);
                    break;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (!UpdateVictim())
                return;

            if (uiFireBlastTimer <= diff)
            {
                uiFireBlastTimer = urand(5000, 15000);
                DoCast(me->GetVictim(), SPELL_FIRE_BLAST);
            }
            else
                uiFireBlastTimer -= diff;

            if (uiBlizzardTimer <= diff)
            {
                uiBlizzardTimer = urand(10000, 25000);
                DoCast(SPELL_BLIZZARD);
            }
            else
                uiBlizzardTimer -= diff;

            if (uiFrostboltTimer <= diff)
            {
                uiFrostboltTimer = urand(5000, 15000);
                DoCast(me->GetVictim(), SPELL_FROSTBOLT);
            }
            else
                uiFrostboltTimer -= diff;
        }
    };
};

class npc_sister_almyra_tbfgc : public CreatureScript
{
public:
    npc_sister_almyra_tbfgc() : CreatureScript("npc_sister_almyra_tbfgc") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_sister_almyra_tbfgcAI(creature);
    }

    struct npc_sister_almyra_tbfgcAI : public npc_escortAI
    {
        npc_sister_almyra_tbfgcAI(Creature* creature) : npc_escortAI(creature)
        {
            creature->setActive(true);
            SetCombatMovement(false);
            SetDespawnAtEnd(false);
            SetDespawnAtFar(false);
            uiFlashHealTimer = urand(1500, 3000);
            uiHolyNovaTimer = urand(3000, 5000);
        }

        uint32 uiFlashHealTimer;
        uint32 uiHolyNovaTimer;

        void SpellHit(Unit* /*caster*/, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_BANSHEE_QUEENS_WAIL)
            {
                me->AddUnitState(UNIT_STATE_ROOT);
                me->AddUnitMovementFlag(MOVEMENTFLAG_ROOT);
                me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_PASSIVE);
            }
        }

        void EnterEvadeMode()
        {
            npc_escortAI::EnterEvadeMode();
            me->AddAura(SPELL_ARCANE_INTELLECT, me);
        }

        void DamageTaken(Unit* /*damager*/, uint32 &damage)
        {
            if (me->GetHealthPct() < 10)
                damage = 0;
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 9:
                    if (me->IsSummon())
                        if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        {
                            if (Creature* ranger = summoner->SummonCreature(NPC_DARK_RANGER_ELITE, -1572.91f,1319.44f,35.556f))
                                if (npc_escortAI* escort = CAST_AI(npc_escortAI, ranger->AI()))
                                {
                                    for (int i = 0; i < 31; ++i)
                                        escort->AddWaypoint(i, FDarkRangerWP[i][0], FDarkRangerWP[i][1], FDarkRangerWP[i][2]);
                                    escort->Start(true, true, 0, NULL, false, true);
                                }

                            if (Creature* ranger = summoner->SummonCreature(NPC_DARK_RANGER_ELITE, -1570.32f,1318.69f,35.556f))
                                if (npc_escortAI* escort = CAST_AI(npc_escortAI, ranger->AI()))
                                {
                                    for (int i = 0; i < 30; ++i)
                                        escort->AddWaypoint(i, SDarkRangerWP[i][0], SDarkRangerWP[i][1], SDarkRangerWP[i][2]);
                                    escort->Start(true, true, 0, NULL, false, true);
                                }
                        }
                    break;
                case 17:
                    if (me->IsSummon())
                        if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                            if (Creature* liam = summoner->ToCreature())
                                if (liam->AI()->GetData(DATA_CURRENT_PHASE) == PHASE_MERCHANT_SQUARE)
                                    SetEscortPaused(true);
                    break;
                case 46:
                    if (me->IsSummon())
                        if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                            if (Creature* liam = summoner->ToCreature())
                                if (liam->AI()->GetData(DATA_CURRENT_PHASE) == PHASE_MILITARY_DISTRICT)
                                    SetEscortPaused(true);
                    break;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (!UpdateVictim())
                return;

            if (uiHolyNovaTimer <= diff)
            {
                uiHolyNovaTimer = urand(3000, 5000);
                DoCast(SPELL_HOLY_NOVA);
            }
            else
                uiHolyNovaTimer -= diff;

            if (uiFlashHealTimer <= diff)
            {
                uiFlashHealTimer = urand(1500, 3000);

                if (me->GetHealthPct() < 30.0f)
                    DoCast(SPELL_HOLY_NOVA);
                else
                    if (Unit* target = DoSelectLowestHpFriendly(35.0f, 1))
                        DoCast(target, SPELL_HOLY_NOVA);
            }
            else
                uiFlashHealTimer -= diff;
        }
    };
};

class npc_dark_ranger_elite_tbfgc : public CreatureScript
{
public:
    npc_dark_ranger_elite_tbfgc() : CreatureScript("npc_dark_ranger_elite_tbfgc") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_dark_ranger_elite_tbfgcAI(creature);
    }

    struct npc_dark_ranger_elite_tbfgcAI : public npc_escortAI
    {
        npc_dark_ranger_elite_tbfgcAI(Creature* creature) : npc_escortAI(creature)
        {
            creature->setActive(true);
            SetDespawnAtEnd(false);
            SetDespawnAtFar(false);
            uiKnockbackTimer = urand(5000, 15000);
            uiShootTimer = 1500;
        }

        uint32 uiKnockbackTimer;
        uint32 uiShootTimer;

        void WaypointReached(uint32 /*point*/)
        {
        }

        void JustDied(Unit* /*killer*/)
        {
            if (me->IsSummon())
                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                    if (Creature* liam = summoner->ToCreature())
                        CAST_AI(npc_prince_liam_greymane_tbfgc::npc_prince_liam_greymane_tbfgcAI, liam->AI())->KilledBoss();
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (!UpdateVictim())
                return;

            if (uiKnockbackTimer <= diff)
            {
                uiKnockbackTimer = urand(5000, 15000);
                DoCast(SPELL_KNOCKBACK);
            }
            else
                uiKnockbackTimer -= diff;

            if (uiShootTimer <= diff)
            {
                uiShootTimer = 1500;
                DoCast(me->GetVictim(), SPELL_SHOOT);
            }
            else
                uiShootTimer -= diff;
        }
    };
};

class npc_emberstone_cannon : public CreatureScript
{
public:
    npc_emberstone_cannon() : CreatureScript("npc_emberstone_cannon") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_emberstone_cannonAI(creature);
    }

    struct npc_emberstone_cannonAI : public npc_escortAI
    {
        npc_emberstone_cannonAI(Creature* creature) : npc_escortAI(creature)
        {
            me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_SOLDIER_OF_TBFGC, true);
            me->setActive(true);
            SetDespawnAtEnd(false);
            SetDespawnAtFar(false);
        }

        void WaypointReached(uint32 point)
        {
            if (point == 10)
                if (Vehicle* vehicle = me->GetVehicleKit())
                    if (Unit* passenger = vehicle->GetPassenger(0))
                        if (Creature* villager = passenger->ToCreature())
                        {
                            villager->ExitVehicle();
                            villager->DespawnOrUnsummon(25000);
                        }
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);
        }
    };
};

class npc_lorna_crowley_tbfgc : public CreatureScript
{
public:
    npc_lorna_crowley_tbfgc() : CreatureScript("npc_lorna_crowley_tbfgc") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lorna_crowley_tbfgcAI(creature);
    }

    struct npc_lorna_crowley_tbfgcAI : public npc_escortAI
    {
        npc_lorna_crowley_tbfgcAI(Creature* creature) : npc_escortAI(creature)
        {
            creature->setActive(true);
            SetCombatMovement(false);
            SetDespawnAtEnd(false);
            SetDespawnAtFar(false);
            uiShootTimer = 1500;
        }

        uint32 uiShootTimer;

        void DamageTaken(Unit* /*damager*/, uint32 &damage)
        {
            if (me->GetHealthPct() < 10)
                damage = 0;
        }

        void SpellHit(Unit* /*caster*/, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_BANSHEE_QUEENS_WAIL)
            {
                me->AddUnitState(UNIT_STATE_ROOT);
                me->AddUnitMovementFlag(MOVEMENTFLAG_ROOT);
                me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_PASSIVE);
            }
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 8:
                    DoScriptText(LORNA_BATTLE_BATTLE_1, me);
                    if (me->IsSummon())
                        if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                            if (Creature* liam = summoner->ToCreature())
                                liam->AI()->DoAction(ACTION_CANNON_AT_POSITION);
                    break;
                case 41:
                    if (me->IsSummon())
                        if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                            if (Creature* liam = summoner->ToCreature())
                                if (liam->AI()->GetData(DATA_CURRENT_PHASE) == PHASE_MILITARY_DISTRICT)
                                    SetEscortPaused(true);
                    break;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (!UpdateVictim())
                return;

            if (uiShootTimer <= diff)
            {
                uiShootTimer = 1500;
                DoCast(me->GetVictim(), SPELL_SHOOT);
            }
            else
                uiShootTimer -= diff;
        }
    };
};

class npc_lord_darius_crowley_tbfgc : public CreatureScript
{
public:
    npc_lord_darius_crowley_tbfgc() : CreatureScript("npc_lord_darius_crowley_tbfgc") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lord_darius_crowley_tbfgcAI(creature);
    }

    struct npc_lord_darius_crowley_tbfgcAI : public npc_escortAI
    {
        npc_lord_darius_crowley_tbfgcAI(Creature* creature) : npc_escortAI(creature)
        {
            creature->setActive(true);
            SetDespawnAtEnd(false);
            SetDespawnAtFar(false);
            uiSliceAndDiceTimer = 30000;
            uiTauntTimer = 5000;
            uiJumpTimer = 8000;
            uiFeralLeapTimer = 1500;
            uiInterceptTimer = 21000;
            gorerot = false;
            jump = false;
        }

        uint32 uiSliceAndDiceTimer;
        uint32 uiTauntTimer;
        uint32 uiFeralLeapTimer;
        uint32 uiInterceptTimer;
        uint32 uiJumpTimer;
        bool gorerot;
        bool jump;

        void DoAction(const int32 action)
        {
            if (action == ACTION_GOREROT_FIGHT)
                gorerot = true;

            if (action == ACTION_GOREROT_DIED)
            {
                gorerot = false;
                me->GetMotionMaster()->MoveJump(-1715.62f, 1403.78f, 21.6688f, 10.0f, 10.0f);
            }
        }

        void SpellHit(Unit* /*caster*/, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_BANSHEE_QUEENS_WAIL)
            {
                me->AddUnitState(UNIT_STATE_ROOT);
                me->AddUnitMovementFlag(MOVEMENTFLAG_ROOT);
                me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_PASSIVE);
            }
        }

        void WaypointReached(uint32 point)
        {
            if (point == 10)
                if (me->IsSummon())
                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        if (Creature* liam = summoner->ToCreature())
                            if (liam->AI()->GetData(DATA_CURRENT_PHASE) == PHASE_MILITARY_DISTRICT)
                                SetEscortPaused(true);
        }

        void DamageTaken(Unit* /*damager*/, uint32 &damage)
        {
            if (me->GetHealthPct() < 10)
                damage = 0;
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (!UpdateVictim())
                return;

            if (gorerot)
            {
                if (uiJumpTimer <= diff)
                {
                    jump = true;
                    uiJumpTimer = 8000;
                    me->AddUnitState(UNIT_STATE_ROOT);
                    me->AddUnitMovementFlag(MOVEMENTFLAG_ROOT);
                    me->GetMotionMaster()->MoveJump(-1690.97f, 1430.47f, 40.9132f, 10.0f, 15.0f);
                }
                else
                    uiJumpTimer -= diff;
            }

            if (jump)
            {
                if (uiFeralLeapTimer <= diff)
                {
                    jump = false;
                    uiFeralLeapTimer = 1500;
                    float x, y, z;

                    if (Unit* target = me->GetVictim())
                    {
                        target->GetPosition(x, y, z);
                        me->CastSpell(x, y, z, SPELL_FERAL_LEAP, false);
                    }

                    me->ClearUnitState(UNIT_STATE_ROOT);
                    me->RemoveUnitMovementFlag(MOVEMENTFLAG_ROOT);
                }
                else
                    uiFeralLeapTimer -= diff;
            }

            if (!jump)
            {
                if (uiSliceAndDiceTimer <= diff)
                {
                    uiSliceAndDiceTimer = 30000;
                    DoCast(SPELL_SLICE_AND_DICE);
                }
                else
                    uiSliceAndDiceTimer -= diff;

                if (uiTauntTimer <= diff)
                {
                    uiTauntTimer = 10000;
                    DoCast(me->GetVictim(), SPELL_TAUNT);
                }
                else
                    uiTauntTimer -= diff;

                if (uiInterceptTimer <= diff)
                {
                    uiInterceptTimer = 11000;

                    if (me->GetVictim())
                    {
                        if (me->GetVictim() && me->IsInRange(me->GetVictim(), 8.0f, 25.0f, false))
                            DoCast(me->GetVictim(), SPELL_INTERCEPT);
                    }
                }
                else
                    uiInterceptTimer -= diff;
            }
        }
    };
};

class worgen_warrior_tbfgc : public CreatureScript
{
public:
    worgen_warrior_tbfgc() : CreatureScript("worgen_warrior_tbfgc") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new worgen_warrior_tbfgcAI(creature);
    }

    struct worgen_warrior_tbfgcAI : public npc_escortAI
    {
        worgen_warrior_tbfgcAI(Creature* creature) : npc_escortAI(creature)
        {
            creature->setActive(true);
            SetDespawnAtEnd(false);
            SetDespawnAtFar(false);
        }

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_SMASH)
            {
                float x, y, z;
                caster->GetPosition(x, y, z);
                me->GetMotionMaster()->MoveJump(x, y, z, 10.0f, 10.0f);
            }

            if (spell->Id == SPELL_BANSHEE_QUEENS_WAIL)
            {
                me->AddUnitState(UNIT_STATE_ROOT);
                me->AddUnitMovementFlag(MOVEMENTFLAG_ROOT);
                me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_PASSIVE);
            }
        }

        void WaypointReached(uint32 point)
        {
            if (point == 10)
                if (me->IsSummon())
                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        if (Creature* liam = summoner->ToCreature())
                            if (liam->AI()->GetData(DATA_CURRENT_PHASE) == PHASE_MILITARY_DISTRICT)
                                SetEscortPaused(true);
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);
        }
    };
};

class npc_gorerot : public CreatureScript
{
public:
    npc_gorerot() : CreatureScript("npc_gorerot") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gorerotAI (creature);
    }

    struct npc_gorerotAI : public npc_escortAI
    {
        npc_gorerotAI(Creature* creature) : npc_escortAI(creature)
        {
            me->setActive(true);
            SetDespawnAtEnd(false);
            SetDespawnAtFar(false);
            uiThunderclapTimer = urand(5000, 15000);
            uiSmashTimer = urand(5000, 10000);
            uiGorerotThreatTimer= 3000;
            FreePlace = true;
            StartEscort();
        }

        void StartEscort()
        {
            AddWaypoint(0,-1671.78f,1449.64f,52.287f, 0);
            AddWaypoint(1,-1710.47f, 1407.91f, 21.752f);
            SetSpeedZ(27.0f);
            Start(true, true);
        }

        uint32 uiThunderclapTimer;
        uint32 uiSmashTimer;
        uint32 uiGorerotThreatTimer;
        bool FreePlace;

        void WaypointReached(uint32 point)
        {
            if (point == 1)
            {
                DoScriptText(GOREROT_YELL_CRUSH, me);

                if (me->IsSummon())
                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        AttackStart(summoner);
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            if (me->IsSummon())
                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                    if (Creature* liam = summoner->ToTempSummon())
                        liam->AI()->DoAction(ACTION_GOREROT_DIED);
        }

        Creature* GetFreeWorgen(std::list<Creature*> List) const
        {
            for (std::list<Creature*>::const_iterator itr = List.begin(); itr != List.end(); )
            {
                if (!(*itr)->IsOnVehicle(me))
                    return (*itr);

                ++itr;
            }

            return NULL;
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (!UpdateVictim())
                return;

            if (FreePlace)
            {
                FreePlace = false;
                std::list<Creature*> WorgenList;
                me->GetCreatureListWithEntryInGrid(WorgenList, NPC_WORGEN_WARRIOR, 30.0f);

                if (Vehicle* vehicle = me->GetVehicleKit())
                {
                    for (int i = 0; i < 2; ++i)
                        if (vehicle->HasEmptySeat(i))
                            if (Creature* worgen = GetFreeWorgen(WorgenList))
                            {
                                worgen->EnterVehicle(me, i);
                                worgen->m_movementInfo.t_pos.m_orientation = M_PI;
                            }

                    for (int i = 2; i < 4; ++i)
                        if (vehicle->HasEmptySeat(i))
                            if (Creature* worgen = GetFreeWorgen(WorgenList))
                                worgen->EnterVehicle(me, i);
                }
            }

            if (uiThunderclapTimer <= diff)
            {
                uiThunderclapTimer = urand(5000, 15000);

                if (Vehicle* vehicle = me->GetVehicleKit())
                    vehicle->RemoveAllPassengers();

                FreePlace = true;
                DoCast(SPELL_THUNDERCLAP);
            }
            else
                uiThunderclapTimer -= diff;

            if (uiSmashTimer <= diff)
            {
                uiSmashTimer = urand(5000, 10000);
                uint8 roll = urand(0, 4);

                if (Vehicle* vehicle = me->GetVehicleKit())
                    if (Unit* passenger = vehicle->GetPassenger(roll))
                    {
                        passenger->ExitVehicle();
                        DoCast(passenger, SPELL_SMASH);
                        FreePlace = true;
                    }
            }
            else
                uiSmashTimer -= diff;

            if (uiGorerotThreatTimer <= diff)
            {
                uiGorerotThreatTimer = 3000;
                DoCast(SPELL_GOREROT_THREAT);
            }
            else
                uiGorerotThreatTimer -= diff;
        }
    };
};

class npc_king_genn_greymane_tbfgc : public CreatureScript
{
public:
    npc_king_genn_greymane_tbfgc() : CreatureScript("npc_king_genn_greymane_tbfgc") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_king_genn_greymane_tbfgcAI(creature);
    }

    struct npc_king_genn_greymane_tbfgcAI : public npc_escortAI
    {
        npc_king_genn_greymane_tbfgcAI(Creature* creature) : npc_escortAI(creature)
        {
            creature->setActive(true);
            SetDespawnAtEnd(false);
            SetDespawnAtFar(false);
            uiSylvanasTimer = 0;
            uiPhase = 0;
            sylvanas = false;
            can_attack = false;
        }

        void DamageTaken(Unit* /*damager*/, uint32 &damage)
        {
            if (me->GetHealthPct() < 10)
                damage = 0;
        }

        uint32 uiSylvanasTimer;
        uint8 uiPhase;
        bool sylvanas;
        bool can_attack;

        void SpellHit(Unit* /*caster*/, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_BANSHEE_QUEENS_WAIL)
            {
                me->AddUnitState(UNIT_STATE_ROOT);
                me->AddUnitMovementFlag(MOVEMENTFLAG_ROOT);
                me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_PASSIVE);
            }
        }

        void DoAction(const int32 action)
        {
            if (action == ACTION_ATTACK_SYLVANAS)
                sylvanas = true;

            if (action == ACTION_CAN_ATTACK)
                can_attack = true;
        }

        void WaypointReached(uint32 /*point*/)
        {
        }

        void UpdateAI(const uint32 diff)
        {
            if (sylvanas && can_attack)
            {
                if (uiSylvanasTimer <= diff)
                {
                    if (Creature* Sylvanas = me->FindNearestCreature(NPC_LADY_SYLVANAS_WINDRUNNER_TBFGC, 50.0f))
                    {
                        ++uiPhase;
                        switch (uiPhase)
                        {
                            case 1:
                                uiSylvanasTimer = 1000;
                                DoCast(SPELL_GREYMANE_TRANSFORM);
                                Sylvanas->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
                                AttackStart(Sylvanas);
                                break;
                            case 2:
                                sylvanas = false;
                                can_attack = false;
                                uiSylvanasTimer = 7000;
                                DoScriptText(GREYMANE_BATTLE_BATTLE_2, me);
                                float x, y, z = Sylvanas->GetPositionZ();
                                Sylvanas->GetNearPoint2D(x, y, 3.0f, Sylvanas->GetOrientation());
                                me->GetMotionMaster()->MoveJump(x, y, z, 10.0f, 10.0f);
                                break;
                        }
                    }
                }
                else
                    uiSylvanasTimer -= diff;
            }

            npc_escortAI::UpdateAI(diff);
        }
    };
};

class npc_lady_sylvanas_windrunner_tbfgc : public CreatureScript
{
public:
    npc_lady_sylvanas_windrunner_tbfgc() : CreatureScript("npc_lady_sylvanas_windrunner_tbfgc") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lady_sylvanas_windrunner_tbfgcAI (creature);
    }

    struct npc_lady_sylvanas_windrunner_tbfgcAI : public ScriptedAI
    {
        npc_lady_sylvanas_windrunner_tbfgcAI(Creature* creature) : ScriptedAI(creature)
        {
            me->AddUnitState(UNIT_STATE_ROOT);
            me->AddUnitMovementFlag(MOVEMENTFLAG_ROOT);
            me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
            uiShootTimer = 1500;
            move = false;
            health = false;
            finish = false;
        }

        uint32 uiShootTimer;
        bool move;
        bool health;
        bool finish;

        void MoveInLineOfSight(Unit* who)
        {
            if (!move)
                if (who->GetEntry() == NPC_KING_GENN_GREYMANE_TBFGC && me->IsWithinDistInMap(who, 25.0f))
                {
                    move = true;
                    who->ToCreature()->AI()->DoAction(ACTION_ATTACK_SYLVANAS);
                }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (!health && me->GetHealthPct() < 30)
            {
                health = true;
                DoScriptText(SYLVANAS_YELL_ENOUGH, me);
                DoCast(SPELL_BANSHEE_QUEENS_WAIL);
                me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_PASSIVE);
                me->CombatStop();

                if (me->IsSummon())
                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        if (Creature* liam = summoner->ToCreature())
                            liam->AI()->DoAction(ACTION_FINISH_TBFGC);
            }

            if (uiShootTimer <= diff)
            {
                uiShootTimer = 1500;
                DoCast(SPELL_SHOOT);
            }
            else
                uiShootTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

class npc_damaged_catapult_tbfgc : public CreatureScript
{
public:
    npc_damaged_catapult_tbfgc() : CreatureScript("npc_damaged_catapult_tbfgc") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_damaged_catapult_tbfgcAI (creature);
    }

    struct npc_damaged_catapult_tbfgcAI : public ScriptedAI
    {
        npc_damaged_catapult_tbfgcAI(Creature* creature) : ScriptedAI(creature)
        {
            me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_SOLDIER_OF_TBFGC, true);
        }

        void PassengerBoarded(Unit* /*who*/, int8 /*seatId*/, bool apply)
        {
            if (apply)
                me->AddAura(72839, me);
            else
                me->RemoveAura(72839);
        }

        void OnCharmed(bool /*charm*/)
        {
            me->EnableAI();
        }

        void UpdateAI(const uint32 /*diff*/)
        {
        }
    };
};

#define    TIME_TO_START_BATTLE   -1977164

class npc_lorna_crowley : public CreatureScript
{
public:
    npc_lorna_crowley() : CreatureScript("npc_lorna_crowley") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_THE_BATTLE_FOR_GILNEAS_CITY)
        {
            if (creature->FindNearestCreature(NPC_KRENNAN_ARANAS_TBFGC, 35.0f))
                DoScriptText(TIME_TO_START_BATTLE, player);

            player->SaveToDB();
        }

        return true;
    }
};

class npc_krennan_aranas_tbfgc : public CreatureScript
{
public:
    npc_krennan_aranas_tbfgc() : CreatureScript("npc_krennan_aranas_tbfgc") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_krennan_aranas_tbfgcAI(creature);
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF + 1:
                if (npc_krennan_aranas_tbfgcAI* aranas = CAST_AI(npc_krennan_aranas_tbfgcAI, creature->AI()))
                    aranas->TelepotPlayer(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                CAST_AI(npc_krennan_aranas_tbfgcAI, creature->AI())->StartEvent();
                break;
        }
 
        player->CLOSE_GOSSIP_MENU();
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

         /*
        if (player->GetPhaseMask() != 262144)
            return false;
        */
        
        if (player->GetQuestStatus(QUEST_THE_BATTLE_FOR_GILNEAS_CITY) == QUEST_STATUS_INCOMPLETE)
            if (npc_krennan_aranas_tbfgcAI* AranasAI = CAST_AI(npc_krennan_aranas_tbfgcAI, creature->AI()))
            {

                    if (AranasAI->IsBattle())
                    {
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "я готов присоединитс€ к битве!",              GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,   "я буду ждать следующую группу атакующих!",    GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    }
                    else
                    {
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "я готов сражатьс€ против отрекшихс€ мразей!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,   "я еще не готов!",                             GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                    }
            }

        player->SEND_GOSSIP_MENU(MENU_START_BATTLE, creature->GetGUID());
        return true;
    }

    struct npc_krennan_aranas_tbfgcAI : public ScriptedAI
    {
        npc_krennan_aranas_tbfgcAI(Creature* creature) : ScriptedAI(creature)
        {
            Battle = false;
            creature->setActive(true);

            if (Creature* liam = me->SummonCreature(NPC_PRINCE_LIAM_GREYMANE, -1412.34f, 1274.66f, 36.4277f, 1.80124f))
                uiLiamGUID = liam->GetGUID();
            else
                uiLiamGUID = 0;
        }

        uint64 uiLiamGUID;
        bool Battle;

        void DoAction(const int32 action)
        {
            if (action == ACTION_BATTLE_COMPLETE)
            {
                Battle = false;
                uiLiamGUID = 0;

                if (Creature* liam = me->SummonCreature(NPC_PRINCE_LIAM_GREYMANE, -1412.34f, 1274.66f, 36.4277f, 1.80124f))
                    uiLiamGUID = liam->GetGUID();
            }
        }

        bool IsBattle()
        {
            return Battle;
        }

        void TelepotPlayer(Player* player)
        {
            if (Creature* liam = Unit::GetCreature(*me, uiLiamGUID))
            {
                float x, y, z, o;
                liam->GetPosition(x, y, z, o);
                player->TeleportTo(liam->GetMapId(), x, y, z, o);
            }
        }

        void StartEvent()
        {
            Battle = true;

            if (Creature* liam = Unit::GetCreature(*me, uiLiamGUID))
                CAST_AI(npc_prince_liam_greymane_tbfgc::npc_prince_liam_greymane_tbfgcAI, liam->AI())->StartEvent();
        }
    };
};

///////////
// Quest The Hunt For Sylvanas 24902
///////////

enum qTHFS
{
    QUEST_THE_HUNT_FOR_SYLVANAS         = 24902,

    NPC_TOBIAS_MISTMANTLE_QTHFS         = 38507,
    NPC_FORSAKEN_GENERAL_QTHFS          = 38617,
    NPC_LADY_SYLVANAS_QTHFS             = 38530,
    NPC_GENERAL_WARHOWL_QTHFS           = 38533,
    NPC_HIGH_EXECUTOR_CRENSHAW_QTHFS    = 38537,

    TOBIAS_SAY_GO                       = -1977123,
    TOBIAS_RAID_BOSS_WHISPER            = -1977124,
    TOBIAS_SAY_NOT_SEEN                 = -1977125,
    TOBIAS_SAY_DID_YOU_HEAR             = -1977126,
    TOBIAS_SAY_HIDE                     = -1977127,
    FORSAKEN_GENERAL_YELL               = -1977128,
    WARHOWL_SAY_LOSING                  = -1977129,
    WARHOWL_SAY_PLAGUE                  = -1977130,
    WARHOWL_SAY_GOOD_BY                 = -1977131,
    SYLVANAS_SAY_ASSURE                 = -1977132,
    SYLVANAS_SAY_TONE                   = -1977133,
    SYLVANAS_SAY_GO_WITH_HONOR          = -1977134,
    SYLVANAS_SAY_WHAT_QUESTION          = -1977135,
    CRENSHAW_SAY_ORDER                  = -1977136,
    CRENSHAW_AS_YOU_WISH                = -1977137,
    PLAYER_SAY_ME_NOOB                  = -1977138,
    SYLVANAS_YELL_FISH                  = -1977139,

    SPELL_SHOOT_QTHFS                   = SPELL_SHOOT_QSKA,
};

struct Psc_qthfs
{
    uint64 uiPlayerGUID;
    uint64 uiTobiasGUID;
};

class npc_lorna_crowley_qthfs : public CreatureScript
{
public:
    npc_lorna_crowley_qthfs() : CreatureScript("npc_lorna_crowley_qthfs") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_THE_HUNT_FOR_SYLVANAS)
        {
            CAST_AI(npc_lorna_crowley_qthfsAI, creature->AI())->SummonPersonalTobias(player->GetGUID());
            player->SaveToDB();
        }

        return true;
    }

    bool OnQuestComplete(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_THE_HUNT_FOR_SYLVANAS)
            CAST_AI(npc_lorna_crowley_qthfsAI, creature->AI())->DespawnPersonalTobias(player->GetGUID());

        if (quest->GetQuestId() == QUEST_THE_BATTLE_FOR_GILNEAS_CITY)
        {
            player->SaveToDB();
            return false;
        }

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lorna_crowley_qthfsAI (creature);
    }

    struct npc_lorna_crowley_qthfsAI : public ScriptedAI
    {
        npc_lorna_crowley_qthfsAI(Creature* creature) : ScriptedAI(creature)
        {
            lPlayers.clear();
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
        }

        std::list<Psc_qthfs> lPlayers;

        void SummonPersonalTobias(uint64 player)
        {
            for (std::list<Psc_qthfs>::iterator itr = lPlayers.begin(); itr != lPlayers.end(); )
            {
                if ((*itr).uiPlayerGUID == player)
                    if (Unit::GetCreature(*me, (*itr).uiTobiasGUID))
                        return;
                    else
                        itr = lPlayers.erase(itr);
                else
                    ++itr;
            }

            if (Creature* tobias = me->SummonCreature(NPC_TOBIAS_MISTMANTLE_QTHFS, -1655.85f,1605.59f,23.1241f))
            {
                tobias->SetSeerGUID(player);
                tobias->SetVisible(false);
                Psc_qthfs new_psc;
                new_psc.uiPlayerGUID = player;
                new_psc.uiTobiasGUID = tobias->GetGUID();
                lPlayers.push_back(new_psc);

                if (npc_escortAI* escort = CAST_AI(npc_escortAI, tobias->AI()))
                {
                    escort->AddWaypoint(1, -1655.85f,1605.59f,23.1241f);
                    escort->AddWaypoint(2, -1662.65f,1588.30f,23.1234f);
                    escort->AddWaypoint(3, -1656.50f,1582.69f,20.4859f);
                    escort->AddWaypoint(4, -1651.79f,1578.62f,21.6913f);
                    escort->AddWaypoint(5, -1626.70f,1601.46f,21.8459f,3000);
                    escort->AddWaypoint(6, -1599.64f,1607.60f,21.5590f,3000);
                    escort->AddWaypoint(7, -1587.31f,1607.03f,21.5981f,0);
                    escort->AddWaypoint(8, -1582.17f,1626.81f,20.5150f);
                    escort->AddWaypoint(9, -1561.72f,1629.94f,20.7313f,0);
                    escort->AddWaypoint(10,-1539.67f,1611.00f,20.6071f);
                    escort->AddWaypoint(11,-1521.61f,1606.76f,20.4858f);
                    escort->AddWaypoint(12,-1493.69f,1574.78f,20.4858f);
                    escort->AddWaypoint(13,-1491.67f,1576.35f,20.4856f, 10000);
                    escort->AddWaypoint(14,-1504.72f,1577.82f,20.4858f);
                    escort->AddWaypoint(15,-1516.82f,1578.70f,26.1162f);
                    escort->AddWaypoint(16,-1532.91f,1579.08f,26.9852f);
                    escort->AddWaypoint(17,-1539.01f,1575.19f,29.1926f);
                    escort->AddWaypoint(18,-1550.37f,1566.61f,29.2215f);
                    escort->AddWaypoint(19,-1555.80f,1570.43f,29.1907f);
                    escort->AddWaypoint(20,-1567.43f,1559.57f,29.1914f);
                    escort->AddWaypoint(21,-1565.06f,1553.10f,29.2230f);
                    escort->AddWaypoint(22,-1568.97f,1548.16f,29.2020f);
                    escort->AddWaypoint(23,-1593.16f,1525.53f,29.2358f);
                    escort->AddWaypoint(24,-1609.31f,1531.94f,29.2298f,0);
                    escort->AddWaypoint(25,-1617.92f,1532.31f,23.6932f);
                    escort->AddWaypoint(26,-1613.88f,1536.84f,24.7464f);
                    escort->AddWaypoint(27,-1613.19f,1536.32f,27.3053f);
                    escort->SetSpeedZ(15.0f);
                    escort->Start(false, true, player);
                }
            }
        }

        void DespawnPersonalTobias(uint64 player)
        {
            for (std::list<Psc_qthfs>::iterator itr = lPlayers.begin(); itr != lPlayers.end(); )
                if ((*itr).uiPlayerGUID == player)
                    itr = lPlayers.erase(itr);
                else
                    ++itr;
        }
    };
};

class npc_tobias_mistmantle_qthfs : public CreatureScript
{
public:
    npc_tobias_mistmantle_qthfs() : CreatureScript("npc_tobias_mistmantle_qthfs") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tobias_mistmantle_qthfsAI(creature);
    }

    struct npc_tobias_mistmantle_qthfsAI : public npc_escortAI
    {
        npc_tobias_mistmantle_qthfsAI(Creature* creature) : npc_escortAI(creature)
        {
            SetDespawnAtEnd(false);
            SetDespawnAtFar(false);
            creature->SetReactState(REACT_PASSIVE);
            creature->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
            uiSylvanasGUID = 0;
            uiWarhowlGUID = 0;
            uiCrenshawGUID = 0;
            uiEventTimer = 0;
            uiFailTimer = 600000;
            uiPhase = 0;
            Event = false;
            CheckSwim = false;
            Ide = false;
        }

        uint64 uiSylvanasGUID;
        uint64 uiWarhowlGUID;
        uint64 uiCrenshawGUID;
        uint32 uiEventTimer;
        uint32 uiFailTimer;
        uint8 uiPhase;
        bool Event;
        bool CheckSwim;
        bool Ide;

        void WaypointReached(uint32 point)
        {
            if (Player* player = GetPlayerForEscort())
                switch (point)
                {
                    case 1:
                        DoScriptText(TOBIAS_SAY_GO, player);
                        Event = true;
                        uiEventTimer = 2000;
                        uiPhase = 0;
                        break;
                    case 5:
                    case 13:
                        Event = true;
                        break;
                    case 24:
                        DoScriptText(TOBIAS_SAY_HIDE, player);
                        break;
                    case 27:
                        Event = true;
                        break;
                }
        }

        void SummonSilvanas(uint64 player)
        {
            if (Creature* sylvanas = me->SummonCreature(NPC_LADY_SYLVANAS_QTHFS, -1563.58f,1554.83f,31.2228f))
            {
                sylvanas->SetSeerGUID(player);
                sylvanas->SetVisible(false);
                uiSylvanasGUID = sylvanas->GetGUID();

                if (npc_escortAI* escort = CAST_AI(npc_escortAI, sylvanas->AI()))
                    escort->Start();
            }

            if (Creature* warhowl = me->SummonCreature(NPC_GENERAL_WARHOWL_QTHFS, -1560.37f,1555.82f,31.2305f))
            {
                warhowl->SetSeerGUID(player);
                warhowl->SetVisible(false);
                uiWarhowlGUID = warhowl->GetGUID();

                if (npc_escortAI* escort = CAST_AI(npc_escortAI, warhowl->AI()))
                    escort->Start();
            }

            if (Creature* crenshaw = me->SummonCreature(NPC_HIGH_EXECUTOR_CRENSHAW_QTHFS, -1561.6f,1554.87f,31.225f))
            {
                crenshaw->SetSeerGUID(player);
                crenshaw->SetVisible(false);
                uiCrenshawGUID = crenshaw->GetGUID();

                if (npc_escortAI* escort = CAST_AI(npc_escortAI, crenshaw->AI()))
                    escort->Start();
            }
        }

        void DespawnEvent()
        {
            if (Creature* sylvanas = Unit::GetCreature(*me, uiSylvanasGUID))
                sylvanas->DespawnOrUnsummon(5000);

            if (Creature* warhowl = Unit::GetCreature(*me, uiWarhowlGUID))
                warhowl->DespawnOrUnsummon(5000);

            if (Creature* crenshaw = Unit::GetCreature(*me, uiCrenshawGUID))
                crenshaw->DespawnOrUnsummon(5000);

            me->DespawnOrUnsummon(5000);
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);

            if (uiFailTimer <= diff)
            {
                if (Player* player = GetPlayerForEscort())
                    if (player->GetQuestStatus(QUEST_THE_HUNT_FOR_SYLVANAS) == QUEST_STATUS_INCOMPLETE)
                        player->FailQuest(QUEST_THE_HUNT_FOR_SYLVANAS);

                DespawnEvent();
            }
            else
                uiFailTimer -= diff;

            if (CheckSwim)
                if (Player* player = GetPlayerForEscort())
                    if(!player->HasUnitMovementFlag(MOVEMENTFLAG_SWIMMING))
                    {
                        CheckSwim = false;

                        if (player->GetQuestStatus(QUEST_THE_HUNT_FOR_SYLVANAS) == QUEST_STATUS_INCOMPLETE)
                            player->FailQuest(QUEST_THE_HUNT_FOR_SYLVANAS);

                        if (Ide)
                        {
                            DoScriptText(PLAYER_SAY_ME_NOOB, player);

                            if (Creature* sylvanas = Unit::GetCreature(*me, uiSylvanasGUID))
                            {
                                DoScriptText(SYLVANAS_YELL_FISH, player);
                                sylvanas->CastSpell(player, SPELL_SHOOT_QTHFS, false);
                            }
                        }

                        DespawnEvent();
                    }

            if (Event)
            {
                if (uiEventTimer <= diff)
                {
                    ++uiPhase;

                    if (Player* player = GetPlayerForEscort())
                        switch (uiPhase)
                        {
                            case 1:
                                Event = false;
                                uiEventTimer = 500;
                                me->Whisper(TOBIAS_RAID_BOSS_WHISPER, player->GetGUID(), true);
                                break;
                            case 2:
                                Event = false;
                                uiEventTimer = 500;
                                DoScriptText(TOBIAS_SAY_NOT_SEEN, player);
                                SetEscortPaused(false);
                                break;
                            case 3:
                                uiEventTimer = 8000;
                                if (me->FindNearestCreature(NPC_FORSAKEN_GENERAL_QTHFS, 50.0f))
                                    DoScriptText(FORSAKEN_GENERAL_YELL, player/*, true*/);
                                break;
                            case 4:
                                Event = false;
                                DoScriptText(TOBIAS_SAY_DID_YOU_HEAR, player);
                                break;
                            case 5:
                                if(player->HasUnitMovementFlag(MOVEMENTFLAG_SWIMMING))
                                {
                                    Event = false;
                                    CheckSwim = true;
                                    SummonSilvanas(player->GetGUID());
                                }
                                else
                                    --uiPhase;
                                break;
                            case 6:
                                uiEventTimer = 8000;
                                if (Creature* warhowl = Unit::GetCreature(*me, uiWarhowlGUID))
                                {
                                    if (Creature* sylvanas = Unit::GetCreature(*me, uiSylvanasGUID))
                                        sylvanas->SetFacingToObject(warhowl);
                                    DoScriptText(WARHOWL_SAY_LOSING, player);
                                }
                                break;
                            case 7:
                                uiEventTimer = 6000;
                                if (Unit::GetCreature(*me, uiSylvanasGUID))
                                    DoScriptText(SYLVANAS_SAY_ASSURE, player);
                                break;
                            case 8:
                                uiEventTimer = 10000;
                                if (Unit::GetCreature(*me, uiWarhowlGUID))
                                    DoScriptText(WARHOWL_SAY_PLAGUE, player);
                                break;
                            case 9:
                                uiEventTimer = 12000;
                                if (Unit::GetCreature(*me, uiSylvanasGUID))
                                    DoScriptText(SYLVANAS_SAY_TONE, player);
                                break;
                            case 10:
                                uiEventTimer = 7000;
                                if (Unit::GetCreature(*me, uiWarhowlGUID))
                                    DoScriptText(WARHOWL_SAY_GOOD_BY, player);
                                break;
                            case 11:
                                uiEventTimer = 12000;
                                if (Unit::GetCreature(*me, uiSylvanasGUID))
                                    DoScriptText(SYLVANAS_SAY_GO_WITH_HONOR, player);
                                if (Creature* warhowl = Unit::GetCreature(*me, uiWarhowlGUID))
                                    if (npc_escortAI* escort = CAST_AI(npc_escortAI, warhowl->AI()))
                                        escort->SetEscortPaused(false);
                                if (Creature* crenshaw = Unit::GetCreature(*me, uiCrenshawGUID))
                                    if (npc_escortAI* escort = CAST_AI(npc_escortAI, crenshaw->AI()))
                                        escort->SetEscortPaused(false);
                                break;
                            case 12:
                                uiEventTimer = 9000;
                                if (Unit::GetCreature(*me, uiCrenshawGUID))
                                    DoScriptText(CRENSHAW_SAY_ORDER, player);
                                break;
                            case 13:
                                uiEventTimer = 12000;
                                if (Unit::GetCreature(*me, uiSylvanasGUID))
                                    DoScriptText(SYLVANAS_SAY_WHAT_QUESTION, player);
                                break;
                            case 14:
                                uiEventTimer = 7000;
                                player->CompleteQuest(QUEST_THE_HUNT_FOR_SYLVANAS);
                                if (Unit::GetCreature(*me, uiCrenshawGUID))
                                    DoScriptText(CRENSHAW_AS_YOU_WISH, player);
                                if (Creature* sylvanas = Unit::GetCreature(*me, uiSylvanasGUID))
                                    if (npc_escortAI* escort = CAST_AI(npc_escortAI, sylvanas->AI()))
                                        escort->SetEscortPaused(false);
                                break;
                            case 15:
                                Event = false;
                                if (Creature* crenshaw = Unit::GetCreature(*me, uiCrenshawGUID))
                                    if (npc_escortAI* escort = CAST_AI(npc_escortAI, crenshaw->AI()))
                                        escort->SetEscortPaused(false);
                                me->DespawnOrUnsummon();
                                break;
                        }
                }
                else
                    uiEventTimer -= diff;
            }
        }
    };
};

class npc_lady_sylvanas_qthfs : public CreatureScript
{
public:
    npc_lady_sylvanas_qthfs() : CreatureScript("npc_lady_sylvanas_qthfs") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lady_sylvanas_qthfsAI(creature);
    }

    struct npc_lady_sylvanas_qthfsAI : public npc_escortAI
    {
        npc_lady_sylvanas_qthfsAI(Creature* creature) : npc_escortAI(creature)
        {
            creature->SetReactState(REACT_PASSIVE);
            creature->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
            SetDespawnAtFar(false);
        }

        void WaypointReached(uint32 point)
        {
            switch (point)
            {
                case 2:
                    if (me->IsSummon())
                        if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                            if (Creature* tobias = summoner->ToCreature())
                                CAST_AI(npc_tobias_mistmantle_qthfs::npc_tobias_mistmantle_qthfsAI, tobias->AI())->Ide = true;
                    break;
                case 3:
                SetEscortPaused(true);
                if (me->IsSummon())
                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        if (Creature* tobias = summoner->ToCreature())
                            CAST_AI(npc_tobias_mistmantle_qthfs::npc_tobias_mistmantle_qthfsAI, tobias->AI())->Event = true;
                    break;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);
        }
    };
};

class npc_general_warhowl_qthfs : public CreatureScript
{
public:
    npc_general_warhowl_qthfs() : CreatureScript("npc_general_warhowl_qthfs"){}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_general_warhowl_qthfsAI(creature);
    }

    struct npc_general_warhowl_qthfsAI : public npc_escortAI
    {
        npc_general_warhowl_qthfsAI(Creature* creature) : npc_escortAI(creature)
        {
            creature->SetReactState(REACT_PASSIVE);
            creature->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
            SetDespawnAtFar(false);
        }

        void WaypointReached(uint32 point)
        {
            if (point == 4)
                SetEscortPaused(true);
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);
        }
    };
};

class npc_high_executor_crenshaw_qthfs : public CreatureScript
{
public:
    npc_high_executor_crenshaw_qthfs() : CreatureScript("npc_high_executor_crenshaw_qthfs") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_high_executor_crenshaw_qthfsAI(creature);
    }

    struct npc_high_executor_crenshaw_qthfsAI : public npc_escortAI
    {
        npc_high_executor_crenshaw_qthfsAI(Creature* creature) : npc_escortAI(creature)
        {
            creature->SetReactState(REACT_PASSIVE);
            creature->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
            SetDespawnAtFar(false);
        }

        void WaypointReached(uint32 point)
        {
            if (point == 4 || point == 5)
                SetEscortPaused(true);
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);
        }
    };
};

///////////
// Quest Slowing the Inevitable 24920
///////////

enum qSTI
{
    QUEST_SLOWING_THE_INEVITABLE    = 24920,

    NPC_CAPTURED_RIDING_BAT         = 38540,
};

const float BatWP[25][3]=
{
    {-1623.96f, 1678.45f, 24.895f},{-1387.62f, 1635.81f, 50.594f},{-1351.91f, 1643.61f, 54.694f},
    {-1276.31f, 1669.73f, 63.570f},{-1252.37f, 1685.45f, 66.732f},{-1226.15f, 1692.88f, 69.788f},
    {-1210.95f, 1693.08f, 71.477f},{-1181.78f, 1681.70f, 74.933f},{-1155.08f, 1665.27f, 78.418f},
    {-1092.38f, 1623.88f, 86.757f},{-1061.24f, 1617.66f, 90.315f},{-1005.78f, 1628.92f, 96.749f},
    {-986.882f, 1638.44f, 99.158f},{-974.702f, 1667.29f, 102.61f},{-968.120f, 1683.84f, 104.58f},
    {-972.953f, 1711.52f, 107.82f},{-1003.23f, 1723.95f, 111.92f},{-1026.01f, 1713.48f, 114.76f},
    {-1098.00f, 1684.50f, 123.43f},{-1262.51f, 1632.93f, 90.103f},{-1353.43f, 1605.96f, 72.326f},
    {-1563.83f, 1657.32f, 59.702f},{-1569.20f, 1658.74f, 59.382f},{-1638.03f, 1671.92f, 30.168f},
    {-1667.43f, 1666.94f, 22.131f},
};


class npc_captured_riding_bat : public CreatureScript
{
public:
    npc_captured_riding_bat() : CreatureScript("npc_captured_riding_bat") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_captured_riding_batAI(creature);
    }

    struct npc_captured_riding_batAI : public npc_escortAI
    {
        npc_captured_riding_batAI(Creature* creature) : npc_escortAI(creature)
        {
            me->SetCanFly(true);
        }

        void FinishEscort()
        {
            me->DespawnOrUnsummon();
        }

        void WaypointReached(uint32 /*point*/)
        {
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);
        }
    };
};

class spell_captured_riding_bat : public SpellScriptLoader
{
    public:
        spell_captured_riding_bat() : SpellScriptLoader("spell_captured_riding_bat") { }

        class spell_captured_riding_bat_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_captured_riding_bat_SpellScript)

            void OnSummon(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                Unit* caster = GetCaster();

                if (!caster)
                    return;

                float x, y, z = caster->GetPositionZ();

                if (Creature* bat = caster->FindNearestCreature(38615, 15.0f))
                    bat->GetNearPoint2D(x, y, 3.0f, bat->GetOrientation() + M_PI / 2);
                else
                    caster->GetPosition(x, y);

                if (Creature* bat = caster->SummonCreature(NPC_CAPTURED_RIDING_BAT, x, y, z, 0.0f))
                    if (npc_escortAI* escort = CAST_AI(npc_escortAI, bat->AI()))
                    {
                        caster->EnterVehicle(bat, 0);
                        bat->EnableAI();
                        bat->SetSpeed(MOVE_FLIGHT, 4.0f, true);

                        for (int i = 0; i < 25; ++i)
                            escort->AddWaypoint(i, BatWP[i][0], BatWP[i][1], BatWP[i][2]);

                        escort->Start(true);
                    }
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_captured_riding_bat_SpellScript::OnSummon, EFFECT_0, SPELL_EFFECT_SUMMON);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_captured_riding_bat_SpellScript();
        }
};

///////////
// Quest Patriarch's Blessing 24679
///////////

enum qPB
{
    NPC_GILNEAS_FUNERAL_CAMERA     = 51083,
    NPC_KING_GENN_GREYMANE_QPB     = 50893,
    NPC_LORD_DARIUS_CROWLEY_QPB    = 50902,
    NPC_LORNA_CROWLEY_QPB          = 50881,
    NPC_CLONE_QPB                  = 51146,

    SPELL_FADE_TO_BLACK            = 89404,
    SPELL_MIRROR_IMAGE             = 45204,

    GREYMANE_SAY_QPB_1             = -1977147,
    GREYMANE_SAY_QPB_2             = -1977148,
    GREYMANE_SAY_QPB_3             = -1977149,
    LORNA_SAY_QPB                  = -1977150,
    CROWLEY_SAY_QPB                = -1977151,

    GO_OFFERINGS                   = 202319,
};

class npc_gilneas_funeral_camera : public CreatureScript
{
public:
    npc_gilneas_funeral_camera() : CreatureScript("npc_gilneas_funeral_camera") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gilneas_funeral_cameraAI(creature);
    }

    struct npc_gilneas_funeral_cameraAI : public ScriptedAI
    {
        npc_gilneas_funeral_cameraAI(Creature* creature) : ScriptedAI(creature)
        {
            creature->SetReactState(REACT_PASSIVE);
            creature->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
            uiGreymaneGUID = 0;
            uiLornaGUID = 0;
            uiCrowleyGUID = 0;
            uiCloneGUID = 0;
            uiEventTimer = 700;
            uiPhase = 0;

            if (me->IsSummon())
                Event = true;
            else
                Event = false;

            Despawn = false;
        }

        uint64 uiGreymaneGUID;
        uint64 uiLornaGUID;
        uint64 uiCrowleyGUID;
        uint64 uiCloneGUID;
        uint32 uiEventTimer;
        uint8 uiPhase;
        bool Event;
        bool Despawn;

        void PassengerBoarded(Unit* /*who*/, int8 /*seatId*/, bool apply)
        {
            if (!apply)
            {
                DespawnEvent();
                Event = false;
            }
        }

        void OnCharmed(bool /*charm*/)
        {
            me->NeedChangeAI = false;
            me->IsAIEnabled = true;
        }

        void SummonEventCreatures()
        {
            if (me->IsSummon())
                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                    if (Player* player = summoner->ToPlayer())
                    {
                        uint64 uiPlayerGUID = player->GetGUID();

                        me->SummonGameObject(GO_OFFERINGS, -1645.87f, 1903.36f, 29.9745f, 0, 0, 0, 0, 0, 0);

                        if (Creature* greymane = me->SummonCreature(NPC_KING_GENN_GREYMANE_QPB, -1644.238f, 1904.066f, 30.04164f, 3.56047f))
                        {
                            greymane->SetSeerGUID(uiPlayerGUID);
                            greymane->SetVisible(false);
                            uiGreymaneGUID = greymane->GetGUID();
                        }

                        if (Creature* crowley = me->SummonCreature(NPC_LORD_DARIUS_CROWLEY_QPB, -1642.351f, 1907.467f, 30.03497f, 3.577925f))
                        {
                            crowley->SetSeerGUID(uiPlayerGUID);
                            crowley->SetVisible(false);
                            uiCrowleyGUID = crowley->GetGUID();
                        }

                        if (Creature* lorna = me->SummonCreature(NPC_LORNA_CROWLEY_QPB, -1640.884f, 1903.595f, 30.03497f, 3.351032f))
                        {
                            lorna->SetSeerGUID(uiPlayerGUID);
                            lorna->SetVisible(false);
                            uiLornaGUID = lorna->GetGUID();
                        }

                        if (Creature* clone = me->SummonCreature(NPC_CLONE_QPB, -1640.681f, 1905.854f, 30.03497f, 3.682645f))
                        {
                            clone->SetSeerGUID(uiPlayerGUID);
                            clone->SetVisible(false);
                            player->AddAura(SPELL_MIRROR_IMAGE, clone);

                            if (Item const* item = (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND)))
                                clone->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, item->GetEntry());

                            if (Item const* item = (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND)))
                                clone->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 1, item->GetEntry());

                            if (Item const* item = (player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED)))
                                clone->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 2, item->GetEntry());

                            uiCloneGUID = clone->GetGUID();
                        }
                    }
        }

        void DespawnEvent()
        {
            if (me->IsSummon())
                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                    if (Player* player = summoner->ToPlayer())
                    {
                        Despawn = true;
                        player->CastSpell(player, SPELL_FADE_TO_BLACK, false);
                    }

            if (GameObject* go = me->FindNearestGameObject(GO_OFFERINGS, 30.0f))
                go->RemoveFromWorld();

            if (Creature* greymane = Unit::GetCreature(*me, uiGreymaneGUID))
                greymane->DespawnOrUnsummon();

            if (Creature* crowley = Unit::GetCreature(*me, uiCrowleyGUID))
                crowley->DespawnOrUnsummon();

            if (Creature* lorna = Unit::GetCreature(*me, uiLornaGUID))
                lorna->DespawnOrUnsummon();

            if (Creature* clone = Unit::GetCreature(*me, uiCloneGUID))
                clone->DespawnOrUnsummon();

            me->DespawnOrUnsummon(500);
        }

        void UpdateAI(const uint32 diff)
        {
            if (Despawn)
            {
                Despawn = false;

                if (me->IsSummon())
                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        if (Player* player = summoner->ToPlayer())
                            player->TeleportTo(654, -1725.0f, 1871.91f, 17.7934f, 3.17831f);
            }

            if (Event)
            {
                if (uiEventTimer <= diff)
                {
                    ++uiPhase;

                    if (me->IsSummon())
                        if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                            if (Player* player = summoner->ToPlayer())
                            switch (uiPhase)
                            {
                                case 1:
                                    uiEventTimer = 7000;
                                    SummonEventCreatures();
                                    player->EnterVehicle(me);
                                    me->EnableAI();
                                    break;
                                case 2:
                                    uiEventTimer = 9000;
                                    if (Creature* greymane = Unit::GetCreature(*me, uiGreymaneGUID))
                                    {
                                        DoScriptText(GREYMANE_SAY_QPB_1, player);
                                        greymane->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
                                    }
                                    break;
                                case 3:
                                    uiEventTimer = 7000;
                                    if (Creature* greymane = Unit::GetCreature(*me, uiGreymaneGUID))
                                    {
                                        DoScriptText(GREYMANE_SAY_QPB_2, player);
                                        greymane->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
                                    }
                                    break;
                                case 4:
                                    uiEventTimer = 9000;
                                    if (Unit::GetCreature(*me, uiLornaGUID))
                                        DoScriptText(LORNA_SAY_QPB, player);
                                    break;
                                case 5:
                                    uiEventTimer = 5000;
                                    if (Creature* crowley = Unit::GetCreature(*me, uiCrowleyGUID))
                                    {
                                        DoScriptText(CROWLEY_SAY_QPB, player);
                                        crowley->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);
                                    }
                                    if (Creature* clone = Unit::GetCreature(*me, uiCloneGUID))
                                        clone->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);
                                    break;
                                case 6:
                                    uiEventTimer = 7000;
                                    if (Creature* greymane = Unit::GetCreature(*me, uiGreymaneGUID))
                                    {
                                        DoScriptText(GREYMANE_SAY_QPB_3, player);
                                        greymane->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);
                                    }
                                    break;
                                case 7:
                                    player->ExitVehicle();
                                    break;
                            }
                }
                else
                    uiEventTimer -= diff;
            }
        }
    };
};

class spell_place_blessed_offerings : public SpellScriptLoader
{
    public:
        spell_place_blessed_offerings() : SpellScriptLoader("spell_place_blessed_offerings") { }

        class spell_place_blessed_offerings_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_place_blessed_offerings_SpellScript)

            void SummonOfferings(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                Unit* caster = GetCaster();

                if (!(caster && caster->GetTypeId() == TYPEID_PLAYER))
                    return;

                if (Creature* camera = caster->SummonCreature(NPC_GILNEAS_FUNERAL_CAMERA, -1647.91f, 1897.56f, 32.4459f, 1.0f))
                {
                    caster->CastSpell(caster, SPELL_FADE_TO_BLACK, true);
                    camera->SetSeerGUID(caster->GetGUID());
                    camera->SetVisible(false);
                }
            }

            void Register()
            {
                OnEffectLaunch += SpellEffectFn(spell_place_blessed_offerings_SpellScript::SummonOfferings, EFFECT_0, SPELL_EFFECT_TRANS_DOOR);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_place_blessed_offerings_SpellScript();
        }
};

enum eMenus
{
    MENU_MAIN                                = 50712,
    MENU_GATHERING_AND_MINING_PROFESSIONS    = 50713,
    MENU_CRAFTING_PROFESSIONS                = 50714,
    MENU_HERBALISM                           = 50716,
    MENU_MINING                              = 50718,
    MENU_SKINNING                            = 50720,
    MENU_ALCHEMY                             = 50715,
    MENU_BLACKSMITHING                       = 50719,
    MENU_ENCHANTING                          = 50725,
    MENU_ENGINERING                          = 50721,
    MENU_INSCRIPTION                         = 50717,
    MENU_JEWELCRAFTING                       = 50722,
    MENU_LEATHERWORKING                      = 50723,
    MENU_TAILORING                           = 50724,
};

#define    TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS    "–асскажи мне подробнее о професси€х, св€занных с собирательством и добычей ресурсов."
#define    TELL_ME_ABOUT_CRAFTING_PROFESSIONS                "–асскажи мне подробнее о ремесленных професси€х."
#define    TELL_ME_ABOUT_HERBALISM                           "–асскажи мне о травничестве."
#define    TELL_ME_ABOUT_MINING                              "–асскажи мне о горном деле."
#define    TELL_ME_ABOUT_SKINNING                            "–асскажи мне о сн€тии шкур."
#define    TELL_ME_ABOUT_ALCHEMY                             "–асскажи мне о алхимии."
#define    TELL_ME_ABOUT_BLACKSMITHING                       "–асскажи мне о кузнечном деле."
#define    TELL_ME_ABOUT_ENCHANTING                          "–асскажи мне о наложении чар."
#define    TELL_ME_ABOUT_ENGINERING                          "–асскажи мне о инженерном деле."
#define    TELL_ME_ABOUT_INSCRIPTION                         "–асскажи мне о начертании."
#define    TELL_ME_ABOUT_JEWELCRAFTING                       "–асскажи мне о ювелирном деле."
#define    TELL_ME_ABOUT_LEATHERWORKING                      "–асскажи мне о кожевничестве."
#define    TELL_ME_ABOUT_TAILORING                           "–асскажи мне о портн€жном деле."
#define    TRAIN_ME_ALCHEMY                                  "ќбучи мен€ алхимии."
#define    TRAIN_ME_HERBALISM                                "ќбучи мен€ травничеству."
#define    TRAIN_ME_INSCRIPTION                              "ќбучи мен€ начертанию."
#define    TRAIN_ME_MINING                                   "ќбучи мен€ горному делу."
#define    TRAIN_ME_BLACKSMITHING                            "ќбучи мен€ кузнечному делу."
#define    TRAIN_ME_SKINNING                                 "ќбучи мен€ сн€тию шкур."
#define    TRAIN_ME_ENGINERING                               "ќбучи мен€ инженерному делу."
#define    TRAIN_ME_JEWELCRAFTING                            "ќбучи мен€ ювелирному делу."
#define    TRAIN_ME_LEATHERWORKING                           "ќбучи мен€ кожевничеству."
#define    TRAIN_ME_TAILORING                                "ќбучи мен€ портн€жному делу."
#define    TRAIN_ME_ENCHANTING                               "ќбучи мен€ наложению чар."

class npc_jack_derrington : public CreatureScript
{
public:
    npc_jack_derrington() : CreatureScript("npc_jack_derrington") { }

    void SendTrainerList(Player* player, Creature* creature, uint32 uiReqSkill)
    {
        std::string  strTitle = player->GetSession()->GetTrinityString(LANG_NPC_TAINER_HELLO);;

        TrainerSpellData const* trainer_spells = creature->GetTrainerSpells();

        if (!trainer_spells)
            return;

        WorldPacket data(SMSG_TRAINER_LIST, 8 + 4 + 4 + 4 + trainer_spells->spellList.size() * 38 + strTitle.size() + 1);
        data << creature->GetGUID();
        data << uint32(trainer_spells->trainerType);
        data << uint32(1);

        size_t count_pos = data.wpos();
        data << uint32(trainer_spells->spellList.size());

        uint32 count = 0;

        for (TrainerSpellMap::const_iterator itr = trainer_spells->spellList.begin(); itr != trainer_spells->spellList.end(); ++itr)
        {
            TrainerSpell const* tSpell = &itr->second;

            TrainerSpellState state = player->GetTrainerSpellState(tSpell);

            if (tSpell->reqSkill != uiReqSkill)
                continue;

            data << uint32(tSpell->spell);
            data << uint8(state);
            data << uint32(tSpell->spellCost);

            data << uint8(tSpell->reqLevel);
            data << uint32(tSpell->reqSkill);
            data << uint32(tSpell->reqSkillValue);

            data << uint32(0);
            data << uint32(0);
            data << uint32(0);

            data << uint32(0);

            ++count;
        }

        data << strTitle;

        data.put<uint32>(count_pos,count);
        player->GetSession()->SendPacket(&data);

        return;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
        player->SEND_GOSSIP_MENU(MENU_MAIN, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_HERBALISM, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_MINING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_SKINNING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU(MENU_GATHERING_AND_MINING_PROFESSIONS, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_ALCHEMY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_BLACKSMITHING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_ENCHANTING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_ENGINERING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_INSCRIPTION, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_JEWELCRAFTING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_LEATHERWORKING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_TAILORING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(MENU_CRAFTING_PROFESSIONS, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, TRAIN_ME_HERBALISM, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + SKILL_HERBALISM);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_ALCHEMY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_INSCRIPTION, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU(MENU_HERBALISM, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, TRAIN_ME_MINING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + SKILL_MINING);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_BLACKSMITHING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_ENGINERING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_JEWELCRAFTING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU(MENU_MINING, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, TRAIN_ME_SKINNING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + SKILL_SKINNING);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_LEATHERWORKING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU(MENU_SKINNING, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, TRAIN_ME_ALCHEMY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + SKILL_ALCHEMY);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_HERBALISM, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_INSCRIPTION, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU(MENU_ALCHEMY, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, TRAIN_ME_BLACKSMITHING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + SKILL_BLACKSMITHING);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_MINING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU(MENU_BLACKSMITHING, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, TRAIN_ME_ENCHANTING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + SKILL_ENCHANTING);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_TAILORING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU(MENU_ENCHANTING, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, TRAIN_ME_ENGINERING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + SKILL_ENGINEERING);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_MINING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU(MENU_ENGINERING, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, TRAIN_ME_INSCRIPTION, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + SKILL_INSCRIPTION);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_HERBALISM, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU(MENU_INSCRIPTION, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, TRAIN_ME_JEWELCRAFTING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + SKILL_JEWELCRAFTING);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_MINING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU(MENU_JEWELCRAFTING, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 12:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, TRAIN_ME_LEATHERWORKING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + SKILL_LEATHERWORKING);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_SKINNING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                   player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU(MENU_LEATHERWORKING, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 13:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, TRAIN_ME_TAILORING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + SKILL_TAILORING);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_ENCHANTING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
                   player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_GATHERING_AND_MINING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELL_ME_ABOUT_CRAFTING_PROFESSIONS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU(MENU_TAILORING, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + SKILL_HERBALISM:
                SendTrainerList(player, creature, SKILL_HERBALISM);
                break;
            case GOSSIP_ACTION_INFO_DEF + SKILL_ALCHEMY:
                SendTrainerList(player, creature, SKILL_ALCHEMY);
                break;
            case GOSSIP_ACTION_INFO_DEF + SKILL_INSCRIPTION:
                SendTrainerList(player, creature, SKILL_INSCRIPTION);
                break;
            case GOSSIP_ACTION_INFO_DEF + SKILL_MINING:
                SendTrainerList(player, creature, SKILL_MINING);
                break;
            case GOSSIP_ACTION_INFO_DEF + SKILL_BLACKSMITHING:
                SendTrainerList(player, creature, SKILL_BLACKSMITHING);
                break;
            case GOSSIP_ACTION_INFO_DEF + SKILL_SKINNING:
                SendTrainerList(player, creature, SKILL_SKINNING);
                break;
            case GOSSIP_ACTION_INFO_DEF + SKILL_ENGINEERING:
                SendTrainerList(player, creature, SKILL_ENGINEERING);
                break;
            case GOSSIP_ACTION_INFO_DEF + SKILL_JEWELCRAFTING:
                SendTrainerList(player, creature, SKILL_JEWELCRAFTING);
                break;
            case GOSSIP_ACTION_INFO_DEF + SKILL_LEATHERWORKING:
                SendTrainerList(player, creature, SKILL_LEATHERWORKING);
                break;
            case GOSSIP_ACTION_INFO_DEF + SKILL_TAILORING:
                SendTrainerList(player, creature, SKILL_TAILORING);
                break;
            case GOSSIP_ACTION_INFO_DEF + SKILL_ENCHANTING:
                SendTrainerList(player, creature, SKILL_ENCHANTING);
                break;
        }

        return true;
    }
};

class npc_prince_liam_greymane_dh : public CreatureScript
{
public:
    npc_prince_liam_greymane_dh() : CreatureScript("npc_prince_liam_greymane_dh") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_prince_liam_greymane_dhAI (creature);
    }

    struct npc_prince_liam_greymane_dhAI : public ScriptedAI
    {
        npc_prince_liam_greymane_dhAI(Creature* creature) : ScriptedAI(creature)
        {
            SetCombatMovement(false);
        }

        uint32 uiShootTimer;
        bool miss;

        void Reset()
        {
            uiShootTimer = 1000;
            miss = false;

            if (Unit* target = me->FindNearestCreature(NPC_FORSAKEN_INVADER, 40.0f))
                AttackStart(target);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (me->GetVictim()->GetTypeId() == TYPEID_UNIT)
            {
                if (me->GetVictim()->GetHealthPct() < 90)
                    miss = true;
                else
                    miss = false;
            }

            if (uiShootTimer <= diff)
            {
                uiShootTimer = 1500;

                if (!me->IsWithinMeleeRange(me->GetVictim(), 0.0f))
                    if (Unit* target = me->FindNearestCreature(NPC_FORSAKEN_INVADER, 40.0f))
                        if (target != me->GetVictim())
                        {
                            me->getThreatManager().modifyThreatPercent(me->GetVictim(), -100);
                            me->CombatStart(target);
                            me->AddThreat(target, 1000);
                        }

                if (!me->IsWithinMeleeRange(me->GetVictim(), 0.0f))
                {
                    if (me->HasUnitState(UNIT_STATE_MELEE_ATTACKING))
                    {
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                        me->ClearUnitState(UNIT_STATE_MELEE_ATTACKING);
                        me->SendMeleeAttackStop(me->GetVictim());
                    }

                    me->CastSpell(me->GetVictim(), SPELL_SHOOT, false);
                }
                else
                    if (!me->HasUnitState(UNIT_STATE_MELEE_ATTACKING))
                    {
                        me->AddUnitState(UNIT_STATE_MELEE_ATTACKING);
                        me->SendMeleeAttackStart(me->GetVictim());
                    }
            }
            else
                uiShootTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

class npc_duskhaven_watchman : public CreatureScript
{
public:
    npc_duskhaven_watchman() : CreatureScript("npc_duskhaven_watchman") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_duskhaven_watchmanAI (creature);
    }

    struct npc_duskhaven_watchmanAI : public ScriptedAI
    {
        npc_duskhaven_watchmanAI(Creature* creature) : ScriptedAI(creature)
        {
            SetCombatMovement(false);
        }

        uint32 uiShootTimer;
        uint32 uiFindEnemyTimer;
        bool miss;

        void Reset()
        {
            uiShootTimer = 1000;
            uiFindEnemyTimer = 1500;
            miss = false;

            if (Unit* target = me->FindNearestCreature(NPC_FORSAKEN_INVADER, 40.0f))
            {
                AttackStart(target);
                return;
            }

            if (Unit* target = me->FindNearestCreature(NPC_FORSAKEN_FOOTSOLDIER, 40.0f))
                AttackStart(target);
        }

        void FindEnemy()
        {
            Creature* target = NULL;

            if (Creature* target = me->FindNearestCreature(NPC_FORSAKEN_FOOTSOLDIER, 40.0f))
            {
                if (target != me->GetVictim())
                {
                    if (me->GetVictim())
                    {
                        if (target == me->GetVictim())
                            return;

                        me->getThreatManager().modifyThreatPercent(me->GetVictim(), -100);
                    }

                    me->AddThreat(target, 1000);
                    target->SetInCombatWith(me);
                    me->SetInCombatWith(target);
                }

                return;
            }

            std::list<Creature*> EnemyList;
            me->GetCreatureListWithEntryInGrid(EnemyList, NPC_FORSAKEN_INVADER, 50.0f);

            if (EnemyList.empty())
                return;

            float curr_dist = 100500;

            for (std::list<Creature*>::const_iterator itr = EnemyList.begin(); itr != EnemyList.end(); ++itr)
            {
                if ((*itr)->IsInCombat())
                    continue;

                if (!(*itr)->IsAlive())
                    continue;

                if (!(*itr)->IsWithinLOSInMap(me))
                    continue;

                if (!(*itr)->isInAccessiblePlaceFor(me))
                    continue;

                float dist = me->GetDistance2d((*itr));

                if (dist < curr_dist)
                {
                    curr_dist = dist;
                    target = (*itr);
                }
            }

            if (target)
            {
                if (me->GetVictim())
                {
                    if (target == me->GetVictim())
                        return;

                    me->getThreatManager().modifyThreatPercent(me->GetVictim(), -100);
                }

                target->SetInCombatWith(me);
                me->SetInCombatWith(target);
                target->AddThreat(me, 100500.0f);
                me->AddThreat(target, 100500.0f);
                float x, y, z;
                float t_x, t_y;
                target->GetPosition(t_x, t_y);
                me->GetNearPoint(me, x, y, z, me->GetObjectSize(), 0.0f, me->GetAngle(t_x, t_y));
                float currentGroundLevel = me->GetBaseMap()->GetHeight(x, y, MAX_HEIGHT);
                me->GetAngle(x, y);

                if (z > currentGroundLevel)
                    z = currentGroundLevel;

                target->GetMotionMaster()->MoveCharge(x, y, z);
                return;
            }

            return;
        }

        void UpdateAI(const uint32 diff)
        {
            if (uiFindEnemyTimer <= diff)
            {
                uiFindEnemyTimer = 10000;

                if (me->GetVictim())
                    if (me->IsWithinMeleeRange(me->GetVictim(), 0.0f))
                        return;

                FindEnemy();
            }
            else
                uiFindEnemyTimer -= diff;

            if (!UpdateVictim())
                return;

            if (me->GetVictim()->GetTypeId() == TYPEID_UNIT)
            {
                if (me->GetVictim()->GetHealthPct() < 90)
                    miss = true;
                else
                    miss = false;
            }

            if (uiShootTimer <= diff)
            {
                uiShootTimer = 1500;

                if (!me->IsWithinMeleeRange(me->GetVictim(), 0.0f))
                {
                    if (me->HasUnitState(UNIT_STATE_MELEE_ATTACKING))
                    {
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                        me->ClearUnitState(UNIT_STATE_MELEE_ATTACKING);
                        me->SendMeleeAttackStop(me->GetVictim());
                    }

                    me->CastSpell(me->GetVictim(), SPELL_SHOOT, false);
                }
                else
                    if (!me->HasUnitState(UNIT_STATE_MELEE_ATTACKING))
                    {
                        me->AddUnitState(UNIT_STATE_MELEE_ATTACKING);
                        me->SendMeleeAttackStart(me->GetVictim());
                    }
            }
            else
                uiShootTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

class npc_forsaken_invader : public CreatureScript
{
public:
    npc_forsaken_invader() : CreatureScript("npc_forsaken_invader") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_forsaken_invaderAI (creature);
    }

    struct npc_forsaken_invaderAI : public ScriptedAI
    {
        npc_forsaken_invaderAI(Creature* creature) : ScriptedAI(creature)
        {
            miss = false;
            me->_ReactDistance = 20.0f;
        }

        bool miss;

        void DamageTaken(Unit* attacker, uint32 &/*damage*/)
        {
            if (attacker->GetTypeId() != TYPEID_PLAYER)
                return;

            Unit* victim = NULL;

            if (Unit* victim = me->GetVictim())
                if (victim->GetTypeId() == TYPEID_PLAYER)
                    return;

            if (victim)
                me->getThreatManager().modifyThreatPercent(victim, -100);

            AttackStart(attacker);
            me->AddThreat(attacker, 10005000);
        }

        void UpdateAI(const uint32 /*diff*/)
        {
            if (!UpdateVictim())
                return;

            if (me->GetVictim()->GetTypeId() == TYPEID_UNIT)
            {
                if (me->GetVictim()->GetHealthPct() < 90)
                    miss = true;
                else
                    miss = false;
            }

            DoMeleeAttackIfReady();
        }
    };
};

///////////
// Quest Leader of the Pack 14386
///////////

enum eLOTP
{
    NPC_DARK_RANGER_THYALA     = 36312,
    NPC_ATTACK_MASTIFF         = 36409,

    SPELL_SHOOT_LOTP           = 16100,
    SPELL_KNOCKBACK_LOTP       = 68683,
    SPELL_DEMORALIZING_ROAR    = 15971,
    SPELL_LEAP                 = 68687,
    SPELL_TAUNT_LOTP           = 26281,

    ACTION_DESPAWN             = 7,
};

class npc_dark_ranger_thyala : public CreatureScript
{
public:
    npc_dark_ranger_thyala() : CreatureScript("npc_dark_ranger_thyala") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_dark_ranger_thyalaAI (creature);
    }

    struct npc_dark_ranger_thyalaAI : public ScriptedAI
    {
        npc_dark_ranger_thyalaAI(Creature* creature) : ScriptedAI(creature)
        {
            SetCombatMovement(false);
        }

        std::list<Player*> lPlayers;
        uint32 uiShootTimer;
        uint32 uiKnockbackTimer;

        void Reset()
        {
            uiShootTimer = 500;
            uiKnockbackTimer = urand(2000, 5000);
        }

        void DamageTaken(Unit* /*attacker*/, uint32 &damage)
        {
            if (me->GetHealth() > damage)
                return;

            ThreatContainer::StorageType const & ThreatList = me->getThreatManager().getThreatList();

            if (!ThreatList.empty())
                for (ThreatContainer::StorageType::const_iterator itr = ThreatList.begin(); itr != ThreatList.end(); ++itr)
                    if (Unit* target = Unit::GetUnit(*me, (*itr)->getUnitGuid()))
                        if (Player* player = target->ToPlayer())
                            player->KilledMonsterCredit(NPC_DARK_RANGER_THYALA, 0);
        }

        void JustDied(Unit* /*who*/)
        {
            std::list<Creature*> lMastiffs;
            me->GetCreatureListWithEntryInGrid(lMastiffs, NPC_ATTACK_MASTIFF, 50.0f);

            if (!lMastiffs.empty())
                for (std::list<Creature*>::const_iterator itr = lMastiffs.begin(); itr != lMastiffs.end(); ++itr)
                    if ((*itr)->IsAlive())
                    {
                        (*itr)->SetReactState(REACT_PASSIVE);
                        (*itr)->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        (*itr)->CombatStop();
                        (*itr)->GetMotionMaster()->MoveTargetedHome();
                        (*itr)->DespawnOrUnsummon(3000);
                    }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (uiShootTimer <= diff)
            {
                uiShootTimer = 1000;
                DoCast(me->GetVictim(), SPELL_SHOOT_LOTP);
            }
            else
                uiShootTimer -= diff;

            if (uiKnockbackTimer <= diff)
            {
                uiKnockbackTimer = urand(1000, 5000);
                DoCast(SPELL_KNOCKBACK_LOTP);
            }
            else
                uiKnockbackTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

class npc_attack_mastiff : public CreatureScript
{
public:
    npc_attack_mastiff() : CreatureScript("npc_attack_mastiff") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_attack_mastiffAI (creature);
    }

    struct npc_attack_mastiffAI : public ScriptedAI
    {
        npc_attack_mastiffAI(Creature* creature) : ScriptedAI(creature){}

        uint32 uiDemoralizingRoarTimer;
        uint32 uiLeapTimer;
        uint32 uiTaunt;

        void Reset()
        {
            uiDemoralizingRoarTimer = 2000;
            uiLeapTimer = 1000;
            uiTaunt = 1000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (uiDemoralizingRoarTimer <= diff)
            {
                uiDemoralizingRoarTimer = urand(5000, 15000);
                DoCast(SPELL_DEMORALIZING_ROAR);
            }
            else
                uiDemoralizingRoarTimer -= diff;

            if (uiLeapTimer <= diff)
            {
                uiLeapTimer = 1000;
                DoCast(me->GetVictim(), SPELL_LEAP);
            }
            else
                uiLeapTimer -= diff;

            if (uiTaunt <= diff)
            {
                uiTaunt = 1000;
                DoCast(me->GetVictim(), SPELL_TAUNT_LOTP);
            }
            else
                uiTaunt -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

class spell_call_attack_mastiffs : public SpellScriptLoader
{
    public:
        spell_call_attack_mastiffs() : SpellScriptLoader("spell_call_attack_mastiffs") { }

        class spell_call_attack_mastiffs_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_call_attack_mastiffs_SpellScript)

            void SummonMastiffs(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);

                Unit* caster = GetCaster();

                if (!caster)
                    return;

                if (Creature* thyala = caster->FindNearestCreature(NPC_DARK_RANGER_THYALA, 30.0f))
                {
                    float angle = thyala->GetHomePosition().GetOrientation();

                    for (int i = 0; i < 12; ++i)
                    {
                        float x, y, z;
                        uint32 DistRoll = urand(30, 50);
                        int RadRoll = irand(-45, 45);
                        thyala->GetNearPoint(thyala, x, y, z, 0, 0.0f + DistRoll, angle + RadRoll * M_PI / 180);
                        float currentGroundLevel = thyala->GetBaseMap()->GetHeight(x, y, MAX_HEIGHT);
                        float curr_angle = thyala->GetAngle(x, y);

                        if (z > currentGroundLevel)
                            z = currentGroundLevel;

                        if (Creature* mastiff = caster->SummonCreature(NPC_ATTACK_MASTIFF, x, y, z, curr_angle))
                        {
                            mastiff->CombatStart(thyala, true);
                            thyala->CombatStart(mastiff, true);
                            mastiff->AddThreat(thyala, 100500);
                            float x, y, z;
                            thyala->GetPosition(x, y, z);
                            mastiff->GetMotionMaster()->MoveCharge(x, y, z);
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_call_attack_mastiffs_SpellScript::SummonMastiffs, EFFECT_2, SPELL_EFFECT_SUMMON);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_call_attack_mastiffs_SpellScript();
        }
};

/////////
//  Hayward Brothers
////////

enum eHB
{
    NPC_FORSAKEN_CASTAWAY    = 36488,
};

class npc_hayward_brother : public CreatureScript
{
public:
    npc_hayward_brother() : CreatureScript("npc_hayward_brother") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hayward_brotherAI (creature);
    }

    struct npc_hayward_brotherAI : public ScriptedAI
    {
        npc_hayward_brotherAI(Creature* creature) : ScriptedAI(creature)
        {
            SetCombatMovement(false);
        }

        uint64 uiPrevTargetGUID;
        uint32 uiFindEnemyTimer;
        bool miss;

        void Reset()
        {
            uiPrevTargetGUID = 0;
            uiFindEnemyTimer = 1500;
            miss = false;

            if (Unit* target = me->FindNearestCreature(NPC_FORSAKEN_CASTAWAY, 40.0f))
                AttackStart(target);
        }

        void FindEnemy()
        {
            std::list<Creature*> EnemyList;
            me->GetCreatureListWithEntryInGrid(EnemyList, NPC_FORSAKEN_CASTAWAY, 50.0f);

            if (EnemyList.empty())
                return;

            Creature* target = NULL;
            float curr_dist = 100500;

            for (std::list<Creature*>::const_iterator itr = EnemyList.begin(); itr != EnemyList.end(); ++itr)
            {
                if ((*itr)->IsInCombat())
                    continue;

                if (!(*itr)->IsAlive())
                    continue;

                if (!(*itr)->IsWithinLOSInMap(me))
                    continue;

                if (!(*itr)->isInAccessiblePlaceFor(me))
                    continue;

                float dist = me->GetDistance2d((*itr));

                if (dist < curr_dist)
                {
                    curr_dist = dist;
                    target = (*itr);
                }
            }

            if (target)
            {
                if (me->GetVictim())
                {
                    if (target == me->GetVictim())
                        return;

                    me->getThreatManager().modifyThreatPercent(me->GetVictim(), -100);
                }

                target->SetInCombatWith(me);
                me->SetInCombatWith(target);
                target->AddThreat(me, 100500.0f);
                me->AddThreat(target, 100500.0f);
                float x, y, z;
                float t_x, t_y;
                target->GetPosition(t_x, t_y);
                me->GetNearPoint(me, x, y, z, me->GetObjectSize(), 0.0f, me->GetAngle(t_x, t_y));
                float currentGroundLevel = me->GetBaseMap()->GetHeight(x, y, MAX_HEIGHT);
                me->GetAngle(x, y);

                if (z > currentGroundLevel)
                    z = currentGroundLevel;

                uint32 uiTargetGUID = target->GetGUID();

                if (uiPrevTargetGUID == uiTargetGUID)
                {
                    target->GetMotionMaster()->MoveJump(x, y, z, 10, 10);
                    target->Relocate(x, y, z);
                    uiPrevTargetGUID = 0;
                    return;
                }

                uiPrevTargetGUID = uiTargetGUID;
                target->GetMotionMaster()->MoveCharge(x, y, z);
                return;
            }

            return;
        }

        void UpdateAI(const uint32 diff)
        {
            if (uiFindEnemyTimer <= diff)
            {
                uiFindEnemyTimer = 10000;

                if (me->GetVictim())
                    if (me->IsWithinMeleeRange(me->GetVictim(), 0.0f))
                        return;

                FindEnemy();
            }
            else
                uiFindEnemyTimer -= diff;

            if (!UpdateVictim())
                return;

            if (me->GetVictim())
                if (me->GetVictim()->GetTypeId() == TYPEID_UNIT)
                {
                    if (me->GetVictim()->GetHealthPct() < 90)
                        miss = true;
                    else
                        miss = false;
                }

            DoMeleeAttackIfReady();
        }
    };
};

/////////
//  Forsaken Catapult
////////
#define SPELL_PLAGUE_BARREL_LAUNCH    71804

const float CataCastPos[5][3]=
{
    {-1274.92f, 1632.53f, 12.775f},
    {-1260.25f, 1580.49f, 20.574f},
    {-1256.74f, 1683.23f, 18.304f},
    {-1285.08f, 1708.93f, 9.4898f},
    {-1291.34f, 1721.51f, 10.621f},
};

class npc_forsaken_catapult_sti : public CreatureScript
{
public:
    npc_forsaken_catapult_sti() : CreatureScript("npc_forsaken_catapult_sti") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_forsaken_catapult_stiAI (creature);
    }

    struct npc_forsaken_catapult_stiAI : public ScriptedAI
    {
        npc_forsaken_catapult_stiAI(Creature* creature) : ScriptedAI(creature)
        {
            CanCast = false;

            for (int i = 0; i < 5; ++i)
                if (me->GetDistance(CataCastPos[i][0], CataCastPos[i][1], CataCastPos[i][2]) < 15.0f)
                {
                    CanCast = true;
                    me->setActive(true);
                }
        }

        uint32 uiCastTimer;
        bool CanCast;

        void Reset()
        {
            uiCastTimer = 500;
        }

        void UpdateAI(const uint32 diff)
        {
            if (CanCast)
            {
                if (uiCastTimer <= diff)
                {
                    uiCastTimer = urand(2000, 7000);
                    float x, y, z;
                    me->GetNearPoint2D(x, y, urand(100, 150), me->GetOrientation());
                    z = me->GetBaseMap()->GetHeight(x, y, MAX_HEIGHT);
                    me->CastSpell(x, y, z, SPELL_PLAGUE_BARREL_LAUNCH, false);
                }
                else
                    uiCastTimer -= diff;
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

///////////
// Quest Knee-Deep 24678
///////////

#define SPELL_SWING_TORCH    70631

class npc_knee_deep_attacker : public CreatureScript
{
public:
    npc_knee_deep_attacker() : CreatureScript("npc_knee_deep_attacker") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_knee_deep_attackerAI (creature);
    }

    struct npc_knee_deep_attackerAI : public ScriptedAI
    {
        npc_knee_deep_attackerAI(Creature* creature) : ScriptedAI(creature)
        {
            CanAttackTimer = 0;
        }

        uint32 CanAttackTimer;

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_SWING_TORCH)
            {
                float x, y, z;
                me->GetNearPoint2D(x, y, urand(5, 10), me->GetAngle(caster->GetPositionX(), caster->GetPositionY()) + M_PI);
                z = me->GetPositionZ();
                me->GetMotionMaster()->MoveCharge(x, y, z);
                CanAttackTimer = 5000;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (CanAttackTimer <= diff)
                DoMeleeAttackIfReady();
            else
                CanAttackTimer -= diff;
        }
    };
};

class npc_gilneas_tremors_credit : public CreatureScript
{
public:
    npc_gilneas_tremors_credit() : CreatureScript("npc_gilneas_tremors_credit") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gilneas_tremors_creditAI (creature);
    }

    struct npc_gilneas_tremors_creditAI : public ScriptedAI
    {
        npc_gilneas_tremors_creditAI(Creature* creature) : ScriptedAI(creature)
        {
            me->setActive(true);
            uiTremorTimerFirst = urand(30000, 150000);
            uiTremorTimerSecond = urand(20000, 100000);
            uiTremorTimerThird = urand(10000, 50000);
        }

        uint32 uiTremorTimerFirst;
        uint32 uiTremorTimerSecond;
        uint32 uiTremorTimerThird;

        void Tremor(uint32 uiPhase, uint32 uiSpellId)
        {
            Map::PlayerList const &PlList = me->GetMap()->GetPlayers();

            if (PlList.isEmpty())
                return;

            for (Map::PlayerList::const_iterator i = PlList.begin(); i != PlList.end(); ++i)
                if (Player* player = i->GetSource())
                    if (uiPhase & player->GetPhaseMask())
                        player->CastSpell(player, uiSpellId, false);
        }

        void UpdateAI(const uint32 diff)
        {
            if (uiTremorTimerFirst <= diff)
            {
                uiTremorTimerFirst = urand(30000, 150000);
                Tremor(4096, SPELL_CATACLYSM_TYPE_1);
            }
            else
                uiTremorTimerFirst -= diff;

            if (uiTremorTimerSecond <= diff)
            {
                uiTremorTimerSecond = urand(20000, 100000);
                Tremor(8192, SPELL_CATACLYSM_TYPE_2);
            }
            else
                uiTremorTimerSecond -= diff;

            if (uiTremorTimerThird <= diff)
            {
                uiTremorTimerThird = urand(10000, 50000);
                Tremor(16384, SPELL_CATACLYSM_TYPE_3);
            }
            else
                uiTremorTimerThird -= diff;
        }
    };
};

////////
// Class Trainers
///////

enum eCT
{
    QUEST_STEADY_SHOT                = 14276,
    QUEST_IMMOLATE                   = 14274,
    QUEST_EVISCERATE                 = 14272,
    QUEST_FLASH_HEAL                 = 14279,
    QUEST_A_REJUVENATING_TOUCH       = 14283,
    QUEST_ARCANE_MISSILES            = 14281,
    QUEST_CHARGE                     = 14266,

    MENU_HUNTSMAN_BLAKE              = 50726,
    MENU_VITUS_DARKWALKER            = 50728,
    MENU_LOREN_THE_FENCE             = 50730,
    MENU_SISTER_ALMYRA               = 50732,
    MENU_CELESTINE_OF_THE_HARVES     = 50734,
    MENU_MYRIAM_SPELLWAKER           = 50736,
    MENU_SERGEANT_CLEESE             = 50738,

    HUNTSMAN_BLAKE_SAY_1             = -1977165,
    HUNTSMAN_BLAKE_SAY_2             = -1977166,
    VITUS_DARKWALKER_SAY_1           = -1977167,
    VITUS_DARKWALKER_SAY_2           = -1977168,
    LOREN_THE_FENCE_SAY_1            = -1977169,
    LOREN_THE_FENCE_SAY_2            = -1977170,
    SISTER_ALMYRA_SAY_1              = -1977171,
    SISTER_ALMYRA_SAY_2              = -1977172,
    CELESTINE_OF_THE_HARVES_SAY_1    = -1977173,
    CELESTINE_OF_THE_HARVES_SAY_2    = -1977174,
    MYRIAM_SPELLWAKER_SAY_1          = -1977175,
    MYRIAM_SPELLWAKER_SAY_2          = -1977176,
    SERGEANT_CLEESE_SAY_1            = -1977177,
    SERGEANT_CLEESE_SAY_2            = -1977178,

    SPELL_FROSTBOLT_NO_DAMAGE        = 74277,
};

class npc_huntsman_blake : public CreatureScript
{
public:
    npc_huntsman_blake() : CreatureScript("npc_huntsman_blake") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->getClass() != CLASS_HUNTER)
        {
            player->SEND_GOSSIP_MENU(MENU_HUNTSMAN_BLAKE, creature->GetGUID());
            return true;
        }

        return false;
    }

    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_STEADY_SHOT)
            DoScriptText(HUNTSMAN_BLAKE_SAY_1, player);

        return true;
    }

    bool OnQuestComplete(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_STEADY_SHOT)
            DoScriptText(HUNTSMAN_BLAKE_SAY_2, player);

        return true;
    }
};

class npc_vitus_darkwalker : public CreatureScript
{
public:
    npc_vitus_darkwalker() : CreatureScript("npc_vitus_darkwalker") { }

    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_IMMOLATE)
            DoScriptText(VITUS_DARKWALKER_SAY_1, player);

        return true;
    }

    bool OnQuestComplete(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_IMMOLATE)
            DoScriptText(VITUS_DARKWALKER_SAY_2, player);

        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->getClass() != CLASS_WARLOCK)
        {
            player->SEND_GOSSIP_MENU(MENU_VITUS_DARKWALKER, creature->GetGUID());
            return true;
        }

        return false;
    }
};

class npc_loren_the_fence : public CreatureScript
{
public:
    npc_loren_the_fence() : CreatureScript("npc_loren_the_fence") { }

    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_EVISCERATE)
            DoScriptText(LOREN_THE_FENCE_SAY_1, player);

        return true;
    }

    bool OnQuestComplete(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_EVISCERATE)
            DoScriptText(LOREN_THE_FENCE_SAY_2, player);

        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->getClass() != CLASS_ROGUE)
        {
            player->SEND_GOSSIP_MENU(MENU_LOREN_THE_FENCE, creature->GetGUID());
            return true;
        }

        return false;
    }
};

class npc_sister_almyra : public CreatureScript
{
public:
    npc_sister_almyra() : CreatureScript("npc_sister_almyra") { }

    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_FLASH_HEAL)
            DoScriptText(SISTER_ALMYRA_SAY_1, player);

        return true;
    }

    bool OnQuestComplete(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_FLASH_HEAL)
            DoScriptText(SISTER_ALMYRA_SAY_2, player);

        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->getClass() != CLASS_PRIEST)
        {
            player->SEND_GOSSIP_MENU(MENU_SISTER_ALMYRA, creature->GetGUID());
            return true;
        }

        return false;
    }
};

class npc_celestine_of_the_harves : public CreatureScript
{
public:
    npc_celestine_of_the_harves() : CreatureScript("npc_celestine_of_the_harves") { }

    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_A_REJUVENATING_TOUCH)
            DoScriptText(CELESTINE_OF_THE_HARVES_SAY_1, player);

        return true;
    }

    bool OnQuestComplete(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_A_REJUVENATING_TOUCH)
            DoScriptText(CELESTINE_OF_THE_HARVES_SAY_2, player);

        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->getClass() != CLASS_DRUID)
        {
            player->SEND_GOSSIP_MENU(MENU_CELESTINE_OF_THE_HARVES, creature->GetGUID());
            return true;
        }

        return false;
    }
};

class npc_myriam_spellwaker : public CreatureScript
{
public:
    npc_myriam_spellwaker() : CreatureScript("npc_myriam_spellwaker") { }

    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_ARCANE_MISSILES)
            DoScriptText(MYRIAM_SPELLWAKER_SAY_1, player);

        return true;
    }

    bool OnQuestComplete(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_ARCANE_MISSILES)
            DoScriptText(MYRIAM_SPELLWAKER_SAY_2, player);

        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->getClass() != CLASS_MAGE)
        {
            player->SEND_GOSSIP_MENU(MENU_MYRIAM_SPELLWAKER, creature->GetGUID());
            return true;
        }

        return false;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_myriam_spellwakerAI (creature);
    }

    struct npc_myriam_spellwakerAI : public ScriptedAI
    {
        npc_myriam_spellwakerAI(Creature* creature) : ScriptedAI(creature)
        {
            uiBoltTimer = 2000;
            SetCombatMovement(false);
        }

        uint32 uiBoltTimer;

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (uiBoltTimer <= diff)
            {
                uiBoltTimer = 2000;
                DoCast(me->GetVictim(), SPELL_FROSTBOLT_NO_DAMAGE);
            }
            else
                uiBoltTimer -= diff;
        }
    };
};

class npc_sergeant_cleese : public CreatureScript
{
public:
    npc_sergeant_cleese() : CreatureScript("npc_sergeant_cleese") { }

    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_CHARGE)
            DoScriptText(SERGEANT_CLEESE_SAY_1, player);

        return true;
    }

    bool OnQuestComplete(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_CHARGE)
            DoScriptText(SERGEANT_CLEESE_SAY_2, player);

        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->getClass() != CLASS_WARRIOR)
        {
            player->SEND_GOSSIP_MENU(MENU_SERGEANT_CLEESE, creature->GetGUID());
            return true;
        }

        return false;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_sergeant_cleeseAI (creature);
    }

    struct npc_sergeant_cleeseAI : public ScriptedAI
    {
        npc_sergeant_cleeseAI(Creature* creature) : ScriptedAI(creature)
        {
            miss = false;
            me->_ReactDistance = 20.0f;
        }

        bool miss;

        void UpdateAI(const uint32 /*diff*/)
        {
            if (!UpdateVictim())
                return;

            if (me->GetVictim()->GetTypeId() == TYPEID_UNIT)
            {
                if (me->GetVictim()->GetHealthPct() < 90)
                    miss = true;
                else
                    miss = false;
            }

            DoMeleeAttackIfReady();
        }
    };
};

class npc_admiral_nightwind : public CreatureScript
{
public:
    npc_admiral_nightwind() : CreatureScript("npc_admiral_nightwind") { }

    bool OnQuestComplete(Player* player, Creature* /*creature*/, Quest const* quest)
    {
        if (quest->GetQuestId() == 14434)
        {
            player->RemoveAllAuras();
            WorldLocation loc;
            loc.m_mapId       = 1;
            loc.m_positionX   = 8181.06f;
            loc.m_positionY   = 1001.92f;
            loc.m_positionZ   = 7.0589f;
            player->TeleportTo(loc);
            player->SetHomebind(loc, 702);
            player->SaveToDB();
        }
        return true;
    }
};

void AddSC_gilneas()
{
    new npc_gilneas_city_guard_gate();
    new npc_panicked_citizen_gate();
    new npc_gilnean_crow();
    new npc_prince_liam_greymane_intro();
    new npc_lieutenant_walden();
    new npc_prince_liam_greymane_phase_1();
    new npc_rampaging_worgen();
    new npc_gilneas_city_guard();
    new npc_king_genn_greymane_qod();
    new npc_qems_citizen();
    new npc_qems_worgen();
    new npc_worgen_attacker();
    new npc_lord_darius_crowley();
    new npc_josiah_avery_worgen();
    new npc_josiah_avery_human();
    new npc_lorna_crowley_qfs();
    new npc_gilneas_mastiff();
    new npc_bloodfang_lurker();
    new npc_king_genn_greymane();
    new npc_cannon_camera();
    new npc_lord_godfrey_qska();
    new npc_saved_aranas();
    new npc_vehicle_genn_horse();
    new npc_king_genn_greymane_qtr();
    new npc_crowley_horse();
    new npc_bloodfang_stalker();
    new npc_crowley_horse_second_round();
    new npc_lord_darius_crowley_qls();
    new npc_king_genn_greymane_qls();
    new npc_krennan_aranas_qls();
    new npc_slain_watchman();
    new npc_horrid_abomination();
    new npc_forsaken_catapult_qtbs();
    new npc_james();
    new npc_ashley();
    new npc_cynthia();
    new npc_drowning_watchman();
    new npc_prince_liam_greymane();
    new npc_chance_the_cat();
    new npc_lucius_the_cruel();
    new npc_wahl();
    new npc_mountain_horse_vehicle();
    new npc_mountain_horse_follower();
    new npc_swift_mountain_horse();
    new npc_gwen_armstead();
    new npc_king_genn_greymane_c3();
    new npc_stagecoach_harness_summoner();
    new npc_stagecoach_harness();
    new npc_crash_survivor();
    new npc_swamp_crocolisk();
    new npc_koroth_the_hillbreaker_qiao_friend();
    new npc_captain_asther_qiao();
    new npc_prince_liam_greymane_qiao();
    new npc_koroth_the_hillbreaker_qiao();
    new npc_koroth_the_hillbreaker();
    new npc_dark_scout_summoner();
    new npc_dark_scout();
    new npc_lord_darius_crowley_qaod();
    new npc_tobias_mistmantle_qaod();
    new npc_taldoren_tracker();
    new npc_tobias_mistmantle_qtbwo();
    new npc_lord_godfrey_qnhnb();
    new npc_lorna_crowley_qnhnb();
    new npc_king_genn_greymane_qnhnb();
    new npc_krennan_aranas_qbatr();
    new npc_lord_godfrey_qbatr();
    new npc_king_genn_greymane_qbatr();
    new npc_prince_liam_greymane_tbfgc();
    new npc_gilnean_militia_tbfgc();
    new npc_myriam_spellwaker_tbfgc();
    new npc_sister_almyra_tbfgc();
    new npc_dark_ranger_elite_tbfgc();
    new npc_emberstone_cannon();
    new npc_lorna_crowley_tbfgc();
    new npc_lord_darius_crowley_tbfgc();
    new worgen_warrior_tbfgc();
    new npc_gorerot();
    new npc_king_genn_greymane_tbfgc();
    new npc_lady_sylvanas_windrunner_tbfgc();
    new npc_damaged_catapult_tbfgc();
    new npc_lorna_crowley();
    new npc_krennan_aranas_tbfgc();
    new npc_lorna_crowley_qthfs();
    new npc_tobias_mistmantle_qthfs();
    new npc_lady_sylvanas_qthfs();
    new npc_general_warhowl_qthfs();
    new npc_high_executor_crenshaw_qthfs();
    new npc_captured_riding_bat();
    new npc_gilneas_funeral_camera();
    new npc_jack_derrington();
    new npc_prince_liam_greymane_dh();
    new npc_duskhaven_watchman();
    new npc_forsaken_invader();
    new npc_dark_ranger_thyala();
    new npc_attack_mastiff();
    new npc_hayward_brother();
    new npc_forsaken_catapult_sti();
    new npc_knee_deep_attacker();
    new npc_gilneas_tremors_credit();
    new npc_huntsman_blake();
    new npc_vitus_darkwalker();
    new npc_loren_the_fence();
    new npc_sister_almyra();
    new npc_celestine_of_the_harves();
    new npc_myriam_spellwaker();
    new npc_sergeant_cleese();
    new npc_gwen_armstead_qi();
    new npc_admiral_nightwind();

    new go_merchant_square_door();
    new go_crate_of_mandrake_essence();
    new go_koroth_banner();
    new go_qnhnb_well();
    new go_ball_and_chain_qld();

    new spell_summon_crowley_horse();
    new spell_summon_crowley_horse_second_round();
    new spell_curse_of_the_worgen_summon();
    new spell_curse_of_the_worgen_invis();
    new spell_launch_qtbs();
    new spell_round_up_horse();
    new spell_belysras_talisman();
    new spell_horn_of_taldoren();
    new spell_worgen_combat_transform_fx();
    new spell_place_blessed_offerings();
    new spell_call_attack_mastiffs();
    new spell_captured_riding_bat();
    new spell_summon_carriage();
}
