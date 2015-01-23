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

/* Script Data Start
SDName: Redridge Mountains
SD%Complete: 0
SDComment:
Script Data End */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "Player.h"

enum eAnimRedridgeCity
{
    NPC_DUMPY = 43249,
    NPC_BIG_EARL = 43248,
    NPC_JOHN_J_KEESHAN_43184 = 43184,
    SPELL_DRINK_ALCOHOL = 58952,
    SPELL_APPLY_QUEST_INVIS_1 = 80895,
    SPELL_APPLY_QUEST_INVIS_2 = 80699,
    SPELL_APPLY_QUEST_INVIS_3 = 80815,
    SPELL_APPLY_QUEST_INVIS_4 = 80816,
    SPELL_APPLY_QUEST_INVIS_5 = 81003,
    QUEST_JOHN_J_KEESHAN = 26567,

};

class npc_marshal_marris : public CreatureScript
{
public:
    npc_marshal_marris() : CreatureScript("npc_marshal_marris") { }

    struct npc_marshal_marrisAI : public ScriptedAI
    {
        npc_marshal_marrisAI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;

        void Reset() override
        {
            m_timer = urand(6000, 10000); 
            m_phase = 0;
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_timer <= diff)
            {
                m_timer = urand(6000, 10000);
                me->CastSpell(me, SPELL_DRINK_ALCOHOL);
            }
            else
                m_timer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_marshal_marrisAI(creature);
    }
};

class npc_dumpy_43249 : public CreatureScript
{
public:
    npc_dumpy_43249() : CreatureScript("npc_dumpy_43249") { }

    struct npc_dumpy_43249AI : public ScriptedAI
    {
        npc_dumpy_43249AI(Creature *c) : ScriptedAI(c) { }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (attacker->GetEntry() == NPC_BIG_EARL)
                damage = 0;
        }
      
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_dumpy_43249AI(creature);
    }
};

class npc_big_earl_43248 : public CreatureScript
{
public:
    npc_big_earl_43248() : CreatureScript("npc_big_earl_43248") { }

    struct npc_big_earl_43248AI : public ScriptedAI
    {
        npc_big_earl_43248AI(Creature *c) : ScriptedAI(c) { }

        uint32 m_timer;
        uint32 m_phase;
        Creature* m_dumpy;
        Creature* m_keeshan;
        int32 m_questCooldown;

        void Reset() override
        {
            m_timer = 1000;
            m_phase = 0;
            m_dumpy = NULL;
            m_keeshan = NULL;
            m_questCooldown = 0;
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (attacker->GetEntry() == NPC_DUMPY)
                damage = 0;
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_questCooldown>0)
                m_questCooldown -= diff;

            if (m_timer <= diff)
            {
                m_timer = 1000;
                DoWork();
            }
            else
                m_timer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }


        void DoWork()
        {
            Player* player = me->FindNearestPlayer(20.0f);
            m_dumpy = me->FindNearestCreature(NPC_DUMPY, 5.0f);
            m_keeshan = me->FindNearestCreature(NPC_JOHN_J_KEESHAN_43184, 5.0f);
            switch (m_phase)
            {
            case 0: 
                if (player && player->m_positionZ < 65.0f)
                    if (player->GetQuestStatus(QUEST_JOHN_J_KEESHAN) == QUEST_STATUS_INCOMPLETE)
                    {
                        if (m_dumpy)
                            m_dumpy->DespawnOrUnsummon();

                        if (!m_keeshan)
                            m_keeshan = me->SummonCreature(NPC_JOHN_J_KEESHAN_43184, -9203.84f, -2155.79f, 57.187f, 3.565f, TEMPSUMMON_TIMED_DESPAWN, 600000);

                        if (!m_keeshan->IsInCombat())
                        {
                            m_keeshan->Attack(me, true);
                            me->Attack(m_keeshan, true);
                        }
                        m_phase = 2; m_timer = 100;
                    }
                    else
                    {
                        if (m_keeshan)
                            m_keeshan->DespawnOrUnsummon();

                        if (!m_dumpy)
                            m_dumpy = me->SummonCreature(NPC_DUMPY, -2101.98f, -2154.78f, 57.19f, 1.659f);

                        if (m_dumpy && !m_dumpy->IsInCombat())
                        {
                            m_dumpy->Attack(me, true);
                            me->Attack(m_dumpy, true);
                        }
                    }
                break;
            case 1: 
                break;
            case 2: // fighting against john until player is gone
                if (!player)
                {
                    m_phase = 3; m_timer = 100;
                }
                else if (player->m_positionZ > 65.0f)
                {
                    m_phase = 3; m_timer = 100;
                }
                break;
            case 3:
                if (m_keeshan)
                    m_keeshan->DespawnOrUnsummon();

                if (!m_dumpy)
                    m_dumpy = me->SummonCreature(NPC_DUMPY, -2101.98f, -2154.78f, 57.19f, 1.659f);

                if (m_dumpy && !m_dumpy->IsInCombat())
                {
                    m_dumpy->Attack(me, true);
                    me->Attack(m_dumpy, true);
                }

                m_phase = 0;
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_big_earl_43248AI(creature);
    }
};



void AddSC_redridge_mountains()
{
    new npc_marshal_marris();
    new npc_dumpy_43249();
    new npc_big_earl_43248();
}

