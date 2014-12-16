
SET @GUID=68610;
SET @ID=68610;

DELETE FROM `waypoint_data` WHERE id=@ID;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`) VALUES 
(@ID, 1, 2327.790, -5345.710, 90.427, 0.000, 0, 0, 0, 100),
(@ID, 2, 2328.580, -5345.100, 90.427, 0.000, 0, 0, 0, 100),
(@ID, 3, 2330.470, -5343.650, 90.388, 0.000, 0, 0, 0, 100),
(@ID, 4, 2336.400, -5341.460, 90.496, 0.000, 0, 0, 0, 100),
(@ID, 5, 2336.400, -5341.460, 90.496, 0.000, 0, 0, 0, 100);

UPDATE `creature` SET `MovementType`=2 WHERE `guid`=@GUID;

INSERT IGNORE INTO `creature_addon` (`guid`) VALUE (@GUID);
UPDATE `creature_addon` SET `path_id`=@ID WHERE `guid`=@GUID;


