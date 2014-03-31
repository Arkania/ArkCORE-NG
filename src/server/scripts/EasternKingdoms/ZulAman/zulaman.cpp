/*
 * Copyright (C) 2011-2014 ArkCORE <http://www.arkania.net/>
 *
 * This file is NOT free software. Third-party users can NOT redistribute 
 * it or modify it. If you find it, you are either hacking something, or very 
 * lucky (presuming someone else managed to hack it).
 */

/* ScriptData
SDName: Zul' Aman 4.1
SD%Complete: 100
SDCategory: Zul'Aman 5 Hc
EndScriptData */

/* ContentData
npc_zulaman_voljin
npc_forest_frog
npc_zulaman_hostage
npc_zulaman_archon
npc_zulaman_juggernaut
npc_zulaman_hierophant
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "zulaman.h"

/*######
## npc_zulaman_voljin
######*/

enum VolJinYells
{
    SAY_FOLLOW = 0,
    SAY_GONG   = 1,
    SAY_OPEN   = 2,
    SAY_RESET  = 3,
    ANN_GONG   = 4
};

enum HostageYells
{
    SAY_BOSS_DEAD = 0,
    SAY_CHEST = 1
};

Position const wayPos[3] =
{
    {120.234f, 1656.628f, 42.021f},
    {129.312f, 1645.332f, 42.021f},
    {120.660f, 1638.805f, 42.358f}
};

enum HierophantYells
{
/*
    // Dialogue:
    Zandalari Hierophant says: Dis shattered world not done breakin, mon.
    Zandalari Hierophant says: De tides of darkness gonna take over. All da trolls be in danger.
    Zandalari Hierophant says: Zul has seen tha' future. We gotta come together, or we all fall to de darkness.
    Zandalari Hierophant says: De Zandalari got powers you never seen. Wisdom of de most ancient of trolls, wisdom dat's rightfully yours.
    Zandalari Hierophant says: Dis land was taken from us in a tide of blood.
    Zandalari Hierophant says: De Darkspear be foolish. No one gonna stand in our way.
    Zandalari Hierophant says: De green fist of de troll empire gonna crush dis land and make it our own again.
    Zandalari Hierophant says: 'Dis be de only way, bruddahs.
*/
   YELL_HIEROPHANT_DIALOGUE_1 = 0,
   YELL_HIEROPHANT_DIALOGUE_2 = 1,
   YELL_HIEROPHANT_DIALOGUE_3 = 2,
   YELL_HIEROPHANT_DIALOGUE_4 = 3,
   YELL_HIEROPHANT_DIALOGUE_5 = 4,
   YELL_HIEROPHANT_DIALOGUE_6 = 5,
   YELL_HIEROPHANT_DIALOGUE_7 = 6,
   YELL_HIEROPHANT_DIALOGUE_8 = 7,

   YELL_HIEROPHANT_GLORY = 8
};

enum Events
{
    EVENT_MOVE_0 = 1,
    EVENT_MOVE_1,
    EVENT_MOVE_2,
    EVENT_STOP_MOVE,
    EVENT_GONG_START,
    EVENT_GONG_RESET,
    EVENT_SAY_OPEN,
    EVENT_OPEN_GATES,

    // Mobs
    EVENT_DIALOGUE_1,
    EVENT_DIALOGUE_2,
    EVENT_DIALOGUE_3,
    EVENT_DIALOGUE_4,
    EVENT_DIALOGUE_5,
    EVENT_DIALOGUE_6,
    EVENT_DIALOGUE_7,
    EVENT_DIALOGUE_8,

    EVENT_BLESSING_ZAND_HIERO,
    EVENT_BLESSING_ZAND_ARCHON,
    EVENT_BLESSING_ZAND_JUGGER,

    EVENT_GLORY_HIERO,  //  Ancients of Zandalar, grant dis one da power ta' mock death itself!
    EVENT_GLORY_ARCHON, //  Ancients of Zandalar, mark 'dem for de black road!
    EVENT_GLORY_JUGGER, //  Ancestors be beside me, let 'dem hear yo' voice!

