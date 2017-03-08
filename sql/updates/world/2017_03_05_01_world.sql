
UPDATE creature_template SET ScriptName="npc_elm_general_purpose_bunny_infinite_hide_body_43359" WHERE entry=43359;

-- 74070 Volcano: Fiery Boulder - South
-- 74072 Volcano: Fiery Boulder - West
-- 74076 Volcano: Fiery Boulder - North
-- 74085 Volcano: Fiery Boulder - East
-- the invisible bunny 43359 cast random Fiery Boulder.. but the 43359 are to far away..  position_z > 400.. the script can't work..
 
UPDATE creature_template SET ScriptName="npc_giant_fireball_bunny_38979" WHERE entry=38979;

DELETE FROM waypoint_data WHERE id=3897900;
INSERT INTO waypoint_data VALUES 
(3897900, 0, 1069.349, 1176.637, 145.1329, 0, 0, 1, 0, 100, 0),
(3897900, 1, 1073.618, 1174.343, 142.0087, 0, 0, 1, 0, 100, 0),
(3897900, 2, 1072.83, 1174.958, 142.0087, 0, 0, 1, 0, 100, 0),
(3897900, 3, 1070.681, 1175.856, 145.2476, 0, 0, 1, 0, 100, 0),
(3897900, 4, 1022.609, 1205.441, 137.8309, 0, 0, 1, 0, 100, 0),
(3897900, 5, 998.6702, 1247.134, 122.0526, 0, 0, 1, 0, 100, 0),
(3897900, 6, 991.2604, 1303.075, 107.4414, 0, 0, 1, 0, 100, 0),
(3897900, 7, 1019.76, 1385.986, 96.35801, 0, 0, 1, 0, 100, 0),
(3897900, 8, 1038.009, 1454.017, 102.6914, 0, 0, 1, 0, 100, 0),
(3897900, 9, 1014.885, 1528.847, 125.9074, 0, 0, 1, 0, 100, 0),
(3897900, 10, 936.3646, 1576.932, 163.9337, 0, 0, 1, 0, 100, 0),
(3897900, 11, 936.3646, 1576.932, 163.9337, 0, 0, 1, 0, 100, 0),
(3897900, 12, 936.3646, 1576.932, 163.9337, 0, 0, 1, 0, 100, 0);

UPDATE quest_template SET NextQuestIdChain=25251 WHERE Id=25244;

UPDATE quest_template SET PrevQuestId=0 WHERE Id=25251;



