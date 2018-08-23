 /*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

/* ScriptData
SDName: Silverpine_Forest
SD%Complete: 100
SDComment: Quest support: 435
SDCategory: Silverpine Forest
EndScriptData */

/* ContentData
npc_deathstalker_erland
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "Player.h"
#include "Vehicle.h"
#include "VehicleDefines.h"


// 1978
class npc_deathstalker_erland : public CreatureScript
{
public:
    npc_deathstalker_erland() : CreatureScript("npc_deathstalker_erland") { }

    enum eErland
    {
        SAY_QUESTACCEPT = 0,
        SAY_START = 1,
        SAY_AGGRO = 2,
        SAY_PROGRESS = 3,
        SAY_LAST = 4,

        SAY_RANE = 0,
        SAY_RANE_ANSWER = 5,
        SAY_MOVE_QUINN = 6,

        SAY_QUINN = 7,
        SAY_QUINN_ANSWER = 0,
        SAY_BYE = 8,

        QUEST_ESCORTING = 435,
        NPC_RANE = 1950,
        NPC_QUINN = 1951
    };

    struct npc_deathstalker_erlandAI : public npc_escortAI
    {
        npc_deathstalker_erlandAI(Creature* creature) : npc_escortAI(creature) { }

        void WaypointReached(uint32 waypointId) override
        {
            Player* player = GetPlayerForEscort();
            if (!player)
                return;

            switch (waypointId)
            {
                case 1:
                    Talk(SAY_START, player);
                    break;
                case 10:
                    Talk(SAY_PROGRESS);
                    break;
                case 13:
                    Talk(SAY_LAST, player);
                    player->GroupEventHappens(QUEST_ESCORTING, me);
                    break;
                case 15:
                    if (Creature* rane = me->FindNearestCreature(NPC_RANE, 20.0f))
                        rane->AI()->Talk(SAY_RANE);
                    break;
                case 16:
                    Talk(SAY_RANE_ANSWER);
                    break;
                case 17:
                    Talk(SAY_MOVE_QUINN);
                    break;
                case 24:
                    Talk(SAY_QUINN);
                    break;
                case 25:
                    if (Creature* quinn = me->FindNearestCreature(NPC_QUINN, 20.0f))
                        quinn->AI()->Talk(SAY_QUINN_ANSWER);
                    break;
                case 26:
                    Talk(SAY_BYE);
                    break;
            }
        }

        void Reset() override { }

        void EnterCombat(Unit* who) override
        {
            Talk(SAY_AGGRO, who);
        }
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_ESCORTING)
        {
            creature->AI()->Talk(SAY_QUESTACCEPT, player);

            if (npc_escortAI* pEscortAI = CAST_AI(npc_deathstalker_erland::npc_deathstalker_erlandAI, creature->AI()))
                pEscortAI->Start(true, false, player->GetGUID());
        }

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_deathstalker_erlandAI(creature);
    }
};

// 44615 // quest 26965
class npc_grand_executor_mortuus_44615 : public CreatureScript
{
public:
    npc_grand_executor_mortuus_44615() : CreatureScript("npc_grand_executor_mortuus_44615") { }

    enum eNPC
    {
        QUEST_THE_WARCHIEF_COMETH_26965 = 26965,
        NPC_GARROSH_HELLSCREAM_44629 = 44629,
        NPC_HIGH_WARLORD_CROMUSH_44640 = 44640,
        NPC_LADY_SYLVANAS_WINDRUNNER_44365 = 44365, 
        NPC_HELLSCREEMS_ELITE_44636 = 44636,
        NPC_AGATHA_44608 = 44608,
        NPC_PORTAL_FROM_ORGRIMMAR_44630 = 44630,
        PLAYER_GUID = 99999,
        MOVE_CROMUSH_TO_SYLVANAS = 5405701,
        MOVE_CROMUSH_TO_HOME = 5405702,
        SPELL_RAISE_FORSAKEN = 83173,
        SPELL_AIR_REVENANT_ENTRANCE = 55761,
        SPELL_SIMPLE_TELEPORT = 12980,
        ACTION_START_ANIM = 101,
        EVENT_START_ANIM,
        EVENT_AGATHA_RAISE_FORSAKEN = 201,
        EVENT_TALK_SEQUENCE = 301,
        EVENT_SUMMON_PORTAL = 401,
        EVENT_SUMMON_GARROSH,
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_THE_WARCHIEF_COMETH_26965)
        {
            creature->GetAI()->SetGUID(player->GetGUID(), PLAYER_GUID);
            creature->GetAI()->DoAction(ACTION_START_ANIM);
            return true;
        }

        return false;
    }

    struct npc_grand_executor_mortuus_44615AI : public ScriptedAI
    {
        npc_grand_executor_mortuus_44615AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64  m_playerGUID;
        uint64  m_garroshGUID;
        uint64  m_cromushGUID;
        uint64  m_sylvanasGUID;
        uint64  m_agathaGUID;
        uint8   m_animPhase;
        std::list<uint64>spawnedList;
        std::list<uint64>portalList;

        void Reset() override
        {
            m_events.Reset();
            m_playerGUID = 0;
            m_garroshGUID = 0;
            m_cromushGUID = 0;
            m_sylvanasGUID = 0;
            m_agathaGUID = 0;
            m_animPhase = 0;
            spawnedList.clear();
            portalList.clear();
        }

        void JustSummoned(Creature* summon) override 
        { 
            spawnedList.push_back(summon->GetGUID());

            switch (summon->GetEntry())
            {
                case NPC_GARROSH_HELLSCREAM_44629:
                {
                    summon->CastSpell(summon, SPELL_SIMPLE_TELEPORT);
                    m_garroshGUID = summon->GetGUID();
                    break;
                }
                case NPC_HELLSCREEMS_ELITE_44636:
                {
                    summon->CastSpell(summon, SPELL_SIMPLE_TELEPORT);
                    break;
                }
                case NPC_PORTAL_FROM_ORGRIMMAR_44630:
                {
                    portalList.push_back(summon->GetGUID());
                    break;
                }
            }
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
                case PLAYER_GUID:
                {
                    m_playerGUID = guid;
                    break;
                }
            }
        }

        void DoAction(int32 param) override 
        { 
            switch (param)
            {
                case ACTION_START_ANIM:
                {
                    if (!m_animPhase)
                    {
                        if (Creature* cromush = me->FindNearestCreature(NPC_HIGH_WARLORD_CROMUSH_44640, 50.0f))
                            if (Creature* sylvanas = me->FindNearestCreature(NPC_LADY_SYLVANAS_WINDRUNNER_44365, 10.0f))
                                if (Creature* agatha = me->FindNearestCreature(NPC_AGATHA_44608, 25.0f))
                                {
                                    m_animPhase = 1;
                                    cromush->GetMotionMaster()->MovePath(5405701, false);
                                    m_cromushGUID = cromush->GetGUID();
                                    m_sylvanasGUID = sylvanas->GetGUID();
                                    m_agathaGUID = agatha->GetGUID();
                                    m_events.ScheduleEvent(EVENT_START_ANIM, 2000);
                                }
                    }
                    break; 
                }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_START_ANIM:
                    {
                        m_events.ScheduleEvent(EVENT_TALK_SEQUENCE, 1000);
                        m_events.ScheduleEvent(EVENT_SUMMON_PORTAL, 4000);
                        m_events.ScheduleEvent(EVENT_SUMMON_GARROSH, 5500);
                        break;
                    }
                    case EVENT_SUMMON_PORTAL:
                    {
                        SummonPortalsFromOrgrimmar();
                        break;
                    }
                    case EVENT_SUMMON_GARROSH:
                    {
                        SummonGarroshAndHisEliteGuards();
                        break;
                    }
                    case EVENT_TALK_SEQUENCE:
                    {
                        if (Creature* sylvanas = sObjectAccessor->GetCreature(*me, m_sylvanasGUID))
                            sylvanas->AI()->Talk(0);

                        m_events.ScheduleEvent(EVENT_TALK_SEQUENCE + 1, 6000);
                        break;
                    }
                    case EVENT_TALK_SEQUENCE + 1:
                    {
                        if (Creature* sylvanas = sObjectAccessor->GetCreature(*me, m_sylvanasGUID))
                            sylvanas->AI()->Talk(1);
                        if (Creature* garrosh = sObjectAccessor->GetCreature(*me, m_garroshGUID))
                            garrosh->GetMotionMaster()->MoveJump(1378.65f, 1044.23f, 53.8389f, 15.0f, 10.0f);
                        m_events.ScheduleEvent(EVENT_TALK_SEQUENCE + 2, 5000);
                        break;
                    }
                    case EVENT_TALK_SEQUENCE + 2:
                    {
                        if (Creature* garrosh = sObjectAccessor->GetCreature(*me, m_garroshGUID))
                            garrosh->AI()->Talk(0);
                        m_events.ScheduleEvent(EVENT_TALK_SEQUENCE + 3, 12000);
                        break;
                    }
                    case EVENT_TALK_SEQUENCE + 3:
                    {
                        if (Creature* garrosh = sObjectAccessor->GetCreature(*me, m_garroshGUID))
                            garrosh->AI()->Talk(1);
                        m_events.ScheduleEvent(EVENT_TALK_SEQUENCE + 4, 7000);
                        break;
                    }
                    case EVENT_TALK_SEQUENCE + 4:
                    {
                        if (Creature* sylvanas = sObjectAccessor->GetCreature(*me, m_sylvanasGUID))
                            sylvanas->AI()->Talk(2);
                        m_events.ScheduleEvent(EVENT_TALK_SEQUENCE + 5, 5000);
                        break;
                    }
                    case EVENT_TALK_SEQUENCE + 5:
                    {
                        if (Creature* sylvanas = sObjectAccessor->GetCreature(*me, m_sylvanasGUID))
                            sylvanas->AI()->Talk(3);
                        m_events.ScheduleEvent(EVENT_TALK_SEQUENCE + 6, 14000);
                        break;
                    }
                    case EVENT_TALK_SEQUENCE + 6:
                    {
                        if (Creature* sylvanas = sObjectAccessor->GetCreature(*me, m_sylvanasGUID))
                            sylvanas->AI()->Talk(4);
                        m_events.ScheduleEvent(EVENT_TALK_SEQUENCE + 7, 5000);
                        break;
                    }
                    case EVENT_TALK_SEQUENCE + 7:
                    {
                        if (Creature* garrosh = sObjectAccessor->GetCreature(*me, m_garroshGUID))
                            garrosh->AI()->Talk(2);
                        m_events.ScheduleEvent(EVENT_TALK_SEQUENCE + 8, 5000);
                        break;
                    }
                    case EVENT_TALK_SEQUENCE + 8:
                    {
                        if (Creature* sylvanas = sObjectAccessor->GetCreature(*me, m_sylvanasGUID))
                            sylvanas->AI()->Talk(5);
                        m_events.ScheduleEvent(EVENT_TALK_SEQUENCE + 9, 6000);
                        break;
                    }
                    case EVENT_TALK_SEQUENCE + 9:
                    {
                        if (Creature* sylvanas = sObjectAccessor->GetCreature(*me, m_sylvanasGUID))
                            sylvanas->AI()->Talk(6);
                        m_events.ScheduleEvent(EVENT_TALK_SEQUENCE + 10, 6000);
                        break;
                    }
                    case EVENT_TALK_SEQUENCE + 10:
                    {
                        if (Creature* sylvanas = sObjectAccessor->GetCreature(*me, m_sylvanasGUID))
                            sylvanas->AI()->Talk(7);
                        m_events.ScheduleEvent(EVENT_TALK_SEQUENCE + 11, 8000);
                        break;
                    }
                    case EVENT_TALK_SEQUENCE + 11:
                    {
                        if (Creature* sylvanas = sObjectAccessor->GetCreature(*me, m_sylvanasGUID))
                            sylvanas->AI()->Talk(8);
                        m_events.ScheduleEvent(EVENT_AGATHA_RAISE_FORSAKEN, 2000);
                        break;
                    }
                    case EVENT_AGATHA_RAISE_FORSAKEN:
                    {
                        if (Creature* agatha = sObjectAccessor->GetCreature(*me, m_agathaGUID))
                            agatha->GetMotionMaster()->MovePoint(1235, 1367.02f, 1031.54f, 55.9914f);

                        m_events.ScheduleEvent(EVENT_AGATHA_RAISE_FORSAKEN + 1, 6000);
                        break;
                    }
                    case EVENT_AGATHA_RAISE_FORSAKEN + 1:
                    {
                        if (Creature* agatha = sObjectAccessor->GetCreature(*me, m_agathaGUID))
                            agatha->CastSpell(1368.65f, 1032.19f, 63.3033f, SPELL_RAISE_FORSAKEN, true);

                        m_events.ScheduleEvent(EVENT_TALK_SEQUENCE + 12, 9000);
                        break;
                    }
                    case EVENT_TALK_SEQUENCE + 12:
                    {
                        if (Creature* cromush = sObjectAccessor->GetCreature(*me, m_cromushGUID))
                            cromush->AI()->Talk(0);
                        m_events.ScheduleEvent(EVENT_TALK_SEQUENCE + 13, 6000);
                        break;
                    }
                    case EVENT_TALK_SEQUENCE + 13:
                    {
                        if (Creature* garrosh = sObjectAccessor->GetCreature(*me, m_garroshGUID))
                            garrosh->AI()->Talk(3);
                        m_events.ScheduleEvent(EVENT_TALK_SEQUENCE + 14, 14000);
                        break;
                    }
                    case EVENT_TALK_SEQUENCE + 14:
                    {
                        if (Creature* agatha = sObjectAccessor->GetCreature(*me, m_agathaGUID))
                            agatha->GetMotionMaster()->MovePoint(1236, agatha->GetHomePosition());

                        if (Creature* sylvanas = sObjectAccessor->GetCreature(*me, m_sylvanasGUID))
                            sylvanas->AI()->Talk(9);
                        m_events.ScheduleEvent(EVENT_TALK_SEQUENCE + 15, 10000);
                        break;
                    }
                    case EVENT_TALK_SEQUENCE + 15:
                    {
                        if (Creature* agatha = sObjectAccessor->GetCreature(*me, m_agathaGUID))
                            agatha->SetFacingTo(0.855211f);
                        if (Creature* garrosh = sObjectAccessor->GetCreature(*me, m_garroshGUID))
                            garrosh->AI()->Talk(4);
                        m_events.ScheduleEvent(EVENT_TALK_SEQUENCE + 16, 6000);
                        break;
                    }
                    case EVENT_TALK_SEQUENCE + 16:
                    {
                        if (Creature* garrosh = sObjectAccessor->GetCreature(*me, m_garroshGUID))
                            garrosh->AI()->Talk(5);
                        m_events.ScheduleEvent(EVENT_TALK_SEQUENCE + 17, 6000);
                        break;
                    }
                    case EVENT_TALK_SEQUENCE + 17:
                    {
                        if (Creature* sylvanas = sObjectAccessor->GetCreature(*me, m_sylvanasGUID))
                            sylvanas->AI()->Talk(10);
                        m_events.ScheduleEvent(EVENT_TALK_SEQUENCE + 18, 6000);
                        break;
                    }
                    case EVENT_TALK_SEQUENCE + 18:
                    {
                        if (Creature* garrosh = sObjectAccessor->GetCreature(*me, m_garroshGUID))
                            garrosh->AI()->Talk(6);
                        m_events.ScheduleEvent(EVENT_TALK_SEQUENCE + 19, 6000);
                        break;
                    }
                    case EVENT_TALK_SEQUENCE + 19:
                    {
                        if (Creature* garrosh = sObjectAccessor->GetCreature(*me, m_garroshGUID))
                            garrosh->AI()->Talk(7);
                        m_events.ScheduleEvent(EVENT_TALK_SEQUENCE + 20, 17000);
                        break;
                    }
                    case EVENT_TALK_SEQUENCE + 20:
                    {
                        if (Creature* cromush = sObjectAccessor->GetCreature(*me, m_cromushGUID))
                            cromush->AI()->Talk(1);
                        m_events.ScheduleEvent(EVENT_TALK_SEQUENCE + 21, 5000);
                        break;
                    }
                    case EVENT_TALK_SEQUENCE + 21:
                    {
                        if (Creature* garrosh = sObjectAccessor->GetCreature(*me, m_garroshGUID))
                            garrosh->AI()->Talk(8);
                        m_events.ScheduleEvent(EVENT_TALK_SEQUENCE + 22, 15000);
                        break;
                    }
                    case EVENT_TALK_SEQUENCE + 22:
                    {
                        if (Creature* cromush = sObjectAccessor->GetCreature(*me, m_cromushGUID))
                            cromush->GetMotionMaster()->MovePath(5405702, false);
                        if (Creature* garrosh = sObjectAccessor->GetCreature(*me, m_garroshGUID))
                            garrosh->GetMotionMaster()->MovePoint(1234, 1357.04f, 1056.93f, 52.95f);                        
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                            player->KilledMonsterCredit(NPC_GARROSH_HELLSCREAM_44629);
                        m_events.ScheduleEvent(EVENT_TALK_SEQUENCE + 23, 8000);
                        break;
                    }
                    case EVENT_TALK_SEQUENCE + 23:
                    {
                        RemoveAllSpawnedCreatures();
                        Reset();
                        break;
                    }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void SummonPortalsFromOrgrimmar()
        {
            me->SummonCreature(NPC_PORTAL_FROM_ORGRIMMAR_44630, 1358.62f, 1054.72f, 53.1200f, 0, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_PORTAL_FROM_ORGRIMMAR_44630, 1393.27f, 1021.20f, 53.2225f, 0, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_PORTAL_FROM_ORGRIMMAR_44630, 1404.71f, 1063.73f, 60.5617f, 0, TEMPSUMMON_TIMED_DESPAWN, 300000);
        }

        void SummonGarroshAndHisEliteGuards()
        {
            for (std::list<uint64>::const_iterator itr = portalList.begin(); itr != portalList.end(); itr++)
                if (Creature* portal = sObjectAccessor->GetCreature(*me, (*itr)))
                    portal->CastSpell(portal, SPELL_AIR_REVENANT_ENTRANCE);

            me->SummonCreature(NPC_HELLSCREEMS_ELITE_44636, 1387.90f, 1029.71f, 53.21853f, 2.827433f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE_44636, 1389.79f, 1024.51f, 53.20833f, 2.827433f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE_44636, 1388.05f, 1026.91f, 53.20833f, 2.827433f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE_44636, 1388.16f, 1020.88f, 53.25523f, 2.827433f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE_44636, 1385.79f, 1025.99f, 53.22593f, 2.827433f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE_44636, 1386.69f, 1023.26f, 53.24393f, 2.827433f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE_44636, 1384.33f, 1022.04f, 53.28123f, 2.827433f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE_44636, 1391.10f, 1027.73f, 53.20483f, 2.827433f, TEMPSUMMON_TIMED_DESPAWN, 300000);

            me->SummonCreature(NPC_HELLSCREEMS_ELITE_44636, 1359.10f, 1046.55f, 52.97053f, 5.253441f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE_44636, 1360.89f, 1051.81f, 53.19793f, 5.253441f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE_44636, 1360.75f, 1048.84f, 53.12893f, 5.253441f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE_44636, 1364.43f, 1053.62f, 53.29343f, 5.253441f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE_44636, 1363.08f, 1048.15f, 53.22223f, 5.253441f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE_44636, 1364.08f, 1050.84f, 53.29163f, 5.253441f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE_44636, 1366.69f, 1050.31f, 53.34203f, 5.253441f, TEMPSUMMON_TIMED_DESPAWN, 300000);
            me->SummonCreature(NPC_HELLSCREEMS_ELITE_44636, 1357.85f, 1050.12f, 52.99823f, 5.253441f, TEMPSUMMON_TIMED_DESPAWN, 300000);

            me->SummonCreature(NPC_GARROSH_HELLSCREAM_44629, 1402.45f, 1061.62f, 60.56173f, 3.926991f, TEMPSUMMON_TIMED_DESPAWN, 300000);
        }

        void RemoveAllSpawnedCreatures()
        {
            for (std::list<uint64>::const_iterator itr = spawnedList.begin(); itr != spawnedList.end(); itr++)
                if (Creature* npc = sObjectAccessor->GetCreature(*me, (*itr)))
                    npc->DespawnOrUnsummon(1);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_grand_executor_mortuus_44615AI(creature);
    }
};

// 83173 // quest 26965
class spell_raise_forsaken_83173 : public SpellScriptLoader
{
public:
    spell_raise_forsaken_83173() : SpellScriptLoader("spell_raise_forsaken_83173") { }

    enum eSpell
    {
        NPC_FALLEN_HUMAN_44592 = 44592,
        NPC_FALLEN_HUMAN_44593 = 44593,
        SPELL_FEIGNED = 80636,
    };

    class IsNotInEntryList
    {
    public:
        explicit IsNotInEntryList(std::list<uint32>entrys) : _entrys(entrys) { }

        bool operator()(WorldObject* obj) const
        {
            if (Creature* target = obj->ToCreature())
                for (std::list<uint32>::const_iterator itr = _entrys.begin(); itr != _entrys.end(); ++itr)
                    if (target->GetEntry() == *itr)
                        return false;

            return true;
        }

    private:
        std::list<uint32> _entrys;
    };

    class spell_raise_forsaken_83173_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_raise_forsaken_83173_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            std::list<uint32>entrys;
            entrys.push_back(NPC_FALLEN_HUMAN_44592);
            entrys.push_back(NPC_FALLEN_HUMAN_44593);
            targets.remove_if(IsNotInEntryList(entrys));
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_raise_forsaken_83173_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_raise_forsaken_83173_SpellScript();
    }

    class spell_raise_forsaken_83173_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_raise_forsaken_83173_AuraScript);

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* unit = GetTarget())
                if (Creature* fallenHuman = unit->ToCreature())
                {
                    fallenHuman->SetHover(true);
                    fallenHuman->SetFloatValue(UNIT_FIELD_HOVERHEIGHT, frand(1.8f, 2.2f));
                }
        }

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* unit = GetTarget())
                if (Creature* fallenHuman = unit->ToCreature())
                {
                    fallenHuman->SetHover(false);
                    fallenHuman->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
                    fallenHuman->RemoveAura(SPELL_FEIGNED);
                    fallenHuman->CastSpell(fallenHuman, 83149, true);
                }
        }

        void Register() override
        {
            OnEffectApply += AuraEffectApplyFn(spell_raise_forsaken_83173_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            AfterEffectRemove += AuraEffectRemoveFn(spell_raise_forsaken_83173_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_raise_forsaken_83173_AuraScript();
    }
};

// 83149 // quest 26965
class spell_forsaken_trooper_master_script_83149 : public SpellScriptLoader
{
public:
    spell_forsaken_trooper_master_script_83149() : SpellScriptLoader("spell_forsaken_trooper_master_script_83149") { }

    enum eSpell
    {
        SPELL_FORSAKEN_TROOPER_MALE_01 = 83150,
        SPELL_FORSAKEN_TROOPER_MALE_02 = 83163,
        SPELL_FORSAKEN_TROOPER_MALE_03 = 83164,
        SPELL_FORSAKEN_TROOPER_MALE_04 = 83165,
        SPELL_FORSAKEN_TROOPER_FEMALE_01 = 83152,
        SPELL_FORSAKEN_TROOPER_FEMALE_02 = 83166,
        SPELL_FORSAKEN_TROOPER_FEMALE_03 = 83167,
        SPELL_FORSAKEN_TROOPER_FEMALE_04 = 83168,

    };

    class spell_forsaken_trooper_master_script_83149_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_forsaken_trooper_master_script_83149_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* unit = GetCaster())
                if (Creature* fallenHuman = unit->ToCreature())
                {
                    uint32 rol = RAND(83150, 83163, 83164, 83165, 83152, 83166, 83167, 83168);
                    fallenHuman->CastSpell(fallenHuman, rol, true);
                    fallenHuman->DespawnOrUnsummon(100000);
                }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_forsaken_trooper_master_script_83149_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_forsaken_trooper_master_script_83149_SpellScript();
    }
};

// 44592 44593 // quest 26965
class npc_fallen_human_44592 : public CreatureScript
{
public:
    npc_fallen_human_44592() : CreatureScript("npc_fallen_human_44592") { }

    enum eSpell
    {
        SPELL_FEIGNED = 80636,
    };

    struct npc_fallen_human_44592AI : public ScriptedAI
    {
        npc_fallen_human_44592AI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            me->AddAura(SPELL_FEIGNED, me);
            me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_fallen_human_44592AI(creature);
    }
};

// 44793 // showfight vs trooper
class npc_worgen_renegade_44793 : public CreatureScript
{
public:
    npc_worgen_renegade_44793() : CreatureScript("npc_worgen_renegade_44793") { }

    enum eNPC
    {
        NPC_FORSAKEN_TROOPER1 = 44791,
        NPC_FORSAKEN_TROOPER2 = 44792,
        EVENT_CHECK_SHOWFIGHT = 101,
        MOVE_TO_HOMEPOSITION,
    };

    struct npc_worgen_renegade_44793AI : public ScriptedAI
    {
        npc_worgen_renegade_44793AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        float    m_minHealthPct;
        bool     m_isShowFight;
        uint32    m_minDamage;
        uint32    m_maxDamage;
        std::list<uint32> m_targetList;

        void Initialize()
        {
            m_targetList.clear();
            m_targetList.push_back(NPC_FORSAKEN_TROOPER1);
            m_targetList.push_back(NPC_FORSAKEN_TROOPER2);
            m_minHealthPct = frand(30.0f, 85.0f);
            m_minDamage = 1;
            m_maxDamage = 1;
        }

        void Reset() override
        {
            m_events.Reset();
            m_isShowFight = true;
            m_events.ScheduleEvent(EVENT_CHECK_SHOWFIGHT, 1000);
        }

        void MovementInform(uint32 type, uint32 pointId) override
        {
            if (type == POINT_MOTION_TYPE && pointId == MOVE_TO_HOMEPOSITION)
                m_events.ScheduleEvent(EVENT_CHECK_SHOWFIGHT, 25);
        }

        uint32 FindTargetEntry(uint32 entry)
        {
            if (m_targetList.empty())
                return 0;

            for (std::list<uint32>::const_iterator itr = m_targetList.begin(); itr != m_targetList.end(); ++itr)
                if ((*itr) == entry)
                    return entry;

            return 0;
        }

        void DamageTaken(Unit* who, uint32 &damage) override
        {
            if (m_isShowFight && who->ToCreature())
                if (FindTargetEntry(who->GetEntry()))
                {
                    if (damage > m_maxDamage)
                        damage = m_maxDamage;

                    if (me->GetHealthPct() < m_minHealthPct)
                        damage = 0;
                }

        }

        void DamageDealt(Unit* victim, uint32& damage, DamageEffectType damageType) override
        {
            if (m_isShowFight && victim->ToCreature())
                if (FindTargetEntry(victim->GetEntry()))
                {
                    if (damage > m_maxDamage)
                        damage = m_maxDamage;

                    if (victim->GetHealthPct() < m_minHealthPct)
                        damage = m_minDamage;
                }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_SHOWFIGHT:
                {
                    if (me->IsInCombat() || me->IsDead())
                    {
                        m_events.ScheduleEvent(EVENT_CHECK_SHOWFIGHT, 2500);
                        return;
                    }

                    if (me->GetDistance2d(me->GetHomePosition().GetPositionX(), me->GetHomePosition().GetPositionY()) > 10.0f)
                    {
                        me->GetMotionMaster()->MovePoint(MOVE_TO_HOMEPOSITION, me->GetHomePosition());
                        return;
                    }

                    if (Creature* worgen = me->FindNearestCreature(m_targetList, 5.0f))
                    {
                        me->Attack(worgen, true);
                        worgen->Attack(me, true);
                        m_events.ScheduleEvent(EVENT_CHECK_SHOWFIGHT, 2500);
                        return;
                    }

                    m_events.ScheduleEvent(EVENT_CHECK_SHOWFIGHT, 2500);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_worgen_renegade_44793AI(creature);
    }
};

// 44791 // 44792
class npc_forsaken_trooper_44791 : public CreatureScript
{
public:
    npc_forsaken_trooper_44791() : CreatureScript("npc_forsaken_trooper_44791") { }

    enum eNPC
    {
        NPC_WORGEN_RENEGATE = 44793,
        EVENT_CHECK_SHOWFIGHT = 101,
        MOVE_TO_HOMEPOSITION,
    };

    struct npc_forsaken_trooper_44791AI : public ScriptedAI
    {
        npc_forsaken_trooper_44791AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        float    m_minHealthPct;
        bool     m_isShowFight;
        uint32    m_minDamage;
        uint32    m_maxDamage;

        void Initialize()
        {
            m_minHealthPct = frand(30.0f, 85.0f);
            m_minDamage = 1;
            m_maxDamage = 1;
        }

        void Reset() override
        {
            m_events.Reset();
            m_isShowFight = true;
            m_events.ScheduleEvent(EVENT_CHECK_SHOWFIGHT, 1000);
        }

        void MovementInform(uint32 type, uint32 pointId) override
        {
            if (type == POINT_MOTION_TYPE && pointId == MOVE_TO_HOMEPOSITION)
                m_events.ScheduleEvent(EVENT_CHECK_SHOWFIGHT, 25);
        }

        void DamageTaken(Unit* who, uint32 &damage) override
        {
            if (m_isShowFight && who->ToCreature())
                if (who->GetEntry() == NPC_WORGEN_RENEGATE)
                {
                    if (damage > m_maxDamage)
                        damage = m_maxDamage;

                    if (me->GetHealthPct() < m_minHealthPct)
                        damage = 0;
                }

        }

        void DamageDealt(Unit* victim, uint32& damage, DamageEffectType damageType) override
        {
            if (m_isShowFight && victim->ToCreature())
                if (victim->GetEntry() == NPC_WORGEN_RENEGATE)
                {
                    if (damage > m_maxDamage)
                        damage = m_maxDamage;

                    if (victim->GetHealthPct() < m_minHealthPct)
                        damage = m_minDamage;
                }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_SHOWFIGHT:
                {
                    if (me->IsInCombat() || me->IsDead())
                    {
                        m_events.ScheduleEvent(EVENT_CHECK_SHOWFIGHT, 2500);
                        return;
                    }

                    if (me->GetDistance2d(me->GetHomePosition().GetPositionX(), me->GetHomePosition().GetPositionY()) > 10.0f)
                    {
                        me->GetMotionMaster()->MovePoint(MOVE_TO_HOMEPOSITION, me->GetHomePosition());
                        return;
                    }

                    if (Creature* worgen = me->FindNearestCreature(NPC_WORGEN_RENEGATE, 5.0f))
                    {
                        me->Attack(worgen, true);
                        worgen->Attack(me, true);
                        m_events.ScheduleEvent(EVENT_CHECK_SHOWFIGHT, 2500);
                        return;
                    }

                    m_events.ScheduleEvent(EVENT_CHECK_SHOWFIGHT, 2500);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_forsaken_trooper_44791AI(creature);
    }
};

// 44825 // quest 26998
class npc_bat_handler_maggotbreath_44825 : public CreatureScript
{
public:
    npc_bat_handler_maggotbreath_44825() : CreatureScript("npc_bat_handler_maggotbreath_44825") { }

    enum eNPC
    {
        QUEST_ITERATING_UPON_SUCCESS = 26998,
        SPELL_SUMMON_BAT = 83584,
        ACTION_OPTION_ID = 1,
    };

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        switch (action) 
        {
        case ACTION_OPTION_ID:
        {
            if (player->GetQuestStatus(QUEST_ITERATING_UPON_SUCCESS) == QUEST_STATUS_INCOMPLETE)
            {
                player->CastSpell(player, SPELL_SUMMON_BAT);
                creature->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                creature->AI()->Talk(0);
                break;
            }
        }
        }
        player->CLOSE_GOSSIP_MENU();
        
        return true;
    }
};

// 44821 // quest 26998
class npc_forsaken_bat_44821 : public CreatureScript
{
public:
    npc_forsaken_bat_44821() : CreatureScript("npc_forsaken_bat_44821") { }

    enum eNPC
    {
        QUEST_ITERATING_UPON_SUCCESS = 26998,
        NPC_VILE_FIN_ORACLE = 1908,
        NPC_BAT_HANDLER_MAGGOTBREATH = 44825,
        WAYPOINT_QUEST_26998 = 4482101,
        SPELL_GO_HOME = 83594,
        EVENT_CHECK_FINISH = 101,
        EVENT_START_MOVEMENT,
        EVENT_GO_HOME2,
        EVENT_GO_HOME,
    };

    struct npc_forsaken_bat_44821AI : public VehicleAI
    {
        npc_forsaken_bat_44821AI(Creature* creature) : VehicleAI(creature) { Initialize(); }

        EventMap m_events;
        uint64 m_playerGUID;
        Position m_homePos;
        Position m_homePos2;

        void Initialize()
        {
            m_playerGUID = 0;
            m_events.Reset();
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
                if (player->GetQuestStatus(QUEST_ITERATING_UPON_SUCCESS) == QUEST_STATUS_INCOMPLETE)
                    if (Vehicle* vehicle = me->GetVehicleKit())
                    {
                        m_playerGUID = player->GetGUID();
                        m_homePos = me->GetPosition();
                    }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == WAYPOINT_MOTION_TYPE)
                switch (id)
                {
                case 0:
                {
                    me->SetSpeed(MOVE_RUN, 3.9f, true);
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        player->KilledMonsterCredit(NPC_BAT_HANDLER_MAGGOTBREATH);
                    break;
                }
                case 1:
                {
                    m_homePos2 = me->GetPosition();
                    m_homePos2.m_positionZ += 40.0f;
                    break;
                }
                case 4:
                {
                    me->SetSpeed(MOVE_RUN, 2.4f, true);
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        Talk(0, player);
                    break;
                }
                }
            if (type == POINT_MOTION_TYPE)
                if (id == 1234)
                    m_events.ScheduleEvent(EVENT_GO_HOME, 10);
                else if (id == 1236)
                {
                    me->GetVehicleKit()->RemoveAllPassengers();
                    me->DespawnOrUnsummon(100);
                }
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override 
        { 
            if (apply)
                if (Player* player = passenger->ToPlayer())
                    if (player->GetQuestStatus(QUEST_ITERATING_UPON_SUCCESS) == QUEST_STATUS_INCOMPLETE)
                    {
                        m_playerGUID = player->GetGUID();                        
                        m_events.ScheduleEvent(EVENT_START_MOVEMENT, 2000);
                        return;
                    }

            m_playerGUID = 0;
        }

        void EnterEvadeMode() override {}

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_FINISH:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        if (player->GetReqKillOrCastCurrentCount(QUEST_ITERATING_UPON_SUCCESS, NPC_VILE_FIN_ORACLE) >= 50)
                        {
                            Talk(1, player);
                            me->CastSpell(me, SPELL_GO_HOME, true);
                            me->GetMotionMaster()->Clear();
                            m_events.ScheduleEvent(EVENT_GO_HOME2, 250);
                            return;
                        }

                    m_events.ScheduleEvent(EVENT_CHECK_FINISH, 1000);
                    break;
                }
                case EVENT_START_MOVEMENT:
                {
                    me->SetCanFly(true);
                    me->SetDisableGravity(true);
                    me->GetMotionMaster()->MovePath(WAYPOINT_QUEST_26998, false);
                    m_events.ScheduleEvent(EVENT_CHECK_FINISH, 1000);
                    break;
                }
                case EVENT_GO_HOME2:
                {
                    me->SetSpeed(MOVE_RUN, 3.5f);
                    me->GetMotionMaster()->MovePoint(1234, m_homePos2);
                    break;
                }
                case EVENT_GO_HOME:
                {
                    me->SetSpeed(MOVE_RUN, 2.0f);
                    me->GetMotionMaster()->MovePoint(1236, m_homePos);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_forsaken_bat_44821AI(creature);
    }
};

// 205143 // quest 27045
class go_abandoned_outhouse_205143 : public GameObjectScript
{
public:
    go_abandoned_outhouse_205143() : GameObjectScript("go_abandoned_outhouse_205143") { }

    enum eGameObject
    {
        QUEST_WAITING_TO_EXSANGUINATE = 27045,
        SPELL_SUMMON_DEATHSTALKER_YORICK = 83751,
    };

    bool OnQuestAccept(Player* player, GameObject* go, Quest const* quest) override
    { 
        if (quest->GetQuestId() == QUEST_WAITING_TO_EXSANGUINATE)
            player->CastSpell(1301.87f, 1189.36f, 52.1045f, SPELL_SUMMON_DEATHSTALKER_YORICK, true, 0, 0, player->GetGUID());

        return false; 
    }
};

// 44882 // quest 27045
class npc_deathstalker_rane_yorick_44882 : public CreatureScript
{
public:
    npc_deathstalker_rane_yorick_44882() : CreatureScript("npc_deathstalker_rane_yorick_44882") { }

    enum eNPC
    {
        NPC_DEATHSTALKER_RANE_YORICK = 44882,
        NPC_ARMOIRE_IN_ROOM = 44894,
        NPC_ARMOIRE_SUMMONED = 44893,
        NPC_PACKLEADER_IVAR_BLOODFANG = 44884,
        SPELL_STEALTH = 34189,
        SPELL_PERMANENT_FEIGN_DEATH = 29266,
        WAYPOINTS_UP = 4488201,
        MOVEPOINT_HIDDEN_PLACE = 1234,
        EVENT_START_ANIM = 101,
        EVENT_WAIT_ON_PLAYER,
        EVENT_TALK_TO_PLAYER,
        EVENT_HIDE,
        EVENT_SET_FACE_TO_BLOODFANG,
        EVENT_RANE_LAST_MOVE,
        ACTION_RANE_JUMP_DEATH = 2,
    };

    struct npc_deathstalker_rane_yorick_44882AI : public ScriptedAI
    {
        npc_deathstalker_rane_yorick_44882AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_bloodfangGUID;

        void Initialize()
        {
            m_playerGUID = 0;
            m_bloodfangGUID = 0;
            m_events.Reset();
        }

        void IsSummonedBy(Unit* summoner) override 
        { 
            if (Player* player = summoner->ToPlayer())
                m_playerGUID = player->GetGUID();
            m_events.ScheduleEvent(EVENT_START_ANIM, 1000);
        }

        void MovementInform(uint32 type, uint32 id) override 
        {
            if (type == WAYPOINT_MOTION_TYPE)
                switch (id)
                {
                case 1:
                {
                    Talk(0);
                    break;
                }
                case 15:
                {
                    m_events.ScheduleEvent(EVENT_WAIT_ON_PLAYER, 1000);
                    break;
                }
                }
            if (type == POINT_MOTION_TYPE)
                switch (id)
                {
                case MOVEPOINT_HIDDEN_PLACE:
                {
                    me->SetFacingTo(4.8f);
                    break;
                }
                }
        }

        void DoAction(int32 param) override 
        { 
            switch (param)
            {
            case ACTION_RANE_JUMP_DEATH:
                m_events.ScheduleEvent(EVENT_RANE_LAST_MOVE, 10);
                break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_ANIM:
                {
                    me->GetMotionMaster()->MovePath(WAYPOINTS_UP, false);
                    break;
                }
                case EVENT_WAIT_ON_PLAYER:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        if (abs(player->GetPositionZ() - me->GetPositionZ()) < 0.1f && player->GetDistance2d(me) < 5.0f)
                            m_events.ScheduleEvent(EVENT_TALK_TO_PLAYER, 1000);
                        else
                            m_events.ScheduleEvent(EVENT_WAIT_ON_PLAYER, 1000);
                    break;
                }
                case EVENT_TALK_TO_PLAYER:
                {
                    Talk(1);
                    m_events.ScheduleEvent(EVENT_HIDE, 3000);
                    m_events.ScheduleEvent(EVENT_SET_FACE_TO_BLOODFANG, 5000);
                    break;
                }
                case EVENT_HIDE:
                {
                    me->GetMotionMaster()->MovePoint(MOVEPOINT_HIDDEN_PLACE, 1313.515f, 1212.22f, 58.4988f);
                    me->CastSpell(me, SPELL_STEALTH);                   
                    break;
                }
                case EVENT_SET_FACE_TO_BLOODFANG:
                {
                    if (!m_bloodfangGUID)
                        if (Creature* ivar = me->FindNearestCreature(NPC_PACKLEADER_IVAR_BLOODFANG, 25.0f))
                            m_bloodfangGUID = ivar->GetGUID();

                    if (Creature* ivar = sObjectAccessor->GetCreature(*me, m_bloodfangGUID))
                        me->SetFacingToObject(ivar);

                    m_events.ScheduleEvent(EVENT_SET_FACE_TO_BLOODFANG, 1000);
                    break;
                }
                case EVENT_RANE_LAST_MOVE:
                {
                    me->MonsterMoveWithSpeed(1299.025f, 1206.724f, 59.64236f, 5.0f);
                    m_events.ScheduleEvent(EVENT_RANE_LAST_MOVE + 1, 1000);
                    break;
                }
                case EVENT_RANE_LAST_MOVE + 1:
                {
                    me->SetDisableGravity(false);
                    me->AddAura(SPELL_PERMANENT_FEIGN_DEATH, me);
                    me->DespawnOrUnsummon(60000);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_deathstalker_rane_yorick_44882AI(creature);
    }
};

// 44893 // quest 27045
class npc_armoire_44893 : public CreatureScript
{
public:
    npc_armoire_44893() : CreatureScript("npc_armoire_44893") { }

    enum eNPC
    {
        NPC_RANE_YORICK = 44882,
        NPC_LORD_DARIUS_CROWLEY = 44883,
        NPC_PACKLEADER_IVAR_BLOODFANG = 44884,
        PLAYER_GUID = 99999,
        MOVEPATH_DARIUS = 4488301,
        MOVEPATH_IVAR = 4488401,
        QUEST_WAITING_TO_EXSANGUINATE = 27045,
        SPELL_STEALTH = 34189,
        SPELL_PERMANENT_FEIGN_DEATH = 29266,
        SPELL_EJECT_PASSENGER_1 = 80743,
        SPELL_SUMMON_CROWLEY = 83752,
        SPELL_SUMMON_BLOODFANG = 83753,
        SPELL_SUMMON_CROWLEY_BLOODFANG_MASTER = 83762, // for spell effect 160 is no handler written in core
        SPELL_ARMOIRE_CAMERA_A = 83763,
        SPELL_ARMOIRE_CAMERA_B = 83764,
        SPELL_ARMOIRE_CAMERA_C = 83768,
        SPELL_ARMOIRE_CAMERA_D = 83769,
        SPELL_CONVERSATION_TRIGGER_01A = 83773,
        SPELL_CONVERSATION_TRIGGER_01B = 83774,
        SPELL_CONVERSATION_TRIGGER_01C = 83782,
        SPELL_CONVERSATION_TRIGGER_02A = 83775,
        SPELL_CONVERSATION_TRIGGER_02B = 83777,
        SPELL_CONVERSATION_TRIGGER_02C = 83779,
        SPELL_CONVERSATION_TRIGGER_02D = 83955,
        SPELL_CONVERSATION_TRIGGER_03 = 83787,
        SPELL_CONVERSATION_TRIGGER_04 = 83784,
        SPELL_REVERSE_RIDE_VEHICLE = 83781,
        SPELL_KILL_CREDIT_YORICK = 83786,
        SPELL_HIDE_IN_ARMOIRE = 83788,
        SPELL_DESPAWN_ALL = 83770,
        ACTION_MOVE_TO_RANA = 500,
        ACTION_RANE_JUMP_DEATH = 2,
        EVENT_START_ANIMATION = 101,
        EVENT_CAMERA_STEP = 200,
        EVENT_TEXT_STEP = 300,
    };

    struct npc_armoire_44893AI : public VehicleAI
    {
        npc_armoire_44893AI(Creature* creature) : VehicleAI(creature) { Initialize(); }

        EventMap m_events;
        uint64 m_playerGUID;
        uint64 m_raneGUID;
        uint64 m_crowleyGUID;
        uint64 m_bloodfangGUID;
        
        void Initialize()
        {
            m_playerGUID = 0;
            m_raneGUID = 0;
            m_crowleyGUID = 0;
            m_bloodfangGUID = 0;
            m_events.Reset();
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
                if (player->GetQuestStatus(QUEST_WAITING_TO_EXSANGUINATE) == QUEST_STATUS_INCOMPLETE)
                    if (Vehicle* vehicle = me->GetVehicleKit())
                        m_playerGUID = player->GetGUID();                        
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override
        {
            if (apply)
            {
                if (Player* player = passenger->ToPlayer())
                    if (player->GetQuestStatus(QUEST_WAITING_TO_EXSANGUINATE) == QUEST_STATUS_INCOMPLETE)
                    {
                        m_playerGUID = player->GetGUID();
                        m_events.ScheduleEvent(EVENT_START_ANIMATION, 2000);
                        return;
                    }
            }
            else
            {
                if (Creature* darius = sObjectAccessor->GetCreature(*me, m_crowleyGUID))
                    darius->DespawnOrUnsummon(1000);
                if (Creature* ivar = sObjectAccessor->GetCreature(*me, m_bloodfangGUID))
                    ivar->DespawnOrUnsummon(1000);
                if (Creature* rane = sObjectAccessor->GetCreature(*me, m_raneGUID))
                    rane->DespawnOrUnsummon(1000);
                me->DespawnOrUnsummon(1000);
            }

            m_playerGUID = 0;
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case PLAYER_GUID:
                m_playerGUID = guid;
                break;
            case NPC_LORD_DARIUS_CROWLEY:
                m_crowleyGUID = guid;
                break;
            case NPC_PACKLEADER_IVAR_BLOODFANG:
                m_bloodfangGUID = guid;
                break;
            }
        }

        void EnterEvadeMode() override {}

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);
            
            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_ANIMATION:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                    {
                        player->CastSpell(player, SPELL_SUMMON_CROWLEY_BLOODFANG_MASTER, true);
                        m_events.ScheduleEvent(EVENT_START_ANIMATION + 1, 2000);
                        m_events.ScheduleEvent(EVENT_CAMERA_STEP + 1, 4000);
                    }
                    break;
                }
                case EVENT_START_ANIMATION + 1:
                {
                    if (Creature* darius = sObjectAccessor->GetCreature(*me, m_crowleyGUID))
                        darius->GetMotionMaster()->MovePath(MOVEPATH_DARIUS, false);
                    if (Creature* ivar = sObjectAccessor->GetCreature(*me, m_bloodfangGUID))
                        ivar->GetMotionMaster()->MovePath(MOVEPATH_IVAR, false);
                    if (Creature* rane = me->FindNearestCreature(NPC_RANE_YORICK, 15.0f))
                        m_raneGUID = rane->GetGUID();
                    break;
                }
                case EVENT_CAMERA_STEP + 1:
                {
                    if (Creature* rane = sObjectAccessor->GetCreature(*me, m_raneGUID))
                        me->CastSpell(rane->GetPositionX(), rane->GetPositionY(), rane->GetPositionZ(), SPELL_CONVERSATION_TRIGGER_02D, true);

                    m_events.ScheduleEvent(EVENT_CAMERA_STEP + 2, 16250);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 1, 11500);
                    break;
                }
                case EVENT_CAMERA_STEP + 2:
                {
                    if (Creature* darius = sObjectAccessor->GetCreature(*me, m_crowleyGUID))
                        if (Creature* ivar = sObjectAccessor->GetCreature(*me, m_bloodfangGUID))
                            darius->CastSpell(ivar->GetPositionX(), ivar->GetPositionY(), ivar->GetPositionZ(), SPELL_CONVERSATION_TRIGGER_01A, true);

                    m_events.ScheduleEvent(EVENT_CAMERA_STEP + 3, 12000);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 2, 3700);
                    break;
                }
                case EVENT_CAMERA_STEP + 3:
                {
                    if (Creature* darius = sObjectAccessor->GetCreature(*me, m_crowleyGUID))
                        if (Creature* ivar = sObjectAccessor->GetCreature(*me, m_bloodfangGUID))
                            ivar->CastSpell(darius->GetPositionX(), darius->GetPositionY(), darius->GetPositionZ(), SPELL_CONVERSATION_TRIGGER_01B, true);

                    m_events.ScheduleEvent(EVENT_CAMERA_STEP + 4, 19250);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 3, 3700);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 4, 12000);
                    break;
                }
                case EVENT_CAMERA_STEP + 4:
                {
                    if (Creature* darius = sObjectAccessor->GetCreature(*me, m_crowleyGUID))
                        if (Creature* ivar = sObjectAccessor->GetCreature(*me, m_bloodfangGUID))
                            darius->CastSpell(ivar->GetPositionX(), ivar->GetPositionY(), ivar->GetPositionZ(), SPELL_CONVERSATION_TRIGGER_02A, true);

                    m_events.ScheduleEvent(EVENT_CAMERA_STEP + 5, 18100);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 5, 3700);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 6, 7300);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 7, 9800);
                    break;
                }
                case EVENT_CAMERA_STEP + 5:
                {
                    if (Creature* darius = sObjectAccessor->GetCreature(*me, m_crowleyGUID))
                        if (Creature* ivar = sObjectAccessor->GetCreature(*me, m_bloodfangGUID))
                            ivar->CastSpell(darius->GetPositionX(), darius->GetPositionY(), darius->GetPositionZ(), SPELL_CONVERSATION_TRIGGER_02B, true);

                    m_events.ScheduleEvent(EVENT_CAMERA_STEP + 6, 4800);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 8, 2500);
                    break;
                }
                case EVENT_CAMERA_STEP + 6:
                {
                    if (Creature* darius = sObjectAccessor->GetCreature(*me, m_crowleyGUID))
                        if (Creature* ivar = sObjectAccessor->GetCreature(*me, m_bloodfangGUID))
                            darius->CastSpell(ivar->GetPositionX(), ivar->GetPositionY(), ivar->GetPositionZ(), SPELL_CONVERSATION_TRIGGER_02C, true);

                    m_events.ScheduleEvent(EVENT_CAMERA_STEP + 7, 30000);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 9, 3700);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 10, 7300);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 11, 12100);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 12, 20500);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 13, 26600);
                    break;
                }
                case EVENT_CAMERA_STEP + 7:
                {
                    if (Creature* rane = sObjectAccessor->GetCreature(*me, m_raneGUID))
                        if (Creature* ivar = sObjectAccessor->GetCreature(*me, m_bloodfangGUID))
                        {
                            ivar->CastSpell(rane->GetPositionX(), rane->GetPositionY(), rane->GetPositionZ(), SPELL_CONVERSATION_TRIGGER_01C, true);
                            rane->RemoveAura(SPELL_STEALTH);
                            rane->SetDisableGravity(true);
                            rane->EnterVehicle(ivar, 0);
                        }

                    m_events.ScheduleEvent(EVENT_CAMERA_STEP + 8, 3600);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 14, 500);
                    break;
                }
                case EVENT_CAMERA_STEP + 8:
                {
                    if (Creature* rane = sObjectAccessor->GetCreature(*me, m_raneGUID))
                        if (Creature* ivar = sObjectAccessor->GetCreature(*me, m_bloodfangGUID))
                        {
                            rane->CastSpell(ivar->GetPositionX(), ivar->GetPositionY(), ivar->GetPositionZ(), SPELL_CONVERSATION_TRIGGER_04, true);
                            //ivar->CastSpell(ivar, SPELL_EJECT_PASSENGER_1);
                            rane->ExitVehicle(0);
                            rane->GetAI()->DoAction(ACTION_RANE_JUMP_DEATH);
                        }

                    m_events.ScheduleEvent(EVENT_CAMERA_STEP + 9, 14500);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 15, 1500);
                    m_events.ScheduleEvent(EVENT_TEXT_STEP + 16, 7400);
                    break;
                }
                case EVENT_CAMERA_STEP + 9:
                {
                    if (Creature* darius = sObjectAccessor->GetCreature(*me, m_crowleyGUID))
                        if (Creature* ivar = sObjectAccessor->GetCreature(*me, m_bloodfangGUID))
                            ivar->CastSpell(darius->GetPositionX(), darius->GetPositionY(), darius->GetPositionZ(), SPELL_CONVERSATION_TRIGGER_03, true);

                    m_events.ScheduleEvent(EVENT_CAMERA_STEP + 10, 6000);
                    break;
                }
                case EVENT_CAMERA_STEP + 10:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                    {
                        if (Creature* darius = sObjectAccessor->GetCreature(*me, m_crowleyGUID))
                            darius->GetAI()->DoAction(ACTION_MOVE_TO_RANA);
                        if (Creature* ivar = sObjectAccessor->GetCreature(*me, m_bloodfangGUID))
                            ivar->GetAI()->DoAction(ACTION_MOVE_TO_RANA);

                        player->RemoveAura(SPELL_HIDE_IN_ARMOIRE);
                        player->GetMotionMaster()->Clear();
                        //player->GetMotionMaster()->MovePoint(1231, 1313.48f, 1206.09f, 58.5119f);
                    }

                    m_events.ScheduleEvent(EVENT_CAMERA_STEP + 11, 1000);
                    break;
                }
                case EVENT_CAMERA_STEP + 11:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        if (Creature* darius = sObjectAccessor->GetCreature(*me, m_crowleyGUID))
                            darius->CastSpell(player, SPELL_KILL_CREDIT_YORICK);

                    me->CastSpell(me, SPELL_DESPAWN_ALL);
                    me->DespawnOrUnsummon(10);
                    break;
                }
                case EVENT_TEXT_STEP + 1:
                    if (Creature* crowley = sObjectAccessor->GetCreature(*me, m_crowleyGUID))
                        crowley->AI()->Talk(0);
                    break;
                case EVENT_TEXT_STEP + 2:
                    if (Creature* ivar = sObjectAccessor->GetCreature(*me, m_bloodfangGUID))
                        ivar->AI()->Talk(0);
                    break;
                case EVENT_TEXT_STEP + 3:
                    if (Creature* crowley = sObjectAccessor->GetCreature(*me, m_crowleyGUID))
                        crowley->AI()->Talk(1);
                    break;
                case EVENT_TEXT_STEP + 4:
                    if (Creature* crowley = sObjectAccessor->GetCreature(*me, m_crowleyGUID))
                        crowley->AI()->Talk(2);
                    break;
                case EVENT_TEXT_STEP + 5:
                    if (Creature* ivar = sObjectAccessor->GetCreature(*me, m_bloodfangGUID))
                        ivar->AI()->Talk(1);
                    break;
                case EVENT_TEXT_STEP + 6:
                    if (Creature* ivar = sObjectAccessor->GetCreature(*me, m_bloodfangGUID))
                        ivar->AI()->Talk(2);
                    break;
                case EVENT_TEXT_STEP + 7:
                    if (Creature* ivar = sObjectAccessor->GetCreature(*me, m_bloodfangGUID))
                        ivar->AI()->Talk(3);
                    break;
                case EVENT_TEXT_STEP + 8:
                    if (Creature* crowley = sObjectAccessor->GetCreature(*me, m_crowleyGUID))
                        crowley->AI()->Talk(3);
                    break;
                case EVENT_TEXT_STEP + 9:
                    if (Creature* ivar = sObjectAccessor->GetCreature(*me, m_bloodfangGUID))
                        ivar->AI()->Talk(4);
                    break;
                case EVENT_TEXT_STEP + 10:
                    if (Creature* ivar = sObjectAccessor->GetCreature(*me, m_bloodfangGUID))
                        ivar->AI()->Talk(5);
                    break;
                case EVENT_TEXT_STEP + 11:
                    if (Creature* ivar = sObjectAccessor->GetCreature(*me, m_bloodfangGUID))
                        ivar->AI()->Talk(6);
                    break;
                case EVENT_TEXT_STEP + 12:
                    if (Creature* ivar = sObjectAccessor->GetCreature(*me, m_bloodfangGUID))
                        ivar->AI()->Talk(7);
                    break;
                case EVENT_TEXT_STEP + 13:
                    if (Creature* ivar = sObjectAccessor->GetCreature(*me, m_bloodfangGUID))
                        ivar->AI()->Talk(8);
                    break;
                case EVENT_TEXT_STEP + 14:
                    if (Creature* rane = sObjectAccessor->GetCreature(*me, m_raneGUID))
                        rane->AI()->Talk(2);
                    break;
                case EVENT_TEXT_STEP + 15:
                    if (Creature* ivar = sObjectAccessor->GetCreature(*me, m_bloodfangGUID))
                        ivar->AI()->Talk(9);
                    break;
                case EVENT_TEXT_STEP + 16:
                    if (Creature* ivar = sObjectAccessor->GetCreature(*me, m_bloodfangGUID))
                        ivar->AI()->Talk(10);
                    break;
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_armoire_44893AI(creature);
    }
};

// 44894 // quest 27045
class npc_armoire_44894 : public CreatureScript
{
public:
    npc_armoire_44894() : CreatureScript("npc_armoire_44894") { }

    enum eNPC
    {
        NPC_DEATHSTALKER_RANE_YORICK = 44882,
        QUEST_WAITING_TO_EXSANGUINATE = 27045,
        SPELL_HIDE_IN_ARMOIRE = 83788,
        SPELL_SUMMON_HIDING_SPOT = 83756,
    };

    struct npc_armoire_44894AI : public ScriptedAI
    {
        npc_armoire_44894AI(Creature* creature) : ScriptedAI(creature) { }

        void OnSpellClick(Unit* clicker, bool& result) override
        {
            if (Player* player = clicker->ToPlayer())
                if (player->GetQuestStatus(QUEST_WAITING_TO_EXSANGUINATE) == QUEST_STATUS_INCOMPLETE)
                    if (Creature* rane = me->FindNearestCreature(NPC_DEATHSTALKER_RANE_YORICK, 5.0f))
                    {
                        player->CastSpell(me, SPELL_HIDE_IN_ARMOIRE, true);
                        player->CastSpell(1314.91f, 1211.39f, 58.49675f, SPELL_SUMMON_HIDING_SPOT, true);
                        return;
                    }

            result = false;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_armoire_44894AI(creature);
    }
};

// 44883 // quest 27045
class npc_lord_darius_crowley_44883 : public CreatureScript
{
public:
    npc_lord_darius_crowley_44883() : CreatureScript("npc_lord_darius_crowley_44883") { }

    enum eNPC
    {
        NPC_ARMOIRE = 44893,
        NPC_PACKLEADER_IVAR_BLOODFANG = 44884,
        EVENTS_TURN_FACE,
        ACTION_MOVE_TO_RANA = 500,
    };

    struct npc_lord_darius_crowley_44883AI : public ScriptedAI
    {
        npc_lord_darius_crowley_44883AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_armoireGUID;
        uint64   m_bloodfangGUID;

        void Initialize()
        {
            m_events.Reset();
            m_playerGUID = 0;
            m_armoireGUID = 0;
            m_bloodfangGUID = 0;
        }

        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
                m_playerGUID = player->GetGUID();

            FindAllGuid();
        }

        void MovementInform(uint32 type, uint32 id) override 
        { 
            FindAllGuid();
            if (type == WAYPOINT_MOTION_TYPE)
                if (id == 5)
                    m_events.ScheduleEvent(EVENTS_TURN_FACE, 250);

            if (type == POINT_MOTION_TYPE && id == 1230)
                me->DespawnOrUnsummon(1000);
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case ACTION_MOVE_TO_RANA:
            {
                me->SetSpeed(MOVE_WALK, 1.0f);
                me->GetMotionMaster()->MovePoint(1230, 1299.025f, 1206.724f, 59.64236f);
                break;
            }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENTS_TURN_FACE:
                {
                    if (Creature* ivar = sObjectAccessor->GetCreature(*me, m_bloodfangGUID))
                        me->SetFacingToObject(ivar);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void FindAllGuid()
        {
            if (!m_bloodfangGUID)
                if (Creature* ivar = me->FindNearestCreature(NPC_PACKLEADER_IVAR_BLOODFANG, 30.0f))
                    m_bloodfangGUID = ivar->GetGUID();

            if (!m_armoireGUID)
                if (Creature* armoire = me->FindNearestCreature(NPC_ARMOIRE, 30.0f))
                {
                    m_armoireGUID = armoire->GetGUID();
                    armoire->GetAI()->SetGUID(me->GetGUID(), me->GetEntry());
                }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_lord_darius_crowley_44883AI(creature);
    }
};

// 44884  // quest 27045
class npc_packleader_ivar_bloodfang_44884 : public CreatureScript
{
public:
    npc_packleader_ivar_bloodfang_44884() : CreatureScript("npc_packleader_ivar_bloodfang_44884") { }

    enum eNPC
    {
        NPC_ARMOIRE = 44893,
        ACTION_MOVE_TO_RANA = 500,
    };

    struct npc_packleader_ivar_bloodfang_44884AI : public ScriptedAI
    {
        npc_packleader_ivar_bloodfang_44884AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_armoireGUID;

        void Initialize()
        {
            m_playerGUID = 0;
        }

        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
                m_playerGUID = player->GetGUID();
            if (Creature* armoire = me->FindNearestCreature(NPC_ARMOIRE, 30.0f))
            {
                m_armoireGUID = armoire->GetGUID();
                armoire->GetAI()->SetGUID(me->GetGUID(), me->GetEntry());
            }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == POINT_MOTION_TYPE && id == 1230)
                me->DespawnOrUnsummon(1000);
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case ACTION_MOVE_TO_RANA:
            {
                me->SetSpeed(MOVE_WALK, 1.0f);
                me->GetMotionMaster()->MovePoint(1230, 1299.025f, 1206.724f, 59.64236f);
                break;
            }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_packleader_ivar_bloodfang_44884AI(creature);
    }
};

// 44365  // quest 27065 // 27096 // 27097 // 27099
class npc_lady_sylvanas_windrunner_44365 : public CreatureScript
{
public:
    npc_lady_sylvanas_windrunner_44365() : CreatureScript("npc_lady_sylvanas_windrunner_44365") { }

    enum eNPC
    {
        QUEST_THE_WARCHIEFS_FLEET_27065 = 27065,
        QUEST_ORCS_ARE_IN_ORDER = 27096,
        QUEST_RISE_FORSAKEN = 27097,
        QUEST_NO_ESCAPE = 27099,
        SPELL_SUMMON_AGATHA = 83982,
        SPELL_SEE_QUEST_INVIS_5 = 84241,
        SPELL_DEATH_WALK = 85451,
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_THE_WARCHIEFS_FLEET_27065)
            player->AddAura(SPELL_SEE_QUEST_INVIS_5, player);
        else if (quest->GetQuestId() == QUEST_RISE_FORSAKEN)
            player->CastSpell(1380.69f, 1037.616f, 53.046f, SPELL_SUMMON_AGATHA, true);
        else if (quest->GetQuestId() == QUEST_NO_ESCAPE)
            player->CastSpell(1380.69f, 1037.616f, 53.046f, SPELL_SUMMON_AGATHA, true);

        return false;
    }

    bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* quest, uint32 /*opt*/) override
    { 
        if (quest->GetQuestId() == QUEST_ORCS_ARE_IN_ORDER)
            player->RemoveAura(SPELL_SEE_QUEST_INVIS_5);
        if (quest->GetQuestId() == QUEST_RISE_FORSAKEN)
            player->RemoveAura(SPELL_DEATH_WALK);
        if (quest->GetQuestId() == QUEST_NO_ESCAPE)
            player->RemoveAura(SPELL_DEATH_WALK);

        return false; 
    }
};

