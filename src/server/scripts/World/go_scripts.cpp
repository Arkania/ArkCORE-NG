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

/* ContentData
go_cat_figurine (the "trap" version of GO, two different exist)
go_barov_journal
go_ethereum_prison
go_ethereum_stasis
go_sacred_fire_of_life
go_shrine_of_the_birds
go_southfury_moonstone
go_field_repair_bot_74A
go_orb_of_command
go_resonite_cask
go_tablet_of_madness
go_tablet_of_the_seven
go_tele_to_dalaran_crystal
go_tele_to_violet_stand
go_scourge_cage
go_jotunheim_cage
go_table_theka
go_soulwell
go_bashir_crystalforge
go_ethereal_teleport_pad
go_soulwell
go_dragonflayer_cage
go_tadpole_cage
go_amberpine_outhouse
go_hive_pod
go_gjalerbron_cage
go_large_gjalerbron_cage
go_veil_skith_cage
EndContentData */

#include "script_helper.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "GameObject.h"
#include "GameObjectAI.h"
#include "Spell.h"
#include "Player.h"
#include "Transport.h"
#include "WorldSession.h"

enum eNpcGoScripts
{
    ACTION_CREATE_NAZGRIM = 1000,
    ACTION_CREATE_VANGUARD = 1001,

    GO_SHRINE_HAWK = 185551,
    GO_SHRINE_EAGLE = 185547,
    GO_SHRINE_FALCON = 185553,

    GOSSIP_OUTHOUSE_INUSE = 12775,
    GOSSIP_OUTHOUSE_VACANT = 12779,
    GOSSIP_TABLE_THEKA = 1653,

    ITEM_ANDERHOLS_SLIDER_CIDER = 37247,
    ITEM_BLUE_PUNCH_CARD = 9282,
    ITEM_CUERGOS_KEY = 9275,
    ITEM_PRISMATIC_PUNCH_CARD = 9316,
    ITEM_RED_PUNCH_CARD = 9281,
    ITEM_TELEPORTER_POWER_PACK = 28969,
    ITEM_WHITE_PUNCH_CARD = 9279,
    ITEM_YELLOW_PUNCH_CARD = 9280,

    MATRIX_PUNCHOGRAPH_3005_A = 142345,
    MATRIX_PUNCHOGRAPH_3005_B = 142475,
    MATRIX_PUNCHOGRAPH_3005_C = 142476,
    MATRIX_PUNCHOGRAPH_3005_D = 142696,

    NPC_ARIKARA = 10882,
    NPC_CAPTIVE_CHILD = 22314,
    NPC_EAGLE_GUARD = 22993,
    NPC_EBON_BLADE_PRISONER_HUMAN = 30186,
    NPC_EBON_BLADE_PRISONER_NE = 30194,
    NPC_EBON_BLADE_PRISONER_TROLL = 30196,
    NPC_EBON_BLADE_PRISONER_ORC = 30195,
    NPC_FALCON_GUARD = 22994,
    NPC_GJALERBRON_PRISONER = 24035,
    NPC_GOGGEROC = 11920,
    NPC_HAWK_GUARD = 22992,
    NPC_HELLSCREAMS_VANGUARD = 43090,
    NPC_HIVE_AMBUSHER = 13301,
    NPC_IMAGE_WIND_TRADER = 20518,
    NPC_LEGIONNAIRE_NAZGRIM = 43100,
    NPC_OUTHOUSE_BUNNY = 27326,
    NPC_PRISONER_PRIEST = 24086,
    NPC_PRISONER_MAGE = 24088,
    NPC_PRISONER_WARRIOR = 24089,
    NPC_PRISONER_PALADIN = 24090,
    NPC_RIZZLE = 23002,
    NPC_SCOURGE_PRISONER = 25610,
    NPC_STILLBLADE = 17716,
    NPC_WINTERFIN_TADPOLE = 25201,
    NPC_ZELEMAR = 17830,

    QUEST_ALLIANCE_OF_KEYS_AND_CAGES = 11231,
    QUEST_DOING_YOUR_DUTY = 12227,
    QUEST_HORDE_OF_KEYS_AND_CAGES = 11265,
    QUEST_LEARN_LEAVE_RETURN = 12790,
    QUEST_OH_NOES_THE_TADPOLES = 11560,
    QUEST_HIVE_IN_THE_TOWER = 9544,
    QUEST_MISSING_FRIENDS = 10852,
    QUEST_PRISON_BREAK = 11587,
    QUEST_PRISONERS_OF_WYRMSKULL = 11255,
    QUEST_SPIDER_GOLD = 2936,
    QUEST_TELE_CRYSTAL_FLAG = 12845,
    QUEST_THE_CLEANSING_HORDE = 11317,
    QUEST_THE_CLEANSING_ALLIANCE = 11322,

    SPELL_ARCANE_PRISONER_KILL_CREDIT = 45456,
    SPELL_BLACKJACK = 39865, //stuns player
    SPELL_BLUE_PUNCH_CARD = 11525,
    SPELL_CLEANSING_SOUL = 43351,
    SPELL_CREATE_1_FLASK_OF_BEAST = 40964,
    SPELL_CREATE_5_FLASK_OF_BEAST = 40965,
    SPELL_CREATE_1_FLASK_OF_SORCERER = 40968,
    SPELL_CREATE_5_FLASK_OF_SORCERER = 40970,
    SPELL_CREATE_AMBERSEEDS = 48330, SPELL_PRISMATIC_PUNCH_CARD = 11545,
    SPELL_INDISPOSED = 53017,
    SPELL_INDISPOSED_III = 48341,
    SPELL_RECENT_MEDITATION = 61720,
    SPELL_RED_PUNCH_CARD = 11528,
    SPELL_REP_LC = 39456,
    SPELL_REP_SHAT = 39457,
    SPELL_REP_CE = 39460,
    SPELL_REP_CON = 39474,
    SPELL_REP_KT = 39475,
    SPELL_REP_SPOR = 39476,
    SPELL_STAMP_OUT_BONFIRE_QUEST_COMPLETE = 45458,
    SPELL_SUMMON_BLADE_KNIGHT_H = 56207,
    SPELL_SUMMON_BLADE_KNIGHT_NE = 56209,
    SPELL_SUMMON_BLADE_KNIGHT_ORC = 56212,
    SPELL_SUMMON_BLADE_KNIGHT_TROLL = 56214,
    SPELL_SUMMON_GHOST_SABER = 5968,
    SPELL_SUMMON_PIRATES_TREASURE_AND_TRIGGER_MOB = 11462,
    SPELL_SUMMON_RIZZLE = 39866,
    SPELL_YELLOW_PUNCH_CARD = 11512,
};

