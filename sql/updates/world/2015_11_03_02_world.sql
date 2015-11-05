SET @GUID=147225;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay) values
(147225, 0, -41.49646, 248.8301, -48.32457, 4.637716, 3000),
(147225, 1, -39.26283, 273.4036, -48.64357, 1.480413, 0),
(147225, 2, -28.1684, 275.0365, -48.38658, 0.211994, 3000),
(147225, 3, -39.26283, 273.4036, -48.64357, 1.480413, 0);
