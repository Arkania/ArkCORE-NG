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
 * Scripts for spells with SPELLFAMILY_WARLOCK and SPELLFAMILY_GENERIC spells used by warlock players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_warl_".
 */

#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

enum WarlockSpells
{
    SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELGUARD    = 54508,
    SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELHUNTER   = 54509,
    SPELL_WARLOCK_DEMONIC_EMPOWERMENT_IMP         = 54444,
    SPELL_WARLOCK_DEMONIC_EMPOWERMENT_SUCCUBUS    = 54435,
    SPELL_WARLOCK_DEMONIC_EMPOWERMENT_VOIDWALKER  = 54443,
    SPELL_WARLOCK_HEALTHSTONE_CREATE              = 34130,
    SPELL_WARLOCK_HEALTHSTONE_HEAL                = 6262,
    SPELL_WARLOCK_DEMONIC_CIRCLE_SUMMON           = 48018,
    SPELL_WARLOCK_DEMONIC_CIRCLE_TELEPORT         = 48020,
    SPELL_WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST       = 62388,
    SPELL_WARLOCK_HAUNT                           = 48181,
    SPELL_WARLOCK_HAUNT_HEAL                      = 48210,
    SPELL_WARLOCK_SOULSHATTER                     = 32835,
    SPELL_WARLOCK_UNSTABLE_AFFLICTION_DISPEL      = 31117,
    SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_R1       = 18703,
    SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_R2       = 18704,
    SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R1  = 60955,
    SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R2  = 60956,
};

// 710 - Banish
/// Updated 4.3.4
class spell_warl_banish : public SpellScriptLoader
{
public:
    spell_warl_banish() : SpellScriptLoader("spell_warl_banish") { }

    class spell_warl_banish_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_banish_SpellScript);

        bool Load()
        {
            _removed = false;
            return true;
        }

        void HandleBanish()
        {
                /// Casting Banish on a banished target will cancel the effect
                /// Check if the target already has Banish, if so, do nothing.
            if (Unit* target = GetHitUnit())
            {
                if (target->GetAuraEffect(SPELL_AURA_SCHOOL_IMMUNITY, SPELLFAMILY_WARLOCK, 0, 0x08000000, 0))
                {
                    // No need to remove old aura since its removed due to not stack by current Banish aura
                    PreventHitDefaultEffect(EFFECT_0);
                    PreventHitDefaultEffect(EFFECT_1);
                    PreventHitDefaultEffect(EFFECT_2);
                    _removed = true;
                }
            }
        }

        void RemoveAura()
        {
            if (_removed)
                PreventHitAura();
        }

        void Register()
        {
            BeforeHit += SpellHitFn(spell_warl_banish_SpellScript::HandleBanish);
            AfterHit += SpellHitFn(spell_warl_banish_SpellScript::RemoveAura);
        }

        bool _removed;
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warl_banish_SpellScript();
    }
};

// 6201 - Create Healthstone
class spell_warl_create_healthstone : public SpellScriptLoader
{
    public:
        spell_warl_create_healthstone() : SpellScriptLoader("spell_warl_create_healthstone") { }

