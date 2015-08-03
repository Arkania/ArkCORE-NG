/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2014 ArkCORE <http://www.arkania.net/>
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
#include "PassiveAI.h"
#include "Player.h"

// npc 28534
class npc_valkyr_battle_maiden : public CreatureScript
{
    enum eVBM
    {
        SPELL_REVIVE = 51918,
        WHISPER_REVIVE = 0,
    };

public:
    npc_valkyr_battle_maiden() : CreatureScript("npc_valkyr_battle_maiden") { }

    CreatureAI* GetAI(Creature* creature) const OVERRIDE
    {
        return new npc_valkyr_battle_maidenAI(creature);
    }

    struct npc_valkyr_battle_maidenAI : public PassiveAI
    {
        npc_valkyr_battle_maidenAI(Creature* creature) : PassiveAI(creature) { }

        uint32 FlyBackTimer;
        float x, y, z;
        uint32 phase;

        void Reset() OVERRIDE
        {
            me->setActive(true);
            me->SetVisible(false);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetCanFly(true);
            FlyBackTimer = 500;
            phase = 0;

            me->GetPosition(x, y, z);
            z += 4.0f;
            x -= 3.5f;
            y -= 5.0f;
            me->GetMotionMaster()->Clear(false);
            me->SetPosition(x, y, z, 0.0f);
        }

        void UpdateAI(uint32 diff) OVERRIDE
        {
            if (FlyBackTimer <= diff)
            {
                Player* player = NULL;
                if (me->IsSummon())
                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                        player = summoner->ToPlayer();

                if (!player)
                    phase = 3;

                switch (phase)
                {
                    case 0:
                        me->SetWalk(false);
                        me->HandleEmoteCommand(EMOTE_STATE_FLYGRABCLOSED);
                        FlyBackTimer = 500;
                        break;
                    case 1:
                        player->GetClosePoint(x, y, z, me->GetObjectSize());
                        z += 2.5f;
                        x -= 2.0f;
                        y -= 1.5f;
                        me->GetMotionMaster()->MovePoint(0, x, y, z);
                        me->SetTarget(player->GetGUID());
                        me->SetVisible(true);
                        FlyBackTimer = 4500;
                        break;
                    case 2:
                        if (!player->IsRessurectRequested())
                        {
                            me->HandleEmoteCommand(EMOTE_ONESHOT_CUSTOM_SPELL_01);
                            DoCast(player, SPELL_REVIVE, true);
                            Talk(WHISPER_REVIVE, player);
                        }
                        FlyBackTimer = 5000;
                        break;
                    case 3:
                        me->SetVisible(false);
                        FlyBackTimer = 3000;
                        break;
                    case 4:
                        me->DisappearAndDie();
                        break;
                    default:
                        //Nothing To DO
                        break;
                }
                ++phase;
            } else FlyBackTimer-=diff;
        }
    };

};

uint32 race_summon[10][2] =
{
    { 52473, 52474 },
    { 52484, 52485 },
    { 52475, 52479 },
    { 52481, 52480 },
    { 52471, 52472 },
    { 52483, 52482 },
    { 52459, 52458 },
    { 52469, 52470 },
    { 52487, 52486 },
    { 52468, 52466 }
};

uint32 race_dk_outfit[10][2] =
{
    { 51520, 51534 },
    { 51543, 51544 },
    { 51538, 51537 },
    { 51535, 51536 },
    { 51549, 51550 },
    { 51547, 51548 },
    { 51539, 51540 },
    { 51546, 51545 },
    { 51551, 51552 },
    { 51541, 51542 }
};

enum eActiveModus
{
    SUMMON_TO_LIFE = 1,
    SUMMON_TO_KILL,
    KILL_INITIATE,
    DK_DRESS_INITIATE,
    DK_SEND_AWAY,
    WORK_DONE = 9,
    BORN_TO_LIFE = 1,
    BORN_TO_DIE,
};

// npc 28383
class npc_acherus_necromancer : public CreatureScript
{
public:
    npc_acherus_necromancer() : CreatureScript("npc_acherus_necromancer") { }

    struct npc_acherus_necromancerAI : public ScriptedAI
    {
        npc_acherus_necromancerAI(Creature* creature) : ScriptedAI(creature) { }

