
SET @ENTRY=49874;
SET @GUID=24305;
SET @PATHID=24305;

DELETE FROM `waypoint_data` WHERE id=@PATHID;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`) VALUES 
(@PATHID, 0, -8958.105, -66.691, 91.916, 4.560, 5000, 0, 0, 100),
(@PATHID, 1, -8958.966, -63.902, 92.220, 1.870, 0, 0, 0, 100),
(@PATHID, 2, -8962.438, -61.150, 92.262, 2.381, 0, 0, 0, 100),
(@PATHID, 3, -8966.710, -60.010, 91.899, 2.970, 5000, 0, 0, 100),
(@PATHID, 4, -8962.438, -61.150, 92.262, 2.381, 0, 0, 0, 100),
(@PATHID, 5, -8958.966, -63.902, 92.220, 1.870, 0, 0, 0, 100);

UPDATE `creature` SET `MovementType`=2 WHERE `guid`=@GUID;

INSERT IGNORE INTO `creature_addon` (`guid`) VALUE (@GUID);
UPDATE `creature_addon` SET `path_id`=@PATHID WHERE `guid`=@GUID;