

SET @GUID=270624;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4315.13, 6753.81, -27.3731, 0, 0, 0),
(@GUID, 1, -4314.44, 6754.54, -27.3731, 0, 0, 0),
(@GUID, 2, -4316.74, 6751.09, -27.6231, 0, 0, 0),
(@GUID, 3, -4316.74, 6751.09, -27.6231, 0, 0, 0);

SET @GUID=270619;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4286.22, 5779.24, -21.2328, 0, 0, 0),
(@GUID, 1, -4287.21, 5779.38, -21.2328, 0, 0, 0),
(@GUID, 2, -4283.48, 5777.93, -22.1078, 0, 0, 0),
(@GUID, 3, -4279.75, 5776.48, -22.7328, 0, 0, 0),
(@GUID, 4, -4276.03, 5775.03, -23.3578, 0, 0, 0),
(@GUID, 5, -4270.44, 5772.86, -24.1078, 0, 0, 0),
(@GUID, 6, -4270.03, 5772.7, -24.1078, 0, 0, 0),
(@GUID, 7, -4270.03, 5772.7, -24.1078, 0, 0, 0);

SET @GUID=270604;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -3584.77, 6719.05, -14.4096, 0, 0, 0),
(@GUID, 1, -3583.82, 6718.76, -14.4096, 0, 0, 0),
(@GUID, 2, -3585.33, 6725.59, -15.0346, 0, 0, 0),
(@GUID, 3, -3585.59, 6726.74, -15.3283, 0, 0, 0),
(@GUID, 4, -3585.59, 6726.74, -15.3283, 0, 0, 0);

SET @GUID=270602;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4212.37, 5786.53, -16.8, 0, 0, 0),
(@GUID, 1, -4211.79, 5787.35, -16.8, 0, 0, 0),
(@GUID, 2, -4212.8, 5785.62, -17.425, 0, 0, 0),
(@GUID, 3, -4213.82, 5783.9, -18.675, 0, 0, 0),
(@GUID, 4, -4214.83, 5782.18, -19.675, 0, 0, 0),
(@GUID, 5, -4216.35, 5779.59, -20.55, 0, 0, 0),
(@GUID, 6, -4216.71, 5778.99, -20.8013, 0, 0, 0),
(@GUID, 7, -4216.71, 5778.99, -20.8013, 0, 0, 0);

SET @GUID=270655;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -3575.83, 6648.77, -24.293, 0, 0, 0),
(@GUID, 1, -3576.79, 6649.02, -24.293, 0, 0, 0),
(@GUID, 2, -3578.27, 6650.37, -23.543, 0, 0, 0),
(@GUID, 3, -3579.01, 6651.04, -22.918, 0, 0, 0),
(@GUID, 4, -3580.49, 6652.4, -22.043, 0, 0, 0),
(@GUID, 5, -3581.96, 6653.75, -21.418, 0, 0, 0),
(@GUID, 6, -3584.49, 6656.06, -20.878, 0, 0, 0),
(@GUID, 7, -3584.49, 6656.06, -20.878, 0, 0, 0);

SET @GUID=270632;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4377.93, 6610.62, 2.29174, 0, 0, 0),
(@GUID, 1, -4377.1, 6611.18, 2.29174, 0, 0, 0),
(@GUID, 2, -4378.03, 6616.09, 1.66674, 0, 0, 0),
(@GUID, 3, -4378.77, 6620.02, 1.04174, 0, 0, 0),
(@GUID, 4, -4378.88, 6620.55, 0.98486, 0, 0, 0),
(@GUID, 5, -4378.88, 6620.55, 0.98486, 0, 0, 0);

SET @GUID=270658;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4254.34, 5821.22, -0.1539, 0, 0, 0),
(@GUID, 1, -4255.01, 5821.96, -0.1539, 0, 0, 0),
(@GUID, 2, -4256.49, 5824.57, 0.8461, 0, 0, 0),
(@GUID, 3, -4257.48, 5826.31, 1.4711, 0, 0, 0),
(@GUID, 4, -4258.96, 5828.92, 2.2211, 0, 0, 0),
(@GUID, 5, -4260.08, 5830.88, 3.741, 0, 0, 0),
(@GUID, 6, -4260.08, 5830.88, 3.741, 0, 0, 0);

SET @GUID=270608;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -3758.12, 6824.8, -11.6824, 0, 0, 0),
(@GUID, 1, -3758.75, 6825.57, -11.6824, 0, 0, 0),
(@GUID, 2, -3758.02, 6823.71, -11.0574, 0, 0, 0),
(@GUID, 3, -3757.28, 6821.86, -10.4324, 0, 0, 0),
(@GUID, 4, -3755.43, 6817.21, -9.68235, 0, 0, 0),
(@GUID, 5, -3754.05, 6813.76, -8.97288, 0, 0, 0),
(@GUID, 6, -3754.05, 6813.76, -8.97288, 0, 0, 0);

SET @GUID=270661;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4438.79, 6512.58, 3.38158, 0, 0, 0),
(@GUID, 1, -4437.83, 6512.85, 3.38158, 0, 0, 0),
(@GUID, 2, -4437.85, 6525.85, 2.75658, 0, 0, 0),
(@GUID, 3, -4437.86, 6530.85, 2.13158, 0, 0, 0),
(@GUID, 4, -4437.87, 6534.85, 1.40767, 0, 0, 0),
(@GUID, 5, -4437.85, 6537.79, 1.04244, 0, 0, 0),
(@GUID, 6, -4437.85, 6537.79, 1.04244, 0, 0, 0);

SET @GUID=270647;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4337.79, 6103.6, -4.55494, 0, 0, 0),
(@GUID, 1, -4337.06, 6104.27, -4.55494, 0, 0, 0),
(@GUID, 2, -4339.8, 6101.36, -5.17994, 0, 0, 0),
(@GUID, 3, -4350.08, 6090.43, -5.69941, 0, 0, 0),
(@GUID, 4, -4353.51, 6086.79, -6.44941, 0, 0, 0),
(@GUID, 5, -4353.77, 6086.5, -6.47968, 0, 0, 0),
(@GUID, 6, -4353.77, 6086.5, -6.47968, 0, 0, 0);

