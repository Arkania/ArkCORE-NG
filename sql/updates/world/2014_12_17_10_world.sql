
DELETE FROM `gameobject_loot_template` WHERE (`entry`=3719) AND (`item` in (159,787,2070,4536,4540,4604));
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(3719, 159, 100, 1, 0, 1, 1),
(3719, 787, 100, 1, 0, 2, 4),
(3719, 2070, 100, 1, 0, 1, 4),
(3719, 4536, 100, 1, 0, 1, 4),
(3719, 4540, 100, 1, 0, 2, 4),
(3719, 4604, 100, 1, 0, 2, 4);
