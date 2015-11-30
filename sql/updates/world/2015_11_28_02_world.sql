
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Findet den vermissten Kodo von Grol'dom irgendwo auf dem Dornenhügel im Nördlichen Brachland." WHERE Id=13969;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Bringt das Getreide zu dem Kodo von Grol'dom auf dem Dornenhügel im Nördlichen Brachland." WHERE Id=13970;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Sprecht mit Kranal Fiss auf Grol'doms Hof im Nördlichen Brachland, um euch zu vergewissern, dass sein vermisstes Kodo sicher angekommen ist." WHERE Id=13971;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Una Wolfsklaue im Nördlichen Brachland zurück.", QuestGiverTextWindow_loc3="Plünderer der Klingenmähnen", QuestGiverTargetName_loc3="Plünderer der Klingenmähnen" WHERE Id=13973;

UPDATE quest_template SET RequiredNpcOrGo1=34514, RequiredNpcOrGoCount1=1 WHERE Id=13961;
UPDATE locales_quest SET EndText_loc3="", ObjectiveText1_loc3="Gefangenen der Klingenmähnen abgeliefert" WHERE Id=13961;
UPDATE quest_template SET EndText="", ObjectiveText1="Razormane Prisoner Delivered" WHERE Id=13961;


SET @GUID=116096;
UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;
INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;
DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, 250.2464, -3043.086, 96.35676, 1.514725, 0, 1),
(@GUID, 1, 250.5933, -3036.438, 97.31423, 1.518652, 0, 1),
(@GUID, 2, 245.6707, -3031.961, 98.04057, 2.441495, 0, 1),
(@GUID, 3, 219.3794, -3024.377, 95.42552, 2.747801, 0, 1),
(@GUID, 4, 205.7916, -3019.747, 91.78239, 2.857757, 0, 1),
(@GUID, 5, 192.9941, -3010.916, 91.97298, 2.523962, 0, 1),
(@GUID, 6, 184.9397, -2971.044, 92.56313, 1.773907, 0, 1),
(@GUID, 7, 167.8358, -2960.872, 91.70457, 2.602502, 0, 1),
(@GUID, 8, 151.74, -2967.224, 91.88222, 3.517492, 0, 1),
(@GUID, 9, 139.1066, -2984.634, 92.69673, 4.082979, 0, 1),
(@GUID, 10, 139.7867, -2992.555, 92.14877, 4.848736, 0, 1),
(@GUID, 11, 165.8212, -3007.802, 92.54465, 5.732303, 0, 1),
(@GUID, 12, 179.118, -3026.743, 93.39221, 5.323898, 0, 1),
(@GUID, 13, 200.7047, -3078.382, 91.66696, 5.170747, 0, 1),
(@GUID, 14, 237.1631, -3072.534, 91.88657, 0.167756, 0, 1),
(@GUID, 15, 245.0818, -3069.838, 95.20671, 0.407302, 0, 1),
(@GUID, 16, 253.8103, -3054.678, 96.32427, 1.090599, 0, 1),
(@GUID, 17, 250.8462, -3047.693, 95.98949, 1.946683, 0, 1);

SET @GUID=129243;
UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;
INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;
DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, 217.7511, -2862.322, 91.62416, 1.337997, 0, 1),
(@GUID, 1, 218.6893, -2818.626, 92.85227, 1.569689, 0, 1),
(@GUID, 2, 229.9894, -2805.837, 92.82257, 0.847123, 0, 1),
(@GUID, 3, 258.5581, -2799.695, 91.66704, 0.265928, 0, 1),
(@GUID, 4, 274.6437, -2778.525, 91.67579, 0.953151, 0, 1),
(@GUID, 5, 269.777, -2752.858, 92.13158, 1.758185, 0, 1),
(@GUID, 6, 245.5311, -2744.493, 92.15919, 2.834181, 0, 1),
(@GUID, 7, 218.7891, -2754.357, 91.66667, 3.497842, 0, 1),
(@GUID, 8, 171.7546, -2840.503, 93.70279, 4.220406, 0, 1),
(@GUID, 9, 176.5635, -2863.855, 93.50722, 4.915481, 0, 1),
(@GUID, 10, 194.845, -2883.845, 92.5011, 5.461326, 0, 1),
(@GUID, 11, 204.3083, -2886.445, 92.44415, 6.015029, 0, 1),
(@GUID, 12, 211.5977, -2883.232, 92.11189, 0.415139, 0, 1),
(@GUID, 13, 216.7482, -2870.699, 91.66961, 1.188757, 0, 1);

delete from creature_text where entry=14872;
insert into creature_text values
(14872, 0, 0, "Help! I'm being chased by a swarm of bees!", 12, 0, 100, 0, 0, 0, "", 10259);

-- db error
delete from creature_addon where guid in (26570, 26571, 138742, 26574, 26576, 26575);

delete from creature_text where entry=16806;
insert into creature_text values
(16806, 0, 0, "You may be a noble but I'm the noble! The definitive article you might say!", 12, 0, 100, 0, 0, 0, "", 18426);

