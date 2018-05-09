/*
* Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
* Copyright (C) 2011-2018 ArkCORE <http://www.arkania.net/>
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


class npc_hyjal_faerie_dragon_39921 : public CreatureScript
{
public:
    npc_hyjal_faerie_dragon_39921() : CreatureScript("npc_hyjal_faerie_dragon_39921") {}

    enum script_enums
    {
        TWILIGHT_INCITER = 39926,
        SPELL_CAST_JUNIPER_BERRY = 74513,
        SEARCH_STARTED = 1,
        SEARCHING = 2,
        SEARCH_DONE = 3,
        START_ATTACKING = 4,
        TEXT_FOLLOW_ME = 39943,
        TEXT_FINDING = 39944,
        TEXT_INCITER_FOUND_ME = 39945,
    };

    struct npc_hyjal_faerie_dragon_39921AI : public ScriptedAI
    {
        npc_hyjal_faerie_dragon_39921AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap  _events;
        uint8     _seek_stage;
        uint64    _playerGUID, _inciterGUID;

        void Initialize()
        {
        }

        void Reset() override
        {
            _playerGUID = 0;
            _inciterGUID = 0;
            _seek_stage = 0;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (Player* player = caster->ToPlayer())
                if (spell->Id == SPELL_CAST_JUNIPER_BERRY && _seek_stage == 0)
                {
                    _playerGUID = player->GetGUID();
                    _seek_stage = SEARCH_STARTED;

                    MotionMaster* motion_master = me->GetMotionMaster();
                    motion_master->Clear(true);
                    motion_master->MoveIdle();
                    me->SetSpeed(MOVE_RUN, 0.50f, true);

                    me->SetOrientation(me->GetOrientation() + frand(0.5f, 2.0f));
                    Position front_pos = me->GetNearPositionInFront(12 + frand(3,6), 0.1f);
                    motion_master->MovePoint(0, front_pos, true);

                    me->Say(TEXT_FOLLOW_ME);

                    _events.ScheduleEvent(EVENT_CHECK_FOR_PLAYER, 4200);
                }
        }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_FOR_PLAYER:
                {
                    Player* player = ObjectAccessor::GetPlayer(*me, _playerGUID);
                    if (player)
                    {
                        if (_seek_stage == SEARCH_STARTED)
                        {
                            me->SetOrientation(me->GetOrientation() + frand(0.50f, 1.00f));
                            Position front_pos = me->GetNearPositionInFront(8 + frand(1, 2), 0.1f);
                            me->GetMotionMaster()->MovePoint(0, front_pos, true);

                            _seek_stage = SEARCHING;
                            _events.ScheduleEvent(EVENT_CHECK_FOR_PLAYER, 1500);
                        }
                        else if (_seek_stage == SEARCHING)
                        {
                            me->Say(TEXT_FINDING);
                            _seek_stage = SEARCH_DONE;

                            _events.ScheduleEvent(EVENT_CHECK_FOR_PLAYER, 1000);
                        }
                        else if (_seek_stage == SEARCH_DONE)
                        {
                            Creature* creature = DoSpawnCreature(TWILIGHT_INCITER, 0, 0, 0, 0,
                                TEMPSUMMON_DEAD_DESPAWN, 0);

                            if (creature)
                            {
                                _inciterGUID = creature->GetGUID();

                                me->SetOrientation(me->GetOrientation() + frand(.75f, 1.00f));
                                Position front_pos = me->GetNearPositionInFront(frand(2, 3), 0.1f);
                                me->GetMotionMaster()->MovePoint(0, front_pos, true);

                                creature->SetReactState(REACT_PASSIVE);
                                creature->AttackStop();
                                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                
                                creature->GetMotionMaster()->MoveFall();
                                creature->SetFacingTo(creature->GetAngle(player->GetPositionX(), player->GetPositionY()));
                                creature->Say(TEXT_INCITER_FOUND_ME);
                            }

                            _seek_stage = START_ATTACKING;
                            _events.ScheduleEvent(EVENT_CHECK_FOR_PLAYER, 4000);
                        }
                        else if (_seek_stage == START_ATTACKING)
                        {
                            Creature* creature = ObjectAccessor::GetCreature(*me, _inciterGUID);
                            if (creature)
                            {
                                creature->SetReactState(REACT_AGGRESSIVE);
                                creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

                                creature->AddThreat(player, 99999);
                                creature->AI()->AttackStart(player);
                            }

                            me->DespawnOrUnsummon(0);
                        }
                    }


                }
                }
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hyjal_faerie_dragon_39921AI(creature);
    }
};




void AddSC_mount_hyjal()
{
    new npc_hyjal_faerie_dragon_39921();
}
