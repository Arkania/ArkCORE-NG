
delete from spell_bonus_data where entry=88668;

SET @GUID=3906;
SET @PATHID=3906;

DELETE FROM `waypoint_data` WHERE id=@PATHID;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`) VALUES 
(@PATHID, 1, -9991.100, 601.473, 39.775, 0.000, 0, 0, 0, 100),
(@PATHID, 2, -9950.860, 587.611, 38.762, 0.000, 0, 0, 0, 100),
(@PATHID, 3, -9931.580, 550.986, 36.783, 0.000, 0, 0, 0, 100),
(@PATHID, 4, -9901.330, 555.418, 36.308, 0.000, 0, 0, 0, 100),
(@PATHID, 5, -9883.580, 573.903, 37.205, 0.000, 0, 0, 0, 100),
(@PATHID, 6, -9916.680, 548.890, 35.310, 0.000, 0, 0, 0, 100),
(@PATHID, 7, -9946.240, 569.831, 37.882, 0.000, 0, 0, 0, 100),
(@PATHID, 8, -9964.440, 589.810, 38.985, 0.000, 0, 0, 0, 100),
(@PATHID, 9, -9988.960, 601.340, 39.742, 0.000, 0, 0, 0, 100),
(@PATHID, 10, -10016.900, 654.152, 37.172, 0.000, 0, 0, 0, 100);

UPDATE `creature` SET `MovementType`=2 WHERE `guid`=@GUID;

INSERT IGNORE INTO `creature_addon` (`guid`) VALUE (@GUID);
UPDATE `creature_addon` SET `path_id`=@PATHID WHERE `guid`=@GUID;


