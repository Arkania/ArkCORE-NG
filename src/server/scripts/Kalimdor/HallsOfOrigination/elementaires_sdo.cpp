/*
* Copyright (C) 2012-2013 HTCore <http://cata.vfire-core.com/>
* Copyright (C) 2012-2013 WoW Source <http://wow.amgi-it.ro/>
* by Shee Shen
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
       npc_gardien_dair() : CreatureScript("npc_gardien_dair") {}
 
       struct npc_gardien_dairAI : public ScriptedAI
       {
            npc_gardien_dairAI(Creature * pCreature) : ScriptedAI(pCreature) {}
			
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
	   
	CreatureAI* GetAI(Creature* pCreature) const
    {
         return new npc_gardien_dairAI(pCreature);
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
       npc_gardien_de_flammes() : CreatureScript("npc_gardien_de_flammes") {}
	   
	   struct npc_gardien_de_flammesAI : public ScriptedAI
	   {
	          npc_gardien_de_flammesAI(Creature * pCreature) : ScriptedAI(pCreature) {}
			  
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
		
	CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_gardien_de_flammesAI(pCreature);
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
    npc_gardien_de_terre() : CreatureScript("npc_gardien_de_terre") {}

		struct npc_gardien_de_terreAI : public ScriptedAI
	    {    
         npc_gardien_de_terreAI(Creature * pCreature) : ScriptedAI(pCreature) {}

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
					DoCast(me->GetVictim(), spell_empaler);
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

	CreatureAI* GetAI(Creature* pCreature) const
    {
		return new npc_gardien_de_terreAI(pCreature);
    }

};

void AddSC_elementaires_sdo()
{
	new npc_gardien_dair();
	new npc_gardien_de_flammes();
	new npc_gardien_de_terre();
}