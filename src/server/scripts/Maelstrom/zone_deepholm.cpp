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
#include "ScriptedEscortAI.h"
#include "SpellMgr.h"
#include "Player.h"
#include "Creature.h"

enum Zone_zone_deepholm
{
    NPC_DEPLETED_TOTEM = 45088,

    QUEST_ELEMENTAL_ENERGY = 27136,

    SPELL_ENERGY_CAPTURE = 84163,
    SPELL_DEPLETED_TOTEM_CREDIT = 84170,

};

// player
class player_zone_maelstrom : public PlayerScript
{
public:
    player_zone_maelstrom() : PlayerScript("player_zone_maelstrom") { }

    void OnQuestRemove(Player* player, uint32 questId) override
    {
        switch (questId)
        {
        case 0:
            break;
        }
    }

    void OnQuestStatusChange(Player* player, uint32 questId, QuestStatus status) override
    {
        switch (questId)
        {
        case 0:
            break;
        }
    }

};

// 43254
class npc_energized_geode_43254 : public CreatureScript
{
public:
    npc_energized_geode_43254() : CreatureScript("npc_energized_geode_43254") { }

    struct npc_energized_geode_43254AI : public ScriptedAI
    {
        npc_energized_geode_43254AI(Creature* creature) : ScriptedAI(creature) { }

        void JustDied(Unit* killer) override 
        { 
            if (Player* player = killer->ToPlayer())
                if (player->GetQuestStatus(QUEST_ELEMENTAL_ENERGY) == QUEST_STATUS_INCOMPLETE)
                    if (Creature* totem = player->FindNearestCreature(NPC_DEPLETED_TOTEM, 30.0f))
                        me->CastSpell(me, SPELL_ENERGY_CAPTURE, true);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_energized_geode_43254AI(creature);
    }
};

// 43258
class npc_lodestone_elemental_43258 : public CreatureScript
{
public:
    npc_lodestone_elemental_43258() : CreatureScript("npc_lodestone_elemental_43258") { }

    struct npc_lodestone_elemental_43258AI : public ScriptedAI
    {
        npc_lodestone_elemental_43258AI(Creature* creature) : ScriptedAI(creature) { }

        void JustDied(Unit* killer) override
        {
            if (Player* player = killer->ToPlayer())
                if (player->GetQuestStatus(QUEST_ELEMENTAL_ENERGY) == QUEST_STATUS_INCOMPLETE)
                    me->CastSpell(me, SPELL_ENERGY_CAPTURE, true);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_lodestone_elemental_43258AI(creature);
    }
};

// 45088
class npc_depleted_totem_45088 : public CreatureScript
{
public:
    npc_depleted_totem_45088() : CreatureScript("npc_depleted_totem_45088") { }

    struct npc_depleted_totem_45088AI : public ScriptedAI
    {
        npc_depleted_totem_45088AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;

        void Initialize()
        {
            m_playerGUID = 0;
        }

        void Reset() override
        {
            me->setFaction(35);
            me->SetReactState(REACT_PASSIVE);
        }

        void IsSummonedBy(Unit* summoner) override 
        { 
            if (Player* player = summoner->ToPlayer())
                m_playerGUID = player->GetGUID();
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override 
        { 
            if (spell->Id == SPELL_ENERGY_CAPTURE)
                if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                    me->CastSpell(me, SPELL_DEPLETED_TOTEM_CREDIT, true);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case 0:
                    break;
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_depleted_totem_45088AI(creature);
    }
};

class spell_energy_capture_84163 : public SpellScriptLoader
{
public:
    spell_energy_capture_84163() : SpellScriptLoader("spell_energy_capture_84163") { }

    class spell_energy_capture_84163_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_energy_capture_84163_SpellScript);

        void CheckTarget(WorldObject*& target)
        {
            if (Creature* npc = target->ToCreature())
                if (npc->GetEntry() == NPC_DEPLETED_TOTEM)
                    return;
            if (target)
                if (Creature* totem = target->FindNearestCreature(NPC_DEPLETED_TOTEM, 50.0f))
                    target = totem;
        }

        void Register()
        {
            OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_energy_capture_84163_SpellScript::CheckTarget, EFFECT_0, TARGET_UNIT_NEARBY_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_energy_capture_84163_SpellScript();
    }
};


void AddSC_zone_deepholm()
{
    new player_zone_maelstrom();
    new npc_energized_geode_43254();
    new npc_lodestone_elemental_43258();
    new npc_depleted_totem_45088();
    new spell_energy_capture_84163();
}

