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

#include "script_helper.h"
#include "MapManager.h"
#include "GameObject.h"
#include "GameObjectAI.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "SpellScript.h"
#include "Transport.h"
#include "TransportMgr.h"
#include "Vehicle.h"

enum eDurotar
{
    AREA_HORDE_374 = 374,
    AREA_ALLIANCE_4411 = 4411,
    ACTION_CREATE_NAZGRIM = 1000,
    ACTION_CREATE_VANGUARD = 1001,
    ACTION_IS_SHIP_VISIBLE_ALLOWED = 1003,
    GO_SHIP_TO_VASHJIR_197195 = 197195,
    GO_SHIP_TO_VASHJIR_203466 = 203466,

    NPC_CAPTAIN_TAYLOR = 42103,
    NPC_STORMWIND_SOLDIER = 99980,
    NPC_STORMWIND_SOLDIER_42021 = 42021,
    NPC_STORMWIND_SOLDIER_42022 = 42022,
    NPC_STORMWIND_RECRUIT_42059 = 42059,
    NPC_STORMWIND_RECRUIT_42095 = 42095,
    NPC_STORMWIND_RECRUIT_42096 = 42096,
    NPC_HELLSCREAMS_VANGUARD = 43090,
    NPC_LEGIONNAIRE_NAZGRIM = 43100,
    NPC_SHIP_TO_VASHJIR_PHASE_CASTER_BUNNY_40559 = 40559,
    NPC_TOTALLY_GENERIC_BUNNY_PHASE_2 = 43091,

    SPELL_QUEST_GENERIC_ZONE_SPECIFIC_02 = 59074,
    SPELL_QUEST_ZONE_SPECIFIC_02 = 78644,

    QUEST_CALL_OF_DUTY_HORDE = 25924,
    QUEST_CALL_OF_DUTY_ALLIANCE = 14482,
};

enum eNpcVanGuard /* List of database guids of all creature involved bridge/ship to vashjir : Horde*/
{
    eVanGuardAA = 117110,
    eVanGuardAB = 118845,
    eVanGuardBA = 117099,
    eVanGuardBB = 117100,
    eVanGuardBC = 117096,
    eVanGuardCA = 118846,
    eVanGuardCB = 117112,
    eVanGuardDA = 118847,
    eVanGuardNaz = 117111,
};

// player
class player_zone_durotar : public PlayerScript
{
public:
    player_zone_durotar() : PlayerScript("player_zone_durotar") { }

    void OnQuestRemove(Player* player, uint32 questId) override
    {
        switch (questId)
        {
        case 25924:
            player->RemoveAura(59074);
            break;
        }
    }
};

// 10556, Quest 25134:
class npc_lazy_peon : public CreatureScript
{
public:
    npc_lazy_peon() : CreatureScript("npc_lazy_peon") { }


    enum LazyPeonYells
    {
        SAY_SPELL_HIT = 0
    };

    enum LazyPeon
    {
        QUEST_LAZY_PEONS = 25134,
        GO_LUMBERPILE = 175784,
        SPELL_BUFF_SLEEP = 17743,
        SPELL_AWAKEN_PEON = 19938
    };

    struct npc_lazy_peonAI : public ScriptedAI
    {
        npc_lazy_peonAI(Creature* creature) : ScriptedAI(creature) { }

        uint64 PlayerGUID;

        uint32 RebuffTimer;
        bool work;

        void Reset() override
        {
            PlayerGUID = 0;
            RebuffTimer = 0;
            work = false;
        }

        void MovementInform(uint32 /*type*/, uint32 id)
        {
            if (id == 1)
                work = true;
        }

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (spell->Id != SPELL_AWAKEN_PEON)
                return;

            Player* player = caster->ToPlayer();
            if (player && player->GetQuestStatus(QUEST_LAZY_PEONS) == QUEST_STATUS_INCOMPLETE)
            {
                player->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
                Talk(SAY_SPELL_HIT, caster);
                me->RemoveAllAuras();
                if (GameObject* Lumberpile = me->FindNearestGameObject(GO_LUMBERPILE, 20))
                    me->GetMotionMaster()->MovePoint(1, Lumberpile->GetPositionX()-1, Lumberpile->GetPositionY(), Lumberpile->GetPositionZ());
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (work == true)
                me->HandleEmoteCommand(EMOTE_ONESHOT_WORK_CHOPWOOD);
            if (RebuffTimer <= diff)
            {
                DoCast(me, SPELL_BUFF_SLEEP);
                RebuffTimer = 300000; //Rebuff agian in 5 minutes
            }
            else
                RebuffTimer -= diff;
            if (!UpdateVictim())
                return;
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_lazy_peonAI(creature);
    }
};

// 17009
class spell_voodoo : public SpellScriptLoader
{
    public:
        spell_voodoo() : SpellScriptLoader("spell_voodoo") { }


        enum VoodooSpells
        {
            SPELL_BREW = 16712, // Special Brew
            SPELL_GHOSTLY = 16713, // Ghostly
            SPELL_HEX1 = 16707, // Hex
            SPELL_HEX2 = 16708, // Hex
            SPELL_HEX3 = 16709, // Hex
            SPELL_GROW = 16711, // Grow
            SPELL_LAUNCH = 16716, // Launch (Whee!)
        };

        class spell_voodoo_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_voodoo_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_BREW) || !sSpellMgr->GetSpellInfo(SPELL_GHOSTLY) ||
                    !sSpellMgr->GetSpellInfo(SPELL_HEX1) || !sSpellMgr->GetSpellInfo(SPELL_HEX2) ||
                    !sSpellMgr->GetSpellInfo(SPELL_HEX3) || !sSpellMgr->GetSpellInfo(SPELL_GROW) ||
                    !sSpellMgr->GetSpellInfo(SPELL_LAUNCH))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                uint32 spellid = RAND(SPELL_BREW, SPELL_GHOSTLY, RAND(SPELL_HEX1, SPELL_HEX2, SPELL_HEX3), SPELL_GROW, SPELL_LAUNCH);
                if (Unit* target = GetHitUnit())
                    GetCaster()->CastSpell(target, spellid, false);
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_voodoo_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_voodoo_SpellScript();
        }
};

// 39464
class npc_drowned_thunder_lizard_39464 : public CreatureScript
{
public:
    npc_drowned_thunder_lizard_39464() : CreatureScript("npc_drowned_thunder_lizard_39464") { }

    enum eQuest
    {
        QUEST_THUNDER_DOWN_UNDER = 25236,
        NPC_THUNDER_LIZARD = 39464,
        NPC_HULKING_ORCISH_LABORER = 39465,
        SPELL_ATTACH_TETHER = 73945,
        SPELL_LIFT_DROWNED_THUNDER_LIZARD_TARGET = 73950,
        SPELL_LIFT_DROWNED_THUNDER_LIZARD = 73951,
        SPELL_LIGHTNING_DISCHARGE = 73958,
        EVENT_WAIT_ON_HULK = 101,
        EVENT_LIGHTNING_DISCHARGE,
        EVENT_LIFT_DROWNED_THUNDER_LIZARD_TARGET1,
        EVENT_LIFT_DROWNED_THUNDER_LIZARD_TARGET2,
        EVENT_RESET_FOR_HULK,
    };

    struct npc_drowned_thunder_lizard_39464AI : public ScriptedAI
    {
        npc_drowned_thunder_lizard_39464AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_hulkGUID;
        uint64   m_playerGUID;
        bool m_isWorking;
        std::list<Position> m_hulkList;

        void Initialize()
        {
            m_hulkGUID = 0;
            m_playerGUID = 0;            
            FillHulkPositionList();
        }

