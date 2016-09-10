/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
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

/*
This placeholder for the instance is needed for dungeon finding to be able
to give credit after the boss defined in lastEncounterDungeon is killed.
Without it, the party doing random dungeon won't get satchel of spoils and
gets instead the deserter debuff.
*/

#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "dire_maul.h"

class instance_dire_maul : public InstanceMapScript
{
public:
    instance_dire_maul() : InstanceMapScript(DMScriptName, 429) { }

    struct instance_dire_maul_InstanceMapScript : public InstanceScript
    {
        instance_dire_maul_InstanceMapScript(Map* map) : InstanceScript(map) { }

        void Initialize() override
        {
            SetBossNumber(MAX_ENC_ENCOUNTER);

            for (uint8 i = 0; i < MAX_DATA_ENCOUNTER; ++i)
                m_ListOfGUID[i] = 0;
            for (uint8 i = 0; i < MAX_EXTRA_ENCOUNTER; i++)
                m_Extra_State[i] = TO_BE_DECIDED;

            m_LoadingInstanceTimer = 0;
            m_checkGameProgressTimer = 0;
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
            switch (go->GetEntry())
            {
                case GO_CONSERVATORY_DOOR:
                    m_ListOfGUID[DATA_CONSERVATORY_DOOR] = go->GetGUID();
                    break;
            }
        }

        void OnGameObjectRemove(GameObject* go) override
        {

        }

        void OnCreatureCreate(Creature* creature) override
        {
            switch (creature->GetEntry())
            {
                case NPC_PUSILLIN:
                    m_ListOfGUID[DATA_PUSILLIN] = creature->GetGUID();
                    break;
                case BOSS_HYDROSPAWN:
                    m_ListOfGUID[DATA_HYDROSPAWN] = creature->GetGUID();
                    break;
                case BOSS_LETHTENDRIS:
                    m_ListOfGUID[DATA_LETHTENDRIS] = creature->GetGUID();
                    break;
                case NPC_PIMGIP:
                    m_ListOfGUID[DATA_PIMGIP] = creature->GetGUID();
                    break;
                case BOSS_ZEVRIM_THORNHOOF:
                    m_ListOfGUID[DATA_ZEVRIM_THORNHOOF] = creature->GetGUID();
                    break;
                case BOSS_ALZZIN_THE_WILDAHAPER:
                    m_ListOfGUID[DATA_ALZZIN_THE_WILDAHAPER] = creature->GetGUID();
                    break;
                case NPC_ISALIEN:
                    m_ListOfGUID[DATA_ISALIEN] = creature->GetGUID();
                    break;
                case NPC_EMPYREAN:
                    m_ListOfGUID[DATA_EMPYREAN] = creature->GetGUID();
                    break;
                case NPC_OLD_IRONBARK:
                    m_ListOfGUID[DATA_OLD_IRONBARK] = creature->GetGUID();
                    break;
                case NPC_IRONBARK_THE_REDEEMED:
                    m_ListOfGUID[DATA_IRONBARK_THE_REDEEMED] = creature->GetGUID();
                    break;
                case BOSS_TENDRIS_WARPWOOD:
                    m_ListOfGUID[DATA_TENDRIS_WARPWOOD] = creature->GetGUID();
                    break;
                case BOSS_ILLYANNA_RAVENOAK:
                    m_ListOfGUID[DATA_ILLYANNA_RAVENOAK] = creature->GetGUID();
                    break;
                case NPC_FERRA:
                    m_ListOfGUID[DATA_FERRA] = creature->GetGUID();
                    break;
                case NPC_TSUZEE:
                    m_ListOfGUID[DATA_TSUZEE] = creature->GetGUID();
                    break;
                case BOSS_MAGISTER_KALENDRIS:
                    m_ListOfGUID[DATA_MAGISTER_KALENDRIS] = creature->GetGUID();
                    break;
                case NPC_REVANCHION:
                    m_ListOfGUID[DATA_REVANCHION] = creature->GetGUID();
                    break;
                case BOSS_IMMOLTHAR:
                    m_ListOfGUID[DATA_IMMOLTHAR] = creature->GetGUID();
                    break;
                case NPC_LORD_HELNURATH:
                    m_ListOfGUID[DATA_LORD_HELNURATH] = creature->GetGUID();
                    break;
                case BOSS_PRINCE_TORTHELDRIN:
                    m_ListOfGUID[DATA_PRINCE_TORTHELDRIN] = creature->GetGUID();
                    break;
                case BOSS_GUARD_MOLDAR:
                    m_ListOfGUID[DATA_GUARD_MOLDAR] = creature->GetGUID();
                    break;
                case BOSS_STOMPER_KREEG:
                    m_ListOfGUID[DATA_STOMPER_KREEG] = creature->GetGUID();
                    break;
                case BOSS_GUARD_FENGUS:
                    m_ListOfGUID[DATA_GUARD_FENGUS] = creature->GetGUID();
                    break;
                case BOSS_GUARD_SLIPKIK:
                    m_ListOfGUID[DATA_GUARD_SLIPKIK] = creature->GetGUID();
                    break;
                case BOSS_CAPTAIN_KROMCRUSH:
                    m_ListOfGUID[DATA_CAPTAIN_KROMCRUSH] = creature->GetGUID();
                    break;
                case BOSS_CHORUSH_THE_OBSERVER:
                    m_ListOfGUID[DATA_CHORUSH_THE_OBSERVER] = creature->GetGUID();
                    break;
                case BOSS_KING_GORDOK:
                    m_ListOfGUID[DATA_KING_GORDOK] = creature->GetGUID();
                    break;
            }
        }

