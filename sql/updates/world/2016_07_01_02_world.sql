
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry` IN (29854, 30013);

delete from creature where id=29730 and guid in (202751, 202892, 202903, 202904, 202905, 202906, 214233);

delete from creature_addon where guid in (202751, 202892, 202903, 202904, 202905, 202906, 214233);

DELETE FROM `vehicle_template_accessory` WHERE `entry`= 30013;
INSERT INTO `vehicle_template_accessory` (`entry`,`accessory_entry`,`seat_id`,`minion`,`description`,`summontype`,`summontimer`) VALUES
(30013,29730,0,1,'Stormcrest Eagle',5,0);

SET @ENTRY=30013;
SET @GUID0 := 200396;
SET @GUID1 := 200476;
SET @GUID2 := 200477;
SET @GUID3 := 200478;
SET @GUID4 := 213907;

UPDATE `creature` SET movementType=2 WHERE `guid` IN (@GUID0, @GUID1, @GUID2, @GUID3, @GUID4);

DELETE FROM `creature_addon` WHERE `guid` IN (200396, 200476, 200477, 200478, 213907);
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`,`auras`) VALUES
(@GUID0, @GUID0*10, 0, 0, 1, 0, ''),
(@GUID1, @GUID1*10, 0, 0, 1, 0, ''),
(@GUID2, @GUID2*10, 0, 0, 1, 0, ''),
(@GUID3, @GUID3*10, 0, 0, 1, 0, ''),
(@GUID4, @GUID4*10, 0, 0, 1, 0, '');

DELETE FROM `waypoint_data` WHERE `id` IN (@GUID0*10, @GUID1*10, @GUID2*10, @GUID3*10, @GUID4*10);
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`) VALUES
(@GUID0*10, 1, 6580.963, -341.5958, 1025.59, 0, 0, 1, 0, 100, 0),
(@GUID0*10, 2, 6595.587, -274.2542, 1025.59, 0, 0, 1, 0, 100, 0),
(@GUID0*10, 3, 6603.651, -214.6846, 1025.59, 0, 0, 1, 0, 100, 0),
(@GUID0*10, 4, 6598.268, -139.6636, 1025.59, 0, 0, 1, 0, 100, 0),
(@GUID0*10, 5, 6583.247, -70.26400, 1025.59, 0, 0, 1, 0, 100, 0),
(@GUID0*10, 6, 6517.861, -27.37788, 1025.59, 0, 0, 1, 0, 100, 0),
(@GUID0*10, 7, 6334.042, -80.26796, 1025.59, 0, 0, 1, 0, 100, 0),
(@GUID0*10, 8, 6302.791, -214.7384, 1025.59, 0, 0, 1, 0, 100, 0),
(@GUID0*10, 9, 6306.531, -372.1047, 1025.59, 0, 0, 1, 0, 100, 0),
(@GUID0*10, 10, 6347.108, -523.2972, 1025.59, 0, 0, 1, 0, 100, 0),
(@GUID0*10, 11, 6469.087, -575.7284, 1025.59, 0, 0, 1, 0, 100, 0),
(@GUID0*10, 12, 6543.881, -476.6713, 1025.59, 0, 0, 1, 0, 100, 0),
(@GUID1*10, 1, 6558.544, -152.0257, 1054.933, 0, 0, 1, 0, 100, 0),
(@GUID1*10, 2, 6609.241, -127.7897, 1055.322, 0, 0, 1, 0, 100, 0),
(@GUID1*10, 3, 6701.458, -107.1807, 1059.877, 0, 0, 1, 0, 100, 0),
(@GUID1*10, 4, 6774.843, -197.2011, 1078.129, 0, 0, 1, 0, 100, 0),
(@GUID1*10, 5, 6777.308, -292.3615, 1095.376, 0, 0, 1, 0, 100, 0),
(@GUID1*10, 6, 6703.971, -329.4862, 1100.933, 0, 0, 1, 0, 100, 0),
(@GUID1*10, 7, 6606.578, -326.3456, 1091.265, 0, 0, 1, 0, 100, 0),
(@GUID1*10, 8, 6552.779, -289.719, 1077.712, 0, 0, 1, 0, 100, 0),
(@GUID1*10, 9, 6536.85, -189.0296, 1059.237, 0, 0, 1, 0, 100, 0),
(@GUID2*10, 1, 6630.098, -152.5961, 999.0965, 0, 0, 1, 0, 100, 0),
(@GUID2*10, 2, 6663.148, -136.3936, 999.0965, 0, 0, 1, 0, 100, 0),
(@GUID2*10, 3, 6705.553, -94.23096, 999.0965, 0, 0, 1, 0, 100, 0),
(@GUID2*10, 4, 6728.896, 43.04465, 999.0965, 0, 0, 1, 0, 100, 0),
(@GUID2*10, 5, 6628.838, 175.6433, 999.0965, 0, 0, 1, 0, 100, 0),
(@GUID2*10, 6, 6520.246, 148.9764, 999.0965, 0, 0, 1, 0, 100, 0),
(@GUID2*10, 7, 6386.172, -22.66618, 999.0965, 0, 0, 1, 0, 100, 0),
(@GUID2*10, 8, 6253.463, -195.8139, 999.0965, 0, 0, 1, 0, 100, 0),
(@GUID2*10, 9, 6330.91, -276.6109, 999.0965, 0, 0, 1, 0, 100, 0),
(@GUID2*10, 10, 6537.496, -198.9901, 999.0965, 0, 0, 1, 0, 100, 0),
(@GUID3*10, 1, 6725.225586, -25.534340, 999.721313, 0, 0, 1, 0, 100, 0),
(@GUID3*10, 2, 6638.638184, -52.154530, 991.158203, 0, 0, 1, 0, 100, 0),
(@GUID3*10, 3, 6567.925293, -153.043152, 1001.600220, 0, 0, 1, 0, 100, 0),
(@GUID3*10, 4, 6591.385742, -224.502579, 1003.976013, 0, 0, 1, 0, 100, 0),
(@GUID3*10, 5, 6695.518555, -252.929214, 1022.529175, 0, 0, 1, 0, 100, 0),
(@GUID3*10, 6, 6802.429199, -243.025558, 1022.408691, 0, 0, 1, 0, 100, 0),
(@GUID3*10, 7, 6798.217285, -161.789276, 1046.530518, 0, 0, 1, 0, 100, 0),
(@GUID4*10, 0, 6487.82, 115.492, 999.096, 0, 0, 1, 0, 100, 0),
(@GUID4*10, 1, 6271.93, 87.492, 999.196, 0, 0, 1, 0, 100, 0),
(@GUID4*10, 2, 6726.61, -264.234, 1049.096, 0, 0, 1, 0, 100, 0);

SET @ENTRY := 36021;
UPDATE creature_template SET minlevel=80, maxlevel=80, faction=58 WHERE entry=@ENTRY;

-- The Brewmaiden
SET @ENTRY := 36021;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,22,0,100,0,101,0,0,0,11,48249,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"The Brewmaiden - Received Emote 101 - Cast 'Brewfest Brew Toss'"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,75,68269,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"The Brewmaiden - On Just Summoned - Add Aura 'The Brewmaiden's Blessing'");

UPDATE `quest_template` SET `ExclusiveGroup`=10983 WHERE  `Id` IN(10983,10989);
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` IN(19,20) AND `SourceEntry` IN(10995,10996,10997);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(19, 0, 10995, 0, 0, 8, 0, 10989, 0, 0, 0, 0, 0, '', 'Grulloc Has Two Skulls after Mog dorg the Wizened'),
(20, 0, 10995, 0, 0, 8, 0, 10989, 0, 0, 0, 0, 0, '', 'Grulloc Has Two Skulls after Mog dorg the Wizened'),
(19, 0, 10995, 0, 1, 8, 0, 10983, 0, 0, 0, 0, 0, '', 'Grulloc Has Two Skulls after Mog dorg the Wizened'),
(20, 0, 10995, 0, 1, 8, 0, 10983, 0, 0, 0, 0, 0, '', 'Grulloc Has Two Skulls after Mog dorg the Wizened'),
(19, 0, 10996, 0, 0, 8, 0, 10989, 0, 0, 0, 0, 0, '', 'Maggocs Treasure Chest after Mog dorg the Wizened'),
(20, 0, 10996, 0, 0, 8, 0, 10989, 0, 0, 0, 0, 0, '', 'Maggocs Treasure Chest after Mog dorg the Wizened'),
(19, 0, 10996, 0, 1, 8, 0, 10983, 0, 0, 0, 0, 0, '', 'Maggocs Treasure Chest after Mog dorg the Wizened'),
(20, 0, 10996, 0, 1, 8, 0, 10983, 0, 0, 0, 0, 0, '', 'Maggocs Treasure Chest after Mog dorg the Wizened'),
(19, 0, 10997, 0, 0, 8, 0, 10989, 0, 0, 0, 0, 0, '', 'Even Gronn Have Standards after Mog dorg the Wizened'),
(20, 0, 10997, 0, 0, 8, 0, 10989, 0, 0, 0, 0, 0, '', 'Even Gronn Have Standards after Mog dorg the Wizened'),
(19, 0, 10997, 0, 1, 8, 0, 10983, 0, 0, 0, 0, 0, '', 'Even Gronn Have Standards after Mog dorg the Wizened'),
(20, 0, 10997, 0, 1, 8, 0, 10983, 0, 0, 0, 0, 0, '', 'Even Gronn Have Standards after Mog dorg the Wizened');

