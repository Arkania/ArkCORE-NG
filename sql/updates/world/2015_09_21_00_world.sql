
-- on some buildings you are leave the zone 4755 and enter 4714 Gilneas.. blizzard area failure?? so we have to expand our zone/area table for entry 4714..
delete from phase_area where areaId=4714 and entry between 0 and 3;
insert into phase_area values (4714, 0, 14091, 14091, 11, 64, 0, "Gilneas phase 1");
insert into phase_area values (4714, 1, 14091, 14159, 74, 64, 0, "Gilneas phase 2");
insert into phase_area values (4714, 2, 14099, 14204, 64, 72, 0, "Gilneas phase 4");
insert into phase_area values (4714, 3, 14204, 12345, 74, 72, 0, "Gilneas phase 8");

delete from phase_definitions where zoneId=4714 and entry between 0 and 3;
insert into phase_definitions values (4714, 0, 1, 0, 638, 0, 1, "Gilneas player startposition");
insert into phase_definitions values (4714, 1, 2, 0, 638, 0, 1, "Gilneas phase 2");
insert into phase_definitions values (4714, 2, 4, 0, 638, 0, 0, "Gilneas phase 4");
insert into phase_definitions values (4714, 3, 8, 0, 638, 0, 1, "Gilneas phase 8");

-- spawned by script
delete from creature where id in (38210, 38348);

update creature_template set AIName="", ScriptName="npc_king_genn_greymane_35112" where entry=35112;
update creature_template set AIName="", ScriptName="npc_lord_godfrey_35115" where entry=35115;
update creature_template set AIName="", ScriptName="npc_bloodfang_worgen_35118" where entry=35118;
update creature_template set AIName="", ScriptName="npc_tobias_mistmantle_35124" where entry=35124;

delete from creature_text where entry=35369;
insert into creature_text values (35369, 0, 0, "What's wrong with me??!", 14, 0, 100, 0, 0, 0, "Quest The Rebel Lord's Arsenal RANDOM_JOSIAH_YELL", 38736);
insert into creature_text values (35369, 1, 0, "My face! What's wrong with my face!", 14, 0, 100, 0, 0, 0, "Quest The Rebel Lord's Arsenal RANDOM_JOSIAH_YELL", 38737);
insert into creature_text values (35369, 2, 0, "My hands... don't look at my hands!", 14, 0, 100, 0, 0, 0, "Quest The Rebel Lord's Arsenal RANDOM_JOSIAH_YELL", 38738);
insert into creature_text values (35369, 3, 0, "The pain is unbearable!", 14, 0, 100, 0, 0, 0, "Quest The Rebel Lord's Arsenal SAY_WORGEN_BITE", 38739);
insert into creature_text values (35369, 4, 0, "Make it stop!", 14, 0, 100, 0, 0, 0, "Quest The Rebel Lord's Arsenal RANDOM_JOSIAH_YELL", 38740);
insert into creature_text values (35369, 5, 0, "I can't fight it!", 14, 0, 100, 0, 0, 0, "Quest The Rebel Lord's Arsenal RANDOM_JOSIAH_YELL", 38741);

update creature set phaseMask=2 where guid in (250195, 250197, 250198, 250218, 250202);

update creature_template set minlevel=5, maxlevel=5 where entry=35112;

UPDATE quest_template SET PrevQuestId=14154 WHERE Id=14159;

update creature_template_addon set auras="34189" where entry=35871;

delete from creature where guid in (251448, 251456, 251453);

UPDATE creature_template SET unit_flags=32768, dynamicflags=0 WHERE entry=2647;

update gameobject set phaseMask=6, state=1 where guid=166796;
update gameobject set phaseMask=1, state=0  where guid=166801;

