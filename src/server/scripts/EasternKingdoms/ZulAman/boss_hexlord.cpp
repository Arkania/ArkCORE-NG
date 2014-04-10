 /*
 * Copyright (C) 2014 Arkania Project
 *
 * This file is NOT free software. You may NOT copy, redistribute it or modify it.
 */

/* ScriptData
SDName: Boss_Hex_Lord_Malacrass 4.1
SD%Complete: 100
SDComment:
SDCategory: Zul'Aman 5 Hc
EndScriptData */

#include "ScriptPCH.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"
#include "MapManager.h"
#include "Spell.h"
#include "Vehicle.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "CreatureTextMgr.h"
#include "Weather.h"

#include "zulaman.h"

enum Yells
{
    YELL_INTRO         = 0,
    YELL_AGGRO,
    YELL_SPIRIT_BOLTS,
    YELL_DRAIN_POWER,
    YELL_KILL_ONE,
    YELL_KILL_TWO,
    YELL_DEATH,
    YELL_BERSERK,

    YELL_ADD_1,
    YELL_ADD_2,
    YELL_ADD_3,

    ANN_SOUL
};

enum Spells
{
    /*** BOSS ***/

    SPELL_SPIRIT_BOLTS              = 43383,
    SPELL_DRAIN_POWER               = 44131,
    SPELL_SIPHON_SOUL               = 43501,

    // Druid
    SPELL_DR_THORNS                 = 43420,
    SPELL_DR_LIFEBLOOM              = 43421,
    SPELL_DR_MOONFIRE               = 43545,

    // Hunter
    SPELL_HU_EXPLOSIVE_TRAP         = 43444,
    SPELL_HU_FREEZING_TRAP          = 43447,
    SPELL_HU_SNAKE_TRAP             = 43449,

    // Mage
    SPELL_MG_FIREBALL               = 41383,
    SPELL_MG_FROST_NOVA             = 43426,
    SPELL_MG_ICE_LANCE              = 43427,
    SPELL_MG_FROSTBOLT              = 43428,

    // Paladin
    SPELL_PA_CONSECRATION           = 43429,
    SPELL_PA_AVENGING_WRATH         = 43430,
    SPELL_PA_HOLY_LIGHT             = 43451,

    // Priest
    SPELL_PR_HEAL                   = 41372,
    SPELL_PR_PSYCHIC_SCREAM         = 43432,
    SPELL_PR_PAIN_SUPP              = 44416,

    // Death Knight
    SPELL_PLAGUE_STRIKE             = 56361,
    SPELL_DEATH_DECAY               = 56359,
    SPELL_BLOOD_WORMS               = 97628,

    // Rogue
    SPELL_RO_BLIND                  = 43433,
    SPELL_RO_SLICE_DICE             = 43457,
    SPELL_RO_WOUND_POISON           = 43461,

    // Shaman
    SPELL_SH_CHAIN_LIGHT            = 43435,
    SPELL_SH_FIRE_NOVA              = 43436,
    SPELL_SH_HEALING_WAVE           = 43548,

    // Warlock
    SPELL_WL_CURSE_OF_DOOM          = 43439,
    SPELL_WL_RAIN_OF_FIRE           = 43440,
    SPELL_WL_UNSTABLE_AFFL          = 43522,
    SPELL_WL_UNST_AFFL_DISPEL       = 43523,

    // Warrior
    SPELL_WR_MORTAL_STRIKE          = 43441,
    SPELL_WR_WHIRLWIND              = 43442,
    SPELL_WR_SPELL_REFLECT          = 43443,

    // Blood Worms
    SPELL_WORM_HEAL                 = 97630,

    SPELL_BERSERK                   = 45078,
    /*** ADDS ***/

    //Alyson Antille
    SPELL_FLASH_HEAL                = 43575,
    SPELL_DISPEL_MAGIC              = 43577,
    //Thurg
    SPELL_BLOODLUST                 = 43578,
    SPELL_CLEAVE                    = 15496,
    //Slither
    SPELL_VENOM_SPIT                = 43579,
    //Lord Raadan
    SPELL_FLAME_BREATH              = 43582,
    SPELL_THUNDERCLAP               = 43583,
    //Gazakroth
    SPELL_FIREBOLT                  = 43584,
    //Fenstalker
    SPELL_VOLATILE_INFECTION        = 43586,
    //Darkheart
    SPELL_PSYCHIC_WAIL              = 43590,
    //Koragg
    SPELL_COLD_STARE                = 43593,
    SPELL_MIGHTY_BLOW               = 43592
};

