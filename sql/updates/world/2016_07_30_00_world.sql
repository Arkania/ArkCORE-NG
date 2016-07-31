
DELETE FROM waypoint_data WHERE id=4375101;
INSERT INTO waypoint_data VALUES 
(4375101, 0, -1303.852, 2127.484, 12.15787, 3.223109, 0, 1, 0, 0, 0),
(4375101, 1, -1346.805, 2132.702, 23.99352, 2.971781, 0, 1, 0, 0, 0),
(4375101, 2, -1393.364, 2207.524, 58.46828, 2.092135, 0, 1, 0, 0, 0),
(4375101, 3, -1414.835, 2333.402, 118.0422, 1.722997, 0, 1, 0, 0, 0),
(4375101, 4, -1411.925, 2534.767, 151.5658, 1.475597, 0, 1, 0, 0, 0),
(4375101, 5, -1393.333, 2776.773, 170.4687, 1.495232, 0, 1, 0, 0, 0),
(4375101, 6, -1420.541, 3074.897, 186.3741, 1.675874, 0, 1, 0, 0, 0),
(4375101, 7, -1469.879, 3257.731, 185.6588, 2.174602, 0, 1, 0, 0, 0);

UPDATE creature_template SET ScriptName="npc_hippogryph_43751" WHERE entry=43751;

UPDATE creature_template SET unit_flags=33280 WHERE entry=43566;

UPDATE creature_template SET unit_flags=32768 WHERE entry=43651;

UPDATE creature_template SET InhabitType=5 WHERE entry=43793;

UPDATE gameobject_template SET flags=16 WHERE entry=204428




