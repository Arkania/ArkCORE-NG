/*
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
 *
 * This file is NOT free software. Third-party users can NOT redistribute
 * it or modify it. If you find it, you are either hacking something, or very
 * lucky (presuming someone else managed to hack it).
 */
/* ScriptData
SDName: boss_warlord
SD%Complete: ~95%
SDComment:
SDCategory: Boss Warlord
EndScriptData
*/

#include "ScriptPCH.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"
#include "MapManager.h"
#include "Spell.h"
#include "MoveSplineInit.h"
#include "Vehicle.h"
#include "dragon_soul.h"

enum Events
{
    EVENT_FOCUSEF_ANGER = 1,
    EVENT_PSYCHIC_DRAIN,
    EVENT_DISRUPTING_SHADOWS,
    EVENT_SPHERE,
    EVENT_SPREY,
    EVENT_SPREY_ACTIVE,
    EVENT_SPREY_REMOVE,
    // Sphere events
    SPHERE_START,
    SPHERE_UPDATE,
    SPHERE_TARGET,
    // eye
    EVENT_SHADOW_GAZE,
    // scourge
    EVENT_SLUDHE_SPEW,
    EVENT_WILD_FLAIL,
    // Claw
    EVENT_OOZE_SPIT,
    EVENT_TENTACLE_TOSS,
    EVENT_TENTACLE_TOSS_V,
    EVENT_TENTACLE_TOSS_J
};

enum YellAndSay
{
    YELL_AGGRO = 0,  // 26335 sound
    SAY_AGGRO = 1,   // 26335 sound

    YELL_DEATH = 2,  // 26336 sound
    SAY_DEATH = 3,   // 26336 sound

    YELL_INTRO = 4,  // 26337 sound
    SAY_INTRO = 5,   // 26337 sound

    YELL_SLAY = 6,   // 26338, 26339, 26341 sound
    SAY_SLAY = 7,    // 26338, 26339, 26341 sound

    YELL_SPELL_1 = 8,  // 26340 sound
    SAY_SPELL_1 = 9,   // 26340 sound

    YELL_SPELL_2 = 10, // 26342 sound
    SAY_SPELL_2 = 11,  // 26342 sound

    YELL_SPELL_3 = 12, // 26343 sound
    SAY_SPELL_3 = 13,  // 26343 sound

    YELL_SPELL_4 = 14, // 26344 sound
    SAY_SPELL_4 = 15,  // 26344 sound

    YELL_SPELL_5 = 16, // 26345 sound
    SAY_SPELL_5 = 17   // 26345 sound
};

enum BossSpellsAndAuras
{
    SPELL_FOCUSED_ANGER = 104543,
    SPELL_PSYCHIC_DRAIN = 104322,
    SPELL_DISRUPTING_SHADOWS = 103434,
    SPELL_BLACK_BLOOD = 104378,
    SPELL_SPREYED_SPHERE = 103527,
    SPELL_BLACK_BLOOD_ERUPTION = 108799,
    SPELL_DARKNESS = 109413,
    AURA_DIFFUSION = 106836
};

Position const eye[8] =
{
    { -1695.34f, -1940.74f, -221.231f, 0.0f },
    { -1835.62f, -1952.04f, -221.299f, 0.0f },
    { -1791.55f, -1989.15f, -221.338f, 0.0f },
    { -1840.42f, -1894.67f, -221.33f, 0.0f },
    { -1734.26f, -1984.63f, -221.348f, 0.0f },
    { -1803.023f, -1849.987f, -221.258f, 0.0f },
    { -1745.402f, -1845.661f, -221.327f, 0.0f },
    { -1701.324f, -1882.644f, -221.353f, 0.0f }
};

Position const scourge[9] =
{
    { -1859.52f, -1889.739f, -219.88f, 0.0f },
    { -1842.489f, -1881.979f, -222.078f, 0.0f },
    { -1836.64f, -1911.88f, -222.272f, 0.0f },
    { -1810.03f, -1987.75f, -222.272f, 0.0f },
    { -1785.859f, -1977.56f, -223.089f, 0.0f },
    { -1785.089f, -2010.68f, -220.38f, 0.0f },
    { -1702.41f, -1959.18f, -223.013f, 0.0f },
    { -1675.77f, -1936.17f, -220.479f, 0.0f },
    { -1707.439f, -1931.699f, -223.498f, 0.0f }
};

