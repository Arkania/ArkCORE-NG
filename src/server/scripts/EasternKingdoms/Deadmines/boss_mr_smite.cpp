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

/* ScriptData
SDName: Boss Mr.Smite
SD%Complete:
SDComment: Timers and say taken from acid script
EndScriptData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "deadmines.h"

enum Spels
{
    SPELL_TRASH             = 3391,
    SPELL_SMITE_STOMP       = 6432,
    SPELL_SMITE_SLAM        = 6435,
    SPELL_NIMBLE_REFLEXES   = 6264,

    EQUIP_SWORD             = 5191,
    EQUIP_MACE              = 7230,

    SAY_AGGRO               = 0,
};

// http://www.wowhead.com/npc=646/mr-smite
class boss_mr_smite : public CreatureScript
{
public:
    boss_mr_smite() : CreatureScript("boss_mr_smite") { }

    struct boss_mr_smiteAI : public ScriptedAI
    {
        boss_mr_smiteAI(Creature* creature) : ScriptedAI(creature)
        {
            m_instance = creature->GetInstanceScript();
        }

        InstanceScript* m_instance;
        EventMap m_events;
        uint32 m_phase;

        uint32 uiTrashTimer;
        uint32 uiSlamTimer;
        uint32 uiNimbleReflexesTimer;

        uint8 uiHealth;

        uint32 uiPhase;
        uint32 uiTimer;

        void Reset()
        {           
            m_events.Reset();

            uiTrashTimer = urand(5000, 9000);
            uiSlamTimer = 9000;
            uiNimbleReflexesTimer = urand(15500, 31600);

            uiHealth = 0;

            uiPhase = 0;
            uiTimer = 0;

            SetEquipmentSlots(false, EQUIP_SWORD, EQUIP_UNEQUIP, EQUIP_NO_CHANGE);
        }

        void EnterCombat(Unit* /*who*/)
        {
           Talk(SAY_AGGRO);
        }

        void JustDied(Unit* /*Killer*/)
        {

        }

        bool bCheckChances()
        {
            uint32 uiChances = urand(0, 99);
            if (uiChances <= 15)
                return false;
            else
                return true;
        }

        void UpdateAI(uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;

        /*START ACID-AI*/
            if (uiTrashTimer <= uiDiff)
            {
                if (bCheckChances())
                    DoCast(me, SPELL_TRASH);
                uiTrashTimer = urand(6000, 15500);
            } else uiTrashTimer -= uiDiff;

            if (uiSlamTimer <= uiDiff)
            {
                if (bCheckChances())
                    DoCastVictim(SPELL_SMITE_SLAM);
                uiSlamTimer = 11000;
            } else uiSlamTimer -= uiDiff;

            if (uiNimbleReflexesTimer <= uiDiff)
            {
                if (bCheckChances())
                    DoCast(me, SPELL_NIMBLE_REFLEXES);
                uiNimbleReflexesTimer = urand(27300, 60100);
            } else uiNimbleReflexesTimer -= uiDiff;
        /*END ACID-AI*/

            if ((uiHealth == 0 && !HealthAbovePct(66)) || (uiHealth == 1 && !HealthAbovePct(33)))
            {
                ++uiHealth;
                DoCastAOE(SPELL_SMITE_STOMP, false);
                SetCombatMovement(false);
                if (GameObject* go = GameObject::GetGameObject(*me, m_instance->GetData64(DATA_MR_SMITE_CHEST)))
                {
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MovePoint(1, go->GetPositionX() - 3.0f, go->GetPositionY(), go->GetPositionZ());
                }
            }

            if (uiPhase)
            {
                if (uiTimer <= uiDiff)
                {
                    switch (uiPhase)
                    {
                        case 1:
                            me->HandleEmoteCommand(EMOTE_STATE_KNEEL); //dosen't work?
                            uiTimer = 1000;
                            uiPhase = 2;
                            break;
                        case 2:
                            if (uiHealth == 1)
                                SetEquipmentSlots(false, EQUIP_SWORD, EQUIP_SWORD, EQUIP_NO_CHANGE);
                            else
                                SetEquipmentSlots(false, EQUIP_MACE, EQUIP_UNEQUIP, EQUIP_NO_CHANGE);
                            uiTimer = 500;
                            uiPhase = 3;
                            break;
                        case 3:
                            SetCombatMovement(true);
                            me->GetMotionMaster()->MoveChase(me->GetVictim(), me->m_CombatDistance);
                            uiPhase = 0;
                            break;
                    }
                } else uiTimer -= uiDiff;
            }

            DoMeleeAttackIfReady();
        }

        void MovementInform(uint32 uiType, uint32 /*uiId*/)
        {
            if (uiType != POINT_MOTION_TYPE)
                return;

            uiTimer = 1500;
            uiPhase = 1;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDeadminesAI<boss_mr_smiteAI>(creature);
    }
};

void AddSC_boss_mr_smite()
{
    new boss_mr_smite();
}
