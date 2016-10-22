
DELETE FROM phase_area WHERE areaId=4737 AND entry=8;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4737, 8, 14120, 14125, 64, 1, 1, "Kezan from reward 14120 to not taken 14125");

DELETE FROM phase_area WHERE areaId=4737 AND entry=9;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4737, 9, 14125, 14126, 74, 11, 1, "Kezan from incomplete 14125 to -reward 14126");

DELETE FROM creature WHERE guid IN (16465, 248944);
INSERT INTO creature VALUES 
( 16465, 34692, 648, 0, 0, 1, "384 ", 0, 1, -8414.11, 1329.39, 102.646, 2.12930, 300, 0, 0, 111, 259, 0, 0, 0, 0), 
(248944, 34692, 648, 0, 0, 1, "379 380 381 382 383 ", 0, 1, -8425.34, 1347.73, 105.055, 4.61407, 300, 0, 0, 111, 259, 0, 0, 0, 0);


