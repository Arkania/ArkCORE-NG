/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 * Copyright (C) 2006-2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

/* ScriptData
SDName: Instance_Deadmines
SD%Complete: 100
SDComment:
SDCategory: Deadmines
EndScriptData */

#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "deadmines.h"
#include "TemporarySummon.h"
#include "WorldPacket.h"
#include "Opcodes.h"
#include "GroupMgr.h"

class instance_deadmines : public InstanceMapScript
{
public:
    instance_deadmines() : InstanceMapScript(DMScriptName, 36) { }

    struct instance_deadmines_InstanceMapScript : public InstanceScript
    {
        instance_deadmines_InstanceMapScript(Map* map) : InstanceScript(map) { }

        void Initialize()
        {
            SetBossNumber(MAX_BOSS_ENCOUNTER);

            for (uint8 i = 0; i < MAX_DATA_ENCOUNTER; ++i)
                m_ListOfGUID[i] = 0;
                    
            m_LoadingInstanceTimer = 3000;
            m_IsHeroicMode = false;
            m_TeamInInstance = 0;
            m_TeamGroup = NULL;
            m_GroupSize = 0;
            m_SpecialNpcSpawned = false;
            m_TeamMinLevel = 0;
            m_TeamMaxLevel = 0;
        }

        void OnPlayerEnter(Player* player)
        {
            Creature* horatio = player->FindNearestCreature(46612, 1000.0f);
            Creature* kagtha = player->FindNearestCreature(46889, 1000.0f);
            if (!horatio && !kagtha)
                m_SpecialNpcSpawned = false;

            if (!m_TeamInInstance)
            {
                m_TeamInInstance = player->GetTeam();
                m_IsHeroicMode = player->GetMap()->IsHeroic();
                if (player->GetGroup())
                {
                    m_GroupSize = player->GetGroup()->GetMembersCount();
                    m_TeamGroup = player->GetGroup();
                }
                else
                    m_GroupSize = 1;
            }
            CheckTeamValues();
        }

        void OnGameObjectCreate(GameObject* go)
        {
            switch (go->GetEntry())
            {
            case GO_FACTORY_DOOR:
                m_ListOfGUID[DATA_FACTORY_DOOR] = go->GetGUID();
                AddDoor(go, true);
                break;
            case GO_FACTORY_DOOR_LEVER:
                m_ListOfGUID[DATA_FACTORY_DOOR_LEVER] = go->GetGUID();
                break;
            case GO_HEAVY_DOOR2:
                AddDoor(go, true);
                m_ListOfGUID[DATA_HEAVY_DOOR2] = go->GetGUID();
                break;
            case GO_MASTROOM_DOOR:
                AddDoor(go, true);
                m_ListOfGUID[DATA_MASTROOM_DOOR] = go->GetGUID();
                break;
            case GO_MASTROOM_DOOR_LEVER:
                m_ListOfGUID[DATA_MASTROOM_DOOR_LEVER] = go->GetGUID();
                break;
            case GO_HEAVY_DOOR4:
                AddDoor(go, true);
                m_ListOfGUID[DATA_HEAVY_DOOR4] = go->GetGUID();
                break;
            case GO_FOUNDRY_DOOR:
                m_ListOfGUID[DATA_FOUNDRY_DOOR] = go->GetGUID();
                AddDoor(go, true);
                break;
            case GO_FOUNDRY_DOOR_LEVER:
                m_ListOfGUID[DATA_FOUNDRY_DOOR_LEVER] = go->GetGUID();
                break;
            case GO_IRONCLAD_DOOR:
                m_ListOfGUID[DATA_IRONCLAD_DOOR] = go->GetGUID();
                AddDoor(go, true);
                break;
            case GO_IRONCLAD_DOOR_LEVER:
                m_ListOfGUID[DATA_IRONCLAD_DOOR_LEVER] = go->GetGUID();
                break;
            case GO_DEFIAS_CANNON:
                m_ListOfGUID[DATA_DEFIAS_CANNON] = go->GetGUID();
                break;
            case GO_MR_SMITE_CHEST:
                m_ListOfGUID[DATA_MR_SMITE_CHEST] = go->GetGUID();
                break;
            }
            if (!m_SpecialNpcSpawned)
                m_LoadingInstanceTimer = 3000;
        }