SET @GUID := 180569;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `id`=16864 WHERE `guid`=@GUID;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-702.9703,`position_y`=1826.119,`position_z`=75.24933 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-702.9703,1826.119,75.24933,0,0,0,0,100,0),
(@PATH,2,-707.4134,1826.754,75.24933,0,0,0,0,100,0);

DELETE FROM `waypoint_data` WHERE `id` in (579650, 579660, 579670, 579680);

SET @ENTRY := 16843;
SET @GUID0 = 180537;
SET @GUID1 = 180538;
SET @GUID2 = 180539;
SET @GUID3 = 180540;

DELETE FROM `creature_formations` WHERE `leaderGUID`=@GUID0;
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`) VALUES
(@GUID0, @GUID0, 0, 0, 2),
(@GUID0, @GUID1, 5, 0, 2),
(@GUID0, @GUID2, 10, 0, 2),
(@GUID0, @GUID3, 15, 0, 2);

UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Honor Hold Cavalryman - On Respawn - Set Run On");

SET @PATH := @GUID0 * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-693.6425,`position_y`=2675.357,`position_z`=93.08069 WHERE `guid`=@GUID0;
DELETE FROM `creature_addon` WHERE `guid`=@GUID0;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID0,@PATH,2410,0,0,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-693.6425,2675.357,93.08069,0,0,0,0,100,0),
(@PATH,2,-678.617,2653.904,90.11584,0,0,0,0,100,0),
(@PATH,3,-670.0779,2623.337,87.22372,0,0,0,0,100,0),
(@PATH,4,-647.809,2588.676,83.14737,0,0,0,0,100,0),
(@PATH,5,-620.405,2546.836,73.68471,0,0,0,0,100,0),
(@PATH,6,-604.7114,2503.37,64.40894,0,0,0,0,100,0),
(@PATH,7,-603.8063,2468.986,57.10122,0,0,0,0,100,0),
(@PATH,8,-604.4416,2435.113,50.43313,0,0,0,0,100,0),
(@PATH,9,-599.5267,2409.476,44.74646,0,0,0,0,100,0),
(@PATH,10,-584.7905,2406.665,43.70581,0,0,0,0,100,0),
(@PATH,11,-582.3721,2430.458,47.94434,0,0,0,0,100,0),
(@PATH,12,-582.2322,2463.321,53.99577,0,0,0,0,100,0),
(@PATH,13,-583.6086,2498.498,61.39573,0,0,0,0,100,0),
(@PATH,14,-558.1572,2532.4,67.07269,0,0,0,0,100,0),
(@PATH,15,-524.5069,2553.839,65.79486,0,0,0,0,100,0),
(@PATH,16,-505.5841,2594.287,68.31036,0,0,0,0,100,0),
(@PATH,17,-504.4444,2604.637,70.43836,0,0,0,0,100,0),
(@PATH,18,-510.0499,2664.531,70.29152,0,0,0,0,100,0),
(@PATH,19,-511.0184,2694.743,68.82625,0,0,0,0,100,0),
(@PATH,20,-517.2742,2716.729,67.8214,0,0,0,0,100,0),
(@PATH,21,-534.5939,2747.733,69.1256,0,0,0,0,100,0),
(@PATH,22,-565.1152,2807.142,63.14902,0,0,0,0,100,0),
(@PATH,23,-596.1111,2836.904,59.59448,0,0,0,0,100,0),
(@PATH,24,-630.4422,2866.988,51.1272,0,0,0,0,100,0),
(@PATH,25,-678.3279,2883.457,47.06744,0,0,0,0,100,0),
(@PATH,26,-723.3876,2887.968,33.10106,0,0,0,0,100,0),
(@PATH,27,-762.0458,2886.646,24.27474,0,0,0,0,100,0),
(@PATH,28,-792.7939,2863.772,21.49371,0,0,0,0,100,0),
(@PATH,29,-819.7803,2843.219,19.12334,0,0,0,0,100,0),
(@PATH,30,-873.9691,2815.151,15.98937,0,0,0,0,100,0),
(@PATH,31,-893.9761,2802.479,14.45792,0,0,0,0,100,0),
(@PATH,32,-897.1367,2771.076,20.99353,0,0,0,0,100,0),
(@PATH,33,-867.2095,2775.483,38.31301,0,0,0,0,100,0),
(@PATH,34,-860.2045,2761.954,45.71127,0,0,0,0,100,0),
(@PATH,35,-868.9539,2736.927,57.97308,0,0,0,0,100,0),
(@PATH,36,-871.5066,2701.324,78.20714,0,0,0,0,100,0),
(@PATH,37,-856.217,2675.711,92.33214,0,0,0,0,100,0),
(@PATH,38,-833.6348,2676.617,98.47594,0,0,0,0,100,0),
(@PATH,39,-808.0863,2687.279,104.1725,0,0,0,0,100,0),
(@PATH,40,-790.8087,2689.64,104.0867,0,0,0,0,100,0),
(@PATH,41,-724.9875,2676.18,96.8718,0,0,0,0,100,0);

delete from spell_dbc where Id=39142;
INSERT INTO `spell_dbc` VALUES (39142, 805306752, 1024, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 13, 32, 0, 0, 0, 0, 0, 0, 0, 0, 'Drain World Tree Dummy');

SET @GUID0 := 180581; -- 57937;
SET @GUID1 := 180580; -- 57923;
SET @ENTRY = 16842;
DELETE FROM `creature_formations` WHERE `leaderGUID`=@GUID0;
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`) VALUES
(@GUID0, @GUID0, 0, 0, 2),
(@GUID0, @GUID1, 3, 90, 2);

