/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
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
#include "blackrock_caverns.h"

enum Spells
{
    SPELL_QUECKSILVER_ARMOR = 75842,
    SPELL_SUPERHEATED_QUECKSILVER_ARMOR = 75846,

    SPELL_HEAT_WAVE = 63677,
    SPELL_BURNING_METAL = 76002,
    SPELL_CLEAVE = 845,
    SPELL_LAVA_SPOUT = 76007,

    SPELL_LAVA_POOL = 93628,
};

enum Events
{
    EVENT_CLEAVE = 1,
    EVENT_CHECK_ARMOR_STATE = 2,
    EVENT_LAVA_POOL = 3,
};

Position const summonPositions[3] =
{
    { 268.717f, 789.984f, 95.3499f, 4.86041f },
    { 226.707f, 754.725f, 95.3501f, 2.75163f },
    { 216.941f, 808.943f, 95.35f, 0.638911f },
};

// 39698
class boss_karsh_steelbender : public CreatureScript
{
public:
    boss_karsh_steelbender() : CreatureScript("boss_karsh_steelbender") { }

    struct boss_karsh_steelbenderAI : public BossAI
    {
        boss_karsh_steelbenderAI(Creature* creature) : BossAI(creature, DATA_KARSH_STEELBENDER_EVENT)
        {
            instance = creature->GetInstanceScript();

            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, NPC_LAVA_SPOUT_TRIGGER, 1000.0f);

            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE);
        }

        InstanceScript* instance;
        EventMap events;
        uint8 SpawnCount;

        void Reset() override
        {
            events.Reset();
            me->RemoveAllAuras();

            DespawnCreatures(NPC_BOUND_FLAMES);
        }

        void EnterCombat(Unit* /*who*/) override
        {
            DoCast(me, SPELL_QUECKSILVER_ARMOR);
            events.ScheduleEvent(EVENT_CLEAVE, urand(15000, 18000));
            events.ScheduleEvent(EVENT_CHECK_ARMOR_STATE, 1000);

            Talk(0);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if ((!me->HasAura(SPELL_QUECKSILVER_ARMOR)) && (!me->HasAura(SPELL_SUPERHEATED_QUECKSILVER_ARMOR)))
            {        // Summon Adds
                LavaSpoutErrupt();

                Talk(1);

                DoCast(me, SPELL_QUECKSILVER_ARMOR);

                if (!me->GetMap()->IsHeroic())
                    return;

                // Heroic: Summon Adds

                uint8 r = urand(0, 2);

                for (uint8 i = 0; i <= 2; i++)
                    me->SummonCreature(NPC_BOUND_FLAMES, summonPositions[r], TEMPSUMMON_CORPSE_DESPAWN);

                SpawnCount = 3;

                return;
            }

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CLEAVE:
                    DoCastVictim(SPELL_CLEAVE);
                    events.ScheduleEvent(EVENT_CLEAVE, urand(15000, 18000));
                    break;

                case EVENT_CHECK_ARMOR_STATE:
                    // Checks weather the Boss is in heat range

                    if (me->GetDistance(237.166f, 785.067f, 95.67f /*Stream of Molten*/) < 4.5f)
                    {
                        me->RemoveAura(SPELL_QUECKSILVER_ARMOR);

                        // We cant do that with CastSpell because with the Spell the Normal Armor is applied too
                        me->SetAuraStack(SPELL_SUPERHEATED_QUECKSILVER_ARMOR, me, me->GetAuraCount(SPELL_SUPERHEATED_QUECKSILVER_ARMOR) + 1);
                        me->GetAura(SPELL_SUPERHEATED_QUECKSILVER_ARMOR)->RefreshDuration();

                        DoCastAOE(SPELL_HEAT_WAVE);
                    }

                    events.ScheduleEvent(EVENT_CHECK_ARMOR_STATE, 1000);
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void SummonedCreatureDespawn(Creature* summon) override
        {
            if (summon->GetEntry() == NPC_BOUND_FLAMES)
            {
                SpawnCount--;

                if (SpawnCount == 0)
                    DoCastAOE(SPELL_LAVA_POOL, true);
            }
        }

        void JustDied(Unit* /*killer*/) override
        {
            DespawnCreatures(NPC_BOUND_FLAMES);
            Talk(2);
        }

    private:
        void DespawnCreatures(uint32 entry)
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, entry, 1000.0f);

            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->DespawnOrUnsummon();
        }

        void LavaSpoutErrupt()
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, NPC_LAVA_SPOUT_TRIGGER, 1000.0f);

            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->CastSpell((*iter), SPELL_LAVA_SPOUT, true);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_karsh_steelbenderAI(creature);
    }
};

void AddSC_boss_karsh_steelbender()
{
    new boss_karsh_steelbender();
}