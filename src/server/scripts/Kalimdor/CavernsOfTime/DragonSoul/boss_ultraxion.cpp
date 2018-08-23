/*
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
 *
 * This file is NOT free software. Third-party users can NOT redistribute
 * it or modify it. If you find it, you are either hacking something, or very
 * lucky (presuming someone else managed to hack it).
 */

/* ScriptData
SDName: boss_ultraxion
SD%Complete: 95%
SDComment:Base Script By Alex And Fixes By Me
SDCategory: Boss Ultraxion
EndScriptData
*/


#include "ScriptPCH.h"
#include "Containers.h"
#include "dragon_soul.h" 

#define TRALL_MENU "We are ready!"
#define ASPECT_MENU_1 "Last Defender of Azeroth"
#define ASPECT_MENU_2 "Revolution Time"
#define ASPECT_MENU_3 "The essence nova"
#define ASPECT_MENU_4 "The gift of life"
#define ASPECT_MENU_5 "magical power"


#define H_TARGETS_10 1
#define H_TARGETS_25 3
#define H_TARGETS_10_HEROIC 2
#define H_TARGETS_25_HEROIC 5

#define F_TARGETS_10 2
#define F_TARGETS_25 3
#define F_TARGETS_10_HEROIC 2
#define F_TARGETS_25_HEROIC 6



enum ScriptedTexts
{
    SAY_AGGRO = 3,
    SAY_BERSERK = 4,
    SAY_DEATH = 11,
    SAY_INTRO_1 = 1,
    SAY_INTRO_2 = 2,
    SAY_KILL = 8,
    SAY_TWILIGHT = 6,
    SAY_UNSTABLE = 7,
};

enum Spells
{
    SPELL_UNSTABLE_MONSTROSITY_1 = 106372, // 6 secs
    SPELL_UNSTABLE_MONSTROSITY_2 = 106376, // 5 secs
    SPELL_UNSTABLE_MONSTROSITY_3 = 106377, // 4 secs
    SPELL_UNSTABLE_MONSTROSITY_4 = 106378, // 3 secs
    SPELL_UNSTABLE_MONSTROSITY_5 = 106379, // 2 secs
    SPELL_UNSTABLE_MONSTROSITY_6 = 106380, // 1 secs
    SPELL_TWILIGHT_INSTABILITY_AOE_1 = 109176,
    SPELL_TWILIGHT_INSTABILITY_AOE_2 = 106374,
    SPELL_TWILIGHT_INSTABILITY_DMG = 106375,
    SPELL_UNSTABLE_MONSTROSITY_DUMMY_1 = 106390, // prevents from casting those auras for 4 secs
    SPELL_UNSTABLE_MONSTROSITY_DUMMY_2 = 106381, // ? 8/6 secs in normal/heroic

    SPELL_LIGHT = 109405, // Lightning Cosmetic

    SPELL_TWILIGHT_SHIFT_AOE = 106369,
    SPELL_TWILIGHT_SHIFT = 106368,
    SPELL_HEROIC_WILL_AOE = 105554,
    SPELL_HEROIC_WILL = 106108,
    SPELL_FADED_INTO_TWILIGHT = 105927,
    SPELL_ULTRAXION_NORMAL_REALM_COSMETIC = 105929,

    SPELL_HOUR_OF_TWILIGHT = 106371,
    SPELL_HOUR_OF_TWILIGHT_DMG = 103327, // dmg + forse cast 109231, force cast 106370
    SPELL_HOUR_OF_TWILIGHT_1 = 106174, // remove heroic will
    SPELL_HOUR_OF_TWILIGHT_2 = 106370, // from player, force cast achievement

    SPELL_LOOMING_DARKNESS_DUMMY = 106498,
    SPELL_LOOMING_DARKNESS_DMG = 109231,

    SPELL_FADING_LIGHT_1 = 105925, // from boss to player, triggered by hour of twilight, tank only
    SPELL_FADING_LIGHT_KILL = 105926, // kill player
    SPELL_FADING_LIGHT_AOE_1 = 109075, // from boss, triggered by 105925, dps
    SPELL_FADING_LIGHT_DUMMY = 109200, // ?

    SPELL_TWILIGHT_BURST = 106415,
    SPELL_TWILIGHT_ERUPTION = 106388,

    SPELL_LAST_DEFENDER_OF_AZEROTH = 106182, // scale + force cast 110327
    SPELL_LAST_DEFENDER_OF_AZEROTH_DUMMY = 110327,
    SPELL_LAST_DEFENDER_OF_AZEROTH_SCRIPT = 106218, // ?
    SPELL_LAST_DEFENDER_OF_AZEROTH_DRUID = 106224,
    SPELL_LAST_DEFENDER_OF_AZEROTH_PALADIN = 106226,
    SPELL_LAST_DEFENDER_OF_AZEROTH_DK = 106227,
    SPELL_LAST_DEFENDER_OF_AZEROTH_WARRIOR = 106080,

    SPELL_GIFT_OF_LIVE_AURA = 105896,
    SPELL_GIFT_OF_LIVE_1 = 106042,
    SPELL_GIFT_OF_LIVE_SUMMON_1 = 106044,
    SPELL_GIFT_OF_LIVE_2 = 109345, // triggered by 106042 in 25 ppl
    SPELL_GIFT_OF_LIVE_SUMMON_2 = 109440,

    SPELL_ESSENCE_OF_DREAMS_AURA = 105900,
    SPELL_ESSENCE_OF_DREAMS_HEAL = 105996,
    SPELL_ESSENCE_OF_DREAMS_1 = 106049,
    SPELL_ESSENCE_OF_DREAMS_SUMMON_1 = 106047,
    SPELL_ESSENCE_OF_DREAMS_2 = 109344, // triggered by 106049 in 25 ppl
    SPELL_ESSENCE_OF_DREAMS_SUMMON_2 = 109342,

