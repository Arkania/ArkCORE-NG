
-- 26520 Festival Scorchling

UPDATE creature_template SET AIName="", ScriptName="npc_festival_scorchling_26520" WHERE entry=26520;

DELETE FROM smart_scripts WHERE entryorguid=26520;

DELETE FROM game_event_creature WHERE guid IN (126956);

DELETE FROM creature_text WHERE entry=26520;
INSERT INTO creature_text 
(entry, groupid, id, text, type, language, probability, emote, duration, sound, comment, BroadcastTextID)
VALUES
(26520, 1, 0, "Thank you again, $n, for this delectable incense.", 12, 0, 100.0, 0, 0, 0, "", 25699),
(26520, 2, 0, "%s devours the incense.  It\'s ravenous!", 42, 0, 100.0, 0, 0, 0, "", 25717),
(26520, 3, 0, "So good!  So packed with energy!", 12, 0, 100.0, 0, 0, 0, "", 25718),
(26520, 4, 0, "It has everything a growing scorchling needs!", 12, 0, 100.0, 0, 0, 0, "", 25719),
(26520, 5, 0, "I can feel the power SURGING within me!", 12, 0, 100.0, 0, 0, 0, "", 25730),
(26520, 6, 0, "%s bellows with laughter!", 42, 0, 100.0, 0, 0, 0, "", 25720),
(26520, 7, 0, "Now!  Finally!  Our plans can take effect!", 12, 0, 100.0, 0, 0, 0, "", 25721),
(26520, 8, 0, "KNEEL, LITTLE MORTAL!  KNEEL BEFORE THE MIGHT OF THE HERALD OF RAGNAROS!", 12, 0, 100.0, 0, 0, 0, "", 25722),
(26520, 9, 0, "YOU WILL ALL PERISH IN FLAMES!", 12, 0, 100.0, 0, 0, 0, "", 25723),
(26520, 10, 0, "%s blinks...", 42, 0, 100.0, 0, 0, 0, "", 25724),
(26520, 11, 0, "Ah.  I was merely jesting...", 12, 0, 100.0, 0, 0, 0, "", 25725);

delete from locales_creature_text where entry=26520;

