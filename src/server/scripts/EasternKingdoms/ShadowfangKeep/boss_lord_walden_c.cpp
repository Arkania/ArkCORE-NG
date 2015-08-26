/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * This file is NOT free software. Third-party users can NOT redistribute 
 * it or modify it. If you find it, you are either hacking something, or very 
 * lucky (presuming someone else managed to hack it).
 */

/*
SDName: Boss Lord Walden
SD%Complete: 98%
SDComment: Just need to fix SPELL_TOXIC_COAGULANT_SLOW/SPELL_TOXIC_COAGULANT_FIRE removing while moving/staying.
SDCategory: Shadowfang Keep
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "shadowfang_keep.h"

enum Spells
{
    SPELL_CONJURE_FROST_MIXTURE     = 93505,
    SPELL_CONJURE_POISONOUS_MIXTURE = 93697,
    SPELL_CONJURE_MYSTERY_TOXIN     = 93563, // used for summon NPC with auras : SPELL_TOXIC_COAGULANT_SLOW or SPELL_TOXIC_COAGULANT_FIRE
    SPELL_TOXIC_COAGULANT_SLOW      = 93572, // H only
    SPELL_TOXIC_COAGULANT_FIRE      = 93573, // H only
    SPELL_ICE_SHARDS                = 93527,
};

enum Yells
{
    SAY_AGGRO                   = 0,
    SAY_KILL_1                  = 1,
    SAY_KILL_2                  = 2,
    SAY_DEATH                   = 3
};

class boss_lord_walden : public CreatureScript
{
public:
    boss_lord_walden() : CreatureScript("boss_lord_walden") { }

    struct boss_lord_waldenAI : public BossAI
    {
        boss_lord_waldenAI(Creature* creature) : BossAI(creature, BOSS_LORD_WALDEN)
        {
            pInstance = creature->GetInstanceScript();
        }

        uint32 ConjureMixtureTimer;
        uint32 ToxicCoagulantTimer;
        uint32 IceShardsTimer;

        InstanceScript *pInstance;

        void Reset() override
        {
            ConjureMixtureTimer = 9000;
            IceShardsTimer = 16000;
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);

            if (IsHeroic())
                ToxicCoagulantTimer = 11000;

            if (pInstance)
                pInstance->SetData(BOSS_LORD_WALDEN, NOT_STARTED);
        }

        void KilledUnit(Unit* /*who*/) override
        {
            switch(urand(0,1))
            {
                case 0: Talk(SAY_KILL_1); break;
                case 1: Talk(SAY_KILL_2); break;
            }
        }

        void EnterCombat(Unit* /*who*/) override
        {
            Talk(SAY_AGGRO);

            if (pInstance)
                pInstance->SetData(BOSS_LORD_WALDEN, IN_PROGRESS);
        }

        void JustDied(Unit* /*pKiller*/) override
        {
            //me->SummonCreature(BOSS_COMMANDER_ULTHOK, 59.185f, 802.251f, 805.730f, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 8640000);
            Talk(SAY_DEATH);

            if (pInstance)
                pInstance->SetData(BOSS_LORD_WALDEN, DONE);
        }

		void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (ConjureMixtureTimer <= diff)
            {
                switch(urand(0,1))
                {
                    case 0: DoCastAOE(SPELL_CONJURE_FROST_MIXTURE); break;
                    case 1: DoCastAOE(SPELL_CONJURE_POISONOUS_MIXTURE); break;
                }
                ConjureMixtureTimer = urand(4000,10000);
            } else ConjureMixtureTimer -= diff;

            if (ToxicCoagulantTimer <= diff)
            {
                DoCastAOE(SPELL_CONJURE_MYSTERY_TOXIN);
                ToxicCoagulantTimer = urand(8000,20000);
            } else ToxicCoagulantTimer -= diff;

            if (IceShardsTimer <= diff)
            {
                DoCastAOE(SPELL_ICE_SHARDS, true);
                IceShardsTimer = urand(6000,10000);
            } else IceShardsTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature *creature) const
    {
        return GetShadowfangKeepAI<boss_lord_waldenAI>(creature);
    }
};

// 50439 50522 
class npc_mystery_toxin : public CreatureScript
{
public:
    npc_mystery_toxin() : CreatureScript("npc_mystery_toxin") { }

    struct npc_mystery_toxinAI : public ScriptedAI
    {
        npc_mystery_toxinAI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = creature->GetInstanceScript();
        }

        InstanceScript *pInstance;

        void Reset()
        {
            me->SetObjectScale(1.0f);
            me->SetDisplayId(23767);
            float x,y,z;
            me->GetPosition(x,y,z);
            me->Relocate(x, y, z + 5.0f);
            
            switch(urand(0,1))
            {
                case 0: me->AddAura(SPELL_TOXIC_COAGULANT_SLOW, me); break;
                case 1: me->AddAura(SPELL_TOXIC_COAGULANT_FIRE, me); break;
            }
        }
    };

    CreatureAI* GetAI(Creature *creature) const
    {
        return new npc_mystery_toxinAI (creature);
    }
};

void AddSC_boss_lord_walden()
{
    new boss_lord_walden();
    new npc_mystery_toxin();
}