// 44914  // quest 27069
class npc_orc_sea_pup_44914 : public CreatureScript
{
public:
    npc_orc_sea_pup_44914() : CreatureScript("npc_orc_sea_pup_44914") { }

    enum eNPC
    {
        QUEST_STEEL_THUNDER = 27069,
        NPC_ORC_CRATE = 44915,
        SPELL_SUMMON_ORC_CRATE = 83835,
        SPELL_PICK_UP_ORC_CRATE = 83838,
        SPELL_DESPAWN_ALL = 83840,
        SPELL_CREDIT = 83843,
        EVENT_TALK_TO_PLAYER = 100,
        EVENT_CHECK_PLAYER_ALIVE,
    };

    struct npc_orc_sea_pup_44914AI : public VehicleAI
    {
        npc_orc_sea_pup_44914AI(Creature* creature) : VehicleAI(creature) { Initialize(); }

        EventMap m_events;
        uint64 m_playerGUID;
        bool   m_IsFull;

        void Initialize()
        {
            m_playerGUID = 0;
            m_IsFull = false;
        }

        void Reset() override
        {
            m_events.Reset();
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
                if (player->GetQuestStatus(QUEST_STEEL_THUNDER) == QUEST_STATUS_INCOMPLETE)
                {
                    Talk(0);
                    m_playerGUID = player->GetGUID();
                    me->GetMotionMaster()->MoveFollow(player, 3.0f, M_PI);
                    m_events.ScheduleEvent(EVENT_CHECK_PLAYER_ALIVE, 1000);
                    int c = player->GetReqKillOrCastCurrentCount(QUEST_STEEL_THUNDER, NPC_ORC_CRATE);
                    for (int i = 0; i < c; i++)
                        me->CastSpell(me, SPELL_SUMMON_ORC_CRATE, true);
                }
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override
        { 
            if (passenger->GetEntry() == NPC_ORC_CRATE)
                if (apply)
                {
                    Talk(seatId + 1);
                    if (seatId == 4)
                    {
                        m_IsFull = true;
                        m_events.ScheduleEvent(EVENT_TALK_TO_PLAYER, 1000);
                    }
                }
                else
                {
                    if (Creature* crate = passenger->ToCreature())
                        crate->DespawnOrUnsummon(6000);
                }
        }

        void JustSummoned(Creature* summon) override 
        { 
            if (summon->GetEntry() == NPC_ORC_CRATE)
                if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                    summon->EnterVehicle(me, -1);
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        { 
            if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                if (spell->Id == SPELL_PICK_UP_ORC_CRATE)
                {
                    me->CastSpell(me, SPELL_SUMMON_ORC_CRATE, true);
                    me->CastSpell(player, SPELL_CREDIT);
                }
        }

        void DoAction(int32 param) override 
        { 
            if (param == 2)
            {
                m_events.CancelEvent(EVENT_TALK_TO_PLAYER);
                Talk(6);
                me->GetVehicleKit()->RemoveAllPassengers();
                me->DespawnOrUnsummon(6000);
            }
            else if (param == 3)
                if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                    player->CastSpell(player, SPELL_DESPAWN_ALL);
        }

        void EnterEvadeMode() override {}

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_TALK_TO_PLAYER:
                {
                    Talk(7);
                    m_events.ScheduleEvent(EVENT_TALK_TO_PLAYER, urand(10000, 20000));
                    break;
                }
                case EVENT_CHECK_PLAYER_ALIVE:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        if (player->IsAlive() && player->IsInWorld())
                        {
                            m_events.ScheduleEvent(EVENT_CHECK_PLAYER_ALIVE, 1000);
                            break;
                        }
                    
                    me->GetVehicleKit()->RemoveAllPassengers();
                    me->DespawnOrUnsummon(10);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_orc_sea_pup_44914AI(creature);
    }
};

// 44916  // quest 27069
class npc_admiral_hatchet_44916 : public CreatureScript
{
public:
    npc_admiral_hatchet_44916() : CreatureScript("npc_admiral_hatchet_44916") { }