    // Hierophant
    EVENT_GUARDIAN,
    EVENT_POWER,
    EVENT_SANCTIFY,
    EVENT_HYPOTHERMIA,

    // Archon
    EVENT_SIGIL_OF_DEATH,
    EVENT_SIGIL_OF_FLAME,
    EVENT_SIGIL_OF_FROST,
    EVENT_SIGIL_SHATTER,

    // Juggernaut
    EVENT_ANCESTRAL_CALL
};

enum MobSpells
{
    SPELL_GLORY_HIEROPHANT = 97969,
    SPELL_GLORY_ARCHON     = 97971,
    SPELL_GLORY_JUGGERNAUT = 97970,

    SPELL_BLESSING_OF_ZAND = 97977, // Before Glory.

   // Hierophant
   SPELL_ANCIENT_GUARDIAN   = 97978, // - Glory.
   SPELL_ANCIENT_POWER      = 23979,
   SPELL_SANCTIFY           = 97973,
   SPELL_HYPOTHERMIA        = 96332,

   // Juggernaut
   SPELL_ANCESTRAL_CALL     = 98000, // - Glory.

   // Archon
   SPELL_SIGIL_OF_DEATH     = 98018,
   SPELL_SIGIL_OF_FLAME     = 98006,
   SPELL_SIGIL_OF_FROST     = 98015,
   SPELL_SIGIL_SHATTER      = 98024, // - Glory.
};

enum Action
{
    ACTION_EVENTS_START,
    ACTION_GONG_COMPLETE
};

class npc_zulaman_voljin : public CreatureScript
{
public:
    npc_zulaman_voljin() : CreatureScript("npc_zulaman_voljin") { }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (creature->IsQuestGiver())
                player->PrepareQuestMenu(creature->GetGUID());

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "We're ready to open the gates.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->SEND_GOSSIP_MENU(66672, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect (Player* pPlayer, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
        {
            if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
            {
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->CLOSE_GOSSIP_MENU();
                creature->GetAI()->DoAction(ACTION_EVENTS_START);
            }

            return true;
        }

        struct npc_zulaman_voljinAI : public ScriptedAI
        {
            npc_zulaman_voljinAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
                activated = false;
                Starting = false;
            }

            InstanceScript* instance;
            bool activated, Starting;
            EventMap events;

            void UpdateAI(const uint32 diff)
            {
                if (!activated)
                    return;

                if (activated && !Starting)
                {
                    events.ScheduleEvent(EVENT_MOVE_0, 1000);
                    Starting = true;
                }

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_MOVE_0:
                            Talk(SAY_FOLLOW);
                            me->GetMotionMaster()->MovePoint(0, wayPos[0]);
                            events.ScheduleEvent(EVENT_MOVE_1, 2000);
                            break;
                        case EVENT_MOVE_1:
                            me->GetMotionMaster()->MovePoint(0, wayPos[1]);
                            events.ScheduleEvent(EVENT_STOP_MOVE, 2500);
                            break;
                        case EVENT_MOVE_2:
                            me->GetMotionMaster()->MovePoint(0, wayPos[2]);
                            events.ScheduleEvent(EVENT_SAY_OPEN, 2500);
                            break;
                        case EVENT_SAY_OPEN:
                            Talk(SAY_OPEN);
                            events.ScheduleEvent(EVENT_OPEN_GATES, 5000);
                            break;
                        case EVENT_OPEN_GATES:
                            if (GameObject * gate = me->FindNearestGameObject(186728, 50.0f))
                                gate->UseDoorOrButton();
                            if (Creature* Guardian = me->FindNearestCreature(23597, 50.0f, true))
                                Guardian->AI()->Talk(1);
                            break;
                        case EVENT_STOP_MOVE:
                            Talk(SAY_GONG);
                            Talk(ANN_GONG);
                            events.ScheduleEvent(EVENT_GONG_START, 3000);
                            break;
                        case EVENT_GONG_START:
                            if (GameObject * gong = me->FindNearestGameObject(187359, 10.0f))
                            {
                                gong->SetGoState(GO_STATE_ACTIVE);
                                gong->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                                DoCast(45226);
                            }
                            events.ScheduleEvent(EVENT_GONG_RESET, 4000);
                            events.ScheduleEvent(EVENT_GONG_START, 6000);
                            break;
                        case EVENT_GONG_RESET:
                            if (GameObject * gong = me->FindNearestGameObject(187359, 10.0f))
                                gong->SetGoState(GO_STATE_READY);
                            break;
                        default:
                            break;
                    }
                }
            }

            void DoAction(const int32 action)
            {
                switch(action)
                {
                    case ACTION_EVENTS_START:
                        me->Dismount();
                        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        activated = true;
                        break;
                    case ACTION_GONG_COMPLETE:
                        events.CancelEvent(EVENT_GONG_RESET);
                        events.CancelEvent(EVENT_GONG_START);
                        events.ScheduleEvent(EVENT_MOVE_2, 2000);
                        if (GameObject * gong = me->FindNearestGameObject(187359, 10.0f))
                            gong->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                        break;
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_zulaman_voljinAI(creature);
        }
};

