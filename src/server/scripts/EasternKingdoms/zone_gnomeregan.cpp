/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2017 ArkCORE <http://www.arkania.net/>
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
SDName: Gnomeregan
SD%Complete: 0
SDComment: Quest Support:
SDCategory: Gnomeregan
EndScriptData */


#include "script_helper.h"
#include "Creature.h"
#include "GameObjectAI.h"
#include "GameObject.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "ScriptedGossip.h"
#include "Vehicle.h"
#include "MovementGenerator.h"
#include "TargetedMovementGenerator.h"

// 42501
class npc_wounded_infantry_42501 : public CreatureScript
{
public:
    npc_wounded_infantry_42501() : CreatureScript("npc_wounded_infantry_42501") { }

    enum Dun_Morogh
    {
        //support quest 24533
        QUEST_ARTS_OF_A_PRIEST_26200 = 26200,
        //credt NPC
        NPC_HEALING_CREDIT_42501 = 42501
    };

    struct npc_wounded_infantry_42501AI : public ScriptedAI
    {
        npc_wounded_infantry_42501AI(Creature* creature) : ScriptedAI(creature) { }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (Player* player = caster->ToPlayer())
                if (player->GetQuestStatus(QUEST_ARTS_OF_A_PRIEST_26200) == QUEST_STATUS_INCOMPLETE)
                    player->KilledMonsterCredit(NPC_HEALING_CREDIT_42501);// New NPC ID
            me->DespawnOrUnsummon(500);
        }


        void EnterCombat(Unit* /*who*/) override { }

        void MoveInLineOfSight(Unit* /*who*/) override { }

        void UpdateAI(uint32 /*diff*/) override { }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_wounded_infantry_42501AI(creature);
    }
};

void AddSC_zone_gnomeregan()
{
    new npc_wounded_infantry_42501();
}