        void OnGameObjectRemove(GameObject* go)
        {
            switch (go->GetEntry())
            {
            case GO_FACTORY_DOOR:
            case GO_HEAVY_DOOR2:
            case GO_MASTROOM_DOOR:
            case GO_HEAVY_DOOR4:
            case GO_FOUNDRY_DOOR:
            case GO_IRONCLAD_DOOR:
                AddDoor(go, false);
                break;
            }
        }

        void OnCreatureCreate(Creature* creature)
        {
            m_CreatureList.push_back(creature->GetGUID());

            switch (creature->GetEntry())
            {
            case NPC_ADMIRAL_RIPSNARL:
                m_ListOfGUID[DATA_ADMIRAL_RIPSNARL] = creature->GetGUID();
                break;
            case NPC_CAPTAIN_COOKIE:
                m_ListOfGUID[DATA_CAPTAIN_COOKIE] = creature->GetGUID();
                break;
            case NPC_FOO_REAPER_5000:
                m_ListOfGUID[DATA_FOO_REAPER_5000] = creature->GetGUID();
                break;
            case NPC_GLUBTOK:
                m_ListOfGUID[DATA_GLUBTOK] = creature->GetGUID();
                break;
            case NPC_LUMBERING_OAF:
                m_ListOfGUID[DATA_LUMBERING_OAF] = creature->GetGUID();
                break;
            case NPC_HELIX_GEARBREAKER:
                m_ListOfGUID[DATA_HELIX_GEARBREAKER] = creature->GetGUID();
                break;
            case NPC_MR_SMITE:
                m_ListOfGUID[DATA_MR_SMITE] = creature->GetGUID();
                break;
            case NPC_VANESSA_VANCLEEF:
                m_ListOfGUID[DATA_VANESSA_VANCLEEF] = creature->GetGUID();
                break;
            }
            if (!m_SpecialNpcSpawned)
                m_LoadingInstanceTimer = 3000;
        }
 
        uint64 GetData64(uint32 identifier) const
        {
            if (identifier < MAX_DATA_ENCOUNTER)
                return m_ListOfGUID[identifier];
            
            return 0;
        }

        uint32 GetData(uint32 DataId) const 
        { 
            if (DataId < MAX_DATA_ENCOUNTER)
                GetBossState(DataId);

            return 0; 
        }

        void SetData(uint32 DataId, uint32 Value) 
        { 
            if (DataId < MAX_DATA_ENCOUNTER)
                SetBossState(DataId, EncounterState(Value));
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "D M " << GetBossSaveData();

            OUT_SAVE_INST_DATA_COMPLETE;
            return saveStream.str();
        }

        void Load(const char* str)
        {
            if (!str)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(str);

            char dataHead1, dataHead2;

            std::istringstream loadStream(str);
            loadStream >> dataHead1 >> dataHead2;

            if (dataHead1 == 'D' && dataHead2 == 'M')
            {
                for (uint32 i = 0; i < MAX_BOSS_ENCOUNTER; ++i)
                {
                    uint32 tmpState;
                    loadStream >> tmpState;
                    if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                        tmpState = NOT_STARTED;

                    SetBossState(i, EncounterState(tmpState));
                }
            }
            else
                OUT_LOAD_INST_DATA_FAIL;

            OUT_LOAD_INST_DATA_COMPLETE;
        }

        void Update(uint32 diff)
        {
            if (m_SpecialNpcSpawned)
                return;

            if (!m_TeamInInstance)
                return;

            if (m_LoadingInstanceTimer < diff)
            {
                CheckTeamValues();
                SummonFactionNpc();
                //SetAllMobToNewLevel();
            }
            else
                m_LoadingInstanceTimer -= diff;

        }

