
-- fix issue #145

delete from creature_text where entry=17885 and groupid=0 and id=0;
insert into creature_text values 
(17885, 0, 0, "Hey, over here!", 12, 0, 100, 0, 0, 0, "", 53162);

-- Earthbinder Rayge
SET @ENTRY := 17885;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,6,0,0,0,0,33,17885,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Earthbinder Rayge - On Gossip Hello - Give Kill Credit"),
(@ENTRY,@SOURCETYPE,1,0,10,0,100,7,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Earthbinder Rayge - On Gossip Hello - Talk");

-- Weeder Greenthumb
SET @ENTRY := 17890;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,6,0,0,0,0,33,17890,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Weeder Greenthumb - On Gossip Hello - Give Kill Credit");

-- Naturalist Bite
SET @ENTRY := 17893;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,10,0,100,7,1,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Naturalist Bite - On LOS Out Of Combat - Say Line 0 (Dungeon Only)"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,6,0,0,0,0,33,17893,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Naturalist Bite - On Gossip Hello - KillCredit");

-- Windcaller Claw
SET @ENTRY := 17894;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,6,0,0,0,0,33,17894,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Windcaller Claw - On Gossip Hello - KillCredit");



