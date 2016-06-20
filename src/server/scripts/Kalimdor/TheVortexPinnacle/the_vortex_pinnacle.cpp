/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "the_vortex_pinnacle.h"
#include "ScriptedEscortAI.h"
#include "PassiveAI.h"
#include "Player.h"
#include "SpellInfo.h"

enum Creatures
{
    NPC_SLIPSTREAM                  = 45455,
    NPC_SLIPSTREAM_LANDING_ZONE     = 45504,
    NPC_SKYFALL_LAND                = 45981,

    NPC_CLOUD_PRINCE                = 45917,
    NPC_WIPPING_WIND                = 47238,
    NPC_YOUNG_STORM_DRAGON          = 45919,
    NPC_ARMORED_MISTRAL             = 45915,
    NPC_EMPYREAN_ASSASSIN           = 45922,
    NPC_EXECUTOR_OF_THE_CALIPH      = 45928,
    NPC_GUST_SOLDIER                = 45477,
    NPC_LURKING_TEMPEST             = 45704,
    NPC_MINISTER_OF_AIR             = 45930,
    NPC_SERVANT_OF_ASAAD            = 45926,
    NPC_TEMPEST_ADEPT               = 45935,
    NPC_TURBULENT_SQUALL            = 45924,
    NPC_HOWLING_GALE                = 45572,
    NPC_WILD_VORTEX                 = 45912,
    NPC_SKYFALL_STAR                = 45932,
    NPC_GOLDEN_ORB                  = 51157,
    NPC_ITESH                       = 49943,
};

enum Spells
{
    //slipstream
    SPELL_SLIPSTREAM_AURA       = 85021,
    SPELL_SLIPSTREAM_VEH        = 87742,

    //cloud prince
    SPELL_TYPHOON               = 88074,
    SPELL_STARFALL              = 88073,
    SPELL_STARFALL_H            = 92783,

    //whipping wind
    SPELL_WHW_LIGHTNING_BOLT    = 88080,

    //young storm dragon
    SPELL_BRUTAL_STRIKES        = 88192,
    SPELL_BRUTAL_STRIKES_DMG    = 88188,
    SPELL_BRUTAL_STRIKES_DMG_H  = 92758,
    SPELL_CHILLING_BLAST        = 88194,
    SPELL_HEALING_WELL          = 88201,

    //armored mistral
    SPELL_GALE_STRIKE           = 88061,
    SPELL_RISING_WINDS          = 88057,
    SPELL_STORM_SURGE           = 88055,

    //empyrean assassin
    SPELL_LETHARGIC_POISON      = 88184,
    SPELL_VAPOR_FORM            = 88186,

    //executor of the caliph
    SPELL_DEVASTATE             = 78660,
    SPELL_RALLY                 = 87761,
    SPELL_SHOCKWAVE             = 87759,
    
    //gust soldier
    SPELL_AIR_NOVA              = 87933,
    SPELL_AIR_NOVA_H            = 92753,
    SPELL_CHARGE                = 87930,
    SPELL_WIND_BLAST            = 87923,

    //lurking tempest
    SPELL_LT_LIGHTNING_BOLT     = 89105,
    SPELL_FEIGN_DEATH           = 85267,
    SPELL_LURK                  = 85467,

    //minister of air
    SPELL_LIGHTNING_LASH        = 87762,
    SPELL_LIGHTNING_LASH_DUMMY  = 87765,
    SPELL_LIGHTNING_LASH_DMG    = 88963,
    SPELL_LIGHTNING_NOVA        = 87768,
    SPELL_LIGHTNING_NOVA_H      = 92780,

    //servant of asaad
    SPELL_CRUSADER_STRIKE       = 87771,
    SPELL_DIVINE_STORM          = 58112,
    SPELL_HAND_OF_PROTECTION    = 87772,

    //temple adept
    SPELL_DESPERATE_SPEED       = 87780,
    SPELL_GREATER_HEAL          = 87779,
    SPELL_HOLY_SMITE            = 88959,

    //turbulent squall
    SPELL_ASPHYXIATE            = 88175,
    SPELL_CLOUDBURST            = 88170,
    SPELL_CLOUDBURST_H          = 92760,
    SPELL_HURRICANE             = 88171,

    //wild vortex
    SPELL_WV_LIGHTNING_BOLT     = 88032,
    SPELL_WIND_SHOCK            = 88029,
    SPELL_CYCLONE               = 88010,