SET @GUID=270646;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4485.45, 6143.58, -15.558, 0, 0, 0),
(@GUID, 1, -4485.88, 6144.48, -15.558, 0, 0, 0),
(@GUID, 2, -4485.11, 6142.63, -16.183, 0, 0, 0),
(@GUID, 3, -4483.95, 6139.87, -16.933, 0, 0, 0),
(@GUID, 4, -4483.18, 6138.02, -17.558, 0, 0, 0),
(@GUID, 5, -4482.4, 6136.18, -18.183, 0, 0, 0),
(@GUID, 6, -4481.63, 6134.34, -18.808, 0, 0, 0),
(@GUID, 7, -4479.26, 6128.67, -18.5938, 0, 0, 0),
(@GUID, 8, -4479.26, 6128.67, -18.5938, 0, 0, 0);

SET @GUID=270635;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4532.89, 6385.86, -10.4929, 0, 0, 0),
(@GUID, 1, -4533.89, 6385.91, -10.4929, 0, 0, 0),
(@GUID, 2, -4517.62, 6381.03, -11.1059, 0, 0, 0),
(@GUID, 3, -4511.88, 6379.31, -11.8559, 0, 0, 0),
(@GUID, 4, -4511.39, 6379.17, -11.9265, 0, 0, 0),
(@GUID, 5, -4511.39, 6379.17, -11.9265, 0, 0, 0);

SET @GUID=270638;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4446.3, 6561.27, -11.7173, 0, 0, 0),
(@GUID, 1, -4445.77, 6562.13, -11.7173, 0, 0, 0),
(@GUID, 2, -4447.9, 6557.6, -11.0923, 0, 0, 0),
(@GUID, 3, -4450.88, 6551.26, -10.3423, 0, 0, 0),
(@GUID, 4, -4451.04, 6550.94, -10.2881, 0, 0, 0),
(@GUID, 5, -4451.04, 6550.94, -10.2881, 0, 0, 0);

SET @GUID=270640;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4384.42, 6684.72, -30.3699, 0, 0, 0),
(@GUID, 1, -4384.31, 6683.73, -30.3699, 0, 0, 0),
(@GUID, 2, -4378.69, 6679.56, -29.7449, 0, 0, 0),
(@GUID, 3, -4377.48, 6678.66, -29.6055, 0, 0, 0),
(@GUID, 4, -4377.48, 6678.66, -29.6055, 0, 0, 0);

SET @GUID=270641;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4443.6, 6620.92, -25.1679, 0, 0, 0),
(@GUID, 1, -4442.98, 6621.71, -25.1679, 0, 0, 0),
(@GUID, 2, -4448.9, 6616.32, -24.5429, 0, 0, 0),
(@GUID, 3, -4455.73, 6610.11, -24.2929, 0, 0, 0),
(@GUID, 4, -4455.73, 6610.11, -24.2929, 0, 0, 0);

SET @GUID=270642;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4347.22, 6714.79, -24.7537, 0, 0, 0),
(@GUID, 1, -4346.49, 6714.11, -24.7537, 0, 0, 0),
(@GUID, 2, -4345.51, 6716.77, -25.3688, 0, 0, 0),
(@GUID, 3, -4345.51, 6716.77, -25.3688, 0, 0, 0);

SET @GUID=270662;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4183.07, 6715.08, -9.43399, 0, 0, 0),
(@GUID, 1, -4184.06, 6715.25, -9.43399, 0, 0, 0),
(@GUID, 2, -4183.3, 6713.4, -8.68399, 0, 0, 0),
(@GUID, 3, -4182.17, 6710.62, -7.80899, 0, 0, 0),
(@GUID, 4, -4181.42, 6708.76, -6.93399, 0, 0, 0),
(@GUID, 5, -4180.66, 6706.91, -6.05899, 0, 0, 0),
(@GUID, 6, -4180.29, 6705.98, -5.43399, 0, 0, 0),
(@GUID, 7, -4179.91, 6705.06, -4.68399, 0, 0, 0),
(@GUID, 8, -4179.91, 6705.06, -4.68399, 0, 0, 0);

SET @GUID=270664;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4251.45, 6714.73, -3.48509, 0, 0, 0),
(@GUID, 1, -4252.38, 6714.36, -3.48509, 0, 0, 0),
(@GUID, 2, -4263.31, 6715.45, -2.86009, 0, 0, 0),
(@GUID, 3, -4263.31, 6715.45, -2.86009, 0, 0, 0);

SET @GUID=270680;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4218.07, 6706.3, -2.7498, 0, 0, 0),
(@GUID, 1, -4218.63, 6707.12, -2.7498, 0, 0, 0),
(@GUID, 2, -4217.19, 6703.39, -1.3748, 0, 0, 0),
(@GUID, 3, -4216.48, 6701.52, -0.7498, 0, 0, 0),
(@GUID, 4, -4215.76, 6699.66, -0.00502, 0, 0, 0),
(@GUID, 5, -4214.68, 6696.86, 0.61998, 0, 0, 0),
(@GUID, 6, -4213.46, 6693.7, 1.0587, 0, 0, 0),
(@GUID, 7, -4213.46, 6693.7, 1.0587, 0, 0, 0);

SET @GUID=270674;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4414.27, 5887.89, 0.38087, 0, 0, 0),
(@GUID, 1, -4415.22, 5888.21, 0.38087, 0, 0, 0),
(@GUID, 2, -4408.22, 5888.07, 1.00587, 0, 0, 0),
(@GUID, 3, -4404.54, 5888, 1.13087, 0, 0, 0),
(@GUID, 4, -4404.54, 5888, 1.13087, 0, 0, 0);

SET @GUID=270665;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4514.96, 6316.29, -12.8193, 0, 0, 0),
(@GUID, 1, -4514.03, 6316.66, -12.8193, 0, 0, 0),
(@GUID, 2, -4524.31, 6328, -12.3395, 0, 0, 0),
(@GUID, 3, -4524.31, 6328, -12.3395, 0, 0, 0);

SET @GUID=270673;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -3956.42, 6746.1, 4.76493, 0, 0, 0),
(@GUID, 1, -3956.74, 6745.15, 4.76493, 0, 0, 0),
(@GUID, 2, -3957.38, 6743.26, 5.51493, 0, 0, 0),
(@GUID, 3, -3958.02, 6741.37, 6.26493, 0, 0, 0),
(@GUID, 4, -3958.71, 6739.35, 6.46354, 0, 0, 0),
(@GUID, 5, -3958.71, 6739.35, 6.46354, 0, 0, 0);