SET @PATH := @GUID0 * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-872.1663,`position_y`=2769.454,`position_z`=37.44319 WHERE `guid`=@GUID0;
DELETE FROM `creature_addon` WHERE `guid`=@GUID0;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID0,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-872.1663,2769.454,37.44319,0,0,0,0,100,0),
(@PATH,2,-869.7395,2768.148,39.13062,0,0,0,0,100,0),
(@PATH,3,-865.2796,2739.821,56.70609,0,0,0,0,100,0),
(@PATH,4,-867.5071,2718.566,68.9836,0,0,0,0,100,0),
(@PATH,5,-867.6776,2699.037,79.59444,0,0,0,0,100,0),
(@PATH,6,-857.8785,2686.67,88.437,0,0,0,0,100,0),
(@PATH,7,-842.5071,2678.96,95.25343,0,0,0,0,100,0),
(@PATH,8,-822.5238,2681.506,102.4034,0,0,0,0,100,0),
(@PATH,9,-817.7297,2683.09,103.48,0,0,0,0,100,0),
(@PATH,10,-817.5452,2683.404,103.4257,0,0,0,0,100,0),
(@PATH,11,-838.7125,2678.288,96.64885,0,0,0,0,100,0),
(@PATH,12,-856.334,2685.094,89.30038,0,0,0,0,100,0),
(@PATH,13,-866.9412,2697.539,80.50797,0,0,0,0,100,0),
(@PATH,14,-867.8522,2713.977,71.4567,0,0,0,0,100,0),
(@PATH,15,-865.3911,2736.797,58.61076,0,0,0,0,100,0),
(@PATH,16,-866.6399,2765.021,41.61932,0,0,0,0,100,0);

