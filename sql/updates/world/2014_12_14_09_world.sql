
SET @ENTRY=49874;
SET @GUID=48620;
SET @PATHID=48620;

DELETE FROM `waypoint_data` WHERE id=@PATHID;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`) VALUES 
(@PATHID, 0, -8836.329, -116.466, 80.657, 3.057, 5000, 0, 0, 100),
(@PATHID, 1, -8833.628, -119.232, 80.693, 5.739, 0, 0, 0, 100),
(@PATHID, 2, -8830.742, -122.293, 80.706, 5.468, 0, 0, 0, 100),
(@PATHID, 3, -8829.675, -126.702, 80.851, 4.950, 5000, 0, 0, 100),
(@PATHID, 4, -8830.742, -122.293, 80.706, 5.468, 0, 0, 0, 100),
(@PATHID, 5, -8833.628, -119.232, 80.693, 5.739, 0, 0, 0, 100);

UPDATE `creature` SET `MovementType`=2 WHERE `guid`=@GUID;

INSERT IGNORE INTO `creature_addon` (`guid`) VALUE (@GUID);
UPDATE `creature_addon` SET `path_id`=@PATHID WHERE `guid`=@GUID;
