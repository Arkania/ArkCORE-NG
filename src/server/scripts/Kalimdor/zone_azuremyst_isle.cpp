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

/* ScriptData
SDName: Azuremyst_Isle
SD%Complete: 75
SDComment: Quest support: 9283, 9537, 9582, 9554, ? (special flight path, proper model for mount missing). Injured Draenei cosmetic only, 9582.
SDCategory: Azuremyst Isle
EndScriptData */

/* ContentData
npc_draenei_survivor
npc_engineer_spark_overgrind
npc_injured_draenei
npc_magwin
go_ravager_cage
npc_death_ravager
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "ScriptedGossip.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"

enum Azuremyst_Isle
{
	NPC_DRAENEI_SURVIVOR				= 16483,
	NPC_NESTLEWOOD_OWLKIN				= 16518,
	NPC_DEATH_RAVAGER					= 17556,
	NPC_STILLPINE_CAPITIVE              = 17375,
	NPC_SPARK_OVERGRIND					= 17243,
	NPC_MAGWIN							= 17312,
	NPC_STILLPINE_CAPTIVE				= 17375,

	GO_BRISTELIMB_CAGE                  = 181714,

	QUEST_INOCULATION					= 9303,
	QUEST_A_CRY_FOR_SAY_HELP			= 9528,
	QUEST_STRENGTH_ONE					= 9582,
	QUEST_THE_PROPHECY_OF_AKIDA         = 9544,
	QUEST_GNOMERCY						= 9537,

	SPELL_INOCULATE_NESTLEWOOD_OWLKIN	= 29528,
	SPELL_IRRIDATION					= 35046,
    SPELL_STUNNED						= 28630,
	SPELL_DYNAMITE						= 7978,
	SPELL_REND							= 13443,
    SPELL_ENRAGING_BITE					= 30736,

	FACTION_HOSTILE						= 14,

	AREA_COVE							= 3579,
    AREA_ISLE							= 3639,      

	POINT_INIT                          = 1,
    EVENT_DESPAWN                       = 1,
};

#define GOSSIP_FIGHT "Traitor! You will be brought to justice!"

/*######
## npc_draenei_survivor
######*/

class npc_draenei_survivor : public CreatureScript
{
public:
    npc_draenei_survivor() : CreatureScript("npc_draenei_survivor") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_draenei_survivorAI (creature);
    }

    struct npc_draenei_survivorAI : public ScriptedAI
    {
        npc_draenei_survivorAI(Creature* creature) : ScriptedAI(creature) {}

        uint64 pCaster;

        uint32 SayThanksTimer;
        uint32 RunAwayTimer;
        uint32 SayHelpTimer;

        bool CanSayHelp;

        void Reset()
        {
            pCaster = 0;

            SayThanksTimer = 0;
            RunAwayTimer = 0;
            SayHelpTimer = 10000;

            CanSayHelp = true;

            DoCast(me, SPELL_IRRIDATION, true);

            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PVP_ATTACKABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IN_COMBAT);
            me->SetHealth(me->CountPctFromMaxHealth(10));
            me->SetStandState(UNIT_STAND_STATE_SLEEP);
        }

        void EnterCombat(Unit* /*who*/) {}

        void MoveInLineOfSight(Unit* who)
        {
            if (CanSayHelp && who->GetTypeId() == TYPEID_PLAYER && me->IsFriendlyTo(who) && me->IsWithinDistInMap(who, 25.0f))
            {                
				Talk(1); // DoScriptText(RAND(SAY_HELP1, SAY_HELP2, SAY_HELP3, SAY_HELP4), me, who);
                SayHelpTimer = 20000;
                CanSayHelp = false;
            }
        }

        void SpellHit(Unit* Caster, const SpellInfo* Spell)
        {
            if (Spell->SpellFamilyFlags[2] & 0x080000000)
            {
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PVP_ATTACKABLE);
                me->SetStandState(UNIT_STAND_STATE_STAND);
                DoCast(me, SPELL_STUNNED, true);
                pCaster = Caster->GetGUID();
                SayThanksTimer = 5000;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (SayThanksTimer)
            {
                if (SayThanksTimer <= diff)
                {
                    me->RemoveAurasDueToSpell(SPELL_IRRIDATION);

                    if (Player* player = Unit::GetPlayer(*me, pCaster))
                    {
                        Talk(0); // DoScriptText(RAND(SAY_HEAL1, SAY_HEAL2, SAY_HEAL3, SAY_HEAL4), me, player);
                        player->TalkedToCreature(me->GetEntry(), me->GetGUID()); // ?? gpn39f ask: what is this
                    }

                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MovePoint(0, -4115.053711f, -13754.831055f, 73.508949f);

                    RunAwayTimer = 10000;
                    SayThanksTimer = 0;
                } else SayThanksTimer -= diff;

                return;
            }

            if (RunAwayTimer)
            {
                if (RunAwayTimer <= diff)
                    me->DespawnOrUnsummon();
                else
                    RunAwayTimer -= diff;

                return;
            }

            if (SayHelpTimer <= diff)
            {
                CanSayHelp = true;
                SayHelpTimer = 20000;
            } else SayHelpTimer -= diff;
        }
    };

};

