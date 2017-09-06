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
SDName: Azuremyst_Isle
SD%Complete: 75
SDComment: Quest support: 26970,9283, 9537, 9582, 9554, ? (special flight path, proper model for mount missing). Injured Draenei cosmetic only, 9582.
SDCategory: Azuremyst Isle
EndScriptData */

/* ContentData
npc_draenei_survivor
npc_engineer_spark_overgrind
npc_injured_draenei_16971
npc_magwin
go_ravager_cage
npc_death_ravager
EndContentData */

#include "script_helper.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "ScriptedGossip.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiersImpl.h"
#include "GridNotifiers.h"

enum Azuremyst_Isle
{
    NPC_DRAENEI_SURVIVOR = 16483,
    NPC_NESTLEWOOD_OWLKIN = 16518,
    NPC_DEATH_RAVAGER = 17556,
    NPC_SPARK_OVERGRIND = 17243,
    NPC_MAGWIN = 17312,
    NPC_STILLPINE_CAPTIVE = 17375,
    NPC_HEALING_CREDIT_16971 = 16971,

    GO_BRISTELIMB_CAGE = 181714,

    QUEST_INOCULATION = 9303,
    QUEST_A_CRY_FOR_SAY_HELP = 9528,
    QUEST_STRENGTH_ONE = 9582,
    QUEST_THE_PROPHECY_OF_AKIDA = 9544,
    QUEST_GNOMERCY = 9537,
    QUEST_AIDING_THE_INJURED_26970 = 26970,

    SPELL_INOCULATE_NESTLEWOOD_OWLKIN = 29528,
    SPELL_STUNNED = 28630,
    SPELL_DYNAMITE = 7978,
    SPELL_REND = 13443,
    SPELL_ENRAGING_BITE = 30736,

    FACTION_HOSTILE = 14,

    AREA_COVE = 3579,
    AREA_ISLE = 3639,

    POINT_INIT = 1,
};

// 16483
class npc_draenei_survivor_16483 : public CreatureScript
{
public:
    npc_draenei_survivor_16483() : CreatureScript("npc_draenei_survivor_16483") { }

    enum draeneiSurvivor
    {
        NPC_DRAENEI_SURVIVOR = 16483,
        SAY_HELP = 2,
        SAY_HEAL = 1,
        SAY_THANKS = 0,
        SPELL_IRRIDATION = 35046,
    };

    struct npc_draenei_survivor_16483AI : public ScriptedAI
    {
        npc_draenei_survivor_16483AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;

        void Reset() override
        {
            m_events.Reset();
            m_events.ScheduleEvent(EVENT_CHECK_PLAYER_NEAR, 1000);
            m_playerGUID = 0;
            me->SetStandState(UNIT_STAND_STATE_SLEEP);
            if (!me->HasAura(SPELL_IRRIDATION))
                DoCast(me, SPELL_IRRIDATION, true);
        }

        void SpellHit(Unit* caster, const SpellInfo* Spell) override
        {
            if (!m_playerGUID)
                if (Spell->Id == 28880 || (Spell->Id >= 59542 && Spell->Id <= 59548) || Spell->Id == 57901)
                {
                    m_playerGUID = caster->GetGUID();
                    m_events.CancelEvent(EVENT_CHECK_PLAYER_NEAR);
                    m_events.ScheduleEvent(EVENT_SAY_THANKS, 6000);
                    Talk(SAY_HEAL);
                    me->SetStandState(UNIT_STAND_STATE_STAND);
                }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_PLAYER_NEAR:
                {
                    if (Player* player = me->FindNearestPlayer(15.0f))
                    {
                        Talk(SAY_HELP);
                        m_events.ScheduleEvent(EVENT_CHECK_PLAYER_NEAR, 10000);
                    }
                    else
                        m_events.ScheduleEvent(EVENT_CHECK_PLAYER_NEAR, 1000);

                    break;
                }
                case EVENT_SAY_THANKS:
                {
                    Talk(SAY_THANKS);
                    me->GetMotionMaster()->Clear();
                    m_events.ScheduleEvent(EVENT_RUN_AWAY, 3000);
                    break;
                }
                case EVENT_RUN_AWAY:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                    {
                        me->GetMotionMaster()->MoveFleeing(player, 10000);
                        player->KilledMonsterCredit(NPC_DRAENEI_SURVIVOR);
                    }
                    m_events.ScheduleEvent(EVENT_FINISH, 5000);
                    break;
                }
                case EVENT_FINISH:
                {
                    me->DespawnOrUnsummon(1);
                    Reset();
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
        return new npc_draenei_survivor_16483AI(creature);
    }
};

// 17243
class npc_engineer_spark_overgrind : public CreatureScript
{
public:
    npc_engineer_spark_overgrind() : CreatureScript("npc_engineer_spark_overgrind") { }

