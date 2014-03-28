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
 * Scripts for spells with SPELLFAMILY_DRUID and SPELLFAMILY_GENERIC spells used by druid players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_dru_".
 */

#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Containers.h"

enum DruidSpells
{
    SPELL_DRUID_INCREASED_MOONFIRE_DURATION   = 38414,
    SPELL_DRUID_NATURES_SPLENDOR              = 57865,
    SPELL_DRUID_LIFEBLOOM_FINAL_HEAL          = 33778,
    SPELL_DRUID_LIFEBLOOM_ENERGIZE            = 64372,
    SPELL_DRUID_SURVIVAL_INSTINCTS            = 50322,
    SPELL_DRUID_SAVAGE_ROAR                   = 62071,
    SPELL_DRUID_ITEM_T8_BALANCE_RELIC         = 64950,
    SPELL_DRUID_TALENT_FUNGAL_GROWTH_1        = 78788,
    SPELL_DRUID_TALENT_FUNGAL_GROWTH_2        = 78789,
    SPELL_DRUID_FUNGAL_GROWTH_1               = 81291,
    SPELL_DRUID_FUNGAL_GROWTH_2               = 81283,
    SPELL_DRUID_WILD_MUSHROOM_SUICIDE         = 92853,
    SPELL_DRUID_WILD_MUSHROOM_DAMAGE          = 78777,
    DRUID_FAERIE_FIRE                         = 91565
};

enum DruidCreatures
{
    DRUID_NPC_FUNGAL_GROWTH_1                 = 43497,
    DRUID_NPC_FUNGAL_GROWTH_2                 = 43484,
    DRUID_NPC_WILD_MUSHROOM                   = 47649
};

// 54846 Glyph of Starfire
class spell_dru_glyph_of_starfire : public SpellScriptLoader
{
    public:
        spell_dru_glyph_of_starfire() : SpellScriptLoader("spell_dru_glyph_of_starfire") { }

        class spell_dru_glyph_of_starfire_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_glyph_of_starfire_SpellScript);

            bool Validate(SpellInfo const* /*spellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DRUID_INCREASED_MOONFIRE_DURATION))
                    return false;
                return true;
            }

            void HandleScriptEffect(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                if (Unit* unitTarget = GetHitUnit())
                    if (AuraEffect const* aurEff = unitTarget->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_DRUID, 0x00000002, 0, 0, caster->GetGUID()))
                    {
                        Aura* aura = aurEff->GetBase();

                        uint32 countMin = aura->GetMaxDuration();
                        uint32 countMax = aura->GetSpellInfo()->GetMaxDuration() + 9000;
                        if (caster->HasAura(SPELL_DRUID_INCREASED_MOONFIRE_DURATION))
                            countMax += 3000;

                        if (countMin < countMax)
                        {
                            aura->SetDuration(uint32(aura->GetDuration() + 3000));
                            aura->SetMaxDuration(countMin + 3000);
                        }
                    }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_dru_glyph_of_starfire_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_glyph_of_starfire_SpellScript();
        }
};

// 62606 - Savage Defense
class spell_dru_savage_defense : public SpellScriptLoader
{
    public:
        spell_dru_savage_defense() : SpellScriptLoader("spell_dru_savage_defense") { }

        class spell_dru_savage_defense_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_savage_defense_AuraScript);

            uint32 absorbPct;

            bool Load()
            {
                absorbPct = GetSpellInfo()->Effects[EFFECT_0].CalcValue(GetCaster());
                return true;
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                amount = GetCaster()->CountPctFromMaxHealth(absorbPct);
            }

            void Absorb(AuraEffect* aurEff, DamageInfo & /*dmgInfo*/, uint32 & absorbAmount)
            {
                absorbAmount = uint32(CalculatePct(GetTarget()->GetTotalAttackPowerValue(BASE_ATTACK), absorbPct));
                aurEff->SetAmount(0);
            }

            void Register()
            {
                 DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dru_savage_defense_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                 OnEffectAbsorb += AuraEffectAbsorbFn(spell_dru_savage_defense_AuraScript::Absorb, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_savage_defense_AuraScript();
        }
};

class spell_dru_t10_restoration_4p_bonus : public SpellScriptLoader
{
    public:
        spell_dru_t10_restoration_4p_bonus() : SpellScriptLoader("spell_dru_t10_restoration_4p_bonus") { }

        class spell_dru_t10_restoration_4p_bonus_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_t10_restoration_4p_bonus_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                if (!GetCaster()->ToPlayer()->GetGroup())
                {
                    targets.clear();
                    targets.push_back(GetCaster());
                }
                else
                {
                    targets.remove(GetExplTargetUnit());
                    std::list<Unit*> tempTargets;
                    for (std::list<WorldObject*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                        if ((*itr)->GetTypeId() == TYPEID_PLAYER && GetCaster()->IsInRaidWith((*itr)->ToUnit()))
                            tempTargets.push_back((*itr)->ToUnit());

                    if (tempTargets.empty())
                    {
                        targets.clear();
                        FinishCast(SPELL_FAILED_DONT_REPORT);
                        return;
                    }

                    Unit* target = Trinity::Containers::SelectRandomContainerElement(tempTargets);
                    targets.clear();
                    targets.push_back(target);
                }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dru_t10_restoration_4p_bonus_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_t10_restoration_4p_bonus_SpellScript();
        }
};

// 40121 - Swift Flight Form (Passive)
class spell_dru_swift_flight_passive : public SpellScriptLoader
{
    public:
        spell_dru_swift_flight_passive() : SpellScriptLoader("spell_dru_swift_flight_passive") { }

