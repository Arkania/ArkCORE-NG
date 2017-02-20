

UPDATE creature SET map=648, zoneId=4720, areaId=4784, position_x=985.7706, position_y=3830.726, position_z=3.231742, orientation=3.61634 WHERE id=36149 AND guid=246171;

UPDATE gameobject_template SET data5=14125 WHERE entry=202850;

UPDATE gameobject SET phaseGroup=563 WHERE guid=57928;

UPDATE quest_template SET SpecialFlags=3 WHERE Id=14046;

delete from spell_linked_spell where spell_trigger=68750 AND spell_effect=-67854;

delete from creature where guid=285355;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Es ist eine Instastadt", QuestGiverTargetName_loc3="Instastadt" WHERE Id=14245;

UPDATE quest_template SET QuestGiverPortrait=0 WHERE Id=14245;

DELETE FROM phase_definitions WHERE zoneId=4720;
INSERT INTO phase_definitions VALUES 
(4720, 0, 170, 0, 0, 0, 1, "Lost island from teleport start "),
(4720, 1, 171, 0, 0, 0, 1, "Lost island"),
(4720, 2, 172, 0, 0, 0, 1, "Lost island"),
(4720, 3, 179, 0, 0, 0, 1, "Lost island"),
(4720, 4, 180, 0, 661, 681, 1, "Lost Isles Town in a Box"),
(4720, 5, 181, 0, 661, 681, 1, "Lost Isles Town in a Box"),
(4720, 6, 182, 0, 661, 681, 1, "Lost Isles Town in a Box"),
(4720, 7, 183, 0, 661, 681, 1, "Lost Isles Town in a Box"),
(4720, 8, 183, 0, 659, 682, 2, "Lost Isles Town in a Box"),
(4720, 9, 184, 0, 659, 682, 1, "Lost Isles Volcano Eruption "),
(4720, 10, 185, 0, 659, 682, 1, "Lost Isles Volcano Eruption ");

DELETE FROM phase_area WHERE areaId=4720;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4720, 0, 14126, 14303, 64, 11, 1, "arrival in Lost Island, phase 170"),
(4720, 1, 14303, 14240, 64, 11, 1, "arrival in Lost Island, phase 171"),
(4720, 2, 14240, 14326, 64, 09, 1, "arrival in Lost Island, phase 172"),
(4720, 3, 14326, 14245, 66, 09, 1, "arrival in Lost Island, phase 179"),
(4720, 4, 14245, 24897, 66, 01, 1, "Lost Isles Town in a Box, phase 180, from 'Its a Town-In-A-Box' to 'Get Back to Town' "),
(4720, 5, 24897, 24937, 74, 01, 1, "Lost Isles Town in a Box, phase 181, from 'Get Back to Town' to 'Oomlot Dealt With' "),
(4720, 6, 24937, 24958, 74, 11, 1, "Lost Isles Town in a Box, phase 182, from 'Oomlot Dealt With' to 'Volcanoth!' "),
(4720, 7, 24958, 25023, 64, 11, 1, "Lost Isles Town in a Box, phase 183, from 'Volcanoth!' to 'Old Friends' "),
(4720, 8, 24958, 39335, 64, 11, 1, "Lost Isles Volcano Eruption, phase 183, from 'Volcanoth!' to 'Wild Mine Cart Ride' "),
(4720, 9, 39335, 25251, 64, 11, 1, "Lost Isles Volcano Eruption, phase 184, from 'Wild Mine Cart Ride' to 'Final Confrontation' "),
(4720,10, 25251, 25266, 64, 11, 1, "Lost Isles Volcano Eruption, phase 185, from 'Final Confrontation' to 'Warchief's Emissary' ");

DELETE FROM creature_addon WHERE guid=285355;

delete from creature_equip_template where entry=35234;
insert into creature_equip_template values 
(35234, 1, 1906, 12745, 0);

