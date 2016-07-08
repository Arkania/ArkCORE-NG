/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

#include "ScriptPCH.h"
#include "Unit.h"
#include "ScriptedEscortAI.h"
#include "ScriptedFollowerAI.h"
#include "Vehicle.h"
#include "GameObjectAI.h"
#include "CreatureGroups.h"


// 68903
class spell_round_up_horse_68903 : public SpellScriptLoader
{
public:
    spell_round_up_horse_68903() : SpellScriptLoader("spell_round_up_horse_68903") { }

    class spell_round_up_horse_68903_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_round_up_horse_68903_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            if (!sSpellMgr->GetSpellInfo(68903))
                return false;
            return true;
        }

        void HandleEffectDummy(SpellEffIndex /*effIndex*/)
        {
            if (GetHitUnit()->GetTypeId() != TYPEID_UNIT || GetCaster()->GetTypeId() != TYPEID_PLAYER || GetCaster()->ToPlayer()->GetQuestStatus(14416) != QUEST_STATUS_INCOMPLETE)
                return ;
            GetHitUnit()->ToCreature()->DespawnOrUnsummon();
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_round_up_horse_68903_SpellScript::HandleEffectDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_round_up_horse_68903_SpellScript();
    }
};

/*###### Quest Gasping for Breath  ######*/

// 68735
class spell_rescue_drowning_watchman_68735 : public SpellScriptLoader
{
public:
    spell_rescue_drowning_watchman_68735() : SpellScriptLoader("spell_rescue_drowning_watchman_68735") { }

    class spell_rescue_drowning_watchman_68735_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rescue_drowning_watchman_68735_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            if (!sSpellMgr->GetSpellInfo(68735))
                return false;
            return true;
        }

        void HandleEffectDummy(SpellEffIndex /*effIndex*/)
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER || GetHitUnit()->GetTypeId() != TYPEID_UNIT || GetCaster()->GetVehicleKit() == NULL)
                return ;
            if (GetCaster()->ToPlayer()->GetQuestStatus(14395) != QUEST_STATUS_INCOMPLETE)
            {
                GetCaster()->RemoveAurasDueToSpell(68735);
                return;
            }
            if (GetCaster()->IsInWater())
                GetHitUnit()->CastCustomSpell(VEHICLE_SPELL_RIDE_HARDCODED, SPELLVALUE_BASE_POINT0, 1, GetCaster(), false);
            else if (GetHitUnit()->GetVehicle())
            {
                GetCaster()->GetVehicleKit()->RemoveAllPassengers();
                GetHitUnit()->RemoveAurasDueToSpell(68730);
                GetHitUnit()->CastSpell(GetHitUnit(), 68442, true);
                GetCaster()->ToPlayer()->KilledMonsterCredit(36440,0);
                GetCaster()->RemoveAurasDueToSpell(68735);
                GetHitUnit()->ToCreature()->DespawnOrUnsummon(5000);
                GetHitUnit()->ToCreature()->AI()->Talk(0);
            }
            else
                GetCaster()->RemoveAurasDueToSpell(68735);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_rescue_drowning_watchman_68735_SpellScript::HandleEffectDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_rescue_drowning_watchman_68735_SpellScript();
    }
};

/*###### Quest Gasping for Breath END  ######*/

/*###### Losing Your Tail ######*/

/*######
## npc_trigger_quest_24616
######*/
class npc_trigger_quest_24616 : public CreatureScript
{
public:
    npc_trigger_quest_24616() : CreatureScript("npc_trigger_quest_24616") { }

    struct npc_trigger_quest_24616AI : public ScriptedAI
    {
        npc_trigger_quest_24616AI(Creature* creature) : ScriptedAI(creature)  { }

        void Reset()
        {
            mui_timerAllowSummon = urand(3000, 5000);
            allowSummon = false;
            playerGUID = 0;
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (who->GetTypeId() != TYPEID_PLAYER)
                return ;
            if (who->ToPlayer()->GetQuestStatus(24616) != QUEST_STATUS_INCOMPLETE || me->FindNearestCreature(37953, 100, false) != NULL)
                return ;
            if (me->IsWithinDistInMap(who, 20.0f))
            {
                allowSummon = true;
                playerGUID = who->GetGUID();
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!allowSummon)
                return;
            if (mui_timerAllowSummon <= diff)
            {
				if (Player *player = ObjectAccessor::GetPlayer(*me, playerGUID))
                    if (me->FindNearestCreature(37953, 100) == NULL)
                        me->CastSpell(player, 70794, true);
                allowSummon = false;
                playerGUID = 0;
                mui_timerAllowSummon = urand(3000, 5000);
            }
            else mui_timerAllowSummon -= diff;
        }

