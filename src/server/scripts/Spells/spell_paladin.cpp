/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
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

 /*
  * Scripts for spells with SPELLFAMILY_PALADIN and SPELLFAMILY_GENERIC spells used by paladin players.
  * Ordered alphabetically using scriptname.
  * Scriptnames of files in this file should be prefixed with "spell_pal_".
  */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Group.h"

enum PaladinSpells
{
    SPELL_PALADIN_AVENGERS_SHIELD = 31935,
    SPELL_PALADIN_AURA_MASTERY_IMMUNE = 64364,
    SPELL_PALADIN_BEACON_OF_LIGHT_MARKER = 53563,
    SPELL_PALADIN_BEACON_OF_LIGHT_HEAL = 53652,
    SPELL_PALADIN_BLESSING_OF_LOWER_CITY_DRUID = 37878,
    SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PALADIN = 37879,
    SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PRIEST = 37880,
    SPELL_PALADIN_BLESSING_OF_LOWER_CITY_SHAMAN = 37881,
    SPELL_PALADIN_CONCENTRACTION_AURA = 19746,
    SPELL_PALADIN_DIVINE_PURPOSE_PROC = 90174,
    SPELL_PALADIN_DIVINE_SACRIFICE = 64205,
    SPELL_PALADIN_DIVINE_STORM = 53385,
    SPELL_PALADIN_DIVINE_STORM_DUMMY = 54171,
    SPELL_PALADIN_DIVINE_STORM_HEAL = 54172,
    SPELL_PALADIN_EYE_FOR_AN_EYE_RANK_1 = 9799,
    SPELL_PALADIN_EYE_FOR_AN_EYE_RANK_2 = 25998,
    SPELL_PALADIN_EYE_FOR_AN_EYE_DAMAGE = 25997,
    SPELL_PALADIN_FORBEARANCE = 25771,
    SPELL_PALADIN_GLYPH_OF_SALVATION = 63225,
    SPELL_PALADIN_HAND_OF_SACRIFICE = 6940,
    SPELL_PALADIN_HOLY_LIGHT = 635,
    SPELL_PALADIN_HOLY_SHOCK_R1 = 20473,
    SPELL_PALADIN_HOLY_SHOCK_R1_DAMAGE = 25912,
    SPELL_PALADIN_HOLY_SHOCK_R1_HEALING = 25914,
    SPELL_PALADIN_IMMUNE_SHIELD_MARKER = 61988,
    SPELL_PALADIN_IMPROVED_CONCENTRACTION_AURA = 63510,
    SPELL_PALADIN_IMPROVED_DEVOTION_AURA = 63514,
    SPELL_PALADIN_ITEM_HEALING_TRANCE = 37706,
    SPELL_PALADIN_JUDGEMENT_DAMAGE = 54158,
    SPELL_PALADIN_RIGHTEOUS_DEFENSE_TAUNT = 31790,
    SPELL_PALADIN_SANCTIFIED_RETRIBUTION_AURA = 63531,
    SPELL_PALADIN_SANCTIFIED_RETRIBUTION_R1 = 31869,
    SPELL_PALADIN_SANCTIFIED_WRATH = 57318,
    SPELL_PALADIN_SANCTIFIED_WRATH_TALENT_R1 = 53375,
    SPELL_PALADIN_SEAL_OF_RIGHTEOUSNESS = 25742,
    SPELL_PALADIN_SWIFT_RETRIBUTION_R1 = 53379,
    SPELL_PALADIN_HOLY_POWER_ARMOR = 28790,
    SPELL_PALADIN_HOLY_POWER_ATTACK_POWER = 28791,
    SPELL_PALADIN_HOLY_POWER_SPELL_POWER = 28793,
    SPELL_PALADIN_HOLY_POWER_MP5 = 28795,
    SPELL_PALADIN_ENDURING_LIGHT = 40471,
    SPELL_PALADIN_ENDURING_JUDGEMENT = 40472,
    SPELL_PALADIN_BEACON_OF_LIGHT = 53563,
    SPELL_PALADIN_HOLY_MENDING = 64891,
    SPELL_PALADIN_EXORCISM = 879,
    SPELL_PALADIN_CONSECRATION_DAMAGE = 81297,
    SPELL_PALADIN_ETERNAL_GLORY_PROC = 88676,
    SPELL_PALADIN_SELFLESS_HEALER_R1 = 85803,
    SPELL_PALADIN_SELFLESS_HEALER_R2 = 85804,
    SPELL_PALADIN_GUARDED_BY_THE_LIGHT = 85639,
    SPELL_PALADIN_GLYPH_OF_LONG_WORD = 93466,
    SPELL_PALADIN_ETERNAL_GLORY_R1 = 87163,
    SPELL_PALADIN_LONG_ARM_OF_THE_LAW = 87168,
    SPELL_PALADIN_GOAK_HOLY_SUMMON = 86669,
    SPELL_PALADIN_GOAK_ANCIENT_HEALER = 86674,
    SPELL_PALADIN_GOAK_PROTECTION_SUMMON = 86659,
    SPELL_PALADIN_GOAK_RETRIBUTION_SUMMON = 86698,
    SPELL_PALADIN_GOAK_ANCIENT_POWER = 86700,
    SPELL_PALADIN_GOAK_ANCIENT_CRUSADER = 86701,
    SPELL_PALADIN_GOAK_ANCIENT_CRUSADER_GUARDIAN = 86703,
    SPELL_PALADIN_GOAK_ANCIENT_FURY = 86704,

};

enum MiscSpells
{
    SPELL_GENERIC_ARENA_DAMPENING = 74410,
    SPELL_GENERIC_BATTLEGROUND_DAMPENING = 74411
};

enum PaladinSpellIcons
{
    PALADIN_ICON_ID_RETRIBUTION_AURA = 555,
    PALADIN_ICOM_ID_SELFLESS_HEALER = 3924, // spell 85804 = IconID 3924
    PALADIN_ICON_ID_ETERNAL_GLORY = 2944, // spell 87163 = IconID 2944
};

/*
// 31850 - Ardent Defender
class spell_pal_ardent_defender : public SpellScriptLoader
{
    public:
        spell_pal_ardent_defender() : SpellScriptLoader("spell_pal_ardent_defender") { }

        class spell_pal_ardent_defender_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pal_ardent_defender_AuraScript);

            uint32 absorbPct, healPct;

            enum Spell
            {
                PAL_SPELL_ARDENT_DEFENDER_HEAL = 66235,
            };

            bool Load() override
            {
                healPct = GetSpellInfo()->Effects[EFFECT_1].CalcValue();
                absorbPct = GetSpellInfo()->Effects[EFFECT_0].CalcValue();
                return GetUnitOwner()->GetTypeId() == TYPEID_PLAYER;
            }

            void CalculateAmount(AuraEffect const* aurEff, int32 & amount, bool & canBeRecalculated)
            {
                // Set absorbtion amount to unlimited
                amount = -1;
            }

            void Absorb(AuraEffect* aurEff, DamageInfo & dmgInfo, uint32 & absorbAmount)
            {
                Unit* victim = GetTarget();
                int32 remainingHealth = victim->GetHealth() - dmgInfo.GetDamage();
                uint32 allowedHealth = victim->CountPctFromMaxHealth(35);
                // If damage kills us
                if (remainingHealth <= 0 && !victim->ToPlayer()->HasSpellCooldown(PAL_SPELL_ARDENT_DEFENDER_HEAL))
                {
                    // Cast healing spell, completely avoid damage
                    absorbAmount = dmgInfo.GetDamage();

                    uint32 defenseSkillValue = victim->GetDefenseSkillValue();
                    // Max heal when defense skill denies critical hits from raid bosses
                    // Formula: max defense at level + 140 (raiting from gear)
                    uint32 reqDefForMaxHeal  = victim->getLevel() * 5 + 140;
                    float pctFromDefense = (defenseSkillValue >= reqDefForMaxHeal)
                        ? 1.0f
                        : float(defenseSkillValue) / float(reqDefForMaxHeal);

                    int32 healAmount = int32(victim->CountPctFromMaxHealth(uint32(healPct * pctFromDefense)));
                    victim->CastCustomSpell(victim, PAL_SPELL_ARDENT_DEFENDER_HEAL, &healAmount, NULL, NULL, true, NULL, aurEff);
                    victim->ToPlayer()->AddSpellCooldown(PAL_SPELL_ARDENT_DEFENDER_HEAL, 0, time(NULL) + 120);
                }
                else if (remainingHealth < int32(allowedHealth))
                {
                    // Reduce damage that brings us under 35% (or full damage if we are already under 35%) by x%
                    uint32 damageToReduce = (victim->GetHealth() < allowedHealth)
                        ? dmgInfo.GetDamage()
                        : allowedHealth - remainingHealth;
                    absorbAmount = CalculatePct(damageToReduce, absorbPct);
                }
            }

            void Register() override
            {
                 DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_ardent_defender_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                 OnEffectAbsorb += AuraEffectAbsorbFn(spell_pal_ardent_defender_AuraScript::Absorb, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_pal_ardent_defender_AuraScript();
        }
};
*/

