/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Instance_Shadowfang_Keep
SD%Complete: 90
SDComment:
SDCategory: Shadowfang Keep
EndScriptData */

#include "ScriptedCreature.h"
#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "shadowfang_keep.h"
#include "TemporarySummon.h"
#include "GroupMgr.h"

enum Apothecary
{
    ACTION_SPAWN_CRAZED         = 3
};

enum Yells
{
    SAY_BOSS_DIE_AD         = 4,
    SAY_BOSS_DIE_AS         = 3,
    SAY_ARCHMAGE            = 0
};


enum Spells
{
    SPELL_ASHCROMBE_TELEPORT    = 15742
};

const Position SpawnLocation[] =
{
    {-148.199f, 2165.647f, 128.448f, 1.026f},
    {-153.110f, 2168.620f, 128.448f, 1.026f},
    {-145.905f, 2180.520f, 128.448f, 4.183f},
    {-140.794f, 2178.037f, 128.448f, 4.090f},
    {-138.640f, 2170.159f, 136.577f, 2.737f}
};
class instance_shadowfang_keep : public InstanceMapScript
{
public:
    instance_shadowfang_keep() : InstanceMapScript("instance_shadowfang_keep", 33) { }

    struct instance_shadowfang_keep_InstanceMapScript : public InstanceScript
    {
        instance_shadowfang_keep_InstanceMapScript(Map* map) : InstanceScript(map) { }

        void Initialize() override
        {
            SetBossNumber(MAX_BOSS_ENCOUNTER);
            LoadDoorData(doorData);

            for (uint8 i = 0; i < MAX_DATA_ENCOUNTER; ++i)
                m_ListOfGUID[i] = 0;

            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                m_ListOfEncounters[i] = 0;

            uiPhase = 0;
            uiTimer = 0;
            spawnCrazedTimer = 0;
            m_IsHeroicMode = false;
            m_TeamId = TEAM_NEUTRAL;
            m_Group = NULL;
            m_GroupSize = 0;
            m_isSpecialNpcSpawned = false;
        }

        void OnPlayerEnter(Player* player)
        {
            if (player->GetGroup()->IsLeader(player->GetGUID()))
            {
                m_IsHeroicMode = player->GetMap()->IsHeroic();
                m_GroupSize = player->GetGroup()->GetMembersCount();
                m_Group = player->GetGroup();
                m_TeamId = player->GetTeamId();

                if (!m_isSpecialNpcSpawned)
                    SummonAllSpecialNpc();
            }            
        }

        void OnCreatureCreate(Creature* creature) override
        {
            switch (creature->GetEntry())
            {
            case NPC_ASH: 
                m_ListOfGUID[DATA_ASH] = creature->GetGUID();
                break;
            case NPC_ADA:
                m_ListOfGUID[DATA_ADA] = creature->GetGUID(); 
                break;
            case NPC_ARCHMAGE_ARUGAL:
                m_ListOfGUID[DATA_ARCHMAGE_ARUGAL] = creature->GetGUID(); 
                break;
            case NPC_ARUGAL_VOIDWALKER:
                m_ListOfGUID[DATA_ARUGAL_VOIDWALKER] = creature->GetGUID();
                break;
            case NPC_FRYE:
                m_ListOfGUID[DATA_FRYE] = creature->GetGUID();
                break;
            case NPC_HUMMEL: 
                m_ListOfGUID[DATA_HUMMEL] = creature->GetGUID();
                break;
            case NPC_BAXTER: 
                m_ListOfGUID[DATA_BAXTER] = creature->GetGUID();
                break;
            case NPC_TORMENTED_OFFICER:
                m_ListOfGUID[DATA_TORMENTED_OFFICER] = creature->GetGUID();
                break;
            case NPC_WAILING_GUARDSMAN:
                m_ListOfGUID[DATA_WAILING_GUARDSMAN] = creature->GetGUID();
                break;
            case BOSS_LORD_WALDEN:
                m_ListOfGUID[DATA_LORD_WALDEN] = creature->GetGUID();
                break;
            case BOSS_BARON_ASHBURY:
                m_ListOfGUID[DATA_BARON_ASHBURY] = creature->GetGUID();
                break;
            case BOSS_BARON_SILVERLAINE: 
                m_ListOfGUID[DATA_BARON_SILVERLAINE] = creature->GetGUID();
                break;
            case BOSS_COMMANDER_SPRINGVALE: 
                m_ListOfGUID[DATA_COMMANDER_SPRINGVALE] = creature->GetGUID();
                break;
            case BOSS_LORD_GODFREY: 
                m_ListOfGUID[DATA_LORD_GODFREY] = creature->GetGUID();
                break;
            }
        }

        void OnGameObjectCreate(GameObject* go) override
        {
            switch (go->GetEntry())
            {
            case GO_COURTYARD_DOOR:
                m_ListOfGUID[DATA_COURTYARD_DOOR] = go->GetGUID();
                AddDoor(go, true);
                if (m_ListOfEncounters[DOOR_COURTYARD] == DONE)
                    HandleGameObject(0, true, go);
                break;
            case GO_SORCERER_DOOR:
                m_ListOfGUID[DATA_SORCERER_DOOR] = go->GetGUID();
                AddDoor(go, true);
                if (m_ListOfEncounters[DOOR_SORCERER] == DONE)
                    HandleGameObject(0, true, go);
                break;
            case GO_ARUGAL_DOOR:
                m_ListOfGUID[DATA_ARUGAL_DOOR] = go->GetGUID();
                AddDoor(go, true);
                if (m_ListOfEncounters[DOOR_ARUGAL] == DONE)
                    HandleGameObject(0, true, go);
                break;
            }
        }