    SPELL_SOURCE_OF_MAGIC_AURA = 105903,
    SPELL_SOURCE_OF_MAGIC_1 = 106050,
    SPELL_SOURCE_OF_MAGIC_SUMMON_1 = 106048,
    SPELL_SOURCE_OF_MAGIC_2 = 109347, // triggered by 106050 in 25 ppl
    SPELL_SOURCE_OF_MAGIC_SUMMON_2 = 109346,

    SPELL_TIMELOOP = 105984,
    SPELL_TIMELOOP_HEAL = 105992,

    SPELL_ULTRAXION_ACHIEVEMENT_AURA = 109188,
    SPELL_ULTRAXION_AHCIEVEMENT_FAILED = 109194,

    SPELL_WARD_OF_MAGIC = 108162,
    SPELL_WARD_OF_TIME = 108160,
    SPELL_WARD_OF_DREAMS = 108164,
    SPELL_WARD_OF_EARTH = 108161,
    SPELL_WARD_OF_LIFE = 108163,
};

enum Events
{
    EVENT_CHARGING_UP = 1,
    EVENT_YSERA_TALK = 2,
    EVENT_MOVE = 3,
    EVENT_LIGHT = 4,
    EVENT_TALK_1 = 5,
    EVENT_UNSTABLE_MONSTROSITY = 6,
    EVENT_HOUR_OF_TWILIGHT = 7,
    EVENT_CHECK_TARGET = 8,
    EVENT_THRALL = 9,
    EVENT_ALEXTRASZA = 10,
    EVENT_YSERA = 11,
    EVENT_KALECGOS = 12,
    EVENT_NOZDORMU = 13,
    EVENT_END_TALK = 14,
};

enum Adds
{
    NPC_ULTRAXION_GAUNTLET = 56305,
    GO_GIFT_OF_LIFE = 209873,
    GO_ESSENCE_OF_DREAMS = 209874,
    GO_SOURCE_OF_MAGIC = 209875,
};

enum Actions
{
    ACTION_TWILIGHT_ERUPTION = 1,
};

// 55294  (spawned from script 56259)
class boss_ultraxion : public CreatureScript
{
public:
    boss_ultraxion() : CreatureScript("boss_ultraxion") {}

