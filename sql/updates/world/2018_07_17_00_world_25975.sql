
-- npc 25975 Master Fire Eater

UPDATE creature_template SET AIName="", ScriptName="npc_master_fire_flame_eater" WHERE entry=25975;

UPDATE quest_template SET Method=2 WHERE id=9339;

UPDATE quest_template SET Method=2 WHERE id=9365;

UPDATE quest_template SET Flags=12290 WHERE id=11921;

UPDATE quest_template SET Flags=12290 WHERE id=11924;

DELETE FROM creature_queststarter WHERE id=25975;
INSERT INTO creature_queststarter 
(id, quest)
VALUES
(25975, 11657),
(25975, 11731),
(25975, 11921),
(25975, 11924);

DELETE FROM creature_questender WHERE id=25975;
INSERT INTO creature_questender 
(id, quest)
VALUES
(25975, 11657),
(25975, 11731),
(25975, 11882),
(25975, 11921),
(25975, 11924);

DELETE FROM creature_text WHERE entry=25975;
INSERT INTO creature_text 
(entry, groupid, id, text, type, language, probability, emote, duration, sound, comment, BroadcastTextID)
VALUES
(25975, 0, 1, "Behold, the Flames of Summer!", 12, 0, 100.0, 5, 0, 0, "", 25105),
(25975, 0, 2, "Careful, don\'t get burned!", 12, 0, 100.0, 25, 0, 0, "", 25106),
(25975, 0, 3, "Enjoying the Fire Festival?", 12, 0, 100.0, 1, 0, 0, "", 25107),
(25975, 0, 4, "Welcome! Have you yet honored this land\'s flame?", 12, 0, 100.0, 3, 0, 0, "", 25108);