Position const claw[3] =
{
    { -1855.319f, -1911.4f, -221.434f, 0.0f },
    { -1804.329f, -2009.03f, -219.785f, 0.0f },
    { -1682.55f, -1959.719f, -220.005f, 0.0f }
};

Position const sphere[3] =
{
    { -1737.349f, -1903.92f, -226.469f, 0.0f },
    { -1762.994f, -1951.96f, -226.269f, 0.0f },
    { -1797.025f, -1919.392f, -226.209f, 0.0f }
};

Position const ShpereMaw[4] =
{
    { -1819.502f, -1822.149f, -219.186f },
    { -1711.553f, -2011.533f, -219.130f },
    { -1828.275f, -2008.838f, -217.703f },
    { -1775.798f, -1926.559f, -226.353f }
};

// 55308
class boss_warlord_zonozz_55308 : public CreatureScript
{
public:
    boss_warlord_zonozz_55308() : CreatureScript("boss_warlord_zonozz_55308") { }

    struct boss_warlord_zonozz_55308AI : public BossAI
    {
        boss_warlord_zonozz_55308AI(Creature* creature) : BossAI(creature, BOSS_WARLORD)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        bool sprey;

        void Reset()
        {
            events.Reset();
            sprey = false;
            instance->SetData(DATA_PORTALS_ON_OFF, DONE);
            me->RemoveAura(EVENT_FOCUSEF_ANGER);
            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            instance->SetBossState(BOSS_WARLORD, IN_PROGRESS);
            instance->SetData(DATA_PORTALS_ON_OFF, IN_PROGRESS);

            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add

            events.ScheduleEvent(EVENT_FOCUSEF_ANGER, 2000);
            events.ScheduleEvent(EVENT_PSYCHIC_DRAIN, 10000);
            events.ScheduleEvent(EVENT_DISRUPTING_SHADOWS, urand(5000, 15000));
            events.ScheduleEvent(EVENT_SPHERE, urand(15000, 30000));

            Talk(YELL_AGGRO);
            Talk(SAY_AGGRO);
            _EnterCombat();
        }

        void EnterEvadeMode()
        {
            Reset();

            me->GetMotionMaster()->MoveTargetedHome();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            instance->SetBossState(BOSS_WARLORD, FAIL);
            instance->SetData(DATA_PORTALS_ON_OFF, DONE);

            _EnterEvadeMode();
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            if (sprey && me->HasAura(AURA_DIFFUSION))
            {
                sprey = false;

                // Summon Eye
                for (int8 i = 0; i < 7; i++)
                    me->SummonCreature(NPC_EYE_1, eye[i], TEMPSUMMON_TIMED_DESPAWN, 30000);
                DoCast(me, SPELL_DARKNESS);

                if (IsHeroic()) // Heroic 10 and 25
                {
                    // Summon Scourge
                    for (int8 i = 0; i < 8; i++)
                        me->SummonCreature(NPC_SCOURGE_1, scourge[i], TEMPSUMMON_TIMED_DESPAWN, 30000);

                    // Summon Claw
                    for (int8 i = 0; i < 3; i++)
                        me->SummonCreature(NPC_CLAW_1, claw[i], TEMPSUMMON_TIMED_DESPAWN, 30000);
                }

                me->RemoveAura(SPELL_FOCUSED_ANGER);
                DoCast(SPELL_BLACK_BLOOD); // cast black blood
                events.ScheduleEvent(EVENT_SPREY_REMOVE, 30000);
                events.CancelEvent(EVENT_SPHERE);
                events.CancelEvent(EVENT_FOCUSEF_ANGER);
            }

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_FOCUSEF_ANGER:
                    DoCast(me, SPELL_FOCUSED_ANGER);

                    events.ScheduleEvent(EVENT_FOCUSEF_ANGER, urand(5000, 15000));
                    break;

                case EVENT_PSYCHIC_DRAIN:
                    DoCast(SPELL_PSYCHIC_DRAIN);

                    events.ScheduleEvent(EVENT_PSYCHIC_DRAIN, urand(10000, 25000));
                    break;

                case EVENT_DISRUPTING_SHADOWS:
                    SelectTargetList(playerList, urand(1, 3), SELECT_TARGET_RANDOM, 0.0f, true);
                    for (std::list<Unit*>::const_iterator itr = playerList.begin(); itr != playerList.end(); ++itr)
                    {
                        Unit* target = (*itr);
                        DoCast(target, SPELL_DISRUPTING_SHADOWS);
                    }

                    events.ScheduleEvent(EVENT_DISRUPTING_SHADOWS, urand(15000, 30000));
                    break;

                case EVENT_SPHERE:
                    if (!me->FindNearestCreature(NPC_SPHERE, 1000.0f, true))
                    {
                        me->SummonCreature(NPC_SPHERE, sphere[urand(0, 2)], TEMPSUMMON_MANUAL_DESPAWN);
                        sprey = true;
                    }

                    events.ScheduleEvent(EVENT_SPHERE, urand(5000, 15000));
                    break;

                case EVENT_SPREY_REMOVE:
                    me->RemoveAura(AURA_DIFFUSION);
                    events.ScheduleEvent(EVENT_SPHERE, urand(5000, 15000));
                    events.ScheduleEvent(EVENT_FOCUSEF_ANGER, urand(5000, 15000));
                    break;
                default:
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void KilledUnit(Unit* victim)
        {
            Talk(YELL_SLAY);
            Talk(SAY_SLAY);
        }

        void JustReachedHome()
        {
            _JustReachedHome();
            instance->SetBossState(BOSS_WARLORD, FAIL);
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(YELL_DEATH);
            Talk(SAY_DEATH);
            instance->SetBossState(BOSS_WARLORD, DONE);
            instance->SetData(DATA_PORTALS_ON_OFF, DONE);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            Unit * portal = me->FindNearestCreature(NPC_PORTAL_WYRMREST_BASE, 20.0f);

            if (!portal)
                portal = me->SummonCreature(NPC_PORTAL_WYRMREST_BASE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 3, 1.5f, TEMPSUMMON_TIMED_DESPAWN, 5 * MINUTE*IN_MILLISECONDS);
        }
    private:
        std::list<Unit *> playerList;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<boss_warlord_zonozz_55308AI>(creature); // GetInstanceAI
    }
};

// 55334
class npc_sphere : public CreatureScript
{
public:
    npc_sphere() : CreatureScript("npc_sphere") { }

