/*Copyright (C) 2014 Arkania Project.
*
* This file is NOT free software. Third-party users can NOT redistribute it or modify it :). 
* If you find it, you are either hacking something, or very lucky (presuming someone else managed to hack it).
*/

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

#include "halls_of_origination.h"

enum Yells
{
    SAY_AGGRO  =   0,
    SAY_BEACON =   1,
    SAY_KILL   =   2,
    SAY_DEATH  =   3,
    SAY_ANNOUNCE = -1900025
};

enum Spells
{
    SPELL_DIVINE_RECKONING      = 75592,
    SPELL_REVERBERATING_HYMN    = 75322,
    SPELL_SHIELD_OF_LIGHT       = 74938,
    SPELL_SEARING_FLAME_SUMM    = 75114,
    SPELL_SEARING_BUNNY         = 75194,

    SPELL_VIPER_DOT             = 74538,
    SPELL_VIPER_DOT_H           = 91167
};

Position const SpawnPosition[21] =
{
    {-654.277f, 361.118f, 52.9508f, 5.86241f},
    {-670.102f, 350.896f, 54.1803f, 2.53073f},
    {-668.896f, 326.048f, 53.2267f, 3.36574f},
    {-618.875f, 344.237f, 52.95f, 0.194356f},
    {-661.667f, 338.78f, 53.0333f, 2.53073f},
    {-607.836f, 348.586f, 53.4939f, 1.0558f},
    {-656.452f, 376.388f, 53.9709f, 1.4525f},
    {-652.762f, 370.634f, 52.9503f, 2.5221f},
    {-682.656f, 343.953f, 53.7329f, 2.53073f},
    {-658.877f, 309.077f, 53.6711f, 0.595064f},
    {-619.399f, 309.049f, 53.4247f, 4.63496f},
    {-612.648f, 318.365f, 53.777f, 3.53434f},
    {-616.398f, 345.109f, 53.0165f, 2.53073f},
    {-681.394f, 342.813f, 53.8955f, 6.24987f},
    {-668.843f, 351.407f, 54.1813f, 5.5293f},
    {-672.797f, 317.175f, 52.9636f, 5.51166f},
    {-631.834f, 375.502f, 55.7079f, 0.738231f},
    {-617.027f, 360.071f, 52.9816f, 2.00725f},
    {-623.891f, 361.178f, 52.9334f, 5.61183f},
    {-614.988f, 331.613f, 52.9533f, 2.91186f},
    {-662.902f, 341.463f, 52.9502f, 2.84307f}
};

enum BossPhases
{
    PHASE_NORMAL  = 1,
    PHASE_SHIELD  = 2
};

/*
 burning light working method:

 - npc 50416 beam bunny - beams cast the light visual on these on anhuur shield.
 - npc on face 51114 which casts 75194 searing light npc on the platform spawned by boss with 75114 on target.

 levers working method:

 - 76606 76608 are spells that are used by the lever beacons, in the template. these have :

   Effect 0: Id 77 (SPELL_EFFECT_SCRIPT_EFFECT)
   BasePoints = 74930
   Targets (22, 7) (TARGET_SRC_CASTER, TARGET_UNIT_SRC_AREA_ENTRY)
   Max Radius (Id 9) 20.00

   Effect 0: Id 77 (SPELL_EFFECT_SCRIPT_EFFECT)
   BasePoints = 76573
   Targets (22, 7) (TARGET_SRC_CASTER, TARGET_UNIT_SRC_AREA_ENTRY)
   Max Radius (Id 9) 20.00

   These spells the player seems to cast on himself and they have script effects, for 74930 and 76573:
 
   Effect 0: Id 6 (SPELL_EFFECT_APPLY_AURA)
   BasePoints = 0
   Targets (1, 0) (TARGET_UNIT_CASTER, NO_TARGET)
   Aura Id 4 (SPELL_AURA_DUMMY), value = 0, misc = 0 (0), miscB = 0, periodic = 0
   
   Effect 1: Id 6 (SPELL_EFFECT_APPLY_AURA)
   BasePoints = 10000
   Targets (22, 7) (TARGET_SRC_CASTER, TARGET_UNIT_SRC_AREA_ENTRY)
   Aura Id 4 (SPELL_AURA_DUMMY), value = 10000, misc = 0 (0), miscB = 0, periodic = 0
   Max Radius (Id 12) 100.00
   
   The first dummy needs script so that player casts 68395 on the lever, which is the cast for opening.
   The second dummy is the time after which the beam is killed and anhuur's shield part drops.
*/

