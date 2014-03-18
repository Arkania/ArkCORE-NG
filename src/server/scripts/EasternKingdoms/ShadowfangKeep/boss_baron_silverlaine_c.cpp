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

    struct boss_baron_silverlaineAI : public ScriptedAI
    {
        boss_baron_silverlaineAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
            pInstance = pCreature->GetInstanceScript();
        }

        InstanceScript *pInstance;

        uint8 Phase;

        uint32 CurserVeilTimer;

        void Reset()
        {
            Phase = 0;

            CurserVeilTimer = 5500;

            if (pInstance)
                pInstance->SetData(DATA_BARON_SILVERLAINE_EVENT, NOT_STARTED);
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_AGGRO);

            if (pInstance)
                pInstance->SetData(DATA_BARON_SILVERLAINE_EVENT, IN_PROGRESS);
        }

        void JustDied(Unit* /*pKiller*/)
        {
            //me->SummonCreature(BOSS_COMMANDER_ULTHOK, 59.185f, 802.251f, 805.730f, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 8640000);
            Talk(SAY_DEATH);

            if (pInstance)
                pInstance->SetData(DATA_BARON_SILVERLAINE_EVENT, DONE);
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

            if (me->HealthBelowPct(76) && Phase == 0 || me->HealthBelowPct(51) && Phase == 1 || me->HealthBelowPct(26) && Phase == 2)
            {
                Phase++;
                DoCast(me, SPELL_SUMMON_WORGEN_SPIRIT);
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature *pCreature) const
    {
        return new boss_baron_silverlaineAI (pCreature);
    }
};

void AddSC_boss_baron_silverlaine()
{
    new boss_baron_silverlaine();
}