const uint32 NpcPrisonEntry[] =
{
    22810, 22811, 22812, 22813, 22814, 22815,               //good guys
    20783, 20784, 20785, 20786, 20788, 20789, 20790         //bad guys
};

const uint32 NpcStasisEntry[] =
{
    22825, 20888, 22827, 22826, 22828
};

enum eNpcVanGuard
{
    eVanGuardAA = 117110,
    eVanGuardAB = 118845,
    eVanGuardBA = 117099,
    eVanGuardBB = 117100,
    eVanGuardBC = 117096,
    eVanGuardCA = 118846,
    eVanGuardCB = 117112,
    eVanGuardDA = 118847,
    eVanGuardNaz = 117111,
};

#define GO_TELE_TO_DALARAN_CRYSTAL_FAILED   "This teleport crystal cannot be used until the teleport crystal in Dalaran has been used at least once."
#define GO_ANDERHOLS_SLIDER_CIDER_NOT_FOUND "Quest item Anderhol's Slider Cider not found."

// 13873
class go_cat_figurine : public GameObjectScript
{
public:
    go_cat_figurine() : GameObjectScript("go_cat_figurine") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/) override
    {
        player->CastSpell(player, SPELL_SUMMON_GHOST_SABER, true);
        return false;
    }
};

// 180794
class go_barov_journal : public GameObjectScript
{
public:
    go_barov_journal() : GameObjectScript("go_barov_journal") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/) override
    {
        if (player->HasSkill(SKILL_TAILORING) && player->GetBaseSkillValue(SKILL_TAILORING) >= 280 && !player->HasSpell(26086))
            player->CastSpell(player, 26095, false);

        return true;
    }
};

// 179552
class go_field_repair_bot_74A : public GameObjectScript
{
public:
    go_field_repair_bot_74A() : GameObjectScript("go_field_repair_bot_74A") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/) override
    {
        if (player->HasSkill(SKILL_ENGINEERING) && player->GetBaseSkillValue(SKILL_ENGINEERING) >= 300 && !player->HasSpell(22704))
            player->CastSpell(player, 22864, false);

        return true;
    }
};

// 181956
class go_gilded_brazier : public GameObjectScript
{
public:
    go_gilded_brazier() : GameObjectScript("go_gilded_brazier") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (go->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
        {
            if (player->GetQuestStatus(9678) == QUEST_STATUS_INCOMPLETE)
            {
                if (Creature* Stillblade = player->SummonCreature(NPC_STILLBLADE, 8106.11f, -7542.06f, 151.775f, 3.02598f, TEMPSUMMON_DEAD_DESPAWN, 60000))
                    Stillblade->AI()->AttackStart(player);
            }
        }
        return true;
    }
};

// 179879
class go_orb_of_command : public GameObjectScript
{
public:
    go_orb_of_command() : GameObjectScript("go_orb_of_command") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/) override
    {
        if (player->GetQuestRewardStatus(7761))
            player->CastSpell(player, 23460, true);

        return true;
    }
};

// 180368
class go_tablet_of_madness : public GameObjectScript
{
public:
    go_tablet_of_madness() : GameObjectScript("go_tablet_of_madness") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/) override
    {
        if (player->HasSkill(SKILL_ALCHEMY) && player->GetSkillValue(SKILL_ALCHEMY) >= 300 && !player->HasSpell(24266))
            player->CastSpell(player, 24267, false);

        return true;
    }
};

// 169294
class go_tablet_of_the_seven : public GameObjectScript
{
public:
    go_tablet_of_the_seven() : GameObjectScript("go_tablet_of_the_seven") { }

    /// @todo use gossip option ("Transcript the Tablet") instead, if Trinity adds support.
    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (go->GetGoType() != GAMEOBJECT_TYPE_QUESTGIVER)
            return true;

        if (player->GetQuestStatus(4296) == QUEST_STATUS_INCOMPLETE)
            player->CastSpell(player, 15065, false);

        return true;
    }
};

// 183146
class go_jump_a_tron : public GameObjectScript
{
public:
    go_jump_a_tron() : GameObjectScript("go_jump_a_tron") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/) override
    {
        if (player->GetQuestStatus(10111) == QUEST_STATUS_INCOMPLETE)
            player->CastSpell(player, 33382, true);

        return true;
    }
};

// 184418 184419 184420 184421 184422 184423 184424 184425 184426 184427 184428 184429 184430 184431
class go_ethereum_prison : public GameObjectScript
{
public:
    go_ethereum_prison() : GameObjectScript("go_ethereum_prison") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        go->UseDoorOrButton();
        int Random = rand() % (sizeof(NpcPrisonEntry) / sizeof(uint32));

        if (Creature* creature = player->SummonCreature(NpcPrisonEntry[Random], go->GetPositionX(), go->GetPositionY(), go->GetPositionZ(), go->GetAngle(player),
            TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000))
        {
            if (!creature->IsHostileTo(player))
            {
                if (FactionTemplateEntry const* pFaction = creature->GetFactionTemplateEntry())
                {
                    uint32 Spell = 0;

                    switch (pFaction->faction)
                    {
                        case 1011: Spell = SPELL_REP_LC; break;
                        case 935: Spell = SPELL_REP_SHAT; break;
                        case 942: Spell = SPELL_REP_CE; break;
                        case 933: Spell = SPELL_REP_CON; break;
                        case 989: Spell = SPELL_REP_KT; break;
                        case 970: Spell = SPELL_REP_SPOR; break;
                    }

                    if (Spell)
                        creature->CastSpell(player, Spell, false);
                    else
                        TC_LOG_ERROR("scripts", "go_ethereum_prison summoned Creature (entry %u) but faction (%u) are not expected by script.", creature->GetEntry(), creature->getFaction());
                }
            }
        }