    enum eNPC
    {
        QUEST_STEEL_THUNDER = 27069,
        NPC_WARLORD_TOROK =  44917,
        NPC_SEA_PUP = 44914,
        SPELL_SUMMON_SEA_PUP = 83839,
        SPELL_SEA_PUP_TRIGGER = 83865,
        EVENT_CHECK_TALK = 100,
        EVENT_TALK_COOLDOWN = 101,
        EVENT_TALK = 200,
    };

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    { 
        if (player->GetQuestStatus(QUEST_STEEL_THUNDER) == QUEST_STATUS_INCOMPLETE)
            if (creature->FindNearestCreature(NPC_SEA_PUP, 10.0f) == 0)
                if (action == 1)
                {
                    player->CastSpell(player, SPELL_SEA_PUP_TRIGGER);
                    player->CLOSE_GOSSIP_MENU();
                    return true;
                }

        return false; 
    }

    bool OnQuestReward(Player* /*player*/, Creature* creature, Quest const* quest, uint32 /*opt*/) override
    { 
        if (quest->GetQuestId() == QUEST_STEEL_THUNDER)
            if (Creature* pup = creature->FindNearestCreature(NPC_SEA_PUP, 10.0f))
                pup->GetAI()->DoAction(2);

        return false; 
    }

    struct npc_admiral_hatchet_44916AI : public ScriptedAI
    {
        npc_admiral_hatchet_44916AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_torokGUID;

