/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2017 ArkCORE <http://www.arkania.net/>
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
SDName: Gnomeregan
SD%Complete: 0
SDComment: Quest Support:
SDCategory: Gnomeregan
EndScriptData */


#include "script_helper.h"
#include "Creature.h"
#include "GameObjectAI.h"
#include "GameObject.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "ScriptedGossip.h"
#include "Vehicle.h"
#include "MovementGenerator.h"
#include "TargetedMovementGenerator.h"

// 45847
class npc_safe_operative_45847 : public CreatureScript
{
public:
    npc_safe_operative_45847() : CreatureScript("npc_safe_operative_45847") { }

    struct npc_safe_operative_45847AI : public ScriptedAI
    {
        npc_safe_operative_45847AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        FakeAttackMembers m_fakeAttack;

        void Initialize()
        {
            m_fakeAttack = FakeAttackMembers(me);
        }

        void Reset() override
        {
            me->GetMotionMaster()->MoveIdle();
            me->SetReactState(REACT_DEFENSIVE);
            m_events.RescheduleEvent(EVENT_CHECK_FOR_CREATURE, 1000);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override 
        { 
            if (m_fakeAttack.IsSparringPartner(attacker))
                damage = 0;
        }

        void AttackStart(Unit* who) override
        {
            if (m_fakeAttack.IsSparringPartner(who))
                AttackStartNoMove(who);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            if (!m_fakeAttack.m_hasInit)
            {
                std::list<uint32> sList;
                sList.push_back(46391);
                m_fakeAttack.Initialize(sList);
            }

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_FOR_CREATURE:
                {
                    if (Creature* creature = m_fakeAttack.GetSparringPartner())
                    {
                        if (!me->IsInCombat())
                            me->Attack(creature, true);
                    }
                    else if (Creature* creature = m_fakeAttack.GetRangedPartner())
                    {
                        me->SetFacingToObject(creature);
                        if (uint32 spellId = m_fakeAttack.GetRangedSpellId())
                            me->CastSpell(creature, spellId, true);
                        me->GetMotionMaster()->MoveIdle();
                    }

                    m_events.ScheduleEvent(EVENT_CHECK_FOR_CREATURE, urand(900, 1200));
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_safe_operative_45847AI(creature);
    }
};

// 46391
class npc_crazed_leper_gnome_46391 : public CreatureScript
{
public:
    npc_crazed_leper_gnome_46391() : CreatureScript("npc_crazed_leper_gnome_46391") { }

    struct npc_crazed_leper_gnome_46391AI : public ScriptedAI
    {
        npc_crazed_leper_gnome_46391AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        FakeAttackMembers m_fakeAttack;

        void Initialize()
        {
            m_fakeAttack = FakeAttackMembers(me);
        }

        void Reset() override
        {
            me->GetMotionMaster()->MoveIdle();
            me->SetReactState(REACT_DEFENSIVE);
            m_events.RescheduleEvent(EVENT_CHECK_FOR_CREATURE, 1000);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (m_fakeAttack.IsSparringPartner(attacker))
                damage = 0;
        }

        void AttackStart(Unit* who) override
        {
            if (m_fakeAttack.IsSparringPartner(who))
                AttackStartNoMove(who);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            if (!m_fakeAttack.m_hasInit)
            {
                std::list<uint32> sList;
                sList.push_back(45847);
                m_fakeAttack.Initialize(sList);
            }

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_FOR_CREATURE:
                {
                    if (Creature* creature = m_fakeAttack.GetSparringPartner())
                    {
                        if (!me->IsInCombat())
                            me->Attack(creature, true);
                    }

                    m_events.ScheduleEvent(EVENT_CHECK_FOR_CREATURE, urand(900, 1200));
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_crazed_leper_gnome_46391AI(creature);
    }
};

// 42501
class npc_wounded_infantry_42501 : public CreatureScript
{
public:
    npc_wounded_infantry_42501() : CreatureScript("npc_wounded_infantry_42501") { }

    enum Dun_Morogh
    {
        //support quest 24533
        QUEST_ARTS_OF_A_PRIEST_26200 = 26200,
        //credt NPC
        NPC_HEALING_CREDIT_42501 = 42501
    };

    struct npc_wounded_infantry_42501AI : public ScriptedAI
    {
        npc_wounded_infantry_42501AI(Creature* creature) : ScriptedAI(creature) { }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (Player* player = caster->ToPlayer())
                if (player->GetQuestStatus(QUEST_ARTS_OF_A_PRIEST_26200) == QUEST_STATUS_INCOMPLETE)
                    player->KilledMonsterCredit(NPC_HEALING_CREDIT_42501);// New NPC ID
            me->DespawnOrUnsummon(500);
        }

        void EnterCombat(Unit* /*who*/) override { }

        void MoveInLineOfSight(Unit* /*who*/) override { }

        void UpdateAI(uint32 /*diff*/) override { }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_wounded_infantry_42501AI(creature);
    }
};

// 45966
class npc_nevin_twistwrench_45966 : public CreatureScript
{
public:
    npc_nevin_twistwrench_45966() : CreatureScript("npc_nevin_twistwrench_45966") { }

    enum eNpc
    {
        SPELL_IRRADIATE = 80653,
        QUEST_DECONTAMINATION = 27635
    };

    struct npc_nevin_twistwrench_45966AI : public ScriptedAI
    {
        npc_nevin_twistwrench_45966AI(Creature* creature) : ScriptedAI(creature) { }

        uint32 uiTimer;

        void Reset() override
        {
            uiTimer = 0;
        }

        void UpdateAI(uint32 diff) override
        {
            if (uiTimer <= diff)
            {
                std::list<Player*> playerList = me->FindNearestPlayers(10.0f, true);
                for (std::list<Player*>::const_iterator itr = playerList.begin(); itr != playerList.end(); ++itr)
                    if (((*itr)->GetQuestStatus(QUEST_DECONTAMINATION) == QUEST_STATUS_NONE) && (!(*itr)->HasAura(SPELL_IRRADIATE)))
                        (*itr)->CastSpell((*itr), SPELL_IRRADIATE, true);

                uiTimer = 100;
            }
            else uiTimer -= diff;
        }

    };

    CreatureAI *GetAI(Creature *Creature) const
    {
        return new npc_nevin_twistwrench_45966AI(Creature);
    }

};

// 47250
class npc_carvo_blastbolt_47250 : public CreatureScript
{
public:
    npc_carvo_blastbolt_47250() : CreatureScript("npc_carvo_blastbolt_47250") { }

    enum eNpc
    {
        QUEST_WITHDRAW_TO_THE_LOADING_ROOM = 28169,
        NPC_IMUN_AGENT = 47836,
        MOVE_IMUN_AGENT = 4783600
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_WITHDRAW_TO_THE_LOADING_ROOM)
        {
            player->SummonCreature(NPC_IMUN_AGENT, -4981.25f, 780.992f, 288.485f, 3.316f, TEMPSUMMON_MANUAL_DESPAWN, 0);
            if (Creature* agent = creature->FindNearestCreature(NPC_IMUN_AGENT, 5.0f))
            {
                agent->SetSpeed(MOVE_RUN, 1.0f);
                agent->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_NOT_SELECTABLE);
                agent->SetReactState(REACT_PASSIVE);
                agent->AI()->Talk(0, player);
                agent->GetMotionMaster()->MovePath(MOVE_IMUN_AGENT, false);
            }
        }

        return true;
    }
};

// 46185
class npc_sanitron_500_46185 : public CreatureScript
{
public:
    npc_sanitron_500_46185() : CreatureScript("npc_sanitron_500_46185") { }

