
/*
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
*
* @File : sc_npc_teleport.cpp
* @Authors : Wilibald09
* @Date : 28/08/2008
* @Version : 1.2
*/

#include "ScriptPCH.h"
#include "sc_npc_teleport.h"
//#include "ProgressBar.h"

#define TELE    nsNpcTel::CatDest
#define PAGE    nsNpcTel::Page
#define PAGEI   PAGE::Instance


nsNpcTel::VCatDest nsNpcTel::TabCatDest;


uint32 PAGE::operator [] (Player * const player) const
{
    for (VInst_t i(0); i < m_TabInstance.size(); ++i)
    {
        if (m_TabInstance[i].GetPlayer() == player)
            return m_TabInstance[i].GetPageId();
    }
    return 0;
}

PAGE::Instance & PAGE::operator () (Player * const player)
{
    for (VInst_t i(0); i < m_TabInstance.size(); ++i)
    {
        if (m_TabInstance[i].GetPlayer() == player)
            return m_TabInstance[i];
    }
    m_TabInstance.push_back(Instance(player));
    return m_TabInstance.back();
}

PAGE::Instance & PAGEI::operator = (const uint32 &id)
{
    m_PageId = id;
    return *this;
}

PAGE::Instance & PAGEI::operator ++ (void)
{
    ++m_PageId;
    return *this;
}

PAGE::Instance PAGEI::operator ++ (int32)
{
    Instance tmp (*this);
    ++m_PageId;
    return tmp;
}

PAGE::Instance & PAGEI::operator -- (void)
{
    --m_PageId;
    return *this;
}

PAGE::Instance PAGEI::operator -- (int32)
{
    Instance tmp (*this);
    --m_PageId;
    return tmp;
}

TELE::CatDest(const CatValue cat, const CatName catname)
    : m_catvalue(cat), m_catname(catname)
{
    m_TabDest.clear();
}

std::string TELE::GetName(const uint8 loc /* = 0 */, const bool IsGM /* = false */) const
{
    std::string name = m_catname.name[loc];
    if (name.length() == 0)
        name = m_catname.name[0];

    if (!IsGM || m_catvalue.flag != FLAG_TEAM)
    {        
        return name;
    }
    
    switch (m_catvalue.data0)
    {
      case TEAM_HORDE:      return name + " (H)";
      case TEAM_ALLIANCE:   return name + " (A)";
    }
    return name;
}

bool TELE::IsAllowedToTeleport(Player * const player) const
{
    if (player->IsGameMaster())
    {
        if (m_catvalue.flag == FLAG_GMLEVEL)
            return player->GetSession()->GetSecurity() >= m_catvalue.data0;
        return true;
    }

    switch (m_catvalue.flag)
    {
    case FLAG_TEAM:
        switch (m_catvalue.data0)
        {
        case TEAM_HORDE:      return player->GetTeam() == HORDE;
        case TEAM_ALLIANCE:   return player->GetTeam() == ALLIANCE;
        case TEAM_ALL:        return true;
        }

    case FLAG_GUILD:
        return player->GetGuildId() == m_catvalue.data0;

    case FLAG_GMLEVEL:
        return player->GetSession()->GetSecurity() >= m_catvalue.data0;

    case FLAG_ISGM:
        return player->IsGameMaster();

    case FLAG_ACCOUNT:
        return player->GetSession()->GetAccountId() == m_catvalue.data0;

    case FLAG_LEVEL:
        return player->getLevel() >= m_catvalue.data0;

    case FLAG_ITEM:
        return player->HasItemCount(m_catvalue.data0, m_catvalue.data1, true);

    case FLAG_QUEST:
        if (m_catvalue.data1 < MAX_QUEST_STATUS)
            return player->GetQuestStatus(m_catvalue.data0) == m_catvalue.data1;
        return player->GetQuestRewardStatus(m_catvalue.data0);

    case FLAG_GENDER:
        return player->getGender() == m_catvalue.data0;

    case FLAG_RACE:
        return player->getRace() == m_catvalue.data0;

    case FLAG_CLASS:
        return player->getClass() == m_catvalue.data0;

    case FLAG_REPUTATION:
        return player->GetReputationRank(m_catvalue.data0) >= (int32)m_catvalue.data1;

    case FLAG_PLAYER:
        return player->GetGUID() == m_catvalue.data0;

    default: TC_LOG_ERROR("misc", "Invalid flag (category: %u). Important problem...", GetCatID());
    }

    TC_LOG_ERROR("misc", "Invalid flag (category: %u). Important problem...", GetCatID());
    return false;
}

uint32 TELE::CountOfCategoryAllowedBy(Player * const player)
{
    uint32 count(0);
    for (VCatDest_t i(0); i < TabCatDest.size(); ++i)
    {
        if (TabCatDest[i].IsAllowedToTeleport(player))
            ++count;
    }
    return count;
}

