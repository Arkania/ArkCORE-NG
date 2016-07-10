
UPDATE creature_template SET AIName="", ScriptName="npc_forsaken_crossbowman_38210" WHERE entry=38210;

delete from smart_scripts where entryorguid=38210;

DELETE FROM creature WHERE id=38470; -- King Genn Greymane .. 
INSERT INTO creature VALUES 
(18584, 38470, 654, 1, 262144, 0, 0, -1750.84, 1670.42, 22.158, 5.6022, 120, 0, 0, 1, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=38469; -- Lady Sylvanas Windrunner
INSERT INTO creature VALUES 
(18585, 38469, 654, 1, 262144, 30776, 1, -1678.06, 1611.81, 20.5728, 2.44346, 300, 3, 0, 27600, 5900, 1, 0, 0, 0);

DELETE FROM creature WHERE id=38426; -- Lorna Crowley
INSERT INTO creature VALUES 
(18586, 38426, 654, 1, 262144, 0, 0, -1549.21, 1285.97, 11.7804, 3.47383, 90, 0, 0, 1, 0, 0, 0, 0, 0);

UPDATE creature_template SET AIName="", ScriptName="npc_king_genn_greymane_38470" WHERE entry=38470;

UPDATE creature_template SET AIName="", ScriptName="npc_lady_sylvanas_windrunner_38469" WHERE entry=38469;

UPDATE creature_template SET ScriptName="npc_lorna_crowley_38426" WHERE entry=38426;

delete from smart_scripts where entryorguid in (38470, 38469);

DELETE FROM phase_area WHERE areaId=4714 AND entry=2;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4714, 2, 24676, 99999, 74, 11, 0, "Gilneas City Battle");

DELETE FROM phase_area WHERE areaId=4755 AND entry=2;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4755, 2, 24676, 99999, 74, 11, 0, "Gilneas City Battle");


