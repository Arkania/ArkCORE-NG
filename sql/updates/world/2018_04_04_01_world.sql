
-- fix silvia movement below ground.. entry 39653, guid 110289
-- the old given 4 points, are the endpoints of randomly walking path's.. 
-- we create from this given points waypoint_data, with 30sec wait time between each endpoint..

DELETE FROM waypoint_data WHERE id=10000333;
INSERT INTO waypoint_data VALUES
(10000333, 1, -4912.04, 1483.12, 84.8, 0, 30000, 0, 0, 100, 0),  -- central point.. stay there for 30 sec
(10000333, 2, -4843.65, 1484.15, 85.4, 0,  5000, 0, 0, 100, 0),  -- move to bridge
(10000333, 3, -4912.04, 1483.12, 84.8, 0, 60000, 0, 0, 100, 0),  -- move to central point.. stay again..
(10000333, 4, -4913.43, 1470.81, 84.8, 0,  5000, 0, 0, 100, 0),  -- move to right table
(10000333, 5, -4912.04, 1483.12, 84.8, 0, 60000, 0, 0, 100, 0),  -- move to central point.. stay again..
(10000333, 6, -4911.71, 1495.91, 84.8, 0,  5000, 0, 0, 100, 0),  -- move to left table
(10000333, 7, -4897.46, 1507.11, 83.85, 0, 5000, 0, 0, 100, 0),  -- move to tree
(10000333, 8, -4903.71, 1505.17, 84.8, 0,  5000, 0, 0, 100, 0),  -- move to left table
(10000333, 9, -4912.04, 1483.12, 84.8, 0, 60000, 0, 0, 100, 0);  -- move to central point.. stay again..

