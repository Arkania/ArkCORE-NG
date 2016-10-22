/*
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
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

#include "ScriptPCH.h"
#include "Unit.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "ScriptedFollowerAI.h"
#include "Vehicle.h"
#include "GameObject.h"
#include "GameObjectAI.h"
#include "CreatureGroups.h"
#include "Transport.h"
#include "TransportMgr.h"

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Spell.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "MapManager.h"
#include "Map.h"
#include "MapReference.h"
#include "CreatureTextMgr.h"

enum eBattleForGilneas
{
    QUEST_PUSH_THEM_OUT = 24676,
    QUEST_THE_BATTLE_FOR_GILNEAS_CITY = 24904,

    NPC_KRENNAN_ARANAS = 38553,
    NPC_SISTER_ALMYRA = 38466,
    NPC_MYRIAM_SPELLWAKER = 38465,
    NPC_GILNEAN_MILITIA = 38221,
    NPC_PRINCE_LIAM_GREYMANE_BATTLE = 38218,
    NPC_PRINCE_LIAM_GREYMANE = 38474,
    NPC_LORNA_CROWLEY = 38426,
    NPC_LORD_DARIUS_CROWLEY = 38415,
    NPC_DAMAGED_CATAPULT = 38377,
    NPC_GOREROT = 38331,
    NPC_KING_GENN_GREYMANE = 38470,
    NPC_LADY_SYLVANAS_WINDRUNNER = 38469,
    NPC_SOULTETHERED_BANSHEE = 38473,
    NPC_FORSAKEN_CROSSBOWMAN = 38210,
    NPC_EMBERSTONE_CANNON = 38424,
    NPC_FREED_EMBERSTONE_VILLAGER = 38425,
    NPC_DARK_RANGER_ELITE = 38464,
    NPC_VILE_ABOMINATION = 38420,
    NPC_WORGEN_WARRIER = 38348,
    NPC_LEADER_GUID = 99992,

    SPELL_GILNEAS_MILITIA_SHOOT = 6660,
    SPELL_FORSAKEN_CROSSBOW_SHOOT = 6660,
    SPELL_KNOCKBACK = 68683,
    SPELL_CLEAVE = 15496,

    SOUND_GILNEAN_MILITIA = 22584,

    ACTION_START_EVENT = 101,
    ACTION_EVENT_RESET_TIMER,
    ACTION_SEND_DATA,
    ACTION_INITIALIZE_DONE,
    ACTION_CHECK_READY_FOR_BATTLE,
    ACTION_START_MOTIVATION,
    ACTION_MOTIVATION_DONE,
    ACTION_MOVE_TO_WAVE_POSION_1,
    ACTION_MOVE_TO_WAVE_POSION_2,
    ACTION_MOVE_TO_WAVE_POSION_3,
    ACTION_MOVE_TO_WAVE_POSION_4,
    ACTION_MOVE_TO_WAVE_POSION_5,
    ACTION_MOVE_TO_WAVE_POSION_6,
    ACTION_MOVE_TO_WAVE_POSION_7,
    ACTION_MOVE_TO_MEET_POINT4,
    ACTION_LIAM_TALK_10,
    ACTION_KING_TALK_2,
    ACTION_LIAM_ARRIVED,
    ACTION_MYRIAM_ARRIVED,
    ACTION_LORNA_ARRIVED,
    ACTION_DARIUS_ARRIVED,
    ACTION_GENN_ARRIVED,
    ACTION_SYLVANAS_ARRIVED,
    ACTION_SYLVANAS_HAS_ENOUGH,
    ACTION_AIM_AT_KING,
    ACTION_SHOOT_AT_KING,
    ACTION_LIAM_IS_DEATH,
    ACTION_QUEST_REWARDED,

    EVENT_GLOBAL_RESET = 201,
    EVENT_CHECK_PLAYER_FOR_PHASE,
    EVENT_CHECK_PLAYER_FOR_INVITE,
    EVENT_PLAYER_INVITE_COOLDOWN,
    EVENT_INITIALISE,
    EVENT_RANDOM_TEXT,
    EVENT_LIAM_TALK_9,
    EVENT_FORSAKEN_CROSSBOW_SHOOT,
    EVENT_FORSAKEN_KNOCKBACK,
    EVENT_START_LIAMS_FIRST_ANIM,
    EVENT_MOTIVATION_0,
    EVENT_MOTIVATION_1,
    EVENT_MOTIVATION_2,
    EVENT_MOTIVATION_3,
    EVENT_MOTIVATION_4,
    EVENT_MOTIVATION_5,
    EVENT_MOTIVATION_6,
    EVENT_MOTIVATION_DONE,
    EVENT_MOVE_WAVE,
    EVENT_FIGHT_WAVE,
    EVENT_SYNC_BEFORE_NEXT_WAVE,
    EVENT_SYLVANAS_HAS_ENOUGH,
    EVENT_DARIUS_TALK_2,
    EVENT_CHECK_FOR_TIMER,
    EVENT_SYLVANAS_ATTACK1,
    EVENT_SYLVANAS_ATTACK2,
    EVENT_SYLVANAS_ATTACK3,
    EVENT_SYLVANAS_ATTACK4,
    EVENT_LIAM_IS_DEATH,
    EVENT_LIAM_DEATH_TALK1,
    EVENT_LIAM_DEATH_TALK2,

    DATA_IS_BATTLE_STARTED = 99991,
};

// 38221 -- gilneas militia... first 3 groups
Position const SpawnPosGroup1[19] =
{
    {-1413.24f, 1251.31f, 36.5112f, 1.44862f},
    {-1412.06f, 1229.05f, 35.3626f, 1.90241f},
    {-1411.20f, 1235.85f, 35.6430f, 1.85005f},
    {-1410.05f, 1237.84f, 35.6059f, 1.85005f},
    {-1410.04f, 1254.17f, 36.5112f, 1.62316f},
    {-1409.91f, 1243.75f, 36.5112f, 1.60570f},
    {-1409.25f, 1240.33f, 35.9492f, 1.62316f},
    {-1409.05f, 1246.82f, 36.5112f, 1.65806f},
    {-1408.33f, 1230.89f, 35.6430f, 1.88496f},
    {-1408.26f, 1247.68f, 36.5112f, 1.69297f},
    {-1408.00f, 1238.71f, 35.5949f, 1.90241f},
    {-1407.86f, 1228.30f, 35.6163f, 1.86750f},
    {-1407.67f, 1240.97f, 36.0177f, 1.90241f},
    {-1407.21f, 1224.88f, 35.4307f, 1.86750f},
    {-1407.16f, 1253.53f, 36.5112f, 1.79769f},
    {-1406.71f, 1230.29f, 35.6430f, 1.86750f},
    {-1406.70f, 1234.23f, 35.6430f, 1.88496f},
    {-1406.45f, 1249.19f, 36.5112f, 1.78024f},
    {-1406.44f, 1243.52f, 36.5112f, 1.72788f}
};

// 38221 -- gilneas militia... first 3 groups
Position const SpawnPosGroup2[19] =
{
    {-1406.21f, 1232.23f, 35.6430f, 1.90241f},
    {-1406.07f, 1241.32f, 36.0042f, 1.72788f},
    {-1406.05f, 1226.87f, 35.6424f, 1.86750f},
    {-1405.36f, 1246.29f, 36.5112f, 1.79769f},
    {-1405.12f, 1238.07f, 35.6430f, 1.95477f},
    {-1404.93f, 1252.91f, 36.5112f, 1.90241f},
    {-1404.41f, 1233.74f, 35.6430f, 1.93731f},
    {-1404.40f, 1228.07f, 35.6430f, 1.90241f},
    {-1404.10f, 1231.50f, 35.6430f, 1.93731f},
    {-1404.04f, 1248.17f, 36.5112f, 1.86750f},
    {-1404.02f, 1225.87f, 35.6430f, 1.90241f},
    {-1403.96f, 1240.07f, 35.6430f, 1.83260f},
    {-1403.25f, 1235.73f, 35.6430f, 1.83260f},
    {-1403.24f, 1230.06f, 35.6430f, 1.90241f},
    {-1402.94f, 1242.49f, 36.1134f, 1.85005f},
    {-1402.87f, 1227.86f, 35.6430f, 1.90241f},
    {-1402.53f, 1238.53f, 35.6430f, 1.83260f},
    {-1402.50f, 1254.84f, 36.5112f, 2.05949f},
    {-1402.42f, 1250.51f, 36.5112f, 1.97222f}
};

// 38221 -- gilneas militia... first 3 groups
Position const SpawnPosGroup3[19] =
{
    {-1402.16f, 1232.82f, 35.6430f, 1.83260f},
    {-1402.03f, 1236.74f, 35.6430f, 1.97222f},
    {-1401.30f, 1231.27f, 35.6430f, 1.97222f},
    {-1401.26f, 1239.94f, 35.6430f, 1.83260f},
    {-1400.90f, 1227.03f, 35.6430f, 1.95477f},
    {-1400.84f, 1234.70f, 35.6430f, 1.83260f},
    {-1400.60f, 1246.62f, 36.5112f, 1.97222f},
    {-1400.49f, 1223.07f, 35.6430f, 1.93731f},
    {-1399.75f, 1229.02f, 35.6430f, 1.83260f},
    {-1399.33f, 1225.06f, 35.6430f, 1.83260f},
    {-1399.30f, 1241.37f, 35.6430f, 1.83260f},
    {-1399.23f, 1237.05f, 35.6430f, 1.83260f},
    {-1398.85f, 1239.30f, 35.6430f, 2.02458f},
    {-1398.56f, 1231.17f, 35.6430f, 2.00713f},
    {-1398.25f, 1243.69f, 36.1213f, 2.00713f},
    {-1397.41f, 1233.16f, 35.6430f, 1.83260f},
    {-1396.73f, 1237.27f, 35.6430f, 2.00713f},
    {-1396.21f, 1228.23f, 35.6430f, 2.00713f},
    {-1395.05f, 1230.22f, 35.6430f, 1.83260f}
};

// 38210 -- Forsaken Crossbowman marktplatz
Position const SpawnPosForsakenCrossbowman[32] =
{
    {-1561.44f, 1361.97f, 35.6543f, 5.41052f},
    {-1560.82f, 1325.08f, 35.6393f, 0.34906f},
    {-1560.14f, 1320.97f, 35.6393f, 0.34906f},
    {-1554.46f, 1420.46f, 35.6393f, 5.41052f},
    {-1547.94f, 1424.68f, 35.6393f, 5.41052f},
    {-1541.36f, 1427.38f, 35.6393f, 5.41052f},
    {-1537.89f, 1406.33f, 35.6393f, 5.41052f},
    {-1536.05f, 1429.70f, 35.6393f, 5.41052f},
    {-1529.61f, 1402.51f, 35.6393f, 5.41052f},
    {-1526.30f, 1406.17f, 35.6393f, 5.41052f},
    {-1524.48f, 1431.05f, 35.6393f, 5.41052f},
    {-1519.17f, 1431.58f, 35.6393f, 5.41052f},
    {-1513.66f, 1431.72f, 35.6393f, 5.41052f},
    {-1509.46f, 1432.15f, 35.6393f, 5.41052f},
    {-1507.16f, 1375.58f, 35.6392f, 5.41052f},
    {-1506.71f, 1380.20f, 35.6393f, 5.41052f},
    {-1505.66f, 1390.99f, 35.6393f, 0.00001f},
    {-1505.25f, 1394.88f, 35.6393f, 0.00001f},
    {-1504.13f, 1398.67f, 35.6392f, 0.00001f},
    {-1503.84f, 1378.14f, 35.6393f, 5.41052f},
    {-1497.26f, 1429.51f, 35.6392f, 5.41052f},
    {-1496.61f, 1424.05f, 35.6392f, 5.41052f},
    {-1492.65f, 1430.91f, 35.6392f, 5.41052f},
    {-1479.81f, 1426.92f, 35.6392f, 5.56760f},
    {-1475.77f, 1430.84f, 35.6392f, 5.42797f},
    {-1470.96f, 1435.55f, 35.8477f, 5.28835f},
    {-1466.62f, 1393.85f, 35.6392f, 5.48033f},
    {-1464.05f, 1397.30f, 35.6392f, 5.46288f},
    {-1461.44f, 1400.33f, 35.6392f, 5.41052f},
    {-1443.30f, 1424.79f, 35.6392f, 5.41052f},
    {-1443.06f, 1428.06f, 35.6392f, 5.41052f},
    {-1440.31f, 1425.90f, 35.6393f, 5.41052f}
};

// 38424 -- Emberstone Cannon
Position const SpawnPosEmberstoneCannon[3] =
{
    {-1542.78f, 1287.52f, 6.85945f, 3.44634f},
    {-1542.28f, 1291.05f, 6.03397f, 3.49002f},
    {-1540.76f, 1283.70f, 6.14954f, 3.34331f}
};

// 38425 -- Freed Emberstone Villager
Position const SpawnPosEmberstoneVillager[15] =
{
    {-1547.77f, 1284.83f, 10.7515f, 3.44930f},
    {-1547.70f, 1291.23f, 10.1994f, 3.28122f},
    {-1547.28f, 1289.11f, 9.42849f, 3.26377f},
    {-1546.86f, 1289.97f, 9.44430f, 3.28122f},
    {-1546.72f, 1282.63f, 9.54710f, 3.21141f},
    {-1546.19f, 1288.76f, 9.29824f, 3.50505f},
    {-1545.92f, 1283.59f, 9.67451f, 3.32181f},
    {-1545.91f, 1282.17f, 8.97509f, 3.21141f},
    {-1544.19f, 1281.59f, 8.35464f, 3.40339f},
    {-1544.14f, 1284.08f, 8.41506f, 3.15950f},
    {-1543.17f, 1288.96f, 7.03947f, 3.27965f},
    {-1542.89f, 1287.09f, 6.95761f, 3.24631f},
    {-1542.79f, 1285.79f, 7.22325f, 3.24631f},
    {-1542.17f, 1290.87f, 6.02407f, 3.28122f},
    {-1540.52f, 1284.16f, 6.02382f, 3.22886f}
};

// 38464 -- Dark Ranger Elite 
Position const SpawnPosDarkRangerElite[2] =
{
    {-1581.59f, 1304.19f, 36.0253f, 0.22827f},
    {-1555.64f, 1358.93f, 35.6108f, 1.57588f}
};

// 38420 -- Vile Abomination
Position const SpawnPosVileAbomination[20] =
{
    {-1745.71f, 1327.94f, 19.8734f, 0.00001f},
    {-1736.72f, 1299.51f, 20.3591f, 0.95369f},
    {-1729.96f, 1331.99f, 20.3535f, 4.70341f},
    {-1718.06f, 1312.01f, 19.8657f, 0.00001f},
    {-1703.58f, 1309.32f, 19.8657f, 0.00001f},
    {-1691.23f, 1323.50f, 18.3880f, 4.89080f},
    {-1691.18f, 1299.36f, 20.3675f, 0.00001f},
    {-1689.80f, 1328.62f, 16.1862f, 4.81711f},
    {-1686.37f, 1325.34f, 17.3616f, 4.81711f},
    {-1675.90f, 1339.06f, 15.2182f, 0.00001f},
    {-1666.57f, 1305.68f, 19.8657f, 0.00001f},
    {-1664.23f, 1344.06f, 15.2182f, 0.00001f},
    {-1653.57f, 1302.92f, 19.8657f, 0.00001f},
    {-1642.65f, 1270.39f, 20.3665f, 0.00001f},
    {-1637.88f, 1306.15f, 19.7463f, 0.00001f},
    {-1635.35f, 1336.59f, 19.9530f, 0.00001f},
    {-1635.26f, 1317.65f, 19.7844f, 0.00001f},
    {-1633.12f, 1368.22f, 20.1907f, 0.00001f},
    {-1630.97f, 1261.69f, 20.3662f, 0.00001f},
    {-1627.87f, 1287.66f, 20.3675f, 0.00001f}
};

// 38210 -- forsaken crossbow militia area
Position const SpawnPosForsakenCrossbowMilitiaArea[34] =
{
    {-1808.76f, 1484.37f, 19.4685f, 5.41052f},
    {-1808.48f, 1442.73f, 19.2855f, 5.41052f},
    {-1807.36f, 1434.65f, 19.4926f, 5.41052f},
    {-1805.94f, 1509.33f, 19.8948f, 5.41052f},
    {-1804.54f, 1439.42f, 19.3655f, 5.41052f},
    {-1804.03f, 1449.68f, 19.0509f, 5.41052f},
    {-1803.73f, 1485.10f, 19.6351f, 5.41052f},
    {-1803.26f, 1513.03f, 19.8657f, 5.41052f},
    {-1800.83f, 1484.45f, 19.7930f, 5.41052f},
    {-1800.79f, 1510.63f, 19.8657f, 5.41052f},
    {-1799.60f, 1517.74f, 19.8657f, 5.41052f},
    {-1798.73f, 1510.62f, 19.8657f, 5.41052f},
    {-1789.39f, 1592.31f, 20.5891f, 5.41052f},
    {-1785.45f, 1598.71f, 20.5657f, 5.41052f},
    {-1785.09f, 1590.39f, 20.5891f, 5.41052f},
    {-1780.18f, 1365.37f, 19.9203f, 5.41052f},
    {-1777.90f, 1366.55f, 19.8959f, 5.41052f},
    {-1776.38f, 1362.18f, 19.6843f, 5.41052f},
    {-1775.68f, 1364.17f, 19.7611f, 5.41052f},
    {-1772.64f, 1361.05f, 19.7172f, 5.41052f},
    {-1763.98f, 1354.37f, 19.7242f, 5.41052f},
    {-1761.43f, 1353.14f, 19.6473f, 4.17134f},
    {-1759.97f, 1358.37f, 19.7832f, 5.41052f},
    {-1759.26f, 1352.12f, 19.7196f, 5.41052f},
    {-1756.69f, 1357.73f, 19.9116f, 5.41052f},
    {-1743.69f, 1384.11f, 19.5636f, 5.41052f},
    {-1741.09f, 1382.12f, 19.6689f, 5.41052f},
    {-1739.17f, 1388.20f, 19.8526f, 5.41052f},
    {-1739.12f, 1380.52f, 19.8633f, 5.41052f},
    {-1736.66f, 1385.70f, 19.8835f, 5.41052f},
    {-1734.02f, 1383.23f, 19.8769f, 5.41052f},
    {-1721.44f, 1404.65f, 21.7520f, 5.41052f},
    {-1715.63f, 1399.68f, 21.6268f, 5.41052f},
    {-1713.13f, 1396.55f, 21.7267f, 5.41052f}
};

// 38331 -- Gorerot
Position const SpawnPosGorerot[1] =
{
    {-1703.10f, 1419.87f, 21.9268f, 3.89208f}
};

// 38377 -- damaged catapult militia area
Position const SpawnPosDamagedCatapult[5] =
{
    {-1793.15f, 1325.93f, 19.8905f, 4.66003f},
    {-1785.23f, 1371.23f, 19.9022f, 0.00001f},
    {-1765.35f, 1398.93f, 19.7152f, 5.21853f},
    {-1712.07f, 1440.97f, 21.7520f, 4.64258f},
    {-1683.16f, 1401.89f, 21.7520f, 3.01942f}
};

// 38473 -- Soultethered Banshee
Position const SpawnPosSoultetheredBanshee[3] =
{
    {-1683.02f, 1602.66f, 20.5689f, 1.55334f},
    {-1674.49f, 1607.05f, 20.5689f, 2.30383f},
    {-1670.25f, 1617.54f, 20.5728f, 3.31613f}
};

// 38221 -- gilneas militia... group 4f,  leader is king greymane
Position const SpawnPosGroup4[25] =
{
    {-1805.66f, 1711.51f, 22.158f, 5.82022f},
    {-1804.46f, 1713.33f, 22.158f, 5.73306f},
    {-1804.10f, 1711.03f, 22.158f, 5.80878f},
    {-1803.97f, 1712.53f, 22.158f, 5.75091f},
    {-1803.89f, 1709.89f, 22.158f, 5.84896f},
    {-1802.94f, 1713.07f, 22.158f, 5.70858f},
    {-1802.32f, 1711.26f, 22.158f, 5.76240f},
    {-1784.48f, 1698.85f, 22.158f, 5.53749f},
    {-1783.25f, 1700.32f, 22.158f, 5.73320f},
    {-1781.23f, 1694.91f, 22.158f, 5.55745f},
    {-1766.98f, 1685.82f, 22.158f, 5.60248f},
    {-1765.97f, 1682.72f, 22.158f, 5.71149f},
    {-1765.95f, 1684.39f, 22.158f, 5.58828f},
    {-1765.48f, 1683.67f, 22.158f, 5.62265f},
    {-1765.26f, 1680.24f, 22.158f, 5.59896f},
    {-1764.69f, 1681.30f, 22.158f, 5.63152f},
    {-1763.39f, 1682.29f, 22.158f, 5.68689f},
    {-1763.05f, 1680.50f, 22.158f, 5.65293f},
    {-1762.94f, 1679.24f, 22.158f, 5.67851f},
    {-1762.88f, 1682.50f, 22.158f, 5.65235f},
    {-1762.85f, 1685.36f, 22.158f, 5.65131f},
    {-1762.16f, 1683.58f, 22.158f, 5.60894f},
    {-1762.15f, 1677.84f, 22.158f, 5.66141f},
    {-1761.58f, 1680.67f, 22.158f, 5.50141f},
    {-1761.40f, 1684.49f, 22.158f, 5.64862f}
};

// 38348 -- group5, leader is lord crowley
Position const SpawnPosGroup5[15] =
{
    {-1787.08f, 1323.25f, 19.8182f, 0.573106f},
    {-1771.52f, 1341.18f, 19.8999f, 0.598678f},
    {-1768.31f, 1342.82f, 19.7964f, 0.645975f},
    {-1775.48f, 1338.13f, 19.8701f, 0.662500f},
    {-1774.56f, 1337.28f, 19.8836f, 0.685529f},
    {-1776.67f, 1335.78f, 19.9317f, 0.698037f},
    {-1770.61f, 1340.16f, 19.9151f, 0.702293f},
    {-1776.28f, 1336.33f, 19.9914f, 0.713269f},
    {-1770.26f, 1342.08f, 19.9424f, 0.715889f},
    {-1776.45f, 1337.74f, 19.9649f, 0.717392f},
    {-1774.06f, 1336.29f, 19.9575f, 0.732912f},
    {-1776.26f, 1336.92f, 19.9147f, 0.737243f},
    {-1775.98f, 1338.47f, 19.7669f, 0.742460f},
    {-1788.63f, 1325.67f, 19.8337f, 0.758611f},
    {-1771.14f, 1342.95f, 19.8481f, 0.760219f}
};

// all groups running to the meeting point near sylvanas
Position const Wave6Pos[21] =
{
    {-1727.384f, 1394.064f, 21.67019f, 4.08833f},
    {-1742.488f, 1380.739f, 19.62942f, 3.864493f},
    {-1765.707f, 1384.909f, 19.66496f, 3.000555f},
    {-1790.892f, 1377.563f, 19.7612f, 3.393254f},
    {-1800.233f, 1406.457f, 19.7627f, 1.904924f},
    {-1803.212f, 1429.975f, 19.65882f, 1.696794f},
    {-1804.345f, 1438.919f, 19.32841f, 1.696794f},
    {-1804.805f, 1450.515f, 18.95232f, 1.6104f},
    {-1804.61f, 1473.499f, 19.36089f, 1.606473f},
    {-1804.593f, 1483.752f, 19.48337f, 1.476882f},
    {-1803.886f, 1501.683f, 19.7777f, 1.512225f},
    {-1803.479f, 1508.616f, 19.78121f, 1.512225f},
    {-1800.368f, 1535.57f, 20.5123f, 1.45332f},
    {-1799.467f, 1541.466f, 22.09082f, 1.421904f},
    {-1797.534f, 1558.138f, 22.28905f, 1.390488f},
    {-1796.441f, 1566.551f, 20.57414f, 1.441539f},
    {-1791.938f, 1580.366f, 20.505f, 1.241262f},
    {-1787.521f, 1591.715f, 20.505f, 1.213773f},
    {-1775.408f, 1611.678f, 20.48242f, 0.997789f},
    {-1761.054f, 1628.766f, 20.42564f, 0.872125f},
    {-1750.531f, 1640.615f, 20.47372f, 0.844636f}
};

Position const SAWave1Pos[9] =
{
    { -1437.389526f, 1393.817383f, 35.555603f, 1.539162f },
    { -1437.941650f, 1404.163208f, 35.555603f, 1.613774f },
    { -1438.317627f, 1412.905151f, 35.555603f, 1.613774f },
    { -1447.051880f, 1417.736816f, 35.555603f, 2.532691f },
    { -1454.315796f, 1423.748657f, 35.555603f, 2.450224f },
    { -1461.147217f, 1428.819946f, 35.555603f, 2.516983f },
    { -1469.281494f, 1430.770996f, 35.555603f, 2.909682f },
    { -1477.451416f, 1432.033936f, 35.555603f, 2.988222f },
    { -1489.788818f, 1433.395752f, 35.667927f, 3.086396f }
};

Position const SAWave2Pos[12] =
{
    { -1500.655762f, 1431.993408f, 35.555920f, 3.227764f },
    { -1510.405518f, 1431.151978f, 35.555920f, 3.223837f },
    { -1518.777100f, 1430.461914f, 35.555920f, 3.223837f },
    { -1529.313232f, 1428.540039f, 35.555920f, 3.322012f },
    { -1538.028564f, 1424.058594f, 35.555920f, 3.616536f },
    { -1549.109619f, 1413.449829f, 35.555920f, 4.091701f },
    { -1550.101563f, 1402.547119f, 35.555920f, 4.617918f },
    { -1552.053833f, 1387.908203f, 35.567951f, 4.594353f },
    { -1553.567261f, 1375.145630f, 35.621307f, 4.594353f },
    { -1556.383667f, 1365.015869f, 35.597328f, 4.441201f },
    { -1560.907715f, 1350.764893f, 35.556774f, 4.421566f },
    { -1564.754028f, 1337.536743f, 35.652534f, 4.429420f }
};

Position const SAWave3Pos[4] =
{
    { -1563.287842f, 1348.462402f, 35.556309f, 4.358731f },
    { -1573.182617f, 1320.758911f, 35.556374f, 4.331242f },
    { -1575.922241f, 1320.336670f, 35.662712f, 3.294517f },
    { -1604.168945f, 1317.651855f, 18.273659f, 3.235612f }
};

Position const SAWave4Pos[23] =
{
    { -1621.967f, 1313.734f, 19.98523f, 3.168626f },
    { -1630.338f, 1313.902f, 19.94785f, 3.094013f },
    { -1633.865f, 1319.981f, 19.82338f, 2.096557f },
    { -1633.993f, 1327.456f, 19.99536f, 1.597829f },
    { -1634.571f, 1340.967f, 20.01138f, 1.613537f },
    { -1634.333f, 1355.469f, 20.0053f, 1.550705f },
    { -1634.165f, 1363.839f, 20.01123f, 1.550705f },
    { -1633.091f, 1339.059f, 20.14444f, 4.664808f },
    { -1641.063f, 1338.686f, 19.85237f, 3.18826f },
    { -1652.922f, 1338.133f, 15.13503f, 3.18826f },
    { -1661.747f, 1338.774f, 15.13503f, 3.066523f },
    { -1670.179f, 1339.409f, 15.13503f, 3.046888f },
    { -1682.22f, 1340.552f, 15.13503f, 3.046888f },
    { -1688.262f, 1333.935f, 15.13503f, 3.969731f },
    { -1693.281f, 1341.391f, 15.13503f, 2.163315f },
    { -1707.232f, 1348.489f, 19.89664f, 2.677751f },
    { -1723.597f, 1356.516f, 19.79759f, 2.685605f },
    { -1739.334f, 1367.332f, 19.92152f, 2.536379f },
    { -1741.163f, 1376.361f, 19.93815f, 1.770616f },
    { -1738.806f, 1383.416f, 19.74238f, 1.248326f },
    { -1731.731f, 1389.446f, 20.34878f, 0.745671f },
    { -1725.584f, 1395.212f, 21.66887f, 0.753525f },
    { -1715.573f, 1397.528f, 21.60112f, 0.227307f }
};

Position const SAWave5Pos[2] =
{
    { -1715.351f, 1394.578f, 21.66827f, 1.855860f },
    { -1693.197f, 1417.967f, 21.65804f, 0.843865f }
};

Position const SAWave7Pos[4] =
{
    { -1742.922f, 1649.848f, 20.47622f, 0.821074f },
    { -1715.093f, 1646.737f, 20.48619f, 6.110734f },
    { -1689.912f, 1639.731f, 20.48837f, 6.043974f },
    { -1673.071f, 1626.676f, 20.48974f, 5.623789f }
};

Position const LGWave1Pos[8] =
{
    { -1437.231934f, 1371.772461f, 35.555882f, 1.711943f },
    { -1443.534302f, 1384.691772f, 35.555882f, 2.092861f },
    { -1449.132690f, 1392.529663f, 35.555882f, 2.191036f },
    { -1458.036621f, 1394.339233f, 35.555882f, 2.941092f },
    { -1471.946533f, 1396.155151f, 35.555882f, 3.011778f },
    { -1486.640137f, 1396.526489f, 35.556095f, 3.125660f },
    { -1498.510620f, 1396.715576f, 35.576904f, 3.125660f },
    { -1501.070557f, 1389.945435f, 35.556374f, 4.350883f }
};

Position const LGWave2Pos[12] =
{
    { -1507.374756f, 1393.394043f, 35.556316f, 2.980361f },
    { -1517.214600f, 1397.292480f, 35.556316f, 2.764377f },
    { -1529.041870f, 1399.841675f, 35.556122f, 2.929310f },
    { -1542.405151f, 1401.980225f, 35.556122f, 3.600830f },
    { -1555.046631f, 1391.780396f, 35.589314f, 3.946405f },
    { -1551.008301f, 1376.774292f, 35.564800f, 4.967419f },
    { -1551.504395f, 1370.156860f, 35.577396f, 4.688603f },
    { -1552.440918f, 1354.336548f, 35.556656f, 4.645407f },
    { -1555.453125f, 1340.044067f, 35.556656f, 4.409791f },
    { -1561.170898f, 1328.073853f, 35.556656f, 4.193810f },
    { -1567.528931f, 1321.278809f, 35.556656f, 4.072073f },
    { -1573.618164f, 1313.105835f, 35.556656f, 4.072073f }
};

Position const LGWave3Pos[4] =
{
    { -1566.759155f, 1320.791504f, 35.556194f, 3.467305f },
    { -1575.836304f, 1318.078857f, 35.663509f, 3.443743f },
    { -1603.772461f, 1314.180420f, 18.277277f, 3.290590f },
    { -1613.415894f, 1312.478149f, 18.646879f, 3.274882f }
};

Position const LGWave4Pos[23] =
{
    { -1622.458130f, 1309.644043f, 20.090324f, 3.085264f },
    { -1630.291016f, 1311.815063f, 19.863869f, 2.959601f },
    { -1642.250244f, 1305.322388f, 19.662914f, 3.638970f },
    { -1652.736206f, 1305.295410f, 19.782557f, 3.136315f },
    { -1664.390625f, 1305.402710f, 19.782516f, 3.132388f },
    { -1676.200439f, 1308.069946f, 19.782516f, 2.951747f },
    { -1687.311890f, 1306.665527f, 19.782223f, 3.269833f },
    { -1692.100464f, 1311.875122f, 19.782223f, 1.353461f },
    { -1697.901733f, 1309.454712f, 19.782223f, 3.536869f },
    { -1711.723389f, 1311.409180f, 19.782347f, 3.034214f },
    { -1728.630249f, 1312.776245f, 19.782347f, 3.281614f },
    { -1731.254883f, 1322.795166f, 20.020033f, 1.761868f },
    { -1743.847900f, 1320.180908f, 19.779135f, 3.328738f },
    { -1752.967773f, 1333.730469f, 19.856970f, 2.146714f },
    { -1761.392578f, 1345.036499f, 19.662756f, 2.178130f },
    { -1762.698853f, 1359.164917f, 19.658524f, 1.706890f },
    { -1776.246094f, 1358.450684f, 19.688379f, 3.167731f },
    { -1759.055786f, 1364.855225f, 19.842024f, 0.359932f },
    { -1747.111694f, 1374.475952f, 19.906626f, 0.670165f },
    { -1741.230835f, 1379.986694f, 19.690134f, 0.748704f },
    { -1733.577148f, 1387.154541f, 19.808998f, 0.752631f },
    { -1727.756470f, 1392.489380f, 21.367025f, 0.752630f },
    { -1720.682617f, 1399.942993f, 21.664991f, 0.811535f }
};

Position const LGWave5Pos[2] =
{
    { -1720.182617f, 1399.842993f, 21.664991f, 0.811535f },
    { -1702.655f, 1407.955f, 21.6687f, 0.690712f }
};

Position const LGWave7Pos[3] =
{
    { -1743.057f, 1649.876f, 20.47626f, 0.89176f },
    { -1743.583f, 1660.951f, 20.48028f, 1.618254f },
    { -1776.187f, 1690.803f, 22.15823f, 2.372236f },
};

Position  const MSWave1Pos[8] =
{
    { -1438.375122f, 1357.833984f, 35.555393f, 2.827223f },
    { -1450.322998f, 1356.605225f, 35.555393f, 3.263119f },
    { -1464.221680f, 1353.181885f, 35.555931f, 3.388775f },
    { -1478.260376f, 1351.074341f, 35.555931f, 3.290600f },
    { -1491.284058f, 1348.592896f, 35.555931f, 3.329870f },
    { -1502.223022f, 1347.533447f, 35.555931f, 3.121739f },
    { -1503.380859f, 1362.383057f, 35.555931f, 1.660898f },
    { -1503.456055f, 1372.238770f, 35.555931f, 1.578432f }
};

Position const MSWave2Pos[10] =
{
    { -1503.550049f, 1367.337036f, 35.556229f, 4.727871f },
    { -1504.166138f, 1356.396729f, 35.556229f, 4.594356f },
    { -1504.506592f, 1347.779419f, 35.556229f, 4.672894f },
    { -1511.895508f, 1341.676025f, 35.556229f, 3.860008f },
    { -1519.750366f, 1335.448242f, 35.556229f, 3.722564f },
    { -1526.749634f, 1333.446167f, 35.556229f, 3.424112f },
    { -1533.222656f, 1331.539551f, 35.556229f, 3.428039f },
    { -1541.016724f, 1329.213257f, 35.556229f, 3.420185f },
    { -1547.694580f, 1327.309448f, 35.556229f, 3.420185f },
    { -1555.790405f, 1324.435913f, 35.556229f, 3.428039f },
};

Position const MSWave3Pos[3] =
{
    { -1566.918823f, 1317.117554f, 35.555355f, 3.251321f },
    { -1575.076172f, 1315.721191f, 35.666946f, 3.310225f },
    { -1602.897461f, 1311.002197f, 18.551262f, 3.384838f }
};

Position const MSWave4Pos[29] =
{
    { -1623.349f, 1306.457f, 20.1988f, 3.471806f },
    { -1628.798f, 1293.628f, 20.28483f, 4.830544f },
    { -1628.207f, 1280.061f, 20.28483f, 4.335746f },
    { -1634.251f, 1269.699f, 20.28329f, 4.202227f },
    { -1627.269f, 1283.753f, 20.28329f, 1.139174f },
    { -1631.366f, 1303.13f, 19.66328f, 3.145867f },
    { -1631.954f, 1304.51f, 19.66319f, 1.75098f },
    { -1645.34f, 1302.396f, 19.78257f, 3.298215f },
    { -1655.134f, 1301.591f, 19.78257f, 3.133281f },
    { -1666.661f, 1302.875f, 19.78257f, 2.976202f },
    { -1676.752f, 1307.861f, 19.78244f, 2.838757f },
    { -1687.291f, 1305.11f, 19.78245f, 3.400317f },
    { -1698.581f, 1305.802f, 19.78245f, 3.074377f },
    { -1708.548f, 1308.185f, 19.78245f, 2.905516f },
    { -1723.52f, 1309.143f, 19.78354f, 2.842684f },
    { -1729.046f, 1311.734f, 19.78354f, 2.705239f },
    { -1741.262f, 1318.574f, 19.78354f, 2.630626f },
    { -1746.946f, 1323.472f, 19.74223f, 2.43035f },
    { -1753.424f, 1330.944f, 19.80925f, 2.285051f },
    { -1760.75f, 1340.322f, 19.85269f, 2.234f },
    { -1766.275f, 1348.886f, 19.52534f, 2.143679f },
    { -1770.323f, 1356.717f, 19.67949f, 2.618846f },
    { -1777.519f, 1361.419f, 19.55937f, 2.571722f },
    { -1765.208f, 1359.214f, 19.76929f, 6.157064f },
    { -1755.574f, 1367.972f, 20.27488f, 0.737816f },
    { -1745.178f, 1377.445f, 19.87417f, 0.741743f },
    { -1734.951f, 1386.964f, 19.79792f, 0.749597f },
    { -1726.138f, 1395.168f, 21.66857f, 0.749597f },
    { -1726.2f, 1403.484f, 21.66857f, 1.578192f }
};

Position const MSWave5Pos[2] =
{
    { -1727.321f, 1414.810f, 21.66901f, 6.081301f },
    { -1715.602f, 1419.07f, 21.66894f, 5.980364f }
};

Position const MSWave7Pos[4] =
{
    { -1740.469f, 1648.645f, 20.47899f, 0.573681f },
    { -1729.113f, 1644.52f, 20.50016f, 5.930099f },
    { -1706.292f, 1622.626f, 20.48796f, 5.541332f },
    { -1692.687f, 1602.029f, 20.5824f, 0.177053f }
};

Position const LCWave3Pos[10] =
{
    { -1549.720093f, 1285.846191f, 12.247921f, 3.246603f },
    { -1581.160889f, 1277.640625f, 35.874260f, 3.450807f },
    { -1588.081787f, 1278.586304f, 35.880508f, 2.944225f },
    { -1589.878662f, 1292.484619f, 35.973133f, 1.699368f },
    { -1567.875610f, 1307.029663f, 35.880470f, 0.584102f },
    { -1569.379272f, 1317.379028f, 35.556068f, 1.715076f },
    { -1573.143433f, 1316.830078f, 35.556297f, 3.164136f },
    { -1575.836304f, 1318.078857f, 35.663509f, 3.443743f },
    { -1603.772461f, 1314.180420f, 18.277277f, 3.290590f },
    { -1606.415894f, 1313.378149f, 18.646879f, 3.274882f }
};

Position const LCWave4Pos[31] =
{
    { -1620.121f, 1308.561f, 19.9279f, 3.297112f },
    { -1626.342f, 1306.55f, 20.34793f, 3.454191f },
    { -1641.361f, 1301.965f, 19.66294f, 3.179297f },
    { -1650.919f, 1301.379f, 19.78221f, 3.202859f },
    { -1658.394f, 1301.537f, 19.78221f, 3.120392f },
    { -1668.168f, 1302.014f, 19.78221f, 3.092903f },
    { -1675.03f, 1307.035f, 19.78221f, 2.719839f },
    { -1682.311f, 1305.757f, 19.78221f, 3.316741f },
    { -1691.982f, 1304.358f, 19.78221f, 3.277472f },
    { -1699.342f, 1305.589f, 19.78221f, 2.971166f },
    { -1708.832f, 1307.975f, 19.78221f, 2.892626f },
    { -1714.742f, 1309.064f, 19.78231f, 2.959385f },
    { -1723.318f, 1311.295f, 19.78231f, 2.884772f },
    { -1729.582f, 1311.974f, 19.78231f, 3.045779f },
    { -1738.853f, 1316.534f, 19.78221f, 2.684496f },
    { -1746.789f, 1322.588f, 19.75776f, 2.492073f },
    { -1753.982f, 1330.772f, 19.7851f, 2.291796f },
    { -1758.898f, 1337.909f, 19.8463f, 2.173987f },
    { -1763.947f, 1345.476f, 19.55916f, 2.05225f },
    { -1768.49f, 1354.427f, 19.7358f, 2.040469f },
    { -1777.133f, 1357.139f, 19.65967f, 2.829794f },
    { -1781.526f, 1362.867f, 19.71775f, 2.225037f },
    { -1773.774f, 1360.402f, 19.63511f, 5.975314f },
    { -1766.378f, 1360.506f, 19.75021f, 0.01414f },
    { -1758.801f, 1366.557f, 19.82114f, 0.673874f },
    { -1750.855f, 1372.903f, 19.91306f, 0.673874f },
    { -1744.28f, 1378.153f, 19.88657f, 0.673874f },
    { -1738.056f, 1383.124f, 19.81904f, 0.673874f },
    { -1730.928f, 1389.849f, 20.52549f, 0.756341f },
    { -1725.869f, 1397.106f, 21.66865f, 0.936983f },
    { -1723.581f, 1405.176f, 21.66865f, 1.192237f }
};

Position const LCWave5Pos[2] =
{
    { -1730.814f, 1407.417f, 21.66901f, 0.516752f },
    { -1708.235f, 1432.356f, 21.66894f, 4.173954f }
};

Position const LCWave7Pos[4] =
{
    { -1740.872f, 1648.488f, 20.47843f, 0.746467f },
    { -1726.228f, 1647.169f, 20.4949f, 5.50598f },
    { -1708.856f, 1630.483f, 20.48794f, 5.549175f },
    { -1686.451f, 1615.535f, 20.48857f, 5.902458f }
};

Position const DCWave4Pos[5] =
{
    { -1766.525f, 1346.081f, 19.70946f, 0.742474f },
    { -1752.061f, 1358.247f, 19.89722f, 0.699277f },
    { -1739.905f, 1377.321f, 19.94529f, 1.029145f },
    { -1727.33f, 1393.516f, 21.59251f, 0.872065f },
    { -1727.921f, 1410.877f, 21.66864f, 1.08805f }
};

Position const DCWave5Pos[1] =
{
    { -1710.235f, 1420.356f, 21.66894f, 4.173954f }
};

Position const DCWave7Pos[4] =
{
    { -1740.872f, 1648.488f, 20.47843f, 0.746467f },
    { -1726.228f, 1647.169f, 20.4949f, 5.50598f },
    { -1708.856f, 1630.483f, 20.48794f, 5.549175f },
    { -1685.742f, 1611.684f, 20.48857f, 0.161197f }
};

Position const GGWave7Pos[4] =
{
    { -1738.539f, 1663.134f, 20.47961f, 5.588446f },
    { -1712.621f, 1643.869f, 20.48606f, 5.64735f },
    { -1699.878f, 1634.308f, 20.48805f, 5.639495f },
    { -1684.787f, 1623.281f, 20.48805f, 5.655202f }
};

// 38553
class npc_krennan_aranas_38553 : public CreatureScript
{
public:
    npc_krennan_aranas_38553() : CreatureScript("npc_krennan_aranas_38553") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (uiAction)
        {
        case GOSSIP_ACTION_INFO_DEF + 1:
        {
            player->CLOSE_GOSSIP_MENU();
            CAST_AI(npc_krennan_aranas_38553::npc_krennan_aranas_38553AI, creature->AI())->StartBattle(player);
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 2:
        {
            player->CLOSE_GOSSIP_MENU();
            break;
        }
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        bool ok = false;
        if (player->GetQuestStatus(QUEST_THE_BATTLE_FOR_GILNEAS_CITY) == QUEST_STATUS_INCOMPLETE)
            if (!creature->AI()->GetData(DATA_IS_BATTLE_STARTED))
                if (Creature* liam = creature->FindNearestCreature(NPC_PRINCE_LIAM_GREYMANE_BATTLE, 50.0f))
                    if (Creature* almyra = creature->FindNearestCreature(NPC_SISTER_ALMYRA, 50.0f))
                        ok = true;
        if (ok)
            player->ADD_GOSSIP_ITEM_DB(11061, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        else
            player->ADD_GOSSIP_ITEM_DB(11061, 1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

        player->SEND_GOSSIP_MENU(2474, creature->GetGUID());

        return true;
    }

    struct npc_krennan_aranas_38553AI : public ScriptedAI
    {
        npc_krennan_aranas_38553AI(Creature *c) : ScriptedAI(c) {}

        EventMap m_events;
        uint64   m_almyraGUID;
        bool	 m_battleIsStarted;
        bool     m_playerIsInvited;

        void Reset()
        {
            m_events.Reset();
            m_events.ScheduleEvent(EVENT_CHECK_PLAYER_FOR_PHASE, 2500);
            m_almyraGUID = 0;
            m_battleIsStarted = false;
            m_playerIsInvited = false;
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case NPC_SISTER_ALMYRA:
                m_almyraGUID = guid;
                break;
            }
        }

        uint32 GetData(uint32 id) const
        {
            switch (id)
            {
            case DATA_IS_BATTLE_STARTED:
                return m_battleIsStarted ? 1 : 0;
            }
            return 0;
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case ACTION_START_EVENT:
            {
                m_events.Reset();
                m_battleIsStarted = true;
                m_playerIsInvited = true;
                break;
            }
            case ACTION_EVENT_RESET_TIMER:
            {
                m_events.RescheduleEvent(EVENT_GLOBAL_RESET, 10 * 60000);
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
                case EVENT_CHECK_PLAYER_FOR_PHASE:
                {
                    std::list<Player*> playerList = me->FindNearestPlayers(200.0f, true);
                    for (std::list<Player*>::const_iterator itr = playerList.begin(); itr != playerList.end(); ++itr)
                        if ((*itr)->GetQuestStatus(QUEST_PUSH_THEM_OUT) == QUEST_STATUS_REWARDED)
                            if ((*itr)->GetPhaseMask() != 262144)
                                (*itr)->SetPhaseMask(262144, true);

                    if (playerList.size() && !m_playerIsInvited && !m_battleIsStarted)
                    {
                        m_playerIsInvited = true;
                        m_events.ScheduleEvent(EVENT_CHECK_PLAYER_FOR_INVITE, 120000);
                        m_events.ScheduleEvent(EVENT_PLAYER_INVITE_COOLDOWN, 300000);
                    }

                    m_events.ScheduleEvent(EVENT_CHECK_PLAYER_FOR_PHASE, 2500);
                    break;
                }
                case EVENT_GLOBAL_RESET:
                {
                    Reset();
                    break;
                }
                case EVENT_PLAYER_INVITE_COOLDOWN:
                {
                    m_playerIsInvited = false;
                    break;
                }
                case EVENT_CHECK_PLAYER_FOR_INVITE:
                {
                    if (!m_battleIsStarted)
                        Talk(0);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void StartBattle(Player* player)
        {
            if (Creature* almyra = sObjectAccessor->GetCreature(*me, m_almyraGUID))
                if (almyra->IsAlive())
                    if (me->GetDistance2d(almyra) < 50)
                    {
                        almyra->AI()->DoAction(ACTION_START_EVENT);
                        Talk(0, player);
                    }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_krennan_aranas_38553AI(creature);
    }
};

// 37803
class npc_marcus_37803 : public CreatureScript
{
public:
    npc_marcus_37803() : CreatureScript("npc_marcus_37803") { }

    enum eNPC
    {
        EVENTS_SAY_TEXT = 101,
    };

    struct npc_marcus_37803AI : public ScriptedAI
    {
        npc_marcus_37803AI(Creature* creature) : ScriptedAI(creature) { }

        EventMap m_events;

        void Reset() override
        {
            m_events.Reset();
            m_events.ScheduleEvent(EVENTS_SAY_TEXT, 60000);
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENTS_SAY_TEXT:
                {
                    Talk(urand(0, 1));
                    m_events.ScheduleEvent(EVENTS_SAY_TEXT, urand(50000, 120000));
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
        return new npc_marcus_37803AI(creature);
    }
};

// 38466 group right.. she has the master AI for the event..
class npc_sister_almyra_38466 : public CreatureScript
{
public:
    npc_sister_almyra_38466() : CreatureScript("npc_sister_almyra_38466") { }

    struct npc_sister_almyra_38466AI : public ScriptedAI
    {
        npc_sister_almyra_38466AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        bool     m_isInitialised;
        uint64   m_krennanGUID;
        uint64   m_prince1GUID;
        uint64   m_prince2GUID;
        uint64   m_myriamGUID;
        uint64   m_lornaGUID;
        uint64   m_dariusGUID;
        uint64   m_kingGUID;
        uint64   m_sylvanaGUID;
        std::list<uint64> my_victimList;
        std::list<uint64> my_followerList;
        uint32   m_arrivedMask;
        uint32   m_shootCoolDown;
        std::list<Creature*> m_targetList;
        uint32    m_wave;
        uint32    m_waveSize;
        uint32    m_point;
        Creature* m_nearestTarget;
        float     m_nearestDistance;
        float     m_checkDistance;
        bool      m_doneA, m_doneB;
        uint32    m_ai_counter;

        void Initialize()
        {
            m_events.Reset();
            m_krennanGUID = 0;
            m_prince1GUID = 0;
            m_prince2GUID = 0;
            m_myriamGUID = 0;
            m_lornaGUID = 0;
            m_dariusGUID = 0;
            m_kingGUID = 0;
            m_sylvanaGUID = 0;
            m_isInitialised = false;
            m_shootCoolDown = 4000;
            m_wave = 0;
            m_arrivedMask = 0;
            m_ai_counter = 0;
            m_events.ScheduleEvent(EVENT_INITIALISE, 1000);
            m_events.ScheduleEvent(EVENT_CHECK_FOR_TIMER, 1000);
        }

        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
            if (my_followerList.empty())
                SummonMyMember();
        }

        void JustSummoned(Creature* summon) override
        {
            if (summon->GetEntry() == NPC_GILNEAN_MILITIA)
                my_followerList.push_back(summon->GetGUID());
            else
                my_victimList.push_back(summon->GetGUID());
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            damage = 0;
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == POINT_MOTION_TYPE)
                switch (id)
                {
                case 2001:
                case 2002:
                case 2003:
                case 2004:
                case 2005:
                case 2006:
                case 2007:
                {
                    m_events.RescheduleEvent(EVENT_FIGHT_WAVE, 250);
                    break;
                }
                }
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case ACTION_START_EVENT:
            {
                m_events.ScheduleEvent(EVENT_START_LIAMS_FIRST_ANIM, 15000);
                SendActionValueToAllLeader(ACTION_START_EVENT);
                break;
            }
            case ACTION_MOTIVATION_DONE:
            {
                SendActionValueToAllLeader(ACTION_MOVE_TO_WAVE_POSION_1);
                m_events.RescheduleEvent(EVENT_MOVE_WAVE, 250);
                break;
            }
            case ACTION_QUEST_REWARDED:
            {
                SendActionValueToAllLeader(ACTION_QUEST_REWARDED);
                break;
            }
            case ACTION_LIAM_ARRIVED:
                m_arrivedMask |= 2;
                break;
            case ACTION_MYRIAM_ARRIVED:
                m_arrivedMask |= 4;
                break;
            case ACTION_LORNA_ARRIVED:
                m_arrivedMask |= 8;
                break;
            case ACTION_DARIUS_ARRIVED:
                m_arrivedMask |= 16;
            case ACTION_GENN_ARRIVED:
                m_arrivedMask |= 32;
                break;
            case ACTION_SYLVANAS_ARRIVED:
                m_arrivedMask |= 64;
                break;
            }
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case NPC_PRINCE_LIAM_GREYMANE_BATTLE:
            {
                if (m_prince1GUID != guid)
                    if (Creature* check = sObjectAccessor->GetCreature(*me, guid))
                    {
                        check->AI()->DoAction(ACTION_INITIALIZE_DONE);
                        m_prince1GUID = guid;
                    }
                break;
            }
            case NPC_PRINCE_LIAM_GREYMANE:
            {
                if (m_prince2GUID != guid)
                    if (Creature* check = sObjectAccessor->GetCreature(*me, guid))
                    {
                        check->AI()->DoAction(ACTION_INITIALIZE_DONE);
                        m_prince2GUID = guid;
                    }
                break;
            }
            case NPC_MYRIAM_SPELLWAKER:
            {
                if (m_myriamGUID != guid)
                    if (Creature* check = sObjectAccessor->GetCreature(*me, guid))
                    {
                        check->AI()->DoAction(ACTION_INITIALIZE_DONE);
                        m_myriamGUID = guid;
                    }
                break;
            }
            case NPC_LORNA_CROWLEY:
            {
                if (m_lornaGUID != guid)
                    if (Creature* check = sObjectAccessor->GetCreature(*me, guid))
                    {
                        check->AI()->DoAction(ACTION_INITIALIZE_DONE);
                        m_lornaGUID = guid;
                    }
                break;
            }
            case NPC_LORD_DARIUS_CROWLEY:
            {
                if (m_dariusGUID != guid)
                    if (Creature* check = sObjectAccessor->GetCreature(*me, guid))
                    {
                        check->AI()->DoAction(ACTION_INITIALIZE_DONE);
                        m_dariusGUID = guid;
                    }
                break;
            }
            case NPC_KING_GENN_GREYMANE:
            {
                if (m_kingGUID != guid)
                    if (Creature* check = sObjectAccessor->GetCreature(*me, guid))
                    {
                        check->AI()->DoAction(ACTION_INITIALIZE_DONE);
                        m_kingGUID = guid;
                    }
                break;
            }
            case NPC_LADY_SYLVANAS_WINDRUNNER:
            {
                if (m_sylvanaGUID != guid)
                    if (Creature* check = sObjectAccessor->GetCreature(*me, guid))
                    {
                        check->AI()->DoAction(ACTION_INITIALIZE_DONE);
                        m_sylvanaGUID = guid;
                    }
                break;
            }
            }
        }

        uint64 GetGUID(int32 id) const override
        {
            switch (id)
            {
            case NPC_PRINCE_LIAM_GREYMANE_BATTLE:
                return m_prince1GUID;
            case NPC_PRINCE_LIAM_GREYMANE:
                return m_prince2GUID;
            case NPC_MYRIAM_SPELLWAKER:
                return m_myriamGUID;
            case NPC_LORNA_CROWLEY:
                return m_lornaGUID;
            case NPC_LORD_DARIUS_CROWLEY:
                return m_dariusGUID;
            case NPC_KING_GENN_GREYMANE:
                return m_kingGUID;
            case NPC_LADY_SYLVANAS_WINDRUNNER:
                return m_sylvanaGUID;
            }

            return 0;
        }

        void EnterEvadeMode() override { }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_INITIALISE:
                {
                    if (!m_isInitialised)
                    {
                        if (!m_krennanGUID)
                            if (Creature* krennan = me->FindNearestCreature(NPC_KRENNAN_ARANAS, 250.0f))
                                m_krennanGUID = krennan->GetGUID();

                        if (Creature* krennan = sObjectAccessor->GetCreature(*me, m_krennanGUID))
                        {
                            krennan->AI()->SetGUID(me->GetGUID(), me->GetEntry());
                            m_isInitialised = true;
                            break;
                        }

                        m_events.ScheduleEvent(EVENT_INITIALISE, 1000);
                    }
                    break;
                }
                case EVENT_GLOBAL_RESET:
                {
                    RemoveMyMember();
                    me->DespawnOrUnsummon(100);
                    break;
                }
                case EVENT_START_LIAMS_FIRST_ANIM:
                {
                    if (Creature* liam = sObjectAccessor->GetCreature(*me, m_prince1GUID))
                        liam->AI()->DoAction(ACTION_START_MOTIVATION);
                    break;
                }
                case EVENT_CHECK_FOR_TIMER:
                {
                    if (m_point < m_waveSize)
                    {
                        uint32 a = m_events.GetNextEventTime(EVENT_MOVE_WAVE);
                        uint32 b = m_events.GetNextEventTime(EVENT_FIGHT_WAVE);
                        if (!a && !b)
                        {
                            m_ai_counter += 1;
                            if (m_ai_counter > 30)
                                m_events.RescheduleEvent(EVENT_FIGHT_WAVE, m_shootCoolDown);
                        }

                    }
                    m_events.ScheduleEvent(EVENT_CHECK_FOR_TIMER, 1000);
                    break;
                }
                case EVENT_MOVE_WAVE:
                {
                    CheckForStartAction();

                    if (m_point < m_waveSize)
                    {
                        me->GetMotionMaster()->MovePoint(2000 + m_wave, GetWavePosition());
                    }
                    else
                    {
                        m_arrivedMask |= 1;
                        m_events.RescheduleEvent(EVENT_SYNC_BEFORE_NEXT_WAVE, 2500);
                    }
                    break;
                }
                case EVENT_FIGHT_WAVE:
                {
                    CheckForStartAction();

                    FindTargets();

                    if (m_nearestTarget)
                    {
                        Position pos = me->GetPosition();
                        if (GetWavePosition().GetExactDist2d(&pos) > 3.0f)
                        {
                            // redo the move, if my distance are growing..
                            m_events.RescheduleEvent(EVENT_MOVE_WAVE, 500);
                        }
                        else if (m_nearestDistance > m_checkDistance)
                        {
                            m_point += 1;
                            m_events.RescheduleEvent(EVENT_MOVE_WAVE, 10);
                        }
                        else
                        {
                            me->SetFacingToObject(m_nearestTarget);
                            for (std::list<uint64>::const_iterator itr = my_followerList.begin(); itr != my_followerList.end(); ++itr)
                                if (Creature* follower = sObjectAccessor->GetCreature(*me, (*itr)))
                                {
                                    follower->SetFacingToObject(m_nearestTarget);
                                    if (m_nearestTarget->GetDistance2d(follower) > 5.0f)
                                        follower->CastSpell(m_nearestTarget, SPELL_GILNEAS_MILITIA_SHOOT);
                                    else
                                        follower->Attack(m_nearestTarget, true);
                                }
                            m_events.RescheduleEvent(EVENT_FIGHT_WAVE, m_shootCoolDown);
                        }
                    }
                    else
                    {
                        if (m_wave == 4 && m_point == 16 && !IsPlayerNear(20.0f))
                        {
                            m_events.RescheduleEvent(EVENT_FIGHT_WAVE, 1000);
                            break;
                        }

                        m_point += 1;
                        m_events.RescheduleEvent(EVENT_MOVE_WAVE, 10);
                    }
                    break;
                }
                case EVENT_SYNC_BEFORE_NEXT_WAVE:
                {
                    m_ai_counter = 0;
                    uint32 mask;
                    switch (m_wave)
                    {
                    case 1:
                    case 2:
                        mask = 7;
                        break;
                    case 3:
                        mask = 15 + 128;
                        break;
                    case 4:
                    case 5:
                    case 6:
                        mask = 31 + 128;
                        break;
                    case 7:
                        mask = 63 + 128;
                        break;
                    }
                    if (IsPlayerNear(25.0f))
                        m_arrivedMask |= 128;

                    if ((m_arrivedMask & mask) == mask)
                    {
                        switch (m_wave)
                        {
                        case 1: // running over marketplace
                        {
                            SendActionValueToAllLeader(ACTION_EVENT_RESET_TIMER);
                            SendActionValueToAllLeader(ACTION_MOVE_TO_WAVE_POSION_2);
                            m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                            break;
                        }
                        case 2: // running down the stairway
                        {
                            SendActionValueToAllLeader(ACTION_EVENT_RESET_TIMER);
                            SendActionValueToAllLeader(ACTION_MOVE_TO_WAVE_POSION_3);
                            m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                            break;
                        }
                        case 3: // running to militaryplace
                        {
                            SendActionValueToAllLeader(ACTION_EVENT_RESET_TIMER);
                            SendActionValueToAllLeader(ACTION_MOVE_TO_WAVE_POSION_4);
                            m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                            break;
                        }
                        case 4: // running near to gorerot
                        {
                            SendActionValueToAllLeader(ACTION_EVENT_RESET_TIMER);
                            me->SummonCreature(NPC_GOREROT, SpawnPosGorerot[0], TEMPSUMMON_DEAD_DESPAWN);
                            SendActionValueToAllLeader(ACTION_MOVE_TO_WAVE_POSION_5);
                            m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                            break;
                        }
                        case 5: // gorerot is death.. now all groups moving to meet silvanas. 
                        {
                            SendActionValueToAllLeader(ACTION_EVENT_RESET_TIMER);
                            SendActionValueToAllLeader(ACTION_MOVE_TO_WAVE_POSION_6);
                            m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                            break;
                        }
                        case 6: // running near sylvanas
                        {
                            SendActionValueToAllLeader(ACTION_EVENT_RESET_TIMER);
                            SendActionValueToAllLeader(ACTION_MOVE_TO_WAVE_POSION_7);
                            m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                            break;
                        }
                        }
                    }
                    else
                        m_events.ScheduleEvent(EVENT_SYNC_BEFORE_NEXT_WAVE, 2500);
                    break;
                }
                case EVENT_SYLVANAS_HAS_ENOUGH:
                {
                    m_events.CancelEvent(EVENT_MOVE_WAVE);
                    m_events.CancelEvent(EVENT_FIGHT_WAVE);
                    m_events.CancelEvent(EVENT_CHECK_FOR_TIMER);
                    SendActionValueToAllLeader(ACTION_SYLVANAS_HAS_ENOUGH);
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void SummonMyMember()
        {
            for (uint32 i = 0; i < 19; ++i)
                if (Creature* summon = DoSummon(NPC_GILNEAN_MILITIA, SpawnPosGroup1[i], 0, TEMPSUMMON_DEAD_DESPAWN))
                    summon->SetReactState(REACT_PASSIVE);

            for (uint32 i = 0; i < 32; ++i)
                if (Creature* summon = DoSummon(NPC_FORSAKEN_CROSSBOWMAN, SpawnPosForsakenCrossbowman[i], 0, TEMPSUMMON_DEAD_DESPAWN))
                    summon->SetReactState(REACT_PASSIVE);

        }

        void RemoveMyMember()
        {
            for (std::list<uint64>::const_iterator itr = my_followerList.begin(); itr != my_followerList.end(); ++itr)
                if (Creature* follower = sObjectAccessor->GetCreature(*me, (*itr)))
                    follower->DespawnOrUnsummon(10);
            for (std::list<uint64>::const_iterator itr = my_victimList.begin(); itr != my_victimList.end(); ++itr)
                if (Creature* victim = sObjectAccessor->GetCreature(*me, (*itr)))
                    victim->DespawnOrUnsummon(10);
            my_followerList.clear();
            my_victimList.clear();
        }

        void BuildFollowerGroup()
        {
            for (std::list<uint64>::const_iterator itr = my_followerList.begin(); itr != my_followerList.end(); ++itr)
                if (Creature* follower = sObjectAccessor->GetCreature(*me, (*itr)))
                {
                    float dist = frand(1.0f, 3.0f);
                    float angl = frand(0.0f, M_PI * 2);
                    follower->GetMotionMaster()->MoveFollow(me, dist, angl);
                    follower->AI()->SetGUID(me->GetGUID(), NPC_LEADER_GUID);
                }
        }

        void FindTargets()
        {
            m_targetList = me->FindAllUnfriendlyCreaturesInRange(21.0f);
            if (m_targetList.empty())
            {
                m_nearestTarget = nullptr;
                m_nearestDistance = 0;
            }
            else
            {
                m_nearestTarget = *m_targetList.begin();
                m_nearestDistance = m_nearestTarget->GetDistance2d(me);
                for (std::list<Creature*>::const_iterator itr = m_targetList.begin(); itr != m_targetList.end(); ++itr)
                {
                    float dist2 = (*itr)->GetDistance2d(me);
                    if (dist2 < m_nearestDistance)
                    {
                        m_nearestTarget = (*itr);
                        m_nearestDistance = dist2;
                    }
                }
            }

            m_checkDistance = 15.0f;
            if (m_nearestTarget)
                if (m_nearestTarget->GetEntry() == NPC_GOREROT)
                    m_checkDistance = 16.0f;
                else if (m_nearestTarget->GetEntry() == NPC_LADY_SYLVANAS_WINDRUNNER)
                    m_checkDistance = 25.0f;
        }

        Position GetWavePosition()
        {
            switch (m_wave)
            {
            case 1:
                return SAWave1Pos[m_point];
            case 2:
                return SAWave2Pos[m_point];
            case 3:
                return SAWave3Pos[m_point];
            case 4:
                return SAWave4Pos[m_point];
            case 5:
                return SAWave5Pos[m_point];
            case 6:
                return Wave6Pos[m_point];
            case 7:
                return SAWave7Pos[m_point];
            default:
                return Position(0, 0);
            }
        }

        void CheckForStartAction()
        {
            m_ai_counter = 0;
            switch (m_wave)
            {
            case 4:
            {
                if (m_point == 17 && !m_doneA)
                {
                    m_doneA = true;
                    if (Creature* darius = sObjectAccessor->GetCreature(*me, m_dariusGUID))
                        darius->AI()->DoAction(ACTION_MOVE_TO_MEET_POINT4);
                    if (Creature* liam = sObjectAccessor->GetCreature(*me, m_prince1GUID))
                        liam->AI()->DoAction(ACTION_LIAM_TALK_10);
                }
                if (m_point == 15)
                    m_shootCoolDown = 5000;
                break;
            }
            case 7:
            {
                if (m_point > 2 && !m_doneA) // let the fight vs sylvanas ending after 45sec
                {
                    m_doneA = true;
                    m_events.ScheduleEvent(EVENT_SYLVANAS_HAS_ENOUGH, 45000);
                }
                break;
            }
            }
        }

        void SendActionValueToAllLeader(uint32 ActionValue)
        {
            if (Creature* krennan = sObjectAccessor->GetCreature(*me, m_krennanGUID))
                krennan->AI()->DoAction(ActionValue);
            if (Creature* liam = sObjectAccessor->GetCreature(*me, m_prince1GUID))
                liam->AI()->DoAction(ActionValue);
            if (Creature* liam = sObjectAccessor->GetCreature(*me, m_prince2GUID))
                liam->AI()->DoAction(ActionValue);
            if (Creature* myriam = sObjectAccessor->GetCreature(*me, m_myriamGUID))
                myriam->AI()->DoAction(ActionValue);
            if (Creature* lorna = sObjectAccessor->GetCreature(*me, m_lornaGUID))
                lorna->AI()->DoAction(ActionValue);
            if (Creature* darius = sObjectAccessor->GetCreature(*me, m_dariusGUID))
                darius->AI()->DoAction(ActionValue);
            if (Creature* king = sObjectAccessor->GetCreature(*me, m_kingGUID))
                king->AI()->DoAction(ActionValue);
            if (Creature* sylvana = sObjectAccessor->GetCreature(*me, m_sylvanaGUID))
                sylvana->AI()->DoAction(ActionValue);

            switch (ActionValue)
            {
            case ACTION_EVENT_RESET_TIMER:
                m_events.RescheduleEvent(EVENT_GLOBAL_RESET, 10 * 60000);
                break;
            case ACTION_MOVE_TO_WAVE_POSION_1:
                BuildFollowerGroup();
                m_doneA = false; m_doneB = false;
                m_shootCoolDown = 3000;
                m_wave = 1;
                m_waveSize = 9;
                m_point = 0;
                m_arrivedMask = 0;
                break;
            case ACTION_MOVE_TO_WAVE_POSION_2:
                m_doneA = false; m_doneB = false;
                m_shootCoolDown = 2500;
                m_wave = 2;
                m_waveSize = 12;
                m_point = 0;
                m_arrivedMask = 0;
                break;
            case ACTION_MOVE_TO_WAVE_POSION_3:
                m_doneA = false; m_doneB = false;
                m_shootCoolDown = 4000;
                m_wave = 3;
                m_waveSize = 4;
                m_point = 0;
                m_arrivedMask = 0;
                break;
            case ACTION_MOVE_TO_WAVE_POSION_4:
                m_doneA = false; m_doneB = false;
                m_shootCoolDown = 3000;
                m_wave = 4;
                m_waveSize = 23;
                m_point = 0;
                m_arrivedMask = 0;
                break;
            case ACTION_MOVE_TO_WAVE_POSION_5:
                m_doneA = false; m_doneB = false;
                m_shootCoolDown = 4000;
                m_wave = 5;
                m_waveSize = 2;
                m_point = 0;
                m_arrivedMask = 0;
                break;
            case ACTION_MOVE_TO_WAVE_POSION_6:
                m_doneA = false; m_doneB = false;
                m_shootCoolDown = 4000;
                m_wave = 6;
                m_waveSize = 21;
                m_point = 0;
                m_arrivedMask = 0;
                break;
            case ACTION_MOVE_TO_WAVE_POSION_7:
                m_doneA = false; m_doneB = false;
                m_shootCoolDown = 4000;
                m_wave = 7;
                m_waveSize = 4;
                m_point = 0;
                m_arrivedMask = 0;
                break;
            case ACTION_QUEST_REWARDED:
                RemoveMyMember();
                me->DespawnOrUnsummon();
                break;
            }


        }

        bool IsPlayerNear(float range)
        {
            return (me->FindNearestPlayer(range)) ? true : false;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_sister_almyra_38466AI(creature);
    }
};

// 38218 group mid
class npc_prince_liam_greymane_38218 : public CreatureScript
{
public:
    npc_prince_liam_greymane_38218() : CreatureScript("npc_prince_liam_greymane_38218") { }

    struct npc_prince_liam_greymane_38218AI : public ScriptedAI
    {
        npc_prince_liam_greymane_38218AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        bool     m_isInitialised;
        uint64   m_almyraGUID;
        uint32   m_shootCoolDown;
        std::list<uint64> my_followerList;
        std::list<Creature*> m_targetList;
        uint32    m_wave;
        uint32    m_waveSize;
        uint32    m_point;
        Creature* m_nearestTarget;
        float     m_nearestDistance;
        float     m_checkDistance;
        bool      m_doneA, m_doneB;
        uint32    m_ai_counter;

        void Initialize()
        {
            m_events.Reset();
            m_events.ScheduleEvent(EVENT_CHECK_PLAYER_FOR_PHASE, 2500);
            m_events.ScheduleEvent(EVENT_INITIALISE, 1000);
            m_events.ScheduleEvent(EVENT_RANDOM_TEXT, 30000);
            m_events.ScheduleEvent(EVENT_CHECK_FOR_TIMER, 1000);
            m_almyraGUID = 0;
            m_isInitialised = false;
            m_shootCoolDown = 4000;
            m_ai_counter = 0;
        }

        void Reset() override
        {
            if (!me->HasAura(458))
                me->AddAura(458, me);
            if (!me->HasAura(72069))
                me->AddAura(72069, me);
            me->SetReactState(REACT_PASSIVE);
            if (my_followerList.empty())
                SummonMyMember();
            me->SetSpeed(MOVE_RUN, 1.0f, true);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            damage = 0;
        }

        void JustSummoned(Creature* summon) override
        {
            my_followerList.push_back(summon->GetGUID());
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == POINT_MOTION_TYPE)
                switch (id)
                {
                case 2001:
                case 2002:
                case 2003:
                case 2004:
                case 2005:
                case 2006:
                case 2007:
                {
                    m_events.RescheduleEvent(EVENT_FIGHT_WAVE, 250);
                    break;
                }
                }
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case ACTION_INITIALIZE_DONE:
            {
                m_isInitialised = true;
                break;
            }
            case ACTION_EVENT_RESET_TIMER:
            {
                m_events.RescheduleEvent(EVENT_GLOBAL_RESET, 10 * 60000);
                break;
            }
            case ACTION_START_MOTIVATION:
            {
                m_events.ScheduleEvent(EVENT_MOTIVATION_0, 1000);
                break;
            }
            case ACTION_LIAM_TALK_10:
            {
                Talk(10);
                break;
            }
            case ACTION_MOVE_TO_WAVE_POSION_1:
            {
                BuildFollowerGroup();
                m_wave = 1;
                m_waveSize = 8;
                m_point = 0;
                m_doneA = false; m_doneB = false;
                m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                break;
            }
            case ACTION_MOVE_TO_WAVE_POSION_2:
            {
                m_wave = 2;
                m_waveSize = 12;
                m_point = 0;
                m_doneA = false; m_doneB = false;
                m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                break;
            }
            case ACTION_MOVE_TO_WAVE_POSION_3:
            {
                Talk(8);
                m_wave = 3;
                m_waveSize = 4;
                m_point = 0;
                m_doneA = false; m_doneB = false;
                m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                break;
            }
            case ACTION_MOVE_TO_WAVE_POSION_4:
            {
                m_wave = 4;
                m_waveSize = 23;
                m_point = 0;
                m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                break;
            }
            case ACTION_MOVE_TO_WAVE_POSION_5:
            {
                m_wave = 5;
                m_waveSize = 2;
                m_point = 0;
                m_doneA = false; m_doneB = false;
                m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                break;
            }
            case ACTION_MOVE_TO_WAVE_POSION_6:
            {
                m_wave = 6;
                m_waveSize = 21;
                m_point = 0;
                m_doneA = false; m_doneB = false;
                m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                break;
            }
            case ACTION_MOVE_TO_WAVE_POSION_7:
            {
                m_wave = 7;
                m_waveSize = 3;
                m_point = 0;
                m_doneA = false; m_doneB = false;
                m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                break;
            }
            }
        }

        void EnterEvadeMode() override { }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_PLAYER_FOR_PHASE:
                {
                    std::list<Player*> playerList = me->FindNearestPlayers(200.0f, true);
                    for (std::list<Player*>::const_iterator itr = playerList.begin(); itr != playerList.end(); ++itr)
                        if ((*itr)->GetQuestStatus(QUEST_PUSH_THEM_OUT) == QUEST_STATUS_REWARDED)
                            if ((*itr)->GetPhaseMask() != 262144)
                                (*itr)->SetPhaseMask(262144, true);

                    m_events.ScheduleEvent(EVENT_CHECK_PLAYER_FOR_PHASE, 2500);
                    break;
                }
                case EVENT_INITIALISE:
                {
                    if (!m_isInitialised)
                    {
                        if (!m_almyraGUID)
                            if (Creature* almyra = me->FindNearestCreature(NPC_SISTER_ALMYRA, 250.0f))
                                m_almyraGUID = almyra->GetGUID();

                        if (Creature* almyra = sObjectAccessor->GetCreature(*me, m_almyraGUID))
                            almyra->AI()->SetGUID(me->GetGUID(), me->GetEntry());

                        m_events.ScheduleEvent(EVENT_INITIALISE, 1000);
                    }
                    break;
                }
                case EVENT_GLOBAL_RESET:
                {
                    RemoveMyMember();
                    me->DespawnOrUnsummon(100);
                    break;
                }
                case EVENT_MOTIVATION_0:
                {
                    Talk(0);
                    m_events.ScheduleEvent(EVENT_MOTIVATION_1, 10000);
                    break;
                }
                case EVENT_MOTIVATION_1:
                {
                    Talk(1);
                    m_events.ScheduleEvent(EVENT_MOTIVATION_2, 10000);
                    break;
                }
                case EVENT_MOTIVATION_2:
                {
                    Talk(2);
                    m_events.ScheduleEvent(EVENT_MOTIVATION_3, 11000);
                    break;
                }
                case EVENT_MOTIVATION_3:
                {
                    Talk(3);
                    m_events.ScheduleEvent(EVENT_MOTIVATION_4, 9000);
                    break;
                }
                case EVENT_MOTIVATION_4:
                {
                    Talk(4);
                    m_events.ScheduleEvent(EVENT_MOTIVATION_5, 11000);
                    break;
                }
                case EVENT_MOTIVATION_5:
                {
                    Talk(5);
                    m_events.ScheduleEvent(EVENT_MOTIVATION_6, 5000);
                    break;
                }
                case EVENT_MOTIVATION_6:
                {
                    Talk(6);
                    m_events.ScheduleEvent(EVENT_MOTIVATION_DONE, 500);
                    break;
                }
                case EVENT_MOTIVATION_DONE:
                {
                    if (Creature* almyra = sObjectAccessor->GetCreature(*me, m_almyraGUID))
                        almyra->AI()->DoAction(ACTION_MOTIVATION_DONE);
                    me->PlayDirectSound(SOUND_GILNEAN_MILITIA);
                    break;
                }
                case EVENT_RANDOM_TEXT:
                {
                    if (m_wave >= 2 && m_wave <= 4)
                    {
                        Talk(7);
                        m_events.ScheduleEvent(EVENT_RANDOM_TEXT, urand(60000, 90000));
                        break;
                    }

                    m_events.ScheduleEvent(EVENT_RANDOM_TEXT, 30000);
                    break;
                }
                case EVENT_LIAM_TALK_9:
                {
                    Talk(9);
                    break;
                }
                case EVENT_CHECK_FOR_TIMER:
                {
                    if (m_point < m_waveSize)
                    {
                        uint32 a = m_events.GetNextEventTime(EVENT_MOVE_WAVE);
                        uint32 b = m_events.GetNextEventTime(EVENT_FIGHT_WAVE);
                        if (!a && !b)
                        {
                            m_ai_counter += 1;
                            if (m_ai_counter > 30)
                                m_events.RescheduleEvent(EVENT_FIGHT_WAVE, m_shootCoolDown);
                        }
                    }
                    m_events.ScheduleEvent(EVENT_CHECK_FOR_TIMER, 1000);
                    break;
                }
                case EVENT_MOVE_WAVE:
                {
                    CheckForStartAction();

                    if (m_point < m_waveSize)
                    {
                        me->GetMotionMaster()->MovePoint(2000 + m_wave, GetWavePosition());
                    }
                    else if (Creature* almyra = sObjectAccessor->GetCreature(*me, m_almyraGUID))
                        almyra->AI()->DoAction(ACTION_LIAM_ARRIVED);

                    break;
                }
                case EVENT_FIGHT_WAVE:
                {
                    CheckForStartAction();

                    FindTargets();

                    if (m_nearestTarget)
                    {
                        Position pos = me->GetPosition();
                        if (GetWavePosition().GetExactDist2d(&pos) > 3.0f)
                        {
                            m_events.RescheduleEvent(EVENT_MOVE_WAVE, 500);
                        }
                        else if (m_nearestDistance > m_checkDistance)
                        {
                            m_point += 1;
                            m_events.RescheduleEvent(EVENT_MOVE_WAVE, 500);
                        }
                        else
                        {
                            me->SetFacingToObject(m_nearestTarget);
                            for (std::list<uint64>::const_iterator itr = my_followerList.begin(); itr != my_followerList.end(); ++itr)
                                if (Creature* follower = sObjectAccessor->GetCreature(*me, (*itr)))
                                {
                                    follower->SetFacingToObject(m_nearestTarget);
                                    if (m_nearestTarget->GetDistance2d(follower) > 5.0f)
                                        follower->CastSpell(m_nearestTarget, SPELL_GILNEAS_MILITIA_SHOOT);
                                    else
                                        follower->Attack(m_nearestTarget, true);
                                }
                            m_events.RescheduleEvent(EVENT_FIGHT_WAVE, m_shootCoolDown);
                        }
                    }
                    else
                    {
                        m_point += 1;
                        m_events.RescheduleEvent(EVENT_MOVE_WAVE, 10);
                    }
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void SummonMyMember()
        {
            for (uint32 i = 0; i < 19; ++i)
                if (Creature* summon = DoSummon(NPC_GILNEAN_MILITIA, SpawnPosGroup2[i], 0, TEMPSUMMON_DEAD_DESPAWN))
                    summon->SetReactState(REACT_PASSIVE);
        }

        void RemoveMyMember()
        {
            for (std::list<uint64>::const_iterator itr = my_followerList.begin(); itr != my_followerList.end(); ++itr)
                if (Creature* follower = sObjectAccessor->GetCreature(*me, (*itr)))
                    follower->DespawnOrUnsummon(10);

            my_followerList.clear();
        }

        void BuildFollowerGroup()
        {
            for (std::list<uint64>::const_iterator itr = my_followerList.begin(); itr != my_followerList.end(); ++itr)
                if (Creature* follower = sObjectAccessor->GetCreature(*me, (*itr)))
                {
                    float dist = frand(1.0f, 3.0f);
                    float angl = frand(0.0f, M_PI * 2);
                    follower->GetMotionMaster()->MoveFollow(me, dist, angl);
                    follower->AI()->SetGUID(me->GetGUID(), NPC_LEADER_GUID);
                }
        }

        void FindTargets()
        {
            m_targetList = me->FindAllUnfriendlyCreaturesInRange(25.0f);
            if (m_targetList.empty())
            {
                m_nearestTarget = nullptr;
                m_nearestDistance = 0;
            }
            else
            {
                m_nearestTarget = *m_targetList.begin();
                m_nearestDistance = m_nearestTarget->GetDistance2d(me);
                for (std::list<Creature*>::const_iterator itr = m_targetList.begin(); itr != m_targetList.end(); ++itr)
                {
                    float dist2 = (*itr)->GetDistance2d(me);
                    if (dist2 < m_nearestDistance)
                    {
                        m_nearestTarget = (*itr);
                        m_nearestDistance = dist2;
                    }
                }
            }

            m_checkDistance = 15.0f;
            if (m_nearestTarget)
                if (m_nearestTarget->GetEntry() == NPC_GOREROT)
                    m_checkDistance = 16.0f;
                else if (m_nearestTarget->GetEntry() == NPC_LADY_SYLVANAS_WINDRUNNER)
                    m_checkDistance = 25.0f;
        }

        Position GetWavePosition()
        {
            switch (m_wave)
            {
            case 1:
                return LGWave1Pos[m_point];
            case 2:
                return LGWave2Pos[m_point];
            case 3:
                return LGWave3Pos[m_point];
            case 4:
                return LGWave4Pos[m_point];
            case 5:
                return LGWave5Pos[m_point];
            case 6:
                return Wave6Pos[m_point];
            case 7:
                return LGWave7Pos[m_point];
            default:
                return Position(0, 0);
            }
        }

        void CheckForStartAction()
        {
            m_ai_counter = 0;
            switch (m_wave)
            {
            case 3:
            {
                if (m_point == 4 && !m_doneA)
                {
                    m_doneA = true;
                    m_events.ScheduleEvent(EVENT_LIAM_TALK_9, 3000);
                }

                break;
            }
            case 6:
            {
                if (m_point == 19 && !m_doneA)
                    if (Creature* almyra = sObjectAccessor->GetCreature(*me, m_almyraGUID))
                        if (Creature* king = sObjectAccessor->GetCreature(*me, almyra->AI()->GetGUID(NPC_KING_GENN_GREYMANE)))
                        {
                            king->AI()->DoAction(ACTION_KING_TALK_2);
                            m_doneA = true;
                        }
                break;
            }
            case 7:
            {
                if (m_point == 3 && !m_doneA)
                {
                    m_doneA = true;
                    RemoveMyMember();
                    me->DespawnOrUnsummon(100);
                    m_events.Reset();
                }
                break;
            }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_prince_liam_greymane_38218AI(creature);
    }
};

// 38465 group left
class npc_myriam_spellwaker_38465 : public CreatureScript
{
public:
    npc_myriam_spellwaker_38465() : CreatureScript("npc_myriam_spellwaker_38465") { }

    struct npc_myriam_spellwaker_38465AI : public ScriptedAI
    {
        npc_myriam_spellwaker_38465AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        bool     m_isInitialised;
        uint64   m_almyraGUID;
        std::list<uint64> my_followerList;
        uint32   m_shootCoolDown;
        std::list<Creature*> m_targetList;
        uint32    m_wave;
        uint32    m_waveSize;
        uint32    m_point;
        Creature* m_nearestTarget;
        float     m_nearestDistance;
        float     m_checkDistance;
        bool      m_doneA, m_doneB;
        uint32    m_ai_counter;

        void Initialize()
        {
            m_events.Reset();
            m_almyraGUID = 0;
            m_isInitialised = false;
            m_shootCoolDown = 4000;
            m_ai_counter = 0;
            m_events.ScheduleEvent(EVENT_INITIALISE, 1000);
            m_events.ScheduleEvent(EVENT_CHECK_FOR_TIMER, 1000);
        }

        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
            if (my_followerList.empty())
                SummonMyMember();
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            damage = 0;
        }

        void JustSummoned(Creature* summon) override
        {
            my_followerList.push_back(summon->GetGUID());
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == POINT_MOTION_TYPE)
                switch (id)
                {
                case 2001:
                case 2002:
                case 2003:
                case 2004:
                case 2005:
                case 2006:
                case 2007:
                {
                    m_events.RescheduleEvent(EVENT_FIGHT_WAVE, 250);
                    break;
                }
                }
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case ACTION_INITIALIZE_DONE:
            {
                m_isInitialised = true;
                break;
            }
            case ACTION_EVENT_RESET_TIMER:
            {
                m_events.RescheduleEvent(EVENT_GLOBAL_RESET, 10 * 60000);
                break;
            }
            case ACTION_MOVE_TO_WAVE_POSION_1:
            {
                BuildFollowerGroup();
                m_shootCoolDown = 4000;
                m_wave = 1;
                m_waveSize = 8;
                m_point = 0;
                m_doneA = false; m_doneB = false;
                m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                break;
            }
            case ACTION_MOVE_TO_WAVE_POSION_2:
            {
                m_shootCoolDown = 4000;
                m_wave = 2;
                m_waveSize = 10;
                m_point = 0;
                m_doneA = false; m_doneB = false;
                m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                break;
            }
            case ACTION_MOVE_TO_WAVE_POSION_3:
            {
                m_shootCoolDown = 4000;
                m_wave = 3;
                m_waveSize = 3;
                m_point = 0;
                m_doneA = false; m_doneB = false;
                m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                break;
            }
            case ACTION_MOVE_TO_WAVE_POSION_4:
            {
                m_shootCoolDown = 2500;
                m_wave = 4;
                m_waveSize = 29;
                m_point = 0;
                m_doneA = false; m_doneB = false;
                m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                break;
            }
            case ACTION_MOVE_TO_WAVE_POSION_5:
            {
                m_wave = 5;
                m_waveSize = 2;
                m_point = 0;
                m_doneA = false; m_doneB = false;
                m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                break;
            }
            case ACTION_MOVE_TO_WAVE_POSION_6:
            {
                m_wave = 6;
                m_waveSize = 21;
                m_point = 0;
                m_doneA = false; m_doneB = false;
                m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                break;
            }
            case ACTION_MOVE_TO_WAVE_POSION_7:
            {
                m_wave = 7;
                m_waveSize = 4;
                m_point = 0;
                m_doneA = false; m_doneB = false;
                m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                break;
            }
            case ACTION_SYLVANAS_HAS_ENOUGH:
            {
                m_events.CancelEvent(EVENT_MOVE_WAVE);
                m_events.CancelEvent(EVENT_FIGHT_WAVE);
                m_events.CancelEvent(EVENT_CHECK_FOR_TIMER);

                break;
            }
            case ACTION_QUEST_REWARDED:
            {
                RemoveMyMember();
                me->DespawnOrUnsummon();
                break;
            }
            }
        }

        void EnterEvadeMode() override { }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_INITIALISE:
                {
                    if (!m_isInitialised)
                    {
                        if (!m_almyraGUID)
                            if (Creature* almyra = me->FindNearestCreature(NPC_SISTER_ALMYRA, 250.0f))
                                m_almyraGUID = almyra->GetGUID();

                        if (Creature* almyra = sObjectAccessor->GetCreature(*me, m_almyraGUID))
                            almyra->AI()->SetGUID(me->GetGUID(), me->GetEntry());

                        m_events.ScheduleEvent(EVENT_INITIALISE, 1000);
                    }
                    break;
                }
                case EVENT_GLOBAL_RESET:
                {
                    RemoveMyMember();
                    me->DespawnOrUnsummon(100);
                    break;
                }
                case EVENT_CHECK_FOR_TIMER:
                {
                    if (m_point < m_waveSize)
                    {
                        uint32 a = m_events.GetNextEventTime(EVENT_MOVE_WAVE);
                        uint32 b = m_events.GetNextEventTime(EVENT_FIGHT_WAVE);
                        if (!a && !b)
                        {
                            m_ai_counter += 1;
                            if (m_ai_counter > 30)
                                m_events.RescheduleEvent(EVENT_FIGHT_WAVE, m_shootCoolDown);
                        }
                    }
                    m_events.ScheduleEvent(EVENT_CHECK_FOR_TIMER, 1000);
                    break;
                }
                case EVENT_MOVE_WAVE:
                {
                    CheckForStartAction();
                    if (m_point < m_waveSize)
                    {
                        me->GetMotionMaster()->MovePoint(2000 + m_wave, GetWavePosition());
                    }
                    else if (Creature* almyra = sObjectAccessor->GetCreature(*me, m_almyraGUID))
                        almyra->AI()->DoAction(ACTION_MYRIAM_ARRIVED);
                    break;
                }
                case EVENT_FIGHT_WAVE:
                {
                    CheckForStartAction();
                    FindTargets();

                    if (m_nearestTarget)
                    {
                        Position pos = me->GetPosition();
                        if (GetWavePosition().GetExactDist2d(&pos) > 3.0f)
                        {
                            m_events.RescheduleEvent(EVENT_MOVE_WAVE, 500);
                        }
                        else if (m_nearestDistance > m_checkDistance)
                        {
                            m_point += 1;
                            m_events.RescheduleEvent(EVENT_MOVE_WAVE, 500);
                        }
                        else
                        {
                            me->SetFacingToObject(m_nearestTarget);
                            for (std::list<uint64>::const_iterator itr = my_followerList.begin(); itr != my_followerList.end(); ++itr)
                                if (Creature* follower = sObjectAccessor->GetCreature(*me, (*itr)))
                                {
                                    follower->SetFacingToObject(m_nearestTarget);
                                    if (m_nearestTarget->GetDistance2d(follower) > 5.0f)
                                        follower->CastSpell(m_nearestTarget, SPELL_GILNEAS_MILITIA_SHOOT);
                                    else
                                        follower->Attack(m_nearestTarget, true);
                                }
                            m_events.RescheduleEvent(EVENT_FIGHT_WAVE, m_shootCoolDown);
                        }
                    }
                    else
                    {
                        m_point += 1;
                        m_events.RescheduleEvent(EVENT_MOVE_WAVE, 10);
                    }
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void SummonMyMember()
        {
            for (uint32 i = 0; i < 19; ++i)
                if (Creature* summon = DoSummon(NPC_GILNEAN_MILITIA, SpawnPosGroup3[i], 0, TEMPSUMMON_DEAD_DESPAWN))
                    summon->SetReactState(REACT_PASSIVE);
        }

        void RemoveMyMember()
        {
            for (std::list<uint64>::const_iterator itr = my_followerList.begin(); itr != my_followerList.end(); ++itr)
                if (Creature* follower = sObjectAccessor->GetCreature(*me, (*itr)))
                    follower->DespawnOrUnsummon(10);
            my_followerList.clear();
        }

        void BuildFollowerGroup()
        {
            for (std::list<uint64>::const_iterator itr = my_followerList.begin(); itr != my_followerList.end(); ++itr)
                if (Creature* follower = sObjectAccessor->GetCreature(*me, (*itr)))
                {
                    float dist = frand(1.0f, 3.0f);
                    float angl = frand(0.0f, M_PI * 2);
                    follower->GetMotionMaster()->MoveFollow(me, dist, angl);
                    follower->AI()->SetGUID(me->GetGUID(), NPC_LEADER_GUID);
                }
        }

        void FindTargets()
        {
            m_targetList = me->FindAllUnfriendlyCreaturesInRange(25.0f);
            if (m_targetList.empty())
            {
                m_nearestTarget = nullptr;
                m_nearestDistance = 0;
            }
            else
            {
                m_nearestTarget = *m_targetList.begin();
                m_nearestDistance = m_nearestTarget->GetDistance2d(me);
                for (std::list<Creature*>::const_iterator itr = m_targetList.begin(); itr != m_targetList.end(); ++itr)
                {
                    float dist2 = (*itr)->GetDistance2d(me);
                    if (dist2 < m_nearestDistance)
                    {
                        m_nearestTarget = (*itr);
                        m_nearestDistance = dist2;
                    }
                }
            }

            m_checkDistance = 15.0f;
            if (m_nearestTarget)
                if (m_nearestTarget->GetEntry() == NPC_GOREROT)
                    m_checkDistance = 16.0f;
                else if (m_nearestTarget->GetEntry() == NPC_LADY_SYLVANAS_WINDRUNNER)
                    m_checkDistance = 25.0f;
        }

        Position GetWavePosition()
        {
            switch (m_wave)
            {
            case 1:
                return MSWave1Pos[m_point];
            case 2:
                return MSWave2Pos[m_point];
            case 3:
                return MSWave3Pos[m_point];
            case 4:
                return MSWave4Pos[m_point];
            case 5:
                return MSWave5Pos[m_point];
            case 6:
                return Wave6Pos[m_point];
            case 7:
                return MSWave7Pos[m_point];
            default:
                return Position(0, 0);
            }
        }

        void CheckForStartAction()
        {
            m_ai_counter = 0;
            switch (m_wave)
            {
            case 4:
            {
                if (m_point == 15)
                    m_shootCoolDown = 4000;
                break;
            }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_myriam_spellwaker_38465AI(creature);
    }
};

// 38426
class npc_lorna_crowley_38426 : public CreatureScript
{
public:
    npc_lorna_crowley_38426() : CreatureScript("npc_lorna_crowley_38426") { }

    struct npc_lorna_crowley_38426AI : public ScriptedAI
    {
        npc_lorna_crowley_38426AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        bool     m_isInitialised;
        uint64   m_almyraGUID;
        uint32   m_shootCoolDown;
        std::list<uint64> my_followerList;
        std::list<uint64> my_cannonList;
        std::list<uint64> my_cannonerList;
        std::list<uint64> my_victimList;
        std::list<Creature*> m_targetList;
        uint32    m_wave;
        uint32    m_waveSize;
        uint32    m_point;
        Creature* m_nearestTarget;
        float     m_nearestDistance;
        float     m_checkDistance;
        bool      m_doneA, m_doneB;
        uint32    m_ai_counter;

        void Initialize()
        {
            m_events.Reset();
            m_almyraGUID = 0;
            m_isInitialised = false;
            m_shootCoolDown = 4000;
            m_ai_counter = 0;
            m_events.ScheduleEvent(EVENT_INITIALISE, 1000);
            m_events.ScheduleEvent(EVENT_CHECK_FOR_TIMER, 1000);
        }

        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
            if (my_followerList.empty())
                SummonMyMember();
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            damage = 0;
        }

        void JustSummoned(Creature* summon) override
        {
            switch (summon->GetEntry())
            {
            case NPC_FREED_EMBERSTONE_VILLAGER:
                if (my_cannonerList.size() < 6)
                    my_cannonerList.push_back(summon->GetGUID());
                else
                    my_followerList.push_back(summon->GetGUID());
                break;
            case NPC_EMBERSTONE_CANNON:
                my_cannonList.push_back(summon->GetGUID());
                break;
            default:
                my_victimList.push_back(summon->GetGUID());
                break;
            }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == POINT_MOTION_TYPE)
                switch (id)
                {
                case 2003:
                case 2004:
                case 2005:
                case 2006:
                case 2007:
                {
                    m_events.RescheduleEvent(EVENT_FIGHT_WAVE, 250);
                    break;
                }
                }
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case ACTION_INITIALIZE_DONE:
            {
                m_isInitialised = true;
                break;
            }
            case ACTION_EVENT_RESET_TIMER:
            {
                m_events.RescheduleEvent(EVENT_GLOBAL_RESET, 10 * 60000);
                break;
            }
            case ACTION_MOVE_TO_WAVE_POSION_3:
            {
                BuildFollowerGroup();
                m_wave = 3;
                m_waveSize = 10;
                m_point = 0;
                m_doneA = false;
                m_doneB = false;
                m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                break;
            }
            case ACTION_MOVE_TO_WAVE_POSION_4:
            {
                m_shootCoolDown = 3000;
                m_wave = 4;
                m_waveSize = 31;
                m_point = 0;
                m_doneA = false; m_doneB = false;
                m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                break;
            }
            case ACTION_MOVE_TO_WAVE_POSION_5:
            {
                m_wave = 5;
                m_waveSize = 2;
                m_point = 0;
                m_doneA = false; m_doneB = false;
                m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                break;
            }
            case ACTION_MOVE_TO_WAVE_POSION_6:
            {
                m_wave = 6;
                m_waveSize = 21;
                m_point = 0;
                m_doneA = false; m_doneB = false;
                m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                break;
            }
            case ACTION_MOVE_TO_WAVE_POSION_7:
            {
                m_wave = 7;
                m_waveSize = 4;
                m_point = 0;
                m_doneA = false; m_doneB = false;
                m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                break;
            }
            case ACTION_SYLVANAS_HAS_ENOUGH:
            {
                m_events.CancelEvent(EVENT_MOVE_WAVE);
                m_events.CancelEvent(EVENT_FIGHT_WAVE);
                m_events.CancelEvent(EVENT_CHECK_FOR_TIMER);

                break;
            }
            case ACTION_QUEST_REWARDED:
            {
                RemoveMyMember();
                me->DespawnOrUnsummon();
                break;
            }
            }
        }

        void EnterEvadeMode() override { }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_INITIALISE:
                {
                    if (!m_isInitialised)
                    {
                        if (!m_almyraGUID)
                            if (Creature* almyra = me->FindNearestCreature(NPC_SISTER_ALMYRA, 250.0f))
                                m_almyraGUID = almyra->GetGUID();

                        if (Creature* almyra = sObjectAccessor->GetCreature(*me, m_almyraGUID))
                            almyra->AI()->SetGUID(me->GetGUID(), me->GetEntry());

                        m_events.ScheduleEvent(EVENT_INITIALISE, 1000);
                    }
                    break;
                }
                case EVENT_GLOBAL_RESET:
                {
                    RemoveMyMember();
                    me->DespawnOrUnsummon(100);
                    break;
                }
                case EVENT_CHECK_FOR_TIMER:
                {
                    if (m_point < m_waveSize)
                    {
                        uint32 a = m_events.GetNextEventTime(EVENT_MOVE_WAVE);
                        uint32 b = m_events.GetNextEventTime(EVENT_FIGHT_WAVE);
                        if (!a && !b)
                        {
                            m_ai_counter += 1;
                            if (m_ai_counter > 30)
                                m_events.RescheduleEvent(EVENT_FIGHT_WAVE, m_shootCoolDown);
                        }
                    }
                    m_events.ScheduleEvent(EVENT_CHECK_FOR_TIMER, 1000);
                    break;
                }
                case EVENT_MOVE_WAVE:
                {
                    CheckForStartAction();

                    if (m_point < m_waveSize)
                    {
                        me->GetMotionMaster()->MovePoint(2000 + m_wave, GetWavePosition());
                    }
                    else if (Creature* almyra = sObjectAccessor->GetCreature(*me, m_almyraGUID))
                        almyra->AI()->DoAction(ACTION_LORNA_ARRIVED);
                    break;
                }
                case EVENT_FIGHT_WAVE:
                {
                    CheckForStartAction();
                    FindTargets();

                    if (m_nearestTarget)
                    {
                        Position pos = me->GetPosition();
                        if (GetWavePosition().GetExactDist2d(&pos) > 3.0f)
                        {
                            m_events.RescheduleEvent(EVENT_MOVE_WAVE, 500);
                        }
                        else if (m_nearestDistance > m_checkDistance)
                        {
                            m_point += 1;
                            m_events.RescheduleEvent(EVENT_MOVE_WAVE, 500);
                        }
                        else
                        {
                            me->SetFacingToObject(m_nearestTarget);
                            for (std::list<uint64>::const_iterator itr = my_followerList.begin(); itr != my_followerList.end(); ++itr)
                                if (Creature* follower = sObjectAccessor->GetCreature(*me, (*itr)))
                                {
                                    follower->SetFacingToObject(m_nearestTarget);
                                    if (m_nearestTarget->GetDistance2d(follower) > 5.0f)
                                        follower->CastSpell(m_nearestTarget, SPELL_GILNEAS_MILITIA_SHOOT);
                                    else
                                        follower->Attack(m_nearestTarget, true);
                                }
                            m_events.RescheduleEvent(EVENT_FIGHT_WAVE, m_shootCoolDown);
                        }
                    }
                    else
                    {
                        m_point += 1;
                        m_events.RescheduleEvent(EVENT_MOVE_WAVE, 10);
                    }
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void SummonMyMember()
        {
            for (uint32 i = 0; i < 3; ++i)
                if (Creature* summon = DoSummon(NPC_EMBERSTONE_CANNON, SpawnPosEmberstoneCannon[i], 0, TEMPSUMMON_DEAD_DESPAWN))
                    summon->SetReactState(REACT_PASSIVE);

            for (uint32 i = 0; i < 15; ++i)
                if (Creature* summon = DoSummon(NPC_FREED_EMBERSTONE_VILLAGER, SpawnPosEmberstoneVillager[i], 0, TEMPSUMMON_DEAD_DESPAWN))
                    summon->SetReactState(REACT_PASSIVE);

            for (uint32 i = 0; i < 20; ++i)
                if (Creature* summon = DoSummon(NPC_VILE_ABOMINATION, SpawnPosVileAbomination[i], 0, TEMPSUMMON_DEAD_DESPAWN))
                    summon->SetReactState(REACT_PASSIVE);

            for (uint32 i = 0; i < 34; ++i)
                if (Creature* summon = DoSummon(NPC_FORSAKEN_CROSSBOWMAN, SpawnPosForsakenCrossbowMilitiaArea[i], 0, TEMPSUMMON_DEAD_DESPAWN))
                    summon->SetReactState(REACT_PASSIVE);

            for (uint32 i = 0; i < 5; ++i)
                if (Creature* summon = DoSummon(NPC_DAMAGED_CATAPULT, SpawnPosDamagedCatapult[i], 0, TEMPSUMMON_DEAD_DESPAWN))
                    summon->SetReactState(REACT_PASSIVE);

            for (uint32 i = 0; i < 2; ++i)
                if (Creature* summon = DoSummon(NPC_DARK_RANGER_ELITE, SpawnPosDarkRangerElite[i], 0, TEMPSUMMON_DEAD_DESPAWN))
                    summon->SetReactState(REACT_PASSIVE);

        }

        void RemoveMyMember()
        {
            for (std::list<uint64>::const_iterator itr = my_followerList.begin(); itr != my_followerList.end(); ++itr)
                if (Creature* follower = sObjectAccessor->GetCreature(*me, (*itr)))
                    follower->DespawnOrUnsummon(10);
            for (std::list<uint64>::const_iterator itr = my_cannonList.begin(); itr != my_cannonList.end(); ++itr)
                if (Creature* cannon = sObjectAccessor->GetCreature(*me, (*itr)))
                    cannon->DespawnOrUnsummon(10);
            for (std::list<uint64>::const_iterator itr = my_cannonerList.begin(); itr != my_cannonerList.end(); ++itr)
                if (Creature* helper = sObjectAccessor->GetCreature(*me, (*itr)))
                    helper->DespawnOrUnsummon(10);
            for (std::list<uint64>::const_iterator itr = my_victimList.begin(); itr != my_victimList.end(); ++itr)
                if (Creature* victim = sObjectAccessor->GetCreature(*me, (*itr)))
                    victim->DespawnOrUnsummon(10);
            my_followerList.clear();
            my_cannonList.clear();
            my_victimList.clear();
        }

        void BuildFollowerGroup()
        {
            if (my_cannonList.size() != 3 || my_cannonerList.size() != 6)
                return;

            std::list<uint64>::const_iterator itrC = my_cannonList.begin();
            std::list<uint64>::const_iterator itrM = my_cannonerList.begin();

            if (Creature* cannon1 = sObjectAccessor->GetCreature(*me, (*itrC)))
                if (Creature* helper1 = sObjectAccessor->GetCreature(*me, (*itrM)))
                {
                    ++itrM;
                    if (Creature* helper2 = sObjectAccessor->GetCreature(*me, (*itrM)))
                    {
                        helper1->GetMotionMaster()->MoveFollow(cannon1, 1.0f, 4.71f);
                        helper2->GetMotionMaster()->MoveFollow(cannon1, 1.0f, 1.57f);
                        cannon1->GetMotionMaster()->MoveFollow(me, 2.0f, 2.14f);
                    }
                }
            ++itrC;
            ++itrM;
            if (Creature* cannon1 = sObjectAccessor->GetCreature(*me, (*itrC)))
                if (Creature* helper1 = sObjectAccessor->GetCreature(*me, (*itrM)))
                {
                    ++itrM;
                    if (Creature* helper2 = sObjectAccessor->GetCreature(*me, (*itrM)))
                    {
                        helper1->GetMotionMaster()->MoveFollow(cannon1, 1.0f, 4.71f);
                        helper2->GetMotionMaster()->MoveFollow(cannon1, 1.0f, 1.57f);
                        cannon1->GetMotionMaster()->MoveFollow(me, 2.0f, 4.14f);
                    }
                }
            ++itrC;
            ++itrM;
            if (Creature* cannon1 = sObjectAccessor->GetCreature(*me, (*itrC)))
                if (Creature* helper1 = sObjectAccessor->GetCreature(*me, (*itrM)))
                {
                    ++itrM;
                    if (Creature* helper2 = sObjectAccessor->GetCreature(*me, (*itrM)))
                    {
                        helper1->GetMotionMaster()->MoveFollow(cannon1, 1.0f, 4.71f);
                        helper2->GetMotionMaster()->MoveFollow(cannon1, 1.0f, 1.57f);
                        cannon1->GetMotionMaster()->MoveFollow(me, 4.0f, 3.14f);
                    }
                }

            for (std::list<uint64>::const_iterator itr = my_followerList.begin(); itr != my_followerList.end(); ++itr)
                if (Creature* follower = sObjectAccessor->GetCreature(*me, (*itr)))
                {
                    float dist = frand(3.0f, 5.0f);
                    float angl = frand(2.14f, 4.14f);
                    follower->GetMotionMaster()->MoveFollow(me, dist, angl);
                    follower->AI()->SetGUID(me->GetGUID(), NPC_LEADER_GUID);
                }
        }

        void FindTargets()
        {
            m_targetList = me->FindAllUnfriendlyCreaturesInRange(25.0f);
            if (m_targetList.empty())
            {
                m_nearestTarget = nullptr;
                m_nearestDistance = 0;
            }
            else
            {
                m_nearestTarget = *m_targetList.begin();
                m_nearestDistance = m_nearestTarget->GetDistance2d(me);
                for (std::list<Creature*>::const_iterator itr = m_targetList.begin(); itr != m_targetList.end(); ++itr)
                {
                    float dist2 = (*itr)->GetDistance2d(me);
                    if (dist2 < m_nearestDistance)
                    {
                        m_nearestTarget = (*itr);
                        m_nearestDistance = dist2;
                    }
                }
            }

            m_checkDistance = 15.0f;
            if (m_nearestTarget)
                if (m_nearestTarget->GetEntry() == NPC_GOREROT)
                    m_checkDistance = 16.0f;
                else if (m_nearestTarget->GetEntry() == NPC_LADY_SYLVANAS_WINDRUNNER)
                    m_checkDistance = 25.0f;
        }

        Position GetWavePosition()
        {
            switch (m_wave)
            {
            case 1:
            case 2:
                break;
            case 3:
                return LCWave3Pos[m_point];
            case 4:
                return LCWave4Pos[m_point];
            case 5:
                return LCWave5Pos[m_point];
            case 6:
                return Wave6Pos[m_point];
            case 7:
                return LCWave7Pos[m_point];
            default:
                break;
            }
            return Position(0, 0);
        }

        void CheckForStartAction()
        {
            m_ai_counter = 0;
            switch (m_wave)
            {
            case 3:
            {
                if (m_point == 2 && !m_doneA)
                {
                    Talk(0);
                    m_doneA = true;
                }
                else if (m_point == 7 && !m_doneB)
                {
                    m_doneB = true;
                    for (std::list<uint64>::const_iterator itr = my_cannonList.begin(); itr != my_cannonList.end(); ++itr)
                        if (Creature* cannon = sObjectAccessor->GetCreature(*me, (*itr)))
                        {
                            cannon->GetMotionMaster()->Clear();
                            cannon->SetFacingTo(3.24f);
                            cannon->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        }
                    for (std::list<uint64>::const_iterator itr = my_followerList.begin(); itr != my_followerList.end(); ++itr)
                        if (Creature* follower = sObjectAccessor->GetCreature(*me, (*itr)))
                            follower->SetSheath(SHEATH_STATE_RANGED);
                }
                break;
            }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_lorna_crowley_38426AI(creature);
    }
};

// 38415
class npc_lord_darius_crowley_38415 : public CreatureScript
{
public:
    npc_lord_darius_crowley_38415() : CreatureScript("npc_lord_darius_crowley_38415") { }

    struct npc_lord_darius_crowley_38415AI : public ScriptedAI
    {
        npc_lord_darius_crowley_38415AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        bool     m_isInitialised;
        uint64   m_almyraGUID;
        uint32 m_ridingWorgen;
        uint32   m_shootCoolDown;
        std::list<uint64> my_followerList;
        std::list<Creature*> m_targetList;
        uint32    m_wave;
        uint32    m_waveSize;
        uint32    m_point;
        Creature* m_nearestTarget;
        float     m_nearestDistance;
        float     m_checkDistance;
        bool      m_doneA, m_doneB;
        uint32    m_ai_counter;

        void Initialize()
        {
            m_events.Reset();
            m_almyraGUID = 0;
            m_isInitialised = false;
            m_ridingWorgen = 0;
            m_shootCoolDown = 4000;
            m_ai_counter = 0;
            m_events.ScheduleEvent(EVENT_INITIALISE, 1000);
            m_events.ScheduleEvent(EVENT_CHECK_FOR_TIMER, 1000);
        }

        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
            if (my_followerList.empty())
                SummonMyMember();
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            damage = 0;
        }

        void JustSummoned(Creature* summon) override
        {
            my_followerList.push_back(summon->GetGUID());
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == POINT_MOTION_TYPE)
                switch (id)
                {
                case 2003:
                case 2004:
                case 2005:
                case 2006:
                case 2007:
                {
                    m_events.RescheduleEvent(EVENT_FIGHT_WAVE, 250);
                    break;
                }
                }
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case ACTION_INITIALIZE_DONE:
            {
                m_isInitialised = true;
                break;
            }
            case ACTION_EVENT_RESET_TIMER:
            {
                m_events.RescheduleEvent(EVENT_GLOBAL_RESET, 10 * 60000);
                break;
            }
            case ACTION_MOVE_TO_MEET_POINT4:
            {
                BuildFollowerGroup();
                m_wave = 4;
                m_waveSize = 5;
                m_point = 0;
                m_doneA = false; m_doneB = false;
                m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                break;
            }
            case ACTION_MOVE_TO_WAVE_POSION_5:
            {
                m_wave = 5;
                m_waveSize = 1;
                m_point = 0;
                m_doneA = false; m_doneB = false;
                m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                m_events.ScheduleEvent(EVENT_DARIUS_TALK_2, 3000);
                break;
            }
            case ACTION_MOVE_TO_WAVE_POSION_6:
            {
                Talk(1);
                m_wave = 6;
                m_waveSize = 21;
                m_point = 0;
                m_doneA = false; m_doneB = false;
                m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                break;
            }
            case ACTION_MOVE_TO_WAVE_POSION_7:
            {
                m_wave = 7;
                m_waveSize = 4;
                m_point = 0;
                m_doneA = false; m_doneB = false;
                m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                break;
            }
            case ACTION_SYLVANAS_HAS_ENOUGH:
            {
                m_events.CancelEvent(EVENT_MOVE_WAVE);
                m_events.CancelEvent(EVENT_FIGHT_WAVE);
                m_events.CancelEvent(EVENT_CHECK_FOR_TIMER);

                break;
            }
            case ACTION_QUEST_REWARDED:
            {
                RemoveMyMember();
                me->DespawnOrUnsummon();
                break;
            }
            }
        }

        void EnterEvadeMode() override { }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_INITIALISE:
                {
                    if (!m_isInitialised)
                    {
                        if (!m_almyraGUID)
                            if (Creature* almyra = me->FindNearestCreature(NPC_SISTER_ALMYRA, 250.0f))
                                m_almyraGUID = almyra->GetGUID();

                        if (Creature* almyra = sObjectAccessor->GetCreature(*me, m_almyraGUID))
                            almyra->AI()->SetGUID(me->GetGUID(), me->GetEntry());

                        m_events.ScheduleEvent(EVENT_INITIALISE, 1000);
                    }
                    break;
                }
                case EVENT_GLOBAL_RESET:
                {
                    RemoveMyMember();
                    me->DespawnOrUnsummon(100);
                    break;
                }
                case EVENT_CHECK_FOR_TIMER:
                {
                    if (m_point < m_waveSize)
                    {
                        uint32 a = m_events.GetNextEventTime(EVENT_MOVE_WAVE);
                        uint32 b = m_events.GetNextEventTime(EVENT_FIGHT_WAVE);
                        if (!a && !b)
                        {
                            m_ai_counter += 1;
                            if (m_ai_counter > 30)
                                m_events.RescheduleEvent(EVENT_FIGHT_WAVE, m_shootCoolDown);
                        }
                    }
                    m_events.ScheduleEvent(EVENT_CHECK_FOR_TIMER, 1000);
                    break;
                }
                case EVENT_MOVE_WAVE:
                {
                    CheckForStartAction();
                    if (m_point < m_waveSize)
                    {
                        me->GetMotionMaster()->MovePoint(2000 + m_wave, GetWavePosition());
                    }
                    else if (Creature* almyra = sObjectAccessor->GetCreature(*me, m_almyraGUID))
                        almyra->AI()->DoAction(ACTION_DARIUS_ARRIVED);
                    break;
                }
                case EVENT_FIGHT_WAVE:
                {
                    CheckForStartAction();
                    FindTargets();

                    if (m_nearestTarget)
                    {
                        Position pos = me->GetPosition();
                        if (GetWavePosition().GetExactDist2d(&pos) > 3.0f)
                        {
                            m_events.RescheduleEvent(EVENT_MOVE_WAVE, 500);
                        }
                        else if (m_nearestDistance > m_checkDistance)
                        {
                            m_point += 1;
                            m_events.RescheduleEvent(EVENT_MOVE_WAVE, 500);
                        }
                        else
                        {
                            me->SetFacingToObject(m_nearestTarget);
                            for (std::list<uint64>::const_iterator itr = my_followerList.begin(); itr != my_followerList.end(); ++itr)
                                if (Creature* follower = sObjectAccessor->GetCreature(*me, (*itr)))
                                {
                                    follower->SetFacingToObject(m_nearestTarget);
                                    follower->Attack(m_nearestTarget, true);
                                }
                            m_events.RescheduleEvent(EVENT_FIGHT_WAVE, m_shootCoolDown);
                        }
                    }
                    else
                    {
                        m_point += 1;
                        m_events.RescheduleEvent(EVENT_MOVE_WAVE, 10);
                    }
                    break;
                }
                case EVENT_DARIUS_TALK_2:
                {
                    Talk(2);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void SummonMyMember()
        {
            for (uint32 i = 0; i < 15; ++i)
                if (Creature* summon = DoSummon(NPC_WORGEN_WARRIER, SpawnPosGroup5[i], 0, TEMPSUMMON_DEAD_DESPAWN))
                    summon->SetReactState(REACT_PASSIVE);
        }

        void RemoveMyMember()
        {
            for (std::list<uint64>::const_iterator itr = my_followerList.begin(); itr != my_followerList.end(); ++itr)
                if (Creature* follower = sObjectAccessor->GetCreature(*me, (*itr)))
                    follower->DespawnOrUnsummon(10);
            my_followerList.clear();
        }

        void BuildFollowerGroup()
        {
            for (std::list<uint64>::const_iterator itr = my_followerList.begin(); itr != my_followerList.end(); ++itr)
                if (Creature* follower = sObjectAccessor->GetCreature(*me, (*itr)))
                {
                    float dist = frand(3.0f, 5.0f);
                    float angl = frand(2.14f, 4.14f);
                    follower->GetMotionMaster()->MoveFollow(me, dist, angl);
                    follower->AI()->SetGUID(me->GetGUID(), NPC_LEADER_GUID);
                }
        }

        void FindTargets()
        {
            m_targetList = me->FindAllUnfriendlyCreaturesInRange(25.0f);
            if (m_targetList.empty())
            {
                m_nearestTarget = nullptr;
                m_nearestDistance = 0;
            }
            else
            {
                m_nearestTarget = *m_targetList.begin();
                m_nearestDistance = m_nearestTarget->GetDistance2d(me);
                for (std::list<Creature*>::const_iterator itr = m_targetList.begin(); itr != m_targetList.end(); ++itr)
                {
                    float dist2 = (*itr)->GetDistance2d(me);
                    if (dist2 < m_nearestDistance)
                    {
                        m_nearestTarget = (*itr);
                        m_nearestDistance = dist2;
                    }
                }
            }

            m_checkDistance = 15.0f;
            if (m_nearestTarget)
                if (m_nearestTarget->GetEntry() == NPC_GOREROT)
                    m_checkDistance = 16.0f;
                else if (m_nearestTarget->GetEntry() == NPC_LADY_SYLVANAS_WINDRUNNER)
                    m_checkDistance = 25.0f;
        }

        Position GetWavePosition()
        {
            switch (m_wave)
            {
            case 4:
                return DCWave4Pos[m_point];
            case 5:
                return DCWave5Pos[m_point];
            case 6:
                return Wave6Pos[m_point];
            case 7:
                return DCWave7Pos[m_point];
            default:
                break;
            }
            return Position(0, 0);
        }

        void CheckForStartAction()
        {
            m_ai_counter = 0;
            switch (m_wave)
            {
            case 4:
            {
                if (m_ridingWorgen < 3)
                {
                    // let some worgen ride the gorerot
                    // me->CastCustomSpell(VEHICLE_SPELL_RIDE_HARDCODED, SPELLVALUE_BASE_POINT0, i + 1, abo, false);
                }
                break;
            }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_lord_darius_crowley_38415AI(creature);
    }
};

// 38470 group 4 the king 
class npc_king_genn_greymane_38470 : public CreatureScript
{
public:
    npc_king_genn_greymane_38470() : CreatureScript("npc_king_genn_greymane_38470") { }

    struct npc_king_genn_greymane_38470AI : public ScriptedAI
    {
        npc_king_genn_greymane_38470AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        bool     m_isInitialised;
        uint64   m_almyraGUID;
        uint64   m_liam2GUID;
        uint32   m_shootCoolDown;
        std::list<uint64> my_followerList;
        std::list<Creature*> m_targetList;
        uint32    m_wave;
        uint32    m_waveSize;
        uint32    m_point;
        Creature* m_nearestTarget;
        float     m_nearestDistance;
        float     m_checkDistance;
        bool      m_doneA, m_doneB;
        uint32    m_ai_counter;

        void Initialize()
        {
            m_events.Reset();
            m_almyraGUID = 0;
            m_liam2GUID = 0;
            m_isInitialised = false;
            m_shootCoolDown = 4000;
            m_ai_counter = 0;
            m_events.ScheduleEvent(EVENT_INITIALISE, 1000);
            m_events.ScheduleEvent(EVENT_CHECK_FOR_TIMER, 1000);
        }

        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
            if (my_followerList.empty())
                SummonMyMember();
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            damage = 0;
        }

        void JustSummoned(Creature* summon) override
        {
            my_followerList.push_back(summon->GetGUID());
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == POINT_MOTION_TYPE)
                switch (id)
                {
                case 1002:
                    m_events.ScheduleEvent(EVENT_LIAM_DEATH_TALK1, 1000);
                    break;
                case 2007:
                {
                    m_events.RescheduleEvent(EVENT_FIGHT_WAVE, 250);
                    break;
                }
                }
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case ACTION_INITIALIZE_DONE:
            {
                m_isInitialised = true;
                break;
            }
            case ACTION_EVENT_RESET_TIMER:
            {
                m_events.RescheduleEvent(EVENT_GLOBAL_RESET, 10 * 60000);
                break;
            }
            case ACTION_MOVE_TO_WAVE_POSION_7:
            {
                Talk(0);
                BuildFollowerGroup();
                m_wave = 7;
                m_waveSize = 4;
                m_point = 0;
                m_doneA = false; m_doneB = false;
                m_events.ScheduleEvent(EVENT_MOVE_WAVE, 250);
                break;
            }
            case ACTION_KING_TALK_2:
            {
                Talk(2);
                break;
            }
            case ACTION_SYLVANAS_HAS_ENOUGH:
            {
                m_events.CancelEvent(EVENT_MOVE_WAVE);
                m_events.CancelEvent(EVENT_FIGHT_WAVE);
                m_events.CancelEvent(EVENT_CHECK_FOR_TIMER);

                break;
            }
            case ACTION_QUEST_REWARDED:
            {
                RemoveMyMember();
                me->DespawnOrUnsummon();
                break;
            }
            }
        }

        void EnterEvadeMode() override { }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_INITIALISE:
                {
                    if (!m_isInitialised)
                    {
                        if (!m_almyraGUID)
                            if (Creature* almyra = me->FindNearestCreature(NPC_SISTER_ALMYRA, 500.0f))
                                m_almyraGUID = almyra->GetGUID();

                        if (Creature* almyra = sObjectAccessor->GetCreature(*me, m_almyraGUID))
                        {
                            almyra->AI()->SetGUID(me->GetGUID(), me->GetEntry());

                            if (!m_liam2GUID)
                                m_liam2GUID = almyra->AI()->GetGUID(NPC_PRINCE_LIAM_GREYMANE);
                        }
                        m_events.ScheduleEvent(EVENT_INITIALISE, 1000);
                    }
                    break;
                }
                case EVENT_CHECK_FOR_TIMER:
                {
                    if (m_point < m_waveSize)
                    {
                        uint32 a = m_events.GetNextEventTime(EVENT_MOVE_WAVE);
                        uint32 b = m_events.GetNextEventTime(EVENT_FIGHT_WAVE);
                        if (!a && !b)
                        {
                            m_ai_counter += 1;
                            if (m_ai_counter > 30)
                                m_events.RescheduleEvent(EVENT_FIGHT_WAVE, m_shootCoolDown);
                        }
                    }
                    m_events.ScheduleEvent(EVENT_CHECK_FOR_TIMER, 1000);
                    break;
                }
                case EVENT_MOVE_WAVE:
                {
                    CheckForStartAction();
                    if (m_point < m_waveSize)
                    {
                        me->GetMotionMaster()->MovePoint(2000 + m_wave, GetWavePosition());
                    }
                    else if (Creature* almyra = sObjectAccessor->GetCreature(*me, m_almyraGUID))
                        almyra->AI()->DoAction(ACTION_LORNA_ARRIVED);
                    break;
                }
                case EVENT_FIGHT_WAVE:
                {
                    CheckForStartAction();
                    FindTargets();

                    if (m_nearestTarget)
                    {
                        Position pos = me->GetPosition();
                        if (GetWavePosition().GetExactDist2d(&pos) > 3.0f)
                        {
                            m_events.RescheduleEvent(EVENT_MOVE_WAVE, 500);
                        }
                        else if (m_nearestDistance > m_checkDistance)
                        {
                            m_point += 1;
                            m_events.RescheduleEvent(EVENT_MOVE_WAVE, 500);
                        }
                        else
                        {
                            me->SetFacingToObject(m_nearestTarget);
                            for (std::list<uint64>::const_iterator itr = my_followerList.begin(); itr != my_followerList.end(); ++itr)
                                if (Creature* follower = sObjectAccessor->GetCreature(*me, (*itr)))
                                {
                                    follower->SetFacingToObject(m_nearestTarget);
                                    if (m_nearestTarget->GetDistance2d(follower) > 5.0f)
                                        follower->CastSpell(m_nearestTarget, SPELL_GILNEAS_MILITIA_SHOOT);
                                    else
                                        follower->Attack(m_nearestTarget, true);
                                }
                            m_events.RescheduleEvent(EVENT_FIGHT_WAVE, m_shootCoolDown);
                        }
                    }
                    else
                    {
                        m_point += 1;
                        m_events.RescheduleEvent(EVENT_MOVE_WAVE, 10);
                    }
                    break;
                }
                case EVENT_LIAM_DEATH_TALK1:
                {
                    if (Creature* liam = sObjectAccessor->GetCreature(*me, m_liam2GUID))
                        liam->AI()->Talk(2);

                    m_events.ScheduleEvent(EVENT_LIAM_DEATH_TALK2, 5000);
                    break;
                }
                case EVENT_LIAM_DEATH_TALK2:
                {
                    if (Creature* liam = sObjectAccessor->GetCreature(*me, m_liam2GUID))
                        liam->AI()->Talk(3);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void SummonMyMember()
        {
            for (uint32 i = 0; i < 25; ++i)
                if (Creature* summon = DoSummon(NPC_GILNEAN_MILITIA, SpawnPosGroup4[i], 0, TEMPSUMMON_DEAD_DESPAWN))
                    summon->SetReactState(REACT_PASSIVE);
        }

        void RemoveMyMember()
        {
            for (std::list<uint64>::const_iterator itr = my_followerList.begin(); itr != my_followerList.end(); ++itr)
                if (Creature* follower = sObjectAccessor->GetCreature(*me, (*itr)))
                    follower->DespawnOrUnsummon(10);
            my_followerList.clear();
        }

        void BuildFollowerGroup()
        {
            for (std::list<uint64>::const_iterator itr = my_followerList.begin(); itr != my_followerList.end(); ++itr)
                if (Creature* follower = sObjectAccessor->GetCreature(*me, (*itr)))
                {
                    float dist = frand(3.0f, 5.0f);
                    float angl = frand(2.14f, 4.14f);
                    follower->GetMotionMaster()->MoveFollow(me, dist, angl);
                    follower->AI()->SetGUID(me->GetGUID(), NPC_LEADER_GUID);
                }
        }

        void FindTargets()
        {
            m_targetList = me->FindAllUnfriendlyCreaturesInRange(25.0f);
            if (m_targetList.empty())
            {
                m_nearestTarget = nullptr;
                m_nearestDistance = 0;
            }
            else
            {
                m_nearestTarget = *m_targetList.begin();
                m_nearestDistance = m_nearestTarget->GetDistance2d(me);
                for (std::list<Creature*>::const_iterator itr = m_targetList.begin(); itr != m_targetList.end(); ++itr)
                {
                    float dist2 = (*itr)->GetDistance2d(me);
                    if (dist2 < m_nearestDistance)
                    {
                        m_nearestTarget = (*itr);
                        m_nearestDistance = dist2;
                    }
                }
            }
        }

        Position GetWavePosition()
        {
            switch (m_wave)
            {
            case 7:
                return GGWave7Pos[m_point];
            default:
                break;
            }
            return Position(0, 0);
        }

        void CheckForStartAction()
        {
            m_ai_counter = 0;

        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_king_genn_greymane_38470AI(creature);
    }
};

// 38469
class npc_lady_sylvanas_windrunner_38469 : public CreatureScript
{
public:
    npc_lady_sylvanas_windrunner_38469() : CreatureScript("npc_lady_sylvanas_windrunner_38469") { }

    enum eNpc
    {
        SPELL_BANSHEE_QUEENS_WAIL = 72113,	// 58:50.000
        SPELL_DESPAWN_FORSAKEN = 72384,		// 58:50.000
        SPELL_AIMED_SHOOT = 72114,			// 58:51.000
        SPELL_LIAM_SYLVANAS_DUMMY = 72115,	// 59:01.000
        SPELL_SHOOT_LIAM = 72116,			// 59:01.000
        SPELL_LIAM_SLAIN_DUMMY = 72361,		// 59:01.000
        SPELL_BFGC_COMPLETE = 72349,		// 59:01.000
    };

    struct npc_lady_sylvanas_windrunner_38469AI : public ScriptedAI
    {
        npc_lady_sylvanas_windrunner_38469AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        bool     m_isInitialised;
        uint64   m_almyraGUID;
        uint64   m_liamGUID;
        uint64   m_kingGUID;
        std::list<uint64> my_followerList;

        void Initialize()
        {
            m_events.Reset();
            m_almyraGUID = 0;
            m_liamGUID = 0;
            m_kingGUID = 0;
            m_isInitialised = false;
            m_events.ScheduleEvent(EVENT_INITIALISE, 1000);
        }

        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
            if (my_followerList.empty())
                SummonMyMember();
        }

        void JustSummoned(Creature* summon) override
        {
            my_followerList.push_back(summon->GetGUID());
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == WAYPOINT_MOTION_TYPE)
                if (id == 2)
                {
                    RemoveMyMember();
                    me->DespawnOrUnsummon();
                }
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case ACTION_INITIALIZE_DONE:
            {
                m_isInitialised = true;
                break;
            }
            case ACTION_EVENT_RESET_TIMER:
            {
                m_events.RescheduleEvent(EVENT_GLOBAL_RESET, 10 * 60000);
                break;
            }
            case ACTION_SYLVANAS_HAS_ENOUGH:
            {
                Talk(0);
                m_events.ScheduleEvent(EVENT_SYLVANAS_ATTACK1, 1000);
                break;
            }
            case ACTION_AIM_AT_KING:
            {
                if (Creature* liam = sObjectAccessor->GetCreature(*me, m_liamGUID))
                    me->CastSpell(liam, SPELL_AIMED_SHOOT);
                Talk(3); // Let's see how brave Gilneas gets on without its stubborn leader!
                break;
            }
            case ACTION_SHOOT_AT_KING:
            {
                if (Creature* liam = sObjectAccessor->GetCreature(*me, m_liamGUID))
                {
                    me->CastSpell(liam, SPELL_SHOOT_LIAM, true);
                }

                break;
            }
            case ACTION_LIAM_IS_DEATH:
            {
                m_events.ScheduleEvent(EVENT_LIAM_IS_DEATH, 7000);
                break;
            }
            case ACTION_QUEST_REWARDED:
            {
                RemoveMyMember();
                me->DespawnOrUnsummon();
                break;
            }
            }
        }

        void EnterEvadeMode() override { }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_INITIALISE:
                {
                    if (!m_almyraGUID || !m_liamGUID || !m_kingGUID)
                        m_isInitialised = false;

                    if (!m_isInitialised)
                    {
                        if (!m_almyraGUID)
                            if (Creature* almyra = me->FindNearestCreature(NPC_SISTER_ALMYRA, 500.0f))
                                m_almyraGUID = almyra->GetGUID();

                        if (Creature* almyra = sObjectAccessor->GetCreature(*me, m_almyraGUID))
                        {
                            almyra->AI()->SetGUID(me->GetGUID(), me->GetEntry());

                            if (!m_liamGUID)
                                m_liamGUID = almyra->AI()->GetGUID(NPC_PRINCE_LIAM_GREYMANE);

                            if (!m_kingGUID)
                                m_kingGUID = almyra->AI()->GetGUID(NPC_KING_GENN_GREYMANE);
                        }

                        m_events.ScheduleEvent(EVENT_INITIALISE, 1000);
                    }
                    break;
                }
                case EVENT_SYLVANAS_ATTACK1:
                {
                    me->CastSpell(me, SPELL_BANSHEE_QUEENS_WAIL);
                    me->CastSpell(me, SPELL_DESPAWN_FORSAKEN);

                    if (Creature* liam = me->SummonCreature(NPC_PRINCE_LIAM_GREYMANE, -1634.62f, 1632.86f, 21.2116f, 4.44084f, TEMPSUMMON_MANUAL_DESPAWN))
                    {
                        m_liamGUID = liam->GetGUID();

                        if (Creature* almyra = sObjectAccessor->GetCreature(*me, m_almyraGUID))
                            almyra->AI()->SetGUID(liam->GetGUID(), liam->GetEntry());
                    }

                    m_events.ScheduleEvent(EVENT_SYLVANAS_ATTACK2, 1000);
                    break;
                }
                case EVENT_SYLVANAS_ATTACK2:
                {
                    if (Creature* liam = sObjectAccessor->GetCreature(*me, m_liamGUID))
                        liam->GetMotionMaster()->MovePath(3847401, false);
                    break;
                }
                case EVENT_LIAM_IS_DEATH:
                {
                    Talk(1);
                    std::list<Player*> playerList = me->FindNearestPlayers(50.0f);
                    for (std::list<Player*>::const_iterator itr = playerList.begin(); itr != playerList.end(); ++itr)
                        if ((*itr)->GetQuestStatus(QUEST_THE_BATTLE_FOR_GILNEAS_CITY) == QUEST_STATUS_INCOMPLETE)
                        {
                            me->CastSpell((*itr), SPELL_BFGC_COMPLETE);
                            (*itr)->KilledMonsterCredit(38854);
                        }

                    BuildFollowerGroup();
                    me->GetMotionMaster()->MovePath(3846901, false);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void SummonMyMember()
        {
            for (uint32 i = 0; i < 3; ++i)
                if (Creature* summon = DoSummon(NPC_SOULTETHERED_BANSHEE, SpawnPosSoultetheredBanshee[i], 0, TEMPSUMMON_DEAD_DESPAWN))
                    summon->SetReactState(REACT_PASSIVE);
        }

        void RemoveMyMember()
        {
            for (std::list<uint64>::const_iterator itr = my_followerList.begin(); itr != my_followerList.end(); ++itr)
                if (Creature* follower = sObjectAccessor->GetCreature(*me, (*itr)))
                    follower->DespawnOrUnsummon(10);
            my_followerList.clear();
        }

        void BuildFollowerGroup()
        {
            for (std::list<uint64>::const_iterator itr = my_followerList.begin(); itr != my_followerList.end(); ++itr)
                if (Creature* follower = sObjectAccessor->GetCreature(*me, (*itr)))
                {
                    float dist = frand(3.0f, 5.0f);
                    float angl = frand(2.14f, 4.14f);
                    follower->GetMotionMaster()->MoveFollow(me, dist, angl);
                }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_lady_sylvanas_windrunner_38469AI(creature);
    }
};

// 38473
class npc_soultethered_banshee_38473 : public CreatureScript
{
public:
    npc_soultethered_banshee_38473() : CreatureScript("npc_soultethered_banshee_38473") { }

    enum eNPC
    {
        EVENT_FOLLOW_LEADER = 300,
    };

    struct npc_soultethered_banshee_38473AI : public ScriptedAI
    {
        npc_soultethered_banshee_38473AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64 m_leaderGUID;

        void Initialize()
        {
            m_leaderGUID = 0;
            m_events.Reset();
        }

        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
            me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (summoner->GetEntry() == NPC_LADY_SYLVANAS_WINDRUNNER)
                m_leaderGUID = summoner->GetGUID();
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

        void EnterEvadeMode() override { }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case 1:
                {
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
        return new npc_soultethered_banshee_38473AI(creature);
    }
};

// 38474
class npc_prince_liam_greymane_38474 : public CreatureScript
{
public:
    npc_prince_liam_greymane_38474() : CreatureScript("npc_prince_liam_greymane_38474") { }

    enum eNPC
    {
        SPELL_SHOOT_LIAM = 72116,
        SPELL_LIAM_SLAIN_DUMMY = 72361,
    };

    struct npc_prince_liam_greymane_38474AI : public ScriptedAI
    {
        npc_prince_liam_greymane_38474AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_almyraGUID;
        uint64   m_kingGUID;
        uint64   m_sylvanaGUID;
        bool     m_isInitialised;

        void Initialize()
        {
            m_events.Reset();
            m_events.ScheduleEvent(EVENT_INITIALISE, 1000);
            m_almyraGUID = 0;
            m_kingGUID = 0;
            m_sylvanaGUID = 0;
            m_isInitialised = false;
        }

        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (caster->GetEntry() == NPC_LADY_SYLVANAS_WINDRUNNER)
                if (spell->Id == SPELL_SHOOT_LIAM)
                {
                    me->CastSpell(me, SPELL_LIAM_SLAIN_DUMMY);

                    if (Creature* sylvana = sObjectAccessor->GetCreature(*me, m_sylvanaGUID))
                        sylvana->AI()->DoAction(ACTION_LIAM_IS_DEATH);

                    if (Creature* king = sObjectAccessor->GetCreature(*me, m_kingGUID))
                    {
                        king->GetMotionMaster()->MovePoint(1002, -1680.864f, 1619.74f, 20.48808f);
                        king->AI()->Talk(1);
                    }
                }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == WAYPOINT_MOTION_TYPE)
                switch (id)
                {
                case 2:
                {
                    Talk(0);
                    if (Creature* sylvana = sObjectAccessor->GetCreature(*me, m_sylvanaGUID))
                        sylvana->AI()->DoAction(ACTION_AIM_AT_KING);
                    break;
                }
                case 3:
                {
                    if (Creature* sylvana = sObjectAccessor->GetCreature(*me, m_sylvanaGUID))
                        sylvana->AI()->DoAction(ACTION_SHOOT_AT_KING);

                    break;
                }
                }
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case ACTION_INITIALIZE_DONE:
            {
                m_isInitialised = true;
                break;
            }
            case ACTION_QUEST_REWARDED:
            {
                me->DespawnOrUnsummon();
                break;
            }
            }
        }

        void EnterEvadeMode() override { }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_INITIALISE:
                {
                    if (!m_almyraGUID || !m_sylvanaGUID || !m_kingGUID)
                        m_isInitialised = false;

                    if (!m_isInitialised)
                    {
                        if (!m_almyraGUID)
                            if (Creature* almyra = me->FindNearestCreature(NPC_SISTER_ALMYRA, 500.0f))
                                m_almyraGUID = almyra->GetGUID();

                        if (Creature* almyra = sObjectAccessor->GetCreature(*me, m_almyraGUID))
                        {
                            almyra->AI()->SetGUID(me->GetGUID(), me->GetEntry());

                            if (!m_sylvanaGUID)
                                m_sylvanaGUID = almyra->AI()->GetGUID(NPC_LADY_SYLVANAS_WINDRUNNER);

                            if (!m_kingGUID)
                                m_kingGUID = almyra->AI()->GetGUID(NPC_KING_GENN_GREYMANE);
                        }

                        m_events.ScheduleEvent(EVENT_INITIALISE, 1000);
                    }
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
        return new npc_prince_liam_greymane_38474AI(creature);
    }
};

// 38611
class npc_lorna_crowley_38611 : public CreatureScript
{
public:
    npc_lorna_crowley_38611() : CreatureScript("npc_lorna_crowley_38611") { }

    enum eNpc
    {
        QUEST_THE_HUNT_FOR_SYLVANAS = 24902,
        SPELL_FORCECAST_SUMMON_TOBIAS = 72471,
    };

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_THE_HUNT_FOR_SYLVANAS)
            creature->CastSpell(player, SPELL_FORCECAST_SUMMON_TOBIAS);

        return true;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* /*quest*/, uint32 /*opt*/)
    {
        if (Creature* almyra = creature->FindNearestCreature(NPC_SISTER_ALMYRA, 50.0f))
            almyra->AI()->DoAction(ACTION_QUEST_REWARDED);

        return false;
    }
};

