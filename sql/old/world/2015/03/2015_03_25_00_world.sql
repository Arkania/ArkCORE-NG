
update creature set spawndist=3, MovementType=1 where id=37956;

update creature set spawndist=3, MovementType=1 where id=37960;

SET @GUID:=89753;
SET @ID:=37960;
SET @PATHID:=89753;

DELETE FROM `creature` WHERE `guid`=@GUID AND `id`=@ID;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`curhealth`,`MovementType`) VALUES 
(@GUID, @ID,1,1,1,29806,-1296.02,-5519.22,20.49,3.16,300,42,2);

DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`) VALUES 
(@GUID,@PATHID);

DELETE FROM `waypoint_data` WHERE `id`=@PATHID;
INSERT INTO `waypoint_data` 
(`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`) VALUES 
(@PATHID,1,-1292.04,-5520.14,20.87,0.00,0,0,0,100),
(@PATHID,2,-1292.04,-5519.14,20.87,0.00,0,0,0,100),
(@PATHID,3,-1300.04,-5519.30,20.12,0.00,0,0,0,100),
(@PATHID,4,-1301.08,-5519.31,19.87,0.00,0,0,0,100),
(@PATHID,5,-1301.08,-5519.31,19.87,0.00,0,0,0,100);


SET @GUID:=88046;
SET @ID:=37960;
SET @PATHID:=88046;

DELETE FROM `creature` WHERE `guid`=@GUID AND `id`=@ID;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`curhealth`,`MovementType`) VALUES 
(@GUID, @ID,1,1,1,29806,-1561.31,-5269.05,7.52,1.88,300,42,2);

DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`) VALUES 
(@GUID,@PATHID);

DELETE FROM `waypoint_data` WHERE `id`=@PATHID;
INSERT INTO `waypoint_data` 
(`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`) VALUES 
(@PATHID,1,-1561.42,-5271.92,7.85,0.00,0,0,0,100),
(@PATHID,2,-1560.42,-5271.88,7.85,0.00,0,0,0,100),
(@PATHID,3,-1561.77,-5267.58,7.35,0.00,0,0,0,100),
(@PATHID,4,-1561.77,-5267.58,7.35,0.00,0,0,0,100);


SET @GUID:=90013;
SET @ID:=37960;
SET @GUID:=90013;

DELETE FROM `creature` WHERE `guid`=@GUID AND `id`=@ID;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`curhealth`,`MovementType`) VALUES 
(@GUID, @ID,1,1,1,29806,-1551.77,-5280.84,8.60,2.44,300,42,2);

DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`) VALUES 
(@GUID,@PATHID);

SET @PATHID:=251718;
DELETE FROM `waypoint_data` WHERE `id`=@PATHID;
INSERT INTO `waypoint_data` 
(`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`) VALUES 
(@PATHID,1,-1552.31,-5280.00,8.60,0.00,0,0,0,100),
(@PATHID,2,-1551.77,-5280.84,8.60,0.00,0,0,0,100),
(@PATHID,3,-1554.58,-5278.46,8.48,0.00,0,0,0,100),
(@PATHID,4,-1554.58,-5278.46,8.48,0.00,0,0,0,100);


SET @GUID:=88932;
SET @ID:=37960;
SET @PATHID:=88932;

DELETE FROM `creature` WHERE `guid`=@GUID AND `id`=@ID;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`curhealth`,`MovementType`) VALUES 
(@GUID, @ID,1,1,1,29806,-1556.23,-5300.56,9.28,2.16,300,42,2);

DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`) VALUES 
(@GUID,@PATHID);

DELETE FROM `waypoint_data` WHERE `id`=@PATHID;
INSERT INTO `waypoint_data` 
(`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`) VALUES 
(@PATHID,1,-1555.61,-5301.94,8.91,0.00,0,0,0,100),
(@PATHID,2,-1555.99,-5302.87,8.91,0.00,0,0,0,100),
(@PATHID,3,-1555.21,-5302.08,8.91,0.00,0,0,0,100),
(@PATHID,4,-1556.25,-5300.52,9.29,0.00,0,0,0,100),
(@PATHID,5,-1556.25,-5300.52,9.29,0.00,0,0,0,100);


SET @GUID:=88825;
SET @ID:=37960;
SET @PATHID:=88825;

DELETE FROM `creature` WHERE `guid`=@GUID AND `id`=@ID;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`curhealth`,`MovementType`) VALUES 
(@GUID, @ID,1,1,1,29806,-1556.21,-5285.23,8.73,1.94,300,42,2);

DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`) VALUES 
(@GUID,@PATHID);

DELETE FROM `waypoint_data` WHERE `id`=@PATHID;
INSERT INTO `waypoint_data` 
(`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`) VALUES 
(@PATHID,1,-1556.57,-5284.29,8.73,0.00,0,0,0,100),
(@PATHID,2,-1556.21,-5285.23,8.73,0.00,0,0,0,100),
(@PATHID,3,-1557.49,-5281.88,8.60,0.00,0,0,0,100),
(@PATHID,4,-1557.49,-5281.88,8.60,0.00,0,0,0,100);

update creature set spawndist=0, MovementType=0 where guid in (92814,94090);