SET @GUID=270622;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4448.35, 6293.07, -5.20237, 0, 0, 0),
(@GUID, 1, -4447.59, 6293.72, -5.20237, 0, 0, 0),
(@GUID, 2, -4446.71, 6293.24, -4.32737, 0, 0, 0),
(@GUID, 3, -4444.09, 6291.78, -3.07737, 0, 0, 0),
(@GUID, 4, -4442.34, 6290.81, -1.95237, 0, 0, 0),
(@GUID, 5, -4440.59, 6289.84, -1.32737, 0, 0, 0),
(@GUID, 6, -4438.42, 6288.63, -1.12474, 0, 0, 0),
(@GUID, 7, -4438.42, 6288.63, -1.12474, 0, 0, 0),
(@GUID, 8, -4446.03, 6288.28, -4.82737, 0, 0, 0),
(@GUID, 9, -4445.04, 6288.41, -4.07737, 0, 0, 0),
(@GUID, 10, -4444.04, 6288.54, -3.45237, 0, 0, 0),
(@GUID, 11, -4443.05, 6288.66, -2.70237, 0, 0, 0),
(@GUID, 12, -4442.06, 6288.79, -2.07737, 0, 0, 0),
(@GUID, 13, -4440.07, 6289.05, -1.45237, 0, 0, 0),
(@GUID, 14, -4435.42, 6289.66, -0.89061, 0, 0, 0),
(@GUID, 15, -4435.42, 6289.66, -0.89061, 0, 0, 0);

SET @GUID=270614;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4440.76, 6246.04, -2.07595, 0, 0, 0),
(@GUID, 1, -4440.86, 6247.04, -2.07595, 0, 0, 0),
(@GUID, 2, -4442.81, 6247.51, -3.32595, 0, 0, 0),
(@GUID, 3, -4443.78, 6247.74, -4.07595, 0, 0, 0),
(@GUID, 4, -4445.73, 6248.21, -4.70095, 0, 0, 0),
(@GUID, 5, -4446.39, 6248.37, -5.62453, 0, 0, 0),
(@GUID, 6, -4446.39, 6248.37, -5.62453, 0, 0, 0);

SET @GUID=270613;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4514.92, 6253.71, -13.2579, 0, 0, 0),
(@GUID, 1, -4514.27, 6252.96, -13.2579, 0, 0, 0),
(@GUID, 2, -4513.15, 6241.33, -12.905, 0, 0, 0),
(@GUID, 3, -4513.15, 6241.33, -12.905, 0, 0, 0);

SET @GUID=270670;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -3648.92, 6644.36, 5.55097, 0, 0, 0),
(@GUID, 1, -3649.92, 6644.4, 5.55097, 0, 0, 0),
(@GUID, 2, -3648.93, 6644.29, 4.92597, 0, 0, 0),
(@GUID, 3, -3646.94, 6644.06, 4.30097, 0, 0, 0),
(@GUID, 4, -3645.94, 6643.95, 3.67597, 0, 0, 0),
(@GUID, 5, -3644.95, 6643.84, 3.05097, 0, 0, 0),
(@GUID, 6, -3643.96, 6643.73, 2.42597, 0, 0, 0),
(@GUID, 7, -3642.96, 6643.61, 1.80097, 0, 0, 0),
(@GUID, 8, -3640.97, 6643.38, 0.67597, 0, 0, 0),
(@GUID, 9, -3638.98, 6643.16, -0.44903, 0, 0, 0),
(@GUID, 10, -3637.99, 6643.04, -1.07403, 0, 0, 0),
(@GUID, 11, -3637, 6642.93, -1.82403, 0, 0, 0),
(@GUID, 12, -3636.57, 6642.88, -2.32892, 0, 0, 0),
(@GUID, 13, -3636.57, 6642.88, -2.32892, 0, 0, 0);

SET @GUID=270683;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -3981.91, 6784.32, -19.2372, 0, 0, 0),
(@GUID, 1, -3980.99, 6783.93, -19.2372, 0, 0, 0),
(@GUID, 2, -3979.58, 6787.67, -19.9872, 0, 0, 0),
(@GUID, 3, -3975.7, 6798.05, -20.4621, 0, 0, 0),
(@GUID, 4, -3975.7, 6798.05, -20.4621, 0, 0, 0);

SET @GUID=270681;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4479.24, 6446.92, -14.1006, 0, 0, 0),
(@GUID, 1, -4478.24, 6446.94, -14.1006, 0, 0, 0),
(@GUID, 2, -4484.83, 6449.32, -14.7256, 0, 0, 0),
(@GUID, 3, -4497.07, 6453.74, -15.3506, 0, 0, 0),
(@GUID, 4, -4497.5, 6453.89, -15.3804, 0, 0, 0),
(@GUID, 5, -4497.5, 6453.89, -15.3804, 0, 0, 0);

SET @GUID=270601;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4391.41, 6588.23, 4.16529, 0, 0, 0),
(@GUID, 1, -4390.42, 6588.07, 4.16529, 0, 0, 0),
(@GUID, 2, -4400.55, 6581.63, 3.38399, 0, 0, 0),
(@GUID, 3, -4403.54, 6579.72, 2.91145, 0, 0, 0),
(@GUID, 4, -4403.54, 6579.72, 2.91145, 0, 0, 0);

SET @GUID=270618;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4440.49, 6454.95, 3.4717, 0, 0, 0),
(@GUID, 1, -4440.11, 6455.87, 3.4717, 0, 0, 0),
(@GUID, 2, -4438.11, 6455.77, 4.2217, 0, 0, 0),
(@GUID, 3, -4436.12, 6455.67, 4.9717, 0, 0, 0),
(@GUID, 4, -4434.12, 6455.57, 5.5967, 0, 0, 0),
(@GUID, 5, -4432.12, 6455.48, 6.17575, 0, 0, 0),
(@GUID, 6, -4430.13, 6455.38, 6.80075, 0, 0, 0),
(@GUID, 7, -4428.92, 6455.31, 7.07614, 0, 0, 0),
(@GUID, 8, -4428.92, 6455.31, 7.07614, 0, 0, 0);

SET @GUID=270625;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4214.73, 5811.52, 5.03802, 0, 0, 0),
(@GUID, 1, -4213.83, 5811.09, 5.03802, 0, 0, 0),
(@GUID, 2, -4219.66, 5812.48, 4.28802, 0, 0, 0),
(@GUID, 3, -4223.55, 5813.42, 3.85821, 0, 0, 0),
(@GUID, 4, -4223.55, 5813.42, 3.85821, 0, 0, 0);

