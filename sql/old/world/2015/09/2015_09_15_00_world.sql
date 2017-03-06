
-- https://cata-twinhead.twinstar.cz/?npc=34884
update creature set phaseMask=2 where id=34884;

-- https://cata-twinhead.twinstar.cz/?npc=34864
update creature set phaseMask=1 where id=34864;

-- https://cata-twinhead.twinstar.cz/?npc=35504
update creature set phaseMask=4 where id in (35504, 35916);

-- https://cata-twinhead.twinstar.cz/?npc=44470
update creature set phaseMask=8 where id in (35554, 44470);

-- https://cata-twinhead.twinstar.cz/?npc=38218
update creature set phaseMask=32 where id in (38218, 38615);

-- this creature are spawned by script, first step: move to unused phase 64
-- https://cata-twinhead.twinstar.cz/?quest=24904
update creature set phaseMask=64 where id in (38424, 38425, 38210, 38420, 38464, 38192, 38467, 35505, 38331, 38348, 38377);
update creature set phaseMask=64 where id in (35905, 38221, 38415, 35385, 38469, 35230, 35231, 38473, 51277, 38470, 35457, 38426);

-- https://cata-twinhead.twinstar.cz/?npc=38465
update creature set phaseMask=4096+8192 where guid=251762;
update creature set phaseMask=64 where guid=251606;

delete from creature_text where entry = 38218;
INSERT INTO `creature_text` VALUES (38218, 0, 0, "The Forsaken think we're weak.  A broken people.  They think we'll roll over like a scared dog.", 14, 0, 100, 0, 0, 19623, '', 37888);
INSERT INTO `creature_text` VALUES (38218, 1, 0, "How wrong they are.  We will fight them in the fields until the last trench collapses and the last cannon is silenced.", 14, 0, 100, 0, 0, 19624, '', 37893);
INSERT INTO `creature_text` VALUES (38218, 2, 0, "We will fight them on the streets until the last shot is fired.  And when there's no more ammunition, we'll crush their skulls with the stones that pave our city.", 14, 0, 100, 0, 0, 19625, '', 37891);
INSERT INTO `creature_text` VALUES (38218, 3, 0, "We will fight them in the alleys, until our knuckles are skinned and bloody and our rapiers lay on the ground shattered.", 14, 0, 100, 0, 0, 19626, '', 37892);
INSERT INTO `creature_text` VALUES (38218, 4, 0, "And if we find ourselves surrounded and disarmed... wounded and without hope... we will lift our heads in defiance and spit in their faces.", 14, 0, 100, 0, 0, 19627, '', 37895);
INSERT INTO `creature_text` VALUES (38218, 5, 0, "But we will... NEVER SURRENDER!!!!!", 14, 0, 100, 0, 0, 19628, '', 37896);
INSERT INTO `creature_text` VALUES (38218, 6, 0, "FOR GILNEAS!!!", 14, 0, 100, 0, 0, 19651, '', 37897);

delete from creature_text where entry = 38469;
INSERT INTO `creature_text` VALUES (38469, 0, 0, "Enough!", 14, 0, 100, 0, 0, 20457, '', 38366);
INSERT INTO `creature_text` VALUES (38469, 1, 0, "Such a waste.  That arrow's poison was not meant to be wasted on your whelp.  We'll meet again, Genn!", 12, 0, 100, 0, 0, 20458, '', 38370);

update gameobject set phaseMask=4 where guid=166801;
update gameobject set phaseMask=1+2 where guid=166796;
delete from gameobject where guid in (400897, 400919);

update creature set phaseMask=6, id=35232 where id=34864 and guid between 250182 and 250194;

delete from creature_text where entry = 38470;
INSERT INTO `creature_text` VALUES (38470, 0, 0, 'SYLVANAS!!', 14, 0, 100, 0, 0, 19726, '', 38365);
INSERT INTO `creature_text` VALUES (38470, 1, 1, 'LIAM!!  NO!!!', 14, 0, 100, 0, 0, 19727, '', 38485);

delete from creature where id=34864 and guid between 250205 and 250210;

