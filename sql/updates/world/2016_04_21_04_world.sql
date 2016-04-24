
-- fix issue #137
delete from creature where id=56003 and guid=252304;

update creature_template set gossip_menu_id=0 where entry=56003;

delete from smart_scripts where entryorguid=56003;

delete from gossip_menu where entry=56003;

delete from gossip_menu_option where menu_id=56003;

delete from creature_queststarter where quest=30001;
 
delete from creature_questender where quest=30001;

delete from quest_template where id=30001;

delete from gameobject where id=196864 and guid=166784;

delete from gameobject where id=196863 and guid=166783;

delete from creature where id=36741 and guid=250065;

update creature_template set AIName="", ScriptName="npc_gwen_armstead_36452" where entry=36452;

update creature_template set AIName="", ScriptName="npc_swift_mountain_horse_36741" where entry=36741;

UPDATE quest_template SET Flags=262144 WHERE Id=14465;

update gameobject set phaseMask=262143 where guid in (166781, 166771, 166787);

delete from creature where id=38853 and guid=278398;

SET @PATHID=3674101;
DELETE FROM waypoint_data WHERE id=@PATHID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@PATHID, 0, -1897.703, 2257.397, 42.32381, 0.799122, 1000, 1),
(@PATHID, 1, -1853.44, 2299.385, 42.13757, 0.732363, 0, 1),
(@PATHID, 2, -1824.017, 2326.213, 36.89969, 0.697021, 0, 1),
(@PATHID, 3, -1798.012, 2346.52, 35.8257, 0.677386, 0, 1),
(@PATHID, 4, -1785.973, 2361.786, 38.47665, 1.266434, 0, 1),
(@PATHID, 5, -1772.397, 2439.341, 60.04873, 1.407805, 0, 1),
(@PATHID, 6, -1764.861, 2455.944, 65.20289, 1.144697, 0, 1),
(@PATHID, 7, -1751.963, 2463.264, 69.94237, 0.422131, 0, 1),
(@PATHID, 8, -1706.282, 2465.77, 83.86064, 0.123679, 0, 1),
(@PATHID, 9, -1687.379, 2498.784, 96.6995, 0.995471, 0, 1),
(@PATHID, 10, -1683.193, 2503.998, 97.65395, 0.995471, 0, 1),
(@PATHID, 11, -1669.508, 2520.815, 97.92444, 0.858027, 1000, 1);

update gameobject_template set type=0, faction=114, flags=32 where entry=196399; -- should be type 33: destructive building.

update gameobject_template set type=0, faction=114, flags=32 where entry=196401; -- should be type 33: destructive building.

update gameobject_template set type=0, faction=114, flags=32 where entry=196412; -- should be type 33: destructive building.

delete from gameobject where id=180322 and guid=400165;

SET @HARNESS=38755; 
SET @CAR=44928; SET @COMC="Car";
SET @HORSE=43338; SET @COMH="Horse";
SET @PASS1=38853; SET @COM1="Marie Allen";
SET @PASS2=44460; SET @COM2="Gwen Armstead ";
SET @PASS3=36138; SET @COM3="Krennan Aranas";
SET @PASS4=43907; SET @COM4="Duskhaven Watchman";
SET @PASS5=37946; SET @COM5="Duskhaven Watchman";
SET @PASS6=51409; SET @COM6="Lorna Crowley";

delete from vehicle_template_accessory where entry in (@CAR, @HARNESS);
insert into vehicle_template_accessory values
(@HARNESS, @HORSE, 0, 1, @COMH, 8, 0),
(@HARNESS, @HORSE, 1, 1, @COMH, 8, 0),
(@HARNESS, @CAR  , 2, 1, @COMC, 8, 0),
(@CAR,     @PASS1, 1, 1, @COM1, 8, 0),
(@CAR,     @PASS2, 2, 1, @COM2, 8, 0),
(@CAR,     @PASS3, 3, 1, @COM3, 8, 0),
(@CAR,     @PASS4, 4, 1, @COM4, 8, 0),
(@CAR,     @PASS5, 5, 1, @COM5, 8, 0),
(@CAR,     @PASS6, 6, 1, @COM6, 8, 0);

delete from npc_spellclick_spells where npc_entry in (@HARNESS, @HORSE, @CAR, @PASS1, @PASS2, @PASS3, @PASS4, @PASS5, @PASS6);
insert into npc_spellclick_spells values
(@HARNESS, 46598, 0, 0),
(@HORSE,   46598, 0, 0),
(@CAR,     46598, 0, 0),
(@PASS1,   46598, 0, 0),
(@PASS2,   46598, 0, 0),
(@PASS3,   46598, 0, 0),
(@PASS4,   46598, 0, 0),
(@PASS5,   46598, 0, 0),
(@PASS6,   46598, 0, 0);

