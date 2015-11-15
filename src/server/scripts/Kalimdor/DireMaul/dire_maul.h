/**
 * ScriptDev3 is an extension for mangos providing enhanced features for
 * area triggers, creatures, game objects, instances, items, and spells beyond
 * the default database scripting in mangos.
 *
 * Copyright (C) 2006-2013  ScriptDev2 <http://www.scriptdev2.com/>
 * Copyright (C) 2014-2015  MaNGOS  <https://getmangos.eu>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * World of Warcraft, and all World of Warcraft or Warcraft art, images,
 * and lore are copyrighted by Blizzard Entertainment, Inc.
 */

#ifndef DEF_DM_H
#define DEF_DM_H

#define DMScriptName "instance_dire_maul"

enum eEncounters
{
    ENC_HYDROSPAWN, // warpwood quarter
    ENC_LETHTENDRIS,
    ENC_ZEVRIM_THORNHOOF,
    ENC_ALZZIN_THE_WILDAHAPER,

    ENC_TENDRIS_WARPWOOD, // capital gardens
    ENC_ILLYANNA_RAVENOAK,
    ENC_MAGISTER_KALENDRIS,
    ENC_IMMOLTHAR,
    ENC_PRINCE_TORTHELDRIN,

    ENC_GUARD_MOLDAR, // Gordok commons
    ENC_STOMPER_KREEG,
    ENC_GUARD_FENGUS,
    ENC_GUARD_SLIPKIK,
    ENC_CAPTAIN_KROMCRUSH,
    ENC_CHORUSH_THE_OBSERVER,
    ENC_KING_GORDOK,
    MAX_ENC_ENCOUNTER
};

enum eExtraEncounters
{
    EXTRA_OLD_IRONBARK = MAX_ENC_ENCOUNTER,
    EXTRA_IRONBARK_THE_REDEEMED,
    EXTRA_CONSERVATORY_DOOR,

    MAX_EXTRA_ENCOUNTER
};

enum eDataTypes
{
    DATA_PUSILLIN,
    DATA_HYDROSPAWN,
    DATA_LETHTENDRIS,
    DATA_PIMGIP,
    DATA_ZEVRIM_THORNHOOF,
    DATA_ALZZIN_THE_WILDAHAPER,
    DATA_ISALIEN,
    DATA_EMPYREAN,
    DATA_OLD_IRONBARK,
    DATA_IRONBARK_THE_REDEEMED,

    DATA_TENDRIS_WARPWOOD,
    DATA_ILLYANNA_RAVENOAK,
    DATA_FERRA,
    DATA_TSUZEE,
    DATA_MAGISTER_KALENDRIS,
    DATA_REVANCHION,
    DATA_IMMOLTHAR,
    DATA_LORD_HELNURATH,
    DATA_PRINCE_TORTHELDRIN,

    DATA_GUARD_MOLDAR,
    DATA_STOMPER_KREEG,
    DATA_GUARD_FENGUS,
    DATA_GUARD_SLIPKIK,
    DATA_CAPTAIN_KROMCRUSH,
    DATA_CHORUSH_THE_OBSERVER,
    DATA_KING_GORDOK,

    DATA_CONSERVATORY_DOOR,

    MAX_DATA_ENCOUNTER
};

enum eBoss
{
    BOSS_ALZZIN_THE_WILDAHAPER = 11492,
    BOSS_CAPTAIN_KROMCRUSH = 14325,
    BOSS_CHORUSH_THE_OBSERVER = 14324,
    BOSS_GUARD_FENGUS = 14321,
    BOSS_GUARD_MOLDAR = 14326,
    BOSS_GUARD_SLIPKIK = 14323,
    BOSS_HYDROSPAWN = 13280,
    BOSS_ILLYANNA_RAVENOAK = 11488,
    BOSS_IMMOLTHAR = 11496,
    BOSS_KING_GORDOK = 11501,
    BOSS_LETHTENDRIS = 14327,
    BOSS_MAGISTER_KALENDRIS = 11487,
    BOSS_PRINCE_TORTHELDRIN = 11486,
    BOSS_STOMPER_KREEG = 14322,
    BOSS_TENDRIS_WARPWOOD = 11489,
    BOSS_ZEVRIM_THORNHOOF = 11490,
};

enum eGameObject
{
    GO_CONSERVATORY_DOOR = 176907,

    GO_CRUMBLE_WALL = 177220,
    GO_CORRUPT_VINE = 179502,
    GO_FELVINE_SHARD = 179559,
    GO_PRINCES_CHEST = 179545,
    GO_PRINCES_CHEST_AURA = 179563,
    GO_CRYSTAL_GENERATOR_1 = 177259,
    GO_CRYSTAL_GENERATOR_2 = 177257,
    GO_CRYSTAL_GENERATOR_3 = 177258,
    GO_CRYSTAL_GENERATOR_4 = 179504,
    GO_CRYSTAL_GENERATOR_5 = 179505,
    GO_FORCEFIELD = 179503,
    GO_WARPWOOD_DOOR = 177221,
    GO_WEST_LIBRARY_DOOR = 179550,
    GO_KNOTS_CACHE = 179501,
    GO_KNOTS_BALL_AND_CHAIN = 179511,
    GO_GORDOK_TRIBUTE = 179564,
    GO_NORTH_LIBRARY_DOOR = 179549,
};

enum eNpc
{
    NPC_PUSILLIN = 14354,
    NPC_PIMGIP = 14349,
    NPC_OLD_IRONBARK = 11491,
    NPC_IRONBARK_THE_REDEEMED = 14241,
    NPC_ISALIEN = 16097,
    NPC_EMPYREAN = 16098,
    NPC_FERRA = 14308,
    NPC_TSUZEE = 11467,
    NPC_REVANCHION = 14690,
    NPC_LORD_HELNURATH = 14506,

    NPC_ARCANE_ABERRATION = 11480,
    NPC_MANA_REMNANT = 11483,
    NPC_HIGHBORNE_SUMMONER = 11466,
    NPC_CHORUSH = 14324,
    NPC_MIZZLE_THE_CRAFTY = 14353,
};

enum eSpells
{
    SPELL_KING_OF_GORDOK = 22799,
};

enum eMisc
{
    FACTION_HOSTILE = 14,
};

enum eDoorState
{
    OpenState = 1,
    CloseState = 2,
};

template<class AI>
CreatureAI* GetDireMaulAI(Creature* creature)
{
    if (InstanceMap* instance = creature->GetMap()->ToInstanceMap())
        if (instance->GetInstanceScript())
            if (instance->GetScriptId() == sObjectMgr->GetScriptId(DMScriptName))
                return new AI(creature);

    return NULL;
}


template<class AI, class T>
AI* GetDireMaulAI(T* obj)
{
    return GetInstanceAI<AI, T>(obj, DMScriptName);
}

#endif

