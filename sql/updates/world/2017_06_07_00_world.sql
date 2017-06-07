

UPDATE creature_template SET npcflag=0 WHERE entry=43713;

UPDATE creature_template SET ScriptName="" WHERE entry=45005;

delete from game_event_creature where eventEntry=7 and guid=243058;
insert into game_event_creature values 
(7, 243058);

UPDATE creature SET position_x=1039.31, position_y=519.615, position_z=-49.2709, orientation=2.6704, spawndist=0, MovementType=0 WHERE guid=242299;

DELETE FROM creature WHERE guid IN (242672, 242866, 6919);
INSERT INTO creature VALUES 
(242672, 44678, 646, 0, 0, 1, 253, 0, 0, 0, 1029.83, 443.443, -38.2184, 2.8364, 500, 0, 0, 64496, 0, 0, 0, 0, 0, 0), 
(242866, 44678, 646, 0, 0, 1, 254, 0, 0, 0, 1029.38, 443.443, -38.2184, 0.5326598, 500, 0, 0, 64496, 0, 0, 0, 0, 0, 0),
(6919,   44678, 646, 0, 0, 1, 257, 0, 0, 0, 1041.55, 485.759, -49.14557, 0.3141593, 500, 0, 0, 64496, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE guid in (244618, 10772, 11536);
INSERT INTO creature VALUES 
(244618, 44669, 646, 0, 0, 1, 253, 0, 0, 0, 1027.39, 509.549, -49.25147, 2.303835, 300, 0, 0, 210, 0, 0, 0, 0, 0, 0),
(10772,  44669, 646, 0, 0, 1, 254, 0, 0, 0, 1027.16, 509.463, -49.33483, 0.006816, 300, 0, 0, 210, 0, 0, 0, 0, 0, 0),
(11536,  44669, 646, 0, 0, 1, 257, 0, 0, 0, 1005.82, 511.167, -49.25147, 2.426008, 300, 0, 0, 210, 0, 0, 0, 0, 0, 0);

delete from game_event_creature where eventEntry=1 and guid=243097;
insert into game_event_creature values 
(1, 243097);

UPDATE creature SET phaseId=254, position_x=931.9712, position_y=506.6098, position_z=-49.3098, orientation=.226, spawntimesecs=300, MovementType=2 WHERE guid=242914;

DELETE FROM creature_addon WHERE guid=242914;
INSERT INTO creature_addon VALUES 
(242914, 242914, 0, 0, 1, 0, 0, 0, 0, "");

DELETE FROM waypoint_data WHERE id=242914;
INSERT INTO waypoint_data VALUES 
(242914, 0, 930.0782, 506.2274, -49.25147, 0, 0, 0, 0, 100, 0),
(242914, 1, 931.063, 506.401, -49.25147, 0, 0, 0, 0, 100, 0),
(242914, 2, 932.1609, 506.6534, -49.32201, 0, 0, 0, 0, 100, 0),
(242914, 3, 939.7656, 508.4018, -49.32757, 0, 0, 0, 0, 100, 0),
(242914, 4, 942.3174, 508.9885, -49.32784, 0, 0, 0, 0, 100, 0),
(242914, 5, 944.7856, 509.5559, -49.3281, 0, 0, 0, 0, 100, 0),
(242914, 6, 951.9686, 511.2074, -49.32919, 0, 0, 0, 0, 100, 0),
(242914, 7, 959.035, 512.832, -49.33477, 0, 0, 0, 0, 100, 0),
(242914, 8, 959.035, 512.832, -49.33477, 0, 0, 0, 0, 100, 0),
(242914, 9, 959.035, 512.832, -49.33477, 0, 0, 0, 0, 100, 0),
(242914, 10, 951.9686, 511.2074, -49.32919, 0, 0, 0, 0, 100, 0),
(242914, 11, 944.7856, 509.5559, -49.3281, 0, 0, 0, 0, 100, 0),
(242914, 12, 942.3174, 508.9885, -49.32784, 0, 0, 0, 0, 100, 0),
(242914, 13, 939.7656, 508.4018, -49.32757, 0, 0, 0, 0, 100, 0),
(242914, 14, 932.1609, 506.6534, -49.32201, 0, 0, 0, 0, 100, 0),
(242914, 15, 931.063, 506.401, -49.25147, 0, 0, 0, 0, 100, 0);

UPDATE creature SET phaseId=254 WHERE guid=242678;

UPDATE creature SET phaseId=253 WHERE guid=242865;

UPDATE creature SET phaseId=237, position_x=1340.389, position_y=623.9145, position_z=-65.439, orientation=.0528, spawntimesecs=300 WHERE guid=243253;

UPDATE gameobject SET phaseId=253 WHERE guid=400523;

delete from creature where id=48732 and guid=242670;

UPDATE creature SET phaseId=253, position_x=1007.78, position_y=506.826, position_z=-49.2515, spawntimesecs=300, spawndist=0, MovementType=0 WHERE guid=244619;

UPDATE creature SET phaseId=257, position_x=991.191, position_y=515.01, position_z=-49.2515, orientation=3.159, spawntimesecs=300, spawndist=0, MovementType=0 WHERE guid=244620;

delete from game_event_gameobject where eventEntry=12 and guid=404159;
insert into game_event_gameobject values 
(12, 404159);

UPDATE creature_template SET faction=35 WHERE entry=45397;

UPDATE creature SET phaseId=237, spawntimesecs=300 WHERE guid=242671;

UPDATE creature SET phaseId=237, spawntimesecs=300 WHERE guid=242913;

DELETE FROM creature WHERE guid IN (244616, 287853, 287854);
INSERT INTO creature VALUES 
(244616, 44676, 646, 0, 0, 1, 253, 0, 0, 0, 1032.52, 426.623, -38.97037, 2.827433, 300, 0, 0, 126, 0, 0, 0, 0, 0, 0), 
(287853, 44676, 646, 0, 0, 1, 254, 0, 0, 0, 1032.52, 426.623, -38.97037, 5.176211, 300, 0, 0, 0, 0, 0, 0, 0, 0, 0), 
(287854, 44676, 646, 0, 0, 1, 257, 0, 0, 0, 1042.93, 483.901, -49.18477, 0.715585, 300, 0, 0, 0, 0, 0, 0, 0, 0, 0);


