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
#include "ScriptedEscortAI.h"
#include "PassiveAI.h"
#include "Player.h"
#include "CreatureTextMgr.h"
#include "Vehicle.h"
#include "GameObjectAI.h"

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

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_valkyr_battle_maidenAI(creature);
    }

    struct npc_valkyr_battle_maidenAI : public PassiveAI
    {
        npc_valkyr_battle_maidenAI(Creature* creature) : PassiveAI(creature) { }

        uint32 FlyBackTimer;
        float x, y, z;
        uint32 phase;

        void Reset() override
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

        void UpdateAI(uint32 diff) override
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

uint32 acherus_unworthy_initiate[5] =
{
    29519,
    29520,    
    29565,
    29566,
    29567
};

uint32 acherus_soul_prison[12] =
{
    191577,
    191580,
    191581,
    191582,
    191583,
    191584,
    191585,
    191586,
    191587,
    191588,
    191589,
    191590
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
        SAY_DUEL = 0,
        FACTION_HOSTILE = 2068,
        SPELL_DUEL = 52996,
        SPELL_DUEL_TRIGGERED = 52990,
        SPELL_DUEL_VICTORY = 52994,
        SPELL_DUEL_FLAG = 52991,
    };
    
    

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF)
        {
            player->CLOSE_GOSSIP_MENU();

            if (player->IsInCombat() || creature->IsInCombat())
                return true;

            if (npc_dk_initiate_28406AI* initiateAI = CAST_AI(npc_dk_initiate_28406AI, creature->AI()))
            {
                if (initiateAI->m_IsDuelInProgress)
                    return true;
            }

            creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNK_15);

            sCreatureTextMgr->SendChat(creature, SAY_DUEL, NULL, CHAT_MSG_ADDON, LANG_ADDON, TEXT_RANGE_NORMAL, 0, TEAM_OTHER, false, player);

            player->CastSpell(creature, SPELL_DUEL, false);
            player->CastSpell(player, SPELL_DUEL_FLAG, true);
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (player->GetQuestStatus(QUEST_DEATHS_CHALLENGE) == QUEST_STATUS_INCOMPLETE && creature->IsFullHealth())
        {
            if (player->HealthBelowPct(10))
                return true;

            if (player->IsInCombat() || creature->IsInCombat())
                return true;
            
            player->ADD_GOSSIP_ITEM_DB(9765, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        }
        return true;
    }

    struct npc_dk_initiate_28406AI : public CombatAI
    {
        npc_dk_initiate_28406AI(Creature* creature) : CombatAI(creature) { }

        bool m_lose;
        uint64 m_DuelerGUID;
        uint32 m_DuelTimer;
        bool m_IsDuelInProgress;

        void Reset() override
        {
            m_lose = false;
            m_DuelerGUID = 0;
            m_DuelTimer = 5000;
            m_IsDuelInProgress = false;

            if (me->IsMounted())
            {
                me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_HOVER);
                me->AddUnitMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);
                me->SetDisableGravity(true);
                me->SetCanFly(true);
            }
            else if (me->GetPositionZ() < 250.0f)
            {
                me->RestoreFaction();
                CombatAI::Reset();
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNK_15);              
                me->SetNoCallAssistance(true);
                me->SetNoSearchAssistance(true);
            }
        }

        void SpellHit(Unit* caster, const SpellInfo* spell) override
        {
            if (!m_IsDuelInProgress && spell->Id == SPELL_DUEL)
            {
                m_DuelerGUID = caster->GetGUID();
                m_IsDuelInProgress = true;
            }
        }

        void DamageTaken(Unit* hitter, uint32 &damage) override
        {
            if (m_IsDuelInProgress && hitter->IsControlledByPlayer())
            {
                if (hitter->GetGUID() != m_DuelerGUID && hitter->GetOwnerGUID() != m_DuelerGUID) // other players cannot help
                    damage = 0;
                else if (damage >= me->GetHealth())
                {
                    damage = 0;

                    if (!m_lose)
                    {
                        hitter->RemoveGameObject(SPELL_DUEL_FLAG, true);
                        hitter->AttackStop();
                        me->CastSpell(hitter, SPELL_DUEL_VICTORY, true);
                        m_lose = true;
                        me->CastSpell(me, 7267, true);
                        me->RestoreFaction();

                       // if (Player* player = hitter->ToPlayer())
                         //   if (player->GetQuestStatus(QUEST_DEATHS_CHALLENGE) == QUEST_STATUS_INCOMPLETE)
                           //     player->KilledMonsterCredit(SPELL_EBON_HOLD_DUEL_CREDIT);
                    }
                }
            }
        }

        void JustDied(Unit* killer) 
        { 
            //if (Player* player = killer->ToPlayer())
              //  if (player->GetQuestStatus(QUEST_DEATHS_CHALLENGE) == QUEST_STATUS_INCOMPLETE)
                    //player->KilledMonsterCredit(SPELL_EBON_HOLD_DUEL_CREDIT);
        }

        void UpdateAI(uint32 uiDiff) override
        {
            if (!UpdateVictim())
            {
                if (m_IsDuelInProgress)
                {
                    if (m_DuelTimer <= uiDiff)
                    {
                        me->setFaction(FACTION_HOSTILE);

                        if (Unit* unit = Unit::GetUnit(*me, m_DuelerGUID))
                            AttackStart(unit);
                    }
                    else
                        m_DuelTimer -= uiDiff;
                }
                return;
            }

            if (m_IsDuelInProgress)
            {
                if (m_lose)
                {
                    if (!me->HasAura(7267))
                        EnterEvadeMode();
                    return;
                }
                else if (me->GetVictim() && me->EnsureVictim()->GetTypeId() == TYPEID_PLAYER && me->EnsureVictim()->HealthBelowPct(10))
                {
                    me->EnsureVictim()->CastSpell(me->GetVictim(), 7267, true); // beg
                    me->EnsureVictim()->RemoveGameObject(SPELL_DUEL_FLAG, true);
                    EnterEvadeMode();
                    return;
                }
            }

            /// @todo spells

            CombatAI::UpdateAI(uiDiff);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_dk_initiate_28406AI(creature);
    }
};