UPDATE `creature` SET `spawndist`=0,`MovementType`=0,`position_x`=-866.125,`position_y`=2751.5,`position_z`=49.3004 WHERE `guid`=@GUID1;
DELETE FROM `creature_addon` WHERE `guid`=@GUID1;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID1,0,0,0,1,0, '');

SET @ENTRY := 16896;
SET @GUID := 180065; -- 58441;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-794.1317,`position_y`=2601.671,`position_z`=133.2523 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-794.1317,2601.671,133.2523,0,0,0,0,100,0),
(@PATH,2,-778.0168,2611.436,133.2532,0,0,0,0,100,0);

SET @GUID := 180066; -- 58440;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-800.5278,`position_y`=2648.273,`position_z`=133.2537 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-800.5278,2648.273,133.2537,0,0,0,0,100,0),
(@PATH,2,-816.2895,2638.862,133.2529,0,0,0,0,100,0);

SET @GUID := 180058; -- 58448;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-697.1456,`position_y`=2567.732,`position_z`=101.4374 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-697.1456,2567.732,101.4374,0,0,0,0,100,0),
(@PATH,2,-683.9911,2574.386,100.8064,0,0,0,0,100,0),
(@PATH,3,-683.9779,2574.394,100.8655,0,0,0,0,100,0),
(@PATH,4,-697.2676,2567.764,101.4445,0,0,0,0,100,0),
(@PATH,5,-682.3236,2567.782,100.8602,0,0,0,0,100,0);

SET @GUID := 180064; -- 58442;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-750.128,`position_y`=2567.929,`position_z`=104.1502 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-750.128,2567.929,104.1502,0,0,0,0,100,0),
(@PATH,2,-746.1736,2566.977,104.3655,0,0,0,0,100,0),
(@PATH,3,-732.6676,2565.869,104.5501,0,0,0,0,100,0),
(@PATH,4,-754.0043,2574.421,104.1675,0,0,0,0,100,0),
(@PATH,5,-754.0061,2574.378,104.2026,0,0,0,0,100,0),
(@PATH,6,-732.6328,2565.721,104.5407,0,0,0,0,100,0),
(@PATH,7,-746.1768,2566.991,104.2605,0,0,0,0,100,0);

SET @GUID := 180054; -- 58452;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-674.274,`position_y`=2787.06,`position_z`=109.5986 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-674.274,2787.06,109.5986,0,0,0,0,100,0),
(@PATH,2,-661.9408,2782.68,107.5661,0,0,0,0,100,0),
(@PATH,3,-645.2046,2773.514,104.8345,0,0,0,0,100,0),
(@PATH,4,-664.4965,2777.165,107.6214,0,0,0,0,100,0),
(@PATH,5,-664.445,2776.807,107.7074,0,0,0,0,100,0),
(@PATH,6,-645.4469,2773.186,104.7909,0,0,0,0,100,0);

SET @GUID := 180053; -- 58453;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-607.841,`position_y`=2612.785,`position_z`=99.32381 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-607.841,2612.785,99.32381,0,0,0,0,100,0),
(@PATH,2,-604.588,2617.701,99.53741,0,0,0,0,100,0),
(@PATH,3,-605.6599,2620.353,99.11266,0,0,0,0,100,0),
(@PATH,4,-605.5408,2620.273,98.99216,0,0,0,0,100,0),
(@PATH,5,-604.4185,2617.526,99.5359,0,0,0,0,100,0);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 13 AND `SourceEntry` IN (93167, 86862, 86863);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 1, 93167, 0, 0, 31, 0, 3, 40350, 0, 0, 0, 0, '', 'Twilight Documents targets Generic Trigger LAB'),
(13, 1, 86862, 0, 0, 31, 0, 3, 42355, 0, 0, 0, 0, '', 'Seismic Shard targets Seismic Shards'),
(13, 1, 86862, 0, 0, 1, 0, 79009, 0, 0, 0, 0, 0, '', 'Seismic Shard''s target must have SPELL_SEISMIC_SHARD_VISUAL aura'),
(13, 1, 86863, 0, 0, 31, 0, 3, 42333, 0, 0, 0, 0, '', 'Seismic Shard targets High Priestess Azil');

