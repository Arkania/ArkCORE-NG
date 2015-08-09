/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * This program is not free software. You may not redistribute 
 * it or modify it.
 *
 * TODO:
 *
 * - Fix wrong/missing db digsite artifact positions.
 * - Implement currency loot (needed for the gameobjects).
 * - Figure a way to deal with that idiotic switch construction, 
 * which determines the id of the gameobject to spawn ;)
 *
 * Done : 99%. ToDo : Above.
 */

#include "SharedDefines.h"
#include "ArcheologyMgr.h"
#include "DBCStores.h"
#include "WorldPacket.h"
#include "Common.h"
#include "DBCEnums.h"
#include "ObjectMgr.h"
#include "World.h"
#include "DatabaseEnv.h"
#include "CellImpl.h"
#include "GameEventMgr.h"
#include "GridNotifiersImpl.h"
#include "Language.h"
#include "Player.h"
#include "GameObject.h"
#include "SpellMgr.h"
#include "DisableMgr.h"
#include "ScriptMgr.h"
#include "MapManager.h"
#include "Map.h"

/****************************** INTERNAL *******************************/
void ArcheologyMgr::Initialize()
{
    m_completedProjects.clear(); 
    m_digsites.clear();

    _loadCurrentDigsites();
    _loadCompletedProjects();
}

/****************************** DIGSITES HANDLING *******************************/

void ArcheologyMgr::_loadCurrentDigsites()
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_PLAYER_SITE_IDS);
    stmt->setUInt32(0, m_player->GetGUIDLow());
    PreparedQueryResult activeDigSites = CharacterDatabase.Query(stmt);

    if (activeDigSites && activeDigSites->GetRowCount() > 0)
    {
        do
        {
            Field* row = activeDigSites->Fetch();
            uint16 digSiteId = row[0].GetUInt16();

            _updateDigsite(uint32(digSiteId), UPDATE_LOADING, false);
        }
        while(activeDigSites->NextRow());

        _UpdateResearchFields();
    }
}

uint8 ArcheologyMgr::GetAvailableDigsitesArtifactsNum(uint32 digSiteId)
{
    uint8 count = 0;
    PreparedStatement* stmt = NULL;

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_PLAYER_FIND_IDS);
    stmt->setUInt32(0, m_player->GetGUIDLow());
    stmt->setUInt32(1, digSiteId);
    PreparedQueryResult digSites = CharacterDatabase.Query(stmt);

    if (digSites && digSites->GetRowCount() > 0)
    {
        Field* row = digSites->Fetch();

        for (uint8 i = 0; i < 3; ++i)
            if (row[0+i].GetFloat() != 0.0f) // Can be both higher or lower, so let's not screw it.
                count++;
    }

    return count;
}

void ArcheologyMgr::DeleteLastAvailableArtifact(uint32 guid, uint32 digsiteId)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_PLAYER_FIND_IDS);
    stmt->setUInt32(0, m_player->GetGUIDLow());
    stmt->setUInt32(1, digsiteId);
    PreparedQueryResult digSites = CharacterDatabase.Query(stmt);

    if(digSites && digSites->GetRowCount() > 0)
    {
        uint8 findCount = GetAvailableDigsitesArtifactsNum(digsiteId); // Find we delete.

        switch (findCount)
        {
            case 0:
                return;
            case 1:
                CharacterDatabase.DirectPExecute("UPDATE character_archaeology_digsites SET find1PosX = 0, find1PosY = 0 WHERE guid = %u AND siteId = %u", guid, digsiteId);
                break;
            case 2:
                CharacterDatabase.DirectPExecute("UPDATE character_archaeology_digsites SET find2PosX = 0, find2PosY = 0 WHERE guid = %u AND siteId = %u", guid, digsiteId);
                break;
            case 3:
                CharacterDatabase.DirectPExecute("UPDATE character_archaeology_digsites SET find3PosX = 0, find3PosY = 0 WHERE guid = %u AND siteId = %u", guid, digsiteId);
                break;
        }
    }
}

void ArcheologyMgr::SaveDigsitesToDB()
{
    SQLTransaction trans = CharacterDatabase.BeginTransaction();
    PreparedStatement* stmt = NULL;

    if(m_digsites.size() > 0)
    {
        for(digSiteList::iterator itr = m_digsites.begin(); itr != m_digsites.end(); ++itr)
        {
            stmt = CharacterDatabase.GetPreparedStatement(CHAR_REP_PLAYER_SITES);

            stmt->setUInt32(0,m_player->GetGUIDLow());
            stmt->setUInt16(1,itr->first);
            stmt->setUInt16(2,itr->second.map);
            stmt->setUInt16(3,itr->second.AreaID);

            for (uint8 i = 0; i < 3; ++i)
            {
                stmt->setFloat(4+(i*2),itr->second.artifacts[i].positionX);
                stmt->setFloat(5+(i*2),itr->second.artifacts[i].positionY);
            }

            trans->Append(stmt);
        }
    }
    CharacterDatabase.CommitTransaction(trans);
}

void ArcheologyMgr::DeletePlayerDigsite(uint32 guid, uint32 digsiteId)
{
    SQLTransaction trans = CharacterDatabase.BeginTransaction();

    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_PLAYER_SITES);
    stmt->setUInt32(0, guid);
    stmt->setUInt32(1, digsiteId);

    trans->Append(stmt);

    CharacterDatabase.CommitTransaction(trans);
}

