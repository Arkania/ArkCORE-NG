/*
 *
* Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
 *
* Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 *
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
SDName: duskhaven
SD%Complete: 0
SDComment: Quest support: 0
SDCategory: Gilneas
EndScriptData */

/* ContentData */

#include "script_helper.h"
#include "CreatureTextMgr.h"
#include "PassiveAI.h"
#include "Player.h"
#include "MoveSplineInit.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "ScriptedFollowerAI.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Vehicle.h"
#include "zone_gilneas.h"

// Phase 1

// 36332
class npc_king_genn_greymane_36332 : public CreatureScript
{
public:
    npc_king_genn_greymane_36332() : CreatureScript("npc_king_genn_greymane_36332") { }

    enum e14375
    {
        QUEST_LAST_CHANCE_AT_HUMANITY = 14375,
        SPELL_PHASE_QUEST_ZONE_SPECIFIC_06 = 68481,
        SPELL_FADE_BACK = 94053,
        SPELL_LAST_STAND_COMPLETE = 72799,
        NPC_LORD_GODFREY_36330 = 36330,
        NPC_LORD_GODFREY_36170 = 36170,
        NPC_KRENNAN_ARANAS_36331 = 36331,
        NPC_KING_GENN_GREYMANE_36332 = 36332,
    };

    bool OnQuestReward(Player* player, Creature* creature, const Quest *_Quest, uint32) override
    {
        if (_Quest->GetQuestId() == QUEST_LAST_CHANCE_AT_HUMANITY)
        {
            player->CastSpell(player, SPELL_PHASE_QUEST_ZONE_SPECIFIC_06, true);
            player->SetUInt32Value(UNIT_FIELD_FLAGS_2, 2048);
            player->RemoveAura(42716);
            player->RemoveAura(50220);
            player->RemoveAura(58284);
            player->RemoveAura(68630);
            return true;
        }
        return false;
    }
};

// 36331
class npc_krennan_aranas_36331 : public CreatureScript
{
public:
    npc_krennan_aranas_36331() : CreatureScript("npc_krennan_aranas_36331") { }

    enum eNpc
    {
        QUEST_LAST_CHANCE_AT_HUMANITY = 14375,
        QUEST_LAST_STAND = 14222,
        NPC_KING_GREYMANE = 36332,
        NPC_LORD_GODFREY = 36330,
        SPELL_CATACLYSM_1 = 68953,
        SPELL_CATACLYSM_2 = 80134,
        SPELL_CATACLYSM_3 = 80133,
        SPELL_LAST_STAND_COMPLETE_2 = 72799,
        EVENT_CHECK_ARRIVEL_PLAYER = 101,
        EVENT_TALK_0,
        EVENT_TALK_1,
        EVENT_TALK_2,
        EVENT_TALK_3,
        EVENT_TALK_4,
        EVENT_RESTART,
    };

    struct npc_krennan_aranas_36331AI : public ScriptedAI
    {
        npc_krennan_aranas_36331AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap  m_events;
        bool      m_videoStarted;
        uint64    m_playerGUID;
        uint64    m_kingGUID;
        uint64    m_godfreyGUID;

        void Reset() override
        {
            m_videoStarted = false;
            m_playerGUID = 0;
            m_kingGUID = 0;
            m_godfreyGUID = 0;
            m_events.Reset();
            m_events.ScheduleEvent(EVENT_CHECK_ARRIVEL_PLAYER, 1000);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            if (CheckPlayerIsInvalid())
            {
                Reset();
                return;
            }

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_ARRIVEL_PLAYER:
                    {
                        if (Player* player = me->FindNearestPlayer(10.0f))
                            if (player->GetQuestStatus(QUEST_LAST_STAND) == QUEST_STATUS_REWARDED && player->GetQuestStatus(QUEST_LAST_CHANCE_AT_HUMANITY) == QUEST_STATUS_NONE)
                                if (!m_videoStarted)
                                {
                                    player->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_DISABLE_TURN);
                                    m_playerGUID = player->GetGUID();
                                    m_videoStarted = true;
                                    if (!m_kingGUID)
                                        if (Creature* king = me->FindNearestCreature(NPC_KING_GREYMANE, 25.0f))
                                            m_kingGUID = king->GetGUID();
                                    if (!m_godfreyGUID)
                                        if (Creature* lord = me->FindNearestCreature(NPC_LORD_GODFREY, 25.0f))
                                            m_godfreyGUID = lord->GetGUID();

                                    m_events.ScheduleEvent(EVENT_TALK_0, 4000);
                                    return;
                                }

                        m_videoStarted = false;

                        m_events.ScheduleEvent(EVENT_CHECK_ARRIVEL_PLAYER, 1000);
                        break;
                    }
                    case EVENT_TALK_0:
                    {
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                            Talk(0, player);
                        m_events.ScheduleEvent(EVENT_TALK_1, 14000);
                        break;
                    }
                    case EVENT_TALK_1:
                    {
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                            if (Creature* lord = sObjectAccessor->GetCreature(*me, m_godfreyGUID))
                            {
                                player->CastSpell(player, SPELL_CATACLYSM_1);
                                lord->AI()->Talk(0, player);
                            }
                        m_events.ScheduleEvent(EVENT_TALK_2, 8000);
                        break;
                    }
                    case EVENT_TALK_2:
                    {
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                            if (Creature* king = sObjectAccessor->GetCreature(*me, m_kingGUID))
                            {
                                player->CastSpell(player, SPELL_CATACLYSM_2);
                                king->AI()->Talk(0, player);
                            }
                        m_events.ScheduleEvent(EVENT_TALK_3, 9000);
                        break;
                    }
                    case EVENT_TALK_3:
                    {
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                            if (Creature* king = sObjectAccessor->GetCreature(*me, m_kingGUID))
                            {
                                player->CastSpell(player, SPELL_CATACLYSM_3);
                                king->AI()->Talk(1, player);
                            }
                        m_events.ScheduleEvent(EVENT_TALK_4, 8000);
                        break;
                    }
                    case EVENT_TALK_4:
                    {
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                            player->CastSpell(player, SPELL_LAST_STAND_COMPLETE_2);

                        break;
                    }
                }
            }
        }

        bool CheckPlayerIsInvalid()
        {
            if (!m_playerGUID)
                return false;

            if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                if (player->IsAlive() && player->IsInWorld())
                    if (player->GetDistance2d(me) < 10.0f)
                        return false;
            return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_krennan_aranas_36331AI(creature);
    }
};

// Phase 4096

// 34571
class npc_gwen_armstead_34571 : public CreatureScript
{
public:
    npc_gwen_armstead_34571() : CreatureScript("npc_gwen_armstead_34571") {}

    enum eNpc
    {
        QUEST_KILL_OR_BE_KILLED = 14336,
        SPELL_PHASE_QUEST_ZONE_SPECIFIC_06 = 68481,
        SPELL_PHASE_QUEST_ZONE_SPECIFIC_07 = 68482,
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_KILL_OR_BE_KILLED)
        {
            player->RemoveAura(SPELL_PHASE_QUEST_ZONE_SPECIFIC_06);
            player->CastSpell(player, SPELL_PHASE_QUEST_ZONE_SPECIFIC_07);
        }
        return true;
    }
};

// 196394  
class go_mandragore_196394 : public GameObjectScript
{
public:
    go_mandragore_196394() : GameObjectScript("go_mandragore_196394") {}

    bool OnQuestReward(Player* player, GameObject *, Quest const* _Quest, uint32) override
    {
        if (_Quest->GetQuestId() == 14320)
        {
            player->SendCinematicStart(168);
            WorldPacket data(SMSG_PLAY_SOUND, 4);
            data << uint32(23676);
            player->GetSession()->SendPacket(&data);
        }
        return true;
    }
};

// Phase 8192

// 36231  // Quest - You Can't Take 'Em Alone - 14348
class npc_horrid_abomination_36231 : public CreatureScript
{
public:
    npc_horrid_abomination_36231() : CreatureScript("npc_horrid_abomination_36231") { }

    enum eHorrid
    {
        QUEST_YOU_CANT_TAKE_EM_ALONE = 14348,
        QUEST_14348_KILL_CREDIT = 36233,
        SPELL_BARREL_KEG = 69094,
        SPELL_BARREL_KEG_PLACED = 68555,
        SPELL_ABOMINATION_KILL_ME = 68558,
        SPELL_HORRID_ABOMINATION_EXPLOSION = 68560,
        SPELL_RANDOM_POINT_POISON = 42266,
        SPELL_RANDOM_POINT_BONE = 42267,
        SPELL_RANDOM_POINT_BONE_2 = 42274,
        SPELL_CORPSE_EXPLOSION = 43999,
        SAY_BARREL = 0,
        EVENT_KEG_PLACED = 101,
        EVENT_KEG_CREDIT,
        EVENT_EXPLOSION,
        EVENT_FINISH,
    };

