/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
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
#include "throne_of_the_tides.h"
#include "Group.h"

#define GOSSIP_READY "We are ready!"

enum ScriptTexts
{
    SAY_INTRO_1     = 0,
    SAY_INTRO_2     = 1,
    SAY_INTRO_3_1   = 2,
    SAY_PHASE_2_1   = 3,
    SAY_50          = 4,
    SAY_25          = 5,
    SAY_INTRO_3_2   = 6,
    SAY_PHASE_2_2   = 7,
    SAY_PHASE_3_1   = 8,
    SAY_PHASE_3_2   = 9,
    SAY_DEATH       = 10,
    SAY_KILL        = 11,
};

enum Spells
{
    SPELL_BLIGHT_OF_OZUMAT_SELF         = 83585,
    SPELL_BLIGHT_OF_OZUMAT_TRIGGER      = 83518,
    SPELL_BLIGHT_OF_OZUMAT_MISSILE      = 83506,
    SPELL_BLIGHT_OF_OZUMAT_SUMMON_1     = 83524,
    SPELL_BLIGHT_OF_OZUMAT_SUMMON_2     = 83606,
    SPELL_BLIGHT_OF_OZUMAT_DUMMY        = 83672,
    SPELL_BLIGHT_OF_OZUMAT_AURA         = 83525,
    SPELL_BLIGHT_OF_OZUMAT_DMG          = 83561,
    SPELL_BLIGHT_OF_OZUMAT_DMG_H        = 91495,
    SPELL_BLIGHT_OF_OZUMAT_AOE          = 83607,
    SPELL_BLIGHT_OF_OZUMAT_AOE_DMG      = 83608,
    SPELL_BLIGHT_OF_OZUMAT_AOE_DMG_H    = 91494,
    SPELL_TIDAL_SURGE                   = 76133,
        
    // Vicious Mindslasher
    SPELL_BRAIN_SPIKE                   = 83915,
    SPELL_BRAIN_SPIKE_H                 = 91497,
    SPELL_VEIL_OF_SHADOW                = 83926,
    SPELL_SHADOW_BOLT                   = 83914,

    // Unyielding Behemoth
    SPELL_BLIGHT_SPRAY                  = 83985,

    // Faceless Sapper
    SPELL_ENTANGLING_GRASP              = 83463,

    SPELL_ENCOUNTER_COMPLETE            = 95673,
}; 

enum Events
{
    EVENT_INTRO_2               = 1,
    EVENT_INTRO_3_2             = 2,
    EVENT_SUMMON_MURLOC         = 3,
    EVENT_SUMMON_BEHEMOTH       = 4,
    EVENT_SUMMON_MINDLASHER     = 5,
    EVENT_SUMMON_SAPPER         = 6,
    EVENT_SUMMON_BEAST          = 7,
    EVENT_BLIGHT_OF_OZUMAT      = 8,
    EVENT_PLAYER_CHECK          = 9,
    EVENT_SHADOW_BOLT           = 10,
    EVENT_BRAIN_SPIKE           = 11,
    EVENT_VEIL_OF_SHADOW        = 12,
    EVENT_BLIGHT_SPRAY          = 13,
    EVENT_PHASE_2_2             = 14,
};

enum Adds
{
    NPC_DEEP_MURLOC_INVADER     = 44658,
    NPC_VICIOUS_MINDLASHER      = 44715,
    NPC_UNYIELDING_BEHEMOTH     = 44648,
    NPC_FACELESS_SAPPER         = 44752,
    NPC_BLIGHT_BEAST            = 44841,
    NPC_BLIGHT_OF_OZUMAT_1      = 44801,
    NPC_BLIGHT_OF_OZUMAT_2      = 44834,
};

enum Actions
{
    ACTION_NEPTULON_START_EVENT = 1,
    ACTION_NEPTULON_START       = 2,
};

enum Achievement
{
    SPELL_KILL_OZUMAT   = 95673,
};

