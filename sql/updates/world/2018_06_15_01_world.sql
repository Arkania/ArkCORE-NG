
-- quest 918

DELETE FROM creature_text WHERE entry=2080;
INSERT INTO creature_text 
(entry, groupid, id, text, type, language, probability, emote, duration, sound, comment, BroadcastTextID)
VALUES
(2080, 0, 0, "Now let us place this rare earth in my planter...", 12, 0, 100.0, 0, 0, 0, "Denalan", 1239),
(2080, 1, 0, "Thank you again, $n.  This rare earth will be very helpful in my experiments.", 12, 7, 100.0, 2, 0, 0, "Denalan", 1240),
(2080, 2, 0, "%s removes the seeds from the Glowing Fruit...", 41, 0, 100.0, 1, 0, 0, "Denalan", 1156),
(2080, 3, 0, "Let\'s see how these seeds grow in my prepared soil...", 12, 0, 100.0, 1, 0, 0, "Denalan", 1157),
(2080, 4, 0, "%s plants the fruit seeds.", 41, 0, 100.0, 1, 0, 0, "Denalan", 1158),
(2080, 5, 0, "%s hurries to his planter.", 41, 0, 100.0, 1, 0, 0, "Denalan", 1159),
(2080, 6, 0, "I hope this frond takes root...", 12, 0, 100.0, 1, 0, 0, "Denalan", 1160),
(2080, 7, 0, "%s rises from the soil!", 41, 0, 100.0, 1, 0, 0, "Denalan", 1174);

DELETE FROM locales_creature_text WHERE entry=2080;
INSERT INTO locales_creature_text 
(entry, groupid, id, text_loc3)
VALUES
(2080, 0, 0, ""),
(2080, 1, 0, "Ich danke Euch nochmals, $n. Diese seltene Erde wird mir bei meinen Experimenten von großem Nutzen sein."),
(2080, 2, 0, ""),
(2080, 3, 0, ""),
(2080, 4, 0, ""),
(2080, 5, 0, ""),
(2080, 6, 0, ""),
(2080, 7, 0, "");

