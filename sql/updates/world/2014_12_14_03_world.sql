
SET @ENTRY=49874;
SET @GUID=48754;
SET @PATHID=48754;

DELETE FROM `waypoint_data` WHERE id=@PATHID;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`) VALUES 
(@PATHID, 0, -8918.082, -47.198, 88.489, 4.812, 5000, 0, 0, 100),
(@PATHID, 1, -8912.457, -42.856, 88.914, 0.547, 0, 0, 0, 100),
(@PATHID, 2, -8906.348, -41.829, 88.161, 0.166, 0, 0, 0, 100),
(@PATHID, 3, -8901.184, -43.418, 86.968, 5.825, 5000, 0, 0, 100),
(@PATHID, 4, -8906.348, -41.829, 88.161, 0.166, 0, 0, 0, 100),
(@PATHID, 5, -8912.457, -42.856, 88.914, 0.547, 0, 0, 0, 100);

UPDATE `creature` SET `MovementType`=2 WHERE `guid`=@GUID;

INSERT IGNORE INTO `creature_addon` (`guid`) VALUE (@GUID);
UPDATE `creature_addon` SET `path_id`=@PATHID WHERE `guid`=@GUID;


