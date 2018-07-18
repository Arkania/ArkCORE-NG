
-- npc 16788 Festival Flamekeeper

DELETE FROM creature_questender WHERE id=16788 AND quest in (9322, 9323, 9386, 9388, 9389);
INSERT INTO creature_questender 
(id, quest)
VALUES
(16788, 9322),
(16788, 9323),
(16788, 9386),
(16788, 9388),
(16788, 9389);
