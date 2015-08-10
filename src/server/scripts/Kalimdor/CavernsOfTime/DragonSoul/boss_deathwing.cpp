/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * This file is NOT free software. Third-party users can NOT redistribute
 * it or modify it. If you find it, you are either hacking something, or very
 * lucky (presuming someone else managed to hack it).
 */

/* ScriptData
SDName: boss_deathwing
SD%Complete: 50%
SDComment:
SDCategory: Boss Deathwing
EndScriptData
*/

#include "ScriptPCH.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "dragon_soul.h"
#include "Vehicle.h"
#include "InstanceScript.h"
#include "Map.h"

#define TRALL_MENU "We are ready!"
#define TELE_MENU_1 "1st Area"
#define TELE_MENU_2 "2nd Area"
#define TELE_MENU_3 "3nd Area"
#define TELE_MENU_4 "4nd Area"

enum Events
{
    // Deathwing
    EVENT_ASSAULT_ASPECTS = 1,
    EVENT_CATACLYSM,
    EVENT_CORRUPTING_PARASITE,
    EVENT_ELEMENTIUM_BOLT,

    //tentacle
    EVENT_AGONUZUNG_PAIN,

    //other
    EVENT_SUMMON,
    EVENT_SUMMON_1,
    ATTACK_START,

    //Phase
    PHASE_1,
    PHASE_2,
    HAS_20PROCENT_HEALTH_NEW_PHASE,

    //Phase 2
    EVENT_ELEMENTIUM_FRAGMENT,
    EVENT_ELEMENTIUM_TERROR,
    EVENT_CORRUPTED_BLOOD,
    EVENT_CONGEALING_BLOOD,

    //Phase 2 mob events
    EVENT_SHRAPNEL,
    EVENT_TETANUS,
    EVENT_CONGEALING_BLOOD_CAST,

    //trall
    EVENT_SAY_TRALL_START,
    EVENT_SAY_TRALL_1,
};

enum Spells
{
    //DeathWing
    SPELL_ASSAULT_ASPECTS = 107018,
    SPELL_CATACLYSM = 106523,
    SPELL_CORRUPTING_PARASITE = 108649,
    SPELL_ELEMENTIUM_BOLT = 105651,

    // Mutated corruption
    SPELL_IMPALE = 106400,
    SPELL_IMPALE_ASPECT = 107029,

    // tentacle
    SPELL_BURNING_BLODD = 105401,
    SPELL_AGONUZUNG_PAIN = 106548,
    SPELL_CRUSH = 106385,

    // Phase 2
    SPELL_CONGEALING_BLOOD = 109102,
    SPELL_SHRAPNEL = 106791,
    SPELL_TETANUS = 106728,
    SPELL_CORRUPTED_BLOOD = 106835,

    SPELL_PLAY_MOVIE = 110112,
};

enum Texts
{
    //trall
    SAY_TRALL_START = 0,
    SAY_TRALL_START_1 = 1,
    SAY_TRALL_20PROCENT = 2,
    SAY_TRALL_DEATH_DEATHWING = 3,

    //Deathwing
    SAY_AGGRO = 0,
    SAY_KILL_ALL = 1,
    SAY_SPELL_1 = 2,
    SAY_SPELL_2 = 3,
    SAY_SPELL_3 = 4,
};

class boss_deathwing : public CreatureScript
{
public:
    boss_deathwing() : CreatureScript("boss_deathwing") { }

    struct boss_deathwingAI : public BossAI
    {
        boss_deathwingAI(Creature* creature) : BossAI(creature, BOSS_DEATHWING)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void InitializeAI()
        {

        }

        void Reset()
        {
            events.Reset();
            me->RemoveAllAuras();
            instance->SetBossState(DATA_PORTALS_ON_OFF, DONE);
            me->SetCanFly(true);
            me->SetReactState(REACT_AGGRESSIVE);

            me->SetInCombatWithZone();

            Talk(SAY_AGGRO);
            _Reset();
        }

