/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
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
#include "TotemAI.h"

enum ShamanSpells
{
    SHAMAN_SPELL_FLAME_SHOCK               = 8050,
    SHAMAN_SPELL_FIRE_NOVA_TRIGGERED_R1    = 8349,
    SHAMAN_SPELL_SATED                     = 57724,
    SHAMAN_SPELL_EXHAUSTION                = 57723,
    HUNTER_SPELL_INSANITY                  = 95809,
    MAGE_SPELL_TEMPORAL_DISPLACEMENT       = 80354,

    SHAMAN_SPELL_EARTH_GRASP               = 51483,
    EARTHBIND_TOTEM_SPELL_EARTHGRAB        = 64695,

    // For Earthen Power
    SHAMAN_TOTEM_SPELL_EARTHBIND_TOTEM     = 6474,
    SHAMAN_TOTEM_SPELL_EARTHEN_POWER       = 59566,

    SHAMAN_BIND_SIGHT                      = 6277,

    ICON_ID_SHAMAN_LAVA_FLOW               = 3087,
    SHAMAN_LAVA_FLOWS_R1                   = 51480,
    SHAMAN_LAVA_FLOWS_TRIGGERED_R1         = 65264,
    SHAMAN_SPELL_ANCESTRAL_AWAKENING_PROC  = 52752,
    
    ICON_ID_SOOTHING_RAIN                  = 2011,
    SPELL_HEALING_STREAM_TOTEM_HEAL        = 52042,

    SHAMAN_SPELL_UNLEASH_ELEMENTS          = 73680,

    SHAMAN_SPELL_SPIRIT_LINK               = 98020,
    SHAMAN_SPELL_SPIRIT_LINK_DAMAGE        = 98021,

    SHAMAN_SPELL_EARTH_SHOCK               = 8042,
    SHAMAN_SPELL_FULMINATION               = 88766,
    SHAMAN_SPELL_FULMINATION_TRIGGERED     = 88767,
    SHAMAN_SPELL_FULMINATION_INFO          = 95774,
    SHAMAN_SPELL_LIGHTNING_SHIELD_PROC     = 26364,

    SHAMAN_TOTEM_SPELL_TOTEMIC_WRATH       = 77746,
    SHAMAN_TOTEM_SPELL_TOTEMIC_WRATH_AURA  = 77747,

    SHAMAN_SPELL_THUNDERSTORM_SLOW         = 100955,
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

// 1535 Fire Nova
/// Updated 4.3.4
class spell_sha_fire_nova : public SpellScriptLoader
{
    public:
        spell_sha_fire_nova() : SpellScriptLoader("spell_sha_fire_nova") { }

        class spell_sha_fire_nova_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_fire_nova_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                if (Unit* target = GetHitUnit())
                {
                    if (target->HasAura(SHAMAN_SPELL_FLAME_SHOCK))
                    {
                        caster->CastSpell(target, SHAMAN_SPELL_FIRE_NOVA_TRIGGERED_R1, true);
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_sha_fire_nova_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_fire_nova_SpellScript();
        }
};

// 6474 - Earthbind Totem - Fix Talent:Earthen Power, Earth's Grasp
/// Updated 4.3.4
class spell_sha_earthbind_totem : public SpellScriptLoader
{
    public:
        spell_sha_earthbind_totem() : SpellScriptLoader("spell_sha_earthbind_totem") { }

        class spell_sha_earthbind_totem_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sha_earthbind_totem_AuraScript);

            bool Validate(SpellInfo const* /*spellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(SHAMAN_TOTEM_SPELL_EARTHBIND_TOTEM) || !sSpellMgr->GetSpellInfo(SHAMAN_TOTEM_SPELL_EARTHEN_POWER))
                    return false;
                return true;
            }

            void HandleEffectPeriodic(AuraEffect const* /*aurEff*/)
            {
                if (!GetCaster())
                    return;
                if (Player* owner = GetCaster()->GetCharmerOrOwnerPlayerOrPlayerItself())
                    if (AuraEffect* aur = owner->GetDummyAuraEffect(SPELLFAMILY_SHAMAN, 2289, 0))
                        if (roll_chance_i(aur->GetBaseAmount()))
                            GetTarget()->CastSpell((Unit*)NULL, SHAMAN_TOTEM_SPELL_EARTHEN_POWER, true);
            }

