
-- quest from 14241
UPDATE quest_template SET Flags=262144 WHERE Id=14242;

DELETE FROM waypoint_data WHERE id=3614300;
INSERT INTO waypoint_data VALUES 
(3614300, 0, 853.6213, 3383.1, 13.31976, 1.368966, 0, 1, 0, 0, 0),
(3614300, 1, 887.4018, 3583.488, 22.0491, 1.41609, 0, 1, 0, 0, 0),
(3614300, 2, 896.8307, 3718.879, 24.08905, 1.427871, 0, 1, 0, 0, 0),
(3614300, 3, 916.0195, 3812.283, 24.05813, 1.043026, 0, 1, 0, 0, 0),
(3614300, 4, 949.0226, 3818.146, 20.40611, 5.857518, 0, 1, 0, 0, 0),
(3614300, 5, 973.5071, 3801.469, 14.43402, 5.594413, 0, 1, 0, 0, 0),
(3614300, 6, 974.5879, 3800.579, 14.50429, 5.594413, 0, 1, 0, 0, 0);

UPDATE creature_text SET sound=1343 WHERE entry=36112 AND groupid=0 AND id=0;

-- gyrochoppa flying to ships.
UPDATE creature_template SET unit_flags=8, VehicleId=505, InhabitType=4 WHERE entry=36143;

DELETE FROM creature_template_addon WHERE entry=36143;
INSERT INTO creature_template_addon VALUES 
(36143, 0, 0, 50331648, 1, 0, "");

UPDATE creature_template SET Scale=0.9, ScriptName="npc_thrall_36145" WHERE entry=36145;

-- gyrochoppa on the beach
UPDATE creature_template SET ScriptName="npc_gyrochoppa_36127" WHERE entry=36127;

delete from creature where guid in (248081, 248082, 248084, 248085, 248086, 248088, 248089, 248090, 248092);

delete from creature_questender where id=36145 and quest=14242;
insert into creature_questender values 
(36145, 14242);
delete from creature_queststarter where id=36145 and quest=14242;

DELETE FROM phase_definitions WHERE zoneId=4720 and entry in (3, 4, 5, 6, 7, 8, 9, 10);
INSERT INTO phase_definitions VALUES 
(4720, 3, 179, 0, 0, 1, "Comment for phase 179"),
(4720, 4, 180, 661, 681, 1, "Comment for phase 180 : Zone town in a box Id: 4871"),
(4720, 5, 181, 661, 681, 1, "Comment for phase 181"),
(4720, 6, 182, 661, 681, 1, "Comment for phase 182"),
(4720, 7, 183, 661, 681, 1, "Comment for phase 183-1"),
(4720, 8, 183, 659, 682, 1, "Comment for phase 183-2"),
(4720, 9, 184, 659, 682, 1, "Comment for phase 184"),
(4720, 10, 185, 659, 682, 1, "Comment for phase 185");

-- from accept quest 14326, next phase 179 are enabled by cast a aura spell..
-- [179] Spell ID: Quest Phase 04 (67854)
-- [180] Spell ID: It's A Town-In-A-Box: Town-In-A-Box Plunger - Effect 2 (71091), Quest Phase 05
delete from phase_area where areaId=4720 and entry in (3,4,5);
-- insert into phase_area values 
-- (4720, 3, 14326, 14245, 74, 11, 0, "phase 179 from accept quest to accept of quest 14245 'Town in a Box' " ),
-- (4720, 4, 14326, 14245, 74, 11, 0, "phase 180 from accept quest to..." ),