const Position spawnPos[5] = 
{
    {-142.48f, 950.78f, 231.05f, 1.88f},
    {-126.62f, 1015.55f, 230.37f, 4.48f},
    {-171.65f, 1006.13f, 230.67f, 5.90f},
    {-162.53f, 966.55f, 229.43f, 0.65f},
    {-110.35f, 981.47f, 229.90f, 2.83f},
};

// 40792
class npc_neptulon : public CreatureScript
{
    public:
        npc_neptulon() : CreatureScript("npc_neptulon") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_neptulonAI (creature);
        }

        bool OnGossipHello(Player* pPlayer, Creature* creature)
        {
            if (InstanceScript* pInstance = creature->GetInstanceScript())
            {
                if (pInstance->GetBossState(DATA_COMMANDER_ULTHOK) != DONE
                    || pInstance->GetBossState(DATA_OZUMAT) == IN_PROGRESS
                    || pInstance->GetBossState(DATA_OZUMAT) == DONE)
                    return false;

                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_READY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                pPlayer->SEND_GOSSIP_MENU(1, creature->GetGUID());
            }
            return true;
        }

        bool OnGossipSelect(Player* pPlayer, Creature* creature, uint32 /*uiSender*/, uint32 /*uiAction*/)
        {
            if (InstanceScript* pInstance = creature->GetInstanceScript())
            {
                if (pInstance->GetBossState(DATA_COMMANDER_ULTHOK) != DONE
                    || pInstance->GetBossState(DATA_OZUMAT) == IN_PROGRESS
                    || pInstance->GetBossState(DATA_OZUMAT) == DONE)
                    return false;

                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->CLOSE_GOSSIP_MENU();
                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                pInstance->SetBossState(DATA_OZUMAT, IN_PROGRESS);
                creature->AI()->DoAction(ACTION_NEPTULON_START);
            }
            return true;
        }

        struct npc_neptulonAI : public ScriptedAI
        {
            npc_neptulonAI(Creature* creature) : ScriptedAI(creature), summons(me)
            {
                pInstance = creature->GetInstanceScript();
            }

            InstanceScript* pInstance;
            EventMap events;
            SummonList summons;
            uint32 uiMindLasherCount;
            uint32 uiSapperCount;
            bool bActive;
            bool b50;
            bool b25;

            void Reset()
            {
                bActive = false;
                b50 = false;
                b25 = false;
                uiMindLasherCount = 0;
                uiSapperCount = 0;
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                events.Reset();
                summons.DespawnAll();
                me->SetHealth(me->GetMaxHealth());
                if (pInstance)
                    if (pInstance->GetBossState(DATA_OZUMAT) != DONE)
                        pInstance->SetBossState(DATA_OZUMAT, NOT_STARTED);
            }

            void DoAction(int32 action)
            {
                if (action == ACTION_NEPTULON_START_EVENT)
                {
                    bActive = true;
                    Talk(SAY_INTRO_1);
                    events.ScheduleEvent(EVENT_INTRO_2, 7000);
                }
                else if (action == ACTION_NEPTULON_START)
                {
                    bActive = true;
                    Talk(SAY_INTRO_3_1);
                    events.ScheduleEvent(EVENT_INTRO_3_2, 30000);
                    events.ScheduleEvent(EVENT_SUMMON_MURLOC, urand(5000, 8000));
                    events.ScheduleEvent(EVENT_SUMMON_MINDLASHER, 10000);
                    events.ScheduleEvent(EVENT_SUMMON_BEHEMOTH, 20000);
                }
            }

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);
            }

            void SummonedCreatureDies(Creature* creature, Unit* /*pKiller*/)
            {
                summons.Despawn(creature);
                if (creature->GetEntry() == NPC_VICIOUS_MINDLASHER)
                {
                    uiMindLasherCount++;
                    if (uiMindLasherCount > 2)
                    {
                        Talk(SAY_PHASE_2_2);
                        events.CancelEvent(EVENT_SUMMON_MURLOC);
                        events.ScheduleEvent(EVENT_PHASE_2_2, 10000);
                        events.ScheduleEvent(EVENT_SUMMON_SAPPER, 8000);
                        events.ScheduleEvent(EVENT_SUMMON_BEAST, 14000);
                        events.ScheduleEvent(EVENT_BLIGHT_OF_OZUMAT, urand(9000, 11000));
                    }
                    else
                        events.ScheduleEvent(EVENT_SUMMON_MINDLASHER, urand(10000, 15000));
                }
                else if (creature->GetEntry() == NPC_FACELESS_SAPPER)
                {
                    uiSapperCount++;
                    if (uiSapperCount > 2)
                    {
                        bActive = false;
                        Talk(SAY_PHASE_3_1);
                        CompleteEncounter();
                    }
                }
            }

            void CompleteEncounter()
            {
                if (pInstance)
                {
                    // Achievement
                    pInstance->DoUpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET, SPELL_KILL_OZUMAT, 0, me); 
                    
                    // Guild Achievement
                    Map::PlayerList const &PlayerList = pInstance->instance->GetPlayers();
                    if (!PlayerList.isEmpty())
                    {
                        for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                        {/* 
                            if (Player* pPlayer = i->GetSource())
                                if (Group* pGroup = pPlayer->GetGroup())
                                    if (pPlayer->GetGuildId() && pGroup->IsGuildGroup(pPlayer->GetGuildId(), true, true))
                                    {
                                        pGroup->UpdateGuildAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET, SPELL_KILL_OZUMAT, 0, 0, NULL, me);
                                        break;
                                    }
                        */
                        }
                    }
                    pInstance->UpdateEncounterState(ENCOUNTER_CREDIT_CAST_SPELL, SPELL_ENCOUNTER_COMPLETE, me); 
                    pInstance->SetBossState(DATA_OZUMAT, DONE);
                }
                EnterEvadeMode();
            }

            void DamageTaken(Unit* /*pAttacker*/, uint32 &damage)
            {
                if (damage >= me->GetHealth())
                {
                    damage = 0;
                    Talk(SAY_DEATH);
                    EnterEvadeMode();
                }
            }

            void UpdateAI(uint32 diff)
            {
                if (!bActive)
                    return;

                if (me->HealthBelowPct(50) && !b50)
                {
                    b50 = true;
                    Talk(SAY_50);
                }
                if (me->HealthBelowPct(25) && !b25)
                {
                    b25 = true;
                    Talk(SAY_25);
                }

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_INTRO_2:
                        Talk(SAY_INTRO_2);
                        bActive = false;
                        break;
                    case EVENT_INTRO_3_2:
                        Talk(SAY_INTRO_3_2);
                        break;
                    case EVENT_PHASE_2_2:
                        Talk(SAY_PHASE_2_1);
                        break;
                    case EVENT_SUMMON_MINDLASHER:
                        if (Creature* pMindlasher = me->SummonCreature(NPC_VICIOUS_MINDLASHER, spawnPos[urand(0, 1)]))
                        {
                            pMindlasher->AddThreat(me, 1.0f);
                            pMindlasher->AI()->AttackStart(me);
                        }
                        break;
                    case EVENT_SUMMON_BEHEMOTH:
                        if (Creature* pBehemoth = me->SummonCreature(NPC_UNYIELDING_BEHEMOTH, spawnPos[urand(0, 1)]))
                        {
                            pBehemoth->AddThreat(me, 1.0f);
                            pBehemoth->AI()->AttackStart(me);
                        }
                        break;
                    case EVENT_SUMMON_SAPPER:
                        for (uint8 i = 2; i < 5; i++)
                            if (Creature* pSapper = me->SummonCreature(NPC_FACELESS_SAPPER, spawnPos[i]))
                                pSapper->CastSpell(me, SPELL_ENTANGLING_GRASP, false);
                        break;
                    case EVENT_SUMMON_BEAST:
                        if (Creature* pBeast = me->SummonCreature(NPC_BLIGHT_BEAST,
                            me->GetPositionX(),
                            me->GetPositionY(),
                            me->GetPositionZ(),
                            me->GetOrientation()))
                            if (Player* pTarget = GetRandomPlayer())
                                pBeast->AI()->AttackStart(pTarget);
                        events.ScheduleEvent(EVENT_SUMMON_BEAST, urand(15000, 24000));
                        break;
                    case EVENT_SUMMON_MURLOC:
                        for (uint8 i = 0; i < 5; i++)
                        {
                            if (Creature* pMurloc = me->SummonCreature(NPC_DEEP_MURLOC_INVADER, spawnPos[urand(0, 1)]))
                            {
                                pMurloc->AddThreat(me, 1.0f);
                                pMurloc->AI()->AttackStart(me);
                            }
                        }
                        events.ScheduleEvent(EVENT_SUMMON_MURLOC, urand(10000, 17000));
                        break;
                    case EVENT_BLIGHT_OF_OZUMAT:
                        if (Player* pTarget = GetRandomPlayer())
                            DoCast(pTarget, SPELL_BLIGHT_OF_OZUMAT_MISSILE);
                        events.ScheduleEvent(EVENT_BLIGHT_OF_OZUMAT, urand(10000, 18000));
                        break;
                    }
                }
            }         

            Player* GetRandomPlayer()
            {
                std::list<Player*> pAliveList;
                Map::PlayerList const &pPlayerList = me->GetMap()->GetPlayers();
                if (!pPlayerList.isEmpty())
                    for (Map::PlayerList::const_iterator itr = pPlayerList.begin(); itr != pPlayerList.end(); ++itr)
                        if (itr->GetSource()->IsAlive())
                            pAliveList.push_back(itr->GetSource());

                if (!pAliveList.empty())
                {
                    std::list<Player*>::const_iterator itr = pAliveList.begin();
                    std::advance(itr, rand() % pAliveList.size());
                    return (*itr);
                }
                return NULL;
            }

            bool isPlayerAlive()
            {
                Map::PlayerList const &pPlayerList = me->GetMap()->GetPlayers();

                if (!pPlayerList.isEmpty())
                    for (Map::PlayerList::const_iterator itr = pPlayerList.begin(); itr != pPlayerList.end(); ++itr)
                        if (itr->GetSource()->IsAlive())
                            return true;
                return false;
            };
        };        
};

