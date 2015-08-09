/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * This file is NOT free software. Third-party users can NOT redistribute 
 * it or modify it. If you find it, you are either hacking something, or very 
 * lucky (presuming someone else managed to hack it).
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ObjectMgr.h"
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

// 47120 boss_argaloth
class boss_argaloth : public CreatureScript
{
    public:
        boss_argaloth() : CreatureScript("boss_argaloth") { }

        struct boss_argalothAI : public ScriptedAI
        {
            boss_argalothAI(Creature* creature) : ScriptedAI(creature)
            {
                m_pInstance = creature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiConsumingDarknessTimer;
            uint32 m_uiMeteorSlashTimer;
            uint32 m_uiCancelTimer;
            uint32 m_uiBerserkTimer;
            bool felfire1, felfire2;
            std::list<uint64> Summons;

            void Reset()
            {
                if (m_pInstance)
                   m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove

                if (me->HasAura(47008))
                    me->RemoveAura(47008);

                Summons.clear();
                if (me->HasAura(47008))
                    me->RemoveAura(47008);
                m_uiConsumingDarknessTimer = 20000;
                m_uiMeteorSlashTimer = 10000;
                m_uiCancelTimer = 0;
                m_uiBerserkTimer = 300000;
            }

            void EnterCombat(Unit* /*who*/)
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

            void JustDied(Unit* /*killer*/)
            {
                if (m_pInstance)
                   m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            void JustSummoned(Creature* summon)
            {
                Summons.push_back(summon->GetGUID());
                DoZoneInCombat(summon);
            }

            void UpdateAI(uint32 uiDiff)
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
                    Summons.clear();
                else
                    m_uiCancelTimer -= uiDiff;

                if (m_uiBerserkTimer <= uiDiff)
                    DoCast(me, SPELL_BERSERK);
                else
                    m_uiBerserkTimer -= uiDiff;
                    
                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_argalothAI(creature);
        }
};

// 47829
class npc_felflames : public CreatureScript
{
    public:
        npc_felflames() : CreatureScript("npc_felflames") { }

        struct npc_felflamesAI : public ScriptedAI
        {
            npc_felflamesAI(Creature* creature) : ScriptedAI(creature)
            {
                m_pInstance = creature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiFlamesTimer;
            bool flames;

            void Reset()
            {
                m_uiFlamesTimer = 100;
                flames = false;
            }

            void EnterCombat(Unit* /*who*/) 
            {
                m_uiFlamesTimer = 100;
                flames = false;
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (m_uiFlamesTimer <= diff && flames == false)
                {
                    DoCast(me, SPELL_FELFLAMES);
                    flames = true;
                }
                else
                    m_uiFlamesTimer -= diff;
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_felflamesAI(creature);
        }
};

void AddSC_boss_argaloth()
{
    new boss_argaloth();
    new npc_felflames();
}