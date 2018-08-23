
-- npc 26113 Master Flame Eater H

UPDATE creature_template SET faction=775, AIName="", ScriptName="npc_master_fire_flame_eater" WHERE entry=26113;

DELETE FROM creature_queststarter WHERE id=26113;
INSERT INTO creature_queststarter 
(id, quest)
VALUES
(26113, 11921),
(26113, 11922),
(26113, 11923),
(26113, 11925),
(26113, 11926);

DELETE FROM creature_questender WHERE id=26113;
INSERT INTO creature_questender 
(id, quest)
VALUES
(26113, 11915),
(26113, 11922),
(26113, 11923),
(26113, 11925),
(26113, 11926);

DELETE FROM creature_text WHERE entry=26113;
INSERT INTO creature_text 
(entry, groupid, id, text, type, language, probability, emote, duration, sound, comment, BroadcastTextID)
VALUES
(26113, 0, 1, "Behold, the Flames of Summer!", 12, 0, 100.0, 5, 0, 0, "", 25105),
(26113, 0, 2, "Careful, don\'t get burned!", 12, 0, 100.0, 25, 0, 0, "", 25106),
(26113, 0, 3, "Enjoying the Fire Festival?", 12, 0, 100.0, 1, 0, 0, "", 25107),
(26113, 0, 4, "Welcome! Have you yet honored this land\'s flame?", 12, 0, 100.0, 3, 0, 0, "", 25108);
