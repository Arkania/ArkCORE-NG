SET @GUID=147419;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay) values
(147419, 0, -139.1857, 291.6797, -46.13552, 2.697807, 3000),
(147419, 1, -131.5469, 283.4805, -45.80113, 5.47026, 0),
(147419, 2, -127.0603, 270.0887, -45.78556, 5.054001, 0),
(147419, 3, -123.2862, 261.6101, -47.63474, 5.156103, 0),
(147419, 4, -123.0917, 251.686, -48.4776, 4.731988, 3000),
(147419, 5, -123.2862, 261.6101, -47.63474, 5.156103, 0),
(147419, 6, -127.0603, 270.0887, -45.78556, 5.054001, 0),
(147419, 7, -131.5469, 283.4805, -45.80113, 5.47026, 0);
