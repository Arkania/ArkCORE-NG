/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
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
 */

#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "hour_of_twilight.h"

DoorData const doorData[] =
{
    {0, 0, DOOR_TYPE_ROOM, BOUNDARY_NONE }, // END
};

class instance_hour_of_twilight : public InstanceMapScript
{
public:
    instance_hour_of_twilight() : InstanceMapScript("instance_hour_of_twilight", 940) { }

    struct instance_hour_of_twilight_InstanceMapScript : public InstanceScript
    {
        instance_hour_of_twilight_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
        {
            Initialize();
        }

        uint64 Thrall1GUID;
        uint64 ArcurionGUID;

        void Initialize()
        {
            SetBossNumber(MAX_ENCOUNTERS);
            LoadDoorData(doorData);
            ArcurionGUID    = 0;
            Thrall1GUID     = 0;
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
                case BOSS_ARCURION:
                    ArcurionGUID = creature->GetGUID();
                    break;
                case NPC_THRALL_1:
                    Thrall1GUID = creature->GetGUID();
                    break;
            }
        }
/*
        void OnGameObjectCreate(GameObject* go)
        {
            switch (go->GetEntry())
            {
            }
        }


        void OnGameObjectRemove(GameObject* go)
        {
            switch (go->GetEntry())
            {
            }
        }
*/
        bool SetBossState(uint32 data, EncounterState state)
        {
            if (!InstanceScript::SetBossState(data, state))
                return false;

            return true;
        }

        uint64 GetData64(uint32 data) const
        {
            switch (data)
            {
                case DATA_ARCURION:
                    return ArcurionGUID;
                case DATA_THRALL_1:
                    return Thrall1GUID;
                default:
                    break;
            }
            return 0;
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "H T " << GetBossSaveData();

            OUT_SAVE_INST_DATA_COMPLETE;
            return saveStream.str();
        }

        void Load(const char* in)
        {
            if (!in)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(in);

            char dataHead1, dataHead2;

            std::istringstream loadStream(in);
            loadStream >> dataHead1 >> dataHead2;

            if (dataHead1 == 'H' && dataHead2 == 'T')
            {
                for (uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
                {
                    uint32 tmpState;
                    loadStream >> tmpState;
                    if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                        tmpState = NOT_STARTED;

                    SetBossState(i, EncounterState(tmpState));
                }

            } else OUT_LOAD_INST_DATA_FAIL;

            OUT_LOAD_INST_DATA_COMPLETE;
        }
    };

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_hour_of_twilight_InstanceMapScript(map);
    }
};

void AddSC_instance_hour_of_twilight()
{
    new instance_hour_of_twilight();
}