DELETE FROM gossip_menu_option WHERE menu_id=12046;
INSERT INTO gossip_menu_option VALUES 
(12046, 0, 3, "Alchemy", 45753, 1, 1, 0, 0, 0, 0, 0, "", 0),
(12046, 1, 3, "Blacksmithing", 45754, 1, 1, 0, 0, 0, 0, 0, "", 0),
(12046, 2, 3, "Enchanting", 45755, 1, 1, 0, 0, 0, 0, 0, "", 0),
(12046, 3, 3, "Engineering", 45756, 1, 1, 0, 0, 0, 0, 0, "", 0),
(12046, 4, 3, "Inscription", 45757, 1, 1, 0, 0, 0, 0, 0, "", 0),
(12046, 5, 3, "Jewelcrafting", 45758, 1, 1, 0, 0, 0, 0, 0, "", 0),
(12046, 6, 3, "Leatherworking", 45759, 1, 1, 0, 0, 0, 0, 0, "", 0),
(12046, 7, 3, "Tailoring", 45760, 1, 1, 0, 0, 0, 0, 0, "", 0),
(12046, 8, 3, "Cooking", 45763, 1, 1, 0, 0, 0, 0, 0, "", 0),
(12046, 9, 3, "First Aid", 45765, 1, 1, 0, 0, 0, 0, 0, "", 0),
(12046, 10, 3, "Fishing", 45767, 1, 1, 0, 0, 0, 0, 0, "", 0),
(12046, 11, 3, "Herbalism", 45768, 1, 1, 0, 0, 0, 0, 0, "", 0),
(12046, 12, 3, "Mining", 45769, 1, 1, 0, 0, 0, 0, 0, "", 0),
(12046, 13, 3, "Skinning", 45770, 1, 1, 0, 0, 0, 0, 0, "", 0);

UPDATE creature_template SET gossip_menu_id=12002 WHERE entry=45286;

UPDATE gossip_menu_option SET OptionBroadcastTextID=45513, option_id=3, npc_option_npcflag=128 WHERE menu_id=12002 AND id=0;

UPDATE gossip_menu_option SET OptionBroadcastTextID=45512 WHERE menu_id=12002 AND id=1;

UPDATE gossip_menu_option SET OptionBroadcastTextID=45761 WHERE menu_id=12002 AND id=2;

update creature set spawndist=25, MovementType=1 where id=36681 and MovementType=0;

UPDATE creature SET spawndist=5 WHERE guid in (286230, 286232, 286233, 286237);

UPDATE creature SET spawndist=30, MovementType=1 WHERE guid=245373;

UPDATE creature_template SET InhabitType=2 WHERE entry=36682;

UPDATE creature_template SET speed_walk=1.71429, HoverHeight=1 WHERE entry=36682;

delete from creature where guid in (283914,284463,247553,247552);

update creature set spawndist=0, MovementType=0 where guid=247549;

update creature set spawndist=0, MovementType=0 where guid=247550;

update creature set spawndist=0, MovementType=0 where guid=247551;

UPDATE creature SET phaseId=0, phaseGroup=418 WHERE guid=6683;

delete from creature where id=44578 and guid between 246680 and 246687;

delete from creature where id=44578 and guid in (246625,246626,246630,246631,246632);

delete from creature where id=38412;

delete from creature where id=44580;

DELETE FROM creature_addon WHERE guid between 284492 and 284499;

DELETE FROM creature_addon WHERE guid=246661;

DELETE FROM creature_addon WHERE guid between 286646 and 286660;

DELETE FROM creature_addon WHERE guid=283914;

DELETE FROM creature_addon WHERE guid=247551;
INSERT INTO creature_addon VALUES 
(247551, 247551, 0, 0, 1, 0, "");

UPDATE creature SET MovementType=2 WHERE guid=247551;

DELETE FROM waypoint_data WHERE id=247551;
INSERT INTO waypoint_data VALUES 
(247551, 0, 667.3389, 2003.419, 39.55524, 0.615805, 2000, 0, 0, 100, 0),
(247551, 1, 678.9508, 2012.951, 46.02834, 0.686491, 0, 0, 0, 100, 0),
(247551, 2, 688.79, 2021.522, 50.58793, 0.67471, 0, 0, 0, 100, 0),
(247551, 3, 696.9946, 2029.985, 53.36478, 0.79252, 2000, 0, 0, 100, 0),
(247551, 4, 688.79, 2021.522, 50.58793, 0.67471, 0, 0, 0, 100, 0),
(247551, 5, 678.9508, 2012.951, 46.02834, 0.686491, 0, 0, 0, 100, 0);