        void EnterEvadeMode()
        {
            Reset();

            Talk(SAY_KILL_ALL);
            _EnterEvadeMode();
        }

        void EnterCombat(Unit* /*who*/)
        {
            instance->SetBossState(DATA_PORTALS_ON_OFF, IN_PROGRESS);
            events.ScheduleEvent(PHASE_1, 1);

            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add
            events.ScheduleEvent(EVENT_SAY_TRALL_START, 5000);
            _EnterCombat();
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    // SAY
                case EVENT_SAY_TRALL_START:
                    if (Creature* trall = me->FindNearestCreature(NPC_MAELSTROM_TRALL, 300.0f, true))
                        trall->AI()->Talk(SAY_TRALL_START);
                    events.ScheduleEvent(EVENT_SAY_TRALL_1, 3000);
                    break;

                case EVENT_SAY_TRALL_1:
                    if (Creature* trall = me->FindNearestCreature(NPC_MAELSTROM_TRALL, 300.0f, true))
                        trall->AI()->Talk(SAY_TRALL_START_1);
                    break;

                    //Phase 1
                case PHASE_1:
                    events.ScheduleEvent(EVENT_ASSAULT_ASPECTS, urand(60000, 100000));
                    if (IsHeroic()) // no work
                        events.ScheduleEvent(EVENT_CATACLYSM, 900000); // no work
                    events.ScheduleEvent(EVENT_CORRUPTING_PARASITE, urand(60000, 120000));
                    events.ScheduleEvent(EVENT_ELEMENTIUM_BOLT, 150); //no work
                    events.ScheduleEvent(HAS_20PROCENT_HEALTH_NEW_PHASE, 150);
                    break;

                case HAS_20PROCENT_HEALTH_NEW_PHASE:
                    if (me->GetHealthPct() < 53)
                    {
                        events.CancelEvent(HAS_20PROCENT_HEALTH_NEW_PHASE);
                        events.ScheduleEvent(PHASE_2, 150);
                        if (Creature* trall = me->FindNearestCreature(NPC_MAELSTROM_TRALL, 300.0f, true))
                        {
                            trall->AI()->Talk(SAY_TRALL_20PROCENT);
                            if (Player* players = trall->FindNearestPlayer(500.0f))
                                trall->SendPlaySound(26600, players);
                        }

                    }
                    events.ScheduleEvent(HAS_20PROCENT_HEALTH_NEW_PHASE, 5000);
                    break;

                case EVENT_ASSAULT_ASPECTS:
                    if (Unit* target = ObjectAccessor::GetCreature(*me, instance->GetData64(NPC_MAELSTROM_TRALL)))
                        DoCast(target, SPELL_ASSAULT_ASPECTS);
                    events.ScheduleEvent(EVENT_ASSAULT_ASPECTS, urand(40000, 80000));
                    break;

                case EVENT_CORRUPTING_PARASITE:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                    {
                        DoCast(target, SPELL_CORRUPTING_PARASITE);
                        me->SummonCreature(NPC_CORRUPTION_PARASITE, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 120000);
                    }
                    events.ScheduleEvent(EVENT_CORRUPTING_PARASITE, urand(40000, 80000));
                    break;

                case PHASE_2:
                    events.CancelEvent(EVENT_ASSAULT_ASPECTS);
                    events.CancelEvent(EVENT_CATACLYSM); // no work
                    events.CancelEvent(EVENT_CORRUPTING_PARASITE);
                    events.CancelEvent(EVENT_ELEMENTIUM_BOLT); // no work
                    events.CancelEvent(PHASE_2);
                    me->Kill(me);
                    if (IsHeroic())
                        events.ScheduleEvent(EVENT_CONGEALING_BLOOD, urand(30000, 60000));
                    events.ScheduleEvent(EVENT_ELEMENTIUM_FRAGMENT, urand(60000, 120000));
                    events.ScheduleEvent(EVENT_ELEMENTIUM_TERROR, urand(40000, 80000));
                    events.ScheduleEvent(EVENT_CORRUPTED_BLOOD, 150);
                    break;

                case EVENT_CORRUPTED_BLOOD:
                    if (me->GetHealthPct() < 15)
                    {
                        events.CancelEvent(EVENT_CORRUPTED_BLOOD);
                        DoCast(SPELL_CORRUPTED_BLOOD);
                    }
                    events.ScheduleEvent(EVENT_CORRUPTED_BLOOD, 5000);
                    break;

                case EVENT_CONGEALING_BLOOD:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                        me->SummonCreature(NPC_CONGEALING_BLOOD, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 120000);
                    events.ScheduleEvent(EVENT_CORRUPTED_BLOOD, urand(30000, 80000));
                    break;

                case EVENT_ELEMENTIUM_TERROR:
                    events.ScheduleEvent(EVENT_ELEMENTIUM_FRAGMENT, urand(60000, 90000));
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                        me->SummonCreature(NPC_ELEMENTIUM_FRAGMENT, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 120000);
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                        me->SummonCreature(NPC_ELEMENTIUM_FRAGMENT, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 120000);
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                        me->SummonCreature(NPC_ELEMENTIUM_FRAGMENT, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 120000);
                    break;

                case EVENT_ELEMENTIUM_FRAGMENT:
                    events.ScheduleEvent(EVENT_ELEMENTIUM_FRAGMENT, urand(120000, 200000));
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                        me->SummonCreature(NPC_ELEMENTIUM_TERROR, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 120000);
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                        me->SummonCreature(NPC_ELEMENTIUM_TERROR, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 120000);
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                        me->SummonCreature(NPC_ELEMENTIUM_TERROR, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 120000);
                    break;
                default:
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*kller*/)
        {
            DoCastAOE(SPELL_PLAY_MOVIE, true);
            instance->SetBossState(DATA_PORTALS_ON_OFF, DONE);
            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            if (Unit* creature = me->FindNearestCreature(57694, 100.0f))
                me->Kill(creature);
            if (Unit* creature = me->FindNearestCreature(57686, 100.0f))
                me->Kill(creature);
            if (Unit* creature = me->FindNearestCreature(57696, 100.0f))
                me->Kill(creature);
            if (Unit* creature = me->FindNearestCreature(57695, 100.0f))
                me->Kill(creature);
            if (Unit* creature = me->FindNearestCreature(56844, 100.0f))
                me->Kill(creature);
            if (Unit* killer = me->FindNearestPlayer(1000.0f))
                killer->SummonGameObject(RAID_MODE(GO_DEATHWING_LOOT_10N, GO_DEATHWING_LOOT_25N, GO_DEATHWING_LOOT_10H, GO_DEATHWING_LOOT_25H), -12075.2f, 12168.2f, -2.56926f, 3.57793f, 0.0f, 0.0f, -0.976295f, 0.216442f, 320000);
            if (Creature* trall = me->FindNearestCreature(NPC_MAELSTROM_TRALL, 300.0f, true))
                trall->AI()->Talk(SAY_TRALL_DEATH_DEATHWING);
            me->DespawnOrUnsummon(5000);
            //if (RAID_DIFFICULTY_10MAN_NORMAL || RAID_DIFFICULTY_10MAN_HEROIC || RAID_DIFFICULTY_25MAN_NORMAL || RAID_DIFFICULTY_25MAN_HEROIC)
            //    instance->DoCompleteAchievement(6177); // Destroyer's End
            //if (RAID_DIFFICULTY_10MAN_HEROIC || RAID_DIFFICULTY_25MAN_HEROIC)
            //    instance->DoCompleteAchievement(6116); // Heroic: Madness of Deathwing
            _JustDied();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<boss_deathwingAI>(creature);
    }
};

class npc_maelstrom_trall : public CreatureScript
{
public:
    npc_maelstrom_trall() : CreatureScript("npc_maelstrom_trall") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->GetInstanceScript())
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TRALL_MENU, GOSSIP_SENDER_MAIN, 10);

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 uiAction)
    {
        if (sender == GOSSIP_SENDER_MAIN)
        {
            player->PlayerTalkClass->ClearMenus();
            switch (uiAction)
            {
            case 10:
                if (InstanceScript* instance = creature->GetInstanceScript())
                {
                    player->CLOSE_GOSSIP_MENU();
                    instance->SetData(DATA_ATTACK_DEATHWING, IN_PROGRESS);
                    creature->SummonCreature(NPC_DEATHWING_1, -11903.9f, 11989.1f, -113.204f, 2.16421f, TEMPSUMMON_TIMED_DESPAWN, 12000000);
                    creature->SummonCreature(57694, -11967.1f, 11958.8f, -49.9822f, 2.16421f, TEMPSUMMON_CORPSE_DESPAWN, 6000000);
                    creature->SummonCreature(57686, -11852.1f, 12036.4f, -49.9821f, 2.16421f, TEMPSUMMON_CORPSE_DESPAWN, 6000000);
                    creature->SummonCreature(57696, -11913.8f, 11926.5f, -60.3749f, 2.16421f, TEMPSUMMON_CORPSE_DESPAWN, 6000000);
                    creature->SummonCreature(57695, -11842.2f, 11974.8f, -60.3748f, 2.16421f, TEMPSUMMON_CORPSE_DESPAWN, 6000000);
                    creature->SummonCreature(56844, -11857.0f, 11795.6f, -73.9549f, 2.23402f, TEMPSUMMON_CORPSE_DESPAWN, 6000000);
                    creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                }
                break;
            default:
                break;
            }
        }
        return true;
    }
};