        class spell_dru_swift_flight_passive_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_swift_flight_passive_AuraScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                if (Player* caster = GetCaster()->ToPlayer())
                    if (caster->GetSkillValue(SKILL_RIDING) >= 375)
                        amount = 310;
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dru_swift_flight_passive_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_MOD_INCREASE_VEHICLE_FLIGHT_SPEED);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_swift_flight_passive_AuraScript();
        }
};

class spell_dru_starfall_dummy : public SpellScriptLoader
{
    public:
        spell_dru_starfall_dummy() : SpellScriptLoader("spell_dru_starfall_dummy") { }

        class spell_dru_starfall_dummy_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_starfall_dummy_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                Trinity::Containers::RandomResizeList(targets, 2);
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                // Shapeshifting into an animal form or mounting cancels the effect
                if (caster->GetCreatureType() == CREATURE_TYPE_BEAST || caster->IsMounted())
                {
                    if (SpellInfo const* spellInfo = GetTriggeringSpell())
                        caster->RemoveAurasDueToSpell(spellInfo->Id);
                    return;
                }

                // Any effect which causes you to lose control of your character will supress the starfall effect.
                if (caster->HasUnitState(UNIT_STATE_CONTROLLED))
                    return;

                caster->CastSpell(GetHitUnit(), uint32(GetEffectValue()), true);
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dru_starfall_dummy_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
                OnEffectHitTarget += SpellEffectFn(spell_dru_starfall_dummy_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_starfall_dummy_SpellScript();
        }
};

class spell_dru_lifebloom : public SpellScriptLoader
{
    public:
        spell_dru_lifebloom() : SpellScriptLoader("spell_dru_lifebloom") { }

        class spell_dru_lifebloom_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_lifebloom_AuraScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DRUID_LIFEBLOOM_FINAL_HEAL))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_DRUID_LIFEBLOOM_ENERGIZE))
                    return false;
                return true;
            }

            void AfterRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                // Final heal only on duration end
                if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_EXPIRE)
                    return;

                // final heal
                int32 stack = GetStackAmount();
                int32 healAmount = aurEff->GetAmount();
                if (Unit* caster = GetCaster())
                {
                    healAmount = caster->SpellHealingBonusDone(GetTarget(), GetSpellInfo(), healAmount, HEAL, stack);
                    healAmount = GetTarget()->SpellHealingBonusTaken(caster, GetSpellInfo(), healAmount, HEAL, stack);

                    GetTarget()->CastCustomSpell(GetTarget(), SPELL_DRUID_LIFEBLOOM_FINAL_HEAL, &healAmount, NULL, NULL, true, NULL, aurEff, GetCasterGUID());

                    // restore mana
                    int32 returnMana = CalculatePct(caster->GetCreateMana(), GetSpellInfo()->ManaCostPercentage) * stack / 2;
                    caster->CastCustomSpell(caster, SPELL_DRUID_LIFEBLOOM_ENERGIZE, &returnMana, NULL, NULL, true, NULL, aurEff, GetCasterGUID());
                    return;
                }

                GetTarget()->CastCustomSpell(GetTarget(), SPELL_DRUID_LIFEBLOOM_FINAL_HEAL, &healAmount, NULL, NULL, true, NULL, aurEff, GetCasterGUID());
            }

            void HandleDispel(DispelInfo* dispelInfo)
            {
                if (Unit* target = GetUnitOwner())
                {
                    if (AuraEffect const* aurEff = GetEffect(EFFECT_1))
                    {
                        // final heal
                        int32 healAmount = aurEff->GetAmount();
                        if (Unit* caster = GetCaster())
                        {
                            healAmount = caster->SpellHealingBonusDone(target, GetSpellInfo(), healAmount, HEAL, dispelInfo->GetRemovedCharges());
                            healAmount = target->SpellHealingBonusTaken(caster, GetSpellInfo(), healAmount, HEAL, dispelInfo->GetRemovedCharges());
                            target->CastCustomSpell(target, SPELL_DRUID_LIFEBLOOM_FINAL_HEAL, &healAmount, NULL, NULL, true, NULL, NULL, GetCasterGUID());

                            // restore mana
                            int32 returnMana = CalculatePct(caster->GetCreateMana(), GetSpellInfo()->ManaCostPercentage) * dispelInfo->GetRemovedCharges() / 2;
                            caster->CastCustomSpell(caster, SPELL_DRUID_LIFEBLOOM_ENERGIZE, &returnMana, NULL, NULL, true, NULL, NULL, GetCasterGUID());
                            return;
                        }

                        target->CastCustomSpell(target, SPELL_DRUID_LIFEBLOOM_FINAL_HEAL, &healAmount, NULL, NULL, true, NULL, NULL, GetCasterGUID());
                    }
                }
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_dru_lifebloom_AuraScript::AfterRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                AfterDispel += AuraDispelFn(spell_dru_lifebloom_AuraScript::HandleDispel);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_lifebloom_AuraScript();
        }
};

class spell_dru_predatory_strikes : public SpellScriptLoader
{
    public:
        spell_dru_predatory_strikes() : SpellScriptLoader("spell_dru_predatory_strikes") { }

        class spell_dru_predatory_strikes_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_predatory_strikes_AuraScript);

            void UpdateAmount(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* target = GetTarget()->ToPlayer())
                    target->UpdateAttackPowerAndDamage();
            }

            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_dru_predatory_strikes_AuraScript::UpdateAmount, EFFECT_ALL, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_CHANGE_AMOUNT_MASK);
                AfterEffectRemove += AuraEffectRemoveFn(spell_dru_predatory_strikes_AuraScript::UpdateAmount, EFFECT_ALL, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_CHANGE_AMOUNT_MASK);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_predatory_strikes_AuraScript();
        }
};

