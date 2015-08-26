/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * This file is NOT free software. Third-party users can NOT redistribute 
 * it or modify it. If you find it, you are either hacking something, or very 
 * lucky (presuming someone else managed to hack it).
 */

/*
SDName: Boss Commander Springvale
SD%Complete: 100%
SDComment: Full working.
SDCategory: Shadowfang Keep
*/

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "Spell.h"
#include "SpellAuraEffects.h"
#include "shadowfang_keep.h"

enum Spells
{
    SPELL_DESECRATION               = 93687,
    SPELL_MALEFIC_STRIKE            = 93685,
    SPELL_SHIELD_OF_THE_PERFIDIOUS  = 93736,
    SPELL_WORD_OF_SHAME             = 93852,
    SPELL_UNHOLY_POWER              = 93686,
    SPELL_UNHOLY_POWER_2            = 93735,
    SPELL_UNHOLY_EMPOWERMENT        = 93844,
};

enum Yells
{
    SAY_AGGRO                   = 0,
    SAY_SUMMON_ADDS             = 1,
    SAY_KILL_1                  = 2,
    SAY_KILL_2                  = 3,
    SAY_DEATH                   = 4
};

class boss_commander_springvale : public CreatureScript
{
public:
    boss_commander_springvale() : CreatureScript("boss_commander_springvale") { }

    struct boss_commander_springvaleAI : public BossAI
    {
        boss_commander_springvaleAI(Creature* creature) : BossAI(creature, BOSS_COMMANDER_SPRINGVALE)
        {
            pInstance = creature->GetInstanceScript();
        }

        std::list<uint64> SummonList;

        InstanceScript *pInstance;

        bool Achievement;

        uint32 DesecrationTimer;
        uint32 MaleficStrikeTimer;
        uint32 SummonAddsTimer;
        uint32 PowerCheckTimer;

        void Reset() override
        {
            Achievement = true;
            RemoveSummons();

            DesecrationTimer = 7500;
            MaleficStrikeTimer = 6000;
            SummonAddsTimer = 40000;
            PowerCheckTimer = 1000;
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);

            if (pInstance)
                pInstance->SetData(BOSS_COMMANDER_SPRINGVALE, NOT_STARTED);
        }

        void KilledUnit(Unit* /*victim*/) override
        {
            switch(urand(0,1))
            {
                case 0: Talk(SAY_KILL_1); break;
                case 1: Talk(SAY_KILL_2); break;
            }
        }

        void SpellHit(Unit* hitter, SpellInfo const* spell) override
        {
            if (!hitter || !spell)
                return;

            if (spell->Id != SPELL_UNHOLY_EMPOWERMENT)
                return;

            Achievement = false;
        }

        void EnterCombat(Unit* /*who*/) override
        {
            Talk(SAY_AGGRO);

            if (pInstance)
                pInstance->SetData(BOSS_COMMANDER_SPRINGVALE, IN_PROGRESS);
        }

        void JustSummoned(Creature* pSummon) override
        {
            if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
                pSummon->AI()->AttackStart(pTarget);
            SummonList.push_back(pSummon->GetGUID());
        }

        void RemoveSummons()
        {
            if (SummonList.empty())
                return;

            for (std::list<uint64>::const_iterator itr = SummonList.begin(); itr != SummonList.end(); ++itr)
            {
                if (Creature* pTemp = Unit::GetCreature(*me, *itr))
                    if (pTemp)
                        pTemp->DisappearAndDie();
            }
            SummonList.clear();
        }

        void JustDied(Unit* /*pKiller*/) override
        {
            //me->SummonCreature(BOSS_COMMANDER_ULTHOK, 59.185f, 802.251f, 805.730f, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 8640000);
            Talk(SAY_DEATH);
            RemoveSummons();
            pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_WORD_OF_SHAME);

            if (pInstance)
                pInstance->SetData(BOSS_COMMANDER_SPRINGVALE, DONE);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (DesecrationTimer <= diff)
            {
                DoCastVictim(SPELL_DESECRATION);
                DesecrationTimer = urand(14000,20000);
            } else DesecrationTimer -= diff;

            if (MaleficStrikeTimer <= diff)
            {
                DoCastVictim(SPELL_MALEFIC_STRIKE);
                MaleficStrikeTimer = urand(12000,18000);
            } else MaleficStrikeTimer -= diff;

            if (SummonAddsTimer <= diff)
            {
                Talk(SAY_SUMMON_ADDS);
                Position pos = me->GetPosition();
                me->SummonCreature(NPC_TORMENTED_OFFICER, pos, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                me->SummonCreature(NPC_WAILING_GUARDSMAN, pos, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                SummonAddsTimer = 40000;
            } else SummonAddsTimer -= diff;

            if (PowerCheckTimer <= diff)
            {
                if (Aura* aura = me->GetAura(SPELL_UNHOLY_POWER))
                    if (aura->GetStackAmount() == 3)
                    {
                        switch (urand(0,1))
                        {
                            case 0: DoCastVictim(SPELL_SHIELD_OF_THE_PERFIDIOUS); break;
                            case 1:
                                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                    DoCast(target, SPELL_WORD_OF_SHAME, true);
                                break;
                        }
                        me->RemoveAura(aura);
                    }
                PowerCheckTimer = 1000;
            } else PowerCheckTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature *creature) const
    {
        return GetShadowfangKeepAI<boss_commander_springvaleAI>(creature);
    }
};

void AddSC_boss_commander_springvale()
{
    new boss_commander_springvale();
}