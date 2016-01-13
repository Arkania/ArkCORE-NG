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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "uldaman.h"

// 2748
class boss_archaedas : public CreatureScript
{
public:
    boss_archaedas() : CreatureScript("boss_archaedas") { }

    enum eSay
    {
        SAY_AGGRO = 0,
        SAY_SUMMON_GUARDIANS = 1,
        SAY_SUMMON_VAULT_WARDER = 2,
        SAY_KILL = 3,
    };

    struct boss_archaedasAI : public BossAI
    {
        boss_archaedasAI(Creature* creature) : BossAI(creature, ENC_ARCHAEDAS) { m_instance = creature->GetInstanceScript(); }

        InstanceScript* m_instance;
        EventMap m_events;
        uint32 m_phase;
        bool   m_flag66, m_flag33;

        void Reset() override
        {
            m_instance->SetData(ENC_ARCHAEDAS, NOT_STARTED);
            m_events.Reset();
            m_phase = 0;
            m_flag66 = false;
            m_flag33 = false;
            me->setFaction(35);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            me->RemoveAllAuras();
            me->AddAura(SPELL_STONED, me);
        }

        void EnterCombat(Unit* /*who*/) override
        {
            m_instance->SetData(ENC_ARCHAEDAS, IN_PROGRESS);
        }

        void JustDied(Unit* /*Killer*/) override
        {
            m_instance->SetData(ENC_ARCHAEDAS, DONE);
        }

        void KilledUnit(Unit* /*victim*/) override
        {
            Talk(SAY_KILL);
        }

        void DamageTaken(Unit* /*attacker*/, uint32& /*damage*/) 
        { 
            if (!m_flag66 && !HealthAbovePct(66)) //  When Archaedas reaches 66% health remaining, he awakens the 6 Earthen Guardians. 
            {
                m_flag66 = true;
                Talk(SAY_SUMMON_GUARDIANS);
                std::list<Creature*> guardians = FindEarthenGuardian();
                for (std::list<Creature*>::const_iterator itr = guardians.begin(); itr != guardians.end(); ++itr)
                    (*itr)->GetAI()->DoAction(ACTION_AWAKE);
            }
            else if (!m_flag33 && !HealthAbovePct(33)) // When Archaedas reaches 33% health remaining, he awakens the 2 Vault Warders. 
            {
                m_flag33 = true;
                Talk(SAY_SUMMON_VAULT_WARDER);
                std::list<Creature*> warders = FindVaultWarder();
                for (std::list<Creature*>::const_iterator itr = warders.begin(); itr != warders.end(); ++itr)
                    (*itr)->GetAI()->DoAction(ACTION_AWAKE);
            }
        }

        void DoAction(int32 action) override
        {
            switch (action)
            {
                case 1:
                {
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->setFaction(415);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    me->SetSpeed(MOVE_WALK, 1.0f, true);
                    me->SetSpeed(MOVE_RUN, 1.2f, true);
                    me->SetWalk(true);
                    if (Player* player = me->FindNearestPlayer(50.0f, true))
                    {
                        me->GetMotionMaster()->MoveChase(player);
                        me->Attack(player, true);
                    }
                    Talk(SAY_AGGRO);
                    m_events.ScheduleEvent(EVENT_AWAKE_HELP, 10000);
                    break;
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
                    case EVENT_AWAKE_HELP: // Archaedas awakens an Earthen Custodian every 10 seconds to assist him in battle. 
                    {
                        if (Creature* stone = FindEarthenCustodian())
                            stone->GetAI()->DoAction(ACTION_AWAKE);

                        m_events.ScheduleEvent(EVENT_AWAKE_HELP, 10000);
                        break;
                    }
                }
            }


            if (!UpdateVictim())
                return;
            DoMeleeAttackIfReady();
        }

        Creature* FindEarthenCustodian()
        {
            std::list<Creature*> stone = me->FindNearestCreatures(NPC_EARTHEN_CUSTODIAN, 50.0f);
            for (std::list<Creature*>::const_iterator itr = stone.begin(); itr != stone.end(); ++itr)
                if ((*itr)->IsAlive() && (*itr)->HasAura(SPELL_STONED))
                    return *itr;

            return nullptr;
        }

        std::list<Creature*> FindEarthenGuardian()
        {
            std::list<Creature*> returnValue;
            std::list<Creature*> stone = me->FindNearestCreatures(NPC_EARTHEN_GUARDIAN, 50.0f);
            for (std::list<Creature*>::const_iterator itr = stone.begin(); itr != stone.end(); ++itr)
                if ((*itr)->IsAlive() && (*itr)->HasAura(SPELL_STONED))
                    returnValue.push_back(*itr);

            return returnValue;
        }

        std::list<Creature*> FindVaultWarder()
        {
            std::list<Creature*> returnValue;
            std::list<Creature*> stone = me->FindNearestCreatures(NPC_VAULT_WARDER, 50.0f);
            for (std::list<Creature*>::const_iterator itr = stone.begin(); itr != stone.end(); ++itr)
                if ((*itr)->IsAlive() && (*itr)->HasAura(SPELL_STONED))
                    returnValue.push_back(*itr);

            return returnValue;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetUldamanAI<boss_archaedasAI>(creature);
    }
};

void AddSC_boss_archaedas()
{
    new boss_archaedas();
}