enum Creatures
{
    NPC_BEAM_OF_LIGHT = 40183,
    NPC_BEAM_BUNNY    = 50416,
    NPC_BLIGHT        = 51114
};

class boss_anhuur : public CreatureScript
{
    public:
        boss_anhuur() : CreatureScript("boss_anhuur") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_anhuurAI(creature);
        }

        struct boss_anhuurAI : public ScriptedAI
        {
            boss_anhuurAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            std::list<uint64> SummonList;

            InstanceScript *instance;

            uint8 Phase;
            uint8 PhaseCount;
            uint8 FlameCount;

            uint32 DivineReckoningTimer;
            uint32 SearingFlameTimer;

            void Reset()
            {
                if (instance)
                    instance->SetData(DATA_TEMPLE_GUARDIAN_ANHUUR_EVENT, NOT_STARTED);

                Phase = PHASE_NORMAL;
                PhaseCount = 0;
                FlameCount = 2;
                DivineReckoningTimer = 8000;
                SearingFlameTimer = 5000;
                RemoveSummons();
                me->RemoveAurasDueToSpell(SPELL_SHIELD_OF_LIGHT);
                me->RemoveAurasDueToSpell(SPELL_REVERBERATING_HYMN);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); //Remove
            }

            void RemoveSummons()
            {
                if (SummonList.empty())
                    return;

                for (std::list<uint64>::const_iterator itr = SummonList.begin(); itr != SummonList.end(); ++itr)
                    if (Creature* pTemp = Unit::GetCreature(*me, *itr))
                        pTemp->DisappearAndDie();

                SummonList.clear();
            }

            void JustSummoned(Creature* pSummon)
            {
                SummonList.push_back(pSummon->GetGUID());
            }

            void ChangePhase()
            {
                me->GetMotionMaster()->MoveTargetedHome();
                me->AddAura(SPELL_SHIELD_OF_LIGHT, me);
                me->AddAura(SPELL_REVERBERATING_HYMN, me);

                PhaseCount++;
                Talk(SAY_BEACON);
                DoScriptText(SAY_ANNOUNCE, me);

                Phase = PHASE_SHIELD;

                for(int i= 0; i<21; i++)
                    me->SummonCreature(NPC_PIT_SNAKE, SpawnPosition[i].GetPositionX(), SpawnPosition[i].GetPositionY(), SpawnPosition[i].GetPositionZ(), SpawnPosition[i].GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);

                me->SummonCreature(NPC_BEAM_OF_LIGHT, -603.465f, 334.38f, 65.4f, 3.12f, TEMPSUMMON_CORPSE_DESPAWN, 1000);
                me->SummonCreature(NPC_BEAM_OF_LIGHT, -678.132f, 334.21f, 64.9f, 0.24f, TEMPSUMMON_CORPSE_DESPAWN, 1000);
            }

            void KilledUnit(Unit* /*Killed*/)
            {
                Talk (SAY_KILL);
            }

            void JustDied(Unit* /*Kill*/)
            {
                RemoveSummons();
                Talk(SAY_DEATH);

                if (instance)
                {
                    instance->SetData(DATA_TEMPLE_GUARDIAN_ANHUUR_EVENT, DONE);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); //Remove
                }

                if (GameObject* Bridge = me->FindNearestGameObject(GO_ANHUUR_BRIDGE, 200))
                    Bridge->SetGoState(GO_STATE_ACTIVE);

                if (GameObject* Door = me->FindNearestGameObject(GO_ANHUUR_DOOR, 200))
                    Door->SetGoState(GO_STATE_ACTIVE);
            }

            void SummonedCreatureDespawn(Creature* summon)
            {
                switch(summon->GetEntry())
                {
                    case NPC_BEAM_OF_LIGHT:
                        FlameCount--;
                        break;
                }
            }

            void EnterCombat(Unit* /*Ent*/)
            {
                Talk(SAY_AGGRO);

                if (instance)
                {
                    instance->SetData(DATA_TEMPLE_GUARDIAN_ANHUUR_EVENT, IN_PROGRESS);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add.
                }

                DoZoneInCombat();
            }

            void EnterEvadeMode()
            {
                RemoveSummons();
                me->GetMotionMaster()->MoveTargetedHome();
                me->SetHealth(me->GetMaxHealth());
                
                if (instance)
                {
                    instance->SetData(DATA_TEMPLE_GUARDIAN_ANHUUR_EVENT, FAIL);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
                }
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim() && !me->HasAura(SPELL_SHIELD_OF_LIGHT) || me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if ((me->HealthBelowPct(67) && Phase == PHASE_NORMAL && PhaseCount == 0) ||(me->HealthBelowPct(34) && Phase == PHASE_NORMAL && PhaseCount == 1))
                    ChangePhase();

                if (Phase == PHASE_SHIELD && FlameCount == 0)
                {
                    me->RemoveAurasDueToSpell(SPELL_SHIELD_OF_LIGHT);
                    me->RemoveAurasDueToSpell(SPELL_REVERBERATING_HYMN);
                    
                    if (Player* target = me->SelectNearestPlayer(10.0f))
                        AttackStart(target);

                    Phase = PHASE_NORMAL;

                    RemoveSummons();
                    FlameCount = 2;
                }

                if (Phase == PHASE_NORMAL)
                {
                    if (DivineReckoningTimer <= diff )
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                            DoCast(target, SPELL_DIVINE_RECKONING);
                        DivineReckoningTimer = urand(15000,18000);
                    }   else DivineReckoningTimer -= diff;

                    if (SearingFlameTimer <= diff)
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                            target->CastSpell(target, SPELL_SEARING_FLAME_SUMM, true);
                        SearingFlameTimer = urand(8000,12000);
                    } else SearingFlameTimer -= diff;
                }

                DoMeleeAttackIfReady();
            }
        };
};

