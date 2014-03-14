#include "ScriptPCH.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "WorldPacket.h"

enum Yells
{
  SAY_AGGRO    = 0, // I hate adventurers!
  SAY_DIED     = 1, // I hate... every.. one of you!
  SAY_KILL     = 2, // I didn't hate that.
  SAY_SEETHING = 3, // My hate will consume you!
  SAY_SKEWER   = 4, // Feel my hatred!
  SAY_DANCE    = 5, // I hate standing still!
  SAY_BERSERK  = 6, // I hate you all!
  SAY_RESET    = 7, // I hate incompetent raiders.
  SAY_INTRO    = 8, // How I hate this place. My captors may be long dead.. but don't think I won't take it out on you, miserable treasure hunters!

  SAY_BLADES   = -1900027  // Announce raid for Blade Dance.
};

enum Spells
{
    SPELL_BLADE_DANCE                        = 105784, // root and trigger. 3 times during dummy, moves to another target each time. 4 sec.x3 = 12 sec dummy.
    SPELL_BLADE_DANCE_DUMMY                  = 105828,
    SPELL_SEETHING_HATE                      = 105067, // triggers every 3 sec.
    SPELL_SKEWER                             = 104936, // on tank.
    SPELL_BERSERK                            = 47008
};

class boss_alizabal : public CreatureScript
{
    public:
        boss_alizabal() : CreatureScript("boss_alizabal") {}

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_alizabalAI(pCreature);
        }
            
        struct boss_alizabalAI : public ScriptedAI
        {
            boss_alizabalAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                m_pInstance = pCreature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiBladeDanceTimer;
            uint32 m_uiSkewerTimer;
            uint32 m_uiSeethingHateTimer;
            uint32 m_uiBerserkTimer;
            uint32 m_uiSkewerorSeethingTimer;
            uint32 skewerTimer;
            uint32 seethingTimer;
            uint32 moveTimer;
            uint32 danceTimer;
            uint32 removeDanceTimer;
            bool bladedance, skewerorseething, seething, skewer, intro;

            void Reset()
            {
                if (m_pInstance)
                   m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove

                 if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == POINT_MOTION_TYPE)
                     me->GetMotionMaster()->MovementExpired();

                if (me->HasAura(47008))
                    me->RemoveAura(47008);

                Talk(SAY_RESET);
                m_uiSkewerorSeethingTimer = urand(6000, 8000);   // 8 sec after blade dance.
                m_uiBladeDanceTimer       = urand(25000, 40000);  // then 60 sec.
                m_uiBerserkTimer          = 300000; // 5 min.

                bladedance = false;
                intro      = false;
                skewerorseething = true;
            }

            void MoveInLineOfSight(Unit* who)
            {
                if (!intro && who->IsWithinDistInMap(me, 50.0f))
                {
                    Talk(SAY_INTRO);
                    intro = true;
                }
            }
            
            void EnterCombat(Unit* who)
            {
                if (m_pInstance)
                   m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add

                Talk(SAY_AGGRO);
                m_uiSkewerorSeethingTimer = urand(6000, 8000);  // 8 sec after blade dance.
                m_uiBladeDanceTimer       = urand(25000, 40000);  // then 60 sec.
                m_uiBerserkTimer          = 300000; // 5 min.

                bladedance = false;
                skewerorseething = true;
            }

            void JustDied(Unit* killer)
            {
               Talk(SAY_DIED);

                if (m_pInstance)
                   m_pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            void KilledUnit(Unit * /*victim*/)
            {
                Talk(SAY_KILL);
            }

            void EnterEvadeMode() // AKA Wipe.
            {
                if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == POINT_MOTION_TYPE)
                    me->GetMotionMaster()->MovementExpired();

                if (me->HasAura(47008))
                    me->RemoveAura(47008);

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

                if (m_uiSkewerorSeethingTimer <= uiDiff && skewerorseething == true)
                {
                    switch(urand(0, 1))
                    {
                        case 0:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
                        {
                            DoCast(target, SPELL_SEETHING_HATE);
                            Talk(SAY_SEETHING);
                            seething = true;
                            skewerTimer = 8000;
                        }
                        break;
                        case 1:
                            DoCast(me->GetVictim(), SPELL_SKEWER);
                            Talk(SAY_SKEWER);
                            skewer = true;
                            seethingTimer = 8000;
                            break;
                       }

                    skewerorseething = false;
                }
                else
                    m_uiSkewerorSeethingTimer -= uiDiff;

                if (skewerTimer <= uiDiff && seething == true)
                {
                    DoCast(me->GetVictim(), SPELL_SKEWER);
                    Talk(SAY_SKEWER);
                    seething = false;
                }
                else
                    skewerTimer -= uiDiff;

                if (seethingTimer <= uiDiff && skewer == true)
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
                    {
                        DoCast(target, SPELL_SEETHING_HATE);
                        Talk(SAY_SEETHING);
                        skewer = false;
                    }
                }
                else
                    seethingTimer -= uiDiff;

                if (m_uiBladeDanceTimer <= uiDiff)
                {
                    DoScriptText(SAY_BLADES, me);
                    Talk(SAY_DANCE);
                    DoCast(me, SPELL_BLADE_DANCE_DUMMY);
                    bladedance = true;
                    moveTimer= 100;
                    removeDanceTimer = 13000;
                    danceTimer = 400;

                    m_uiBladeDanceTimer = 60000;
                }
                else
                    m_uiBladeDanceTimer -= uiDiff;

                if (moveTimer <= uiDiff && bladedance == true)
                {
                    me->SetSpeed(MOVE_WALK, 4.0f);
                    me->SetSpeed(MOVE_RUN, 4.0f);

                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
                        me->GetMotionMaster()->MovePoint(1,target->GetPositionX(),target->GetPositionY(),target->GetPositionZ());

                    moveTimer  = 4200;
                }
                else
                    moveTimer -= uiDiff;

                if (danceTimer <= uiDiff && bladedance == true)
                {
                    danceTimer = 4300;
                    DoCast(me, SPELL_BLADE_DANCE);
                }
                else
                    danceTimer -= uiDiff;

                if (removeDanceTimer <= uiDiff && bladedance == true)
                {
                    if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == POINT_MOTION_TYPE)
                        me->GetMotionMaster()->MovementExpired();

                    me->GetMotionMaster()->MoveChase(me->GetVictim());

                    me->SetSpeed(MOVE_WALK, 1.0f);
                    me->SetSpeed(MOVE_RUN, 1.14f);

                    me->RemoveAura(SPELL_BLADE_DANCE);
                    me->RemoveAura(SPELL_BLADE_DANCE_DUMMY);
                    bladedance = false;
                    skewerorseething = true;
                    m_uiSkewerorSeethingTimer = 8000;
                }
                else
                    removeDanceTimer -= uiDiff;

                if (m_uiBerserkTimer <= uiDiff)
                {
                    DoCast(me, SPELL_BERSERK);
                    Talk(SAY_BERSERK);

                    m_uiBerserkTimer = 2400000; // just assuming they get over first one...heh.
                }
                else
                    m_uiBerserkTimer -= uiDiff;
                    
                DoMeleeAttackIfReady();
            }
        };
};

void AddSC_boss_alizabal()
{
    new boss_alizabal();
}