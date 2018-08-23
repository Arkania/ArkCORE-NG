
#ifndef DEF_THRONE_OF_THE_FOUR_WINDS_H
#define DEF_THRONE_OF_THE_FOUR_WINDS_H

enum Data
{
    DATA_CONCLAVE_OF_WIND_EVENT,
    DATA_ALAKIR_EVENT,

    MAX_BOSSES,

    DATA_GATHERING_STRENGTH,
    DATA_WEATHER_EVENT,
    DATA_ALAKIR_FLIGHT_PHASE,
};

enum Data64
{
    DATA_ANSHAL,
    DATA_NEZIR,
    DATA_ROHASH,
    DATA_ALAKIR,
};

enum CreatureIds
{
    BOSS_ANSHAL                       = 45870,
    BOSS_NEZIR                        = 45871,
    BOSS_ROHASH                       = 45872,
    BOSS_ALAKIR                       = 46753,

    // Conclave of Wind
    NPC_SOOTHING_BREEZE               = 46246,
    NPC_RAVENOUS_CREEPER              = 45812,
    NPC_RAVENOUS_CREEPER_TRIGGER      = 45813,
    NPC_ICE_PATCH                     = 46186,
    NPC_TORNADO                       = 46207,

    // Al'akir
    NPC_SLIPSTREAM_ALAKIR             = 47066,
    NPC_SQUILL_LINE_1                 = 48852,
    NPC_SQUILL_LINE_2                 = 47034,
    NPC_SQUILL_1                      = 48855,
    NPC_SQUILL_2                      = 48854,
    NPC_ICE_STORM_RAIN                = 46734,
    NPC_LIGHTNING_STRIKE_TRIGGER      = 48977,
    NPC_STORMLING                     = 47175,
    NPC_STORMLING_PRE_EFFECT          = 47177,
    NPC_LIGHTNING_CLOUD_TRIGGER       = 48190,
    NPC_LIGHTNING_CLOUD_TRIGGER_EXTRA = 48196,
    NPC_LIGHTNING_CLOUD_TRIGGER2      = 51597,
    NPC_RELENTLESS_STORM              = 47807,
    NPC_RELENTLESS_STORM_VEHICLE      = 47806,
    NPC_ICE_STORM_ROTATE_TRIGGER      = 46766,
    NPC_WIND_BURST_TRIGGER            = 8777000,
    NPC_WIND_BURST_INSTANT_TRIGGER    = 8885800,

    NPC_WORLD_TRIGGER                 = 36171,
    NPC_HURRICANE                     = 46419,
    NPC_GENERAL_PURPOSE_BUNNY_JMF     = 45979,
};

enum GobjectIds
{
    GO_SKYWALL_RAID                   = 207737,
    GO_SKYWALL_WIND                   = 223271,
    GO_HEART_OF_WIND_10               = 207891,
    GO_HEART_OF_WIND_25               = 207892,
};

enum Platforms
{
    GO_NAZIR_PLATFORM                 = 206700,
    GO_ANSHAL_PLATFORM                = 206699,
    GO_ROHASH_PLATFORM                = 206701,
};

enum InstanceSpells
{
    SPELL_PRE_COMBAT_EFFECT_ANSHAL      = 85537,
    SPELL_PRE_COMBAT_EFFECT_NEZIR       = 85532,
    SPELL_PRE_COMBAT_EFFECT_ROHASH      = 85538,
    SPELL_EYE_OF_THE_STORM              = 89107,
    SPELL_SLIPSTREAM_BUFF               = 87740,
    SPELL_RELENTLESS_STORM_VISUAL       = 89428,
    SPELL_STAY_CHILL_ACHIEVEMENT_CREDIT = 94119,
    SPELL_WIND_CHILL_10                 = 84645,
    SPELL_WIND_CHILL_25                 = 93123,
    SPELL_WIND_CHILL_10H                = 93124,
    SPELL_WIND_CHILL_25H                = 93125,
    SPELL_SLIPSTREAM_PLAYER_VISUAL      = 85063,
};

enum InstanceDataMisc
{
    DATA_START_HELP_PLAYER,
};

#endif