    enum eNpc
    {

        SPELL_CANNON_BURST = 86080,
        SPELL_DECONTAMINATE_STAGE_1 = 86075,
        SPELL_DECONTAMINATE_STAGE_2 = 86086,
        SPELL_IRRADIATE = 80653,

        SPELL_EXPLOSION = 30934,

        QUEST_DECONTAMINATION = 27635,

        NPC_DECONTAMINATION_BUNNY = 46165,
        NPC_CLEAN_CANNON = 46208,
        NPC_SAFE_TECHNICAN = 46230
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_DECONTAMINATION) == QUEST_STATUS_INCOMPLETE)
        {
            player->HandleEmoteCommand(0);
            Vehicle *vehicle = creature->GetVehicleKit();
            player->EnterVehicle(creature->ToUnit(), 0);
            creature->AI()->Talk(0);
        }
        return true;
    }

    struct npc_sanitron_500_46185AI : public ScriptedAI
    {
        npc_sanitron_500_46185AI(Creature* pCreature) : ScriptedAI(pCreature), vehicle(pCreature->GetVehicleKit())
        {
            assert(vehicle);
        }

        Vehicle *vehicle;
        Creature* Technician;
        Creature::Unit* Bunny[4];
        Creature::Unit* Cannon[4];
        std::list<Unit*> targets;
        uint32 uiTimer;
        uint32 uiRespawnTimer;
        uint8 uiPhase;

