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
 * Scripts for spells with SPELLFAMILY_DEATHKNIGHT and SPELLFAMILY_GENERIC spells used by deathknight players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_dk_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Containers.h"
#include "SpellAuras.h"
#include "ObjectMgr.h"
#include "ScriptedCreature.h"
#include "Unit.h"

enum DeathKnightSpells
{
    SPELL_DK_ANTI_MAGIC_SHELL_TALENT            = 51052,
    SPELL_DK_BLACK_ICE_R1                       = 49140,
    SPELL_DK_BLOOD_BOIL_TRIGGERED               = 65658,
    SPELL_DK_BLOOD_GORGED_HEAL                  = 50454,
    SPELL_DK_BLOOD_PRESENCE                     = 48263,
    SPELL_DK_BLOOD_PRESENCE_TRIGGERED           = 61261,
    SPELL_DK_BLOOD_SHIELD_MASTERY               = 77513,
    SPELL_DK_BLOOD_SHIELD_ABSORB                = 77535,
    SPELL_DK_BUTCHERY                           = 50163,
    SPELL_DK_CORPSE_EXPLOSION_TRIGGERED         = 43999,
    SPELL_DK_CORPSE_EXPLOSION_VISUAL            = 51270,
    SPELL_DK_DEATH_COIL_DAMAGE                  = 47632,
    SPELL_DK_DEATH_COIL_HEAL                    = 47633,
    SPELL_DK_DEATH_STRIKE_HEAL                  = 45470,
    SPELL_DK_DEATH_STRIKE_ENABLER               = 89832,
    SPELL_DK_FROST_PRESENCE                     = 48266,
    SPELL_DK_GHOUL_EXPLODE                      = 47496,
    SPELL_DK_GLYPH_OF_CHAINS_OF_ICE             = 58620,
    SPELL_DK_GLYPH_OF_CHAINS_OF_ICE_DAMAGE      = 58621,
    SPELL_DK_GLYPH_OF_ICEBOUND_FORTITUDE        = 58625,
    SPELL_DK_GLYPH_OF_SCOURGE_STRIKE            = 58642,
    SPELL_DK_IMPROVED_BLOOD_PRESENCE_R1         = 50365,
    SPELL_DK_IMPROVED_DEATH_STRIKE              = 62905,
    SPELL_DK_IMPROVED_FROST_PRESENCE_R1         = 50384,
    SPELL_DK_IMPROVED_FROST_PRESENCE_TRIGGERED  = 63621,
    SPELL_DK_IMPROVED_UNHOLY_PRESENCE_R1        = 50391,
    SPELL_DK_IMPROVED_UNHOLY_PRESENCE_TRIGGERED = 63622,
    SPELL_DK_ITEM_SIGIL_VENGEFUL_HEART          = 64962,
    SPELL_DK_ITEM_T8_MELEE_4P_BONUS             = 64736,
    SPELL_DK_MASTER_OF_GHOULS                   = 52143,
    SPELL_DK_MERCILESS_COMBAT_RANK_1            = 49024,
    SPELL_DK_MERCILESS_COMBAT_RANK_2            = 49538,
    SPELL_DK_RAISE_DEAD_USE_REAGENT             = 48289,
    SPELL_DK_RUNIC_POWER_ENERGIZE               = 49088,
    SPELL_DK_RUNE_TAP                           = 48982,
    SPELL_DK_SCENT_OF_BLOOD                     = 50422,
    SPELL_DK_SCOURGE_STRIKE_TRIGGERED           = 70890,
    SPELL_DK_UNHOLY_PRESENCE                    = 48265,
    SPELL_DK_WILL_OF_THE_NECROPOLIS             = 96171,
    SPELL_DK_WILL_OF_THE_NECROPOLIS_TALENT_R1   = 49189,
    SPELL_DK_WILL_OF_THE_NECROPOLIS_AURA_R1     = 52284,
	SPELL_DK_DEATH_GRIP							= 49560,
    SPELL_DK_RUNIC_RETURN                       = 61258,

    NPC_DK_DANCING_RUNE_WEAPON                  = 27893,
};

enum DeathKnightSpellIcons
{
    DK_ICON_ID_IMPROVED_DEATH_STRIKE = 2751
};

enum DKPetCalculate
{
    SPELL_DEATH_KNIGHT_RUNE_WEAPON_02 = 51906,
    SPELL_DEATH_KNIGHT_PET_SCALING_01 = 54566,
    SPELL_DEATH_KNIGHT_PET_SCALING_02 = 51996,
    SPELL_DEATH_KNIGHT_PET_SCALING_03 = 61697,
    SPELL_NIGHT_OF_THE_DEAD = 55620,
    ENTRY_ARMY_OF_THE_DEAD_GHOUL = 24207,
    SPELL_DEATH_KNIGHT_GLYPH_OF_GHOUL = 58686,
};

// 50462 - Anti-Magic Shell (on raid member)
class spell_dk_anti_magic_shell_raid : public SpellScriptLoader
{
    public:
        spell_dk_anti_magic_shell_raid() : SpellScriptLoader("spell_dk_anti_magic_shell_raid") { }

        class spell_dk_anti_magic_shell_raid_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_anti_magic_shell_raid_AuraScript);

            uint32 absorbPct;

            bool Load() override
            {
                absorbPct = GetSpellInfo()->Effects[EFFECT_0].CalcValue(GetCaster());
                return true;
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                /// @todo this should absorb limited amount of damage, but no info on calculation formula
                amount = -1;
            }

            void Absorb(AuraEffect* /*aurEff*/, DamageInfo & dmgInfo, uint32 & absorbAmount)
            {
                absorbAmount = CalculatePct(dmgInfo.GetDamage(), absorbPct);
            }

            void Register() override
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_anti_magic_shell_raid_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                OnEffectAbsorb += AuraEffectAbsorbFn(spell_dk_anti_magic_shell_raid_AuraScript::Absorb, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_anti_magic_shell_raid_AuraScript();
        }
};

// 48707 - Anti-Magic Shell (on self)
class spell_dk_anti_magic_shell_self : public SpellScriptLoader
{
    public:
        spell_dk_anti_magic_shell_self() : SpellScriptLoader("spell_dk_anti_magic_shell_self") { }

        class spell_dk_anti_magic_shell_self_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_anti_magic_shell_self_AuraScript);

            uint32 absorbPct, hpPct;
            bool Load() override
            {
                absorbPct = GetSpellInfo()->Effects[EFFECT_0].CalcValue(GetCaster());
                hpPct = GetSpellInfo()->Effects[EFFECT_1].CalcValue(GetCaster());
                return true;
            }

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_RUNIC_POWER_ENERGIZE))
                    return false;
                return true;
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                amount = GetCaster()->CountPctFromMaxHealth(hpPct);
            }

            void Absorb(AuraEffect* /*aurEff*/, DamageInfo & dmgInfo, uint32 & absorbAmount)
            {
                absorbAmount = std::min(CalculatePct(dmgInfo.GetDamage(), absorbPct), GetTarget()->CountPctFromMaxHealth(hpPct));
            }

            void Trigger(AuraEffect* aurEff, DamageInfo& /*dmgInfo*/, uint32& absorbAmount)
            {
                // damage absorbed by Anti-Magic Shell energizes the DK with additional runic power.
                // This, if I'm not mistaken, shows that we get back ~20% of the absorbed damage as runic power.
                int32 bp = CalculatePct(absorbAmount, 20);
                GetTarget()->CastCustomSpell(SPELL_DK_RUNIC_POWER_ENERGIZE, SPELLVALUE_BASE_POINT0, bp, GetTarget(), true, NULL, aurEff);
            }

            void Register() override
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_anti_magic_shell_self_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                OnEffectAbsorb += AuraEffectAbsorbFn(spell_dk_anti_magic_shell_self_AuraScript::Absorb, EFFECT_0);
                AfterEffectAbsorb += AuraEffectAbsorbFn(spell_dk_anti_magic_shell_self_AuraScript::Trigger, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_anti_magic_shell_self_AuraScript();
        }
};

// 50461 - Anti-Magic Zone
class spell_dk_anti_magic_zone : public SpellScriptLoader
{
    public:
        spell_dk_anti_magic_zone() : SpellScriptLoader("spell_dk_anti_magic_zone") { }

        class spell_dk_anti_magic_zone_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_anti_magic_zone_AuraScript);

            uint32 absorbPct;

            bool Load() override
            {
                absorbPct = GetSpellInfo()->Effects[EFFECT_0].CalcValue(GetCaster());
                return true;
            }

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_ANTI_MAGIC_SHELL_TALENT))
                    return false;
                return true;
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                SpellInfo const* talentSpell = sSpellMgr->EnsureSpellInfo(SPELL_DK_ANTI_MAGIC_SHELL_TALENT);
                amount = talentSpell->Effects[EFFECT_0].CalcValue(GetCaster());
                if (Player* player = GetCaster()->ToPlayer())
                     amount += int32(2 * player->GetTotalAttackPowerValue(BASE_ATTACK));
            }

            void Absorb(AuraEffect* /*aurEff*/, DamageInfo & dmgInfo, uint32 & absorbAmount)
            {
                 absorbAmount = CalculatePct(dmgInfo.GetDamage(), absorbPct);
            }

            void Register() override
            {
                 DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_anti_magic_zone_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                 OnEffectAbsorb += AuraEffectAbsorbFn(spell_dk_anti_magic_zone_AuraScript::Absorb, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_anti_magic_zone_AuraScript();
        }
};

