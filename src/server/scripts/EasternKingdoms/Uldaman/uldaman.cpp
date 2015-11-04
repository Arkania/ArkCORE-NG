/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
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

// 4863 npc_jadespine_basilisk
class npc_jadespine_basilisk : public CreatureScript
{
    public:

        npc_jadespine_basilisk(): CreatureScript("npc_jadespine_basilisk") { }

        struct npc_jadespine_basiliskAI : public ScriptedAI
        {
            npc_jadespine_basiliskAI(Creature* creature) : ScriptedAI(creature), m_instance ( creature->GetInstanceScript()){ }
            
            uint32 m_slumberTimer;
            InstanceScript* m_instance;

            void Reset() override
            {
                m_slumberTimer = 2000;
            }

            void EnterCombat(Unit* /*who*/) override
            {
            }

            void UpdateAI(uint32 uiDiff) override
            {
                //Return since we have no target
                if (!UpdateVictim())
                    return;

                //uiCslumberTimer
                if (m_slumberTimer <= uiDiff)
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
                else m_slumberTimer -= uiDiff;

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetUldamanAI<npc_jadespine_basiliskAI>(creature);
        }       
};

// 124371  go_keystone_chamber
class go_keystone_chamber : public GameObjectScript
{
public:
    go_keystone_chamber() : GameObjectScript("go_keystone_chamber") { }

    struct go_keystone_chamberAI : public GameObjectAI
    {
        go_keystone_chamberAI(GameObject* go) : GameObjectAI(go), m_instance(go->GetInstanceScript()){ }

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
        return GetUldamanAI<go_keystone_chamberAI>(go);
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



// 822  at_map_chamber
class AreaTrigger_at_map_chamber : public AreaTriggerScript
{
    public:

        AreaTrigger_at_map_chamber(): AreaTriggerScript("at_map_chamber") { }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*trigger*/) override
        {
            if (player->GetQuestStatus(QUEST_HIDDEN_CHAMBER) == QUEST_STATUS_INCOMPLETE)
                player->AreaExploredOrEventHappens(QUEST_HIDDEN_CHAMBER);

            return true;
        }
};

void AddSC_uldaman()
{
    new npc_jadespine_basilisk();
    new go_keystone_chamber();
    new go_ironaya_seal_door_124372();
    new AreaTrigger_at_map_chamber();
}