UPDATE `creature_template` SET `flags_extra` = 128 WHERE `entry` IN (51396, 51397, 43242, 43159, 49597, 49576, 42499, 42355);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` IN (51396, 51397);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(51396, 95284, 3, 0),
(51397, 95285, 3, 0);

DELETE FROM `spell_target_position` WHERE `id` IN (95284, 95285);

DELETE FROM `spell_script_names` WHERE `spell_id`=49576;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(49576, 'spell_dk_death_grip_initial');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = 49576;

UPDATE `creature_template` SET  `flags_extra` = 130  WHERE `entry` IN (40670, 40671, 40672);

SET @ENTRY=16873;
SET @GUID := 181680;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-945.313,`position_y`=1948.252,`position_z`=67.06455 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-945.313,1948.252,67.06455,0,0,0,0,100,0),
(@PATH,2,-946.7964,1966.628,67.06455,0,0,0,0,100,0),
(@PATH,3,-932.1639,1983.549,66.96194,0,0,0,0,100,0),
(@PATH,4,-914.9733,1976.555,67.05032,0,0,0,0,100,0),
(@PATH,5,-929.8001,1991.014,66.44107,0,0,0,0,100,0),
(@PATH,6,-929.8001,1991.014,66.44107,0,0,0,0,100,0),
(@PATH,7,-941.426,2015.632,66.31691,0,0,0,0,100,0),
(@PATH,8,-965.7396,2015.727,67.03322,0,0,0,0,100,0),
(@PATH,9,-968.4443,2047.705,67.06454,0,0,0,0,100,0),
(@PATH,10,-965.7396,2015.727,67.03322,0,0,0,0,100,0),
(@PATH,11,-965.7396,2015.727,67.03322,0,0,0,0,100,0),
(@PATH,12,-941.426,2015.632,66.31691,0,0,0,0,100,0),
(@PATH,13,-929.8001,1991.014,66.44107,0,0,0,0,100,0),
(@PATH,14,-914.9733,1976.555,67.05032,0,0,0,0,100,0),
(@PATH,15,-914.9733,1976.555,67.05032,0,0,0,0,100,0),
(@PATH,16,-932.1639,1983.549,66.96194,0,0,0,0,100,0),
(@PATH,17,-946.7964,1966.628,67.06455,0,0,0,0,100,0);

DELETE FROM `creature` WHERE `guid`=221905;

SET @ENTRY=27750;
SET @GUID := 221904;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=4903.906,`position_y`=1220.93,`position_z`=223.7604 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,4903.906,1220.93,223.7604,0,1000,0,0,100,0),
(@PATH,2,4907.209,1219.953,222.8496,0,0,0,0,100,0),
(@PATH,3,4905.934,1220.017,223.2021,0,0,0,0,100,0),
(@PATH,4,4902.668,1221.12,224.2068,0,1000,0,0,100,0),
(@PATH,5,4903.906,1220.93,223.7604,0,0,0,0,100,0),
(@PATH,6,4907.628,1220.036,222.8975,0,0,0,0,100,0),
(@PATH,7,4905.934,1220.017,223.2021,0,0,0,0,100,0),
(@PATH,8,4902.884,1221.202,224.2569,0,0,0,0,100,0);

SET @ENTRY := 27560;
SET @GUID := 229266; -- 111723;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=5064.595,`position_y`=1152.95,`position_z`=256.9933 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,5064.595,1152.95,256.9933,0,0,0,0,100,0),
(@PATH,2,5070.195,1148.834,258.9739,0,0,0,0,100,0),
(@PATH,3,5073.693,1146.814,259.7574,0,0,0,0,100,0),
(@PATH,4,5064.595,1152.95,256.9933,0,0,0,0,100,0),
(@PATH,5,5070.188,1148.872,259.0485,0,0,0,0,100,0),
(@PATH,6,5073.804,1146.81,259.5706,0,0,0,0,100,0),
(@PATH,7,5078.612,1145.942,259.8978,0,0,0,0,100,0),
(@PATH,8,5067.567,1150.284,258.2607,0,0,0,0,100,0),
(@PATH,9,5063.21,1155.218,255.487,0,0,0,0,100,0);
 
SET @GUID := 229249; -- 111724;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=4911.591,`position_y`=1159.036,`position_z`=236.6868 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,4911.591,1159.036,236.6868,0,0,0,0,100,0),
(@PATH,2,4911.276,1158.72,236.4579,0,0,0,0,100,0),
(@PATH,3,4911.188,1158.772,236.7394,0,0,0,0,100,0),
(@PATH,4,4899.376,1152.87,236.8453,0,0,0,0,100,0),
(@PATH,5,4894.586,1145.359,234.9626,0,0,0,0,100,0),
(@PATH,6,4897.318,1151.077,236.903,0,0,0,0,100,0),
(@PATH,7,4901.86,1152.988,236.7417,0,0,0,0,100,0),
(@PATH,8,4906.159,1153.659,236.4303,0,0,0,0,100,0);
 
SET @GUID := 229264; -- 111725;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=4920.973,`position_y`=1199.484,`position_z`=220.5279 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,4920.973,1199.484,220.5279,0,10000,0,0,100,0),
(@PATH,2,4906.262,1193.945,216.8263,0,0,0,0,100,0),
(@PATH,3,4896.307,1191.923,213.5118,0,0,0,0,100,0),
(@PATH,4,4877.854,1191.151,207.1242,0,0,0,0,100,0),
(@PATH,5,4869.318,1191.457,203.3286,0,0,0,0,100,0),
(@PATH,6,4861.047,1185.213,197.0835,0,0,0,0,100,0),
(@PATH,7,4855.936,1177.188,191.9594,0,0,0,0,100,0),
(@PATH,8,4851.635,1166.61,185.649,0,0,0,0,100,0),
(@PATH,9,4851.767,1158.619,182.5839,0,0,0,0,100,0),
(@PATH,10,4851.611,1145.529,178.0937,0,0,0,0,100,0),
(@PATH,11,4848.171,1135.259,173.5705,0,0,0,0,100,0),
(@PATH,12,4841.896,1128.136,169.8648,0,0,0,0,100,0),
(@PATH,13,4829.645,1127.843,162.5515,0,0,0,0,100,0),
(@PATH,14,4817.105,1120.131,150.2594,0,0,0,0,100,0),
(@PATH,15,4837.624,1131.328,167.8283,0,0,0,0,100,0),
(@PATH,16,4843.094,1133.076,170.812,0,0,0,0,100,0),
(@PATH,17,4849.752,1146.139,177.2836,0,0,0,0,100,0),
(@PATH,18,4851.623,1160.048,182.5452,0,0,0,0,100,0),
(@PATH,19,4853.529,1172.237,188.9928,0,0,0,0,100,0),
(@PATH,20,4860.48,1186.084,197.2776,0,0,0,0,100,0),
(@PATH,21,4865.775,1191.164,201.062,0,0,0,0,100,0),
(@PATH,22,4882.853,1189.864,208.7863,0,0,0,0,100,0),
(@PATH,23,4898.756,1190.01,214.2629,0,0,0,0,100,0),
(@PATH,24,4903.106,1189.946,216.3225,0,0,0,0,100,0),
(@PATH,25,4916.818,1193.317,219.5798,0,0,0,0,100,0),
(@PATH,26,4927.818,1197.552,223.1037,0,0,0,0,100,0),
(@PATH,27,4934.524,1200.075,224.6629,0,0,0,0,100,0);

SET @ENTRY=27553;
SET @GUID0=229741;
SET @GUID1=229743;
DELETE FROM `creature_formations` WHERE `leaderGUID`=@GUID0;
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`) VALUES
(@GUID0, @GUID0, 0, 0, 2),
(@GUID0, @GUID1, 3, 270, 2);

