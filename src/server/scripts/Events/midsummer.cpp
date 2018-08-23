
// Scripted by Xinef

#include "script_helper.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Spell.h"
#include "SpellAuras.h"
#include "SpellScript.h"
#include "Player.h"
#include "GameObjectAI.h"
#include "PassiveAI.h"

enum eBonfire
{
    NPC_TORCH_TOSSING_TARGET_BUNNY = 25535,
    NPC_TORCH_CATCHING_TARGET_BUNNY = 26188,

    GO_MIDSUMMER_BONFIRE = 181288,
    GO_TORCH_TARGET_BRAZIER = 187708,

    SPELL_STAMP_OUT_BONFIRE = 45437,
    SPELL_STAMP_OUT_BONFIRE_QUEST_COMPLETE = 45458,
    SPELL_LIGHT_BONFIRE = 29831,
    SPELL_TORCH_TOSSING_TRAINIG_SUCCESS_A = 45719,
    SPELL_TORCH_TOSSING_TRAINIG_SUCCESS_H = 46651,
    SPELL_FLING_TORCH = 45669,
    SPELL_FLING_TORCH_DUMMY = 46747,
    SPELL_JUGGLE_TORCH_CATCH_QUEST = 45671,
    SPELL_MISSED_TORCH = 45676,
    SPELL_TORCH_COUNTER = 45693,

    QUEST_TORCH_TOSSING_A = 11731,
    QUEST_TORCH_TOSSING_H = 11922,
    QUEST_TORCH_CATCHING_A = 11657,
    QUEST_TORCH_CATCHING_H = 11923,
    QUEST_MORE_TORCH_TOSSING_A = 11921,
    QUEST_MORE_TORCH_TOSSING_H = 11926,
    QUEST_MORE_TORCH_CATCHING_A = 11924,
    QUEST_MORE_TORCH_CATCHING_H = 11925,

    ACTION_TORCH_INIT = 10,
    ACTION_TORCH_MISSING = 11,
    ACTION_TORCH_HIT = 12,
    ACTION_TORCH_FINISH = 13,

    GetSetDataPositionX = 20,
    GetSetDataPositionY = 21,
    GetSetDataPositionZ = 22,
    GetSetDataPositionO = 23,
    GetSetDataCounter = 24,
    GetSetData_CoolDown = 25,
};

// 16817
class npc_festival_loremaster_16817 : public CreatureScript
{
public:
    npc_festival_loremaster_16817() : CreatureScript("npc_festival_loremaster_16817") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case 11964:
            player->AreaExploredOrEventHappens(11964);
            break;
        }

        return false;
    }

};

// 16818
class npc_festival_talespinner_16818 : public CreatureScript
{
public:
    npc_festival_talespinner_16818() : CreatureScript("npc_festival_talespinner_16818") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case 11966:
            player->AreaExploredOrEventHappens(11966);
            break;
        }

        return false;
    }

};