/*######
## npc_engineer_spark_overgrind
######*/

class npc_engineer_spark_overgrind : public CreatureScript
{
public:
    npc_engineer_spark_overgrind() : CreatureScript("npc_engineer_spark_overgrind") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF)
        {
            player->CLOSE_GOSSIP_MENU();
            creature->setFaction(FACTION_HOSTILE);
            CAST_AI(npc_engineer_spark_overgrind::npc_engineer_spark_overgrindAI, creature->AI())->AttackStart(player);
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_GNOMERCY) == QUEST_STATUS_INCOMPLETE)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FIGHT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_engineer_spark_overgrindAI (creature);
    }

    struct npc_engineer_spark_overgrindAI : public ScriptedAI
    {
        npc_engineer_spark_overgrindAI(Creature* creature) : ScriptedAI(creature)
        {
            NormFaction = creature->getFaction();
            NpcFlags = creature->GetUInt32Value(UNIT_NPC_FLAGS);

            if (creature->GetAreaId() == AREA_COVE || creature->GetAreaId() == AREA_ISLE)
                IsTreeEvent = true;
        }

        uint32 NormFaction;
        uint32 NpcFlags;

        uint32 DynamiteTimer;
        uint32 EmoteTimer;

        bool IsTreeEvent;

        void Reset()
        {
            DynamiteTimer = 8000;
            EmoteTimer = urand(120000, 150000);

            me->setFaction(NormFaction);
            me->SetUInt32Value(UNIT_NPC_FLAGS, NpcFlags);

            IsTreeEvent = false;
        }

        void EnterCombat(Unit* who)
        {
			Talk(2); // DoScriptText(ATTACK_YELL, me, who);
        }

        void UpdateAI(uint32 diff)
        {
            if (!me->IsInCombat() && !IsTreeEvent)
            {
                if (EmoteTimer <= diff)
                {
					Talk(12); // DoScriptText(SAY_TEXT, me);                    
					Talk(1);  // DoScriptText(SAY_EMOTE, me);  // SAY_EMOTE = -1000185,
                    EmoteTimer = urand(120000, 150000);
                } else EmoteTimer -= diff;
            }
            else if (IsTreeEvent)
                return;

            if (!UpdateVictim())
                return;

            if (DynamiteTimer <= diff)
            {
                DoCast(me->GetVictim(), SPELL_DYNAMITE);
                DynamiteTimer = 8000;
            } else DynamiteTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };

};

/*######
## npc_injured_draenei
######*/

