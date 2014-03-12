#include "ScriptPCH.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
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

enum Creatures
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
        boss_setesh() : CreatureScript("boss_setesh") {}

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_seteshAI(pCreature);
        }
            
        struct boss_seteshAI : public ScriptedAI
        {
            boss_seteshAI(Creature* pCreature) : ScriptedAI(pCreature), summons(me)
            {
                m_pInstance = pCreature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiChaosBoltTimer;
            uint32 m_uiPortalTimer;
            uint32 m_uiShadowCrashTimer;
            uint32 m_uiSeedofChaosTimer;
            uint32 m_uiReignofChaosTimer;
            SummonList summons;

            void Reset()
            {
                m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
                summons.DespawnAll();
                m_uiChaosBoltTimer = 1000;
                m_uiPortalTimer = 10000;
                m_uiShadowCrashTimer = 7000;
                m_uiReignofChaosTimer = IsHeroic() ? 20000 : 30000;
                m_uiSeedofChaosTimer = IsHeroic() ? 6000 : 9000;
            }

            void EnterCombat(Unit* pWho)
            {
                m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                m_uiChaosBoltTimer = 1000;
                m_uiPortalTimer = 10000;
                m_uiShadowCrashTimer = 7000;
                m_uiReignofChaosTimer = IsHeroic() ? 20000 : 30000;
                m_uiSeedofChaosTimer = IsHeroic() ? 6000 : 9000;
                Talk(SAY_AGGRO);
            }

            void KilledUnit(Unit * /*victim*/)
            {
                Talk(SAY_KILL);
            }
            
            void JustDied(Unit* killer)
            {
                summons.DespawnAll();
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

            void UpdateAI(const uint32 uiDiff)
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

                    me->SummonCreature(NPC_SEED_OF_CHAOS, me->GetPositionX() + urand(-40, 40), me->GetPositionY() + urand(-40, 40), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 24000);

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
                        portal = me->SummonCreature(NPC_PORTAL, me->GetPositionX()+urand(15, 25), me->GetPositionY()+urand(15, 25), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 36000);
                    else
                        portal = me->SummonCreature(NPC_PORTAL, me->GetPositionX()-urand(15, 25), me->GetPositionY()+urand(15, 25), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 36000);
                    DoZoneInCombat(portal);
                    m_uiPortalTimer = IsHeroic() ? urand(22000, 27000) : urand(27000, 32000);
                }
                else
                    m_uiPortalTimer -= uiDiff;            
            }
        };
};

class npc_portal : public CreatureScript
{
    public:
        npc_portal() : CreatureScript("npc_portal") {}

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_portalAI(pCreature);
        }
            
        struct npc_portalAI : public ScriptedAI
        {
            npc_portalAI(Creature* pCreature) : ScriptedAI(pCreature), summons(me)
            {
                m_pInstance = pCreature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiSentinelTimer;
            uint32 m_uiWurmsTimer;
            uint32 m_uiSeekerTimer;
            SummonList summons;
            
            void Reset()
            {
                summons.DespawnAll();
                m_uiSentinelTimer = 5000;
                m_uiWurmsTimer = IsHeroic() ? 12000 : 15000;
                m_uiSeekerTimer = IsHeroic() ? 20000 : 26000;
            }

            void EnterCombat(Unit* pWho)
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

            void UpdateAI(const uint32 uiDiff)
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
};

class npc_sentinel : public CreatureScript
{
    public:
        npc_sentinel() : CreatureScript("npc_sentinel") {}

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_sentinelAI(pCreature);
        }
            
        struct npc_sentinelAI : public ScriptedAI
        {
            npc_sentinelAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                m_pInstance = pCreature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            
            void Reset()
            {
                if(IsHeroic())
                    me->AddAura(SPELL_VOID_BARRIER, me);
            }

            void EnterCombat(Unit* pWho)
            {
                if(IsHeroic())
                    me->AddAura(SPELL_VOID_BARRIER, me);
            }

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;
                DoMeleeAttackIfReady();
            }
        };
};

class npc_seeker : public CreatureScript
{
    public:
        npc_seeker() : CreatureScript("npc_seeker") {}

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_seekerAI(pCreature);
        }
            
        struct npc_seekerAI : public ScriptedAI
        {
            npc_seekerAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                m_pInstance = pCreature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiPrisonTimer;
            
            void Reset()
            {
                m_uiPrisonTimer = 5000;
            }

            void EnterCombat(Unit* pWho)
            {
                m_uiPrisonTimer = 5000;
            }

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (m_uiPrisonTimer <= uiDiff)
                {
                    DoCast(me->GetVictim(), SPELL_MAGIC_PRISON);
                    m_uiPrisonTimer = 31000;
                }
                else
                    m_uiPrisonTimer -= uiDiff;
                DoMeleeAttackIfReady();
            }
        };
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

            void UpdateAI(const uint32 diff)
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

            void EnterCombat(Unit * /*who*/)
            {
                me->AddAura(SPELL_REIGN_OF_CHAOS_AURA, me);
                m_uiNovaTimer = urand(1000, 7000);
            }

            void UpdateAI(const uint32 diff)
            {

                if (!UpdateVictim())
                    return;

                if (m_uiNovaTimer <= diff)
                {
                    Unit *pTarget;
                    std::list<HostileReference *> t_list = me->getThreatManager().getThreatList();
                    for (std::list<HostileReference *>::const_iterator itr = t_list.begin(); itr!= t_list.end(); ++itr)
                    {
                        pTarget = Unit::GetUnit(*me, (*itr)->getUnitGuid());
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
    new npc_portal();
    new npc_sentinel();
    new npc_seeker();
    new npc_seed_of_chaos();
    new npc_reign_of_chaos();
}