// 38210
class npc_forsaken_crossbowman_38210 : public CreatureScript
{
public:
    npc_forsaken_crossbowman_38210() : CreatureScript("npc_forsaken_crossbowman_38210") { }

    struct npc_forsaken_crossbowman_38210AI : public ScriptedAI
    {
        npc_forsaken_crossbowman_38210AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;

        void Initialize()
        {
            m_events.Reset();
            m_events.ScheduleEvent(EVENT_FORSAKEN_CROSSBOW_SHOOT, 400);
        }

        void Reset() override
        {
            me->SetSheath(SHEATH_STATE_RANGED);
        }

        void EnterEvadeMode() override { }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_FORSAKEN_CROSSBOW_SHOOT:
                {
                    if (Unit* target = FindNearestTarget(25))
                    {
                        me->CastSpell(target, SPELL_FORSAKEN_CROSSBOW_SHOOT);
                        me->SetFacingToObject(target);
                        m_events.ScheduleEvent(EVENT_FORSAKEN_CROSSBOW_SHOOT, urand(900, 1500));
                        break;
                    }

                    m_events.ScheduleEvent(EVENT_FORSAKEN_CROSSBOW_SHOOT, 400);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        Unit* FindNearestTarget(float range)
        {
            Unit* target = nullptr;
            float dist = range;
            std::list<Creature*> targetList = me->FindAllUnfriendlyCreaturesInRange(range);
            Player* player = me->FindNearestPlayer(range);
            if (!targetList.empty())
            {
                for (std::list<Creature*>::const_iterator itr = targetList.begin(); itr != targetList.end(); ++itr)
                {
                    float d = (*itr)->GetDistance2d(me);
                    if (d < dist)
                    {
                        dist = d;
                        target = (*itr);
                    }
                }
            }
            if (player)
            {
                if (player->GetDistance2d(me) < dist)
                    target = player;
            }
            return target;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_forsaken_crossbowman_38210AI(creature);
    }
};

// 38464
class npc_dark_ranger_elite_38464 : public CreatureScript
{
public:
    npc_dark_ranger_elite_38464() : CreatureScript("npc_dark_ranger_elite_38464") { }

