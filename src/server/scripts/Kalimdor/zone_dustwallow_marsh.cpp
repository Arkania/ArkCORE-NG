/*
* Copyright (C) 2011-2017 ArkCORE <http://www.arkania.net/>
* Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
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

#include "script_helper.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "ScriptedGossip.h"
#include "SpellScript.h"
#include "Player.h"
#include "WorldSession.h"

 // 4968
class npc_lady_jaina_proudmoore_4968 : public CreatureScript
{
public:
    npc_lady_jaina_proudmoore_4968() : CreatureScript("npc_lady_jaina_proudmoore_4968") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        if (action == 1)
        {
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -8390.0f, 265.0f, 155.35f, 5.367f);
            return true;
        }
        return false;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        switch (quest->GetQuestId())
        {
        case 27239:
        {
            creature->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
            creature->AI()->DoAction(1);
            break;
        }
        }

        return false;
    }

    struct npc_lady_jaina_proudmoore_4968AI : public ScriptedAI
    {
        npc_lady_jaina_proudmoore_4968AI(Creature* creature) : ScriptedAI(creature) {  }

        enum eJaina
        {
            eBlizzIni = 950,
            eBlastIni,
            eBallIni,
            eTeleIni,
            eSummIni,
            eBlizzCD,
            eBlastCD,
            eBallCD,
            eTeleCD,
            eSummCD,
        };

        EventMap m_events;
        bool m_blizzINI, m_blastINI, m_ballINI, m_teleINI, m_summINI;
        bool m_blizzCD, m_blastCD, m_ballCD, m_teleCD, m_summCD;
        uint32 m_IsMoving; /* 0=no, 1=home 2=chase 3=flee */
        uint64 m_targetChase;
        uint64 m_targetFlee;
        std::set<uint64> pList;
        uint64 m_playerGUID;
        bool   m_talk;

        void Reset() override
        {
            m_playerGUID = 0;
            m_talk = false;
            m_targetChase = 0;
            m_targetFlee = 0;
            m_blizzCD = true; m_blastCD = true; m_ballCD = true; m_teleCD = true; m_summCD = true;
            m_blizzINI = false; m_blastINI = false; m_ballINI = false; m_teleINI = false; m_summINI = false;
            m_events.RescheduleEvent(eBlizzIni, urand(4000, 5000));
            m_events.RescheduleEvent(eBlastIni, urand(4000, 5000));
            m_events.RescheduleEvent(eBallIni, urand(4000, 5000));
            m_events.RescheduleEvent(eTeleIni, urand(4000, 5000));
            m_events.RescheduleEvent(eSummIni, urand(4000, 5000));
            StopMoving();
        }

        void AddPlayer()
        {
            if (!HasPlayer())
                pList.insert(m_playerGUID);
        }

        bool HasPlayer()
        {
            return (pList.find(m_playerGUID) != pList.end());
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case PLAYER_GUID:
            {
                m_playerGUID = guid;
                break;
            }
            }
        }

        Player* GetPlayer()
        {
            return ObjectAccessor::GetPlayer(*me, m_playerGUID);
        }

        void EnterCombat(Unit* victim) override
        {
            float dist = me->GetDistance(victim);
            if (dist > 30.0f)
                CastBall(victim);
            if (dist > 20.0f)
                CastBlizz(victim);
            if (dist > 5.0f)
            {
                CastBlast(victim);
                StopMoving();
            }
            else
            {
                StartMovingFlee(victim);
                DoMeleeAttackIfReady();
            }
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            float m_healthPct = me->GetHealthPct();
            float m_manaPct = (100.0f / me->GetMaxPower(POWER_MANA)) * me->GetPower(POWER_MANA);
            float dist = me->GetDistance(attacker);

            if (m_manaPct < 15.0f)
                StartMovingFlee(attacker);
            else if (dist < 5.0f)
            {
                CastBlast(attacker);
                StartMovingFlee(attacker);
            }
            else if (m_manaPct > 30.0f)
            {
                StopMoving();
                if (dist > 30.0f)
                    CastBall(attacker);
                if (dist > 20.0f)
                    CastBlizz(attacker);
                if (dist > 5.0f)
                    CastBlast(attacker);
                if (m_healthPct < 50.0f)
                    CastTele(attacker);
                if (m_manaPct < 30.0f)
                    CastSumm(attacker);
            }
        }

        void EnterEvadeMode() override
        {
            StartMovingHome();
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case 1:
            {
                if (!m_talk && !HasPlayer())
                {
                    m_events.RescheduleEvent(EVENT_TALK_PART_00, 2000);
                    m_talk = true;
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
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
                case eBlizzIni:
                    m_blizzINI = true;
                    break;
                case eBlastIni:
                    m_blastINI = true;
                case eBallIni:
                    m_ballINI = true;
                case eTeleIni:
                    m_teleINI = true;
                case eSummIni:
                    m_summINI = true;
                case  eBlizzCD:
                    m_blizzCD = true;
                    m_events.ScheduleEvent(eBlizzIni, urand(4000, 5000));
                    break;
                case eBlastCD:
                    m_blastCD = true;
                    m_events.ScheduleEvent(eBlastIni, urand(4000, 5000));
                    break;
                case eBallCD:
                    m_ballCD = true;
                    m_events.ScheduleEvent(eBallIni, urand(4000, 5000));
                    break;
                case eTeleCD:
                    m_teleCD = true;
                    m_events.ScheduleEvent(eTeleIni, urand(4000, 5000));
                    break;
                case eSummCD:
                    m_summCD = true;
                    m_events.ScheduleEvent(eSummIni, urand(4000, 5000));
                    break;
                case EVENT_TALK_PART_00:
                {
                    if (Player* player = GetPlayer())
                        Talk(1, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_01, 5000);
                    break;
                }
                case EVENT_TALK_PART_01:
                {
                    if (Player* player = GetPlayer())
                        Talk(2, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_02, 5000);
                    break;
                }
                case EVENT_TALK_PART_02:
                {
                    if (Player* player = GetPlayer())
                        Talk(3, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_03, 5000);
                    break;
                }
                case EVENT_TALK_PART_03:
                {
                    if (Player* player = GetPlayer())
                        Talk(4, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_04, 5000);
                    break;
                }
                case EVENT_TALK_PART_04:
                {
                    if (Player* player = GetPlayer())
                        Talk(5, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_05, 5000);
                    break;
                }
                case EVENT_TALK_PART_05:
                {
                    if (Player* player = GetPlayer())
                        Talk(6, player);
                    m_events.ScheduleEvent(EVENT_TALK_PART_06, 5000);
                    break;
                }
                case EVENT_TALK_PART_06:
                {
                    m_talk = false;
                    AddPlayer();
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void CastBlizz(Unit* target)
        {
            if (m_blizzCD && m_blizzINI)
            {
                me->CastSpell(target, 20680, true);
                m_blizzCD = false; m_blizzINI = false;
                m_events.ScheduleEvent(eBlizzCD, urand(25000, 28000));
            }
        }
        void CastBlast(Unit* target)
        {
            if (m_blastCD && m_blastINI)
            {
                me->CastSpell(target, 20679, true);
                m_blastCD = false; m_blastINI = false;
                m_events.ScheduleEvent(eBlastCD, urand(15000, 17000));
            }
        }
        void CastBall(Unit* target)
        {
            if (m_ballCD && m_ballINI)
            {
                me->CastSpell(target, 20692, true);
                m_ballCD = false; m_ballINI = false;
                m_events.ScheduleEvent(eBallCD, urand(3400, 4700));
            }
        }
        void CastTele(Unit* target)
        {
            if (m_teleCD && m_teleINI)
            {
                target->CastSpell(target, 20682, true);
                m_teleCD = false; m_teleINI = false;
                m_events.ScheduleEvent(eTeleCD, urand(14000, 21000));
            }
        }
        void CastSumm(Unit* target)
        {
            if (m_summCD && m_summINI)
            {
                me->CastSpell(target, 20681, true);
                m_summCD = false; m_summINI = false;
                m_events.ScheduleEvent(eSummCD, urand(45000, 55000));
            }
        }
        void StopMoving()
        {
            if (m_IsMoving > 0)
            {
                me->GetMotionMaster()->MoveIdle();
                m_targetFlee = 0;
                m_targetChase = 0;
                m_IsMoving = 0;
            }
        }
        void StartMovingHome()
        {
            if (m_IsMoving != 1)
            {
                me->GetMotionMaster()->MoveTargetedHome();
                m_targetFlee = 0;
                m_targetChase = 0;
                m_IsMoving = 1;
            }
        }
        void StartMovingChase(Unit* target)
        {
            if (m_IsMoving != 2 || m_targetChase != target->GetGUID())
            {
                me->GetMotionMaster()->MoveChase(target, 5.0f);
                m_targetFlee = 0;
                m_targetChase = target->GetGUID();
                m_IsMoving = 2;
            }
        }
        void StartMovingFlee(Unit* target)
        {
            if (m_IsMoving != 3 || m_targetFlee != target->GetGUID())
            {
                me->GetMotionMaster()->MoveFleeing(target);
                m_targetFlee = target->GetGUID();
                m_targetChase = 0;
                m_IsMoving = 3;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_lady_jaina_proudmoore_4968AI(creature);
    }
};

// 23704
class npc_cassa_crimsonwing_23704 : public CreatureScript
{
public:
    npc_cassa_crimsonwing_23704() : CreatureScript("npc_cassa_crimsonwing_23704") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == 1)
        {
            player->CLOSE_GOSSIP_MENU();
            player->CastSpell(player, 42295, true);
            return true;
        }
        return false;
    }
};

// 23864
class npc_zelfrax_23864 : public CreatureScript
{
public:
    npc_zelfrax_23864() : CreatureScript("npc_zelfrax_23864") { }

    enum Zelfrax
    {
        SAY_ZELFRAX1 = 0,
        SAY_ZELFRAX2 = 1
    };

    struct npc_zelfrax_23864AI : public ScriptedAI
    {
        npc_zelfrax_23864AI(Creature* creature) : ScriptedAI(creature)
        {
            MoveToDock();
        }

        void AttackStart(Unit* who) override
        {
            if (!who)
                return;

            if (me->Attack(who, true))
            {
                me->SetInCombatWith(who);
                who->SetInCombatWith(me);

                if (IsCombatMovementAllowed())
                    me->GetMotionMaster()->MoveChase(who);
            }
        }

        void MovementInform(uint32 Type, uint32 /*Id*/) override
        {
            if (Type != POINT_MOTION_TYPE)
                return;

            me->SetHomePosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            SetCombatMovement(true);

            if (me->IsInCombat())
                if (Unit* unit = me->GetVictim())
                    me->GetMotionMaster()->MoveChase(unit);
        }

        void MoveToDock()
        {
            SetCombatMovement(false);
            me->GetMotionMaster()->MovePoint(0, -2967.030f, -3872.1799f, 35.620f);
            Talk(SAY_ZELFRAX1);
            Talk(SAY_ZELFRAX2);
        }

        void UpdateAI(uint32 /*Diff*/) override
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_zelfrax_23864AI(creature);
    }
};

// 42485
class spell_ooze_zap : public SpellScriptLoader
{
public:
    spell_ooze_zap() : SpellScriptLoader("spell_ooze_zap") { }

    enum SpellScripts
    {
        SPELL_OOZE_ZAP = 42489,
    };

    class spell_ooze_zap_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ooze_zap_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_OOZE_ZAP))
                return false;
            return true;
        }

        SpellCastResult CheckRequirement()
        {
            if (!GetCaster()->HasAura(GetSpellInfo()->Effects[EFFECT_1].CalcValue()))
                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW; // This is actually correct

            if (!GetExplTargetUnit())
                return SPELL_FAILED_BAD_TARGETS;

            return SPELL_CAST_OK;
        }

        void HandleDummy(SpellEffIndex effIndex)
        {
            PreventHitDefaultEffect(effIndex);
            if (GetHitUnit())
                GetCaster()->CastSpell(GetHitUnit(), uint32(GetEffectValue()), true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_ooze_zap_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            OnCheckCast += SpellCheckCastFn(spell_ooze_zap_SpellScript::CheckRequirement);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_ooze_zap_SpellScript();
    }
};

