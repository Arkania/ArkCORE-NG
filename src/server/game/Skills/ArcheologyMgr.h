/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * This program is not free software. You may not redistribute
 * it or modify it.
 */

#ifndef __TRINITY_ARCHEOLOGY_MGR_H
#define __TRINITY_ARCHEOLOGY_MGR_H

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

enum eArcheology
{
    MAX_RESEARCH_SITES = 16,
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
    MAP_NORTHREND        = 571
};

enum eGameObjectsEntries
{
    ARCHEOLOGY_FIND_ORCS      = 207187,
    ARCHEOLOGY_FIND_DRANEI    = 207188,
    ARCHEOLOGY_FIND_TROLL     = 202655,
    ARCHEOLOGY_FIND_NERUBIAN  = 203078,
    ARCHEOLOGY_FIND_NIGHT_ELF = 203071,
    ARCHEOLOGY_FIND_VRYKUL    = 207189,
    ARCHEOLOGY_FIND_DWARF     = 204282,
    ARCHEOLOGY_FIND_FOSSIL    = 206836,
    ARCHEOLOGY_FIND_TOLVIR    = 207190
};

enum eKeyStoneEntries
{
    ARCHEOLOGY_STONE_ORC       = 64392,
    ARCHEOLOGY_STONE_DRAENEI   = 64394,
    ARCHEOLOGY_STONE_TROLL     = 63128,
    ARCHEOLOGY_STONE_NERUBIAN  = 64396,
    ARCHEOLOGY_STONE_NIGHT_ELF = 63127,
    ARCHEOLOGY_STONE_VRYKUL    = 64395,
    ARCHEOLOGY_STONE_DWARF     = 52843,
    ARCHEOLOGY_STONE_FOSSIL    = 0,
    ARCHEOLOGY_STONE_TOLVIR    = 64397
};

enum eUpdateAction
{
    UPDATE_GENERATE_NEW,
    UPDATE_EXCAVATION,
    UPDATE_LOADING,
    UPDATE_REMOVE
};

struct Artifact
{
    float positionX;
    float positionY;

    uint32 loot_GO_entry;
    uint32 loot_currency_type;
};

struct DigSite
{
    uint8 artifactsAvailable;
    uint16 entry;
    uint32 map;
    uint32 AreaID;

    Artifact artifacts[3];
};

typedef std::map<uint32, DigSite> digSiteList;

class Player;
class GameObject;

class ArcheologyMgr
{
    public:
        explicit ArcheologyMgr(Player* owner) : m_player(owner) { }
        ~ArcheologyMgr() { }

        // Internals.
        void Initialize();

        // Digsites.
        void _updateDigsite(uint32 digSiteId, uint8 action, bool updateClient = true);
        void OnSolvedProject(uint32 projectId);
        void OnSkillUpdate(uint16 skill);
        void SaveDigsitesToDB();
        void DeletePlayerDigsite(uint32 guid, uint32 digsiteId);
        void DeleteLastAvailableArtifact(uint32 guid, uint32 digsiteId);
        uint32 OnSurveyBotActivated();
        uint32 SetNearestFindOrientation();
        uint32 GenerateRandomDigSite(uint32 MapId);
        uint8 GetAvailableDigsitesArtifactsNum(uint32 digSiteId);

        uint8 GetEKDigSitesCount() { return _getMapDigsiteCount(MAP_EASTERN_KINGDOMS);}
        uint8 GetKLDigSitesCount() { return _getMapDigsiteCount(MAP_KALIMDOR);}
        uint8 GetOLDigSitesCount() { return _getMapDigsiteCount(MAP_OUTLAND);}
        uint8 GetNRDigSitesCount() { return _getMapDigsiteCount(MAP_NORTHREND);}

        digSiteList             m_digsites;                     // For sites which we have.

        // Projects.
        uint32 m_researchProject[28];                           // Current player projects.

        void GenerateResearchProject(uint32 branchId, bool force, uint32 excludeId);
        void GenerateSavedArtifacts();
        void CompleteArtifact(uint32 artId, uint32 spellId, ByteBuffer &data);
        void SaveCompletedProjectsToDB(uint32 guid, uint32 projectId);
        void SaveProjectToDB(uint32 guid, uint32 branchId, uint32 projectId);
        void DeletePlayerProject(uint32 guid, uint32 projectId);
        void UpdateCompletedProjectsCount(uint32 guid, uint32 projectId);
        uint32 GetCompletedProjectsCount(uint32 guid, uint32 projectId);
        uint32 GetCompletedProjectsTime(uint32 guid, uint32 projectId);

        std::list<uint32>       m_completedProjects;            // For completed projects which must not be used.
    private:
        void _loadCurrentDigsites();
        void _loadCompletedProjects();
        void _UpdateResearchFields();
        uint8 _CalculateDigsites(uint16 skill);
        uint8 _getMapDigsiteCount(uint32 MapId);

        uint8                   m_maxResearchSites;             // Maximum research sites a player can have
        Player*                 m_player;
};

#endif