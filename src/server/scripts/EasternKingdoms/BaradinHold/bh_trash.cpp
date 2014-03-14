#include "ScriptPCH.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "WorldPacket.h"

enum Spells
{
 SPELL_GAZE_OF_OCCUTHAR = 97028,
 SPELL_EYE_EXPLODE      = 101008,
 SPELL_WHIRL_OF_BLADES  = 105855,
 SPELL_RUN_THROUGH      = 105859
};

#define SPELL_REPELLENT_RAY                   RAID_MODE(89348, 95178)

class npc_containment_unit : public CreatureScript
{
    public:
        npc_containment_unit() : CreatureScript("npc_containment_unit") {}

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_containment_unitAI(pCreature);
        }
            
        struct npc_containment_unitAI : public ScriptedAI
        {
            npc_containment_unitAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                m_pInstance = pCreature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiRepellentRayTimer;

            void Reset()
            {
                m_uiRepellentRayTimer = 10000;
            }

            void EnterCombat(Unit* pWho)
            {
                m_uiRepellentRayTimer = 10000;
            }

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (m_uiRepellentRayTimer <= uiDiff)
                {
                    DoCastAOE(SPELL_REPELLENT_RAY);
                    m_uiRepellentRayTimer = urand(10000, 20000);
                }
                else
                    m_uiRepellentRayTimer -= uiDiff;

                DoMeleeAttackIfReady();
            }
        };
};

class npc_disciple_of_hate : public CreatureScript
{
    public:
        npc_disciple_of_hate() : CreatureScript("npc_disciple_of_hate") {}

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_disciple_of_hateAI(pCreature);
        }
            
        struct npc_disciple_of_hateAI : public ScriptedAI
        {
            npc_disciple_of_hateAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                m_pInstance = pCreature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiWhirlingBladesTimer;
            uint32 m_uiRunThroughTimer;

            void Reset()
            {
                m_uiWhirlingBladesTimer = urand(5000, 15000);
            }

            void EnterCombat(Unit* pWho)
            {
                m_uiWhirlingBladesTimer = urand(5000, 15000);
                m_uiRunThroughTimer = urand(2000, 4000);
            }

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (m_uiWhirlingBladesTimer <= uiDiff)
                {
                    DoCast(me, SPELL_WHIRL_OF_BLADES);
                    m_uiWhirlingBladesTimer = urand(25000, 35000);
                }
                else
                    m_uiWhirlingBladesTimer -= uiDiff;

                if (m_uiRunThroughTimer <= uiDiff)
                {
                    DoCast(me->GetVictim(), SPELL_RUN_THROUGH);
                    m_uiRunThroughTimer = urand(9000, 12000);
                }
                else
                    m_uiRunThroughTimer -= uiDiff;

                DoMeleeAttackIfReady();
            }
        };
};

class npc_eye_of_occuthar : public CreatureScript
{
    public:
        npc_eye_of_occuthar() : CreatureScript("npc_eye_of_occuthar") {}

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_eye_of_occutharAI(pCreature);
        }
            
        struct npc_eye_of_occutharAI : public ScriptedAI
        {
            npc_eye_of_occutharAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                m_pInstance = pCreature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiGazeTimer;
            uint32 m_uiExplodeTimer;

            void Reset()
            {
                m_uiGazeTimer = 1000;
            }

            void EnterCombat(Unit* pWho)
            {
                m_uiGazeTimer = 1000;
            }

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (m_uiGazeTimer <= uiDiff)
                {
                    DoCast(me, SPELL_GAZE_OF_OCCUTHAR);
                    m_uiExplodeTimer = 10100;
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

void AddSC_bh_trash()
{
    new npc_containment_unit();
    new npc_eye_of_occuthar();
    new npc_disciple_of_hate();
}
