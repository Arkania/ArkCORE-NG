UPDATE `gossip_menu_option` SET `action_menu_id`=9753 WHERE `menu_id`=9754;

-- Hall of Stone formation fixes
UPDATE `creature_formations` SET `angle`=310, `point_1`=1, `point_2`=3 WHERE `leaderGUID`=234018 AND `memberGUID`=234035;
UPDATE `creature_formations` SET `angle`=50, `point_1`=1, `point_2`=3 WHERE `leaderGUID`=234018 AND `memberGUID`=234034;
UPDATE `creature_formations` SET `angle`=310, `point_1`=3, `point_2`=7 WHERE `leaderGUID`=234032 AND `memberGUID`=234022;
UPDATE `creature_formations` SET `angle`=50, `point_1`=3, `point_2`=7 WHERE `leaderGUID`=234032 AND `memberGUID`=234027;
UPDATE `creature_formations` SET `angle`=310, `point_1`=2, `point_2`=6 WHERE `leaderGUID`=234037 AND `memberGUID`=234020;
UPDATE `creature_formations` SET `angle`=50, `point_1`=2, `point_2`=6 WHERE `leaderGUID`=234037 AND `memberGUID`=234026;
UPDATE `creature_formations` SET `angle`=310, `point_1`=4, `point_2`=8 WHERE `leaderGUID`=234040 AND `memberGUID`=234014;
UPDATE `creature_formations` SET `angle`=50, `point_1`=4, `point_2`=8 WHERE `leaderGUID`=234040 AND `memberGUID`=234024;
UPDATE `creature_formations` SET `angle`=50, `point_1`=4, `point_2`=8 WHERE `leaderGUID`=234031 AND `memberGUID`=234013;
UPDATE `creature_formations` SET `angle`=310, `point_1`=4, `point_2`=8 WHERE `leaderGUID`=234031 AND `memberGUID`=234023;
UPDATE `creature_formations` SET `dist`=4, `point_1`=2, `point_2`=4 WHERE `leaderGUID`=234012 AND `memberGUID`=234011;
UPDATE `creature_formations` SET `angle`=310, `point_1`=1, `point_2`=3 WHERE `leaderGUID`=234038 AND `memberGUID`=234016;
UPDATE `creature_formations` SET `angle`=50, `point_1`=1, `point_2`=3 WHERE `leaderGUID`=234038 AND `memberGUID`=234015;

DELETE FROM `creature_text` WHERE `entry` =23257 and `groupid`=0 and `id` in(7,8,9);
DELETE FROM `creature_text` WHERE `entry` =22982 and `groupid`=0 and `id` in(5,6);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `comment`) VALUES 
(23257, 0, 7, "Well one thing's for sure, $N's not a nugget any more!", 12, 0, 100, 0, 0, 0, 21896, "Skyguard Windcharger"),
(23257, 0, 8, "Buzz the landing pad lately, $N?", 12, 0, 100, 0, 0, 0, 21889, "Skyguard Windcharger"),
(23257, 0, 9, "The list of Skyguard members is long and distinguished.  $N tops that list.", 12, 0, 100, 0, 0, 0, 21939, "Skyguard Windcharger"),
(22982, 0, 5, "Well, if it isn't our resident $G flyboy : flygirl;, $N.  How's it going, ace?", 12, 0, 100, 0, 0, 0, 21898, "Skyguard Navigator"),
(22982, 0, 6, "Hey, it's our ace flyer, $N!", 12, 0, 100, 0, 0, 0, 21883, "Skyguard Navigator");

-- Pathing for Death Knight Cavalier Entry: 16163 'ark FORMAT'
SET @NPC := 190350;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2828.418,`position_y`=-3128.86,`position_z`=273.8336 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,25278,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2828.418,-3128.86,273.8336,0,0,0,0,100,0),
(@PATH,2,2828.67,-3097.49,273.8114,0,0,0,0,100,0),
(@PATH,3,2824.122,-3127.451,273.8372,0,0,0,0,100,0),
(@PATH,4,2813.568,-3143.734,273.8355,0,0,0,0,100,0),
(@PATH,5,2801.097,-3163.161,273.787,0,0,0,0,100,0),
(@PATH,6,2799.644,-3189.22,273.787,0,0,0,0,100,0),
(@PATH,7,2820.002,-3202.299,273.7898,0,0,0,0,100,0),
(@PATH,8,2844.853,-3200.758,273.787,0,0,0,0,100,0),
(@PATH,9,2848.53,-3180.427,273.787,0,0,0,0,100,0),
(@PATH,10,2827.984,-3152.95,273.787,0,0,0,0,100,0);

-- Pathing for Death Knight Cavalier Entry: 16163 'ark FORMAT'
SET @NPC := 190351;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2831.418,`position_y`=-3128.86,`position_z`=273.8336 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,25278,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2828.418,-3128.86,273.8336,0,0,0,0,100,0),
(@PATH,2,2828.67,-3097.49,273.8114,0,0,0,0,100,0),
(@PATH,3,2824.122,-3127.451,273.8372,0,0,0,0,100,0),
(@PATH,4,2813.568,-3143.734,273.8355,0,0,0,0,100,0),
(@PATH,5,2801.097,-3163.161,273.787,0,0,0,0,100,0),
(@PATH,6,2799.644,-3189.22,273.787,0,0,0,0,100,0),
(@PATH,7,2820.002,-3202.299,273.7898,0,0,0,0,100,0),
(@PATH,8,2844.853,-3200.758,273.787,0,0,0,0,100,0),
(@PATH,9,2848.53,-3180.427,273.787,0,0,0,0,100,0),
(@PATH,10,2827.984,-3152.95,273.787,0,0,0,0,100,0);