    struct npc_dark_ranger_elite_38464AI : public ScriptedAI
    {
        npc_dark_ranger_elite_38464AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;

        void Initialize()
        {
            m_events.Reset();
            m_events.ScheduleEvent(EVENT_FORSAKEN_CROSSBOW_SHOOT, 400);
            m_events.ScheduleEvent(EVENT_FORSAKEN_KNOCKBACK, 500);
        }

        void Reset() override
        {
            me->SetSheath(SHEATH_STATE_RANGED);
        }

        void EnterEvadeMode() override { }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_FORSAKEN_CROSSBOW_SHOOT:
                {
                    if (Creature* target = me->FindNearestCreature(NPC_GILNEAN_MILITIA, 20.0f))
                    {
                        me->CastSpell(target, SPELL_FORSAKEN_CROSSBOW_SHOOT);
                        me->SetFacingToObject(target);
                        m_events.ScheduleEvent(EVENT_FORSAKEN_CROSSBOW_SHOOT, urand(800, 1100));
                        break;
                    }
                    m_events.ScheduleEvent(EVENT_FORSAKEN_CROSSBOW_SHOOT, 400);
                    break;
                }
                case EVENT_FORSAKEN_KNOCKBACK:
                {
                    if (Creature* target = me->FindNearestCreature(NPC_GILNEAN_MILITIA, 4.5f))
                    {
                        me->CastSpell(me, SPELL_KNOCKBACK);
                        m_events.ScheduleEvent(EVENT_FORSAKEN_KNOCKBACK, 5000);
                        break;
                    }
                    m_events.ScheduleEvent(EVENT_FORSAKEN_KNOCKBACK, 500);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        Unit* FindNearestTarget(float range)
        {
            Unit* target = nullptr;
            float dist = range;
            std::list<Creature*> targetList = me->FindAllUnfriendlyCreaturesInRange(range);
            Player* player = me->FindNearestPlayer(range);
            if (!targetList.empty())
            {
                for (std::list<Creature*>::const_iterator itr = targetList.begin(); itr != targetList.end(); ++itr)
                {
                    float d = (*itr)->GetDistance2d(me);
                    if (d < dist)
                    {
                        dist = d;
                        target = (*itr);
                    }
                }
            }
            if (player)
            {
                if (player->GetDistance2d(me) < dist)
                    target = player;
            }
            return target;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_dark_ranger_elite_38464AI(creature);
    }
};

// 38420
class npc_vile_abomination_38420 : public CreatureScript
{
public:
    npc_vile_abomination_38420() : CreatureScript("npc_vile_abomination_38420") { }

