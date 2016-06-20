/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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
#include "ObjectMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "halls_of_origination.h"
#include "WorldPacket.h"

#define SAY_ANNOUNCE "Rajh's energy has dropped low!"
#define SAY_JUMP "Rajh is about to leap on a nearby target!"

enum Spells
{
    SPELL_NO_REGEN                           = 78725,

    SPELL_SUN_STRIKE                         = 73872,
    SPELL_SUN_STRIKE_PERIODIC                = 73874,

    SPELL_SUMMON_ORB                         = 80352,
    SPELL_SUN_ORB_VISUAL                     = 73658,

    SPELL_BLAZING_INFERNO_N                  = 82643,
    SPELL_BLAZING_INFERNO_H                  = 92528,

    SPELL_WINDS_VISUAL                       = 74109,
    SPELL_SOLAR_WINDS                        = 74104,
    SPELL_SOLAR_WINDS_PERIODIC               = 74107, //summon flames on the ground also

    SPELL_SOLAR_FIRE                         = 89131, //damage for the leftover flames

    SPELL_INFERNO_LEAP_MOB_SUMMON            = 87650,
    SPELL_INFERNO_LEAP_CAST_TIME             = 87653, //actual spell
    SPELL_INFERNO_LEAP_BUFF                  = 87645, //visual aura for inferno leap target
    SPELL_ADRENALINE                         = 87657, //to be used with AddAura
    SPELL_INFERNO_LEAP                       = 82856, //Jumps

    SPELL_BLESSING_RECHARGE                  = 76352,
    SPELL_SELF_ROOT                          = 42716,
};

enum Texts
{
    SAY_AGGRO      = 0,
    SAY_KILL       = 2,
    SAY_DEATH      = 3,
    SAY_BLESSING   = 1,
};

enum Npc
{
    NPC_WINDS                                = 39634,
    NPC_SUN_ORB                              = 40835,
    NPC_INFERNO_LEAP                         = 47040,
    NPC_SOLAR_WINDS                          = 47922,
};

