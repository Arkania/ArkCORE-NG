
SET @ENTRY=49874;
SET @GUID=50006;
SET @PATHID=50006;

DELETE FROM `waypoint_data` WHERE id=@PATHID;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`) VALUES 
(@PATHID, 0, -8910.790, -38.732, 89.975, 3.705, 7000, 0, 0, 100),
(@PATHID, 1, -8898.197, -42.666, 86.778, 5.959, 0, 0, 0, 100),
(@PATHID, 2, -8896.386, -47.218, 86.926, 5.091, 0, 0, 0, 100),
(@PATHID, 3, -8896.242, -50.722, 87.292, 4.753, 7000, 0, 0, 100),
(@PATHID, 4, -8896.386, -47.218, 86.926, 5.091, 0, 0, 0, 100),
(@PATHID, 5, -8898.197, -42.666, 86.778, 5.959, 0, 0, 0, 100);

UPDATE `creature` SET `MovementType`=2 WHERE `guid`=@GUID;

INSERT IGNORE INTO `creature_addon` (`guid`) VALUE (@GUID);
UPDATE `creature_addon` SET `path_id`=@PATHID WHERE `guid`=@GUID;

