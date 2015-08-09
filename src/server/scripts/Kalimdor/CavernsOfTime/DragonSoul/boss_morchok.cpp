/*
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
 *
 * This file is NOT free software. Third-party users can NOT redistribute
 * it or modify it. If you find it, you are either hacking something, or very
 * lucky (presuming someone else managed to hack it).
 */

/* ScriptData
SDName: boss_morchok
SD%Complete: 70%
SDComment:
SDCategory: Boss Morchok
EndScriptData
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "dragon_soul.h"
#include "GameObjectAI.h"

#define SPELL_STOMP RAID_MODE(109033, 109034, 103414, 108571)
#define SPELL_KORCHOM RAID_MODE(109034, 109017) // This spell must be just in 10HC / 25HC 

enum Yells
{
    SAY_AGGRO = 0,
    SAY_DEATH = 1,
    SAY_EVENT1 = 2, // No work
    SAY_EVENT2 = 3, // No work
    SAY_EVENT3 = 4,
    SAY_EVENT4 = 5,
    SAY_GROUNT1 = 6,
    SAY_GROUNT2 = 7,
    SAY_INTRO = 8,
    SAY_ORB = 9, // No work
    SAY_SLAY = 10,
    SAY_SPLIT = 11,
    SAY_PLAYER_KILL = 12,
    SAY_SUMMON_CRYSTAL = 13
};

enum Events
{
    EVENT_CRUSH_ARMOR = 1,
    EVENT_STOMP,
    EVENT_RESONATING_CRYSTAL,
    EVENT_FURIOUS,
    EVENT_KORCHOM,
    EVENT_EARTHS_VENGEANCE,
    EVENT_BLACK_BLOOD_OF_THE_EARTH,
    EVENT_SUMMON,
    EVENT_EXPLODE,
    EVENT_EXPLODE_1,
    EVENT_EXPLODE_2,
    EVENT_EXPLODE_3,
    EVENT_UN_EXPLODE_1,
    EVENT_UN_EXPLODE_2,
    EVENT_UN_EXPLODE_3,
    EVENT_DESPAWN,
    EVENT_RESONATING,
    EVENT_ANTI_EXPLODE,
    EVENT_CLEANING,
    EVENT_PHASE_NORMAL,
    EVENT_PHASE_BLACK_BLOOD,
    EVENT_EARTHS_VENGEANCE_DROP,
    EVENT_ENRAGE,
    EVENT_BLACK_BLOOD,
    EVENT_BLACK_BLOOD_DESPAWN,
    EVENT_EARTHER_VORTEX,
    EVENT_VORTEX,
    EVENT_SUMMON_KOHCROM,
    EVENT_SAY
};

enum Spells
{
    SPELL_FURIOUS = 103846,
    SPELL_CRUSH_ARMOR = 103687,
    SPELL_BLACK_BLOOD_OF_THE_EARTH = 103851,
    SPELL_EARTHER_VORTEX = 103821,
    SPELL_CLEAR_DEBUFFS = 34098,
    SPELL_RESONATING_CRYSTAL = 103640,
    SPELL_SUMMON_KOHCROM = 109017,
    SPELL_EARTHS_VENGEANCE_CHANNEL = 103176,
    SPELL_EARTHS_VENGEANCE = 103178,
    SPELL_SUMMON = 22951,
    SPELL_BLACK_BLOOD_SUM = 103180,
    SPELL_RESONATING_CRYSTAL_EX = 108572,
    SPELL_RESONATING_CRYSTAL_AURA = 103494,
    SPELL_DANGER = 103534,
    SPELL_WARNING = 103536,
    SPELL_SAFE = 103541,
    SPELL_VORTEX = 103821,
    SPELL_ENRAGE = 47008
};

enum Phases
{
    PHASE_NORMAL = 1,
    PHASE_BLACK_BLOOD = 2
};

#define NPC_BLACK_BLOOD_OF_THE_EARTH 55267

enum Auras
{
    AURA_BLACK_BLOOD_OF_THE_EARTH = 103180
};

enum Actions
{
    ACTION_SUMMON = 1,
};

Position const BlackBloodPositions[105] =
{
    { -2021.22f, -2423.58f, 70.4165f, 0.0f },
    { -1955.89f, -2390.33f, 68.1956f, 0.0f },
    { -1951.74f, -2396.78f, 68.708f, 0.0f },
    { -1951.51f, -2405.36f, 68.7822f, 0.0f },
    { -1955.62f, -2413.88f, 68.1675f, 0.0f },
    { -1961.79f, -2425.51f, 67.7393f, 0.0f },
    { -1968.3f, -2422.94f, 68.427f, 0.0f },
    { -1968.65f, -2416.38f, 68.777f, 0.0f },
    { -1969.11f, -2407.54f, 68.5753f, 0.0f },
    { -1974.8f, -2399.67f, 68.6092f, 0.0f },
    { -1979.19f, -2407.44f, 68.8731f, 0.0f },
    { -1983.27f, -2413.9f, 69.2383f, 0.0f },
    { -1989.26f, -2417.97f, 69.4564f, 0.0f },
    { -1991.56f, -2410.02f, 69.7882f, 0.0f },
    { -1992.43f, -2402.21f, 70.1632f, 0.0f },
    { -1961.03f, -2385.62f, 67.876f, 0.0f },
    { -1994.42f, -2400.44f, 70.266f, 0.0f },
    { -1996.89f, -2393.62f, 70.3023f, 0.0f },
    { -1992.96f, -2388.57f, 70.453f, 0.0f },
    { -1985.18f, -2385.94f, 69.6471f, 0.0f },
    { -1978.36f, -2385.15f, 68.8438f, 0.0f },
    { -1970.38f, -2385.12f, 68.0089f, 0.0f },
    { -2007.42f, -2400.52f, 70.5017f, 0.0f },
    { -2009.46f, -2408.04f, 70.3216f, 0.0f },
    { -2008.13f, -2416.89f, 69.9967f, 0.0f },
    { -2007.37f, -2423.34f, 69.8728f, 0.0f },
    { -2000.04f, -2426.77f, 69.4225f, 0.0f },
    { -2000.25f, -2417.37f, 69.7463f, 0.0f },
    { -2000.57f, -2410.2f, 70.0755f, 0.0f },
    { -1993.59f, -2407.42f, 69.9894f, 0.0f },
    { -2011.53f, -2392.92f, 70.6457f, 0.0f },
    { -2019.63f, -2413.32f, 70.5068f, 0.0f },
    { -2020.19f, -2404.12f, 70.9386f, 0.0f },
    { -2021.8f, -2394.2f, 71.2534f, 0.0f },
    { -1992.81f, -2426.21f, 69.4211f, 0.0f },
    { -1988.45f, -2425.0f, 69.3596f, 0.0f },
    { -1980.25f, -2423.91f, 69.0551f, 0.0f },
    { -1973.34f, -2422.84f, 68.8028f, 0.0f },
    { -1966.64f, -2421.79f, 68.407f, 0.0f },
    { -1986.08f, -2417.15f, 69.3694f, 0.0f },
    { -1978.52f, -2440.58f, 67.1988f, 0.0f },
    { -1984.1f, -2442.4f, 66.9516f, 0.0f },
    { -1982.69f, -2438.67f, 67.6049f, 0.0f },
    { -2012.15f, -2437.57f, 68.0544f, 0.0f },
    { -2016.98f, -2426.87f, 70.3127f, 0.0f },
    { -2000.99f, -2431.11f, 69.0353f, 0.0f },
    { -1993.64f, -2431.1f, 68.9213f, 0.0f },
    { -1984.42f, -2431.09f, 68.7047f, 0.0f },
    { -1978.58f, -2431.09f, 68.65f, 0.0f },
    { -1973.91f, -2431.09f, 68.3554f, 0.0f },
    { -1968.89f, -2431.08f, 67.898f, 0.0f },
    { -1962.73f, -2431.27f, 67.2818f, 0.0f },
    { -1961.02f, -2413.67f, 68.5201f, 0.0f },
    { -1962.63f, -2419.23f, 68.2877f, 0.0f },
    { -1954.19f, -2408.76f, 68.4403f, 0.0f },
    { -1953.64f, -2402.56f, 68.4936f, 0.0f },
    { -1956.7f, -2395.52f, 68.4261f, 0.0f },
    { -1962.6f, -2389.32f, 68.1263f, 0.0f },
    { -1961.92f, -2394.32f, 68.3855f, 0.0f },
    { -1974.53f, -2393.77f, 68.7515f, 0.0f },
    { -1967.44f, -2394.01f, 68.4261f, 0.0f },
    { -1981.13f, -2394.35f, 69.4465f, 0.0f },
    { -1986.05f, -2395.71f, 69.9705f, 0.0f },
    { -1990.98f, -2397.83f, 70.2395f, 0.0f },
    { -2008.34f, -2440.57f, 67.0582f, 0.0f },
    { -2011.88f, -2439.44f, 67.9698f, 0.0f },
    { -2014.65f, -2434.91f, 68.3184f, 0.0f },
    { -2018.61f, -2435.17f, 68.4743f, 0.0f },
    { -2022.57f, -2435.51f, 69.2892f, 0.0f },
    { -2027.45f, -2435.43f, 69.602f, 0.0f },
    { -2015.21f, -2417.41f, 70.1609f, 0.0f },
    { -2008.82f, -2419.37f, 69.9932f, 0.0f },
    { -2008.82f, -2426.1f, 69.8704f, 0.0f },
    { -2013.16f, -2423.11f, 70.1221f, 0.0f },
    { -2017.14f, -2427.58f, 70.3475f, 0.0f },
    { -2022.16f, -2427.76f, 70.5097f, 0.0f },
    { -2021.3f, -2423.44f, 70.4219f, 0.0f },
    { -2025.08f, -2419.15f, 70.832f, 0.0f },
    { -2021.26f, -2413.17f, 70.7051f, 0.0f },
    { -2020.63f, -2410.67f, 70.7262f, 0.0f },
    { -2023.63f, -2405.14f, 71.2652f, 0.0f },
    { -2030.02f, -2400.16f, 71.9833f, 0.0f },
    { -2030.28f, -2396.21f, 71.9617f, 0.0f },
    { -2029.97f, -2390.89f, 71.9104f, 0.0f },
    { -2028.22f, -2383.63f, 72.0727f, 0.0f },
    { -2030.42f, -2383.55f, 72.2351f, 0.0f },
    { -2021.73f, -2386.6f, 71.2048f, 0.0f },
    { -2028.09f, -2387.95f, 71.8631f, 0.0f },
    { -2033.45f, -2385.24f, 72.2711f, 0.0f },
    { -2035.06f, -2375.8f, 72.5967f, 0.0f },
    { -2017.14f, -2358.85f, 68.9937f, 0.0f },
    { -1989.93f, -2367.58f, 67.4807f, 0.0f },
    { -1976.86f, -2367.3f, 67.0363f, 0.0f },
    { -1969.88f, -2367.03f, 66.4227f, 0.0f },
    { -1962.88f, -2367.09f, 66.0655f, 0.0f },
    { -1962.88f, -2367.09f, 66.0655f, 0.0f },
    { -1959.14f, -2373.96f, 67.0187f, 0.0f },
    { -1967.66f, -2374.79f, 67.071f, 0.0f },
    { -1988.93f, -2376.36f, 68.3446f, 0.0f },
    { -1982.93f, -2375.78f, 68.4679f, 0.0f },
    { -2005.59f, -2374.14f, 68.0983f, 0.0f },
    { -1999.94f, -2382.01f, 67.7758f, 0.0f },
    { -1994.12f, -2374.01f, 67.2098f, 0.0f }
};

// 55265
class boss_morchok : public CreatureScript
{
public:
    boss_morchok() : CreatureScript("boss_morchok") { }

    struct boss_morchokAI : public BossAI
    {
        boss_morchokAI(Creature* creature) : BossAI(creature, DATA_MORCHOK) { }

        Creature* blackblood;
        GameObject* Innerwall;
        void Reset()
        {
            _Reset();
            instance->SetBossState(BOSS_MORCHOK, NOT_STARTED);
            me->SetObjectScale(1);
            events.SetPhase(PHASE_NORMAL);
            events.ScheduleEvent(EVENT_STOMP, urand(9000, 14000));
            events.ScheduleEvent(EVENT_CRUSH_ARMOR, urand(10000, 15000));
            events.ScheduleEvent(EVENT_RESONATING_CRYSTAL, urand(25000, 35000));
            events.ScheduleEvent(EVENT_PHASE_BLACK_BLOOD, urand(45000, 55000));
            events.ScheduleEvent(IsHeroic() ? EVENT_SUMMON_KOHCROM : EVENT_SUMMON_KOHCROM, 15000, 0);
            events.ScheduleEvent(EVENT_ENRAGE, 447000);
        }

        void EnterCombat(Unit* /*who*/)
        {
            instance->SetBossState(BOSS_MORCHOK, IN_PROGRESS);
            Talk(SAY_AGGRO);
            _EnterCombat();
        }

        void JustDied(Unit* /*killer*/)
        {
            instance->SetBossState(BOSS_MORCHOK, DONE);
            Talk(SAY_DEATH);
            DespawnGameobjects(209596, 100.0f);
        }

        void EnterEvadeMode()
        {
            events.Reset();
            summons.DespawnAll();
            DespawnGameobjects(209596, 100.0f);
            me->GetMotionMaster()->MoveTargetedHome();
            me->SetObjectScale(1);
            _Reset();
            _EnterEvadeMode();
        }

        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_PLAYER_KILL);
        }

        void JustSummoned(Creature* summoned)
        {
            summons.Summon(summoned);

            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
            {
                summoned->AI()->AttackStart(target);
                summoned->AddThreat(target, 250.0f);
                DoZoneInCombat(summoned);
            }

            if (summoned->GetEntry() == NPC_KOHCROM)
            {
                summoned->AI()->AttackStart(me->GetVictim());
                summoned->SetHealth(me->GetHealth());
                summoned->setActive(true);
                summoned->setFaction(14);

                DoZoneInCombat(summoned);
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
            case ACTION_SUMMON:
                DoCast(me, SPELL_CLEAR_DEBUFFS);
                DoCast(me, SPELL_KORCHOM);
                Talk(SAY_PLAYER_KILL);
                break;
            default:
                break;
            }
        }

        void DespawnGameobjects(uint32 entry, float distance)
        {
            std::list<GameObject*> gameobjects;
            GetGameObjectListWithEntryInGrid(gameobjects, me, entry, distance);

            if (gameobjects.empty())
                return;

            for (std::list<GameObject*>::iterator iter = gameobjects.begin(); iter != gameobjects.end(); ++iter)
                (*iter)->RemoveFromWorld();
        }

        void DamageTaken(Unit* /*attacker*/, uint32& damage)
        {
            if (me->HealthBelowPct(80) && me->HealthAbovePct(71))
                me->SetObjectScale(0.7f);
            else if (me->HealthBelowPct(70) && me->HealthAbovePct(61))
                me->SetObjectScale(0.6f);
            else if (me->HealthBelowPct(60) && me->HealthAbovePct(51))
                me->SetObjectScale(0.5f);
            else if (me->HealthBelowPct(50) && me->HealthAbovePct(41))
                me->SetObjectScale(0.4f);
            else if (me->HealthBelowPct(40) && me->HealthAbovePct(31))
                me->SetObjectScale(0.3f);
            else if (me->HealthBelowPct(20))
                DoCast(me, SPELL_FURIOUS);
            else if (me->HealthBelowPct(20))
                DoCastVictim(SPELL_KORCHOM);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (Unit* victim = me->GetVictim())
                if (!me->IsWithinLOSInMap(victim) && events.IsInPhase(PHASE_NORMAL))
                    me->DealDamage(victim, victim->GetHealth());

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_STOMP:
                    if (events.IsInPhase(PHASE_NORMAL))
                        DoCastVictim(SPELL_STOMP);
                    events.ScheduleEvent(EVENT_STOMP, urand(12000, 18000));
                    break;
                case EVENT_CRUSH_ARMOR:
                    if (events.IsInPhase(PHASE_NORMAL))
                        DoCastVictim(SPELL_CRUSH_ARMOR);
                    events.ScheduleEvent(EVENT_CRUSH_ARMOR, urand(12000, 18000));
                    break;
                case EVENT_RESONATING_CRYSTAL:
                    if (events.IsInPhase(PHASE_NORMAL))
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                        {
                            DoCast(target, SPELL_RESONATING_CRYSTAL);
                            Talk(SAY_SUMMON_CRYSTAL);
                        }
                    events.ScheduleEvent(EVENT_RESONATING_CRYSTAL, urand(20000, 25000));
                    break;
                case EVENT_PHASE_BLACK_BLOOD:
                    events.SetPhase(PHASE_BLACK_BLOOD);
                    events.ScheduleEvent(EVENT_EARTHS_VENGEANCE, 100);
                    break;
                case EVENT_EARTHS_VENGEANCE:
                    DoCast(me, SPELL_EARTHS_VENGEANCE_CHANNEL);
                    float x, y, z, x1, y1, x2, y2, x3, y3, x4, y4;
                    x = me->GetPositionX();
                    y = me->GetPositionY();
                    z = me->GetPositionZ() - 3;
                    x1 = x + urand(18, 25);
                    y1 = y + urand(18, 25);
                    x2 = x + urand(18, 25);
                    y2 = y - urand(18, 25);
                    x3 = x - urand(18, 25);
                    y3 = y + urand(18, 25);
                    x4 = x - urand(18, 25);
                    y4 = y - urand(18, 25);
                    //me->SummonCreature(NPC_MINNOR_RESONATING_CRYSTAL, x1, y1, z, 0, TEMPSUMMON_TIMED_DESPAWN, 10000);
                    //me->SummonCreature(NPC_MINNOR_RESONATING_CRYSTAL, x2, y2, z, 0, TEMPSUMMON_TIMED_DESPAWN, 10000);
                    //me->SummonCreature(NPC_MINNOR_RESONATING_CRYSTAL, x3, y3, z, 0, TEMPSUMMON_TIMED_DESPAWN, 10000);
                    //me->SummonCreature(NPC_MINNOR_RESONATING_CRYSTAL, x4, y4, z, 0, TEMPSUMMON_TIMED_DESPAWN, 10000);
                    me->SummonGameObject(209596, -2002.05f, -2433.74f, 68.7619f, 0.0757895f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -2017.05f, -2378.74f, 70.7733f, 0.0757895f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -1967.05f, -2413.74f, 68.8055f, 0.0757895f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -1977.05f, -2373.74f, 67.7071f, 0.0757895f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -2027.05f, -2383.74f, 71.9733f, 0.0757895f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -1992.05f, -2438.74f, 66.9456f, 0.0757895f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -1987.05f, -2433.74f, 68.4344f, 0.0753314f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -2022.05f, -2413.74f, 70.8337f, 0.0753314f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -1982.05f, -2368.74f, 67.4537f, 0.0753314f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -1997.05f, -2438.74f, 66.9817f, 0.0753314f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -1967.05f, -2388.74f, 68.1322f, 0.0753314f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -2022.05f, -2418.74f, 70.6474f, 0.0753314f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -1962.05f, -2398.74f, 68.5796f, 0.0753314f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -1962.05f, -2393.74f, 68.3909f, 0.0753314f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -2022.05f, -2393.74f, 71.3734f, 0.0753008f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -2022.05f, -2398.74f, 71.2904f, 0.0753008f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -2013.92f, -2419.19f, 70.1257f, 5.57749f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -1968.92f, -2384.19f, 68.0035f, 5.57749f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -1988.92f, -2439.19f, 67.1592f, 5.57749f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -1963.92f, -2419.19f, 68.4089f, 5.57749f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -1963.92f, -2404.19f, 68.6589f, 5.57749f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -1998.92f, -2434.19f, 68.5938f, 5.57749f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -1968.92f, -2389.19f, 68.3109f, 5.57749f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -2018.92f, -2394.19f, 71.1232f, 5.57749f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -1998.92f, -2379.19f, 67.9784f, 5.57749f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -1993.92f, -2374.19f, 67.3168f, 5.57749f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -1973.92f, -2399.19f, 68.6708f, 5.57749f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -2018.92f, -2399.19f, 71.1232f, 5.57749f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -1963.92f, -2414.19f, 68.6589f, 5.57749f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -1983.92f, -2434.19f, 68.3592f, 5.57749f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -2018.92f, -2414.19f, 70.4433f, 5.57748f, 0, 0, 0, 0, 0);
                    me->SummonGameObject(209596, -2018.92f, -2429.19f, 70.4409f, 5.57748f, 0, 0, 0, 0, 0);

                    events.ScheduleEvent(EVENT_SUMMON, 5000, 0, PHASE_BLACK_BLOOD);
                    break;
                case EVENT_SUMMON:
                    DoCastAOE(SPELL_SUMMON);
                    events.ScheduleEvent(EVENT_BLACK_BLOOD_OF_THE_EARTH, 100, 0, PHASE_BLACK_BLOOD);
                    break;
                case EVENT_BLACK_BLOOD_OF_THE_EARTH:
                    for (int8 i = 0; i < 105; i++)
                    {
                        blackblood = me->SummonCreature(NPC_BLACK_BLOOD_OF_THE_EARTH, BlackBloodPositions[i], TEMPSUMMON_MANUAL_DESPAWN);
                    }
                    DoCast(me, SPELL_BLACK_BLOOD_OF_THE_EARTH);
                    events.ScheduleEvent(EVENT_CLEANING, 17000, 0, PHASE_BLACK_BLOOD);
                    break;
                case EVENT_CLEANING:
                    DespawnGameobjects(209596, 100.0f);
                    events.ScheduleEvent(EVENT_PHASE_NORMAL, 100, 0, PHASE_BLACK_BLOOD);
                    break;
                case EVENT_PHASE_NORMAL:
                    events.SetPhase(PHASE_NORMAL);
                    events.ScheduleEvent(EVENT_PHASE_BLACK_BLOOD, urand(30000, 50000));
                    break;
                case EVENT_SUMMON_KOHCROM:
                    if (me->GetMap()->IsHeroic())
                        if (me->GetHealthPct() < 90)
                        {
                            DoCastVictim(SPELL_SUMMON_KOHCROM);
                            events.CancelEvent(EVENT_FURIOUS);
                        }
                        else
                            events.ScheduleEvent(IsHeroic() ? EVENT_SUMMON_KOHCROM : EVENT_SUMMON_KOHCROM, 15000, 0);
                    break;
                case EVENT_ENRAGE:
                    me->InterruptNonMeleeSpells(true);
                    DoCast(me, SPELL_ENRAGE);
                    events.ScheduleEvent(EVENT_ENRAGE, 447000);
                    break;
                default:
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<boss_morchokAI>(creature);
    }
};