SET @GUID=270615;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4481.86, 6285.76, -14.9924, 0, 0, 0),
(@GUID, 1, -4482.63, 6285.12, -14.9924, 0, 0, 0),
(@GUID, 2, -4479.46, 6281.2, -14.9924, 0, 0, 0),
(@GUID, 3, -4479.46, 6281.2, -14.9924, 0, 0, 0);

SET @GUID=270627;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4493.37, 6363.58, -14.8625, 0, 0, 0),
(@GUID, 1, -4493.55, 6364.56, -14.8625, 0, 0, 0),
(@GUID, 2, -4487.15, 6351.58, -14.9875, 0, 0, 0),
(@GUID, 3, -4487.15, 6351.58, -14.9875, 0, 0, 0);

SET @GUID=270790;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4008.83, 6640.63, 14.4554, 0, 0, 0),
(@GUID, 1, -4009.74, 6641.03, 14.4554, 0, 0, 0),
(@GUID, 2, -4017.96, 6644.69, 14.3304, 0, 0, 0),
(@GUID, 3, -4017.96, 6644.69, 14.3304, 0, 0, 0);

SET @GUID=270791;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4282.97, 6067.85, 24.6405, 0, 0, 0),
(@GUID, 1, -4283.42, 6066.96, 24.6405, 0, 0, 0),
(@GUID, 2, -4284.31, 6065.17, 25.2916, 0, 0, 0),
(@GUID, 3, -4284.75, 6064.27, 26.0416, 0, 0, 0),
(@GUID, 4, -4285.64, 6062.48, 27.1666, 0, 0, 0),
(@GUID, 5, -4286.53, 6060.69, 27.9166, 0, 0, 0),
(@GUID, 6, -4287.19, 6059.35, 28.5612, 0, 0, 0),
(@GUID, 7, -4287.19, 6059.35, 28.5612, 0, 0, 0);

SET @GUID=270795;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4229, 6390.46, 13.2042, 0, 0, 0),
(@GUID, 1, -4229.71, 6391.17, 13.2042, 0, 0, 0),
(@GUID, 2, -4232.39, 6393.06, 13.2042, 0, 0, 0),
(@GUID, 3, -4232.39, 6393.06, 13.2042, 0, 0, 0);

SET @GUID=270794;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4158.15, 6463.14, 16.4918, 0, 0, 0),
(@GUID, 1, -4157.76, 6464.06, 16.4918, 0, 0, 0),
(@GUID, 2, -4157.85, 6466.63, 16.626, 0, 0, 0),
(@GUID, 3, -4157.85, 6466.63, 16.626, 0, 0, 0),
(@GUID, 4, -4167.58, 6507.66, 14.2434, 0, 0, 0);

SET @GUID=270792;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4190.2, 6009.53, 102.299, 0, 0, 0),
(@GUID, 1, -4190.63, 6010.43, 102.299, 0, 0, 0),
(@GUID, 2, -4188.91, 6002.62, 103.174, 0, 0, 0),
(@GUID, 3, -4188.27, 5999.69, 103.822, 0, 0, 0),
(@GUID, 4, -4186.12, 5989.92, 104.447, 0, 0, 0),
(@GUID, 5, -4183.79, 5979.35, 104.657, 0, 0, 0),
(@GUID, 6, -4183.79, 5979.35, 104.657, 0, 0, 0);

SET @GUID=270793;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -3730.27, 6675.83, 12.6952, 0, 0, 0),
(@GUID, 1, -3729.51, 6675.19, 12.6952, 0, 0, 0),
(@GUID, 2, -3722.69, 6669.33, 12.9452, 0, 0, 0),
(@GUID, 3, -3722.69, 6669.33, 12.9452, 0, 0, 0);

SET @GUID=270510;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4331.73, 6203.62, 13.2417, 0, 0, 0),
(@GUID, 1, -4330.73, 6203.65, 13.2417, 0, 0, 0),
(@GUID, 2, -4332.6, 6203.46, 13.2417, 0, 0, 0),
(@GUID, 3, -4332.6, 6203.46, 13.2417, 0, 0, 0);

SET @GUID=270512;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4335.67, 6222.15, 13.2417, 0, 0, 0),
(@GUID, 1, -4336.66, 6222.26, 13.2417, 0, 0, 0),
(@GUID, 2, -4337.64, 6222.66, 13.2417, 0, 0, 0),
(@GUID, 3, -4337.64, 6222.66, 13.2417, 0, 0, 0);

SET @GUID=270511;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4353.18, 6206.85, 13.2417, 0, 0, 0),
(@GUID, 1, -4352.21, 6206.63, 13.2417, 0, 0, 0),
(@GUID, 2, -4353.02, 6207, 13.2417, 0, 0, 0),
(@GUID, 3, -4353.02, 6207, 13.2417, 0, 0, 0);

SET @GUID=270356;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4348.16, 6224.58, 13.2417, 0, 0, 0),
(@GUID, 1, -4347.35, 6224.01, 13.2417, 0, 0, 0),
(@GUID, 2, -4349.31, 6222.27, 13.2417, 0, 0, 0),
(@GUID, 3, -4349.31, 6222.27, 13.2417, 0, 0, 0);

SET @GUID=270692;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4282.12, 6269.06, 13.225, 0, 0, 0),
(@GUID, 1, -4282.13, 6268.06, 13.225, 0, 0, 0),
(@GUID, 2, -4282.04, 6269.9, 13.225, 0, 0, 0),
(@GUID, 3, -4282.04, 6269.9, 13.225, 0, 0, 0);

SET @GUID=270686;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4285.22, 6223.84, 19.3072, 0, 0, 0),
(@GUID, 1, -4284.23, 6223.97, 19.3072, 0, 0, 0),
(@GUID, 2, -4287.61, 6226.11, 18.0572, 0, 0, 0),
(@GUID, 3, -4288.17, 6226.47, 18.0847, 0, 0, 0),
(@GUID, 4, -4288.17, 6226.47, 18.0847, 0, 0, 0);

SET @GUID=270687;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4305.06, 6165.85, 13.201, 0, 0, 0),
(@GUID, 1, -4304.1, 6165.55, 13.201, 0, 0, 0),
(@GUID, 2, -4307.29, 6167.71, 13.2409, 0, 0, 0),
(@GUID, 3, -4307.29, 6167.71, 13.2409, 0, 0, 0);

SET @GUID=270688;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4306.34, 6242.99, 15.3171, 0, 0, 0),
(@GUID, 1, -4307.03, 6242.26, 15.3171, 0, 0, 0),
(@GUID, 2, -4306.77, 6246.35, 15.8171, 0, 0, 0),
(@GUID, 3, -4306.77, 6246.35, 15.8171, 0, 0, 0);

