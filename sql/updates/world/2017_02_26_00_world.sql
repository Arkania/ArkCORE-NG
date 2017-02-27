

delete from game_event_creature where eventEntry=1 and guid=192132;

delete from game_event_seasonal_questrelation where questId=24615 and eventEntry=335;
delete from game_event_seasonal_questrelation where questId=24615 and eventEntry=8;
insert into game_event_seasonal_questrelation values
(24615, 8);

update gameobject_template set ScriptName="go_worgen_gunship_203428" where entry=203428;

delete from spell_script_names where spell_id=72886;
insert into spell_script_names values
(72886, "spell_rocket_boots_damage_effect_72886");

delete from smart_scripts where entryorguid=38753;

UPDATE creature_template SET AIName="", ScriptName="npc_goblin_zombie_38753" WHERE entry=38753;

UPDATE quest_template SET NextQuestId=24952, ExclusiveGroup=-24945 WHERE Id=24942;

UPDATE gameobject SET phaseId=182 WHERE guid=404094;

DELETE FROM waypoint_data WHERE id=2383701;
INSERT INTO waypoint_data VALUES 
(2383701, 0, 1475.434, 1975.518, 238.0769, 1.490936, 0, 0, 0, 100, 0),
(2383701, 1, 1476.444, 1987.504, 236.7882, 1.506644, 0, 0, 0, 100, 0),
(2383701, 2, 1477.28, 1998.328, 235.506, 2.244914, 0, 0, 0, 100, 0),
(2383701, 3, 1471.282, 2009.833, 233.734, 2.001441, 0, 0, 0, 100, 0),
(2383701, 4, 1478.1, 2020.926, 232.5404, 1.019693, 0, 0, 0, 100, 0),
(2383701, 5, 1477.951, 2031.855, 231.456, 1.620522, 2000, 0, 0, 100, 0),
(2383701, 6, 1478.1, 2020.926, 232.5404, 1.019693, 0, 0, 0, 100, 0),
(2383701, 7, 1471.282, 2009.833, 233.734, 2.001441, 0, 0, 0, 100, 0),
(2383701, 8, 1477.28, 1998.328, 235.506, 2.244914, 0, 0, 0, 100, 0),
(2383701, 9, 1476.444, 1987.504, 236.7882, 1.506644, 0, 0, 0, 100, 0);

delete from smart_scripts where entryorguid in (38745, 38409);

UPDATE creature_template SET AIName="", ScriptName="npc_goblin_survivor_38409" WHERE entry=38409;

UPDATE creature_template SET AIName="", ScriptName="npc_kezan_citizen_38745" WHERE entry=38745;

delete from spell_script_names where spell_id=72944;
insert into spell_script_names values
(72944, "spell_shoot_72944");

delete from creature where guid in (286150, 286151, 286152, 286153, 286154, 286155, 286156, 286157, 286158, 286159, 286160, 286161);
delete from creature where guid in (286162, 286163, 286164, 286165, 286166, 286167, 286168, 286169, 286170, 286171, 286172, 286173);
delete from creature where guid in (286174, 286175, 286176, 286177, 286178, 286179, 286180, 286181, 286182, 286183, 286184, 286185, 286186);

update creature set phaseId=182, phaseGroup=0, position_z=166.5, spawndist=20.0, MovementType=1 where guid in (248630, 248631);

UPDATE creature_template SET unit_flags=32768, dynamicflags=0, ScriptName="npc_volcanoth_champion_38850" WHERE entry=38850;

UPDATE creature_template SET unit_flags=33280, dynamicflags=0, ScriptName="" WHERE entry=38851;

update creature set phaseId=182, phaseGroup=0, spawndist=0, MovementType=0 where id in (38850, 38851);

delete from creature_addon where guid in (249682,249683,249685,249688,249690,249691,249694,249695);

delete from waypoint_data where id in (249682,249683,249685,249688,249690,249691,249694,249695);

delete from creature where guid in (4018, 7018, 248235, 248236);

UPDATE creature SET spawndist=0 WHERE guid=5807;

DELETE FROM creature_addon WHERE guid=286175;
DELETE FROM creature_addon WHERE guid=286176;
DELETE FROM creature_addon WHERE guid=286179;
DELETE FROM creature_addon WHERE guid=286181;
DELETE FROM creature_addon WHERE guid=286185;

DELETE FROM creature_addon WHERE guid=285805;
INSERT INTO creature_addon VALUES 
(285805, 0, 0, 0, 1, 0, "");