        uint32 m_phase;
        uint32 m_timer;
        uint8 m_command;    // 1=SummonToLife 2=SummonToKill 3=Kill 4=Dress
        uint8 m_gender;     // 0=male 1=female
        uint8 m_race;
        Position m_position;
        Creature* m_npc;    // the summoned Initiate
        Creature* m_ghoul1;
        Creature* m_ghoul2;
        Creature* m_ghoul3;
        uint32 m_entry;
        uint32 m_dress;
        bool m_WorkDone;

        void Reset() override
        {
            m_phase = 0;
            m_timer = 0;
            m_npc = NULL;
            m_ghoul1 = NULL;
            m_ghoul2 = NULL;
            m_ghoul3 = NULL;
            m_entry = 0;
            m_dress = 0;
            m_command = WORK_DONE;
            m_gender = 0;
            m_race = 0;
            m_WorkDone = false;
        }

        void CreateInitiantValues()
        {
            float my_angle = me->GetAngle(me);
            m_position = me->GetNearPosition(7.7f, my_angle);
            m_position.SetOrientation(m_position.GetOrientation() + 3.14f);
            m_gender = urand(0, 1);
            m_race = urand(0, 9);
        }

        void StartAnimation(uint8 command)
        {
            m_phase = 1;
            m_command = command;
            m_timer = 200;
            m_WorkDone = false;
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
            if (m_phase == 0 || m_WorkDone)
                return;
            
            switch (m_command)
            {
            case SUMMON_TO_LIFE:
                WorkSummonInitiate(BORN_TO_LIFE);
                break;
            case SUMMON_TO_KILL:
                WorkSummonInitiate(BORN_TO_DIE);
                break;
            case KILL_INITIATE:
                WorkKillInitiate();
                break;
            case DK_DRESS_INITIATE:
                WorkDKDressInitiate();
                break;
            case DK_SEND_AWAY:
                WorkDKSendAwayInitiate();
                break;
            }
        }

        void WorkSummonInitiate(uint8 work)
        {
            switch (m_phase)
            {
                case 1: // summon initiate
                    Talk(0);
                    m_timer = 2000;
                    m_phase = 2;
                    break;
                case 2:
                    DoCast(me, 51516, true); // visual spell ReBorn
                    m_timer = 10000;
                    m_phase = 3;
                    break;
                case 3: // summon one of 10 races.. both gender possible.. 
                {
                    
                    m_entry = race_summon[m_race][m_gender];
                    if (m_npc = me->SummonCreature(m_entry, m_position, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 70000))
                    {
                        m_npc->SetLevel(55);
                        m_npc->SetMaxHealth(3700);
                        m_npc->SetHealth(3659);
                        m_npc->SetArmor(4732);
                    }
                    m_timer = 2000;
                    m_phase = 4;
                    break;
                }
                case 4:
                    if (IsCreatureAlive(m_npc))
                    {
                        if (work == BORN_TO_DIE)
                            m_npc->AI()->Talk(0);
                        else
                            m_npc->AI()->Talk(1);
                    }
                    m_timer = 6000;
                    m_phase = 5;
                    break;
                case 5:
                    m_phase = 0;
                    m_timer = 0;
                    m_WorkDone = true;
                    break;
            }
        }

