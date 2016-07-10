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
#include "ScriptedEscortAI.h"
#include "ScriptedFollowerAI.h"
#include "Vehicle.h"
#include "GameObjectAI.h"
#include "CreatureGroups.h"

enum eBattleForGilneas
{
	QUEST_PUSH_THEM_OUT = 24676,
	QUEST_THE_BATTLE_FOR_GILNEAS_CITY = 24904,

	NPC_KRENNAN_ARANAS = 38553,
	NPC_SISTER_ALMYRA = 38466,
	NPC_MYRIAM_SPELLWAKER = 38465,
	NPC_GILNEAN_MILITIA = 38221,
	NPC_PRINCE_LIAM_GREYMANE_BATTLE = 38218,
	NPC_LORNA_CROWLEY=38426,
	NPC_DAMAGED_CATAPULT = 38377,
	NPC_GOREROT = 38331,
	NPC_KING_GENN_GRAYMANE = 38470,
	NPC_LADY_SYLVANAS_WINDRUNNER = 38469,
	NPC_SOULTETHERED_BANSHEE = 38473,
	NPC_FORSAKEN_CROSSBOWMAN = 38210,
	NPC_EMBERSTONE_CANNON = 38424,
	NPC_FREED_EMBERSTONE_VILLAGER = 38425,
	NPC_DARK_RANGER_ELITE = 38464,
	NPC_VILE_ABOMINATION = 38420,

	ACTION_START_EVENT = 101,
	ACTION_SEND_DATA,
	ACTION_CHECK_READY_FOR_BATTLE,

