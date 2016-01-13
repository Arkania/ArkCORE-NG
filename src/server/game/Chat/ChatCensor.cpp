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

#include "ScriptMgr.h"
#include "Channel.h"
#include "Guild.h"
#include "Group.h"
#include "ChatCensor.h"
#include "Configuration/Config.h"

typedef std::list<sBadWords> BadWordsList;
static BadWordsList m_BadWordsList;
static bool IsInitializes = false;
static bool IsEnabled = false;
static int BadnessLevel = 0;

class ChatCensorScript : public PlayerScript
{
public:
    ChatCensorScript() : PlayerScript("ChatCensorScript") 
    { 
        InitializeCensor();
    }

    void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg) override
    {
        if (CalculateBadWords(msg) >= BadnessLevel)
        {
            msg = "";
            player->MonsterWhisper(8003, player);
        }
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Player* receiver) override
    {
        if (CalculateBadWords(msg) >= BadnessLevel)
        {
            msg = "";
            player->MonsterWhisper(8003, player);
        }
    }

    void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Group* group) override
    {
        if (CalculateBadWords(msg) >= BadnessLevel)
        {
            msg = "";
            player->MonsterWhisper(8003, player);
        }
    }

    void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Guild* guild) override
    {
        if (CalculateBadWords(msg) >= BadnessLevel)
        {
            msg = "";
            player->MonsterWhisper(8003, player);
        }
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& msg, Channel* channel) override
    {
        if (CalculateBadWords(msg) >= BadnessLevel)
        {
            msg = "";
            player->MonsterWhisper(8003, player);
        }
    }

    int32 CalculateBadWords(std::string& msg)
    {

        if (m_BadWordsList.empty() || !IsDisabled() || BadnessLevel == 0)
            return -1;

        int32 value = -1;
        for (std::list<sBadWords>::iterator itr = m_BadWordsList.begin(); itr != m_BadWordsList.end(); ++itr)
        {
            if (HasWord(msg, itr->m_word))
            {
                if (value < 0) 
                    value = 0;

                value += itr->m_level;
            }
        }
        return value;
    }

    bool HasWord(std::string& msg, std::string& word)
    {
        if (msg.find(word) != std::string::npos)
            return true;
        
        return false;
    }

    bool HasChar(std::string& msg, char c)
    {
        if (strchr(msg.c_str(), c))
            return true;

        return false;
    }

    // return a string without non ascii char
    // kill spaces on start on end of string
    std::string strip(const std::string &msg) 
    {
        std::string result;
        result.reserve(msg.length());

        std::remove_copy_if(msg.begin(),
            msg.end(),
            std::back_inserter(result),
            std::not1(std::ptr_fun(isalpha)));

        return result;
    }

    void InitializeCensor()
    {
        if (IsInitializes)
            return;

        m_BadWordsList.clear();
        IsInitializes = true;

        IsEnabled = sConfigMgr->GetBoolDefault("ChatCensor.Enabled", false);
        BadnessLevel = sConfigMgr->GetIntDefault("ChatCensor.BadnessLevel", 1);

        QueryResult result = WorldDatabase.PQuery(
            "SELECT `word`, `level` FROM `censor_bad_words`;");

        if (!result)
        {
            TC_LOG_ERROR("server.loading", ">> Loaded 0 bad word definitions. DB table `censor_bad_words` is empty.");
            return;
        }

        do
        {
            Field* fields = result->Fetch();

            std::string word = fields[0].GetString();
            uint32 level = fields[1].GetUInt32();

            m_BadWordsList.push_back(sBadWords(word, level));

        } while (result->NextRow());

    }

    static bool IsDisabled()
    {
        return !IsEnabled;
    }
};

void AddSC_chat_censor()
{
    new ChatCensorScript();
}

