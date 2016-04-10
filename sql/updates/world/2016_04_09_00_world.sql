
-- fix issue #117 
-- fix quest 27550
UPDATE locales_quest SET OfferRewardText_loc3="Der Teil von mir, der aus Gilneas stammte, starb an der Witterfront. Es bleibt nur Rache, $N. Und in der Hinsicht haben wir noch einiges zu tun. Erspart mir Eure sinnlosen Fragen.", CompletedText_loc3="Sprecht mit Lord Godfrey inm Silberwald" WHERE Id=27550;

UPDATE quest_template SET PrevQuestId=27542 WHERE Id=27550;

-- fix quest 27096
UPDATE locales_quest SET OfferRewardText_loc3="<Sylvanas zieht eine Augenbraue hoch.>$B$BAlso ist bei den Orcs alles in Ordnung?$B$B<Sylvanas liest das Empfehlungsschreiben.>$B$BIhre Vorräte zurückgeholt? Ein Dutzend Worgen getötet? Einen Ettin zur Strecke gebracht? Ihre Soldaten befreit und die Netzhuschermatriarchin vernichtet?$B$BIch sage das ja selten, aber ich bin beeindruckt. Vielleicht entsprechen Eure Fähigkeiten tatsächlich Euren Ambitionen. Wir werden sehen, ich werde Euch auf die Probe stellen." WHERE Id=27096;

-- fix quest 27097
update creature_template set AIName="", ScriptName="npc_agatha_44951" where entry=44951;

update creature_template set AIName="", ScriptName="" where entry=44959;

update creature_template set AIName="", ScriptName="npc_hillsbrad_refugee_44966" where entry=44966;

update creature_template set AIName="", ScriptName="npc_hillsbrad_refugee_44966" where entry=44954;

delete from creature where id in (1767, 1909, 1944, 44958, 44959, 44960, 44961, 44962, 44963, 44964, 44965);

delete from creature where id=1768 and guid in (6118, 6120, 66135, 66307, 66099, 65385, 65386, 65387, 64907, 66221, 66098);
delete from creature where id=1768 and guid in (66108, 65409, 65410, 65411, 65120, 60637, 66134, 57995, 57984);