// 29519 29520 29565 29566 29567: unworthy_initiate
class npc_unworthy_initiate : public CreatureScript
{
public:
    npc_unworthy_initiate() : CreatureScript("npc_unworthy_initiate") { }

    enum eUnworthyInitiatePhase
    {
        PHASE_CHAINED = 0,
        PHASE_TO_EQUIP,
        PHASE_EQUIPING,
        PHASE_TO_ATTACK,
        PHASE_ATTACKING,
    };

    enum eMisc
    {
        EVENT_ICY_TOUCH = 1,
        EVENT_PLAGUE_STRIKE = 2,
        EVENT_BLOOD_STRIKE = 3,
        EVENT_DEATH_COIL = 4,

        GCD_CAST = 1,

        SPELL_SOUL_PRISON_CHAIN_SELF = 54612,
        SPELL_SOUL_PRISON_CHAIN = 54613,
        SPELL_DK_INITIATE_VISUAL = 51519,
        SPELL_ICY_TOUCH = 52372,
        SPELL_PLAGUE_STRIKE = 52373,
        SPELL_BLOOD_STRIKE = 52374,
        SPELL_DEATH_COIL = 52375,

        SAY_EVENT_START = 0,
        SAY_EVENT_ATTACK = 1,
    };

    struct npc_unworthy_initiateAI : public ScriptedAI
    {
        npc_unworthy_initiateAI(Creature* creature) : ScriptedAI(creature)
        {
            me->SetReactState(REACT_PASSIVE);
            if (!me->GetCurrentEquipmentId())
                me->SetCurrentEquipmentId(me->GetOriginalEquipmentId());
        }

        uint64 playerGUID;
        eUnworthyInitiatePhase phase;
        uint32 wait_timer;
        float anchorX, anchorY;
        uint64 anchorGUID;

        EventMap events;

        void Reset()
        {
            anchorGUID = 0;
            phase = PHASE_CHAINED;
            events.Reset();
            me->setFaction(7);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            me->SetUInt32Value(UNIT_FIELD_BYTES_1, 8);
            me->LoadEquipment(0, true);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_ICY_TOUCH, 1000, GCD_CAST);
            events.ScheduleEvent(EVENT_PLAGUE_STRIKE, 3000, GCD_CAST);
            events.ScheduleEvent(EVENT_BLOOD_STRIKE, 2000, GCD_CAST);
            events.ScheduleEvent(EVENT_DEATH_COIL, 5000, GCD_CAST);
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type != POINT_MOTION_TYPE)
                return;

            if (id == 1)
            {
                wait_timer = 5000;
                me->CastSpell(me, SPELL_DK_INITIATE_VISUAL, true);

                if (Player* starter = ObjectAccessor::GetPlayer(*me, playerGUID))
                    sCreatureTextMgr->SendChat(me, SAY_EVENT_ATTACK, NULL, CHAT_MSG_ADDON, LANG_ADDON, TEXT_RANGE_NORMAL, 0, TEAM_OTHER, false, starter);

                phase = PHASE_TO_ATTACK;
            }
        }

        void EventStart(Creature* anchor, Player* target)
        {
            wait_timer = 5000;
            phase = PHASE_TO_EQUIP;

            me->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
            me->RemoveAurasDueToSpell(SPELL_SOUL_PRISON_CHAIN_SELF);
            me->RemoveAurasDueToSpell(SPELL_SOUL_PRISON_CHAIN);

            float z;
            anchor->GetContactPoint(me, anchorX, anchorY, z, 1.0f);

            playerGUID = target->GetGUID();
            Talk(SAY_EVENT_START);
        }

        void UpdateAI(uint32 diff)
        {
            switch (phase)
            {
            case PHASE_CHAINED:
                if (!anchorGUID)
                {
                    if (Creature* anchor = me->FindNearestCreature(29521, 30))
                    {
                        anchor->AI()->SetGUID(me->GetGUID());
                        anchor->CastSpell(me, SPELL_SOUL_PRISON_CHAIN, true);
                        anchorGUID = anchor->GetGUID();
                    }
                    else
                        TC_LOG_ERROR("scripts", "npc_unworthy_initiateAI: unable to find anchor!");

                    float dist = 99.0f;
                    GameObject* prison = NULL;

                    for (uint8 i = 0; i < 12; ++i)
                    {
                        if (GameObject* temp_prison = me->FindNearestGameObject(acherus_soul_prison[i], 30))
                        {
                            if (me->IsWithinDist(temp_prison, dist, false))
                            {
                                dist = me->GetDistance2d(temp_prison);
                                prison = temp_prison;
                            }
                        }
                    }

                    if (prison)
                        prison->ResetDoorOrButton();
                    else
                        TC_LOG_ERROR("scripts", "npc_unworthy_initiateAI: unable to find prison!");
                }
                break;
            case PHASE_TO_EQUIP:
                if (wait_timer)
                {
                    if (wait_timer > diff)
                        wait_timer -= diff;
                    else
                    {
                        me->GetMotionMaster()->MovePoint(1, anchorX, anchorY, me->GetPositionZ());
                        //TC_LOG_DEBUG("scripts", "npc_unworthy_initiateAI: move to %f %f %f", anchorX, anchorY, me->GetPositionZ());
                        phase = PHASE_EQUIPING;
                        wait_timer = 0;
                    }
                }
                break;
            case PHASE_TO_ATTACK:
                if (wait_timer)
                {
                    if (wait_timer > diff)
                        wait_timer -= diff;
                    else
                    {
                        me->setFaction(14);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                        phase = PHASE_ATTACKING;

                        if (Player* target = ObjectAccessor::GetPlayer(*me, playerGUID))
                            AttackStart(target);
                        wait_timer = 0;
                    }
                }
                break;
            case PHASE_ATTACKING:
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_ICY_TOUCH:
                        DoCastVictim(SPELL_ICY_TOUCH);
                        events.DelayEvents(1000, GCD_CAST);
                        events.ScheduleEvent(EVENT_ICY_TOUCH, 5000, GCD_CAST);
                        break;
                    case EVENT_PLAGUE_STRIKE:
                        DoCastVictim(SPELL_PLAGUE_STRIKE);
                        events.DelayEvents(1000, GCD_CAST);
                        events.ScheduleEvent(EVENT_PLAGUE_STRIKE, 5000, GCD_CAST);
                        break;
                    case EVENT_BLOOD_STRIKE:
                        DoCastVictim(SPELL_BLOOD_STRIKE);
                        events.DelayEvents(1000, GCD_CAST);
                        events.ScheduleEvent(EVENT_BLOOD_STRIKE, 5000, GCD_CAST);
                        break;
                    case EVENT_DEATH_COIL:
                        DoCastVictim(SPELL_DEATH_COIL);
                        events.DelayEvents(1000, GCD_CAST);
                        events.ScheduleEvent(EVENT_DEATH_COIL, 5000, GCD_CAST);
                        break;
                    }
                }

                DoMeleeAttackIfReady();
                break;
            default:
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_unworthy_initiateAI(creature);
    }
};