 // private instance functions

        void SummonFactionNpc()
        {
            if (m_SpecialNpcSpawned)
                return;

            if (!m_TeamInInstance)
                return;

            GameObject* door = instance->GetGameObject(GetData64(DATA_FACTORY_DOOR));
            if (!door)
                return;

            if (ServerAllowsTwoSideGroups())
            {
                if (Creature* npc = door->SummonCreature(46902, -57.0278f, -403.214f, 54.3313f, 2.37365f))
                    npc->setFaction(35);
                if (Creature* npc = door->SummonCreature(46906, -66.6233f, -398.573f, 54.6927f, 4.85202f))
                    npc->setFaction(35);
                if (Creature* npc = door->SummonCreature(46889, -66.2517f, -401.241f, 54.2756f, 1.51844f))
                    npc->setFaction(35);
                if (Creature* npc = door->SummonCreature(46612, -71.3333f, -406.488f, 55.1161f, 0.890118f))
                    npc->setFaction(35);
                if (Creature* npc = door->SummonCreature(24935, -55.8281f, -405.351f, 54.9577f, 1.27409f))
                    npc->setFaction(35);
                if (Creature* npc = door->SummonCreature(50595, -19.3856f, -382.425f, 61.2815f, 5.46498f))
                    npc->setFaction(35);
                if (Creature* npc = door->SummonCreature(46890, -10.822f, -381.801f, 61.7296f, 4.2307f))
                    npc->setFaction(35);
                if (Creature* npc = door->SummonCreature(46890, -47.0517f, -384.61f, 55.5244f, 0.137929f))
                    npc->setFaction(35);
                if (Creature* npc = door->SummonCreature(50595, -82.5855f, -370.036f, 57.1863f, 3.60782f))
                    npc->setFaction(35);
                if (Creature* npc = door->SummonCreature(46890, -82.8833f, -380.416f, 56.5812f, 2.71094f))
                    npc->setFaction(35);
                if (Creature* npc = door->SummonCreature(46614, -49.7597f, -399.682f, 55.6046f, 0.55936f))
                    npc->setFaction(35);
                if (Creature* npc = door->SummonCreature(46614, -46.989f, -395.134f, 55.4531f, 5.28353f))
                    npc->setFaction(35);
                if (Creature* npc = door->SummonCreature(46614, -65.4093f, -353.747f, 55.2116f, 2.83702f))
                    npc->setFaction(35);
                if (Creature* npc = door->SummonCreature(46613, -54.9423f, -380.117f, 54.2159f, 0.389306f))
                    npc->setFaction(35);
                if (Creature* npc = door->SummonCreature(46613, -19.3453f, -375.108f, 60.8902f, 4.6391f))
                    npc->setFaction(35);
                if (Creature* npc = door->SummonCreature(46613, -46.0976f, -390.719f, 55.7053f, 0.985423f))
                    npc->setFaction(35);
                if (Creature* npc = door->SummonCreature(46903, -59.4844f, -405.837f, 55.0932f, 1.81514f))
                    npc->setFaction(35);
                if (Creature* npc = door->SummonCreature(46903, -53.5035f, -402.894f, 55.534f, 2.40855f))
                    npc->setFaction(35);
            }
            else if (m_TeamInInstance == HORDE)
            {
                door->SummonCreature(46890, -19.3698f, -382.516f, 61.3321f, 5.65618f);
                door->SummonCreature(46890, -10.822f, -381.801f, 61.7296f, 4.2307f);
                door->SummonCreature(46890, -47.0517f, -384.61f, 55.5244f, 0.137929f);
                door->SummonCreature(46903, -59.4844f, -405.837f, 55.0932f, 1.81514f);
                door->SummonCreature(46903, -53.5035f, -402.894f, 55.534f, 2.40855f);
                door->SummonCreature(46902, -57.0278f, -403.214f, 54.3313f, 2.37365f);
                door->SummonCreature(46906, -66.6233f, -398.573f, 54.6927f, 4.85202f);
                door->SummonCreature(46889, -66.2517f, -401.241f, 54.2756f, 1.51844f);
                door->SummonCreature(46890, -82.8833f, -380.416f, 56.5812f, 2.71094f);
                door->SummonCreature(46890, -82.5976f, -369.945f, 57.2399f, 3.44135f);
            }
            else if (m_TeamInInstance == ALLIANCE)
            {
                door->SummonCreature(50595, -19.3856f, -382.425f, 61.2815f, 5.46498f);
                door->SummonCreature(50595, -10.8074f, -381.678f, 61.7195f, 4.38898f);
                door->SummonCreature(50595, -46.7356f, -384.701f, 55.5368f, 0.752586f);
                door->SummonCreature(46612, -71.3333f, -406.488f, 55.1161f, 0.890118f);
                door->SummonCreature(24935, -55.8281f, -405.351f, 54.9577f, 1.27409f);
                door->SummonCreature(46614, -49.7597f, -399.682f, 55.6046f, 0.55936f);
                door->SummonCreature(46614, -46.989f, -395.134f, 55.4531f, 5.28353f);
                door->SummonCreature(46614, -65.4093f, -353.747f, 55.2116f, 2.83702f);
                door->SummonCreature(46613, -54.9423f, -380.117f, 54.2159f, 0.389306f);
                door->SummonCreature(46613, -19.3453f, -375.108f, 60.8902f, 4.6391f);
                door->SummonCreature(46613, -46.0976f, -390.719f, 55.7053f, 0.985423f);
                door->SummonCreature(50595, -82.5855f, -370.036f, 57.1863f, 3.60782f);
                door->SummonCreature(50595, -82.9935f, -380.318f, 56.6257f, 2.72818f);
            }
            if (m_IsHeroicMode) // in heroic mode, add some level 85 elite mops
            {
                door->SummonCreature(49494, -231.9f, -585.074f, 51.3176f, 1.05134f);
                door->SummonCreature(49494, -230.046f, -569.505f, 51.3167f, 0.82184f);
                door->SummonCreature(49495, -232.8f, -591.18f, 19.3898f, 0);
                door->SummonCreature(49495, -218.608f, -581.075f, 21.0602f, 0);
                door->SummonCreature(49495, -233.625f, -570.587f, 19.3898f, 0);
                door->SummonCreature(49495, -222.154f, -555.108f, 19.3898f, 0);
                door->SummonCreature(49495, -212.606f, -567.224f, 21.0602f, 0);
                door->SummonCreature(49495, -203.918f, -551.061f, 19.3898f, 0);
                door->SummonCreature(49495, -202.866f, -590.137f, 21.0602f, 0);
                door->SummonCreature(49495, -196.476f, -573.083f, 21.0602f, 0);
                door->SummonCreature(49495, -185.929f, -558.125f, 19.3898f, 0);

                door->SummonCreature(49229, -205.583f, -574.135f, 21.4459f, 0);
                door->SummonCreature(49229, -205.75f, -584.432f, 21.5056f, 0);
                door->SummonCreature(49229, -210.821f, -579.18f, 21.5066f, 0);
                door->SummonCreature(49229, -200.573f, -579.406f, 21.444f, 0);

                door->SummonCreature(49534, -98.6319f, -721.627f, 8.54707f, 1.53589f);
                door->SummonCreature(49532, -97.7917f, -717.854f, 8.66809f, 4.5204f);
                door->SummonCreature(49532, -94.4028f, -719.727f, 8.59865f, 3.56047f);
                door->SummonCreature(49532, -101.917f, -718.755f, 8.72638f, 5.51524f);
                door->SummonCreature(49535, 5.23958f, -763.087f, 9.80043f, 2.00713f);
                door->SummonCreature(49532, 3.13715f, -760.031f, 9.726f, 5.39307f);
                door->SummonCreature(49532, 8.79801f, -762.225f, 9.60111f, -2.90404f);
                door->SummonCreature(49532, 4.23281f, -766.612f, 9.839f, 1.29265f);

                door->SummonCreature(49229, -205.583f, -574.135f, 21.4459f, 0);
                door->SummonCreature(49229, -205.75f, -584.432f, 21.5056f, 0);
                door->SummonCreature(49229, -210.821f, -579.18f, 21.5066f, 0);
                door->SummonCreature(49229, -200.573f, -579.406f, 21.444f, 0);

                door->SummonCreature(49539, -86.1057f, -775.447f, 26.8078f, 1.69932f);

            }
            else // if not heroic, then spawn some other mops
            {
                door->SummonCreature(657, -103.699f, -722.274f, 8.72363f, 4.95674f);
                door->SummonCreature(657, -96.4404f, -721.125f, 8.53125f, 3.94444f);
                door->SummonCreature(657, 6.70123f, -766.381f, 9.71319f, 2.25148f);
            }
            m_SpecialNpcSpawned = true;
        }

