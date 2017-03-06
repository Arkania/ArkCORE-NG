UPDATE creature_template SET ScriptName="npc_sassy_hardwrench_38928" WHERE entry=38928;

delete from creature_addon where guid in (285586, 285582, 285580, 285581, 285583, 285606, 285602, 285597, 285594, 285585, 285604, 285601, 285605, 285596);

insert into creature_addon values
(285586, 0, 0, 0, 1, 0, "73080"),
(285582, 0, 0, 0, 1, 0, "73080"),
(285580, 0, 0, 0, 1, 0, "73080"),
(285581, 0, 0, 0, 1, 0, "73080"),
(285583, 0, 0, 0, 1, 0, "73080"),
(285606, 0, 0, 0, 1, 0, "73080"),
(285602, 0, 0, 0, 1, 0, "73080"),
(285597, 0, 0, 0, 1, 0, "73080"),
(285594, 0, 0, 0, 1, 0, "73080"),
(285585, 0, 0, 0, 1, 0, "73080"),
(285604, 0, 0, 0, 1, 0, "73080"),
(285601, 0, 0, 0, 1, 0, "73080"),
(285605, 0, 0, 0, 1, 0, "73080"),
(285596, 0, 0, 0, 1, 0, "73080");

delete from vehicle_template_accessory where entry=38929 and accessory_entry=38928;
insert into vehicle_template_accessory values 
(38929, 38928, 0, 1, "Flying Bomber", 6, 30000);

delete from npc_spellclick_spells where npc_entry=38929 and spell_id=46598;
insert into npc_spellclick_spells values 
(38929, 46598, 1, 0);

UPDATE creature_template SET ScriptName="npc_volcanoth_dead_explosion_bunny_38985" WHERE entry=38985;

UPDATE creature_addon SET auras="73116 73126" WHERE guid=286245;

delete from creature where guid=286244;

delete from creature_addon where guid=286244;

UPDATE creature_template SET npcflag=2, dynamicflags=0, InhabitType=4 WHERE entry=38928;

UPDATE creature_template SET minlevel=10, maxlevel=10, faction=2204, unit_flags=8, unit_flags2=67584, InhabitType=4, ScriptName="npc_flying_bomber_38918" WHERE entry=38918;

DELETE FROM creature_template_addon WHERE entry=38918;
INSERT INTO creature_template_addon VALUES 
(38918, 0, 0, 50331648, 1, 0, "");

DELETE FROM waypoint_data WHERE id=3891800;
INSERT INTO waypoint_data VALUES 
(3891800, 0, 1159.168, 1104.536, 126.8868, 0, 0, 1, 0, 100, 0),
(3891800, 1, 1151.068, 1115.432, 129.643, 0, 0, 1, 0, 100, 0),
(3891800, 2, 1135.733, 1140.052, 142.9035, 0, 0, 1, 0, 100, 0),
(3891800, 3, 1099.583, 1166.042, 160.9143, 0, 0, 1, 0, 100, 0),
(3891800, 4, 1035.833, 1199.629, 140.9983, 0, 0, 1, 0, 100, 0),
(3891800, 5, 985.6024, 1262.278, 123.749, 0, 0, 1, 0, 100, 0),
(3891800, 6, 993.0347, 1328.351, 114.8601, 0, 0, 1, 0, 100, 0),
(3891800, 7, 1028.523, 1418.127, 106.6932, 0, 0, 1, 0, 100, 0),
(3891800, 8, 1012.313, 1533.017, 129.8396, 0, 0, 1, 0, 100, 0),
(3891800, 9, 922.4358, 1584.993, 168.4136, 0, 0, 1, 0, 100, 0),
(3891800, 10, 798.5573, 1588.155, 174.2195, 0, 0, 1, 0, 100, 0),
(3891800, 11, 737.9097, 1636.477, 142.386, 0, 0, 1, 0, 100, 0),
(3891800, 12, 721.8958, 1756.576, 120.6636, 0, 0, 1, 0, 100, 0),
(3891800, 13, 763.0087, 1888.224, 119.608, 0, 0, 1, 0, 100, 0),
(3891800, 14, 808.3715, 2035.257, 112.9135, 0, 0, 1, 0, 100, 0),
(3891800, 15, 894.9583, 2161.132, 93.30235, 0, 0, 1, 0, 100, 0),
(3891800, 16, 940.9375, 2306.293, 39.80235, 0, 0, 1, 0, 100, 0),
(3891800, 17, 938.3368, 2458.16, 23.83012, 0, 0, 1, 0, 100, 0),
(3891800, 18, 868.5504, 2537.892, 11.08012, 0, 0, 1, 0, 100, 0),
(3891800, 19, 771.257, 2526.758, 11.08012, 0, 0, 1, 0, 100, 0),
(3891800, 20, 746.3073, 2438.623, 11.08012, 0, 0, 1, 0, 100, 0),
(3891800, 21, 807.4288, 2367.575, 30.66352, 0, 0, 1, 0, 100, 0),
(3891800, 22, 930.7847, 2316.547, 45.20028, 0, 0, 1, 0, 100, 0),
(3891800, 23, 1235.776, 2192.42, 93.26237, 0, 0, 1, 0, 100, 0),
(3891800, 24, 1534.63, 2529.204, 125.1861, 0, 0, 1, 0, 100, 0),
(3891800, 25, 1584.891, 2684.934, 95.60267, 0, 0, 1, 0, 100, 0),
(3891800, 26, 1584.891, 2684.934, 95.60267, 0, 0, 1, 0, 100, 0);

delete from vehicle_template_accessory where entry=38918 and accessory_entry=38869;
insert into vehicle_template_accessory values 
(38918, 38869, 0, 1, "Flying Bomber", 6, 30000);

delete from npc_spellclick_spells where npc_entry=38918 and spell_id=46598;
insert into npc_spellclick_spells values 
(38918, 46598, 1, 0);

UPDATE quest_template SET RequiredGender=0 WHERE Id=25243;

UPDATE quest_template SET RequiredGender=1 WHERE Id=25244;