// 29521 unworthy_initiate_anchor
class npc_unworthy_initiate_anchor : public CreatureScript
{
public:
    npc_unworthy_initiate_anchor() : CreatureScript("npc_unworthy_initiate_anchor") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_unworthy_initiate_anchorAI(creature);
    }

    struct npc_unworthy_initiate_anchorAI : public PassiveAI
    {
        npc_unworthy_initiate_anchorAI(Creature* creature) : PassiveAI(creature), prisonerGUID(0) { }

        uint64 prisonerGUID;

        void SetGUID(uint64 guid, int32 /*id*/) override
        {
            if (!prisonerGUID)
            prisonerGUID = guid;
        }

            uint64 GetGUID(int32 /*id*/) const override
        {
            return prisonerGUID;
        }
    };
};

// 191577 191580 191581 191582 191583 191584 191585 191586 191587 191588 191589 191590 gameobject acherus_soul_prison
class go_acherus_soul_prison : public GameObjectScript
{
public:
    go_acherus_soul_prison() : GameObjectScript("go_acherus_soul_prison") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (Creature* anchor = go->FindNearestCreature(29521, 15))
        if (uint64 prisonerGUID = anchor->AI()->GetGUID())
            if (Creature* prisoner = Creature::GetCreature(*player, prisonerGUID))
                CAST_AI(npc_unworthy_initiate::npc_unworthy_initiateAI, prisoner->AI())->EventStart(anchor, player);

        return false;
    }

};

Position const EyeOFAcherusFallPoint = { 2361.21f, -5660.45f, 496.7444f, 0.0f };

// 28511 eye_of_acherus
class npc_eye_of_acherus : public CreatureScript
{
public:
    npc_eye_of_acherus() : CreatureScript("npc_eye_of_acherus") { }

    enum EyeOfAcherus
    {
        DISPLAYID_EYE_HUGE = 26320,
        DISPLAYID_EYE_SMALL = 25499,

        SPELL_EYE_PHASEMASK = 70889,
        SPELL_EYE_VISUAL = 51892,
        SPELL_EYE_FL_BOOST_RUN = 51923,
        SPELL_EYE_FL_BOOST_FLY = 51890,
        SPELL_EYE_CONTROL = 51852,

        SAY_EYE_MOVE_START = 0,
        SAY_EYE_LAUNCHED = 1,
        SAY_EYE_UNDER_CONTROL = 2,
        SAY_EYE_CONTROL = 3,

        EVENT_MOVE_START = 1,

        POINT_EYE_FALL = 1,
        POINT_EYE_MOVE_END = 3
    };

    struct npc_eye_of_acherusAI : public ScriptedAI
    {
        npc_eye_of_acherusAI(Creature* creature) : ScriptedAI(creature)
        {
            me->SetDisplayId(me->GetCreatureTemplate()->Modelid1);
            if (Player* owner = me->GetCharmerOrOwner()->ToPlayer())
                owner->SendAutoRepeatCancel(me);

            me->SetReactState(REACT_PASSIVE);

            me->GetMotionMaster()->MovePoint(POINT_EYE_FALL, EyeOFAcherusFallPoint, false);

            Movement::MoveSplineInit init(me);
            init.MoveTo(EyeOFAcherusFallPoint.GetPositionX(), EyeOFAcherusFallPoint.GetPositionY(), EyeOFAcherusFallPoint.GetPositionZ(), false);
            init.SetFall();
            init.Launch();
        }

        void OnCharmed(bool /*apply*/) override { }

        void UpdateAI(uint32 diff) override
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_MOVE_START:
                {
                    DoCast(me, SPELL_EYE_FL_BOOST_RUN);

                    me->SetControlled(false, UNIT_STATE_ROOT);
                    if (Player* owner = me->GetCharmerOrOwner()->ToPlayer())
                    {
                        for (uint8 i = 0; i < MAX_MOVE_TYPE; ++i)
                            me->SetSpeed(UnitMoveType(i), owner->GetSpeedRate(UnitMoveType(i)), true);
                        Talk(SAY_EYE_MOVE_START, owner);
                        Talk(SAY_EYE_LAUNCHED, owner);
                    }
                    me->GetMotionMaster()->MovePath(me->GetEntry() * 100, false);
                    break;
                }
                default:
                    break;
                }
            }
        }

        void MovementInform(uint32 movementType, uint32 pointId) override
        {
            if (movementType == WAYPOINT_MOTION_TYPE && pointId == POINT_EYE_MOVE_END - 1)
            {
                me->SetByteValue(UNIT_FIELD_BYTES_2, 0, SHEATH_STATE_MELEE);
                me->RemoveAllAuras();

                if (Player* owner = me->GetCharmerOrOwner()->ToPlayer())
                {
                    owner->RemoveAura(SPELL_EYE_FL_BOOST_RUN);
                    for (uint8 i = 0; i < MAX_MOVE_TYPE; ++i)
                        me->SetSpeed(UnitMoveType(i), owner->GetSpeedRate(UnitMoveType(i)), true);

                    Talk(SAY_EYE_UNDER_CONTROL, owner);
                    Talk(SAY_EYE_CONTROL, owner);
                }
                me->SetDisableGravity(false);
                DoCast(me, SPELL_EYE_FL_BOOST_FLY);
            }

            if (movementType == POINT_MOTION_TYPE && pointId == POINT_EYE_FALL)
            {
                me->SetDisableGravity(true);
                me->SetControlled(true, UNIT_STATE_ROOT);
                _events.ScheduleEvent(EVENT_MOVE_START, 5000);
            }
        }

    private:
        EventMap _events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_eye_of_acherusAI(creature);
    }
};