        void Reset() override
        {
            uiTimer = 0;
            uiRespawnTimer = 6000;
            uiPhase = 0;
        }

        Unit* unit(uint32 entry, uint32 range, bool alive)
        {
            if (Unit* unit = me->FindNearestCreature(entry, float(range), alive))
                if (Unit* unit2 = sObjectAccessor->GetCreature(*me, unit->GetGUID()))
                    return unit2;
        }

        void GetTargets()
        {
            std::list<Creature*> targets = me->FindAllCreaturesInRange(100.0f);
            if (!targets.empty())
                for (std::list<Creature*>::const_iterator iter = targets.begin(); iter != targets.end(); ++iter)
                {
                    if ((*iter)->GetTypeId() != TYPEID_PLAYER)
                    {
                        switch ((*iter)->GetEntry())
                        {
                        case 46230:
                            if ((*iter)->GetDistance2d(-5165.209961f, 713.809021f) <= 1)
                                Technician = (*iter);
                            break;
                        case 46165:
                            if ((*iter)->GetDistance2d(-5164.919922f, 723.890991f) <= 1)
                                Bunny[0] = (*iter);
                            if ((*iter)->GetDistance2d(-5182.560059f, 726.656982f) <= 1)
                                Bunny[1] = (*iter);
                            if ((*iter)->GetDistance2d(-5166.350098f, 706.336975f) <= 1)
                                Bunny[2] = (*iter);
                            if ((*iter)->GetDistance2d(-5184.040039f, 708.405029f) <= 1)
                                Bunny[3] = (*iter);
                            break;
                        case 46208:
                            if ((*iter)->GetDistance2d(-5164.209961f, 719.267029f) <= 1)
                                Cannon[0] = (*iter);
                            if ((*iter)->GetDistance2d(-5165.000000f, 709.453979f) <= 1)
                                Cannon[1] = (*iter);
                            if ((*iter)->GetDistance2d(-5183.830078f, 722.093994f) <= 1)
                                Cannon[2] = (*iter);
                            if ((*iter)->GetDistance2d(-5184.470215f, 712.554993f) <= 1)
                                Cannon[3] = (*iter);
                            break;
                        }
                    }
                }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!vehicle->HasEmptySeat(0))
                if (uiTimer <= diff)
                {
                    if (Player* player = vehicle->GetPassenger(0)->ToPlayer())
                    {
                        switch (uiPhase)
                        {
                        case 0:
                            ++uiPhase;
                            uiTimer = 2500;
                            break;
                        case 1:
                            me->GetMotionMaster()->MovePoint(1, -5173.34f, 730.11f, 294.25f);
                            GetTargets();
                            ++uiPhase;
                            uiTimer = 3000;
                            break;
                        case 2:
                            if (Bunny[0] && Bunny[1])
                            {
                                Bunny[0]->CastSpell(player, SPELL_DECONTAMINATE_STAGE_1, true);
                                Bunny[1]->CastSpell(player, SPELL_DECONTAMINATE_STAGE_1, true);
                            }
                            ++uiPhase;
                            uiTimer = 1500;
                            break;
                        case 3:
                            me->GetMotionMaster()->MovePoint(2, -5173.72f, 725.7f, 294.03f);
                            ++uiPhase;
                            uiTimer = 500;
                            break;
                        case 4:
                            me->GetMotionMaster()->MovePoint(3, -5174.57f, 716.45f, 289.53f);
                            ++uiPhase;
                            uiTimer = 3000;
                            break;
                        case 5:
                            if (Cannon[0] && Cannon[1] && Cannon[2] && Cannon[3])
                            {
                                Cannon[0]->CastSpell(player, SPELL_CANNON_BURST, true);
                                Cannon[1]->CastSpell(player, SPELL_CANNON_BURST, true);
                                Cannon[2]->CastSpell(player, SPELL_CANNON_BURST, true);
                                Cannon[3]->CastSpell(player, SPELL_CANNON_BURST, true);
                            }
                            ++uiPhase;
                            uiTimer = 4000;
                            break;
                        case 6:
                            if (Technician)
                                Technician->AI()->Talk(0);
                            me->GetMotionMaster()->MovePoint(4, -5175.04f, 707.2f, 294.4f);
                            ++uiPhase;
                            uiTimer = 4000;
                            break;
                        case 7:
                            if (Bunny[2] && Bunny[3])
                            {
                                Bunny[2]->CastSpell(player, SPELL_DECONTAMINATE_STAGE_2, true);
                                Bunny[3]->CastSpell(player, SPELL_DECONTAMINATE_STAGE_2, true);
                            }
                            player->RemoveAurasDueToSpell(SPELL_IRRADIATE);
                            ++uiPhase;
                            uiTimer = 1000;
                            break;
                        case 8:
                            player->CompleteQuest(QUEST_DECONTAMINATION);
                            Talk(1);
                            me->GetMotionMaster()->MovePoint(5, -5175.61f, 700.38f, 290.89f);
                            ++uiPhase;
                            uiTimer = 3000;
                            break;
                        case 9:
                            Talk(2);
                            me->CastSpell(me, SPELL_EXPLOSION);
                            ++uiPhase;
                            uiTimer = 1000;
                            break;
                        case 10:
                            vehicle->RemoveAllPassengers();
                            me->SetDeathState(JUST_DIED);
                            ++uiPhase;
                            uiTimer = 0;
                            break;
                        }
                    }

                }
                else uiTimer -= diff;
        }
    };

    CreatureAI *GetAI(Creature *creature) const
    {
        return new npc_sanitron_500_46185AI(creature);
    }

};

