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

#define SAY_ANNOUNCE "Ammunae plants some Seedling Pods nearby!"

enum Spells
{
    // NPCs
    SPELL_ENERGIZING_GROWTH                  = 89123,
    SPELL_ENERGIZING_GROWTH_TICK             = 89124,
    SPELL_THORN_SLASH                        = 76044,
    SPELL_THORN_SLASH_H                      = 90007,
    SPELL_ENERGIZE_ENRAGE                    = 75657,
    SPELL_VISUAL_ENERGIZE                    = 75624,
    
    // Ammunae
    SPELL_NO_REGEN                           = 78725,
    SPELL_RAMPANT_GROWTH                     = 75790,
    SPELL_RAMPANT_GROWTH_H                   = 89888,
    SPELL_WITHER                             = 76043,
    SPELL_CONSUME_ENERGY_MANA_N              = 75718, 
    SPELL_CONSUME_ENERGY_ENER_N              = 79766,
    SPELL_CONSUME_ENERGY_RAGE_N              = 79767, //rage stiil rises (1)
    SPELL_CONSUME_ENERGY_RUNE_N              = 79768, //runic is (6)
    SPELL_CONSUME_ENERGY_FOCU_N              = 80968, //focus is (2)
    SPELL_CONSUME_ENERGY_ENER_H              = 94961, //power burn (3)
    
    SPELL_SPORE                              = 75866, // Summon spore.
};

enum ScriptTexts
{
    SAY_AGGRO                = 0,
    SAY_RAMPANT              = 1,
    SAY_KILL                 = 2,
    SAY_DEATH                = 3,
};

 uint16 i;

