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

/*Copyright (C) 2014 Arkania Project.
*
* Script 99% done. TODO:
*
* - Get correctly weapon equipment for baleroc. 101035 - trigger bridge visual, after that it summons.
*
* - Live testing needed.
*
* This file is NOT free software; third-party users can NOT redistribute it or modify it. :)
*/

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"
#include "MapManager.h"
#include "Spell.h"
#include "Vehicle.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "CreatureTextMgr.h"

#include "firelands.h"

enum Yells
{
    SAY_AGGRO      = 0,
    SAY_DEATH      = 1,
    SAY_KILL       = 2,
    
    SAY_DECIMATION = 3,
    SAY_INFERNO    = 4,
    SAY_CRYSTAL    = 5,
    SAY_COUNTDOWN  = 6,

    SAY_DECI_ANN   = 7,
    SAY_INFE_ANN   = 8,
    SAY_CRY_ANN    = 9,

    SAY_BERSERK    = 10,
};

enum Spells
{
//Baleroc

    // Misc
    SPELL_BLAZE_OF_GLORY           = 99252,
    SPELL_INCENDIARY_SOUL          = 99369,
    
    SPELL_SHARDS_OF_TORMENT        = 99259, //dummy
    SPELL_SHARDS_OF_TORMENT_SUMMON = 99260, //end of dummy cast
    
    SPELL_COUNTDOWN                = 99516, //check with 99517 every 200 ms
    SPELL_COUNTDOWN_DUMMY          = 99515, // player visual
    SPELL_COUNTDOWN_DUMMY1         = 99519, // player visual 2 other player linked
    SPELL_COUNTDOWN_DAMAGE         = 99518, // spell damage

    // Decimation Phase
    SPELL_DECIMATION_BLADE_10      = 99352, //aura apply, as increase
    SPELL_DECIMATION_BLADE_25      = 99405, //aura apply, as increase

    // Inferno Phase
    SPELL_INFERNO_BLADE            = 99350, //aura apply
    
    SPELL_BERSERK                  = 47008,
    SPELL_DUAL_BLADES              = 674,

    // Shard of torment
    SPELL_VISUAL                   = 99254,
    SPELL_TORMENT_DUMMY            = 99258,

    SPELL_TORMENT                  = 99255,

    SPELL_TORMENT_10N              = 99256,
    SPELL_TORMENT_25N              = 100230,
    SPELL_TORMENT_10H              = 100231,
    SPELL_TORMENT_25H              = 100232,
    
    SPELL_TORMENTED                = 99257, //when torment ends this is applied, spell_linked_spell needed for aura removal apply.
    SPELL_WAVE_OF_TORMENT_10N      = 99261, //every second a player is not within 15 yards of shard
    SPELL_WAVE_OF_TORMENT_25N      = 101636,
    SPELL_WAVE_OF_TORMENT_10H      = 101637,
    SPELL_WAVE_OF_TORMENT_25H      = 101638,
    
    SPELL_VITAL_SPARK              = 99262, //when healing people with Torment buff. Healing tank with Blaze of Glory turns to vital flame for 15 sec, then returns to vs stacks had.
    SPELL_VITAL_FLAME              = 99263  //have vs and cast on tank or someone with blaze of glory.
};

enum Events
{
// Baleroc

    // Misc
    EVENT_BLAZE_OF_GLORY    = 1,
    EVENT_COUNTDOWN         = 2,
    EVENT_SHARDS_OF_TORMENT = 3,
    EVENT_SUMMON_SHARDS     = 4,

    // Decimation Phase
    EVENT_DECIMATION_BLADE  = 5,

    // Inferno Phase
    EVENT_INFERNO_BLADE     = 6,
    
    EVENT_BERSERK           = 7,

    // Shards of torment
    EVENT_CHECK_RANGE       = 8,
    EVENT_WAVE_OF_TORMENT   = 9,
    EVENT_LAST_PLAYER       = 10,
};

enum Equipment
{
    EQUIPMENT_ID_SWORD_1H    = 69757,  // Normal
    EQUIPMENT_ID_SWORD_2H    = 71780,   // Normal
};