// 44715
class npc_vicious_mindslasher : public CreatureScript
{
    public:
        npc_vicious_mindslasher() : CreatureScript("npc_vicious_mindslasher") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_vicious_mindslasherAI(creature);
        }

        struct npc_vicious_mindslasherAI : public ScriptedAI
        {
            npc_vicious_mindslasherAI(Creature* creature) : ScriptedAI(creature)
            {
                pInstance = creature->GetInstanceScript();
            }

            InstanceScript* pInstance;
            EventMap events;

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit* /*who*/)
            {
                events.ScheduleEvent(EVENT_BRAIN_SPIKE, urand(6000, 10000));
                if (IsHeroic())
                    events.ScheduleEvent(EVENT_VEIL_OF_SHADOW, urand(10000, 15000));
                events.ScheduleEvent(EVENT_SHADOW_BOLT, 2000);
            }

            void KilledUnit(Unit* /*victim*/)
            {
                if (pInstance)
                    if (Creature* pNeptulon = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_NEPTULON)))
                        pNeptulon->AI()->Talk(SAY_KILL);
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
                    case EVENT_BRAIN_SPIKE:
                        DoCast(me, SPELL_BRAIN_SPIKE);
                        events.ScheduleEvent(EVENT_BRAIN_SPIKE, urand(15000, 20000));
                        break;
                    case EVENT_VEIL_OF_SHADOW:
                        DoCastVictim(SPELL_VEIL_OF_SHADOW);
                        events.ScheduleEvent(EVENT_VEIL_OF_SHADOW, urand(13000, 20000));
                        break;
                    case EVENT_SHADOW_BOLT:
                        DoCastVictim(SPELL_SHADOW_BOLT);
                        events.ScheduleEvent(EVENT_SHADOW_BOLT, 2000);
                        break;
                    }
                }            
                DoMeleeAttackIfReady();
            }
        };
};