    struct boss_ultraxionAI : public BossAI
    {
        boss_ultraxionAI(Creature* pCreature) : BossAI(pCreature, DATA_ULTRAXION)
        {
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_STUN, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FEAR, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_ROOT, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FREEZE, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_POLYMORPH, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_HORROR, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_SAPPED, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_CHARM, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_DISORIENTED, true);
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_CONFUSE, true);
            me->setActive(true);
            me->SetReactState(REACT_DEFENSIVE);
            unstableCount = 0;
        }

        void InitializeAI()
        {
            if (!instance || static_cast<InstanceMap*>(me->GetMap())->GetScriptId() != sObjectMgr->GetScriptId(DSScriptName))
                me->IsAIEnabled = false;
            else if (!me->IsDead())
                Reset();
        }

        void Reset()
        {
            _Reset();
            events.Reset();
            me->GetMotionMaster()->MovePoint(4659700, -1699.160f, -2388.110f, 341.540f);
            me->SetSpeed(MOVE_FLIGHT, 2.5f);
            events.ScheduleEvent(EVENT_MOVE, 15000);
            me->SetPhaseMask(17, true);
            me->SetCanFly(true);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);

            RemoveEncounterAuras();
            DeleteGameObjects(GO_GIFT_OF_LIFE);
            DeleteGameObjects(GO_ESSENCE_OF_DREAMS);
            DeleteGameObjects(GO_SOURCE_OF_MAGIC);

            me->setActive(true);

            unstableCount = 0;
        }

        void AttackStart(Unit* victim)
        {
            if (!victim)
                return;

            if (me->Attack(victim, true))
                DoStartNoMovement(victim);
        }

        void IsSummonedBy(Unit* /*owner*/)
        {
            me->SetVisible(false);

            unstableCount = 0;
            phase = 1;

            RemoveEncounterAuras();
            DeleteGameObjects(GO_GIFT_OF_LIFE);
            DeleteGameObjects(GO_ESSENCE_OF_DREAMS);
            DeleteGameObjects(GO_SOURCE_OF_MAGIC);

            events.ScheduleEvent(EVENT_CHARGING_UP, 1000);
        }

        void SetFly(bool command = false)
        {
            if (command)
            {
                me->HandleEmoteCommand(EMOTE_ONESHOT_FLY_SIT_GROUND_UP);
                me->SetCanFly(true);
            }
            else
            {
                me->SetCanFly(false);
            }
        }

        void EnterCombat(Unit* who)
        {
            Talk(SAY_AGGRO);

            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_ULTRAXION_ACHIEVEMENT_AURA);
            RemoveEncounterAuras();
            DeleteGameObjects(GO_GIFT_OF_LIFE);
            DeleteGameObjects(GO_ESSENCE_OF_DREAMS);
            DeleteGameObjects(GO_SOURCE_OF_MAGIC);

            unstableCount = 0;
            phase = 0;

            DoCastAOE(SPELL_TWILIGHT_SHIFT_AOE, true);
            DoCastAOE(SPELL_HEROIC_WILL_AOE, true);
            DoCastAOE(SPELL_LAST_DEFENDER_OF_AZEROTH_DUMMY, true);

            events.ScheduleEvent(EVENT_UNSTABLE_MONSTROSITY, 1000);
            events.ScheduleEvent(EVENT_HOUR_OF_TWILIGHT, 45000);
            events.ScheduleEvent(EVENT_CHECK_TARGET, 5000);
            events.ScheduleEvent(EVENT_LIGHT, 4000);
            events.ScheduleEvent(EVENT_THRALL, 5000);
            events.ScheduleEvent(EVENT_ALEXTRASZA, 80000);
            events.ScheduleEvent(EVENT_YSERA, 155000);
            events.ScheduleEvent(EVENT_KALECGOS, 215000);
            events.ScheduleEvent(EVENT_NOZDORMU, 5 * MINUTE * IN_MILLISECONDS);

            DoZoneInCombat();
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
            instance->SetBossState(DATA_ULTRAXION, IN_PROGRESS);
        }

        bool AllowAchieve()
        {
            Map::PlayerList const &playerList = instance->instance->GetPlayers();
            if (!playerList.isEmpty())
            {
                for (Map::PlayerList::const_iterator itr = playerList.begin(); itr != playerList.end(); ++itr)
                    if (Player* pPlayer = itr->GetSource())
                    {
                        if (Aura const* aur = pPlayer->GetAura(SPELL_ULTRAXION_ACHIEVEMENT_AURA))
                            if (aur->GetStackAmount() > 1)
                                return false;
                    }
            }
            return true;
        }

        void DoAction(int32 action)
        {
            if (action == ACTION_TWILIGHT_ERUPTION)
            {
                unstableCount = 8;
                events.RescheduleEvent(EVENT_UNSTABLE_MONSTROSITY, 1000);
            }
        }

        void JustDied(Unit* killer)
        {
            _JustDied();

            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);

            Talk(SAY_DEATH);

            RemoveEncounterAuras();
            DeleteGameObjects(GO_GIFT_OF_LIFE);
            DeleteGameObjects(GO_ESSENCE_OF_DREAMS);
            DeleteGameObjects(GO_SOURCE_OF_MAGIC);
            killer->SummonGameObject(RAID_MODE(GO_ULTRAXION_LOOT_10N, GO_ULTRAXION_LOOT_25N, GO_ULTRAXION_LOOT_10H, GO_ULTRAXION_LOOT_25H), -1753.63f, -2370.01f, 340.845f, 0.0f, 0.0f, 0.0f, -0.66913f, 0.743145f, 100000);

            if (Creature* pThrall = me->FindNearestCreature(NPC_THRALL_1, 300.0f))
            {
                pThrall->InterruptNonMeleeSpells(true);
                pThrall->RemoveAllAuras();
                pThrall->AI()->DoAction(1); // ACTION_ULTRAXION_WIN
            }
            if (Creature* pYsera = me->FindNearestCreature(NPC_YSERA_THE_AWAKENED, 300.0f))
            {
                pYsera->InterruptNonMeleeSpells(true);
                pYsera->RemoveAllAuras();
            }
            if (Creature* pAlextrasza = me->FindNearestCreature(NPC_ALEXTRASZA_THE_LIFE_BINDER, 300.0f))
            {
                pAlextrasza->InterruptNonMeleeSpells(true);
                pAlextrasza->RemoveAllAuras();
            }
            if (Creature* pNozdormu = me->FindNearestCreature(NPC_NOZDORMU_THE_TIMELESS_ONE, 300.0f))
            {
                pNozdormu->InterruptNonMeleeSpells(true);
                pNozdormu->RemoveAllAuras();
            }
            if (Creature* pKalecgos = me->FindNearestCreature(NPC_KALECGOS, 300.0f))
            {
                pKalecgos->InterruptNonMeleeSpells(true);
                pKalecgos->RemoveAllAuras();
            }

            switch (GetDifficulty())
            {
            case RAID_DIFFICULTY_10MAN_NORMAL:
                instance->DoRespawnGameObject(instance->GetData64(DATA_LESSER_CACHE_10N), DAY);
                break;
            case RAID_DIFFICULTY_25MAN_NORMAL:
                instance->DoRespawnGameObject(instance->GetData64(DATA_LESSER_CACHE_25N), DAY);
                break;
            case RAID_DIFFICULTY_10MAN_HEROIC:
                instance->DoRespawnGameObject(instance->GetData64(DATA_LESSER_CACHE_10H), DAY);
                break;
            case RAID_DIFFICULTY_25MAN_HEROIC:
                instance->DoRespawnGameObject(instance->GetData64(DATA_LESSER_CACHE_25H), DAY);
                break;
            }

            Unit * portal = me->FindNearestCreature(NPC_PORTAL_WYRMREST_BASE, 20.0f);

            if (!portal)
                portal = me->SummonCreature(NPC_PORTAL_WYRMREST_BASE, me->GetPositionX(), me->GetPositionY() + 2, me->GetPositionZ() + 3, 1.5f, TEMPSUMMON_TIMED_DESPAWN, 5 * MINUTE*IN_MILLISECONDS);


            Unit * secondportal = me->FindNearestCreature(NPC_PORTAL_ETERNITY, 20.0f);

            if (!secondportal)
                portal = me->SummonCreature(NPC_PORTAL_ETERNITY, me->GetPositionX(), me->GetPositionY() - 2, me->GetPositionZ() + 3, 1.5f, TEMPSUMMON_TIMED_DESPAWN, 5 * MINUTE*IN_MILLISECONDS);

            me->DespawnOrUnsummon(3000);
        }

        void KilledUnit(Unit* victim)
        {
            if (victim && victim->GetTypeId() == TYPEID_PLAYER)
                Talk(SAY_KILL);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() && !phase)
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHARGING_UP:
                    if (Creature* pThrall = me->FindNearestCreature(NPC_THRALL_1, 300.0f))
                        pThrall->CastSpell(pThrall, SPELL_WARD_OF_EARTH);
                    if (Creature* pYsera = me->FindNearestCreature(NPC_YSERA_THE_AWAKENED, 300.0f))
                        pYsera->CastSpell(pYsera, SPELL_WARD_OF_DREAMS);
                    if (Creature* pAlextrasza = me->FindNearestCreature(NPC_ALEXTRASZA_THE_LIFE_BINDER, 300.0f))
                        pAlextrasza->CastSpell(pAlextrasza, SPELL_WARD_OF_LIFE);
                    if (Creature* pNozdormu = me->FindNearestCreature(NPC_NOZDORMU_THE_TIMELESS_ONE, 300.0f))
                        pNozdormu->CastSpell(pNozdormu, SPELL_WARD_OF_TIME);
                    if (Creature* pKalecgos = me->FindNearestCreature(NPC_KALECGOS, 300.0f))
                        pKalecgos->CastSpell(pKalecgos, SPELL_WARD_OF_MAGIC);
                    events.ScheduleEvent(EVENT_YSERA_TALK, 5000);
                    break;
                case EVENT_YSERA_TALK:
                    if (Creature* pYsera = me->FindNearestCreature(NPC_YSERA_THE_AWAKENED, 300.0f))
                        pYsera->AI()->Talk(0); // SAY_PRE_ULTRAXION
                    events.ScheduleEvent(EVENT_MOVE, 7000);
                    break;
                case EVENT_MOVE:
                {
                    me->SetVisible(true);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1 | UNIT_FLAG_NOT_SELECTABLE);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                    me->SetSpeed(MOVE_FLIGHT, 1.0f);
                    Talk(SAY_INTRO_1);
                    events.ScheduleEvent(EVENT_TALK_1, 13000);
                    break;
                }
                case EVENT_TALK_1:
                    Talk(SAY_INTRO_2);
                    events.ScheduleEvent(EVENT_END_TALK, 10000);
                    break;
                case EVENT_END_TALK:
                    phase = 0;
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    break;
                case EVENT_CHECK_TARGET:
                    if (!me->IsWithinMeleeRange(me->GetVictim()))
                        DoCastAOE(SPELL_TWILIGHT_BURST);
                    events.ScheduleEvent(EVENT_CHECK_TARGET, 5000);
                    break;
                case EVENT_LIGHT:
                    if (!me->IsWithinMeleeRange(me->GetVictim()))
                        DoCastAOE(SPELL_LIGHT);
                    events.ScheduleEvent(EVENT_LIGHT, 4000);
                    break;
                case EVENT_THRALL:
                    if (Creature* pThrall = me->FindNearestCreature(NPC_THRALL_1, 300.0f))
                    {
                        pThrall->AI()->Talk(0); // SAY_ULTRAXION
                        pThrall->CastSpell(pThrall, SPELL_LAST_DEFENDER_OF_AZEROTH, true);
                    }
                    break;
                case EVENT_ALEXTRASZA:
                    if (Creature* pAlextrasza = me->FindNearestCreature(NPC_ALEXTRASZA_THE_LIFE_BINDER, 300.0f))
                    {
                        pAlextrasza->AI()->Talk(1); // SAY_ULTRAXION
                        pAlextrasza->CastSpell(pAlextrasza, SPELL_GIFT_OF_LIVE_1, true);
                    }
                    break;
                case EVENT_YSERA:
                    if (Creature* pYsera = me->FindNearestCreature(NPC_YSERA_THE_AWAKENED, 300.0f))
                    {
                        pYsera->AI()->Talk(1); // SAY_ULTRAXION
                        pYsera->CastSpell(pYsera, SPELL_ESSENCE_OF_DREAMS_1, true);
                    }
                    break;
                case EVENT_KALECGOS:
                    if (Creature* pKalecgos = me->FindNearestCreature(NPC_KALECGOS, 300.0f))
                    {
                        pKalecgos->AI()->Talk(0); // SAY_ULTRAXION
                        pKalecgos->CastSpell(pKalecgos, SPELL_SOURCE_OF_MAGIC_1, true);
                    }
                    break;
                case EVENT_NOZDORMU:
                    if (Creature* pNozdormu = me->FindNearestCreature(NPC_NOZDORMU_THE_TIMELESS_ONE, 300.0f))
                    {
                        pNozdormu->AI()->Talk(0); // SAY_ULTRAXION
                        pNozdormu->CastSpell(pNozdormu, SPELL_TIMELOOP, true);
                    }
                    break;
                case EVENT_UNSTABLE_MONSTROSITY:
                    unstableCount++;
                    switch (unstableCount)
                    {
                    case 1:
                        DoCast(me, SPELL_UNSTABLE_MONSTROSITY_1, true);
                        break;
                    case 2:
                        me->RemoveAura(SPELL_UNSTABLE_MONSTROSITY_1);
                        DoCast(me, SPELL_UNSTABLE_MONSTROSITY_2, true);
                        break;
                    case 3:
                        me->RemoveAura(SPELL_UNSTABLE_MONSTROSITY_2);
                        DoCast(me, SPELL_UNSTABLE_MONSTROSITY_3, true);
                        break;
                    case 4:
                        Talk(SAY_UNSTABLE);
                        me->RemoveAura(SPELL_UNSTABLE_MONSTROSITY_3);
                        DoCast(me, SPELL_UNSTABLE_MONSTROSITY_4, true);
                        break;
                    case 5:
                        me->RemoveAura(SPELL_UNSTABLE_MONSTROSITY_4);
                        DoCast(me, SPELL_UNSTABLE_MONSTROSITY_5, true);
                        break;
                    case 6:
                        me->RemoveAura(SPELL_UNSTABLE_MONSTROSITY_5);
                        DoCast(me, SPELL_UNSTABLE_MONSTROSITY_6, true);
                        break;
                    case 7:
                        me->RemoveAura(SPELL_UNSTABLE_MONSTROSITY_6);
                        me->RemoveAura(SPELL_UNSTABLE_MONSTROSITY_5);
                        me->RemoveAura(SPELL_UNSTABLE_MONSTROSITY_4);
                        me->RemoveAura(SPELL_UNSTABLE_MONSTROSITY_3);
                        me->RemoveAura(SPELL_UNSTABLE_MONSTROSITY_2);
                        me->RemoveAura(SPELL_UNSTABLE_MONSTROSITY_1);
                        break;
                    default:
                        break;
                    }
                    if (unstableCount >= 8)
                    {
                        Talk(SAY_BERSERK);
                        DoCast(me, SPELL_TWILIGHT_ERUPTION);
                    }
                    else
                        events.ScheduleEvent(EVENT_UNSTABLE_MONSTROSITY, MINUTE * IN_MILLISECONDS);
                    break;
                case EVENT_HOUR_OF_TWILIGHT:
                    Talk(SAY_TWILIGHT);
                    DoCast(SPELL_HOUR_OF_TWILIGHT);
                    events.ScheduleEvent(EVENT_HOUR_OF_TWILIGHT, 45000);
                    break;
                default:
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }

    private:

        uint8 unstableCount;
        uint8 phase;

        void DespawnCreatures(uint32 entry)
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, entry, 1000.0f);

            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->DespawnOrUnsummon();
        }

        void DeleteGameObjects(uint32 entry)
        {
            std::list<GameObject*> gameobjects;
            me->GetGameObjectListWithEntryInGrid(gameobjects, entry, 300.0f);
            if (!gameobjects.empty())
                for (std::list<GameObject*>::iterator itr = gameobjects.begin(); itr != gameobjects.end(); ++itr)
                    (*itr)->Delete();
        }

        void RemoveEncounterAuras()
        {
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_SHIFT);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_HEROIC_WILL_AOE);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_GIFT_OF_LIVE_AURA);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_ESSENCE_OF_DREAMS_AURA);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_SOURCE_OF_MAGIC_AURA);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TIMELOOP);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_LAST_DEFENDER_OF_AZEROTH_DK);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_LAST_DEFENDER_OF_AZEROTH_PALADIN);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_LAST_DEFENDER_OF_AZEROTH_DRUID);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_LAST_DEFENDER_OF_AZEROTH_WARRIOR);
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return GetDragonSoulAI<boss_ultraxionAI>(pCreature);
    }

};