class spell_dru_savage_roar : public SpellScriptLoader
{
    public:
        spell_dru_savage_roar() : SpellScriptLoader("spell_dru_savage_roar") { }

        class spell_dru_savage_roar_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_savage_roar_SpellScript);

            SpellCastResult CheckCast()
            {
                Unit* caster = GetCaster();
                if (caster->GetShapeshiftForm() != FORM_CAT)
                    return SPELL_FAILED_ONLY_SHAPESHIFT;

                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_dru_savage_roar_SpellScript::CheckCast);
            }
        };

        class spell_dru_savage_roar_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_savage_roar_AuraScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DRUID_SAVAGE_ROAR))
                    return false;
                return true;
            }

            void AfterApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                Unit* target = GetTarget();
                target->CastSpell(target, SPELL_DRUID_SAVAGE_ROAR, true, NULL, aurEff, GetCasterGUID());
            }

            void AfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                GetTarget()->RemoveAurasDueToSpell(SPELL_DRUID_SAVAGE_ROAR);
            }

            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_dru_savage_roar_AuraScript::AfterApply, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                AfterEffectRemove += AuraEffectRemoveFn(spell_dru_savage_roar_AuraScript::AfterRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_savage_roar_SpellScript();
        }

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_savage_roar_AuraScript();
        }
};

class spell_dru_survival_instincts : public SpellScriptLoader
{
    public:
        spell_dru_survival_instincts() : SpellScriptLoader("spell_dru_survival_instincts") { }

        class spell_dru_survival_instincts_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_survival_instincts_SpellScript);

            SpellCastResult CheckCast()
            {
                Unit* caster = GetCaster();
                if (!caster->IsInFeralForm())
                    return SPELL_FAILED_ONLY_SHAPESHIFT;

                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_dru_survival_instincts_SpellScript::CheckCast);
            }
        };

        class spell_dru_survival_instincts_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_survival_instincts_AuraScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_DRUID_SURVIVAL_INSTINCTS))
                    return false;
                return true;
            }

            void AfterApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                Unit* target = GetTarget();
                int32 bp0 = target->CountPctFromMaxHealth(aurEff->GetAmount());
                target->CastCustomSpell(target, SPELL_DRUID_SURVIVAL_INSTINCTS, &bp0, NULL, NULL, true);
            }

            void AfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                GetTarget()->RemoveAurasDueToSpell(SPELL_DRUID_SURVIVAL_INSTINCTS);
            }

            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_dru_survival_instincts_AuraScript::AfterApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_CHANGE_AMOUNT_MASK);
                AfterEffectRemove += AuraEffectRemoveFn(spell_dru_survival_instincts_AuraScript::AfterRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_CHANGE_AMOUNT_MASK);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_survival_instincts_SpellScript();
        }

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_survival_instincts_AuraScript();
        }
};

// Stampede
class spell_dru_stampede : public SpellScriptLoader
{
    public:
        spell_dru_stampede() : SpellScriptLoader("spell_dru_stampede") { }

        class spell_dru_stampede_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_stampede_SpellScript);

            bool Load()
            {
                return GetCaster()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_DRUID, 3930, 0);
            }

            void HandleAfterCast()
            {
                if (GetSpellInfo()->Id == 16979)
                {
                    if (GetCaster()->HasAura(78892))
                        GetCaster()->CastSpell(GetCaster(), 81016, true);
                    else if (GetCaster()->HasAura(78893))
                        GetCaster()->CastSpell(GetCaster(), 81017, true);
                }
                else if (GetSpellInfo()->Id == 49376)
                {
                    if (GetCaster()->HasAura(78892))
                        GetCaster()->CastSpell(GetCaster(), 81021, true);
                    else if (GetCaster()->HasAura(78893))
                        GetCaster()->CastSpell(GetCaster(), 81022, true);
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_dru_stampede_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_stampede_SpellScript();
        }
};

class spell_dru_insect_swarm : public SpellScriptLoader
{
    public:
        spell_dru_insect_swarm() : SpellScriptLoader("spell_dru_insect_swarm") { }

        class spell_dru_insect_swarm_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_insect_swarm_AuraScript);

            void CalculateAmount(AuraEffect const* aurEff, int32 & amount, bool & /*canBeRecalculated*/)
            {
                if (Unit* caster = GetCaster())
                    if (AuraEffect const* relicAurEff = caster->GetAuraEffect(SPELL_DRUID_ITEM_T8_BALANCE_RELIC, EFFECT_0))
                        amount += relicAurEff->GetAmount() / aurEff->GetTotalTicks();
            }

            void Register()
            {
                 DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dru_insect_swarm_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_insect_swarm_AuraScript();
        }
};

// Wild mushroom, 88747
class spell_druid_wild_mushroom : public SpellScriptLoader
{
    public:
        spell_druid_wild_mushroom() : SpellScriptLoader("spell_druid_wild_mushroom") { }

