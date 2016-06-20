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

#define SAY_REIG "Setesh begins casting Reign of Chaos!"

enum Spells
{
    // NPCs
    SPELL_PORTAL_VISUAL1                     = 95014,
    SPELL_PORTAL_VISUAL2                     = 64416,
    SPELL_MAGIC_PRISON                       = 76903,
    SPELL_VOID_BARRIER                       = 76959,
    
    // Setesh
    SPELL_CHAOS_BOLT                         = 77069,
    SPELL_CHAOS_BOLT_H                       = 89873,
    SPELL_REIGN_OF_CHAOS_N                   = 77213,
    SPELL_REIGN_OF_CHAOS_H                   = 89870,
    SPELL_REIGN_OF_CHAOS_CAST                = 77023, //casted by the boss
    SPELL_REIGN_OF_CHAOS_AURA                = 77026, //addaura to boss (visual) (77023)
    SPELL_SEED_OF_CHAOS_N                    = 76870, //to be used with both DoCast & AddAura
    SPELL_SEED_OF_CHAOS_H                    = 89867, //same
    SPELL_SEED_OF_CHAOS_VISUAL               = 76865,

    SPELL_SHADOW_CRASH                       = 63722, // Best resemblance I could find.
};

enum Texts
{
    SAY_AGGRO      = 0,
    SAY_KILL       = 2,
    SAY_DEATH      = 3,
    SAY_REIGN      = 1,
};

enum Npc
{
    NPC_PORTAL                               = 41055,
    NPC_VOID_SENTINEL                        = 41208,
    NPC_VOID_WURM                            = 41212,
    NPC_VOID_SEEKER                          = 41371,
    NPC_SEED_OF_CHAOS                        = 41126,
};

