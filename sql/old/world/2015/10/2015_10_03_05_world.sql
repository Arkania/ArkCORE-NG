

DELETE FROM `creature` WHERE `guid` IN (162065, 162066, 86092, 86091, 86090, 162074, 162075, 162076, 162077, 162078);

-- Pathing for Dragonmaw Shaman Entry: 21720 'ark FORMAT' 
SET @NPC := 170720;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-4178.686,`position_y`=490.5659,`position_z`=30.16439 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-4178.686,490.5659,30.16439,0,0,0,0,100,0), -- 10:20:24
(@PATH,2,-4197.292,485.9068,30.38932,0,0,0,0,100,0), -- 10:20:35
(@PATH,3,-4225.723,467.5575,41.27721,0,0,0,0,100,0), -- 10:20:44
(@PATH,4,-4215.874,436.8994,48.21687,0,0,0,0,100,0), -- 10:20:57
(@PATH,5,-4237.429,402.9925,63.27236,0,0,0,0,100,0), -- 10:21:13
(@PATH,6,-4257.311,375.9668,78.98435,0,0,0,0,100,0), -- 10:21:30
(@PATH,7,-4218.265,427.3583,49.21005,0,0,0,0,100,0), -- 10:21:59
(@PATH,8,-4226.337,464.256,42.97073,0,0,0,0,100,0), -- 10:22:17
(@PATH,9,-4205.016,481.8601,31.38265,0,0,0,0,100,0), -- 10:22:32
(@PATH,10,-4193.525,487.0911,30.10522,0,0,0,0,100,0), -- 10:22:46
(@PATH,11,-4172.567,476.759,31.17034,0,0,0,0,100,0), -- 10:22:55
(@PATH,12,-4151.987,448.1165,33.53831,0,0,0,0,100,0), -- 10:23:06
(@PATH,13,-4113.85,424.8085,34.97233,0,0,0,0,100,0), -- 10:23:18
(@PATH,14,-4147.163,444.2449,34.1104,0,0,0,0,100,0), -- 10:23:38
(@PATH,15,-4157.673,454.7521,31.41072,0,0,0,0,100,0); -- 10:23:57

-- Pathing for Dragonmaw Shaman Entry: 21720 'ark FORMAT' 
SET @NPC := 170711;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-4294.086,`position_y`=400.621,`position_z`=81.62926 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,233, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-4294.086,400.621,81.62926,0,25000,0,0,100,0), -- 10:13:30
(@PATH,2,-4292.586,399.621,81.62926,0,25000,0,0,100,0); -- 10:13:50

-- Pathing for Dragonmaw Shaman Entry: 21720 'ark FORMAT' 
SET @NPC := 170716;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-4244.082,`position_y`=315.9884,`position_z`=134.664 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-4244.082,315.9884,134.664,0,0,0,0,100,0), -- 10:12:22
(@PATH,2,-4235.726,319.797,134.6712,0,0,0,0,100,0), -- 10:12:25
(@PATH,3,-4229.505,315.7428,134.6895,0,0,0,0,100,0), -- 10:12:28
(@PATH,4,-4194.724,303.9587,136.7709,0,0,0,0,100,0), -- 10:12:30
(@PATH,5,-4190.966,294.0813,135.7594,0,0,0,0,100,0), -- 10:12:45
(@PATH,6,-4183.756,287.0773,135.6553,0,0,0,0,100,0), -- 10:14:20
(@PATH,7,-4191.174,297.8928,136.033,0,0,0,0,100,0), -- 10:14:26
(@PATH,8,-4220.702,310.0533,134.9795,0,0,0,0,100,0), -- 10:14:30
(@PATH,9,-4229.358,315.7001,134.6958,0,0,0,0,100,0), -- 10:14:45
(@PATH,10,-4230.426,317.3666,134.676,0,0,0,0,100,0), -- 10:14:48
(@PATH,11,-4235.935,319.6286,134.6698,0,0,0,0,100,0), -- 10:14:50
(@PATH,12,-4255.562,318.7018,134.6108,0,0,0,0,100,0), -- 10:14:54
(@PATH,13,-4249.844,317.125,134.6809,0,0,0,0,100,0), -- 10:15:00
(@PATH,14,-4243.675,313.4105,134.6629,0,0,0,0,100,0), -- 10:15:06
(@PATH,15,-4235.89,308.923,134.6676,0,0,0,0,100,0), -- 10:15:08
(@PATH,16,-4230.517,310.4198,134.6871,0,0,0,0,100,0), -- 10:15:11
(@PATH,17,-4194.894,303.7994,136.77,0,0,0,0,100,0), -- 10:15:14
(@PATH,18,-4188.841,309.6393,135.933,0,0,0,0,100,0), -- 10:15:29
(@PATH,19,-4175.213,316.2365,135.7092,0,0,0,0,100,0), -- 10:15:34
(@PATH,20,-4161.508,360.043,141.9081,0,0,0,0,100,0), -- 10:15:40
(@PATH,21,-4171.737,320.0564,135.9073,0,0,0,0,100,0), -- 10:16:01
(@PATH,22,-4185.639,313.6697,135.3489,0,0,0,0,100,0), -- 10:16:20
(@PATH,23,-4191.21,305.0679,136.4015,0,0,0,0,100,0), -- 10:16:26
(@PATH,24,-4220.617,309.9903,134.8077,0,0,0,0,100,0), -- 10:16:31
(@PATH,25,-4229.755,310.8228,134.6904,0,0,0,0,100,0), -- 10:16:45
(@PATH,26,-4235.208,308.5773,134.6808,0,0,0,0,100,0), -- 10:16:48
(@PATH,27,-4243.492,313.3849,134.6674,0,0,0,0,100,0), -- 10:16:51
(@PATH,28,-4255.519,318.5628,134.6098,0,0,0,0,100,0), -- 10:16:54
(@PATH,29,-4249.62,317.301,134.6521,0,0,0,0,100,0); -- 10:17:00