        class spell_warl_create_healthstone_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_create_healthstone_SpellScript);

            bool Validate(SpellInfo const* /*spellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_HEALTHSTONE_CREATE) || !sSpellMgr->GetSpellInfo(SPELL_WARLOCK_HEALTHSTONE_HEAL))
                    return false;
                return true;
            }

            void HandleScriptEffect(SpellEffIndex effIndex)
            {
                Unit* caster = GetCaster();
                if (caster)
                    caster->CastSpell(caster,SPELL_WARLOCK_HEALTHSTONE_CREATE,false);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_create_healthstone_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_create_healthstone_SpellScript();
        }
};

enum LifeTap
{
    SPELL_LIFE_TAP_ENERGIZE     = 31818,
    SPELL_LIFE_TAP_ENERGIZE_2   = 32553,
    ICON_ID_IMPROVED_LIFE_TAP   = 208,
    ICON_ID_MANA_FEED           = 1982,
};

class spell_warl_demonic_circle_summon : public SpellScriptLoader
{
    public:
        spell_warl_demonic_circle_summon() : SpellScriptLoader("spell_warl_demonic_circle_summon") { }

        class spell_warl_demonic_circle_summon_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_demonic_circle_summon_AuraScript);

            void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
            {
                // If effect is removed by expire remove the summoned demonic circle too.
                if (!(mode & AURA_EFFECT_HANDLE_REAPPLY))
                    GetTarget()->RemoveGameObject(GetId(), true);

                GetTarget()->SendAuraVisualForSelf(false, 62388);
            }

            void HandleDummyTick(AuraEffect const* /*aurEff*/)
            {
                if (GameObject* circle = GetTarget()->GetGameObject(GetId()))
                {
                    // Here we check if player is in demonic circle teleport range, if so add
                    // SPELL_WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST; allowing him to cast the SPELL_WARLOCK_DEMONIC_CIRCLE_TELEPORT.
                    // If not in range remove the SPELL_WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST.
                    
                    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_CIRCLE_TELEPORT);
                    if (GetTarget()->IsWithinDist(circle, spellInfo->GetMaxRange(true)))
                        GetTarget()->SendAuraVisualForSelf(true, 62388, 1);
                    else
                        GetTarget()->SendAuraVisualForSelf(false, 62388);
                }
            }

            void Register()
            {
                OnEffectRemove += AuraEffectApplyFn(spell_warl_demonic_circle_summon_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_demonic_circle_summon_AuraScript::HandleDummyTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_demonic_circle_summon_AuraScript();
        }
};

// 48020 - Demonic Circle: Teleport
/// Updated 4.3.4
class spell_warl_demonic_circle_teleport : public SpellScriptLoader
{
    public:
        spell_warl_demonic_circle_teleport() : SpellScriptLoader("spell_warl_demonic_circle_teleport") { }

        class spell_warl_demonic_circle_teleport_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_demonic_circle_teleport_AuraScript);

            void HandleTeleport(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* player = GetTarget()->ToPlayer())
                {
                    if (GameObject* circle = player->GetGameObject(SPELL_WARLOCK_DEMONIC_CIRCLE_SUMMON))
                    {
                        player->NearTeleportTo(circle->GetPositionX(), circle->GetPositionY(), circle->GetPositionZ(), circle->GetOrientation());
                        player->RemoveMovementImpairingAuras();
                    }
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warl_demonic_circle_teleport_AuraScript::HandleTeleport, EFFECT_0, SPELL_AURA_MECHANIC_IMMUNITY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_demonic_circle_teleport_AuraScript();
        }
};

// 77801 - Demon Soul - Updated to 4.3.4
class spell_warl_demon_soul : public SpellScriptLoader
{
    public:
        spell_warl_demon_soul() : SpellScriptLoader("spell_warl_demon_soul") { }

