/*
* Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
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

#ifndef __TRINITY_ARCHAEOLOGY_MGR_H
#define __TRINITY_ARCHAEOLOGY_MGR_H

#include <map>
#include <string>
#include <vector>
#include <ace/Singleton.h>

#include "Common.h"
#include "DatabaseEnv.h"
#include "DBCEnums.h"
#include "DBCStores.h"
#include "WorldSession.h"
#include "SharedDefines.h"
#include "Language.h"
#include "DBCStructure.h"
#include "QueryResult.h"

const float  ARCHAEOLOGY_DIG_SITE_RADIUS     = 150.0f; // Digsite radius - distance check between finds.
const float  ARCHAEOLOGY_DIG_SITE_FAR_DIST   = 150.0f; // Far from find.
const float  ARCHAEOLOGY_DIG_SITE_MED_DIST   = 75.0f;  // Mid from find.
const float  ARCHAEOLOGY_DIG_SITE_CLOSE_DIST = 35.0f;  // Close to find.
const float  ARCHAEOLOGY_DIG_SITE_FIND_DIST  = 5.0f;   // Found it!

enum eArchaeology
{
    MAX_RESEARCH_SITES = 16,
    MAX_RESEARCH_POINTS = 3,
    MAX_RESEARCH_PROJECTS = 10,
    MAX_DIGS = 8,

    ARCHAEOLOGY_DIG_SITE_FAR_SURVEYBOT    = 206590,
    ARCHAEOLOGY_DIG_SITE_MEDIUM_SURVEYBOT = 206589,
    ARCHAEOLOGY_DIG_SITE_CLOSE_SURVEYBOT  = 204272,

    ARCHAEOLOGY_DIG_SITE_REWARD_AMMT_MIN  = 5, // Min fragments you can get.
    ARCHAEOLOGY_DIG_SITE_REWARD_AMMT_MAX  = 9  // Max fragments you can get.
};

enum eMapId
{
    MAP_EASTERN_KINGDOMS = 0,
    MAP_KALIMDOR         = 1,
    MAP_OUTLAND          = 530,
    MAP_NORTHREND        = 571,
    MAP_UNKNOWN          = -1
};

enum eGameObjectsEntries
{
    ARCHAEOLOGY_FIND_ORC       = 207187,
    ARCHAEOLOGY_FIND_DRAENEI   = 207188,
    ARCHAEOLOGY_FIND_TROLL     = 202655,
    ARCHAEOLOGY_FIND_NERUBIAN  = 203078,
    ARCHAEOLOGY_FIND_NIGHT_ELF = 203071,
    ARCHAEOLOGY_FIND_VRYKUL    = 207189,
    ARCHAEOLOGY_FIND_DWARF     = 204282,
    ARCHAEOLOGY_FIND_FOSSIL    = 206836,
    ARCHAEOLOGY_FIND_TOLVIR    = 207190
};

enum eKeyStoneEntries
{
    ARCHAEOLOGY_STONE_ORC       = 64392,
    ARCHAEOLOGY_STONE_DRAENEI   = 64394,
    ARCHAEOLOGY_STONE_TROLL     = 63128,
    ARCHAEOLOGY_STONE_NERUBIAN  = 64396,
    ARCHAEOLOGY_STONE_NIGHT_ELF = 63127,
    ARCHAEOLOGY_STONE_VRYKUL    = 64395,
    ARCHAEOLOGY_STONE_DWARF     = 52843,
    ARCHAEOLOGY_STONE_FOSSIL    = 0,
    ARCHAEOLOGY_STONE_TOLVIR    = 64397
};

enum eArchaeologyBranchId
{
    ARCHAEOLOGY_BRANCH_DWARF        = 1,
    ARCHAEOLOGY_BRANCH_DRAENEI      = 2,
    ARCHAEOLOGY_BRANCH_FOSSIL       = 3,
    ARCHAEOLOGY_BRANCH_NIGHT_ELF    = 4,
    ARCHAEOLOGY_BRANCH_NERUBIAN     = 5,
    ARCHAEOLOGY_BRANCH_ORC          = 6,
    ARCHAEOLOGY_BRANCH_TOLVIR       = 7,
    ARCHAEOLOGY_BRANCH_TROLL        = 8,
    ARCHAEOLOGY_BRANCH_VRYKUL       = 27,
    ARCHAEOLOGY_BRANCH_TEST         = 29
};

enum eArchaeologyBranchIndex
{
    ARCHAEOLOGY_INDEX_DWARF     = 0,
    ARCHAEOLOGY_INDEX_DRAENEI   = 1,
    ARCHAEOLOGY_INDEX_FOSSIL    = 2,
    ARCHAEOLOGY_INDEX_NIGHT_ELF = 3,
    ARCHAEOLOGY_INDEX_NERUBIAN  = 4,
    ARCHAEOLOGY_INDEX_ORC       = 5,
    ARCHAEOLOGY_INDEX_TOLVIR    = 6,
    ARCHAEOLOGY_INDEX_TROLL     = 7,
    ARCHAEOLOGY_INDEX_VRYKUL    = 8,
    ARCHAEOLOGY_INDEX_TEST      = 9
};

enum eUpdateAction
{
    UPDATE_GENERATE_NEW,
    UPDATE_EXCAVATION,
    UPDATE_LOADING,
    UPDATE_REMOVE
};

struct sWorldPositionTemplate
{
    uint16 entry;
    uint16 id;
    float position_X;
    float position_Y;
    uint16 count;

    void Clear();
    void CreateFromDB(Field* fields);
    void LoadFromDB(uint16 entry, uint16 pointId);
    sWorldPositionTemplate GetPositionTemplate(uint16 entry, uint16 id);
    std::vector<sWorldPositionTemplate> GetPositionTemplates(uint16 entry);
    float GetDistance2D(Player* player);
    float GetOrientation(Player* player);
};

struct sWorldDigsiteTemplate
{
    uint16 entry;
    uint16 level;
    uint16 mapId;
    uint16 areaId;
    uint16 branchId;

    void Clear();
    void CreateFromDB(Field* fields);
    void LoadFromDB(uint16 entry);
    sWorldDigsiteTemplate GetDigsiteTemplate(uint16 entry);
    std::vector<sWorldDigsiteTemplate> GetDigsiteTemplates(uint16 entry, uint16 mapId);
};

struct sCharacterDigsite
{
    uint16 slot;
    uint32 guid;
    uint16 entry;
    uint16 counter_digsite;
    uint32 time_digged;
    
    sWorldDigsiteTemplate digsite;
    sWorldPositionTemplate positions[3];
    bool isChanged;

    void CreateFromDB(Field* fields);
    void SaveToDB(uint32 guid, PreparedStatement* &stmt);
    void UpdateToDB(uint32 guid);
    void DeleteCharacterSlotFromDB(uint16 slot, uint32 guid, uint16 entry);
    void DeleteCharacterFromDB(uint32 guid);
    void Clear();
    std::vector<sCharacterDigsite*> GetDigSites(uint32 guid);
    uint16 GetBranchId(){ return digsite.branchId; }; 
    uint16 GetArchaeologyCurrency();
    uint16 GetArchaeologyKeyStone();
    uint32 GetArchaeologyLootGO();
    float GetDistance2D(Player* player, uint8 index);
    float GetOrientation(Player* player, uint8 index);
};

struct sCurrentProject
{
    uint16 branchId;
    uint16 projectId;
    
    uint32 spellId;
    uint16 reqFragments;
    uint16 currencyId;
    uint16 keyStoneId;
    uint16 complexity;

    void Clear();
    void CreateFromDB(Field* fields);
    void DeleteFromDB(uint32 guid);
    void SaveToDB(uint32 guid);
    void InsertDbcValues();
};

struct sCompletedProject
{
    uint16 projectId;
    uint32 counter_completed;
    uint32 timeFirst;
    uint32 timeLast;

    void CreateFromDB(Field* fields);
    void Clear();
    void SaveCompletedProjectToDB(uint32 guid);

};

class Player;
class GameObject;

class ArchaeologyMgr
{
public:
    explicit ArchaeologyMgr(Player* owner) : m_player(owner) { m_isDigsiteInitialized = false; m_isProjectsInitialized = false; }
    ~ArchaeologyMgr() { }

    // Internals.
    void Initialize();
    void RemovePlayerProfession();

    // digging
    void UpdateCharacterDigsite();
    void SaveDigsitesToDB();
    uint16 GetArchaeologyCurrency(uint8 branchId);
    uint16 GetArchaeologyKeyStone(uint8 branchId);
    uint32 OnSurveyBotActivated(sCharacterDigsite* &cd, uint16 &pos, float &dist, float &orientation);
    float GetOrientationWithDeviation(float dist, float orientation);

    // projects
    bool CompleteArtifact(uint32 spellId, ByteBuffer &data);
    void UpdateCurrentProjects();
    void SaveCurrentProjects();
    void InitCurrentProjects();
    void GenerateCurrentProject(uint32 branchId, bool force, uint32 excludeId);
    sCurrentProject FindCurrentProjects(uint32 spellId);
    sCompletedProject FindCompletedProjects(uint16 projectId);
    void EffectOnCreateItem(uint32 spellId, int32 &damage);

    // storage
    std::vector<sCompletedProject> completedProjects;
    sCurrentProject currentProjects[MAX_RESEARCH_PROJECTS];

private:
    // digging
    void LoadCharacterDigsite();
    void LoadProjects();
    void SaveCharacterDigsite();
    void FillRandomArtifactPos(std::vector<sWorldPositionTemplate> posList, sCharacterDigsite* &digsite);
    void UpdatePlayerFieldsResearchSite();
    void UpdatePlayerFieldsResearchSite(uint16 slot);
    bool FindNearestDigsite(sCharacterDigsite* &digsite, uint16 &pos, float &distance2D, float &orientation);
    bool IsAllowedDigsite(sWorldDigsiteTemplate digsite);
    int16 GetMap(uint8 id);
    int16 GetBranchIndex(uint8 branchId);
    uint16 GetBranchId(uint8 index);
    uint16 GetMaxDigsite();
    uint16 GetArchaeologyMap(uint16 slot);
    uint32 GetArchaeologyLootGO(uint8 branchId);
    sCharacterDigsite* CreateNewRandomDigsite(uint16 slot);
    std::vector<sWorldDigsiteTemplate> GetListOfAllowedNotUsedDigsiteTemplates(uint16 slot);
    std::vector<sWorldPositionTemplate> GetListOfDigsitePositions(uint16 entry);

    // current projects
    void LoadCurrentProjects();

    // completed projects
    void LoadCompletedProjects();
    void UpdatePlayerFieldsResearching();
    void UpdatePlayerFieldsResearching(uint16 slot);
    std::vector<uint32> GetResearchProjectList(uint16 branchId, uint16 excludeSpellId);

    // variable and storage
    sCharacterDigsite m_characterDigsite[MAX_RESEARCH_SITES];
    bool m_isDigsiteInitialized;
    bool m_isDigsiteChanged;
    bool m_isProjectsInitialized;
    bool m_isProjectChanged;
    Player* m_player;

};

#endif