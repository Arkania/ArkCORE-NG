/*
* Copyright (C) 2011-2017 ArkCORE <http://www.arkania.net/>
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 3 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
* 
*/

#ifndef DEF_SCRIPT_HELPERS_H_
#define DEF_SCRIPT_HELPERS_H_

enum Events
{
    EVENT_ACTIVATE_FIRE = 101,
    EVENT_ACTIVE_OBJECT_CD,
    EVENT_ANIMATION_START,
    EVENT_ANIMATION_STOP,
    EVENT_ANIMATION_SUBJECT,
    EVENT_ATTACK_PART_00,
    EVENT_ATTACK_PART_01,
    EVENT_ATTACK_PART_02,
    EVENT_ATTACK_PART_03,
    EVENT_ATTACK_PART_04,
    EVENT_ATTACK_PART_05,
    EVENT_ATTACK_PART_06,
    EVENT_ATTACK_PART_07,
    EVENT_ATTACK_PART_08,
    EVENT_ATTACK_PART_09,
    EVENT_ATTACK_SPELL,
    EVENT_BALLON_MESSAGE,
    EVENT_BEGIN_FLYING,
    EVENT_BEGIN_LANDING,
    EVENT_CAST_BOULDER,
    EVENT_CAST_COOLDOWN,
    EVENT_CAST_COOLDOWN_01,
    EVENT_CAST_COOLDOWN_02,
    EVENT_CAST_COOLDOWN_03,
    EVENT_CAST_COOLDOWN_04,
    EVENT_CHANGE_PHASE,
    EVENT_CAST_PLAYER,
    EVENT_CAST_SPELL_00,
    EVENT_CAST_SPELL_01,
    EVENT_CHECK_ARRIVEL_PLAYER,
    EVENT_CHECK_ATTACK,
    EVENT_CHECK_AURA,
    EVENT_CHECK_BOAT,
    EVENT_CHECK_FIGHT,
    EVENT_CHECK_FIRE,
    EVENT_CHECK_FOLLOWING,
    EVENT_CHECK_FOR_CREATURE,
    EVENT_CHECK_FOR_PLAYER,
    EVENT_CHECK_FOR_HEALTH,
    EVENT_CHECK_PLAYER,
    EVENT_CHECK_PLAYER_NEAR,
    EVENT_CHECK_POSITION,
    EVENT_CHECK_START_PARTY,
    EVENT_CHECK_TIMEOUT,
    EVENT_CLEAR_INVITE,
    EVENT_CLEAR_AREA_00,
    EVENT_CLEAR_AREA_01,
    EVENT_CLEAR_AREA_02,
    EVENT_CLEAR_AREA_03,
    EVENT_CLEAR_AREA_04,
    EVENT_CLEAR_AREA_05,
    EVENT_CLEAR_AREA_06,
    EVENT_CLEAR_AREA_07,
    EVENT_CLEAR_AREA_08,
    EVENT_CLEAR_AREA_09,
    EVENT_CLEAR_AREA_10,
    EVENT_COMBAT_STOP,
    EVENT_COOLDOWN_00,
    EVENT_COOLDOWN_01,
    EVENT_COOLDOWN_02,
    EVENT_COOLDOWN_03,
    EVENT_COOLDOWN_04,
    EVENT_COOLDOWN_05,
    EVENT_COOLDOWN_06,
    EVENT_COOLDOWN_07,
    EVENT_COOLDOWN_08,
    EVENT_COOLDOWN_09,
    EVENT_COOLDOWN_PLAYER_NEAR,
    EVENT_CREATE_WARRIER,
    EVENT_DELIVER_PACKET,
    EVENT_DESPAWN_PART_00,
    EVENT_DESPAWN_PART_01,
    EVENT_DESPAWN_PART_02,
    EVENT_DESPAWN_PART_03,
    EVENT_DESPAWN_PART_04,
    EVENT_EARTHQUAKE,
    EVENT_ENTER_CAR,
    EVENT_ENTER_VEHICLE,
    EVENT_EXIT_CAR,
    EVENT_EXIT_VEHICLE,
    EVENT_EXPLOSION,
    EVENT_FIGHT_PART_00,
    EVENT_FIGHT_PART_01,
    EVENT_FIGHT_PART_02,
    EVENT_FIGHT_PART_03,
    EVENT_FIND_TARGET,
    EVENT_FINISH,
    EVENT_GIVE_UP,
    EVENT_INIT_TARGET,
    EVENT_INIT_PLAYER,
    EVENT_INIT_VIDEO,
    EVENT_INIT_MOUNT,
    EVENT_INVISIBLE_OBJECT,
    EVENT_KILL_TARGET,
    EVENT_MASTER_RESET,
    EVENT_MELEE_ATTACK,
    EVENT_MOVE_ATTACK,
    EVENT_MOVE_HOME,
    EVENT_MOVE_PART0,
    EVENT_MOVE_PART1,
    EVENT_MOVE_PART2,
    EVENT_MOVE_PART3,
    EVENT_MOVE_PART4,
    EVENT_MOVE_PART5,
    EVENT_MOVE_PART6,
    EVENT_MOVE_PART7,
    EVENT_MOVEMENT_DELAY,
    EVENT_MOVEMENT_PAUSE,
    EVENT_MOVEMENT_START,
    EVENT_MOVEMENT_STOP,
    EVENT_MUSIC_PERIODIC,
    EVENT_PACKET_EXPLODE,
    EVENT_PERIODIC_CHEERING,
    EVENT_PARTY_COOLDOWN,
    EVENT_PHASE_UPDATE_00,
    EVENT_PLAY_PHASE_00,
    EVENT_PLAY_PHASE_01,
    EVENT_PLAY_PHASE_02,
    EVENT_PLAY_PHASE_03,
    EVENT_PLAY_COOLDOWN,
    EVENT_PLAY_PERIODIC_SOUND,
    EVENT_PLAY_PERIODIC_EMOTE,
    EVENT_PLAY_SOUND1,
    EVENT_PLAY_SOUND2,
    EVENT_PLAYING,
    EVENT_PLAYER_ENTER_VEHICLE,
    EVENT_PLAYER_EXIT,
    EVENT_PLAYER_LANDING,
    EVENT_PLAYER_LAUNCH,
    EVENT_PREPARE_00,
    EVENT_PREPARE_01,
    EVENT_PREPARE_02,
    EVENT_PREPARE_03,
    EVENT_PREPARE_04,
    EVENT_RANDOM_EMOTE,
    EVENT_RANDOM_CAST,
    EVENT_REMOVE_FIRE,
    EVENT_RESET_TARGET,
    EVENT_RESTART,
    EVENT_RUN_AWAY,
    EVENT_SAY_ATTACK,
    EVENT_SAY_HAVE_UNDERSTAND,
    EVENT_SAY_OUTCH,
    EVENT_SAY_THANKS,
    EVENT_SET_ACTIVE_TO_TRUE,
    EVENT_SET_ACTIVE_TO_FALSE,
    EVENT_SHOOT,
    EVENT_SHOOT_ON_DUMMY,
    EVENT_SHOW_FIGHT,
    EVENT_SPAWN_OBJECT_00,
    EVENT_SPAWN_OBJECT_01,
    EVENT_SPAWN_OBJECT_02,
    EVENT_SPAWN_OBJECT_03,
    EVENT_SPAWN_OBJECT_04,
    EVENT_SPAWN_OBJECT_05,
    EVENT_SPAWN_OBJECT_06,
    EVENT_SPAWN_OBJECT_07,
    EVENT_SPAWN_OBJECT_08,
    EVENT_SPAWN_OBJECT_09,
    EVENT_SPAWN_OBJECT_10,
    EVENT_SPELLCAST,
    EVENT_START_ANIM,
    EVENT_START_ANIM_01,
    EVENT_START_ANIM_02,
    EVENT_START_ANIM_03,
    EVENT_START_ANIM_04,
    EVENT_START_ANIM_05,
    EVENT_START_ANIM_06,
    EVENT_START_ANIM_07,
    EVENT_START_ANIM_08,
    EVENT_START_ANIM_09,
    EVENT_START_ANIMATION_PACKET,
    EVENT_START_FIGHT,
    EVENT_START_FLY,
    EVENT_START_FLYING,
    EVENT_START_FOLLOW,
    EVENT_START_FOLLOWING,
    EVENT_START_MOVEMENT,
    EVENT_START_MOVIE,
    EVENT_START_PARTY,
    EVENT_START_PLAY,
    EVENT_START_PLAY_GAME,
    EVENT_START_RESCUE_LIVE,
    EVENT_START_RUN_AWAY,
    EVENT_START_SPELL_01, 
    EVENT_START_SPELL_02, 
    EVENT_START_SPELL_03, 
    EVENT_START_SPELL_04, 
    EVENT_START_SPELL_05, 
    EVENT_START_TALK,
    EVENT_START_TELEPORT,
    EVENT_START_VIDEO,
    EVENT_START_WALK,
    EVENT_START_WAYPOINTS,
    EVENT_STOP_WAYPOINTS,
    EVENT_SUMMON_DEATHWING,
    EVENT_TALK,
    EVENT_TALK_COOLDOWN,
    EVENT_TALK_PART_00,
    EVENT_TALK_PART_01,
    EVENT_TALK_PART_02,
    EVENT_TALK_PART_03,
    EVENT_TALK_PART_04,
    EVENT_TALK_PART_05,
    EVENT_TALK_PART_06,
    EVENT_TALK_PART_07,
    EVENT_TALK_PART_08,
    EVENT_TALK_PART_09,
    EVENT_TALK_PART_10,
    EVENT_TALK_PART_11,
    EVENT_TALK_PART_12,
    EVENT_TALK_PART_13,
    EVENT_TALK_PART_14,
    EVENT_TALK_PART_15,
    EVENT_TALK_PART_16,
    EVENT_TALK_PART_17,
    EVENT_TALK_PART_18,
    EVENT_TALK_PART_19,
    EVENT_TALK_PART_20,
    EVENT_TALK_PART_21,
    EVENT_TALK_PART_22,
    EVENT_TALK_PART_23,
    EVENT_TALK_PART_24,
    EVENT_TALK_PART_25,
    EVENT_TALK_PERIODIC,
    EVENT_TALK_START,
    EVENT_TORCH_COOLDOWN,
    EVENT_TRIGGER_TRAP,
    EVENT_TELEPORT_00,
    EVENT_TELEPORT_01,
    EVENT_WAIT_FOR_NEW_SPEED,
    EVENT_WAIT_TO_MOVE,
    EVENT_WAIT_FOR_ACTION_00,
    EVENT_WAIT_FOR_ACTION_01,
    EVENT_WAIT_FOR_ACTION_02,
    EVENT_WAIT_FOR_ACTION_03,
    EVENT_WAIT_FOR_ACTION_04,
    EVENT_START_WALK_01,
    EVENT_START_WALK_02,
    EVENT_START_WALK_03,
    EVENT_START_WALK_04,
    EVENT_START_WALK_05,
    EVENT_START_WALK_06,
    EVENT_START_WALK_07,
    EVENT_START_WALK_08,
    EVENT_START_WALK_09,
    EVENT_WE_ARE_KILLED,
    ACTION_ACTIVATE_FIRE,
    ACTION_DELIVER_PACKET,
    ACTION_ENTER_CAR,
    ACTION_ERASE,
    ACTION_FOLLOW,
    ACTION_INSERT,
    ACTION_IS_PLAYER_NEAR,
    ACTION_MASTER_KILLED,
    ACTION_REMOVE_FIRE,
    ACTION_RESET_00,
    ACTION_RESET_01, 
    ACTION_RESET_02, 
    ACTION_RESET_03, 
    ACTION_RUN_AWAY,
    ACTION_SIZE_OF_LIST,
    ACTION_SPELL_HIT_00,
    ACTION_SPELL_HIT_01,
    ACTION_SPELL_HIT_02,
    ACTION_SPELL_HIT_03,
    ACTION_START_ANIM_01,
    ACTION_START_ANIM_02,
    ACTION_START_ANIM_03,
    ACTION_START_ANIM_04,
    ACTION_START_ANIM_05,
    ACTION_START_ANIM_06,
    ACTION_START_ANIM_07,
    ACTION_START_ANIM_08,
    ACTION_START_ANIM_09,
    ACTION_START_HELP_PLAYER,
    ACTION_START_RESCUE_LIVE,
    ACTION_START_RUN_AWAY,
    ACTION_START_TALK,
    ACTION_START_WALK,
    ACTION_START_WALK_01,
    ACTION_START_WALK_02,
    ACTION_START_WALK_03,
    ACTION_START_WALK_04,
    ACTION_STOP_HELP_PLAYER,
    ACTION_TEST,
    ACTION_WALK_TO_HOME_POSITION,

