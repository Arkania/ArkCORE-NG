
UPDATE `creature_template` SET `npcflag`=0 WHERE `entry` IN (37200); 

UPDATE `creature_template` SET `npcflag`=1, `gossip_menu_id`=10953 WHERE `entry`=37187;

DELETE FROM `gossip_menu` WHERE `entry` IN (10953, 10952) AND `text_id` IN (15217, 15218);
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES
(10953, 15217),
(10952, 15218);

DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (10953, 10952);
INSERT INTO `gossip_menu_option` (`menu_id`,`id`,`option_icon`,`option_text`, `OptionBroadcastTextID`, `option_id`,`npc_option_npcflag`,`action_menu_id`) VALUES
(10953,0,0,"We are ready to go, High Overlord. The Lich King must fall!",37631,1,1,10952),
(10952,0,0,"Lok'tar ogar! We are ready! Onward, brother orc!",37633,1,1,0);

DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (10933, 10934);
INSERT INTO `gossip_menu_option` (`menu_id`,`id`,`option_icon`,`option_text`, `OptionBroadcastTextID`, `option_id`,`npc_option_npcflag`,`action_menu_id`) VALUES
(10933,0,0,"We're ready, Muradin",37446,1,1,10934),
(10934,0,0,"We're sure. Let's go!",37448,1,1,0);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` IN (14,15) AND `SourceGroup` IN (10933, 10953);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10933, 0, 0, 0, 13, 1, 2, 4, 2, 1, 0, 0, '', 'Show gossip option only if Deathbringer Saurfang is not done'),
(15, 10953, 0, 0, 0, 13, 1, 2, 4, 2, 1, 0, 0, '', 'Show gossip option only if Deathbringer Saurfang is not done');

DELETE FROM `spelldifficulty_dbc` WHERE id IN (28308,41926);
INSERT INTO `spelldifficulty_dbc` (`id`,`spellid0`,`spellid1`) VALUES (28308,28308,59192);

DELETE FROM `creature` WHERE `id`=22023;

DELETE FROM `smart_scripts` WHERE `entryorguid`=3518 AND `source_type`=0;
UPDATE `creature_template` SET `AIName`='' WHERE `entry`=3518;
UPDATE `waypoint_scripts` SET `dataint`=1102 WHERE `id`=273 ;

delete from waypoint_data where id in (797230, 2550700) and point=22;
insert into waypoint_data values
(2550700, 22, -8811.88, 634.469, 94.2293, 0, 0, 0, 273, 100, 0);

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = 29320;
INSERT INTO `spell_linked_spell` VALUES (29320, 29321, 0, 'Charge-Fear');

-- Pathing for Death Knight Cavalier Entry: 16163 'Ark FORMAT' 
SET @NPC := 190349;  -- guid by arkdb
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2926.023,`position_y`=-3200.403,`position_z`=273.3712 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,25278,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2926.023,-3200.403,273.3712,0,0,0,0,100,0),
(@PATH,2,2931.457,-3188.328,273.3712,0,0,0,0,100,0),
(@PATH,3,2925.778,-3167.298,273.787,0,0,0,0,100,0),
(@PATH,4,2907.542,-3166.655,273.787,0,0,0,0,100,0),
(@PATH,5,2873.219,-3165.419,273.787,0,0,0,0,100,0),
(@PATH,6,2861.632,-3165.088,273.787,0,0,0,0,100,0),
(@PATH,7,2860.526,-3185.717,273.787,0,0,0,0,100,0),
(@PATH,8,2860.435,-3203.401,273.787,0,0,0,0,100,0),
(@PATH,9,2875.204,-3203.906,273.4088,0,0,0,0,100,0),
(@PATH,10,2892.834,-3204.38,273.3965,0,0,0,0,100,0),
(@PATH,11,2911.993,-3204.611,273.3846,0,0,0,0,100,0);

-- Pathing for Toxic Tunnel Entry: 16400 'Ark FORMAT' 
SET @NPC := 190472;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=3223.018,`position_y`=-3218.725,`position_z`=316.3705 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '28370');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,3223.018,-3218.725,316.3705,0,0,0,0,100,0),
(@PATH,2,3230.179,-3211.59,316.5933,0,0,0,0,100,0);

-- Pathing for Toxic Tunnel Entry: 16400 'Ark FORMAT' 
SET @NPC := 190471;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=3208.167,`position_y`=-3234.595,`position_z`=315.4565 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '28370');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,3208.167,-3234.595,315.4565,0,0,0,0,100,0),
(@PATH,2,3200.392,-3242.829,315.141,0,0,0,0,100,0);

-- Pathing for Toxic Tunnel Entry: 16400 'Ark FORMAT' 
SET @NPC := 190470;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=3178.613,`position_y`=-3263.671,`position_z`=316.4281 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '28370');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,3178.613,-3263.671,316.4281,0,0,0,0,100,0),
(@PATH,2,3174.119,-3267.95,316.7845,0,0,0,0,100,0);

-- Pathing for Toxic Tunnel Entry: 16400 'Ark FORMAT' 
SET @NPC := 190469;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=3217.316,`position_y`=-3224.753,`position_z`=316.0583 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '28370');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,3217.316,-3224.753,316.0583,0,0,0,0,100,0),
(@PATH,2,3209.847,-3232.841,315.5579,0,0,0,0,100,0);

-- Pathing for Toxic Tunnel Entry: 16400 'Ark FORMAT' 
SET @NPC := 190468;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=3190.628,`position_y`=-3252.565,`position_z`=315.5675 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '28370');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,3190.628,-3252.565,315.5675,0,0,0,0,100,0),
(@PATH,2,3196.852,-3246.524,315.0298,0,0,0,0,100,0);

-- Pathing for Toxic Tunnel Entry: 16400 'Ark FORMAT' 
SET @NPC := 190467;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=3244.748,`position_y`=-3198.743,`position_z`=317.3646 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '28370');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,3244.748,-3198.743,317.3646,0,0,0,0,100,0),
(@PATH,2,3236.25,-3205.753,316.6993,0,0,0,0,100,0);

-- Pathing for Toxic Tunnel Entry: 16400 'Ark FORMAT' 
SET @NPC := 190466;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=3246.763,`position_y`=-3193.856,`position_z`=317.3302 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '28370');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,3246.763,-3193.856,317.3302,0,0,0,0,100,0),
(@PATH,2,3252.532,-3188.566,318.1087,0,0,0,0,100,0);


-- Pathing for Stitched Colossus Entry: 30071 'Ark FORMAT' 
SET @NPC := 190045;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=3454.427,`position_y`=-3187.954,`position_z`=294.6607 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,3454.427,-3187.954,294.6607,0,0,0,0,100,0),
(@PATH,2,3453.837,-3215.978,284.005,0,0,0,0,100,0),
(@PATH,3,3453.848,-3237.722,272.597,0,0,0,0,100,0),
(@PATH,4,3453.705,-3262.583,267.5943,0,0,0,0,100,0),
(@PATH,5,3453.507,-3285.881,267.5923,0,0,0,0,100,0),
(@PATH,6,3450.008,-3299.009,267.593,0,0,0,0,100,0),
(@PATH,7,3434.539,-3314.597,267.592,0,0,0,0,100,0),
(@PATH,8,3423.135,-3338.302,267.593,0,0,0,0,100,0),
(@PATH,9,3430.531,-3358.816,267.592,0,0,0,0,100,0),
(@PATH,10,3450.598,-3369.066,267.5927,0,0,0,0,100,0),
(@PATH,11,3472.296,-3362.288,267.5991,0,0,0,0,100,0),
(@PATH,12,3483.6,-3341.974,267.5938,0,0,0,0,100,0),
(@PATH,13,3477.419,-3326.692,267.5933,0,0,0,0,100,0),
(@PATH,14,3466.747,-3312.542,267.5925,0,0,0,0,100,0),
(@PATH,15,3455.716,-3299.394,267.5929,0,0,0,0,100,0),
(@PATH,16,3453.988,-3285.853,267.5922,0,0,0,0,100,0),
(@PATH,17,3454.239,-3262.38,267.5943,0,0,0,0,100,0),
(@PATH,18,3454.453,-3237.651,272.6341,0,0,0,0,100,0),
(@PATH,19,3454.135,-3215.837,284.079,0,0,0,0,100,0);

-- Pathing for Stitched Colossus Entry: 30071 'Ark FORMAT' 
SET @NPC := 190046;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=3331.301,`position_y`=-3008.488,`position_z`=294.6606 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,3331.301,-3008.488,294.6606,0,0,0,0,100,0),
(@PATH,2,3352.705,-3027.659,294.6606,0,0,0,0,100,0),
(@PATH,3,3378.292,-3052.875,294.6657,0,0,0,0,100,0),
(@PATH,4,3400.806,-3075.215,294.6628,0,0,0,0,100,0),
(@PATH,5,3420.535,-3095.16,294.6607,0,0,0,0,100,0),
(@PATH,6,3423.608,-3104.254,294.6607,0,0,0,0,100,0),
(@PATH,7,3424.381,-3122.999,294.6599,0,0,0,0,100,0),
(@PATH,8,3428.679,-3145.677,294.659,0,0,0,0,100,0),
(@PATH,9,3444.718,-3157.384,294.6608,0,0,0,0,100,0),
(@PATH,10,3466.77,-3155.3,294.6603,0,0,0,0,100,0),
(@PATH,11,3481.494,-3139.173,294.6597,0,0,0,0,100,0),
(@PATH,12,3480.309,-3114.887,294.6596,0,0,0,0,100,0),
(@PATH,13,3467.193,-3102.655,294.6595,0,0,0,0,100,0),
(@PATH,14,3448.526,-3099.575,294.6612,0,0,0,0,100,0),
(@PATH,15,3428.409,-3099.175,294.6607,0,0,0,0,100,0),
(@PATH,16,3420.901,-3094.735,294.6607,0,0,0,0,100,0),
(@PATH,17,3401.064,-3074.813,294.6629,0,0,0,0,100,0),
(@PATH,18,3378.616,-3052.372,294.6658,0,0,0,0,100,0),
(@PATH,19,3352.98,-3027.292,294.6606,0,0,0,0,100,0),
(@PATH,20,3331.301,-3008.488,294.6606,0,0,0,0,100,0),
(@PATH,21,3311.187,-2990.615,294.6598,0,0,0,0,100,0),
(@PATH,22,3311.187,-2990.615,294.6598,2.505866,0,0,0,100,0),
(@PATH,23,3311.187,-2990.615,294.6598,2.251878,0,0,0,100,0),
(@PATH,24,3311.187,-2990.615,294.6598,3.254467,0,0,0,100,0),
(@PATH,25,3311.187,-2990.615,294.6598,5.113917,0,0,0,100,0);

-- Pathing for Stitched Colossus Entry: 30071 'Ark FORMAT' 
SET @NPC := 190047;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=3425.885,`position_y`=-3100.784,`position_z`=294.6607 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,3425.885,-3100.784,294.6607,0,0,0,0,100,0),
(@PATH,2,3400.279,-3075.093,294.6628,0,0,0,0,100,0),
(@PATH,3,3373.177,-3047.739,294.6664,0,0,0,0,100,0),
(@PATH,4,3344.838,-3019.543,294.6606,0,0,0,0,100,0),
(@PATH,5,3341.914,-3012.742,294.6606,0,0,0,0,100,0),
(@PATH,6,3339.663,-2995.398,294.6601,0,0,0,0,100,0),
(@PATH,7,3337.08,-2977.52,294.6604,0,0,0,0,100,0),
(@PATH,8,3323.939,-2963.499,294.6603,0,0,0,0,100,0),
(@PATH,9,3299.76,-2962.284,294.6606,0,0,0,0,100,0),
(@PATH,10,3286.439,-2972.35,294.6593,0,0,0,0,100,0),
(@PATH,11,3280.707,-2995.567,294.6606,0,0,0,0,100,0),
(@PATH,12,3288.473,-3011.645,294.6597,0,0,0,0,100,0),
(@PATH,13,3307.809,-3020.176,294.659,0,0,0,0,100,0),
(@PATH,14,3325.226,-3018.351,294.6606,0,0,0,0,100,0),
(@PATH,15,3338.513,-3016.632,294.6606,0,0,0,0,100,0),
(@PATH,16,3344.342,-3020.255,294.6606,0,0,0,0,100,0),
(@PATH,17,3372.666,-3048.441,294.6662,0,0,0,0,100,0),
(@PATH,18,3399.818,-3075.62,294.6627,0,0,0,0,100,0),
(@PATH,19,3425.406,-3101.135,294.6607,0,0,0,0,100,0),
(@PATH,20,3451.888,-3127.903,294.6607,0,0,0,0,100,0),
(@PATH,21,3451.888,-3127.903,294.6607,1.541391,0,0,0,100,0),
(@PATH,22,3456.634,-3133.219,294.6606,0,0,0,0,100,0),
(@PATH,23,3455.112,-3131.514,294.6606,6.06443,0,0,0,100,0),
(@PATH,24,3455.112,-3131.514,294.6606,4.858006,0,0,0,100,0),
(@PATH,25,3455.112,-3131.514,294.6606,2.345938,0,0,0,100,0);

-- Pathing for Stitched Colossus Entry: 30071 'Ark FORMAT' 
SET @NPC := 190049;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=3250.639,`position_y`=-2986.463,`position_z`=294.6606 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,3250.639,-2986.463,294.6606,0,0,0,0,100,0),
(@PATH,2,3218.217,-2985.765,281.2667,0,0,0,0,100,0),
(@PATH,3,3198.772,-2985.637,271.0636,0,0,0,0,100,0),
(@PATH,4,3178.061,-2985.433,267.5943,0,0,0,0,100,0),
(@PATH,5,3159.365,-2985.343,267.5929,0,0,0,0,100,0),
(@PATH,6,3139.7,-2981.853,267.5929,0,0,0,0,100,0),
(@PATH,7,3126.553,-2971.708,267.5919,0,0,0,0,100,0),
(@PATH,8,3114.558,-2959.215,267.5926,0,0,0,0,100,0),
(@PATH,9,3095.302,-2956.31,267.5921,0,0,0,0,100,0),
(@PATH,10,3078.464,-2964.795,267.5918,0,0,0,0,100,0),
(@PATH,11,3070.598,-2982.696,267.5929,0,0,0,0,100,0),
(@PATH,12,3076.846,-3004.052,267.592,0,0,0,0,100,0),
(@PATH,13,3096.726,-3015.381,267.5934,0,0,0,0,100,0),
(@PATH,14,3115.124,-3011.505,267.5921,0,0,0,0,100,0),
(@PATH,15,3127.605,-2998.091,267.5924,0,0,0,0,100,0),
(@PATH,16,3139.447,-2989.035,267.5929,0,0,0,0,100,0),
(@PATH,17,3159.26,-2985.907,267.5929,0,0,0,0,100,0),
(@PATH,18,3178.106,-2985.838,267.5943,0,0,0,0,100,0),
(@PATH,19,3198.909,-2986.179,271.1352,0,0,0,0,100,0),
(@PATH,20,3218.02,-2986.236,281.1633,0,0,0,0,100,0);

-- Pathing for Shade of Naxxramas Entry: 16164 'Ark FORMAT' 
SET @NPC := 190348;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=2915.294,`position_y`=-3343.234,`position_z`=298.1457 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,2915.294,-3343.234,298.1457,0,0,0,0,100,0),
(@PATH,2,2898.639,-3327.008,298.1457,0,0,0,0,100,0),
(@PATH,3,2915.294,-3343.234,298.1457,0,0,0,0,100,0),
(@PATH,4,2898.639,-3327.008,298.1457,0,0,0,0,100,0),
(@PATH,5,2915.294,-3343.234,298.1457,0,0,0,0,100,0),
(@PATH,6,2898.639,-3327.008,298.1457,0,0,0,0,100,0);

-- Sludge Belcher SAI On Reset - Cast Disease Cloud was set to OOC
UPDATE `smart_scripts` SET `event_type`=25 WHERE `entryorguid`=16029 AND `source_type`=0 AND `id`=0;

DELETE FROM `creature_text` WHERE `entry` in(23392,23257,23334,23208,23335,22982);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `comment`) VALUES 
(23392, 0, 0, '$N is an officer and a $G gentleman : gentlewoman;.', 12, 0, 100, 0, 0, 0, 21940, 'Skyguard Stable Master <Stable Master>'),
(23257, 0, 0, 'Look who''s here.  It''s $N, our top gun.', 12, 0, 100, 0, 0, 0, 21885, 'Skyguard Windcharger'),
(23257, 0, 1, '$N, terror of the skies, how are you doing?', 12, 0, 100, 0, 0, 0, 21893, 'Skyguard Windcharger'),
(23257, 0, 2, 'A-TEN-HUT, officer $N on the deck!', 12, 0, 100, 0, 0, 0, 21891, 'Skyguard Windcharger'),
(23257, 0, 3, '$G Mister : Lady; $N, what an unexpected pleasure, $G sir : ma''am;.', 12, 0, 100, 0, 0, 0, 21890, 'Skyguard Windcharger'),
(23257, 0, 4, 'Heh, the skies aren''t so friendly with $N flying them!', 12, 0, 100, 0, 0, 0, 21895, 'Skyguard Windcharger'),
(23257, 0, 5, '$N, you and I should race sometime.', 12, 0, 100, 0, 0, 0, 21937, 'Skyguard Windcharger'),
(23257, 0, 6, '$N, how''s your mount holding up?  Pretty rough up there these days?', 12, 0, 100, 0, 0, 0, 21897, 'Skyguard Windcharger'),
(23334, 0, 0, 'Maybe one day $N will teach us a few of $G his : her; tricks?', 12, 0, 100, 0, 0, 0, 21942, 'Sky Commander Keller'),
(23208, 0, 0, 'Maybe one day $N will teach us a few of $G his : her; tricks?', 12, 0, 100, 0, 0, 0, 21942, 'Skyguard Pyrotechnician'),
(23335, 0, 0, 'You''re a peach!  I''ll make sure that the ray is properly cared for.', 12, 0, 100, 0, 0, 0, 21371, 'Skyguard Khatie'),
(23335, 0, 1, 'Wow!  Thanks for bringing it all the way back here.  You didn''t have to do that.', 12, 0, 100, 0, 0, 0, 21370, 'Skyguard Khatie'),
(22982, 0, 0, '$N, do you feel the need -- the need for speed?', 12, 0, 100, 0, 0, 0, 21886, 'Skyguard Navigator'),
(22982, 0, 1, '$N, how''s your mount holding up?  Pretty rough up there these days?', 12, 0, 100, 0, 0, 0, 21897, 'Skyguard Navigator'),
(22982, 0, 3, 'Heh, the skies aren''t so friendly with $N flying them!', 12, 0, 100, 0, 0, 0, 21895, 'Skyguard Navigator'),
(22982, 0, 4, '$N, terror of the skies, how are you doing?', 12, 0, 100, 0, 0, 0, 21893, 'Skyguard Navigator');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN(23392,23257,23334,23208,23335,22982) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(23392, 0, 0, 0, 10, 0, 100, 0, 1, 10, 300000, 300000, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Skyguard Stable Master <Stable Master> - OOC LOS - Say'),
(23257, 0, 0, 0, 10, 0, 100, 0, 1, 10, 150000, 150000, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Skyguard Stable Master - OOC LOS - Say'),
(23334, 0, 0, 0, 10, 0, 100, 0, 1, 10, 300000, 300000, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Sky Commander Keller - OOC LOS - Say'),
(23208, 0, 0, 0, 10, 0, 100, 0, 1, 10, 300000, 300000, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Skyguard Pyrotechnician - OOC LOS - Say'),
(23335, 0, 0, 0, 10, 0, 100, 0, 1, 10, 300000, 300000, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Skyguard Khatie - OOC LOS - Say'),
(22982, 0, 0, 0, 10, 0, 100, 0, 1, 10, 150000, 150000, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Skyguard Navigator - OOC LOS - Say');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=22 AND `SourceEntry` IN(23392,23257,23334,23208,23335,22982);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(22, 1, 23392, 0, 0, 5, 0, 1031, 128, 0, 0, 0, 0, '', 'requires shatari skyguard exhalted'),
(22, 1, 23257, 0, 0, 5, 0, 1031, 128, 0, 0, 0, 0, '', 'requires shatari skyguard exhalted'),
(22, 1, 23334, 0, 0, 5, 0, 1031, 128, 0, 0, 0, 0, '', 'requires shatari skyguard exhalted'),
(22, 1, 23208, 0, 0, 5, 0, 1031, 128, 0, 0, 0, 0, '', 'requires shatari skyguard exhalted'),
(22, 1, 23335, 0, 0, 28, 0, 11023, 0, 0, 0, 0, 0, '', 'requires Bomb Them Again complete in quest log'),
(22, 1, 23335, 0, 1, 28, 0, 11010, 0, 0, 0, 0, 0, '', 'requires Bombing run complete in quest log'),
(22, 1, 23335, 0, 2, 28, 0, 11102, 0, 0, 0, 0, 0, '', 'requires Bombing run complete in quest log'),
(22, 1, 22982, 0, 0, 5, 0, 1031, 128, 0, 0, 0, 0, '', 'requires shatari skyguard exhalted');

-- Update formation points
UPDATE `creature_formations` SET `point_1`=1, `point_2`=19 WHERE `leaderGUID`=236681 AND `memberGUID`=236668; -- arkdb
UPDATE `creature_formations` SET `point_1`=4, `point_2`=8 WHERE `leaderGUID`=240404 AND `memberGUID`=240346;
UPDATE `creature_formations` SET `angle`=270,`point_1`=4, `point_2`=7 WHERE `leaderGUID`=240397 AND `memberGUID`=240375;
UPDATE `creature_formations` SET `angle`=260, `point_1`=4, `point_2`=8 WHERE `leaderGUID`=191567 AND `memberGUID` IN (191527);
UPDATE `creature_formations` SET `angle`=100, `point_1`=4, `point_2`=8 WHERE `leaderGUID`=191567 AND `memberGUID` IN (191525);
UPDATE `creature_formations` SET `point_1`=2, `point_2`=7 WHERE `leaderGUID`=191568 AND `memberGUID` IN (191526,191523);
UPDATE `creature_formations` SET `point_1`=1, `point_2`=10 WHERE `leaderGUID`=191515 AND `memberGUID` IN (191512,191511);
UPDATE `creature_formations` SET `point_1`=2, `point_2`=7 WHERE `leaderGUID`=256577 AND `memberGUID` IN (256588,256587);
UPDATE `creature_formations` SET `point_1`=3, `point_2`=6 WHERE `leaderGUID`=256576 AND `memberGUID` IN (256586,256585);

UPDATE `creature_template` SET `npcflag`=4194305 WHERE `entry`=9988;
UPDATE `conditions` SET `ConditionValue1` =4 WHERE `SourceGroup`=9576 AND `SourceTypeOrReferenceId`=15;
UPDATE `creature_template` SET `npcflag`=4194305 WHERE  `npcflag`=4194304 ;
UPDATE `creature_template` SET `npcflag`=4194307 WHERE  `npcflag`=4194306 ;
UPDATE `creature_template` SET `gossip_menu_id`=9821 WHERE `entry` IN (9976,9978,9979,9982,9985,9986,10048,10049,10051,10052,10057,10058,11105,13616,15131,16094,16586,16656,16824,17896,18984,19018,21336,21517,22469,9896,19325,22551,22577,23392,24905,24974,25037,25519,29251,30155,31991,32105,35290);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` IN (14) AND `SourceGroup`=9821;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`ScriptName`,`Comment`, `NegativeCondition`) VALUES
(14, 9821, 13557, 0, 15, 4, 0, 0, 0, '', 'Show gossip text if player is a hunter', 0),
(14, 9821, 13584, 0, 15, 4, 0, 0, 0, '', 'Show gossip text if player is not a hunter', 1);

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1, `action_menu_id`=9820 WHERE `menu_id`=9821 AND `id`=1;