    struct npc_vile_abomination_38420AI : public ScriptedAI
    {
        npc_vile_abomination_38420AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;

        void Initialize()
        {
            m_events.Reset();
        }

        void Reset() override
        {
            me->SetSheath(SHEATH_STATE_MELEE);
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (Unit* target = FindNearestTarget(5.0f))
            {
                me->Attack(target, true);
            }
        }

        void EnterEvadeMode() override { }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case 1:
                {
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        Unit* FindNearestTarget(float range)
        {
            Unit* target = nullptr;
            float dist = range;
            std::list<Creature*> targetList = me->FindAllUnfriendlyCreaturesInRange(range);
            Player* player = me->FindNearestPlayer(range);
            if (!targetList.empty())
            {
                for (std::list<Creature*>::const_iterator itr = targetList.begin(); itr != targetList.end(); ++itr)
                {
                    float d = (*itr)->GetDistance2d(me);
                    if (d < dist)
                    {
                        dist = d;
                        target = (*itr);
                    }
                }
            }
            if (player)
            {
                if (player->GetDistance2d(me) < dist)
                    target = player;
            }
            return target;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_vile_abomination_38420AI(creature);
    }
};

// 38221 
class npc_gilnean_militia_38221 : public CreatureScript
{
public:
    npc_gilnean_militia_38221() : CreatureScript("npc_gilnean_militia_38221") { }

