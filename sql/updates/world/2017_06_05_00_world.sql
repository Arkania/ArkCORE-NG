
UPDATE creature_template_addon SET auras="31765 83323 " WHERE entry=42573;

DELETE FROM creature WHERE id=43397 AND guid=6902;
INSERT INTO creature VALUES 
(6902, 43397, 646, 0, 0, 1, 237, 0, 0, 0, 1024.155, 534.8016, -49.33482, 2.134974, 120, 0, 0, 0, 0, 2, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=6902;
INSERT INTO creature_addon VALUES 
(6902, 690200, 0, 65536, 1, 0, 0, 0, 0, "83305");

DELETE FROM waypoint_data WHERE id=690200;
INSERT INTO waypoint_data VALUES 
(690200, 0, 1025.212, 533.1303, -49.33482, 0, 2000, 0, 0, 100, 0),
(690200, 1, 1024.677, 533.9753, -49.33482, 0, 0, 0, 0, 100, 0),
(690200, 2, 1023.005, 536.6186, -49.33482, 0, 0, 0, 0, 100, 0),
(690200, 3, 1017.892, 538.4261, -49.33482, 0, 0, 0, 0, 100, 0),
(690200, 4, 1015.06, 539.4277, -49.33482, 0, 0, 0, 0, 100, 0),
(690200, 5, 1013.24, 540.071, -49.33482, 0, 2000, 0, 0, 100, 0),
(690200, 6, 1013.24, 540.071, -49.33482, 0, 0, 0, 0, 100, 0),
(690200, 7, 1015.06, 539.4277, -49.33482, 0, 0, 0, 0, 100, 0),
(690200, 8, 1017.892, 538.4261, -49.33482, 0, 0, 0, 0, 100, 0),
(690200, 9, 1023.005, 536.6186, -49.33482, 0, 0, 0, 0, 100, 0),
(690200, 10, 1024.677, 533.9753, -49.33482, 0, 0, 0, 0, 100, 0);

UPDATE creature SET spawntimesecs=300 WHERE guid=243061;

UPDATE creature SET spawntimesecs=300 WHERE guid=243258;

DELETE FROM creature WHERE id=44361 AND guid=279202;
INSERT INTO creature VALUES 
(279202, 44361, 646, 0, 0, 1, 237, 0, 0, 0, 1033.17, 503.28, -49.25147, 2.303835, 300, 0, 0, 0, 0, 0, 0, 0, 0, 0);

UPDATE creature SET phaseId=237 WHERE guid=242599;

UPDATE creature SET phaseId=237, position_x=1021.73, position_y=552.314, position_z=-49.2515, orientation=4.3808, spawntimesecs=300, spawndist=0, MovementType=0 WHERE guid=244617;

UPDATE creature SET position_x=969.91, position_y=605.311, position_z=-36.3289, orientation=3.6303 WHERE guid=242600;

DELETE FROM creature WHERE id=43836 AND guid=279203;
INSERT INTO creature VALUES 
(279203, 43836, 646, 0, 0, 1, 169, 0, 33037, 0, 829.1432, 437.5266, -66.926, 4.764165, 300, 0, 0, 0, 0, 2, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=279203;
INSERT INTO creature_addon VALUES 
(279203, 279203, 0, 65536, 1, 0, 0, 0, 0, "83305");

DELETE FROM waypoint_data WHERE id=279203;
INSERT INTO waypoint_data VALUES 
(279203, 0, 828.9257, 441.7245, -67.14858, 0, 0, 0, 0, 100, 0),
(279203, 1, 828.9774, 440.7258, -67.14858, 0, 0, 0, 0, 100, 0),
(279203, 2, 829.1875, 436.6719, -66.86653, 0, 0, 0, 0, 100, 0),
(279203, 3, 829.5498, 429.6855, -66.263, 0, 0, 0, 0, 100, 0),
(279203, 4, 829.686, 427.156, -66.19196, 0, 0, 0, 0, 100, 0),
(279203, 5, 829.9785, 424.168, -67.013, 0, 0, 0, 0, 100, 0),
(279203, 6, 830.1738, 422.1758, -68.013, 0, 0, 0, 0, 100, 0),
(279203, 7, 830.2715, 421.1797, -68.763, 0, 0, 0, 0, 100, 0),
(279203, 8, 830.5645, 418.1914, -69.763, 0, 0, 0, 0, 100, 0),
(279203, 9, 831.399, 409.71, -69.888, 0, 0, 0, 0, 100, 0),
(279203, 10, 831.399, 409.71, -69.888, 0, 0, 0, 0, 100, 0),
(279203, 11, 831.399, 409.71, -69.888, 0, 0, 0, 0, 100, 0),
(279203, 12, 830.5645, 418.1914, -69.763, 0, 0, 0, 0, 100, 0),
(279203, 13, 830.2715, 421.1797, -68.763, 0, 0, 0, 0, 100, 0),
(279203, 14, 830.1738, 422.1758, -68.013, 0, 0, 0, 0, 100, 0),
(279203, 15, 829.9785, 424.168, -67.013, 0, 0, 0, 0, 100, 0),
(279203, 16, 829.686, 427.156, -66.19196, 0, 0, 0, 0, 100, 0),
(279203, 17, 829.5498, 429.6855, -66.263, 0, 0, 0, 0, 100, 0),
(279203, 18, 829.1875, 436.6719, -66.86653, 0, 0, 0, 0, 100, 0),
(279203, 19, 828.9774, 440.7258, -67.14858, 0, 0, 0, 0, 100, 0);

UPDATE creature SET MovementType=2 WHERE guid=242598;

DELETE FROM creature_addon WHERE guid=242598;
INSERT INTO creature_addon VALUES 
(242598, 242598, 0, 65536, 1, 0, 0, 0, 0, "83305");

DELETE FROM waypoint_data WHERE id=242598;
INSERT INTO waypoint_data VALUES 
(242598, 0, 1060.379, 417.8855, -43.72758, 0, 0, 0, 0, 100, 0),
(242598, 1, 1060.77, 418.806, -43.72758, 0, 0, 0, 0, 100, 0),
(242598, 2, 1058.821, 419.4446, -43.5175, 0, 0, 0, 0, 100, 0),
(242598, 3, 1057.731, 419.8017, -43.27487, 0, 0, 0, 0, 100, 0),
(242598, 4, 1046.975, 423.3249, -40.99565, 0, 0, 0, 0, 100, 0),
(242598, 5, 1041.45, 425.135, -40.1723, 0, 0, 0, 0, 100, 0),
(242598, 6, 1041.45, 425.135, -40.1723, 0, 0, 0, 0, 100, 0),
(242598, 7, 1041.45, 425.135, -40.1723, 0, 0, 0, 0, 100, 0),
(242598, 8, 1046.975, 423.3249, -40.99565, 0, 0, 0, 0, 100, 0),
(242598, 9, 1057.731, 419.8017, -43.27487, 0, 0, 0, 0, 100, 0),
(242598, 10, 1058.821, 419.4446, -43.5175, 0, 0, 0, 0, 100, 0),
(242598, 11, 1060.77, 418.806, -43.72758, 0, 0, 0, 0, 100, 0);

UPDATE creature SET spawntimesecs=300 WHERE guid=242622;

UPDATE creature SET spawntimesecs=300, MovementType=2 WHERE guid=243261;

DELETE FROM creature_addon WHERE guid=243261;
INSERT INTO creature_addon VALUES 
(243261, 243261, 0, 65636, 1, 0, 0, 0, 0, "78148 78150 84667");

DELETE FROM waypoint_data WHERE id=243261;
INSERT INTO waypoint_data VALUES 
(243261, 0, 1037.867, 508.2682, -49.25263, 0, 0, 0, 0, 100, 0),
(243261, 1, 1037.361, 509.1303, -49.25263, 0, 0, 0, 0, 100, 0),
(243261, 2, 1036.05, 511.361, -49.22079, 0, 0, 0, 0, 100, 0),
(243261, 3, 1034.351, 517.9017, -49.30329, 0, 0, 0, 0, 100, 0),
(243261, 4, 1033.766, 520.1537, -49.33482, 0, 0, 0, 0, 100, 0),
(243261, 5, 1032.831, 523.7492, -49.33483, 0, 0, 0, 0, 100, 0),
(243261, 6, 1031.628, 528.3825, -49.33483, 0, 0, 0, 0, 100, 0),
(243261, 7, 1031.39, 529.297, -49.33486, 0, 0, 0, 0, 100, 0),
(243261, 8, 1031.39, 529.297, -49.33486, 0, 0, 0, 0, 100, 0),
(243261, 9, 1031.39, 529.297, -49.33486, 0, 0, 0, 0, 100, 0),
(243261, 10, 1031.628, 528.3825, -49.33483, 0, 0, 0, 0, 100, 0),
(243261, 11, 1032.831, 523.7492, -49.33483, 0, 0, 0, 0, 100, 0),
(243261, 12, 1033.766, 520.1537, -49.33482, 0, 0, 0, 0, 100, 0),
(243261, 13, 1034.351, 517.9017, -49.30329, 0, 0, 0, 0, 100, 0),
(243261, 14, 1036.05, 511.361, -49.22079, 0, 0, 0, 0, 100, 0),
(243261, 15, 1037.361, 509.1303, -49.25263, 0, 0, 0, 0, 100, 0);

UPDATE creature SET position_x=1030.78, position_y=519.733, position_z=-49.3348, orientation=1.829, MovementType=2 WHERE guid=242298;

DELETE FROM creature_addon WHERE guid=242298;
INSERT INTO creature_addon VALUES 
(242298, 242298, 0, 65536, 1, 0, 0, 0, 0, "79949 84667 ");

DELETE FROM waypoint_data WHERE id=242298;
INSERT INTO waypoint_data VALUES 
(242298, 0, 1031.036, 518.7662, -49.33483, 0, 0, 0, 0, 100, 0),
(242298, 1, 1030.78, 519.733, -49.33483, 0, 0, 0, 0, 100, 0),
(242298, 2, 1029.73, 523.7575, -49.33483, 0, 0, 0, 0, 100, 0),
(242298, 3, 1029.73, 523.7575, -49.33483, 0, 0, 0, 0, 100, 0),
(242298, 4, 1029.73, 523.7575, -49.33483, 0, 0, 0, 0, 100, 0),
(242298, 5, 1030.78, 519.733, -49.33483, 0, 0, 0, 0, 100, 0);

UPDATE creature SET position_x=1065, position_y=637.158, position_z=-45.5963, orientation=5.2534, spawntimesecs=300 WHERE guid=244615;

UPDATE creature SET spawntimesecs=300, MovementType=2 WHERE guid=242624;

DELETE FROM creature_addon WHERE guid=242624;
INSERT INTO creature_addon VALUES 
(242624, 242624, 0, 0, 1, 0, 0, 0, 0, "78148 78150 83305");

DELETE FROM waypoint_data WHERE id=242624;
INSERT INTO waypoint_data VALUES 
(242624, 0, 1099.594, 585.06, -45.49322, 0, 0, 0, 0, 100, 0),
(242624, 1, 1099.14, 585.951, -45.49322, 0, 0, 0, 0, 100, 0),
(242624, 2, 1096.25, 586.0198, -45.20688, 0, 0, 0, 0, 100, 0),
(242624, 3, 1092.453, 586.1101, -44.81414, 0, 0, 0, 0, 100, 0),
(242624, 4, 1086.95, 586.241, -44.56657, 0, 0, 0, 0, 100, 0),
(242624, 5, 1086.95, 586.241, -44.56657, 0, 0, 0, 0, 100, 0),
(242624, 6, 1086.95, 586.241, -44.56657, 0, 0, 0, 0, 100, 0),
(242624, 7, 1092.453, 586.1101, -44.81414, 0, 0, 0, 0, 100, 0),
(242624, 8, 1096.25, 586.0198, -45.20688, 0, 0, 0, 0, 100, 0),
(242624, 9, 1099.14, 585.951, -45.49322, 0, 0, 0, 0, 100, 0);

UPDATE creature SET spawntimesecs=300, MovementType=2 WHERE guid=242655;

DELETE FROM creature_addon WHERE guid=242655;
INSERT INTO creature_addon VALUES 
(242655, 242655, 0, 0, 1, 0, 0, 0, 0, "78148 78150 83305");

DELETE FROM waypoint_data WHERE id=242655;
INSERT INTO waypoint_data VALUES 
(242655, 0, 1077.225, 580.5602, -44.29789, 0, 0, 0, 0, 100, 0),
(242655, 1, 1077.678, 581.4513, -44.29789, 0, 0, 0, 0, 100, 0),
(242655, 2, 1079.66, 585.342, -44.26242, 0, 0, 0, 0, 100, 0),
(242655, 3, 1079.785, 594.1592, -44.0152, 0, 0, 0, 0, 100, 0),
(242655, 4, 1079.88, 600.837, -44.25139, 0, 0, 0, 0, 100, 0),
(242655, 5, 1079.88, 600.837, -44.25139, 0, 0, 0, 0, 100, 0),
(242655, 6, 1079.88, 600.837, -44.25139, 0, 0, 0, 0, 100, 0),
(242655, 7, 1079.785, 594.1592, -44.0152, 0, 0, 0, 0, 100, 0),
(242655, 8, 1079.66, 585.342, -44.26242, 0, 0, 0, 0, 100, 0),
(242655, 9, 1077.678, 581.4513, -44.29789, 0, 0, 0, 0, 100, 0);

UPDATE creature SET spawntimesecs=300 WHERE guid in (242625, 242603);

update creature set phaseId=237 where guid in (242290);

update creature set phaseId=237 where id in (44680, 44681, 44684, 44685);

UPDATE creature SET phaseId=237 WHERE guid=245184;

update creature set phaseId=253 where guid in (242918, 243059, 242561, 243277, 244614);

update creature set phaseId=254 where guid in (244006);

UPDATE creature SET phaseId=237 WHERE guid=242545;

DELETE FROM creature WHERE id=44672 AND guid=6890;
INSERT INTO creature VALUES 
(6890, 44672, 646, 0, 0, 1, 253, 0, 0, 0, 993.984, 517.974, -49.25147, 0.1919862, 300, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=44672 AND guid=6892;
INSERT INTO creature VALUES 
(6892, 44672, 646, 0, 0, 1, 254, 0, 0, 0, 1079.783, 543.5899, -44.33477, 0.3316667, 300, 0, 0, 0, 0, 0, 0, 0, 0, 0);

UPDATE creature SET phaseId=253 WHERE guid=242679;

UPDATE creature SET phaseId=257 WHERE guid=242864;

delete from phase_definitions where zoneId=5355;
insert into phase_definitions values 
(5355, 0, 170, 0, 0, 0, 1, "Deepholm, Abyssion's Lair");

delete from phase_definitions where zoneId=5350;
insert into phase_definitions values 
(5350, 0, 251, 0, 0, 0, 1, "Deepholm, Needlerock Chasm");

delete from phase_definitions where zoneId=5335;
insert into phase_definitions values 
(5335, 0, 237, 0, 0, 0, 1, "Deepholm, Quartzite Basin");

delete from phase_definitions where zoneId=5291;
insert into phase_definitions values 
(5291, 0, 237, 0, 0, 0, 1, "Deepholm, Jagged Wastes");

delete from phase_area where areaId=5291 and entry=0;
insert into phase_area values 
(5291, 0, 27938, 27003, 64, 11, 1, "Deepholm, Jagged Wastes");

delete from phase_definitions where zoneId=5297;
insert into phase_definitions values 
(5297, 0, 252, 0, 0, 0, 1, "Deepholm, Halcyon Egress");

delete from phase_definitions where zoneId=5298;
insert into phase_definitions values 
(5298, 0, 252, 0, 0, 0, 1, "Deepholm, Twilight Precipice");

delete from phase_definitions where zoneId=5299;
insert into phase_definitions values 
(5299, 0, 252, 0, 0, 0, 1, "Lorthuna's Gate");