    //skyfall star
    SPELL_ARCANE_BARRAGE        = 87854,
    SPELL_ARCANE_BARRAGE_H      = 92756,

    //howling gale
    SPELL_HOWLING_GALE          = 85084,
    SPELL_HOWLING_GALE_1        = 85086,
    SPELL_HOWLING_GALE_2        = 85136,
    SPELL_HOWLING_GALE_3        = 85137,
    SPELL_HOWLING_GALE_4        = 85158,
    SPELL_HOWLING_GALE_DMG      = 85159,

};

enum Events
{
    EVENT_ARCANE_BARRAGE        = 1,
    EVENT_TYPHOON               = 2,
    EVENT_STARFALL              = 3,
    EVENT_WHW_LIGHTNING_BOLT    = 4,
    EVENT_CHILLING_BLAST        = 5,
    EVENT_GALE_STRIKE           = 6,
    EVENT_STORM_SURGE           = 7,
    EVENT_VAPOR_FORM            = 8,
    EVENT_DEVASTATE             = 9,
    EVENT_SHOCKWAVE             = 10,
    EVENT_RALLY                 = 11,
    EVENT_AIR_NOVA              = 12,
    EVENT_WIND_BLAST            = 13,
    EVENT_LIGHTNING_NOVA        = 14,
    EVENT_LIGHTNING_LASH        = 15,
    EVENT_CRUSADER_STRIKE       = 16,
    EVENT_HAND_OF_PROTECTION    = 17,
    EVENT_DESPERATE_SPEED       = 18,
    EVENT_GREATER_HEAL          = 19,
    EVENT_HOLY_SMITE            = 20,
    EVENT_ASPHYXIATE            = 21,
    EVENT_HURRICANE             = 22,
    EVENT_CLOUDBURST            = 23,
    EVENT_CYCLONE               = 24,
    EVENT_WIND_SHOCK            = 25,
    EVENT_WV_LIGHTNING_BOLT     = 26,
    EVENT_HOWLING_GALE          = 27,
};

const Position teleportPos[2] = 
{
    {-906.08f, -176.51f, 664.50f, 2.86f},
    {-1193.67f, 472.83f, 634.86f, 0.50f},
};

enum Other
{
    TYPE_SLIPSTREAM    = 1,
};

// 45455
class npc_slipstream_45455 : public CreatureScript
{
    public:
        npc_slipstream_45455() : CreatureScript("npc_slipstream_45455") { }

        bool OnGossipHello(Player* pPlayer, Creature* creature)
        {
            if (InstanceScript* pInstance = creature->GetInstanceScript())
            {
                if (pInstance->GetData(DATA_ALTAIRUS) == DONE)  // 43873
                {
                    pPlayer->NearTeleportTo(
                        teleportPos[1].GetPositionX(),
                        teleportPos[1].GetPositionY(),
                        teleportPos[1].GetPositionZ()+10.0f,
                        teleportPos[1].GetOrientation());
                    return true;
                }
                else if (pInstance->GetData(DATA_GRAND_VIZIER_ERTAN) == DONE) // 43878
                {
                    pPlayer->NearTeleportTo(
                        teleportPos[0].GetPositionX(),
                        teleportPos[0].GetPositionY(),
                        teleportPos[0].GetPositionZ()+10.0f,
                        teleportPos[0].GetOrientation());
                    return true;
                }
            }
            return false;
        }

        struct npc_slipstream_45455AI : public ScriptedAI
        {
            npc_slipstream_45455AI(Creature* creature) : ScriptedAI(creature)
            {
                me->SetCanFly(true);
            }

            void Reset()
            {
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                DoCast(me, SPELL_SLIPSTREAM_AURA);
            }

            void UpdateAI(uint32 /*diff*/) { }
     };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_slipstream_45455AI(creature);
        }
};

// 45932 // 52019
class npc_skyfall_star_45932 : public CreatureScript
{
    public:
        npc_skyfall_star_45932() : CreatureScript("npc_skyfall_star_45932") { }

        struct npc_skyfall_star_45932AI : public ScriptedAI
        {
            npc_skyfall_star_45932AI(Creature* creature) : ScriptedAI(creature)
            {
                me->SetCanFly(true);
                SetCombatMovement(false);
            }

            EventMap events;

            void Reset()
            {
                events.Reset();
            }