-- Pathing for Death Knight Cavalier Entry: 16163 'ark FORMAT' 
SET @NPC := 190352; -- 127747
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2561.589,`position_y`=-3158.63,`position_z`=240.5253 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,25278,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2561.589,-3158.63,240.5253,0,0,0,0,100,0), -- 00:55:40
(@PATH,2,2577.802,-3151.077,240.5241,0,0,0,0,100,0), -- 00:55:45
(@PATH,3,2585.239,-3138.162,240.5253,0,0,0,0,100,0), -- 00:55:52
(@PATH,4,2585.295,-3121.586,240.5244,0,0,0,0,100,0), -- 00:55:58
(@PATH,5,2580.453,-3111.228,240.5249,0,0,0,0,100,0), -- 00:56:05
(@PATH,6,2584.915,-3101.806,240.5252,0,0,0,0,100,0), -- 00:56:09
(@PATH,7,2608.073,-3078.412,240.5271,0,0,0,0,100,0), -- 00:56:14
(@PATH,8,2627.942,-3058.567,240.5237,0,0,0,0,100,0), -- 00:56:27
(@PATH,9,2645.011,-3041.33,240.523,0,0,0,0,100,0), -- 00:56:38
(@PATH,10,2664.399,-3022.119,240.5253,0,0,0,0,100,0), -- 00:56:47
(@PATH,11,2673.592,-3015.558,240.5253,0,0,0,0,100,0), -- 00:56:58
(@PATH,12,2692.232,-3014.315,240.5253,0,0,0,0,100,0), -- 00:57:02
(@PATH,13,2715.057,-3011.801,240.5254,0,0,0,0,100,0), -- 00:57:10
(@PATH,14,2728.214,-2992.568,240.5253,0,0,0,0,100,0), -- 00:57:19
(@PATH,15,2725.241,-2970.892,240.5249,0,0,0,0,100,0), -- 00:57:29
(@PATH,16,2710.557,-2958.161,240.5251,0,0,0,0,100,0), -- 00:57:38
(@PATH,17,2685.363,-2959.393,240.5253,0,0,0,0,100,0), -- 00:57:45
(@PATH,18,2671.24,-2977.426,240.5248,0,0,0,0,100,0), -- 00:57:56
(@PATH,19,2671.708,-2994.812,240.5246,0,0,0,0,100,0), -- 00:58:04
(@PATH,20,2670.703,-3012.506,240.5252,0,0,0,0,100,0), -- 00:58:12
(@PATH,21,2663.621,-3021.305,240.5253,0,0,0,0,100,0), -- 00:58:19
(@PATH,22,2644.285,-3041.24,240.523,0,0,0,0,100,0), -- 00:58:24
(@PATH,23,2627.018,-3058.662,240.5237,0,0,0,0,100,0), -- 00:58:35
(@PATH,24,2607.562,-3078.047,240.5271,0,0,0,0,100,0), -- 00:58:44
(@PATH,25,2583.966,-3101.257,240.5253,0,0,0,0,100,0), -- 00:58:55
(@PATH,26,2575.257,-3105.696,240.5253,0,0,0,0,100,0), -- 00:59:08
(@PATH,27,2561.672,-3099.622,240.5251,0,0,0,0,100,0), -- 00:59:11
(@PATH,28,2542.95,-3102.525,240.5249,0,0,0,0,100,0), -- 00:59:17
(@PATH,29,2529.021,-3116.719,240.5249,0,0,0,0,100,0), -- 00:59:26
(@PATH,30,2527.216,-3133.08,240.5253,0,0,0,0,100,0), -- 00:59:33
(@PATH,31,2530.838,-3143.624,240.5245,0,0,0,0,100,0), -- 00:59:40
(@PATH,32,2537.175,-3152.094,240.524,0,0,0,0,100,0), -- 00:59:44
(@PATH,33,2547.807,-3157.692,240.5253,0,0,0,0,100,0); -- 00:59:49

-- Pathing for Death Knight Cavalier Entry: 16163 'ark FORMAT' 
SET @NPC := 190353; -- 127746
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2561.589,`position_y`=-3158.63,`position_z`=240.5253 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,25278,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2561.589,-3158.63,240.5253,0,0,0,0,100,0), -- 00:55:40
(@PATH,2,2577.802,-3151.077,240.5241,0,0,0,0,100,0), -- 00:55:45
(@PATH,3,2585.239,-3138.162,240.5253,0,0,0,0,100,0), -- 00:55:52
(@PATH,4,2585.295,-3121.586,240.5244,0,0,0,0,100,0), -- 00:55:58
(@PATH,5,2580.453,-3111.228,240.5249,0,0,0,0,100,0), -- 00:56:05
(@PATH,6,2584.915,-3101.806,240.5252,0,0,0,0,100,0), -- 00:56:09
(@PATH,7,2608.073,-3078.412,240.5271,0,0,0,0,100,0), -- 00:56:14
(@PATH,8,2627.942,-3058.567,240.5237,0,0,0,0,100,0), -- 00:56:27
(@PATH,9,2645.011,-3041.33,240.523,0,0,0,0,100,0), -- 00:56:38
(@PATH,10,2664.399,-3022.119,240.5253,0,0,0,0,100,0), -- 00:56:47
(@PATH,11,2673.592,-3015.558,240.5253,0,0,0,0,100,0), -- 00:56:58
(@PATH,12,2692.232,-3014.315,240.5253,0,0,0,0,100,0), -- 00:57:02
(@PATH,13,2715.057,-3011.801,240.5254,0,0,0,0,100,0), -- 00:57:10
(@PATH,14,2728.214,-2992.568,240.5253,0,0,0,0,100,0), -- 00:57:19
(@PATH,15,2725.241,-2970.892,240.5249,0,0,0,0,100,0), -- 00:57:29
(@PATH,16,2710.557,-2958.161,240.5251,0,0,0,0,100,0), -- 00:57:38
(@PATH,17,2685.363,-2959.393,240.5253,0,0,0,0,100,0), -- 00:57:45
(@PATH,18,2671.24,-2977.426,240.5248,0,0,0,0,100,0), -- 00:57:56
(@PATH,19,2671.708,-2994.812,240.5246,0,0,0,0,100,0), -- 00:58:04
(@PATH,20,2670.703,-3012.506,240.5252,0,0,0,0,100,0), -- 00:58:12
(@PATH,21,2663.621,-3021.305,240.5253,0,0,0,0,100,0), -- 00:58:19
(@PATH,22,2644.285,-3041.24,240.523,0,0,0,0,100,0), -- 00:58:24
(@PATH,23,2627.018,-3058.662,240.5237,0,0,0,0,100,0), -- 00:58:35
(@PATH,24,2607.562,-3078.047,240.5271,0,0,0,0,100,0), -- 00:58:44
(@PATH,25,2583.966,-3101.257,240.5253,0,0,0,0,100,0), -- 00:58:55
(@PATH,26,2575.257,-3105.696,240.5253,0,0,0,0,100,0), -- 00:59:08
(@PATH,27,2561.672,-3099.622,240.5251,0,0,0,0,100,0), -- 00:59:11
(@PATH,28,2542.95,-3102.525,240.5249,0,0,0,0,100,0), -- 00:59:17
(@PATH,29,2529.021,-3116.719,240.5249,0,0,0,0,100,0), -- 00:59:26
(@PATH,30,2527.216,-3133.08,240.5253,0,0,0,0,100,0), -- 00:59:33
(@PATH,31,2530.838,-3143.624,240.5245,0,0,0,0,100,0), -- 00:59:40
(@PATH,32,2537.175,-3152.094,240.524,0,0,0,0,100,0), -- 00:59:44
(@PATH,33,2547.807,-3157.692,240.5253,0,0,0,0,100,0); -- 00:59:49