        void Initialize()
        {
            m_playerGUID = 0;
            m_torokGUID = 0;
        }

        void Reset() override
        {
            m_events.Reset();
            m_events.ScheduleEvent(EVENT_CHECK_TALK, 1000);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_TALK:
                {
                    CheckForGUID();
                    if (Player* player = me->FindNearestPlayer(30.0f))
                    {
                        m_playerGUID = player->GetGUID();
                        m_events.ScheduleEvent(EVENT_TALK + 1, 1000);
                        m_events.ScheduleEvent(EVENT_TALK_COOLDOWN, 90000);

                    }
                    else
                    {
                        m_playerGUID = 0;
                        m_events.ScheduleEvent(EVENT_CHECK_TALK, 1000);
                    }
                    break;
                }
                case EVENT_TALK_COOLDOWN:
                {
                    Reset();
                    break;
                }
                case EVENT_TALK + 1:
                {
                    Talk(0);
                    m_events.ScheduleEvent(EVENT_TALK + 2, 8000);
                    break;
                }
                case EVENT_TALK + 2:
                {
                    if (Creature* torok = sObjectAccessor->GetCreature(*me, m_torokGUID))
                        torok->AI()->Talk(0);
                    m_events.ScheduleEvent(EVENT_TALK + 3, 6000);
                    break;
                }
                case EVENT_TALK + 3:
                {
                    Talk(1);
                    m_events.ScheduleEvent(EVENT_TALK + 4, 6000);
                    break;
                }
                case EVENT_TALK + 4:
                {
                    if (Creature* torok = sObjectAccessor->GetCreature(*me, m_torokGUID))
                        torok->AI()->Talk(1);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void CheckForGUID()
        {
            if (!m_torokGUID)
                if (Creature* torok = me->FindNearestCreature(NPC_WARLORD_TOROK, 30.0f))
                    m_torokGUID = torok->GetGUID();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_admiral_hatchet_44916AI(creature);
    }
};

// 45498  // conversation
class npc_salty_rocka_45498 : public CreatureScript
{
public:
    npc_salty_rocka_45498() : CreatureScript("npc_salty_rocka_45498") { }

    enum eNPC
    {
        NPC_GORGAR = 45497,
        NPC_ROCKA = 45498,
        EVENT_CHECK_TALK = 100,
        EVENT_TALK_COOLDOWN = 101,
        EVENT_TALK = 200,
    };

    struct npc_salty_rocka_45498AI : public ScriptedAI
    {
        npc_salty_rocka_45498AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_gorgarGUID;

        void Initialize()
        {           
            m_gorgarGUID = 0;
        }

        void Reset() override
        {
            m_events.Reset();
            m_events.ScheduleEvent(EVENT_CHECK_TALK, 1000);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_TALK:
                {
                    CheckForGUID();
                    if (Player* player = me->FindNearestPlayer(30.0f))
                    {
                        m_playerGUID = player->GetGUID(); 
                        m_events.ScheduleEvent(EVENT_TALK + 1, 1000);
                        m_events.ScheduleEvent(EVENT_TALK_COOLDOWN, 120000);

                    }
                    else
                    {
                        m_playerGUID = 0;
                        m_events.ScheduleEvent(EVENT_CHECK_TALK, 1000);
                    }
                    break;
                }
                case EVENT_TALK_COOLDOWN:
                {
                    Reset();
                    break;
                }
                case EVENT_TALK + 1:
                {
                    Talk(0);
                    m_events.ScheduleEvent(EVENT_TALK + 2, 8000);
                    break;
                }
                case EVENT_TALK + 2:
                {
                    Talk(1);
                    m_events.ScheduleEvent(EVENT_TALK + 3, 8000);
                    break;
                }
                case EVENT_TALK + 3:
                {
                    Talk(2);
                    m_events.ScheduleEvent(EVENT_TALK + 4, 8000);
                    break;
                }
                case EVENT_TALK + 4:
                {
                    if (Creature* gorgar = sObjectAccessor->GetCreature(*me, m_gorgarGUID))
                        gorgar->AI()->Talk(0);
                    m_events.ScheduleEvent(EVENT_TALK + 5, 8000);
                    break;
                }
                case EVENT_TALK + 5:
                {
                    if (Creature* gorgar = sObjectAccessor->GetCreature(*me, m_gorgarGUID))
                        gorgar->AI()->Talk(1);
                    m_events.ScheduleEvent(EVENT_TALK + 6, 8000);
                    break;
                }
                case EVENT_TALK + 6:
                {
                    if (Creature* gorgar = sObjectAccessor->GetCreature(*me, m_gorgarGUID))
                        gorgar->AI()->Talk(2);
                    m_events.ScheduleEvent(EVENT_TALK + 7, 8000);
                    break;
                }
                case EVENT_TALK + 7:
                {
                    Talk(3);
                    m_events.ScheduleEvent(EVENT_TALK + 8, 8000);
                    break;
                }
                case EVENT_TALK + 8:
                {
                    Talk(4);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void CheckForGUID()
        {
            if (!m_gorgarGUID)
                if (Creature* gorgar = me->FindNearestCreature(NPC_GORGAR, 50.0f))
                    m_gorgarGUID = gorgar->GetGUID();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_salty_rocka_45498AI(creature);
    }
};

// 83865  // quest 27069
class spell_sea_pup_trigger_83865 : public SpellScriptLoader
{
public:
    spell_sea_pup_trigger_83865() : SpellScriptLoader("spell_sea_pup_trigger_83865") { }

    enum eSpell
    {
        SPELL_SUMMON_SEA_PUP = 83839,
    };

    class IsNotPlayerGuid
    {
    public:
        explicit IsNotPlayerGuid(uint64 guid) : _guid(guid) { }

        bool operator()(WorldObject* obj) const
        {
            if (Player* player = obj->ToPlayer())
                return player->GetGUID() != _guid;

            return true;
        }

    private:
        uint64 _guid;
    };

    class spell_sea_pup_trigger_83865_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sea_pup_trigger_83865_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if(IsNotPlayerGuid(GetCaster()->GetGUID()));
        }

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* unit = GetCaster())
                if (Player* player = unit->ToPlayer())
                    player->CastSpell(player, SPELL_SUMMON_SEA_PUP);
        }
        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sea_pup_trigger_83865_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            OnEffectHitTarget += SpellEffectFn(spell_sea_pup_trigger_83865_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_sea_pup_trigger_83865_SpellScript();
    }
};

// 83838  // quest 27069
class spell_pick_up_orc_crate_83838 : public SpellScriptLoader
{
public:
    spell_pick_up_orc_crate_83838() : SpellScriptLoader("spell_pick_up_orc_crate_83838") { }

    enum eSpell
    {
        NPC_ORC_SEA_PUP = 44914,
    };

    class IsNotEntry
    {
    public:
        explicit IsNotEntry(uint32 entry) : _entry(entry) { }

        bool operator()(WorldObject* obj) const
        {
            if (Creature* target = obj->ToCreature())
                return target->GetEntry() != _entry;

            return true;
        }

    private:
        uint32 _entry;
    };

    class spell_pick_up_orc_crate_83838_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pick_up_orc_crate_83838_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if(IsNotEntry(NPC_ORC_SEA_PUP));
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pick_up_orc_crate_83838_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pick_up_orc_crate_83838_SpellScript();
    }
};

// 44941  // quest 27093
class npc_webbed_victim_44941 : public CreatureScript
{
public:
    npc_webbed_victim_44941() : CreatureScript("npc_webbed_victim_44941") { }