// 28654  dark_rider_of_acherus
class npc_dark_rider_of_acherus : public CreatureScript
{
public:
    npc_dark_rider_of_acherus() : CreatureScript("npc_dark_rider_of_acherus") { }

    enum eDarkRiderOfAcherus
    {
        SAY_DARK_RIDER = 0,
        SPELL_DESPAWN_HORSE = 51918
    };

    struct npc_dark_rider_of_acherusAI : public ScriptedAI
    {
        npc_dark_rider_of_acherusAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset()
        {
            PhaseTimer = 4000;
            Phase = 0;
            Intro = false;
            TargetGUID = 0;
        }

        void UpdateAI(uint32 diff)
        {
            if (!Intro || !TargetGUID)
                return;

            if (PhaseTimer <= diff)
            {
                switch (Phase)
                {
                case 0:
                    Talk(SAY_DARK_RIDER);
                    PhaseTimer = 5000;
                    Phase = 1;
                    break;
                case 1:
                    if (Unit* target = ObjectAccessor::GetUnit(*me, TargetGUID))
                        DoCast(target, SPELL_DESPAWN_HORSE, true);
                    PhaseTimer = 3000;
                    Phase = 2;
                    break;
                case 2:
                    me->SetVisible(false);
                    PhaseTimer = 2000;
                    Phase = 3;
                    break;
                case 3:
                    me->DespawnOrUnsummon();
                    break;
                default:
                    break;
                }
            }
            else
                PhaseTimer -= diff;
        }

        void InitDespawnHorse(Unit* who)
        {
            if (!who)
                return;

            TargetGUID = who->GetGUID();
            me->SetWalk(true);
            me->SetSpeed(MOVE_RUN, 0.4f);
            me->GetMotionMaster()->MoveChase(who);
            me->SetTarget(TargetGUID);
            Intro = true;
        }

    private:
        uint32 PhaseTimer;
        uint32 Phase;
        bool Intro;
        uint64 TargetGUID;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_dark_rider_of_acherusAI(creature);
    }
};

// 28653 salanar_the_horseman
class npc_salanar_the_horseman_28653 : public CreatureScript
{
public:
    npc_salanar_the_horseman_28653() : CreatureScript("npc_salanar_the_horseman_28653") { }

    enum Spells_Salanar
    {
        SPELL_REALM_OF_SHADOWS = 52693,
        SPELL_EFFECT_STOLEN_HORSE = 52263,
        SPELL_DELIVER_STOLEN_HORSE = 52264,
        SPELL_CALL_DARK_RIDER = 52266,
        SPELL_EFFECT_OVERTAKE = 52349
    };