UPDATE creature_template SET npcflag=16777217 WHERE entry=44928;

delete from creature where guid in (252305, 252307, 252308);

delete from creature where id=36606 and guid=251988;

UPDATE quest_template SET RewardSpell=0, Flags=1310728 WHERE Id=14466;

UPDATE quest_template SET Method=2, NextQuestId=0, Flags=2097160 WHERE Id=14467;

UPDATE quest_template SET PrevQuestId=14467, Flags=2359304 WHERE Id=24438;

update creature_template set AIName="", ScriptName="npc_queen_mia_greymane_36606" where entry=36606;

update creature_template set AIName="", ScriptName="npc_king_genn_greymane_36743" where entry=36743;

delete from gameobject_template where entry=197334;
INSERT INTO `gameobject_template` VALUES 
(197334, 13, 9146, "King Greymane\'s Telescope", "", "", "", 0, 16, 0.76, 0, 0, 0, 0, 0, 0, 0, 167, 22483, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 1);

delete from gameobject where guid=46318 and id=197334;
INSERT INTO `gameobject` VALUES (46318, 197334, 654, 1, 65535, -1513.67, 2606.96, 203.5252, 0.182989, 0, 0, 0, 0, 300, 0, 0);

DELETE FROM spell_phase WHERE spell_id=68483;
INSERT INTO spell_phase (spell_id, phasemask, terrainswapmap, worldmapareaswap) VALUES 
(68483, 16384, 655, 678);

DELETE FROM spell_phase WHERE spell_id=69077;
INSERT INTO spell_phase (spell_id, phasemask, terrainswapmap, worldmapareaswap) VALUES 
(69077, 32768, 0, 0);

DELETE FROM spell_phase WHERE spell_id=69484;
INSERT INTO spell_phase (spell_id, phasemask, terrainswapmap, worldmapareaswap) VALUES 
(69484, 131072, 656, 679);

SET @PATHID=4492801;
DELETE FROM waypoint_data WHERE id=@PATHID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@PATHID, 0, -1677.377, 2516.294, 97.89328, 4.30266, 0, 1),
(@PATHID, 1, -1678.95, 2512.673, 97.89328, 4.286952, 1, 1), -- open door 197401
(@PATHID, 2, -1687.499, 2500.815, 97.02721, 4.314443, 0, 1),
(@PATHID, 3, -1704.147, 2472.054, 86.20731, 4.196633, 0, 1),
(@PATHID, 4, -1698.867, 2445.326, 80.09706, 4.907414, 0, 1),
(@PATHID, 5, -1701.86, 2428.852, 74.75138, 4.538277, 0, 1),
(@PATHID, 6, -1719.459, 2404.089, 63.65119, 4.094529, 0, 1),
(@PATHID, 7, -1729.933, 2379.973, 60.37991, 4.302658, 0, 1),
(@PATHID, 8, -1746.551, 2339.364, 68.19585, 4.491152, 0, 1),
(@PATHID, 9, -1760.25, 2297.375, 76.62185, 4.361562, 0, 1),
(@PATHID, 10, -1784.243, 2262.901, 84.16702, 4.114161, 0, 1),
(@PATHID, 11, -1801.918, 2250.852, 88.05366, 3.73717, 0, 1),
(@PATHID, 12, -1826.04, 2240.113, 89.31554, 3.560455, 0, 1),
(@PATHID, 13, -1867.802, 2175.622, 89.31554, 4.137723, 0, 1),
(@PATHID, 14, -1873.229, 2125.262, 89.31554, 4.605035, 0, 1),
(@PATHID, 15, -1872.935, 2089.737, 89.31554, 4.70321, 1, 1), -- open door 196412
(@PATHID, 16, -1874.611, 2063.415, 89.31799, 4.334078, 0, 1),
(@PATHID, 17, -1885.149, 2034.266, 89.31799, 4.365494, 0, 1),
(@PATHID, 18, -1886.153, 2004.3, 89.31799, 4.699288, 0, 1),
(@PATHID, 19, -1874.461, 1959.722, 89.14916, 4.923126, 0, 1),
(@PATHID, 20, -1877.806, 1928.259, 89.13686, 4.601116, 0, 1),
(@PATHID, 21, -1886.061, 1908.403, 89.15066, 4.318374, 0, 1),
(@PATHID, 22, -1905.365, 1902.492, 89.28486, 3.399458, 0, 1),
(@PATHID, 23, -1999.603, 1902.787, 89.29601, 3.159912, 0, 1),
(@PATHID, 24, -2020.971, 1911.697, 86.82968, 2.727942, 0, 1),
(@PATHID, 25, -2046.525, 1915.164, 80.40865, 3.006759, 0, 1),
(@PATHID, 26, -2068.034, 1903.729, 70.74565, 3.611516, 0, 1),
(@PATHID, 27, -2097.354, 1877.561, 50.75932, 3.851062, 0, 1),
(@PATHID, 28, -2106.137, 1863.109, 43.22727, 4.16522, 0, 1),
(@PATHID, 29, -2117.601, 1836.219, 31.68614, 4.294808, 0, 1),
(@PATHID, 30, -2150.546, 1813.513, 17.86472, 3.74503, 0, 1),
(@PATHID, 31, -2172.291, 1810.452, 13.28982, 3.348404, 0, 1),
(@PATHID, 32, -2182.513, 1806.792, 12.50777, 3.242377, 0, 1),
(@PATHID, 33, -2213.215, 1808.384, 11.82914, 3.12064, 1, 1), -- eject player
(@PATHID, 34, -2245.987, 1800.968, 11.94947, 3.379822, 0, 1),
(@PATHID, 35, -2267.334, 1792.831, 11.70791, 3.493704, 0, 1),
(@PATHID, 36, -2301.925, 1781.58, 11.23015, 3.521193, 0, 1),
(@PATHID, 37, -2317.021, 1766.306, 10.93367, 3.941382, 0, 1),
(@PATHID, 38, -2372.177, 1708.57, 11.27532, 3.929601, 0, 1),
(@PATHID, 39, -2384.742, 1684.459, 10.85017, 4.231979, 0, 1),
(@PATHID, 40, -2394.802, 1658.367, 11.11809, 4.357642, 0, 1),
(@PATHID, 41, -2435.95, 1627.049, 12.63173, 3.792156, 0, 1),
(@PATHID, 42, -2464.311, 1609.2, 14.6012, 3.788229, 0, 1),
(@PATHID, 43, -2476.106, 1591.893, 16.10364, 4.114169, 0, 1),
(@PATHID, 44, -2478.144, 1576.207, 16.26113, 4.550061, 0, 1); -- despawn

