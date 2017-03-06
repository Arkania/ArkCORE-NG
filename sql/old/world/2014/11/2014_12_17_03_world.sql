
update gameobject_template set data0=57,data1=3719,faction=94 where entry=3719;

DELETE FROM `gameobject_loot_template` WHERE (`entry`=3719) AND (`item`=414);
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(3719, 414, 100, 1, 0, 1, 1);