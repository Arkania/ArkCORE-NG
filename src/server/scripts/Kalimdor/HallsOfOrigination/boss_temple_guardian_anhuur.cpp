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

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "GameObjectAI.h"
#include "GridNotifiers.h"
#include "Player.h"
#include "halls_of_origination.h"

enum Spells
{
    SPELL_TELEPORT = 74969, // Teleport on phase switch
    SPELL_SHIELD_OF_LIGHT = 74938,
    SPELL_SHIELD_VISUAL_2 = 74930,
    SPELL_DIVINE_RECKONING_NORMAL = 75592,
    SPELL_DIVINE_RECKONING_HEROIC = 75591,
    SPELL_REVERBERATING_HYMN = 75322,
    SPELL_BURNING_LIGHT_1 = 75115, // trigger 75114
    SPELL_BURNING_LIGHT_2 = 75194,  // trigger 75116
    SPELL_BURNING_LIGHT_NORMAL10 = 75117,
    SPELL_BURNING_LIGHT_NORMAL25 = 94951,
    SPELL_BEAM_LEFT = 83697,
    SPELL_BEAM_RIGHT = 83698,
    SPELL_BEAM_OPEN = 68398,
    SPELL_DISABLE_BEACON_BEAM_LEFT = 76606,
    SPELL_DISABLE_BEACON_BEAM_RIGHT = 76608,
};

enum Quotes
{
    SAY_AGGRO,
    SAY_SHIELD,
    SAY_DEATH,
    SAY_SLAY,
    EMOTE_SHIELD,
    EMOTE_SHIELD_REMOVED
};

enum Events
{
    EVENT_DIVINE_RECKONING = 1,
    EVENT_BURNING_LIGHT = 2,
};

enum Entities
{
    GO_BEACON_OF_LIGHT_LEVER_LEFT = 207218,
    GO_BEACON_OF_LIGHT_LEVER_RIGHT = 207219,
    GO_BEACON_OF_LIGHT_LIGHT_LEFT = 203133,
    GO_BEACON_OF_LIGHT_LIGHT_RIGHT = 203136,    
};

enum MiscData
{
    DATA_SHIELD = 1,
};

enum Phases
{
    PHASE_LOADED = 0,
    PHASE_NORMAL = 1,
    PHASE_SHIELDED = 2,
};

class boss_temple_guardian_anhuur : public CreatureScript
{
public:
    boss_temple_guardian_anhuur() : CreatureScript("boss_temple_guardian_anhuur") {}

    struct boss_temple_guardian_anhuurAI : public BossAI
    {
        boss_temple_guardian_anhuurAI(Creature * creature) : BossAI(creature, DATA_TEMPLE_GUARDIAN_ANHUUR) {} // DATA_TEMPLE_GUARDIAN_ANHUUR_EVENT

        Creature*   _StalkerOnBeam[2];  //left=0 right=1
        Creature*   _StalkerOnTribun[4];
        Creature*   _StalkerOnEyesFront[4];
        Creature*   _StalkerOnEyesRear[4];
        Creature*   _StalkerOnShield[4];
        GameObject* _LeverLeft;
        GameObject* _LeverRight;

        uint32    _Phase;
        bool      _BeaconLeft, _BeaconRight;

        // called from spell 76606/76608
        void SetData(uint32 type, uint32 data)
        {
            if (events.IsInPhase(PHASE_NORMAL) || type != DATA_SHIELD)
                return;

            if (data == SPELL_DISABLE_BEACON_BEAM_RIGHT)
            {
                _BeaconRight = true;
                _StalkerOnBeam[1]->RemoveAura(SPELL_BEAM_RIGHT);
                _LeverRight->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
            }
            else if (data == SPELL_DISABLE_BEACON_BEAM_LEFT)
            {
                _BeaconLeft = true;
                _StalkerOnBeam[0]->RemoveAura(SPELL_BEAM_LEFT);
                _LeverLeft->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
            }

            if (_BeaconLeft && _BeaconRight)
            {
                Talk(EMOTE_SHIELD_REMOVED);
                EndShieldEvent();
            }
        }