/*######
## npc_forest_frog
######*/

#define SPELL_REMOVE_AMANI_CURSE    43732
#define SPELL_PUSH_MOJO             43923
#define ENTRY_FOREST_FROG           24396

class npc_forest_frog : public CreatureScript
{
    public:
        npc_forest_frog() : CreatureScript("npc_forest_frog") { }

        struct npc_forest_frogAI : public ScriptedAI
        {
            npc_forest_frogAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;

            void Reset() {}

            void EnterCombat(Unit* /*who*/) {}

            void DoSpawnRandom()
            {
                if (instance)
                {
                    uint32 cEntry = 0;
                    switch (rand()%10)
                    {
                        case 0: cEntry = 24397; break;          //Mannuth
                        case 1: cEntry = 24403; break;          //Deez
                        case 2: cEntry = 24404; break;          //Galathryn
                        case 3: cEntry = 24405; break;          //Adarrah
                        case 4: cEntry = 24406; break;          //Fudgerick
                        case 5: cEntry = 24407; break;          //Darwen
                        case 6: cEntry = 24445; break;          //Mitzi
                        case 7: cEntry = 24448; break;          //Christian
                        case 8: cEntry = 24453; break;          //Brennan
                        case 9: cEntry = 24455; break;          //Hollee
                    }

                    if (!instance->GetData(TYPE_RAND_VENDOR_1))
                        if (rand()%10 == 1) cEntry = 24408;      //Gunter
                    if (!instance->GetData(TYPE_RAND_VENDOR_2))
                        if (rand()%10 == 1) cEntry = 24409;      //Kyren

                    if (cEntry) me->UpdateEntry(cEntry);

                    if (cEntry == 24408) instance->SetData(TYPE_RAND_VENDOR_1, DONE);
                    if (cEntry == 24409) instance->SetData(TYPE_RAND_VENDOR_2, DONE);
                }
            }

            void SpellHit(Unit* caster, const SpellInfo* spell)
            {
                if (spell->Id == SPELL_REMOVE_AMANI_CURSE && caster->GetTypeId() == TYPEID_PLAYER && me->GetEntry() == ENTRY_FOREST_FROG)
                {
                    //increase or decrease chance of mojo?
                    if (rand()%99 == 50) DoCast(caster, SPELL_PUSH_MOJO, true);
                    else DoSpawnRandom();
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_forest_frogAI(creature);
        }
};

/*######
## npc_zulaman_hostage
######*/

#define GOSSIP_HOSTAGE1        "I am glad to help you."

//  Hazlek, Bakkalzu, Norkani, Kasha
static uint32 HostageEntry[] = {52939, 52941, 52943, 52945};
static uint32 ChestEntry[] = {186648, 187021, 186667, 186672};

class npc_zulaman_hostage : public CreatureScript
{
    public:
        npc_zulaman_hostage() : CreatureScript("npc_zulaman_hostage") { }