// 56667
class npc_trall_vs_ultraxion : public CreatureScript
{
public:
    npc_trall_vs_ultraxion() : CreatureScript("npc_trall_vs_ultraxion") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (InstanceScript* instance = creature->GetInstanceScript())
        {
            if (instance->GetBossState(DATA_TRALL_VS_ULTRAXION) == IN_PROGRESS && instance->GetBossState(BOSS_WARLORD) == DONE && instance->GetBossState(BOSS_UNSLEEPING) == DONE && instance->GetBossState(BOSS_HAGARA) == DONE)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TRALL_MENU, GOSSIP_SENDER_MAIN, 10);
            }
            if (instance->GetBossState(DATA_TRALL_VS_ULTRAXION) == DONE)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, ASPECT_MENU_1, GOSSIP_SENDER_MAIN, 11);
            }
        }

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 uiAction)
    {
        if (sender == GOSSIP_SENDER_MAIN)
        {
            player->PlayerTalkClass->ClearMenus();
            switch (uiAction)
            {
            case 10:
                player->CLOSE_GOSSIP_MENU();
                creature->SummonCreature(NPC_ULTRAXION, -1616.576f, -2369.113f, 311.776f, 3.33f, TEMPSUMMON_CORPSE_DESPAWN, 1000000);
                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                break;
            case 11:
                player->CLOSE_GOSSIP_MENU();
                player->AddAura(LAST_DEFENDER_OF_AZEROTH, player);
                player->RemoveAurasDueToSpell(TIMELOOP);
                player->RemoveAurasDueToSpell(SOURCE_OF_MAGIC);
                player->RemoveAurasDueToSpell(ESSENCE_OF_DREAMS);
                player->RemoveAurasDueToSpell(GIFT_OF_LIFE);
                break;
            default:
                break;
            }
        }
        return true;
    }
};

