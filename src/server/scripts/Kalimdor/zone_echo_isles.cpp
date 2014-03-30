/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2014 ArkCORE <http://www.arkania.net/> 
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "ScriptedFollowerAI.h"

enum eZoneEchoIsle
{
	NPC_NOVICE_DARKSPEAR_WARRIOR		= 38268,
	NPC_TIKI_TARGET						= 38038,
};

/*######
## npc_novice_darkspear_warrior
######*/

class npc_novice_darkspear_warrior : public CreatureScript
{
public:
    npc_novice_darkspear_warrior() : CreatureScript("npc_novice_darkspear_warrior") { }

    struct npc_novice_darkspear_warriorAI : public ScriptedAI
    {
        npc_novice_darkspear_warriorAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 _timer;            

        void Reset()  
        {
            _timer = urand(1800,2200);                       
        }

        void UpdateAI(const uint32 diff) 
        {                        
            if (!UpdateVictim())
            {
                if (Creature* tiki = me->FindNearestCreature (NPC_TIKI_TARGET, 3.0f)) 
                {
                    if (_timer <= diff)
                    {
                        me->SetFacingTo (me->GetAngle(tiki));
                        me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK1H);
                        _timer = urand(1800,2200);
                    }
                    else 
						_timer -= diff;
                }
            } else 
                DoMeleeAttackIfReady();
            
        }
    };

       CreatureAI* GetAI(Creature* creature) const  
    {
        return new npc_novice_darkspear_warriorAI (creature);
    }
};




void AddSC_zone_echo_isles()
{
	new npc_novice_darkspear_warrior();
}