        class spell_druid_wild_mushroom_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_druid_wild_mushroom_SpellScript)

            void HandleSummon(SpellEffIndex effIndex)
            {
                if (Player* player = GetCaster()->ToPlayer())
                {
                    PreventHitDefaultEffect(effIndex);
                    SpellInfo const* spell = GetSpellInfo();

                    std::list<Creature*> list;
                    player->GetCreatureListWithEntryInGrid(list, DRUID_NPC_WILD_MUSHROOM, 500.0f);
                    for (std::list<Creature*>::iterator i = list.begin(); i != list.end(); ++i)
                    {
                        if ((*i)->IsSummon() && (*i)->GetCharmerOrOwner() == player)
                            if (!player)
                                return;
                        continue;

                        list.remove((*i));
                    }

                    // Max 3 Wild Mushroom
                    if ((int32)list.size() >= spell->Effects[0].BasePoints)
                        list.front()->ToTempSummon()->UnSummon();

                    Position pos;
                    GetExplTargetDest()->GetPosition(&pos);
                    const SummonPropertiesEntry* properties = sSummonPropertiesStore.LookupEntry(spell->Effects[effIndex].MiscValueB);
                    TempSummon* summon = player->SummonCreature(spell->Effects[0].MiscValue, pos, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, spell->GetDuration());

                    if (!summon)
                        return;

                    summon->SetUInt64Value(UNIT_FIELD_SUMMONEDBY, player->GetGUID());
                    summon->setFaction(player->getFaction());
                    summon->SetUInt32Value(UNIT_CREATED_BY_SPELL, GetSpellInfo()->Id);
                    summon->SetMaxHealth(5);
                    summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                    summon->StopMoving();
                    summon->SetControlled(true, UNIT_STATE_STUNNED);
                }
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_druid_wild_mushroom_SpellScript::HandleSummon, EFFECT_0, SPELL_EFFECT_SUMMON);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_druid_wild_mushroom_SpellScript();
        }
};

// Wild mushroom : Detonate, 88751
class spell_druid_wild_mushroom_detonate : public SpellScriptLoader
{
    public:
        spell_druid_wild_mushroom_detonate() : SpellScriptLoader("spell_druid_wild_mushroom_detonate") { }

        class spell_druid_wild_mushroom_detonate_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_druid_wild_mushroom_detonate_SpellScript)

            // Globals variables
            float spellRange;
            std::list<TempSummon*> mushroomList;
            std::list<TempSummon*> fungal_List;

            bool Load()
            {
                spellRange = GetSpellInfo()->GetMaxRange();

                Player* player = GetCaster()->ToPlayer();

                if (!player)
                    return false;

                std::list<Creature*> list;
                std::list<TempSummon*> summonList;
                player->GetCreatureListWithEntryInGrid(list, DRUID_NPC_WILD_MUSHROOM, 500.0f);

                for (std::list<Creature*>::const_iterator i = list.begin(); i != list.end(); ++i)
                {
                    if ((*i)->IsSummon() && (*i)->GetCharmerOrOwner() == player)
                    {
                        summonList.push_back((*i)->ToTempSummon());
                        continue;
                    }
                }
                mushroomList = summonList;

                if (!spellRange)
                    return false;

                return true;
            }

            SpellCastResult CheckCast()
            {
                Player* player = GetCaster()->ToPlayer();
                if (!player)
                    return SPELL_FAILED_CASTER_DEAD;

                if (mushroomList.empty())
                    return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

                bool inRange = false;

                for (std::list<TempSummon*>::const_iterator i = mushroomList.begin(); i != mushroomList.end(); ++i)
                {
                    Position shroomPos;
                    (*i)->GetPosition(&shroomPos);

                    // Must have at least one mushroom within 40 yards
                    if (player->IsWithinDist3d(&shroomPos, spellRange))
                    {
                        inRange = true;
                        break;
                    }
                }

                if (!inRange)
                {
                    SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_TARGET_TOO_FAR);
                    return SPELL_FAILED_CUSTOM_ERROR;
                }

                return SPELL_CAST_OK;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Player* player = GetCaster()->ToPlayer())
                {
                    uint32 fungal = NULL;
                    uint32 npcfungal = NULL;

                    // Fungal Growth Rank 1
                    if (player->HasAura(SPELL_DRUID_TALENT_FUNGAL_GROWTH_1))
                    {
                        fungal = SPELL_DRUID_FUNGAL_GROWTH_1;
                        npcfungal = DRUID_NPC_FUNGAL_GROWTH_1;
                    }
                    // Fungal Growth Rank 2
                    else if (player->HasAura(SPELL_DRUID_TALENT_FUNGAL_GROWTH_2))
                    {
                        fungal = SPELL_DRUID_FUNGAL_GROWTH_2;
                        npcfungal = DRUID_NPC_FUNGAL_GROWTH_2;
                    }
                    else
                    {
                        // Nothing do
                    }

                    for (std::list<TempSummon*>::const_iterator i = mushroomList.begin(); i != mushroomList.end(); ++i)
                    {
                        Position shroomPos;

                        (*i)->GetPosition(&shroomPos);

                        if (!player->IsWithinDist3d(&shroomPos, spellRange))
                            continue;

                        // Explosion visual and suicide
                        (*i)->CastSpell((*i), SPELL_DRUID_WILD_MUSHROOM_SUICIDE, true);

                        // damage
                        player->CastSpell((*i)->GetPositionX(), (*i)->GetPositionY(), (*i)->GetPositionZ(), SPELL_DRUID_WILD_MUSHROOM_DAMAGE, true);

                        // Summoning fungal growth
                        if (fungal)
                            player->CastSpell((*i)->GetPositionX(), (*i)->GetPositionY(), (*i)->GetPositionZ(), fungal, true);
                    }

                    // Stop Moving on Fungal Growth
                    std::list<Creature*> fungal_list;
                    std::list<TempSummon*> fungalsummonList;
                    player->GetCreatureListWithEntryInGrid(fungal_list, npcfungal, 500.0f);

                    for (std::list<Creature*>::const_iterator i = fungal_list.begin(); i != fungal_list.end(); ++i)
                    {
                        if ((*i)->IsSummon() && (*i)->GetCharmerOrOwner() == player)
                        {
                            fungalsummonList.push_back((*i)->ToTempSummon());
                            continue;
                        }
                    }
                    fungal_List = fungalsummonList;

                    if (!fungal_List.empty())
                    {
                        for (std::list<TempSummon*>::const_iterator iter = fungal_List.begin(); iter != fungal_List.end(); ++iter)
                        {
                            (*iter)->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                            (*iter)->StopMoving();
                            (*iter)->SetControlled(true, UNIT_STATE_STUNNED);
                        }
                    }

                    // Cleanup Wild Mushroom
                    std::list<Creature*> list;
                    player->GetCreatureListWithEntryInGrid(list, DRUID_NPC_WILD_MUSHROOM, 500.0f);
                    for (std::list<Creature*>::iterator i = list.begin(); i != list.end(); ++i)
                    {
                        if ((*i)->IsSummon() && (*i)->GetCharmerOrOwner() == player)
                            if (!player)
                                return;
                        continue;

                        list.remove((*i));
                    }

                    if ((int32)list.size() > 0)
                        list.front()->ToTempSummon()->UnSummon();
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_druid_wild_mushroom_detonate_SpellScript::CheckCast);
                OnEffectHitTarget += SpellEffectFn(spell_druid_wild_mushroom_detonate_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_druid_wild_mushroom_detonate_SpellScript();
        }
};

