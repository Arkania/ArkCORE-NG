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

#include "SharedDefines.h"
#include "ArchaeologyMgr.h"
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
void ArchaeologyMgr::Initialize()
{
    //if (!m_isDigsiteInitialized)
    //    ASSERT(false);

    LoadCharacterDigsite();
    LoadProjects();

    UpdatePlayerFieldsResearchSite();
    UpdatePlayerFieldsResearching();
}

void ArchaeologyMgr::RemovePlayerProfession()
{
    SQLTransaction trans = CharacterDatabase.BeginTransaction();
    PreparedStatement* stmt = nullptr;

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_PLAYER_SURVEY_DATA);
    stmt->setUInt32(0, m_player->GetGUIDLow());
    trans->Append(stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_PLAYER_CURRENT_DATA);
    stmt->setUInt32(0, m_player->GetGUIDLow());
    trans->Append(stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_PLAYER_COMPLETE_DATA);
    stmt->setUInt32(0, m_player->GetGUIDLow());
    trans->Append(stmt);

    for (uint16 slot = 0; slot < MAX_RESEARCH_PROJECTS; slot++)
    {
        m_player->SetUInt16Value(PLAYER_FIELD_RESERACH_SITE_1 + slot, 0, 0);
        m_player->SetUInt16Value(PLAYER_FIELD_RESEARCHING_1 + slot, 0, 0);
        m_player->RemoveFlag(PLAYER_TRACK_RESOURCES, uint32(1) << (22 - 1));
        if (uint16 branchId = GetBranchId(slot))
            if (uint16 currency = GetArchaeologyCurrency(branchId))
                m_player->SetCurrency(currency, 0);
    }

    CharacterDatabase.CommitTransaction(trans);
}

/******************************* called from core *********************************/

uint32 ArchaeologyMgr::OnSurveyBotActivated(sCharacterDigsite* &cd, uint16 &pos, float &dist, float &orientation)
{
    if (!m_player->HasSkill(SKILL_ARCHAEOLOGY))
        return 0;

    if (FindNearestDigsite(cd, pos, dist, orientation))
    {
        if (dist > ARCHAEOLOGY_DIG_SITE_FAR_DIST)
        {
            m_player->GetSession()->SendNotification(LANG_COMMAND_TARGETOBJNOTFOUND);
            return 0;
        }
        else if (dist <= ARCHAEOLOGY_DIG_SITE_FAR_DIST && dist > ARCHAEOLOGY_DIG_SITE_MED_DIST) // Red 80-50y
            return ARCHAEOLOGY_DIG_SITE_FAR_SURVEYBOT;
        else if (dist <= ARCHAEOLOGY_DIG_SITE_MED_DIST && dist > ARCHAEOLOGY_DIG_SITE_CLOSE_DIST) // Yellow 50-20y
            return ARCHAEOLOGY_DIG_SITE_MEDIUM_SURVEYBOT;
        else if (dist <= ARCHAEOLOGY_DIG_SITE_CLOSE_DIST && dist > ARCHAEOLOGY_DIG_SITE_FIND_DIST) // Green 20-5y
            return ARCHAEOLOGY_DIG_SITE_CLOSE_SURVEYBOT;
        else if (dist <= ARCHAEOLOGY_DIG_SITE_FIND_DIST) // Found it!
        {
            uint8 race = m_player->getRace();
            uint16 branchId = cd->digsite.branchId;
            uint16 slot = GetBranchIndex(branchId);

            if (race == RACE_DWARF)
                m_player->ModifyCurrency(cd->GetArchaeologyCurrency(), urand(6, 10));
            else
                m_player->ModifyCurrency(cd->GetArchaeologyCurrency(), urand(5, 9));

            uint32 go = cd->GetArchaeologyLootGO();
            if (cd->counter_digsite < 6)
                cd->counter_digsite++;
            if (cd->positions[pos].count > 0)
                cd->positions[pos].count--;
            cd->time_digged = time(NULL);
            cd->isChanged = true;

            if (currentProjects[slot].projectId == 0)
                UpdateCurrentProjects();

            UpdateCharacterDigsite();

            return go;
        }
    }
    return 0;
}

void ArchaeologyMgr::SaveDigsitesToDB()
{
    if (!m_isDigsiteChanged)
        return;

    TC_LOG_ERROR("misc", "ArchaeologyMgr::SaveDigsitesToDB has Data to save to DB. Should not heappen.");
}

bool ArchaeologyMgr::CompleteArtifact(uint32 spellId, ByteBuffer &data)
{
    sCurrentProject curP = FindCurrentProjects(spellId);
    if (curP.branchId && curP.projectId)
    {
        uint32 target_mask, unk1;
        uint16 curId, unk7;
        uint8 unk2, unk4, unk5, reqFragments;
        data >> target_mask >> unk1 >> unk2 >> curId >> unk4 >> unk5 >> reqFragments >> unk7;
                
        uint32 numberOfStones = 0;
        uint32 currencyId = curP.currencyId;
        uint32 keyStoneId = curP.keyStoneId;
        uint32 currencySale = 0;

        if (!(unk1 == 1 && unk2 == 1 && unk4 == 0 && unk5 == 0 && unk7 == 0))
            TC_LOG_ERROR("misc", "ArchaeologyMgr::CompleteArtifact found opcode data: unk1: %u, unk2: %u, unk4: %u, unk5: %u, unk7: %u, spellId: %u, branchId: %u, projectId: %u \n", unk1, unk2, unk4, unk5, unk7, spellId, curP.branchId, curP.projectId);

        if (numberOfStones > 0)
        {
            if (m_player->HasItemCount(keyStoneId, numberOfStones, false))
                currencySale = 12 * numberOfStones;
        }

        int32 bp0 = int32(numberOfStones);

        if (currencyId)
        {
            uint32 fragments = m_player->GetCurrency(currencyId, true);
            if (fragments >= reqFragments - currencySale)
            {
                m_player->CastCustomSpell(m_player, curP.spellId, &bp0, NULL, NULL, false);
                sCompletedProject comP = FindCompletedProjects(curP.projectId);
                if (!comP.projectId) // not in the list.
                {
                    comP.projectId = curP.projectId;
                    comP.counter_completed = 1;
                    comP.timeFirst = time(NULL);
                    comP.timeLast = time(NULL);
                    completedProjects.push_back(comP);
                }
                else
                    comP.counter_completed += 1;

                comP.SaveCompletedProjectToDB(m_player->GetGUIDLow());
                return true;
            }
        }
    }

    return false;
}

