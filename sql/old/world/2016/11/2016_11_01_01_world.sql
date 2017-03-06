
DELETE FROM phase_area WHERE areaId=4720 AND entry=2;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4720, 2, 14240, 14326, 64, 9, 0, "phase 172 from reward quest 14240 to accept 14326");

update gameobject_template set data1=207892 where entry=207892;

delete from creature where guid in (248081, 248082, 248084, 248085, 248086, 248088, 248089, 248090, 248091, 248092);
INSERT INTO creature VALUES 
(248081, 36176, 648, 0, 0, 1, "179", 0, 0, 0, 975.478, 3798.85, 14.7504, 0.813797, 500, 0, 0, 137, 0, 0, 0, 0, 0), 
(248082, 36176, 648, 0, 0, 1, "179", 0, 0, 0, 965.548, 3798.65, 15.9251, 1.12796, 500, 0, 0, 120, 0, 0, 0, 0, 0), 
(248084, 36176, 648, 0, 0, 1, "179", 0, 0, 0, 991.446, 3837.88, 13.0503, 1.018, 500, 0, 0, 137, 0, 0, 0, 0, 0), 
(248085, 36176, 648, 0, 0, 1, "179", 0, 0, 0, 990.977, 3818.92, 8.91223, 0.0873046, 500, 0, 0, 120, 0, 0, 0, 0, 0), 
(248086, 36176, 648, 0, 0, 1, "179", 0, 0, 0, 976.468, 3832.79, 8.99501, 4.3049, 500, 0, 0, 120, 0, 0, 0, 0, 0), 
(248088, 36176, 648, 0, 0, 1, "179", 0, 0, 0, 984.518, 3845.78, 3.23032, 0.381835, 500, 0, 0, 137, 0, 0, 0, 0, 0), 
(248089, 36176, 648, 0, 0, 1, "179", 0, 0, 0, 975.456, 3832.28, 3.23141, 0.350419, 500, 0, 0, 120, 0, 0, 0, 0, 0), 
(248090, 36176, 648, 0, 0, 1, "179", 0, 0, 0, 988.361, 3829.57, 3.23183, 2.34926, 500, 0, 0, 137, 0, 0, 0, 0, 0), 
(248091, 36176, 648, 0, 0, 1, "179", 0, 0, 0, 966.684, 3810.58, 3.23091, 0.966956, 500, 0, 0, 137, 0, 0, 0, 0, 0), 
(248092, 36176, 648, 0, 0, 1, "179", 0, 0, 0, 970.803, 3822.01, 3.23091, 2.81264, 500, 0, 0, 120, 0, 0, 0, 0, 0); 

DELETE FROM creature_addon WHERE guid=248081;
INSERT INTO creature_addon VALUES 
(248081, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature_addon WHERE guid=248082;
INSERT INTO creature_addon VALUES 
(248082, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature_addon WHERE guid=248084;
INSERT INTO creature_addon VALUES 
(248084, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature_addon WHERE guid=248085;
INSERT INTO creature_addon VALUES 
(248085, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature_addon WHERE guid=248086;
INSERT INTO creature_addon VALUES 
(248086, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature_addon WHERE guid=248088;
INSERT INTO creature_addon VALUES 
(248088, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature_addon WHERE guid=248089;
INSERT INTO creature_addon VALUES 
(248089, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature_addon WHERE guid=248090;
INSERT INTO creature_addon VALUES 
(248090, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature_addon WHERE guid=248091;
INSERT INTO creature_addon VALUES 
(248091, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature_addon WHERE guid=248092;
INSERT INTO creature_addon VALUES 
(248092, 0, 0, 0, 1, 0, "29266");

delete from creature where guid=34388;

update phase_area set flags=1 where areaId=4720 and entry in (1, 2);