// 44648
class npc_unyielding_behemoth : public CreatureScript
{
    public:
        npc_unyielding_behemoth() : CreatureScript("npc_unyielding_behemoth") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_unyielding_behemothAI(creature);
        }

        struct npc_unyielding_behemothAI : public ScriptedAI
        {
            npc_unyielding_behemothAI(Creature* creature) : ScriptedAI(creature)
            {
                pInstance = creature->GetInstanceScript();
            }

            InstanceScript* pInstance;
            EventMap events;

            void Reset()
            {
                events.Reset();
            }

            void KilledUnit(Unit* /*victim*/)
            {
                if (pInstance)
                    if (Creature* pNeptulon = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_NEPTULON)))
                        pNeptulon->AI()->Talk(SAY_KILL);
            }

            void EnterCombat(Unit* /*who*/)
            {
                events.ScheduleEvent(EVENT_BLIGHT_SPRAY, urand(8000, 12000));
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
                    case EVENT_BLIGHT_SPRAY:
                        DoCast(me, SPELL_BLIGHT_SPRAY);
                        events.ScheduleEvent(EVENT_BLIGHT_SPRAY, urand(15000, 23000));
                        break;
                    }
                }            
                DoMeleeAttackIfReady();
            }
        };
};

// 44752
class npc_faceless_sapper : public CreatureScript
{
    public:
        npc_faceless_sapper() : CreatureScript("npc_faceless_sapper") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_faceless_sapperAI(creature);
        }

        struct npc_faceless_sapperAI : public ScriptedAI
        {
            npc_faceless_sapperAI(Creature* creature) : ScriptedAI(creature)
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
                me->SetReactState(REACT_PASSIVE);
            }

            void Reset() { }

            void UpdateAI(uint32 /*diff*/) { }
        };
};

