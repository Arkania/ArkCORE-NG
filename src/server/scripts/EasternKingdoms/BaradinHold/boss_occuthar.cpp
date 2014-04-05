#include "ScriptPCH.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
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

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_occutharAI(creature);
        }
            
        struct boss_occutharAI : public ScriptedAI
        {
            boss_occutharAI(Creature* creature) : ScriptedAI(creature), summons(me)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            uint32 SearingShadowsTimer;
            uint32 FocusedFireTimer;
            uint32 focusTimer;
            uint32 EyesOfOccutharTimer;
            uint32 EyesTimer;
            uint32 BerserkTimer;
            SummonList summons;
            bool eyes, focus;

            void Reset()
            {
                if (instance)
                   instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove

                summons.DespawnAll();

                if (me->HasAura(47008))
                    me->RemoveAura(47008);

                SearingShadowsTimer  = 20000;
                FocusedFireTimer     = 15000;
                EyesOfOccutharTimer  = 7000;
                BerserkTimer         = 300000;
                eyes = false;
                focus = false;
            }

            void EnterCombat(Unit* pWho)
            {
                if (instance)
                   instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add

                SearingShadowsTimer  = 20000;
                FocusedFireTimer     = 15000;
                EyesOfOccutharTimer  = 7000;
                BerserkTimer         = 300000;
                eyes = false;
                focus = false;
            }

            void EnterEvadeMode() // AKA Wipe.
            {
			    me->GetMotionMaster()->MoveTargetedHome();
                me->SetHealth(me->GetMaxHealth());

                if (me->HasAura(47008))
                    me->RemoveAura(47008);
					
                if (instance)
                   instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            void JustDied(Unit* killer)
            {
                if (instance)
                   instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            void JustSummoned(Creature* summon)
            {
                summons.push_back(summon->GetGUID());
                DoZoneInCombat(summon);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

				if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (EyesOfOccutharTimer <= diff)
                {
                    DoCast(me, SPELL_EYES_OF_OCCUTHAR);
                    EyesTimer = 2100;
                    eyes = true;

                    EyesOfOccutharTimer = urand(55000, 65000);
                }
                else
                    EyesOfOccutharTimer -= diff;

                if (EyesTimer <= diff && eyes == true)
                {
					   std::list<Unit*> targetList;
                       {
                       const std::list<HostileReference*>& threatlist = me->getThreatManager().getThreatList();
                         for (std::list<HostileReference*>::const_iterator itr = threatlist.begin(); itr != threatlist.end(); ++itr)
                             if ((*itr)->GetTarget()->GetTypeId() == TYPEID_PLAYER)
                                targetList.push_back((*itr)->GetTarget());
                        }

                         for (std::list<Unit*>::iterator itr = targetList.begin(); itr != targetList.end(); ++itr)
                        {
                            DoCast(*itr, SPELL_EYES_OF_OCCUTHAR_DUMMY);
                            me->SummonCreature(56369, (*itr)->GetPositionX(), (*itr)->GetPositionY(), (*itr)->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 10400);
                        }

                    FocusedFireTimer += 8000;
                    eyes = false;
                }
                else
                    EyesTimer -= diff;

                if (SearingShadowsTimer <= diff)
                {
                    DoCast(me->GetVictim(), SPELL_SEARING_SHADOWS);
                    SearingShadowsTimer = 20000;
                }
                else
                    SearingShadowsTimer -= diff;

                if (FocusedFireTimer <= diff)
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
                    DoCast(target, SPELL_FOCUSED_FIRE_SUMMON);

                    FocusedFireTimer = 15000;
					focusTimer = 200;
                    focus = true;
                }
                else
                    FocusedFireTimer -= diff;

                if (focusTimer <= diff && focus == true)
                {
                    if (Creature* focus = me->FindNearestCreature(52369, 500.f))
                    DoCast(focus, SPELL_FOCUSED_FIRE);

                    focus = false;
                }
                else
                    focusTimer -= diff;

                if (BerserkTimer <= diff)
                    DoCast(me, SPELL_BERSERK);
                else
                    BerserkTimer -= diff;
                    
                DoMeleeAttackIfReady();
            }
        };
};

class npc_occuthar_eye : public CreatureScript
{
    public:
        npc_occuthar_eye() : CreatureScript("npc_occuthar_eye") {}

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_occuthar_eyeAI(creature);
        }
            
        struct npc_occuthar_eyeAI : public ScriptedAI
        {
            npc_occuthar_eyeAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            uint32 GazeTimer;
            uint32 ExplodeTimer;
            bool gaze;

            void Reset()
            {
                gaze = true;
                GazeTimer = 100;
            }

            void EnterCombat(Unit* who)
            {
                gaze = true;
                GazeTimer = 100;
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

				if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (GazeTimer <= diff && gaze == true)
                {
                    if (Unit* target = me->FindNearestPlayer(10.0f, true))
					{
                        DoCast(target, SPELL_GAZE_OF_OCCUTHAR);
                        DoCast(target, 68985);
					}
                    ExplodeTimer = 10100;
                    gaze = false;
                }
                else
                    GazeTimer -= diff;

                if (ExplodeTimer <= diff)
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