    struct npc_horrid_abomination_36231AI : public ScriptedAI
    {
        npc_horrid_abomination_36231AI(Creature* creature) : ScriptedAI(creature) {}

        bool m_creditGiven;

        void Reset() override
        {
            me->ClearUnitState(UNIT_STATE_ROOT | UNIT_STATE_STUNNED);
            m_creditGiven = false;
        }

        void SpellHit(Unit* caster, const SpellInfo* spell) override
        {
            if (Player* player = caster->ToPlayer())
            {
                if (spell->Id == SPELL_BARREL_KEG_PLACED)
                {
                    Talk(SAY_BARREL);
                    me->AddUnitState(UNIT_STATE_ROOT | UNIT_STATE_STUNNED);
                }
                if (!m_creditGiven && player->GetQuestStatus(QUEST_YOU_CANT_TAKE_EM_ALONE) == QUEST_STATUS_INCOMPLETE)
                {
                        player->KilledMonsterCredit(QUEST_14348_KILL_CREDIT);
                        m_creditGiven = true;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_horrid_abomination_36231AI(creature);
    }
};

// 69094
class spell_cast_keg_69094 : public SpellScriptLoader
{
public:
    spell_cast_keg_69094() : SpellScriptLoader("spell_cast_keg_69094") { }

    enum eNpc
    {
        NPC_HORRID_ABOMINATION = 36231,
    };

    class spell_cast_keg_69094_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_cast_keg_69094_SpellScript);

        void CheckTarget(WorldObject*& target)
        {
            if (target->GetEntry() != NPC_HORRID_ABOMINATION)
                target = target->FindNearestCreature(NPC_HORRID_ABOMINATION, 25.0f);           
        }

        void Register() override
        {
            OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_cast_keg_69094_SpellScript::CheckTarget, EFFECT_0, TARGET_UNIT_TARGET_ANY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_cast_keg_69094_SpellScript();
    }
};

// 36287  // Quest save the children 14368
class npc_cynthia_36267 : public CreatureScript
{
public:
    npc_cynthia_36267() : CreatureScript("npc_cynthia_36267") {}

    enum eNpc
    {
        QUEST_SAVE_THE_CHILDREN = 14368,
        NPC_CYNTIA_CREDIT = 36287,
    };

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (player->GetQuestStatus(QUEST_SAVE_THE_CHILDREN) == QUEST_STATUS_INCOMPLETE)
        {
            sCreatureTextMgr->SendChat(creature, 0, NULL, CHAT_MSG_ADDON, LANG_ADDON, TEXT_RANGE_NORMAL, 0, TEAM_OTHER, false, player);
            creature->AI()->Talk(1);
            player->KilledMonsterCredit(NPC_CYNTIA_CREDIT);
            return true;
        }
        return false;
    }
};

// 36288
class npc_james_36268 : public CreatureScript
{
public:
    npc_james_36268() : CreatureScript("npc_james_36268") {}

    enum eNpc
    {
        QUEST_SAVE_THE_CHILDREN = 14368,
        NPC_JAMES_CREDIT = 36288,
    };

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (player->GetQuestStatus(QUEST_SAVE_THE_CHILDREN) == QUEST_STATUS_INCOMPLETE)
        {
            sCreatureTextMgr->SendChat(creature, 0, NULL, CHAT_MSG_ADDON, LANG_ADDON, TEXT_RANGE_NORMAL, 0, TEAM_OTHER, false, player);
            creature->AI()->Talk(1);
            player->KilledMonsterCredit(NPC_JAMES_CREDIT);
            return true;
        }
        return false;
    }
};

// 36289
class npc_ashley_36269 : public CreatureScript
{
public:
    npc_ashley_36269() : CreatureScript("npc_ashley_36269") {}

    enum eNpc
    {
        QUEST_SAVE_THE_CHILDREN = 14368,
        NPC_ASHLEY_CREDIT = 36289,
    };

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (player->GetQuestStatus(QUEST_SAVE_THE_CHILDREN) == QUEST_STATUS_INCOMPLETE)
        {
            sCreatureTextMgr->SendChat(creature, 0, NULL, CHAT_MSG_ADDON, LANG_ADDON, TEXT_RANGE_NORMAL, 0, TEAM_OTHER, false, player);
            creature->AI()->Talk(1);
            player->KilledMonsterCredit(NPC_ASHLEY_CREDIT);
            return true;
        }
        return false;
    }
};

// 36283 quest 14382 Two by Sea (enter the ship)
class npc_forsaken_catapult_36283 : public CreatureScript
{
public:
    npc_forsaken_catapult_36283() : CreatureScript("npc_forsaken_catapult_36283") { }

    enum eCatapult
    {
        NPC_FORSAKEN_MACHINIST = 36292,
        NPC_GENERIC_TRIGGER_LAB_AOI = 36286, // target on land
        NPC_GENERIC_TRIGGER_LAB_MP = 35374, // target on ship
        PASSENGER_GUID = 99998,
        PLAYER_GUID = 99999,
        SPELL_FIERY_BOULDER = 68591, 
        SPELL_LAUNCH1 = 68659,
        SPELL_LAUNCH2 = 66251,
        SPELL_LAUNCH3 = 66227,
        SPELL_LAUNCH4 = 96185,
        EVENT_CHECK_PLAYER = 101,
        EVENT_CAST_BOULDER,
        EVENT_CAST_PLAYER,
        EVENT_MASTER_RESET,
    };

    struct npc_forsaken_catapult_36283AI : public VehicleAI
    {
        npc_forsaken_catapult_36283AI(Creature* creature) : VehicleAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID; // guid only set if mounted
        uint64   m_forsakenGUID; // guid only set if mounted
        uint64   m_targetGUID;

        void Reset() override
        {
            m_events.Reset();
            m_playerGUID = 0;
            m_forsakenGUID = 0;
            m_targetGUID = 0;
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_NOT_SELECTABLE);
            me->SetReactState(REACT_PASSIVE);
            me->setFaction(1735);
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override
        { 
            if (apply)
            {
                if (Player* player = passenger->ToPlayer())
                {
                    m_playerGUID = player->GetGUID();
                }
                else if (Creature* npc = passenger->ToCreature())
                {
                    m_forsakenGUID = npc->GetGUID();
                    npc->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_NOT_SELECTABLE);
                    m_events.ScheduleEvent(EVENT_CAST_BOULDER, 100);
                    m_events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
                    me->setFaction(1735);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                }
            }
            else
            {
                if (Player* player = passenger->ToPlayer())
                {
                    m_events.ScheduleEvent(EVENT_CAST_PLAYER, 1000);
                }
                else if (Creature* npc = passenger->ToCreature())
                {
                    m_forsakenGUID = 0;
                    npc->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_NOT_SELECTABLE);
                    m_events.CancelEvent(EVENT_CAST_BOULDER);
                    m_events.CancelEvent(EVENT_CHECK_PLAYER);
                    m_events.ScheduleEvent(EVENT_MASTER_RESET, 180000);
                    me->setFaction(35);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                }
            }
        }

        void EnterEvadeMode() {}

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case NPC_GENERIC_TRIGGER_LAB_MP:
            {
                m_targetGUID = guid;
                me->GetVehicleKit()->RemoveAllPassengers();
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
                case EVENT_CHECK_PLAYER:
                {
                    if (Creature* target = sObjectAccessor->GetCreature(*me, m_forsakenGUID))
                        if (Player* player = me->FindNearestPlayer(7.0f))
                            {
                                target->ExitVehicle();
                                break;
                            }
                    m_events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
                    break;
                }
                case EVENT_CAST_BOULDER:
                {
                    me->CastSpell(me, SPELL_FIERY_BOULDER, true);
                    m_events.ScheduleEvent(EVENT_CAST_BOULDER, urand(10000, 15000));
                    break;
                }
                case EVENT_MASTER_RESET:
                {
                    if (m_forsakenGUID || m_playerGUID)
                        m_events.ScheduleEvent(EVENT_MASTER_RESET, 180000);
                    else
                    {
                        if (Creature* npc = me->SummonCreature(NPC_FORSAKEN_MACHINIST, me->GetPosition()))
                            npc->EnterVehicle(me, 0);

                        Reset();
                    }
                    break;
                }
                case EVENT_CAST_PLAYER:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        if (Creature* t = sObjectAccessor->GetCreature(*me, m_targetGUID))
                            player->NearTeleportTo(t->GetPositionX(), t->GetPositionY(), t->GetPositionZ(), player->GetOrientation());

                    m_playerGUID = 0;
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_forsaken_catapult_36283AI(creature);
    }
};