// 57773
class npc_kohcrom : public CreatureScript
{
public:
    npc_kohcrom() : CreatureScript("npc_kohcrom") { }

    struct npc_kohcromAI : public ScriptedAI
    {
        npc_kohcromAI(Creature* creature) : ScriptedAI(creature)
        {
            _instance = creature->GetInstanceScript();
        }

        uint32 MorchokGUID;
        uint32 Raid10H;
        uint32 Raid25H;

        void EnterCombat(Unit* /*who*/)
        {
            DoZoneInCombat();
            _events.Reset();
            _events.ScheduleEvent(EVENT_STOMP, 14000);
            _events.ScheduleEvent(EVENT_CRUSH_ARMOR, 15000);
            _events.ScheduleEvent(EVENT_VORTEX, 71000);


            _instance->SetData(DATA_KOHCROM_HEALTH, me->GetHealth());
        }

        void DamageTaken(Unit* /*attacker*/, uint32& damage)
        {
            _instance->SetData(DATA_KOHCROM_HEALTH, me->GetHealth() >= damage ? me->GetHealth() - damage : 0);

            if (me->HealthBelowPctDamaged(80, damage))
            {
                me->SetObjectScale(0.7f);
            }
            else if (me->HealthBelowPctDamaged(70, damage))
            {
                me->SetObjectScale(0.6f);
            }
            else if (me->HealthBelowPctDamaged(60, damage))
            {
                me->SetObjectScale(0.5f);
            }
            else if (me->HealthBelowPctDamaged(50, damage))
            {
                me->SetObjectScale(0.4f);
            }
            else if (me->HealthBelowPctDamaged(40, damage))
            {
                me->SetObjectScale(0.3f);
            }
            else if (me->HealthBelowPctDamaged(20, damage))
            {
                DoCast(me, SPELL_FURIOUS);
            }
        }