-- Make the second guard sit on a wolf 
DELETE FROM `creature_addon` WHERE `guid`=@GUID1;
INSERT INTO `creature_addon` (`guid`, `mount`, `bytes2`) VALUES (@GUID1, 14574, 1);

SET @PATH := @GUID0 * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=4924.406,`position_y`=1275.88,`position_z`=226.2913 WHERE `guid`=@GUID0;
DELETE FROM `creature_addon` WHERE `guid`=@GUID0;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID0,@PATH,14574,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,4924.406,1275.88,226.2913,0,0,0,0,100,0),
(@PATH,2,4937.631,1293.169,231.839,0,0,0,0,100,0),
(@PATH,3,4942.635,1298.434,233.2347,0,0,0,0,100,0),
(@PATH,4,4945.541,1308.453,235.1535,0,0,0,0,100,0),
(@PATH,5,4945.916,1311.464,235.4867,0,0,0,0,100,0),
(@PATH,6,4933.331,1328.104,234.9145,0,0,0,0,100,0),
(@PATH,7,4920.956,1329.519,232.9218,0,0,0,0,100,0),
(@PATH,8,4910.192,1318.32,229.7501,0,0,0,0,100,0),
(@PATH,9,4907.542,1298.864,227.4101,0,0,0,0,100,0),
(@PATH,10,4920.273,1273.854,225.6455,0,0,0,0,100,0),
(@PATH,11,4921.565,1272.237,225.4687,0,0,0,0,100,0),
(@PATH,12,4934.279,1260.357,225.9705,0,0,0,0,100,0),
(@PATH,13,4942.9,1231.032,225.8454,0,0,0,0,100,0),
(@PATH,14,4937.212,1219.435,224.397,0,0,0,0,100,0),
(@PATH,15,4911.338,1207.108,217.914,0,0,0,0,100,0),
(@PATH,16,4891.614,1199.313,212.0708,0,0,0,0,100,0),
(@PATH,17,4863.26,1198.326,202.0412,0,0,0,0,100,0),
(@PATH,18,4850.935,1180.464,192.229,0,0,0,0,100,0),
(@PATH,19,4847.402,1162.623,182.7594,0,0,0,0,100,0),
(@PATH,20,4841.849,1139.334,171.3826,0,0,0,0,100,0),
(@PATH,21,4820.599,1131.604,157.3213,0,0,0,0,100,0),
(@PATH,22,4801.356,1123.592,143.7112,0,0,0,0,100,0),
(@PATH,23,4793.032,1123.066,139.6156,0,0,0,0,100,0),
(@PATH,24,4768.374,1127.539,137.6369,0,0,0,0,100,0),
(@PATH,25,4754.815,1120.818,134.7707,0,0,0,0,100,0),
(@PATH,26,4756.951,1111.815,133.9409,0,0,0,0,100,0),
(@PATH,27,4783.79,1110.19,135.937,0,0,0,0,100,0),
(@PATH,28,4794.232,1119.631,139.188,0,0,0,0,100,0),
(@PATH,29,4821.204,1132.168,157.943,0,0,0,0,100,0),
(@PATH,30,4839.43,1138.844,170.0454,0,0,0,0,100,0),
(@PATH,31,4845.836,1150.71,177.3853,0,0,0,0,100,0),
(@PATH,32,4845.682,1166.896,184.5937,0,0,0,0,100,0),
(@PATH,33,4851.188,1179.674,191.6429,0,0,0,0,100,0),
(@PATH,34,4856.156,1191.45,197.6969,0,0,0,0,100,0),
(@PATH,35,4866.021,1197.9,202.6528,0,0,0,0,100,0),
(@PATH,36,4877.186,1197.585,207.2055,0,0,0,0,100,0),
(@PATH,37,4886.485,1195.461,210.3322,0,0,0,0,100,0),
(@PATH,38,4899.135,1196.966,214.2494,0,0,0,0,100,0),
(@PATH,39,4918.985,1205.409,219.7656,0,0,0,0,100,0),
(@PATH,40,4937.731,1213.068,223.7986,0,0,0,0,100,0),
(@PATH,41,4945.257,1216.732,225.4393,0,0,0,0,100,0),
(@PATH,42,4964.039,1213.632,227.3908,0,0,0,0,100,0),
(@PATH,43,4977.262,1211.667,228.8397,0,0,0,0,100,0),
(@PATH,44,4995.401,1220.229,230.2568,0,0,0,0,100,0),
(@PATH,45,5005.794,1216.344,229.7073,0,0,0,0,100,0),
(@PATH,46,4999.293,1203.755,229.2162,0,0,0,0,100,0),
(@PATH,47,4998.588,1202.614,228.9512,0,0,0,0,100,0),
(@PATH,48,4990.875,1206.203,228.9671,0,0,0,0,100,0),
(@PATH,49,4981.535,1210.325,228.6667,0,0,0,0,100,0),
(@PATH,50,4954.279,1220.26,226.6951,0,0,0,0,100,0),
(@PATH,51,4947.755,1223.85,226.0268,0,0,0,0,100,0),
(@PATH,52,4940.268,1236.863,226.4474,0,0,0,0,100,0),
(@PATH,53,4938.791,1241.772,226.2903,0,0,0,0,100,0),
(@PATH,54,4938.446,1241.541,226.0408,0,0,0,0,100,0),
(@PATH,55,4942.353,1231.415,225.6545,0,0,0,0,100,0),
(@PATH,56,4951.323,1221.968,226.2391,0,0,0,0,100,0),
(@PATH,57,4968.059,1214.005,228.1602,0,0,0,0,100,0),
(@PATH,58,4968.759,1213.868,228.1815,0,0,0,0,100,0),
(@PATH,59,4981.347,1210.41,228.6719,0,0,0,0,100,0),
(@PATH,60,4990.792,1206.41,229.0509,0,0,0,0,100,0),
(@PATH,61,5001.532,1208.859,229.2795,0,0,0,0,100,0),
(@PATH,62,5006.636,1217.603,229.9853,0,0,0,0,100,0),
(@PATH,63,4988.494,1214.931,229.4006,0,0,0,0,100,0),
(@PATH,64,4970.586,1211.76,228.4952,0,0,0,0,100,0),
(@PATH,65,4955.156,1216.567,226.4764,0,0,0,0,100,0),
(@PATH,66,4920.63,1206.658,220.0801,0,0,0,0,100,0),
(@PATH,67,4908.19,1199.289,216.899,0,0,0,0,100,0),
(@PATH,68,4888.762,1195.545,210.6963,0,0,0,0,100,0),
(@PATH,69,4878.838,1197.535,207.8827,0,0,0,0,100,0),
(@PATH,70,4868.977,1198.564,204.075,0,0,0,0,100,0),
(@PATH,71,4857.268,1192.864,198.429,0,0,0,0,100,0),
(@PATH,72,4852.329,1182.311,193.1272,0,0,0,0,100,0),
(@PATH,73,4846.871,1170.936,186.4543,0,0,0,0,100,0),
(@PATH,74,4846.116,1153.266,178.4778,0,0,0,0,100,0),
(@PATH,75,4840.938,1140.415,171.2645,0,0,0,0,100,0),
(@PATH,76,4822.356,1132.747,159.001,0,0,0,0,100,0),
(@PATH,77,4795.46,1120.689,140.3265,0,0,0,0,100,0),
(@PATH,78,4786.737,1111.815,136.5621,0,0,0,0,100,0),
(@PATH,79,4761.876,1105.746,133.8939,0,0,0,0,100,0),
(@PATH,80,4754.403,1118.203,134.364,0,0,0,0,100,0),
(@PATH,81,4764.019,1125.688,136.6772,0,0,0,0,100,0),
(@PATH,82,4782.308,1124.246,137.7441,0,0,0,0,100,0),
(@PATH,83,4797.498,1123.224,141.726,0,0,0,0,100,0),
(@PATH,84,4818.895,1130.859,156.3943,0,0,0,0,100,0),
(@PATH,85,4839.273,1137.457,169.8718,0,0,0,0,100,0),
(@PATH,86,4846.415,1158.605,180.5813,0,0,0,0,100,0),
(@PATH,87,4849.638,1177.232,190.3028,0,0,0,0,100,0),
(@PATH,88,4860.67,1196.271,200.4404,0,0,0,0,100,0),
(@PATH,89,4886.715,1198.448,210.6501,0,0,0,0,100,0),
(@PATH,90,4906.66,1204.837,216.6283,0,0,0,0,100,0),
(@PATH,91,4934.462,1217.512,223.728,0,0,0,0,100,0),
(@PATH,92,4940.261,1224.569,225.2942,0,0,0,0,100,0),
(@PATH,93,4940.506,1242.196,226.2575,0,0,0,0,100,0),
(@PATH,94,4933.305,1263.189,225.7185,0,0,0,0,100,0),
(@PATH,95,4931.952,1265.79,225.6381,0,0,0,0,100,0),
(@PATH,96,4907.601,1289.275,226.642,0,0,0,0,100,0),
(@PATH,97,4907.739,1309.926,228.4361,0,0,0,0,100,0),
(@PATH,98,4916.103,1327.044,231.7567,0,0,0,0,100,0),
(@PATH,99,4928.627,1329.424,234.3804,0,0,0,0,100,0),
(@PATH,100,4940.942,1320.479,235.4543,0,0,0,0,100,0),
(@PATH,101,4944.531,1301.983,234.3128,0,0,0,0,100,0),
(@PATH,102,4940.48,1296.446,232.8031,0,0,0,0,100,0),
(@PATH,103,4924.831,1276.205,226.2591,0,0,0,0,100,0);

