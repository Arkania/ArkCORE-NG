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
SDName: Hellfire_Peninsula
SD%Complete: 100
SDComment: Quest support: 9375, 9410, 9418, 10129, 10146, 10162, 10163, 10340, 10346, 10347, 10382 (Special flight paths) "Needs update"
SDCategory: Hellfire Peninsula
EndScriptData */

/* ContentData
npc_aeranas
npc_ancestral_wolf
npc_wounded_blood_elf
npc_fel_guard_hound
EndContentData */

#include "GameObjectAI.h"
#include "GameObject.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "Player.h"
#include "WorldSession.h"

/*######
## npc_aeranas
######*/

enum Aeranas
{
    SAY_SUMMON                  = 0,
    SAY_FREE                    = 1,
    FACTION_HOSTILE             = 16,
    FACTION_FRIENDLY            = 35,
    SPELL_ENVELOPING_WINDS      = 15535,
    SPELL_SHOCK                 = 12553
};

class npc_aeranas : public CreatureScript
{
public:
    npc_aeranas() : CreatureScript("npc_aeranas") { }

    struct npc_aeranasAI : public ScriptedAI
    {
        npc_aeranasAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            faction_Timer = 8000;
            envelopingWinds_Timer = 9000;
            shock_Timer = 5000;

            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            me->setFaction(FACTION_FRIENDLY);

            Talk(SAY_SUMMON);
        }

        void UpdateAI(uint32 diff) override
        {
            if (faction_Timer)
            {
                if (faction_Timer <= diff)
                {
                    me->setFaction(FACTION_HOSTILE);
                    faction_Timer = 0;
                } else faction_Timer -= diff;
            }

            if (!UpdateVictim())
                return;

            if (HealthBelowPct(30))
            {
                me->setFaction(FACTION_FRIENDLY);
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                me->RemoveAllAuras();
                me->DeleteThreatList();
                me->CombatStop(true);
                Talk(SAY_FREE);
                return;
            }

            if (shock_Timer <= diff)
            {
                DoCastVictim(SPELL_SHOCK);
                shock_Timer = 10000;
            } else shock_Timer -= diff;

            if (envelopingWinds_Timer <= diff)
            {
                DoCastVictim(SPELL_ENVELOPING_WINDS);
                envelopingWinds_Timer = 25000;
            } else envelopingWinds_Timer -= diff;

            DoMeleeAttackIfReady();
        }

    private:
        uint32 faction_Timer;
        uint32 envelopingWinds_Timer;
        uint32 shock_Timer;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_aeranasAI(creature);
    }
};

/*######
## npc_ancestral_wolf
######*/

enum AncestralWolf
{
    EMOTE_WOLF_LIFT_HEAD        = 0,
    EMOTE_WOLF_HOWL             = 1,
    SAY_WOLF_WELCOME            = 2,
    SPELL_ANCESTRAL_WOLF_BUFF   = 29981,
    NPC_RYGA                    = 17123
};

class npc_ancestral_wolf : public CreatureScript
{
public:
    npc_ancestral_wolf() : CreatureScript("npc_ancestral_wolf") { }

    struct npc_ancestral_wolfAI : public npc_escortAI
    {
        npc_ancestral_wolfAI(Creature* creature) : npc_escortAI(creature)
        {
            if (creature->GetOwner() && creature->GetOwner()->GetTypeId() == TYPEID_PLAYER)
                Start(false, false, creature->GetOwner()->GetGUID());
            else
                TC_LOG_ERROR("scripts", "TRINITY: npc_ancestral_wolf can not obtain owner or owner is not a player.");

            creature->SetSpeed(MOVE_WALK, 1.5f);
            Reset();
        }

        void Reset() override
        {
            ryga = nullptr;
            DoCast(me, SPELL_ANCESTRAL_WOLF_BUFF, true);
        }

        void MoveInLineOfSight(Unit* who) override

        {
            if (!ryga && who->GetEntry() == NPC_RYGA && me->IsWithinDistInMap(who, 15.0f))
                if (Creature* temp = who->ToCreature())
                    ryga = temp;

            npc_escortAI::MoveInLineOfSight(who);
        }

        void WaypointReached(uint32 waypointId) override
        {
            switch (waypointId)
            {
                case 0:
                    Talk(EMOTE_WOLF_LIFT_HEAD);
                    break;
                case 2:
                    Talk(EMOTE_WOLF_HOWL);
                    break;
                case 50:
                    if (ryga && ryga->IsAlive() && !ryga->IsInCombat())
                        ryga->AI()->Talk(SAY_WOLF_WELCOME);
                    break;
            }
        }