    private :
        uint32 mui_timerAllowSummon;
        bool allowSummon;
        uint64 playerGUID;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_trigger_quest_24616AI(creature);
    }
};

// 38553
class npc_krennan_aranas_38553 : public CreatureScript
{
public:
    npc_krennan_aranas_38553() : CreatureScript("npc_krennan_aranas_38553") { }

    enum eNpc
    {
        QUEST_THE_BATTLE_FOR_GILNEAS_CITY = 24904,
        NPC_PRINCE_LIAM_GREYMANE_BATTLE = 38218,
        ACTION_START_EVENT = 101,
    };

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (uiAction)
        {
        case GOSSIP_ACTION_INFO_DEF+1:
            player->CLOSE_GOSSIP_MENU();
            CAST_AI(npc_krennan_aranas_38553::npc_krennan_aranas_38553AI, creature->AI())->StartBattle(player);
            break;

        case GOSSIP_ACTION_INFO_DEF+2:
            player->CLOSE_GOSSIP_MENU();
            CAST_AI(npc_krennan_aranas_38553::npc_krennan_aranas_38553AI, creature->AI())->EndBattle();
            break;
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(QUEST_THE_BATTLE_FOR_GILNEAS_CITY) == QUEST_STATUS_INCOMPLETE)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "start battle !", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

        if (player->IsGameMaster())
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "(GM ONLY) RESET EVENT!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

        player->SEND_GOSSIP_MENU(2474, creature->GetGUID());

        return true;
    }

    struct npc_krennan_aranas_38553AI : public ScriptedAI
    {
        npc_krennan_aranas_38553AI(Creature *c) : ScriptedAI(c) {}

        uint64 princeGUID;

        void Reset()
        {
            princeGUID = 0;
            if (Creature* newPrince = me->SummonCreature(NPC_PRINCE_LIAM_GREYMANE_BATTLE, -1408.661f, 1260.017f, 36.51123f, 1.79f, TEMPSUMMON_DEAD_DESPAWN, 180000))
                princeGUID = newPrince->GetGUID();
        }

        void StartBattle(Player* player)
        {
			if (Creature* prince = ObjectAccessor::GetCreature(*me, princeGUID))
            {
                if (me->GetDistance2d(prince->GetPositionX(), prince->GetPositionY()) > 50)
                    me->MonsterSay("event already started please wait a minute.", LANG_UNIVERSAL, 0);
                else
                {
                    prince->AI()->DoAction(ACTION_START_EVENT);
                    Talk(0, player);
                }
            }
            else
            {
                princeGUID = 0;
                if (Creature* newPrince = me->SummonCreature(NPC_PRINCE_LIAM_GREYMANE_BATTLE, -1408.661f, 1260.017f, 36.51123f, 1.79f, TEMPSUMMON_DEAD_DESPAWN, 180000))
                {
                    princeGUID = newPrince->GetGUID();
                    prince->AI()->DoAction(ACTION_START_EVENT);
                    Talk(0, player);
                }
            }
        }

        void EndBattle()
        {
			if (Creature* prince = ObjectAccessor::GetCreature(*me, princeGUID))
                prince->DespawnOrUnsummon();
            princeGUID = 0;
            if (Creature* newPrince = me->SummonCreature(NPC_PRINCE_LIAM_GREYMANE_BATTLE, -1408.661f, 1260.017f, 36.51123f, 1.79f, TEMPSUMMON_DEAD_DESPAWN, 180000))
                princeGUID = newPrince->GetGUID();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_krennan_aranas_38553AI(pCreature);
    }
};

/*######
## npc_prince_liam_greymane_gilneas ??? 38474
######*/
class npc_prince_liam_greymane_gilneas : public CreatureScript
{
    public:    
        npc_prince_liam_greymane_gilneas() : CreatureScript("npc_prince_liam_greymane_gilneas") {}

    enum eNpc
    {
        DATA_GROUP = 101,
        GROUP_1,
        GROUP_2,
        ACTION_START_EVENT,
    };

    struct npc_prince_liam_greymane_gilneasAI : public npc_escortAI
    {
        npc_prince_liam_greymane_gilneasAI(Creature *c) : npc_escortAI(c) , summons(me) { }