// 68659
class spell_launch_68659 : public SpellScriptLoader
{
public:
    spell_launch_68659() : SpellScriptLoader("spell_launch_68659") { }

    enum eNpc
    {
        // TRAJ  short from trajectories = Flugbahnen, Flugkurven, Bewegungsbahnen 
        NPC_FORSAKEN_CATAPULT = 36283,
        NPC_FORSAKEN_MACHINIST = 36292,
        NPC_GENERIC_TRIGGER_LAB_AOI = 36286, // target on land
        NPC_GENERIC_TRIGGER_LAB_MP = 35374, // target on ship
        PASSENGER_GUID = 99998,
        PLAYER_GUID = 99999,
    };

    class IsNotEntry
    {
    public:
        explicit IsNotEntry(uint32 entry) : _entry(entry) { }

        bool operator()(WorldObject* obj) const
        {
            if (Creature* target = obj->ToCreature())
                return target->GetEntry() != _entry;

            return true;
        }

    private:
        uint32 _entry;
    };

    class spell_launch_68659_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_launch_68659_SpellScript);

        uint64 m_playerGUID = 0;
        Position pos = Position();

        void HandleBeforeCast()
        {
            m_playerGUID = 0;
            if (Creature* catapult = GetCaster()->ToCreature())
                if (Vehicle* vehicle = catapult->GetVehicleKit())
                    if (Unit* unit = vehicle->GetPassenger(0))
                        if (Player* player = unit->ToPlayer())
                        {
                            m_playerGUID = player->GetGUID();
                            player->EnterVehicle(GetCaster(), 1);
                        }
        }
       
        void CheckTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if(IsNotEntry(NPC_GENERIC_TRIGGER_LAB_MP));
            if (targets.empty())
                return;
            WorldObject* target = nullptr;
            float target_orientation = 6.28f;
            float ori = GetCaster()->GetOrientation();
            for (std::list<WorldObject*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                float angle = GetCaster()->GetAngle((*itr));
                float diff = abs(ori - angle);
                if (diff < target_orientation)
                {
                    target_orientation = diff;
                    target = (*itr);
                    pos = target->GetPosition();
                }
            }
            targets.clear();
            targets.push_back(target);
            GetCaster()->GetAI()->SetGUID(target->GetGUID(), target->GetEntry());            
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {

        }

        void Register() override
        {
           // BeforeCast += SpellCastFn(spell_launch_68659_SpellScript::HandleBeforeCast);
            OnEffectHit += SpellEffectFn(spell_launch_68659_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_launch_68659_SpellScript::CheckTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_launch_68659_SpellScript();
    }
};

// 68591
class spell_fire_boulder_68591 : public SpellScriptLoader
{
public:
    spell_fire_boulder_68591() : SpellScriptLoader("spell_fire_boulder_68591") { }

    enum eNpc
    {
        // TRAJ  short from trajectories = Flugbahnen, Flugkurven, Bewegungsbahnen 
        NPC_FORSAKEN_CATAPULT = 36283,
        NPC_FORSAKEN_MACHINIST = 36292,
        NPC_GENERIC_TRIGGER_LAB_AOI = 36286, // target on land
        NPC_GENERIC_TRIGGER_LAB_MP = 35374, // target on ship
    };

    class IsNotEntryButPlayer
    {
    public:
        explicit IsNotEntryButPlayer(Unit const* caster, uint32 entry) : _caster(caster), _entry(entry) { }

        bool operator()(WorldObject* obj) const
        {
            if (_caster->GetExactDist2d(obj) < 5.0f || _caster->GetExactDist2d(obj) > 80.0f)
                return true;
            if (Player* player = obj->ToPlayer())
                return player->IsMounted();
            else if (Creature* target = obj->ToCreature())
                return target->GetEntry() != _entry;

            return true;
        }

    private:
        const Unit* _caster;
        uint32 _entry;
    };

    class spell_fire_boulder_68591_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_fire_boulder_68591_SpellScript);

        void CheckTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if(IsNotEntryButPlayer(GetCaster(), NPC_GENERIC_TRIGGER_LAB_AOI));
            targets.remove_if(ReduceToOneRandomTarget(targets));
            if (!targets.size())
                this->FinishCast(SPELL_CAST_OK);
            else
            {
                std::list<WorldObject*>::iterator itr = targets.begin();
                GetCaster()->SetFacingToObject(*itr);
            }
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_fire_boulder_68591_SpellScript::CheckTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_fire_boulder_68591_SpellScript();
    }
};

// 36409
class npc_mastiff_36409 : public CreatureScript
{
public:
    npc_mastiff_36409() : CreatureScript("npc_mastiff_36409") { }

    enum eNPC
    {
        QUEST_LEADER_OF_THE_PACK = 14386,
        NPC_DARK_RANGER_THYALA = 36312,
        NPC_MASTIFF = 36405,
        NPC_TRIGGER = 36198,
        PLAYER_GUID = 99999,
        EVENT_CHECK_ATTACK = 101,
        EVENT_SEND_MORE_MASTIFF,
    };

    struct npc_mastiff_36409AI : public ScriptedAI
    {
        npc_mastiff_36409AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_thyalaGUID;
        uint64   m_player_GUID;
        uint32   m_mastiff_counter;

        void Initialize()
        {
            m_events.Reset();
        }

        void Reset() override
        {
            m_thyalaGUID = 0;
            m_player_GUID = 0;
            m_mastiff_counter = 0;
            m_events.ScheduleEvent(EVENT_CHECK_ATTACK, 500);
            m_events.ScheduleEvent(EVENT_SEND_MORE_MASTIFF, 250);
        }

        void IsSummonedBy(Unit* summoner) override 
        { 
            if (Player* player = summoner->ToPlayer())
                m_player_GUID = player->GetGUID();
            if (Creature* thyala = me->FindNearestCreature(NPC_DARK_RANGER_THYALA, 100.0f))
            {
                m_thyalaGUID = thyala->GetGUID();
                me->SetReactState(REACT_PASSIVE);
                me->GetMotionMaster()->MoveChase(thyala, 3.0f, 0.0f);
            }
        }

        void DamageTaken(Unit* attacker, uint32& damage) override 
        { 
            damage = 0;
        }

        void JustSummoned(Creature* summon) override 
        { 
            m_mastiff_counter += 1;
            summon->GetAI()->SetGUID(m_player_GUID, PLAYER_GUID);
            summon->GetAI()->SetGUID(m_thyalaGUID, NPC_DARK_RANGER_THYALA);
        }

        void SummonedCreatureDies(Creature* summon, Unit* killer) override 
        { 
            m_mastiff_counter -= 1;
        }

        void SummonedCreatureDespawn(Creature* summon) 
        { 
            m_mastiff_counter -= 1;
        }

        void EnterEvadeMode() override { }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_ATTACK:
                    {
                        if (Creature* thyala = sObjectAccessor->GetCreature(*me, m_thyalaGUID))
                        {
                            if (!thyala->IsAlive() || !thyala->IsInWorld())
                            {
                                if (Player* player = sObjectAccessor->GetPlayer(*me, m_player_GUID))
                                    player->KilledMonsterCredit(NPC_DARK_RANGER_THYALA);

                                me->DespawnOrUnsummon(1000);
                            }

                            if (me->GetDistance2d(thyala) < 20.0f)
                            {
                                me->SetWalk(false);
                                me->GetMotionMaster()->MoveIdle();
                            }
                        }
                        m_events.ScheduleEvent(EVENT_CHECK_ATTACK, 1000);
                        break;
                    }
                    case EVENT_SEND_MORE_MASTIFF:
                    {
                        if (Creature* thyala = sObjectAccessor->GetCreature(*me, m_thyalaGUID))
                            if (m_mastiff_counter < 50)
                            {
                                std::list<Creature*>trigger = me->FindNearestCreatures(NPC_TRIGGER, 100.0f);
                                for (std::list<Creature*>::const_iterator itr = trigger.begin(); itr != trigger.end(); ++itr)
                                    me->SummonCreature(NPC_MASTIFF, (*itr)->GetNearPosition(5.0f, frand(0.0f, 6.28f)), TEMPSUMMON_TIMED_DESPAWN, urand(30000, 60000));
                            }

                        m_events.ScheduleEvent(EVENT_SEND_MORE_MASTIFF, 250);
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
        return new npc_mastiff_36409AI(creature);
    }
};

// 36405
class npc_mastiff_36405 : public CreatureScript
{
public:
    npc_mastiff_36405() : CreatureScript("npc_mastiff_36405") { }

