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
    EVENT_ANIMATION_SUBJECT = 101,
    EVENT_ATTACK_SPELL,
    EVENT_BALLON_MESSAGE,
    EVENT_BEGIN_FLYING,
    EVENT_BEGIN_LANDING,
    EVENT_CAST_COOLDOWN,
    EVENT_CAST_COOLDOWN_01,
    EVENT_CAST_COOLDOWN_02,
    EVENT_CAST_COOLDOWN_03,
    EVENT_CAST_COOLDOWN_04,
    EVENT_CAST_SPELL_00,
    EVENT_CAST_SPELL_01,
    EVENT_CHECK_BOAT,
    EVENT_CHECK_FIGHT,
    EVENT_CHECK_FIRE,
    EVENT_CHECK_FOLLOWING,
    EVENT_CHECK_FOR_CREATURE,
    EVENT_CHECK_FOR_PLAYER,
    EVENT_CHECK_PLAYER,
    EVENT_CHECK_POSITION,
    EVENT_CHECK_START_PARTY,
    EVENT_CHECK_TIMEOUT,
    EVENT_COMBAT_STOP,
    EVENT_COOLDOWN_00,
    EVENT_COOLDOWN_01,
    EVENT_COOLDOWN_PLAYER_NEAR,
    EVENT_CREATE_WARRIER,
    EVENT_DELIVER_PACKET,
    EVENT_DESPAWN,
    EVENT_EARTHQUAKE,
    EVENT_ENTER_CAR,
    EVENT_ENTER_VEHICLE,
    EVENT_EXIT_CAR,
    EVENT_EXIT_VEHICLE,
    EVENT_FIGHT_PART_00,
    EVENT_FIGHT_PART_01,
    EVENT_FIGHT_PART_02,
    EVENT_FIGHT_PART_03,
    EVENT_FIND_TARGET,
    EVENT_GIVE_UP,
    EVENT_INVISIBLE_OBJECT,
    EVENT_KILL_TARGET,
    EVENT_MASTER_RESET,
    EVENT_MOVE_ATTACK,
    EVENT_MOVE_HOME,
    EVENT_MOVE_PART1,
    EVENT_MOVE_PART2,
    EVENT_MOVE_PART3,
    EVENT_MOVE_PART4,
    EVENT_MOVE_PART5,
    EVENT_MOVE_PART6,
    EVENT_MOVE_PART7,
    EVENT_MUSIC_PERIODIC,
    EVENT_PACKET_EXPLODE,
    EVENT_PERIODIC_CHEERING,
    EVENT_PARTY_COOLDOWN,
    EVENT_PLAY_COOLDOWN,
    EVENT_PLAY_PERIODIC_SOUND,
    EVENT_PLAY_PERIODIC_EMOTE,
    EVENT_PLAY_SOUND1,
    EVENT_PLAY_SOUND2,
    EVENT_PLAYING,
    EVENT_PLAYER_EXIT,
    EVENT_RANDOM_EMOTE,
    EVENT_RANDOM_CAST,
    EVENT_RESET_TARGET,
    EVENT_SAY_HAVE_UNDERSTAND,
    EVENT_SAY_OUTCH,
    EVENT_SHOOT_ON_DUMMY,
    EVENT_SHOW_FIGHT,
    EVENT_SPAWN_OBJECT,
    EVENT_SPELLCAST,
    EVENT_START_ANIMATION_PACKET,
    EVENT_START_FLYING,
    EVENT_START_FOLLOW,
    EVENT_START_PARTY,
    EVENT_START_PLAY,
    EVENT_START_PLAY_GAME,
    EVENT_START_RESCUE_LIVE,
    EVENT_START_TALK,
    EVENT_START_WALK,
    EVENT_START_FLY,
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
    EVENT_TALK_PERIODIC,
    EVENT_TORCH_COOLDOWN,
    EVENT_TRIGGER_TRAP,
    EVENT_WAIT_FOR_NEW_SPEED,
    EVENT_WAIT_TO_MOVE,
    EVENT_WE_ARE_KILLED,

    ACTION_DELIVER_PACKET,
    ACTION_ENTER_CAR,
    ACTION_ERASE,
    ACTION_FOLLOW,
    ACTION_INSERT,
    ACTION_MASTER_KILLED,
    ACTION_RUN_AWAY,
    ACTION_SIZE_OF_LIST,
    ACTION_START_HELP_PLAYER,
    ACTION_START_RESCUE_LIVE,
    ACTION_START_TALK,
    ACTION_STOP_HELP_PLAYER,

    PLAYER_GUID = 99991,
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

// end beta test area



#endif