class boss_setesh : public CreatureScript
{
    public:
        boss_setesh() : CreatureScript("boss_setesh") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_seteshAI(creature);
        }
            
        struct boss_seteshAI : public ScriptedAI
        {
            boss_seteshAI(Creature* creature) : ScriptedAI(creature)
            {
                m_pInstance = creature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiChaosBoltTimer;
            uint32 m_uiPortalTimer;
            uint32 m_uiShadowCrashTimer;
            uint32 m_uiSeedofChaosTimer;
            uint32 m_uiReignofChaosTimer;
            std::list<uint64> summons;

            void Reset()
            {
                m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
                summons.clear();
                m_uiChaosBoltTimer = 1000;
                m_uiPortalTimer = 10000;
                m_uiShadowCrashTimer = 7000;
                m_uiReignofChaosTimer = IsHeroic() ? 20000 : 30000;
                m_uiSeedofChaosTimer = IsHeroic() ? 6000 : 9000;
            }

            void EnterCombat(Unit* /*who*/)
            {
                m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                m_uiChaosBoltTimer = 1000;
                m_uiPortalTimer = 10000;
                m_uiShadowCrashTimer = 7000;
                m_uiReignofChaosTimer = IsHeroic() ? 20000 : 30000;
                m_uiSeedofChaosTimer = IsHeroic() ? 6000 : 9000;
                Talk(SAY_AGGRO);
            }

            void KilledUnit(Unit* /*victim*/)
            {
                Talk(SAY_KILL);
            }
            
            void JustDied(Unit* /*killer*/)
            {
                summons.clear();
                Talk(SAY_DEATH);
                m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            void JustSummoned(Creature* summon)
            {
                summons.push_back(summon->GetGUID());
                summon->AI()->DoZoneInCombat();
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

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (m_uiChaosBoltTimer <= uiDiff)
                {
                    if(Unit* victim = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        DoCast(victim, IsHeroic() ? SPELL_CHAOS_BOLT_H : SPELL_CHAOS_BOLT);
                    m_uiChaosBoltTimer = 2500;
                }
                else
                    m_uiChaosBoltTimer -= uiDiff;

                if (m_uiShadowCrashTimer <= uiDiff)
                {
                    if(Unit* victim = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    {
                        DoCast(victim, SPELL_SHADOW_CRASH, true);
                        me->SummonCreature(41856, victim->GetPositionX(), victim->GetPositionY(), victim->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 24000);
                    }
                    m_uiShadowCrashTimer = urand(17000, 21000);
                }
                else
                    m_uiShadowCrashTimer -= uiDiff;
                    
                if (m_uiSeedofChaosTimer <= uiDiff)
                {
                    me->CastStop();

                    me->SummonCreature(NPC_SEED_OF_CHAOS, me->GetPositionX() + frand(-40.0f, 40.0f), me->GetPositionY() + frand(-40.0f, 40.0f), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 24000);

                    m_uiSeedofChaosTimer = urand(15000, 20000);
                }
                else
                    m_uiSeedofChaosTimer -= uiDiff;

                if (m_uiReignofChaosTimer <= uiDiff)
                {
                    me->CastStop();
                    DoCast(me, SPELL_REIGN_OF_CHAOS_CAST, true);
                    Talk(SAY_REIGN);
                    me->MonsterTextEmote(SAY_REIG, NULL, true);
                    m_uiReignofChaosTimer = urand(23000,27000);
                    m_uiChaosBoltTimer = 8000;
                    m_uiSeedofChaosTimer = urand(7000, 12000);
                }
                else
                    m_uiReignofChaosTimer -= uiDiff;

                if (m_uiPortalTimer <= uiDiff)
                {
                    me->CastStop();
                    Creature* portal;
                    if(urand(1, 2) == 1)
                        portal = me->SummonCreature(NPC_PORTAL, me->GetPositionX()+frand(15.0f, 25.0f), me->GetPositionY()+frand(15.0f, 25.0f), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 36000);
                    else
                        portal = me->SummonCreature(NPC_PORTAL, me->GetPositionX()-frand(15.0f, 25.0f), me->GetPositionY()+frand(15.0f, 25.0f), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 36000);
                    DoZoneInCombat(portal);
                    m_uiPortalTimer = IsHeroic() ? urand(22000, 27000) : urand(27000, 32000);
                }
                else
                    m_uiPortalTimer -= uiDiff;            
            }
        };
};

// 41055
class npc_chaos_portal_41055 : public CreatureScript
{
    public:
        npc_chaos_portal_41055() : CreatureScript("npc_chaos_portal_41055") { }
            
        struct npc_chaos_portal_41055AI : public ScriptedAI
        {
            npc_chaos_portal_41055AI(Creature* creature) : ScriptedAI(creature)
            {
                m_pInstance = creature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiSentinelTimer;
            uint32 m_uiWurmsTimer;
            uint32 m_uiSeekerTimer;
            std::list<uint64> summons;
            
            void Reset()
            {
                summons.clear();
                m_uiSentinelTimer = 5000;
                m_uiWurmsTimer = IsHeroic() ? 12000 : 15000;
                m_uiSeekerTimer = IsHeroic() ? 20000 : 26000;
            }

            void EnterCombat(Unit* /*who*/)
            {
                DoCast(me, SPELL_PORTAL_VISUAL1);
                DoCast(me, SPELL_PORTAL_VISUAL2);
                m_uiWurmsTimer = IsHeroic() ? 8000 : 5000;
                m_uiSeekerTimer = IsHeroic() ? 20000 : 25000;
                m_uiSentinelTimer = IsHeroic() ? 35000 : 45000;
                if(!IsHeroic())
                    me->DespawnOrUnsummon(46000);
            }

            void JustSummoned(Creature* summon)
            {
                summons.push_back(summon->GetGUID());
            }

            void UpdateAI(uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if (m_uiSentinelTimer <= uiDiff)
                {
                    Creature* sentinel = me->SummonCreature(NPC_VOID_SENTINEL, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 300000);
                    DoZoneInCombat(sentinel);
                    m_uiSentinelTimer = 60000;
                }
                else
                    m_uiSentinelTimer -= uiDiff;

                if (m_uiWurmsTimer <= uiDiff)
                {
                    Creature* wurm1 = me->SummonCreature(NPC_VOID_WURM, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 300000);
                    Creature* wurm2 = me->SummonCreature(NPC_VOID_WURM, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 300000);
                    DoZoneInCombat(wurm1);
                    DoZoneInCombat(wurm2);
                    m_uiWurmsTimer = 60000;
                }
                else
                    m_uiWurmsTimer -= uiDiff;
                
                if (m_uiSeekerTimer <= uiDiff)
                {
                    Creature* seeker = me->SummonCreature(NPC_VOID_SEEKER, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 300000);
                    DoZoneInCombat(seeker);
                    m_uiSeekerTimer = 60000;
                }
                else
                    m_uiSeekerTimer -= uiDiff;
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_chaos_portal_41055AI(creature);
        }
};

// 41208
class npc_void_sentinel_41208 : public CreatureScript
{
    public:
        npc_void_sentinel_41208() : CreatureScript("npc_void_sentinel_41208") { }
            
        struct npc_void_sentinel_41208AI : public ScriptedAI
        {
            npc_void_sentinel_41208AI(Creature* creature) : ScriptedAI(creature)
            {
                m_pInstance = creature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            
            void Reset()
            {
                if(IsHeroic())
                    me->AddAura(SPELL_VOID_BARRIER, me);
            }

            void EnterCombat(Unit* /*who*/)
            {
                if(IsHeroic())
                    me->AddAura(SPELL_VOID_BARRIER, me);
            }

            void UpdateAI(uint32 /*diff*/)
            {
                if (!UpdateVictim())
                    return;
                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_void_sentinel_41208AI(creature);
        }
};

// 41148 // 41371
class npc_void_seeker_41148 : public CreatureScript
{
    public:
        npc_void_seeker_41148() : CreatureScript("npc_void_seeker_41148") { }
            
        struct npc_void_seeker_41148AI : public ScriptedAI
        {
            npc_void_seeker_41148AI(Creature* creature) : ScriptedAI(creature)
            {
                m_pInstance = creature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiPrisonTimer;
            
            void Reset()
            {
                m_uiPrisonTimer = 5000;
            }

            void EnterCombat(Unit* /*who*/)
            {
                m_uiPrisonTimer = 5000;
            }

            void UpdateAI(uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (m_uiPrisonTimer <= uiDiff)
                {
                    DoCastVictim(SPELL_MAGIC_PRISON);
                    m_uiPrisonTimer = 31000;
                }
                else
                    m_uiPrisonTimer -= uiDiff;
                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_void_seeker_41148AI(creature);
        }
};

class npc_seed_of_chaos : public CreatureScript
{
    public:
        npc_seed_of_chaos() : CreatureScript("npc_seed_of_chaos") { }

        struct npc_seed_of_chaosAI : public ScriptedAI
        {
            npc_seed_of_chaosAI(Creature* creature) : ScriptedAI(creature)
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->setFaction(16);
                me->DespawnOrUnsummon(26000);
                DoStartNoMovement(me);
            }

            InstanceScript* pInstance;
            uint32 m_uiCheckTimer;

            void Reset()
            {
                DoCast(me, SPELL_SEED_OF_CHAOS_VISUAL);
                m_uiCheckTimer = 1000;
            }

            void EnterCombat(Unit * /*who*/)
            {
                DoCast(me, SPELL_SEED_OF_CHAOS_VISUAL);
                m_uiCheckTimer = 1000;
            }

            void UpdateAI(uint32 diff)
            {

                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (m_uiCheckTimer <= diff)
                {
                    if (Unit *pTarget = me->FindNearestPlayer(6.0f, true))
                        {

                            me->AddAura(DUNGEON_MODE(SPELL_SEED_OF_CHAOS_N, SPELL_SEED_OF_CHAOS_H), pTarget);
                            DoCast(me, DUNGEON_MODE(SPELL_SEED_OF_CHAOS_N, SPELL_SEED_OF_CHAOS_H));
                            me->DespawnOrUnsummon();
                        }
                        m_uiCheckTimer = 1000;
                } else 
                    m_uiCheckTimer -= diff;
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_seed_of_chaosAI(creature);
        }
};

class npc_reign_of_chaos : public CreatureScript
{
    public:
        npc_reign_of_chaos() : CreatureScript("npc_reign_of_chaos") { }

        struct npc_reign_of_chaosAI : public ScriptedAI
        {
            npc_reign_of_chaosAI(Creature* creature) : ScriptedAI(creature)
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->setFaction(16);
                me->DespawnOrUnsummon(5000);
                DoStartNoMovement(me);
            }

            InstanceScript* pInstance;
            uint32 m_uiNovaTimer;

            void EnterCombat(Unit* /*who*/)
            {
                me->AddAura(SPELL_REIGN_OF_CHAOS_AURA, me);
                m_uiNovaTimer = urand(1000, 7000);
            }

            void UpdateAI(uint32 diff)
            {

                if (!UpdateVictim())
                    return;

                if (m_uiNovaTimer <= diff)
                {
                    Unit *pTarget;
                    std::list<HostileReference *> t_list = me->getThreatManager().getThreatList();
                    for (std::list<HostileReference *>::const_iterator itr = t_list.begin(); itr!= t_list.end(); ++itr)
                    {
						pTarget = ObjectAccessor::GetUnit(*me, (*itr)->getUnitGuid());
                        if (pTarget && pTarget->IsWithinDistInMap(me, 6))
                            DoCast(pTarget, DUNGEON_MODE(SPELL_REIGN_OF_CHAOS_N, SPELL_REIGN_OF_CHAOS_H), true);

                    }
                    m_uiNovaTimer = urand(1000, 7000);
                } else 
                    m_uiNovaTimer -= diff;
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_reign_of_chaosAI(creature);
        }
};

void AddSC_boss_setesh()
{
    new boss_setesh();
    new npc_chaos_portal_41055();
    new npc_void_sentinel_41208();
    new npc_void_seeker_41148();
    new npc_seed_of_chaos();
    new npc_reign_of_chaos();
}
