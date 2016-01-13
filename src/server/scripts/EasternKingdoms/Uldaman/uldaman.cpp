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

#include "uldaman.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "GameObjectAI.h"
#include "GameObject.h"
#include "PassiveAI.h"
#include "Player.h"
#include "WorldSession.h"
#include "MapManager.h"
#include "ObjectMgr.h"
#include "Vehicle.h"


// 4857 stonekeepers
class npc_stonekeepers_4857 : public CreatureScript
{
public:

    npc_stonekeepers_4857() : CreatureScript("npc_stonekeepers_4857") { }

    struct npc_stonekeepers_4857AI : public ScriptedAI
    {
        npc_stonekeepers_4857AI(Creature* creature) : ScriptedAI(creature) { m_instance = me->GetInstanceScript(); }

        InstanceScript* m_instance;

        void Reset() override
        {
            me->setFaction(35);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            me->RemoveAllAuras();
            me->AddAura(SPELL_STONED, me);
        }

        void EnterCombat(Unit* who) override
        {
            //if (Player* player = who->ToPlayer())
            //    player->CastSpell(player, SPELL_BOSS_OBJECT_VISUAL, false);
        }

        void JustDied(Unit* /*attacker*/) override
        {
            DoCast(me, SPELL_SELF_DESTRUCT, true);
            if (GameObject* altar = me->FindNearestGameObject(130511, 25.0f))
                altar->AI()->DoAction(2);
        }

        void DoAction(int32 action) override
        {
            switch (action)
            {
            case 1:
            {
                me->RemoveAllAuras();
                me->setFaction(14);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                me->SetReactState(REACT_AGGRESSIVE);
                me->GetMotionMaster()->Clear(true);
                me->SetSpeed(MOVE_WALK, 1.0f, true);
                me->SetSpeed(MOVE_RUN, 1.2f, true);
                me->SetWalk(true);
                if (Player* player = me->FindNearestPlayer(25.0f, true))
                {
                    me->GetMotionMaster()->MoveChase(player);
                    me->Attack(player, true);
                }
                break;
            }
            }
        }

        void UpdateAI(uint32 /*diff*/) override
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_stonekeepers_4857AI(creature);
    }
};

// 4863 jadespine_basilisk
class npc_jadespine_basilisk_4863 : public CreatureScript
{
    public:

        npc_jadespine_basilisk_4863() : CreatureScript("npc_jadespine_basilisk_4863") { }

        struct npc_jadespine_basilisk_4863AI : public ScriptedAI
        {
            npc_jadespine_basilisk_4863AI(Creature* creature) : ScriptedAI(creature), m_instance(creature->GetInstanceScript()){ }
            
            uint32 m_slumberTimer;
            InstanceScript* m_instance;

            void Reset() override
            {
                m_slumberTimer = 2000;
            }

            void EnterCombat(Unit* /*who*/) override
            {
            }

            void UpdateAI(uint32 diff) override
            {
                //Return since we have no target
                if (!UpdateVictim())
                    return;

                //uiCslumberTimer
                if (m_slumberTimer <= diff)
                {
                    //Cast
                    DoCastVictim(SPELL_CRYSTALLINE_SLUMBER, true);

                    //Stop attacking target thast asleep and pick new target
                    m_slumberTimer = 28000;

                    Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO, 0);

                    if (!target || target == me->GetVictim())
                        target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true);

                    if (target)
                        me->TauntApply(target);

                }
                else m_slumberTimer -= diff;

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetUldamanAI<npc_jadespine_basilisk_4863AI>(creature);
        }       
};

// 7076 earthen_guardian
class npc_earthen_guardian_7076 : public CreatureScript
{
public:

    npc_earthen_guardian_7076() : CreatureScript("npc_earthen_guardian_7076") { }

    struct npc_earthen_guardian_7076AI : public ScriptedAI
    {
        npc_earthen_guardian_7076AI(Creature* creature) : ScriptedAI(creature) { m_instance = me->GetInstanceScript(); }

        InstanceScript* m_instance;

        void Reset() override
        {
            me->setFaction(35);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            me->RemoveAllAuras();
            me->AddAura(SPELL_STONED, me);
        }

