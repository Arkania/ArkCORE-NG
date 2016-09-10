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
 * Scripts for spells with SPELLFAMILY_ROGUE and SPELLFAMILY_GENERIC spells used by rogue players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_rog_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Containers.h"

enum RogueSpells
{
    SPELL_ROGUE_BLADE_FLURRY                        = 13877,
    SPELL_ROGUE_BLADE_FLURRY_EXTRA_ATTACK           = 22482,
    SPELL_ROGUE_CHEAT_DEATH_COOLDOWN                = 31231,
    SPELL_ROGUE_CRIPPLING_POISON                    = 3409,
    SPELL_ROGUE_GLYPH_OF_PREPARATION                = 56819,
    SPELL_ROGUE_KILLING_SPREE                       = 51690,
    SPELL_ROGUE_KILLING_SPREE_TELEPORT              = 57840,
    SPELL_ROGUE_KILLING_SPREE_WEAPON_DMG            = 57841,
    SPELL_ROGUE_KILLING_SPREE_DMG_BUFF              = 61851,
    SPELL_ROGUE_MASTER_OF_SUBTLETY_DAMAGE_PERCENT   = 31665,
    SPELL_ROGUE_MASTER_OF_SUBTLETY_PASSIVE          = 31223,
    SPELL_ROGUE_MASTER_OF_SUBTLETY_PERIODIC         = 31666,
    SPELL_ROGUE_OVERKILL_TALENT                     = 58426,
    SPELL_ROGUE_OVERKILL_PERIODIC                   = 58428,
    SPELL_ROGUE_OVERKILL_POWER_REGEN                = 58427,
    SPELL_ROGUE_PREY_ON_THE_WEAK                    = 58670,
    SPELL_ROGUE_SHIV_TRIGGERED                      = 5940,
    SPELL_ROGUE_SILCE_AND_DICE                      = 5171,
    SPELL_ROGUE_TRICKS_OF_THE_TRADE_DMG_BOOST       = 57933,
    SPELL_ROGUE_TRICKS_OF_THE_TRADE_PROC            = 59628
};

// 53 - Backstab
class spell_rog_backstab : public SpellScriptLoader
{
public:
    spell_rog_backstab() : SpellScriptLoader("spell_rog_backstab") { }

    class spell_rog_backstab_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_backstab_SpellScript);

        bool Load()
        {
            return GetCaster()->GetTypeId() == TYPEID_PLAYER;
        }

        bool Validate(SpellInfo const* /*spellInfo*/){ return true; }

        void HandleOnHit()
        {
            Unit* caster = GetCaster();
            if (Unit* unitTarget = GetHitUnit())
                if (unitTarget->HasAuraState(AURA_STATE_HEALTHLESS_35_PERCENT, GetSpellInfo(), caster))
                    if (AuraEffect* aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_ROGUE, 134, 0))
                    {
                        int32 bp0 = aurEff->GetAmount();
                        caster->CastCustomSpell(caster, 79132, &bp0, 0, 0, true);
                    }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_rog_backstab_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_rog_backstab_SpellScript();
    }
};

// 1776
class spell_rog_gouge : public SpellScriptLoader
{
public:
    spell_rog_gouge(): SpellScriptLoader("spell_rog_gouge") { }

    class aura_script_impl : public AuraScript
    {
        enum { SPELL_SANGUINARY_VEIN = 79146 };

        PrepareAuraScript(aura_script_impl);

        bool Load()
        {
            Unit const* const caster = GetCaster();
            return caster && caster->GetTypeId() == TYPEID_PLAYER;
        }

        bool HandleCheckProc(ProcEventInfo& eventInfo)
        {
            Unit const* const caster = GetCaster();
            SpellInfo const* const triggerSpell = eventInfo.GetSpellInfo();

            if (triggerSpell)
            {
                // Prevents proc by damage from the spell itself
                if (triggerSpell->Id != GetId())
                    return true;

                // Sanguinary Vein
                if (AuraEffect const* const aurEff = caster->GetAuraEffectOfRankedSpell(SPELL_SANGUINARY_VEIN, EFFECT_1))
                    if (triggerSpell->GetAuraState() == AURA_STATE_BLEEDING && roll_chance_i(aurEff->GetAmount()))
                        return false;
            }

            return true;
        }

        void Register()
        {
            DoCheckProc += AuraCheckProcFn(aura_script_impl::HandleCheckProc);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new aura_script_impl();
    }
};

// 1784 - Stealth
class spell_rog_stealth : public SpellScriptLoader
{
public:
    spell_rog_stealth() : SpellScriptLoader("spell_rog_stealth") { }