// 48721 - Blood Boil
class spell_dk_blood_boil : public SpellScriptLoader
{
    public:
        spell_dk_blood_boil() : SpellScriptLoader("spell_dk_blood_boil") { }

        class spell_dk_blood_boil_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_blood_boil_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_BLOOD_BOIL_TRIGGERED))
                    return false;
                return true;
            }

            bool Load() override
            {
                _executed = false;
                return GetCaster()->GetTypeId() == TYPEID_PLAYER && GetCaster()->getClass() == CLASS_DEATH_KNIGHT;
            }

            void HandleAfterHit()
            {
                if (_executed || !GetHitUnit())
                    return;

                _executed = true;
                GetCaster()->CastSpell(GetCaster(), SPELL_DK_BLOOD_BOIL_TRIGGERED, true);
            }

            void Register() override
            {
                AfterHit += SpellHitFn(spell_dk_blood_boil_SpellScript::HandleAfterHit);
            }

            bool _executed;
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_blood_boil_SpellScript();
        }
};

// 50453 - Bloodworms Health Leech
class spell_dk_blood_gorged : public SpellScriptLoader
{
    public:
        spell_dk_blood_gorged() : SpellScriptLoader("spell_dk_blood_gorged") { }

        class spell_dk_blood_gorged_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_blood_gorged_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_BLOOD_GORGED_HEAL))
                    return false;
                return true;
            }

            bool Load() override
            {
                _procTarget = nullptr;
                return true;
            }

            bool CheckProc(ProcEventInfo& /*eventInfo*/)
            {
                _procTarget = GetTarget()->GetOwner();
                return _procTarget;
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                int32 heal = int32(CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), 150));
                GetTarget()->CastCustomSpell(SPELL_DK_BLOOD_GORGED_HEAL, SPELLVALUE_BASE_POINT0, heal, _procTarget, true, NULL, aurEff);
            }

            void Register() override
            {
                DoCheckProc += AuraCheckProcFn(spell_dk_blood_gorged_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_dk_blood_gorged_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
            }

        private:
            Unit* _procTarget;
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_blood_gorged_AuraScript();
        }
};

// -48979 - Butchery
class spell_dk_butchery : public SpellScriptLoader
{
    public:
        spell_dk_butchery() : SpellScriptLoader("spell_dk_butchery") { }

        class spell_dk_blood_gorged_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_blood_gorged_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_BUTCHERY))
                    return false;
                return true;
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
            {
                PreventDefaultAction();
                GetTarget()->CastCustomSpell(SPELL_DK_BUTCHERY, SPELLVALUE_BASE_POINT0, aurEff->GetAmount(), GetTarget(), true, NULL, aurEff);
            }

            void Register() override
            {
                OnEffectProc += AuraEffectProcFn(spell_dk_blood_gorged_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_blood_gorged_AuraScript();
        }
};

// 47541, 52375, 59134, -62900 - Death Coil
class spell_dk_death_coil : public SpellScriptLoader
{
    public:
        spell_dk_death_coil() : SpellScriptLoader("spell_dk_death_coil") { }

        class spell_dk_death_coil_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_death_coil_SpellScript);

            bool Validate(SpellInfo const* /*spell*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_DEATH_COIL_DAMAGE) || !sSpellMgr->GetSpellInfo(SPELL_DK_DEATH_COIL_HEAL))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                int32 damage = GetEffectValue();
                Unit* caster = GetCaster();
                if (Unit* target = GetHitUnit())
                {
                    if (caster->IsFriendlyTo(target))
                    {
                        int32 bp = int32(damage * 1.5f);
                        caster->CastCustomSpell(target, SPELL_DK_DEATH_COIL_HEAL, &bp, NULL, NULL, true);
                    }
                    else
                    {
                        if (AuraEffect const* auraEffect = caster->GetAuraEffect(SPELL_DK_ITEM_SIGIL_VENGEFUL_HEART, EFFECT_1))
                            damage += auraEffect->GetBaseAmount();
                        caster->CastCustomSpell(target, SPELL_DK_DEATH_COIL_DAMAGE, &damage, NULL, NULL, true);
                    }
                }
            }

            SpellCastResult CheckCast()
            {
                Unit* caster = GetCaster();
                if (Unit* target = GetExplTargetUnit())
                {
                    if (!caster->IsFriendlyTo(target) && !caster->isInFront(target))
                        return SPELL_FAILED_UNIT_NOT_INFRONT;

                    if (target->IsFriendlyTo(caster) && target->GetCreatureType() != CREATURE_TYPE_UNDEAD)
                        return SPELL_FAILED_BAD_TARGETS;
                }
                else
                    return SPELL_FAILED_BAD_TARGETS;

                return SPELL_CAST_OK;
            }

            void Register() override
            {
                OnCheckCast += SpellCheckCastFn(spell_dk_death_coil_SpellScript::CheckCast);
                OnEffectHitTarget += SpellEffectFn(spell_dk_death_coil_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_death_coil_SpellScript();
        }
};

// 52751 - Death Gate
class spell_dk_death_gate : public SpellScriptLoader
{
    public:
        spell_dk_death_gate() : SpellScriptLoader("spell_dk_death_gate") { }

        class spell_dk_death_gate_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_death_gate_SpellScript);

            SpellCastResult CheckClass()
            {
                if (GetCaster()->getClass() != CLASS_DEATH_KNIGHT)
                {
                    SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_MUST_BE_DEATH_KNIGHT);
                    return SPELL_FAILED_CUSTOM_ERROR;
                }

                return SPELL_CAST_OK;
            }

            void HandleScript(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                if (Unit* target = GetHitUnit())
                    target->CastSpell(target, GetEffectValue(), false);
            }

            void Register() override
            {
                OnCheckCast += SpellCheckCastFn(spell_dk_death_gate_SpellScript::CheckClass);
                OnEffectHitTarget += SpellEffectFn(spell_dk_death_gate_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_death_gate_SpellScript();
        }
};

// 49560 - Death Grip
class spell_dk_death_grip : public SpellScriptLoader
{
    public:
        spell_dk_death_grip() : SpellScriptLoader("spell_dk_death_grip") { }

        class spell_dk_death_grip_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_death_grip_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                int32 damage = GetEffectValue();
                Position const* pos = GetExplTargetDest();
                if (Unit* target = GetHitUnit())
                {
                    if (!target->HasAuraType(SPELL_AURA_DEFLECT_SPELLS)) // Deterrence
                        target->CastSpell(pos->GetPositionX(), pos->GetPositionY(), pos->GetPositionZ(), damage, true);
                }
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_dk_death_grip_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }

        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_death_grip_SpellScript();
        }
};

// 48743 - Death Pact
class spell_dk_death_pact : public SpellScriptLoader
{
    public:
        spell_dk_death_pact() : SpellScriptLoader("spell_dk_death_pact") { }

        class spell_dk_death_pact_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_death_pact_SpellScript);

            SpellCastResult CheckCast()
            {
                // Check if we have valid targets, otherwise skip spell casting here
                if (Player* player = GetCaster()->ToPlayer())
                    for (Unit::ControlList::const_iterator itr = player->m_Controlled.begin(); itr != player->m_Controlled.end(); ++itr)
                        if (Creature* undeadPet = (*itr)->ToCreature())
                            if (undeadPet->IsAlive() &&
                                undeadPet->GetOwnerGUID() == player->GetGUID() &&
                                undeadPet->GetCreatureType() == CREATURE_TYPE_UNDEAD &&
                                undeadPet->IsWithinDist(player, 100.0f, false))
                                return SPELL_CAST_OK;

                return SPELL_FAILED_NO_PET;
            }

            void FilterTargets(std::list<WorldObject*>& targetList)
            {
                Unit* target = nullptr;
                for (std::list<WorldObject*>::iterator itr = targetList.begin(); itr != targetList.end(); ++itr)
                {
                    if (Unit* unit = (*itr)->ToUnit())
                        if (unit->GetOwnerGUID() == GetCaster()->GetGUID() && unit->GetCreatureType() == CREATURE_TYPE_UNDEAD)
                        {
                            target = unit;
                            break;
                        }
                }

                targetList.clear();
                if (target)
                    targetList.push_back(target);
            }

            void Register() override
            {
                OnCheckCast += SpellCheckCastFn(spell_dk_death_pact_SpellScript::CheckCast);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dk_death_pact_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ALLY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_death_pact_SpellScript();
        }
};

// 49998 - Death Strike
class spell_dk_death_strike : public SpellScriptLoader
{
    public:
        spell_dk_death_strike() : SpellScriptLoader("spell_dk_death_strike") { }

        class spell_dk_death_strike_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_death_strike_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_DEATH_STRIKE_ENABLER) ||
                    !sSpellMgr->GetSpellInfo(SPELL_DK_DEATH_STRIKE_HEAL) ||
                    !sSpellMgr->GetSpellInfo(SPELL_DK_BLOOD_SHIELD_MASTERY) ||
                    !sSpellMgr->GetSpellInfo(SPELL_DK_BLOOD_SHIELD_ABSORB))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (AuraEffect* enabler = GetCaster()->GetAuraEffect(SPELL_DK_DEATH_STRIKE_ENABLER, EFFECT_0, GetCaster()->GetGUID()))
                {
                    // Call CalculateAmount() to constantly fire the AuraEffect's HandleCalcAmount method
                    int32 heal = CalculatePct(enabler->CalculateAmount(GetCaster()), GetSpellInfo()->Effects[EFFECT_0].DamageMultiplier);

                    if (AuraEffect const* aurEff = GetCaster()->GetAuraEffectOfRankedSpell(SPELL_DK_IMPROVED_DEATH_STRIKE, EFFECT_2))
                        heal = AddPct(heal, aurEff->GetAmount());

                    heal = std::max(heal, int32(GetCaster()->CountPctFromMaxHealth(GetEffectValue())));
                    GetCaster()->CastCustomSpell(SPELL_DK_DEATH_STRIKE_HEAL, SPELLVALUE_BASE_POINT0, heal, GetCaster(), true);
                }

                if (!GetCaster()->HasAura(SPELL_DK_BLOOD_PRESENCE))
                    return;

                if (AuraEffect const* aurEff = GetCaster()->GetAuraEffect(SPELL_DK_BLOOD_SHIELD_MASTERY, EFFECT_0))
                    GetCaster()->CastCustomSpell(SPELL_DK_BLOOD_SHIELD_ABSORB, SPELLVALUE_BASE_POINT0, GetCaster()->CountPctFromMaxHealth(aurEff->GetAmount()), GetCaster());
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_dk_death_strike_SpellScript::HandleDummy, EFFECT_2, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_death_strike_SpellScript();
        }
};

// 89832 - Death Strike (Save damage taken in last 5 sec)
class spell_dk_death_strike_enabler : public SpellScriptLoader
{
    public:
        spell_dk_death_strike_enabler() : SpellScriptLoader("spell_dk_death_strike_enabler") { }

        class spell_dk_death_strike_enabler_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_death_strike_enabler_AuraScript);

            bool Load() override
            {
                for (uint8 i = 0; i < 5; ++i)
                    _damagePerSecond[i] = 0;
                return true;
            }

            bool CheckProc(ProcEventInfo& eventInfo)
            {
                return eventInfo.GetDamageInfo();
            }

            void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
            {
                if (!GetUnitOwner()->HasAura(SPELL_DK_BLOOD_PRESENCE))
                {
                    for (uint8 i = 0; i < 5; ++i)
                        _damagePerSecond[i] = 0;
                }
                else
                    _damagePerSecond[0] += eventInfo.GetDamageInfo()->GetDamage();
            }

            // Cheap hack to have update calls
            void CalcPeriodic(AuraEffect const* /*aurEff*/, bool& isPeriodic, int32& amplitude)
            {
                isPeriodic = true;
                amplitude = 1000;
            }

            void Update(AuraEffect* /*aurEff*/)
            {
                // Move backwards all datas by one
                for (uint8 i = 4; i > 0; --i)
                    _damagePerSecond[i] = _damagePerSecond[i - 1];
                _damagePerSecond[0] = 0;
            }

            void HandleCalcAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
            {
                canBeRecalculated = true;
                amount = 0;
                for (uint8 i = 0; i < 5; ++i)
                    amount += int32(_damagePerSecond[i]);
            }

            void Register() override
            {
                DoCheckProc += AuraCheckProcFn(spell_dk_death_strike_enabler_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_dk_death_strike_enabler_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
                DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(spell_dk_death_strike_enabler_AuraScript::CalcPeriodic, EFFECT_0, SPELL_AURA_DUMMY);
                OnEffectUpdatePeriodic += AuraEffectUpdatePeriodicFn(spell_dk_death_strike_enabler_AuraScript::Update, EFFECT_0, SPELL_AURA_DUMMY);
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_death_strike_enabler_AuraScript::HandleCalcAmount, EFFECT_0, SPELL_AURA_DUMMY);
            }

            uint32 _damagePerSecond[5];
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_death_strike_enabler_AuraScript();
        }
};