    enum eNPC
    {
        QUEST_LEADER_OF_THE_PACK = 14386,
        NPC_DARK_RANGER_THYALA = 36312,
        NPC_MASTIFF = 36405,
        NPC_TRIGGER = 36198,
        PLAYER_GUID = 99999,
        EVENT_CHECK_ATTACK = 101,
    };

    struct npc_mastiff_36405AI : public ScriptedAI
    {
        npc_mastiff_36405AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_thyalaGUID;
        uint64   m_player_GUID;

        void Initialize()
        {
            m_events.Reset();
        }

        void Reset() override
        {
            me->SetWalk(true);
            me->SetSpeed(MOVE_RUN, true);
            me->SetReactState(REACT_AGGRESSIVE);
            m_thyalaGUID = 0;
            m_player_GUID = 0;
            m_events.RescheduleEvent(EVENT_CHECK_ATTACK, 1000);
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
                case PLAYER_GUID:
                {
                    m_player_GUID = guid;
                    break;
                }
                case NPC_DARK_RANGER_THYALA:
                {
                    m_thyalaGUID = guid;
                    break;
                }
            }
        }

        void EnterEvadeMode() override 
        { 
            StartAttackThyala();
            m_events.RescheduleEvent(EVENT_CHECK_ATTACK, 1000);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_ATTACK:
                    {
                        StartAttackThyala();
                        m_events.ScheduleEvent(EVENT_CHECK_ATTACK, 1000);
                        break;
                    }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void StartAttackThyala()
        {
            Creature* thyala = sObjectAccessor->GetCreature(*me, m_thyalaGUID);
            if (!thyala)
                return;

            if (!thyala->IsAlive() || !thyala->IsInWorld())
            {
                me->DespawnOrUnsummon(1);
                return;
            }

            if (me->IsInCombat())
                if (Unit* npc = me->GetVictim())
                    if (npc->GetEntry() == NPC_DARK_RANGER_THYALA)
                        return;

            me->SetReactState(REACT_AGGRESSIVE);
            me->GetMotionMaster()->MoveChase(thyala, 3.0f, frand(0.0f, 6.28f));
            me->Attack(thyala, true);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_mastiff_36405AI(creature);
    }
};

// 36290 
class npc_lord_godfrey_36290 : public CreatureScript
{
public:
    npc_lord_godfrey_36290() : CreatureScript("npc_lord_godfrey_36290") { }

    enum eNpc
    {
        QUEST_AS_THE_LAND_SHATTERS = 14396,
        SPELL_PHASE_QUEST_ZONE_SPECIFIC_07 = 68482,
        SPELL_PHASE_QUEST_ZONE_SPECIFIC_08 = 68483,
        SPELL_FORCECAST_CATACLYSM_I = 69027,
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == 14396)
        {
            // creature->CastSpell(player, SPELL_FORCECAST_CATACLYSM_I, true);
            player->RemoveAura(SPELL_PHASE_QUEST_ZONE_SPECIFIC_07);
            player->AddAura(SPELL_PHASE_QUEST_ZONE_SPECIFIC_08, player);
        }

        return true;
    }
};

// Phase 16384 // from here: WorldMap 678 and TerrainSwap 655

// 36440
class npc_drowning_watchman_36440 : public CreatureScript
{
public:
    npc_drowning_watchman_36440() : CreatureScript("npc_drowning_watchman_36440") { }

    enum eNpc
    {
        QUEST_GASPING_FOR_BREATH = 14395,
        NPC_PRINCE_LIAM_GREYMANE = 36451,
        NPC_DROWNING_WATCHMANN_CREDIT = 36450,
        SPELL_PARACHUTE = 45472,
        SPELL_RESCUE_DROWNING_WATCHMANN = 68735,
        SPELL_SAVE_DROWNING_MILITIA_EFFECT = 68737,
        SPELL_EXIT_VEHICLE = 68741,
        EVENT_MASTER_RESET = 201,
        EVENT_CHECK_NEAR_GREYMANE,
        EVENT_DESPAWN,
    };

    struct npc_drowning_watchman_36440AI : public ScriptedAI
    {
        npc_drowning_watchman_36440AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        bool     m_isOnPlayer;

        void Reset() override
        {
            m_playerGUID = 0;
            m_isOnPlayer = false;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override 
        { 
            if (!m_isOnPlayer)
                if (spell->Id == SPELL_RESCUE_DROWNING_WATCHMANN)
                    if (Player* player = caster->ToPlayer())
                        if (player->GetQuestStatus(QUEST_GASPING_FOR_BREATH) == QUEST_STATUS_INCOMPLETE)
                        {
                            m_isOnPlayer = true;
                            m_playerGUID = player->GetGUID();
                            m_events.ScheduleEvent(EVENT_MASTER_RESET, 60000);
                            m_events.ScheduleEvent(EVENT_CHECK_NEAR_GREYMANE, 1000);
                        }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_MASTER_RESET:
                    me->DespawnOrUnsummon(10);
                    break;
                case EVENT_CHECK_NEAR_GREYMANE:
                    if (m_isOnPlayer)
                        if (Creature* liam = me->FindNearestCreature(NPC_PRINCE_LIAM_GREYMANE, 15.0f))
                            if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                                if (me->m_positionZ > 0.75f)
                                {
                                    player->KilledMonsterCredit(NPC_DROWNING_WATCHMANN_CREDIT);
                                    player->CastSpell(me, SPELL_SAVE_DROWNING_MILITIA_EFFECT, true);
                                    player->CastSpell(me, SPELL_EXIT_VEHICLE, true);
                                    Talk(0, player);
                                    //me->ExitVehicle();
                                    m_events.ScheduleEvent(EVENT_DESPAWN, 3000);                                    
                                    break;
                                }

                    m_events.ScheduleEvent(EVENT_CHECK_NEAR_GREYMANE, 1000);
                    break;
                case EVENT_DESPAWN:
                    me->DespawnOrUnsummon(10);
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_drowning_watchman_36440AI(creature);
    }
};

// 36440
class npc_chance_36459 : public CreatureScript
{
public:
    npc_chance_36459() : CreatureScript("npc_chance_36459") { }

    enum eNpc
    {
        QUEST_GRANDMAS_CAT = 14401,
        NPC_CAT = 36459,
        NPC_LUCIUS = 36461,
        EVENT_CHECK_PLAYER = 101,
        EVENT_CREATE_LUCIUS,
        EVENT_MASTER_RESET,
    };

    struct npc_chance_36459AI : public ScriptedAI
    {
        npc_chance_36459AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_luciusGUID;
        uint64   m_playerGUID;
        bool     m_isLucisKilled;

        void Reset() override
        {
            m_events.Reset();
            m_events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
            m_luciusGUID = 0;
            m_playerGUID = 0;
            m_isLucisKilled = false;
        }

        void JustSummoned(Creature* summon) override 
        { 
            if (summon->GetEntry() == NPC_LUCIUS)
                summon->AI()->Talk(1);
        }

        void SummonedCreatureDies(Creature* summon, Unit* killer) override 
        { 
            m_isLucisKilled = true;
            m_luciusGUID = 0;
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_PLAYER:
                {
                    if (!m_playerGUID)
                    {
                        if (Player* player = me->FindNearestPlayer(10.0f))
                            if (player->GetQuestStatus(QUEST_GRANDMAS_CAT) == QUEST_STATUS_INCOMPLETE)
                            {
                                m_playerGUID = player->GetGUID();
                                m_events.ScheduleEvent(EVENT_MASTER_RESET, 180000);
                                me->SummonCreature(NPC_LUCIUS, -2109.36f, 2330.28f, 7.36667f, 0.151307f, TEMPSUMMON_TIMED_DESPAWN, 180000);
                            }
                    }
                    else if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                    {
                        if (player->GetQuestStatus(QUEST_GRANDMAS_CAT) == QUEST_STATUS_COMPLETE)
                        {
                            me->DespawnOrUnsummon(10);
                            Reset();
                        }
                    }
                    else if (m_isLucisKilled)
                        Reset();

                    m_events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
                    break;
                }
                case EVENT_MASTER_RESET:
                {
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
        return new npc_chance_36459AI(creature);
    }
};

// 36488
class npc_forsaken_castaway_36488 : public CreatureScript
{
public:
    npc_forsaken_castaway_36488() : CreatureScript("npc_forsaken_castaway_36488") { }