        void JustDied(Unit* killer)
        {
            _instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            _instance->SetData(DATA_KOHCROM_HEALTH, 0);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (me->GetHealth() > _instance->GetData(DATA_MORCHOK) && _instance->GetData(DATA_MORCHOK) != 0)
                me->SetHealth(_instance->GetData(DATA_MORCHOK));

            _events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_STOMP:
                    DoCastAOE(SPELL_STOMP);
                    _events.ScheduleEvent(EVENT_STOMP, 14000);
                    break;

                case EVENT_CRUSH_ARMOR:
                    DoCastVictim(SPELL_CRUSH_ARMOR);
                    _events.ScheduleEvent(EVENT_CRUSH_ARMOR, 15000);
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }

    private:
        EventMap _events;
        InstanceScript* _instance;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<npc_kohcromAI>(creature);
    }
};

// 55346 15769
class npc_resonating_crystal : public CreatureScript
{
public:
    npc_resonating_crystal() : CreatureScript("npc_resonating_crystal") { }

    struct npc_resonating_crystalAI : public ScriptedAI
    {
        npc_resonating_crystalAI(Creature* creature) : ScriptedAI(creature),
            _instance(creature->GetInstanceScript())
        {
            me->AttackStop();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            me->AddAura(103494, me);
        }

