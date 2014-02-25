/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2014 ArkCORE <http://www.arkania.net/> 
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
 * Scripts for spells with SPELLFAMILY_SHAMAN and SPELLFAMILY_GENERIC spells used by shaman players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_sha_".
 */

#include "ScriptMgr.h"
#include "GridNotifiers.h"
#include "Unit.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

enum ShamanSpells
{
    SHAMAN_BIND_SIGHT                      = 6277,

    ICON_ID_SHAMAN_LAVA_FLOW               = 3087,
    SHAMAN_LAVA_FLOWS_R1                   = 51480,
    SHAMAN_LAVA_FLOWS_TRIGGERED_R1         = 65264,
};

enum RaidHasteSpellsBuffsAndDebuffs
{
    HASTE_BUFF_BLOODLUST                = 2825,
    HASTE_DEBUFF_SATED                  = 57724,

    HASTE_BUFF_HEROISM                  = 32182,
    HASTE_DEBUFF_EXHAUSTION             = 57723,

    HASTE_BUFF_TIME_WARP                = 80353,
    HASTE_DEBUFF_TEMPORAL_DISPLACEMENT  = 80354,

    HASTE_BUFF_ANCIENT_HYSTERIA         = 90355,
    HASTE_DEBUFF_INSANITY               = 95809,
};

class spell_raid_haste : public SpellScriptLoader
{
    public:
        spell_raid_haste() : SpellScriptLoader("spell_raid_haste") { }

        class spell_raid_haste_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_raid_haste_SpellScript);

            bool Validate(SpellInfo const* /*spellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(HASTE_DEBUFF_SATED) || !sSpellMgr->GetSpellInfo(HASTE_DEBUFF_EXHAUSTION) || !sSpellMgr->GetSpellInfo(HASTE_DEBUFF_TEMPORAL_DISPLACEMENT) || !sSpellMgr->GetSpellInfo(HASTE_DEBUFF_INSANITY))
                    return false;
                return true;
            }

            void RemoveInvalidTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if(Trinity::UnitAuraCheck(true, HASTE_DEBUFF_SATED));
                targets.remove_if(Trinity::UnitAuraCheck(true, HASTE_DEBUFF_EXHAUSTION));
                targets.remove_if(Trinity::UnitAuraCheck(true, HASTE_DEBUFF_TEMPORAL_DISPLACEMENT));
                targets.remove_if(Trinity::UnitAuraCheck(true, HASTE_DEBUFF_INSANITY));
            }

            void ApplyDebuff()
            {
                switch (GetSpellInfo()->Id)
                {
                        case HASTE_BUFF_BLOODLUST:
                             GetHitUnit()->CastSpell(GetHitUnit(), HASTE_DEBUFF_SATED, true);
                             break;
                        case HASTE_BUFF_HEROISM:
                             GetHitUnit()->CastSpell(GetHitUnit(), HASTE_DEBUFF_EXHAUSTION, true);
                             break;
                        case HASTE_BUFF_TIME_WARP:
                             GetHitUnit()->CastSpell(GetHitUnit(), HASTE_DEBUFF_TEMPORAL_DISPLACEMENT, true);
                             break;
                        case HASTE_BUFF_ANCIENT_HYSTERIA:
                             GetHitUnit()->CastSpell(GetHitUnit(), HASTE_DEBUFF_INSANITY, true);
                             break;
                    }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_raid_haste_SpellScript::RemoveInvalidTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_RAID);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_raid_haste_SpellScript::RemoveInvalidTargets, EFFECT_1, TARGET_UNIT_CASTER_AREA_RAID);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_raid_haste_SpellScript::RemoveInvalidTargets, EFFECT_2, TARGET_UNIT_CASTER_AREA_RAID);
                AfterHit += SpellHitFn(spell_raid_haste_SpellScript::ApplyDebuff);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_raid_haste_SpellScript();
        }
};

// 1064 Chain Heal
class spell_sha_chain_heal : public SpellScriptLoader
{
    public:
        spell_sha_chain_heal() : SpellScriptLoader("spell_sha_chain_heal") { }

        class spell_sha_chain_heal_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_chain_heal_SpellScript);

            bool Load()
            {
                firstHeal = true;
                riptide = false;
                amount = 0;
                return true;
            }

            void HandleHeal(SpellEffIndex /*effIndex*/)
            {
                if (firstHeal)
                {
                    // Check if the target has Riptide
                    if (AuraEffect* aurEff = GetHitUnit()->GetAuraEffect(SPELL_AURA_PERIODIC_HEAL, SPELLFAMILY_SHAMAN, 0, 0, 0x10, GetCaster()->GetGUID()))
                    {
                        riptide = true;
                        // Consume it
                        amount = aurEff->GetSpellInfo()->Effects[EFFECT_2].CalcValue();
                        GetHitUnit()->RemoveAura(aurEff->GetBase());
                    }
                    firstHeal = false;
                }
                // Riptide increases the Chain Heal effect by 25%
                if (riptide)
                    {
                        uint32 bonus = CalculatePctN(GetHitHeal(), amount);
                        SetHitHeal(GetHitHeal() + bonus);
                        }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_sha_chain_heal_SpellScript::HandleHeal, EFFECT_0, SPELL_EFFECT_HEAL);
            }

            bool firstHeal;
            bool riptide;
            uint32 amount;
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_chain_heal_SpellScript();
        }
};

