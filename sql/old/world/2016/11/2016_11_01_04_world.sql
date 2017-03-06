

DELETE FROM phase_definitions WHERE zoneId=4720;
DELETE FROM phase_area WHERE areaId=4720;

DELETE FROM phase_definitions WHERE zoneId=4720;
INSERT INTO phase_definitions VALUES 
(4720, 0, 170, 0, 0, 0, 1, "Lost island from start ");

DELETE FROM phase_area WHERE areaId=4720;
INSERT INTO phase_area VALUES 
(4720, 0, 14474, 14303, 75, 11, 1, "arrival in Lost Island");