        void Reset()
        {
            me->CastSpell(me, 72069, true);

            startEvent = false;
            intro = true;
            canFollow = false;
            phase = 1;
            intoTimer = 5000;
            checkTimer = 3000;
            summons.DespawnAll();
            float summon_x = me->GetPositionX() - 6;
            float summon_y = me->GetPositionY() - 4;

            int j = 0;
            int row = 0;

            for (int i = 0; i < 70; i++)
            {
                if (j > 6)
                {
                    j = 0;
                    row++;
                    summon_y -= 3;
                    summon_x = me->GetPositionX() - 6;
                }

                if (Creature * milit = me->SummonCreature(38221, (summon_x+cos(5.42f)*row), (summon_y-sin(5.42f)*j), 36.51123f, 1.79f, TEMPSUMMON_MANUAL_DESPAWN))
                {
                    militiamans[i] = milit->GetGUID();
                    if (i % 2 == 0)
                        milit->AI()->SetData(DATA_GROUP, GROUP_1);
                    else
                        milit->AI()->SetData(DATA_GROUP, GROUP_1); // need to be improved...
                }
                summon_x += 2;
                j++;
            }
            mui_moveTimer = 1000;
        }

        void JustDied(Unit* /*killer*/)
        {
            summons.DespawnAll();
        }

        bool CanFollow() { return canFollow; }

        void EnterCombat(Unit* pWho)
        {
            Talk(10);
        }

        void moveGroup(uint32 group, float x, float y, float z)
        {
            for (int i = 0; i < 70; i++)
				if (Creature *milit = ObjectAccessor::GetCreature(*me, militiamans[i]))
                    if (milit->AI()->GetData(DATA_GROUP) == group)
                    {
                        milit->SetHomePosition(x, y, z, milit->GetOrientation());
                        milit->GetMotionMaster()->MovePoint(0, x, y, z);
                    }
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
        }

        void SummonedCreatureDies(Creature* summon, Unit* /*killer*/)
        {
            summons.Despawn(summon);
        }

