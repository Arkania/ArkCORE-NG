/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

#ifndef DEF_ULDAMAN_H
#define DEF_ULDAMAN_H

#define ULScriptName "instance_uldaman"

enum eEncounters
{
    ENC_REVELOSH = 0,
    ENC_THE_LOST_DWARVES,
    ENC_IRONAYA,
    ENC_OBSIDIAN_SENTINEL,
    ENC_ANCIENT_STONE_KEEPER,
    ENC_GALGANN_FIREHAMMER,
    ENC_GRIMLOK,
    ENC_ARCHAEDAS,
    ENC_IRONAYA_SEAL,   // door animation and save state.
    MAX_BOSS_ENCOUNTER
};

enum eDataTypes
{
    DATA_REVELOSH = 0,
    DATA_BAELOG,
    DATA_ERIC,
    DATA_OLAV,
    DATA_IRONAYA,
    DATA_OBSIDIAN_SENTINEL,
    DATA_ANCIENT_STONE_KEEPER,
    DATA_GALGANN_FIREHAMMER,
    DATA_GRIMLOK,
    DATA_ARCHAEDAS,
    DATA_TEMPLE_DOOR_1,
    DATA_TEMPLE_DOOR_2,
    DATA_TEMPLE_DOOR_3,
    DATA_ANCIENT_VAULT_DOOR,
    DATA_IRONAYA_SEAL_DOOR,
    DATA_KEYSTONE,
    DATA_ECHOMOK_DOOR,
    DATA_ALTAR_OF_THE_KEEPER,
    MAX_DATA_ENCOUNTER
};

enum eBoss
{
    BOSS_REVELOSH = 6910,
    BOSS_BAELOG = 6906,
    BOSS_ERIC = 6907,
    BOSS_OLAV = 6908,
    BOSS_IRONAYA = 7228,
    BOSS_OBSIDIAN_SENTINEL = 7023,
    BOSS_ANCIENT_STONE_KEEPER = 7206,
    BOSS_GALGANN_FIREHAMMER = 7291,
    BOSS_GRIMLOK = 4854,
    BOSS_ARCHAEDAS = 2748,
};

enum eGameObject
{
    GO_TEMPLE_DOOR_1        = 124368,
    GO_TEMPLE_DOOR_2        = 124367,
    GO_TEMPLE_DOOR_3        = 141869,
    GO_ANCIENT_VAULT_DOOR   = 124369,
    GO_IRONAYA_SEAL_DOOR    = 124372,
    GO_KEYSTONE             = 124371,
    GO_ALTAR_OF_THE_KEEPER  = 130511,
    GO_ECHOMOK_DOOR         = 124370,
};

DoorData const doorData[] =
{
    { GO_TEMPLE_DOOR_1,         DATA_ARCHAEDAS,             DOOR_TYPE_ROOM, BOUNDARY_NONE },
    { GO_TEMPLE_DOOR_2,         DATA_ALTAR_OF_THE_KEEPER,   DOOR_TYPE_ROOM, BOUNDARY_NONE },
    { GO_TEMPLE_DOOR_3,         DATA_ARCHAEDAS,             DOOR_TYPE_ROOM, BOUNDARY_NONE },
    { GO_ANCIENT_VAULT_DOOR,    DATA_ANCIENT_VAULT_DOOR,    DOOR_TYPE_ROOM, BOUNDARY_NONE },
    { GO_IRONAYA_SEAL_DOOR,     DATA_IRONAYA_SEAL_DOOR,     DOOR_TYPE_ROOM, BOUNDARY_NONE },
    { GO_ECHOMOK_DOOR,          DATA_OBSIDIAN_SENTINEL,     DOOR_TYPE_ROOM, BOUNDARY_NONE },
    { 0,                        0,                          DOOR_TYPE_ROOM, BOUNDARY_NONE } // END
};

enum eSpells
{
    SPELL_ARCHAEDAS_AWAKEN = 10347,
    SPELL_AWAKEN_VAULT_WALKER = 10258,
    SPELL_CRYSTALLINE_SLUMBER = 3636,
};

enum eEvents
{
    EVENT_SUB_BOSS_AGGRO = 2228
};

enum eQuest
{
    QUEST_HIDDEN_CHAMBER = 2240
};

template<class AI>
CreatureAI* GetUldamanAI(Creature* creature)
{
    if (InstanceMap* instance = creature->GetMap()->ToInstanceMap())
        if (instance->GetInstanceScript())
            if (instance->GetScriptId() == sObjectMgr->GetScriptId(ULScriptName))
                return new AI(creature);

    return NULL;
}

template<class AI, class T>
AI* GetUldamanAI(T* obj)
{
    return GetInstanceAI<AI, T>(obj, ULScriptName);
}

#endif
