#include "ScriptPCH.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "WorldPacket.h"

enum Spells
{
    // Fel Flames
    SPELL_FELFLAMES                          = 88999,

    // Argaloth
    SPELL_CONSUMING_DARKNESS                 = 88954,
    SPELL_FEL_FIRESTORM                      = 88972,
    SPELL_BERSERK                            = 47008,
};

#define SPELL_METEOR_SLASH                   RAID_MODE(88942, 95172)

class boss_argaloth : public CreatureScript
{
    public:
        boss_argaloth() : CreatureScript("boss_argaloth") {}

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_argalothAI(pCreature);
        }
            
        struct boss_argalothAI : public ScriptedAI
        {
            boss_argalothAI(Creature* pCreature) : ScriptedAI(pCreature), summons(me)
            {
                m_pInstance = pCreature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiConsumingDarknessTimer;
            uint32 m_uiMeteorSlashTimer;
            uint32 m_uiCancelTimer;
            uint32 m_uiBerserkTimer;
            SummonList summons;
            bool felfire1, felfire2;

            void Reset()
            {
                if (m_pInstance)
                   m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove

                if (me->HasAura(47008))
                    me->RemoveAura(47008);

                summons.DespawnAll();
                if (me->HasAura(47008))
                    me->RemoveAura(47008);
                m_uiConsumingDarknessTimer = 20000;
                m_uiMeteorSlashTimer = 10000;
                m_uiCancelTimer = 0;
                m_uiBerserkTimer = 300000;
            }

            void EnterCombat(Unit* pWho)
            {
                if (m_pInstance)
                   m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add

                felfire1 = false;
                felfire2 = false;
                m_uiConsumingDarknessTimer = 20000;
                m_uiMeteorSlashTimer = 10000;
                m_uiCancelTimer = 0;
                m_uiBerserkTimer = 300000;
            }

            void EnterEvadeMode() // AKA Wipe.
            {
                me->GetMotionMaster()->MoveTargetedHome();
                me->SetHealth(me->GetMaxHealth());

                if (me->HasAura(47008))
                    me->RemoveAura(47008);

                if (m_pInstance)
                   m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            void JustDied(Unit* killer)
            {
                if (m_pInstance)
                   m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            void JustSummoned(Creature* summon)
            {
                summons.push_back(summon->GetGUID());
                DoZoneInCombat(summon);
            }

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (m_uiConsumingDarknessTimer <= uiDiff)
                {
                    std::list<Unit*> targets;
                    SelectTargetList(targets, RAID_MODE(3, 8), SELECT_TARGET_RANDOM, 0.0f, true);
                    if (!targets.empty())
                        for (std::list<Unit*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            me->AddAura(SPELL_CONSUMING_DARKNESS, *itr);

                    m_uiConsumingDarknessTimer = urand(40000, 50000);
                }
                else
                    m_uiConsumingDarknessTimer -= uiDiff;
                if (m_uiMeteorSlashTimer <= uiDiff)
                {
                    DoCastAOE(SPELL_METEOR_SLASH);
                    m_uiMeteorSlashTimer = urand(15000, 18000);
                }
                else
                    m_uiMeteorSlashTimer -= uiDiff;
                if(me->GetHealth() <= me->CountPctFromMaxHealth(66) && !felfire1)
                {
                    me->CastStop();
                    DoCastAOE(SPELL_FEL_FIRESTORM);
                    m_uiConsumingDarknessTimer += 23000;
                    m_uiMeteorSlashTimer += 23000;
                    m_uiCancelTimer = 21000;
                    felfire1 = true;
                }
                if(me->GetHealth() <= me->CountPctFromMaxHealth(33) && !felfire2)
                {
                    me->CastStop();
                    DoCastAOE(SPELL_FEL_FIRESTORM);
                    m_uiConsumingDarknessTimer += 23000;
                    m_uiMeteorSlashTimer += 23000;
                    m_uiCancelTimer = 21000;
                    felfire2 = true;
                }
                if (m_uiCancelTimer <= uiDiff && m_uiCancelTimer > 0)
                    summons.DespawnAll();
                else
                    m_uiCancelTimer -= uiDiff;

                if (m_uiBerserkTimer <= uiDiff)
                    DoCast(me, SPELL_BERSERK);
                else
                    m_uiBerserkTimer -= uiDiff;
                    
                DoMeleeAttackIfReady();
            }
        };
};

class npc_felflames : public CreatureScript
{
    public:
        npc_felflames() : CreatureScript("npc_felflames") {}

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_felflamesAI(pCreature);
        }
            
        struct npc_felflamesAI : public ScriptedAI
        {
            npc_felflamesAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                m_pInstance = pCreature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiFlamesTimer;
            bool flames;

            void Reset()
            {
                m_uiFlamesTimer = 100;
                flames = false;
            }

            void EnterCombat(Unit* pWho) 
            {
                m_uiFlamesTimer = 100;
                flames = false;
            }

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (m_uiFlamesTimer <= uiDiff && flames == false)
                {
                    DoCast(me, SPELL_FELFLAMES);
                    flames = true;
                }
                else
                    m_uiFlamesTimer -= uiDiff;
            }
        };
};

void AddSC_boss_argaloth()
{
    new boss_argaloth();
    new npc_felflames();
}