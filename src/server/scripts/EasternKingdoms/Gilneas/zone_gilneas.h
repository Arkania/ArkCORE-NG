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

enum CreatureIds
{
    NPC_PANICKED_CITIZEN                              = 34851,
    NPC_PANICKED_CITIZEN_GATE                         = 44086,
    NPC_PRINCE_LIAM_GREYMANE                          = 34913,
    NPC_GILNEAS_CITY_GUARD                            = 34916,
    NPC_RAMPAGING_WORGEN_1                            = 34884,
    NPC_RAMPAGING_WORGEN_2                            = 35660,
    NPC_BLOODFANG_WORGEN                              = 35118,
    NPC_SERGEANT_CLEESE                               = 35839,
	NPC_BLOODFANG_RIPPER_P4                           = 35505, // General AI spawns
	NPC_JOSIAH_AVERY_P4                               = 35370, // NPC for worgen bite
	NPC_LORNA_CROWLEY_P4                              = 35378, // Quest - From the Shadows
    NPC_MYRIAM_SPELLWALKER                            = 35872,
    NPC_GILNEAN_ROYAL_GUARD                           = 35232,
    NPC_FRIGHTENED_CITIZEN_1                          = 34981,
    NPC_FRIGHTENED_CITIZEN_2                          = 35836,
    NPC_DARIUS_CROWLEY                                = 35230,
    NPC_NORTHGATE_REBEL_1                             = 36057,
    NPC_NORTHGATE_REBEL_2                             = 41015,
    NPC_BLOODFANG_STALKER_C1                          = 35229,
    NPC_BLOODFANG_STALKER_C2                          = 51277,
    NPC_BLOODFANG_STALKER_CREDIT                      = 35582,
    NPC_CROWLEY_HORSE                                 = 35231,
    NPC_NORTHGATE_REBEL                               = 41015,
    NPC_FRENZIED_STALKER                              = 35627,
    NPC_PRINCE_LIAM_GREYMANE_BATTLE                   = 38218,
    NPC_TOBIAS_MISTMANTLE                             = 38507,
    NPC_LORD_DARIUS_CROWLEY_C1                        = 35077, // Quest - By the skin of his teeth start/stop	
    NPC_WORGEN_ALPHA_C1                               = 35170, // Quest - By the skin of his teeth spawns
    NPC_WORGEN_ALPHA_C2                               = 35167, // Quest - By the skin of his teeth spawns
    NPC_WORGEN_RUNT_C1                                = 35188, // Quest - By the skin of his teeth spawns
    NPC_WORGEN_RUNT_C2                                = 35456, // Quest - By the skin of his teeth spawns
	NPC_COMMANDEERED_CANNON                           = 35914,
	NPC_KRENNAN_ARANAS_TREE                           = 35753,
	NPC_GREYMANE_HORSE_P4                             = 35905
};

enum QuestIds
{
    QUEST_LOCKDOWN                                     = 14078,
    QUEST_EVAC_MERC_SQUA                               = 14098,
	QUEST_THE_REBEL_LORDS_ARSENAL                      = 14159,
	QUEST_FROM_THE_SHADOWS                             = 14204,
    QUEST_SAVE_KRENNAN_ARANAS                          = 14293,
    QUEST_SACRIFICES                                   = 14212,
    QUEST_THE_BATTLE_FOR_GILNEAS_CITY                  = 24904,
	QUEST_ROYAL_ORDERS                                 = 14099,
    QUEST_14348_KILL_CREDIT                            = 36233,
    QUEST_YOU_CANT_TAKE_EM_ALONE                       = 14348
};

