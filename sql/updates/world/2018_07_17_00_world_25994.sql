
-- 25994 Flame Eater H
DELETE FROM creature_queststarter WHERE id=25994 AND quest=11915;
INSERT INTO creature_queststarter 
(id, quest)
VALUES
(25994, 11915);

DELETE FROM creature_text WHERE entry=25994;
INSERT INTO creature_text 
(entry, groupid, id, text, type, language, probability, emote, duration, sound, comment, BroadcastTextID)
VALUES
(25994, 0, 1, "Behold, the Flames of Summer!", 12, 0, 100.0, 5, 0, 0, "", 25105),
(25994, 0, 2, "Careful, don\'t get burned!", 12, 0, 100.0, 25, 0, 0, "", 25106),
(25994, 0, 3, "Enjoying the Fire Festival?", 12, 0, 100.0, 1, 0, 0, "", 25107),
(25994, 0, 4, "Welcome! Have you yet honored this land\'s flame?", 12, 0, 100.0, 3, 0, 0, "", 25108);

update creature set position_x=157.531403, position_y=-4747.337891, position_z=13.817058, orientation=5.243170 where id=25994 and guid=127068;

