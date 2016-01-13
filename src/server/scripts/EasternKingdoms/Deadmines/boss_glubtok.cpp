/*
* Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
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

#include "ScriptPCH.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "deadmines.h"

enum Spells
{
    SPELL_FIRE_BLOSSOM = 88129, // Fireball explodes on the ground
    SPELL_FROST_BLOSSOM = 88169, // Iceball explodes on the ground
    SPELL_ARCANE_POWER = 88009, // Spell Phase 2
    SPELL_FIST_OF_FLAME = 87859, // elemental_fists
    SPELL_FIST_OF_FROST = 87861, // elemental_fists
    SPELL_BLINK = 87925  // correct Blink spell
};


#define SAY_AGGRO            0
#define SAY_ARCANE_POWER     1
#define SAY_FLAME            2
#define SAY_TOO_MUCH_POWER   3
#define SAY_KILL             4  
#define SAY_FISTS_OF_FLAME   5
#define SAY_FISTS_OF_FROST   6
#define SAY_READY            7
#define SAY_LETS_DO_IT       8

#define spell_elemental_fists RAND(87859, 91273)

const Position pos[1] =
{
    { -192.328003f, -450.244995f, 54.521500f, 0.00f }
};

enum Phases
{
    PHASE_NORMAL = 1,
    PHASE_50_PERCENT = 2,
};


// 47162 boss_glubtok       his abilities need rechecked http://www.wowhead.com/npc=47162#abilities
class boss_glubtok : public CreatureScript
{
public:
    boss_glubtok() : CreatureScript("boss_glubtok") { }

    struct boss_glubtokAI : public BossAI
    {
        boss_glubtokAI(Creature* creature) : BossAI(creature, BOSS_GLUBTOK) 
        { 
            m_instance = creature->GetInstanceScript(); 
        }

        InstanceScript* m_instance;
        EventMap m_events;

        uint8 Phase;
        uint32 phase;
        uint32 SpellTimer;

        uint32 elemental_fists;
        uint32 ArcanePowerTimer;
        uint32 blinkTimer;
        uint32 PhaseChangeTimer;
        uint32 NormalCastTimer;
        uint8 BlossomSpell;

        bool Phased;

        void Reset()
        {
            m_events.Reset();
            m_events.ScheduleEvent(1, 10000);

            Phased = false;
            Phase = PHASE_NORMAL;

            phase = 1;
            SpellTimer = urand(10 * IN_MILLISECONDS, 25 * IN_MILLISECONDS);

            elemental_fists = 20000;
            blinkTimer = 12000;

            NormalCastTimer = 3000;
            instance->SetData(BOSS_GLUBTOK, NOT_STARTED);
        }

        void EnterCombat(Unit* /*who*/)
        {
            instance->SetData(BOSS_GLUBTOK, IN_PROGRESS);
            Talk(SAY_AGGRO);
        }

        void DamageTaken(Unit* /*attacker*/, uint32& damage)
        {
        }

        void JustDied(Unit* Killer)
        {
            if (GameObject* door = ObjectAccessor::GetGameObject(*me, m_instance->GetData64(DATA_FACTORY_DOOR)))
                door->ResetDoorOrButton();

            if (Player* player = Killer->ToPlayer())
                player->KilledMonsterCredit(47162);

            instance->SetData(BOSS_GLUBTOK, DONE);
            Talk(SAY_TOO_MUCH_POWER);
        }

        void KilledUnit(Unit* Victim)
        {
            Talk(SAY_KILL);
        }

        void UpdateAI(uint32 diff)
        {
            m_events.Update(diff);
            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case 1:
                {
                    // if (GameObject* door = ObjectAccessor::GetGameObject(*me, m_instance->GetData64(DATA_FACTORY_DOOR)))
                    // door->UseDoorOrButton();

                    

                    m_events.ScheduleEvent(1, 10000);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;

            if (phase == 1)
            {
                if (SpellTimer <= diff)
                {
                    switch (urand(0, 1))
                    {
                    case 0:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                            DoCast(me, SPELL_FIST_OF_FLAME);
                        Talk(SAY_FISTS_OF_FLAME);
                        break;

                    case 1:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                            DoCast(me, SPELL_FIST_OF_FROST);
                        Talk(SAY_FISTS_OF_FROST);
                        break;
                    }

                    SpellTimer = urand(10 * IN_MILLISECONDS, 25 * IN_MILLISECONDS);
                }
                else SpellTimer -= diff;

                if (HealthBelowPct(50))
                {
                    phase = 2;
                    DoCast(me, SPELL_ARCANE_POWER);
                    Talk(SAY_ARCANE_POWER);
                }

                DoMeleeAttackIfReady();
            }
            else
            {
                if (SpellTimer <= diff)
                {
                    DoCast(me, urand(1, 2) == 1 ? SPELL_FROST_BLOSSOM : SPELL_FIRE_BLOSSOM);
                    SpellTimer = urand(10 * IN_MILLISECONDS, 25 * IN_MILLISECONDS);
                }
                else SpellTimer -= diff;
            }

            if (PhaseChangeTimer <= diff && Phase == PHASE_NORMAL)
            {
                if (PhaseChangeTimer <= diff)
                {
                    me->SetReactState(REACT_AGGRESSIVE);
                    elemental_fists = 20000;
                    blinkTimer = 12000;
                    Phase = PHASE_NORMAL;
                }
                else PhaseChangeTimer -= diff;

                if (elemental_fists <= diff && Phase == PHASE_NORMAL)
                {
                    if (elemental_fists <= diff)
                    {
                        DoCast(me, elemental_fists);
                        me->MonsterYell(SAY_FLAME, LANG_UNIVERSAL, NULL);
                        elemental_fists = 20000;
                    }
                    else elemental_fists -= diff;
                }

                if (blinkTimer <= diff && Phase == PHASE_NORMAL)
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 10.0f, true))
                        DoCast(me, SPELL_BLINK);
                    blinkTimer = 12000;
                }
                else blinkTimer -= diff;

                DoMeleeAttackIfReady();
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDeadminesAI<boss_glubtokAI>(creature);
    }
};

void AddSC_boss_glubtok()
{
    new boss_glubtok();
}




