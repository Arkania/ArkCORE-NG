
-- Mal'Ganis is spawned from script
delete from creature where guid=233681 and id=26533;

-- activate chromie script
UPDATE creature_template SET ScriptName="npc_chromie_26527" WHERE entry=26527;

-- add waypoint for 26838 Dreadtalon
DELETE FROM waypoint_data WHERE id=225068;
INSERT INTO waypoint_data VALUES 
(225068, 0, 3912.76, 1018.02, 156.865, 0, 0, 0, 0, 100, 0),
(225068, 1, 3887.62, 1044.48, 156.865, 0, 0, 0, 0, 100, 0),
(225068, 2, 3887, 1065.33, 156.865, 0, 0, 0, 0, 100, 0),
(225068, 3, 3902.59, 1082.07, 153.809, 0, 0, 0, 0, 100, 0),
(225068, 4, 3932.91, 1094.74, 149.087, 0, 0, 0, 0, 100, 0),
(225068, 5, 3964.97, 1072.68, 151.198, 0, 0, 0, 0, 100, 0),
(225068, 6, 3964.99, 1029.14, 153.393, 0, 0, 0, 0, 100, 0),
(225068, 7, 3938.71, 1015.41, 156.865, 0, 0, 0, 0, 100, 0);

UPDATE creature_addon SET path_id=225068 WHERE guid=225068;

-- console error, item not exist
delete from npc_vendor where entry=14844 and item=93208;

-- console error, waypoint not used
delete from waypoint_data where id=797230;

DELETE FROM waypoint_data WHERE id=2550700 AND point=22;
INSERT INTO waypoint_data VALUES 
(2550700, 22, -8811.88, 634.469, 94.2293, 0, 0, 0, 273, 100, 0);