//  81262 - Efflorescence
class spell_druid_Efflorescence: public SpellScriptLoader
{
public:
    spell_druid_Efflorescence () : SpellScriptLoader("spell_druid_Efflorescence") { }

    class spell_druid_Efflorescence_AuraScript: public AuraScript
    {
        PrepareAuraScript(spell_druid_Efflorescence_AuraScript);

        void OnTick (AuraEffect const* aurEff)
        {
            if (DynamicObject* dynObj = GetCaster()->GetDynObject(81262))
                if (GetCaster()->GetMapId() == dynObj->GetMapId())
                    GetCaster()->CastSpell(dynObj->GetPositionX(), dynObj->GetPositionY(), dynObj->GetPositionZ(), 81269, true);
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_druid_Efflorescence_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_druid_Efflorescence_AuraScript();
    }
};

// Rejuvenation - Gift of the Earthmother
class spell_druid_rejuvenation_earthmother : public SpellScriptLoader
{
    public:
        spell_druid_rejuvenation_earthmother() : SpellScriptLoader("spell_druid_rejuvenation_earthmother") { }

        class spell_druid_rejuvenation_earthmother_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_druid_rejuvenation_earthmother_AuraScript);

            void AfterApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                        if (AuraEffect const* Gift = GetCaster()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_DRUID, 3186, 1))
                        {
                            int32 heal = aurEff->GetAmount();
                            uint8 baseTotalTicks = uint8(GetCaster()->CalcSpellDuration(GetSpellInfo()) / GetSpellInfo()->Effects[0].Amplitude);
                            heal = GetCaster()->SpellHealingBonusDone(GetTarget(), GetSpellInfo(), heal, DOT, GetSpellInfo()->StackAmount);
                            heal = GetTarget()->SpellHealingBonusTaken(GetCaster(), GetSpellInfo(), heal, DOT, GetSpellInfo()->StackAmount);
                            heal = heal * Gift->GetAmount() / 100;
                            heal = heal * baseTotalTicks;
                            GetCaster()->CastCustomSpell(GetTarget(), 64801, &heal, NULL, NULL, true);
                        }
            }

            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_druid_rejuvenation_earthmother_AuraScript::AfterApply, EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_druid_rejuvenation_earthmother_AuraScript();
        }
};

// Harmony
class spell_dru_harmony : public SpellScriptLoader
{
    public:
        spell_dru_harmony() : SpellScriptLoader("spell_dru_harmony") { }

        class spell_dru_harmony_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_harmony_SpellScript);

            void HandleAfterCast()
            {
                if (AuraEffect* aurEff = GetCaster()->GetAuraEffect(77495, 0))
                if (GetCaster()->ToPlayer()->GetPrimaryTalentTree(GetCaster()->ToPlayer()->GetActiveSpec()) == BS_DRUID_RESTORATION)
                {
                    int32 bp = aurEff->GetAmount();
                    GetCaster()->CastCustomSpell(GetCaster(), 100977, &bp, &bp, NULL,true);
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_dru_harmony_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_harmony_SpellScript();
        }
};

enum EclipseSpells
{
    SPELL_DRUID_WRATH                       = 5176,
    SPELL_DRUID_STARFIRE                    = 2912,
    SPELL_DRUID_STARSURGE                   = 78674,
    SPELL_DRUID_ECLIPSE_GENERAL_ENERGIZE    = 89265,
    SPELL_DRUID_STARSURGE_ENERGIZE          = 86605,
    SPELL_DRUID_LUNAR_ECLIPSE_MARKER        = 67484, // Will make the yellow arrow on eclipse bar point to the blue side (lunar)
    SPELL_DRUID_SOLAR_ECLIPSE_MARKER        = 67483, // Will make the yellow arrow on eclipse bar point to the yellow side (solar)
    SPELL_DRUID_SOLAR_ECLIPSE               = 48517,
    SPELL_DRUID_LUNAR_ECLIPSE               = 48518,
    SPELL_DRUID_EUPHORIA_ENERGIZE            = 81069
};

// 69366 - Moonkin Form passive
class spell_dru_moonkin_form_passive : public SpellScriptLoader
{
    public:
        spell_dru_moonkin_form_passive() : SpellScriptLoader("spell_dru_moonkin_form_passive") { }

