
-- loot for item 41426
DELETE FROM `item_loot_template` WHERE (`entry`=41426);
INSERT INTO `item_loot_template` VALUES ('41426', '41427', '0', '99', '0', '1', '0', '5', '5', null);
INSERT INTO `item_loot_template` VALUES ('41426', '40211', '0', '99', '0', '1', '0', '5', '5', null);
INSERT INTO `item_loot_template` VALUES ('41426', '33447', '0', '98', '0', '1', '0', '5', '5', null);
INSERT INTO `item_loot_template` VALUES ('41426', '33448', '0', '98', '0', '1', '0', '5', '5', null);

-- loot for item 63349
DELETE FROM `item_loot_template` WHERE (`entry`=63349 AND `item` IN (63300,67348,62323,68047,67319,67335));
INSERT INTO `item_loot_template` VALUES ('63349', '63300', '0', '17', '0', '1', '0', '1', '1', null);
INSERT INTO `item_loot_template` VALUES ('63349', '67348', '0', '1.5', '0', '1', '0', '1', '1', null);
INSERT INTO `item_loot_template` VALUES ('63349', '62323', '0', '1.5', '0', '1', '0', '1', '1', null);
INSERT INTO `item_loot_template` VALUES ('63349', '68047', '0', '1.5', '0', '1', '0', '1', '1', null);
INSERT INTO `item_loot_template` VALUES ('63349', '67319', '0', '1.4', '0', '1', '0', '1', '1', null);
INSERT INTO `item_loot_template` VALUES ('63349', '67335', '0', '1.4', '0', '1', '0', '1', '1', null);

-- GO 202616 Shouldn't be selectable 
UPDATE `gameobject_template` SET `flags` = 4 WHERE `entry` = 202616;

-- Gilneas
-- cannon level must be 5
UPDATE `creature_template` SET `minlevel` = 5, `maxlevel` = 5 WHERE `entry` = 35317;

-- too much health npc 36397,36399
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 36397;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 36399;

-- IcecrownCitadel instance
-- npc level must be 80
UPDATE `creature_template` SET `minlevel` = 80, `maxlevel` = 80 WHERE `entry` = 38608;
UPDATE `creature_template` SET `minlevel` = 80, `maxlevel` = 80 WHERE `entry` = 38606;

-- DragonSoul instance
-- npc level must be 87
UPDATE `creature_template` SET `minlevel` = 87, `maxlevel` = 87 WHERE `entry` = 57684;
UPDATE `creature_template` SET `exp` = 3 WHERE `entry` = 57684;

-- GrimBatol instance
-- quest objective fix 
UPDATE `quest_template` SET `RequiredNpcOrGo2` = 39450 WHERE `Id` = 28852;

-- loot for item 66943
DELETE FROM `item_loot_template` WHERE (`entry`=66943);
INSERT INTO `item_loot_template` VALUES ('66943', '66948', '0', '16', '0', '1', '0', '1', '3', null);
INSERT INTO `item_loot_template` VALUES ('66943', '66945', '0', '16', '0', '1', '0', '1', '1', null);
INSERT INTO `item_loot_template` VALUES ('66943', '66950', '0', '16', '0', '1', '0', '1', '1', null);
INSERT INTO `item_loot_template` VALUES ('66943', '66947', '0', '15', '0', '1', '0', '1', '3', null);
INSERT INTO `item_loot_template` VALUES ('66943', '66946', '0', '15', '0', '1', '0', '1', '1', null);
INSERT INTO `item_loot_template` VALUES ('66943', '66949', '0', '15', '0', '1', '0', '1', '1', null);
INSERT INTO `item_loot_template` VALUES ('66943', '66944', '0', '8', '0', '1', '0', '1', '1', null);