        void EnterCombat(Unit* who) override
        {
            
        }

        void JustDied(Unit* /*attacker*/) override
        {
            //DoCast(me, SPELL_SELF_DESTRUCT, true);            
        }

        void DoAction(int32 action) override
        {
            switch (action)
            {
            case ACTION_AWAKE:
            {
                me->RemoveAllAuras();
                me->setFaction(14);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                me->SetReactState(REACT_AGGRESSIVE);
                me->GetMotionMaster()->Clear(true);
                me->SetSpeed(MOVE_WALK, 1.0f, true);
                me->SetSpeed(MOVE_RUN, 1.2f, true);
                me->SetWalk(true);
                if (Player* player = me->FindNearestPlayer(50.0f, true))
                {
                    me->GetMotionMaster()->MoveChase(player);
                    me->Attack(player, true);
                }
                break;
            }
            }
        }

        void UpdateAI(uint32 /*diff*/) override
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_earthen_guardian_7076AI(creature);
    }
};

// 7309 earthen_custodian
class npc_earthen_custodian_7309 : public CreatureScript
{
public:

    npc_earthen_custodian_7309() : CreatureScript("npc_earthen_custodian_7309") { }

    struct npc_earthen_custodian_7309AI : public ScriptedAI
    {
        npc_earthen_custodian_7309AI(Creature* creature) : ScriptedAI(creature) { m_instance = me->GetInstanceScript(); }

        InstanceScript* m_instance;

        void Reset() override
        {
            me->setFaction(35);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            me->RemoveAllAuras();
            me->AddAura(SPELL_STONED, me);
        }

        void EnterCombat(Unit* who) override
        {

        }

        void JustDied(Unit* /*attacker*/) override
        {
            DoCast(me, SPELL_SELF_DESTRUCT, true);
        }

        void DoAction(int32 action) override
        {
            switch (action)
            {
            case ACTION_AWAKE:
            {
                me->RemoveAllAuras();
                me->setFaction(14);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                me->SetReactState(REACT_AGGRESSIVE);
                me->GetMotionMaster()->Clear(true);
                me->SetSpeed(MOVE_WALK, 1.0f, true);
                me->SetSpeed(MOVE_RUN, 1.2f, true);
                me->SetWalk(true);
                if (Player* player = me->FindNearestPlayer(50.0f, true))
                {
                    me->GetMotionMaster()->MoveChase(player);
                    me->Attack(player, true);
                }
                break;
            }
            }
        }

        void UpdateAI(uint32 /*diff*/) override
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_earthen_custodian_7309AI(creature);
    }
};

// 10120 vault_warder
class npc_vault_warder_10120 : public CreatureScript
{
public:

    npc_vault_warder_10120() : CreatureScript("npc_vault_warder_10120") { }

    struct npc_vault_warder_10120AI : public ScriptedAI
    {
        npc_vault_warder_10120AI(Creature* creature) : ScriptedAI(creature) { m_instance = me->GetInstanceScript(); }

        InstanceScript* m_instance;

        void Reset() override
        {
            me->setFaction(35);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            me->RemoveAllAuras();
            me->AddAura(SPELL_STONED, me);
        }

        void EnterCombat(Unit* who) override
        {

        }

        void JustDied(Unit* /*attacker*/) override
        {
            DoCast(me, SPELL_SELF_DESTRUCT, true);
        }

        void DoAction(int32 action) override
        {
            switch (action)
            {
            case ACTION_AWAKE:
            {
                me->RemoveAllAuras();
                me->setFaction(14);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                me->SetReactState(REACT_AGGRESSIVE);
                me->GetMotionMaster()->Clear(true);
                me->SetSpeed(MOVE_WALK, 1.0f, true);
                me->SetSpeed(MOVE_RUN, 1.2f, true);
                me->SetWalk(true);
                if (Player* player = me->FindNearestPlayer(50.0f, true))
                {
                    me->GetMotionMaster()->MoveChase(player);
                    me->Attack(player, true);
                }
                break;
            }
            }
        }

        void UpdateAI(uint32 /*diff*/) override
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_vault_warder_10120AI(creature);
    }
};