        void Reset() override
        {           
            m_events.Reset();
            m_events.ScheduleEvent(EVENT_LIGHTNING_DISCHARGE, urand(20000, 60000));
            m_isWorking = false;
        }

        void OnSpellClick(Unit* clicker, bool& result) 
        { 
            if (!m_isWorking)
            if (Player* player = clicker->ToPlayer())
                if (player->GetQuestStatus(QUEST_THUNDER_DOWN_UNDER) == QUEST_STATUS_INCOMPLETE)
                {
                    m_isWorking = true;
                    m_playerGUID = player->GetGUID();
                    m_events.ScheduleEvent(EVENT_WAIT_ON_HULK, 250);
                    m_events.ScheduleEvent(EVENT_RESET_FOR_HULK, 10000);
                }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_LIGHTNING_DISCHARGE:
                    {
                        me->CastSpell(me, SPELL_LIGHTNING_DISCHARGE);
                        m_events.ScheduleEvent(EVENT_LIGHTNING_DISCHARGE, urand(30000, 60000));
                        break;
                    }
                    case EVENT_WAIT_ON_HULK:
                    {
                        if (Creature* hulk = me->FindNearestCreature(NPC_HULKING_ORCISH_LABORER, 15.0f))
                        {
                            m_hulkGUID = hulk->GetGUID();
                            Position pos = FindBestHulkPosition(hulk->GetPosition());
                            hulk->NearTeleportTo(pos.m_positionX, pos.m_positionY, pos.m_positionZ, pos.m_orientation, true);
                            m_events.ScheduleEvent(EVENT_LIFT_DROWNED_THUNDER_LIZARD_TARGET1, 25);
                        }
                        else
                            m_events.ScheduleEvent(EVENT_WAIT_ON_HULK, 100);

                        break;
                    }
                    case EVENT_LIFT_DROWNED_THUNDER_LIZARD_TARGET1:
                    {
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                            if (Creature* hulk = sObjectAccessor->GetCreature(*me, m_hulkGUID))
                            {
                                hulk->CastSpell(me, SPELL_LIFT_DROWNED_THUNDER_LIZARD, true);
                                hulk->CastSpell(hulk, SPELL_LIFT_DROWNED_THUNDER_LIZARD_TARGET, true);
                            }

                        m_events.ScheduleEvent(EVENT_LIFT_DROWNED_THUNDER_LIZARD_TARGET2, 2000);
                        break;
                    }
                    case EVENT_LIFT_DROWNED_THUNDER_LIZARD_TARGET2:
                    {
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                            if (Creature* hulk = sObjectAccessor->GetCreature(*me, m_hulkGUID))
                            {
                                Position pos = me->GetPosition();
                                pos.m_positionZ = 12.0f;
                                me->SetCanFly(true);
                                me->SetDisableGravity(true);
                                me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_HOVER);
                                me->SetSpeed(MOVE_RUN, 0.15f, true);
                                me->GetMotionMaster()->MoveTakeoff(101, pos);
                                me->DespawnOrUnsummon(10000);
                                hulk->DespawnOrUnsummon(10000);
                            }
                        break;
                    }
                    case EVENT_RESET_FOR_HULK:
                    {
                        Reset();
                        break;
                    }
                }
            }
        }

        Position FindBestHulkPosition(Position pos)
        {
            float dist = 500.0f;
            Position newPos;
            for (std::list<Position>::iterator itr = m_hulkList.begin(); itr != m_hulkList.end(); ++itr)
            {
                Position p = (*itr);
                float d = p.GetExactDist2d(pos.m_positionX, pos.m_positionY);
                if (d < dist)
                {
                    dist = d; 
                    newPos = p;
                }
            }
            return newPos;
        }

        void FillHulkPositionList()
        {
            m_hulkList.clear();
            m_hulkList.push_back(Position(761.681519f, -4114.352539f, 27.533762f, 1.669859f));
            m_hulkList.push_back(Position(789.240173f, -4105.788574f, 26.680470f, 1.956528f));
            m_hulkList.push_back(Position(843.065918f, -4059.360596f, 27.911030f, 2.596630f));
            m_hulkList.push_back(Position(769.185669f, -4030.059082f, 26.620789f, 4.336287f));
            m_hulkList.push_back(Position(868.856018f, -4027.161377f, 32.579823f, 3.539107f));
            m_hulkList.push_back(Position(885.622131f, -4024.350342f, 33.658619f, 6.154483f));
            m_hulkList.push_back(Position(921.469360f, -4034.692871f, 36.609566f, 0.256142f));
            m_hulkList.push_back(Position(961.751343f, -4070.507324f, 23.249489f, 2.918641f));
            m_hulkList.push_back(Position(945.061340f, -4078.592041f, 27.331806f, 0.558519f));
            m_hulkList.push_back(Position(941.900757f, -4121.144043f, 23.914780f, 5.867807f));
            m_hulkList.push_back(Position(899.980408f, -4170.012207f, 24.881603f, 1.709126f));
            m_hulkList.push_back(Position(965.486877f, -4204.474121f, 22.279196f, 3.095355f));
            m_hulkList.push_back(Position(940.573730f, -4231.450195f, 20.181242f, 5.592918f));
            m_hulkList.push_back(Position(905.344482f, -4176.950195f, 26.277588f, 0.307187f));
            m_hulkList.push_back(Position(972.444702f, -4222.325684f, 22.747892f, 3.550868f));
            m_hulkList.push_back(Position(801.102844f, -4089.484619f, 25.795090f, 4.882112f));
            m_hulkList.push_back(Position(810.994995f, -4087.808594f, 25.023535f, 5.612078f));
            m_hulkList.push_back(Position(829.534973f, -4022.998779f, 20.646587f, 4.626402f));
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_drowned_thunder_lizard_39464AI(creature);
    }
};

// 80962
class spell_kill_golden_stonefish_80962 : public SpellScriptLoader
{
public:
    spell_kill_golden_stonefish_80962() : SpellScriptLoader("spell_kill_golden_stonefish_80962") { }

    enum eSpell
    {
        NPC_GOLDEN_STONEFISH = 43331,
    };

    class spell_kill_golden_stonefish_80962_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_kill_golden_stonefish_80962_SpellScript);

        void SelectTarget(std::list<WorldObject*>& targets)
        {
            std::list<WorldObject*> list;
            for (std::list<WorldObject*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                if ((*itr)->ToCreature() && (*itr)->GetEntry() == NPC_GOLDEN_STONEFISH)
                    list.push_back((*itr));

            targets = list;
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_kill_golden_stonefish_80962_SpellScript::SelectTarget, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_kill_golden_stonefish_80962_SpellScript();
    }
};

// 39380
class npc_shin_stonepillar_39380 : public CreatureScript
{
public:
    npc_shin_stonepillar_39380() : CreatureScript("npc_shin_stonepillar_39380") { }

    enum eNPC
    {
        QUEST_THE_KODO_AND_THE_WOLF = 25205,
        PLAYER_GUID = 99999,
        SPELL_SUMMON_THE_WOLF = 73840,
        SPELL_QUEST_INVIS_KODO_AND_THE_WOLF = 73919,
        SPELL_SEE_QUEST_INVIS_01 = 73426,
    };

