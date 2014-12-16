
SET @ENTRY=49874;
SET @GUID=49393;
SET @PATHID=49393;

DELETE FROM `waypoint_data` WHERE id=@PATHID;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`) VALUES 
(@PATHID, 0, -8844.739, -76.670, 84.725, 4.247, 5000, 0, 0, 100),
(@PATHID, 1, -8844.345, -67.153, 84.836, 2.099, 0, 0, 0, 100),
(@PATHID, 2, -8851.762, -63.304, 85.238, 2.864, 0, 0, 0, 100),
(@PATHID, 3, -8858.159, -63.010, 85.779, 3.610, 5000, 0, 0, 100),
(@PATHID, 4, -8851.762, -63.304, 85.238, 2.864, 0, 0, 0, 100),
(@PATHID, 5, -8844.345, -67.153, 84.836, 2.099, 0, 0, 0, 100);

UPDATE `creature` SET `MovementType`=2 WHERE `guid`=@GUID;

INSERT IGNORE INTO `creature_addon` (`guid`) VALUE (@GUID);
UPDATE `creature_addon` SET `path_id`=@PATHID WHERE `guid`=@GUID;