            void JustDied(Unit* /*who*/)
            {
                me->SetCanFly(false);
            }

            void EnterCombat(Unit* /*attacker*/)
            {
                events.ScheduleEvent(EVENT_ARCANE_BARRAGE, urand(5000, 6000));
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_ARCANE_BARRAGE:
                        DoCast(SPELL_ARCANE_BARRAGE);
                        events.ScheduleEvent(EVENT_ARCANE_BARRAGE, urand(5000, 6000));
                        break;
                    }
                }
            }
     };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_skyfall_star_45932AI(creature);
        }
};

// 45917
class npc_cloud_prince_45917 : public CreatureScript
{
    public:
        npc_cloud_prince_45917() : CreatureScript("npc_cloud_prince_45917") { }

        struct npc_cloud_prince_45917AI : public ScriptedAI
        {
            npc_cloud_prince_45917AI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit* /*attacker*/)
            {
                events.ScheduleEvent(EVENT_TYPHOON, urand(5000, 7000));
                events.ScheduleEvent(EVENT_STARFALL, urand(7000, 15000));
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_TYPHOON:
                        DoCast(SPELL_TYPHOON);
                        events.ScheduleEvent(EVENT_TYPHOON, urand(15000, 20000));
                        break;
                    case EVENT_STARFALL:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                            DoCast(target, SPELL_STARFALL);
                        events.ScheduleEvent(EVENT_STARFALL, 20000);
                        break;
                    }
                }
                DoMeleeAttackIfReady();
            }
     };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_cloud_prince_45917AI(creature);
        }
};

// 47238
class npc_whipping_wind_47238 : public CreatureScript
{
    public:
        npc_whipping_wind_47238() : CreatureScript("npc_whipping_wind_47238") { }

        struct npc_whipping_wind_47238AI : public ScriptedAI
        {
            npc_whipping_wind_47238AI(Creature* creature) : ScriptedAI(creature) { }

            EventMap events;

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit* /*attacker*/)
            {
                events.ScheduleEvent(EVENT_WHW_LIGHTNING_BOLT, 2000);
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_WHW_LIGHTNING_BOLT:
                        DoCastVictim(SPELL_WHW_LIGHTNING_BOLT);
                        events.ScheduleEvent(EVENT_WHW_LIGHTNING_BOLT, 2000);
                        break;
                    }
                }
                DoMeleeAttackIfReady();
            }
     };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_whipping_wind_47238AI(creature);
        }
};

// 45919
class npc_young_storm_dragon_45919 : public CreatureScript
{
    public:
        npc_young_storm_dragon_45919() : CreatureScript("npc_young_storm_dragon_45919") { }

        struct npc_young_storm_dragon_45919AI : public ScriptedAI
        {
            npc_young_storm_dragon_45919AI(Creature* creature) : ScriptedAI(creature)
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
            }

            EventMap events;

            void Reset()
            {
                DoCast(me, SPELL_BRUTAL_STRIKES);
                events.Reset();
            }

            void EnterCombat(Unit* /*attacker*/)
            {
                DoCast(me, SPELL_HEALING_WELL);
                events.ScheduleEvent(EVENT_CHILLING_BLAST, urand(12000, 15000));
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_CHILLING_BLAST:
                        DoCastVictim(SPELL_CHILLING_BLAST);
                        events.ScheduleEvent(EVENT_CHILLING_BLAST, urand(15000, 18000));
                        break;
                    }
                }
                DoMeleeAttackIfReady();
            }
     };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_young_storm_dragon_45919AI(creature);
        }
};

// 45915
class npc_armored_mistral_45915 : public CreatureScript
{
    public:
        npc_armored_mistral_45915() : CreatureScript("npc_armored_mistral_45915") { }

        struct npc_armored_mistral_45915AI : public ScriptedAI
        {
            npc_armored_mistral_45915AI(Creature* creature) : ScriptedAI(creature) { }

            EventMap events;

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit* /*attacker*/)
            {
                DoCast(me, SPELL_RISING_WINDS);
                events.ScheduleEvent(EVENT_GALE_STRIKE, urand(2000, 4000));
                events.ScheduleEvent(EVENT_STORM_SURGE, urand(10000, 15000));    
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_GALE_STRIKE:
                        DoCast(me, SPELL_GALE_STRIKE);
                        events.ScheduleEvent(EVENT_GALE_STRIKE, urand(15000, 20000));
                        break;
                    case EVENT_STORM_SURGE:
                        DoCast(me, SPELL_STORM_SURGE);
                        events.ScheduleEvent(EVENT_STORM_SURGE, urand(15000, 20000));
                        break;
                    }
                }
                DoMeleeAttackIfReady();
            }
     };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_armored_mistral_45915AI(creature);
        }
};