// 31821 - Aura Mastery
class spell_pal_aura_mastery : public SpellScriptLoader
{
public:
    spell_pal_aura_mastery() : SpellScriptLoader("spell_pal_aura_mastery") { }

    class spell_pal_aura_mastery_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_aura_mastery_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_AURA_MASTERY_IMMUNE))
                return false;
            return true;
        }

        void HandleEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            GetTarget()->CastSpell(GetTarget(), SPELL_PALADIN_AURA_MASTERY_IMMUNE, true);
        }

        void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            GetTarget()->RemoveOwnedAura(SPELL_PALADIN_AURA_MASTERY_IMMUNE, GetCasterGUID());
        }

        void Register() override
        {
            AfterEffectApply += AuraEffectApplyFn(spell_pal_aura_mastery_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
            AfterEffectRemove += AuraEffectRemoveFn(spell_pal_aura_mastery_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_pal_aura_mastery_AuraScript();
    }
};

// 64364 - Aura Mastery Immune
class spell_pal_aura_mastery_immune : public SpellScriptLoader
{
public:
    spell_pal_aura_mastery_immune() : SpellScriptLoader("spell_pal_aura_mastery_immune") { }

    class spell_pal_aura_mastery_immune_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_aura_mastery_immune_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_CONCENTRACTION_AURA))
                return false;
            return true;
        }

        bool CheckAreaTarget(Unit* target)
        {
            return target->HasAura(SPELL_PALADIN_CONCENTRACTION_AURA, GetCasterGUID());
        }

        void Register() override
        {
            DoCheckAreaTarget += AuraCheckAreaTargetFn(spell_pal_aura_mastery_immune_AuraScript::CheckAreaTarget);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_pal_aura_mastery_immune_AuraScript();
    }
};

// 31884 - Avenging Wrath
class spell_pal_avenging_wrath : public SpellScriptLoader
{
public:
    spell_pal_avenging_wrath() : SpellScriptLoader("spell_pal_avenging_wrath") { }

    class spell_pal_avenging_wrath_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_avenging_wrath_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_SANCTIFIED_WRATH)
                || !sSpellMgr->GetSpellInfo(SPELL_PALADIN_SANCTIFIED_WRATH_TALENT_R1))
                return false;
            return true;
        }

        void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* target = GetTarget();
            if (AuraEffect const* aurEff = target->GetAuraEffectOfRankedSpell(SPELL_PALADIN_SANCTIFIED_WRATH_TALENT_R1, EFFECT_2))
            {
                int32 basepoints = aurEff->GetAmount();
                target->CastCustomSpell(target, SPELL_PALADIN_SANCTIFIED_WRATH, &basepoints, &basepoints, NULL, true, NULL, aurEff);
            }
        }

        void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            GetTarget()->RemoveAurasDueToSpell(SPELL_PALADIN_SANCTIFIED_WRATH);
        }

        void Register() override
        {
            OnEffectApply += AuraEffectApplyFn(spell_pal_avenging_wrath_AuraScript::HandleApply, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE, AURA_EFFECT_HANDLE_REAL);
            AfterEffectRemove += AuraEffectRemoveFn(spell_pal_avenging_wrath_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_pal_avenging_wrath_AuraScript();
    }
};

// 53651 - Beacon of Light
class spell_pal_beacon_of_light : public SpellScriptLoader
{
public:
    spell_pal_beacon_of_light() : SpellScriptLoader("spell_pal_beacon_of_light") { }

    class spell_pal_beacon_of_light_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_beacon_of_light_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_BEACON_OF_LIGHT_HEAL))
                return false;
            return true;
        }

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetActionTarget()->GetAura(SPELL_PALADIN_BEACON_OF_LIGHT_MARKER, GetCasterGUID()))
                return false;
            return true;
        }

        void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();
            int32 heal = eventInfo.GetHealInfo()->GetHeal();

            if (eventInfo.GetDamageInfo()->GetSpellInfo()->Id != SPELL_PALADIN_HOLY_LIGHT)
                heal = int32(CalculatePct(heal, aurEff->GetAmount()));

            Unit::AuraList const& auras = GetCaster()->GetSingleCastAuras();
            for (Unit::AuraList::const_iterator itr = auras.begin(); itr != auras.end(); ++itr)
            {
                if ((*itr)->GetId() == SPELL_PALADIN_BEACON_OF_LIGHT_MARKER)
                {
                    std::list<AuraApplication*> applications;
                    (*itr)->GetApplicationList(applications);
                    if (applications.empty())
                        return;

                    GetCaster()->CastCustomSpell(SPELL_PALADIN_BEACON_OF_LIGHT_HEAL, SPELLVALUE_BASE_POINT0, heal, applications.front()->GetTarget(), true, NULL, aurEff);
                    return;
                }
            }
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_pal_beacon_of_light_AuraScript::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_pal_beacon_of_light_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_pal_beacon_of_light_AuraScript();
    }
};

// 37877 - Blessing of Faith
class spell_pal_blessing_of_faith : public SpellScriptLoader
{
public:
    spell_pal_blessing_of_faith() : SpellScriptLoader("spell_pal_blessing_of_faith") { }

    class spell_pal_blessing_of_faith_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_blessing_of_faith_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_BLESSING_OF_LOWER_CITY_DRUID) || !sSpellMgr->GetSpellInfo(SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PALADIN) || !sSpellMgr->GetSpellInfo(SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PRIEST) || !sSpellMgr->GetSpellInfo(SPELL_PALADIN_BLESSING_OF_LOWER_CITY_SHAMAN))
                return false;
            return true;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* unitTarget = GetHitUnit())
            {
                uint32 spell_id = 0;
                switch (unitTarget->getClass())
                {
                case CLASS_DRUID:
                    spell_id = SPELL_PALADIN_BLESSING_OF_LOWER_CITY_DRUID;
                    break;
                case CLASS_PALADIN:
                    spell_id = SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PALADIN;
                    break;
                case CLASS_PRIEST:
                    spell_id = SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PRIEST;
                    break;
                case CLASS_SHAMAN:
                    spell_id = SPELL_PALADIN_BLESSING_OF_LOWER_CITY_SHAMAN;
                    break;
                default:
                    return; // ignore for non-healing classes
                }
                Unit* caster = GetCaster();
                caster->CastSpell(caster, spell_id, true);
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_pal_blessing_of_faith_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pal_blessing_of_faith_SpellScript();
    }
};

// 64205 - Divine Sacrifice
class spell_pal_divine_sacrifice : public SpellScriptLoader
{
public:
    spell_pal_divine_sacrifice() : SpellScriptLoader("spell_pal_divine_sacrifice") { }

