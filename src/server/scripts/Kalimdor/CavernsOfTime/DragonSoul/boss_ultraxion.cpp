/*
 * Copyright (C) 2011-2014 ArkCORE <http://www.arkania.net/>
 *
 * This file is NOT free software. Third-party users can NOT redistribute 
 * it or modify it. If you find it, you are either hacking something, or very 
 * lucky (presuming someone else managed to hack it).
 */

/* ScriptData
SDName: boss_ultraxion
SD%Complete: 50%
SDComment:
SDCategory: Boss Ultraxion
EndScriptData
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "dragon_soul.h"

#define TRALL_MENU "We are ready!"
#define ASPECT_MENU_1 "Last Defender of Azeroth"
#define ASPECT_MENU_2 "Revolution time"
#define ASPECT_MENU_3 "Essence of Dreams"
#define ASPECT_MENU_4 "Gift of Life"
#define ASPECT_MENU_5 "Magical power"


#define H_TARGETS_10 1
#define H_TARGETS_25 3
#define H_TARGETS_10_HEROIC 2
#define H_TARGETS_25_HEROIC 5

#define F_TARGETS_10 2
#define F_TARGETS_25 3
#define F_TARGETS_10_HEROIC 2
#define F_TARGETS_25_HEROIC 6

enum Events
{
    ATTACK_START = 1,
    EVENT_TWILIGHT_ERUPTION,
    EVENT_TWILIGHT_BURST,
    EVENT_FADING_LIGHT,
    EVENT_HOUR_OF_TWILIGHT,
    EVENT_TWILIGHT_SHIFT,
};

enum Spells
{
    SPELL_TWILIGHT_SHIFT       = 106369,
    SPELL_HOUR_OF_TWILIGHT     = 106371,
    SPELL_TWILIGHT_BURST       = 106415,
    SPELL_TWILIGHT_ERUPTION    = 106388,
    SPELL_FADING_LIGHT         = 109075,
    SPELL_UNSTABLE_MONSTROSITY = 106372,
};

class boss_ultraxion : public CreatureScript
{
public:
    boss_ultraxion() : CreatureScript("boss_ultraxion") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<boss_ultraxionAI>(creature);
    }

    struct boss_ultraxionAI: public BossAI
    {
        boss_ultraxionAI(Creature* creature) : BossAI(creature, BOSS_ULTRAXION)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            _Reset();
            events.Reset();
            me->GetMotionMaster()->MovePoint(4659700, -1699.160f, -2388.110f, 341.540f);
            me->SetSpeed(MOVE_FLIGHT, 2.5f);
            events.ScheduleEvent(ATTACK_START, 15000);
            me->SetPhaseMask(17, true);
            if(instance->GetBossState(DATA_PORTALS_ON_OFF) == IN_PROGRESS)
            {
                me->DespawnOrUnsummon(100);
                instance->SetBossState(DATA_TRALL_VS_ULTRAXION, IN_PROGRESS);
                instance->SetBossState(DATA_PORTALS_ON_OFF, DONE);
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            instance->SetBossState(DATA_PORTALS_ON_OFF, IN_PROGRESS);
            instance->SetBossState(DATA_TRALL_VS_ULTRAXION, DONE);
            events.ScheduleEvent(EVENT_TWILIGHT_ERUPTION, 360000);
            events.ScheduleEvent(EVENT_TWILIGHT_BURST, urand(10000,60000));
            events.ScheduleEvent(EVENT_FADING_LIGHT, urand(30000,120000));
            events.ScheduleEvent(EVENT_HOUR_OF_TWILIGHT, urand(120000,180000));
            events.ScheduleEvent(EVENT_TWILIGHT_SHIFT, 1);
            DoCast(SPELL_UNSTABLE_MONSTROSITY);
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
                // attack start
                case ATTACK_START:
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_NOT_SELECTABLE);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                    me->SetSpeed(MOVE_FLIGHT, 1.0f);
                    break;

                case EVENT_TWILIGHT_ERUPTION:
                    DoCastVictim(SPELL_TWILIGHT_ERUPTION);
                    break;

                case EVENT_TWILIGHT_BURST:
                    events.ScheduleEvent(EVENT_TWILIGHT_BURST, urand(10000,60000));
                    if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                    DoCast(target, SPELL_TWILIGHT_BURST);
                    break;

                case EVENT_TWILIGHT_SHIFT:
                    events.ScheduleEvent(EVENT_TWILIGHT_SHIFT, urand(30000,120000));
                    SelectTargetList(playerList, 25, SELECT_TARGET_RANDOM,0.0f,true);
                    for (std::list<Unit*>::const_iterator itr = playerList.begin(); itr != playerList.end(); ++itr)
                    {
                        Unit* targets = (*itr);
                        DoCast(targets, SPELL_TWILIGHT_SHIFT);
                    }
                    break;


                case EVENT_FADING_LIGHT:
                    events.ScheduleEvent(EVENT_TWILIGHT_BURST, urand(60000,120000));
                    SelectTargetList(playerList, RAID_MODE(F_TARGETS_10,F_TARGETS_25,F_TARGETS_10_HEROIC,F_TARGETS_25_HEROIC), SELECT_TARGET_RANDOM,0.0f,true);
                    for (std::list<Unit*>::const_iterator itr = playerList.begin(); itr != playerList.end(); ++itr)
                    {
                        Unit* targets = (*itr);
                        DoCast(targets, SPELL_FADING_LIGHT);
                    }
                    break;

                case EVENT_HOUR_OF_TWILIGHT:
                    events.ScheduleEvent(EVENT_TWILIGHT_BURST, urand(130000,160000));
                    SelectTargetList(playerList, RAID_MODE(H_TARGETS_10,H_TARGETS_25,H_TARGETS_10_HEROIC,H_TARGETS_25_HEROIC), SELECT_TARGET_RANDOM,0.0f,true);
                    for (std::list<Unit*>::const_iterator itr = playerList.begin(); itr != playerList.end(); ++itr)
                    {
                        Unit* targets = (*itr);
                        DoCast(targets, SPELL_HOUR_OF_TWILIGHT);
                    }
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void KilledUnit(Unit* /*victim*/) { }

        void JustDied(Unit* killer)
        {
            instance->SetBossState(BOSS_ULTRAXION, DONE);
            instance->SetBossState(DATA_PORTALS_ON_OFF, DONE);
            instance->SetBossState(DATA_TRALL_VS_ULTRAXION, FAIL);
            killer->SummonGameObject(RAID_MODE(GO_ULTRAXION_LOOT_10N, GO_ULTRAXION_LOOT_25N, GO_ULTRAXION_LOOT_10H, GO_ULTRAXION_LOOT_25H), -1753.63f,  -2370.01f, 340.845f, 0.0f, 0.0f, 0.0f, -0.66913f, 0.743145f, 100000);
            _JustDied();
        }

    private:
        std::list<Unit *> playerList;

    };
};

