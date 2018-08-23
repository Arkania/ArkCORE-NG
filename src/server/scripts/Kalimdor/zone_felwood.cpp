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
SDName: Felwood
SD%Complete: 95
SDComment: Quest support:
SDCategory: Felwood
EndScriptData */

/* ContentData
EndContentData */

#include "script_helper.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Player.h"


// player
class player_zone_felwood : public PlayerScript
{
public:
    player_zone_felwood() : PlayerScript("player_zone_felwood") { }

    enum ePlayer
    {
        QUEST_DO_THE_IMP_POSSIBLE = 28000,
    };

    void OnQuestRemove(Player* player, uint32 questId) override
    {
        switch (questId)
        {
        case QUEST_DO_THE_IMP_POSSIBLE:
            break;
        }
    }
    
    void OnQuestStatusChange(Player* player, uint32 questId, QuestStatus status) override
    {
        switch (questId)
        {
        case QUEST_DO_THE_IMP_POSSIBLE:
            break;
        }
    }
};

// 88254
class spell_swipe_honey_88254 : public SpellScriptLoader 
{
public:
    spell_swipe_honey_88254() : SpellScriptLoader("spell_swipe_honey_88254") { }

    enum eSpell
    {
        SPELL_BEES_BEES = 88426,
        ITEM_DEADWOOD_HONEY_GLOB = 62820,
        NPC_HONEY_BUNNY = 47308,
    };

    class spell_swipe_honey_88254SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_swipe_honey_88254SpellScript);

        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            return true;
        }

        bool Load()
        {
            return true;
        }

        void CheckTarget(WorldObject*& target)
        {
            if (target)
                if (Creature* bees = target->FindNearestCreature(NPC_HONEY_BUNNY, 5.0f))
                    if (Player* player = target->ToPlayer())
                        if (urand(0, 100) > 20)
                        {
                            player->AddItem(ITEM_DEADWOOD_HONEY_GLOB, 1);
                            bees->DespawnOrUnsummon(10);
                        }
                        else
                        {
                            bees->AI()->Talk(0, player);
                            bees->CastSpell(player, SPELL_BEES_BEES, true);
                        }
        }

        void Register()
        {
            OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_swipe_honey_88254SpellScript::CheckTarget, EFFECT_0, TARGET_UNIT_NEARBY_ENTRY);
            //OnEffectHit += SpellEffectFn(spell_swipe_honey_88254SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript *GetSpellScript() const
    {
        return new spell_swipe_honey_88254SpellScript();
    }
};

// 206585
class go_totem_of_ruumbo_206585 : public GameObjectScript
{
public:
    go_totem_of_ruumbo_206585() : GameObjectScript("go_totem_of_ruumbo_206585") { }

    enum eGo
    {
        QUEST_DANCE_FOR_RUUMBO_27995 = 27995,
        SPELL_RUUMBOS_SILLY_DANCE = 88665,
        NPC_FERLI_47558 = 47558,
    };

    bool OnQuestAccept(Player* player, GameObject* go, Quest const* quest) 
    { 
        if (quest->GetQuestId() == QUEST_DANCE_FOR_RUUMBO_27995)
        {
            go->CastSpell(player, SPELL_RUUMBOS_SILLY_DANCE, true);            
            player->HandleEmoteCommand(EMOTE_ONESHOT_DANCE);

            Position pos = Position(3850.44f, -1323.34f, 213.211f, 5.6374f);
            Creature* ferli = go->SummonCreature(NPC_FERLI_47558, pos, TEMPSUMMON_TIMED_DESPAWN, 60000);
            ferli->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
        }

        return false; 
    }
};

// 47558
class npc_ferli_47558 : public CreatureScript
{
public:
    npc_ferli_47558() : CreatureScript("npc_ferli_47558") { }

    enum eNPC
    {
        NPC_RUUMBOS_SILLY_DANCE_CREDIT = 47555,
        NPC_DRIZZLE_48460 = 48460,
    };