// 46293
class npc_gnomeregan_torben_46293 : public CreatureScript
{
public:
    npc_gnomeregan_torben_46293() : CreatureScript("npc_gnomeregan_torben_46293") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->ADD_GOSSIP_ITEM_DB(12104, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF + 1)
        {
            player->TeleportTo(0, -5201.58f, 477.98f, 388.47f, 5.13f);
            player->PlayerTalkClass->SendCloseGossip();
        }
        return true;
    }
};

// 42317
class npc_mekka_torque_42317 : public CreatureScript
{
public:
    npc_mekka_torque_42317() : CreatureScript("npc_mekka_torque_42317") {}

    enum eNpc
    {
        QUEST_THE_FIGHT_CONTINUES = 26208,
        SPELL_GNOMEREGAN_RECAP_CREDIT = 79227,
        SPELL_TELEPORT = 86264,
        SPELL_DETONATION = 65429,
        HOLO_MEKKA_TORQUE = 42419,
        HOLO_BRAG_BOT = 42423,
        HOLO_IRRADIATOR = 42452,
        HOLO_HINKLES = 42422,
        HOLO_COGSPIN = 42420,
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());

        return true;
    }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_THE_FIGHT_CONTINUES && !CAST_AI(npc_mekka_torque_42317::npc_mekka_torque_42317AI, creature->AI())->questStart)
        {
            CAST_AI(npc_mekka_torque_42317::npc_mekka_torque_42317AI, creature->AI())->startQuest();
        }

        return true;
    }

    struct npc_mekka_torque_42317AI : public ScriptedAI
    {
        npc_mekka_torque_42317AI(Creature *creature) : ScriptedAI(creature) {}

        bool questStart;
        uint32 timer;
        uint8 aktion;
        Creature* mekkaTorque;
        Creature* bragBot;
        Creature* irradiator;
        Creature* hinkles;
        Creature* cogspin;
        GameObject* go;


        void Reset() override
        {
            questStart = false;
            timer = 0;
            aktion = 0;
        }

        void startQuest()
        {
            questStart = true;
            aktion = 0;
            timer = 4000;
        }

        void QuestComplete()
        {
            std::list<Player*> players = me->FindNearestPlayers(35.0f, true);

            for (std::list<Player*>::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                if ((*itr)->GetQuestStatus(QUEST_THE_FIGHT_CONTINUES) == QUEST_STATUS_INCOMPLETE)
                    (*itr)->CastSpell((*itr), SPELL_GNOMEREGAN_RECAP_CREDIT, true);
        }

        void UpdateAI(uint32 diff) override
        {
            if (timer <= diff)
            {
                if (questStart)
                {
                    switch (aktion)
                    {
                    case 0:
                        me->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
                        me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                        Talk(0);
                        ++aktion;
                        timer = 1000;
                        break;
                    case 1:
                        me->GetMotionMaster()->MovePoint(1, -5133.279f, 491.546f, 395.5456f);
                        ++aktion;
                        timer = 7500;
                        break;
                    case 2:
                        go = me->SummonGameObject(203862, -5133.611f, 494.835f, 396.451f, 0, 0, 0, 0, 0, 0);
                        irradiator = me->SummonCreature(HOLO_IRRADIATOR, -5132.447f, 493.8725f, 396.4518f, 5.73f, TEMPSUMMON_MANUAL_DESPAWN);
                        irradiator->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_UNK1);
                        irradiator->SetObjectScale(0.1f);
                        ++aktion;
                        timer = 2500;
                        break;
                    case 3:
                        Talk(1);
                        mekkaTorque = me->SummonCreature(HOLO_MEKKA_TORQUE, -5134.807f, 495.452f, 396.4518f, 5.678f, TEMPSUMMON_MANUAL_DESPAWN);
                        hinkles = me->SummonCreature(HOLO_HINKLES, -5134.548f, 496.269f, 396.4518f, 5.678f, TEMPSUMMON_MANUAL_DESPAWN);
                        cogspin = me->SummonCreature(HOLO_COGSPIN, -5135.389f, 494.903f, 396.4518f, 5.678f, TEMPSUMMON_MANUAL_DESPAWN);
                        irradiator->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_UNK1);
                        ++aktion;
                        timer = 6000;
                        break;
                    case 4:
                        mekkaTorque->AI()->Talk(0);
                        ++aktion;
                        timer = 10000;
                        break;
                    case 5:
                        bragBot = me->SummonCreature(HOLO_BRAG_BOT, -5133.817f, 494.796f, 396.4518f, 2.605f, TEMPSUMMON_MANUAL_DESPAWN);
                        ++aktion;
                        timer = 2000;
                        break;
                    case 6:
                        bragBot->AI()->Talk(0);
                        ++aktion;
                        timer = 6000;
                        break;
                    case 7:
                        bragBot->AI()->Talk(1);
                        ++aktion;
                        timer = 6000;
                        break;
                    case 8:
                        bragBot->AI()->Talk(2);
                        ++aktion;
                        timer = 3000;
                        break;
                    case 9:
                        mekkaTorque->AI()->Talk(1);
                        ++aktion;
                        timer = 6000;
                        break;
                    case 10:
                        irradiator->AI()->Talk(0);
                        ++aktion;
                        timer = 12000;
                        break;
                    case 11:
                        mekkaTorque->AI()->Talk(2);
                        ++aktion;
                        timer = 6000;
                        break;
                    case 12:
                        mekkaTorque->AI()->Talk(3);
                        ++aktion;
                        timer = 10000;
                        break;
                    case 13:
                        bragBot->AI()->Talk(3);
                        ++aktion;
                        timer = 7000;
                        break;
                    case 14:
                        irradiator->AI()->Talk(1);
                        ++aktion;
                        timer = 5000;
                        break;
                    case 15:
                        mekkaTorque->AI()->Talk(4);
                        ++aktion;
                        timer = 4000;
                        break;
                    case 16:
                        mekkaTorque->CastSpell(mekkaTorque, SPELL_TELEPORT);
                        hinkles->CastSpell(hinkles, SPELL_TELEPORT);
                        cogspin->CastSpell(cogspin, SPELL_TELEPORT);
                        ++aktion;
                        timer = 2000;
                        break;
                    case 17:
                        mekkaTorque->DespawnOrUnsummon(0);
                        hinkles->DespawnOrUnsummon(0);
                        cogspin->DespawnOrUnsummon(0);
                        ++aktion;
                        timer = 1000;
                        break;
                    case 18:
                        irradiator->CastSpell(irradiator, SPELL_DETONATION);
                        ++aktion;
                        timer = 1000;
                        break;
                    case 19:
                        Talk(2);
                        ++aktion;
                        timer = 1000;
                        break;
                    case 20:
                        irradiator->DespawnOrUnsummon(0);
                        bragBot->DespawnOrUnsummon(0);
                        ++aktion;
                        timer = 1000;
                        break;
                    case 21:
                        go->Delete();
                        QuestComplete();
                        me->GetMotionMaster()->MovePoint(2, me->GetHomePosition());
                        me->GetMotionMaster()->MoveIdle();
                        questStart = false;
                        aktion = 0;
                        timer = 10000;
                        break;
                    }
                }
                else
                    timer = 10000;
            }
            else
                timer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_mekka_torque_42317AI(creature);
    }
};