class npc_trall_vs_ultraxion : public CreatureScript
{
    public:
        npc_trall_vs_ultraxion() : CreatureScript("npc_trall_vs_ultraxion") { }

        bool OnGossipHello(Player* player, Creature* creature)
        {
             if (InstanceScript* instance = creature->GetInstanceScript())
             {
                 if (instance->GetBossState(DATA_TRALL_VS_ULTRAXION) == IN_PROGRESS && instance->GetBossState(BOSS_WARLORD) == DONE && instance->GetBossState(BOSS_UNSLEEPING) == DONE && instance->GetBossState(BOSS_HAGARA) == DONE)
                 {
                     player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TRALL_MENU, GOSSIP_SENDER_MAIN, 10);
                 }
                 if (instance->GetBossState(DATA_TRALL_VS_ULTRAXION) == DONE)
                 {
                     player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, ASPECT_MENU_1, GOSSIP_SENDER_MAIN, 11);
                 }
             }

             player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
             return true;
        }

        bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 uiAction)
        {
            if (sender == GOSSIP_SENDER_MAIN)
            {
                player->PlayerTalkClass->ClearMenus();
                switch(uiAction)
                {
                case 10:
                    player->CLOSE_GOSSIP_MENU();
                    creature->SummonCreature(NPC_ULTRAXION, -1616.576f, -2369.113f, 311.776f, 3.33f, TEMPSUMMON_CORPSE_DESPAWN, 1000000);
                    creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    break;
                case 11:
                    player->CLOSE_GOSSIP_MENU();
                    player->AddAura(LAST_DEFENDER_OF_AZEROTH, player);
                    player->RemoveAurasDueToSpell(TIMELOOP);
                    player->RemoveAurasDueToSpell(SOURCE_OF_MAGIC);
                    player->RemoveAurasDueToSpell(ESSENCE_OF_DREAMS);
                    player->RemoveAurasDueToSpell(GIFT_OF_LIFE);
                    break;
                default:
                    break;
                }
            }
            return true;
        }
};

class npc_nozdormu : public CreatureScript
{
    public:
        npc_nozdormu() : CreatureScript("npc_nozdormu") { }

        bool OnGossipHello(Player* player, Creature* creature)
        {
             if (InstanceScript* instance = creature->GetInstanceScript())
             {
                 if (instance->GetBossState(DATA_TRALL_VS_ULTRAXION) == DONE)
                 {
                     player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, ASPECT_MENU_2, GOSSIP_SENDER_MAIN, 20);
                 }
             }