    struct npc_ferli_47558AI : public ScriptedAI
    {
        npc_ferli_47558AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap _events;
        uint64   _drizzleGuid;
        uint64   _player_GUID;

        void Initialize()
        {
        }

        void Reset() override
        {
            _drizzleGuid = 0;
            _player_GUID = 0;
            _events.RescheduleEvent(EVENT_START_ANIM, 500);
        }

        void JustSummoned(Creature* summon) override 
        { 
            _drizzleGuid = summon->GetGUID();
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case PLAYER_GUID:
            {
                _player_GUID = guid;
                break;
            }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_ANIM:
                {
                    Position pos = Position(3850.44f, -1323.34f, 213.211f, 5.6374f);
                    me->SummonCreature(NPC_DRIZZLE_48460, pos, TEMPSUMMON_TIMED_DESPAWN, 60000);
                    _events.ScheduleEvent(EVENT_TALK_PART_01, 500);
                    break;
                }
                case EVENT_TALK_PART_01:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, _player_GUID))
                        if (Creature* drizzle = sObjectAccessor->GetCreature(*me, _drizzleGuid))
                            drizzle->AI()->Talk(0, player);

                    _events.ScheduleEvent(EVENT_TALK_PART_02, 7000);
                    break;
                }
                case EVENT_TALK_PART_02:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, _player_GUID))
                        Talk(0, player);

                    _events.ScheduleEvent(EVENT_TALK_PART_03, 4000);
                    break;
                }
                case EVENT_TALK_PART_03:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, _player_GUID))
                        if (Creature* drizzle = sObjectAccessor->GetCreature(*me, _drizzleGuid))
                            drizzle->AI()->Talk(1, player);

                    _events.ScheduleEvent(EVENT_TALK_PART_04, 5000);
                    break;
                }
                case EVENT_TALK_PART_04:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, _player_GUID))
                        Talk(1, player);

                    Position pos1 = Position(3850.069f, -1327.742f, 210.930f, 2.5810f);
                    Position pos2 = Position(3846.036f, -1321.102f, 210.213f, 2.3218f);
                    if (Creature* drizzle = sObjectAccessor->GetCreature(*me, _drizzleGuid))
                        drizzle->GetMotionMaster()->MovePoint(1022, pos1, true);
                    me->GetMotionMaster()->MovePoint(1022, pos2, true);

                    _events.ScheduleEvent(EVENT_TALK_PART_05, 3000);
                    break;
                }
                case EVENT_TALK_PART_05:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, _player_GUID))
                    {
                        player->KilledMonsterCredit(NPC_RUUMBOS_SILLY_DANCE_CREDIT);

                        if (Creature* drizzle = sObjectAccessor->GetCreature(*me, _drizzleGuid))
                            drizzle->AI()->Talk(2, player);
                    }

                    _events.ScheduleEvent(EVENT_TALK_PART_06, 500);
                    break;
                }
                case EVENT_TALK_PART_06:
                {
                    Position pos1 = Position(3811.841f, -1336.789f, 200.430f, 3.6609f);
                    Position pos2 = Position(3771.855f, -1254.947f, 208.221f, 2.4003f);
                    if (Creature* drizzle = sObjectAccessor->GetCreature(*me, _drizzleGuid))
                        drizzle->GetMotionMaster()->MovePoint(1022, pos1, true);
                    me->GetMotionMaster()->MovePoint(1022, pos2, true);

                    _events.ScheduleEvent(EVENT_TALK_PART_07, 3000);
                    break;
                }
                case EVENT_TALK_PART_07:
                {
                    if (Creature* drizzle = sObjectAccessor->GetCreature(*me, _drizzleGuid))
                        drizzle->DespawnOrUnsummon(10);

                    me->DespawnOrUnsummon(10);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_ferli_47558AI(creature);
    }
};

// npc 47339
class npc_impsy_47339 : public CreatureScript
{
public:
    npc_impsy_47339() : CreatureScript("npc_impsy_47339") {}