void ArchaeologyMgr::EffectOnCreateItem(uint32 spellId, int32 &damage)
{
    sCurrentProject curProject = FindCurrentProjects(spellId);
    if (curProject.branchId)
    {
        uint16 slot = GetBranchIndex(curProject.branchId);
        int32 reqFragments = curProject.reqFragments;

        if (damage)
        {
            
            // why can the item or keystone be damaged ???

            damage = 0;
        }

        // Send research complete opcode.
        WorldPacket completed(SMSG_RESEARCH_COMPLETE, 12);
        uint32 unk0 = 0; // I have my theory that the second must be onRare, but I'm not quite sure.
        completed << uint32(curProject.branchId) << uint32(unk0) << uint32(curProject.projectId);
        m_player->GetSession()->SendPacket(&completed);

        m_player->ModifyCurrency(curProject.currencyId, -(reqFragments));
        GenerateCurrentProject(curProject.branchId, true, curProject.spellId);
    }
}

sCurrentProject ArchaeologyMgr::FindCurrentProjects(uint32 spellId)
{
    sCurrentProject cp;
    cp.Clear();

    if (!spellId)
        return cp;

    for (uint16 slot = 0; slot < 10; slot++)
    {
        if (currentProjects[slot].spellId == spellId)
            return currentProjects[slot];
    }

    return cp;
}

float ArchaeologyMgr::GetOrientationWithDeviation(float dist, float orientation)
{
    if (dist < 5.0f)
        return orientation;

    float max = M_PI * 2;
    float maxDeviation = (M_PI / 180.0f) * dist;
    float rndDeviation = frand(maxDeviation / 5, maxDeviation) / 2;
    float newOrientation = orientation;
    if (urand(0, 1))
        newOrientation -= rndDeviation;
    else
        newOrientation += rndDeviation;

    if (newOrientation > max)
        newOrientation -= max;
    if (newOrientation < 0)
        newOrientation += max;

    return newOrientation;
}

/****************************** called from archaeologyMgr *******************************/

/** digsite handling **/

void ArchaeologyMgr::LoadCharacterDigsite()
{
    if (m_isDigsiteInitialized)
        return;

    m_isDigsiteInitialized = true;
    m_isDigsiteChanged = false;
    uint32 guid = m_player->GetGUIDLow();

    for (uint16 i = 0; i < MAX_RESEARCH_SITES; i++)
        m_characterDigsite[i].Clear();

    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_PLAYER_DIGGING_ALL);
    stmt->setUInt32(0, guid);
    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (result && result->GetRowCount() > 0)
    {
        do
        {
            Field* fields = result->Fetch();

            uint16 slot = fields[0].GetUInt16();
            m_characterDigsite[slot].guid = guid;
            m_characterDigsite[slot].CreateFromDB(fields);
        } 
        while (result->NextRow());
    }
    UpdateCharacterDigsite();
    SaveCharacterDigsite();
}

void ArchaeologyMgr::UpdateCharacterDigsite()
{
    bool changed = false;
    for (uint16 slot = 0; slot < GetMaxDigsite(); slot++)
    {
        sCharacterDigsite* cd = &m_characterDigsite[slot];
        if (cd->entry == 0)
            cd = CreateNewRandomDigsite(slot);

        if (cd->counter_digsite >= 6)
            if ((time(NULL) - cd->time_digged) > 1800) // 30 min cooldown.
                cd = CreateNewRandomDigsite(slot);

        if (cd->isChanged)
            cd->UpdateToDB(m_player->GetGUIDLow());

        m_characterDigsite[slot] = *cd;
    }
    UpdatePlayerFieldsResearchSite();
}

void ArchaeologyMgr::SaveCharacterDigsite()
{
    if (!m_isDigsiteChanged)
        return;
    
    m_isDigsiteChanged = false;



}

sCharacterDigsite* ArchaeologyMgr::CreateNewRandomDigsite(uint16 slot)
{
    sCharacterDigsite* cd = new sCharacterDigsite();
    cd->slot = slot;
    cd->time_digged = time(0);
    cd->counter_digsite = 0;
    std::vector<sWorldDigsiteTemplate> myDList = GetListOfAllowedNotUsedDigsiteTemplates(slot);
    sWorldDigsiteTemplate wdt = myDList[urand(0, myDList.size() - 1)];
    cd->entry = wdt.entry;
    cd->digsite = wdt;
    std::vector<sWorldPositionTemplate> myPList = GetListOfDigsitePositions(cd->entry);
    FillRandomArtifactPos(myPList, cd);
    cd->isChanged = true;
    return cd;
}