        class spell_dru_moonkin_form_passive_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_moonkin_form_passive_AuraScript);

            uint32 absorbPct;

            bool Load()
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
                // reduces all damage taken while Stunned in Moonkin Form
                if (GetTarget()->GetUInt32Value(UNIT_FIELD_FLAGS) & (UNIT_FLAG_STUNNED) && GetTarget()->HasAuraWithMechanic(1<<MECHANIC_STUN))
                    absorbAmount = CalculatePct(dmgInfo.GetDamage(), absorbPct);
            }

            void Register()
            {
                 DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dru_moonkin_form_passive_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                 OnEffectAbsorb += AuraEffectAbsorbFn(spell_dru_moonkin_form_passive_AuraScript::Absorb, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_moonkin_form_passive_AuraScript();
        }
};


// 33851 - Primal Tenacity
class spell_dru_primal_tenacity : public SpellScriptLoader
{
    public:
        spell_dru_primal_tenacity() : SpellScriptLoader("spell_dru_primal_tenacity") { }

        class spell_dru_primal_tenacity_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_primal_tenacity_AuraScript);

            uint32 absorbPct;

            bool Load()
            {
                absorbPct = GetSpellInfo()->Effects[EFFECT_1].CalcValue(GetCaster());
                return true;
            }

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                // Set absorbtion amount to unlimited
                amount = -1;
            }

            void Absorb(AuraEffect* /*aurEff*/, DamageInfo & dmgInfo, uint32 & absorbAmount)
            {
                // reduces all damage taken while Stunned in Cat Form
                if (GetTarget()->GetShapeshiftForm() == FORM_CAT && GetTarget()->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED) && GetTarget()->HasAuraWithMechanic(1<<MECHANIC_STUN))
                    absorbAmount = CalculatePct(dmgInfo.GetDamage(), absorbPct);
            }

            void Register()
            {
                 DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dru_primal_tenacity_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_SCHOOL_ABSORB);
                 OnEffectAbsorb += AuraEffectAbsorbFn(spell_dru_primal_tenacity_AuraScript::Absorb, EFFECT_1);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_primal_tenacity_AuraScript();
        }
};

class spell_dru_starfall_aoe : public SpellScriptLoader
{
    public:
        spell_dru_starfall_aoe() : SpellScriptLoader("spell_dru_starfall_aoe") { }

        class spell_dru_starfall_aoe_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_starfall_aoe_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove(GetExplTargetUnit());
                for (std::list<WorldObject*>::iterator itr = targets.begin(); itr != targets.end(); )
                {
                    if (!(*itr)->ToUnit()->IsHostileTo(GetCaster()))
                        itr = targets.erase(itr);
                    else
                        ++itr;
                }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dru_starfall_aoe_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_starfall_aoe_SpellScript();
        }
};

// Wrath, Starfire, and Starsurge
class spell_dru_eclipse_energize : public SpellScriptLoader
{
public:
    spell_dru_eclipse_energize() : SpellScriptLoader("spell_dru_eclipse_energize") { }