        class spell_warl_demon_soul_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_demon_soul_SpellScript);

            bool Load()
            {
                if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                    return false;
                return true;
            }

            void HandleScriptEffect(SpellEffIndex /*effIndex*/)
            {
                if (Pet* pet = GetCaster()->ToPlayer()->GetPet())
                {
                    CreatureTemplate const* ci = sObjectMgr->GetCreatureTemplate(pet->GetEntry());
                    switch (ci->family)
                    {
                    case CREATURE_FAMILY_SUCCUBUS:
                        GetCaster()->CastSpell(GetCaster(), 79463, true);
                        break;
                    case CREATURE_FAMILY_VOIDWALKER:
                        GetCaster()->CastSpell(GetCaster(), 79464, true);
                        break;
                    case CREATURE_FAMILY_FELGUARD:
                        GetCaster()->CastSpell(GetCaster(), 79462, true);
                        break;
                    case CREATURE_FAMILY_FELHUNTER:
                        GetCaster()->CastSpell(GetCaster(), 79460, true);
                        break;
                    case CREATURE_FAMILY_IMP:
                        GetCaster()->CastSpell(GetCaster(), 79459, true);
                        break;
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_demon_soul_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_demon_soul_SpellScript();
        }
};

// 47193 - Demonic Empowerment
/// Updated 4.3.4
class spell_warl_demonic_empowerment : public SpellScriptLoader
{
    public:
        spell_warl_demonic_empowerment() : SpellScriptLoader("spell_warl_demonic_empowerment") { }

        class spell_warl_demonic_empowerment_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_demonic_empowerment_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_EMPOWERMENT_SUCCUBUS) || !sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_EMPOWERMENT_VOIDWALKER) || !sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELGUARD) || !sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELHUNTER) || !sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_EMPOWERMENT_IMP))
                    return false;
                return true;
            }

            void HandleScriptEffect(SpellEffIndex /*effIndex*/)
            {
                if (Creature* targetCreature = GetHitCreature())
                {
                    if (targetCreature->IsPet())
                    {
                        CreatureTemplate const* ci = sObjectMgr->GetCreatureTemplate(targetCreature->GetEntry());
                        switch (ci->family)
                        {
                        case CREATURE_FAMILY_SUCCUBUS:
                            targetCreature->CastSpell(targetCreature, SPELL_WARLOCK_DEMONIC_EMPOWERMENT_SUCCUBUS, true);
                            break;
                        case CREATURE_FAMILY_VOIDWALKER:
                        {
                            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(SPELL_WARLOCK_DEMONIC_EMPOWERMENT_VOIDWALKER);
                            int32 hp = int32(targetCreature->CountPctFromMaxHealth(GetCaster()->CalculateSpellDamage(targetCreature, spellInfo, 0)));
                            targetCreature->CastCustomSpell(targetCreature, SPELL_WARLOCK_DEMONIC_EMPOWERMENT_VOIDWALKER, &hp, NULL, NULL, true);
                            break;
                        }
                        case CREATURE_FAMILY_FELGUARD:
                            targetCreature->CastSpell(targetCreature, SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELGUARD, true);
                            break;
                        case CREATURE_FAMILY_FELHUNTER:
                            targetCreature->CastSpell(targetCreature, SPELL_WARLOCK_DEMONIC_EMPOWERMENT_FELHUNTER, true);
                            break;
                        case CREATURE_FAMILY_IMP:
                            targetCreature->CastSpell(targetCreature, SPELL_WARLOCK_DEMONIC_EMPOWERMENT_IMP, true);
                            break;
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_demonic_empowerment_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_demonic_empowerment_SpellScript();
        }
};

// 47422 - Everlasting Affliction
/// Updated 4.3.4
class spell_warl_everlasting_affliction : public SpellScriptLoader
{
    public:
        spell_warl_everlasting_affliction() : SpellScriptLoader("spell_warl_everlasting_affliction") { }

        class spell_warl_everlasting_affliction_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_everlasting_affliction_SpellScript);

            void HandleScriptEffect(SpellEffIndex /*effIndex*/)
            {
                if (Unit* unitTarget = GetHitUnit())
                    // Refresh corruption on target
                    if (AuraEffect* aur = unitTarget->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_WARLOCK, 0x2, 0, 0, GetCaster()->GetGUID()))
                        aur->GetBase()->RefreshDuration();
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_everlasting_affliction_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_everlasting_affliction_SpellScript();
        }
};

// 77799 Fel Flame
class spell_warl_fel_flame: public SpellScriptLoader 
{
public:
    spell_warl_fel_flame() : SpellScriptLoader("spell_warl_fel_flame") { }

    class spell_warl_fel_flame_SpellScript: public SpellScript 
    {
        PrepareSpellScript(spell_warl_fel_flame_SpellScript)

