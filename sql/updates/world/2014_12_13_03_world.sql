
SET @GUID=68342;
SET @ID=68342;

DELETE FROM `waypoint_data` WHERE id=@ID;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`) VALUES 
(@ID, 1, 2232.630, -5297.400, 89.535, 0.000, 0, 0, 0, 100),
(@ID, 2, 2231.790, -5296.850, 89.535, 0.000, 0, 0, 0, 100),
(@ID, 3, 2230.630, -5299.600, 89.535, 0.000, 0, 0, 0, 100),
(@ID, 4, 2230.750, -5304.250, 89.535, 0.000, 0, 0, 0, 100),
(@ID, 5, 2229.700, -5314.070, 89.467, 0.000, 0, 0, 0, 100),
(@ID, 6, 2229.700, -5314.070, 89.467, 0.000, 0, 0, 0, 100);

UPDATE `creature` SET `MovementType`=2 WHERE `guid`=@GUID;

INSERT IGNORE INTO `creature_addon` (`guid`) VALUE (@GUID);
UPDATE `creature_addon` SET `path_id`=@ID WHERE `guid`=@GUID;


