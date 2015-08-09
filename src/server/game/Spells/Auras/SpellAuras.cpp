/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
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

#include "Common.h"
#include "WorldPacket.h"
#include "Opcodes.h"
#include "Log.h"
#include "ObjectMgr.h"
#include "SpellMgr.h"
#include "Player.h"
#include "Pet.h"
#include "Unit.h"
#include "Spell.h"
#include "SpellAuraEffects.h"
#include "DynamicObject.h"
#include "ObjectAccessor.h"
#include "Util.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "CellImpl.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "Vehicle.h"

AuraApplication::AuraApplication(Unit* target, Unit* caster, Aura* aura, uint8 effMask):
_target(target), _base(aura), _removeMode(AURA_REMOVE_NONE), _slot(MAX_AURAS),
_flags(AFLAG_NONE), _effectsToApply(effMask), _needClientUpdate(false)
{
    ASSERT(GetTarget() && GetBase());

    if (GetBase()->CanBeSentToClient())
    {
        // Try find slot for aura
        uint8 slot = MAX_AURAS;
        // Lookup for auras already applied from spell
        if (AuraApplication * foundAura = GetTarget()->GetAuraApplication(GetBase()->GetId(), GetBase()->GetCasterGUID(), GetBase()->GetCastItemGUID()))
        {
            // allow use single slot only by auras from same caster
            slot = foundAura->GetSlot();
        }
        else
        {
            Unit::VisibleAuraMap const* visibleAuras = GetTarget()->GetVisibleAuras();
            // lookup for free slots in units visibleAuras
            Unit::VisibleAuraMap::const_iterator itr = visibleAuras->find(0);
            for (uint32 freeSlot = 0; freeSlot < MAX_AURAS; ++itr, ++freeSlot)
            {
                if (itr == visibleAuras->end() || itr->first != freeSlot)
                {
                    slot = freeSlot;
                    break;
                }
            }
        }

        // Register Visible Aura
        if (slot < MAX_AURAS)
        {
            _slot = slot;
            GetTarget()->SetVisibleAura(slot, this);
            SetNeedClientUpdate();
            TC_LOG_DEBUG("spells", "Aura: %u Effect: %d put to unit visible auras slot: %u", GetBase()->GetId(), GetEffectMask(), slot);
        }
        else
            TC_LOG_DEBUG("spells", "Aura: %u Effect: %d could not find empty unit visible slot", GetBase()->GetId(), GetEffectMask());
    }

    _InitFlags(caster, effMask);
}

void AuraApplication::_Remove()
{
    uint8 slot = GetSlot();

    if (slot >= MAX_AURAS)
        return;

    if (AuraApplication * foundAura = _target->GetAuraApplication(GetBase()->GetId(), GetBase()->GetCasterGUID(), GetBase()->GetCastItemGUID()))
    {
        // Reuse visible aura slot by aura which is still applied - prevent storing dead pointers
        if (slot == foundAura->GetSlot())
        {
            if (GetTarget()->GetVisibleAura(slot) == this)
            {
                GetTarget()->SetVisibleAura(slot, foundAura);
                foundAura->SetNeedClientUpdate();
            }
            // set not valid slot for aura - prevent removing other visible aura
            slot = MAX_AURAS;
        }
    }

    // update for out of range group members
    if (slot < MAX_AURAS)
    {
        GetTarget()->RemoveVisibleAura(slot);
        ClientUpdate(true);
    }
}

void AuraApplication::_InitFlags(Unit* caster, uint8 effMask)
{
    // mark as selfcast if needed
    _flags |= (GetBase()->GetCasterGUID() == GetTarget()->GetGUID()) ? AFLAG_CASTER : AFLAG_NONE;

    // aura is cast by self or an enemy
    // one negative effect and we know aura is negative
    if (IsSelfcast() || !caster || !caster->IsFriendlyTo(GetTarget()))
    {
        bool negativeFound = false;
        for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
        {
            if (((1<<i) & effMask) && !GetBase()->GetSpellInfo()->IsPositiveEffect(i))
            {
                negativeFound = true;
                break;
            }
        }
        _flags |= negativeFound ? AFLAG_NEGATIVE : AFLAG_POSITIVE;
    }
    // aura is cast by friend
    // one positive effect and we know aura is positive
    else
    {
        bool positiveFound = false;
        for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
        {
            if (((1<<i) & effMask) && GetBase()->GetSpellInfo()->IsPositiveEffect(i))
            {
                positiveFound = true;
                break;
            }
        }
        _flags |= positiveFound ? AFLAG_POSITIVE : AFLAG_NEGATIVE;
    }

    if (GetBase()->GetSpellInfo()->AttributesEx8 & SPELL_ATTR8_AURA_SEND_AMOUNT)
        _flags |= AFLAG_ANY_EFFECT_AMOUNT_SENT;
}

void AuraApplication::_HandleEffect(uint8 effIndex, bool apply)
{
    AuraEffect* aurEff = GetBase()->GetEffect(effIndex);
    ASSERT(aurEff);
    ASSERT(HasEffect(effIndex) == (!apply));
    ASSERT((1<<effIndex) & _effectsToApply);
    TC_LOG_DEBUG("spells", "AuraApplication::_HandleEffect: %u, apply: %u: amount: %u", aurEff->GetAuraType(), apply, aurEff->GetAmount());

    if (apply)
    {
        ASSERT(!(_flags & (1<<effIndex)));
        _flags |= 1<<effIndex;
        aurEff->HandleEffect(this, AURA_EFFECT_HANDLE_REAL, true);
    }
    else
    {
        ASSERT(_flags & (1<<effIndex));
        _flags &= ~(1<<effIndex);
        aurEff->HandleEffect(this, AURA_EFFECT_HANDLE_REAL, false);

        // Remove all triggered by aura spells vs unlimited duration
        aurEff->CleanupTriggeredSpells(GetTarget());
    }
    SetNeedClientUpdate();
}

void AuraApplication::BuildUpdatePacket(ByteBuffer& data, bool remove) const
{
    data << uint8(_slot);

    if (remove)
    {
        ASSERT(!_target->GetVisibleAura(_slot));
        data << uint32(0);
        return;
    }
    else
    {
        ASSERT(_target->GetVisibleAura(_slot));

        Aura const* aura = GetBase();
        data << uint32(aura->GetId());
        uint32 flags = _flags;
        if (aura->GetMaxDuration() > 0 && !(aura->GetSpellInfo()->AttributesEx5 & SPELL_ATTR5_HIDE_DURATION))
            flags |= AFLAG_DURATION;
        if (!aura->IsPassive())
            flags |= AFLAG_ANY_EFFECT_AMOUNT_SENT;
        data << uint16(flags);
        data << uint8(aura->GetCasterLevel());
        // send stack amount for aura which could be stacked (never 0 - causes incorrect display) or charges
        // stack amount has priority over charges (checked on retail with spell 50262)
        data << uint8(aura->GetSpellInfo()->StackAmount ? aura->GetStackAmount() : aura->GetCharges());

        if (!(flags & AFLAG_CASTER))
            data.appendPackGUID(aura->GetCasterGUID());

        if (flags & AFLAG_DURATION)
        {
            data << uint32(aura->GetMaxDuration());
            data << uint32(aura->GetDuration());
        }

        if (flags & AFLAG_ANY_EFFECT_AMOUNT_SENT)
            for (uint32 i = 0; i < MAX_SPELL_EFFECTS; ++i)
                if (AuraEffect const* eff = aura->GetEffect(i))
                    if (HasEffect(i))       // Not all of aura's effects have to be applied on every target
                        data << int32(eff->GetAmount());
    }
}

void AuraApplication::ClientUpdate(bool remove)
{
    _needClientUpdate = false;

    WorldPacket data(SMSG_AURA_UPDATE);
    data.append(GetTarget()->GetPackGUID());
    BuildUpdatePacket(data, remove);

    _target->SendMessageToSet(&data, true);
}

uint8 Aura::BuildEffectMaskForOwner(SpellInfo const* spellProto, uint8 avalibleEffectMask, WorldObject* owner)
{
    ASSERT(spellProto);
    ASSERT(owner);
    uint8 effMask = 0;
    switch (owner->GetTypeId())
    {
        case TYPEID_UNIT:
        case TYPEID_PLAYER:
            for (uint8 i = 0; i< MAX_SPELL_EFFECTS; ++i)
            {
                if (spellProto->Effects[i].IsUnitOwnedAuraEffect())
                    effMask |= 1 << i;
            }
            break;
        case TYPEID_DYNAMICOBJECT:
            for (uint8 i = 0; i< MAX_SPELL_EFFECTS; ++i)
            {
                if (spellProto->Effects[i].Effect == SPELL_EFFECT_PERSISTENT_AREA_AURA)
                    effMask |= 1 << i;
            }
            break;
        default:
            break;
    }
    return effMask & avalibleEffectMask;
}

Aura* Aura::TryRefreshStackOrCreate(SpellInfo const* spellproto, uint8 tryEffMask, WorldObject* owner, Unit* caster, int32* baseAmount /*= NULL*/, Item* castItem /*= NULL*/, uint64 casterGUID /*= 0*/, bool* refresh /*= NULL*/)
{
    ASSERT(spellproto);
    ASSERT(owner);
    ASSERT(caster || casterGUID);
    ASSERT(tryEffMask <= MAX_EFFECT_MASK);
    if (refresh)
        *refresh = false;
    uint8 effMask = Aura::BuildEffectMaskForOwner(spellproto, tryEffMask, owner);
    if (!effMask)
        return NULL;
    if (Aura* foundAura = owner->ToUnit()->_TryStackingOrRefreshingExistingAura(spellproto, effMask, caster, baseAmount, castItem, casterGUID))
    {
        // we've here aura, which script triggered removal after modding stack amount
        // check the state here, so we won't create new Aura object
        if (foundAura->IsRemoved())
            return NULL;

        if (refresh)
            *refresh = true;
        return foundAura;
    }
    else
        return Create(spellproto, effMask, owner, caster, baseAmount, castItem, casterGUID);
}

Aura* Aura::TryCreate(SpellInfo const* spellproto, uint8 tryEffMask, WorldObject* owner, Unit* caster, int32* baseAmount /*= NULL*/, Item* castItem /*= NULL*/, uint64 casterGUID /*= 0*/)
{
    ASSERT(spellproto);
    ASSERT(owner);
    ASSERT(caster || casterGUID);
    ASSERT(tryEffMask <= MAX_EFFECT_MASK);
    uint8 effMask = Aura::BuildEffectMaskForOwner(spellproto, tryEffMask, owner);
    if (!effMask)
        return NULL;
    return Create(spellproto, effMask, owner, caster, baseAmount, castItem, casterGUID);
}

Aura* Aura::Create(SpellInfo const* spellproto, uint8 effMask, WorldObject* owner, Unit* caster, int32* baseAmount, Item* castItem, uint64 casterGUID)
{
    ASSERT(effMask);
    ASSERT(spellproto);
    ASSERT(owner);
    ASSERT(caster || casterGUID);
    ASSERT(effMask <= MAX_EFFECT_MASK);
    // try to get caster of aura
    if (casterGUID)
    {
        if (owner->GetGUID() == casterGUID)
            caster = owner->ToUnit();
        else
            caster = ObjectAccessor::GetUnit(*owner, casterGUID);
    }
    else
        casterGUID = caster->GetGUID();

    // check if aura can be owned by owner
    if (owner->isType(TYPEMASK_UNIT))
        if (!owner->IsInWorld() || ((Unit*)owner)->IsDuringRemoveFromWorld())
            // owner not in world so don't allow to own not self cast single target auras
            if (casterGUID != owner->GetGUID() && spellproto->IsSingleTarget())
                return NULL;

    Aura* aura = NULL;
    switch (owner->GetTypeId())
    {
        case TYPEID_UNIT:
        case TYPEID_PLAYER:
            aura = new UnitAura(spellproto, effMask, owner, caster, baseAmount, castItem, casterGUID);
            break;
        case TYPEID_DYNAMICOBJECT:
            aura = new DynObjAura(spellproto, effMask, owner, caster, baseAmount, castItem, casterGUID);
            break;
        default:
            ASSERT(false);
            return NULL;
    }
    // aura can be removed in Unit::_AddAura call
    if (aura->IsRemoved())
        return NULL;
    return aura;
}

Aura::Aura(SpellInfo const* spellproto, WorldObject* owner, Unit* caster, Item* castItem, uint64 casterGUID) :
m_spellInfo(spellproto), m_casterGuid(casterGUID ? casterGUID : caster->GetGUID()),
m_castItemGuid(castItem ? castItem->GetGUID() : 0), m_applyTime(time(NULL)),
m_owner(owner), m_timeCla(0), m_updateTargetMapInterval(0),
m_casterLevel(caster ? caster->getLevel() : m_spellInfo->SpellLevel), m_procCharges(0), m_stackAmount(1),
m_isRemoved(false), m_isSingleTarget(false), m_isUsingCharges(false)
{
    if (m_spellInfo->ManaPerSecond)
        m_timeCla = 1 * IN_MILLISECONDS;

    m_maxDuration = CalcMaxDuration(caster);
    m_duration = m_maxDuration;
    m_procCharges = CalcMaxCharges(caster);
    m_isUsingCharges = m_procCharges != 0;
    memset(m_effects, 0, sizeof(m_effects));
    // m_casterLevel = cast item level/caster level, caster level should be saved to db, confirmed with sniffs
}

AuraScript* Aura::GetScriptByName(std::string const& scriptName) const
{
    for (std::list<AuraScript*>::const_iterator itr = m_loadedScripts.begin(); itr != m_loadedScripts.end(); ++itr)
        if ((*itr)->_GetScriptName()->compare(scriptName) == 0)
            return *itr;
    return NULL;
}

void Aura::_InitEffects(uint8 effMask, Unit* caster, int32 *baseAmount)
{
    // shouldn't be in constructor - functions in AuraEffect::AuraEffect use polymorphism
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
    {
        if (effMask & (uint8(1) << i))
            m_effects[i] = new AuraEffect(this, i, baseAmount ? baseAmount + i : NULL, caster);
        else
            m_effects[i] = NULL;
    }
}

