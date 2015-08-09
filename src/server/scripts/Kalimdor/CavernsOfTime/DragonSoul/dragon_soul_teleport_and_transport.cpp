/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * This file is NOT free software. Third-party users can NOT redistribute
 * it or modify it. If you find it, you are either hacking something, or very
 * lucky (presuming someone else managed to hack it).
 */

/* ScriptData
SDName: dragon_soul_teleport_and_transport
SD%Complete: 100%
SDComment:
SDCategory: Teleport and Transport
EndScriptData
*/

#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "dragon_soul.h"
#include "Vehicle.h"
#include "CombatAI.h"

// 57288
class npc_eiendormi : public CreatureScript
{
public:
    npc_eiendormi() : CreatureScript("npc_eiendormi") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (InstanceScript* instance = creature->GetInstanceScript())
        {
            if (instance->GetBossState(BOSS_MORCHOK) == DONE)
            {
                player->TeleportTo(967, -1870.114f, -3077.727f, -176.308f, 0.390f);
                //if (Creature *t = player->SummonCreature(572880, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(),
                //player->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 300 * IN_MILLISECONDS))
                //player->CastCustomSpell(VEHICLE_SPELL_RIDE_HARDCODED, SPELLVALUE_BASE_POINT0, 1, t, false);
            }
        }

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }
};

// 57630
class npc_halo_jump_parachute_57630 : public CreatureScript
{
public:
    npc_halo_jump_parachute_57630() : CreatureScript("npc_halo_jump_parachute_57630") { }

    enum eWarden
    {
        SPELL_FORCE_SUMONER_TO_RIDE_VEHICLE = 108583,
        SPELL_RIDE_DRAKE = 108582,
        SPELL_HALO_JUMP = 108774,
        SPELL_PULL_THE_RIPCORD = 108689,
        SPELL_EJECT_ALL_PASSENGERS = 50630,

        NPC_HALO_JUMP_PARASCHUT = 57630,

        EVENT_FREE_FALL = 1,
        EVENT_USE_RIPCORD,
        EVENT_EJECT_ALL_PASSENGERS,
    };

    struct npc_halo_jump_parachute_57630AI : public VehicleAI
    {
        npc_halo_jump_parachute_57630AI(Creature* creature) : VehicleAI(creature), m_instance(creature->GetInstanceScript()) { }

        EventMap m_events;
        InstanceScript* m_instance;
        Player* m_player;
        uint64 m_vehicleGuid;
        uint32 m_counter;

        void Reset() override
        {
            m_events.Reset();
            m_player = NULL;
            m_vehicleGuid = 0;
            m_counter = 0;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            m_player = caster->ToPlayer();                      
        }

        void PassengerBoarded(Unit* unit, int8 seat, bool apply) override
        {
            m_player = unit->ToPlayer();
            if (m_player && apply)
            {
                me->CastSpell(me, SPELL_EJECT_ALL_PASSENGERS, true);
                m_events.ScheduleEvent(EVENT_USE_RIPCORD, 5000);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);
            
            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_USE_RIPCORD:
                    {
                        if (m_player)
                            if (Creature* npc = FindTarget())
                            {
                                // m_player->SetTarget(npc->GetGUID());
                                // m_player->CastSpell(m_player, SPELL_PULL_THE_RIPCORD, true);
                                me->ExitVehicle();
                                me->DespawnOrUnsummon(1000);
                                m_player->NearTeleportTo(-1746.6f, -1849.3f, -221.72f, 4.406f);
                            }

                        break;
                    }
                }
            }
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

        void DoWork() // only memo
        {
            // Player* player = sObjectAccessor->FindPlayer(m_playerGuid);

            // Creature* vehicle = Unit::GetCreature(*me, m_vehicleGuid);
            // Player* player = Unit::GetPlayer(*me, m_playerGuid);

            // No defined handler for opcode[CMSG_MOVE_GRAVITY_ENABLE_ACK 0x700A (28682)] sent by[Player:Mepal(Guid : 11, Account : 1)]
        }

        Creature* FindTarget()
        {
            std::list<Creature*> crs = me->FindNearestCreatures(53488, 250.0f);

            if (!crs.empty())
                for (std::list<Creature*>::const_iterator itr = crs.begin(); itr != crs.end(); ++itr)
                {
                    if ((*itr)->GetDBTableGUIDLow() == 268506)
                        return *itr;
                }

            return NULL;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<npc_halo_jump_parachute_57630AI>(creature);
    }

};

