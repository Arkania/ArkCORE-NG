/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
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
#include "throne_of_the_tides.h"

enum ScriptTexts
{
    SAY_START_EVENT = 0,
    SAY_EVADE       = 1,
};

enum Events
{
    EVENT_SUMMON_DRUDGE = 1,
};

enum Actions
{
    ACTION_LADY_NAZJAR_START_EVENT      = 1,
};

enum Points
{
    POINT_EVADE = 1,
};

enum DataOther
{
    DATA_ATTACKER_GUID  = 1,
};

enum Creatures
{
    NPC_THRONE_OF_THE_TIDES_TELEPORTER_1    = 51391,
    NPC_THRONE_OF_THE_TIDES_TELEPORTER_2    = 51395,
    NPC_NAZJAR_INVADER                      = 39616,
    NPC_NAZJAR_SPIRITMENDER                 = 41139,
    NPC_DEEP_MURLOC_DRUDGE                  = 39960,
    NPC_TEMPEST_WITCH                       = 40634,
};

const Position eventPos[7] = 
{
    {-121.93f, 807.15f, 797.19f, 3.13f},
    {-122.00f, 799.22f, 797.13f, 3.13f},
    {-97.83f, 798.27f, 797.04f, 3.13f},
    {-98.13f, 806.96f, 797.04f, 3.13f},
    {-65.19f, 808.50f, 796.96f, 3.13f},
    {-66.57f, 798.02f, 796.87f, 3.13f},
    {13.67f, 802.34f, 806.43f, 0.12f},
};

/*
intro 1 1 1st floor
5806,643,-463.23f, 804.91f, 250.27f
intro 2 1
5834,643,-148.63f, 802.23f, 796.47f
intro gulthok
5873,643,99.62f, 803.47f, 807.60f
intro right
6017,643,-310.11f, 775.83f, 261.34f
intro left
6018,643,-310.354003906,839.882019043,258.59f
intro 0
6073,643,-651.87f, 807.44f, 270.0f
intro 0 0
6197,643,-660.95f, 807.43f, 244.75f
ozumat 1
6646,643,-198.41f, 981.96f, 230.59f
*/

class at_tott_lady_nazjar_event : public AreaTriggerScript
{
public:
    at_tott_lady_nazjar_event() : AreaTriggerScript("at_tott_lady_nazjar_event") { }

    bool OnTrigger(Player* pPlayer, const AreaTriggerEntry* /*pAt*/)
    {
        if (InstanceScript* pInstance = pPlayer->GetInstanceScript())
        {
            if (pInstance->GetData(DATA_LADY_NAZJAR_EVENT) != DONE
                && pInstance->GetBossState(DATA_COMMANDER_ULTHOK) != DONE)
            {
                pInstance->SetData(DATA_LADY_NAZJAR_EVENT, DONE);
                if (Creature* pLadyNazjarEvent = ObjectAccessor::GetCreature(*pPlayer, pInstance->GetData64(DATA_LADY_NAZJAR_EVENT)))
                    pLadyNazjarEvent->AI()->DoAction(ACTION_LADY_NAZJAR_START_EVENT);
            }
        }
        return true;
    }
};

const Position teleporterPos[2] = 
{
    {-560.25f, 819.19f, 245.28f, 5.20f}, // entrance;
    {-14.72f, 796.57f, 808.12f, 1.99f}, // upper
};

// 51391 51395
class npc_throne_of_the_tides_teleporter : public CreatureScript
{
    public:
        npc_throne_of_the_tides_teleporter() : CreatureScript("npc_throne_of_the_tides_teleporter"){ }

        bool OnGossipHello(Player* pPlayer, Creature* creature)
        {
            if (pPlayer->IsInCombat())
                return false;
            switch (creature->GetEntry())
            {
            case NPC_THRONE_OF_THE_TIDES_TELEPORTER_1:
                    pPlayer->NearTeleportTo(teleporterPos[1].GetPositionX(),
                        teleporterPos[1].GetPositionY(),
                        teleporterPos[1].GetPositionZ(),
                        teleporterPos[1].GetOrientation());
                    return false;
                break;
            case NPC_THRONE_OF_THE_TIDES_TELEPORTER_2:
                pPlayer->NearTeleportTo(teleporterPos[0].GetPositionX(),
                    teleporterPos[0].GetPositionY(),
                    teleporterPos[0].GetPositionZ(),
                    teleporterPos[0].GetOrientation());
                break;
            }
            return false;
        }
};

class npc_lady_nazjar_event : public CreatureScript
{
    public:
        npc_lady_nazjar_event() : CreatureScript("npc_lady_nazjar_event") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_lady_nazjar_eventAI (creature);
        }

        struct npc_lady_nazjar_eventAI : public ScriptedAI
        {
            npc_lady_nazjar_eventAI(Creature* creature) : ScriptedAI(creature)
            {
                pInstance = creature->GetInstanceScript();
            }

            InstanceScript* pInstance;
            EventMap events;
            bool bEvade;

            void Reset()
            {
                if (!pInstance)
                    return;

                if(pInstance->GetData(DATA_LADY_NAZJAR_EVENT) == DONE)
                    me->DespawnOrUnsummon();

                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_PASSIVE);
                me->setActive(true);
                bEvade = false;
                events.Reset();
            }

            void MovementInform(uint32 type, uint32 id)
            {
                if (type == POINT_MOTION_TYPE)
                {
                    if (id == POINT_EVADE)
                        me->DespawnOrUnsummon();
                }
            }

            void DoAction(int32 action)
            {
                if (action == ACTION_LADY_NAZJAR_START_EVENT)
                {
                    Talk(SAY_START_EVENT);
                    me->SummonCreature(NPC_NAZJAR_INVADER, eventPos[0]);
                    me->SummonCreature(NPC_NAZJAR_INVADER, eventPos[1]);
                    me->SummonCreature(NPC_NAZJAR_INVADER, eventPos[2]);
                    me->SummonCreature(NPC_TEMPEST_WITCH, eventPos[3]);
                    me->SummonCreature(NPC_NAZJAR_SPIRITMENDER, eventPos[4]);
                    me->SummonCreature(NPC_NAZJAR_SPIRITMENDER, eventPos[5]);
                }
            }

            void UpdateAI(uint32 /*diff*/)
            {
                if(!pInstance)
                    return;

                if (me->SelectNearestTarget(50.0f) && !bEvade)
                {
                    bEvade = true;
                    Talk(SAY_EVADE);
                    me->GetMotionMaster()->MovePoint(POINT_EVADE, eventPos[6]);
                }
            }
        };
};

// 203199
class go_totd_defense_system : public GameObjectScript
{
public:
    go_totd_defense_system() : GameObjectScript("go_totd_defense_system") { }

    bool OnGossipHello(Player* /*player*/, GameObject* go)
    {
        if(go->GetInstanceScript())
        {
            Map::PlayerList const &PlayerList = go->GetMap()->GetPlayers();

            if (!PlayerList.isEmpty())
                for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    i->GetSource()->SendCinematicStart(169);
        }
        return false;
    }
};

void AddSC_throne_of_the_tides()
{
    new npc_lady_nazjar_event();
    new go_totd_defense_system();
    new npc_throne_of_the_tides_teleporter();
    new at_tott_lady_nazjar_event();
}