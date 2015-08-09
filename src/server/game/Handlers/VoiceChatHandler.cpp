/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
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

#include "Common.h"
#include "Player.h"
#include "World.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "Opcodes.h"
#include "Log.h"
#include "ChannelMgr.h"
#include "Channel.h"
#include "Chat.h"
#include "ObjectMgr.h"
#include "SocialMgr.h"

void WorldSession::HandleVoiceSessionEnableOpcode(WorldPacket& recvData)
{
    TC_LOG_DEBUG("network", "WORLD: CMSG_VOICE_SESSION_ENABLE");

    bool VoiceEnabled, MicrophoneEnabled;

    recvData >> VoiceEnabled;
    recvData >> MicrophoneEnabled;
    // Something lacking here.
}

void WorldSession::HandleChannelVoiceOnOpcode(WorldPacket& recvData)
{
    TC_LOG_DEBUG("network", "WORLD: CMSG_CHANNEL_VOICE_ON");

    uint32 length = recvData.ReadBits(8);
    std::string channelName = recvData.ReadString(length);

    if (ChannelMgr* cMgr = ChannelMgr::forTeam(GetPlayer()->GetTeam()))
        if (Channel* channel = cMgr->GetChannel(channelName, GetPlayer()))
            channel->MakeVoiceOn(&recvData, GetPlayer()->GetGUID());
}

void WorldSession::HandleChannelVoiceOffOpcode(WorldPacket& recvData)
{
    TC_LOG_DEBUG("network", "WORLD: CMSG_CHANNEL_VOICE_OFF");

    uint32 length = recvData.ReadBits(8);
    std::string channelName = recvData.ReadString(length);

    if (ChannelMgr* cMgr = ChannelMgr::forTeam(GetPlayer()->GetTeam()))
        if (Channel* channel = cMgr->GetChannel(channelName, GetPlayer()))
            channel->MakeVoiceOff(&recvData, GetPlayer()->GetGUID());
}

void WorldSession::HandleSetActiveVoiceChannel(WorldPacket& recvData)
{
    TC_LOG_DEBUG("network", "WORLD: CMSG_SET_ACTIVE_VOICE_CHANNEL");

    uint32 channelId;
    std::string channelName;

    recvData >> channelId;
    uint32 length = recvData.ReadBits(8);
    channelName = recvData.ReadString(length);
}

