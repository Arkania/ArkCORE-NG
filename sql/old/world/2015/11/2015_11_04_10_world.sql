SET @GUID=147207;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay) values
(147207, 0, 156.0105, 283.2513, -26.58144, 5.336597, 3000),
(147207, 1, 144.0865, 308.8637, -26.58144, 2.00651, 3000),
(147207, 2, 158.2847, 300.3236, -26.58144, 5.324811, 0),
(147207, 3, 157.5369, 299.9897, -26.58144, 3.561594, 3000);
