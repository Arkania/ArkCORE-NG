SET @GUID=147420;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay) values
(147420, 0, -80.61125, 372.0056, -45.83071, 4.716255, 3000),
(147420, 1, -74.68849, 376.4933, -46.97439, 0.506518, 0),
(147420, 2, -71.08943, 368.8929, -48.58848, 5.234616, 0),
(147420, 3, -46.5785, 370.6857, -49.48237, 0.125599, 0),
(147420, 4, -45.25912, 362.1349, -48.31962, 4.86548, 3000),
(147420, 5, -46.5785, 370.6857, -49.48237, 0.125599, 0),
(147420, 6, -71.08943, 368.8929, -48.58848, 5.234616, 0),
(147420, 7, -74.68849, 376.4933, -46.97439, 0.506518, 0);
