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
	SPELL_PHASE_QUEST_2                                = 59073,
	SPELL_SUMMON_JOSIAH_AVERY                          = 67350,
	SPELL_SUMMON_GILNEAN_MASTIFF                       = 67807,
	SPELL_ATTACK_LURKER                                = 67805,
	SPELL_SHADOWSTALKER_STEALTH                        = 5916,
	SPELL_GET_SHOT                                     = 67349,
	SPELL_SHOOT                                        = 6660,
	SPELL_PHASE_2                                      = 59073,
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
    SPELL_PHASING_AURA                                 = 59073,
	SPELL_GILNEAS_CANNON_CAMERA                        = 93555,
	SPELL_CANNON_FIRE                                  = 68235,
    SPELL_WORGEN_BITE                                  = 72870,
    SPELL_INFECTED_BITE                                = 72872,
    SPELL_QUEST_DETECTION                              = 49416,
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

struct Waypoint
{
    float X, Y, Z;
};

Waypoint NW_WAYPOINT_LOC1[2]=
{
    { -1630.62f, 1480.55f, 70.40f }, // Worgen Runt 1 top edge of Roof Waypoint
    { -1636.01f, 1475.81f, 64.51f }  // Worgen Runt 1 Edge of Roof Waypoint
};

Waypoint NW_WAYPOINT_LOC2[2]=
{
    { -1637.26f, 1488.86f, 69.95f }, // Worgen Runt 1 top edge of Roof Waypoint
    { -1642.45f, 1482.23f, 64.30f }  // Worgen Runt 1 Edge of Roof Waypoint
};

Waypoint SW_WAYPOINT_LOC1[2]=
{
    { -1718.31f, 1526.62f, 55.91f }, // Worgen Runt 2 Corner where we turn
    { -1717.86f, 1490.77f, 56.61f }  // Worgen Runt 2 Edge of Roof Waypoint
};

Waypoint SW_WAYPOINT_LOC2[2]=
{
    { -1718.31f, 1526.62f, 55.91f }, // Worgen Alpha 1 Corner where we turn
    { -1717.86f, 1487.00f, 57.07f }  // Worgen Alpha 1 Edge of Roof Waypoint
};

Waypoint N_WAYPOINT_LOC[1]=
{
    { -1593.38f, 1408.02f, 72.64f } // Worgen Runt 2 Edge of Roof Waypoint
};

/* QUEST - 14154 - By The Skin of His Teeth */
static const Position spawnPos[3][3] =
{
    {
        { -1718.195f, 1526.525879f, 55.918981f, 4.698965f }, // Spawn Left
        { -1718.152f, 1486.315918f, 57.232832f, 5.437238f }, // MoveTo Left
        { -1699.458f, 1468.477783f, 52.297140f, 5.523634f } // JumpTo Left
    },
    {
        { -1625.497f, 1492.348755f, 73.716627f, 4.070646f }, // Spawn Mid
        { -1632.688f, 1485.533447f, 74.958799f, 3.874443f }, // MoveTo Mid
        { -1676.319f, 1445.140747f, 52.297140f, 0.748411f } // JumpTo Mid - CENTER
    },
    {
        { -1562.104f, 1409.827148f, 71.676458f, 3.218636f }, // Spawn Right
        { -1594.044f, 1408.207397f, 72.850088f, 3.120459f }, // MoveTo Right
        { -1655.406f, 1425.001953f, 52.297109f, 2.291864f } //JumpTo Right
    }
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

