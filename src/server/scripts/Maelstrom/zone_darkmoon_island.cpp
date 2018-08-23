/*
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "SpellMgr.h"
#include "Player.h"
#include "Creature.h"

enum eZone_darkmoon_island
{
    PLAYER_GUID = 99999,

    NPC_DARKMOON_FAIRE_GNOLL = 54444,
    NPC_DARKMOON_FAIRE_GNOLL_BABY = 54466,
    NPC_DARKMOON_FAIRE_GNOLL_BONUS = 54549,
    NPC_DARKMOON_FAIRE_GNOLL_BUNNY = 58570,
    NPC_MOLA = 54601,
    NPC_MAXIMA_BLASTENHEIMER = 15303,
    NPC_JESSICA_ROGERS = 54485,
    NPC_JUBJUB = 14867,

    ITEM_DARK_IRON_ALE_MUG = 11325,
    ITEM_UNHATCHED_JUBLING_EGG = 19462,

    QUEST_ITS_HAMMER_TIME = 29463,
    QUEST_THE_HUMANOID_CANNONBALL = 29436,
    QUEST_HE_SHOOTS_HE_SCORES = 29438,
    QUEST_TARGET_TURTLE = 29455,
    QUEST_SPAWN_OF_JUBJUB = 7946,

    SPELL_WHACK_A_GNOLL_1 = 101612,
    SPELL_WRONG_WHACK = 101679,
    SPELL_STAY_OUT_1 = 110966,
    SPELL_WHACK_A_GNOLL_KILL_CREDIT = 101835,
    SPELL_WHACK_A_GNOLL_GNOLL_SPAWN = 102136,
    SPELL_MALLET_GOSSIP = 102188,
    SPELL_WHACK_A_GNOLL2 = 110230,
    //
    SPELL_CANNON_BLAST = 102121,
    SPELL_CANNON_TARGET_AREA_AURA_A = 62171,
    SPELL_CANNON_TARGET_AREA_AURA_B = 62174,
    SPELL_CANNON_TARGET_AREA_AURA_C = 62178,
    SPELL_DISMOUNT_CHECK_AURA = 101300,
    //
    SPELL_RING_TOSS_GOSSIP = 101808, // Trigger spell (101814) Marke ausgeben. Chance = 0
    SPELL_RING_TOSS = 109765,
    SPELL_STAY_OUT = 109972,
    SPELL_RING_TOSS_1 = 101696,
    SPELL_RING_TOSS_2 = 101699,
    SPELL_RING_TOSS_3 = 101734,
    //
    SPELL_SUMMON_JUBLING = 23811,
    SPELL_JUBLING_COOLDOWN = 23853,
    //
};

// 54601
class npc_mola_54601 : public CreatureScript
{
public:
    npc_mola_54601() : CreatureScript("npc_mola_54601") { }

    enum eNpc
    {
        MOLA_GOSSIP_MENU_ID = 13018,
        MOLA_GOSSIP_TEXT_ID = 18289,
        MOLA_GOSSIP_MENU_ID2 = 13065,
        MOLA_GOSSIP_TEXT_ID2 = 18350,
        EVENT_TALK = 101,
        EVENT_TALK_DC,
    };

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        player->PrepareQuestMenu(creature->GetGUID());
        player->ADD_GOSSIP_ITEM_DB(MOLA_GOSSIP_MENU_ID, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        player->ADD_GOSSIP_ITEM_DB(MOLA_GOSSIP_MENU_ID, 1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
        player->SEND_GOSSIP_MENU(MOLA_GOSSIP_TEXT_ID, creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
        case GOSSIP_ACTION_INFO_DEF + 1:
        {
            player->ADD_GOSSIP_ITEM_DB(MOLA_GOSSIP_MENU_ID2, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->SEND_GOSSIP_MENU(MOLA_GOSSIP_TEXT_ID2, creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 3:
        {
            player->PrepareQuestMenu(creature->GetGUID());
            player->ADD_GOSSIP_ITEM_DB(MOLA_GOSSIP_MENU_ID, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM_DB(MOLA_GOSSIP_MENU_ID, 1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->SEND_GOSSIP_MENU(MOLA_GOSSIP_TEXT_ID, creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 2:
        {
            Quest const* quest = sObjectMgr->GetQuestTemplate(QUEST_ITS_HAMMER_TIME);
            if (player->CanTakeQuest(quest, false))
            {
                player->AddQuest(quest, creature);
            }
            if (player->GetQuestStatus(QUEST_ITS_HAMMER_TIME) == QUEST_STATUS_INCOMPLETE && !player->HasAura(SPELL_WHACK_A_GNOLL_1))
            {
                player->CastSpell(player, SPELL_MALLET_GOSSIP);
            }
            if (player->HasAura(SPELL_WHACK_A_GNOLL_1))
            {
                player->AddAura(110230, player);
                //creature->SummonCreature(58570, -3984.896973f, 6291.482422f, 13.117249f, (0.0F), TEMPSUMMON_TIMED_DESPAWN, 60000);
            }
            player->CLOSE_GOSSIP_MENU();
            break;
        }
        }

        return true;
    }

    struct npc_mola_54601AI : public ScriptedAI
    {
        npc_mola_54601AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        bool     m_talk_dc;

        void Reset() override
        {
            m_events.Reset();
            m_talk_dc = false;
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (!m_talk_dc)
                if (Player* player = who->ToPlayer())
                    RandomTalk();
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_TALK_DC:
                {
                    m_talk_dc = false;
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void RandomTalk()
        {
            Talk(0);
            m_talk_dc = true;
            m_events.ScheduleEvent(EVENT_TALK_DC, urand(20000, 60000));
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_mola_54601AI(creature);
    }
};

// 58570
class npc_darkmoon_faire_whack_a_gnoll_bunny_58570 : public CreatureScript
{
public:
    npc_darkmoon_faire_whack_a_gnoll_bunny_58570() : CreatureScript("npc_darkmoon_faire_whack_a_gnoll_bunny_58570") { }

    enum eNpc
    {
        EVENT_CHECK_VISIBLE_BUNNY = 101,
        EVENT_PLAYER_WITH_GAME_IS_AVAIBLE,
    };

    struct npc_darkmoon_faire_whack_a_gnoll_bunny_58570AI : public ScriptedAI
    {
        npc_darkmoon_faire_whack_a_gnoll_bunny_58570AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        bool     m_active_player;

        void Initialize()
        {
            m_events.Reset();
        }

        void Reset() override
        {
            
            m_active_player = false;
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (Player* player = who->ToPlayer())
                if (player->HasAura(101612))
                {
                  
                    
                }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_PLAYER_WITH_GAME_IS_AVAIBLE:
                {
           
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_darkmoon_faire_whack_a_gnoll_bunny_58570AI(creature);
    }
};

// 54444 // 54466 // 54549
class npc_darkmoon_faire_gnoll_54444 : public CreatureScript
{
public:

    npc_darkmoon_faire_gnoll_54444() : CreatureScript("npc_darkmoon_faire_gnoll_54444") { }

    struct npc_darkmoon_faire_gnoll_54444AI : public ScriptedAI
    {
        npc_darkmoon_faire_gnoll_54444AI(Creature* creature) : ScriptedAI(creature) { }

        void IsSummonedBy(Unit* summoner) override
        {

        }

        void JustDied(Unit* killer) override
        {
            switch (me->GetEntry())
            {
            case 54444:
                killer->CastSpell(killer, 101835, true);
                break;
            case 54466:
                killer->CastSpell(killer, 101679, true);
                break;
            case 54549:
                killer->CastSpell(killer, 101835, true);
                killer->CastSpell(killer, 101835, true);
                killer->CastSpell(killer, 101835, true);
                break;
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_darkmoon_faire_gnoll_54444AI(creature);
    }
};

// 54546
class npc_gnoll_barrel : public CreatureScript
{
public:

    npc_gnoll_barrel() : CreatureScript("npc_gnoll_barrel") { }

    struct npc_gnoll_barrelAI : public ScriptedAI
    {
        npc_gnoll_barrelAI(Creature* creature) : ScriptedAI(creature) { }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            printf("SpellHit: %u \n", spell->Id);
        }

        void UpdateAI(uint32 diff) override
        {
            // me->CastSpell(me, 102136);
            // me->SummonCreature(RAND(54444, 54466, 54549), me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, RAND(3000, 4000, 4500));
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_gnoll_barrelAI(creature);
    }
};

// only prepared
class spell_mallet : public SpellScriptLoader
{
public:
    spell_mallet() : SpellScriptLoader("spell_mallet") { }

    class spell_mallet_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mallet_SpellScript);

        //bool Validate(SpellInfo const* spellEntry){return true;} OVERRIDE
        //bool Load(){return true;}
        //void Unload(){ }
        Creature * target;

        void Function()
        {
            if (target = GetCaster()->FindNearestCreature(54444, 1, true))
            {
                GetCaster()->Kill(target);
            }
            if (target = GetCaster()->FindNearestCreature(54466, 1, true))
            {
                GetCaster()->Kill(target);
            }
            if (target = GetCaster()->FindNearestCreature(54549, 1, true))
            {
                GetCaster()->Kill(target);
            }
        }
        //void Function() //OnHit += SpellEffectFn(spell_ex_SpellScript::Function);
        void Register() override
        {
            OnCast += SpellCastFn(spell_mallet_SpellScript::Function);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_mallet_SpellScript();
    }
};

// 15303
class npc_maxima_blastenheimer_15303 : public CreatureScript
{
public:
    npc_maxima_blastenheimer_15303() : CreatureScript("npc_maxima_blastenheimer_15303") { }

    enum eNpc
    {
        MAXIMA_GOSSIP_MENU_ID = 6575,
        MAXIMA_GOSSIP_TEXT_ID = 7789,
        MAXIMA_GOSSIP_MENU_ID2 = 6574,
        MAXIMA_GOSSIP_TEXT_ID2 = 7790,
        EVENT_TALK = 101,
        EVENT_TALK_DC,
    };

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        player->PrepareQuestMenu(creature->GetGUID());
        player->ADD_GOSSIP_ITEM_DB(MAXIMA_GOSSIP_MENU_ID, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        player->ADD_GOSSIP_ITEM_DB(MAXIMA_GOSSIP_MENU_ID, 1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
        player->SEND_GOSSIP_MENU(MAXIMA_GOSSIP_TEXT_ID, creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
        case GOSSIP_ACTION_INFO_DEF + 1:
        {
            player->ADD_GOSSIP_ITEM_DB(MAXIMA_GOSSIP_MENU_ID2, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->SEND_GOSSIP_MENU(MAXIMA_GOSSIP_TEXT_ID2, creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 3:
        {
            player->PrepareQuestMenu(creature->GetGUID());
            player->ADD_GOSSIP_ITEM_DB(MAXIMA_GOSSIP_MENU_ID, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM_DB(MAXIMA_GOSSIP_MENU_ID, 1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->SEND_GOSSIP_MENU(MAXIMA_GOSSIP_TEXT_ID, creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 2:
        {
            Quest const* quest = sObjectMgr->GetQuestTemplate(QUEST_THE_HUMANOID_CANNONBALL);
            if (player->CanTakeQuest(quest, false))
            {
                player->AddQuest(quest, creature);
            }
            if (player->GetQuestStatus(QUEST_THE_HUMANOID_CANNONBALL) == QUEST_STATUS_INCOMPLETE)
            {
                // start shoot
            }            
            player->CLOSE_GOSSIP_MENU();
            break;
        }
        }

        return true;
    }

    struct npc_maxima_blastenheimer_15303AI : public ScriptedAI
    {
        npc_maxima_blastenheimer_15303AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        bool     m_talk_dc;

        void Reset() override
        {
            m_events.Reset();
            m_talk_dc = false;
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (!m_talk_dc)
                if (Player* player = who->ToPlayer())
                    RandomTalk();
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_TALK_DC:
                {
                    m_talk_dc = false;
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void RandomTalk()
        {
            Talk(0);
            m_talk_dc = true;
            m_events.ScheduleEvent(EVENT_TALK_DC, urand(20000, 60000));
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_maxima_blastenheimer_15303AI(creature);
    }
};

// 57850
class npc_teleportologist_fozlebub_57850 : public CreatureScript
{
public:
    npc_teleportologist_fozlebub_57850() : CreatureScript("npc_teleportologist_fozlebub_57850") { }

    enum eNpc
    {
        FOLZEBUB_GOSSIP_MENU_ID = 13352,
        FOLZEBUB_GOSSIP_TEXT_ID1 = 18941,
        FOLZEBUB_GOSSIP_TEXT_ID2 = 18942,
    };

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        player->PrepareQuestMenu(creature->GetGUID());
        player->ADD_GOSSIP_ITEM_DB(FOLZEBUB_GOSSIP_MENU_ID, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        //player->ADD_GOSSIP_ITEM_DB(FOLZEBUB_GOSSIP_MENU_ID, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2); // higher price
        player->ADD_GOSSIP_ITEM_DB(FOLZEBUB_GOSSIP_MENU_ID, 2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
        player->SEND_GOSSIP_MENU(FOLZEBUB_GOSSIP_TEXT_ID1, creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
        case GOSSIP_ACTION_INFO_DEF + 1:
        {
            player->NearTeleportTo(-4018.96f, 6285.51f, 12.4f, 1.359f);
            player->CLOSE_GOSSIP_MENU();
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 3:
        {
            player->CLOSE_GOSSIP_MENU();
            break;
        }
        }

        return true;
    }
};

// 14841
class npc_rinling_14841 : public CreatureScript
{
public:
    npc_rinling_14841() : CreatureScript("npc_rinling_14841") { }

    enum eNpc
    {
        RINLING_GOSSIP_MENU_ID = 6225,
        RINLING_GOSSIP_TEXT_ID = 7398,
        RINLING_GOSSIP_MENU_ID2 = 6574,
        RINLING_GOSSIP_TEXT_ID2 = 18353,
        EVENT_TALK = 101,
        EVENT_TALK_DC,
    };

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        player->PrepareQuestMenu(creature->GetGUID());
        player->ADD_GOSSIP_ITEM_DB(RINLING_GOSSIP_MENU_ID, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        player->ADD_GOSSIP_ITEM_DB(RINLING_GOSSIP_MENU_ID, 1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
        player->SEND_GOSSIP_MENU(RINLING_GOSSIP_TEXT_ID, creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
        case GOSSIP_ACTION_INFO_DEF + 1:
        {
            player->ADD_GOSSIP_ITEM_DB(RINLING_GOSSIP_MENU_ID2, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->SEND_GOSSIP_MENU(RINLING_GOSSIP_TEXT_ID2, creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 3:
        {
            player->PrepareQuestMenu(creature->GetGUID());
            player->ADD_GOSSIP_ITEM_DB(RINLING_GOSSIP_MENU_ID, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM_DB(RINLING_GOSSIP_MENU_ID, 1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->SEND_GOSSIP_MENU(RINLING_GOSSIP_TEXT_ID, creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 2:
        {
            Quest const* quest = sObjectMgr->GetQuestTemplate(QUEST_HE_SHOOTS_HE_SCORES);
            if (player->CanTakeQuest(quest, false))
            {
                player->AddQuest(quest, creature);
            }
            if (player->GetQuestStatus(QUEST_HE_SHOOTS_HE_SCORES) == QUEST_STATUS_INCOMPLETE)
            {
                // start shoot
            }
            player->CLOSE_GOSSIP_MENU();
            break;
        }
        }

        return true;
    }

    struct npc_rinling_14841AI : public ScriptedAI
    {
        npc_rinling_14841AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        bool     m_talk_dc;

        void Reset() override
        {
            m_events.Reset();
            m_talk_dc = false;
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (!m_talk_dc)
                if (Player* player = who->ToPlayer())
                    RandomTalk();
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_TALK_DC:
                {
                    m_talk_dc = false;
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void RandomTalk()
        {
            Talk(0);
            m_talk_dc = true;
            m_events.ScheduleEvent(EVENT_TALK_DC, urand(20000, 60000));
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_rinling_14841AI(creature);
    }
};

// 54485
class npc_jessica_rogers_54485 : public CreatureScript
{
public:
    npc_jessica_rogers_54485() : CreatureScript("npc_jessica_rogers_54485") { }

    enum eNpc
    {
        JESSICA_GOSSIP_MENU_ID = 13012,
        JESSICA_GOSSIP_TEXT_ID = 18284,
        JESSICA_GOSSIP_MENU_ID2 = 13080,
        JESSICA_GOSSIP_TEXT_ID2 = 18369,
        EVENT_TALK = 101,
        EVENT_TALK_DC,
    };

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        player->PrepareQuestMenu(creature->GetGUID());
        player->ADD_GOSSIP_ITEM_DB(JESSICA_GOSSIP_MENU_ID, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        player->ADD_GOSSIP_ITEM_DB(JESSICA_GOSSIP_MENU_ID, 1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
        player->SEND_GOSSIP_MENU(JESSICA_GOSSIP_TEXT_ID, creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
        case GOSSIP_ACTION_INFO_DEF + 1:
        {
            player->ADD_GOSSIP_ITEM_DB(JESSICA_GOSSIP_MENU_ID2, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->SEND_GOSSIP_MENU(JESSICA_GOSSIP_TEXT_ID2, creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 3:
        {
            player->PrepareQuestMenu(creature->GetGUID());
            player->ADD_GOSSIP_ITEM_DB(JESSICA_GOSSIP_MENU_ID, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM_DB(JESSICA_GOSSIP_MENU_ID, 1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->SEND_GOSSIP_MENU(JESSICA_GOSSIP_TEXT_ID, creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 2:
        {
            Quest const* quest = sObjectMgr->GetQuestTemplate(QUEST_TARGET_TURTLE);
            if (player->CanTakeQuest(quest, false))
            {
                player->AddQuest(quest, creature);
            }
            if (player->GetQuestStatus(QUEST_TARGET_TURTLE) == QUEST_STATUS_INCOMPLETE)
            {
                player->CastSpell(player, 101808, true);
            }
            player->CLOSE_GOSSIP_MENU();
            break;
        }
        }

        return true;
    }

    struct npc_jessica_rogers_54485AI : public ScriptedAI
    {
        npc_jessica_rogers_54485AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        bool     m_talk_dc;

        void Reset() override
        {
            m_events.Reset();
            m_talk_dc = false;
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (!m_talk_dc)
                if (Player* player = who->ToPlayer())
                    RandomTalk();
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_TALK_DC:
                {
                    m_talk_dc = false;
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void RandomTalk()
        {
            Talk(0);
            m_talk_dc = true;
            m_events.ScheduleEvent(EVENT_TALK_DC, urand(20000, 60000));
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_jessica_rogers_54485AI(creature);
    }
};

// 54490
class npc_dubenko_54490 : public CreatureScript
{
public:
    npc_dubenko_54490() : CreatureScript("npc_dubenko_54490") { }

    enum eNpc
    {
        
    };

    struct npc_dubenko_54490AI : public ScriptedAI
    {
        npc_dubenko_54490AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_jessicaGUID;

        void Reset() override
        {
            m_events.Reset();
            m_jessicaGUID = 0;
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (!m_jessicaGUID)
                SearchJessica();
            if (Player* player = who->ToPlayer())
                if (player->GetDistance2d(me) < 12.0f)
                    if (Creature* jessica = sObjectAccessor->GetCreature(*me, m_jessicaGUID))
                        jessica->CastSpell(player, SPELL_STAY_OUT, true);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case 1:
                {                    
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void SearchJessica()
        {
            if (Creature* jessica = me->FindNearestCreature(NPC_JESSICA_ROGERS, 30.0f))
                m_jessicaGUID = jessica->GetGUID();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_dubenko_54490AI(creature);
    }
};

// 14871
class npc_morja_14871 : public CreatureScript
{
public:
    npc_morja_14871() : CreatureScript("npc_morja_14871") { }

    enum eNpc
    {
        SAY_WHERE = 3,
        SAY_HELP = 0,
        SAY_HELLO = 2,
        SAY_THANKS = 1,
        PHASE_WAIT = 101,
        PHASE_SEARCH,
        PHASE_GET_HELP,
        EVENT_MASTER_RESET,
        EVENT_SEARCHING_COOLDOWN,
        EVENT_CHECK_FOR_HELP,
        EVENT_ASK_FOR_HELP,
        EVENT_CHECK_FOR_ALE,
        EVENT_WAIT_FOR_JUBJUB,
        EVENT_WELCOME_JUBJUB,
        EVENT_7_DAYS_DELAY,
    };

    struct npc_morja_14871AI : public ScriptedAI
    {
        npc_morja_14871AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_playerGUID2;
        uint64   m_jubjubGUID;
        uint64   m_aleGUID;
        uint8    m_phase;
        uint8    m_max_move;
        bool     m_searching_cooldown;

        void Initialize()
        {
            m_playerGUID2 = 0;
        }

        void Reset() override
        {
            m_events.Reset();
            m_playerGUID = 0;
            m_jubjubGUID = 0;
            m_aleGUID = 0;
            m_phase = PHASE_WAIT;
            m_max_move = 0;
            m_searching_cooldown = false;
        }

        void MovementInform(uint32 type, uint32 id) override 
        { 
            if (m_phase != PHASE_SEARCH || type != WAYPOINT_MOTION_TYPE)
                return;

            if (id == m_max_move)
            {
                m_events.ScheduleEvent(EVENT_CHECK_FOR_HELP, 1000);
                m_events.ScheduleEvent(EVENT_SEARCHING_COOLDOWN, 10000);
            }
            else if (id== 1)
            {
                Talk(SAY_WHERE);
            }
            else if (id > 1)
            {
                me->HandleEmoteCommand(EMOTE_ONESHOT_KNEEL);
            }
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (m_phase != PHASE_WAIT || m_searching_cooldown)
                return;

            if (Player* player = who->ToPlayer())
                if (player->GetDistance2d(me) > 5.0f)
                {
                    uint8 rol = urand(0, 100);
                    if (rol < 50)
                    {
                        me->GetMotionMaster()->MovePath(27036001, false);
                        m_max_move = 4;
                    }
                    else
                    {
                        me->GetMotionMaster()->MovePath(27036002, false);
                        m_max_move = 3;
                    }
                    m_searching_cooldown = true;
                    m_phase = PHASE_SEARCH;
                }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_SEARCHING_COOLDOWN:
                {
                    m_events.CancelEvent(EVENT_CHECK_FOR_HELP);
                    m_phase = PHASE_WAIT;
                    m_max_move = 0;
                    m_searching_cooldown = false;
                    break;
                }
                case EVENT_MASTER_RESET:
                {
                    if (Creature* jubjub = sObjectAccessor->GetCreature(*me, m_jubjubGUID))
                        jubjub->DespawnOrUnsummon();
                    if (GameObject* ale = sObjectAccessor->GetGameObject(*me, m_aleGUID))
                        ale->Delete();
                    Reset();
                    break;
                }
                case EVENT_CHECK_FOR_HELP:
                {
                    CheckHelp();
                    m_events.ScheduleEvent(EVENT_CHECK_FOR_HELP, 1000);
                    break;
                }
                case EVENT_CHECK_FOR_ALE:
                {
                    if (GameObject* ale = me->FindNearestGameObject(165578, 5.0f))
                    {
                        m_aleGUID = ale->GetGUID();
                        if (Creature* jubjub = me->SummonCreature(NPC_JUBJUB, -4187.5f, 6222.5f, 13.12f, 0, TEMPSUMMON_TIMED_DESPAWN, 30000))
                        {
                            m_jubjubGUID = jubjub->GetGUID();
                            jubjub->SetHomePosition(ale->GetPosition());
                            jubjub->GetMotionMaster()->MoveTargetedHome();
                        }
                        m_events.RescheduleEvent(EVENT_MASTER_RESET, 30000);
                        m_events.ScheduleEvent(EVENT_WAIT_FOR_JUBJUB, 500);
                        return;
                    }
                    m_events.ScheduleEvent(EVENT_CHECK_FOR_ALE, 250);
                }
                case EVENT_WAIT_FOR_JUBJUB:
                {
                    if (Creature* jubjub = sObjectAccessor->GetCreature(*me, m_jubjubGUID))
                        if (jubjub->GetDistance2d(me) < 3.0f)
                        {
                            m_events.RescheduleEvent(EVENT_MASTER_RESET, 30000);
                            m_events.ScheduleEvent(EVENT_WELCOME_JUBJUB, 4000);
                            Talk(SAY_HELLO);
                        }
                        else
                            m_events.ScheduleEvent(EVENT_WAIT_FOR_JUBJUB, 500);
                    break;
                }
                case EVENT_WELCOME_JUBJUB:
                {
                    Talk(SAY_THANKS);
                    
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        if (!player->HasSpell(SPELL_SUMMON_JUBLING))
                            if (!player->hasQuest(QUEST_SPAWN_OF_JUBJUB) || player->GetQuestStatus(QUEST_SPAWN_OF_JUBJUB) != QUEST_STATUS_REWARDED)
                            {
                                Quest const* quest = sObjectMgr->GetQuestTemplate(QUEST_SPAWN_OF_JUBJUB);
                                player->AddQuest(quest, me);
                                if (player->GetItemCount(ITEM_DARK_IRON_ALE_MUG) > 0)
                                    player->SetQuestStatus(QUEST_SPAWN_OF_JUBJUB, QUEST_STATUS_COMPLETE);
                                else
                                    player->SetQuestStatus(QUEST_SPAWN_OF_JUBJUB, QUEST_STATUS_INCOMPLETE);
                            }

                    m_events.RescheduleEvent(EVENT_MASTER_RESET, 500);
                    break;
                }
                }
            }
        }

        void CheckHelp()
        {
            if (m_phase == PHASE_GET_HELP)
                return;

            if (Player* player = me->FindNearestPlayer(5.0f))
            {
                m_playerGUID = player->GetGUID();
                Talk(SAY_HELP);
                m_phase = PHASE_GET_HELP;
                m_events.ScheduleEvent(EVENT_MASTER_RESET, 30000);
                m_events.ScheduleEvent(EVENT_CHECK_FOR_ALE, 250);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_morja_14871AI(creature);
    }
};



void AddSC_zone_darkmoon_island()
{
    new npc_mola_54601();
    new npc_darkmoon_faire_gnoll_54444();
    //new npc_gnoll_barrel();
    new npc_darkmoon_faire_whack_a_gnoll_bunny_58570();
    //new spell_mallet();
    new npc_maxima_blastenheimer_15303();
    new npc_teleportologist_fozlebub_57850();
    new npc_rinling_14841();
    new npc_jessica_rogers_54485();
    new npc_dubenko_54490();
    new npc_morja_14871();

}

