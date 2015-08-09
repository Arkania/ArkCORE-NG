/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * This file is NOT free software. Third-party users can NOT redistribute 
 * it or modify it. If you find it, you are either hacking something, or very 
 * lucky (presuming someone else managed to hack it).
 */

#ifndef DEF_BASTION_OF_TWILIGHT_H
#define DEF_BASTION_OF_TWILIGHT_H

#define BOTScriptName "instance_bastion_of_twilight"
#define MAX_ENCOUNTER 5

enum DataTypes
{
    // Encounters
    DATA_HALFUS                     = 1,
    DATA_VALIONA_THERALION          = 2,
    DATA_ASCENDANT_COUNCIL          = 3,
    DATA_CHOGALL                    = 4,
    DATA_SINESTRA                   = 5,

    // NPC GUIDs
    DATA_AC_PHASE                   = 6,
    DATA_FELUDIUS                   = 7,
    DATA_IGNACIOUS                  = 8,
    DATA_ARION                      = 9,
    DATA_TERRASTRA                  = 10,
    DATA_ELEMENTIUM_MONSTROSITY     = 11,
};

enum CreaturesIds
{
    // Halfus
    NPC_HALFUS_WORMBREAKER                      = 44600,
    // Valiona and Theralion
    NPC_VALIONA_BOT                             = 45992,
    NPC_THERALION_BOT                           = 45993,
    // Ascendant Lord Council
    NPC_ASCENDANT_COUNCIL                       = 45420,
    NPC_FELUDIUS                                = 43687,
    NPC_IGNACIOUS                               = 43686,
    NPC_ARION                                   = 43688,
    NPC_TERRASTRA                               = 43689,
    NPC_ELEMENTIUM_MONSTROSITY                  = 43735,
    // Cho'gall
    NPC_CHOGALL                                 = 43324,
    // Sinestra
    NPC_SINESTRA                                = 45213,

   // Intro's and cutscenes - Misc
    NPC_CHOGALL_HALFUS                          = 46965,
    NPC_CHOGALL_DRAGONS                         = 48142,
    NPC_CHOGALL_COUNCIL                         = 46900
};

enum Gameobjects
{
};

#endif // DEF_BASTION_OF_TWILIGHT_H
