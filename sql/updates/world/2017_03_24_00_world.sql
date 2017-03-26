
UPDATE locales_quest SET QuestGiverTextWindow_loc3="Gnoll der Flusspfoten", QuestGiverTargetName_loc3="Gnoll der Flusspfoten" WHERE Id=26287;

UPDATE quest_template SET PrevQuestId=26266 WHERE Id=26287;

UPDATE quest_template SET PrevQuestId=26266 WHERE Id=26286;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Westfalleintopf", QuestGiverTargetName_loc3="Westfalleintopf" WHERE Id=26271;

UPDATE creature SET phaseId=171 WHERE id=42407;

DELETE FROM creature_template_addon WHERE entry=501;
INSERT INTO creature_template_addon VALUES 
(501, 0, 0, 0, 1, 0, "80471");

DELETE FROM creature_addon WHERE guid=43609;
DELETE FROM creature_addon WHERE guid=43608;
DELETE FROM creature_addon WHERE guid=43607;
DELETE FROM creature_addon WHERE guid=43593;
DELETE FROM creature_addon WHERE guid=43564;
DELETE FROM creature_addon WHERE guid=43539;
DELETE FROM creature_addon WHERE guid=43527;
DELETE FROM creature_addon WHERE guid=43515;
DELETE FROM creature_addon WHERE guid=43492;
DELETE FROM creature_addon WHERE guid=43478;
DELETE FROM creature_addon WHERE guid=43431;
DELETE FROM creature_addon WHERE guid=43421;
DELETE FROM creature_addon WHERE guid=43407;
DELETE FROM creature_addon WHERE guid=43379;
DELETE FROM creature_addon WHERE guid=43336;
DELETE FROM creature_addon WHERE guid=43323;
DELETE FROM creature_addon WHERE guid=43321;
DELETE FROM creature_addon WHERE guid=43307;
DELETE FROM creature_addon WHERE guid=43292;
DELETE FROM creature_addon WHERE guid=43272;
DELETE FROM creature_addon WHERE guid=43258;
DELETE FROM creature_addon WHERE guid=43244;
DELETE FROM creature_addon WHERE guid=43232;
DELETE FROM creature_addon WHERE guid=43200;
DELETE FROM creature_addon WHERE guid=43186;
DELETE FROM creature_addon WHERE guid=43176;
DELETE FROM creature_addon WHERE guid=43164;
DELETE FROM creature_addon WHERE guid=43130;
DELETE FROM creature_addon WHERE guid=43085;
DELETE FROM creature_addon WHERE guid=43080;
DELETE FROM creature_addon WHERE guid=43038;
DELETE FROM creature_addon WHERE guid=43036;
DELETE FROM creature_addon WHERE guid=42993;
DELETE FROM creature_addon WHERE guid=42926;
DELETE FROM creature_addon WHERE guid=42911;
DELETE FROM creature_addon WHERE guid=42888;
DELETE FROM creature_addon WHERE guid=42872;
DELETE FROM creature_addon WHERE guid=42851;
DELETE FROM creature_addon WHERE guid=42842;
DELETE FROM creature_addon WHERE guid=42831;
DELETE FROM creature_addon WHERE guid=42819;
DELETE FROM creature_addon WHERE guid=42802;
DELETE FROM creature_addon WHERE guid=42761;
DELETE FROM creature_addon WHERE guid=42756;
DELETE FROM creature_addon WHERE guid=42729;
DELETE FROM creature_addon WHERE guid=42646;
DELETE FROM creature_addon WHERE guid=42596;
DELETE FROM creature_addon WHERE guid=42558;
DELETE FROM creature_addon WHERE guid=42555;
DELETE FROM creature_addon WHERE guid=42517;
DELETE FROM creature_addon WHERE guid=42504;
DELETE FROM creature_addon WHERE guid=42479;
DELETE FROM creature_addon WHERE guid=42478;
DELETE FROM creature_addon WHERE guid=42474;
DELETE FROM creature_addon WHERE guid=42437;
DELETE FROM creature_addon WHERE guid=42426;
DELETE FROM creature_addon WHERE guid=42423;
DELETE FROM creature_addon WHERE guid=42392;
DELETE FROM creature_addon WHERE guid=42361;
DELETE FROM creature_addon WHERE guid=42360;
DELETE FROM creature_addon WHERE guid=42359;
DELETE FROM creature_addon WHERE guid=42335;
DELETE FROM creature_addon WHERE guid=42322;
DELETE FROM creature_addon WHERE guid=42308;

DELETE FROM creature WHERE id=452 AND guid=6935;
DELETE FROM creature WHERE id=501 AND guid=42287;
DELETE FROM creature WHERE id=124 AND guid=6599;
DELETE FROM creature WHERE id=452 AND guid=6945;
DELETE FROM creature WHERE id=501 AND guid=42371;
DELETE FROM creature WHERE id=124 AND guid=43255;
DELETE FROM creature WHERE id=452 AND guid=6946;
DELETE FROM creature WHERE id=501 AND guid=43488;
DELETE FROM creature WHERE id=452 AND guid=6930;
DELETE FROM creature WHERE id=501 AND guid=6955;
DELETE FROM creature WHERE id=124 AND guid=43019;
DELETE FROM creature WHERE id=501 AND guid=43056;
DELETE FROM creature WHERE id=452 AND guid=6951;
DELETE FROM creature WHERE id=501 AND guid=6722;
DELETE FROM creature WHERE id=452 AND guid=6940;
DELETE FROM creature WHERE id=124 AND guid=42518;
DELETE FROM creature WHERE id=501 AND guid=42775;
DELETE FROM creature WHERE id=452 AND guid=7157;

delete from pool_gameobject where guid=19017 and pool_entry=5829;

UPDATE gameobject_template SET data1=2843 WHERE entry=2843;

delete from gameobject_loot_template where entry=202780;
insert into gameobject_loot_template values
(202780, 11050, 11050, 100, 0, 1, 0, 1, 1, "");

delete from fishing_loot_template where entry in (5145,4815,5146,5144,5004,3277,209,5095,5034,4922,5389);
insert into fishing_loot_template values
(209, 11051, 11051, 100, 0, 1, 0, 1, 1, ""),
(5145, 11051, 11051, 100, 0, 1, 0, 1, 1, ""),
(4815, 11051, 11051, 100, 0, 1, 0, 1, 1, ""),
(5146, 11051, 11051, 100, 0, 1, 0, 1, 1, ""),
(5144, 11051, 11051, 100, 0, 1, 0, 1, 1, ""),
(5004, 11051, 11051, 100, 0, 1, 0, 1, 1, ""),
(3277, 11051, 11051, 100, 0, 1, 0, 1, 1, ""),
(5095, 11051, 11051, 100, 0, 1, 0, 1, 1, ""),
(5034, 11051, 11051, 100, 0, 1, 0, 1, 1, ""),
(4922, 11051, 11051, 100, 0, 1, 0, 1, 1, ""),
(5389, 11051, 11051, 100, 0, 1, 0, 1, 1, "");

update creature_template set AIName="" where entry=42559;

delete from smart_scripts where entryorguid=42559;

update spell_area set quest_start=26209 where spell=101419 and area=40;