// 47496 - Explode, Ghoul spell for Corpse Explosion
class spell_dk_ghoul_explode : public SpellScriptLoader
{
    public:
        spell_dk_ghoul_explode() : SpellScriptLoader("spell_dk_ghoul_explode") { }

        class spell_dk_ghoul_explode_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_ghoul_explode_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_CORPSE_EXPLOSION_TRIGGERED))
                    return false;
                return true;
            }

            void Suicide(SpellEffIndex /*effIndex*/)
            {
                if (Unit* unitTarget = GetHitUnit())
                {
                    // Corpse Explosion (Suicide)
                    unitTarget->CastSpell(unitTarget, SPELL_DK_CORPSE_EXPLOSION_TRIGGERED, true);
                }
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_dk_ghoul_explode_SpellScript::Suicide, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_ghoul_explode_SpellScript();
        }
};

// 48792 - Icebound Fortitude
class spell_dk_icebound_fortitude : public SpellScriptLoader
{
    public:
        spell_dk_icebound_fortitude() : SpellScriptLoader("spell_dk_icebound_fortitude") { }

        class spell_dk_icebound_fortitude_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_icebound_fortitude_AuraScript);

            bool Load() override
            {
                Unit* caster = GetCaster();
                return caster && caster->GetTypeId() == TYPEID_PLAYER;
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
            {
                if (Unit* caster = GetCaster())
                {
                    int32 value = amount;
                    uint32 defValue = uint32(caster->ToPlayer()->GetSkillValue(SKILL_DEFENSE) + caster->ToPlayer()->GetRatingBonusValue(CR_DEFENSE_SKILL));

                    if (defValue > 400)
                        value -= int32((defValue - 400) * 0.15);

                    // Glyph of Icebound Fortitude
                    if (AuraEffect const* aurEff = caster->GetAuraEffect(SPELL_DK_GLYPH_OF_ICEBOUND_FORTITUDE, EFFECT_0))
                    {
                        int32 valMax = -aurEff->GetAmount();
                        if (value > valMax)
                            value = valMax;
                    }
                    amount = value;
                }
            }

            void Register() override
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_icebound_fortitude_AuraScript::CalculateAmount, EFFECT_2, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_icebound_fortitude_AuraScript();
        }
};

// -50365 - Improved Blood Presence
class spell_dk_improved_blood_presence : public SpellScriptLoader
{
    public:
        spell_dk_improved_blood_presence() : SpellScriptLoader("spell_dk_improved_blood_presence") { }

        class spell_dk_improved_blood_presence_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_improved_blood_presence_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_BLOOD_PRESENCE)
                    || !sSpellMgr->GetSpellInfo(SPELL_DK_FROST_PRESENCE)
                    || !sSpellMgr->GetSpellInfo(SPELL_DK_UNHOLY_PRESENCE)
                    || !sSpellMgr->GetSpellInfo(SPELL_DK_BLOOD_PRESENCE_TRIGGERED))
                    return false;
                return true;
            }

            void HandleModDamagePctTaken(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                Unit* target = GetTarget();
                if ((target->HasAura(SPELL_DK_FROST_PRESENCE) || target->HasAura(SPELL_DK_UNHOLY_PRESENCE)) && !target->HasAura(SPELL_DK_BLOOD_PRESENCE_TRIGGERED))
                    target->CastCustomSpell(SPELL_DK_BLOOD_PRESENCE_TRIGGERED, SPELLVALUE_BASE_POINT0, -aurEff->GetAmount(), target, true, NULL, aurEff);
            }

            void HandleModAttackerMeleeCritChance(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                Unit* target = GetTarget();
                if (target->HasAura(SPELL_DK_BLOOD_PRESENCE))
                    if (AuraEffect* triggeredEff = target->GetAuraEffect(SPELL_DK_BLOOD_PRESENCE_TRIGGERED, EFFECT_1))
                        triggeredEff->SetAmount(aurEff->GetAmount());
            }

            void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                Unit* target = GetTarget();

                if (target->HasAura(SPELL_DK_BLOOD_PRESENCE))
                {
                    if (AuraEffect* triggeredEff = target->GetAuraEffect(SPELL_DK_BLOOD_PRESENCE_TRIGGERED, EFFECT_1))
                        triggeredEff->SetAmount(0);
                }
                else
                    target->RemoveAura(SPELL_DK_BLOOD_PRESENCE_TRIGGERED);
            }

            void Register() override
            {
                AfterEffectApply += AuraEffectApplyFn(spell_dk_improved_blood_presence_AuraScript::HandleModDamagePctTaken, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                AfterEffectApply += AuraEffectApplyFn(spell_dk_improved_blood_presence_AuraScript::HandleModAttackerMeleeCritChance, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                AfterEffectRemove += AuraEffectRemoveFn(spell_dk_improved_blood_presence_AuraScript::HandleEffectRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_improved_blood_presence_AuraScript();
        }
};

// -50384 - Improved Frost Presence
class spell_dk_improved_frost_presence : public SpellScriptLoader
{
    public:
        spell_dk_improved_frost_presence() : SpellScriptLoader("spell_dk_improved_frost_presence") { }

        class spell_dk_improved_frost_presence_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_improved_frost_presence_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_BLOOD_PRESENCE)
                    || !sSpellMgr->GetSpellInfo(SPELL_DK_UNHOLY_PRESENCE)
                    || !sSpellMgr->GetSpellInfo(SPELL_DK_IMPROVED_FROST_PRESENCE_TRIGGERED))
                    return false;
                return true;
            }

            void HandleEffectApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                Unit* target = GetTarget();
                if ((target->HasAura(SPELL_DK_BLOOD_PRESENCE) || target->HasAura(SPELL_DK_UNHOLY_PRESENCE)) && !target->HasAura(SPELL_DK_IMPROVED_FROST_PRESENCE_TRIGGERED))
                    target->CastCustomSpell(SPELL_DK_IMPROVED_FROST_PRESENCE_TRIGGERED, SPELLVALUE_BASE_POINT0, aurEff->GetAmount(), target, true, NULL, aurEff);
            }

            void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                GetTarget()->RemoveAura(SPELL_DK_IMPROVED_FROST_PRESENCE_TRIGGERED);
            }

            void Register() override
            {
                AfterEffectApply += AuraEffectApplyFn(spell_dk_improved_frost_presence_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                AfterEffectRemove += AuraEffectRemoveFn(spell_dk_improved_frost_presence_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_improved_frost_presence_AuraScript();
        }
};

// -50391 - Improved Unholy Presence
class spell_dk_improved_unholy_presence : public SpellScriptLoader
{
    public:
        spell_dk_improved_unholy_presence() : SpellScriptLoader("spell_dk_improved_unholy_presence") { }

        class spell_dk_improved_unholy_presence_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_improved_unholy_presence_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_BLOOD_PRESENCE)
                    || !sSpellMgr->GetSpellInfo(SPELL_DK_FROST_PRESENCE)
                    || !sSpellMgr->GetSpellInfo(SPELL_DK_IMPROVED_UNHOLY_PRESENCE_TRIGGERED))
                    return false;
                return true;
            }

            void HandleEffectApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                Unit* target = GetTarget();
                if ((target->HasAura(SPELL_DK_BLOOD_PRESENCE) || target->HasAura(SPELL_DK_FROST_PRESENCE)) && !target->HasAura(SPELL_DK_IMPROVED_UNHOLY_PRESENCE_TRIGGERED))
                    target->CastCustomSpell(SPELL_DK_IMPROVED_UNHOLY_PRESENCE_TRIGGERED, SPELLVALUE_BASE_POINT0, aurEff->GetAmount(), target, true, NULL, aurEff);
            }

            void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                GetTarget()->RemoveAura(SPELL_DK_IMPROVED_UNHOLY_PRESENCE_TRIGGERED);
            }

            void Register() override
            {
                AfterEffectApply += AuraEffectApplyFn(spell_dk_improved_unholy_presence_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                AfterEffectRemove += AuraEffectRemoveFn(spell_dk_improved_unholy_presence_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_improved_unholy_presence_AuraScript();
        }
};

// 73975 - Necrotic Strike
class spell_dk_necrotic_strike : public SpellScriptLoader
{
    public:
        spell_dk_necrotic_strike() : SpellScriptLoader("spell_dk_necrotic_strike") { }

        class spell_dk_necrotic_strike_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_necrotic_strike_AuraScript);

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool & /*canBeRecalculated*/)
            {
                if (Unit* caster = GetCaster())
                    amount = int32(caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.7f);
            }

            void Register() override
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_necrotic_strike_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_HEAL_ABSORB);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_necrotic_strike_AuraScript();
        }
};