    enum eNpc
    {
       
    };

    struct npc_forsaken_castaway_36488AI : public ScriptedAI
    {
        npc_forsaken_castaway_36488AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_luciusGUID;
        uint64   m_playerGUID;
        bool     m_isLucisKilled;

        void DamageDealt(Unit* victim, uint32& damage, DamageEffectType damageType) 
        { 
            uint8 rol = urand(0, 100);
            if (victim->GetEntry() == 36454 || victim->GetEntry() == 36455 || victim->GetEntry() == 36492 || victim->GetEntry() == 36456)
                if (rol < 70 || victim->GetHealthPct() < 70.0f)
                    damage = 0;
                else
                    damage = 1;
        }

        void DamageTaken(Unit* attacker, uint32& damage) override 
        { 
            uint8 rol = urand(0, 100);
            if (attacker->GetEntry() == 36454 || attacker->GetEntry() == 36455 || attacker->GetEntry() == 36492 || attacker->GetEntry() == 36456)
                if (rol < 70)
                    damage = 0;
                else
                    damage = 1;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_forsaken_castaway_36488AI(creature);
    }
};

// 36555
class npc_mountain_horse_36555 : public CreatureScript
{
public:
    npc_mountain_horse_36555() : CreatureScript("npc_mountain_horse_36555") { }

    enum eNpc
    {
        QUEST_THE_HUNGRY_ETTIN = 54416,
        NPC_LORNA_CROWLEY = 36457,
        SPELL_ROUND_UP_HORSE = 68903,
        SPELL_ROPE_IN_HORSE = 68908,
        SPELL_ROPE_CHANNEL = 68940,
        SPELL_MOUNTAIN_HORSE_CREDIT = 68917,
        SPELL_RIDE_VEHICLE = 94654,
        EVENT_START_FOLLOWING = 101,
    };

    struct npc_mountain_horse_36555AI : public ScriptedAI
    {
        npc_mountain_horse_36555AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_lornaGUID;
        float    m_dist;
        float    m_angle;
        float    m_size;
        Position m_oldPosition;
        bool     m_isLornaNear;
        bool     m_isPlayerMounted;
        bool     m_hasPlayerRope;


        void Reset() override
        {
            m_events.Reset();
            m_playerGUID = 0;
            m_lornaGUID = 0;
            m_isLornaNear = false;
            m_isPlayerMounted = false;
            m_hasPlayerRope = false;
            me->SetWalk(false);
            me->SetSpeed(MOVE_RUN, 1.4f);
        }

        void IsSummonedBy(Unit* summoner) override 
        { 
            if (Player* player = summoner->ToPlayer())
            {
                m_playerGUID = summoner->GetGUID();
                me->CastSpell(player, SPELL_ROPE_CHANNEL, true);
                m_dist = frand(3.0f, 5.0f);
                m_angle = frand(2.59f, 3.53f);
                m_size = me->GetObjectSize();
                m_oldPosition = player->GetPosition();
                m_events.ScheduleEvent(EVENT_START_FOLLOWING, 100);
            }
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (Creature* lorna = who->ToCreature())
                if (lorna->GetEntry() == NPC_LORNA_CROWLEY)
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        m_lornaGUID = lorna->GetGUID();
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_FOLLOWING:
                {                    
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                    {
                        CheckLornaRelated(player);
                        if (abs(m_oldPosition.GetExactDist(player) > 0.5f))
                        {
                            Position pos;
                            player->GetNearPoint(player, pos.m_positionX, pos.m_positionY, pos.m_positionZ, m_size, m_dist, m_angle);
                            me->GetMotionMaster()->MovePoint(0, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ());
                            m_oldPosition = player->GetPosition();
                        }
                        if (!m_isPlayerMounted && m_hasPlayerRope)
                        {
                            if (m_isLornaNear)
                                me->CastSpell(player, SPELL_MOUNTAIN_HORSE_CREDIT);
                            me->DespawnOrUnsummon();
                        }
                    }
                    m_events.ScheduleEvent(EVENT_START_FOLLOWING, 100);
                    break;
                }
                }
            }
        }

        void CheckLornaRelated(Player* player)
        {
            if (!player)
                return;

            m_isPlayerMounted = player->HasAura(SPELL_RIDE_VEHICLE);
            m_hasPlayerRope = player->HasAura(SPELL_ROPE_CHANNEL);
            if (m_lornaGUID)
                if (Creature* lorna = sObjectAccessor->GetCreature(*me, m_lornaGUID))
                    m_isLornaNear = (player->GetDistance(lorna) < 10.0f);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_mountain_horse_36555AI(creature);
    }
};

// 36540
class npc_mountain_horse_36540 : public CreatureScript
{
public:
    npc_mountain_horse_36540() : CreatureScript("npc_mountain_horse_36540") { }

    enum eNpc
    {
        QUEST_THE_HUNGRY_ETTIN = 54416,
        NPC_LORNA_CROWLEY = 36457,
        SPELL_ROUND_UP_HORSE = 68903,
        SPELL_ROPE_IN_HORSE = 68908,
        SPELL_ROPE_CHANNEL = 68940,
        EVENT_START_FOLLOWING = 101,
        EVENT_CHECK_HEALTH_AND_LORNA,
    };

    struct npc_mountain_horse_36540AI : public VehicleAI
    {
        npc_mountain_horse_36540AI(Creature* creature) : VehicleAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_lornaGUID;
        float    m_dist;
        float    m_angle;
        float    m_size;
        Position m_oldPosition;
        bool     m_lornaIsNear;