void ArchaeologyMgr::UpdatePlayerFieldsResearchSite()
{
    if (m_player->HasSkill(SKILL_ARCHAEOLOGY))
        for (uint16 slot = 0; slot < MAX_RESEARCH_SITES; slot++)
            UpdatePlayerFieldsResearchSite(slot);
}

void ArchaeologyMgr::UpdatePlayerFieldsResearchSite(uint16 slot)
{
    if (slot < GetMaxDigsite())
    {
        if (m_characterDigsite[slot].counter_digsite < 6)
            m_player->SetUInt16Value(PLAYER_FIELD_RESERACH_SITE_1 + slot, 0, m_characterDigsite[slot].entry);
        else
            m_player->SetUInt16Value(PLAYER_FIELD_RESERACH_SITE_1 + slot, 0, 0);
    }
    else
    {
        m_player->SetUInt16Value(PLAYER_FIELD_RESERACH_SITE_1 + slot, 0, 0);
    }
}

void ArchaeologyMgr::FillRandomArtifactPos(std::vector<sWorldPositionTemplate> posList, sCharacterDigsite* &digsite)
{
    uint8 a = 4;
    uint8 b = 4;
    uint8 c = 4;

    while ((a + b + c) > 6)
    {
        switch (urand(1, 3))
        {
        case 1:
            if (a > 1)
                a--;
            break;
        case 2:
            if (b > 1)
                b--;
            break;
        case 3:
            if (c > 1)
                c--;
            break;
        }
    }
    if (posList.size() == 0)
    {
        return;
    }
    else if (posList.size() == 1)
    {
        
        digsite->positions[0] = posList[0];
        digsite->positions[0].count = a ;
        return;
    }
    else if (posList.size() == 2)
    {
        digsite->positions[0] = posList[0];
        digsite->positions[1] = posList[1];
        digsite->positions[0].count  = a;
        digsite->positions[1].count  = b;
        return;
    }
    else if (posList.size() == 3)
    {
        digsite->positions[0] = posList[0];
        digsite->positions[1] = posList[1];
        digsite->positions[2] = posList[2];
        digsite->positions[0].count = a;
        digsite->positions[1].count = b;
        digsite->positions[2].count = c;
        return;
    }
    uint8 rol = urand(0, posList.size() - 1);
    digsite->positions[0] = posList[rol];
    do
    {
        rol = urand(0, posList.size() - 1);
        digsite->positions[1] = posList[rol];
    } while (digsite->positions[0].id == digsite->positions[1].id);
    do
    {
        rol = urand(0, posList.size() - 1);
        digsite->positions[2] = posList[rol];
    } while (digsite->positions[0].id == digsite->positions[2].id || digsite->positions[1].id == digsite->positions[2].id);
    digsite->positions[0].count = a;
    digsite->positions[1].count = b;
    digsite->positions[2].count = c;
}

uint16 ArchaeologyMgr::GetMaxDigsite()
{
    if (uint16 skill = m_player->GetSkillValue(SKILL_ARCHAEOLOGY))
    {
        if (skill <= 275)
            return 8;
        else if (skill > 275 && skill <= 350)
            return 12;
        else
            return MAX_RESEARCH_SITES;
    }

    return 0;
}

int16 ArchaeologyMgr::GetMap(uint8 id)
{
    switch (id)
    {
    case 0:
        return MAP_EASTERN_KINGDOMS;
    case 1:
        return MAP_KALIMDOR;
    case 2:
        return MAP_OUTLAND;
    case 3:
        return MAP_NORTHREND;
    }
    return MAP_UNKNOWN;
}

uint16 ArchaeologyMgr::GetArchaeologyMap(uint16 slot)
{
    return GetMap(slot / 4);
}

int16 ArchaeologyMgr::GetBranchIndex(uint8 branchId)
{
    switch (branchId)
    {
    case ARCHAEOLOGY_BRANCH_DWARF:
        return ARCHAEOLOGY_INDEX_DWARF;
    case ARCHAEOLOGY_BRANCH_DRAENEI:
        return ARCHAEOLOGY_INDEX_DRAENEI;
    case ARCHAEOLOGY_BRANCH_FOSSIL:
        return ARCHAEOLOGY_INDEX_FOSSIL;
    case ARCHAEOLOGY_BRANCH_NIGHT_ELF:
        return ARCHAEOLOGY_INDEX_NIGHT_ELF;
    case ARCHAEOLOGY_BRANCH_NERUBIAN:
        return ARCHAEOLOGY_INDEX_NERUBIAN;
    case ARCHAEOLOGY_BRANCH_ORC:
        return ARCHAEOLOGY_INDEX_ORC;
    case ARCHAEOLOGY_BRANCH_TOLVIR:
        return ARCHAEOLOGY_INDEX_TOLVIR;
    case ARCHAEOLOGY_BRANCH_TROLL:
        return ARCHAEOLOGY_INDEX_TROLL;
    case ARCHAEOLOGY_BRANCH_VRYKUL:
        return ARCHAEOLOGY_INDEX_VRYKUL;
    case ARCHAEOLOGY_BRANCH_TEST:
        return ARCHAEOLOGY_INDEX_TEST;
    }
    return -1;
}

