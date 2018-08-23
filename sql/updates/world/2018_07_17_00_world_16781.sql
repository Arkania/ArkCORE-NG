
-- 16781  Midsummer Celebrant A+H 
DELETE FROM creature_text WHERE entry=16781;
INSERT INTO creature_text 
(entry, groupid, id, text, type, language, probability, emote, duration, sound, comment, BroadcastTextID)
VALUES
(16781, 0, 1, "The Midsummer Fire Festival has something for everyone to enjoy!", 12, 0, 50.0, 396, 0, 0, "", 24528),
(16781, 0, 2, "Across the lands our fires burn strong and true!", 12, 0, 50.0, 396, 0, 0, "", 25068),
(16781, 0, 3, "Have you danced at the ribbon pole yet?", 12, 0, 50.0, 396, 0, 0, "", 25069),
(16781, 0, 4, "I admire the skill that torch jugglers have.", 12, 0, 50.0, 396, 0, 0, "", 25070);

DELETE FROM smart_scripts WHERE entryorguid=16781;
INSERT INTO smart_scripts 
(entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance, event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2, action_param3, action_param4, action_param5, action_param6, target_type, target_param1, target_param2, target_param3, target_x, target_y, target_z, target_o, comment)
VALUES
(16781, 0, 0, 0, 1, 0, 50, 0, 500, 1000, 45000, 120000, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0.0, 0.0, 0.0, 0.0, "");

UPDATE creature_template SET faction=35, AIName="SmartAI" WHERE entry=16781;

DELETE FROM game_event_creature WHERE guid IN (127027, 127028, 136331, 136332);