DELETE FROM `gossip_menu` WHERE `entry`=11971 AND `text_id`=16788;
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES (11971,16788);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` IN (14) AND `SourceGroup`=11971;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`ScriptName`,`Comment`, `NegativeCondition`) VALUES
(14, 11971, 16788, 0, 15, 4, 0, 0, 0, '', 'Show gossip text if player is a hunter', 0),
(14, 11971, 16789, 0, 15, 4, 0, 0, 0, '', 'Show gossip text if player is not a hunter', 1);

DELETE FROM `npc_text` WHERE id=16788;
INSERT INTO `npc_text` (`ID`, `text0_0`, `BroadcastTextID0`) VALUES 
(16788, "Hey der, mon.$B$BDid ya want ta be stablin' yer pets, or were ya lookin' for a lost companion?", 45395);

DELETE FROM `gossip_menu_option` WHERE `menu_id` = 11971;
INSERT INTO `gossip_menu_option` (`menu_id`,`id`,`option_icon`,`option_text`,`OptionBroadcastTextID`,`option_id`,`npc_option_npcflag`,`action_menu_id`,`action_poi_id`,`box_coded`,`box_money`,`box_text`,`BoxBroadcastTextID`) VALUES
(11971,0,0,'I''d like to stable my pet here.',30181,14,4194304,0,0,0,0,'',0),
(11971,1,1,'I''m looking for a lost companion.',56613,1,1,9820,0,0,0,'',0);

DELETE FROM `gossip_menu` WHERE `entry`=9864 AND `text_id`=13662;
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES (9864,13662);

UPDATE `npc_text` SET `text0_0`="", `text0_1`="Well met, Battle-Sister. I can help stable your pets or assist you in recovering lost companions.", `BroadcastTextID0`=30667 WHERE `ID`=13662;

DELETE FROM `gossip_menu_option` WHERE `menu_id` = 9864;
INSERT INTO `gossip_menu_option` (`menu_id`,`id`,`option_icon`,`option_text`,`OptionBroadcastTextID`,`option_id`,`npc_option_npcflag`,`action_menu_id`,`action_poi_id`,`box_coded`,`box_money`,`box_text`,`BoxBroadcastTextID`) VALUES
(9864,0,0,'I''d like to stable my pet here.',30181,14,4194304,0,0,0,0,'',0),
(9864,1,1,'I''m looking for a lost companion.',56613,1,1,9820,0,0,0,'',0);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` IN (14) AND `SourceGroup`=9864;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`ScriptName`,`Comment`, `NegativeCondition`) VALUES
(14, 9864, 13662, 0, 15, 4, 0, 0, 0, '', 'Show gossip text if player is a hunter', 0),
(14, 9864, 13661, 0, 15, 4, 0, 0, 0, '', 'Show gossip text if player is not a hunter', 1);