            void Apply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (!GetCaster())
                    return;
                Player* owner = GetCaster()->GetCharmerOrOwnerPlayerOrPlayerItself();
                if (!owner)
                    return;
                // Earth's Grasp
                if (AuraEffect* aurEff = owner->GetAuraEffectOfRankedSpell(SHAMAN_SPELL_EARTH_GRASP, EFFECT_1))
                {
                    if (roll_chance_i(aurEff->GetAmount()))
                        GetCaster()->CastSpell(GetCaster(), EARTHBIND_TOTEM_SPELL_EARTHGRAB, false);
                }
            }

            void Register()
            {
                 OnEffectPeriodic += AuraEffectPeriodicFn(spell_sha_earthbind_totem_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
                 OnEffectApply += AuraEffectApplyFn(spell_sha_earthbind_totem_AuraScript::Apply, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_sha_earthbind_totem_AuraScript();
        }
};

class EarthenPowerTargetSelector
{
    public:
        EarthenPowerTargetSelector() { }

        bool operator() (WorldObject* target)
        {
            if (!target->ToUnit())
                return true;

            if (!target->ToUnit()->HasAuraWithMechanic(1 << MECHANIC_SNARE))
                return true;

            return false;
        }
};

class spell_sha_earthen_power : public SpellScriptLoader
{
    public:
        spell_sha_earthen_power() : SpellScriptLoader("spell_sha_earthen_power") { }

        class spell_sha_earthen_power_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_earthen_power_SpellScript);

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                unitList.remove_if(EarthenPowerTargetSelector());
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_earthen_power_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_earthen_power_SpellScript();
        }
};

/// Updated 4.3.4
class spell_sha_bloodlust : public SpellScriptLoader
{
    public:
        spell_sha_bloodlust() : SpellScriptLoader("spell_sha_bloodlust") { }

        class spell_sha_bloodlust_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_bloodlust_SpellScript);

            bool Validate(SpellInfo const* /*spellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(SHAMAN_SPELL_SATED))
                    return false;
                return true;
            }

            void RemoveInvalidTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if(Trinity::UnitAuraCheck(true, SHAMAN_SPELL_SATED));
                targets.remove_if(Trinity::UnitAuraCheck(true, HUNTER_SPELL_INSANITY));
                targets.remove_if(Trinity::UnitAuraCheck(true, MAGE_SPELL_TEMPORAL_DISPLACEMENT));
            }

            void ApplyDebuff()
            {
                if (Unit* target = GetHitUnit())
                    target->CastSpell(target, SHAMAN_SPELL_SATED, true);
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_bloodlust_SpellScript::RemoveInvalidTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_RAID);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_bloodlust_SpellScript::RemoveInvalidTargets, EFFECT_1, TARGET_UNIT_CASTER_AREA_RAID);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_bloodlust_SpellScript::RemoveInvalidTargets, EFFECT_2, TARGET_UNIT_CASTER_AREA_RAID);
                AfterHit += SpellHitFn(spell_sha_bloodlust_SpellScript::ApplyDebuff);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_bloodlust_SpellScript();
        }
};

/// Updated 4.3.4
class spell_sha_heroism : public SpellScriptLoader
{
    public:
        spell_sha_heroism() : SpellScriptLoader("spell_sha_heroism") { }

        class spell_sha_heroism_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_heroism_SpellScript);

            bool Validate(SpellInfo const* /*spellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(SHAMAN_SPELL_EXHAUSTION))
                    return false;
                return true;
            }

            void RemoveInvalidTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if(Trinity::UnitAuraCheck(true, SHAMAN_SPELL_EXHAUSTION));
                targets.remove_if(Trinity::UnitAuraCheck(true, HUNTER_SPELL_INSANITY));
                targets.remove_if(Trinity::UnitAuraCheck(true, MAGE_SPELL_TEMPORAL_DISPLACEMENT));
            }

            void ApplyDebuff()
            {
                if (Unit* target = GetHitUnit())
                    target->CastSpell(target, SHAMAN_SPELL_EXHAUSTION, true);
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_heroism_SpellScript::RemoveInvalidTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_RAID);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_heroism_SpellScript::RemoveInvalidTargets, EFFECT_1, TARGET_UNIT_CASTER_AREA_RAID);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_heroism_SpellScript::RemoveInvalidTargets, EFFECT_2, TARGET_UNIT_CASTER_AREA_RAID);
                AfterHit += SpellHitFn(spell_sha_heroism_SpellScript::ApplyDebuff);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_heroism_SpellScript();
        }
};

/// Updated 4.3.4
class spell_sha_ancestral_awakening_proc : public SpellScriptLoader
{
    public:
        spell_sha_ancestral_awakening_proc() : SpellScriptLoader("spell_sha_ancestral_awakening_proc") { }

        class spell_sha_ancestral_awakening_proc_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_ancestral_awakening_proc_SpellScript);

            bool Validate(SpellInfo const* /*SpellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(SHAMAN_SPELL_ANCESTRAL_AWAKENING_PROC))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /* effIndex */)
            {
                int32 damage = GetEffectValue();
                if (GetCaster() && GetHitUnit())
                    GetCaster()->CastCustomSpell(GetHitUnit(), SHAMAN_SPELL_ANCESTRAL_AWAKENING_PROC, &damage, NULL, NULL, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_sha_ancestral_awakening_proc_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_ancestral_awakening_proc_SpellScript();
        }
};