// 42563
class npc_toxic_pool_42563 : public CreatureScript
{
public:
    npc_toxic_pool_42563() : CreatureScript("npc_toxic_pool_42563") { }

    enum eObject
    {
        SPELL_TOXIC_ERUPTION = 79391,
        OBJECT_TOXIC_POOL = 203975,
    };

    struct npc_toxic_pool_42563AI : public ScriptedAI
    {
        npc_toxic_pool_42563AI(Creature* creature) : ScriptedAI(creature) { }

        uint32 uiTimer;

        void Reset() override
        {
            uiTimer = 0;
        }

        void UpdateAI(uint32 diff) override
        {
            if (uiTimer <= diff)
            {
                GameObject* pool = me->FindNearestGameObject(OBJECT_TOXIC_POOL, 2.0f);
                if (pool)
                    me->CastSpell(me, SPELL_TOXIC_ERUPTION);

                uiTimer = urand(10000, 25000);
            }
            else
                uiTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_toxic_pool_42563AI(creature);
    }
};

// 42553
class npc_engineer_grindspark_42553 : public CreatureScript
{
public:
    npc_engineer_grindspark_42553() : CreatureScript("npc_engineer_grindspark_42553") { }

    enum eNpc
    {
        QUEST_A_JOB_FOR_THE_MULTI_BOT = 26205,
        SPELL_FORCECAST_SUMMON_MULTI_BOT = 79419,
        SAY_MULTIBOT_0 = 0,
        SAY_MULTIBOT_1 = 1,
        SAY_MULTIBOT_2 = 2,
        SAY_MULTIBOT_3 = 3,
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(QUEST_A_JOB_FOR_THE_MULTI_BOT) == QUEST_STATUS_INCOMPLETE)
            player->ADD_GOSSIP_ITEM_DB(12634, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        if (action == (GOSSIP_ACTION_INFO_DEF + 1))
        {
            player->CastSpell(player, SPELL_FORCECAST_SUMMON_MULTI_BOT);
        }
        player->PlayerTalkClass->SendCloseGossip();
        return true;
    }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_A_JOB_FOR_THE_MULTI_BOT)
        {
            CAST_AI(npc_engineer_grindspark_42553::npc_engineer_grindspark_42553AI, creature->AI())->doAktion(player);
        }

