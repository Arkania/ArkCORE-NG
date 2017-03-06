
SET @GUID=68061;
SET @ID=68061;

DELETE FROM `waypoint_data` WHERE id=@ID;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`) VALUES 
(@ID, 1, 2296.950, -5314.890, 90.267, 0.000, 0, 0, 0, 100),
(@ID, 2, 2297.930, -5315.090, 90.267, 0.000, 0, 0, 0, 100),
(@ID, 3, 2299.980, -5315.500, 90.380, 0.000, 0, 0, 0, 100),
(@ID, 4, 2309.180, -5321.400, 90.371, 0.000, 0, 0, 0, 100),
(@ID, 5, 2309.180, -5321.400, 90.371, 0.000, 0, 0, 0, 100);

UPDATE `creature` SET `MovementType`=2 WHERE `guid`=@GUID;

INSERT IGNORE INTO `creature_addon` (`guid`) VALUE (@GUID);
UPDATE `creature_addon` SET `path_id`=@ID WHERE `guid`=@GUID;


