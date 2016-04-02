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

        void WaypointReached(uint32 waypointId)
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

        void EnterCombat(Unit* who)
        {
            Talk(SAY_AGGRO, who);
        }
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
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

// 44615
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

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
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
        npc_grand_executor_mortuus_44615AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64  m_playerGUID;
        uint64  m_garroshGUID;
        uint64  m_cromushGUID;
        uint64  m_sylvanasGUID;
        uint64  m_agathaGUID;
        uint8   m_animPhase;
        std::list<uint64>spawnedList;
        std::list<uint64>portalList;

        void Initialize()
        {

        }

        void Reset() override
        {
            m_events.Reset();
            m_playerGUID = NULL;
            m_garroshGUID = NULL;
            m_cromushGUID = NULL;
            m_sylvanasGUID = NULL;
            m_agathaGUID = NULL;
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

// 83173
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

// 83149
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

// 44592 44593
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
        
    };

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        switch (action) // is option_id in gossip_menu_option
        {
        case 1:
           
            break;
        }
        player->CLOSE_GOSSIP_MENU();
        
        return true;
    }

    struct npc_bat_handler_maggotbreath_44825AI : public ScriptedAI
    {
        npc_bat_handler_maggotbreath_44825AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        
        void Initialize()
        {

        }

        void Reset() override
        {
            m_events.Reset();
           
        }

  

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

          

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_bat_handler_maggotbreath_44825AI(creature);
    }
};

// 44821 // quest 26998
class npc_forsaken_bat_44821 : public CreatureScript
{
public:
    npc_forsaken_bat_44821() : CreatureScript("npc_forsaken_bat_44821") { }

    enum eNPC
    {

    };

    struct npc_forsaken_bat_44821AI : public ScriptedAI
    {
        npc_forsaken_bat_44821AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;

        void Initialize()
        {

        }

        void Reset() override
        {
            m_events.Reset();

        }



        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);



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

}
