

UPDATE creature SET position_x=908.699, position_y=430.847, position_z=155.154, orientation=3.3256, MovementType=2 WHERE guid=243034;

DELETE FROM creature_addon WHERE guid=243034;
INSERT INTO creature_addon VALUES 
(243034, 243034, 0, 50331648, 1, 0, 0, 0, 0, "");

DELETE FROM waypoint_data WHERE id=243034;
INSERT INTO waypoint_data VALUES 
(243034, 0, 908.6997, 430.8475, 155.1546, 3.32564, 10000, 0, 0, 100, 0),
(243034, 1, 874.9426, 423.3204, 172.9053, 3.360982, 0, 0, 0, 100, 0),
(243034, 2, 836.5046, 330.7504, 176.2274, 4.311316, 0, 0, 0, 100, 0),
(243034, 3, 657.3047, 380.7551, 178.9962, 2.846548, 0, 0, 0, 100, 0),
(243034, 4, 687.5109, 582.2733, 181.6918, 1.413196, 0, 0, 0, 100, 0),
(243034, 5, 756.7435, 595.163, 188.5563, 0.184047, 0, 0, 0, 100, 0),
(243034, 6, 933.5749, 442.7511, 194.0512, 5.51298, 0, 0, 0, 100, 0);

UPDATE creature SET phaseId=254, position_x=998.005, position_y=521.946, position_z=-49.2515, orientation=3.2463, spawntimesecs=120 WHERE guid=242291;

UPDATE creature SET position_x=1032.42, position_y=542.142, position_z=-49.3179, orientation=3.9968, spawntimesecs=120 WHERE guid=243260;

DELETE FROM creature WHERE id=45300 AND guid=288855;
INSERT INTO creature VALUES 
(288855, 45300, 646, 0, 0, 1, 253, 0, 0, 0, 1032.42, 542.142, -49.3179, 3.9968, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=45300 AND guid=288856;
INSERT INTO creature VALUES 
(288856, 45300, 646, 0, 0, 1, 254, 0, 0, 0, 1032.42, 542.142, -49.3179, 3.9968, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0);

UPDATE creature_template_addon SET auras="78148 78150" WHERE entry=45300;

UPDATE creature SET phaseId=253, spawndist=0, MovementType=0 WHERE guid=242548;

UPDATE creature SET phaseId=257, spawndist=0, MovementType=0 WHERE guid=242561;

DELETE FROM creature WHERE id=44667 AND guid=290855;
INSERT INTO creature VALUES 
(290855, 44667, 646, 0, 0, 1, 254, 0, 33354, 0, 1033.12, 528.877, -49.33486, 0.09396218, 300, 0, 0, 0, 0, 0, 0, 0, 0, 0);

