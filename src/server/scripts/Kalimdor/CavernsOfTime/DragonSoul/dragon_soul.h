#ifndef DRAGON_SOUL_H_
#define DRAGON_SOUL_H_

#include "SpellScript.h"
#include "Map.h"
#include "Creature.h"

#define DSScriptName "instance_dragon_soul"

enum Bosses
{
    BOSS_MORCHOK            = 0,
    BOSS_WARLORD            = 1,
    BOSS_UNSLEEPING         = 2,
    BOSS_HAGARA             = 3,
    BOSS_ULTRAXION          = 4,
    BOSS_WARMASTER          = 5,
    BOSS_DEATHWING          = 6,
    DATA_PORTALS_ON_OFF     = 7,
    DATA_WAVE               = 8,
    DATA_TRALL_VS_ULTRAXION = 9,

    MAX_ENCOUNTER           = 10,
};

enum Data
{
    DATA_DAMAGE_DEATHWING,
    DATA_ATTACK_DEATHWING,
};

enum GameObject_
{
	GO_ULTRAXION_LOOT_10N = 210160,
	GO_ULTRAXION_LOOT_25N = 210161,
	GO_ULTRAXION_LOOT_10H = 210162,
	GO_ULTRAXION_LOOT_25H = 210163,
	GO_DEATHWING_LOOT_10N = 209894,
	GO_DEATHWING_LOOT_25N = 209895,
	GO_DEATHWING_LOOT_10H = 209896,
	GO_DEATHWING_LOOT_25H = 209897,
};

enum Spell_aspect
{
    LAST_DEFENDER_OF_AZEROTH = 106080,
    TIMELOOP                 = 105984,
    SOURCE_OF_MAGIC          = 105903,
    ESSENCE_OF_DREAMS        = 105900,
    GIFT_OF_LIFE             = 105896,
};

enum Creatures
{
    NPC_MORCHOK      = 55265,
    NPC_WARLORD      = 55308,
    NPC_UNSLEEPING   = 55312,
    NPC_HAGARA       = 55689,
    NPC_ULTRAXION    = 55294,
    NPC_WARMASTER    = 56427,
    NPC_DEATHWING_1  = 56173,
    NPC_DEATHWING_2  = 0,

    NPC_MAELSTROM_ALEXSTRASZA = 56099,
    NPC_MAELSTROM_TRALL       = 56103,
    NPC_MAELSTROM_KALECGOS    = 56101,
    NPC_MAELSTROM_YSERA       = 56100,
    NPC_MAELSTROM_NOZDORMY    = 56102,

    NPC_ARM_TENTACLE_1     = 56167,
    NPC_ARM_TENTACLE_2     = 56846,
    NPC_WING_TENTACLE_1    = 56168,
    NPC_WING_TENTACLE_2    = 57972,
    NPC_MYTATED_CORRUPTION = 56471,

    NPC_EIENDORMI          = 57288,


    NPC_FORZEN_BINDIG_CRYSTAL     = 56136,
    NPC_CRYSTAL_CONDUCTOR         = 56165,
    NPC_BOUND_LIGHTNING_ELEMENTAL = 56700,
    NPC_ICE_WAVE                  = 56104,
    NPC_ICICLE                    = 48916,
    NPC_TWILIGHT_ELITE_SLAYER     = 56848,
    NPC_TWILIGHT_ELITE_DREADBLADE = 56854,

    NPC_TRALL_VS_ULTRAXION = 56667,
    NPC_ALEXSTRASZA        = 56630,
    NPC_YSERA              = 56665,
    NPC_NOZDORMU           = 56666,
    NPC_ASPECT_OF_MAGIC    = 56664,

    NPC_TRAVEL_TO_THE_DECK_OF_THE_SKYFIRE = 57378,
    NPC_TRAVEL_TO_THE_MAELSTROM           = 57443,
    NPC_PORTAL                            = 57328,

    NPC_CORRUPTION_PARASITE = 57479,
    NPC_CONGEALING_BLOOD    = 57798,
    NPC_ELEMENTIUM_FRAGMENT = 56724,
    NPC_ELEMENTIUM_TERROR   = 56710,
};

template<class AI>
CreatureAI* GetDragonSoulAI(Creature* creature)
{
    if (InstanceMap* instance = creature->GetMap()->ToInstanceMap())
        if (instance->GetInstanceScript())
            if (instance->GetScriptId() == sObjectMgr->GetScriptId(DSScriptName))
                return new AI(creature);

    return NULL;
}

#endif // DRAGON_SOUL_H_