class npc_anhuur_viper : public CreatureScript
{
    public:
        npc_anhuur_viper() : CreatureScript("npc_anhuur_viper") {}

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_viperAI(creature);
        }
            
        struct npc_viperAI : public ScriptedAI
        {
            npc_viperAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
                m_uiViperDotTimer = urand(8000, 15000);
            }

            InstanceScript* instance;
            uint32 m_uiViperDotTimer;

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if (m_uiViperDotTimer <= uiDiff)
                {
                    DoCast(me->GetVictim(), IsHeroic() ? SPELL_VIPER_DOT_H : SPELL_VIPER_DOT);
                    m_uiViperDotTimer = urand(41000, 50000);
                }
                else
                    m_uiViperDotTimer -= uiDiff;

                DoMeleeAttackIfReady();
            }
        };
};

class go_beacon_of_light : public GameObjectScript
{
public:
    go_beacon_of_light() : GameObjectScript("go_beacon_of_light") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        go->UseDoorOrButton();
        player->CastSpell(go, 68398, false);
        if (Creature* beam = go->FindNearestCreature(NPC_BEAM_OF_LIGHT, 14.0f, true))
            beam->Kill(beam);
        player->PlayerTalkClass->ClearMenus();

        return true;
    }
};

class go_lift_of_the_makers_controller : public GameObjectScript
{
    public:
        go_lift_of_the_makers_controller() : GameObjectScript("go_lift_of_the_makers_controller") { }

        bool OnGossipHello(Player* player, GameObject* go)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Bring elevator to first floor.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Bring elevator to second floor.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

            player->SEND_GOSSIP_MENU(207669, go->GetGUID());

            return true;
        }

        bool OnGossipSelect(Player* player, GameObject* go, uint32 /*sender*/, uint32 action)
        {
            InstanceScript* instance = go->GetInstanceScript();

            player->PlayerTalkClass->ClearMenus();
            player->CLOSE_GOSSIP_MENU();

            if (GameObject* lift = GameObject::GetGameObject(*go, instance->GetData64(DATA_ORIGINATION_ELEVATOR)))
            {
                if (action == GOSSIP_ACTION_INFO_DEF+1)
                    lift->SetGoState(GO_STATE_ACTIVE);
                else if (action == GOSSIP_ACTION_INFO_DEF+2)
                    lift->SetGoState(GO_STATE_READY);
            }

            return true;
        }
};

void AddSC_boss_anhuur()
{
    new boss_anhuur();
    new go_beacon_of_light();
    new npc_anhuur_viper();
    new go_lift_of_the_makers_controller();
}