delete from creature where id=34916 and guid in(250198, 250199, 250278, 250279, 250280, 250281);
insert into creature values
(250198, 34916, 654, 1, 2, 0, 0, -1767.91, 1405.72, 19.7933, 5.4925,  500, 0, 0, 52668, 0, 0, 0, 0, 0),
(250199, 34916, 654, 1, 2, 0, 0, -1733.99, 1416.65, 21.669,  5.80578, 500, 0, 0, 52668, 0, 0, 0, 0, 0),
(250278, 34916, 654, 1, 2, 0, 0, -1795.0,  1395.63, 19.892,  4.81814, 500, 0, 0, 40328, 0, 0, 0, 0, 0),
(250279, 34916, 654, 1, 2, 0, 0, -1799.22, 1394.71, 19.8935, 5.0891,  500, 0, 0, 23856, 0, 0, 0, 0, 0),
(250280, 34916, 654, 1, 2, 0, 0, -1803.0,  1391.03, 20.2854, 5.44253, 500, 0, 0, 31240, 0, 0, 0, 0, 0),
(250281, 34916, 654, 1, 2, 0, 0, -1790.93, 1396.96, 20.2941, 5.1323,  500, 0, 0, 40328, 0, 0, 0, 0, 0);


delete from creature where id=35504;
insert into creature values
(251114, 35504, 654, 1, 4, 29466, 0, -1766.27, 1409.79, 19.8657, 5.11381, 300, 3, 0, 207, 79, 1, 0, 0, 0),
(251115, 35504, 654, 1, 4, 29467, 0, -1770.87, 1409.41, 19.7831, 0.222471, 300, 3, 0, 207, 79, 1, 0, 0, 0),
(251116, 35504, 654, 1, 4, 29826, 0, -1798.91, 1399.47, 19.8947, 5.18618, 300, 3, 0, 207, 79, 1, 0, 0, 0),
(251117, 35504, 654, 1, 4, 29466, 0, -1769.11, 1410.07, 19.8657, 5.0463, 300, 3, 0, 207, 79, 1, 0, 0, 0),
(251118, 35504, 654, 1, 4, 29826, 0, -1799.77, 1402.17, 19.9723, 4.95674, 300, 3, 0, 207, 79, 1, 0, 0, 0),
(251119, 35504, 654, 1, 4, 29466, 0, -1755.9,  1409.44, 19.8655, 5.11381, 300, 3, 0, 207, 79, 1, 0, 0, 0),
(251184, 35504, 654, 1, 4, 29826, 0, -1800.22, 1398.86, 19.9878, 5.11381, 300, 3, 0, 207, 79, 1, 0, 0, 0),
(251185, 35504, 654, 1, 4, 29467, 0, -1798.17, 1404.51, 19.9237, 5.16617, 300, 3, 0, 207, 79, 1, 0, 0, 0),
(251186, 35504, 654, 1, 4, 29826, 0, -1767.91, 1405.72, 19.7933, 2.08387, 300, 3, 0, 207, 79, 1, 0, 0, 0),
(251187, 35504, 654, 1, 4, 29466, 0, -1803.91, 1395.08, 20.3679, 5.04637, 300, 3, 0, 207, 79, 1, 0, 0, 0),
(251188, 35504, 654, 1, 4, 29466, 0, -1759.49, 1410.24, 20.9499, 5.11381, 300, 3, 0, 207, 79, 1, 0, 0, 0);

UPDATE creature_template SET KillCredit1=35118 WHERE entry=35916;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Lord Godfrey im Militärviertel in Gilneas zurück." WHERE Id=24930;

DELETE FROM `creature` WHERE `guid` in (278395, 278396);
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES
(278395, 35118, 654, 1, 2, 0, 0, -1725.81, 1449.33, 52.2857, 2.56687, 300, 0, 0, 71, 0, 0, 0, 0, 0),
(278396, 35118, 654, 1, 2, 0, 0, -1738.17, 1436.62, 52.2899, 3.91383, 300, 0, 0, 55, 0, 0, 0, 0, 0);

update creature_template_addon set path_id=0 where entry in (35170, 35188, 35456, 35167);
update creature_template set MovementType=0 where entry in (35170, 35188, 35456, 35167);
delete from waypoint_data where id in (351700, 351880, 354560, 351670);

UPDATE creature_template SET flags_extra=0 WHERE entry=35124;