             player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
             return true;
        }

        bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 sender, uint32 uiAction)
        {
            if (sender == GOSSIP_SENDER_MAIN)
            {
                player->PlayerTalkClass->ClearMenus();
                switch(uiAction)
                {
                case 20:
                    player->CLOSE_GOSSIP_MENU();
                    player->CastSpell(player, TIMELOOP);
                    player->RemoveAurasDueToSpell(LAST_DEFENDER_OF_AZEROTH);
                    player->RemoveAurasDueToSpell(SOURCE_OF_MAGIC);
                    player->RemoveAurasDueToSpell(ESSENCE_OF_DREAMS);
                    player->RemoveAurasDueToSpell(GIFT_OF_LIFE);
                    break;
                default:
                    break;
                }
            }
            return true;
        }
};

class npc_ysera : public CreatureScript
{
    public:
        npc_ysera() : CreatureScript("npc_ysera") { }

        bool OnGossipHello(Player* player, Creature* creature)
        {
             if (InstanceScript* instance = creature->GetInstanceScript())
             {
                 if (instance->GetBossState(DATA_TRALL_VS_ULTRAXION) == DONE)
                 {
                     player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, ASPECT_MENU_3, GOSSIP_SENDER_MAIN, 30);
                 }
             }

             player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
             return true;
        }

        bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 sender, uint32 uiAction)
        {
            if (sender == GOSSIP_SENDER_MAIN)
            {
                player->PlayerTalkClass->ClearMenus();
                switch(uiAction)
                {
                case 30:
                    player->CLOSE_GOSSIP_MENU();
                    player->CastSpell(player, ESSENCE_OF_DREAMS);
                    player->RemoveAurasDueToSpell(LAST_DEFENDER_OF_AZEROTH);
                    player->RemoveAurasDueToSpell(SOURCE_OF_MAGIC);
                    player->RemoveAurasDueToSpell(TIMELOOP);
                    player->RemoveAurasDueToSpell(GIFT_OF_LIFE);
                    break;
                default:
                    break;
                }
            }
            return true;
        }
};

class npc_alexstrasza : public CreatureScript
{
    public:
        npc_alexstrasza() : CreatureScript("npc_alexstrasza") { }

        bool OnGossipHello(Player* player, Creature* creature)
        {
             if (InstanceScript* instance = creature->GetInstanceScript())
             {
                 if (instance->GetBossState(DATA_TRALL_VS_ULTRAXION) == DONE)
                 {
                     player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, ASPECT_MENU_4, GOSSIP_SENDER_MAIN, 40);
                 }
             }

             player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
             return true;
        }

        bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 sender, uint32 uiAction)
        {
            if (sender == GOSSIP_SENDER_MAIN)
            {
                player->PlayerTalkClass->ClearMenus();
                switch(uiAction)
                {
                case 40:
                    player->CLOSE_GOSSIP_MENU();
                    player->CastSpell(player, GIFT_OF_LIFE);
                    player->RemoveAurasDueToSpell(LAST_DEFENDER_OF_AZEROTH);
                    player->RemoveAurasDueToSpell(SOURCE_OF_MAGIC);
                    player->RemoveAurasDueToSpell(TIMELOOP);
                    player->RemoveAurasDueToSpell(ESSENCE_OF_DREAMS);
                    break;
                default:
                    break;
                }
            }
            return true;
        }
};

class npc_aspect_of_magic : public CreatureScript
{
    public:
        npc_aspect_of_magic() : CreatureScript("npc_aspect_of_magic") { }

        bool OnGossipHello(Player* player, Creature* creature)
        {
             if (InstanceScript* instance = creature->GetInstanceScript())
             {
                 if (instance->GetBossState(DATA_TRALL_VS_ULTRAXION) == DONE)
                 {
                     player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, ASPECT_MENU_5, GOSSIP_SENDER_MAIN, 50);
                 }
             }

             player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
             return true;
        }

        bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 sender, uint32 uiAction)
        {
            if (sender == GOSSIP_SENDER_MAIN)
            {
                player->PlayerTalkClass->ClearMenus();
                switch(uiAction)
                {
                case 50:
                    player->CLOSE_GOSSIP_MENU();
                    player->CastSpell(player, SOURCE_OF_MAGIC);
                    player->RemoveAurasDueToSpell(LAST_DEFENDER_OF_AZEROTH);
                    player->RemoveAurasDueToSpell(GIFT_OF_LIFE);
                    player->RemoveAurasDueToSpell(TIMELOOP);
                    player->RemoveAurasDueToSpell(ESSENCE_OF_DREAMS);
                    break;
                default:
                    break;
                }
            }
            return true;
        }
};

void AddSC_boss_ultraxion()
{
    new boss_ultraxion();
    new npc_trall_vs_ultraxion();
    new npc_nozdormu();
    new npc_ysera();
    new npc_aspect_of_magic();
    new npc_alexstrasza();
}