UPDATE creature SET position_x=689.605, position_y=2038.481, position_z=54.747, orientation=2.4693 WHERE guid=284462;

DELETE FROM creature_addon WHERE guid=284462;
INSERT INTO creature_addon VALUES 
(284462, 0, 0, 0, 0, 233, "");

UPDATE creature SET position_x=731.362, position_y=2058.661, position_z=60.248, orientation=.7375 WHERE guid=247549;

DELETE FROM creature_addon WHERE guid=247549;
INSERT INTO creature_addon VALUES 
(247549, 0, 0, 0, 0, 233, "");

delete from creature_queststarter where id=38432 and quest=24856;

delete from creature where guid in (284399,284381,284355,284353,284370,284359,284392,245395);

DELETE FROM creature_addon WHERE guid=284370;
DELETE FROM creature_addon WHERE guid=284355;

DELETE FROM creature_addon WHERE guid=245383;
INSERT INTO creature_addon VALUES 
(245383, 245383, 0, 0, 1, 0, "");

UPDATE creature SET MovementType=2 WHERE guid=245383;

DELETE FROM waypoint_data WHERE id=245383;
INSERT INTO waypoint_data VALUES 
(245383, 0, 466.8776, 1837.144, 0.806475, 3.820225, 3000, 0, 0, 100, 0),
(245383, 1, 458.0041, 1821.636, 1.087762, 4.095113, 3000, 0, 0, 100, 0),
(245383, 2, 478.9732, 1783.024, 1.085549, 5.288916, 3000, 0, 0, 100, 0),
(245383, 3, 517.8772, 1810.191, 4.650264, 0.592232, 3000, 0, 0, 100, 0),
(245383, 4, 510.5123, 1832.605, 3.387321, 1.660374, 3000, 0, 0, 100, 0),
(245383, 5, 468.5624, 1831.453, 1.24796, 3.254733, 0, 0, 0, 100, 0);

DELETE FROM creature_addon WHERE guid=284384;
INSERT INTO creature_addon VALUES 
(284384, 284384, 0, 0, 1, 0, "");

UPDATE creature SET MovementType=2 WHERE guid=284384;

DELETE FROM waypoint_data WHERE id=284384;
INSERT INTO waypoint_data VALUES 
(284384, 0, 515.7573, 1871.608, 2.656249, 2.131612, 0, 0, 0, 100, 0),
(284384, 1, 484.0249, 1892.504, 2.448867, 2.701025, 0, 0, 0, 100, 0),
(284384, 2, 468.5167, 1881.276, 0.592417, 3.765239, 3000, 0, 0, 100, 0),
(284384, 3, 471.4772, 1869.395, 0.142756, 5.2732, 3000, 0, 0, 100, 0),
(284384, 4, 460.5201, 1842.052, 0.214209, 4.346427, 0, 0, 0, 100, 0),
(284384, 5, 489.1178, 1832.365, 1.473217, 6.054666, 0, 0, 0, 100, 0),
(284384, 6, 507.9636, 1837.435, 3.111291, 0.317332, 3000, 0, 0, 100, 0),
(284384, 7, 518.6674, 1870.485, 2.795112, 1.271591, 0, 0, 0, 100, 0);

UPDATE creature_addon SET path_id=245396 WHERE guid=245396;

UPDATE creature SET MovementType=2 WHERE guid=245396;