// 26401
class npc_summer_scorchling_26401 : public CreatureScript
{
public:
    npc_summer_scorchling_26401() : CreatureScript("npc_summer_scorchling_26401") { }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt)
    {
        switch (quest->GetQuestId())
        {
        case 11964:
            creature->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
            creature->AI()->DoAction(ACTION_START_ANIM_01);
            break;
        }
        return false;
    }

    struct npc_summer_scorchling_26401AI : public ScriptedAI
    {
        npc_summer_scorchling_26401AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        bool     m_isAnimStarted;


        void Reset() override
        {
            m_playerGUID = 0;
            m_isAnimStarted = false;
        }

        void SetGUID(uint64 guid, int32 id)
        {
            switch (id)
            {
            case PLAYER_GUID:
                if (!m_isAnimStarted)
                    m_playerGUID = guid;
                break;
            }
        }

        void DoAction(int32 param)
        {
            switch (param)
            {
            case ACTION_START_ANIM_01:
                if (m_isAnimStarted)
                    return;
                m_isAnimStarted = true;
                m_events.RescheduleEvent(EVENT_START_ANIM_01, 500);
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
                case EVENT_START_ANIM_01:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(1, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_02, 1000);
                    break;
                case EVENT_TALK_PART_02:
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(2, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_03, 2000);
                    break;
                case EVENT_TALK_PART_03:
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(3, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_04, 3000);
                    break;
                case EVENT_TALK_PART_04:
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(4, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_05, 3000);
                    break;
                case EVENT_TALK_PART_05:
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(5, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_06, 500);
                    break;
                case EVENT_TALK_PART_06:
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(6, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_07, 2500);
                    break;
                case EVENT_TALK_PART_07:
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(7, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_08, 3000);
                    break;
                case EVENT_TALK_PART_08:
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(8, player);
                    me->AddAura(47114, me);
                    m_events.ScheduleEvent(EVENT_TALK_PART_09, 3000);
                    break;
                case EVENT_TALK_PART_09:
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(9, player);
                    me->RemoveAura(47114);
                    m_events.ScheduleEvent(EVENT_TALK_PART_10, 3000);
                    break;
                case EVENT_TALK_PART_10:
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(10, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_11, 3000);
                    break;
                case EVENT_TALK_PART_11:
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(11, player);
                    m_events.ScheduleEvent(EVENT_RESET_TARGET, 3000);
                    break;
                case EVENT_RESET_TARGET:
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
        return new npc_summer_scorchling_26401AI(creature);
    }
};

// 26520
class npc_festival_scorchling_26520 : public CreatureScript
{
public:
    npc_festival_scorchling_26520() : CreatureScript("npc_festival_scorchling_26520") { }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt)
    {
        switch (quest->GetQuestId())
        {
        case 11966:
            creature->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
            creature->AI()->DoAction(ACTION_START_ANIM_01);
            break;
        }
        return false;
    }

    struct npc_festival_scorchling_26520AI : public ScriptedAI
    {
        npc_festival_scorchling_26520AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        bool     m_isAnimStarted;

        void Reset() override
        {
            m_playerGUID = 0;
            m_isAnimStarted = false;
        }

        void SetGUID(uint64 guid, int32 id)
        {
            switch (id)
            {
            case PLAYER_GUID:
                if (!m_isAnimStarted)
                    m_playerGUID = guid;
                break;
            }
        }

        void DoAction(int32 param)
        {
            switch (param)
            {
            case ACTION_START_ANIM_01:
                if (m_isAnimStarted)
                    return;
                m_isAnimStarted = true;
                m_events.RescheduleEvent(EVENT_START_ANIM_01, 500);
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
                case EVENT_START_ANIM_01:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(1, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_02, 1000);
                    break;
                case EVENT_TALK_PART_02:
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(2, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_03, 2000);
                    break;
                case EVENT_TALK_PART_03:
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(3, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_04, 3000);
                    break;
                case EVENT_TALK_PART_04:
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(4, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_05, 3000);
                    break;
                case EVENT_TALK_PART_05:
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(5, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_06, 500);
                    break;
                case EVENT_TALK_PART_06:
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(6, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_07, 2500);
                    break;
                case EVENT_TALK_PART_07:
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(7, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_08, 3000);
                    break;
                case EVENT_TALK_PART_08:
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(8, player);
                    me->AddAura(47114, me);
                    m_events.ScheduleEvent(EVENT_TALK_PART_09, 3000);
                    break;
                case EVENT_TALK_PART_09:
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(9, player);
                    me->RemoveAura(47114);
                    m_events.ScheduleEvent(EVENT_TALK_PART_10, 3000);
                    break;
                case EVENT_TALK_PART_10:
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(10, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_11, 3000);
                    break;
                case EVENT_TALK_PART_11:
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(11, player);
                    m_events.ScheduleEvent(EVENT_RESET_TARGET, 3000);
                    break;
                case EVENT_RESET_TARGET:
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
        return new npc_festival_scorchling_26520AI(creature);
    }
};

// 25975 26113 
class npc_master_fire_flame_eater : public CreatureScript
{
public:
    npc_master_fire_flame_eater() : CreatureScript("npc_master_fire_flame_eater") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        switch (quest->GetQuestId())
        {
        case QUEST_TORCH_TOSSING_A:
            if (creature->AI()->GetData(1) == 0) // is a game running
            {
                creature->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
                creature->AI()->DoAction(ACTION_START_ANIM_01);
            }
            break;
        case QUEST_TORCH_CATCHING_A:
            creature->AI()->DoAction(ACTION_START_ANIM_02);
            break;
        case QUEST_MORE_TORCH_TOSSING_A:
            if (creature->AI()->GetData(1) == 0) // is a game running
            {
                creature->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
                creature->AI()->DoAction(ACTION_START_ANIM_03);
            }
            break;
        case QUEST_MORE_TORCH_CATCHING_A:
            creature->AI()->DoAction(ACTION_START_ANIM_04);
            break;
        }

        return false;
    }

    struct npc_master_fire_flame_eaterAI : public ScriptedAI
    {
        npc_master_fire_flame_eaterAI(Creature* c) : ScriptedAI(c) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_casterGUID;
        uint64   m_bunnyGUID;
        std::vector<GameObject*> m_braziersVec;
        uint8    m_randomIndex;
        uint8    m_hitCounter;

        void Reset() override
        {
            m_events.Reset();
            m_playerGUID = 0;
            m_randomIndex = 0;
            m_hitCounter = 0;
            me->setActive(false);
            m_events.RescheduleEvent(EVENT_INIT_TARGET, 1000);
        }

        void SetGUID(uint64 guid, int32 id)
        {
            switch (id)
            {
            case PLAYER_GUID:
                m_playerGUID = guid;
                break;
            }
        }

        uint32 GetData(uint32 id) const
        {
            switch (id)
            {
            case 1:
            {
                if (m_hitCounter > 0)
                    return 1;
                break;
            }
            }
            return 0;
        }

        void DoAction(int32 param)
        {
            switch (param)
            {
            case ACTION_START_ANIM_01: // Torch Tossing
            {
                m_hitCounter = 8;
                me->setActive(true);
                m_events.RescheduleEvent(EVENT_COOLDOWN_00, 90000);
                m_events.RescheduleEvent(EVENT_CHECK_PLAYER, 1000);
                m_events.ScheduleEvent(EVENT_START_ANIM_01, 500);
                break;
            }
            case ACTION_START_ANIM_03: // More Torch Tossing
            {
                m_hitCounter = 20;
                me->setActive(true);
                m_events.RescheduleEvent(EVENT_COOLDOWN_00, 90000);
                m_events.RescheduleEvent(EVENT_CHECK_PLAYER, 1000);
                m_events.ScheduleEvent(EVENT_START_ANIM_01, 500);
                break;
            }
            case ACTION_SPELL_HIT_01:
            {
                m_events.CancelEvent(EVENT_PLAY_PHASE_01);
                m_hitCounter -= 1;
                if (!m_hitCounter)
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        player->CastSpell(player, SPELL_TORCH_TOSSING_TRAINIG_SUCCESS_A, true); // quest complete spell
                    if (Creature* bunny = sObjectAccessor->GetCreature(*me, m_bunnyGUID))
                        bunny->DespawnOrUnsummon(10);
                    Reset();
                    return;
                }

                m_events.ScheduleEvent(EVENT_PLAY_PHASE_01, 750);
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
                case EVENT_INIT_TARGET:
                {
                    if (!m_braziersVec.size())
                        InitVectors();
                    break;
                }
                case EVENT_COOLDOWN_00:
                {
                    m_events.CancelEvent(EVENT_START_ANIM_03);
                    Reset();
                    break;
                }
                case EVENT_CHECK_PLAYER:
                {
                    Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID);
                    if (!player || player->GetQuestStatus(QUEST_TORCH_TOSSING_A) == QUEST_STATUS_FAILED)
                    {
                        Reset();
                        return;
                    }

                    m_events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
                    break;
                }
                case EVENT_START_ANIM_01:
                {
                    if (m_braziersVec.size() >= 5)
                        m_events.ScheduleEvent(EVENT_PREPARE_01, 500);
                    else
                        Reset();
                    break;
                }
                case EVENT_PREPARE_01:
                {
                    Position pos = m_braziersVec[0]->GetPosition();
                    if (Creature* bunny = me->SummonCreature(NPC_TORCH_TOSSING_TARGET_BUNNY, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 90000))
                    {
                        m_bunnyGUID = bunny->GetGUID();
                        bunny->AI()->SetGUID(m_playerGUID, PLAYER_GUID);
                        bunny->AI()->SetGUID(me->GetGUID(), CONTROLLER_GUID);
                        m_events.ScheduleEvent(EVENT_PLAY_PHASE_01, 1000);
                    }

                    break;
                }
                case EVENT_PLAY_PHASE_01:
                {
                    m_randomIndex = urand(0, 4);
                    TeleportBunnyToBraziers(m_randomIndex);
                    m_events.ScheduleEvent(EVENT_PLAY_PHASE_01, urand(1800, 3000));
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void InitVectors()
        {
            std::list<GameObject*> braziersList;
            std::list<Creature*> bunnyList;
            m_braziersVec.clear();
            me->GetGameObjectListWithEntryInGrid(braziersList, GO_TORCH_TARGET_BRAZIER, 40.0f);
            me->GetCreatureListWithEntryInGrid(bunnyList, NPC_TORCH_TOSSING_TARGET_BUNNY, 40.0f);
            for (std::list<Creature*>::const_iterator itr = bunnyList.begin(); itr != bunnyList.end(); ++itr)
                (*itr)->DespawnOrUnsummon(10);
            for (std::list<GameObject*>::const_iterator itr = braziersList.begin(); itr != braziersList.end(); ++itr)
                m_braziersVec.push_back(*itr);
        }

        void TeleportBunnyToBraziers(uint8 index)
        {
            Position pos;
            pos.Relocate(m_braziersVec[index]);
            if (Creature* bunny = sObjectAccessor->GetCreature(*me, m_bunnyGUID))
                bunny->NearTeleportTo(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation());
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_master_fire_flame_eaterAI(creature);
    }
};

// 25535
class npc_torch_tossing_target_bunny_25535 : public CreatureScript
{
public:
    npc_torch_tossing_target_bunny_25535() : CreatureScript("npc_torch_tossing_target_bunny_25535") { }

    struct npc_torch_tossing_target_bunny_25535AI : public ScriptedAI
    {
        npc_torch_tossing_target_bunny_25535AI(Creature* c) : ScriptedAI(c) { Initialize(); }

        uint64 m_playerGUID;
        uint64 m_controllerGUID;
        uint8  m_targetIndex;

        void Initialize()
        {
            m_controllerGUID = 0;
        }

        void Reset() override
        {
            m_playerGUID = 0;
            me->CastSpell(me, 43313, true);
        }

        void SetData(uint32 id, uint32 value)
        {
            switch (id)
            {
            case 1:
                m_targetIndex = id;
                break;
            }
        }

        void SetGUID(uint64 guid, int32 id)
        {
            switch (id)
            {
            case CONTROLLER_GUID:
                m_controllerGUID = guid;
                break;
            case PLAYER_GUID:
                m_playerGUID = guid;
                break;
            }
        }

        bool CanBeSeen(Player const* seer)
        {
            return seer->GetGUID() == m_playerGUID;
        }

        void SpellHit(Unit* caster, SpellInfo const* spellInfo)
        {
            // Triggered spell from torch
            if (Player* player = caster->ToPlayer())
                if (player->GetGUID() == m_playerGUID)
                    if (spellInfo->Id == 46054)
                    {
                        me->CastSpell(me, 45724, true); // hit visual anim
                        if (Creature* controller = sObjectAccessor->GetCreature(*me, m_controllerGUID))
                        {
                            controller->AI()->SetGUID(player->GetGUID(), CASTER_GUID);
                            controller->AI()->DoAction(ACTION_SPELL_HIT_01);
                        }
                    }
        }

        void UpdateAI(uint32 diff)
        {

        }

    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_torch_tossing_target_bunny_25535AI(creature);
    }
};

// 45716, 46630
class spell_midsummer_torch_quest : public SpellScriptLoader
{
public:
    spell_midsummer_torch_quest() : SpellScriptLoader("spell_midsummer_torch_quest") { }

    class spell_midsummer_torch_quest_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_midsummer_torch_quest_AuraScript)

            bool Load()
        {
            torchGUID = 0;
            return true;
        }

        uint64 torchGUID;

        void HandleEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* ar = GetTarget();
            if (Creature* cr = ar->SummonCreature(25535, ar->GetPositionX(), ar->GetPositionY(), ar->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 90000))
            {
                torchGUID = cr->GetGUID();
                cr->AI()->SetGUID(ar->GetGUID(), PLAYER_GUID);
                // GetId() == 45716 ? 8 : 20
            }
        }

        void HandleEffectRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Creature* cr = ObjectAccessor::GetCreature(*GetTarget(), torchGUID))
                cr->DespawnOrUnsummon(1);
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_midsummer_torch_quest_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_DETECT_AMORE, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectRemoveFn(spell_midsummer_torch_quest_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_DETECT_AMORE, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_midsummer_torch_quest_AuraScript();
    }
};

// 45671 46747
class spell_midsummer_fling_torch : public SpellScriptLoader
{
public:
    spell_midsummer_fling_torch() : SpellScriptLoader("spell_midsummer_fling_torch") {}

    class spell_midsummer_fling_torch_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_midsummer_fling_torch_SpellScript);

        bool _isHandled;

        bool Load()
        {
            _isHandled = false;
            return true;
        }

        void RemoveOldBunnys(Player* player)
        {
            std::list<Creature*> cList = player->FindNearestCreatures(NPC_TORCH_CATCHING_TARGET_BUNNY, 10.0f);
            for (std::list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); ++itr)
                (*itr)->DespawnOrUnsummon();
        }

        void ThrowNextTorch(Player* player)
        {
            Creature* bunny = player->FindNearestCreature(NPC_TORCH_CATCHING_TARGET_BUNNY, 5.0f);
            if (!bunny)
                bunny = player->SummonCreature(NPC_TORCH_CATCHING_TARGET_BUNNY, player->GetPosition(), TEMPSUMMON_TIMED_DESPAWN, 90000);

            if (bunny)
            {
                float f1 = frand(0, 0.25f);
                float f2 = frand(6.03f, 6.28f);
                Position pos = bunny->GetNearPosition(3.1f, RAND(f1, f2)); //   (frand(3.2f, 3.2f), frand(0.60f, 0.95f));
                bunny->NearTeleportTo(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation());
                player->CastSpell(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), SPELL_FLING_TORCH, true);
                if (!player->HasAura(SPELL_TORCH_COUNTER))
                    player->CastSpell(player, SPELL_TORCH_COUNTER, true);
            }
        }

        void HandleAfterCast()
        {
            if (Unit* caster = GetCaster())
                if (Player* player = caster->ToPlayer())
                    ThrowNextTorch(player);
        }

        void HandleScriptHitTarget(SpellEffIndex effIndex)
        {
            PreventHitDefaultEffect(effIndex);

            if (Unit* caster = GetCaster())
                if (Player* player = caster->ToPlayer())
                {
                    Player* hitter = GetHitPlayer();
                    Aura* aur = player->GetAura(SPELL_TORCH_COUNTER);
                    if (const WorldLocation* loc = GetExplTargetDest())
                        if (aur && hitter && loc->GetExactDist(player) < 4.5f && hitter->GetGUID() == player->GetGUID())
                        {
                            _isHandled = true;
                            aur->ModStackAmount(1);

                            uint8 count = 4;
                            if (player->GetQuestStatus(player->GetTeamId() ? 11925 : 11924) == QUEST_STATUS_INCOMPLETE) // More Torch Catching quests
                                count = 10;

                            if (aur->GetStackAmount() >= count)
                            {
                                //target->CastSpell(target, 46711, true); // Set Flag: all torch returning quests are complete
                                player->CastSpell(player, (player->GetTeamId() ? 46654 : 46081), true); // Quest completion
                                aur->SetDuration(1);
                                RemoveOldBunnys(player);
                                return;
                            }

                            ThrowNextTorch(player);
                        }
                        else
                        {
                            player->CastSpell(loc->GetPositionX(), loc->GetPositionY(), loc->GetPositionZ(), SPELL_MISSED_TORCH, true);
                            player->RemoveAurasDueToSpell(SPELL_TORCH_COUNTER);
                            RemoveOldBunnys(player);
                            return;
                        }
                }
            printf("Exit Check: %u \n", _isHandled);
        }

        void Register()
        {
            if (m_scriptSpellId == SPELL_FLING_TORCH_DUMMY)
                AfterCast += SpellCastFn(spell_midsummer_fling_torch_SpellScript::HandleAfterCast);
            if (m_scriptSpellId == SPELL_JUGGLE_TORCH_CATCH_QUEST)
                OnEffectHitTarget += SpellEffectFn(spell_midsummer_fling_torch_SpellScript::HandleScriptHitTarget, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_midsummer_fling_torch_SpellScript();
    }
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Honor the Flame! & Desecrate this Fire!
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// i have no idee how blizz have done this.. i missing good sniff..
// so i use some similar spell and objects to do as needed..
//
// Honor the Flame!         Start & End of quest on FlameKeeper
// Desecrate this Fire!     Start & End of quest on the Bonfire
//                          the fire is deleted until player other faction is enable it again, or after 30 min cooldown..
// Enable the fire with cast of Burning Blossom on self: 
//                          click on a Burning Blossom in youre bag: then cast a torch range 40 meter, 
//                          and the fire enables and you receive 10 Burning Blossom
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 187971 187973 187952 187963 187943 187950 187929 187961 187945 187959 187957 187968 187948
// 187953 187946 187970 187966 187975 187930 187969 187944 187951 187956 187954 187947 187972
// 187914 187964 187559 187965 187927 187564 187916 187920 187923 187924 187925 187926 187928
// 187931 187932 187934 187936 187938 187940 194043 187921 194037 194046 194042 187958 194044
// 194045 194034 194035 194032 194033 187922 187967 187917 187937 187939 187941 187942 187949
// 187962 187919 187933 187935 187955 187960 187974 194036 194038 194039 194040 194048 194049
class go_midsummer_bonfire : public GameObjectScript
{
public:
    go_midsummer_bonfire() : GameObjectScript("go_midsummer_bonfire") { }

    struct go_midsummer_bonfire_accessAI : public GameObjectAI
    {
        go_midsummer_bonfire_accessAI(GameObject* go) : GameObjectAI(go) { }

        EventMap m_events;
        uint64   m_bonfireDummyGUID;

        void Reset()
        {
            m_bonfireDummyGUID = 0;
            go->SetInPhase(190, true, true);
            m_events.RescheduleEvent(EVENT_INIT_TARGET, 1000);
        }

        bool GossipHello(Player* player) 
        { 
            QuestRelationBounds qr = sObjectMgr->GetGOQuestRelationBounds(go->GetEntry());
            for (QuestRelations::const_iterator itr = qr.first; itr != qr.second; ++itr)
            {
                uint32 questID = itr->second;
                const Quest* quest = sObjectMgr->GetQuestTemplate(itr->second);
                if (quest->GetTitle() == "Desecrate this Fire!")
                    if (player->GetQuestStatus(questID) == QUEST_STATUS_NONE && player->CanTakeQuest(quest, false))
                    {
                        player->AddQuest(quest, go);
                        player->PlayerTalkClass->ClearMenus();
                        player->CLOSE_GOSSIP_MENU();
                        return true;
                    }
            }
            return false; 
        }

        bool GossipSelect(Player* player, uint32 /*sender*/, uint32 /*action*/) 
        {
            if (Creature* dummy = sObjectAccessor->GetCreature(*go, m_bonfireDummyGUID))
            {
                dummy->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
                dummy->AI()->DoAction(SPELL_STAMP_OUT_BONFIRE);
            }
            return false; 
        }

        bool QuestReward(Player* player, Quest const* /*quest*/, uint32 /*opt*/) 
        { 
            player->CLOSE_GOSSIP_MENU();
            if (Creature* dummy = sObjectAccessor->GetCreature(*go, m_bonfireDummyGUID))
            {
                dummy->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
                dummy->AI()->DoAction(SPELL_STAMP_OUT_BONFIRE);
            }
            return false;
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_INIT_TARGET:
                    if (Creature* dummy = go->FindNearestCreature(16592, 1.0f))
                        if (GameObject* fire = go->SummonGameObject(181288, go->GetPositionX(), go->GetPositionY(), go->GetPositionZ(), go->GetOrientation(), 0, 0, 0, 0, 0))
                        {
                            fire->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                            m_bonfireDummyGUID = dummy->GetGUID();
                            dummy->AI()->SetGUID(go->GetGUID(), 1); // the dummy sends own guid back..
                            dummy->AI()->SetGUID(fire->GetGUID(), fire->GetEntry());
                        }
                    break;
                }
            }
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_midsummer_bonfire_accessAI(go);
    }
};