    DATA_GET_EVENTID,
    DATA_GUARD_INDEX,

    PLAYER_GUID = 99991,
    CASTER_GUID = 99992,
    CONTROLLER_GUID = 99993,
    PASSENGER_GUID = 99998,
};


// to filter std::list<*>, the list has a powerfull command .remove_if
// this command step's during all element's of the list and delete all where the operator-function returns true

// until now this it's beta, a small test for some functions

class IsNotEntry
{
public:
    explicit IsNotEntry(uint32 entry) : _entry(entry) { }

    bool operator()(WorldObject* obj) const
    {
        if (Creature* target = obj->ToCreature())
            return target->GetEntry() != _entry;

        return true;
    }

private:
    uint32 _entry;
};

class IsCreatureEntry
{
public:
    explicit IsCreatureEntry(uint32 entry) : _entry(entry) { }

    bool operator()(WorldObject* obj) const
    {
        if (Creature* target = obj->ToCreature())
            return target->GetEntry() == _entry;

        return true;
    }

private:
    uint32 _entry;
};

class IsNotEntryButPlayer
{
public:
    explicit IsNotEntryButPlayer(uint32 entry) : _entry(entry) { }

    bool operator()(WorldObject* obj) const
    {
        if (Player* player = obj->ToPlayer())
            return false;
        else if (Creature* target = obj->ToCreature())
            return target->GetEntry() != _entry;

        return true;
    }

private:
    uint32 _entry;
};