enum SpellIds
{
    SPELL_ENRAGE                                       = 8599,
    SPELL_PHASE_QUEST_ZONE_SPECIFIC_01                 = 59073,
	SPELL_SUMMON_JOSIAH_AVERY                          = 67350,
	SPELL_SUMMON_GILNEAN_MASTIFF                       = 67807,
	SPELL_ATTACK_LURKER                                = 67805,
	SPELL_SHADOWSTALKER_STEALTH                        = 5916,
	SPELL_GET_SHOT                                     = 67349,
	SPELL_SHOOT                                        = 6660,
	SPELL_PHASE_4                                      = 59074,
    SPELL_FROSTBOLT_VISUAL_ONLY                        = 74277,
    SPELL_SUMMON_CROWLEY                               = 67004,
    SPELL_RIDE_HORSE                                   = 43671,
    SPELL_THROW_TORCH                                  = 67063,
    SPELL_FADE_BACK                                    = 94053,
    SPELL_DEMORALIZING_SHOUT                           = 61044,
    SPELL_BY_THE_SKIN                                  = 66914,				
    SPELL_LEFT_HOOK                                    = 67825,
    SPELL_SNAP_KICK                                    = 67827,
	SPELL_GILNEAS_CANNON_CAMERA                        = 93555,
	SPELL_CANNON_FIRE                                  = 68235,
    SPELL_WORGEN_BITE                                  = 72870,
    SPELL_INFECTED_BITE                                = 72872,
    SPELL_GENERIC_QUEST_INVISIBILITY_DERECTION_1       = 49416,
    SPELL_BARREL_KEG                                   = 69094	
};

enum NpcTextIds
{
    SAY_PRINCE_LIAM_GREYMANE_1                        = 0,
    SAY_PRINCE_LIAM_GREYMANE_2                        = 1,
    SAY_PRINCE_LIAM_GREYMANE_3                        = 2,
    SAY_PRINCE_LIAM_GREYMANE_4                        = 0,
    SAY_PRINCE_LIAM_GREYMANE_5                        = 1,
    SAY_PRINCE_LIAM_GREYMANE_6                        = 2,
    SAY_PRINCE_LIAM_GREYMANE_7                        = 3,
	YELL_PRINCE_LIAM_GREYMANE						  = 1,
	DELAY_SAY_PRINCE_LIAM_GREYMANE                    = 2000,
	DELAY_YELL_PRINCE_LIAM_GREYMANE					  = 2000,

    SAY_PANICKED_CITIZEN_1                             = -1638016,
    SAY_PANICKED_CITIZEN_2                             = -1638017,
    SAY_PANICKED_CITIZEN_3                             = -1638018,
    SAY_PANICKED_CITIZEN_4                             = -1638019,

    SAY_GILNEAS_CITY_GUARD_GATE_1                      = -1638022,
    SAY_GILNEAS_CITY_GUARD_GATE_2                      = -1638023,
    SAY_GILNEAS_CITY_GUARD_GATE_3                      = -1638024,
	
	SAY_JOSIAH_AVERY_1                                = 0,
	SAY_JOSIAH_AVERY_2                                = 1,
	SAY_JOSIAH_AVERY_3                                = 2,
	SAY_JOSIAH_AVERY_4                                = 3,
	SAY_JOSIAH_AVERY_5                                = 4,
	DELAY_SAY_JOSIAH_AVERY                            = 20000,
	
    SAY_JOSAIH_AVERY_TRIGGER                          = 1,
	
	SAY_LORNA_CROWLEY_P4                              = 0,
	
	SAY_KING_GENN_GREYMANE                            = 0,
	
	SAY_LORD_GODFREY_P4                               = 0,

    SAY_CITIZEN_1                                      = -1638003,
    SAY_CITIZEN_2                                      = -1638004,
    SAY_CITIZEN_3                                      = -1638005,
    SAY_CITIZEN_4                                      = -1638006,
    SAY_CITIZEN_5                                      = -1638007,
    SAY_CITIZEN_6                                      = -1638008,
    SAY_CITIZEN_7                                      = -1638009,
    SAY_CITIZEN_8                                      = -1638010,
    SAY_CITIZEN_1b                                     = -1638011,
    SAY_CITIZEN_2b                                     = -1638012,
    SAY_CITIZEN_3b                                     = -1638013,
    SAY_CITIZEN_4b                                     = -1638014,
    SAY_CITIZEN_5b                                     = -1638015,