// 16592
class npc_midsummer_bonfire_16592 : public CreatureScript
{
public:
    npc_midsummer_bonfire_16592() : CreatureScript("npc_midsummer_bonfire_16592") { }

    struct npc_midsummer_bonfire_16592AI : public ScriptedAI
    {
        npc_midsummer_bonfire_16592AI(Creature* c) : ScriptedAI(c) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_bonfireGUID;
        uint64   m_fireGUID;
        std::set<uint64> pList;

        void Reset()
        {
            m_playerGUID = 0;
            m_bonfireGUID = 0;
            m_fireGUID = 0;
        };

        void SetGUID(uint64 guid, int32 id = 0)
        {
            switch (id)
            {
            case 1:
                m_bonfireGUID = guid;
                break;
            case 181288:
                m_fireGUID = guid;
                break;
            case PLAYER_GUID:
                m_playerGUID = guid;
                break;
            }
        }

        uint64 GetGUID(int32 id = 0) const 
        {
            switch (id)
            {
            case 1:
                return m_bonfireGUID;
                break;
            }
            return 0; 
        }

        void DoAction(int32 param)
        {
            switch (param)
            {
            case SPELL_LIGHT_BONFIRE:
                FireOn();
                break;
            case SPELL_STAMP_OUT_BONFIRE:
                FireOff();
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
                case EVENT_TORCH_COOLDOWN:
                    m_playerGUID = 0;
                    FireOn();
                    break;  
                case EVENT_CHECK_FIRE:
                    if (GameObject* fire = ObjectAccessor::GetGameObject(*me, m_fireGUID))
                        if (!fire->HasFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE))
                            fire->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                    break;
                }
            }
        }

        void FireOn()
        {
            m_events.ScheduleEvent(EVENT_CHECK_FIRE, 100);
            if (GameObject* bonfire = ObjectAccessor::GetGameObject(*me, m_bonfireGUID))
                if (GameObject* fire = ObjectAccessor::GetGameObject(*me, m_fireGUID))
                {
                    if (fire->IsInPhase(169))
                        return;

                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        player->AddItem(23247, 10);

                    bonfire->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                    fire->SetInPhase(169, true, true);
                }

            m_playerGUID = 0;
        }

        void FireOff()
        {
            m_events.ScheduleEvent(EVENT_CHECK_FIRE, 100);
            if (GameObject* bonfire = ObjectAccessor::GetGameObject(*me, m_bonfireGUID))
                if (GameObject* fire = ObjectAccessor::GetGameObject(*me, m_fireGUID))
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        if (!HasPlayer(player->GetGUID()))
                            if (fire->IsInPhase(169))
                            {
                                player->AddItem(23247, 10);
                                AddPlayer();
                            }

                    bonfire->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                    fire->SetInPhase(169, true, false);
                    m_events.RescheduleEvent(EVENT_TORCH_COOLDOWN, 1800 * 1000); // 30 min to set fire on
                }
        }

        void AddPlayer()
        {
            if (!HasPlayer(m_playerGUID))
                pList.insert(m_playerGUID);
        }

        bool HasPlayer(uint64 guid)
        {
            return (pList.find(guid) != pList.end());
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_midsummer_bonfire_16592AI(creature);
    }
};

