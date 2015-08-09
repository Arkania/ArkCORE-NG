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
#include "the_vortex_pinnacle.h"
#include "Player.h"

#define ENCOUNTERS 3

class instance_the_vortex_pinnacle : public InstanceMapScript
{
public:
    instance_the_vortex_pinnacle() : InstanceMapScript("instance_the_vortex_pinnacle", 657) { }
    
    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_the_vortex_pinnacle_InstanceMapScript(map);
    }

    struct instance_the_vortex_pinnacle_InstanceMapScript: public InstanceScript
    {
        instance_the_vortex_pinnacle_InstanceMapScript(InstanceMap* map) : InstanceScript(map) { }

        uint32 uiEncounter[ENCOUNTERS];

        uint64 uiGrandVizierErtanGUID;
        uint64 uiAltairusGUID;
        uint64 uiAsaadGUID;

        void Initialize()
        {
            uiGrandVizierErtanGUID = 0;
            uiAltairusGUID = 0;
            uiAsaadGUID = 0;

            for(uint8 i=0; i < ENCOUNTERS; ++i)
                uiEncounter[i] = NOT_STARTED;
        }

        bool IsEncounterInProgress() const
        {
            for(uint8 i=0; i < ENCOUNTERS; ++i)
            {
                if (uiEncounter[i] == IN_PROGRESS)
                    return true;
            }

            return false;
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch(creature->GetEntry())
            {
                case NPC_GRAND_VIZIER_ERTAN:
                    uiGrandVizierErtanGUID = creature->GetGUID();
                    break;
                case NPC_ALTAIRUS:
                    uiAltairusGUID = creature->GetGUID();
                    break;
                case NPC_ASAAD:
                    uiAsaadGUID = creature->GetGUID();
                    break;
            }
            
        }

        uint64 GetData64(uint32 identifier) const
        {
            switch(identifier)
            {
                case DATA_GRAND_VIZIER_ERTAN:
                    return uiGrandVizierErtanGUID;
                case DATA_ALTAIRUS:
                    return uiAltairusGUID;
                case DATA_ASAAD:
                    return uiAsaadGUID;
            }
            return 0;
        }

        void SetData(uint32 type,uint32 data)
        {
            switch(type)
            {
                case DATA_GRAND_VIZIER_ERTAN:
                    uiEncounter[0] = data;
                    break;
                case DATA_ALTAIRUS:
                    uiEncounter[1] = data;
                    break;
                case DATA_ASAAD:
                    uiEncounter[2] = data;
                    break;
            }
         
         if (data == DONE)
             SaveToDB();
        }

        uint32 GetData(uint32 type) const
        {
            switch(type)
            {
                case DATA_GRAND_VIZIER_ERTAN:
                    return uiEncounter[0];
                case DATA_ALTAIRUS:
                    return uiEncounter[1];
                case DATA_ASAAD:
                    return uiEncounter[2];
            }   
            return 0;
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::string str_data;
            std::ostringstream saveStream;
            saveStream << "V P" << uiEncounter[0] << " " << uiEncounter[1]  << " " << uiEncounter[2]; 
            str_data = saveStream.str();

            OUT_SAVE_INST_DATA_COMPLETE;
            return str_data;
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
            uint16 data0, data1, data2;

            std::istringstream loadStream(in);
            loadStream >> dataHead1 >> dataHead2 >> data0 >> data1 >> data2;

            if (dataHead1 == 'V' && dataHead2 == 'P')
            {
                uiEncounter[0] = data0;
                uiEncounter[1] = data1;
                uiEncounter[2] = data2;
                
                for(uint8 i=0; i < ENCOUNTERS; ++i)
                    if (uiEncounter[i] == IN_PROGRESS)
                        uiEncounter[i] = NOT_STARTED;
            }
            else OUT_LOAD_INST_DATA_FAIL;

            OUT_LOAD_INST_DATA_COMPLETE;
        }
    };
};

void AddSC_instance_the_vortex_pinnacle()
{
    new instance_the_vortex_pinnacle();
}
