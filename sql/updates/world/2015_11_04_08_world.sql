SET @GUID=147187;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay) values
(147187, 0, 114.8284, 218.7558, -42.49013, 3.57338, 3000),
(147187, 1, 141.5668, 230.9828, -42.49013, 0.447495, 0),
(147187, 2, 163.682, 240.9816, -29.36031, 0.42786, 0),
(147187, 3, 172.5302, 245.1934, -29.36172, 0.451422, 0),
(147187, 4, 169.1673, 252.636, -29.36001, 1.982949, 3000),
(147187, 5, 172.5302, 245.1934, -29.36172, 0.451422, 0),
(147187, 6, 163.682, 240.9816, -29.36031, 0.42786, 0),
(147187, 7, 141.5668, 230.9828, -42.49013, 0.447495, 0);