    enum eNPC
    {
        NPC_ORC_SEA_DOG = 44942,
        QUEST_LOST_IN_THE_DARKNESS = 27093,
        SPELL_FREE_WEBBED_VICTIM1 = 83919,
        SPELL_FREE_WEBBED_VICTIM2 = 83921,
        SPELL_FREE_WEBBED_VICTIM3 = 83927,
        SPELL_DESPAWN_ALL_SUMMONS = 83935,
    };

    struct npc_webbed_victim_44941AI : public ScriptedAI
    {
        npc_webbed_victim_44941AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        uint64   m_playerGUID;

        void Initialize()
        {
            m_playerGUID = 0;
        }

        void JustDied(Unit* killer) override
        {
            if (Player* player = killer->ToPlayer())
                if (player->GetQuestStatus(QUEST_LOST_IN_THE_DARKNESS) == QUEST_STATUS_INCOMPLETE)
                {
                    m_playerGUID = player->GetGUID();
                    player->CastSpell(me, SPELL_FREE_WEBBED_VICTIM3, true);
                }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_webbed_victim_44941AI(creature);
    }
};

// 44942  // quest 27093
class npc_orc_sea_dog_44942 : public CreatureScript
{
public:
    npc_orc_sea_dog_44942() : CreatureScript("npc_orc_sea_dog_44942") { }