    bool OnGossipHello(Player* player, Creature* creature) override
    { 
        if (player->GetQuestStatus(QUEST_THE_KODO_AND_THE_WOLF) == QUEST_STATUS_INCOMPLETE)
        {
            player->PrepareQuestMenu(creature->GetGUID());
            player->ADD_GOSSIP_ITEM_DB(11209, 0, GOSSIP_SENDER_MAIN, 1001);
            player->SEND_GOSSIP_MENU(11209, creature->GetGUID());
            return true;
        }

        return false;     
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override 
    { 
        if (action == 1001)
        {
            player->CastSpell(player, SPELL_SUMMON_THE_WOLF);
            player->CastSpell(player, SPELL_SEE_QUEST_INVIS_01);            
            player->CLOSE_GOSSIP_MENU();
            return true;
        }

        return false; 
    }
};

// 39364
class npc_the_wolf_39364 : public CreatureScript
{
public:
    npc_the_wolf_39364() : CreatureScript("npc_the_wolf_39364") { }

    enum eNPC
    {
        NPC_SHIN_STONEPILLAR = 39380,
        NPC_KODO = 39365,
        SPELL_HUNTING = 73841,
        SPELL_STUN_WOLF = 73866,
        SPELL_RUMBLING_HOOVES = 73868,
        SPELL_PLAYER_SWITCHES_SEATS = 82959,
        SPELL_PERMANENT_FEIGN_DEATH = 29266,
        SPELL_QUEST_INVIS_KODO_AND_THE_WOLF = 73919,
        SPELL_SEE_QUEST_INVIS_01 = 73426,
        PHASE_START_TO_EAST = 0,
        PHASE_SEARCHING_FOR_KODO,
        PHASE_WAITING_FOR_EAT,
        EVENT_CHECK_POSITION,
        EVENT_CHECK_KODOS,
        EVENT_TALK_SEARCHING,
        EVENT_KODOS_FIGHTING,
        EVENT_TRY_EAT_KODO,
    };

    struct npc_the_wolf_39364_AI : public VehicleAI
    {
        npc_the_wolf_39364_AI(Creature* creature) : VehicleAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_shinGUID;
        uint64   m_kodo1GUID, m_kodo2GUID;
        uint8    m_phase;

        void Reset() override
        {
            m_events.Reset();
            m_events.ScheduleEvent(EVENT_CHECK_POSITION, 1000);
            m_phase = PHASE_START_TO_EAST;
            m_playerGUID = 0;
            m_shinGUID = 0;
            m_kodo1GUID = 0;
            m_kodo2GUID = 0;
            FindShinStonepillar();
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
                m_playerGUID = player->GetGUID();
        }

        void PassengerBoarded(Unit* passenger, int8 /*seatId*/, bool apply) override
        {
            if (Player* player = passenger->ToPlayer())
                if (apply)
                    m_playerGUID = player->GetGUID();
                else
                    m_playerGUID = 0;
            
            FindShinStonepillar();
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_POSITION:
                {
                    switch (m_phase)
                    {
                    case PHASE_START_TO_EAST:
                    {
                        if (Creature* shin = sObjectAccessor->GetCreature(*me, m_shinGUID))
                            if (shin->GetDistance2d(me) < 10.0f)
                                m_phase = PHASE_START_TO_EAST;
                            else
                            {
                                if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                                    Talk(0, player);

                                m_phase = PHASE_SEARCHING_FOR_KODO;
                                me->AddAura(SPELL_HUNTING, me);
                                m_events.ScheduleEvent(EVENT_TALK_SEARCHING, urand(5000, 7000));
                                m_events.ScheduleEvent(EVENT_CHECK_KODOS, 1000);
                            }
                        break;
                    }
                    case PHASE_SEARCHING_FOR_KODO:
                    {
                        if (Creature* shin = sObjectAccessor->GetCreature(*me, m_shinGUID))
                            if (shin->GetDistance2d(me) < 10.0f)
                                m_phase = PHASE_START_TO_EAST;

                        if (Creature* kodo = sObjectAccessor->GetCreature(*me, m_kodo1GUID))
                            if (kodo->GetDistance2d(me) < 20)
                            {
                                m_phase = PHASE_WAITING_FOR_EAT;
                                m_events.Reset();
                                m_events.ScheduleEvent(EVENT_TRY_EAT_KODO, 100);
                                return;
                            }
                        break;
                    }
                    }
                    m_events.ScheduleEvent(EVENT_CHECK_POSITION, 1000);
                    break;
                }
                case EVENT_TALK_SEARCHING:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(4, player);
                    m_events.ScheduleEvent(EVENT_TALK_SEARCHING, urand(5000, 7000));
                    break;
                }
                case EVENT_CHECK_KODOS:
                {
                    if (!m_kodo1GUID || !m_kodo2GUID)
                    {
                        std::list<Creature*> kodos = me->FindNearestCreatures(NPC_KODO, 100.0f);
                        if (kodos.size() == 2)
                        {
                            std::list<Creature*>::iterator itr = kodos.begin();
                            m_kodo1GUID = (*itr)->GetGUID();
                            itr++;
                            m_kodo2GUID = (*itr)->GetGUID();
                        }
                        m_events.ScheduleEvent(EVENT_CHECK_KODOS, 1000);
                    }
                    else
                        m_events.ScheduleEvent(EVENT_KODOS_FIGHTING, urand(2000, 4000));

                    break;
                }
                case EVENT_KODOS_FIGHTING:
                {
                    if (Creature* kodo1 = sObjectAccessor->GetCreature(*me, m_kodo1GUID))
                        if (Creature* kodo2 = sObjectAccessor->GetCreature(*me, m_kodo2GUID))
                        {
                            kodo1->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK_UNARMED);
                            kodo2->HandleEmoteCommand(EMOTE_ONESHOT_WOUND);
                        }

                    m_events.ScheduleEvent(EVENT_KODOS_FIGHTING, urand(2000,4000));
                    break;
                }
                case EVENT_TRY_EAT_KODO:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(1, player);
                    me->SetControlled(true, UNIT_STATE_ROOT);
                    me->GetMotionMaster()->Clear();
                    m_events.ScheduleEvent(EVENT_TRY_EAT_KODO + 1, 2000);
                    break;
                }
                case EVENT_TRY_EAT_KODO + 1:
                {
                    if (Creature* kodo1 = sObjectAccessor->GetCreature(*me, m_kodo1GUID))
                        kodo1->HandleEmoteCommand(EMOTE_ONESHOT_SPELL_CAST);
                    if (Creature* kodo2 = sObjectAccessor->GetCreature(*me, m_kodo2GUID))
                        kodo2->HandleEmoteCommand(EMOTE_ONESHOT_WOUND_CRITICAL);

                    m_events.ScheduleEvent(EVENT_TRY_EAT_KODO + 2, 4000);
                    break;
                }
                case EVENT_TRY_EAT_KODO + 2:
                {
                    if (Creature* kodo1 = sObjectAccessor->GetCreature(*me, m_kodo1GUID))
                        if (Creature* kodo2 = sObjectAccessor->GetCreature(*me, m_kodo2GUID))
                        {
                            kodo1->HandleEmoteCommand(EMOTE_ONESHOT_SPELL_CAST);
                            kodo1->Kill(kodo2);
                        }
                    // kodo2->HandleEmoteState(EMOTE_STATE_DEAD);

                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(2, player);

                    m_events.ScheduleEvent(EVENT_TRY_EAT_KODO + 3, 2000);
                    break;
                }
                case EVENT_TRY_EAT_KODO + 3:
                {
                    Position pos;
                    if (Creature* kodo = sObjectAccessor->GetCreature(*me, m_kodo2GUID))
                    {
                        me->SetSpeed(MOVE_WALK, 0.7f, true);
                        me->GetMotionMaster()->MovePoint(1234, kodo->GetNearPosition(3.0f, kodo->GetAngle(me)));
                    }

                    m_events.ScheduleEvent(EVENT_TRY_EAT_KODO + 4, 4000);
                    break;
                }
                case EVENT_TRY_EAT_KODO + 4:
                {
                    m_events.Reset();
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(3, player);

                    if (Creature* kodo = sObjectAccessor->GetCreature(*me, m_kodo1GUID))
                    {
                        kodo->CastSpell(me, SPELL_STUN_WOLF);
                        me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_DISABLE_TURN);
                        kodo->CastSpell(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), SPELL_RUMBLING_HOOVES, true);
                        kodo->CastSpell(me, SPELL_PLAYER_SWITCHES_SEATS, true);
                    }

                    m_events.ScheduleEvent(EVENT_TRY_EAT_KODO + 5, 3000);
                    break;
                }
                case EVENT_TRY_EAT_KODO + 5:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        player->KilledMonsterCredit(NPC_KODO);

                    m_events.ScheduleEvent(EVENT_TRY_EAT_KODO + 6, 6000);
                    break;
                }
                case EVENT_TRY_EAT_KODO + 6:
                {
                    me->DespawnOrUnsummon(200);

                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                    {
                        player->RemoveAura(SPELL_SEE_QUEST_INVIS_01);
                        player->NearTeleportTo(1287.98f, -4336.36f, 34.0345f, 3.176133f);
                    }
                    break;
                }
                }
            }
        }

        void FindShinStonepillar()
        {
            if (m_shinGUID)
                return;

            if (Creature* shin = me->FindNearestCreature(NPC_SHIN_STONEPILLAR, 10.0f))
                m_shinGUID = shin->GetGUID();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_the_wolf_39364_AI(creature);
    }
};