-- Pathing for Death Knight Cavalier Entry: 16163 'ark FORMAT' 
SET @NPC := 190354;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2529.461,`position_y`=-3350.972,`position_z`=267.5927 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,25278,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2529.461,-3350.972,267.5927,0,0,0,0,100,0), -- 00:55:41
(@PATH,2,2530.323,-3325.176,267.5925,0,0,0,0,100,0), -- 00:55:47
(@PATH,3,2543.675,-3311.973,267.593,0,0,0,0,100,0), -- 00:55:58
(@PATH,4,2556.406,-3299.54,267.593,0,0,0,0,100,0), -- 00:56:05
(@PATH,5,2555.974,-3276.286,267.5939,0,0,0,0,100,0), -- 00:56:13
(@PATH,6,2556.132,-3255.743,258.8458,0,0,0,0,100,0), -- 00:56:21
(@PATH,7,2556.734,-3215.111,240.5262,0,0,0,0,100,0), -- 00:56:31
(@PATH,8,2556.227,-3191.951,240.5252,0,0,0,0,100,0), -- 00:56:49
(@PATH,9,2556.103,-3169.521,240.5253,0,0,0,0,100,0), -- 00:56:58
(@PATH,10,2544.249,-3156.771,240.5248,0,0,0,0,100,0), -- 00:57:07
(@PATH,11,2530.144,-3142.768,240.5245,0,0,0,0,100,0), -- 00:57:13
(@PATH,12,2526.182,-3127.083,240.5254,0,0,0,0,100,0), -- 00:57:22
(@PATH,13,2529.482,-3115.22,240.5248,0,0,0,0,100,0), -- 00:57:28
(@PATH,14,2541.532,-3103.333,240.5248,0,0,0,0,100,0), -- 00:57:33
(@PATH,15,2554.839,-3099.154,240.5252,0,0,0,0,100,0), -- 00:57:40
(@PATH,16,2573.704,-3104.429,240.5253,0,0,0,0,100,0), -- 00:57:45
(@PATH,17,2584.594,-3120.166,240.5245,0,0,0,0,100,0), -- 00:57:53
(@PATH,18,2579.713,-3142.299,240.5249,0,0,0,0,100,0), -- 00:58:01
(@PATH,19,2568.922,-3153.001,240.5249,0,0,0,0,100,0), -- 00:58:10
(@PATH,20,2556.966,-3168.974,240.5253,0,0,0,0,100,0), -- 00:58:16
(@PATH,21,2556.745,-3191.808,240.5251,0,0,0,0,100,0), -- 00:58:24
(@PATH,22,2556.038,-3215.004,240.5273,0,0,0,0,100,0), -- 00:58:33
(@PATH,23,2555.711,-3255.515,258.7258,0,0,0,0,100,0), -- 00:58:42
(@PATH,24,2555.592,-3276.532,267.5936,0,0,0,0,100,0), -- 00:59:00
(@PATH,25,2556.91,-3299.243,267.5934,0,0,0,0,100,0), -- 00:59:10
(@PATH,26,2565.721,-3309.663,267.5924,0,0,0,0,100,0), -- 00:59:18
(@PATH,27,2580.893,-3321.083,267.5922,0,0,0,0,100,0), -- 00:59:23
(@PATH,28,2586.392,-3342.971,267.5935,0,0,0,0,100,0), -- 00:59:32
(@PATH,29,2578.376,-3360.212,267.5924,0,0,0,0,100,0), -- 00:59:40
(@PATH,30,2556.463,-3369.452,267.593,0,0,0,0,100,0), -- 00:59:47
(@PATH,31,2538.893,-3363.072,267.592,0,0,0,0,100,0); -- 00:59:57
-- 0x1C2F4042A00FC8C0004C5C00017F5587 .go 2529.461 -3350.972 267.5927

