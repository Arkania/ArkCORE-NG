
UPDATE quest_template SET NextQuestIdChain=24920 WHERE Id=24903;

UPDATE quest_template SET Flags=8, NextQuestIdChain=24678 WHERE Id=24920;

update creature set phaseMask=2883584 where id in (38614, 38539, 37889, 37891, 37892, 38615, 39015);

update creature set phaseMask=14155776 where id in (38150);

update creature set phaseMask=983040 where id in (38287);

UPDATE creature_template SET npcflag=16777216, ScriptName="" WHERE entry=38615;

UPDATE creature_template SET VehicleId=0 WHERE entry=38615;

UPDATE creature SET phaseMask=524288 WHERE guid=24573;

UPDATE creature SET phaseMask=524288 WHERE guid=26582;

UPDATE creature_template SET InhabitType=4, ScriptName="npc_captured_riding_bat_38540" WHERE entry=38540;

UPDATE creature SET position_x=-1673.73, position_y=1658.628, position_z=20.489, orientation=0.5966 WHERE guid=24573;

DELETE FROM creature WHERE id=44388 AND guid=26582;
INSERT INTO creature VALUES 
(26582, 44388, 654, 1, 524288, 0, 0, -1663.35, 1658.1, 20.4894, 2.06499, 500, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_template_addon WHERE entry=38540;
INSERT INTO creature_template_addon VALUES 
(38540, 0, 0, 33554432, 0, 0, "");

delete from phase_definitions where zoneId=4714 and entry=3;
INSERT INTO `phase_definitions` VALUES (4714, 3, 524288, 0, 656, 679, 1, "(Vengeance or Survival) to (Patriarch\'s Blessing)");

DELETE FROM phase_area WHERE areaId=4714 AND entry=3;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4714, 3, 24902, 24679, 64, 11, 1, "(Vengeance or Survival) to (Patriarch's Blessing)");

delete from spell_script_names where spell_id=72849;
insert into spell_script_names values 
(72849, "spell_fly_back_72849");

DELETE FROM waypoint_data WHERE id=3854001;
INSERT INTO waypoint_data VALUES 
(3854001, 0, -1671.259277, 1664.473633, 22.170950, 1.798105, 0, 1, 0, 100, 0),
(3854001, 1, -1681.305420, 1701.839233, 36.116096, 1.833448, 0, 1, 0, 100, 0),
(3854001, 2, -1581.880859, 1779.514771, 74.067627, 0.663204, 0, 1, 0, 100, 0),
(3854001, 3, -1448.941650, 1798.372803, 74.613380, 0.140914, 0, 1, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=3854002;
INSERT INTO waypoint_data VALUES
(3854002, 0, -1338.347778, 1808.891602, 70.0, 0.508483, 0, 1, 0, 100, 0),
(3854002, 1, -1274.626343, 1825.017578, 70.0, 0.134634, 0, 1, 0, 100, 0),
(3854002, 2, -1340.714478, 1461.107544, 70.0, 4.470029, 0, 1, 0, 100, 0),
(3854002, 3, -1293.453003, 1424.857544, 70.0, 5.739233, 0, 1, 0, 100, 0),
(3854002, 4, -1228.931641, 1473.459595, 70.0, 0.649853, 0, 1, 0, 100, 0),
(3854002, 5, -1199.912964, 1549.127563, 70.0, 1.177641, 0, 1, 0, 100, 0),
(3854002, 6, -1242.192017, 1670.079102, 70.0, 1.831092, 0, 1, 0, 100, 0),
(3854002, 7, -1214.064209, 1699.221069, 70.0, 0.806932, 0, 1, 0, 100, 0),
(3854002, 8, -925.950623, 1548.444214, 70.0, 5.899453, 0, 1, 0, 100, 0),
(3854002, 9, -880.131104, 1633.386108, 70.0, 1.878217, 0, 1, 0, 100, 0),
(3854002, 10, -920.155762, 1711.755615, 70.0, 2.792421, 0, 1, 0, 100, 0),
(3854002, 11, -1101.337646, 1771.179199, 70.0, 2.861537, 0, 1, 0, 100, 0),
(3854002, 12, -1200.921509, 1834.714600, 70.0, 2.585077, 0, 1, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=3854003;
INSERT INTO waypoint_data VALUES 
(3854003, 0, -1448.941650, 1798.372803, 74.613380, 0.140914, 0, 1, 0, 100, 0),
(3854003, 1, -1581.880859, 1779.514771, 79.067627, 0.663204, 0, 1, 0, 100, 0),
(3854003, 2, -1681.305420, 1701.839233, 36.116096, 1.833448, 0, 1, 0, 100, 0),
(3854003, 3, -1671.259277, 1664.473633, 22.170950, 1.798105, 0, 1, 0, 100, 0);

UPDATE gameobject_template SET flags=4, data8=24602 WHERE entry=201871;

update gameobject_loot_template set QuestRequired=1 where entry=201871 and item=49921;

UPDATE gameobject_template SET data4=24679 WHERE entry=201964;

DELETE FROM phase_definitions WHERE zoneId=4714 AND entry=4;
INSERT INTO phase_definitions VALUES 
(4714, 4, 1048576, 0, 656, 679, 1, "(Patriarch's Blessing) to (They Have Allies, But So Do We)");

DELETE FROM phase_area WHERE areaId=4714 AND entry=4;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4714, 4, 24679, 24681, 64, 9, 1, "(Patriarch's Blessing) to (They Have Allies, But So Do We)");





