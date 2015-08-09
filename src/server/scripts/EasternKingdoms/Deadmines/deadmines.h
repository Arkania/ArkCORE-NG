/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
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

#ifndef DEF_DEADMINES_H
#define DEF_DEADMINES_H

#define DMScriptName "instance_deadmines"

enum Bosses
{
    BOSS_ADMIRAL_RIPSNARL = 0,
    BOSS_CAPTAIN_COOKIE,
    BOSS_FOO_REAPER_5000,
    BOSS_GLUBTOK,
    BOSS_HELIX_GEARBREAKER,
    BOSS_VANESSA_VANCLEEF,
    MAX_BOSS_ENCOUNTER
};

enum Data64
{
    DATA_ADMIRAL_RIPSNARL = 0,
    DATA_CAPTAIN_COOKIE,
    DATA_FOO_REAPER_5000,
    DATA_GLUBTOK,
    DATA_HELIX_GEARBREAKER,
    DATA_VANESSA_VANCLEEF,
    DATA_LUMBERING_OAF,
    DATA_MR_SMITE,
    DATA_MR_SMITE_CHEST,
    DATA_FACTORY_DOOR,
    DATA_FACTORY_DOOR_LEVER,
    DATA_HEAVY_DOOR2,
    DATA_MASTROOM_DOOR,
    DATA_MASTROOM_DOOR_LEVER,
    DATA_HEAVY_DOOR4,
    DATA_FOUNDRY_DOOR,
    DATA_FOUNDRY_DOOR_LEVER,
    DATA_IRONCLAD_DOOR,
    DATA_IRONCLAD_DOOR_LEVER,
    DATA_DEFIAS_CANNON,
    MAX_DATA_ENCOUNTER
};

enum GameObjectsIds
{
    GO_FACTORY_DOOR             = 13965,
    GO_FACTORY_DOOR_LEVER       = 101831,
    GO_HEAVY_DOOR2              = 17173,
    GO_MASTROOM_DOOR            = 16400,
    GO_MASTROOM_DOOR_LEVER      = 101832,
    GO_HEAVY_DOOR4              = 17174,
    GO_FOUNDRY_DOOR             = 16399,
    GO_FOUNDRY_DOOR_LEVER       = 101834,
    GO_IRONCLAD_DOOR            = 16397,
    GO_IRONCLAD_DOOR_LEVER      = 101833,
    GO_DEFIAS_CANNON            = 16398,
    GO_MR_SMITE_CHEST           = 144111,
};

enum CreatureIds
{
    NPC_ADMIRAL_RIPSNARL    = 47626,
    NPC_CAPTAIN_COOKIE      = 47739,
    NPC_FOO_REAPER_5000     = 43778,
    NPC_GLUBTOK             = 47162,
    NPC_LUMBERING_OAF       = 47297,
    NPC_HELIX_GEARBREAKER   = 47296,
    NPC_MR_SMITE            = 646,
    NPC_VANESSA_VANCLEEF    = 49541,


};

template<class AI>
CreatureAI* GetDeadminesAI(Creature* creature)
{
    if (InstanceMap* instance = creature->GetMap()->ToInstanceMap())
        if (instance->GetInstanceScript())
            if (instance->GetScriptId() == sObjectMgr->GetScriptId(DMScriptName))
                return new AI(creature);

    return NULL;
}

template<class AI, class T>
AI* GetDeadminesAI(T* obj)
{
    return GetInstanceAI<AI, T>(obj, DMScriptName);
}

#endif
