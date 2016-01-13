/*
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
 *
 * This file is NOT free software. Third-party users can NOT redistribute
 * it or modify it. If you find it, you are either hacking something, or very
 * lucky (presuming someone else managed to hack it).
 */

/* ScriptData
SDName: Instance dragon soul
SD%Complete: 100%
SDComment:
SDCategory: Instance
EndScriptData
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "dragon_soul.h"
#include "Map.h"
#include "Player.h"

class instance_dragon_soul : public InstanceMapScript
{
public:
    instance_dragon_soul() : InstanceMapScript("instance_dragon_soul", 967) { }

    struct instance_dragon_soul_InstanceMapScript : public InstanceScript
    {
        instance_dragon_soul_InstanceMapScript(InstanceMap* map) : InstanceScript(map) { }
        // Creatures
        uint64 MorchokGUID;
        uint64 UnsleepingGUID;
        uint64 WarlordGUID;
        uint64 HagaraGUID;
        uint64 UltraxionGUID;
        uint64 WarmasterGUID;
        uint64 PortalGUID;

        uint64 Maelstrom_trall;
        uint64 Maelstrom_kalecgos;
        uint64 Maelstrom_ysera;
        uint64 Maelstrom_nozdormy;
        uint64 Maelstrom_alexstrasza;

        uint64 Aspect_Of_MagicGUID;
        uint64 AlexstraszaGUID;
        uint64 YseraGUID;
        uint64 NozdormuGUID;
        uint64 Trall_Vs_UltraxionGUID;
        uint64 DeathwingGUID;
        uint64 arm_tentacle_1;
        uint64 arm_tentacle_2;
        uint64 wing_tentacle_1;
        uint64 wing_tentacle_2;

        void Initialize()
        {
            SetBossNumber(MAX_ENCOUNTER);
            MorchokGUID = 0;
            UnsleepingGUID = 0;
            WarlordGUID = 0;
            HagaraGUID = 0;
            UltraxionGUID = 0;
            WarmasterGUID = 0;
            PortalGUID = 0;

            Maelstrom_trall = 0;
            Maelstrom_kalecgos = 0;
            Maelstrom_ysera = 0;
            Maelstrom_nozdormy = 0;
            Maelstrom_alexstrasza = 0;

            Aspect_Of_MagicGUID = 0;
            AlexstraszaGUID = 0;
            YseraGUID = 0;
            NozdormuGUID = 0;
            Trall_Vs_UltraxionGUID = 0;
            DeathwingGUID = 0;
            arm_tentacle_1 = 0;
            arm_tentacle_2 = 0;
            wing_tentacle_1 = 0;
            wing_tentacle_2 = 0;
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
            case NPC_MORCHOK:
                MorchokGUID = creature->GetGUID();
                break;
            case NPC_WARLORD:
                UnsleepingGUID = creature->GetGUID();
                break;
            case NPC_UNSLEEPING:
                WarlordGUID = creature->GetGUID();
                break;
            case NPC_HAGARA:
                HagaraGUID = creature->GetGUID();
                break;
            case NPC_ULTRAXION:
                UltraxionGUID = creature->GetGUID();
                break;
            case NPC_WARMASTER:
                WarmasterGUID = creature->GetGUID();
                break;
            case NPC_PORTAL:
                PortalGUID = creature->GetGUID();
                break;
            case NPC_TRALL_VS_ULTRAXION:
                Trall_Vs_UltraxionGUID = creature->GetGUID();
                break;
            case NPC_ALEXSTRASZA:
                AlexstraszaGUID = creature->GetGUID();
                break;
            case NPC_YSERA:
                YseraGUID = creature->GetGUID();
                break;
            case NPC_NOZDORMU:
                NozdormuGUID = creature->GetGUID();
                break;
            case NPC_ASPECT_OF_MAGIC:
                Aspect_Of_MagicGUID = creature->GetGUID();
                break;
            case NPC_MAELSTROM_TRALL:
                Maelstrom_trall = creature->GetGUID();
                break;
            case NPC_MAELSTROM_KALECGOS:
                Maelstrom_kalecgos = creature->GetGUID();
                break;
            case NPC_MAELSTROM_YSERA:
                Maelstrom_ysera = creature->GetGUID();
                break;
            case NPC_MAELSTROM_NOZDORMY:
                Maelstrom_nozdormy = creature->GetGUID();
                break;
            case NPC_MAELSTROM_ALEXSTRASZA:
                Maelstrom_alexstrasza = creature->GetGUID();
                break;
            case NPC_DEATHWING_1:
                DeathwingGUID = creature->GetGUID();
                break;
            case NPC_ARM_TENTACLE_1:
                arm_tentacle_1 = creature->GetGUID();
                break;
            case NPC_ARM_TENTACLE_2:
                arm_tentacle_2 = creature->GetGUID();
                break;
            case NPC_WING_TENTACLE_1:
                wing_tentacle_1 = creature->GetGUID();
                break;
            case NPC_WING_TENTACLE_2:
                wing_tentacle_2 = creature->GetGUID();
                break;
            }
        }

        void SetData(uint32 type, uint32 data)
        {
            switch (type)
            {
            case DATA_DAMAGE_DEATHWING:
                if (data == DONE)
                    if (Creature* creature = instance->GetCreature(DeathwingGUID))
                        creature->CastSpell(creature, 106548);
                SaveToDB();
                break;
            case DATA_ATTACK_DEATHWING:
            {
                switch (data)
                {
                case IN_PROGRESS:
                    if (Creature* creature = instance->GetCreature(arm_tentacle_1))
                    {
                        creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                        creature->SetVisible(true);
                    }
                    if (Creature* creature = instance->GetCreature(arm_tentacle_2))
                    {
                        creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                        creature->SetVisible(true);
                    }
                    if (Creature* creature = instance->GetCreature(wing_tentacle_1))
                    {
                        creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                        creature->SetVisible(true);
                    }
                    if (Creature* creature = instance->GetCreature(wing_tentacle_2))
                    {
                        creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                        creature->SetVisible(true);
                    }
                    break;
                }
                SaveToDB();
                break;
            }
            default:
                break;
            }
        }

        uint64 GetData64(uint32 identifier) const
        {
            switch (identifier)
            {
            case NPC_MAELSTROM_TRALL:
                return Maelstrom_trall;
            case NPC_DEATHWING_1:
                return DeathwingGUID;
            }

            return 0;
        }

        bool SetBossState(uint32 type, EncounterState state)
        {
            if (!InstanceScript::SetBossState(type, state))
                return false;

            switch (type)
            {
            case BOSS_MORCHOK:
            case BOSS_WARLORD:
            case BOSS_UNSLEEPING:
            case BOSS_HAGARA:
            case BOSS_WARMASTER:
            case BOSS_DEATHWING:
                break;
            case BOSS_ULTRAXION:
                if (state == DONE)
                    if (Creature* creature = instance->GetCreature(Trall_Vs_UltraxionGUID))
                        creature->SummonCreature(NPC_TRAVEL_TO_THE_DECK_OF_THE_SKYFIRE, -1802.141f, -2364.638f, 340.796f, 5.234f, TEMPSUMMON_CORPSE_DESPAWN, 900000);
                break;
            case DATA_TRALL_VS_ULTRAXION:
                switch (state)
                {
                case DONE:
                    if (Creature* creature = instance->GetCreature(Trall_Vs_UltraxionGUID))
                    {
                        creature->AddAura(LAST_DEFENDER_OF_AZEROTH, creature);
                        creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    }
                    if (Creature* creature = instance->GetCreature(AlexstraszaGUID))
                        creature->CastSpell(creature, GIFT_OF_LIFE);
                    if (Creature* creature = instance->GetCreature(YseraGUID))
                        creature->CastSpell(creature, ESSENCE_OF_DREAMS);
                    if (Creature* creature = instance->GetCreature(NozdormuGUID))
                        creature->AddAura(TIMELOOP, creature);
                    if (Creature* creature = instance->GetCreature(Aspect_Of_MagicGUID))
                        creature->CastSpell(creature, SOURCE_OF_MAGIC);
                case FAIL:
                    DoRemoveAurasDueToSpellOnPlayers(105554);
                    DoRemoveAurasDueToSpellOnPlayers(106368);
                    DoRemoveAurasDueToSpellOnPlayers(LAST_DEFENDER_OF_AZEROTH);
                    DoRemoveAurasDueToSpellOnPlayers(TIMELOOP);
                    DoRemoveAurasDueToSpellOnPlayers(SOURCE_OF_MAGIC);
                    DoRemoveAurasDueToSpellOnPlayers(ESSENCE_OF_DREAMS);
                    DoRemoveAurasDueToSpellOnPlayers(GIFT_OF_LIFE);
                    break;
                default:
                    break;
                }
                break;
            case DATA_PORTALS_ON_OFF:
                break;
            }

            return true;
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "D S " << GetBossSaveData();

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

            if (dataHead1 == 'D' && dataHead2 == 'S')
            {
                for (uint32 i = 0; i < MAX_ENCOUNTER; ++i)
                {
                    uint32 tmpState;
                    loadStream >> tmpState;
                    if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                        tmpState = NOT_STARTED;

                    SetBossState(i, EncounterState(tmpState));
                }
            }

            OUT_LOAD_INST_DATA_COMPLETE;
        }
    };

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_dragon_soul_InstanceMapScript(map);
    }
};

void AddSC_instance_dragon_soul()
{
    new instance_dragon_soul();
}