uint16 ArchaeologyMgr::GetBranchId(uint8 index)
{
    switch (index)
    {
    case ARCHAEOLOGY_INDEX_DWARF:
        return ARCHAEOLOGY_BRANCH_DWARF;
    case ARCHAEOLOGY_INDEX_DRAENEI:
        return ARCHAEOLOGY_BRANCH_DRAENEI;
    case ARCHAEOLOGY_INDEX_FOSSIL:
        return ARCHAEOLOGY_BRANCH_FOSSIL;
    case ARCHAEOLOGY_INDEX_NIGHT_ELF:
        return ARCHAEOLOGY_BRANCH_NIGHT_ELF;
    case ARCHAEOLOGY_INDEX_NERUBIAN:
        return ARCHAEOLOGY_BRANCH_NERUBIAN;
    case ARCHAEOLOGY_INDEX_ORC:
        return ARCHAEOLOGY_BRANCH_ORC;
    case ARCHAEOLOGY_INDEX_TOLVIR:
        return ARCHAEOLOGY_BRANCH_TOLVIR;
    case ARCHAEOLOGY_INDEX_TROLL:
        return ARCHAEOLOGY_BRANCH_TROLL;
    case ARCHAEOLOGY_INDEX_VRYKUL:
        return ARCHAEOLOGY_BRANCH_VRYKUL;
    case ARCHAEOLOGY_INDEX_TEST:
        return ARCHAEOLOGY_BRANCH_TEST;
    }
    return 0;
}

uint16 ArchaeologyMgr::GetArchaeologyCurrency(uint8 branchId)
{
    switch (branchId)
    {
    case ARCHAEOLOGY_BRANCH_DWARF:
        return CURRENCY_TYPE_DWARF_FRAGMENT;
    case ARCHAEOLOGY_BRANCH_DRAENEI:
        return CURRENCY_TYPE_DRAENEI_FRAGMENT;
    case ARCHAEOLOGY_BRANCH_FOSSIL:
        return CURRENCY_TYPE_FOSSIL_FRAGMENT;
    case ARCHAEOLOGY_BRANCH_NIGHT_ELF:
        return CURRENCY_TYPE_NIGHT_ELF_FRAGMENT;
    case ARCHAEOLOGY_BRANCH_NERUBIAN:
        return CURRENCY_TYPE_NERUBIAN_FRAGMENT;
    case ARCHAEOLOGY_BRANCH_ORC:
        return CURRENCY_TYPE_ORC_FRAGMENT;
    case ARCHAEOLOGY_BRANCH_TOLVIR:
        return CURRENCY_TYPE_TOLVIR_FRAGMENT;
    case ARCHAEOLOGY_BRANCH_TROLL:
        return CURRENCY_TYPE_TROLL_FRAGMENT;
    case ARCHAEOLOGY_BRANCH_VRYKUL:
        return CURRENCY_TYPE_VRYKUL_FRAGMENT;
    }
    return 0;
}

uint16 ArchaeologyMgr::GetArchaeologyKeyStone(uint8 branchId)
{
    switch (branchId)
    {
    case ARCHAEOLOGY_BRANCH_DWARF:
        return ARCHAEOLOGY_STONE_DWARF;
    case ARCHAEOLOGY_BRANCH_DRAENEI:
        return ARCHAEOLOGY_STONE_DRAENEI;
    case ARCHAEOLOGY_BRANCH_FOSSIL:
        return ARCHAEOLOGY_STONE_FOSSIL;
    case ARCHAEOLOGY_BRANCH_NIGHT_ELF:
        return ARCHAEOLOGY_STONE_NIGHT_ELF;
    case ARCHAEOLOGY_BRANCH_NERUBIAN:
        return ARCHAEOLOGY_STONE_NERUBIAN;
    case ARCHAEOLOGY_BRANCH_ORC:
        return ARCHAEOLOGY_STONE_ORC;
    case ARCHAEOLOGY_BRANCH_TOLVIR:
        return ARCHAEOLOGY_STONE_TOLVIR;
    case ARCHAEOLOGY_BRANCH_TROLL:
        return ARCHAEOLOGY_STONE_TROLL;
    case ARCHAEOLOGY_BRANCH_VRYKUL:
        return ARCHAEOLOGY_STONE_VRYKUL;
    }
    return 0;
}

uint32 ArchaeologyMgr::GetArchaeologyLootGO(uint8 branchId)
{
    switch (branchId)
    {
    case 1:
        return ARCHAEOLOGY_FIND_DWARF;
    case 2:
        return ARCHAEOLOGY_FIND_DRAENEI;
    case 3:
        return ARCHAEOLOGY_FIND_FOSSIL;
    case 4:
        return ARCHAEOLOGY_FIND_NIGHT_ELF;
    case 5:
        return ARCHAEOLOGY_FIND_NERUBIAN;
    case 6:
        return ARCHAEOLOGY_FIND_ORC;
    case 7:
        return ARCHAEOLOGY_FIND_TOLVIR;
    case 8:
        return ARCHAEOLOGY_FIND_TROLL;
    case 27:
        return ARCHAEOLOGY_FIND_VRYKUL;
    }
    return 0;
}

std::vector<sWorldDigsiteTemplate> ArchaeologyMgr::GetListOfAllowedNotUsedDigsiteTemplates(uint16 slot)
{
    std::vector<sWorldDigsiteTemplate> myList;

    PreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_DIGSITE_ENTRY_MAP);

    stmt->setUInt16(0, m_player->getLevel());
    stmt->setUInt16(1, GetArchaeologyMap(slot));

    PreparedQueryResult result = WorldDatabase.Query(stmt);

    if (result && result->GetRowCount() > 0)
    {
        do
        {
            Field* fields = result->Fetch();
            sWorldDigsiteTemplate wdt;
            wdt.CreateFromDB(fields);
            if (IsAllowedDigsite(wdt))
                myList.push_back(wdt);            
        }
        while (result->NextRow());
    }

    return myList;
}