        void HandleOnHit()
        {
            Unit* unitTarget = GetHitUnit();
            Unit* caster = GetCaster();

            // Immolate
            if (Aura* aur = unitTarget->GetOwnedAura(348, caster->GetGUID()))
            {
                if (aur->GetDuration() + 6000 > 15000)
                    aur->SetDuration(15000);
                else
                    aur->SetDuration(aur->GetDuration() + 6000);
            }

            //Unstable Affliction
            if (Aura* aur = unitTarget->GetOwnedAura(30108, caster->GetGUID()))
            {
                if (aur->GetDuration() + 6000 > 15000)
                    aur->SetDuration(15000);
                else
                    aur->SetDuration(aur->GetDuration() + 6000);
            }
        }

        void Register() 
        {
            OnHit += SpellHitFn(spell_warl_fel_flame_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const 
    {
        return new spell_warl_fel_flame_SpellScript();
    }
};

// 48181 - Haunt
/// Updated 4.3.4
class spell_warl_haunt : public SpellScriptLoader
{
    public:
        spell_warl_haunt() : SpellScriptLoader("spell_warl_haunt") { }

        class spell_warl_haunt_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_haunt_SpellScript);

            void HandleOnHit()
            {
                if (Aura* aura = GetHitAura())
                    if (AuraEffect* aurEff = aura->GetEffect(EFFECT_1))
                        aurEff->SetAmount(CalculatePctN(aurEff->GetAmount(), GetHitDamage()));
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_haunt_SpellScript::HandleOnHit);
            }
        };

        class spell_warl_haunt_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_haunt_AuraScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_HAUNT_HEAL))
                    return false;
                return true;
            }

            void HandleRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    int32 amount = aurEff->GetAmount();
                    GetTarget()->CastCustomSpell(caster, SPELL_WARLOCK_HAUNT_HEAL, &amount, NULL, NULL, true, NULL, aurEff, GetCasterGUID());
                }
            }

            void Register()
            {
                OnEffectRemove += AuraEffectApplyFn(spell_warl_haunt_AuraScript::HandleRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_haunt_SpellScript();
        }

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_haunt_AuraScript();
        }
};

class spell_warl_life_tap : public SpellScriptLoader
{
    public:
        spell_warl_life_tap() : SpellScriptLoader("spell_warl_life_tap") { }

        class spell_warl_life_tap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_life_tap_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_LIFE_TAP_ENERGIZE) || !sSpellMgr->GetSpellInfo(SPELL_LIFE_TAP_ENERGIZE_2))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Player* caster = GetCaster()->ToPlayer();
                if (Unit* target = GetHitUnit())
                {
                    int32 damage = GetEffectValue();
                    int32 mana = int32(damage + (caster->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS+SPELL_SCHOOL_SHADOW) * 0.5f));

                    // Shouldn't Appear in Combat Log
                    target->ModifyHealth(-damage);

                    // Improved Life Tap mod
                    if (AuraEffect const* aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_WARLOCK, ICON_ID_IMPROVED_LIFE_TAP, 0))
                        AddPctN(mana, aurEff->GetAmount());

                    caster->CastCustomSpell(target, SPELL_LIFE_TAP_ENERGIZE, &mana, NULL, NULL, false);

                    // Mana Feed
                    int32 manaFeedVal = 0;
                    if (AuraEffect const* aurEff = caster->GetAuraEffect(SPELL_AURA_ADD_FLAT_MODIFIER, SPELLFAMILY_WARLOCK, ICON_ID_MANA_FEED, 0))
                        manaFeedVal = aurEff->GetAmount();

                    if (manaFeedVal > 0)
                    {
                        ApplyPctN(manaFeedVal, mana);
                        caster->CastCustomSpell(caster, SPELL_LIFE_TAP_ENERGIZE_2, &manaFeedVal, NULL, NULL, true, NULL);
                    }
                }
            }

            SpellCastResult CheckCast()
            {
                if ((int32(GetCaster()->GetHealth()) > int32(GetSpellInfo()->Effects[EFFECT_0].CalcValue() + (6.3875 * GetSpellInfo()->BaseLevel))))
                    return SPELL_CAST_OK;
                return SPELL_FAILED_FIZZLE;
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_life_tap_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnCheckCast += SpellCheckCastFn(spell_warl_life_tap_SpellScript::CheckCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_life_tap_SpellScript();
        }
};

