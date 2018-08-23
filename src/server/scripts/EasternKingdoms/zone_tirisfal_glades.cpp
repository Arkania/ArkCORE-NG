/*
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

#include "Vehicle.h"

// npc_aradne 50372
class npc_aradne_50372 : public CreatureScript
{
public:
    npc_aradne_50372() : CreatureScript("npc_aradne_50372") { }

    enum eAradne
    {
        SPELL_RAISE_UNDEAD = 93446,
        EVENT_RISE_DEAD = 901,
        EVENT_START_TALK,
    };

    struct npc_aradne_50372AI : public ScriptedAI
    {
        npc_aradne_50372AI(Creature *c) : ScriptedAI(c) { }

        EventMap m_events;

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == WAYPOINT_MOTION_TYPE)
                switch (id)
                {
                case 5:
                case 7:
                case 12:
                case 17:
                case 22:
                case 25:
                    m_events.ScheduleEvent(EVENT_RISE_DEAD, 100);
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
                case EVENT_RISE_DEAD:
                    if (Creature* npc = me->FindNearestCreature(50373, 15.0f))
                        npc->CastSpell(npc, SPELL_RAISE_UNDEAD, true);

                    m_events.ScheduleEvent(EVENT_START_TALK, 1000);
                    break;
                case EVENT_START_TALK:
                    Talk(0);
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const  override
    {
        return new npc_aradne_50372AI(pCreature);
    }
};

// Deathknell Grave Target 50373
class npc_deathknell_grave_target : public CreatureScript
{
public:
    npc_deathknell_grave_target() : CreatureScript("npc_deathknell_grave_target") { }

    enum eRisenDead
    {
        SPELL_DIRT_EXPLOSION = 89199,
        SPELL_CHURNING_DIRT = 92788,
        SPELL_RIDE_UNDEAD = 93446,
    };

    struct npc_deathknell_grave_targetAI : public ScriptedAI
    {
        npc_deathknell_grave_targetAI(Creature *c) : ScriptedAI(c) {}

        uint32 m_timer;
        uint32 m_phase;

        void Reset()  override
        {
            m_timer = 0;
            m_phase = 0;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) 
        { 
            if (spell->Id == SPELL_RIDE_UNDEAD)
            {
                m_timer = 100;
                m_phase = 1;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_timer <= diff)
            {
                m_timer = 1000;
                DoWork();
            }
            else m_timer -= diff;
        }

        void DoWork()
        {
            switch (m_phase)
            {
                case 1:
                    me->AddAura(SPELL_DIRT_EXPLOSION, me);
                    DoCast(me, SPELL_CHURNING_DIRT);
                    m_phase = 2;
                    break;
                case 2:
                    if (Creature* npc = me->SummonCreature(50374, me->GetPosition(), TEMPSUMMON_TIMED_DESPAWN, 30000))
                    {
                    }

                    m_phase = 3;
                    m_timer = 3000;
                    break;
                case 3:
                    me->RemoveAllAuras();
                    m_phase = 4;
                    break;
                case 4:
                    m_timer = 0;
                    m_phase = 0;
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const  override
    {
        return new npc_deathknell_grave_targetAI(pCreature);
    }
};

// npc_risen_dead 50374
class npc_risen_dead : public CreatureScript
{
public:
    npc_risen_dead() : CreatureScript("npc_risen_dead") { }

    enum eNpc
    {
        EVENT_START_ANIM = 901,
        EVENT_SHOW_DEAD,
        EVENT_SHOW_LIFE,
        EVENT_SHOW_RUNNING,
        EVENT_SHOW_DEAD1,
        EVENT_SHOW_DEAD2,
        EVENT_SHOW_DEAD3,
        EVENT_SHOW_DEAD4,
        EVENT_SHOW_LIFE1,
        EVENT_SHOW_LIFE2,
        EVENT_SHOW_LIFE3,
        EVENT_SHOW_RUNNING1,
        EVENT_SHOW_RUNNING2,
        EVENT_SHOW_RUNNING3,
    };

    struct npc_risen_deadAI : public ScriptedAI
    {
        npc_risen_deadAI(Creature *c) : ScriptedAI(c) {}

        EventMap m_events;
        uint32 m_WishToBeDead;

        void Reset()  override
        {           
            m_WishToBeDead = urand(0, 100);
            m_events.RescheduleEvent(EVENT_START_ANIM, 1000);
        }
     
        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_ANIM:
                    if (m_WishToBeDead < 33)
                        m_events.ScheduleEvent(EVENT_SHOW_DEAD, 1000);
                    else if (m_WishToBeDead < 66)
                        m_events.ScheduleEvent(EVENT_SHOW_LIFE, 1000);
                    else
                       m_events.ScheduleEvent(EVENT_SHOW_RUNNING, 1000);
                    break;
                case EVENT_SHOW_DEAD:
                    me->HandleEmote(EMOTE_ONESHOT_QUESTION);
                    m_events.ScheduleEvent(EVENT_SHOW_DEAD1, 100);
                    break;
                case EVENT_SHOW_DEAD1:
                    Talk(0);
                    m_events.ScheduleEvent(EVENT_SHOW_DEAD2, 6000);
                    break;
                case EVENT_SHOW_DEAD2:
                    Talk(1);
                    m_events.ScheduleEvent(EVENT_SHOW_DEAD3, 6000);
                    break;
                case EVENT_SHOW_DEAD3:
                    Talk(8);
                    m_events.ScheduleEvent(EVENT_SHOW_DEAD4, 6000);
                    break;
                case EVENT_SHOW_DEAD4:
                    me->Kill(me);
                    break;
                case EVENT_SHOW_LIFE:
                    me->HandleEmote(EMOTE_ONESHOT_QUESTION);
                    m_events.ScheduleEvent(EVENT_SHOW_LIFE1, 100);
                    break;
                case EVENT_SHOW_LIFE1:
                    Talk(4);
                    m_events.ScheduleEvent(EVENT_SHOW_LIFE2, 6000);
                    break;
                case EVENT_SHOW_LIFE2:
                    Talk(5);
                    m_events.ScheduleEvent(EVENT_SHOW_LIFE3, 6000);
                    break;
                case EVENT_SHOW_LIFE3:
                    Talk(9);
                    me->GetMotionMaster()->MovePath(5037401, false);
                    break;
                case EVENT_SHOW_RUNNING:
                    me->HandleEmote(EMOTE_ONESHOT_QUESTION);
                    m_events.ScheduleEvent(EVENT_SHOW_RUNNING1, 100);
                    break;
                case EVENT_SHOW_RUNNING1:
                    Talk(2);
                    m_events.ScheduleEvent(EVENT_SHOW_RUNNING2, 6000);
                    break;
                case EVENT_SHOW_RUNNING2:
                    Talk(3);
                    m_events.ScheduleEvent(EVENT_SHOW_RUNNING3, 6000);
                    break;
                case EVENT_SHOW_RUNNING3:
                    Talk(7);
                    me->HandleEmote(EMOTE_ONESHOT_CRY);
                    me->GetMotionMaster()->MovePath(5037402, false);
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const  override
    {
        return new npc_risen_deadAI(pCreature);
    }
};

// npc_undertaker_mordo 1568
class npc_undertaker_mordo : public CreatureScript
{
public:
    npc_undertaker_mordo() : CreatureScript("npc_undertaker_mordo") { }

    enum eNpc
    {
        EVENT_START_ANIM = 901,
        EVENT_MASTER_RESET,
        EVENT_START_TALK,
        EVENT_ANIM_PART_01,
        EVENT_ANIM_PART_02,
        EVENT_ANIM_PART_03,
        EVENT_ANIM_PART_04,
        EVENT_ANIM_PART_05,
        EVENT_ANIM_PART_06,
        EVENT_ANIM_PART_07,
        EVENT_ANIM_PART_08,
        EVENT_ANIM_PART_09,
        EVENT_ANIM_PART_10,
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) 
    { 
        if (!player->hasQuest(28608))
            if (quest->GetQuestId() == 28608)
            {
                player->CastSpell(player, 91576);
            }

        return false; 
    }

    struct npc_undertaker_mordoAI : public ScriptedAI
    {
        npc_undertaker_mordoAI(Creature *c) : ScriptedAI(c) {}

        EventMap m_events;
        uint64   m_targetGUID;

        void Reset()  override
        {
            m_targetGUID = 0;
            m_events.RescheduleEvent(EVENT_START_ANIM, urand(50000, 70000));
            m_events.RescheduleEvent(EVENT_MASTER_RESET, 150000);
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
                    if (Creature* npc_trigger = me->FindNearestCreature(50373, 20.0f))
                        if (Creature* target = me->SummonCreature(50414, npc_trigger->GetPosition(), TEMPSUMMON_TIMED_DESPAWN, 40000))
                        {
                            m_targetGUID = target->GetGUID();
                            Position pos = me->GetNearPosition(1.5f, 1.72f);
                            target->GetMotionMaster()->MovePoint(0, pos, true);
                            m_events.ScheduleEvent(EVENT_START_TALK, 1000);
                        }
                    break;
                }
                case EVENT_MASTER_RESET:
                    Reset();
                    break;
                case EVENT_START_TALK:
                {
                    Talk(0);
                    m_events.ScheduleEvent(EVENT_ANIM_PART_01, 3000);
                    m_events.RescheduleEvent(EVENT_MASTER_RESET, 150000);
                    break;
                }
                case EVENT_ANIM_PART_01:
                {
                    if (Creature* target = ObjectAccessor::GetCreature(*me, m_targetGUID))
                    {
                        target->SetUInt32Value(UNIT_FIELD_BYTES_1, UNIT_STAND_STATE_KNEEL);
                        target->SetFacingToObject(me);
                        m_events.ScheduleEvent(EVENT_ANIM_PART_02, 750);
                    }
                    break;
                }
                case EVENT_ANIM_PART_02:
                {
                    me->HandleEmoteState(EMOTE_STATE_USE_STANDING);
                    m_events.ScheduleEvent(EVENT_ANIM_PART_03, 6000);
                    break;
                }
                case EVENT_ANIM_PART_03:
                {
                    me->HandleEmoteState(EMOTE_ONESHOT_NONE);
                    m_events.ScheduleEvent(EVENT_ANIM_PART_04, 750);
                    break;
                }
                case EVENT_ANIM_PART_04:
                {
                    me->HandleEmote(EMOTE_ONESHOT_POINT);
                    m_events.ScheduleEvent(EVENT_ANIM_PART_05, 2500);
                    break;
                }
                case EVENT_ANIM_PART_05:
                {
                    Talk(1);
                    m_events.ScheduleEvent(EVENT_ANIM_PART_06, 250);
                    break;
                }
                case EVENT_ANIM_PART_06:
                {
                    if (Creature* target = ObjectAccessor::GetCreature(*me, m_targetGUID))
                    {
                        target->AddAura(93460, target);
                        target->CastSpell(target, 93460);
                        target->SetDisplayId(36775);
                        target->SetUInt32Value(UNIT_FIELD_BYTES_1, UNIT_STAND_STATE_STAND);
                        m_events.ScheduleEvent(EVENT_ANIM_PART_07, 2500);
                    }
                    break;
                }
                case EVENT_ANIM_PART_07:
                {
                    if (Creature* target = ObjectAccessor::GetCreature(*me, m_targetGUID))
                    {
                        target->HandleEmote(EMOTE_ONESHOT_TALK);
                        target->AI()->Talk(0);
                        m_events.ScheduleEvent(EVENT_ANIM_PART_08, 3750);
                    }
                    break;
                }
                case EVENT_ANIM_PART_08:
                {
                    if (Creature* target = ObjectAccessor::GetCreature(*me, m_targetGUID))
                    {
                        target->HandleEmote(EMOTE_ONESHOT_SALUTE);
                        m_events.ScheduleEvent(EVENT_ANIM_PART_09, 2500);
                    }
                    break;
                }
                case EVENT_ANIM_PART_09:
                {
                    if (Creature* target = ObjectAccessor::GetCreature(*me, m_targetGUID))
                    {
                        target->GetMotionMaster()->MovePath(5041401, false);
                        m_events.ScheduleEvent(EVENT_ANIM_PART_10, 45000);
                        m_events.RescheduleEvent(EVENT_START_ANIM, urand(50000, 70000));
                        m_events.RescheduleEvent(EVENT_MASTER_RESET, 150000);
                    }
                    break;
                }
                case EVENT_ANIM_PART_10:
                {
                    if (Creature* target = ObjectAccessor::GetCreature(*me, m_targetGUID))
                    {
                        target->DespawnOrUnsummon();                        
                    }
                    break;
                }
                }
            }
        }
    };
 
    CreatureAI* GetAI(Creature* pCreature) const  override
    {
        return new npc_undertaker_mordoAI(pCreature);
    }
};

// npc_darnell 49141
class npc_darnell_49141 : public CreatureScript
{
public:
    npc_darnell_49141() : CreatureScript("npc_darnell_49141") { }

    enum ePlaceDescription
    {
        Unknown = 0,
        Outsite,
        Entrance,
        Stairs1,
        Stairs2,
        Ground,
    };

    struct npc_darnell_49141AI : public ScriptedAI
    {
        npc_darnell_49141AI(Creature *c) : ScriptedAI(c) {}

        void Reset()  override
        {
            m_timer = urand(30000, 45000);
            m_phase = 0;
            m_modus = 0;

            if (Unit* npc = me->GetCharmerOrOwner())
                if (m_player = npc->ToPlayer())
                    if (m_player->GetQuestStatus(28608) == QUEST_STATUS_INCOMPLETE)
                    {
                        m_modus = 1; 
                        m_phase = 1;
                        m_timer = 1000;
                        m_counter = 0;
                        m_path = 0;
                        m_FoundGround = false;
                        m_ItemsFound = false;
                        m_OldPosition = m_player->GetPosition();
                        m_player_pos = m_player->GetPosition();
                        m_player_area = m_player->GetAreaId();
                        Talk(0, m_player);
                    }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (!CheckPlayerValid())
                return;

            if (type == POINT_MOTION_TYPE)
                m_arrived = true;
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (who->GetGUID() != m_player->GetGUID())
                return;

            m_player_pos = who->GetPosition();
            m_player_area = who->GetAreaId();

            if (m_modus == 1 && me->GetMotionMaster()->GetCurrentMovementGeneratorType() != FOLLOW_MOTION_TYPE)
                if (m_arrived)
                    if (me->GetDistance(m_player) < 4.0f)
                        me->GetMotionMaster()->MoveFollow(m_player, 0.0f, 0.0f);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!CheckPlayerValid())
                return;

            if (m_timer <= diff)
            {
                m_timer = 1000;
                DoWork();
            }
            else m_timer -= diff;
        }

        void DoWork()
        {
            if (m_FoundGround)
            {
                SearchOnGround();
                return;
            }

            switch (GetPlaceDescription())
            {
                case ePlaceDescription::Outsite:
                    InviteToFollow();
                    break;
                case ePlaceDescription::Entrance:
                    InviteToFollowDeeper1();
                    break;
                case ePlaceDescription::Stairs1:
                    InviteToFollowDeeper2();
                    break;
                case ePlaceDescription::Stairs2:
                    InviteToFollowToGround();
                    break;
                case ePlaceDescription::Ground:
                    SearchOnGround();
                    break;
            }
        }

        void InviteToFollow() 
        {
            m_counter++;
            if (GetMovedPlayerDistance() > 1.0f)
                m_counter = 0;

            if (m_counter >= 10)
            {
                Talk(1); // this way
                me->GetMotionMaster()->MovePoint(1, 1665.368896f, 1662.722656f, 141.850983f);
                m_path = 1;
                m_arrived = false;
                m_counter = 0;
            }
        }

        void InviteToFollowDeeper1() 
        {
            m_counter++;
            if (GetMovedPlayerDistance() > 1.0f)
                m_counter = 0;

            if (m_counter >= 10)
            {
                Talk(2); // this way
                me->GetMotionMaster()->MovePoint(2, 1642.761963f, 1662.547729f, 132.477753f);
                m_path = 2;
                m_arrived = false;
                m_counter = 0;
            }
        }

        void InviteToFollowDeeper2()
        {
            m_counter++;
            if (GetMovedPlayerDistance() > 1.0f)
                m_counter = 0;

            if (m_counter >= 10)
            {
                Talk(2); // this way
                me->GetMotionMaster()->MovePoint(3, 1642.498779f, 1677.809937f, 126.932129f);
                m_path = 3;
                m_arrived = false;
                m_counter = 0;
            }
        }

        void InviteToFollowToGround()
        {
            m_counter++;
            if (GetMovedPlayerDistance() > 1.0f)
                m_counter = 0;

            if (m_counter >= 10)
            {
                Talk(2); // this way
                me->GetMotionMaster()->MovePoint(4, 1656.714478f, 1678.538330f, 120.718788f);
                m_path = 4;
                m_arrived = false;
                m_counter = 0;
            }
        }

        void SearchOnGround()
        {
            if (CheckPlayerFoundItems())
            {
                if (m_ItemsFound == false)
                {
                    m_ItemsFound = true;
                    Talk(9);
                    m_timer = 10000;
                    return;
                }
                else
                {
                    //me->DespawnOrUnsummon(0);
                    return;
                }
            }
                

            switch (m_modus)
            {
                case 2: 
                    MoveToCenter();
                    break;
                case 3: // go to random corner
                    MoveToRandomCorner();
                    break;
                case 4: // say searching
                    SearchingOnCorner();
                    break;
                case 5: // found
                    break;
                default:
                    m_modus = 2;
                    break;
            }
        }

        void MoveToCenter()
        {
            if (m_path != 8)
            {
                me->GetMotionMaster()->MovePoint(8, 1664.128052f, 1679.201294f, 120.530205f);
                m_arrived = false;
                m_path = 8;
            }
            else if (m_arrived == false)
            { }
            else
            {
                m_modus = 3;
            }
        }

        void MoveToRandomCorner()
        {
            if (m_path == 8)
            {
                switch (urand(1, 4))
                {
                case 1:
                    me->GetMotionMaster()->MovePoint(4, 1663.849609f, 1694.495239f, 120.719284f);
                    m_arrived = false;
                    m_path = 4;
                    break;
                case 2:
                    me->GetMotionMaster()->MovePoint(5, 1672.939331f, 1668.029541f, 120.719307f);
                    m_arrived = false;
                    m_path = 5;
                    break;
                case 3:
                    me->GetMotionMaster()->MovePoint(6, 1656.963379f, 1667.456299f, 120.719093f);
                    m_arrived = false;
                    m_path = 6;
                    break;
                case 4:
                    me->GetMotionMaster()->MovePoint(7, 1656.098999f, 1688.312866f, 120.719093f);
                    m_arrived = false;
                    m_path = 7;
                    break;
                }
            }
            else if (m_arrived == false)
            {  }
            else
            {
                m_modus = 4;
            }
        }

        void SearchingOnCorner()
        {
            Talk(urand(3, 8));
            m_timer = 6000;
            m_modus = 2;
        }

        bool CheckPlayerFoundItems()
        {
            if (m_player->HasItemCount(64582) && m_player->HasItemCount(64581))
                return true;

            return false;
        }

        bool CheckPlayerValid()
        {
            if (!m_player->IsInWorld() || 
                m_player->IsDead() ||
                m_player->GetQuestStatus(28608) != QUEST_STATUS_INCOMPLETE ||
                (m_player->GetAreaId() != 5692 && m_player->GetAreaId() != 2117))
            {
                me->DespawnOrUnsummon(); return false;
            }

            return true;
        }

        ePlaceDescription GetPlaceDescription()
        {
            switch (m_player_area)
            {
                case 5692:
                    return ePlaceDescription::Outsite;
                case 2117:
                {
                    if (m_player_pos.GetPositionZ() < 123.0)
                    {
                        m_FoundGround = true;
                        return ePlaceDescription::Ground;
                    }

                    if (m_player_pos.GetPositionZ() < 127.0)
                        return ePlaceDescription::Stairs2;

                    if (m_player_pos.GetPositionZ() < 133.0)
                        return ePlaceDescription::Stairs1;

                    return ePlaceDescription::Entrance;
                }
                default:
                    return ePlaceDescription::Unknown;
            }
        }

        float GetMovedPlayerDistance()
        {
            float dist = m_player->GetDistance(m_OldPosition);
            m_OldPosition = m_player->GetPosition();
            return dist;
        }

    private:
        bool m_arrived;
        uint32 m_counter;
        Position m_OldPosition;
        Position m_player_pos;
        uint32 m_player_area;
        uint8 m_path;
        uint8 m_modus;
        uint32 m_timer;
        uint32 m_phase;
        Player* m_player;
        bool m_FoundGround;
        bool m_ItemsFound;
    };

    CreatureAI* GetAI(Creature* pCreature) const  override
    {
        return new npc_darnell_49141AI(pCreature);
    }
};

// npc_marshal_redpath_49230
class npc_marshal_redpath_49230 : public CreatureScript
{
public:
    npc_marshal_redpath_49230() : CreatureScript("npc_marshal_redpath_49230") { }

    enum eMarshal
    {
        QUEST_THE_WAKENING = 24960,
    };

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (player->GetQuestStatus(QUEST_THE_WAKENING) == QUEST_STATUS_INCOMPLETE)
            return false;

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        if (player->GetQuestStatus(24960) == QUEST_STATUS_INCOMPLETE)
        {
            uint32 id = player->PlayerTalkClass->GetGossipMenu().GetMenuId();
            if (id == 17567 && player->GetReqKillOrCastCurrentCount(QUEST_THE_WAKENING, 49230) == 0)
            {
                player->PlayerTalkClass->SendCloseGossip();
                CAST_AI(npc_marshal_redpath_49230AI, creature->AI())->StartAnim(player);
            }
        }
        return false;
    }

    struct npc_marshal_redpath_49230AI : public ScriptedAI
    {
        npc_marshal_redpath_49230AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;
        Player* m_player;

        void Reset()  override
        {
            m_timer = 0;
            m_phase = 0;
            m_player = nullptr;
        }

        void StartAnim(Player* player)
        {
            if (!m_phase)
            {
                m_player = player;
                m_phase = 1;
                m_timer = 100;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_timer <= diff)
            {
                m_timer = 1000;
                DoWork();
            }
            else m_timer -= diff;
        }

        void DoWork()
        {
            switch (m_phase)
            {
            case 1:
                Talk(1, m_player);
                m_timer = 2000;
                m_phase = 2;
                break;
            case 2:
                if (m_player)
                    m_player->KilledMonsterCredit(49230);

                m_timer = 4000;
                m_phase = 3;
                break;
            case 3:
                me->GetMotionMaster()->MovePath(4923001, false);
                m_timer = 10000;
                m_phase = 4;
                break;
            case 4:
                me->DespawnOrUnsummon();
                m_timer = 0;
                m_phase = 0;
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const  override
    {
        return new npc_marshal_redpath_49230AI(pCreature);
    }
};

// npc_valdred_moray_49231
class npc_valdred_moray_49231 : public CreatureScript
{
public:
    npc_valdred_moray_49231() : CreatureScript("npc_valdred_moray_49231") { }

    enum eValdred
    {
        QUEST_THE_WAKENING = 24960,
    };

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (player->GetQuestStatus(QUEST_THE_WAKENING) == QUEST_STATUS_INCOMPLETE)
            return false;

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        if (player->GetQuestStatus(QUEST_THE_WAKENING) == QUEST_STATUS_INCOMPLETE)
        {
            uint32 id = player->PlayerTalkClass->GetGossipMenu().GetMenuId();
            if (id == 12488 && player->GetReqKillOrCastCurrentCount(QUEST_THE_WAKENING, 49231) == 0)
            {
                player->PlayerTalkClass->SendCloseGossip();
                CAST_AI(npc_valdred_moray_49231AI, creature->AI())->StartAnim(player);
            }
        }

        return false;
    }

    struct npc_valdred_moray_49231AI : public ScriptedAI
    {
        npc_valdred_moray_49231AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;
        Player* m_player;

        void Reset()  override
        {
            m_timer = 0;
            m_phase = 0;
            m_player = nullptr;
        }

        void StartAnim(Player* player)
        {
            if (!m_phase)
            {
                m_player = player;
                m_phase = 1;
                m_timer = 100;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_timer <= diff)
            {
                m_timer = 1000;
                DoWork();
            }
            else m_timer -= diff;
        }

        void DoWork()
        {
            switch (m_phase)
            {
            case 1:
                Talk(1, m_player);
                m_timer = 2000;
                m_phase = 2;
                break;
            case 2:
                if (m_player)
                    m_player->KilledMonsterCredit(49231);

                m_timer = 4000;
                m_phase = 3;
                break;
            case 3:
                me->GetMotionMaster()->MovePath(4923101, false);
                m_timer = 10000;
                m_phase = 4;
                break;
            case 4:
                me->DespawnOrUnsummon();
                m_timer = 0;
                m_phase = 0;
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const  override
    {
        return new npc_valdred_moray_49231AI(pCreature);
    }
};

// npc_lilian_voss_38895
class npc_lilian_voss_38895 : public CreatureScript
{
public:
    npc_lilian_voss_38895() : CreatureScript("npc_lilian_voss_38895") { }

    enum eLilian
    {
        QUEST_THE_WAKENING = 24960,
    };

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (player->GetQuestStatus(QUEST_THE_WAKENING) == QUEST_STATUS_INCOMPLETE)
            return false;

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        if (player->GetQuestStatus(QUEST_THE_WAKENING) == QUEST_STATUS_INCOMPLETE)
        {
            uint32 id = player->PlayerTalkClass->GetGossipMenu().GetMenuId();
            if (id == 17565 && player->GetReqKillOrCastCurrentCount(QUEST_THE_WAKENING, 38895) == 0)
            {
                player->PlayerTalkClass->SendCloseGossip();
                CAST_AI(npc_lilian_voss_38895AI, creature->AI())->StartAnim(player);
            }
        }

        return false;
    }

    struct npc_lilian_voss_38895AI : public ScriptedAI
    {
        npc_lilian_voss_38895AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;
        Player* m_player;

        void Reset()  override
        {
            m_timer = 0;
            m_phase = 0;
            m_player = nullptr;
        }

        void StartAnim(Player* player)
        {
            if (!m_phase)
            {
                m_player = player;
                m_phase = 1;
                m_timer = 100;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_timer <= diff)
            {
                m_timer = 1000;
                DoWork();
            }
            else m_timer -= diff;
        }

        void DoWork()
        {
            switch (m_phase)
            {
            case 1:
                Talk(1, m_player);
                m_timer = 2000;
                m_phase = 2;
                break;
            case 2:
                if (m_player)
                    m_player->KilledMonsterCredit(38895);

                m_timer = 5000;
                m_phase = 3;
                break;
            case 3:
                me->GetMotionMaster()->MovePath(3889501, false);
                m_timer = 10000;
                m_phase = 4;
                break;
            case 4:
                me->DespawnOrUnsummon();
                m_timer = 0;
                m_phase = 0;
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const  override
    {
        return new npc_lilian_voss_38895AI(pCreature);
    }
};

// npc_deathguard_saltain 1740
class npc_deathguard_saltain : public CreatureScript
{
public:
    npc_deathguard_saltain() : CreatureScript("npc_deathguard_saltain") { }

    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest) 
    { 
        if (quest->GetQuestId() == 26800)
        {
            player->CastSpell(player, 91938);
        }

        return false; 
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/) 
    {
        switch (quest->GetQuestId())
        {
        case 26800:
        { 
            if (Creature* darnell = GetDarnell(player))
                if (Vehicle* npc = darnell->GetVehicleKit())
                {
                    npc->RemoveAllPassengers();
                    darnell->DespawnOrUnsummon(1000);
                }

            break; 
        }
        }
        return false; 
    }

    Creature* GetDarnell(Player* player)
    {
        for (Unit::ControlList::const_iterator itr = player->m_Controlled.begin(); itr != player->m_Controlled.end(); ++itr)
            if ((*itr)->GetEntry() == 49337)
                return (*itr)->ToCreature();

        return nullptr;
    }
};

// npc_darnell 49337
class npc_darnell_49337 : public CreatureScript
{
public:
    npc_darnell_49337() : CreatureScript("npc_darnell_49337") { }

    enum eQuest
    {
        NPC_SCARLET_CORPSE_49340 = 49340,
    };

    struct npc_darnell_49337AI : public VehicleAI
    {
        npc_darnell_49337AI(Creature *c) : VehicleAI(c) { }

        uint8 m_seat;
        uint64 m_scarletGUID;

        void Reset()  override
        {
            m_seat = 0;
            m_scarletGUID = 0;
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override 
        { 
            if (!apply)
                if (Creature* scarlet = passenger->ToCreature())
                {
                    scarlet->SetDisableGravity(false);
                    scarlet->DespawnOrUnsummon(500);
                }
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case NPC_SCARLET_CORPSE_49340:
            {
                m_scarletGUID = guid;
                break;
            }
            }
        }

        void DoAction(int32 param) override 
        { 
            if (param == 1)
                if (Creature* scarlet = ObjectAccessor::GetCreature(*me, m_scarletGUID))
                {
                    me->CastSpell(scarlet, 91945, true);
                    scarlet->AddAura(46598, scarlet);
                    scarlet->SetDisableGravity(true);
                    scarlet->EnterVehicle(me, m_seat);
                    m_seat++;
                    me->CastSpell(scarlet, 91935, true);
                }
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const  override
    {
        return new npc_darnell_49337AI(pCreature);
    }
};

// npc_scarlet_corpse_49340
class npc_scarlet_corpse_49340 : public CreatureScript
{
public:
    npc_scarlet_corpse_49340() : CreatureScript("npc_scarlet_corpse_49340") { }

    struct npc_scarlet_corpse_49340AI : public ScriptedAI
    {
        npc_scarlet_corpse_49340AI(Creature *c) : ScriptedAI(c) {}

        void SpellHit(Unit* caster, SpellInfo const* spell) 
        { 
            if (Player* player = caster->ToPlayer())
                if (player->GetQuestStatus(26800) == QUEST_STATUS_INCOMPLETE)
                    if (Creature* darnell = GetDarnell(player))
                    {
                        darnell->AI()->SetGUID(me->GetGUID(), me->GetEntry());
                        darnell->AI()->DoAction(1);
                    }
        }

        Creature* GetDarnell(Player* player)
        {
            for (Unit::ControlList::const_iterator itr = player->m_Controlled.begin(); itr != player->m_Controlled.end(); ++itr)
                if ((*itr)->GetEntry() == 49337)
                    return (*itr)->ToCreature();

            return nullptr;
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const  override
    {
        return new npc_scarlet_corpse_49340AI(pCreature);
    }
};

// npc_lilian_voss_38910
class npc_lilian_voss_38910 : public CreatureScript
{
public:
    npc_lilian_voss_38910() : CreatureScript("npc_lilian_voss_38910") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        uint32 id = player->PlayerTalkClass->GetGossipMenu().GetMenuId();
        if (player->GetReqKillOrCastCurrentCount(24961, 38910) == 0)
            if (player->GetQuestStatus(24961) == QUEST_STATUS_INCOMPLETE && id == 15486)
            {
                player->PlayerTalkClass->SendCloseGossip();
                CAST_AI(npc_lilian_voss_38910AI, creature->AI())->StartAnim(player);
                return false;
            }

        return false;
    }

    struct npc_lilian_voss_38910AI : public ScriptedAI
    {
        npc_lilian_voss_38910AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;
        Player* m_player;

        void Reset()  override
        {
            m_timer = 0;
            m_phase = 0;
            m_player = nullptr;
        }

        void StartAnim(Player* player)
        {
            if (!m_phase)
            {
                m_player = player;
                m_phase = 1;
                m_timer = 100;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_timer <= diff)
            {
                m_timer = 1000;
                DoWork();
            }
            else m_timer -= diff;
        }

        void DoWork()
        {
            switch (m_phase)
            {
            case 1:

                m_timer = 2000;
                m_phase = 2;
                break;
            case 2:
                Talk(0);
                if (m_player)
                    m_player->KilledMonsterCredit(38910);

                m_timer = 5000;
                m_phase = 3;
                break;
            case 3:
                me->GetMotionMaster()->MovePath(3891001, false);
                m_timer = 10000;
                m_phase = 4;
                break;
            case 4:
                me->DespawnOrUnsummon();
                m_timer = 0;
                m_phase = 0;
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const  override
    {
        return new npc_lilian_voss_38910AI(pCreature);
    }
};

// showfight npc_rotbrain_berserker 49422
class npc_rotbrain_berserker : public CreatureScript
{
public:
    npc_rotbrain_berserker() : CreatureScript("npc_rotbrain_berserker") { }

    struct npc_rotbrain_berserkerAI : public ScriptedAI
    {
        npc_rotbrain_berserkerAI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;
        float m_health;

        void Reset()  override
        {
            m_timer = 1000;
            m_phase = 0;
            m_health = frand(60.0f, 95.0f);
        }

        void DamageTaken(Unit* attacker, uint32& damage) 
        {
            if (attacker->GetEntry() == 49428 && me->GetHealthPct() < m_health)
                damage = 0;
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_timer <= diff)
            {
                m_timer = 1000;
                DoWork();
            }
            else m_timer -= diff;

            if (UpdateVictim())
                DoMeleeAttackIfReady();
        }

        void DoWork()
        {
            if (me->IsInCombat())
                return;

            if (Creature* guard = me->FindNearestCreature(49428, 4.0f, true))
            {
                me->Attack(guard, true);
                guard->Attack(me, true);
            }
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const  override
    {
        return new npc_rotbrain_berserkerAI(pCreature);
    }
};

// showfight npc_rotbrain_magus 49423
class npc_rotbrain_magus : public CreatureScript
{
public:
    npc_rotbrain_magus() : CreatureScript("npc_rotbrain_magus") { }

    struct npc_rotbrain_magusAI : public ScriptedAI
    {
        npc_rotbrain_magusAI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;
        float m_health;

        void Reset()  override
        {
            m_timer = 1000;
            m_phase = 0;
            m_health = frand(60.0f, 95.0f);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetEntry() == 49428 && me->GetHealthPct() < m_health)
                damage = 0;
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_timer <= diff)
            {
                m_timer = 1000;
                DoWork();
            }
            else m_timer -= diff;

            if (UpdateVictim())
                DoMeleeAttackIfReady();
        }

        void DoWork()
        {
            if (me->IsInCombat())
                return;

            if (Creature* guard = me->FindNearestCreature(49428, 4.0f, true))
            {
                me->Attack(guard, true);
                guard->Attack(me, true);
            }
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const  override
    {
        return new npc_rotbrain_magusAI(pCreature);
    }
};

// showfight npc_marshal_redpath 49424
class npc_marshal_redpath : public CreatureScript
{
public:
    npc_marshal_redpath() : CreatureScript("npc_marshal_redpath") { }

    struct npc_marshal_redpathAI : public ScriptedAI
    {
        npc_marshal_redpathAI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;
        float m_health;

        void Reset()  override
        {
            m_timer = 1000;
            m_phase = 0;
            m_health = frand(60.0f, 95.0f);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (attacker->GetEntry() == 49428 && me->GetHealthPct() < m_health)
                damage = 0;
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_timer <= diff)
            {
                m_timer = 1000;
                DoWork();
            }
            else m_timer -= diff;

            if (UpdateVictim())
                DoMeleeAttackIfReady();
        }

        void DoWork()
        {
            if (me->IsInCombat())
                return;

            if (Creature* guard = me->FindNearestCreature(49428, 4.0f, true))
            {
                me->Attack(guard, true);
                guard->Attack(me, true);
            }
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const  override
    {
        return new npc_marshal_redpathAI(pCreature);
    }
};

// showfight npc_deathguard_protector 49428
class npc_deathguard_protector : public CreatureScript
{
public:
    npc_deathguard_protector() : CreatureScript("npc_deathguard_protector") { }

    struct npc_deathguard_protectorAI : public ScriptedAI
    {
        npc_deathguard_protectorAI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;
        float m_health;

        void Reset()  override
        {
            m_timer = 1000;
            m_phase = 0;
            m_health = frand(60.0f, 95.0f);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if ((attacker->GetEntry() == 49422 || attacker->GetEntry() == 49423 || attacker->GetEntry() == 49424) && me->GetHealthPct() < m_health)
                damage = 0;
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_timer <= diff)
            {
                m_timer = 1000;
                DoWork();
            }
            else m_timer -= diff;

            if (UpdateVictim())
                DoMeleeAttackIfReady();
        }

        void DoWork()
        {
           
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const  override
    {
        return new npc_deathguard_protectorAI(pCreature);
    }
};

// 1543
class npc_vile_fin_puddlejumper_1543 : public CreatureScript
{
public:
    npc_vile_fin_puddlejumper_1543() : CreatureScript("npc_vile_fin_puddlejumper_1543") { }

    enum eNPC
    {
        SPELL_MURLOC_LEACH = 73108,
        SPELL_SUMMON_PUDDLEJUMPER = 73110,
        SPELL_VILE_FIN_GUARDIAN_AURA = 94266,
    };

    struct npc_vile_fin_puddlejumper_1543AI : public ScriptedAI
    {
        npc_vile_fin_puddlejumper_1543AI(Creature* creature) : ScriptedAI(creature) { }

        uint64 m_playerGUID;

        void Reset()  override
        {
            uint64 m_playerGUID = 0;
        }

        void DamageTaken(Unit* attacker, uint32& damage) 
        { 
            if (Player* player = attacker->ToPlayer())
                if (me->GetHealthPct() <= 15.0f)
                {
                    Talk(0);
                    me->GetMotionMaster()->MoveIdle();
                    me->GetMotionMaster()->MoveFleeing(player);
                }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_vile_fin_puddlejumper_1543AI(creature);
    }
};

// 1544
class npc_vile_fin_minor_oracle_1544 : public CreatureScript
{
public:
    npc_vile_fin_minor_oracle_1544() : CreatureScript("npc_vile_fin_minor_oracle_1544") { }

    enum eNPC
    {
        SPELL_MURLOC_LEACH = 73108,
        SPELL_SUMMON_ORACLE = 73434,
        SPELL_VILE_FIN_GUARDIAN_AURA = 94266,
    };

    struct npc_vile_fin_minor_oracle_1544AI : public ScriptedAI
    {
        npc_vile_fin_minor_oracle_1544AI(Creature* creature) : ScriptedAI(creature) { }

        uint64 m_playerGUID;

        void Reset()  override
        {
            uint64 m_playerGUID = 0;
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (Player* player = attacker->ToPlayer())
                if (me->GetHealthPct() <= 15.0f)
                {
                    Talk(0);
                    me->GetMotionMaster()->MoveIdle();
                    me->GetMotionMaster()->MoveFleeing(player);
                }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_vile_fin_minor_oracle_1544AI(creature);
    }
};

// 73108
class spell_murloc_leash_73108 : public SpellScriptLoader
{
public:
    spell_murloc_leash_73108() : SpellScriptLoader("spell_murloc_leash_73108") { }

    enum eSpell
    {
        NPC_CAPTURED_PUDDLEJUMPER = 38923,
        NPC_CAPTURED_ORACLE = 39078,
        NPC_PUDDLEJUMPER = 1543,
        NPC_MINOR_ORACLE = 1544,
        SPELL_SUMMON_PUDDLEJUMPER = 73110,
        SPELL_SUMMON_ORACLE = 73434,
    };

    class spell_murloc_leash_73108_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_murloc_leash_73108_SpellScript);

        SpellCastResult CheckRequirement()
        {
            std::list<uint32>targets;
            targets.push_back(NPC_CAPTURED_PUDDLEJUMPER);
            targets.push_back(NPC_CAPTURED_ORACLE);
            if (Player* player = GetCaster()->ToPlayer())
            {
                std::list<Creature*> npcs = player->FindNearestCreatures(targets, 10.0f);
                if (npcs.size() > 0)
                    return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
            }

            if (Unit* unit = GetExplTargetUnit())
                if (unit->GetEntry() == NPC_PUDDLEJUMPER || unit->GetEntry() == NPC_MINOR_ORACLE)
                {
                    if (unit->GetHealthPct() < 80.0f)
                        return SPELL_CAST_OK;
                }
                else
                    return SPELL_FAILED_BAD_TARGETS;

            return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
        }

        void CheckTarget(WorldObject*& target)
        {
            if (Creature* npc = target->ToCreature())
                if (npc->GetEntry() == NPC_PUDDLEJUMPER || npc->GetEntry() == NPC_MINOR_ORACLE)
                    if (npc->GetHealthPct() < 80.0f)
                        return;
            target = nullptr;
        }

        void ApplyBeforeCast()
        {
            if (Player* player = GetCaster()->ToPlayer())
                if (Unit* unit = GetExplTargetUnit())
                    if (Creature* npc = unit->ToCreature())
                    {
                        if (npc->GetEntry() == NPC_PUDDLEJUMPER)
                            player->CastSpell(player, SPELL_SUMMON_PUDDLEJUMPER);
                        else if (npc->GetEntry() == NPC_MINOR_ORACLE)
                            player->CastSpell(player, SPELL_SUMMON_ORACLE);
                        npc->DespawnOrUnsummon(1);
                    }
        }

        void Register()
        {
            BeforeCast += SpellCastFn(spell_murloc_leash_73108_SpellScript::ApplyBeforeCast);
            OnCheckCast += SpellCheckCastFn(spell_murloc_leash_73108_SpellScript::CheckRequirement);
            OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_murloc_leash_73108_SpellScript::CheckTarget, EFFECT_0, TARGET_UNIT_TARGET_ANY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_murloc_leash_73108_SpellScript();
    }
};

// 38923
class npc_captured_vile_fin_puddlejumper_38923 : public CreatureScript
{
public:
    npc_captured_vile_fin_puddlejumper_38923() : CreatureScript("npc_captured_vile_fin_puddlejumper_38923") { }

    enum eNPC
    {
        NPC_CAPTURE_MURLOC_CREDIT = 38923,
        SPELL_VILE_FIN_GUARDIAN_AURA = 94266,
        EVENT_CHECK_PLAYER = 101,
    };

    struct npc_captured_vile_fin_puddlejumper_38923AI : public ScriptedAI
    {
        npc_captured_vile_fin_puddlejumper_38923AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64 m_playerGUID;

        void Reset()  override
        {
            m_events.Reset();
            m_events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
            uint64 m_playerGUID = 0;
        }

        void IsSummonedBy(Unit* summoner) override 
        { 
            if (Player* player = summoner->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                player->KilledMonsterCredit(NPC_CAPTURE_MURLOC_CREDIT);
                me->GetMotionMaster()->MoveFollow(player, 4.0f, 3.14f);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_captured_vile_fin_puddlejumper_38923AI(creature);
    }
};

// 39078
class npc_captured_vile_fin_minor_oracle_39078 : public CreatureScript
{
public:
    npc_captured_vile_fin_minor_oracle_39078() : CreatureScript("npc_captured_vile_fin_minor_oracle_39078") { }

    enum eNPC
    {
        NPC_CAPTURE_MURLOC_CREDIT = 38923,
        SPELL_VILE_FIN_GUARDIAN_AURA = 94266,
        EVENT_CHECK_PLAYER = 101,
    };

    struct npc_captured_vile_fin_minor_oracle_39078AI : public ScriptedAI
    {
        npc_captured_vile_fin_minor_oracle_39078AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64 m_playerGUID;

        void Reset()  override
        {
            m_events.Reset();
            m_events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
            uint64 m_playerGUID = 0;
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                player->KilledMonsterCredit(NPC_CAPTURE_MURLOC_CREDIT);
                me->GetMotionMaster()->MoveFollow(player, 4.0f, 3.14f);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_captured_vile_fin_minor_oracle_39078AI(creature);
    }
};

// 38925
class npc_sedrick_calston_38925 : public CreatureScript
{
public:
    npc_sedrick_calston_38925() : CreatureScript("npc_sedrick_calston_38925") { }

    enum eNPC
    {
        NPC_CAPTURED_PUDDLEJUMPER = 38923,
        NPC_CAPTURED_ORACLE = 39078,
        NPC_CAPTURE_MURLOC_CREDIT = 38923,
        NPC_DELIVERED_MURLOC_CREDIT = 38887,
        QUEST_EVER_SO_LONELY = 24974,
        SPELL_VILE_FIN_GUARDIAN_AURA = 94266,
        EVENT_CHECK_PLAYER=101,
    };

    struct npc_sedrick_calston_38925AI : public ScriptedAI
    {
        npc_sedrick_calston_38925AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset() override
        {
            m_events.Reset();
            m_events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
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
                        if (Player* player = me->FindNearestPlayer(7.0f))
                            if (player->GetQuestStatus(QUEST_EVER_SO_LONELY) == QUEST_STATUS_INCOMPLETE)
                                if (player->GetReqKillOrCastCurrentCount(QUEST_EVER_SO_LONELY, NPC_CAPTURE_MURLOC_CREDIT) > 0)
                                {
                                    std::list<uint32>targets;
                                    targets.push_back(NPC_CAPTURED_PUDDLEJUMPER);
                                    targets.push_back(NPC_CAPTURED_ORACLE);
                                    std::list<Creature*> npcs = me->FindNearestCreatures(targets, 10.0f);
                                    if (npcs.size() > 0)
                                    {
                                        player->RemoveAura(SPELL_VILE_FIN_GUARDIAN_AURA);
                                        player->KilledMonsterCredit(NPC_DELIVERED_MURLOC_CREDIT);

                                        for (std::list<Creature*>::iterator itr = npcs.begin(); itr != npcs.end(); ++itr)
                                            (*itr)->DespawnOrUnsummon(1);
                                    }
                                }

                        m_events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
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
        return new npc_sedrick_calston_38925AI(creature);
    }
};

// 39117 // quest 25006
class npc_shadow_priestess_malia_39117 : public CreatureScript
{
public:
    npc_shadow_priestess_malia_39117() : CreatureScript("npc_shadow_priestess_malia_39117") { }

    enum eNPC
    {
        QUEST_THE_GRASP_WEAKENS = 25006,
        NPC_SPIRIT_OF_DEVLIN_AGAMAND_38980 = 38980,
        NPC_SHADOW_OF_AGAMAND_38981 = 38981,
        NPC_SHADOW_OF_AGAMAND_38983 = 38983,
        PLAYER_GUID = 99999,
        WAYPOINT_UPSTARS = 3702201,
        WAYPOINT_DOWNSTARS = 3702202,
        ACTION_START_ANIM = 100,
        EVENT_CHECK_MasterReset = 101,
        EVENT_START_ANIM,
        EVENT_ANIM,
    };

    bool OnGossipHello(Player* player, Creature* creature) 
    {
        if (player->GetQuestStatus(QUEST_THE_GRASP_WEAKENS) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM_DB(11156, 0, GOSSIP_SENDER_MAIN, 1001);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());

            return true;
        }

        return false; 
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        switch (action)
        {
        case 1001:
            creature->AI()->SetGUID(player->GetGUID(), PLAYER_GUID);
            creature->AI()->DoAction(ACTION_START_ANIM);
            break;
        }
        player->CLOSE_GOSSIP_MENU();

        return true;
    }

    struct npc_shadow_priestess_malia_39117AI : public ScriptedAI
    {
        npc_shadow_priestess_malia_39117AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_spiritAgamand;
        uint64   m_shadowAgamand1;
        uint64   m_shadowAgamand2;
        bool     m_animStarted;
        uint32   m_phase;
        uint32   m_sayPriestess;
        uint32   m_sayAgamand;

        void Reset() override
        {
            m_events.Reset();
            m_playerGUID = 0;
            m_spiritAgamand = 0;
            m_shadowAgamand1 = 0;
            m_shadowAgamand2 = 0;
            m_animStarted = 0;
            m_phase = 0;
            m_sayPriestess = 0;
            m_sayAgamand = 0;
        }

        void JustSummoned(Creature* summon) override
        {
            switch (summon->GetEntry())
            {
                case NPC_SPIRIT_OF_DEVLIN_AGAMAND_38980:
                {
                    m_spiritAgamand = summon->GetGUID();
                    break;
                }
                case NPC_SHADOW_OF_AGAMAND_38981: // attacker
                {
                    m_shadowAgamand1 = summon->GetGUID();
                    summon->SetReactState(REACT_AGGRESSIVE);
                    summon->SetWalk(true);
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        summon->Attack(player, true);
                    break;
                }
                case NPC_SHADOW_OF_AGAMAND_38983: // shadow
                {
                    m_shadowAgamand2 = summon->GetGUID();
                    summon->SetReactState(REACT_PASSIVE);
                    break;
                }
            }
        }

        void SummonedCreatureDies(Creature* summon, Unit* killer) override 
        { 
            if (summon->GetGUID() == m_shadowAgamand1)
                if (killer->GetGUID() == m_playerGUID)
                    m_events.ScheduleEvent(EVENT_ANIM + 6, 7000);
        }

        void MovementInform(uint32 type, uint32 id) override 
        { 
            if (type == WAYPOINT_MOTION_TYPE && id == 9 && m_phase == 1)
                    m_events.ScheduleEvent(EVENT_ANIM + 2, 1000);
            if (type == WAYPOINT_MOTION_TYPE && id == 10 && m_phase == 2)
            {
                if (Creature* shadow = sObjectAccessor->GetCreature(*me, m_shadowAgamand2))
                    shadow->DespawnOrUnsummon(1);
                Reset();
            }
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

        void DoAction(int32 param) override 
        { 
            if (!m_animStarted && param == ACTION_START_ANIM)
            {
                m_animStarted = true;
                m_events.ScheduleEvent(EVENT_START_ANIM, 500);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_MasterReset:
                    {
                        me->DespawnOrUnsummon(1);
                        break;
                    }
                    case EVENT_START_ANIM:
                    {
                        Talk(m_sayPriestess);
                        m_sayPriestess++;
                        m_events.ScheduleEvent(EVENT_ANIM+1, 2000);
                        m_events.ScheduleEvent(EVENT_CHECK_MasterReset, 120000);
                        break;
                    }
                    case EVENT_ANIM + 1:
                    {
                        m_phase = 1;
                        me->GetMotionMaster()->MovePath(WAYPOINT_UPSTARS, false);
                        break;
                    }
                    case EVENT_ANIM + 2: // priestess is telling the story
                    {
                        Talk(m_sayPriestess);
                        m_sayPriestess++;
                        if (m_sayPriestess < 5)
                            m_events.ScheduleEvent(EVENT_ANIM + 2, 5000);
                        else
                            m_events.ScheduleEvent(EVENT_ANIM + 3, 5000);
                        break;
                    }
                    case EVENT_ANIM + 3:
                    {
                        me->SummonCreature(NPC_SPIRIT_OF_DEVLIN_AGAMAND_38980, 2247.13f, 228.04f, 44.2511f, 1.95477f, TEMPSUMMON_TIMED_DESPAWN, 120000);
                        m_events.ScheduleEvent(EVENT_ANIM + 4, 3000);
                        break;
                    }
                    case EVENT_ANIM + 4: // agamand is telling the story
                    {
                        if (Creature* agamand = sObjectAccessor->GetCreature(*me, m_spiritAgamand))
                            agamand->AI()->Talk(m_sayAgamand);
                        m_sayAgamand++;
                        if (m_sayAgamand < 7)
                            m_events.ScheduleEvent(EVENT_ANIM + 4, 5000);
                        else
                            m_events.ScheduleEvent(EVENT_ANIM + 5, 1000); // say immediately: die wretches
                        break;
                    }
                    case EVENT_ANIM + 5:
                    {
                        me->SummonCreature(NPC_SHADOW_OF_AGAMAND_38981, 2247.13f, 228.04f, 44.2511f, 1.95477f, TEMPSUMMON_TIMED_DESPAWN, 60000); // attacker of agamand
                        me->SummonCreature(NPC_SHADOW_OF_AGAMAND_38983, 2247.13f, 228.04f, 44.2511f, 1.95477f, TEMPSUMMON_TIMED_DESPAWN, 60000); // shadow of agamand
                        if (Creature* agamand = sObjectAccessor->GetCreature(*me, m_spiritAgamand))
                            agamand->DespawnOrUnsummon(1);
                        break;
                    }
                    case EVENT_ANIM + 6:
                    {
                        Talk(m_sayPriestess);
                        m_phase = 2;
                        me->GetMotionMaster()->MovePath(WAYPOINT_DOWNSTARS, false);
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
        return new npc_shadow_priestess_malia_39117AI(creature);
    }
};

// 38936 // vehicle sanders
class npc_lieutenant_sanders_noose_38936 : public CreatureScript
{
public:
    npc_lieutenant_sanders_noose_38936() : CreatureScript("npc_lieutenant_sanders_noose_38936") { }

    enum eNPC
    {
        NPC_LEUTNANT_SANDERS = 13158,
        NPC_LEUTNANT_SANDERS_NOSE_FOCUS = 39093,
        SPELL_SANDERS_HANGING = 73443,
        SPELL_SANDERS_FOOT_NOSE = 73444,
        EVENT_CHECK_SANDERS = 101,
    };

    struct npc_lieutenant_sanders_noose_38936AI : public ScriptedAI
    {
        npc_lieutenant_sanders_noose_38936AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset() override
        {
            m_events.Reset();
            m_events.ScheduleEvent(EVENT_CHECK_SANDERS, 250);
            me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_HOVER);
            me->AddUnitMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);
            me->SetDisableGravity(true);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_SANDERS:
                    {
                        if (!me->HasAura(SPELL_SANDERS_HANGING))
                            me->CastSpell(me, SPELL_SANDERS_HANGING, true);

                        if (Vehicle* vehicle = me->GetVehicleKit())
                            if (Unit* sanders = vehicle->GetPassenger(0))
                            {
                                if (!sanders->HasAura(SPELL_SANDERS_FOOT_NOSE))
                                    me->CastSpell(2533.339f, -920.6719f, 60.98916f, SPELL_SANDERS_FOOT_NOSE, true);
                            }
                            else
                                if (Creature* sanders = me->FindNearestCreature(NPC_LEUTNANT_SANDERS, 10.0f))
                                {
                                    sanders->SetDisableGravity(true);
                                    sanders->EnterVehicle(me, 0);
                                }

                        m_events.ScheduleEvent(EVENT_CHECK_SANDERS, 1000);
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
        return new npc_lieutenant_sanders_noose_38936AI(creature);
    }
};

// 39038
class npc_lilian_voss_39038 : public CreatureScript
{
public:
    npc_lilian_voss_39038() : CreatureScript("npc_lilian_voss_39038") { }

    enum eNPC
    {
        QUEST_A_DAUGHTERS_EMBRACE = 25046,
        NPC_BENEDICTUS = 39097,
        NPC_BENEDICTUS_CREDIT = 39098,
        NPC_BODYGUARD = 1660,
        NPC_MELRACHE = 1665,
        NPC_SCARLET_FRIAR = 1538,
        NPC_SCARLET_NEOPHYTE = 1539,
        NPC_SCARLET_VANGUARD = 1540,
        SPELL_SHADOWY_AURA = 73304,
        SPELL_LILIANS_BRAIN_BURST = 73307,
        SPELL_LILIANS_SHADOW_HOP = 73308,
        SPELL_LILIANS_DEATH_GRIP = 73309,
        SPELL_STEALTH = 73392,
        EVENT_CD_73308 = 101,
        EVENT_CD_73309,
        EVENT_CHECK_ATTACK,
        EVENT_CHECK_FATHER_SEQUENCE,
        EVENT_START_FATHER_SEQUENCE,
        EVENT_TALK_PART,
    };

    struct npc_lilian_voss_39038AI : public ScriptedAI
    {
        npc_lilian_voss_39038AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64 m_playerGUID;
        uint64 m_fatherGUID;
        bool   cd_73308, cd_73309;
        std::list<uint32>m_targets;
        std::list<uint32>m_father;
        bool m_fatherSequence1;

        void Initialize()
        {
            m_events.Reset();
            m_playerGUID = 0;
            m_fatherGUID = 0;
            cd_73308 = false;
            cd_73309 = false;
            m_targets.push_back(NPC_SCARLET_FRIAR);
            m_targets.push_back(NPC_SCARLET_NEOPHYTE);
            m_targets.push_back(NPC_SCARLET_VANGUARD);
            m_father.push_back(NPC_BODYGUARD);
            m_father.push_back(NPC_MELRACHE);
            m_father.push_back(NPC_BENEDICTUS);
            m_fatherSequence1 = false;
            m_events.ScheduleEvent(EVENT_CHECK_FATHER_SEQUENCE, 1000);
            m_events.ScheduleEvent(EVENT_CHECK_ATTACK, 1000);
        }

        void Reset() override
        {
            if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                me->GetMotionMaster()->MoveFollow(player, 4.0f, 3.14f);
            me->SetReactState(REACT_DEFENSIVE);
        }

        void IsSummonedBy(Unit* summoner) override 
        { 
            if (Player* player = summoner->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                me->GetMotionMaster()->MoveFollow(player, 4.0f, 3.14f);
            }
        }

        void EnterCombat(Unit* victim)
        { 
            uint8 rol = urand(0, 100);
            std::list<Creature*>m_c30 = me->FindNearestCreatures(m_targets, 30.0f);
            if (!cd_73309 && m_c30.size() > 4)
                CastSpell_LiliansDeathGrip();
            else
                if (!cd_73308 && rol < 90)
                    if (Creature* target = victim->ToCreature())
                        CastSpell_LiliansShadowHop(target);
        }

        void KilledUnit(Unit* victim) 
        { 
            if (victim->GetCreatureType() == CREATURE_TYPE_HUMANOID)
                me->AddAura(SPELL_SHADOWY_AURA, victim);

            if (victim->GetEntry() == NPC_BENEDICTUS)
                if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                {
                    player->KilledMonsterCredit(NPC_BENEDICTUS_CREDIT);
                    m_events.ScheduleEvent(EVENT_TALK_PART + 11, 1000);
                }
            if (victim->GetEntry() == NPC_BODYGUARD || victim->GetEntry() == NPC_MELRACHE)
                m_events.ScheduleEvent(EVENT_TALK_PART + 3, 500);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CD_73308:
                    {
                        cd_73308 = false;
                        break;
                    }
                    case EVENT_CD_73309:
                    {
                        cd_73309 = false;
                        break;
                    }
                    case EVENT_CHECK_ATTACK:
                    {                        
                        if (!cd_73309 && !cd_73308)
                            if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                                if (player->IsInCombat())
                                    if (me->IsInCombat())
                                    {
                                        if (Unit* unit = me->SelectVictim())
                                            if (Creature* target = unit->ToCreature())
                                                if (target->GetEntry() == NPC_SCARLET_FRIAR || target->GetEntry() == NPC_SCARLET_NEOPHYTE || target->GetEntry() == NPC_SCARLET_VANGUARD)
                                                    CastSpell_LiliansShadowHop(target);
                                    }
                                    else
                                    {
                                        printf("EVENT_CHECK_ATTACK player is in combat, ich nicht...\n");
                                    }

                        m_events.ScheduleEvent(EVENT_CHECK_ATTACK, 1000);
                        break;
                    }
                    case EVENT_CHECK_FATHER_SEQUENCE:
                    {
                        std::list<Creature*>m_guard = me->FindNearestCreatures(m_father, 23.0f);
                        if (m_guard.size() > 0)
                            for (std::list<Creature*>::iterator itr = m_guard.begin(); itr != m_guard.end(); ++itr)
                                (*itr)->SetReactState(REACT_PASSIVE);

                        Creature* father = me->FindNearestCreature(NPC_BENEDICTUS, 23.0f);
                        if (father)
                        {
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
                            m_fatherGUID = father->GetGUID();
                            m_events.ScheduleEvent(EVENT_START_FATHER_SEQUENCE, 200);
                        }
                        else
                            m_events.ScheduleEvent(EVENT_CHECK_FATHER_SEQUENCE, 1000);

                        break;
                    }
                    case EVENT_START_FATHER_SEQUENCE:
                    {
                        Talk(0);
                        me->GetMotionMaster()->Clear();
                        me->SetWalk(true);
                        me->GetMotionMaster()->MovePath(3903801, false);
                        m_events.ScheduleEvent(EVENT_TALK_PART + 1, 6000);
                        break;
                    }
                    case EVENT_TALK_PART + 1:
                    {
                        if (Creature* father = sObjectAccessor->GetCreature(*me, m_fatherGUID))
                            father->AI()->Talk(0); 
                        m_events.ScheduleEvent(EVENT_TALK_PART + 2, 6000);
                        break;
                    }
                    case EVENT_TALK_PART + 2:
                    {
                        Talk(1);
                        m_events.ScheduleEvent(EVENT_TALK_PART + 3, 6000);
                        break;
                    }
                    case EVENT_TALK_PART + 3:
                    {
                        std::list<Creature*>m_guard = me->FindNearestCreatures(m_father, 20.0f);
                        if (m_guard.size() > 0)
                            for (std::list<Creature*>::iterator itr = m_guard.begin(); itr != m_guard.end(); ++itr)
                                if ((*itr)->IsAlive())
                                    if ((*itr)->GetEntry() != NPC_BENEDICTUS)
                                    {
                                        me->CastSpell((*itr), SPELL_LILIANS_SHADOW_HOP, true);
                                        return;
                                    }

                        if (!m_fatherSequence1)
                        {
                            m_events.ScheduleEvent(EVENT_TALK_PART + 4, 1000);
                            m_fatherSequence1 = true;
                        }
                        break;
                    }
                    case EVENT_TALK_PART + 4:
                    {
                        Talk(2);
                        m_events.ScheduleEvent(EVENT_TALK_PART + 5, 6000);
                        break;
                    }
                    case EVENT_TALK_PART + 5:
                    {
                        if (Creature* father = sObjectAccessor->GetCreature(*me, m_fatherGUID))
                            father->AI()->Talk(1);
                        m_events.ScheduleEvent(EVENT_TALK_PART + 6, 6000);
                        break;
                    }
                    case EVENT_TALK_PART + 6:
                    {
                        Talk(3);
                        m_events.ScheduleEvent(EVENT_TALK_PART + 7, 6000);
                        break;
                    }
                    case EVENT_TALK_PART + 7:
                    {
                        if (Creature* father = sObjectAccessor->GetCreature(*me, m_fatherGUID))
                            father->AI()->Talk(2); 
                        m_events.ScheduleEvent(EVENT_TALK_PART + 8, 6000);
                        break;
                    }
                    case EVENT_TALK_PART + 8:
                    {
                        Talk(4); 
                        m_events.ScheduleEvent(EVENT_TALK_PART + 9, 6000);
                        break;
                    }
                    case EVENT_TALK_PART + 9:
                    {
                        Talk(5);
                        m_events.ScheduleEvent(EVENT_TALK_PART + 10, 6000);
                        break;
                    }
                    case EVENT_TALK_PART + 10:
                    {
                        if (Creature* father = sObjectAccessor->GetCreature(*me, m_fatherGUID))
                            me->CastSpell(father, SPELL_LILIANS_SHADOW_HOP, true);

                        break;
                    }
                    case EVENT_TALK_PART + 11:
                    {
                        me->GetMotionMaster()->MovePath(3903802, false);
                        m_events.ScheduleEvent(EVENT_TALK_PART + 12, 9000);
                        break;
                    }
                    case EVENT_TALK_PART + 12:
                    {
                        me->DespawnOrUnsummon(1);
                        break;
                    }
                }
            }
            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void CastSpell_LiliansDeathGrip()
        {
            me->CastSpell(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), SPELL_LILIANS_DEATH_GRIP, true);
            m_events.ScheduleEvent(EVENT_CD_73309, 30000);
            cd_73309 = true;
        }

        void CastSpell_LiliansShadowHop(Creature* target)
        {
            me->CastSpell(target, SPELL_LILIANS_SHADOW_HOP, true);
            m_events.ScheduleEvent(EVENT_CD_73308, 5000);
            cd_73308 = true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_lilian_voss_39038AI(creature);
    }
};

// 73307
class spell_lilians_brain_burst_73307 : public SpellScriptLoader
{
public:
    spell_lilians_brain_burst_73307() : SpellScriptLoader("spell_lilians_brain_burst_73307") { }

    class spell_lilians_brain_burst_73307_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_lilians_brain_burst_73307_AuraScript);

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (!GetCaster() || !GetTarget())
                return;

            GetCaster()->Kill(GetTarget());
        }

        void Register() override
        {      
            OnEffectApply += AuraEffectApplyFn(spell_lilians_brain_burst_73307_AuraScript::OnApply, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_lilians_brain_burst_73307_AuraScript();
    }
};

// 73308
class spell_lilians_shadow_hop_73308 : public SpellScriptLoader
{
public:
    spell_lilians_shadow_hop_73308() : SpellScriptLoader("spell_lilians_shadow_hop_73308") { }

    enum Spells
    {
        SPELL_LILIANS_BRAIN_BURST = 73307,
    };

    class spell_lilians_shadow_hop_73308_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_lilians_shadow_hop_73308_AuraScript);

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (!GetCaster() || !GetTarget())
                return;

            GetCaster()->CastSpell(GetTarget(), SPELL_LILIANS_BRAIN_BURST, true);
        }

        void Register() override
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_lilians_shadow_hop_73308_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_CONTROL_VEHICLE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_lilians_shadow_hop_73308_AuraScript();
    }
};

// 73309
class spell_lilians_death_grip_73309 : public SpellScriptLoader
{
public:
    spell_lilians_death_grip_73309() : SpellScriptLoader("spell_lilians_death_grip_73309") { }

    class spell_lilians_death_grip_73309_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_lilians_death_grip_73309_AuraScript);

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* owner = GetOwner()->ToUnit())
                if (Unit* target = GetTarget())
                {
                    target->JumpTo(owner, 15.0f);
                    target->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED | UNIT_FLAG_DISABLE_MOVE);
                }
        }

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* owner = GetOwner()->ToUnit())
                if (Unit* target = GetTarget())
                    owner->Kill(target);
        }

        void Register() override
        {
            OnEffectApply += AuraEffectApplyFn(spell_lilians_death_grip_73309_AuraScript::OnApply, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            AfterEffectRemove += AuraEffectRemoveFn(spell_lilians_death_grip_73309_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_lilians_death_grip_73309_AuraScript();
    }
};


void AddSC_tirisfal_glades()
{
    new npc_aradne_50372();
    new npc_deathknell_grave_target();
    new npc_risen_dead();
    new npc_undertaker_mordo();
    new npc_darnell_49141();
    new npc_marshal_redpath_49230();
    new npc_valdred_moray_49231();
    new npc_lilian_voss_38895();
    new npc_deathguard_saltain();
    new npc_scarlet_corpse_49340();
    new npc_darnell_49337();
    new npc_lilian_voss_38910();
    new npc_rotbrain_berserker();
    new npc_rotbrain_magus();
    new npc_marshal_redpath();
    new npc_deathguard_protector();
    new npc_vile_fin_puddlejumper_1543();
    new npc_vile_fin_minor_oracle_1544();
    new spell_murloc_leash_73108();
    new npc_captured_vile_fin_puddlejumper_38923();
    new npc_captured_vile_fin_minor_oracle_39078();
    new npc_sedrick_calston_38925();
    new npc_shadow_priestess_malia_39117();
    new npc_lieutenant_sanders_noose_38936();
    new npc_lilian_voss_39038();
    new spell_lilians_brain_burst_73307();
    new spell_lilians_shadow_hop_73308();
    new spell_lilians_death_grip_73309();
}
