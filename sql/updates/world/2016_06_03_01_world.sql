
-- fix issue 151, add missing loot

UPDATE creature_loot_template SET Chance=100 WHERE entry=18472 AND item=27633;