SET @GUID=120363;
delete from creature where guid between @GUID and @GUID+42;
delete from creature where id in (44954, 44966);
insert into creature values
(@GUID+0, 44954, 0, 1, 1, 33979, 1, 735.089, 745.693, 36.5505, 3.31214, 300, 3, 0, 494, 0, 1, 0, 0, 0),
(@GUID+1, 44954, 0, 1, 1, 33979, 1, 1067.5, 739.682, 44.6044, 1.34563, 300, 3, 0, 494, 0, 1, 0, 0, 0),
(@GUID+2, 44954, 0, 1, 1, 33978, 1, 985.659, 738.325, 59.3645, 1.93725, 300, 3, 0, 494, 0, 1, 0, 0, 0),
(@GUID+3, 44954, 0, 1, 1, 33978, 1, 965.273, 729.008, 59.3923, 5.93129, 300, 3, 0, 494, 0, 1, 0, 0, 0),
(@GUID+4, 44954, 0, 1, 1, 33979, 1, 967.903, 592.802, 53.6101, 0.992163, 300, 3, 0, 494, 0, 1, 0, 0, 0),
(@GUID+5, 44954, 0, 1, 1, 33981, 1, 740.559, 704.448, 38.3997, 1.9765, 300, 3, 0, 494, 0, 1, 0, 0, 0),
(@GUID+6, 44954, 0, 1, 1, 33981, 1, 950.566, 627.721, 53.6142, 1.48353, 300, 3, 0, 494, 0, 1, 0, 0, 0),
(@GUID+7, 44954, 0, 1, 1, 33980, 1, 946.639, 696.479, 59.3605, 1.58825, 300, 3, 0, 494, 0, 1, 0, 0, 0),
(@GUID+8, 44954, 0, 1, 1, 33979, 1, 944.477, 694.101, 59.367, 3.26377, 300, 3, 0, 494, 0, 1, 0, 0, 0),
(@GUID+9, 44954, 0, 1, 1, 33981, 1, 747.786, 670.804, 47.1173, 5.59771, 300, 3, 0, 494, 0, 1, 0, 0, 0),
(@GUID+10, 44954, 0, 1, 1, 33980, 1, 749.685, 673.126, 46.7423, 5.59935, 300, 3, 0, 494, 0, 1, 0, 0, 0),
(@GUID+11, 44954, 0, 1, 1, 33980, 1, 823.939, 681.715, 53.6688, 3.08923, 300, 3, 0, 494, 0, 1, 0, 0, 0),
(@GUID+12, 44954, 0, 1, 1, 33978, 1, 879.397, 703.513, 55.7673, 4.96324, 300, 3, 0, 494, 0, 1, 0, 0, 0),
(@GUID+13, 44954, 0, 1, 1, 33980, 1, 844.26, 688.267, 53.8889, 3.10727, 300, 3, 0, 494, 0, 1, 0, 0, 0),
(@GUID+14, 44954, 0, 1, 1, 33980, 1, 826.406, 683.024, 53.7038, 2.56563, 300, 3, 0, 494, 0, 1, 0, 0, 0),
(@GUID+15, 44954, 0, 1, 1, 33979, 1, 913.314, 713.031, 55.2673, 2.43979, 300, 3, 0, 494, 0, 1, 0, 0, 0),
(@GUID+16, 44954, 0, 1, 1, 33981, 1, 953.439, 711.873, 59.2673, 5.64743, 300, 3, 0, 494, 0, 1, 0, 0, 0),
(@GUID+17, 44954, 0, 1, 1, 33979, 1, 913.96, 669.524, 53.5841, 2.1345, 300, 3, 0, 494, 0, 1, 0, 0, 0),
(@GUID+18, 44954, 0, 1, 1, 33980, 1, 912.052, 680.637, 53.635, 3.19395, 300, 3, 0, 494, 0, 1, 0, 0, 0),
(@GUID+19, 44954, 0, 1, 1, 33980, 1, 914.627, 697.276, 54.1919, 1.51844, 300, 3, 0, 494, 0, 1, 0, 0, 0),
(@GUID+20, 44966, 0, 1, 1, 33985, 1, 988.19, 605.527, 55.0663, 2.00529, 300, 3, 0, 546, 0, 1, 0, 0, 0),
(@GUID+21, 44966, 0, 1, 1, 33983, 1, 1079.59, 716.006, 45.6833, 3.06556, 300, 0, 0, 546, 0, 2, 0, 0, 0),
(@GUID+22, 44966, 0, 1, 1, 33982, 1, 1090.31, 712.209, 42.9922, 3.08757, 300, 3, 0, 546, 0, 1, 0, 0, 0),
(@GUID+23, 44966, 0, 1, 1, 33982, 1, 729.795, 760.619, 36.5505, 3.7779, 300, 3, 0, 546, 0, 1, 0, 0, 0),
(@GUID+24, 44966, 0, 1, 1, 33982, 1, 1022.21, 725.2, 60.2404, 0.10472, 300, 3, 0, 546, 0, 1, 0, 0, 0),
(@GUID+25, 44966, 0, 1, 1, 33984, 1, 1022.32, 728.483, 59.4135, 6.10865, 300, 3, 0, 546, 0, 1, 0, 0, 0),
(@GUID+26, 44966, 0, 1, 1, 33983, 1, 1003.08, 734.945, 59.2673, 1.63585, 300, 0, 0, 546, 0, 2, 0, 0, 0),
(@GUID+27, 44966, 0, 1, 1, 33982, 1, 1047.49, 725.92, 52.442, 4.75534, 300, 3, 0, 546, 0, 1, 0, 0, 0),
(@GUID+28, 44966, 0, 1, 1, 33984, 1, 977.24, 636.233, 53.7072, 3.03687, 300, 3, 0, 546, 0, 1, 0, 0, 0),
(@GUID+29, 44966, 0, 1, 1, 33982, 1, 977.925, 630.656, 53.4049, 2.98451, 300, 3, 0, 546, 0, 1, 0, 0, 0),
(@GUID+30, 44966, 0, 1, 1, 33985, 1, 1052.18, 692.916, 53.4623, 4.82914, 300, 3, 0, 546, 0, 1, 0, 0, 0),
(@GUID+31, 44966, 0, 1, 1, 33985, 1, 944.83, 681.802, 59.3483, 3.22886, 300, 3, 0, 546, 0, 1, 0, 0, 0),
(@GUID+32, 44966, 0, 1, 1, 33983, 1, 814.115, 589.747, 36.1269, 3.40038, 300, 3, 0, 546, 0, 1, 0, 0, 0),
(@GUID+33, 44966, 0, 1, 1, 33985, 1, 802.081, 591.858, 33.981, 3.21558, 300, 0, 0, 546, 0, 2, 0, 0, 0),
(@GUID+34, 44966, 0, 1, 1, 33982, 1, 818.667, 693.582, 53.7265, 3.85718, 300, 3, 0, 546, 0, 1, 0, 0, 0),
(@GUID+35, 44966, 0, 1, 1, 33982, 1, 855.63, 680.262, 53.6077, 2.6529, 300, 3, 0, 546, 0, 1, 0, 0, 0),
(@GUID+36, 44966, 0, 1, 1, 33983, 1, 821.964, 692.889, 53.4492, 3.97935, 300, 3, 0, 546, 0, 1, 0, 0, 0),
(@GUID+37, 44966, 0, 1, 1, 33985, 1, 944.193, 679.759, 59.3609, 3.28122, 300, 3, 0, 546, 0, 1, 0, 0, 0),
(@GUID+38, 44966, 0, 1, 1, 33983, 1, 878.703, 672.145, 55.223, 2.2572, 300, 3, 0, 546, 0, 1, 0, 0, 0),
(@GUID+39, 44966, 0, 1, 1, 33985, 1, 854.613, 696.894, 53.6658, 3.35103, 300, 3, 0, 546, 0, 1, 0, 0, 0),
(@GUID+40, 44966, 0, 1, 1, 33982, 1, 914.627, 697.276, 54.1919, 1.51844, 300, 3, 0, 546, 0, 1, 0, 0, 0),
(@GUID+41, 44966, 0, 1, 1, 33982, 1, 912.061, 693.785, 53.6937, 3.15905, 300, 3, 0, 546, 0, 1, 0, 0, 0),
(@GUID+42, 44966, 0, 1, 1, 33983, 1, 912.052, 680.637, 53.635, 3.19395, 300, 3, 0, 546, 0, 1, 0, 0, 0);