SET @HARNESS=43336; 
SET @CAR=43337;   SET @COMC="Car";
SET @HORSE=43338; SET @COMH="Horse";
SET @PASS1=38853; SET @COM1="Marie Allen";
SET @PASS2=44460; SET @COM2="Gwen Armstead ";
SET @PASS3=36138; SET @COM3="Krennan Aranas";
SET @PASS4=43907; SET @COM4="Duskhaven Watchman";
SET @PASS5=37946; SET @COM5="Duskhaven Watchman";
SET @PASS6=51409; SET @COM6="Lorna Crowley";

delete from vehicle_template_accessory where entry in (@HARNESS, @CAR);
insert into vehicle_template_accessory values
(@HARNESS, @HORSE, 0, 1, @COMH, 8, 0),
(@HARNESS, @HORSE, 1, 1, @COMH, 8, 0),
(@HARNESS, @CAR  , 2, 1, @COMC, 8, 0),
(@CAR,     @PASS1, 1, 1, @COM1, 8, 0),
(@CAR,     @PASS2, 2, 1, @COM2, 8, 0),
(@CAR,     @PASS3, 3, 1, @COM3, 8, 0),
(@CAR,     @PASS4, 4, 1, @COM4, 8, 0),
(@CAR,     @PASS5, 5, 1, @COM5, 8, 0),
(@CAR,     @PASS6, 6, 1, @COM6, 8, 0);

delete from npc_spellclick_spells where npc_entry in (@HARNESS, @HORSE, @CAR, @PASS1, @PASS2, @PASS3, @PASS4, @PASS5, @PASS6);
insert into npc_spellclick_spells values
(@HARNESS, 46598, 0, 0),
(@HORSE,   46598, 0, 0),
(@CAR,     46598, 0, 0),
(@PASS1,   46598, 0, 0),
(@PASS2,   46598, 0, 0),
(@PASS3,   46598, 0, 0),
(@PASS4,   46598, 0, 0),
(@PASS5,   46598, 0, 0),
(@PASS6,   46598, 0, 0);

update creature_template set AIName="", ScriptName="npc_harness_43336" where entry=43336;

update creature_template set AIName="", ScriptName="npc_stagecoach_carriage_43337" where entry=43337;

update creature_template set AIName="", ScriptName="npc_stagecoach_carriage_44928" where entry=44928;

update creature set phaseMask=32768 where id in (36293, 38762);