    YELL_KRENNAN_C1                                    = 0,
    SAY_KRENNAN_C2                                     = 1,
    SAY_GREYMANE_HORSE                                 = 0,
    SAY_CROWLEY_HORSE_1                                = 0,
    SAY_CROWLEY_HORSE_2                                = 1,
	SAY_NPC_KRENNAN_ARANAS_TREE                        = 0
};

enum SoundIds
{
    SOUND_SWORD_FLESH                                 = 143,
    SOUND_SWORD_PLATE                                 = 147,
    SOUND_WORGEN_ATTACK                               = 558,
    DELAY_SOUND                                       = 500,
    DELAY_ANIMATE                                     = 2000,
};

enum eAction
{
    ACTION_START_EVENT,
    ACTION_END_EVENT
};

enum eData
{
    DATA_GROUP,
    GROUP_1,
    GROUP_2,
};

Position const FrightenedWay[2] =
{
    {-1404.01f, 1444.38f, 35.55f, 0.0f},
    {-1403.31f, 1375.35f, 35.55f, 0.0f}
};

Position const JumpW1[3] =
{
    { -1643.91f, 1482.96f, 63.22f, 3.95f },
    { -1638.83f, 1478.07f, 65.36f, 3.84f },
    { -1631.49f, 1475.02f, 65.64f, 3.84f }
};

Position const LandingW1[3] =
{
    { -1677.39f, 1455.52f, 52.29f, 4.06f },
    { -1671.89f, 1449.27f, 52.29f, 3.84f },
    { -1664.82f, 1443.62f, 52.29f, 3.84f }
};

Position const LandingW2[4] =
{
    { -1704.93f, 1469.07f, 52.29f, 5.34f },
    { -1698.90f, 1472.92f, 52.29f, 5.41f },
    { -1703.37f, 1470.66f, 52.29f, 5.49f },
    { -1700.37f, 1473.32f, 52.29f, 5.41f }
};

#define DELAY_EMOTE_PANICKED_CITIZEN                  urand(5000, 15000)
#define DELAY_SAY_PANICKED_CITIZEN                    urand(30000, 120000)
#define DELAY_SAY_GILNEAS_CITY_GUARD_GATE             urand(30000, 120000)
#define PATHS_COUNT_PANICKED_CITIZEN                  8
#define CD_ENRAGE                                     30000
#define SUMMON1_TTL                                   300000
#define PATHS_COUNT                                   2
#define DOOR_TIMER                                    30*IN_MILLISECONDS
#define KRENNAN_END_X                                 -1772.4172f
#define KRENNAN_END_Y                                 1430.6125f
#define KRENNAN_END_Z                                 19.79f
#define KRENNAN_END_O                                 2.79f
#define CROWLEY_SPEED                                 1.85f
#define MAP_GILNEAS                                   654
#define AI_MIN_HP                                     85
#define Event_Time                                    118500
#define WORGEN_EVENT_SPAWNTIME                        20000 // Default Despawn Timer
#define NW_ROOF_SPAWN_LOC_1                           -1618.86f, 1505.68f, 70.24f, 3.91f
#define NW_ROOF_SPAWN_LOC_2                           -1611.40f, 1498.49f, 69.82f, 3.79f
#define SW_ROOF_SPAWN_LOC_1                           -1732.81f, 1526.34f, 55.39f, 0.01f
#define SW_ROOF_SPAWN_LOC_2                           -1737.49f, 1526.11f, 55.51f, 0.01f
#define N_ROOF_SPAWN_LOC                              -1562.59f, 1409.35f, 71.66f, 3.16f
#define PLATFORM_Z                                    52.29f

#endif