SET @GUID=270685;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4256.37, 6291.05, 13.7463, 0, 0, 0),
(@GUID, 1, -4257.37, 6290.97, 13.7463, 0, 0, 0),
(@GUID, 2, -4258.33, 6290.63, 13.6, 0, 0, 0),
(@GUID, 3, -4258.92, 6288.28, 13.5843, 0, 0, 0),
(@GUID, 4, -4258.92, 6288.28, 13.5843, 0, 0, 0);

SET @GUID=270693;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4256.78, 6293.62, 13.725, 0, 0, 0),
(@GUID, 1, -4256.18, 6292.82, 13.725, 0, 0, 0),
(@GUID, 2, -4255.74, 6291.13, 13.7268, 0, 0, 0),
(@GUID, 3, -4255.74, 6291.13, 13.7268, 0, 0, 0);

SET @GUID=270499;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4144.85, 6308.92, 13.1739, 0, 0, 0),
(@GUID, 1, -4144.61, 6307.95, 13.1739, 0, 0, 0),
(@GUID, 2, -4144.43, 6307.2, 13.1739, 0, 0, 0),
(@GUID, 3, -4143.35, 6309.35, 13.1739, 0, 0, 0),
(@GUID, 4, -4141.93, 6312.54, 13.1739, 0, 0, 0),
(@GUID, 5, -4141.93, 6312.54, 13.1739, 0, 0, 0);

SET @GUID=270500;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4133.41, 6294.24, 13.1168, 0, 0, 0),
(@GUID, 1, -4132.54, 6294.74, 13.1168, 0, 0, 0),
(@GUID, 2, -4134.82, 6293.96, 13.1168, 0, 0, 0),
(@GUID, 3, -4136.81, 6293.94, 13.1168, 0, 0, 0),
(@GUID, 4, -4139.58, 6294.63, 13.1168, 0, 0, 0),
(@GUID, 5, -4141.24, 6295.32, 13.1456, 0, 0, 0),
(@GUID, 6, -4144.01, 6296.85, 13.1293, 0, 0, 0),
(@GUID, 7, -4145.52, 6298.58, 13.1168, 0, 0, 0),
(@GUID, 8, -4145.52, 6298.58, 13.1168, 0, 0, 0);

SET @GUID=270496;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4140.48, 6294.04, 13.2417, 0, 0, 0),
(@GUID, 1, -4139.56, 6293.67, 13.2417, 0, 0, 0),
(@GUID, 2, -4138.88, 6293.39, 13.1276, 0, 0, 0),
(@GUID, 3, -4136.98, 6293.25, 13.1168, 0, 0, 0),
(@GUID, 4, -4134.35, 6293.69, 13.1168, 0, 0, 0),
(@GUID, 5, -4132.54, 6294.74, 13.1168, 0, 0, 0),
(@GUID, 6, -4132.54, 6294.74, 13.1168, 0, 0, 0);

SET @GUID=270497;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4145.48, 6314.67, 13.1739, 0, 0, 0),
(@GUID, 1, -4145.94, 6313.78, 13.1739, 0, 0, 0),
(@GUID, 2, -4147.2, 6311.33, 13.1739, 0, 0, 0),
(@GUID, 3, -4147.64, 6308.77, 13.1739, 0, 0, 0),
(@GUID, 4, -4147.64, 6308.77, 13.1739, 0, 0, 0);

SET @GUID=270445;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4185.65, 6241.73, 13.2417, 0, 0, 0),
(@GUID, 1, -4186.58, 6241.35, 13.2417, 0, 0, 0),
(@GUID, 2, -4195.83, 6237.55, 13.2417, 0, 0, 0),
(@GUID, 3, -4195.83, 6237.55, 13.2417, 0, 0, 0);

SET @GUID=270443;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4185.59, 6241.46, 13.2417, 0, 0, 0),
(@GUID, 1, -4186.58, 6241.35, 13.2417, 0, 0, 0),
(@GUID, 2, -4196.52, 6240.22, 13.2417, 0, 0, 0),
(@GUID, 3, -4196.52, 6240.22, 13.2417, 0, 0, 0);

SET @GUID=270448;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4223.74, 6227.55, 13.2584, 0, 0, 0),
(@GUID, 1, -4222.86, 6228.03, 13.2584, 0, 0, 0),
(@GUID, 2, -4214.07, 6232.79, 13.1334, 0, 0, 0),
(@GUID, 3, -4214.07, 6232.79, 13.1334, 0, 0, 0);

SET @GUID=270503;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4134.57, 6298.01, 13.2001, 0, 0, 0),
(@GUID, 1, -4135.57, 6297.96, 13.2001, 0, 0, 0),
(@GUID, 2, -4137.04, 6297.88, 13.1168, 0, 0, 0),
(@GUID, 3, -4139.61, 6298.29, 13.1168, 0, 0, 0),
(@GUID, 4, -4141.69, 6298.68, 13.1168, 0, 0, 0),
(@GUID, 5, -4143.64, 6299.9, 13.1168, 0, 0, 0),
(@GUID, 6, -4144.88, 6302.24, 13.1168, 0, 0, 0),
(@GUID, 7, -4145.34, 6304.31, 13.1168, 0, 0, 0),
(@GUID, 8, -4144.26, 6307.38, 13.1168, 0, 0, 0),
(@GUID, 9, -4142.75, 6309.9, 13.1168, 0, 0, 0),
(@GUID, 10, -4141.9, 6312.75, 13.1168, 0, 0, 0),
(@GUID, 11, -4139.56, 6314.34, 13.1168, 0, 0, 0),
(@GUID, 12, -4137.03, 6315.31, 13.1168, 0, 0, 0),
(@GUID, 13, -4133.43, 6315.82, 13.1168, 0, 0, 0),
(@GUID, 14, -4130.7, 6315.42, 13.1168, 0, 0, 0),
(@GUID, 15, -4129.55, 6312.52, 13.1168, 0, 0, 0),
(@GUID, 16, -4129.5, 6309.89, 13.1168, 0, 0, 0),
(@GUID, 17, -4129.41, 6306.67, 13.1168, 0, 0, 0),
(@GUID, 18, -4129.29, 6302.96, 13.1168, 0, 0, 0),
(@GUID, 19, -4130.25, 6300.81, 13.1168, 0, 0, 0),
(@GUID, 20, -4132.23, 6298.95, 13.1168, 0, 0, 0),
(@GUID, 21, -4134.29, 6298.37, 13.1168, 0, 0, 0),
(@GUID, 22, -4134.29, 6298.37, 13.1168, 0, 0, 0);