    struct npc_sphereAI : public ScriptedAI
    {
        npc_sphereAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        bool player, boss, maw;

        void Reset()
        {
            events.Reset();
            player = false;
            boss = false;
            maw = false;
            me->SetInCombatWithZone();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(SPHERE_START, 1000);
            events.ScheduleEvent(SPHERE_UPDATE, 2000);
            me->AddAura(AURA_DIFFUSION, me);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            if (Creature* warlord = me->FindNearestCreature(NPC_WARLORD, 1000.0f, true))
            {
                if (warlord->FindNearestCreature(me->GetEntry(), 2.0f, true) && !boss)
                {
                    boss = true;
                    uint32 stack = me->GetAura(AURA_DIFFUSION)->GetStackAmount();

                    if (stack >= 1)
                        warlord->CastSpell(warlord, AURA_DIFFUSION, true);
                    if (stack >= 2 && warlord->HasAura(AURA_DIFFUSION))
                        warlord->GetAura(AURA_DIFFUSION)->SetStackAmount(stack);

                    me->DespawnOrUnsummon(1000);
                }
            }

            if (Creature* cmaw = me->FindNearestCreature(55544, 100.0f, true)) // Maw of Shu'ma 
            {
                if (cmaw->GetDistance(me) >= 40.0f && !maw)
                {
                    maw = true;
                    DoCast(SPELL_BLACK_BLOOD_ERUPTION);

                    me->NearTeleportTo(-1762.994f, -1951.96f, -226.269f, 0.0f, true);
                }
            }

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case SPHERE_START:
                    me->SetSpeed(MOVE_RUN, 0.6f);
                    me->GetMotionMaster()->MoveRandom(20.0f);
                    events.ScheduleEvent(SPHERE_TARGET, urand(5000, 15000));
                    break;

                case SPHERE_TARGET:
                    player = true;
                    break;

                case SPHERE_UPDATE:
                    if (player)
                    {
                        Unit* victim = SelectTarget(SELECT_TARGET_RANDOM);
                        me->GetMotionMaster()->MovePoint(0, victim->GetPositionX(), victim->GetPositionY(), victim->GetPositionZ());
                        me->SetSpeed(MOVE_RUN, 5.0f);
                        if (victim->FindNearestCreature(me->GetEntry(), 10.0f, true))
                        {
                            DoCast(SPELL_SPREYED_SPHERE);

                            events.ScheduleEvent(SPHERE_START, 2000);
                            player = false;
                        }
                    }
                    events.ScheduleEvent(SPHERE_UPDATE, 2000);
                    break;
                }
            }
        }