// 48263 - Blood Presence
// 48265 - Unholy Presence
// 48266 - Frost Presence
class spell_dk_presence : public SpellScriptLoader
{
    public:
        spell_dk_presence() : SpellScriptLoader("spell_dk_presence") { }

        class spell_dk_presence_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_presence_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_BLOOD_PRESENCE)
                    || !sSpellMgr->GetSpellInfo(SPELL_DK_FROST_PRESENCE)
                    || !sSpellMgr->GetSpellInfo(SPELL_DK_UNHOLY_PRESENCE)
                    || !sSpellMgr->GetSpellInfo(SPELL_DK_IMPROVED_BLOOD_PRESENCE_R1)
                    || !sSpellMgr->GetSpellInfo(SPELL_DK_IMPROVED_FROST_PRESENCE_R1)
                    || !sSpellMgr->GetSpellInfo(SPELL_DK_IMPROVED_UNHOLY_PRESENCE_R1)
                    || !sSpellMgr->GetSpellInfo(SPELL_DK_BLOOD_PRESENCE_TRIGGERED)
                    || !sSpellMgr->GetSpellInfo(SPELL_DK_IMPROVED_UNHOLY_PRESENCE_TRIGGERED)
                    || !sSpellMgr->GetSpellInfo(SPELL_DK_IMPROVED_FROST_PRESENCE_TRIGGERED))
                    return false;

                return true;
            }

            void HandleImprovedBloodPresence(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                /// @todo: rune regg (effect 2)
                Unit* target = GetTarget();
                if (Aura const* aura = target->GetAuraOfRankedSpell(SPELL_DK_IMPROVED_BLOOD_PRESENCE_R1))
                {
                    CustomSpellValues val;
                    if (GetSpellInfo()->Id == SPELL_DK_BLOOD_PRESENCE)
                    {
                        if (AuraEffect const* impAurEff = aura->GetEffect(EFFECT_1))
                            val.AddSpellMod(SPELLVALUE_BASE_POINT1, impAurEff->GetAmount());
                    }
                    else
                    {
                        if (AuraEffect const* impAurEff = aura->GetEffect(EFFECT_0))
                            val.AddSpellMod(SPELLVALUE_BASE_POINT0, -impAurEff->GetAmount());
                    }

                    if (!target->HasAura(SPELL_DK_BLOOD_PRESENCE_TRIGGERED))
                        target->CastCustomSpell(SPELL_DK_BLOOD_PRESENCE_TRIGGERED, val, target, TRIGGERED_FULL_MASK, NULL, aurEff);
                }
                else if (GetSpellInfo()->Id == SPELL_DK_BLOOD_PRESENCE)
                    target->CastSpell(target, SPELL_DK_BLOOD_PRESENCE_TRIGGERED, true, NULL, aurEff);
            }

            void HandleImprovedFrostPresence(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (GetSpellInfo()->Id != SPELL_DK_BLOOD_PRESENCE && GetSpellInfo()->Id != SPELL_DK_UNHOLY_PRESENCE)
                    return;

                Unit* target = GetTarget();
                if (AuraEffect const* impAurEff = target->GetAuraEffectOfRankedSpell(SPELL_DK_IMPROVED_FROST_PRESENCE_R1, EFFECT_0))
                    if (!target->HasAura(SPELL_DK_IMPROVED_FROST_PRESENCE_TRIGGERED))
                        target->CastCustomSpell(SPELL_DK_IMPROVED_FROST_PRESENCE_TRIGGERED, SPELLVALUE_BASE_POINT0, impAurEff->GetAmount(), target, true, NULL, aurEff);
            }

            void HandleImprovedUnholyPresence(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (GetSpellInfo()->Id != SPELL_DK_BLOOD_PRESENCE && GetSpellInfo()->Id != SPELL_DK_FROST_PRESENCE)
                    return;

                Unit* target = GetTarget();
                if (AuraEffect const* impAurEff = target->GetAuraEffectOfRankedSpell(SPELL_DK_IMPROVED_UNHOLY_PRESENCE_R1, EFFECT_0))
                    if (!target->HasAura(SPELL_DK_IMPROVED_UNHOLY_PRESENCE_TRIGGERED))
                        target->CastCustomSpell(SPELL_DK_IMPROVED_UNHOLY_PRESENCE_TRIGGERED, SPELLVALUE_BASE_POINT0, impAurEff->GetAmount(), target, true, NULL, aurEff);
            }

            void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                Unit* target = GetTarget();
                target->RemoveAura(SPELL_DK_BLOOD_PRESENCE_TRIGGERED);
                target->RemoveAura(SPELL_DK_IMPROVED_FROST_PRESENCE_TRIGGERED);
                target->RemoveAura(SPELL_DK_IMPROVED_UNHOLY_PRESENCE_TRIGGERED);
            }

            void Register() override
            {
                AfterEffectApply += AuraEffectApplyFn(spell_dk_presence_AuraScript::HandleImprovedBloodPresence, EFFECT_0, SPELL_AURA_ANY, AURA_EFFECT_HANDLE_REAL);
                AfterEffectApply += AuraEffectApplyFn(spell_dk_presence_AuraScript::HandleImprovedFrostPresence, EFFECT_0, SPELL_AURA_ANY, AURA_EFFECT_HANDLE_REAL);
                AfterEffectApply += AuraEffectApplyFn(spell_dk_presence_AuraScript::HandleImprovedUnholyPresence, EFFECT_0, SPELL_AURA_ANY, AURA_EFFECT_HANDLE_REAL);
                AfterEffectRemove += AuraEffectRemoveFn(spell_dk_presence_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_ANY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_presence_AuraScript();
        }
};

class RaiseDeadCheck
{
public:
    explicit RaiseDeadCheck(Player const* caster) : _caster(caster) { }

    bool operator()(WorldObject* obj) const
    {
        if (Unit* target = obj->ToUnit())
        {
            if (!target->IsAlive()
                && _caster->isHonorOrXPTarget(target)
                && target->GetCreatureType() == CREATURE_TYPE_HUMANOID
                && target->GetDisplayId() == target->GetNativeDisplayId())
                return false;
        }

        return true;
    }

private:
    Player const* _caster;
};


// 46584 - Raise Dead
class spell_dk_raise_dead : public SpellScriptLoader
{
    public:
        spell_dk_raise_dead() : SpellScriptLoader("spell_dk_raise_dead") { }