class IsNotInEntryList
{
public:
    explicit IsNotInEntryList(std::list<uint32>entrys) : _entrys(entrys) { }

    bool operator()(WorldObject* obj) const
    {
        if (Creature* target = obj->ToCreature())
            for (std::list<uint32>::const_iterator itr = _entrys.begin(); itr != _entrys.end(); ++itr)
                if (target->GetEntry() == *itr)
                    return false;

        return true;
    }

private:
    std::list<uint32> _entrys;
};

class IsNotInDBGuidList
{
public:
    explicit IsNotInDBGuidList(std::list<uint32>guids) : _guids(guids) { }

    bool operator()(WorldObject* obj) const
    {
        if (Creature* target = obj->ToCreature())
            for (std::list<uint32>::const_iterator itr = _guids.begin(); itr != _guids.end(); ++itr)
                if (target->GetGUIDLow() == *itr)
                    return false;

        return true;
    }

private:
    std::list<uint32> _guids;
};

class IsOutsideDistance
{
public:
    explicit IsOutsideDistance(Unit const* caster, float minDist, float maxDist) : _caster(caster), _minDist(minDist), _maxDist(maxDist) { }

    bool operator()(WorldObject* obj) const
    {
        if (Unit* target = obj->ToUnit())
        {
            float dist = target->GetDistance2d(_caster);
            if (dist > _minDist && dist < _maxDist)
                return false;
        }

        return true;
    }

private:
    Unit const* _caster;
    float _minDist;
    float _maxDist;
};

