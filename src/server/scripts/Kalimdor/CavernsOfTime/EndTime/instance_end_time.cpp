/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * THIS particular file is NOT free software; third-party users 
 * should NOT have access to it, redistribute it or modify it. :)
 */

#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "end_time.h"
#include "Player.h"

#define ENCOUNTERS 4

class instance_end_time : public InstanceMapScript
{
public:
    instance_end_time() : InstanceMapScript("instance_end_time", 938) { }

    InstanceScript* GetInstanceScript(InstanceMap *map) const
    {
        return new instance_end_time_InstanceMapScript(map);
    }

    struct instance_end_time_InstanceMapScript: public InstanceScript
    {
        instance_end_time_InstanceMapScript(InstanceMap *map) : InstanceScript(map) { }
        
        uint32 uiEncounter[ENCOUNTERS];

        uint64 uiEchoOfJaina;
        uint64 uiEchoOfBaine;
        uint64 uiEchoOfSylvanas;
        uint64 uiEchoOfTyrande;
        uint64 uiMurozond;

        uint32 FragmentsCollected;
        uint32 JainaPickedState;

        void Initialize()
        {
            uiEchoOfJaina = 0;
            uiEchoOfBaine = 0;
            uiEchoOfSylvanas = 0;
            uiEchoOfTyrande = 0;
            uiMurozond = 0;
            FragmentsCollected = 0;
            JainaPickedState = NOT_STARTED;

            for(uint8 i=0; i<ENCOUNTERS; ++i)
                uiEncounter[i] = NOT_STARTED;
        }

        bool IsEncounterInProgress() const
        {
            for(uint8 i=0; i<ENCOUNTERS; ++i)
            {
                if (uiEncounter[i] == IN_PROGRESS)
                    return true;
            }

            return false;
        }

        void FillInitialWorldStates(WorldPacket& data)
        {
            data << uint32(WORLDSTATE_SHOW_FRAGMENTS) << uint32(JainaPickedState == IN_PROGRESS);
            data << uint32(WORLDSTATE_FRAGMENTS_COLLECTED) << uint32(FragmentsCollected);
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch(creature->GetEntry())
            {
                case NPC_ECHO_OF_JAINA:
                    uiEchoOfJaina = creature->GetGUID();
                    break;
                case NPC_ECHO_OF_BAINE:
                    uiEchoOfBaine = creature->GetGUID();
                    break;
                case NPC_ECHO_OF_SYLVANAS:
                    uiEchoOfSylvanas = creature->GetGUID();
                    break;
                case NPC_ECHO_OF_TYRANDE:
                    uiEchoOfTyrande = creature->GetGUID();
                    break;
                case NPC_MUROZOND:
                    uiMurozond = creature->GetGUID();
                    break;

            }
        }

        void OnGameObjectCreate(GameObject* /*go*/)
        {
        }

        uint64 GetData64(uint32 identifier) const
        {
            switch(identifier)
            {
                case BOSS_ECHO_OF_JAINA:
                    return uiEchoOfJaina;
                case BOSS_ECHO_OF_BAINE:
                    return uiEchoOfBaine;
                case BOSS_ECHO_OF_SYLVANAS:
                    return uiEchoOfSylvanas;
                case BOSS_ECHO_OF_TYRANDE:
                    return uiEchoOfTyrande;
                case BOSS_MUROZOND:
                    return uiMurozond;
            }
            return 0;
        }

        void SetData(uint32 type,uint32 data)
        {
            switch(type)
            {
                case DATA_FIRST_ENCOUNTER:
                    uiEncounter[1] = data;
                    break;
                case DATA_SECOND_ENCOUNTER:
                    uiEncounter[2] = data;
                    break;
                case DATA_LAST_ENCOUNTER:
                    uiEncounter[3] = data;
                    break;
                case DATA_JAINA_PICKED_STATE:
                    switch (data)
                    {
                        case IN_PROGRESS:
                            DoUpdateWorldState(WORLDSTATE_SHOW_FRAGMENTS, 1);
                            break;
                        case DONE:
                            DoUpdateWorldState(WORLDSTATE_SHOW_FRAGMENTS, 0);
                            break;
                    }
                    JainaPickedState = data;
                    break;
            }
         
            if (data == DONE)
                SaveToDB();
        }

        uint32 GetData(uint32 type) const
        {
            switch(type)
            {
                case DATA_JAINA_PICKED_STATE:
                    return JainaPickedState;
            }
            return 0;
        }
        
        bool SetBossState(uint32 type, EncounterState state)
        {
            if (!InstanceScript::SetBossState(type, state))
                return false;

            switch (type)
            {
                case BOSS_ECHO_OF_JAINA:                   
                case BOSS_ECHO_OF_BAINE:
                case BOSS_ECHO_OF_SYLVANAS:
                case BOSS_ECHO_OF_TYRANDE:
                case BOSS_MUROZOND:
                    break;
                default:
                    break;
            }
             return true;
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "T E " << GetBossSaveData() << ' ' << JainaPickedState;

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

            if (dataHead1 == 'T' && dataHead2 == 'E')
            {
                for (uint32 i = 0; i < ENCOUNTERS; ++i)
                {
                    uint32 tmpState;
                    loadStream >> tmpState;
                    if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                        tmpState = NOT_STARTED;
                    SetBossState(i, EncounterState(tmpState));
                }

                uint32 temp = 0;
                loadStream >> temp;
                JainaPickedState = temp ? DONE : NOT_STARTED;
            }
            else
                OUT_LOAD_INST_DATA_FAIL;

            OUT_LOAD_INST_DATA_COMPLETE;
        }

    };
};

void AddSC_instance_end_time()
{
    new instance_end_time;
}