-- Pathing for Death Knight Cavalier Entry: 16163 'ark FORMAT' 
SET @NPC := 190355;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2529.461,`position_y`=-3350.972,`position_z`=267.5927 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,25278,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2529.461,-3350.972,267.5927,0,0,0,0,100,0), -- 00:55:41
(@PATH,2,2530.323,-3325.176,267.5925,0,0,0,0,100,0), -- 00:55:47
(@PATH,3,2543.675,-3311.973,267.593,0,0,0,0,100,0), -- 00:55:58
(@PATH,4,2556.406,-3299.54,267.593,0,0,0,0,100,0), -- 00:56:05
(@PATH,5,2555.974,-3276.286,267.5939,0,0,0,0,100,0), -- 00:56:13
(@PATH,6,2556.132,-3255.743,258.8458,0,0,0,0,100,0), -- 00:56:21
(@PATH,7,2556.734,-3215.111,240.5262,0,0,0,0,100,0), -- 00:56:31
(@PATH,8,2556.227,-3191.951,240.5252,0,0,0,0,100,0), -- 00:56:49
(@PATH,9,2556.103,-3169.521,240.5253,0,0,0,0,100,0), -- 00:56:58
(@PATH,10,2544.249,-3156.771,240.5248,0,0,0,0,100,0), -- 00:57:07
(@PATH,11,2530.144,-3142.768,240.5245,0,0,0,0,100,0), -- 00:57:13
(@PATH,12,2526.182,-3127.083,240.5254,0,0,0,0,100,0), -- 00:57:22
(@PATH,13,2529.482,-3115.22,240.5248,0,0,0,0,100,0), -- 00:57:28
(@PATH,14,2541.532,-3103.333,240.5248,0,0,0,0,100,0), -- 00:57:33
(@PATH,15,2554.839,-3099.154,240.5252,0,0,0,0,100,0), -- 00:57:40
(@PATH,16,2573.704,-3104.429,240.5253,0,0,0,0,100,0), -- 00:57:45
(@PATH,17,2584.594,-3120.166,240.5245,0,0,0,0,100,0), -- 00:57:53
(@PATH,18,2579.713,-3142.299,240.5249,0,0,0,0,100,0), -- 00:58:01
(@PATH,19,2568.922,-3153.001,240.5249,0,0,0,0,100,0), -- 00:58:10
(@PATH,20,2556.966,-3168.974,240.5253,0,0,0,0,100,0), -- 00:58:16
(@PATH,21,2556.745,-3191.808,240.5251,0,0,0,0,100,0), -- 00:58:24
(@PATH,22,2556.038,-3215.004,240.5273,0,0,0,0,100,0), -- 00:58:33
(@PATH,23,2555.711,-3255.515,258.7258,0,0,0,0,100,0), -- 00:58:42
(@PATH,24,2555.592,-3276.532,267.5936,0,0,0,0,100,0), -- 00:59:00
(@PATH,25,2556.91,-3299.243,267.5934,0,0,0,0,100,0), -- 00:59:10
(@PATH,26,2565.721,-3309.663,267.5924,0,0,0,0,100,0), -- 00:59:18
(@PATH,27,2580.893,-3321.083,267.5922,0,0,0,0,100,0), -- 00:59:23
(@PATH,28,2586.392,-3342.971,267.5935,0,0,0,0,100,0), -- 00:59:32
(@PATH,29,2578.376,-3360.212,267.5924,0,0,0,0,100,0), -- 00:59:40
(@PATH,30,2556.463,-3369.452,267.593,0,0,0,0,100,0), -- 00:59:47
(@PATH,31,2538.893,-3363.072,267.592,0,0,0,0,100,0); -- 00:59:57

-- Pathing for Death Knight Cavalier Entry: 16163 'ark FORMAT'
SET @NPC := 190356;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2907.542,`position_y`=-3166.655,`position_z`=273.787 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,25278,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2907.542,-3166.655,273.787,0,0,0,0,100,0), -- 00:46:47
(@PATH,2,2873.219,-3165.419,273.787,0,0,0,0,100,0), -- 00:46:54
(@PATH,3,2861.632,-3165.088,273.787,0,0,0,0,100,0), -- 00:47:09
(@PATH,4,2860.526,-3185.717,273.787,0,0,0,0,100,0), -- 00:47:13
(@PATH,5,2860.435,-3203.401,273.787,0,0,0,0,100,0), -- 00:47:21
(@PATH,6,2875.204,-3203.906,273.4088,0,0,0,0,100,0), -- 00:47:28
(@PATH,7,2892.834,-3204.38,273.3965,0,0,0,0,100,0), -- 00:47:34
(@PATH,8,2911.993,-3204.611,273.3846,0,0,0,0,100,0), -- 00:47:42
(@PATH,9,2926.023,-3200.403,273.3712,0,0,0,0,100,0), -- 00:47:49
(@PATH,10,2931.457,-3188.328,273.3712,0,0,0,0,100,0), -- 00:47:55
(@PATH,11,2925.778,-3167.298,273.787,0,0,0,0,100,0); -- 00:48:00

-- Pathing for Death Knight Cavalier Entry: 16163 'ark FORMAT'
SET @NPC := 190357;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2907.542,`position_y`=-3171.655,`position_z`=273.787 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,25278,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2907.542,-3166.655,273.787,0,0,0,0,100,0), -- 00:46:47
(@PATH,2,2873.219,-3165.419,273.787,0,0,0,0,100,0), -- 00:46:54
(@PATH,3,2861.632,-3165.088,273.787,0,0,0,0,100,0), -- 00:47:09
(@PATH,4,2860.526,-3185.717,273.787,0,0,0,0,100,0), -- 00:47:13
(@PATH,5,2860.435,-3203.401,273.787,0,0,0,0,100,0), -- 00:47:21
(@PATH,6,2875.204,-3203.906,273.4088,0,0,0,0,100,0), -- 00:47:28
(@PATH,7,2892.834,-3204.38,273.3965,0,0,0,0,100,0), -- 00:47:34
(@PATH,8,2911.993,-3204.611,273.3846,0,0,0,0,100,0), -- 00:47:42
(@PATH,9,2926.023,-3200.403,273.3712,0,0,0,0,100,0), -- 00:47:49
(@PATH,10,2931.457,-3188.328,273.3712,0,0,0,0,100,0), -- 00:47:55
(@PATH,11,2925.778,-3167.298,273.787,0,0,0,0,100,0); -- 00:48:00

-- Pathing for Death Knight Cavalier Entry: 16163 'ark FORMAT'
SET @NPC := 190358;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2787.931,`position_y`=-3363.628,`position_z`=267.6847 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,25278,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2787.931,-3363.628,267.6847,0,0,0,0,100,0),
(@PATH,2,2787.864,-3320.595,267.6845,0,0,0,0,100,0),
(@PATH,3,2787.388,-3287.191,267.6845,0,0,0,0,100,0),
(@PATH,4,2787.864,-3320.595,267.6845,0,0,0,0,100,0);

-- Pathing for Death Knight Cavalier Entry: 16163 'ark FORMAT'
SET @NPC := 190359;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2790.931,`position_y`=-3363.628,`position_z`=267.6847 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,25278,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2787.931,-3363.628,267.6847,0,0,0,0,100,0),
(@PATH,2,2787.864,-3320.595,267.6845,0,0,0,0,100,0),
(@PATH,3,2787.388,-3287.191,267.6845,0,0,0,0,100,0),
(@PATH,4,2787.864,-3320.595,267.6845,0,0,0,0,100,0);