        void WorkKillInitiate()
        {
            switch (m_phase)
            {
                case 1:
                    m_timer = 1000;
                    m_phase = 2;
                    break;
                case 2: 
                    Talk(2);  // say: Right away, instructor.
                    m_timer = 5000;
                    m_phase = 3;
                    break;
                case 3:
                    Talk(1); // say: Rise, minions. Rise and feast upon the weak!
                    m_timer = 2000;
                    m_phase = 4;
                    break;
                case 4:
                    me->HandleEmote(EMOTE_STATE_USE_STANDING);
                    if (m_npc) // summon the ghouls..
                    {
                        Position pos = m_npc->GetNearPosition(3.0f, 0.0f);
                        if (m_ghoul1 = me->SummonCreature(28405, pos, TEMPSUMMON_TIMED_DESPAWN, 20000))
                        {
                            m_ghoul1->SetFacingToObject(m_npc);
                            m_ghoul1->HandleEmoteState(EMOTE_ONESHOT_ATTACK1H);
                        }

                        pos = m_npc->GetNearPosition(3.0f, 2.095f);
                        if (m_ghoul2 = me->SummonCreature(28405, pos, TEMPSUMMON_TIMED_DESPAWN, 20000))
                        {
                            m_ghoul2->SetFacingToObject(m_npc);
                            m_ghoul2->HandleEmoteState(EMOTE_ONESHOT_ATTACK1H);
                        }

                        pos = m_npc->GetNearPosition(3.0f, 4.19f);
                        if (m_ghoul3 = me->SummonCreature(28405, pos, TEMPSUMMON_TIMED_DESPAWN, 20000))
                        {
                            m_ghoul3->Attack(m_npc, true);
                            m_npc->Attack(m_ghoul3, true);
                            m_ghoul3->CallAssistance();
                        }
                    }

                    m_timer = 1000;
                    m_phase = 5;
                    break;
                case 5:
                    if (IsCreatureDeath(m_npc))
                    {
                        m_phase = 6;
                        m_timer = 3000;
                        break;
                    }
                    break;
                case 6:
                    me->HandleEmote(EMOTE_ONESHOT_NONE);
                    // kill ghouls
                    if (IsCreatureAlive(m_ghoul1))
                        m_ghoul1->DespawnOrUnsummon();

                    if (IsCreatureAlive(m_ghoul2))
                        m_ghoul2->DespawnOrUnsummon();

                    if (IsCreatureAlive(m_ghoul3))
                        m_ghoul3->DespawnOrUnsummon();

                    m_phase = 7;
                    break;
                case 7:
                    m_phase = 0;
                    m_timer = 0;
                    m_WorkDone = true;
                    break;
            }
        }

        void WorkDKDressInitiate()
        {
            switch (m_phase)
            {
                case 1:
                    m_timer = 1000;
                    m_phase = 2;
                    break;
                case 2: 
                    Talk(3);
                    if (IsCreatureAlive(m_npc))
                    {
                        me->SetWalk(true);
                        Position pos = m_npc->GetNearPosition(1.0f, me->GetOrientation());
                        me->GetMotionMaster()->MovePoint(0, pos);
                    }
                    m_timer = 4000;
                    m_phase = 3;
                    break;
                case 3:
                    if (IsCreatureAlive(m_npc))
                    {
                        me->HandleEmote(EMOTE_STATE_USE_STANDING);
                        m_dress = race_dk_outfit[m_race][m_gender];
                        m_npc->CastSpell(m_npc, m_dress, true);
                    }
                    m_phase = 4;
                    break;
                case 4:
                {
                    me->HandleEmote(EMOTE_ONESHOT_NONE);
                    Position pos = me->GetHomePosition();
                    me->GetMotionMaster()->MovePoint(1, pos);                    
                    m_timer = 4000;
                    m_phase = 5;
                    break;
                }
                case 5:
                    me->SetFacingTo(me->GetHomePosition().GetOrientation());
                    m_phase = 6;
                    break;
                case 6:
                    m_phase = 0;
                    m_timer = 0;
                    m_WorkDone = true;
                    break;
            }
        }

        void WorkDKSendAwayInitiate()
        {
            switch (m_phase)
            {
            case 1: // dk send away initiate
                m_phase = 2;
                m_timer = 2000;
                break;
            case 2:
                if (IsCreatureAlive(m_npc))
                    m_npc->AI()->Talk(2);

                m_phase = 3;
                m_timer = 5000;
                break;
            case 3:
                if (IsCreatureAlive(m_npc))
                {
                    m_npc->GetMotionMaster()->MovePath(5247300, false);
                }
                m_phase = 4;
                break;
            case 4:
                m_phase = 0;
                m_timer = 0;
                m_WorkDone = true;
                break;
            }
        }

        bool IsCreatureDeath(Creature* npc)
        {
            if (!npc)
                return true;
            if (!npc->IsInWorld())
                return true;
            return npc->IsDead();
        }

        bool IsCreatureAlive(Creature* npc)
        {
            return !IsCreatureDeath(npc);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_acherus_necromancerAI(creature);
    }
};

// npc 28357
class npc_instructor_razuvious : public CreatureScript
{
public:
    npc_instructor_razuvious() : CreatureScript("npc_instructor_razuvious") { }

    struct npc_instructor_razuviousAI : public ScriptedAI
    {
        npc_instructor_razuviousAI(Creature* creature) : ScriptedAI(creature) { }

        uint32 m_phase;
        uint32 m_timer;
        uint8 m_born_modus; // 1=born to life    2=born to kill