    class spell_dru_eclipse_energize_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dru_eclipse_energize_SpellScript);

        int32 energizeAmount;

        bool Load()
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return false;

            if (GetCaster()->ToPlayer()->getClass() != CLASS_DRUID)
                return false;

            energizeAmount = 0;

            return true;
        }

        void HandleEnergize(SpellEffIndex effIndex)
        {
            Player* caster = GetCaster()->ToPlayer();

            // No boomy, no deal.
            if (caster->GetPrimaryTalentTree(caster->GetActiveSpec()) != TALENT_TREE_DRUID_BALANCE)
                return;

            switch(GetSpellInfo()->Id)
            {
                case SPELL_DRUID_WRATH:
                {
                    energizeAmount = -GetSpellInfo()->Effects[effIndex].BasePoints; // -13
                    // If we are set to fill the lunar side or we've just logged in with 0 power..
                    if ((!caster->HasAura(SPELL_DRUID_SOLAR_ECLIPSE_MARKER) && caster->HasAura(SPELL_DRUID_LUNAR_ECLIPSE_MARKER))
                        || caster->GetPower(POWER_ECLIPSE) == 0)
                    {
                        // Euphoria
                        // To do: which spell we have to use?
                        if (AuraEffect const* aurEff = caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_DRUID, 4431, 0))
                            if (roll_chance_i(aurEff->GetAmount()))
                                //caster->CastCustomSpell(caster, SPELL_DRUID_EUPHORIA_ENERGIZE, &energizeAmount, 0, 0, true);
                                energizeAmount *=2;

                        // Item - Druid T12 Balance 4P Bonus
                        if (caster->HasAura(99049))
                            energizeAmount -= 3;

                        caster->CastCustomSpell(caster,SPELL_DRUID_ECLIPSE_GENERAL_ENERGIZE,&energizeAmount,0,0,true);
                        // If the energize was due to 0 power, cast the eclipse marker aura
                        if (!caster->HasAura(SPELL_DRUID_LUNAR_ECLIPSE_MARKER))
                            caster->CastSpell(caster,SPELL_DRUID_LUNAR_ECLIPSE_MARKER,true);
                    }
                    // The energizing effect brought us out of the solar eclipse, remove the aura
                    if (caster->HasAura(SPELL_DRUID_SOLAR_ECLIPSE) && caster->GetPower(POWER_ECLIPSE) <= 0)
                        caster->RemoveAurasDueToSpell(SPELL_DRUID_SOLAR_ECLIPSE);
                    break;
                }
                case SPELL_DRUID_STARFIRE:
                {
                    energizeAmount = GetSpellInfo()->Effects[effIndex].BasePoints; // 20
                    // If we are set to fill the solar side or we've just logged in with 0 power..
                    if ((!caster->HasAura(SPELL_DRUID_LUNAR_ECLIPSE_MARKER) && caster->HasAura(SPELL_DRUID_SOLAR_ECLIPSE_MARKER))
                        || caster->GetPower(POWER_ECLIPSE) == 0)
                    {
                        // Euphoria
                        // To do: which spell we have to use?
                        if (AuraEffect const* aurEff = caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_DRUID, 4431, 0))
                            if (roll_chance_i(aurEff->GetAmount()))
                                //caster->CastCustomSpell(caster, SPELL_DRUID_EUPHORIA_ENERGIZE, &energizeAmount, 0, 0, true);
                                energizeAmount *=2;

                        // Item - Druid T12 Balance 4P Bonus
                        if (caster->HasAura(99049))
                            energizeAmount += 5;

                        caster->CastCustomSpell(caster,SPELL_DRUID_ECLIPSE_GENERAL_ENERGIZE,&energizeAmount,0,0,true);
                        // If the energize was due to 0 power, cast the eclipse marker aura
                        if (!caster->HasAura(SPELL_DRUID_SOLAR_ECLIPSE_MARKER))
                            caster->CastSpell(caster,SPELL_DRUID_SOLAR_ECLIPSE_MARKER,true);
                    }
                    // The energizing effect brought us out of the lunar eclipse, remove the aura
                    if (caster->HasAura(SPELL_DRUID_LUNAR_ECLIPSE) && caster->GetPower(POWER_ECLIPSE) >= 0)
                        caster->RemoveAura(SPELL_DRUID_LUNAR_ECLIPSE);
                    break;
                }
                case SPELL_DRUID_STARSURGE:
                {
                    // If we are set to fill the solar side or we've just logged in with 0 power (confirmed with sniffs)
                    if ((!caster->HasAura(SPELL_DRUID_LUNAR_ECLIPSE_MARKER) && caster->HasAura(SPELL_DRUID_SOLAR_ECLIPSE_MARKER))
                        || caster->GetPower(POWER_ECLIPSE) == 0)
                    {
                        energizeAmount = GetSpellInfo()->Effects[effIndex].BasePoints; // 15
                        caster->CastCustomSpell(caster,SPELL_DRUID_STARSURGE_ENERGIZE,&energizeAmount,0,0,true);

                        // If the energize was due to 0 power, cast the eclipse marker aura
                        if (!caster->HasAura(SPELL_DRUID_SOLAR_ECLIPSE_MARKER))
                            caster->CastSpell(caster,SPELL_DRUID_SOLAR_ECLIPSE_MARKER,true);
                    }
                    else if (!caster->HasAura(SPELL_DRUID_SOLAR_ECLIPSE_MARKER) && caster->HasAura(SPELL_DRUID_LUNAR_ECLIPSE_MARKER))
                    {
                        energizeAmount = -GetSpellInfo()->Effects[effIndex].BasePoints; // -15
                        caster->CastCustomSpell(caster,SPELL_DRUID_STARSURGE_ENERGIZE,&energizeAmount,0,0,true);
                    }
                    // The energizing effect brought us out of the lunar eclipse, remove the aura
                    if (caster->HasAura(SPELL_DRUID_LUNAR_ECLIPSE) && caster->GetPower(POWER_ECLIPSE) >= 0)
                        caster->RemoveAura(SPELL_DRUID_LUNAR_ECLIPSE);
                    // The energizing effect brought us out of the solar eclipse, remove the aura
                    else if (caster->HasAura(SPELL_DRUID_SOLAR_ECLIPSE) && caster->GetPower(POWER_ECLIPSE) <= 0)
                        caster->RemoveAura(SPELL_DRUID_SOLAR_ECLIPSE);
                    break;
                }
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_dru_eclipse_energize_SpellScript::HandleEnergize, EFFECT_1, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dru_eclipse_energize_SpellScript;
    }
};

// Primal Madness
// 5229 Enrage
// 5217 Name: Tiger's Fury
// 50334 Berserk
class spell_dru_primal_madness : public SpellScriptLoader
{
    public:
        spell_dru_primal_madness() : SpellScriptLoader("spell_dru_primal_madness") {}

        class spell_dru_primal_madness_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_dru_primal_madness_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->getClass() != CLASS_DRUID)
                        return;

                    if (caster->HasAura(80316) || caster->HasAura(80317))
                    {
                       if (caster->GetShapeshiftForm() == FORM_BEAR)
                        {
                            int spell_id = caster->HasAura(80316) ? 80316 : 80317;
                            int bp0 = int32(sSpellMgr->GetSpellInfo(spell_id)->Effects[0].BasePoints);
                            caster->CastCustomSpell(caster, 17080, &bp0, NULL, NULL, true);
                        }
                        else if (caster->GetShapeshiftForm() == FORM_CAT)
                        {
                            int spell_id = caster->HasAura(80316) ? 80879 : 80886;
                            caster->CastSpell(caster, spell_id , true);

                            int bp = int32(sSpellMgr->GetSpellInfo(spell_id)->Effects[0].BasePoints);
                            caster->ModifyPower(POWER_ENERGY, bp);
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_dru_primal_madness_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_dru_primal_madness_SpellScript();
        }
};

enum LunarShowerSpells
{
    SPELL_DRUID_MOONFIRE    = 8921,
    SPELL_DRUID_SUNFIRE     = 93402,
};

// Moonfire and Sunfire
class spell_dru_lunar_shower_energize : public SpellScriptLoader
{
public:
    spell_dru_lunar_shower_energize() : SpellScriptLoader("spell_dru_lunar_shower_energize") { }