	EVENT_GLOBAL_RESET = 201,
	EVENT_CHECK_PLAYER_FOR_PHASE,
	EVENT_INITIALISE,
	EVENT_BATTLE_IS_STARTED,

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

// 38426 -- Lorna Crowley
Position const SpawnPosLornaCrowley[1] =
{
	{-1549.21f, 1285.97f, 11.7804f, 3.47383f}
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
	{-1674.29f, 1446.18f, 52.3704f, 3.89208f}
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

// 38469 -- Lady Sylvanas Windrunner
Position const SpawnPosLadySylvanasWindrunner[1] =
{
	{-1678.06f, 1611.81f, 20.5728f, 2.44346f}
};

// 38473 -- Soultethered Banshee
Position const SpawnPosSoultetheredBanshee[3] =
{
	{-1683.02f, 1602.66f, 20.5689f, 1.55334f},
	{-1674.49f, 1607.05f, 20.5689f, 2.30383f},
	{-1670.25f, 1617.54f, 20.5728f, 3.31613f}
};

// 38470 -- King Genn Greymane
Position const SpawnPosKingGennGreymane[1] =
{
	{-1750.84f, 1670.42f, 22.1580f, 5.60220f}
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

		if (player->GetQuestStatus(QUEST_THE_BATTLE_FOR_GILNEAS_CITY) == QUEST_STATUS_INCOMPLETE)
			if (Creature* liam = creature->FindNearestCreature(NPC_PRINCE_LIAM_GREYMANE_BATTLE, 50.0f))
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

		void Reset()
		{
			m_events.Reset();
			m_events.ScheduleEvent(EVENT_CHECK_PLAYER_FOR_PHASE, 2500);
			m_almyraGUID = 0;
			m_battleIsStarted = false;
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

		uint64 GetGUID(int32 id) const override 
		{ 
			return 0; 
		}

		void SetData(uint32 id, uint32 value) override
		{
			switch (id)
			{
			case 1:
			{

				break;
			}
			}
		}

		uint32 GetData(uint32 id) const 
		{ 

			return 0; 
		}

		void UpdateAI(uint32 diff) override
		{
			m_events.Update(diff);

			while (uint32 eventId = m_events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_BATTLE_IS_STARTED:
				{
					m_battleIsStarted = false;
					break;
				}
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
				}
			}

			if (!UpdateVictim())
				return;
			else
				DoMeleeAttackIfReady();
		}

		void StartBattle(Player* player)
		{
			if (Creature* almyra = ObjectAccessor::GetCreature(*me, m_almyraGUID))
				if (almyra->IsAlive() && me->GetDistance2d(almyra->GetPositionX(), almyra->GetPositionY()) > 50)
					if (m_battleIsStarted)
						Talk(1);
					else
					{
						m_battleIsStarted = true;
						m_events.ScheduleEvent(EVENT_BATTLE_IS_STARTED, 300000);
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
		uint64   m_princeGUID;
		uint64   m_myriamGUID;
		uint64   m_lornaGUID;
		uint64   m_kingGUID;
		uint64   m_sylvanaGUID;
		std::list<uint64> my_summonList;

		void Initialize()
		{
			m_events.Reset();
			m_krennanGUID = 0;
			m_princeGUID = 0;
			m_myriamGUID = 0;
			m_lornaGUID = 0;
			m_kingGUID = 0;
			m_sylvanaGUID = 0;
			m_isInitialised = false;
			m_events.ScheduleEvent(EVENT_INITIALISE, 1000);
			SummonMyMember();
		}

		void Reset() override
		{
		}

		void JustSummoned(Creature* summon) override
		{
			my_summonList.push_back(summon->GetGUID());
		}

		void DoAction(int32 param) override
		{
			switch (param)
			{
			case ACTION_START_EVENT:
			{

				break;
			}
			}
		}

		void SetGUID(uint64 guid, int32 id) override
		{
			switch (id)
			{
			case NPC_PRINCE_LIAM_GREYMANE_BATTLE:
				m_princeGUID = guid;
				break;
			case NPC_MYRIAM_SPELLWAKER:
				m_myriamGUID = guid;
				break;
			case NPC_LORNA_CROWLEY:
				m_lornaGUID = guid;
				break;
			case NPC_KING_GENN_GRAYMANE:
				m_kingGUID = guid;
				break;
			case NPC_LADY_SYLVANAS_WINDRUNNER:
				m_sylvanaGUID = guid;
				break;
			}
		}

		uint64 GetGUID(int32 id) const override
		{
			switch (id)
			{
			case NPC_PRINCE_LIAM_GREYMANE_BATTLE:
				return m_princeGUID;
			case NPC_MYRIAM_SPELLWAKER:
				return m_myriamGUID;
			case NPC_LORNA_CROWLEY:
				return m_lornaGUID;
			case NPC_KING_GENN_GRAYMANE:
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
							break;
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

		void SummonMyMember()
		{
			for (uint32 i = 0; i < 19; ++i)
				if (Creature* summon = DoSummon(NPC_GILNEAN_MILITIA, SpawnPosGroup1[i], 0, TEMPSUMMON_DEAD_DESPAWN))
					summon->SetReactState(REACT_PASSIVE);

			for (uint32 i = 0; i < 32; ++i)
				if (Creature* summon = DoSummon(NPC_FORSAKEN_CROSSBOWMAN, SpawnPosForsakenCrossbowman[i], 0, TEMPSUMMON_DEAD_DESPAWN))
					summon->SetReactState(REACT_PASSIVE);
			
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
		std::list<uint64> my_summonList;

		void Initialize()
		{
			m_events.Reset();
			m_events.ScheduleEvent(EVENT_CHECK_PLAYER_FOR_PHASE, 2500);
			m_events.ScheduleEvent(EVENT_INITIALISE, 1000);
			m_almyraGUID = 0;
			m_isInitialised = false;
			SummonMyMember();
		}

		void Reset() override
		{
			if (!me->HasAura(458))
				me->AddAura(458, me);
			if (!me->HasAura(72069))
				me->AddAura(72069, me);
		}

		void JustSummoned(Creature* summon) override 
		{ 
			my_summonList.push_back(summon->GetGUID());
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
						{
							almyra->AI()->SetGUID(me->GetGUID(), me->GetEntry());
							break;
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
		 
		void SummonMyMember()
		{
			for (uint32 i = 0; i < 19; ++i)
				if (Creature* summon = DoSummon(NPC_GILNEAN_MILITIA, SpawnPosGroup2[i], 0, TEMPSUMMON_DEAD_DESPAWN))
					summon->SetReactState(REACT_PASSIVE);
		}

		void CheckForIsGroupReady()
		{

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
		std::list<uint64> my_summonList;

		void Initialize()
		{
			m_events.Reset();
			m_almyraGUID = 0;
			m_isInitialised = false;
			m_events.ScheduleEvent(EVENT_INITIALISE, 1000);
			SummonMyMember();
		}

		void Reset() override
		{

		}

		void JustSummoned(Creature* summon) override
		{
			my_summonList.push_back(summon->GetGUID());
		}

		void DoAction(int32 param) override
		{
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
						{
							almyra->AI()->SetGUID(me->GetGUID(), me->GetEntry());
							break;
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

		void SummonMyMember()
		{
			for (uint32 i = 0; i < 19; ++i)
				if (Creature* summon = DoSummon(NPC_GILNEAN_MILITIA, SpawnPosGroup3[i], 0, TEMPSUMMON_DEAD_DESPAWN))
					summon->SetReactState(REACT_PASSIVE);
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
		std::list<uint64> my_summonList;

		void Initialize()
		{
			m_events.Reset();
			m_almyraGUID=0;
			m_isInitialised = false;
			m_events.ScheduleEvent(EVENT_INITIALISE, 1000);
			SummonMyMember();
		}

		void Reset() override
		{
			
		}

		void JustSummoned(Creature* summon) override
		{
			my_summonList.push_back(summon->GetGUID());
		}

		void DoAction(int32 param) override
		{
			switch (param)
			{
			case 1:
				break;
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
							if (Creature* almyra = me->FindNearestCreature(NPC_SISTER_ALMYRA,250.0f))
								m_almyraGUID =almyra->GetGUID();

						if (Creature* almyra = sObjectAccessor->GetCreature(*me, m_almyraGUID))
						{
							almyra->AI()->SetGUID(me->GetGUID(), me->GetEntry());
							m_isInitialised=true;
							break;
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
	};

	CreatureAI* GetAI(Creature* creature) const override
	{
		return new npc_lorna_crowley_38426AI(creature);
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
		std::list<uint64> my_summonList;

		void Initialize()
		{
			m_events.Reset();
			m_almyraGUID = 0;
			m_isInitialised = false;
			m_events.ScheduleEvent(EVENT_INITIALISE, 1000);
			SummonMyMember();
		}

		void Reset() override
		{
		}

		void JustSummoned(Creature* summon) override
		{
			my_summonList.push_back(summon->GetGUID());
		}

		void DoAction(int32 param) override
		{
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
							break;
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

		void SummonMyMember()
		{
			for (uint32 i = 0; i < 25; ++i)
				if (Creature* summon = DoSummon(NPC_GILNEAN_MILITIA, SpawnPosGroup4[i], 0, TEMPSUMMON_DEAD_DESPAWN))
					summon->SetReactState(REACT_PASSIVE);
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

	struct npc_lady_sylvanas_windrunner_38469AI : public ScriptedAI
	{
		npc_lady_sylvanas_windrunner_38469AI(Creature* creature) : ScriptedAI(creature) { Initialize(); }

		EventMap m_events;
		bool     m_isInitialised;
		uint64   m_almyraGUID;
		std::list<uint64> my_summonList;

		void Initialize()
		{
			m_events.Reset();
			m_almyraGUID = 0;
			m_isInitialised = false;
			m_events.ScheduleEvent(EVENT_INITIALISE, 1000);
			SummonMyMember();
		}

		void Reset() override
		{

		}

		void JustSummoned(Creature* summon) override
		{
			my_summonList.push_back(summon->GetGUID());
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
							break;
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

		void SummonMyMember()
		{
			for (uint32 i = 0; i < 3; ++i)
				if (Creature* summon = DoSummon(NPC_SOULTETHERED_BANSHEE, SpawnPosSoultetheredBanshee[i], 0, TEMPSUMMON_DEAD_DESPAWN))
					summon->SetReactState(REACT_PASSIVE);
			
		}
	};

	CreatureAI* GetAI(Creature* creature) const override
	{
		return new npc_lady_sylvanas_windrunner_38469AI(creature);
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
		}

		void Reset() override
		{
			
		}

		void DoAction(int32 param) override
		{
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
		return new npc_forsaken_crossbowman_38210AI(creature);
	}
};

// old contend

// 38221
class npc_gilnean_militia_38221 : public CreatureScript
{
public:
	npc_gilnean_militia_38221() : CreatureScript("npc_gilnean_militia_38221") { }

	enum eNpc
	{
		DATA_GROUP = 101,
		GROUP_1,
	};

	struct npc_gilnean_militia_38221AI : public ScriptedAI
	{
		npc_gilnean_militia_38221AI(Creature* pCreature) : ScriptedAI(pCreature) { }

		void Reset()
		{
			mui_spell1 = urand(1200, 5100);
			mui_spell2 = urand(2100, 5400);
			me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
		}

		void AttackStart(Unit* who)
		{
			if (me->Attack(who, true))
				DoStartNoMovement(who);
		}

		void SetData(uint32 uiType, uint32 uiData)
		{
			if (uiType == DATA_GROUP)
				group = uiData;
		}

		uint32 GetData(uint32 uiType) const
		{
			if (uiType == DATA_GROUP)
				return group;
			return 0;
		}

		void JustReachedHome()
		{
			if (group == GROUP_1)
				if (!UpdateVictim())
					if (me->ToTempSummon())
						if (Unit *p = me->ToTempSummon()->GetSummoner())
						{
							float distance = urand(7, 15);
							float angle = frand(-3 * M_PI / 4, 3 * M_PI / 2);
							float x, y, z;
							me->GetNearPoint(p, x, y, z, p->GetObjectSize(), distance, angle);
							me->GetMotionMaster()->MoveFollow(p, distance, angle, MOTION_SLOT_ACTIVE);
						}
		}

		void UpdateAI(uint32 diff)
		{
			if (!UpdateVictim())
				return;
			if (mui_spell1 <= diff)
			{
				// 15572 Rüstung zerreißen. Hackt auf die Rüstung des Gegners ein und verringert sie pro Einsatz von 'Rüstung zerreißen'. 
				// Kann bis zu 5-mal angewendet werden. Hält $d lang an.
				DoCastVictim(15572); 
				mui_spell1 = 10000 + urand(1200, 5100);
			}
			else
				mui_spell1 -= diff;

			if (mui_spell2 <= diff)
			{
				// 47168 Verbessertes Zurechtstutzen. Description: Macht das Ziel $d lang bewegungsunfähig.
				DoCastVictim(47168);
				mui_spell2 = 10000 + urand(2100, 5400);
			}
			else
				mui_spell2 -= diff;

			// 3te fähigkeit: 6660 Schießen.  Description: Schießt auf den Feind und fügt körperlichen Schaden zu
			victim = me->GetVictim();
			if (victim && me->GetDistance2d(victim->GetPositionX(), victim->GetPositionY()) > 7)
				DoSpellAttackIfReady(6660);
			else
				DoMeleeAttackIfReady();
		}

	private:
		uint32 mui_spell1;
		uint32 mui_spell2;
		Unit *victim;
		uint32 group;
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_gilnean_militia_38221AI(pCreature);
	}
};

// 38348
class npc_worgen_warrior_38348 : public CreatureScript
{
public:
	npc_worgen_warrior_38348() : CreatureScript("npc_worgen_warrior_38348") { }

	struct npc_worgen_warrior_38348AI : public ScriptedAI
	{
		npc_worgen_warrior_38348AI(Creature* pCreature) : ScriptedAI(pCreature) { }

		void EnterCombat(Unit* pWho)
		{
			if (pWho->GetEntry() == 38348)
			{
				me->CastSpell(pWho, 71921, true);
			}
		}

		void UpdateAI(uint32 diff)
		{
			if (!UpdateVictim())
				return;

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_worgen_warrior_38348AI(pCreature);
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
	new npc_lorna_crowley_38426();
	new npc_gilnean_militia_38221();
	new npc_forsaken_crossbowman_38210();
	new npc_worgen_warrior_38348();
}