    enum eNpc
    {
        EVENT_FOLLOW_LEADER = 300,
    };

    struct npc_gilnean_militia_38221AI : public ScriptedAI
    {
        npc_gilnean_militia_38221AI(Creature* pCreature) : ScriptedAI(pCreature) { Initialize(); }

        EventMap m_events;
        uint64   m_leaderGUID;

        void Initialize()
        {
            m_leaderGUID = 0;
        }

        void Reset()
        {
            me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) override
        {
            if (spell->Id == SPELL_KNOCKBACK)
            {
                m_events.ScheduleEvent(EVENT_FOLLOW_LEADER, 3000);
            }
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case NPC_LEADER_GUID:
            {
                m_leaderGUID = guid;
                break;
            }
            }
        }

        void EnterEvadeMode() override { }

        void UpdateAI(uint32 diff)
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_FOLLOW_LEADER:
                {
                    if (Creature* leader = sObjectAccessor->GetCreature(*me, m_leaderGUID))
                    {
                        float dist = frand(1.0f, 3.0f);
                        float angl = frand(0.0f, M_PI * 2);
                        me->GetMotionMaster()->MoveFollow(leader, dist, angl);
                    }
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

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_gilnean_militia_38221AI(pCreature);
    }
};

// 38425 
class npc_freed_emberstone_villager_38425 : public CreatureScript
{
public:
    npc_freed_emberstone_villager_38425() : CreatureScript("npc_freed_emberstone_villager_38425") { }