-- Pathing for Death Knight Cavalier Entry: 16163 'ark FORMAT'
SET @NPC := 190360;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2910.233,`position_y`=-2955.379,`position_z`=267.593 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,25278,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2910.233,-2955.379,267.593,0,0,0,0,100,0), -- 00:55:44
(@PATH,2,2892.628,-2961.647,267.5928,0,0,0,0,100,0), -- 00:55:51
(@PATH,3,2884.039,-2971.864,267.5928,0,0,0,0,100,0), -- 00:56:00
(@PATH,4,2870.617,-2985.568,267.593,0,0,0,0,100,0), -- 00:56:05
(@PATH,5,2847.519,-2985.616,267.5938,0,0,0,0,100,0), -- 00:56:17
(@PATH,6,2831.011,-2985.781,260.82,0,0,0,0,100,0), -- 00:56:26
(@PATH,7,2811.443,-2985.972,250.9583,0,0,0,0,100,0), -- 00:56:34
(@PATH,8,2781.199,-2986.169,240.5266,0,0,0,0,100,0), -- 00:56:42
(@PATH,9,2763.189,-2986.039,240.5251,0,0,0,0,100,0), -- 00:56:54
(@PATH,10,2744.237,-2985.519,240.5253,0,0,0,0,100,0), -- 00:57:02
(@PATH,11,2734.137,-2977.427,240.5253,0,0,0,0,100,0), -- 00:57:10
(@PATH,12,2722.754,-2967.005,240.5245,0,0,0,0,100,0), -- 00:57:15
(@PATH,13,2708.031,-2957.228,240.5251,0,0,0,0,100,0), -- 00:57:21
(@PATH,14,2691.098,-2957.404,240.525,0,0,0,0,100,0), -- 00:57:28
(@PATH,15,2676.669,-2966.855,240.5253,0,0,0,0,100,0), -- 00:57:34
(@PATH,16,2671.321,-2976.635,240.5248,0,0,0,0,100,0), -- 00:57:42
(@PATH,17,2671.421,-2993.49,240.5246,0,0,0,0,100,0), -- 00:57:47
(@PATH,18,2680.976,-3008.883,240.5253,0,0,0,0,100,0), -- 00:57:53
(@PATH,19,2697.444,-3015.56,240.5247,0,0,0,0,100,0), -- 00:58:00
(@PATH,20,2713.618,-3012.186,240.5255,0,0,0,0,100,0), -- 00:58:07
(@PATH,21,2724.357,-3002.94,240.5247,0,0,0,0,100,0), -- 00:58:14
(@PATH,22,2734.208,-2991.862,240.5253,0,0,0,0,100,0), -- 00:58:19
(@PATH,23,2743.945,-2987.434,240.5253,0,0,0,0,100,0), -- 00:58:25
(@PATH,24,2763.65,-2986.421,240.5252,0,0,0,0,100,0), -- 00:58:30
(@PATH,25,2781.449,-2986.182,240.5266,0,0,0,0,100,0), -- 00:58:37
(@PATH,26,2811.903,-2985.583,251.1997,0,0,0,0,100,0), -- 00:58:45
(@PATH,27,2830.531,-2985.851,260.8194,0,0,0,0,100,0), -- 00:58:58
(@PATH,28,2847.362,-2985.841,267.5938,0,0,0,0,100,0), -- 00:59:07
(@PATH,29,2870.534,-2986.177,267.593,0,0,0,0,100,0), -- 00:59:14
(@PATH,30,2882.414,-2997.007,267.593,0,0,0,0,100,0), -- 00:59:22
(@PATH,31,2895.966,-3012.106,267.5926,0,0,0,0,100,0), -- 00:59:30
(@PATH,32,2915.716,-3014.353,267.5935,0,0,0,0,100,0), -- 00:59:37
(@PATH,33,2931.21,-3007.478,267.5931,0,0,0,0,100,0), -- 00:59:45
(@PATH,34,2938.199,-2994.229,267.5933,0,0,0,0,100,0), -- 00:59:53
(@PATH,35,2937.735,-2977.154,267.593,0,0,0,0,100,0), -- 00:59:59
(@PATH,36,2927.648,-2962.08,267.5935,0,0,0,0,100,0); -- 01:00:05

-- Pathing for Death Knight Cavalier Entry: 16163 'ark FORMAT'
SET @NPC := 190361;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2910.233,`position_y`=-2955.379,`position_z`=267.593 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,25278,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2910.233,-2955.379,267.593,0,0,0,0,100,0), -- 00:55:44
(@PATH,2,2892.628,-2961.647,267.5928,0,0,0,0,100,0), -- 00:55:51
(@PATH,3,2884.039,-2971.864,267.5928,0,0,0,0,100,0), -- 00:56:00
(@PATH,4,2870.617,-2985.568,267.593,0,0,0,0,100,0), -- 00:56:05
(@PATH,5,2847.519,-2985.616,267.5938,0,0,0,0,100,0), -- 00:56:17
(@PATH,6,2831.011,-2985.781,260.82,0,0,0,0,100,0), -- 00:56:26
(@PATH,7,2811.443,-2985.972,250.9583,0,0,0,0,100,0), -- 00:56:34
(@PATH,8,2781.199,-2986.169,240.5266,0,0,0,0,100,0), -- 00:56:42
(@PATH,9,2763.189,-2986.039,240.5251,0,0,0,0,100,0), -- 00:56:54
(@PATH,10,2744.237,-2985.519,240.5253,0,0,0,0,100,0), -- 00:57:02
(@PATH,11,2734.137,-2977.427,240.5253,0,0,0,0,100,0), -- 00:57:10
(@PATH,12,2722.754,-2967.005,240.5245,0,0,0,0,100,0), -- 00:57:15
(@PATH,13,2708.031,-2957.228,240.5251,0,0,0,0,100,0), -- 00:57:21
(@PATH,14,2691.098,-2957.404,240.525,0,0,0,0,100,0), -- 00:57:28
(@PATH,15,2676.669,-2966.855,240.5253,0,0,0,0,100,0), -- 00:57:34
(@PATH,16,2671.321,-2976.635,240.5248,0,0,0,0,100,0), -- 00:57:42
(@PATH,17,2671.421,-2993.49,240.5246,0,0,0,0,100,0), -- 00:57:47
(@PATH,18,2680.976,-3008.883,240.5253,0,0,0,0,100,0), -- 00:57:53
(@PATH,19,2697.444,-3015.56,240.5247,0,0,0,0,100,0), -- 00:58:00
(@PATH,20,2713.618,-3012.186,240.5255,0,0,0,0,100,0), -- 00:58:07
(@PATH,21,2724.357,-3002.94,240.5247,0,0,0,0,100,0), -- 00:58:14
(@PATH,22,2734.208,-2991.862,240.5253,0,0,0,0,100,0), -- 00:58:19
(@PATH,23,2743.945,-2987.434,240.5253,0,0,0,0,100,0), -- 00:58:25
(@PATH,24,2763.65,-2986.421,240.5252,0,0,0,0,100,0), -- 00:58:30
(@PATH,25,2781.449,-2986.182,240.5266,0,0,0,0,100,0), -- 00:58:37
(@PATH,26,2811.903,-2985.583,251.1997,0,0,0,0,100,0), -- 00:58:45
(@PATH,27,2830.531,-2985.851,260.8194,0,0,0,0,100,0), -- 00:58:58
(@PATH,28,2847.362,-2985.841,267.5938,0,0,0,0,100,0), -- 00:59:07
(@PATH,29,2870.534,-2986.177,267.593,0,0,0,0,100,0), -- 00:59:14
(@PATH,30,2882.414,-2997.007,267.593,0,0,0,0,100,0), -- 00:59:22
(@PATH,31,2895.966,-3012.106,267.5926,0,0,0,0,100,0), -- 00:59:30
(@PATH,32,2915.716,-3014.353,267.5935,0,0,0,0,100,0), -- 00:59:37
(@PATH,33,2931.21,-3007.478,267.5931,0,0,0,0,100,0), -- 00:59:45
(@PATH,34,2938.199,-2994.229,267.5933,0,0,0,0,100,0), -- 00:59:53
(@PATH,35,2937.735,-2977.154,267.593,0,0,0,0,100,0), -- 00:59:59
(@PATH,36,2927.648,-2962.08,267.5935,0,0,0,0,100,0); -- 01:00:05