// 29437
class spell_toss_fuel_on_bonfire_29437 : public SpellScriptLoader
{
public:
    spell_toss_fuel_on_bonfire_29437() : SpellScriptLoader("spell_toss_fuel_on_bonfire_29437") {}

    class spell_toss_fuel_on_bonfire_29437_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_toss_fuel_on_bonfire_29437_SpellScript);

        void CheckOnCast()
        {
            Unit* unit = GetCaster();
            if (Player* player = unit->ToPlayer())
                if (Creature* dummy = player->FindNearestCreature(16592, 40.0f))
                {
                    uint64 m_bonfireGUID = dummy->AI()->GetGUID(1);
                    dummy->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
                    dummy->AI()->DoAction(SPELL_LIGHT_BONFIRE);
                    if (GameObject* bonfire = ObjectAccessor::GetGameObject(*player, m_bonfireGUID))
                        player->CastSpell(bonfire, 45732, true); // Toss Torch
                }
        }

        void Register()
        {
            OnCast += SpellCastFn(spell_toss_fuel_on_bonfire_29437_SpellScript::CheckOnCast);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_toss_fuel_on_bonfire_29437_SpellScript();
    }
};


//  unchecked functions


enum eJuggle
{
    SPELL_JUGGLE_SELF = 45638,
    SPELL_JUGGLE_SLOW = 45792,
    SPELL_JUGGLE_MED = 45806,
    SPELL_JUGGLE_FAST = 45816,

