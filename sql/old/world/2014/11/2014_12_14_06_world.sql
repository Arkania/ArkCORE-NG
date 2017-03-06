
SET @ENTRY=49874;
SET @GUID=49917;
SET @PATHID=49917;

DELETE FROM `waypoint_data` WHERE id=@PATHID;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`) VALUES 
(@PATHID, 0, -8921.853, -78.846, 87.948, 4.910, 5000, 0, 0, 100),
(@PATHID, 1, -8921.534, -73.285, 88.767, 1.769, 0, 0, 0, 100),
(@PATHID, 2, -8926.493, -69.391, 89.696, 2.495, 0, 0, 0, 100),
(@PATHID, 3, -8930.614, -70.215, 89.845, 3.394, 5000, 0, 0, 100),
(@PATHID, 4, -8926.493, -69.391, 89.696, 2.495, 0, 0, 0, 100),
(@PATHID, 5, -8921.534, -73.285, 88.767, 1.769, 0, 0, 0, 100);

UPDATE `creature` SET `MovementType`=2 WHERE `guid`=@GUID;

INSERT IGNORE INTO `creature_addon` (`guid`) VALUE (@GUID);
UPDATE `creature_addon` SET `path_id`=@PATHID WHERE `guid`=@GUID;


