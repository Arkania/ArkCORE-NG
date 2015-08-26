/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * This file is NOT free software. Third-party users can NOT redistribute 
 * it or modify it. If you find it, you are either hacking something, or very 
 * lucky (presuming someone else managed to hack it).
 */

/*
SDName: Boss Baron Silverlaine
SD%Complete: 100%
SDComment: Works fine.
SDCategory: Shadowfang Keep
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "shadowfang_keep.h"

enum Spells
{
    /// Boss
    SPELL_SUMMON_WORGEN_SPIRIT    = 93857,
    SPELL_CURSED_VEIL             = 93956,
};

enum Yells
{
    SAY_AGGRO                   = 0,
    SAY_DEATH                   = 1
};

class boss_baron_silverlaine : public CreatureScript
{
public:
    boss_baron_silverlaine() : CreatureScript("boss_baron_silverlaine") { }

    struct boss_baron_silverlaineAI : public BossAI
    {
        boss_baron_silverlaineAI(Creature* creature) : BossAI(creature, BOSS_BARON_SILVERLAINE)
        {
            pInstance = creature->GetInstanceScript();
        }

        InstanceScript *pInstance;

        uint8 Phase;

        uint32 CurserVeilTimer;

        void Reset()
        {
            Phase = 0;

            CurserVeilTimer = 5500;
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);

            if (pInstance)
                pInstance->SetData(BOSS_BARON_SILVERLAINE, NOT_STARTED);
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_AGGRO);

            if (pInstance)
                pInstance->SetData(BOSS_BARON_SILVERLAINE, IN_PROGRESS);
        }

        void JustDied(Unit* /*pKiller*/)
        {
            //me->SummonCreature(BOSS_COMMANDER_ULTHOK, 59.185f, 802.251f, 805.730f, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 8640000);
            Talk(SAY_DEATH);

            if (pInstance)
                pInstance->SetData(BOSS_BARON_SILVERLAINE, DONE);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (CurserVeilTimer <= diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    DoCast(target, SPELL_CURSED_VEIL, true);
                CurserVeilTimer = urand(18000,22000);
            } else CurserVeilTimer -= diff;

            if ((me->HealthBelowPct(76) && Phase == 0) || (me->HealthBelowPct(51) && Phase == 1) || (me->HealthBelowPct(26) && Phase == 2))
            {
                Phase++;
                DoCast(me, SPELL_SUMMON_WORGEN_SPIRIT);
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature *creature) const
    {
        return GetShadowfangKeepAI<boss_baron_silverlaineAI>(creature);
    }
};

void AddSC_boss_baron_silverlaine()
{
    new boss_baron_silverlaine();
}