class spell_warl_soulshatter : public SpellScriptLoader
{
    public:
        spell_warl_soulshatter() : SpellScriptLoader("spell_warl_soulshatter") { }

        class spell_warl_soulshatter_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_soulshatter_SpellScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_SOULSHATTER))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                if (Unit* target = GetHitUnit())
                {
                    if (target->CanHaveThreatList() && target->getThreatManager().getThreat(caster) > 0.0f)
                        caster->CastSpell(target, SPELL_WARLOCK_SOULSHATTER, true);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_soulshatter_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_soulshatter_SpellScript();
        }
};

// 30108, 34438, 34439, 35183 - Unstable Affliction
/// Updated 4.3.4
class spell_warl_unstable_affliction : public SpellScriptLoader
{
    public:
        spell_warl_unstable_affliction() : SpellScriptLoader("spell_warl_unstable_affliction") { }

        class spell_warl_unstable_affliction_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_unstable_affliction_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARLOCK_UNSTABLE_AFFLICTION_DISPEL))
                    return false;
                return true;
            }

            void HandleDispel(DispelInfo* dispelInfo)
            {
                if (Unit* caster = GetCaster())
                    if (AuraEffect const* aurEff = GetEffect(EFFECT_1))
                    {
                        int32 damage = aurEff->GetAmount() * 9;
                        // backfire damage and silence
                        caster->CastCustomSpell(dispelInfo->GetDispeller(), SPELL_WARLOCK_UNSTABLE_AFFLICTION_DISPEL, &damage, NULL, NULL, true, NULL, aurEff);
                    }
            }

            void Register()
            {
                AfterDispel += AuraDispelFn(spell_warl_unstable_affliction_AuraScript::HandleDispel);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_unstable_affliction_AuraScript();
        }
};

// DrainLife
class spell_warl_drain_life: public SpellScriptLoader
{
public:
    spell_warl_drain_life () : SpellScriptLoader("spell_warl_drain_life") { }

    class spell_warl_drain_life_AuraScript: public AuraScript
    {
        PrepareAuraScript(spell_warl_drain_life_AuraScript);
        void OnPeriodic (AuraEffect const* /*aurEff*/)
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return;

            int32 bp = 0;
            if (GetId() == 689)
                bp = 2; // Normal, restore 2% of health
            else if (GetId() == 89420)
                bp = 5; // Soulburn restore 5% of health

            // Check for Death's Embrace
            if (AuraEffect const* aurEff = GetCaster()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_WARLOCK, 3223, 0))
                if (GetCaster()->HealthBelowPct(25))
                    bp += int32(aurEff->GetAmount());

            GetCaster()->CastCustomSpell(GetCaster(), 89653, &bp, NULL, NULL, true);
        }

        void OnRemove (AuraEffect const * aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (GetCaster()->GetTypeId()== TYPEID_PLAYER && GetCaster()->HasAura(74434)) 
                GetCaster()->RemoveAura(74434);
        }

        void Register ()
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_warl_drain_life_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_drain_life_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
        }
    };
    AuraScript* GetAuraScript () const
    {
        return new spell_warl_drain_life_AuraScript();
    }
};

