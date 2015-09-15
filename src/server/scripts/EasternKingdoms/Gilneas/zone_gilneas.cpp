/*
* Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
* Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>

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
SDName: Gilneas
SD%Complete: 0
SDComment: Quest support: 0
SDCategory: Gilneas
EndScriptData */

/* ContentData */

#include "Creature.h"
#include "CreatureAI.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "ScriptedFollowerAI.h"
#include "Player.h"



// 34864
class npc_gilneas_city_guard_gate_34864 : public CreatureScript
{
public:
    npc_gilneas_city_guard_gate_34864() : CreatureScript("npc_gilneas_city_guard_gate_34864") { }

    struct npc_gilneas_city_guard_gate_34864AI : public ScriptedAI
    {
        npc_gilneas_city_guard_gate_34864AI(Creature* creature) : ScriptedAI(creature)  { }

        enum e34864
        {
            NPC_PANICKED_CITIZEN_GATE = 44086,
        };

        uint32		_timer;
        uint8		_phase;
        bool		_nearGate;
        uint8		_say;
        uint8		_emote;
        Creature*	_citizen;

        void Reset() override
        {
            _timer = urand(10000, 30000);
            _phase = 0;
            _nearGate = false;

            if (me->GetDistance2d(-1430.47f, 1345.55f) < 10.0f)
                _nearGate = true;
        }

        void UpdateAI(uint32 diff) override
        {
            if (_nearGate)
                if (_timer <= diff)
                {
                    DoWork();
                }
                else
                    _timer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

        void DoWork()
        {
            switch (_phase)
            {
            case 0:
            {
                std::list<Creature*> listOfCitizen;
                me->GetCreatureListWithEntryInGrid(listOfCitizen, NPC_PANICKED_CITIZEN_GATE, 35.0f);

                if (!listOfCitizen.empty())
                {
                    uint8 id = urand(0, listOfCitizen.size() - 1);
                    std::list<Creature*>::iterator itr = listOfCitizen.begin();
                    std::advance(itr, id);

                    if (_citizen = *itr)
                    {
                        _timer = urand(1000, 2000);
                        _emote = urand(0, 4);
                        _say = urand(0, 2);
                        _citizen->HandleEmoteCommand(RAND(EMOTE_STATE_COWER, EMOTE_STATE_TALK, EMOTE_ONESHOT_CRY, EMOTE_STATE_SPELL_PRECAST, EMOTE_STATE_EXCLAIM));
                        _phase = 1;
                        return;
                    }
                }
                break;
            }
            case 1:
            {
                if (_citizen)
                {
                    _citizen->AI()->Talk(_say);
                    _timer = urand(4000, 7000);
                    _phase = 2;
                }
                break;
            }
            case 2:
            {
                if (_citizen)
                {
                    Talk(_say);
                    _timer = 6000;
                    _phase = 3;
                }
                break;
            }
            case 3:
            {
                if (_citizen)
                {
                    _citizen->HandleEmoteCommand(EMOTE_ONESHOT_NONE);
                    _timer = urand(10000, 20000);
                    _phase = 0;
                }
                break;
            }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gilneas_city_guard_gate_34864AI(creature);
    }
};

// 34850
class npc_prince_liam_greymane_34850 : public CreatureScript
{
public:
    npc_prince_liam_greymane_34850() : CreatureScript("npc_prince_liam_greymane_34850") { }

    enum e34850
    {
        QUEST_LOCKDOWN = 14078,
        NPC_PANICKED_CITIZEN = 34851,
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_LOCKDOWN)
            if (Creature* citizen = creature->FindNearestCreature(NPC_PANICKED_CITIZEN, 20.0f))
                citizen->AI()->Talk(0);

        return true;
    }

    struct npc_prince_liam_greymane_34850AI : public ScriptedAI
    {
        npc_prince_liam_greymane_34850AI(Creature *c) : ScriptedAI(c) {}

        uint32 m_timer;
        uint32 m_phase;

        void Reset() override
        {
            m_timer = 1000;
            m_phase = 4;
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_timer <= diff)
            {
                switch (m_phase)
                {
                case 1:
                    Talk(0);
                    m_timer = 15000;
                    m_phase = 2;
                    break;
                case 2:
                    Talk(1);
                    m_timer = 18000;
                    m_phase = 3;
                    break;
                case 3:
                    Talk(2);
                    m_timer = 25000;
                    m_phase = 4;
                    break;
                case 4:
                    m_timer = 45000;
                    m_phase = 1;
                    break;
                }
            }
            else
                m_timer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_prince_liam_greymane_34850AI(creature);
    }
};

// 34863
class npc_lieutenant_walden_34863 : public CreatureScript
{
public:
    npc_lieutenant_walden_34863() : CreatureScript("npc_lieutenant_walden_34863") { }

    enum e34863
    {
        QUEST_LOCKDOWN = 14078,
        SPELL_GENERIC_QUEST_INVISIBILITY_DERECTION_1 = 49416,
    };

    bool OnQuestComplete(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_LOCKDOWN)
        {
            player->AddAura(SPELL_GENERIC_QUEST_INVISIBILITY_DERECTION_1, player);
            player->SaveToDB();
        }

        return true;
    }
};


void AddSC_zone_gilneas_city()
{
    new npc_gilneas_city_guard_gate_34864();
    new npc_prince_liam_greymane_34850();
    new npc_lieutenant_walden_34863();

};

