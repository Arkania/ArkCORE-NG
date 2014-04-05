/*
 * Copyright (C) 2011-2014 ArkCORE <http://www.arkania.net/>
 *
 * This file is NOT free software. Third-party users can NOT redistribute 
 * it or modify it. If you find it, you are either hacking something, or very 
 * lucky (presuming someone else managed to hack it).
 */

/* ScriptData
SDName: instance_zulaman
SD%Complete: 100
SDComment:
SDCategory: Zul'Aman 4.1
EndScriptData */

#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "zulaman.h"
#include "Player.h"

#define MAX_ENCOUNTER  6
#define RAND_VENDOR    2

struct SHostageInfo
{
    uint32 npc, go;
    float x, y, z, o;
};

static SHostageInfo HostageInfo[] =
{
    {52939, 186648, -57, 1343, 40.77f, 3.2f}, // bear
    {52941, 187021, 400, 1414, 74.36f, 3.3f}, // eagle
    {52943, 186667, -35, 1134, 18.71f, 1.9f}, // dragonhawk
    {52945, 186672, 383, 1088,  5.97f, 1.63f}  // lynx
};

class instance_zulaman : public InstanceMapScript
{
    public:
        instance_zulaman() : InstanceMapScript("instance_zulaman", 568) { }

        struct instance_zulaman_InstanceMapScript : public InstanceScript
        {
            instance_zulaman_InstanceMapScript(Map* map) : InstanceScript(map) { }

            uint64 HarkorsSatchelGUID;
            uint64 TanzarsTrunkGUID;
            uint64 AshlisBagGUID;
            uint64 KrazsPackageGUID;

            uint64 HexLordEntranceGateGUID;
            uint64 HexLordExitGateGUID;
            uint64 AkilzonDoorGUID;
            uint64 HalazziEntranceDoorGUID;
            uint64 HalazziExitDoorGUID;

            uint32 QuestTimer;
            uint16 BossKilled;
            uint16 QuestMinute;
            uint16 ChestLooted;

            uint32 m_auiEncounter[MAX_ENCOUNTER];
            uint32 RandVendor[RAND_VENDOR];

            void Initialize()
            {
                memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));

                HarkorsSatchelGUID = 0;
                TanzarsTrunkGUID = 0;
                AshlisBagGUID = 0;
                KrazsPackageGUID = 0;

                HexLordEntranceGateGUID = 0;
                HexLordExitGateGUID = 0;
                AkilzonDoorGUID = 0;
                HalazziEntranceDoorGUID = 0;
                HalazziExitDoorGUID = 0;

                QuestTimer = 0;
                QuestMinute = 21;
                BossKilled = 0;
                ChestLooted = 0;