    struct npc_salanar_the_horseman_28653AI : public ScriptedAI
    {
        npc_salanar_the_horseman_28653AI(Creature* creature) : ScriptedAI(creature) { }

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_DELIVER_STOLEN_HORSE)
            {
                if (caster->GetTypeId() == TYPEID_UNIT && caster->IsVehicle())
                {
                    if (Unit* charmer = caster->GetCharmer())
                    {
                        if (charmer->HasAura(SPELL_EFFECT_STOLEN_HORSE))
                        {
                            charmer->RemoveAurasDueToSpell(SPELL_EFFECT_STOLEN_HORSE);
                            caster->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                            caster->setFaction(35);
                            DoCast(caster, SPELL_CALL_DARK_RIDER, true);
                            if (Creature* Dark_Rider = me->FindNearestCreature(28654, 15))
                                CAST_AI(npc_dark_rider_of_acherus::npc_dark_rider_of_acherusAI, Dark_Rider->AI())->InitDespawnHorse(caster);
                        }
                    }
                }
            }
        }

        void MoveInLineOfSight(Unit* who)
        {
            ScriptedAI::MoveInLineOfSight(who);

            if (who->GetTypeId() == TYPEID_UNIT && who->IsVehicle() && me->IsWithinDistInMap(who, 5.0f))
            {
                if (Unit* charmer = who->GetCharmer())
                {
                    if (Player* player = charmer->ToPlayer())
                    {
                        // for quest Into the Realm of Shadows(12687)
                        if (me->GetEntry() == 28788 && player->GetQuestStatus(12687) == QUEST_STATUS_INCOMPLETE)
                        {
                            player->GroupEventHappens(12687, me);
                            charmer->RemoveAurasDueToSpell(SPELL_EFFECT_OVERTAKE);
                            if (Creature* creature = who->ToCreature())
                            {
                                creature->DespawnOrUnsummon();
                                //creature->Respawn(true);
                            }
                        }

                        if (player->HasAura(SPELL_REALM_OF_SHADOWS))
                            player->RemoveAurasDueToSpell(SPELL_REALM_OF_SHADOWS);
                    }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_salanar_the_horseman_28653AI(creature);
    }
};

// 28788 salanar_the_horseman
class npc_salanar_the_horseman_28788 : public CreatureScript
{
public:
    npc_salanar_the_horseman_28788() : CreatureScript("npc_salanar_the_horseman_28788") { }

    enum e28788
    {
        SPELL_REALM_OF_SHADOWS = 52275,
        SPELL_DEATH_RACE_COMPLETE = 52361,
    };

    struct npc_salanar_the_horseman_28788AI : public ScriptedAI
    {
        npc_salanar_the_horseman_28788AI(Creature* creature) : ScriptedAI(creature) { }

        uint32 m_timer;
        uint32 m_phase;

        void Reset() override
        {
            m_timer = 1000;
            m_phase = 1;
            if (Player* player = me->FindNearestPlayer(10.0f))
                me->SetFacingToObject(player);
        }

        void UpdateAI(uint32 diff)
        {
            if (m_timer <= diff)
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
            case 1:
                Talk(0);
                m_phase = 2;
                m_timer = 6000;
                break;
            case 2:
                if (Unit* owner = me->GetCharmerOrOwnerOrSelf())
                    if (Player* player = owner->ToPlayer())
                    {
                        player->Dismount();
                        player->RemoveAura(SPELL_REALM_OF_SHADOWS);
                        player->CastSpell(player, SPELL_DEATH_RACE_COMPLETE);
                        m_phase = 3;
                        m_timer = 5000;
                    }
                break;
            case 3:
                me->DespawnOrUnsummon();
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_salanar_the_horseman_28788AI(creature);
    }
};

// 28768
class npc_dark_rider_of_acherus_28768 : public CreatureScript
{
public:
    npc_dark_rider_of_acherus_28768() : CreatureScript("npc_dark_rider_of_acherus_28768") { }

    enum e28768
    {
        NPC_ACHERUS_DEATHCHARGER = 28782,
        SPELL_SUMMON_DARK_RIDER_OF_ACHERUS = 52289,
        SPELL_DESPAWN_DARK_RIDER_OF_ACHERUS = 52294,
    };

    struct npc_dark_rider_of_acherus_28768AI : public ScriptedAI
    {
        npc_dark_rider_of_acherus_28768AI(Creature* creature) : ScriptedAI(creature) { }

        uint32 m_timer;
        uint32 m_phase;

        void Reset() override
        {
            m_timer = 1000;
            m_phase = 1;
            if (me->FindNearestCreature(28653, 15.0f))
                me->DespawnOrUnsummon();
        }

        void EnterCombat(Unit* who) override
        {
            me->ExitVehicle();
            me->HandleEmoteState(EMOTE_ONESHOT_NONE);
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_NONE);
            me->SetByteFlag(UNIT_FIELD_BYTES_1, 0, 0x00);
            me->SetByteFlag(UNIT_FIELD_BYTES_2, 0, 0x00);
            me->Attack(who, true);
        }

        void JustDied(Unit* killer) override
        {
            if (Creature* deathcharger = me->FindNearestCreature(NPC_ACHERUS_DEATHCHARGER, 30))
                if (Player* player = killer->ToPlayer())
                    if (deathcharger->GetTypeId() == TYPEID_UNIT && deathcharger->IsVehicle())
                    {
                        deathcharger->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                        deathcharger->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        deathcharger->setFaction(35);
                    }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_dark_rider_of_acherus_28768AI(creature);
    }
};

// 28782
class npc_acherus_deathcharger_28782 : public CreatureScript
{
public:
    npc_acherus_deathcharger_28782() : CreatureScript("npc_acherus_deathcharger_28782") { }

    enum e28782
    {   
        QUEST_INTO_THE_REALM_OF_SHADOW = 12687,
        NPC_ACHERUS_DEATHCHARGER = 28782,
        NPC_DARK_RIDER_OF_ACHERUS = 28768,
        SPELL_SUMMON_DARK_RIDER_OF_ACHERUS = 52289,
        SPELL_DESPAWN_DARK_RIDER_OF_ACHERUS = 52294,
    };

    struct npc_acherus_deathcharger_28782AI : public ScriptedAI
    {
        npc_acherus_deathcharger_28782AI(Creature* creature) : ScriptedAI(creature) { }

        uint32 m_timer;
        uint32 m_phase;
        uint64 m_darkriderGUID;

        void Reset() override
        {
            m_timer = 1000;
            m_phase = 0;
            m_darkriderGUID = NULL;
            if (me->FindNearestCreature(28653, 15.0f))
                me->DespawnOrUnsummon();
        }

        void OnSpellClick(Unit* clicker, bool& result) override
        {
            if (me->getFaction() == 35)
                if (Player* player = clicker->ToPlayer())
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        if (player->GetQuestStatus(QUEST_INTO_THE_REALM_OF_SHADOW) == QUEST_STATUS_INCOMPLETE)
                            if (Creature* darkrider = ObjectAccessor::GetCreature(*me, m_darkriderGUID))
                            {
                                me->GetMotionMaster()->Initialize();
                                me->SetSpeed(MOVE_RUN, 3.0f, true);
                            }
        }

        void PassengerBoarded(Unit* who, int8 seatId, bool apply)
        {
            if (who->GetEntry() == NPC_DARK_RIDER_OF_ACHERUS)
            {
                m_darkriderGUID = who->GetGUID();
                if (apply)
                {
                    me->RestoreFaction();
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    me->setFaction(2096);
                }
                else
                {
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    me->AttackStop();
                    me->setFaction(35);
                }
            }
            else
                if (Player* player = who->ToPlayer())
                    if (apply == false)
                        me->DespawnOrUnsummon();
        }

        void UpdateAI(uint32 diff)
        {
            if (m_timer <= diff)
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
            Vehicle* vehicle = me->GetVehicleKit();
            if (!vehicle)
                return;
            if (vehicle->IsVehicleInUse())
                return;
            Creature* darkrider = me->FindNearestCreature(NPC_DARK_RIDER_OF_ACHERUS, 20);
            if (!darkrider)
                return;
            if (darkrider->IsMounted())
                return;
            if (darkrider->IsAlive() && !darkrider->IsInCombat() && vehicle->HasEmptySeat(0) && !darkrider->IsMounted())
            {
                darkrider->EnterVehicle(me, 0);
                return;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_acherus_deathcharger_28782AI(creature);
    }
};

// 28658    // correct way: 52312 52314 52555 ...
class npc_gothik_the_harvester_28658 : public CreatureScript
{
public:
    npc_gothik_the_harvester_28658() : CreatureScript("npc_gothik_the_harvester_28658") { }

    enum Creatures_SG
    {
        NPC_GHOULS = 28845,
        NPC_GHOSTS = 28846,
        SPELL_SCARLET_GHOUL_CREDIT = 52517,
        QUEST_THE_GIFT_THAT_KEEPS_ON_GIVING = 12698,
    };

    struct npc_gothik_the_harvester_28658AI : public ScriptedAI
    {
        npc_gothik_the_harvester_28658AI(Creature* creature) : ScriptedAI(creature) { }

        void MoveInLineOfSight(Unit* who) override
        {
            ScriptedAI::MoveInLineOfSight(who);

            if (Creature* creature = who->ToCreature())
                if (creature->GetEntry() == NPC_GHOULS && me->IsWithinDistInMap(who, 10.0f))
                    if (Unit* owner = who->GetOwner())
                        if (Player* player = owner->ToPlayer())
                            if (player->GetQuestStatus(QUEST_THE_GIFT_THAT_KEEPS_ON_GIVING) == QUEST_STATUS_INCOMPLETE)
                            {
                                player->KilledMonsterCredit(NPC_GHOULS);
                                creature->DespawnOrUnsummon();
                            }
                            //  @todo Creatures must not be removed, but, must instead
                            //  stand next to Gothik and be commanded into the pit
        }                   //  and dig into the ground.
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_gothik_the_harvester_28658AI(creature);
    }
};

// 28845 28846
class npc_scarlet_ghoul_28845 : public CreatureScript
{
public:
    npc_scarlet_ghoul_28845() : CreatureScript("npc_scarlet_ghoul_28845") { }

    enum Creatures_SG
    {
        NPC_GHOULS = 28845,
        NPC_GHOSTS = 28846,
    };

    struct npc_scarlet_ghoul_28845AI : public ScriptedAI
    {
        npc_scarlet_ghoul_28845AI(Creature* creature) : ScriptedAI(creature)
        {
            // Ghouls should display their Birth Animation
            // Crawling out of the ground
            //DoCast(me, 35177, true);
            //me->MonsterSay("Mommy?", LANG_UNIVERSAL, 0);
            me->SetReactState(REACT_DEFENSIVE);
        }

        void FindMinions(Unit* owner)
        {
            std::list<Creature*> MinionList;
            owner->GetAllMinionsByEntry(MinionList, NPC_GHOULS);

            if (!MinionList.empty())
            {
                for (std::list<Creature*>::const_iterator itr = MinionList.begin(); itr != MinionList.end(); ++itr)
                {
                    if ((*itr)->GetOwner()->GetGUID() == me->GetOwner()->GetGUID())
                    {
                        if ((*itr)->IsInCombat() && (*itr)->getAttackerForHelper())
                        {
                            AttackStart((*itr)->getAttackerForHelper());
                        }
                    }
                }
            }
        }

        void UpdateAI(uint32 /*diff*/) override
        {
            if (!me->IsInCombat())
            {
                if (Unit* owner = me->GetOwner())
                {
                    Player* plrOwner = owner->ToPlayer();
                    if (plrOwner && plrOwner->IsInCombat())
                    {
                        if (plrOwner->getAttackerForHelper() && plrOwner->getAttackerForHelper()->GetEntry() == NPC_GHOSTS)
                            AttackStart(plrOwner->getAttackerForHelper());
                        else
                            FindMinions(owner);
                    }
                }
            }

            if (!UpdateVictim() || !me->GetVictim())
                return;

            //ScriptedAI::UpdateAI(diff);
            //Check if we have a current target
            if (me->EnsureVictim()->GetEntry() == NPC_GHOSTS)
            {
                if (me->isAttackReady())
                {
                    //If we are within range melee the target
                    if (me->IsWithinMeleeRange(me->GetVictim()))
                    {
                        me->AttackerStateUpdate(me->GetVictim());
                        me->resetAttackTimer();
                    }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_scarlet_ghoul_28845AI(creature);
    }
};

// 28817
class npc_scarlet_miner_cart_28817 : public CreatureScript
{
public:
    npc_scarlet_miner_cart_28817() : CreatureScript("npc_scarlet_miner_cart_28817") { }

    enum ScarletMinerCart
    {
        SPELL_CART_CHECK = 54173,
        SPELL_SUMMON_CART = 52463,
        SPELL_SUMMON_MINER = 52464,

        NPC_MINER = 28841
    };

    struct npc_scarlet_miner_cart_28817AI : public PassiveAI
    {
        npc_scarlet_miner_cart_28817AI(Creature* creature) : PassiveAI(creature), _minerGUID(0), _playerGUID(0)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            me->SetDisplayId(me->GetCreatureTemplate()->Modelid1); // Modelid2 is a horse.
        }

        void JustSummoned(Creature* summon) override
        {
            if (summon->GetEntry() == NPC_MINER)
            {
                _minerGUID = summon->GetGUID();
                summon->AI()->SetGUID(_playerGUID);
            }
        }

        void SummonedCreatureDespawn(Creature* summon) override
        {
            if (summon->GetEntry() == NPC_MINER)
                _minerGUID = 0;
        }

        void DoAction(int32 /*param*/) override
        {
            if (Creature* miner = ObjectAccessor::GetCreature(*me, _minerGUID))
            {
                me->SetWalk(false);

                // Not 100% correct, but movement is smooth. Sometimes miner walks faster
                // than normal, this speed is fast enough to keep up at those times.
                me->SetSpeed(MOVE_RUN, 1.25f);

                me->GetMotionMaster()->MoveFollow(miner, 1.0f, 0);
            }
        }

        void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply) override
        {
            if (apply)
            {
                _playerGUID = who->GetGUID();
                me->CastSpell((Unit*)NULL, SPELL_SUMMON_MINER, true);
            }
            else
            {
                _playerGUID = 0;
                if (Creature* miner = ObjectAccessor::GetCreature(*me, _minerGUID))
                    miner->DespawnOrUnsummon();
            }
        }

    private:
        uint64 _minerGUID;
        uint64 _playerGUID;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_scarlet_miner_cart_28817AI(creature);
    }
};

// 28841
class npc_scarlet_miner_28841 : public CreatureScript
{
public:
    npc_scarlet_miner_28841() : CreatureScript("npc_scarlet_miner_28841") { }

    enum eMiner
    {
        SAY_SCARLET_MINER_0 = 0,
        SAY_SCARLET_MINER_1 = 1,
        SPELL_CART_DRAG = 52465,
    };

    struct npc_scarlet_miner_28841AI : public npc_escortAI
    {
        npc_scarlet_miner_28841AI(Creature* creature) : npc_escortAI(creature)
        {
            me->SetReactState(REACT_PASSIVE);
        }

        uint32 IntroTimer;
        uint32 IntroPhase;
        uint64 carGUID;

        void Reset() override
        {
            carGUID = 0;
            IntroTimer = 0;
            IntroPhase = 0;
        }

        void IsSummonedBy(Unit* summoner) override
        {
            carGUID = summoner->GetGUID();
        }

        void InitWaypoint()
        {
            AddWaypoint(1, 2389.03f, -5902.74f, 109.014f, 5000);
            AddWaypoint(2, 2341.812012f, -5900.484863f, 102.619743f);
            AddWaypoint(3, 2306.561279f, -5901.738281f, 91.792419f);
            AddWaypoint(4, 2300.098389f, -5912.618652f, 86.014885f);
            AddWaypoint(5, 2294.142090f, -5927.274414f, 75.316849f);
            AddWaypoint(6, 2286.984375f, -5944.955566f, 63.714966f);
            AddWaypoint(7, 2280.001709f, -5961.186035f, 54.228283f);
            AddWaypoint(8, 2259.389648f, -5974.197754f, 42.359348f);
            AddWaypoint(9, 2242.882812f, -5984.642578f, 32.827850f);
            AddWaypoint(10, 2217.265625f, -6028.959473f, 7.675705f);
            AddWaypoint(11, 2202.595947f, -6061.325684f, 5.882018f);
            AddWaypoint(12, 2188.974609f, -6080.866699f, 3.370027f);

            if (urand(0, 1))
            {
                AddWaypoint(13, 2176.483887f, -6110.407227f, 1.855181f);
                AddWaypoint(14, 2172.516602f, -6146.752441f, 1.074235f);
                AddWaypoint(15, 2138.918457f, -6158.920898f, 1.342926f);
                AddWaypoint(16, 2129.866699f, -6174.107910f, 4.380779f);
                AddWaypoint(17, 2117.709473f, -6193.830078f, 13.3542f, 10000);
            }
            else
            {
                AddWaypoint(13, 2184.190186f, -6166.447266f, 0.968877f);
                AddWaypoint(14, 2234.265625f, -6163.741211f, 0.916021f);
                AddWaypoint(15, 2268.071777f, -6158.750977f, 1.822252f);
                AddWaypoint(16, 2270.028320f, -6176.505859f, 6.340538f);
                AddWaypoint(17, 2271.739014f, -6195.401855f, 13.3542f, 10000);
            }
        }

        void SetGUID(uint64 guid, int32 /*id = 0*/) override
        {
            InitWaypoint();
            Start(false, false, guid);
            SetDespawnAtFar(false);
        }

        void WaypointReached(uint32 waypointId) override
        {
            switch (waypointId)
            {
            case 1:
                if (Unit* car = ObjectAccessor::GetCreature(*me, carGUID))
                    me->SetFacingToObject(car);
                Talk(SAY_SCARLET_MINER_0);
                SetRun(true);
                IntroTimer = 4000;
                IntroPhase = 1;
                break;
            case 17:
                if (Unit* car = ObjectAccessor::GetCreature(*me, carGUID))
                {
                    me->SetFacingToObject(car);
                    car->Relocate(car->GetPositionX(), car->GetPositionY(), me->GetPositionZ() + 1);
                    car->StopMoving();
                    car->RemoveAura(SPELL_CART_DRAG);
                }
                Talk(SAY_SCARLET_MINER_1);
                break;
            default:
                break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (IntroPhase)
            {
                if (IntroTimer <= diff)
                {
                    if (IntroPhase == 1)
                    {
                        if (Creature* car = Unit::GetCreature(*me, carGUID))
                            DoCast(car, SPELL_CART_DRAG);
                        IntroTimer = 800;
                        IntroPhase = 2;
                    }
                    else
                    {
                        if (Creature* car = Unit::GetCreature(*me, carGUID))
                            car->AI()->DoAction(0);
                        IntroPhase = 0;
                    }
                }
                else
                    IntroTimer -= diff;
            }
            npc_escortAI::UpdateAI(diff);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_scarlet_miner_28841AI(creature);
    }
};

// 28907  prince_valanar
class npc_prince_valanar_28907 : public CreatureScript
{
public:
    npc_prince_valanar_28907() : CreatureScript("npc_prince_valanar_28907") { }

    struct npc_prince_valanar_28907AI : public ScriptedAI
    {
        npc_prince_valanar_28907AI(Creature* creature) : ScriptedAI(creature) { }

        uint32 m_phase;
        uint32 m_timer;
        uint32 m_say;
        
        void Reset() override
        {
            m_phase = 0;
            m_timer = 1000;
            m_say = 0;
            me->SetWalk(true);
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_timer <= diff)
            {
                DoWork();
            }
            else
                m_timer -= diff;
        }

        void DoWork()
        {
            m_phase++;
            switch (m_phase)
            {
            case 1:
                me->GetMotionMaster()->MovePoint(1, 2321.48f, -5739.86f, 153.92f);
                m_timer = 2000;
                break;
            case 2:
                me->SetFacingTo(0.7f);
                Talk(m_say);
                m_timer = urand(5000, 8000);
                break;
            case 3:
                me->GetMotionMaster()->MovePoint(1, 2319.13f, -5736.79f, 153.92f);
                m_timer = 2000;
                break;
            case 4:
                me->SetFacingTo(0.7f);
                Talk(m_say);
                m_timer = urand(5000, 8000);
                break;
            case 5:
                me->GetMotionMaster()->MovePoint(1, 2316.30f, -5733.26f, 153.92f);
                m_timer = 2000;
                break;
            case 6:
                me->SetFacingTo(0.7f);
                Talk(m_say);
                m_timer = urand(5000, 8000);
                m_phase = 0;
                break;
            }

            m_say++;
            if (m_say > 14)
                m_say = 0;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_prince_valanar_28907AI(creature);
    }
};

//28610, 28939, 28940
class npc_crusade_persuaded_28610 : public CreatureScript
{
public:
    npc_crusade_persuaded_28610() : CreatureScript("npc_crusade_persuaded_28610") { }

    enum win_friends
    {
        SAY_PLAYER = 1,
        SAY_CRUSADER = 2,
        SAY_BREAK1 = 3,
        SAY_BREAK2 = 4,
        SAY_BREAK3 = 5,
        SAY_BREAK4 = 6,
        SAY_BREAK5 = 7,
        SAY_BREAK6 = 8,
        SAY_DEAD1 = 9,
        SPELL_PERSUASIVE_STRIKE = 52781,
        SPELL_THREAT_PULSE = 58111,
        QUEST_HOW_TO_WIN_FRIENDS = 12720,
    };

    struct npc_crusade_persuaded_28610AI : public ScriptedAI
    {
        npc_crusade_persuaded_28610AI(Creature* creature) : ScriptedAI(creature) { }

        uint32 speechTimer;
        uint32 speechCounter;
        uint64 playerGUID;

        void Reset() override
        {
            speechTimer = 0;
            speechCounter = 0;
            playerGUID = 0;
        }

        void DamageTaken(Unit* attacker, uint32& damage) 
        { 
            switch (speechCounter)
            {
            case 0:
                return;
                break;
            case 1:
                if (me->GetHealthPct() < 20)
                {
                    damage = 1;
                    speechCounter++;
                }
                break;
            default:
                damage /= 2;
                break;
            }
        }

        void SpellHit(Unit* caster, const SpellInfo* spell) override
        {
            if (spell->Id == SPELL_PERSUASIVE_STRIKE && caster->GetTypeId() == TYPEID_PLAYER && me->IsAlive() && !speechCounter)
            {
                if (Player* player = caster->ToPlayer())
                {
                    if (player->GetQuestStatus(QUEST_HOW_TO_WIN_FRIENDS) == QUEST_STATUS_INCOMPLETE)
                    {
                        playerGUID = player->GetGUID();
                        speechTimer = 500;
                        speechCounter = 1;
                    }
                }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (speechCounter)
            {
                if (speechTimer <= diff)
                {
                    Player* player = ObjectAccessor::GetPlayer(*me, playerGUID);
                    if (!player)
                    {
                        EnterEvadeMode();
                        return;
                    }

                    switch (speechCounter)
                    {
                    case 1:
                        sCreatureTextMgr->SendChat(me, SAY_PLAYER, NULL, CHAT_MSG_ADDON, LANG_ADDON, TEXT_RANGE_NORMAL, 0, TEAM_OTHER, false, player);
                        Talk(SAY_CRUSADER);
                        speechTimer = 8000;
                        break;
                    case 2:
                        Talk(SAY_BREAK1);
                        me->setFaction(player->getFaction());
                        me->CombatStop(true);
                        me->GetMotionMaster()->MoveIdle();
                        me->SetReactState(REACT_PASSIVE);
                        DoCastAOE(SPELL_THREAT_PULSE, true);
                        speechTimer = 8000;
                        break;
                    case 3:
                        Talk(SAY_BREAK2);
                        speechTimer = 8000;
                        break;
                    case 4:
                        Talk(SAY_BREAK3);
                        speechTimer = 8000;
                        break;
                    case 5:
                        Talk(SAY_BREAK4);
                        speechTimer = 8000;
                        break;
                    case 6:
                        sCreatureTextMgr->SendChat(me, SAY_BREAK5, NULL, CHAT_MSG_ADDON, LANG_ADDON, TEXT_RANGE_NORMAL, 0, TEAM_OTHER, false, player);
                        speechTimer = 8000;
                        break;
                    case 7:
                        Talk(SAY_BREAK6);
                        speechTimer = 8000;
                        break;
                    case 8:
                        Talk(SAY_DEAD1);
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->RestoreFaction();
                        player->Kill(me);
                        speechCounter = 0;
                        player->GroupEventHappens(QUEST_HOW_TO_WIN_FRIENDS, me);
                        return;
                    }

                    if (speechCounter > 1)
                        ++speechCounter;

                    DoCastAOE(SPELL_THREAT_PULSE, true);

                }
                else
                    speechTimer -= diff;

                return;
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_crusade_persuaded_28610AI(creature);
    }
};

//31084
class npc_highlord_darion_mograine_31084 : public CreatureScript
{
public:
    npc_highlord_darion_mograine_31084() : CreatureScript("npc_highlord_darion_mograine_31084") { }

    enum eMograine
    {
        QUEST_THE_BATTLE_FOR_THE_EBON_HOLD = 13166,
        SPELL_THE_MIGHT_OF_MOGRAINE = 53642,
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) 
    { 
        if (quest->GetQuestId() == QUEST_THE_BATTLE_FOR_THE_EBON_HOLD)
            creature->CastSpell(player, SPELL_THE_MIGHT_OF_MOGRAINE);

        return false; 
    }
 
    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        if (quest->GetQuestId() == QUEST_THE_BATTLE_FOR_THE_EBON_HOLD)
        {
            player->RemoveAura(SPELL_THE_MIGHT_OF_MOGRAINE);
            creature->RemoveAura(SPELL_THE_MIGHT_OF_MOGRAINE);
        }
            

        return false;
    }
};

void AddSC_the_scarlet_enclave()
{
    new npc_valkyr_battle_maiden();
    new npc_acherus_necromancer();
    new npc_instructor_razuvious();
    new npc_dk_initiate_28406();
    new npc_unworthy_initiate();
    new npc_unworthy_initiate_anchor();
    new go_acherus_soul_prison();
    new npc_eye_of_acherus();
    new npc_dark_rider_of_acherus();
    new npc_salanar_the_horseman_28653();
    new npc_salanar_the_horseman_28788();
    new npc_dark_rider_of_acherus_28768();
    new npc_acherus_deathcharger_28782();
    new npc_gothik_the_harvester_28658();
    new npc_scarlet_ghoul_28845();
    new npc_scarlet_miner_cart_28817();
    new npc_scarlet_miner_28841();
    new npc_prince_valanar_28907();
    new npc_crusade_persuaded_28610();
    new npc_highlord_darion_mograine_31084();
}