Aura::~Aura()
{
    // unload scripts
    while (!m_loadedScripts.empty())
    {
        std::list<AuraScript*>::iterator itr = m_loadedScripts.begin();
        (*itr)->_Unload();
        delete (*itr);
        m_loadedScripts.erase(itr);
    }

    // free effects memory
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
         delete m_effects[i];

    ASSERT(m_applications.empty());
    _DeleteRemovedApplications();
}

Unit* Aura::GetCaster() const
{
    if (GetOwner()->GetGUID() == GetCasterGUID())
        return GetUnitOwner();
    if (AuraApplication const* aurApp = GetApplicationOfTarget(GetCasterGUID()))
        return aurApp->GetTarget();

    return ObjectAccessor::GetUnit(*GetOwner(), GetCasterGUID());
}

AuraObjectType Aura::GetType() const
{
    return (m_owner->GetTypeId() == TYPEID_DYNAMICOBJECT) ? DYNOBJ_AURA_TYPE : UNIT_AURA_TYPE;
}

void Aura::_ApplyForTarget(Unit* target, Unit* caster, AuraApplication * auraApp)
{
    ASSERT(target);
    ASSERT(auraApp);
    // aura mustn't be already applied on target
    ASSERT (!IsAppliedOnTarget(target->GetGUID()) && "Aura::_ApplyForTarget: aura musn't be already applied on target");

    m_applications[target->GetGUID()] = auraApp;

    // set infinity cooldown state for spells
    if (caster && caster->GetTypeId() == TYPEID_PLAYER)
    {
        if (m_spellInfo->IsCooldownStartedOnEvent())
        {
            Item* castItem = m_castItemGuid ? caster->ToPlayer()->GetItemByGuid(m_castItemGuid) : NULL;
            caster->ToPlayer()->AddSpellAndCategoryCooldowns(m_spellInfo, castItem ? castItem->GetEntry() : 0, NULL, true);
        }
    }
}

void Aura::_UnapplyForTarget(Unit* target, Unit* caster, AuraApplication * auraApp)
{
    ASSERT(target);
    ASSERT(auraApp->GetRemoveMode());
    ASSERT(auraApp);

    ApplicationMap::iterator itr = m_applications.find(target->GetGUID());

    /// @todo Figure out why this happens
    if (itr == m_applications.end())
    {
        TC_LOG_ERROR("spells", "Aura::_UnapplyForTarget, target:%u, caster:%u, spell:%u was not found in owners application map!",
        target->GetGUIDLow(), caster ? caster->GetGUIDLow() : 0, auraApp->GetBase()->GetSpellInfo()->Id);
        ASSERT(false);
    }

    // aura has to be already applied
    ASSERT(itr->second == auraApp);
    m_applications.erase(itr);

    m_removedApplications.push_back(auraApp);

    // reset cooldown state for spells
    if (caster && caster->GetTypeId() == TYPEID_PLAYER)
    {
        if (GetSpellInfo()->IsCooldownStartedOnEvent())
            // note: item based cooldowns and cooldown spell mods with charges ignored (unknown existed cases)
            caster->ToPlayer()->SendCooldownEvent(GetSpellInfo());
    }
}

// removes aura from all targets
// and marks aura as removed
void Aura::_Remove(AuraRemoveMode removeMode)
{
    ASSERT (!m_isRemoved);
    m_isRemoved = true;
    ApplicationMap::iterator appItr = m_applications.begin();
    for (appItr = m_applications.begin(); appItr != m_applications.end();)
    {
        AuraApplication * aurApp = appItr->second;
        Unit* target = aurApp->GetTarget();
        target->_UnapplyAura(aurApp, removeMode);
        appItr = m_applications.begin();
    }
}

void Aura::UpdateTargetMap(Unit* caster, bool apply)
{
    if (IsRemoved())
        return;

    m_updateTargetMapInterval = UPDATE_TARGET_MAP_INTERVAL;

    // fill up to date target list
    //       target, effMask
    std::map<Unit*, uint8> targets;

    FillTargetMap(targets, caster);

    UnitList targetsToRemove;

    // mark all auras as ready to remove
    for (ApplicationMap::iterator appIter = m_applications.begin(); appIter != m_applications.end();++appIter)
    {
        std::map<Unit*, uint8>::iterator existing = targets.find(appIter->second->GetTarget());
        // not found in current area - remove the aura
        if (existing == targets.end())
            targetsToRemove.push_back(appIter->second->GetTarget());
        else
        {
            // needs readding - remove now, will be applied in next update cycle
            // (dbcs do not have auras which apply on same type of targets but have different radius, so this is not really needed)
            if (appIter->second->GetEffectMask() != existing->second || !CanBeAppliedOn(existing->first))
                targetsToRemove.push_back(appIter->second->GetTarget());
            // nothing todo - aura already applied
            // remove from auras to register list
            targets.erase(existing);
        }
    }

    // register auras for units
    for (std::map<Unit*, uint8>::iterator itr = targets.begin(); itr!= targets.end();)
    {
        // aura mustn't be already applied on target
        if (AuraApplication * aurApp = GetApplicationOfTarget(itr->first->GetGUID()))
        {
            // the core created 2 different units with same guid
            // this is a major failue, which i can't fix right now
            // let's remove one unit from aura list
            // this may cause area aura "bouncing" between 2 units after each update
            // but because we know the reason of a crash we can remove the assertion for now
            if (aurApp->GetTarget() != itr->first)
            {
                // remove from auras to register list
                targets.erase(itr++);
                continue;
            }
            else
            {
                // ok, we have one unit twice in target map (impossible, but...)
                ASSERT(false);
            }
        }

        bool addUnit = true;
        // check target immunities
        for (uint8 effIndex = 0; effIndex < MAX_SPELL_EFFECTS; ++effIndex)
        {
            if (itr->first->IsImmunedToSpellEffect(GetSpellInfo(), effIndex))
                itr->second &= ~(1 << effIndex);
        }
        if (!itr->second
            || itr->first->IsImmunedToSpell(GetSpellInfo())
            || !CanBeAppliedOn(itr->first))
            addUnit = false;

        if (addUnit)
        {
            // persistent area aura does not hit flying targets
            if (GetType() == DYNOBJ_AURA_TYPE)
            {
                if (itr->first->IsInFlight())
                    addUnit = false;
            }
            // unit auras can not stack with each other
            else // (GetType() == UNIT_AURA_TYPE)
            {
                // Allow to remove by stack when aura is going to be applied on owner
                if (itr->first != GetOwner())
                {
                    // check if not stacking aura already on target
                    // this one prevents unwanted usefull buff loss because of stacking and prevents overriding auras periodicaly by 2 near area aura owners
                    for (Unit::AuraApplicationMap::iterator iter = itr->first->GetAppliedAuras().begin(); iter != itr->first->GetAppliedAuras().end(); ++iter)
                    {
                        Aura const* aura = iter->second->GetBase();
                        if (!CanStackWith(aura))
                        {
                            addUnit = false;
                            break;
                        }
                    }
                }
            }
        }
        if (!addUnit)
            targets.erase(itr++);
        else
        {
            // owner has to be in world, or effect has to be applied to self
            if (!GetOwner()->IsSelfOrInSameMap(itr->first))
            {
                /// @todo There is a crash caused by shadowfiend load addon
                TC_LOG_FATAL("spells", "Aura %u: Owner %s (map %u) is not in the same map as target %s (map %u).", GetSpellInfo()->Id,
                    GetOwner()->GetName().c_str(), GetOwner()->IsInWorld() ? GetOwner()->GetMap()->GetId() : uint32(-1),
                    itr->first->GetName().c_str(), itr->first->IsInWorld() ? itr->first->GetMap()->GetId() : uint32(-1));
                ASSERT(false);
            }
            itr->first->_CreateAuraApplication(this, itr->second);
            ++itr;
        }
    }

    // remove auras from units no longer needing them
    for (UnitList::iterator itr = targetsToRemove.begin(); itr != targetsToRemove.end();++itr)
        if (AuraApplication * aurApp = GetApplicationOfTarget((*itr)->GetGUID()))
            (*itr)->_UnapplyAura(aurApp, AURA_REMOVE_BY_DEFAULT);

    if (!apply)
        return;

    // apply aura effects for units
    for (std::map<Unit*, uint8>::iterator itr = targets.begin(); itr!= targets.end();++itr)
    {
        if (AuraApplication * aurApp = GetApplicationOfTarget(itr->first->GetGUID()))
        {
            // owner has to be in world, or effect has to be applied to self
            ASSERT((!GetOwner()->IsInWorld() && GetOwner() == itr->first) || GetOwner()->IsInMap(itr->first));
            itr->first->_ApplyAura(aurApp, itr->second);
        }
    }
}

// targets have to be registered and not have effect applied yet to use this function
void Aura::_ApplyEffectForTargets(uint8 effIndex)
{
    // prepare list of aura targets
    UnitList targetList;
    for (ApplicationMap::iterator appIter = m_applications.begin(); appIter != m_applications.end(); ++appIter)
    {
        if ((appIter->second->GetEffectsToApply() & (1<<effIndex)) && !appIter->second->HasEffect(effIndex))
            targetList.push_back(appIter->second->GetTarget());
    }

    // apply effect to targets
    for (UnitList::iterator itr = targetList.begin(); itr != targetList.end(); ++itr)
    {
        if (GetApplicationOfTarget((*itr)->GetGUID()))
        {
            // owner has to be in world, or effect has to be applied to self
            ASSERT((!GetOwner()->IsInWorld() && GetOwner() == *itr) || GetOwner()->IsInMap(*itr));
            (*itr)->_ApplyAuraEffect(this, effIndex);
        }
    }
}
void Aura::UpdateOwner(uint32 diff, WorldObject* owner)
{
    ASSERT(owner == m_owner);

    Unit* caster = GetCaster();
    // Apply spellmods for channeled auras
    // used for example when triggered spell of spell:10 is modded
    Spell* modSpell = NULL;
    Player* modOwner = NULL;
    if (caster)
    {
        modOwner = caster->GetSpellModOwner();
        if (modOwner)
        {
            modSpell = modOwner->FindCurrentSpellBySpellId(GetId());
            if (modSpell)
                modOwner->SetSpellModTakingSpell(modSpell, true);
        }
    }

    Update(diff, caster);

    if (m_updateTargetMapInterval <= int32(diff))
        UpdateTargetMap(caster);
    else
        m_updateTargetMapInterval -= diff;

    // update aura effects
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
        if (m_effects[i])
            m_effects[i]->Update(diff, caster);

    // remove spellmods after effects update
    if (modSpell)
        modOwner->SetSpellModTakingSpell(modSpell, false);

    _DeleteRemovedApplications();
}

void Aura::Update(uint32 diff, Unit* caster)
{
    if (m_duration > 0)
    {
        m_duration -= diff;
        if (m_duration < 0)
            m_duration = 0;

        // handle manaPerSecond/manaPerSecondPerLevel
        if (m_timeCla)
        {
            if (m_timeCla > int32(diff))
                m_timeCla -= diff;
            else if (caster)
            {
                if (int32 manaPerSecond = m_spellInfo->ManaPerSecond)
                {
                    m_timeCla += 1000 - diff;

                    Powers powertype = Powers(m_spellInfo->PowerType);
                    if (powertype == POWER_HEALTH)
                    {
                        if (int32(caster->GetHealth()) > manaPerSecond)
                            caster->ModifyHealth(-manaPerSecond);
                        else
                        {
                            Remove();
                            return;
                        }
                    }
                    else
                    {
                        if (int32(caster->GetPower(powertype)) >= manaPerSecond)
                            caster->ModifyPower(powertype, -manaPerSecond);
                        else
                        {
                            Remove();
                            return;
                        }
                    }
                }
            }
        }
    }
}

int32 Aura::CalcMaxDuration(Unit* caster) const
{
    Player* modOwner = NULL;
    int32 maxDuration;

    if (caster)
    {
        modOwner = caster->GetSpellModOwner();
        maxDuration = caster->CalcSpellDuration(m_spellInfo);
    }
    else
        maxDuration = m_spellInfo->GetDuration();

    if (IsPassive() && !m_spellInfo->DurationEntry)
        maxDuration = -1;

    // IsPermanent() checks max duration (which we are supposed to calculate here)
    if (maxDuration != -1 && modOwner)
        modOwner->ApplySpellMod(GetId(), SPELLMOD_DURATION, maxDuration);
    return maxDuration;
}

void Aura::SetDuration(int32 duration, bool withMods)
{
    if (withMods)
    {
        if (Unit* caster = GetCaster())
            if (Player* modOwner = caster->GetSpellModOwner())
                modOwner->ApplySpellMod(GetId(), SPELLMOD_DURATION, duration);
    }
    m_duration = duration;
    SetNeedClientUpdateForTargets();
}

void Aura::RefreshDuration()
{
    SetDuration(GetMaxDuration());

    if (m_spellInfo->ManaPerSecond)
        m_timeCla = 1 * IN_MILLISECONDS;
}

void Aura::RefreshTimers()
{
    m_maxDuration = CalcMaxDuration();
    bool resetPeriodic = true;
    if (m_spellInfo->AttributesEx8 & SPELL_ATTR8_DONT_RESET_PERIODIC_TIMER)
    {
        int32 minAmplitude = m_maxDuration;
        for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
            if (AuraEffect const* eff = GetEffect(i))
                if (int32 ampl = eff->GetAmplitude())
                    minAmplitude = std::min(ampl, minAmplitude);

        // If only one tick remaining, roll it over into new duration
        if (GetDuration() <= minAmplitude)
        {
            m_maxDuration += GetDuration();
            resetPeriodic = false;
        }
    }

    RefreshDuration();
    Unit* caster = GetCaster();
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
        if (HasEffect(i))
            GetEffect(i)->CalculatePeriodic(caster, resetPeriodic, false);
}

void Aura::SetCharges(uint8 charges)
{
    if (m_procCharges == charges)
        return;
    m_procCharges = charges;
    m_isUsingCharges = m_procCharges != 0;
    SetNeedClientUpdateForTargets();
}

