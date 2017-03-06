
SET @ENTRY=49874;
SET @GUID=50039;
SET @PATHID=50039;

DELETE FROM `waypoint_data` WHERE id=@PATHID;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`) VALUES 
(@PATHID, 0, -8870.675, -103.967, 81.788, 4.580, 5000, 0, 0, 100),
(@PATHID, 1, -8869.589, -97.520, 82.265, 1.419, 0, 0, 0, 100),
(@PATHID, 2, -8873.128, -93.171, 82.989, 2.271, 0, 0, 0, 100),
(@PATHID, 3, -8881.561, -94.053, 84.033, 3.748, 5000, 0, 0, 100),
(@PATHID, 4, -8873.128, -93.171, 82.989, 2.271, 0, 0, 0, 100),
(@PATHID, 5, -8869.589, -97.520, 82.265, 1.419, 0, 0, 0, 100);

UPDATE `creature` SET `MovementType`=2 WHERE `guid`=@GUID;

INSERT IGNORE INTO `creature_addon` (`guid`) VALUE (@GUID);
UPDATE `creature_addon` SET `path_id`=@PATHID WHERE `guid`=@GUID;