// Soul burn
class spell_warl_soul_burn: public SpellScriptLoader
{
public:
    spell_warl_soul_burn () : SpellScriptLoader("spell_warl_soul_burn") { }
    class spell_warl_soul_burn_SpellScript: public SpellScript
    {
        PrepareSpellScript(spell_warl_soul_burn_SpellScript);
        bool Load()
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER || !GetCaster()->HasAura(74434))
                return false;
            return true;
        }

        void HandleOnHit ()
        {
            int32 spell = 0;
            if (GetSpellInfo()->Id == 6262) // Soulburn: Healstone
                spell = 79437;
            else if (GetSpellInfo()->Id == 5676) // Soulburn: Searing Pain
                spell = 79440;
            else if (GetSpellInfo()->Id == 48020) // Soulburn: Demonic Circle
                spell = 79438;
            else if (GetSpellInfo()->Id == 27243) // Soulburn: Seed of corruption
                GetCaster()->ToPlayer()->AddTemporarySpell(93312);

            GetCaster()->CastSpell(GetCaster(),spell,true);
        }

        void HandleAfterHit ()
        {
            if (GetCaster()->HasAura(74434)) 
                GetCaster()->RemoveAura(74434);
        }

        void Register ()
        {
            OnHit += SpellHitFn(spell_warl_soul_burn_SpellScript::HandleOnHit);
            AfterHit += SpellHitFn(spell_warl_soul_burn_SpellScript::HandleAfterHit);
        }
    };
    SpellScript* GetSpellScript () const
    {
        return new spell_warl_soul_burn_SpellScript();
    }
};

// Drain soul
class spell_warl_drain_soul: public SpellScriptLoader
{
public:
    spell_warl_drain_soul () : SpellScriptLoader("spell_warl_drain_soul") { }          //1120

    class spell_warl_drain_soul_AuraScript: public AuraScript
    {
        PrepareAuraScript(spell_warl_drain_soul_AuraScript)

        void HandleApplyEffect(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            //Pandemic
            if (AuraEffect const* aurEff = GetCaster()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_WARLOCK, 4554, 0))
                if (roll_chance_i(aurEff->GetAmount()))
                    if (GetTarget()->HealthBelowPct(25))
                        if (AuraEffect* aur = GetTarget()->GetAuraEffect(30108,1,GetCaster()->GetGUID()))
                            aur->GetBase()->RefreshDuration();
        }

