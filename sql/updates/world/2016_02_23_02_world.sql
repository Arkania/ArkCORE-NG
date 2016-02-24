
-- fix some console errors
DELETE FROM creature_addon WHERE guid=93071;

DELETE FROM creature_addon WHERE guid=89301;

UPDATE creature_template SET npcflag=npcflag | 2 WHERE entry=35177;