uint8 Aura::CalcMaxCharges(Unit* caster) const
{
    uint32 maxProcCharges = m_spellInfo->ProcCharges;
    if (SpellProcEntry const* procEntry = sSpellMgr->GetSpellProcEntry(GetId()))
        maxProcCharges = procEntry->charges;

    if (caster)
        if (Player* modOwner = caster->GetSpellModOwner())
            modOwner->ApplySpellMod(GetId(), SPELLMOD_CHARGES, maxProcCharges);
    return uint8(maxProcCharges);
}

bool Aura::ModCharges(int32 num, AuraRemoveMode removeMode)
{
    if (IsUsingCharges())
    {
        int32 charges = m_procCharges + num;
        int32 maxCharges = CalcMaxCharges();

        // limit charges (only on charges increase, charges may be changed manually)
        if ((num > 0) && (charges > int32(maxCharges)))
            charges = maxCharges;
        // we're out of charges, remove
        else if (charges <= 0)
        {
            Remove(removeMode);
            return true;
        }

        SetCharges(charges);
    }
    return false;
}

void Aura::SetStackAmount(uint8 stackAmount)
{
    m_stackAmount = stackAmount;
    Unit* caster = GetCaster();

    std::list<AuraApplication*> applications;
    GetApplicationList(applications);

    for (std::list<AuraApplication*>::const_iterator apptItr = applications.begin(); apptItr != applications.end(); ++apptItr)
        if (!(*apptItr)->GetRemoveMode())
            HandleAuraSpecificMods(*apptItr, caster, false, true);

    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
        if (HasEffect(i))
            m_effects[i]->ChangeAmount(m_effects[i]->CalculateAmount(caster), false, true);

    for (std::list<AuraApplication*>::const_iterator apptItr = applications.begin(); apptItr != applications.end(); ++apptItr)
        if (!(*apptItr)->GetRemoveMode())
            HandleAuraSpecificMods(*apptItr, caster, true, true);

    SetNeedClientUpdateForTargets();
}

bool Aura::ModStackAmount(int32 num, AuraRemoveMode removeMode)
{
    int32 stackAmount = m_stackAmount + num;

    // limit the stack amount (only on stack increase, stack amount may be changed manually)
    if ((num > 0) && (stackAmount > int32(m_spellInfo->StackAmount)))
    {
        // not stackable aura - set stack amount to 1
        if (!m_spellInfo->StackAmount)
            stackAmount = 1;
        else
            stackAmount = m_spellInfo->StackAmount;
    }
    // we're out of stacks, remove
    else if (stackAmount <= 0)
    {
        Remove(removeMode);
        return true;
    }

    bool refresh = stackAmount >= GetStackAmount();

    // Update stack amount
    SetStackAmount(stackAmount);

    if (refresh)
    {
        RefreshSpellMods();
        RefreshTimers();

        // reset charges
        SetCharges(CalcMaxCharges());
        // FIXME: not a best way to synchronize charges, but works
        for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
            if (AuraEffect* aurEff = GetEffect(i))
                if (aurEff->GetAuraType() == SPELL_AURA_ADD_FLAT_MODIFIER || aurEff->GetAuraType() == SPELL_AURA_ADD_PCT_MODIFIER)
                    if (SpellModifier* mod = aurEff->GetSpellModifier())
                        mod->charges = GetCharges();
    }
    SetNeedClientUpdateForTargets();
    return false;
}

void Aura::RefreshSpellMods()
{
    for (Aura::ApplicationMap::const_iterator appIter = m_applications.begin(); appIter != m_applications.end(); ++appIter)
        if (Player* player = appIter->second->GetTarget()->ToPlayer())
            player->RestoreAllSpellMods(0, this);
}

bool Aura::IsArea() const
{
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
    {
        if (HasEffect(i) && GetSpellInfo()->Effects[i].IsAreaAuraEffect())
            return true;
    }
    return false;
}

bool Aura::IsPassive() const
{
    return GetSpellInfo()->IsPassive();
}

bool Aura::IsDeathPersistent() const
{
    return GetSpellInfo()->IsDeathPersistent();
}

bool Aura::CanBeSaved() const
{
    if (IsPassive())
        return false;

    if (GetCasterGUID() != GetOwner()->GetGUID())
        if (GetSpellInfo()->IsSingleTarget())
            return false;

    // Can't be saved - aura handler relies on calculated amount and changes it
    if (HasEffectType(SPELL_AURA_CONVERT_RUNE))
        return false;

    // No point in saving this, since the stable dialog can't be open on aura load anyway.
    if (HasEffectType(SPELL_AURA_OPEN_STABLE))
        return false;

    // Can't save vehicle auras, it requires both caster & target to be in world
    if (HasEffectType(SPELL_AURA_CONTROL_VEHICLE))
        return false;

    // Incanter's Absorbtion - considering the minimal duration and problems with aura stacking
    // we skip saving this aura
    // Also for some reason other auras put as MultiSlot crash core on keeping them after restart,
    // so put here only these for which you are sure they get removed
    switch (GetId())
    {
        case 44413: // Incanter's Absorption
        case 40075: // Fel Flak Fire
        case 55849: // Power Spark
        // Don't save special liquid auras 
        case 57634: // Magma, CoA Black / Chamber 
        case 42201: // Water, Hyjal Past 
        case 37025: // Water, Coilfang Raid 
        case 36444: // Water, Lake Wintergrasp 
        case 28801: // Slime, Naxxramas 
            return false;
    }

    // When a druid logins, he doesnt have either eclipse power, nor the marker auras, nor the eclipse buffs. Dont save them.
    /*if (GetId() == 67483 || GetId() == 67484 || GetId() == 48517 || GetId() == 48518)
        return false;*/

    // don't save auras removed by proc system
    if (IsUsingCharges() && !GetCharges())
        return false;

    return true;
}

bool Aura::CanBeSentToClient() const
{
    return !IsPassive() || GetSpellInfo()->HasAreaAuraEffect() || HasEffectType(SPELL_AURA_ABILITY_IGNORE_AURASTATE) || HasEffectType(SPELL_AURA_CAST_WHILE_WALKING);
}

bool Aura::IsSingleTargetWith(Aura const* aura) const
{
    // Same spell?
    if (GetSpellInfo()->IsRankOf(aura->GetSpellInfo()))
        return true;

    SpellSpecificType spec = GetSpellInfo()->GetSpellSpecific();
    // spell with single target specific types
    switch (spec)
    {
        case SPELL_SPECIFIC_JUDGEMENT:
        case SPELL_SPECIFIC_MAGE_POLYMORPH:
            if (aura->GetSpellInfo()->GetSpellSpecific() == spec)
                return true;
            break;
        default:
            break;
    }

    if (HasEffectType(SPELL_AURA_CONTROL_VEHICLE) && aura->HasEffectType(SPELL_AURA_CONTROL_VEHICLE))
        return true;

    return false;
}

void Aura::UnregisterSingleTarget()
{
    ASSERT(m_isSingleTarget);
    Unit* caster = GetCaster();
    /// @todo find a better way to do this.
    if (!caster)
        caster = ObjectAccessor::GetObjectInOrOutOfWorld(GetCasterGUID(), (Unit*)NULL);
    ASSERT(caster);
    caster->GetSingleCastAuras().remove(this);
    SetIsSingleTarget(false);
}

int32 Aura::CalcDispelChance(Unit* auraTarget, bool offensive) const
{
    // we assume that aura dispel chance is 100% on start
    // need formula for level difference based chance
    int32 resistChance = 0;

    // Apply dispel mod from aura caster
    if (Unit* caster = GetCaster())
        if (Player* modOwner = caster->GetSpellModOwner())
            modOwner->ApplySpellMod(GetId(), SPELLMOD_RESIST_DISPEL_CHANCE, resistChance);

    // Dispel resistance from target SPELL_AURA_MOD_DISPEL_RESIST
    // Only affects offensive dispels
    if (offensive && auraTarget)
        resistChance += auraTarget->GetTotalAuraModifier(SPELL_AURA_MOD_DISPEL_RESIST);

    RoundToInterval(resistChance, 0, 100);
    return 100 - resistChance;
}

void Aura::SetLoadedState(int32 maxduration, int32 duration, int32 charges, uint8 stackamount, uint8 recalculateMask, int32 * amount)
{
    m_maxDuration = maxduration;
    m_duration = duration;
    m_procCharges = charges;
    m_isUsingCharges = m_procCharges != 0;
    m_stackAmount = stackamount;
    Unit* caster = GetCaster();
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
        if (m_effects[i])
        {
            m_effects[i]->SetAmount(amount[i]);
            m_effects[i]->SetCanBeRecalculated(recalculateMask & (1<<i));
            m_effects[i]->CalculatePeriodic(caster, false, true);
            m_effects[i]->CalculateSpellMod();
            m_effects[i]->RecalculateAmount(caster);
        }
}

bool Aura::HasEffectType(AuraType type) const
{
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
    {
        if (HasEffect(i) && m_effects[i]->GetAuraType() == type)
            return true;
    }
    return false;
}

void Aura::RecalculateAmountOfEffects()
{
    ASSERT (!IsRemoved());
    Unit* caster = GetCaster();
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
        if (HasEffect(i))
            m_effects[i]->RecalculateAmount(caster);
}

void Aura::HandleAllEffects(AuraApplication * aurApp, uint8 mode, bool apply)
{
    ASSERT (!IsRemoved());
    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
        if (m_effects[i] && !IsRemoved())
            m_effects[i]->HandleEffect(aurApp, mode, apply);
}

void Aura::GetApplicationList(std::list<AuraApplication*> & applicationList) const
{
    for (Aura::ApplicationMap::const_iterator appIter = m_applications.begin(); appIter != m_applications.end(); ++appIter)
    {
        if (appIter->second->GetEffectMask())
            applicationList.push_back(appIter->second);
    }
}

void Aura::SetNeedClientUpdateForTargets() const
{
    for (ApplicationMap::const_iterator appIter = m_applications.begin(); appIter != m_applications.end(); ++appIter)
        appIter->second->SetNeedClientUpdate();
}