        int32 count;
        void Reset()
        {
            _events.Reset();
            _events.ScheduleEvent(EVENT_RESONATING, 100);
            _events.ScheduleEvent(EVENT_EXPLODE, 500);
            _events.ScheduleEvent(EVENT_ANTI_EXPLODE, 11900);
            _events.ScheduleEvent(EVENT_DESPAWN, 12000);
            count = 0;
        }

        void JustSummoned(Creature* summoned)
        {
            DoCast(me, 103494);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            _events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_RESONATING:
                    DoCast(me, SPELL_RESONATING_CRYSTAL_AURA);
                    _events.ScheduleEvent(EVENT_RESONATING, 100);
                    break;
                case EVENT_EXPLODE:
                {
                    count = 0;
                    Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
                    if (!PlayerList.isEmpty())
                    {
                        for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                        {
                            if (i->GetSource()->IsAlive())
                            {
                                if (me->GetExactDist(i->GetSource()) < 3.0f)
                                {
                                    count++;
                                }
                            }
                        }
                    }

                    if (!PlayerList.isEmpty())
                    {
                        for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                        {
                            if (i->GetSource()->IsAlive())
                            {
                                if (count == 0)
                                {
                                    DoCast(i->GetSource(), SPELL_DANGER);
                                    i->GetSource()->RemoveAurasDueToSpell(SPELL_WARNING);
                                    i->GetSource()->RemoveAurasDueToSpell(SPELL_SAFE);
                                }
                                else if (count == 1)
                                {
                                    DoCast(i->GetSource(), SPELL_DANGER);
                                    i->GetSource()->RemoveAurasDueToSpell(SPELL_WARNING);
                                    i->GetSource()->RemoveAurasDueToSpell(SPELL_SAFE);
                                }
                                else if (count == 2)
                                {
                                    DoCast(i->GetSource(), SPELL_WARNING);
                                    i->GetSource()->RemoveAurasDueToSpell(SPELL_DANGER);
                                    i->GetSource()->RemoveAurasDueToSpell(SPELL_SAFE);
                                }
                                else
                                {
                                    DoCast(i->GetSource(), SPELL_SAFE);
                                    i->GetSource()->RemoveAurasDueToSpell(SPELL_WARNING);
                                    i->GetSource()->RemoveAurasDueToSpell(SPELL_DANGER);
                                    _events.ScheduleEvent(EVENT_DESPAWN, 2000);
                                }
                            }
                        }
                    }
                    _events.ScheduleEvent(EVENT_EXPLODE, 500);
                    break;
                }
                case EVENT_ANTI_EXPLODE:
                {
                    Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
                    if (!PlayerList.isEmpty())
                    {
                        for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                        {
                            if (i->GetSource()->IsAlive())
                            {
                                i->GetSource()->RemoveAurasDueToSpell(SPELL_SAFE);
                                i->GetSource()->RemoveAurasDueToSpell(SPELL_WARNING);
                                i->GetSource()->RemoveAurasDueToSpell(SPELL_DANGER);
                            }
                        }
                    }
                    DoCast(me, SPELL_RESONATING_CRYSTAL_EX);
                    _events.ScheduleEvent(EVENT_ANTI_EXPLODE, 11900);
                    break;
                }
                case EVENT_DESPAWN:
                {
                    Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
                    if (!PlayerList.isEmpty())
                    {
                        for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                        {
                            if (i->GetSource()->IsAlive())
                            {
                                i->GetSource()->RemoveAurasDueToSpell(SPELL_SAFE);
                                i->GetSource()->RemoveAurasDueToSpell(SPELL_WARNING);
                                i->GetSource()->RemoveAurasDueToSpell(SPELL_DANGER);
                            }
                        }
                    }
                    me->DespawnOrUnsummon();
                    _events.ScheduleEvent(EVENT_DESPAWN, 12000);
                    break;
                }
                default:
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }

    private:
        EventMap _events;
        InstanceScript* _instance;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<npc_resonating_crystalAI>(creature);
    }
};

// 15805
class npc_minor_resonating_crystal : public CreatureScript
{
public:
    npc_minor_resonating_crystal() : CreatureScript("npc_minor_resonating_crystal") { }

    struct npc_minor_resonating_crystalAI : public ScriptedAI
    {
        npc_minor_resonating_crystalAI(Creature* creature) : ScriptedAI(creature),
            _instance(creature->GetInstanceScript())
        {
        }

        void Reset()
        {
            _events.Reset();
            _events.ScheduleEvent(EVENT_EARTHS_VENGEANCE_DROP, urand(2000, 4000));
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            _events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_EARTHS_VENGEANCE_DROP:
                    DoCast(me, SPELL_EARTHS_VENGEANCE);
                    break;
                default:
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }

    private:
        EventMap _events;
        InstanceScript* _instance;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<npc_minor_resonating_crystalAI>(creature);
    }
};

// 103414
class spell_morchok_stomp : public SpellScriptLoader
{
public:
    spell_morchok_stomp() : SpellScriptLoader("spell_morchok_stomp") { }

    class spell_morchok_stomp_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_morchok_stomp_SpellScript);

        void HandleOnHit()
        {
            Unit* caster = GetCaster();
            int32 damage;
            int32 count = 1;
            damage = 675000;

            if (caster->GetMap()->IsHeroic())
            {
                if (caster->GetMap()->Is25ManRaid())
                    damage = 2700000;
                else
                    damage = 1350000;
            }
            else
            {
                if (caster->GetMap()->Is25ManRaid())
                    damage = 2000000;
                else
                    damage = 675000;
            }

            Map::PlayerList const &PlayerList = caster->GetMap()->GetPlayers();
            if (!PlayerList.isEmpty())
                for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    if (i->GetSource()->IsAlive())
                    {
                        if (caster->GetExactDist(i->GetSource()) < 26.0f)
                        {
                            count++;
                        }
                    }
            damage = damage / count;
            SetHitDamage(damage);
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_morchok_stomp_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_morchok_stomp_SpellScript();
    }

};

