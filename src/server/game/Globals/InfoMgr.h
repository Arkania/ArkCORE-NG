/*
* Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
* Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
* Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
* Copyright (C) 2015-2015 TerServer 
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

#ifndef _INFOMGR_H_
#define _INFOMGR_H_

#include "Common.h"
#include "ArenaTeam.h"
#include <ace/Singleton.h>
#include "ObjectMgr.h"

#define MAX_INFOCHAR_NAME_LENGTH (MAX_CHARTER_NAME * 2 + 1) // should be MAX_CHARACTER_NAME + 1 but i saw longer name in db... idk

struct InfoCharEntry
{
    uint32 Guid;
    char Name[MAX_INFOCHAR_NAME_LENGTH];
    uint8 Class;
    uint8 Race;
    uint8 Gender;
    uint8 Level;
    uint16 Zone;
    uint32 Guild;
    uint32 Account;
    uint32 Group;
    uint32 ArenaTeam[MAX_ARENA_SLOT];
    uint32 MMR[MAX_ARENA_SLOT];
};

class InfoMgr
{
public:
    //~InfoMgr();
    // Misc
    void Initialize();
    void UnloadAll();

    // Characters
    void UpdateCharBase(uint32 guid, std::string name, uint8 gender = GENDER_NONE, uint8 race = 0, uint8 cclass = 0, uint32 account = 0, uint8 level = 0, uint16 zone = 0, uint8 XPfactor = 0);
    void UpdateCharGuild(uint32 guid, uint32 guild);
    void UpdateCharGroup(uint32 guid, uint32 group);
    void UpdateCharArenaTeam(uint32 guid, uint32 team, uint8 slot);
    void UpdateCharLevel(uint32 guid, uint8 level);
    void UpdateCharMMR(uint32 guid, uint32 mmr, uint8 slot);
    void RemoveCharInfo(uint32 guid);
    bool GetCharInfo(uint32 guid, InfoCharEntry &info);
    bool GetCharInfo(std::string name, InfoCharEntry &info);
    uint32 GetCharCount() { return m_charInfos.size(); }

    // Accounts
    void IncreaseAccountCharCount(uint32 id);
    void DecreaseAccountCharCount(uint32 id);
    uint8 GetAccountCharCount(uint32 id);

    // Pets
    /*void FillPetList(uint32 ownerId, SavedPetList &petList);
    void SavePet(SavedPet* pet, Player* owner);
    void DeletePet(SavedPet* pet, Player* owner);
    void DeleteAllPetsFromOwner(uint32 ownerGuid);*/

private:
    // Characters
    void _RemoveName(std::string name);
    void _AddName(std::string name, InfoCharEntry *info);
    typedef std::map<std::string, InfoCharEntry*> CharInfoNameMap;
    typedef std::map<uint32, InfoCharEntry*> CharInfoMap;
    typedef CharInfoNameMap::iterator CharInfoNameItr;
    typedef CharInfoMap::iterator CharInfoItr;
    CharInfoNameMap m_charInfosName;
    CharInfoMap m_charInfos;
    ACE_Thread_Mutex m_charMutex;

    // Accounts
    void SetAccountCharCount(uint32 id, uint8 count);
    typedef std::map<uint32, uint8> AccountCharCountMap;
    typedef AccountCharCountMap::iterator AccountCharCountMapItr;
    AccountCharCountMap m_accountCharCounts;
    ACE_Thread_Mutex m_accountMutex;

    // Pets
    /*typedef std::map<uint32, SavedPet*> PetsMap;
    typedef PetsMap::iterator PetsMapItr;
    typedef std::set<SavedPet*> PetsSet;
    typedef PetsSet::iterator PetsSetItr;
    typedef std::map<uint32, PetsSet*> PetsToOwnerMap;
    typedef PetsToOwnerMap::iterator PetsToOwnerMapItr;
    PetsMap petsMap;
    PetsToOwnerMap petsToOwner;
    ACE_Thread_Mutex petsMutex;
    void UpdatePet(uint32 id, uint32 entry, uint32 ownerId, uint32 modelId, uint32 createdBySpell, uint32 type, uint8 reacteState, std::string name, uint8 renamed, uint8 slot,
        uint32 health, uint32 mana, uint32 happiness, uint32 saveTime, std::string actionbars, uint8 level, uint32 experience);
    void UpdatePetAuras(uint32 guid, uint64 casterGuid, uint32 spellId, uint8 effectMask, uint8 recalcMask, uint8 stacks, int32 amount_0, int32 amount_1, int32 amount_2, int32 baseAmount_0, int32 baseAmount_1, int32 baseAmount_2, int32 maxDuration, int32 remDuration, uint8 charges);
    void UpdatePetSpells(uint32 id, uint32 spellId, uint8 active);
    void UpdatePetSpellCooldowns(uint32 id, uint32 spellId, uint32 time);*/
};

#define sInfoMgr ACE_Singleton<InfoMgr, ACE_Null_Mutex>::instance()

#endif