DELETE FROM `creature_formations` WHERE `leaderGUID` IN (190350,190351,190352,190353,190354,190355,190356,190357,190358,190359,190360,190361);
DELETE FROM `creature_formations` WHERE `memberGUID` IN (190350,190351,190352,190353,190354,190355,190356,190357,190358,190359,190360,190361);
INSERT INTO `creature_formations` (`leaderGUID`,`memberGUID`,`dist`,`angle`,`groupAI`,`point_1`,`point_2`) VALUES
(190350,190350,0,0,2,0,0),
(190350,190351,3,90,2,2,0),
(190352,190352,0,0,2,0,0),
(190352,190353,3,270,2,0,0),
(190354,190354,0,0,2,0,0),
(190354,190355,3,270,2,0,0),
(190356,190356,0,0,2,0,0),
(190356,190357,3,270,2,0,0),
(190358,190358,0,0,2,0,0),
(190358,190359,3,270,2,1,3),
(190360,190360,0,0,2,0,0),
(190360,190361,3,270,2,0,0);

-- Pathing for Death Knight Entry: 16146 'ark FORMAT' 
SET @NPC := 190435;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2828.432,`position_y`=-3176.265,`position_z`=298.1476 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2828.432,-3176.265,298.1476,0,0,0,0,100,0), -- 00:46:45
(@PATH,2,2839.448,-3185.542,298.1487,0,0,0,0,100,0), -- 00:46:49
(@PATH,3,2848.306,-3195.512,298.1775,0,0,0,0,100,0), -- 00:46:54
(@PATH,4,2860.46,-3207.91,298.1058,0,0,0,0,100,0), -- 00:46:58
(@PATH,5,2871.515,-3216.969,298.1441,0,0,0,0,100,0), -- 00:47:02
(@PATH,6,2886.36,-3218.305,298.146,0,0,0,0,100,0), -- 00:47:07
(@PATH,7,2871.515,-3216.969,298.1441,0,0,0,0,100,0), -- 00:47:13
(@PATH,8,2860.46,-3207.91,298.1058,0,0,0,0,100,0), -- 00:47:17
(@PATH,9,2848.306,-3195.512,298.1775,0,0,0,0,100,0), -- 00:47:22
(@PATH,10,2839.448,-3185.542,298.1487,0,0,0,0,100,0), -- 00:47:27
(@PATH,11,2828.432,-3176.265,298.1476,0,0,0,0,100,0), -- 00:47:30
(@PATH,12,2813.296,-3175.835,298.1458,0,0,0,0,100,0), -- 00:47:35
(@PATH,13,2790.895,-3179.5,298.1464,0,0,0,0,100,0), -- 00:47:40
(@PATH,14,2813.296,-3175.835,298.1458,0,0,0,0,100,0); -- 00:47:49

-- Pathing for Dark Touched Warrior Entry: 16156 'ark FORMAT' 
SET @NPC := 190404;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2830.432,`position_y`=-3173.265,`position_z`=298.1476 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2828.432,-3176.265,298.1476,0,0,0,0,100,0), -- 00:46:45
(@PATH,2,2839.448,-3185.542,298.1487,0,0,0,0,100,0), -- 00:46:49
(@PATH,3,2848.306,-3195.512,298.1775,0,0,0,0,100,0), -- 00:46:54
(@PATH,4,2860.46,-3207.91,298.1058,0,0,0,0,100,0), -- 00:46:58
(@PATH,5,2871.515,-3216.969,298.1441,0,0,0,0,100,0), -- 00:47:02
(@PATH,6,2886.36,-3218.305,298.146,0,0,0,0,100,0), -- 00:47:07
(@PATH,7,2871.515,-3216.969,298.1441,0,0,0,0,100,0), -- 00:47:13
(@PATH,8,2860.46,-3207.91,298.1058,0,0,0,0,100,0), -- 00:47:17
(@PATH,9,2848.306,-3195.512,298.1775,0,0,0,0,100,0), -- 00:47:22
(@PATH,10,2839.448,-3185.542,298.1487,0,0,0,0,100,0), -- 00:47:27
(@PATH,11,2828.432,-3176.265,298.1476,0,0,0,0,100,0), -- 00:47:30
(@PATH,12,2813.296,-3175.835,298.1458,0,0,0,0,100,0), -- 00:47:35
(@PATH,13,2790.895,-3179.5,298.1464,0,0,0,0,100,0), -- 00:47:40
(@PATH,14,2813.296,-3175.835,298.1458,0,0,0,0,100,0); -- 00:47:49