// 103851
class spell_morchok_black_blood : public SpellScriptLoader
{
public:
    spell_morchok_black_blood() : SpellScriptLoader("spell_morchok_black_blood") { }

    class spell_morchok_black_blood_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_morchok_black_blood_SpellScript);

        void HandleOnCast()
        {
            Unit* caster = GetCaster();
            Map::PlayerList const &PlayerList = caster->GetMap()->GetPlayers();
            if (!PlayerList.isEmpty())
                for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    if (i->GetSource()->IsAlive())
                    {
                        if (!caster->IsWithinLOSInMap(i->GetSource()))
                        {
                            i->GetSource()->RemoveAurasDueToSpell(103785); //TODO this just remove aura stacks but i->GetSource() should not receive damage at all
                        }
                    }
        }

        void Register()
        {
            OnCast += SpellCastFn(spell_morchok_black_blood_SpellScript::HandleOnCast);
        }

    };

    SpellScript* GetSpellScript() const
    {
        return new spell_morchok_black_blood_SpellScript();
    }
};

// 55267
class npc_black_blood_of_the_earth : public CreatureScript 
{
public:
    npc_black_blood_of_the_earth() : CreatureScript("npc_black_blood_of_the_earth") { }

    struct npc_black_blood_of_the_earthAI : public ScriptedAI
    {
        npc_black_blood_of_the_earthAI(Creature* creature) : ScriptedAI(creature),
            _instance(creature->GetInstanceScript())
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            me->AddAura(103180, me);
        }

