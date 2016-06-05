
-- creature 30571
delete from creature_text where entry=30571 and groupid=0 and id in (0,1);
insert into creature_text values 
(30571, 0, 0, "Hey! Stop rooting around in my cellar! Clear out!", 12, 0, 100, 0, 0, 0, "", 31322),
(30571, 0, 1, "What were you doing in my cellar? There's a food scare going on, and the last thing I need is strangers rummaging around in my goods! Shoo!", 12, 0, 100, 0, 0, 0, "", 31323);

UPDATE creature_template SET AIName="SmartAI" WHERE entry=30571;

DELETE FROM `smart_scripts` WHERE `entryorguid`=30571 AND `id`=0 AND `source_type`=0 LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(30571,0,0,0,10,0,100,7,1,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On LOS Out Of Combat - Say groupid 0 ");