// trigger effects on real aura apply/remove
void Aura::HandleAuraSpecificMods(AuraApplication const* aurApp, Unit* caster, bool apply, bool onReapply)
{
    Unit* target = aurApp->GetTarget();
    AuraRemoveMode removeMode = aurApp->GetRemoveMode();
    // handle spell_area table
    SpellAreaForAreaMapBounds saBounds = sSpellMgr->GetSpellAreaForAuraMapBounds(GetId());
    if (saBounds.first != saBounds.second)
    {
        uint32 zone, area;
        target->GetZoneAndAreaId(zone, area);

        for (SpellAreaForAreaMap::const_iterator itr = saBounds.first; itr != saBounds.second; ++itr)
        {
            // some auras remove at aura remove
            if (!itr->second->IsFitToRequirements(target->ToPlayer(), zone, area))
                target->RemoveAurasDueToSpell(itr->second->spellId);
            // some auras applied at aura apply
            else if (itr->second->autocast)
            {
                if (!target->HasAura(itr->second->spellId))
                    target->CastSpell(target, itr->second->spellId, true);
            }
        }
    }

    // handle spell_linked_spell table
    if (!onReapply)
    {
        // apply linked auras
        if (apply)
        {
            if (std::vector<int32> const* spellTriggered = sSpellMgr->GetSpellLinked(GetId() + SPELL_LINK_AURA))
            {
                for (std::vector<int32>::const_iterator itr = spellTriggered->begin(); itr != spellTriggered->end(); ++itr)
                {
                    if (*itr < 0)
                        target->ApplySpellImmune(GetId(), IMMUNITY_ID, -(*itr), true);
                    else if (caster)
                        caster->AddAura(*itr, target);
                }
            }
        }
        else
        {
            // remove linked auras
            if (std::vector<int32> const* spellTriggered = sSpellMgr->GetSpellLinked(-(int32)GetId()))
            {
                for (std::vector<int32>::const_iterator itr = spellTriggered->begin(); itr != spellTriggered->end(); ++itr)
                {
                    if (*itr < 0)
                        target->RemoveAurasDueToSpell(-(*itr));
                    else if (removeMode != AURA_REMOVE_BY_DEATH)
                        target->CastSpell(target, *itr, true, NULL, NULL, GetCasterGUID());
                }
            }
            if (std::vector<int32> const* spellTriggered = sSpellMgr->GetSpellLinked(GetId() + SPELL_LINK_AURA))
            {
                for (std::vector<int32>::const_iterator itr = spellTriggered->begin(); itr != spellTriggered->end(); ++itr)
                {
                    if (*itr < 0)
                        target->ApplySpellImmune(GetId(), IMMUNITY_ID, -(*itr), false);
                    else
                        target->RemoveAura(*itr, GetCasterGUID(), 0, removeMode);
                }
            }
        }
    }
    else if (apply)
    {
        // modify stack amount of linked auras
        if (std::vector<int32> const* spellTriggered = sSpellMgr->GetSpellLinked(GetId() + SPELL_LINK_AURA))
        {
            for (std::vector<int32>::const_iterator itr = spellTriggered->begin(); itr != spellTriggered->end(); ++itr)
                if (*itr > 0)
                    if (Aura* triggeredAura = target->GetAura(*itr, GetCasterGUID()))
                        triggeredAura->ModStackAmount(GetStackAmount() - triggeredAura->GetStackAmount());
        }
    }

    // mods at aura apply
    if (apply)
    {
        switch (GetSpellInfo()->SpellFamilyName)
        {
            case SPELLFAMILY_GENERIC:
                switch (GetId())
                {
                    case 32474: // Buffeting Winds of Susurrus
                        if (target->GetTypeId() == TYPEID_PLAYER)
                            target->ToPlayer()->ActivateTaxiPathTo(506, GetId());
                        break;
                    case 33572: // Gronn Lord's Grasp, becomes stoned
                        if (GetStackAmount() >= 5 && !target->HasAura(33652))
                            target->CastSpell(target, 33652, true);
                        break;
                    case 50836: //Petrifying Grip, becomes stoned
                        if (GetStackAmount() >= 5 && !target->HasAura(50812))
                            target->CastSpell(target, 50812, true);
                        break;
                }
                break;
            case SPELLFAMILY_DRUID:
                if (!caster)
                    break;
                // Rejuvenation
                if (GetSpellInfo()->SpellFamilyFlags[0] & 0x10 && GetEffect(EFFECT_0))
                {
                    // Druid T8 Restoration 4P Bonus
                    if (caster->HasAura(64760))
                    {
                        int32 heal = GetEffect(EFFECT_0)->GetAmount();
                        caster->CastCustomSpell(target, 64801, &heal, NULL, NULL, true, NULL, GetEffect(EFFECT_0));
                    }
                }
                switch (GetId())
                {
                    case 93400: // Shooting Stars
                    {
                        // Reset cooldown on Starsurge
                        caster->ToPlayer()->RemoveSpellCooldown(78674, true);
                        break;
                    }
                }
                break;
            case SPELLFAMILY_MAGE:
                if (!caster)
                    break;
                /// @todo This should be moved to similar function in spell::hit
                if (GetSpellInfo()->SpellFamilyFlags[0] & 0x01000000)
                {
                    // Polymorph Sound - Sheep && Penguin
                    if (GetSpellInfo()->SpellIconID == 82 && GetSpellInfo()->SpellVisual[0] == 12978)
                    {
                        // Glyph of the Penguin
                        if (caster->HasAura(52648))
                            caster->CastSpell(target, 61635, true);
                        else
                            caster->CastSpell(target, 61634, true);
                    }
                }
                switch (GetId())
                {
                    case 12536: // Clearcasting
                    case 12043: // Presence of Mind
                        // Arcane Potency
                        if (AuraEffect const* aurEff = caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_MAGE, 2120, 0))
                        {
                            uint32 spellId = 0;

                            switch (aurEff->GetId())
                            {
                                case 31571: spellId = 57529; break;
                                case 31572: spellId = 57531; break;
                                default:
                                    TC_LOG_ERROR("spells", "Aura::HandleAuraSpecificMods: Unknown rank of Arcane Potency (%d) found", aurEff->GetId());
                            }
                            if (spellId)
                                caster->CastSpell(caster, spellId, true);
                        }
                        break;
                    case 64343: // Impact
                    {
                        // Reset cooldown on Fire Blast
                        if (Player* player = caster->ToPlayer())
                            player->RemoveSpellCooldown(2136, true);
                        break;
                    }
                    default:
                        break;
                }
                break;
            case SPELLFAMILY_HUNTER:
                if (!caster)
                    break;

                switch (GetId())
                {
                    // Improved Serpent Sting
                    case 1978:
                    {
                        if (AuraEffect* aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_HUNTER, 536, 0))
                        {
                            SpellInfo const* SerpentSpell = sSpellMgr->GetSpellInfo(1978);
                            int32 bp = (caster->SpellDamageBonusDone(target, SerpentSpell, SerpentSpell->Effects[0].CalcValue(caster), DOT)) * aurEff->GetAmount() / 100;
                            caster->CastCustomSpell(target, 83077, &bp, NULL, NULL, true);
                        }
                        break;
                    }
                    // Rapid Recuperation 
                    case 35098:
                    case 35099:
                    {
                        if (AuraEffect* aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_HUNTER, 3560, 1))
                        {
                            int32 bp = aurEff->GetAmount();
                            caster->CastCustomSpell(caster,58883,&bp,NULL,NULL,true);
                        }
                        break;
                    }
                    case 82692: // Focus fire
                    {
                        if (Pet *pet = caster->ToPlayer()->GetPet())
                            if (pet->HasAura(19615))
                            {
                                int32 bp = pet->GetAura(19615)->GetStackAmount() * 3;
                                // int32 bp2 = 4;
                                caster->GetAura(82692)->GetEffect(EFFECT_0)->SetAmount(bp);
                                caster->CastCustomSpell(pet,83468,&bp,NULL,NULL,true);
                                pet->RemoveAurasDueToSpell(19615);
                            }
                        break;
                    }
                    case 82925: // Master Marksman
                    {
                        if (target->GetTypeId() == TYPEID_PLAYER && GetStackAmount() == 5)
                        {
                            target->CastSpell(target, 82926, true);
                            target->RemoveAura(82925);
                        }
                        break;
                    }
                }
                break;
            case SPELLFAMILY_PRIEST:
                if (!caster)
                    break;
                // Prayer of Mending
                if (GetId() == 41635)
                {
                    if (caster->HasAura(14751))
                    {
                        caster->CastSpell(caster, 81206, true); // Chakra: Sanctuary
                        caster->RemoveAurasDueToSpell(14751);
                    }
                }
                // Mind spike
                else if (GetId() == 87178)
                {
                    if (caster->HasAura(14751))
                    {
                        caster->CastSpell(caster, 81209, true); // Chakra: Chastise
                        caster->RemoveAurasDueToSpell(14751);
                    }
                }
                // Devouring Plague
                else if (GetId() == 2944)
                {
                    // Improved Devouring Plague
                    if (AuraEffect const* aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_PRIEST, 3790, 0))
                    {
                        int32 basepoints0 = aurEff->GetAmount() * GetEffect(0)->GetTotalTicks() * caster->SpellDamageBonusDone(target, GetSpellInfo(), GetEffect(0)->GetAmount(), DOT) / 100;

                        caster->CastCustomSpell(target, 63675, &basepoints0, NULL, NULL, true, NULL, GetEffect(0));
                    }
                }
                // Renew
                else if (GetId() == 139)
                {
                    // Empowered Renew
                    if (AuraEffect const * aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_PRIEST, 3021, 0))
                    {
                        int32 basepoints0 = aurEff->GetAmount() * GetEffect(0)->GetTotalTicks() * caster->SpellHealingBonusDone(target, GetSpellInfo(), GetEffect(0)->GetAmount(), HEAL) / 100;
                        caster->CastCustomSpell(target, 63544, &basepoints0, NULL, NULL, true, NULL, GetEffect(0));
                    }
                }
                // Power Word: Shield
                else if (GetId() == 17) 
                {
                    //Body and Soul rank 2
                    if(caster->HasAura(64129))
                        caster->CastSpell(target, 65081,true);
                    //Body and Soul rank 1
                    if(caster->HasAura(64127))
                        caster->CastSpell(target, 64128,true);
                    // Glyph of Power Word: Shield
                    if (AuraEffect* glyph = caster->GetAuraEffect(55672, 0))
                    {
                        // instantly heal m_amount% of the absorb-value
                        int32 heal = glyph->GetAmount() * GetEffect(0)->GetAmount()/100;
                        caster->CastCustomSpell(GetUnitOwner(), 56160, &heal, NULL, NULL, true, 0, GetEffect(0));
                    }
                }
                // Inner Focus
                else if (GetId() == 89485)
                {
                     // Strength of Soul rank 1
                     if (caster->HasAura(89488))
                         caster->CastSpell(caster, 96266,true);
                     // Strenght of Soul rank 2
                     else if (caster->HasAura(89489))
                         caster->CastSpell(caster, 96267,true);
                }
                // Phantasm
                else if (GetId() == 586)
                {
                    if ((target->HasAura(47569) && roll_chance_i(50)) || target->HasAura(47570))
                        target->RemoveMovementImpairingAuras();
                }
                break;
            case SPELLFAMILY_ROGUE:
                // Glyph of blind
                if (GetId() == 2094)
                    if (caster->HasAura(91299))
                        target->RemoveAurasByType(SPELL_AURA_PERIODIC_DAMAGE);

                // Sprint (skip non player cast spells by category)
                if (GetSpellInfo()->SpellFamilyFlags[0] & 0x40 && GetSpellInfo()->GetCategory() == 44)
                    // in official maybe there is only one icon?
                    if (target->HasAura(58039)) // Glyph of Blurred Speed
                        target->CastSpell(target, 61922, true); // Sprint (waterwalk)

                // Deadly Momentum
                if (GetId() == 84590)
                {
                    if (Aura* snd = target->GetAura(5171))
                        snd->RefreshDuration();
                    if (Aura* rec = target->GetAura(73651))
                        rec->RefreshDuration();
                }

                //Savage Combat
                if (GetSpellInfo()->Dispel == DISPEL_POISON && (GetSpellInfo()->SchoolMask & SPELL_SCHOOL_MASK_NATURE) && GetSpellInfo()->DmgClass == SPELL_DAMAGE_CLASS_MAGIC)
                    if (caster && target && caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (caster->HasAura(51682))
                            caster->CastSpell(target,58684,true);
                        else if (caster->HasAura(58413))
                            caster->CastSpell(target,58683,true);
                    }
                break;
            case SPELLFAMILY_PALADIN: // Speed of Light (talent)
                if (GetId() == 498)
                {
                    int32 bp = 0;
                    if (target->HasAura(85495)) // r1
                    {
                        bp = 20;
                        target->CastCustomSpell(target, 85497, &bp, NULL, NULL, true);
                    }
                    if (target->HasAura(85498)) // r2
                    {
                        bp = 40;
                        target->CastCustomSpell(target, 85497, &bp, NULL, NULL, true);
                    }
                    if (target->HasAura(85499)) // r3
                    {
                        bp = 60;
                        target->CastCustomSpell(target, 85497, &bp, NULL, NULL, true);
                    }
                }
                // Inquisition
                if (m_spellInfo->Id == 84963) // Inquisition
                {
                    // Divine Purpose
                    if (target->HasAura(90174))
                        target->SetPower(POWER_HOLY_POWER, 0);
                }

                // Sanctfied Wrath Cataclysm proc
                if (GetId() == 31884)
                    if (caster->HasAura(53375) || caster->HasAura(53376) || caster->HasAura(90286))
                        caster->CastSpell(caster,57318,true);
                break;
            case SPELLFAMILY_WARLOCK:
                //Nether ward
                if (GetId() == 28176 || GetId() == 687)
                {
                    if (caster->HasAura(91713))
                        caster->GetAura(GetId())->GetEffect(2)->ChangeAmount(91711);
                }
                // Soul link glyph
                else if (GetId() == 25228 && caster->IsPet())
                {
                    if (caster->GetOwner()->HasAura(63312))
                        caster->GetOwner()->GetAura(GetId())->GetEffect(0)->ChangeAmount(25);
                }
                break;
            case SPELLFAMILY_WARRIOR:
                // Heroic Fury (remove Intercept cooldown)
                if (GetId() == 60970)
                    if (target->GetTypeId() == TYPEID_PLAYER)
                        target->ToPlayer()->RemoveSpellCooldown(20252, true);
                break;
            case SPELLFAMILY_DEATHKNIGHT:
                // Dark transformation - shadow infusion
                if (GetId() == 91342)
                    if (GetStackAmount() >= 5)
                    {
                        caster->CastSpell(caster, 93426, true);
                        target->RemoveAurasDueToSpell(91342); // Remove all shadow infusions
                        target->ApplySpellImmune(GetId(), IMMUNITY_ID, 91342, apply);
                    }

                if (GetId() == 63560) //Dark transformation, on cast remove the aura
                    if (target->ToCreature()->IsPet())
                        target->ToCreature()->GetOwner()->RemoveAurasDueToSpell(93426);

                // Chains of Ice
                if (GetId() == 45524)
                {
                    if (caster->HasAura(50040))
                        caster->CastSpell(target, 96293, true);
                    else if (caster->HasAura(50041))
                        caster->CastSpell(target, 96294, true);

                    // Ebon Plaguebringer
                    if (AuraEffect const * aurEff = caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_DEATHKNIGHT, 1766, 0))
                    {
                        int32 bp = aurEff->GetAmount();
                        caster->CastCustomSpell(target, 65142, &bp, NULL, NULL, true);
                    }
                }
                // Necrotic strike
                if (GetId() == 73975)
                {
                    int32 amount = caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.7f;
                    target->GetAura(GetId())->GetEffect(EFFECT_0)->ChangeAmount(amount);
                }
                break;
            default:
                break;
        }
        
        // Pursuit of Justice
        if (GetSpellInfo()->GetAllEffectsMechanicMask() & ((1<<MECHANIC_ROOT)|(1<<MECHANIC_STUN) |(1<<MECHANIC_FEAR)))
            if ((target->HasAura(26022) && roll_chance_i(50)) || target->HasAura(26023))
                target->CastSpell(target,89024,true);
    }
    // mods at aura remove
    else
    {
        switch (GetSpellInfo()->SpellFamilyName)
        {
            case SPELLFAMILY_GENERIC:
                switch (GetId())
                {
                    case 61987: // Avenging Wrath
                        // Remove the immunity shield marker on Avenging Wrath removal if Forbearance is not present
                        if (target->HasAura(61988) && !target->HasAura(25771))
                            target->RemoveAura(61988);
                        break;
                    case 72368: // Shared Suffering
                    case 72369:
                        if (caster)
                        {
                            if (AuraEffect* aurEff = GetEffect(0))
                            {
                                int32 remainingDamage = aurEff->GetAmount() * (aurEff->GetTotalTicks() - aurEff->GetTickNumber());
                                if (remainingDamage > 0)
                                    caster->CastCustomSpell(caster, 72373, NULL, &remainingDamage, NULL, true);
                            }
                        }
                        break;
                    case 79582: // Magmatron barrier
                        if (caster)
                        {
                            if (removeMode == AURA_REMOVE_BY_EXPIRE)
                            break;

                            caster->CastSpell(caster, 79617, true);
                        }
                        break;
                    case 93103: // Corruption Cho'gall
                        if (target->HasAura(81836))
                            target->RemoveAura(81836);
                        if (target->HasAura(81829))
                            target->RemoveAura(81829);
                        if (target->HasAura(82125))
                        {
                            target->RemoveAura(82125);
                            if(Creature* malformation = target->FindNearestCreature(43888,20.0f,true))
                            malformation->DisappearAndDie();
                        }
                        if (target->HasAura(82167))
                            target->RemoveAura(82167);
                        if (target->HasAura(82193))
                            target->RemoveAura(82193);
                        if (target->HasAura(82170))
                            target->RemoveAura(82170);
                        break;
                }
                break;
            case SPELLFAMILY_MAGE:
                if (!caster)
                    break;
                switch (GetId())
                {
                    case 66: // Invisibility
                        if (removeMode != AURA_REMOVE_BY_EXPIRE)
                            break;
                        target->CastSpell(target, 32612, true, NULL, GetEffect(1));
                        target->CombatStop();
                        break;
                    case 11426: // Shattered Barrier
                        if (removeMode != AURA_REMOVE_BY_ENEMY_SPELL)
                            break;
                        if (target->HasAura(44745))
                            target->CastSpell(target,55080,true);
                        else if (target->HasAura(54787))
                            target->CastSpell(target,83073,true);
                        break;
                    case 44401: //Missile Barrage
                    case 48108: //Hot Streak
                    case 57761: //Fireball
                        if (removeMode != AURA_REMOVE_BY_EXPIRE || aurApp->GetBase()->IsExpired())
                            break;
                        if (target->HasAura(70752))          //Item - Mage T10 2P Bonus
                            target->CastSpell(target, 70753, true);
                        break;
                    default:
                        break;
                }
                break;
            case SPELLFAMILY_WARLOCK:
                if (!caster)
                    break;
                // Curse of Doom
                if (GetSpellInfo()->SpellFamilyFlags[1] & 0x02)
                {
                    if (removeMode == AURA_REMOVE_BY_DEATH)
                    {
                        if (caster->GetTypeId() == TYPEID_PLAYER && caster->ToPlayer()->isHonorOrXPTarget(target))
                            caster->CastSpell(target, 18662, true, NULL, GetEffect(0));
                    }
                }
                // Improved Fear
                else if (GetSpellInfo()->SpellFamilyFlags[1] & 0x00000400)
                {
                    if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_WARLOCK, 98, 0))
                    {
                        uint32 spellId = 0;
                        switch (aurEff->GetId())
                        {
                            case 53759: spellId = 60947; break;
                            case 53754: spellId = 60946; break;
                            default:
                                TC_LOG_ERROR("spells", "Aura::HandleAuraSpecificMods: Unknown rank of Improved Fear (%d) found", aurEff->GetId());
                        }
                        if (spellId)
                            caster->CastSpell(target, spellId, true);
                    }
                }
                // Seed of corruption
                else if (GetSpellInfo()->Id == 27243 && removeMode == AURA_REMOVE_BY_DEATH)
                    caster->CastSpell(target, 27285, true);
                break;
            case SPELLFAMILY_PRIEST:
                if (!caster)
                    break;

                if ((removeMode == AURA_REMOVE_BY_ENEMY_SPELL || removeMode == AURA_REMOVE_BY_EXPIRE) && GetSpellInfo()->SpellFamilyFlags[0] & 0x00000001 && caster)
                {
                    if (AuraEffect const * aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_PRIEST, 2894, 0))
                        if (!caster->ToPlayer()->HasSpellCooldown(47755))
                        {
                            int32 basepoints0 = int32(aurEff->GetAmount() * caster->GetMaxPower(POWER_MANA) / 100);
                            caster->CastCustomSpell(caster, 47755, &basepoints0, NULL, NULL, true);
                            caster->ToPlayer()->AddSpellCooldown(47755, 0, time(NULL) + 12);
                        }
                }
                break;
            case SPELLFAMILY_ROGUE:
                // After remove Vanish set in stealth
                if (GetId() == 11327)
                    target->AddAura(1784, target);

                // Venomous Wounds
                if (GetId() == 1943 && removeMode == AURA_REMOVE_BY_DEATH)
                    if (caster->HasAura(79133) || caster->HasAura(79134))
                    {
                        int32 bp = GetDuration() / 1000;
                        caster->CastCustomSpell(caster, 51637, &bp, NULL, NULL, true);
                    }

                    //if (GetEffect(0)->GetTickNumber() * this->GetDuration();)
                // On-sap removal - blackjack talent
                if (GetId() == 6770)
                {
                    if (target && caster)
                    {
                        if (caster->HasAura(79125))          // rank 2
                            caster->CastSpell(target, 79126, true);
                        else if (caster->HasAura(79123))          // rank 1
                            caster->CastSpell(target, 79124, true);
                    }
                }

                //Savage Combat
                if (GetSpellInfo()->Dispel == DISPEL_POISON && (GetSpellInfo()->SchoolMask & SPELL_SCHOOL_MASK_NATURE) && GetSpellInfo()->DmgClass == SPELL_DAMAGE_CLASS_MAGIC)
                {
                    if (target->HasAura(58684))
                        target->RemoveAura(58684);
                    else if (target->HasAura(58683))
                        target->RemoveAura(58683);
                }
                break;
            case SPELLFAMILY_PALADIN:
                // Remove the immunity shield marker on Forbearance removal if AW marker is not present
                if (GetId() == 25771 && target->HasAura(61988) && !target->HasAura(61987))
                    target->RemoveAura(61988);

                // Guardian of ancient king
                if (GetId() == 86674)
                    if (Unit *caster = GetCaster())
                        caster->ToTempSummon()->DespawnOrUnsummon();
                break;
            case SPELLFAMILY_DEATHKNIGHT:
                // Blood of the North
                // Reaping
                // Blood Rites
                // Death Rune Mastery
                if (GetSpellInfo()->SpellIconID == 3041 || GetSpellInfo()->SpellIconID == 22 || GetSpellInfo()->SpellIconID == 2622 || GetSpellInfo()->SpellIconID == 2724)
                {
                    if (!GetEffect(0) || GetEffect(0)->GetAuraType() != SPELL_AURA_PERIODIC_DUMMY)
                        break;
                    if (target->GetTypeId() != TYPEID_PLAYER)
                        break;
                    if (target->ToPlayer()->getClass() != CLASS_DEATH_KNIGHT)
                        break;

                     // aura removed - remove death runes
                    target->ToPlayer()->RemoveRunesByAuraEffect(GetEffect(0));
                }
                // Resilient Infection
                if ((GetId() == 55095 || GetId() == 55078) && target && caster)
                    if (AuraEffect const * aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_GENERIC, 1910, 0))
                        if (roll_chance_i(aurEff->GetAmount()))
                            if (removeMode == AURA_REMOVE_BY_ENEMY_SPELL)
                            {
                                int32 bp0 = 0;
                                int32 bp1 = 0;
                                if (GetId() == 55095)
                                    bp0 = 1;
                                else if (GetId() == 55078)
                                    bp1 = 1;
                                caster->CastCustomSpell(caster, 90721, &bp0, &bp1, NULL, true);
                            }
                break;
            case SPELLFAMILY_HUNTER:
                // Glyph of Freezing Trap
                if (GetSpellInfo()->SpellFamilyFlags[0] & 0x00000008)
                    if (caster && caster->HasAura(56845))
                        target->CastSpell(target, 61394, true);
                break;
            case SPELLFAMILY_SHAMAN:
                // Flame Shock
                if (GetId() == 8050 && removeMode == AURA_REMOVE_BY_ENEMY_SPELL)
                    // Lava Flows
                    if (AuraEffect const * aurEff = caster->GetDummyAuraEffect(SPELLFAMILY_SHAMAN, 3087, 0))
                    {
                        int32 bp = aurEff->GetAmount();
                        caster->CastCustomSpell(caster, 65264, &bp, NULL, NULL, true);
                    }
                break;
        }
    }

    // mods at aura apply or remove
    switch (GetSpellInfo()->SpellFamilyName)
    {
        case SPELLFAMILY_WARLOCK:
        {
            switch (GetId())
            {
                case 1490: // Curse of the Elements
                {
                    if (apply && caster && target)
                    {
                        if(caster->HasAura(18179)) // Jinx rank 1
                            caster->CastSpell(target,85547,true);
                        else if(caster->HasAura(85479)) // Jinxs rank 2
                            caster->CastSpell(target,86105,true);
                        // Need remove jinx of target who has CoE
                        if (target->HasAura(85547))
                            target->RemoveAura(85547);
                        else if (target->HasAura(86105))
                           target->RemoveAura(86105);
                    }
                    break;
                }
                case 702: // Curse of weakness
                {
                    if(apply && caster && target)
                    {
                        if(caster->HasAura(18179)) // Jinx rank 1
                        {
                            int32 bp = 5;
                            uint32 spellid = 0;
                            switch(target->getClass())
                            {
                                case CLASS_DEATH_KNIGHT:
                                    spellid = 85541;
                                    break;
                                case CLASS_HUNTER:
                                    spellid = 85542;
                                    break;
                                case CLASS_ROGUE:
                                    spellid = 85540;
                                    break;
                                case CLASS_WARRIOR:
                                    spellid = 85539;
                                    break;
                            }
                            if(spellid)
                                caster->CastCustomSpell(target,spellid,&bp,NULL,NULL,true);
                        }
                        else if(caster->HasAura(85479)) // Jinx rank 2
                        {
                            int32 bp = 10;
                            uint32 spellid = 0;
                            switch(target->getClass())
                            {
                                case CLASS_DEATH_KNIGHT:
                                    spellid = 85541;
                                    break;
                                case CLASS_HUNTER:
                                    spellid = 85542;
                                    break;
                                case CLASS_ROGUE:
                                    spellid = 85540;
                                    break;
                                case CLASS_WARRIOR:
                                    spellid = 85539;
                                    break;
                            }
                            if(spellid)
                                caster->CastCustomSpell(target,spellid,&bp,NULL,NULL,true);
                        }
                    }
                    else
                    {
                        if (!target)
                            return;
                        target->RemoveAurasDueToSpell(85541);
                        target->RemoveAurasDueToSpell(85542);
                        target->RemoveAurasDueToSpell(85540);
                        target->RemoveAurasDueToSpell(85539);
                    }
                }
                default:
                    break;
            }
            break;
        }
        case SPELLFAMILY_DRUID:
        {
            if (!caster)
                return;
            switch (GetId())
            {
                case 8936: // // Nature's Bounty
                {
                    if (apply)
                    {
                        if (caster->GetAuraEffect(SPELL_AURA_ADD_FLAT_MODIFIER, SPELLFAMILY_DRUID, 197, 0))
                        {
                            if (!target->GetAuraEffect(8936, 1))
                                ++caster->NatureBounty;
                        }
                    }
                    else if (caster->NatureBounty != 0)
                        if (!target->GetAuraEffect(8936, 1))
                            --caster->NatureBounty;

                    if (caster->NatureBounty >= 3 && !caster->HasAura(96206))
                    {
                        if (AuraEffect const* aurEff = caster->GetAuraEffect(SPELL_AURA_ADD_FLAT_MODIFIER, SPELLFAMILY_DRUID, 197, 0))
                        {
                            int32 bp = aurEff->GetAmount() / 2 * (-1);
                            caster->CastCustomSpell(caster,96206,&bp,NULL,NULL,true);
                        }
                    }
                    else if (caster->NatureBounty < 3 && caster->HasAura(96206))
                        caster->RemoveAurasDueToSpell(96206);
                }
                case 50334: // Primal Madness
                case 5217:
                {
                    if (target->GetAuraEffect(SPELL_AURA_PROC_TRIGGER_SPELL_WITH_VALUE, SPELLFAMILY_DRUID, 1181, 0))
                    {
                        if (apply)
                        {
                            if (caster->HasAura(80316))
                                caster->CastSpell(caster, 80879, true);
                            else if (caster->HasAura(80317))
                                caster->CastSpell(caster, 80886, true);
                        }
                        else
                        {
                            if (caster->HasAura(80879))
                                caster->RemoveAurasDueToSpell(80879);
                            if (caster->HasAura(80886))
                                caster->RemoveAurasDueToSpell(80886);
                        }
                    }

                    // Tiger's Fury
                    if (GetId() == 5217)
                        if (AuraEffect const * aurEff = target->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_DRUID, 2850, 1))
                            if (apply)
                            {
                                int32 basepoints0 = aurEff->GetAmount();
                                target->CastCustomSpell(target, 51178, &basepoints0, NULL, NULL, true, NULL, NULL, target->GetGUID());
                            }
                    break;
                }
                case 5229: // Enrage
                {
                    //King of the Jungle
                    if (AuraEffect const * aurEff = target->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_DRUID, 2850, 0))
                    {
                        if (apply)
                        {
                            int32 basepoints0 = aurEff->GetAmount();
                            target->CastCustomSpell(target, 51185, &basepoints0, NULL, NULL, true, NULL, NULL, target->GetGUID());
                        }
                        else
                            target->RemoveAurasDueToSpell(51185);
                    }

                    if (target->HasAura(70726)) // Druid T10 Feral 4P Bonus
                    {
                        if (apply)
                            target->CastSpell(target, 70725, true);
                    }
                    else if (AuraEffect * auraEff = target->GetAuraEffectOfRankedSpell(1178, 0)) // armor reduction implemented here
                    {
                        int32 value = auraEff->GetAmount();
                        int32 mod = 0;

                        switch (auraEff->GetId())
                        {
                            case 1178:
                                mod = 27;
                                break;
                            case 9635:
                                mod = 16;
                                break;
                        }
                        mod = value / 100 * mod;
                        value = value + (apply ? -mod : mod);
                        auraEff->ChangeAmount(value);
                    }
                    break;
                }
            }
            break;
        }
        case SPELLFAMILY_HUNTER:
            switch (GetId())
            {
                case 19574: // Bestial Wrath
                    // The Beast Within cast on owner if talent present
                    if (Unit* owner = target->GetOwner())
                    {
                        // Search talent
                        if (owner->HasAura(34692))
                        {
                            if (apply)
                                owner->CastSpell(owner, 34471, true, 0, GetEffect(0));
                            else
                                owner->RemoveAurasDueToSpell(34471);
                        }
                    }
                    break;
            }
            break;
        case SPELLFAMILY_PALADIN:
            switch (GetId())
            {
                case 31842: // Divine Favor
                    // Item - Paladin T10 Holy 2P Bonus
                    if (target->HasAura(70755))
                    {
                        if (apply)
                            target->CastSpell(target, 71166, true);
                        else
                            target->RemoveAurasDueToSpell(71166);
                    }
                    break;
            }
            break;
        case SPELLFAMILY_DEATHKNIGHT:
            if (GetSpellInfo()->GetSpellSpecific() == SPELL_SPECIFIC_PRESENCE)
            {
                caster->SetPower(POWER_RUNIC_POWER, 0);
                uint32 presence = GetId();
                if (apply)
                {
                    if (target != caster && !target->HealthAbovePct(25))
                        caster->CastSpell(caster, 100001, true);
                    // Blood Presence bonus
                    if (presence == 48263)
                    {
                        int32 bp0 = -8;
                        int32 bp1 = 0;
                        // Improved Blood Presence
                        if (AuraEffect const * aurEff = target->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_GENERIC, 2636, 1))
                            bp1 = aurEff->GetAmount();
                        target->CastCustomSpell(target, 61261,&bp0,&bp1,NULL, true);
                        target->ModifyAuraState(AURA_STATE_DEFENSE,true);
                        if (target->HasAura(56816))
                            target->RemoveAura(56816);
                    }

                    // Improved Presence
                    if (presence)
                    {
                        // Improved Blood Presence - frost unholy
                        if (presence == 48266 || presence == 48265)
                            if (AuraEffect const * aurEff = target->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_GENERIC, 2636, 0))
                            {
                                int32 bp0 = -(aurEff->GetAmount());
                                target->CastCustomSpell(target, 61261, &bp0,NULL,NULL, true);
                            }
                        // Improved Frost Presence - blood unholy
                        if (presence == 48263 || presence == 48265)
                            if (AuraEffect const * aurEff = target->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_DEATHKNIGHT, 2632, 0))
                            {
                                int32 bp0 = -(aurEff->GetAmount());
                                target->CastCustomSpell(target, 63621, &bp0,NULL,NULL, true);
                            }
                        // Improved Unholy Presence - blood frost
                        if (presence == 48263 || presence == 48266)
                            if (AuraEffect const * aurEff = target->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_DEATHKNIGHT, 2633, 0))
                            {
                                int32 bp0 = aurEff->GetAmount();
                                target->CastCustomSpell(target, 63622, &bp0,NULL,NULL, true);
                            }
                    }
                }
                else
                {
                    // Remove passive auras
                    if (target->HasAura(63611))
                        target->RemoveAurasDueToSpell(63611);
                    if (target->HasAura(61261))
                        target->RemoveAurasDueToSpell(61261);
                    if (target->HasAura(63622))
                        target->RemoveAurasDueToSpell(63622);
                    if (GetSpellInfo()->Id == 48263)
                    {
                        target->AddAura(56816,target);
                        target->ModifyAuraState(AURA_STATE_DEFENSE,false);
                    }
                }
            }
            break;
        case SPELLFAMILY_MAGE:
            {
                // Pyromaniac
                if (GetSpellInfo()->IsPeriodicDamage() && caster)
                {
                    if (apply)
                    {
                        if (caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_MAGE, 2128, 0))
                            if (target->GetDoTsByCaster(caster->GetGUID()) == 0)
                                ++caster->PyromaniacCount;
                    }
                    else if (caster->PyromaniacCount != 0)
                        if (target->GetDoTsByCaster(caster->GetGUID()) == 0)
                            --caster->PyromaniacCount;

                    if (caster->PyromaniacCount >= 3 && !caster->HasAura(83582))
                    {
                        if (AuraEffect const* aurEff = caster->GetAuraEffect(SPELL_AURA_DUMMY, SPELLFAMILY_MAGE, 2128, 0))
                        {
                            int32 bp = aurEff->GetAmount();
                            caster->CastCustomSpell(caster, 83582, &bp, NULL, NULL, true);
                        }
                    }
                    else if (caster->PyromaniacCount < 3 && caster->HasAura(83582))
                        caster->RemoveAurasDueToSpell(83582);
                }
            break;
            }
    }
}

