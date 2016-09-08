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


#include "Random.h"
#include "Common.h"
#include "Errors.h"
#include "SFMT.h"

typedef ACE_TSS<SFMTRand> SFMTRandTSS;
static SFMTRandTSS sfmtRand;

int32 irand(int32 min, int32 max)
{
    ASSERT(max >= min);
    return int32(sfmtRand->IRandom(min, max));
}

uint32 urand(uint32 min, uint32 max)
{
    ASSERT(max >= min);
    return sfmtRand->URandom(min, max);
}

uint32 urandms(uint32 min, uint32 max)
{
    ASSERT(max >= min);
    ASSERT(INT_MAX / IN_MILLISECONDS >= max);
    return sfmtRand->URandom(min * IN_MILLISECONDS, max * IN_MILLISECONDS);
}

float frand(float min, float max)
{
    ASSERT(max >= min);
    return float(sfmtRand->Random() * (max - min) + min);
}

Milliseconds randtime(Milliseconds const& min, Milliseconds const& max)
{
    long long diff = max.count() - min.count();
    ASSERT(diff >= 0);
    ASSERT(diff <= (uint32)-1);
    return min + Milliseconds(urand(0, diff));
}

uint32 rand32()
{
    return sfmtRand->BRandom();
}

double rand_norm()
{
    return sfmtRand->Random();
}

double rand_chance()
{
    return sfmtRand->Random() * 100.0;
}

bool rand_chance(uint8 percent)
{
    uint8 rol = urand(0, 100);
    return percent > rol ? true : false;
}

SFMTEngine& SFMTEngine::Instance()
{
    static SFMTEngine engine;
    return engine;
}