class Teleportation_to_the_platforms : public CreatureScript
{
public:
    Teleportation_to_the_platforms() : CreatureScript("Teleportation_to_the_platforms") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELE_MENU_1, GOSSIP_SENDER_MAIN, 20);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELE_MENU_2, GOSSIP_SENDER_MAIN, 21);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELE_MENU_3, GOSSIP_SENDER_MAIN, 22);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TELE_MENU_4, GOSSIP_SENDER_MAIN, 23);

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 sender, uint32 uiAction)
    {
        if (sender == GOSSIP_SENDER_MAIN)
        {
            player->PlayerTalkClass->ClearMenus();
            switch (uiAction)
            {
            case 20:
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(967, -11961.371f, 12294.102f, 1.284f, 5.094f);
                break;
            case 21:
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(967, -12058.748f, 12245.875f, -6.151f, 5.464f);
                break;
            case 22:
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(967, -12121.12f, 12174.846f, -2.735f, 5.604f);
                break;
            case 23:
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(967, -12157.026f, 12090.791f, 2.308f, 6.029f);
                break;
            default:
                break;
            }
        }
        return true;
    }
};

class npc_arm_tentacle_one : public CreatureScript
{
public:
    npc_arm_tentacle_one() : CreatureScript("npc_arm_tentacle_one") { }