// 56666
class npc_nozdormu : public CreatureScript
{
public:
    npc_nozdormu() : CreatureScript("npc_nozdormu") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (InstanceScript* instance = creature->GetInstanceScript())
        {
            if (instance->GetBossState(DATA_TRALL_VS_ULTRAXION) == DONE)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, ASPECT_MENU_2, GOSSIP_SENDER_MAIN, 20);
            }
        }

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 uiAction)
    {
        if (sender == GOSSIP_SENDER_MAIN)
        {
            player->PlayerTalkClass->ClearMenus();
            switch (uiAction)
            {
            case 20:
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, TIMELOOP);
                player->RemoveAurasDueToSpell(LAST_DEFENDER_OF_AZEROTH);
                player->RemoveAurasDueToSpell(SOURCE_OF_MAGIC);
                player->RemoveAurasDueToSpell(ESSENCE_OF_DREAMS);
                player->RemoveAurasDueToSpell(GIFT_OF_LIFE);
                break;
            default:
                break;
            }
        }
        return true;
    }
};

// 56665
class npc_ysera : public CreatureScript
{
public:
    npc_ysera() : CreatureScript("npc_ysera") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (InstanceScript* instance = creature->GetInstanceScript())
        {
            if (instance->GetBossState(DATA_TRALL_VS_ULTRAXION) == DONE)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, ASPECT_MENU_3, GOSSIP_SENDER_MAIN, 30);
            }
        }

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 uiAction)
    {
        if (sender == GOSSIP_SENDER_MAIN)
        {
            player->PlayerTalkClass->ClearMenus();
            switch (uiAction)
            {
            case 30:
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, ESSENCE_OF_DREAMS);
                player->RemoveAurasDueToSpell(LAST_DEFENDER_OF_AZEROTH);
                player->RemoveAurasDueToSpell(SOURCE_OF_MAGIC);
                player->RemoveAurasDueToSpell(TIMELOOP);
                player->RemoveAurasDueToSpell(GIFT_OF_LIFE);
                break;
            default:
                break;
            }
        }
        return true;
    }
};

