/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
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
#include "script_helper.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "SpellInfo.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "Cell.h"
#include "CellImpl.h"

/*####
# npc_omen
####*/

enum Omen
{
    NPC_OMEN                    = 15467,

    SPELL_OMEN_CLEAVE           = 15284,
    SPELL_OMEN_STARFALL         = 26540,
    SPELL_OMEN_SUMMON_SPOTLIGHT = 26392,
    SPELL_ELUNE_CANDLE          = 26374,

    GO_ELUNE_TRAP_1             = 180876,
    GO_ELUNE_TRAP_2             = 180877,

    EVENT_CAST_CLEAVE           = 1,
    EVENT_CAST_STARFALL         = 2,
    EVENT_DESPAWN               = 3,
};

class npc_omen : public CreatureScript
{
public:
    npc_omen() : CreatureScript("npc_omen") { }

    struct npc_omenAI : public ScriptedAI
    {
        npc_omenAI(Creature* creature) : ScriptedAI(creature)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            me->GetMotionMaster()->MovePoint(1, 7549.977f, -2855.137f, 456.9678f);
        }

        EventMap events;

        void MovementInform(uint32 type, uint32 pointId) override
        {
            if (type != POINT_MOTION_TYPE)
                return;

            if (pointId == 1)
            {
                me->SetHomePosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                if (Player* player = me->SelectNearestPlayer(40.0f))
                    AttackStart(player);
            }
        }

        void EnterCombat(Unit* /*attacker*/) override
        {
            events.Reset();
            events.ScheduleEvent(EVENT_CAST_CLEAVE, urand(3000, 5000));
            events.ScheduleEvent(EVENT_CAST_STARFALL, urand(8000, 10000));
        }

        void JustDied(Unit* /*killer*/) override
        {
            DoCast(SPELL_OMEN_SUMMON_SPOTLIGHT);
        }