bool Aura::CanBeAppliedOn(Unit* target)
{
    // unit not in world or during remove from world
    if (!target->IsInWorld() || target->IsDuringRemoveFromWorld())
    {
        // area auras mustn't be applied
        if (GetOwner() != target)
            return false;
        // do not apply non-selfcast single target auras
        if (GetCasterGUID() != GetOwner()->GetGUID() && GetSpellInfo()->IsSingleTarget())
            return false;
        return true;
    }
    else
        return CheckAreaTarget(target);
}

bool Aura::CheckAreaTarget(Unit* target)
{
    return CallScriptCheckAreaTargetHandlers(target);
}

bool Aura::CanStackWith(Aura const* existingAura) const
{
    // Can stack with self
    if (this == existingAura)
        return true;

    // Dynobj auras always stack
    if (GetType() == DYNOBJ_AURA_TYPE || existingAura->GetType() == DYNOBJ_AURA_TYPE)
        return true;

    SpellInfo const* existingSpellInfo = existingAura->GetSpellInfo();
    bool sameCaster = GetCasterGUID() == existingAura->GetCasterGUID();

    // passive auras don't stack with another rank of the spell cast by same caster
    if (IsPassive() && sameCaster && m_spellInfo->IsDifferentRankOf(existingSpellInfo))
        return false;

    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
    {
        // prevent remove triggering aura by triggered aura
        if (existingSpellInfo->Effects[i].TriggerSpell == GetId()
            // prevent remove triggered aura by triggering aura refresh
            || m_spellInfo->Effects[i].TriggerSpell == existingAura->GetId())
            return true;
    }

    // check spell specific stack rules
    if (m_spellInfo->IsAuraExclusiveBySpecificWith(existingSpellInfo)
        || (sameCaster && m_spellInfo->IsAuraExclusiveBySpecificPerCasterWith(existingSpellInfo)))
        return false;

    // check spell group stack rules
    SpellGroupStackRule stackRule = sSpellMgr->CheckSpellGroupStackRules(m_spellInfo, existingSpellInfo);
    if (stackRule)
    {
        if (stackRule == SPELL_GROUP_STACK_RULE_EXCLUSIVE)
            return false;
        if (sameCaster && stackRule == SPELL_GROUP_STACK_RULE_EXCLUSIVE_FROM_SAME_CASTER)
            return false;
    }

    if (m_spellInfo->SpellFamilyName != existingSpellInfo->SpellFamilyName)
        return true;

    if (!sameCaster)
    {
        // Channeled auras can stack if not forbidden by db or aura type
        if (existingAura->GetSpellInfo()->IsChanneled())
            return true;

        if (m_spellInfo->AttributesEx3 & SPELL_ATTR3_STACK_FOR_DIFF_CASTERS)
            return true;

        // check same periodic auras
        for (uint32 i = 0; i < MAX_SPELL_EFFECTS; ++i)
        {
            switch (m_spellInfo->Effects[i].ApplyAuraName)
            {
                // DOT or HOT from different casters will stack
                case SPELL_AURA_PERIODIC_DAMAGE:
                case SPELL_AURA_PERIODIC_DUMMY:
                case SPELL_AURA_PERIODIC_HEAL:
                case SPELL_AURA_PERIODIC_TRIGGER_SPELL:
                case SPELL_AURA_PERIODIC_ENERGIZE:
                case SPELL_AURA_PERIODIC_MANA_LEECH:
                case SPELL_AURA_PERIODIC_LEECH:
                case SPELL_AURA_POWER_BURN:
                case SPELL_AURA_OBS_MOD_POWER:
                case SPELL_AURA_OBS_MOD_HEALTH:
                case SPELL_AURA_PERIODIC_TRIGGER_SPELL_WITH_VALUE:
                    // periodic auras which target areas are not allowed to stack this way (replenishment for example)
                    if (m_spellInfo->Effects[i].IsTargetingArea() || existingSpellInfo->Effects[i].IsTargetingArea())
                        break;
                    return true;
                default:
                    break;
            }
        }
    }

    if (HasEffectType(SPELL_AURA_CONTROL_VEHICLE) && existingAura->HasEffectType(SPELL_AURA_CONTROL_VEHICLE))
    {
        Vehicle* veh = NULL;
        if (GetOwner()->ToUnit())
            veh = GetOwner()->ToUnit()->GetVehicleKit();

        if (!veh)           // We should probably just let it stack. Vehicle system will prevent undefined behaviour later
            return true;

        if (!veh->GetAvailableSeatCount())
            return false;   // No empty seat available

        return true; // Empty seat available (skip rest)
    }

    // spell of same spell rank chain
    if (m_spellInfo->IsRankOf(existingSpellInfo))
    {
        // don't allow passive area auras to stack
        if (m_spellInfo->IsMultiSlotAura() && !IsArea())
            return true;
        if (GetCastItemGUID() && existingAura->GetCastItemGUID())
            if (GetCastItemGUID() != existingAura->GetCastItemGUID() && (m_spellInfo->AttributesCu & SPELL_ATTR0_CU_ENCHANT_PROC))
                return true;
        // same spell with same caster should not stack
        return false;
    }

    return true;
}