    class spell_rog_stealth_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_stealth_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_ROGUE_MASTER_OF_SUBTLETY_PASSIVE) ||
                !sSpellMgr->GetSpellInfo(SPELL_ROGUE_MASTER_OF_SUBTLETY_DAMAGE_PERCENT) ||
                !sSpellMgr->GetSpellInfo(SPELL_ROGUE_MASTER_OF_SUBTLETY_PERIODIC) ||
                !sSpellMgr->GetSpellInfo(SPELL_ROGUE_OVERKILL_TALENT) ||
                !sSpellMgr->GetSpellInfo(SPELL_ROGUE_OVERKILL_POWER_REGEN) ||
                !sSpellMgr->GetSpellInfo(SPELL_ROGUE_OVERKILL_PERIODIC))
                return false;
            return true;
        }

        void HandleEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* target = GetTarget();

            // Master of Subtlety
            if (AuraEffect const* aurEff = target->GetAuraEffect(SPELL_ROGUE_MASTER_OF_SUBTLETY_PASSIVE, EFFECT_0))
            {
                int32 basepoints0 = aurEff->GetAmount();
                target->CastCustomSpell(target, SPELL_ROGUE_MASTER_OF_SUBTLETY_DAMAGE_PERCENT, &basepoints0, NULL, NULL, true);
            }

            // Overkill
            if (target->HasAura(SPELL_ROGUE_OVERKILL_TALENT))
                target->CastSpell(target, SPELL_ROGUE_OVERKILL_POWER_REGEN, true);
        }

        void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* target = GetTarget();

            // Master of subtlety
            if (target->HasAura(SPELL_ROGUE_MASTER_OF_SUBTLETY_PASSIVE))
                target->CastSpell(target, SPELL_ROGUE_MASTER_OF_SUBTLETY_PERIODIC, true);

            // Overkill
            if (target->HasAura(SPELL_ROGUE_OVERKILL_TALENT))
                target->CastSpell(target, SPELL_ROGUE_OVERKILL_PERIODIC, true);
        }

        void Register()
        {
            AfterEffectApply += AuraEffectApplyFn(spell_rog_stealth_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            AfterEffectRemove += AuraEffectRemoveFn(spell_rog_stealth_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_rog_stealth_AuraScript();
    }
};

// 1943 - Rupture
class spell_rog_rupture : public SpellScriptLoader
{
public:
    spell_rog_rupture() : SpellScriptLoader("spell_rog_rupture") { }

    class spell_rog_rupture_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_rupture_AuraScript);

        bool Load() override
        {
            Unit* caster = GetCaster();
            return caster && caster->GetTypeId() == TYPEID_PLAYER;
        }

        void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
        {
            if (Unit* caster = GetCaster())
            {
                canBeRecalculated = false;

                float const attackpowerPerCombo[6] =
                {
                    0.0f,
                    0.015f,         // 1 point:  ${($m1 + $b1*1 + 0.015 * $AP) * 4} damage over 8 secs
                    0.024f,         // 2 points: ${($m1 + $b1*2 + 0.024 * $AP) * 5} damage over 10 secs
                    0.03f,          // 3 points: ${($m1 + $b1*3 + 0.03 * $AP) * 6} damage over 12 secs
                    0.03428571f,    // 4 points: ${($m1 + $b1*4 + 0.03428571 * $AP) * 7} damage over 14 secs
                    0.0375f         // 5 points: ${($m1 + $b1*5 + 0.0375 * $AP) * 8} damage over 16 secs
                };

                uint8 cp = caster->ToPlayer()->GetComboPoints();
                if (cp > 5)
                    cp = 5;

                amount += int32(caster->GetTotalAttackPowerValue(BASE_ATTACK) * attackpowerPerCombo[cp]);
            }
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_rog_rupture_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_rog_rupture_AuraScript();
    }
};

// 2094 - Blind
class spell_rog_blind : public SpellScriptLoader
{
public:
    spell_rog_blind() : SpellScriptLoader("spell_rog_blind") { }

    class spell_rog_blind_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_blind_SpellScript);

        bool Load()
        {
            return GetCaster()->GetTypeId() == TYPEID_PLAYER;
        }

        bool Validate(SpellInfo const* /*spellInfo*/){ return true; }

        void HandleOnHit()
        {
            Unit* caster = GetCaster();
            if (Unit* unitTarget = GetHitUnit())
                if (AuraEffect* aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_ROGUE, 48, 0))
                {
                    unitTarget->RemoveAurasByType(SPELL_AURA_PERIODIC_DAMAGE, 0, unitTarget->GetAura(32409)); // SW:D shall not be removed.
                    unitTarget->RemoveAurasByType(SPELL_AURA_PERIODIC_DAMAGE_PERCENT, 0, NULL, true, false);
                    unitTarget->RemoveAurasByType(SPELL_AURA_PERIODIC_LEECH);
                }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_rog_blind_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_rog_blind_SpellScript();
    }
};

// 2098
class spell_rog_eviscerate : public SpellScriptLoader
{
public:
    spell_rog_eviscerate(): SpellScriptLoader("spell_rog_eviscerate") { }

    class script_impl : public SpellScript
    {
        PrepareSpellScript(script_impl);

        enum
        {
            SPELL_EVISCERATE_BONUS = 37169,
            SPELL_SERRATED_BLADES = 14171,
            SPELL_RUPTURE = 1943,
            SPELL_REVEALING_STRIKE = 84617,
        };

        bool Load()
        {
            return GetCaster()->GetTypeId() == TYPEID_PLAYER;
        }

        void HandleHit()
        {
            Player* const caster = GetCaster()->ToPlayer();
            Unit* const target = GetHitUnit();
            if (!target)
                return;

            int32 value = GetHitDamage();
            uint8 const cp = caster->GetComboPoints();
            float const ap = caster->GetTotalAttackPowerValue(BASE_ATTACK);

            value += int32(ap * cp * 0.091f);

            // Eviscerate and Envenom Bonus Damage
            if (AuraEffect const* const aurEff = caster->GetAuraEffect(SPELL_EVISCERATE_BONUS, EFFECT_0))
                value += cp * aurEff->GetAmount();

            // Revealing Strike
            if (AuraEffect const* const aurEff = target->GetAuraEffect(SPELL_REVEALING_STRIKE, EFFECT_2))
                AddPct(value, aurEff->GetAmount());

            // Serrated Blades
            if (AuraEffect const* const aurEff = caster->GetAuraEffectOfRankedSpell(SPELL_SERRATED_BLADES, EFFECT_0))
                if (roll_chance_i(aurEff->GetAmount() * cp))
                    if (Aura* const aura = target->GetAura(SPELL_RUPTURE, caster->GetGUID()))
                        aura->RefreshDuration();

            SetHitDamage(value);
        }