bool ArchaeologyMgr::IsAllowedDigsite(sWorldDigsiteTemplate digsite)
{
    for (uint16 slot = 0; slot < GetMaxDigsite(); slot++)
    {
        if (m_characterDigsite[slot].entry == digsite.entry)
            return false;
    }

    return true;
}

std::vector<sWorldPositionTemplate> ArchaeologyMgr::GetListOfDigsitePositions(uint16 entry)
{
    std::vector<sWorldPositionTemplate> myList;

    PreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_POSITION_ID);
    stmt->setUInt16(0, entry);
    PreparedQueryResult result = WorldDatabase.Query(stmt);

    if (result && result->GetRowCount() > 0)
        do
        {
            Field* fields = result->Fetch();

            sWorldPositionTemplate wpt;
            wpt.CreateFromDB(fields);
            myList.push_back(wpt);

        } 
        while (result->NextRow());

        return myList;
}

bool ArchaeologyMgr::FindNearestDigsite(sCharacterDigsite* &digsite, uint16 &pos, float &distance2D, float &orientation)
{
    uint16 map = m_player->GetMapId();
    uint16 area = m_player->GetAreaId();
    uint16 zone = m_player->GetZoneId();

    float dist = 2000.0f;
    bool inside = false;

    for (uint16 slot = 0; slot < GetMaxDigsite(); slot++)
    {
        sCharacterDigsite* cd = &m_characterDigsite[slot];
        if (cd->entry>0 && cd->digsite.mapId == map && (cd->digsite.areaId == area || cd->digsite.areaId == zone))
        {
            inside = true;
            if (cd->counter_digsite < 6)
                for (uint8 i = 0; i < 3; i++)
                    if (cd->positions[i].count > 0)
                    {
                        float d = cd->positions[i].GetDistance2D(m_player);
                        if (d < dist)
                        {
                            digsite = cd;
                            pos = i;
                            dist = d;
                            distance2D = d;
                            orientation = cd->positions[i].GetOrientation(m_player);
                        }
                    }
        }
    }

    return inside;  
}

/** current project handling **/

void ArchaeologyMgr::LoadProjects()
{
    if (m_isProjectsInitialized)
        return;

    m_isProjectsInitialized = true;

    LoadCompletedProjects();
    LoadCurrentProjects();

    m_isProjectChanged = false;
}

void ArchaeologyMgr::LoadCurrentProjects()
{
    InitCurrentProjects();
    m_isProjectChanged = false;

    PreparedStatement* stmt = nullptr;
    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_PLAYER_CURRENT_PROJECT);
    stmt->setUInt32(0, m_player->GetGUIDLow());
    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (result && result->GetRowCount() > 0)
    {
        do
        {
            Field* fields = result->Fetch();
           
            sCurrentProject curP;
            curP.CreateFromDB(fields);
            curP.currencyId = GetArchaeologyCurrency(curP.branchId);
            curP.keyStoneId = GetArchaeologyKeyStone(curP.branchId);
            
            currentProjects[GetBranchIndex(curP.branchId)] = curP;
        }
        while (result->NextRow());
    }
    UpdateCurrentProjects();
}

void ArchaeologyMgr::UpdateCurrentProjects()
{
    for (uint16 slot = 0; slot < MAX_RESEARCH_PROJECTS; slot++)
        if (uint16 branchId = GetBranchId(slot))
        {
            uint32 fragments = m_player->GetCurrency(GetArchaeologyCurrency(branchId), true);
            if (fragments && !currentProjects[slot].projectId)
                GenerateCurrentProject(branchId, false, 0);
        }

    UpdatePlayerFieldsResearching();
}

void ArchaeologyMgr::InitCurrentProjects()
{
    for (uint16 slot = 0; slot < MAX_RESEARCH_PROJECTS; slot++)
        currentProjects[slot].Clear();
}

void ArchaeologyMgr::SaveCurrentProjects()
{
    if (!m_isProjectChanged)
        return;

    SQLTransaction trans = CharacterDatabase.BeginTransaction();
    PreparedStatement* stmt = nullptr;

    for (uint16 slot = 0; slot < MAX_RESEARCH_PROJECTS; slot++)
    {
        if (currentProjects[slot].projectId)
        {
            stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_PLAYER_CURRENT_PROJECT);
            stmt->setUInt32(0, m_player->GetGUIDLow());
            stmt->setUInt16(1, currentProjects[slot].branchId);

            trans->Append(stmt);
            
            stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_PLAYER_CURRENT_PROJECT);
            stmt->setUInt32(0, m_player->GetGUIDLow());
            stmt->setUInt16(1, currentProjects[slot].branchId);
            stmt->setUInt16(2, currentProjects[slot].projectId);

            trans->Append(stmt);
        }
    }

    CharacterDatabase.CommitTransaction(trans);

    m_isProjectChanged = false;
}

void ArchaeologyMgr::GenerateCurrentProject(uint32 branchId, bool force, uint32 excludeSpellId)
{
    uint16 slot = GetBranchIndex(branchId);
    if (currentProjects[slot].projectId != 0 && !force)
        return;

    // Remove old
    if (force)
    {
        currentProjects[slot].projectId = 0;
        m_isProjectChanged = true;
    }

    std::vector<uint32> projectList = GetResearchProjectList(branchId, excludeSpellId);
    if (projectList.size() == 0)
    {
        TC_LOG_INFO("server.loading", "Size of ResearchProjectList is = 0!");
        return;
    }

    sCurrentProject cup;
    cup.branchId = branchId;
    cup.projectId = projectList[urand(0, projectList.size() - 1)];
    cup.currencyId = GetArchaeologyCurrency(branchId);
    cup.keyStoneId = GetArchaeologyKeyStone(branchId);
    cup.InsertDbcValues();
    currentProjects[slot] = cup;
    currentProjects[slot].SaveToDB(m_player->GetGUIDLow());
    UpdatePlayerFieldsResearching(slot);
}

