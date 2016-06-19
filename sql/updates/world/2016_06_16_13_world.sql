


DELETE FROM `creature_text` WHERE `entry`=29903;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`,`BroadcastTextID`) VALUES
(29903, 0, 0, '%s sniffs and finds the trail.', 16, 0, 100, 0, 0, 0, 'Frostbite',30550),
(29903, 1, 0, 'The iron dwarves followed you! Use the net and the ice slick to escape!', 42, 0, 100, 0, 0, 0, 'Frostbite',30548),
(29903, 2, 0, '%s has tracked the scent to its source inside the cave.', 16, 0, 100, 377, 0, 0, 'Frostbite',30551),
(29903, 3, 0, 'Frostbite has tracked the scent to its source. Investigate the cave!', 42, 0, 100, 377, 0, 0, 'Frostbite',30549);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry`=29857;
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES 
(29857, 55460, 3, 0); -- old value 46598

UPDATE `creature_template` SET `spell1`=54997, `spell2`=54996,`ainame`='SmartAI', `scriptname`='' WHERE `entry`=29903;

DELETE FROM `smart_scripts` WHERE `entryorguid`=29903 AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2990300 AND `source_type`=9;

INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(29903,0,0,1,54,0,100,0,0,0,0,0,11,54993,0,0,0,0,0,1,0,0,0,0,0,0,0,'Frost Bite - On Just Summoned - Cast Frosthound Periodic'),
(29903,0,1,0,61,0,100,0,0,0,0,0,80,2990300,0,0,0,0,0,1,0,0,0,0,0,0,0,'Frost Bite - On Just Summoned - Run Script'),
(29903,0,2,0,7,0,100,0,0,0,0,0,11,54993,0,0,0,0,0,1,0,0,0,0,0,0,0,'Frost Bite - On Evade - Cast Frosthound Periodic'),
(29903,0,3,0,40,0,100,0,4,29903,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Frost Bite - On Reached WP3 - Say Line 1'),
(29903,0,4,5,40,0,100,0,23,29903,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'Frost Bite - On Reached WP3 - Say Line 2'),
(29903,0,5,6,61,0,100,0,0,0,0,0,1,3,0,0,0,0,0,23,0,0,0,0,0,0,0,'Frost Bite - On Reached WP3 - Say Line 3'),
(29903,0,6,7,61,0,100,0,0,0,0,0,33,29677,0,0,0,0,0,23,0,0,0,0,0,0,0,'Frost Bite - On Reached WP3 - Give Kill Credit'),
(29903,0,7,0,61,0,100,0,0,0,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Frost Bite - On Reached WP3 - Despawn'),
(2990300,9,0,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Frost Bite - Script - Say Line 0'),
(2990300,9,1,0,0,0,100,0,0,0,0,0,11,55476,0,0,0,0,0,1,0,0,0,0,0,0,0,'Frost Bite - Script - Cast Frostbite Boss Emote'),
(2990300,9,2,0,0,0,100,0,0,0,0,0,53,1,29903,0,0,0,0,1,0,0,0,0,0,0,0,'Frost Bite - Script - Start WP');

DELETE FROM `waypoints` WHERE `entry`=29903;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(29903, 1, 7749.87 ,-1092.157 ,925.391, 'Frost Bite'),
(29903, 2, 7730.882 ,-1117.335 ,923.5192, 'Frost Bite'),
(29903, 3, 7709.588 ,-1138.151 ,923.0368, 'Frost Bite'),
(29903, 4, 7684.467 ,-1156.5 ,926.3825, 'Frost Bite'),
(29903, 5, 7667.916 ,-1167.89 ,925.6334, 'Frost Bite'),
(29903, 6, 7644.327 ,-1188.346 ,924.3444, 'Frost Bite'),
(29903, 7, 7626.495 ,-1208.446 ,928.0288, 'Frost Bite'),
(29903, 8, 7616.337 ,-1225.497 ,931.144, 'Frost Bite'),
(29903, 9, 7603.483 ,-1248.83 ,929.348, 'Frost Bite'),
(29903, 10, 7587.603 ,-1277.074 ,930.1173, 'Frost Bite'),
(29903, 11, 7579.03 ,-1288.508 ,930.7244, 'Frost Bite'),
(29903, 12, 7562.141 ,-1316.05 ,930.8729, 'Frost Bite'),
(29903, 13, 7534.76 ,-1348.399 ,931.9465, 'Frost Bite'),
(29903, 14, 7511.374 ,-1368.219 ,933.2729, 'Frost Bite'),
(29903, 15, 7476.767 ,-1399.918 ,934.6421, 'Frost Bite'),
(29903, 16, 7453.468 ,-1419.903 ,935.6179, 'Frost Bite'),
(29903, 17, 7422.59 ,-1443.929 ,934.3792, 'Frost Bite'),
(29903, 18, 7390.717 ,-1473.35 ,930.7485, 'Frost Bite'),
(29903, 19, 7366.973 ,-1493.927 ,930.0501, 'Frost Bite'),
(29903, 20, 7341.166 ,-1526.338 ,932.729, 'Frost Bite'),
(29903, 21, 7328.682 ,-1533.398 ,932.6253, 'Frost Bite'),
(29903, 22, 7318.588 ,-1547.078 ,936.2808, 'Frost Bite'),
(29903, 23, 7311.917 ,-1563.737 ,940.9844, 'Frost Bite');

delete from creature where id=5668 and guid=5343;
delete from creature where id=5670 and guid=5342;

-- Pathing for Mattie Alred Entry: 5668 
SET @GUID1 := 50887;
SET @GUID2 := 50519;
SET @PATH := @GUID1 * 10;
DELETE FROM `creature_formations` WHERE `leaderGUID`=@GUID1;
INSERT INTO `creature_formations` VALUES
(@GUID1, @GUID1, 0, 0, 2, 0, 0),
(@GUID1, @GUID2, 3, 270, 2, 0, 0);

UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=1717.818,`position_y`=303.1138,`position_z`=-61.47988 WHERE `guid`=@GUID1;

DELETE FROM `creature_addon` WHERE `guid`=@GUID1;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID1,@PATH,0,0,1,0, '');

DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,1717.818,303.1138,-61.47988,0,0,0,0,100,0),
(@PATH,2,1724.056,285.5189,-62.18394,0,0,0,0,100,0),
(@PATH,3,1725.809,279.2398,-62.18219,0,0,0,0,100,0),
(@PATH,4,1728.313,268.6199,-62.17767,0,0,0,0,100,0),
(@PATH,5,1730.295,250.8002,-62.17767,0,0,0,0,100,0),
(@PATH,6,1716.658,240.3017,-62.17767,0,0,0,0,100,0),
(@PATH,7,1692.596,241.7838,-62.17767,0,0,0,0,100,0),
(@PATH,8,1672.504,242.9413,-62.17767,0,0,0,0,100,0),
(@PATH,9,1665.619,249.5088,-62.1778,0,0,0,0,100,0),
(@PATH,10,1663.849,264.2947,-62.17823,0,0,0,0,100,0),
(@PATH,11,1659.715,273.889,-62.17942,0,0,0,0,100,0),
(@PATH,12,1652.447,286.605,-62.18125,0,0,0,0,100,0),
(@PATH,13,1637.696,299.425,-62.17578,0,0,0,0,100,0),
(@PATH,14,1621.363,308.3512,-62.17768,0,0,0,0,100,0),
(@PATH,15,1605.388,311.2079,-62.17768,0,0,0,0,100,0),
(@PATH,16,1598.25,318.9116,-62.17767,0,0,0,0,100,0),
(@PATH,17,1598.482,334.9213,-62.17767,0,0,0,0,100,0),
(@PATH,18,1599.09,358.2072,-62.17767,0,0,0,0,100,0),
(@PATH,19,1598.418,367.1544,-62.22174,0,0,0,0,100,0),
(@PATH,20,1610.374,374.7628,-62.17767,0,0,0,0,100,0),
(@PATH,21,1627.031,371.8268,-62.17767,0,0,0,0,100,0),
(@PATH,22,1637.79,368.5305,-62.16847,0,0,0,0,100,0),
(@PATH,23,1655.578,358.9601,-60.74146,0,0,0,0,100,0),
(@PATH,24,1657.84,352.9977,-60.72892,0,0,0,0,100,0),
(@PATH,25,1654.79,342.4309,-62.17167,0,0,0,0,100,0),
(@PATH,26,1668.162,325.3488,-62.15568,0,0,0,0,100,0),
(@PATH,27,1680.751,314.6597,-62.15656,0,0,0,0,100,0),
(@PATH,28,1694.482,302.0437,-62.16363,0,0,0,0,100,0);


UPDATE creature_template SET npcflag=16777216 WHERE entry=35427;


-- Ymirjar Flesh Hunter
SET @ENTRY := 26670;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,1,0,100,6,0,0,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - Out of Combat - Disable Combat Movement (Dungeon)"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - On Aggro - Stop Attacking (No Repeat) (Normal Dungeon)"),
(@ENTRY,@SOURCETYPE,2,3,4,0,100,3,0,0,0,0,11,48854,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - On Aggro - Cast 'Shoot' (No Repeat) (Normal Dungeon)"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - Within 5-30 Range - Increment Phase By 1 (Phase 1) (Normal Dungeon)"),
(@ENTRY,@SOURCETYPE,4,5,9,1,100,2,5,30,5000,8000,11,48854,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - Within 5-30 Range - Cast 'Shoot' (Phase 1) (Normal Dungeon)"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,40,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - On Aggro - Set Sheath Ranged (No Repeat) (Heroic Dungeon)"),
(@ENTRY,@SOURCETYPE,6,7,4,0,100,5,0,0,0,0,11,59241,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - On Aggro - Cast 'Shoot' (No Repeat) (Heroic Dungeon)"),
(@ENTRY,@SOURCETYPE,7,0,61,0,100,0,0,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - On Gossip Option 0 Selected - Increment Phase By 1"),
(@ENTRY,@SOURCETYPE,8,9,9,1,100,4,5,30,5000,8000,11,59241,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - Within 5-30 Range - Cast 'Shoot' (Phase 1) (Heroic Dungeon)"),
(@ENTRY,@SOURCETYPE,9,0,61,0,100,0,0,0,0,0,40,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - Within 5-30 Range - Set Sheath Ranged (Phase 1) (Heroic Dungeon)"),
(@ENTRY,@SOURCETYPE,10,11,9,1,100,6,25,80,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - Within 25-80 Range - Enable Combat Movement (Phase 1) (Dungeon)"),
(@ENTRY,@SOURCETYPE,11,0,61,0,100,0,0,0,0,0,20,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - Within 25-80 Range - Start Attacking (Phase 1) (Dungeon)"),
(@ENTRY,@SOURCETYPE,12,13,9,1,100,6,0,5,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - Within 0-5 Range - Enable Combat Movement (Phase 1) (Dungeon)"),
(@ENTRY,@SOURCETYPE,13,14,61,0,100,0,0,0,0,0,40,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - Within 0-5 Range - Set Sheath Melee (Phase 1) (Dungeon)"),
(@ENTRY,@SOURCETYPE,14,0,61,0,100,0,0,0,0,0,20,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - Within 0-5 Range - Start Attacking (Phase 1) (Dungeon)"),
(@ENTRY,@SOURCETYPE,15,16,9,1,100,6,5,15,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - Within 5-15 Range - Disable Combat Movement (Phase 1) (Dungeon)"),
(@ENTRY,@SOURCETYPE,16,0,61,0,100,0,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - Within 5-15 Range - Stop Attacking (Phase 1) (Dungeon)"),
(@ENTRY,@SOURCETYPE,17,18,0,0,100,2,9000,14000,22000,26000,11,48871,0,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - In Combat - Cast 'Aimed Shot' (Normal Dungeon)"),
(@ENTRY,@SOURCETYPE,18,18,61,0,100,0,0,0,0,0,40,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - In Combat - Set Sheath Ranged (Normal Dungeon)"),
(@ENTRY,@SOURCETYPE,19,20,0,0,100,4,9000,14000,22000,26000,11,59243,0,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - In Combat - Cast 'Aimed Shot' (Heroic Dungeon)"),
(@ENTRY,@SOURCETYPE,20,0,61,0,100,0,0,0,0,0,40,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - In Combat - Set Sheath Ranged (Heroic Dungeon)"),
(@ENTRY,@SOURCETYPE,21,22,0,0,100,2,14000,17000,24000,27000,11,48872,1,0,0,0,0,6,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - In Combat - Cast 'Multi-Shot' (Normal Dungeon)"),
(@ENTRY,@SOURCETYPE,22,0,61,0,100,0,0,0,0,0,40,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - In Combat - Set Sheath Ranged (Normal Dungeon)"),
(@ENTRY,@SOURCETYPE,23,24,0,0,100,4,14000,17000,24000,27000,11,59244,1,0,0,0,0,6,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - In Combat - Cast 'Multi-Shot' (Heroic Dungeon)"),
(@ENTRY,@SOURCETYPE,24,0,61,0,100,0,0,0,0,0,40,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - In Combat - Set Sheath Ranged (Heroic Dungeon)"),
(@ENTRY,@SOURCETYPE,25,0,7,0,100,6,0,0,0,0,40,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Ymirjar Flesh Hunter - On Evade - Set Sheath Melee (Dungeon)");



-- Spire Gargoyle SAI
SET @ENTRY := 37544;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,3000,2000,4000,11,70189,0,0,0,0,0,2,0,0,0,0,0,0,0,"Spire Gargoyle - In Combat - Cast 'Poison Spit'");

-- Frenzied Abomination SAI
SET @ENTRY := 37546;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,6000,6000,6000,6000,11,70191,0,0,0,0,0,0,0,0,0,0,0,0,0,"Frenzied Abomination - In Combat - Cast 'Cleave'"),
(@ENTRY,0,1,0,0,0,100,0,30000,30000,60000,60000,11,70371,0,0,0,0,0,1,0,0,0,0,0,0,0,"Frenzied Abomination - In Combat - Cast 'Enrage'");

-- Skybreaker Summoner SAI
SET @ENTRY := 37148;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,3000,2000,6000,11,69969,0,0,0,0,0,5,0,0,0,0,0,0,0,"Skybreaker Summoner - In Combat - Cast 'Curse of Doom'"),
(@ENTRY,0,1,0,0,0,100,0,3000,3000,6000,10000,11,69972,0,0,0,0,0,2,0,0,0,0,0,0,0,"Skybreaker Summoner - In Combat - Cast 'Shadow Bolt'"),
(@ENTRY,0,2,0,0,0,100,0,10000,10000,10000,15000,11,69973,0,0,0,0,0,2,0,0,0,0,0,0,0,"Skybreaker Summoner - In Combat - Cast 'Incinerate'");

-- Kor'kron Necrolyte SAI
SET @ENTRY := 37149;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,3000,2000,6000,11,69969,0,0,0,0,0,5,0,0,0,0,0,0,0,"Kor'kron Necrolyte - In Combat - Cast 'Curse of Doom'"),
(@ENTRY,0,1,0,0,0,100,0,3000,3000,6000,10000,11,69972,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kor'kron Necrolyte - In Combat - Cast 'Shadow Bolt'"),
(@ENTRY,0,2,0,0,0,100,0,10000,10000,10000,15000,11,69973,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kor'kron Necrolyte - In Combat - Cast 'Incinerate'");

-- Skybreaker Luminary SAI
SET @ENTRY := 37016;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,1000,1500,20000,25000,11,69926,0,0,0,0,0,26,40,0,0,0,0,0,0,"Skybreaker Luminary - In Combat - Cast 'Earth Shield'"),
(@ENTRY,0,1,0,0,0,100,0,3000,3000,6000,7000,11,69958,0,0,0,0,0,26,40,0,0,0,0,0,0,"Skybreaker Luminary - In Combat - Cast 'Healing Wave'"),
(@ENTRY,0,2,0,0,0,100,0,4000,6000,6000,7000,11,69923,0,0,0,0,0,26,40,0,0,0,0,0,0,"Skybreaker Luminary - In Combat - Cast 'Chain Heal'"),
(@ENTRY,0,3,0,0,0,100,0,7000,8000,7000,8000,11,69970,0,0,0,0,0,2,0,0,0,0,0,0,0,"Skybreaker Luminary - In Combat - Cast 'Lightning Bolt'");

-- Kor'kron Oracle SAI
SET @ENTRY := 37031;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,1000,1500,20000,25000,11,69926,0,0,0,0,0,26,40,0,0,0,0,0,0,"Kor'kron Oracle - In Combat - Cast 'Earth Shield'"),
(@ENTRY,0,1,0,0,0,100,0,3000,3000,6000,7000,11,69958,0,0,0,0,0,26,40,0,0,0,0,0,0,"Kor'kron Oracle - In Combat - Cast 'Healing Wave'"),
(@ENTRY,0,2,0,0,0,100,0,4000,6000,6000,7000,11,69923,0,0,0,0,0,26,40,0,0,0,0,0,0,"Kor'kron Oracle - In Combat - Cast 'Chain Heal'"),
(@ENTRY,0,3,0,0,0,100,0,7000,8000,7000,8000,11,69970,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kor'kron Oracle - In Combat - Cast 'Lightning Bolt'");

-- Kor'kron Vanquisher SAI
SET @ENTRY := 37035;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,1,0,0,0,100,0,12000,12000,16000,20000,11,69927,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kor'kron Vanquisher - In Combat - Cast 'Avenger's Shield'"),
(@ENTRY,0,2,0,0,0,100,0,6000,6000,16000,18000,11,69930,0,0,0,0,0,1,0,0,0,0,0,0,0,"Kor'kron Vanquisher - In Combat - Cast 'Consecration'"),
(@ENTRY,0,3,0,0,0,100,0,4000,4000,16000,20000,11,69934,0,0,0,0,0,1,0,0,0,0,0,0,0,"Kor'kron Vanquisher - In Combat - Cast 'Holy Wrath'");


-- Skybreaker Assassin SAI
SET @ENTRY := 37017;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,1,0,0,0,100,0,60000,60000,100000,120000,11,69921,0,0,0,0,0,1,0,0,0,0,0,0,0,"Skybreaker Assassin - In Combat - Cast 'Fan of Knives'"),
(@ENTRY,0,2,0,0,0,100,0,0,0,4000,5000,11,69920,0,0,0,0,0,2,0,0,0,0,0,0,0,"Skybreaker Assassin - In Combat - Cast 'Sinister Strike'");

-- Skybreaker Marksman SAI
SET @ENTRY := 37144;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,3000,10000,14000,11,69989,0,0,0,0,0,2,0,0,0,0,0,0,0,"Skybreaker Marksman - In Combat - Cast 'Arcane Shot'"),
(@ENTRY,0,1,0,0,0,100,0,6000,6000,7000,14000,11,69975,0,0,0,0,0,2,0,0,0,0,0,0,0,"Skybreaker Marksman - In Combat - Cast 'Explosive Shot'"),
(@ENTRY,0,2,0,0,0,100,0,0,0,3000,4000,11,69974,0,0,0,0,0,2,0,0,0,0,0,0,0,"Skybreaker Marksman - In Combat - Cast 'Shoot'");

-- Kor'kron Sniper SAI
SET @ENTRY := 37146;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,3000,10000,14000,11,69989,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kor'kron Sniper - In Combat - Cast 'Arcane Shot'"),
(@ENTRY,0,1,0,0,0,100,0,6000,6000,7000,14000,11,69975,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kor'kron Sniper - In Combat - Cast 'Explosive Shot'"),
(@ENTRY,0,2,0,0,0,100,0,0,0,3000,4000,11,69974,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kor'kron Sniper - In Combat - Cast 'Shoot'");

-- Skybreaker Dreadblade SAI
SET @ENTRY := 37004;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,3000,6000,6000,11,69911,0,0,0,0,0,2,0,0,0,0,0,0,0,"Skybreaker Dreadblade - In Combat - Cast 'Blood Plague'"),
(@ENTRY,0,1,0,0,0,100,0,0,0,5000,6000,11,69917,0,0,0,0,0,2,0,0,0,0,0,0,0,"Skybreaker Dreadblade - In Combat - Cast 'Frost Fever'"),
(@ENTRY,0,2,0,0,0,100,0,0,500,5000,6000,11,69916,0,0,0,0,0,2,0,0,0,0,0,0,0,"Skybreaker Dreadblade - In Combat - Cast 'Icy Touch'"),
(@ENTRY,0,3,0,0,0,100,0,4000,5000,6000,6000,11,69912,0,0,0,0,0,2,0,0,0,0,0,0,0,"Skybreaker Dreadblade - In Combat - Cast 'Plague Strike'");

-- Kor'kron Reaver
SET @ENTRY := 37029;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,3000,3000,6000,6000,11,69911,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kor'kron Reaver - In Combat - Cast 'Blood Plague'"),
(@ENTRY,0,1,0,0,0,100,0,0,0,5000,6000,11,69917,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kor'kron Reaver - In Combat - Cast 'Frost Fever'"),
(@ENTRY,0,2,0,0,0,100,0,0,500,5000,6000,11,69916,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kor'kron Reaver - In Combat - Cast 'Icy Touch'"),
(@ENTRY,0,3,0,0,0,100,0,4000,5000,6000,6000,11,69912,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kor'kron Reaver- In Combat - Cast 'Plague Strike'");

-- Skybreaker Vicar SAI
SET @ENTRY := 37021;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,7000,7000,5000,10000,11,69963,0,0,0,0,0,26,40,0,0,0,0,0,0,"Skybreaker Vicar - In Combat - Cast 'Greater Heal'"),
(@ENTRY,0,1,0,0,0,100,0,0,0,7000,8000,11,69967,0,0,0,0,0,2,0,0,0,0,0,0,0,"Skybreaker Vicar - In Combat - Cast 'Smite'"),
(@ENTRY,0,2,0,0,0,100,0,25000,30000,25000,30000,11,69910,0,0,0,0,0,26,40,0,0,0,0,0,0,"Skybreaker Vicar - In Combat - Cast 'Pain Suppression'");

-- Kor'kron Templar SAI
SET @ENTRY := 37034;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,7000,7000,5000,10000,11,69963,0,0,0,0,0,26,40,0,0,0,0,0,0,"Kor'kron Templar - In Combat - Cast 'Greater Heal'"),
(@ENTRY,0,1,0,0,0,100,0,0,0,7000,8000,11,69967,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kor'kron Templar - In Combat - Cast 'Smite'"),
(@ENTRY,0,2,0,0,0,100,0,25000,30000,25000,30000,11,69910,0,0,0,0,0,26,40,0,0,0,0,0,0,"Kor'kron Templar - In Combat - Cast 'Pain Suppression'");

-- Skybreaker Sorcerer SAI
SET @ENTRY := 37026;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3000,4000,11,69869,0,0,0,0,0,2,0,0,0,0,0,0,0,"Skybreaker Sorcerer - In Combat - Cast 'Frostfire Bolt'"),
(@ENTRY,0,1,0,0,0,100,0,30000,30000,180000,180000,11,69904,0,0,0,0,0,1,0,0,0,0,0,0,0,"Skybreaker Sorcerer - In Combat - Cast 'Blink'"),
(@ENTRY,0,2,0,0,0,100,1,60000,60000,60000,60000,11,69810,0,0,0,0,0,1,0,0,0,0,0,0,0,"Skybreaker Sorcerer - In Combat - Cast 'Summon Skybreaker Battle Standard' (No Repeat)");

-- Kor'kron Invoker SAI
SET @ENTRY := 37033;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3000,4000,11,69869,0,0,0,0,0,2,0,0,0,0,0,0,0,"Kor'kron Invoker - In Combat - Cast 'Frostfire Bolt'"),
(@ENTRY,0,1,0,0,0,100,0,30000,30000,180000,180000,11,69904,0,0,0,0,0,1,0,0,0,0,0,0,0,"Kor'kron Invoker - In Combat - Cast 'Blink'"),
(@ENTRY,0,2,0,0,0,100,1,60000,60000,60000,60000,11,69810,0,0,0,0,0,1,0,0,0,0,0,0,0,"Kor'kron Invoker - In Combat - Cast 'Summon Kor'kron Battle Standard' (No Repeat)");

-- Skybreaker Hierophant SAI
SET @ENTRY := 37027;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,0,0,3000,5000,11,69898,0,0,0,0,0,26,40,0,0,0,0,0,0,"Skybreaker Hierophant - In Combat - Cast 'Rejuvenation'"),
(@ENTRY,0,1,0,0,0,100,0,7000,7000,18000,24000,11,69882,0,0,0,0,0,26,40,0,0,0,0,0,0,"Skybreaker Hierophant - In Combat - Cast 'Regrowth'"),
(@ENTRY,0,2,0,0,0,100,0,25000,25000,10000,15000,11,69899,0,0,0,0,0,26,40,0,0,0,0,0,0,"Skybreaker Hierophant - In Combat - Cast 'Healing Touch'"),
(@ENTRY,0,3,0,0,0,100,0,0,500,3000,5000,11,69968,0,0,0,0,0,2,0,0,0,0,0,0,0,"Skybreaker Hierophant - In Combat - Cast 'Wrath'");


delete from waypoint_data where id=9999999;

DELETE FROM `waypoints` WHERE `entry`=14508;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(14508,1,-13187.14, 319.7746, 33.2346, 'Short John Mithril'),
(14508,2,-13215.14, 322.7813, 33.24456, 'Short John Mithril'),
(14508,3,-13234.32, 314.1292, 33.20762, 'Short John Mithril'),
(14508,4,-13248.82, 299.0459, 33.22644, 'Short John Mithril'),
(14508,5,-13254.88, 284.0705, 33.24255, 'Short John Mithril'),
(14508,6,-13255.58, 264.5797, 33.24498, 'Short John Mithril'),
(14508,7,-13247.58, 243.589, 33.20824, 'Short John Mithril'),
(14508,8,-13237.57, 231.7462, 33.23737, 'Short John Mithril'),
(14508,9,-13233.31, 231.8894, 33.2352, 'Short John Mithril'),
(14508,10,-13235.35, 231.8208, 33.23225, 'Short John Mithril'),
(14508,11,-13234.51, 239.4648, 33.36068, 'Short John Mithril'),
(14508,12,-13239.65, 247.5611, 29.29738, 'Short John Mithril'),
(14508,13,-13244.49, 256.3933, 22.63047, 'Short John Mithril'),
(14508,14,-13241.24, 261.35, 21.93297, 'Short John Mithril'),
(14508,15,-13204.08, 277.1676, 21.98207, 'Short John Mithril'),
(14508,16,-13219.24, 275.4513, 21.98207, 'Short John Mithril'),
(14508,17,-13240.61, 268.921, 21.93298, 'Short John Mithril'),
(14508,18,-13240.61, 268.921, 21.93298, 'Short John Mithril'),
(14508,19,-13244.04, 261.8775, 21.93297, 'Short John Mithril'),
(14508,20,-13243.42, 254.9109, 23.88685, 'Short John Mithril'),
(14508,21,-13239.03, 245.3709, 29.23729, 'Short John Mithril'),
(14508,22,-13233.62, 238.1597, 33.35011, 'Short John Mithril'),
(14508,23,-13237.55, 232.776, 33.23082, 'Short John Mithril'),
(14508,24,-13250.02, 248.9038, 33.23286, 'Short John Mithril'),
(14508,25,-13255.25, 264.0384, 33.24439, 'Short John Mithril'),
(14508,26,-13255.29, 282.6273, 33.24288, 'Short John Mithril'),
(14508,27,-13248.91, 298.4456, 33.24187, 'Short John Mithril'),
(14508,28,-13233.84, 314.3157, 33.20814, 'Short John Mithril'),
(14508,29,-13215.96, 322.7598, 33.24435, 'Short John Mithril'),
(14508,30,-13199.4, 323.3979, 33.24255, 'Short John Mithril'),
(14508,31,-13188.29, 320.0755, 33.23479, 'Short John Mithril'),
(14508,32,-13184.82, 329.8854, 37.95504, 'Short John Mithril'),
(14508,33,-13184.48, 332.6711, 40.32992, 'Short John Mithril');


UPDATE `creature_template` SET `ainame`='SmartAI', `scriptname`='' WHERE `entry` =14508;
DELETE FROM `smart_scripts` WHERE `entryorguid` =14508 AND `source_type`=0;

INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(14508, 0, 0, 0, 68, 0, 100, 0, 16, 0, 0, 0, 53, 0, 14508, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Short John Mithril - On Event Start - Start WP'),
(14508, 0, 1, 0, 40, 0, 100, 0, 1, 14508, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Short John Mithril - On Reached WP1 - Say'),
(14508, 0, 2, 3, 40, 0, 100, 0, 16, 14508, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Short John Mithril - On Reached WP16 - Say'),
(14508, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 50, 179697, 10740, 0, 0, 0, 0, 8, 0, 0, 0, -13202.89, 276.757,21.85707,2.775069, 'Short John Mithril - On Reached WP19 - Spawn Chest'),
(14508, 0, 4, 0, 40, 0, 100, 0, 33, 14508, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 4.415683, 'Short John Mithril - On Reached WP33 - Set orientation');

DELETE FROM `creature_text` WHERE `entry`=14508;
INSERT INTO `creature_text`  VALUES 
(14508, 0, 0, "Arrr, Me Hearties!   I be havin'' some extra Treasure that I be givin'' away at the Gurubashi Arena!  All ye need do to collect it is open the chest I leave on the arena floor!", 14, 0, 100, 0, 0, 0, "Short John Mithril", 9730),
(14508, 1, 0, "Let the Bloodletting Begin!", 14, 0, 100, 0, 0, 0, "Short John Mithril", 9731);


-- Spell difficulty entry for Slag Pot Damage spell
DELETE FROM `spelldifficulty_dbc` WHERE `id` = 65722;
INSERT INTO `spelldifficulty_dbc` (`id`, `spellid0`, `spellid1`, `spellid2`, `spellid3`) VALUES
(65722, 65722, 65723, 0, 0);

-- Clean up unneeded criteria data, enables achievement Hot Pocket
DELETE FROM `achievement_criteria_data` WHERE `criteria_id` IN (10430, 10431) AND `type` = 18;

DELETE FROM `achievement_criteria_data` WHERE `criteria_id` IN (12358, 12359) AND `type` = 14;


UPDATE `creature_template` SET `AIName`='SmartAI',`ScriptName`='' WHERE `entry` IN(30894,31049);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN(30894,31049) AND `source_type`=0;

INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(30894, 0, 0, 1, 8, 0, 100, 0, 58151, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Lithe Stalker - On Spellhit (Subdued Lithe Stalker) - Store Targetlist'),
(30894, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 29, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Lithe Stalker - On Spellhit (Subdued Lithe Stalker) - Follow Target'),
(30894, 0, 2, 3, 8, 0, 100, 0, 58178, 0, 0, 0, 33, 31049, 0, 0, 0, 0, 0, 12, 1, 0, 0, 0, 0, 0, 0, 'Lithe Stalker - On Spellhit (CSA Dummy Effect) - Give Kill Credit'),
(30894, 0, 3, 0, 61, 0, 100, 0, 58178, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Lithe Stalker - On Spellhit (CSA Dummy Effect) - Despawn'),
(31049, 0, 0, 0, 1, 0, 100, 0, 0, 0, 1000, 1000, 11, 58178, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Geist Return Bunny - OOC - Cast CSA Dummy Effect (25 yards)');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=22 AND `SourceEntry`=30894;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(22, 4, 30894, 0, 0, 1, 1, 58151, 0, 0, 0, 0, 0, '', 'Only run AI if Lithe Stalker has Aura (Subdued Lithe Stalker)');


UPDATE `gameobject_template` SET `AIName`='SmartGameObjectAI' WHERE  `entry`=193424;
DELETE FROM `smart_scripts` WHERE `entryorguid`=193424 AND `source_type`=1;

INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(193424, 1, 0, 1, 62, 0, 100, 0, 10111, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Eye of Dominion - On Gossip Option 0 Selected - Close Gossip'),
(193424, 1, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 85, 58106, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Eye of Dominion - On Gossip Option 0 Selected - Invoker Cast Forcecast: Control Lithe Stalker'),
(193424, 1, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 85, 58037, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Eye of Dominion - On Gossip Option 0 Selected - Invoker Cast Control Lithe Stalker');

UPDATE `creature_template` SET `AIName`='SmartAI',`ScriptName`='' WHERE `entry` =30895;
DELETE FROM `smart_scripts` WHERE `entryorguid` =30895 AND `source_type`=0;

INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(30895, 0, 0, 0, 27, 0, 100, 1, 0, 0, 0, 0, 11, 58117, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Lithe Stalker - On Passenger Boarded - Cast Force Reaction: Scourge'),
(30895, 0, 1, 0, 28, 0, 100, 1, 0, 0, 0, 0, 28, 58117, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Lithe Stalker - On Passenger Removed - Remove Aura Force Reaction: Scourge');


UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry` IN(31119,30952,30951,31131,30951);

DELETE FROM `smart_scripts` WHERE `entryorguid`IN(31110,31119,30952,3095200,31131,3113100,30951);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(31110, 0, 0, 0, 54, 0, 100, 1, 0, 0, 0, 0, 11, 58548, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Eidolon Watcher - On Just Summoned - Cast Ethereal'),
(31110, 0, 1, 0, 27, 0, 100, 1, 0, 0, 0, 0, 11, 58548, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Eidolon Watcher - On Passenger Boarded - Cast Ethereal'),
(31110, 0, 2, 0, 28, 0, 100, 1, 0, 0, 0, 0, 28, 58548, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Eidolon Watcher - On Passenger Removed - Remove Ethereal'),
(31110, 0, 3, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 58548, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Eidolon Watcher - On Reset - Cast Ethereal'),
(31119, 0, 0, 1, 54, 0, 100, 1, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Bloody Meat - On Just Summoned - Store Targetlist'),
(31119, 0, 1, 0, 61, 0, 100, 1, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 30952, 0, 0, 0, 0, 0, 0, 'Bloody Meat - On Just Summoned - Set Data on Hungering Plaguehound'),
(31119, 0, 2, 3, 38, 0, 100, 1, 1, 1, 0, 0, 11, 58564, 2, 0, 0, 0, 0, 21, 100, 0, 0, 0, 0, 0, 0, 'Bloody Meat - On Data Set - Give Kill Credit'),
(31119, 0, 3, 0, 61, 0, 100, 1, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bloody Meat - On Data Set - Despawn'),
(30952, 0, 0, 0, 75, 0, 100, 0, 0, 31119, 20, 15000, 80, 3095200, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Hungering Plaguehound - On Bloody Meat within 20 yards - Run Script'),
(30951, 0, 0, 0, 8, 0, 100, 0, 45254, 0, 0, 0, 33, 30951, 0, 0, 0, 0, 0, 21, 50, 0, 0, 0, 0, 0, 0, 'Restless Lookout - On Spellhit - Killcredit'),
(31131, 0, 0, 0, 8, 0, 100, 0, 58662, 0, 300000, 300000, 80, 3113100, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Containment Crystal - On Spellhit - Run Script'),
(3113100, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 33, 31131, 0, 0, 0, 0, 0, 21, 50, 0, 0, 0, 0, 0, 0, 'Containment Crystal - Script - Kill Credit'),
(3113100, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 90, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Containment Crystal - Script - Set Bytes 1'),
(3113100, 9, 2, 0, 0, 0, 100, 0, 300000, 300000, 0, 0, 91, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Containment Crystal - Script - Remove Bytes 1'),
(3095200, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 89, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Hungering Plaguehound - Script - Disable Random Move'),
(3095200, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 19, 31119, 0, 0, 0, 0, 0, 0, 'Hungering Plaguehound - Script - Move to Bloodymeat'),
(3095200, 9, 2, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 31119, 0, 0, 0, 0, 0, 0, 'Hungering Plaguehound - Script - Move to Bloodymeat'),
(3095200, 9, 3, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Hungering Plaguehound - Script - Evade'),
(3095200, 9, 4, 0, 0, 0, 100, 0, 0, 0, 0, 0, 89, 5, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Hungering Plaguehound - Script - Enable Random Move');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`IN(-58563);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(-58563, 45254, 0,'Assasinate Restless Lookout triggers Suicide');


DELETE FROM `smart_scripts` WHERE `entryorguid`=30922 AND `source_type`=0 AND `id` IN(3,4,5,6);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(30922, 0, 3, 4, 8, 0, 100, 0, 58283, 0, 120000, 120000, 11, 52353, 0, 0, 0, 0, 0, 19, 30895, 0, 0, 0, 0, 0, 0, 'Umbral Brute - On Spellhit (Throw Rock) - Cast Script Effect - Creature Capture GUID to Dot Variable'),
(30922, 0, 4, 5,61, 0, 100, 0, 0, 0, 0, 0, 11, 56685, 0, 0, 0, 0, 0, 19, 30921, 0, 0, 0, 0, 0, 0, 'Umbral Brute - On Spellhit (Throw Rock) - Cast CSA Dummy Effect 1'),
(30922, 0, 5, 6,61, 0, 100, 0, 0, 0, 0, 0, 11, 59120, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Umbral Brute - On Spellhit (Throw Rock) - Cast Scourge Fight Kill Credit'),
(30922, 0, 6, 0,61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 30895, 0, 0, 0, 0, 0, 0, 'Umbral Brute - On Spellhit (Throw Rock) - Set Data 1 1 - Lithe Stalker');

DELETE FROM `smart_scripts` WHERE `entryorguid`=30895 AND `source_type`=0 AND `id` IN(2,3,4,5);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(30895, 0, 2, 0, 38, 0, 100, 0, 1, 1, 0, 0, 11, 59129, 2, 0, 0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 'Lithe Stalker - On Data Set 1 1 - Cast Scourge Fight Kill Credit For Real'),
(30895, 0, 3, 4, 38, 0, 100, 0, 2, 2, 0, 0, 11, 59098, 2, 0, 0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 'Lithe Stalker - On Data Set 2 2 - Cast Scourge Bomb Kill Credit'),
(30895, 0, 4, 0, 61, 0, 100, 0, 0, 0, 0, 0, 28, 58203, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Lithe Stalker - On Data Set 2 2 - Remove Iron chain'),
(30895, 0, 5, 0, 38, 0, 100, 0, 3, 3, 0, 0, 11, 59137, 2, 0, 0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 'Lithe Stalker - On Data Set 3 3 - Cast Gargoyle Kill Credit');

UPDATE `creature_template` SET `AIName`='SmartAI',`ScriptName`='' WHERE `entry` =31075;
DELETE FROM `smart_scripts` WHERE `entryorguid` =31075 AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` =3107500 AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(31075, 0, 0, 0, 8, 0, 100, 0, 58203, 0, 30000, 30000, 29, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Scourge Bomb - On Spell Hit (Iron Chain) - Follow Lith Stalker'),
(31075, 0, 1, 0, 34, 0, 100, 0, 0, 0, 0, 0, 11, 58206, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scourge Bomb - On Movement Inform - Cast Scourge Bomb Dragging Aura'),
(31075, 0, 2, 0, 38, 0, 100, 0, 1, 1, 0, 0, 80, 3107500, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scourge Bomb - On Data Set 1 1 - Run Script'),
(31075, 0, 3, 0, 1, 0, 100, 0, 1000, 1000, 1000, 1000, 101, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scourge Bomb - OOC - Set Home Position'),
(3107500, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 59078, 0, 0, 0, 0, 0, 19, 30920, 0, 0, 0, 0, 0, 0, 'Scourge Bomb - Script - Cast Scourge Bomb Explosion'),
(3107500, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 41, 1000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scourge Bomb - Script - Despawn');

DELETE FROM `smart_scripts` WHERE `entryorguid`=30920 AND `source_type`=0 AND `id` >0;
DELETE FROM `smart_scripts` WHERE `entryorguid` =3092000 AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(30920, 0, 1, 2, 75, 0, 100, 1, 0, 31075, 5, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Lumbering Atrocity - On Scourge Bomb within 5 yards - say'),
(30920, 0, 2, 3, 61, 0, 100, 1, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 31075, 0, 0, 0, 0, 0, 0, 'Lumbering Atrocity - On Scourge Bomb within 5 yards -  Set Data 1 1 on Scourge Bomb'),
(30920, 0, 3, 4, 61, 0, 100, 1, 0, 0, 0, 0, 45, 2, 2, 0, 0, 0, 0, 19, 30895, 0, 0, 0, 0, 0, 0, 'Lumbering Atrocity - On Scourge Bomb within 5 yards -  Set Data 2 2 on Lithstalker'),
(30920, 0, 4, 0, 61, 0, 100, 1, 0, 0, 0, 0, 80, 3092000, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Lumbering Atrocity - On Scourge Bomb within 5 yards -  Run Script'),
(3092000, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 52593, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Lumbering Atrocity - Script - Cast Bloated Abomination Feign Death'),
(3092000, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 52516, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Lumbering Atrocity - Script - Cast Burst at the Seams:Bone'),
(3092000, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 52520, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Lumbering Atrocity - Script - Cast Explode Abomination:Meat'),
(3092000, 9, 3, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 52523, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Lumbering Atrocity - Script - Cast Explode Abomination:Bloody Meat'),
(3092000, 9, 4, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 58231, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Lumbering Atrocity - Script - Cast Exploding Abomination'),
(3092000, 9, 5, 0, 0, 0, 100, 0, 400, 400, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Lumbering Atrocity - Script - Despawn');

DELETE FROM `creature_text` WHERE `entry`=30920;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) VALUES
(30920, 0, 0, 'What little geist want?', 12, 0, 100, 0, 0, 0, 'Lumbering Atrocity',31614),
(30920, 0, 1, 'Present?', 12, 0, 100, 0, 0, 0, 'Lumbering Atrocity',31609),
(30920, 0, 2, 'That not nice!', 12, 0, 100, 0, 0, 0, 'Lumbering Atrocity',31615),
(30920, 0, 3, 'What bomb thing for?', 12, 0, 100, 0, 0, 0, 'Lumbering Atrocity',31610),
(30920, 0, 4, 'Want me to deliver somewhere?', 12, 0, 100, 0, 0, 0, 'Lumbering Atrocity',31611),
(30920, 0, 5, 'I not sure this safe, little geist.', 12, 0, 100, 0, 0, 0, 'Lumbering Atrocity',31612),
(30920, 0, 6, 'This no go here.', 12, 0, 100, 0, 0, 0, 'Lumbering Atrocity',31613),
(30920, 0, 7, 'For me?', 12, 0, 100, 0, 0, 0, 'Lumbering Atrocity',31608);

UPDATE `creature_template` SET `AIName`='SmartAI',`ScriptName`='' WHERE `entry` =31012;
DELETE FROM `smart_scripts` WHERE `entryorguid` =31012 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(31012, 0, 0, 1, 8, 0, 100, 1, 58282, 0, 0, 0, 11, 58285, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Iceskin Sentry - On Spellhiy - Cast Gargoyle Explosion'),
(31012, 0, 1, 0, 61, 0, 100, 1, 0, 0, 0, 0, 45, 3, 3, 0, 0, 0, 0, 19, 30895, 0, 0, 0, 0, 0, 0, 'Iceskin Sentry - On Spellhiy - Set Data 3 3 on Lithe Stalker');


DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup` IN(10111,10028);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(15, 10111, 0, 0, 0, 9, 0, 13145, 0, 0, 0, 0, 0, '', 'Eye of Dominion - Show gossip option only if player has taken The Vile Hold (13145)'),
(15, 10111, 0, 0, 1, 9, 0, 13146, 0, 0, 0, 0, 0, '', 'Eye of Dominion - Show gossip option only if player has taken Generosity Abounds (13146)'),
(15, 10111, 0, 0, 2, 9, 0, 13147, 0, 0, 0, 0, 0, '', 'Eye of Dominion - Show gossip option only if player has taken Matchmaker (13147)'),
(15, 10111, 0, 0, 3, 9, 0, 13147, 0, 0, 0, 0, 0, '', 'Eye of Dominion - Show gossip option only if player has taken Stunning View (13160)'),
(15, 10028, 0, 0, 0, 9, 0, 13168, 0, 0, 0, 0, 0, '', 'Eye of Dominion - Show gossip option only if player has taken Parting Gifts (13168)'),
(15, 10028, 0, 0, 1, 9, 0, 13169, 0, 0, 0, 0, 0, '', 'Eye of Dominion - Show gossip option only if player has taken An Undeads Best Friend (13169)'),
(15, 10028, 0, 0, 2, 9, 0, 13171, 0, 0, 0, 0, 0, '', 'Eye of Dominion - Show gossip option only if player has taken From Whence They Came (13171)'),
(15, 10028, 0, 0, 3, 9, 0, 13170, 0, 0, 0, 0, 0, '', 'Eye of Dominion - Show gossip option only if player has taken Honor is for the Weak (13170)');

DELETE FROM `disables` WHERE `entry` IN (10185, 10296) AND `sourceType` = 4;

DELETE FROM `instance_template` WHERE `map` = 725;
INSERT INTO `instance_template` (`map`, `parent`, `script`, `allowMount`) VALUES
(725, 0, 'instance_stonecore', 0);

UPDATE `creature_template` SET `mechanic_immune_mask` = 617299839 WHERE `entry` IN (43391, 43438, 43214, 42188, 42333);






