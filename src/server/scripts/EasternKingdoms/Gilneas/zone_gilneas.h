/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
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
 */

#ifndef DEF_GILNEAS_H
#define DEF_GILNEAS_H


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