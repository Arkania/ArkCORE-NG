/*
Name: bot_GridNotifiers
%Complete: 95+
Comment: Custom grid notifiers for Bot system by Graff (onlysuffering@gmail.com)
Category: creature_cripts/custom/bots/grids
*/

#ifndef _BOT_GRIDNOTIFIERS_H
#define _BOT_GRIDNOTIFIERS_H

#include "Group.h"
#include "Player.h"
#include "SpellAuras.h"
#include "bot_ai.h"

uint8 PvP = 1;

class NearestHostileUnitCheck
{
    public:
        explicit NearestHostileUnitCheck(Unit const* unit, float dist, bool magic, bot_ai const* m_ai, bool targetCCed = false) :
        me(unit), m_range(dist), byspell(magic), ai(m_ai), AttackCCed(targetCCed) { }
        bool operator()(Unit* u)
        {
            if (!PvP && (u->ToPlayer() || (u->ToCreature() && u->ToCreature()->GetBotAI())))
                return false;
            if (!me->IsWithinDistInMap(u, m_range))
                return false;
            if (!u->IsInCombat())
                return false;
            if (!u->InSamePhase(me))
                return false;
            if (!ai->CanBotAttack(u, byspell))
                return false;
            if (ai->InDuel(u))
                return false;
            if (!AttackCCed && (u->HasUnitState(UNIT_STATE_CONFUSED | UNIT_STATE_STUNNED | UNIT_STATE_FLEEING | UNIT_STATE_DISTRACTED | UNIT_STATE_CONFUSED_MOVE | UNIT_STATE_FLEEING_MOVE)))
                return false;//do not allow CCed units if checked
            //if (u->HasUnitState(UNIT_STATE_CASTING) && (u->GetTypeId() == TYPEID_PLAYER || u->IsPet()))
            //    for (uint8 i = 0; i != CURRENT_MAX_SPELL; ++i)
            //        if (Spell* spell = u->GetCurrentSpell(i))
            //            if (ai->IsInBotParty(spell->m_targets.GetUnitTarget()))
            //                return true;
            if (!ai->IsInBotParty(u->GetVictim()))
                return false;

            m_range = me->GetDistance(u);   // use found unit range as new range limit for next check
            return true;
        }
    private:
        Unit const* me;
        float m_range;
        bool byspell;
        bot_ai const* ai;
        bool AttackCCed;
        NearestHostileUnitCheck(NearestHostileUnitCheck const&);
};

class HostileDispelTargetCheck
{
    public:
        explicit HostileDispelTargetCheck(Unit const* unit, float dist = 30, bool stealable = false, bot_ai const* m_ai = NULL) :
        me(unit), m_range(dist), checksteal(stealable), ai(m_ai) { }
        bool operator()(Unit* u)
        {
            if (!PvP && (u->ToPlayer() || (u->ToCreature() && u->ToCreature()->GetBotAI())))
                return false;
            if (u->IsWithinDistInMap(me, m_range) &&
                u->IsAlive() &&
                u->InSamePhase(me) &&
                u->IsInCombat() &&
                u->isTargetableForAttack() &&
                u->IsVisible() &&
                u->GetReactionTo(me) < REP_NEUTRAL &&
                ai->IsInBotParty(u->GetVictim()))
            {
                if (checksteal && u->IsImmunedToSpell(sSpellMgr->GetSpellInfo(30449))) return false;//immune to steal
                if (!checksteal)
                {
                    if (me->getLevel() >= 72 && u->IsImmunedToSpell(sSpellMgr->GetSpellInfo(32375))) return false;//immune to mass dispel
                    if (me->getLevel() < 72 && u->IsImmunedToSpell(sSpellMgr->GetSpellInfo(527))) return false;//immune to direct dispel
                }
                Unit::AuraMap const &Auras = u->GetOwnedAuras();
                for (Unit::AuraMap::const_iterator itr = Auras.begin(); itr != Auras.end(); ++itr)
                {
                    Aura* aura = itr->second;
                    SpellInfo const* Info = aura->GetSpellInfo();
                    if (Info->Dispel != DISPEL_MAGIC) continue;
                    if (Info->Attributes & (SPELL_ATTR0_PASSIVE | SPELL_ATTR0_HIDDEN_CLIENTSIDE)) continue;
                    if (checksteal && (Info->AttributesEx4 & SPELL_ATTR4_NOT_STEALABLE)) continue;
                    AuraApplication const* aurApp = aura->GetApplicationOfTarget(u->GetGUID());
                    if (aurApp && aurApp->IsPositive())
                    {
                        return true;
                    }
                }
            }
            return false;
        }
    private:
        Unit const* me;
        float m_range;
        bool checksteal;
        bot_ai const* ai;
        HostileDispelTargetCheck(HostileDispelTargetCheck const&);
};