        bool eventblood;

        void Reset()
        {
            eventblood = true;
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            if (eventblood)
            {
                events.ScheduleEvent(EVENT_BLACK_BLOOD, urand(3000, 11000));
                events.ScheduleEvent(EVENT_BLACK_BLOOD_DESPAWN, 17000);
                eventblood = false;
            }

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_BLACK_BLOOD:
                    DoCast(me, AURA_BLACK_BLOOD_OF_THE_EARTH);
                    events.ScheduleEvent(EVENT_BLACK_BLOOD, 3000);
                    break;
                case EVENT_BLACK_BLOOD_DESPAWN:
                    me->DespawnOrUnsummon();
                    break;
                }
            }
        }
    private:
        EventMap events;
        InstanceScript* _instance;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<npc_black_blood_of_the_earthAI>(creature);
    }
};

// ###################### old

class boss_morchok2 : public CreatureScript
{
public:
    boss_morchok2() : CreatureScript("boss_morchok2") { }

    struct boss_morchokAI : public BossAI
    {
        boss_morchokAI(Creature* creature) : BossAI(creature, BOSS_MORCHOK)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();

            me->RemoveAura(SPELL_FURIOUS);
            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_CRUSH_ARMOR, 1500);
            events.ScheduleEvent(EVENT_STOMP, 60000);
            events.ScheduleEvent(EVENT_FURIOUS, 3000);
            events.ScheduleEvent(EVENT_BLACK_BLOOD_OF_THE_EARTH, 340000);
            if (Is25ManRaid())
                events.ScheduleEvent(EVENT_SUMMON_KOHCROM, 3000);
            events.ScheduleEvent(EVENT_SAY, 30000);