class npc_injured_draenei : public CreatureScript
{
public:
    npc_injured_draenei() : CreatureScript("npc_injured_draenei") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_injured_draeneiAI (creature);
    }

    struct npc_injured_draeneiAI : public ScriptedAI
    {
        npc_injured_draeneiAI(Creature* creature) : ScriptedAI(creature) {}

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IN_COMBAT);
            me->SetHealth(me->CountPctFromMaxHealth(15));
            switch (urand(0, 1))
            {
                case 0:
                    me->SetStandState(UNIT_STAND_STATE_SIT);
                    break;

                case 1:
                    me->SetStandState(UNIT_STAND_STATE_SLEEP);
                    break;
            }
        }

        void EnterCombat(Unit* /*who*/) {}

        void MoveInLineOfSight(Unit* /*who*/) {}

        void UpdateAI(uint32 /*diff*/) {}
    };

};

/*######
## npc_magwin
######*/

class npc_magwin : public CreatureScript
{
public:
    npc_magwin() : CreatureScript("npc_magwin") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_A_CRY_FOR_SAY_HELP)
        {
            creature->setFaction(113);
            if (npc_escortAI* pEscortAI = CAST_AI(npc_escortAI, creature->AI()))
                pEscortAI->Start(true, false, player->GetGUID());
        }
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_magwinAI(creature);
    }

    struct npc_magwinAI : public npc_escortAI
    {
        npc_magwinAI(Creature* creature) : npc_escortAI(creature) {}

        void WaypointReached(uint32 waypointId)
        {
            if (Player* player = GetPlayerForEscort())
            {
                switch (waypointId)
                {
                    case 0:
                        Talk(0); // DoScriptText(SAY_START, me, player);
                        break;
                    case 17:
                        Talk(2); // DoScriptText(SAY_PROGRESS, me, player);
                        break;
                    case 28:
                        Talk(3); // DoScriptText(SAY_END1, me, player);
                        break;
                    case 29:
                        Talk(5); // DoScriptText(EMOTE_HUG, me, player);
                        Talk(4); // DoScriptText(SAY_END2, me, player);
                        player->GroupEventHappens(QUEST_A_CRY_FOR_SAY_HELP, me);
                        break;
                }
            }
        }

        void EnterCombat(Unit* who)
        {
            Talk(1); // DoScriptText(SAY_AGGRO, me, who);
        }

        void Reset() {}
    };

};

/*######
## go_ravager_cage
######*/

class go_ravager_cage : public GameObjectScript
{
public:
    go_ravager_cage() : GameObjectScript("go_ravager_cage") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_STRENGTH_ONE) == QUEST_STATUS_INCOMPLETE)
        {
            if (Creature* ravager = go->FindNearestCreature(NPC_DEATH_RAVAGER, 5.0f, true))
            {
                ravager->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                ravager->SetReactState(REACT_AGGRESSIVE);
                ravager->AI()->AttackStart(player);
            }
        }
        return true;
    }
};

/*######
## npc_death_ravager
######*/

class npc_death_ravager : public CreatureScript
{
public:
    npc_death_ravager() : CreatureScript("npc_death_ravager") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_death_ravagerAI(creature);
    }

    struct npc_death_ravagerAI : public ScriptedAI
    {
        npc_death_ravagerAI(Creature* creature) : ScriptedAI(creature){}

        uint32 RendTimer;
        uint32 EnragingBiteTimer;

        void Reset()
        {
            RendTimer = 30000;
            EnragingBiteTimer = 20000;

            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_PASSIVE);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (RendTimer <= diff)
            {
                DoCast(me->GetVictim(), SPELL_REND);
                RendTimer = 30000;
            }
            else RendTimer -= diff;

            if (EnragingBiteTimer <= diff)
            {
                DoCast(me->GetVictim(), SPELL_ENRAGING_BITE);
                EnragingBiteTimer = 15000;
            }
            else EnragingBiteTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };

};

/*########
## Quest: The Prophecy of Akida
########*/

/*######
## npc_stillpine_captive
######*/

class npc_stillpine_captive : public CreatureScript
{
    public:
        npc_stillpine_captive() : CreatureScript("npc_stillpine_captive") { }