    SPELL_TORCH_CHECK = 45644,
    SPELL_GIVE_TORCH = 45280,
    QUEST_CHECK = 11937,
};

// 45644, 45819
class spell_midsummer_juggling_torch : public SpellScriptLoader
{
public:
    spell_midsummer_juggling_torch() : SpellScriptLoader("spell_midsummer_juggling_torch") {}

    class spell_midsummer_juggling_torch_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_midsummer_juggling_torch_SpellScript);

        bool handled;
        bool Load() { handled = false; return true; }
        void HandleFinish()
        {
            Unit* caster = GetCaster();
            if (!caster || caster->GetTypeId() != TYPEID_PLAYER)
                return;

            if (const WorldLocation* loc = GetExplTargetDest())
            {
                if (loc->GetExactDist(caster) < 3.0f)
                    caster->CastSpell(loc->GetPositionX(), loc->GetPositionY(), loc->GetPositionZ(), SPELL_JUGGLE_SELF, true);
                else if (loc->GetExactDist(caster) < 10.0f)
                    caster->CastSpell(loc->GetPositionX(), loc->GetPositionY(), loc->GetPositionZ(), SPELL_JUGGLE_SLOW, true);
                else if (loc->GetExactDist(caster) < 25.0f)
                    caster->CastSpell(loc->GetPositionX(), loc->GetPositionY(), loc->GetPositionZ(), SPELL_JUGGLE_MED, true);
                else
                    caster->CastSpell(loc->GetPositionX(), loc->GetPositionY(), loc->GetPositionZ(), SPELL_JUGGLE_FAST, true);
            }
            else
                caster->CastSpell(caster, SPELL_JUGGLE_SELF, true);
        }

        void HandleDummy(SpellEffIndex effIndex)
        {
            PreventHitDefaultEffect(effIndex);
            Unit* caster = GetCaster();
            if (!caster || caster->GetTypeId() != TYPEID_PLAYER)
                return;

            if (Player* target = GetHitPlayer())
                if (!handled && target->GetQuestRewardStatus(target->GetTeamId() == TEAM_ALLIANCE ? 11657 : 11923))
                {
                    handled = true;
                    caster->CastSpell(target, SPELL_GIVE_TORCH, true);
                }
        }

        void Register()
        {
            if (m_scriptSpellId == SPELL_TORCH_CHECK)
                OnEffectHitTarget += SpellEffectFn(spell_midsummer_juggling_torch_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            else
                AfterCast += SpellCastFn(spell_midsummer_juggling_torch_SpellScript::HandleFinish);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_midsummer_juggling_torch_SpellScript();
    }
};

