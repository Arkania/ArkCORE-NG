/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * This file is NOT free software. Third-party users can NOT redistribute 
 * it or modify it. If you find it, you are either hacking something, or very 
 * lucky (presuming someone else managed to hack it).
 */

#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "ScriptedCreature.h"
#include "bastion_of_twilight.h"
#include "ObjectMgr.h"
#include "Map.h"
#include "PoolMgr.h"

class instance_bastion_of_twilight : public InstanceMapScript
{
    public:
        instance_bastion_of_twilight() : InstanceMapScript("instance_bastion_of_twilight", 671) { }

        struct instance_bastion_of_twilight_InstanceMapScript : public InstanceScript
        {
            instance_bastion_of_twilight_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
            {
                data_phase = 1;
                SetBossNumber(MAX_ENCOUNTER);
                memset(&Encounter, 0, sizeof(Encounter));
            }

            uint32 uiEncounter[MAX_ENCOUNTER];

            // Bosses

            // Halfus
            uint64 halfus;          
            // Valiona and Theralion
            uint64 valiona;      
            uint64 theralion;      
            // Ascendant Council
            uint8 data_phase;       
            uint64 ascendantcouncil;
            uint64 feludius;      
            uint64 ignacious;    
            uint64 arion;       
            uint64 terrastra;   
            uint64 monstrosity;
            // Cho'gall
            uint64 chogall;  
            // Sinestra
            uint64 sinestra;   
            
            // Gobjects
            
            // Misc
            uint64 chogallHalfus;
            uint64 chogallValiona;
            uint64 chogallCouncil;

            void Initialize()
            {
                for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                    uiEncounter[i] = NOT_STARTED;
            
                // Bosses
                    // Halfus
                    halfus           = 0;
                    // Valiona and Theralion
                    valiona          = 0;
                    theralion        = 0;
                    // Ascendant Council
                    data_phase        = 0;
                    ascendantcouncil = 0;
                    feludius         = 0;
                    ignacious        = 0;
                    arion            = 0;
                    terrastra        = 0;
                    monstrosity      = 0;
                    // Cho'gall
                    chogall          = 0;
                    // Sinestra
                    sinestra         = 0;
            
                // Gobjects
            
                // Misc
                    chogallHalfus   = 0;
                    chogallValiona  = 0;
                    chogallCouncil  = 0;
            }
            
            bool IsEncounterInProgress() const
            {
                for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                    if (uiEncounter[i] == IN_PROGRESS)
                        return true;
            
                return false;
            }

            void OnCreatureCreate(Creature* creature)
            {
                switch (creature->GetEntry())
                {
                    case NPC_HALFUS_WORMBREAKER:
                        halfus = creature->GetGUID();
                        break;
                    case NPC_VALIONA_BOT:
                        valiona = creature->GetGUID();
                        break;
                    case NPC_THERALION_BOT:
                        theralion = creature->GetGUID();
                        break;
                    case NPC_ASCENDANT_COUNCIL:
                        ascendantcouncil = creature->GetGUID();
                        break;
                    case NPC_FELUDIUS:
                        feludius = creature->GetGUID();
                        break;
                    case NPC_IGNACIOUS:
                        ignacious = creature->GetGUID();
                        break;
                    case NPC_ARION:
                        arion = creature->GetGUID();
                        break;
                    case NPC_TERRASTRA:
                        terrastra = creature->GetGUID();
                        break;
                    case NPC_ELEMENTIUM_MONSTROSITY:
                        monstrosity = creature->GetGUID();
                        break;
                    case NPC_CHOGALL:
                        chogall = creature->GetGUID();
                        break;
                    case NPC_SINESTRA:
                        sinestra = creature->GetGUID();
                        break;
                    case NPC_CHOGALL_HALFUS:
                        chogallHalfus = creature->GetGUID();
                        break;
                    case NPC_CHOGALL_DRAGONS:
                        chogallValiona = creature->GetGUID();
                        break;
                    case NPC_CHOGALL_COUNCIL:
                        chogallCouncil = creature->GetGUID();
                        break;
                }
            }

            void OnGameObjectCreate(GameObject* go)
            {
               
            }

            void SetData(uint32 type, uint32 data)
            {
                if (type == DATA_AC_PHASE)
                    data_phase = data;
            }

            uint32 GetData(uint32 type) const
            {
                if (type == DATA_AC_PHASE)
                    return data_phase;

                return Encounter[type];
            }

            uint64 GetData64(uint32 type) const
            {
                switch (type)
                {
                    case NPC_HALFUS_WORMBREAKER:
                        return halfus;
                        break;
                    case NPC_VALIONA_BOT:
                        return valiona;
                        break;
                    case NPC_THERALION_BOT:
                        return theralion;
                        break;
                    case NPC_ASCENDANT_COUNCIL:
                        return ascendantcouncil;
                        break;
                    case NPC_FELUDIUS:
                        return feludius;
                        break;
                    case NPC_IGNACIOUS:
                        return ignacious;
                        break;
                    case NPC_ARION:
                        return arion;
                        break;
                    case NPC_TERRASTRA:
                        return terrastra;
                        break;
                    case NPC_ELEMENTIUM_MONSTROSITY:
                        return monstrosity;
                        break;
                    case NPC_CHOGALL:
                        return chogall;
                        break;
                    case NPC_SINESTRA:
                        return sinestra;
                        break;
                    case NPC_CHOGALL_HALFUS:
                        return chogallHalfus;
                        break;
                    case NPC_CHOGALL_DRAGONS:
                        return chogallValiona;
                        break;
                    case NPC_CHOGALL_COUNCIL:
                        return chogallCouncil;
                        break;
                }

                return 0;
            }

            bool SetBossState(uint32 data, EncounterState state) 
            {
                if (!InstanceScript::SetBossState(data, state))
                    return false;
            
                if(state == DONE)
                {
                    switch(data)
                    {
                        case DATA_HALFUS:
                        case DATA_VALIONA_THERALION:
                        case DATA_ASCENDANT_COUNCIL:
                        case DATA_CHOGALL:
                        case DATA_SINESTRA:
                        break;
                    }
                }
            
                return true;
            }

            std::string GetSaveData()
            {
                OUT_SAVE_INST_DATA;
            
                std::ostringstream saveStream;
                saveStream << "B T" << GetBossSaveData();
            
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
            
                if (dataHead1 == 'B' && dataHead2 == 'T')
                {
                    for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                    {
                        uint32 tmpState;
                        loadStream >> tmpState;
                        if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                            tmpState = NOT_STARTED;
                        Encounter[i] = tmpState;
                    }
                } else OUT_LOAD_INST_DATA_FAIL;
            
                OUT_LOAD_INST_DATA_COMPLETE;
            }

        private:
            uint32 Encounter[MAX_ENCOUNTER];
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_bastion_of_twilight_InstanceMapScript(map);
        }
};

void AddSC_instance_bastion_of_twilight()
{
    new instance_bastion_of_twilight();
}