        void Reset() override
        {
            m_events.Reset();
            m_playerGUID = 0;
            m_lornaGUID = 0;
            m_lornaIsNear = false;
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override
        {
            if (apply)
            {
                if (Player* player = passenger->ToPlayer())
                {
                    m_playerGUID = player->GetGUID();
                    me->SetMaxHealth(250);
                }
                m_events.ScheduleEvent(EVENT_CHECK_HEALTH_AND_LORNA, 1000);
            }
            else if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
            {
                if (m_lornaIsNear)
                {
                    player->KilledMonsterCredit(36560);
                    me->DespawnOrUnsummon(1000);
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
                case EVENT_CHECK_HEALTH_AND_LORNA:
                    me->SetHealth(me->GetMaxHealth());

                    if (!m_lornaGUID)
                        if (Creature* lorna = me->FindNearestCreature(NPC_LORNA_CROWLEY, 100.0f))
                            m_lornaGUID = lorna->GetGUID();

                    if (!m_lornaIsNear)
                        if (Creature* lorna = ObjectAccessor::GetCreature(*me, m_lornaGUID))
                            if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                                m_lornaIsNear = (player->GetDistance(lorna) < 7.0f);

                    m_events.ScheduleEvent(EVENT_CHECK_HEALTH_AND_LORNA, 1000);
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_mountain_horse_36540AI(creature);
    }
};

// 36452
class npc_gwen_armstead_36452 : public CreatureScript
{
public:
    npc_gwen_armstead_36452() : CreatureScript("npc_gwen_armstead_36452") {}

    enum eNpc
    {
        QUEST_TO_GREYMANE_MANOR = 14465,
        SPELL_FORCECAST_SUMMON_SWIFT_MOUNTAIN_HORSE = 69256,
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_TO_GREYMANE_MANOR)
        {
            player->CastSpell(player, SPELL_FORCECAST_SUMMON_SWIFT_MOUNTAIN_HORSE);
        }
        return true;
    }
};

// Phase 16384 + 32768 

// 36741
class npc_swift_mountain_horse_36741 : public CreatureScript
{
public:
    npc_swift_mountain_horse_36741() : CreatureScript("npc_swift_mountain_horse_36741") { }

    enum eNpc
    {
        SPELL_PHASE_QUEST_ZONE_SPECIFIC_09 = 69077,
        SPELL_FORCECAST_UPDATE_ZONE_AURAS = 94828,
        SPELL_UPDATE_ZONE_AURAS = 89180,
        WAYPOINT_ID = 3674101,

    };

    struct npc_swift_mountain_horse_36741AI : public VehicleAI
    {
        npc_swift_mountain_horse_36741AI(Creature* creature) : VehicleAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        
        void Reset() override
        {
            m_events.Reset();
            m_playerGUID = 0;
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == WAYPOINT_MOTION_TYPE)
                switch (id)
                {
                case 2:
                {
                    if (GameObject* door = me->FindNearestGameObject(196399, 15.0f))
                        door->UseDoorOrButton(5000);
                    break;
                }
                case 3:
                {
                    if (GameObject* door = me->FindNearestGameObject(196399, 15.0f))
                        door->ResetDoorOrButton();
                    break;
                }
                case 9:
                {
                    if (GameObject* door = me->FindNearestGameObject(196401, 15.0f))
                        door->UseDoorOrButton(5000);
                    break;
                }
                case 10:
                {
                    if (GameObject* door = me->FindNearestGameObject(196401, 15.0f))
                        door->ResetDoorOrButton();
                    break;
                }
                case 11:
                {
                    me->GetVehicleKit()->RemoveAllPassengers();
                    break;
                }
                }
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override
        {
            if (apply)
            {
                if (Player* player = passenger->ToPlayer())
                {
                    m_playerGUID = player->GetGUID();
                    me->CastSpell(player, SPELL_FORCECAST_UPDATE_ZONE_AURAS, true);
                    me->GetMotionMaster()->MovePath(WAYPOINT_ID, false);
                }
            }
            else 
            {
                if (Player* player = passenger->ToPlayer())
                    player->AddAura(SPELL_PHASE_QUEST_ZONE_SPECIFIC_09, player);

                me->DespawnOrUnsummon(1000);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_swift_mountain_horse_36741AI(creature);
    }
};

// 36606 
class npc_queen_mia_greymane_36606 : public CreatureScript
{
public:
    npc_queen_mia_greymane_36606() : CreatureScript("npc_queen_mia_greymane_36606") { }

    enum eNpc
    {
        QUEST_TO_GREYMANE_MANOR = 14465,
        SPELL_UPDATE_BIND_TO_GREYMANE_MANOR = 82892,
    };

    bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* quest, uint32 /*opt*/) 
    {
        if (quest->GetQuestId() == QUEST_TO_GREYMANE_MANOR)
            player->CastSpell(player, SPELL_UPDATE_BIND_TO_GREYMANE_MANOR);

        return false; 
    }
};

// 36743 
class npc_king_genn_greymane_36743 : public CreatureScript
{
public:
    npc_king_genn_greymane_36743() : CreatureScript("npc_king_genn_greymane_36743") { }

    enum eNpc
    {
        QUEST_ALAS_GILNEAS = 14467,
        SPELL_PHASE_QUEST_ZONE_SPECIFIC_08 = 68483, //  16384
        SPELL_PHASE_QUEST_ZONE_SPECIFIC_09 = 69077, //  32768
        SPELL_PHASE_QUEST_ZONE_SPECIFIC_11 = 69484, // 131072
        SPELL_FORCECAST_GILNEAS_TELESCOPE = 69258,
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_ALAS_GILNEAS)
        {
            player->RemoveAura(SPELL_PHASE_QUEST_ZONE_SPECIFIC_08);
            player->AddAura(SPELL_PHASE_QUEST_ZONE_SPECIFIC_11, player);
            player->CastSpell(player, SPELL_FORCECAST_GILNEAS_TELESCOPE);
        }

        return true;
    }
};

// Phase 32768 + 131072  // from here: WorldMap 679 and TerrainSwap 656

// 44928
class npc_stagecoach_carriage_44928 : public CreatureScript
{
public:
    npc_stagecoach_carriage_44928() : CreatureScript("npc_stagecoach_carriage_44928") { }

    enum eNpc
    {
        QUEST_EXODUS = 24438,
        SPELL_SUMMON_CARRIAGE = 72767,
        NPC_HARNESS_38755 = 38755,
        NPC_HARNESS_43336 = 43336,
        NPC_CAR_43337 = 43337,
        PLAYER_GUID = 99999, 
    };

    bool OnGossipHello(Player* player, Creature* creature) 
    { 
        if (player->GetQuestStatus(QUEST_EXODUS) == QUEST_STATUS_COMPLETE)
            if (Creature* harness = creature->FindNearestCreature(NPC_HARNESS_38755, 15.0f))
                player->SummonCreature(NPC_HARNESS_43336, harness->GetPosition(), TEMPSUMMON_MANUAL_DESPAWN);                
                    
        return true; 
    }
};

// 43336
class npc_harness_43336 : public CreatureScript
{
public:
    npc_harness_43336() : CreatureScript("npc_harness_43336") { }

    enum eNpc
    {
        WAYPOINT_ID = 4492801,
        NPC_LORNA_CRAWLEY = 51409,
        NPC_HARNESS_43336 = 43336,
        NPC_CARRIAGE_43337 = 43337,
        PLAYER_GUID = 99999,
        LORNA_SAY_ATTACK = 1,
        CAR_DESPAWN = 2,
        EVENT_START_MOVEMENT = 101,
        EVENT_PLAYER_ENTER_VEHICLE,
    };

    struct npc_harness_43336AI : public VehicleAI
    {
        npc_harness_43336AI(Creature* creature) : VehicleAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_carriageGUID;

        void Reset() override
        {
            m_events.Reset();
            m_playerGUID = 0;
            m_carriageGUID = 0;           
        }

        void IsSummonedBy(Unit* summoner) override 
        { 
            if (Player* player = summoner->ToPlayer())
                m_playerGUID = player->GetGUID();
        }

        void JustSummoned(Creature* summon) override
        {
            if (Creature* carriage = summon->ToCreature())
                if (carriage->GetEntry() == NPC_CARRIAGE_43337)
                {
                    m_carriageGUID = carriage->GetGUID();
                    m_events.ScheduleEvent(EVENT_PLAYER_ENTER_VEHICLE, 1000);
                }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == WAYPOINT_MOTION_TYPE)
                switch (id)
            {
                case 3:
                {
                    if (GameObject* door = me->FindNearestGameObject(196401, 50.0f))
                        door->ResetDoorOrButton();
                    break;
                }
                case 15:
                {
                    if (GameObject* door = me->FindNearestGameObject(196412, 15.0f))
                        door->UseDoorOrButton(5000);
                    break;
                }
                case 16:
                {
                    if (GameObject* door = me->FindNearestGameObject(196412, 15.0f))
                        door->ResetDoorOrButton();
                    break;
                }
                case 28:
                {
                    // attack from orc...
                    if (Creature* car = sObjectAccessor->GetCreature(*me, m_carriageGUID))
                        car->GetAI()->DoAction(LORNA_SAY_ATTACK);
                    break;
                }
                case 33:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        player->ExitVehicle();
                    break;
                }
                case 44:
                {
                    me->DespawnOrUnsummon(1000);
                    if (Creature* car = sObjectAccessor->GetCreature(*me, m_carriageGUID))
                        car->GetAI()->DoAction(CAR_DESPAWN);
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
                case EVENT_PLAYER_ENTER_VEHICLE:
                {
                    if (Creature* car = sObjectAccessor->GetCreature(*me, m_carriageGUID))
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                            player->EnterVehicle(car, 0);

                    m_events.ScheduleEvent(EVENT_START_MOVEMENT, 1000);
                    break;
                }
                case EVENT_START_MOVEMENT:
                {
                    if (GameObject* door = me->FindNearestGameObject(196401, 25.0f))
                        door->UseDoorOrButton(5000);
                    me->GetMotionMaster()->MovePath(WAYPOINT_ID, false);
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_harness_43336AI(creature);
    }
};

// 43337
class npc_stagecoach_carriage_43337 : public CreatureScript
{
public:
    npc_stagecoach_carriage_43337() : CreatureScript("npc_stagecoach_carriage_43337") { }

    enum eNpc
    {
        NPC_LORNA_CRAWLEY = 51409,
        NPC_HARNESS_43336 = 43336,
        PLAYER_GUID = 99999,
    };

    struct npc_stagecoach_carriage_43337AI : public VehicleAI
    {
        npc_stagecoach_carriage_43337AI(Creature* creature) : VehicleAI(creature) { }

        uint64 m_playerGUID;
        uint64   m_lornaGUID;

        void Reset() override
        {
            m_playerGUID = 0;
            m_lornaGUID = 0;
        }

        void JustSummoned(Creature* summon) override
        {
            if (Creature* lorna = summon->ToCreature())
                if (lorna->GetEntry() == NPC_LORNA_CRAWLEY)
                    m_lornaGUID = lorna->GetGUID();
        }

        void DoAction(int32 param) override 
        { 
            if (param == 1)
                if (Creature* lorna = sObjectAccessor->GetCreature(*me, m_lornaGUID))
                    lorna->AI()->Talk(0);
            if (param == 2)
                me->DespawnOrUnsummon(1000);
        }
   };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_stagecoach_carriage_43337AI(creature);
    }
};

// 37065
class npc_prince_liam_greymane_37065 : public CreatureScript
{
public:
    npc_prince_liam_greymane_37065() : CreatureScript("npc_prince_liam_greymane_37065") { }

    enum eNpc
    {
        NPC_KOROTH = 37808,
        MOVEMENT_KOROTH = 2515531,
        QUEST_INTRODUCTIONS_ARE_IN_ORDER = 24472,
        QUEST_STORMGLEN = 24483,
        SPELL_GENERIC_QUEST_INVISIBLE_DETECTION_10 = 84481,
    };

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/) 
    { 
        if (quest->GetQuestId() == QUEST_INTRODUCTIONS_ARE_IN_ORDER)
        {
            if (Creature* koroth = creature->FindNearestCreature(NPC_KOROTH, 50.0f))
            {
                player->AddAura(SPELL_GENERIC_QUEST_INVISIBLE_DETECTION_10, player);
                koroth->SetSpeed(MOVE_RUN, 1.3f);
                koroth->SetReactState(REACT_AGGRESSIVE);
                koroth->GetMotionMaster()->MovePath(MOVEMENT_KOROTH, false);
                koroth->AI()->Talk(0);
            }
        }
        return false; 
    }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_STORMGLEN)
        {
            player->RemoveAura(SPELL_GENERIC_QUEST_INVISIBLE_DETECTION_10);
        }
        return true;
    }
};

// 6687
class at_the_blackwald_6687 : public AreaTriggerScript
{
public:
    at_the_blackwald_6687() : AreaTriggerScript("at_the_blackwald_6687") { }

