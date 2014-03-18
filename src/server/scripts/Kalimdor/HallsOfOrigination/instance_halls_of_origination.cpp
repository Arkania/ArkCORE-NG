 /*
* Copyright (C) 2010-2011 SkyFire <http://www.projectskyfire.org/>
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
#include "halls_of_origination.h"

#define ENCOUNTERS 7

/* Boss Encounters
   Temple Guardian Anhuur
   Earthrager Ptah
   Anraphet
   Isiset
   Ammunae
   Setesh
   Rajh
*/

class instance_halls_of_origination : public InstanceMapScript
{
public:
    instance_halls_of_origination() : InstanceMapScript("instance_halls_of_origination", 644) { }

    InstanceScript* GetInstanceScript(InstanceMap *map) const
    {
        return new instance_halls_of_origination_InstanceMapScript(map);
    }

    struct instance_halls_of_origination_InstanceMapScript: public InstanceScript
    {
        instance_halls_of_origination_InstanceMapScript(InstanceMap *map) : InstanceScript(map) {}

        uint32 Encounter[ENCOUNTERS];
        std::string m_strInstData;
        uint64 uiTempleGuardianAnhuur;
        uint64 uiEarthragerPtah;
        uint64 uiAnraphet;
        uint64 uiIsiset;
        uint64 uiAmmunae;
        uint64 uiSetesh;
        uint64 uiRajh;

        uint64 OriginationElevatorGUID;
        uint64 uiAnhuurBridgeGUID;

        void Initialize()
        {
            SetBossNumber(ENCOUNTERS);
            uiTempleGuardianAnhuur = 0;
            uiEarthragerPtah       = 0;
            uiAnraphet             = 0;
            uiIsiset               = 0;
            uiAmmunae              = 0;
            uiSetesh               = 0;
            uiRajh                 = 0;

            uiAnhuurBridgeGUID     = 0;
            OriginationElevatorGUID = 0;
        }

        bool IsEncounterInProgress() const
        {
            for (uint8 i = 0; i < ENCOUNTERS; ++i)
                if (Encounter[i] == IN_PROGRESS)
                    return true;
        
            return false;
        }

        void OnCreatureCreate(Creature* pCreature, bool)
        {
            switch(pCreature->GetEntry())
            {
                case BOSS_TEMPLE_GUARDIAN_ANHUUR:
                    uiTempleGuardianAnhuur = pCreature->GetGUID();
                    break;
                case BOSS_EARTHRAGER_PTAH:
                    uiEarthragerPtah = pCreature->GetGUID();
                    break;
                case BOSS_ANRAPHET:
                    uiAnraphet = pCreature->GetGUID();
                    break;
                case BOSS_ISISET:
                    uiIsiset = pCreature->GetGUID();
                    break;
                case BOSS_AMMUNAE:
                    uiAmmunae = pCreature->GetGUID();
                    break;
                case BOSS_SETESH:
                    uiSetesh = pCreature->GetGUID();
                    break;
                case BOSS_RAJH:
                    uiRajh = pCreature->GetGUID();
                    break;
            }
        }

        void OnGameObjectCreate(GameObject* go)
        {
            switch (go->GetEntry())
            {
                case GO_ORIGINATION_ELEVATOR:
                    OriginationElevatorGUID = go->GetGUID();
                    break;
                case GO_ANHUUR_BRIDGE:
                    uiAnhuurBridgeGUID = go->GetGUID();
                    break;
            }
        }

        uint64 GetData64(uint32 identifier)
        {
            switch(identifier)
            {
                case DATA_TEMPLE_GUARDIAN_ANHUUR:
                    return uiTempleGuardianAnhuur;
                case DATA_EARTHRAGER_PTAH:
                    return uiEarthragerPtah;
                case DATA_ANRAPHET:
                    return uiAnraphet;
                case DATA_ISISET:
                    return uiIsiset;
                case DATA_AMMUNAE:
                    return uiAmmunae;
                case DATA_SETESH:
                    return uiSetesh;
                case DATA_RAJH:
                    return uiRajh;

                case DATA_ORIGINATION_ELEVATOR:
                    return OriginationElevatorGUID;
            }
            return 0;
        }

        bool SetBossState(uint32 type, EncounterState state)
        {
            if (!InstanceScript::SetBossState(type, state))
                return false;

            return true;
        }

        uint32 GetData(uint32 type)
        {
            return Encounter[type];
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "H O " << GetBossSaveData();

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

            if (dataHead1 == 'H' && dataHead2 == 'O')
            {
                for (uint32 i = 0; i < ENCOUNTERS; ++i)
                {
                    uint32 tmpState;
                    loadStream >> tmpState;
                    if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                        tmpState = NOT_STARTED;
                    Encounter[i] = tmpState;
                }
            }
            else OUT_LOAD_INST_DATA_FAIL;

            OUT_LOAD_INST_DATA_COMPLETE;
        }
    };
};

void AddSC_instance_halls_of_origination()
{
    new instance_halls_of_origination();
}