    struct npc_freed_emberstone_villager_38425AI : public ScriptedAI
    {
        npc_freed_emberstone_villager_38425AI(Creature* pCreature) : ScriptedAI(pCreature) { }

        void Reset()
        {
            me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
        }

        void EnterEvadeMode() override { }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_freed_emberstone_villager_38425AI(pCreature);
    }
};

// 38348
class npc_worgen_warrior_38348 : public CreatureScript
{
public:
    npc_worgen_warrior_38348() : CreatureScript("npc_worgen_warrior_38348") { }

    struct npc_worgen_warrior_38348AI : public ScriptedAI
    {
        npc_worgen_warrior_38348AI(Creature* pCreature) : ScriptedAI(pCreature) { Initialize(); }

        EventMap m_events;
        uint64 m_leaderGUID;

        void Initialize()
        {
            m_leaderGUID = 0;
        }

        void Reset()
        {
            me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
        }

        void EnterCombat(Unit* pWho)
        {
            if (pWho->GetEntry() == 38348)
            {
                me->CastSpell(pWho, 71921, true);
            }
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case NPC_LEADER_GUID:
            {
                m_leaderGUID = guid;
                break;
            }
            }
        }

        void EnterEvadeMode() override { }

        void UpdateAI(uint32 diff)
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case 1:
                {

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

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_worgen_warrior_38348AI(pCreature);
    }
};

// 38331
class npc_gorerot_38331 : public CreatureScript
{
public:
    npc_gorerot_38331() : CreatureScript("npc_gorerot_38331") { }

    enum eNpc
    {
        SPELL_SMASH = 71774,
        SPELL_THUNDERCLAP = 8078,
        EVENT_SMASH = 301,
        EVENT_THUNDERCLAP = 302,
        EVENT_SAY1 = 303,
    };

    struct npc_gorerot_38331AI : public ScriptedAI
    {
        npc_gorerot_38331AI(Creature* pCreature) : ScriptedAI(pCreature) { }

        EventMap m_events;

        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
            me->PlayDirectSound(23530);
            m_events.ScheduleEvent(EVENT_SAY1, 10000);
            m_events.ScheduleEvent(EVENT_SMASH, 13000);
            m_events.ScheduleEvent(EVENT_THUNDERCLAP, 21000);
        }

        void UpdateAI(uint32 diff)
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_SAY1:
                    Talk(0);
                    break;
                case EVENT_SMASH:
                {
                    std::list<Unit*> targetList = FindNearestTarget(5.0f, 5);
                    if (!targetList.empty())
                        for (std::list<Unit*>::const_iterator itr = targetList.begin(); itr != targetList.end(); ++itr)
                            me->CastSpell((*itr), SPELL_SMASH);

                    m_events.ScheduleEvent(EVENT_SMASH, 13000);
                    break;
                }
                case EVENT_THUNDERCLAP:
                {
                    Position p = me->GetPosition();
                    me->CastSpell(p.GetPositionX(), p.GetPositionY(), p.GetPositionZ(), SPELL_THUNDERCLAP, true);
                    m_events.ScheduleEvent(EVENT_THUNDERCLAP, 21000);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

        std::list<Unit*> FindNearestTarget(float range, uint8 maxCount)
        {
            std::list<Unit*> returnList;
            std::list<Creature*> targetList = me->FindAllUnfriendlyCreaturesInRange(range);
            Player* player = me->FindNearestPlayer(range);
            if (player)
            {
                if (player->GetDistance2d(me) < range)
                    returnList.push_back(player);
            }
            if (!targetList.empty())
            {
                for (std::list<Creature*>::const_iterator itr = targetList.begin(); itr != targetList.end(); ++itr)
                {
                    if ((*itr)->GetDistance2d(me) < range && returnList.size() < maxCount)
                        returnList.push_back((*itr));
                }
            }

            return returnList;
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_gorerot_38331AI(pCreature);
    }
};

// 72050
class spell_fiery_boulder_72050 : public SpellScriptLoader
{
public:
    spell_fiery_boulder_72050() : SpellScriptLoader("spell_fiery_boulder_72050") { }

    class IsFriendly
    {
    public:
        explicit IsFriendly(Unit const* caster) : _caster(caster) { }

        bool operator()(WorldObject* obj) const
        {
            if (Unit* unit = obj->ToUnit())
                return _caster->IsFriendlyTo(unit);

            return false;
        }

    private:
        Unit const* _caster;
    };

    class spell_fiery_boulder_72050_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_fiery_boulder_72050_SpellScript);

        void FilterTargets(std::list<WorldObject*>& unitList)
        {
            unitList.remove_if(IsFriendly(GetCaster()));
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_fiery_boulder_72050_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_fiery_boulder_72050_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_fiery_boulder_72050_SpellScript();
    }
};

// 71388
class spell_rapier_of_the_gilnean_patriots_71388 : public SpellScriptLoader
{
public:
    spell_rapier_of_the_gilnean_patriots_71388() : SpellScriptLoader("spell_rapier_of_the_gilnean_patriots_71388") { }

    class IsHostile
    {
    public:
        explicit IsHostile(Unit const* caster) : _caster(caster) { }

        bool operator()(WorldObject* obj) const
        {
            if (Unit* unit = obj->ToUnit())
                return _caster->IsHostileTo(unit);

            return false;
        }

    private:
        Unit const* _caster;
    };

    class spell_rapier_of_the_gilnean_patriots_71388_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rapier_of_the_gilnean_patriots_71388_SpellScript);

