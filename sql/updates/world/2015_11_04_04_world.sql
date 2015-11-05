SET @GUID=147426;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay) values
(147426, 0, -135.5387, 287.8567, -45.96881, 5.580207, 3000),
(147426, 1, -141.6509, 290.2906, -46.3088, 2.792046, 0),
(147426, 2, -148.1008, 286.5106, -46.1574, 3.671693, 0),
(147426, 3, -149.2381, 283.8964, -46.18592, 4.307862, 0),
(147426, 4, -151.1023, 271.0493, -47.05257, 5.089329, 3000),
(147426, 5, -149.2381, 283.8964, -46.18592, 4.307862, 0),
(147426, 6, -148.1008, 286.5106, -46.1574, 3.671693, 0),
(147426, 7, -141.6509, 290.2906, -46.3088, 2.792046, 0);
