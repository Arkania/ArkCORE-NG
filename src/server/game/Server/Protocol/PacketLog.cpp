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

#include "PacketLog.h"
#include "ByteBuffer.h"
#include "Config.h"
#include "Timer.h"
#include "World.h"
#include "WorldPacket.h"

#include <thread>

 // Packet logging structures in PKT 3.1 format
struct LogHeader
{
    char Signature[3];
    uint16 FormatVersion;
    uint8 SnifferId;
    uint32 Build;
    char Locale[4];
    uint8 SessionKey[40];
    uint32 SniffStartUnixtime;
    uint32 SniffStartTicks;
    uint32 OptionalDataSize;

    void WriteBinary(FILE* _file)
    {
        fwrite(&Signature, 1, 3, _file);
        fwrite(&FormatVersion, sizeof(uint16), 1, _file);
        fwrite(&SnifferId, sizeof(uint8), 1, _file);
        fwrite(&Build, sizeof(uint32), 1, _file);
        fwrite(&Locale, 4, 1, _file);
        fwrite(&SessionKey, sizeof(uint8), 40, _file);
        fwrite(&SniffStartUnixtime, sizeof(uint32), 1, _file);
        fwrite(&SniffStartTicks, sizeof(uint32), 1, _file);
        fwrite(&OptionalDataSize, sizeof(uint32), 1, _file);
    }
};

struct PacketHeader
{
    // used to uniquely identify a connection
    struct OptionalData
    {
        uint8 SocketIPBytes[16];
        uint32 SocketPort;
    };

    uint32 Direction;
    uint32 ConnectionId;
    uint32 ArrivalTicks;
    uint32 OptionalDataSize;
    uint32 DataSize;
    OptionalData OptionalData;
    uint32 Opcode;

    void WriteBinary(FILE* _file)
    {
        fwrite(&Direction, sizeof(uint32), 1, _file);
        fwrite(&ConnectionId, sizeof(uint32), 1, _file);
        fwrite(&ArrivalTicks, sizeof(uint32), 1, _file);
        fwrite(&OptionalDataSize, sizeof(uint32), 1, _file);
        fwrite(&DataSize, sizeof(uint32), 1, _file);
        fwrite(&OptionalData.SocketIPBytes, sizeof(uint8), 16, _file);
        fwrite(&OptionalData.SocketPort, sizeof(uint32), 1, _file);
        fwrite(&Opcode, sizeof(uint32), 1, _file);
    }
};

PacketLog::PacketLog() : _file(NULL), _pktLogType(0)
{
    std::call_once(_initializeFlag, &PacketLog::Initialize, this);
}

PacketLog::~PacketLog()
{
    if (_file)
        fclose(_file);

    _file = nullptr;
}

PacketLog* PacketLog::instance()
{
    static PacketLog instance;
    return &instance;
}

void PacketLog::Initialize()
{
    std::string logsDir = sConfigMgr->GetStringDefault("LogsDir", "");

    if (!logsDir.empty())
        if ((logsDir.at(logsDir.length() - 1) != '/') && (logsDir.at(logsDir.length() - 1) != '\\'))
            logsDir.push_back('/');

    std::string logname = sConfigMgr->GetStringDefault("PacketLogFile", "");
    if (std::size_t found = logname.find(".pkt"))
        _pktLogType = 1;

    if (!logname.empty())
        _file = fopen((logsDir + logname).c_str(), "wb");

    if (_file == NULL)
        perror("Open PacketLog: The following error occurred: ");

    if (IsPktLogFormat() && CanLogPacket())
    {
        LogHeader header;
        header.Signature[0] = 'P'; header.Signature[1] = 'K'; header.Signature[2] = 'T';
        header.FormatVersion = 0x0301;
        header.SnifferId = 'T';
        header.Build = 15595;
        int localeID = sConfigMgr->GetIntDefault("DBC.Locale", 0);
        std::string locale = localeNames[localeID];
        if (locale.size() == 4)
        {
            uint8_t* localeKey = GetBytes(locale);
            header.Locale[0] = localeKey[0]; header.Locale[1] = localeKey[1]; header.Locale[2] = localeKey[2]; header.Locale[3] = localeKey[3];
        }
        else
        {
            header.Locale[0] = 'e'; header.Locale[1] = 'n'; header.Locale[2] = 'U'; header.Locale[3] = 'S';
        }
        std::memset(header.SessionKey, 0, sizeof(header.SessionKey));
        header.SniffStartUnixtime = time(NULL);
        header.SniffStartTicks = getMSTime();
        header.OptionalDataSize = 0;
        header.WriteBinary(_file);
    }
}

void PacketLog::LogPacket(WorldPacket const& packet, Direction direction, std::string addr, uint16 port)
{
    if (IsPktLogFormat())
    {
        PacketHeader header;
        header.Direction = direction == CLIENT_TO_SERVER ? 0x47534d43 : 0x47534d53;
        header.ConnectionId = 0;
        header.ArrivalTicks = getMSTime();

        header.OptionalDataSize = sizeof(header.OptionalData);

        memset(header.OptionalData.SocketIPBytes, 0, sizeof(header.OptionalData.SocketIPBytes));
        uint8_t* bytes = GetBytes(addr);
        memcpy(header.OptionalData.SocketIPBytes, bytes, addr.size());

        header.OptionalData.SocketPort = port;
        header.DataSize = packet.size() + sizeof(header.Opcode);
        header.Opcode = packet.GetOpcode();

        header.WriteBinary(_file);
        if (!packet.empty())
            fwrite(packet.contents(), 1, packet.size(), _file);

        fflush(_file);
    }
    else
    {
        ByteBuffer data(4 + 4 + 4 + 1 + packet.size());
        data << int32(packet.GetOpcode());
        data << int32(packet.size());
        data << uint32(time(NULL));
        data << uint8(direction);

        for (uint32 i = 0; i < packet.size(); i++)
            data << packet[i];

        fwrite(data.contents(), 1, data.size(), _file);
        fflush(_file);
    }
}

