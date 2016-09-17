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
#include "GameObjectAI.h"
#include "GameObject.h"
#include "PassiveAI.h"
#include "deadmines.h"
#include "Player.h"
#include "WorldSession.h"
#include "MapManager.h"
#include "ObjectMgr.h"
#include "Vehicle.h"

enum Event
{
    EVENT_STATE = 0,
    EVENT_GLUBTOK
};

enum CannonState
{
    CANNON_NOT_USED = 0,
    CANNON_GUNPOWDER_USED,
    CANNON_BLAST_INITIATED,
    PIRATES_ATTACK,
    EVENT_DONE
};

// http://www.wowhead.com/item=5397/defias-gunpowder
class item_defias_gunpowder : public ItemScript
{
public:
    item_defias_gunpowder() : ItemScript("item_defias_gunpowder") { }

    bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
    {
        InstanceScript* instance = player->GetInstanceScript();

        if (!instance)
        {
            player->GetSession()->SendNotification("Instance script not initialized");
            return true;
        }
        if (instance->GetData(EVENT_STATE) != CANNON_NOT_USED)
            return false;
        if (targets.GetGOTarget() && targets.GetGOTarget()->GetEntry() == GO_DEFIAS_CANNON)
        {
            instance->SetData(EVENT_STATE, CANNON_GUNPOWDER_USED);
        }

        player->DestroyItemCount(item->GetEntry(), 1, true);
        return true;
    }
};

// gameobject 101831 lever for factory door
class go_factory_lever_101831 : public GameObjectScript
{
public:
    go_factory_lever_101831() : GameObjectScript("go_factory_lever_101831") { }

    struct go_factory_lever_101831_AI : public GameObjectAI
    {
        go_factory_lever_101831_AI(GameObject* go) : GameObjectAI(go) { _instance = go->GetInstanceScript(); }

        InstanceScript* _instance;

        void OnStateChanged(uint32 state, Unit* unit)
        {
            if (_instance > 0 && state == 2)
                if (GameObject* door = ObjectAccessor::GetGameObject(*go, _instance->GetData64(DATA_MASTROOM_DOOR)))
                {
                    GOState state = door->GetGoState() == GO_STATE_READY ? GO_STATE_ACTIVE : GO_STATE_READY;
                    door->SetGoState(state); // open the door  GO_STATE_READY  GO_STATE_ACTIVE  GO_STATE_ACTIVE_ALTERNATIVE
                }
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return GetDeadminesAI<go_factory_lever_101831_AI>(go);
    }
};

// gameobject 13965 factory door
class go_factory_door_13965 : public GameObjectScript
{
public:
    go_factory_door_13965() : GameObjectScript("go_factory_door_13965") { }

    enum eDoor13965
    {
        EVENT_CLOSE_DOOR = 0,
    };

    struct go_factory_door_13965_AI : public GameObjectAI
    {
        go_factory_door_13965_AI(GameObject* go) : GameObjectAI(go) { m_instance = go->GetInstanceScript(); }

        InstanceScript* m_instance;
        EventMap m_events;

        void Reset()
        {
            m_events.Reset();
        }

        void OnStateChanged(uint32 state, Unit* unit)
        {
            if (m_instance)
                if (Creature* glubtok = ObjectAccessor::GetCreature(*go, m_instance->GetData64(DATA_GLUBTOK)))
                    if (GameObject* door = ObjectAccessor::GetGameObject(*go, m_instance->GetData64(DATA_FACTORY_DOOR)))
                        if (GameObject* lever = ObjectAccessor::GetGameObject(*go, m_instance->GetData64(DATA_FACTORY_DOOR_LEVER)))
                            if (glubtok->IsAlive())
                            {
                                if (lever->GetGoState() == 2)
                                {
                                    door->SetGoState(GO_STATE_ACTIVE);
                                    m_events.ScheduleEvent(EVENT_CLOSE_DOOR, 10000);
                                }
                                else
                                    door->SetGoState(GO_STATE_READY);
                            }
                            else
                                door->SetGoState(GO_STATE_ACTIVE); // open the door  GO_STATE_READY  GO_STATE_ACTIVE  GO_STATE_ACTIVE_ALTERNATIVE
        }

        void UpdateAI(uint32 diff)
        {
            m_events.Update(diff);
            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CLOSE_DOOR:
                {
                    if (m_instance)
                        if (GameObject* door = ObjectAccessor::GetGameObject(*go, m_instance->GetData64(DATA_FACTORY_DOOR)))
                            door->SetGoState(GO_STATE_READY);
                    break;
                }
                }
            }
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return GetDeadminesAI<go_factory_door_13965_AI>(go);
    }
};

