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

// 42548
class npc_muddy_crawfish_42548 : public CreatureScript
{
public:
    npc_muddy_crawfish_42548() : CreatureScript("npc_muddy_crawfish_42548") { }

    struct npc_muddy_crawfish_42548AI : public ScriptedAI
    {
        npc_muddy_crawfish_42548AI(Creature* creature) : ScriptedAI(creature) { }

        void OnSpellClick(Unit* clicker, bool& /*result*/)  override
        { 
            if (Player* player = clicker->ToPlayer())
                if (player->GetQuestStatus(26226) == QUEST_STATUS_INCOMPLETE)
                    me->DespawnOrUnsummon(500);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_muddy_crawfish_42548AI(creature);
    }
};

// spell 94687
class spell_waters_of_farseeing_94687 : public SpellScriptLoader
{
public:
    spell_waters_of_farseeing_94687() : SpellScriptLoader("spell_waters_of_farseeing_94687") { }

    class spell_waters_of_farseeing_94687_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_waters_of_farseeing_94687_AuraScript);

        void OnApply(AuraEffect const* aurEff, AuraEffectHandleModes mode)
        {
            if (aurEff->GetMiscValue() == 807)
                if (Unit* caster = GetCaster())                
                    if (Player* player = caster->ToPlayer())
                        if (player->GetQuestStatus(28805) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(28826) == QUEST_STATUS_INCOMPLETE)
                            player->KilledMonsterCredit(50054);
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_waters_of_farseeing_94687_AuraScript::OnApply, EFFECT_0, SPELL_AURA_SCREEN_EFFECT, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_waters_of_farseeing_94687_AuraScript();
    }
};


void AddSC_orgrimmar()
{
    new npc_muddy_crawfish_42548();
    new spell_waters_of_farseeing_94687();

}