UPDATE creature_template SET unit_flags=33536, ScriptName="npc_doc_zapnozzle_36615" WHERE entry=36615;

UPDATE creature SET map=648, zoneId=4720, areaId=4909, position_x=1472.524, position_y=1222.168, position_z=121.1354, orientation=2.829472 WHERE id=38409 AND guid=284436;
UPDATE creature SET map=648, zoneId=4720, areaId=4909, position_x=1471.674, position_y=1228.503, position_z=119.6856, orientation=3.190755 WHERE id=38647 AND guid=2133;
UPDATE creature SET map=648, zoneId=4720, areaId=4909, position_x=1476.136, position_y=1225.934, position_z=119.909, orientation=3.281077 WHERE id=36615 AND guid=248235;
UPDATE creature SET map=648, zoneId=4720, areaId=4909, position_x=1441.08, position_y=1283.753, position_z=115.4878, orientation=3.320349 WHERE id=38409 AND guid=284453;
UPDATE creature SET map=648, zoneId=4720, areaId=4909, position_x=1436.683, position_y=1288.995, position_z=116.3467, orientation=4.015427 WHERE id=38745 AND guid=285805;

DELETE FROM waypoint_data WHERE id=5807;
INSERT INTO waypoint_data VALUES 
(5807, 0, 1439.191, 1283.92, 115.9321, 5.134604, 5000, 0, 0, 100, 0),
(5807, 1, 1442.502, 1275.972, 114.8671, 5.016801, 0, 0, 0, 100, 0),
(5807, 2, 1446.246, 1266.939, 111.7409, 5.091412, 0, 0, 0, 100, 0),
(5807, 3, 1447.819, 1265.061, 110.7109, 5.154245, 0, 0, 0, 100, 0),
(5807, 4, 1449.98, 1260.51, 110.8993, 5.154246, 0, 0, 0, 100, 0),
(5807, 5, 1455.657, 1247.472, 115.3108, 5.236711, 0, 0, 0, 100, 0),
(5807, 6, 1460.168, 1239.981, 117.6581, 5.181734, 0, 0, 0, 100, 0),
(5807, 7, 1463.237, 1233.956, 119.0072, 5.189584, 0, 0, 0, 100, 0),
(5807, 8, 1466.382, 1226.805, 121.0561, 5.126753, 5000, 0, 0, 100, 0),
(5807, 9, 1463.237, 1233.956, 119.0072, 5.189584, 0, 0, 0, 100, 0),
(5807, 10, 1460.168, 1239.981, 117.6581, 5.181734, 0, 0, 0, 100, 0),
(5807, 11, 1455.657, 1247.472, 115.3108, 5.236711, 0, 0, 0, 100, 0),
(5807, 12, 1449.98, 1260.51, 110.8993, 5.154246, 0, 0, 0, 100, 0),
(5807, 13, 1447.819, 1265.061, 110.7109, 5.154245, 0, 0, 0, 100, 0),
(5807, 14, 1446.246, 1266.939, 111.7409, 5.091412, 0, 0, 0, 100, 0),
(5807, 15, 1442.502, 1275.972, 114.8671, 5.016801, 0, 0, 0, 100, 0);

UPDATE creature SET phaseId=182, phaseGroup=0, position_x=1474.581, position_y=1225.161, position_z=120.506, spawndist=0, MovementType=0 WHERE guid=247540;

UPDATE creature SET phaseId=182, phaseGroup=0, position_x=1435.781, position_y=1280.41, position_z=116.856, spawndist=0, MovementType=0 WHERE guid=247541;

UPDATE creature SET phaseId=182, phaseGroup=0, position_x=1439.971, position_y=1289.561, position_z=115.674, spawndist=0, MovementType=0 WHERE guid=247542;

UPDATE creature SET phaseId=182, phaseGroup=0, position_x=1465.211, position_y=1229.331, position_z=120.463, spawndist=0, MovementType=0 WHERE guid=247543;

UPDATE creature_template_addon SET bytes1=33554432 WHERE entry=36719;

UPDATE creature_template SET InhabitType=4 WHERE entry=39039;

UPDATE creature_template SET InhabitType=4 WHERE entry=39041;

UPDATE creature_template SET InhabitType=4 WHERE entry=39042;

UPDATE creature SET position_z=155.237 WHERE guid=248632;

UPDATE creature_template SET unit_flags=32768 WHERE entry=38745;