class boss_baloroc: public CreatureScript
{
public: 
    boss_baloroc() : CreatureScript("boss_baloroc") { } 

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_balorocAI (creature);
    }

    struct boss_balorocAI : public BossAI
    {
        boss_balorocAI(Creature* creature) : BossAI(creature, DATA_BALOROC)
        {
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_DECIMATION_BLADE, 30000);
            events.ScheduleEvent(EVENT_BLAZE_OF_GLORY, 5000);
            events.ScheduleEvent(EVENT_SHARDS_OF_TORMENT, 20000);

            if (IsHeroic())
                events.ScheduleEvent(EVENT_COUNTDOWN, 15000);

            Talk(SAY_AGGRO);

            if (instance)
            {
                instance->SetBossState(DATA_BALOROC, IN_PROGRESS);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add
            }

            events.ScheduleEvent(EVENT_BERSERK, 6 * MINUTE * IN_MILLISECONDS);

            _EnterCombat();
        }

        void JustDied(Unit * /*victim*/)
        {
            if (instance)
            {
                instance->SetBossState(DATA_BALOROC, DONE);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            Talk(SAY_DEATH);
            summons.DespawnAll();

            RemoveBlazeOfGlory();

            _JustDied();
        }

        void KilledUnit(Unit * victim)
        {
            Talk(SAY_KILL-urand(0,1));
            if (victim->HasAura(SPELL_BLAZE_OF_GLORY))
                victim->RemoveAura(SPELL_BLAZE_OF_GLORY);
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
            summon->setActive(true);
            summon->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE);
 
            if(me->IsInCombat())
               summon->AI()->DoZoneInCombat();
        }
        
        void RemoveBlazeOfGlory()
        {
            Map::PlayerList const& players = me->GetMap()->GetPlayers();
            for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                if (Player* player = itr->GetSource())
                    if (player->HasAura(SPELL_BLAZE_OF_GLORY))
                        player->RemoveAura(SPELL_BLAZE_OF_GLORY);
        }

        void CastCountDown()
        {
            std::list<Unit*> targets;
            SelectTargetList(targets, 2, SELECT_TARGET_RANDOM, 0.0f, true);
            if (!targets.empty())
                for (std::list<Unit*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    DoCast(*itr, SPELL_COUNTDOWN);
        }

        void Reset()
        {
            if (instance)
            {
                instance->SetBossState(DATA_BALOROC, NOT_STARTED);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            events.Reset();
            me->GetMotionMaster()->MoveTargetedHome();
            me->RemoveAllAuras();
            summons.DespawnAll();
            RemoveBlazeOfGlory();

            //DoCast(me, SPELL_DUAL_BLADES);
            SetEquipmentSlots(false, EQUIPMENT_ID_SWORD_1H, EQUIPMENT_ID_SWORD_1H, 0);
        }

        void EnterEvadeMode()
        {
            Reset();

            if (instance)
                instance->SetBossState(DATA_BALOROC, FAIL);

            _EnterEvadeMode();
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;
                
            if ((!me->HasAura(SPELL_DECIMATION_BLADE_10) && !me->HasAura(SPELL_DECIMATION_BLADE_25)) && !me->HasAura(SPELL_INFERNO_BLADE)) //set normal 2 blade equip
                SetEquipmentSlots(false, EQUIPMENT_ID_SWORD_1H, EQUIPMENT_ID_SWORD_1H, 0);

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                
                case EVENT_BERSERK:
                    DoCast(me, SPELL_BERSERK);
                    break;
                
                case EVENT_BLAZE_OF_GLORY:
                    DoCastVictim(SPELL_BLAZE_OF_GLORY);
                    DoCast(me, SPELL_INCENDIARY_SOUL);
                    
                    events.ScheduleEvent(EVENT_BLAZE_OF_GLORY, 20000);
                    break;
                
                case EVENT_SHARDS_OF_TORMENT:
                    Talk(SAY_CRY_ANN);
                    DoCast(me, SPELL_SHARDS_OF_TORMENT);
                    
                    events.ScheduleEvent(EVENT_SUMMON_SHARDS, 1000);
                    break;
                
                case EVENT_DECIMATION_BLADE:  
                    Talk(SAY_DECIMATION);
                    Talk(SAY_DECI_ANN);
                    DoCast(me, (Is25ManRaid() ? SPELL_DECIMATION_BLADE_25 : SPELL_DECIMATION_BLADE_10));
                    SetEquipmentSlots(false, EQUIPMENT_ID_SWORD_2H, 0, 0); //set one blade equip
                    
                    events.ScheduleEvent(EVENT_INFERNO_BLADE, 30000);
                    break;
                
                case EVENT_INFERNO_BLADE:   
                    Talk(SAY_INFERNO);
                    Talk(SAY_INFE_ANN);                    
                    DoCast(me, SPELL_INFERNO_BLADE);
                    SetEquipmentSlots(false, EQUIPMENT_ID_SWORD_2H, 0, 0); //set one blade equip
                    
                    events.ScheduleEvent(EVENT_DECIMATION_BLADE, 30000);
                    break;

                case EVENT_COUNTDOWN:
                    Talk(SAY_COUNTDOWN);
                    CastCountDown();

                    events.ScheduleEvent(EVENT_COUNTDOWN, 40000);
                    break;

                case EVENT_SUMMON_SHARDS:
                    std::list<Unit*> players;
                    SelectTargetList(players, Is25ManRaid() ? 2 : 1, SELECT_TARGET_RANDOM, 500.0f, true);
                    if (!players.empty())
                        for (std::list<Unit*>::iterator itr = players.begin(); itr != players.end(); ++itr)
                            DoCast(*itr, SPELL_SHARDS_OF_TORMENT_SUMMON);

                    events.ScheduleEvent(EVENT_SHARDS_OF_TORMENT, 35000);
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

class npc_shard_of_torment : public CreatureScript
{
public:
    npc_shard_of_torment() : CreatureScript("npc_shard_of_torment") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_shard_of_tormentAI (creature);
    }

    struct npc_shard_of_tormentAI : public ScriptedAI
    {
        npc_shard_of_tormentAI(Creature* creature) : ScriptedAI(creature)
        {
            creature->SetReactState(REACT_PASSIVE);
        }

        EventMap events;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            DoZoneInCombat();

            // me->SetDisplayId(11686);
            me->AddAura(SPELL_TORMENT_DUMMY,me);
            events.ScheduleEvent(EVENT_LAST_PLAYER, 30000);        
            events.ScheduleEvent(EVENT_CHECK_RANGE, 4000);        
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                case EVENT_LAST_PLAYER:
                    if (Unit* nearPlayer = me->FindNearestPlayer(3.0f))
                        if (nearPlayer->HasAura(SPELL_TORMENT_10N) && nearPlayer->HasAura(SPELL_TORMENT))
                        {
                            nearPlayer->RemoveAurasDueToSpell(SPELL_TORMENT_10N);
                            nearPlayer->RemoveAurasDueToSpell(SPELL_TORMENT);
                        }
                    break;

                case EVENT_CHECK_RANGE:
                    if (me->HasAura(SPELL_TORMENT_DUMMY))
                        me->RemoveAura(SPELL_TORMENT_DUMMY);
                    
                    DoCast(me, SPELL_VISUAL);

                    if (Unit* nearPlayer = me->FindNearestPlayer(15.0f, true))
                        DoCast(nearPlayer, SPELL_TORMENT);
                    else
                        events.ScheduleEvent(EVENT_WAVE_OF_TORMENT, 1000);

                    events.ScheduleEvent(EVENT_CHECK_RANGE, 1000);
                    break;

                case EVENT_WAVE_OF_TORMENT:
                    DoCast(me, RAID_MODE(SPELL_WAVE_OF_TORMENT_10N,SPELL_WAVE_OF_TORMENT_25N,SPELL_WAVE_OF_TORMENT_10H,SPELL_WAVE_OF_TORMENT_25H));
                    break;
                }
            }
        }
    };
};