    class spell_pal_divine_sacrifice_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_divine_sacrifice_AuraScript);

        uint32 groupSize, minHpPct;
        int32 remainingAmount;

        bool Load() override
        {

            if (Unit* caster = GetCaster())
            {
                if (caster->GetTypeId() == TYPEID_PLAYER)
                {
                    if (caster->ToPlayer()->GetGroup())
                        groupSize = caster->ToPlayer()->GetGroup()->GetMembersCount();
                    else
                        groupSize = 1;
                }
                else
                    return false;

                remainingAmount = (caster->CountPctFromMaxHealth(GetSpellInfo()->Effects[EFFECT_2].CalcValue(caster)) * groupSize);
                minHpPct = GetSpellInfo()->Effects[EFFECT_1].CalcValue(caster);
                return true;
            }
            return false;
        }

        void Split(AuraEffect* /*aurEff*/, DamageInfo & /*dmgInfo*/, uint32 & splitAmount)
        {
            remainingAmount -= splitAmount;
            // break when absorbed everything it could, or if the casters hp drops below 20%
            if (Unit* caster = GetCaster())
                if (remainingAmount <= 0 || (caster->GetHealthPct() < minHpPct))
                    caster->RemoveAura(SPELL_PALADIN_DIVINE_SACRIFICE);
        }

        void Register() override
        {
            OnEffectSplit += AuraEffectSplitFn(spell_pal_divine_sacrifice_AuraScript::Split, EFFECT_0);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_pal_divine_sacrifice_AuraScript();
    }
};

// 53385 - Divine Storm
class spell_pal_divine_storm : public SpellScriptLoader
{
public:
    spell_pal_divine_storm() : SpellScriptLoader("spell_pal_divine_storm") { }

    class spell_pal_divine_storm_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_divine_storm_SpellScript);

        uint32 healPct;

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_DIVINE_STORM_DUMMY))
                return false;
            return true;
        }

        bool Load() override
        {
            healPct = GetSpellInfo()->Effects[EFFECT_1].CalcValue(GetCaster());
            return true;
        }

        void TriggerHeal()
        {
            Unit* caster = GetCaster();
            caster->CastCustomSpell(SPELL_PALADIN_DIVINE_STORM_DUMMY, SPELLVALUE_BASE_POINT0, (GetHitDamage() * healPct) / 100, caster, true);
        }

        void Register() override
        {
            AfterHit += SpellHitFn(spell_pal_divine_storm_SpellScript::TriggerHeal);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pal_divine_storm_SpellScript();
    }
};

// 54171 - Divine Storm (Dummy)
class spell_pal_divine_storm_dummy : public SpellScriptLoader
{
public:
    spell_pal_divine_storm_dummy() : SpellScriptLoader("spell_pal_divine_storm_dummy") { }

    class spell_pal_divine_storm_dummy_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_divine_storm_dummy_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_DIVINE_STORM_HEAL))
                return false;
            return true;
        }

        void CountTargets(std::list<WorldObject*>& targetList)
        {
            _targetCount = targetList.size();
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (!_targetCount || !GetHitUnit())
                return;

            int32 heal = GetEffectValue() / _targetCount;
            GetCaster()->CastCustomSpell(GetHitUnit(), SPELL_PALADIN_DIVINE_STORM_HEAL, &heal, NULL, NULL, true);
        }
    private:
        uint32 _targetCount;

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_pal_divine_storm_dummy_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_divine_storm_dummy_SpellScript::CountTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_RAID);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pal_divine_storm_dummy_SpellScript();
    }
};

// 33695 - Exorcism and Holy Wrath Damage
class spell_pal_exorcism_and_holy_wrath_damage : public SpellScriptLoader
{
public:
    spell_pal_exorcism_and_holy_wrath_damage() : SpellScriptLoader("spell_pal_exorcism_and_holy_wrath_damage") { }

    class spell_pal_exorcism_and_holy_wrath_damage_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_exorcism_and_holy_wrath_damage_AuraScript);

        void HandleEffectCalcSpellMod(AuraEffect const* aurEff, SpellModifier*& spellMod)
        {
            if (!spellMod)
            {
                spellMod = new SpellModifier(aurEff->GetBase());
                spellMod->op = SPELLMOD_DAMAGE;
                spellMod->type = SPELLMOD_FLAT;
                spellMod->spellId = GetId();
                spellMod->mask[1] = 0x200002;
            }

            spellMod->value = aurEff->GetAmount();
        }

        void Register() override
        {
            DoEffectCalcSpellMod += AuraEffectCalcSpellModFn(spell_pal_exorcism_and_holy_wrath_damage_AuraScript::HandleEffectCalcSpellMod, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_pal_exorcism_and_holy_wrath_damage_AuraScript();
    }
};

// -9799 - Eye for an Eye
class spell_pal_eye_for_an_eye : public SpellScriptLoader
{
public:
    spell_pal_eye_for_an_eye() : SpellScriptLoader("spell_pal_eye_for_an_eye") { }

    class spell_pal_eye_for_an_eye_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_eye_for_an_eye_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_EYE_FOR_AN_EYE_DAMAGE))
                return false;
            return true;
        }

        void HandleEffectProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();
            int32 damage = CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), aurEff->GetAmount());
            GetTarget()->CastCustomSpell(SPELL_PALADIN_EYE_FOR_AN_EYE_DAMAGE, SPELLVALUE_BASE_POINT0, damage, eventInfo.GetProcTarget(), true, NULL, aurEff);
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_pal_eye_for_an_eye_AuraScript::HandleEffectProc, EFFECT_0, m_scriptSpellId == SPELL_PALADIN_EYE_FOR_AN_EYE_RANK_1 ? SPELL_AURA_DUMMY : SPELL_AURA_PROC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_pal_eye_for_an_eye_AuraScript();
    }
};

// -75806 - Grand Crusader
class spell_pal_grand_crusader : public SpellScriptLoader
{
public:
    spell_pal_grand_crusader() : SpellScriptLoader("spell_pal_grand_crusader") { }

    class spell_pal_grand_crusader_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_grand_crusader_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_AVENGERS_SHIELD))
                return false;
            return true;
        }

        bool CheckProc(ProcEventInfo& /*eventInfo*/)
        {
            return GetTarget()->GetTypeId() == TYPEID_PLAYER;
        }

        void HandleEffectProc(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
        {
            GetTarget()->ToPlayer()->RemoveSpellCooldown(SPELL_PALADIN_AVENGERS_SHIELD, true);
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_pal_grand_crusader_AuraScript::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_pal_grand_crusader_AuraScript::HandleEffectProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_pal_grand_crusader_AuraScript();
    }
};

// 54968 - Glyph of Holy Light
class spell_pal_glyph_of_holy_light : public SpellScriptLoader
{
public:
    spell_pal_glyph_of_holy_light() : SpellScriptLoader("spell_pal_glyph_of_holy_light") { }

    class spell_pal_glyph_of_holy_light_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_glyph_of_holy_light_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            uint32 const maxTargets = GetSpellInfo()->MaxAffectedTargets;

            if (targets.size() > maxTargets)
            {
                targets.sort(Trinity::HealthPctOrderPred());
                targets.resize(maxTargets);
            }
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_glyph_of_holy_light_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pal_glyph_of_holy_light_SpellScript();
    }
};

// 6940 - Hand of Sacrifice
class spell_pal_hand_of_sacrifice : public SpellScriptLoader
{
public:
    spell_pal_hand_of_sacrifice() : SpellScriptLoader("spell_pal_hand_of_sacrifice") { }

    class spell_pal_hand_of_sacrifice_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_hand_of_sacrifice_AuraScript);

        int32 remainingAmount;

        bool Load() override
        {
            if (Unit* caster = GetCaster())
            {
                remainingAmount = caster->GetMaxHealth();
                return true;
            }
            return false;
        }

        void Split(AuraEffect* /*aurEff*/, DamageInfo & /*dmgInfo*/, uint32 & splitAmount)
        {
            remainingAmount -= splitAmount;

            if (remainingAmount <= 0)
            {
                GetTarget()->RemoveAura(SPELL_PALADIN_HAND_OF_SACRIFICE);
            }
        }

        void Register() override
        {
            OnEffectSplit += AuraEffectSplitFn(spell_pal_hand_of_sacrifice_AuraScript::Split, EFFECT_0);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_pal_hand_of_sacrifice_AuraScript();
    }
};

// 20473 - Holy Shock
class spell_pal_holy_shock : public SpellScriptLoader
{
public:
    spell_pal_holy_shock() : SpellScriptLoader("spell_pal_holy_shock") { }