        void FilterTargets(std::list<WorldObject*>& unitList)
        {
            unitList.remove_if(IsHostile(GetCaster()));
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_rapier_of_the_gilnean_patriots_71388_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENTRY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_rapier_of_the_gilnean_patriots_71388_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_rapier_of_the_gilnean_patriots_71388_SpellScript();
    }
};

// 72116
class spell_shoot_liam_72116 : public SpellScriptLoader
{
public:
    spell_shoot_liam_72116() : SpellScriptLoader("spell_shoot_liam_72116") { }

    class spell_shoot_liam_72116_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_shoot_liam_72116_SpellScript);

        void CheckTarget(WorldObject*& target)
        {
            if (target)
                if (target->GetEntry() != 38474)
                    target = target->FindNearestCreature(38474, 25.0f);
        }

        void Register() override
        {
            OnObjectTargetSelect += SpellObjectTargetSelectFn(spell_shoot_liam_72116_SpellScript::CheckTarget, EFFECT_0, TARGET_UNIT_NEARBY_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_shoot_liam_72116_SpellScript();
    }
};

// phase 262144 ending with quest 24904, then phase 190 (2097152) is active.. starting with quest 24902 

enum eQuest24902
{
    NPC_TOBIAS_MISTMANTLE = 38507,
    NPC_LADY_SYLVANAS_WINDRUNNER_38530 = 38530,
    NPC_GENERAL_WARHOWL = 38533,
    NPC_HIGH_EXECUTOR_CRENSHAW = 38537,
    ACTION_SYLVANAS_START = 501,
    PLAYER_GUID = 99999,
};

// 38507
class npc_tobias_mistmantle_38507 : public CreatureScript
{
public:
    npc_tobias_mistmantle_38507() : CreatureScript("npc_tobias_mistmantle_38507") { }

    enum eNpc
    {
        NPC_FORSAKEN_GENERAL = 38617,
        NPC_FORSAKEN_SERGANT = 38618,
        SPELL_AI_CAST_HFS_MASTER = 72476,
        SPELL_SUMMON_GENERAL_WARHOWL = 72236,
        SPELL_SUMMON_SYLVANAS = 72238,
        SPELL_SUMMON_MASTER = 72239,
        SPELL_SUMMON_CRENSHAW = 72245,
        EVENT_MOVEMENT_START_PATH_1 = 301,
        EVENT_MOVEMENT_START_PATH_2,
        EVENT_MOVEMENT_START_PATH_3,
        EVENT_MOVEMENT_START_PATH_4,
        EVENT_MOVEMENT_START_PATH_5,
        EVENT_MOVEMENT_START_PATH_6,
        EVENT_MOVEMENT_START_SYLVANAS_AI,
        EVENT_WAIT_FOR_PLAYER_1,
        EVENT_WAIT_FOR_PLAYER_2,
        EVENT_WAIT_FOR_PLAYER_3,
        EVENT_WAIT_FOR_PLAYER_4,
        EVENT_WAIT_FOR_OUTSIDE_EVENT,
        EVENT_WAIT_FOR_OUTSIDE_EVENT1,
    };

    struct npc_tobias_mistmantle_38507AI : public ScriptedAI
    {
        npc_tobias_mistmantle_38507AI(Creature* pCreature) : ScriptedAI(pCreature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_sylvanasGUID;
        uint64   m_warhowlGUID;
        uint64   m_crenshawGUID;
        uint32   m_eventPhase;

        void Reset() override
        {
            m_playerGUID = 0;
            m_eventPhase = 0;
            m_sylvanasGUID = 0;
            m_warhowlGUID = 0;
            m_crenshawGUID = 0;
        }

        void IsSummonedBy(Unit* summoner) override
        {
            m_playerGUID = summoner->GetGUID();
            m_eventPhase = 1;
            m_events.ScheduleEvent(EVENT_WAIT_FOR_PLAYER_1, 3000);
        }

        void JustSummoned(Creature* summon) override
        {
            summon->SetWalk(true);
            switch (summon->GetEntry())
            {
            case NPC_LADY_SYLVANAS_WINDRUNNER_38530:
                m_sylvanasGUID = summon->GetGUID();
                me->SetFacingToObject(summon);
                summon->AI()->SetGUID(me->GetGUID(), me->GetEntry());
                summon->AI()->SetGUID(m_playerGUID, PLAYER_GUID);
                summon->AI()->DoAction(ACTION_SYLVANAS_START);
                summon->GetMotionMaster()->MovePoint(2005, -1600.11f, 1518.04f, 29.24f);
                break;
            case NPC_GENERAL_WARHOWL:
                m_warhowlGUID = summon->GetGUID();
                summon->GetMotionMaster()->MovePoint(2006, -1593.35f, 1531.32f, 29.24f);
                break;
            case NPC_HIGH_EXECUTOR_CRENSHAW:
                m_crenshawGUID = summon->GetGUID();
                summon->GetMotionMaster()->MovePoint(2007, -1587.55f, 1519.32f, 29.24f);
                break;
            }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            switch (type)
            {
            case WAYPOINT_MOTION_TYPE:
            {
                if (m_eventPhase == 1 && id == 0)
                    Talk(0);
                else if (m_eventPhase == 1 && id == 1)
                    m_events.ScheduleEvent(EVENT_MOVEMENT_START_PATH_1, 1000);
                else if (m_eventPhase == 2 && id == 0)
                    Talk(1);
                else if (m_eventPhase == 2 && id == 1)
                    m_events.ScheduleEvent(EVENT_WAIT_FOR_PLAYER_2, 1000); // on open gate
                else if (m_eventPhase == 3 && id == 3)
                    m_events.ScheduleEvent(EVENT_WAIT_FOR_PLAYER_3, 1000); // on wall 1
                else if (m_eventPhase == 4 && id == 5)
                    m_events.ScheduleEvent(EVENT_WAIT_FOR_OUTSIDE_EVENT, 1000);
                else if (m_eventPhase == 5 && id == 23)
                    m_events.ScheduleEvent(EVENT_WAIT_FOR_PLAYER_4, 1000); // inside water
                break;
            }
            case EFFECT_MOTION_TYPE: // jump
            {
                if (m_eventPhase == 1 && id == 2001)
                    m_events.ScheduleEvent(EVENT_MOVEMENT_START_PATH_2, 1000);
                else if (m_eventPhase == 3 && id == 2003)
                    m_events.ScheduleEvent(EVENT_MOVEMENT_START_PATH_4, 1000);
                else if (m_eventPhase == 5 && id == 2004)
                {
                    me->SetFacingTo(5.6f);
                    m_events.ScheduleEvent(EVENT_MOVEMENT_START_PATH_6, 10);
                    m_events.ScheduleEvent(EVENT_MOVEMENT_START_SYLVANAS_AI, 1000);
                }
                break;
            }
            }
        }

        void EnterEvadeMode() {};

        uint64 GetGUID(int32 id) const override
        {
            switch (id)
            {
            case NPC_TOBIAS_MISTMANTLE:
                return me->GetGUID();
            case NPC_LADY_SYLVANAS_WINDRUNNER_38530:
                return m_sylvanasGUID;
            case NPC_GENERAL_WARHOWL:
                return m_warhowlGUID;
            case NPC_HIGH_EXECUTOR_CRENSHAW:
                return m_crenshawGUID;
            case PLAYER_GUID:
                return m_playerGUID;
            }
            return 0;
        }

        void UpdateAI(uint32 diff)
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_WAIT_FOR_PLAYER_1:
                {
                    if (IsPlayerNear(20.0f))
                        me->GetMotionMaster()->MovePath(3850701, false);
                    else
                        m_events.ScheduleEvent(EVENT_WAIT_FOR_PLAYER_1, 1000);
                    break;
                }
                case EVENT_MOVEMENT_START_PATH_1:
                {
                    me->GetMotionMaster()->MoveJump(-1601.925f, 1607.654f, 20.11606f, 20.0f, 20.0f, 2001);
                    break;
                }
                case EVENT_MOVEMENT_START_PATH_2:
                {
                    m_eventPhase = 2;
                    me->GetMotionMaster()->MovePath(3850702, false);
                    break;
                }
                case EVENT_WAIT_FOR_PLAYER_2:
                {
                    if (IsPlayerNear(8.0f))
                    {
                        m_eventPhase = 3;
                        me->GetMotionMaster()->MovePath(3850703, false);
                    }
                    else
                        m_events.ScheduleEvent(EVENT_WAIT_FOR_PLAYER_2, 1000);
                    break;
                }
                case EVENT_WAIT_FOR_PLAYER_3:
                {
                    if (IsPlayerNear(8.0f))
                        me->GetMotionMaster()->MoveJump(-1548.65f, 1618.41f, 23.1788f, 20.0f, 5.0f, 2003);
                    else
                        m_events.ScheduleEvent(EVENT_WAIT_FOR_PLAYER_3, 1000);
                    break;
                }
                case EVENT_MOVEMENT_START_PATH_4:
                {
                    m_eventPhase = 4;
                    me->GetMotionMaster()->MovePath(3850704, false);
                    break;
                }
                case EVENT_WAIT_FOR_OUTSIDE_EVENT:
                {
                    if (Creature* general = me->FindNearestCreature(NPC_FORSAKEN_GENERAL, 25.0f))
                        general->AI()->Talk(0);
                    m_events.ScheduleEvent(EVENT_WAIT_FOR_OUTSIDE_EVENT1, 6000);
                    break;
                }
                case EVENT_WAIT_FOR_OUTSIDE_EVENT1:
                {
                    Talk(2);
                    m_events.ScheduleEvent(EVENT_MOVEMENT_START_PATH_5, 6000);
                    break;
                }
                case EVENT_MOVEMENT_START_PATH_5:
                {
                    m_eventPhase = 5;
                    me->GetMotionMaster()->MovePath(3850705, false);
                    break;
                }
                case EVENT_WAIT_FOR_PLAYER_4:
                {
                    if (IsPlayerNear(8.0f))
                    {
                        Talk(3);
                        me->GetMotionMaster()->MoveJump(-1614.5f, 1533.9f, 27.26f, 20.0f, 5.0f, 2004);
                    }
                    else
                        m_events.ScheduleEvent(EVENT_WAIT_FOR_PLAYER_4, 1000);
                    break;
                }
                case EVENT_MOVEMENT_START_PATH_6:
                {
                    me->SetSwim(true);
                    me->GetMotionMaster()->MovePoint(2008, -1613.95f, 1536.012f, 27.4f);
                    break;
                }
                case EVENT_MOVEMENT_START_SYLVANAS_AI:
                {
                    // there are several summon spell, but all have the summoner position as spawnpoint.. 72476, 72239, 72236, 72238, 72245
                    me->SummonCreature(NPC_GENERAL_WARHOWL, -1566.053f, 1557.191f, 29.36808f, 4.273f, TEMPSUMMON_TIMED_DESPAWN, 180000);
                    me->SummonCreature(NPC_LADY_SYLVANAS_WINDRUNNER_38530, -1567.477f, 1554.569f, 29.36808f, 0.88f, TEMPSUMMON_TIMED_DESPAWN, 180000);
                    me->SummonCreature(NPC_HIGH_EXECUTOR_CRENSHAW, -1566.795f, 1555.300f, 29.36808f, 3.275f, TEMPSUMMON_TIMED_DESPAWN, 180000);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

        bool IsPlayerNear(float range)
        {
            if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                if (player->GetDistance2d(me) < range)
                    return true;
            return false;
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_tobias_mistmantle_38507AI(pCreature);
    }
};

// 38530
class npc_lady_sylvanas_windrunner_38530 : public CreatureScript
{
public:
    npc_lady_sylvanas_windrunner_38530() : CreatureScript("npc_lady_sylvanas_windrunner_38530") { }

    enum eNpc
    {
        EVENT_START_TALK = 401,
        EVENT_TALK_2,
        EVENT_TALK_3,
        EVENT_TALK_4,
        EVENT_TALK_5,
        EVENT_TALK_6,
        EVENT_TALK_7,
        EVENT_TALK_8,
        EVENT_END,
        EVENT_DESPAWN_WARHOWL,
        EVENT_DESPAWN,
    };

    struct npc_lady_sylvanas_windrunner_38530AI : public ScriptedAI
    {
        npc_lady_sylvanas_windrunner_38530AI(Creature* pCreature) : ScriptedAI(pCreature) { }

        EventMap m_events;
        uint64   m_playerGUID;
        uint64   m_tobiasGUID;
        uint64   m_sylvanasGUID;
        uint64   m_warhowlGUID;
        uint64   m_crenshawGUID;

        void Reset() override
        {
            m_playerGUID = 0;
            m_tobiasGUID = 0;
            m_sylvanasGUID = 0;
            m_warhowlGUID = 0;
            m_crenshawGUID = 0;
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (summoner->GetEntry() == NPC_TOBIAS_MISTMANTLE)
                m_tobiasGUID = summoner->GetGUID();
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == POINT_MOTION_TYPE)
                if (id == 2005)
                {
                    me->SetFacingTo(5.6f);
                    m_events.ScheduleEvent(EVENT_START_TALK, 1000);
                }
        }

        void EnterEvadeMode() {};

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case PLAYER_GUID:
                m_playerGUID = guid;
                break;
            case NPC_TOBIAS_MISTMANTLE:
                m_tobiasGUID = guid;
                break;
            }
        }

        void UpdateAI(uint32 diff)
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_TALK:
                {
                    if (Creature* tobias = sObjectAccessor->GetCreature(*me, m_tobiasGUID))
                    {
                        m_playerGUID = tobias->AI()->GetGUID(PLAYER_GUID);
                        m_warhowlGUID = tobias->AI()->GetGUID(NPC_GENERAL_WARHOWL);
                        m_crenshawGUID = tobias->AI()->GetGUID(NPC_HIGH_EXECUTOR_CRENSHAW);
                    }
                    if (Creature* warhowl = sObjectAccessor->GetCreature(*me, m_warhowlGUID))
                        warhowl->AI()->Talk(0);
                    m_events.ScheduleEvent(EVENT_TALK_2, 10000);
                    break;
                }
                case EVENT_TALK_2:
                {
                    if (Creature* warhowl = sObjectAccessor->GetCreature(*me, m_warhowlGUID))
                        me->SetFacingToObject(warhowl);
                    Talk(0);
                    m_events.ScheduleEvent(EVENT_TALK_3, 8000);
                    break;
                }
                case EVENT_TALK_3:
                {
                    if (Creature* warhowl = sObjectAccessor->GetCreature(*me, m_warhowlGUID))
                        warhowl->AI()->Talk(1);
                    m_events.ScheduleEvent(EVENT_TALK_4, 11000);
                    break;
                }
                case EVENT_TALK_4:
                {
                    Talk(1);
                    m_events.ScheduleEvent(EVENT_TALK_5, 14000);
                    break;
                }
                case EVENT_TALK_5:
                {
                    if (Creature* warhowl = sObjectAccessor->GetCreature(*me, m_warhowlGUID))
                        warhowl->AI()->Talk(2);
                    m_events.ScheduleEvent(EVENT_TALK_6, 8000);
                    break;
                }
                case EVENT_TALK_6:
                {
                    if (Creature* warhowl = sObjectAccessor->GetCreature(*me, m_warhowlGUID))
                        warhowl->GetMotionMaster()->MovePoint(2010, -1566.053f, 1557.191f, 29.36808f);
                    Talk(2);
                    m_events.ScheduleEvent(EVENT_DESPAWN_WARHOWL, 8000);
                    m_events.ScheduleEvent(EVENT_TALK_7, 5000);
                    break;
                }
                case EVENT_TALK_7:
                {
                    if (Creature* crenshaw = sObjectAccessor->GetCreature(*me, m_crenshawGUID))
                    {
                        crenshaw->AI()->Talk(0);
                        me->SetFacingToObject(crenshaw);
                    }
                    m_events.ScheduleEvent(EVENT_TALK_8, 10000);
                    break;
                }
                case EVENT_TALK_8:
                {
                    Talk(3);
                    m_events.ScheduleEvent(EVENT_END, 8000);
                    break;
                }
                case EVENT_END:
                {
                    if (Creature* crenshaw = sObjectAccessor->GetCreature(*me, m_crenshawGUID))
                        crenshaw->GetMotionMaster()->MovePoint(2010, -1566.053f, 1557.191f, 29.36808f);
                    me->GetMotionMaster()->MovePoint(2010, -1566.053f, 1557.191f, 29.36808f);
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        player->KilledMonsterCredit(38530);
                    m_events.ScheduleEvent(EVENT_DESPAWN, 8000);
                    break;
                }
                case EVENT_DESPAWN_WARHOWL:
                {
                    if (Creature* warhowl = sObjectAccessor->GetCreature(*me, m_warhowlGUID))
                        warhowl->DespawnOrUnsummon(10);
                    break;
                }
                case EVENT_DESPAWN:
                {
                    if (Creature* crenshaw = sObjectAccessor->GetCreature(*me, m_crenshawGUID))
                        crenshaw->DespawnOrUnsummon(10);
                    if (Creature* tobias = sObjectAccessor->GetCreature(*me, m_tobiasGUID))
                        tobias->DespawnOrUnsummon(10);
                    me->DespawnOrUnsummon(10);
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_lady_sylvanas_windrunner_38530AI(pCreature);
    }
};

// phase 2097152 is only for quest 24902, now the phase 524288 is active, startig with quest 24903

class npc_captured_riding_bat_38540 : public CreatureScript
{
public:
    npc_captured_riding_bat_38540() : CreatureScript("npc_captured_riding_bat_38540") { }

    enum eNpc
    {
        EVENT_START_WORK_AREA = 201,
        EVENT_TIMEOUT,
    };

    struct npc_captured_riding_bat_38540AI : public VehicleAI
    {
        npc_captured_riding_bat_38540AI(Creature* creature) : VehicleAI(creature) {}

        EventMap m_events;
        uint8    m_gamePhase;

        void AttackStart(Unit* /*who*/) {}
        void EnterCombat(Unit* /*who*/) {}
        void EnterEvadeMode() {}

        void Reset()
        {
            m_events.Reset();
            m_gamePhase = 0;
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type == WAYPOINT_MOTION_TYPE)
                if (m_gamePhase == 1 && id == 3)
                {
                    m_events.ScheduleEvent(EVENT_START_WORK_AREA, 10);
                    m_events.ScheduleEvent(EVENT_TIMEOUT, 120000);
                }
                else if (m_gamePhase == 3 && id == 3)
                {
                    if (Vehicle* bat = me->GetVehicleKit())
                        bat->RemoveAllPassengers();
                    me->DespawnOrUnsummon(10);
                }
        }

        void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply)
        {
            if (apply)
            {
                if (who->GetTypeId() == TYPEID_PLAYER)
                    if (who->ToPlayer()->GetQuestStatus(24920) != QUEST_STATUS_INCOMPLETE)
                    {
                        me->GetVehicleKit()->RemoveAllPassengers();
                        return;
                    }
                me->SetCanFly(true);
                me->SetDisableGravity(true);
                me->SetSpeed(MOVE_FLIGHT, 6.0f);
                me->GetMotionMaster()->MovePath(3854001, false);
                m_gamePhase = 1;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            VehicleAI::UpdateAI(diff);
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_WORK_AREA:
                {
                    me->SetSpeed(MOVE_FLIGHT, 4.0f);
                    m_gamePhase = 2;
                    me->GetMotionMaster()->MovePath(3854002, true);
                    break;
                }
                case EVENT_TIMEOUT:
                {
                    m_gamePhase = 3;
                    me->SetSpeed(MOVE_FLIGHT, 6.0f);
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MovePath(3854003, false);
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_captured_riding_bat_38540AI(creature);
    }
};

// 72849
class spell_fly_back_72849 : public SpellScriptLoader
{
public:
    spell_fly_back_72849() : SpellScriptLoader("spell_fly_back_72849") { }

    class spell_fly_back_72849_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_fly_back_72849_SpellScript);

        void HandleDummy(SpellEffIndex /*effindex*/)
        {
            if (Unit* caster = GetCaster())
                if (Creature* bat = caster->ToCreature())
                {
                    bat->SetSpeed(MOVE_FLIGHT, 6.0f);
                    bat->GetMotionMaster()->MovePath(3854003, false);
                }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_fly_back_72849_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_fly_back_72849_SpellScript();
    }
};

// 72247
class spell_iron_bomb_72247 : public SpellScriptLoader
{
public:
    spell_iron_bomb_72247() : SpellScriptLoader("spell_iron_bomb_72247") { }

    class IsFriendly
    {
    public:
        IsFriendly(Unit* caster) : _caster(caster) { }

        bool operator()(WorldObject* object) const
        {
            if (Unit* unit = object->ToUnit())
                return _caster->IsFriendlyTo(unit);
            return true;
        }

    private:
        Unit* _caster;
    };

    class spell_iron_bomb_72247_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_iron_bomb_72247_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if(IsFriendly(GetCaster()));
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_iron_bomb_72247_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_iron_bomb_72247_SpellScript();
    }
};

// the endgame is in phase 4194304

enum eEndGame
{
    QUEST_ENDGAME = 26706,
    QUEST_RUTTHERAN = 14434,

    NPC_HIPPOGRYPH = 43747,
    NPC_HIPPOGRYPH_AIR = 43751,
    NPC_WORGEN_WARRIOR = 43651,
    NPC_GILNEAN_SHARPSHOOTER = 43703,
    NPC_GUNSHIP_GRUNT = 42141,
    NPC_TOBIAS_MISTMANTLE_43749 = 43749,
    NPC_LORNA_CRAWLEY_43566 = 43566,
    NPC_GILNEAS_VEHICLE_ROPE = 43793,

    GO_WORGEN_GUNSHIP = 203428,
    GO_ROPE = 204428,

    ACTION_30_SEC_BEFORE_FIGHT = 25663,
    ACTION_15_SEC_BEFORE_FIGHT = 25727,
    ACTION_SHIP_ON_THE_WAY = 25664,
    ACTION_START_FEIGHTING_180_SEC = 25670,
    ACTION_START_LORNA_TALK = 401,

    EVENT_MAKE_SHOWFIGHT = 301,
    EVENT_START_SHOWFIGHT,
    EVENT_IS_BRIDGE_CLEAN,
    EVENT_START_ROPE_PART,
    EVENT_MASTER_RESET,

    SPELL_FOR_GILNEAS = 81790,
    SPELL_ROPE1 = 81974,
    SPELL_JUMP1 = 81421,
};

// 43749
class npc_tobias_mistmantle_43749 : public CreatureScript
{
public:
    npc_tobias_mistmantle_43749() : CreatureScript("npc_tobias_mistmantle_43749") { }

    enum eNPC
    {
        EVENTS_CHECK_TALKING_WAIT = 201,
        EVENTS_CHECK_TALKING_HIPPO,
        EVENTS_GET_INITIAL_VALUES,
    };

    struct npc_tobias_mistmantle_43749AI : public ScriptedAI
    {
        npc_tobias_mistmantle_43749AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        uint64   m_gunshipGUID;
        uint32   m_gunshipEventId;
        std::list<uint64> m_hippoList;

