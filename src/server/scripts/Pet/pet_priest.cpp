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

/*
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "npc_pet_pri_".
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "PassiveAI.h"
#include "PetAI.h"

enum PriestSpells
{
    SPELL_PRIEST_GLYPH_OF_SHADOWFIEND       = 58228,
    SPELL_PRIEST_GLYPH_OF_SHADOWFIEND_MANA  = 58227,
    SPELL_PRIEST_LIGHTWELL_CHARGES          = 59907
};

class npc_pet_pri_lightwell : public CreatureScript
{
    public:
        npc_pet_pri_lightwell() : CreatureScript("npc_pet_pri_lightwell") { }

        struct npc_pet_pri_lightwellAI : public PassiveAI
        {
            npc_pet_pri_lightwellAI(Creature* creature) : PassiveAI(creature)
            {
                DoCast(me, SPELL_PRIEST_LIGHTWELL_CHARGES, false);
            }

            void EnterEvadeMode() 
            {
                if (!me->IsAlive())
                    return;

                me->DeleteThreatList();
                me->CombatStop(true);
                me->ResetPlayerDamageReq();
            }
        };

        CreatureAI* GetAI(Creature* creature) const 
        {
            return new npc_pet_pri_lightwellAI(creature);
        }
};

/*######
# npc_shadowfiend
######*/

enum Shadowfiend
{
    MANA_LEECH                       = 28305,
    GLYPH_OF_SHADOWFIEND_MANA        = 58227,
    GLYPH_OF_SHADOWFIEND             = 58228
};

class npc_shadowfiend : public CreatureScript
{
public:
    npc_shadowfiend() : CreatureScript("npc_shadowfiend") { }

    struct npc_shadowfiendAI : public ScriptedAI
    {
        npc_shadowfiendAI(Creature* creature) : ScriptedAI(creature) {}

        void Reset() 
        {
            if (me->IsSummon())
                if (Unit* owner = me->ToTempSummon()->GetSummoner())
                    if (Unit* pet = owner->GetGuardianPet())
                        pet->CastSpell(pet, MANA_LEECH, true);
        }
 
        void DamageTaken(Unit* /*killer*/, uint32& damage) 
        {
            if (me->IsSummon())
                if (Unit* owner = me->ToTempSummon()->GetSummoner())
                    if (owner->HasAura(GLYPH_OF_SHADOWFIEND) && damage >= me->GetHealth())
                        owner->CastSpell(owner, GLYPH_OF_SHADOWFIEND_MANA, true);
        }

        void UpdateAI(const uint32 /*diff*/) 
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const 
    {
        return new npc_shadowfiendAI(creature);
    }
};

void AddSC_priest_pet_scripts()
{
    new npc_pet_pri_lightwell();
    new npc_shadowfiend();
}