enum RibbonPole
{
    SPELL_RIBBON_POLE_CHANNEL_VISUAL = 29172,
    SPELL_RIBBON_POLE_XP = 29175,
    SPELL_RIBBON_POLE_FIREWORKS = 46971,

    NPC_RIBBON_POLE_DEBUG_TARGET = 17066,
};

// 45406
class spell_midsummer_ribbon_pole : public SpellScriptLoader
{
public:
    spell_midsummer_ribbon_pole() : SpellScriptLoader("spell_midsummer_ribbon_pole") { }

    class spell_midsummer_ribbon_pole_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_midsummer_ribbon_pole_AuraScript)

            void HandleEffectPeriodic(AuraEffect const * aurEff)
        {
            PreventDefaultAction();
            if (Unit *target = GetTarget())
            {
                Creature* cr = target->FindNearestCreature(NPC_RIBBON_POLE_DEBUG_TARGET, 10.0f);
                if (!cr)
                {
                    target->RemoveAura(SPELL_RIBBON_POLE_CHANNEL_VISUAL);
                    SetDuration(1);
                    return;
                }

                if (Aura* aur = target->GetAura(SPELL_RIBBON_POLE_XP))
                    aur->SetDuration(std::min(aur->GetDuration() + 3 * MINUTE*IN_MILLISECONDS, 60 * MINUTE*IN_MILLISECONDS));
                else
                    target->CastSpell(target, SPELL_RIBBON_POLE_XP, true);

                if (roll_chance_i(5))
                {
                    cr->Relocate(cr->GetPositionX(), cr->GetPositionY(), cr->GetPositionZ() - 6.5f);
                    cr->CastSpell(cr, SPELL_RIBBON_POLE_FIREWORKS, true);
                    cr->Relocate(cr->GetPositionX(), cr->GetPositionY(), cr->GetPositionZ() + 6.5f);
                }

                // Achievement
                if ((time(NULL) - GetApplyTime()) > 60 && target->GetTypeId() == TYPEID_PLAYER)
                    target->ToPlayer()->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET, 58934, 0, 0, target);
            }
        }

        void HandleEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            Unit* ar = GetTarget();
            ar->CastSpell(ar, SPELL_RIBBON_POLE_CHANNEL_VISUAL, true);
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_midsummer_ribbon_pole_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_midsummer_ribbon_pole_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_midsummer_ribbon_pole_AuraScript();
    }
};

void AddSC_event_midsummer_scripts()
{
    // NPCs
    new npc_festival_loremaster_16817();
    new npc_festival_talespinner_16818();
    new npc_summer_scorchling_26401();
    new npc_festival_scorchling_26520();
    new npc_master_fire_flame_eater();
    new npc_midsummer_bonfire_16592();
    new npc_torch_tossing_target_bunny_25535();
    new go_midsummer_bonfire();

    // Spells
    new spell_midsummer_ribbon_pole();
    new spell_midsummer_torch_quest();
    new spell_midsummer_fling_torch();
    new spell_midsummer_juggling_torch();
    new spell_toss_fuel_on_bonfire_29437();
}
