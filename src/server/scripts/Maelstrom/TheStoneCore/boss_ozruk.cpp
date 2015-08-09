/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * THIS particular file is NOT free software; third-party users should 
 * NOT have access to it, redistribute it or modify it.
 * We need to think up a better copyright than this. Who's your third party
 * on the net dude, dude? Should NOT? Er must nicht!
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "stonecore.h"
#include "Vehicle.h"
#include "Unit.h"
#include "ScriptedEscortAI.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "CombatAI.h"
#include "PassiveAI.h"
#include "ObjectMgr.h"
#include "SpellInfo.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"
#include "CreatureTextMgr.h"
#include "Vehicle.h"
#include "VehicleDefines.h"
#include "Spell.h"
#include "Player.h"
#include "Map.h"
#include "InstanceScript.h"
/***Note: Spell 78807 and 92426 - requires range in 15 yd ***/
/***Note: Spell 92427 - requires pre-cast so that 92426 works - 94661 damage***/
enum Yells
{
    OZRUK_AGGRO    = 1,
    OZRUK_SHIELD,
    OZRUK_KILL,
    OZRUK_DEATH,
    WARNING_SLAM,
    WARNING_SHAT,
};

enum Spells
{    
    SPELL_GROUND_SLAM  = 78903,  //Very violent. GTFO.
    SPELL_RUPTURE      = 80803,  //This - is implemented a little hacky.
    SPELL_RUPTURE_DMG  = 92381,
    SPELL_RUPTURE_SPK  = 92383,

    SPELL_ELEM_BULKWAR = 78939,
    SPELL_ELEM_SPIKE   = 78835,
    SPELL_SHATTER      = 78807,
    SPELL_PARALYZE     = 92426,
    SPELL_PARALYZE_DMG = 94611,
};

enum Events
{
    EVENT_GROUND_SLAM,
    EVENT_ELEM_BULKWAR,
    EVENT_ELEM_SPIKE,
    EVENT_SHATTER,
    EVENT_PARALYZE,
    EVENT_PARALYZE_DAMAGE,
};

enum Creatures
{
    NPC_RUPTURE   = 49597,
};

/*** Note: Doors are unknown. ***/

class boss_ozruk : public CreatureScript
{
    public:
        boss_ozruk() : CreatureScript("boss_ozruk") { }