class IsNotBetweenAngle
{
public:
    explicit IsNotBetweenAngle(Unit const* caster, float minAngle, float maxAngle) : _caster(caster), _minAngle(minAngle), _maxAngle(maxAngle) { }

    bool operator()(WorldObject* obj) const
    {
        if (Unit* target = obj->ToUnit())
        {
            Position pos = target->GetPosition();
            float angle = _caster->GetAngle(&pos);
            if (angle > _minAngle && angle < _maxAngle)
                return false;
        }

        return true;
    }

private:
    Unit const* _caster;
    float _minAngle;
    float _maxAngle;
};

class IsNotFaction
{
public:
    explicit IsNotFaction(uint32 faction) : _faction(faction) { }

    bool operator()(WorldObject* obj) const
    {
        if (Unit* target = obj->ToUnit())
            return target->getFaction() != _faction;

        return true;
    }

private:
    uint32 _faction;
};

class IsNotNearPosition
{
public:
    explicit IsNotNearPosition(std::list<Position>position, float radius) : _position(position), _radius(radius) { }

    bool operator()(WorldObject* obj) const
    {
        if (Unit* target = obj->ToUnit())
            for (std::list<Position>::const_iterator itr = _position.begin(); itr != _position.end(); ++itr)
            {
                Position pos = *itr;
                return !(target->GetDistance2d(pos.GetPositionX(), pos.GetPositionY()) > _radius);
            }

        return true;
    }

private:
    std::list<Position> _position;
    float _radius;
};

