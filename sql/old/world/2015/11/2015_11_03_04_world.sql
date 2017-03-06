SET @GUID=147373;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay) values
(147373, 0, -71.39214, 368.5264, -48.64456, 4.76337, 3000),
(147373, 1, -47.96698, 372.5497, -49.95192, 0.027417, 0),
(147373, 2, -48.57298, 357.8468, -48.21437, 4.704463, 0),
(147373, 3, -31.85178, 347.6162, -44.52285, 5.804014, 3000),
(147373, 4, -48.57298, 357.8468, -48.21437, 4.704463, 0),
(147373, 5, -47.96698, 372.5497, -49.95192, 0.027417, 0);
