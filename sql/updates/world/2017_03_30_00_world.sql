

update creature set phaseId=232 where id=42793;

DELETE FROM creature WHERE id=42771 AND guid=42413;
INSERT INTO creature VALUES 
(42413, 42771, 0, 0, 0, 1, 232, 0, 0, 0, -10511.16, 1050.486, 60.16436, 4.974188, 120, 0, 0, 0, 0, 0, 0, 0, 0);

UPDATE gameobject SET phaseId=169, phaseGroup=0 WHERE guid=183244;

DELETE FROM gameobject WHERE id=204043 AND guid=54;
INSERT INTO gameobject VALUES 
(54, 204043, 0, 0, 0, 1, 232, 0, -10514.18, 1045.856, 60.51798, 0.4537851, 0, 0, 0.2249508, 0.9743701, 120, 255, 1);

DELETE FROM creature WHERE id=42771 AND guid=42423;
INSERT INTO creature VALUES 
(42423, 42771, 0, 0, 0, 1, 232, 0, 0, 0, -10507.99, 1051.469, 60.25721, 4.886922, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=42771 AND guid=42426;
INSERT INTO creature VALUES 
(42426, 42771, 0, 0, 0, 1, 232, 0, 0, 0, -10510.16, 1052.729, 59.49126, 5.113815, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=42771 AND guid=42437;
INSERT INTO creature VALUES 
(42437, 42771, 0, 0, 0, 1, 232, 0, 0, 0, -10512.3, 1042.028, 60.60131, 1.082104, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=42771 AND guid=42440;
INSERT INTO creature VALUES 
(42440, 42771, 0, 0, 0, 1, 232, 0, 0, 0, -10514.06, 1052.134, 59.15881, 5.323254, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=42771 AND guid=42504;
INSERT INTO creature VALUES 
(42504, 42771, 0, 0, 0, 1, 232, 0, 0, 0, -10516.88, 1048.599, 60.03143, 5.8294, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=42771 AND guid=42514;
INSERT INTO creature VALUES 
(42514, 42771, 0, 0, 0, 1, 232, 0, 0, 0, -10504.66, 1050.417, 60.60131, 4.45059, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=42771 AND guid=42555;
INSERT INTO creature VALUES 
(42555, 42771, 0, 0, 0, 1, 232, 0, 0, 0, -10507.73, 1039.929, 60.60131, 1.954769, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=42771 AND guid=42558;
INSERT INTO creature VALUES 
(42558, 42771, 0, 0, 0, 1, 232, 0, 0, 0, -10505, 1053.427, 59.97273, 4.625123, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=42771 AND guid=42585;
INSERT INTO creature VALUES 
(42585, 42771, 0, 0, 0, 1, 232, 0, 0, 0, -10505.78, 1040.786, 60.60131, 1.937315, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=42771 AND guid=42637;
INSERT INTO creature VALUES 
(42637, 42771, 0, 0, 0, 1, 232, 0, 0, 0, -10515.77, 1040.724, 60.60131, 0.3665192, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=42771 AND guid=42646;
INSERT INTO creature VALUES 
(42646, 42771, 0, 0, 0, 1, 232, 0, 0, 0, -10512.69, 1038.826, 60.60131, 1.22173, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=42771 AND guid=42649;
INSERT INTO creature VALUES 
(42649, 42771, 0, 0, 0, 1, 232, 0, 0, 0, -10501.51, 1046.292, 60.60131, 3.228859, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=42771 AND guid=42752;
INSERT INTO creature VALUES 
(42752, 42771, 0, 0, 0, 1, 232, 0, 0, 0, -10501.6, 1042.736, 60.60131, 2.617994, 120, 0, 0, 0, 0, 0, 0, 0, 0);

delete from  creature WHERE id=42750 and guid=6983;

UPDATE creature_template SET ScriptName="npc_ripsnarl_sentinel_hill_42635" WHERE entry=42635;

UPDATE creature SET position_x=-10597.12, position_y=1035.674, position_z=34.4373, orientation=1.1718, spawntimesecs=120, MovementType=2 WHERE guid=10756;

DELETE FROM creature_addon WHERE guid=10756;
INSERT INTO creature_addon VALUES 
(10756, 10756, 0, 0, 1, 0, "5301");

DELETE FROM waypoint_data WHERE id=10756;
INSERT INTO waypoint_data VALUES 
(10756, 0, -10597.12, 1035.674, 34.43727, 0, 0, 0, 0, 100, 0),
(10756, 1, -10582.62, 1073.045, 38.55705, 0, 0, 0, 0, 100, 0),
(10756, 2, -10584.62, 1067.295, 37.80705, 0, 0, 0, 0, 100, 0),
(10756, 3, -10586.37, 1063.045, 37.05705, 0, 0, 0, 0, 100, 0),
(10756, 4, -10587.87, 1059.295, 36.80705, 0, 0, 0, 0, 100, 0),
(10756, 5, -10590.37, 1052.795, 36.05705, 0, 0, 0, 0, 100, 0),
(10756, 6, -10592.62, 1047.045, 35.55705, 0, 0, 0, 0, 100, 0),
(10756, 7, -10596.62, 1037.045, 34.80705, 0, 0, 0, 0, 100, 0),
(10756, 8, -10598.42, 1035.05, 34.4032, 0, 0, 0, 0, 100, 0),
(10756, 9, -10599.6, 1039.942, 34.50879, 0, 0, 0, 0, 100, 0),
(10756, 10, -10598.42, 1035.05, 34.4032, 0, 0, 0, 0, 100, 0),
(10756, 11, -10596.62, 1037.045, 34.80705, 0, 0, 0, 0, 100, 0),
(10756, 12, -10592.62, 1047.045, 35.55705, 0, 0, 0, 0, 100, 0),
(10756, 13, -10590.37, 1052.795, 36.05705, 0, 0, 0, 0, 100, 0),
(10756, 14, -10587.87, 1059.295, 36.80705, 0, 0, 0, 0, 100, 0),
(10756, 15, -10586.37, 1063.045, 37.05705, 0, 0, 0, 0, 100, 0),
(10756, 16, -10584.62, 1067.295, 37.80705, 0, 0, 0, 0, 100, 0),
(10756, 17, -10582.62, 1073.045, 38.55705, 0, 0, 0, 0, 100, 0);

UPDATE creature SET position_x=-10641.46, position_y=1148.257, position_z=33.7605, orientation=.4532, spawntimesecs=120, MovementType=2 WHERE guid=10757;

DELETE FROM creature_addon WHERE guid=10757;
INSERT INTO creature_addon VALUES 
(10757, 10757, 0, 0, 1, 0, "5301");

DELETE FROM waypoint_data WHERE id=10757;
INSERT INTO waypoint_data VALUES 
(10757, 0, -10641.46, 1148.257, 33.76053, 0, 0, 0, 0, 100, 0),
(10757, 1, -10642.08, 1146.896, 33.72567, 0, 0, 0, 0, 100, 0),
(10757, 2, -10642.22, 1147.886, 33.72567, 0, 0, 0, 0, 100, 0),
(10757, 3, -10629.64, 1154.011, 34.30106, 0, 0, 0, 0, 100, 0),
(10757, 4, -10620.66, 1158.386, 34.92606, 0, 0, 0, 0, 100, 0),
(10757, 5, -10613.47, 1161.886, 35.55106, 0, 0, 0, 0, 100, 0),
(10757, 6, -10602.69, 1167.136, 36.14262, 0, 0, 0, 0, 100, 0),
(10757, 7, -10583.82, 1176.323, 35.55974, 0, 0, 0, 0, 100, 0),
(10757, 8, -10583.42, 1176.52, 35.56487, 0, 0, 0, 0, 100, 0),
(10757, 9, -10583.42, 1176.52, 35.56487, 0, 0, 0, 0, 100, 0),
(10757, 10, -10583.42, 1176.52, 35.56487, 0, 0, 0, 0, 100, 0),
(10757, 11, -10583.82, 1176.323, 35.55974, 0, 0, 0, 0, 100, 0),
(10757, 12, -10602.69, 1167.136, 36.14262, 0, 0, 0, 0, 100, 0),
(10757, 13, -10613.47, 1161.886, 35.55106, 0, 0, 0, 0, 100, 0),
(10757, 14, -10620.66, 1158.386, 34.92606, 0, 0, 0, 0, 100, 0),
(10757, 15, -10629.64, 1154.011, 34.30106, 0, 0, 0, 0, 100, 0),
(10757, 16, -10642.22, 1147.886, 33.72567, 0, 0, 0, 0, 100, 0),
(10757, 17, -10642.08, 1146.896, 33.72567, 0, 0, 0, 0, 100, 0);

DELETE FROM creature WHERE id=51915 AND guid=42761;
INSERT INTO creature VALUES 
(42761, 51915, 0, 0, 0, 1, 169, 0, 0, 0, -10687.37, 1203.287, 34.62099, 0.7709001, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=42761;
INSERT INTO creature_addon VALUES 
(42761, 0, 0, 0, 1, 0, "5301");

UPDATE creature SET position_x=-10640.7, position_y=1150.502, position_z=33.8225, orientation=1.0429, spawntimesecs=120, MovementType=2 WHERE guid=10758;

DELETE FROM creature_addon WHERE guid=10758;
INSERT INTO creature_addon VALUES 
(10758, 10758, 0, 0, 1, 0, "5301");

DELETE FROM waypoint_data WHERE id=10758;
INSERT INTO waypoint_data VALUES 
(10758, 0, -10640.7, 1150.502, 33.82245, 0, 0, 0, 0, 100, 0),
(10758, 1, -10642.08, 1146.896, 33.72567, 0, 0, 0, 0, 100, 0),
(10758, 2, -10642.22, 1147.886, 33.72567, 0, 0, 0, 0, 100, 0),
(10758, 3, -10633.15, 1163.442, 34.30106, 0, 0, 0, 0, 100, 0),
(10758, 4, -10630.2, 1168.51, 34.58134, 0, 0, 0, 0, 100, 0),
(10758, 5, -10630.2, 1168.51, 34.58134, 0, 0, 0, 0, 100, 0),
(10758, 6, -10630.2, 1168.51, 34.58134, 0, 0, 0, 0, 100, 0),
(10758, 7, -10633.15, 1163.442, 34.30106, 0, 0, 0, 0, 100, 0),
(10758, 8, -10642.22, 1147.886, 33.72567, 0, 0, 0, 0, 100, 0),
(10758, 9, -10642.08, 1146.896, 33.72567, 0, 0, 0, 0, 100, 0);

DELETE FROM creature_addon WHERE guid=13620;
INSERT INTO creature_addon VALUES 
(13620, 0, 0, 65536, 0, 0, "79497");

DELETE FROM creature_addon WHERE guid=13621;
INSERT INTO creature_addon VALUES 
(13621, 0, 0, 65536, 0, 0, "79497");

DELETE FROM creature_addon WHERE guid=43299;
INSERT INTO creature_addon VALUES 
(43299, 0, 0, 65536, 0, 0, "79488");

DELETE FROM creature_addon WHERE guid=6984;
INSERT INTO creature_addon VALUES 
(6984, 0, 0, 65536, 0, 0, "79497");

UPDATE creature_template SET unit_flags2=2099200 WHERE entry=42635;

DELETE FROM creature_addon WHERE guid=275259;
INSERT INTO creature_addon VALUES 
(275259, 0, 0, 65536, 1, 0, "79497"); 
 
DELETE FROM creature_addon WHERE guid=275273;
INSERT INTO creature_addon VALUES 
(275273, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275274;
INSERT INTO creature_addon VALUES 
(275274, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275275;
INSERT INTO creature_addon VALUES 
(275275, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275277;
INSERT INTO creature_addon VALUES 
(275277, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275276;
INSERT INTO creature_addon VALUES 
(275276, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275278;
INSERT INTO creature_addon VALUES 
(275278, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275279;
INSERT INTO creature_addon VALUES 
(275279, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275280;
INSERT INTO creature_addon VALUES 
(275280, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275281;
INSERT INTO creature_addon VALUES 
(275281, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275282;
INSERT INTO creature_addon VALUES 
(275282, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275283;
INSERT INTO creature_addon VALUES 
(275283, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275284;
INSERT INTO creature_addon VALUES 
(275284, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275285;
INSERT INTO creature_addon VALUES 
(275285, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275286;
INSERT INTO creature_addon VALUES 
(275286, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275272;
INSERT INTO creature_addon VALUES 
(275272, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275254;
INSERT INTO creature_addon VALUES 
(275254, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275258;
INSERT INTO creature_addon VALUES 
(275258, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275260;
INSERT INTO creature_addon VALUES 
(275260, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275261;
INSERT INTO creature_addon VALUES 
(275261, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275262;
INSERT INTO creature_addon VALUES 
(275262, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275257;
INSERT INTO creature_addon VALUES 
(275257, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275256;
INSERT INTO creature_addon VALUES 
(275256, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275265;
INSERT INTO creature_addon VALUES 
(275265, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275266;
INSERT INTO creature_addon VALUES 
(275266, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275267;
INSERT INTO creature_addon VALUES 
(275267, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275268;
INSERT INTO creature_addon VALUES 
(275268, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275255;
INSERT INTO creature_addon VALUES 
(275255, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275269;
INSERT INTO creature_addon VALUES 
(275269, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275270;
INSERT INTO creature_addon VALUES 
(275270, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275271;
INSERT INTO creature_addon VALUES 
(275271, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275253;
INSERT INTO creature_addon VALUES 
(275253, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275287;
INSERT INTO creature_addon VALUES 
(275287, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275264;
INSERT INTO creature_addon VALUES 
(275264, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275263;
INSERT INTO creature_addon VALUES 
(275263, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275295;
INSERT INTO creature_addon VALUES 
(275295, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275251;
INSERT INTO creature_addon VALUES 
(275251, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275250;
INSERT INTO creature_addon VALUES 
(275250, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275297;
INSERT INTO creature_addon VALUES 
(275297, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275296;
INSERT INTO creature_addon VALUES 
(275296, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275294;
INSERT INTO creature_addon VALUES 
(275294, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275252;
INSERT INTO creature_addon VALUES 
(275252, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275289;
INSERT INTO creature_addon VALUES 
(275289, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275290;
INSERT INTO creature_addon VALUES 
(275290, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275288;
INSERT INTO creature_addon VALUES 
(275288, 0, 0, 65536, 1, 0, "79497");
 
DELETE FROM creature_addon WHERE guid=275291;
INSERT INTO creature_addon VALUES 
(275291, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275292;
INSERT INTO creature_addon VALUES 
(275292, 0, 0, 65536, 1, 0, "79497");

DELETE FROM creature_addon WHERE guid=275293;
INSERT INTO creature_addon VALUES 
(275293, 0, 0, 65536, 1, 0, "79497");

update creature_addon set auras="5301 79497" where guid in (10756, 10757, 10758, 42761);

UPDATE gameobject SET phaseId=226 WHERE id=204099;

UPDATE creature SET MovementType=2 WHERE guid=43531;

UPDATE creature_addon SET path_id=43531 WHERE guid=43531;

DELETE FROM waypoint_data WHERE id=43531;
INSERT INTO waypoint_data VALUES 
(43531, 0, -9876.88, 913.8506, 31.69556, 1.764076, 0, 0, 0, 100, 0),
(43531, 1, -9877.703, 916.4565, 31.55146, 1.893672, 0, 0, 0, 100, 0),
(43531, 2, -9887.246, 949.8434, 32.91191, 1.858329, 3000, 0, 0, 100, 0),
(43531, 3, -9891.326, 948.685, 33.5674, 3.417345, 0, 0, 0, 100, 0),
(43531, 4, -9912.803, 970.4868, 35.43868, 2.325642, 3000, 0, 0, 100, 0),
(43531, 5, -9916.422, 967.1622, 35.67848, 3.884658, 0, 0, 0, 100, 0),
(43531, 6, -9913.153, 947.0421, 34.48892, 4.862479, 0, 0, 0, 100, 0),
(43531, 7, -9916.117, 931.1304, 34.50907, 4.834993, 3000, 0, 0, 100, 0),
(43531, 8, -9907.738, 931.9835, 32.56341, 0.020497, 0, 0, 0, 100, 0),
(43531, 9, -9870.402, 883.7288, 32.31892, 5.506501, 3000, 0, 0, 100, 0),
(43531, 10, -9875.064, 904.5765, 32.28777, 1.764076, 0, 0, 0, 100, 0),
(43531, 11, -9876.88, 913.8506, 31.69556, 1.764076, 0, 0, 0, 100, 0);

UPDATE creature_addon SET auras="79343" WHERE guid=13617;

UPDATE creature SET spawntimesecs=120, spawndist=0, MovementType=2 WHERE guid=43026;

UPDATE creature_addon SET path_id=43026 WHERE guid=43026;

DELETE FROM waypoint_data WHERE id=43026;
INSERT INTO waypoint_data VALUES 
(43026, 0, -9889.4, 1309.9, 42.11688, 2.510188, 0, 0, 0, 100, 0),
(43026, 1, -9899.219, 1317.08, 42.49965, 2.510188, 0, 0, 0, 100, 0),
(43026, 2, -9895.04, 1356.662, 43.33812, 1.465608, 0, 0, 0, 100, 0),
(43026, 3, -9864.994, 1366.802, 44.31771, 0.311073, 0, 0, 0, 100, 0),
(43026, 4, -9847.659, 1359.558, 43.94466, 5.887397, 0, 0, 0, 100, 0),
(43026, 5, -9841.237, 1334.818, 43.27987, 4.960632, 0, 0, 0, 100, 0),
(43026, 6, -9847.804, 1312.341, 44.48492, 4.469757, 0, 0, 0, 100, 0),
(43026, 7, -9871.37, 1294.651, 42.19362, 3.751118, 0, 0, 0, 100, 0),
(43026, 8, -9882.614, 1297.845, 42.09189, 2.871472, 0, 0, 0, 100, 0),
(43026, 9, -9888.352, 1306.658, 42.03308, 2.137123, 0, 0, 0, 100, 0);

update creature set spawndist=0, MovementType=0 where guid in (42662,42903,42547,43074,43088,43327,43441);

UPDATE creature SET spawntimesecs=120, MovementType=2 WHERE guid=43449;

UPDATE creature_addon SET path_id=43449, auras="" WHERE guid=43449;

DELETE FROM waypoint_data WHERE id=43449;
INSERT INTO waypoint_data VALUES 
(43449, 0, -9886.822, 1308.34, 42.2481, 0.939396, 5000, 0, 0, 100, 0),
(43449, 1, -9880.822, 1313.952, 42.96179, 0.73912, 0, 0, 0, 100, 0),
(43449, 2, -9875.419, 1308.857, 42.99954, 5.541829, 0, 0, 0, 100, 0),
(43449, 3, -9872.152, 1312.509, 43.02404, 0.841219, 0, 0, 0, 100, 0),
(43449, 4, -9874.939, 1316.707, 43.00893, 2.156761, 0, 0, 0, 100, 0),
(43449, 5, -9868.296, 1324.572, 43.06206, 0.970809, 0, 0, 0, 100, 0),
(43449, 6, -9865.098, 1321.891, 43.08759, 5.22767, 0, 0, 0, 100, 0),
(43449, 7, -9876.314, 1309.073, 42.9957, 3.971038, 0, 0, 0, 100, 0),
(43449, 8, -9881.901, 1313.99, 42.95489, 2.573029, 0, 0, 0, 100, 0),
(43449, 9, -9885.144, 1310.306, 42.3856, 3.990673, 0, 0, 0, 100, 0);

UPDATE creature SET spawndist=0, MovementType=2 WHERE guid=42422;

UPDATE creature_addon SET path_id=42422, auras="" WHERE guid=42422;

DELETE FROM waypoint_data WHERE id=42422;
INSERT INTO waypoint_data VALUES 
(42422, 0, -9836.631, 1031.775, 32.59782, 3.495886, 0, 1, 0, 100, 0),
(42422, 1, -9842.359, 1028.881, 32.65715, 3.590133, 0, 1, 0, 100, 0),
(42422, 2, -9844.642, 1031.374, 33.03287, 2.321715, 0, 1, 0, 100, 0),
(42422, 3, -9845.918, 1032.74, 34.05635, 2.321715, 0, 1, 0, 100, 0),
(42422, 4, -9848.13, 1035.109, 34.01158, 2.321715, 0, 1, 0, 100, 0),
(42422, 5, -9846.071, 1033.039, 34.06534, 5.494724, 5000, 1, 0, 100, 0),
(42422, 6, -9844.357, 1030.89, 32.97982, 5.384769, 0, 1, 0, 100, 0),
(42422, 7, -9848.513, 1026.457, 33.0567, 3.959275, 0, 1, 0, 100, 0),
(42422, 8, -9849.766, 1026.193, 32.96046, 3.346664, 1000, 1, 0, 100, 0),
(42422, 9, -9849.766, 1026.193, 32.96046, 3.346664, 0, 1, 0, 100, 0),
(42422, 10, -9841.787, 1025.509, 32.70155, 6.197657, 0, 1, 0, 100, 0),
(42422, 11, -9832.627, 1034.131, 32.92649, 0.743066, 0, 1, 0, 100, 0),
(42422, 12, -9832.726, 1037.73, 33.20349, 1.59915, 0, 1, 0, 100, 0),
(42422, 13, -9835.345, 1038.336, 33.28572, 2.918619, 0, 1, 0, 100, 0),
(42422, 14, -9837.216, 1037.156, 32.99725, 3.704018, 0, 1, 0, 100, 0),
(42422, 15, -9837.854, 1034.538, 32.84866, 4.473706, 0, 1, 0, 100, 0),
(42422, 16, -9837.112, 1032.576, 32.659, 4.97636, 0, 1, 0, 100, 0);

UPDATE creature SET spawndist=0, MovementType=2 WHERE guid=43551;

UPDATE creature_addon SET path_id=43551, auras="" WHERE guid=43551;

DELETE FROM waypoint_data WHERE id=43551;
INSERT INTO waypoint_data VALUES 
(43551, 0, -9830.989, 1036.063, 33.05743, 2.910766, 0, 1, 0, 100, 0),
(43551, 1, -9837.685, 1039.259, 33.43539, 2.360991, 0, 1, 0, 100, 0),
(43551, 2, -9843.149, 1046.091, 34.01668, 2.258889, 0, 1, 0, 100, 0),
(43551, 3, -9828.942, 1049.38, 33.12466, 0.185437, 0, 1, 0, 100, 0),
(43551, 4, -9817.892, 1046.725, 31.41439, 6.138753, 0, 1, 0, 100, 0),
(43551, 5, -9819.27, 1051.02, 30.97835, 2.019339, 0, 1, 0, 100, 0),
(43551, 6, -9816.979, 1054.967, 30.0217, 0.6606, 0, 1, 0, 100, 0),
(43551, 7, -9809.823, 1052.617, 29.23803, 5.910995, 0, 1, 0, 100, 0),
(43551, 8, -9811.615, 1049.473, 29.85701, 4.18705, 0, 1, 0, 100, 0),
(43551, 9, -9818.808, 1047.562, 31.47888, 3.582294, 0, 1, 0, 100, 0),
(43551, 10, -9817.491, 1043.214, 31.92016, 5.031352, 0, 1, 0, 100, 0),
(43551, 11, -9812.942, 1043.075, 31.07733, 6.260497, 0, 1, 0, 100, 0),
(43551, 12, -9810.963, 1048.407, 29.92243, 1.332123, 0, 1, 0, 100, 0),
(43551, 13, -9818.42, 1054.547, 30.30217, 2.443461, 0, 1, 0, 100, 0),
(43551, 14, -9821.693, 1051.091, 31.46535, 4.065308, 0, 1, 0, 100, 0),
(43551, 15, -9819.606, 1048.36, 31.51276, 5.37692, 0, 1, 0, 100, 0),
(43551, 16, -9811.923, 1047.846, 30.13931, 6.142683, 0, 1, 0, 100, 0),
(43551, 17, -9812.863, 1042.713, 31.1249, 4.363761, 0, 1, 0, 100, 0),
(43551, 18, -9827.047, 1040.735, 33.41303, 3.272058, 0, 1, 0, 100, 0),
(43551, 19, -9836.273, 1039.389, 33.50148, 3.291693, 0, 1, 0, 100, 0);

delete from creature where guid in (6890,6892,6888,6821,6923,6921,6902,6919,6912,6908,6907,6913,6922,6602,6603,6605);

delete from creature where guid in (43485,43578,43179,43358,42450,42852,43187,43017,42524,42968,42533);

update creature set phaseId=170 where id=573; -- the npc is not part of standard quest. 

UPDATE creature SET zoneId=40, areaId=918, position_x=-10168.01, position_y=1441.211, position_z=40.60195, orientation=3.245536 WHERE id=42342 AND guid=42321;
UPDATE creature SET zoneId=40, areaId=918, position_x=-10183.94, position_y=1473.852, position_z=40.34966, orientation=3.441885 WHERE id=42342 AND guid=42767;
UPDATE creature SET zoneId=40, areaId=918, position_x=-10224.23, position_y=1505.259, position_z=40.53627, orientation=4.136963 WHERE id=42342 AND guid=42453;
UPDATE creature SET zoneId=40, areaId=918, position_x=-10221.35, position_y=1466.438, position_z=40.87732, orientation=3.771749 WHERE id=42342 AND guid=43208;
UPDATE creature SET zoneId=40, areaId=918, position_x=-10154.76, position_y=1410.755, position_z=39.00261, orientation=2.448354 WHERE id=42342 AND guid=42511;
UPDATE creature SET zoneId=40, areaId=918, position_x=-10225.23, position_y=1369.988, position_z=39.41589, orientation=2.26771 WHERE id=42342 AND guid=42773;
UPDATE creature SET zoneId=40, areaId=918, position_x=-10322.1, position_y=1471.106, position_z=39.1837, orientation=5.978718 WHERE id=42342 AND guid=43644;
UPDATE creature SET zoneId=40, areaId=918, position_x=-10292.89, position_y=1507.748, position_z=39.35442, orientation=5.040167 WHERE id=42342 AND guid=42693;

DELETE FROM creature_addon WHERE guid=43578;
DELETE FROM creature_addon WHERE guid=43485;
DELETE FROM creature_addon WHERE guid=43358;
DELETE FROM creature_addon WHERE guid=43187;
DELETE FROM creature_addon WHERE guid=43179;
DELETE FROM creature_addon WHERE guid=43017;
DELETE FROM creature_addon WHERE guid=42852;
DELETE FROM creature_addon WHERE guid=42533;
DELETE FROM creature_addon WHERE guid=42524;
DELETE FROM creature_addon WHERE guid=42450;

update creature set spawntimesecs=120 where id=42342;

UPDATE creature_template SET mindmg=2, maxdmg=2, attackpower=24, minrangedmg=1, maxrangedmg=1, rangedattackpower=0 WHERE entry=42601;

delete from spell_script_names where spell_id=79084;
insert into spell_script_names values 
(79084, "spell_unbound_energy_79084");   

UPDATE creature_template SET AIName="SmartAI", ScriptName="" WHERE entry=42342;

UPDATE creature_template SET ScriptName="npc_salma_saldean_235" WHERE entry=235;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Schattenhafte Person", QuestGiverTargetName_loc3="Schattenhafte Person" WHERE Id=26297;

DELETE FROM phase_definitions WHERE zoneId=40;
INSERT INTO phase_definitions VALUES 
(40, 0, 226, 0, 0, 683, 1, "Quest 26320, 'A Vision of the Past', Westfall - Sentinel Hill"),
(40, 1, 232, 0, 0, 683, 1, "Quest 26233, Rise of the Brotherhood, Westfall - Sentinel Hill");


DELETE FROM phase_area WHERE areaId=40;
INSERT INTO phase_area VALUES 
(40, 0, 26320, 26761, 66, 11, 1,"Quest 26320, 'A Vision of the Past', Westfall - Sentinel Hill"),
(40, 1, 26322, 26322, 74, 11, 3,"Quest 26233, Rise of the Brotherhood, Westfall - Sentinel Hill");

UPDATE creature SET zoneId=40, areaId=108, position_x=-10711.88, position_y=1029.754, position_z=34.52897, orientation=0.907397 WHERE id=594 AND guid=6243;
UPDATE creature SET zoneId=40, areaId=108, position_x=-10717.21, position_y=1037.21, position_z=34.52897, orientation=5.643349 WHERE id=42407 AND guid=275323;
UPDATE creature SET zoneId=40, areaId=108, position_x=-10718.53, position_y=1034.675, position_z=34.52897, orientation=0.42045 WHERE id=42407 AND guid=275321;
UPDATE creature SET zoneId=40, areaId=108, position_x=-10716.77, position_y=1035.486, position_z=34.52897, orientation=3.573828 WHERE id=594 AND guid=6245;
UPDATE creature SET zoneId=40, areaId=108, position_x=-10710.66, position_y=1032.839, position_z=34.52901, orientation=5.42736 WHERE id=42407 AND guid=275316;
UPDATE creature SET zoneId=40, areaId=108, position_x=-10713.95, position_y=1029.899, position_z=34.52901, orientation=0.063094 WHERE id=42407 AND guid=275320;

update creature_template_addon set auras="" where entry in (594,589,449);

UPDATE creature SET spawndist=0, MovementType=0 WHERE guid=251841;


 