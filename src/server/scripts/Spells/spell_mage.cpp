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
 * Scripts for spells with SPELLFAMILY_MAGE and SPELLFAMILY_GENERIC spells used by mage players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_mage_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

enum MageSpells
{
    SPELL_MAGE_COLD_SNAP                         = 11958,
    SPELL_MAGE_SQUIRREL_FORM                     = 32813,
    SPELL_MAGE_GIRAFFE_FORM                      = 32816,
    SPELL_MAGE_SERPENT_FORM                      = 32817,
    SPELL_MAGE_DRAGONHAWK_FORM                   = 32818,
    SPELL_MAGE_WORGEN_FORM                       = 32819,
    SPELL_MAGE_SHEEP_FORM                        = 32820,
    SPELL_MAGE_GLYPH_OF_ETERNAL_WATER            = 70937,
    SPELL_MAGE_SUMMON_WATER_ELEMENTAL_PERMANENT  = 70908,
    SPELL_MAGE_SUMMON_WATER_ELEMENTAL_TEMPORARY  = 70907,
    SPELL_MAGE_CAUTERIZE_DAMAGE                  = 87023,
    SPELL_MAGE_CHILLED_R1                        = 12484,
    SPELL_MAGE_CHILLED_R2                        = 12485,
};

// Cauterize talent
class spell_mage_cauterize : public SpellScriptLoader
{
public:
    spell_mage_cauterize() : SpellScriptLoader("spell_mage_cauterize") { }

    class spell_mage_cauterize_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_mage_cauterize_AuraScript);

        int32 absorbChance;
        
        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_CAUTERIZE_DAMAGE))
                return false;

            return true;
        }

        bool Load()
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return false;

            absorbChance = GetSpellInfo()->Effects[0].BasePoints;
            return true;
        }

        void CalculateAmount(AuraEffect const * /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
        {
            // Set absorbtion amount to unlimited
            amount = -1;
        }

        void Absorb(AuraEffect* aurEff, DamageInfo & dmgInfo, uint32 & absorbAmount)
        {
            Unit * caster = GetCaster();

            if (!caster)
                return;
            
            int32 remainingHealth = caster->GetHealth() - dmgInfo.GetDamage();
            int32 cauterizeHeal = caster->CountPctFromMaxHealth(40);
            
            if (caster->ToPlayer()->HasSpellCooldown(SPELL_MAGE_CAUTERIZE_DAMAGE))
                return;

            if (!roll_chance_i(absorbChance))
                return;

            if (remainingHealth <= 0)
            {
                absorbAmount = dmgInfo.GetDamage();
                caster->CastCustomSpell(caster,SPELL_MAGE_CAUTERIZE_DAMAGE,NULL,&cauterizeHeal,NULL, true, NULL, aurEff);
                caster->ToPlayer()->AddSpellCooldown(SPELL_MAGE_CAUTERIZE_DAMAGE, 0, time(NULL) + 60);
            }
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_cauterize_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            OnEffectAbsorb += AuraEffectAbsorbFn(spell_mage_cauterize_AuraScript::Absorb, EFFECT_0);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_mage_cauterize_AuraScript();
    }
};

class spell_mage_cold_snap : public SpellScriptLoader
{
    public:
        spell_mage_cold_snap() : SpellScriptLoader("spell_mage_cold_snap") { }

        class spell_mage_cold_snap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_mage_cold_snap_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {

                Player* caster = GetCaster()->ToPlayer();
                // immediately finishes the cooldown on Frost spells
                const SpellCooldowns& cm = caster->GetSpellCooldownMap();
                for (SpellCooldowns::const_iterator itr = cm.begin(); itr != cm.end();)
                {
                    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(itr->first);

                    if (spellInfo->SpellFamilyName == SPELLFAMILY_MAGE &&
                        (spellInfo->GetSchoolMask() & SPELL_SCHOOL_MASK_FROST) &&
                        spellInfo->Id != SPELL_MAGE_COLD_SNAP && spellInfo->GetRecoveryTime() > 0)
                    {
                        caster->RemoveSpellCooldown((itr++)->first, true);
                    }
                    else
                        ++itr;
                }
            }

            void Register()
            {
                // add dummy effect spell handler to Cold Snap
                OnEffectHit += SpellEffectFn(spell_mage_cold_snap_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_mage_cold_snap_SpellScript();
        }
};

// Frost Warding
class spell_mage_frost_warding_trigger : public SpellScriptLoader
{
    public:
        spell_mage_frost_warding_trigger() : SpellScriptLoader("spell_mage_frost_warding_trigger") { }