// gameobject 101832 lever for mastroom door
class go_mastroom_lever_101832 : public GameObjectScript
{
public:
    go_mastroom_lever_101832() : GameObjectScript("go_mastroom_lever_101832") { }

    struct go_mastroom_lever_101832_AI : public GameObjectAI
    {
        go_mastroom_lever_101832_AI(GameObject* go) : GameObjectAI(go) { _instance = go->GetInstanceScript(); }

        InstanceScript* _instance;

        void OnStateChanged(uint32 state, Unit* unit)
        {
            if (_instance > 0 && state == 2)
                if (GameObject* door = ObjectAccessor::GetGameObject(*go, _instance->GetData64(DATA_MASTROOM_DOOR)))
                {
                    GOState state = door->GetGoState() == GO_STATE_READY ? GO_STATE_ACTIVE : GO_STATE_READY;
                    door->SetGoState(state); // open the door  GO_STATE_READY  GO_STATE_ACTIVE  GO_STATE_ACTIVE_ALTERNATIVE
                }
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return GetDeadminesAI<go_mastroom_lever_101832_AI>(go);
    }
};

// gameobject 16400 mastroom door
class go_mastroom_door_16400 : public GameObjectScript
{
public:
    go_mastroom_door_16400() : GameObjectScript("go_mastroom_door_16400") { }

    struct go_mastroom_door_16400_AI : public GameObjectAI
    {
        go_mastroom_door_16400_AI(GameObject* go) : GameObjectAI(go) { m_instance = go->GetInstanceScript(); }

        InstanceScript* m_instance;

        void OnStateChanged(uint32 state, Unit* unit)
        {
            bool mustBeClosed = false;
            if (m_instance)
            {
                if (Creature* olaf = ObjectAccessor::GetCreature(*go, m_instance->GetData64(DATA_LUMBERING_OAF)))
                    if (olaf->IsAlive())
                        mustBeClosed = true;
                if (Creature* helix = ObjectAccessor::GetCreature(*go, m_instance->GetData64(DATA_HELIX_GEARBREAKER)))
                    if (helix->IsAlive())
                        mustBeClosed = true;
                if (GameObject* door = ObjectAccessor::GetGameObject(*go, m_instance->GetData64(DATA_MASTROOM_DOOR)))
                    if (mustBeClosed)
                        door->SetGoState(GO_STATE_READY);
                    else
                        door->SetGoState(GO_STATE_ACTIVE); // open the door  GO_STATE_READY  GO_STATE_ACTIVE  GO_STATE_ACTIVE_ALTERNATIVE
            }
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return GetDeadminesAI<go_mastroom_door_16400_AI>(go);
    }
};

// gameobject 101834 lever for foundry door
class go_foundry_lever_101834 : public GameObjectScript
{
public:
    go_foundry_lever_101834() : GameObjectScript("go_foundry_lever_101834") { }

    struct go_foundry_lever_101834_AI : public GameObjectAI
    {
        go_foundry_lever_101834_AI(GameObject* go) : GameObjectAI(go) { _instance = go->GetInstanceScript(); }

        InstanceScript* _instance;

        void OnStateChanged(uint32 state, Unit* unit)
        {
            if (_instance > 0 && state == 2)
                if (GameObject* door = ObjectAccessor::GetGameObject(*go, _instance->GetData64(DATA_MASTROOM_DOOR)))
                {
                    GOState state = door->GetGoState() == GO_STATE_READY ? GO_STATE_ACTIVE : GO_STATE_READY;
                    door->SetGoState(state); // open the door  GO_STATE_READY  GO_STATE_ACTIVE  GO_STATE_ACTIVE_ALTERNATIVE
                }
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return GetDeadminesAI<go_foundry_lever_101834_AI>(go);
    }
};

// gameobject 16399 foundry door 
class go_foundry_door_16399 : public GameObjectScript
{
public:
    go_foundry_door_16399() : GameObjectScript("go_foundry_door_16399") { }

    struct go_foundry_door_16399_AI : public GameObjectAI
    {
        go_foundry_door_16399_AI(GameObject* go) : GameObjectAI(go) { m_instance = go->GetInstanceScript(); }

        InstanceScript* m_instance;

        void OnStateChanged(uint32 state, Unit* unit)
        {
            if (m_instance)
                if (Creature* foo = ObjectAccessor::GetCreature(*go, m_instance->GetData64(DATA_FOO_REAPER_5000)))
                    if (GameObject* door = ObjectAccessor::GetGameObject(*go, m_instance->GetData64(DATA_FOUNDRY_DOOR)))
                        if (foo->IsAlive())
                            door->SetGoState(GO_STATE_READY);
                        else
                            door->SetGoState(GO_STATE_ACTIVE); // open the door  GO_STATE_READY  GO_STATE_ACTIVE  GO_STATE_ACTIVE_ALTERNATIVE
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return GetDeadminesAI<go_foundry_door_16399_AI>(go);
    }
};

// gameobject 101833 lever for iron clad door
class go_ironclad_lever_101833 : public GameObjectScript
{
public:
    go_ironclad_lever_101833() : GameObjectScript("go_ironclad_lever_101833") { }