        void SpawnSummons()
        {
            _StalkerOnBeam[0] = me->SummonCreature(NPC_CAVE_IN_STALKER, -603.5f, 334.3f, 65.39f, 3.12414f);
            _StalkerOnBeam[1] = me->SummonCreature(NPC_CAVE_IN_STALKER, -678.1f, 334.3f, 64.90f, 0.24434f);
            _StalkerOnTribun[0] = me->SummonCreature(NPC_CAVE_IN_STALKER, -656.4f, 319.0f, 85.6f, 0.768f);
            _StalkerOnTribun[1] = me->SummonCreature(NPC_CAVE_IN_STALKER, -656.4f, 350.3f, 85.6f, 5.428f);
            _StalkerOnTribun[2] = me->SummonCreature(NPC_CAVE_IN_STALKER, -625.4f, 319.3f, 85.6f, 2.391f);
            _StalkerOnTribun[3] = me->SummonCreature(NPC_CAVE_IN_STALKER, -625.4f, 350.6f, 85.6f, 3.979f);
            _StalkerOnShield[0] = me->SummonCreature(NPC_CAVE_IN_STALKER, -657.8f, 325.0f, 92.6f, 0.0f);
            _StalkerOnShield[1] = me->SummonCreature(NPC_CAVE_IN_STALKER, -657.8f, 338.3f, 92.6f, 0.0f);
            _StalkerOnShield[2] = me->SummonCreature(NPC_CAVE_IN_STALKER, -624.0f, 325.0f, 92.6f, 3.14f);
            _StalkerOnShield[3] = me->SummonCreature(NPC_CAVE_IN_STALKER, -624.0f, 338.3f, 92.6f, 3.14f);
            _StalkerOnEyesFront[0] = me->SummonCreature(NPC_CAVE_IN_STALKER, -662.21f, 373.78f, 101.628f, 0.0873f);
            _StalkerOnEyesFront[1] = me->SummonCreature(NPC_CAVE_IN_STALKER, -661.816f, 368.4965f, 101.7023f, 0.314f);
            _StalkerOnEyesFront[2] = me->SummonCreature(NPC_CAVE_IN_STALKER, -619.62f, 373.23f, 102.70f, 3.037f);
            _StalkerOnEyesFront[3] = me->SummonCreature(NPC_CAVE_IN_STALKER, -619.54f, 368.26f, 102.65f, 2.827f);
            _StalkerOnEyesRear[0] = me->SummonCreature(NPC_CAVE_IN_STALKER, -662.53f, 301.94f, 102.85f, 6.231f);
            _StalkerOnEyesRear[1] = me->SummonCreature(NPC_CAVE_IN_STALKER, -662.13f, 296.63f, 102.78f, 0.192f);
            _StalkerOnEyesRear[2] = me->SummonCreature(NPC_CAVE_IN_STALKER, -619.46f, 301.64f, 102.96f, 3.351f);
            _StalkerOnEyesRear[3] = me->SummonCreature(NPC_CAVE_IN_STALKER, -619.06f, 296.11f, 102.91f, 3.142f);
            _LeverLeft = me->FindNearestGameObject(GO_BEACON_OF_LIGHT_LEVER_LEFT, 50.0f);
            _LeverRight = me->FindNearestGameObject(GO_BEACON_OF_LIGHT_LEVER_RIGHT, 50.0f);
        }

        void Reset() override
        {    
            _Phase = 0;
            _StalkerOnBeam[0] = 0;
            _StalkerOnBeam[1] = 0;
            for (uint32 c = 0; c < 4; c++)
            {
                _StalkerOnTribun[c] = 0;
                _StalkerOnEyesFront[c] = 0;
                _StalkerOnEyesRear[c] = 0;
                _StalkerOnShield[c] = 0;
            }
            _Reset();
            SpawnSummons();
            _BeaconLeft = false;
            _BeaconRight = false;
            SetLeversAreSelectableFlag(false);
        }
        
        void SetLeversAreSelectableFlag(bool active)
        {            
                if (active)
                    _LeverLeft->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                else
                    _LeverLeft->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
            
                if (active)
                    _LeverRight->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                else
                    _LeverRight->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
        }

        void StartShieldEvent()
        {
            Talk(EMOTE_SHIELD);
            Talk(SAY_SHIELD);

            me->SetReactState(REACT_PASSIVE);
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveIdle();
            DoCast(me, SPELL_TELEPORT, true);

            events.SetPhase(PHASE_SHIELDED);
            DoCast(me, SPELL_SHIELD_VISUAL_2, true);
            DoCast(me, SPELL_SHIELD_OF_LIGHT, true);
            DoCast(me, SPELL_REVERBERATING_HYMN, true);
            me->SetReactState(REACT_AGGRESSIVE);
            SetLeversAreSelectableFlag(true);
            
            if (_StalkerOnBeam[0] && _StalkerOnBeam[1])
            {
                _StalkerOnBeam[0]->CastSpell(me, SPELL_BEAM_LEFT, false);
                _StalkerOnBeam[1]->CastSpell(me, SPELL_BEAM_RIGHT, false);
            }
        }

