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

/* ScriptData
SDName: Shadowfang_Keep
SD%Complete: 75
SDComment: npc_shadowfang_prisoner using escortAI for movement to door. Might need additional code in case being attacked. Add proper texts/say().
SDCategory: Shadowfang Keep
EndScriptData */

/* ContentData
npc_shadowfang_prisoner
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "ScriptedEscortAI.h"
#include "shadowfang_keep.h"
#include "Player.h"
#include "GameObjectAI.h"
#include "GameObject.h"

/*######
## npc_shadowfang_prisoner
######*/

// gameobject 18934 prison door right
class go_prison_door_18934 : public GameObjectScript
{
public:
    go_prison_door_18934() : GameObjectScript("go_prison_door_18934") { }

    struct go_prison_door_18934AI : public GameObjectAI
    {
        go_prison_door_18934AI(GameObject* go) : GameObjectAI(go) { m_instance = go->GetInstanceScript(); }

        InstanceScript* m_instance;

        void Reset() override
        {
            m_instance->SetData(TYPE_DOOR_1, NOT_STARTED);
        }

        void OnStateChanged(uint32 state, Unit* unit)
        {
            if (m_instance)
                if (Creature* ashbury = ObjectAccessor::GetCreature(*go, m_instance->GetData64(DATA_BARON_ASHBURY)))
                    if (!ashbury->IsAlive())
                    {
                        m_instance->SetData(TYPE_DOOR_1, DONE);
                        return;
                    }

            go->SetGoState(GO_STATE_READY);
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return GetShadowfangKeepAI<go_prison_door_18934AI>(go);
    }
};

// gameobject 18900 lever for prison door right
class go_prison_lever_18900 : public GameObjectScript
{
public:
    go_prison_lever_18900() : GameObjectScript("go_prison_lever_18900") { }

    enum eLeverStateOnWork
    {
        StateWaiting = 1,
        StateWork = 2,
        StateReset = 3,
        CloseDoor = 0,
        OpenDoor = 1,
    };

    struct go_prison_lever_18900AI : public GameObjectAI
    {
        go_prison_lever_18900AI(GameObject* go) : GameObjectAI(go) { m_instance = go->GetInstanceScript(); }

        InstanceScript* m_instance;

        void OnStateChanged(uint32 state, Unit* unit) override
        {
            if (m_instance && state == StateWork)
                if (Creature* ashbury = ObjectAccessor::GetCreature(*go, m_instance->GetData64(DATA_BARON_ASHBURY)))
                    if (GameObject* door = ObjectAccessor::GetGameObject(*go, m_instance->GetData64(DATA_PRISON_DOOR1)))
                        if (ashbury->IsAlive())
                        {
                            door->ResetDoorOrButton();
                            go->ResetDoorOrButton();
                        }
                        else
                        {
                            m_instance->DoUseDoorOrButton(m_instance->GetData64(DATA_PRISON_LEVER1), 3000);
                            m_instance->DoUseDoorOrButton(m_instance->GetData64(DATA_PRISON_DOOR1));
                        }
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return GetShadowfangKeepAI<go_prison_lever_18900AI>(go);
    }
};

// gameobject 18936 prison door mid
class go_prison_door_18936 : public GameObjectScript
{
public:
    go_prison_door_18936() : GameObjectScript("go_prison_door_18936") { }

    struct go_prison_door_18936AI : public GameObjectAI
    {
        go_prison_door_18936AI(GameObject* go) : GameObjectAI(go) { m_instance = go->GetInstanceScript(); }

        InstanceScript* m_instance;

        void Reset() override
        {
            m_instance->SetData(TYPE_DOOR_2, NOT_STARTED);
        }

        void OnStateChanged(uint32 state, Unit* unit)
        {
            if (m_instance)
                if (Creature* ashbury = ObjectAccessor::GetCreature(*go, m_instance->GetData64(DATA_BARON_ASHBURY)))
                    if (!ashbury->IsAlive())
                    {
                        m_instance->SetData(TYPE_DOOR_2, DONE);
                        return;
                    }
 
            go->SetGoState(GO_STATE_READY);
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return GetShadowfangKeepAI<go_prison_door_18936AI>(go);
    }
};

// gameobject 18901 lever for prison door mid
class go_prison_lever_18901 : public GameObjectScript
{
public:
    go_prison_lever_18901() : GameObjectScript("go_prison_lever_18901") { }