class boss_ammunae : public CreatureScript
{
    public:
        boss_ammunae() : CreatureScript("boss_ammunae") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_ammunaeAI(creature);
        }
            
        struct boss_ammunaeAI : public ScriptedAI
        {
            boss_ammunaeAI(Creature* creature) : ScriptedAI(creature)
            {                
                m_pInstance = creature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiWitherTimer;
            uint32 m_uiSporeTimer;
            uint32 m_uiSeedlingTimer;
            uint32 m_uiRampantTimer;
            uint32 m_uiBoomTimer;
            uint32 m_uiEnergizingGrowthTimer;
            uint32 m_uiLife_Drain_Timer;
            uint32 m_uiLife_Drain2_Timer;
            uint32 m_uiLife_Drain3_Timer;
            uint32 m_uiLife_Drain4_Timer;
            uint32 m_uiLife_Drain5_Timer;
            std::list<uint64> summons;
            Creature* seedling[10];
            Creature* blossom[10];

            void Reset()
            {
                m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
                DoCast(me, SPELL_NO_REGEN);
                summons.clear();
                me->SetPower(POWER_ENERGY, 0);
                me->SetMaxPower(POWER_ENERGY, 100);
                m_uiWitherTimer = 5000;
                m_uiSeedlingTimer = 10000;
                m_uiRampantTimer = 15000;
                m_uiLife_Drain_Timer = 6000;
                m_uiLife_Drain2_Timer = 10000;
                m_uiLife_Drain3_Timer = 14000;
                m_uiLife_Drain4_Timer = 19000;
                m_uiLife_Drain5_Timer = 25000;
                m_uiSporeTimer   = 7500;

                i = 0;
                for(uint8 p=0; p<10; p++)
                {
                    seedling[p] = nullptr;
                    blossom[p] = nullptr;
                }
            }

            void EnterCombat(Unit* /*who*/)
            {
                m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                DoCast(me, SPELL_NO_REGEN);
                me->SetPower(POWER_ENERGY, 0);
                me->SetMaxPower(POWER_ENERGY, 100);
                m_uiWitherTimer = 5000;
                m_uiSeedlingTimer = 10000;
                m_uiRampantTimer = 15000;
                m_uiLife_Drain_Timer = 6000;
                m_uiLife_Drain2_Timer = 10000;
                m_uiLife_Drain3_Timer = 14000;
                m_uiLife_Drain4_Timer = 19000;
                m_uiLife_Drain5_Timer = 25000;
                m_uiSporeTimer   = 7500;

                i = 0;
                for(uint8 p=0; p<10; p++)
                {
                    seedling[p] = nullptr;
                    blossom[p] = nullptr;
                }
                Talk(SAY_AGGRO);
            }

            void KilledUnit(Unit* /*killed*/)
            {
                Talk(SAY_KILL);
            }

            void JustDied(Unit* /*killer*/)
            {
                summons.clear();
                i = 0;
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

            void JustSummoned(Creature* summon)
            {
                summons.push_back(summon->GetGUID());
            }

            void UpdateAI(uint32 uiDiff)
            {
                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (!UpdateVictim())
                    return;

                if (m_uiSporeTimer <= uiDiff)
                {
                    if(Unit* victim = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
                        DoCast(victim, SPELL_SPORE);
                    m_uiSporeTimer = urand(20000, 25000);
                }
                else
                    m_uiSporeTimer -= uiDiff;

                if (m_uiWitherTimer <= uiDiff)
                {
                    if(Unit* victim = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        DoCast(victim, SPELL_WITHER);
                    m_uiWitherTimer = urand(14000, 18000);
                }
                else
                    m_uiWitherTimer -= uiDiff;

                if (m_uiLife_Drain_Timer <= uiDiff)
                {
                    Unit *pTarget = nullptr;

                    uint8 i = 0;
                    while (i < 5)                                   // max 5 tries to get a random target with power_mana
                    {
                    ++i;
                    pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 100, true); 
                    if (pTarget && pTarget->getPowerType() == POWER_MANA)
                    {
                        i = 5;

                        me->SetPower(POWER_ENERGY, me->GetPower(POWER_ENERGY) + 10); // cast spell on target with mana.
                        DoCast(pTarget, SPELL_CONSUME_ENERGY_MANA_N);
                    }
                }

                    m_uiLife_Drain_Timer = 15000;

                } else m_uiLife_Drain_Timer -= uiDiff;

                if (m_uiLife_Drain2_Timer <= uiDiff)
                {
                    Unit *pTarget = nullptr;

                    uint8 i = 0;
                    while (i < 5)                                   // max 5 tries to get a random target with power_energy
                    {
                    ++i;
                    pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 100, true); 
                    if (pTarget && pTarget->getPowerType() == POWER_ENERGY)
                    {
                            i = 5;

                        me->SetPower(POWER_ENERGY, me->GetPower(POWER_ENERGY) + 10); // cast spell on target with mana.
                        DoCast(pTarget, SPELL_CONSUME_ENERGY_ENER_N);
                    }
                    }

                    m_uiLife_Drain2_Timer = 15000;
                } else m_uiLife_Drain2_Timer -= uiDiff;

                if (m_uiLife_Drain3_Timer <= uiDiff)
                {
                    Unit *pTarget = nullptr;

                    uint8 i = 0;
                    while (i < 5)                                   // max 5 tries to get a random target with power_runic
                    {
                    ++i;
                    pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 100, true); 
                    if (pTarget && pTarget->getPowerType() == POWER_RUNIC_POWER)
                    {
                            i = 5;

                        DoCast(pTarget, SPELL_CONSUME_ENERGY_RUNE_N);
                        me->SetPower(POWER_ENERGY, me->GetPower(POWER_ENERGY) + 20);
                    }
                    }

                    m_uiLife_Drain3_Timer = 15000;
                } else m_uiLife_Drain3_Timer -= uiDiff;

                if (m_uiLife_Drain4_Timer <= uiDiff)
                {
                    Unit *pTarget = nullptr;

                    uint8 i = 0;
                    while (i < 5)                                   // max 5 tries to get a random target with power_rage
                    {
                    ++i;
                    pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 100, true);                    
                    if (pTarget && pTarget->getPowerType() == POWER_RAGE)
                    {
                            i = 5;

                        DoCast(pTarget, SPELL_CONSUME_ENERGY_RAGE_N);
                        me->SetPower(POWER_ENERGY, me->GetPower(POWER_ENERGY) + 10);
                    }
                    }

                    m_uiLife_Drain4_Timer = 15000;
                } else m_uiLife_Drain4_Timer -= uiDiff;

                if (m_uiLife_Drain5_Timer <= uiDiff)
                {
                    Unit *pTarget = nullptr;

                    uint8 i = 0;
                    while (i < 5)                                   // max 5 tries to get a random target with power_focus
                    {
                    ++i;
                    pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 100, true); 
                    if (pTarget && pTarget->getPowerType() == POWER_FOCUS)
                    {
                            i = 5;

                        DoCast(pTarget, SPELL_CONSUME_ENERGY_FOCU_N);
                        me->SetPower(POWER_ENERGY, me->GetPower(POWER_ENERGY) + 20);
                    }
                    }

                    m_uiLife_Drain5_Timer = 15000;
                } else m_uiLife_Drain5_Timer -= uiDiff;

                if (m_uiSeedlingTimer <= uiDiff)
                {
                    me->MonsterTextEmote(SAY_ANNOUNCE, NULL, true);
                     
                    if(urand(1, 2) == 1)
                    {
                        seedling[i] = me->SummonCreature(40716, me->GetPositionX()+15+i*3, me->GetPositionY()+urand(10, 20), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 300000);
                        DoZoneInCombat(seedling[i]);
                    }
                    else
                    {
                        seedling[i] = me->SummonCreature(40716, me->GetPositionX()-15-i*3, me->GetPositionY()+urand(10, 20), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 300000);
                        DoZoneInCombat(seedling[i]);
                    }
                    if(!i) 
                        m_uiEnergizingGrowthTimer = 3000;
                    i++;
                    m_uiSeedlingTimer = IsHeroic() ? urand(12000, 17000) : urand(17000, 23000);
                    m_uiRampantTimer += 5000;
                }
                else
                    m_uiSeedlingTimer -= uiDiff;

                if (me->GetPower(POWER_ENERGY) == 100)
                {
                    if(me->HasUnitState(UNIT_STATE_CASTING))
                        me->CastStop();
                    DoCast(me, IsHeroic() ? SPELL_RAMPANT_GROWTH_H : SPELL_RAMPANT_GROWTH);
                    m_uiBoomTimer = 2000;
                    m_uiRampantTimer = 30000;
                    Talk(SAY_RAMPANT);
                }
                else
                    m_uiRampantTimer -= uiDiff;
                if (m_uiBoomTimer > 0 && m_uiBoomTimer <= uiDiff)
                {
                    uint8 k = 0;
                    for(uint8 j=0; j<10; j++)
                        if(seedling[j] && k != i)
                        {
                            k++;
                            blossom[j] = me->SummonCreature(40620, seedling[j]->GetPositionX(), seedling[j]->GetPositionY(), seedling[j]->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 300000);
                            DoZoneInCombat(blossom[j]);
                            seedling[j]->SetDeathState(JUST_DIED);
                        }
                    for(uint8 p=0; p<10; p++)
                    {
                        seedling[p] = nullptr;
                        blossom[p] = nullptr;
                    }
                    i = 0;
                    m_uiBoomTimer = 0;
                }
                else
                    m_uiBoomTimer -= uiDiff;

                if (i > 0 && m_uiEnergizingGrowthTimer <= uiDiff)
                {
                    if(IsHeroic())
                    {
                    DoCast(me, SPELL_ENERGIZING_GROWTH_TICK);
                    me->AddAura(SPELL_ENERGIZE_ENRAGE, me);
                    }
                    else if (!IsHeroic())
                    me->AddAura(SPELL_ENERGIZE_ENRAGE, me);
                    
                    m_uiEnergizingGrowthTimer = 4000 - i*1000;
                    me->SetPower(POWER_ENERGY, me->GetPower(POWER_ENERGY) + 10);
                }
                else
                    m_uiEnergizingGrowthTimer -= uiDiff;

                DoMeleeAttackIfReady();
            }
        };
};

