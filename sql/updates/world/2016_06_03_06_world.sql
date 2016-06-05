

DELETE FROM creature_text WHERE entry=27885;
INSERT INTO creature_text VALUES 
(27885, 0, 0, "Ah, I'll make him some fresh bread! I need to get some flour from Martha!", 12, 0, 100, 1, 0, 0, "", 27223);

-- Jena Anderson
SET @ENTRY := 27885;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,10,0,100,6,1,15,60000,90000,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Jena Anderson - On Near - Talk 0");

UPDATE creature_addon SET path_id=233702 WHERE guid=233702;
UPDATE creature SET MovementType=2 WHERE guid=233702;

DELETE FROM waypoint_data WHERE id=233702;
INSERT INTO waypoint_data VALUES 
(233702, 0, 1605.332153, 746.266357, 114.730873, 6.003164, 0, 0, 0, 100, 0),
(233702, 1, 1607.892822, 746.182800, 114.731377, 0.254046, 0, 0, 0, 100, 0),
(233702, 2, 1609.044678, 749.174683, 114.731506, 0.744920, 0, 0, 0, 100, 0),
(233702, 3, 1610.139038, 748.784058, 114.731506, 5.940330, 5000, 0, 0, 100, 0),
(233702, 4, 1608.137451, 742.672607, 114.731613, 4.412735, 5000, 0, 0, 100, 0),
(233702, 5, 1602.023071, 744.947449, 114.730156, 2.794815, 5000, 0, 0, 100, 0),
(233702, 6, 1602.000000, 748.404846, 114.731339, 2.865501, 0, 0, 0, 100, 0),
(233702, 7, 1604.626587, 749.735535, 114.731339, 5.995311, 5000, 0, 0, 100, 0),
(233702, 8, 1604.179321, 747.440735, 114.731339, 4.652280, 0, 0, 0, 100, 0);

