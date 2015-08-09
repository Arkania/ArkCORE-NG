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

#ifndef FIRELANDS_H_
#define FIRELANDS_H_

#include "Map.h"
#include "CreatureAI.h"

#define FirelandsScriptName "instance_firelands"

enum CreatureIds
{
    //bosses
    NPC_BETHTILAC = 52498,
    NPC_RHYOLITH = 52558,
    NPC_ALYSRAZOR = 52530,
    NPC_SHANNOX = 53691,
    NPC_BALOROC = 53494,
    NPC_MAJORDOMUS = 52571,
    NPC_RAGNAROS_CATA = 52409,

    //other npc's

    // Shannox
    NPC_RIPLIMB = 53694, // Shannox Dogs
    NPC_RAGEFACE = 53695,
    NPC_SHANNOX_SPEAR = 53752, // Shannox Spear
    NPC_FAKE_SHANNOX_SPEAR = 53910, 
    NPC_CRYSTAL_TRAP = 53713,
    NPC_IMMOLATION_TRAP = 53724,
    NPC_CRYSTAL_PRISON = 53819,

    // Bethilac
    NPC_CINDERWEB_SPINNER = 53642,
    NPC_CINDERWEB_DRONE = 53635,
    NPC_CINDERWEB_SPIDERLING = 53631,
    NPC_ENGORGED_BROODLING = 53745,
    NPC_SPIDERWEB_FILAMENT = 53082, // This is the Elevator
    NPC_WEB_RIP = 53450,
    NPC_LIFT_CONTROLLER = 52528,

    // Rhyolith
    NPC_LEFT_LEG = 52577,
    NPC_RIGHT_LEG = 53087,
    NPC_RHYOLITH_VOLCANO = 52582,
    NPC_RHYOLITH_CRATER = 52866,
    NPC_LIQUID_OBSIDIAN = 52619,
    NPC_FRAGMENT_OF_RHYOLITH = 52620,
    NPC_SPARK_OF_RHYOLITH = 53211,

    //Ragnaros
    NPC_SULFURAS_SMASH = 53268,
    NPC_MAGMA_TRAP = 53086,
    NPC_SPLITTING_BLOW = 53393,
    NPC_ENGULFING_FLAMES = 53485,
    NPC_MOLTEN_SEED = 53186,
    NPC_LAVA_WAVE = 53363,
    NPC_LAVA_SCION = 53231,
    NPC_SON_OF_FLAME = 53140,
    NPC_LIVING_METEOR = 53500,
    NPC_MOLTEN_ELEMENTAL = 53189,
    NPC_SULFURAS = 53420,
    NPC_ENTRAPPING_ROOTS = 54074,
    NPC_DREADFLAME = 54127,
    NPC_CLOUDBURST = 54147,
    NPC_DREADFLAME_SPAWN = 54203,
    NPC_BREATH_OF_FROST = 53953,
    NPC_HAMUUL = 54109,
    NPC_MALFURION = 54110,
    NPC_CENARIUS = 53872,
    NPC_HEART_OF_RAGNAROS = 54293,
};

enum GameObjectIds
{
    GOB_DOOR_BETHILAC = 208877,
    GOB_DOOR_BALOROC  = 209066,
    GOB_VOLCANO_ALYS  = 209253, // destructable
    GOB_WALL_SULFURON = 208873,
    GOB_DOOR_RAGNAROS = 209073,
    GOB_PLATFORM_RAGN = 208835, // destructable - heroic.
};

enum Data
{
    // Encounter States
    DATA_BALOROC_EVENT,
    DATA_SHANNOX_EVENT,
    DATA_ALYSRAZAR_EVENT,
    DATA_BETHTILAC_EVENT,
    DATA_LORD_RHYOLITH_EVENT,
    DATA_MAJORDOMUS_EVENT,
    DATA_RAGNAROS_EVENT,
};
enum Data64
{
    // Encounter States
    DATA_BALOROC,
    DATA_SHANNOX,
    DATA_ALYSRAZAR,
    DATA_BETHTILAC,
    DATA_LORD_RHYOLITH,
    DATA_MAJORDOMUS,
    DATA_RAGNAROS,

    DATA_RIPLIMB,
    DATA_RAGEFACE,
    DATA_SHANNOX_SPEAR,

    DATA_BETHTILAC_DOOR,
    DATA_BALOROC_DOOR,
    DATA_ALYSRAZOR_VOLCANO,
    DATA_SULFURON_DOOR,
    DATA_RAGNAROS_PLATFORM
};

enum MovePoints
{
    POINT_RAGNAROS_DOWN, //end of each phase
    POINT_RAGNAROS_UP, //start of each next phase
    POINT_RAGNAROS_STANDUP, //only on heroic mode
    POINT_SULFURAS_SMASH //target for smashes
};

enum SharedActions
{
    ACTION_RAGNAROS_DOWN, //end of each phase
    ACTION_RAGNAROS_UP, //start of each next phase
    ACTION_RAGNAROS_STANDUP, //only on heroic mode
    ACTION_SULFURAS_SMASH, //target for smashes
};

enum PathIDs
{
    PATH_SHANNOX = 154280940,
};

enum DataVar
{
    DATA_PHASE,
};

class DelayedAttackStartEvent : public BasicEvent
{
    public:
        DelayedAttackStartEvent(Creature* owner) : _owner(owner) { }

        bool Execute(uint64 /*e_time*/, uint32 /*p_time*/)
        {
            _owner->AI()->DoZoneInCombat(_owner, 200.0f);
            return true;
        }

    private:
        Creature* _owner;
};

template<class AI>
CreatureAI* GetFirelandsAI(Creature* creature)
{
    if (InstanceMap* instance = creature->GetMap()->ToInstanceMap())
        if (instance->GetInstanceScript())
            if (instance->GetScriptId() == sObjectMgr->GetScriptId(FirelandsScriptName))
                return new AI(creature);
    return NULL;
}

#endif // FIRELANDS_H_
