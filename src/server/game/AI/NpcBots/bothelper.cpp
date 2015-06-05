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

const uint8 GroupIcons[TARGETICONCOUNT] =
{
    /*STAR        = */0x001,
    /*CIRCLE      = */0x002,
    /*DIAMOND     = */0x004,
    /*TRIANGLE    = */0x008,
    /*MOON        = */0x010,
    /*SQUARE      = */0x020,
    /*CROSS       = */0x040,
    /*SKULL       = */0x080
};

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

BotHelper::BotHelper(Player* const master) : _master(master) { }
BotHelper::~BotHelper() {}

bool BotHelper::OnGossipSelect(Player* player, uint32 sender, uint32 action)
{
    switch (sender)
    {
        case SENDER_MAIN_PAGE:                          OnGossipHello(player);                              break;

        case SENDER_CREATE_NBOT_MENU:                   SendCreateNPCBotMenu(player, action);               break;
        case SENDER_CREATE_NBOT:                        SendCreateNPCBot(player, action);                   break;
        case SENDER_REMOVE_NBOT_MENU:                   SendRemoveNPCBotMenu(player, action);               break;
        case SENDER_REMOVE_NBOT:                        SendRemoveNPCBot(player, action);                   break;

        case SENDER_INFO_WHISPER:                       SendBotHelpWhisper(player, action);                 break;

        default:
            break;
    }
    return true;
}

bool BotHelper::OnGossipHello(Player* player)
{
    player->PlayerTalkClass->ClearMenus(); //in case of return;

    uint8 count = 0;

    uint8 maxNBcount = player->GetMaxNpcBots();

    bool allowNBots = sConfigMgr->GetBoolDefault("Bot.EnableNpcBots", true) && !player->RestrictBots();

    std::string tempstr;

    if (player->HaveBot())
    {
        count = player->GetNpcBotsCount();
        if (count > 0)
        {
            tempstr = "Abandon my Minion";
            player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, GetLocaleStringForTextID(tempstr, ABANDON_MINION, player->GetSession()->GetSessionDbLocaleIndex()), SENDER_REMOVE_NBOT_MENU, GOSSIP_ACTION_INFO_DEF + 4, "", 0);
        }
        if (count < maxNBcount && allowNBots)
        {
            tempstr = "Recruit a Minion";
            player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, GetLocaleStringForTextID(tempstr, RECRUIT_MINION, player->GetSession()->GetSessionDbLocaleIndex()), SENDER_CREATE_NBOT_MENU, GOSSIP_ACTION_INFO_DEF + 2, "", 0);
        }
    }
    else if (allowNBots && maxNBcount != 0)
    {
        tempstr = "Recruit a Minion";
        player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, GetLocaleStringForTextID(tempstr, RECRUIT_MINION, player->GetSession()->GetSessionDbLocaleIndex()), SENDER_CREATE_NBOT_MENU, GOSSIP_ACTION_INFO_DEF + 2, "", 0);
    }

    tempstr = "Help";
    player->PlayerTalkClass->GetGossipMenu().AddMenuItem(6, 0, GetLocaleStringForTextID(tempstr, HELP_STR, player->GetSession()->GetSessionDbLocaleIndex()), SENDER_INFO_WHISPER, GOSSIP_ACTION_INFO_DEF + 6, "", 0);

    player->PlayerTalkClass->SendGossipMenu(8446, player->GetGUID());
    return true;
}