        void Register()
        {
            OnHit += SpellHitFn(script_impl::HandleHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new script_impl();
    }
};

// 2818 - Deadly Poison
class spell_rog_deadly_poison : public SpellScriptLoader
{
public:
    spell_rog_deadly_poison() : SpellScriptLoader("spell_rog_deadly_poison") { }

    class spell_rog_deadly_poison_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_deadly_poison_SpellScript);

        bool Load() override
        {
            _stackAmount = 0;
            // at this point CastItem must already be initialized
            return GetCaster()->GetTypeId() == TYPEID_PLAYER && GetCastItem();
        }

        void HandleBeforeHit()
        {
            if (Unit* target = GetHitUnit())
                // Deadly Poison
                if (AuraEffect const* aurEff = target->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_ROGUE, 0x10000, 0x80000, 0, GetCaster()->GetGUID()))
                    _stackAmount = aurEff->GetBase()->GetStackAmount();
        }

        void HandleAfterHit()
        {
            if (_stackAmount < 5)
                return;

            Player* player = GetCaster()->ToPlayer();

            if (Unit* target = GetHitUnit())
            {

                Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);

                if (item == GetCastItem())
                    item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

                if (!item)
                    return;

                // item combat enchantments
                for (uint8 slot = 0; slot < MAX_ENCHANTMENT_SLOT; ++slot)
                {
                    if (slot > PRISMATIC_ENCHANTMENT_SLOT && slot < PROP_ENCHANTMENT_SLOT_0)    // not holding enchantment id
                        continue;

                    SpellItemEnchantmentEntry const* enchant = sSpellItemEnchantmentStore.LookupEntry(item->GetEnchantmentId(EnchantmentSlot(slot)));
                    if (!enchant)
                        continue;

                    for (uint8 s = 0; s < 3; ++s)
                    {
                        if (enchant->type[s] != ITEM_ENCHANTMENT_TYPE_COMBAT_SPELL)
                            continue;

                        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(enchant->spellid[s]);
                        if (!spellInfo)
                        {
                            TC_LOG_ERROR("spells", "Player::CastItemCombatSpell Enchant %i, player (Name: %s, GUID: %u) cast unknown spell %i", enchant->ID, player->GetName().c_str(), player->GetGUIDLow(), enchant->spellid[s]);
                            continue;
                        }

                        // Proc only rogue poisons
                        if (spellInfo->SpellFamilyName != SPELLFAMILY_ROGUE || spellInfo->Dispel != DISPEL_POISON)
                            continue;

                        // Do not reproc deadly
                        if (spellInfo->SpellFamilyFlags.IsEqual(0x10000, 0x80000, 0))
                            continue;

                        if (spellInfo->IsPositive())
                            player->CastSpell(player, enchant->spellid[s], true, item);
                        else
                            player->CastSpell(target, enchant->spellid[s], true, item);
                    }
                }
            }
        }

        void Register() override
        {
            BeforeHit += SpellHitFn(spell_rog_deadly_poison_SpellScript::HandleBeforeHit);
            AfterHit += SpellHitFn(spell_rog_deadly_poison_SpellScript::HandleAfterHit);
        }

        uint8 _stackAmount;
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_rog_deadly_poison_SpellScript();
    }
};

// 5938 - Shiv
class spell_rog_shiv : public SpellScriptLoader
{
public:
    spell_rog_shiv() : SpellScriptLoader("spell_rog_shiv") { }

    class spell_rog_shiv_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_shiv_SpellScript);

        bool Load() override
        {
            return GetCaster()->GetTypeId() == TYPEID_PLAYER;
        }

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_ROGUE_SHIV_TRIGGERED))
                return false;
            return true;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            if (Unit* unitTarget = GetHitUnit())
                caster->CastSpell(unitTarget, SPELL_ROGUE_SHIV_TRIGGERED, true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_rog_shiv_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_rog_shiv_SpellScript();
    }
};

// 6770 - Sap
class spell_rog_sap : public SpellScriptLoader
{
public:
    spell_rog_sap() : SpellScriptLoader("spell_rog_sap") { }

    class spell_rog_sap_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_sap_AuraScript);

        void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (!GetCaster())
                return;

            if (AuraEffect * dummy = GetCaster()->GetDummyAuraEffect(SPELLFAMILY_GENERIC, 4900, 0))
            {
                uint32 spellId = 0;
                switch (dummy->GetId())
                {
                case 79123:
                    spellId = 79124;
                    break;
                case 79125:
                    spellId = 79126;
                    break;
                }
                GetTarget()->CastSpell(GetTarget(), spellId, true);
            }
        }

        void Register()
        {
            AfterEffectRemove += AuraEffectRemoveFn(spell_rog_sap_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_rog_sap_AuraScript();
    }
};

