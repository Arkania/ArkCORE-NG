SET @GUID=147423;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay) values
(147423, 0, -124.0551, 262.7386, -47.52401, 1.661082, 3000),
(147423, 1, -122.5682, 250.9524, -48.42651, 4.83016, 0),
(147423, 2, -125.5134, 238.7071, -48.17736, 4.021203, 0),
(147423, 3, -132.4009, 231.4301, -47.87068, 3.817, 3000),
(147423, 4, -125.5134, 238.7071, -48.17736, 4.021203, 0),
(147423, 5, -122.5682, 250.9524, -48.42651, 4.83016, 0);