bool nsNpcTel::IsValidData(CatValue catvalue) //  const uint32 &cat, const Flag &flag, const uint64 &data0, const uint32 &data1
{
    switch (catvalue.flag)
    {
    case FLAG_TEAM:
        if (catvalue.data1)
            TC_LOG_ERROR("misc", "Invalid data1 (category: %u).", catvalue.catid);
        if (catvalue.data0 < MAX_FLAG_TEAM)
            return true;
        TC_LOG_ERROR("misc", "Invalid data0 (Team) (category: %u).", catvalue.catid);
        return false;

    case FLAG_GUILD:
        if (catvalue.data1)
            TC_LOG_ERROR("misc", "Invalid data1 (category: %u).", catvalue.catid);
        if (catvalue.data0)
            return true;
        TC_LOG_ERROR("misc", "Invalid data0 (GuildID) (category: %u).", catvalue.catid);
        return false;

    case FLAG_GMLEVEL:
        if (catvalue.data1)
            TC_LOG_ERROR("misc", "Invalid data1 (category: %u).", catvalue.catid);
        if (0 < catvalue.data0 && catvalue.data0 < 256)
            return true;
        TC_LOG_ERROR("misc", "Invalid data0 (GmLevel) (category: %u).", catvalue.catid);
        return false;

    case FLAG_ISGM:
        if (catvalue.data0)
            TC_LOG_ERROR("misc", "Invalid data0 (category: %u).", catvalue.catid);
        if (catvalue.data1)
            TC_LOG_ERROR("misc", "Invalid data1 (category: %u).", catvalue.catid);
        return true;

    case FLAG_ACCOUNT:
        if (catvalue.data1)
            TC_LOG_ERROR("misc", "Invalid data1 (category: %u).", catvalue.catid);
        if (catvalue.data0)
            return true;
        TC_LOG_ERROR("misc", "Invalid data0 (AccountID) (category: %u).", catvalue.catid);
        return false;

    case FLAG_LEVEL:
        if (catvalue.data1)
            TC_LOG_ERROR("misc", "Invalid data1 (category: %u).", catvalue.catid);
        if (0 < catvalue.data0 && catvalue.data0 < 256)
            return true;
        TC_LOG_ERROR("misc", "Invalid data0 (Level) (category: %u).", catvalue.catid);
        return false;

    case FLAG_ITEM:
        if (!catvalue.data0)
        {
            TC_LOG_ERROR("misc", "Invalid data0 (ItemID) (category: %u).", catvalue.catid);
            return false;
        }
        if (catvalue.data1)
            return true;
        TC_LOG_ERROR("misc", "Invalid data1 (Item Count) (category: %u).", catvalue.catid);
        return false;

    case FLAG_QUEST:
        if (!catvalue.data0)
        {
            TC_LOG_ERROR("misc", "Invalid data0 (QuestID) (category: %u).", catvalue.catid);
            return false;
        }
        if (catvalue.data1 < MAX_QUEST_STATUS + 1)
            return true;
        TC_LOG_ERROR("misc", "Invalid data1 (Quest Status) (category: %u).", catvalue.catid);
        return false;

    case FLAG_GENDER:
        if (catvalue.data1)
            TC_LOG_ERROR("misc", "Invalid data1 (category: %u).", catvalue.catid);
        if (catvalue.data0 < GENDER_NONE)
            return true;
        TC_LOG_ERROR("misc", "Invalid data0 (Gender) (category: %u).", catvalue.catid);
        return false;

    case FLAG_RACE:
        if (catvalue.data1)
            TC_LOG_ERROR("misc", "Invalid data1 (category: %u).", catvalue.catid);
        if (0 < catvalue.data0 && catvalue.data0 < MAX_RACES)
            return true;
        TC_LOG_ERROR("misc", "Invalid data0 (Race) (category: %u).", catvalue.catid);
        return false;

    case FLAG_CLASS:
        if (catvalue.data1)
            TC_LOG_ERROR("misc", "Invalid data1 (category: %u).", catvalue.catid);
        if (0 < catvalue.data0 && catvalue.data0 < MAX_CLASSES)
            return true;
        TC_LOG_ERROR("misc", "Invalid data0 (Class) (category: %u).", catvalue.catid);
        return false;

    case FLAG_REPUTATION:
        if (!catvalue.data0)
        {
            TC_LOG_ERROR("misc", "Invalid data0 (Faction/Reputation) (category: %u).", catvalue.catid);
            return false;
        }
        if (catvalue.data1 <= REP_EXALTED)
            return true;
        TC_LOG_ERROR("misc", "Invalid data1 (Faction/Reputation) (category: %u).", catvalue.catid);
        return false;

    case FLAG_PLAYER:
        if (catvalue.data1)
            TC_LOG_ERROR("misc", "Invalid data1 (category: %u).", catvalue.catid);
        if (catvalue.data0)
            return true;
        TC_LOG_ERROR("misc", "Invalid data0 (PlayerGuid) (category: %u).", catvalue.catid);
        return false;

    default: TC_LOG_ERROR("misc", "Invalid flag (category: %u).", catvalue.catid);
    }

    TC_LOG_ERROR("misc", "Invalid flag (category: %u).", catvalue.catid);
    return false;
}