// 42489
class spell_ooze_zap_channel_end : public SpellScriptLoader
{
public:
    spell_ooze_zap_channel_end() : SpellScriptLoader("spell_ooze_zap_channel_end") { }

    enum SpellScripts
    {
        SPELL_OOZE_ZAP_CHANNEL_END = 42485,
        SPELL_OOZE_CHANNEL_CREDIT = 42486,
    };

    class spell_ooze_zap_channel_end_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ooze_zap_channel_end_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_OOZE_ZAP_CHANNEL_END))
                return false;
            return true;
        }

        void HandleDummy(SpellEffIndex effIndex)
        {
            PreventHitDefaultEffect(effIndex);
            if (Player* player = GetCaster()->ToPlayer())
                player->CastSpell(player, SPELL_OOZE_CHANNEL_CREDIT, true);
            GetHitUnit()->Kill(GetHitUnit());
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_ooze_zap_channel_end_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_ooze_zap_channel_end_SpellScript();
    }
};

// 42492
class spell_energize_aoe : public SpellScriptLoader
{
public:
    spell_energize_aoe() : SpellScriptLoader("spell_energize_aoe") { }

    enum SpellScripts
    {
        SPELL_ENERGIZED = 42492,
    };

    class spell_energize_aoe_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_energize_aoe_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_ENERGIZED))
                return false;
            return true;
        }

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            for (std::list<WorldObject*>::iterator itr = targets.begin(); itr != targets.end();)
            {
                if ((*itr)->GetTypeId() == TYPEID_PLAYER && (*itr)->ToPlayer()->GetQuestStatus(GetSpellInfo()->Effects[EFFECT_1].CalcValue()) == QUEST_STATUS_INCOMPLETE)
                    ++itr;
                else
                    targets.erase(itr++);
            }
            targets.push_back(GetCaster());
        }

        void HandleScript(SpellEffIndex effIndex)
        {
            PreventHitDefaultEffect(effIndex);
            GetCaster()->CastSpell(GetCaster(), uint32(GetEffectValue()), true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_energize_aoe_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_energize_aoe_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_energize_aoe_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_energize_aoe_SpellScript();
    }
};

// 186287
class go_blackhoof_cage_186287 : public GameObjectScript
{
public:
    go_blackhoof_cage_186287() : GameObjectScript("go_blackhoof_cage_186287") { }

    enum PrisonersOfTheGrimTotems
    {
        NPC_THERAMORE_PRISONER = 23720,
        SAY_FREE = 0,
    };

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        go->UseDoorOrButton();
        if (Creature* prisoner = go->FindNearestCreature(NPC_THERAMORE_PRISONER, 1.0f))
        {
            if (player)
                player->KilledMonsterCredit(NPC_THERAMORE_PRISONER, 0);

            prisoner->AI()->Talk(SAY_FREE); // We also emote cry here (handled in creature_text.emote)
            prisoner->DespawnOrUnsummon(6000);
        }
        return true;
    }
};

void AddSC_dustwallow_marsh()
{
    new npc_lady_jaina_proudmoore_4968();
    new npc_cassa_crimsonwing_23704();
    new npc_zelfrax_23864();
    new spell_ooze_zap();
    new spell_ooze_zap_channel_end();
    new spell_energize_aoe();
    new go_blackhoof_cage_186287();
}