class AffectedTargetCheck
{
    public:
        explicit AffectedTargetCheck(uint64 casterguid, float dist, uint32 spellId, Player const* groupCheck = 0, uint8 hostileCheckType = 0) :
        caster(casterguid), m_range(dist), spell(spellId), checker(groupCheck), needhostile(hostileCheckType)
        { if (checker->GetTypeId() != TYPEID_PLAYER) return; gr = checker->GetGroup(); }
        bool operator()(Unit* u)
        {
            if (caster && u->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                return false;
            if (needhostile == 0 && !u->IsHostileTo(checker)) return false;
            if (needhostile == 1 && !(gr && gr->IsMember(u->GetGUID()) && u->GetTypeId() == TYPEID_PLAYER)) return false;
            if (needhostile == 2 && !(gr && gr->IsMember(u->GetGUID()))) return false;
            if (needhostile == 3 && !u->IsFriendlyTo(checker)) return false;

            if (u->IsAlive() && checker->IsWithinDistInMap(u, m_range))
            {
                Unit::AuraMap const &Auras = u->GetOwnedAuras();
                for (Unit::AuraMap::const_iterator itr = Auras.begin(); itr != Auras.end(); ++itr)
                {
                    Aura* aura = itr->second;
                    if (aura->GetId() == spell)
                        if (caster == 0 || aura->GetCasterGUID() == caster)
                            return true;
                }
            }
            return false;
        }
    private:
        uint64 const caster;
        float m_range;
        uint32 const spell;
        Player const* checker;
        uint8 needhostile;
        Group const* gr;
        AffectedTargetCheck(AffectedTargetCheck const&);
};

class PolyUnitCheck
{
    public:
        explicit PolyUnitCheck(Unit const* unit, float dist, Unit const* currTarget) : me(unit), m_range(dist), mytar(currTarget) {}
        bool operator()(Unit* u)
        {
            if (!PvP && (u->ToPlayer() || (u->ToCreature() && u->ToCreature()->GetBotAI())))
                return false;
            if (u == mytar)
                return false;
            if (!me->IsWithinDistInMap(u, m_range))
                return false;
            if (!u->IsInCombat() || !u->IsAlive() || !u->GetVictim())
                return false;
            if (u->GetCreatureType() != CREATURE_TYPE_HUMANOID &&
                u->GetCreatureType() != CREATURE_TYPE_BEAST)
                return false;
            if (me->GetDistance(u) < 6 || mytar->GetDistance(u) < 5 ||
                (me->ToCreature()->GetBotClass() == CLASS_MAGE && u->GetHealthPct() < 70))
                return false;
            if (!u->InSamePhase(me))
                return false;
            if (!u->isTargetableForAttack())
                return false;
            if (!u->IsVisible())
                return false;
            if (me->ToCreature()->GetBotClass() == CLASS_MAGE ? !u->getAttackers().empty() : u->getAttackers().size() > 1)
                return false;
            if (!u->IsHostileTo(me))
                return false;
            if (u->IsPolymorphed() ||
                u->isFrozen() ||
                u->isInRoots() ||
                u->HasAura(51514)/*hex*/ ||
                u->HasAura(20066)/*repentance*/ ||
                //u->HasAuraTypeWithAffectMask(SPELL_AURA_PERIODIC_DAMAGE, sSpellMgr->GetSpellInfo(339)) || //entangling roots
                //u->HasAuraTypeWithAffectMask(SPELL_AURA_PERIODIC_DAMAGE, sSpellMgr->GetSpellInfo(16914)) || //hurricane
                //u->HasAuraTypeWithAffectMask(SPELL_AURA_PERIODIC_DAMAGE, sSpellMgr->GetSpellInfo(10)) || //blizzard
                //u->HasAuraTypeWithAffectMask(SPELL_AURA_PERIODIC_DAMAGE, sSpellMgr->GetSpellInfo(2121)) || //flamestrike
                //u->HasAuraTypeWithAffectMask(SPELL_AURA_PERIODIC_DAMAGE, sSpellMgr->GetSpellInfo(20116)) || //consecration
                u->HasAuraType(SPELL_AURA_PERIODIC_DAMAGE))
                return false;

            if (me->ToCreature()->GetBotClass() == CLASS_MAGE && !u->IsImmunedToSpell(sSpellMgr->GetSpellInfo(118)))//Polymorph
                return true;
            if (me->ToCreature()->GetBotClass() == CLASS_SHAMAN && !u->IsImmunedToSpell(sSpellMgr->GetSpellInfo(51514)))//Hex
                return true;

            return false;
        }
    private:
        Unit const* me;
        float m_range;
        Unit const* mytar;
        PolyUnitCheck(PolyUnitCheck const&);
};

class FearUnitCheck
{
    public:
        explicit FearUnitCheck(Unit const* unit, float dist = 30) : me(unit), m_range(dist) {}
        bool operator()(Unit* u)
        {
            if (!PvP && (u->ToPlayer() || (u->ToCreature() && u->ToCreature()->GetBotAI())))
                return false;
            if (!me->IsWithinDistInMap(u, m_range))
                return false;
            if (!u->InSamePhase(me))
                return false;
            if (!u->IsInCombat())
                return false;
            if (u->GetCreatureType() == CREATURE_TYPE_UNDEAD)
                return false;
            if (u->GetCreatureType() != CREATURE_TYPE_BEAST &&
                me->ToCreature()->GetBotClass() == CLASS_HUNTER)
                return false;
            if (!u->IsAlive())
                return false;
            if (!u->isTargetableForAttack())
                return false;
            if (!u->IsVisible())
                return false;
            if (u->getAttackers().size() > 1 && u->GetVictim() != me)
                return false;
            if (u->HasUnitState(UNIT_STATE_CONFUSED | UNIT_STATE_STUNNED | UNIT_STATE_FLEEING | UNIT_STATE_DISTRACTED | UNIT_STATE_CONFUSED_MOVE | UNIT_STATE_FLEEING_MOVE))
                return false;
            if (u->isFeared())
                return false;
            if (u->GetReactionTo(me) > REP_NEUTRAL)
                return false;

            if (me->ToCreature()->GetBotClass() == CLASS_WARLOCK &&
                !u->IsImmunedToSpell(sSpellMgr->GetSpellInfo(5782)))//fear rank1
                return true;
            if (me->ToCreature()->GetBotClass() == CLASS_HUNTER &&
                !u->IsImmunedToSpell(sSpellMgr->GetSpellInfo(1513)))//scare beast rank1
                return true;

            return false;
        }
    private:
        Unit const* me;
        float m_range;
        FearUnitCheck(FearUnitCheck const&);
};

class StunUnitCheck
{
    public:
        explicit StunUnitCheck(Unit const* unit, float dist = 20) : me(unit), m_range(dist) {}
        bool operator()(Unit* u)
        {
            if (!PvP && (u->ToPlayer() || (u->ToCreature() && u->ToCreature()->GetBotAI())))
                return false;
            if (!me->IsWithinDistInMap(u, m_range))
                return false;
            if (!u->IsInCombat())
                return false;
            if (me->GetVictim() == u)
                return false;
            if (me->GetTypeId() == TYPEID_UNIT)
                if (Player* mymaster = me->ToCreature()->GetBotOwner())
                    if (mymaster->GetVictim() == u)
                        return false;
            if (!u->InSamePhase(me))
                return false;
            if (u->GetReactionTo(me) > REP_NEUTRAL)
                return false;
            if (!u->IsAlive())
                return false;
            if (!u->IsVisible())
                return false;
            if (!u->isTargetableForAttack())
                return false;
            if (!u->getAttackers().empty())
                return false;
            if (u->HasAuraType(SPELL_AURA_PERIODIC_DAMAGE))
                return false;
            if (me->ToCreature()->GetBotClass() == CLASS_PALADIN &&
                !(u->GetCreatureType() == CREATURE_TYPE_HUMANOID ||
                u->GetCreatureType() == CREATURE_TYPE_DEMON ||
                u->GetCreatureType() == CREATURE_TYPE_DRAGONKIN ||
                u->GetCreatureType() == CREATURE_TYPE_GIANT ||
                u->GetCreatureType() == CREATURE_TYPE_UNDEAD))
                return false;
            if (me->ToCreature()->GetBotClass() == CLASS_HUNTER && u->isFeared())
                return false;
            if (me->GetDistance(u) < 10)//do not allow close cast to prevent break due to AOE damage
                return false;
            if (u->IsPolymorphed() ||
                u->HasAura(51514)/*hex*/ ||
                u->HasAura(20066)/*repentance*/ ||
                u->HasAuraWithMechanic((1<<MECHANIC_SHACKLE)|(1<<MECHANIC_SLEEP)|(1<<MECHANIC_DISORIENTED)))
                return false;
            if (me->ToCreature()->GetBotClass() == CLASS_PALADIN &&
                !u->IsImmunedToSpell(sSpellMgr->GetSpellInfo(20066)))//repentance
                return true;
            if (me->ToCreature()->GetBotClass() == CLASS_HUNTER &&
                !u->IsImmunedToSpell(sSpellMgr->GetSpellInfo(60210)))//freezing arrow effect
                return true;
            if (me->ToCreature()->GetBotClass() == CLASS_HUNTER &&
                !u->IsImmunedToSpell(sSpellMgr->GetSpellInfo(19386)))//wyvern sting rank 1
                return true;
            if (me->ToCreature()->GetBotClass() == CLASS_HUNTER &&
                !u->IsImmunedToSpell(sSpellMgr->GetSpellInfo(1991)))//scatter shot
                return true;

            return false;
        }
    private:
        Unit const* me;
        float m_range;
        StunUnitCheck(StunUnitCheck const&);
};

class UndeadCCUnitCheck
{
    public:
        explicit UndeadCCUnitCheck(Unit const* unit, float dist = 30, uint32 spell = 0) : me(unit), m_range(dist), m_spellId(spell) { if (!spell) return; }
        bool operator()(Unit* u)
        {
            if (!PvP && (u->ToPlayer() || (u->ToCreature() && u->ToCreature()->GetBotAI())))
                return false;
            if (!me->IsWithinDistInMap(u, m_range))
                return false;
            if (!u->InSamePhase(me))
                return false;
            if (!u->IsInCombat())
                return false;
            if (u->GetReactionTo(me) > REP_NEUTRAL)
                return false;
            if (!u->IsAlive())
                return false;
            if (!u->isTargetableForAttack())
                return false;
            if (!u->IsVisible())
                return false;
            if (me->GetVictim() == u && u->GetVictim() == me)
                return false;
            if (!u->getAttackers().empty())
                return false;
            if (u->GetCreatureType() != CREATURE_TYPE_UNDEAD && m_spellId == 9484)//shackle undead
                return false;
            //most horrible hacks
            if (u->GetCreatureType() != CREATURE_TYPE_UNDEAD &&
                u->GetCreatureType() != CREATURE_TYPE_DEMON &&
                (m_spellId == 2812 || m_spellId == 10326))//holy wrath or turn evil
                return false;
            if (u->HasUnitState(UNIT_STATE_CONFUSED | UNIT_STATE_STUNNED | UNIT_STATE_FLEEING | UNIT_STATE_DISTRACTED | UNIT_STATE_CONFUSED_MOVE | UNIT_STATE_FLEEING_MOVE))
                return false;
            if (u->HasAuraType(SPELL_AURA_PERIODIC_DAMAGE) && m_spellId == 9484)//shackle undead
                return false;
            if (!u->IsImmunedToSpell(sSpellMgr->GetSpellInfo(m_spellId)))
                return true;

            return false;
        }
    private:
        Unit const* me;
        float m_range;
        uint32 m_spellId;
        UndeadCCUnitCheck(UndeadCCUnitCheck const&);
};

class RootUnitCheck
{
    public:
        explicit RootUnitCheck(Unit const* unit, Unit const* mytarget, float dist = 30, uint32 spell = 0) : me(unit), curtar(mytarget), m_range(dist), m_spellId(spell)
        { if (!spell) return; }
        bool operator()(Unit* u)
        {
            if (!PvP && (u->ToPlayer() || (u->ToCreature() && u->ToCreature()->GetBotAI())))
                return false;
            if (u == curtar)
                return false;
            if (!me->IsWithinDistInMap(u, m_range))
                return false;
            if (!u->IsAlive())
                return false;
            if (!u->IsInCombat())
                return false;
            if (me->GetDistance(u) < 8)
                return false;
            if (!u->InSamePhase(me))
                return false;
            if (!u->IsVisible())
                return false;
            if (!u->isTargetableForAttack())
                return false;
            if (u->GetReactionTo(me) > REP_NEUTRAL)
                return false;
            if (u->isFrozen() || u->isInRoots())
                return false;
            if (!u->getAttackers().empty())
                return false;
            if (u->IsPolymorphed() ||
                u->HasAura(51514)/*hex*/ ||
                u->HasAura(20066)/*repentance*/ ||
                u->HasAuraWithMechanic(1<<MECHANIC_SHACKLE)/*shackle undead*/)
                return false;
            if (!u->IsImmunedToSpell(sSpellMgr->GetSpellInfo(m_spellId)))
                return true;

            return false;
        }
    private:
        Unit const* me;
        Unit const* curtar;
        float m_range;
        uint32 m_spellId;
        RootUnitCheck(RootUnitCheck const&);
};

class CastingUnitCheck
{
    public:
        explicit CastingUnitCheck(Unit const* unit, float mindist = 0.f, float maxdist = 30, bool friendly = false, uint32 spell = 0) :
        me(unit), min_range(mindist), max_range(maxdist), m_friend(friendly), m_spell(spell) {}
        bool operator()(Unit* u)
        {
            if (!m_friend && !PvP && (u->ToPlayer() || (u->ToCreature() && u->ToCreature()->GetBotAI())))
                return false;
            if (min_range > 0.1f && me->GetDistance(u) < min_range)
                return false;
            if (!me->IsWithinDistInMap(u, max_range))
                return false;
            if (!u->IsAlive())
                return false;
            if (!u->InSamePhase(me))
                return false;
            if (!u->IsVisible())
                return false;
            if (!m_friend && !u->isTargetableForAttack())
                return false;
            //if (!m_friend && u->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SILENCED))//prevent double silence
            //    return false;
            if (!u->IsNonMeleeSpellCast(false))
                return false;
            if (m_friend == (u->GetReactionTo(me) < REP_FRIENDLY))
                return false;
            if (m_spell == 10326 && //turn evil
                u->GetCreatureType() != CREATURE_TYPE_UNDEAD &&
                u->GetCreatureType() != CREATURE_TYPE_DEMON)
                return false;
            if (m_spell == 20066 && //repentance
                !(u->GetCreatureType() == CREATURE_TYPE_HUMANOID ||
                u->GetCreatureType() == CREATURE_TYPE_DEMON ||
                u->GetCreatureType() == CREATURE_TYPE_DRAGONKIN ||
                u->GetCreatureType() == CREATURE_TYPE_GIANT ||
                u->GetCreatureType() == CREATURE_TYPE_UNDEAD))
                return false;
            if (!m_spell || !u->IsImmunedToSpell(sSpellMgr->GetSpellInfo(m_spell)))
                return true;

            return false;
        }
    private:
        Unit const* me;
        float min_range, max_range;
        bool m_friend;
        uint32 m_spell;
        CastingUnitCheck(CastingUnitCheck const&);
};

class SecondEnemyCheck
{
    public:
        explicit SecondEnemyCheck(Unit const* unit, float dist, float splashdist, Unit const* currtarget, bot_ai const* m_ai) :
        me(unit), m_range(dist), m_splashrange(splashdist), mytar(currtarget), ai(m_ai) {}
        bool operator()(Unit* u)
        {
            if (!PvP && (u->ToPlayer() || (u->ToCreature() && u->ToCreature()->GetBotAI())))
                return false;
            if (u == mytar)
                return false;//We need to find SECONDARY target
            if (!u->IsInCombat())
                return false;
            if (u->isMoving() != mytar->isMoving())//only when both targets idle or both moving
                return false;
            if (!me->IsWithinDistInMap(u, m_range + 1.f))//distance check
                return false;
            if (mytar->GetDistance(u) > m_splashrange)//not close enough to each other
                return false;

            if (ai->CanBotAttack(u))
                return true;

            return false;
        }
    private:
        Unit const* me;
        float m_range, m_splashrange;
        Unit const* mytar;
        bot_ai const* ai;
        SecondEnemyCheck(SecondEnemyCheck const&);
};

class TranquilTargetCheck
{
    public:
        explicit TranquilTargetCheck(Unit const* unit, float mindist, float maxdist, bot_ai const* m_ai) :
        me(unit), min_range(mindist), max_range(maxdist), ai(m_ai) { }
        bool operator()(Unit* u)
        {
            if (!PvP && (u->ToPlayer() || (u->ToCreature() && u->ToCreature()->GetBotAI())))
                return false;
            if (u != me->GetVictim() &&//check hunter_bot::hunter_botAI::CheckTranquil(uint32)
                u->IsWithinDistInMap(me, max_range) &&
                u->GetDistance(me) > min_range &&
                u->IsAlive() &&
                u->InSamePhase(me) &&
                u->IsInCombat() &&
                u->isTargetableForAttack() &&
                u->IsVisible() &&
                u->GetReactionTo(me) < REP_NEUTRAL &&
                ai->IsInBotParty(u->GetVictim()))
            {
                if (u->IsImmunedToSpell(sSpellMgr->GetSpellInfo(19801))) return false;//immune to tranquilizing shot
                Unit::AuraMap const &Auras = u->GetOwnedAuras();
                for (Unit::AuraMap::const_iterator itr = Auras.begin(); itr != Auras.end(); ++itr)
                {
                    SpellInfo const* Info = itr->second->GetSpellInfo();
                    if (Info->Dispel != DISPEL_MAGIC && Info->Dispel != DISPEL_ENRAGE) continue;
                    if (Info->Attributes & (SPELL_ATTR0_PASSIVE | SPELL_ATTR0_HIDDEN_CLIENTSIDE)) continue;
                    AuraApplication const* aurApp = itr->second->GetApplicationOfTarget(u->GetGUID());
                    if (aurApp && aurApp->IsPositive())
                    {
                        return true;
                    }
                }
            }

            return false;
        }
    private:
        Unit const* me;
        float min_range, max_range;
        bot_ai const* ai;
        TranquilTargetCheck(TranquilTargetCheck const&);
};

class NearbyHostileUnitCheck
{
    public:
        explicit NearbyHostileUnitCheck(Unit const* unit, float maxdist, float mindist, bot_ai const* m_ai, bool forCC) :
        me(unit), max_range(maxdist), min_range(mindist), ai(m_ai), m_forCC(forCC) { }
        bool operator()(Unit* u)
        {
            if (!PvP && (u->ToPlayer() || (u->ToCreature() && u->ToCreature()->GetBotAI())))
                return false;
            if (!me->IsWithinDistInMap(u, max_range))
                return false;
            if (min_range > 0.1f && me->GetDistance(u) < min_range)
                return false;
            if (!u->IsInCombat())
                return false;
            if (!u->InSamePhase(me))
                return false;
            if (!ai->CanBotAttack(u))
                return false;
            if (ai->InDuel(u))
                return false;
            if (u->HasUnitState(UNIT_STATE_CONFUSED|UNIT_STATE_STUNNED|UNIT_STATE_FLEEING|UNIT_STATE_DISTRACTED|UNIT_STATE_CONFUSED_MOVE))
                return false;
            if (m_forCC && u->HasAuraType(SPELL_AURA_PERIODIC_DAMAGE))
                return false;

            if (ai->IsInBotParty(u->GetVictim()))
                return true;

            return false;
        }
    private:
        Unit const* me;
        float max_range, min_range;
        bot_ai const* ai;
        bool m_forCC;
        NearbyHostileUnitCheck(NearbyHostileUnitCheck const&);
};

#endif