        return false;
    }
};

// 185465 185466 185467 184595 185461 185462 185463 185464 185464 185464 185464 185464 185464 185464
class go_ethereum_stasis : public GameObjectScript
{
public:
    go_ethereum_stasis() : GameObjectScript("go_ethereum_stasis") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        go->UseDoorOrButton();
        int Random = rand() % (sizeof(NpcStasisEntry) / sizeof(uint32));

        player->SummonCreature(NpcStasisEntry[Random], go->GetPositionX(), go->GetPositionY(), go->GetPositionZ(), go->GetAngle(player),
            TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);

        return false;
    }
};

// 178145
class go_resonite_cask : public GameObjectScript
{
public:
    go_resonite_cask() : GameObjectScript("go_resonite_cask") { }

    bool OnGossipHello(Player* /*player*/, GameObject* go) override
    {
        if (go->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
            go->SummonCreature(NPC_GOGGEROC, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000);

        return false;
    }
};

// 175944
class go_sacred_fire_of_life : public GameObjectScript
{
public:
    go_sacred_fire_of_life() : GameObjectScript("go_sacred_fire_of_life") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (go->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
            player->SummonCreature(NPC_ARIKARA, -5008.338f, -2118.894f, 83.657f, 0.874f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);

        return true;
    }
};

// 185547 185553 185551
class go_shrine_of_the_birds : public GameObjectScript
{
public:
    go_shrine_of_the_birds() : GameObjectScript("go_shrine_of_the_birds") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        uint32 BirdEntry = 0;

        float fX, fY, fZ;
        go->GetClosePoint(fX, fY, fZ, go->GetObjectSize(), INTERACTION_DISTANCE);

        switch (go->GetEntry())
        {
            case GO_SHRINE_HAWK:
                BirdEntry = NPC_HAWK_GUARD;
                break;
            case GO_SHRINE_EAGLE:
                BirdEntry = NPC_EAGLE_GUARD;
                break;
            case GO_SHRINE_FALCON:
                BirdEntry = NPC_FALCON_GUARD;
                break;
        }

        if (BirdEntry)
            player->SummonCreature(BirdEntry, fX, fY, fZ, go->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);

        return false;
    }
};

// 185566
class go_southfury_moonstone : public GameObjectScript
{
public:
    go_southfury_moonstone() : GameObjectScript("go_southfury_moonstone") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/) override
    {
        //implicitTarget=48 not implemented as of writing this code, and manual summon may be just ok for our purpose
        //player->CastSpell(player, SPELL_SUMMON_RIZZLE, false);

        if (Creature* creature = player->SummonCreature(NPC_RIZZLE, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0))
            creature->CastSpell(player, SPELL_BLACKJACK, false);

        return false;
    }
};

// 191230
class go_tele_to_dalaran_crystal : public GameObjectScript
{
public:
    go_tele_to_dalaran_crystal() : GameObjectScript("go_tele_to_dalaran_crystal") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/) override
    {
        if (player->GetQuestRewardStatus(QUEST_TELE_CRYSTAL_FLAG))
            return false;

        player->GetSession()->SendNotification(GO_TELE_TO_DALARAN_CRYSTAL_FAILED);

        return true;
    }
};

// 191229
class go_tele_to_violet_stand : public GameObjectScript
{
public:
    go_tele_to_violet_stand() : GameObjectScript("go_tele_to_violet_stand") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/) override
    {
        if (player->GetQuestRewardStatus(QUEST_LEARN_LEAVE_RETURN) || player->GetQuestStatus(QUEST_LEARN_LEAVE_RETURN) == QUEST_STATUS_INCOMPLETE)
            return false;

        return true;
    }
};

// 185919
class go_fel_crystalforge : public GameObjectScript
{
public:
    go_fel_crystalforge() : GameObjectScript("go_fel_crystalforge") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (go->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER) /* != GAMEOBJECT_TYPE_QUESTGIVER) */
            player->PrepareQuestMenu(go->GetGUID()); /* return true*/