bool Aura::IsProcOnCooldown() const
{
    /*if (m_procCooldown)
    {
        if (m_procCooldown > time(NULL))
            return true;
    }*/
    return false;
}

void Aura::AddProcCooldown(uint32 /*msec*/)
{
    //m_procCooldown = time(NULL) + msec;
}

void Aura::PrepareProcToTrigger(AuraApplication* aurApp, ProcEventInfo& eventInfo)
{
    bool prepare = CallScriptPrepareProcHandlers(aurApp, eventInfo);
    if (!prepare)
        return;

    // take one charge, aura expiration will be handled in Aura::TriggerProcOnEvent (if needed)
    if (IsUsingCharges())
    {
        --m_procCharges;
        SetNeedClientUpdateForTargets();
    }

    SpellProcEntry const* procEntry = sSpellMgr->GetSpellProcEntry(GetId());

    ASSERT(procEntry);

    // cooldowns should be added to the whole aura (see 51698 area aura)
    AddProcCooldown(procEntry->cooldown);
}

bool Aura::IsProcTriggeredOnEvent(AuraApplication* aurApp, ProcEventInfo& eventInfo) const
{
    SpellProcEntry const* procEntry = sSpellMgr->GetSpellProcEntry(GetId());
    // only auras with spell proc entry can trigger proc
    if (!procEntry)
        return false;

    // check if we have charges to proc with
    if (IsUsingCharges() && !GetCharges())
        return false;

    // check proc cooldown
    if (IsProcOnCooldown())
        return false;

    /// @todo
    // something about triggered spells triggering, and add extra attack effect

    // do checks against db data
    if (!sSpellMgr->CanSpellTriggerProcOnEvent(*procEntry, eventInfo))
        return false;

    // do checks using conditions table
    ConditionList conditions = sConditionMgr->GetConditionsForNotGroupedEntry(CONDITION_SOURCE_TYPE_SPELL_PROC, GetId());
    ConditionSourceInfo condInfo = ConditionSourceInfo(eventInfo.GetActor(), eventInfo.GetActionTarget());
    if (!sConditionMgr->IsObjectMeetToConditions(condInfo, conditions))
        return false;

    // AuraScript Hook
    bool check = const_cast<Aura*>(this)->CallScriptCheckProcHandlers(aurApp, eventInfo);
    if (!check)
        return false;

    /// @todo
    // do allow additional requirements for procs
    // this is needed because this is the last moment in which you can prevent aura charge drop on proc
    // and possibly a way to prevent default checks (if there're going to be any)

    // Check if current equipment meets aura requirements
    // do that only for passive spells
    /// @todo this needs to be unified for all kinds of auras
    Unit* target = aurApp->GetTarget();
    if (IsPassive() && target->GetTypeId() == TYPEID_PLAYER)
    {
        if (GetSpellInfo()->EquippedItemClass == ITEM_CLASS_WEAPON)
        {
            if (target->ToPlayer()->IsInFeralForm())
                return false;

            if (eventInfo.GetDamageInfo())
            {
                WeaponAttackType attType = eventInfo.GetDamageInfo()->GetAttackType();
                Item* item = NULL;
                if (attType == BASE_ATTACK)
                    item = target->ToPlayer()->GetUseableItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
                else if (attType == OFF_ATTACK)
                    item = target->ToPlayer()->GetUseableItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);
                else
                    item = target->ToPlayer()->GetUseableItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED);

                if (!item || item->IsBroken() || item->GetTemplate()->Class != ITEM_CLASS_WEAPON || !((1<<item->GetTemplate()->SubClass) & GetSpellInfo()->EquippedItemSubClassMask))
                    return false;
            }
        }
        else if (GetSpellInfo()->EquippedItemClass == ITEM_CLASS_ARMOR)
        {
            // Check if player is wearing shield
            Item* item = target->ToPlayer()->GetUseableItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);
            if (!item || item->IsBroken() || item->GetTemplate()->Class != ITEM_CLASS_ARMOR || !((1<<item->GetTemplate()->SubClass) & GetSpellInfo()->EquippedItemSubClassMask))
                return false;
        }
    }

    return roll_chance_f(CalcProcChance(*procEntry, eventInfo));
}

float Aura::CalcProcChance(SpellProcEntry const& procEntry, ProcEventInfo& eventInfo) const
{
    float chance = procEntry.chance;
    // calculate chances depending on unit with caster's data
    // so talents modifying chances and judgements will have properly calculated proc chance
    if (Unit* caster = GetCaster())
    {
        // calculate ppm chance if present and we're using weapon
        if (eventInfo.GetDamageInfo() && procEntry.ratePerMinute != 0)
        {
            uint32 WeaponSpeed = caster->GetAttackTime(eventInfo.GetDamageInfo()->GetAttackType());
            chance = caster->GetPPMProcChance(WeaponSpeed, procEntry.ratePerMinute, GetSpellInfo());
        }
        // apply chance modifer aura, applies also to ppm chance (see improved judgement of light spell)
        if (Player* modOwner = caster->GetSpellModOwner())
            modOwner->ApplySpellMod(GetId(), SPELLMOD_CHANCE_OF_SUCCESS, chance);
    }
    return chance;
}

void Aura::TriggerProcOnEvent(AuraApplication* aurApp, ProcEventInfo& eventInfo)
{
    CallScriptProcHandlers(aurApp, eventInfo);

    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
        if (aurApp->HasEffect(i))
            // OnEffectProc / AfterEffectProc hooks handled in AuraEffect::HandleProc()
            GetEffect(i)->HandleProc(aurApp, eventInfo);

    CallScriptAfterProcHandlers(aurApp, eventInfo);

    // Remove aura if we've used last charge to proc
    if (IsUsingCharges() && !GetCharges())
        Remove();
}

void Aura::_DeleteRemovedApplications()
{
    while (!m_removedApplications.empty())
    {
        delete m_removedApplications.front();
        m_removedApplications.pop_front();
    }
}