/** completed project handling **/

void ArchaeologyMgr::LoadCompletedProjects()
{
    completedProjects.clear();

    PreparedStatement* stmt = nullptr;
    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_PLAYER_COMPLETED_PROJECT);
    stmt->setUInt32(0, m_player->GetGUIDLow());
    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (result && result->GetRowCount() > 0)
    {
        do
        {
            Field* fields = result->Fetch();            
            sCompletedProject cp;
            cp.CreateFromDB(fields);
            completedProjects.push_back(cp);
        } 
        while (result->NextRow());
    }
}

void ArchaeologyMgr::UpdatePlayerFieldsResearching()
{
    for (uint8 slot = 0; slot < MAX_RESEARCH_PROJECTS; slot++)
        UpdatePlayerFieldsResearching(slot);
}

void ArchaeologyMgr::UpdatePlayerFieldsResearching(uint16 slot)
{
    if (uint16 branchId = GetBranchId(slot))
    {
        sCurrentProject curP = currentProjects[slot];
        uint32 fragments = m_player->GetCurrency(curP.currencyId, true);
        if (fragments > 0)
            if (currentProjects[slot].projectId)
                m_player->SetUInt16Value(PLAYER_FIELD_RESEARCHING_1 + slot, 0, currentProjects[slot].projectId);
            else
                m_player->SetUInt16Value(PLAYER_FIELD_RESEARCHING_1 + slot, 0, 0);
    }
}

std::vector<uint32> ArchaeologyMgr::GetResearchProjectList(uint16 branchId, uint16 excludeSpellId)
{
    uint16 skill_value = m_player->GetSkillValue(SKILL_ARCHAEOLOGY);
    uint16 skill_complexity = skill_value / 75;
    uint16 fragments = m_player->GetCurrency(GetArchaeologyCurrency(branchId), true);
    std::vector<uint32> projectList;

    for (uint32 row = 0; row < sResearchProjectStore.GetNumRows(); row++)
    {
        ResearchProjectEntry* rs = sResearchProjectStore.LookupRow(row);
        if (!rs)
            continue;

        if (rs->ResearchBranchID != branchId)
            continue;

        if (excludeSpellId)
            if (rs->ProjectSpell == excludeSpellId)
                continue;

        if (rs->Complexity > skill_complexity)
            continue;

        projectList.push_back(rs->ID);
    }
    return projectList;
}

sCompletedProject ArchaeologyMgr::FindCompletedProjects(uint16 projectId)
{
    sCompletedProject cp;
    cp.Clear();

    if (!projectId)
        return cp;

    for (std::vector<sCompletedProject>::iterator itr = completedProjects.begin(); itr != completedProjects.end(); ++itr)
        if (itr->projectId == projectId)
            return *itr;

    return cp;
}

/****************************** struct WorldPositionTemplate **************************/

void sWorldPositionTemplate::Clear()
{
    entry       = 0;
    id          = 0;
    position_X  = 0;
    position_Y  = 0;
    count       = 0;
}

void sWorldPositionTemplate::CreateFromDB(Field* fields)
{
    entry       = fields[0].GetUInt16();
    id          = fields[1].GetUInt16();
    position_X  = fields[2].GetFloat();
    position_Y  = fields[3].GetFloat();
}

void sWorldPositionTemplate::LoadFromDB(uint16 entry, uint16 id)
{
    PreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_POSITION_ENTRY);
    stmt->setUInt16(0, entry);
    stmt->setUInt16(1, id);
    PreparedQueryResult result = WorldDatabase.Query(stmt);

    if (result && result->GetRowCount() > 0)
    {
        Field* fields = result->Fetch();
        CreateFromDB(fields);
    }
    else
        Clear();

}

sWorldPositionTemplate sWorldPositionTemplate::GetPositionTemplate(uint16 entry, uint16 id)
{
    sWorldPositionTemplate pos;
    pos.LoadFromDB(entry, id);
    return pos;
}

std::vector<sWorldPositionTemplate> sWorldPositionTemplate::GetPositionTemplates(uint16 entry)
{
    std::vector<sWorldPositionTemplate> myList;

    PreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_POSITION_ID);
    stmt->setUInt16(0, entry);
    PreparedQueryResult result = WorldDatabase.Query(stmt);

    if (!result || !result->GetRowCount())
        return myList;

    do
    {
        Field* fields = result->Fetch();

        sWorldPositionTemplate pos;
        pos.CreateFromDB(fields);
        myList.push_back(pos);

    } while (result->NextRow());

    return myList;
}

float sWorldPositionTemplate::GetDistance2D(Player* player)
{
    return player->GetDistance2d(position_X, position_Y);
}

float sWorldPositionTemplate::GetOrientation(Player* player)
{
    return player->GetAngle(position_X, position_Y);
}

/****************************** struct WorldDigsiteTemplate***********************************/

void sWorldDigsiteTemplate::Clear()
{
    entry       = 0;
    level       = 0;
    mapId       = 0;
    areaId      = 0;
    branchId    = 0;
}

void sWorldDigsiteTemplate::CreateFromDB(Field* fields)
{
    entry       = fields[0].GetUInt16();
    level       = fields[1].GetUInt16();
    mapId       = fields[2].GetUInt16();
    areaId      = fields[3].GetUInt16();
    branchId    = fields[4].GetUInt16();
}