uint32 ArcheologyMgr::OnSurveyBotActivated()
{
    if (m_digsites.size() == 0 || !m_player->HasSkill(SKILL_ARCHAEOLOGY))
        return 0; // No object - should not happen normally.

    digSiteList::iterator iter = m_digsites.find(m_player->GetDigsiteEntry());

    // Check player digsites and current position.
    if (iter != m_digsites.end())
    {
        uint8 artifactPos = 0;
        float dist = ARCHAEOLOGY_DIG_SITE_RADIUS;

        switch (iter->second.artifactsAvailable)
        {
            case 1:
                dist = m_player->GetDistance2d(iter->second.artifacts[0].positionX, iter->second.artifacts[0].positionY);
                break;
            case 2:
                if (m_player->GetDistance2d(iter->second.artifacts[1].positionX, iter->second.artifacts[1].positionY) < m_player->GetDistance2d(iter->second.artifacts[0].positionX, iter->second.artifacts[0].positionY))
                {
                    dist = m_player->GetDistance2d(iter->second.artifacts[1].positionX, iter->second.artifacts[1].positionY);
                    artifactPos = 1;
                }
                else
                    dist = m_player->GetDistance2d(iter->second.artifacts[0].positionX, iter->second.artifacts[0].positionY);
                break;
            case 3:
                if (m_player->GetDistance2d(iter->second.artifacts[2].positionX, iter->second.artifacts[2].positionY) < m_player->GetDistance2d(iter->second.artifacts[1].positionX, iter->second.artifacts[1].positionY))
                {
                    dist = m_player->GetDistance2d(iter->second.artifacts[2].positionX, iter->second.artifacts[2].positionY);
                    artifactPos = 2;
                }
                else if (m_player->GetDistance2d(iter->second.artifacts[2].positionX, iter->second.artifacts[2].positionY) < m_player->GetDistance2d(iter->second.artifacts[0].positionX, iter->second.artifacts[0].positionY))
                {
                    dist = m_player->GetDistance2d(iter->second.artifacts[2].positionX, iter->second.artifacts[2].positionY);
                    artifactPos = 2;
                }
                else if (m_player->GetDistance2d(iter->second.artifacts[1].positionX, iter->second.artifacts[1].positionY) < m_player->GetDistance2d(iter->second.artifacts[0].positionX, iter->second.artifacts[0].positionY))
                {
                    dist = m_player->GetDistance2d(iter->second.artifacts[1].positionX, iter->second.artifacts[1].positionY);
                    artifactPos = 1;
                }
                else
                    dist = m_player->GetDistance2d(iter->second.artifacts[0].positionX, iter->second.artifacts[0].positionY);
                break;
        }

        if (dist <= ARCHAEOLOGY_DIG_SITE_FAR_DIST && dist > ARCHAEOLOGY_DIG_SITE_MED_DIST) // Red 80-50y
            return ARCHAEOLOGY_DIG_SITE_FAR_SURVEYBOT;
        else if (dist <= ARCHAEOLOGY_DIG_SITE_MED_DIST && dist > ARCHAEOLOGY_DIG_SITE_CLOSE_DIST) // Yellow 50-20y
            return ARCHAEOLOGY_DIG_SITE_MEDIUM_SURVEYBOT;
        else if (dist <= ARCHAEOLOGY_DIG_SITE_CLOSE_DIST && dist > ARCHAEOLOGY_DIG_SITE_FIND_DIST) // Green 20-5y
            return ARCHAEOLOGY_DIG_SITE_CLOSE_SURVEYBOT;
        else if (dist <= ARCHAEOLOGY_DIG_SITE_FIND_DIST) // Found it!
        {
            m_player->ModifyCurrency(iter->second.artifacts[artifactPos].loot_currency_type, urand(5, 9)); // Add a random number of 5-9 fragments to the player : 4.3 Archaeology change.

            // Advance Archaeology skill. - done from gather skill in player.cpp on open container.
            //m_player->SetSkill(SKILL_ARCHAEOLOGY, m_player->GetSkillStep(SKILL_ARCHAEOLOGY), m_player->GetSkillValue(SKILL_ARCHAEOLOGY) + 1, m_player->GetPureMaxSkillValue(SKILL_ARCHAEOLOGY));

            uint32 findGoEntry = iter->second.artifacts[artifactPos].loot_GO_entry;

            _updateDigsite(iter->first, UPDATE_EXCAVATION, false);

            return findGoEntry;
        }
    }
    else return 0; // Summon nothing.

return 0;
}

uint32 ArcheologyMgr::SetNearestFindOrientation() // must bind this to show same artifact angle until it is found.
{
    if (m_digsites.size() == 0 || !m_player->HasSkill(SKILL_ARCHAEOLOGY))
        return 0; // No angle - should not happen normally.

    digSiteList::iterator iter = m_digsites.find(m_player->GetDigsiteEntry());

    // Check player digsites and current position.
    if (iter != m_digsites.end())
    {
        switch (iter->second.artifactsAvailable)
        {
            case 1:
                return m_player->GetAngle(iter->second.artifacts[0].positionX, iter->second.artifacts[0].positionY);
                break;
            case 2:
                if (m_player->GetDistance2d(iter->second.artifacts[1].positionX, iter->second.artifacts[1].positionY) < m_player->GetDistance2d(iter->second.artifacts[0].positionX, iter->second.artifacts[0].positionY))
                    return m_player->GetAngle(iter->second.artifacts[1].positionX, iter->second.artifacts[1].positionY);
                else
                    return m_player->GetAngle(iter->second.artifacts[0].positionX, iter->second.artifacts[0].positionY);
                break;
            case 3:
                if (m_player->GetDistance2d(iter->second.artifacts[2].positionX, iter->second.artifacts[2].positionY) < m_player->GetDistance2d(iter->second.artifacts[1].positionX, iter->second.artifacts[1].positionY))
                    return m_player->GetAngle(iter->second.artifacts[2].positionX, iter->second.artifacts[2].positionY);
                else if (m_player->GetDistance2d(iter->second.artifacts[2].positionX, iter->second.artifacts[2].positionY) < m_player->GetDistance2d(iter->second.artifacts[0].positionX, iter->second.artifacts[0].positionY))
                    return m_player->GetAngle(iter->second.artifacts[2].positionX, iter->second.artifacts[2].positionY);
                else if (m_player->GetDistance2d(iter->second.artifacts[1].positionX, iter->second.artifacts[1].positionY) < m_player->GetDistance2d(iter->second.artifacts[0].positionX, iter->second.artifacts[0].positionY))
                    return m_player->GetAngle(iter->second.artifacts[1].positionX, iter->second.artifacts[1].positionY);
                else
                    return m_player->GetAngle(iter->second.artifacts[0].positionX, iter->second.artifacts[0].positionY);
                break;
        }
    }
    else return 0;

return 0; // No angle
}

