
SET @ENTRY=49874;
SET @GUID=49992;
SET @PATHID=49992;

DELETE FROM `waypoint_data` WHERE id=@PATHID;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`) VALUES 
(@PATHID, 0, -8842.742, -116.804, 80.377, 3.356, 5000, 0, 0, 100),
(@PATHID, 1, -8840.536, -116.642, 80.416, 0.073, 0, 0, 0, 100),
(@PATHID, 2, -8837.500, -116.741, 80.506, 6.251, 0, 0, 0, 100),
(@PATHID, 3, -8831.698, -118.669, 80.781, 5.426, 5000, 0, 0, 100),
(@PATHID, 4, -8837.500, -116.741, 80.506, 6.251, 0, 0, 0, 100),
(@PATHID, 5, -8840.536, -116.642, 80.416, 0.073, 0, 0, 0, 100);

UPDATE `creature` SET `MovementType`=2 WHERE `guid`=@GUID;

INSERT IGNORE INTO `creature_addon` (`guid`) VALUE (@GUID);
UPDATE `creature_addon` SET `path_id`=@PATHID WHERE `guid`=@GUID;