        void Reset() override
        {
            m_phase = 0;
            m_timer = 0;
            m_born_modus = 0;
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type != WAYPOINT_MOTION_TYPE)
                return;

            switch (id)
            {
            case 7:
                m_born_modus = urand(1, 2);
                m_phase = 1;
                m_timer = 200;
                break;
            case 11:
                m_born_modus = urand(1, 2);
                m_phase = 1;
                m_timer = 200;
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
            if (m_phase == 0 || m_born_modus == 0)
                return;

            switch (m_born_modus)
            {
            case BORN_TO_LIFE:
                VideoBornToLife();
                break;
            case BORN_TO_DIE:
                VideoBornToDie();
                break;
            }
        }

        void VideoBornToLife()
        {
            switch (m_phase)
            {
            case 1: // life video
                if (Creature* npc = me->FindNearestCreature(28383, 10.0f))
                    if (npc_acherus_necromancer::npc_acherus_necromancerAI* NpcAI = CAST_AI(npc_acherus_necromancer::npc_acherus_necromancerAI, npc->GetAI()))
                    {
                        NpcAI->CreateInitiantValues();
                        Position pos = NpcAI->m_position;
                        float angle = me->GetAngle(pos.m_positionX, pos.m_positionY);
                        me->SetFacingTo(angle);
                    }

                m_timer = 2000;
                m_phase = 2;
                break;
            case 2: 
                Talk(5); // say this one
                me->HandleEmote(EMOTE_ONESHOT_POINT); // point to him
                m_timer = 3000;
                m_phase = 3;
                break;
            case 3:
                if (Creature* npc = me->FindNearestCreature(28383, 10.0f))
                    if (npc_acherus_necromancer::npc_acherus_necromancerAI* NpcAI = CAST_AI(npc_acherus_necromancer::npc_acherus_necromancerAI, npc->GetAI()))
                        NpcAI->StartAnimation(SUMMON_TO_LIFE);

                m_phase = 4;
                break;
            case 4:
                if (Creature* npc = me->FindNearestCreature(28383, 10.0f))
                    if (npc_acherus_necromancer::npc_acherus_necromancerAI* NpcAI = CAST_AI(npc_acherus_necromancer::npc_acherus_necromancerAI, npc->GetAI()))
                        if (NpcAI->m_WorkDone)
                            m_phase = 5;
                break;
            case 5:
                Talk(3); // say: The Lich King will be pleased with this initiate.
                m_timer = 5000;
                m_phase = 6;
                break;
            case 6:
                Talk(4); // say: Place upon it the trappings befitting a herald of Arthas
                m_timer = 5000;
                m_phase = 7;
                break;
            case 7:
                if (Creature* npc = me->FindNearestCreature(28383, 10.0f))
                    if (npc_acherus_necromancer::npc_acherus_necromancerAI* NpcAI = CAST_AI(npc_acherus_necromancer::npc_acherus_necromancerAI, npc->GetAI()))
                        NpcAI->StartAnimation(DK_DRESS_INITIATE);

                m_phase = 8;
                break;
            case 8:
                if (Creature* npc = me->FindNearestCreature(28383, 10.0f))
                    if (npc_acherus_necromancer::npc_acherus_necromancerAI* NpcAI = CAST_AI(npc_acherus_necromancer::npc_acherus_necromancerAI, npc->GetAI()))
                        if (NpcAI->m_WorkDone)
                            m_phase = 9;
                break;
            case 9:
                Talk(6); // say: Listen, death knight... Listen for the voice of your master. He calls to you now
                m_timer = 5000;
                m_phase = 10;
                break;
            case 10:
                Talk(7); // say: Stand and be measured! Rise, for your master awaits your arrival. Go now
                m_timer = 5000;
                m_phase = 11;
                break;
            case 11:
                if (Creature* npc = me->FindNearestCreature(28383, 10.0f))
                    if (npc_acherus_necromancer::npc_acherus_necromancerAI* NpcAI = CAST_AI(npc_acherus_necromancer::npc_acherus_necromancerAI, npc->GetAI()))
                        NpcAI->StartAnimation(DK_SEND_AWAY);

                m_phase = 12;
                break;
            case 12:
                m_timer = 0;
                m_phase = 0;
                m_born_modus = 0;
                break;
            }
        }