        class spell_dk_raise_dead_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_raise_dead_SpellScript);

            bool Validate(SpellInfo const* spellInfo) override
            {
                if (!sSpellMgr->GetSpellInfo(spellInfo->Effects[EFFECT_0].CalcValue())
                    || !sSpellMgr->GetSpellInfo(spellInfo->Effects[EFFECT_1].CalcValue())
                    || !sSpellMgr->GetSpellInfo(SPELL_DK_RAISE_DEAD_USE_REAGENT)
                    || !sSpellMgr->GetSpellInfo(SPELL_DK_MASTER_OF_GHOULS))
                    return false;
                return true;
            }

            bool Load() override
            {
                _result = SPELL_CAST_OK;
                _corpse = false;
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            SpellCastResult CheckCast()
            {
                /// process spell target selection before cast starts
                /// targets of effect_1 are used to check cast
                GetSpell()->SelectSpellTargets();
                /// cleanup spell target map, and fill it again on normal way
                GetSpell()->CleanupTargetList();
                /// _result is set in spell target selection
                return _result;
            }

            SpellCastResult CheckReagents()
            {
                /// @workaround: there is no access to castresult of other spells, check it manually
                SpellInfo const* reagentSpell = sSpellMgr->GetSpellInfo(SPELL_DK_RAISE_DEAD_USE_REAGENT);
                Player* player = GetCaster()->ToPlayer();
                if (!player->CanNoReagentCast(reagentSpell))
                {
                    for (uint32 i = 0; i < MAX_SPELL_REAGENTS; i++)
                    {
                        if (reagentSpell->Reagent[i] <= 0)
                            continue;

                        if (!player->HasItemCount(reagentSpell->Reagent[i], reagentSpell->ReagentCount[i]))
                        {
                            Spell::SendCastResult(player, reagentSpell, 0, SPELL_FAILED_REAGENTS);
                            return SPELL_FAILED_DONT_REPORT;
                        }
                    }
                }
                return SPELL_CAST_OK;
            }

            void CheckTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if(RaiseDeadCheck(GetCaster()->ToPlayer()));

                if (targets.empty())
                {
                    if (GetSpell()->getState() == SPELL_STATE_PREPARING)
                        _result = CheckReagents();

                    return;
                }

                WorldObject* target = Trinity::Containers::SelectRandomContainerElement(targets);
                targets.clear();
                targets.push_back(target);
                _corpse = true;
            }

            void CheckTarget(WorldObject*& target)
            {
                // Don't add caster to target map, if we found a corpse to raise dead
                if (_corpse)
                    target = nullptr;
            }

            void ConsumeReagents()
            {
                // No corpse found, take reagents
                if (!_corpse)
                    GetCaster()->CastSpell(GetCaster(), SPELL_DK_RAISE_DEAD_USE_REAGENT, TriggerCastFlags(TRIGGERED_FULL_MASK & ~TRIGGERED_IGNORE_POWER_AND_REAGENT_COST));
            }

            uint32 GetGhoulSpellId()
            {
                // Do we have talent Master of Ghouls?
                if (GetCaster()->HasAura(SPELL_DK_MASTER_OF_GHOULS))
                    // summon as pet
                    return GetSpellInfo()->Effects[EFFECT_1].CalcValue();

                // or guardian
                return GetSpellInfo()->Effects[EFFECT_0].CalcValue();
            }

            void HandleRaiseDead(SpellEffIndex /*effIndex*/)
            {
                SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(GetGhoulSpellId());
                SpellCastTargets targets;
                targets.SetDst(*GetHitUnit());

                GetCaster()->CastSpell(targets, spellInfo, NULL, TRIGGERED_FULL_MASK);
            }

            void Register() override
            {
                OnCheckCast += SpellCheckCastFn(spell_dk_raise_dead_SpellScript::CheckCast);
                OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_dk_raise_dead_SpellScript::CheckTarget, EFFECT_1, TARGET_UNIT_CASTER);
                OnCast += SpellCastFn(spell_dk_raise_dead_SpellScript::ConsumeReagents);
                OnEffectHitTarget += SpellEffectFn(spell_dk_raise_dead_SpellScript::HandleRaiseDead, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnEffectHitTarget += SpellEffectFn(spell_dk_raise_dead_SpellScript::HandleRaiseDead, EFFECT_1, SPELL_EFFECT_DUMMY);
            }

        private:
            SpellCastResult _result;
            bool _corpse;
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_raise_dead_SpellScript();
        }
};

// 59754 Rune Tap - Party
class spell_dk_rune_tap_party : public SpellScriptLoader
{
    public:
        spell_dk_rune_tap_party() : SpellScriptLoader("spell_dk_rune_tap_party") { }

        class spell_dk_rune_tap_party_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_rune_tap_party_SpellScript);

            void CheckTargets(std::list<WorldObject*>& targets)
            {
                targets.remove(GetCaster());
            }

            void Register() override
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dk_rune_tap_party_SpellScript::CheckTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_PARTY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_rune_tap_party_SpellScript();
        }
};

// 50421 - Scent of Blood
class spell_dk_scent_of_blood : public SpellScriptLoader
{
    public:
        spell_dk_scent_of_blood() : SpellScriptLoader("spell_dk_scent_of_blood") { }

        class spell_dk_scent_of_blood_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_scent_of_blood_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_SCENT_OF_BLOOD))
                    return false;
                return true;
            }

            void OnProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
            {
                PreventDefaultAction();
                GetTarget()->CastSpell(GetTarget(), SPELL_DK_SCENT_OF_BLOOD, true, NULL, aurEff);
                GetTarget()->RemoveAuraFromStack(GetId());
            }

            void Register() override
            {
                OnEffectProc += AuraEffectProcFn(spell_dk_scent_of_blood_AuraScript::OnProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_scent_of_blood_AuraScript();
        }
};

// 55090 - Scourge Strike (55265, 55270, 55271)
class spell_dk_scourge_strike : public SpellScriptLoader
{
    public:
        spell_dk_scourge_strike() : SpellScriptLoader("spell_dk_scourge_strike") { }

        class spell_dk_scourge_strike_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dk_scourge_strike_SpellScript);
            float multiplier;

            bool Load() override
            {
                multiplier = 1.0f;
                return true;
            }

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_SCOURGE_STRIKE_TRIGGERED))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                if (Unit* unitTarget = GetHitUnit())
                {
                    multiplier = (GetEffectValue() * unitTarget->GetDiseasesByCaster(caster->GetGUID()) / 100.f);
                    // Death Knight T8 Melee 4P Bonus
                    if (AuraEffect const* aurEff = caster->GetAuraEffect(SPELL_DK_ITEM_T8_MELEE_4P_BONUS, EFFECT_0))
                        AddPct(multiplier, aurEff->GetAmount());
                }
            }

            void HandleAfterHit()
            {
                Unit* caster = GetCaster();
                if (Unit* unitTarget = GetHitUnit())
                {
                    int32 bp = GetHitDamage() * multiplier;

                    if (AuraEffect* aurEff = caster->GetAuraEffectOfRankedSpell(SPELL_DK_BLACK_ICE_R1, EFFECT_0))
                        AddPct(bp, aurEff->GetAmount());

                    caster->CastCustomSpell(unitTarget, SPELL_DK_SCOURGE_STRIKE_TRIGGERED, &bp, NULL, NULL, true);
                }
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_dk_scourge_strike_SpellScript::HandleDummy, EFFECT_2, SPELL_EFFECT_DUMMY);
                AfterHit += SpellHitFn(spell_dk_scourge_strike_SpellScript::HandleAfterHit);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_dk_scourge_strike_SpellScript();
        }
};

// 55233 - Vampiric Blood
class spell_dk_vampiric_blood : public SpellScriptLoader
{
    public:
        spell_dk_vampiric_blood() : SpellScriptLoader("spell_dk_vampiric_blood") { }

        class spell_dk_vampiric_blood_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_vampiric_blood_AuraScript);

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
            {
                amount = GetUnitOwner()->CountPctFromMaxHealth(amount);
            }

            void Register() override
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_vampiric_blood_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_MOD_INCREASE_HEALTH);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_vampiric_blood_AuraScript();
        }
};

// -52284 - Will of the Necropolis
class spell_dk_will_of_the_necropolis : public SpellScriptLoader
{
    public:
        spell_dk_will_of_the_necropolis() : SpellScriptLoader("spell_dk_will_of_the_necropolis") { }

        class spell_dk_will_of_the_necropolis_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dk_will_of_the_necropolis_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DK_WILL_OF_THE_NECROPOLIS))
                    return false;
                return true;
            }

            bool CheckProc(ProcEventInfo& eventInfo)
            {
                //! HACK due to currenct proc system implementation
                if (Player* player = GetTarget()->ToPlayer())
                    if (player->HasSpellCooldown(GetId()))
                        return false;

               return GetTarget()->HealthBelowPctDamaged(30, eventInfo.GetDamageInfo()->GetDamage());
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
            {
                GetTarget()->CastSpell(GetTarget(), SPELL_DK_WILL_OF_THE_NECROPOLIS, true, NULL, aurEff);

                if (Player* player = GetTarget()->ToPlayer())
                {
                    player->RemoveSpellCooldown(SPELL_DK_RUNE_TAP, true);
                    player->AddSpellCooldown(GetId(), 0, time(NULL) + 45);
                }
            }

            void Register() override
            {
                DoCheckProc += AuraCheckProcFn(spell_dk_will_of_the_necropolis_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_dk_will_of_the_necropolis_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL_WITH_VALUE);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_dk_will_of_the_necropolis_AuraScript();
        }
};

// new #############################################

// 62137
class spell_dk_avoidance_passive : public SpellScriptLoader
{
public:
    spell_dk_avoidance_passive() : SpellScriptLoader("spell_dk_avoidance_passive") { }