// 13877, 33735, (check 51211, 65956) - Blade Flurry
class spell_rog_blade_flurry : public SpellScriptLoader
{
    public:
        spell_rog_blade_flurry() : SpellScriptLoader("spell_rog_blade_flurry") { }

        class spell_rog_blade_flurry_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_rog_blade_flurry_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_ROGUE_BLADE_FLURRY_EXTRA_ATTACK))
                    return false;
                return true;
            }

            bool Load() override
            {
                _procTarget = nullptr;
                return true;
            }

            bool CheckProc(ProcEventInfo& eventInfo)
            {
                _procTarget = GetTarget()->SelectNearbyTarget(eventInfo.GetProcTarget());
                return _procTarget && eventInfo.GetDamageInfo();
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                TC_LOG_ERROR("misc", "damage: %u procSpell: %u",
                    eventInfo.GetDamageInfo()->GetDamage(), eventInfo.GetDamageInfo()->GetSpellInfo() ? eventInfo.GetDamageInfo()->GetSpellInfo()->Id : 0);

                GetTarget()->CastCustomSpell(SPELL_ROGUE_BLADE_FLURRY_EXTRA_ATTACK, SPELLVALUE_BASE_POINT0, eventInfo.GetDamageInfo()->GetDamage(), _procTarget, true, NULL, aurEff);
            }

            void Register() override
            {
                DoCheckProc += AuraCheckProcFn(spell_rog_blade_flurry_AuraScript::CheckProc);
                if (m_scriptSpellId == SPELL_ROGUE_BLADE_FLURRY)
                    OnEffectProc += AuraEffectProcFn(spell_rog_blade_flurry_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_MOD_POWER_REGEN_PERCENT);
                else
                    OnEffectProc += AuraEffectProcFn(spell_rog_blade_flurry_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_MOD_MELEE_HASTE);
            }

        private:
            Unit* _procTarget;
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_rog_blade_flurry_AuraScript();
        }
};

// 14185 - Preparation
class spell_rog_preparation : public SpellScriptLoader
{
public:
    spell_rog_preparation() : SpellScriptLoader("spell_rog_preparation") { }

    class spell_rog_preparation_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_preparation_SpellScript);

        bool Load() override
        {
            return GetCaster()->GetTypeId() == TYPEID_PLAYER;
        }

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_ROGUE_GLYPH_OF_PREPARATION))
                return false;
            return true;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Player* caster = GetCaster()->ToPlayer();

            // immediately finishes the cooldown on certain Rogue abilities
            SpellCooldowns const& cm = caster->GetSpellCooldownMap();
            for (SpellCooldowns::const_iterator itr = cm.begin(); itr != cm.end();)
            {
                SpellInfo const* spellInfo = sSpellMgr->EnsureSpellInfo(itr->first);
                if (spellInfo->SpellFamilyName != SPELLFAMILY_ROGUE)
                {
                    ++itr;
                    continue;
                }

                if ((spellInfo->SpellFamilyFlags[1] & SPELLFAMILYFLAG1_ROGUE_SHADOWSTEP ||              // Shadowstep
                    spellInfo->SpellFamilyFlags[0] & SPELLFAMILYFLAG0_ROGUE_VAN_SPRINT) ||              // Vanish, Sprint
                    // Glyph of Preparation
                    (caster->HasAura(SPELL_ROGUE_GLYPH_OF_PREPARATION) &&
                    (spellInfo->SpellFamilyFlags[1] & SPELLFAMILYFLAG1_ROGUE_DISMANTLE_SMOKE_BOMB ||    // Dismantle, Smoke Bomb
                    spellInfo->SpellFamilyFlags[0] & SPELLFAMILYFLAG0_ROGUE_KICK)))                     // Kick
                {
                    caster->RemoveSpellCooldown((itr++)->first, true);
                }
                else
                    ++itr;
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_rog_preparation_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_rog_preparation_SpellScript();
    }
};

// 31130 - Nerves of Steel
class spell_rog_nerves_of_steel : public SpellScriptLoader
{
public:
    spell_rog_nerves_of_steel() : SpellScriptLoader("spell_rog_nerves_of_steel") { }

    class spell_rog_nerves_of_steel_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_nerves_of_steel_AuraScript);

        uint32 absorbPct;

        bool Load() override
        {
            absorbPct = GetSpellInfo()->Effects[EFFECT_0].CalcValue(GetCaster());
            return true;
        }

        void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
        {
            // Set absorbtion amount to unlimited
            amount = -1;
        }

        void Absorb(AuraEffect* /*aurEff*/, DamageInfo & dmgInfo, uint32 & absorbAmount)
        {
            // reduces all damage taken while stun or fear
            if (GetTarget()->GetUInt32Value(UNIT_FIELD_FLAGS) & (UNIT_FLAG_FLEEING) || (GetTarget()->GetUInt32Value(UNIT_FIELD_FLAGS) & (UNIT_FLAG_STUNNED) && GetTarget()->HasAuraWithMechanic(1 << MECHANIC_STUN)))
                absorbAmount = CalculatePct(dmgInfo.GetDamage(), absorbPct);
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_rog_nerves_of_steel_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            OnEffectAbsorb += AuraEffectAbsorbFn(spell_rog_nerves_of_steel_AuraScript::Absorb, EFFECT_0);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_rog_nerves_of_steel_AuraScript();
    }
};

// 31228 - Cheat Death
class spell_rog_cheat_death : public SpellScriptLoader
{
    public:
        spell_rog_cheat_death() : SpellScriptLoader("spell_rog_cheat_death") { }