        class spell_mage_frost_warding_trigger_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mage_frost_warding_trigger_AuraScript);

            enum Spells
            {
                SPELL_MAGE_FROST_WARDING_TRIGGERED = 57776,
                SPELL_MAGE_FROST_WARDING_R1 = 28332,
            };

            bool Validate(SpellInfo const* /*spellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_FROST_WARDING_TRIGGERED) || !sSpellMgr->GetSpellInfo(SPELL_MAGE_FROST_WARDING_R1))
                    return false;
                return true;
            }

            void Absorb(AuraEffect* aurEff, DamageInfo & dmgInfo, uint32 & absorbAmount)
            {
                Unit* target = GetTarget();
                if (AuraEffect* talentAurEff = target->GetAuraEffectOfRankedSpell(SPELL_MAGE_FROST_WARDING_R1, EFFECT_0))
                {
                    int32 chance = talentAurEff->GetSpellInfo()->Effects[EFFECT_1].CalcValue();

                    if (roll_chance_i(chance))
                    {
                        int32 bp = dmgInfo.GetDamage();
                        dmgInfo.AbsorbDamage(bp);
                        target->CastCustomSpell(target, SPELL_MAGE_FROST_WARDING_TRIGGERED, &bp, NULL, NULL, true, NULL, aurEff);
                        absorbAmount = 0;
                        PreventDefaultAction();
                    }
                }
            }

            void Register()
            {
                 OnEffectAbsorb += AuraEffectAbsorbFn(spell_mage_frost_warding_trigger_AuraScript::Absorb, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_frost_warding_trigger_AuraScript();
        }
};

// Incanter's Absorption
class spell_mage_incanters_absorbtion_manashield: public SpellScriptLoader 
{
    public:
    spell_mage_incanters_absorbtion_manashield() : SpellScriptLoader("spell_mage_incanters_absorbtion_manashield") { }

    class spell_mage_incanters_absorbtion_manashield_AuraScript: public AuraScript 
	{
        PrepareAuraScript(spell_mage_incanters_absorbtion_manashield_AuraScript);

        enum Spells 
        {
            SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED = 44413,
            SPELL_MAGE_INCANTERS_ABSORBTION_R1 = 44394,
            SPELL_MAGE_INCANTERS_ABSORBTION_R2 = 44395,
        };

        bool Load ()
        {
            return GetCaster()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_GENERIC, 2941, 0);
        }

        bool Validate(SpellEntry const * /*spellEntry*/) 
        {
            return sSpellStore.LookupEntry(SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED) && (sSpellStore.LookupEntry(SPELL_MAGE_INCANTERS_ABSORBTION_R1) || sSpellStore.LookupEntry(SPELL_MAGE_INCANTERS_ABSORBTION_R2));
        }

        void HandleAfterEffectAbsorb(AuraEffect * aurEff, DamageInfo & dmgInfo, uint32 & absorbAmount) 
        {
            Unit * target = GetTarget();

            int32 bp = CalculatePctN(absorbAmount,target->HasAura(44394) ? 10 : 20);
            if (target->HasAura(SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED))
                target->GetAura(SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED)->GetEffect(EFFECT_0)->ChangeAmount(target->GetAura(SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED)->GetEffect(EFFECT_0)->GetAmount() + bp);
            else
                target->CastCustomSpell(target,SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED, &bp, NULL, NULL, true, NULL, aurEff);
        }