    enum eLeverStateOnWork
    {
        StateWaiting = 1,
        StateWork = 2,
        StateReset = 3,
        CloseDoor = 0,
        OpenDoor = 1,
    };

    struct go_prison_lever_18901AI : public GameObjectAI
    {
        go_prison_lever_18901AI(GameObject* go) : GameObjectAI(go) { m_instance = go->GetInstanceScript(); }

        InstanceScript* m_instance;
        
        void OnStateChanged(uint32 state, Unit* unit) override
        {
            if (m_instance && state == StateWork)
                if (Creature* ashbury = ObjectAccessor::GetCreature(*go, m_instance->GetData64(DATA_BARON_ASHBURY)))
                    if (GameObject* door = ObjectAccessor::GetGameObject(*go, m_instance->GetData64(DATA_PRISON_DOOR2)))
                        if (ashbury->IsAlive())
                        {
                            door->ResetDoorOrButton();
                            go->ResetDoorOrButton();
                        }
                        else
                        {
                            m_instance->DoUseDoorOrButton(m_instance->GetData64(DATA_PRISON_LEVER2), 3000);
                            m_instance->DoUseDoorOrButton(m_instance->GetData64(DATA_PRISON_DOOR2));
                        }
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return GetShadowfangKeepAI<go_prison_lever_18901AI>(go);
    }
};

// gameobject 18935 prison door left
class go_prison_door_18935 : public GameObjectScript
{
public:
    go_prison_door_18935() : GameObjectScript("go_prison_door_18935") { }

    struct go_prison_door_18935AI : public GameObjectAI
    {
        go_prison_door_18935AI(GameObject* go) : GameObjectAI(go) { m_instance = go->GetInstanceScript(); }

        InstanceScript* m_instance;

        void Reset() override
        {
            m_instance->SetData(TYPE_DOOR_3, NOT_STARTED);
        }

        void OnStateChanged(uint32 state, Unit* unit)
        {
            if (m_instance)
                if (Creature* ashbury = ObjectAccessor::GetCreature(*go, m_instance->GetData64(DATA_BARON_ASHBURY)))
                    if (!ashbury->IsAlive())
                    {
                        m_instance->SetData(TYPE_DOOR_3, DONE);
                        return;
                    }

            go->SetGoState(GO_STATE_READY);
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return GetShadowfangKeepAI<go_prison_door_18935AI>(go);
    }
};

// gameobject 101811 lever for prison door left
class go_prison_lever_101811 : public GameObjectScript
{
public:
    go_prison_lever_101811() : GameObjectScript("go_prison_lever_101811") { }

    enum eLeverStateOnWork
    {
        StateWaiting = 1,
        StateWork = 2,
        StateReset = 3,
        CloseDoor = 0,
        OpenDoor = 1,
    };

    struct go_prison_lever_101811AI : public GameObjectAI
    {
        go_prison_lever_101811AI(GameObject* go) : GameObjectAI(go) { m_instance = go->GetInstanceScript(); }

        InstanceScript* m_instance;

        void OnStateChanged(uint32 state, Unit* unit) override
        {
            if (m_instance && state == StateWork)
                if (Creature* ashbury = ObjectAccessor::GetCreature(*go, m_instance->GetData64(DATA_BARON_ASHBURY)))
                    if (GameObject* door = ObjectAccessor::GetGameObject(*go, m_instance->GetData64(DATA_PRISON_DOOR3)))
                        if (ashbury->IsAlive())
                        {
                            door->ResetDoorOrButton();
                            go->ResetDoorOrButton();
                        }
                        else
                        {
                            m_instance->DoUseDoorOrButton(m_instance->GetData64(DATA_PRISON_LEVER3), 3000);
                            m_instance->DoUseDoorOrButton(m_instance->GetData64(DATA_PRISON_DOOR3));
                        }
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return GetShadowfangKeepAI<go_prison_lever_101811AI>(go);
    }
};

// Horde: 3849 Deathstalker Adamant  // Alliance: 3850 Sorcerer Ashcrombe
class npc_shadowfang_prisoner : public CreatureScript
{
public:
    npc_shadowfang_prisoner() : CreatureScript("npc_shadowfang_prisoner") { }

