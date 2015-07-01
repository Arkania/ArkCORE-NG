/*
Bot Helper by Graff (onlysuffering@gmail.com)
Type: empty-type player-to-self dialog-like manager for npcbot mod
Complete: ???
Category: scripts/custom/bots
*/

#include "bothelper.h"
#include "Chat.h"
#include "Config.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "Group.h"
#include "Language.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"

enum HelperActions
{
    ACTION_ENABLE                                               = 1,
    ACTION_DISABLE                                              = 2,
    ACTION_TOGGLE                                               = 3
};

enum BotgiverTexIDs
{
    ABANDON_MINION                                              = 3,
    RECRUIT_MINION                                              = 4,
    HELP_STR                                                    = 5,
    ADD_ALL                                                     = 6,
    REMOVE_ALL                                                  = 7,
    RECRUIT_WARRIOR                                             = 8,
    RECRUIT_HUNTER                                              = 9,
    RECRUIT_PALADIN                                             = 10,
    RECRUIT_SHAMAN                                              = 11,
    RECRUIT_ROGUE                                               = 12,
    RECRUIT_DRUID                                               = 13,
    RECRUIT_MAGE                                                = 14,
    RECRUIT_PRIEST                                              = 15,
    RECRUIT_WARLOCK                                             = 16,
    RECRUIT_DEATH_KNIGHT                                        = 17,
    ABOUT_BASIC_STR1                                            = 18,
    ABOUT_BASIC_STR2                                            = 19,
    ABOUT_BASIC_STR3                                            = 20,
    ABOUT_ICONS_STR1                                            = 21,
    ABOUT_ICONS_STR2                                            = 22,
    ICON_STRING_STAR                                            = 23,
    ICON_STRING_CIRCLE                                          = 24,
    ICON_STRING_DIAMOND                                         = 25,
    ICON_STRING_TRIANGLE                                        = 26,
    ICON_STRING_MOON                                            = 27,
    ICON_STRING_SQUARE                                          = 28,
    ICON_STRING_CROSS                                           = 29,
    ICON_STRING_SKULL                                           = 30,
    ICON_STRING_UNKNOWN                                         = 31,
    NO_MORE_AVAILABLE                                           = 32,
    ONE_MORE_AVAILABLE                                          = 33,
    SOME_MORE_AVAILABLE                                         = 34,
    ONE_AVAILABLE                                               = 35,
    SOME_AVAILABLE                                              = 36,

    ENABLE_STRING,
    DISABLE_STRING,
    TOGGLE_STRING,
    BACK_STRING,
    ALL_STRING,
    MAX_STRINGS
};

enum HelperGossip
{
    SENDER_CREATE_NBOT_MENU                                     = 1,
    SENDER_CREATE_NBOT                                          = 2,
    SENDER_REMOVE_NBOT_MENU                                     = 7,
    SENDER_REMOVE_NBOT                                          = 8,

    SENDER_INFO_WHISPER                                         = 9,

    SENDER_MAIN_PAGE,
    MAX_SENDERS
};

#define BOT_GOSSIP 56100
#define BOT_TEXT 8446

BotHelper::BotHelper(Player* const master) : _master(master) { }
BotHelper::~BotHelper() {}

bool BotHelper::OnGossipSelect(Player* player, uint32 sender, uint32 action)
{
    switch (sender)
    {
        case SENDER_MAIN_PAGE:
            OnGossipHello(player);
            break;
        case SENDER_CREATE_NBOT_MENU:
            SendCreateNPCBotMenu(player, action);
            break;
        case SENDER_CREATE_NBOT:
            SendCreateNPCBot(player, action);
            break;
        case SENDER_REMOVE_NBOT_MENU:
            SendRemoveNPCBotMenu(player, action);
            break;
        case SENDER_REMOVE_NBOT:
            SendRemoveNPCBot(player, action);
            break;
        case SENDER_INFO_WHISPER:
            SendBotHelpWhisper(player, action);
            break;
        default:
            break;
    }
    return true;
}

