
-- npc 25962 Fire Eater A
DELETE FROM creature_queststarter WHERE id=25962 AND quest=11882;
INSERT INTO creature_queststarter 
(id, quest)
VALUES
(25962, 11882);

DELETE FROM creature_text WHERE entry=25962;
INSERT INTO creature_text 
(entry, groupid, id, text, type, language, probability, emote, duration, sound, comment, BroadcastTextID)
VALUES
(25962, 0, 1, "Behold, the Flames of Summer!", 12, 0, 100.0, 5, 0, 0, "", 25105),
(25962, 0, 2, "Careful, don\'t get burned!", 12, 0, 100.0, 25, 0, 0, "", 25106),
(25962, 0, 3, "Enjoying the Fire Festival?", 12, 0, 100.0, 1, 0, 0, "", 25107),
(25962, 0, 4, "Welcome! Have you yet honored this land\'s flame?", 12, 0, 100.0, 3, 0, 0, "", 25108);

update creature_template set faction=84 where entry=25962;