// 124371  go_keystone_chamber
class go_keystone_chamber_124371 : public GameObjectScript
{
public:
    go_keystone_chamber_124371() : GameObjectScript("go_keystone_chamber_124371") { }

    struct go_keystone_chamber_124371AI : public GameObjectAI
    {
        go_keystone_chamber_124371AI(GameObject* go) : GameObjectAI(go), m_instance(go->GetInstanceScript()){ }

        InstanceScript* m_instance;
        uint32 m_phase;
        uint32 m_timer;

        void Reset()
        {
            m_phase = 0;
            m_timer = 0;
        }

        bool GossipHello(Player* player) override
        { 
            GameObject* door = ObjectAccessor::GetGameObject(*go, m_instance->GetData64(DATA_IRONAYA_SEAL_DOOR));
            Creature* ironaya = go->FindNearestCreature(7228, 100.0f);            
            GOState keyState = go->GetGoState();

            if (!ironaya || m_phase)
                return false;

            GOState doorState = door->GetGoState();
            if (doorState == GO_STATE_ACTIVE)
                return false;

            Creature* npc1 = go->FindNearestCreature(7175, 20.0f);
            Creature* npc2 = go->FindNearestCreature(4850, 20.0f);
            Creature* npc3 = go->FindNearestCreature(4852, 20.0f);

            if (!npc1 && !npc2 && !npc3)
            {                               
                m_phase = 1;
                m_timer = 100;
            }
            return false; 
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_timer <= diff)
            {
                m_timer = 1000;
                DoWork();
            }
            else
                m_timer -= diff;
        }

        void DoWork()
        {
            switch (m_phase)
            {
                case 1:
                    // castspell blue laser to the door
                    m_phase++;
                    m_timer = 3000;
                    break;
                case 2:
                    if (GameObject* door = ObjectAccessor::GetGameObject(*go, m_instance->GetData64(DATA_IRONAYA_SEAL_DOOR)))
                        door->SetGoState(GO_STATE_ACTIVE);

                    m_phase++;
                    m_timer = 2000;
                    break;
                case 3:
                    if (GameObject* key = ObjectAccessor::GetGameObject(*go, m_instance->GetData64(DATA_KEYSTONE)))
                        if (Player* player = key->FindNearestPlayer(30.0f))
                            if (Creature* ironaya = ObjectAccessor::GetCreature(*go, m_instance->GetData64(DATA_IRONAYA)))
                            {
                                ironaya->SetReactState(REACT_AGGRESSIVE);
                                ironaya->setFaction(415);
                                ironaya->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                                ironaya->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                ironaya->Attack(player, true);
                            }
                    m_phase++;
                    m_timer = 3000;
                    break;
                case 4:
                    break;
            }
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return GetUldamanAI<go_keystone_chamber_124371AI>(go);
    }
};

// gameobject 124372 go_ironaya_seal_door
class go_ironaya_seal_door_124372 : public GameObjectScript
{
public:
    go_ironaya_seal_door_124372() : GameObjectScript("go_ironaya_seal_door_124372") { }

    struct go_ironaya_seal_door_124372AI : public GameObjectAI
    {
        go_ironaya_seal_door_124372AI(GameObject* go) : GameObjectAI(go) { m_instance = go->GetInstanceScript(); }

        
        InstanceScript* m_instance;

        void Reset() override
        {

        }

        void OnStateChanged(uint32 state, Unit* unit) override
        {
            bool mustBeClosed = false;
            if (m_instance)
            {
                if (GameObject* key = ObjectAccessor::GetGameObject(*go, m_instance->GetData64(DATA_KEYSTONE)))
                {

                }
                if (GameObject* door = ObjectAccessor::GetGameObject(*go, m_instance->GetData64(DATA_IRONAYA_SEAL_DOOR)))
                {

                }
                    //if (mustBeClosed)
                        //door->SetGoState(GO_STATE_READY);
                    //else
                        //door->SetGoState(GO_STATE_ACTIVE); // open the door  GO_STATE_READY  GO_STATE_ACTIVE  GO_STATE_ACTIVE_ALTERNATIVE
            }
        }

        void UpdateAI(uint32 diff) override
        {

        }

    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return GetUldamanAI<go_ironaya_seal_door_124372AI>(go);
    }
};