    class spell_pal_holy_shock_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_holy_shock_SpellScript);

        bool Validate(SpellInfo const* spellInfo) override
        {
            SpellInfo const* firstRankSpellInfo = sSpellMgr->GetSpellInfo(SPELL_PALADIN_HOLY_SHOCK_R1);
            if (!firstRankSpellInfo)
                return false;

            // can't use other spell than holy shock due to spell_ranks dependency
            if (!spellInfo->IsRankOf(firstRankSpellInfo))
                return false;

            uint8 rank = spellInfo->GetRank();
            if (!sSpellMgr->GetSpellWithRank(SPELL_PALADIN_HOLY_SHOCK_R1_DAMAGE, rank, true) || !sSpellMgr->GetSpellWithRank(SPELL_PALADIN_HOLY_SHOCK_R1_HEALING, rank, true))
                return false;

            return true;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            if (Unit* unitTarget = GetHitUnit())
            {
                uint8 rank = GetSpellInfo()->GetRank();
                if (caster->IsFriendlyTo(unitTarget))
                    caster->CastSpell(unitTarget, sSpellMgr->GetSpellWithRank(SPELL_PALADIN_HOLY_SHOCK_R1_HEALING, rank), true);
                else
                    caster->CastSpell(unitTarget, sSpellMgr->GetSpellWithRank(SPELL_PALADIN_HOLY_SHOCK_R1_DAMAGE, rank), true);
            }
        }

        SpellCastResult CheckCast()
        {
            Unit* caster = GetCaster();
            if (Unit* target = GetExplTargetUnit())
            {
                if (!caster->IsFriendlyTo(target))
                {
                    if (!caster->IsValidAttackTarget(target))
                        return SPELL_FAILED_BAD_TARGETS;

                    if (!caster->isInFront(target))
                        return SPELL_FAILED_UNIT_NOT_INFRONT;
                }
            }
            else
                return SPELL_FAILED_BAD_TARGETS;
            return SPELL_CAST_OK;
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_pal_holy_shock_SpellScript::CheckCast);
            OnEffectHitTarget += SpellEffectFn(spell_pal_holy_shock_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pal_holy_shock_SpellScript();
    }
};

// 63510 - Improved Concentraction Aura (Area Aura)
// 63514 - Improved Devotion Aura (Area Aura)
// 63531 - Sanctified Retribution (Area Aura)
class spell_pal_improved_aura_effect : public SpellScriptLoader
{
public:
    spell_pal_improved_aura_effect(char const* name) : SpellScriptLoader(name) { }

    class spell_pal_improved_aura_effect_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_improved_aura_effect_AuraScript);

        bool CheckAreaTarget(Unit* target)
        {
            Unit::AuraApplicationMap& appliedAuras = target->GetAppliedAuras();
            for (Unit::AuraApplicationMap::iterator itr = appliedAuras.begin(); itr != appliedAuras.end(); ++itr)
            {
                Aura const* aura = itr->second->GetBase();
                if (aura->GetSpellInfo()->GetSpellSpecific() == SPELL_SPECIFIC_AURA && aura->GetCasterGUID() == GetCasterGUID())
                {
                    // Not allow for Retribution Aura (prevent stacking) - Retribution Aura Overflow and Retribution Aura has same spell effects
                    if (GetSpellInfo()->Id == SPELL_PALADIN_SANCTIFIED_RETRIBUTION_AURA && aura->GetSpellInfo()->SpellIconID == PALADIN_ICON_ID_RETRIBUTION_AURA)
                        return false;
                    return true;
                }
            }

            return false;
        }

        void Register() override
        {
            DoCheckAreaTarget += AuraCheckAreaTargetFn(spell_pal_improved_aura_effect_AuraScript::CheckAreaTarget);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_pal_improved_aura_effect_AuraScript();
    }
};

// 37705 - Healing Discount
class spell_pal_item_healing_discount : public SpellScriptLoader
{
public:
    spell_pal_item_healing_discount() : SpellScriptLoader("spell_pal_item_healing_discount") { }

    class spell_pal_item_healing_discount_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_item_healing_discount_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_ITEM_HEALING_TRANCE))
                return false;
            return true;
        }

        void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
        {
            PreventDefaultAction();
            GetTarget()->CastSpell(GetTarget(), SPELL_PALADIN_ITEM_HEALING_TRANCE, true, NULL, aurEff);
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_pal_item_healing_discount_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_pal_item_healing_discount_AuraScript();
    }
};

// 40470 - Paladin Tier 6 Trinket
class spell_pal_item_t6_trinket : public SpellScriptLoader
{
public:
    spell_pal_item_t6_trinket() : SpellScriptLoader("spell_pal_item_t6_trinket") { }

    class spell_pal_item_t6_trinket_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_item_t6_trinket_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({ SPELL_PALADIN_ENDURING_LIGHT, SPELL_PALADIN_ENDURING_JUDGEMENT });
        }

        void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();
            SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
            if (!spellInfo)
                return;

            uint32 spellId;
            int32 chance;

            // Holy Light & Flash of Light
            if (spellInfo->SpellFamilyFlags[0] & 0xC0000000)
            {
                spellId = SPELL_PALADIN_ENDURING_LIGHT;
                chance = 15;
            }
            // Judgements
            else if (spellInfo->SpellFamilyFlags[0] & 0x00800000)
            {
                spellId = SPELL_PALADIN_ENDURING_JUDGEMENT;
                chance = 50;
            }
            else
                return;

            if (roll_chance_i(chance))
                eventInfo.GetActor()->CastSpell(eventInfo.GetProcTarget(), spellId, true);
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_pal_item_t6_trinket_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_pal_item_t6_trinket_AuraScript();
    }
};

// 20271 - Judgement (based on Seal to judge)
class spell_pal_judgement_20271 : public SpellScriptLoader
{
public:
    spell_pal_judgement_20271() : SpellScriptLoader("spell_pal_judgement_20271") { }

    class spell_pal_judgement_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_judgement_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_JUDGEMENT_DAMAGE))
                return false;
            return true;
        }

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            uint32 spellId = SPELL_PALADIN_JUDGEMENT_DAMAGE;

            // some seals have SPELL_AURA_DUMMY in EFFECT_2
            Unit::AuraEffectList const& auras = GetCaster()->GetAuraEffectsByType(SPELL_AURA_DUMMY);
            for (Unit::AuraEffectList::const_iterator i = auras.begin(); i != auras.end(); ++i)
            {
                if ((*i)->GetSpellInfo()->GetSpellSpecific() == SPELL_SPECIFIC_SEAL && (*i)->GetEffIndex() == EFFECT_2)
                    if (sSpellMgr->GetSpellInfo((*i)->GetAmount()))
                    {
                        spellId = (*i)->GetAmount();
                        break;
                    }
            }

            GetCaster()->CastSpell(GetHitUnit(), spellId, true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_pal_judgement_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pal_judgement_SpellScript();
    }
};

// 633 - Lay on Hands
class spell_pal_lay_on_hands : public SpellScriptLoader
{
public:
    spell_pal_lay_on_hands() : SpellScriptLoader("spell_pal_lay_on_hands") { }