    class spell_dk_avoidance_passive_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dk_avoidance_passive_AuraScript);

        bool Load()
        {
            if (!GetCaster() || !GetCaster()->GetOwner() || GetCaster()->GetOwner()->GetTypeId() != TYPEID_PLAYER)
                return false;
            return true;
        }

        void CalculateAvoidanceAmount(AuraEffect const* /* aurEff */, int32& amount, bool& /*canBeRecalculated*/)
        {
            if (Unit* pet = GetUnitOwner())
            {
                if (Unit* owner = pet->GetOwner())
                {
                    // Army of the dead ghoul
                    if (pet->GetEntry() == ENTRY_ARMY_OF_THE_DEAD_GHOUL)
                        amount = -90;
                    // Night of the dead
                    else if (Aura* aur = owner->GetAuraOfRankedSpell(SPELL_NIGHT_OF_THE_DEAD))
                        amount = aur->GetSpellInfo()->Effects[EFFECT_2].CalcValue();
                }
            }
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_avoidance_passive_AuraScript::CalculateAvoidanceAmount, EFFECT_0, SPELL_AURA_MOD_CREATURE_AOE_DAMAGE_AVOIDANCE);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_dk_avoidance_passive_AuraScript();
    }
};

// 54566
class spell_dk_pet_scaling_01 : public SpellScriptLoader
{
public:
    spell_dk_pet_scaling_01() : SpellScriptLoader("spell_dk_pet_scaling_01") { }

    class spell_dk_pet_scaling_01_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dk_pet_scaling_01_AuraScript);

        bool Load()
        {
            if (!GetCaster() || !GetCaster()->GetOwner() || GetCaster()->GetOwner()->GetTypeId() != TYPEID_PLAYER)
                return false;
            _tempHealth = 0;
            return true;
        }

        void CalculateStaminaAmount(AuraEffect const* /* aurEff */, int32& amount, bool& /*canBeRecalculated*/)
        {
            if (Unit* pet = GetUnitOwner())
            {
                if (pet->IsGuardian())
                {
                    if (Unit* owner = pet->GetOwner())
                    {
                        float mod = 1.0f;
                        // Glyph of Raise dead
                        if (AuraEffect const* aurEff = owner->GetAuraEffect(58686, 0))
                            AddPct(mod, aurEff->GetAmount());

                        float ownerBonus = float(owner->GetStat(STAT_STAMINA)) * mod;
                        amount += ownerBonus;
                    }
                }
            }
        }

        void ApplyEffect(AuraEffect const* /* aurEff */, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* pet = GetUnitOwner())
                if (_tempHealth)
                    pet->SetHealth(_tempHealth);
        }

        void RemoveEffect(AuraEffect const* /* aurEff */, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* pet = GetUnitOwner())
                _tempHealth = pet->GetHealth();
        }

        void CalculateStrengthAmount(AuraEffect const* /* aurEff */, int32& amount, bool& /*canBeRecalculated*/)
        {
            if (Unit* pet = GetUnitOwner())
            {
                if (!pet->IsGuardian())
                    return;

                Unit* owner = pet->GetOwner();
                if (!owner)
                    return;

                float mod = 1.0f;
                // Glyph of raise dead
                if (AuraEffect const* aurEff = owner->GetAuraEffect(58686, 0))
                    AddPct(mod, aurEff->GetAmount());

                float ownerBonus = float(owner->GetStat(STAT_STRENGTH)) * mod;
                amount += ownerBonus;
            }
        }

        void Register()
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_dk_pet_scaling_01_AuraScript::RemoveEffect, EFFECT_0, SPELL_AURA_MOD_STAT, AURA_EFFECT_HANDLE_CHANGE_AMOUNT_MASK);
            AfterEffectApply += AuraEffectApplyFn(spell_dk_pet_scaling_01_AuraScript::ApplyEffect, EFFECT_0, SPELL_AURA_MOD_STAT, AURA_EFFECT_HANDLE_CHANGE_AMOUNT_MASK);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_pet_scaling_01_AuraScript::CalculateStaminaAmount, EFFECT_0, SPELL_AURA_MOD_STAT);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_pet_scaling_01_AuraScript::CalculateStrengthAmount, EFFECT_1, SPELL_AURA_MOD_STAT);
        }

    private:
        uint32 _tempHealth;
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_dk_pet_scaling_01_AuraScript();
    }
};

// 51996
class spell_dk_pet_scaling_02 : public SpellScriptLoader
{
public:
    spell_dk_pet_scaling_02() : SpellScriptLoader("spell_dk_pet_scaling_02") { }

    class spell_dk_pet_scaling_02_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dk_pet_scaling_02_AuraScript);

        bool Load()
        {
            if (!GetCaster() || !GetCaster()->GetOwner() || GetCaster()->GetOwner()->GetTypeId() != TYPEID_PLAYER)
                return false;
            return true;
        }

        void CalculateAmountMeleeHaste(AuraEffect const* /* aurEff */, int32& amount, bool& /*canBeRecalculated*/)
        {
            if (!GetCaster() || !GetCaster()->GetOwner())
                return;
            if (Player* owner = GetCaster()->GetOwner()->ToPlayer())
            {
                // For others recalculate it from:
                float HasteMelee = 0.0f;
                HasteMelee += (1 - owner->m_modAttackSpeedPct[BASE_ATTACK]) * 100;
                amount += int32(HasteMelee);
            }
        }

        void CalculateBonusDamagePct(AuraEffect const* /* aurEff */, int32& amount, bool& /*canBeRecalculated*/)
        {
            if (!GetCaster() || !GetCaster()->GetOwner())
                return;

            if (Player* owner = GetCaster()->GetOwner()->ToPlayer())
            {
                Unit::AuraEffectList const& auraDamagePctList = owner->GetAuraEffectsByType(SPELL_AURA_MOD_DAMAGE_PERCENT_DONE);
                for (Unit::AuraEffectList::const_iterator itr = auraDamagePctList.begin(); itr != auraDamagePctList.end(); ++itr)
                    if ((*itr)->GetMiscValue() & SPELL_SCHOOL_MASK_NORMAL)
                        amount += (*itr)->GetAmount();
            }
        }


        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_pet_scaling_02_AuraScript::CalculateBonusDamagePct, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_pet_scaling_02_AuraScript::CalculateAmountMeleeHaste, EFFECT_1, SPELL_AURA_MELEE_SLOW);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_dk_pet_scaling_02_AuraScript();
    }
};

// 61697
class spell_dk_pet_scaling_03 : public SpellScriptLoader
{
public:
    spell_dk_pet_scaling_03() : SpellScriptLoader("spell_dk_pet_scaling_03") { }

    class spell_dk_pet_scaling_03_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dk_pet_scaling_03_AuraScript);

        bool Load()
        {
            if (!GetCaster() || !GetCaster()->GetOwner() || GetCaster()->GetOwner()->GetTypeId() != TYPEID_PLAYER)
                return false;
            return true;
        }

        void CalculateAmountMeleeHit(AuraEffect const* /* aurEff */, int32& amount, bool& /*canBeRecalculated*/)
        {
            if (!GetCaster() || !GetCaster()->GetOwner())
                return;
            if (Player* owner = GetCaster()->GetOwner()->ToPlayer())
            {
                // For others recalculate it from:
                float HitMelee = 0.0f;
                // Increase hit from SPELL_AURA_MOD_HIT_CHANCE
                HitMelee += owner->GetTotalAuraModifier(SPELL_AURA_MOD_HIT_CHANCE);
                // Increase hit melee from meele hit ratings
                HitMelee += owner->GetRatingBonusValue(CR_HIT_MELEE);

                amount += int32(HitMelee);
            }
        }

        void CalculateAmountSpellHit(AuraEffect const* /* aurEff */, int32& amount, bool& /*canBeRecalculated*/)
        {
            if (!GetCaster() || !GetCaster()->GetOwner())
                return;
            if (Player* owner = GetCaster()->GetOwner()->ToPlayer())
            {
                // For others recalculate it from:
                float HitSpell = 0.0f;
                // Increase hit from SPELL_AURA_MOD_SPELL_HIT_CHANCE
                HitSpell += owner->GetTotalAuraModifier(SPELL_AURA_MOD_SPELL_HIT_CHANCE);
                // Increase hit spell from spell hit ratings
                HitSpell += owner->GetRatingBonusValue(CR_HIT_SPELL);

                amount += int32(HitSpell);
            }
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_pet_scaling_03_AuraScript::CalculateAmountMeleeHit, EFFECT_0, SPELL_AURA_MOD_HIT_CHANCE);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_pet_scaling_03_AuraScript::CalculateAmountSpellHit, EFFECT_1, SPELL_AURA_MOD_SPELL_HIT_CHANCE);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_dk_pet_scaling_03_AuraScript();
    }
};

// 51906
class spell_dk_rune_weapon_scaling_02 : public SpellScriptLoader
{
public:
    spell_dk_rune_weapon_scaling_02() : SpellScriptLoader("spell_dk_rune_weapon_scaling_02") { }

    class spell_dk_rune_weapon_scaling_02_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dk_rune_weapon_scaling_02_AuraScript);

        bool Load()
        {
            if (!GetCaster() || !GetCaster()->GetOwner() || GetCaster()->GetOwner()->GetTypeId() != TYPEID_PLAYER)
                return false;
            return true;
        }

        void CalculateDamageDoneAmount(AuraEffect const* /* aurEff */, int32& amount, bool& /*canBeRecalculated*/)
        {
            if (Unit* pet = GetUnitOwner())
            {
                Unit* owner = pet->GetOwner();
                if (!owner)
                    return;

                if (pet->IsGuardian())
                    ((Guardian*)pet)->SetBonusDamage(owner->GetTotalAttackPowerValue(BASE_ATTACK));

                amount += owner->CalculateDamage(BASE_ATTACK, true, true);
            }
        }

        void CalculateAmountMeleeHaste(AuraEffect const* /* aurEff */, int32& amount, bool& /*canBeRecalculated*/)
        {
            if (!GetCaster() || !GetCaster()->GetOwner())
                return;
            if (Player* owner = GetCaster()->GetOwner()->ToPlayer())
            {
                // For others recalculate it from:
                float HasteMelee = 0.0f;
                // Increase hit from SPELL_AURA_MOD_HIT_CHANCE
                HasteMelee += (1 - owner->m_modAttackSpeedPct[BASE_ATTACK]) * 100;

                amount += int32(HasteMelee);
            }
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_rune_weapon_scaling_02_AuraScript::CalculateDamageDoneAmount, EFFECT_0, SPELL_AURA_MOD_DAMAGE_DONE);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dk_rune_weapon_scaling_02_AuraScript::CalculateAmountMeleeHaste, EFFECT_1, SPELL_AURA_MELEE_SLOW);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_dk_rune_weapon_scaling_02_AuraScript();
    }
};