void ArcheologyMgr::OnSkillUpdate(uint16 skill)
{
    m_maxResearchSites = _CalculateDigsites(skill);

    uint8 diff = m_maxResearchSites - m_digsites.size();

    if(m_digsites.size() == 0)
    {
        for(uint8 i = 0; i < m_maxResearchSites;++i)
        {
            _updateDigsite(GenerateRandomDigSite(i/4),UPDATE_GENERATE_NEW,false);
        }
    }
    else if(diff > 0)
    {
        uint8 missingDigsites = 0;
        if(GetEKDigSitesCount() < 4)
        {
            missingDigsites = 4 - GetEKDigSitesCount();

            for(uint8 i = 0; i < missingDigsites;++i)
            {
                _updateDigsite(GenerateRandomDigSite(MAP_EASTERN_KINGDOMS),UPDATE_GENERATE_NEW,false);
            }
            diff -= missingDigsites;
        }
        else if(GetKLDigSitesCount() < 4)
        {
            missingDigsites = 4 - GetKLDigSitesCount();

            for(uint8 i = 0; i < missingDigsites;++i)
            {
                _updateDigsite(GenerateRandomDigSite(MAP_KALIMDOR),UPDATE_GENERATE_NEW,false);
            }
            diff -= missingDigsites;
        }
        else if(GetOLDigSitesCount() < 4)
        {
            missingDigsites = 4 - GetOLDigSitesCount();

            for(uint8 i = 0; i < missingDigsites;++i)
            {
                _updateDigsite(GenerateRandomDigSite(MAP_OUTLAND),UPDATE_GENERATE_NEW,false);
            }
            diff -= missingDigsites;
        }
        else if(GetNRDigSitesCount() < 4)
        {
            missingDigsites = 4 - GetNRDigSitesCount();

            for(uint8 i = 0; i < missingDigsites;++i)
            {
                _updateDigsite(GenerateRandomDigSite(MAP_NORTHREND),UPDATE_GENERATE_NEW,false);
            }
            diff -= missingDigsites;
        }
    }

    _UpdateResearchFields();
    SaveDigsitesToDB(); // save the newly generated sites.
}

uint8 ArcheologyMgr::_getMapDigsiteCount(uint32 MapId)
{
    uint8 count = 0;

    for(digSiteList::iterator itr = m_digsites.begin(); itr != m_digsites.end();++itr)
    {
        if(itr->second.map == MapId)
            ++count;
    }

    return count;
}