        void DoSpeech()
        {
            Creature* pAda = instance->GetCreature(m_ListOfGUID[DATA_ADA]);
            Creature* pAsh = instance->GetCreature(m_ListOfGUID[DATA_ASH]);

            if (pAda && pAda->IsAlive() && pAsh && pAsh->IsAlive())
            {
                pAda->AI()->Talk(SAY_BOSS_DIE_AD);
                pAsh->AI()->Talk(SAY_BOSS_DIE_AS);
            }
        }

        void SetData(uint32 State, uint32 Value) override
        {
            if (State < MAX_DATA_ENCOUNTER)
                SetBossState(State, EncounterState(Value));

            if (State == DONE)
            {
                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << "S K " << GetBossSaveData();
                    
                for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                    saveStream << ' ' << m_ListOfEncounters[i];

                str_data = saveStream.str();

                SaveToDB();
                OUT_SAVE_INST_DATA_COMPLETE;
            }
        }

        uint32 GetData(uint32 DataId) const override
        {
            if (DataId < MAX_DATA_ENCOUNTER)
                GetBossState(DataId);
            
            return 0;
        }

        uint64 GetData64(uint32 identifier) const
        {
            if (identifier < MAX_DATA_ENCOUNTER)
                return m_ListOfGUID[identifier];

            return 0;
        }

        std::string GetSaveData()
        {
            return str_data;
        }

        void Load(const char* in) override
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

            if (dataHead1 == 'S' && dataHead2 == 'K')
            {
                for (uint32 i = 0; i < MAX_BOSS_ENCOUNTER; ++i)
                {
                    uint32 tmpState;
                    loadStream >> tmpState;
                    if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                        tmpState = NOT_STARTED;
                    SetBossState(i, EncounterState(tmpState));
                }
                for (uint32 i = 0; i < MAX_ENCOUNTER; ++i)
                {
                    uint32 tmpState;
                    loadStream >> tmpState;
                    if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                        tmpState = NOT_STARTED;
                    m_ListOfEncounters[i] = tmpState;
                }
            }

            OUT_LOAD_INST_DATA_COMPLETE;
        }

        void Update(uint32 uiDiff)
        {
            if (GetData(TYPE_CROWN) == IN_PROGRESS)
            {
                if (spawnCrazedTimer <= uiDiff)
                {
                    if (Creature* hummel = instance->GetCreature(m_ListOfGUID[DATA_HUMMEL]))
                        hummel->AI()->DoAction(ACTION_SPAWN_CRAZED);
                    spawnCrazedTimer = urand(2000, 5000);
                }
                else
                    spawnCrazedTimer -= uiDiff;
            }

            if (GetData(TYPE_FENRUS) != DONE)
                return;

            Creature* pArchmage = instance->GetCreature(m_ListOfGUID[DATA_ARCHMAGE_ARUGAL]);

            if (!pArchmage || !pArchmage->IsAlive())
                return;

            if (uiPhase)
            {
                if (uiTimer <= uiDiff)
                {
                    switch (uiPhase)
                    {
                    case 1:
                    {
                        Creature* summon = pArchmage->SummonCreature(pArchmage->GetEntry(), SpawnLocation[4], TEMPSUMMON_TIMED_DESPAWN, 10000);
                        summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                        summon->SetReactState(REACT_DEFENSIVE);
                        summon->CastSpell(summon, SPELL_ASHCROMBE_TELEPORT, true);
                        summon->AI()->Talk(SAY_ARCHMAGE);
                        uiTimer = 2000;
                        uiPhase = 2;
                        break;
                    }
                    case 2:
                    {
                        pArchmage->SummonCreature(NPC_ARUGAL_VOIDWALKER, SpawnLocation[0], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
                        pArchmage->SummonCreature(NPC_ARUGAL_VOIDWALKER, SpawnLocation[1], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
                        pArchmage->SummonCreature(NPC_ARUGAL_VOIDWALKER, SpawnLocation[2], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
                        pArchmage->SummonCreature(NPC_ARUGAL_VOIDWALKER, SpawnLocation[3], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
                        uiPhase = 0;
                        break;
                    }

                    }
                }
                else uiTimer -= uiDiff;
            }
        }

        void SummonAllSpecialNpc()
        {
            m_isSpecialNpcSpawned = true;
            if (m_TeamId == TEAM_HORDE || m_TeamId == TEAM_NEUTRAL)
            {

            }
            if (m_TeamId == TEAM_ALLIANCE || m_TeamId == TEAM_NEUTRAL)
            {

            }
        }

    private:
        uint64 m_ListOfGUID[MAX_DATA_ENCOUNTER];
        uint32 m_ListOfEncounters[MAX_ENCOUNTER];
        std::string str_data;
        uint32 uiPhase;
        uint32 uiTimer;
        uint32 spawnCrazedTimer;
        bool m_IsHeroicMode;
        uint8 m_TeamId;
        Group* m_Group;
        uint32 m_GroupSize;
        bool m_isSpecialNpcSpawned;
    };

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_shadowfang_keep_InstanceMapScript(map);
    }
};

void AddSC_instance_shadowfang_keep()
{
    new instance_shadowfang_keep();
}