DELETE FROM creature_addon WHERE guid=221905;

SET @ENTRY=31269;
SET @GUID := 202699;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=5001.591,`position_y`=1222.632,`position_z`=256.7944 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,50331648,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,5001.591,1222.632,256.7944,0,0,0,0,100,0),
(@PATH,2,5030.151,1242.143,268.1555,0,0,0,0,100,0),
(@PATH,3,5016.198,1276.81,265.4842,0,0,0,0,100,0),
(@PATH,4,4991.751,1280.123,265.4842,0,0,0,0,100,0),
(@PATH,5,4956.835,1268.773,265.4842,0,0,0,0,100,0),
(@PATH,6,4938.806,1223.236,259.9842,0,0,0,0,100,0),
(@PATH,7,4926.227,1191.379,255.3177,0,0,0,0,100,0),
(@PATH,8,4900.753,1152.352,243.8777,0,0,0,0,100,0),
(@PATH,9,4881.784,1164.878,242.3777,0,0,0,0,100,0),
(@PATH,10,4851.181,1199.767,234.0444,0,0,0,0,100,0),
(@PATH,11,4846.833,1226.647,234.0444,0,0,0,0,100,0),
(@PATH,12,4855.959,1279.159,239.3777,0,0,0,0,100,0),
(@PATH,13,4911.077,1262.704,243.6555,0,0,0,0,100,0),
(@PATH,14,4964.954,1234.062,250.3221,0,0,0,0,100,0);