    struct npc_arm_tentacle_oneAI : public ScriptedAI
    {
        npc_arm_tentacle_oneAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            me->RemoveAllAuras();
            me->SetVisible(false);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            me->SetCanFly(true);
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoCast(SPELL_BURNING_BLODD);
            events.ScheduleEvent(EVENT_SUMMON, 30000);
            instance->SetData(DATA_DAMAGE_DEATHWING, IN_PROGRESS);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_SUMMON:
                    events.ScheduleEvent(EVENT_SUMMON, 5000);
                    if (me->GetHealthPct() < 50)
                    {
                        events.CancelEvent(EVENT_SUMMON);
                        me->SummonCreature(NPC_MYTATED_CORRUPTION, -12110.934f, 12184.085f, -2.731f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 120000);
                    }
                    break;
                }
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            instance->SetData(DATA_DAMAGE_DEATHWING, DONE);
        }

    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<npc_arm_tentacle_oneAI>(creature);
    }
};

class npc_arm_tentacle_two : public CreatureScript
{
public:
    npc_arm_tentacle_two() : CreatureScript("npc_arm_tentacle_two") { }

    struct npc_arm_tentacle_twoAI : public ScriptedAI
    {
        npc_arm_tentacle_twoAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            me->RemoveAllAuras();
            me->SetVisible(false);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            me->SetCanFly(true);
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoCast(SPELL_BURNING_BLODD);
            events.ScheduleEvent(EVENT_SUMMON, 30000);
            instance->SetData(DATA_DAMAGE_DEATHWING, IN_PROGRESS);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_SUMMON:
                    events.ScheduleEvent(EVENT_SUMMON, 5000);
                    if (me->GetHealthPct() < 50)
                    {
                        events.CancelEvent(EVENT_SUMMON);
                        me->SummonCreature(NPC_MYTATED_CORRUPTION, -12060.653f, 12235.851f, -6.255f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 120000);
                    }
                    break;
                }
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            instance->SetData(DATA_DAMAGE_DEATHWING, DONE);
        }

    };


    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<npc_arm_tentacle_twoAI>(creature);
    }
};

