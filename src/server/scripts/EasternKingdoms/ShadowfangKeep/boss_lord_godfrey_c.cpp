/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * This file is NOT free software. Third-party users can NOT redistribute 
 * it or modify it. If you find it, you are either hacking something, or very 
 * lucky (presuming someone else managed to hack it).
 */

/*
SDName: Boss Lord Godfrey
SD%Complete: 100%
SDComment: Works fine.
SDCategory: Shadowfang Keep
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "shadowfang_keep.h"

enum eTexts
{
    SAY_AGGRO_A            = 0,
    SAY_AGGRO_H            = 1,
    SAY_DEATH              = 2,
    SAY_KILL_1             = 3,
    SAY_KILL_2             = 4,
    SAY_PISTOL_BARRAGE     = 5,
};

enum eSpells
{
    SPELL_PISTOL_BARRAGE        = 93520,
    SPELL_CURSED_BULLETS        = 93629,
    SPELL_SUMMON_GHOULS         = 93707,
    SPELL_MORTAL_WOUND          = 93675,
    SPELL_GHOUL_ACHIEVEMENT     = 95929,
};

class boss_lord_godfrey : public CreatureScript
{
public:
    boss_lord_godfrey() : CreatureScript("boss_lord_godfrey") { }

    struct boss_lord_godfreyAI : public BossAI
    {
        boss_lord_godfreyAI(Creature* creature) : BossAI(creature, BOSS_LORD_GODFREY)
        {
            pInstance = creature->GetInstanceScript();
        }

        InstanceScript *pInstance;

        uint32 SummonGhoulsTimer;
        uint32 PistolBarrageTimer;
        uint32 CursedBulletsTimer;
        uint32 MortalWoundTimer;

        uint16 GhoulCount;

        void Reset() override
        {
            GhoulCount = 0;
            SummonGhoulsTimer = 30000;
            CursedBulletsTimer = 15000;
            MortalWoundTimer = 6000;
            me->ApplySpellImmune(0, IMMUNITY_ID, 93564, true); // Pistol Barrage
            me->ApplySpellImmune(0, IMMUNITY_ID, 93784, true); // Pistol Barrage

            if (pInstance)
                pInstance->SetData(BOSS_LORD_GODFREY, NOT_STARTED);
        }

        void EnterCombat(Unit* who) override
        {
            if(who->ToPlayer()->GetTeamId() == TEAM_ALLIANCE)
                Talk(SAY_AGGRO_A);
            else
                Talk(SAY_AGGRO_H);

            if (pInstance)
                pInstance->SetData(BOSS_LORD_GODFREY, IN_PROGRESS);
        }

        void KilledUnit(Unit* creature) override
        {
            if (creature->GetEntry() == NPC_BLOODTHIRSTY_GHOUL)
                GhoulCount++;
            else
                switch(urand(0,1))
                {
                    case 0: Talk(SAY_KILL_1); break;
                    case 1: Talk(SAY_KILL_2); break;
                }
        }

        void JustDied(Unit* /*pKiller*/) override
        {
            Talk(SAY_DEATH);

            if (pInstance)
                pInstance->SetData(BOSS_LORD_GODFREY, DONE);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (SummonGhoulsTimer <= diff)
            {
                DoCast(me,SPELL_SUMMON_GHOULS);
                Position pos = me->GetPosition();
                for(uint32 i = 0; i<3; i++) // Hack.
                    me->SummonCreature(NPC_BLOODTHIRSTY_GHOUL, pos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 4000);
                PistolBarrageTimer = 500;
                SummonGhoulsTimer = 30000;
            } else SummonGhoulsTimer -= diff;

            if (PistolBarrageTimer <= diff)
            {
                Talk(SAY_PISTOL_BARRAGE);
                DoCastVictim(SPELL_PISTOL_BARRAGE);
                PistolBarrageTimer = 35000;
                SummonGhoulsTimer = 30000;
            } else PistolBarrageTimer -= diff;

            if (CursedBulletsTimer <= diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    DoCast(target,SPELL_CURSED_BULLETS);
                CursedBulletsTimer = 15000;
            } else CursedBulletsTimer -= diff;

            if (MortalWoundTimer <= diff)
            {
                DoCastVictim(SPELL_MORTAL_WOUND);
                MortalWoundTimer = 6000;
            } else MortalWoundTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetShadowfangKeepAI<boss_lord_godfreyAI>(creature);
    }
};


void AddSC_boss_lord_godfrey()
{
    new boss_lord_godfrey();
}
