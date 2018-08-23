/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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
 
#include "Pet.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"

 /*######
## npc_trainings_dummy
######*/

class npc_trainings_dummy : public CreatureScript
{
public:
    npc_trainings_dummy() : CreatureScript("npc_trainings_dummy") { }

    enum npc
    {
        EVENT_COOLDOWN = 101,
        EVENT_COMBAT_TIMER = 102,
    };

    struct npc_trainings_dummyAI : public ScriptedAI
    {
        npc_trainings_dummyAI(Creature *c) : ScriptedAI(c) { Initialize(); }

        EventMap m_events;
        bool	 m_spell_is_on_work;
        std::unordered_map<uint64, time_t> m_combatTime;

        void Initialize()
        {
            SetCombatMovement(false);
            m_events.Reset();
            m_combatTime.clear();
        }

        void Reset() override
        {
            m_spell_is_on_work = false;
            me->SetReactState(REACT_PASSIVE);
            SetCombatMovement(false);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            m_events.RescheduleEvent(EVENT_COMBAT_TIMER, 1000);
            damage = 0;
            me->SetHealth(me->GetMaxHealth());
            me->AddThreat(attacker, float(damage));
            m_combatTime[attacker->GetGUID()] = time(NULL);            
        }

        void SpellHit(Unit * Hitter, SpellInfo const* spell) override
        {
            m_events.RescheduleEvent(EVENT_COMBAT_TIMER, 1000);
            m_combatTime[Hitter->GetGUID()] = time(NULL);

            if (Player* player = Hitter->ToPlayer())
            {
                switch (player->getClass())
                {
                case CLASS_WARRIOR:
                {
                    if (spell->Id == 100) player->KilledMonsterCredit(44175);
                    break;
                }
                case CLASS_PALADIN:
                {
                    if (player->HasAura(105361) && spell->Id == 20271) // wowhead: this is the correct spell/aura	: Seal of Command	
                    {
                        player->KilledMonsterCredit(44420);
                        player->KilledMonsterCredit(44175);
                    }
                    if (player->HasAura(20154) && spell->Id == 20271)	// wowhead: this is a wrong lv 42 spell/aura, but used now in core.. : Seal of Righteousness				
                    {
                        player->KilledMonsterCredit(44420);
                        player->KilledMonsterCredit(44175);
                    }
                    break;
                }
                case CLASS_HUNTER:
                {
                    if (spell->Id == 56641) player->KilledMonsterCredit(44175);
                    break;
                }
                case CLASS_ROGUE:
                {
                    if (spell->Id == 2098) player->KilledMonsterCredit(44175);
                    break;
                }
                case CLASS_PRIEST:
                {
                    if (spell->Id == 589) player->KilledMonsterCredit(44175);
                    break;
                }
                case CLASS_DEATH_KNIGHT:
                {
                    break;
                }
                case CLASS_SHAMAN:
                {
                    if (spell->Id == 73899) player->KilledMonsterCredit(44175);
                    break;
                }
                case CLASS_MAGE:
                {
                    if (!m_spell_is_on_work)
                    {
                        if (Hitter->getRace() == RACE_TROLL)
                        {
                            if (spell->Id == 122) 
                                player->KilledMonsterCredit(44175);
                            if (spell->Id == 133) 
                                player->KilledMonsterCredit(44175);
                            if (spell->Id == 2136) 
                                player->KilledMonsterCredit(44175);
                        }
                        if (spell->Id == 7268 && !m_spell_is_on_work)
                        {
                            m_spell_is_on_work = true;
                            m_events.ScheduleEvent(EVENT_COOLDOWN, 7000);
                            player->KilledMonsterCredit(44175);
                        }
                    }
                    break;
                }
                case CLASS_WARLOCK:
                {
                    if (spell->Id == 172) player->KilledMonsterCredit(44175); // Corruption
                    if (spell->Id == 348) player->KilledMonsterCredit(44175); // Immolate
                    if (spell->Id == 2098) player->KilledMonsterCredit(44175); // Eviscerate
                    break;
                }
                case CLASS_DRUID:
                {
                    if (spell->Id == 8921) player->KilledMonsterCredit(44175);
                    break;
                }
                }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_COOLDOWN:
                {
                    m_spell_is_on_work = false;
                    break;
                }
                case EVENT_COMBAT_TIMER:
                {
                    time_t now = time(NULL);
                    for (std::unordered_map<uint64, time_t>::iterator itr = m_combatTime.begin(); itr != m_combatTime.end();)
                        if (itr->second < now - 5)
                        {
                            if (Unit* unit = ObjectAccessor::GetUnit(*me, itr->first))
                            {
                                unit->getHostileRefManager().deleteReference(me);
                                me->CombatStop(true);
                            }

                            itr = m_combatTime.erase(itr);
                        }
                        else
                            ++itr;

                    if (m_combatTime.size())
                        m_events.ScheduleEvent (EVENT_COMBAT_TIMER, 1000);
                    break;
                }
                }
            }
        }
    };

	CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_trainings_dummyAI (creature);
    }
};

 void AddSC_npc_trainings_dummy()
{
    new npc_trainings_dummy();
}