// 45922
class npc_empyrean_assassin_45922 : public CreatureScript
{
    public:
        npc_empyrean_assassin_45922() : CreatureScript("npc_empyrean_assassin_45922") { }

        struct npc_empyrean_assassin_45922AI : public ScriptedAI
        {
            npc_empyrean_assassin_45922AI(Creature* creature) : ScriptedAI(creature) { }

            EventMap events;

            void Reset()
            {
                DoCast(me, SPELL_LETHARGIC_POISON);
                events.Reset();
            }

            void EnterCombat(Unit* /*attacker*/)
            {
                events.ScheduleEvent(EVENT_VAPOR_FORM, urand(15000, 20000));    
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_VAPOR_FORM:
                        DoCast(me, SPELL_VAPOR_FORM);
                        events.ScheduleEvent(EVENT_VAPOR_FORM, urand(20000, 25000));
                        break;
                    }
                }
                DoMeleeAttackIfReady();
            }
     };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_empyrean_assassin_45922AI(creature);
        }
};

// 45928
class npc_executor_of_the_caliph_45928 : public CreatureScript
{
    public:
        npc_executor_of_the_caliph_45928() : CreatureScript("npc_executor_of_the_caliph_45928") { }

        struct npc_executor_of_the_caliph_45928AI : public ScriptedAI
        {
            npc_executor_of_the_caliph_45928AI(Creature* creature) : ScriptedAI(creature) { }

            EventMap events;

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit* /*attacker*/)
            {
                events.ScheduleEvent(EVENT_RALLY, urand(5000, 20000));
                events.ScheduleEvent(EVENT_DEVASTATE, urand(2000, 8000));
                events.ScheduleEvent(EVENT_SHOCKWAVE, urand(12000, 20000));
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_RALLY:
                        DoCast(SPELL_RALLY);
                        events.ScheduleEvent(EVENT_RALLY, urand(20000, 30000));
                        break;
                    case EVENT_SHOCKWAVE:
                        DoCast(SPELL_SHOCKWAVE);
                        events.ScheduleEvent(EVENT_SHOCKWAVE, urand(16000, 30000));
                        break;
                    case EVENT_DEVASTATE:
                        DoCastVictim(SPELL_DEVASTATE);
                        events.ScheduleEvent(EVENT_DEVASTATE, urand(15000, 18000));
                        break;
                    }
                }
                DoMeleeAttackIfReady();
            }
     };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_executor_of_the_caliph_45928AI(creature);
        }
};

// 45477
class npc_gust_soldier_45477 : public CreatureScript
{
    public:
        npc_gust_soldier_45477() : CreatureScript("npc_gust_soldier_45477") { }

        struct npc_gust_soldier_45477AI : public ScriptedAI
        {
            npc_gust_soldier_45477AI(Creature* creature) : ScriptedAI(creature) { }

            EventMap events;

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit* attacker)
            {
                DoCast(attacker, SPELL_CHARGE);
                events.ScheduleEvent(EVENT_AIR_NOVA, urand(5000, 15000));
                events.ScheduleEvent(EVENT_WIND_BLAST, urand(6000, 8000));
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_AIR_NOVA:
                        DoCast(SPELL_AIR_NOVA);
                        events.ScheduleEvent(EVENT_AIR_NOVA, urand(10000, 15000));
                        break;
                    case EVENT_WIND_BLAST:
                        DoCastVictim(SPELL_WIND_BLAST);
                        events.ScheduleEvent(EVENT_WIND_BLAST, urand(6000, 8000));
                        break;
                    }
                }
                DoMeleeAttackIfReady();
            }
     };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_gust_soldier_45477AI(creature);
        }
};

// 45704
class npc_lurking_tempest_45704 : public CreatureScript
{
    public:
        npc_lurking_tempest_45704() : CreatureScript("npc_lurking_tempest_45704") { }

        struct npc_lurking_tempest_45704AI : public ScriptedAI
        {
            npc_lurking_tempest_45704AI(Creature* creature) : ScriptedAI(creature) { }