// 73868
class spell_rumbling_hooves_73868 : public SpellScriptLoader
{
public:
    spell_rumbling_hooves_73868() : SpellScriptLoader("spell_rumbling_hooves_73868") { }

    enum eSpell
    {
        NPC_THE_WOLF = 39364,
    };

    class IsEntry
    {
    public:
        explicit IsEntry(uint32 entry) : _entry(entry) { }

        bool operator()(WorldObject* obj) const
        {
            if (Creature* target = obj->ToCreature())
                return target->GetEntry() == _entry;

            return true;
        }

    private:
        uint32 _entry;
    };

    class spell_rumbling_hooves_73868_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rumbling_hooves_73868_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if(IsEntry(GetCaster()->GetEntry()));
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_rumbling_hooves_73868_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_rumbling_hooves_73868_SpellScript();
    }
};

// 39365
class npc_the_kodo_39365 : public CreatureScript
{
public:
    npc_the_kodo_39365() : CreatureScript("npc_the_kodo_39365") { }

    enum eNPC
    {
        SPELL_QUEST_INVIS_KODO_AND_THE_WOLF = 73919,
    };

    struct npc_the_kodo_39365AI : public ScriptedAI
    {
        npc_the_kodo_39365AI(Creature* creature) : ScriptedAI(creature) {}
       
        void Reset() override
        {
            me->AddAura(SPELL_QUEST_INVIS_KODO_AND_THE_WOLF, me);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_the_kodo_39365AI(creature);
    }
};

// 41621
class npc_commander_thorak_41621 : public CreatureScript
{
public:
    npc_commander_thorak_41621() : CreatureScript("npc_commander_thorak_41621") { }

    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest) override 
    { 
        switch (quest->GetQuestId())
        {
        case QUEST_CALL_OF_DUTY_HORDE:
            player->CastSpell(player, SPELL_QUEST_GENERIC_ZONE_SPECIFIC_02, true);
            break;
        }
        return false; 
    }
};

/* Start Quest: Call of Duty.. */

/* 32520 bunny (!!! ally & horde !!!), as commander outside ship, check for player near and active quest...   
first starting the animation on bridge... then let guards go upto ship. there spawns new version of them and at last, the AI of each ship is started, to do furter communication */
class npc_totally_generic_bunny_all_phase_32520 : public CreatureScript
{
public:
    npc_totally_generic_bunny_all_phase_32520() : CreatureScript("npc_totally_generic_bunny_all_phase_32520") { }

    struct npc_totally_generic_bunny_all_phase_32520AI : public ScriptedAI
    {
        npc_totally_generic_bunny_all_phase_32520AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        bool     m_playerNearFlag;
        uint32   m_areaId;
        uint64   m_vashjirShipGUID;
        uint32   m_lastShipEventId;
        uint32   m_animState;                   // 0=not started 1=started 2=talk started 3=nazgrim anim 4=ship boarding 5=map1 6=map0
        uint64   m_commanderGUID;
        std::map<uint32, uint64> m_guardsGUID;  // dbGuid, GUID 

        void Initialize()
        {
            m_playerNearFlag=false;
            m_vashjirShipGUID = 0;
            m_areaId = 0;
            m_lastShipEventId = 0;
            m_animState = 0;
            m_commanderGUID = 0;
        }

        void Reset() override
        {
            switch (me->GetAreaId())
            {
            case AREA_ALLIANCE_4411:
            case AREA_HORDE_374:
                if (abs(me->GetPositionZ() - 30.00427f) < 1.0f)
                    m_areaId = me->GetAreaId();
                break;
            }
        }

        void CreatureMoveInLineOfSight(Unit* who) override
        {
            if (Player* player = who->ToPlayer())
                if (m_areaId == AREA_ALLIANCE_4411 || m_areaId == AREA_HORDE_374)
                {
                    me->setActive(true);
                    m_events.RescheduleEvent(EVENT_SET_ACTIVE_TO_FALSE, 10 * MINUTE * 1000);
                }

            if (!m_vashjirShipGUID || m_commanderGUID || m_guardsGUID.size() < 8)
                FindAllMembersWorldwide();
        }

        uint32 GetData(uint32 id = 0) const override
        { 
            switch (id)
            {
            case ACTION_IS_SHIP_VISIBLE_ALLOWED:
            {
                bool _ok = PlayerWithActiveQuestIsNear();                
                if (m_commanderGUID == 0)
                    _ok = false;
                if (m_guardsGUID.size() < 8)
                    _ok = false;
                if (m_areaId == AREA_HORDE_374 && m_animState < 2)
                    _ok = false;
                else if (m_areaId == AREA_ALLIANCE_4411 && m_animState < 12)
                    _ok = false;

                return (uint32)(_ok); 
            }
            case 1:
                return m_lastShipEventId;
            case 2:
                return m_animState;
            }
            return 0; 
        }

        void DoAction(int32 param) override
        {
            if (param > 22500 && param < 27000)
                m_lastShipEventId = param;
            
            if (m_areaId == AREA_HORDE_374)
                HandleDoActionHorde(param);
            else if (m_areaId == AREA_ALLIANCE_4411)
                HandleDoActionAlliance(param);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);
            
