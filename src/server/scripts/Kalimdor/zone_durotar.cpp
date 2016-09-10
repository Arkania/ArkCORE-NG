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
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "Player.h"

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

}