        class spell_rog_cheat_death_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_rog_cheat_death_AuraScript);

            uint32 absorbChance;

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_ROGUE_CHEAT_DEATH_COOLDOWN))
                    return false;
                return true;
            }

            bool Load() override
            {
                absorbChance = GetSpellInfo()->Effects[EFFECT_0].CalcValue();
                return GetUnitOwner()->ToPlayer();
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                // Set absorbtion amount to unlimited
                amount = -1;
            }

            void Absorb(AuraEffect* /*aurEff*/, DamageInfo & dmgInfo, uint32 & absorbAmount)
            {
                Player* target = GetTarget()->ToPlayer();
                if (dmgInfo.GetDamage() < target->GetHealth() || target->HasSpellCooldown(SPELL_ROGUE_CHEAT_DEATH_COOLDOWN) ||  !roll_chance_i(absorbChance))
                    return;

                target->CastSpell(target, SPELL_ROGUE_CHEAT_DEATH_COOLDOWN, true);
                target->AddSpellCooldown(SPELL_ROGUE_CHEAT_DEATH_COOLDOWN, 0, time(NULL) + 60);

                uint32 health10 = target->CountPctFromMaxHealth(10);

                // hp > 10% - absorb hp till 10%
                if (target->GetHealth() > health10)
                    absorbAmount = dmgInfo.GetDamage() - target->GetHealth() + health10;
                // hp lower than 10% - absorb everything
                else
                    absorbAmount = dmgInfo.GetDamage();
            }

            void Register() override
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_rog_cheat_death_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                OnEffectAbsorb += AuraEffectAbsorbFn(spell_rog_cheat_death_AuraScript::Absorb, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_rog_cheat_death_AuraScript();
        }
};

// 31666 - Master of Subtlety
class spell_rog_master_of_subtlety : public SpellScriptLoader
{
public:
    spell_rog_master_of_subtlety() : SpellScriptLoader("spell_rog_master_of_subtlety") { }

    class spell_rog_master_of_subtlety_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_master_of_subtlety_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_ROGUE_MASTER_OF_SUBTLETY_DAMAGE_PERCENT))
                return false;
            return true;
        }

        void HandleEffectPeriodic(AuraEffect const* /*aurEff*/)
        {
            Unit* target = GetTarget();

            if (!target->HasAuraType(SPELL_AURA_MOD_STEALTH))
                target->RemoveAurasDueToSpell(SPELL_ROGUE_MASTER_OF_SUBTLETY_DAMAGE_PERCENT);
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_rog_master_of_subtlety_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_rog_master_of_subtlety_AuraScript();
    }
};

// 51625 51626
class spell_rog_deadly_brew : public SpellScriptLoader
{
public:
    spell_rog_deadly_brew(): SpellScriptLoader("spell_rog_deadly_brew") {  }

    class script_impl : public AuraScript
    {
        PrepareAuraScript(script_impl);

        enum { SPELL_CRIPPLING_POISON = 3409 };

        void OnProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
        {
            GetTarget()->CastSpell(eventInfo.GetProcTarget(), SPELL_CRIPPLING_POISON, true, NULL, aurEff);
        }

        void Register()
        {
            OnEffectProc += AuraEffectProcFn(script_impl::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new script_impl();
    }
};

// -51664 - Cut to the Chase
class spell_rog_cut_to_the_chase : public SpellScriptLoader
{
    public:
        spell_rog_cut_to_the_chase () : SpellScriptLoader("spell_rog_cut_to_the_chase") { }

        class spell_rog_cut_to_the_chase_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_rog_cut_to_the_chase_AuraScript);

            void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
            {
                PreventDefaultAction();
                if (Aura* aur = GetTarget()->GetAura(SPELL_ROGUE_SILCE_AND_DICE))
                    aur->SetDuration(aur->GetSpellInfo()->GetMaxDuration(), true);
            }

            void Register() override
            {
                OnEffectProc += AuraEffectProcFn(spell_rog_cut_to_the_chase_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_rog_cut_to_the_chase_AuraScript();
        }
};

// 51685 - Prey on the Weak
class spell_rog_prey_on_the_weak : public SpellScriptLoader
{
public:
    spell_rog_prey_on_the_weak() : SpellScriptLoader("spell_rog_prey_on_the_weak") { }

    class spell_rog_prey_on_the_weak_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_prey_on_the_weak_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_ROGUE_PREY_ON_THE_WEAK))
                return false;
            return true;
        }

        void HandleEffectPeriodic(AuraEffect const* /*aurEff*/)
        {
            Unit* target = GetTarget();
            Unit* victim = target->GetVictim();
            if (victim && (target->GetHealthPct() > victim->GetHealthPct()))
            {
                if (!target->HasAura(SPELL_ROGUE_PREY_ON_THE_WEAK))
                {
                    int32 bp = GetSpellInfo()->Effects[EFFECT_0].CalcValue();
                    target->CastCustomSpell(target, SPELL_ROGUE_PREY_ON_THE_WEAK, &bp, 0, 0, true);
                }
            }
            else
                target->RemoveAurasDueToSpell(SPELL_ROGUE_PREY_ON_THE_WEAK);
        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_rog_prey_on_the_weak_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_rog_prey_on_the_weak_AuraScript();
    }
};

// 51690 - Killing Spree
class spell_rog_killing_spree : public SpellScriptLoader
{
    public:
        spell_rog_killing_spree() : SpellScriptLoader("spell_rog_killing_spree") { }

