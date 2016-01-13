
/*
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
*
* @File : sc_npc_teleport.cpp
* @Authors : Wilibald09
* @Date : 19/08/2008
* @Version : 1.2
*/

#include "ScriptPCH.h"
#include "sc_npc_teleport.h"
#include <sstream>

#define GOSSIP_SHOW_DEST        1000
#define GOSSIP_TELEPORT         1001
#define GOSSIP_NEXT_PAGEC       1002
#define GOSSIP_PREV_PAGEC       1003
#define GOSSIP_NEXT_PAGED       1004
#define GOSSIP_PREV_PAGED       1005
#define GOSSIP_MAIN_MENU        1006

#define SPELL_ID_PASSIVE_RESURRECTION_SICKNESS  15007
#define SPELL_VISUAL_TELEPORT   35517

#define NB_ITEM_PAGE            15
#define MSG_CAT                 100000
#define MSG_DEST                100001

#define NEXT_PAGE               "-> [Next Page]"
#define PREV_PAGE               "<- [Previous Page]"
#define MAIN_MENU               "<= [Main Menu]"


using namespace nsNpcTel;


namespace
{
    Page PageC, PageD;
    Page Cat;

    // Conversion function int->string
    std::string ConvertStr(const int64 &val)
    {
        std::ostringstream ostr;
        ostr << val;
        return ostr.str();
    }

    // Conversion function intMoney->stringMoney
    std::string ConvertMoney(const uint32 &Money)
    {
        std::string Str(ConvertStr(Money));
        uint32 SizeStr = Str.length();

        if (SizeStr > 4)
            Str = Str.insert(Str.length()-4, "g");
        if (SizeStr > 2)
            Str = Str.insert(Str.length()-2, "s");
        Str += "c";

        return Str;
    }

    // Teleport Player
    void Teleport(Player * const player, const uint16 &map,
                  const float &X, const float &Y, const float &Z, const float &orient)
    {
        player->CastSpell(player, SPELL_VISUAL_TELEPORT, true);
        player->TeleportTo(map, X, Y, Z, orient);
    }

    // Display categories
    void AffichCat(Player * const player, Creature * const creature)
    {
        uint8 loc = player->GetSession()->GetSessionDbcLocale();

        if (PageC[player] > 0)
            player->ADD_GOSSIP_ITEM(7, PREV_PAGE, GOSSIP_PREV_PAGEC, 0);

        VCatDest_t i (PageC[player] * NB_ITEM_PAGE);
        for ( ; i < TabCatDest.size() && i < (NB_ITEM_PAGE * (PageC[player] + 1)); ++i)
        {
            if (TabCatDest[i].IsAllowedToTeleport(player))
                player->ADD_GOSSIP_ITEM(7, TabCatDest[i].GetName(loc, player->IsGameMaster()).c_str(), GOSSIP_SHOW_DEST, i);
        }

        if (i < TabCatDest.size())
            player->ADD_GOSSIP_ITEM(7, NEXT_PAGE, GOSSIP_NEXT_PAGEC, 0);

        player->SEND_GOSSIP_MENU(MSG_CAT, creature->GetGUID());
    }

    // Display destination categories
    void AffichDest(Player * const player, Creature * const creature)
    {
        uint8 loc = player->GetSession()->GetSessionDbcLocale();

        if (PageD[player] > 0)
            player->ADD_GOSSIP_ITEM(7, PREV_PAGE, GOSSIP_PREV_PAGED, 0);

        CatDest::VDest_t i (PageD[player] * NB_ITEM_PAGE);
        for ( ; i < TabCatDest[Cat[player]].size() && i < (NB_ITEM_PAGE * (PageD[player] + 1)); ++i)
        {
            std::string name = TabCatDest[Cat[player]].GetDest(i).m_name[loc];
            if (name.length() == 0)
                name = TabCatDest[Cat[player]].GetDest(i).m_name[0];

            player->ADD_GOSSIP_ITEM(5, name.c_str(), GOSSIP_TELEPORT, i); 
        }

        if (i < TabCatDest[Cat[player]].size())
            player->ADD_GOSSIP_ITEM(7, NEXT_PAGE, GOSSIP_NEXT_PAGED, 0);

        if (CatDest::CountOfCategoryAllowedBy(player) > 1)
            player->ADD_GOSSIP_ITEM(7, MAIN_MENU, GOSSIP_MAIN_MENU, 0);

        player->SEND_GOSSIP_MENU(MSG_DEST, creature->GetGUID());
    }