// Add spawn positions :
#define POS_Y  921.2795f
#define POS_Z  33.8883f
#define ORIENT 1.5696f

static float Pos_X[2]               = {107.8827f, 127.8827f};

// Possible adds :
static uint32 AddEntryList[8]=
{
    24240, //Alyson Antille
    24241, //Thurg
    24242, //Slither
    24243, //Lord Raadan
    24244, //Gazakroth
    24245, //Fenstalker
    24246, //Darkheart
    24247  //Koragg
};

enum AbilityTarget
{
    ABILITY_TARGET_SELF             = 0,
    ABILITY_TARGET_VICTIM           = 1,
    ABILITY_TARGET_ENEMY            = 2,
    ABILITY_TARGET_HEAL             = 3,
    ABILITY_TARGET_BUFF             = 4,
    ABILITY_TARGET_SPECIAL          = 5
};

// Defines for spells, targets, cooldowns of siphon soul abilities :
struct PlayerAbilityStruct
{
    uint32 spell;
    AbilityTarget target;
};

// Defines for various powers he uses after using siphon soul (0 - 9) :
static PlayerAbilityStruct PlayerAbility[][3] =
{
    // class 1  - warrior
    {{SPELL_WR_SPELL_REFLECT,  ABILITY_TARGET_SELF},
    {SPELL_WR_WHIRLWIND,       ABILITY_TARGET_SELF},
    {SPELL_WR_MORTAL_STRIKE,   ABILITY_TARGET_VICTIM}},
    // class 2  - paladin
    {{SPELL_PA_CONSECRATION,   ABILITY_TARGET_SELF},
    {SPELL_PA_HOLY_LIGHT,      ABILITY_TARGET_HEAL},
    {SPELL_PA_AVENGING_WRATH,  ABILITY_TARGET_SELF}},
    // class 3  - hunter
    {{SPELL_HU_EXPLOSIVE_TRAP, ABILITY_TARGET_SELF},
    {SPELL_HU_FREEZING_TRAP,   ABILITY_TARGET_SELF},
    {SPELL_HU_SNAKE_TRAP,      ABILITY_TARGET_SELF}},
    // class 4  - rogue
    {{SPELL_RO_WOUND_POISON,   ABILITY_TARGET_VICTIM},
    {SPELL_RO_SLICE_DICE,      ABILITY_TARGET_SELF},
    {SPELL_RO_BLIND,           ABILITY_TARGET_ENEMY}},
    // class 5  - priest
    {{SPELL_PR_PAIN_SUPP,      ABILITY_TARGET_HEAL},
    {SPELL_PR_HEAL,            ABILITY_TARGET_HEAL},
    {SPELL_PR_PSYCHIC_SCREAM,  ABILITY_TARGET_SELF}},
    // class 6  - death knight
    {{SPELL_PLAGUE_STRIKE,     ABILITY_TARGET_VICTIM},
    {SPELL_DEATH_DECAY,        ABILITY_TARGET_ENEMY},
    {SPELL_BLOOD_WORMS,        ABILITY_TARGET_ENEMY}},
    // class 7  - shaman
    {{SPELL_SH_FIRE_NOVA,      ABILITY_TARGET_SELF},
    {SPELL_SH_HEALING_WAVE,    ABILITY_TARGET_HEAL},
    {SPELL_SH_CHAIN_LIGHT,     ABILITY_TARGET_ENEMY}},
    // class 8  - mage
    {{SPELL_MG_FIREBALL,       ABILITY_TARGET_ENEMY},
    {SPELL_MG_FROSTBOLT,       ABILITY_TARGET_ENEMY},
    {SPELL_MG_ICE_LANCE,       ABILITY_TARGET_SPECIAL}},
    // class 9  - warlock
    {{SPELL_WL_CURSE_OF_DOOM,  ABILITY_TARGET_ENEMY},
    {SPELL_WL_RAIN_OF_FIRE,    ABILITY_TARGET_ENEMY},
    {SPELL_WL_UNSTABLE_AFFL,   ABILITY_TARGET_ENEMY}},
    // class 11(10 here) - druid
    {{SPELL_DR_LIFEBLOOM,      ABILITY_TARGET_HEAL},
    {SPELL_DR_THORNS,          ABILITY_TARGET_SELF},
    {SPELL_DR_MOONFIRE,        ABILITY_TARGET_ENEMY}}
};