REPLACE INTO `creature` VALUES (278370, 34916, 654, 1, 2, 0, 0, -1441.17, 1407.62, 35.5564, 3.12932, 500, 0, 0, 2650, 0, 0, 0, 0, 0);
REPLACE INTO `creature` VALUES (278371, 34916, 654, 1, 2, 0, 0, -1444.09, 1412.21, 35.5561, 3.11888, 500, 0, 0, 2650, 0, 0, 0, 0, 0);
REPLACE INTO `creature` VALUES (278372, 34916, 654, 1, 2, 0, 0, -1444.09, 1404.17, 35.5564, 3.05526, 500, 0, 0, 2650, 0, 0, 0, 0, 0);
REPLACE INTO `creature` VALUES (278373, 34916, 654, 1, 2, 0, 0, -1441.17, 1404.17, 35.5561, 3.0442, 500, 0, 0, 2650, 0, 0, 0, 0, 0);
REPLACE INTO `creature` VALUES (278374, 34916, 654, 1, 2, 0, 0, -1441.17, 1412.21, 35.5561, 3.0874, 500, 0, 0, 2650, 0, 0, 0, 0, 0);
REPLACE INTO `creature` VALUES (278375, 34916, 654, 1, 2, 0, 0, -1441.17, 1400.05, 35.5561, 3.0874, 500, 0, 0, 2650, 0, 0, 0, 0, 0);
REPLACE INTO `creature` VALUES (278376, 34916, 654, 1, 2, 0, 0, -1444.09, 1418.94, 35.5564, 3.11047, 500, 0, 0, 2650, 0, 0, 0, 0, 0);
REPLACE INTO `creature` VALUES (278377, 34916, 654, 1, 2, 0, 0, -1444.09, 1400.05, 35.5564, 3.11102, 500, 0, 0, 2650, 0, 0, 0, 0, 0);
REPLACE INTO `creature` VALUES (278378, 34916, 654, 1, 2, 0, 0, -1441.17, 1415.11, 35.5561, 3.0442, 500, 0, 0, 2650, 0, 0, 0, 0, 0);
REPLACE INTO `creature` VALUES (278379, 34916, 654, 1, 2, 0, 0, -1444.09, 1407.62, 35.5561, 3.13066, 500, 0, 0, 2650, 0, 0, 0, 0, 0);
REPLACE INTO `creature` VALUES (278380, 34916, 654, 1, 2, 0, 0, -1444.09, 1415.11, 35.5564, 3.11047, 500, 0, 0, 2650, 0, 0, 0, 0, 0);
REPLACE INTO `creature` VALUES (278381, 34916, 654, 1, 2, 0, 0, -1441.17, 1418.94, 35.5561, 3.0442, 500, 0, 0, 2650, 0, 0, 0, 0, 0);

delete from creature where id=34864 and map=638;

SET @GUID=250799;
SET @PATHID=250799;

DELETE FROM `waypoint_data` WHERE id=@PATHID;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`) VALUES 
(@PATHID, 0, -1441.165, 1427.617, 35.556, 3.228, 0, 1, 0, 100),
(@PATHID, 1, -1544.720, 1426.794, 35.556, 3.142, 0, 1, 0, 100),
(@PATHID, 2, -1551.927, 1422.041, 35.556, 3.754, 0, 1, 0, 100),
(@PATHID, 3, -1553.961, 1369.555, 35.628, 4.701, 0, 1, 0, 100),
(@PATHID, 4, -1556.845, 1365.271, 35.623, 4.049, 0, 1, 0, 100),
(@PATHID, 5, -1583.877, 1364.094, 35.699, 3.220, 0, 1, 0, 100),
(@PATHID, 6, -1583.531, 1359.908, 36.168, 4.795, 2000, 1, 1184, 100);

UPDATE `creature` SET `MovementType`=2 WHERE `guid`=@GUID;

INSERT IGNORE INTO `creature_addon` (`guid`) VALUE (@GUID);
UPDATE `creature_addon` SET `path_id`=@PATHID WHERE `guid`=@GUID;

SET @GUID=250803;
SET @PATHID=250803;

DELETE FROM `waypoint_data` WHERE id=@PATHID;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`) VALUES 
(@PATHID, 0, -1528.820, 1334.271, 35.557, 0.357, 0, 1, 0, 100),
(@PATHID, 1, -1505.816, 1341.246, 35.557, 0.306, 0, 1, 0, 100),
(@PATHID, 2, -1502.348, 1347.326, 35.557, 1.052, 0, 1, 0, 100),
(@PATHID, 3, -1504.182, 1423.109, 35.557, 1.567, 0, 1, 0, 100),
(@PATHID, 4, -1510.716, 1427.184, 35.557, 2.584, 0, 1, 0, 100),
(@PATHID, 5, -1549.440, 1427.186, 35.557, 3.142, 0, 1, 0, 100),
(@PATHID, 6, -1553.561, 1420.965, 35.557, 4.127, 0, 1, 0, 100),
(@PATHID, 7, -1554.421, 1393.651, 35.576, 4.681, 0, 1, 0, 100),
(@PATHID, 8, -1560.495, 1390.586, 35.758, 3.609, 0, 1, 0, 100),
(@PATHID, 9, -1568.862, 1391.212, 36.199, 3.067, 0, 1, 0, 100),
(@PATHID, 10, -1569.407, 1385.645, 36.578, 4.642, 2000, 1, 1184, 100);