            while (uint32 eventId = m_events.ExecuteEvent())
            {
                if (m_areaId == AREA_HORDE_374)
                    HandleUpdateAIHorde(eventId);
                else if (m_areaId == AREA_ALLIANCE_4411)
                    HandleUpdateAIAlliance(eventId);

                switch (eventId)
                {
                case EVENT_SET_ACTIVE_TO_FALSE:
                    if (PlayerWithActiveQuestIsNear())
                    {
                        me->setActive(true);
                        m_events.RescheduleEvent(EVENT_SET_ACTIVE_TO_FALSE, 10 * MINUTE * 1000);
                    }
                    else
                        me->setActive(false);
                    break;
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        bool PlayerWithActiveQuestIsNear() const
        {
            std::list<Player*> pList = me->FindNearestPlayers(100.0f);
            for (auto player : pList)
                if (player->GetPosition().GetExactDist(me) < 100.0f)
                    if (m_areaId == AREA_HORDE_374 && player->GetQuestStatus(QUEST_CALL_OF_DUTY_HORDE) == QUEST_STATUS_INCOMPLETE)
                        return true;
                    else if (m_areaId == AREA_ALLIANCE_4411 && player->GetQuestStatus(QUEST_CALL_OF_DUTY_ALLIANCE) == QUEST_STATUS_INCOMPLETE)
                        return true;

            return false;
        }

        GameObject* FindGameObjectWorldwide(uint32 entry)
        {
            TRINITY_READ_GUARD(HashMapHolder<GameObject>::LockType, *HashMapHolder<GameObject>::GetLock());
            HashMapHolder<GameObject>::MapType const& m = ObjectAccessor::GetGameObjects();
            for (HashMapHolder<GameObject>::MapType::const_iterator iter = m.begin(); iter != m.end(); ++iter)
                if (GameObject* ship = iter->second->ToGameObject())
                    if (ship->IsInWorld())
                        if (ship->GetEntry() == entry)
                            return ship;

            return nullptr;
        }

        void FindAllMembersWorldwide()
        {
            if (m_areaId == AREA_HORDE_374)
            {
                if (!m_vashjirShipGUID)
                    if (GameObject* ship = FindGameObjectWorldwide(GO_SHIP_TO_VASHJIR_203466))
                    {
                        m_vashjirShipGUID = ship->GetGUID();
                        ship->AI()->SetGUID(me->GetGUID(), me->GetEntry());
                    }
                if (!m_commanderGUID || m_guardsGUID.size() < 8)
                {
                    std::list<Creature*> cList;
                    m_guardsGUID.clear();
                    m_commanderGUID = 0;

                    if (m_areaId == AREA_HORDE_374)
                    {
                        cList = me->FindAllCreaturesInRange(75.0f);
                        for (auto npc : cList)
                            switch (npc->GetEntry())
                            {
                            case NPC_HELLSCREAMS_VANGUARD:
                                m_guardsGUID.insert(std::pair<uint32, uint64>(npc->GetDBTableGUIDLow(), npc->GetGUID())); // npc->AI()->GetData(NPC_HELLSCREAMS_VANGUARD)
                                break;
                            case NPC_LEGIONNAIRE_NAZGRIM:
                                m_commanderGUID = npc->GetGUID();
                                break;
                            }
                    }
                }
            }
            else if (m_areaId == AREA_ALLIANCE_4411)
            {
                if (!m_vashjirShipGUID)
                    if (GameObject* ship = FindGameObjectWorldwide(GO_SHIP_TO_VASHJIR_197195))
                    {
                        m_vashjirShipGUID = ship->GetGUID();
                        ship->AI()->SetGUID(me->GetGUID(), me->GetEntry());
                    }
                if (!m_commanderGUID || m_guardsGUID.size() < 8)
                {
                    std::list<Creature*> cList;
                    m_guardsGUID.clear();
                    m_commanderGUID = 0;

                    cList = me->FindAllCreaturesInRange(75.0f);
                    for (auto npc : cList)
                        switch (npc->GetEntry())
                        {
                        case NPC_STORMWIND_SOLDIER_42021:
                        case NPC_STORMWIND_SOLDIER_42022:
                        case NPC_STORMWIND_RECRUIT_42059:
                        case NPC_STORMWIND_RECRUIT_42095:
                        case NPC_STORMWIND_RECRUIT_42096:
                            m_guardsGUID.insert(std::pair<uint32, uint64>(npc->GetDBTableGUIDLow(), npc->GetGUID())); // npc->AI()->GetData(NPC_STORMWIND_SOLDIER)
                            break;
                        case NPC_CAPTAIN_TAYLOR:
                            m_commanderGUID = npc->GetGUID();
                            break;
                        }
                }
            }
        }

        Creature* GetStoredCreature(uint32 dbGuid)
        {
            if (m_guardsGUID.find(dbGuid) == m_guardsGUID.end())
                return nullptr;

            if (uint64 guid = m_guardsGUID[dbGuid])
                if (Creature* npc = sObjectAccessor->GetCreature(*me, guid))
                    return npc;

            return nullptr;
        }

/* Horde */

        void TryStartAnimHorde()
        {

            FindAllMembersWorldwide();

            if (m_animState != 0)
                return;

            if (!PlayerWithActiveQuestIsNear())
                return;

            if (m_guardsGUID.size() < 8)
                return;

            if (!m_commanderGUID)
                return;

            switch (m_lastShipEventId)
            {
            case 25489:
            case 25448:
            case 25428:
                m_animState = 1; // we can start the anim on next ship event
                m_events.ScheduleEvent(EVENT_START_ANIM, 1000);
                break;
            default:
                return;
            }
        }

        void HandleDoActionHorde(int32 param)
        {
            TryStartAnimHorde();

            switch (param) //Part: Horde ship eventIds
            {
            case 25448:
                break;
            case 25428:
                break;
            case 26605: // ship teleport to map 1
                if (m_animState == 1)
                {
                    m_animState = 2;
                    m_events.ScheduleEvent(EVENT_START_ANIM_01, 30000);
                }
                else
                    m_animState = 0;
                break;
            case 25447: // inside curve, before bridge                
                break;
            case 25445: // arrive bridge
                if (m_animState == 3)
                {
                    if (Creature* npc = sObjectAccessor->GetCreature(*me, m_commanderGUID))
                    {
                        npc->AI()->SetGUID(m_vashjirShipGUID, GO_SHIP_TO_VASHJIR_203466);
                        npc->AI()->DoAction(ACTION_START_ANIM_02);
                        m_animState = 4;
                    }
                    for (auto guid : m_guardsGUID)
                        if (Creature* npc = sObjectAccessor->GetCreature(*me, guid.second))
                        {
                            npc->AI()->SetGUID(m_vashjirShipGUID, GO_SHIP_TO_VASHJIR_203466);
                            npc->AI()->DoAction(ACTION_START_WALK_01);
                        }
                }
                break;
            case 26515: // departure horde bridge.. now ship are the commander
                if (m_animState == 4)
                {
                    m_animState = 5;
                }
                break;
            case 25467:
                break;
            case 25446:
                break;
            case 25452: // teleport to map 0
            {
                if (m_animState == 5)
                {
                    if (Creature* npc = sObjectAccessor->GetCreature(*me, m_commanderGUID))
                        if (npc->IsDead())
                            npc->Respawn(true);
                    for (auto guid : m_guardsGUID)
                        if (Creature* npc = sObjectAccessor->GetCreature(*me, guid.second))
                            if (npc->IsDead())
                                npc->Respawn(true);
                }
                m_animState = 0;
                break;
            }
            }
        }

        void HandleUpdateAIHorde(uint32 eventId)
        {
            switch (eventId)
            {
            case EVENT_START_ANIM_01:
            {
                if (Creature* nazgrim = sObjectAccessor->GetCreature(*me, m_commanderGUID))
                {
                    m_animState = 3;
                    nazgrim->AI()->SetGUID(m_vashjirShipGUID, GO_SHIP_TO_VASHJIR_203466);
                    nazgrim->AI()->DoAction(ACTION_START_ANIM_01);
                }
                break;
            }   
            }

            switch (m_animState)
            {
            case 1:
            case 2:  // m_animState = 1 + 2 = talk started
                HordeAnimation_smalltalk(eventId);
                break;
            }
        }

        void HordeAnimation_smalltalk(uint32 eventId)
        {
            switch (eventId)
            {
            case EVENT_START_ANIM: // smalltalk between soldier
            {
                if (Creature* npc = GetStoredCreature(eVanGuardCA))
                    npc->AI()->Talk(1);

                m_events.ScheduleEvent(EVENT_TALK_PART_00, 8000);
                break;
            }
            case EVENT_TALK_PART_00:
            {
                if (Creature* npc = GetStoredCreature(eVanGuardCA))
                    npc->AI()->Talk(2);

                m_events.ScheduleEvent(EVENT_TALK_PART_01, 9000);
                break;
            }
            case EVENT_TALK_PART_01:
            {
                if (Creature* npc = GetStoredCreature(eVanGuardCB))
                    npc->AI()->Talk(3);

                m_events.ScheduleEvent(EVENT_TALK_PART_02, 6000);
                break;
            }
            case EVENT_TALK_PART_02:
            {
                if (Creature* npc = GetStoredCreature(eVanGuardCB))
                    npc->AI()->Talk(4);

                m_events.ScheduleEvent(EVENT_TALK_PART_03, 9000);
                break;
            }
            case EVENT_TALK_PART_03:
            {
                if (Creature* npc = GetStoredCreature(eVanGuardCB))
                    npc->AI()->Talk(5);

                m_events.ScheduleEvent(EVENT_TALK_PART_04, 6000);
                break;
            }
            case EVENT_TALK_PART_04:
            {
                if (Creature* npc = GetStoredCreature(eVanGuardCB))
                    npc->AI()->Talk(6);

                m_events.ScheduleEvent(EVENT_TALK_PART_05, 20000);
                break;
            }
            case EVENT_TALK_PART_05:
            {
                if (Creature* npc = GetStoredCreature(eVanGuardAA))
                    npc->AI()->Talk(7);

                m_events.ScheduleEvent(EVENT_TALK_PART_06, 6000);
                break;
            }
            case EVENT_TALK_PART_06:
            {
                if (Creature* npc = GetStoredCreature(eVanGuardAA))
                    npc->AI()->Talk(8);

                m_events.ScheduleEvent(EVENT_TALK_PART_07, 9000);
                break;
            }
            case EVENT_TALK_PART_07:
            {
                if (Creature* npc = GetStoredCreature(eVanGuardAB))
                    npc->AI()->Talk(17);

                m_events.ScheduleEvent(EVENT_TALK_PART_08, 20000);
                break;
            }
            case EVENT_TALK_PART_08:
            {
                if (Creature* npc = GetStoredCreature(eVanGuardBA))
                    npc->AI()->Talk(9);

                m_events.ScheduleEvent(EVENT_TALK_PART_09, 6000);
                break;
            }
            case EVENT_TALK_PART_09:
            {
                if (Creature* npc = GetStoredCreature(eVanGuardBA))
                    npc->AI()->Talk(10);

                m_events.ScheduleEvent(EVENT_TALK_PART_10, 6000);
                break;
            }
            case EVENT_TALK_PART_10:
            {
                if (Creature* npc = GetStoredCreature(eVanGuardBB))
                    npc->AI()->Talk(11);

                m_events.ScheduleEvent(EVENT_TALK_PART_11, 6000);
                break;
            }
            case EVENT_TALK_PART_11:
            {
                if (Creature* npc = GetStoredCreature(eVanGuardBB))
                    npc->AI()->Talk(12);

                m_events.ScheduleEvent(EVENT_TALK_PART_12, 8000);
                break;
            }
            case EVENT_TALK_PART_12:
            {
                if (Creature* npc = GetStoredCreature(eVanGuardBA))
                    npc->AI()->Talk(13);

                m_events.ScheduleEvent(EVENT_TALK_PART_13, 9000);
                break;
            }
            case EVENT_TALK_PART_13:
            {
                if (Creature* npc = GetStoredCreature(eVanGuardBA))
                    npc->AI()->Talk(14);

                m_events.ScheduleEvent(EVENT_TALK_PART_14, 7000);
                break;
            }
            case EVENT_TALK_PART_14:
            {
                if (Creature* npc = GetStoredCreature(eVanGuardBA))
                    npc->AI()->Talk(15);

                m_events.ScheduleEvent(EVENT_TALK_PART_15, 8000);
                break;
            }
            case EVENT_TALK_PART_15:
            {
                if (Creature* npc = GetStoredCreature(eVanGuardBB))
                    npc->AI()->Talk(16);

                m_events.ScheduleEvent(EVENT_TALK_PART_16, 8000);
                break;
            }
            case EVENT_TALK_PART_16:
            {
                if (Creature* npc = GetStoredCreature(eVanGuardBC))
                    npc->AI()->Talk(18);

                m_events.ScheduleEvent(EVENT_TALK_PART_17, 20000);
                break;
            }
            case EVENT_TALK_PART_17:
            {
                if (Creature* npc = GetStoredCreature(eVanGuardAA))
                    npc->AI()->Talk(19);

                m_events.ScheduleEvent(EVENT_TALK_PART_18, 6000);
                break;
            }

            case EVENT_TALK_PART_18:
            {
                if (Creature* npc = GetStoredCreature(eVanGuardAB))
                    npc->AI()->Talk(20);

                m_events.ScheduleEvent(EVENT_TALK_PART_19, 6000);
                break;
            }
            case EVENT_TALK_PART_19:
            {
                if (Creature* npc = GetStoredCreature(eVanGuardAA))
                    npc->AI()->Talk(21);

                m_events.ScheduleEvent(EVENT_TALK_PART_20, 11000);
                break;
            }
            case EVENT_TALK_PART_20:
            {
                if (Creature* npc = GetStoredCreature(eVanGuardAA))
                    npc->AI()->Talk(22);

                m_events.ScheduleEvent(EVENT_TALK_PART_21, 8000);
                break;
            }
            case EVENT_TALK_PART_21:
            {
                m_events.Reset();
                break;
            }
            }
        }

/*  Alliance */

        void TryStartAnimAlliance()
        {
            if (m_animState != 0)
                return;

            if (!PlayerWithActiveQuestIsNear())
                return;

            if (m_guardsGUID.size() < 8)
                return;

            if (!m_commanderGUID)
                return;

            switch (m_lastShipEventId)
            {
            case 25769:
                m_animState = 1; // we can start the anim on next ship event
                m_events.ScheduleEvent(EVENT_START_ANIM, 1000);
                break;
            default:
                return;
            }
        }

        void HandleDoActionAlliance(int32 param)
        {
            TryStartAnimAlliance();
            printf("Alliance Ship EventID: %u \n", param);
            switch (param) // alliance
            {
            case 25769:  
                printf("Abfahrt: Tritt mehrfach auf.. \n");
                if (m_animState == 11)
                {
                    m_animState = 12;
                    m_events.ScheduleEvent(EVENT_START_ANIM_03, 30000);
                }
                else
                    m_animState = 10;
                break;
                break;
            case 24015:  // we are 15 sec. arrived on brigge
                printf("Alliance Ship 15 sec after arrive bridge \n");
                break;
            case 24986:  // we are started from bridge 15 sec before
                printf("");
                break;
            case 24009:  // big see
                printf("");
                break;
            case 25075:  // big see
                printf("");
                break;
            case 24014:  // we can see the shipwreck, 25 sec before stop on wreck..
                printf("");
                break;
            case 22520:  // we are fighting vs tentakles, 35 sec before starting to position to teleport
                printf("");
                break;
            case 24036:  // this events never fires..
                printf("");
                break;
            }
        }

        void HandleUpdateAIAlliance(uint32 eventId)
        {
            switch (eventId)
            {
            case EVENT_START_ANIM_01:
            {
                printf("");
                break;
            }
            }

            switch (m_animState)
            {
            case 1:
            case 2:  // m_animState = 1 + 2 = talk started
                AllianceAnimation_smalltalk(eventId);
                break;
            }
        }

        void AllianceAnimation_smalltalk(uint32 eventId)
        {
            switch (eventId)
            {
            case EVENT_START_ANIM: // smalltalk between soldier
            {

                m_events.ScheduleEvent(EVENT_START_ANIM, 1000);
                break;
            }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_totally_generic_bunny_all_phase_32520AI(creature);
    }
};

// 43100  nazgrim exist twice... allways on bridge... new spawned when he enter the ship
class npc_legionnaire_nazgrim_43100 : public CreatureScript
{
public:
    npc_legionnaire_nazgrim_43100() : CreatureScript("npc_legionnaire_nazgrim_43100") { }

    struct npc_legionnaire_nazgrim_43100AI : public ScriptedAI
    {
        npc_legionnaire_nazgrim_43100AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_vashjirShipGUID;
        uint32   m_path;
        Position m_hordePosNazA, m_hordePosNazB, m_hordePosNazC; 

        void Initialize()
        {
            m_vashjirShipGUID = 0;
            m_path = 0;
            m_hordePosNazA = Position(1439.42f, -5009.48f, 11.64f);         // bridge: talk pos
            m_hordePosNazB = Position(1441.87f, -5025.65f, 12.20f, 4.825f); // ship: first pos
            m_hordePosNazC = Position(1450.60f, -5028.54f, 12.05f, 3.951f); // ship: home pos
        }

        void MovementInform(uint32 type, uint32 id) override 
        { 
            if (type == POINT_MOTION_TYPE)
                switch (id)
                {
                case 1024:
                    m_events.ScheduleEvent(EVENT_TALK_PART_00, 10);
                    break;
                case 1025:
                    m_events.ScheduleEvent(EVENT_START_WALK_02, 10);
                    break;
                case 1026:
                    m_events.ScheduleEvent(EVENT_START_WALK_03, 10);
                    break;
                }
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case GO_SHIP_TO_VASHJIR_203466:
            {
                m_vashjirShipGUID = guid;
                break;
            }
            }
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case ACTION_START_ANIM_01: // walk to talk-point, and start to talk..
                me->SetWalk(true);
                me->GetMotionMaster()->MovePoint(1024, m_hordePosNazA);
                break;
            case ACTION_START_ANIM_02: // walk to ship.. and to home..
                me->SetWalk(true);                
                me->GetMotionMaster()->MovePoint(1025, m_hordePosNazB, false);
                break;
            case ACTION_CREATE_NAZGRIM:
                // some neccassary init after spawn new passenger nazgrim on ship
                break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_TALK_PART_00:
                    Talk(1);
                    m_events.ScheduleEvent(EVENT_TALK_PART_01, 6000);
                    break;
                case EVENT_TALK_PART_01:
                    Talk(2);
                    m_events.ScheduleEvent(EVENT_TALK_PART_02, 8000);
                    break;
                case EVENT_TALK_PART_02:
                    Talk(3);
                    break;
                case EVENT_START_WALK_02: // walk to home
                    me->SetWalk(true);
                    me->GetMotionMaster()->MovePoint(1026, m_hordePosNazC, false);
                    break;
                case EVENT_START_WALK_03: // set facing to center, send to ship: create passenger nazgrim
                {
                    me->DespawnOrUnsummon(200);
                    if (GameObject* go = sObjectAccessor->GetGameObject(*me, m_vashjirShipGUID))
                    {
                        me->SetFacingTo(3.5f);
                        go->AI()->SetGUID(me->GetGUID(), me->GetEntry());
                    }
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
        return new npc_legionnaire_nazgrim_43100AI(creature);
    }
};

// 43090  vanguard's exist twice... allways on bridge... new spawned when enter the ship
class npc_hellscreams_vanguard_43090 : public CreatureScript
{
public:
    npc_hellscreams_vanguard_43090() : CreatureScript("npc_hellscreams_vanguard_43090") { }

    struct npc_hellscreams_vanguard_43090AI : public ScriptedAI
    {
        npc_hellscreams_vanguard_43090AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        Position m_hordeShipPosA, m_hordeShipPosB;
        uint64   m_vashjirShipGUID;
        uint32   m_guardIndex;
        std::map<uint32, Position>m_guardHomePos;

        void Initialize()
        {
            m_hordeShipPosA   = Position(1439.79f, -5015.64f, 12.12f, 4.825f);  // pos on bridge
            m_hordeShipPosB   = Position(1441.87f, -5025.65f, 12.20f, 4.825f);  // first pos ship
            m_guardHomePos.insert(std::pair<uint32, Position>(eVanGuardAA, Position(1451.11f, -5041.84f, 12.02f, 1.563f)));
            m_guardHomePos.insert(std::pair<uint32, Position>(eVanGuardAB, Position(1445.82f, -5043.93f, 12.03f, 1.563f)));
            m_guardHomePos.insert(std::pair<uint32, Position>(eVanGuardBA, Position(1440.38f, -5043.80f, 12.08f, 1.539f)));
            m_guardHomePos.insert(std::pair<uint32, Position>(eVanGuardBB, Position(1435.82f, -5045.21f, 12.13f, 1.586f)));
            m_guardHomePos.insert(std::pair<uint32, Position>(eVanGuardBC, Position(1429.85f, -5029.32f, 12.20f, 4.889f)));
            m_guardHomePos.insert(std::pair<uint32, Position>(eVanGuardCA, Position(1435.38f, -5028.59f, 12.11f, 5.172f)));
            m_vashjirShipGUID = 0;
            m_guardIndex = 0;
        }

        void Reset() override
        {
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == POINT_MOTION_TYPE)
                switch (id)
                {
                case 1024:
                    m_events.ScheduleEvent(EVENT_START_WALK_02, 10);
                    break;
                case 1025:
                    m_events.ScheduleEvent(EVENT_START_WALK_03, 10);
                    break;
                case 1026:
                    m_events.ScheduleEvent(EVENT_START_WALK_04, 10);
                    break;
                }
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case GO_SHIP_TO_VASHJIR_203466:
            {
                m_vashjirShipGUID = guid;
                break;
            }
            }
        }

        void SetData(uint32 id, uint32 value) override
        {
            return;

            switch (id)
            {
            case NPC_HELLSCREAMS_VANGUARD:
                m_guardIndex = value;
                break;
            }

        }

        uint32 GetData(uint32 id = 0) const override
        {
            switch (id)
            {
            case NPC_HELLSCREAMS_VANGUARD:
                return m_guardIndex;
            }
            return 0;
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case ACTION_START_WALK_01:
                m_events.ScheduleEvent(EVENT_START_WALK_01, urand(2000, 4000)); 
                break;
            case ACTION_CREATE_VANGUARD:
                // some neccassary init after spawn new passenger vangard on ship
                break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_WALK_01: // walk to bridge-center, ship entry
                    me->SetWalk(true);
                    me->GetMotionMaster()->MovePoint(1024, m_hordeShipPosA);
                    break;
                case EVENT_START_WALK_02: // walk to first pos on ship,
                    me->SetWalk(true);
                    me->GetMotionMaster()->MovePoint(1025, m_hordeShipPosB, false);
                    break;
                case EVENT_START_WALK_03:
                {
                    if (m_guardHomePos.find(me->GetDBTableGUIDLow()) == m_guardHomePos.end())
                        me->DespawnOrUnsummon(10);
                    else
                        me->GetMotionMaster()->MovePoint(1026, m_guardHomePos[me->GetDBTableGUIDLow()], false);
                    break;
                }
                case EVENT_START_WALK_04:
                {
                    me->DespawnOrUnsummon(200);
                    if (GameObject* go = sObjectAccessor->GetGameObject(*me, m_vashjirShipGUID))
                    {
                        Position pos = me->GetPosition();
                        if (pos.m_positionY>0)
                            me->SetFacingTo(5.1f);
                        else
                            me->SetFacingTo(1.5f);
                        me->SetTransportHomePosition(me->GetTransportPosition());
                        go->AI()->SetGUID(me->GetGUID(), me->GetDBTableGUIDLow());
                    }
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        float GetGlobalOrientation(float transportOrientation)
        {
            if (GameObject* go = sObjectAccessor->GetGameObject(*me, m_vashjirShipGUID))
                if (Transport* transport = go->ToTransport())
                {
                    float x, y, z, o;
                    me->GetPosition(x, y, z, o);
                    transport->CalculatePassengerPosition(x, y, z, &o);
                    return o;
                }
            return 0;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_hellscreams_vanguard_43090AI(creature);
    }
};

// 203466 horde
class go_ship_to_vashjir_203466 : public GameObjectScript
{
public:
    go_ship_to_vashjir_203466() : GameObjectScript("go_ship_to_vashjir_203466") {}

    struct go_ship_to_vashjir_203466AI : public GameObjectAI
    {
        go_ship_to_vashjir_203466AI(GameObject* go) : GameObjectAI(go) { }

        EventMap m_events;
        uint64   m_bunnyBridgeGUID;
        uint64   m_nazgrimShipGUID;
        std::map<uint32, uint64> m_vanGuardShipGUID;

        void InitializeShip()
        {
            m_nazgrimShipGUID = 0;
            m_vanGuardShipGUID.clear();
        }

        void Reset()
        {
            m_bunnyBridgeGUID = 0;
            InitializeShip();
        }

        void EventInform(uint32 eventId)
        {
            if (m_bunnyBridgeGUID)
                if (Creature* bunny = FindCreatureWorldwide(m_bunnyBridgeGUID))
                    bunny->AI()->DoAction(eventId);

            switch (eventId)
            {
            case 26605: // teleport to map 1
                break;
            case 25447:
            {
                // delete all guards from ship                
                std::list<uint64> pList;
                if (Transport* transport = go->ToTransport())
                {
                    transport->RemoveNpcPassenger(m_nazgrimShipGUID);
                    for (auto guid : m_vanGuardShipGUID)
                        transport->RemoveNpcPassenger(guid.second);
                }
                m_nazgrimShipGUID = 0;
                m_vanGuardShipGUID.clear();
                break;
            }
            case 25445: // arrive bridge
                break;
            case 26515: // departure from bridge..
                m_events.Reset();
                break;
            case 25467:
                break;
            case 25446:
                break;
            case 25452: // teleport to map 0
                break;
            case 25489:
                break;
            case 25448:
                break;
            case 25428:
                break;
            }
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case 32520: // horde bunny controller outside ship
                m_bunnyBridgeGUID = guid;
                break;
            case eVanGuardNaz:
            case NPC_LEGIONNAIRE_NAZGRIM:
                if (Transport* transport = go->ToTransport())
                    if (Creature* nazgrimOld = sObjectAccessor->GetCreature(*go, guid))
                    {
                        float x, y, z, o;
                        nazgrimOld->GetPosition(x, y, z, o);
                        transport->CalculatePassengerOffset(x, y, z, &o);
                        uint32 _mapId = transport->GetMoTransportMapId();
                        if (Creature* nazgrim = CreateCreatureAsPassenger(NPC_LEGIONNAIRE_NAZGRIM, _mapId, x, y, z, o))
                        {
                            m_nazgrimShipGUID = nazgrim->GetGUID();
                            nazgrim->AI()->SetGUID(go->GetGUID(), go->GetEntry());
                            nazgrim->AI()->DoAction(ACTION_CREATE_NAZGRIM);
                        }
                    }
                break;
            case eVanGuardAA:
            case eVanGuardAB:
            case eVanGuardBA:
            case eVanGuardBB:
            case eVanGuardBC:
            case eVanGuardCA:
            case eVanGuardCB:
            case eVanGuardDA:
            case NPC_HELLSCREAMS_VANGUARD:
                if (Transport* transport = go->ToTransport())
                    if (Creature* old = sObjectAccessor->GetCreature(*go, guid))
                    {
                        float x, y, z, o;
                        old->GetPosition(x, y, z, o);
                        transport->CalculatePassengerOffset(x, y, z, &o);
                        (y < 0.0f) ? o = 1.5f : o = 4.9f;
                        uint32 _mapId = transport->GetMoTransportMapId();
                        if (Creature* guard = CreateCreatureAsPassenger(NPC_HELLSCREAMS_VANGUARD, _mapId, x, y, z, o))
                        {
                            m_vanGuardShipGUID.insert(std::pair<uint32, uint64>(guard->GetDBTableGUIDLow(), guard->GetGUID()));
                            guard->AI()->SetGUID(go->GetGUID(), go->GetEntry());
                            guard->AI()->DoAction(ACTION_CREATE_VANGUARD);
                        }
                    }
                break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case 0:
                    break;
                }
            }
        }

        Creature* FindCreatureWorldwide(uint64 guid)
        {
            if (Creature* cr = HashMapHolder<Creature>::Find(guid))
                return cr;

            return nullptr;
        }

        bool IsPassengerPlayerBoarded()
        {
            if (Transport* transport = go->ToTransport())
            {
                std::set<WorldObject*> pList = transport->GetPassengers();
                if (!pList.empty())
                    return true;
            }
            return false;
        }

        GameObject* CreateGameObjectAsPassenger(uint32 entry, uint32 map, float x, float y, float z, float o)
        {
            if (Transport* transport = go->ToTransport())
                if (uint32 guid = sObjectMgr->GenerateLowGuid(HIGHGUID_GAMEOBJECT))
                {
                    GameObjectData& data = sObjectMgr->NewGOData(guid);
                    data.id = entry;
                    data.mapid = map;
                    data.phaseMask = 1;
                    data.spawnMask = 1;
                    data.posX = x;
                    data.posY = y;
                    data.posZ = z;
                    data.orientation = o;
                    GameObject* g = transport->CreateGOPassenger(guid, &data);
                    sObjectMgr->AddGameobjectToGrid(guid, &data);
                    return g;
                }
        }

        Creature* CreateCreatureAsPassenger(uint32 entry, uint32 map, float x, float y, float z, float o)
        {
            if (Transport* transport = go->ToTransport())
                if (uint32 guid = sObjectMgr->GenerateLowGuid(HIGHGUID_UNIT))
                {
                    CreatureData& data = sObjectMgr->NewOrExistCreatureData(guid);
                    data.id = entry;
                    data.mapid = map;
                    data.phaseMask = 1;
                    data.spawnMask = 1;
                    data.posX = x;
                    data.posY = y;
                    data.posZ = z;
                    data.orientation = o;
                    Creature* c = transport->CreateNPCPassenger(guid, &data);
                    sObjectMgr->AddCreatureToGrid(guid, &data);
                    return c;
                }
            return nullptr;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return new go_ship_to_vashjir_203466AI(go);
    }
};

/* End Quest: Call of Duty.. */






void AddSC_durotar()
{
    new player_zone_durotar();
    new npc_lazy_peon();
    new spell_voodoo();
    new npc_drowned_thunder_lizard_39464();
    new spell_kill_golden_stonefish_80962();
    new npc_shin_stonepillar_39380();
    new npc_the_wolf_39364();
    new spell_rumbling_hooves_73868();
    new npc_the_kodo_39365();
    new npc_commander_thorak_41621();
    new npc_totally_generic_bunny_all_phase_32520();
    new npc_legionnaire_nazgrim_43100();
    new npc_hellscreams_vanguard_43090();
    new go_ship_to_vashjir_203466();
}