// 44801 44834
class npc_blight_of_ozumat : public CreatureScript
{
    public:
        npc_blight_of_ozumat() : CreatureScript("npc_blight_of_ozumat") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_blight_of_ozumatAI (creature);
        }

        struct npc_blight_of_ozumatAI : public ScriptedAI
        {
            npc_blight_of_ozumatAI(Creature* creature) : ScriptedAI(creature)
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_PASSIVE);
            }

            void Reset()
            {
                DoCast(me, SPELL_BLIGHT_OF_OZUMAT_AURA);
            }

            void UpdateAI(uint32 /*diff*/) { }
        };
};

// ???
class at_tott_ozumat : public AreaTriggerScript
{
    public:
        at_tott_ozumat() : AreaTriggerScript("at_tott_ozumat") { }

        bool OnTrigger(Player* pPlayer, const AreaTriggerEntry* /*pAt*/)
        {
            if (InstanceScript* pInstance = pPlayer->GetInstanceScript())
            {
                if (pInstance->GetData(DATA_NEPTULON_EVENT) != DONE
                    && pInstance->GetBossState(DATA_OZUMAT) != IN_PROGRESS
                    && pInstance->GetBossState(DATA_OZUMAT) != DONE)
                {
                    pInstance->SetData(DATA_NEPTULON_EVENT, DONE);
                    if (Creature* pNeptulon = ObjectAccessor::GetCreature(*pPlayer, pInstance->GetData64(DATA_NEPTULON)))
                    {
                        pNeptulon->AI()->DoAction(ACTION_NEPTULON_START_EVENT);
                    }
                }
            }
            return true;
        }
};

void AddSC_boss_ozumat()
{
    new npc_neptulon();
    new npc_vicious_mindslasher();
    new npc_unyielding_behemoth();
    new npc_faceless_sapper();
    new npc_blight_of_ozumat();
    new at_tott_ozumat();
}