void BotHelper::SendRemoveNPCBot(Player* player, uint32 action)
{
    int8 x = action - GOSSIP_ACTION_INFO_DEF;
    if (x == 1)
    {
        player->CLOSE_GOSSIP_MENU();
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
    player->CLOSE_GOSSIP_MENU();
}

void BotHelper::SendRemoveNPCBotMenu(Player* player, uint32 /*action*/)
{
    player->PlayerTalkClass->ClearMenus();
    if (player->GetNpcBotsCount() == 1)
    {
        for (uint8 i = 0; i != player->GetMaxNpcBots(); ++i)
            player->RemoveBot(player->GetBotMap(i)->_Guid(), true);
        player->CLOSE_GOSSIP_MENU();
        return;
    }
    std::string tempstr = "REMOVE ALL";
    player->ADD_GOSSIP_ITEM(9, GetLocaleStringForTextID(tempstr, REMOVE_ALL, player->GetSession()->GetSessionDbLocaleIndex()), SENDER_REMOVE_NBOT, GOSSIP_ACTION_INFO_DEF + 1);

    uint8 x = 2;
    for (uint8 i = 0; i != player->GetMaxNpcBots(); ++i)
    {
        Creature* bot = player->GetBotMap(i)->_Cre();
        if (!bot) continue;
        player->ADD_GOSSIP_ITEM(9, bot->GetName(), SENDER_REMOVE_NBOT, GOSSIP_ACTION_INFO_DEF + x);
        ++x;
    }

    tempstr = "BACK";
    player->ADD_GOSSIP_ITEM(0, GetLocaleStringForTextID(tempstr, BACK_STRING, player->GetSession()->GetSessionDbLocaleIndex()), SENDER_MAIN_PAGE, GOSSIP_ACTION_INFO_DEF + x);

    player->PlayerTalkClass->SendGossipMenu(8446, player->GetGUID());
}

void BotHelper::SendCreateNPCBot(Player* player, uint32 action)
{
    uint8 bot_class = 0;
    if (action == GOSSIP_ACTION_INFO_DEF + 1)//"Back"
    {
        player->CLOSE_GOSSIP_MENU();
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
    player->CLOSE_GOSSIP_MENU();
    return;
}

void BotHelper::SendCreateNPCBotMenu(Player* player, uint32 /*action*/)
{
    std::string cost = player->GetNpcBotCostStr();
    player->PlayerTalkClass->ClearMenus();

    std::string tempstr = "Recruit a Warrior ";
    player->ADD_GOSSIP_ITEM(9, GetLocaleStringForTextID(tempstr, RECRUIT_WARRIOR, player->GetSession()->GetSessionDbLocaleIndex()) + cost, SENDER_CREATE_NBOT, GOSSIP_ACTION_INFO_DEF + 2);
    tempstr = "Recruit a Hunter ";
    player->ADD_GOSSIP_ITEM(9, GetLocaleStringForTextID(tempstr, RECRUIT_HUNTER, player->GetSession()->GetSessionDbLocaleIndex()) + cost, SENDER_CREATE_NBOT, GOSSIP_ACTION_INFO_DEF + 3);
    tempstr = "Recruit a Paladin ";
    player->ADD_GOSSIP_ITEM(9, GetLocaleStringForTextID(tempstr, RECRUIT_PALADIN, player->GetSession()->GetSessionDbLocaleIndex()) + cost, SENDER_CREATE_NBOT, GOSSIP_ACTION_INFO_DEF + 4);
    tempstr = "Recruit a Shaman ";
    player->ADD_GOSSIP_ITEM(9, GetLocaleStringForTextID(tempstr, RECRUIT_SHAMAN, player->GetSession()->GetSessionDbLocaleIndex()) + cost, SENDER_CREATE_NBOT, GOSSIP_ACTION_INFO_DEF + 5);
    tempstr = "Recruit a Rogue ";
    player->ADD_GOSSIP_ITEM(9, GetLocaleStringForTextID(tempstr, RECRUIT_ROGUE, player->GetSession()->GetSessionDbLocaleIndex()) + cost, SENDER_CREATE_NBOT, GOSSIP_ACTION_INFO_DEF + 6);
    tempstr = "Recruit a Druid ";
    player->ADD_GOSSIP_ITEM(3, GetLocaleStringForTextID(tempstr, RECRUIT_DRUID, player->GetSession()->GetSessionDbLocaleIndex()) + cost, SENDER_CREATE_NBOT, GOSSIP_ACTION_INFO_DEF + 7);
    tempstr = "Recruit a Mage ";
    player->ADD_GOSSIP_ITEM(3, GetLocaleStringForTextID(tempstr, RECRUIT_MAGE, player->GetSession()->GetSessionDbLocaleIndex()) + cost, SENDER_CREATE_NBOT, GOSSIP_ACTION_INFO_DEF + 8);
    tempstr = "Recruit a Priest ";
    player->ADD_GOSSIP_ITEM(3, GetLocaleStringForTextID(tempstr, RECRUIT_PRIEST, player->GetSession()->GetSessionDbLocaleIndex()) + cost, SENDER_CREATE_NBOT, GOSSIP_ACTION_INFO_DEF + 9);
    tempstr = "Recruit a Warlock ";
    player->ADD_GOSSIP_ITEM(3, GetLocaleStringForTextID(tempstr, RECRUIT_WARLOCK, player->GetSession()->GetSessionDbLocaleIndex()) + cost, SENDER_CREATE_NBOT, GOSSIP_ACTION_INFO_DEF + 10);
    if (player->getLevel() >= 55)
    {
        tempstr = "Recruit a Death Knight ";
        player->ADD_GOSSIP_ITEM(9, GetLocaleStringForTextID(tempstr, RECRUIT_DEATH_KNIGHT, player->GetSession()->GetSessionDbLocaleIndex()) + cost, SENDER_CREATE_NBOT, GOSSIP_ACTION_INFO_DEF + 11);
    }

    std::ostringstream buff;
    uint8 bots = player->GetNpcBotsCount();
    uint8 maxNBcount = player->GetMaxNpcBots();
    uint32 freeNBSlots = maxNBcount - bots;

    if (freeNBSlots == 0)
    {
        tempstr = "no more bots available";
        buff << GetLocaleStringForTextID(tempstr, NO_MORE_AVAILABLE, player->GetSession()->GetSessionDbLocaleIndex());
    }
    else
    {
        buff << freeNBSlots;
        buff << ' ';
        if (freeNBSlots == 1)
        {
            if (bots == 0)
            {
                tempstr = "bot available";
                buff << GetLocaleStringForTextID(tempstr, ONE_AVAILABLE, player->GetSession()->GetSessionDbLocaleIndex());
            }
            else
            {
                tempstr = "more bot available";
                buff << GetLocaleStringForTextID(tempstr, ONE_MORE_AVAILABLE, player->GetSession()->GetSessionDbLocaleIndex());
            }
        }
        else
        {
            if (bots == 0)
            {
                tempstr = "bots available";
                buff << GetLocaleStringForTextID(tempstr, SOME_AVAILABLE, player->GetSession()->GetSessionDbLocaleIndex());
            }
            else
            {
                tempstr = "more bots available";
                buff << GetLocaleStringForTextID(tempstr, SOME_MORE_AVAILABLE, player->GetSession()->GetSessionDbLocaleIndex());
            }
        }
    }
    player->ADD_GOSSIP_ITEM(0, buff.str(), SENDER_CREATE_NBOT_MENU, GOSSIP_ACTION_INFO_DEF + 12);

    tempstr = "BACK";
    player->ADD_GOSSIP_ITEM(0, GetLocaleStringForTextID(tempstr, BACK_STRING, player->GetSession()->GetSessionDbLocaleIndex()), SENDER_MAIN_PAGE, GOSSIP_ACTION_INFO_DEF + 13);

    player->PlayerTalkClass->SendGossipMenu(8446, player->GetGUID());
}

void BotHelper::SendBotHelpWhisper(Player* player, uint32 /*action*/)
{
    player->CLOSE_GOSSIP_MENU();
    ChatHandler ch(player->GetSession());
    //Basic
    std::string tempstr = "To see list of available npcbot commands type .npcbot or .npcb";
    std::string msg2 = GetLocaleStringForTextID(tempstr, ABOUT_BASIC_STR2, player->GetSession()->GetSessionDbLocaleIndex());
    tempstr = "You can also use .maintank (or .mt or .main) command on any party member (even npcbot) so your bots will stick to your plan";
    std::string msg3 = GetLocaleStringForTextID(tempstr, ABOUT_BASIC_STR3, player->GetSession()->GetSessionDbLocaleIndex());
    ch.SendSysMessage(msg2.c_str());
    ch.SendSysMessage(msg3.c_str());
    //Heal Icons
    uint8 mask = sConfigMgr->GetIntDefault("Bot.HealTargetIconsMask", 8);
    std::string msg4 = "";
    if (mask == 255)
    {
        tempstr = "If you want your npcbots to heal someone out of your party set any raid target icon on them";
        msg4 = GetLocaleStringForTextID(tempstr, ABOUT_ICONS_STR1, player->GetSession()->GetSessionDbLocaleIndex());
        ch.SendSysMessage(msg4.c_str());
    }
    else if (mask != 0)
    {
        tempstr = "If you want your npcbots to heal someone out of your party set proper raid target icon on them, one of these: ";
        msg4 = GetLocaleStringForTextID(tempstr, ABOUT_ICONS_STR2, player->GetSession()->GetSessionDbLocaleIndex());
        std::string iconrow = "";
        uint8 count = 0;
        for (uint8 i = 0; i != TARGETICONCOUNT; ++i)
        {
            if (mask & GroupIcons[i])
            {
                if (count != 0)
                    iconrow += ", ";
                ++count;
                switch (i)
                {
                    case 0:
                        tempstr = "star";
                        iconrow += GetLocaleStringForTextID(tempstr, ICON_STRING_STAR, player->GetSession()->GetSessionDbLocaleIndex());
                        break;
                    case 1:
                        tempstr = "circle";
                        iconrow += GetLocaleStringForTextID(tempstr, ICON_STRING_CIRCLE, player->GetSession()->GetSessionDbLocaleIndex());
                        break;
                    case 2:
                        tempstr = "diamond";
                        iconrow += GetLocaleStringForTextID(tempstr, ICON_STRING_DIAMOND, player->GetSession()->GetSessionDbLocaleIndex());
                        break;
                    case 3:
                        tempstr = "triangle";
                        iconrow += GetLocaleStringForTextID(tempstr, ICON_STRING_TRIANGLE, player->GetSession()->GetSessionDbLocaleIndex());
                        break;
                    case 4:
                        tempstr = "moon";
                        iconrow += GetLocaleStringForTextID(tempstr, ICON_STRING_MOON, player->GetSession()->GetSessionDbLocaleIndex());
                        break;
                    case 5:
                        tempstr = "square";
                        iconrow += GetLocaleStringForTextID(tempstr, ICON_STRING_SQUARE, player->GetSession()->GetSessionDbLocaleIndex());
                        break;
                    case 6:
                        tempstr = "cross";
                        iconrow += GetLocaleStringForTextID(tempstr, ICON_STRING_CROSS, player->GetSession()->GetSessionDbLocaleIndex());
                        break;
                    case 7:
                        tempstr = "skull";
                        iconrow += GetLocaleStringForTextID(tempstr, ICON_STRING_SKULL, player->GetSession()->GetSessionDbLocaleIndex());
                        break;
                    default:
                        tempstr = "unknown icon";
                        iconrow += GetLocaleStringForTextID(tempstr, ICON_STRING_UNKNOWN, player->GetSession()->GetSessionDbLocaleIndex());
                        break;
                }
            }
        }
        msg4 += iconrow;
        ch.SendSysMessage(msg4.c_str());
    }
}

std::string BotHelper::GetLocaleStringForTextID(std::string& textValue, uint32 textId, int32 localeIdx)
{
    if (textId >= MAX_STRINGS)
    {
        TC_LOG_ERROR("entities.player", "botgiver:GetLocaleStringForTextID:: unknown text id: %u!", uint32(textId));
        return textValue;
    }

    if (localeIdx == DEFAULT_LOCALE)
        return textValue; //use default

    if (localeIdx < 0)
    {
        TC_LOG_ERROR("entities.player", "botgiver:GetLocaleStringForTextID:: unknown locale: %i! Sending default locale text...", localeIdx);
        return textValue;
    }

    uint32 idxEntry = MAKE_PAIR32(60000, textId);
    if (GossipMenuItemsLocale const* no = sObjectMgr->GetGossipMenuItemsLocale(idxEntry))
        ObjectMgr::GetLocaleString(no->OptionText, localeIdx, textValue);
    return textValue;
}