void ArcheologyMgr::_updateDigsite(uint32 digSiteId,uint8 action, bool updateClient)
{
    PreparedStatement* stmt = NULL;

    switch(action)
    {
        case UPDATE_GENERATE_NEW:
        {
            stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_DIGSITE_INFO);
            stmt->setUInt32(0,digSiteId);
            PreparedQueryResult resultInfo = WorldDatabase.Query(stmt);

            if(resultInfo && resultInfo->GetRowCount() > 0)
            {
                Field* digsiteInfo = resultInfo->Fetch();
                DigSite newDigSite;
                newDigSite.entry = digSiteId;
                newDigSite.map = digsiteInfo[1].GetUInt16();
                newDigSite.AreaID = digsiteInfo[2].GetUInt16();
                newDigSite.artifactsAvailable = 3; // When first generated, they have three artifacts available.

                stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_DIGSITE_POS);
                stmt->setUInt32(0,digSiteId);
                PreparedQueryResult resultPos = WorldDatabase.Query(stmt);

                if(resultPos && resultPos->GetRowCount() > 0)
                {
                    uint8 counter = 0;
                    do
                    {
                        if (counter < 3)
                        {
                            Field* digsitePos = resultPos->Fetch();
                            newDigSite.artifacts[counter].positionX = digsitePos[1].GetFloat();
                            newDigSite.artifacts[counter].positionY = digsitePos[2].GetFloat();

                            switch(newDigSite.map) // The finds depend on the map.
                            {
                                case 530: // Outland Fragments (Orc and Draenei currency).
                                    if (newDigSite.entry == 339 || newDigSite.entry == 341 || newDigSite.entry == 343 || newDigSite.entry == 345 || newDigSite.entry == 359 || newDigSite.entry == 363 || newDigSite.entry == 365 || newDigSite.entry == 367 || newDigSite.entry == 371 || newDigSite.entry == 375 || newDigSite.entry == 377 || newDigSite.entry == 395 || newDigSite.entry == 399) // Orc fragments.
                                    {
                                        newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_ORCS;
                                        newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_ORC_FRAGMENT;
                                    }
                                    else // Draenei fragments.
                                    {
                                        newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_DRANEI;
                                        newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_DRAENEI_FRAGMENT;
                                    }
                                    break;

                                case 571: // Northrend Fragments (Vrykul, Nerubian, Troll, Night Elf currency).
                                    if (newDigSite.entry == 429 || newDigSite.entry == 431 || newDigSite.entry == 433 || newDigSite.entry == 435 || newDigSite.entry == 443) // Troll fragments.
                                    {
                                        newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_TROLL;
                                        newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_TROLL_FRAGMENT;
                                    }
                                    else if (newDigSite.entry == 415 || newDigSite.entry == 419 || newDigSite.entry == 421|| newDigSite.entry == 437 || newDigSite.entry == 451 || newDigSite.entry == 587 || newDigSite.entry == 589) // Nerubian fragments.
                                    {
                                        newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_NERUBIAN;
                                        newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_NERUBIAN_FRAGMENT;
                                    }
                                    else if (newDigSite.entry == 423 || newDigSite.entry == 425 || newDigSite.entry == 427) // Night Elf fragments.
                                    {
                                        newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_NIGHT_ELF;
                                        newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_NELF_FRAGMENT;
                                    }
                                    else // Vrykul fragments.
                                    {
                                        newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_VRYKUL;
                                        newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_VRYKUL_FRAGMENT;
                                    }
                                    break;

                                case 0: //Eastern Kingdoms Fragments (Night Elf, Fossil, Nerubian, Troll, Dwarf currency).
                                    if (newDigSite.entry == 18 || newDigSite.entry == 23 || newDigSite.entry == 24 || newDigSite.entry == 25 || newDigSite.entry == 26 || newDigSite.entry == 27 || newDigSite.entry == 152 || newDigSite.entry == 217 || newDigSite.entry == 223 || newDigSite.entry == 225 || newDigSite.entry == 227 || newDigSite.entry == 229 || newDigSite.entry == 231 || newDigSite.entry == 233 || newDigSite.entry == 235 || newDigSite.entry == 239 || newDigSite.entry == 241 || newDigSite.entry == 243 || newDigSite.entry == 245) // Troll fragments.
                                    {
                                        newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_TROLL;
                                        newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_TROLL_FRAGMENT;
                                    }
                                    else if (newDigSite.entry == 615 || newDigSite.entry == 617) // Nerubian fragments.
                                    {
                                        newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_NERUBIAN;
                                        newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_NERUBIAN_FRAGMENT;
                                    }
                                    else if (newDigSite.entry == 163 || newDigSite.entry == 219 || newDigSite.entry == 471 || newDigSite.entry == 473 || newDigSite.entry == 475) // Night Elf fragments.
                                    {
                                        newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_NIGHT_ELF;
                                        newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_NELF_FRAGMENT;
                                    }
                                    else if (newDigSite.entry == 9 || newDigSite.entry == 10 || newDigSite.entry == 12 || newDigSite.entry == 15 || newDigSite.entry == 19 || newDigSite.entry == 20 || newDigSite.entry == 22 || newDigSite.entry == 144 || newDigSite.entry == 146 || newDigSite.entry == 150 || newDigSite.entry == 207 || newDigSite.entry == 209 || newDigSite.entry == 211 || newDigSite.entry == 213 || newDigSite.entry == 477 || newDigSite.entry == 479 || newDigSite.entry == 481) // Dwarf fragments.
                                    {
                                        newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_DWARF;
                                        newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_DWARF_FRAGMENT;
                                    }
                                    else // Fossil fragments.
                                    {
                                        newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_FOSSIL;
                                        newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_FOSSIL_FRAGMENT;
                                    }
                                    break;

                                case 1: //Kalimdor Fragments (Night Elf, Fossil, Tol'vir, Troll, Dwarf currency).
                                    if (newDigSite.entry == 315 || newDigSite.entry == 317 || newDigSite.entry == 319 || newDigSite.entry == 321) // Troll fragments.
                                    {
                                        newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_TROLL;
                                        newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_TROLL_FRAGMENT;
                                    }
                                    else if (newDigSite.entry == 485 || newDigSite.entry == 487 || newDigSite.entry == 489 || newDigSite.entry == 491 || newDigSite.entry == 493 || newDigSite.entry == 495 || newDigSite.entry == 497 || newDigSite.entry == 499 || newDigSite.entry == 501 || newDigSite.entry == 570 || newDigSite.entry == 572 || newDigSite.entry == 574 || newDigSite.entry == 576 || newDigSite.entry == 578 || newDigSite.entry == 581 || newDigSite.entry == 583) // Tol'vir fragments.
                                    {
                                        newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_TOLVIR;
                                        newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_TOLVIR_FRAGMENT;
                                    }
                                    else if (newDigSite.entry == 167 || newDigSite.entry == 169 || newDigSite.entry == 171 || newDigSite.entry == 173 || newDigSite.entry == 175 || newDigSite.entry == 177 || newDigSite.entry == 179 || newDigSite.entry == 185 || newDigSite.entry == 187 || newDigSite.entry == 191 || newDigSite.entry == 193 || newDigSite.entry == 197 || newDigSite.entry == 201 || newDigSite.entry == 279 || newDigSite.entry == 281 || newDigSite.entry == 283 || newDigSite.entry == 285 ||
                                        newDigSite.entry == 287 || newDigSite.entry == 289 || newDigSite.entry == 291 || newDigSite.entry == 293 || newDigSite.entry == 295 || newDigSite.entry == 297 || newDigSite.entry == 299 || newDigSite.entry == 301 || newDigSite.entry == 303 || newDigSite.entry == 305 || newDigSite.entry == 307 || newDigSite.entry == 313 || newDigSite.entry == 337 || newDigSite.entry == 461 || newDigSite.entry == 463 || newDigSite.entry == 465 || newDigSite.entry == 467 || newDigSite.entry == 469) // Night Elf fragments.
                                    {
                                        newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_NIGHT_ELF;
                                        newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_NELF_FRAGMENT;
                                    }
                                    else if (newDigSite.entry == 183) // Dwarf fragments.
                                    {
                                        newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_DWARF;
                                        newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_DWARF_FRAGMENT;
                                    }
                                    else // Fossil fragments.
                                    {
                                        newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_FOSSIL;
                                        newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_FOSSIL_FRAGMENT;
                                    }
                                    break;
                            }
                            counter++;
                        }
                    }
                    while(resultPos->NextRow());
                    m_digsites[digSiteId] = newDigSite;
                }
            }
            break;
        }
        case UPDATE_LOADING:
        {
            stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_PLAYER_SITES);
            stmt->setUInt32(0, m_player->GetGUIDLow());
            stmt->setUInt32(1, digSiteId);
            PreparedQueryResult resultInfo = CharacterDatabase.Query(stmt);

            if(resultInfo && resultInfo->GetRowCount() > 0)
            {
                Field* digsiteInfo = resultInfo->Fetch();
                DigSite newDigSite;
                newDigSite.entry = digSiteId;
                newDigSite.artifactsAvailable = GetAvailableDigsitesArtifactsNum(digSiteId);
                newDigSite.map = digsiteInfo[1].GetUInt16();
                newDigSite.AreaID = digsiteInfo[2].GetUInt16();

                for (uint8 counter = 0; counter < newDigSite.artifactsAvailable; counter++)
                {
                    newDigSite.artifacts[counter].positionX = digsiteInfo[3+(counter*2)].GetFloat();
                    newDigSite.artifacts[counter].positionY = digsiteInfo[4+(counter*2)].GetFloat();

                    switch(newDigSite.map) // The finds depend on the map.
                    {
                        case 530: // Outland Fragments (Orc and Draenei currency).
                            if (newDigSite.entry == 339 || newDigSite.entry == 341 || newDigSite.entry == 343 || newDigSite.entry == 345 || newDigSite.entry == 359 || newDigSite.entry == 363 || newDigSite.entry == 365 || newDigSite.entry == 367 || newDigSite.entry == 371 || newDigSite.entry == 375 || newDigSite.entry == 377 || newDigSite.entry == 395 || newDigSite.entry == 399) // Orc fragments.
                            {
                                newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_ORCS;
                                newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_ORC_FRAGMENT;
                            }
                            else // Draenei fragments.
                            {
                                newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_DRANEI;
                                newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_DRAENEI_FRAGMENT;
                            }
                            break;

                        case 571: // Northrend Fragments (Vrykul, Nerubian, Troll, Night Elf currency).
                            if (newDigSite.entry == 429 || newDigSite.entry == 431 || newDigSite.entry == 433 || newDigSite.entry == 435 || newDigSite.entry == 443) // Troll fragments.
                            {
                                newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_TROLL;
                                newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_TROLL_FRAGMENT;
                            }
                            else if (newDigSite.entry == 415 || newDigSite.entry == 419 || newDigSite.entry == 421|| newDigSite.entry == 437 || newDigSite.entry == 451 || newDigSite.entry == 587 || newDigSite.entry == 589) // Nerubian fragments.
                            {
                                newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_NERUBIAN;
                                newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_NERUBIAN_FRAGMENT;
                            }
                            else if (newDigSite.entry == 423 || newDigSite.entry == 425 || newDigSite.entry == 427) // Night Elf fragments.
                            {
                                newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_NIGHT_ELF;
                                newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_NELF_FRAGMENT;
                            }
                            else // Vrykul fragments.
                            {
                                newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_VRYKUL;
                                newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_VRYKUL_FRAGMENT;
                            }
                            break;

                        case 0: //Eastern Kingdoms Fragments (Night Elf, Fossil, Nerubian, Troll, Dwarf currency).
                            if (newDigSite.entry == 18 || newDigSite.entry == 23 || newDigSite.entry == 24 || newDigSite.entry == 25 || newDigSite.entry == 26 || newDigSite.entry == 27 || newDigSite.entry == 152 || newDigSite.entry == 217 || newDigSite.entry == 223 || newDigSite.entry == 225 || newDigSite.entry == 227 || newDigSite.entry == 229 || newDigSite.entry == 231 || newDigSite.entry == 233 || newDigSite.entry == 235 || newDigSite.entry == 239 || newDigSite.entry == 241 || newDigSite.entry == 243 || newDigSite.entry == 245) // Troll fragments.
                            {
                                newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_TROLL;
                                newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_TROLL_FRAGMENT;
                            }
                            else if (newDigSite.entry == 615 || newDigSite.entry == 617) // Nerubian fragments.
                            {
                                newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_NERUBIAN;
                                newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_NERUBIAN_FRAGMENT;
                            }
                            else if (newDigSite.entry == 163 || newDigSite.entry == 219 || newDigSite.entry == 471 || newDigSite.entry == 473 || newDigSite.entry == 475) // Night Elf fragments.
                            {
                                newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_NIGHT_ELF;
                                newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_NELF_FRAGMENT;
                            }
                            else if (newDigSite.entry == 9 || newDigSite.entry == 10 || newDigSite.entry == 12 || newDigSite.entry == 15 || newDigSite.entry == 19 || newDigSite.entry == 20 || newDigSite.entry == 22 || newDigSite.entry == 144 || newDigSite.entry == 146 || newDigSite.entry == 150 || newDigSite.entry == 207 || newDigSite.entry == 209 || newDigSite.entry == 211 || newDigSite.entry == 213 || newDigSite.entry == 477 || newDigSite.entry == 479 || newDigSite.entry == 481) // Dwarf fragments.
                            {
                                newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_DWARF;
                                newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_DWARF_FRAGMENT;
                            }
                            else // Fossil fragments.
                            {
                                newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_FOSSIL;
                                newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_FOSSIL_FRAGMENT;
                            }
                            break;

                        case 1: //Kalimdor Fragments (Night Elf, Fossil, Tol'vir, Troll, Dwarf currency).
                            if (newDigSite.entry == 315 || newDigSite.entry == 317 || newDigSite.entry == 319 || newDigSite.entry == 321) // Troll fragments.
                            {
                                newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_TROLL;
                                newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_TROLL_FRAGMENT;
                            }
                            else if (newDigSite.entry == 485 || newDigSite.entry == 487 || newDigSite.entry == 489 || newDigSite.entry == 491 || newDigSite.entry == 493 || newDigSite.entry == 495 || newDigSite.entry == 497 || newDigSite.entry == 499 || newDigSite.entry == 501 || newDigSite.entry == 570 || newDigSite.entry == 572 || newDigSite.entry == 574 || newDigSite.entry == 576 || newDigSite.entry == 578 || newDigSite.entry == 581 || newDigSite.entry == 583) // Tol'vir fragments.
                            {
                                newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_TOLVIR;
                                newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_TOLVIR_FRAGMENT;
                            }
                            else if (newDigSite.entry == 167 || newDigSite.entry == 169 || newDigSite.entry == 171 || newDigSite.entry == 173 || newDigSite.entry == 175 || newDigSite.entry == 177 || newDigSite.entry == 179 || newDigSite.entry == 185 || newDigSite.entry == 187 || newDigSite.entry == 191 || newDigSite.entry == 193 || newDigSite.entry == 197 || newDigSite.entry == 201 || newDigSite.entry == 279 || newDigSite.entry == 281 || newDigSite.entry == 283 || newDigSite.entry == 285 ||
                                newDigSite.entry == 287 || newDigSite.entry == 289 || newDigSite.entry == 291 || newDigSite.entry == 293 || newDigSite.entry == 295 || newDigSite.entry == 297 || newDigSite.entry == 299 || newDigSite.entry == 301 || newDigSite.entry == 303 || newDigSite.entry == 305 || newDigSite.entry == 307 || newDigSite.entry == 313 || newDigSite.entry == 337 || newDigSite.entry == 461 || newDigSite.entry == 463 || newDigSite.entry == 465 || newDigSite.entry == 467 || newDigSite.entry == 469) // Night Elf fragments.
                            {
                                newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_NIGHT_ELF;
                                newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_NELF_FRAGMENT;
                            }
                            else if (newDigSite.entry == 183) // Dwarf fragments.
                            {
                                newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_DWARF;
                                newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_DWARF_FRAGMENT;
                            }
                            else // Fossil fragments.
                            {
                                newDigSite.artifacts[counter].loot_GO_entry = ARCHEOLOGY_FIND_FOSSIL;
                                newDigSite.artifacts[counter].loot_currency_type = CURRENCY_TYPE_FOSSIL_FRAGMENT;
                            }
                            break;
                    }
                }

                m_digsites[digSiteId] = newDigSite;
            }
            break;
        }
        case UPDATE_REMOVE:
        {
            digSiteList::iterator itr = m_digsites.find(digSiteId);
            if(itr != m_digsites.end())
            {
                DeletePlayerDigsite(m_player->GetGUIDLow(), digSiteId); // delete current
                m_digsites.erase(itr);
            }
            break;
        }
        case UPDATE_EXCAVATION:
        {
            digSiteList::iterator itr = m_digsites.find(digSiteId);
            if(itr != m_digsites.end())
            {
                if (itr->second.artifactsAvailable > 1)
                {
                    itr->second.artifactsAvailable--;
                    DeleteLastAvailableArtifact(m_player->GetGUIDLow(), digSiteId);
                }
                else if (itr->second.artifactsAvailable == 1)
                {
                    itr->second.artifactsAvailable--; // set to 0.
                    //here we remove the digsite, then generate a new one ;) We use recursion
                    _updateDigsite(digSiteId, UPDATE_REMOVE, false);
                    _updateDigsite(GenerateRandomDigSite(m_player->GetMapId()), UPDATE_GENERATE_NEW, true);
                    SaveDigsitesToDB(); // prevent crash on next DeleteLastAvailableArtifact in the new site, by saving it to the db.
                }
            }
            break;
        }
    }

    if(updateClient)
        _UpdateResearchFields();
}