/// Updated 4.3.4
class spell_sha_healing_stream_totem : public SpellScriptLoader
{
    public:
        spell_sha_healing_stream_totem() : SpellScriptLoader("spell_sha_healing_stream_totem") { }

        class spell_sha_healing_stream_totem_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_healing_stream_totem_SpellScript);

            bool Validate(SpellInfo const* /*SpellEntry*/)
            {
                return sSpellMgr->GetSpellInfo(SPELL_HEALING_STREAM_TOTEM_HEAL);
            }

            void HandleDummy(SpellEffIndex /* effIndex */)
            {
                int32 damage = GetEffectValue();
                SpellInfo const* triggeringSpell = GetTriggeringSpell();
                if (Unit* target = GetHitUnit())
                    if (Unit* caster = GetCaster())
                    {
                        if (Unit* owner = caster->GetOwner())
                        {
                            if (triggeringSpell)
                                damage = int32(owner->SpellHealingBonusDone(target, triggeringSpell, damage, HEAL));

                            // Soothing Rains
                            if (AuraEffect* dummy = owner->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_SHAMAN, ICON_ID_SOOTHING_RAIN, EFFECT_0))
                                AddPctN(damage, dummy->GetAmount());

                            damage = int32(target->SpellHealingBonusTaken(owner, triggeringSpell, damage, HEAL));
                        }
                        caster->CastCustomSpell(target, SPELL_HEALING_STREAM_TOTEM_HEAL, &damage, 0, 0, true, 0, 0, GetOriginalCaster()->GetGUID());
                    }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_sha_healing_stream_totem_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_healing_stream_totem_SpellScript();
        }
};