enum Events
{
    // Boss
    EVENT_SPIRIT_BOLTS              = 1,
    EVENT_DRAIN_POWER,
    EVENT_SIPHON_SOUL,
    EVENT_USE_ABILITY,

    EVENT_CHECK_ADDS,
    EVENT_CHECK_POSITION,

    EVENT_BERSERK

    // Adds have timer scripts.
};

// General Add AI
struct boss_hexlord_addAI : public ScriptedAI
{
    InstanceScript* instance;

    boss_hexlord_addAI(Creature* creature) : ScriptedAI(creature)
    {
        instance = creature->GetInstanceScript();
    }

    void Reset() {}

    void EnterCombat(Unit* /*who*/)
    {
        DoZoneInCombat();
    }

    void UpdateAI(uint32 /*diff*/)
    {
        if (instance && instance->GetData(DATA_HEXLORDEVENT) != IN_PROGRESS)
        {
            EnterEvadeMode();
            return;
        }

        DoMeleeAttackIfReady();
    }
};

/*** BOSS **/

class boss_hexlord_malacrass : public CreatureScript
{
public:
    boss_hexlord_malacrass() : CreatureScript("boss_hexlord_malacrass") { }

    struct boss_hex_lord_malacrassAI : public ScriptedAI
    {
        boss_hex_lord_malacrassAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            SelectAddEntry();
            for (uint8 i = 0; i < 2; ++i)
                AddGUID[i] = 0;
            introDone = false;
        }

        InstanceScript* instance;
        EventMap events;

        // Adds
        uint64 AddGUID[2];
        uint32 AddEntry[2];

        // Siphon Soul
        uint64 PlayerGUID;
        uint32 PlayerClass;

        uint32 castNumber;
        uint32 addDeadSays;

        bool introDone, hasSoul;