        return true;
    }

    struct npc_engineer_grindspark_42553AI : public ScriptedAI
    {
        npc_engineer_grindspark_42553AI(Creature* creature) : ScriptedAI(creature) { }

        Player* player;
        uint32 uiTimer;
        uint8 transform;
        uint8 aktion;

        void Reset() override
        {
            uiTimer = 0;
            aktion = 0;
        }

        void UpdateAI(uint32 diff) override
        {
            if (uiTimer <= diff)
            {
                switch (aktion)
                {
                case 1:
                    Talk(SAY_MULTIBOT_0);
                    aktion = 2;
                    break;
                case 2:
                    Talk(SAY_MULTIBOT_1);
                    aktion = 3;
                    break;
                case 3:
                    Talk(SAY_MULTIBOT_2);
                    aktion = 4;
                    break;
                case 4:
                    Talk(SAY_MULTIBOT_3);
                    aktion = 5;
                    break;
                case 5:
                    player->CastSpell(player, SPELL_FORCECAST_SUMMON_MULTI_BOT);
                    aktion = 0;
                    break;
                }
                uiTimer = 3000;
            }
            else uiTimer -= diff;
        }

        void doAktion(Player* Player)
        {
            player = Player;
            aktion = 1;
            uiTimer = 0;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_engineer_grindspark_42553AI(creature);
    }

};

