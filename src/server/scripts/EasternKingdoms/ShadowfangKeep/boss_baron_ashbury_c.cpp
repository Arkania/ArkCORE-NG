/*
 * Copyright (C) 2011-2014 ArkCORE <http://www.arkania.net/>
 *
 * This file is NOT free software. Third-party users can NOT redistribute 
 * it or modify it. If you find it, you are either hacking something, or very 
 * lucky (presuming someone else managed to hack it).
 */

/*
SDName: Boss Baron Ashbury
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
    SPELL_PAIN_AND_SUFFERING        = 93581, // N/H - 1st. 5500 - every 20 sec.
    SPELL_ASPHYXIATE                = 93423, // N/H - 1st. 20000 - every 45 secs.
    SPELL_STAY_OF_EXECUTION         = 93468, // N/H - 1.5 sec after SPELL_ASPHYXIATE
    SPELL_DARK_ARCHANGEL_FORM       = 93757, // H only - at. 20%
    SPELL_DARK_ARCHANGEL_VISUAL     = 93766,
    SPELL_CALAMITY                  = 93812, // H only - at. 20%
    SPELL_WRACKING_PAIN             = 93720, // H only - 1st. 13000 - every 25 sec.
};

enum Yells
{
    SAY_AGGRO                   = 0,
    SAY_ASPHYXIATE_CAST         = 1,
    SAY_STAY_OF_EXECUTION_CAST  = 2,
    SAY_DARK_ARCHANGEL_CAST     = 3,
    SAY_KILL_1                  = 4,
    SAY_KILL_2                  = 5,
    SAY_DEATH                   = 6
};

class boss_baron_ashbury : public CreatureScript
{
public:
    boss_baron_ashbury() : CreatureScript("boss_baron_ashbury") { }

    struct boss_baron_ashburyAI : public BossAI
    {
        boss_baron_ashburyAI(Creature* pCreature) : BossAI(pCreature, DATA_BARON_ASHBURY)
        {
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
            pInstance = pCreature->GetInstanceScript();
        }

        uint32 PainAndSufferingTimer;
        uint32 AsphyxiateTimer;
        uint32 StayOfExecutionTimer;
        uint32 WrackingPainTimer;
        uint32 DarkArchangelTimer;

        InstanceScript *pInstance;

        bool Phased, Asphyxiate, Angel, Achievement;

        void Reset()
        {
            Phased = false;
            Asphyxiate = false;
            Angel = false;
            Achievement = false;

            PainAndSufferingTimer = 5500;
            AsphyxiateTimer = 15000;

            me->RemoveAurasDueToSpell(SPELL_DARK_ARCHANGEL_FORM);
            me->RemoveAurasDueToSpell(SPELL_DARK_ARCHANGEL_VISUAL);

            if (IsHeroic())
            {
                WrackingPainTimer = 12000;
                Achievement = true;
            }

            if (pInstance)
                pInstance->SetData(DATA_BARON_ASHBURY_EVENT, NOT_STARTED);
        }

        void SpellHit(Unit* hitter, SpellInfo const* spell)
        {
            if (!hitter || !spell)
                return;

            if (spell->Id != SPELL_STAY_OF_EXECUTION)
                return;

            Achievement = false;
        }

        void KilledUnit(Unit* /*who*/)
        {
            switch(urand(0,1))
            {
                case 0: Talk(SAY_KILL_1); break;
                case 1: Talk(SAY_KILL_2); break;
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_AGGRO);

            if (pInstance)
                pInstance->SetData(DATA_BARON_ASHBURY_EVENT, IN_PROGRESS);
        }

        void JustDied(Unit* /*pKiller*/)
        {
            Talk(SAY_DEATH);

            if (pInstance)
                pInstance->SetData(DATA_BARON_ASHBURY_EVENT, DONE);
        }

        void UpdateAI(uint32 const diff)
        {
            if (!UpdateVictim())
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
                
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, false);
            
            if (PainAndSufferingTimer <= diff && Phased == false)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    DoCast(target, SPELL_PAIN_AND_SUFFERING, true);
                PainAndSufferingTimer = urand(10000,15000);
            } else PainAndSufferingTimer -= diff;

            if (WrackingPainTimer <= diff && Phased == false)
            {
                DoCastAOE(SPELL_WRACKING_PAIN, true);
                WrackingPainTimer = urand(22000,26000);
            } else WrackingPainTimer -= diff;

            if (AsphyxiateTimer <= diff && Phased == false && Asphyxiate == false)
            {
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, true);
                Asphyxiate = true;
                Talk(SAY_ASPHYXIATE_CAST);
                DoCastAOE(SPELL_ASPHYXIATE, false);
                StayOfExecutionTimer = 100;
                PainAndSufferingTimer = 12000;
                AsphyxiateTimer = 40000;
            } else AsphyxiateTimer -= diff;

            if (StayOfExecutionTimer <= diff && Phased == false && Asphyxiate == true)
            {
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, false);
                Asphyxiate = false;
                Talk(SAY_STAY_OF_EXECUTION_CAST);
                DoCast(me, SPELL_STAY_OF_EXECUTION);
            } else StayOfExecutionTimer -= diff;

            if (DarkArchangelTimer <= diff && Phased == true && Angel == false)
            {
                Angel = true;
                DoCast(me, SPELL_DARK_ARCHANGEL_FORM);
                me->AddAura(SPELL_DARK_ARCHANGEL_VISUAL, me);
                me->AddAura(SPELL_CALAMITY, me);
                Talk(SAY_DARK_ARCHANGEL_CAST);
            } else DarkArchangelTimer -= diff;

            if (IsHeroic() && me->HealthBelowPct(21) && Phased == false)
            {
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, true);
                DarkArchangelTimer = 100;
                Phased = true;
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature *pCreature) const
    {
        return new boss_baron_ashburyAI (pCreature);
    }
};

void AddSC_boss_baron_ashbury()
{
    new boss_baron_ashbury();
}