void sWorldDigsiteTemplate::LoadFromDB(uint16 entry)
{
    PreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_DIGSITE_ENTRY);
    stmt->setUInt16(0, entry);
    PreparedQueryResult result = WorldDatabase.Query(stmt);

    if (result && result->GetRowCount() > 0)
    {
        Field* fields = result->Fetch();
        CreateFromDB(fields);
    }
    else
        Clear();
}

sWorldDigsiteTemplate sWorldDigsiteTemplate::GetDigsiteTemplate(uint16 entry)
{
    sWorldDigsiteTemplate wdt;
    wdt.LoadFromDB(entry);
    return wdt;
}

std::vector<sWorldDigsiteTemplate> sWorldDigsiteTemplate::GetDigsiteTemplates(uint16 entry, uint16 mapId)
{
    std::vector<sWorldDigsiteTemplate> myList;

    PreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_DIGSITE_ENTRY_MAP);
    stmt->setUInt16(0, entry);
    stmt->setUInt16(1, mapId);
    PreparedQueryResult result = WorldDatabase.Query(stmt);

    if (!result || !result->GetRowCount())
        return myList;

    do
    {
        Field* fields = result->Fetch();

        sWorldDigsiteTemplate site;
        site.CreateFromDB(fields);
        myList.push_back(site);

    } while (result->NextRow());

    return myList;
}

/****************************** struct CharacterDigsite *******************************/

void sCharacterDigsite::CreateFromDB(Field* fields)
{
    slot            = fields[0].GetUInt16();
    entry           = fields[1].GetUInt16();
    counter_digsite = fields[2].GetUInt16();
    time_digged     = fields[3].GetUInt32();
    uint16 point1   = fields[4].GetUInt16();
    uint16 count1   = fields[5].GetUInt16();
    uint16 point2   = fields[6].GetUInt16();
    uint16 count2   = fields[7].GetUInt16();
    uint16 point3   = fields[8].GetUInt16();
    uint16 count3   = fields[9].GetUInt16();
    digsite.LoadFromDB(entry);
    positions[0].LoadFromDB(entry, point1);
    positions[0].count = count1;
    positions[1].LoadFromDB(entry, point2);
    positions[1].count = count2;
    positions[2].LoadFromDB(entry, point3);
    positions[2].count = count3;
    isChanged = false;
}

void sCharacterDigsite::SaveToDB(uint32 guid, PreparedStatement* &stmt)
{
    stmt->setUInt16(0, slot);
    stmt->setUInt32(1, guid);
    stmt->setUInt16(2, entry);
    stmt->setUInt16(3, counter_digsite);
    stmt->setUInt32(4, time_digged);
    stmt->setUInt16(5, positions[0].id);
    stmt->setUInt16(6, positions[0].count);
    stmt->setUInt16(7, positions[1].id);
    stmt->setUInt16(8, positions[1].count);
    stmt->setUInt16(9, positions[2].id);
    stmt->setUInt16(10, positions[2].count);
    isChanged = false;
}

void sCharacterDigsite::UpdateToDB(uint32 guid)
{
    SQLTransaction trans = CharacterDatabase.BeginTransaction();
    PreparedStatement* stmt = nullptr;
    
    stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_PLAYER_DIGGING);
    stmt->setUInt16(0, slot);
    stmt->setUInt32(1, guid);
    trans->Append(stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_PLAYER_DIGGING);
    stmt->setUInt16(0, slot);
    stmt->setUInt32(1, guid);
    stmt->setUInt16(2, entry);
    stmt->setUInt16(3, counter_digsite);
    stmt->setUInt32(4, time_digged);
    stmt->setUInt16(5, positions[0].id);
    stmt->setUInt16(6, positions[0].count);
    stmt->setUInt16(7, positions[1].id);
    stmt->setUInt16(8, positions[1].count);
    stmt->setUInt16(9, positions[2].id);
    stmt->setUInt16(10, positions[2].count);
    trans->Append(stmt);

    CharacterDatabase.CommitTransaction(trans);

    isChanged = false;
}

void sCharacterDigsite::DeleteCharacterSlotFromDB(uint16 slot, uint32 guid, uint16 entry)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_PLAYER_DIGGING);

    stmt->setUInt16(0, slot);
    stmt->setUInt32(1, guid);
    stmt->setUInt16(2, entry);

    CharacterDatabase.Execute(stmt);
}

void sCharacterDigsite::DeleteCharacterFromDB(uint32 guid)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_PLAYER_DIGGING_ALL);
    stmt->setUInt32(0, guid);
    CharacterDatabase.Execute(stmt);
}

void sCharacterDigsite::Clear()
{
    slot            = 0;
    guid            = 0;
    entry           = 0;
    counter_digsite = 0;
    time_digged = time(NULL);
    digsite.Clear();
    positions[0].Clear();
    positions[1].Clear();
    positions[2].Clear();
    isChanged = false;
}

std::vector<sCharacterDigsite*> sCharacterDigsite::GetDigSites(uint32 guid)
{
    std::vector<sCharacterDigsite*> myList;

    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_PLAYER_DIGGING_ALL);
    stmt->setUInt32(0, guid);
    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (!result || !result->GetRowCount())
        return myList;

    do
    {
        Field* fields = result->Fetch();

        sCharacterDigsite* site = new sCharacterDigsite();
        site->guid = guid;
        site->CreateFromDB(fields);
        myList.push_back(site);

    } while (result->NextRow());

    return myList;
}

