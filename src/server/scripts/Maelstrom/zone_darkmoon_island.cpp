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
    NPC_DARKMOON_FAIRE_GNOLL = 54444,
    NPC_DARKMOON_FAIRE_GNOLL_BABY = 54466,
    NPC_DARKMOON_FAIRE_GNOLL_BONUS = 54549,
    NPC_DARKMOON_FAIRE_GNOLL_BUNNY = 58570,
    NPC_MOLA = 54601,
    NPC_MAXIMA_BLASTENHEIMER = 15303,

    QUEST_ITS_HAMMER_TIME = 29463,
    QUEST_THE_HUMANOID_CANNONBALL = 29436,

    SPELL_WHACK_A_GNOLL_1 = 101612,
    SPELL_WRONG_WHACK = 101679,
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
                //player->AddAura(110230, player);
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

// only prepared
class npc_whacked_gnoll : public CreatureScript
{
public:

    npc_whacked_gnoll() : CreatureScript("npc_whacked_gnoll") { }

    struct npc_whacked_gnollAI : public ScriptedAI
    {
        npc_whacked_gnollAI(Creature* creature) : ScriptedAI(creature) { }

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
        return new npc_whacked_gnollAI(creature);
    }
};

// only prepared
class npc_gnoll_barrel : public CreatureScript
{
public:

    npc_gnoll_barrel() : CreatureScript("npc_gnoll_barrel") { }

    struct npc_gnoll_barrelAI : public ScriptedAI
    {
        npc_gnoll_barrelAI(Creature* creature) : ScriptedAI(creature) { spawn = 10000; }
       
        uint16 spawn;

        virtual void UpdateAI(uint32 diff) override
        {
            if (me->FindNearestCreature(58570, /*distance*/300, /*alive*/true))
                if (spawn<diff)
                {
                    if (RAND(0, 1, 2))
                    {
                        me->CastSpell(me, 102136);
                        me->SummonCreature(RAND(54444, 54466, 54549), me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, RAND(3000, 4000, 4500));
                        spawn = RAND(5000, 6200, 6800);
                    }
                    else
                        spawn = RAND(1000, 2000, 1500);
                }
                else
                    spawn -= diff;
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
            player->NearTeleportTo(-4018.96f, 6285.51f, 12.4f, 1.359);
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


void AddSC_zone_darkmoon_island()
{
    new npc_mola_54601();
    new npc_whacked_gnoll();
    new npc_gnoll_barrel();
    new spell_mallet();
    new npc_maxima_blastenheimer_15303();
    new npc_teleportologist_fozlebub_57850();
}