-- Pathing for Dragonmaw Shaman Entry: 21720 'ark FORMAT' 
SET @NPC := 170713;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-4263.521,`position_y`=408.381,`position_z`=79.67068 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-4263.521,408.381,79.67068,0,0,0,0,100,0), -- 10:12:48
(@PATH,2,-4275.601,391.1442,81.45609,0,0,0,0,100,0), -- 10:13:03
(@PATH,3,-4276.916,384.2662,79.99209,0,0,0,0,100,0), -- 10:13:13
(@PATH,4,-4272.852,367.3383,83.40826,0,0,0,0,100,0), -- 10:13:19
(@PATH,5,-4299.143,333.1703,109.8589,0,0,0,0,100,0), -- 10:13:24
(@PATH,6,-4291.638,298.5769,121.6239,0,0,0,0,100,0), -- 10:13:44
(@PATH,7,-4284.62,294.5884,122.3762,0,0,0,0,100,0), -- 10:14:00
(@PATH,8,-4265.867,286.0486,122.6935,0,0,0,0,100,0), -- 10:14:11
(@PATH,9,-4231.655,272.0292,122.6157,0,0,0,0,100,0), -- 10:14:22
(@PATH,10,-4221.664,271.404,122.5952,0,0,0,0,100,0), -- 10:14:30
(@PATH,11,-4221.826,271.2171,122.3309,0,0,0,0,100,0), -- 10:14:42
(@PATH,12,-4241.433,272.7845,122.9299,0,0,0,0,100,0), -- 10:14:50
(@PATH,13,-4243.721,273.0889,123.1742,0,0,0,0,100,0), -- 10:15:00
(@PATH,14,-4287.71,296.0865,122.0869,0,0,0,0,100,0), -- 10:15:09
(@PATH,15,-4299.358,330.6028,110.9833,0,0,0,0,100,0), -- 10:15:20
(@PATH,16,-4274.684,364.696,85.32684,0,0,0,0,100,0), -- 10:15:36
(@PATH,17,-4269.528,373.963,80.26889,0,0,0,0,100,0), -- 10:15:57
(@PATH,18,-4276.889,385.2,79.98441,0,0,0,0,100,0); -- 10:16:01