        class spell_rog_killing_spree_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_rog_killing_spree_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                if (targets.empty() || GetCaster()->GetVehicleBase())
                    FinishCast(SPELL_FAILED_OUT_OF_RANGE);
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Aura* aura = GetCaster()->GetAura(SPELL_ROGUE_KILLING_SPREE))
                {
                    if (spell_rog_killing_spree_AuraScript* script = dynamic_cast<spell_rog_killing_spree_AuraScript*>(aura->GetScriptByName("spell_rog_killing_spree")))
                        script->AddTarget(GetHitUnit());
                }
            }

            void Register() override
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_rog_killing_spree_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ENEMY);
                OnEffectHitTarget += SpellEffectFn(spell_rog_killing_spree_SpellScript::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_rog_killing_spree_SpellScript();
        }

        class spell_rog_killing_spree_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_rog_killing_spree_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_ROGUE_KILLING_SPREE_TELEPORT)
                    || !sSpellMgr->GetSpellInfo(SPELL_ROGUE_KILLING_SPREE_WEAPON_DMG)
                    || !sSpellMgr->GetSpellInfo(SPELL_ROGUE_KILLING_SPREE_DMG_BUFF))
                    return false;
                return true;
            }

            void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                GetTarget()->CastSpell(GetTarget(), SPELL_ROGUE_KILLING_SPREE_DMG_BUFF, true);
            }

            void HandleEffectPeriodic(AuraEffect const* /*aurEff*/)
            {
                while (!_targets.empty())
                {
                    uint64 guid = Trinity::Containers::SelectRandomContainerElement(_targets);
                    if (Unit* target = ObjectAccessor::GetUnit(*GetTarget(), guid))
                    {
                        GetTarget()->CastSpell(target, SPELL_ROGUE_KILLING_SPREE_TELEPORT, true);
                        GetTarget()->CastSpell(target, SPELL_ROGUE_KILLING_SPREE_WEAPON_DMG, true);
                        break;
                    }
                    else
                        _targets.remove(guid);
                }
            }

            void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                GetTarget()->RemoveAurasDueToSpell(SPELL_ROGUE_KILLING_SPREE_DMG_BUFF);
            }

            void Register() override
            {
                AfterEffectApply += AuraEffectApplyFn(spell_rog_killing_spree_AuraScript::HandleApply, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_rog_killing_spree_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
                AfterEffectRemove += AuraEffectRemoveFn(spell_rog_killing_spree_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }

        public:
            void AddTarget(Unit* target)
            {
                _targets.push_back(target->GetGUID());
            }

        private:
            std::list<uint64> _targets;
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_rog_killing_spree_AuraScript();
        }
};

// 56807
class spell_rog_glyph_of_hemorrhage : public SpellScriptLoader
{
public:
    spell_rog_glyph_of_hemorrhage(): SpellScriptLoader("spell_rog_glyph_of_hemorrhage") { }

    class script_impl : public AuraScript
    {
        PrepareAuraScript(script_impl);

        bool Load()
        {
            Unit const* const caster = GetCaster();
            return caster && caster->GetTypeId() == TYPEID_PLAYER;
        }

        bool HandleCheckProc(ProcEventInfo& eventInfo)
        {
            DamageInfo* const damageInfo = eventInfo.GetDamageInfo();
            return damageInfo && damageInfo->GetDamage();
        }

        void HandleEffectProc(AuraEffect const* aurEff, ProcEventInfo& procInfo)
        {
            PreventDefaultAction();
            Unit* const target = procInfo.GetProcTarget();
            if (!target)
                return;

            uint32 const damage = procInfo.GetDamageInfo()->GetDamage();
            int32 const value = CalculatePct(damage, aurEff->GetAmount()) / 8; // total 40% damage will proc every 3s for 24s, so divide by 8
            uint32 const triggerSpellId = GetSpellInfo()->Effects[EFFECT_0].TriggerSpell;

            GetCaster()->CastCustomSpell(target, triggerSpellId, &value, NULL, NULL, true);
        }

        void Register()
        {
            DoCheckProc += AuraCheckProcFn(script_impl::HandleCheckProc);
            OnEffectProc += AuraEffectProcFn(script_impl::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new script_impl();
    }
};

// 57934 - Tricks of the Trade
class spell_rog_tricks_of_the_trade : public SpellScriptLoader
{
public:
    spell_rog_tricks_of_the_trade() : SpellScriptLoader("spell_rog_tricks_of_the_trade") { }

    class spell_rog_tricks_of_the_trade_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_tricks_of_the_trade_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_ROGUE_TRICKS_OF_THE_TRADE_DMG_BOOST))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_ROGUE_TRICKS_OF_THE_TRADE_PROC))
                return false;
            return true;
        }

        bool Load() override
        {
            _redirectTarget = nullptr;
            return true;
        }

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_DEFAULT)
                GetTarget()->ResetRedirectThreat();
        }

        bool CheckProc(ProcEventInfo& /*eventInfo*/)
        {
            _redirectTarget = GetTarget()->GetRedirectThreatTarget();
            return _redirectTarget;
        }

        void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
        {
            PreventDefaultAction();

            Unit* target = GetTarget();
            target->CastSpell(_redirectTarget, SPELL_ROGUE_TRICKS_OF_THE_TRADE_DMG_BOOST, true);
            target->CastSpell(target, SPELL_ROGUE_TRICKS_OF_THE_TRADE_PROC, true);
            Remove(AURA_REMOVE_BY_DEFAULT); // maybe handle by proc charges
        }

        void Register() override
        {
            AfterEffectRemove += AuraEffectRemoveFn(spell_rog_tricks_of_the_trade_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            DoCheckProc += AuraCheckProcFn(spell_rog_tricks_of_the_trade_AuraScript::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_rog_tricks_of_the_trade_AuraScript::HandleProc, EFFECT_1, SPELL_AURA_DUMMY);
        }

    private:
        Unit* _redirectTarget;
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_rog_tricks_of_the_trade_AuraScript();
    }
};