// 45524 
class spell_dk_chains_of_ice : public SpellScriptLoader
{
public:
    spell_dk_chains_of_ice() : SpellScriptLoader("spell_dk_chains_of_ice") { }

    class spell_dk_chains_of_ice_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dk_chains_of_ice_SpellScript);

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
                if (Unit* target = GetHitUnit())
                    if (_player->HasAura(SPELL_DK_GLYPH_OF_CHAINS_OF_ICE))
                        _player->CastSpell(target, SPELL_DK_GLYPH_OF_CHAINS_OF_ICE_DAMAGE, true);
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_dk_chains_of_ice_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dk_chains_of_ice_SpellScript();
    }
};

// 50435
class spell_dk_chilblains : public SpellScriptLoader
{
public:
    spell_dk_chilblains() : SpellScriptLoader("spell_dk_chilblains") { }

    class spell_dk_chilblains_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dk_chilblains_SpellScript);

        void OnHitTarget(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (AuraEffect* chilblains = caster->GetAuraEffect(SPELL_AURA_ADD_TARGET_TRIGGER, SPELLFAMILY_DEATHKNIGHT, 143, EFFECT_0))
            {
                uint32 triggeredId = 0;
                switch (chilblains->GetId())
                {
                case 50040:
                    triggeredId = 96293;
                    break;
                case 50041:
                    triggeredId = 96294;
                    break;
                }
                caster->CastSpell(target, triggeredId, true);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_dk_chilblains_SpellScript::OnHitTarget, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dk_chilblains_SpellScript;
    }
};

// 63560
class spell_dk_dark_transformation : public SpellScriptLoader
{
public:
    spell_dk_dark_transformation() : SpellScriptLoader("spell_dk_dark_transformation") { }

    class spell_dk_dark_transformation_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dk_dark_transformation_SpellScript);

        void HandleOnHit()
        {
            GetHitUnit()->RemoveAurasDueToSpell(91342);
            GetCaster()->RemoveAurasDueToSpell(93426);
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_dk_dark_transformation_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dk_dark_transformation_SpellScript();
    }
};

// 96268
class spell_dk_deaths_advance : public SpellScriptLoader
{
public:
    spell_dk_deaths_advance() : SpellScriptLoader("spell_dk_deaths_advance") { }

    class spell_dk_deaths_advance_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dk_deaths_advance_AuraScript);

        void HandleEffectPeriodic(AuraEffect const* /*aurEff*/)
        {
            Player* player = GetCaster()->ToPlayer();
            if (!player)
                return;

            uint8 unholyRunesOnCooldown = 0;
            for (uint32 i = 2; i < 4; ++i)
                if (player->GetRuneCooldown(i))
                    unholyRunesOnCooldown++;
            if (unholyRunesOnCooldown == 2)
                RefreshDuration();
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_dk_deaths_advance_AuraScript::HandleEffectPeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_dk_deaths_advance_AuraScript();
    }
};

// 85948
class spell_dk_festering : public SpellScriptLoader
{
public:
    spell_dk_festering() : SpellScriptLoader("spell_dk_festering") { }

    class spell_dk_festering_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dk_festering_SpellScript);

        void OnHitTarget(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            Aura* aura = nullptr;
            int32 newDuration = GetSpellInfo()->Effects[EFFECT_2].BasePoints * 1000;
            // Increase chains of ice
            if (aura = target->GetAura(45524, caster->GetGUID()))
                aura->SetDuration(std::min(newDuration + aura->GetDuration(), aura->GetMaxDuration()), true);
            // Increase Blood plague
            if (aura = target->GetAura(55078, caster->GetGUID()))
                aura->SetDuration(std::min(newDuration + aura->GetDuration(), aura->GetMaxDuration()), true);
            // Increase frost fever
            if (aura = target->GetAura(55095, caster->GetGUID()))
                aura->SetDuration(std::min(newDuration + aura->GetDuration(), aura->GetMaxDuration()), true);
            // Increase Ebon Plague
            if (aura = target->GetAura(65142, caster->GetGUID()))
                aura->SetDuration(std::min(newDuration + aura->GetDuration(), aura->GetMaxDuration()), true);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_dk_festering_SpellScript::OnHitTarget, EFFECT_2, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dk_festering_SpellScript;
    }
};

// 49024 49538
class spell_dk_merciless_combat : public SpellScriptLoader
{
public:
    spell_dk_merciless_combat() : SpellScriptLoader("spell_dk_merciless_combat") { }

    class spell_dk_merciless_combat_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dk_merciless_combat_SpellScript);

        void HandleOnHit()
        {
            if (Player* caster = GetCaster()->ToPlayer())
            {
                if (GetHitUnit()->GetHealthPct() <= 35.0f)
                {
                    int32 damage = GetHitDamage();
                    if (caster->HasTalent(SPELL_DK_MERCILESS_COMBAT_RANK_1, caster->GetActiveSpec()))
                    {
                        SetHitDamage(uint32(damage * 1.06f));
                    }
                    else if (caster->HasTalent(SPELL_DK_MERCILESS_COMBAT_RANK_2, caster->GetActiveSpec()))
                    {
                        SetHitDamage(uint32(damage * 1.12f));
                    }
                }
            }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_dk_merciless_combat_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dk_merciless_combat_SpellScript();
    }
};

// 50842
class spell_dk_pestilence : public SpellScriptLoader
{
public:
    spell_dk_pestilence() : SpellScriptLoader("spell_dk_pestilence") { }

    class script_impl : public SpellScript
    {
        PrepareSpellScript(script_impl);

        enum
        {
            SPELL_DOT_REDUCTION = 76243,
            SPELL_GLYPH_OF_PESTILENCE = 63334,
            SPELL_PESTILENCE_ANIMATION = 91939,
            SPELL_BLOOD_PLAGUE = 55078,
            SPELL_FROST_FEVER = 55095,
        };

        Unit* m_explTarget;

        bool Load()
        {
            m_explTarget = GetExplTargetUnit();
            return m_explTarget;
        }

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            targets.remove(m_explTarget);
        }

        void HandleScript(SpellEffIndex)
        {
            Unit* const caster = GetCaster();
            Unit* const target = GetHitUnit();
            if (!target)
                return;

            caster->CastSpell(caster, SPELL_DOT_REDUCTION, true);

            // Blood Plague
            if (m_explTarget->HasAura(SPELL_BLOOD_PLAGUE, caster->GetGUID()))
                caster->CastSpell(target, SPELL_BLOOD_PLAGUE, true);

            // Frost Fever
            if (m_explTarget->HasAura(SPELL_FROST_FEVER, caster->GetGUID()))
                caster->CastSpell(target, SPELL_FROST_FEVER, true);

            caster->CastSpell(target, SPELL_PESTILENCE_ANIMATION, true);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(script_impl::FilterTargets, EFFECT_2, TARGET_UNIT_DEST_AREA_ENEMY);
            OnEffectHitTarget += SpellEffectFn(script_impl::HandleScript, EFFECT_2, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

   SpellScript* GetSpellScript() const
    {
        return new script_impl();
    }
};

// 47468 47481 47482 47484
class spell_dk_pet_spells : public SpellScriptLoader
{
public:
    spell_dk_pet_spells() : SpellScriptLoader("spell_dk_pet_spells") { }

    class spell_dk_pet_spells_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dk_pet_spells_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            bool darkTransformation = GetCaster()->HasAura(63560);
            int32 triggered_spell_id = 0;
            switch (GetSpellInfo()->Id)
            {
            case 47481: // Gnaw
                triggered_spell_id = darkTransformation ? 91797 : 91800;
                break;
            case 47468: // Claw
                triggered_spell_id = darkTransformation ? 91778 : 91776;
                break;
            case 47482: // Leap
                triggered_spell_id = darkTransformation ? 91802 : 91809;
                break;
            case 47484: // Huddle
                triggered_spell_id = darkTransformation ? 91837 : 91838;
                break;
            }
            if (triggered_spell_id)
                GetCaster()->CastSpell(GetHitUnit(), triggered_spell_id, true);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_dk_pet_spells_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dk_pet_spells_SpellScript();
    }
};

// 51271
class spell_dk_pillar_of_frost : public SpellScriptLoader
{
public:
    spell_dk_pillar_of_frost() : SpellScriptLoader("spell_dk_pillar_of_frost") { }

    class spell_dk_pillar_of_frost_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dk_pillar_of_frost_AuraScript);