        struct npc_zulaman_hostageAI : public ScriptedAI
        {
            npc_zulaman_hostageAI(Creature* creature) : ScriptedAI(creature)
            {
                IsLoot = false;
            }

            bool IsLoot;
            uint64 PlayerGUID;

            void Reset() {}

            void EnterCombat(Unit* /*who*/) {}

            void IsSummonedBy(Unit* /*summoner*/)
            {
                Talk(SAY_BOSS_DEAD);
            }

            void JustDied(Unit* /*killer*/)
            {
                Player* player = Unit::GetPlayer(*me, PlayerGUID);
                if (player)
                    player->SendLoot(me->GetGUID(), LOOT_CORPSE);
            }

            void UpdateAI(const uint32 /*diff*/)
            {
                if (IsLoot)
                    DoCast(me, 7, false);
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_zulaman_hostageAI(creature);
        }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HOSTAGE1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
        {
            player->PlayerTalkClass->ClearMenus();

            if (action == GOSSIP_ACTION_INFO_DEF + 1)
                player->CLOSE_GOSSIP_MENU();

            if (!creature->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP))
                return true;

            creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

            InstanceScript* instance = creature->GetInstanceScript();
            if (instance)
            {
                creature->AI()->Talk(SAY_CHEST);
                //uint8 progress = instance->GetData(DATA_CHESTLOOTED);
                instance->SetData(DATA_CHESTLOOTED, 0);
                float x, y, z;
                creature->GetClosePoint(x, y, z, creature->GetObjectSize() / 3, 5.0f);
                uint32 entry = creature->GetEntry();
                for (uint8 i = 0; i < 4; ++i)
                {
                    if (HostageEntry[i] == entry)
                    {
                        creature->SummonGameObject(ChestEntry[i], x, y, z, 0, 0, 0, 0, 0, 0);
                        break;
                    }
                }
            }
            return true;
        }
};

class npc_zulaman_archon : public CreatureScript
{
    public:
        npc_zulaman_archon() : CreatureScript("npc_zulaman_archon") { }

        struct npc_zulaman_archonAI : public ScriptedAI
        {
            npc_zulaman_archonAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;
            bool gloryCasted;

            void Reset()
            {
                gloryCasted = false;
            }

            void EnterEvadeMode()
            {
                if (me->HasAura(SPELL_GLORY_ARCHON))
                    me->RemoveAura(SPELL_GLORY_ARCHON);

                me->GetMotionMaster()->MoveTargetedHome();
                Reset();

                me->SetHealth(me->GetMaxHealth());
            }

            void EnterCombat(Unit* /*who*/)
            {
                events.ScheduleEvent(EVENT_SIGIL_OF_DEATH, 4000);
                events.ScheduleEvent(EVENT_SIGIL_OF_FLAME, 6000);
                events.ScheduleEvent(EVENT_SIGIL_OF_FROST, 8000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (me->HealthBelowPct(36) && !gloryCasted)
                {
                    events.ScheduleEvent(EVENT_BLESSING_ZAND_ARCHON, 100);
                    events.ScheduleEvent(EVENT_GLORY_ARCHON, 200);
                    events.ScheduleEvent(EVENT_SIGIL_SHATTER, 5000);
                    gloryCasted = true;
                }

                events.Update(diff);
                
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SIGIL_OF_DEATH:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                me->AddAura(SPELL_SIGIL_OF_DEATH, target);
                            events.ScheduleEvent(EVENT_SIGIL_OF_DEATH, urand(25000, 29000));
                            break;

                        case EVENT_SIGIL_OF_FLAME:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(target, SPELL_SIGIL_OF_FLAME);
                            events.ScheduleEvent(EVENT_SIGIL_OF_FLAME, urand(25000, 29000));
                            break;

                        case EVENT_SIGIL_OF_FROST:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(target, SPELL_SIGIL_OF_FROST);
                            events.ScheduleEvent(EVENT_SIGIL_OF_FROST, urand(25000, 29000));
                            break;

                        case EVENT_BLESSING_ZAND_ARCHON:
                            Talk(0);
                            DoCast(me, SPELL_BLESSING_OF_ZAND);
                            break;

                        case EVENT_GLORY_ARCHON:
                            DoCast(me, SPELL_GLORY_ARCHON);
                            break;

                        case EVENT_SIGIL_SHATTER:
                            DoCast(me, SPELL_SIGIL_SHATTER);
                            events.ScheduleEvent(EVENT_SIGIL_SHATTER, urand(20000, 30000));
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_zulaman_archonAI(creature);
        }
};

class npc_zulaman_juggernaut : public CreatureScript
{
    public:
        npc_zulaman_juggernaut() : CreatureScript("npc_zulaman_juggernaut") { }