uint8 ArcheologyMgr::_CalculateDigsites(uint16 skill)
{
    uint8 digsites; // Count.

    if(skill <= 275)
    {
        digsites = MAX_RESEARCH_SITES / 2;
    }
    else if(skill > 275 && skill <= 350)
    {
        digsites = MAX_RESEARCH_SITES - 4;
    }
    else
    {
        digsites = MAX_RESEARCH_SITES;
    }

    return digsites;
}

void ArcheologyMgr::_UpdateResearchFields()
{
    uint8 counter = 0;
    for(digSiteList::iterator itr = m_digsites.begin(); itr != m_digsites.end(); ++itr)
    {
        m_player->SetUInt16Value(PLAYER_FIELD_RESERACH_SITE_1+(counter/2),counter%2,itr->second.entry);
        ++counter;
    }
}

uint32 ArcheologyMgr::GenerateRandomDigSite(uint32 MapId) // For generating a digsite when a project is solved. It is same thing as for initial digsites, diff is we select only 1, not 4.
{
    if (MapId != 0 && MapId != 1 && MapId != 530 && MapId != 571) // Can only have digsites on these 4 maps (EK, Kalimdor, Outland, Northrend).
        return 0; // Map Id is invalid!

    uint8 level = m_player->getLevel();

    if (level < 20)
        return 0; // You don't have required level!

    uint16 skill_now = m_player->GetSkillValue(SKILL_ARCHAEOLOGY);

    int16 levelToSelect = 0;
    uint32 site = 0;

    if (level >= 20 && level <= 30) // Levels 20 - 30
        levelToSelect = 20;
    else if (level > 30 && level <= 40) // Levels 31 - 40
            levelToSelect = 30;
    else if (level > 40 && level <= 50) // Levels 41 - 50
            levelToSelect = 40;
    else if (level > 50 && level <= 80) // Levels 51 - 80
            levelToSelect = 50;
    else if (level > 80 && level <= 85) // Levels 81 - 85
    {
        if (skill_now < 450) // Cata zones requirement. Lower skill -> You can't get such a zone.
            levelToSelect = 50;
        else // You can get Cata zones too.
            levelToSelect = 85;
    }

    PreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_RANDOM_DIGSITE);

    stmt->setUInt16(0, levelToSelect);
    stmt->setUInt16(1, MapId);

    PreparedQueryResult result = WorldDatabase.Query(stmt);

    if(result && result->GetRowCount() > 0)
    {
        do
        {
            Field* row = result->Fetch();
            uint32 digSite = row[0].GetUInt32();

            if (m_digsites.find(digSite) == m_digsites.end())
                site = digSite;
        }
        while (result->NextRow() && result->GetRowPosition() < result->GetRowCount() && site == 0);
    }

    return site;
}

