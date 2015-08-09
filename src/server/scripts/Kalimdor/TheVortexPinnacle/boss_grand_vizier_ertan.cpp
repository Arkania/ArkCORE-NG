/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
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
#include"the_vortex_pinnacle.h"

enum ScriptTexts
{
    SAY_AGGRO    = 0,
    SAY_KILL     = 1,
    SAY_DEATH    = 2,
};

enum Spells
{
    SPELL_CYCLONE_SHIELD        = 86267,
    SPELL_CYCLONE_SHIELD_DMG    = 86292,
    SPELL_CYCLONE_SHIELD_DMG_H  = 93991,
    SPELL_SUMMON_TEMPEST        = 86340,
    SPELL_STORM_EDGE            = 86309,
    SPELL_STORM_EDGE_H          = 93992,
    SPELL_LIGHTNING_BOLT        = 86331,
    SPELL_LIGHTNING_BOLT_H      = 93990,
};

enum Events
{
    EVENT_LIGHTNING_BOLT    = 1,
    EVENT_STORM_EDGE        = 2,
    EVENT_CALL_VORTEX       = 3,
    EVENT_RESET_VORTEX      = 4,
};

enum Adds
{
    NPC_ERTAN_VORTEX      = 46007,
    NPC_SLIPSTREAM        = 45455,
};

const Position ertanvortexPos_1[8] = 
{
    {-702.11f, -13.50f, 635.67f, 0.0f},
    {-694.54f, 4.25f, 635.67f, 0.0f},
    {-702.07f, 22.15f, 635.67f, 0.0f},
    {-720.19f, 29.54f, 635.67f, 0.0f},
    {-737.65f, 21.79f, 635.67f, 0.0f},
    {-745.00f, 3.99f, 635.67f, 0.0f},
    {-737.42f, -13.97f, 635.67f, 0.0f},
    {-719.55f,   -21.19f, 635.67f, 0.0f},
};

