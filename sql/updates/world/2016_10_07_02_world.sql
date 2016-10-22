

UPDATE creature SET phaseIds="170 171 172", spawndist=0, MovementType=0 WHERE guid=249464;

UPDATE creature SET phaseIds="170 171 172", spawndist=0, MovementType=0 WHERE guid=249466;

UPDATE creature SET phaseIds="170 171 172", spawndist=0, MovementType=0 WHERE guid=249463;

UPDATE creature SET phaseIds="170 171 172", spawndist=0, MovementType=0 WHERE guid=249465;

UPDATE creature SET phaseIds="171", spawndist=0, MovementType=0 WHERE id=36344;

UPDATE creature SET phaseIds="170 171 179", spawndist=0, MovementType=0 WHERE id=35837;

UPDATE creature SET phaseIds="170", spawndist=0, MovementType=0 WHERE id=35812;

UPDATE gameobject SET phaseIds="170 171 172 179" WHERE id=195622;

UPDATE gameobject SET phaseIds="170 171 172" WHERE id=205351;

UPDATE gameobject SET phaseIds="172" WHERE id=205471;

UPDATE creature SET phaseIds="170 171 172" WHERE id=35810;

delete from creature where id=39329;

delete from creature where id=46485;

UPDATE creature SET phaseIds="170 171 172 179" WHERE guid=246177;

DELETE FROM phase_area WHERE areaId=4720 AND entry=0;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4720, 0, 14474, 14303, 75, 11, 1, "arrival in Lost Island");

DELETE FROM phase_definitions WHERE zoneID=4720 AND entry=1;
INSERT INTO phase_definitions VALUES 
(4720, 1, 171, 0, 0, 1, "Comment for phase 171");

DELETE FROM phase_definitions WHERE zoneID=4720 AND entry=2;
INSERT INTO phase_definitions VALUES 
(4720, 2, 172, 0, 0, 1, "Comment for phase 172");

DELETE FROM phase_definitions WHERE zoneID=4720 AND entry=3;
INSERT INTO phase_definitions VALUES 
(4720, 3, 179, 0, 0, 1, "Comment for phase 179");

DELETE FROM phase_definitions WHERE zoneID=4720 AND entry=4;
INSERT INTO phase_definitions VALUES 
(4720, 4, 180, 661, 681, 1, "Comment for phase 180");



