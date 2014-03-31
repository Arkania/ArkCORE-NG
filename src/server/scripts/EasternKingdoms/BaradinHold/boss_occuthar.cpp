/*
 * Copyright (C) 2011-2014 ArkCORE <http://www.arkania.net/>
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
    // Eye
    SPELL_GAZE_OF_OCCUTHAR = 97028, // triggers damage every sec.
    SPELL_EYE_EXPLODE      = 96968, // 20 k dmg to all.

    // Occu'thar
    SPELL_SEARING_SHADOWS                    = 101007, // every 20 sec
    SPELL_FOCUSED_FIRE                       = 96884,  // every 15 sec, 8 sec after eyes. Casted on summon.
    SPELL_FOCUSED_FIRE_SUMMON                = 96873,  // summon.
    SPELL_EYES_OF_OCCUTHAR                   = 101006, // cast time, 1 per minute
    SPELL_EYES_OF_OCCUTHAR_DUMMY             = 96932,  // visual,  boss->players.
    SPELL_BERSERK                            = 47008,
};

class boss_occuthar : public CreatureScript
{
    public:
        boss_occuthar() : CreatureScript("boss_occuthar") {}

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_occutharAI(pCreature);
        }
            
        struct boss_occutharAI : public ScriptedAI
        {
            boss_occutharAI(Creature* pCreature) : ScriptedAI(pCreature), summons(me)
            {
                m_pInstance = pCreature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiSearingShadowsTimer;
            uint32 m_uiFocusedFireTimer;
            uint32 focusTimer;
            uint32 m_uiEyesOfOccutharTimer;
            uint32 m_uiEyesTimer;
            uint32 m_uiBerserkTimer;
            SummonList summons;
            bool eyes, focus;

            void Reset()
            {
                if (m_pInstance)
                   m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove

                summons.DespawnAll();

                if (me->HasAura(47008))
                    me->RemoveAura(47008);

                m_uiSearingShadowsTimer  = 20000;
                m_uiFocusedFireTimer     = 15000;
                m_uiEyesOfOccutharTimer  = 7000;
                m_uiBerserkTimer         = 300000;
                eyes = false;
                focus = false;
            }

            void EnterCombat(Unit* pWho)
            {
                if (m_pInstance)
                   m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add

                m_uiSearingShadowsTimer  = 20000;
                m_uiFocusedFireTimer     = 15000;
                m_uiEyesOfOccutharTimer  = 7000;
                m_uiBerserkTimer         = 300000;
                eyes = false;
                focus = false;
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

                if (m_uiEyesOfOccutharTimer <= uiDiff)
                {
                    DoCast(me, SPELL_EYES_OF_OCCUTHAR);
                    m_uiEyesTimer = 2100;
                    eyes = true;

                    m_uiEyesOfOccutharTimer = urand(55000, 65000);
                }
                else
                    m_uiEyesOfOccutharTimer -= uiDiff;

                if (m_uiEyesTimer <= uiDiff && eyes == true)
                {
                       std::list<Unit*> targetList;
                       {
                        ThreatContainer::StorageType const &threatlist = me->getThreatManager().getThreatList();
                        for (ThreatContainer::StorageType::const_iterator itr = threatlist.begin(); itr != threatlist.end(); ++itr)
                            if ((*itr)->GetTarget()->GetTypeId() == TYPEID_PLAYER)
                                targetList.push_back((*itr)->GetTarget());
                        }

                         for (std::list<Unit*>::iterator itr = targetList.begin(); itr != targetList.end(); ++itr)
                        {
                            DoCast(*itr, SPELL_EYES_OF_OCCUTHAR_DUMMY);
                            me->SummonCreature(56369, (*itr)->GetPositionX(), (*itr)->GetPositionY(), (*itr)->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 10400);
                        }

                    m_uiFocusedFireTimer += 8000;
                    eyes = false;
                }
                else
                    m_uiEyesTimer -= uiDiff;

                if (m_uiSearingShadowsTimer <= uiDiff)
                {
                    DoCast(me->GetVictim(), SPELL_SEARING_SHADOWS);
                    m_uiSearingShadowsTimer = 20000;
                }
                else
                    m_uiSearingShadowsTimer -= uiDiff;

                if (m_uiFocusedFireTimer <= uiDiff)
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
                    DoCast(target, SPELL_FOCUSED_FIRE_SUMMON);

                    m_uiFocusedFireTimer = 15000;
                    focusTimer = 200;
                    focus = true;
                }
                else
                    m_uiFocusedFireTimer -= uiDiff;

                if (focusTimer <= uiDiff && focus == true)
                {
                    if (Creature* focus = me->FindNearestCreature(52369, 500.f))
                    DoCast(focus, SPELL_FOCUSED_FIRE);

                    focus = false;
                }
                else
                    focusTimer -= uiDiff;

                if (m_uiBerserkTimer <= uiDiff)
                    DoCast(me, SPELL_BERSERK);
                else
                    m_uiBerserkTimer -= uiDiff;
                    
                DoMeleeAttackIfReady();
            }
        };
};

class npc_occuthar_eye : public CreatureScript
{
    public:
        npc_occuthar_eye() : CreatureScript("npc_occuthar_eye") {}

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_occuthar_eyeAI(pCreature);
        }
            
        struct npc_occuthar_eyeAI : public ScriptedAI
        {
            npc_occuthar_eyeAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                m_pInstance = pCreature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiGazeTimer;
            uint32 m_uiExplodeTimer;
            bool gaze;

            void Reset()
            {
                gaze = true;
                m_uiGazeTimer = 100;
            }

            void EnterCombat(Unit* pWho)
            {
                gaze = true;
                m_uiGazeTimer = 100;
            }

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (m_uiGazeTimer <= uiDiff && gaze == true)
                {
                    if (Unit* target = me->FindNearestPlayer(10.0f, true))
                    {
                        DoCast(target, SPELL_GAZE_OF_OCCUTHAR);
                        DoCast(target, 68985);
                    }
                    m_uiExplodeTimer = 10100;
                    gaze = false;
                }
                else
                    m_uiGazeTimer -= uiDiff;

                if (m_uiExplodeTimer <= uiDiff)
                {
                    DoCast(me, SPELL_EYE_EXPLODE);
                    me->DespawnOrUnsummon(100);
                }
            }
        };
};

void AddSC_boss_occuthar()
{
    new boss_occuthar();
    new npc_occuthar_eye();
}