/****************************** PROJECTS HANDLING *******************************/

void ArcheologyMgr::GenerateResearchProject(uint32 branchId, bool force, uint32 excludeId)
{
    if (m_researchProject[branchId] != 0 && !force)
    {
        TC_LOG_INFO("server.loading", "Project not generated, m_researchProject[%u] is not 0", branchId);
        return;
    }

    // Remove old
    if (force)
    {
        uint32 reset_value = 0;
        uint8 resetSlot = 0;
        for (uint8 i = 0; i < 5; i++)
        {
            uint32 project_now_1 = m_player->GetUInt32Value(PLAYER_FIELD_RESEARCHING_1 + i) & 0xFFFF;
            uint32 project_now_2 = m_player->GetUInt32Value(PLAYER_FIELD_RESEARCHING_1 + i) >> 16;

            if (project_now_1 == m_researchProject[branchId])
            {
                resetSlot = int32(i);
                reset_value = (project_now_2 << 16) | 0;
                break;
            } else if (project_now_2 == m_researchProject[branchId])
            {
                resetSlot = int32(i);
                reset_value = (0 << 16) | (project_now_1);
                break;
            }
        }

        m_player->SetUInt32Value(PLAYER_FIELD_RESEARCHING_1 + resetSlot, reset_value);
        m_researchProject[branchId] = 0;
    }

    uint32 skill_now = m_player->GetSkillValue(SKILL_ARCHAEOLOGY);
    std::list<uint32> projectList;
    for(uint32 row = 39; row < sResearchProjectStore.GetNumRows(); row++)
    {
        ResearchProjectEntry* rs = sResearchProjectStore.LookupRow(row);
        if (!rs)
            continue;

        if (rs->ResearchBranchID != branchId)
            continue;

        if (excludeId != 0)
            if (rs->ProjectSpell == excludeId)
                continue;

        uint32 frag_req = 75;
        if (skill_now / 3 > 75)
            frag_req = skill_now / 3;

        if (rs->RequiredFragments > frag_req)
            continue;

        //stop generating crap - this needs check, i think crap is generated even at high skill.
        //if (rs->Complexity < std::max<uint32>(0, skill_now / 75 - 2))
        //    continue;

        projectList.push_back(rs->ID);
    }

    uint32 selectedProject = urand (0, projectList.size());
    uint8 count = 0;

    if (projectList.size() == 0)
    {
      TC_LOG_INFO("server.loading", "Project list size is 0!");
      return;
    }

    for (std::list<uint32>::const_iterator itr = projectList.begin(); itr != projectList.end(); ++itr)
    {
        if (count == selectedProject)
        {
            int32 slot = -10;
            int32 new_value = -10;
            for (uint8 i = 0; i < 5; i++)
            {
                uint32 project_now_1 = m_player->GetUInt32Value(PLAYER_FIELD_RESEARCHING_1 + i) & 0xFFFF;
                uint32 project_now_2 = m_player->GetUInt32Value(PLAYER_FIELD_RESEARCHING_1 + i) >> 16;

                if (project_now_1 == 0)
                {
                    slot = int32(i);
                    new_value = (project_now_2 << 16) | (*itr);
                    break;
                } else if (project_now_2 == 0)
                {
                    slot = int32(i);
                    new_value = ((*itr) << 16) | (project_now_1);
                    break;
                }
            }

            if (slot >= 0 && new_value >= 0)
            {
                m_player->SetUInt32Value(PLAYER_FIELD_RESEARCHING_1 + slot, new_value);
                // Save it to the DB.
                SaveProjectToDB(m_player->GetGUIDLow(), branchId, new_value);
            }

            m_researchProject[branchId] = (*itr);
            break;
        }
        count++;
    }
}