        void AfterRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_DEATH)
            {
                // Restore soul shard when target dead from drain soul
                GetCaster()->CastSpell(GetCaster(), 79264, true);

                // Glyph of drain soul
                if (AuraEffect* aur = GetCaster()->GetAuraEffect(58070, 0))
                    GetCaster()->CastSpell(GetCaster(), 58068, true);
            }
        }

        void Register ()
        {
            OnEffectApply += AuraEffectApplyFn(spell_warl_drain_soul_AuraScript::HandleApplyEffect, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
            AfterEffectRemove += AuraEffectRemoveFn(spell_warl_drain_soul_AuraScript::AfterRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript () const
    {
        return new spell_warl_drain_soul_AuraScript();
    }
};

// Nether protection
class spell_warl_nether_protection : public SpellScriptLoader
{
    public:
        spell_warl_nether_protection() : SpellScriptLoader("spell_warl_nether_protection") { }

        class spell_warl_nether_protection_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_nether_protection_AuraScript);

            bool Load()
            {
                if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                    return false;

                if (AuraEffect* aurEff = GetCaster()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_WARLOCK, 1985, 0))
                    return true;
                return false;
            }

            void OnAbsorb(AuraEffect* aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
            {
                if (!dmgInfo.GetSpellInfo())
                    return;

                int32 trigger_spell_id = 0;
                switch (GetFirstSchoolInMask(dmgInfo.GetSpellInfo()->GetSchoolMask()))
                {
                case SPELL_SCHOOL_HOLY:
                    trigger_spell_id = 54370;
                    break;
                case SPELL_SCHOOL_FIRE:
                    trigger_spell_id = 54371;
                    break;
                case SPELL_SCHOOL_NATURE:
                    trigger_spell_id = 54375;
                    break;
                case SPELL_SCHOOL_FROST:
                    trigger_spell_id = 54372;
                    break;
                case SPELL_SCHOOL_SHADOW:
                    trigger_spell_id = 54374;
                    break;
                case SPELL_SCHOOL_ARCANE:
                    trigger_spell_id = 54373;
                    break;
                default:
                    break;
                }

                if (trigger_spell_id != 0)
                {
                    if (GetCaster()->HasAura(54370))
                        GetCaster()->RemoveAura(54370);
                    else if (GetCaster()->HasAura(54371))
                        GetCaster()->RemoveAura(54371);
                    else if (GetCaster()->HasAura(54375))
                        GetCaster()->RemoveAura(54375);
                    else if (GetCaster()->HasAura(54372))
                        GetCaster()->RemoveAura(54372);
                    else if (GetCaster()->HasAura(54374))
                        GetCaster()->RemoveAura(54374);
                    else if (GetCaster()->HasAura(54373))
                        GetCaster()->RemoveAura(54373);
                
                    int32 bp = 0;
                    if (GetCaster()->HasAura(30299))
                        bp = -15;
                    else 
                        bp = -30;

                    GetCaster()->CastCustomSpell(GetCaster(), trigger_spell_id, &bp, NULL, NULL, true);
                }
            }

            void Register()
            {
                OnEffectAbsorb += AuraEffectAbsorbFn(spell_warl_nether_protection_AuraScript::OnAbsorb, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_nether_protection_AuraScript();
        }
};

// Improved Soul Fire
class spell_warl_improved_soul_fire: public SpellScriptLoader 
{
public:
    spell_warl_improved_soul_fire() : SpellScriptLoader("spell_warl_improved_soul_fire") { }

    class spell_warl_improved_soul_fire_SpellScript: public SpellScript
    {
        PrepareSpellScript(spell_warl_improved_soul_fire_SpellScript)

        bool Load()
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return false;
            return true;
        }

        void HandleOnHit()
        {
            if (AuraEffect* SoulFire = GetCaster()->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_WARLOCK, 184, 0))
            {
                int32 bp = SoulFire->GetAmount();
                GetCaster()->CastCustomSpell(GetCaster(),85383,&bp,NULL,NULL,true);
            }
        }

        void Register() 
        {
            OnHit += SpellHitFn(spell_warl_improved_soul_fire_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const 
    {
        return new spell_warl_improved_soul_fire_SpellScript();
    }
};

// Shadowburn soul shards regen
class spell_warl_shadowburn_soul_shards_regen : public SpellScriptLoader
{
    public:
        spell_warl_shadowburn_soul_shards_regen() : SpellScriptLoader("spell_warl_shadowburn_soul_shards_regen") { }

        class spell_warl_shadowburn_soul_shards_regen_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_shadowburn_soul_shards_regen_AuraScript);

            bool Load ()
            {
                if (GetCaster()->GetTypeId() != TYPEID_PLAYER || !GetCaster()->ToPlayer()->isHonorOrXPTarget(GetUnitOwner()))
                    return false;
                return true;
            }

            void AfterRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_DEATH)
                {
                    int32 bp = 3;
                    GetCaster()->CastCustomSpell(GetCaster(),87388,&bp,NULL,NULL,true);
                }
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_warl_shadowburn_soul_shards_regen_AuraScript::AfterRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_shadowburn_soul_shards_regen_AuraScript();
        }
};

// Glyph of Shadowburn
class spell_warl_shadowburn_glyph : public SpellScriptLoader
{
    public:
        spell_warl_shadowburn_glyph() : SpellScriptLoader("spell_warl_shadowburn_glyph") { }

        class spell_warl_shadowburn_glyph_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_shadowburn_glyph_SpellScript);

            bool Load ()
            {
                if (GetCaster()->GetTypeId() != TYPEID_PLAYER || !GetCaster()->HasAura(56229))
                    return false;
                return true;
            }

            void HandleAfterHit()
            {
                if (GetHitUnit()->IsAlive() && GetHitUnit()->HealthBelowPct(20))
                    GetCaster()->ToPlayer()->RemoveSpellCooldown(17877);
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_warl_shadowburn_glyph_SpellScript::HandleAfterHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_shadowburn_glyph_SpellScript();
        }
};

// Empowered imp
class spell_warl_empowered_imp: public SpellScriptLoader 
{
public:
    spell_warl_empowered_imp() : SpellScriptLoader("spell_warl_empowered_imp") { }