// 56630
class npc_alexstrasza : public CreatureScript
{
public:
    npc_alexstrasza() : CreatureScript("npc_alexstrasza") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (InstanceScript* instance = creature->GetInstanceScript())
        {
            if (instance->GetBossState(DATA_TRALL_VS_ULTRAXION) == DONE)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, ASPECT_MENU_4, GOSSIP_SENDER_MAIN, 40);
            }
        }

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 uiAction)
    {
        if (sender == GOSSIP_SENDER_MAIN)
        {
            player->PlayerTalkClass->ClearMenus();
            switch (uiAction)
            {
            case 40:
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, GIFT_OF_LIFE);
                player->RemoveAurasDueToSpell(LAST_DEFENDER_OF_AZEROTH);
                player->RemoveAurasDueToSpell(SOURCE_OF_MAGIC);
                player->RemoveAurasDueToSpell(TIMELOOP);
                player->RemoveAurasDueToSpell(ESSENCE_OF_DREAMS);
                break;
            default:
                break;
            }
        }
        return true;
    }
};

// 56664
class npc_aspect_of_magic : public CreatureScript
{
public:
    npc_aspect_of_magic() : CreatureScript("npc_aspect_of_magic") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (InstanceScript* instance = creature->GetInstanceScript())
        {
            if (instance->GetBossState(DATA_TRALL_VS_ULTRAXION) == DONE)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, ASPECT_MENU_5, GOSSIP_SENDER_MAIN, 50);
            }
        }

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 uiAction)
    {
        if (sender == GOSSIP_SENDER_MAIN)
        {
            player->PlayerTalkClass->ClearMenus();
            switch (uiAction)
            {
            case 50:
                player->CLOSE_GOSSIP_MENU();
                player->CastSpell(player, SOURCE_OF_MAGIC);
                player->RemoveAurasDueToSpell(LAST_DEFENDER_OF_AZEROTH);
                player->RemoveAurasDueToSpell(GIFT_OF_LIFE);
                player->RemoveAurasDueToSpell(TIMELOOP);
                player->RemoveAurasDueToSpell(ESSENCE_OF_DREAMS);
                break;
            default:
                break;
            }
        }
        return true;
    }
};

class spell_ultraxion_twilight_instability : public SpellScriptLoader
{
public:
    spell_ultraxion_twilight_instability() : SpellScriptLoader("spell_ultraxion_twilight_instability") { }

    class spell_ultraxion_twilight_instability_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ultraxion_twilight_instability_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (!GetCaster())
                return;

            targets.remove_if(AuraCheck(SPELL_HEROIC_WILL, true));
        }

        void HandleScript()
        {
            if (!GetCaster() || !GetHitUnit())
                return;

            if (GetCaster()->HasUnitState(UNIT_STATE_CASTING))
                return;

            GetCaster()->CastSpell(GetHitUnit(), SPELL_TWILIGHT_INSTABILITY_DMG, true);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ultraxion_twilight_instability_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            AfterHit += SpellHitFn(spell_ultraxion_twilight_instability_SpellScript::HandleScript);
        }

    private:
        class AuraCheck
        {
        public:
            AuraCheck(uint32 spellId, bool present) : _spellId(spellId), _present(present)
            {}

            bool operator()(WorldObject* unit)
            {
                if (!unit->ToUnit())
                    return true;

                if (_present)
                    return unit->ToUnit()->HasAura(_spellId);
                else
                    return !unit->ToUnit()->HasAura(_spellId);
            }

        private:
            uint32 _spellId;
            bool _present;
        };
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ultraxion_twilight_instability_SpellScript();
    }
};

class spell_ultraxion_hour_of_twilight_dmg : public SpellScriptLoader
{
public:
    spell_ultraxion_hour_of_twilight_dmg() : SpellScriptLoader("spell_ultraxion_hour_of_twilight_dmg")
    {}