void ArcheologyMgr::GenerateSavedArtifacts()
{
    uint8 slot = 0;
    for (uint8 i = 1; i < 28; i++)
    {
        if (i == 9)
            i = 27;

        uint32 project_1 = m_researchProject[i];
        uint32 project_2 = 0;

        if (i != 27)
            project_2 = m_researchProject[i+1];

        uint32 value = (project_2 << 16) | (project_1);
        m_player->SetUInt32Value(PLAYER_FIELD_RESEARCHING_1 + slot, value);
        ++slot;
        ++i;
    }
}

void ArcheologyMgr::CompleteArtifact(uint32 artId, uint32 /*spellId*/, ByteBuffer &data)
{
    uint32 target_mask, unk1, unk2, numberOfStones;
    data >> target_mask >> unk1 >> unk2 >> numberOfStones;

    if (numberOfStones == 256 || numberOfStones == 512 || numberOfStones == 768)
        numberOfStones = numberOfStones / 256;
    else
        numberOfStones = 0;

    if (ResearchProjectEntry* rp = sResearchProjectStore.LookupRow(artId))
    {
        uint32 currencyId = 0;
        uint32 stone = 0;
        switch (rp->ResearchBranchID)
        {
            // Dwarf
            case 1: currencyId = CURRENCY_TYPE_DWARF_FRAGMENT; stone = ARCHEOLOGY_STONE_DWARF; break;
            // Draenei
            case 2: currencyId = CURRENCY_TYPE_DRAENEI_FRAGMENT; stone = ARCHEOLOGY_STONE_DRAENEI; break;
            // Fossil
            case 3: currencyId = CURRENCY_TYPE_FOSSIL_FRAGMENT; stone = ARCHEOLOGY_STONE_FOSSIL; break;
            // Nerubian
            case 5: currencyId = CURRENCY_TYPE_NERUBIAN_FRAGMENT; stone = ARCHEOLOGY_STONE_NERUBIAN; break;
            // Night Elf
            case 4: currencyId = CURRENCY_TYPE_NELF_FRAGMENT; stone = ARCHEOLOGY_STONE_NIGHT_ELF; break;
            // Orc
            case 6: currencyId = CURRENCY_TYPE_ORC_FRAGMENT; stone = ARCHEOLOGY_STONE_ORC; break;
            // Tol'vir
            case 7: currencyId = CURRENCY_TYPE_TOLVIR_FRAGMENT; stone = ARCHEOLOGY_STONE_TOLVIR; break;
            // Troll
            case 8: currencyId = CURRENCY_TYPE_TROLL_FRAGMENT; stone = ARCHEOLOGY_STONE_TROLL; break;
            // Vrykul
            case 27: currencyId = CURRENCY_TYPE_VRYKUL_FRAGMENT; stone = ARCHEOLOGY_STONE_VRYKUL; break;
        }

        uint32 currencySale = 0;
        if (numberOfStones > 0)
        {
            if (m_player->HasItemCount(stone, numberOfStones, false))
                currencySale = 12 * numberOfStones;
        }

        bool found = false;
        for (uint8 x = 0; x < 5; x++)
        {
            uint32 project_now_1 = m_player->GetUInt32Value(PLAYER_FIELD_RESEARCHING_1 + x) & 0xFFFF;
            uint32 project_now_2 = m_player->GetUInt32Value(PLAYER_FIELD_RESEARCHING_1 + x) >> 16;

            if (project_now_1 == rp->ID || project_now_2 == rp->ID)
            {
                found = true;
                break;
            }
        }

        if (!found)
            return;

        int32 bp0 = int32(numberOfStones);

        if (currencyId != 0)
            if (m_player->GetCurrency(currencyId, true) >= rp->RequiredFragments - currencySale)
            {
                m_player->CastCustomSpell(m_player, rp->ProjectSpell, &bp0, NULL, NULL, false);
                // Save to completed projects.
                if (std::find(m_completedProjects.begin(), m_completedProjects.end(), rp->ID) == m_completedProjects.end()) // not in the list.
                {
                    m_completedProjects.push_back(rp->ID);
                    SaveCompletedProjectsToDB(m_player->GetGUIDLow(), rp->ID);
                }
                else
                    UpdateCompletedProjectsCount(m_player->GetGUIDLow(), rp->ID);
                // Delete from current ones.
                DeletePlayerProject(m_player->GetGUIDLow(), rp->ID);
            }
    }
}

