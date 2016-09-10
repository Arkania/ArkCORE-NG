/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
 * Copyright (C) 2006-2007 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
#include "InstanceScript.h"
#include "uldaman.h"

class instance_uldaman : public InstanceMapScript
{
    public: 
        instance_uldaman() : InstanceMapScript(ULScriptName, 70) { } 

        struct instance_uldaman_InstanceMapScript : public InstanceScript
        {
            instance_uldaman_InstanceMapScript(Map* map) : InstanceScript(map) { }

            void Initialize() override
            {
                SetBossNumber(MAX_BOSS_ENCOUNTERS);

                for (uint8 i = 0; i < MAX_DATA_ENCOUNTER; ++i)
                    m_ListOfGUID[i] = 0;

                m_LoadingInstanceTimer = 0;
                m_IsTeamNpcsSpawned = false;
                m_hasDoor = false;
                m_hasPlayer = false;
                m_team = 0;
                m_doorTimer = 5000;
            }

            void OnPlayerEnter(Player* player) override
            {
                m_hasPlayer = true;
                m_team = player->GetTeam(); // ALLIANCE or HORDE
                m_LoadingInstanceTimer = 100;
            }

            void OnGameObjectCreate(GameObject* go) override
            {
                uint32 entry = go->GetEntry();
                switch (entry)
                {
                    case GO_TEMPLE_DOOR_1:
                        m_ListOfGUID[DATA_TEMPLE_DOOR_1] = go->GetGUID();
                        break;
                    case GO_TEMPLE_DOOR_2:
                        m_ListOfGUID[DATA_TEMPLE_DOOR_2] = go->GetGUID();
                        break;
                    case GO_TEMPLE_DOOR_3:
                        m_ListOfGUID[DATA_TEMPLE_DOOR_3] = go->GetGUID();
                        m_hasDoor = true;
                        break;
                    case GO_ANCIENT_VAULT_DOOR:
                        m_ListOfGUID[DATA_ANCIENT_VAULT_DOOR] = go->GetGUID();
                        break;
                    case GO_IRONAYA_SEAL_DOOR:
                        m_ListOfGUID[DATA_IRONAYA_SEAL_DOOR] = go->GetGUID();
                        break;
                    case GO_ECHOMOK_DOOR:
                        m_ListOfGUID[DATA_ECHOMOK_DOOR] = go->GetGUID();
                        break;
                    case GO_KEYSTONE:
                        m_ListOfGUID[DATA_KEYSTONE] = go->GetGUID();
                        break;
                    case GO_ALTAR_OF_THE_KEEPER:
                        m_ListOfGUID[DATA_ALTAR_OF_THE_KEEPER] = go->GetGUID();
                        break;
                    case GO_ALTAR_OF_ARCHAEDAS:
                        m_ListOfGUID[DATA_ALTAR_OF_ARCHAEDAS] = go->GetGUID();
                        break;
                }
            }

            void OnGameObjectRemove(GameObject* go) override
            {
                uint32 entry = go->GetEntry();
                switch (entry)
                {
                    case GO_TEMPLE_DOOR_1:
                        m_ListOfGUID[DATA_TEMPLE_DOOR_1] = 0;
                        break;
                    case GO_TEMPLE_DOOR_2:
                        m_ListOfGUID[DATA_TEMPLE_DOOR_2] = 0;
                        break;
                    case GO_TEMPLE_DOOR_3:
                        m_ListOfGUID[DATA_TEMPLE_DOOR_3] = 0;
                        m_hasDoor = false;
                        break;
                    case GO_ANCIENT_VAULT_DOOR:
                        m_ListOfGUID[DATA_ANCIENT_VAULT_DOOR] = 0;
                        break;
                    case GO_IRONAYA_SEAL_DOOR:
                        m_ListOfGUID[DATA_IRONAYA_SEAL_DOOR] = 0;
                        break;
                    case GO_ECHOMOK_DOOR:
                        m_ListOfGUID[DATA_ECHOMOK_DOOR] = 0;
                        break;
                    case GO_KEYSTONE:
                        m_ListOfGUID[DATA_KEYSTONE] = 0;
                        break;
                    case GO_ALTAR_OF_THE_KEEPER:
                        m_ListOfGUID[DATA_ALTAR_OF_THE_KEEPER] = 0;
                        break;
                    case GO_ALTAR_OF_ARCHAEDAS:
                        m_ListOfGUID[DATA_ALTAR_OF_ARCHAEDAS] = 0;
                        break;
                }
            }

