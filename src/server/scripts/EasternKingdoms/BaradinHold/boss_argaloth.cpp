/*
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
 *
 * This file is NOT free software. Third-party users can NOT redistribute 
 * it or modify it. If you find it, you are either hacking something, or very 
 * lucky (presuming someone else managed to hack it).
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ObjectMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "WorldPacket.h"

enum Spells
{
    // Fel Flames
    SPELL_FELFLAMES                          = 88999,
};

// 47829
class npc_felflames : public CreatureScript
{
    public:
        npc_felflames() : CreatureScript("npc_felflames") { }

        struct npc_felflamesAI : public ScriptedAI
        {
            npc_felflamesAI(Creature* creature) : ScriptedAI(creature)
            {
                m_pInstance = creature->GetInstanceScript();
            }

            InstanceScript* m_pInstance;
            uint32 m_uiFlamesTimer;
            bool flames;

            void Reset()
            {
                m_uiFlamesTimer = 100;
                flames = false;
            }

            void EnterCombat(Unit* /*who*/) 
            {
                m_uiFlamesTimer = 100;
                flames = false;
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (m_uiFlamesTimer <= diff && flames == false)
                {
                    DoCast(me, SPELL_FELFLAMES);
                    flames = true;
                }
                else
                    m_uiFlamesTimer -= diff;
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_felflamesAI(creature);
        }
};

void AddSC_boss_argaloth()
{   
    new npc_felflames();
}