bool BotHelper::OnGossipHello(Player* player)
{
    PlayerMenu* tc = player->PlayerTalkClass;
    tc->ClearMenus();

    uint8 count = 0;
    uint8 maxNBcount = player->GetMaxNpcBots();
    bool allowNBots = sConfigMgr->GetBoolDefault("Bot.EnableNpcBots", true) && !player->RestrictBots();

    if (player->HaveBot())
    {
        count = player->GetNpcBotsCount();
        if (count > 0)
            tc->GetGossipMenu().AddMenuItem(BOT_GOSSIP, 1, SENDER_REMOVE_NBOT_MENU, GOSSIP_ACTION_INFO_DEF + 4);

        if (count < maxNBcount && allowNBots)
            tc->GetGossipMenu().AddMenuItem(BOT_GOSSIP, 0, SENDER_CREATE_NBOT_MENU, GOSSIP_ACTION_INFO_DEF + 2);
    }
    else if (allowNBots && maxNBcount != 0)
        tc->GetGossipMenu().AddMenuItem(BOT_GOSSIP, 0, SENDER_CREATE_NBOT_MENU, GOSSIP_ACTION_INFO_DEF + 2);

    tc->GetGossipMenu().AddMenuItem(BOT_GOSSIP, 2, SENDER_INFO_WHISPER, GOSSIP_ACTION_INFO_DEF + 6);

    tc->SendGossipMenu(BOT_TEXT, player->GetGUID());
    return true;
}

void BotHelper::SendRemoveNPCBot(Player* player, uint32 action)
{
    PlayerMenu* tc = player->PlayerTalkClass;

    int8 x = action - GOSSIP_ACTION_INFO_DEF;
    if (x == 1)
    {
        tc->SendCloseGossip();
        for (uint8 i = 0; i != player->GetMaxNpcBots(); ++i)
            player->RemoveBot(player->GetBotMap(i)->_Guid(), true);
        return;
    }
    for (uint8 i = 0; i != player->GetMaxNpcBots(); ++i)
    {
        if (!player->GetBotMap(i)->_Cre())
            continue;
        if (x == 2)
        {
            player->RemoveBot(player->GetBotMap(i)->_Guid(), true);
            break;
        }
        --x;
    }
    tc->SendCloseGossip();
}

void BotHelper::SendRemoveNPCBotMenu(Player* player, uint32 /*action*/)
{
    PlayerMenu* tc = player->PlayerTalkClass;
    tc->ClearMenus();

    if (player->GetNpcBotsCount() == 1)
    {
        for (uint8 i = 0; i != player->GetMaxNpcBots(); ++i)
            player->RemoveBot(player->GetBotMap(i)->_Guid(), true);

        tc->SendCloseGossip();
        return;
    }

    tc->GetGossipMenu().AddMenuItem(BOT_GOSSIP, 3, SENDER_REMOVE_NBOT, GOSSIP_ACTION_INFO_DEF + 1);

    uint8 x = 2;
    for (uint8 i = 0; i != player->GetMaxNpcBots(); ++i)
    {
        Creature* bot = player->GetBotMap(i)->_Cre();
        if (!bot) continue;
        tc->GetGossipMenu().AddMenuItem(-1, 9, bot->GetName(), SENDER_REMOVE_NBOT, GOSSIP_ACTION_INFO_DEF + x, "", 0);
        ++x;
    }

    AddMenuItem_CountOfAvaibleBots(player, tc);
    AddMenuItem_BackToMainMenu(player, tc);

    tc->SendGossipMenu(BOT_TEXT, player->GetGUID());
}

void BotHelper::SendCreateNPCBot(Player* player, uint32 action)
{
    PlayerMenu* tc = player->PlayerTalkClass;
    
    uint8 bot_class = 0;
    if (action == GOSSIP_ACTION_INFO_DEF + 1)//"Back"
    {
        tc->SendCloseGossip();
        return;
    }
    else if (action == GOSSIP_ACTION_INFO_DEF + 2)
        bot_class = CLASS_WARRIOR;
    else if (action == GOSSIP_ACTION_INFO_DEF + 3)
        bot_class = CLASS_HUNTER;
    else if (action == GOSSIP_ACTION_INFO_DEF + 4)
        bot_class = CLASS_PALADIN;
    else if (action == GOSSIP_ACTION_INFO_DEF + 5)
        bot_class = CLASS_SHAMAN;
    else if (action == GOSSIP_ACTION_INFO_DEF + 6)
        bot_class = CLASS_ROGUE;
    else if (action == GOSSIP_ACTION_INFO_DEF + 7)
        bot_class = CLASS_DRUID;
    else if (action == GOSSIP_ACTION_INFO_DEF + 8)
        bot_class = CLASS_MAGE;
    else if (action == GOSSIP_ACTION_INFO_DEF + 9)
        bot_class = CLASS_PRIEST;
    else if (action == GOSSIP_ACTION_INFO_DEF + 10)
        bot_class = CLASS_WARLOCK;
    else if (action == GOSSIP_ACTION_INFO_DEF + 11)
        bot_class = CLASS_DEATH_KNIGHT;

    if (bot_class != 0)
        player->CreateNPCBot(bot_class);
    tc->SendCloseGossip();
    return;
}