        void JustDied(Unit* /*pKiller*/)
        {
            me->DespawnOrUnsummon(1);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<npc_sphereAI>(creature);
    }
};

// 57875
class npc_eye_of_gorath : public CreatureScript
{
public:
    npc_eye_of_gorath() : CreatureScript("npc_eye_of_gorath") { }

    enum EyeSpells
    {
        SPELL_SHADOW_GAZE = 109391
    };

    struct npc_eye_of_gorathAI : public ScriptedAI
    {
        npc_eye_of_gorathAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_SHADOW_GAZE, 1000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_SHADOW_GAZE:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                        DoCast(target, SPELL_SHADOW_GAZE, false);
                    events.ScheduleEvent(EVENT_SHADOW_GAZE, 3100);
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<npc_eye_of_gorathAI>(creature);
    }
};

class npc_eye_of_gorath_s : public CreatureScript
{
public:
    npc_eye_of_gorath_s() : CreatureScript("npc_eye_of_gorath_s") { }

    enum EyeSSpells
    {
        SPELL_SHADOW_GAZE_S = 104347
    };

    struct npc_eye_of_gorath_sAI : public ScriptedAI
    {
        npc_eye_of_gorath_sAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        void IsSummonedBy(Unit* summoner)
        {
            DoZoneInCombat();
            me->DespawnOrUnsummon(30000);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_SHADOW_GAZE, 1000);
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_SHADOW_GAZE:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                        DoCast(target, SPELL_SHADOW_GAZE_S);
                    events.ScheduleEvent(EVENT_SHADOW_GAZE, 3100);
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<npc_eye_of_gorath_sAI>(creature);
    }
};

class npc_scourge_of_gorath : public CreatureScript
{
public:
    npc_scourge_of_gorath() : CreatureScript("npc_scourge_of_gorath") { }

    enum ScourgeSpells
    {
        SPELL_SLUDHE_SPEW = 110102,
        SPELL_WILD_FLAIL = 109199
    };

    struct npc_scourge_of_gorathAI : public ScriptedAI
    {
        npc_scourge_of_gorathAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        void Reset()
        {
            events.Reset();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_SLUDHE_SPEW, 5000);
            events.ScheduleEvent(EVENT_WILD_FLAIL, urand(1500, 15000));
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_SLUDHE_SPEW:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                        DoCast(target, SPELL_SLUDHE_SPEW);
                    events.ScheduleEvent(EVENT_SHADOW_GAZE, urand(5000, 15000));
                    break;
                case EVENT_WILD_FLAIL:
                    DoCast(SPELL_WILD_FLAIL);
                    events.ScheduleEvent(EVENT_WILD_FLAIL, urand(2500, 7500));
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<npc_scourge_of_gorathAI>(creature);
    }
};

class npc_scourge_of_gorath_s : public CreatureScript
{
public:
    npc_scourge_of_gorath_s() : CreatureScript("npc_scourge_of_gorath_s") { }

    enum ScourheSSpells
    {
        SPELL_SLUDHE_SPEW_S = 110297,
        SPELL_WILD_FLAIL_S = 109199
    };

    struct npc_scourge_of_gorath_sAI : public ScriptedAI
    {
        npc_scourge_of_gorath_sAI(Creature* creature) : ScriptedAI(creature) {}

        EventMap events;

        void IsSummonedBy(Unit* summoner)
        {
            DoZoneInCombat();
            me->DespawnOrUnsummon(30000);
        }