DELETE FROM waypoint_data WHERE id=245396;
INSERT INTO waypoint_data VALUES 
(245396, 0, 582.1873, 1954.739, 10.73295, 3.741659, 0, 0, 0, 100, 0),
(245396, 1, 597.2665, 1984.108, 12.04339, 1.275508, 3000, 0, 0, 100, 0),
(245396, 2, 583.1958, 1998.328, 11.29428, 2.367212, 3000, 0, 0, 100, 0),
(245396, 3, 547.9056, 1991.245, 5.658841, 3.380376, 3000, 0, 0, 100, 0),
(245396, 4, 517.1201, 2014.277, 3.683401, 2.406482, 0, 0, 0, 100, 0),
(245396, 5, 503.7521, 1995.662, 1.663888, 4.091163, 0, 0, 0, 100, 0),
(245396, 6, 492.0665, 1982.635, 7.032451, 3.981208, 0, 0, 0, 100, 0),
(245396, 7, 489.2331, 1967.964, 11.29633, 4.582033, 0, 0, 0, 100, 0),
(245396, 8, 483.2221, 1961.819, 11.07659, 3.938006, 0, 0, 0, 100, 0),
(245396, 9, 470.8588, 1954.42, 10.64112, 3.761292, 0, 0, 0, 100, 0),
(245396, 10, 470.8555, 1923.677, 10.54698, 4.746964, 0, 0, 0, 100, 0),
(245396, 11, 562.1395, 1919.044, 13.57218, 6.223512, 0, 0, 0, 100, 0),
(245396, 12, 563.0154, 1938.882, 13.66388, 1.550393, 0, 0, 0, 100, 0),
(245396, 13, 565.7397, 1938.426, 14.63848, 6.117484, 0, 0, 0, 100, 0),
(245396, 14, 568.1027, 1939.357, 13.69218, 0.077771, 0, 0, 0, 100, 0),
(245396, 15, 576.6555, 1940.567, 12.21486, 0.140603, 0, 0, 0, 100, 0),
(245396, 16, 578.0433, 1948.866, 11.47951, 1.405094, 0, 0, 0, 100, 0);

delete from gameobject where id=202133 and guid<60000;

UPDATE creature_template SET faction=190, npcflag=0, ScriptName="npc_naga_hatchling_44579" WHERE entry in (44578, 44579, 44580);

update creature set spawndist=10 where id=38360 and MovementType=1 and position_z<-5;

UPDATE creature_template SET ScriptName="npc_naga_hatchling_38457" WHERE entry=38457;

update waypoint_data set move_type=1 where id in (3845501, 3845502, 3845503);

DELETE FROM creature WHERE id=24110 AND guid=286851;
INSERT INTO creature VALUES 
(286851, 24110, 648, 0, 0, 1, 181, 0, 11686, 1, 783.796, 1948.81, 102.405, 1.2841, 300, 0, 0, 0, 0, 0, 0, 0, 0);

UPDATE creature_template_addon SET auras="" WHERE entry=38531; -- 71333 smoke.. 29266 death : if hit by cannon..

update creature set phaseId=181 where guid=285584;

DELETE FROM creature_addon WHERE guid=286851;

delete from creature where guid in (247548);

update creature set ModelId=11686 where id=24110 and ModelId=0;