                for (uint8 i = 0; i < RAND_VENDOR; ++i)
                    RandVendor[i] = NOT_STARTED;
            }

            bool IsEncounterInProgress() const
            {
                for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                    if (m_auiEncounter[i] == IN_PROGRESS)
                        return true;

                return false;
            }

            void OnCreatureCreate(Creature* creature)
            {
                switch (creature->GetEntry())
                {
                    case 23578://janalai
                    case 23863://daakara
                    case 24239://hexlord
                    case 23577://halazzi
                    case 23576://nalorakk
                    default: break;
                }
            }

            void OnGameObjectCreate(GameObject* go)
            {
                switch (go->GetEntry())
                {
                    case 186304: HalazziEntranceDoorGUID  = go->GetGUID(); break;
                    case 186303: HalazziExitDoorGUID = go->GetGUID(); break;
                    case 186305: HexLordEntranceGateGUID = go->GetGUID(); break;
                    case 186306: HexLordExitGateGUID = go->GetGUID(); break;
                    case 186858: AkilzonDoorGUID = go->GetGUID(); break;

                    case 187021: HarkorsSatchelGUID  = go->GetGUID(); break;
                    case 186648: TanzarsTrunkGUID = go->GetGUID(); break;
                    case 186672: AshlisBagGUID = go->GetGUID(); break;
                    case 186667: KrazsPackageGUID  = go->GetGUID(); break;
                    default: break;
                }
                CheckInstanceStatus();
            }

            void SummonHostage(uint8 num)
            {
                if (!QuestMinute)
                    return;

                Map::PlayerList const &PlayerList = instance->GetPlayers();
                if (PlayerList.isEmpty())
                    return;

                Map::PlayerList::const_iterator i = PlayerList.begin();
                if (Player* i_pl = i->GetSource())
                {
                    if (Unit* Hostage = i_pl->SummonCreature(HostageInfo[num].npc, HostageInfo[num].x, HostageInfo[num].y, HostageInfo[num].z, HostageInfo[num].o, TEMPSUMMON_DEAD_DESPAWN, 0))
                    {
                        Hostage->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        Hostage->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    }
                }
            }

            void CheckInstanceStatus()
            {
                if (BossKilled >= 4)
                    HandleGameObject(HexLordEntranceGateGUID, true);

                if (BossKilled >= 5)
                    HandleGameObject(HexLordExitGateGUID, true);
            }

            std::string GetSaveData()
            {
                OUT_SAVE_INST_DATA;
                std::ostringstream ss;
                ss << "S" << BossKilled << ' ' << ChestLooted << ' ' << QuestMinute;

                OUT_SAVE_INST_DATA_COMPLETE;
                return ss.str();
            }

            void Load(const char* load)
            {
                if (!load)
                    return;

                std::istringstream ss(load);

                char dataHead; // S
                uint16 data1, data2, data3;
                ss >> dataHead >> data1 >> data2 >> data3;

                if (dataHead == 'S')
                {
                    BossKilled = data1;
                    ChestLooted = data2;
                    QuestMinute = data3;
                } else sLog->outError("TSCR: Zul'aman: corrupted save data.");
            }

            void SetData(uint32 type, uint32 data)
            {
                switch (type)
                {
                case DATA_NALORAKKEVENT:
                    m_auiEncounter[0] = data;
                    if (data == DONE)
                    {
                        if (QuestMinute)
                        {
                            QuestMinute += 5;
                            DoUpdateWorldState(3106, QuestMinute);
                        }
                        SummonHostage(0);
                    }
                    break;

                case DATA_AKILZONEVENT:
                    m_auiEncounter[1] = data;
                    HandleGameObject(AkilzonDoorGUID, data != IN_PROGRESS);
                    if (data == DONE)
                    {
                        if (QuestMinute)
                        {
                            QuestMinute += 5;
                            DoUpdateWorldState(3106, QuestMinute);
                        }
                        SummonHostage(1);
                    }
                    break;
                case DATA_JANALAIEVENT:
                    m_auiEncounter[2] = data;
                    if (data == DONE)
                        SummonHostage(2);
                    break;

                case DATA_HALAZZIEVENT:
                    m_auiEncounter[3] = data;
                    HandleGameObject(HalazziEntranceDoorGUID, data != IN_PROGRESS);
                    if (data == DONE)
                    {
                        HandleGameObject(HalazziExitDoorGUID, true);
                        SummonHostage(3);
                    }
                    break;

                case DATA_HEXLORDEVENT:
                    m_auiEncounter[4] = data;
                    if (data == IN_PROGRESS)
                        HandleGameObject(HexLordEntranceGateGUID, false);
                    else if (data == NOT_STARTED)
                        CheckInstanceStatus();
                    break;

                case DATA_DAAKARAEVENT:
                    m_auiEncounter[5] = data;
                    break;

                case DATA_CHESTLOOTED:
                    ++ChestLooted;
                    SaveToDB();
                    break;

                case TYPE_RAND_VENDOR_1:
                    RandVendor[0] = data;
                    break;

                case TYPE_RAND_VENDOR_2:
                    RandVendor[1] = data;
                    break;
                }

                if (data == DONE)
                {
                    ++BossKilled;
                    if (QuestMinute && BossKilled >= 4)
                    {
                        QuestMinute = 0;
                        DoUpdateWorldState(3104, 0);
                    }
                    CheckInstanceStatus();
                    SaveToDB();
                }
            }

            uint32 GetData(uint32 type) const
            {
                switch (type)
                {
                    case DATA_NALORAKKEVENT: return m_auiEncounter[0];
                    case DATA_AKILZONEVENT:  return m_auiEncounter[1];
                    case DATA_JANALAIEVENT:  return m_auiEncounter[2];
                    case DATA_HALAZZIEVENT:  return m_auiEncounter[3];
                    case DATA_HEXLORDEVENT:  return m_auiEncounter[4];
                    case DATA_DAAKARAEVENT:  return m_auiEncounter[5];
                    case DATA_CHESTLOOTED:   return ChestLooted;
                    case TYPE_RAND_VENDOR_1: return RandVendor[0];
                    case TYPE_RAND_VENDOR_2: return RandVendor[1];
                    default:                 return 0;
                }
            }

            void Update(uint32 diff)
            {
                if (QuestMinute)
                {
                    if (QuestTimer <= diff)
                    {
                        QuestMinute--;
                        SaveToDB();
                        QuestTimer += 60000;
                        if (QuestMinute)
                        {
                            DoUpdateWorldState(3104, 1);
                            DoUpdateWorldState(3106, QuestMinute);
                        } else DoUpdateWorldState(3104, 0);
                    }
                    QuestTimer -= diff;
                }
            }
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_zulaman_InstanceMapScript(map);
        }
};

void AddSC_instance_zulaman()
{
    new instance_zulaman();
}