void Aura::LoadScripts()
{
    sScriptMgr->CreateAuraScripts(m_spellInfo->Id, m_loadedScripts);
    for (std::list<AuraScript*>::iterator itr = m_loadedScripts.begin(); itr != m_loadedScripts.end();)
    {
        if (!(*itr)->_Load(this))
        {
            std::list<AuraScript*>::iterator bitr = itr;
            ++itr;
            delete (*bitr);
            m_loadedScripts.erase(bitr);
            continue;
        }
        TC_LOG_DEBUG("spells", "Aura::LoadScripts: Script `%s` for aura `%u` is loaded now", (*itr)->_GetScriptName()->c_str(), m_spellInfo->Id);
        (*itr)->Register();
        ++itr;
    }
}

bool Aura::CallScriptCheckAreaTargetHandlers(Unit* target)
{
    bool result = true;
    for (std::list<AuraScript*>::iterator scritr = m_loadedScripts.begin(); scritr != m_loadedScripts.end(); ++scritr)
    {
        (*scritr)->_PrepareScriptCall(AURA_SCRIPT_HOOK_CHECK_AREA_TARGET);
        std::list<AuraScript::CheckAreaTargetHandler>::iterator hookItrEnd = (*scritr)->DoCheckAreaTarget.end(), hookItr = (*scritr)->DoCheckAreaTarget.begin();
        for (; hookItr != hookItrEnd; ++hookItr)
            result &= hookItr->Call(*scritr, target);

        (*scritr)->_FinishScriptCall();
    }
    return result;
}

void Aura::CallScriptDispel(DispelInfo* dispelInfo)
{
    for (std::list<AuraScript*>::iterator scritr = m_loadedScripts.begin(); scritr != m_loadedScripts.end(); ++scritr)
    {
        (*scritr)->_PrepareScriptCall(AURA_SCRIPT_HOOK_DISPEL);
        std::list<AuraScript::AuraDispelHandler>::iterator hookItrEnd = (*scritr)->OnDispel.end(), hookItr = (*scritr)->OnDispel.begin();
        for (; hookItr != hookItrEnd; ++hookItr)
            hookItr->Call(*scritr, dispelInfo);

        (*scritr)->_FinishScriptCall();
    }
}

void Aura::CallScriptAfterDispel(DispelInfo* dispelInfo)
{
    for (std::list<AuraScript*>::iterator scritr = m_loadedScripts.begin(); scritr != m_loadedScripts.end(); ++scritr)
    {
        (*scritr)->_PrepareScriptCall(AURA_SCRIPT_HOOK_AFTER_DISPEL);
        std::list<AuraScript::AuraDispelHandler>::iterator hookItrEnd = (*scritr)->AfterDispel.end(), hookItr = (*scritr)->AfterDispel.begin();
        for (; hookItr != hookItrEnd; ++hookItr)
            hookItr->Call(*scritr, dispelInfo);

        (*scritr)->_FinishScriptCall();
    }
}

bool Aura::CallScriptEffectApplyHandlers(AuraEffect const* aurEff, AuraApplication const* aurApp, AuraEffectHandleModes mode)
{
    bool preventDefault = false;
    for (std::list<AuraScript*>::iterator scritr = m_loadedScripts.begin(); scritr != m_loadedScripts.end(); ++scritr)
    {
        (*scritr)->_PrepareScriptCall(AURA_SCRIPT_HOOK_EFFECT_APPLY, aurApp);
        std::list<AuraScript::EffectApplyHandler>::iterator effEndItr = (*scritr)->OnEffectApply.end(), effItr = (*scritr)->OnEffectApply.begin();
        for (; effItr != effEndItr; ++effItr)
            if (effItr->IsEffectAffected(m_spellInfo, aurEff->GetEffIndex()))
                effItr->Call(*scritr, aurEff, mode);

        if (!preventDefault)
            preventDefault = (*scritr)->_IsDefaultActionPrevented();

        (*scritr)->_FinishScriptCall();
    }

    return preventDefault;
}

bool Aura::CallScriptEffectRemoveHandlers(AuraEffect const* aurEff, AuraApplication const* aurApp, AuraEffectHandleModes mode)
{
    bool preventDefault = false;
    for (std::list<AuraScript*>::iterator scritr = m_loadedScripts.begin(); scritr != m_loadedScripts.end(); ++scritr)
    {
        (*scritr)->_PrepareScriptCall(AURA_SCRIPT_HOOK_EFFECT_REMOVE, aurApp);
        std::list<AuraScript::EffectApplyHandler>::iterator effEndItr = (*scritr)->OnEffectRemove.end(), effItr = (*scritr)->OnEffectRemove.begin();
        for (; effItr != effEndItr; ++effItr)
            if (effItr->IsEffectAffected(m_spellInfo, aurEff->GetEffIndex()))
                effItr->Call(*scritr, aurEff, mode);

        if (!preventDefault)
            preventDefault = (*scritr)->_IsDefaultActionPrevented();

        (*scritr)->_FinishScriptCall();
    }
    return preventDefault;
}

void Aura::CallScriptAfterEffectApplyHandlers(AuraEffect const* aurEff, AuraApplication const* aurApp, AuraEffectHandleModes mode)
{
    for (std::list<AuraScript*>::iterator scritr = m_loadedScripts.begin(); scritr != m_loadedScripts.end(); ++scritr)
    {
        (*scritr)->_PrepareScriptCall(AURA_SCRIPT_HOOK_EFFECT_AFTER_APPLY, aurApp);
        std::list<AuraScript::EffectApplyHandler>::iterator effEndItr = (*scritr)->AfterEffectApply.end(), effItr = (*scritr)->AfterEffectApply.begin();
        for (; effItr != effEndItr; ++effItr)
            if (effItr->IsEffectAffected(m_spellInfo, aurEff->GetEffIndex()))
                effItr->Call(*scritr, aurEff, mode);

        (*scritr)->_FinishScriptCall();
    }
}

void Aura::CallScriptAfterEffectRemoveHandlers(AuraEffect const* aurEff, AuraApplication const* aurApp, AuraEffectHandleModes mode)
{
    for (std::list<AuraScript*>::iterator scritr = m_loadedScripts.begin(); scritr != m_loadedScripts.end(); ++scritr)
    {
        (*scritr)->_PrepareScriptCall(AURA_SCRIPT_HOOK_EFFECT_AFTER_REMOVE, aurApp);
        std::list<AuraScript::EffectApplyHandler>::iterator effEndItr = (*scritr)->AfterEffectRemove.end(), effItr = (*scritr)->AfterEffectRemove.begin();
        for (; effItr != effEndItr; ++effItr)
            if (effItr->IsEffectAffected(m_spellInfo, aurEff->GetEffIndex()))
                effItr->Call(*scritr, aurEff, mode);

        (*scritr)->_FinishScriptCall();
    }
}

bool Aura::CallScriptEffectPeriodicHandlers(AuraEffect const* aurEff, AuraApplication const* aurApp)
{
    bool preventDefault = false;
    for (std::list<AuraScript*>::iterator scritr = m_loadedScripts.begin(); scritr != m_loadedScripts.end(); ++scritr)
    {
        (*scritr)->_PrepareScriptCall(AURA_SCRIPT_HOOK_EFFECT_PERIODIC, aurApp);
        std::list<AuraScript::EffectPeriodicHandler>::iterator effEndItr = (*scritr)->OnEffectPeriodic.end(), effItr = (*scritr)->OnEffectPeriodic.begin();
        for (; effItr != effEndItr; ++effItr)
            if (effItr->IsEffectAffected(m_spellInfo, aurEff->GetEffIndex()))
                effItr->Call(*scritr, aurEff);

        if (!preventDefault)
            preventDefault = (*scritr)->_IsDefaultActionPrevented();

        (*scritr)->_FinishScriptCall();
    }

    return preventDefault;
}

void Aura::CallScriptEffectUpdatePeriodicHandlers(AuraEffect* aurEff)
{
    for (std::list<AuraScript*>::iterator scritr = m_loadedScripts.begin(); scritr != m_loadedScripts.end(); ++scritr)
    {
        (*scritr)->_PrepareScriptCall(AURA_SCRIPT_HOOK_EFFECT_UPDATE_PERIODIC);
        std::list<AuraScript::EffectUpdatePeriodicHandler>::iterator effEndItr = (*scritr)->OnEffectUpdatePeriodic.end(), effItr = (*scritr)->OnEffectUpdatePeriodic.begin();
        for (; effItr != effEndItr; ++effItr)
            if (effItr->IsEffectAffected(m_spellInfo, aurEff->GetEffIndex()))
                effItr->Call(*scritr, aurEff);

        (*scritr)->_FinishScriptCall();
    }
}

void Aura::CallScriptEffectCalcAmountHandlers(AuraEffect const* aurEff, int32 & amount, bool & canBeRecalculated)
{
    for (std::list<AuraScript*>::iterator scritr = m_loadedScripts.begin(); scritr != m_loadedScripts.end(); ++scritr)
    {
        (*scritr)->_PrepareScriptCall(AURA_SCRIPT_HOOK_EFFECT_CALC_AMOUNT);
        std::list<AuraScript::EffectCalcAmountHandler>::iterator effEndItr = (*scritr)->DoEffectCalcAmount.end(), effItr = (*scritr)->DoEffectCalcAmount.begin();
        for (; effItr != effEndItr; ++effItr)
            if (effItr->IsEffectAffected(m_spellInfo, aurEff->GetEffIndex()))
                effItr->Call(*scritr, aurEff, amount, canBeRecalculated);

        (*scritr)->_FinishScriptCall();
    }
}

void Aura::CallScriptEffectCalcPeriodicHandlers(AuraEffect const* aurEff, bool & isPeriodic, int32 & amplitude)
{
    for (std::list<AuraScript*>::iterator scritr = m_loadedScripts.begin(); scritr != m_loadedScripts.end(); ++scritr)
    {
        (*scritr)->_PrepareScriptCall(AURA_SCRIPT_HOOK_EFFECT_CALC_PERIODIC);
        std::list<AuraScript::EffectCalcPeriodicHandler>::iterator effEndItr = (*scritr)->DoEffectCalcPeriodic.end(), effItr = (*scritr)->DoEffectCalcPeriodic.begin();
        for (; effItr != effEndItr; ++effItr)
            if (effItr->IsEffectAffected(m_spellInfo, aurEff->GetEffIndex()))
                effItr->Call(*scritr, aurEff, isPeriodic, amplitude);

        (*scritr)->_FinishScriptCall();
    }
}

void Aura::CallScriptEffectCalcSpellModHandlers(AuraEffect const* aurEff, SpellModifier* & spellMod)
{
    for (std::list<AuraScript*>::iterator scritr = m_loadedScripts.begin(); scritr != m_loadedScripts.end(); ++scritr)
    {
        (*scritr)->_PrepareScriptCall(AURA_SCRIPT_HOOK_EFFECT_CALC_SPELLMOD);
        std::list<AuraScript::EffectCalcSpellModHandler>::iterator effEndItr = (*scritr)->DoEffectCalcSpellMod.end(), effItr = (*scritr)->DoEffectCalcSpellMod.begin();
        for (; effItr != effEndItr; ++effItr)
            if (effItr->IsEffectAffected(m_spellInfo, aurEff->GetEffIndex()))
                effItr->Call(*scritr, aurEff, spellMod);

        (*scritr)->_FinishScriptCall();
    }
}

void Aura::CallScriptEffectAbsorbHandlers(AuraEffect* aurEff, AuraApplication const* aurApp, DamageInfo & dmgInfo, uint32 & absorbAmount, bool& defaultPrevented)
{
    for (std::list<AuraScript*>::iterator scritr = m_loadedScripts.begin(); scritr != m_loadedScripts.end(); ++scritr)
    {
        (*scritr)->_PrepareScriptCall(AURA_SCRIPT_HOOK_EFFECT_ABSORB, aurApp);
        std::list<AuraScript::EffectAbsorbHandler>::iterator effEndItr = (*scritr)->OnEffectAbsorb.end(), effItr = (*scritr)->OnEffectAbsorb.begin();
        for (; effItr != effEndItr; ++effItr)

            if (effItr->IsEffectAffected(m_spellInfo, aurEff->GetEffIndex()))
                effItr->Call(*scritr, aurEff, dmgInfo, absorbAmount);

        if (!defaultPrevented)
            defaultPrevented = (*scritr)->_IsDefaultActionPrevented();

        (*scritr)->_FinishScriptCall();
    }
}

void Aura::CallScriptEffectAfterAbsorbHandlers(AuraEffect* aurEff, AuraApplication const* aurApp, DamageInfo & dmgInfo, uint32 & absorbAmount)
{
    for (std::list<AuraScript*>::iterator scritr = m_loadedScripts.begin(); scritr != m_loadedScripts.end(); ++scritr)
    {
        (*scritr)->_PrepareScriptCall(AURA_SCRIPT_HOOK_EFFECT_AFTER_ABSORB, aurApp);
        std::list<AuraScript::EffectAbsorbHandler>::iterator effEndItr = (*scritr)->AfterEffectAbsorb.end(), effItr = (*scritr)->AfterEffectAbsorb.begin();
        for (; effItr != effEndItr; ++effItr)
            if (effItr->IsEffectAffected(m_spellInfo, aurEff->GetEffIndex()))
                effItr->Call(*scritr, aurEff, dmgInfo, absorbAmount);

        (*scritr)->_FinishScriptCall();
    }
}

void Aura::CallScriptEffectManaShieldHandlers(AuraEffect* aurEff, AuraApplication const* aurApp, DamageInfo & dmgInfo, uint32 & absorbAmount, bool & /*defaultPrevented*/)
{
    for (std::list<AuraScript*>::iterator scritr = m_loadedScripts.begin(); scritr != m_loadedScripts.end(); ++scritr)
    {
        (*scritr)->_PrepareScriptCall(AURA_SCRIPT_HOOK_EFFECT_MANASHIELD, aurApp);
        std::list<AuraScript::EffectManaShieldHandler>::iterator effEndItr = (*scritr)->OnEffectManaShield.end(), effItr = (*scritr)->OnEffectManaShield.begin();
        for (; effItr != effEndItr; ++effItr)
            if (effItr->IsEffectAffected(m_spellInfo, aurEff->GetEffIndex()))
                effItr->Call(*scritr, aurEff, dmgInfo, absorbAmount);

        (*scritr)->_FinishScriptCall();
    }
}

