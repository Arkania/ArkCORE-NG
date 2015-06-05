#ifndef _BOTHLP_H
#define _BOTHLP_H

#include "Common.h"

class Player;

class BotHelper
{
    public:
        BotHelper(Player* const master);
        ~BotHelper();

        Player* GetOwner() const { return _master; }

        static bool OnGossipHello(Player* player);
        static bool OnGossipSelect(Player* player, uint32 sender, uint32 action);

    private:
        static void SendRemoveNPCBot(Player* player, uint32 action);
        static void SendRemoveNPCBotMenu(Player* player, uint32 /*action*/);
        static void SendCreateNPCBot(Player* player, uint32 action);
        static void SendCreateNPCBotMenu(Player* player, uint32 /*action*/);


        static void SendBotHelpWhisper(Player* player, uint32 /*action*/);
        static std::string GetLocaleStringForTextID(std::string& textValue, uint32 textId, int32 localeIdx = 0);

        Player* const _master;
};

#endif
