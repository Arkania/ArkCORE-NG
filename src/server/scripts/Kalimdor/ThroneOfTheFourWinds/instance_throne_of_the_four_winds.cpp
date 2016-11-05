
#include "throne_of_the_four_winds.h"

#define ENCOUNTERS 2

Position const GoBackPositions[8] =
{
    {-16,  1021, 205, 0},
    {-80,  1021, 205, 0},
    {-256, 850,  205, 0},
    {-256, 785,  205, 0},
    {-83,  610,  205, 0},
    {-18,  610,  205, 0},
    {156,  780,  205, 0},
    {156,  850,  205, 0},
};

Position const AlakirSlipstreamPositions[4] =
{
    {-51.0972f, 576.807f, 200.7063f, 1.553343f},
    {-287.604f, 816.51f,  200.7063f, 0.0f},
    {188.823f,  813.54f,  200.7063f, 3.124139f},
    {-47.9531f, 1053.3f,  200.7063f, 4.694936f},
};

class instance_throne_of_the_four_winds : public InstanceMapScript
{
public:
    instance_throne_of_the_four_winds() : InstanceMapScript("instance_throne_of_the_four_winds", 754) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_throne_of_the_four_winds_InstanceMapScript(map);
    }

    struct instance_throne_of_the_four_winds_InstanceMapScript: public InstanceScript
    {
        instance_throne_of_the_four_winds_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
        {
            SetBossNumber(MAX_BOSSES);
        }

        uint32 Encounter[ENCOUNTERS];

        uint64 uiAnshal;
        uint64 uiNezir;
        uint64 uiRohash;

        uint64 uiAlakir;

        uint64 AnshalPlatform;
        uint64 NezirPlatform;
        uint64 RohashPlatform;
        uint64 SkyWallRaid;
        uint64 SkyWallWind;
        uint64 HeartOfWindGUID;

        uint8 GatheringStrength;
        uint8 WeatherData;
        uint8 AlakirFlightData;


        void Initialize()
        {
            for (uint8 i = 0; i < ENCOUNTERS; ++i)
                Encounter[i] = NOT_STARTED;

            uiAnshal = 0;
            uiNezir = 0;
            uiRohash = 0;
            uiAlakir = 0;
            GatheringStrength = 0;
            WeatherData = 0;
            AlakirFlightData = 0;

            AnshalPlatform = NezirPlatform = RohashPlatform = 0;
            SkyWallRaid = SkyWallWind = HeartOfWindGUID = 0;
        }

        void Update(uint32 diff)
        { }

        void OnPlayerEnter(Player* player)
        {
            if (GetData(DATA_ALAKIR_EVENT) == DONE)
            {
                player->CastSpell(player, SPELL_EYE_OF_THE_STORM, true);
            }
        }

        bool IsEncounterInProgress() const
        {
            for (uint8 i = 0; i < ENCOUNTERS; ++i)
            {
                if (Encounter[i] == IN_PROGRESS)
                    return true;
            }
            return false;
        }

        void OnGameObjectCreate(GameObject* go)
        {
            switch (go->GetEntry())
            {
            case GO_NAZIR_PLATFORM:
                NezirPlatform = go->GetGUID();
                go->setActive(true);
                break;
            case GO_ANSHAL_PLATFORM:
                AnshalPlatform = go->GetGUID();
                go->setActive(true);
                break;
            case GO_ROHASH_PLATFORM:
                RohashPlatform = go->GetGUID();
                go->setActive(true);
                break;
            case GO_SKYWALL_RAID:
                SkyWallRaid = go->GetGUID();
                go->setActive(true);
                break;
            case GO_SKYWALL_WIND:
                SkyWallWind = go->GetGUID();
                go->setActive(true);
                break;
            case GO_HEART_OF_WIND_10:
                if (instance->GetDifficulty() == RAID_DIFFICULTY_10MAN_NORMAL)
                    HeartOfWindGUID = go->GetGUID();
                break;
            case GO_HEART_OF_WIND_25:
                if (instance->GetDifficulty() == RAID_DIFFICULTY_25MAN_NORMAL)
                    HeartOfWindGUID = go->GetGUID();
                break;
            }
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
            case BOSS_ANSHAL:
                uiAnshal = creature->GetGUID();
                break;
            case BOSS_NEZIR:
                uiNezir = creature->GetGUID();
                break;
            case BOSS_ROHASH:
                uiRohash = creature->GetGUID();
                break;
            case BOSS_ALAKIR:
                uiAlakir = creature->GetGUID();
                if (GetData(DATA_CONCLAVE_OF_WIND_EVENT) == DONE)
                    SummonSplistreamAlakir();
                break;
            }
        }

        uint64 GetData64(uint32 identifier) const
        {
            switch (identifier)
            {
            case DATA_ANSHAL:
                return uiAnshal;
            case DATA_NEZIR:
                return uiNezir;
            case DATA_ROHASH:
                return uiRohash;
            case DATA_ALAKIR:
                return uiAlakir;
            }
            return 0;
        }

        void SetData(uint32 type, uint32 data)
        {
            switch (type)
            {
            case DATA_GATHERING_STRENGTH:
                GatheringStrength = data;
                break;
            case DATA_CONCLAVE_OF_WIND_EVENT:
                switch (data)
                {
                case IN_PROGRESS:
                    if (Creature* Anshal = instance->GetCreature(uiAnshal))
                    {
                        if (Anshal->IsAlive())
                        {
                            Anshal->SetInCombatWithZone();
                            SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, Anshal);
                        }
                    }
                    if (Creature* Nezir = instance->GetCreature(uiNezir))
                    {
                        if (Nezir->IsAlive())
                        {
                            Nezir->SetInCombatWithZone();
                            SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, Nezir);
                        }
                    }
                    if (Creature* Rohash = instance->GetCreature(uiRohash))
                    {
                        if (Rohash->IsAlive())
                        {
                            Rohash->SetInCombatWithZone();
                            SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, Rohash);
                        }
                    }
                    break;

                case FAIL:
                    if (Creature* Anshal = instance->GetCreature(uiAnshal))
                    {
                        SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, Anshal);
                        Anshal->Respawn(true);
                    }
                    if (Creature* Nezir = instance->GetCreature(uiNezir))
                    {
                        SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, Nezir);
                        Nezir->Respawn(true);
                    }
                    if (Creature* Rohash = instance->GetCreature(uiRohash))
                    {
                        SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, Rohash);
                        Rohash->Respawn(true);
                    }
                    break;

                case DONE:
                    bool achievementReadytoGet = CheckAchivementStayChill();

                    if (Creature* Anshal = instance->GetCreature(uiAnshal))
                    {
                        Anshal->LowerPlayerDamageReq(Anshal->GetMaxHealth());
                        SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, Anshal);
                        if (Anshal->IsAlive())
                        {
                            if (achievementReadytoGet == true)
                                Anshal->CastSpell(Anshal, SPELL_STAY_CHILL_ACHIEVEMENT_CREDIT, true);
                            if (Player* pPlayer = Anshal->FindNearestPlayer(1000, true))
                                pPlayer->DealDamage(Anshal, Anshal->GetHealth());
                        }
                    }
                    if (Creature* Nezir = instance->GetCreature(uiNezir))
                    {
                        Nezir->LowerPlayerDamageReq(Nezir->GetMaxHealth());
                        SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, Nezir);
                        if (Nezir->IsAlive())
                        {
                            if (achievementReadytoGet == true)
                                Nezir->CastSpell(Nezir, SPELL_STAY_CHILL_ACHIEVEMENT_CREDIT, true);
                            if (Player* pPlayer = Nezir->FindNearestPlayer(1000, true))
                                pPlayer->DealDamage(Nezir, Nezir->GetHealth());
                        }
                    }
                    if (Creature* Rohash = instance->GetCreature(uiRohash))
                    {
                        Rohash->LowerPlayerDamageReq(Rohash->GetMaxHealth());
                        SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, Rohash);
                        if (Rohash->IsAlive())
                        {
                            if (achievementReadytoGet == true)
                                Rohash->CastSpell(Rohash, SPELL_STAY_CHILL_ACHIEVEMENT_CREDIT, true);
                            if (Player* pPlayer = Rohash->FindNearestPlayer(1000, true))
                                pPlayer->DealDamage(Rohash, Rohash->GetHealth());
                        }
                    }
                    SummonSplistreamAlakir();

                    break;
                }
                Encounter[0] = data;
                break;
            case DATA_ALAKIR_EVENT:
                switch (data)
                {
                case DONE:
                    DoRespawnGameObject(HeartOfWindGUID, 7*DAY);

                    Map::PlayerList const &players = instance->GetPlayers();
                    if (players.isEmpty())
                        break;

                    for (Map::PlayerList::const_iterator i = players.begin(); i != players.end(); ++i)
                    {
                        if (Player* player = i->GetSource())
                        {
                            player->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE, BOSS_ALAKIR, 1);
                            player->ModifyCurrency(CURRENCY_TYPE_VALOR_POINTS, 70, true);
                        }
                    }
                    break;
                }
                Encounter[1] = data;
                break;
            case DATA_WEATHER_EVENT:
                WeatherData = data;
                break;
            case DATA_ALAKIR_FLIGHT_PHASE:
                if (data == NOT_STARTED)
                {
                    if (GameObject* go = instance->GetGameObject(AnshalPlatform))
                        if (GameObject* go = instance->GetGameObject(NezirPlatform))
                            if (GameObject* go = instance->GetGameObject(RohashPlatform))
                                if (GameObject* go = instance->GetGameObject(SkyWallRaid))
                                {
                                    go->SetGoState(GO_STATE_READY);
                                }
                }

                if (data == IN_PROGRESS)
                {
                    if (GameObject* go = instance->GetGameObject(SkyWallRaid))
                        go->SetDestructibleState(GO_DESTRUCTIBLE_DESTROYED);
                }

                if (data == FAIL)
                {
                    if (GameObject* go = instance->GetGameObject(SkyWallRaid))
                        go->SetDestructibleState(GO_DESTRUCTIBLE_REBUILDING);
                }

                if (data == DONE)
                {
                    if (GameObject* go = instance->GetGameObject(SkyWallWind))
                        go->Delete();
                }
                AlakirFlightData = data;
                break;
            }

            if (data == DONE)
                SaveToDB();

            if (data == IN_PROGRESS)
            {
                if (Creature* Anshal = instance->GetCreature(uiAnshal))
                    Anshal->RemoveAura(SPELL_PRE_COMBAT_EFFECT_ANSHAL);

                if (Creature* Nezir = instance->GetCreature(uiNezir))
                    Nezir->RemoveAura(SPELL_PRE_COMBAT_EFFECT_NEZIR);

                if (Creature* Rohash = instance->GetCreature(uiRohash))
                    Rohash->RemoveAura(SPELL_PRE_COMBAT_EFFECT_ROHASH);

            }
            else if (data == FAIL || data == NOT_STARTED)
            {
                if (Creature* Anshal = instance->GetCreature(uiAnshal))
                    if (!Anshal->HasAura(SPELL_PRE_COMBAT_EFFECT_ANSHAL))
                        Anshal->CastSpell(Anshal, SPELL_PRE_COMBAT_EFFECT_ANSHAL, true);

                if (Creature* Nezir = instance->GetCreature(uiNezir))
                    if (!Nezir->HasAura(SPELL_PRE_COMBAT_EFFECT_NEZIR))
                        Nezir->CastSpell(Nezir, SPELL_PRE_COMBAT_EFFECT_NEZIR, true);

                if (Creature* Rohash = instance->GetCreature(uiRohash))
                    if (!Rohash->HasAura(SPELL_PRE_COMBAT_EFFECT_ROHASH))
                        Rohash->CastSpell(Rohash, SPELL_PRE_COMBAT_EFFECT_ROHASH, true);
            }
        }

        bool SetBossState(uint32 id, EncounterState state)
        {
            if (!InstanceScript::SetBossState(id, state))
                return false;

            return true;
        }

        uint32 GetData(uint32 type) const
        {
            switch (type)
            {
            case DATA_CONCLAVE_OF_WIND_EVENT:
                return Encounter[0];
            case DATA_ALAKIR_EVENT:
                return Encounter[1];
            case DATA_GATHERING_STRENGTH:
                return GatheringStrength;
            case DATA_WEATHER_EVENT:
                return WeatherData;
            case DATA_ALAKIR_FLIGHT_PHASE:
                return AlakirFlightData;
            }
            return 0;
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::string str_data;
            std::ostringstream saveStream;
            saveStream << "T W" << Encounter[0] << " " << Encounter[1];
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
            uint16 data0, data1;

            std::istringstream loadStream(in);
            loadStream >> dataHead1 >> dataHead2 >> data0 >> data1;

            if (dataHead1 == 'T' && dataHead2 == 'W')
            {
                Encounter[0] = data0;
                Encounter[1] = data1;

                for (uint8 i = 0; i < ENCOUNTERS; ++i)
                    if (Encounter[i] == IN_PROGRESS)
                        Encounter[i] = NOT_STARTED;
            }
            else OUT_LOAD_INST_DATA_FAIL;

            OUT_LOAD_INST_DATA_COMPLETE;
        }

        bool CheckAchivementStayChill()
        {
            uint32 spellid = GetSpellWindChill();
            Map::PlayerList const& players = instance->GetPlayers();
            if (!players.isEmpty())
            {
                for (Map::PlayerList::const_iterator i = players.begin(); i != players.end(); ++i)
                {
                    if (Player* player = i->GetSource())
                    {
                        if (Aura* aur = player->GetAura(spellid))
                        {
                            if (aur->GetStackAmount() < 7)
                                return false;
                        }
                        else
                            return false;
                    }
                }
                return true;
            }
            return false;
        }

        uint32 GetSpellWindChill()
        {
            switch(instance->GetDifficulty())
            {
            case RAID_DIFFICULTY_10MAN_NORMAL:
                return SPELL_WIND_CHILL_10;
            case RAID_DIFFICULTY_25MAN_NORMAL:
                return SPELL_WIND_CHILL_25;
            case RAID_DIFFICULTY_10MAN_HEROIC:
                return SPELL_WIND_CHILL_10H;
            case RAID_DIFFICULTY_25MAN_HEROIC:
                return SPELL_WIND_CHILL_25H;
            }
            return 0;
        }

        void SummonSplistreamAlakir()
        {
            for (int i = 0; i < 4; ++i)
                instance->SummonCreature(NPC_SLIPSTREAM_ALAKIR, AlakirSlipstreamPositions[i]);
        }
    };
};