    class spell_dru_lunar_shower_energize_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dru_lunar_shower_energize_SpellScript);

        bool Load()
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return false;

            if (GetCaster()->ToPlayer()->getClass() != CLASS_DRUID)
                return false;

            if (!GetCaster()->HasAura(81006) &&
                !GetCaster()->HasAura(81191) &&
                !GetCaster()->HasAura(81192))
                return false;

            return true;
        }

        void HandleEnergize(SpellEffIndex /*effIndex*/)
        {
            Player* caster = GetCaster()->ToPlayer();

            // No boomy, no deal.
            if (caster->GetPrimaryTalentTree(caster->GetActiveSpec()) != TALENT_TREE_DRUID_BALANCE)
                return;

            switch(GetSpellInfo()->Id)
            {
                case SPELL_DRUID_SUNFIRE:
                {
                    int32 energizeAmount = -8;
                    // If we are set to fill the lunar side or we've just logged in with 0 power..
                    if ((!caster->HasAura(SPELL_DRUID_SOLAR_ECLIPSE_MARKER) && caster->HasAura(SPELL_DRUID_LUNAR_ECLIPSE_MARKER))
                        || caster->GetPower(POWER_ECLIPSE) == 0)
                    {
                        caster->CastCustomSpell(caster,SPELL_DRUID_ECLIPSE_GENERAL_ENERGIZE,&energizeAmount,0,0,true);
                        // If the energize was due to 0 power, cast the eclipse marker aura
                        if (!caster->HasAura(SPELL_DRUID_LUNAR_ECLIPSE_MARKER))
                            caster->CastSpell(caster,SPELL_DRUID_LUNAR_ECLIPSE_MARKER,true);
                    }
                    // The energizing effect brought us out of the solar eclipse, remove the aura
                    if (caster->HasAura(SPELL_DRUID_SOLAR_ECLIPSE) && caster->GetPower(POWER_ECLIPSE) <= 0)
                        caster->RemoveAurasDueToSpell(SPELL_DRUID_SOLAR_ECLIPSE);
                    break;
                }
                case SPELL_DRUID_MOONFIRE:
                {
                    int32 energizeAmount = 8;
                    // If we are set to fill the solar side or we've just logged in with 0 power..
                    if ((!caster->HasAura(SPELL_DRUID_LUNAR_ECLIPSE_MARKER) && caster->HasAura(SPELL_DRUID_SOLAR_ECLIPSE_MARKER))
                        || caster->GetPower(POWER_ECLIPSE) == 0)
                    {
                        caster->CastCustomSpell(caster,SPELL_DRUID_ECLIPSE_GENERAL_ENERGIZE,&energizeAmount,0,0,true);
                        // If the energize was due to 0 power, cast the eclipse marker aura
                        if (!caster->HasAura(SPELL_DRUID_SOLAR_ECLIPSE_MARKER))
                            caster->CastSpell(caster,SPELL_DRUID_SOLAR_ECLIPSE_MARKER,true);
                    }
                    // The energizing effect brought us out of the lunar eclipse, remove the aura
                    if (caster->HasAura(SPELL_DRUID_LUNAR_ECLIPSE) && caster->GetPower(POWER_ECLIPSE) >= 0)
                        caster->RemoveAura(SPELL_DRUID_LUNAR_ECLIPSE);
                    break;
                }
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_dru_lunar_shower_energize_SpellScript::HandleEnergize, EFFECT_1, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dru_lunar_shower_energize_SpellScript;
    }
};

// Feral Agression - Faerie Fire
class spell_dru_faerie_fire : public SpellScriptLoader
{
public:
    spell_dru_faerie_fire() : SpellScriptLoader("spell_dru_faerie_fire") {}

    class spell_dru_faerie_fire_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dru_faerie_fire_SpellScript);

        bool Load()
        {
            return GetCaster() && GetCaster()->GetTypeId() == TYPEID_PLAYER;
        }

        void ChangeStackAmount()
        {
            if (AuraEffect const* aurEff = GetCaster()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_DRUID, 960, 0))
            {
                if (GetHitUnit() && GetCaster()->IsInFeralForm())
                {
                    if (Aura* faerieFire = GetHitUnit()->GetAura(DRUID_FAERIE_FIRE, GetCaster()->GetGUID()))
                        faerieFire->SetStackAmount(aurEff->GetAmount());
                }
            }
        }

        void Register()
        {
            AfterHit += SpellHitFn(spell_dru_faerie_fire_SpellScript::ChangeStackAmount);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dru_faerie_fire_SpellScript();
    }
};



void AddSC_druid_spell_scripts()
{
    new spell_dru_glyph_of_starfire();
    new spell_dru_savage_defense();
    new spell_dru_t10_restoration_4p_bonus();
    new spell_dru_swift_flight_passive();
    new spell_dru_starfall_dummy();
    new spell_dru_lifebloom();
    new spell_dru_predatory_strikes();
    new spell_dru_savage_roar();
    new spell_dru_survival_instincts();
    new spell_dru_insect_swarm();
    new spell_druid_wild_mushroom();
    new spell_druid_wild_mushroom_detonate();
    new spell_dru_stampede();
    new spell_druid_Efflorescence();
    new spell_druid_rejuvenation_earthmother();
    new spell_dru_harmony();
    new spell_dru_moonkin_form_passive();
    new spell_dru_primal_tenacity();
    new spell_dru_starfall_aoe();
    new spell_dru_eclipse_energize();
    new spell_dru_primal_madness();
    new spell_dru_lunar_shower_energize();
    new spell_dru_faerie_fire();
}