void LoadNpcTele(void)
{
    const char *Table[] =
    {
        "custom_npc_tele_category",
        "custom_npc_tele_destination",
        "custom_npc_tele_association",
    };


    QueryResult result = WorldDatabase.PQuery(
        "SELECT `flag`, `data0`, `data1`, `cat_id`, C.`name` `namecat`, "
        //      0        1        2        3                  4                   
        "C.`name_loc1`, C.`name_loc2`, C.`name_loc3`, C.`name_loc4`, C.`name_loc5`, C.`name_loc6`, C.`name_loc7`, C.`name_loc8`, "
        //          5                     6                     7                     8                     9                     10                    11                    12                  
        "D.`name` `namedest`, "
        //          13
        "D.`name_loc1`, D.`name_loc2`, D.`name_loc3`, D.`name_loc4`, D.`name_loc5`, D.`name_loc6`, D.`name_loc7`, D.`name_loc8`, "
        //      14                      15                      16                  17                      18                  19                      20                  21
        "`pos_X`, `pos_Y`, `pos_Z`, `orientation`, `map`, `level`, `cost` "
        //      22        23        24        25        26     27       28 
        "FROM `%s` C, `%s` D, `%s` A "
        "WHERE C.`id` = `cat_id` AND D.`id` = `dest_id` "
        "ORDER BY `namecat`, `cat_id`, `namedest`", Table[0], Table[1], Table[2]);

    nsNpcTel::TabCatDest.clear();

    if (result)
    {
        TC_LOG_INFO("server.loading", "Loading %s, %s and %s...", Table[0], Table[1], Table[2]);
        // barGoLink bar(result->GetRowCount());

        uint32 catid = 0;
        uint32 nbDest = 0;
        bool IsValidCat = true;
        bool FirstTime = true;

        do
        {
            // bar.step();
            Field *fields = result->Fetch();

            if (!IsValidCat && catid == fields[3].GetUInt32() && !FirstTime)
                continue;

            IsValidCat = true;
            FirstTime = false;

            nsNpcTel::CatValue catvalue =
            {
                fields[3].GetUInt32(),
                (nsNpcTel::Flag)fields[0].GetUInt8(),
                fields[1].GetUInt64(),
                fields[2].GetUInt32()
            };

            if (!nsNpcTel::IsValidData(catvalue))
            {
                IsValidCat = false;
                catid = catvalue.catid;
                continue;
            }

            if (catid != catvalue.catid)
            {
                catid = catvalue.catid;
                nsNpcTel::CatName catname =
                {
                    fields[4].GetString(),  // Cat Name
                    fields[5].GetString(),  // Cat Name Loc1
                    fields[6].GetString(),  // Cat Name Loc2
                    fields[7].GetString(),  // Cat Name Loc3
                    fields[8].GetString(),  // Cat Name Loc4
                    fields[9].GetString(),  // Cat Name Loc5
                    fields[10].GetString(), // Cat Name Loc6
                    fields[11].GetString(), // Cat Name Loc7
                    fields[12].GetString()  // Cat Name Loc8
                };

                nsNpcTel::CatDest categorie(catvalue, catname);
                nsNpcTel::TabCatDest.push_back(categorie);
            }

            nsNpcTel::Dest item =
            {
                fields[13].GetString(),    // Dest Name
                fields[14].GetString(),    // Dest Name_loc1
                fields[15].GetString(),    // Dest Name_loc2
                fields[16].GetString(),    // Dest Name_loc3
                fields[17].GetString(),    // Dest Name_loc4
                fields[18].GetString(),    // Dest Name_loc5
                fields[19].GetString(),    // Dest Name_loc6
                fields[20].GetString(),    // Dest Name_loc7
                fields[21].GetString(),    // Dest Name_loc8
                fields[22].GetFloat(),      // X
                fields[23].GetFloat(),      // Y
                fields[24].GetFloat(),      // Z
                fields[25].GetFloat(),      // Orientation
                fields[26].GetUInt16(),     // Map
                fields[27].GetUInt8(),      // Level
                fields[28].GetUInt32(),     // Cost
            };

            nsNpcTel::TabCatDest.back().AddDest(item);
            ++nbDest;
        } while (result->NextRow());

        TC_LOG_INFO("server.loading", " ");
        TC_LOG_INFO("server.loading", "Loaded %u npc_teleport.", nbDest);
    }
    else
        TC_LOG_ERROR("misc", "WARNING >> Loaded 0 npc_teleport.");
}


#undef TELE
#undef PAGE
#undef PAGEI