    // Verification before teleportation
    void ActionTeleport(Player * const player, Creature * const creature, const uint32 &id)
    {
        Dest dest (TabCatDest[Cat[player]].GetDest(id));

        if (player->getLevel() < dest.m_level && !player->IsGameMaster())
        {
            LocaleConstant loc_idx = player->GetSession()->GetSessionDbLocaleIndex();
            char const* text = sObjectMgr->GetTrinityString(8000, loc_idx);
            std::string msg(text + (" " + ConvertStr(dest.m_level) + "."));

            //std::string msg ("You do not have the required level. This destination requires level " + ConvertStr(dest.m_level) + ".");
            creature->MonsterWhisper(msg.c_str(), player);
            return;
        }

        if (player->GetMoney() < dest.m_cost && !player->IsGameMaster())
        {
            LocaleConstant loc_idx = player->GetSession()->GetSessionDbLocaleIndex();
            char const* text = sObjectMgr->GetTrinityString(8001, loc_idx);
            std::string msg(text + (" " + ConvertMoney(dest.m_cost) + "."));

            // std::string msg ("You do not have enough money. The price for teleportation is " + ConvertMoney(dest.m_cost) + ".");
            creature->MonsterWhisper(msg.c_str(), player);
            return;
        }

        if (!player->IsGameMaster() && dest.m_cost)
            player->ModifyMoney(-1 * dest.m_cost);

        Teleport(player, dest.m_map, dest.m_X, dest.m_Y, dest.m_Z, dest.m_orient);
    }
}

class npc_teleport : public CreatureScript
{
public:
    npc_teleport() : CreatureScript("npc_teleport") {}

bool OnGossipHello(Player *player, Creature *creature)
{
    PageC(player) = PageD(player) = Cat(player) = 0;

    if(player->IsInCombat())
    {
        player->CLOSE_GOSSIP_MENU();

        LocaleConstant loc_idx = player->GetSession()->GetSessionDbLocaleIndex();
        char const* text = sObjectMgr->GetTrinityString(8002, loc_idx);
        creature->MonsterWhisper(text, player);

        return true;
    }
    AffichCat(player, creature);
    return true;
}

bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 param)
{
    player->PlayerTalkClass->ClearMenus();
    switch(sender)
    {
      // Display destinations
      case GOSSIP_SHOW_DEST:
        Cat(player) = param;
        AffichDest(player, creature);
        break;

      // Previous categories page
      case GOSSIP_PREV_PAGEC:
        --PageC(player);
        AffichCat(player, creature);
        break;

      // Next page categories
      case GOSSIP_NEXT_PAGEC:
        ++PageC(player);
        AffichCat(player, creature);
        break;

      // Previous destinations page
      case GOSSIP_PREV_PAGED:
        --PageD(player);
        AffichDest(player, creature);
        break;

      // Next destination page
      case GOSSIP_NEXT_PAGED:
        ++PageD(player);
        AffichDest(player, creature);
        break;

      // Display main menu
      case GOSSIP_MAIN_MENU:
        OnGossipHello(player, creature);
        break;

      // Teleportation
      case GOSSIP_TELEPORT:
        player->CLOSE_GOSSIP_MENU();
        if(player->HasAura(SPELL_ID_PASSIVE_RESURRECTION_SICKNESS)) {
            creature->CastSpell(player,38588,false); // Healing effect
            player->RemoveAurasDueToSpell(SPELL_ID_PASSIVE_RESURRECTION_SICKNESS);
        }

        ActionTeleport(player, creature, param);
        break;
    }
    return true;
}
};

void AddSC_npc_teleport()
{
    new npc_teleport;
}
// End of TeleNPC2