    class spell_warl_empowered_imp_SpellScript: public SpellScript 
    {
        PrepareSpellScript(spell_warl_empowered_imp_SpellScript)

        bool Load()
        {
            if (!GetCaster()->IsPet() || !GetCaster()->ToPet()->GetOwner())
                return false;

            if (AuraEffect* aurEff = GetCaster()->ToPet()->GetOwner()->GetAuraEffect(SPELL_AURA_ADD_FLAT_MODIFIER, SPELLFAMILY_WARLOCK, 3171, 0))
                return true;
            return false;
        }

        void HandleOnHit()
        {
            if (Unit *owner = GetCaster()->ToPet()->GetOwner())
                if (AuraEffect* EmpImp = owner->GetAuraEffect(SPELL_AURA_ADD_FLAT_MODIFIER, SPELLFAMILY_WARLOCK, 3171, 0))
                    if (roll_chance_i(EmpImp->GetAmount()))
                        GetCaster()->CastSpell(owner,47283,true);
        }

        void Register() 
        {
            OnHit += SpellHitFn(spell_warl_empowered_imp_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const 
    {
        return new spell_warl_empowered_imp_SpellScript();
    }
};

// Dark intent
class spell_warl_dark_intent: public SpellScriptLoader 
{
public:
    spell_warl_dark_intent() : SpellScriptLoader("spell_warl_dark_intent") { }

    class spell_warl_dark_intent_SpellScript: public SpellScript 
    {
        PrepareSpellScript(spell_warl_dark_intent_SpellScript)

        void HandleScriptEffect(SpellEffIndex effIndex)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();

            if (!caster || !target)
                return;

            target->CastSpell(caster, 85767, true);
            caster->AddAura(85768, target);
            PreventHitEffect(effIndex);
        }

        void Register() 
        {
            OnEffectLaunchTarget += SpellEffectFn(spell_warl_dark_intent_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_TRIGGER_SPELL);
        }
    };

    SpellScript* GetSpellScript() const 
    {
        return new spell_warl_dark_intent_SpellScript();
    }
};

class spell_warl_health_funnel : public SpellScriptLoader
{
public:
    spell_warl_health_funnel() : SpellScriptLoader("spell_warl_health_funnel") { }

    class spell_warl_health_funnel_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_health_funnel_AuraScript);

        void ApplyEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            Unit* target = GetTarget();
            if (caster->HasAura(SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_R2))
                target->CastSpell(target, SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R2, true);
            else if (caster->HasAura(SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_R1))
                target->CastSpell(target, SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R1, true);
        }

        void RemoveEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* target = GetTarget();
            target->RemoveAurasDueToSpell(SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R1);
            target->RemoveAurasDueToSpell(SPELL_WARLOCK_IMPROVED_HEALTH_FUNNEL_BUFF_R2);
        }

        void Register()
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_warl_health_funnel_AuraScript::RemoveEffect, EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL);
            OnEffectApply += AuraEffectApplyFn(spell_warl_health_funnel_AuraScript::ApplyEffect, EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warl_health_funnel_AuraScript();
    }
};

void AddSC_warlock_spell_scripts()
{
    new spell_warl_banish();
    new spell_warl_create_healthstone();
    new spell_warl_demonic_circle_summon();
    new spell_warl_demonic_circle_teleport();
    new spell_warl_demonic_empowerment();
    new spell_warl_dark_intent();
    new spell_warl_drain_life();
    new spell_warl_drain_soul();
    new spell_warl_demon_soul();
    new spell_warl_empowered_imp();
    new spell_warl_everlasting_affliction();
    new spell_warl_fel_flame();
    new spell_warl_haunt();
    new spell_warl_improved_soul_fire();
    new spell_warl_life_tap();
    new spell_warl_nether_protection();
    new spell_warl_shadowburn_glyph();
    new spell_warl_shadowburn_soul_shards_regen();
    new spell_warl_soul_burn();
    new spell_warl_soulshatter();
    new spell_warl_unstable_affliction();
    new spell_warl_health_funnel();
}