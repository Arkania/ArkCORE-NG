DELETE FROM `creature` WHERE `guid` in (250256, 250257, 250843, 250864, 250903);
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES
(250256, 35118, 654, 1, 2, 0, 0, -1658.33, 1365.74, 15.1351, 4.07202, 500, 0, 0, 71, 0, 0, 0, 0, 0),
(250257, 35118, 654, 1, 2, 0, 0, -1667.6, 1367.5, 15.1351, 4.22412, 500, 0, 0, 71, 0, 0, 0, 0, 0),
(250843, 35118, 654, 1, 2, 0, 0, -1671.65, 1381.63, 15.4334, 5.45573, 500, 0, 0, 55, 0, 0, 0, 0, 0),
(250864, 35118, 654, 1, 2, 0, 0, -1664.82, 1385.11, 15.1356, 4.6664, 500, 0, 0, 55, 0, 0, 0, 0, 0),
(250903, 35118, 654, 1, 2, 0, 0, -1678.33, 1362.85, 15.1359, 4.43617, 600, 0, 0, 55, 0, 0, 0, 0, 0);

DELETE FROM `creature` WHERE `guid` in (251341, 251342, 251343);
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES
(251341, 35505, 654, 1, 4, 36771, 0, -1662.32, 1351.54, 15.1351, 4.05919, 300, 0, 0, 55, 0, 0, 0, 0, 0),
(251342, 35505, 654, 1, 4, 36772, 0, -1689.58, 1354.18, 15.1359, 5.08413, 300, 0, 0, 55, 0, 0, 0, 0, 0),
(251343, 35505, 654, 1, 4, 36770, 0, -1647.27, 1337.55, 17.5073, 3.19524, 300, 0, 0, 55, 0, 0, 0, 0, 0);

update creature set phaseMask=2 where guid in (250854, 250161);