// 58428 - Overkill
class spell_rog_overkill : public SpellScriptLoader
{
    public:
        spell_rog_overkill() : SpellScriptLoader("spell_rog_overkill") { }

        class spell_rog_overkill_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_rog_overkill_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_ROGUE_OVERKILL_POWER_REGEN))
                    return false;
                return true;
            }

            void HandleEffectPeriodic(AuraEffect const* /*aurEff*/)
            {
                Unit* target = GetTarget();

                if (!target->HasAuraType(SPELL_AURA_MOD_STEALTH))
                    target->RemoveAurasDueToSpell(SPELL_ROGUE_OVERKILL_POWER_REGEN);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_rog_overkill_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_rog_overkill_AuraScript();
        }
};

// 59628 - Tricks of the Trade (Proc)
class spell_rog_tricks_of_the_trade_proc : public SpellScriptLoader
{
public:
    spell_rog_tricks_of_the_trade_proc() : SpellScriptLoader("spell_rog_tricks_of_the_trade_proc") { }

    class spell_rog_tricks_of_the_trade_proc_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_tricks_of_the_trade_proc_AuraScript);

        void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            GetTarget()->ResetRedirectThreat();
        }

        void Register() override
        {
            AfterEffectRemove += AuraEffectRemoveFn(spell_rog_tricks_of_the_trade_proc_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_rog_tricks_of_the_trade_proc_AuraScript();
    }
};

// 73651 - Recuperate
class spell_rog_recuperate : public SpellScriptLoader
{
    public:
        spell_rog_recuperate() : SpellScriptLoader("spell_rog_recuperate") { }

        class spell_rog_recuperate_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_rog_recuperate_AuraScript);

            enum RogueSpellIcons
            {
                ICON_ROGUE_IMPROVED_RECUPERATE = 4819
            };

            bool Load() override
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void OnPeriodic(AuraEffect const* /*aurEff*/)
            {
                if (Unit* caster = GetCaster())
                    if (AuraEffect* effect = GetAura()->GetEffect(EFFECT_0))
                        effect->RecalculateAmount(caster);
            }

            void CalculateBonus(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
            {
                canBeRecalculated = false;
                if (Unit* caster = GetCaster())
                {
                    int32 baseAmount = GetSpellInfo()->Effects[EFFECT_0].CalcValue(caster) * 1000;
                    // Improved Recuperate
                    if (AuraEffect const* auraEffect = caster->GetDummyAuraEffect(SPELLFAMILY_ROGUE, ICON_ROGUE_IMPROVED_RECUPERATE, EFFECT_0))
                        baseAmount += auraEffect->GetAmount();

                    amount = CalculatePct(caster->GetMaxHealth(), float(baseAmount) / 1000.0f);
                }
            }

            void Register() override
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_rog_recuperate_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_rog_recuperate_AuraScript::CalculateBonus, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_rog_recuperate_AuraScript();
        }
};

// 73981
class spell_rog_redirect : public SpellScriptLoader
{
public:
    spell_rog_redirect(): SpellScriptLoader("spell_rog_redirect"){ }

    class script_impl : public SpellScript
    {
        PrepareSpellScript(script_impl);

        bool Load()
        {
            return GetCaster()->GetTypeId() == TYPEID_PLAYER;
        }

        SpellCastResult CheckCast()
        {
            Player* const caster = GetCaster()->ToPlayer();
            Unit* const target = ObjectAccessor::GetUnit(*caster, caster->GetComboTarget());
            Unit* const selectedUnit = caster->GetSelectedUnit();
            if (!target || !caster->GetComboPoints())
                return SPELL_FAILED_NO_COMBO_POINTS;

            if (!selectedUnit || selectedUnit == target || !selectedUnit->IsAlive())
                return SPELL_FAILED_BAD_TARGETS;

            return SPELL_CAST_OK;
        }

        void HandleAddComboPoints(SpellEffIndex)
        {
            Player* const caster = GetCaster()->ToPlayer();
            uint8 const count = caster->GetComboPoints();
            SetBasepoints(count);

            // Remove Combo points from old target
            if (Unit* const target = ObjectAccessor::GetUnit(*caster, caster->GetComboTarget()))
                target->ClearComboPointHolders();
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(script_impl::CheckCast);
            OnEffectHitTarget += SpellEffectFn(script_impl::HandleAddComboPoints, EFFECT_0, SPELL_EFFECT_ADD_COMBO_POINTS);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new script_impl();
    }
};

// 76577 - Smoke Bomb
class spell_rog_smoke_bomb : public SpellScriptLoader
{
public:
    spell_rog_smoke_bomb() : SpellScriptLoader("spell_rog_smoke_bomb") { }

    class spell_rog_smoke_bomb_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_smoke_bomb_AuraScript);

