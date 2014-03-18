/*
 *
 * Copyright (C) 2011-2014 ArkCORE <http://www.arkania.net/>
 *
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 *
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

#define MAX_ENCOUNTER              9

enum DataTypes
{
    TYPE_FREE_NPC                     = 1,
    TYPE_RETHILGORE                   = 2,
    TYPE_FENRUS                       = 3,
    TYPE_NANDOS                       = 4,
    TYPE_CROWN                        = 5,
    DATA_LORD_WALDEN_EVENT            = 6,
    DATA_BARON_ASHBURY_EVENT          = 7,
    DATA_BARON_SILVERLAINE_EVENT      = 8,
    DATA_COMMANDER_SPRINGVALE_EVENT   = 9,
    DATA_LORD_GODFREY_EVENT           = 10,
};

enum Creaturesapothecary
{
    NPC_FRYE                          = 36272,
    NPC_HUMMEL                        = 36296,
    NPC_BAXTER                        = 36565,
    NPC_TORMENTED_OFFICER             = 50615,
    NPC_WAILING_GUARDSMAN             = 50613,
    NPC_BLOODTHIRSTY_GHOUL            = 50561,
    // Bosses
    BOSS_LORD_WALDEN                  = 46963,
    BOSS_BARON_ASHBURY                = 46962,
    BOSS_BARON_SILVERLAINE            = 3887,
    BOSS_LORD_GODFREY                 = 46964,
    BOSS_COMMANDER_SPRINGVALE         = 4278
};

enum Achievements
{
    ACHIEV_PARDON_DENIED              = 5503,
    ACHIEV_TO_THE_GROUND              = 5504,
    ACHIEV_BULLET_TIME                = 5505,
};

enum Data64
{
    DATA_DOOR,
    DATA_FRYE,
    DATA_HUMMEL,
    DATA_BAXTER,
    DATA_LORD_WALDEN,
    DATA_BARON_ASHBURY,
    DATA_BARON_SILVERLAINE,
    DATA_COMMANDER_SPRINGVALE,
    DATA_LORD_GODFREY,
};

#endif

