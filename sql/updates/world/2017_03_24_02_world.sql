
DELETE FROM creature WHERE id=234 AND guid IN (10755);

DELETE FROM creature WHERE guid IN (4018, 6682);
INSERT INTO creature VALUES 
(4018, 234, 0, 0, 0, 1, 226, 0, 0, 0, -10558.2, 1043.74, 57.4103, 3.22886, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(6682, 234, 0, 0, 0, 1, 0, 0, 0, 1, -10508.8, 1045.23, 60.518, 1.29154, 120, 0, 0, 1, 0, 0, 0, 0, 0);

UPDATE creature SET phaseId=226 WHERE guid=6661;

UPDATE creature SET phaseId=226 WHERE guid=6662;

DELETE FROM creature WHERE guid IN (5806);
INSERT INTO creature VALUES 
(5806, 489, 0, 0, 0, 1, 226, 0, 0, 0, -10541.7, 1041.73, 56.6891, 3.22886, 120, 0, 0, 1, 0, 0, 0, 0, 0);

UPDATE creature SET phaseId=226 WHERE guid=6657;

DELETE FROM creature WHERE guid IN (658, 659, 42608);
INSERT INTO creature VALUES 
(658, 491, 0, 0, 0, 1, 226, 0, 0, 0, -10500.6, 1021.59, 60.6106, 1.8326, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(659, 491, 36, 0, 0, 6, 0, 0, 3342, 1, -60.6806, -406.563, 55.2114, 1.76278, 120, 0, 0, 484, 0, 0, 0, 0, 0), 
(42608, 491, 0, 0, 0, 1, 169, 0, 3342, 0, -10500.6, 1021.59, 60.6106, 1.8326, 120, 0, 0, 484, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE guid IN (6593, 42283);
INSERT INTO creature VALUES 
(6593, 523, 0, 0, 0, 1, 226, 0, 0, 0, -10553.6, 1034.42, 57.0394, 0.0174533, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(42283, 523, 0, 0, 0, 1, 169, 0, 3263, 0, -10553.6, 1034.42, 57.0394, 0.017453, 120, 0, 0, 232470, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE guid IN (6599, 7089);
INSERT INTO creature VALUES 
(6599, 820, 0, 0, 0, 1, 226, 0, 0, 0, -10504.8, 1033.25, 95.7959, 4.43314, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(7089, 820, 0, 0, 0, 1, 169, 0, 2374, 0, -10504.8, 1033.25, 95.7958, 4.43314, 120, 0, 0, 1003, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE guid IN (6715, 7088);
INSERT INTO creature VALUES 
(6715, 821, 0, 0, 0, 1, 226, 0, 0, 0, -10554.6, 1041.32, 57.1813, 3.20759, 120, 0, 0, 1221, 0, 0, 0, 0, 0), 
(7088, 821, 0, 0, 0, 1, 169, 0, 2372, 0, -10511.2, 1041.84, 60.7013, 1.50098, 120, 0, 0, 1221, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE guid IN (7168, 13630);
INSERT INTO creature VALUES 
(7168, 843, 0, 0, 0, 1, 169, 0, 3260, 0, -10661.2, 999.356, 32.9575, 0.628319, 120, 0, 0, 328, 0, 0, 0, 0, 0), 
(13630, 843, 0, 0, 0, 1, 226, 0, 0, 0, -10509.4, 1046.86, 60.5188, 5.11567, 120, 0, 0, 328, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE guid IN (6993, 42823);
INSERT INTO creature VALUES 
(6993, 870, 0, 0, 0, 1, 0, 0, 0, 1, -10660.2, 1096.6, 33.7965, 5.34071, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(42823, 870, 0, 0, 0, 1, 226, 0, 0, 0, -10544.4, 1038.12, 56.6851, 3.14159, 120, 0, 0, 1, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE guid IN (6713, 6992);
INSERT INTO creature VALUES 
(6713, 876, 0, 0, 0, 1, 226, 0, 0, 0, -10546.7, 1039.88, 56.591, 3.1801, 120, 0, 0, 1910, 0, 0, 0, 0, 0), 
(6992, 876, 0, 0, 0, 1, 169, 0, 2370, 0, -10638.6, 1095.89, 33.6951, 2.61102, 120, 5, 0, 1910, 0, 1, 0, 0, 0);

DELETE FROM creature WHERE guid IN (6714, 43587);
INSERT INTO creature VALUES 
(6714, 878, 0, 0, 0, 1, 226, 0, 0, 0, -10554.7, 1045.52, 57.4031, 3.22329, 120, 0, 0, 1003, 0, 0, 0, 0, 0), 
(43587, 878, 0, 0, 0, 1, 169, 0, 2373, 0, -10504.7, 1042.87, 60.6013, 1.93731, 120, 0, 0, 1003, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE guid IN (7167, 13628);
INSERT INTO creature VALUES 
(7167, 1668, 0, 0, 0, 1, 169, 0, 3259, 0, -10658.5, 996.851, 32.9575, 0.872665, 120, 0, 0, 328, 0, 0, 0, 0, 0), 
(13628, 1668, 0, 0, 0, 1, 226, 0, 0, 0, -10512.5, 1043.09, 60.5188, 0.411456, 120, 0, 0, 328, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE guid IN (7170, 13629);
INSERT INTO creature VALUES 
(7170, 1670, 0, 0, 0, 1, 169, 0, 3262, 0, -10653.3, 995.395, 32.9575, 1.6057, 120, 0, 0, 484, 0, 0, 0, 0, 0), 
(13629, 1670, 0, 0, 0, 1, 226, 0, 0, 0, -10506.9, 1044.9, 60.5188, 2.47673, 120, 0, 0, 484, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE guid=6628;
INSERT INTO creature VALUES 
(6628, 6180, 0, 0, 0, 1, 226, 0, 0, 0, -10505.7, 1244.8, 43.5787, 4.43218, 120, 0, 0, 1, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE guid IN (13626, 42546);
INSERT INTO creature VALUES 
(13626, 8931, 0, 0, 0, 1, 226, 0, 0, 0, -10501.6, 1027.79, 60.5223, 2.00593, 120, 0, 0, 955, 0, 0, 0, 0, 0), 
(42546, 8931, 0, 0, 0, 1, 169, 0, 8185, 0, -10653.3, 1166.43, 34.9278, 5.77704, 120, 0, 0, 955, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE guid IN (7086, 13625);
INSERT INTO creature VALUES 
(7086, 8934, 0, 0, 0, 1, 169, 0, 8186, 0, -10632.6, 1188.78, 35.3057, 3.33358, 120, 0, 0, 1003, 0, 0, 0, 0, 0), 
(13625, 8934, 0, 0, 0, 1, 226, 0, 0, 0, -10498.9, 1022.02, 60.526, 1.90382, 120, 0, 0, 1003, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE guid IN (7087, 13627);
INSERT INTO creature VALUES 
(7087, 10045, 0, 0, 0, 1, 169, 0, 9265, 0, -10638.3, 1163.87, 33.5578, 5.51524, 120, 0, 0, 1003, 0, 0, 0, 0, 0), 
(13627, 10045, 0, 0, 0, 1, 226, 0, 0, 0, -10509.7, 1040.33, 60.5188, 1.9348, 120, 0, 0, 955, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE guid IN (6718, 43161);
INSERT INTO creature VALUES 
(6718, 43011, 0, 0, 0, 1, 226, 0, 0, 0, -10511.3, 1026.04, 68.4086, 1.2009, 120, 0, 0, 610, 655, 0, 0, 0, 0), 
(43161, 43011, 0, 0, 0, 1, 169, 0, 33175, 0, -10642.7, 1187.93, 34.2248, 4.11898, 120, 0, 0, 610, 655, 0, 0, 0, 0);

DELETE FROM creature WHERE guid IN (6719, 43624);
INSERT INTO creature VALUES 
(6719, 49736, 0, 0, 0, 1, 226, 0, 0, 0, -10493, 1032.02, 60.5226, 2.73243, 120, 0, 0, 699, 0, 0, 0, 0, 0), 
(43624, 49736, 0, 0, 0, 1, 169, 0, 36589, 0, -10657.5, 1172.18, 34.5962, 4.08407, 120, 0, 0, 699, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE guid IN (6816, 42921);
INSERT INTO creature VALUES 
(6816, 49741, 0, 0, 0, 1, 226, 0, 0, 0, -10495.5, 1034.84, 60.5225, 4.1972, 120, 0, 0, 699, 0, 0, 0, 0, 0), 
(42921, 49741, 0, 0, 0, 1, 169, 0, 36590, 0, -10658.9, 1170.22, 34.5723, 0.925025, 120, 0, 0, 699, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE guid IN (6756, 42498);
INSERT INTO creature VALUES 
(6756, 49745, 0, 0, 0, 1, 226, 0, 0, 0, -10511.8, 1026.09, 60.5238, 0.0934805, 120, 0, 0, 699, 0, 0, 0, 0, 0), 
(42498, 49745, 0, 0, 0, 1, 169, 0, 36593, 0, -10634.9, 1191.04, 34.3522, 3.97935, 120, 0, 0, 699, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE guid IN (13624, 42685);
INSERT INTO creature VALUES 
(13624, 49749, 0, 0, 0, 1, 226, 0, 0, 0, -10504.9, 1022.98, 60.5267, 1.12235, 120, 0, 0, 562, 5502, 0, 0, 0, 0), 
(42685, 49749, 0, 0, 0, 1, 169, 0, 36602, 0, -10654.8, 1177.42, 34.6437, 5.70723, 120, 0, 0, 562, 1633, 0, 0, 0, 0);

DELETE FROM creature WHERE guid IN (6717, 43403);
INSERT INTO creature VALUES 
(6717, 49760, 0, 0, 0, 1, 226, 0, 0, 0, -10510.6, 1028.79, 68.4093, 4.43674, 120, 0, 0, 699, 0, 0, 0, 0, 0), 
(43403, 49760, 0, 0, 0, 1, 169, 0, 36606, 0, -10644.2, 1185.94, 34.173, 0.890118, 120, 0, 0, 699, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE guid IN (6720, 42747);
INSERT INTO creature VALUES 
(6720, 49769, 0, 0, 0, 1, 226, 0, 0, 0, -10496.6, 1031.6, 60.5225, 0.81998, 120, 0, 0, 699, 0, 0, 0, 0, 0), 
(42747, 49769, 0, 0, 0, 1, 169, 0, 36610, 0, -10645.4, 1167.11, 34.5441, 4.03344, 120, 0, 0, 699, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE guid IN (6656, 53345);
INSERT INTO creature VALUES 
(6656, 52190, 0, 0, 0, 1, 226, 0, 0, 0, -10639.8, 997.01, 33.3108, 0.925025, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(53345, 52190, 0, 0, 0, 1, 169, 0, 37802, 0, -10639.8, 997.01, 33.3108, 0.925025, 120, 0, 0, 328, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=18543;
DELETE FROM creature_addon WHERE guid=18542;
DELETE FROM creature_addon WHERE guid=18540;
DELETE FROM creature_addon WHERE guid=43480;
DELETE FROM creature_addon WHERE guid=18539;
DELETE FROM creature_addon WHERE guid=23423;
DELETE FROM creature_addon WHERE guid=43638;
DELETE FROM creature_addon WHERE guid=43606;
DELETE FROM creature_addon WHERE guid=43588;
DELETE FROM creature_addon WHERE guid=43570;
DELETE FROM creature_addon WHERE guid=43546;
DELETE FROM creature_addon WHERE guid=43524;
DELETE FROM creature_addon WHERE guid=43523;
DELETE FROM creature_addon WHERE guid=43518;
DELETE FROM creature_addon WHERE guid=43468;
DELETE FROM creature_addon WHERE guid=43411;
DELETE FROM creature_addon WHERE guid=43377;
DELETE FROM creature_addon WHERE guid=43341;
DELETE FROM creature_addon WHERE guid=43324;
DELETE FROM creature_addon WHERE guid=43316;
DELETE FROM creature_addon WHERE guid=43248;
DELETE FROM creature_addon WHERE guid=43235;
DELETE FROM creature_addon WHERE guid=43228;
DELETE FROM creature_addon WHERE guid=43180;
DELETE FROM creature_addon WHERE guid=43103;
DELETE FROM creature_addon WHERE guid=43072;
DELETE FROM creature_addon WHERE guid=43061;
DELETE FROM creature_addon WHERE guid=43007;
DELETE FROM creature_addon WHERE guid=42953;
DELETE FROM creature_addon WHERE guid=42898;
DELETE FROM creature_addon WHERE guid=42864;
DELETE FROM creature_addon WHERE guid=42841;
DELETE FROM creature_addon WHERE guid=42799;
DELETE FROM creature_addon WHERE guid=42757;
DELETE FROM creature_addon WHERE guid=42752;
DELETE FROM creature_addon WHERE guid=42730;
DELETE FROM creature_addon WHERE guid=42678;
DELETE FROM creature_addon WHERE guid=42649;
DELETE FROM creature_addon WHERE guid=42637;
DELETE FROM creature_addon WHERE guid=42597;
DELETE FROM creature_addon WHERE guid=42585;
DELETE FROM creature_addon WHERE guid=42514;
DELETE FROM creature_addon WHERE guid=42475;
DELETE FROM creature_addon WHERE guid=42413;
DELETE FROM creature_addon WHERE guid=42387;
DELETE FROM creature_addon WHERE guid=42386;
DELETE FROM creature_addon WHERE guid=42385;
DELETE FROM creature_addon WHERE guid=42370;
DELETE FROM creature_addon WHERE guid=42342;
DELETE FROM creature_addon WHERE guid=42326;
DELETE FROM creature_addon WHERE guid=6930;