        void OnCreatureRemove(Creature* creature) override
        {

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
            if (Id < MAX_ENC_ENCOUNTER)
                GetBossState(Id);
            else if (Id < MAX_EXTRA_ENCOUNTER)
                GetExtraState(Id);

            return 0;
        }

        // Prefix ENC_ : NOT_STARTED = 0, IN_PROGRESS = 1, FAIL = 2, DONE = 3, SPECIAL = 4, TO_BE_DECIDED = 5
        void SetData(uint32 Id, uint32 Value) override
        {
            if (Id < MAX_ENC_ENCOUNTER)
                SetBossState(Id, EncounterState(Value));
            else if (Id < MAX_EXTRA_ENCOUNTER)
                SetExtraState(Id, TO_BE_DECIDED);
        }

        std::string GetSaveData() override
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "D M " << GetBossSaveData() << GetExtraSaveData();

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

            if (dataHead1 == 'D' && dataHead2 == 'M')
            {
                for (uint32 i = 0; i < MAX_ENC_ENCOUNTER; ++i)
                {
                    uint32 tmpState;
                    loadStream >> tmpState;
                    if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                        tmpState = NOT_STARTED;

                    SetBossState(i, EncounterState(tmpState));
                }
                for (uint32 i = MAX_ENC_ENCOUNTER; i < MAX_EXTRA_ENCOUNTER; i++)
                {
                    uint32 tmpState;
                    loadStream >> tmpState;
                    if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                        tmpState = NOT_STARTED;

                    SetExtraState(i, EncounterState(tmpState));
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
                {
                    m_LoadingInstanceTimer = 0;
                    m_checkGameProgressTimer = 100;
                }
                else
                {
                    SpawnNpcs();
                    m_LoadingInstanceTimer = 100;
                }
            }
            else
                m_LoadingInstanceTimer -= diff;

            if (m_checkGameProgressTimer < diff)
            {
                m_checkGameProgressTimer = 5000;
                DoCheckGameProgress();
            }
            else
                m_checkGameProgressTimer -= diff;
        }

        void ProcessEvent(WorldObject* obj, uint32 eventId) override
        {
            printf("Instance Dire Maul ProcessEvent: ID: %u \n", eventId);
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

            if (GetData(DATA_ZEVRIM_THORNHOOF) == DONE)
            {
                printf("Data is done");
            }

        }
        void SpawnHordeNpcs()
        {
            GameObject* door = nullptr;
            if (m_ListOfGUID[0] > 0)
                if (door = instance->GetGameObject(m_ListOfGUID[0]))
                {
                    m_IsTeamNpcsSpawned = true;
                    
                }
        }
        void SpawnAllyNpcs()
        {
            GameObject* door = nullptr;
            if (m_ListOfGUID[0] > 0)
                if (door = instance->GetGameObject(m_ListOfGUID[0]))
                {
                    m_IsTeamNpcsSpawned = true;
                   
                }
        }
        void DoCheckGameProgress()
        {
            if (GetData(DATA_ZEVRIM_THORNHOOF) == DONE)
            {
                printf("Data is done");
            }
        }
        EncounterState GetExtraState(uint32 id) const
        {
            if (id < MAX_EXTRA_ENCOUNTER)
                return m_Extra_State[id];

            return TO_BE_DECIDED;
        }
        void SetExtraState(uint32 id, EncounterState state)
        {
            if (id < MAX_EXTRA_ENCOUNTER)
                m_Extra_State[id] = state;

            this->SaveToDB();
        }
        std::string GetExtraSaveData()
        {
            std::ostringstream saveStream;
            
            for (uint32 i = MAX_ENC_ENCOUNTER; i < MAX_EXTRA_ENCOUNTER; i++)
                saveStream << (uint32)m_Extra_State[i] << ' ';

            return saveStream.str();
        }

        private:
            uint64  m_ListOfGUID[MAX_DATA_ENCOUNTER];
            EncounterState m_Extra_State[MAX_EXTRA_ENCOUNTER];
            uint32  m_LoadingInstanceTimer;
            uint32 m_checkGameProgressTimer;
            bool    m_IsTeamNpcsSpawned;
            bool    m_hasDoor;
            bool    m_hasPlayer;
            uint32  m_team;
            uint32  m_doorTimer;
    };

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_dire_maul_InstanceMapScript(map);
    }
};

void AddSC_instance_dire_maul()
{
    new instance_dire_maul();
}