    struct go_ironclad_lever_101833_AI : public GameObjectAI
    {
        go_ironclad_lever_101833_AI(GameObject* go) : GameObjectAI(go) { _instance = go->GetInstanceScript(); }

        InstanceScript* _instance;

        void OnStateChanged(uint32 state, Unit* unit)
        {
            if (_instance > 0 && state == 2)
                if (GameObject* door = ObjectAccessor::GetGameObject(*go, _instance->GetData64(DATA_IRONCLAD_DOOR)))
                    door->SetGoState(GO_STATE_ACTIVE); // open the door  GO_STATE_READY  GO_STATE_ACTIVE  GO_STATE_ACTIVE_ALTERNATIVE
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return GetDeadminesAI<go_ironclad_lever_101833_AI>(go);
    }
};

// gameobject 16397 iron clad door
class go_ironclad_door_16397 : public GameObjectScript
{
public:
    go_ironclad_door_16397() : GameObjectScript("go_ironclad_door_16397") { }

    struct go_ironclad_door_16397_AI : public GameObjectAI
    {
        go_ironclad_door_16397_AI(GameObject* go) : GameObjectAI(go) { m_instance = go->GetInstanceScript(); }

        InstanceScript* m_instance;

        void Destroyed(Player* /*player*/, uint32 eventId)
        {
            printf("\ngo_ironclad_door_16397::Destroyed  eventId=%u \n", eventId);
        }

        void OnStateChanged(uint32 state, Unit* unit) // the door is allways closed until destroyed..
        {
            if (m_instance)
                if (GameObject* door = ObjectAccessor::GetGameObject(*go, m_instance->GetData64(DATA_IRONCLAD_DOOR)))
                    door->SetGoState(GO_STATE_READY);
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return GetDeadminesAI<go_ironclad_door_16397_AI>(go);
    }
};

// gameobject 16398 defias cannon
class go_defias_cannon_16398 : public GameObjectScript
{
public:
    go_defias_cannon_16398() : GameObjectScript("go_defias_cannon_16398") { }

    enum Sounds
    {
        SOUND_CANNONFIRE = 1400,
        SOUND_DESTROYDOOR = 3079,
    };

    enum Misc
    {
        DATA_CANNON_BLAST_TIMER = 3000,
        DATA_PIRATES_DELAY_TIMER = 1000
    };

    struct go_defias_cannon_16398_AI : public GameObjectAI
    {
        go_defias_cannon_16398_AI(GameObject* go) : GameObjectAI(go) { m_instance = go->GetInstanceScript(); }

        InstanceScript* m_instance;

        void OnStateChanged(uint32 state, Unit* unit) // the door is allways closed until destroyed..
        {
            if (m_instance)
                if (state = 2)
                    if (GameObject* cannon = ObjectAccessor::GetGameObject(*go, m_instance->GetData64(DATA_DEFIAS_CANNON))) // m_instance->GetGameObject(DefiasCannonGUID))
                        if (GameObject* door = ObjectAccessor::GetGameObject(*go, m_instance->GetData64(DATA_IRONCLAD_DOOR)))
                        {
                            cannon->SetGoState(GO_STATE_ACTIVE);
                            DoPlaySound(cannon, SOUND_CANNONFIRE);
                            cannon->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
                            DoPlaySound(cannon, SOUND_DESTROYDOOR);
                            door->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
                        }
        }

        void DoPlaySound(GameObject* unit, uint32 sound)
        {
            WorldPacket data(SMSG_PLAY_SOUND, 4);
            data << uint32(sound);
            data << uint64(unit->GetGUID());
            unit->SendMessageToSet(&data, false);
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return GetDeadminesAI<go_defias_cannon_16398_AI>(go);
    }
};

// 48266 npc_defias_cannon
class npc_defias_cannon_48266 : public CreatureScript
{
public:
    npc_defias_cannon_48266() : CreatureScript("npc_defias_cannon_48266") { }

    enum eCannon
    {
        SPELL_CANNON_A = 89697,
        SPELL_CANNON_B = 95495,
        NPC_TARGET_BUNNY = 45979,
        NPC_OGER = 48230,
        NPC_KOBOLD = 48229,
        NPC_DEFIAS = 48522,
    };

    struct npc_defias_cannon_48266AI : public ScriptedAI
    {
        npc_defias_cannon_48266AI(Creature *creature) : ScriptedAI(creature)
        {
            m_instance = creature->GetInstanceScript();
        }