// 6281
class AreaTrigger_at_return_wind : public AreaTriggerScript
{
public:
    AreaTrigger_at_return_wind() : AreaTriggerScript("at_return_wind") { }

    bool OnTrigger(Player* player, AreaTriggerEntry const* /*trigger*/)
    {
        InstanceScript* instance = player->GetInstanceScript();
        if (instance)
        {
            if (player->IsAlive())
            {
                if (instance->GetData(DATA_ALAKIR_EVENT) != IN_PROGRESS)
                {
                    float smallestDist = player->GetDistance2d(GoBackPositions[0].GetPositionX(), GoBackPositions[0].GetPositionY());
                    int PointToGo = 0;
                    for (int i = 0; i < 8; i++)
                    {
                        float distance = player->GetDistance2d(GoBackPositions[i].GetPositionX(), GoBackPositions[i].GetPositionY());
                        if (distance < smallestDist)
                        {
                            smallestDist = distance;
                            PointToGo = i;
                        }
                    }
                    player->GetMotionMaster()->MoveJump(GoBackPositions[PointToGo], 50, 10);
                    player->AddAura(SPELL_SLIPSTREAM_BUFF, player);
                    player->AddAura(SPELL_SLIPSTREAM_PLAYER_VISUAL, player);
                }
                else if (instance->GetData(DATA_ALAKIR_EVENT) == IN_PROGRESS && (instance->GetData(DATA_ALAKIR_FLIGHT_PHASE) == NOT_STARTED || instance->GetData(DATA_ALAKIR_FLIGHT_PHASE) == FAIL))
                {
                    if (player->HasAura(SPELL_RELENTLESS_STORM_VISUAL))
                        return false;

                    player->CastSpell(player, SPELL_RELENTLESS_STORM_VISUAL, true);
                    float speedFly = (210.0f - player->GetPositionZ()) / 15;
                    player->GetMotionMaster()->MoveJump(player->GetPositionX(), player->GetPositionY(), 220.0f, speedFly, speedFly);
                }
            }
        }

        return true;
    }
};

void AddSC_instance_throne_of_the_four_winds()
{
    new instance_throne_of_the_four_winds();
    new AreaTrigger_at_return_wind();
}