        void SpellHit(Unit* /*caster*/, const SpellInfo* spell) override
        {
            if (spell->Id == SPELL_ELUNE_CANDLE)
            {
                if (me->HasAura(SPELL_OMEN_STARFALL))
                    me->RemoveAurasDueToSpell(SPELL_OMEN_STARFALL);

                events.RescheduleEvent(EVENT_CAST_STARFALL, urand(14000, 16000));
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            switch (events.ExecuteEvent())
            {
                case EVENT_CAST_CLEAVE:
                    DoCastVictim(SPELL_OMEN_CLEAVE);
                    events.ScheduleEvent(EVENT_CAST_CLEAVE, urand(8000, 10000));
                    break;
                case EVENT_CAST_STARFALL:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        DoCast(target, SPELL_OMEN_STARFALL);
                    events.ScheduleEvent(EVENT_CAST_STARFALL, urand(14000, 16000));
                    break;
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_omenAI(creature);
    }
};

class npc_giant_spotlight : public CreatureScript
{
public:
    npc_giant_spotlight() : CreatureScript("npc_giant_spotlight") { }

    struct npc_giant_spotlightAI : public ScriptedAI
    {
        npc_giant_spotlightAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        void Reset() override
        {
            events.Reset();
            events.ScheduleEvent(EVENT_DESPAWN, 5*MINUTE*IN_MILLISECONDS);
        }

        void UpdateAI(uint32 diff) override
        {
            events.Update(diff);

            if (events.ExecuteEvent() == EVENT_DESPAWN)
            {
                if (GameObject* trap = me->FindNearestGameObject(GO_ELUNE_TRAP_1, 5.0f))
                    trap->RemoveFromWorld();

                if (GameObject* trap = me->FindNearestGameObject(GO_ELUNE_TRAP_2, 5.0f))
                    trap->RemoveFromWorld();

                if (Creature* omen = me->FindNearestCreature(NPC_OMEN, 5.0f, false))
                    omen->DespawnOrUnsummon();

                me->DespawnOrUnsummon();
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_giant_spotlightAI(creature);
    }
};

class npc_druid_only_flights : public CreatureScript
{
public:
    npc_druid_only_flights() : CreatureScript("npc_druid_only_flights") {}

    enum script_enums
    {
        RUTTHERAN_TAXI_NODE = 315,
        THUNDER_TAXI_NODE = 316,
        NPC_SILVA_FILNAVETH = 11800,
        NPC_BUNTHEN = 11798,
        MENU_OPT_FLY_RUTTHERAN = 7573,
        MENU_OPT_FLY_THUNDER_BLUFF = 12804,
        MENU_OPT_PENDANT = 8035,
        TEXT_PENDANT_LOCATION_ALLIANCE = 5373,
        TEXT_PENDANT_LOCATION_HORDE = 5374,
        TEXT_NOT_A_DRUID = 4916
    };


    struct npc_druid_only_flightsAI : public ScriptedAI
    {
        npc_druid_only_flightsAI(Creature* creature) : ScriptedAI(creature) {}

        EventMap _events;

        void Reset() override
        {
            _events.Reset();
        }

        void sGossipHello(Player* player) override
        {
            player->PlayerTalkClass->ClearMenus();

            if (player->getClass() == CLASS_DRUID)
            {
                LocaleConstant locale = player->GetSession()->GetSessionDbLocaleIndex();

                if (me->GetEntry() == NPC_SILVA_FILNAVETH)
                {
                    if (player->GetTeamId() == TEAM_ALLIANCE)
                    {
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, sObjectMgr->GetBroadcastText(MENU_OPT_FLY_RUTTHERAN)->GetText(locale), GOSSIP_SENDER_MAIN, 1);
                        if (player->GetQuestStatus(272) == QUEST_STATUS_INCOMPLETE)
                            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, sObjectMgr->GetBroadcastText(MENU_OPT_PENDANT)->GetText(locale), GOSSIP_SENDER_MAIN, 2);
                        player->SEND_GOSSIP_MENU(4914, me->GetGUID());
                    }
                    else
                        player->SEND_GOSSIP_MENU(4915, me->GetGUID());

                }
                else if (me->GetEntry() == NPC_BUNTHEN)
                {
                    if (player->GetTeamId() == TEAM_HORDE)
                    {
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, sObjectMgr->GetBroadcastText(MENU_OPT_FLY_THUNDER_BLUFF)->GetText(locale), GOSSIP_SENDER_MAIN, 1);
                        if (player->GetQuestStatus(30) == QUEST_STATUS_INCOMPLETE)
                            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, sObjectMgr->GetBroadcastText(MENU_OPT_PENDANT)->GetText(locale), GOSSIP_SENDER_MAIN, 2);
                        player->SEND_GOSSIP_MENU(4918, me->GetGUID());
                    }
                    else
                        player->SEND_GOSSIP_MENU(4917, me->GetGUID());

                }
            } else
                player->SEND_GOSSIP_MENU(TEXT_NOT_A_DRUID, me->GetGUID());
        }

        void sGossipSelect(Player* player, uint32 sender, uint32 action) override
        {
            player->PlayerTalkClass->ClearMenus();

            switch (action)
            {
            case 0:
                player->CLOSE_GOSSIP_MENU();
                if (player->GetTeamId() == TEAM_ALLIANCE)
                    player->ActivateTaxiPathTo(RUTTHERAN_TAXI_NODE);
                else if (player->GetTeamId() == TEAM_HORDE)
                    player->ActivateTaxiPathTo(THUNDER_TAXI_NODE);

                break;
            case 1:
                if (player->GetTeamId() == TEAM_ALLIANCE)
                    player->SEND_GOSSIP_MENU(TEXT_PENDANT_LOCATION_ALLIANCE, me->GetGUID());
                else if (player->GetTeamId() == TEAM_HORDE)
                    player->SEND_GOSSIP_MENU(TEXT_PENDANT_LOCATION_HORDE, me->GetGUID());

                break;

            }

        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_druid_only_flightsAI(creature);
    }
};

void AddSC_moonglade()
{
    new npc_omen();
    new npc_giant_spotlight();
    new npc_druid_only_flights();
}
