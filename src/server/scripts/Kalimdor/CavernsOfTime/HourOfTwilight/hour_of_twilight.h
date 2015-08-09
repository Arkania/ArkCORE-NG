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

#ifndef DEF_HOUR_OF_TWILIGHT_H
#define DEF_HOUR_OF_TWILIGHT_H

#define MAX_ENCOUNTERS 3

enum Data
{
    DATA_ARCURION       = 1,
    DATA_ASIRA          = 2,
    DATA_BENEDICTUS     = 3,
    DATA_THRALL_1       = 4,
};

enum CreatureIds
{
    // Bosses
    BOSS_ARCURION           = 54590,
    BOSS_ASIRA              = 54968,
    BOSS_BENEDICTUS         = 54938,

    //Event Npcs
    NPC_THRALL_1            = 54548,

    NPC_FROZEN_SERVITOR     = 54555,
    NPC_CRYSTAL_ELEMENTAR   = 55559,

    NPC_GLOWING_EYES_1  = 54522,
    NPC_GLOWING_EYES_2  = 54599,
};

#endif