    enum Overgrind
    {
        SAY_TEXT = 0,
        SAY_EMOTE = 1,
        ATTACK_YELL = 2
    };

    struct npc_engineer_spark_overgrindAI : public ScriptedAI
    {
        npc_engineer_spark_overgrindAI(Creature* creature) : ScriptedAI(creature)
        {
            NormFaction = creature->getFaction();
            NpcFlags = creature->GetUInt32Value(UNIT_NPC_FLAGS);

            if (creature->GetAreaId() == AREA_COVE || creature->GetAreaId() == AREA_ISLE)
                IsTreeEvent = true;
        }

        void Reset() override
        {
            DynamiteTimer = 8000;
            EmoteTimer = urand(120000, 150000);

            me->setFaction(NormFaction);
            me->SetUInt32Value(UNIT_NPC_FLAGS, NpcFlags);

            IsTreeEvent = false;
        }

        void EnterCombat(Unit* who) override
        {
            Talk(ATTACK_YELL, who);
        }

        void sGossipSelect(Player* player, uint32 /*sender*/, uint32 /*action*/) override
        {
            player->CLOSE_GOSSIP_MENU();
            me->setFaction(FACTION_HOSTILE);
            me->Attack(player, true);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!me->IsInCombat() && !IsTreeEvent)
            {
                if (EmoteTimer <= diff)
                {
                    Talk(SAY_TEXT);
                    Talk(SAY_EMOTE);
                    EmoteTimer = urand(120000, 150000);
                }
                else EmoteTimer -= diff;
            }
            else if (IsTreeEvent)
                return;

            if (!UpdateVictim())
                return;

            if (DynamiteTimer <= diff)
            {
                DoCastVictim(SPELL_DYNAMITE);
                DynamiteTimer = 8000;
            }
            else DynamiteTimer -= diff;

            DoMeleeAttackIfReady();
        }

    private:
        uint32 NormFaction;
        uint32 NpcFlags;
        uint32 DynamiteTimer;
        uint32 EmoteTimer;
        bool   IsTreeEvent;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_engineer_spark_overgrindAI(creature);
    }
};

// 16971
class npc_injured_draenei_16971 : public CreatureScript
{
public:
    npc_injured_draenei_16971() : CreatureScript("npc_injured_draenei_16971") { }

    struct npc_injured_draenei_16971AI : public ScriptedAI
    {
        npc_injured_draenei_16971AI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IN_COMBAT);
            me->SetHealth(me->CountPctFromMaxHealth(15));
            switch (urand(0, 1))
            {
            case 0:
                me->SetStandState(UNIT_STAND_STATE_SIT);
                break;

            case 1:
                me->SetStandState(UNIT_STAND_STATE_SLEEP);
                break;
            }
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (Player* player = caster->ToPlayer())
                if (player->GetQuestStatus(QUEST_AIDING_THE_INJURED_26970) == QUEST_STATUS_INCOMPLETE)
                    player->KilledMonsterCredit(NPC_HEALING_CREDIT_16971);// New NPC ID
            me->DespawnOrUnsummon(500);
        }


        void EnterCombat(Unit* /*who*/) override { }

        void MoveInLineOfSight(Unit* /*who*/) override { }

        void UpdateAI(uint32 /*diff*/) override { }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_injured_draenei_16971AI(creature);
    }
};