        void Reset()
        {
			events.Reset();

            if (instance)
                instance->SetData(DATA_HEXLORDEVENT, NOT_STARTED);

            hasSoul = false;

            SpawnAdds();
            castNumber = 0;
            addDeadSays = 0;
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (!introDone && me->IsWithinDistInMap(who, 40) && who->GetTypeId() == TYPEID_PLAYER)
            {
                Talk(YELL_INTRO);
                introDone = true;
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(YELL_AGGRO);

            if (instance)
            {
                instance->SetData(DATA_HEXLORDEVENT, IN_PROGRESS);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add
            }

            events.ScheduleEvent(EVENT_SPIRIT_BOLTS, 20000);
            events.ScheduleEvent(EVENT_DRAIN_POWER, 60000);

            events.ScheduleEvent(EVENT_CHECK_ADDS, 5000);
            events.ScheduleEvent(EVENT_CHECK_POSITION, 6000);

            events.ScheduleEvent(EVENT_BERSERK, 10 * MINUTE * IN_MILLISECONDS);

            for (uint8 i = 0; i < 2; ++i)
            {
                Unit* Temp = Unit::GetUnit(*me, AddGUID[i]);
                if (Temp && Temp->IsAlive())
                    CAST_CRE(Temp)->AI()->AttackStart(me->GetVictim());
                else
                {
                    EnterEvadeMode();
                    break;
                }
            }
        }

        void KilledUnit(Unit* /*victim*/)
        {
            Talk(RAND(YELL_KILL_ONE, YELL_KILL_TWO));
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(YELL_DEATH);

            if (instance)
            {
                instance->SetData(DATA_HEXLORDEVENT, DONE);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }

            for (uint8 i = 0; i < 2; ++i)
            {
                Unit* Temp = Unit::GetUnit(*me, AddGUID[i]);
                if (Temp && Temp->IsAlive())
                    Temp->DealDamage(Temp, Temp->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
            }
        }

        void SelectAddEntry()
        {
            std::vector<uint32> AddList;

            for (uint8 i = 0; i < 8; ++i)
                AddList.push_back(AddEntryList[i]);

            while (AddList.size() > 2)
                AddList.erase(AddList.begin()+rand()%AddList.size());

            uint8 i = 0;
            for (std::vector<uint32>::const_iterator itr = AddList.begin(); itr != AddList.end(); ++itr, ++i)
                AddEntry[i] = *itr;
        }

        void SpawnAdds()
        {
            for (uint8 i = 0; i < 2; ++i)
            {
                Creature* creature = (Unit::GetCreature((*me), AddGUID[i]));
                if (!creature || !creature->IsAlive())
                {
                    if (creature) creature->setDeathState(DEAD);
                    creature = me->SummonCreature(AddEntry[i], Pos_X[i], POS_Y, POS_Z, ORIENT, TEMPSUMMON_DEAD_DESPAWN, 0);
                    if (creature) AddGUID[i] = creature->GetGUID();
                }
                else
                {
                    creature->AI()->EnterEvadeMode();
                    creature->SetPosition(Pos_X[i], POS_Y, POS_Z, ORIENT);
                    creature->StopMoving();
                }
            }
        }

        void EnterEvadeMode()
        {
			Reset();
			me->GetMotionMaster()->MoveTargetedHome();
			me->RemoveAllAuras();

            if (instance)
            {
                instance->SetBossState(DATA_HEXLORDEVENT, FAIL);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (castNumber == 3 && hasSoul)
            {
                castNumber = 0;
                hasSoul = false;
            }

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_SPIRIT_BOLTS:
                        Talk(YELL_SPIRIT_BOLTS);
                        DoCast(me, SPELL_SPIRIT_BOLTS, false);
                        events.ScheduleEvent(EVENT_SPIRIT_BOLTS, 40000);
                        events.ScheduleEvent(EVENT_SIPHON_SOUL, 10000);
                        break;

                    case EVENT_DRAIN_POWER:
                        Talk(YELL_DRAIN_POWER);
                        DoCast(me, SPELL_DRAIN_POWER, true);
                        events.ScheduleEvent(EVENT_DRAIN_POWER, urand(40000, 55000));
                        break;

                    case EVENT_SIPHON_SOUL:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 70, true))
                        {
                            DoCast(target, SPELL_SIPHON_SOUL);

                            PlayerGUID = target->GetGUID();
                            PlayerClass = target->getClass();

                            if (PlayerClass == CLASS_DRUID) // 11.
                                PlayerClass = 10; // for defines match use.

                            hasSoul = true;
                            events.ScheduleEvent(EVENT_USE_ABILITY, urand(8000, 10000));
                        }
                        break;

                    case EVENT_USE_ABILITY:
                        if (hasSoul)
                        {
                            UseAbility();
                            castNumber++;
                            events.ScheduleEvent(EVENT_USE_ABILITY, urand(8000, 10000));
                        }
                        break;

                    case EVENT_CHECK_ADDS:
                        for (uint8 i = 0; i < 2; ++i)
                            if (Creature* temp = Unit::GetCreature(*me, AddGUID[i]))
                            {
                                if (temp->IsAlive() && !temp->GetVictim())
                                    temp->AI()->AttackStart(me->GetVictim());
                                else if(!temp->IsAlive() && addDeadSays < 2)
                                {
                                    Talk(RAND(YELL_ADD_1, YELL_ADD_2, YELL_ADD_3));
                                    addDeadSays++;
                                }
                            }
                        events.ScheduleEvent(EVENT_CHECK_ADDS, 5000);
                        break;

                    case EVENT_CHECK_POSITION:
                        if (me->IsWithinDist3d(119.223f, 1035.45f, 29.4481f, 10))
                            EnterEvadeMode();
                        events.ScheduleEvent(EVENT_CHECK_POSITION, 5000);
                        break;

                    case EVENT_BERSERK:
                        Talk(YELL_BERSERK);
                        DoCast(me, SPELL_BERSERK);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void UseAbility()
        {
            uint8 random = urand(0, 2);
            Unit* target = NULL;
            switch (PlayerAbility[PlayerClass-1][random].target)
            {
                case ABILITY_TARGET_SELF:
                    target = me;
                    break;
                case ABILITY_TARGET_VICTIM:
                    target = me->GetVictim();
                    break;
                case ABILITY_TARGET_ENEMY:
                default:
                    target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true);
                    break;
                case ABILITY_TARGET_HEAL:
                    target = DoSelectLowestHpFriendly(50, 0);
                    break;
                case ABILITY_TARGET_BUFF:
                    {
                        std::list<Creature*> templist = DoFindFriendlyMissingBuff(50, PlayerAbility[PlayerClass][random].spell);
                        if (!templist.empty())
                            target = *(templist.begin());
                    }
                    break;
            }
            if (target)
                DoCast(target, PlayerAbility[PlayerClass-1][random].spell);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_hex_lord_malacrassAI(creature);
    }
};

/*** ADDS ***/

// Thurg
class boss_thurg : public CreatureScript
{
    public:

        boss_thurg() : CreatureScript("boss_thurg") { }

        struct boss_thurgAI : public boss_hexlord_addAI
        {

            boss_thurgAI(Creature* creature) : boss_hexlord_addAI(creature) {}

            uint32 bloodlust_timer;
            uint32 cleave_timer;

            void Reset()
            {
                bloodlust_timer = 15000;
                cleave_timer = 10000;
                boss_hexlord_addAI::Reset();
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (bloodlust_timer <= diff)
                {
                    std::list<Creature*> templist = DoFindFriendlyMissingBuff(50, SPELL_BLOODLUST);
                    if (!templist.empty())
                    {
                        if (Unit* target = *(templist.begin()))
                            DoCast(target, SPELL_BLOODLUST, false);
                    }
                    bloodlust_timer = 12000;
                } else bloodlust_timer -= diff;

                if (cleave_timer <= diff)
                {
                    DoCast(me->GetVictim(), SPELL_CLEAVE, false);
                    cleave_timer = 12000; //3 sec cast
                } else cleave_timer -= diff;

                boss_hexlord_addAI::UpdateAI(diff);
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_thurgAI(creature);
        }
};

// Alyson Antille
class boss_alyson_antille : public CreatureScript
{
    public:

        boss_alyson_antille() : CreatureScript("boss_alyson_antille") { }

        struct boss_alyson_antilleAI : public boss_hexlord_addAI
        {
            //Holy Priest
            boss_alyson_antilleAI(Creature* creature) : boss_hexlord_addAI(creature) {}

            uint32 flashheal_timer;
            uint32 dispelmagic_timer;

            void Reset()
            {
                flashheal_timer = 2500;
                boss_hexlord_addAI::Reset();
            }

            void AttackStart(Unit* who)
            {
                if (!who)
                    return;

                if (who->isTargetableForAttack())
                {
                    if (me->Attack(who, false))
                    {
                        me->GetMotionMaster()->MoveChase(who, 20);
                        me->AddThreat(who, 0.0f);
                    }
                }
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (flashheal_timer <= diff)
                {
                    Unit* target = DoSelectLowestHpFriendly(99, 30000);
                    if (target)
                    {
                        if (target->IsWithinDistInMap(me, 50))
                            DoCast(target, SPELL_FLASH_HEAL, false);
                    }
                    else
                    {
                        if (urand(0, 1))
                            target = DoSelectLowestHpFriendly(50, 0);
                        else
                            target = SelectTarget(SELECT_TARGET_RANDOM, 0);
                        if (target)
                            DoCast(target, SPELL_DISPEL_MAGIC, false);
                    }
                    flashheal_timer = 2500;
                } else flashheal_timer -= diff;

                boss_hexlord_addAI::UpdateAI(diff);
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_alyson_antilleAI(creature);
        }
};

// Gazakroth
class boss_gazakroth : public CreatureScript
{
    public:
        boss_gazakroth() : CreatureScript("boss_gazakroth") { }

