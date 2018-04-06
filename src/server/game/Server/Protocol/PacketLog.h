/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
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
 */

#ifndef TRINITY_PACKETLOG_H
#define TRINITY_PACKETLOG_H

#include "Common.h"
#include <ace/Singleton.h>
#include <mutex>

enum Direction
{
    CLIENT_TO_SERVER,
    SERVER_TO_CLIENT
};

class WorldPacket;

class PacketLog
{
    private:
        PacketLog();
        ~PacketLog();
        std::once_flag _initializeFlag;

    public:
        static PacketLog* instance();

        void Initialize();
        bool CanLogPacket() const { return (_file != NULL); }
        bool IsPktLogFormat() const { return (_pktLogType == 1); }
        void LogPacket(WorldPacket const& packet, Direction direction, std::string addr, uint16 port);

    private:
        FILE* _file;
        uint8 _pktLogType = 0;
};

#define sPacketLog PacketLog::instance()
#endif