    enum Yells
    {
        SAY_FREE_AS = 0,
        SAY_OPEN_DOOR_AS = 1,
        SAY_POST_DOOR_AS = 2,
        SAY_FREE_AD = 0,
        SAY_OPEN_DOOR_AD = 1,
        SAY_POST1_DOOR_AD = 2,
        SAY_POST2_DOOR_AD = 3
    };

    enum Spells
    {
        SPELL_ASHCROMBE_TELEPORT = 15742,
        SPELL_UNLOCK = 6421,
    };

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        InstanceScript* m_instance = creature->GetInstanceScript();

        if (!m_instance) return false;

        if (creature->GetEntry() == NPC_ADA && m_instance->GetData(TYPE_DOOR_1) == DONE)
            player->ADD_GOSSIP_ITEM_DB(21214, 0, GOSSIP_SENDER_MAIN, 1001);

        if (creature->GetEntry() == NPC_ASH && m_instance->GetData(TYPE_DOOR_2) == DONE)
            player->ADD_GOSSIP_ITEM_DB(21213, 0, GOSSIP_SENDER_MAIN, 1001);

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF+1)
        {
            player->CLOSE_GOSSIP_MENU();

            if (npc_escortAI* pEscortAI = CAST_AI(npc_shadowfang_prisoner::npc_shadowfang_prisonerAI, creature->AI()))
                pEscortAI->Start(false, false);
        }
        return true;
    }

    struct npc_shadowfang_prisonerAI : public npc_escortAI
    {
        npc_shadowfang_prisonerAI(Creature* creature) : npc_escortAI(creature)
        {
            m_instance = creature->GetInstanceScript();
        }

        InstanceScript* m_instance;

        void WaypointReached(uint32 waypointId) override
        {
            switch (waypointId)
            {
                case 0:
                    if (me->GetEntry() == NPC_ASH)
                        Talk(SAY_FREE_AS);
                    else
                        Talk(SAY_FREE_AD);
                    break;
                case 10:
                    if (me->GetEntry() == NPC_ASH)
                        Talk(SAY_OPEN_DOOR_AS);
                    else
                        Talk(SAY_OPEN_DOOR_AD);
                    break;
                case 11:
                    if (me->GetEntry() == NPC_ASH)
                        DoCast(me, SPELL_UNLOCK);
                    break;
                case 12:
                    if (me->GetEntry() == NPC_ASH)
                        Talk(SAY_POST_DOOR_AS);
                    else
                        Talk(SAY_POST1_DOOR_AD);

                    m_instance->SetData(TYPE_FREE_NPC, DONE);
                    m_instance->DoUseDoorOrButton(m_instance->GetData64(DATA_COURTYARD_DOOR), 999999);

                    break;
                case 13:
                    if (me->GetEntry() != NPC_ASH)
                        Talk(SAY_POST2_DOOR_AD);
                    break;
                case 14:
                    me->CastSpell(me, SPELL_ASHCROMBE_TELEPORT);
                    break;
                case 15:
                    float x, y, z, o;
                    me->GetHomePosition(x, y, z, o);
                    me->NearTeleportTo(x, y, z, o);
                    break;
            }
        }

        void Reset() override { }
        void EnterCombat(Unit* /*who*/) override { }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<npc_shadowfang_prisonerAI>(creature);
    }
};

// gameobject 18895 door
class go_courtyard_door_18895 : public GameObjectScript
{
public:
    go_courtyard_door_18895() : GameObjectScript("go_courtyard_door_18895") { }

    struct go_courtyard_door_18895AI : public GameObjectAI
    {
        go_courtyard_door_18895AI(GameObject* go) : GameObjectAI(go) { m_instance = go->GetInstanceScript(); }