        void OnTick(AuraEffect const* aurEff)
        {
            Unit* caster = GetCaster();

            if (!caster)
                return;

            if (DynamicObject* dynObj = caster->GetDynObject(76577))
            {
                // Casts aoe interfere targetting aura
                caster->CastSpell(dynObj->GetPositionX(), dynObj->GetPositionY(), dynObj->GetPositionZ(), 88611, true);
            }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_rog_smoke_bomb_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_rog_smoke_bomb_AuraScript();
    }
};

// 79095 79096
class spell_rog_restless_blades : public SpellScriptLoader
{
public:
    spell_rog_restless_blades(): SpellScriptLoader("spell_rog_restless_blades") {  }

    class script_impl : public AuraScript
    {
        PrepareAuraScript(script_impl);

        enum
        {
            SPELL_ADRENALINE_RUSH = 13750,
            SPELL_KILLING_SPREE = 51690,
            SPELL_REDIRECT = 73981,
            SPELL_SPRINT = 2983,
        };

        bool Load()
        {
            Unit const* const caster = GetCaster();
            return caster && caster->GetTypeId() == TYPEID_PLAYER;
        }

        bool HandleCheckProc(ProcEventInfo& eventInfo)
        {
            Player* const player = GetUnitOwner()->ToPlayer();
            if (!player)
                return false;

            uint8 const comboPoints = player->GetComboPoints();
            if (!comboPoints)
                return false;

            return true;
        }

        void HandleEffectProc(AuraEffect const* aurEff, ProcEventInfo& procInfo)
        {
            Player* const player = GetUnitOwner()->ToPlayer();
            uint8 const comboPoints = player->GetComboPoints();

            int32 const value = aurEff->GetAmount() * comboPoints;

            // Reduce cooldown of Adrenaline Rush, Killing Spree, Redirect and Sprint
            player->ModifySpellCooldown(SPELL_ADRENALINE_RUSH, -value);
            player->ModifySpellCooldown(SPELL_KILLING_SPREE, -value);
            player->ModifySpellCooldown(SPELL_REDIRECT, -value);
            player->ModifySpellCooldown(SPELL_SPRINT, -value);
        }

        void Register()
        {
            DoCheckProc += AuraCheckProcFn(script_impl::HandleCheckProc);
            OnEffectProc += AuraEffectProcFn(script_impl::HandleEffectProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new script_impl();
    }
};

// 84590
class spell_rog_deadly_momentum : public SpellScriptLoader
{
public:
    spell_rog_deadly_momentum(): SpellScriptLoader("spell_rog_deadly_momentum") { }

    class script_impl : public AuraScript
    {
        PrepareAuraScript(script_impl);

        enum
        {
            SPELL_RECUPERATE = 73651,
            SPELL_SLICE_AND_DICE = 5171,
        };

        void OnApply(AuraEffect const* const, AuraEffectHandleModes)
        {
            Unit const* const target = GetTarget();

            // Recuperate
            if (Aura* const aura = target->GetAura(SPELL_RECUPERATE))
                aura->RefreshDuration();

            // Slice and Dice
            if (Aura* const aura = target->GetAura(SPELL_SLICE_AND_DICE))
                aura->RefreshDuration();
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(script_impl::OnApply, EFFECT_0, SPELL_AURA_ADD_FLAT_MODIFIER, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new script_impl();
    }
};

// 84617
class spell_rog_revealing_strike : public SpellScriptLoader
{
public:
    spell_rog_revealing_strike() : SpellScriptLoader("spell_rog_revealing_strike") { }

    class spell_rog_revealing_strike_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_revealing_strike_AuraScript);

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetDamageInfo())
            {
                if (const SpellInfo*  procSpell = eventInfo.GetDamageInfo()->GetSpellInfo())
                {
                    if (!procSpell->NeedsComboPoints() || !eventInfo.GetDamageInfo()->GetDamage())
                        return false;
                    return true;
                }
            }
            return false;
        }

        void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();
        }

        void Register()
        {
            DoCheckProc += AuraCheckProcFn(spell_rog_revealing_strike_AuraScript::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_rog_revealing_strike_AuraScript::HandleProc, EFFECT_2, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_rog_revealing_strike_AuraScript();
    }
};


void AddSC_rogue_spell_scripts()
{
    new spell_rog_blade_flurry();
    new spell_rog_cheat_death();
    new spell_rog_cut_to_the_chase();
    new spell_rog_deadly_poison();
    new spell_rog_killing_spree();
    new spell_rog_master_of_subtlety();
    new spell_rog_nerves_of_steel();
    new spell_rog_overkill();
    new spell_rog_preparation();
    new spell_rog_prey_on_the_weak();
    new spell_rog_recuperate();
    new spell_rog_rupture();
    new spell_rog_shiv();
    new spell_rog_stealth();
    new spell_rog_tricks_of_the_trade();
    new spell_rog_tricks_of_the_trade_proc();
    new spell_rog_revealing_strike();
    new spell_rog_backstab();
    new spell_rog_sap();
    new spell_rog_gouge();
    new spell_rog_blind();
    new spell_rog_deadly_brew();
    new spell_rog_deadly_momentum();
    new spell_rog_eviscerate();
    new spell_rog_redirect();
    new spell_rog_glyph_of_hemorrhage();
    new spell_rog_restless_blades();

};

/*  found old spells there now are part of core

    new spell_rog_smoke_bomb();
    new spell_rog_crippling_poison();

*/