        player->ADD_GOSSIP_ITEM_DB(8672, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        player->ADD_GOSSIP_ITEM_DB(8672, 1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        player->SEND_GOSSIP_MENU(31000, go->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, GameObject* go, uint32 /*sender*/, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF:
                player->CastSpell(player, SPELL_CREATE_1_FLASK_OF_BEAST, false);
                player->ADD_GOSSIP_ITEM_DB(8673, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->SEND_GOSSIP_MENU(31001, go->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->CastSpell(player, SPELL_CREATE_5_FLASK_OF_BEAST, false);
                player->ADD_GOSSIP_ITEM_DB(8673, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->SEND_GOSSIP_MENU(31001, go->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                player->ADD_GOSSIP_ITEM_DB(8672, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM_DB(8672, 1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(31000, go->GetGUID());
                break;
        }
        return true;
    }
};

// 185921
class go_bashir_crystalforge : public GameObjectScript
{
public:
    go_bashir_crystalforge() : GameObjectScript("go_bashir_crystalforge") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (go->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER) /* != GAMEOBJECT_TYPE_QUESTGIVER) */
            player->PrepareQuestMenu(go->GetGUID()); /* return true*/

        player->ADD_GOSSIP_ITEM_DB(8677, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        player->ADD_GOSSIP_ITEM_DB(8677, 1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        player->SEND_GOSSIP_MENU(31100, go->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, GameObject* go, uint32 /*sender*/, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF:
                player->CastSpell(player, SPELL_CREATE_1_FLASK_OF_SORCERER, false);
                player->ADD_GOSSIP_ITEM_DB(8676, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->SEND_GOSSIP_MENU(31101, go->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->CastSpell(player, SPELL_CREATE_5_FLASK_OF_SORCERER, false);
                player->ADD_GOSSIP_ITEM_DB(8676, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->SEND_GOSSIP_MENU(31101, go->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                player->ADD_GOSSIP_ITEM_DB(8677, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                player->ADD_GOSSIP_ITEM_DB(8677, 1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(31100, go->GetGUID());
                break;
        }
        return true;
    }
};

// 142345 142475 142476 142696 
class go_matrix_punchograph : public GameObjectScript
{
public:
    go_matrix_punchograph() : GameObjectScript("go_matrix_punchograph") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        switch (go->GetEntry())
        {
            case MATRIX_PUNCHOGRAPH_3005_A:
                if (player->HasItemCount(ITEM_WHITE_PUNCH_CARD))
                {
                    player->DestroyItemCount(ITEM_WHITE_PUNCH_CARD, 1, true);
                    player->CastSpell(player, SPELL_YELLOW_PUNCH_CARD, true);
                }
                break;
            case MATRIX_PUNCHOGRAPH_3005_B:
                if (player->HasItemCount(ITEM_YELLOW_PUNCH_CARD))
                {
                    player->DestroyItemCount(ITEM_YELLOW_PUNCH_CARD, 1, true);
                    player->CastSpell(player, SPELL_BLUE_PUNCH_CARD, true);
                }
                break;
            case MATRIX_PUNCHOGRAPH_3005_C:
                if (player->HasItemCount(ITEM_BLUE_PUNCH_CARD))
                {
                    player->DestroyItemCount(ITEM_BLUE_PUNCH_CARD, 1, true);
                    player->CastSpell(player, SPELL_RED_PUNCH_CARD, true);
                }
                break;
            case MATRIX_PUNCHOGRAPH_3005_D:
                if (player->HasItemCount(ITEM_RED_PUNCH_CARD))
                {
                    player->DestroyItemCount(ITEM_RED_PUNCH_CARD, 1, true);
                    player->CastSpell(player, SPELL_PRISMATIC_PUNCH_CARD, true);
                }
                break;
            default:
                break;
        }
        return false;
    }
};

// 187854 187855 187856 187857 187858 187859 187860 187862 187863 187864 
// 187865 187866 187867 187868 187870 187871 187872 187873 187874 187861 190803
class go_scourge_cage : public GameObjectScript
{
public:
    go_scourge_cage() : GameObjectScript("go_scourge_cage") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        go->UseDoorOrButton();
        if (Creature* pNearestPrisoner = go->FindNearestCreature(NPC_SCOURGE_PRISONER, 5.0f, true))
        {
            player->KilledMonsterCredit(NPC_SCOURGE_PRISONER, pNearestPrisoner->GetGUID());
            pNearestPrisoner->DisappearAndDie();
        }

        return true;
    }
};

// 187561
class go_arcane_prison : public GameObjectScript
{
public:
    go_arcane_prison() : GameObjectScript("go_arcane_prison") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (player->GetQuestStatus(QUEST_PRISON_BREAK) == QUEST_STATUS_INCOMPLETE)
        {
            go->SummonCreature(25318, 3485.089844f, 6115.7422188f, 70.966812f, 0, TEMPSUMMON_TIMED_DESPAWN, 60000);
            player->CastSpell(player, SPELL_ARCANE_PRISONER_KILL_CREDIT, true);
            return true;
        }
        return false;
    }
};

// 182024
class go_blood_filled_orb : public GameObjectScript
{
public:
    go_blood_filled_orb() : GameObjectScript("go_blood_filled_orb") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (go->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
            player->SummonCreature(NPC_ZELEMAR, -369.746f, 166.759f, -21.50f, 5.235f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);

        return true;
    }
};

// 192135
class go_jotunheim_cage : public GameObjectScript
{
public:
    go_jotunheim_cage() : GameObjectScript("go_jotunheim_cage") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        go->UseDoorOrButton();
        Creature* pPrisoner = go->FindNearestCreature(NPC_EBON_BLADE_PRISONER_HUMAN, 5.0f, true);
        if (!pPrisoner)
        {
            pPrisoner = go->FindNearestCreature(NPC_EBON_BLADE_PRISONER_TROLL, 5.0f, true);
            if (!pPrisoner)
            {
                pPrisoner = go->FindNearestCreature(NPC_EBON_BLADE_PRISONER_ORC, 5.0f, true);
                if (!pPrisoner)
                    pPrisoner = go->FindNearestCreature(NPC_EBON_BLADE_PRISONER_NE, 5.0f, true);
            }
        }
        if (!pPrisoner || !pPrisoner->IsAlive())
            return false;

        pPrisoner->DisappearAndDie();
        player->KilledMonsterCredit(NPC_EBON_BLADE_PRISONER_HUMAN, 0);
        switch (pPrisoner->GetEntry())
        {
            case NPC_EBON_BLADE_PRISONER_HUMAN:
                player->CastSpell(player, SPELL_SUMMON_BLADE_KNIGHT_H, true);
                break;
            case NPC_EBON_BLADE_PRISONER_NE:
                player->CastSpell(player, SPELL_SUMMON_BLADE_KNIGHT_NE, true);
                break;
            case NPC_EBON_BLADE_PRISONER_TROLL:
                player->CastSpell(player, SPELL_SUMMON_BLADE_KNIGHT_TROLL, true);
                break;
            case NPC_EBON_BLADE_PRISONER_ORC:
                player->CastSpell(player, SPELL_SUMMON_BLADE_KNIGHT_ORC, true);
                break;
        }
        return true;
    }
};

// 142715
class go_table_theka : public GameObjectScript
{
public:
    go_table_theka() : GameObjectScript("go_table_theka") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (player->GetQuestStatus(QUEST_SPIDER_GOLD) == QUEST_STATUS_INCOMPLETE)
            player->AreaExploredOrEventHappens(QUEST_SPIDER_GOLD);

        player->SEND_GOSSIP_MENU(GOSSIP_TABLE_THEKA, go->GetGUID());

        return true;
    }
};

// 142189
class go_inconspicuous_landmark : public GameObjectScript
{
public:
    go_inconspicuous_landmark() : GameObjectScript("go_inconspicuous_landmark") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/) override
    {
        if (player->HasItemCount(ITEM_CUERGOS_KEY))
            return false;

        player->CastSpell(player, SPELL_SUMMON_PIRATES_TREASURE_AND_TRIGGER_MOB, true);

        return true;
    }
};

// 184073
class go_ethereal_teleport_pad : public GameObjectScript
{
public:
    go_ethereal_teleport_pad() : GameObjectScript("go_ethereal_teleport_pad") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (!player->HasItemCount(ITEM_TELEPORTER_POWER_PACK))
            return false;

        go->SummonCreature(NPC_IMAGE_WIND_TRADER, go->GetPositionX(), go->GetPositionY(), go->GetPositionZ(), go->GetAngle(player), TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000);

        return true;
    }
};

// 181621 193169
class go_soulwell : public GameObjectScript
{
    public:
        go_soulwell() : GameObjectScript("go_soulwell") { }

        struct go_soulwellAI : public GameObjectAI
        {
            go_soulwellAI(GameObject* go) : GameObjectAI(go)
            {
            }

            /// Due to the fact that this GameObject triggers CMSG_GAMEOBJECT_USE
            /// _and_ CMSG_GAMEOBJECT_REPORT_USE, this GossipHello hook is called
            /// twice. The script's handling is fine as it won't remove two charges
            /// on the well. We have to find how to segregate REPORT_USE and USE.
            bool GossipHello(Player* player) override
            {
                Unit* owner = go->GetOwner();
                if (!owner || owner->GetTypeId() != TYPEID_PLAYER || !player->IsInSameRaidWith(owner->ToPlayer()))
                    return true;
                return false;
            }
        };

        GameObjectAI* GetAI(GameObject* go) const override
        {
            return new go_soulwellAI(go);
        }
};

// 186566 86567 186568 186569 186570 186571 186572 186573 186574 186575
class go_dragonflayer_cage : public GameObjectScript
{
public:
    go_dragonflayer_cage() : GameObjectScript("go_dragonflayer_cage") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        go->UseDoorOrButton();
        if (player->GetQuestStatus(QUEST_PRISONERS_OF_WYRMSKULL) != QUEST_STATUS_INCOMPLETE)
            return true;

        Creature* pPrisoner = go->FindNearestCreature(NPC_PRISONER_PRIEST, 2.0f);
        if (!pPrisoner)
        {
            pPrisoner = go->FindNearestCreature(NPC_PRISONER_MAGE, 2.0f);
            if (!pPrisoner)
            {
                pPrisoner = go->FindNearestCreature(NPC_PRISONER_WARRIOR, 2.0f);
                if (!pPrisoner)
                    pPrisoner = go->FindNearestCreature(NPC_PRISONER_PALADIN, 2.0f);
            }
        }

        if (!pPrisoner || !pPrisoner->IsAlive())
            return true;

        Quest const* qInfo = sObjectMgr->GetQuestTemplate(QUEST_PRISONERS_OF_WYRMSKULL);
        if (qInfo)
        {
            /// @todo prisoner should help player for a short period of time
            player->KilledMonsterCredit(qInfo->RequiredNpcOrGo[0], 0);
            pPrisoner->DisappearAndDie();
        }
        return true;
    }
};

// 187373
class go_tadpole_cage : public GameObjectScript
{
public:
    go_tadpole_cage() : GameObjectScript("go_tadpole_cage") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        go->UseDoorOrButton();
        if (player->GetQuestStatus(QUEST_OH_NOES_THE_TADPOLES) == QUEST_STATUS_INCOMPLETE)
        {
            Creature* pTadpole = go->FindNearestCreature(NPC_WINTERFIN_TADPOLE, 1.0f);
            if (pTadpole)
            {
                pTadpole->DisappearAndDie();
                player->KilledMonsterCredit(NPC_WINTERFIN_TADPOLE, 0);
                //FIX: Summon minion tadpole
            }
        }
        return true;
    }
};

// 188666
class go_amberpine_outhouse : public GameObjectScript
{
public:
    go_amberpine_outhouse() : GameObjectScript("go_amberpine_outhouse") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        QuestStatus status = player->GetQuestStatus(QUEST_DOING_YOUR_DUTY);
        if (status == QUEST_STATUS_INCOMPLETE || status == QUEST_STATUS_COMPLETE || status == QUEST_STATUS_REWARDED)
        {
            player->ADD_GOSSIP_ITEM_DB(9492, 1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->SEND_GOSSIP_MENU(GOSSIP_OUTHOUSE_VACANT, go->GetGUID());
        }
        else
            player->SEND_GOSSIP_MENU(GOSSIP_OUTHOUSE_INUSE, go->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, GameObject* go, uint32 /*sender*/, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF +1)
        {
            player->CLOSE_GOSSIP_MENU();
            Creature* target = GetClosestCreatureWithEntry(player, NPC_OUTHOUSE_BUNNY, 3.0f);
            if (target)
            {
                target->AI()->SetData(1, player->getGender());
                go->CastSpell(target, SPELL_INDISPOSED_III);
            }
            go->CastSpell(player, SPELL_INDISPOSED);
            if (player->HasItemCount(ITEM_ANDERHOLS_SLIDER_CIDER))
                go->CastSpell(player, SPELL_CREATE_AMBERSEEDS);
            return true;
        }
        else
        {
            player->CLOSE_GOSSIP_MENU();
            player->GetSession()->SendNotification(GO_ANDERHOLS_SLIDER_CIDER_NOT_FOUND);
            return false;
        }
    }
};

// 178553
class go_hive_pod : public GameObjectScript
{
public:
    go_hive_pod() : GameObjectScript("go_hive_pod") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        player->SendLoot(go->GetGUID(), LOOT_CORPSE);
        go->SummonCreature(NPC_HIVE_AMBUSHER, go->GetPositionX()+1, go->GetPositionY(), go->GetPositionZ(), go->GetAngle(player), TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000);
        go->SummonCreature(NPC_HIVE_AMBUSHER, go->GetPositionX(), go->GetPositionY()+1, go->GetPositionZ(), go->GetAngle(player), TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000);
        return true;
    }
};

// 190752
class go_massive_seaforium_charge : public GameObjectScript
{
    public:
        go_massive_seaforium_charge() : GameObjectScript("go_massive_seaforium_charge") { }

        bool OnGossipHello(Player* /*player*/, GameObject* go) override
        {
            go->SetLootState(GO_JUST_DEACTIVATED);
            return true;
        }
};

// 186491 186492 186493 186494 186498 186499 186500 186501 186502 186503 186504 186505 186508
// 186509 186512 186513 186514 186515 186516 186883 186895 186907 186908 186910 186911 186923 
// 186924 186495 186496 186497 186507 186510 186511 186517 186518 186798 186909 186929 186930
class go_gjalerbron_cage : public GameObjectScript
{
    public:
        go_gjalerbron_cage() : GameObjectScript("go_gjalerbron_cage") { }

        enum Cages
        {
            SAY_FREE = 0,
        };

        bool OnGossipHello(Player* player, GameObject* go) override
        {
            go->UseDoorOrButton();
            if ((player->GetTeamId() == TEAM_ALLIANCE && player->GetQuestStatus(QUEST_ALLIANCE_OF_KEYS_AND_CAGES) == QUEST_STATUS_INCOMPLETE) ||
                (player->GetTeamId() == TEAM_HORDE && player->GetQuestStatus(QUEST_HORDE_OF_KEYS_AND_CAGES) == QUEST_STATUS_INCOMPLETE))
            {
                if (Creature* prisoner = go->FindNearestCreature(NPC_GJALERBRON_PRISONER, 5.0f))
                {
                    player->KilledMonsterCredit(NPC_GJALERBRON_PRISONER, 0);

                    prisoner->AI()->Talk(SAY_FREE);
                    prisoner->DespawnOrUnsummon(6000);
                }
            }
            return true;
        }
};

// 186490
class go_large_gjalerbron_cage : public GameObjectScript
{
    public:
        go_large_gjalerbron_cage() : GameObjectScript("go_large_gjalerbron_cage") { }

        enum Cages
        {
            SAY_FREE = 0,
        };

        bool OnGossipHello(Player* player, GameObject* go) override
        {
            go->UseDoorOrButton();
            if ((player->GetTeamId() == TEAM_ALLIANCE && player->GetQuestStatus(QUEST_ALLIANCE_OF_KEYS_AND_CAGES) == QUEST_STATUS_INCOMPLETE) ||
                (player->GetTeamId() == TEAM_HORDE && player->GetQuestStatus(QUEST_HORDE_OF_KEYS_AND_CAGES) == QUEST_STATUS_INCOMPLETE))
            {
                std::list<Creature*> prisonerList;
                GetCreatureListWithEntryInGrid(prisonerList, go, NPC_GJALERBRON_PRISONER, INTERACTION_DISTANCE);
                for (std::list<Creature*>::const_iterator itr = prisonerList.begin(); itr != prisonerList.end(); ++itr)
                {
                    player->KilledMonsterCredit(NPC_GJALERBRON_PRISONER, (*itr)->GetGUID());
                    (*itr)->DespawnOrUnsummon(6000);
                    (*itr)->AI()->Talk(SAY_FREE);
                }
            }
            return false;
        }
};

// 185202 185203 185204 185205
class go_veil_skith_cage : public GameObjectScript
{
    public:
       go_veil_skith_cage() : GameObjectScript("go_veil_skith_cage") { }

       enum Cages
       {
           SAY_FREE = 0,
       };

       bool OnGossipHello(Player* player, GameObject* go) override
       {
           go->UseDoorOrButton();
           if (player->GetQuestStatus(QUEST_MISSING_FRIENDS) == QUEST_STATUS_INCOMPLETE)
           {
               std::list<Creature*> childrenList;
               GetCreatureListWithEntryInGrid(childrenList, go, NPC_CAPTIVE_CHILD, INTERACTION_DISTANCE);
               for (std::list<Creature*>::const_iterator itr = childrenList.begin(); itr != childrenList.end(); ++itr)
               {
                   player->KilledMonsterCredit(NPC_CAPTIVE_CHILD, (*itr)->GetGUID());
                   (*itr)->DespawnOrUnsummon(5000);
                   (*itr)->GetMotionMaster()->MovePoint(1, go->GetPositionX()+5, go->GetPositionY(), go->GetPositionZ());
                   (*itr)->AI()->Talk(SAY_FREE);
                   (*itr)->GetMotionMaster()->Clear();
               }
           }
           return false;
       }
};

// 186649
class go_frostblade_shrine : public GameObjectScript
{
public:
    go_frostblade_shrine() : GameObjectScript("go_frostblade_shrine") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        go->UseDoorOrButton(10);
        if (!player->HasAura(SPELL_RECENT_MEDITATION))
            if (player->GetQuestStatus(QUEST_THE_CLEANSING_HORDE) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_THE_CLEANSING_ALLIANCE) == QUEST_STATUS_INCOMPLETE)
            {
                player->CastSpell(player, SPELL_CLEANSING_SOUL);
                player->SetStandState(UNIT_STAND_STATE_SIT);
            }
            return true;
    }
};

// 187971 187973 187952 187963 187943 187950 187929 187961 187945 187959 187957 187968 187948
// 187953 187946 187970 187966 187975 187930 187969 187944 187951 187956 187954 187947 187972
// 187914 187964 187559 187965 187927 187564 187916 187920 187923 187924 187925 187926 187928
// 187931 187932 187934 187936 187938 187940 194043 187921 194037 194046 194042 187958 194044
// 194045 194034 194035 194032 194033 187922 187967 187917 187937 187939 187941 187942 187949
// 187962 187919 187933 187935 187955 187960 187974 194036 194038 194039 194040 194048 194049
class go_midsummer_bonfire : public GameObjectScript
{
public:
    go_midsummer_bonfire() : GameObjectScript("go_midsummer_bonfire") { }

    bool OnGossipSelect(Player* player, GameObject* /*go*/, uint32 /*sender*/, uint32 /*action*/) override
    {
        player->CastSpell(player, SPELL_STAMP_OUT_BONFIRE_QUEST_COMPLETE, true);
        player->CLOSE_GOSSIP_MENU();
        return false;
    }
};

// 197195
class go_ship_to_vashjir_197195 : public GameObjectScript
{
public:
    go_ship_to_vashjir_197195() : GameObjectScript("go_ship_to_vashjir_197195") {}

    struct go_ship_to_vashjir_197195AI : public GameObjectAI
    {
        go_ship_to_vashjir_197195AI(GameObject* go) : GameObjectAI(go) { }

        EventMap m_events;
        uint64   m_bunnyControllerGUID;
        bool     m_playerNearWithActiveQuest;

        void Reset() 
        { 
            m_bunnyControllerGUID = 0;
            m_playerNearWithActiveQuest = false;
            SetShipVisibleState();
            m_events.RescheduleEvent(EVENT_CHECK_POSITION, 10000);
        }

        void EventInform(uint32 eventId)
        {
            if (m_bunnyControllerGUID)
                if (Creature* bunny = sObjectAccessor->GetCreature(*go, m_bunnyControllerGUID))
                    bunny->AI()->DoAction(eventId);

            switch (eventId)
            {
            case 22520:
                break;
            case 24009:
                break;
            case 24014:
                break;
            case 24015:
                break;
            case 24036:
                break;
            case 24986:
                break;
            case 25075:
                break;
            case 25769:
                SetShipVisibleState();
                break;
            }
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case 32520: // alliance bunny controller outside ship
                m_bunnyControllerGUID = guid;
                break;
            }
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case 1:
            {
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
                case EVENT_CHECK_POSITION:
                    m_events.ScheduleEvent(EVENT_CHECK_POSITION, 10000);
                    break;
                }
            }
        }

        void SetShipVisibleState()
        {
            go->SetInPhase(171, false, m_playerNearWithActiveQuest);
            go->SetInPhase(172, false, !m_playerNearWithActiveQuest);
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return new go_ship_to_vashjir_197195AI(go);
    }
};

// 203466
class go_ship_to_vashjir_203466 : public GameObjectScript
{
public:
    go_ship_to_vashjir_203466() : GameObjectScript("go_ship_to_vashjir_203466") {}
    