delete from npc_text where ID=10123;
insert into npc_text (ID, text0_0) values (10123, "This party is pointless. Those foolish nobles will never get to see Medivh.$B$BCan't they see this? I should have just stayed in Drkshire with my family instead of wasting my time here.");

update creature_template set AIName="" where entry in (6906, 6907, 6908, 6910, 7023, 7175, 7206, 7291, 8658, 9978, 10052, 11486, 11487, 11488, 11489, 11490, 11492, 11496, 11501, 11517, 11518, 11519, 11520, 11561, 11680, 12319);
update creature_template set AIName="" where entry in (13280, 14321, 14322, 14323, 14324, 14325, 14326, 14327, 14354, 15277, 16425, 16593, 17612, 18855, 18927, 19169, 22982, 23208, 23257, 23334, 23335, 23368, 23392, 26428, 29021);
update creature_template set AIName="" where entry in (29022, 29023, 29024, 30736, 33854, 34430, 35167, 36231, 36845, 39388, 40008, 40011, 40013, 40448, 40597, 40633, 42698, 44404, 44648, 44715, 44752, 46209, 46210, 46211, 48832);
update creature_template set AIName="" where entry in (48936, 479010, 3904800);


delete from creature_text where entry=14873; -- Okla
insert into creature_text values
(14873, 0, 0, "Can I go collect more rocks for my necklace, Papa?", 12, 0, 100, 0, 0, 0, "", 10274),
(14873, 1, 0, "Dabu! I will be careful Papa!", 12, 0, 100, 0, 0, 0, "", 10276);

delete from creature_text where entry=5907; -- Kranal Fiss
insert into creature_text values
(5907, 0, 0, "Yes you may, Okla. But do not stray too far from home.", 12, 0, 100, 0, 0, 0, "", 10275);

delete from creature_text where entry=34503;
insert into creature_text values
(34503, 0, 0, "%s attempts to run away in fear!", 16, 0, 100, 0, 0, 0, "combat Flee", 1150),
(34503, 1, 0, "%s is ensnared!", 16, 0, 100, 0, 0, 0, "", 34691);

delete from creature_text where entry=34523;
insert into creature_text values
(34523, 0, 0, "I say nothing!", 12, 0, 100, 0, 0, 0, "", 34738),
(34523, 0, 1, "I not scared of you!", 12, 0, 100, 0, 0, 0, "", 34739),
(34523, 1, 0, "I say nothing! <snort>", 12, 0, 100, 0, 0, 0, "", 34740),
(34523, 2, 0, "Ow! <Snort>", 12, 0, 100, 0, 0, 0, "", 34730),
(34523, 2, 1, "Unf. You learn nothing from me!", 12, 0, 100, 0, 0, 0, "", 34731),
(34523, 2, 2, "Oof! I not talking!", 12, 0, 100, 0, 0, 0, "", 34733),
(34523, 2, 3, "<Snort!> That all you got?", 12, 0, 100, 0, 0, 0, "", 34734),
(34523, 2, 4, "Ow-oooh! I not talk for nothing!", 12, 0, 100, 0, 0, 0, "", 34735),
(34523, 2, 5, "<Snort!>", 12, 0, 100, 0, 0, 0, "", 34737),
(34523, 3, 0, "Unf - Not the face!", 12, 0, 100, 0, 0, 0, "", 34732),
(34523, 4, 0, "You waste your strength! Tortusk train us warriors never to talk.", 12, 0, 100, 0, 0, 0, "", 34736),
(34523, 4, 1, "Haha - <snort> ha - heee! <snort> Haha no stop haha <SNORT> <wheeze> Hee hee! Battlemaster Tortusk never prepared us for this!", 12, 0, 100, 0, 0, 0, "", 34741),
(34523, 5, 0, "Oh - I've said too much!", 12, 0, 100, 0, 0, 0, "", 34729);


delete from creature_text where entry=34509;
insert into creature_text values
(34509, 0, 0, "Flat-nosed filth! Get off of my land!", 12, 0, 100, 0, 0, 0, "", 34676),
(34509, 1, 0, "Pigs! Scum! I will cleave your fat heads like apples!", 12, 0, 100, 0, 0, 0, "", 34677),
(34509, 2, 0, "I will tear your tusks out. You hear me?", 12, 0, 100, 0, 0, 0, "", 34678),
(34509, 3, 0, "That's right! Die, vermin! The Horde will have your heads for this.", 12, 0, 100, 0, 0, 0, "", 34679),
(34509, 4, 0, "I will RIP off your HEADS and EAT your filthy faces!", 12, 0, 100, 0, 0, 0, "", 34680),
(34509, 5, 0, "That's right, squeal you maggots. I will gut you lengthwise and roast you when we are through!", 12, 0, 100, 0, 0, 0, "", 34681),
(34509, 6, 0, "Nobody steals my livestock!", 12, 0, 100, 0, 0, 0, "", 34682),
(34509, 7, 0, "Eat axe you bacon-brained porkchops!", 12, 0, 100, 0, 0, 0, "", 34683);

delete from creature_text where entry=34545;
insert into creature_text values
(34545, 0, 0, "%s goes into a frenzy!", 16, 0, 100, 0, 0, 0, "combat Frenzy", 2384);

