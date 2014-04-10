
#include "ScriptPCH.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "halls_of_origination.h"
#include "WorldPacket.h"

enum Yells
{
    SAY_INTRO                = 0,
    SAY_AGGRO                = 1,
    SAY_KILL                 = 2,
    SAY_OMEGA                = 3,
    SAY_DEATH                = 4
};

enum Spells
{
    // Beams NPC
    SPELL_BEAM_VISUAL                          = 91205,
    SPELL_BEAM_DMG                             = 75547,
    SPELL_BEAM_DMG_H                           = 89880,
    
    // Anraphet
    SPELL_BEAMS_CAST                           = 76184,
    SPELL_VISUAL_ON_BEAM                       = 76912,
    SPELL_NEMESIS_STRIKE                       = 83650,
    SPELL_NEMESIS_STRIKE_H                     = 91175,
    SPELL_CRUMBLING_RUIN                       = 75609,
    SPELL_CRUMBLING_RUIN_H                     = 91206,
    SPELL_OMEGA_STANCE_H                       = 75622,
};

enum Creatures
{
    NPC_BEAM                                   = 41144,
};

class boss_anraphet : public CreatureScript
{
    public:
        boss_anraphet() : CreatureScript("boss_anraphet") {}

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_anraphetAI(pCreature);
        }
            
        struct boss_anraphetAI : public ScriptedAI
        {
            boss_anraphetAI(Creature* pCreature) : ScriptedAI(pCreature), summons(me)
            {
                m_pInstance = pCreature->GetInstanceScript();
            }

            bool IntroDone;
            InstanceScript* m_pInstance;
            uint32 m_uiBeamsTimer;
            uint32 m_uiFirstTimer;
            uint32 m_uiSecondTimer;
            uint32 m_uiThirdTimer;
            uint32 m_uiNemesisStrikeTimer;
            uint32 m_uiCrumblingRuinTimer;
            uint32 m_uiOmegaStanceTimer;
            SummonList summons;

            Unit* victim1;
            Unit* victim2;
            Unit* victim3;

   void MoveInLineOfSight(Unit* who)
   {
       if (me->IsWithinDistInMap(who, 50.0f) && IntroDone == false)
       {
           Talk(SAY_INTRO);
           IntroDone = true;
       }
   }
            
            void Reset()
            {
                if (m_pInstance)
                    m_pInstance->SetData(DATA_ANRAPHET, NOT_STARTED);

                IntroDone = false;
                summons.DespawnAll();
                m_uiNemesisStrikeTimer = 7000;
                m_uiBeamsTimer = 10000;
                m_uiFirstTimer = 0;
                m_uiSecondTimer = 0;
                m_uiThirdTimer = 0;
                m_uiCrumblingRuinTimer = 25000;
                m_uiOmegaStanceTimer = 30000;
                m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); //Remove
            }

            void EnterCombat(Unit* pWho)
            {
                Talk(SAY_AGGRO);

                if (m_pInstance)
                    m_pInstance->SetData(DATA_ANRAPHET, IN_PROGRESS);                    
                m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);            
                GameObject* Door = me->FindNearestGameObject(GO_ANRAPHET_DOOR, 500);
                if (Door)
                    Door->SetGoState(GO_STATE_ACTIVE);

                DoZoneInCombat();
            }

            void EnterEvadeMode()
            {
                if (m_pInstance)
                    m_pInstance->SetData(DATA_ANRAPHET, FAIL);
                m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); //Remove
                summons.DespawnAll();
            }

            void KilledUnit(Unit * /*victim*/)
            {
                Talk(SAY_KILL);
            }

            void JustDied(Unit* killer)
            {
                if (m_pInstance)
                    m_pInstance->SetData(DATA_ANRAPHET, DONE);

                GameObject* Door = me->FindNearestGameObject(GO_ANRAPHET_DOOR, 500);
                if (Door)
                    Door->SetGoState(GO_STATE_ACTIVE);

                GameObject* Lift = me->FindNearestGameObject(GO_ORIGINATION_ELEVATOR, 500);
                if (Lift)
                    Lift->SetGoState(GO_STATE_ACTIVE);
                                    
                summons.DespawnAll();
                m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); //Remove                
                Talk(SAY_DEATH);
            }

            void JustSummoned(Creature* summon)
            {
                summons.push_back(summon->GetGUID());
            }

            void UpdateAI(uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (m_uiNemesisStrikeTimer <= uiDiff)
                {
                    DoCast(me->GetVictim(), IsHeroic() ? SPELL_NEMESIS_STRIKE_H : SPELL_NEMESIS_STRIKE);
                    m_uiNemesisStrikeTimer = urand(15000, 20000);
                }
                else
                    m_uiNemesisStrikeTimer -= uiDiff;
                if (m_uiBeamsTimer <= uiDiff)
                {
                    victim1 = SelectTarget(SELECT_TARGET_RANDOM, 0);
                    victim2 = SelectTarget(SELECT_TARGET_RANDOM, 0);
                    victim3 = SelectTarget(SELECT_TARGET_RANDOM, 0);

                    DoCast(me, SPELL_BEAMS_CAST);
                    //me->MonsterYell(SAY_ALPHA, LANG_UNIVERSAL, NULL);
                    m_uiFirstTimer = 3300;
                    m_uiSecondTimer = 0;
                    m_uiThirdTimer = 0;
                    m_uiBeamsTimer = 45000;
                }
                else
                    m_uiBeamsTimer -= uiDiff;
                if (m_uiFirstTimer > 0 && m_uiFirstTimer <= uiDiff)
                {
                    Creature* Beam1 = me->SummonCreature(NPC_BEAM, victim1->GetPositionX(), victim1->GetPositionY(), victim1->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN, 3000);
                    DoZoneInCombat(Beam1);
                    DoCast(Beam1, SPELL_VISUAL_ON_BEAM);
                    m_uiFirstTimer = 0;
                    m_uiSecondTimer = 3300;
                    m_uiThirdTimer = 0;
                }
                else
                    m_uiFirstTimer -= uiDiff;
                if (m_uiSecondTimer > 0 && m_uiSecondTimer <= uiDiff)
                {
                    Creature* Beam2 = me->SummonCreature(NPC_BEAM, victim2->GetPositionX(), victim2->GetPositionY(), victim2->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN, 3000);
                    DoZoneInCombat(Beam2);
                    DoCast(Beam2, SPELL_VISUAL_ON_BEAM);
                    m_uiFirstTimer = 0;
                    m_uiSecondTimer = 0;
                    m_uiThirdTimer = 3300;
                }
                else
                    m_uiSecondTimer -= uiDiff;
                if (m_uiThirdTimer > 0 && m_uiThirdTimer <= uiDiff)
                {
                    Creature* Beam3 = me->SummonCreature(NPC_BEAM, victim3->GetPositionX(), victim3->GetPositionY(), victim3->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN, 3000);
                    DoZoneInCombat(Beam3);
                    DoCast(Beam3, SPELL_VISUAL_ON_BEAM);
                    m_uiFirstTimer = 0;
                    m_uiSecondTimer = 0;
                    m_uiThirdTimer = 0;
                    m_uiNemesisStrikeTimer = 5500;
                }
                else
                    m_uiThirdTimer -= uiDiff;
                if (m_uiCrumblingRuinTimer <= uiDiff)
                {
                    std::vector<Unit*> targets;
                    std::list<HostileReference*>::const_iterator i = me->getThreatManager().getThreatList().begin();
                    for (; i != me->getThreatManager().getThreatList().end(); ++i)
                        if ((*i)->GetTarget()->GetTypeId() == TYPEID_PLAYER)
                            me->AddAura(IsHeroic() ? SPELL_CRUMBLING_RUIN_H : SPELL_CRUMBLING_RUIN, (*i)->GetTarget());

                    m_uiCrumblingRuinTimer = IsHeroic() ? 45000 : 50000;
                }
                else
                    m_uiCrumblingRuinTimer -= uiDiff;
                if (IsHeroic())
                    if (m_uiOmegaStanceTimer <= uiDiff)
                    {
                        DoCast(me->GetVictim(), SPELL_OMEGA_STANCE_H);
                        //if(urand(1, 3) == 1)
                            //me->MonsterYell(SAY_OMEGA, LANG_UNIVERSAL, NULL);
                        m_uiOmegaStanceTimer = 40000;
                    }
                    else
                        m_uiOmegaStanceTimer -= uiDiff;
                if(me->GetHealth() < me->CountPctFromMaxHealth(1.5))
                {
                    std::vector<Unit*> targets;
                    std::list<HostileReference*>::const_iterator i = me->getThreatManager().getThreatList().begin();
                    for (; i != me->getThreatManager().getThreatList().end(); ++i)
                        if ((*i)->GetTarget()->GetTypeId() == TYPEID_PLAYER && (*i)->GetTarget()->HasAura(IsHeroic() ? SPELL_CRUMBLING_RUIN_H : SPELL_CRUMBLING_RUIN))
                            (*i)->GetTarget()->RemoveAura(IsHeroic() ? SPELL_CRUMBLING_RUIN_H : SPELL_CRUMBLING_RUIN);
                }
                DoMeleeAttackIfReady();
            }
        };
};

class npc_beam : public CreatureScript
{
    public:
        npc_beam() : CreatureScript("npc_beam") {}

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_beamAI(pCreature);
        }
            
        struct npc_beamAI : public ScriptedAI
        {
            npc_beamAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                m_pInstance = pCreature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            
            void Reset()
            {
                DoCast(me, SPELL_BEAM_VISUAL);
            }

            void EnterCombat(Unit* pWho)
            {
            }

            void UpdateAI(uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;
            }
        };
};

void AddSC_boss_anraphet()
{
    new boss_anraphet();
    new npc_beam();
}