class IsPlayer
{
public:
    explicit IsPlayer() { }

    bool operator()(WorldObject* obj) const
    {
        if (Player* player = obj->ToPlayer())
            return true;

        return false;
    }
};

class IsNotPlayer
{
public:
    explicit IsNotPlayer() { }

    bool operator()(WorldObject* obj) const
    {
        if (Player* player = obj->ToPlayer())
            return false;
        else
            return true;
    }
};

class IsNotPlayerGuid
{
public:
    explicit IsNotPlayerGuid(uint64 guid) : _guid(guid) { }

    bool operator()(WorldObject* obj) const
    {
        if (Player* player = obj->ToPlayer())
            return player->GetGUID() != _guid;

        return true;
    }

private:
    uint64 _guid;
};

class IsPowerType
{
public:
    explicit IsPowerType(Powers const power) : _power(power) { }

    bool operator()(WorldObject* obj) const
    {
        if (Unit* target = obj->ToUnit())
            return target->getPowerType() != _power;

        return true;
    }

private:
    Powers const _power;
};

class IsInRaidWith
{
public:
    explicit IsInRaidWith(Unit const* caster) : _caster(caster) { }

    bool operator()(WorldObject* obj) const
    {
        if (Unit* target = obj->ToUnit())
            return !_caster->IsInRaidWith(target);

        return true;
    }

private:
    Unit const* _caster;
};

class ReduceToOneRandomTarget
{
public:
    explicit ReduceToOneRandomTarget(std::list<WorldObject*>targets) : _targets(targets) { Init(); }

    void Init()
    {
        if (!_targets.empty())
        {
            uint32 rol = urand(0, _targets.size() - 1);
            std::list<WorldObject*>::iterator itr = _targets.begin();
            std::advance(itr, rol);
            _targetGUID = (*itr)->GetGUID();
            _targetEntry = (*itr)->GetEntry();
        }
    }

    bool operator()(WorldObject* obj) const
    {
        if (_targetGUID && obj)
            if (_targetGUID == obj->GetGUID())
                return false;

        return true;
    }

private:
    std::list<WorldObject*> _targets;
    uint64 _targetGUID = 0;
    uint32 _targetEntry = 0;
};

