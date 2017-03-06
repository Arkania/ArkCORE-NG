SET @GUID=147376;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay) values
(147376, 0, -122.5622, 249.8881, -48.4082, 1.771035, 3000),
(147376, 1, -133.2686, 233.056, -47.57782, 3.832703, 0),
(147376, 2, -127.7398, 228.1817, -48.04626, 5.548799, 3000),
(147376, 3, -133.2686, 233.056, -47.57782, 3.832703, 0);