        struct npc_stillpine_captiveAI : public ScriptedAI
        {
            npc_stillpine_captiveAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void Reset()
            {
                if (GameObject* cage = me->FindNearestGameObject(GO_BRISTELIMB_CAGE, 5.0f))
                {
                    cage->SetLootState(GO_JUST_DEACTIVATED);
                    cage->SetGoState(GO_STATE_READY);
                }
                _events.Reset();
                _player = NULL;
                _movementComplete = false;
            }

            void StartMoving(Player* owner)
            {
                if (owner)
                {
                    Talk(0); // DoScriptText(RAND(CAPITIVE_SAY_1, CAPITIVE_SAY_2, CAPITIVE_SAY_3), me, owner);
                    _player = owner;
                }
                Position pos;
                me->GetNearPosition(pos, 3.0f, 0.0f);
                me->GetMotionMaster()->MovePoint(POINT_INIT, pos);
            }

            void MovementInform(uint32 type, uint32 id)
            {
                if (type != POINT_MOTION_TYPE || id != POINT_INIT)
                    return;

                if (_player)
                    _player->KilledMonsterCredit(me->GetEntry(), me->GetGUID());

                _movementComplete = true;
                _events.ScheduleEvent(EVENT_DESPAWN, 3500);
            }

            void UpdateAI(uint32 diff)
            {
                if (!_movementComplete)
                    return;

                _events.Update(diff);

                if (_events.ExecuteEvent() == EVENT_DESPAWN)
                    me->DespawnOrUnsummon();
            }

        private:
            Player* _player;
            EventMap _events;
            bool _movementComplete;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_stillpine_captiveAI(creature);
        }
};

/*######
## go_bristlelimb_cage
######*/

class go_bristlelimb_cage : public GameObjectScript
{
    public:
        go_bristlelimb_cage() : GameObjectScript("go_bristlelimb_cage") { }

        bool OnGossipHello(Player* player, GameObject* go)
        {
            if (player->GetQuestStatus(QUEST_THE_PROPHECY_OF_AKIDA) == QUEST_STATUS_INCOMPLETE)
            {
                if (Creature* capitive = go->FindNearestCreature(NPC_STILLPINE_CAPITIVE, 5.0f, true))
                {
                    go->ResetDoorOrButton();
                    CAST_AI(npc_stillpine_captive::npc_stillpine_captiveAI, capitive->AI())->StartMoving(player);
                    return false;
                }
            }
            return true;
        }
};

/*######
## npc_nestlewood_owlkin
######*/

class npc_nestlewood_owlkin : public CreatureScript
{
    public:
        npc_nestlewood_owlkin() : CreatureScript("npc_nestlewood_owlkin") { }

        struct npc_nestlewood_owlkinAI : public ScriptedAI
        {
            npc_nestlewood_owlkinAI(Creature* creature) : ScriptedAI(creature) { }

			void SpellHit(Unit * Hitter, SpellInfo const* spell) 
			{		
				Player* player = Hitter->ToPlayer();

				if (!player)
					return;				

				if (spell->Id == SPELL_INOCULATE_NESTLEWOOD_OWLKIN )
				{
					if (player->GetQuestStatus(QUEST_INOCULATION) == QUEST_STATUS_INCOMPLETE) 
					{						
						player->KilledMonsterCredit(NPC_NESTLEWOOD_OWLKIN, NULL);
						me->DespawnOrUnsummon(0);
					}									
				}
			}                               
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_nestlewood_owlkinAI(creature);
        }
};

void AddSC_azuremyst_isle()
{
    new npc_draenei_survivor();
    new npc_engineer_spark_overgrind();
    new npc_injured_draenei();
    new npc_magwin();
    new npc_death_ravager();
    new go_ravager_cage();
    new npc_stillpine_captive();
    new go_bristlelimb_cage();
	new npc_nestlewood_owlkin();
}