class spell_sha_flame_shock : public SpellScriptLoader
{
    public:
        spell_sha_flame_shock() : SpellScriptLoader("spell_sha_flame_shock") { }

        class spell_sha_flame_shock_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sha_flame_shock_AuraScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SHAMAN_LAVA_FLOWS_R1))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SHAMAN_LAVA_FLOWS_TRIGGERED_R1))
                    return false;
                return true;
            }

            void HandleDispel(DispelInfo* /*dispelInfo*/)
            {
                if (Unit* caster = GetCaster())
                {
                    // Lava Flows
                    if (AuraEffect const* aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_SHAMAN, ICON_ID_SHAMAN_LAVA_FLOW, EFFECT_0))
                    {
                        if (sSpellMgr->GetFirstSpellInChain(SHAMAN_LAVA_FLOWS_R1) != sSpellMgr->GetFirstSpellInChain(aurEff->GetId()))
                            return;

                        int32 basepoints = aurEff->GetAmount();
                        caster->CastCustomSpell(caster, SHAMAN_LAVA_FLOWS_TRIGGERED_R1, &basepoints, NULL, NULL, true);
                    }
                }
            }

            void Register()
            {
                AfterDispel += AuraDispelFn(spell_sha_flame_shock_AuraScript::HandleDispel);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sha_flame_shock_AuraScript();
        }
};

// 61882 - Earthquake
class spell_sha_earthquake : public SpellScriptLoader
{
public:
    spell_sha_earthquake() : SpellScriptLoader("spell_sha_earthquake") { }

    class spell_sha_earthquake_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_sha_earthquake_AuraScript);

        void earthquake(AuraEffect const* /*aurEff*/)
        {
            if (!GetCaster())
                 return;

            if (DynamicObject* dynObj = GetCaster()->GetDynObject(61882))
            {
                GetCaster()->CastSpell(dynObj->GetPositionX(), dynObj->GetPositionY(), dynObj->GetPositionZ(), 77478, true);
            if (roll_chance_i(10))
                    GetCaster()->CastSpell(dynObj->GetPositionX(), dynObj->GetPositionY(), dynObj->GetPositionZ(), 77505, true);
            }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_sha_earthquake_AuraScript::earthquake, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_sha_earthquake_AuraScript();
    }
};

// 16191 - Mana Tide
class spell_sha_mana_tide_totem : public SpellScriptLoader
{
    public:
        spell_sha_mana_tide_totem() : SpellScriptLoader("spell_sha_mana_tide_totem") { }

        class spell_sha_mana_tide_totem_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sha_mana_tide_totem_AuraScript);

            void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
            {
                if (Unit* caster = GetCaster())
                    if (Unit* owner = caster->GetOwner())
                        amount = owner->GetStat(STAT_SPIRIT) * 2;
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_sha_mana_tide_totem_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_MOD_STAT);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sha_mana_tide_totem_AuraScript();
        }
};

void AddSC_shaman_spell_scripts()
{
    new spell_raid_haste();
    new spell_sha_chain_heal();
    new spell_sha_flame_shock();
    new spell_sha_earthquake();
    new spell_sha_mana_tide_totem();
}