DELETE FROM `gossip_menu_option` WHERE `menu_id` = 9212 AND `id`=1;
INSERT INTO `gossip_menu_option` (`menu_id`,`id`,`option_icon`,`option_text`,`OptionBroadcastTextID`,`option_id`,`npc_option_npcflag`,`action_menu_id`,`action_poi_id`,`box_coded`,`box_money`,`box_text`,`BoxBroadcastTextID`) VALUES
(9212,1,0,'I''d like to stable my pet here.',30181,14,4194304,0,0,0,0,'',0);

DELETE FROM `gossip_menu` WHERE `entry`=9820 AND `text_id`=13584;
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES (9820,13584);

DELETE FROM `gossip_menu_option` WHERE `menu_id` = 9820;
INSERT INTO `gossip_menu_option` (`menu_id`,`id`,`option_icon`,`option_text`,`OptionBroadcastTextID`,`option_id`,`npc_option_npcflag`,`action_menu_id`,`action_poi_id`,`box_coded`,`box_money`,`box_text`,`BoxBroadcastTextID`) VALUES
(9820,0,0,'I''ve lost Miniwing.',30182,1,1,0,0,0,0,'',0),
(9820,1,0,'I''ve lost my Jubling.',30183,1,1,0,0,0,0,'',0),
(9820,2,0,'I''ve lost my sprite darter hatchling.',30192,1,1,0,0,0,0,'',0),
(9820,3,0,'I''ve lost my worg pup.',30196,1,1,0,0,0,0,'',0),
(9820,4,0,'I''ve lost my Smolderweb hatchling.',30197,1,1,0,0,0,0,'',0),
(9820,5,0,'I''ve lost my Prairie Chicken.',30217,1,1,0,0,0,0,'',0),
(9820,6,0,'I''ve lost my wolpertinger.',30224,1,1,0,0,0,0,'',0);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` IN (15) AND `SourceGroup`=9820;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`ScriptName`,`Comment`, `NegativeCondition`) VALUES
(15, 9820, 0, 0, 8, 10898, 0, 0, 0, '', 'Show the gossip option if the player rewarded the quest', 0),
(15, 9820, 0, 0, 2, 31760, 1, 1, 0, '', 'Show the gossip option if the player Didn''t have the item', 1),
(15, 9820, 0, 0, 25, 39181, 0, 0, 0, '', 'Show the gossip option if the player Didn''t lear the spell', 1),
(15, 9820, 1, 0, 8, 7946, 0, 0, 0, '', 'Show the gossip option if the player rewarded the quest', 0),
(15, 9820, 1, 0, 2, 19450, 1, 1, 0, '', 'Show the gossip option if the player Didn''t have the item', 1),
(15, 9820, 1, 0, 2, 19462, 1, 1, 0, '', 'Show the gossip option if the player Didn''t have the item', 1),
(15, 9820, 1, 0, 25, 23811, 0, 0, 0, '', 'Show the gossip option if the player Didn''t lear the spell', 1),
(15, 9820, 2, 0, 8, 4298, 0, 0, 0, '', 'Show the gossip option if the player rewarded the quest', 0),
(15, 9820, 2, 0, 2, 11474, 1, 1, 0, '', 'Show the gossip option if the player Didn''t have the item', 1),
(15, 9820, 2, 0, 25, 15067, 0, 0, 0, '', 'Show the gossip option if the player Didn''t lear the spell', 1),
(15, 9820, 3, 0, 8, 4729, 0, 0, 0, '', 'Show the gossip option if the player rewarded the quest', 0),
(15, 9820, 3, 0, 2, 12264, 1, 1, 0, '', 'Show the gossip option if the player Didn''t have the item', 1),
(15, 9820, 3, 0, 25, 15999, 0, 0, 0, '', 'Show the gossip option if the player Didn''t lear the spell', 1),
(15, 9820, 4, 0, 8, 4862, 0, 0, 0, '', 'Show the gossip option if the player rewarded the quest', 0),
(15, 9820, 4, 0, 2, 12529, 1, 1, 0, '', 'Show the gossip option if the player Didn''t have the item', 1),
(15, 9820, 4, 0, 25, 16450, 0, 0, 0, '', 'Show the gossip option if the player Didn''t lear the spell', 1),
(15, 9820, 5, 0, 8, 3861, 0, 0, 0, '', 'Show the gossip option if the player rewarded the quest', 0),
(15, 9820, 5, 0, 2, 11110, 1, 1, 0, '', 'Show the gossip option if the player Didn''t have the item', 1),
(15, 9820, 5, 0, 25, 13548, 0, 0, 0, '', 'Show the gossip option if the player Didn''t lear the spell', 1),   
(15, 9820, 5, 1, 8, 13840, 0, 0, 0, '', 'Show the gossip option if the player rewarded the quest', 0),
(15, 9820, 5, 1, 2, 11110, 1, 1, 0, '', 'Show the gossip option if the player Didn''t have the item', 1),
(15, 9820, 5, 1, 25, 13548, 0, 0, 0, '', 'Show the gossip option if the player Didn''t lear the spell', 1),
(15, 9820, 6, 0, 8, 11117, 0, 0, 0, '', 'Show the gossip option if the player rewarded the quest', 0),
(15, 9820, 6, 0, 2, 32233, 1, 1, 0, '', 'Show the gossip option if the player Didn''t have the item', 1),
(15, 9820, 6, 0, 25, 39709, 0, 0, 0, '', 'Show the gossip option if the player Didn''t lear the spell', 1),
(15, 9820, 6, 1, 8, 11431, 0, 0, 0, '', 'Show the gossip option if the player rewarded the quest', 0),
(15, 9820, 6, 1, 2, 32233, 1, 1, 0, '', 'Show the gossip option if the player Didn''t have the item', 1),
(15, 9820, 6, 1, 25, 39709, 0, 0, 0, '', 'Show the gossip option if the player Didn''t lear the spell', 1);

UPDATE `creature_template` SET `AIName`="", `ScriptName`="npc_stable_master" WHERE `entry` IN (10052, 9978, 33854, 16764, 9986, 9987, 9989, 10045, 10046, 10047, 10048, 10049, 10050, 10051, 10053, 10054, 10055, 10056, 10057, 10058, 10059, 10060, 10061, 10062, 10063, 10085, 11069, 11104, 11105, 11117, 11119, 13616, 9983,  9982,  15131, 9981,  16094, 16185, 9985,  16656, 9980, 16824, 17485, 17666, 17896, 18244, 18250, 18984, 19018, 9979,  19368, 19476, 21336, 21517, 21518, 22468, 22469, 9896,  19325, 23392, 24905, 24974, 25037, 27010, 27385,  24066, 24067, 24154, 24350, 25519, 9977,  16586, 9976,  26597, 26721, 9984,  6749,  27056, 27065, 27068, 27150, 27183, 27194, 27948, 28057, 28690, 28790, 29250, 29251, 29658, 29740, 29906, 29948, 29959, 29967, 35344, 30039, 30155, 30304, 35290, 35291, 30008, 9988);



