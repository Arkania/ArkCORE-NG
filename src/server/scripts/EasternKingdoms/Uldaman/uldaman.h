/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
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
    // BossEncounters
    ENC_REVELOSH = 0,
    ENC_THE_LOST_DWARVES,
    ENC_IRONAYA,
    ENC_OBSIDIAN_SENTINEL,
    ENC_ANCIENT_STONE_KEEPER,
    ENC_GALGANN_FIREHAMMER,
    ENC_GRIMLOK,
    ENC_ARCHAEDAS,
    MAX_BOSS_ENCOUNTERS
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
    DATA_ECHOMOK_DOOR,
    DATA_KEYSTONE,
    DATA_ALTAR_OF_THE_KEEPER,
    DATA_ALTAR_OF_ARCHAEDAS,
    MAX_DATA_ENCOUNTER
};

enum eBoss
{
    BOSS_REVELOSH               = 6910,
    BOSS_BAELOG                 = 6906,
    BOSS_ERIC                   = 6907,
    BOSS_OLAV                   = 6908,
    BOSS_IRONAYA                = 7228,
    BOSS_OBSIDIAN_SENTINEL      = 7023,
    BOSS_ANCIENT_STONE_KEEPER   = 7206,
    BOSS_GALGANN_FIREHAMMER     = 7291,
    BOSS_GRIMLOK                = 4854,
    BOSS_ARCHAEDAS              = 2748,
};

enum eGameObject
{
    GO_TEMPLE_DOOR_1        = 124368,
    GO_TEMPLE_DOOR_2        = 124367,
    GO_TEMPLE_DOOR_3        = 141869,
    GO_ANCIENT_VAULT_DOOR   = 124369,
    GO_IRONAYA_SEAL_DOOR    = 124372,
    GO_ECHOMOK_DOOR         = 124370,
    GO_KEYSTONE             = 124371,
    GO_ALTAR_OF_THE_KEEPER  = 130511,
    GO_ALTAR_OF_ARCHAEDAS   = 133234,
};

enum eNpc
{
    NPC_EARTHEN_GUARDIAN    = 7076,
    NPC_EARTHEN_CUSTODIAN   = 7309,
    NPC_VAULT_WARDER        = 10120,
};

enum eSpells
{
    SPELL_ARCHAEDAS_AWAKEN          = 10347,
    SPELL_AWAKEN_VAULT_WALKER       = 10258,
    SPELL_CRYSTALLINE_SLUMBER       = 3636,
    SPELL_ARCINGSMASH               = 8374,
    SPELL_KNOCKAWAY                 = 10101,
    SPELL_WSTOMP                    = 11876,
    SPELL_GROUND_TREMOR             = 6524,   
    SPELL_BOSS_OBJECT_VISUAL        = 11206,
    SPELL_BOSS_AGGRO                = 10340,
    SPELL_SUB_BOSS_AGGRO            = 11568,
    SPELL_AWAKEN_EARTHEN_GUARDIAN   = 10252,
    SPELL_STONED                    = 10255,
    SPELL_SELF_DESTRUCT             = 9874,
    SPELL_AWAKEN_EARTHEN_DWARF      = 10259,

};

enum eEvents
{
    EVENT_SUB_BOSS_AGGRO = 2228
};

enum eAction
{
    ACTION_AWAKE = 1,
};

enum eTimerEvent
{
    EVENT_CHECK_HEALTH = 1,
    EVENT_AWAKE_HELP = 2,
};

enum eQuest
{
    QUEST_HIDDEN_CHAMBER = 2240
};

enum eDoorState
{
    OpenState = 1,
    CloseState = 2,
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