    enum eAreatrigger
    {
        QUEST_LOSING_YOUR_TAIL = 24616,
        SPELL_FREEZING_TRAP_EFFECT = 70794,
		NPC_DARK_SCOUT = 37953,
    };

	bool OnTrigger(Player* player, const AreaTriggerEntry* at) override
	{
		if (player->GetQuestStatus(QUEST_LOSING_YOUR_TAIL) == QUEST_STATUS_INCOMPLETE)
			if (!player->FindNearestCreature(NPC_DARK_SCOUT, 50.0f))
				player->CastSpell(player, SPELL_FREEZING_TRAP_EFFECT, true);
		return false;
	}
};

// 37953
class npc_dark_scout_37953 : public CreatureScript
{
public:
    npc_dark_scout_37953() : CreatureScript("npc_dark_scout_37953") { }

    enum eNpc
    {
        QUEST_LOSING_YOUR_TAIL = 24616,
        SPELL_AIMED_SHOOT = 70796,
        SPELL_FREEZING_TRAP_EFFECT = 70794,
        TALK_EASY = 0,
        TALK_DO = 2,
        TALK_HOW = 1,
        EVENT_CHECK_PLAYER = 101,
        EVENT_TALK_START,
        EVENT_SHOOT,
        EVENT_CHECK_AURA,
        EVENT_MELEE_ATTACK,
    };

    struct npc_dark_scout_37953AI : public ScriptedAI
    {
        npc_dark_scout_37953AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64 m_playerGUID;
       

        void Reset() override
        {
            m_events.Reset();
            m_playerGUID = 0;
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                me->GetMotionMaster()->Clear();
                me->SetFacingToObject(player);
                me->AI()->Talk(TALK_EASY);
                m_events.ScheduleEvent(EVENT_TALK_START, 5000);
                m_events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
				switch (eventId)
				{
				case EVENT_CHECK_PLAYER:
				{
					if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
						if (player->GetQuestStatus(QUEST_LOSING_YOUR_TAIL) == QUEST_STATUS_INCOMPLETE)
							if (player->GetDistance2d(me) < 30.0f)
							{
								if (!me->IsInCombat())
									m_events.ScheduleEvent(EVENT_MELEE_ATTACK, 500);
								m_events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
								break;
							}
					me->DespawnOrUnsummon(100);
					break;
				}
				case EVENT_TALK_START:
				{
					if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
						Talk(TALK_DO, player);
					m_events.ScheduleEvent(EVENT_SHOOT, 7500);
					m_events.ScheduleEvent(EVENT_CHECK_AURA, 250);
					break;
				}
				case EVENT_SHOOT:
				{
					if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
					{
						m_events.CancelEvent(EVENT_CHECK_AURA);
						me->CastSpell(player, SPELL_AIMED_SHOOT);
						me->GetMotionMaster()->Clear();
						me->SetWalk(true);
						me->SetSpeed(MOVE_WALK, 1.0f);
						me->GetMotionMaster()->MoveChase(player);
						me->Attack(player, true);
					}
					break;
				}
				case EVENT_CHECK_AURA:
				{
					if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
						if (player->HasAura(SPELL_FREEZING_TRAP_EFFECT))
						{
							m_events.ScheduleEvent(EVENT_CHECK_AURA, 250);
							break;
						}
					m_events.CancelEvent(EVENT_SHOOT);
					Talk(TALK_HOW);
					m_events.ScheduleEvent(EVENT_MELEE_ATTACK, 1500);
					break;
				}
				case EVENT_MELEE_ATTACK:
				{
					if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
						if (!player->IsInCombat())
							if (player->GetDistance2d(me) < 30.0f)
							{
								me->GetMotionMaster()->Clear();
								me->SetWalk(true);
								me->SetSpeed(MOVE_WALK, 1.0f);
								me->GetMotionMaster()->MoveChase(player);
								me->Attack(player, true);
							}
					m_events.ScheduleEvent(EVENT_MELEE_ATTACK, 1500);
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
        return new npc_dark_scout_37953AI(creature);
    }
};

// 49944
class item_belysras_talisman_49944 : public ItemScript
{
public:
    item_belysras_talisman_49944() : ItemScript("item_belysras_talisman_49944") { }

    enum eItem
    {
        QUEST_LOSING_YOUR_TAIL = 24616,
        SPELL_FREEZING_TRAP_EFFECT = 70794,
    };

    bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& targets) override
    {
        if (player->GetQuestStatus(QUEST_LOSING_YOUR_TAIL) == QUEST_STATUS_INCOMPLETE)
            if (player->HasAura(SPELL_FREEZING_TRAP_EFFECT))
                player->RemoveAura(SPELL_FREEZING_TRAP_EFFECT);

        return false;
    }
};

// 38195
class npc_tobias_mistmantle_38051 : public CreatureScript
{
public:
	npc_tobias_mistmantle_38051() : CreatureScript("npc_tobias_mistmantle_38051") { }

	enum eNpc
	{
		QUEST_AT_OUR_DOORSTEP = 24627,
		NPC_LORD_DARIUS_CROWLEY = 37195,
		EVENT_START_ANIM = 101,
		EVENT_START_TALK = 102,
	};

	struct npc_tobias_mistmantle_38051AI : public ScriptedAI
	{
		npc_tobias_mistmantle_38051AI(Creature* creature) : ScriptedAI(creature) { }

		EventMap m_events;
		uint64   m_dariusGUID;

		void Reset() override
		{
			m_events.Reset();
			m_dariusGUID = 0;
			if (Creature* darius = me->FindNearestCreature(NPC_LORD_DARIUS_CROWLEY, 50.0f))
				m_dariusGUID = darius->GetGUID();
			m_events.ScheduleEvent(EVENT_START_ANIM, 250);
		}

		void MovementInform(uint32 type, uint32 id) override
		{
			if (type == POINT_MOTION_TYPE)
				if (id == 1001)
				{
					me->HandleEmoteCommand(EMOTE_ONESHOT_KNEEL);
					m_events.ScheduleEvent(EVENT_START_TALK, 250);
				}
				else if (id = 1002)
					me->DespawnOrUnsummon();
		}