        void Initialize()
        {
            m_gunshipGUID = 0;
            m_gunshipEventId = 0;
            m_events.ScheduleEvent(EVENTS_GET_INITIAL_VALUES, 1000);
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case ACTION_30_SEC_BEFORE_FIGHT:
            case ACTION_15_SEC_BEFORE_FIGHT:
                m_events.ScheduleEvent(EVENTS_CHECK_TALKING_HIPPO, 10);
                break;
            case ACTION_SHIP_ON_THE_WAY:
            case ACTION_START_FEIGHTING_180_SEC:
                m_events.ScheduleEvent(EVENTS_CHECK_TALKING_WAIT, 10);
                break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENTS_GET_INITIAL_VALUES:
                {
                    if (GameObject* ship = sObjectAccessor->GetGameObject(*me, m_gunshipGUID))
                    {
                        m_gunshipGUID = ship->GetGUID();
                        ship->AI()->SetGUID(me->GetGUID(), me->GetEntry());
                        break;
                    }

                    FindWorgenGunshipWorldwide();
                    m_events.ScheduleEvent(EVENTS_GET_INITIAL_VALUES, 1000);
                    break;
                }
                case EVENTS_CHECK_TALKING_WAIT:
                {
                    Talk(1);
                    SetHippoSpellClick(false);
                    break;
                }
                case EVENTS_CHECK_TALKING_HIPPO:
                {
                    if (CheckPlayerForQuest() && CheckIsGunshipReady())
                    {
                        SetHippoSpellClick(true);
                        Talk(0);
                    }
                    else
                    {
                        SetHippoSpellClick(false);
                        Talk(1);
                    }
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        void FindNearestHippogryphs()
        {
            m_hippoList.clear();
            std::list<Creature*> hippoList = me->FindNearestCreatures(NPC_HIPPOGRYPH, 25.0f);
            for (std::list<Creature*>::iterator itr = hippoList.begin(); itr != hippoList.end(); ++itr)
                m_hippoList.push_back((*itr)->GetGUID());
        }

        void SetHippoSpellClick(bool value)
        {
            if (m_hippoList.empty())
            {
                std::list<Creature*> hippoList = me->FindNearestCreatures(NPC_HIPPOGRYPH, 15.0f);
                for (std::list<Creature*>::const_iterator itr = hippoList.begin(); itr != hippoList.end(); ++itr)
                    if (Creature* hippo = (*itr))
                        m_hippoList.push_back(hippo->GetGUID());
            }

            for (std::list<uint64>::iterator itr = m_hippoList.begin(); itr != m_hippoList.end(); ++itr)
                if (Creature* hippo = sObjectAccessor->GetCreature(*me, (*itr)))
                {
                    if (value)
                        hippo->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                    else
                        hippo->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                }
        }

        bool CheckPlayerForQuest()
        {
            std::list<Player*> playerList = me->FindNearestPlayers(25.0f);
            for (std::list<Player*>::iterator itr = playerList.begin(); itr != playerList.end(); ++itr)
                if ((*itr)->GetQuestStatus(QUEST_ENDGAME) == QUEST_STATUS_INCOMPLETE)
                    return true;
            return false;
        }

        void FindWorgenGunshipWorldwide()
        {
            TRINITY_READ_GUARD(HashMapHolder<GameObject>::LockType, *HashMapHolder<GameObject>::GetLock());
            HashMapHolder<GameObject>::MapType const& m = ObjectAccessor::GetGameObjects();
            for (HashMapHolder<GameObject>::MapType::const_iterator iter = m.begin(); iter != m.end(); ++iter)
                if (iter->second->IsInWorld() && iter->second->GetEntry() == GO_WORGEN_GUNSHIP)
                    m_gunshipGUID = iter->second->GetGUID();
        }

        bool CheckIsGunshipReady()
        {
            if (GameObject* ship = sObjectAccessor->GetGameObject(*me, m_gunshipGUID))
                if (Transport* transport = ship->ToTransport())
                {
                    uint32 count = transport->GetStaticPassengers().size();
                    return (count >= 39) ? true : false;
                }

            return false;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_tobias_mistmantle_43749AI(creature);
    }
};

// 43751
class npc_hippogryph_43751 : public CreatureScript
{
public:
    npc_hippogryph_43751() : CreatureScript("npc_hippogryph_43751") { }

    enum eNpc
    {
        SPELL_DANS_EJECT_PASSENGER = 51254,
        EVENT_MOVEMENT_START = 201,
        EVENT_MOVE_LAST_POINT,
        EVENT_EJECT_ALL_PASSENGER,
        EVENT_JUMP_TO_LORNA,
    };

    struct npc_hippogryph_43751AI : public VehicleAI
    {
        npc_hippogryph_43751AI(Creature* creature) : VehicleAI(creature) {}

        EventMap m_events;
        uint64 m_playerGUID;
        uint64 m_lornaGUID;
        float  m_maxSpeed;

        void EnterEvadeMode() {}

        void Reset()
        {
            m_events.Reset();
            m_playerGUID = 0;
            m_lornaGUID = 0;
            m_maxSpeed = 4.9f;
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            switch (type)
            {
            case WAYPOINT_MOTION_TYPE:
            {
                if (id == 2)
                    me->SetSpeed(MOVE_RUN, m_maxSpeed);
                else if (id == 6)
                    me->SetSpeed(MOVE_RUN, 2);
                else if (id == 7)
                    m_events.ScheduleEvent(EVENT_MOVE_LAST_POINT, 10);
                break;
            }
            case POINT_MOTION_TYPE:
            {
                if (id == 1002)
                {
                    m_events.ScheduleEvent(EVENT_EJECT_ALL_PASSENGER, 10);
                }
                break;
            }
            }
        }

        void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply)
        {
            if (apply)
            {
                if (Player* player = who->ToPlayer())
                    if (player->GetQuestStatus(QUEST_ENDGAME) == QUEST_STATUS_INCOMPLETE)
                    {
                        m_events.ScheduleEvent(EVENT_MOVEMENT_START, 2500);
                        m_playerGUID = who->GetGUID();
                        return;
                    }

                m_playerGUID = 0;
                if (Vehicle* hippo = me->GetVehicleKit())
                    hippo->RemoveAllPassengers();
            }
            else
                me->DespawnOrUnsummon(1000);
        }

        void UpdateAI(uint32 diff) override
        {
            VehicleAI::UpdateAI(diff);
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_MOVEMENT_START:
                {
                    me->SetCanFly(true);
                    me->SetDisableGravity(true);
                    me->SetSpeed(MOVE_RUN, 3);
                    me->GetMotionMaster()->MovePath(4375101, false);
                    break;
                }
                case EVENT_MOVE_LAST_POINT:
                {
                    FindLornaGuid();
                    if (Creature* lorna = sObjectAccessor->GetCreature(*me, m_lornaGUID))
                    {
                        Position pos = lorna->GetPosition();
                        pos.m_positionZ = me->GetPositionZ();
                        me->GetMotionMaster()->MovePoint(1002, pos);
                    }
                    break;
                }
                case EVENT_EJECT_ALL_PASSENGER:
                {
                    if (Vehicle* hippo = me->GetVehicleKit())
                        hippo->RemoveAllPassengers();

                    m_events.ScheduleEvent(EVENT_JUMP_TO_LORNA, 10);
                    break;
                }
                case EVENT_JUMP_TO_LORNA:
                {
                    if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                        if (Creature* lorna = sObjectAccessor->GetCreature(*me, m_lornaGUID))
                        {
                            lorna->AI()->DoAction(ACTION_START_LORNA_TALK);
                            player->JumpTo(lorna, 0.5f);
                        }
                        else
                        {
                            player->GetMotionMaster()->MoveJump(-1472.0f, 3250.0f, 180.0f, 20.0f, 0.4f);
                        }

                    m_playerGUID = 0;
                    me->DespawnOrUnsummon(2000);
                    break;
                }
                }
            }
        }

        void FindLornaGuid()
        {
            if (Creature* lorna = sObjectAccessor->GetCreature(*me, m_lornaGUID))
                if (lorna->GetDistance2d(me) > 50.0f)
                    m_lornaGUID = 0;

            if (!m_lornaGUID)
                if (Creature* lorna = me->FindNearestCreature(NPC_LORNA_CRAWLEY_43566, 25.0f))
                    m_lornaGUID = lorna->GetGUID();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hippogryph_43751AI(creature);
    }
};

// GO 203428
class go_worgen_gunship_203428 : public GameObjectScript
{
public:
    go_worgen_gunship_203428() : GameObjectScript("go_worgen_gunship_203428") { }

    enum eObject
    {
        EVENT_CHECK_POSITIONS = 201,
    };

    struct go_worgen_gunship_203428AI : public GameObjectAI
    {
        go_worgen_gunship_203428AI(GameObject* gameobject) : GameObjectAI(gameobject) { }

        EventMap m_events;
        uint64   m_tobiasGUID;
        uint64   m_playerGUID;
        uint64   m_lornaGUID;
        uint64   m_ropeGUID;

        void Reset() override
        {
            m_events.Reset();
            m_tobiasGUID = 0;
            m_playerGUID = 0;
            m_lornaGUID = 0;
            m_ropeGUID = 0;
            m_events.ScheduleEvent(EVENT_CHECK_POSITIONS, 2500);
        }

        void EventInform(uint32 eventId)
        {
            if (Creature* tobias = sObjectAccessor->GetCreature(*go, m_tobiasGUID))
                tobias->AI()->DoAction(eventId);
        }

        void SetGUID(uint64 guid, int32 id) override
        {
            switch (id)
            {
            case NPC_TOBIAS_MISTMANTLE_43749:
                m_tobiasGUID = guid;
                break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_CHECK_POSITIONS:
                {
                    if (!m_playerGUID)
                        if (Player* player = go->FindNearestPlayer(100.0f))
                            m_playerGUID = player->GetGUID();

                     m_events.ScheduleEvent(EVENT_CHECK_POSITIONS, 2500);
                    break;
                }
                }
            }
        }
    };

    GameObjectAI* GetAI(GameObject* gameobject) const override
    {
        return new go_worgen_gunship_203428AI(gameobject);
    }
};

// 43566
class npc_lorna_crowley_43566 : public CreatureScript
{
public:
    npc_lorna_crowley_43566() : CreatureScript("npc_lorna_crowley_43566") { }

    struct npc_lorna_crowley_43566AI : public ScriptedAI
    {
        npc_lorna_crowley_43566AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap  m_events;
        uint64    m_targetGUID;
        bool      m_doneA;
        bool      m_anim_is_started;
        std::list<Creature*>victimList;

        void Initialize()
        {
            m_anim_is_started = false;
            m_targetGUID = 0;
        }

        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
            m_doneA = false;
            if (!me->HasAura(SPELL_FOR_GILNEAS))
                me->AddAura(SPELL_FOR_GILNEAS, me);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (attacker->GetGUID() != m_targetGUID)
                m_targetGUID = attacker->GetGUID();

            switch (attacker->GetEntry())
            {
            case NPC_GUNSHIP_GRUNT:
                damage = 0;
                break;
            }
        }

        void DoAction(int32 param) override
        {
            switch (param)
            {
            case ACTION_START_LORNA_TALK:
                Talk(2);
                m_anim_is_started = true;
                SetRopeNotSelectableFlag(true);
                if (Transport* transport = me->GetTransport())
                    transport->EnableMovement(false);
                m_events.ScheduleEvent(EVENT_IS_BRIDGE_CLEAN, 2500);
                m_events.ScheduleEvent(EVENT_MASTER_RESET, 180000);
                break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_MASTER_RESET:
                {
                    Initialize();
                    me->DespawnOrUnsummon(10);
                    break;
                }
                case EVENT_IS_BRIDGE_CLEAN:
                {
                    uint32 count = IsBridgeClean();
                    if (count < 2 && !m_doneA)
                    {
                        m_doneA = true;
                        Talk(3);
                        m_events.ScheduleEvent(EVENT_IS_BRIDGE_CLEAN, 5000);
                        break;
                    }
                    else if (!count)
                    {
                        Talk(4);
                        SetRopeNotSelectableFlag(false);
                        m_events.ScheduleEvent(EVENT_START_ROPE_PART, 7000);
                        break;
                    }

                    m_events.ScheduleEvent(EVENT_IS_BRIDGE_CLEAN, 2500);
                    break;
                }
                case EVENT_START_ROPE_PART:
                {
                    SpawnGunshipOrcsWave2();
                    std::vector<Creature*> friendsList = FindFriendlyCreatureList();
                    std::vector<Creature*> jumpTargetList = FindJumpTargetPositions();
                    for (uint32 i = 0; i < friendsList.size(); i++)
                        friendsList[i]->JumpTo(jumpTargetList[i], 0.4f);

                    m_events.ScheduleEvent(11, 2000);
                    break;
                }
                case 11:
                {

                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        bool FindTarget()
        {
            m_targetGUID = 0;
            if (!IsPlayerInRange())
                return false;
            std::list<Creature*>m_targetList = me->FindAllUnfriendlyCreaturesInRange(40.0f);
            if (!m_targetList.empty())
            {
                Creature* m_nearestTarget = *m_targetList.begin();
                float m_nearestDistance = m_nearestTarget->GetDistance(me);
                for (std::list<Creature*>::const_iterator itr = m_targetList.begin(); itr != m_targetList.end(); ++itr)
                    if (isInSameHeight((*itr)->GetPosition()))
                    {
                        float dist2 = (*itr)->GetDistance(me);
                        if (dist2 < m_nearestDistance)
                        {
                            m_nearestTarget = (*itr);
                            m_nearestDistance = dist2;
                        }
                    }
                m_targetGUID = m_nearestTarget->GetGUID();
            }

            return (m_targetGUID) ? true : false;
        }

        bool IsPlayerInRange()
        {
            Player* player = me->FindNearestPlayer(50.0f);
            return player ? true : false;
        }

        bool isInSameHeight(Position pos)
        {
            float diff = abs(me->GetPositionZ() - pos.GetPositionZ());
            return (diff < 5) ? true : false;
        }

        uint32 IsBridgeClean()
        {
            uint32 count = 0;
            std::list<Creature*>m_targetList = me->FindAllUnfriendlyCreaturesInRange(75.0f);
            for (std::list<Creature*>::iterator itr = m_targetList.begin(); itr != m_targetList.end(); ++itr)
                if ((*itr)->GetTransOffsetZ() > 75.0f)
                    count += 1;

            return count;
        }

        void SetRopeNotSelectableFlag(bool value)
        {
            std::list<GameObject*> goList = me->FindNearestGameObjects(GO_ROPE, 30.0f); // there are 2 rope on bridge
            for (std::list<GameObject*>::const_iterator itr = goList.begin(); itr != goList.end(); ++itr)
                if (value)
                    (*itr)->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                else
                    (*itr)->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
        }

        std::vector<Creature*> FindFriendlyCreatureList()
        {
            std::vector<Creature*> rList;
            std::list<Creature*> tList = me->FindAllCreaturesInRange(12.0f);
            for (std::list<Creature*>::iterator itr = tList.begin(); itr != tList.end(); ++itr)
                if (Creature* target = (*itr))
                    if (isInSameHeight(target->GetPosition()) && target->IsAlive())
                        rList.push_back(target);

            return rList;
        }

        std::vector<Creature*> FindJumpTargetPositions()
        {
            std::vector<Creature*> rList;
            std::list<Creature*> tList = me->FindNearestCreatures(NPC_GILNEAS_VEHICLE_ROPE, 50.0f);
            for (std::list<Creature*>::iterator itr = tList.begin(); itr != tList.end(); ++itr)
                if (Creature* target = (*itr))
                    if (!isInSameHeight(target->GetPosition()))
                        rList.push_back(target);
            return rList;
        }

        void SpawnGunshipOrcsWave2()
        {
            // AddPassenger(42141, );
        }

        void AddPassenger(uint32 entry, float x, float y, float z, float o)
        {
            uint32 guid = sObjectMgr->GenerateLowGuid(HIGHGUID_UNIT);
            CreatureData& data = sObjectMgr->NewOrExistCreatureData(guid);
            data.id = entry;
            data.phaseMask = 4194304;
            data.posX = x;
            data.posY = y;
            data.posZ = z;
            data.orientation = o;
            data.mapid = 749;

            if (Transport* transport = me->GetTransport())
                if (Creature* creature = transport->CreateNPCPassenger(guid, &data))
                {
                    creature->SetReactState(REACT_AGGRESSIVE);
                }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_lorna_crowley_43566AI(creature);
    }
};

// 43651
class npc_worgen_warrior_43651 : public CreatureScript
{
public:
    npc_worgen_warrior_43651() : CreatureScript("npc_worgen_warrior_43651") { }

    struct npc_worgen_warrior_43651AI : public ScriptedAI
    {
        npc_worgen_warrior_43651AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap  m_events;
        uint64    m_targetGUID;
        float     m_targetDistance;
        uint64    m_playerGUID;

        void Initialize()
        {
            me->SetReactState(REACT_PASSIVE);
            m_playerGUID = 0;
            m_targetGUID = 0;
            m_targetDistance = 0;
            m_events.ScheduleEvent(EVENT_START_SHOWFIGHT, 5000);
        }

        void Reset() override
        {
            DoStartNoMovement(me);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            damage = 0;
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_SHOWFIGHT:
                {
                    m_events.ScheduleEvent(EVENT_MAKE_SHOWFIGHT, 1000);
                    break;
                }
                case EVENT_MAKE_SHOWFIGHT:
                {
                    if (me->IsInCombat())
                    {
                        if (Creature* target = sObjectAccessor->GetCreature(*me, m_targetGUID))
                            if (m_targetDistance < 5.0f)
                                me->CastSpell(target, SPELL_CLEAVE);
                    }
                    else if (FindTarget())
                        if (Creature* target = sObjectAccessor->GetCreature(*me, m_targetGUID))
                            if (m_targetDistance < 5.0f)
                                me->CastSpell(target, SPELL_CLEAVE);

                    m_events.ScheduleEvent(EVENT_MAKE_SHOWFIGHT, urand(900, 1200));
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        bool FindTarget()
        {
            m_targetGUID = 0;
            if (!IsPlayerInRange())
                return false;
            std::list<Creature*>m_targetList = me->FindAllUnfriendlyCreaturesInRange(5.0f);
            if (!m_targetList.empty())
            {
                Creature* m_nearestTarget = *m_targetList.begin();
                float m_nearestDistance = m_nearestTarget->GetDistance2d(me);
                for (std::list<Creature*>::const_iterator itr = m_targetList.begin(); itr != m_targetList.end(); ++itr)
                {
                    float dist2 = (*itr)->GetDistance2d(me);
                    if (dist2 < m_nearestDistance)
                    {
                        m_nearestTarget = (*itr);
                        m_nearestDistance = dist2;
                    }
                }
                if (m_nearestDistance < 5.0f)
                    m_targetGUID = m_nearestTarget->GetGUID();
            }

            return (m_targetGUID) ? true : false;
        }

        bool IsPlayerInRange()
        {
            Player* player = me->FindNearestPlayer(50.0f);
            return player ? true : false;
        }

        bool CheckPlayer()
        {
            if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                if (player->GetDistance(me) > 20.0f)
                    m_playerGUID = 0;
            if (!m_playerGUID)
                if (Player* player = me->FindNearestPlayer(20.0f))
                    m_playerGUID = player->GetGUID();
            return (m_playerGUID) ? true : false;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_worgen_warrior_43651AI(creature);
    }
};

// 43703
class npc_gilnean_sharpshooter_43703 : public CreatureScript
{
public:
    npc_gilnean_sharpshooter_43703() : CreatureScript("npc_gilnean_sharpshooter_43703") { }

    struct npc_gilnean_sharpshooter_43703AI : public ScriptedAI
    {
        npc_gilnean_sharpshooter_43703AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap  m_events;
        uint64    m_targetGUID;
        float     m_targetDistance;
        uint64    m_playerGUID;

        void Initialize()
        {

            m_playerGUID = 0;
            m_targetGUID = 0;
            m_targetDistance = 0;
            m_events.ScheduleEvent(EVENT_START_SHOWFIGHT, 5000);
        }

        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
            DoStartNoMovement(me);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            damage = 0;
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_START_SHOWFIGHT:
                {
                    m_events.ScheduleEvent(EVENT_MAKE_SHOWFIGHT, 1000);
                    break;
                }
                case EVENT_MAKE_SHOWFIGHT:
                {
                    if (me->IsInCombat())
                    {
                        if (Creature* target = sObjectAccessor->GetCreature(*me, m_targetGUID))
                            if (m_targetDistance > 5.0f)
                                me->CastSpell(target, SPELL_GILNEAS_MILITIA_SHOOT);
                            else
                            {
                                me->CastSpell(target, SPELL_CLEAVE);
                                if (!target->IsInCombat())
                                    target->Attack(me, true);
                            }
                    }
                    else
                        if (FindTarget())
                            if (Creature* target = sObjectAccessor->GetCreature(*me, m_targetGUID))
                                if (m_targetDistance > 5.0f)
                                    me->CastSpell(target, SPELL_GILNEAS_MILITIA_SHOOT);
                                else
                                {
                                    me->SetReactState(REACT_AGGRESSIVE);
                                    me->CastSpell(target, SPELL_CLEAVE);
                                    if (!target->IsInCombat())
                                        target->Attack(me, true);
                                }

                    m_events.ScheduleEvent(EVENT_MAKE_SHOWFIGHT, urand(900, 1200));
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }

        bool FindTarget()
        {
            m_targetGUID = 0;
            if (!IsPlayerInRange())
                return false;
            std::list<Creature*>m_targetList = me->FindAllUnfriendlyCreaturesInRange(40.0f);
            if (!m_targetList.empty())
            {
                Creature* m_nearestTarget = *m_targetList.begin();
                float m_nearestDistance = m_nearestTarget->GetDistance(me);
                for (std::list<Creature*>::const_iterator itr = m_targetList.begin(); itr != m_targetList.end(); ++itr)
                    if (isInSameHeight((*itr)->GetPosition()))
                    {
                        float dist2 = (*itr)->GetDistance(me);
                        if (dist2 < m_nearestDistance)
                        {
                            m_nearestTarget = (*itr);
                            m_nearestDistance = dist2;
                        }
                    }
                if (m_nearestDistance < 40.0f)
                {
                    m_targetGUID = m_nearestTarget->GetGUID();
                    m_targetDistance = m_nearestDistance;
                }
            }

            return (m_targetGUID) ? true : false;
        }

        bool IsPlayerInRange()
        {
            Player* player = me->FindNearestPlayer(50.0f);
            return player ? true : false;
        }

        bool isInSameHeight(Position pos)
        {
            float diff = abs(me->GetPositionZ() - pos.GetPositionZ());
            return (diff < 5) ? true : false;
        }

        bool CheckPlayer()
        {
            if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                if (player->GetDistance(me) > 20.0f)
                    m_playerGUID = 0;
            if (!m_playerGUID)
                if (Player* player = me->FindNearestPlayer(20.0f))
                    m_playerGUID = player->GetGUID();
            return (m_playerGUID) ? true : false;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_gilnean_sharpshooter_43703AI(creature);
    }
};

// 42141
class npc_gunship_grunt_42141 : public CreatureScript
{
public:
    npc_gunship_grunt_42141() : CreatureScript("npc_gunship_grunt_42141") { }

    struct npc_gunship_grunt_42141AI : public ScriptedAI
    {
        npc_gunship_grunt_42141AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

        EventMap m_events;
        Unit* m_target;
        uint64 m_playerGUID;

        void Initialize()
        {
            m_playerGUID = 0;
        }

        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
            m_target = nullptr;
            DoStartNoMovement(me);
        }

        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            if (IsPlayerInRange() && me->GetReactState() != REACT_AGGRESSIVE)
                me->SetReactState(REACT_AGGRESSIVE);
            damage *= 2;
        }

        bool IsPlayerInRange()
        {
            Player* player = me->FindNearestPlayer(50.0f);
            return player ? true : false;
        }

        void CheckPlayer()
        {
            if (Player* player = sObjectAccessor->GetPlayer(*me, m_playerGUID))
                if (player->GetDistance(me) > 20.0f)
                    m_playerGUID = 0;
            if (!m_playerGUID)
                if (Player* player = me->FindNearestPlayer(20.0f))
                    m_playerGUID = player->GetGUID();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_gunship_grunt_42141AI(creature);
    }
};

// GO 204428
class go_rope_204428 : public GameObjectScript
{
public:
    go_rope_204428() : GameObjectScript("go_rope_204428") { }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (Creature* target = FindRandomJumpTargetPosition(player))
            player->JumpTo(target, 0.4f);

        return true;
    }

    Creature* FindRandomJumpTargetPosition(Player* player)
    {
        float zHeight = player->GetPositionZ() - 10.0f;
        std::vector<Creature*> rList;
        std::list<Creature*> tList = player->FindNearestCreatures(NPC_GILNEAS_VEHICLE_ROPE, 50.0f);
        for (std::list<Creature*>::iterator itr = tList.begin(); itr != tList.end(); ++itr)
            if (Creature* target = (*itr))
                if (target->GetPositionZ() < zHeight)
                    rList.push_back(target);

        return (!rList.empty()) ? rList[urand(0, rList.size() - 1)] : nullptr;
    }
};

// 43727
class npc_lorna_crowley_43727 : public CreatureScript
{
public:
    npc_lorna_crowley_43727() : CreatureScript("npc_lorna_crowley_43727") { }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
    {
        if (quest->GetQuestId() == QUEST_ENDGAME)
        {
            creature->AI()->Talk(0);
        }
        return true;
    }
};

// 36616
class npc_admiral_nightwind_36616 : public CreatureScript
{
public:
    npc_admiral_nightwind_36616() : CreatureScript("npc_admiral_nightwind_36616") { }

    bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* quest, uint32 /*opt*/)
    {
        if (quest->GetQuestId() == QUEST_RUTTHERAN)
        {
            player->RemoveAllAuras();
            player->TeleportTo(1, 8343, 801, 4, 4.19f);
        }
        return true;
    }
};

void AddSC_zone_gilneas_city3()
{
    new npc_krennan_aranas_38553();
    new npc_marcus_37803();
    new npc_prince_liam_greymane_38218();
    new npc_myriam_spellwaker_38465();
    new npc_sister_almyra_38466();
    new npc_king_genn_greymane_38470();
    new npc_lady_sylvanas_windrunner_38469();
    new npc_soultethered_banshee_38473();
    new npc_lorna_crowley_38426();
    new npc_lord_darius_crowley_38415();
    new npc_gilnean_militia_38221();
    new npc_freed_emberstone_villager_38425();
    new npc_forsaken_crossbowman_38210();
    new npc_dark_ranger_elite_38464();
    new npc_vile_abomination_38420();
    new npc_worgen_warrior_38348();
    new npc_gorerot_38331();
    new npc_prince_liam_greymane_38474();
    new npc_lorna_crowley_38611();
    new spell_rapier_of_the_gilnean_patriots_71388();
    new spell_fiery_boulder_72050();
    new spell_shoot_liam_72116();
    new npc_tobias_mistmantle_38507();
    new npc_lady_sylvanas_windrunner_38530();
    new npc_captured_riding_bat_38540();
    new spell_fly_back_72849();
    new spell_iron_bomb_72247();
    new npc_tobias_mistmantle_43749();
    new npc_hippogryph_43751();
    new go_worgen_gunship_203428();
    new npc_lorna_crowley_43566();
    new npc_worgen_warrior_43651();
    new npc_gilnean_sharpshooter_43703();
    new npc_gunship_grunt_42141();
    // new go_rope_204428();
    new npc_lorna_crowley_43727();
    new npc_admiral_nightwind_36616();
}

