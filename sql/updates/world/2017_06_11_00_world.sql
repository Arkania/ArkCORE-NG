

UPDATE creature SET phaseId=252, spawntimesecs=120 WHERE guid=243276;

UPDATE creature_template SET minlevel=82, maxlevel=83 WHERE entry=44818;

DELETE FROM creature WHERE id=45297 AND guid=42819;
INSERT INTO creature VALUES 
(42819, 45297, 646, 0, 0, 1, 253, 0, 0, 0, 1088.271, 434.7274, -45.72447, 1.972222, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=45297 AND guid=42831;
INSERT INTO creature VALUES 
(42831, 45297, 646, 0, 0, 1, 254, 0, 0, 0, 1088.271, 434.7274, -45.72447, 1.972222, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=44818 AND guid=243251;
INSERT INTO creature VALUES 
(243251, 44818, 646, 0, 0, 1, 169, 0, 0, 0, 1095.77, 436.955, -45.93797, 3.403392, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=44818 AND guid=42864;
INSERT INTO creature VALUES 
(42864, 44818, 646, 0, 0, 1, 253, 0, 0, 0, 1095.77, 436.955, -45.93797, 3.403392, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=44818 AND guid=42872;
INSERT INTO creature VALUES 
(42872, 44818, 646, 0, 0, 1, 254, 0, 0, 0, 1095.77, 436.955, -45.93797, 3.403392, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0);

delete from spell_area where spell in (84117, 84955) and area=5042;









