SET @GUID=147383;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay) values
(147383, 0, 72.0007, 222.1333, -54.97138, 1.939754, 3000),
(147383, 1, 80.4725, 203.281, -54.97847, 5.140251, 0),
(147383, 2, 90.4733, 208.0485, -54.97847, 0.408225, 0),
(147383, 3, 111.2344, 217.3599, -42.49224, 0.404298, 0),
(147383, 4, 117.1295, 219.8822, -42.49013, 0.404298, 3000),
(147383, 5, 111.2344, 217.3599, -42.49224, 0.404298, 0),
(147383, 6, 90.4733, 208.0485, -54.97847, 0.408225, 0),
(147383, 7, 80.4725, 203.281, -54.97847, 5.140251, 0);