// 1064 Chain Heal
/// Updated 4.3.4
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
                if (!GetCaster() || !GetHitUnit())
                    return;

                if (firstHeal)
                {
                    // Check if the target has Riptide
                    if (AuraEffect* aurEff = GetHitUnit()->GetAuraEffect(SPELL_AURA_PERIODIC_HEAL, SPELLFAMILY_SHAMAN, 0, 0, 0x10, GetCaster()->GetGUID()))
                    {
                        riptide = true;
                        amount = aurEff->GetSpellInfo()->Effects[EFFECT_2].CalcValue();
                        
                        // Consume it
                        // if caster has no Item - Shaman T12 Restoration 4P Bonus
                        if (!GetCaster()->HasAura(99195))
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

/// Updated 4.3.4
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

        class spell_sha_flame_shock_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_flame_shock_SpellScript)
            bool Validate(SpellEntry const * spellEntry)
            {
                if (!sSpellStore.LookupEntry(SHAMAN_SPELL_FLAME_SHOCK))
                    return false;

                return true;
            }

            void HandleDamage(SpellEffIndex /*effIndex*/)
            {
                if (!GetCaster() || !GetHitUnit())
                    return;

                if (Unit* minion = ObjectAccessor::GetUnit(*GetCaster(), GetCaster()->m_SummonSlot[SUMMON_SLOT_TOTEM]))
                    if (minion->IsTotem() && minion->GetEntry() == 2523) // Searing Totem
                    {
                       // static_cast<TotemAI*>(minion->GetAI())->SetVictim(GetHitUnit()->GetGUID());
                    }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_sha_flame_shock_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_flame_shock_SpellScript();
        }
};

// 73680 Unleash Elements
class spell_sha_unleash_elements : public SpellScriptLoader
{
public:
    spell_sha_unleash_elements() : SpellScriptLoader("spell_sha_unleash_elements") { }

    class spell_sha_unleash_elements_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_unleash_elements_SpellScript)
        bool Validate(SpellEntry const * spellEntry)
        {
            if (!sSpellStore.LookupEntry(SHAMAN_SPELL_UNLEASH_ELEMENTS))
                return false;

            return true;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            if(!caster)
                return;
            Player* plr = caster->ToPlayer();
            if(!plr)
                return;

            if(!GetExplTargetUnit())
                return;

            Item *weapons[2];
            weapons[0] = plr->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
            weapons[1] = plr->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);
            for(int i = 0; i < 2; i++)
            {
                if(!weapons[i])
                    continue;

                uint32 unleashSpell = 0;
                Unit *target = GetExplTargetUnit();
                bool hostileTarget = !plr->IsFriendlyTo(target);
                bool hostileSpell = true;

                switch (weapons[i]->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT))
                {
                    case 3345: // Earthliving Weapon
                        unleashSpell = 73685; //Unleash Life
                        hostileSpell = false;
                        break;
                    case 5: // Flametongue Weapon
                        unleashSpell = 73683; // Unleash Flame
                        break;
                    case 2: // Frostbrand Weapon
                        unleashSpell = 73682; // Unleash Frost
                        break;
                    case 3021: // Rockbiter Weapon
                        unleashSpell = 73684; // Unleash Earth
                        break;
                    case 283: // Windfury Weapon
                        unleashSpell = 73681; // Unleash Wind
                        break;
                }

                if(hostileSpell && !hostileTarget)
                    return; // don't allow to attack non-hostile targets. TODO: check this before cast

                if(!hostileSpell && hostileTarget)
                    target = plr;   // heal ourselves instead of the enemy

                if(unleashSpell)
                {
                    plr->CastSpell(target, unleashSpell, true);
                }
            }
        }

        void Register()
        {
            OnEffectHit += SpellEffectFn(spell_sha_unleash_elements_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_sha_unleash_elements_SpellScript();
    }
};

// 77829 77830 Ancestral Resolve
class spell_shaman_ancestral_resolve : public SpellScriptLoader
{
public:
    spell_shaman_ancestral_resolve() : SpellScriptLoader("spell_shaman_ancestral_resolve") { }

