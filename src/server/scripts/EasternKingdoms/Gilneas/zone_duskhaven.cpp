/*
 *
* Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
* Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 *
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

/* ScriptData
SDName: duskhaven
SD%Complete: 0
SDComment: Quest support: 0
SDCategory: Gilneas
EndScriptData */

/* ContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "Player.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

// ++++++++++++++++++++++++++++++++++++++++++++ QUEST_LAST_CHANCE_AT_HUMANITY 14375 

enum e14375
{
    QUEST_LAST_CHANCE_AT_HUMANITY = 14375,

    NPC_LORD_GODFREY_36330 = 36330,
    NPC_LORD_GODFREY_36170 = 36170,
    NPC_KRENNAN_ARANAS_36331 = 36331,
    NPC_KING_GENN_GREYMANE_36332 = 36332,

};

/*######
## npc_lord_godfrey_36170
######*/

class npc_lord_godfrey_36170 : public CreatureScript
{
public:
    npc_lord_godfrey_36170() : CreatureScript("npc_lord_godfrey_36170") { }

    struct npc_lord_godfrey_36170AI : public ScriptedAI
    {
        npc_lord_godfrey_36170AI(Creature* creature) : ScriptedAI(creature) { }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lord_godfrey_36170AI(creature);
    }
};

/*######
## npc_king_genn_greymane_36332
######*/

class npc_king_genn_greymane_36332 : public CreatureScript
{
public:
    npc_king_genn_greymane_36332() : CreatureScript("npc_king_genn_greymane_36332") { }

    struct npc_king_genn_greymane_36332AI : public ScriptedAI
    {
        npc_king_genn_greymane_36332AI(Creature* creature) : ScriptedAI(creature) { }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_king_genn_greymane_36332AI(creature);
    }
};

/*######
## npc_krennan_aranas_36331
######*/

class npc_krennan_aranas_36331 : public CreatureScript
{
public:
    npc_krennan_aranas_36331() : CreatureScript("npc_krennan_aranas_36331") { }

    struct npc_krennan_aranas_36331AI : public ScriptedAI
    {
        npc_krennan_aranas_36331AI(Creature* creature) : ScriptedAI(creature) { }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_krennan_aranas_36331AI(creature);
    }
};



void AddSC_zone_gilneas_duskhaven()
{	
    new npc_lord_godfrey_36170();
    new npc_krennan_aranas_36331();
    new npc_king_genn_greymane_36332();


};
