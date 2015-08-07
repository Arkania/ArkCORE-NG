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

/*
This placeholder for the instance is needed for dungeon finding to be able
to give credit after the boss defined in lastEncounterDungeon is killed.
Without it, the party doing random dungeon won't get satchel of spoils and
gets instead the deserter debuff.
*/

#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "ragefire_chasm.h"

class instance_ragefire_chasm : public InstanceMapScript
{
public:
    instance_ragefire_chasm() : InstanceMapScript("instance_ragefire_chasm", 389) { }

    struct instance_ragefire_chasm_InstanceMapScript : public InstanceScript
    {
        instance_ragefire_chasm_InstanceMapScript(Map* map) : InstanceScript(map) { }

        void Initialize()
        {
            SetBossNumber(MAX_BOSS_ENCOUNTER);

            for (uint8 i = 0; i < MAX_DATA_ENCOUNTER; ++i)
                m_ListOfDataGUID[i] = 0;

        }

        void OnPlayerEnter(Player* player)
        {

        }

        void OnGameObjectCreate(GameObject* go)
        {
            // there is no door 
        }

        void OnGameObjectRemove(GameObject* go)
        {
            // there is no door 
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
            case NPC_TARAGAMAN_THE_HUNGERER:
                m_ListOfDataGUID[BOSS_TARAGAMAN_THE_HUNGERER] = creature->GetGUID();
                AddMinion(creature, true);
                break;
            case NPC_OGGLEFLINT:
                m_ListOfDataGUID[BOSS_OGGLEFLINT] = creature->GetGUID();
                AddMinion(creature, true);
                break;
            case NPC_JERGOSH_THE_INVOKER:
                m_ListOfDataGUID[BOSS_JERGOSH_THE_INVOKER] = creature->GetGUID();
                AddMinion(creature, true);
                break;
            case NPC_BAZZALAN:
                m_ListOfDataGUID[BOSS_BAZZALAN] = creature->GetGUID();
                AddMinion(creature, true);
                break;
            }
        }

        void OnCreatureRemove(Creature* creature)
        {
            switch (creature->GetEntry())
            {
            case BOSS_TARAGAMAN_THE_HUNGERER:
            case BOSS_OGGLEFLINT:
            case BOSS_JERGOSH_THE_INVOKER:
            case BOSS_BAZZALAN:
                AddMinion(creature, false);
                break;
            }
        }

        //All-purpose data storage 64 bit : dataId = enum npc 0 .. n 
        uint64 GetData64(uint32 dataId) const   
        {
            if (dataId < MAX_DATA_ENCOUNTER)
                return m_ListOfDataGUID[dataId];

            return 0;
        }

        //All-purpose data storage 64 bit : dataId = enum npc 0 .. n, value = GUID
        void SetData64(uint32 dataId, uint64 value) 
        { 
            if (dataId < MAX_DATA_ENCOUNTER)
                m_ListOfDataGUID[dataId] = value;
        }

        //All-purpose data storage 32 bit
        uint32 GetData(uint32 bossId) const         // handle enum BossState
        {
            if (bossId < MAX_BOSS_ENCOUNTER)
                return GetBossState(bossId);

            return 0;
        }

        //All-purpose data storage 32 bit : bossId = enum boss 0 .. n, value = EncounterState = 0..5
        void SetData(uint32 bossId, uint32 value)   // handle enum BossState
        {
            if (bossId < MAX_BOSS_ENCOUNTER)
                SetBossState(bossId, EncounterState(value));
        }

        bool SetBossState(uint32 data, EncounterState state) 
        {
            if (!InstanceScript::SetBossState(data, state))
                return false;
            
            return true;
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "R C " << GetBossSaveData();

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

            if (dataHead1 == 'R' && dataHead2 == 'C')
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

    private:
        uint64 m_ListOfDataGUID[MAX_DATA_ENCOUNTER];
    };

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_ragefire_chasm_InstanceMapScript(map);
    }
};

void AddSC_instance_ragefire_chasm()
{
    new instance_ragefire_chasm();
}