    class spell_shaman_ancestral_resolve_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_shaman_ancestral_resolve_AuraScript);
        uint32 absorbPct;
        bool Validate(SpellEntry const * /*spellEntry*/)
        {
            if(!sSpellStore.LookupEntry(77829))
                return false;
            if(!sSpellStore.LookupEntry(77830))
                return false;
            return true;
        }

        bool Load()
        {
            absorbPct = GetSpellInfo()->Effects[EFFECT_0].CalcValue();
            return GetUnitOwner()->ToPlayer();
        }

        void CalculateAmount(AuraEffect const * /*aurEff*/, int32 & amount, bool & canBeRecalculated)
        {
            // Set absorbtion amount to unlimited
            amount = -1;
        }

        void Absorb(AuraEffect * aurEff, DamageInfo & dmgInfo, uint32 & absorbAmount)
        {
            Unit * target = GetTarget();
            if (!target->HasUnitState(UNIT_STATE_CASTING))
                return;
            absorbAmount = absorbPct*dmgInfo.GetDamage()/100;
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_shaman_ancestral_resolve_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            OnEffectAbsorb += AuraEffectAbsorbFn(spell_shaman_ancestral_resolve_AuraScript::Absorb, EFFECT_0);
        }
    };

    AuraScript *GetAuraScript() const
    {
        return new spell_shaman_ancestral_resolve_AuraScript();
    }
};

// 98020 Spirit Link
class spell_sha_spirit_link : public SpellScriptLoader
{
    public:
        spell_sha_spirit_link() : SpellScriptLoader("spell_sha_spirit_link") { }

        class spell_sha_spirit_link_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_spirit_link_SpellScript)
            bool Validate(SpellEntry const * spellEntry)
            {
                if (!sSpellStore.LookupEntry(SHAMAN_SPELL_SPIRIT_LINK))
                    return false;

                if (!sSpellStore.LookupEntry(SHAMAN_SPELL_SPIRIT_LINK_DAMAGE))
                    return false;

                m_healthPct = 100.0f;

                return true;
            }

            void CheckTargets(std::list<WorldObject*>& targets)
            {
                float healthPct = 0;

                if (targets.size() == 0)
                    return;
                
                for (std::list<WorldObject*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    healthPct += (*itr)->ToUnit()->GetHealthPct();

                if (healthPct > 0.0f)
                    m_healthPct = healthPct / targets.size();
            }
            

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (!GetCaster() || !GetHitUnit())
                    return;

                int32 dmg = 0;

                float curPct = GetHitUnit()->GetHealthPct();

                if (curPct < m_healthPct)
                {
                    dmg = CalculatePctN(GetHitUnit()->GetMaxHealth(), m_healthPct) - GetHitUnit()->GetHealth(); 
                    GetCaster()->CastCustomSpell(GetHitUnit(), SHAMAN_SPELL_SPIRIT_LINK_DAMAGE, 0, &dmg, 0, true);
                }
                else if (curPct > m_healthPct)
                {
                    dmg = GetHitUnit()->GetHealth() - CalculatePctN(GetHitUnit()->GetMaxHealth(), m_healthPct);
                    GetCaster()->CastCustomSpell(GetHitUnit(), SHAMAN_SPELL_SPIRIT_LINK_DAMAGE, &dmg, 0, 0, true);
                }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_spirit_link_SpellScript::CheckTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_RAID);
                OnEffectHitTarget += SpellEffectFn(spell_sha_spirit_link_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }

        private:
            float m_healthPct;
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_spirit_link_SpellScript();
        }
};

// 88766 Fulmination handled in 8042 Earth Shock
class spell_sha_fulmination : public SpellScriptLoader
{
    public:
        spell_sha_fulmination() : SpellScriptLoader("spell_sha_fulmination") { }

