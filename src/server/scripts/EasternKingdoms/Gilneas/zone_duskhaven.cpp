/*
 *
* Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
 *
* Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 *
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
SDName: duskhaven
SD%Complete: 0
SDComment: Quest support: 0
SDCategory: Gilneas
EndScriptData */

/* ContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "Player.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

// Phase 1

// 36332
class npc_king_genn_greymane_36332 : public CreatureScript
{
public:
    npc_king_genn_greymane_36332() : CreatureScript("npc_king_genn_greymane_36332") { }

    enum e14375
    {
        QUEST_LAST_CHANCE_AT_HUMANITY = 14375,
        SPELL_PHASE_QUEST_ZONE_SPECIFIC_06 = 68481, 
        NPC_LORD_GODFREY_36330 = 36330,
        NPC_LORD_GODFREY_36170 = 36170,
        NPC_KRENNAN_ARANAS_36331 = 36331,
        NPC_KING_GENN_GREYMANE_36332 = 36332,
    };

    bool OnQuestReward(Player* player, Creature* creature, const Quest *_Quest, uint32) override
    {
        if (_Quest->GetQuestId() == QUEST_LAST_CHANCE_AT_HUMANITY)
        {
            player->CastSpell(player, SPELL_PHASE_QUEST_ZONE_SPECIFIC_06, true);
            player->SetUInt32Value(UNIT_FIELD_FLAGS_2, 2048);
            player->RemoveAura(42716);
            player->RemoveAura(50220);
            player->RemoveAura(58284);
            player->RemoveAura(68630);
            return true;
        }
        return false;
    }

    struct npc_king_genn_greymane_36332AI : public ScriptedAI
    {
        npc_king_genn_greymane_36332AI(Creature* creature) : ScriptedAI(creature) { }

        void UpdateAI(uint32 diff)
        {
           
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_king_genn_greymane_36332AI(creature);
    }
};

// 36331
class npc_krennan_aranas_36331 : public CreatureScript
{
public:
    npc_krennan_aranas_36331() : CreatureScript("npc_krennan_aranas_36331") { }

    enum eNpc
    {
        QUEST_LAST_CHANCE_AT_HUMANITY = 14375,
        NPC_KING_GREYMANE = 36332,
        NPC_LORD_GODFREY = 36330,
        SPELL_CATACLYSM_1 = 68953,
        SPELL_CATACLYSM_2 = 80134,
        SPELL_CATACLYSM_3 = 80133,
        SPELL_LAST_STAND_COMPLETE_2 = 72799,
        EVENT_CHECK_ARRIVEL_PLAYER = 101,
        EVENT_TALK_0,
        EVENT_TALK_1,
        EVENT_TALK_2,
        EVENT_TALK_3,
        EVENT_TALK_4,
        EVENT_RESTART,
    };

    struct npc_krennan_aranas_36331AI : public ScriptedAI
    {
        npc_krennan_aranas_36331AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap  m_events;
        bool      m_videoStarted;
        uint64    m_playerGUID;
        uint64    m_kingGUID;
        uint64    m_godfreyGUID;

        void Reset()
        {
            m_videoStarted = false;
            m_playerGUID = NULL;
            m_kingGUID = NULL;
            m_godfreyGUID = NULL;
            m_events.Reset();
            m_events.ScheduleEvent(EVENT_CHECK_ARRIVEL_PLAYER, 1000);
        }

        void UpdateAI(uint32 diff)
        {
            m_events.Update(diff);

            if (CheckPlayerIsInvalid())
            {
                Reset();
                return;
            }

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHECK_ARRIVEL_PLAYER:
                    {
                        if (!m_videoStarted)
                            if (Player* player = me->FindNearestPlayer(10.0f))
                                if (player->GetQuestStatus(QUEST_LAST_CHANCE_AT_HUMANITY) == QUEST_STATUS_NONE)
                                {
                                    player->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_DISABLE_TURN);
                                    m_playerGUID = player->GetGUID();
                                    m_videoStarted = true;
                                    if (!m_kingGUID)
                                        if (Creature* king = me->FindNearestCreature(NPC_KING_GREYMANE, 25.0f))
                                            m_kingGUID = king->GetGUID();
                                    if (!m_godfreyGUID)
                                        if (Creature* lord = me->FindNearestCreature(NPC_LORD_GODFREY, 25.0f))
                                            m_godfreyGUID = lord->GetGUID();

                                    m_events.ScheduleEvent(EVENT_TALK_0, 4000);
                                    return;
                                }
                        m_events.ScheduleEvent(EVENT_CHECK_ARRIVEL_PLAYER, 1000);
                        break;
                    }
                    case EVENT_TALK_0:
                    {
                        m_events.ScheduleEvent(EVENT_TALK_1, 14000);
                        Talk(0);
                        break;
                    }
                    case EVENT_TALK_1:
                    {
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                            player->CastSpell(player, SPELL_CATACLYSM_1);
                        if (Creature* lord = sObjectAccessor->GetCreature(*me, m_godfreyGUID))
                            lord->AI()->Talk(0);
                        m_events.ScheduleEvent(EVENT_TALK_2, 8000);
                        break;
                    }
                    case EVENT_TALK_2:
                    {
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                            player->CastSpell(player, SPELL_CATACLYSM_2);
                        if (Creature* king = sObjectAccessor->GetCreature(*me, m_kingGUID))
                            king->AI()->Talk(0);
                        m_events.ScheduleEvent(EVENT_TALK_3, 9000);
                        break;
                    }
                    case EVENT_TALK_3:
                    {
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                            player->CastSpell(player, SPELL_CATACLYSM_3);
                        if (Creature* king = sObjectAccessor->GetCreature(*me, m_kingGUID))
                            king->AI()->Talk(1);
                        m_events.ScheduleEvent(EVENT_TALK_4, 8000);
                        break;
                    }
                    case EVENT_TALK_4:
                    {
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                            player->CastSpell(player, SPELL_LAST_STAND_COMPLETE_2);

                        m_events.ScheduleEvent(EVENT_RESTART, 30000);
                        break;
                    }
                    case EVENT_RESTART:
                    {
                        Reset();
                        break;
                    }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        bool CheckPlayerIsInvalid()
        {
            if (!m_playerGUID)
                return false;

            if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                if (player->IsAlive() && player->IsInWorld())
                    if (player->GetDistance2d(me) < 10.0f)
                        return false;
            return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_krennan_aranas_36331AI(creature);
    }
};

// Phase 4096

void AddSC_zone_gilneas_duskhaven()
{	
    new npc_krennan_aranas_36331();
    new npc_king_genn_greymane_36332();


};
