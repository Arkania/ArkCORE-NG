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

};

enum Spells
{
    SPELL_CALL_OF_WIND            = 88244,
    SPELL_CALL_OF_WIND_DUMMY_1    = 88276,
    SPELL_CALL_OF_WIND_DUMMY_2    = 88772,
    SPELL_DOWNWIND_OF_ALTAIRUS    = 88286,
    SPELL_UPWIND_OF_ALTAIRUS      = 88282,
    SPELL_CHILLING_BREATH         = 88308,
    SPELL_CHILLING_BREATH_DUMMY   = 88322,
    SPELL_LIGHTNING_BLAST         = 88357,
    SPELL_LIGHTNING_BLAST_DUMMY   = 88332,
    SPELL_TWISTER_AURA            = 88313,
    SPELL_TWISTER_AURA_DMG        = 88314,
    
};

enum Events
{
    EVENT_CALL_OF_WIND            = 1,
    EVENT_CHILLING_BREATH         = 2,
    EVENT_LIGHTNING_BLAST         = 3,
    EVENT_CHECK_FACING            = 4,
    EVENT_RESET_WIND              = 5,
};

enum Adds
{
    NPC_TWISTER        = 47342,
    NPC_AIR_CURRENT    = 47305,
};

const float orientations[4] = {5.70f, 2.54f, 0.84f, 4.44f};

const Position twisterPos[8] =
{
    {-1213.09f, 37.58f, 734.17f, 0.0f},
    {-1208.80f, 54.49f, 734.17f, 0.0f},
    {-1219.45f, 68.33f, 734.17f, 0.0f},
};

class boss_altairus : public CreatureScript
{
    public:
        boss_altairus() : CreatureScript("boss_altairus") { }
        
        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_altairusAI(creature);
        }
        struct boss_altairusAI : public ScriptedAI
        {
            boss_altairusAI(Creature* creature) : ScriptedAI(creature), summons(me)
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
            SummonList summons;
            Creature* _aircurrent;
            uint8 _twisternum;

            void Reset()
            {
                if (!pInstance)
                    return;

                _twisternum = 0;
                summons.DespawnAll();
                events.Reset();
                pInstance->SetData(DATA_ALTAIRUS, NOT_STARTED);
            }
    
            void EnterCombat(Unit* /*pWho*/)
            {
                if (!pInstance)
                    return;

                events.ScheduleEvent(EVENT_CHILLING_BREATH, urand(5000, 10000));
                events.ScheduleEvent(EVENT_CALL_OF_WIND, 2000);
                events.ScheduleEvent(EVENT_CHECK_FACING, 2500);
                DoZoneInCombat();
                pInstance->SetData(DATA_ALTAIRUS, IN_PROGRESS);
            }    

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);
            }

            void SummonedCreatureDespawn(Creature* summon)
            {
                summons.Despawn(summon);
            }

            void JustDied(Unit* /*who*/)
            {
                if (!pInstance)
                    return;

                summons.DespawnAll();
                pInstance->SetData(DATA_ALTAIRUS, DONE);
            }
            
            bool CheckOrientation(float player, float creature)
            {
                float _cur, _up, _down;
                
                if (creature > M_PI)
                    _cur = creature - M_PI;
                else
                    _cur = creature + M_PI;
                

                _up = _cur + 1.0f;
                _down = _cur - 1.0f;

                if (player > _down && player < _up)
                    return true;
                else
                    return false;
            }

            void UpdateAI(uint32 diff)
            {
                if (!pInstance || !UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (me->GetVictim())
                    if (me->GetVictim()->GetDistance2d(me->GetHomePosition().GetPositionX(), me->GetHomePosition().GetPositionY()) > 55.0f)
                    {
                        DoCastVictim(SPELL_LIGHTNING_BLAST);
                        return;
                    }

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_CHILLING_BREATH:
                        if (Unit* target  = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                            DoCast(target, SPELL_CHILLING_BREATH);
                        events.ScheduleEvent(EVENT_CHILLING_BREATH, urand(10000, 16000));
                        break;
                    case EVENT_RESET_WIND:
                        if (_aircurrent)
                            _aircurrent->DespawnOrUnsummon();
                        events.DelayEvents(1000);
                        events.ScheduleEvent(EVENT_CALL_OF_WIND, 800);
                        break;
                    case EVENT_CALL_OF_WIND:
                        _aircurrent = me->SummonCreature(NPC_AIR_CURRENT,
                            me->GetPositionX(),
                            me->GetPositionY(),
                            me->GetPositionZ(),
                            orientations[urand(0, 3)]);
                        events.ScheduleEvent(EVENT_RESET_WIND, 18000);
                        break;
                    case EVENT_CHECK_FACING:
                        if (me->GetMap()->GetPlayers().isEmpty() || !_aircurrent)
                            break;

                        for (Map::PlayerList::const_iterator itr = me->GetMap()->GetPlayers().begin(); itr != me->GetMap()->GetPlayers().end(); ++itr) 
                        {
                            if (CheckOrientation(itr->GetSource()->GetOrientation(), _aircurrent->GetOrientation()))
                            {
                                itr->GetSource()->RemoveAurasDueToSpell(SPELL_DOWNWIND_OF_ALTAIRUS);
                                me->AddAura(SPELL_UPWIND_OF_ALTAIRUS, itr->GetSource());
                            }
                            else
                            {
                                itr->GetSource()->RemoveAurasDueToSpell(SPELL_UPWIND_OF_ALTAIRUS);
                                me->AddAura(SPELL_DOWNWIND_OF_ALTAIRUS, itr->GetSource());
                            }
                        }
                        events.ScheduleEvent(EVENT_CHECK_FACING, 3000);
                        break;
                    }
                }
                DoMeleeAttackIfReady();
            }
        };
};

class npc_air_current : public CreatureScript
{
    public:
        npc_air_current() : CreatureScript("npc_air_current") { }
        
        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_air_currentAI(creature);
        }
        struct npc_air_currentAI : public ScriptedAI
        {
            npc_air_currentAI(Creature* creature) : ScriptedAI(creature)
            {
                me->SetReactState(REACT_PASSIVE);
            }

            void Reset()
            {
                
                //DoCast(me, SPELL_CALL_OF_WIND_DUMMY_1);
                DoCast(me, SPELL_CALL_OF_WIND_DUMMY_2);
                //DoCast(me, SPELL_CALL_OF_WIND);
            }

            void UpdateAI(uint32 /*diff*/) { }
     };
};

/*class npc_altairus_twister : public CreatureScript
{
    public:
        npc_altairus_twister() : CreatureScript("npc_altairus_twister") { }
        
        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_altairus_twisterAI(creature);
        }
        struct npc_altairus_twisterAI : public ScriptedAI
        {
            npc_altairus_twisterAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void Reset()
            {
                DoCast(me, SPELL_TWISTER_AURA);
            }

            void UpdateAI(uint32 diff)
            {
            }
     };
};*/

void AddSC_boss_altairus()
{
    new boss_altairus();
    new npc_air_current();
    //new npc_altairus_twister();
}