        void CheckTeamValues()
        {
            m_TeamMinLevel = 255;
            m_TeamMaxLevel = 0;
            if (m_GroupSize > 1)
                for (GroupReference* itr = m_TeamGroup->GetFirstMember(); itr != NULL; itr = itr->next())
                    if (Player* player = itr->GetSource())
                    {
                        if (player->getLevel() < m_TeamMinLevel)
                            m_TeamMinLevel = player->getLevel();
                        if (player->getLevel() > m_TeamMaxLevel)
                            m_TeamMaxLevel = player->getLevel();
                    }

            Map::PlayerList const& Players = instance->GetPlayers();
            if (!Players.isEmpty())
            {
                for (Map::PlayerList::const_iterator i = Players.begin(); i != Players.end(); ++i)
                    if (Player* player = i->GetSource())
                    {
                        if (player->getLevel() < m_TeamMinLevel)
                            m_TeamMinLevel = player->getLevel();
                        if (player->getLevel() > m_TeamMaxLevel)
                            m_TeamMaxLevel = player->getLevel();
                    }
            }
            if (m_TeamMinLevel < 14)
                m_TeamMinLevel = 14;
            if (m_TeamMaxLevel < 15)
                m_TeamMaxLevel = 15;
            if (m_TeamMinLevel > 85)
                m_TeamMinLevel = 85;
            if (m_TeamMaxLevel > 85)
                m_TeamMaxLevel = 85;
            if (m_TeamMaxLevel < m_TeamMinLevel)
                m_TeamMaxLevel = m_TeamMinLevel;
        }