class npc_wing_tentacle_one : public CreatureScript
{
public:
    npc_wing_tentacle_one() : CreatureScript("npc_wing_tentacle_one") { }

    struct npc_wing_tentacle_oneAI : public ScriptedAI
    {
        npc_wing_tentacle_oneAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            me->RemoveAllAuras();
            me->SetVisible(false);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            me->SetCanFly(true);
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoCast(SPELL_BURNING_BLODD);
            events.ScheduleEvent(EVENT_SUMMON, 30000);
            instance->SetData(DATA_DAMAGE_DEATHWING, IN_PROGRESS);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_SUMMON:
                    events.ScheduleEvent(EVENT_SUMMON, 5000);
                    if (me->GetHealthPct() < 50)
                    {
                        events.CancelEvent(EVENT_SUMMON);
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                            me->SummonCreature(NPC_MYTATED_CORRUPTION, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 120000);
                    }
                    break;
                }
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            instance->SetData(DATA_DAMAGE_DEATHWING, DONE);
        }

    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<npc_wing_tentacle_oneAI>(creature);
    }
};

class npc_wing_tentacle_two : public CreatureScript
{
public:
    npc_wing_tentacle_two() : CreatureScript("npc_wing_tentacle_two") { }

    struct npc_wing_tentacle_twoAI : public ScriptedAI
    {
        npc_wing_tentacle_twoAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            me->RemoveAllAuras();
            me->SetVisible(false);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            me->SetCanFly(true);
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoCast(SPELL_BURNING_BLODD);
            events.ScheduleEvent(EVENT_SUMMON, 30000);
            instance->SetData(DATA_DAMAGE_DEATHWING, IN_PROGRESS);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_SUMMON:
                    events.ScheduleEvent(EVENT_SUMMON, 5000);
                    if (me->GetHealthPct() < 50)
                    {
                        events.CancelEvent(EVENT_SUMMON);
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                            me->SummonCreature(NPC_MYTATED_CORRUPTION, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 120000);
                    }
                    break;
                }
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            instance->SetData(DATA_DAMAGE_DEATHWING, DONE);
        }

    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<npc_wing_tentacle_twoAI>(creature);
    }
};

void AddSC_boss_deathwing()
{
    new boss_deathwing();
    new npc_maelstrom_trall();
    new npc_arm_tentacle_one();
    new npc_arm_tentacle_two();
    new npc_wing_tentacle_one();
    new npc_wing_tentacle_two();
    new Teleportation_to_the_platforms();
    //new npc_mytated_corruption();
    //new npc_maelstrom_alexstrasza();
    //new npc_maelstrom_kalecgos();
    //new npc_maelstrom_ysera();
    //new npc_maelstrom_nozdormy();
}