    private:
        Creature* ryga;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_ancestral_wolfAI(creature);
    }
};

/*######
## npc_wounded_blood_elf
######*/

enum WoundedBloodElf
{
    SAY_ELF_START               = 0,
    SAY_ELF_SUMMON1             = 1,
    SAY_ELF_RESTING             = 2,
    SAY_ELF_SUMMON2             = 3,
    SAY_ELF_COMPLETE            = 4,
    SAY_ELF_AGGRO               = 5,
    QUEST_ROAD_TO_FALCON_WATCH  = 9375,
    NPC_HAALESHI_WINDWALKER     = 16966,
    NPC_HAALESHI_TALONGUARD     = 16967,
    FACTION_FALCON_WATCH_QUEST  = 775
};

class npc_wounded_blood_elf : public CreatureScript
{
public:
    npc_wounded_blood_elf() : CreatureScript("npc_wounded_blood_elf") { }

    struct npc_wounded_blood_elfAI : public npc_escortAI
    {
        npc_wounded_blood_elfAI(Creature* creature) : npc_escortAI(creature) { }

        void Reset() override { }

        void EnterCombat(Unit* /*who*/) override
        {
            if (HasEscortState(STATE_ESCORT_ESCORTING))
                Talk(SAY_ELF_AGGRO);
        }

        void JustSummoned(Creature* summoned) override
        {
            summoned->AI()->AttackStart(me);
        }

        bool sQuestAccept(Player* player, Quest const* quest)
        {
            if (quest->GetQuestId() == QUEST_ROAD_TO_FALCON_WATCH)
            {
                me->setFaction(FACTION_FALCON_WATCH_QUEST);
                npc_escortAI::Start(true, false, player->GetGUID());
            }
            return false;
        }