class CheckTargetsList
{
public:
    explicit CheckTargetsList(std::list<WorldObject*> targets) : _targets(targets) { }

    bool CheckIsNearPosition(std::list<Position> position, float radius)
    {
        for (std::list<WorldObject*>::const_iterator itr1 = _targets.begin(); itr1 != _targets.end(); ++itr1)
            for (std::list<Position>::const_iterator itr2 = position.begin(); itr2 != position.end(); ++itr2)
                if (((*itr1)->GetPosition().GetExactDist2d((*itr2).GetPositionX(), (*itr2).GetPositionY())) < radius)
                    return true;

        return false;
    }

private:
    std::list<WorldObject*> _targets;
};

class IsUnitDead
{
public:
    explicit IsUnitDead() { }

    bool operator()(WorldObject* obj) const
    {
        if (Unit* unit = obj->ToUnit())
            return unit->IsDead();

        return false;
    }
};

class IsUnitAlive
{
public:
    explicit IsUnitAlive() { }

    bool operator()(WorldObject* obj) const
    {
        if (Unit* unit = obj->ToUnit())
            return unit->IsAlive();

        return false;
    }
};

// remove randomly, only randomPct is left
class RandomCheck
{
public:
    explicit RandomCheck(float const randomPct) : m_pct(randomPct) { }

    bool operator()(WorldObject* obj) const
    {
        return (frand(0, 100) > m_pct);
    }

private:
    float const m_pct;
};

class RemoveFromList
{
public:
    explicit RemoveFromList(std::list<uint32> cList, bool RemoveWhenInList, bool RemovePlayer) : m_cList(cList), m_removeWhenInList(RemoveWhenInList), m_removePlayer(RemovePlayer) { }

    bool operator()(WorldObject* obj) const
    {
        if (Player* player = obj->ToPlayer())
            return m_removePlayer;
        else if (Creature* npc = obj->ToCreature())
            for (auto entry : m_cList)
                if (entry == obj->GetEntry())
                    return m_removeWhenInList;

        return true;
    }

private:
    std::list<uint32> m_cList;
    bool m_removeWhenInList;
    bool m_removePlayer;
};
// end beta test area

class FakeAttackMembers
{
public:
    FakeAttackMembers() : m_hasInit(false) {}
    FakeAttackMembers(Creature* me) : m_me(me), m_hasInit(false) {}