    class spell_pal_lay_on_hands_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_lay_on_hands_SpellScript);

        bool Validate(SpellInfo const* /*spell*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_FORBEARANCE) ||
                !sSpellMgr->GetSpellInfo(SPELL_PALADIN_IMMUNE_SHIELD_MARKER))
                return false;
            return true;
        }

        SpellCastResult CheckCast()
        {
            Unit* caster = GetCaster();
            if (Unit* target = GetExplTargetUnit())
                if (caster == target)
                    if (target->HasAura(SPELL_PALADIN_FORBEARANCE) ||
                        target->HasAura(SPELL_PALADIN_IMMUNE_SHIELD_MARKER))
                    {
                        return SPELL_FAILED_TARGET_AURASTATE;
                    }

            return SPELL_CAST_OK;
        }

        void HandleScript()
        {
            Unit* caster = GetCaster();
            if (caster == GetHitUnit())
            {
                caster->CastSpell(caster, SPELL_PALADIN_FORBEARANCE, true);
                caster->CastSpell(caster, SPELL_PALADIN_IMMUNE_SHIELD_MARKER, true);
            }
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_pal_lay_on_hands_SpellScript::CheckCast);
            AfterHit += SpellHitFn(spell_pal_lay_on_hands_SpellScript::HandleScript);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pal_lay_on_hands_SpellScript();
    }
};

// 53651 - Light's Beacon - Beacon of Light
class spell_pal_light_s_beacon : public SpellScriptLoader
{
public:
    spell_pal_light_s_beacon() : SpellScriptLoader("spell_pal_light_s_beacon") { }

    class spell_pal_light_s_beacon_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_light_s_beacon_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({ SPELL_PALADIN_BEACON_OF_LIGHT, SPELL_PALADIN_BEACON_OF_LIGHT_HEAL });
        }

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (!eventInfo.GetActionTarget())
                return false;
            if (eventInfo.GetActionTarget()->HasAura(SPELL_PALADIN_BEACON_OF_LIGHT, eventInfo.GetActor()->GetGUID()))
                return false;
            return true;
        }

        void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();

            HealInfo* healInfo = eventInfo.GetHealInfo();
            if (!healInfo || !healInfo->GetHeal())
                return;

            uint32 heal = CalculatePct(healInfo->GetHeal(), aurEff->GetAmount());

            Unit::AuraList const& auras = GetCaster()->GetSingleCastAuras();
            for (Unit::AuraList::const_iterator itr = auras.begin(); itr != auras.end(); ++itr)
            {
                if ((*itr)->GetId() == SPELL_PALADIN_BEACON_OF_LIGHT)
                {
                    std::list<AuraApplication*> applications;
                    (*itr)->GetApplicationList(applications);
                    if (!applications.empty())
                        eventInfo.GetActor()->CastCustomSpell(SPELL_PALADIN_BEACON_OF_LIGHT_HEAL, SPELLVALUE_BASE_POINT0, heal, applications.front()->GetTarget(), true);
                    return;
                }
            }
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_pal_light_s_beacon_AuraScript::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_pal_light_s_beacon_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_pal_light_s_beacon_AuraScript();
    }
};

// 31789 - Righteous Defense
class spell_pal_righteous_defense : public SpellScriptLoader
{
public:
    spell_pal_righteous_defense() : SpellScriptLoader("spell_pal_righteous_defense") { }

    class spell_pal_righteous_defense_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_righteous_defense_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_RIGHTEOUS_DEFENSE_TAUNT))
                return false;
            return true;
        }

        SpellCastResult CheckCast()
        {
            Unit* caster = GetCaster();
            if (caster->GetTypeId() != TYPEID_PLAYER)
                return SPELL_FAILED_DONT_REPORT;

            if (Unit* target = GetExplTargetUnit())
            {
                if (!target->IsFriendlyTo(caster) || target->getAttackers().empty())
                    return SPELL_FAILED_BAD_TARGETS;
            }
            else
                return SPELL_FAILED_BAD_TARGETS;

            return SPELL_CAST_OK;
        }

        void HandleTriggerSpellLaunch(SpellEffIndex effIndex)
        {
            PreventHitDefaultEffect(effIndex);
        }

        void HandleTriggerSpellHit(SpellEffIndex effIndex)
        {
            PreventHitDefaultEffect(effIndex);
            if (Unit* target = GetHitUnit())
                GetCaster()->CastSpell(target, SPELL_PALADIN_RIGHTEOUS_DEFENSE_TAUNT, true);
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_pal_righteous_defense_SpellScript::CheckCast);
            //! WORKAROUND
            //! target select will be executed in hitphase of effect 0
            //! so we must handle trigger spell also in hit phase (default execution in launch phase)
            //! see issue #3718
            OnEffectLaunchTarget += SpellEffectFn(spell_pal_righteous_defense_SpellScript::HandleTriggerSpellLaunch, EFFECT_1, SPELL_EFFECT_TRIGGER_SPELL);
            OnEffectHitTarget += SpellEffectFn(spell_pal_righteous_defense_SpellScript::HandleTriggerSpellHit, EFFECT_1, SPELL_EFFECT_TRIGGER_SPELL);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pal_righteous_defense_SpellScript();
    }
};

// 85285 - Sacred Shield
class spell_pal_sacred_shield : public SpellScriptLoader
{
public:
    spell_pal_sacred_shield() : SpellScriptLoader("spell_pal_sacred_shield") { }

    class spell_pal_sacred_shield_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_sacred_shield_SpellScript);

        SpellCastResult CheckCast()
        {
            Unit* caster = GetCaster();
            if (caster->GetTypeId() != TYPEID_PLAYER)
                return SPELL_FAILED_DONT_REPORT;

            if (!caster->HealthBelowPct(30))
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

            return SPELL_CAST_OK;
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_pal_sacred_shield_SpellScript::CheckCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pal_sacred_shield_SpellScript();
    }
};

// 53600 - Shield of the Righteous
class spell_pal_shield_of_the_righteous : public SpellScriptLoader
{
public:
    spell_pal_shield_of_the_righteous() : SpellScriptLoader("spell_pal_shield_of_the_righteous") { }

    class spell_pal_shield_of_the_righteous_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_shield_of_the_righteous_SpellScript);

        bool Load() override
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return false;

            if (GetCaster()->ToPlayer()->getClass() != CLASS_PALADIN)
                return false;

            return true;
        }

        void ChangeDamage(SpellEffIndex /*effIndex*/)
        {
            if (!GetCaster())
                return;

            Player* player = GetCaster()->ToPlayer();

            if (!player)
                return;

            int32 damage = GetHitDamage();
            // int32 damage = CalculatePct(player->GetTotalAttackPowerValue(BASE_ATTACK), 400);
            int32 power = GetCaster()->GetHolyPoints();

            switch (power)
            {
            case 0:
            case 1:
                damage *= 1;
                break;
            case 2:
                damage *= 3;
                break;
            case 3:
                damage *= 6;
                break;
            }

            TC_LOG_INFO("server.loading", "\n\n spell_pal_shield_of_the_righteous: SetHitDamage Power: %i Damage: %i\n\n", power, damage);
            SetHitDamage(damage);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_pal_shield_of_the_righteous_SpellScript::ChangeDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pal_shield_of_the_righteous_SpellScript();
    }
};

// 85256 - Templar's Verdict
class spell_pal_templar_s_verdict : public SpellScriptLoader
{
public:
    spell_pal_templar_s_verdict() : SpellScriptLoader("spell_pal_templar_s_verdict") { }

    class spell_pal_templar_s_verdict_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_templar_s_verdict_SpellScript);

        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_DIVINE_PURPOSE_PROC))
                return false;

            return true;
        }

        bool Load() override
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return false;

            if (GetCaster()->ToPlayer()->getClass() != CLASS_PALADIN)
                return false;

            return true;
        }

        void ChangeDamage(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            int32 damage = GetHitDamage();
            int32 power = caster->GetHolyPoints();

            if (caster->HasAura(SPELL_PALADIN_DIVINE_PURPOSE_PROC))
                damage *= 7.5;  // 7.5*30% = 225%
            else
            {
                switch (power)
                {
                case 0:
                case 1: // 1 Holy Power
                //        DoNothing is 1*30 = 30%
                    break;
                case 2: // 2 Holy Power
                    damage *= 3;    // 3*30 = 90%
                    break;
                case 3: // 3 Holy Power
                    damage *= 7.5;  // 7.5*30% = 225%
                    break;
                }
            }

            TC_LOG_INFO("server.loading", "\n\n spell_pal_templar_s_verdict: SetHitDamage Power: %i Damage: %i\n\n", power, damage);
            SetHitDamage(damage);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_pal_templar_s_verdict_SpellScript::ChangeDamage, EFFECT_0, SPELL_EFFECT_WEAPON_PERCENT_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pal_templar_s_verdict_SpellScript();
    }
};

// 20154, 21084 - Seal of Righteousness - melee proc dummy (addition ${$MWS*(0.022*$AP+0.044*$SPH)} damage)
class spell_pal_seal_of_righteousness : public SpellScriptLoader
{
public:
    spell_pal_seal_of_righteousness() : SpellScriptLoader("spell_pal_seal_of_righteousness") { }

