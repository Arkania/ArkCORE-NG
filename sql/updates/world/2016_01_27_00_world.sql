
-- Quest fix for "Spirits be praised" escort quest id=25189.
-- Query: SELECT * FROM `waypoints` WHERE entry=39325

update `quest_template` set `flags`=10,`SpecialFlags`=2 where `id`=25189;
delete from waypoints where entry=39325;
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES (39325,1,562.997,-4102.51,16.7166,'Matron start escort point 1');
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES (39325,2,555.197,-4099.27,15.988,NULL);
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES (39325,3,531.832,-4088.02,17.3711,NULL);
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES (39325,4,494.424,-4092.6,20.7331,NULL);
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES (39325,5,458.715,-4092.12,19.9677,NULL);
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES (39325,6,428.855,-4080.41,18.9763,NULL);
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES (39325,7,403.795,-4101.33,20.2952,NULL);
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES (39325,8,374.801,-4124.45,22.5308,NULL);
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES (39325,9,321.541,-4174.03,19.6734,NULL);
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES (39325,10,302.944,-4183.96,15.9791,NULL);
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES (39325,11,285.046,-4191.74,19.7184,NULL);
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES (39325,12,216.961,-4181.32,22.2233,NULL);
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES (39325,13,155.381,-4181.31,21.819,NULL);
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES (39325,14,103.661,-4187.2,21.5025,NULL);
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES (39325,15,69.7498,-4187.14,26.5646,NULL);
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES (39325,16,56.396,-4196.96,30.0534,NULL);
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES (39325,17,36.1102,-4204.75,34.3997,NULL);
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES (39325,18,35.5582,-4219.21,35.6572,NULL);
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES (39325,19,49.9231,-4218.63,34.9947,'Pause and despawn point');
-- SAI grandmother escort.
DELETE FROM `smart_scripts` WHERE `entryorguid` =39325;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(39325,0,0,1,19,0,100,1,25189,0,0,0,53,0,39325,0,0,0,0,1,0,0,0,0,0,0,0,'Start waypoint.');
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(39325,0,1,2,58,0,100,1,19,39325,0,0,15,25189,0,0,0,0,0,7,0,0,0,0,0,0,0,'quest credit 25189');
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(39325,0,2,3,58,0,100,1,19,0,0,0,33,39331,0,0,0,0,0,7,0,0,0,0,0,0,0,'Credit for Shore Patrol.');
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(39325,0,3,0,58,0,100,1,19,39325,0,0,41,2000,0,0,0,0,0,1,0,0,0,0,0,0,0,'Despawn matron');

-- Voljin
UPDATE `creature_template` SET `gossip_menu_id`=11020 WHERE `entry`=38225;

-- Gorrik
update `creature` set `phaseMask`=1,`curhealth`=10572 where `id`=2861;
-- double spawn 
delete from `creature` where `guid`=56742 and `id`=2861; 