            void Reset() { }

            void EnterCombat(Unit* /*attacker*/) { }

            void UpdateAI(uint32 /*diff*/)
            {
                if (!UpdateVictim())
                    return;
            }
     };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_lurking_tempest_45704AI(creature);
        }
};

// 45572
class npc_howling_gale_45572 : public CreatureScript
{
    public:
        npc_howling_gale_45572() : CreatureScript("npc_howling_gale_45572") { }

        struct npc_howling_gale_45572AI : public ScriptedAI
        {
            npc_howling_gale_45572AI(Creature* creature) : ScriptedAI(creature)
            {
                me->SetReactState(REACT_PASSIVE);
                SetCombatMovement(false);
            }

            EventMap events;
            bool bCombat;

            void Reset()
            {
                bCombat = false;
                events.Reset();
                DoCast(me, SPELL_HOWLING_GALE);
                events.ScheduleEvent(EVENT_HOWLING_GALE, 1000);
            }

            void JustReachedHome()
            {
                bCombat = false;
            }

            void EnterEvadeMode()
            {
                bCombat = false;
                _EnterEvadeMode();
                Reset();
            }

            void DamageTaken(Unit* /*who*/, uint32& /*damage*/)
            {
                bCombat = true;
                events.CancelEvent(EVENT_HOWLING_GALE);
                me->RemoveAurasDueToSpell(SPELL_HOWLING_GALE);
            }

            void UpdateAI(uint32 diff)
            {
                
                if (bCombat)
                {
                    if (!me->GetMap()->GetPlayers().isEmpty())
                    {
                        uint8 _attackersnum = 0;
                        for (Map::PlayerList::const_iterator itr = me->GetMap()->GetPlayers().begin(); itr != me->GetMap()->GetPlayers().end(); ++itr)
                            if (me->GetDistance2d(itr->GetSource()) < 30.0f)
                                _attackersnum++;

                        if (_attackersnum == 0)
                        {
                            EnterEvadeMode();
                            return;
                        }
                    }
                }

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_HOWLING_GALE:
                        DoCast(me, SPELL_HOWLING_GALE_1, true);
                        DoCast(me, SPELL_HOWLING_GALE_2, true);
                        DoCast(me, SPELL_HOWLING_GALE_3, true);
                        events.ScheduleEvent(EVENT_HOWLING_GALE, 2500);
                        break;
                    }
                }
            }
     };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_howling_gale_45572AI(creature);
        }
};

// 45930
class npc_minister_of_air_45930 : public CreatureScript
{
    public:
        npc_minister_of_air_45930() : CreatureScript("npc_minister_of_air_45930") { }

        struct npc_minister_of_air_45930AI : public ScriptedAI
        {
            npc_minister_of_air_45930AI(Creature* creature) : ScriptedAI(creature) { }

            EventMap events;

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit* /*attacker*/)
            {
                events.ScheduleEvent(EVENT_LIGHTNING_LASH, urand(4000, 8000));
                events.ScheduleEvent(EVENT_LIGHTNING_NOVA, urand(7000, 10000));

            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_LIGHTNING_NOVA:
                        DoCast(SPELL_LIGHTNING_NOVA);
                        events.ScheduleEvent(EVENT_LIGHTNING_NOVA, urand(10000, 20000));
                        break;
                    case EVENT_LIGHTNING_LASH:
                        DoCast(SPELL_LIGHTNING_LASH);
                        events.ScheduleEvent(EVENT_LIGHTNING_LASH, urand(8000, 15000));
                        break;
                    }
                }
                DoMeleeAttackIfReady();
            }
     };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_minister_of_air_45930AI(creature);
        }
};

// 45926
class npc_servant_of_asaad_45926 : public CreatureScript
{
    public:
        npc_servant_of_asaad_45926() : CreatureScript("npc_servant_of_asaad_45926") { }

        struct npc_servant_of_asaad_45926AI : public ScriptedAI
        {
            npc_servant_of_asaad_45926AI(Creature* creature) : ScriptedAI(creature) { }

            EventMap events;

            void Reset()
            {

                events.Reset();
            }