// 42598
class npc_multi_bot_42598 : public CreatureScript
{
public:
    npc_multi_bot_42598() : CreatureScript("npc_multi_bot_42598") { }

    enum eNpc
    {
        QUEST_A_JOB_FOR_THE_MULTI_BOT = 26205,
        OBJECT_TOXIC_POOL = 203975,
        SPELL_CLEAN_UP_TOXIC_POOL = 79424,
        SPELL_TOXIC_POOL_CREDIT_TO_MASTER = 79422,
        SPELL_GREEN_FUEL_BOT_TRANSFORM = 94513,
        SAY_MULTI_BOT = 0,
    };

    struct npc_multi_bot_42598AI : public ScriptedAI
    {
        npc_multi_bot_42598AI(Creature* creature) : ScriptedAI(creature) { }
        Player* player = me->GetCharmerOrOwnerPlayerOrPlayerItself();

        uint32 uiTimer;
        uint8 transform;
        uint8 aktion;

        void Reset() override
        {
            uiTimer = 0;
            transform = 0;
            aktion = 0;
        }

        void UpdateAI(uint32 diff) override
        {
            if (uiTimer <= diff)
            {
                GameObject* pool = me->FindNearestGameObject(OBJECT_TOXIC_POOL, 3.0f);
                if (pool)
                {
                    if (Player* player = me->GetCharmerOrOwnerPlayerOrPlayerItself())
                    {
                        if (aktion == 0)
                        {
                            Talk(SAY_MULTI_BOT);
                            aktion = 1;
                            me->GetMotionMaster()->MovePoint(1, pool->GetPosition());
                            uiTimer = 1000;
                        }
                        else
                        {
                            me->CastSpell(me, SPELL_CLEAN_UP_TOXIC_POOL);
                            if (transform == 0)
                            {
                                me->CastSpell(me, SPELL_GREEN_FUEL_BOT_TRANSFORM);
                                transform = 1;
                            }
                            me->CastSpell(player, SPELL_TOXIC_POOL_CREDIT_TO_MASTER);
                            pool->Delete();
                            me->GetMotionMaster()->MoveFollow(me->GetCharmerOrOwnerPlayerOrPlayerItself(), 1, 1.5);
                            aktion = 0;
                            uiTimer = 2000;
                        }
                    }
                }
                else
                    uiTimer = 3000;

                if ((player->GetQuestStatus(QUEST_A_JOB_FOR_THE_MULTI_BOT) == QUEST_STATUS_NONE) || (player->GetQuestStatus(QUEST_A_JOB_FOR_THE_MULTI_BOT) == QUEST_STATUS_REWARDED))
                {
                    me->DespawnOrUnsummon(0);
                }
            }
            else uiTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_multi_bot_42598AI(creature);
    }


};

// 204019
class go_makeshift_cage_204019 : public GameObjectScript
{
public:
    go_makeshift_cage_204019() : GameObjectScript("go_makeshift_cage_204019") { }

