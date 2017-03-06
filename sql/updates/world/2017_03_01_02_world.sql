UPDATE creature_template SET ScriptName="npc_volcanoth_38855" WHERE entry=38855;

DELETE FROM phase_area WHERE areaId=4720 AND entry=6;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4720, 6, 24937, 24958, 74, 9, 1, "Lost Isles Town in a Box, phase 182, from 'Oomlot Dealt With' to 'Volcanoth!' ");

DELETE FROM phase_area WHERE areaId=4720 AND entry=7;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4720, 7, 24958, 25023, 66, 11, 1, "Lost Isles Town in a Box, phase 183, from 'Volcanoth!' to 'Old Friends' ");

DELETE FROM phase_area WHERE areaId=4720 AND entry=8;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4720, 8, 24958, 39335, 66, 11, 1, "Lost Isles Volcano Eruption, phase 183, from 'Volcanoth!' to 'Wild Mine Cart Ride' ");

UPDATE quest_template SET QuestGiverPortrait=34145, RequiredNpcOrGo1=45199 WHERE Id=27066;

UPDATE creature_template SET InhabitType=4 WHERE entry=38929;
