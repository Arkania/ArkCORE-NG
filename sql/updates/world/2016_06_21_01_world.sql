
-- Short John Mithril
SET @ENTRY := 14508;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,68,0,100,0,16,0,0,0,53,0,14508,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Short John Mithril - On Event Start - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,40,0,100,0,1,14508,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Short John Mithril - On Reached WP1 - Say"),
(@ENTRY,@SOURCETYPE,2,3,40,0,100,0,16,14508,0,0,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Short John Mithril - On Reached WP16 - Say"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,85,23176,0,0,0,0,0,8,0,0,0,-13202.9,276.757,21.8571,2.77507,"Short John Mithril - On Reached WP19 - Spawn Chest"),
(@ENTRY,@SOURCETYPE,4,0,40,0,100,0,33,14508,0,0,66,0,0,0,0,0,0,8,0,0,0,0.0,0.0,0.0,4.41568,"Short John Mithril - On Reached WP33 - Set orientation");

-- Bjorn Halgurdsson
SET @ENTRY := 24238;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3000,4000,11000,13800,11,32736,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Mortal Strike"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5800,6200,18900,21200,11,33661,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Crush Armor"),
(@ENTRY,@SOURCETYPE,2,0,8,0,100,0,40085,0,6000,6000,85,43315,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Bjorn Insult Quest Credit");

-- Steel Gate Chief Archaeologist
SET @ENTRY := 24399;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,8954,0,0,0,11,45973,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Steel Gate Chief Archaeologist - On gossip option select - Cast spell"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Steel Gate Chief Archaeologist - On Link - Close gossip"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,11,43767,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Steel Gate Chief Archaeologist - On Link - Cast Invoker"),
(@ENTRY,@SOURCETYPE,3,4,19,0,100,0,11390,0,0,0,11,45973,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Steel Gate Chief Archaeologist - On Quest Accept - Cast spell"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,11,43767,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Steel Gate Chief Archaeologist - On Link - Cast Invoker"),
(@ENTRY,@SOURCETYPE,5,6,19,0,100,0,11390,0,0,0,85,43787,0,0,0,0,0,8,0,0,0,1972.77,-3265.38,134.719,0.0,"Steel Gate Chief Archaeologist - On Quest Accept - Summon Graple Target");

-- Steam Rager - On Death - Kill Credit

DELETE FROM `smart_scripts` WHERE `entryorguid`=24601 AND `id`=2 AND `source_type`=0 LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(24601,0,2,0,6,0,100,0,0,0,0,0,85,46377,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Steam Rager - On Death - Kill Credit");

-- Thorim - gossip select  - give quest credit

DELETE FROM `smart_scripts` WHERE `entryorguid`=29445 AND `id`=0 AND `source_type`=0 LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(29445,0,0,0,62,0,100,0,9926,0,0,0,85,56940,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Thorim - gossip select  - give quest credit");

-- Frost Bite - On Reached WP3 - Give Kill Credit

DELETE FROM `smart_scripts` WHERE `entryorguid`=29903 AND `id`=6 AND `source_type`=0 LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(29903,0,6,7,61,0,100,0,0,0,0,0,85,55036,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Frost Bite - On Reached WP3 - Give Kill Credit");

-- Lithe Stalker - On Spellhit (CSA Dummy Effect) - Give Kill Credit

DELETE FROM `smart_scripts` WHERE `entryorguid`=30894 AND `id`=2 AND `source_type`=0 LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(30894,0,2,3,8,0,100,0,58178,0,0,0,85,58190,0,0,0,0,0,12,1,0,0,0.0,0.0,0.0,0.0,"Lithe Stalker - On Spellhit (CSA Dummy Effect) - Give Kill Credit");

DELETE FROM `smart_scripts` WHERE `entryorguid`=41520 AND `id`=0 AND `source_type`=0 AND `link`=1 LIMIT 1;

-- Donneitemquette

DELETE FROM `smart_scripts` WHERE `entryorguid`=41520 AND `id`=0 AND `source_type`=0 LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(41520,0,0,0,23,0,100,0,77682,1,15100,15100,85,77684,0,0,0,0,0,21,3,0,0,0.0,0.0,0.0,0.0,"Donneitemquette");

DELETE FROM `smart_scripts` WHERE `entryorguid`=42638 AND `id`=0 AND `source_type`=0 AND `link`=1 LIMIT 1;

-- Herezegor Flametusk

DELETE FROM `smart_scripts` WHERE `entryorguid`=42638 AND `id`=1 AND `source_type`=0 LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(42638,0,1,0,62,0,100,0,42638,0,0,0,85,79653,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Herezegor Flametusk add item");

-- Skittering Spiderling

DELETE FROM `smart_scripts` WHERE `entryorguid`=42689 AND `id`=1 AND `source_type`=0 LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(42689,0,1,0,61,0,100,0,0,0,0,0,85,79591,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Skittering Spiderling add item");

-- Schnottz Scout - Scout journal

DELETE FROM `smart_scripts` WHERE `entryorguid`=45874 AND `id`=1 AND `source_type`=0 LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(45874,0,1,0,61,0,100,0,0,0,0,0,85,85796,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Schnottz Scout - Scout journal");
 
-- Schnottz Scout - Gafas

DELETE FROM `smart_scripts` WHERE `entryorguid`=45874 AND `id`=3 AND `source_type`=0 LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(45874,0,3,0,61,0,100,0,0,0,0,0,85,85798,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Schnottz Scout - Gafas");
 
-- Desert Fox - Additem

DELETE FROM `smart_scripts` WHERE `entryorguid`=47201 AND `id`=1 AND `source_type`=0 LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(47201,0,1,2,61,0,100,0,0,0,0,0,85,87963,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Desert Fox - Additem");

-- Commander Schnottz - Kill Credit

DELETE FROM `smart_scripts` WHERE `entryorguid`=47972 AND `id`=1 AND `source_type`=0 LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(47972,0,1,0,61,0,100,0,0,0,0,0,85,89563,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Commander Schnottz - Kill Credit");

-- On script - Cast - Invoker

DELETE FROM `smart_scripts` WHERE `entryorguid`=3833700 AND `id`=5 AND `source_type`=9 LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(3833700,9,5,0,0,0,100,0,12000,12000,0,0,85,71712,0,0,0,0,0,17,0,5,0,0.0,0.0,0.0,0.0,"On script - Cast - Invoker");

-- On script - Quest Credit - Nearby players.

DELETE FROM `smart_scripts` WHERE `entryorguid`=3833800 AND `id`=7 AND `source_type`=9 LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(3833800,9,7,0,0,0,100,0,1000,1000,0,0,85,71744,0,0,0,0,0,17,0,10,0,0.0,0.0,0.0,0.0,"On script - Quest Credit - Nearby players.");

-- On script - quest credit - nearby players

DELETE FROM `smart_scripts` WHERE `entryorguid`=3833900 AND `id`=8 AND `source_type`=9 LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(3833900,9,8,0,0,0,100,0,1000,1000,0,0,85,71751,0,0,0,0,0,17,0,10,0,0.0,0.0,0.0,0.0,"On script - quest credit - nearby players");
 
 delete from conditions where SourceEntry=48397;
 
 