            void OnCreatureCreate(Creature* creature) override
            {
                uint32 entry = creature->GetEntry();
                switch (entry)
                {
                    case BOSS_REVELOSH:
                        m_ListOfGUID[DATA_REVELOSH] = creature->GetGUID();
                        break;
                    case BOSS_BAELOG:
                        m_ListOfGUID[DATA_BAELOG] = creature->GetGUID();
                        break;
                    case BOSS_ERIC:
                        m_ListOfGUID[DATA_ERIC] = creature->GetGUID();
                        break;
                    case BOSS_OLAV:
                        m_ListOfGUID[DATA_OLAV] = creature->GetGUID();
                        break;
                    case BOSS_IRONAYA:
                        m_ListOfGUID[DATA_IRONAYA] = creature->GetGUID();
                        break;
                    case BOSS_OBSIDIAN_SENTINEL:
                        m_ListOfGUID[DATA_OBSIDIAN_SENTINEL] = creature->GetGUID();
                        break;
                    case BOSS_ANCIENT_STONE_KEEPER:
                        m_ListOfGUID[DATA_ANCIENT_STONE_KEEPER] = creature->GetGUID();
                        break;
                    case BOSS_GALGANN_FIREHAMMER:
                        m_ListOfGUID[DATA_GALGANN_FIREHAMMER] = creature->GetGUID();
                        break;
                    case BOSS_GRIMLOK:
                        m_ListOfGUID[DATA_GRIMLOK] = creature->GetGUID();
                        break;
                    case BOSS_ARCHAEDAS:
                        m_ListOfGUID[DATA_ARCHAEDAS] = creature->GetGUID();
                        break;
                    case NPC_EARTHEN_GUARDIAN:
                         
                        break;
                    case NPC_EARTHEN_CUSTODIAN:
                         
                        break;
                    case NPC_VAULT_WARDER:
                         
                        break;
                }
            }

            void OnCreatureRemove(Creature* creature) override
            { 
                uint32 entry = creature->GetEntry();
                switch (entry)
                {
                case BOSS_REVELOSH:
                    m_ListOfGUID[DATA_REVELOSH] = 0;
                    break;
                case BOSS_BAELOG:
                    m_ListOfGUID[DATA_BAELOG] = 0;
                    break;
                case BOSS_ERIC:
                    m_ListOfGUID[DATA_ERIC] = 0;
                    break;
                case BOSS_OLAV:
                    m_ListOfGUID[DATA_OLAV] = 0;
                    break;
                case BOSS_IRONAYA:
                    m_ListOfGUID[DATA_IRONAYA] = 0;
                    break;
                case BOSS_OBSIDIAN_SENTINEL:
                    m_ListOfGUID[DATA_OBSIDIAN_SENTINEL] = 0;
                    break;
                case BOSS_ANCIENT_STONE_KEEPER:
                    m_ListOfGUID[DATA_ANCIENT_STONE_KEEPER] = 0;
                    break;
                case BOSS_GALGANN_FIREHAMMER:
                    m_ListOfGUID[DATA_GALGANN_FIREHAMMER] = 0;
                    break;
                case BOSS_GRIMLOK:
                    m_ListOfGUID[DATA_GRIMLOK] = 0;
                    break;
                case BOSS_ARCHAEDAS:
                    m_ListOfGUID[DATA_ARCHAEDAS] = 0;
                    break;
                }
            }

            // Prefix DATA_ : Stored GUID of Boss, GameObjects and Creatures
            uint64 GetData64(uint32 identifier) const override
            {
                if (identifier < MAX_DATA_ENCOUNTER)
                    return m_ListOfGUID[identifier];

                return 0;
            }

            // Prefix ENC_ : NOT_STARTED = 0, IN_PROGRESS = 1, FAIL = 2, DONE = 3, SPECIAL = 4, TO_BE_DECIDED = 5
            uint32 GetData(uint32 Id) const override
            {
                if (Id < MAX_BOSS_ENCOUNTERS)
                    GetBossState(Id);

                return 0;
            }

            // Prefix ENC_ : NOT_STARTED = 0, IN_PROGRESS = 1, FAIL = 2, DONE = 3, SPECIAL = 4, TO_BE_DECIDED = 5
            void SetData(uint32 Id, uint32 Value) override
            {
                if (Id < MAX_BOSS_ENCOUNTERS)
                    SetBossState(Id, EncounterState(Value));
            }

            std::string GetSaveData() override
            {
                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << "U L " << GetBossSaveData();

                OUT_SAVE_INST_DATA_COMPLETE;
                return saveStream.str();
            }

            void Load(const char* str) override
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