UPDATE `creature` SET `MovementType`=2 WHERE `guid`=@GUID;

INSERT IGNORE INTO `creature_addon` (`guid`) VALUE (@GUID);
UPDATE `creature_addon` SET `path_id`=@PATHID WHERE `guid`=@GUID;

SET @GUID=250798;
SET @PATHID=250798;

DELETE FROM `waypoint_data` WHERE id=@PATHID;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`) VALUES 
(@PATHID, 0, -1502.163, 1372.487, 35.556, 1.508, 0, 1, 0, 100),
(@PATHID, 1, -1502.466, 1391.861, 35.556, 1.586, 0, 1, 0, 100),
(@PATHID, 2, -1508.599, 1395.265, 35.556, 2.635, 0, 1, 0, 100),
(@PATHID, 3, -1548.689, 1396.629, 35.556, 3.114, 0, 1, 0, 100),
(@PATHID, 4, -1552.451, 1403.348, 35.556, 2.081, 0, 1, 0, 100),
(@PATHID, 5, -1552.083, 1420.153, 35.556, 1.559, 0, 1, 0, 100),
(@PATHID, 6, -1545.650, 1426.267, 35.556, 0.754, 0, 1, 0, 100),
(@PATHID, 7, -1444.343, 1425.762, 35.556, 6.244, 0, 1, 0, 100),
(@PATHID, 8, -1432.256, 1420.810, 35.556, 5.894, 0, 1, 0, 100),
(@PATHID, 9, -1421.057, 1420.633, 35.556, 6.267, 0, 1, 0, 100),
(@PATHID, 10, -1420.756, 1413.394, 36.519, 4.775, 2000, 1, 1184, 100);

UPDATE `creature` SET `MovementType`=2 WHERE `guid`=@GUID;

INSERT IGNORE INTO `creature_addon` (`guid`) VALUE (@GUID);
UPDATE `creature_addon` SET `path_id`=@PATHID WHERE `guid`=@GUID;

SET @GUID=250014;
SET @PATHID=250014;

DELETE FROM `waypoint_data` WHERE id=@PATHID;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`) VALUES 
(@PATHID, 0, -1539.906, 1428.300, 35.556, 4.367, 0, 1, 0, 100),
(@PATHID, 1, -1547.920, 1424.476, 35.556, 3.625, 0, 1, 0, 100),
(@PATHID, 2, -1552.733, 1417.594, 35.556, 4.123, 0, 1, 0, 100),
(@PATHID, 3, -1552.274, 1397.537, 35.559, 4.681, 0, 1, 0, 100),
(@PATHID, 4, -1545.806, 1392.543, 35.556, 5.655, 0, 1, 0, 100),
(@PATHID, 5, -1509.615, 1393.336, 35.556, 6.283, 0, 1, 0, 100),
(@PATHID, 6, -1504.657, 1386.280, 35.556, 5.325, 0, 1, 0, 100),
(@PATHID, 7, -1503.036, 1348.725, 35.556, 4.756, 0, 1, 0, 100),
(@PATHID, 8, -1507.975, 1341.639, 35.556, 4.104, 0, 1, 0, 100),
(@PATHID, 9, -1551.662, 1330.598, 35.556, 2.741, 0, 1, 0, 100),
(@PATHID, 10, -1556.326, 1337.885, 35.556, 2.140, 0, 1, 0, 100),
(@PATHID, 11, -1555.253, 1362.333, 35.556, 1.579, 0, 1, 0, 100),
(@PATHID, 12, -1565.593, 1365.382, 35.771, 2.855, 0, 1, 0, 100),
(@PATHID, 13, -1583.779, 1364.382, 35.716, 3.197, 2000, 1, 1184, 100);

UPDATE `creature` SET `MovementType`=2 WHERE `guid`=@GUID;

INSERT IGNORE INTO `creature_addon` (`guid`) VALUE (@GUID);
UPDATE `creature_addon` SET `path_id`=@PATHID WHERE `guid`=@GUID;


delete from waypoint_scripts where guid=764;
insert into waypoint_scripts values
(1184, 0, 18, 2000, 0, 0, 0, 0, 0, 0, 764);