        struct boss_ozrukAI : public BossAI
        {
            boss_ozrukAI(Creature* creature) : BossAI(creature, BOSS_OZRUK)
            {
                instance = me->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;

            void Reset()
            {
                events.Reset();

                if (instance)
                    instance->SetBossState(BOSS_OZRUK, NOT_STARTED);

                summons.DespawnAll();
            }

            void EnterEvadeMode()
            {
                me->GetMotionMaster()->MoveTargetedHome();
                events.Reset();

                if (instance)
                {
                    instance->SetBossState(BOSS_OZRUK, FAIL);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove

                    instance->HandleGameObject(0000000, true); // Open the doors.
                    instance->HandleGameObject(0000000, true);
                }
            }

            void JustDied(Unit* /*killer*/)
            {
                if (instance)
                {
                    instance->SetBossState(BOSS_OZRUK, DONE);

                    instance->HandleGameObject(0000000, true); // Open the doors.
                    instance->HandleGameObject(0000000, true);

                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
                }
            }

            void EnterCombat(Unit* /*who*/)
            {
                if (instance)
                {
                    instance->SetBossState(BOSS_OZRUK, IN_PROGRESS);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add

                    instance->HandleGameObject(0000000, false); // Close the doors.
                    instance->HandleGameObject(0000000, false);
                }

                events.ScheduleEvent(EVENT_GROUND_SLAM, 7000);
                events.ScheduleEvent(EVENT_ELEM_BULKWAR, 4000);
                events.ScheduleEvent(EVENT_ELEM_SPIKE, 12000);
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                    while (uint32 eventId = events.ExecuteEvent())
                    {
                        switch (eventId)
                        {       
                            case EVENT_GROUND_SLAM:
                                DoCastVictim(SPELL_GROUND_SLAM);
                                events.ScheduleEvent(EVENT_GROUND_SLAM, urand(10000, 12000));
                                break;
                                
                            case EVENT_ELEM_BULKWAR:
                                DoCast(me, SPELL_ELEM_BULKWAR);
                                events.ScheduleEvent(EVENT_ELEM_BULKWAR, urand(7000, 11000));
                                break;

                            case EVENT_ELEM_SPIKE:
                                DoCast(me, SPELL_ELEM_SPIKE);
                                if(IsHeroic())
                                {
                                    events.ScheduleEvent(EVENT_PARALYZE, 9500);
                                    me->AddAura(92427, me);
                                }
                                events.ScheduleEvent(EVENT_SHATTER, 10000);
                                break;
                                
                            case EVENT_PARALYZE:
                                DoCastAOE(SPELL_PARALYZE);
                                events.ScheduleEvent(EVENT_PARALYZE_DAMAGE, 7500);
                                break;

                            case EVENT_SHATTER:
                                DoCastAOE(SPELL_SHATTER);
                                events.ScheduleEvent(EVENT_ELEM_SPIKE, urand(12000, 15000));
                                break;
                                
                            case EVENT_PARALYZE_DAMAGE:
                                if (me->GetVictim())
                                {
                                    std::list<HostileReference*> t_list = me->getThreatManager().getThreatList();
                                    for (std::list<HostileReference*>::const_iterator itr = t_list.begin(); itr!= t_list.end(); ++itr)
                                    {
                                        Unit* target = Unit::GetUnit(*me, (*itr)->getUnitGuid());
                                        if (target && target->HasAura(SPELL_PARALYZE))
                                        {
                                            target->CastSpell(target, SPELL_PARALYZE_DMG, true);
                                        }
                                    }
                                }       
                        }
                    }

                    DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_ozrukAI(creature);
        }
};

class npc_rupture : public CreatureScript // 51422
{
public:
    npc_rupture() : CreatureScript("npc_rupture") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ruptureAI (creature);
    }

    struct npc_ruptureAI : public ScriptedAI
    {
        npc_ruptureAI(Creature* creature) : ScriptedAI(creature)
        {
            timerAura    = 100;
            creature->SetReactState(REACT_PASSIVE);
        }

        uint32 timerAura;
        
        void EnterCombat(Unit* /*who*/)
        {
                me->SetSpeed(MOVE_RUN, 0.8f);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_PASSIVE);
                me->SetInCombatWithZone();
                float x, y, z;
                me->GetClosePoint(x, y, z, me->GetObjectSize() / 3, 100.0f);
                me->GetMotionMaster()->MovePoint(1, x, y, z);
                me->DespawnOrUnsummon(6000);
        }

        void UpdateAI(uint32 diff)
        {
            if (timerAura <= diff)
            {
            if (Unit* target = me->GetVictim())
                if (target && target->IsWithinDistInMap(me, 2.0f))
                {
                    DoCast(target, SPELL_RUPTURE_DMG);
                    DoCast(target, SPELL_RUPTURE_SPK);
                }
                timerAura = 500;
            } else timerAura -= diff;
        }
    };
};
/*
class spell_ozruk_paralyze : public SpellScriptLoader
{
    public:
        spell_ozruk_paralyze() :  SpellScriptLoader("spell_ozruk_paralyze") { }

        class spell_ozruk_paralyze_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_ozruk_paralyze_AuraScript);

            void OnRemove(AuraEffect const* / *aurEff* /, AuraEffectHandleModes / *mode* /)
            {
                switch (GetTargetApplication()->GetRemoveMode())
                {
                    case AURA_REMOVE_BY_ENEMY_SPELL:
                        break;
                    case AURA_REMOVE_BY_EXPIRE:
                        GetTarget()->CastSpell(GetTarget(), 94661, true);
                        break;
                    case AURA_REMOVE_BY_DEATH:
                        break;
                    default:
                        return;
                }
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_ozruk_paralyze_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_ozruk_paralyze_AuraScript();
        }
};*/
    
void AddSC_boss_ozruk()
{
    new boss_ozruk();
    new npc_rupture();
}