        void HandleEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* target = GetTarget();
            if (AuraEffect* glyph = target->GetDummyAuraEffect(SPELLFAMILY_DEATHKNIGHT, 4919, EFFECT_0))
                target->CastSpell(target, 90259, true);
        }

        void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            GetTarget()->RemoveAurasDueToSpell(90259);
        }

        void Register()
        {
            AfterEffectApply += AuraEffectApplyFn(spell_dk_pillar_of_frost_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            AfterEffectRemove += AuraEffectRemoveFn(spell_dk_pillar_of_frost_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_dk_pillar_of_frost_AuraScript();
    }
};

// 55078 55095
class spell_dk_resilient_infection : public SpellScriptLoader
{
public:
    spell_dk_resilient_infection() : SpellScriptLoader("spell_dk_resilient_infection") { }

    class spell_dk_resilient_infection_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dk_resilient_infection_AuraScript);

        void HandleDispel(DispelInfo* /*dispelInfo*/)
        {
            if (Unit* caster = GetCaster())
            {
                // Resilient Infection
                if (AuraEffect const* aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_GENERIC, 1910, EFFECT_0))
                    if (roll_chance_i(aurEff->GetAmount()))
                    {
                        int32 bp0 = 0;
                        int32 bp1 = 0;
                        if (GetId() == 55095)
                            bp0 = 1;
                        else
                            bp1 = 1;

                        caster->CastCustomSpell(caster, 90721, &bp0, &bp1, NULL, true);
                    }
            }
        }

        void Register()
        {
            AfterDispel += AuraDispelFn(spell_dk_resilient_infection_AuraScript::HandleDispel);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_dk_resilient_infection_AuraScript();
    }
};

// 47476
class spell_dk_strangulate : public SpellScriptLoader
{
public:
    spell_dk_strangulate() : SpellScriptLoader("spell_dk_strangulate") { }

    class spell_dk_strangulate_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dk_strangulate_SpellScript);

        bool Load()
        {
            wasCasting = false;
            return true;
        }

        void HandleBeforeHit()
        {
            if (GetHitUnit())
                wasCasting = GetHitUnit()->IsNonMeleeSpellCast(false, false, true);
        }

        void OnHitTarget(SpellEffIndex /*effIndex*/)
        {
            if (!wasCasting)
                return;

            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (AuraEffect* glyph = caster->GetDummyAuraEffect(SPELLFAMILY_DEATHKNIGHT, 2027, EFFECT_0))
                if (Aura* strangulate = GetHitAura())
                {
                    strangulate->SetMaxDuration(strangulate->GetDuration() + glyph->GetAmount());
                    strangulate->SetDuration(strangulate->GetDuration() + glyph->GetAmount());
                }
        }

        void Register()
        {
            BeforeHit += SpellHitFn(spell_dk_strangulate_SpellScript::HandleBeforeHit);
            OnEffectHitTarget += SpellEffectFn(spell_dk_strangulate_SpellScript::OnHitTarget, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
        }

        bool wasCasting;
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dk_strangulate_SpellScript;
    }
};

// 49576 - Death Grip Initial
class spell_dk_death_grip_initial : public SpellScriptLoader
{
public:
	spell_dk_death_grip_initial() : SpellScriptLoader("spell_dk_death_grip_initial") { }

	class spell_dk_death_grip_initial_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_dk_death_grip_initial_SpellScript);

		SpellCastResult CheckCast()
		{
			Unit* caster = GetCaster();
			// Death Grip should not be castable while jumping/falling
			if (caster->HasUnitState(UNIT_STATE_JUMPING) || caster->HasUnitMovementFlag(MOVEMENTFLAG_FALLING))
				return SPELL_FAILED_MOVING;

			// Patch 3.3.3 (2010-03-23): Minimum range has been changed to 8 yards in PvP.
			Unit* target = GetExplTargetUnit();
			if (target && target->GetTypeId() == TYPEID_PLAYER)
				if (caster->GetDistance(target) < 8.f)
					return SPELL_FAILED_TOO_CLOSE;

			return SPELL_CAST_OK;
		}

		void HandleDummy(SpellEffIndex /*effIndex*/)
		{
			GetCaster()->CastSpell(GetHitUnit(), SPELL_DK_DEATH_GRIP, true);
		}

		void Register() override
		{
			OnCheckCast += SpellCheckCastFn(spell_dk_death_grip_initial_SpellScript::CheckCast);
			OnEffectHitTarget += SpellEffectFn(spell_dk_death_grip_initial_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
		}
	};

	SpellScript* GetSpellScript() const override
	{
		return new spell_dk_death_grip_initial_SpellScript();
	}
};

// 70656 - Advantage (T10 4P Melee Bonus)
class spell_dk_advantage_t10_4p : public SpellScriptLoader
{
public:
    spell_dk_advantage_t10_4p() : SpellScriptLoader("spell_dk_advantage_t10_4p") { }

    class spell_dk_advantage_t10_4p_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dk_advantage_t10_4p_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (Unit* caster = eventInfo.GetActor())
            {
                Player* player = caster->ToPlayer();
                if (!player || caster->getClass() != CLASS_DEATH_KNIGHT)
                    return false;

                for (uint8 i = 0; i < player->GetMaxPower(POWER_RUNES); ++i)
                    if (player->GetRuneCooldown(i) == 0)
                        return false;

                return true;
            }

            return false;
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_dk_advantage_t10_4p_AuraScript::CheckProc);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dk_advantage_t10_4p_AuraScript();
    }
};

// 49028 - Dancing Rune Weapon
class spell_dk_dancing_rune_weapon : public SpellScriptLoader
{
public:
    spell_dk_dancing_rune_weapon() : SpellScriptLoader("spell_dk_dancing_rune_weapon") { }

    class spell_dk_dancing_rune_weapon_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dk_dancing_rune_weapon_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sObjectMgr->GetCreatureTemplate(NPC_DK_DANCING_RUNE_WEAPON))
                return false;
            return true;
        }

        // This is a port of the old switch hack in Unit.cpp, it's not correct
        void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();
            Unit* caster = GetCaster();
            if (!caster)
                return;

            Unit* drw = nullptr;
            for (Unit* controlled : caster->m_Controlled)
            {
                if (controlled->GetEntry() == NPC_DK_DANCING_RUNE_WEAPON)
                {
                    drw = controlled;
                    break;
                }
            }

            if (!drw || !drw->GetVictim())
                return;

            SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
            if (!spellInfo)
                return;

            DamageInfo* damageInfo = eventInfo.GetDamageInfo();
            if (!damageInfo || !damageInfo->GetDamage())
                return;

            int32 amount = static_cast<int32>(damageInfo->GetDamage()) / 2;
            SpellNonMeleeDamage log(drw, drw->GetVictim(), GetSpellInfo()->Id, GetSpellInfo()->SchoolMask);
            log.damage = amount;
            drw->DealDamage(drw->GetVictim(), amount, nullptr, SPELL_DIRECT_DAMAGE, spellInfo->GetSchoolMask(), spellInfo, true);
            drw->SendSpellNonMeleeDamageLog(&log);
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_dk_dancing_rune_weapon_AuraScript::HandleProc, EFFECT_1, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dk_dancing_rune_weapon_AuraScript();
    }
};

// 61257 - Runic Power Back on Snare/Root
class spell_dk_pvp_4p_bonus : public SpellScriptLoader
{
public:
    spell_dk_pvp_4p_bonus() : SpellScriptLoader("spell_dk_pvp_4p_bonus") { }

    class spell_dk_pvp_4p_bonus_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dk_pvp_4p_bonus_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({ SPELL_DK_RUNIC_RETURN });
        }

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
            if (!spellInfo)
                return false;

            return (spellInfo->GetAllEffectsMechanicMask() & ((1 << MECHANIC_ROOT) | (1 << MECHANIC_SNARE))) != 0;
        }

        void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();
            eventInfo.GetActionTarget()->CastSpell((Unit*)nullptr, SPELL_DK_RUNIC_RETURN, true);
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_dk_pvp_4p_bonus_AuraScript::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_dk_pvp_4p_bonus_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dk_pvp_4p_bonus_AuraScript();
    }
};

void AddSC_deathknight_spell_scripts()
{
    new spell_dk_anti_magic_shell_raid();
    new spell_dk_anti_magic_shell_self();
    new spell_dk_anti_magic_zone();
    new spell_dk_avoidance_passive();
    new spell_dk_blood_boil();
    new spell_dk_blood_gorged();
    new spell_dk_butchery();
    new spell_dk_chains_of_ice();
    new spell_dk_chilblains();
    new spell_dk_dark_transformation();
    new spell_dk_deaths_advance();
    new spell_dk_death_coil();
    new spell_dk_death_gate();
    new spell_dk_death_grip();
    new spell_dk_death_pact();
    new spell_dk_death_strike();
    new spell_dk_death_strike_enabler();
    new spell_dk_festering();
    new spell_dk_ghoul_explode();
    new spell_dk_icebound_fortitude();
    new spell_dk_improved_blood_presence();
    new spell_dk_improved_frost_presence();
    new spell_dk_improved_unholy_presence();
    new spell_dk_merciless_combat();
    new spell_dk_necrotic_strike();
    new spell_dk_pestilence();
    new spell_dk_pet_scaling_01();
    new spell_dk_pet_scaling_02();
    new spell_dk_pet_scaling_03();
    new spell_dk_pet_spells();
    new spell_dk_pillar_of_frost();
    new spell_dk_presence();
    new spell_dk_raise_dead();
    new spell_dk_resilient_infection();
    new spell_dk_rune_tap_party();
    new spell_dk_rune_weapon_scaling_02();
    new spell_dk_scent_of_blood();
    new spell_dk_scourge_strike();
    new spell_dk_strangulate();
    new spell_dk_vampiric_blood();
    new spell_dk_will_of_the_necropolis();
	new spell_dk_death_grip_initial();

    new spell_dk_advantage_t10_4p();
    new spell_dk_dancing_rune_weapon();
    new spell_dk_pvp_4p_bonus();

}


