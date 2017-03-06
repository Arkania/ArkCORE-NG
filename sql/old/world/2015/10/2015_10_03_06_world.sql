
-- 
SET @DredgeWorm:=      8925;
SET @DeepStinger:=     8926;
SET @DarkScreecher:=   8927;
SET @Burrowing:=       8928;
SET @Creeper:=         8933;
SET @Beetle:=          8932;
SET @Gorosh:=          9027;
SET @Grizzle:=         9028;
SET @Eviscerator:=     9029;
SET @Okthor:=          9030;
SET @Anubshiah:=       9031;
SET @Hedrum:=          9032;

UPDATE `creature_template` SET `AIName`="SmartAI", `ScriptName`='' WHERE `entry` IN (@DredgeWorm, @DeepStinger, @DarkScreecher, @Burrowing, @Creeper, @Beetle, @Gorosh, @Grizzle, @Eviscerator, @Okthor, @Anubshiah, @Hedrum);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@DredgeWorm, @DeepStinger, @DarkScreecher, @Burrowing, @Creeper, @Beetle, @Gorosh, @Grizzle, @Eviscerator, @Okthor, @Anubshiah, @Hedrum) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@DredgeWorm,0,0,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,21,100,0,0,0,0,0,0,"@DredgeWorm - Just summoned - Start Attack"),
(@DeepStinger,0,0,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,21,100,0,0,0,0,0,0,"@DredgeWorm - Just summoned - Start Attack"),
(@DarkScreecher,0,0,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,21,100,0,0,0,0,0,0,"@DredgeWorm - Just summoned - Start Attack"),
(@Burrowing,0,0,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,21,100,0,0,0,0,0,0,"@DredgeWorm - Just summoned - Start Attack"),
(@Creeper,0,0,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,21,100,0,0,0,0,0,0,"@DredgeWorm - Just summoned - Start Attack"),
(@Beetle,0,0,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,21,100,0,0,0,0,0,0,"@DredgeWorm - Just summoned - Start Attack"),
(@Gorosh,0,0,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,21,100,0,0,0,0,0,0,"@DredgeWorm - Just summoned - Start Attack"),
(@Grizzle,0,0,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,21,100,0,0,0,0,0,0,"@DredgeWorm - Just summoned - Start Attack"),
(@Eviscerator,0,0,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,21,100,0,0,0,0,0,0,"@DredgeWorm - Just summoned - Start Attack"),
(@Okthor,0,0,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,21,100,0,0,0,0,0,0,"@DredgeWorm - Just summoned - Start Attack"),
(@Anubshiah,0,0,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,21,100,0,0,0,0,0,0,"@DredgeWorm - Just summoned - Start Attack"),
(@Hedrum,0,0,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,21,100,0,0,0,0,0,0,"@DredgeWorm - Just summoned - Start Attack"),
(@DredgeWorm,0,1,0,0,0,100,0,3000,4000,10000,15000,11,14535,0,0,0,0,0,5,0,0,0,0,0,0,0,"Dredge Worm - In Combat - Cast Dredge Sickness"),
(@DredgeWorm,0,2,0,0,0,100,0,4000,4000,8000,8000,11,13298,32,0,0,0,0,5,0,0,0,0,0,0,0,"Dredge Worm - In Combat - Cast Poison"),
(@DredgeWorm,0,3,0,0,0,100,0,5000,6000,3000,3000,11,6917,0,0,0,0,0,5,0,0,0,0,0,0,0,"Dredge Worm - In Combat - Cast Venom Spit)"),
(@DeepStinger,0,1,0,0,0,100,0,2000,2000,6000,8000,11,14534,0,0,0,0,0,5,0,0,0,0,0,0,0,"Deep Stinger - In Combat - Cast Barbed Sting"),
(@DeepStinger,0,2,0,0,0,100,0,4000,4000,4000,4000,11,40504,0,0,0,0,0,2,0,0,0,0,0,0,0,"Deep Stinger - In Combat - Cast Cleave"),
(@DarkScreecher,0,1,0,0,0,100,0,2000,2000,6000,8000,11,14538,0,0,0,0,0,5,0,0,0,0,0,0,0,"Dark Screecher - In Combat - Cast Aural Shock"),
(@DarkScreecher,0,2,0,0,0,100,0,4000,4000,9000,10000,11,8281,0,0,0,0,0,5,0,0,0,0,0,0,0,"Dark Screecher - In Combat - Cast Sonic Burst"),
(@Burrowing,0,1,0,0,0,100,0,2000,2000,30000,30000,11,14533,0,0,0,0,0,5,0,0,0,0,0,0,0,"Burrowing Thundersnout - In Combat - Cast Disjonction"),
(@Burrowing,0,2,0,0,0,100,0,3000,3000,3000,3000,11,15611,0,0,0,0,0,5,0,0,0,0,0,0,0,"Burrowing Thundersnout - In Combat - Cast Lizard Bolt"),
(@Burrowing,0,3,0,0,0,100,0,5000,5000,8000,8000,11,15548,0,0,0,0,0,5,0,0,0,0,0,0,0,"Burrowing Thundersnout - In Combat - Cast Thunderclap"),
(@Creeper,0,1,0,0,0,100,0,2000,2000,20000,20000,11,14532,0,0,0,0,0,5,0,0,0,0,0,0,0,"Cave Creeper - In Combat - Cast Creeper Venom"),
(@Creeper,0,2,0,0,0,100,0,4000,4000,8000,8000,11,745,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cave Creeper - In Combat - Cast Web"),
(@Creeper,0,3,0,0,0,100,0,5000,6000,4000,8000,11,15656,0,0,0,0,0,5,0,0,0,0,0,0,0,"Cave Creeper - In Combat - Cast Poisonous Stab"),
(@Beetle,0,1,0,0,0,100,0,2000,2000,30000,30000,11,14539,0,0,0,0,0,2,0,0,0,0,0,0,0,"Borer Beetle - In Combat - Cast Putrid Enzyme"),
(@Beetle,0,2,0,0,0,100,0,4000,4000,15000,20000,11,6016,0,0,0,0,0,5,0,0,0,0,0,0,0,"Borer Beetle - In Combat - Cast Pierce Armor"),
(@Gorosh,0,1,0,0,0,100,0,2000,4000,6000,8000,11,13736,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gorosh the Dervish - In Combat - Cast Whirlwind"),
(@Gorosh,0,2,0,0,0,100,0,4000,6000,5000,6000,11,15708,0,0,0,0,0,2,0,0,0,0,0,0,0,"Gorosh the Dervish - In Combat - Cast Mortal Strike"),
(@Gorosh,0,3,0,0,0,100,1,10000,15000,10000,15000,11,21049,0,0,0,0,0,1,0,0,0,0,0,0,0,"Gorosh the Dervish - In Combat - Cast Bloodlust"),
(@Grizzle,0,1,0,0,0,100,0,2000,3000,4000,5000,11,40504,0,0,0,0,0,2,0,0,0,0,0,0,0,"Grizzle the Dervish - In Combat - Cast Cleave"),
(@Grizzle,0,2,0,0,0,100,0,4000,5000,8000,9000,11,6524,0,0,0,0,0,2,0,0,0,0,0,0,0,"Grizzle the Dervish - In Combat - Cast Ground Tremor"),
(@Grizzle,0,3,0,0,0,100,1,10000,15000,10000,15000,11,8269,0,0,0,0,0,1,0,0,0,0,0,0,0,"Grizzle the Dervish - In Combat - Cast Frenzy"),
(@Grizzle,0,4,0,0,0,100,0,6000,7000,6000,9000,11,24458,0,0,0,0,0,5,0,0,0,0,0,0,0,"Grizzle the Dervish - In Combat - Cast Shadow Shock"),
(@Eviscerator,0,1,0,0,0,100,0,2000,3000,14000,15000,11,14331,0,0,0,0,0,2,0,0,0,0,0,0,0,"Eviscerator - In Combat - Cast Vicious Rend"),
(@Eviscerator,0,2,0,0,0,100,0,4000,5000,4000,5000,11,15245,0,0,0,0,0,2,0,0,0,0,0,0,0,"Eviscerator - In Combat - Cast Shadow Bolt Volley"),
(@Eviscerator,0,3,0,0,0,100,0,5000,6000,15000,16000,11,8269,0,0,0,0,0,1,0,0,0,0,0,0,0,"Eviscerator - In Combat - Cast Anti-Magic Shield"),
(@Okthor,0,1,0,0,0,100,0,2000,3000,4000,5000,11,15254,0,0,0,0,0,2,0,0,0,0,0,0,0,"Okthor - In Combat - Cast Arcane Bolt"),
(@Okthor,0,2,0,0,0,100,0,5000,6000,6000,7000,11,15453,0,0,0,0,0,2,0,0,0,0,0,0,0,"Okthor - In Combat - Cast Arcane Explosion"),
(@Okthor,0,3,0,0,0,100,0,9000,11000,11000,12000,11,13323,0,0,0,0,0,5,0,0,0,0,0,0,0,"Okthor - In Combat - Cast Polymorph"),
(@Okthor,0,4,0,0,0,100,0,7000,8000,9000,10000,11,13747,0,0,0,0,0,5,0,0,0,0,0,0,0,"Okthor - In Combat - Cast Slow"),
(@Anubshiah,0,1,0,0,0,100,0,5000,7000,10000,11000,11,8994,0,0,0,0,0,5,0,0,0,0,0,0,0,"Anubshiah - In Combat - Cast Banish"),
(@Anubshiah,0,2,0,0,0,100,0,2000,3000,8000,9000,11,15470,0,0,0,0,0,5,0,0,0,0,0,0,0,"Anubshiah - In Combat - Cast Curse of Tongues"),
(@Anubshiah,0,3,0,0,0,100,0,4000,5000,13000,15000,11,12493,0,0,0,0,0,5,0,0,0,0,0,0,0,"Anubshiah - In Combat - Cast Curse of Weakness"),
(@Anubshiah,0,4,0,0,0,100,0,1000,1000,300000,300000,11,13787,0,0,0,0,0,1,0,0,0,0,0,0,0,"Anubshiah - In Combat - Cast Demon Armor"),
(@Anubshiah,0,5,0,0,0,100,0,7000,8000,10000,13000,11,15471,0,0,0,0,0,5,0,0,0,0,0,0,0,"Anubshiah - In Combat - Cast Enveloping Web"),
(@Anubshiah,0,6,0,0,0,100,0,3000,4000,4000,5000,11,15472,0,0,0,0,0,5,0,0,0,0,0,0,0,"Anubshiah - In Combat - Cast Shadow Bolt"),
(@Hedrum,0,1,0,0,0,100,0,2000,2000,15000,18000,11,15475,0,0,0,0,0,5,0,0,0,0,0,0,0,"Hedrum - In Combat - Cast Baneful Poison"),
(@Hedrum,0,2,0,0,0,100,0,7000,9000,15000,18000,11,3609,0,0,0,0,0,5,0,0,0,0,0,0,0,"Hedrum - In Combat - Cast Paralyzing Poison"),
(@Hedrum,0,3,0,0,0,100,1,10000,15000,20000,25000,11,15474,0,0,0,0,0,5,0,0,0,0,0,0,0,"Hedrum - In Combat - Cast Web Explosion");

UPDATE `creature_template` SET `unit_flags`=131904 WHERE `entry`=10096;
DELETE FROM `creature_template_addon` WHERE `entry` IN (@DeepStinger);
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES 
(@DeepStinger, 1, '8601');

UPDATE `creature_text` SET `groupid`=4, `id`=1 WHERE `BroadcastTextId`=5441 AND `entry`=10096;
UPDATE `creature_text` SET `groupid`=0, `id`=1 WHERE `BroadcastTextId`=5442 AND `entry`=10096;
UPDATE `creature_text` SET `groupid`=1, `id`=1 WHERE `BroadcastTextId`=5443 AND `entry`=10096;
UPDATE `creature_text` SET `groupid`=5, `id`=1 WHERE `BroadcastTextId`=5444 AND `entry`=10096;
UPDATE `creature_text` SET `groupid`=2, `id`=1 WHERE `BroadcastTextId`=5445 AND `entry`=10096;
UPDATE `creature_text` SET `groupid`=3, `id`=1 WHERE `BroadcastTextId`=5446 AND `entry`=10096;
UPDATE `creature_text` SET `id`=0 WHERE `entry`=10096;

UPDATE `creature_formations` SET `point_1`=2, `point_2`=8 WHERE `leaderGUID`=232151 AND `memberGUID`<>232151;
UPDATE `creature_formations` SET `point_1`=1, `point_2`=5 WHERE `leaderGUID`=240410 AND `memberGUID`<>240410;
UPDATE `creature_formations` SET `point_1`=5, `point_2`=11 WHERE `leaderGUID`=256568 AND `memberGUID`<>256568;
UPDATE `creature_formations` SET `point_1`=1, `point_2`=8 WHERE `leaderGUID`=234591 AND `memberGUID`<>234591;
UPDATE `creature_formations` SET `point_1`=3, `point_2`=7 WHERE `leaderGUID`=239422 AND `memberGUID`<>239422;
UPDATE `creature_formations` SET `point_1`=1, `point_2`=5 WHERE `leaderGUID`=239432 AND `memberGUID`<>239432;
UPDATE `creature_formations` SET `point_1`=1, `point_2`=5 WHERE `leaderGUID`=239426 AND `memberGUID`<>239426;
UPDATE `creature_formations` SET `point_1`=1, `point_2`=10 WHERE `leaderGUID`=253977 AND `memberGUID`<>253977;

-- Pathing for Death Knight Captain Entry: 16145 'ark FORMAT' 
SET @NPC := 190463;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2556.952,`position_y`=-3294.904,`position_z`=267.5933 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2556.952,`position_y`=-3294.904,`position_z`=267.5933 WHERE `guid` IN (190418,190417,190447,190446);
DELETE FROM `creature_addon` WHERE `guid` IN (190418,190417,190447,190446);
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES
(190418,@PATH,0,0,1,0, ''), (190417,@PATH,0,0,1,0, ''), (190447,@PATH,0,0,1,0, ''), (190446,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2556.952,-3294.904,267.5933,0,0,0,0,100,0),
(@PATH,2,2556.655,-3273.629,266.7731,0,0,0,0,100,0),
(@PATH,3,2556.505,-3258.446,260.2637,0,0,0,0,100,0),
(@PATH,4,2556.29,-3229.774,245.2207,0,0,0,0,100,0),
(@PATH,5,2555.99,-3205.854,240.5267,0,0,0,0,100,0),
(@PATH,6,2555.881,-3183.735,240.5253,0,0,0,0,100,0),
(@PATH,7,2556.055,-3164.447,240.5253,0,0,0,0,100,0),
(@PATH,8,2556.121,-3141.804,240.5253,0,0,0,0,100,0),
(@PATH,9,2556.055,-3164.447,240.5253,0,0,0,0,100,0),
(@PATH,10,2555.881,-3183.735,240.5253,0,0,0,0,100,0),
(@PATH,11,2555.99,-3205.854,240.5267,0,0,0,0,100,0),
(@PATH,12,2556.29,-3229.774,245.2207,0,0,0,0,100,0),
(@PATH,13,2556.505,-3258.446,260.2637,0,0,0,0,100,0),
(@PATH,14,2556.655,-3273.629,266.7731,0,0,0,0,100,0),
(@PATH,15,2556.952,-3294.904,267.5933,0,0,0,0,100,0),
(@PATH,16,2556.716,-3318.195,267.593,0,0,0,0,100,0),
(@PATH,17,2556.767,-3335.356,267.593,0,0,0,0,100,0),
(@PATH,18,2556.716,-3318.195,267.593,0,0,0,0,100,0);

DELETE FROM `creature_formations` WHERE `leaderGUID` IN (190463);
INSERT INTO `creature_formations` (`leaderGUID`,`memberGUID`,`dist`,`angle`,`groupAI`,`point_1`,`point_2`) VALUES
(190463,190463,0,0,2,0,0),
(190463,190418,3,360,2,8,17),
(190463,190417,3,40,2,8,17),
(190463,190447,3,320,2,8,17),
(190463,190446,3,260,2,8,17);

-- Pathing for Death Knight Captain Entry: 16145 'ark FORMAT' 
SET @NPC := 190462;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2540.547,`position_y`=-3209.821,`position_z`=240.5256 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2540.547,`position_y`=-3209.821,`position_z`=240.5256 WHERE `guid` IN (190416,190415,190444,190445);
DELETE FROM `creature_addon` WHERE `guid` IN (190416,190415,190444,190445);
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES
(190416,@PATH,0,0,1,0, ''), (190415,@PATH,0,0,1,0, ''), (190444,@PATH,0,0,1,0, ''), (190445,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2540.547,-3209.821,240.5256,0,0,0,0,100,0),
(@PATH,2,2550.174,-3195.296,240.5253,0,0,0,0,100,0),
(@PATH,3,2550.015,-3178.325,240.5252,0,0,0,0,100,0),
(@PATH,4,2542.807,-3161.292,240.5246,0,0,0,0,100,0),
(@PATH,5,2531.76,-3145.814,240.5244,0,0,0,0,100,0),
(@PATH,6,2526.761,-3124.435,240.5252,0,0,0,0,100,0),
(@PATH,7,2535.071,-3107.707,240.5244,0,0,0,0,100,0),
(@PATH,8,2553.146,-3099.002,240.5252,0,0,0,0,100,0),
(@PATH,9,2568.556,-3098.702,240.5253,0,0,0,0,100,0),
(@PATH,10,2586.523,-3091.121,240.5253,0,0,0,0,100,0),
(@PATH,11,2599.675,-3076.474,240.5264,0,0,0,0,100,0),
(@PATH,12,2599.267,-3055.494,240.5239,0,0,0,0,100,0),
(@PATH,13,2618.495,-3035.821,240.5235,0,0,0,0,100,0),
(@PATH,14,2634.81,-3052.702,240.5237,0,0,0,0,100,0),
(@PATH,15,2651.288,-3069.151,240.5216,0,0,0,0,100,0),
(@PATH,16,2628.244,-3086.696,240.5232,0,0,0,0,100,0),
(@PATH,17,2608.684,-3085.287,240.5264,0,0,0,0,100,0),
(@PATH,18,2595.005,-3098.484,240.5253,0,0,0,0,100,0),
(@PATH,19,2587.623,-3116.573,240.5246,0,0,0,0,100,0),
(@PATH,20,2586.39,-3131.935,240.525,0,0,0,0,100,0),
(@PATH,21,2577.873,-3150.335,240.524,0,0,0,0,100,0),
(@PATH,22,2565.028,-3163.529,240.5253,0,0,0,0,100,0),
(@PATH,23,2559.751,-3177.576,240.5253,0,0,0,0,100,0),
(@PATH,24,2559.432,-3195.028,240.5254,0,0,0,0,100,0),
(@PATH,25,2570.551,-3210.158,240.5293,0,0,0,0,100,0),
(@PATH,26,2555.933,-3210.18,240.5274,0,0,0,0,100,0);

DELETE FROM `creature_formations` WHERE `leaderGUID` IN (190462);
INSERT INTO `creature_formations` (`leaderGUID`,`memberGUID`,`dist`,`angle`,`groupAI`,`point_1`,`point_2`) VALUES
(190462,190462,0,0,2,0,0),
(190462,190416,3,360,2,0,0),
(190462,190415,3,40,2,0,0),
(190462,190444,3,320,2,0,0),
(190462,190445,3,260,2,0,0);

-- Pathing for Death Knight Captain Entry: 16145 'ark FORMAT' 
SET @NPC := 190461;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2781.675,`position_y`=-2973.126,`position_z`=240.5271 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2781.675,`position_y`=-2973.126,`position_z`=240.5271 WHERE `guid` IN (190414,190413,190443,190442);
DELETE FROM `creature_addon` WHERE `guid` IN (190414,190413,190443,190442);
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES
(190414,@PATH,0,0,1,0, ''), (190413,@PATH,0,0,1,0, ''), (190443,@PATH,0,0,1,0, ''), (190442,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2781.675,-2973.126,240.5271,0,0,0,0,100,0),
(@PATH,2,2781.545,-2987.27,240.5265,0,0,0,0,100,0),
(@PATH,3,2781.296,-2999.196,240.5251,0,0,0,0,100,0),
(@PATH,4,2761.818,-2991.876,240.525,0,0,0,0,100,0),
(@PATH,5,2741.577,-2996.512,240.5255,0,0,0,0,100,0),
(@PATH,6,2720.587,-3007.503,240.5255,0,0,0,0,100,0),
(@PATH,7,2702.402,-3013.772,240.5244,0,0,0,0,100,0),
(@PATH,8,2678.602,-3021.83,240.5253,0,0,0,0,100,0),
(@PATH,9,2662.359,-3033.787,240.5253,0,0,0,0,100,0),
(@PATH,10,2656.579,-3044.628,240.5232,0,0,0,0,100,0),
(@PATH,11,2654.518,-3070.607,240.5216,0,0,0,0,100,0),
(@PATH,12,2642.806,-3082.523,240.5241,0,0,0,0,100,0),
(@PATH,13,2625.915,-3067.382,240.5231,0,0,0,0,100,0),
(@PATH,14,2613.159,-3055.652,240.5243,0,0,0,0,100,0),
(@PATH,15,2603.647,-3046.96,240.5242,0,0,0,0,100,0),
(@PATH,16,2613.084,-3036.567,240.5217,0,0,0,0,100,0),
(@PATH,17,2640.296,-3028.944,240.525,0,0,0,0,100,0),
(@PATH,18,2652.006,-3024.45,240.5253,0,0,0,0,100,0),
(@PATH,19,2664.795,-3009.59,240.5253,0,0,0,0,100,0),
(@PATH,20,2670.619,-2990.552,240.5244,0,0,0,0,100,0),
(@PATH,21,2679.347,-2964.029,240.5253,0,0,0,0,100,0),
(@PATH,22,2697.98,-2955.501,240.5241,0,0,0,0,100,0),
(@PATH,23,2719.132,-2962.616,240.5251,0,0,0,0,100,0),
(@PATH,24,2741.907,-2976.874,240.5253,0,0,0,0,100,0),
(@PATH,25,2760.453,-2981.653,240.5253,0,0,0,0,100,0);

DELETE FROM `creature_formations` WHERE `leaderGUID` IN (190461);
INSERT INTO `creature_formations` (`leaderGUID`,`memberGUID`,`dist`,`angle`,`groupAI`,`point_1`,`point_2`) VALUES
(190461,190461,0,0,2,0,0),
(190461,190414,3,360,2,0,0),
(190461,190413,3,40,2,0,0),
(190461,190443,3,320,2,0,0),
(190461,190442,3,260,2,0,0);

-- Pathing for Death Knight Captain Entry: 16145 'ark FORMAT' 
SET @NPC := 190458;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2584.613,`position_y`=-3100.685,`position_z`=240.5253 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2584.613,`position_y`=-3100.685,`position_z`=240.5253 WHERE `guid` IN (190412,190411,190439,190438);
DELETE FROM `creature_addon` WHERE `guid` IN (190412,190411,190439,190438);
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES
(190412,@PATH,0,0,1,0, ''), (190411,@PATH,0,0,1,0, ''), (190439,@PATH,0,0,1,0, ''), (190438,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2584.613,-3100.685,240.5253,0,0,0,0,100,0),
(@PATH,2,2601.56,-3083.452,240.5258,0,0,0,0,100,0),
(@PATH,3,2629.143,-3055.421,240.5237,0,0,0,0,100,0),
(@PATH,4,2650.178,-3034.592,240.526,0,0,0,0,100,0),
(@PATH,5,2667.962,-3017.14,240.5253,0,0,0,0,100,0),
(@PATH,6,2680.883,-3004.51,240.5252,0,0,0,0,100,0),
(@PATH,7,2699.352,-2986.865,240.5253,0,0,0,0,100,0),
(@PATH,8,2680.883,-3004.51,240.5252,0,0,0,0,100,0),
(@PATH,9,2667.962,-3017.14,240.5253,0,0,0,0,100,0),
(@PATH,10,2650.178,-3034.592,240.526,0,0,0,0,100,0),
(@PATH,11,2629.143,-3055.421,240.5237,0,0,0,0,100,0),
(@PATH,12,2601.56,-3083.452,240.5258,0,0,0,0,100,0),
(@PATH,13,2584.613,-3100.685,240.5253,0,0,0,0,100,0),
(@PATH,14,2570.169,-3114.794,240.5253,0,0,0,0,100,0),
(@PATH,15,2556.747,-3128.429,240.5253,0,0,0,0,100,0),
(@PATH,16,2570.169,-3114.794,240.5253,0,0,0,0,100,0);

DELETE FROM `creature_formations` WHERE `leaderGUID` IN (190458);
INSERT INTO `creature_formations` (`leaderGUID`,`memberGUID`,`dist`,`angle`,`groupAI`,`point_1`,`point_2`) VALUES
(190458,190458,0,0,2,0,0),
(190458,190412,3,360,2,7,15),
(190458,190411,3,40,2,7,15),
(190458,190439,3,320,2,7,15),
(190458,190438,3,260,2,7,15);

-- Pathing for Death Knight Captain Entry: 16145 'ark FORMAT' 
SET @NPC := 190454;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2871.322,`position_y`=-2985.748,`position_z`=267.593 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2871.322,`position_y`=-2985.748,`position_z`=267.593 WHERE `guid` IN (190402,190401,190433,190432);
DELETE FROM `creature_addon` WHERE `guid` IN (190402,190401,190433,190432);
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES
(190402,@PATH,0,0,1,0, ''), (190401,@PATH,0,0,1,0, ''), (190433,@PATH,0,0,1,0, ''), (190432,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2871.322,-2985.748,267.593,0,0,0,0,100,0),
(@PATH,2,2852.31,-2985.821,267.593,0,0,0,0,100,0),
(@PATH,3,2838.662,-2985.802,264.0277,0,0,0,0,100,0),
(@PATH,4,2807.427,-2985.919,248.8516,0,0,0,0,100,0),
(@PATH,5,2784.644,-2986.206,240.5265,0,0,0,0,100,0),
(@PATH,6,2760.957,-2986.261,240.5249,0,0,0,0,100,0),
(@PATH,7,2735.987,-2986.227,240.5253,0,0,0,0,100,0),
(@PATH,8,2716.594,-2986.268,240.5253,0,0,0,0,100,0),
(@PATH,9,2700.477,-2986.242,240.525,0,0,0,0,100,0),
(@PATH,10,2716.594,-2986.268,240.5253,0,0,0,0,100,0),
(@PATH,11,2735.987,-2986.227,240.5253,0,0,0,0,100,0),
(@PATH,12,2760.708,-2986.261,240.5253,0,0,0,0,100,0),
(@PATH,13,2784.644,-2986.206,240.5265,0,0,0,0,100,0),
(@PATH,14,2807.427,-2985.919,248.8516,0,0,0,0,100,0),
(@PATH,15,2838.662,-2985.802,264.0277,0,0,0,0,100,0),
(@PATH,16,2852.31,-2985.821,267.593,0,0,0,0,100,0),
(@PATH,17,2871.322,-2985.748,267.593,0,0,0,0,100,0),
(@PATH,18,2893.314,-2985.45,267.593,0,0,0,0,100,0),
(@PATH,19,2908.467,-2985.152,267.5937,0,0,0,0,100,0),
(@PATH,20,2893.314,-2985.45,267.593,0,0,0,0,100,0);

DELETE FROM `creature_formations` WHERE `leaderGUID` IN (190454);
INSERT INTO `creature_formations` (`leaderGUID`,`memberGUID`,`dist`,`angle`,`groupAI`,`point_1`,`point_2`) VALUES
(190454,190454,0,0,2,0,0),
(190454,190402,3,360,2,9,19),
(190454,190401,3,40,2,9,19),
(190454,190433,3,320,2,9,19),
(190454,190432,3,260,2,9,19);

DELETE FROM `creature_formations` WHERE `leaderGUID` IN (190463);
INSERT INTO `creature_formations` (`leaderGUID`,`memberGUID`,`dist`,`angle`,`groupAI`,`point_1`,`point_2`) VALUES
(190463,190463,0,0,2,0,0),
(190463,190418,3,360,2,0,0),
(190463,190417,3,40,2,0,0),
(190463,190447,3,320,2,0,0),
(190463,190446,3,260,2,0,0);
 
DELETE FROM `creature_formations` WHERE `leaderGUID` IN (190458);
INSERT INTO `creature_formations` (`leaderGUID`,`memberGUID`,`dist`,`angle`,`groupAI`,`point_1`,`point_2`) VALUES
(190458,190458,0,0,2,0,0),
(190458,190412,3,360,2,0,0),
(190458,190411,3,40,2,0,0),
(190458,190439,3,320,2,0,0),
(190458,190438,3,260,2,0,0);
 
DELETE FROM `creature_formations` WHERE `leaderGUID` IN (190454);
INSERT INTO `creature_formations` (`leaderGUID`,`memberGUID`,`dist`,`angle`,`groupAI`,`point_1`,`point_2`) VALUES
(190454,190454,0,0,2,0,0),
(190454,190402,3,360,2,0,0),
(190454,190401,3,40,2,0,0),
(190454,190433,3,320,2,0,0),
(190454,190432,3,260,2,0,0);

UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `Entry` IN (29698, 26043);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (29698, 26043) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(29698,0,0,0,4,0,100,0,0,0,0,0,11,54487,0,0,0,0,0,2,0,0,0,0,0,0,0,'Drakuru Raptor - On aggro - Cast Jump Attack'),
(26043,0,0,0,1,0,100,0,2000,8000,8000,15000,11,46400,0,0,0,0,0,1,0,0,0,0,0,0,0,'Steam Burst - OOC - Cast Steam Weapon');

UPDATE `creature_equip_template` SET `itemEntry1`=21573, `itemEntry2`=143 WHERE `entry`=27160;
UPDATE `creature_template` SET `InhabitType`=4 WHERE `Entry`=27375;

DELETE FROM `creature_template_addon` WHERE `entry`= 27268;
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `bytes2`, `auras`) VALUES (27268,0,0,1,48553);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` IN (13) AND `SourceEntry`=48551;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`ScriptName`,`Comment`, `NegativeCondition`) VALUES
(13, 1, 48551, 0, 31, 3, 27375, 0, 0, '', 'Vengeful Stormhammer only on Risen Gryphon Rider Target', 0);

DELETE FROM `creature_formations` WHERE `leaderGUID` IN (190454);
INSERT INTO `creature_formations` (`leaderGUID`,`memberGUID`,`dist`,`angle`,`groupAI`,`point_1`,`point_2`) VALUES
(190454,190454,0,0,2,0,0),
(190454,190402,3,360,2,9,19),
(190454,190401,3,40,2,9,19),
(190454,190433,3,320,2,9,19),
(190454,190432,3,260,2,9,19);

DELETE FROM `creature_formations` WHERE `leaderGUID` IN (190458);
INSERT INTO `creature_formations` (`leaderGUID`,`memberGUID`,`dist`,`angle`,`groupAI`,`point_1`,`point_2`) VALUES
(190458,190458,0,0,2,0,0),
(190458,190412,3,360,2,7,15),
(190458,190411,3,40,2,7,15),
(190458,190439,3,320,2,7,15),
(190458,190438,3,260,2,7,15);

DELETE FROM `creature_formations` WHERE `leaderGUID` IN (190463);
INSERT INTO `creature_formations` (`leaderGUID`,`memberGUID`,`dist`,`angle`,`groupAI`,`point_1`,`point_2`) VALUES
(190463,190463,0,0,2,0,0),
(190463,190418,3,360,2,8,17),
(190463,190417,3,40,2,8,17),
(190463,190447,3,320,2,8,17),
(190463,190446,3,260,2,8,17);

SET @LAMENTER := 39048;
UPDATE `creature_template` SET `AIName`='SmartAI', `InhabitType`=4 WHERE `entry`=@LAMENTER;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@LAMENTER AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@LAMENTER*100 AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(@LAMENTER, 0, 0, 0, 54, 0, 100, 0, 0, 0, 0, 0, 80, @LAMENTER*100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sylvanas'' Lamenter - On Summoned - Action list'),
(@LAMENTER*100, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 37090, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sylvanas'' Lamenter - Action list - Cast Lament of the Highborne: Highborne Aura'),
(@LAMENTER*100, 9, 1, 0, 0, 0, 100,0,0,0,0,0,59,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Sylvanas'' Lamenter - Action list - Set run off"),
(@LAMENTER*100, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 114, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sylvanas'' Lamenter - Action list - Rise up'),
(@LAMENTER*100, 9, 3, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 4, 15095, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sylvanas'' Lamenter - Action list - Play Sound Lament of the Highborne');

UPDATE `creature_template` SET `unit_flags`=33555200 WHERE `entry`=28253;

SET @ENTRY := 30736;
UPDATE `creature_template` SET `AIName`="SmartAI", `unit_flags`=33555200, `InhabitType`=4 WHERE `entry` IN (@ENTRY);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@ENTRY) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,54,0,100,0,0,0,0,0,75,57806,0,0,0,0,0,1,0,0,0,0,0,0,0,"Released Soul - Just summoned - Add aura"),
(@ENTRY,0,1,2,61,0,100,0,0,0,0,0,4,37,0,0,0,0,0,1,0,0,0,0,0,0,0,"Released Soul - Just summoned - Play sound"),
(@ENTRY,0,2,3,61,0,100,0,0,0,0,0,59,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Released Soul - Just summoned - Set run off"),
(@ENTRY,0,3,0,61,0,100,0,0,0,0,0,114,40,0,0,0,0,0,1,0,0,0,0,0,0,0,"Released Soul - Just summoned - Rise up"),
(@ENTRY,0,4,0,54,0,100,0,0,0,0,0,41,10000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Released Soul - Just summoned - Despawn");

UPDATE `creature_template` SET `unit_flags`=33554432 WHERE `entry` IN (30850,30852,30841);

UPDATE `creature_template` SET `unit_flags`=131076, `flags_extra`=66 WHERE `entry`=25534;

UPDATE `creature_template` SET `unit_flags`=32768 WHERE `entry`=26271;
UPDATE `creature` SET `unit_flags`=537166592 WHERE `guid` IN (230079, 230078, 230077, 230076, 230075, 230074);

DELETE FROM `creature_addon` WHERE `guid` IN (230079, 230078, 230077, 230076, 230075, 230074);
INSERT INTO `creature_addon` (`guid`, `bytes2`, `auras`) VALUES 
(230079, 1, "29266"),
(230078, 1, "29266"),
(230077, 1, "29266"),
(230076, 1, "29266"),
(230075, 1, "29266"),
(230074, 1, "29266");

UPDATE `creature_template` SET `unit_flags`=512 WHERE `entry`=31402;

UPDATE `creature_template` SET `unit_flags`=33536 WHERE `entry`=30501;

DELETE FROM `creature` WHERE `guid`=214800 AND `id`=28414;

DELETE FROM `creature_template_addon` WHERE `entry` IN (28413);
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES 
(28413, 0, "54450");

UPDATE `creature_template` SET `flags_extra`=2 WHERE `entry` IN (28413);

-- Eversong Ranger
DELETE FROM `smart_scripts` WHERE `entryorguid`=15938 AND `source_type`=0 AND `id`<14;
UPDATE `smart_scripts` SET `id`= `id`-12 WHERE `entryorguid`=15938 AND `source_type`=0 AND `id`>13;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(15938,0,0,0,0,0,100,0,0,0,2200,3800,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,"Eversong Ranger - In Combat CMC - Cast 'Shoot'"),
(15938,0,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Eversong Ranger - Between 0-15% Health - Flee For Assist (No Repeat)");

-- Iceskin Sentry
UPDATE `creature` SET `movementtype`=0, `spawndist`=0 WHERE `id`=31012;
UPDATE `creature_addon` SET `bytes1`=50331657 WHERE `guid`=214101;
UPDATE `creature_template` SET `unit_flags`=2147778560 WHERE `entry`=31012;
UPDATE `creature_addon` SET `auras`="58269" WHERE `guid` between 214101 AND 214111;
UPDATE `creature_addon` SET `auras`="58269" WHERE `guid` between 214113 AND 214116;

UPDATE `creature` SET `movementtype`=0, `spawndist`=0 WHERE `id`=32264;
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=32264;
DELETE FROM `smart_scripts` WHERE `entryorguid`=32262 AND `source_type`=0 AND `id`=3;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(32262, 0, 3, 0, 1, 0, 100, 1, 0, 0, 0, 0, 11, 60309, 0, 0, 0, 0, 0, 19, 32264, 30, 0, 0, 0, 0, 0, 'Shadow Channeler - OOC - Cast Channel Souls');

UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=27075;
DELETE FROM `smart_scripts` WHERE `entryorguid`IN (27075) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(27075,0,0,1,8,0,100,0,47935,0,0,0,33,27075,0,0,0,0,0,7,0,0,0,0,0,0,0,"Dun Argol Power Core - On Spellhit  - Credit Kill"),
(27075,0,1,0,61,0,100,0,0,0,0,0,51,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Dun Argol Power Core - On Spellhit  - Kill Self");

DELETE FROM `creature_template_addon` WHERE `entry`=27632;
INSERT INTO `creature_template_addon` (`entry`,`bytes1`,`bytes2`,`auras`) VALUES
(27632,0,0,"49135");

UPDATE `creature_template` SET `flags_extra`=2 WHERE `entry`=29639;
UPDATE `creature` SET `MovementType`=0, `spawndist`=0 WHERE `guid`=221871;
UPDATE `creature_addon` SET `auras`=29266 WHERE `guid`=221871;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=29500;
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry` IN (29558, 32520);
UPDATE `creature` SET `MovementType`=0, `spawndist`=0 WHERE `guid`=221795;
UPDATE `creature_addon` SET `auras`=29266 WHERE `guid`=221795;

UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `Entry` IN (29351, 29358);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (29351, 29358) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(29351,0,0,0,0,0,100,0,2000,5000,7000,9000,11,38621,0,0,0,0,0,2,0,0,0,0,0,0,0,'Niffelem Frost Giant - IC - Cast Debilitating Strike'),
(29358,0,0,0,0,0,100,0,2000,5000,7000,9000,11,61572,0,0,0,0,0,2,0,0,0,0,0,0,0,'Frostworg - IC - Cast Frostbite'),
(29358,0,1,0,0,0,100,0,2000,6000,6000,9000,11,50075,0,0,0,0,0,2,0,0,0,0,0,0,0,'Frostworg - IC - Cast Maim Flesh');

UPDATE `creature_template` SET `npcflag`=16777216 WHERE `entry` IN (29351, 29358);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` IN (29358, 29351);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(29358,46598,0,0),
(29351,46598,0,0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` IN (29358, 29351);
INSERT INTO `vehicle_template_accessory` (`entry`,`accessory_entry`,`seat_id`,`minion`,`description`,`summontype`) VALUES
(29351,29558,0,1, 'Niffelem Frost Giant', 8),
(29351,29558,1,1, 'Niffelem Frost Giant', 8),
(29351,29558,2,1, 'Niffelem Frost Giant', 8),
(29351,29558,3,1, 'Niffelem Frost Giant', 8),
(29358,29558,0,1, 'Frostworg', 8),
(29358,29558,1,1, 'Frostworg', 8);

UPDATE `waypoint_data` SET `position_z` = 45.5099 WHERE `id` = 845820 AND `point` = 5;

-- Pathing for Azuremyst Peacekeeper Entry: 18038 'ark FORMAT' 
SET @NPC := 174948;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-4171.392,`position_y`=-12464.35,`position_z`=44.40071 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,4097,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-4171.392,-12464.35,44.40071,0,0,0,0,100,0),
(@PATH,2,-4172.635,-12441.57,43.73568,0,0,0,0,100,0),
(@PATH,3,-4183.271,-12464.69,44.86507,0,0,0,0,100,0),
(@PATH,4,-4191.694,-12478.19,45.88747,0,0,0,0,100,0),
(@PATH,5,-4208.529,-12485.6,44.76502,0,0,0,0,100,0),
(@PATH,6,-4206.412,-12507.59,45.07471,0,0,0,0,100,0),
(@PATH,7,-4195.887,-12522.06,45.18763,0,0,0,0,100,0),
(@PATH,8,-4175.124,-12527.87,44.7594,0,0,0,0,100,0),
(@PATH,9,-4159.117,-12516.98,44.69878,0,0,0,0,100,0),
(@PATH,10,-4153.929,-12500.22,44.07134,0,0,0,0,100,0),
(@PATH,11,-4155.868,-12489.98,44.48027,0,0,0,0,100,0);