SET @GUID=120384;
UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;
INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;
DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, 1095.38, 715.004, 41.1172, 0, 0, 0),
(@GUID, 1, 1094.38, 714.918, 41.1172, 0, 0, 0),
(@GUID, 2, 1092.39, 715.065, 41.8672, 0, 0, 0),
(@GUID, 3, 1090.39, 715.211, 42.6172, 0, 0, 0),
(@GUID, 4, 1088.4, 715.357, 43.2422, 0, 0, 0),
(@GUID, 5, 1086.4, 715.504, 44.1172, 0, 0, 0),
(@GUID, 6, 1082.42, 715.797, 44.8672, 0, 0, 0),
(@GUID, 7, 1080.42, 715.943, 45.4922, 0, 0, 0),
(@GUID, 8, 1078.26, 716.108, 45.9922, 0, 0, 0),
(@GUID, 9, 1078.26, 716.108, 45.9922, 0, 0, 0);

SET @GUID=120389;
UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;
INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;
DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, 1003.4, 733.004, 59.2673, 0, 0, 0),
(@GUID, 1, 1003.27, 732.014, 59.2673, 0, 0, 0),
(@GUID, 2, 1003.02, 735.855, 59.2673, 0, 0, 0),
(@GUID, 3, 1003.02, 735.855, 59.2673, 0, 0, 0);

SET @GUID=120396;
UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;
INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;
DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, 805.073, 592.08, 34.1269, 0, 0, 0),
(@GUID, 1, 804.076, 592.006, 34.1269, 0, 0, 0),
(@GUID, 2, 799.92, 591.698, 33.8231, 0, 0, 0),
(@GUID, 3, 799.92, 591.698, 33.8231, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=35706;


