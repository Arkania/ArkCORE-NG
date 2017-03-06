
SET @GUID=67875;
SET @ID=67875;

DELETE FROM `waypoint_data` WHERE id=@ID;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`) VALUES 
(@ID, 1, 2248.950, -5251.470, 96.021, 0.000, 0, 0, 0, 100),
(@ID, 2, 2222.480, -5286.320, 96.058, 0.000, 0, 0, 0, 100),
(@ID, 3, 2213.030, -5315.600, 99.853, 0.000, 0, 0, 0, 100),
(@ID, 4, 2220.950, -5335.590, 100.981, 0.000, 0, 0, 0, 100),
(@ID, 5, 2234.000, -5340.950, 98.916, 0.000, 0, 0, 0, 100),
(@ID, 6, 2254.380, -5336.100, 100.981, 0.000, 0, 0, 0, 100),
(@ID, 7, 2281.870, -5319.980, 99.744, 0.000, 0, 0, 0, 100),
(@ID, 8, 2324.230, -5290.130, 99.527, 0.000, 0, 0, 0, 100),
(@ID, 9, 2365.940, -5259.190, 94.329, 0.000, 0, 0, 0, 100),
(@ID, 10, 2374.890, -5241.550, 94.850, 0.000, 0, 0, 0, 100),
(@ID, 11, 2357.650, -5229.590, 100.980, 0.000, 0, 0, 0, 100),
(@ID, 12, 2325.250, -5222.080, 100.981, 0.000, 0, 0, 0, 100),
(@ID, 13, 2290.850, -5225.840, 98.095, 0.000, 0, 0, 0, 100),
(@ID, 14, 2248.950, -5251.470, 96.021, 0.000, 0, 0, 0, 100),
(@ID, 15, 2222.480, -5286.320, 96.058, 0.000, 0, 0, 0, 100),
(@ID, 16, 2213.030, -5315.600, 99.853, 0.000, 0, 0, 0, 100);

UPDATE `creature` SET `id`=11099, `MovementType`=2 WHERE `guid`=@GUID;

INSERT IGNORE INTO `creature_addon` (`guid`) VALUE (@GUID);
UPDATE `creature_addon` SET `path_id`=@ID, `mount`=22471, `bytes1`=50331648,`bytes2`=257  WHERE `guid`=@GUID;

UPDATE `creature_template` SET `InhabitType`=3, `unit_flags`=0, `type_flags`=2048,`dynamicflags`=0, `flags_extra`=0 WHERE `entry`=16378;
UPDATE `creature_template` SET `InhabitType`=4, `unit_flags`=32768, `type_flags`=2048,`dynamicflags`=2048, `flags_extra`=0 WHERE `entry`=11099;

