    enum script_enums
    {
        QUEST_DO_THE_IMP_POSSIBLE = 28000,
        ITEM_ENCHANTED_IMP_SACK = 62899,
        SPELL_ENCHANTED_IMP_SACK_88330 = 88330, // Apply Aura #296: Set Vehicle Id (1264)  used by spawned Impsy 47360
        SPELL_ENCHANTED_IMP_SACK_88354 = 88354, // used by item
        SPELL_GENERIC_QUEST_INVISIBILITY_DETECTION_1 = 49416, // impsy aura=49414 
        NPC_IMPSY_CAPTURE_CREDIT = 47365,
        NPC_IMPSY_47339 = 47339,
        NPC_IMPSY_47360 = 47360,
    };

    struct npc_impsy_47339AI : public ScriptedAI
    {
        npc_impsy_47339AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap  _events;
        bool      _attackTalk;

        void Initialize()
        {
        }

        void Reset() override
        {
            _attackTalk = false;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (Player* player = caster->ToPlayer())
                if (player->GetQuestStatus(QUEST_DO_THE_IMP_POSSIBLE) == QUEST_STATUS_INCOMPLETE)
                    if (me->GetHealthPct() < 2.0f)
                        if (spell->Id == SPELL_ENCHANTED_IMP_SACK_88354)
                        {
                            Talk(4, player);
                            Talk(6, player);
                            player->KilledMonsterCredit(NPC_IMPSY_CAPTURE_CREDIT);
                            me->DespawnOrUnsummon(10); // or spell 88330 transfer as vehicle???
                        }
        }

        void DamageTaken(Unit* attacker, uint32& damage) override 
        { 
            if (Player* player = attacker->ToPlayer())
                if (player->GetQuestStatus(QUEST_DO_THE_IMP_POSSIBLE) == QUEST_STATUS_INCOMPLETE)
                    if (!_attackTalk && (urand(0, 100) > 66)) 
                    {
                        _attackTalk = true;
                        Talk(2, player);
                    }

            if (me->GetHealthPct() < 1.0f)
            {
                damage = 0;
                me->SetHealth(me->GetMaxHealth() / 100);
            }
        }

        void EnterCombat(Unit* who) override
        {
            if (Player* player = who->ToPlayer())
            {
                Talk(0, player);
                me->setActive(true);
            }
        }

        void EnterEvadeMode() 
        {
            _attackTalk = false;
        };

        void JustReachedHome() 
        { 
            if (!_attackTalk)
                me->setActive(false);
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_FOR_PLAYER:
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
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_impsy_47339AI(creature);
    }
};

// npc 47341
class npc_arcanist_delaris_47341 : public CreatureScript
{
public:
    npc_arcanist_delaris_47341() : CreatureScript("npc_arcanist_delaris_47341") {}

    enum eNpc
    {
        QUEST_DO_THE_IMP_POSSIBLE = 28000,
        QUEST_AN_ARCANE_ALLY = 28150,
        NPC_IMPSY = 47339,
        SPELL_GENERIC_QUEST_INVISIBILITY_DETECTION_1 = 49416,
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) 
    { 
        if (player->GetQuestStatus(QUEST_AN_ARCANE_ALLY) == QUEST_STATUS_REWARDED)
            if (quest->GetQuestId() == QUEST_DO_THE_IMP_POSSIBLE)
            {
               // creature->AddAura(SPELL_GENERIC_QUEST_INVISIBILITY_DETECTION_1, player);
            }

        return false; 
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt) override
    {
        if (quest->GetQuestId() == QUEST_DO_THE_IMP_POSSIBLE)
        {
           //impsy Talk(6, player) m ?? spawn impsy shortly near player???
        }
        return true;
    }

};

void AddSC_felwood()
{
    new player_zone_felwood();
    new spell_swipe_honey_88254();
    new go_totem_of_ruumbo_206585();
    new npc_ferli_47558();
    new npc_impsy_47339();
    new npc_arcanist_delaris_47341();
}