// 57475
class npc_dream_warden_57475 : public CreatureScript
{
public:
    npc_dream_warden_57475() : CreatureScript("npc_dream_warden_57475") { }

    enum eWarden
    {
        SPELL_FORCE_SUMONER_TO_RIDE_VEHICLE = 108583,
        SPELL_RIDE_DRAKE = 108582,
        SPELL_RIDE_PARACHUTE = 108582,
        SPELL_HALO_JUMP = 108774,
        SPELL_PULL_THE_RIPCORD = 108689,
        SPELL_EJECT_ALL_PASSENGERS = 50630,

        NPC_HALO_JUMP_PARACHUTE = 57630,
        EVENT_FREE_FALL = 1,
        EVENT_DELETE_VEHICLE = 2,
    };

    struct npc_dream_warden_57475AI : public ScriptedAI
    {
        npc_dream_warden_57475AI(Creature* creature) : ScriptedAI(creature), m_instance(creature->GetInstanceScript()) { }

        EventMap m_events;
        InstanceScript* m_instance;
        uint64 m_playerGuid;
        uint64 m_vehicleGuid;

        void Reset() override
        {
            m_events.Reset();
            m_playerGuid = 0;
            m_vehicleGuid = 0;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (spell->Id == SPELL_RIDE_DRAKE)
            {
                me->SetSpeed(MOVE_RUN, 4.5f);
                me->GetMotionMaster()->MovePath(5747501, false);
            }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type != WAYPOINT_MOTION_TYPE)
                return;
        
            if (id == 3)
            {
                if (Vehicle* vehicle = me->GetVehicleKit())
                    if (Unit* unit = vehicle->GetPassenger(0))
                        if (Player* player = unit->ToPlayer())
                        {
                            m_playerGuid = player->GetGUID();
                            me->CastSpell(me, SPELL_EJECT_ALL_PASSENGERS);
                            me->CastSpell(player, SPELL_HALO_JUMP, true);
                            me->DespawnOrUnsummon(20000);
                        }
            }
        }

        void JustSummoned(Creature* summon) override
        {
            if (summon->GetEntry() == NPC_HALO_JUMP_PARACHUTE)
                if (Player* player = Unit::GetPlayer(*me, m_playerGuid))
                {
                    m_vehicleGuid = summon->GetGUID();
                    summon->SetDisplayId(11686);
                    summon->DespawnOrUnsummon(20000);
                    player->CastSpell(summon, SPELL_RIDE_PARACHUTE, true);
                }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_FREE_FALL:
                        {
                        }
                    case EVENT_DELETE_VEHICLE:
                    {
                    }
                }
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<npc_dream_warden_57475AI>(creature);
    }

};

// 57289
class npc_valeera_tele_57289 : public CreatureScript
{
public:
    npc_valeera_tele_57289() : CreatureScript("npc_valeera_tele_57289") { }

    enum eValeera
    {
        SPELL_SUMMON_DRAKE_57475 = 108651, 
        SPELL_FORCE_SUMMONER_TO_RIDE_VEHICLE=108583,
        SPELL_RIDE_DRAKE = 108582,
    };

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (InstanceScript* instance = creature->GetInstanceScript())
        {
            if (instance->GetBossState(BOSS_MORCHOK) == DONE)
            {
                CAST_AI(npc_valeera_tele_57289AI, creature->GetAI())->SummonDrake(player);
                player->CLOSE_GOSSIP_MENU();
                return true;
            }
        }

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    struct npc_valeera_tele_57289AI : public ScriptedAI
    {
        npc_valeera_tele_57289AI(Creature* creature) : ScriptedAI(creature), m_instance(creature->GetInstanceScript()) { }

        InstanceScript* m_instance;
        Player* m_player;
       
        void Reset() override
        {
            m_player = NULL;
        }

        void JustSummoned(Creature* summon) override
        { 
            if (m_player)
            {
                summon->CastSpell(summon, SPELL_FORCE_SUMMONER_TO_RIDE_VEHICLE, true, 0, 0, m_player->GetGUID());
                m_player->CastSpell(summon, SPELL_RIDE_DRAKE, true);
            }
        }

        void SummonDrake(Player* player)
        {
            m_player = player;
            me->CastSpell(player, SPELL_SUMMON_DRAKE_57475, false);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<npc_valeera_tele_57289AI>(creature);
    }

};

// 57287
class npc_nethestrasz : public CreatureScript
{
public:
    npc_nethestrasz() : CreatureScript("npc_nethestrasz") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (InstanceScript* instance = creature->GetInstanceScript())
        {
            if (instance->GetBossState(BOSS_UNSLEEPING) == DONE && instance->GetBossState(BOSS_WARLORD) == DONE)
            {
                player->TeleportTo(967, -1786.69f, -2393.67f, 341.355f, 0.16f);
                //if (Creature *t = player->SummonCreature(572870, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(),
                //player->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 300 * IN_MILLISECONDS))
                //player->CastCustomSpell(VEHICLE_SPELL_RIDE_HARDCODED, SPELLVALUE_BASE_POINT0, 1, t, false);
            }
        }

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }
};