        class spell_sha_fulmination_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_fulmination_SpellScript)

            bool Validate(SpellEntry const * /*spellEntry*/)
            {
                if (!sSpellStore.LookupEntry(SHAMAN_SPELL_FULMINATION))
                    return false;

                if (!sSpellStore.LookupEntry(SHAMAN_SPELL_FULMINATION_TRIGGERED))
                    return false;

                if (!sSpellStore.LookupEntry(SHAMAN_SPELL_FULMINATION_INFO))
                    return false;

                return true;
            }

            void HandleFulmination(SpellEffIndex effIndex)
            {
                // make caster cast a spell on a unit target of effect

                Unit *target = GetHitUnit();

                Unit *caster = GetCaster();

                if(!target || !caster)
                    return;

                AuraEffect *fulminationAura = caster->GetDummyAuraEffect(SPELLFAMILY_SHAMAN, 2010, 0);

                if (!fulminationAura)
                    return;

                Aura * lightningShield = caster->GetAura(324);

                if(!lightningShield)
                    return;

                uint8 lsCharges = lightningShield->GetCharges();

                if(lsCharges <= 3)
                    return;
                uint8 usedCharges = lsCharges - 3;

                caster->RemoveAurasDueToSpell(95774); // remove visual effect

                SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SHAMAN_SPELL_LIGHTNING_SHIELD_PROC);
                int32 basePoints = caster->CalculateSpellDamage(target, spellInfo, 0);
                uint32 damage = usedCharges * caster->SpellDamageBonusDone(target, spellInfo, basePoints, SPELL_DIRECT_DAMAGE);
                caster->CastCustomSpell(SHAMAN_SPELL_FULMINATION_TRIGGERED, SPELLVALUE_BASE_POINT0, damage, target, true, NULL, fulminationAura);
                lightningShield->SetCharges(lsCharges - usedCharges);
            }

            // register functions used in spell script - names of these functions do not matter
            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_sha_fulmination_SpellScript::HandleFulmination, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_sha_fulmination_SpellScript();
        }
};

// 77746 - Totemic Wrath
class spell_sha_totemic_wrath : public SpellScriptLoader
{
    public:
        spell_sha_totemic_wrath() : SpellScriptLoader("spell_sha_totemic_wrath") { }

        class spell_sha_totemic_wrath_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_sha_totemic_wrath_AuraScript);

            bool Validate(SpellEntry const * /*spellEntry*/)
            {
                if (!sSpellStore.LookupEntry(SHAMAN_TOTEM_SPELL_TOTEMIC_WRATH))
                    return false;

                if (!sSpellStore.LookupEntry(SHAMAN_TOTEM_SPELL_TOTEMIC_WRATH_AURA))
                    return false;

                return true;
            }

            void HandleEffectApply(AuraEffect const * aurEff, AuraEffectHandleModes /*mode*/)
            {
                Unit* target = GetTarget();

                if(target->ToPlayer())
                    return; // just apply as dummy

                // applied by a totem - cast the real aura if owner has the talent
                if (Unit *caster = aurEff->GetBase()->GetCaster())
                    if (caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_GENERIC, 2019, 0))
                        target->CastSpell(target, SHAMAN_TOTEM_SPELL_TOTEMIC_WRATH_AURA, true, NULL, aurEff);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_sha_totemic_wrath_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript *GetAuraScript() const
        {
            return new spell_sha_totemic_wrath_AuraScript();
        }
};

class spell_sha_thunderstorm : public SpellScriptLoader
{
    public:
        spell_sha_thunderstorm() : SpellScriptLoader("spell_sha_thunderstorm") { }

        class spell_sha_thunderstorm_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_sha_thunderstorm_SpellScript);

            void HandleScript(SpellEffIndex /*effIndex*/)
            {
                if (!GetCaster() || !GetHitUnit())
                    return;

                GetCaster()->CastSpell(GetHitUnit(), SHAMAN_SPELL_THUNDERSTORM_SLOW, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_sha_thunderstorm_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_sha_thunderstorm_SpellScript();
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

void AddSC_shaman_spell_scripts()
{
    new spell_sha_fire_nova();
    new spell_sha_earthbind_totem();
    new spell_sha_earthen_power();
    new spell_sha_bloodlust();
    new spell_sha_heroism();
    new spell_sha_ancestral_awakening_proc();
    new spell_sha_healing_stream_totem();
    new spell_sha_chain_heal();
    new spell_sha_flame_shock();
    new spell_sha_unleash_elements();
    new spell_shaman_ancestral_resolve();
    new spell_sha_spirit_link();
    new spell_sha_fulmination();
    new spell_sha_totemic_wrath();
    new spell_sha_thunderstorm();
    new spell_raid_haste();
    new spell_sha_earthquake();
    new spell_sha_mana_tide_totem();
}
