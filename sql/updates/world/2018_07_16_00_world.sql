
-- move 2 single values to free big area
delete from gameobject where id=180322 and guid in (401068, 401159);
delete from gameobject where guid in (401248, 401249);

-- in darnassus are some npc's on old place (335)

UPDATE creature SET position_x=9976.830, position_y=2214.60, position_z=1329.230, orientation=2.4609 WHERE guid=126896;

UPDATE creature SET position_x=9968.460, position_y=2234.550, position_z=1331.860, orientation=4.7298 WHERE guid=126845;

UPDATE creature SET position_x=9980.0, position_y=2222.560, position_z=1328.960, orientation=3.4907, spawntimesecs=300 WHERE guid=136293;

UPDATE creature SET position_x=9969.710, position_y=2225.180, position_z=1329.830, orientation=4.2586, spawntimesecs=300 WHERE guid=136294;

UPDATE creature SET position_x=9968.040, position_y=2221.810, position_z=1329.750, orientation=1.4486, spawntimesecs=300 WHERE guid=126978;

UPDATE creature SET position_x=9975.540, position_y=2221.80, position_z=1329.210, orientation=0.2443, spawntimesecs=300 WHERE guid=136306;

UPDATE creature SET position_x=9963.6670, position_y=2224.6410, position_z=1330.4310, orientation=4.9323, spawntimesecs=300 WHERE guid=126893;

UPDATE creature SET position_x=9965.4440, position_y=2213.5980, position_z=1329.5990, orientation=1.5943, spawntimesecs=300 WHERE guid=127084;

UPDATE creature SET position_x=9972.1720, position_y=2231.4390, position_z=1330.3440, orientation=3.7651, spawntimesecs=300 WHERE guid=126937;

UPDATE creature SET position_x=10003.720, position_y=2208.6780, position_z=1327.8970, orientation=0.1719, spawntimesecs=300 WHERE guid=142803;

delete from creature where id=26188 and guid=143091;

DELETE FROM creature WHERE id=25535 AND guid IN (142806, 142807, 142808, 142809, 142811);

-- in orgrimmar are some npc's on old place (335)

UPDATE creature SET position_x=2044.9460, position_y=-4332.3759, position_z=95.4710, orientation=2.3583, spawntimesecs=300 WHERE guid=127065; -- 26124

UPDATE creature SET position_x=2078.9006, position_y=-4337.3847, position_z=97.6711, orientation=3.1854, spawntimesecs=300 WHERE guid=126979; -- 16781

UPDATE creature SET position_x=2044.5999, position_y=-4322.0151, position_z=95.4712, orientation=3.3935, spawntimesecs=300 WHERE guid=126906; -- 16781

UPDATE creature SET position_x=2051.4436, position_y=-4330.4926, position_z=95.4712, orientation=2.8555, spawntimesecs=300 WHERE guid=127029; -- 16781

UPDATE creature SET position_x=2065.6572, position_y=-4323.7104, position_z=97.1524, orientation=3.2812, spawntimesecs=300 WHERE guid=127039; -- 17041

UPDATE creature SET position_x=2056.3359, position_y=-4326.2421, position_z=95.7476, orientation=6.2696, spawntimesecs=300 WHERE guid=127040; -- 17041

UPDATE creature SET position_x=2053.7114, position_y=-4339.5917, position_z=95.4880, orientation=0.3171, spawntimesecs=300 WHERE guid=127041; -- 25974

UPDATE creature SET position_x=2042.8073, position_y=-4336.2119, position_z=95.4760, orientation=2.8618, spawntimesecs=300 WHERE guid=127034; -- 26113

UPDATE creature SET position_x=2042.8619, position_y=-4318.0078, position_z=95.4717, orientation=3.5639, spawntimesecs=300 WHERE guid=127081; -- 16818

UPDATE creature SET position_x=2041.1571, position_y=-4324.5175, position_z=95.4712, orientation=2.3741, spawntimesecs=300 WHERE guid=127086; -- 26221

-- bonfire from 335 in thousend needles is under water
DELETE FROM creature WHERE guid IN (126948, 126956, 127027, 127028, 136331, 136332);

DELETE FROM gameobject WHERE guid IN (45339, 6207);

-- npc in teldrassil on 335 places
DELETE FROM creature WHERE guid IN (142848, 142849, 142855, 142856, 142857, 142858, 142859, 142860, 142861, 141956, 142871, 126894);

DELETE FROM gameobject WHERE guid IN (403686, 22029, 22040, 41836, 6213);

UPDATE creature SET position_x=8296.044922, position_y=1089.166382, position_z=2.900801, orientation=1.725771 WHERE guid=142897 AND id=10118;

UPDATE creature SET position_x=8317.887695, position_y=1081.029907, position_z=2.381111, orientation=0.738527 WHERE guid=143148 AND id=3607;

UPDATE CREATURE SET position_x=8346.242188, position_y=987.775757, position_z=19.588758, orientation=5.592271 WHERE guid=142213 AND id=7907;

UPDATE CREATURE SET position_x=8348.541016, position_y=986.309814, position_z=20.144920, orientation=2.637625 WHERE guid=142140 AND id=7916;

UPDATE CREATURE SET position_x=9963.396484, position_y=2237.128174, position_z=1332.788574, orientation=3.175617 WHERE guid=133462 AND id=26221;