        void EndShieldEvent()
        {
            me->RemoveAurasDueToSpell(SPELL_REVERBERATING_HYMN);
            me->RemoveAurasDueToSpell(SPELL_SHIELD_VISUAL_2);
            me->RemoveAurasDueToSpell(SPELL_SHIELD_OF_LIGHT);
            _StalkerOnBeam[0]->RemoveAura(SPELL_BEAM_LEFT);
            _StalkerOnBeam[1]->RemoveAura(SPELL_BEAM_RIGHT);
            SetLeversAreSelectableFlag(false);
            events.SetPhase(PHASE_NORMAL);
            _BeaconLeft = false;
            _BeaconRight = false;
        }

        void EnterCombat(Unit * /*who*/) override
        {
            Talk(SAY_AGGRO);
            events.ScheduleEvent(EVENT_DIVINE_RECKONING, 8000, 0, PHASE_NORMAL);
            events.ScheduleEvent(EVENT_BURNING_LIGHT, 10000, 0, PHASE_NORMAL);
            _EnterCombat();
        }

        void JustDied(Unit * killer) override
        {
            Talk(SAY_DEATH);
            BossAI::JustDied(killer);
        }

        void KilledUnit(Unit *) override
        {
            Talk(SAY_SLAY);
        }

        void DamageTaken(Unit * done_by, uint32 &damage) override
        {
            if (me->HasAura(SPELL_SHIELD_OF_LIGHT))
            {
                if (!me->HasAura(SPELL_REVERBERATING_HYMN))
                    DoCast(me, SPELL_REVERBERATING_HYMN, true);

                damage = 0;
                return;
            }
            else
            {
                if (_LeverLeft->HasFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE))
                    _LeverLeft->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);

                if (_LeverRight->HasFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE))
                    _LeverRight->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);

                if (_StalkerOnBeam[0]->HasAura(SPELL_BEAM_LEFT))
                    _StalkerOnBeam[0]->RemoveAura(SPELL_BEAM_LEFT);

                if (_StalkerOnBeam[1]->HasAura(SPELL_BEAM_RIGHT))
                    _StalkerOnBeam[1]->RemoveAura(SPELL_BEAM_RIGHT);
            }

            if (me->GetHealthPct() <= 66.0f && _Phase == 0)
            {
                _Phase = 1;
                StartShieldEvent();
            }
            if (me->GetHealthPct() <= 33.0f && _Phase == 1)
            {
                _Phase = 2;
                StartShieldEvent();
            }
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);

            if (!UpdateVictim())
                return;

            if (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_DIVINE_RECKONING:
                    if (!me->HasUnitState(UNIT_STATE_CASTING))
                    {
                        Unit * target = SelectTarget(SELECT_TARGET_RANDOM, 1, 50.0f, true);
                        if (!target)
                            target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true);
                        if (target)
                            DoCast(target, SPELL_DIVINE_RECKONING_NORMAL);
                    }
                    events.ScheduleEvent(EVENT_DIVINE_RECKONING, urand(10000, 12000), 0, PHASE_NORMAL);
                    break;
                case EVENT_BURNING_LIGHT:
                    if (!me->HasUnitState(UNIT_STATE_CASTING))
                    {
                        Unit * target = SelectTarget(SELECT_TARGET_RANDOM, 1, 50.0f, true);
                        if (!target)
                            target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true);
                        if (target)
                        {
                            DoCast(target, SPELL_BURNING_LIGHT_1, true);
                        }
                    }
                    events.ScheduleEvent(EVENT_BURNING_LIGHT, urand(10000, 15000), 0, PHASE_NORMAL);
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_temple_guardian_anhuurAI(creature);
    }
};

// spell 76606 and 76608
class spell_disable_beacon_beams : public SpellScriptLoader
{
public:
    spell_disable_beacon_beams() : SpellScriptLoader("spell_disable_beacon_beams") {}

    class spell_disable_beacon_beams_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_disable_beacon_beams_SpellScript)
        
        void HandleScript(SpellEffIndex /*effIndex*/)
        {
            if (Unit * caster = GetCaster())
            {                
                if (Creature * boss = caster->FindNearestCreature(BOSS_TEMPLE_GUARDIAN_ANHUUR, 100.0f))
                    boss->AI()->SetData(DATA_SHIELD, GetSpellInfo()->Id);
            }
        }
       
        void Register()
        {
            OnEffectLaunch += SpellEffectFn(spell_disable_beacon_beams_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_disable_beacon_beams_SpellScript();
    }
};

void AddSC_boss_temple_guardian_anhuur()
{
    new boss_temple_guardian_anhuur();
    new spell_disable_beacon_beams();
}