        void VideoBornToDie()
        {
            switch (m_phase)
            {
                case 1: // life video
                    if (Creature* npc = me->FindNearestCreature(28383, 10.0f))
                        if (npc_acherus_necromancer::npc_acherus_necromancerAI* NpcAI = CAST_AI(npc_acherus_necromancer::npc_acherus_necromancerAI, npc->GetAI()))
                        {
                            NpcAI->CreateInitiantValues();
                            Position pos = NpcAI->m_position;
                            float angle = me->GetAngle(pos.m_positionX, pos.m_positionY);
                            me->SetFacingTo(angle); 
                        }

                    m_timer = 2000;
                    m_phase = 2;
                    break;
                case 2: // die video
                    Talk(5); // say this one
                    me->HandleEmote(EMOTE_ONESHOT_POINT); // point 
                    m_timer = 3000;
                    m_phase = 3;
                    break;
                case 3:
                    if (Creature* npc = me->FindNearestCreature(28383, 10.0f))
                        if (npc_acherus_necromancer::npc_acherus_necromancerAI* NpcAI = CAST_AI(npc_acherus_necromancer::npc_acherus_necromancerAI, npc->GetAI()))
                            NpcAI->StartAnimation(SUMMON_TO_KILL);

                    m_phase = 4;
                    break;
                case 4:
                    if (Creature* npc = me->FindNearestCreature(28383, 10.0f))
                        if (npc_acherus_necromancer::npc_acherus_necromancerAI* NpcAI = CAST_AI(npc_acherus_necromancer::npc_acherus_necromancerAI, npc->GetAI()))
                            if (NpcAI->m_WorkDone)
                                m_phase = 5;
                    break;
                case 5:
                    Talk(0); // say: Another failure...
                    m_timer = 5000;
                    m_phase = 6;
                    break;
                case 6:
                    Talk(1); // say: You have been measured and found wanting...
                    m_timer = 5000;
                    m_phase = 7;
                    break;
                case 7:
                    Talk(2); // say Dispose of it...
                    m_timer = 5000;
                    m_phase = 8;
                    break;
                case 8:
                    if (Creature* npc = me->FindNearestCreature(28383, 10.0f))
                        if (npc_acherus_necromancer::npc_acherus_necromancerAI* NpcAI = CAST_AI(npc_acherus_necromancer::npc_acherus_necromancerAI, npc->GetAI()))
                            NpcAI->StartAnimation(KILL_INITIATE);

                    m_phase = 9;
                    break;
                case 9:  
                    if (Creature* npc = me->FindNearestCreature(28383, 10.0f))
                        if (npc_acherus_necromancer::npc_acherus_necromancerAI* NpcAI = CAST_AI(npc_acherus_necromancer::npc_acherus_necromancerAI, npc->GetAI()))
                            if (NpcAI->m_WorkDone)
                                m_phase = 10;
                    break;               
                case 10:
                    m_timer = 0;
                    m_phase = 0;
                    m_born_modus = 0;
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_instructor_razuviousAI(creature);
    }
};

// npc 28406 -- some initiate are mounted and flying
class npc_dk_initiate_28406 : public CreatureScript
{
public:
    npc_dk_initiate_28406() : CreatureScript("npc_dk_initiate_28406") { }

    enum eInitiate
    {
        QUEST_DEATHS_CHALLENGE = 12733,
        SPELL_EBON_HOLD_DUEL_CREDIT = 29025,
    };

    struct npc_dk_initiate_28406AI : public ScriptedAI
    {
        npc_dk_initiate_28406AI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            if (me->IsMounted())
            {
                me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_HOVER);
                me->AddUnitMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);
                me->SetDisableGravity(true);
                me->SetCanFly(true);
            }
            else
            {
                me->setFaction(12);
            }
                
        }

        void JustDied(Unit* killer) 
        { 
            if (Player* player = killer->ToPlayer())
                if (player->GetQuestStatus(QUEST_DEATHS_CHALLENGE) == QUEST_STATUS_INCOMPLETE)
                {
                    me->CastSpell(killer,SPELL_EBON_HOLD_DUEL_CREDIT);
                }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_dk_initiate_28406AI(creature);
    }
};


void AddSC_the_scarlet_enclave()
{
    new npc_valkyr_battle_maiden();
    new npc_acherus_necromancer();
    new npc_instructor_razuvious();
    new npc_dk_initiate_28406();

}