    class spell_pal_seal_of_righteousness_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_seal_of_righteousness_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_SEAL_OF_RIGHTEOUSNESS))
                return false;
            return true;
        }

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            return eventInfo.GetProcTarget();
        }

        void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();

            float ap = GetTarget()->GetTotalAttackPowerValue(BASE_ATTACK);
            int32 holy = GetTarget()->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_HOLY);
            holy += eventInfo.GetProcTarget()->SpellBaseDamageBonusTaken(SPELL_SCHOOL_MASK_HOLY);
            int32 bp = int32((ap * 0.022f + 0.044f * holy) * GetTarget()->GetAttackTime(BASE_ATTACK) / 1000);
            GetTarget()->CastCustomSpell(SPELL_PALADIN_SEAL_OF_RIGHTEOUSNESS, SPELLVALUE_BASE_POINT0, bp, eventInfo.GetProcTarget(), true, NULL, aurEff);
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_pal_seal_of_righteousness_AuraScript::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_pal_seal_of_righteousness_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_pal_seal_of_righteousness_AuraScript();
    }
};

// 498
class spell_pal_divine_protection_498 : public SpellScriptLoader
{
public:
    spell_pal_divine_protection_498() : SpellScriptLoader("spell_pal_divine_protection_498") { }

    class spell_pal_divine_protection_498_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_divine_protection_498_AuraScript);

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            // Paladin T12 Protection 4P Bonus
            if (Unit* caster = GetCaster())
                if (caster->HasAura(99091) && caster->IsAlive())
                    caster->CastSpell(caster, 99090, true);
        }

        void Register()
        {
            AfterEffectRemove += AuraEffectRemoveFn(spell_pal_divine_protection_498_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_pal_divine_protection_498_AuraScript();
    }
};

// 28789 - Holy Power
class spell_pal_t3_6p_bonus : public SpellScriptLoader
{
public:
    spell_pal_t3_6p_bonus() : SpellScriptLoader("spell_pal_t3_6p_bonus") { }

    class spell_pal_t3_6p_bonus_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_t3_6p_bonus_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo(
                {
                    SPELL_PALADIN_HOLY_POWER_ARMOR,
                    SPELL_PALADIN_HOLY_POWER_ATTACK_POWER,
                    SPELL_PALADIN_HOLY_POWER_SPELL_POWER,
                    SPELL_PALADIN_HOLY_POWER_MP5
                });
        }

        void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();

            uint32 spellId;
            Unit* caster = eventInfo.GetActor();
            Unit* target = eventInfo.GetProcTarget();

            switch (target->getClass())
            {
            case CLASS_PALADIN:
            case CLASS_PRIEST:
            case CLASS_SHAMAN:
            case CLASS_DRUID:
                spellId = SPELL_PALADIN_HOLY_POWER_MP5;
                break;
            case CLASS_MAGE:
            case CLASS_WARLOCK:
                spellId = SPELL_PALADIN_HOLY_POWER_SPELL_POWER;
                break;
            case CLASS_HUNTER:
            case CLASS_ROGUE:
                spellId = SPELL_PALADIN_HOLY_POWER_ATTACK_POWER;
                break;
            case CLASS_WARRIOR:
                spellId = SPELL_PALADIN_HOLY_POWER_ARMOR;
                break;
            default:
                return;
            }

            caster->CastSpell(target, spellId, true);
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_pal_t3_6p_bonus_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_pal_t3_6p_bonus_AuraScript();
    }
};

// 64890 Item - Paladin T8 Holy 2P Bonus
class spell_pal_t8_2p_bonus : public SpellScriptLoader
{
public:
    spell_pal_t8_2p_bonus() : SpellScriptLoader("spell_pal_t8_2p_bonus") { }

    class spell_pal_t8_2p_bonus_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_t8_2p_bonus_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({ SPELL_PALADIN_HOLY_MENDING });
        }

        void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();

            HealInfo* healInfo = eventInfo.GetHealInfo();
            if (!healInfo || !healInfo->GetHeal())
                return;

            Unit* caster = eventInfo.GetActor();
            Unit* target = eventInfo.GetProcTarget();

            SpellInfo const* spellInfo = sSpellMgr->EnsureSpellInfo(SPELL_PALADIN_HOLY_MENDING);
            int32 amount = CalculatePct(static_cast<int32>(healInfo->GetHeal()), aurEff->GetAmount());
            amount /= spellInfo->GetMaxTicks();
            // Add remaining ticks to damage done
            amount += target->GetRemainingPeriodicAmount(caster->GetGUID(), SPELL_PALADIN_HOLY_MENDING, SPELL_AURA_PERIODIC_HEAL);

            caster->CastCustomSpell(SPELL_PALADIN_HOLY_MENDING, SPELLVALUE_BASE_POINT0, amount, target, true);
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_pal_t8_2p_bonus_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_pal_t8_2p_bonus_AuraScript();
    }
};

// 20167 Seal of Insight
class spell_pal_seal_of_insight : public SpellScriptLoader
{
public:
    spell_pal_seal_of_insight() : SpellScriptLoader("spell_pal_seal_of_insight") { }

    class spell_pal_seal_of_insight_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_seal_of_insight_SpellScript);

        void HandleOnHit()
        {
            if (!GetCaster())
                return;

            uint32 heal = GetCaster()->SpellBaseHealingBonusDone(SPELL_SCHOOL_MASK_HOLY) * 0.16f;
            SetHitHeal(heal);
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_pal_seal_of_insight_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_seal_of_insight_SpellScript();
    }
};

// 26573 Consecration (periodic dummy)
class spell_pal_consecration : public SpellScriptLoader
{
public:
    spell_pal_consecration() : SpellScriptLoader("spell_pal_consecration") { }

    class spell_pal_consecration_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_consecration_AuraScript);

        void HandlePeriodic(AuraEffect const* aurEff)
        {
            if (!GetCaster())
                return;

            GetCaster()->CastSpell(GetCaster(), SPELL_PALADIN_CONSECRATION_DAMAGE, true);
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_pal_consecration_AuraScript::HandlePeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_pal_consecration_AuraScript();
    }
};

// 81297 Consecration (Damage)
class spell_pal_consecration_damage : public SpellScriptLoader
{
public:
    spell_pal_consecration_damage() : SpellScriptLoader("spell_pal_consecration_damage") { }

    class spell_pal_consecration_damage_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_consecration_damage_SpellScript);

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                uint32 damage = CalculatePct(_player->GetTotalAttackPowerValue(BASE_ATTACK), 30) * 9;
                SetHitDamage(damage);
            }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_pal_consecration_damage_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_consecration_damage_SpellScript();
    }
};

// 85222 - Light of Dawn
class spell_pal_ligh_of_dawn : public SpellScriptLoader
{
public:
    spell_pal_ligh_of_dawn() : SpellScriptLoader("spell_pal_ligh_of_dawn") { }

    class spell_pal_ligh_of_dawn_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_ligh_of_dawn_SpellScript);

        void HandleOnHit()
        {
            GetCaster()->CastSpell(GetHitUnit(), 225311, true);
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_pal_ligh_of_dawn_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_ligh_of_dawn_SpellScript();
    }
};

// 31935 Avenger Shield
class spell_pal_avenger_shield : public SpellScriptLoader
{
public:
    spell_pal_avenger_shield() : SpellScriptLoader("spell_pal_avenger_shield") { }

    class spell_pal_avenger_shield_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_avenger_shield_SpellScript);

        void HandleDamage(SpellEffIndex effIndex)
        {
            if (!GetCaster())
                return;

            if (Player* player = GetCaster()->ToPlayer())
            {
                uint32 damage = CalculatePct(player->GetTotalAttackPowerValue(BASE_ATTACK), 435);

                SetHitDamage(damage);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_pal_avenger_shield_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_avenger_shield_SpellScript();
    }
};

// 19750 Flash of Light
class spell_pal_flash_of_light : public SpellScriptLoader
{
public:
    spell_pal_flash_of_light() : SpellScriptLoader("spell_pal_flash_of_light") { }