    enum eNPC
    {
        QUEST_LOST_IN_THE_DARKNESS = 27093,
        NPC_WEBBED_VICTIM = 44941,
        NPC_ORC_SEA_DOG = 44942,
        SPELL_DESPAWN_ALL_SUMMONS = 83935,
        EVENT_CHECK_PLAYER = 100,
    };

    struct npc_orc_sea_dog_44942AI : public ScriptedAI
    {
        npc_orc_sea_dog_44942AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_playerGUID;

        void Initialize()
        {
            m_playerGUID = 0;
            m_events.Reset();
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                me->GetMotionMaster()->MoveFollow(player, 4.0f, frand(1.57f, 4.71f));
                m_events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_PLAYER:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        if (player->IsAlive() && player->IsInWorld() && !player->IsQuestRewarded(QUEST_LOST_IN_THE_DARKNESS))
                        {
                            m_events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
                            break;
                        }

                    me->DespawnOrUnsummon(10);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_orc_sea_dog_44942AI(creature);
    }
};

// 44367  // quest 27088
class npc_forest_ettin_44367 : public CreatureScript
{
public:
    npc_forest_ettin_44367() : CreatureScript("npc_forest_ettin_44367") { }

    enum eNPC
    {
        NPC_MUTANT_BUSH_CHICKEN = 44935,
        SPELL_BUSH_CHICKEN_EXPLOSION = 83903,
        SPELL_REVERSE_CAST_RIDE_VEHICLE = 83904,
        SPELL_ETTINS_MOUTH = 83907,
        EVENT_CHECK_FOR_CHICKEN = 101,
        EVENT_EAT_CHICKEN,
        EVENT_CHICKEN_EXPLODE,
    };

    struct npc_forest_ettin_44367AI : public VehicleAI
    {
        npc_forest_ettin_44367AI(Creature* creature) : VehicleAI(creature) { }

        EventMap m_events;
        uint64 m_playerGUID;
        uint64 m_chickenGUID;
        bool isChickenFollower;
        bool isChickenRideOnEttin;

        void Reset() override
        {
            m_playerGUID = 0;
            m_chickenGUID = 0;
            isChickenFollower = false;
            isChickenRideOnEttin = false;
            m_events.Reset();
            m_events.ScheduleEvent(EVENT_CHECK_FOR_CHICKEN, 1000);
        }

        void JustDied(Unit* killer) override
        { 
            if (killer->GetEntry() == NPC_MUTANT_BUSH_CHICKEN)
                if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                    player->KilledMonsterCredit(me->GetEntry());
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override
        { 
            if (apply && passenger->GetEntry() == NPC_MUTANT_BUSH_CHICKEN)
            {
                m_playerGUID = passenger->GetCharmerOrOwnerGUID();
                isChickenRideOnEttin = true;
                m_events.ScheduleEvent(EVENT_EAT_CHICKEN, 2500);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_FOR_CHICKEN:
                {
                    if (!m_chickenGUID)
                        if (Creature* chicken = me->FindNearestCreature(NPC_MUTANT_BUSH_CHICKEN, 20.0f))
                            m_chickenGUID = chicken->GetGUID();

                    if (Creature* chicken = sObjectAccessor->GetCreature(*me, m_chickenGUID))
                    {
                        if (!isChickenRideOnEttin && me->GetDistance2d(chicken) < 5.0f)
                        {
                            me->GetMotionMaster()->Clear();
                            me->GetMotionMaster()->MoveIdle();
                            me->CastSpell(chicken, SPELL_REVERSE_CAST_RIDE_VEHICLE, true);
                            chicken->SendPlaySound(15936, false);
                        }
                        else if (!isChickenFollower)
                        {
                            isChickenFollower = true;
                            chicken->SetWalk(true);
                            chicken->GetMotionMaster()->MoveFollow(me, 5.0f, 0.0f);
                            chicken->SendPlaySound(15936, false);
                        }
                    }
                    else
                    {
                        m_chickenGUID = 0;
                        isChickenFollower = false;
                        isChickenRideOnEttin = false;
                    }

                    m_events.ScheduleEvent(EVENT_CHECK_FOR_CHICKEN, 1000);
                    break;
                }
                case EVENT_EAT_CHICKEN:
                {
                    if (Creature* chicken = sObjectAccessor->GetCreature(*me, m_chickenGUID))
                    {
                        chicken->CastSpell(me, SPELL_ETTINS_MOUTH, true);
                        m_events.ScheduleEvent(EVENT_CHICKEN_EXPLODE, 6000);
                    }
                    break;
                }
                case EVENT_CHICKEN_EXPLODE:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        if (Creature* chicken = sObjectAccessor->GetCreature(*me, m_chickenGUID))
                            chicken->CastSpell(me, SPELL_BUSH_CHICKEN_EXPLOSION, true);

                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_forest_ettin_44367AI(creature);
    }
};

// 83904  // quest 27088
class spell_reverse_cast_ride_vehicle_83904 : public SpellScriptLoader
{
public:
    spell_reverse_cast_ride_vehicle_83904() : SpellScriptLoader("spell_reverse_cast_ride_vehicle_83904") { }

    enum eSpell
    {
        NPC_ETTIN = 44367,
        NPC_CHICKEN = 44935,
    };

    class spell_reverse_cast_ride_vehicle_83904_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_reverse_cast_ride_vehicle_83904_SpellScript);

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            if (Unit* unit1 = GetHitUnit())
                if (Creature* chicken = unit1->ToCreature())
                    if (Unit* unit2 = GetCaster())
                        if (Creature* ettin = unit2->ToCreature())
                            chicken->EnterVehicle(ettin, 0);
        }
        
        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_reverse_cast_ride_vehicle_83904_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_reverse_cast_ride_vehicle_83904_SpellScript();
    }
};

// 44954 //44966 // quest 27097
class npc_hillsbrad_refugee_44966 : public CreatureScript
{
public:
    npc_hillsbrad_refugee_44966() : CreatureScript("npc_hillsbrad_refugee_44966") { }

    enum eNPC
    {
        NPC_AGATHA = 44951,
        SPELL_NOTIFY_AGATHA = 83990,
        SPELL_DOOMHOWL = 84012,
        SPELL_UNHOLY_SMITE = 84014,
        QUEST_RISE_FORSAKEN = 27097,
    };

    struct npc_hillsbrad_refugee_44966AI : public ScriptedAI
    {
        npc_hillsbrad_refugee_44966AI(Creature* creature) : ScriptedAI(creature) { }

        void JustSummoned(Creature* summon) override
        {
            uint32 rol = urand(0, 100);
            if (rol < 50)
            {
                summon->AI()->Talk(0);
                summon->DespawnOrUnsummon(10000);
            }
        }

        void JustDied(Unit* killer) override
        {
            if (Creature* agatha = me->FindNearestCreature(NPC_AGATHA, 30.0f))
            {
                me->CastSpell(agatha, SPELL_NOTIFY_AGATHA);
                uint32 m_forsakenSpell;
                if (me->getGender() == GENDER_MALE)
                    m_forsakenSpell = RAND(83998, 83999, 84000, 84001);
                else
                    m_forsakenSpell = RAND(84002, 84003, 84004, 84005);
                me->CastSpell(me, m_forsakenSpell);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_hillsbrad_refugee_44966AI(creature);
    }
};

// 44951  // quest 27097 // 27099
class npc_agatha_44951 : public CreatureScript
{
public:
    npc_agatha_44951() : CreatureScript("npc_agatha_44951") { }

    enum eNPC
    {
        NPC_HILLSBRAD_REFUGEE1 = 44954,
        NPC_HILLSBRAD_REFUGEE2 = 44966,
        NPC_FORSAKEN = 44959,
        QUEST_RISE_FORSAKEN = 27097,
        QUEST_NO_ESCAPE = 27099,
        SPELL_DEATH_WALK = 85451,
        SPELL_NOTIFY_AGATHA = 83990,
        SPELL_RISE_FORSAKEN = 83993,
        SPELL_KILL_CREDIT = 83996,
        SPELL_DOOMHOWL = 84012,
        SPELL_UNHOLY_DARKNESS = 84013,
        SPELL_UNHOLY_SMITE = 84014,
        SPELL_GENERAL_TRIGGER_84107 = 84107,
        SPELL_GENERAL_TRIGGER_84114 = 84114,
        EVENT_CHAT_TO_PLAYER = 100,
        EVENT_CHECK_PLAYER,
        EVENT_CAST_AGGRO,
        EVENT_HEAL_COOLDOWN,
        EVENT_27099_RUN,
    };

    struct npc_agatha_44951AI : public VehicleAI
    {
        npc_agatha_44951AI(Creature* creature) : VehicleAI(creature) { Initialize(); }

        EventMap m_events;
        uint64 m_playerGUID;
        uint64 m_targetGUID;
        bool   m_doomhoulDone;
        bool   m_healCD;
        
        void Initialize()
        {
            m_playerGUID = 0;
            m_targetGUID = 0;
            m_doomhoulDone = false;
            m_events.Reset();
            m_events.ScheduleEvent(EVENT_CHAT_TO_PLAYER, 60000);
            m_events.ScheduleEvent(EVENT_CHECK_PLAYER, 2000);
            m_healCD = false;
        }

        void Reset() override
        {
            me->SetDisableGravity(true);
            me->SetWaterWalking(true);
        }