    class spell_ultraxion_hour_of_twilight_dmg_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ultraxion_hour_of_twilight_dmg_SpellScript);

        void FilterTargetsDamage(std::list<WorldObject*>& targets)
        {
            if (!GetCaster())
                return;

            targets.remove_if(AuraCheck(SPELL_HEROIC_WILL, true));

            uint32 min_players = 1;

            switch (GetCaster()->GetMap()->GetDifficulty())
            {
            case RAID_DIFFICULTY_10MAN_HEROIC: min_players = 2; break;
            case RAID_DIFFICULTY_25MAN_NORMAL: min_players = 3; break;
            case RAID_DIFFICULTY_25MAN_HEROIC: min_players = 5; break;
            default: min_players = 1; break;
            }

            if (targets.size() < min_players)
                if (Creature* pUltraxion = GetCaster()->ToCreature())
                    pUltraxion->AI()->DoAction(ACTION_TWILIGHT_ERUPTION);
        }

        void FilterTargetsDarkness(std::list<WorldObject*>& targets)
        {
            if (!GetCaster())
                return;

            targets.remove_if(AuraCheck(SPELL_HEROIC_WILL, true));
            targets.remove_if(AuraCheck(SPELL_LOOMING_DARKNESS_DUMMY, false));
        }

        void FilterTargetsAchievement(std::list<WorldObject*>& targets)
        {
            if (!GetCaster())
                return;

            targets.remove_if(AuraCheck(SPELL_HEROIC_WILL, true));
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ultraxion_hour_of_twilight_dmg_SpellScript::FilterTargetsDamage, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ultraxion_hour_of_twilight_dmg_SpellScript::FilterTargetsDarkness, EFFECT_1, TARGET_UNIT_SRC_AREA_ENTRY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ultraxion_hour_of_twilight_dmg_SpellScript::FilterTargetsAchievement, EFFECT_2, TARGET_UNIT_SRC_AREA_ENTRY);
        }

    private:
        class AuraCheck
        {
        public:
            AuraCheck(uint32 spellId, bool present) : _spellId(spellId), _present(present)
            {}

            bool operator()(WorldObject* unit)
            {
                if (!unit->ToUnit())
                    return true;

                if (_present)
                    return unit->ToUnit()->HasAura(_spellId);
                else
                    return !unit->ToUnit()->HasAura(_spellId);
            }

        private:
            uint32 _spellId;
            bool _present;
        };
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ultraxion_hour_of_twilight_dmg_SpellScript();
    }
};

class spell_ultraxion_fading_light : public SpellScriptLoader
{
public:
    spell_ultraxion_fading_light() : SpellScriptLoader("spell_ultraxion_fading_light") { }

    class spell_ultraxion_fading_light_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_ultraxion_fading_light_AuraScript);

        void OnApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (!GetCaster())
                return;

            Aura* aura = aurEff->GetBase();

            uint32 duration = urand((GetCaster()->GetMap()->IsHeroic() ? 3000 : 5000), 9000);
            aura->SetDuration(duration);
            aura->SetMaxDuration(duration);
        }

        void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (GetTarget())
            {
                if (GetTarget()->HasAura(SPELL_TWILIGHT_SHIFT))
                    GetTarget()->CastSpell(GetTarget(), SPELL_FADING_LIGHT_KILL, true);
                else if (GetTarget()->HasAura(SPELL_HEROIC_WILL))
                    GetTarget()->CastSpell(GetTarget(), SPELL_TWILIGHT_SHIFT, true);
            }
        }

        void Register()
        {
            AfterEffectApply += AuraEffectApplyFn(spell_ultraxion_fading_light_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
            AfterEffectRemove += AuraEffectRemoveFn(spell_ultraxion_fading_light_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);

        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_ultraxion_fading_light_AuraScript();
    }

    class spell_ultraxion_fading_light_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ultraxion_fading_light_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (!GetCaster())
                return;

            targets.remove_if(DPSCheck());
            if (Creature* pUltraxion = GetCaster()->ToCreature())
                if (Unit* pTarget = pUltraxion->AI()->SelectTarget(SELECT_TARGET_TOPAGGRO, 0, 0.0f, true))
                    targets.remove(pTarget);

            uint32 min_players = 1;
            switch (GetCaster()->GetMap()->GetDifficulty())
            {
            case RAID_DIFFICULTY_10MAN_HEROIC: min_players = 2; break;
            case RAID_DIFFICULTY_25MAN_NORMAL: min_players = 3; break;
            case RAID_DIFFICULTY_25MAN_HEROIC: min_players = 6; break;
            default: min_players = 1; break;
            }

            if (targets.size() > min_players)
                Trinity::Containers::RandomResizeList(targets, min_players);
        }

        void Register()
        {
            if (m_scriptSpellId == SPELL_FADING_LIGHT_AOE_1 ||
                m_scriptSpellId == 110080 ||
                m_scriptSpellId == 110079 ||
                m_scriptSpellId == 110078)
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ultraxion_fading_light_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }

    private:
        class DPSCheck
        {
        public:
            DPSCheck()
            {}

            bool operator()(WorldObject* unit)
            {
                if (unit->GetTypeId() != TYPEID_PLAYER)
                    return true;

                switch (unit->ToPlayer()->GetPrimaryTalentTree(unit->ToPlayer()->GetActiveSpec()))
                {
                case TALENT_TREE_WARRIOR_PROTECTION:
                case TALENT_TREE_PALADIN_HOLY:
                case TALENT_TREE_PALADIN_PROTECTION:
                case TALENT_TREE_PRIEST_DISCIPLINE:
                case TALENT_TREE_PRIEST_HOLY:
                case TALENT_TREE_DEATH_KNIGHT_BLOOD:
                case TALENT_TREE_SHAMAN_RESTORATION:
                case TALENT_TREE_DRUID_RESTORATION:
                    return true;
                default:
                    return false;
                }
                return false;
            }

        private:
            uint32 _spellId;
        };
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ultraxion_fading_light_SpellScript();
    }
};

class spell_ultraxion_last_defender_of_azeroth : public SpellScriptLoader
{
public:
    spell_ultraxion_last_defender_of_azeroth() : SpellScriptLoader("spell_ultraxion_last_defender_of_azeroth") { }

    class spell_ultraxion_last_defender_of_azeroth_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ultraxion_last_defender_of_azeroth_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (!GetCaster())
                return;