    void Initialize(std::list<uint32> allowedSparrList)
    {
        m_allowedSparrList = allowedSparrList;

        m_meleeWeaponId = m_me->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + BASE_ATTACK);
        m_rangedWeaponId = m_me->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + RANGED_ATTACK);

        int8 id = 1;
        EquipmentInfo const* einfo = sObjectMgr->GetEquipmentInfo(m_me->GetEntry(), id);
        if (!m_meleeWeaponId)
            m_meleeWeaponId = einfo->ItemEntry[BASE_ATTACK];
        if (!m_rangedWeaponId)
            m_rangedWeaponId = einfo->ItemEntry[RANGED_ATTACK];

        for (uint8 i = 0; i < CREATURE_MAX_SPELLS; ++i)
            if (m_me->m_spells[i])
            {
                uint32 spellId = m_me->m_spells[i];
                if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId))
                    if (spellInfo->RangeEntry)
                        if (spellInfo->RangeEntry->maxRangeHostile < 5.0f && spellInfo->DmgClass == SPELL_DAMAGE_CLASS_MELEE)
                            m_meeleeSpellInfo.push_back(spellInfo);
                        else if (spellInfo->RangeEntry->maxRangeHostile >= 5.0f && spellInfo->DmgClass == SPELL_DAMAGE_CLASS_RANGED)
                            m_rangedSpellInfo.push_back(spellInfo);
            }

        m_sparrGUID = 0;
        m_shootGUID = 0;
        m_nearestGUID = 0;
        std::list<Creature*> cList = m_me->FindAllCreaturesInRange(30.0f);
        float dist = 30.0f;
        for (auto npc : cList)
            if (IsSparringPartner(npc))
            {
                float d = m_me->GetDistance(npc);
                if (d < 5.0f)
                {
                    if (d < dist)
                    {
                        dist = d;
                        m_nearestGUID = npc->GetGUID();
                    }
                    sparrList.push_back(npc->GetGUID());
                }
                else
                    shootList.push_back(npc->GetGUID());
            }
        m_hasInit = true;
    }

    bool IsSparringPartner(Unit* attacker)
    {
        if (Creature* creature = attacker->ToCreature())
        {
            uint32 entry = creature->GetEntry();
                if (m_me->IsWithinLOSInMap(creature))
                    for (auto e : m_allowedSparrList)
                        if (e == entry)
                            return true;
        }

        return false;
    }

    bool IsMeeleAttack()
    {
        return sparrList.size() ? true : false;
    }

    Creature* GetSparringPartner()
    {
        if (!m_sparrGUID && m_nearestGUID)
            m_sparrGUID = m_nearestGUID;


        if (!m_sparrGUID)
        {
            std::list<Creature*> cList;
            for (auto npc : sparrList)
                if (Creature* target = ObjectAccessor::GetCreature(*m_me, npc))
                    if (!target->IsDead())
                        cList.push_back(target);

            if (cList.size() > 0)
            {
                uint32 rol = urand(0, cList.size() - 1);
                std::list<Creature*>::const_iterator itr = cList.begin();
                std::advance(itr, rol);
                m_sparrGUID = (*itr)->GetGUID();
            }
        }

        if (Creature* creature = ObjectAccessor::GetCreature(*m_me, m_sparrGUID))
            if (!creature->IsDead())
                return creature;

        m_sparrGUID = 0;
        return nullptr;
    }

    Creature* GetRangedPartner()
    {
        if (Creature* creature = ObjectAccessor::GetCreature(*m_me, m_shootGUID))
            if (creature->IsDead())
                m_shootGUID = 0;

        if (shootList.size() && m_rangedSpellInfo.size() & m_rangedWeaponId)
        {
            if (!m_shootGUID)
            {
                std::list<Creature*> cList;
                for (auto npc : shootList)
                    if (Creature* target = ObjectAccessor::GetCreature(*m_me, npc))
                        if (!target->IsDead())
                            cList.push_back(target);

                if (cList.size() > 0)
                {
                    uint32 rol = urand(0, cList.size() - 1);
                    std::list<Creature*>::const_iterator itr = cList.begin();
                    std::advance(itr, rol);
                    m_shootGUID = (*itr)->GetGUID();
                }
            }

            if (Creature* creature = ObjectAccessor::GetCreature(*m_me, m_shootGUID))
                if (!creature->IsDead())
                    return creature;
        }

        m_shootGUID = 0;
        return nullptr;
    }

    uint32 GetRangedSpellId()
    {
        switch (m_rangedSpellInfo.size())
        {
        case 0:
            return 0;
        default:
            uint32 rol = urand(0, m_rangedSpellInfo.size() - 1);
            std::list<const SpellInfo*>::const_iterator itr = m_rangedSpellInfo.begin();
            std::advance(itr, rol);
            return (*itr)->Id;
        }
        return 0;
    }

    bool m_hasInit;
private:
    Creature* m_me;
    std::list<uint32> m_allowedSparrList;
    uint64   m_nearestGUID;
    uint64   m_sparrGUID;
    uint64   m_shootGUID;
    std::list<uint64> sparrList;
    std::list<uint64> shootList;
    uint32 m_meleeWeaponId;
    std::list<const SpellInfo*> m_meeleeSpellInfo;
    uint32 m_rangedWeaponId;
    std::list<const SpellInfo*>  m_rangedSpellInfo;
};

#endif
