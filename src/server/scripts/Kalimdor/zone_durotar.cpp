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
    ACTION_CREATE_NAZGRIM = 1000,
    ACTION_CREATE_VANGUARD = 1001,
    
    GO_SHIP_TO_VASHJIR_197195 = 197195,
    GO_SHIP_TO_VASHJIR_203466 = 203466,

    NPC_HELLSCREAMS_VANGUARD = 43090,
    NPC_LEGIONNAIRE_NAZGRIM = 43100,

    SPELL_QUEST_GENERIC_ZONE_SPECIFIC_02 = 59074,
    SPELL_QUEST_ZONE_SPECIFIC_02 = 78644,

    QUEST_CALL_OF_DUTY_HORDE = 25924,
    QUEST_CALL_OF_DUTY_ALLIANCE = 14482,
};

enum eNpcVanGuard 
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

// 43091 bunny, as commander inside ship
class npc_totally_generic_bunny_phase_43091 : public CreatureScript
{
public:
    npc_totally_generic_bunny_phase_43091() : CreatureScript("npc_totally_generic_bunny_phase_43091") { }

    struct npc_totally_generic_bunny_phase_43091AI : public ScriptedAI
    {
        npc_totally_generic_bunny_phase_43091AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_hordeShipGUID;

        void Initialize()
        {
            m_hordeShipGUID = 0;
        }

        void Reset() override
        {
        }

        void SetData(uint32 id, uint32 value) 
        { 
            switch (id)
            {
            case 1: // data are ship's eventId 
                switch (value)
                {
                case 0:
                    break;
                }
                break;
            }
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case ACTION_START_ANIM_02:
            {
                // ship has started from bridge.. next animation starts now..
                break;
            }
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

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_totally_generic_bunny_phase_43091AI(creature);
    }
};

// 32520  bunny, as commander outside ship, check for player near and active quest...   then starting the animation on bridge...
class npc_totally_generic_bunny_all_phase_32520 : public CreatureScript
{
public:
    npc_totally_generic_bunny_all_phase_32520() : CreatureScript("npc_totally_generic_bunny_all_phase_32520") { }

    struct npc_totally_generic_bunny_all_phase_32520AI : public ScriptedAI
    {
        npc_totally_generic_bunny_all_phase_32520AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint32   m_areaId;
        uint64   m_vashjirShipGUID;
        bool     m_animCanBeStarted;
        uint32   m_lastShipEventId;
        uint32   m_animState;
        std::map<uint32, uint64> sList;

        void Initialize()
        {
            m_vashjirShipGUID = 0;
            m_areaId = 0;
            m_animCanBeStarted = false;
            m_lastShipEventId = 0;
            m_animState = 0;
        }

        void Reset() override
        {
            switch (me->GetAreaId())
            {
            case 4411:
            case 374:
                m_areaId = me->GetAreaId();
                break;
            }
        }

        void CreatureMoveInLineOfSight(Unit* who) override
        {
            TryStartAnim();            
        }

        uint32 GetData(uint32 id = 0) const override
        { 
            switch (id)
            {
            case ACTION_IS_PLAYER_NEAR:
                return m_animCanBeStarted | m_animState;
            case 1:
                return m_lastShipEventId;
            case 2:
                return m_animState;
            }
            return 0; 
        }