            Talk(SAY_AGGRO);
            _EnterCombat();
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CRUSH_ARMOR:
                    DoCastVictim(SPELL_CRUSH_ARMOR);
                    events.ScheduleEvent(EVENT_CRUSH_ARMOR, urand(5000, 15000));
                    break;

                case EVENT_STOMP:
                    DoCast(SPELL_STOMP);
                    Talk(SAY_GROUNT1);
                    events.ScheduleEvent(EVENT_STOMP, urand(60000, 120000));
                    break;

                case EVENT_BLACK_BLOOD_OF_THE_EARTH:
                    DoCast(me, SPELL_BLACK_BLOOD_OF_THE_EARTH);
                    Talk(SAY_GROUNT2);
                    events.ScheduleEvent(EVENT_BLACK_BLOOD_OF_THE_EARTH, urand(120000, 240000));
                    break;

                case EVENT_FURIOUS:
                    if (me->GetHealthPct() < 20)
                    {
                        DoCast(me, SPELL_FURIOUS);
                        events.CancelEvent(EVENT_FURIOUS);
                    }
                    else
                        events.ScheduleEvent(EVENT_FURIOUS, 15000);
                    break;

                case EVENT_SAY:
                    switch (urand(0, 1))
                    {
                    case 0:
                        Talk(SAY_EVENT3);
                        break;
                    case 1:
                        Talk(SAY_EVENT4);
                        break;
                    }
                    break;

                case EVENT_SUMMON_KOHCROM:
                    if (me->GetHealthPct() < 90)
                    {
                        DoCastVictim(SPELL_SUMMON_KOHCROM);
                        events.CancelEvent(EVENT_FURIOUS);
                        Talk(SAY_SPLIT);
                    }
                    else
                        events.ScheduleEvent(EVENT_SUMMON_KOHCROM, 15000);
                    break;
                default:
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void KilledUnit(Unit* /*victim*/)
        {
            Talk(SAY_SLAY);
        }

        void JustDied(Unit* /*killer*/)
        {
            instance->SetBossState(BOSS_MORCHOK, DONE);
            instance->SetBossState(DATA_PORTALS_ON_OFF, DONE);
            Talk(SAY_DEATH);
            _JustDied();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<boss_morchokAI>(creature);
    }
};

class npc_kohcrom2 : public CreatureScript
{
public:
    npc_kohcrom2() : CreatureScript("npc_kohcrom2") { }

    struct npc_kohcromAI : public ScriptedAI
    {
        npc_kohcromAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_CRUSH_ARMOR, 3000);
            events.ScheduleEvent(EVENT_STOMP, 120000);
            events.ScheduleEvent(EVENT_FURIOUS, 3000);
            events.ScheduleEvent(EVENT_BLACK_BLOOD_OF_THE_EARTH, 400000);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CRUSH_ARMOR:
                    DoCastVictim(SPELL_CRUSH_ARMOR);
                    events.ScheduleEvent(EVENT_CRUSH_ARMOR, urand(15000, 30000));
                    break;

                case EVENT_STOMP:
                    DoCast(SPELL_STOMP);
                    events.ScheduleEvent(EVENT_STOMP, urand(120000, 180000));
                    break;

                case EVENT_BLACK_BLOOD_OF_THE_EARTH:
                    DoCast(me, SPELL_BLACK_BLOOD_OF_THE_EARTH);
                    events.ScheduleEvent(EVENT_BLACK_BLOOD_OF_THE_EARTH, urand(240000, 360000));
                    break;

                case EVENT_FURIOUS:
                    if (me->GetHealthPct() < 20)
                    {
                        DoCast(me, SPELL_FURIOUS);
                        events.CancelEvent(EVENT_FURIOUS);
                    }
                    else
                        events.ScheduleEvent(EVENT_FURIOUS, 15000);
                    break;
                default:
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<npc_kohcromAI>(creature);
    }
};

void AddSC_boss_morchok()
{
    new boss_morchok();
    new npc_kohcrom();
    new npc_resonating_crystal();
    new npc_minor_resonating_crystal();
    new spell_morchok_stomp();
    new spell_morchok_black_blood();
    new npc_black_blood_of_the_earth();

    new boss_morchok2();
    new npc_kohcrom2();
}