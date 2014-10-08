/*
* Copyright (C) 2010-2011 Trinity <http://www.projecttrinity.org/>
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
    SPELL_DIVINE_RECKONING = 75592,
    SPELL_REVERBERATING_HYMN = 75322,
    SPELL_BURNING_LIGHT = 75115,
    SPELL_BURNING_LIGHT_2 = 75194,
    SPELL_BEAM_LEFT = 83697,
    SPELL_BEAM_RIGHT = 83698,

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
    NPC_ANHUUR = 39425,
    GO_LEVER_1 = 207218,
    GO_LEVER_2 = 207219,
};

enum MiscData
{
    DATA_SHIELD = 1,
};

enum Phases
{
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

        std::list<uint64> SummonList;    
        bool shielded;
        int8 stage;
        uint64 targetGUID;
        bool beacons[2];

        void Reset() override
        {
            RemoveSummons();
            shielded = false;
            stage = 0;
            targetGUID = 0;
            SetLevers(false);
            memset(&beacons, false, sizeof(beacons));
            _Reset();
        }

        void SetLevers(bool active)
        {
            if (GameObject * lever1 = me->FindNearestGameObject(GO_LEVER_1, 50.0f))
            {
                if (active)
                    lever1->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                else
                    lever1->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
            }

            if (GameObject * lever2 = me->FindNearestGameObject(GO_LEVER_2, 50.0f))
            {
                if (active)
                    lever2->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                else
                    lever2->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
            }
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
            RemoveSummons();
        }

        void KilledUnit(Unit *) override
        {
            Talk(SAY_SLAY);
        }

        void DamageTaken(Unit * done_by, uint32 &damage) override
        {
            if (shielded) // to prevent possible exploits
            {
                if (me->HasAura(SPELL_SHIELD_OF_LIGHT))
                    damage = 0;
                else
                {
                    events.SetPhase(PHASE_NORMAL);
                    me->RemoveAurasDueToSpell(SPELL_REVERBERATING_HYMN);
                    me->GetMotionMaster()->MoveChase(me->GetVictim() ? me->GetVictim() : done_by);
                    shielded = false;
                }
            }

            if (stage >= 2)
                return;

            if (me->GetHealthPct() <= (stage ? 33.0f : 66.0f))
            {
                ++stage;

                Talk(SAY_SHIELD);
                Talk(EMOTE_SHIELD);

                me->SetReactState(REACT_PASSIVE);
                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MoveIdle();
                DoCast(me, SPELL_TELEPORT, true);

                events.SetPhase(PHASE_SHIELDED);
                DoCast(me, SPELL_SHIELD_VISUAL_2, true);
                DoCast(me, SPELL_SHIELD_OF_LIGHT, true);
                DoCast(me, SPELL_REVERBERATING_HYMN, true);
                me->SetReactState(REACT_AGGRESSIVE);
                SetLevers(true);

                shielded = true;

                if (Creature *light1 = me->SummonCreature(40183, -603.465f, 334.38f, 65.4f, 3.12f, TEMPSUMMON_CORPSE_DESPAWN, 1000))
                    light1->CastSpell(me, SPELL_BEAM_LEFT, false);

                if (Creature *light2 = me->SummonCreature(40183, -678.132f, 334.212f, 64.9f, 0.24f, TEMPSUMMON_CORPSE_DESPAWN, 1000))
                    light2->CastSpell(me, SPELL_BEAM_RIGHT, false);
            }
        }

        void SetData(uint32 type, uint32 data)
        {
            if (!shielded || type != DATA_SHIELD)
                return;

            if (data == 76608)
                beacons[1] = true;
            else if (data == 76606)
                beacons[0] = true;

            if (beacons[0] && beacons[1])
            {
                me->RemoveAurasDueToSpell(SPELL_SHIELD_OF_LIGHT);
                Talk(EMOTE_SHIELD_REMOVED);
                RemoveSummons();
                memset(&beacons, false, sizeof(beacons));
            }
        }

        void RemoveSummons()
        {
            if (SummonList.empty())
                return;

            for (std::list<uint64>::const_iterator itr = SummonList.begin(); itr != SummonList.end(); ++itr)
            {
                if (Creature* pTemp = Unit::GetCreature(*me, *itr))
                    if (pTemp)
                        pTemp->DisappearAndDie();
            }
            SummonList.clear();
        }

        void JustSummoned(Creature * summon)
        {
            SummonList.push_back(summon->GetGUID());
            if (Player * player = me->GetPlayer(*me, targetGUID))
            {
                if (Creature * stalker = player->FindNearestCreature(NPC_CAVE_IN_STALKER, 100.0f))
                    stalker->CastSpell(stalker, SPELL_BURNING_LIGHT_2, true, NULL, NULL, me->GetGUID());
                summon->setFaction(14);
                targetGUID = 0;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
            if (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_DIVINE_RECKONING:
                {
                    Unit * target = SelectTarget(SELECT_TARGET_RANDOM, 1, 50.0f, true);
                    if (!target)
                        target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true);
                    if (target)
                        DoCast(target, SPELL_DIVINE_RECKONING);
                    events.ScheduleEvent(EVENT_DIVINE_RECKONING, urand(10000, 12000), 0, PHASE_NORMAL);
                }
                    break;
                case EVENT_BURNING_LIGHT:
                {
                    Unit * target = SelectTarget(SELECT_TARGET_RANDOM, 1, 50.0f, true);
                    if (!target)
                        target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true);
                    if (target)
                    {
                        targetGUID = target->GetGUID();
                        DoCast(target, SPELL_BURNING_LIGHT, true);
                    }
                    events.ScheduleEvent(EVENT_BURNING_LIGHT, urand(10000, 15000), 0, PHASE_NORMAL);
                }
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
                if (Creature * boss = caster->FindNearestCreature(NPC_ANHUUR, 100.0f))
                    boss->AI()->SetData(DATA_SHIELD, GetSpellInfo()->Id);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_disable_beacon_beams_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_disable_beacon_beams_SpellScript();
    }
};

class go_beacon_of_light : public GameObjectScript
{
    
public:
    go_beacon_of_light() : GameObjectScript("go_beacon_of_light") { }

    struct go_beacon_of_lightAI : public GameObjectAI
    {
        go_beacon_of_lightAI(GameObject* go) : GameObjectAI(go) { }

        void Reset() override
        {
            printf("Reset \n");
        }

        bool OnDummyEffect(Unit* /*caster*/, uint32 /*spellId*/, SpellEffIndex /*effIndex*/, GameObject* target) 
        { 
            printf("Reset %d \n", target->GetGUIDLow());
            return false; 
        }

        void OnLootStateChanged(GameObject* go, uint32 /*state*/, Unit* /*unit*/) 
        {         
            printf("Reset %d \n", go->GetGUIDLow());
        }

        void OnGameObjectStateChanged(GameObject* go, uint32 /*state*/) 
        { 
            printf("Reset %d \n", go->GetGUIDLow());
        }

        void UpdateAI(uint32 diff) override
        {

        }
    };

    GameObjectAI* GetAI(GameObject* go) const OVERRIDE
    {
        return new go_beacon_of_lightAI(go);
    }
};




void AddSC_boss_temple_guardian_anhuur()
{
    new boss_temple_guardian_anhuur();
    new spell_disable_beacon_beams();
    new go_beacon_of_light();

}