        void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_ENEMY_SPELL)
                GetCaster()->CastSpell(GetCaster(),86261,true);
        }

        void Register() {
            AfterEffectManaShield += AuraEffectManaShieldFn(spell_mage_incanters_absorbtion_manashield_AuraScript::HandleAfterEffectAbsorb, EFFECT_0);
            OnEffectRemove += AuraEffectRemoveFn(spell_mage_incanters_absorbtion_manashield_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MANA_SHIELD, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript *GetAuraScript() const {
        return new spell_mage_incanters_absorbtion_manashield_AuraScript();
    }
};

// Incanter's Absorption
class spell_mage_incanters_absorbtion_absorb: public SpellScriptLoader 
{
public:
    spell_mage_incanters_absorbtion_absorb() : SpellScriptLoader("spell_mage_incanters_absorbtion_absorb") { }

    class spell_mage_incanters_absorbtion_absorb_AuraScript: public AuraScript { PrepareAuraScript(spell_mage_incanters_absorbtion_absorb_AuraScript ) ;

        enum Spells 
        {
            SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED = 44413,
            SPELL_MAGE_INCANTERS_ABSORBTION_R1 = 44394,
            SPELL_MAGE_INCANTERS_ABSORBTION_R2 = 44395,
        };

        bool Validate(SpellEntry const * /*spellEntry*/) 
        {
            return sSpellStore.LookupEntry(SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED) && (sSpellStore.LookupEntry(SPELL_MAGE_INCANTERS_ABSORBTION_R1) || sSpellStore.LookupEntry(SPELL_MAGE_INCANTERS_ABSORBTION_R2));
        }

        bool Load ()
        {
            return GetCaster()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_GENERIC, 2941, 0);
        }

        void HandleAfterEffectAbsorb(AuraEffect * aurEff, DamageInfo & dmgInfo, uint32 & absorbAmount) 
        {
            Unit * target = GetTarget();

            int32 bp = CalculatePctN(absorbAmount,target->HasAura(44394) ? 10 : 20);
            if (target->HasAura(SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED))
                target->GetAura(SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED)->GetEffect(EFFECT_0)->ChangeAmount(target->GetAura(SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED)->GetEffect(EFFECT_0)->GetAmount() + bp);
            else
                target->CastCustomSpell(target,SPELL_MAGE_INCANTERS_ABSORBTION_TRIGGERED, &bp, NULL, NULL, true, NULL, aurEff);
        }

        void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_ENEMY_SPELL)
                GetCaster()->CastSpell(GetCaster(),86261,true);
        }

        void Register() {
            AfterEffectAbsorb += AuraEffectAbsorbFn(spell_mage_incanters_absorbtion_absorb_AuraScript::HandleAfterEffectAbsorb, EFFECT_0);
            OnEffectRemove += AuraEffectRemoveFn(spell_mage_incanters_absorbtion_absorb_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript *GetAuraScript() const {
        return new spell_mage_incanters_absorbtion_absorb_AuraScript();
    }
};

class spell_mage_living_bomb : public SpellScriptLoader
{
    public:
        spell_mage_living_bomb() : SpellScriptLoader("spell_mage_living_bomb") { }

        class spell_mage_living_bomb_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mage_living_bomb_AuraScript);

            bool Validate(SpellInfo const* spell)
            {
                if (!sSpellMgr->GetSpellInfo(uint32(spell->Effects[EFFECT_1].CalcValue())))
                    return false;
                return true;
            }

            void AfterRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
                if (removeMode != AURA_REMOVE_BY_ENEMY_SPELL && removeMode != AURA_REMOVE_BY_EXPIRE)
                    return;

                if (Unit* caster = GetCaster())
                    caster->CastSpell(GetTarget(), uint32(aurEff->GetAmount()), true, NULL, aurEff);
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_mage_living_bomb_AuraScript::AfterRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mage_living_bomb_AuraScript();
        }
};

// Ice Shards
class spell_mage_blizzard : public SpellScriptLoader
{
   public:
       spell_mage_blizzard() : SpellScriptLoader("spell_mage_blizzard") { }

       class spell_mage_blizzard_SpellScript : public SpellScript
       {
           PrepareSpellScript(spell_mage_blizzard_SpellScript);

           bool Validate(SpellInfo const* /*spellEntry*/)
           {
               if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_CHILLED_R1))
                   return false;
               if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_CHILLED_R2))
                   return false;
               return true;
           }

           void AddChillEffect(SpellEffIndex /*effIndex*/)
           {
               Unit* caster = GetCaster();
               if (Unit* unitTarget = GetHitUnit())
               {
                   if (caster->IsScriptOverriden(GetSpellInfo(), 836))
                       caster->CastSpell(unitTarget, SPELL_MAGE_CHILLED_R1, true);
                   else if (caster->IsScriptOverriden(GetSpellInfo(), 988))
                       caster->CastSpell(unitTarget, SPELL_MAGE_CHILLED_R2, true);
               }
           }

           void Register()
           {
               OnEffectHitTarget += SpellEffectFn(spell_mage_blizzard_SpellScript::AddChillEffect, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
           }
       };

       SpellScript *GetSpellScript() const
       {
           return new spell_mage_blizzard_SpellScript();
       }
};

void AddSC_mage_spell_scripts()
{
    new spell_mage_cauterize();
    new spell_mage_cold_snap();
    new spell_mage_frost_warding_trigger();
    new spell_mage_incanters_absorbtion_manashield();
    new spell_mage_incanters_absorbtion_absorb();
    new spell_mage_living_bomb();
    new spell_mage_blizzard();
}