        void WaypointReached(uint32 point)
        {
            RefreshMovementMilitary(GROUP_1);
            switch (point)
            {
            case 1:
                moveGroup(GROUP_2, -1487.67f, 1345.69f, 35.56f);
                break;
            case 3:
                moveGroup(GROUP_2, -1551.90f, 1327.45f, 35.56f);
                break;
            case 5:
                Talk(7);
                if (Creature *c = me->SummonCreature(38426, -1549.20f, 1285.96f, 11.78f, 3.47f, TEMPSUMMON_MANUAL_DESPAWN))
                    c->AI()->DoAction(ACTION_START_EVENT);
                SetEscortPaused(true);
                break;
            case 6:
                moveGroup(GROUP_2, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
                Talk(8);
                break;
            case 7 :
                moveGroup(GROUP_2, -1657.01f, 1337.70f, 15.135f);
                break;
            case 8: //crowley
                moveGroup(GROUP_2, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
                Talk(9);
                break;
            case 10:
            case 11:
            case 12:
                moveGroup(GROUP_2, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
                break;
            case 13:
                if (Creature *abo = me->SummonCreature(38331, -1710.466f, 1407.905f, 21.75196f, -1.89314f, TEMPSUMMON_DEAD_DESPAWN, 60000))
                {
                    abo->GetMotionMaster()->MoveJump(-1710.466f, 1407.905f, 21.75196f, 20.0f, 20.0f);
                    if (Creature *darius = me->SummonCreature(38415, -1771.81f, 1341.33f, 19.75, 0.81314f, TEMPSUMMON_MANUAL_DESPAWN))
                        darius->AI()->SetGUID(abo->GetGUID());
                }
                break;
            case 14 :
                moveGroup(GROUP_2, -1761.24f, 1512.72f, 26.22f);
                break;
            case 15:
                for (int i = 0; i < 70; i++)
					if (Creature *milit = ObjectAccessor::GetCreature(*me, militiamans[i]))
                        milit->AI()->SetData(DATA_GROUP, GROUP_1);
                break;
            case 19:
                if (Creature *c = me->FindNearestCreature(38470, 100, true))
                    c->AI()->SetData(0, 1);
                summons.DespawnAll();
                me->DespawnOrUnsummon();
                break;
            }
        }

        void RefreshMovementMilitary(uint32 group)
        {
            float x, y, z;
            for (int i = 0; i < 70; i++)
            {
                float distance = urand(0, 7);
                float angle = frand(-3 * M_PI / 4, 3 * M_PI / 2);
                me->GetNearPoint(me, x, y, z, me->GetObjectSize(), distance, angle);
				if (Creature *milit = ObjectAccessor::GetCreature(*me, militiamans[i]))
                    if (milit->AI()->GetData(DATA_GROUP) == group)
                        milit->SetHomePosition(x, y, z, me->GetOrientation());
            }
        }

        void DoAction(int32 info)
        {
            switch (info)
            {
                case ACTION_START_EVENT:
                    startEvent = true;
                    break;
                default:
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!startEvent)
                return;
            npc_escortAI::UpdateAI(diff);

            if (canFollow)
            {
                if (mui_moveTimer <= diff)
                {
                    RefreshMovementMilitary(GROUP_1);
                    mui_moveTimer = 10000;
                }
                else
                    mui_moveTimer -= diff;
            }

            if (intro)
            {
                if (intoTimer <= diff)
                {
                    switch (phase)
                    {
                    case 1:
                        Talk(0);
                        intoTimer = 10000;
                        break;
                    case 2:
                        Talk(1);
                        intoTimer = 10000;
                        break;
                    case 3:
                        Talk(2);
                        intoTimer = 12000;
                        break;
                    case 4:
                        Talk(3);
                        intoTimer = 10000;
                        break;
                    case 5:
                        Talk(4);
                        intoTimer = 12000;
                        break;
                    case 6:
                        Talk(5);
                        intoTimer = 5500;
                        break;
                    case 7:
                        Talk(6);
                        intoTimer = 1500;
                        Start(true, true);
                        SetDespawnAtEnd(true);
                        break;
                    case 8:
                        me->PlayDistanceSound(22584);
                        for (int i = 0; i < 70; i++)
							if (Creature *milit = ObjectAccessor::GetCreature(*me, militiamans[i]))
                            {
                                milit->HandleEmoteCommand(25);
                                float distance = urand(7, 15);
                                float angle = frand(-3 * M_PI / 4, 3 * M_PI / 4);
                                milit->GetMotionMaster()->MoveFollow(me, distance, angle, MOTION_SLOT_ACTIVE);
                            }
                        intro = false;
                        canFollow = true;
                        break;
                    }
                    phase++;
                } else intoTimer -= diff;
            }

            if (checkTimer <= diff)
            {
                if (!me->HasAura(72069))
                    me->CastSpell(me, 72069, true);
                checkTimer = 3000;
            } else checkTimer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

    private :
        bool intro;
        bool canFollow;
        uint32 phase;
        uint32 intoTimer;
        uint32 checkTimer;
        uint64 militiamans[70];
        uint32 mui_moveTimer;
        bool startEvent;
        SummonList summons;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_prince_liam_greymane_gilneasAI(creature);
    }
};

/*######
## npc_lorna_crowley_event
######*/
class npc_lorna_crowley_event : public CreatureScript
{
public:
    npc_lorna_crowley_event() : CreatureScript("npc_lorna_crowley_event") { }

    enum eNpc
    {
        ACTION_START_EVENT = 101,
        DATA_GROUP,        
    };

    struct npc_lorna_crowley_eventAI : public ScriptedAI
    {
        npc_lorna_crowley_eventAI(Creature *c) : ScriptedAI(c) {}

        void Reset()
        {
            eventInProgress = false;
            mui_moveTimer = 5000;
            mui_attack = 8000;
        }

        void MovementInform(uint32 type, uint32 point)
        {
            if (!eventInProgress)
                Talk(0);
            eventInProgress = true;
            me->DespawnOrUnsummon(60000);
        }

        void DoAction(int32 info)
        {
            switch (info)
            {
                case ACTION_START_EVENT:
                    float summon_x = me->GetPositionX();
                    float summon_y = me->GetPositionY();
                    float summon_z = me->GetPositionZ();
                    for (int i = 0; i < 12; i++)
                        if (Creature * milit = me->SummonCreature(38425, summon_x, summon_y, summon_z, 0.0f, TEMPSUMMON_MANUAL_DESPAWN))
                        {
                            if (i == 0 || i == 1 || i == 2)
                                citizenGUID[i] = milit->GetGUID();
                            if (i != 0)
								if (Creature *firstCiti = ObjectAccessor::GetCreature(*me, citizenGUID[0]))
                                    milit->GetMotionMaster()->MoveFollow(firstCiti, urand(0, 5), frand(-3 * M_PI / 8, 3 * M_PI / 8), MOTION_SLOT_ACTIVE);
                        }
					if (Creature *firstCiti = ObjectAccessor::GetCreature(*me, citizenGUID[0]))
                        firstCiti->GetMotionMaster()->MovePoint(0, -1571.79f, 1318.833f, 35.56271f);
                    me->GetMotionMaster()->MovePoint(0, -1571.79f, 1318.833f, 35.56271f);
                    if (Creature *c = me->SummonCreature(38424, -1542.548f, 1290.957f, 6.239825f, 3.490021f, TEMPSUMMON_MANUAL_DESPAWN))
                    {
                        c->GetMotionMaster()->MovePoint(0, -1571.79f, 1318.833f, 35.56271f);
                        canonGUID = c->GetGUID();
                    }
                    if (Creature *c = me->SummonCreature(38424, -1541.036f, 1283.645f, 6.35803f,  3.343305f, TEMPSUMMON_MANUAL_DESPAWN))
                        c->GetMotionMaster()->MovePoint(0, -1571.79f, 1318.833f, 35.56271f);
                    if (Creature *c = me->SummonCreature(38424, -1543.06f,  1287.436f, 7.076612f, 3.446335f, TEMPSUMMON_MANUAL_DESPAWN))
                        c->GetMotionMaster()->MovePoint(0, -1571.79f, 1318.833f, 35.56271f);
                    break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!eventInProgress)
                return;

            if (mui_moveTimer <= diff)
            {
				if (Creature *canon = ObjectAccessor::GetCreature(*me, canonGUID))
                {
					if (Creature *firstCiti = ObjectAccessor::GetCreature(*me, citizenGUID[1]))
                        firstCiti->GetMotionMaster()->MovePoint(1, -1606.97f, 1313.59f, 18.99f);
					if (Creature *firstCiti = ObjectAccessor::GetCreature(*me, citizenGUID[2]))
                        firstCiti->GetMotionMaster()->MovePoint(1, -1610.97f, 1310.59f, 18.11f);
                    me->CastCustomSpell(VEHICLE_SPELL_RIDE_HARDCODED, SPELLVALUE_BASE_POINT0, 1, canon, false);
                    canon->GetMotionMaster()->MovePoint(1, -1609.97f, 1312.59f, 18.11f);
                    if (me->ToTempSummon())
                        if (Unit *general = me->ToTempSummon()->GetSummoner())
                        {
                            me->GetMotionMaster()->MoveFollow(general, urand(0, 5), frand(-3 * M_PI / 8, 3 * M_PI / 8), MOTION_SLOT_ACTIVE);
                            if (general->ToCreature())
                                CAST_AI(npc_escortAI, (general->ToCreature()->AI()))->SetEscortPaused(false);
                        }
                }
                mui_moveTimer = 3600000;
            }
            else  mui_moveTimer -= diff;

            if (mui_attack <= diff)
            {
                if (Creature *c = me->FindNearestCreature(38420, 200))
					if (Creature *canon = ObjectAccessor::GetCreature(*me, canonGUID))
                        canon->CastSpell(c, 72013, true);
                mui_attack = 5000;
            }
            else mui_attack -= diff;
        }

    private:
        bool eventInProgress;
        uint32 mui_moveTimer;
        uint32 mui_attack;
        uint64 canonGUID;
        uint64 citizenGUID[2];
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_lorna_crowley_eventAI(pCreature);
    }
};

// 38221
class npc_gilnean_militia_38221 : public CreatureScript
{
public:
    npc_gilnean_militia_38221() : CreatureScript("npc_gilnean_militia_38221") { }

    enum eNpc
    {
        DATA_GROUP = 101,
        GROUP_1,
    };

    struct npc_gilnean_militia_38221AI : public ScriptedAI
    {
        npc_gilnean_militia_38221AI(Creature* pCreature) : ScriptedAI(pCreature) { }

        void Reset()
        {
            mui_spell1 = urand(1200, 5100);
            mui_spell2 = urand(2100, 5400);
            me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
        }

        void AttackStart(Unit* who)
        {
            if (me->Attack(who, true))
                DoStartNoMovement(who);
        }

        void SetData(uint32 uiType, uint32 uiData)
        {
            if (uiType == DATA_GROUP)
                group = uiData;
        }

        uint32 GetData(uint32 uiType) const
        {
            if (uiType == DATA_GROUP)
                return group;
			return 0;
        }

        void JustReachedHome()
        {
            if (group == GROUP_1)
                if (!UpdateVictim())
                    if (me->ToTempSummon())
                        if (Unit *p = me->ToTempSummon()->GetSummoner())
                        {
                            float distance = urand(7, 15);
                            float angle = frand(-3 * M_PI / 4, 3 * M_PI / 2);
                            float x, y, z;
                            me->GetNearPoint(p, x, y, z, p->GetObjectSize(), distance, angle);
                            me->GetMotionMaster()->MoveFollow(p, distance, angle, MOTION_SLOT_ACTIVE);
                        }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;
            if (mui_spell1 <= diff)
            {
                DoCastVictim(15572);
                mui_spell1 = 10000 + urand(1200, 5100);
            }
            else
                mui_spell1 -= diff;

            if (mui_spell2 <= diff)
            {
                DoCastVictim(47168);
                mui_spell2 = 10000 + urand(2100, 5400);
            }
            else
                mui_spell2 -= diff;

            victim = me->GetVictim();
            if (victim && me->GetDistance2d(victim->GetPositionX(), victim->GetPositionY()) > 7)
                DoSpellAttackIfReady(6660);
            else
                DoMeleeAttackIfReady();
        }

    private :
        uint32 mui_spell1;
        uint32 mui_spell2;
        Unit *victim;
        uint32 group;
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_gilnean_militia_38221AI(pCreature);
    }
};

// 38415
class npc_lord_darius_crowley_38415 : public CreatureScript
{
public:
    npc_lord_darius_crowley_38415() : CreatureScript("npc_lord_darius_crowley_38415") { }

    struct npc_lord_darius_crowley_38415AI : public ScriptedAI
    {
        npc_lord_darius_crowley_38415AI(Creature* pCreature) : ScriptedAI(pCreature) { }

        void Reset()
        {
            float angle = 0;
            for (int i = 0; i < 30; i++)
            {
                if (Creature *summon = me->SummonCreature(38348, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
                {
                    summon->GetMotionMaster()->MovePoint(0, -1710.466f + cos(angle) * 15, 1407.905f + sin(angle) * 15, 21.75196f);
                    if (i >= 0 && i <= 3)
                        worgenGUID[i] = summon->GetGUID();
                }
                angle += M_PI / 15;
            }
            me->GetMotionMaster()->MovePoint(0, -1710.466f, 1407.905f, 21.75196f);
            aboGUID = 0;
            mui_jumpBoss = 3000;
            moveJumpBoss = true;
        }

        void SetGUID(uint64 guid, int32 type = 0)
        {
            aboGUID = guid;
        }

        void EnterCombat(Unit* pWho)
        {
            if (pWho->GetEntry() == 38348)
                me->CastSpell(pWho, 71921, true);
            Talk(0);
        }

        void UpdateAI(uint32 diff)
        {
            if (moveJumpBoss)
            {
                if (mui_jumpBoss <= diff)
                {
					if (Creature *abo = ObjectAccessor::GetCreature(*me, aboGUID))
                        for (int i = 0; i <= 3; i++)
							if (Creature *worgen = ObjectAccessor::GetCreature(*me, worgenGUID[i]))
                                worgen->CastCustomSpell(VEHICLE_SPELL_RIDE_HARDCODED, SPELLVALUE_BASE_POINT0, i + 1, abo, false);
                    moveJumpBoss = false;
                    mui_jumpBoss = 3600000;
                }
                else mui_jumpBoss -= diff;
            }
            if (!UpdateVictim())
                return;
            DoMeleeAttackIfReady();
        }

    private:
        uint64 aboGUID;
        uint32 mui_jumpBoss;
        bool moveJumpBoss;
        uint64 worgenGUID[4];
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_lord_darius_crowley_38415AI(pCreature);
    }
};

// 38348
class npc_worgen_warrior_38348 : public CreatureScript
{
public:
    npc_worgen_warrior_38348() : CreatureScript("npc_worgen_warrior_38348") { }

    struct npc_worgen_warrior_38348AI : public ScriptedAI
    {
        npc_worgen_warrior_38348AI(Creature* pCreature) : ScriptedAI(pCreature) { }

        void EnterCombat(Unit* pWho)
        {
            if (pWho->GetEntry() == 38348)
            {
                me->CastSpell(pWho, 71921, true);
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_worgen_warrior_38348AI(pCreature);
    }
};

/*######
## npc_lady_sylvanas_gilneas
######*/
class npc_lady_sylvanas_gilneas : public CreatureScript
{
public:
    npc_lady_sylvanas_gilneas() : CreatureScript("npc_lady_sylvanas_gilneas") { }

    enum eNpc
    {
        ACTION_START_EVENT = 101,
    };

    struct npc_lady_sylvanas_gilneasAI : public ScriptedAI
    {
        npc_lady_sylvanas_gilneasAI(Creature* pCreature) : ScriptedAI(pCreature) { }

        bool outEvent;
        uint32 phase;
        uint32 phaseTimer;

        Creature* liam;
        Creature* genn;

        void Reset()
        {
            outEvent = false;
            phase = 1;
            phaseTimer = 300;
        }

        void EnterCombat(Unit* pWho)
        {

        }

        void DoAction(int32 type)
        {
            if (type == ACTION_START_EVENT)
                outEvent = true;
        }

        void DamageTaken(Unit* who, uint32 &damage)
        {
            if (me->GetHealthPct() <= 20)
            {
                DoAction(ACTION_START_EVENT);
                damage = 0;
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (outEvent)
            {
                if (phaseTimer <= diff)
                {
                    switch (phase)
                    {
                    case 1:
                        phaseTimer = 1000;
                        DoCastAOE(72113);
                        break;
                    case 2:
                        me->SetReactState(REACT_PASSIVE);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        phaseTimer = 2000;
                        break;
                    case 3:
                        if (genn = me->FindNearestCreature(38470, 100))
                            genn->CastSpell(genn, 86141, true);
                        phaseTimer = 2000;
                        break;
                    case 4:
                        if (liam = me->SummonCreature(38474, -1634.634f, 1631.859f, 21.21159f, 4.694936f, TEMPSUMMON_TIMED_DESPAWN, 60000))
                        {
                            liam->AI()->Talk(0);
                            liam->SetReactState(REACT_PASSIVE);
                        }
                        phaseTimer = 2000;
                        break;
                    case 5:
                        liam->GetMotionMaster()->MovePoint(0, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
                        liam->AI()->Talk(1);
                        phaseTimer = 6000;
                        break;
                    case 7:
                        liam->AI()->Talk(2);
                        me->CastSpell(liam, 72116, true);
                        me->Kill(liam);
                        genn->RemoveAurasDueToSpell(86141);
                        genn->RemoveAurasDueToSpell(72113);
                        genn->CastSpell(genn, 68442, true);
                        phaseTimer = 2000;
                        break;
                    case 8:
                        Talk(0);
                        phaseTimer = 2000;
                        break;
                    case 9:
                        Talk(1);
                        phaseTimer = 3500;
                        break;
                    case 10:
                        Talk(2);
                        phaseTimer = 2500;
                        break;
                    case 11:
                        me->GetMotionMaster()->MovePoint(0, -1634.634f, 1631.859f, 21.21159f);
                        phaseTimer = 2500;
                        break;
                    case 12:
                        genn->DespawnOrUnsummon();
                        std::list<Player *> players = me->FindNearestPlayers(100.0f, true);
                        for (std::list<Player *>::const_iterator it = players.begin(); it != players.end(); it++)
                            (*it)->KilledMonsterCredit(38854, 0);
                        outEvent = false;
                        me->DespawnOrUnsummon();
                        break;
                    }
                    phase++;
                } else phaseTimer -= diff;
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_lady_sylvanas_gilneasAI(pCreature);
    }
};

// 38611
class npc_lorna_crowley_38611 : public CreatureScript
{
public:
    npc_lorna_crowley_38611() : CreatureScript("npc_lorna_crowley_38611") { }

    enum eNpc
    {
        NPC_TOBIAS_MISTMANTLE = 38507,
        MAP_GILNEAS = 654,
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == 24902)
            CAST_AI(npc_lorna_crowley_38611::npc_lorna_crowley_38611AI, creature->AI())->StartEncounter(player);
        return true;
    }

    struct npc_lorna_crowley_38611AI : public ScriptedAI
    {
        npc_lorna_crowley_38611AI(Creature *c) : ScriptedAI(c) {}

        uint64 tobiasGUID;

        void Reset()
        {
            tobiasGUID = 0;
        }

        void StartEncounter(Player* pl)
        {
			if (Creature* tobias = ObjectAccessor::GetCreature(*me, tobiasGUID))
                pl->TeleportTo(MAP_GILNEAS, tobias->GetPositionX(), tobias->GetPositionY(), tobias->GetPositionZ(), 5.42f);
            else
            {
                if (Creature* newTobias = me->SummonCreature(NPC_TOBIAS_MISTMANTLE, -1662.616f, 1591.453f, 23.20896f, 3.740811f, TEMPSUMMON_DEAD_DESPAWN, 180000))
                {
                    newTobias->SetPhaseMask(pl->GetPhaseMask(), true);
                    tobiasGUID = newTobias->GetGUID();
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_lorna_crowley_38611AI(pCreature);
    }
};

// 38615
class npc_captured_riding_bat_38615 : public CreatureScript
{
public:
    npc_captured_riding_bat_38615() : CreatureScript("npc_captured_riding_bat_38615") { }

    struct npc_captured_riding_bat_38615AI : public npc_escortAI
    {
        npc_captured_riding_bat_38615AI(Creature* creature) : npc_escortAI(creature) {}

        void AttackStart(Unit* /*who*/) {}
        void EnterCombat(Unit* /*who*/) {}
        void EnterEvadeMode() {}

        void Reset()
        {
            _checkQuest = 1000;
            _checkDespawn = 1000;
            isBoarded = false;
            isBoarded2 = false;
        }

        void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply)
        {
            if (apply)
            {
                if (who->GetTypeId() == TYPEID_PLAYER)
                    if (who->ToPlayer()->GetQuestStatus(24920) != QUEST_STATUS_INCOMPLETE)
                    {
                        me->GetVehicleKit()->RemoveAllPassengers();
                        return ;
                    }
                me->SetCanFly(true);
                me->SetSpeed(MOVE_FLIGHT, 3.0f);
                isBoarded = true;
                Start(false, true, who->GetGUID(), NULL, false, true);
            }
        }

        void WaypointReached(uint32 i)
        {
            me->SetCanFly(true);
        }

        void JustDied(Unit* /*killer*/)
        {
        }

        void OnCharmed(bool /*apply*/)
        {
        }


        void UpdateAI(uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);
        }

        void UpdateEscortAI(const uint32 diff)
        {
            if (isBoarded)
            {
                if (isBoarded2)
                {
                    if (_checkDespawn <= diff)
                    {
                        me->GetVehicleKit()->RemoveAllPassengers();
                        me->DespawnOrUnsummon();
                        _checkDespawn = 1000;
                    }
                    else
                        _checkDespawn -= diff;
                }
                else
                {
                    if (_checkQuest <= diff)
                    {
                        if (me->GetVehicleKit())
                            if (Unit *u = me->GetVehicleKit()->GetPassenger(0))
                                if (u->GetTypeId() == TYPEID_PLAYER)
                                {
                                    Player *player = u->ToPlayer();
                                    if (player->GetQuestStatus(24920) == QUEST_STATUS_COMPLETE)
                                    {
                                        isBoarded2 = true;
                                        _checkDespawn = 70000;
                                        SetEscortPaused(true);
                                        me->GetMotionMaster()->MovePoint(4242, me->GetHomePosition());
                                    }
                                }
                        _checkQuest = 1000;
                    }
                    else
                        _checkQuest -= diff;
                }
            }
        }

    private :
        uint32 _checkQuest;
        uint32 _checkDespawn;
        bool isBoarded;
        bool isBoarded2;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_captured_riding_bat_38615AI(creature);
    }
};

// 36616
class npc_admiral_nightwind_36616 : public CreatureScript
{
public:
    npc_admiral_nightwind_36616() : CreatureScript("npc_admiral_nightwind_36616") { }

	bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* quest, uint32 /*opt*/)
	{		
        if (quest->GetQuestId() == 14434)
            {
				player->RemoveAllAuras();
				player->TeleportTo(1,8343,801,4,4);
			}
		return true;
	}
};


void AddSC_zone_gilneas2()
{
    new npc_admiral_nightwind_36616();


    //new npc_bloodfang_worgen();

    
    new spell_rescue_drowning_watchman_68735();
    new spell_round_up_horse_68903();
    new npc_trigger_quest_24616();

    new npc_krennan_aranas_38553();
    //new npc_prince_liam_greymane_gilneas();
    new npc_gilnean_militia_38221();
    new npc_lord_darius_crowley_38415();
    new npc_worgen_warrior_38348();
    //new npc_lady_sylvanas_gilneas();
    new npc_lorna_crowley_38611();

    //new npc_lorna_crowley_event();
    new npc_captured_riding_bat_38615();
  
}

