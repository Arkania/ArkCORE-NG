

SET @PATHID=3679001;

DELETE FROM waypoint_data WHERE id=@PATHID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@PATHID, 0, -2914.524, -51.80302, 187.0252, 5.654843, 0, 1),
(@PATHID, 1, -2507.789, -365.0092, 86.47243, 5.623429, 0, 1),
(@PATHID, 2, -2457.847, -401.8771, 59.40245, 5.654847, 0, 1),
(@PATHID, 3, -2395.454, -425.6935, 23.3136, 5.933658, 0, 1),
(@PATHID, 4, -2356.149, -422.0188, 0.905305, 0.219881, 0, 1),
(@PATHID, 5, -2342.442, -405.1882, -8.894143, 0.934594, 0, 1);


DELETE FROM creature_text WHERE entry=2949;
INSERT INTO creature_text (entry, groupid, id, text, type, language, probability, emote, duration, sound, BroadcastTextID, comment) VALUES 
(2949, 0, 0, "More bones to gnaw on...", 12, 0, 50, 0, 0, 0, 1871, "on Aggro Text"),
(2949, 0, 1, "Grrrr... fresh meat!", 12, 0, 50, 0, 0, 0, 1870, "on Aggro Text"),
(2949, 1, 0, "%s attempts to run away in fear!", 16, 0, 100, 0, 0, 0, 1150, "combat Flee");


DELETE FROM creature_text WHERE entry=2950;
INSERT INTO creature_text (entry, groupid, id, text, type, language, probability, emote, duration, sound, BroadcastTextID, comment) VALUES 
(2950, 0, 0, "More bones to gnaw on...", 12, 0, 50, 0, 0, 0, 1871, "on Aggro Text"),
(2950, 0, 1, "Grrrr... fresh meat!", 12, 0, 50, 0, 0, 0, 1870, "on Aggro Text"),
(2950, 1, 0, "%s attempts to run away in fear!", 16, 0, 100, 0, 0, 0, 1150, "combat Flee");

DELETE FROM creature_text WHERE entry=2951;
INSERT INTO creature_text (entry, groupid, id, text, type, language, probability, emote, duration, sound, BroadcastTextID, comment) VALUES 
(2951, 0, 0, "More bones to gnaw on...", 12, 0, 50, 0, 0, 0, 1871, "on Aggro Text"),
(2951, 0, 1, "Grrrr... fresh meat!", 12, 0, 50, 0, 0, 0, 1870, "on Aggro Text"),
(2951, 1, 0, "%s attempts to run away in fear!", 16, 0, 100, 0, 0, 0, 1150, "combat Flee");

DELETE FROM creature_text WHERE entry=5786;
INSERT INTO creature_text (entry, groupid, id, text, type, language, probability, emote, duration, sound, BroadcastTextID, comment) VALUES 
(5786, 0, 0, "%s becomes enraged!", 16, 0, 100, 0, 0, 0, 7798, "combat Enrage");

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Mull Donnerhorn im Dorf der Bluthufe zurück." WHERE Id=20440;

UPDATE quest_template SET QuestGiverPortrait=549, QuestGiverTextWindow="Agitated Earth Spirit", QuestGiverTargetName="Agitated Earth Spirit" WHERE Id=14491;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Ahmo Donnerhorn im Dorf der Bluthufe zurück.", QuestGiverTextWindow_loc3="Aufgebrachter Erdgeist", QuestGiverTargetName_loc3="Aufgebrachter Erdgeist" WHERE Id=14491;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Ruul Adlerklaue im Dorf der Bluthufe in Mulgore zurück." WHERE Id=743;

update creature_template set AIName="", ScriptName="npc_agitated_earth_spirit_36845" where entry=36845;

delete from creature where guid=75916 and id=2988;