class boss_rajh : public CreatureScript
{
    public:
        boss_rajh() : CreatureScript("boss_rajh") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_rajhAI(creature);
        }
            
        struct boss_rajhAI : public ScriptedAI
        {
            boss_rajhAI(Creature* creature) : ScriptedAI(creature)
            {
                m_pInstance = creature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiSunStrikeTimer;
            uint32 m_uiWindsTimer;
            uint32 m_uiSunOrbTimer;
            uint32 m_uiLeapTimer;
            uint32 leap_timer;
            bool leap, blessing;

            void Reset()
            {
                m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
                me->RemoveAurasDueToSpell(SPELL_NO_REGEN);
                me->SetPower(POWER_ENERGY, 100);
                me->SetMaxPower(POWER_ENERGY, 100);
                m_uiSunStrikeTimer = 5000;
                m_uiWindsTimer = urand(7000, 12000);
                m_uiSunOrbTimer = urand(20000, 24000);
                m_uiLeapTimer = urand(17000, 19000);
                leap = false;
                blessing = false;
            }

            void EnterCombat(Unit* /*who*/)
            {
                m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                DoCast(me, SPELL_NO_REGEN);
                me->SetPower(POWER_ENERGY, 100);
                me->SetMaxPower(POWER_ENERGY, 100);
                m_uiSunStrikeTimer = 5000;
                m_uiWindsTimer = urand(7000, 12000);
                m_uiSunOrbTimer = urand(20000, 24000);
                m_uiLeapTimer = urand(17000, 19000);
                leap = false;
                blessing = false;
                Talk(SAY_AGGRO);
            }

            void KilledUnit(Unit * /*victim*/)
            {
                Talk(SAY_KILL);
            }

            void JustDied(Unit* /*killer*/)
            {
                Talk(SAY_DEATH);
                m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            void EnterEvadeMode()
            {
                me->GetMotionMaster()->MoveTargetedHome();
                me->SetHealth(me->GetMaxHealth());
                
                if (m_pInstance)
                   m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            void UpdateAI(uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if (me->GetPower(POWER_ENERGY) < 0)
                    me->SetPower(POWER_ENERGY, 0);
                    
                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (me->GetPower(POWER_ENERGY) == 100)
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, 512);
                    me->RemoveAura(SPELL_SELF_ROOT);
                    me->RemoveAura(SPELL_BLESSING_RECHARGE);
                    blessing = false;
                }

                if (m_uiSunStrikeTimer <= uiDiff && blessing == false)
                {
                    Unit* victim = SelectTarget(SELECT_TARGET_RANDOM, 0);
                    if(victim)
                    {
                        DoCast(victim, SPELL_SUN_STRIKE);
                        me->AddAura(SPELL_SUN_STRIKE_PERIODIC, victim);
                    }
                    m_uiSunStrikeTimer = urand(11000, 14000);
                }
                else
                    m_uiSunStrikeTimer -= uiDiff;

                if (m_uiWindsTimer <= uiDiff && blessing == false)
                {
                        if(Unit* victim = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
                        DoCast(victim, SPELL_SOLAR_WINDS);
                        m_uiWindsTimer = urand(9000, 15000);
                }
                else
                    m_uiWindsTimer -= uiDiff;

                if (m_uiLeapTimer <= uiDiff && blessing == false)
                {
                    if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
                    {
                        me->MonsterTextEmote(SAY_JUMP, NULL, true);
                        me->AddThreat(pTarget, 9000.0f);
                        DoCast(pTarget, SPELL_INFERNO_LEAP_MOB_SUMMON);
                        DoCast(pTarget, SPELL_INFERNO_LEAP_CAST_TIME);
                        leap_timer = 1500;
                        leap = true;

                        Creature* Summoned = me->FindNearestCreature(NPC_INFERNO_LEAP, 100, true);
                        if (Summoned)
                        {
                            Summoned->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            Summoned->SetFloatValue(OBJECT_FIELD_SCALE_X, Summoned->GetFloatValue(OBJECT_FIELD_SCALE_X)*2.5f);
                            Summoned->setFaction(me->getFaction());
                            Summoned->SetLevel(me->getLevel());
                        }

                        m_uiLeapTimer = urand(18000, 22000);
                    }
                }
                else
                    m_uiLeapTimer -= uiDiff;

                if (leap_timer <= uiDiff && leap == true)
                {                
                    DoCastVictim(SPELL_INFERNO_LEAP);
                    leap = false;
                } else leap_timer -= uiDiff;

                if (m_uiSunOrbTimer <= uiDiff && blessing == false)
                {
                    if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
                        DoCast(pTarget, SPELL_SUMMON_ORB);
                    m_uiSunOrbTimer = urand(24000, 31000);
                }
                else
                    m_uiSunOrbTimer -= uiDiff;

                if (me->GetPower(POWER_ENERGY) == 0)
                {
                    me->MonsterTextEmote(SAY_ANNOUNCE, NULL, true);
                    DoCast(me, SPELL_BLESSING_RECHARGE);
                    blessing = true;
                    me->SetFlag(UNIT_FIELD_FLAGS, 512);
                    me->AddAura(SPELL_SELF_ROOT, me);
                    Talk(SAY_BLESSING);
                }

                if(!me->HasAura(SPELL_BLESSING_RECHARGE))
                    DoMeleeAttackIfReady();
            }
        };
};

// 39634
class npc_solar_winds_39634 : public CreatureScript
{
    public:
        npc_solar_winds_39634() : CreatureScript("npc_solar_winds_39634") { }
            
        struct npc_solar_winds_39634AI : public ScriptedAI
        {
            npc_solar_winds_39634AI(Creature* creature) : ScriptedAI(creature)
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, false);
                me->setFaction(16);
                me->DespawnOrUnsummon(20000);
                me->SetSpeed(MOVE_RUN, 0.4f);
                m_pInstance = creature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiDamageTimer;
            
            void Reset()
            {
                DoCast(me, SPELL_SOLAR_WINDS_PERIODIC);
                m_uiDamageTimer = IsHeroic() ? 1000 : 1500;
                DoCast(me, SPELL_WINDS_VISUAL);
            }

            void EnterCombat(Unit* /*who*/)
            {
                DoCast(me, SPELL_SOLAR_WINDS_PERIODIC);
                m_uiDamageTimer = IsHeroic() ? 1000 : 1500;
                DoCast(me, SPELL_WINDS_VISUAL);
            }

            void UpdateAI(uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if(m_uiDamageTimer <= uiDiff)
                {
                    me->SummonCreature(42495, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 10000);
                    m_uiDamageTimer = IsHeroic() ? 1500 : 2000;
                    float x,y,randx,randy;
                    randx = 0.0f + rand()%60;
                    randy = 0.0f + rand()%60;
                    x = 210+ randx ;
                    y = -60- randy ;
                    me->GetMotionMaster()->MovePoint(1,x,y,me->GetPositionZ());
                }
                else
                    m_uiDamageTimer -= uiDiff;
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_solar_winds_39634AI(creature);
        }
};

// 40835
class npc_orb_of_the_sun_40835 : public CreatureScript
{
    public:
        npc_orb_of_the_sun_40835() : CreatureScript("npc_orb_of_the_sun_40835") { }

        struct npc_orb_of_the_sun_40835AI : public ScriptedAI
        {
            npc_orb_of_the_sun_40835AI(Creature* creature) : ScriptedAI(creature)
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->setFaction(16);
                me->DespawnOrUnsummon(8000);
                DoStartNoMovement(me);
                m_uiExplode_timer = 2000;
                pInstance = me->GetInstanceScript();
            }

            InstanceScript* pInstance;

            void Reset()
            {
                DoCast(me, SPELL_SUN_ORB_VISUAL);
                m_uiExplode_timer = 3000;
            }
            
            void EnterCombat(Unit * /*who*/)
            {
                DoCast(me, SPELL_SUN_ORB_VISUAL);
                m_uiExplode_timer = 3000;
            }

            void UpdateAI(uint32 diff)
            {
                 if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (m_uiExplode_timer <= diff)
                {
                    DoCast(me, DUNGEON_MODE(SPELL_BLAZING_INFERNO_N, SPELL_BLAZING_INFERNO_H));
                    m_uiExplode_timer = 3000;
                } else m_uiExplode_timer -= diff;
            }

        private:
            uint32 m_uiExplode_timer;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_orb_of_the_sun_40835AI(creature);
        }
};