        struct boss_gazakrothAI : public boss_hexlord_addAI
        {
            boss_gazakrothAI(Creature* creature) : boss_hexlord_addAI(creature)  {}
        
            uint32 firebolt_timer;
        
            void Reset()
            {
                firebolt_timer = 2000;
                boss_hexlord_addAI::Reset();
            }
        
            void AttackStart(Unit* who)
            {
                if (!who)
                    return;
        
                if (who->isTargetableForAttack())
                {
                    if (me->Attack(who, false))
                    {
                        me->GetMotionMaster()->MoveChase(who, 20);
                        me->ToUnit()->getThreatManager().modifyThreatPercent(who, 100);
        	            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
                        me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, true);
                    }
                }
            }
        
            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;
        
                if (firebolt_timer <= diff)
                {
                    DoCast(me->GetVictim(), SPELL_FIREBOLT, false);
                    firebolt_timer = 700;
                } else firebolt_timer -= diff;
        
                boss_hexlord_addAI::UpdateAI(diff);
            }
        };
        
        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_gazakrothAI(creature);
        }
};

// Raadan
class boss_lord_raadan : public CreatureScript
{
    public:

        boss_lord_raadan() : CreatureScript("boss_lord_raadan") { }

        struct boss_lord_raadanAI : public boss_hexlord_addAI
        {
            boss_lord_raadanAI(Creature* creature) : boss_hexlord_addAI(creature)  {}

            uint32 flamebreath_timer;
            uint32 thunderclap_timer;

            void Reset()
            {
                flamebreath_timer = 8000;
                thunderclap_timer = 13000;
                boss_hexlord_addAI::Reset();
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (thunderclap_timer <= diff)
                {
                    DoCast(me->GetVictim(), SPELL_THUNDERCLAP, false);
                    thunderclap_timer = 12000;
                } else thunderclap_timer -= diff;

                if (flamebreath_timer <= diff)
                {
                    DoCast(me->GetVictim(), SPELL_FLAME_BREATH, false);
                    flamebreath_timer = 12000;
                } else flamebreath_timer -= diff;

                boss_hexlord_addAI::UpdateAI(diff);
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_lord_raadanAI(creature);
        }
};

// Darkheart
class boss_darkheart : public CreatureScript
{
    public:

        boss_darkheart() : CreatureScript("boss_darkheart") { }

        struct boss_darkheartAI : public boss_hexlord_addAI
        {
            boss_darkheartAI(Creature* creature) : boss_hexlord_addAI(creature)  {}

            uint32 psychicwail_timer;

            void Reset()
            {
                psychicwail_timer = 8000;
                boss_hexlord_addAI::Reset();
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (psychicwail_timer <= diff)
                {
                    DoCast(me->GetVictim(), SPELL_PSYCHIC_WAIL, false);
                    psychicwail_timer = 12000;
                } else psychicwail_timer -= diff;

                boss_hexlord_addAI::UpdateAI(diff);
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_darkheartAI(creature);
        }
};

// Slither
class boss_slither : public CreatureScript
{
    public:

        boss_slither() : CreatureScript("boss_slither") { }

        struct boss_slitherAI : public boss_hexlord_addAI
        {
            boss_slitherAI(Creature* creature) : boss_hexlord_addAI(creature) {}

            uint32 venomspit_timer;

            void Reset()
            {
                venomspit_timer = 5000;
                boss_hexlord_addAI::Reset();
            }

            void AttackStart(Unit* who)
            {
                if (!who)
                    return;

                if (who->isTargetableForAttack())
                {
                    if (me->Attack(who, false))
                    {
                        me->GetMotionMaster()->MoveChase(who, 20);
                        me->AddThreat(who, 0.0f);
                    }
                }
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (venomspit_timer <= diff)
                {
                    if (Unit* victim = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                        DoCast(victim, SPELL_VENOM_SPIT, false);
                    venomspit_timer = 2500;
                } else venomspit_timer -= diff;

                boss_hexlord_addAI::UpdateAI(diff);
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_slitherAI(creature);
        }
};

//Fenstalker
class boss_fenstalker : public CreatureScript
{
    public:

        boss_fenstalker() : CreatureScript("boss_fenstalker") { }

        struct boss_fenstalkerAI : public boss_hexlord_addAI
        {
            boss_fenstalkerAI(Creature* creature) : boss_hexlord_addAI(creature) {}

            uint32 volatileinf_timer;

            void Reset()
            {
                volatileinf_timer = 15000;
                boss_hexlord_addAI::Reset();
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (volatileinf_timer <= diff)
                {
                    // core bug
                    me->GetVictim()->CastSpell(me->GetVictim(), SPELL_VOLATILE_INFECTION, false);
                    volatileinf_timer = 12000;
                } else volatileinf_timer -= diff;

                boss_hexlord_addAI::UpdateAI(diff);
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_fenstalkerAI(creature);
        }
};

//Koragg
class boss_koragg : public CreatureScript
{
    public:

        boss_koragg() : CreatureScript("boss_koragg") { }

        struct boss_koraggAI : public boss_hexlord_addAI
        {
            boss_koraggAI(Creature* creature) : boss_hexlord_addAI(creature) {}

            uint32 coldstare_timer;
            uint32 mightyblow_timer;

            void Reset()
            {
                coldstare_timer = 15000;
                mightyblow_timer = 10000;
                boss_hexlord_addAI::Reset();
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (mightyblow_timer <= diff)
                {
                    DoCast(me->GetVictim(), SPELL_MIGHTY_BLOW, false);
                    mightyblow_timer = 12000;
                }
                if (coldstare_timer <= diff)
                {
                    if (Unit* victim = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                        DoCast(victim, SPELL_COLD_STARE, false);
                    coldstare_timer = 12000;
                }

                boss_hexlord_addAI::UpdateAI(diff);
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_koraggAI(creature);
        }
};

// Bloodworms DK
class npc_hexlord_bloodworm : public CreatureScript
{
public:
    npc_hexlord_bloodworm() : CreatureScript("npc_hexlord_bloodworm") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hexlord_bloodwormAI(creature);
    }

    struct npc_hexlord_bloodwormAI : public ScriptedAI
    {
        npc_hexlord_bloodwormAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            if (Creature* hexLord = creature->FindNearestCreature(24239, 100.0f, true))
                creature->GetMotionMaster()->MoveChase(hexLord);
            creature->SetReactState(REACT_PASSIVE);
        }

        InstanceScript* instance;

        void UpdateAI(uint32 /*diff*/)
        {
            if (Creature* hexLord = me->FindNearestCreature(24239, 100.0f, true))
                if(me->IsWithinDistInMap(hexLord, 5))
                {
                    DoCast(hexLord, SPELL_WORM_HEAL, true);
                    me->DisappearAndDie();
                }
        }
    };
};

class spell_hexlord_unstable_affliction : public SpellScriptLoader
{
    public:
        spell_hexlord_unstable_affliction() : SpellScriptLoader("spell_hexlord_unstable_affliction") { }

        class spell_hexlord_unstable_affliction_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_hexlord_unstable_affliction_AuraScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WL_UNST_AFFL_DISPEL))
                    return false;
                return true;
            }

            void HandleDispel(DispelInfo* dispelInfo)
            {
                if (Unit* caster = GetCaster())
                    caster->CastSpell(dispelInfo->GetDispeller(), SPELL_WL_UNST_AFFL_DISPEL, true, NULL, GetEffect(EFFECT_0));
            }

            void Register()
            {
                AfterDispel += AuraDispelFn(spell_hexlord_unstable_affliction_AuraScript::HandleDispel);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_hexlord_unstable_affliction_AuraScript();
        }
};

void AddSC_boss_hex_lord_malacrass()
{
    new boss_hexlord_malacrass();
    new boss_thurg();
    new boss_gazakroth();
    new boss_lord_raadan();
    new boss_darkheart();
    new boss_slither();
    new boss_fenstalker();
    new boss_koragg();
    new boss_alyson_antille();
    new npc_hexlord_bloodworm();
    new spell_hexlord_unstable_affliction();
}