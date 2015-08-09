/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * THIS particular file is NOT free software; third-party users 
 * should NOT have access to it, redistribute it or modify it. :)
 */

#ifndef DEF_TIME_END_H
#define DEF_TIME_END_H

enum Data
{
    DATA_FIRST_ENCOUNTER,
    DATA_SECOND_ENCOUNTER,
    DATA_LAST_ENCOUNTER,

    // Misc
    DATA_JAINA_PICKED_STATE,
};

enum Bosses
{
    BOSS_ECHO_OF_SYLVANAS,
    BOSS_ECHO_OF_BAINE,
    BOSS_MUROZOND,
    BOSS_ECHO_OF_TYRANDE,
    BOSS_ECHO_OF_JAINA,
};

enum GameObjectIds
{
    MUROZOND_CACHE                   = 209547,
    GO_ET_TELEPORT                   = 209438,
};

enum CreatureIds
{
    NPC_ECHO_OF_JAINA               = 54445,
    NPC_ECHO_OF_BAINE               = 54431,
    NPC_ECHO_OF_SYLVANAS            = 54123,
    NPC_ECHO_OF_TYRANDE             = 54544,
    NPC_MUROZOND                    = 54432,
};

enum WorldStatesET
{
    WORLDSTATE_SHOW_FRAGMENTS       = 6046,
    WORLDSTATE_FRAGMENTS_COLLECTED  = 6025,
};

#endif