-- Pathing for Azuremyst Peacekeeper Entry: 18038 'ark FORMAT' 
SET @NPC := 174946;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-4200.606,`position_y`=-12494.63,`position_z`=44.62513 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,4097,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-4200.606,-12494.63,44.62513,0,0,0,0,100,0),
(@PATH,2,-4177.409,-12486.11,44.26247,0,0,0,0,100,0),
(@PATH,3,-4164.705,-12500.84,44.40313,0,0,0,0,100,0),
(@PATH,4,-4134.247,-12503.81,43.62505,0,0,0,0,100,0),
(@PATH,5,-4100.406,-12490.22,40.99446,0,0,0,0,100,0),
(@PATH,6,-4067.271,-12473.87,35.7093,0,0,0,0,100,0),
(@PATH,7,-4034.042,-12460.46,31.01041,0,0,0,0,100,0),
(@PATH,8,-4000.527,-12450.34,25.04846,0,0,0,0,100,0),
(@PATH,9,-3967.376,-12442.74,18.43705,0,0,0,0,100,0),
(@PATH,10,-3951.83,-12430.16,14.62435,0,0,0,0,100,0),
(@PATH,11,-3923.009,-12427.82,9.259804,0,0,0,0,100,0),
(@PATH,12,-3890.977,-12420.35,3.110225,0,0,0,0,100,0),
(@PATH,13,-3845.61,-12400.15,-0.5076148,0,0,0,0,100,0),
(@PATH,14,-3799.788,-12396.9,-1.57003,0,0,0,0,100,0),
(@PATH,15,-3767.789,-12389.86,-1.612022,0,0,0,0,100,0),
(@PATH,16,-3733.884,-12386.01,-2.563792,0,0,0,0,100,0),
(@PATH,17,-3699.675,-12379.4,-3.253355,0,0,0,0,100,0),
(@PATH,18,-3676.898,-12366.13,-3.005086,0,0,0,0,100,0),
(@PATH,19,-3634.198,-12353.74,-1.517532,0,0,0,0,100,0),
(@PATH,20,-3600.196,-12362.62,0.9561348,0,0,0,0,100,0),
(@PATH,21,-3566.171,-12360.33,3.723941,0,0,0,0,100,0),
(@PATH,22,-3533.756,-12360.66,6.88605,0,0,0,0,100,0),
(@PATH,23,-3500.217,-12359.56,9.171444,0,0,0,0,100,0),
(@PATH,24,-3533.756,-12360.66,6.88605,0,0,0,0,100,0),
(@PATH,25,-3566.171,-12360.33,3.723941,0,0,0,0,100,0),
(@PATH,26,-3600.196,-12362.62,0.9561348,0,0,0,0,100,0),
(@PATH,27,-3634.033,-12353.8,-1.465286,0,0,0,0,100,0),
(@PATH,28,-3676.898,-12366.13,-3.005086,0,0,0,0,100,0),
(@PATH,29,-3699.675,-12379.4,-3.253355,0,0,0,0,100,0),
(@PATH,30,-3733.884,-12386.01,-2.563792,0,0,0,0,100,0),
(@PATH,31,-3767.789,-12389.86,-1.612022,0,0,0,0,100,0),
(@PATH,32,-3799.788,-12396.9,-1.57003,0,0,0,0,100,0),
(@PATH,33,-3845.61,-12400.15,-0.5076148,0,0,0,0,100,0),
(@PATH,34,-3890.977,-12420.35,3.110225,0,0,0,0,100,0),
(@PATH,35,-3923.009,-12427.82,9.259804,0,0,0,0,100,0),
(@PATH,36,-3951.679,-12430.06,14.65267,0,0,0,0,100,0),
(@PATH,37,-3967.376,-12442.74,18.43705,0,0,0,0,100,0),
(@PATH,38,-4000.527,-12450.34,25.04846,0,0,0,0,100,0),
(@PATH,39,-4034.023,-12460.46,30.9877,0,0,0,0,100,0),
(@PATH,40,-4067.271,-12473.87,35.7093,0,0,0,0,100,0),
(@PATH,41,-4100.406,-12490.22,40.99446,0,0,0,0,100,0),
(@PATH,42,-4134.247,-12503.81,43.62505,0,0,0,0,100,0),
(@PATH,43,-4164.705,-12500.84,44.40313,0,0,0,0,100,0),
(@PATH,44,-4177.409,-12486.11,44.26247,0,0,0,0,100,0);