        void WaypointReached(uint32 waypointId) override
        {
            Player* player = GetPlayerForEscort();
            if (!player)
                return;

            switch (waypointId)
            {
                case 0:
                    Talk(SAY_ELF_START, player);
                    break;
                case 9:
                    Talk(SAY_ELF_SUMMON1, player);
                    // Spawn two Haal'eshi Talonguard
                    DoSpawnCreature(NPC_HAALESHI_TALONGUARD, -15, -15, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                    DoSpawnCreature(NPC_HAALESHI_TALONGUARD, -17, -17, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                    break;
                case 13:
                    Talk(SAY_ELF_RESTING, player);
                    break;
                case 14:
                    Talk(SAY_ELF_SUMMON2, player);
                    // Spawn two Haal'eshi Windwalker
                    DoSpawnCreature(NPC_HAALESHI_WINDWALKER, -15, -15, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                    DoSpawnCreature(NPC_HAALESHI_WINDWALKER, -17, -17, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                    break;
                case 27:
                    Talk(SAY_ELF_COMPLETE, player);
                    // Award quest credit
                    player->GroupEventHappens(QUEST_ROAD_TO_FALCON_WATCH, me);
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_wounded_blood_elfAI(creature);
    }
};

/*######
## npc_fel_guard_hound
######*/

enum FelGuard
{
    SPELL_SUMMON_POO            = 37688,
    NPC_DERANGED_HELBOAR        = 16863
};

class npc_fel_guard_hound : public CreatureScript
{
public:
    npc_fel_guard_hound() : CreatureScript("npc_fel_guard_hound") { }

    struct npc_fel_guard_houndAI : public ScriptedAI
    {
        npc_fel_guard_houndAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            checkTimer = 5000; //check for creature every 5 sec
            helboarGUID = 0;
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type != POINT_MOTION_TYPE || id != 1)
                return;

            if (Creature* helboar = ObjectAccessor::GetCreature(*me, helboarGUID))
            {
                helboar->RemoveCorpse();
                DoCast(SPELL_SUMMON_POO);

                if (Player* owner = me->GetCharmerOrOwnerPlayerOrPlayerItself())
                    me->GetMotionMaster()->MoveFollow(owner, 0.0f, 0.0f);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (checkTimer <= diff)
            {
                if (Creature* helboar = me->FindNearestCreature(NPC_DERANGED_HELBOAR, 10.0f, false))
                {
                    if (helboar->GetGUID() != helboarGUID && me->GetMotionMaster()->GetCurrentMovementGeneratorType() != POINT_MOTION_TYPE && !me->FindCurrentSpellBySpellId(SPELL_SUMMON_POO))
                    {
                        helboarGUID = helboar->GetGUID();
                        me->GetMotionMaster()->MovePoint(1, helboar->GetPositionX(), helboar->GetPositionY(), helboar->GetPositionZ());
                    }
                }
                checkTimer = 5000;
            }
            else checkTimer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

    private:
        uint32 checkTimer;
        uint64 helboarGUID;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_fel_guard_houndAI(creature);
    }
};

// 18930 horde
class npc_vlagga_freyfeather_18930 : public CreatureScript
{
public:
    npc_vlagga_freyfeather_18930() : CreatureScript("npc_vlagga_freyfeather_18930") { }

    enum eNPC
    {
        QUEST_JOURNEY_TO_THRALLMAR = 10289,
        TAXINODE_VALIANCE = 565,
        NPC_ENRAGED_GRYPHON = 9297,
        GOSSIP_MENU = 7938,
        NPC_TEXT = 10053,
        GMO_NORMAL = 0,
        GMO_QUEST = 1,
        SPELL_TAXI_FLIGHT = 34924,
    };

    bool OnGossipHello(Player* player, Creature* creature) 
    { 
        player->PrepareQuestMenu(creature->GetGUID());
        if (player->getLevel() >= 58)
        {
            player->ADD_GOSSIP_ITEM_DB(GOSSIP_MENU, GMO_NORMAL, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TAXI);

            if (player->GetQuestStatus(QUEST_JOURNEY_TO_THRALLMAR) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_JOURNEY_TO_THRALLMAR) == QUEST_STATUS_COMPLETE)
                player->ADD_GOSSIP_ITEM_DB(GOSSIP_MENU, GMO_QUEST, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
            
            player->SEND_GOSSIP_MENU(NPC_TEXT, creature->GetGUID());            
        }
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) 
    { 
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
        case GOSSIP_ACTION_TAXI:
            player->GetSession()->SendTaxiMenu(creature);
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:
            player->CLOSE_GOSSIP_MENU();
            player->CastSpell(player, SPELL_TAXI_FLIGHT);
           break;
        }
        return true; 
    }

    struct npc_vlagga_freyfeather_18930AI : public ScriptedAI
    {
        npc_vlagga_freyfeather_18930AI(Creature* creature) : ScriptedAI(creature) { }

        void EnterCombat(Unit* victim) override
        {
            Talk(0);
            Position pos = victim->GetNearPosition(frand(4.0f, 5.0f), frand(0.0f, 6.28f));
            me->SummonCreature(NPC_ENRAGED_GRYPHON, pos, TEMPSUMMON_TIMED_DESPAWN, 60000);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            Position pos = attacker->GetNearPosition(frand(4.0f, 5.0f), frand(0.0f, 6.28f));
            me->SummonCreature(NPC_ENRAGED_GRYPHON, pos, TEMPSUMMON_TIMED_DESPAWN, 60000);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_vlagga_freyfeather_18930AI(creature);
    }
};

// 18931 alliance
class npc_amish_wildhammer_18931 : public CreatureScript
{
public:
    npc_amish_wildhammer_18931() : CreatureScript("npc_amish_wildhammer_18931") { }

    enum eNPC
    {
        QUEST_JOURNEY_TO_HONOR_HOLD = 10140,
        TAXINODE_DARK_PORTAL = 613,
        NPC_ENRAGED_GRYPHON = 9526,
        GOSSIP_MENU = 7939,
        NPC_TEXT_1 = 9991, 
        NPC_TEXT_2 = 10052, 
        GMO_NORMAL = 0,
        GMO_QUEST = 1,
        SPELL_TAXI_FLIGHT = 34907,
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->PrepareQuestMenu(creature->GetGUID());
        if (player->getLevel() >= 58)
        {
            player->ADD_GOSSIP_ITEM_DB(GOSSIP_MENU, GMO_NORMAL, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TAXI);

            if (player->GetQuestStatus(QUEST_JOURNEY_TO_HONOR_HOLD) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_JOURNEY_TO_HONOR_HOLD) == QUEST_STATUS_COMPLETE)
            {
                player->ADD_GOSSIP_ITEM_DB(GOSSIP_MENU, GMO_QUEST, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
                player->SEND_GOSSIP_MENU(NPC_TEXT_1, creature->GetGUID());
                return true;
            }

            player->SEND_GOSSIP_MENU(NPC_TEXT_2, creature->GetGUID());
        }
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
        case GOSSIP_ACTION_TAXI:
            player->GetSession()->SendTaxiMenu(creature);
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:
            player->CLOSE_GOSSIP_MENU();
            player->CastSpell(player, SPELL_TAXI_FLIGHT);
            break;
        }
        return true;
    }

    struct npc_amish_wildhammer_18931AI : public ScriptedAI
    {
        npc_amish_wildhammer_18931AI(Creature* creature) : ScriptedAI(creature) { }

        void EnterCombat(Unit* victim) override
        {
            Talk(1);
            Position pos = victim->GetNearPosition(frand(4.0f, 5.0f), frand(0.0f, 6.28f));
            me->SummonCreature(NPC_ENRAGED_GRYPHON, pos, TEMPSUMMON_TIMED_DESPAWN, 60000);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            Position pos = attacker->GetNearPosition(frand(4.0f, 5.0f), frand(0.0f, 6.28f));
            me->SummonCreature(NPC_ENRAGED_GRYPHON, pos, TEMPSUMMON_TIMED_DESPAWN, 60000);
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_amish_wildhammer_18931AI(creature);
    }
};

// 16896 
class npc_honor_hold_archer_16896 : public CreatureScript
{
public:
    npc_honor_hold_archer_16896() : CreatureScript("npc_honor_hold_archer_16896") { }

    enum eNPC
    {
        NPC_ARCHER = 16896,
        NPC_TARGET_MIDDLE = 16897,
        NPC_TARGET_RIGHT = 16898,
        NPC_TARGET_LEFT = 16899,
        SPELL_SHOOT_MIDDLE = 29121, // shoot is invisible
        SPELL_SHOOT_RIGHT = 29122,
        SPELL_SHOOT_LEFT = 29120,
        EVENT_START_SHOOT = 100,
        EVENT_SHOOT = 101,
    };

    struct npc_honor_hold_archer_16896AI : public ScriptedAI
    {
        npc_honor_hold_archer_16896AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_targetGUID;
        uint32   m_shoot;

        void Initialize()
        {
            m_events.ScheduleEvent(EVENT_START_SHOOT, 5000);
            m_targetGUID = 0;
            m_shoot = 0;
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_SHOOT:
                {
                    float dist = 20.0f;
                    Creature* target;
                    if (Creature* npc = me->FindNearestCreature(NPC_TARGET_MIDDLE, dist))
                        if (npc->GetDistance2d(me) < dist)
                        {
                            dist = npc->GetDistance2d(me);
                            target = npc;
                            m_shoot = RAND(SPELL_SHOOT_LEFT, SPELL_SHOOT_RIGHT);
                        }
                    if (Creature* npc = me->FindNearestCreature(NPC_TARGET_RIGHT, dist))
                        if (npc->GetDistance2d(me) < dist)
                        {
                            dist = npc->GetDistance2d(me);
                            target = npc;
                            m_shoot = SPELL_SHOOT_RIGHT;
                        }
                    if (Creature* npc = me->FindNearestCreature(NPC_TARGET_LEFT, dist))
                        if (npc->GetDistance2d(me) < dist)
                        {
                            dist = npc->GetDistance2d(me);
                            target = npc;
                            m_shoot = SPELL_SHOOT_LEFT;
                        }
                    if (dist < 19.0f && target)
                    {
                        m_targetGUID = target->GetGUID();
                        m_events.ScheduleEvent(EVENT_SHOOT, 5000);
                    }
                    break;
                }
                case EVENT_SHOOT:
                {
                    if (Creature* npc = sObjectAccessor->GetCreature(*me, m_targetGUID))
                        me->CastSpell(npc, m_shoot, true);
                    m_events.ScheduleEvent(EVENT_SHOOT, urand(5000, 10000));
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
        return new npc_honor_hold_archer_16896AI(creature);
    }
};

void AddSC_hellfire_peninsula()
{
    new npc_aeranas();
    new npc_ancestral_wolf();
    new npc_wounded_blood_elf();
    new npc_fel_guard_hound();
    new npc_vlagga_freyfeather_18930();
    new npc_amish_wildhammer_18931();
    new npc_honor_hold_archer_16896();
}
