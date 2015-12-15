/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
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
#include "Player.h"

 /*######
## npc_trainings_dummy
######*/

class npc_trainings_dummy : public CreatureScript
{
public:
    npc_trainings_dummy() : CreatureScript("npc_trainings_dummy") { }

    struct npc_trainings_dummyAI : public ScriptedAI
    {
        npc_trainings_dummyAI(Creature *c) : ScriptedAI(c) 
        { 
            SetCombatMovement(false);
        }
	
		bool	_spell_is_on_work;
		uint32	_timer;

		void Reset() override
		{ 			
			_spell_is_on_work=false; 
            _timer=0;
            me->SetReactState(REACT_PASSIVE);
            me->SetControlled(true, UNIT_STATE_STUNNED);
		}

        void DamageTaken(Unit* /*attacker*/, uint32& damage) override
        { 
            damage = 0;
        }

        void SpellHit(Unit * Hitter, SpellInfo const* spell) override
        {		
			// printf("Trigger Spell: %d \n",spell->Id);
			if (Player* player = Hitter->ToPlayer())
			{
				switch (player->getClass())
				{
				case CLASS_NONE:
					{
						break;
					}
				case CLASS_WARRIOR:
					{
						if (spell->Id==100) player->KilledMonsterCredit (44175);
						break;
					}
				case CLASS_PALADIN:
					{
						if (player->HasAura(105361) && spell->Id==20271) // wowhead: this is the correct spell/aura	: Seal of Command	
						{
							player->KilledMonsterCredit (44420); 
							player->KilledMonsterCredit (44175); 	
						}
						if (player->HasAura(20154) && spell->Id==20271)	// wowhead: this is a wrong lv 42 spell/aura, but used now in core.. : Seal of Righteousness				
						{
							player->KilledMonsterCredit (44420);
							player->KilledMonsterCredit (44175); 	
						}						
						break;
					}
				case CLASS_HUNTER:
					{
						if (spell->Id==56641) player->KilledMonsterCredit (44175);
						break;
					}
				case CLASS_ROGUE:
					{
						if (spell->Id==2098) player->KilledMonsterCredit (44175);
						break;
					}
				case CLASS_PRIEST:
					{
						if (spell->Id==589) player->KilledMonsterCredit (44175);
						break;
					}
				case CLASS_DEATH_KNIGHT:
					{					
						break;
					}
				case CLASS_SHAMAN:
					{
						if (spell->Id==73899) player->KilledMonsterCredit (44175);
						break;
					}
				case CLASS_MAGE:
					{
						if (!_spell_is_on_work)
						{
							if (Hitter->getRace()==RACE_TROLL)
							{
								if (spell->Id==122) player->KilledMonsterCredit (44175);
								if (spell->Id==133) player->KilledMonsterCredit (44175);
								if (spell->Id==2136) player->KilledMonsterCredit (44175);
							}
							if (spell->Id==7268 && !_spell_is_on_work)
							{
								_spell_is_on_work=true; _timer=7000;
								player->KilledMonsterCredit (44175);							
							}												
						}												
						break;
					}
				case CLASS_WARLOCK:
					{
						if (spell->Id==172) player->KilledMonsterCredit (44175);
                        if (spell->Id==348) player->KilledMonsterCredit (44175);
                        if (spell->Id==2098) player->KilledMonsterCredit (44175);
						break;
					}
				case CLASS_DRUID:
					{
						if (spell->Id==8921) player->KilledMonsterCredit (44175);
						break;
					}
				}		  
			}
        }

        void UpdateAI(uint32 diff) override
        {
            if (_spell_is_on_work)
            {
                if (_timer <= diff)
                    _spell_is_on_work = false;
                else
                    _timer -= diff;
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

