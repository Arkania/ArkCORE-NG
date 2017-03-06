SET @GUID=147206;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay) values
(147206, 0, 167.6428, 256.2778, -29.35842, 5.175591, 3000),
(147206, 1, 162.7382, 267.7522, -29.35507, 1.96724, 0),
(147206, 2, 159.4054, 275.7138, -26.58144, 1.96724, 0),
(147206, 3, 156.9709, 281.3838, -26.58144, 2.045779, 3000),
(147206, 4, 159.4054, 275.7138, -26.58144, 1.96724, 0),
(147206, 5, 162.7382, 267.7522, -29.35507, 1.96724, 0);
