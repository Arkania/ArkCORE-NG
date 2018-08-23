/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
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
SDName: Mulgore
SD%Complete: 100
SDComment: Support for quest: 11129, 861
SDCategory: Mulgore
EndScriptData */

/* ContentData
npc_kyle_frenzied
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "SpellInfo.h"
#include "GameObjectAI.h"
#include "GameObject.h"
#include "Vehicle.h"
#include "VehicleDefines.h"
#include "Transport.h"
#include "TransportMgr.h"

// 23616
class npc_kyle_frenzied : public CreatureScript
{
public:
    npc_kyle_frenzied() : CreatureScript("npc_kyle_frenzied") { }

    enum KyleFrenzied
    {
        EMOTE_SEE_LUNCH = 0,
        EMOTE_EAT_LUNCH = 1,
        EMOTE_DANCE = 2,

        SPELL_LUNCH = 42222,
        NPC_KYLE_FRENZIED = 23616,
        NPC_KYLE_FRIENDLY = 23622,
        POINT_ID = 1
    };

    struct npc_kyle_frenziedAI : public ScriptedAI
    {
        npc_kyle_frenziedAI(Creature* creature) : ScriptedAI(creature) { }

        bool EventActive;
        bool IsMovingToLunch;
        uint64 PlayerGUID;
        uint32 EventTimer;
        uint8 EventPhase;

        void Reset() override
        {
            EventActive = false;
            IsMovingToLunch = false;
            PlayerGUID = 0;
            EventTimer = 5000;
            EventPhase = 0;

            if (me->GetEntry() == NPC_KYLE_FRIENDLY)
                me->UpdateEntry(NPC_KYLE_FRENZIED);
        }

        void SpellHit(Unit* Caster, SpellInfo const* Spell)
        {
            if (!me->GetVictim() && !EventActive && Spell->Id == SPELL_LUNCH)
            {
                if (Caster->GetTypeId() == TYPEID_PLAYER)
                    PlayerGUID = Caster->GetGUID();

                if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == WAYPOINT_MOTION_TYPE)
                {
                    me->GetMotionMaster()->MovementExpired();
                    me->GetMotionMaster()->MoveIdle();
                    me->StopMoving();
                }

                EventActive = true;
                Talk(EMOTE_SEE_LUNCH);
                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_CREATURE_SPECIAL);
            }
        }

        void MovementInform(uint32 type, uint32 pointId) override
        {
            if (type != POINT_MOTION_TYPE || !EventActive)
                return;

            if (pointId == POINT_ID)
                IsMovingToLunch = false;
        }

        void UpdateAI(uint32 diff) override
        {
            if (EventActive)
            {
                if (IsMovingToLunch)
                    return;

                if (EventTimer <= diff)
                {
                    EventTimer = 5000;
                    ++EventPhase;

                    switch (EventPhase)
                    {
                        case 1:
                            if (Unit* unit = ObjectAccessor::GetUnit(*me, PlayerGUID))
                            {
                                if (GameObject* go = unit->GetGameObject(SPELL_LUNCH))
                                {
                                    IsMovingToLunch = true;
                                    me->GetMotionMaster()->MovePoint(POINT_ID, go->GetPositionX(), go->GetPositionY(), go->GetPositionZ());
                                }
                            }
                            break;
                        case 2:
                            Talk(EMOTE_EAT_LUNCH);
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_USE_STANDING);
                            break;
                        case 3:
                            if (Player* unit = ObjectAccessor::GetPlayer(*me, PlayerGUID))
                                unit->TalkedToCreature(me->GetEntry(), me->GetGUID());

                            me->UpdateEntry(NPC_KYLE_FRIENDLY);
                            break;
                        case 4:
                            EventTimer = 30000;
                            Talk(EMOTE_DANCE);
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_DANCESPECIAL);
                            break;
                        case 5:
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);
                            Reset();
                            me->GetMotionMaster()->Clear();
                            break;
                    }
                }
                else
                    EventTimer -= diff;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_kyle_frenziedAI(creature);
    }
};

// 36943
class npc_bristleback_invader : public CreatureScript
{
public:
    npc_bristleback_invader() : CreatureScript("npc_bristleback_invader") { }

    enum eMulgore
    {
        NPC_FLEDGLING_BRAVE = 36942,
    };

    struct npc_bristleback_invaderAI : public ScriptedAI
    {
        npc_bristleback_invaderAI(Creature *c) : ScriptedAI(c) {}

        uint32 _timer;            

        void Reset()  
        {
            _timer = urand(1800,2200);                       
        }

        void UpdateAI(uint32 diff) 
        {                        
            if (!UpdateVictim())
            {
				if (_timer <= diff)
				{
					if (Creature* brave = me->FindNearestCreature (NPC_FLEDGLING_BRAVE, 3.0f)) 
					{                   
                        me->SetFacingTo (me->GetAngle(brave));
                        me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK1H);
                        _timer = urand(1800,2200);
                    }                    
                } 
				else 
					_timer -= diff;
            } 
			else 
                DoMeleeAttackIfReady();
            
        }
    };

       CreatureAI* GetAI(Creature* creature) const  
    {
        return new npc_bristleback_invaderAI (creature);
    }
};

// 36942
class npc_fledgling_brave : public CreatureScript
{
public:
    npc_fledgling_brave() : CreatureScript("npc_fledgling_brave") { }

    enum eMulgore
    {
        NPC_BRISTLEBACK_INVADER = 36943,
    };

    struct npc_fledgling_braveAI : public ScriptedAI
    {
        npc_fledgling_braveAI(Creature *c) : ScriptedAI(c) {}

        uint32 _timer;            

        void Reset()  
        {
            _timer = urand(1800,2200);                       
        }

        void UpdateAI(uint32 diff) 
        {                        
            if (!UpdateVictim())
            {
				if (_timer <= diff)
                {
					if (Creature* invader = me->FindNearestCreature (NPC_BRISTLEBACK_INVADER, 3.0f)) 
					{                   
                        me->SetFacingTo (me->GetAngle(invader));
                        me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK1H);
                        _timer = urand(1800,2200);
                    }                   
                } 
				else 
					_timer -= diff;
            } 
			else 
                DoMeleeAttackIfReady();
            
        }
    };

       CreatureAI* GetAI(Creature* creature) const  
    {
        return new npc_fledgling_braveAI (creature);
    }
};

// 202112
class go_quilboar_cage_202112 : public GameObjectScript
{
public:
    go_quilboar_cage_202112() : GameObjectScript("go_quilboar_cage_202112") { }

    struct go_quilboar_cage_202112AI : public GameObjectAI
    {
        go_quilboar_cage_202112AI(GameObject* go) : GameObjectAI(go) { }

        void OnStateChanged(uint32 state, Unit* unit) override
        {
            if (unit)
                if (Player* player = unit->ToPlayer())
                    if (player->GetQuestStatus(24852) != QUEST_STATUS_REWARDED)
                        if (Creature* brave = go->FindNearestCreature(38345, 5.0f))
                        {
                            player->CastSpell(go, 71725, false);
                            brave->AI()->Talk(0);
                            Position pos = brave->GetNearPosition(30.0f, 0.0f);
                            brave->GetMotionMaster()->MovePoint(1, pos);
                            brave->DespawnOrUnsummon(5000);
                        }
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_quilboar_cage_202112AI(go);
    }

};

// 50465
class item_water_pitcher_50465 : public ItemScript
{
public:
    item_water_pitcher_50465() : ItemScript("item_water_pitcher_50465") { }

    bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& targets) override
    {
        player->KilledMonsterCredit(38438);
        return false;
    }

};

// 36790
class npc_eagle_spirit_36790 : public CreatureScript
{
public:
    npc_eagle_spirit_36790() : CreatureScript("npc_eagle_spirit_36790") { }

    struct npc_eagle_spirit_36790AI : public ScriptedAI
    {
        npc_eagle_spirit_36790AI(Creature *c) : ScriptedAI(c) {}

        void Reset()
        {
            me->SetSpeed(MOVE_FLIGHT, 4.0f, true);
            me->GetMotionMaster()->MovePath(3679001, false);
        }

        void MovementInform(uint32 type, uint32 pointId) override
        {
            if (type == WAYPOINT_MOTION_TYPE && pointId == 5)
                if (Vehicle* vehicle = me->GetVehicleKit())
                    if (Unit* unit = vehicle->GetPassenger(0))
                        if (Player* player = unit->ToPlayer())
                            player->ExitVehicle();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_eagle_spirit_36790AI(creature);
    }
};

// 36845
class npc_agitated_earth_spirit_36845 : public CreatureScript
{
public:
    npc_agitated_earth_spirit_36845() : CreatureScript("npc_agitated_earth_spirit_36845") { }

    struct npc_agitated_earth_spirit_36845AI : public ScriptedAI
    {
        npc_agitated_earth_spirit_36845AI(Creature *c) : ScriptedAI(c) {}

        uint32 m_phase;
        uint32 m_cd81305;
        uint64 m_playerGUID;

        void Reset()
        {
            m_phase = 0;
            m_cd81305 = 0;
            m_playerGUID = 0;
        }

        void EnterCombat(Unit* victim) 
        {
            if (Player* player = victim->ToPlayer())
                m_playerGUID = player->GetGUID();

            CastRockBarrage();
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) 
        { 
            if (spell->Id == 69453)
                if (Player* player = caster->ToPlayer())
                    if (player->GetQuestStatus(14491) == QUEST_STATUS_INCOMPLETE)
                    {
                        m_playerGUID = player->GetGUID();
                        uint32 rol = urand(0, 100);
                        if (rol < 30)
                        {
                            m_phase = 1;
                            me->setFaction(57);
                            CastRockBarrage();
                        }
                        else
                        {
                            me->setFaction(35);
                            player->KilledMonsterCredit(36872);
                            me->DespawnOrUnsummon(3000);
                        }
                    }
        }

        void UpdateAI(uint32 diff) override
        {
            if (m_phase)
                if (m_cd81305 < diff)
                    CastRockBarrage();
                else
                    m_cd81305 -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

        void CastRockBarrage()
        {
            if (!m_playerGUID || !m_phase)
                return;
            
            m_cd81305 = urand(21000, 31000);
            if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))                
                me->CastSpell(player, 81305);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_agitated_earth_spirit_36845AI(creature);
    }
};
//FIX THE QUEST 27066 MULGORE priest quest and druid quest 27067
// 45199

class npc_wounded_brave_45199 : public CreatureScript
{
public:
	npc_wounded_brave_45199() : CreatureScript("npc_wounded_brave_45199") {}

	enum eNpc
	{
		QUEST_A_REJUVENATING_TOUCH_27067 = 27067,
		QUEST_FLASH_HEAL_27066 = 27066,
		NPC_HEALING_CREDIT_44175 = 44175,
	};

	struct npc_wounded_brave_45199AI : public ScriptedAI
	{
		npc_wounded_brave_45199AI(Creature* creature) : ScriptedAI(creature) {}

		void SpellHit(Unit* caster, SpellInfo const* spell) override
		{
			if (Player* player = caster->ToPlayer())
				if (player->GetQuestStatus(QUEST_FLASH_HEAL_27066) == QUEST_STATUS_INCOMPLETE)
					player->KilledMonsterCredit(45199);
		}
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_wounded_brave_45199AI(creature);
	}
};


void AddSC_mulgore()
{
    new npc_kyle_frenzied();
    new npc_bristleback_invader();
    new npc_fledgling_brave();
    new go_quilboar_cage_202112();
    new item_water_pitcher_50465();
    new npc_eagle_spirit_36790();
    new npc_agitated_earth_spirit_36845();
    new npc_wounded_brave_45199();

}