-- Dragonmaw Subjugator SAI
SET @ENTRY := 21718;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,1,0,0,0,0,21,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonmaw Subjugator - Out of Combat - Enable Combat Movement (No Repeat)"),
(@ENTRY,0,1,2,4,0,100,1,0,0,0,0,11,9613,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonmaw Subjugator - On Aggro - Cast 'Shadow Bolt' (No Repeat)"),
(@ENTRY,0,2,0,61,0,100,0,0,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonmaw Subjugator - On Aggro - Increment Phase By 1 (No Repeat)"),
(@ENTRY,0,3,0,9,1,100,0,0,40,2400,3800,11,9613,0,0,0,0,0,2,0,0,0,0,0,0,0,"Dragonmaw Subjugator - Within 0-40 Range - Cast 'Shadow Bolt' (No Repeat)"),
(@ENTRY,0,4,5,3,1,100,1,0,15,0,0,21,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonmaw Subjugator - Between 0-15% Mana - Enable Combat Movement (Phase 1) (No Repeat)"),
(@ENTRY,0,5,0,61,1,100,0,0,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonmaw Subjugator - Between 0-15% Mana - Increment Phase By 1 (Phase 1) (No Repeat)"),
(@ENTRY,0,6,0,9,1,100,1,35,80,0,0,21,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonmaw Subjugator - Within 35-80 Range - Enable Combat Movement (Phase 1) (No Repeat)"),
(@ENTRY,0,7,0,9,1,100,1,5,15,0,0,21,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonmaw Subjugator - Within 5-15 Range - Disable Combat Movement (Phase 1) (No Repeat)"),
(@ENTRY,0,8,0,9,1,100,1,0,5,0,0,21,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonmaw Subjugator - Within 0-5 Range - Enable Combat Movement (Phase 1) (No Repeat)"),
(@ENTRY,0,9,0,3,2,100,0,30,100,100,100,23,0,1,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonmaw Subjugator - Between 30-100% Mana - Decrement Phase By 1 (Phase 1) (No Repeat)"),
(@ENTRY,0,10,11,2,0,100,1,0,15,0,0,22,3,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonmaw Subjugator - Between 0-15% Health - Set Event Phase 3 (No Repeat)"),
(@ENTRY,0,11,12,61,0,100,0,0,0,0,0,21,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonmaw Subjugator - Between 0-15% Health - Enable Combat Movement (No Repeat)"),
(@ENTRY,0,12,0,61,0,100,0,0,0,0,0,25,1,0,0,0,0,0,0,0,0,0,0,0,0,0,"Dragonmaw Subjugator - Between 0-15% Health - Flee For Assist (No Repeat)"),
(@ENTRY,0,13,0,6,0,100,1,0,0,0,0,33,22197,0,0,0,0,0,7,0,0,0,0,0,0,0,"Dragonmaw Subjugator - On Just Died - Quest Credit 'Infiltrating Dragonmaw Fortress' (No Repeat)");

-- Pathing for Dragonmaw Subjugator Entry: 21718 'ark FORMAT' 
SET @NPC := 170732;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-4102.015,`position_y`=377.2606,`position_z`=30.89463 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-4102.015,377.2606,30.89463,0,0,0,0,100,0), -- 10:20:43
(@PATH,2,-4108.736,382.3355,30.58962,0,0,0,0,100,0), -- 10:20:47
(@PATH,3,-4115.181,384.7361,30.83398,0,0,0,0,100,0), -- 10:20:49
(@PATH,4,-4115.945,392.739,30.79796,0,0,0,0,100,0), -- 10:20:53
(@PATH,5,-4111.743,392.8836,30.53397,0,0,0,0,100,0), -- 10:20:54
(@PATH,6,-4106.752,389.3356,30.54209,0,0,0,0,100,0), -- 10:20:57
(@PATH,7,-4103.535,395.7037,30.67706,0,0,0,0,100,0), -- 10:21:00
(@PATH,8,-4103.445,396.1037,30.62162,0,0,0,0,100,0), -- 10:21:02
(@PATH,9,-4099.806,402.0006,30.79059,0,0,0,0,100,0), -- 10:21:14
(@PATH,10,-4099.44,401.964,30.87934,0,0,0,0,100,0), -- 10:21:15
(@PATH,11,-4086.569,405.2619,30.82691,0,0,0,0,100,0), -- 10:21:21
(@PATH,12,-4089.497,392.9045,30.76514,0,0,0,0,100,0), -- 10:21:26
(@PATH,13,-4089.03,381.2375,31.16474,0,0,0,0,100,0), -- 10:21:31
(@PATH,14,-4091.608,379.7381,30.97511,0,0,0,0,100,0); -- 10:21:33

-- Pathing for Dragonmaw Subjugator Entry: 21718 'ark FORMAT' 
SET @NPC := 170734;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-4192.549,`position_y`=463.3147,`position_z`=30.76653 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-4192.549,463.3147,30.76653,0,0,0,0,100,0), -- 10:21:58
(@PATH,2,-4188.431,467.3629,30.58786,0,0,0,0,100,0); -- 10:22:00

-- 
SET @GUID0 := 168083; 		-- 78496; 132818  132814
SET @GUID1 := -168083; 		-- -78496;
SET @GUID2 := -166372;		-- -52330;
SET @W1 := 231880;
SET @W2 := 231881;
SET @W3 := 231882;
SET @W4 := 231883;
SET @W11 := 2318800;
SET @W12 := 2318801;
SET @W13 := 2318802;
SET @W14 := 2318803;
UPDATE `creature` SET `position_x`= -4236.136230, `position_y`= 313.865417, `position_z`= 160.389038, `orientation`= 3.5595 WHERE `guid`= @GUID0;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry` IN (22317, 23188, 22253);
UPDATE `creature_template` SET `InhabitType`= 4 WHERE `entry`=23225;
DELETE FROM `creature` WHERE `guid` IN (161639, 161638, 161640) AND `id`=23188; -- remove wrong spawns
UPDATE `smart_scripts` SET `event_type`=25 WHERE `entryorguid`=23311 AND `source_type`=0 AND `id`=11; -- Fix an aura set by spawn instead of reset
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@GUID1, @GUID2, 23188, 22253) AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (22317*100, 22317*100+1, 22317*100+2, @W11, @W12, @W13, @W14, 22253*100) AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@GUID1,0,0,0,1,0,100,0,2000,4000,12000,16000,12,23188,7,0,0,0,0,8,0,0,0,-4236.136230, 313.865417, 160.389038, 3.9795,"Netherwing Drake Escape Dummy - OOC - Summon Creature 'Dragonmaw Transporter'"),
(@GUID1,0,1,0,63,0,100,0,0,0,0,0,48,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Netherwing Drake Escape Dummy - Just created - Set active"),
(23188,0,0,0,54,0,100,0,0,0,0,0,87,@W11,@W12,@W13,0,0,0,1,0,0,0,0,0,0,0,"Dragonmaw Transporter - Just summoned  - action list"),
(@W11,9,0,0,0,0,100,0,0,0,0,0,53,1,@W1,0,0,0,2,1,0,0,0,0,0,0,0,"Dragonmaw Transporter - Action list - Start Waypoint"),
(@W11,9,1,0,0,0,100,0,0,0,0,0,48,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonmaw Transporter - Action list - Set Active On"),
(@W12,9,0,0,0,0,100,0,0,0,0,0,53,1,@W2,0,0,0,2,1,0,0,0,0,0,0,0,"Dragonmaw Transporter - Action list - Start Waypoint"),
(@W12,9,1,0,0,0,100,0,0,0,0,0,48,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonmaw Transporter - Action list - Set Active On"),
(@W13,9,0,0,0,0,100,0,0,0,0,0,53,1,@W3,0,0,0,2,1,0,0,0,0,0,0,0,"Dragonmaw Transporter - Action list - Start Waypoint"),
(@W13,9,1,0,0,0,100,0,0,0,0,0,48,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonmaw Transporter - Action list - Set Active On"),
(23188,0,1,0,58,0,100,0,27,@W1,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonmaw Transporter - On Waypoint Finished - Despawn Instant"),
(23188,0,2,0,58,0,100,0,31,@W2,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonmaw Transporter - On Waypoint Finished - Despawn Instant"),
(23188,0,3,0,58,0,100,0,25,@W3,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonmaw Transporter - On Waypoint Finished - Despawn Instant"),
(23188,0,4,0,58,0,100,0,26,@W4,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonmaw Transporter - On Waypoint Finished - Despawn Instant"),
(22253, 0, 0, 0, 0, 0, 100, 0, 3000, 5000, 7000, 7000, 11, 15496, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Dragonmaw Ascendant - IC - Cast Cleave"),
(22253, 0, 1, 0, 0, 0, 100, 0, 5000, 7000, 8000, 10000, 11, 17547, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Dragonmaw Ascendant - IC - Cast Mortal Strike"),
(22253, 0, 2, 0, 0, 0, 100, 0, 4000, 7000, 9000, 12000, 11, 10966, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Dragonmaw Ascendant - IC - Cast Uppercut"),
(@GUID2, 0, 0, 0, 0, 0, 100, 0, 3000, 5000, 7000, 7000, 11, 15496, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Dragonmaw Ascendant - IC - Cast Cleave"),
(@GUID2, 0, 1, 0, 0, 0, 100, 0, 5000, 7000, 8000, 10000, 11, 17547, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Dragonmaw Ascendant - IC - Cast Mortal Strike"),
(@GUID2, 0, 2, 0, 0, 0, 100, 0, 4000, 7000, 9000, 12000, 11, 10966, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Dragonmaw Ascendant - IC - Cast Uppercut"),
(@GUID2,0,3,0,1,0,100,0,2000,5000,12000,16000,12,23188,7,0,0,0,0,8,0,0,0,-4933.316895, 31.134706, 61.772137, 0.480736,"Dragonmaw Ascendant - OOC - Summon Creature 'Dragonmaw Transporter'"),
(@GUID2,0,4,0,63,0,100,0,0,0,0,0,48,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonmaw Ascendant - Just created - Set active"),
(23188,0,5,0,54,0,100,0,0,0,0,0,80,@W14,2,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonmaw Transporter - Just summoned - action list"),
(@W14,9,0,0,0,0,100,0,0,0,0,0,53,1,@W4,0,0,0,2,1,0,0,0,0,0,0,0,"Dragonmaw Transporter - action list - Start Waypoint"),
(@W14,9,1,0,0,0,100,0,0,0,0,0,48,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dragonmaw Transporter - action list - Set Active On"),
(23188, 0, 6, 0, 0, 0, 100, 0, 3000, 5000, 7000, 7000, 11, 38861, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Dragonmaw Transporter- IC - Aimed Shot"),
(23188, 0, 7, 0, 0, 0, 100, 0, 5000, 7000, 8000, 10000, 11, 19503, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Dragonmaw Transporter - IC - Scatter Shot"),
(23188, 0, 8, 0, 0, 0, 100, 0, 4000, 7000, 9000, 12000, 11, 38859, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Dragonmaw Transporter - IC - Serpent Sting"),
(23188, 0, 9, 0, 0, 0, 100, 0, 1000, 2000, 3000, 4000, 11, 38858, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, "Dragonmaw Transporter - IC - Shoot");

DELETE FROM conditions WHERE SourceTypeOrReferenceId=22 AND SourceEntry=23188;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorTextId, ScriptName, Comment) VALUES
(22, 1, 23188, 0, 0, 23, 0, 3939, 0, 0, 0, 0, '', 'Execute SmartAI for Dragonmaw Transporter if the area is 3759'),
(22, 6, 23188, 0, 0, 23, 0, 3759, 0, 0, 0, 0, '', 'Execute SmartAI for Dragonmaw Transporter if the area is 3759');

SET @PATH := @W1;
DELETE FROM `waypoints` WHERE `entry`=@PATH;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(@PATH,1,-4234.259,316.7951,194.5695, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,2,-4278.778,291.9364,162.6098, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,3,-4315.755,272.5735,162.6098, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,4,-4332.82,267.5372,162.6098, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,5,-4354.233,260.8795,162.6098, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,6,-4391.55,249.5022,162.6098, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,7,-4429.059,238.4517,162.6098, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,8,-4470.008,227.2337,162.6098, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,9,-4489.761,222.9549,162.6098, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,10,-4502.434,220.6088,162.6098, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,11,-4528.817,218.5281,162.6098, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,12,-4546.15,218.6741,162.6098, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,13,-4595.704,217.5207,162.6098, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,14,-4641.978,205.2794,147.0265, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,15,-4662.014,198.3955,118.6931, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,16,-4686.042,195.7724,92.6098, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,17,-4720.744,183.9892,92.33202, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,18,-4745.649,173.8856,98.19311, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,19,-4756.257,154.736,105.7487, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,20,-4761.057,143.5172,108.3876, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,21,-4787.247,129.8356,110.6098, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,22,-4815.383,124.4918,109.6376, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,23,-4841.104,99.13585,116.1653, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,24,-4876.217,68.20888,99.16536, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,25,-4887.112,56.80024,92.74867, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,26,-4921.727,36.11827,73.94312, 'Dragonmaw Transporter'), -- 07:14:59
(@PATH,27,-4924.737,36.20354,61.87088, 'Dragonmaw Transporter'); -- 07:14:59
-- 0x1C09FC424016A500000019000022323C .go -4234.259 316.7951 194.5695
 
-- Pathing for Dragonmaw Transporter Entry: 23188 'ark FORMAT'
SET @PATH := @W2;
DELETE FROM `waypoints` WHERE `entry`=@PATH;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(@PATH,1,-4235.772,310.6806,195.9172, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,2,-4266.868,305.2986,170.0554, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,3,-4289.381,299.2866,169.0554, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,4,-4313.463,296.8451,169.0554, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,5,-4334.991,295.7913,169.0554, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,6,-4355.52,290.1741,169.0554, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,7,-4382.983,278.409,169.0554, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,8,-4419.237,271.8036,169.0554, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,9,-4448.44,268.7892,169.0554, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,10,-4463.974,265.9718,169.0554, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,11,-4486.522,265.1359,165.4998, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,12,-4515.319,266.4659,154.3332, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,13,-4538.145,266.9955,143.7777, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,14,-4565.51,267.0066,134.7498, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,15,-4574.724,266.6996,130.4999, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,16,-4585.344,265.8585,125.2221, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,17,-4610.452,266.8059,114.0276, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,18,-4648.119,265.0245,89.41651, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,19,-4679.999,264.3499,80.02769, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,20,-4726.6,265.6508,91.11095, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,21,-4757.61,263.9644,96.61092, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,22,-4790.494,252.6213,107.7221, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,23,-4830.46,243.5237,113.6109, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,24,-4850.946,232.3608,114.611, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,25,-4865.539,204.393,115.9165, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,26,-4867.515,184.822,112.5276, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,27,-4869.98,147.345,96.99986, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,28,-4875.779,115.5371,89.69432, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,29,-4900.512,79.47276,79.22215, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,30,-4920.873,41.16504,69.30544, 'Dragonmaw Transporter'), -- 07:15:20
(@PATH,31,-4924.737,36.20354,61.87088, 'Dragonmaw Transporter'); -- 07:15:20
-- 0x1C09FC424016A5000000190000223259 .go -4235.772 310.6806 195.9172
 
-- Pathing for Dragonmaw Transporter Entry: 23188 'ark FORMAT'
SET @PATH := @W3;
DELETE FROM `waypoints` WHERE `entry`=@PATH;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(@PATH,1,-4235.186,312.622,195.6112, 'Dragonmaw Transporter'), -- 07:18:37
(@PATH,2,-4234.272,312.2153,195.6112, 'Dragonmaw Transporter'), -- 07:18:37
(@PATH,3,-4293.566,245.1756,179.3634, 'Dragonmaw Transporter'), -- 07:18:37
(@PATH,4,-4305.508,238.4082,179.3634, 'Dragonmaw Transporter'), -- 07:18:37
(@PATH,5,-4329.843,217.8027,179.3634, 'Dragonmaw Transporter'), -- 07:18:37
(@PATH,6,-4362.729,186.0796,186.419, 'Dragonmaw Transporter'), -- 07:18:37
(@PATH,7,-4434.846,123.756,230.3912, 'Dragonmaw Transporter'), -- 07:18:37
(@PATH,8,-4459.073,85.18902,233.9189, 'Dragonmaw Transporter'), -- 07:18:37
(@PATH,9,-4482.534,56.35666,232.5023, 'Dragonmaw Transporter'), -- 07:18:37
(@PATH,10,-4493.029,34.64518,235.1689, 'Dragonmaw Transporter'), -- 07:18:37
(@PATH,11,-4503.293,2.772352,232.5856, 'Dragonmaw Transporter'), -- 07:18:37
(@PATH,12,-4536.873,-16.30306,224.7523, 'Dragonmaw Transporter'), -- 07:18:37
(@PATH,13,-4579.444,-18.38878,223.5301, 'Dragonmaw Transporter'), -- 07:18:37
(@PATH,14,-4611.417,9.642578,219.03, 'Dragonmaw Transporter'), -- 07:18:37
(@PATH,15,-4660.565,11.25814,228.7522, 'Dragonmaw Transporter'), -- 07:18:37
(@PATH,16,-4698.878,14.15853,227.3911, 'Dragonmaw Transporter'), -- 07:18:37
(@PATH,17,-4734.97,25.07422,223.0023, 'Dragonmaw Transporter'), -- 07:18:37
(@PATH,18,-4766.538,46.62153,220.8356, 'Dragonmaw Transporter'), -- 07:18:37
(@PATH,19,-4794.966,67.12045,197.8634, 'Dragonmaw Transporter'), -- 07:18:37
(@PATH,20,-4815.075,72.55089,183.6967, 'Dragonmaw Transporter'), -- 07:18:37
(@PATH,21,-4855.917,67.18316,133.6689, 'Dragonmaw Transporter'), -- 07:18:37
(@PATH,22,-4868.51,61.47526,116.2801, 'Dragonmaw Transporter'), -- 07:18:37
(@PATH,23,-4890.089,51.30317,92.11338, 'Dragonmaw Transporter'), -- 07:18:37
(@PATH,24,-4922.806,35.50499,72.91895, 'Dragonmaw Transporter'), -- 07:18:37
(@PATH,25,-4924.737,36.20354,61.87088, 'Dragonmaw Transporter'); -- 07:18:37
-- 0x1C09FC424016A50000001900002232FF .go -4235.186 312.622 195.6112
 
-- Pathing for Dragonmaw Transporter Entry: 23188 'ark FORMAT'
SET @PATH := @W4;
DELETE FROM `waypoints` WHERE `entry`=@PATH;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(@PATH,1,-4921.116,38.40239,62.79848, 'Dragonmaw Transporter'), -- 07:15:14
(@PATH,2,-4920.266,38.92785,62.79848, 'Dragonmaw Transporter'), -- 07:15:14
(@PATH,3,-4911.522,44.50662,65.54009, 'Dragonmaw Transporter'), -- 07:15:14
(@PATH,4,-4897.991,49.12988,69.23454, 'Dragonmaw Transporter'), -- 07:15:14
(@PATH,5,-4854.699,71.66743,69.23454, 'Dragonmaw Transporter'), -- 07:15:14
(@PATH,6,-4811.554,91.95888,69.23454, 'Dragonmaw Transporter'), -- 07:15:14
(@PATH,7,-4782.642,107.2382,69.23454, 'Dragonmaw Transporter'), -- 07:15:14
(@PATH,8,-4749.689,123.6898,102.4568, 'Dragonmaw Transporter'), -- 07:15:14
(@PATH,9,-4717.377,120.1987,102.5401, 'Dragonmaw Transporter'), -- 07:15:14
(@PATH,10,-4677.343,111.8249,122.37344, 'Dragonmaw Transporter'), -- 07:15:14
(@PATH,11,-4642.299,106.9923,122.62343, 'Dragonmaw Transporter'), -- 07:15:14
(@PATH,12,-4595.685,101.0696,122.23454, 'Dragonmaw Transporter'), -- 07:15:14
(@PATH,13,-4568.682,107.7912,122.23454, 'Dragonmaw Transporter'), -- 07:15:14
(@PATH,14,-4532.451,105.1658,122.23454, 'Dragonmaw Transporter'), -- 07:15:14
(@PATH,15,-4502.495,109.315,122.23454, 'Dragonmaw Transporter'), -- 07:15:14
(@PATH,16,-4478.215,118.6488,122.23454, 'Dragonmaw Transporter'), -- 07:15:14
(@PATH,17,-4437.049,132.6271,122.23454, 'Dragonmaw Transporter'), -- 07:15:14
(@PATH,18,-4401.484,131.5858,122.23454, 'Dragonmaw Transporter'), -- 07:15:14
(@PATH,19,-4360.693,156.9551,122.37343, 'Dragonmaw Transporter'), -- 07:15:14
(@PATH,20,-4324.191,184.9894,122.9568, 'Dragonmaw Transporter'), -- 07:15:14
(@PATH,21,-4299.081,216.2382,141.7901, 'Dragonmaw Transporter'), -- 07:15:14
(@PATH,22,-4292.715,227.4521,179.9077, 'Dragonmaw Transporter'), -- 07:15:14
(@PATH,23,-4281.613,263.6761,179.9077, 'Dragonmaw Transporter'), -- 07:15:14
(@PATH,24,-4260.6,294.3777,179.9077, 'Dragonmaw Transporter'), -- 07:15:14
(@PATH,25,-4240.507,326.8979,154.0465, 'Dragonmaw Transporter'), -- 07:15:14
(@PATH,26,-4240.507,326.8979,154.0465, 'Dragonmaw Transporter'); -- 07:15:14
-- 0x1C09FC424016A5000000190000223269 .go -4921.116 38.40239 62.79848









