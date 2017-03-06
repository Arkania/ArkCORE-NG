UPDATE creature SET modelid=0 WHERE guid=286187;
UPDATE creature_addon SET auras="" WHERE guid=286187;

UPDATE creature_template_addon SET auras="" WHERE entry=38855;

DELETE FROM `spell_area` WHERE `spell` = 75207;
