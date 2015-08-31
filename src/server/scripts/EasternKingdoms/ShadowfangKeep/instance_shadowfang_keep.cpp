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

enum Spells
{
    SPELL_ASHCROMBE_TELEPORT = 15742,
};
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
    instance_shadowfang_keep() : InstanceMapScript(SKScriptName, SKScriptId) { }

    struct instance_shadowfang_keep_InstanceMapScript : public InstanceScript
    {
        instance_shadowfang_keep_InstanceMapScript(Map* map) : InstanceScript(map) { }

        void Initialize() override
        {
            SetBossNumber(MAX_BOSS_ENCOUNTERS);
            LoadDoorData(doorData);

            for (uint8 i = 0; i < MAX_DATA_ENCOUNTER; ++i)
                m_ListOfGUID[i] = 0;

            for (uint8 i = 0; i < MAX_EXTRA_ENCOUNTERS; ++i)
                m_ListOfEncounters[i] = 0;

            uiPhase = 0;
            uiTimer = 0;
            spawnCrazedTimer = 0;
            m_IsHeroicMode = false;
            m_Team = -1;
            m_Group = NULL;
            m_GroupSize = 0;
            m_isSpecialNpcSpawned = false;
        }

        void OnPlayerEnter(Player* player)
        {
            if (m_Group = player->GetGroup())
            {
                if (m_Group->IsLeader(player->GetGUID()))
                {
                    m_GroupSize = m_Group->GetMembersCount();
                    m_IsHeroicMode = player->GetMap()->IsHeroic();
                    m_Team = player->GetTeam();
                    SummonAllSpecialNpc();
                }
            }
            else
            {
                m_IsHeroicMode = player->GetMap()->IsHeroic();
                m_Team = player->GetTeam();
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
            case NPC_LORD_WALDEN:
                m_ListOfGUID[DATA_LORD_WALDEN] = creature->GetGUID();
                break;
            case NPC_BARON_ASHBURY:
                m_ListOfGUID[DATA_BARON_ASHBURY] = creature->GetGUID();
                break;
            case NPC_BARON_SILVERLAINE: 
                m_ListOfGUID[DATA_BARON_SILVERLAINE] = creature->GetGUID();
                break;
            case NPC_COMMANDER_SPRINGVALE: 
                m_ListOfGUID[DATA_COMMANDER_SPRINGVALE] = creature->GetGUID();
                break;
            case NPC_LORD_GODFREY: 
                m_ListOfGUID[DATA_LORD_GODFREY] = creature->GetGUID();
                break;
            }
            SummonAllSpecialNpc();
        }

        void OnGameObjectCreate(GameObject* go) override
        {            
            switch (go->GetEntry())
            {
            case GO_COURTYARD_DOOR:
                m_ListOfGUID[DATA_COURTYARD_DOOR] = go->GetGUID();
                AddDoor(go, true);
                if (m_ListOfEncounters[TYPE_DOOR_COURTYARD] == DONE)
                    HandleGameObject(0, true, go);
                SummonAllSpecialNpc();
                break;
            case GO_SORCERER_DOOR:
                m_ListOfGUID[DATA_SORCERER_DOOR] = go->GetGUID();
                AddDoor(go, true);
                if (m_ListOfEncounters[TYPE_DOOR_SORCERER] == DONE)
                    HandleGameObject(0, true, go);
                break;
            case GO_ARUGAL_DOOR:
                m_ListOfGUID[DATA_ARUGAL_DOOR] = go->GetGUID();
                AddDoor(go, true);
                if (m_ListOfEncounters[TYPE_DOOR_ARUGAL] == DONE)
                    HandleGameObject(0, true, go);
                break;
            case GO_PRISON_DOOR1:
                m_ListOfGUID[DATA_PRISON_DOOR1] = go->GetGUID();
                AddDoor(go, true);
                if (m_ListOfEncounters[DATA_PRISON_DOOR1] == DONE)
                    HandleGameObject(0, true, go);
                break;
            case GO_PRISON_DOOR2:
                m_ListOfGUID[DATA_PRISON_DOOR2] = go->GetGUID();
                AddDoor(go, true);
                if (m_ListOfEncounters[DATA_PRISON_DOOR2] == DONE)
                    HandleGameObject(0, true, go);
                break;
            case GO_PRISON_DOOR3:
                m_ListOfGUID[DATA_PRISON_DOOR3] = go->GetGUID();
                AddDoor(go, true);
                if (m_ListOfEncounters[DATA_PRISON_DOOR3] == DONE)
                    HandleGameObject(0, true, go);
                break;
            case GO_PRISON_LEVER1:
                m_ListOfGUID[DATA_PRISON_LEVER1] = go->GetGUID();
                break;
            case GO_PRISON_LEVER2:
                m_ListOfGUID[DATA_PRISON_LEVER2] = go->GetGUID();
                break;
            case GO_PRISON_LEVER3:
                m_ListOfGUID[DATA_PRISON_LEVER3] = go->GetGUID();
                break;
            }
        }

        uint64 GetData64(uint32 identifier) const
        {
            if (identifier < MAX_DATA_ENCOUNTER)
                return m_ListOfGUID[identifier];

            return 0;
        }

        void SetData(uint32 id, uint32 state) override
        {
            if (id < MAX_BOSS_ENCOUNTERS)
                SetBossState(id, EncounterState(state));
            if (id < MAX_EXTRA_ENCOUNTERS)
                m_ListOfEncounters[id] = state;

            if (state == DONE)
            {
                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << "S K " << GetBossSaveData();
                    
                for (uint8 i = MAX_BOSS_ENCOUNTERS; i < MAX_EXTRA_ENCOUNTERS; ++i)
                    saveStream << m_ListOfEncounters[i] << ' ';

                str_data = saveStream.str();

                SaveToDB();
                OUT_SAVE_INST_DATA_COMPLETE;
            }
        }

        uint32 GetData(uint32 id) const override
        {
            if (id < MAX_BOSS_ENCOUNTERS)
                GetBossState(id);
            if (id < MAX_EXTRA_ENCOUNTERS)
                return m_ListOfEncounters[id];

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
                for (uint32 i = 0; i < MAX_EXTRA_ENCOUNTERS; ++i)
                {
                    uint32 tmpState;
                    loadStream >> tmpState;
                    if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                        tmpState = NOT_STARTED;
                    if (i < MAX_BOSS_ENCOUNTERS)
                        SetBossState(i, EncounterState(tmpState));
                    if (i < MAX_EXTRA_ENCOUNTERS)
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

        void SummonAllSpecialNpc()
        {
            if (m_isSpecialNpcSpawned || m_Team == -1)
                return;

            GameObject* door = instance->GetGameObject(GetData64(DATA_COURTYARD_DOOR));
            if (!door) return;

            m_isSpecialNpcSpawned = true;

            if (m_Team == HORDE)
            {
                door->SummonCreature(47293, -220.958f, 2129.48f, 80.7898f, 4.60767f);
                door->SummonCreature(47293, -241.012f, 2129.97f, 87.0242f, 4.04738f);
                door->SummonCreature(47293, -260.385f, 2290.04f, 75.0826f, 2.77507f);
                door->SummonCreature(47293, -227.415f, 2257.64f, 102.753f, 3.44501f);
                door->SummonCreature(47293, -171.591f, 2181.00f, 129.284f, 1.06933f);
                door->SummonCreature(47293, -168.792f, 2183.66f, 151.936f, 4.79931f);
                door->SummonCreature(3849, -243.712f, 2113.72f, 81.2629f, 2.86234f);
                door->SummonCreature(6486, -217.264f, 2246.63f, 79.7742f, 5.05225f);
                door->SummonCreature(6486, -223.681f, 2245.57f, 79.7747f, 5.18184f);
                door->SummonCreature(11153, -225.453f, 2232.16f, 79.7772f, 1.85567f);
                door->SummonCreature(11154, -234.999f, 2236.92f, 79.7772f, 0.310152f);

            }
            if (m_Team == ALLIANCE)
            {
                door->SummonCreature(47006, -219.417f, 2137.05f, 80.9709f, 4.4855f);
                door->SummonCreature(47006, -228.681f, 2146.92f, 90.624f, 2.72695f);
                door->SummonCreature(47006, -246.660f, 2163.02f, 96.6991f, 2.44048f);
                door->SummonCreature(47006, -170.928f, 2180.24f, 129.297f, 0.661583f);
                door->SummonCreature(47027, -225.805f, 2131.28f, 80.7369f, 4.4482f);
                door->SummonCreature(47027, -216.662f, 2128.37f, 80.6875f, 4.41238f);
                door->SummonCreature(47862, -248.597f, 2115.47f, 81.2629f, 2.77507f);
                door->SummonCreature(3865, -217.197f, 2246.87f, 79.7733f, 5.04009f);
                door->SummonCreature(3864, -234.131f, 2236.26f, 79.8619f, 0.296706f);
                door->SummonCreature(3865, -223.612f, 2245.72f, 79.8582f, 5.13127f);
                door->SummonCreature(3864, -225.615f, 2232.22f, 79.7786f, 1.83252f);

            }
        }

    private:
        uint64 m_ListOfGUID[MAX_DATA_ENCOUNTER];
        uint32 m_ListOfEncounters[MAX_EXTRA_ENCOUNTERS];
        std::string str_data;
        uint32 uiPhase;
        uint32 uiTimer;
        uint32 spawnCrazedTimer;
        bool m_IsHeroicMode;
        int32 m_Team;
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