    class spell_pal_flash_of_light_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_flash_of_light_SpellScript);

        void HandleOnHeal(SpellEffIndex /*effIndex*/)
        {
            if (!GetCaster())
                return;

            if (Player* player = GetCaster()->ToPlayer())
            {
                uint32 heal = CalculatePct(player->SpellBaseHealingBonusDone(SPELL_SCHOOL_MASK_HOLY), 450);

                SetHitHeal(heal);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_pal_flash_of_light_SpellScript::HandleOnHeal, EFFECT_0, SPELL_EFFECT_HEAL);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_flash_of_light_SpellScript();
    }
};

// 85673 - Word of Glory
class spell_pal_word_of_glory : public SpellScriptLoader
{
public:
    spell_pal_word_of_glory() : SpellScriptLoader("spell_pal_word_of_glory") { }

    class spell_pal_word_of_glory_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_word_of_glory_SpellScript);

        bool Load() override
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return false;

            if (GetCaster()->ToPlayer()->getClass() != CLASS_PALADIN)
                return false;

            return true;
        }

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo(
                {
                    SPELL_PALADIN_DIVINE_PURPOSE_PROC,
                    SPELL_PALADIN_ETERNAL_GLORY_PROC,
                    SPELL_PALADIN_SELFLESS_HEALER_R1,
                    SPELL_PALADIN_ETERNAL_GLORY_R1
                });
        }

        void HandleHeal(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            int32 heal = GetHitHeal();
            int32 power = caster->GetHolyPoints();

            if (caster->HasAura(SPELL_PALADIN_DIVINE_PURPOSE_PROC))
                heal += heal * 2;
            else
            {
                switch (power)
                {
                case 0:
                case 1: // 1 Holy Power
                //        DoNothing 
                    heal += heal * 1;
                    break;
                case 2: // 2 Holy Power
                    heal += heal * 2;
                    break;
                case 3: // 3 Holy Power
                    heal += heal * 3;
                    break;
                }
            }

            if (caster != GetHitUnit())
                if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_PALADIN_SELFLESS_HEALER_R2, EFFECT_0))
                    heal += CalculatePct(heal, aurEff->GetAmount());

            TC_LOG_INFO("server.loading", "\n\n spell_pal_word_of_glory: SetHitHeal Power: %i Heal: %i\n\n", power, heal);
            SetHitHeal(heal);
        }

        void HandleEternalGlory()
        {
            if (Unit* caster = GetCaster())
            {
                if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_PALADIN_ETERNAL_GLORY_R1, EFFECT_0))
                {
                    if (roll_chance_i(aurEff->GetAmount()))
                    {
                        uint8 powerCost = 1 + GetSpell()->GetPowerCost();
                        caster->CastCustomSpell(SPELL_PALADIN_ETERNAL_GLORY_PROC, SPELLVALUE_BASE_POINT0, powerCost, caster, true, nullptr, aurEff);
                    }
                }
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_pal_word_of_glory_SpellScript::HandleHeal, EFFECT_0, SPELL_EFFECT_HEAL);
            AfterCast += SpellCastFn(spell_pal_word_of_glory_SpellScript::HandleEternalGlory);
        }
    };

    class spell_pal_word_of_glory_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_word_of_glory_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({ SPELL_PALADIN_DIVINE_PURPOSE_PROC });
        }

        void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetTarget();
            if (!caster || !target)
                return;

            int32 power = caster->GetHolyPoints();

            if (caster->HasAura(SPELL_PALADIN_DIVINE_PURPOSE_PROC))
                amount += amount * 2;
            else
            {
                switch (power)
                {
                case 0:
                case 1: // 1 Holy Power
                    amount += amount * 1;
                    break;
                case 2: // 2 Holy Power
                    amount += amount * 2;
                    break;
                case 3: // 3 Holy Power
                    amount += amount * 3;
                    break;
                }
            }

            if (caster == target)
            {
                // Guarded by the Light
                if (AuraEffect const* const aurEff = caster->GetAuraEffectOfRankedSpell(SPELL_PALADIN_GUARDED_BY_THE_LIGHT, EFFECT_0))
                    amount += CalculatePct(amount, aurEff->GetAmount());
            }
            else
            {
                // Selfless Healer
                if (AuraEffect const* const aurEff = caster->GetAuraEffectOfRankedSpell(SPELL_PALADIN_SELFLESS_HEALER_R1, EFFECT_0))
                    amount += CalculatePct(amount, aurEff->GetAmount());
            }

            TC_LOG_INFO("server.loading", "\n\n spell_pal_word_of_glory: CalculateAmount Power: %i Amount: %i\n\n", power, amount);
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_word_of_glory_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_PERIODIC_HEAL);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_word_of_glory_SpellScript();
    }

    AuraScript* GetAuraScript() const
    {
        return new spell_pal_word_of_glory_AuraScript();
    }
};

// 84963 - Inquisition
class spell_pal_inquisition : public SpellScriptLoader
{
public:
    spell_pal_inquisition() : SpellScriptLoader("spell_pal_inquisition") { }

    class spell_pal_inquisition_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_inquisition_SpellScript);

        void ChangeDuration()
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            if (Aura* aura = caster->GetAura(GetSpellInfo()->Id))
            {
                int32 power = caster->GetHolyPoints();
                int32 duration = aura->GetDuration();

                if (caster->HasAura(SPELL_PALADIN_DIVINE_PURPOSE_PROC))
                    duration *= 2;
                else
                {
                    switch (power)
                    {
                    case 0:
                    case 1: // 1 Holy Power
                        duration *= 1;
                        break;
                    case 2: // 2 Holy Power
                        duration *= 2;
                        break;
                    case 3: // 3 Holy Power
                        duration *= 3;
                        break;
                    }
                }

                TC_LOG_INFO("server.loading", "\n\n spell_pal_inquisition: ChangeDuration Power: %i Duration: %i\n\n", power, duration);
                aura->SetDuration(duration);
            }
        }

        void Register()
        {
            AfterHit += SpellHitFn(spell_pal_inquisition_SpellScript::ChangeDuration);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_inquisition_SpellScript();
    }
};

// -87168 - Long Arm of the Law (rang1, rang2=87172)
class spell_pal_long_arm_of_the_law : public SpellScriptLoader
{
public:
    spell_pal_long_arm_of_the_law() : SpellScriptLoader("spell_pal_long_arm_of_the_law") { }

    class spell_pal_long_arm_of_the_law_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_long_arm_of_the_law_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({ SPELL_PALADIN_LONG_ARM_OF_THE_LAW });
        }

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (roll_chance_i(GetEffect(EFFECT_0)->GetAmount()))
                if (Spell const* spell = eventInfo.GetProcSpell())
                    if (Unit* target = spell->m_targets.GetUnitTarget())
                        return (eventInfo.GetActor()->GetDistance2d(target) > 15.0f);

            return false;
        }

        void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();
            GetTarget()->CastSpell(GetTarget(), SPELL_PALADIN_LONG_ARM_OF_THE_LAW, true, nullptr, aurEff);
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_pal_long_arm_of_the_law_AuraScript::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_pal_long_arm_of_the_law_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_pal_long_arm_of_the_law_AuraScript();
    }
};

// 86704 - Ancient Fury
class spell_pal_ancient_fury : public SpellScriptLoader
{
public:
    spell_pal_ancient_fury() : SpellScriptLoader("spell_pal_ancient_fury") { }

    class spell_pal_ancient_fury_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_ancient_fury_SpellScript);

        void CountTargets(std::list<WorldObject*>& targetList)
        {
            _targetCount = targetList.size();
        }

        void ChangeDamage(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();

            if (caster && target && _targetCount)
            {
                int32 damage = GetHitDamage();

                if (Aura* aura = caster->GetAura(SPELL_PALADIN_GOAK_ANCIENT_POWER))
                {
                    damage = caster->SpellDamageBonusDone(target, GetSpellInfo(), damage, SPELL_DIRECT_DAMAGE);
                    damage = (damage * aura->GetStackAmount());

                    // "divided evenly among all targets"
                    damage /= _targetCount;
                }

                SetHitDamage(damage);
            }
        }
    private:
        uint32 _targetCount;

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_ancient_fury_SpellScript::CountTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            OnEffectHitTarget += SpellEffectFn(spell_pal_ancient_fury_SpellScript::ChangeDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_ancient_fury_SpellScript();
    }
};