class npc_seedling : public CreatureScript
{
    public:
        npc_seedling() : CreatureScript("npc_seedling") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_seedlingAI(creature);
        }
            
        struct npc_seedlingAI : public ScriptedAI
        {
            npc_seedlingAI(Creature* creature) : ScriptedAI(creature)
            {
                m_pInstance = creature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;

            void Reset()
            {
                DoCast(me, SPELL_VISUAL_ENERGIZE);
                DoCast(me, SPELL_ENERGIZING_GROWTH);
            }

            void EnterCombat(Unit* /*who*/)
            {
                DoCast(me, SPELL_VISUAL_ENERGIZE);
                DoCast(me, SPELL_ENERGIZING_GROWTH);
            }

            void JustDied(Unit* /*killer*/)
            {
                me->RemoveAura(SPELL_ENERGIZING_GROWTH);
                me->RemoveAura(SPELL_VISUAL_ENERGIZE);
                i--;
            }
            
            void UpdateAI(uint32 /*diff*/)
            {
                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;
                    
                if (!UpdateVictim())
                    return;
            }
        };
};

// 40620
class npc_bloodpetal_blossom_40620 : public CreatureScript
{
    public:
        npc_bloodpetal_blossom_40620() : CreatureScript("npc_bloodpetal_blossom_40620") { }
            
        struct npc_bloodpetal_blossom_40620AI : public ScriptedAI
        {
            npc_bloodpetal_blossom_40620AI(Creature* creature) : ScriptedAI(creature)
            {
                m_pInstance = creature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiThornSlashTimer;

            void Reset()
            {
                m_uiThornSlashTimer = urand(5000, 10000);
            }

            void EnterCombat(Unit* /*who*/)
            {
                m_uiThornSlashTimer = urand(5000, 10000);
            }

            void UpdateAI(uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;
                    
                if (m_uiThornSlashTimer <= uiDiff)
                {
                    DoCastVictim(IsHeroic() ? SPELL_THORN_SLASH_H : SPELL_THORN_SLASH);
                    m_uiThornSlashTimer = urand(15000, 20000);
                }
                else
                    m_uiThornSlashTimer -= uiDiff;
                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_bloodpetal_blossom_40620AI(creature);
        }
};

class npc_spore : public CreatureScript
{
    public:
        npc_spore() : CreatureScript("npc_spore") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_sporeAI(creature);
        }
            
        struct npc_sporeAI : public ScriptedAI
        {
            npc_sporeAI(Creature* creature) : ScriptedAI(creature)
            {
                m_pInstance = creature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;

            void Reset() { }

            void EnterCombat(Unit* /*who*/) { }

            void JustDied(Unit* /*killer*/)
            {
                me->SummonCreature(40585, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 300000);
            }
            
            void UpdateAI(uint32 /*diff*/)
            {
                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;
                    
                if (!UpdateVictim())
                    return;
                    
                DoMeleeAttackIfReady();        
            }
        };
};

void AddSC_boss_ammunae()
{
    new boss_ammunae();
    new npc_seedling();
    new npc_bloodpetal_blossom_40620();
    new npc_spore();
}