SET @GUID=270502;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4134.57, 6298.01, 13.2001, 0, 0, 0),
(@GUID, 1, -4135.57, 6297.96, 13.2001, 0, 0, 0),
(@GUID, 2, -4137.04, 6297.88, 13.1168, 0, 0, 0),
(@GUID, 3, -4139.61, 6298.29, 13.1168, 0, 0, 0),
(@GUID, 4, -4141.69, 6298.68, 13.1168, 0, 0, 0),
(@GUID, 5, -4143.64, 6299.9, 13.1168, 0, 0, 0),
(@GUID, 6, -4144.88, 6302.24, 13.1168, 0, 0, 0),
(@GUID, 7, -4145.34, 6304.31, 13.1168, 0, 0, 0),
(@GUID, 8, -4144.26, 6307.38, 13.1168, 0, 0, 0),
(@GUID, 9, -4142.75, 6309.9, 13.1168, 0, 0, 0),
(@GUID, 10, -4141.9, 6312.75, 13.1168, 0, 0, 0),
(@GUID, 11, -4139.56, 6314.34, 13.1168, 0, 0, 0),
(@GUID, 12, -4137.03, 6315.31, 13.1168, 0, 0, 0),
(@GUID, 13, -4133.43, 6315.82, 13.1168, 0, 0, 0),
(@GUID, 14, -4130.7, 6315.42, 13.1168, 0, 0, 0),
(@GUID, 15, -4129.55, 6312.52, 13.1168, 0, 0, 0),
(@GUID, 16, -4129.5, 6309.89, 13.1168, 0, 0, 0),
(@GUID, 17, -4129.41, 6306.67, 13.1168, 0, 0, 0),
(@GUID, 18, -4129.29, 6302.96, 13.1168, 0, 0, 0),
(@GUID, 19, -4130.25, 6300.81, 13.1168, 0, 0, 0),
(@GUID, 20, -4132.23, 6298.95, 13.1168, 0, 0, 0),
(@GUID, 21, -4134.29, 6298.37, 13.1168, 0, 0, 0),
(@GUID, 22, -4134.29, 6298.37, 13.1168, 0, 0, 0);

SET @GUID=270505;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4134.57, 6298.01, 13.2001, 0, 0, 0),
(@GUID, 1, -4135.57, 6297.96, 13.2001, 0, 0, 0),
(@GUID, 2, -4137.04, 6297.88, 13.1168, 0, 0, 0),
(@GUID, 3, -4139.61, 6298.29, 13.1168, 0, 0, 0),
(@GUID, 4, -4141.69, 6298.68, 13.1168, 0, 0, 0),
(@GUID, 5, -4143.64, 6299.9, 13.1168, 0, 0, 0),
(@GUID, 6, -4144.88, 6302.24, 13.1168, 0, 0, 0),
(@GUID, 7, -4145.34, 6304.31, 13.1168, 0, 0, 0),
(@GUID, 8, -4144.26, 6307.38, 13.1168, 0, 0, 0),
(@GUID, 9, -4142.75, 6309.9, 13.1168, 0, 0, 0),
(@GUID, 10, -4141.9, 6312.75, 13.1168, 0, 0, 0),
(@GUID, 11, -4139.56, 6314.34, 13.1168, 0, 0, 0),
(@GUID, 12, -4137.03, 6315.31, 13.1168, 0, 0, 0),
(@GUID, 13, -4133.43, 6315.82, 13.1168, 0, 0, 0),
(@GUID, 14, -4130.7, 6315.42, 13.1168, 0, 0, 0),
(@GUID, 15, -4129.55, 6312.52, 13.1168, 0, 0, 0),
(@GUID, 16, -4129.5, 6309.89, 13.1168, 0, 0, 0),
(@GUID, 17, -4129.41, 6306.67, 13.1168, 0, 0, 0),
(@GUID, 18, -4129.29, 6302.96, 13.1168, 0, 0, 0),
(@GUID, 19, -4130.25, 6300.81, 13.1168, 0, 0, 0),
(@GUID, 20, -4132.23, 6298.95, 13.1168, 0, 0, 0),
(@GUID, 21, -4134.29, 6298.37, 13.1168, 0, 0, 0),
(@GUID, 22, -4134.29, 6298.37, 13.1168, 0, 0, 0);

SET @GUID=270504;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4134.57, 6298.01, 13.2001, 0, 0, 0),
(@GUID, 1, -4135.57, 6297.96, 13.2001, 0, 0, 0),
(@GUID, 2, -4137.04, 6297.88, 13.1168, 0, 0, 0),
(@GUID, 3, -4139.61, 6298.29, 13.1168, 0, 0, 0),
(@GUID, 4, -4141.69, 6298.68, 13.1168, 0, 0, 0),
(@GUID, 5, -4143.64, 6299.9, 13.1168, 0, 0, 0),
(@GUID, 6, -4144.88, 6302.24, 13.1168, 0, 0, 0),
(@GUID, 7, -4145.34, 6304.31, 13.1168, 0, 0, 0),
(@GUID, 8, -4144.26, 6307.38, 13.1168, 0, 0, 0),
(@GUID, 9, -4142.75, 6309.9, 13.1168, 0, 0, 0),
(@GUID, 10, -4141.9, 6312.75, 13.1168, 0, 0, 0),
(@GUID, 11, -4139.56, 6314.34, 13.1168, 0, 0, 0),
(@GUID, 12, -4137.03, 6315.31, 13.1168, 0, 0, 0),
(@GUID, 13, -4133.43, 6315.82, 13.1168, 0, 0, 0),
(@GUID, 14, -4130.7, 6315.42, 13.1168, 0, 0, 0),
(@GUID, 15, -4129.55, 6312.52, 13.1168, 0, 0, 0),
(@GUID, 16, -4129.5, 6309.89, 13.1168, 0, 0, 0),
(@GUID, 17, -4129.41, 6306.67, 13.1168, 0, 0, 0),
(@GUID, 18, -4129.29, 6302.96, 13.1168, 0, 0, 0),
(@GUID, 19, -4130.25, 6300.81, 13.1168, 0, 0, 0),
(@GUID, 20, -4132.23, 6298.95, 13.1168, 0, 0, 0),
(@GUID, 21, -4134.29, 6298.37, 13.1168, 0, 0, 0),
(@GUID, 22, -4134.29, 6298.37, 13.1168, 0, 0, 0);