// 86698 - Guardian of Ancient Kings Retribution
class spell_pal_guardian_of_ancient_kings_retri : public SpellScriptLoader
{
public:
    spell_pal_guardian_of_ancient_kings_retri() : SpellScriptLoader("spell_pal_guardian_of_ancient_kings_retri") { }

    class spell_pal_guardian_of_ancient_kings_retri_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_guardian_of_ancient_kings_retri_AuraScript);

        void Remove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_EXPIRE)
                return;

            Unit* target = GetTarget();
            Aura* stacks = target->GetAura(SPELL_PALADIN_GOAK_ANCIENT_POWER, target->GetGUID());
            if (!stacks)
                return;

            int32 bp0 = sSpellMgr->GetSpellInfo(SPELL_PALADIN_GOAK_ANCIENT_FURY)->Effects[EFFECT_0].CalcValue(target) * stacks->GetStackAmount();
            target->CastCustomSpell(target, SPELL_PALADIN_GOAK_ANCIENT_FURY, &bp0, NULL, NULL, true);
            target->RemoveAurasDueToSpell(SPELL_PALADIN_GOAK_ANCIENT_POWER);
            target->RemoveAurasDueToSpell(SPELL_PALADIN_GOAK_ANCIENT_CRUSADER);
        }

        void Register()
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_pal_guardian_of_ancient_kings_retri_AuraScript::Remove, EFFECT_2, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_pal_guardian_of_ancient_kings_retri_AuraScript();
    }
};

// 86150 - Guardian of Ancient Kings action bar spell
class spell_pal_guardian_of_ancient_kings : public SpellScriptLoader
{
public:
    spell_pal_guardian_of_ancient_kings() : SpellScriptLoader("spell_pal_guardian_of_ancient_kings") { }

    class spell_pal_guardian_of_ancient_kings_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_guardian_of_ancient_kings_SpellScript);

        void HandleOnHit()
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            // Choose which guardian to summon based on spec
            switch (caster->ToPlayer()->GetPrimaryTalentTree(caster->ToPlayer()->GetActiveSpec()))
            {
            case TALENT_TREE_PALADIN_HOLY:
                caster->RemoveAllMinionsByEntry(46499);
                caster->CastSpell(caster, SPELL_PALADIN_GOAK_HOLY_SUMMON, true);
                caster->CastSpell(caster, SPELL_PALADIN_GOAK_ANCIENT_HEALER, true);
                break;
            case TALENT_TREE_PALADIN_PROTECTION:
                caster->RemoveAllMinionsByEntry(46490);
                caster->CastSpell(caster, SPELL_PALADIN_GOAK_PROTECTION_SUMMON, true);
                break;
            case TALENT_TREE_PALADIN_RETRIBUTION:
                caster->RemoveAllMinionsByEntry(46506);
                caster->CastSpell(caster, SPELL_PALADIN_GOAK_RETRIBUTION_SUMMON, true);
                caster->CastSpell(caster, SPELL_PALADIN_GOAK_ANCIENT_CRUSADER, true);
                break;
            default:
                return;
            }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_pal_guardian_of_ancient_kings_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_guardian_of_ancient_kings_SpellScript();
    }
};

// 54158 Judgement (based on Seals for Judgement )
class spell_pal_judgement_54158 : public SpellScriptLoader
{
public:
    spell_pal_judgement_54158() : SpellScriptLoader("spell_pal_judgement_54158") { }

    class spell_pal_judgement_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_judgement_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            Player* caster = GetCaster()->ToPlayer();
            int32 spellPower = caster->SpellBaseDamageBonusDone(GetSpellInfo()->GetSchoolMask());
            int32 attackPower = caster->GetTotalAttackPowerValue(BASE_ATTACK);
            int32 basepoints0 = 0;
            Unit::AuraApplicationMap & sealAuras = caster->GetAppliedAuras();
            for (Unit::AuraApplicationMap::iterator iter = sealAuras.begin(); iter != sealAuras.end(); iter++)
            {
                Aura* aura = iter->second->GetBase();
                if (aura->GetSpellInfo()->GetSpellSpecific() == SPELL_SPECIFIC_SEAL)
                {
                    switch (aura->GetSpellInfo()->Id)
                    {
                    case 20165: // Seal of Insight
                        basepoints0 = 0.25f * spellPower + 0.16f * attackPower;
                        break;
                    case 20154: // Seal of Righteousness
                        basepoints0 = 0.32f * spellPower + 0.2f * attackPower;
                        break;
                    case 20164: // Seal of Justice
                        basepoints0 = 0.25f * spellPower + 0.16f * attackPower;
                        break;
                    case 31801: // Seal of Truth
                    {
                        basepoints0 = 0.223f * spellPower + 0.142f * attackPower;
                        // Damage is increased by 20% per stack
                        if (Aura* censure = GetHitUnit()->GetAura(31803, caster->GetGUID()))
                            AddPct(basepoints0, censure->GetStackAmount() * 20);
                        break;
                    }
                    }
                    break;
                }
            }
            caster->CastCustomSpell(GetHitUnit(), 54158, &basepoints0, NULL, NULL, true);
            // Long arm of the law
            if (AuraEffect* aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_PALADIN, 3013, EFFECT_0))
                if (roll_chance_i(aurEff->GetAmount()))
                    if (caster->GetDistance(GetHitUnit()) > 15.0f)
                        caster->CastSpell(caster, 87173, true);

            // Communion
            if (AuraEffect* communion = caster->GetAuraEffect(31876, EFFECT_1, caster->GetGUID()))
                caster->CastSpell(caster, 57669, true);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_pal_judgement_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_judgement_SpellScript();
    }
};

void AddSC_paladin_spell_scripts()
{
    //new spell_pal_ardent_defender();
    new spell_pal_aura_mastery();
    new spell_pal_aura_mastery_immune();
    new spell_pal_avenging_wrath();
    new spell_pal_beacon_of_light();
    new spell_pal_blessing_of_faith();
    new spell_pal_divine_sacrifice();
    new spell_pal_divine_storm();
    new spell_pal_divine_storm_dummy();
    new spell_pal_exorcism_and_holy_wrath_damage();
    new spell_pal_eye_for_an_eye();
    new spell_pal_glyph_of_holy_light();
    new spell_pal_grand_crusader();
    new spell_pal_hand_of_sacrifice();
    new spell_pal_holy_shock();
    new spell_pal_improved_aura_effect("spell_pal_improved_concentraction_aura_effect");
    new spell_pal_improved_aura_effect("spell_pal_improved_devotion_aura_effect");
    new spell_pal_improved_aura_effect("spell_pal_sanctified_retribution_effect");
    new spell_pal_item_healing_discount();
    new spell_pal_item_t6_trinket();
    new spell_pal_judgement_20271();
    new spell_pal_lay_on_hands();
    new spell_pal_light_s_beacon();
    new spell_pal_righteous_defense();
    new spell_pal_sacred_shield();
    new spell_pal_shield_of_the_righteous();
    new spell_pal_templar_s_verdict();
    new spell_pal_seal_of_righteousness();
    new spell_pal_divine_protection_498();
    new spell_pal_t3_6p_bonus();
    new spell_pal_t8_2p_bonus();
    new spell_pal_seal_of_insight();
    new spell_pal_consecration();
    new spell_pal_consecration_damage();
    new spell_pal_ligh_of_dawn();
    new spell_pal_avenger_shield();
    new spell_pal_flash_of_light();
    new spell_pal_word_of_glory();
    new spell_pal_inquisition();
    new spell_pal_long_arm_of_the_law();
    new spell_pal_guardian_of_ancient_kings_retri();
    new spell_pal_guardian_of_ancient_kings();
    new spell_pal_ancient_fury();
    new spell_pal_judgement_54158();
}
