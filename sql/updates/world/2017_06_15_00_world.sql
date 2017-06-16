
-- fix deepholm
-- add invisible 12
DELETE FROM spell_area WHERE spell=83322 AND area=5303;
INSERT INTO spell_area (spell, area, quest_start, quest_end, aura_spell, racemask, gender, autocast, quest_start_status, quest_end_status) VALUES 
(83322, 5303, 27123, 27938, 0, 0, 2, 1, 64, 11);

-- add quest 26244
UPDATE quest_template SET PrevQuestId=27123, NextQuestId=0, ExclusiveGroup=0 WHERE Id=26244;

-- fix quest 26245 Gunship Down
UPDATE quest_template SET ExclusiveGroup=0, NextQuestIdChain=26247 WHERE Id=26246;

UPDATE creature SET spawndist=5 WHERE guid=244096;

UPDATE creature SET spawndist=0, MovementType=2 WHERE guid=244095;

DELETE FROM creature_addon WHERE guid=244095;
INSERT INTO creature_addon VALUES 
(244095, 244095, 0, 0, 1, 0, 0, 0, 0, "82839");

DELETE FROM waypoint_data WHERE id=244095;
INSERT INTO waypoint_data VALUES 
(244095, 0, 290.462, 311.5602, 61.47269, 2.041459, 0, 0, 0, 100, 0),
(244095, 1, 295.9863, 301.9465, 63.98468, 5.230174, 0, 0, 0, 100, 0),
(244095, 2, 287.7036, 296.3885, 61.5195, 3.836093, 0, 0, 0, 100, 0),
(244095, 3, 289.8757, 304.9495, 60.92257, 1.417065, 0, 0, 0, 100, 0),
(244095, 4, 300.1223, 308.6775, 66.70729, 0.191844, 0, 0, 0, 100, 0),
(244095, 5, 291.692, 316.4182, 62.46639, 2.398813, 0, 0, 0, 100, 0),
(244095, 6, 291.8988, 304.7574, 61.85199, 4.676466, 0, 0, 0, 100, 0);

-- enable quest 27952
UPDATE quest_template SET PrevQuestId=26326, ExclusiveGroup=0, NextQuestIdChain=27004 WHERE Id=27952;

-- let Earthcaller Yevaa stand
UPDATE creature_template_addon set emote=0 WHERE entry=243062;

DELETE FROM phase_area WHERE areaId=5297 AND entry=0;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(5297, 0, 26828, 26833, 74, 11, 1, "Deepholm phase 252");

DELETE FROM phase_area WHERE areaId=5298 AND entry=0;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(5298, 0, 26828, 26833, 74, 11, 1, "Deepholm phase 252");

DELETE FROM phase_area WHERE areaId=5299 AND entry=0;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(5299, 0, 26828, 26833, 74, 11, 1, "Deepholm phase 252");

