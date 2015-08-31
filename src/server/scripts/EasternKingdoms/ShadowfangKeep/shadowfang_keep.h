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

#ifndef DEF_SHADOWFANG_H
#define DEF_SHADOWFANG_H

#define SKScriptName    "instance_shadowfang_keep"
#define SKScriptId      33

enum Bosses // boss bit value given by DungeonEncounter.dbc
{
    BOSS_BARON_ASHBURY = 0,
    BOSS_BARON_SILVERLAINE,
    BOSS_COMMANDER_SPRINGVALE,
    BOSS_LORD_WALDEN,
    BOSS_LORD_GODFREY,
    MAX_BOSS_ENCOUNTERS
};

enum eExtraEncounters // additional bit values, no official value 
{
    TYPE_DOOR_COURTYARD = MAX_BOSS_ENCOUNTERS,
    TYPE_DOOR_SORCERER,
    TYPE_DOOR_ARUGAL,
    TYPE_DOOR_1,
    TYPE_DOOR_2,
    TYPE_DOOR_3,
    TYPE_FREE_NPC,  // if courtyard door is been opened 
    TYPE_RETHILGORE,
    TYPE_FENRUS,
    TYPE_NANDOS,
    TYPE_CROWN,
    MAX_EXTRA_ENCOUNTERS
};


enum Data64 
{
    DATA_BARON_ASHBURY = 0,
    DATA_BARON_SILVERLAINE,
    DATA_COMMANDER_SPRINGVALE,
    DATA_LORD_WALDEN,
    DATA_LORD_GODFREY,
    DATA_PRISON_DOOR1,
    DATA_PRISON_LEVER1,
    DATA_PRISON_DOOR2,
    DATA_PRISON_LEVER2,
    DATA_PRISON_DOOR3,
    DATA_PRISON_LEVER3,
    DATA_COURTYARD_DOOR,
    DATA_SORCERER_DOOR,
    DATA_ARUGAL_DOOR,
    DATA_ASH,
    DATA_ADA,
    DATA_ARCHMAGE_ARUGAL,
    DATA_ARUGAL_VOIDWALKER,
    DATA_FRYE,
    DATA_HUMMEL,
    DATA_BAXTER,
    DATA_TORMENTED_OFFICER,
    DATA_WAILING_GUARDSMAN,
    MAX_DATA_ENCOUNTER
};

enum CreaturesIDs
{
    NPC_FRYE                        = 36272,
    NPC_HUMMEL                      = 36296,
    NPC_BAXTER                      = 36565,
    NPC_TORMENTED_OFFICER           = 50615,
    NPC_WAILING_GUARDSMAN           = 50613,
    NPC_BLOODTHIRSTY_GHOUL          = 50561,
    // Bosses
    NPC_LORD_WALDEN                 = 46963,
    NPC_BARON_ASHBURY               = 46962,
    NPC_BARON_SILVERLAINE           = 3887,
    NPC_LORD_GODFREY                = 46964,
    NPC_COMMANDER_SPRINGVALE        = 4278,
    NPC_ASH                         = 3850,
    NPC_ADA                         = 3849,
    NPC_ARCHMAGE_ARUGAL             = 4275,
    NPC_ARUGAL_VOIDWALKER           = 4627,
};

enum GameObjectIDs
{
    GO_COURTYARD_DOOR               = 18895, //door to open when talking to NPC's
    GO_SORCERER_DOOR                = 18972, //door to open when Fenrus the Devourer
    GO_ARUGAL_DOOR                  = 18971, //door to open when Wolf Master Nandos
    GO_PRISON_DOOR1                 = 18934,
    GO_PRISON_LEVER1                = 18900,
    GO_PRISON_DOOR2                 = 18936,
    GO_PRISON_LEVER2                = 18901,
    GO_PRISON_DOOR3                 = 18935,
    GO_PRISON_LEVER3                = 101811,
};

enum Achievements
{
    ACHIEV_PARDON_DENIED              = 5503,
    ACHIEV_TO_THE_GROUND              = 5504,
    ACHIEV_BULLET_TIME                = 5505,
};

DoorData const doorData[] =
{
    { GO_COURTYARD_DOOR, DATA_COURTYARD_DOOR, DOOR_TYPE_PASSAGE, BOUNDARY_NONE },
    { GO_SORCERER_DOOR, DATA_SORCERER_DOOR, DOOR_TYPE_PASSAGE, BOUNDARY_NONE },
    { GO_ARUGAL_DOOR, DATA_ARUGAL_DOOR, DOOR_TYPE_PASSAGE, BOUNDARY_NONE },
    { GO_PRISON_DOOR1, DATA_PRISON_DOOR1, DOOR_TYPE_PASSAGE, BOUNDARY_NONE },
    { GO_PRISON_DOOR2, DATA_PRISON_DOOR2, DOOR_TYPE_PASSAGE, BOUNDARY_NONE },
    { GO_PRISON_DOOR3, DATA_PRISON_DOOR3, DOOR_TYPE_PASSAGE, BOUNDARY_NONE },
    { 0, 0, DOOR_TYPE_ROOM, BOUNDARY_NONE }, // END
};

template<class AI>
CreatureAI* GetShadowfangKeepAI(Creature* creature)
{
    if (InstanceMap* instance = creature->GetMap()->ToInstanceMap())
        if (instance->GetInstanceScript())
            if (instance->GetScriptId() == sObjectMgr->GetScriptId(SKScriptName))
                return new AI(creature);

    return NULL;
}

template<class AI, class T>
AI* GetShadowfangKeepAI(T* obj)
{
    return GetInstanceAI<AI, T>(obj, SKScriptName);
}


#endif