DELETE FROM waypoint_data WHERE id=883750;
INSERT INTO waypoint_data VALUES 
(883750, 0, -8541.23, 1144.3, 18.9831, 0, 3000, 0, 0, 100, 0),
(883750, 1, -8538.3, 1149.52, 19.0522, 0, 2000, 0, 0, 100, 0),
(883750, 2, -8538.3, 1149.52, 19.0522, 0, 15000, 0, 1029, 100, 0),
(883750, 3, -8538.3, 1149.52, 19.0522, 0, 2000, 0, 0, 100, 0),
(883750, 4, -8544.61, 1133.18, 18.1536, 0, 0, 0, 0, 100, 0),
(883750, 5, -8551.97, 1118.55, 19.0523, 0, 0, 0, 0, 100, 0),
(883750, 6, -8564.22, 1107.25, 19.0523, 0, 0, 0, 0, 100, 0),
(883750, 7, -8566.66, 1101.82, 19.0523, 0, 2000, 0, 0, 100, 0),
(883750, 8, -8566.66, 1101.82, 19.0523, 0, 15000, 0, 1030, 100, 0),
(883750, 9, -8566.66, 1101.82, 19.0523, 0, 2000, 0, 0, 100, 0),
(883750, 10, -8559.28, 1114.25, 19.0523, 0, 0, 0, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=883760;
INSERT INTO waypoint_data VALUES 
(883760, 0, -8576.71, 1146.47, 18.0207, 0, 0, 0, 0, 100, 0),
(883760, 1, -8592.24, 1140.14, 19.0232, 0, 2000, 0, 0, 100, 0),
(883760, 2, -8592.24, 1140.14, 19.0232, 0, 15000, 0, 1031, 100, 0),
(883760, 3, -8592.24, 1140.14, 19.0232, 0, 2000, 0, 0, 100, 0),
(883760, 4, -8587.63, 1142.05, 18.664, 0, 0, 0, 0, 100, 0),
(883760, 5, -8589.12, 1147.9, 18.8099, 0, 0, 0, 0, 100, 0),
(883760, 6, -8593.48, 1149.63, 19.0517, 0, 2000, 0, 0, 100, 0),
(883760, 7, -8593.48, 1149.63, 19.0517, 0, 15000, 0, 1032, 100, 0),
(883760, 8, -8593.48, 1149.63, 19.0517, 0, 2000, 0, 0, 100, 0),
(883760, 9, -8577.21, 1153.82, 17.9682, 0, 0, 0, 0, 100, 0),
(883760, 10, -8558.95, 1154.11, 18.8956, 0, 0, 0, 0, 100, 0),
(883760, 11, -8557.69, 1153.3, 19.0169, 0, 2000, 0, 0, 100, 0),
(883760, 12, -8557.69, 1153.3, 19.0169, 0, 15000, 0, 1033, 100, 0),
(883760, 13, -8557.69, 1153.3, 19.0169, 0, 2000, 0, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=883770;
INSERT INTO waypoint_data VALUES 
(883770, 0, -8418.49, 1216.51, 5.15492, 0, 0, 0, 0, 100, 0),
(883770, 1, -8437.26, 1216.18, 5.15686, 0, 2000, 0, 0, 100, 0),
(883770, 2, -8437.26, 1216.18, 5.15686, 0, 25000, 0, 1034, 100, 0),
(883770, 3, -8437.26, 1216.18, 5.15686, 0, 5000, 0, 0, 100, 0),
(883770, 4, -8418.49, 1216.51, 5.15492, 0, 0, 0, 0, 100, 0),
(883770, 5, -8401.74, 1217.04, 5.14119, 0, 2000, 0, 0, 100, 0),
(883770, 6, -8401.74, 1217.04, 5.14119, 0, 25000, 0, 1035, 100, 0),
(883770, 7, -8401.74, 1217.04, 5.14119, 0, 5000, 0, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=883780;
INSERT INTO waypoint_data VALUES 
(883780, 0, -8483.92, 1205.52, 5.30837, 0, 0, 0, 0, 100, 0),
(883780, 1, -8504.95, 1204.34, 5.43422, 0, 2000, 0, 0, 100, 0),
(883780, 2, -8504.95, 1204.34, 5.43422, 0, 25000, 0, 1036, 100, 0),
(883780, 3, -8504.95, 1204.34, 5.43422, 0, 5000, 0, 0, 100, 0),
(883780, 4, -8496.24, 1205.74, 5.33554, 0, 0, 0, 0, 100, 0),
(883780, 5, -8472.6, 1205.68, 5.3309, 0, 0, 0, 0, 100, 0),
(883780, 6, -8451.6, 1202.08, 5.28666, 0, 0, 0, 0, 100, 0),
(883780, 7, -8440.75, 1198.68, 5.49148, 0, 0, 0, 0, 100, 0),
(883780, 8, -8437.91, 1192.77, 5.47497, 0, 2000, 0, 0, 100, 0),
(883780, 9, -8437.91, 1192.77, 5.47497, 0, 25000, 0, 1037, 100, 0),
(883780, 10, -8437.91, 1192.77, 5.47497, 0, 5000, 0, 0, 100, 0),
(883780, 11, -8443.81, 1199.8, 5.43047, 0, 0, 0, 0, 100, 0),
(883780, 12, -8463.18, 1206.26, 5.2489, 0, 0, 0, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=1004930;
INSERT INTO waypoint_data VALUES 
(1004930, 0, 3694.05, -5419.93, 29.8607, 0, 0, 0, 0, 100, 0),
(1004930, 1, 3703.84, -5410.59, 31.9159, 0, 0, 0, 0, 100, 0),
(1004930, 2, 3713.04, -5396.53, 35.2108, 0, 0, 0, 0, 100, 0),
(1004930, 3, 3736.31, -5388.52, 37.2879, 0, 0, 0, 0, 100, 0),
(1004930, 4, 3758.76, -5378.36, 37.9129, 0, 0, 0, 0, 100, 0),
(1004930, 5, 3771.44, -5360.71, 46.7247, 0, 2000, 0, 1156, 100, 0),
(1004930, 6, 3657.57, -5440.7, 26.5234, 0, 0, 0, 0, 100, 0),
(1004930, 7, 3679.07, -5423.48, 29.6107, 0, 0, 0, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=1005300;
INSERT INTO waypoint_data VALUES 
(1005300, 0, 3745.2, -5187.22, 120.89, 0, 2000, 0, 1157, 100, 0);

DELETE FROM waypoint_data WHERE id=1004880;
INSERT INTO waypoint_data VALUES 
(1004880, 0, 3760.31, -5413.58, 26.5976, 0, 0, 0, 0, 100, 0),
(1004880, 1, 3767.48, -5379.59, 37.1119, 0, 0, 0, 0, 100, 0),
(1004880, 2, 3766.13, -5345.33, 53.1732, 0, 0, 0, 0, 100, 0),
(1004880, 3, 3777.34, -5323.27, 63.4175, 0, 0, 0, 0, 100, 0),
(1004880, 4, 3784.32, -5306.1, 69.4175, 0, 2000, 0, 1158, 100, 0),
(1004880, 5, 3638.17, -5528.01, 15.9111, 0, 0, 0, 0, 100, 0),
(1004880, 6, 3659.66, -5509.71, 18.4111, 0, 0, 0, 0, 100, 0),
(1004880, 7, 3685.62, -5492.93, 17.1109, 0, 0, 0, 0, 100, 0),
(1004880, 8, 3707.26, -5465.77, 22.0405, 0, 0, 0, 0, 100, 0),
(1004880, 9, 3740.28, -5445.48, 23.4599, 0, 0, 0, 0, 100, 0);

delete from conditions where SourceTypeOrReferenceId=14 and SourceGroup=9586 and SourceEntry=12939 and ConditionTypeOrReference=14 and ConditionValue1=13149;
insert into conditions values
(14, 9586, 12939, 0, 0, 14, 0, 13149, 0, 0, 0, 0, 0, "", "Show title before quest 13149 is taken");

delete from conditions where SourceTypeOrReferenceId=14 and SourceGroup=9586 and SourceEntry=13471 and ConditionTypeOrReference=9 and ConditionValue1=13149;
insert into conditions values
(14, 9586, 13471, 0, 0, 9, 0, 13149, 0, 0, 0, 0, 0, "", "Show title if quest 13149 is taken");

delete from conditions where SourceTypeOrReferenceId=14 and SourceGroup=9586 and SourceEntry=13470 and ConditionTypeOrReference=8 and ConditionValue1=13149;
insert into conditions values
(14, 9586, 13470, 0, 0, 8, 0, 13149, 0, 0, 0, 0, 0, "", "Show title if quest 13149 is rewardet");

delete from conditions where SourceTypeOrReferenceId=15 and SourceGroup=9586 and SourceEntry=0 and ConditionTypeOrReference=8 and ConditionValue1=13149;
insert into conditions values
(15, 9586, 0, 0, 0, 8, 0, 13149, 0, 0, 1, 0, 0, "", "Show gossip if quest 13149 is not rewardet");

delete from conditions where SourceTypeOrReferenceId=15 and SourceGroup=9586 and SourceEntry=1 and ConditionTypeOrReference=8 and ConditionValue1=13149;
insert into conditions values
(15, 9586, 1, 0, 0, 8, 0, 13149, 0, 0, 0, 0, 0, "", "Show gossip if quest 13149 is rewardet");

delete from conditions where SourceTypeOrReferenceId=15 and SourceGroup=9586 and SourceEntry=2 and ConditionTypeOrReference=8 and ConditionValue1=13151;
insert into conditions values
(15, 9586, 2, 0, 0, 8, 0, 13151, 0, 0, 0, 0, 0, "", "Show gossip if quest 13151 is rewardet");

-- Roger Owens
DELETE FROM creature_text WHERE entry=27903 AND groupid=0 AND id=0;
INSERT INTO creature_text VALUES 
(27903, 0, 0, "Ok, enough work for now. Time for refreshments and a little conversation in the inn.", 12, 0, 100, 0, 0, 0, "", 27247);

SET @ENTRY := 27903;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,10,0,100,7,1,15,5000,10000,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Worker say finish text");

-- Silvio Perelli
DELETE FROM creature_text WHERE entry=27876 AND groupid=0 AND id=0;
INSERT INTO creature_text VALUES 
(27876, 0, 0, "No, Sergeant.", 12, 0, 100, 1, 0, 0, "", 27198);

SET @ENTRY := 27876;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,10,0,100,1,1,15,5000,10000,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Answer to Sergeant Morigan");

-- Sergeant Morigan
DELETE FROM creature_text WHERE entry=27877 AND groupid=0 AND id=0;
INSERT INTO creature_text VALUES 
(27877, 0, 0, "You don't mind me checking out your merchandise for signs of tampering, do you?", 12, 0, 100, 1, 0, 0, "", 27205);

SET @ENTRY := 27877;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,10,0,100,1,1,15,5000,10000,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Sergeant Morigan ask for control");

-- Bartleby Battson
DELETE FROM creature_text WHERE entry=27907;
INSERT INTO creature_text VALUES 
(27907, 0, 0, "I knew I should have secured the wagon lock better when I was in Andorhal.", 12, 0, 100, 1, 0, 0, "", 27253),
(27907, 0, 1, "This grain shipment has been nothing but trouble!", 12, 0, 100, 1, 0, 0, "", 27254),
(27907, 0, 2, "I'm going to lose my on time bonus because of this!", 12, 0, 100, 1, 0, 0, "", 27255),
(27907, 0, 3, "I wasn't even supposed to be here today!", 12, 0, 100, 1, 0, 0, "", 27256),
(27907, 0, 4, "Well, guess I should load everything back into the cart.", 12, 0, 100, 1, 0, 0, "", 27257),
(27907, 0, 5, "Oh, come on! My cart broke, my horse lost a shoe, and now the cargo goes bad!", 12, 0, 100, 1, 0, 0, "", 27258),
(27907, 0, 6, "I guess I'll go find the authorities. If I'm lucky they'll tell me it's the plague and that we're all going to die.", 12, 0, 100, 1, 0, 0, "", 27259);

SET @ENTRY := 27907;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,10,0,100,0,1,15,15000,30000,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Battson Talk about work");