    struct go_ship_to_vashjir_203466AI : public GameObjectAI
    {
        go_ship_to_vashjir_203466AI(GameObject* go) : GameObjectAI(go) { }

        EventMap m_events;
        uint64   m_bunnyBridgeGUID;
        uint64   m_bunnyShipGUID;
        uint64   m_nazgrimGUID;
        uint64   m_vanGuardGUID[7];

        void Reset() 
        { 
            m_bunnyBridgeGUID = 0;
            m_bunnyShipGUID = 0;
            m_nazgrimGUID = 0;
            SetShipVisibleState(false);
            for (int i = 0; i < 8; i++)
                m_vanGuardGUID[i] = 0;
        }

        void EventInform(uint32 eventId)
        {
            if (!m_bunnyShipGUID)
                if (Creature* bunny = GetStaticPassenger(40559))
                    m_bunnyShipGUID = bunny->GetGUID();

            if (m_bunnyShipGUID)
                if (Creature* bunny = sObjectAccessor->GetCreature(*go, m_bunnyShipGUID))
                    bunny->AI()->DoAction(eventId);

            if (m_bunnyBridgeGUID)
                if (Creature* bunny = FindCreatureWorldwide(m_bunnyBridgeGUID))
                    bunny->AI()->DoAction(eventId);

            switch (eventId)
            {
            case 26605: // teleport to map 1
                if (Creature* bunny = FindCreatureWorldwide(m_bunnyBridgeGUID))
                {
                    bool state = bunny->AI()->GetData(ACTION_IS_PLAYER_NEAR);
                    SetShipVisibleState(state);
                }
                break;
            case 25447:
                if (Creature* bunny = sObjectAccessor->GetCreature(*go, m_bunnyShipGUID))
                    bunny->RemoveAllAuras();
                break;
            case 25445: // arrive bridge
                break;
            case 26515: // departure horde bridge.. now bunny inside ship are the commander
                break;
            case 25467:
                if (IsPassengerPlayerBoarded())
                    if (GetPassengerCrewCount() == 11)
                        if (Creature* bunny = sObjectAccessor->GetCreature(*go, m_bunnyShipGUID))
                            bunny->AI()->DoAction(ACTION_START_ANIM_02);
                break;
            case 25446:
                if (IsPassengerPlayerBoarded())
                    if (Creature* bunny = sObjectAccessor->GetCreature(*go, m_bunnyShipGUID))
                        bunny->AddAura(80225, bunny);
                break;
            case 25452: // teleport to map 0
                if (Creature* bunny = FindCreatureWorldwide(m_bunnyBridgeGUID))
                {
                    bool state = bunny->AI()->GetData(ACTION_IS_PLAYER_NEAR);
                    SetShipVisibleState(state);
                }
                break;
            case 25489:
                break;
            case 25448:
                break;
            case 25428:
                break;
            
            }
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case 32520: // horde bunny controller outside ship
                m_bunnyBridgeGUID = guid;
                break;
            case 43091: // horde bunny controller inside ship
                break;
            case NPC_LEGIONNAIRE_NAZGRIM:
                m_nazgrimGUID = guid;
                break;
            case eVanGuardAA:
            case eVanGuardAB:
            case eVanGuardBA:
            case eVanGuardBB:
            case eVanGuardBC:
            case eVanGuardCA:
            case eVanGuardCB:
            case eVanGuardDA:
                if (Transport* transport = go->ToTransport())
                    if (Creature* old = sObjectAccessor->GetCreature(*go, guid))
                    {
                        uint32 id = old->AI()->GetData(old->GetEntry());
                        float x, y, z, o;
                        old->GetPosition(x, y, z, o);
                        transport->CalculatePassengerOffset(x, y, z, &o);
                        (y < 0.0f) ? o = 1.5f : o = 4.9f;
                        if (Creature* guard = CreateCreatureAsPassenger(NPC_HELLSCREAMS_VANGUARD, x, y, z, o))
                        {
                            guard->AI()->SetData(NPC_HELLSCREAMS_VANGUARD, id);
                            guard->AI()->DoAction(ACTION_CREATE_VANGUARD);
                        }
                    }
                break;
            }
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case ACTION_CREATE_NAZGRIM: 
                if (Transport* transport = go->ToTransport())
                    if (Creature* nazgrimOld = sObjectAccessor->GetCreature(*go, m_nazgrimGUID))
                    {
                        float x, y, z, o;
                        nazgrimOld->GetPosition(x, y, z, o);
                        transport->CalculatePassengerOffset(x, y, z, &o);
                        if (Creature* nazgrim = CreateCreatureAsPassenger(43100, x, y, z, 3.5f))
                            nazgrim->AI()->DoAction(ACTION_CREATE_NAZGRIM);
                    }
                    