uint16 sCharacterDigsite::GetArchaeologyCurrency()
{
    switch (digsite.branchId)
    {
    case 1:
        return CURRENCY_TYPE_DWARF_FRAGMENT;
    case 2:
        return CURRENCY_TYPE_DRAENEI_FRAGMENT;
    case 3:
        return CURRENCY_TYPE_FOSSIL_FRAGMENT;
    case 4:
        return CURRENCY_TYPE_NIGHT_ELF_FRAGMENT;
    case 5:
        return CURRENCY_TYPE_NERUBIAN_FRAGMENT;
    case 6:
        return CURRENCY_TYPE_ORC_FRAGMENT;
    case 7:
        return CURRENCY_TYPE_TOLVIR_FRAGMENT;
    case 8:
        return CURRENCY_TYPE_TROLL_FRAGMENT;
    case 27:
        return CURRENCY_TYPE_VRYKUL_FRAGMENT;
    }
    return 0;
}

uint16 sCharacterDigsite::GetArchaeologyKeyStone()
{
    switch (digsite.branchId)
    {
    case 1:
        return ARCHAEOLOGY_STONE_DWARF;
    case 2:
        return ARCHAEOLOGY_STONE_DRAENEI;
    case 3:
        return ARCHAEOLOGY_STONE_FOSSIL;
    case 4:
        return ARCHAEOLOGY_STONE_NIGHT_ELF;
    case 5:
        return ARCHAEOLOGY_STONE_NERUBIAN;
    case 6:
        return ARCHAEOLOGY_STONE_ORC;
    case 7:
        return ARCHAEOLOGY_STONE_TOLVIR;
    case 8:
        return ARCHAEOLOGY_STONE_TROLL;
    case 27:
        return ARCHAEOLOGY_STONE_VRYKUL;
    }
    return 0;
}

uint32 sCharacterDigsite::GetArchaeologyLootGO()
{
    switch (digsite.branchId)
    {
    case 1:
        return ARCHAEOLOGY_FIND_DWARF;
    case 2:
        return ARCHAEOLOGY_FIND_DRAENEI;
    case 3:
        return ARCHAEOLOGY_FIND_FOSSIL;
    case 4:
        return ARCHAEOLOGY_FIND_NIGHT_ELF;
    case 5:
        return ARCHAEOLOGY_FIND_NERUBIAN;
    case 6:
        return ARCHAEOLOGY_FIND_ORC;
    case 7:
        return ARCHAEOLOGY_FIND_TOLVIR;
    case 8:
        return ARCHAEOLOGY_FIND_TROLL;
    case 27:
        return ARCHAEOLOGY_FIND_VRYKUL;
    }
    return 0;
}

float sCharacterDigsite::GetDistance2D(Player* player, uint8 index)
{
    return positions[index].GetDistance2D(player);
}

float sCharacterDigsite::GetOrientation(Player* player, uint8 index)
{
    return positions[index].GetOrientation(player);
}

/****************************** struct CurrentProject *******************************/

void sCurrentProject::CreateFromDB(Field* fields)
{
    this->branchId = fields[0].GetUInt16();
    this->projectId = fields[1].GetUInt16();
   
    if (projectId)
        if (ResearchProjectEntry* rp = sResearchProjectStore.LookupRow(projectId))
        {
            this->reqFragments = rp->RequiredFragments;
            this->spellId = rp->ProjectSpell; // kontrolle ob gleicher spell
            this->complexity = rp->Complexity;
        }
}

void sCurrentProject::DeleteFromDB(uint32 guid)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_PLAYER_CURRENT_PROJECT2);
    stmt->setUInt32(0, guid);
    stmt->setUInt16(1, branchId);
    stmt->setUInt16(2, projectId);
    CharacterDatabase.Execute(stmt);
}

void sCurrentProject::SaveToDB(uint32 guid)
{
    SQLTransaction trans = CharacterDatabase.BeginTransaction();
    PreparedStatement* stmt = nullptr;

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_PLAYER_CURRENT_PROJECT);
    stmt->setUInt32(0, guid);
    stmt->setUInt16(1, branchId);
    trans->Append(stmt);

    stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_PLAYER_CURRENT_PROJECT);
    stmt->setUInt32(0, guid);
    stmt->setUInt16(1, branchId);
    stmt->setUInt16(2, projectId);
    trans->Append(stmt);

    CharacterDatabase.CommitTransaction(trans);
}

void sCurrentProject::InsertDbcValues()
{
    ResearchProjectEntry* rp = sResearchProjectStore.LookupRow(projectId);
    if (rp)
    {
        this->reqFragments = rp->RequiredFragments;
        this->spellId = rp->ProjectSpell;
        this->complexity = rp->Complexity;
    }
}

void sCurrentProject::Clear()
{
    branchId     = 0;
    projectId    = 0;
    spellId      = 0;
    reqFragments = 0;
    complexity   = 0;
    currencyId   = 0;
    keyStoneId   = 0;
}

/****************************** struct CompletedProject *******************************/

void sCompletedProject::CreateFromDB(Field* fields)
{
    projectId           = fields[0].GetUInt16();
    counter_completed   = fields[1].GetUInt32();
    timeFirst           = fields[2].GetUInt32();
    timeLast            = fields[3].GetUInt32();
}

void sCompletedProject::Clear()
{
    projectId           = 0;
    counter_completed   = 0;
    timeFirst           = 0;
    timeLast            = 0;
}

void sCompletedProject::SaveCompletedProjectToDB(uint32 guid)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_REP_PLAYER_COMPLETED_PROJECT);

    stmt->setUInt32(0, guid);
    stmt->setUInt16(1, projectId);
    stmt->setUInt32(2, counter_completed);
    stmt->setUInt32(3, timeFirst);
    stmt->setUInt32(4, timeLast);

    CharacterDatabase.Execute(stmt);
}