// 130511
class go_altar_of_the_keepers_130511 : public GameObjectScript
{
public:
    go_altar_of_the_keepers_130511() : GameObjectScript("go_altar_of_the_keepers_130511") {}

    struct go_altar_of_the_keepers_130511AI : public GameObjectAI
    {
        go_altar_of_the_keepers_130511AI(GameObject* go) : GameObjectAI(go), m_instance(go->GetInstanceScript()){ }

        InstanceScript* m_instance;
        uint32 m_phase;
        uint32 m_timer;

        void Reset()
        {
            m_phase = 0;
            m_timer = 0;
        }

        bool GossipHello(Player* player) override
        {
            m_phase = 1;
            m_timer = 100;

            return false;
        }

        void DoAction(int32 action) override
        {
            switch (action)
            {
                case 2:
                    m_phase = 1;
                    m_timer = 100;
                    break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_timer <= diff)
            {
                m_timer = 1000;
                DoWork();
            }
            else
                m_timer -= diff;
        }

        void DoWork()
        {
            switch (m_phase)
            {
            case 1:
                {
                    std::vector<Creature*> minionsDeath = go->FindNearestCreatures(4857, 25.0f, false);
                    std::vector<Creature*> minions = go->FindNearestCreatures(4857, 25.0f, true);
                    if (minions.size() == 0 || minionsDeath.size() >= 4)
                    {
                        m_phase = 0;
                        m_timer = 0;
                        if (GameObject* door = ObjectAccessor::GetGameObject(*go, m_instance->GetData64(DATA_TEMPLE_DOOR_2)))
                        {
                            m_instance->SetBossState(ENC_ANCIENT_STONE_KEEPER, DONE);
                            door->SetGoState(GO_STATE_ACTIVE);
                        }
                    }
                    else
                    {
                        uint8 rol = urand(0, minions.size() - 1);
                        Creature* keeper = minions[rol];
                        keeper->GetAI()->DoAction(1);
                        m_phase = 2;
                    }
                    break;
                }
                case 2:
                    break;
                case 3:
                    break;
            }
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return GetUldamanAI<go_altar_of_the_keepers_130511AI>(go);
    }
};

// 133234
class go_altar_of_archaedas_133234 : public GameObjectScript
{
public:
    go_altar_of_archaedas_133234() : GameObjectScript("go_altar_of_archaedas_133234") {}

    struct go_altar_of_archaedas_133234AI : public GameObjectAI
    {
        go_altar_of_archaedas_133234AI(GameObject* go) : GameObjectAI(go), m_instance(go->GetInstanceScript()){ }

        InstanceScript* m_instance;
        uint32 m_phase;

        void Reset() override
        {
            m_phase = 0;          
        }

        bool GossipHello(Player* player) override
        {
            if (m_phase == 0 && m_instance->GetData(DATA_ARCHAEDAS) != DONE)
            {
                if (Creature* archaedas = ObjectAccessor::GetCreature(*go, m_instance->GetData64(DATA_ARCHAEDAS)))
                {
                    archaedas->GetAI()->DoAction(1);
                    m_phase = 2;
                }
            }

            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return GetUldamanAI<go_altar_of_archaedas_133234AI>(go);
    }
};

// 822  at_map_chamber
class at_map_chamber_822 : public AreaTriggerScript
{
    public:

        at_map_chamber_822() : AreaTriggerScript("at_map_chamber_822") { }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*trigger*/) override
        {
            if (player->GetQuestStatus(QUEST_HIDDEN_CHAMBER) == QUEST_STATUS_INCOMPLETE)
                player->AreaExploredOrEventHappens(QUEST_HIDDEN_CHAMBER);

            return true;
        }
};

void AddSC_uldaman()
{
    new npc_jadespine_basilisk_4863();
    new npc_stonekeepers_4857();
    new npc_earthen_guardian_7076();
    new npc_earthen_custodian_7309();
    new npc_vault_warder_10120();
    new go_keystone_chamber_124371();
    new go_ironaya_seal_door_124372();
    new go_altar_of_the_keepers_130511();
    new go_altar_of_archaedas_133234();
    new at_map_chamber_822();
}

