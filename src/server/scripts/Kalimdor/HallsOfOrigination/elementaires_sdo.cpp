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

#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

/**************
**Gardien D'air
***************/

#define spell_cisaille_de_vent 91164 // Cisaille_de_Vent

class npc_gardien_dair: public CreatureScript
{
public:
       npc_gardien_dair() : CreatureScript("npc_gardien_dair") { }
 
       struct npc_gardien_dairAI : public ScriptedAI
       {
            npc_gardien_dairAI(Creature * creature) : ScriptedAI(creature) { }
            
            uint32 cisaille_de_vent;
            
            void Reset()
            {
             cisaille_de_vent = 10000;
            }
            
            void UpdateAI(uint32 diff)
            {
            if (!UpdateVictim())
            return;
             
            if (cisaille_de_vent<= diff)
            {
            if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 10.0f, true))
            DoCast(pTarget, spell_cisaille_de_vent);
            cisaille_de_vent = 10000;
            } else cisaille_de_vent -= diff;
            
            DoMeleeAttackIfReady();
         }
       };
       
    CreatureAI* GetAI(Creature* creature) const
    {
         return new npc_gardien_dairAI(creature);
    }
 
};

/*******************
**Gardien de Flammes
********************/

#define spell_eruption_de_lave 91161 // Eruption_de_Lave
#define spell_inferno_dechaine 91160 // Inferno_Déchaîné

class npc_gardien_de_flammes: public CreatureScript
{
public:
       npc_gardien_de_flammes() : CreatureScript("npc_gardien_de_flammes") { }
       
       struct npc_gardien_de_flammesAI : public ScriptedAI
       {
              npc_gardien_de_flammesAI(Creature * creature) : ScriptedAI(creature) { }
              
              uint32 eruption_de_lave;
              uint32 inferno_dechaine;
              
              void Reset()
              {
              eruption_de_lave = 10000;
              inferno_dechaine = 25000;
              }
              
              void UpdateAI(uint32 diff)
              {
              if (!UpdateVictim())
              return;
              
              if (eruption_de_lave<= diff)
              {
              DoCast(SelectTarget(SELECT_TARGET_RANDOM,1,100,true), spell_eruption_de_lave);
              eruption_de_lave = 10000;
              } else eruption_de_lave -= diff;
              
              DoMeleeAttackIfReady();
              }
       };
        
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gardien_de_flammesAI(creature);
    }      

};

/*****************
**Gardien de Terre
******************/

#define spell_empaler 91163 // Empaler
#define spell_vague_de_roche 77234// Vague_de_Roche

class npc_gardien_de_terre: public CreatureScript
{
public:
    npc_gardien_de_terre() : CreatureScript("npc_gardien_de_terre") { }

        struct npc_gardien_de_terreAI : public ScriptedAI
        {    
         npc_gardien_de_terreAI(Creature * creature) : ScriptedAI(creature) { }

            uint32 empaler;
            uint32 vague_de_roche;

            void Reset()
            {
                empaler = 12000;
                vague_de_roche = 20000;
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                return;

                if (empaler<= diff)
                {
                    DoCastVictim(spell_empaler);
                    empaler = 12000;
                } else empaler -= diff;

                if (vague_de_roche<= diff)
                {
                    DoCast(me, spell_vague_de_roche);
                    vague_de_roche = 20000;
                } else vague_de_roche -= diff;
              
                DoMeleeAttackIfReady();

            }
        };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gardien_de_terreAI(creature);
    }

};

void AddSC_elementaires_sdo()
{
    new npc_gardien_dair();
    new npc_gardien_de_flammes();
    new npc_gardien_de_terre();
}