        InstanceScript* m_instance;

        void Reset() override
        {
            m_instance->SetData(TYPE_FREE_NPC, NOT_STARTED);
        }

        void OnStateChanged(uint32 state, Unit* unit) override
        {
            if (m_instance)
            {
                if (m_instance->GetData(TYPE_FREE_NPC) == DONE)
                {
                    m_instance->SetData(TYPE_DOOR_COURTYARD, DONE);

                    if (state == GO_STATE_ACTIVE)
                        return;
                    
                    go->SetGoState(GO_STATE_ACTIVE);
                    return;
                }
            }

            go->SetGoState(GO_STATE_READY); // GO_STATE_ACTIVE
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return GetShadowfangKeepAI<go_courtyard_door_18895AI>(go);
    }
};

// 4627 Arugal's Voidwalker
class npc_arugal_voidwalker : public CreatureScript
{
public:
    npc_arugal_voidwalker() : CreatureScript("npc_arugal_voidwalker") { }

    enum Spells
    {
        SPELL_DARK_OFFERING = 7154
    };

    struct npc_arugal_voidwalkerAI : public ScriptedAI
    {
        npc_arugal_voidwalkerAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        uint32 uiDarkOffering;

        void Reset() override
        {
            uiDarkOffering = urand(200, 1000);
        }

        void UpdateAI(uint32 uiDiff) override
        {
            if (!UpdateVictim())
                return;

            if (uiDarkOffering <= uiDiff)
            {
                if (Creature* pFriend = me->FindNearestCreature(me->GetEntry(), 25.0f, true))
                    DoCast(pFriend, SPELL_DARK_OFFERING);
                else
                    DoCast(me, SPELL_DARK_OFFERING);
                uiDarkOffering = urand(4400, 12500);
            } else uiDarkOffering -= uiDiff;

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/) override
        {
            instance->SetData(TYPE_FENRUS, instance->GetData(TYPE_FENRUS) + 1);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<npc_arugal_voidwalkerAI>(creature);
    }
};

// 7057 Haunting Spirits
class spell_shadowfang_keep_haunting_spirits : public SpellScriptLoader
{
    public:
        spell_shadowfang_keep_haunting_spirits() : SpellScriptLoader("spell_shadowfang_keep_haunting_spirits") { }

        class spell_shadowfang_keep_haunting_spirits_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_shadowfang_keep_haunting_spirits_AuraScript);

            void CalcPeriodic(AuraEffect const* /*aurEff*/, bool& isPeriodic, int32& amplitude)
            {
                isPeriodic = true;
                amplitude = (irand(0, 60) + 30) * IN_MILLISECONDS;
            }

            void HandleDummyTick(AuraEffect const* aurEff)
            {
                GetTarget()->CastSpell((Unit*)NULL, aurEff->GetAmount(), true);
            }

            void HandleUpdatePeriodic(AuraEffect* aurEff)
            {
                aurEff->CalculatePeriodic(GetCaster());
            }

            void Register() override
            {
                DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(spell_shadowfang_keep_haunting_spirits_AuraScript::CalcPeriodic, EFFECT_0, SPELL_AURA_DUMMY);
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_shadowfang_keep_haunting_spirits_AuraScript::HandleDummyTick, EFFECT_0, SPELL_AURA_DUMMY);
                OnEffectUpdatePeriodic += AuraEffectUpdatePeriodicFn(spell_shadowfang_keep_haunting_spirits_AuraScript::HandleUpdatePeriodic, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_shadowfang_keep_haunting_spirits_AuraScript();
        }
};

void AddSC_shadowfang_keep()
{
    new go_prison_lever_18900();
    new go_prison_door_18934();
    new go_prison_lever_18901();
    new go_prison_door_18935();
    new go_prison_lever_101811();
    new go_prison_door_18936();
    new npc_shadowfang_prisoner();
    new go_courtyard_door_18895();
    new npc_arugal_voidwalker();
    new spell_shadowfang_keep_haunting_spirits();
}
