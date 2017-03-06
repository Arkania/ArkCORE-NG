
-- fix issue #137 quest 24468, 24472
UPDATE quest_template SET PrevQuestId=24472 WHERE Id=24483;

UPDATE quest_template SET PrevQuestId=24483 WHERE Id=24495;

UPDATE quest_template SET PrevQuestId=24501 WHERE Id=24578;

UPDATE quest_template SET PrevQuestId=24592 WHERE Id=24677;

UPDATE quest_template SET PrevQuestId=24627 WHERE Id=24646;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Sumpfkrokilisk", QuestGiverTargetName_loc3="Sumpfkrokilisk" WHERE Id=24468;

delete from creature where id=44108;

update creature set phaseMask=32768, spawndist=8, MovementType=1 where id=37078;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Ogerdiener", QuestGiverTargetName_loc3="Ogerdiener" WHERE Id=24472;

delete from creature where id=36293 and guid in (252356, 252359, 252360, 252361, 252362, 252363, 252367, 252368, 252378, 25239, 252381);

SET @GUID=252355;
SET @PATHID=@GUID;
UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;
INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@PATHID WHERE guid=@GUID;
DELETE FROM waypoint_data WHERE id=@PATHID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@PATHID, 0, -2278.481, 1842.174, 18.44715, 5.99264, 5000, 0),
(@PATHID, 1, -2278.481, 1842.174, 18.44715, 5.99264, 0, 0),
(@PATHID, 2, -2309.942, 1846.407, 33.21977, 2.709676, 0, 0),
(@PATHID, 3, -2322.389, 1852.35, 37.58092, 2.081357, 0, 0),
(@PATHID, 4, -2316.347, 1865.906, 41.82138, 1.39806, 0, 0),
(@PATHID, 5, -2301.361, 1889.564, 55.75282, 1.021069, 0, 0),
(@PATHID, 6, -2294.865, 1889.59, 56.70953, 0.003981, 0, 0),
(@PATHID, 7, -2280.876, 1876.983, 55.36668, 5.521405, 0, 0),
(@PATHID, 8, -2280.876, 1876.983, 55.36668, 5.521405, 5000, 0),
(@PATHID, 9, -2297.362, 1891.982, 57.28648, 2.403374, 0, 0),
(@PATHID, 10, -2302.475, 1905.195, 62.69324, 1.947843, 0, 0),
(@PATHID, 11, -2309.922, 1909.104, 66.02825, 2.64292, 0, 0),
(@PATHID, 12, -2330.363, 1917.036, 72.27673, 2.827489, 0, 0),
(@PATHID, 13, -2345.464, 1926.208, 72.76286, 2.595796, 0, 0),
(@PATHID, 14, -2364.265, 1947.78, 70.36697, 2.179537, 0, 0),
(@PATHID, 15, -2376.469, 1988.987, 71.71623, 3.169139, 0, 0),
(@PATHID, 16, -2376.469, 1988.987, 71.71623, 3.169139, 5000, 0),
(@PATHID, 17, -2376.469, 1988.987, 71.71623, 3.169139, 0, 0),
(@PATHID, 18, -2364.265, 1947.78, 70.36697, 2.179537, 0, 0),
(@PATHID, 19, -2345.464, 1926.208, 72.76286, 2.595796, 0, 0),
(@PATHID, 20, -2330.363, 1917.036, 72.27673, 2.827489, 0, 0),
(@PATHID, 21, -2309.922, 1909.104, 66.02825, 2.64292, 0, 0),
(@PATHID, 22, -2302.475, 1905.195, 62.69324, 1.947843, 0, 0),
(@PATHID, 23, -2297.362, 1891.982, 57.28648, 2.403374, 0, 0),
(@PATHID, 24, -2280.876, 1876.983, 55.36668, 5.521405, 5000, 0),
(@PATHID, 25, -2280.876, 1876.983, 55.36668, 5.521405, 0, 0),
(@PATHID, 26, -2294.865, 1889.59, 56.70953, 0.003981, 0, 0),
(@PATHID, 27, -2301.361, 1889.564, 55.75282, 1.021069, 0, 0),
(@PATHID, 28, -2316.347, 1865.906, 41.82138, 1.39806, 0, 0),
(@PATHID, 29, -2322.389, 1852.35, 37.58092, 2.081357, 0, 0),
(@PATHID, 30, -2309.942, 1846.407, 33.21977, 2.709676, 0, 0),
(@PATHID, 31, -2278.481, 1842.174, 18.44715, 5.99264, 0, 0);

update creature set phaseMask=32768 where id=36294;

update creature_template set faction=1934 where entry=37808;

update creature_template_addon set auras="80852 84481" where entry in (37805, 37806, 37807, 37808);

update creature set phaseMask=32768 where id in (37805, 37806, 37807, 37808);

SET @PATHID=2515531;
DELETE FROM waypoint_data WHERE id=@PATHID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@PATHID, 0, -2197.42, 1868.711, 18.27061, 4.141808, 0, 1),
(@PATHID, 1, -2197.42, 1868.711, 18.27061, 4.141808, 0, 1),
(@PATHID, 2, -2197.102, 1845.295, 15.62501, 5.374879, 0, 1),
(@PATHID, 3, -2173.823, 1825.345, 12.75349, 5.276709, 0, 1),
(@PATHID, 4, -2168.851, 1817.491, 14.51206, 5.276709, 0, 1),
(@PATHID, 5, -2156.115, 1811.479, 16.48027, 5.842195, 0, 1),
(@PATHID, 6, -2153.454, 1812.352, 17.10654, 0.316918, 0, 1);

update creature_template set AIName="", ScriptName="npc_prince_liam_greymane_37065" where entry=37065;