        struct npc_zulaman_juggernautAI : public ScriptedAI
        {
            npc_zulaman_juggernautAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;
            bool gloryCasted;

            void Reset()
            {
                gloryCasted = false;
            }

            void EnterEvadeMode()
            {
                if (me->HasAura(SPELL_GLORY_JUGGERNAUT))
                    me->RemoveAura(SPELL_GLORY_JUGGERNAUT);

                me->GetMotionMaster()->MoveTargetedHome();
                Reset();

                me->SetHealth(me->GetMaxHealth());
            }

            void EnterCombat(Unit* /*who*/) { }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (me->HealthBelowPct(36) && !gloryCasted)
                {
                    events.ScheduleEvent(EVENT_BLESSING_ZAND_JUGGER, 100);
                    events.ScheduleEvent(EVENT_GLORY_JUGGER, 200);
                    events.ScheduleEvent(EVENT_ANCESTRAL_CALL, 5000);
                    gloryCasted = true;
                }

                events.Update(diff);
                
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_BLESSING_ZAND_JUGGER:
                            Talk(0);
                            DoCast(me, SPELL_BLESSING_OF_ZAND);
                            break;

                        case EVENT_GLORY_JUGGER:
                            DoCast(me, SPELL_GLORY_JUGGERNAUT);
                            break;

                        case EVENT_ANCESTRAL_CALL:
                            DoCast(me, SPELL_ANCESTRAL_CALL);
                            events.ScheduleEvent(EVENT_ANCESTRAL_CALL, urand(20000, 30000));
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_zulaman_juggernautAI(creature);
        }
};

class npc_zulaman_hierophant : public CreatureScript
{
    public:
        npc_zulaman_hierophant() : CreatureScript("npc_zulaman_hierophant") { }

        struct npc_zulaman_hierophantAI : public ScriptedAI
        {
            npc_zulaman_hierophantAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
                scheduled = false;
            }

            InstanceScript* instance;
            EventMap events;
            bool gloryCasted, scheduled;

            void Reset()
            {
                if (!scheduled)
                {
                    events.ScheduleEvent(EVENT_DIALOGUE_1, 5000);
                    scheduled = true;
                }

                gloryCasted = false;
            }

            void EnterEvadeMode()
            {
                if (me->HasAura(SPELL_GLORY_HIEROPHANT))
                    me->RemoveAura(SPELL_GLORY_HIEROPHANT);

                me->GetMotionMaster()->MoveTargetedHome();
                Reset();

                me->SetHealth(me->GetMaxHealth());
            }