class boss_grand_vizier_ertan : public CreatureScript
{
    public:
        boss_grand_vizier_ertan() : CreatureScript("boss_grand_vizier_ertan") { }
        
        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_grand_vizier_ertanAI(creature);
        }
        struct boss_grand_vizier_ertanAI : public ScriptedAI
        {
            boss_grand_vizier_ertanAI(Creature* creature) : ScriptedAI(creature), Summons(me)
            {
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_STUN, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FEAR, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_ROOT, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FREEZE, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_POLYMORPH, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_HORROR, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_SAPPED, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_CHARM, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_DISORIENTED, true);
                pInstance = creature->GetInstanceScript();
            }

            InstanceScript *pInstance;
            EventMap events;
            SummonList Summons;
            Creature* _vortexes[8];
            float _distance;
    
            void Reset()
            {
                if (!pInstance)
                    return;

                events.Reset();
                pInstance->SetData(DATA_GRAND_VIZIER_ERTAN, NOT_STARTED);
            }
    
            void EnterCombat(Unit* /*pWho*/)
            {
                if (!pInstance)
                    return;

                //for (uint8 i = 0; i < 8; i++)
                    //_vortexes[i] = me->SummonCreature(NPC_ERTAN_VORTEX, ertanvortexPos_1[i]);

                events.ScheduleEvent(EVENT_LIGHTNING_BOLT, 3000);
                //events.ScheduleEvent(EVENT_CALL_VORTEX, urand(18000, 21000));
                //events.ScheduleEvent(EVENT_STORM_EDGE, 5000);
                Talk(SAY_AGGRO);
                DoZoneInCombat();
                pInstance->SetData(DATA_GRAND_VIZIER_ERTAN, IN_PROGRESS);
            }    

            void KilledUnit(Unit* /*who*/)
            {
                Talk(SAY_KILL);                
            }

            void JustSummoned(Creature* summon)
            {
                Summons.Summon(summon);
            }

            void SummonedCreatureDespawn(Creature* summon)
            {
                Summons.Despawn(summon);
            }

            void JustDied(Unit* /*who*/)
            {
                if (!pInstance)
                    return;

                Talk(SAY_DEATH);
                pInstance->SetData(DATA_GRAND_VIZIER_ERTAN, DONE);
            }
            
            void UpdateAI(uint32 diff)
            {
                if (!pInstance || !UpdateVictim())
                    return;

                Summons.DespawnAll();
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_LIGHTNING_BOLT:
                        if (me->HasUnitState(UNIT_STATE_CASTING))
                            return;
                        DoCastVictim(SPELL_LIGHTNING_BOLT);
                        events.ScheduleEvent(EVENT_LIGHTNING_BOLT, 2000);
                        break;
                    case EVENT_CALL_VORTEX:
                        for (uint8 i = 0; i < 8; i++)
                            if (_vortexes[i])
                            {
                                float _angle;
                                _angle = me->GetAngle(_vortexes[i]->GetPositionX(), _vortexes[i]->GetPositionY());
                                Position _pos = me->GetNearPosition(5.0f, _angle);
                                _vortexes[i]->GetMotionMaster()->MovementExpired(false);
                                _vortexes[i]->GetMotionMaster()->MovePoint(1, _pos);
                            }
                        
                        events.ScheduleEvent(EVENT_RESET_VORTEX, urand(14000, 17000));
                        break;
                    case EVENT_RESET_VORTEX:
                        for (uint8 i = 0; i < 8; i++)
                            if (_vortexes[i])
                            {
                                _vortexes[i]->GetMotionMaster()->MovementExpired(false);
                                _vortexes[i]->GetMotionMaster()->MovePoint(2, ertanvortexPos_1[i]);
                            }
                        events.ScheduleEvent(EVENT_CALL_VORTEX, urand(20000, 25000));
                        break;
                    case EVENT_STORM_EDGE:
                        _distance = me->GetDistance2d(_vortexes[1]);
                        if (me->GetMap()->GetPlayers().isEmpty())
                            return;
                        for (Map::PlayerList::const_iterator itr = me->GetMap()->GetPlayers().begin(); itr != me->GetMap()->GetPlayers().end(); ++itr)
                        {
                            if (Player* pPlayer = itr->GetSource())
                            {
                                if (me->GetDistance2d(pPlayer) > _distance)
                                {
                                    //uint8 i = urand(0, 7);
                                    //if (_vortexes[i])
                                        //_vortexes[i]->CastSpell(itr->GetSource(), SPELL_STORM_EDGE, true);
                                    DoCast(pPlayer, SPELL_STORM_EDGE, true);
                                }
                            }
                        }
                        events.ScheduleEvent(EVENT_STORM_EDGE, 2000);
                        break;
                    }
                }                    
            }
        };
};

class npc_ertan_vortex : public CreatureScript
{
    public:
        npc_ertan_vortex() : CreatureScript("npc_ertan_vortex") { }
        
        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_ertan_vortexAI(creature);
        }
        struct npc_ertan_vortexAI : public ScriptedAI
        {
            npc_ertan_vortexAI(Creature* creature) : ScriptedAI(creature)
            {
                pInstance = creature->GetInstanceScript();
            }

            InstanceScript *pInstance;
            uint32 uiDespawnTimer;


            void Reset()
            {
                DoCast(me, SPELL_CYCLONE_SHIELD);
                uiDespawnTimer = 3000;
            }

            void UpdateAI(uint32 diff)
            {
                if (!pInstance)
                    return;

                if (uiDespawnTimer <= diff)
                {
                    if (pInstance->GetData(DATA_GRAND_VIZIER_ERTAN) != IN_PROGRESS)
                        me->DespawnOrUnsummon(1000);
                    uiDespawnTimer = 5000;
                }
                else
                    uiDespawnTimer -= diff;
            }
     };
};

void AddSC_boss_grand_vizier_ertan()
{
    new boss_grand_vizier_ertan();
    new npc_ertan_vortex();
}