-- Pathing for Azuremyst Peacekeeper Entry: 18038 'ark FORMAT' 
SET @NPC := 174947;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-4134.126,`position_y`=-12506.01,`position_z`=43.88897 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,4097,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-4134.126,-12506.01,43.88897,0,0,0,0,100,0),
(@PATH,2,-4167.211,-12511.93,44.3844,0,0,0,0,100,0),
(@PATH,3,-4197.208,-12508.09,44.48694,0,0,0,0,100,0),
(@PATH,4,-4233.25,-12487.22,41.86756,0,0,0,0,100,0),
(@PATH,5,-4267.729,-12476.33,29.47266,0,0,0,0,100,0),
(@PATH,6,-4289.251,-12471.83,24.20484,0,0,0,0,100,0),
(@PATH,7,-4319.148,-12478.5,18.93451,0,0,0,0,100,0),
(@PATH,8,-4333.606,-12469.67,15.57558,0,0,0,0,100,0),
(@PATH,9,-4364.828,-12471.54,10.27822,0,0,0,0,100,0),
(@PATH,10,-4399.945,-12455.7,5.627916,0,0,0,0,100,0),
(@PATH,11,-4432.767,-12443.6,2.278673,0,0,0,0,100,0),
(@PATH,12,-4467.428,-12430.61,2.763325,0,0,0,0,100,0),
(@PATH,13,-4499.994,-12415.54,4.523335,0,0,0,0,100,0),
(@PATH,14,-4533.506,-12416.08,7.310507,0,0,0,0,100,0),
(@PATH,15,-4566.756,-12417.92,9.204178,0,0,0,0,100,0),
(@PATH,16,-4533.506,-12416.08,7.310507,0,0,0,0,100,0),
(@PATH,17,-4499.994,-12415.54,4.523335,0,0,0,0,100,0),
(@PATH,18,-4467.428,-12430.61,2.763325,0,0,0,0,100,0),
(@PATH,19,-4432.767,-12443.6,2.278673,0,0,0,0,100,0),
(@PATH,20,-4399.945,-12455.7,5.627916,0,0,0,0,100,0),
(@PATH,21,-4364.828,-12471.54,10.27822,0,0,0,0,100,0),
(@PATH,22,-4333.889,-12469.66,15.56435,0,0,0,0,100,0),
(@PATH,23,-4319.148,-12478.5,18.93451,0,0,0,0,100,0),
(@PATH,24,-4289.251,-12471.83,24.20484,0,0,0,0,100,0),
(@PATH,25,-4267.729,-12476.33,29.47266,0,0,0,0,100,0),
(@PATH,26,-4233.25,-12487.22,41.86756,0,0,0,0,100,0),
(@PATH,27,-4197.208,-12508.09,44.48694,0,0,0,0,100,0),
(@PATH,28,-4167.211,-12511.93,44.3844,0,0,0,0,100,0);

DELETE FROM `creature` WHERE `guid`=174950;
DELETE FROM `creature_addon` WHERE `guid`=174950;