void ArcheologyMgr::SaveProjectToDB(uint32 guid, uint32 branchId, uint32 projectId) // For projects.
{
    SQLTransaction trans = CharacterDatabase.BeginTransaction();
    PreparedStatement* stmt = NULL;
    
    stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_PLAYER_PROJECT);
    stmt->setUInt32(0, guid);
    stmt->setUInt32(1, branchId);
    stmt->setUInt32(2, projectId);
    
    trans->Append(stmt);
    
    CharacterDatabase.CommitTransaction(trans);
}

void ArcheologyMgr::DeletePlayerProject(uint32 guid, uint32 projectId)
{
    SQLTransaction trans = CharacterDatabase.BeginTransaction();
    PreparedStatement* stmt = NULL;

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_PLAYER_PROJECT);
    stmt->setUInt32(0, guid);
    stmt->setUInt32(1, projectId);

    trans->Append(stmt);

    CharacterDatabase.CommitTransaction(trans);
}

void ArcheologyMgr::SaveCompletedProjectsToDB(uint32 guid, uint32 projectId)
{
    uint32 count = 1; // First inserted completed project count.
    time_t currTime = time(NULL); // Completion time.
    SQLTransaction trans = CharacterDatabase.BeginTransaction();
    PreparedStatement* stmt = NULL;

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_PLAYER_COMPLETED_PROJECT);
    stmt->setUInt32(0, guid);
    stmt->setUInt32(1, projectId);
    stmt->setUInt32(2, count);
    stmt->setUInt32(3, currTime);

    trans->Append(stmt);

    CharacterDatabase.CommitTransaction(trans);
}

void ArcheologyMgr::UpdateCompletedProjectsCount(uint32 guid, uint32 projectId)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_PLAYER_COMPLETED_PROJECT_COUNT);

    stmt->setUInt32(0, GetCompletedProjectsCount(guid, projectId) + 1);
    stmt->setUInt32(1, guid);
    stmt->setUInt32(2, projectId);

    CharacterDatabase.Execute(stmt);
}

void ArcheologyMgr::_loadCompletedProjects()
{
    PreparedStatement* stmt = NULL;
    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_PLAYER_COMPLETED_PROJECT);
    stmt->setUInt32(0, m_player->GetGUIDLow());
    PreparedQueryResult projectsResult = CharacterDatabase.Query(stmt);

    if(projectsResult && projectsResult->GetRowCount() > 0)
    {
        do
        {
            Field* row = projectsResult->Fetch();
            uint32 projectId = row[0].GetUInt32();

            m_completedProjects.push_back(projectId);
        }
        while(projectsResult->NextRow());
    }
}

uint32 ArcheologyMgr::GetCompletedProjectsCount(uint32 guid, uint32 projectId)
{
    PreparedStatement* stmt = NULL;
    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_PLAYER_COMPLETED_PROJECT_COUNT);
    stmt->setUInt32(0, guid);
    stmt->setUInt32(1, projectId);
    PreparedQueryResult projectsResult = CharacterDatabase.Query(stmt);

    if(projectsResult && projectsResult->GetRowCount() > 0)
    {
        do
        {
            Field* row = projectsResult->Fetch();
            uint32 count = row[0].GetUInt32();

            return count;
        }
        while(projectsResult->NextRow());
    }
    else return 0;
}

uint32 ArcheologyMgr::GetCompletedProjectsTime(uint32 guid, uint32 projectId)
{
    PreparedStatement *stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_PLAYER_COMPLETED_PROJECT_TIME);
    stmt->setUInt32(0, guid);
    stmt->setUInt32(1, projectId);
    PreparedQueryResult result = CharacterDatabase.Query(stmt);
    if (result) //load
    {
        Field* fields = result->Fetch();
        uint32 complete_time = fields[0].GetUInt32();
        return complete_time;
    }
    else
        return 0;
}