                if (dataHead1 == 'U' && dataHead2 == 'L')
                {
                    for (uint32 i = 0; i < MAX_BOSS_ENCOUNTERS; ++i)
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

            void Update(uint32 diff) override
            {
                if (m_LoadingInstanceTimer < diff)
                {
                    if (m_IsTeamNpcsSpawned)
                        m_LoadingInstanceTimer = 0;
                    else
                    {
                        SpawnNpcs();
                        m_LoadingInstanceTimer = 100;
                    }
                }
                else
                    m_LoadingInstanceTimer -= diff;

                if (m_doorTimer < diff)
                {
                    m_doorTimer = 5000;
                    if (GameObject* door = instance->GetGameObject(m_ListOfGUID[DATA_IRONAYA_SEAL_DOOR]))
                        if (GetData(ENC_IRONAYA) == DONE)
                            door->SetGoState(GO_STATE_ACTIVE);

                    if (GameObject* door = instance->GetGameObject(m_ListOfGUID[DATA_TEMPLE_DOOR_1]))
                        if (GetData(ENC_ANCIENT_STONE_KEEPER) == DONE)
                            door->SetGoState(GO_STATE_ACTIVE);

                    if (GameObject* door = instance->GetGameObject(m_ListOfGUID[DATA_TEMPLE_DOOR_2]))
                        if (GetData(ENC_ANCIENT_STONE_KEEPER) == DONE)
                            door->SetGoState(GO_STATE_ACTIVE);

                }
                else
                    m_doorTimer -= diff;
            }

            void ProcessEvent(WorldObject* obj, uint32 eventId) override
            { 
                printf("Instance Uldaman ProcessEvent: ID: %u \n", eventId);
            }

            // private instance functions

            void SpawnNpcs()
            {
                if (m_IsTeamNpcsSpawned || !m_hasDoor || !m_hasPlayer)
                    return;

                if (m_team == ALLIANCE)
                    SpawnAllyNpcs();
                else if (m_team == HORDE)
                    SpawnHordeNpcs();
                else
                    ASSERT(false);

            }
            void SpawnHordeNpcs()
            {
                GameObject* door = nullptr;
                if (m_ListOfGUID[DATA_TEMPLE_DOOR_3] > 0)
                    if (door = instance->GetGameObject(m_ListOfGUID[DATA_TEMPLE_DOOR_3]))
                    {
                        m_IsTeamNpcsSpawned = true;
                        door->SummonCreature(46231, -217.644f, 65.1548f, -45.9551f, 4.67748f);
                        door->SummonCreature(46231, -243.465f, 49.8025f, -45.9353f, 3.78736f);
                        door->SummonCreature(46231, -223.069f, 54.5037f, -45.9551f, 4.76475f);
                        door->SummonCreature(46231, -243.518f, 71.8074f, -45.9353f, 3.33358f);
                        door->SummonCreature(46231, -238.607f, 65.729f, -45.9551f, 4.67748f);
                        door->SummonCreature(46231, -212.148f, 48.7422f, -45.9353f, 0.314159f);
                        door->SummonCreature(46231, -233.206f, 54.7517f, -45.9551f, 4.86947f);
                        door->SummonCreature(46231, -209.9f, 69.7882f, -45.9353f, 1.65806f);
                        door->SummonCreature(46235, -231.96f, 72.4446f, -46.0254f, 4.75985f);
                        door->SummonCreature(46236, -235.179f, 68.2282f, -46.037f, 6.21836f);
                        door->SummonCreature(46241, -229.572f, 72.4077f, -46.0257f, 4.72296f);
                        door->SummonGameObject(205970, -233.49f, 75.5449f, -46.0186f, -1.55334f, 0, 0, -0.700909f, 0.713251f, 7200);
                        door->SummonGameObject(205970, -222.345f, 75.5217f, -46.0186f, -1.55334f, 0, 0, -0.700909f, 0.713251f, 7200);
                    }
            }
            void SpawnAllyNpcs()
            {
                GameObject* door = nullptr;
                if (m_ListOfGUID[DATA_TEMPLE_DOOR_3 ] > 0)
                    if (door = instance->GetGameObject(m_ListOfGUID[DATA_TEMPLE_DOOR_3]))
                    {
                        m_IsTeamNpcsSpawned = true;
                        door->SummonCreature(46232, -243.503f, 71.802f, -45.9353f, 3.12414f);
                        door->SummonCreature(46232, -209.841f, 69.7669f, -45.9353f, 1.64061f);
                        door->SummonCreature(46232, -243.499f, 49.799f, -45.9353f, 3.80482f);
                        door->SummonCreature(46232, -238.625f, 65.7627f, -45.9551f, 4.97419f);
                        door->SummonCreature(46232, -233.23f, 54.7151f, -45.9551f, 4.71239f);
                        door->SummonCreature(46232, -212.185f, 48.7618f, -45.9353f, 6.26573f);
                        door->SummonCreature(46232, -217.629f, 65.0299f, -45.9551f, 4.60767f);
                        door->SummonCreature(46232, -223.084f, 54.4619f, -45.9551f, 4.72984f);
                        door->SummonCreature(46233, -226.355f, 72.4579f, -46.0268f, 4.69574f);
                        door->SummonCreature(46234, -220.662f, 68.2366f, -46.0384f, 3.1286f);
                        door->SummonCreature(46247, -223.899f, 72.3204f, -46.0249f, 4.75464f);
                        door->SummonGameObject(205969, -233.501f, 75.5574f, -46.0186f, 4.71239f, 0, 0, -0.707107f, 0.707107f, 7200);
                        door->SummonGameObject(205969, -222.369f, 75.6659f, -46.0186f, 4.71239f, 0, 0, -0.707107f, 0.707107f, 7200);
                    }
            }

         private:
            uint64  m_ListOfGUID[MAX_DATA_ENCOUNTER];
            uint32  m_LoadingInstanceTimer;
            bool    m_IsTeamNpcsSpawned;
            bool    m_hasDoor;
            bool    m_hasPlayer;
            uint32  m_team;
            uint32  m_doorTimer;
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const override
        {
            return new instance_uldaman_InstanceMapScript(map);
        }
};

void AddSC_instance_uldaman()
{
    new instance_uldaman();
}