// 17312
class npc_magwin : public CreatureScript
{
public:
    npc_magwin() : CreatureScript("npc_magwin") { }

    enum Magwin
    {
        SAY_START = 0,
        SAY_AGGRO = 1,
        SAY_PROGRESS = 2,
        SAY_END1 = 3,
        SAY_END2 = 4,
        EMOTE_HUG = 5,
        FACTION_QUEST = 113
    };

    struct npc_magwinAI : public npc_escortAI
    {
        npc_magwinAI(Creature* creature) : npc_escortAI(creature) { }

        void Reset() override { }

        void EnterCombat(Unit* who) override
        {
            Talk(SAY_AGGRO, who);
        }

        bool sQuestAccept(Player* player, Quest const* quest)
        {
            if (quest->GetQuestId() == QUEST_A_CRY_FOR_SAY_HELP)
            {
                me->setFaction(FACTION_QUEST);
                npc_escortAI::Start(true, false, player->GetGUID());
            }
            return false;
        }

        void WaypointReached(uint32 waypointId) override
        {
            if (Player* player = GetPlayerForEscort())
            {
                switch (waypointId)
                {
                case 0:
                    Talk(SAY_START, player);
                    break;
                case 17:
                    Talk(SAY_PROGRESS, player);
                    break;
                case 28:
                    Talk(SAY_END1, player);
                    break;
                case 29:
                    Talk(EMOTE_HUG, player);
                    Talk(SAY_END2, player);
                    player->GroupEventHappens(QUEST_A_CRY_FOR_SAY_HELP, me);
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_magwinAI(creature);
    }
};

Position const SparkPos = { -5029.91f, -11291.79f, 8.096f, 0.0f };

// 17318
class npc_geezle : public CreatureScript
{
public:
    npc_geezle() : CreatureScript("npc_geezle_17318") { }

    enum Geezle
    {
        QUEST_TREES_COMPANY = 9531,

        SPELL_TREE_DISGUISE = 30298,

        GEEZLE_SAY_1 = 0,
        SPARK_SAY_2 = 3,
        SPARK_SAY_3 = 4,
        GEEZLE_SAY_4 = 1,
        SPARK_SAY_5 = 5,
        SPARK_SAY_6 = 6,
        GEEZLE_SAY_7 = 2,

        EMOTE_SPARK = 7,

        NPC_SPARK = 17243,
        GO_NAGA_FLAG = 181694
    };

    struct npc_geezleAI : public ScriptedAI
    {
        npc_geezleAI(Creature* creature) : ScriptedAI(creature) { }

        uint64 SparkGUID;

        uint8 Step;
        uint32 SayTimer;

        bool EventStarted;

        void Reset() override
        {
            SparkGUID = 0;
            Step = 0;
            StartEvent();
        }

        void EnterCombat(Unit* /*who*/) override { }

        void StartEvent()
        {
            Step = 0;
            EventStarted = true;
            if (Creature* Spark = me->SummonCreature(NPC_SPARK, SparkPos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000))
            {
                SparkGUID = Spark->GetGUID();
                Spark->setActive(true);
                Spark->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            }
            SayTimer = 8000;
        }

        uint32 NextStep(uint8 Step)
        {
            Creature* Spark = ObjectAccessor::GetCreature(*me, SparkGUID);
            if (!Spark)
                return 99999999;

            switch (Step)
            {
            case 0:
                Spark->GetMotionMaster()->MovePoint(0, -5080.70f, -11253.61f, 0.56f);
                me->GetMotionMaster()->MovePoint(0, -5092.26f, -11252, 0.71f);
                return 9000;
            case 1:
                DespawnNagaFlag(true);
                Spark->AI()->Talk(EMOTE_SPARK);
                return 1000;
            case 2:
                Talk(GEEZLE_SAY_1, Spark);
                Spark->SetInFront(me);
                me->SetInFront(Spark);
                return 5000;
            case 3:
                Spark->AI()->Talk(SPARK_SAY_2);
                return 7000;
            case 4:
                Spark->AI()->Talk(SPARK_SAY_3);
                return 8000;
            case 5:
                Talk(GEEZLE_SAY_4, Spark);
                return 8000;
            case 6:
                Spark->AI()->Talk(SPARK_SAY_5);
                return 9000;
            case 7:
                Spark->AI()->Talk(SPARK_SAY_6);
                return 8000;
            case 8:
                Talk(GEEZLE_SAY_7, Spark);
                return 2000;
            case 9:
                me->GetMotionMaster()->MoveTargetedHome();
                Spark->GetMotionMaster()->MovePoint(0, SparkPos);
                CompleteQuest();
                return 9000;
            case 10:
                Spark->DisappearAndDie();
                DespawnNagaFlag(false);
                me->DisappearAndDie();
            default: return 99999999;
            }
        }

        // will complete Tree's company quest for all nearby players that are disguised as trees
        void CompleteQuest()
        {
            float radius = 50.0f;
            std::list<Player*> players;
            Trinity::AnyPlayerInObjectRangeCheck checker(me, radius);
            Trinity::PlayerListSearcher<Trinity::AnyPlayerInObjectRangeCheck> searcher(me, players, checker);
            me->VisitNearbyWorldObject(radius, searcher);

            for (std::list<Player*>::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                if ((*itr)->GetQuestStatus(QUEST_TREES_COMPANY) == QUEST_STATUS_INCOMPLETE && (*itr)->HasAura(SPELL_TREE_DISGUISE))
                    (*itr)->KilledMonsterCredit(NPC_SPARK, 0);
        }

        void DespawnNagaFlag(bool despawn)
        {
            std::list<GameObject*> FlagList;
            me->GetGameObjectListWithEntryInGrid(FlagList, GO_NAGA_FLAG, 100.0f);

            if (!FlagList.empty())
            {
                for (std::list<GameObject*>::const_iterator itr = FlagList.begin(); itr != FlagList.end(); ++itr)
                {
                    if (despawn)
                        (*itr)->SetLootState(GO_JUST_DEACTIVATED);
                    else
                        (*itr)->Respawn();
                }
            }
            else
                TC_LOG_ERROR("scripts", "SD2 ERROR: FlagList is empty!");
        }

        void UpdateAI(uint32 diff) override
        {
            if (SayTimer <= diff)
            {
                if (EventStarted)
                    SayTimer = NextStep(Step++);
            }
            else
                SayTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_geezleAI(creature);
    }
};

// 181849
class go_ravager_cage : public GameObjectScript
{
public:
    go_ravager_cage() : GameObjectScript("go_ravager_cage") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        go->UseDoorOrButton();
        if (player->GetQuestStatus(QUEST_STRENGTH_ONE) == QUEST_STATUS_INCOMPLETE)
        {
            if (Creature* ravager = go->FindNearestCreature(NPC_DEATH_RAVAGER, 5.0f, true))
            {
                ravager->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                ravager->SetReactState(REACT_AGGRESSIVE);
                ravager->AI()->AttackStart(player);
            }
        }
        return true;
    }
};

// 17556
class npc_death_ravager : public CreatureScript
{
public:
    npc_death_ravager() : CreatureScript("npc_death_ravager") { }

    struct npc_death_ravagerAI : public ScriptedAI
    {
        npc_death_ravagerAI(Creature* creature) : ScriptedAI(creature) { }

        uint32 RendTimer;
        uint32 EnragingBiteTimer;

        void Reset() override
        {
            RendTimer = 30000;
            EnragingBiteTimer = 20000;

            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_PASSIVE);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (RendTimer <= diff)
            {
                DoCastVictim(SPELL_REND);
                RendTimer = 30000;
            }
            else RendTimer -= diff;

            if (EnragingBiteTimer <= diff)
            {
                DoCastVictim(SPELL_ENRAGING_BITE);
                EnragingBiteTimer = 15000;
            }
            else EnragingBiteTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_death_ravagerAI(creature);
    }
};

// 17375
class npc_stillpine_captive : public CreatureScript
{
public:
    npc_stillpine_captive() : CreatureScript("npc_stillpine_captive") { }

    enum BristlelimbCage
    {
        CAPTIVE_SAY = 0,
    };

    struct npc_stillpine_captiveAI : public ScriptedAI
    {
        npc_stillpine_captiveAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            if (GameObject* cage = me->FindNearestGameObject(GO_BRISTELIMB_CAGE, 5.0f))
            {
                cage->SetLootState(GO_JUST_DEACTIVATED);
                cage->SetGoState(GO_STATE_READY);
            }
            _events.Reset();
            _player = nullptr;
            _movementComplete = false;
        }

        void StartMoving(Player* owner)
        {
            if (owner)
            {
                Talk(CAPTIVE_SAY, owner);
                _player = owner;
            }
            Position pos = me->GetNearPosition(3.0f, 0.0f);
            me->GetMotionMaster()->MovePoint(POINT_INIT, pos);
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type != POINT_MOTION_TYPE || id != POINT_INIT)
                return;

            if (_player)
                _player->KilledMonsterCredit(me->GetEntry(), me->GetGUID());

            _movementComplete = true;
            _events.ScheduleEvent(EVENT_DESPAWN_PART_00, 3500);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!_movementComplete)
                return;

            _events.Update(diff);

            if (_events.ExecuteEvent() == EVENT_DESPAWN_PART_00)
                me->DespawnOrUnsummon();
        }

    private:
        Player* _player;
        EventMap _events;
        bool _movementComplete;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_stillpine_captiveAI(creature);
    }
};

// 181714
class go_bristlelimb_cage : public GameObjectScript
{
public:
    go_bristlelimb_cage() : GameObjectScript("go_bristlelimb_cage") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        go->SetGoState(GO_STATE_READY);
        if (player->GetQuestStatus(QUEST_THE_PROPHECY_OF_AKIDA) == QUEST_STATUS_INCOMPLETE)
        {
            if (Creature* captive = go->FindNearestCreature(NPC_STILLPINE_CAPTIVE, 5.0f, true))
            {
                go->ResetDoorOrButton();
                CAST_AI(npc_stillpine_captive::npc_stillpine_captiveAI, captive->AI())->StartMoving(player);
                return false;
            }
        }
        return true;
    }
};