class spell_baloroc_countdown : public SpellScriptLoader
{
    public:
        spell_baloroc_countdown() : SpellScriptLoader("spell_baloroc_countdown") { }

        class spell_baloroc_countdown_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_baloroc_countdown_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if(Trinity::UnitAuraCheck(false, SPELL_COUNTDOWN));

                bool remove = true;
                std::list<WorldObject*>::const_iterator itrEnd = targets.end(), itr, itr2;
                
                for (itr = targets.begin(); itr != itrEnd && remove; ++itr)
                {
                    if (!GetCaster()->IsWithinDist(*itr, 4.0f, false))
                        remove = false;

                    for (itr2 = targets.begin(); itr2 != itrEnd && remove; ++itr2)
                        if (itr != itr2 && !(*itr2)->IsWithinDist(*itr, 4.0f, false))
                            remove = false;
                }

                if (remove)
                {
                    if (InstanceScript* instance = GetCaster()->GetInstanceScript())
                    {
                        instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_COUNTDOWN);
                        targets.clear();
                    }
                }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_baloroc_countdown_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_baloroc_countdown_SpellScript();
        }
};

// 99518 
class spell_baloroc_countdown_dmg : public SpellScriptLoader
{
    public:
        spell_baloroc_countdown_dmg() : SpellScriptLoader("spell_baloroc_countdown_dmg") { }

        class spell_baloroc_countdown_dmg_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_baloroc_countdown_dmg_AuraScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_COUNTDOWN_DAMAGE))
                    return false;
                return true;
            }
            
            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/) // All-raid damage, 8-sec tick at time expire.
            {
                SpellInfo const* damageSpell = sSpellMgr->GetSpellInfo(SPELL_COUNTDOWN_DAMAGE);
                int32 damage = damageSpell->Effects[EFFECT_0].CalcValue();
                damage = int32(damage);
                
                AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
                if (removeMode == AURA_REMOVE_BY_DEATH || !IsExpired())
                    return;
                    
                GetUnitOwner()->CastCustomSpell(SPELL_COUNTDOWN_DAMAGE, SPELLVALUE_BASE_POINT0, damage, GetUnitOwner(), true);
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_baloroc_countdown_dmg_AuraScript::OnRemove, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_baloroc_countdown_dmg_AuraScript();
        }
};

// 99519
class spell_baloroc_countdown_dmg_target : public SpellScriptLoader
{
    public:
        spell_baloroc_countdown_dmg_target() : SpellScriptLoader("spell_baloroc_countdown_dmg_target") { }

        class spell_baloroc_countdown_dmg_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_baloroc_countdown_dmg_SpellScript);

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                unitList.remove_if(Trinity::UnitAuraCheck(true, SPELL_COUNTDOWN));
                unitList.push_back(GetCaster());
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_baloroc_countdown_dmg_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_TARGET_ANY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_baloroc_countdown_dmg_SpellScript();
        }
};

void AddSC_boss_baloroc() 
{
    new boss_baloroc();
    new npc_shard_of_torment();
    new spell_baloroc_countdown();
    // new spell_baloroc_countdown_dmg();
    new spell_baloroc_countdown_dmg_target();
}