-- Pathing for Dark Touched Warrior Entry: 16156 'ark FORMAT' 
SET @NPC := 190403;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2827.432,`position_y`=-3178.265,`position_z`=298.1476 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2828.432,-3176.265,298.1476,0,0,0,0,100,0), -- 00:46:45
(@PATH,2,2839.448,-3185.542,298.1487,0,0,0,0,100,0), -- 00:46:49
(@PATH,3,2848.306,-3195.512,298.1775,0,0,0,0,100,0), -- 00:46:54
(@PATH,4,2860.46,-3207.91,298.1058,0,0,0,0,100,0), -- 00:46:58
(@PATH,5,2871.515,-3216.969,298.1441,0,0,0,0,100,0), -- 00:47:02
(@PATH,6,2886.36,-3218.305,298.146,0,0,0,0,100,0), -- 00:47:07
(@PATH,7,2871.515,-3216.969,298.1441,0,0,0,0,100,0), -- 00:47:13
(@PATH,8,2860.46,-3207.91,298.1058,0,0,0,0,100,0), -- 00:47:17
(@PATH,9,2848.306,-3195.512,298.1775,0,0,0,0,100,0), -- 00:47:22
(@PATH,10,2839.448,-3185.542,298.1487,0,0,0,0,100,0), -- 00:47:27
(@PATH,11,2828.432,-3176.265,298.1476,0,0,0,0,100,0), -- 00:47:30
(@PATH,12,2813.296,-3175.835,298.1458,0,0,0,0,100,0), -- 00:47:35
(@PATH,13,2790.895,-3179.5,298.1464,0,0,0,0,100,0), -- 00:47:40
(@PATH,14,2813.296,-3175.835,298.1458,0,0,0,0,100,0); -- 00:47:49

DELETE FROM `creature_formations` WHERE `leaderGUID` IN (190435);
INSERT INTO `creature_formations` (`leaderGUID`,`memberGUID`,`dist`,`angle`,`groupAI`,`point_1`,`point_2`) VALUES
(190435,190435,0,0,2,0,0),
(190435,190403,3,270,2,5,12),
(190435,190404,3,90,2,5,12);

-- Pathing for Death Knight Captain Entry: 16145 'ark FORMAT' 
SET @NPC := 190456;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2863.143,`position_y`=-3303.327,`position_z`=298.1498 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2863.593,-3303.907,298.1498,0,0,0,0,100,0), -- 00:46:45
(@PATH,2,2869.523,-3320.972,298.1457,0,0,0,0,100,0), -- 00:46:50
(@PATH,3,2883.242,-3330.484,298.1457,0,0,0,0,100,0), -- 00:46:56
(@PATH,4,2869.523,-3320.972,298.1457,0,0,0,0,100,0), -- 00:47:03
(@PATH,5,2863.593,-3303.907,298.1498,0,0,0,0,100,0), -- 00:47:07
(@PATH,6,2865.348,-3285.952,298.0973,0,0,0,0,100,0), -- 00:47:12
(@PATH,7,2874.288,-3265.404,298.1561,0,0,0,0,100,0), -- 00:47:18
(@PATH,8,2865.348,-3285.952,298.0973,0,0,0,0,100,0); -- 00:47:27

-- Pathing for Death Knight Captain Entry: 16145 'ark FORMAT' 
SET @NPC := 190455;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2867.593,`position_y`=-3304.907,`position_z`=298.1498 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2863.593,-3303.907,298.1498,0,0,0,0,100,0), -- 00:46:45
(@PATH,2,2869.523,-3320.972,298.1457,0,0,0,0,100,0), -- 00:46:50
(@PATH,3,2883.242,-3330.484,298.1457,0,0,0,0,100,0), -- 00:46:56
(@PATH,4,2869.523,-3320.972,298.1457,0,0,0,0,100,0), -- 00:47:03
(@PATH,5,2863.593,-3303.907,298.1498,0,0,0,0,100,0), -- 00:47:07
(@PATH,6,2865.348,-3285.952,298.0973,0,0,0,0,100,0), -- 00:47:12
(@PATH,7,2874.288,-3265.404,298.1561,0,0,0,0,100,0), -- 00:47:18
(@PATH,8,2865.348,-3285.952,298.0973,0,0,0,0,100,0); -- 00:47:27

DELETE FROM `creature_formations` WHERE `leaderGUID` IN (190456);
INSERT INTO `creature_formations` (`leaderGUID`,`memberGUID`,`dist`,`angle`,`groupAI`,`point_1`,`point_2`) VALUES
(190456,190456,0,0,2,0,0),
(190456,190455,4,270,2,2,6);

-- Pathing for Shade of Naxxramas Entry: 16164 'ark FORMAT' 
SET @NPC := 190348;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2915.294,`position_y`=-3343.234,`position_z`=298.1457 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2915.294,-3343.234,298.1457,0,9000,0,0,100,0),
(@PATH,2,2898.639,-3327.008,298.1457,0,9000,0,0,100,0);

UPDATE `creature` SET `orientation`=5.51352 WHERE `guid` IN (190348,190345,190344);
DELETE FROM `creature_formations` WHERE `leaderGUID` IN (190348);
INSERT INTO `creature_formations` (`leaderGUID`,`memberGUID`,`dist`,`angle`,`groupAI`,`point_1`,`point_2`) VALUES
(190348,190348,0,0,2,0,0),
(190348,190345,2,360,2,1,2),
(190348,190344,2,180,2,1,2);

UPDATE `creature` SET `modelid`=0 WHERE `id` IN (16145,16146,16156,16163);

-- Pathing for Unholy Staff Entry: 16215 'ark FORMAT' 
SET @NPC := 190287;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2724.483,`position_y`=-3142.47,`position_z`=267.6181 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2724.483,-3142.47,267.6181,0,0,0,0,100,0), -- 00:55:47
(@PATH,2,2740.318,-3170.808,267.576,0,0,0,0,100,0); -- 00:56:00

-- Pathing for Unholy Staff Entry: 16215 'ark FORMAT' 
SET @NPC := 127817;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2721.483,`position_y`=-3144.47,`position_z`=267.6181 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2724.483,-3142.47,267.6181,0,0,0,0,100,0), -- 00:55:47
(@PATH,2,2740.318,-3170.808,267.576,0,0,0,0,100,0); -- 00:56:00