void Aura::CallScriptEffectAfterManaShieldHandlers(AuraEffect* aurEff, AuraApplication const* aurApp, DamageInfo & dmgInfo, uint32 & absorbAmount)
{
    for (std::list<AuraScript*>::iterator scritr = m_loadedScripts.begin(); scritr != m_loadedScripts.end(); ++scritr)
    {
        (*scritr)->_PrepareScriptCall(AURA_SCRIPT_HOOK_EFFECT_AFTER_MANASHIELD, aurApp);
        std::list<AuraScript::EffectManaShieldHandler>::iterator effEndItr = (*scritr)->AfterEffectManaShield.end(), effItr = (*scritr)->AfterEffectManaShield.begin();
        for (; effItr != effEndItr; ++effItr)
            if (effItr->IsEffectAffected(m_spellInfo, aurEff->GetEffIndex()))
                effItr->Call(*scritr, aurEff, dmgInfo, absorbAmount);

        (*scritr)->_FinishScriptCall();
    }
}

void Aura::CallScriptEffectSplitHandlers(AuraEffect* aurEff, AuraApplication const* aurApp, DamageInfo & dmgInfo, uint32 & splitAmount)
{
    for (std::list<AuraScript*>::iterator scritr = m_loadedScripts.begin(); scritr != m_loadedScripts.end(); ++scritr)
    {
        (*scritr)->_PrepareScriptCall(AURA_SCRIPT_HOOK_EFFECT_SPLIT, aurApp);
        std::list<AuraScript::EffectSplitHandler>::iterator effEndItr = (*scritr)->OnEffectSplit.end(), effItr = (*scritr)->OnEffectSplit.begin();
        for (; effItr != effEndItr; ++effItr)
            if (effItr->IsEffectAffected(m_spellInfo, aurEff->GetEffIndex()))
                effItr->Call(*scritr, aurEff, dmgInfo, splitAmount);

        (*scritr)->_FinishScriptCall();
    }
}

bool Aura::CallScriptCheckProcHandlers(AuraApplication const* aurApp, ProcEventInfo& eventInfo)
{
    bool result = true;
    for (std::list<AuraScript*>::iterator scritr = m_loadedScripts.begin(); scritr != m_loadedScripts.end(); ++scritr)
    {
        (*scritr)->_PrepareScriptCall(AURA_SCRIPT_HOOK_CHECK_PROC, aurApp);
        std::list<AuraScript::CheckProcHandler>::iterator hookItrEnd = (*scritr)->DoCheckProc.end(), hookItr = (*scritr)->DoCheckProc.begin();
        for (; hookItr != hookItrEnd; ++hookItr)
            result &= hookItr->Call(*scritr, eventInfo);

        (*scritr)->_FinishScriptCall();
    }

    return result;
}

bool Aura::CallScriptPrepareProcHandlers(AuraApplication const* aurApp, ProcEventInfo& eventInfo)
{
    bool prepare = true;
    for (std::list<AuraScript*>::iterator scritr = m_loadedScripts.begin(); scritr != m_loadedScripts.end(); ++scritr)
    {
        (*scritr)->_PrepareScriptCall(AURA_SCRIPT_HOOK_PREPARE_PROC, aurApp);
        std::list<AuraScript::AuraProcHandler>::iterator effEndItr = (*scritr)->DoPrepareProc.end(), effItr = (*scritr)->DoPrepareProc.begin();
        for (; effItr != effEndItr; ++effItr)
            effItr->Call(*scritr, eventInfo);

        if (prepare)
            prepare = !(*scritr)->_IsDefaultActionPrevented();

        (*scritr)->_FinishScriptCall();
    }

    return prepare;
}

bool Aura::CallScriptProcHandlers(AuraApplication const* aurApp, ProcEventInfo& eventInfo)
{
    bool handled = false;
    for (std::list<AuraScript*>::iterator scritr = m_loadedScripts.begin(); scritr != m_loadedScripts.end(); ++scritr)
    {
        (*scritr)->_PrepareScriptCall(AURA_SCRIPT_HOOK_PROC, aurApp);
        std::list<AuraScript::AuraProcHandler>::iterator hookItrEnd = (*scritr)->OnProc.end(), hookItr = (*scritr)->OnProc.begin();
        for (; hookItr != hookItrEnd; ++hookItr)
            hookItr->Call(*scritr, eventInfo);

        handled |= (*scritr)->_IsDefaultActionPrevented();
        (*scritr)->_FinishScriptCall();
    }

    return handled;
}

void Aura::CallScriptAfterProcHandlers(AuraApplication const* aurApp, ProcEventInfo& eventInfo)
{
    for (std::list<AuraScript*>::iterator scritr = m_loadedScripts.begin(); scritr != m_loadedScripts.end(); ++scritr)
    {
        (*scritr)->_PrepareScriptCall(AURA_SCRIPT_HOOK_AFTER_PROC, aurApp);
        std::list<AuraScript::AuraProcHandler>::iterator hookItrEnd = (*scritr)->AfterProc.end(), hookItr = (*scritr)->AfterProc.begin();
        for (; hookItr != hookItrEnd; ++hookItr)
            hookItr->Call(*scritr, eventInfo);

        (*scritr)->_FinishScriptCall();
    }
}

bool Aura::CallScriptEffectProcHandlers(AuraEffect const* aurEff, AuraApplication const* aurApp, ProcEventInfo& eventInfo)
{
    bool preventDefault = false;
    for (std::list<AuraScript*>::iterator scritr = m_loadedScripts.begin(); scritr != m_loadedScripts.end(); ++scritr)
    {
        (*scritr)->_PrepareScriptCall(AURA_SCRIPT_HOOK_EFFECT_PROC, aurApp);
        std::list<AuraScript::EffectProcHandler>::iterator effEndItr = (*scritr)->OnEffectProc.end(), effItr = (*scritr)->OnEffectProc.begin();
        for (; effItr != effEndItr; ++effItr)
            if (effItr->IsEffectAffected(m_spellInfo, aurEff->GetEffIndex()))
                effItr->Call(*scritr, aurEff, eventInfo);

        if (!preventDefault)
            preventDefault = (*scritr)->_IsDefaultActionPrevented();

        (*scritr)->_FinishScriptCall();
    }
    return preventDefault;
}

void Aura::CallScriptAfterEffectProcHandlers(AuraEffect const* aurEff, AuraApplication const* aurApp, ProcEventInfo& eventInfo)
{
    for (std::list<AuraScript*>::iterator scritr = m_loadedScripts.begin(); scritr != m_loadedScripts.end(); ++scritr)
    {
        (*scritr)->_PrepareScriptCall(AURA_SCRIPT_HOOK_EFFECT_AFTER_PROC, aurApp);
        std::list<AuraScript::EffectProcHandler>::iterator effEndItr = (*scritr)->AfterEffectProc.end(), effItr = (*scritr)->AfterEffectProc.begin();
        for (; effItr != effEndItr; ++effItr)
            if (effItr->IsEffectAffected(m_spellInfo, aurEff->GetEffIndex()))
                effItr->Call(*scritr, aurEff, eventInfo);

        (*scritr)->_FinishScriptCall();
    }
}

UnitAura::UnitAura(SpellInfo const* spellproto, uint8 effMask, WorldObject* owner, Unit* caster, int32 *baseAmount, Item* castItem, uint64 casterGUID)
    : Aura(spellproto, owner, caster, castItem, casterGUID)
{
    m_AuraDRGroup = DIMINISHING_NONE;
    LoadScripts();
    _InitEffects(effMask, caster, baseAmount);
    GetUnitOwner()->_AddAura(this, caster);
}

void UnitAura::_ApplyForTarget(Unit* target, Unit* caster, AuraApplication * aurApp)
{
    Aura::_ApplyForTarget(target, caster, aurApp);

    // register aura diminishing on apply
    if (DiminishingGroup group = GetDiminishGroup())
        target->ApplyDiminishingAura(group, true);
}

void UnitAura::_UnapplyForTarget(Unit* target, Unit* caster, AuraApplication * aurApp)
{
    Aura::_UnapplyForTarget(target, caster, aurApp);

    // unregister aura diminishing (and store last time)
    if (DiminishingGroup group = GetDiminishGroup())
        target->ApplyDiminishingAura(group, false);
}

void UnitAura::Remove(AuraRemoveMode removeMode)
{
    if (IsRemoved())
        return;
    GetUnitOwner()->RemoveOwnedAura(this, removeMode);
}

void UnitAura::FillTargetMap(std::map<Unit*, uint8> & targets, Unit* caster)
{
    for (uint8 effIndex = 0; effIndex < MAX_SPELL_EFFECTS; ++effIndex)
    {
        if (!HasEffect(effIndex))
            continue;
        UnitList targetList;
        // non-area aura
        if (GetSpellInfo()->Effects[effIndex].Effect == SPELL_EFFECT_APPLY_AURA)
        {
            targetList.push_back(GetUnitOwner());
        }
        else
        {
            float radius = GetSpellInfo()->Effects[effIndex].CalcRadius(caster);

            if (!GetUnitOwner()->HasUnitState(UNIT_STATE_ISOLATED))
            {
                switch (GetSpellInfo()->Effects[effIndex].Effect)
                {
                    case SPELL_EFFECT_APPLY_AREA_AURA_PARTY:
                    case SPELL_EFFECT_APPLY_AREA_AURA_RAID:
                    {
                        targetList.push_back(GetUnitOwner());
                        Trinity::AnyGroupedUnitInObjectRangeCheck u_check(GetUnitOwner(), GetUnitOwner(), radius, GetSpellInfo()->Effects[effIndex].Effect == SPELL_EFFECT_APPLY_AREA_AURA_RAID);
                        Trinity::UnitListSearcher<Trinity::AnyGroupedUnitInObjectRangeCheck> searcher(GetUnitOwner(), targetList, u_check);
                        GetUnitOwner()->VisitNearbyObject(radius, searcher);
                        break;
                    }
                    case SPELL_EFFECT_APPLY_AREA_AURA_FRIEND:
                    {
                        targetList.push_back(GetUnitOwner());
                        Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(GetUnitOwner(), GetUnitOwner(), radius);
                        Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(GetUnitOwner(), targetList, u_check);
                        GetUnitOwner()->VisitNearbyObject(radius, searcher);
                        break;
                    }
                    case SPELL_EFFECT_APPLY_AREA_AURA_ENEMY:
                    {
                        Trinity::AnyAoETargetUnitInObjectRangeCheck u_check(GetUnitOwner(), GetUnitOwner(), radius); // No GetCharmer in searcher
                        Trinity::UnitListSearcher<Trinity::AnyAoETargetUnitInObjectRangeCheck> searcher(GetUnitOwner(), targetList, u_check);
                        GetUnitOwner()->VisitNearbyObject(radius, searcher);
                        break;
                    }
                    case SPELL_EFFECT_APPLY_AREA_AURA_PET:
                        targetList.push_back(GetUnitOwner());
                        // no break
                    case SPELL_EFFECT_APPLY_AREA_AURA_OWNER:
                    {
                        if (Unit* owner = GetUnitOwner()->GetCharmerOrOwner())
                            if (GetUnitOwner()->IsWithinDistInMap(owner, radius))
                                targetList.push_back(owner);
                        break;
                    }
                }
            }
        }

        for (UnitList::iterator itr = targetList.begin(); itr!= targetList.end();++itr)
        {
            std::map<Unit*, uint8>::iterator existing = targets.find(*itr);
            if (existing != targets.end())
                existing->second |= 1<<effIndex;
            else
                targets[*itr] = 1<<effIndex;
        }
    }
}

DynObjAura::DynObjAura(SpellInfo const* spellproto, uint8 effMask, WorldObject* owner, Unit* caster, int32 *baseAmount, Item* castItem, uint64 casterGUID)
    : Aura(spellproto, owner, caster, castItem, casterGUID)
{
    LoadScripts();
    ASSERT(GetDynobjOwner());
    ASSERT(GetDynobjOwner()->IsInWorld());
    ASSERT(GetDynobjOwner()->GetMap() == caster->GetMap());
    _InitEffects(effMask, caster, baseAmount);
    GetDynobjOwner()->SetAura(this);
}

void DynObjAura::Remove(AuraRemoveMode removeMode)
{
    if (IsRemoved())
        return;
    _Remove(removeMode);
}

void DynObjAura::FillTargetMap(std::map<Unit*, uint8> & targets, Unit* /*caster*/)
{
    Unit* dynObjOwnerCaster = GetDynobjOwner()->GetCaster();
    float radius = GetDynobjOwner()->GetRadius();

    for (uint8 effIndex = 0; effIndex < MAX_SPELL_EFFECTS; ++effIndex)
    {
        if (!HasEffect(effIndex))
            continue;
        UnitList targetList;
        if (GetSpellInfo()->Effects[effIndex].TargetB.GetTarget() == TARGET_DEST_DYNOBJ_ALLY
            || GetSpellInfo()->Effects[effIndex].TargetB.GetTarget() == TARGET_UNIT_DEST_AREA_ALLY)
        {
            Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(GetDynobjOwner(), dynObjOwnerCaster, radius);
            Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(GetDynobjOwner(), targetList, u_check);
            GetDynobjOwner()->VisitNearbyObject(radius, searcher);
        }
        else
        {
            Trinity::AnyAoETargetUnitInObjectRangeCheck u_check(GetDynobjOwner(), dynObjOwnerCaster, radius);
            Trinity::UnitListSearcher<Trinity::AnyAoETargetUnitInObjectRangeCheck> searcher(GetDynobjOwner(), targetList, u_check);
            GetDynobjOwner()->VisitNearbyObject(radius, searcher);
        }

        for (UnitList::iterator itr = targetList.begin(); itr!= targetList.end();++itr)
        {
            std::map<Unit*, uint8>::iterator existing = targets.find(*itr);
            if (existing != targets.end())
                existing->second |= 1<<effIndex;
            else
                targets[*itr] = 1<<effIndex;
        }
    }
}