        void SetAllMobToNewLevel()
        {
            GameObject* door = instance->GetGameObject(GetData64(DATA_FACTORY_DOOR));
            if (!door)
                return;

            for (std::list<uint64>::const_iterator itr = m_CreatureList.begin(); itr != m_CreatureList.end(); ++itr)
                if (Creature* npc = (Unit::GetCreature(*door, *itr)))
                {
                    SetMobToLevel(npc, RAND(m_TeamMinLevel, m_TeamMaxLevel));
                }
        }

        void SetMobToLevel(Creature* creature, uint8 level)
        {
            if (creature->getLevel() > 20)
                return;

            creature->SetLevel(level);
            creature->SetMaxHealth(100 + 32 * level);
            creature->SetHealth(100 + 30 * level);
            creature->SetArmor(100 + 44 * level);
        }

    private:
        uint64 m_ListOfGUID[MAX_DATA_ENCOUNTER];
        uint32 m_LoadingInstanceTimer;
        bool   m_IsHeroicMode;
        uint32 m_TeamInInstance;
        Group* m_TeamGroup;
        uint32 m_GroupSize;
        bool   m_SpecialNpcSpawned;
        uint32 m_TeamMinLevel;
        uint32 m_TeamMaxLevel;
        std::list<uint64> m_CreatureList;
    };

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_deadmines_InstanceMapScript(map);
    }
};

void AddSC_instance_deadmines()
{
    new instance_deadmines();
}