        void DoAction(int32 param) override
        {
            if (m_areaId == 374)
                printf("EventId: %u \n", param);

            if (param > 24000 && param < 27000)
                m_lastShipEventId = param;
            
            TryStartAnim();

            switch (param)
            {
            //Part: Horde ship eventIds
            case 25448: 
                break;
            case 25428:
                break;
            case 26605: // ship teleport to map 1
                if (m_animState == 1)
                    m_events.ScheduleEvent(EVENT_START_ANIM_01, 30000);
                else if (m_animState >= 5)
                    m_animState = 0;
                break;
            case 25447: // inside curve, before bridge                
                break;
            case 25445: // arrive bridge
                if (m_animState == 2)
                {
                    m_animState = 3;
                    if (Creature* nazgrim = GetStoredCreature(eVanGuardNaz))
                        nazgrim->AI()->DoAction(ACTION_START_ANIM_02);
                    std::list<Creature*> cList = me->FindNearestCreatures(NPC_HELLSCREAMS_VANGUARD, 75.0f);
                    for (auto orc : cList)
                    {
                        orc->AI()->SetGUID(m_vashjirShipGUID, GO_SHIP_TO_VASHJIR_203466);
                        orc->AI()->DoAction(ACTION_START_WALK_01);
                    }
                }
                break;
            case 26515: // departure horde bridge.. now bunny inside ship are the commander
                if (m_animState == 3)
                    m_animState = 4;
                break; 
            case 25467:
                break;
            case 25446:
                break;
            case 25452: // teleport to map 0
                if (m_animState == 4)
                    m_animState = 5;
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
                case EVENT_SET_ACTIVE_FALSE:
                    me->setActive(false);
                    break;
                case EVENT_START_ANIM_01:
                {
                    m_events.Reset();
                    m_animState = 2;
                    if (Creature* nazgrim = GetStoredCreature(eVanGuardNaz))
                    {
                        nazgrim->AI()->SetGUID(m_vashjirShipGUID, GO_SHIP_TO_VASHJIR_203466);
                        nazgrim->AI()->DoAction(ACTION_START_ANIM_01);
                    }
                    break;
                }
                }

                switch (m_areaId)
                {
                case 374:
                    switch (1)
                    {
                    case 1:
                        HordeAnimation_smalltalk(eventId);
                        break;
                    }
                    break;
                case 4411:
                    switch (0)
                    {
                    case 1:
                        AllianceAnimation_smalltalk(eventId);
                        break;
                    }
                    break;
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void FindAllMembersWorldwide()
        {
            TRINITY_READ_GUARD(HashMapHolder<GameObject>::LockType, *HashMapHolder<GameObject>::GetLock());
            HashMapHolder<GameObject>::MapType const& m = ObjectAccessor::GetGameObjects();
            for (HashMapHolder<GameObject>::MapType::const_iterator iter = m.begin(); iter != m.end(); ++iter)
                if (GameObject* ship = iter->second->ToGameObject())
                    if (ship->IsInWorld())
                        if ((m_areaId == 374 && ship->GetEntry() == GO_SHIP_TO_VASHJIR_203466) || (m_areaId == 4411 && ship->GetEntry() == GO_SHIP_TO_VASHJIR_197195))
                        {
                            m_vashjirShipGUID = ship->GetGUID();
                            ship->AI()->SetGUID(me->GetGUID(), me->GetEntry());
                        }
            std::list<Creature*> cList;
            cList = me->FindNearestCreatures(NPC_HELLSCREAMS_VANGUARD, 75.0f);
            for (auto npc : cList)
                sList[npc->GetDBTableGUIDLow()] = npc->GetGUID();
            if (Creature* nazgrim = me->FindNearestCreature(NPC_LEGIONNAIRE_NAZGRIM, 80.0f))
                sList[nazgrim->GetDBTableGUIDLow()] = nazgrim->GetGUID();
        }

        uint32 IsPlayerOnBridgeWithQuestActive() const
        {
            std::list<Player*> pList = me->FindNearestPlayers(75.0f);
            for (auto player : pList)
                if (player->GetQuestStatus(QUEST_CALL_OF_DUTY_HORDE) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_CALL_OF_DUTY_ALLIANCE) == QUEST_STATUS_INCOMPLETE)
                    return 1;

            return 0;
        }

        void TryStartAnim()
        {
            m_animCanBeStarted = false;

            if (!m_vashjirShipGUID)
                FindAllMembersWorldwide();
            
            if (CanAnimationBeStarted() == false)
                return;

            m_animState = 1;
            m_events.ScheduleEvent(EVENT_START_ANIM, 1000);
        }

        Creature* GetStoredCreature(uint32 dbGuid)
        {
            if (Creature* npc = sObjectAccessor->GetCreature(*me, sList[dbGuid]))
                return npc;

            return nullptr;
        }

        uint32 CanAnimationBeStarted()
        {
            m_animCanBeStarted = false;

            if (m_animState != 0)
                return false;

            bool playerOnBridge = IsPlayerOnBridgeWithQuestActive();

            Creature* nazgrim = me->FindNearestCreature(NPC_LEGIONNAIRE_NAZGRIM, 75.0f);

            std::list<Creature*> cList = me->FindNearestCreatures(NPC_HELLSCREAMS_VANGUARD, 75.0f);
            
            if (!playerOnBridge)
                return false;

            if (!nazgrim)
                return false;

            if (cList.size() != 8)
                return false;
            
            m_animCanBeStarted = true;

            switch (m_lastShipEventId)
            {
            case 25489:
            case 25448:
            case 25428:                
                return true;
                break;
            }
            return false;
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
                    me->DespawnOrUnsummon(200);
                    if (GameObject* go = sObjectAccessor->GetGameObject(*me, m_vashjirShipGUID))
                    {
                        me->SetFacingTo(3.5f);
                        go->AI()->SetGUID(me->GetGUID(), me->GetEntry());
                        go->AI()->DoAction(ACTION_CREATE_NAZGRIM);
                    }
                    break;
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
        Position m_guardHomePos[6];

        void Initialize()
        {
            m_hordeShipPosA   = Position(1439.79f, -5015.64f, 12.12f, 4.825f);  // pos on bridge
            m_hordeShipPosB   = Position(1441.87f, -5025.65f, 12.20f, 4.825f);  // first pos ship
            m_guardHomePos[0] = Position(1451.11f, -5041.84f, 12.02f, 1.563f);  // homepos
            m_guardHomePos[1] = Position(1445.82f, -5043.93f, 12.03f, 1.563f);
            m_guardHomePos[2] = Position(1440.38f, -5043.80f, 12.08f, 1.539f);
            m_guardHomePos[3] = Position(1435.82f, -5045.21f, 12.13f, 1.586f);
            m_guardHomePos[4] = Position(1429.85f, -5029.32f, 12.20f, 4.889f);
            m_guardHomePos[5] = Position(1435.38f, -5028.59f, 12.11f, 5.172f);
            m_vashjirShipGUID = 0;
            m_guardIndex = 0;
        }

        void Reset() override
        {
            switch (me->GetDBTableGUIDLow())
            {            
            case eVanGuardAA:
                m_guardIndex = 0;
                break;
            case eVanGuardAB:
                m_guardIndex = 1;
                break;
            case eVanGuardBA:
                m_guardIndex = 2;
                break;
            case eVanGuardBB:
                m_guardIndex = 3;
                break;
            case eVanGuardBC:
                m_guardIndex = 4;
                break;
            case eVanGuardCA:
                m_guardIndex = 5;
                break;
            case eVanGuardCB:
                m_guardIndex = 6;
                break;
            case eVanGuardDA:
                m_guardIndex = 7;
                break;
            }
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
                    if (m_guardIndex < 6)
                        me->GetMotionMaster()->MovePoint(1026, m_guardHomePos[m_guardIndex], false);
                    else
                        me->DespawnOrUnsummon(10);
                    break;
                case EVENT_START_WALK_04:
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

/* End Quest: Call of Duty.. */

void AddSC_durotar()
{
    new npc_lazy_peon();
    new spell_voodoo();
    new npc_drowned_thunder_lizard_39464();
    new spell_kill_golden_stonefish_80962();
    new npc_shin_stonepillar_39380();
    new npc_the_wolf_39364();
    new spell_rumbling_hooves_73868();
    new npc_the_kodo_39365();
    new npc_commander_thorak_41621();
    new npc_totally_generic_bunny_phase_43091();
    new npc_totally_generic_bunny_all_phase_32520();
    new npc_legionnaire_nazgrim_43100();
    new npc_hellscreams_vanguard_43090();

}