DELETE FROM waypoint_data WHERE id=286851;
INSERT INTO waypoint_data VALUES 
(286851, 0, 780.6337, 1949.33, 102.4497, 0, 0, 1, 0, 100, 0),
(286851, 1, 790.6962, 1969.042, 100.8657, 0, 0, 1, 0, 100, 0),
(286851, 2, 790.5313, 1992.896, 98.23127, 0, 0, 1, 0, 100, 0),
(286851, 3, 802.7813, 2014.576, 97.60346, 0, 0, 1, 0, 100, 0),
(286851, 4, 822.5989, 2045.604, 96.09377, 0, 0, 1, 0, 100, 0),
(286851, 5, 844.243, 2068.012, 93.42007, 0, 0, 1, 0, 100, 0),
(286851, 6, 851.533, 2095.686, 88.25676, 0, 0, 1, 0, 100, 0),
(286851, 7, 866.2795, 2121.394, 80.82765, 0, 0, 1, 0, 100, 0),
(286851, 8, 868.9774, 2137.936, 75.4072, 0, 0, 1, 0, 100, 0),
(286851, 9, 884.8559, 2147.109, 71.69846, 0, 0, 1, 0, 100, 0),
(286851, 10, 901.3958, 2162.396, 65.74876, 0, 0, 1, 0, 100, 0),
(286851, 11, 908.0938, 2180.066, 57.25764, 0, 0, 1, 0, 100, 0),
(286851, 12, 907.2864, 2202.446, 43.59169, 0, 0, 1, 0, 100, 0),
(286851, 13, 916.2778, 2227.62, 27.9863, 0, 0, 1, 0, 100, 0),
(286851, 14, 911.3195, 2247.063, 20.18579, 0, 0, 1, 0, 100, 0),
(286851, 15, 918.8386, 2272.995, 14.70055, 0, 0, 1, 0, 100, 0),
(286851, 16, 912.7743, 2285.163, 12.82682, 0, 0, 1, 0, 100, 0),
(286851, 17, 920.1094, 2298.903, 10.39059, 0, 0, 1, 0, 100, 0),
(286851, 18, 905.1389, 2310.08, 8.279609, 0, 0, 1, 0, 100, 0),
(286851, 19, 893.9063, 2315.606, 7.613342, 0, 0, 1, 0, 100, 0),
(286851, 20, 888.7136, 2325.795, 7.254128, 0, 0, 1, 0, 100, 0),
(286851, 21, 896.5521, 2333.224, 5.74977, 0, 0, 1, 0, 100, 0),
(286851, 22, 905.0018, 2332.984, 5.042526, 0, 0, 1, 0, 100, 0),
(286851, 23, 906.7379, 2330.615, 5.055651, 0, 0, 1, 0, 100, 0),
(286851, 24, 922.44, 2336.16, 3.695, 0, 0, 1, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=285584;
INSERT INTO waypoint_data VALUES 
(285584, 0, 822.5989, 2045.604, 96.09377, 0, 0, 1, 0, 100, 0),
(285584, 1, 844.243, 2068.012, 93.42007, 0, 0, 1, 0, 100, 0),
(285584, 2, 851.533, 2095.686, 88.25676, 0, 0, 1, 0, 100, 0),
(285584, 3, 866.2795, 2121.394, 80.82765, 0, 0, 1, 0, 100, 0),
(285584, 4, 868.9774, 2137.936, 75.4072, 0, 0, 1, 0, 100, 0),
(285584, 5, 884.8559, 2147.109, 71.69846, 0, 0, 1, 0, 100, 0),
(285584, 6, 901.3958, 2162.396, 65.74876, 0, 0, 1, 0, 100, 0),
(285584, 7, 908.0938, 2180.066, 57.25764, 0, 0, 1, 0, 100, 0),
(285584, 8, 907.2864, 2202.446, 43.59169, 0, 0, 1, 0, 100, 0),
(285584, 9, 916.2778, 2227.62, 27.9863, 0, 0, 1, 0, 100, 0),
(285584, 10, 911.3195, 2247.063, 20.18579, 0, 0, 1, 0, 100, 0),
(285584, 11, 918.8386, 2272.995, 14.70055, 0, 0, 1, 0, 100, 0),
(285584, 12, 912.7743, 2285.163, 12.82682, 0, 0, 1, 0, 100, 0),
(285584, 13, 915.0443, 2315.163, 7.5395, 0, 0, 1, 0, 100, 0),
(285584, 14, 922.44, 2336.16, 3.695, 0, 0, 1, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=285598;
INSERT INTO waypoint_data VALUES 
(285598, 0, 907.2864, 2202.446, 43.59169, 0, 0, 1, 0, 100, 0),
(285598, 1, 916.2778, 2227.62, 27.9863, 0, 0, 1, 0, 100, 0),
(285598, 2, 911.3195, 2247.063, 20.18579, 0, 0, 1, 0, 100, 0),
(285598, 3, 918.8386, 2272.995, 14.70055, 0, 0, 1, 0, 100, 0),
(285598, 4, 912.7743, 2285.163, 12.82682, 0, 0, 1, 0, 100, 0),
(285598, 5, 927.0773, 2316.716, 7.2781, 0, 0, 1, 0, 100, 0),
(285598, 6, 922.44, 2336.16, 3.695, 0, 0, 1, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=285600;
INSERT INTO waypoint_data VALUES 
(285600, 0, 918.8386, 2272.995, 14.70055, 0, 0, 1, 0, 100, 0),
(285600, 1, 912.7743, 2285.163, 12.82682, 0, 0, 1, 0, 100, 0),
(285600, 2, 943.3143, 2307.816, 6.4792, 0, 0, 1, 0, 100, 0),
(285600, 3, 932.007, 2327.463, 5.0244, 0, 0, 1, 0, 100, 0),
(285600, 4, 922.44, 2336.16, 3.695, 0, 0, 1, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=285592;
INSERT INTO waypoint_data VALUES 
(285592, 0, 911.3195, 2247.063, 20.18579, 0, 0, 1, 0, 100, 0),
(285592, 1, 918.8386, 2272.995, 14.70055, 0, 0, 1, 0, 100, 0),
(285592, 2, 912.7743, 2285.163, 12.82682, 0, 0, 1, 0, 100, 0),
(285592, 3, 927.0773, 2316.716, 7.2781, 0, 0, 1, 0, 100, 0),
(285592, 4, 922.44, 2336.16, 3.695, 0, 0, 1, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=285588;
INSERT INTO waypoint_data VALUES 
(285588, 0, 918.8386, 2272.995, 14.70055, 0, 0, 1, 0, 100, 0),
(285588, 1, 912.7743, 2285.163, 12.82682, 0, 0, 1, 0, 100, 0),
(285588, 2, 920.1094, 2298.903, 10.39059, 0, 0, 1, 0, 100, 0),
(285588, 3, 915.0443, 2315.163, 7.5395, 0, 0, 1, 0, 100, 0),
(285588, 4, 922.44, 2336.16, 3.695, 0, 0, 1, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=285591;
INSERT INTO waypoint_data VALUES 
(285591, 0, 920.1094, 2298.903, 10.39059, 0, 0, 1, 0, 100, 0),
(285591, 1, 915.0443, 2315.163, 7.5395, 0, 0, 1, 0, 100, 0),
(285591, 2, 922.44, 2336.16, 3.695, 0, 0, 1, 0, 100, 0);

delete from smart_scripts where entryorguid in (38746, 38513);

UPDATE creature_template SET AIName="", ScriptName="npc_gobber_38746" WHERE entry=38746;

UPDATE creature_template SET ScriptName="npc_sally_salvager_sandscrew_38511" WHERE entry=38511;

UPDATE creature_template SET AIName="", ScriptName="npc_evol_fingers_38513" WHERE entry=38513;

UPDATE creature_template SET ScriptName="npc_warrior_matic_nx__38518" WHERE entry=38518;

UPDATE creature_template SET ScriptName="npc_fizz_lighter_38514" WHERE entry=38514;

UPDATE creature_template SET ScriptName="npc_sister_goldskimmer_38516" WHERE entry=38516;

UPDATE creature_template SET ScriptName="npc_sassy_hardwrench_38387" WHERE entry=38387;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Krieger von Oomlot", QuestGiverTargetName_loc3="Krieger von Oomlot" WHERE Id=24901;

UPDATE quest_template SET QuestGiverPortrait=32113, QuestGiverTextWindow="Oomlot Warrior", QuestGiverTargetName="Oomlot Warrior" WHERE Id=24901;

UPDATE creature SET phaseId=0, phaseGroup=429 WHERE guid=2132;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Schamane von Oomlot", QuestGiverTargetName_loc3="Schamane von Oomlot" WHERE Id=24925;

DELETE FROM creature_addon WHERE guid=284370;
DELETE FROM creature_addon WHERE guid=284355;

delete from spelldifficulty_dbc where id in (28308, 50255);

delete from smart_scripts where entryorguid=38647;

DELETE FROM smart_scripts WHERE entryorguid=38647;

UPDATE creature_template SET AIName="", ScriptName="npc_izzy_38647" WHERE entry=38647;

delete from creature where id in (38644, 40722);

update creature set phaseId=0, phaseGroup=415 where id in (38574,38575,38696);

delete from creature where id=38696 and guid in (285676, 285677);

delete from creature_addon where guid in (285676, 285677);

UPDATE creature_addon SET auras="" WHERE guid=246513;

delete from creature where id=38574 and guid in (285467);

delete from creature_addon where guid in (285467);