    enum ScourgeCage
    {
        NPC_TROGG_PRISONER = 42645,
        QUEST_MISSING_IN_ACTION = 26284,
    };

    bool OnGossipHello(Player* player, GameObject* go)
    {
        go->SetGoState(GO_STATE_ACTIVE);

        if (Creature* pNearestPrisoner = go->FindNearestCreature(NPC_TROGG_PRISONER, 5.0f, true))
        {
            if (player->GetQuestStatus(QUEST_MISSING_IN_ACTION) == QUEST_STATUS_INCOMPLETE)
            {
                CAST_AI(go_makeshift_cage_204019::go_makeshift_cage_204019AI, go->AI())->start(player, pNearestPrisoner);
            }
            else
                go->SetGoState(GO_STATE_READY);
        }
        else
            go->SetGoState(GO_STATE_READY);

        return true;
    }

    struct go_makeshift_cage_204019AI : public GameObjectAI
    {
        go_makeshift_cage_204019AI(GameObject* go) : GameObjectAI(go) { }

        uint32 timer;
        bool open;
        Creature* prisoner;
        Player* player;
        uint8 state;

        void Reset() override
        {
            timer = 0;
            state = 0;
            open = false;
        }

        void start(Player* pl, Creature* pr)
        {
            prisoner = pr;
            player = pl;
            timer = 0;
            open = true;
            prisoner->SetCorpseDelay(0);
        }

        void UpdateAI(uint32 diff) override
        {
            if (timer <= diff)
            {
                if (open)
                {
                    switch (state)
                    {
                    case 0:
                        //	go->SetGoState(GO_STATE_ACTIVE);
                        timer = 1000;
                        state = 1;
                        break;
                    case 1:
                        prisoner->AI()->Talk(0);
                        timer = 5000;
                        state = 2;
                        break;
                    case 2:
                        player->KilledMonsterCredit(NPC_TROGG_PRISONER, prisoner->GetGUID());
                        prisoner->DespawnOrUnsummon(0);
                        timer = 60000;
                        state = 3;
                        break;
                    case 3:
                        go->SetGoState(GO_STATE_READY);
                        timer = 1000;
                        state = 0;
                        open = false;
                        break;
                    }
                }
                timer = 1000;

            }
            else
                timer -= diff;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_makeshift_cage_204019AI(go);
    }
};

void AddSC_zone_gnomeregan()
{
    new npc_safe_operative_45847();
    new npc_crazed_leper_gnome_46391();
    new npc_wounded_infantry_42501();
    new npc_nevin_twistwrench_45966();
    new npc_carvo_blastbolt_47250();
    new npc_sanitron_500_46185();
    new npc_gnomeregan_torben_46293();
    new npc_mekka_torque_42317();
    new npc_toxic_pool_42563();
    new npc_engineer_grindspark_42553();
    new npc_multi_bot_42598();
    new go_makeshift_cage_204019();
}