        void Reset()
        {
            events.Reset();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            if (me->IsSummon())
            {
                me->DespawnOrUnsummon(30000);
                me->SetInCombatWithZone();
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_SLUDHE_SPEW, 5000);
            events.ScheduleEvent(EVENT_WILD_FLAIL, urand(1500, 15000));
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_SLUDHE_SPEW:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                        DoCast(target, SPELL_SLUDHE_SPEW_S);
                    events.ScheduleEvent(EVENT_SHADOW_GAZE, urand(5000, 15000));
                    break;
                case EVENT_WILD_FLAIL:
                    DoCast(SPELL_WILD_FLAIL_S);
                    events.ScheduleEvent(EVENT_WILD_FLAIL, urand(2500, 7500));
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<npc_scourge_of_gorath_sAI>(creature);
    }
};

class npc_claw_of_gorath : public CreatureScript
{
public:
    npc_claw_of_gorath() : CreatureScript("npc_claw_of_gorath") { }

    enum ClawSpells
    {
        SPELL_OOZE_SPIT = 109396,
        SPELL_TENTACLE_TOSS = 109243
    };

    struct npc_claw_of_gorathAI : public ScriptedAI
    {
        npc_claw_of_gorathAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        EventMap events;

        void Reset()
        {
            events.Reset();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
        }

        void PassengerBoarded(Unit* who, int8 seatId, bool apply)
        {
            if (apply)
                events.ScheduleEvent(EVENT_TENTACLE_TOSS, urand(6000, 18000));
            else
            {
                events.ScheduleEvent(EVENT_TENTACLE_TOSS_V, urand(5000, 15000));
                events.CancelEvent(EVENT_TENTACLE_TOSS); // If Logout player
                events.CancelEvent(EVENT_TENTACLE_TOSS_J); // If Logout player
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_OOZE_SPIT, 5000);
            events.ScheduleEvent(EVENT_TENTACLE_TOSS_V, urand(3000, 9000));
        }

        void JustDied(Unit* /*pKiller*/)
        {
            if (Unit* tv = me->GetVehicleKit()->GetPassenger(0))
                tv->ExitVehicle();
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_OOZE_SPIT:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                        DoCast(target, SPELL_OOZE_SPIT);
                    events.ScheduleEvent(EVENT_OOZE_SPIT, urand(5000, 10000));
                    break;
                case EVENT_TENTACLE_TOSS_V:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                        target->EnterVehicle(me, 0);
                    break;
                case EVENT_TENTACLE_TOSS:
                    DoCast(SPELL_TENTACLE_TOSS);
                    events.ScheduleEvent(EVENT_TENTACLE_TOSS_J, 1600);
                    break;
                case EVENT_TENTACLE_TOSS_J:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                    {
                        if (Unit* tv = me->GetVehicleKit()->GetPassenger(0))
                        {
                            if (target = tv)
                            {
                                if (Creature* tentacle = me->FindNearestCreature(NPC_TENTACLE_TOSS, 100.0f))
                                {
                                    tv->ExitVehicle();
                                    tv->GetMotionMaster()->MoveJump(tentacle->GetPositionX(), tentacle->GetPositionY(), tentacle->GetPositionZ(), 50.0f, 10.0f);
                                }
                            }
                            else
                                if (target)
                                {
                                    tv->ExitVehicle();
                                    tv->GetMotionMaster()->MoveJump(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 50.0f, 10.0f);
                                }
                        }
                    }
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<npc_claw_of_gorathAI>(creature);
    }
};

class npc_claw_of_gorath_s : public CreatureScript
{
public:
    npc_claw_of_gorath_s() : CreatureScript("npc_claw_of_gorath_s") { }

    enum ClawSSpells
    {
        SPELL_OOZE_SPIT_S = 109396
    };

    struct npc_claw_of_gorath_sAI : public ScriptedAI
    {
        npc_claw_of_gorath_sAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        void IsSummonedBy(Unit* summoner)
        {
            DoZoneInCombat();
            me->DespawnOrUnsummon(30000);
        }

        void Reset()
        {
            events.Reset();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_OOZE_SPIT, 5000);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_OOZE_SPIT:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                        DoCast(target, SPELL_OOZE_SPIT_S);
                    events.ScheduleEvent(EVENT_OOZE_SPIT, urand(5000, 10000));
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<npc_claw_of_gorath_sAI>(creature);
    }
};

void AddSC_boss_warlord()
{
    new boss_warlord_zonozz_55308();
    new npc_sphere();
    new npc_eye_of_gorath();
    //new npc_scourge_of_gorath();
    //new npc_claw_of_gorath();
    //new npc_eye_of_gorath_s();
    //new npc_scourge_of_gorath_s();
    //new npc_claw_of_gorath_s();
}