		void UpdateAI(uint32 diff) override
		{
			m_events.Update(diff);

			while (uint32 eventId = m_events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_START_ANIM:
				{
					me->GetMotionMaster()->MovePoint(1001, -2068.833252f, 1277.579468f, -85.201454f, true);
					break;
				}
				case EVENT_START_TALK:
				{
					Talk(0);
					if (Creature* darius = sObjectAccessor->GetCreature(*me, m_dariusGUID))
						darius->SetFacingToObject(me);
					m_events.ScheduleEvent(EVENT_START_TALK + 1, 5000);
					break;
				}
				case EVENT_START_TALK + 1:
				{
					if (Creature* darius = sObjectAccessor->GetCreature(*me, m_dariusGUID))
						darius->AI()->Talk(1);
					m_events.ScheduleEvent(EVENT_START_TALK + 2, 5000);
					break;
				}
				case EVENT_START_TALK + 2:
				{
					Talk(1);
					m_events.ScheduleEvent(EVENT_START_TALK + 3, 5000);
					break;
				}
				case EVENT_START_TALK + 3:
				{
					me->HandleEmoteCommand(EMOTE_STATE_NONE);
					me->GetMotionMaster()->MovePoint(1002, -2069.574951f, 1305.952393f, -83.195412f, true);
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
		return new npc_tobias_mistmantle_38051AI(creature);
	}
};

// 37876
class npc_king_genn_greymane_37876 : public CreatureScript
{
public:
	npc_king_genn_greymane_37876() : CreatureScript("npc_king_genn_greymane_37876") { }

	enum eNpc
	{
		QUEST_BETRAYAL_AT_TEMPESTS_REACH = 24592,
		NPC_LORD_GODFREY = 37875,
		SPELL_FORCE_REACTION_1 = 61899,
		EVENT_START_ANIM = 101,
	};

	bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
	{
		if (quest->GetQuestId() == QUEST_BETRAYAL_AT_TEMPESTS_REACH)
		{
			player->CastSpell(player, SPELL_FORCE_REACTION_1);
			creature->AI()->DoAction(1);
		}

		return false;
	}

	struct npc_king_genn_greymane_37876AI : public ScriptedAI
	{
		npc_king_genn_greymane_37876AI(Creature* creature) : ScriptedAI(creature) { }

		EventMap m_events;
		uint64 m_godfreyGUID;

		void Reset() override
		{
			m_events.Reset();
			m_godfreyGUID = 0;
			if (Creature* godfrey = me->FindNearestCreature(NPC_LORD_GODFREY, 20.0f))
				m_godfreyGUID = godfrey->GetGUID();
		}

		void DoAction(int32 /*param*/) override
		{
			if (!m_godfreyGUID)
				if (Creature* godfrey = me->FindNearestCreature(NPC_LORD_GODFREY, 20.0f))
					m_godfreyGUID = godfrey->GetGUID();

			m_events.ScheduleEvent(EVENT_START_ANIM, 100);
		}

		void MovementInform(uint32 type, uint32 id) override
		{
			if (type == WAYPOINT_MOTION_TYPE)
				switch (id)
				{
				case 4:
				{
					if (Creature* godfrey = sObjectAccessor->GetCreature(*me, m_godfreyGUID))
					{
						godfrey->SetDisableGravity(false);
						godfrey->DespawnOrUnsummon(5000);
					}
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
				case EVENT_START_ANIM:
				{
					if (Creature* godfrey = sObjectAccessor->GetCreature(*me, m_godfreyGUID))
						m_events.ScheduleEvent(EVENT_START_ANIM+1, 100);
					break;
				}
				case EVENT_START_ANIM+1:
				{
					Talk(0);
					m_events.ScheduleEvent(EVENT_START_ANIM + 2, 5000);
					break;
				}
				case EVENT_START_ANIM + 2:
				{
					if (Creature* godfrey = sObjectAccessor->GetCreature(*me, m_godfreyGUID))
						godfrey->AI()->Talk(0);
					m_events.ScheduleEvent(EVENT_START_ANIM + 3, 3000);
					break;
				}
				case EVENT_START_ANIM + 3:
				{
					if (Creature* godfrey = sObjectAccessor->GetCreature(*me, m_godfreyGUID))
					{
						godfrey->GetMotionMaster()->MovePath(godfrey->GetDBTableGUIDLow(), false);
						godfrey->SetDisableGravity(true);
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
		return new npc_king_genn_greymane_37876AI(creature);
	}
};

// 38764
class npc_lord_hewell_38764 : public CreatureScript
{
public:
	npc_lord_hewell_38764() : CreatureScript("npc_lord_hewell_38764") { }

	enum eNpc
	{
		QUEST_FLANK_THE_FORSAKEN = 24677,
	};

	bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 /*action*/) 
	{
		if (player->GetQuestStatus(QUEST_FLANK_THE_FORSAKEN) == QUEST_STATUS_COMPLETE)
		{
			player->CastSpell(player, 72773);
		}

		return false; 
	}
};

// from here only phase 131072

// 38765
class npc_stout_mountain_horse_38765 : public CreatureScript
{
public:
	npc_stout_mountain_horse_38765() : CreatureScript("npc_stout_mountain_horse_38765") { }

	enum eNpc
	{
		QUEST_FLANK_THE_FORSAKEN = 24677,
		PATH_ID = 3876500,
		SPELL_DANS_EJECT_ALL_PASSENGERS = 51254,
		SPELL_FORCE_REACTION_1 = 61899,
		SPELL_PHASE_QUEST_ZONE_SPECIFIC_09 = 69077,
		EVENT_START_WAYPOINTS = 101,
		EVENT_STOP_WAYPOINTS = 102,
	};

	struct npc_stout_mountain_horse_38765AI : public VehicleAI
	{
		npc_stout_mountain_horse_38765AI(Creature* creature) : VehicleAI(creature) { }

		EventMap m_events;
		uint64 m_playerGUID;

		void Reset() override
		{
			m_events.Reset();
			m_playerGUID=0;
		}

		void IsSummonedBy(Unit* summoner) override
		{
			if (Player* player = summoner->ToPlayer())
			{
				m_playerGUID = summoner->GetGUID();				
				m_events.ScheduleEvent(EVENT_START_WAYPOINTS, 100);
			}
		}

		void MovementInform(uint32 type, uint32 id) override
		{
			if (type == WAYPOINT_MOTION_TYPE)
				switch (id)
				{
				case 41:
				{
					m_events.ScheduleEvent(EVENT_STOP_WAYPOINTS, 1000);
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
				case EVENT_START_WAYPOINTS:
				{
					me->GetMotionMaster()->MovePath(PATH_ID, false);
					break;
				}
				case EVENT_STOP_WAYPOINTS:
				{
					me->CastSpell(me, SPELL_DANS_EJECT_ALL_PASSENGERS);
					me->DespawnOrUnsummon(3000);
					if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
					{
						if (player->HasAura(SPELL_FORCE_REACTION_1))
							player->RemoveAura(SPELL_FORCE_REACTION_1);
						if (player->HasAura(SPELL_PHASE_QUEST_ZONE_SPECIFIC_09))
							player->RemoveAura(SPELL_PHASE_QUEST_ZONE_SPECIFIC_09);
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
		return new npc_stout_mountain_horse_38765AI(creature);
	}
};

// 37783
class npc_lorna_crowley_37783 : public CreatureScript
{
public:
	npc_lorna_crowley_37783() : CreatureScript("npc_lorna_crowley_37783") { }

	enum eNpc
	{
		QUEST_PUSH_THEM_OUT = 24676,
		SPELL_PHASE_QUEST_ZONE_SPECIFIC_12 = 69485,
	};

	bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
	{
		if (quest->GetQuestId() == QUEST_PUSH_THEM_OUT)
		{
			if (!player->HasAura(SPELL_PHASE_QUEST_ZONE_SPECIFIC_12))
			{
				// done by phase_definition and phase_area
				// player->AddAura(SPELL_PHASE_QUEST_ZONE_SPECIFIC_12, player);
			}
		}

		return false;
	}
};

// from here phase 262144 is active.. battle for gilneas in zone_gilneas_city3

void AddSC_zone_gilneas_duskhaven()
{	
    new npc_krennan_aranas_36331();
    new npc_king_genn_greymane_36332();
    new npc_gwen_armstead_34571();
    new go_mandragore_196394();
    new npc_horrid_abomination_36231();
    new spell_cast_keg_69094();
    new npc_cynthia_36267();
    new npc_james_36268();
    new npc_ashley_36269();
    new npc_forsaken_catapult_36283();
    new spell_launch_68659();
    new spell_fire_boulder_68591();
    new npc_mastiff_36409();
    new npc_mastiff_36405();
    new npc_lord_godfrey_36290();
    new npc_drowning_watchman_36440();
    new npc_chance_36459();
    new npc_forsaken_castaway_36488();
    new npc_mountain_horse_36555();
    new npc_mountain_horse_36540();
    new npc_gwen_armstead_36452();
    new npc_swift_mountain_horse_36741();
    new npc_queen_mia_greymane_36606();
    new npc_king_genn_greymane_36743();
    new npc_stagecoach_carriage_44928();
    new npc_harness_43336();
    new npc_stagecoach_carriage_43337();
    new npc_prince_liam_greymane_37065();
    new at_the_blackwald_6687();
    new npc_dark_scout_37953();
    new item_belysras_talisman_49944();
	new npc_tobias_mistmantle_38051();
	new npc_king_genn_greymane_37876();
	new npc_lord_hewell_38764();
	new npc_stout_mountain_horse_38765();
	new npc_lorna_crowley_37783();
};