SET @GUID := 202700;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=4875.777,`position_y`=1347.747,`position_z`=240.9708 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,50331648,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,4875.777,1347.747,240.9708,0,0,0,0,100,0),
(@PATH,2,4900.708,1348.037,250.7207,0,0,0,0,100,0),
(@PATH,3,4926.32,1316.925,257.1653,0,0,0,0,100,0),
(@PATH,4,4938.213,1286.196,257.1653,0,0,0,0,100,0),
(@PATH,5,4947.025,1253.411,257.1653,0,0,0,0,100,0),
(@PATH,6,4945.441,1212.37,257.1653,0,0,0,0,100,0),
(@PATH,7,4948.411,1192.561,257.1653,0,0,0,0,100,0),
(@PATH,8,4972.647,1168.416,257.1653,0,0,0,0,100,0),
(@PATH,9,4995.961,1172.082,257.1653,0,0,0,0,100,0),
(@PATH,10,5004.243,1187.687,257.1653,0,0,0,0,100,0),
(@PATH,11,4989.543,1213.347,257.1653,0,0,0,0,100,0),
(@PATH,12,4965.152,1218.435,257.1653,0,0,0,0,100,0),
(@PATH,13,4923.045,1229.254,257.1653,0,0,0,0,100,0),
(@PATH,14,4887.481,1234.967,253.9984,0,0,0,0,100,0),
(@PATH,15,4851.523,1249.735,247.804,0,0,0,0,100,0),
(@PATH,16,4823.958,1288.316,234.6374,0,0,0,0,100,0),
(@PATH,17,4814.918,1327.853,230.693,0,0,0,0,100,0),
(@PATH,18,4853.216,1355.696,237.3319,0,0,0,0,100,0);

SET @GUID := 202703;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=5079.162,`position_y`=1142.135,`position_z`=267.7354 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,5079.162,1142.135,267.7354,0,0,0,0,100,0),
(@PATH,2,5078.512,1126.875,267.7354,0,0,0,0,100,0),
(@PATH,3,5055.61,1116.456,267.7354,0,0,0,0,100,0),
(@PATH,4,5039.365,1121.131,267.7354,0,0,0,0,100,0),
(@PATH,5,4967.615,1187.905,260.0954,0,0,0,0,100,0),
(@PATH,6,4945.081,1216.898,260.0954,0,0,0,0,100,0),
(@PATH,7,4956.427,1234.148,260.0954,0,0,0,0,100,0),
(@PATH,8,4960.777,1262.983,260.0954,0,0,0,0,100,0),
(@PATH,9,4914.742,1284.397,254.9566,0,0,0,0,100,0),
(@PATH,10,4891.905,1273.239,254.5677,0,0,0,0,100,0),
(@PATH,11,4867.362,1252.014,255.6233,0,0,0,0,100,0),
(@PATH,12,4872.584,1220.825,255.6233,0,0,0,0,100,0),
(@PATH,13,4921.48,1192.52,255.6233,0,0,0,0,100,0),
(@PATH,14,4940.803,1188.571,255.6233,0,0,0,0,100,0),
(@PATH,15,4982.143,1184.493,255.6233,0,0,0,0,100,0),
(@PATH,16,5063.028,1170.208,265.2344,0,0,0,0,100,0),
(@PATH,17,5072.713,1157.194,267.7354,0,0,0,0,100,0);

SET @ENTRY = 27558;
SET @GUID := 229509; -- 111465;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=5033.687,`position_y`=1241.426,`position_z`=231.0835 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,234, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,5033.687,1241.426,231.0835,0,10000,0,0,100,0),
(@PATH,2,5035.556,1229.439,230.2363,0,0,0,0,100,0),
(@PATH,3,5040.211,1214.877,229.068,0,0,0,0,100,0),
(@PATH,4,5040.954,1202.383,228.5539,0,0,0,0,100,0),
(@PATH,5,5040.104,1193.25,228.4282,0,0,0,0,100,0),
(@PATH,6,5031.986,1186.173,228.1725,0,10000,0,0,100,0),
(@PATH,7,5040.118,1194.927,228.1124,0,0,0,0,100,0),
(@PATH,8,5040.393,1195.888,228.1124,0,0,0,0,100,0),
(@PATH,9,5042.309,1202.575,228.527,0,0,0,0,100,0),
(@PATH,10,5040.336,1213.374,228.7625,0,0,0,0,100,0),
(@PATH,11,5040.336,1213.374,228.7625,0,0,0,0,100,0),
(@PATH,12,5038.792,1223.162,229.6375,0,0,0,0,100,0),
(@PATH,13,5033.343,1233.986,230.8479,0,0,0,0,100,0);

update creature_template set AIName="SmartAI" where entry=44880;