            targets.remove_if(TankCheck());
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ultraxion_last_defender_of_azeroth_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ultraxion_last_defender_of_azeroth_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENTRY);
        }

    private:
        class TankCheck
        {
        public:
            TankCheck()
            {}

            bool operator()(WorldObject* unit)
            {
                if (unit->GetTypeId() != TYPEID_PLAYER)
                    return true;

                switch (unit->ToPlayer()->GetPrimaryTalentTree(unit->ToPlayer()->GetActiveSpec()))
                {
                case TALENT_TREE_WARRIOR_PROTECTION:
                case TALENT_TREE_PALADIN_PROTECTION:
                case TALENT_TREE_DEATH_KNIGHT_BLOOD:
                    return false;
                case TALENT_TREE_DRUID_FERAL_COMBAT:
                    if (unit->ToPlayer()->HasAura(5487))
                        return false;
                    else
                        return true;
                default:
                    return true;
                }
                return true;
            }

        private:
            uint32 _spellId;
        };
    };
    SpellScript* GetSpellScript() const
    {
        return new spell_ultraxion_last_defender_of_azeroth_SpellScript();
    }
};

class spell_ultraxion_last_defender_of_azeroth_dummy : public SpellScriptLoader
{
public:
    spell_ultraxion_last_defender_of_azeroth_dummy() : SpellScriptLoader("spell_ultraxion_last_defender_of_azeroth_dummy") { }

    class spell_ultraxion_last_defender_of_azeroth_dummy_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ultraxion_last_defender_of_azeroth_dummy_SpellScript);

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (!GetCaster() || !GetHitUnit())
                return;

            if (GetHitUnit()->GetTypeId() != TYPEID_PLAYER)
                return;

            switch (GetHitUnit()->ToPlayer()->GetPrimaryTalentTree(GetHitUnit()->ToPlayer()->GetActiveSpec()))
            {
            case TALENT_TREE_WARRIOR_PROTECTION:
                GetHitUnit()->CastSpell(GetHitUnit(), SPELL_LAST_DEFENDER_OF_AZEROTH_WARRIOR, true);
                break;
            case TALENT_TREE_PALADIN_PROTECTION:
                GetHitUnit()->CastSpell(GetHitUnit(), SPELL_LAST_DEFENDER_OF_AZEROTH_PALADIN, true);
                break;
            case TALENT_TREE_DEATH_KNIGHT_BLOOD:
                GetHitUnit()->CastSpell(GetHitUnit(), SPELL_LAST_DEFENDER_OF_AZEROTH_DK, true);
                break;
            case TALENT_TREE_DRUID_FERAL_COMBAT:
                GetHitUnit()->CastSpell(GetHitUnit(), SPELL_LAST_DEFENDER_OF_AZEROTH_DRUID, true);
                break;
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_ultraxion_last_defender_of_azeroth_dummy_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ultraxion_last_defender_of_azeroth_dummy_SpellScript();
    }
};

class spell_ultraxion_heroic_will : public SpellScriptLoader
{
public:
    spell_ultraxion_heroic_will() : SpellScriptLoader("spell_ultraxion_heroic_will") { }

    class spell_ultraxion_heroic_will_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_ultraxion_heroic_will_AuraScript);

        void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (GetTarget())
                GetTarget()->CastSpell(GetTarget(), SPELL_FADED_INTO_TWILIGHT, true);
        }

        void Register()
        {
            AfterEffectRemove += AuraEffectRemoveFn(spell_ultraxion_heroic_will_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_PACIFY_SILENCE, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_ultraxion_heroic_will_AuraScript();
    }
};

class spell_ultraxion_time_loop : public SpellScriptLoader
{
public:
    spell_ultraxion_time_loop() : SpellScriptLoader("spell_ultraxion_time_loop") { }

    class spell_ultraxion_time_loop_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_ultraxion_time_loop_AuraScript);

        bool Load()
        {
            return GetUnitOwner()->GetTypeId() == TYPEID_PLAYER;
        }

        void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool& /*canBeRecalculated*/)
        {
            amount = -1;
        }

        void Absorb(AuraEffect* aurEff, DamageInfo & dmgInfo, uint32 & absorbAmount)
        {
            Unit* victim = GetTarget();
            int32 remainingHealth = victim->GetHealth() - dmgInfo.GetDamage();

            if (remainingHealth <= 0)
            {
                absorbAmount = dmgInfo.GetDamage();
                int32 healAmount = int32(victim->GetMaxHealth());
                victim->CastCustomSpell(victim, SPELL_TIMELOOP_HEAL, &healAmount, NULL, NULL, true, NULL, aurEff);
                aurEff->GetBase()->Remove();
            }
            else
            {
                absorbAmount = 0;
            }
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_ultraxion_time_loop_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_SCHOOL_ABSORB);
            OnEffectAbsorb += AuraEffectAbsorbFn(spell_ultraxion_time_loop_AuraScript::Absorb, EFFECT_1);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_ultraxion_time_loop_AuraScript();
    }
};

typedef boss_ultraxion::boss_ultraxionAI UltraxionAI;

class achievement_minutes_to_midnight : public AchievementCriteriaScript
{
public:
    achievement_minutes_to_midnight() : AchievementCriteriaScript("achievement_minutes_to_midnight") { }

    bool OnCheck(Player* source, Unit* target)
    {
        if (!target)
            return false;

        if (UltraxionAI* ultraxionAI = CAST_AI(UltraxionAI, target->GetAI()))
            return ultraxionAI->AllowAchieve();

        return false;
    }
};

void AddSC_boss_ultraxion()
{
    new boss_ultraxion();
    //new spell_ultraxion_twilight_instability();
    //new spell_ultraxion_hour_of_twilight_dmg();
    //new spell_ultraxion_fading_light();
    //new spell_ultraxion_last_defender_of_azeroth();
    //new spell_ultraxion_last_defender_of_azeroth_dummy();
    //new spell_ultraxion_heroic_will();
    //new spell_ultraxion_time_loop();
    new npc_trall_vs_ultraxion();
    new npc_nozdormu();
    new npc_ysera();
    new npc_aspect_of_magic();
    new npc_alexstrasza();
    //new achievement_minutes_to_midnight();
}