SET @GUID=270699;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4308.98, 6338.68, 9.74605, 0, 0, 0),
(@GUID, 1, -4309.97, 6338.78, 9.74605, 0, 0, 0),
(@GUID, 2, -4314.07, 6338.64, 9.74605, 0, 0, 0),
(@GUID, 3, -4314.07, 6338.64, 9.74605, 0, 0, 0);

SET @GUID=270490;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4068.89, 6293.57, 13.0844, 0, 0, 0),
(@GUID, 1, -4068.28, 6294.36, 13.0844, 0, 0, 0),
(@GUID, 2, -4066.15, 6297.14, 12.812, 0, 0, 0),
(@GUID, 3, -4068.99, 6303.69, 12.5765, 0, 0, 0),
(@GUID, 4, -4068.99, 6303.69, 12.5765, 0, 0, 0);

SET @GUID=270550;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4255.19, 6328.58, 10.9564, 0, 0, 0),
(@GUID, 1, -4255.46, 6327.61, 10.9564, 0, 0, 0),
(@GUID, 2, -4255.98, 6325.71, 11.326, 0, 0, 0),
(@GUID, 3, -4256.13, 6325.12, 11.3743, 0, 0, 0),
(@GUID, 4, -4263.95, 6321.72, 11.0838, 0, 0, 0),
(@GUID, 5, -4263.95, 6321.72, 11.0838, 0, 0, 0);

SET @GUID=270551;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4255.71, 6326.68, 11.326, 0, 0, 0),
(@GUID, 1, -4255.98, 6325.71, 11.326, 0, 0, 0),
(@GUID, 2, -4259.34, 6323.72, 11.449, 0, 0, 0),
(@GUID, 3, -4259.34, 6323.72, 11.449, 0, 0, 0);

SET @GUID=270552;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4253.25, 6329.1, 10.701, 0, 0, 0),
(@GUID, 1, -4253.52, 6328.14, 10.701, 0, 0, 0),
(@GUID, 2, -4254.85, 6325.45, 11.326, 0, 0, 0),
(@GUID, 3, -4255.9, 6323.33, 11.8313, 0, 0, 0),
(@GUID, 4, -4255.9, 6323.33, 11.8313, 0, 0, 0);

SET @GUID=270553;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4256.59, 6330.02, 10.576, 0, 0, 0),
(@GUID, 1, -4256.85, 6329.05, 10.576, 0, 0, 0),
(@GUID, 2, -4257.28, 6326.51, 10.9576, 0, 0, 0),
(@GUID, 3, -4257.28, 6326.51, 10.9576, 0, 0, 0);

SET @GUID=270543;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4048.59, 6298.66, 10.1572, 0, 0, 0),
(@GUID, 1, -4049.24, 6299.43, 10.1572, 0, 0, 0),
(@GUID, 2, -4056.23, 6307.76, 10.1183, 0, 0, 0),
(@GUID, 3, -4072.18, 6323.65, 9.85196, 0, 0, 0),
(@GUID, 4, -4072.18, 6323.65, 9.85196, 0, 0, 0),
(@GUID, 5, -4072, 6332.86, 9.99881, 0, 0, 0);

SET @GUID=270542;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4050.06, 6300.22, 10.1183, 0, 0, 0),
(@GUID, 1, -4050.55, 6301.09, 10.1183, 0, 0, 0),
(@GUID, 2, -4060.59, 6318.32, 10.1183, 0, 0, 0),
(@GUID, 3, -4060.59, 6318.32, 10.1183, 0, 0, 0);

SET @GUID=270544;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4051.73, 6299.22, 10.1183, 0, 0, 0),
(@GUID, 1, -4052.19, 6300.1, 10.1183, 0, 0, 0),
(@GUID, 2, -4063.41, 6316.45, 10.1183, 0, 0, 0),
(@GUID, 3, -4063.41, 6316.45, 10.1183, 0, 0, 0);

SET @GUID=270545;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4051.41, 6300.68, 10.1183, 0, 0, 0),
(@GUID, 1, -4052.07, 6301.43, 10.1183, 0, 0, 0),
(@GUID, 2, -4058.74, 6311.02, 10.1183, 0, 0, 0),
(@GUID, 3, -4058.74, 6311.02, 10.1183, 0, 0, 0);

SET @GUID=270518;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4346.54, 6202.79, 13.2417, 0, 0, 0),
(@GUID, 1, -4347.03, 6201.92, 13.2417, 0, 0, 0),
(@GUID, 2, -4346.17, 6202.42, 13.2417, 0, 0, 0),
(@GUID, 3, -4346.17, 6202.42, 13.2417, 0, 0, 0);

SET @GUID=270424;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4297.52, 6296.69, 13.225, 0, 0, 0),
(@GUID, 1, -4296.59, 6297.06, 13.225, 0, 0, 0),
(@GUID, 2, -4296.95, 6296.83, 13.225, 0, 0, 0),
(@GUID, 3, -4296.95, 6296.83, 13.225, 0, 0, 0);

SET @GUID=270591;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4351.05, 6255.72, 13.2417, 0, 0, 0),
(@GUID, 1, -4352.05, 6255.72, 13.2417, 0, 0, 0),
(@GUID, 2, -4350.28, 6257.93, 13.2417, 0, 0, 0),
(@GUID, 3, -4351.92, 6260.61, 13.2417, 0, 0, 0),
(@GUID, 4, -4351.92, 6260.61, 13.2417, 0, 0, 0);

SET @GUID=270546;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4376.74, 6332.16, 11.1699, 0, 0, 0),
(@GUID, 1, -4375.77, 6332.38, 11.1699, 0, 0, 0),
(@GUID, 2, -4374.3, 6332.72, 11.1302, 0, 0, 0),
(@GUID, 3, -4361.63, 6335.66, 10.496, 0, 0, 0),
(@GUID, 4, -4360, 6336.04, 10.3828, 0, 0, 0),
(@GUID, 5, -4360, 6336.04, 10.3828, 0, 0, 0);

SET @GUID=270547;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4374.81, 6332.6, 11.0265, 0, 0, 0),
(@GUID, 1, -4373.83, 6332.83, 11.0265, 0, 0, 0),
(@GUID, 2, -4369.79, 6333.77, 10.7765, 0, 0, 0),
(@GUID, 3, -4369.79, 6333.77, 10.7765, 0, 0, 0);