// 47040
class npc_inferno_leap_47040 : public CreatureScript
{
    public:
        npc_inferno_leap_47040() : CreatureScript("npc_inferno_leap_47040") { }

        struct npc_inferno_leap_47040AI : public ScriptedAI
        {
            npc_inferno_leap_47040AI(Creature* creature) : ScriptedAI(creature)
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->setFaction(16);
                me->DespawnOrUnsummon(1700);
                DoStartNoMovement(me);
            }

            InstanceScript* pInstance;
            uint32 m_uiCheckTimer;

            void Reset()
            {
                DoCast(me, SPELL_INFERNO_LEAP_BUFF);
                m_uiCheckTimer = 500;
            }

            void EnterCombat(Unit * /*who*/)
            {
                DoCast(me, SPELL_INFERNO_LEAP_BUFF);
                m_uiCheckTimer = 500;
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (m_uiCheckTimer <= diff)
                {
                    Unit *pTarget;
                    std::list<HostileReference *> t_list = me->getThreatManager().getThreatList();
                    for (std::list<HostileReference *>::const_iterator itr = t_list.begin(); itr!= t_list.end(); ++itr)
                    {
						pTarget = ObjectAccessor::GetUnit(*me, (*itr)->getUnitGuid());
                        if (pTarget && pTarget->IsWithinDistInMap(me, 12))
                        {
                            me->AddAura(SPELL_ADRENALINE, pTarget);
                            m_uiCheckTimer = 1000;
                        }
                    }
                } else 
                    m_uiCheckTimer -= diff;
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_inferno_leap_47040AI(creature);
        }
};

// 47922
class npc_solar_winds_47922 : public CreatureScript
{
    public:
        npc_solar_winds_47922() : CreatureScript("npc_solar_winds_47922") { }

        struct npc_solar_winds_47922AI : public ScriptedAI
        {
            npc_solar_winds_47922AI(Creature* creature) : ScriptedAI(creature)
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->setFaction(16);
                me->DespawnOrUnsummon(30000);
                DoStartNoMovement(me);
                pInstance = me->GetInstanceScript();
            }

            InstanceScript* pInstance;

            void Reset() { }
            
            void EnterCombat(Unit* /*who*/) { }

            void UpdateAI(uint32 /*diff*/)
            {
                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_solar_winds_47922AI(creature);
        }
};

void AddSC_boss_rajh()
{
    new boss_rajh();
    new npc_solar_winds_39634();
    new npc_orb_of_the_sun_40835();
    new npc_inferno_leap_47040();
    new npc_solar_winds_47922();
}