// 16518
class npc_nestlewood_owlkin_16518 : public CreatureScript
{
public:
    npc_nestlewood_owlkin_16518() : CreatureScript("npc_nestlewood_owlkin_16518") { }

    struct npc_nestlewood_owlkin_16518AI : public ScriptedAI
    {
        npc_nestlewood_owlkin_16518AI(Creature* creature) : ScriptedAI(creature) { }

        void SpellHit(Unit * Hitter, SpellInfo const* spell)
        {
            Player* player = Hitter->ToPlayer();

            if (!player)
                return;

            if (spell->Id == SPELL_INOCULATE_NESTLEWOOD_OWLKIN)
            {
                if (player->GetQuestStatus(QUEST_INOCULATION) == QUEST_STATUS_INCOMPLETE)
                {
                    player->KilledMonsterCredit(NPC_NESTLEWOOD_OWLKIN);
                    me->DespawnOrUnsummon(0);
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_nestlewood_owlkin_16518AI(creature);
    }
};

void AddSC_zone_azuremyst_isle()
{
    new npc_draenei_survivor_16483();
    new npc_engineer_spark_overgrind();
    new npc_injured_draenei_16971();
    new npc_magwin();
    new npc_death_ravager();
    new go_ravager_cage();
    new npc_stillpine_captive();
    new go_bristlelimb_cage();
    new npc_nestlewood_owlkin_16518();
}
