
SET @ENTRY=49874;
SET @GUID=50035;
SET @PATHID=50035;

DELETE FROM `waypoint_data` WHERE id=@PATHID;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`) VALUES 
(@PATHID, 0, -8862.392, -68.692, 85.347, 4.038, 5000, 0, 0, 100),
(@PATHID, 1, -8855.483, -64.575, 85.564, 0.465, 0, 0, 0, 100),
(@PATHID, 2, -8846.617, -64.501, 84.880, 5.570, 0, 0, 0, 100),
(@PATHID, 3, -8845.326, -69.202, 84.854, 4.847, 5000, 0, 0, 100),
(@PATHID, 4, -8846.617, -64.501, 84.880, 5.570, 0, 0, 0, 100),
(@PATHID, 5, -8855.483, -64.575, 85.564, 0.465, 0, 0, 0, 100);

UPDATE `creature` SET `MovementType`=2 WHERE `guid`=@GUID;

INSERT IGNORE INTO `creature_addon` (`guid`) VALUE (@GUID);
UPDATE `creature_addon` SET `path_id`=@PATHID WHERE `guid`=@GUID;