            void EnterCombat(Unit* /*attacker*/)
            {
                events.ScheduleEvent(EVENT_CRUSADER_STRIKE, urand(3000, 6000));
                events.ScheduleEvent(EVENT_HAND_OF_PROTECTION, urand(10000, 15000));
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_CRUSADER_STRIKE:
                        DoCastVictim(SPELL_CRUSADER_STRIKE);
                        events.ScheduleEvent(EVENT_CRUSADER_STRIKE, urand(8000, 12000));
                        break;
                    case EVENT_HAND_OF_PROTECTION:
                        DoCast(me, SPELL_HAND_OF_PROTECTION);
                        events.ScheduleEvent(EVENT_HAND_OF_PROTECTION, urand(20000, 30000));
                        break;
                    }
                }
                DoMeleeAttackIfReady();
            }
     };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_servant_of_asaad_45926AI(creature);
        }
};

// 45935
class npc_temple_adept_45935 : public CreatureScript
{
    public:
        npc_temple_adept_45935() : CreatureScript("npc_temple_adept_45935") { }

        struct npc_temple_adept_45935AI : public ScriptedAI
        {
            npc_temple_adept_45935AI(Creature* creature) : ScriptedAI(creature) { }

            EventMap events;

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit* /*attacker*/)
            {
                events.ScheduleEvent(EVENT_HOLY_SMITE, urand(5000, 6000));
                events.ScheduleEvent(EVENT_GREATER_HEAL, urand(5000, 6000));
                events.ScheduleEvent(EVENT_DESPERATE_SPEED, urand(10000, 15000));
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_HOLY_SMITE:
                        DoCastVictim(SPELL_HOLY_SMITE);
                        events.ScheduleEvent(EVENT_HOLY_SMITE, urand(5000, 6000));
                        break;
                    case EVENT_DESPERATE_SPEED:
                        DoCast(me, SPELL_DESPERATE_SPEED);
                        events.ScheduleEvent(EVENT_DESPERATE_SPEED, urand(20000, 30000));
                        break;
                    case EVENT_GREATER_HEAL:
                        if (Creature* _target = me->FindNearestCreature(NPC_EXECUTOR_OF_THE_CALIPH, 30.0f))
                        {
                            if (_target->GetHealthPct() < 50)
                                DoCast(_target, SPELL_GREATER_HEAL);
                        }
                        else if (Creature* _target = me->FindNearestCreature(NPC_MINISTER_OF_AIR, 30.0f))
                        {
                            if (_target->GetHealthPct() < 50)
                                DoCast(_target, SPELL_GREATER_HEAL);
                        }
                        else if (Creature* _target = me->FindNearestCreature(NPC_SERVANT_OF_ASAAD, 30.0f))
                        {
                            if (_target->GetHealthPct() < 50)
                                DoCast(_target, SPELL_GREATER_HEAL);
                        }
                        else if (Creature* _target = me->FindNearestCreature(NPC_TEMPEST_ADEPT, 30.0f))
                        {
                            if (_target->GetHealthPct() < 50)
                                DoCast(_target, SPELL_GREATER_HEAL);
                        }
                        else
                            break;
                        events.ScheduleEvent(EVENT_GREATER_HEAL, urand(5000, 6000));
                        break;
                    }
                }
            }
     };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_temple_adept_45935AI(creature);
        }
};

// 45924
class npc_turbulent_squall_45924 : public CreatureScript
{
    public:
        npc_turbulent_squall_45924() : CreatureScript("npc_turbulent_squall_45924") { }

        struct npc_turbulent_squall_45924AI : public ScriptedAI
        {
            npc_turbulent_squall_45924AI(Creature* creature) : ScriptedAI(creature) { }

            EventMap events;

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit* /*attacker*/)
            {
                events.ScheduleEvent(EVENT_ASPHYXIATE, urand(3000, 10000));
                events.ScheduleEvent(EVENT_HURRICANE, urand(10000, 20000));
                events.ScheduleEvent(EVENT_CLOUDBURST, urand(5000, 30000));
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_ASPHYXIATE:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                            DoCast(target, SPELL_ASPHYXIATE);
                        events.ScheduleEvent(EVENT_ASPHYXIATE, urand(10000, 20000));
                        break;
                    case EVENT_HURRICANE:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                            DoCast(target, SPELL_HURRICANE);
                        events.ScheduleEvent(EVENT_HURRICANE, urand(15000, 30000));
                        break;
                    case EVENT_CLOUDBURST:
                        DoCast(SPELL_CLOUDBURST);
                        events.ScheduleEvent(EVENT_CLOUDBURST, urand(20000, 30000));
                        break;
                    }
                }
                DoMeleeAttackIfReady();
            }
     };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_turbulent_squall_45924AI(creature);
        }
};

