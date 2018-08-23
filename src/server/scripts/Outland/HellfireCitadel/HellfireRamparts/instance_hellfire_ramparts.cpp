/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
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
SDName: Instance_Hellfire_Ramparts
SD%Complete: 50
SDComment:
SDCategory: Hellfire Ramparts
EndScriptData */


#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "PassiveAI.h"
#include "GameObjectAI.h"
#include "MapManager.h"
#include "MoveSplineInit.h"
#include "InstanceScript.h"
#include "hellfire_ramparts.h"

class instance_ramparts : public InstanceMapScript
{
    public:
        instance_ramparts() : InstanceMapScript(HRScriptName, 543) { }

        struct instance_ramparts_InstanceMapScript : public InstanceScript
        {
            instance_ramparts_InstanceMapScript(Map* map) : InstanceScript(map) { }

            void Initialize() override
            {
                SetBossNumber(EncounterCount);
                felIronChestGUID = 0;
                m_team = 0;
                m_chadwickGUID = 0;
                m_reconGUID = 0;
                m_stoktonGUID = 0;
                m_thrallmarGUID = 0;
            }

            void OnGameObjectCreate(GameObject* go) override
            {
                switch (go->GetEntry())
                {
                case GO_FEL_IRON_CHEST_NORMAL:
                case GO_FEL_IRON_CHECT_HEROIC:
                    felIronChestGUID = go->GetGUID();
                    break;
                }
            }

            void OnCreatureCreate(Creature* creature) override
            {
                switch (creature->GetEntry())
                {
                case NPC_ADVANCE_SCOUT_CHADWICK:
                    m_chadwickGUID = creature->GetGUID();
                    break;
                case NPC_STONE_GUARD_STOKTON:
                    m_stoktonGUID = creature->GetGUID();
                    break;
                case NPC_THRALLMAR_INVADER:
                    m_thrallmarGUID = creature->GetGUID();
                    break;
                case NPC_HONOR_HOLD_RECON:
                    m_reconGUID = creature->GetGUID();
                    break;
                }
                switch (creature->GetEntry())
                {
                case NPC_ADVANCE_SCOUT_CHADWICK:
                case NPC_STONE_GUARD_STOKTON:
                case NPC_THRALLMAR_INVADER:
                case NPC_HONOR_HOLD_RECON:
                    creature->SetVisible(false);
                    creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
                    CheckVisible(creature);
                    break;
                }
            }

            void OnPlayerEnter(Player* player)
            {
                m_team = player->GetTeam();
                CheckVisible(player);
            }

            bool SetBossState(uint32 type, EncounterState state) override
            {
                if (!InstanceScript::SetBossState(type, state))
                    return false;

                switch (type)
                {
                case DATA_VAZRUDEN:
                case DATA_NAZAN:
                    if (GetBossState(DATA_VAZRUDEN) == DONE && GetBossState(DATA_NAZAN) == DONE && !spawned)
                    {
                        DoRespawnGameObject(felIronChestGUID, HOUR*IN_MILLISECONDS);
                        spawned = true;
                    }
                    break;
                }
                return true;
            }

            std::string GetSaveData() override
            {
                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << "H R " << GetBossSaveData();

                OUT_SAVE_INST_DATA_COMPLETE;
                return saveStream.str();
            }

            void Load(const char* strIn) override
            {
                if (!strIn)
                {
                    OUT_LOAD_INST_DATA_FAIL;
                    return;
                }

                OUT_LOAD_INST_DATA(strIn);

                char dataHead1, dataHead2;

                std::istringstream loadStream(strIn);
                loadStream >> dataHead1 >> dataHead2;

                if (dataHead1 == 'H' && dataHead2 == 'R')
                {
                    for (uint8 i = 0; i < EncounterCount; ++i)
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

            void CheckVisible(Unit* m_char)
            {
                switch (m_team)
                {
                case 0:
                    break;
                case 67: // is Horde
                    if (Creature* npc = ObjectAccessor::GetCreature(*m_char, m_stoktonGUID))
                        npc->SetVisible(true);
                    if (Creature* npc = ObjectAccessor::GetCreature(*m_char, m_thrallmarGUID))
                        npc->SetVisible(true);
                    break;
                case 469:
                    if (Creature* npc = ObjectAccessor::GetCreature(*m_char, m_chadwickGUID))
                        npc->SetVisible(true);
                    if (Creature* npc = ObjectAccessor::GetCreature(*m_char, m_reconGUID))
                        npc->SetVisible(true);
                    break;
                }
            }

            uint64 felIronChestGUID;
            bool spawned;
            uint32 m_team;
            uint64 m_chadwickGUID;
            uint64 m_reconGUID;
            uint64 m_stoktonGUID;
            uint64 m_thrallmarGUID;
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const override
        {
            return new instance_ramparts_InstanceMapScript(map);
        }
};

void AddSC_instance_ramparts()
{
    new instance_ramparts;
}