        InstanceScript* m_instance;
        uint32 m_timer;
        uint32 m_phase;
        uint64 m_PlayerGUID;
        uint64 m_BunnyGUID;
        uint64 m_WorkerGUID;
        uint8  m_TargetTyp;
        uint32 m_WorkCounter;

        void Reset()
        {
            m_timer = 1000;
            m_phase = 0;
            m_PlayerGUID = 0;
            m_BunnyGUID = 0;
            m_WorkerGUID = 0;
            m_TargetTyp = 0;
            m_WorkCounter = 0;
        }

        void UpdateAI(uint32 diff)
        {
            if (m_timer < diff)
            {
                m_timer = 1000;
                DoWork();
            }
            else
                m_timer -= diff;

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void DoWork()
        {
            switch (m_phase)
            {
            case 0:
            {
                Creature* oger = me->FindNearestCreature(NPC_OGER, 10.0f);
                Creature* kobold = me->FindNearestCreature(NPC_KOBOLD, 10.0f);
                Creature* defias = me->FindNearestCreature(NPC_DEFIAS, 10.0f);
                if (Creature* bunny = me->FindNearestCreature(NPC_TARGET_BUNNY, 125.0f))
                    if (Player* player = me->FindNearestPlayer(125.0f, true))
                    {
                        m_PlayerGUID = player->GetGUID();
                        m_BunnyGUID = bunny->GetGUID();
                        Creature* worker = nullptr;
                        if (oger && kobold)
                            worker = RAND(oger, kobold);
                        else if (oger)
                            worker = oger;
                        else if (kobold)
                            worker = kobold;
                        else if(defias)
                            worker = defias;

                        if (worker)
                        {
                            m_WorkerGUID = worker->GetGUID();
                            m_WorkCounter = 0;
                            worker->HandleEmote(EMOTE_STATE_WORK);
                            m_phase = 1;
                            m_timer = 5000;
                            return;
                        }
                    }

                if (m_WorkCounter < 2)
                {
                    m_WorkCounter++;
                    if (oger)
                        oger->HandleEmoteState(EMOTE_ONESHOT_NONE);
                    if (kobold)
                    {
                        kobold->HandleEmoteCommand(EMOTE_ONESHOT_NONE);
                        kobold->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                    }
                    if (defias)
                        defias->HandleEmoteState(EMOTE_ONESHOT_NONE);
                }
                break;
            }
            case 1:
            {
				if (Player* player = ObjectAccessor::GetPlayer(*me, m_PlayerGUID))
					if (Creature* bunny = ObjectAccessor::GetCreature(*me, m_BunnyGUID))
						if (Creature* worker = ObjectAccessor::GetCreature(*me, m_WorkerGUID))
                        {
                            float dist = bunny->GetDistance2d(player);
                            if (dist < 10.0f)
                            {
                                m_TargetTyp = 1;
                                me->CastSpell(player, SPELL_CANNON_A, true);
                                worker->HandleEmoteState(EMOTE_ONESHOT_NONE);
                                m_phase = 2;
                                return;
                            }
                            else
                            {
                                m_TargetTyp = 2;
                                me->CastSpell(bunny, SPELL_CANNON_A, true);
                                worker->HandleEmoteState(EMOTE_ONESHOT_NONE);
                                m_phase = 2;
                                return;
                            }
                        }

                m_phase = 0;
                break;
            }
            case 2:
				if (Player* player = ObjectAccessor::GetPlayer(*me, m_PlayerGUID))
					if (Creature* bunny = ObjectAccessor::GetCreature(*me, m_BunnyGUID))
						if (Creature* worker = ObjectAccessor::GetCreature(*me, m_WorkerGUID))
                            if (m_TargetTyp == 1)
                            {
                                me->CastSpell(player, SPELL_CANNON_B, true);
                                worker->HandleEmoteState(EMOTE_ONESHOT_NONE);
                            }
                            else if (m_TargetTyp == 2)
                            {
                                me->CastSpell(bunny, SPELL_CANNON_B, true);
                                worker->HandleEmoteCommand(EMOTE_ONESHOT_NONE);
                                worker->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                            }

                m_TargetTyp = 0;
                m_phase = 0;
                m_timer = urand(11000, 16000);
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDeadminesAI<npc_defias_cannon_48266AI>(creature);
    }
};

void AddSC_deadmines()
{
    new item_defias_gunpowder();
    new go_factory_lever_101831();
    new go_factory_door_13965();
    new go_mastroom_lever_101832();
    new go_mastroom_door_16400();
    new go_foundry_lever_101834();
    new go_foundry_door_16399();
    new go_ironclad_lever_101833();
    new go_ironclad_door_16397();
    new go_defias_cannon_16398();
    new npc_defias_cannon_48266();
}