// 45912
class npc_wild_vortex_45912 : public CreatureScript
{
    public:
        npc_wild_vortex_45912() : CreatureScript("npc_wild_vortex_45912") { }

        struct npc_wild_vortex_45912AI : public ScriptedAI
        {
            npc_wild_vortex_45912AI(Creature* creature) : ScriptedAI(creature) { }

            EventMap events;

            void Reset()
            {

                events.Reset();
            }

            void EnterCombat(Unit* /*attacker*/)
            {
                events.ScheduleEvent(EVENT_WIND_SHOCK, urand(5000, 10000));
                events.ScheduleEvent(EVENT_WV_LIGHTNING_BOLT, 3000);
                events.ScheduleEvent(EVENT_CYCLONE, urand(5000, 15000));
            }

            void UpdateAI(uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_CYCLONE:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 0.0f, true))
                            DoCast(target, SPELL_CYCLONE);
                        events.ScheduleEvent(EVENT_CYCLONE, urand(10000, 20000));
                        break;
                    case EVENT_WIND_SHOCK:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 0.0f, true))
                            DoCast(target, SPELL_WIND_SHOCK);
                        events.ScheduleEvent(EVENT_WIND_SHOCK, urand(10000, 20000));
                        break;
                    case EVENT_WV_LIGHTNING_BOLT:
                        DoCastVictim(SPELL_WV_LIGHTNING_BOLT);
                        events.ScheduleEvent(EVENT_WV_LIGHTNING_BOLT, 3000);
                        break;
                    }
                }
            }
     };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_wild_vortex_45912AI(creature);
        }
};

// 87762
class spell_minister_of_air_lightning_lash : public SpellScriptLoader
{
    public:
        spell_minister_of_air_lightning_lash() : SpellScriptLoader("spell_minister_of_air_lightning_lash") { }


        class spell_minister_of_air_lightning_lash_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_minister_of_air_lightning_lash_SpellScript);


            void HandleScript(SpellEffIndex /*effIndex*/)
            {
                if (!GetCaster() || !GetHitUnit())
                    return;

                GetCaster()->CastSpell(GetHitUnit(), SPELL_LIGHTNING_LASH_DMG, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_minister_of_air_lightning_lash_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_minister_of_air_lightning_lash_SpellScript();
        }
};

// 85084 
class spell_howling_gale_howling_gale : public SpellScriptLoader
{
    public:
        spell_howling_gale_howling_gale() : SpellScriptLoader("spell_howling_gale_howling_gale") { }
 
        class spell_howling_gale_howling_gale_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_howling_gale_howling_gale_AuraScript)

            void OnPeriodic(AuraEffect const* /*aurEff*/)
            {
                if (!GetCaster())
                    return;

                GetCaster()->MonsterSay("ok", 0, 0);
                //GetCaster()->CastSpell(GetCaster(), SPELL_HOWLING_GALE_1, true);
                //GetCaster()->CastSpell(GetCaster(), SPELL_HOWLING_GALE_2, true);
                //GetCaster()->CastSpell(GetCaster(), SPELL_HOWLING_GALE_3, true);
            }
 
            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_howling_gale_howling_gale_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            }
        };
 
        AuraScript* GetAuraScript() const
        {
            return new spell_howling_gale_howling_gale_AuraScript();
        }
};

void AddSC_the_vortex_pinnacle()
{
    new npc_slipstream_45455();
    new npc_skyfall_star_45932();
    new npc_cloud_prince_45917();
    new npc_whipping_wind_47238();
    new npc_young_storm_dragon_45919();
    new npc_armored_mistral_45915();
    new npc_empyrean_assassin_45922();
    new npc_executor_of_the_caliph_45928();
    new npc_gust_soldier_45477();
    new npc_howling_gale_45572();
    new npc_lurking_tempest_45704();
    new npc_minister_of_air_45930();
    new npc_servant_of_asaad_45926();
    new npc_temple_adept_45935();
    new npc_turbulent_squall_45924();
    new npc_wild_vortex_45912();
    new spell_minister_of_air_lightning_lash();
    new spell_howling_gale_howling_gale();
};