void BotHelper::SendCreateNPCBotMenu(Player* player, uint32 /*action*/)
{
    std::string cost = player->GetNpcBotCostStr();
    PlayerMenu* tc = player->PlayerTalkClass;
    tc->ClearMenus();

    for (uint8 id = 0; id < 9; ++id)
    {
        tc->GetGossipMenu().AddMenuItem(BOT_GOSSIP, 10 + id, SENDER_CREATE_NBOT, GOSSIP_ACTION_INFO_DEF + 2 + id);
    }
    if (player->getLevel() >= 55)
    {
        tc->GetGossipMenu().AddMenuItem(BOT_GOSSIP, 19, SENDER_CREATE_NBOT, GOSSIP_ACTION_INFO_DEF + 11);
    }

    AddMenuItem_CountOfAvaibleBots(player, tc);
    AddMenuItem_BackToMainMenu(player, tc);

    tc->SendGossipMenu(BOT_TEXT, player->GetGUID());
}

void BotHelper::SendBotHelpWhisper(Player* player, uint32 /*action*/)
{
    PlayerMenu* tc = player->PlayerTalkClass;
    tc->SendCloseGossip();
    LocaleConstant loc = player->GetSession()->GetSessionDbLocaleIndex();
    ChatHandler ch(player->GetSession());
    
    std::string msg1 = "\n";
    msg1 += sObjectMgr->GetTrinityString(8010, loc);
    std::string msg2 = sObjectMgr->GetTrinityString(8011, loc);
    ch.SendSysMessage(msg1.c_str());
    ch.SendSysMessage(msg2.c_str());
    uint8 heal_mask = sConfigMgr->GetIntDefault("Bot.HealTargetIconsMask", 8);
    if (heal_mask == 255)
    {
        std::string msg3 = sObjectMgr->GetTrinityString(8012, loc);
        ch.SendSysMessage(msg3.c_str());
    }
    else if (heal_mask != 0)
    {
        std::string msg4 = sObjectMgr->GetTrinityString(8013, loc);
        msg4 += "\n";
        bool addComma = false;
        for (uint8 i = 0; i < TARGETICONCOUNT; ++i)
        {
            uint16 x = 2 ^ i;
            if (addComma)
                msg4 += ", ";
            addComma = true;
            msg4 += sObjectMgr->GetTrinityString(8014 + i, loc);
        }
        ch.SendSysMessage(msg4.c_str());
    }
}

void BotHelper::AddMenuItem_CountOfAvaibleBots(Player* player, PlayerMenu* pm)
{
    uint8 bots = player->GetNpcBotsCount();
    uint8 maxNBcount = player->GetMaxNpcBots();
    uint32 freeNBSlots = maxNBcount - bots;

    if (freeNBSlots == 0)
    {
        pm->GetGossipMenu().AddMenuItem(BOT_GOSSIP, 5, SENDER_CREATE_NBOT_MENU, GOSSIP_ACTION_INFO_DEF + 12);
    }
    else
    {
        if (freeNBSlots == 1)
        {
            if (bots == 0)
                pm->GetGossipMenu().AddMenuItem(BOT_GOSSIP, 6, SENDER_CREATE_NBOT_MENU, GOSSIP_ACTION_INFO_DEF + 12);
            else
                pm->GetGossipMenu().AddMenuItem(BOT_GOSSIP, 7, SENDER_CREATE_NBOT_MENU, GOSSIP_ACTION_INFO_DEF + 12);
        }
        else
        {
            if (bots == 0)
                pm->GetGossipMenu().AddMenuItem(BOT_GOSSIP, 8, SENDER_CREATE_NBOT_MENU, GOSSIP_ACTION_INFO_DEF + 12);
            else
                pm->GetGossipMenu().AddMenuItem(BOT_GOSSIP, 9, SENDER_CREATE_NBOT_MENU, GOSSIP_ACTION_INFO_DEF + 12);
        }
    }

}

void BotHelper::AddMenuItem_BackToMainMenu(Player* player, PlayerMenu* pm)
{
    pm->GetGossipMenu().AddMenuItem(BOT_GOSSIP, 4, SENDER_MAIN_PAGE, GOSSIP_ACTION_INFO_DEF + 13);
}