        void IsSummonedBy(Unit* summoner) override 
        { 
            if (Player* player = summoner->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                me->SetFacingToObject(player);
                me->GetMotionMaster()->MoveFollow(player, 3.0f, M_PI);
                me->SetReactState(REACT_PASSIVE);
                me->CastSpell(me, SPELL_DEATH_WALK, true);
                me->AddAura(SPELL_DEATH_WALK, player);
            }
            if (Creature* stalker = me->FindNearestCreature(45032,25.0f))
                SetForQuest27099();
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override 
        { 
            switch (spell->Id)
            {
            case SPELL_NOTIFY_AGATHA:
                me->CastSpell(caster, SPELL_RISE_FORSAKEN, true);
                if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                    player->CastSpell(player, SPELL_KILL_CREDIT);
                break;
            case SPELL_GENERAL_TRIGGER_84114:
                SetForQuest27099();
                break;
            case 83978:
            {
                // send chat to player..
                break;
            }
            case 84107:
            {
                m_events.ScheduleEvent(EVENT_27099_RUN, 1000);
                break;
            }
            }
        }

        void MovementInform(uint32 type, uint32 id) override 
        { 
            if (type == POINT_MOTION_TYPE && id == 1231)
                m_events.ScheduleEvent(EVENT_27099_RUN + 1, 100);
            if (type == WAYPOINT_MOTION_TYPE && id == 42)
                m_events.ScheduleEvent(EVENT_27099_RUN + 4, 100);
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override 
        { 
            if (apply && passenger->ToPlayer())
                m_events.ScheduleEvent(EVENT_27099_RUN + 3, 100);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override 
        { 
            if (attacker->GetGUID() != m_targetGUID)
                if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                    if (Unit* unit = player->GetVictim())
                        if (unit->GetGUID() != m_targetGUID)
                            EnterCombat(unit);
        }

        void EnterCombat(Unit* victim) override
        {
            m_doomhoulDone = false;
            m_targetGUID = victim->GetGUID();
            me->CastSpell(victim, SPELL_UNHOLY_SMITE);
            m_events.RescheduleEvent(EVENT_CAST_AGGRO, urand(1000, 4000));
        }

        void EnterEvadeMode() override { }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHAT_TO_PLAYER:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        me->AI()->Talk(0);
                    m_events.ScheduleEvent(EVENT_CHAT_TO_PLAYER, 60000);
                    break;
                }
                case EVENT_CHECK_PLAYER:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        if (player->IsAlive() || player->IsInWorld())
                            if (CheckQuestStatus(player))
                            {
                                if (!m_healCD && player->GetHealthPct() < 90.0f)
                                {
                                    me->CastSpell(player, SPELL_UNHOLY_DARKNESS);
                                    m_healCD = true;
                                    m_events.ScheduleEvent(EVENT_HEAL_COOLDOWN, 2000);
                                }
                                
                                if (Unit* unit = player->GetVictim())
                                {
                                    if (unit->GetGUID() != m_targetGUID)
                                        EnterCombat(unit);
                                }
                                else if (player->IsInCombat())
                                {
                                    if (Unit* unit = player->GetSelectedUnit())
                                        if (unit->GetGUID() != m_targetGUID)
                                            EnterCombat(unit);
                                }

                                m_events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
                                break;
                            }

                    me->DespawnOrUnsummon(10);
                    break;
                }
                case EVENT_CAST_AGGRO:
                {
                    if (Creature* target = sObjectAccessor->GetCreature(*me, m_targetGUID))
                        if (target->IsAlive())
                        {
                            if (target->GetEntry() == NPC_HILLSBRAD_REFUGEE1 || target->GetEntry() == NPC_HILLSBRAD_REFUGEE2)
                                if (!m_doomhoulDone)
                                {
                                    m_doomhoulDone = true;
                                    me->CastSpell(me, SPELL_DOOMHOWL); 
                                    m_events.ScheduleEvent(EVENT_CAST_AGGRO, urand(2000, 3000));
                                    break;
                                }

                            me->CastSpell(target, SPELL_UNHOLY_SMITE);
                            m_events.ScheduleEvent(EVENT_CAST_AGGRO, urand(1000, 6000));                           
                        }
                    break;
                }
                case EVENT_HEAL_COOLDOWN:
                {
                    m_healCD = false;
                    break;
                }
                case EVENT_27099_RUN:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        me->GetMotionMaster()->MovePoint(1231, player->GetPosition());

                    break;
                }
                case EVENT_27099_RUN + 1:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                    {
                        player->ExitVehicle();
                        me->CastSpell(player, 84112, true); // camera spell
                        Talk(2, player);
                    }
                    m_events.ScheduleEvent(EVENT_27099_RUN + 2, 1500);
                    break;
                }
                case EVENT_27099_RUN + 2:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                    {
                        me->CastSpell(player, 84109); // ride vehicle, script_effect
                        player->EnterVehicle(me);
                        Talk(3, player);                        
                    }
                    break;
                }
                case EVENT_27099_RUN + 3:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        player->KilledMonsterCredit(44951);
                    me->GetMotionMaster()->MovePath(4495101, false);
                    break;
                }
                case EVENT_27099_RUN + 4:
                {
                    me->GetVehicleKit()->RemoveAllPassengers();
                    me->DespawnOrUnsummon(1000);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        bool CheckQuestStatus(Player* player)
        {
            if (player->GetQuestStatus(QUEST_RISE_FORSAKEN) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_RISE_FORSAKEN) == QUEST_STATUS_COMPLETE)
                return true;
            else if (player->GetQuestStatus(QUEST_NO_ESCAPE) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_NO_ESCAPE) == QUEST_STATUS_COMPLETE)
                return true;

            return false;
        }

        void SetForQuest27099()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
            me->SetReactState(REACT_PASSIVE);
            me->GetMotionMaster()->MovePoint(1234, 982.57f, 671.04f, 77.298f);
            m_events.CancelEvent(EVENT_CHAT_TO_PLAYER);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_agatha_44951AI(creature);
    }
};

enum eQuest27099
{
    NPC_AGATHA = 44951,
    QUEST_NO_ESCAPE = 27099,
    NPC_BLOODFANG = 44990,
    NPC_CROWLEY = 44989,
    NPC_PHIN_ODELIC = 44993,
    NPC_BARTOLO_GINSETTI = 44994,
    NPC_LOREMASTER_DIBBS = 44995,
    NPC_MAGISTRATE_HENRY_MALEB = 44996,
    NPC_CARETAKER_SMITHERS = 44997,
    NPC_SOPHIA_ZWOSKI = 45002,
    SPELL_FORCE_CAST_FENRIS_CAMERA = 84113,
    SPELL_SUMMON_BLOODFANG = 84054,
    SPELL_SUMMON_CROWLEY = 84055,
    SPELL_SUMMON_PHIN_ODELIC = 84056,
    SPELL_SUMMON_BARTOLO_GINSETTI = 84057,
    SPELL_SUMMON_LOREMASTER_DIBBS = 84058,
    SPELL_SUMMON_MAGISTRATE_HENRY_MALEB = 84059,
    SPELL_SUMMON_CARETAKER_SMITHERS = 84060,
    SPELL_SUMMON_SOPHIA = 84061,
    SPELL_SUMMON_AGATHA = 83982,
    SPELL_CONVERSATION_TRIGGER_84076 = 84076, // start conversation for maleb
    SPELL_CONVERSATION_TRIGGER_84077 = 84077, // start drinking poison
    SPELL_ARMORE_CAMERA = 84104,
    SPELL_GENERAL_TRIGGER_84102 = 84102,      // start conversation for crowley
    SPELL_GENERAL_TRIGGER_84107 = 84107,      // finish video.. starting agatha RUN
    SPELL_GENERAL_TRIGGER_84114 = 84114,      // von player an agatha.. n:262723
    SOUND_WORGEN_HOWLING = 17671,
    EVENT_CHECK_QUEST = 101,
    EVENT_CHECK_PLAYER,
    EVENT_START_ANIMATION,
    EVENT_MASTER_RESET,
    EVENT_DRINKING,
    EVENT_MORPHING,
    EVENT_HOWLING,
    EVENT_MOVE_TO_STARTPOINT,
    EVENT_CHANGE_TO_SEAT_2,
    EVENT_TRIGGER_84102,
    EVENT_ANIMATION = 200,
};

// 45032 // quest 27099
class npc_fenris_keep_stalker_45032 : public CreatureScript
{
public:
    npc_fenris_keep_stalker_45032() : CreatureScript("npc_fenris_keep_stalker_45032") { }

    struct npc_fenris_keep_stalker_45032AI : public ScriptedAI
    {
        npc_fenris_keep_stalker_45032AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_bloodfangGUID;
        uint64   m_crowleyGUID;
        uint64   m_phinOdelicGUID;
        uint64   m_bartoloGinsettiGUID;
        uint64   m_loremasterDibbsGUID;
        uint64   m_henryMalebGUID;
        uint64   m_caretakersSmithersGUID;
        uint64   m_sophiaGUID;
        bool     m_animatonIsStarted;

        void Reset() override
        {
            m_playerGUID = 0;
            m_bloodfangGUID = 0;
            m_crowleyGUID = 0;
            m_phinOdelicGUID = 0;
            m_bartoloGinsettiGUID = 0;
            m_loremasterDibbsGUID = 0;
            m_henryMalebGUID = 0;
            m_caretakersSmithersGUID = 0;
            m_sophiaGUID = 0;
            m_events.Reset();
            m_events.ScheduleEvent(EVENT_CHECK_QUEST, 1000);
            m_animatonIsStarted = false;
        }

        void JustSummoned(Creature* summon) override 
        { 
            switch (summon->GetEntry())
            {
            case NPC_BLOODFANG:
                m_bloodfangGUID = summon->GetGUID();
                break;
            case NPC_CROWLEY:
                m_crowleyGUID = summon->GetGUID();
                break;
            case NPC_PHIN_ODELIC:
                m_phinOdelicGUID = summon->GetGUID();
                SetCreatureValues(summon);
                break;
            case NPC_BARTOLO_GINSETTI:
                m_bartoloGinsettiGUID = summon->GetGUID();
                SetCreatureValues(summon);
                break;
            case NPC_LOREMASTER_DIBBS:
                m_loremasterDibbsGUID = summon->GetGUID();
                SetCreatureValues(summon);
                break;
            case NPC_MAGISTRATE_HENRY_MALEB:
                m_henryMalebGUID = summon->GetGUID();
                SetCreatureValues(summon);
                break;
            case NPC_CARETAKER_SMITHERS:
                m_caretakersSmithersGUID = summon->GetGUID();
                SetCreatureValues(summon);
                break;
            case NPC_SOPHIA_ZWOSKI:
                m_sophiaGUID = summon->GetGUID();
                SetCreatureValues(summon);
                break;
            }
            summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            switch (spell->Id)
            {
            case SPELL_GENERAL_TRIGGER_84107:               
                m_events.RescheduleEvent(EVENT_MASTER_RESET, 30000);
                break;
            case SPELL_GENERAL_TRIGGER_84102:
                if (Creature* camera = me->FindNearestCreature(45003, 25.0f))
                    if (Creature* crowley = sObjectAccessor->GetCreature(*me, m_crowleyGUID))
                        if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        {
                            // camera spell is wrong
                            // camera->CastSpell(crowley->GetPositionX(), crowley->GetPositionY(), crowley->GetPositionZ(), 83763, true);
                        }
                break;
            }
        }

        void EnterEvadeMode() override { }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_QUEST:
                {
                    if (!m_animatonIsStarted)
                        if (Player* player = me->FindNearestPlayer(15.0f))
                            if (abs(player->GetPositionZ() - me->GetPositionZ()) < 1.0f)
                                if (player->GetQuestStatus(QUEST_NO_ESCAPE) == QUEST_STATUS_INCOMPLETE)
                                {
                                    m_playerGUID = player->GetGUID();
                                    m_animatonIsStarted = true;
                                    m_events.ScheduleEvent(EVENT_START_ANIMATION, 100);
                                    m_events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
                                    m_events.ScheduleEvent(EVENT_MASTER_RESET, 250000);
                                }

                    m_events.ScheduleEvent(EVENT_CHECK_QUEST, 1000);
                    break;
                }
                case EVENT_CHECK_PLAYER:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        if (player->IsAlive() || player->IsInWorld())
                        {
                            m_events.ScheduleEvent(EVENT_CHECK_PLAYER, 1000);
                            break;
                        }
                } // no break;
                case EVENT_MASTER_RESET:
                {
                    DespawnAllSummons();
                    Reset();
                    break;
                }
                case EVENT_START_ANIMATION:
                {
                    me->CastSpell(994.530f, 687.740f, 74.8984f, SPELL_SUMMON_BLOODFANG, true);
                    me->CastSpell(994.562f, 691.186f, 74.8984f, SPELL_SUMMON_CROWLEY, true);
                    me->CastSpell(1002.520f, 693.027f, 76.1922f, SPELL_SUMMON_PHIN_ODELIC, true);
                    me->CastSpell(1002.760f, 687.195f, 76.1922f, SPELL_SUMMON_BARTOLO_GINSETTI, true);
                    me->CastSpell(1002.800f, 684.256f, 76.1922f, SPELL_SUMMON_LOREMASTER_DIBBS, true);
                    me->CastSpell(1000.670f, 689.759f, 76.1922f, SPELL_SUMMON_MAGISTRATE_HENRY_MALEB, true);
                    me->CastSpell(1002.700f, 695.775f, 76.1922f, SPELL_SUMMON_CARETAKER_SMITHERS, true);
                    me->CastSpell(1004.530f, 688.619f, 76.1922f, SPELL_SUMMON_SOPHIA, true);
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                    {
                        Creature* agatha = me->FindNearestCreature(NPC_AGATHA, 30.0f);
                        if (!agatha)
                            player->CastSpell(982.57f, 671.04f, 77.298f, SPELL_SUMMON_AGATHA, true);
                        me->CastSpell(player, SPELL_FORCE_CAST_FENRIS_CAMERA, true);
                    }
                    break;
                }
                }
            }
        }

