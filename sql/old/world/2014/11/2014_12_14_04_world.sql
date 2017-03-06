
SET @ENTRY=49874;
SET @GUID=49701;
SET @PATHID=49701;

DELETE FROM `waypoint_data` WHERE id=@PATHID;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`) VALUES 
(@PATHID, 0, -8979.376, -43.774, 90.989, 4.098, 5000, 0, 0, 100),
(@PATHID, 1, -8979.385, -39.567, 91.202, 1.753, 0, 0, 0, 100),
(@PATHID, 2, -8981.122, -36.661, 91.534, 2.146, 0, 0, 0, 100),
(@PATHID, 3, -8984.838, -34.957, 91.457, 2.900, 5000, 0, 0, 100),
(@PATHID, 4, -8981.122, -36.661, 91.534, 2.146, 0, 0, 0, 100),
(@PATHID, 5, -8979.385, -39.567, 91.202, 1.753, 0, 0, 0, 100);

UPDATE `creature` SET `MovementType`=2 WHERE `guid`=@GUID;

INSERT IGNORE INTO `creature_addon` (`guid`) VALUE (@GUID);
UPDATE `creature_addon` SET `path_id`=@PATHID WHERE `guid`=@GUID;