                break;
            }
        }

        void SetShipVisibleState(uint32 state)
        {
            bool append = bool(state) | IsPassengerPlayerBoarded();
            go->SetInPhase(171, false, append);
            go->SetInPhase(173, true, !append);
        }

        Creature* FindCreatureWorldwide(uint64 guid)
        {
            if (Creature* cr = HashMapHolder<Creature>::Find(guid))
                return cr;

            return nullptr;
        }

        bool IsPassengerPlayerBoarded()
        {
            if (Transport* transport = go->ToTransport())
            {
                std::set<WorldObject*> pList = transport->GetPassengers();
                if (!pList.empty())
                    return true;
            }
            return false;
        }

        bool GetPassengerCrewCount()
        {
            if (Transport* transport = go->ToTransport())
            {
                std::set<WorldObject*> pList = transport->GetStaticPassengers();
                return pList.size();
            }
            return 0;
        }

        GameObject* CreateGameObjectAsPassenger(uint32 entry, float x, float y, float z, float o)
        {
            if (Transport* transport = go->ToTransport())
                if (uint32 guid = sObjectMgr->GenerateLowGuid(HIGHGUID_GAMEOBJECT))
                {
                    GameObjectData& data = sObjectMgr->NewGOData(guid);
                    data.id = entry;
                    data.phaseMask = 1;
                    data.posX = x;
                    data.posY = y;
                    data.posZ = z;
                    data.orientation = o;
                    GameObject* g = transport->CreateGOPassenger(guid, &data);
                    sObjectMgr->AddGameobjectToGrid(guid, &data);
                    return g;
                }
        }