        void DespawnAllSummons()
        {
            if (Creature* creature = sObjectAccessor->GetCreature(*me, m_bloodfangGUID))
                creature->DespawnOrUnsummon(10);
            if (Creature* creature = sObjectAccessor->GetCreature(*me, m_crowleyGUID))
                creature->DespawnOrUnsummon(10);
            if (Creature* creature = sObjectAccessor->GetCreature(*me, m_phinOdelicGUID))
                creature->DespawnOrUnsummon(10);
            if (Creature* creature = sObjectAccessor->GetCreature(*me, m_bartoloGinsettiGUID))
                creature->DespawnOrUnsummon(10);
            if (Creature* creature = sObjectAccessor->GetCreature(*me, m_loremasterDibbsGUID))
                creature->DespawnOrUnsummon(10);
            if (Creature* creature = sObjectAccessor->GetCreature(*me, m_henryMalebGUID))
                creature->DespawnOrUnsummon(10);
            if (Creature* creature = sObjectAccessor->GetCreature(*me, m_caretakersSmithersGUID))
                creature->DespawnOrUnsummon(10);
            if (Creature* creature = sObjectAccessor->GetCreature(*me, m_sophiaGUID))
                creature->DespawnOrUnsummon(10);
            if (Creature* creature = me->FindNearestCreature(45003, 30.0f))
                creature->DespawnOrUnsummon(10);
        }

        void SetCreatureValues(Creature* npc)
        {
            Position pos = npc->GetPosition();
            pos.SetOrientation(3.33f);
            npc->SetHomePosition(pos);
            npc->GetMotionMaster()->MoveTargetedHome();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_fenris_keep_stalker_45032AI(creature);
    }
};

// 44989 // quest 27099
class npc_lord_darius_crowley_44989 : public CreatureScript
{
public:
    npc_lord_darius_crowley_44989() : CreatureScript("npc_lord_darius_crowley_44989") { }

    struct npc_lord_darius_crowley_44989AI : public ScriptedAI
    {
        npc_lord_darius_crowley_44989AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64 m_playerGUID;

        void Initialize()
        {
            m_playerGUID = 0;
        }

        void Reset() override
        {

        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
                m_playerGUID = player->GetGUID();
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            switch (spell->Id)
            {
            case SPELL_GENERAL_TRIGGER_84102:
                m_events.ScheduleEvent(EVENT_ANIMATION, 500);
                break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {                
                case EVENT_ANIMATION + 0:
                {
                    Talk(0);
                    m_events.ScheduleEvent(EVENT_ANIMATION + 1, 4700);
                    break;
                }
                case EVENT_ANIMATION + 1:
                {
                    Talk(1);
                    m_events.ScheduleEvent(EVENT_ANIMATION + 2, 4700);
                    break;
                }
                case EVENT_ANIMATION + 2:
                {
                    Talk(2);
                    m_events.ScheduleEvent(EVENT_ANIMATION + 3, 4700);
                    break;
                }
                case EVENT_ANIMATION + 3:
                {
                    Talk(3);
                    m_events.ScheduleEvent(EVENT_ANIMATION + 4, 4700);
                    break;
                }
                case EVENT_ANIMATION + 4:
                {
                    Talk(4);
                    m_events.ScheduleEvent(EVENT_ANIMATION + 5, 6100);
                    break;
                }
                case EVENT_ANIMATION + 5:
                {
                    Talk(5);
                    m_events.ScheduleEvent(EVENT_ANIMATION + 6, 9500);
                    break;
                }
                case EVENT_ANIMATION + 6:
                {
                    me->CastSpell(me, SPELL_CONVERSATION_TRIGGER_84076, true);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_lord_darius_crowley_44989AI(creature);
    }
};

// 44993 // quest 27099
class npc_phin_odelic_44993 : public CreatureScript
{
public:
    npc_phin_odelic_44993() : CreatureScript("npc_phin_odelic_44993") { }

    struct npc_phin_odelic_44993AI : public ScriptedAI
    {
        npc_phin_odelic_44993AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64 m_playerGUID;
        bool   m_isWorgen;

        void Initialize()
        {
            m_playerGUID = 0;
        }

        void Reset() override
        {
            m_isWorgen = false;
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
                m_playerGUID = player->GetGUID();
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            switch (spell->Id)
            {
            case SPELL_CONVERSATION_TRIGGER_84077:
                m_events.ScheduleEvent(EVENT_DRINKING, 100);
                break;
            }
            if (!m_isWorgen)
                if (me->HasAura(84094))
                    me->RemoveAura(84094);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_DRINKING:
                {
                    // place for emote
                    m_events.ScheduleEvent(EVENT_MORPHING, 3000);
                    break;
                }
                case EVENT_MORPHING:
                {
                    m_isWorgen = true;
                    me->CastSpell(me, 84094);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_phin_odelic_44993AI(creature);
    }
};

// 44994 // quest 27099
class npc_bartolo_ginsetti_44994 : public CreatureScript
{
public:
    npc_bartolo_ginsetti_44994() : CreatureScript("npc_bartolo_ginsetti_44994") { }

    struct npc_bartolo_ginsetti_44994AI : public ScriptedAI
    {
        npc_bartolo_ginsetti_44994AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64 m_playerGUID;
        bool   m_isWorgen;

        void Initialize()
        {
            m_playerGUID = 0;
        }

        void Reset() override
        {
            m_isWorgen = false;
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
                m_playerGUID = player->GetGUID();
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            switch (spell->Id)
            {
            case SPELL_CONVERSATION_TRIGGER_84077:
                m_events.ScheduleEvent(EVENT_DRINKING, 100);
                break;
            }
            if (!m_isWorgen)
                if (me->HasAura(84095))
                    me->RemoveAura(84095);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_DRINKING:
                {
                    // place for emote
                    m_events.ScheduleEvent(EVENT_MORPHING, 3000);
                    break;
                }
                case EVENT_MORPHING:
                {
                    m_isWorgen = true;
                    me->CastSpell(me, 84095);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_bartolo_ginsetti_44994AI(creature);
    }
};

// 44995 // quest 27099
class npc_loremaster_dibbs_44995 : public CreatureScript
{
public:
    npc_loremaster_dibbs_44995() : CreatureScript("npc_loremaster_dibbs_44995") { }

    struct npc_loremaster_dibbs_44995AI : public ScriptedAI
    {
        npc_loremaster_dibbs_44995AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64 m_playerGUID;
        bool   m_isWorgen;

        void Initialize()
        {
            m_playerGUID = 0;
        }

        void Reset() override
        {
            m_isWorgen = false;
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
                m_playerGUID = player->GetGUID();
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            switch (spell->Id)
            {
            case SPELL_CONVERSATION_TRIGGER_84077:
                m_events.ScheduleEvent(EVENT_DRINKING, 100);
                break;
            }
            if (!m_isWorgen)
                if (me->HasAura(84096))
                    me->RemoveAura(84096);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_DRINKING:
                {
                    // place for emote
                    m_events.ScheduleEvent(EVENT_MORPHING, 3000);
                    break;
                }
                case EVENT_MORPHING:
                {
                    m_isWorgen = true;
                    me->CastSpell(me, 84096);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_loremaster_dibbs_44995AI(creature);
    }
};

// 44996 // quest 27099
class npc_magistrate_henry_maleb_44996: public CreatureScript
{
public:
    npc_magistrate_henry_maleb_44996() : CreatureScript("npc_magistrate_henry_maleb_44996") { }

    struct npc_magistrate_henry_maleb_44996AI : public ScriptedAI
    {
        npc_magistrate_henry_maleb_44996AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64 m_playerGUID;
        bool   m_isWorgen;

        void Initialize()
        {
            m_playerGUID = 0;
        }

        void Reset() override
        {
            m_isWorgen = false;
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
                m_playerGUID = player->GetGUID();
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            switch (spell->Id)
            {
            case SPELL_CONVERSATION_TRIGGER_84076:
                if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                    me->CastSpell(player, SPELL_ARMORE_CAMERA, true);
                m_events.ScheduleEvent(EVENT_ANIMATION, 500);
                break;
            case SPELL_CONVERSATION_TRIGGER_84077:
                m_events.ScheduleEvent(EVENT_DRINKING, 100);
                break;
            }
            if (!m_isWorgen)
                if (me->HasAura(84097))
                    me->RemoveAura(84097);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_ANIMATION:
                {
                    Talk(0);
                    m_events.ScheduleEvent(EVENT_ANIMATION + 1, 10800);
                    break;
                }
                case EVENT_ANIMATION + 1:
                {
                    Talk(1);
                    m_events.ScheduleEvent(EVENT_ANIMATION + 2, 3500);
                    break;
                }
                case EVENT_ANIMATION + 2:
                {
                    me->CastSpell(me, SPELL_CONVERSATION_TRIGGER_84077, true);
                    break;
                }
                case EVENT_DRINKING:
                {
                    
                    m_events.ScheduleEvent(EVENT_MORPHING, 3000);
                    break;
                }
                case EVENT_MORPHING:
                {
                    m_isWorgen = true;
                    me->CastSpell(me, 84097);
                    me->CastSpell(me, SPELL_GENERAL_TRIGGER_84107, true);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_magistrate_henry_maleb_44996AI(creature);
    }
};

// 44997 // quest 27099
class npc_caretaker_smithers_44997 : public CreatureScript
{
public:
    npc_caretaker_smithers_44997() : CreatureScript("npc_caretaker_smithers_44997") { }

    struct npc_caretaker_smithers_44997AI : public ScriptedAI
    {
        npc_caretaker_smithers_44997AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64 m_playerGUID;
        bool   m_isWorgen;

        void Initialize()
        {
            m_playerGUID = 0;
        }

        void Reset() override
        {
            m_isWorgen = false;
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
                m_playerGUID = player->GetGUID();
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            switch (spell->Id)
            {
            case SPELL_CONVERSATION_TRIGGER_84077:
                m_events.ScheduleEvent(EVENT_DRINKING, 100);
                break;
            }
            if (!m_isWorgen)
                if (me->HasAura(84098))
                    me->RemoveAura(84098);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_DRINKING:
                {
                    // place for emote
                    m_events.ScheduleEvent(EVENT_MORPHING, 3000);
                    break;
                }
                case EVENT_MORPHING:
                {
                    m_isWorgen = true;
                    me->CastSpell(me, 84098);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_caretaker_smithers_44997AI(creature);
    }
};

// 45002 // quest 27099
class npc_sophia_zwoski_45002 : public CreatureScript
{
public:
    npc_sophia_zwoski_45002() : CreatureScript("npc_sophia_zwoski_45002") { }

    struct npc_sophia_zwoski_45002AI : public ScriptedAI
    {
        npc_sophia_zwoski_45002AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64 m_playerGUID;
        bool   m_isWorgen;

        void Initialize()
        {
            m_playerGUID = 0;
        }

        void Reset() override
        {
            m_isWorgen = false;
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
                m_playerGUID = player->GetGUID();
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            switch (spell->Id)
            {
            case SPELL_CONVERSATION_TRIGGER_84077:
                m_events.ScheduleEvent(EVENT_DRINKING, 100);
                break;
            }
            if (!m_isWorgen)
                if (me->HasAura(84099))
                    me->RemoveAura(84099);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {               
                case EVENT_DRINKING:
                {
                    // place for emote
                    m_events.ScheduleEvent(EVENT_MORPHING, 3000);
                    break;
                }
                case EVENT_MORPHING:
                {
                    m_isWorgen = true;
                    me->CastSpell(me, 84099);
                    m_events.ScheduleEvent(EVENT_HOWLING, 1500);
                    break;
                }
                case EVENT_HOWLING:
                {
                    me->PlayDirectSound(SOUND_WORGEN_HOWLING);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_sophia_zwoski_45002AI(creature);
    }
};

// 45003 // quest 27099
class npc_camera_45003 : public CreatureScript
{
public:
    npc_camera_45003() : CreatureScript("npc_camera_45003") { }

    struct npc_camera_45003AI : public VehicleAI
    {
        npc_camera_45003AI(Creature* creature) : VehicleAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_playerGUID;

        void Initialize()
        {
            m_playerGUID = 0;
        }

        void Reset() override
        {
            me->SetVisible(false);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
            me->SetReactState(REACT_PASSIVE);
        }

        void IsSummonedBy(Unit* summoner) override 
        { 
            if (Player* player = summoner->ToPlayer())
                m_playerGUID = player->GetGUID();
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool apply) override 
        { 
            if (apply && seatId == 0)
                m_events.ScheduleEvent(EVENT_MOVE_TO_STARTPOINT, 100);
            if (apply && seatId == 1)
                passenger->SetFacingTo(0.0f);
            if (!apply && seatId == 1)
                me->DespawnOrUnsummon(1000);
        }

        void MovementInform(uint32 type, uint32 id) override 
        { 
            if (type == POINT_MOTION_TYPE && id == 1230)
                m_events.ScheduleEvent(EVENT_CHANGE_TO_SEAT_2, 100);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_MOVE_TO_STARTPOINT:
                {
                    me->GetMotionMaster()->MovePoint(1230, 980.7f, 689.14f, 76.9f);
                    break;
                }
                case EVENT_CHANGE_TO_SEAT_2:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                    {
                        player->EnterVehicle(me, 1);
                        me->CastSpell(player, 84091, true);
                    }
                    m_events.ScheduleEvent(EVENT_TRIGGER_84102, 1500);
                    break;
                }
                case EVENT_TRIGGER_84102:
                {
                    me->CastSpell(me, SPELL_GENERAL_TRIGGER_84102, true);
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_camera_45003AI(creature);
    }
};



void AddSC_silverpine_forest()
{
    new npc_deathstalker_erland();
    new npc_grand_executor_mortuus_44615();
    new spell_raise_forsaken_83173();
    new spell_forsaken_trooper_master_script_83149();
    new npc_fallen_human_44592();
    new npc_worgen_renegade_44793();
    new npc_forsaken_trooper_44791();
    new npc_bat_handler_maggotbreath_44825();
    new npc_forsaken_bat_44821();
    new go_abandoned_outhouse_205143();
    new npc_deathstalker_rane_yorick_44882();
    new npc_armoire_44893();
    new npc_armoire_44894();
    new npc_lord_darius_crowley_44883();
    new npc_packleader_ivar_bloodfang_44884();
    new npc_lady_sylvanas_windrunner_44365();
    new npc_orc_sea_pup_44914();
    new npc_admiral_hatchet_44916();
    new npc_salty_rocka_45498();
    new spell_sea_pup_trigger_83865();
    new spell_pick_up_orc_crate_83838();
    new npc_webbed_victim_44941();
    new npc_orc_sea_dog_44942();
    new npc_forest_ettin_44367();
    new spell_reverse_cast_ride_vehicle_83904();
    new npc_agatha_44951();
    new npc_hillsbrad_refugee_44966();
    new npc_fenris_keep_stalker_45032();
    new npc_lord_darius_crowley_44989();
    new npc_phin_odelic_44993();
    new npc_bartolo_ginsetti_44994();
    new npc_loremaster_dibbs_44995();
    new npc_magistrate_henry_maleb_44996();
    new npc_caretaker_smithers_44997();
    new npc_sophia_zwoski_45002();
    new npc_camera_45003();

}