            void EnterCombat(Unit* who)
            {
                events.CancelEvent(EVENT_DIALOGUE_1);
                events.CancelEvent(EVENT_DIALOGUE_2);
                events.CancelEvent(EVENT_DIALOGUE_3);
                events.CancelEvent(EVENT_DIALOGUE_4);
                events.CancelEvent(EVENT_DIALOGUE_5);
                events.CancelEvent(EVENT_DIALOGUE_6);
                events.CancelEvent(EVENT_DIALOGUE_7);
                events.CancelEvent(EVENT_DIALOGUE_8);
                events.ScheduleEvent(EVENT_POWER, urand(3000, 8000));
                events.ScheduleEvent(EVENT_SANCTIFY, urand(9000, 15000));
                events.ScheduleEvent(EVENT_HYPOTHERMIA, urand(5000, 12000));

                std::list<Creature*> creatures;
                GetCreatureListWithEntryInGrid(creatures, me, 53021, 80.0f);
                
                if (creatures.empty())
                    return;
                
                for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                {
                    (*iter)->SetWalk(false);
                    (*iter)->SetSpeed(MOVE_RUN, 2.0f);
                    (*iter)->AI()->AttackStart(who);
                }
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim() && me->IsInCombat() || me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (me->HealthBelowPct(36) && !gloryCasted)
                {
                    events.ScheduleEvent(EVENT_BLESSING_ZAND_HIERO, 100);
                    events.ScheduleEvent(EVENT_GLORY_HIERO, 200);
                    events.ScheduleEvent(EVENT_GUARDIAN, 5000);
                    gloryCasted = true;
                }

                events.Update(diff);
                
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_DIALOGUE_1:
                            Talk(YELL_HIEROPHANT_DIALOGUE_1);
                            events.ScheduleEvent(EVENT_DIALOGUE_2, 7000);
                            break;

                        case EVENT_DIALOGUE_2:
                            Talk(YELL_HIEROPHANT_DIALOGUE_2);
                            events.ScheduleEvent(EVENT_DIALOGUE_3, 7000);
                            break;

                        case EVENT_DIALOGUE_3:
                            Talk(YELL_HIEROPHANT_DIALOGUE_3);
                            events.ScheduleEvent(EVENT_DIALOGUE_4, 7000);
                            break;

                        case EVENT_DIALOGUE_4:
                            Talk(YELL_HIEROPHANT_DIALOGUE_4);
                            events.ScheduleEvent(EVENT_DIALOGUE_5, 7000);
                            break;

                        case EVENT_DIALOGUE_5:
                            Talk(YELL_HIEROPHANT_DIALOGUE_5);
                            events.ScheduleEvent(EVENT_DIALOGUE_6, 7000);
                            break;

                        case EVENT_DIALOGUE_6:
                            Talk(YELL_HIEROPHANT_DIALOGUE_6);
                            events.ScheduleEvent(EVENT_DIALOGUE_7, 7000);
                            break;

                        case EVENT_DIALOGUE_7:
                            Talk(YELL_HIEROPHANT_DIALOGUE_7);
                            events.ScheduleEvent(EVENT_DIALOGUE_8, 7000);
                            break;

                        case EVENT_DIALOGUE_8:
                            Talk(YELL_HIEROPHANT_DIALOGUE_8);
                            events.ScheduleEvent(EVENT_DIALOGUE_1, 40000);
                            break;

                        case EVENT_BLESSING_ZAND_HIERO:
                            DoCast(me, SPELL_BLESSING_OF_ZAND);
                            break;

                        case EVENT_GLORY_HIERO:
                            Talk(YELL_HIEROPHANT_GLORY);
                            DoCast(me, SPELL_GLORY_HIEROPHANT);
                            break;

                        case EVENT_GUARDIAN:
                            DoCast(me, SPELL_ANCIENT_GUARDIAN);
                            break;

                        case EVENT_POWER:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(target, SPELL_ANCIENT_POWER);
                            events.ScheduleEvent(EVENT_POWER, urand(9000, 17000));
                            break;

                        case EVENT_SANCTIFY:
                            DoCast(me, SPELL_SANCTIFY);
                            events.ScheduleEvent(EVENT_SANCTIFY, urand(25000, 30000));
                            break;

                        case EVENT_HYPOTHERMIA:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                me->AddAura(SPELL_HYPOTHERMIA, target);
                            events.ScheduleEvent(EVENT_HYPOTHERMIA, urand(15000, 20000));
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_zulaman_hierophantAI(creature);
        }
};

void AddSC_zulaman()
{
    new npc_zulaman_voljin();
    new npc_forest_frog();
    new npc_zulaman_hostage();
    new npc_zulaman_archon();
    new npc_zulaman_juggernaut();
    new npc_zulaman_hierophant();
}