SET @GUID=270707;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4310.47, 6336.72, 9.78916, 0, 0, 0),
(@GUID, 1, -4309.47, 6336.78, 9.78916, 0, 0, 0),
(@GUID, 2, -4305.31, 6337.03, 9.86471, 0, 0, 0),
(@GUID, 3, -4287.98, 6333.47, 9.74605, 0, 0, 0),
(@GUID, 4, -4287.98, 6333.47, 9.74605, 0, 0, 0);

SET @GUID=270703;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4378.02, 6311.7, 13.1515, 0, 0, 0),
(@GUID, 1, -4377.13, 6311.25, 13.1515, 0, 0, 0),
(@GUID, 2, -4375.4, 6310.36, 13.1515, 0, 0, 0),
(@GUID, 3, -4371.68, 6305.8, 13.1515, 0, 0, 0),
(@GUID, 4, -4371.68, 6305.8, 13.1515, 0, 0, 0);

SET @GUID=270714;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4132.33, 6360.83, 9.91336, 0, 0, 0),
(@GUID, 1, -4133.27, 6361.2, 9.91336, 0, 0, 0),
(@GUID, 2, -4137.44, 6362.85, 9.92992, 0, 0, 0),
(@GUID, 3, -4163.21, 6362.7, 9.82592, 0, 0, 0),
(@GUID, 4, -4163.21, 6362.7, 9.82592, 0, 0, 0);

SET @GUID=270716;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4255.1, 6334.29, 9.88288, 0, 0, 0),
(@GUID, 1, -4254.1, 6334.31, 9.88288, 0, 0, 0),
(@GUID, 2, -4252.29, 6334.36, 9.89016, 0, 0, 0),
(@GUID, 3, -4221.84, 6336.78, 10.3499, 0, 0, 0),
(@GUID, 4, -4221.84, 6336.78, 10.3499, 0, 0, 0);

SET @GUID=270717;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4340.67, 6209.85, 13.2417, 0, 0, 0),
(@GUID, 1, -4341.53, 6210.36, 13.2417, 0, 0, 0),
(@GUID, 2, -4344.52, 6213.33, 13.2417, 0, 0, 0),
(@GUID, 3, -4344.52, 6213.33, 13.2417, 0, 0, 0);

SET @GUID=270541;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4078.72, 6330.35, 9.841, 0, 0, 0),
(@GUID, 1, -4079.42, 6331.07, 9.841, 0, 0, 0),
(@GUID, 2, -4089.36, 6341.26, 9.82596, 0, 0, 0),
(@GUID, 3, -4092.45, 6349.71, 10.451, 0, 0, 0),
(@GUID, 4, -4093.48, 6352.53, 11.076, 0, 0, 0),
(@GUID, 5, -4093.62, 6352.91, 11.1378, 0, 0, 0),
(@GUID, 6, -4093.62, 6352.91, 11.1378, 0, 0, 0);

SET @GUID=270539;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4089.11, 6339.99, 9.82596, 0, 0, 0),
(@GUID, 1, -4089.85, 6340.67, 9.82596, 0, 0, 0),
(@GUID, 2, -4091.07, 6345.95, 10.0279, 0, 0, 0),
(@GUID, 3, -4091.07, 6345.95, 10.0279, 0, 0, 0);

SET @GUID=270540;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4086.41, 6339.65, 9.82596, 0, 0, 0),
(@GUID, 1, -4087.03, 6340.43, 9.82596, 0, 0, 0),
(@GUID, 2, -4092.13, 6349.03, 10.451, 0, 0, 0),
(@GUID, 3, -4094.68, 6353.33, 11.201, 0, 0, 0),
(@GUID, 4, -4096.72, 6356.78, 11.826, 0, 0, 0),
(@GUID, 5, -4099.25, 6361.03, 12.3279, 0, 0, 0),
(@GUID, 6, -4099.25, 6361.03, 12.3279, 0, 0, 0);

SET @GUID=270698;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4398.87, 6226.96, 13.2082, 0, 0, 0),
(@GUID, 1, -4399.38, 6227.82, 13.2082, 0, 0, 0),
(@GUID, 2, -4402.95, 6229.23, 13.1666, 0, 0, 0),
(@GUID, 3, -4402.95, 6229.23, 13.1666, 0, 0, 0);

SET @GUID=270710;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4216.64, 6352.29, 10.2044, 0, 0, 0),
(@GUID, 1, -4217.6, 6352, 10.2044, 0, 0, 0),
(@GUID, 2, -4219.05, 6351.56, 10.2007, 0, 0, 0),
(@GUID, 3, -4241.67, 6348.38, 10.444, 0, 0, 0),
(@GUID, 4, -4241.67, 6348.38, 10.444, 0, 0, 0);

SET @GUID=270388;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4353.86, 6336.85, 10.121, 0, 0, 0),
(@GUID, 1, -4352.87, 6336.98, 10.121, 0, 0, 0),
(@GUID, 2, -4348.77, 6337.52, 10.1815, 0, 0, 0),
(@GUID, 3, -4348.77, 6337.52, 10.1815, 0, 0, 0);

SET @GUID=270715;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4190.97, 6343.69, 9.9651, 0, 0, 0),
(@GUID, 1, -4189.99, 6343.91, 9.9651, 0, 0, 0),
(@GUID, 2, -4188.02, 6344.35, 9.94131, 0, 0, 0),
(@GUID, 3, -4160.38, 6346.62, 10.3301, 0, 0, 0),
(@GUID, 4, -4160.38, 6346.62, 10.3301, 0, 0, 0);

SET @GUID=270697;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4321.22, 6340.11, 9.99605, 0, 0, 0),
(@GUID, 1, -4320.22, 6340.11, 9.99605, 0, 0, 0),
(@GUID, 2, -4316.08, 6340.08, 9.74605, 0, 0, 0),
(@GUID, 3, -4316.08, 6340.08, 9.74605, 0, 0, 0);

SET @GUID=270789;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4231.6, 6392.72, 13.2042, 0, 0, 0),
(@GUID, 1, -4232.52, 6393.12, 13.2042, 0, 0, 0),
(@GUID, 2, -4235.39, 6395.78, 13.2415, 0, 0, 0),
(@GUID, 3, -4238.5, 6399.74, 13.2415, 0, 0, 0),
(@GUID, 4, -4238.5, 6399.74, 13.2415, 0, 0, 0);


