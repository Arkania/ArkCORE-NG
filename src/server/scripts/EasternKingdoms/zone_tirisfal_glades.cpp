/*
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

#include "Vehicle.h"

// npc_aradne 50372
class npc_aradne_50372 : public CreatureScript
{
public:
    npc_aradne_50372() : CreatureScript("npc_aradne_50372") { }

    enum eAradne
    {
        RAISE_UNDEAD = 93446,
    };

    struct npc_aradne_50372AI : public ScriptedAI
    {
        npc_aradne_50372AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;

        void Reset()  override
        {
            m_timer = 0;
            m_phase = 0;
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == WAYPOINT_MOTION_TYPE)
                switch (id)
                {
                case 5:
                    m_phase = 1;
                    m_timer = 100;
                    break;
                case 7:
                    m_phase = 1;
                    m_timer = 100;
                    break;
                case 12:
                    m_phase = 1;
                    m_timer = 100;
                    break;
                case 17:
                    m_phase = 1;
                    m_timer = 100;
                    break;
                case 22:
                    m_phase = 1;
                    m_timer = 100;
                    break;
                case 25:
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
            else m_timer -= diff;
        }

        void DoWork()
        {
            switch (m_phase)
            {
            case 1:
                if (Creature* npc = me->FindNearestCreature(50373, 15.0f))
                    npc->CastSpell(npc, 93446, true);

                m_phase = 2;
                break;
            case 2:
                Talk(0);
                m_phase = 3;
                break;
            default:
                m_timer = 0;
                m_phase = 0;
                break;
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
        DIRT_EXPLOSION = 89199,
        CHURNING_DIRT = 92788,
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
            if (spell->Id == 93446)
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
                    me->AddAura(DIRT_EXPLOSION, me);
                    DoCast(me, CHURNING_DIRT);
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

    struct npc_risen_deadAI : public ScriptedAI
    {
        npc_risen_deadAI(Creature *c) : ScriptedAI(c) {}

        uint32 m_timer;
        uint32 m_phase;
        uint32 m_WishToBeDead;

        void Reset()  override
        {
            m_timer = 2000;
            m_phase = 0;
            m_WishToBeDead = urand(0, 100);
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
            if (m_WishToBeDead < 33)
                ShowDead();
            else if (m_WishToBeDead < 66)
                ShowLife();
            else
                ShowRunning();
        }

        void ShowDead()
        {
            switch (m_phase)
            {
                case 0:
                    me->HandleEmote(EMOTE_ONESHOT_QUESTION);
                    m_timer = 200;
                    m_phase = 1;
                    break;
                case 1:
                    Talk(0);
                    m_timer = 5000;
                    m_phase = 2;
                    break;
                case 2:
                    Talk(1);
                    m_timer = 5000;
                    m_phase = 3;
                    break;
                case 3:
                    Talk(8);
                    me->Kill(me);
                    m_timer = 5000;
                    m_phase = 4;
                    break;
                case 4:
                    m_timer = 0;
                    m_phase = 5;
                    break;
            }
        }

        void ShowLife()
        {
            switch (m_phase)
            {
            case 0:
                me->HandleEmote(EMOTE_ONESHOT_QUESTION);
                m_timer = 200;
                m_phase = 1;
                break;
            case 1:
                Talk(4);
                m_timer = 5000;
                m_phase = 2;
                break;
            case 2:
                Talk(5);
                m_timer = 5000;
                m_phase = 3;
                break;
            case 3:
                Talk(9);
                me->GetMotionMaster()->MovePath(5037401, false);
                m_timer = 20000;
                m_phase = 4;
                break;
            case 4:
                m_timer = 0;
                m_phase = 5;
                break;
            }
        }

        void ShowRunning()
        {
            switch (m_phase)
            {
            case 0:
                me->HandleEmote(EMOTE_ONESHOT_QUESTION);
                m_timer = 200;
                m_phase = 1;
                break;
            case 1:
                Talk(2);
                m_timer = 5000;
                m_phase = 2;
                break;
            case 2:
                Talk(3);
                m_timer = 5000;
                m_phase = 3;
                break;
            case 3:
                Talk(7);
                me->HandleEmote(44427);
                me->GetMotionMaster()->MovePath(5037402, false);
                m_timer = 5000;
                m_phase = 4;
                break;
            case 4:
                m_timer = 0;
                m_phase = 5;
                break;
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

        uint32 m_timer;
        uint32 m_phase;
        Creature* m_npc;

        void Reset()  override
        {
            m_timer = urand(30000, 45000);
            m_phase = 0;
            m_npc = NULL;
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
            case 0: // Time: 07/03/2015 11:08:09.619
                if (Creature* npc_trigger = me->FindNearestCreature(50373, 20.0f))
                    if (m_npc = me->SummonCreature(50414, npc_trigger->GetPosition(), TEMPSUMMON_TIMED_DESPAWN, 40000))
                    {
                        Position pos = me->GetNearPosition(1.5f, 1.72f);
                        m_npc->GetMotionMaster()->MovePoint(0, pos, true);
                    }

                m_phase = 1;
                break;
            case 1: // Time: 07/03/2015 11:08:10.539
                Talk(0);
                m_timer = 3000;
                m_phase = 2;
                break;
            case 2: // Time: 07/03/2015 11:08:13.253 Number: 5796
                if (m_npc && m_npc->IsAlive())
                {
                    m_npc->SetUInt32Value(UNIT_FIELD_BYTES_1, UNIT_STAND_STATE_KNEEL);
                    m_npc->SetFacingToObject(me);
                }

                m_timer = 750;
                m_phase = 3;
                break;
            case 3: // Time: 07/03/2015 11:08:14.080 Number: 5805
                me->HandleEmoteState(EMOTE_STATE_USE_STANDING);
                m_timer = 6000;
                m_phase = 4;
                break;
            case 4: // Time: 07/03/2015 11:08:20.133 Number: 5875
                me->HandleEmoteState(EMOTE_ONESHOT_NONE);
                m_timer = 750;
                m_phase = 5;
                break;
            case 5: // Time: 07/03/2015 11:08:21.350 Number: 5891
                me->HandleEmote(EMOTE_ONESHOT_POINT);
                m_timer = 2500;
                m_phase = 6;
                break;
            case 6: // Time: 07/03/2015 11:08:23.908 Number: 5934
                Talk(1);
                m_timer = 250;
                m_phase = 7;
                break;
            case 7: // 07/03/2015 11:08:24.189 Number: 5935
                if (m_npc && m_npc->IsAlive())
                {
                    m_npc->AddAura(93460, m_npc);
                    m_npc->CastSpell(m_npc, 93460);
                    m_npc->SetDisplayId(36775);
                    m_npc->SetUInt32Value(UNIT_FIELD_BYTES_1, UNIT_STAND_STATE_STAND);
                }

                m_timer = 2500;
                m_phase = 8;
                break;
            case 8: // Time: 07/03/2015 11:08:26.607 Number: 5967
                if (m_npc && m_npc->IsAlive())
                {
                    m_npc->HandleEmote(EMOTE_ONESHOT_TALK);
                    m_npc->AI()->Talk(0);
                }

                m_timer = 3750;
                m_phase = 9;
                break;
            case 9: // Time: 07/03/2015 11:08:30.257 Number: 6015
                if (m_npc && m_npc->IsAlive())
                    m_npc->HandleEmote(EMOTE_ONESHOT_SALUTE);

                m_timer = 2500;
                m_phase = 10;
                break;
            case 10: // Time: 07/03/2015 11:08:32.691 Number: 6043
                if (m_npc && m_npc->IsAlive())
                    m_npc->GetMotionMaster()->MovePath(5041401, false);

                m_timer = 45000;
                m_phase = 11;
                break;
            case 11: // Time: 07/03/2015 11:09:15.139 Number: 6405
                if (m_npc && m_npc->IsAlive())
                    m_npc->DespawnOrUnsummon();

                m_timer = urand(15000, 45000);;
                m_phase = 0;
                break;
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
                        Talk(0);
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
            m_player = NULL;
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
                Talk(1);
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
            m_player = NULL;
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
                Talk(1);
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
            m_player = NULL;
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
                Talk(1);
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
};

// npc_darnell 49337
class npc_darnell_49337 : public CreatureScript
{
public:
    npc_darnell_49337() : CreatureScript("npc_darnell_49337") { }

    struct npc_darnell_49337AI : public ScriptedAI
    {
        npc_darnell_49337AI(Creature *c) : ScriptedAI(c) {}

        uint32 m_timer;
        uint8 m_seat;

        void Reset()  override
        {
            m_timer = 1000;
            m_seat = 0;
        }

        void StartAnim(Unit* caster, Creature* corpse)
        {
            if (caster->GetGUID() == me->GetCharmerOrOwnerGUID() && m_seat < 7)
            {
                me->CastSpell(corpse, 91945, true);
                corpse->AddAura(46598, corpse);
                corpse->SetDisableGravity(true);
                corpse->EnterVehicle(me, m_seat);
                m_seat++;
                me->CastSpell(corpse, 91935, true);
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
            if (Unit* unit = me->GetCharmerOrOwner())
                if (Player* player = unit->ToPlayer())
                    if (player->GetQuestStatus(26800) == QUEST_STATUS_REWARDED)
                    {
                        if (Vehicle* vehicle = me->GetVehicleKit())
                            vehicle->RemoveAllPassengers();
                        
                        me->DespawnOrUnsummon(5000);
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

        uint32 m_timer;
        uint8 m_modus;
        Player* m_player;

        void Reset()  override
        {
            m_timer = 0;
            m_modus = 0;
            m_player = NULL;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) 
        { 
            if (Player* player = caster->ToPlayer())
                if (player->GetQuestStatus(26800) == QUEST_STATUS_INCOMPLETE && m_modus == 0)
                {
                    m_modus = 1;
                    m_player = player;
                    std::list<Creature*> darnells = me->FindNearestCreatures(49337, 10.0f);

                    if (!darnells.empty())
                        for (std::list<Creature*>::const_iterator itr = darnells.begin(); itr != darnells.end(); ++itr)
                            if ((*itr)->GetOwner() == caster && *itr != me)
                                CAST_AI(npc_darnell_49337::npc_darnell_49337AI, (*itr)->GetAI())->StartAnim(caster, me);
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
            if (m_modus == 1)
            {
                if (m_player && m_player->GetQuestStatus(26800) == QUEST_STATUS_REWARDED)
                    me->DespawnOrUnsummon(5000);

                if (!m_player)
                    me->DespawnOrUnsummon(5000);
            }
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
            m_player = NULL;
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

}
