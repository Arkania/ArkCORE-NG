
-- fix in stormwind for quest call of duty

UPDATE creature SET phaseId=0, phaseGroup=368 WHERE guid=27023;

UPDATE creature SET phaseId=0, phaseGroup=368 WHERE guid in (1112, 1171, 1172, 1173, 1176, 1189, 1190, 49026, 48700, 48894);

delete from creature where guid in (51723, 51724, 117108, 117109);

update creature_text set sound=21336, emote=396 where entry=42021 and groupid=0 and id=0;

update creature set phaseId=171 where id=42094;

UPDATE creature SET phaseId=171 WHERE guid in (51749, 51750, 51751, 51752, 51753, 51754, 51755, 51756, 51757, 51758);

DELETE FROM creature WHERE id=39480 AND guid=11346;
INSERT INTO creature VALUES 
(11346, 39480, 674, 0, 0, 1, 171, 0, 0, 0, -13.17935, -0.025574, 5.655972, 0, 300, 0, 0, 1, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=39460 AND guid=80867;
INSERT INTO creature VALUES 
(80867, 39460, 674, 0, 0, 1, 171, 0, 0, 0, -14.88076, 4.362975, 5.622851, 2.129302, 300, 0, 0, 1, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=40559 AND guid=51725;
INSERT INTO creature VALUES 
(51725, 40559, 674, 0, 0, 1, 171, 0, 21342, 0, 7.730865, -0.805738, 5.262063, 3.01727, 300, 0, 0, 1, 0, 0, 0, 0, 0, 0);

UPDATE creature_template SET ScriptName="npc_ship_to_vashjir_phase_caster_bunny_40559" WHERE entry=40559;

UPDATE creature_template_addon SET auras="" WHERE entry=40559;

DELETE FROM creature WHERE id=39447 AND guid=51715;
INSERT INTO creature VALUES 
(51715, 39447, 674, 0, 0, 1, 171, 0, 0, 0, 36.46296, 0.054415, 12.03765, 3.106686, 300, 0, 0, 1, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=39478 AND guid=42968;
INSERT INTO creature VALUES 
(42968, 39478, 674, 0, 0, 1, 171, 0, 0, 0, 15.46177, -3.40272, 5.150597, 3.106686, 300, 0, 0, 1, 0, 0, 0, 0, 0, 0);

delete from creature where id=42202;

UPDATE gameobject_template SET ScriptName="go_ship_to_vashjir_197195" WHERE entry=197195;

UPDATE gameobject_template SET ScriptName="go_ship_to_vashjir_203466" WHERE entry=203466;

DELETE FROM creature WHERE id=43091 AND guid=42993;
INSERT INTO creature VALUES 
(42993, 43091, 1, 0, 0, 1, 171, 0, 21342, 0, 1453.23, -5033.88, 12.2535, 3.36792, 300, 0, 0, 1, 0, 0, 0, 0, 0, 0);

UPDATE creature_template SET ScriptName="npc_totally_generic_bunny_phase_43091" WHERE entry=43091;

update creature set zoneId=0, areaId=0, phaseId=171, phaseGroup=0, spawntimesecs=300, curhealth=24916 where map=738 and id in (43051, 43030, 43022, 43023);

DELETE FROM creature WHERE id=40559 AND guid=117108;
INSERT INTO creature VALUES 
(117108, 40559, 738, 0, 0, 1, 171, 0, 21342, 0, 7.730865, -0.805738, 5.262063, 3.01727, 300, 0, 0, 1, 0, 0, 0, 0, 0, 0);

UPDATE creature SET phaseId=0, phaseGroup=393 WHERE guid=49800;

DELETE FROM creature WHERE id=32520 AND guid=43007;
INSERT INTO creature VALUES 
(43007, 32520, 1, 0, 0, 1, 0, 393, 0, 0, 1440.01, -5040.01, 12.057, 0, 300, 0, 0, 1, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=42982 AND guid=43017;
INSERT INTO creature VALUES 
(43017, 42982, 738, 0, 0, 1, 171, 0, 0, 0, 16.087, 5.076, 5.016, 3.073, 300, 0, 0, 1, 0, 0, 0, 0, 0, 0);

UPDATE creature_template SET ScriptName="npc_totally_generic_bunny_all_phase_32520" WHERE entry=32520;

UPDATE creature_template SET ScriptName="npc_legionnaire_nazgrim_43100" WHERE entry=43100;

UPDATE creature_template SET ScriptName="npc_hellscreams_vanguard_43090" WHERE entry=43090;

update creature set spawntimesecs=120 where id in (43090, 43100);

DELETE FROM waypoint_data WHERE id=1171111; -- nazgrim
DELETE FROM waypoint_data WHERE id=1170961; -- vanguard_1
DELETE FROM waypoint_data WHERE id=1170991; -- vanguard_2
DELETE FROM waypoint_data WHERE id=1171001; -- vanguard_3
DELETE FROM waypoint_data WHERE id=1171101; -- vanguard_4
DELETE FROM waypoint_data WHERE id=1171121; -- vanguard_5
DELETE FROM waypoint_data WHERE id=1188451; -- vanguard_6














            