// 57882
class travel_to_wyrmrest_base : public CreatureScript
{
public:
    travel_to_wyrmrest_base() : CreatureScript("travel_to_wyrmrest_base") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (InstanceScript* instance = creature->GetInstanceScript())
        {
            if (instance->GetBossState(DATA_PORTALS_ON_OFF) == DONE)
            {
                player->TeleportTo(967, -1793.22f, -2391.78f, 45.604f, 5.871f);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            }
        }

        player->CLOSE_GOSSIP_MENU();
        return true;
    }
};

// 57379
class travel_to_wyrmrest_summit : public CreatureScript
{
public:
    travel_to_wyrmrest_summit() : CreatureScript("travel_to_wyrmrest_summit") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (InstanceScript* instance = creature->GetInstanceScript())
        {
            if (instance->GetBossState(DATA_PORTALS_ON_OFF) == DONE)
            {
                player->TeleportTo(967, -1786.92f, -2393.18f, 341.355f, 6.141f);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            }
        }

        player->CLOSE_GOSSIP_MENU();
        return true;
    }
};

// 57377
class travel_to_the_eye_of_eternity : public CreatureScript
{
public:
    travel_to_the_eye_of_eternity() : CreatureScript("travel_to_the_eye_of_eternity") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (InstanceScript* instance = creature->GetInstanceScript())
        {
            if (instance->GetBossState(BOSS_UNSLEEPING) == DONE && instance->GetBossState(BOSS_WARLORD) == DONE)
            {
                player->TeleportTo(967, 13629.7f, 13611.9f, 123.482f, 3.468f);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            }
        }

        player->CLOSE_GOSSIP_MENU();
        return true;
    }
};

// 57378
class travel_to_the_deck_of_the_skyfire : public CreatureScript
{
public:
    travel_to_the_deck_of_the_skyfire() : CreatureScript("travel_to_the_deck_of_the_skyfire") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (InstanceScript* instance = creature->GetInstanceScript())
        {
            if (instance->GetBossState(BOSS_ULTRAXION) == DONE)
            {
                player->TeleportTo(967, 13397.298f, -12131.405f, 153.8732f, 3.152f);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            }
        }

        player->CLOSE_GOSSIP_MENU();
        return true;
    }
};

// ????
class travel_to_spine : public CreatureScript
{
public:
    travel_to_spine() : CreatureScript("travel_to_Spine") { }
    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (InstanceScript* instance = creature->GetInstanceScript())
        {
            if (instance->GetBossState(BOSS_WARMASTER) == DONE)
            {
                player->TeleportTo(967, -13855.28f, -13667.97f, 268.03f, 1.64f);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            }
        }
        player->CLOSE_GOSSIP_MENU();
        return true;
    }
};

// 57443
class travel_to_maelstrom : public CreatureScript
{
public:
    travel_to_maelstrom() : CreatureScript("travel_to_maelstrom") { }
    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (InstanceScript* instance = creature->GetInstanceScript())
        {
            if (instance->GetBossState(BOSS_ULTRAXION) == DONE)  //Need Spine Done
            {
                player->TeleportTo(967, -12120.15f, -12175.022f, 2.56f, 5.77f);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            }
        }
        player->CLOSE_GOSSIP_MENU();
        return true;
    }
};

void AddSC_dragon_soul_teleport_and_transport()
{
    new npc_eiendormi();
    new npc_halo_jump_parachute_57630();
    new npc_dream_warden_57475();
    new npc_valeera_tele_57289();
    new npc_nethestrasz();
    new travel_to_wyrmrest_base;
    new travel_to_wyrmrest_summit;
    new travel_to_the_eye_of_eternity;
    new travel_to_the_deck_of_the_skyfire;
    // new travel_to_spine;
    new travel_to_maelstrom;
}