        Creature* CreateCreatureAsPassenger(uint32 entry, float x, float y, float z, float o)
        {
            if (Transport* transport = go->ToTransport())
                if (uint32 guid = sObjectMgr->GenerateLowGuid(HIGHGUID_UNIT))
                {
                    CreatureData& data = sObjectMgr->NewOrExistCreatureData(guid);
                    data.id = entry;
                    data.phaseMask = 1;
                    data.posX = x;
                    data.posY = y;
                    data.posZ = z;
                    data.orientation = o;
                    Creature* c = transport->CreateNPCPassenger(guid, &data);
                    sObjectMgr->AddCreatureToGrid(guid, &data);
                    return c;
                }
        }

        Creature* GetStaticPassenger(uint32 entry)
        {
            if (Transport* transport = go->ToTransport())
            {
                const std::set<WorldObject*> spList = transport->GetStaticPassengers();
                for (auto wo : spList)
                    if (Creature* npc = wo->ToCreature())
                        if (npc->GetEntry() == entry)
                            return npc;
            }
            return nullptr;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const
    {
        return new go_ship_to_vashjir_203466AI(go);
    }
};

void AddSC_go_scripts()
{
    new go_cat_figurine();
    new go_barov_journal();
    new go_field_repair_bot_74A();
    new go_gilded_brazier();
    new go_orb_of_command();
    new go_shrine_of_the_birds();
    new go_southfury_moonstone();
    new go_tablet_of_madness();
    new go_tablet_of_the_seven();
    new go_jump_a_tron();
    new go_ethereum_prison();
    new go_ethereum_stasis();
    new go_resonite_cask();
    new go_sacred_fire_of_life();
    new go_tele_to_dalaran_crystal();
    new go_tele_to_violet_stand();
    new go_fel_crystalforge();
    new go_bashir_crystalforge();
    new go_matrix_punchograph();
    new go_scourge_cage();
    new go_arcane_prison();
    new go_blood_filled_orb();
    new go_jotunheim_cage();
    new go_table_theka();
    new go_inconspicuous_landmark();
    new go_ethereal_teleport_pad();
    new go_soulwell();
    new go_tadpole_cage();
    new go_dragonflayer_cage();
    new go_amberpine_outhouse();
    new go_hive_pod();
    new go_massive_seaforium_charge();
    new go_gjalerbron_cage();
    new go_large_gjalerbron_cage();
    new go_veil_skith_cage();
    new go_frostblade_shrine();
    new go_midsummer_bonfire();
    new go_ship_to_vashjir_197195();
    new go_ship_to_vashjir_203466();
}