-- Pathing for Unholy Staff Entry: 16215 'ark FORMAT' 
SET @NPC := 190286;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2687.124,`position_y`=-3143.13,`position_z`=267.6205 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2687.124,-3143.13,267.6205,0,0,0,0,100,0), -- 00:55:49
(@PATH,2,2667.474,-3173.004,267.634,0,0,0,0,100,0); -- 00:56:04

-- Pathing for Unholy Staff Entry: 16215 'ark FORMAT' 
SET @NPC := 190283;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2684.124,`position_y`=-3142.13,`position_z`=267.6205 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2687.124,-3143.13,267.6205,0,0,0,0,100,0), -- 00:55:49
(@PATH,2,2667.474,-3173.004,267.634,0,0,0,0,100,0); -- 00:56:04

DELETE FROM `creature_formations` WHERE `leaderGUID` IN (190287,190286);
INSERT INTO `creature_formations` (`leaderGUID`,`memberGUID`,`dist`,`angle`,`groupAI`,`point_1`,`point_2`) VALUES
(190287,190287,0,0,2,0,0),
(190287,127817,3,270,2,1,2),
(190286,190286,0,0,2,0,0),
(190286,190283,3,270,2,1,2);

-- Pathing for Unholy Axe Entry: 16194 'ark FORMAT' 
SET @NPC := 190307;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2690.577,`position_y`=-3156.689,`position_z`=267.6078 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2690.577,-3156.689,267.6078,0,0,0,0,100,0), -- 00:55:41
(@PATH,2,2706.089,-3166.321,267.5782,0,0,0,0,100,0), -- 00:55:49
(@PATH,3,2721.288,-3159.098,267.5903,0,0,0,0,100,0), -- 00:55:56
(@PATH,4,2723.902,-3133.336,267.6333,0,0,0,0,100,0), -- 00:56:04
(@PATH,5,2706.458,-3124.162,267.6098,0,0,0,0,100,0), -- 00:56:13
(@PATH,6,2688.671,-3133.302,267.6201,0,0,0,0,100,0); -- 00:56:22

-- Pathing for Unholy Axe Entry: 16194 'ark FORMAT' 
SET @NPC := 190306;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2693.577,`position_y`=-3154.689,`position_z`=267.6078 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2690.577,-3156.689,267.6078,0,0,0,0,100,0), -- 00:55:41
(@PATH,2,2706.089,-3166.321,267.5782,0,0,0,0,100,0), -- 00:55:49
(@PATH,3,2721.288,-3159.098,267.5903,0,0,0,0,100,0), -- 00:55:56
(@PATH,4,2723.902,-3133.336,267.6333,0,0,0,0,100,0), -- 00:56:04
(@PATH,5,2706.458,-3124.162,267.6098,0,0,0,0,100,0), -- 00:56:13
(@PATH,6,2688.671,-3133.302,267.6201,0,0,0,0,100,0); -- 00:56:22

DELETE FROM `creature_formations` WHERE `leaderGUID` IN (190307);
INSERT INTO `creature_formations` (`leaderGUID`,`memberGUID`,`dist`,`angle`,`groupAI`,`point_1`,`point_2`) VALUES
(190307,190307,0,0,2,0,0),
(190307,190306,3,270,2,0,0);

-- Pathing for Unholy Swords Entry: 16216 'ark FORMAT' 
SET @NPC := 190281;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2740.497,`position_y`=-3216.551,`position_z`=267.6155 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2740.497,-3216.551,267.6155,0,0,0,0,100,0), -- 00:55:46
(@PATH,2,2735.71,-3191.704,267.4987,0,0,0,0,100,0), -- 00:55:54
(@PATH,3,2721.61,-3178.054,267.5587,0,0,0,0,100,0), -- 00:56:05
(@PATH,4,2735.71,-3191.704,267.4987,0,0,0,0,100,0), -- 00:56:14
(@PATH,5,2740.497,-3216.551,267.6155,0,0,0,0,100,0), -- 00:56:21
(@PATH,6,2734.737,-3239.713,267.602,0,0,0,0,100,0), -- 00:56:30
(@PATH,7,2717.949,-3253.626,267.6629,0,0,0,0,100,0), -- 00:56:40
(@PATH,8,2734.737,-3239.713,267.602,0,0,0,0,100,0); -- 00:56:50

-- Pathing for Unholy Swords Entry: 16216 'ark FORMAT' 
SET @NPC := 190280;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2743.497,`position_y`=-3216.551,`position_z`=267.6155 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2740.497,-3216.551,267.6155,0,0,0,0,100,0), -- 00:55:46
(@PATH,2,2735.71,-3191.704,267.4987,0,0,0,0,100,0), -- 00:55:54
(@PATH,3,2721.61,-3178.054,267.5587,0,0,0,0,100,0), -- 00:56:05
(@PATH,4,2735.71,-3191.704,267.4987,0,0,0,0,100,0), -- 00:56:14
(@PATH,5,2740.497,-3216.551,267.6155,0,0,0,0,100,0), -- 00:56:21
(@PATH,6,2734.737,-3239.713,267.602,0,0,0,0,100,0), -- 00:56:30
(@PATH,7,2717.949,-3253.626,267.6629,0,0,0,0,100,0), -- 00:56:40
(@PATH,8,2734.737,-3239.713,267.602,0,0,0,0,100,0); -- 00:56:50

DELETE FROM `creature_formations` WHERE `leaderGUID` IN (190281);
INSERT INTO `creature_formations` (`leaderGUID`,`memberGUID`,`dist`,`angle`,`groupAI`,`point_1`,`point_2`) VALUES
(190281,190281,0,0,2,0,0),
(190281,190280,4,90,2,3,7);

-- Pathing for Instructor Razuvious Entry: 16061 'ark FORMAT' 
SET @NPC := 189803;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2758.932,`position_y`=-3107.118,`position_z`=267.6845 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2758.932,-3107.118,267.6845,0,0,0,0,100,0),
(@PATH,2,2758.409,-3091.983,267.6845,0,0,0,0,100,0),
(@PATH,3,2772.748,-3085.515,267.6845,0,0,0,0,100,0),
(@PATH,4,2783.736,-3101.491,267.6845,0,0,0,0,100,0),
(@PATH,5,2772.544,-3112.944,267.6845,0,0,0,0,100,0);











