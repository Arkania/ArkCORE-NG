
-- fix issue #117 quest 27099
update creature_template set AIName="", ScriptName="npc_fenris_keep_stalker_45032" where entry=45032;

delete from creature where id=1947 and guid=6087;

update creature set spawndist=0, MovementType=0 where id=45032 and guid=53491;

update creature_template set InhabitType=5, AIName="", ScriptName="npc_camera_45003" where entry=45003;

DELETE FROM creature_text where entry=44989 and groupid between 0 and 5;
INSERT INTO creature_text values 
(44989, 0, 0, "The Forsaken have broken through your defenses, magistrate.", 12, 0, 100, 396, 0, 0, "", 45161),
(44989, 1, 0, "You are out of time.", 12, 0, 100, 274, 0, 0, "", 45162),
(44989, 2, 0, "A decision must be made!", 12, 0, 100, 5, 0, 0, "", 45163),
(44989, 3, 0, "Die in battle and be raised as a servant of the Forsaken or...", 12, 0, 100, 396, 0, 0, "", 45164),
(44989, 4, 0, "Drink in my blood and be reborn as worgen, immune to the depravity of the Forsaken.", 12, 0, 100, 396, 0, 0, "", 45165),
(44989, 5, 0, "Help us destroy the Forsaken and retake Lordaeron for the Alliance!", 12, 0, 100, 5, 0, 0, "", 45166);

DELETE FROM creature_text where entry=44996 and groupid in (0, 1);
INSERT INTO creature_text values 
(44996, 0, 0, "We would rather die than be turned into worgen, but seeing as how even death provides no relief from the atrocities of this war...", 12, 0, 100, 1, 0, 0, "", 45167),
(44996, 1, 0, "We choose vengeance!", 12, 0, 100, 5, 0, 0, "", 45168);

DELETE FROM creature_text where entry=44951 and groupid in (2, 3);
INSERT INTO creature_text values 
(44951, 2, 0, "Run...", 12, 0, 100, 457, 0, 0, "", 45184),
(44951, 3, 0, "RUN!", 12, 0, 100, 457, 0, 0, "", 45185);

update creature_template set AIName="", ScriptName="npc_camera_45003" where entry=45003;
update creature_template set AIName="", ScriptName="npc_lord_darius_crowley_44989" where entry=44989;
update creature_template set AIName="", ScriptName="npc_phin_odelic_44993" where entry=44993;
update creature_template set AIName="", ScriptName="npc_bartolo_ginsetti_44994" where entry=44994;
update creature_template set AIName="", ScriptName="npc_loremaster_dibbs_44995" where entry=44995;
update creature_template set AIName="", ScriptName="npc_magistrate_henry_maleb_44996" where entry=44996;
update creature_template set AIName="", ScriptName="npc_caretaker_smithers_44997" where entry=44997;
update creature_template set AIName="", ScriptName="npc_sophia_zwoski_45002" where entry=45002;

SET @GUID=4495101;
DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, 978.1359, 701.0002, 74.89857, 1.469464, 0, 1),
(@GUID, 1, 980.0945, 707.5026, 74.89857, 0.53484, 0, 1),
(@GUID, 2, 983.2339, 707.6531, 74.79117, 0.047892, 0, 1),
(@GUID, 3, 993.0419, 708.1599, 69.7968, 0.051819, 0, 1),
(@GUID, 4, 996.8337, 706.6511, 69.7968, 5.903038, 0, 1),
(@GUID, 5, 997.8134, 685.7626, 69.7968, 4.756361, 0, 1),
(@GUID, 6, 1000.605, 683.2662, 69.7968, 5.55354, 0, 1),
(@GUID, 7, 1008.984, 683.5966, 64.96407, 0.051824, 0, 1),
(@GUID, 8, 1011.667, 683.7565, 64.90376, 0.201049, 0, 1),
(@GUID, 9, 1013.713, 686.3148, 64.90376, 0.93147, 0, 1),
(@GUID, 10, 1012.84, 692.0942, 60.97515, 1.720795, 0, 1),
(@GUID, 11, 1009.927, 696.0195, 60.97515, 2.247012, 0, 1),
(@GUID, 12, 999.3065, 695.5478, 60.97515, 3.162001, 0, 1),
(@GUID, 13, 995.6049, 697.9961, 60.97515, 2.557245, 0, 1),
(@GUID, 14, 996.0381, 708.152, 60.97515, 1.744357, 0, 1),
(@GUID, 15, 991.2772, 712.1159, 60.97515, 2.447289, 0, 1),
(@GUID, 16, 987.5659, 711.0661, 60.97515, 3.417256, 0, 1),
(@GUID, 17, 983.5695, 705.4751, 60.97515, 4.120186, 0, 1),
(@GUID, 18, 983.7156, 694.2731, 59.48418, 4.701381, 0, 1),
(@GUID, 19, 978.3207, 688.5763, 59.45862, 3.939546, 0, 1),
(@GUID, 20, 972.1443, 689.1495, 59.73647, 3.18618, 0, 1),
(@GUID, 21, 947.125, 688.8077, 59.73647, 3.119421, 0, 1),
(@GUID, 22, 940.7419, 692.6727, 59.28345, 2.58535, 0, 1),
(@GUID, 23, 942.0499, 710.1451, 59.30516, 1.411179, 0, 1),
(@GUID, 24, 962.5223, 728.5516, 59.28381, 0.70432, 0, 1),
(@GUID, 25, 1005.039, 732.6902, 59.26571, 6.10786, 0, 1),
(@GUID, 26, 1011.227, 727.5854, 59.5486, 5.593425, 0, 1),
(@GUID, 27, 1027.919, 725.5515, 58.62294, 6.186398, 0, 1),
(@GUID, 28, 1034.905, 726.7658, 54.57361, 6.151052, 0, 1),
(@GUID, 29, 1045.765, 725.6252, 53.04143, 6.178541, 0, 1),
(@GUID, 30, 1075.915, 722.2546, 45.57275, 6.16676, 0, 1),
(@GUID, 31, 1093.561, 720.1909, 40.58342, 6.16676, 0, 1),
(@GUID, 32, 1117.21, 719.6275, 32.31801, 0.068142, 0, 1),
(@GUID, 33, 1192.305, 909.5518, 32.97552, 1.226605, 0, 1),
(@GUID, 34, 1204.633, 938.8166, 35.41784, 1.1677, 0, 1),
(@GUID, 35, 1222.831, 979.2708, 36.98741, 1.12843, 0, 1),
(@GUID, 36, 1229.703, 991.4185, 36.01954, 1.061671, 0, 1),
(@GUID, 37, 1252.699, 1031.865, 42.21674, 1.053817, 0, 1),
(@GUID, 38, 1265.049, 1043.249, 45.64476, 0.712169, 0, 1),
(@GUID, 39, 1275.689, 1048.93, 54.42715, 0.331248, 0, 1),
(@GUID, 40, 1311.694, 1060.33, 54.59864, 0.327321, 0, 1),
(@GUID, 41, 1367.728, 1050.514, 53.25192, 6.103925, 0, 1),
(@GUID, 42, 1379.508, 1044.309, 54.09616, 5.793697, 0, 1);


