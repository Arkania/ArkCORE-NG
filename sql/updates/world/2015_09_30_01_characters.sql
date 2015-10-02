/*
Navicat MySQL Data Transfer
Date: 2015-10-02 10:16:50
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for character_archaeology_completed
-- ----------------------------
DROP TABLE IF EXISTS `character_archaeology_completed`;
CREATE TABLE `character_archaeology_completed` (
  `guid` int(10) unsigned NOT NULL DEFAULT '0',
  `projectId` smallint(5) unsigned NOT NULL DEFAULT '0',
  `counter_completed` int(10) unsigned NOT NULL DEFAULT '0',
  `time_first` int(10) unsigned NOT NULL DEFAULT '0',
  `time_last` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`guid`,`projectId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='here are stored all completed project''s of all players by giving GUID\r\neach possible project is stored only one time by key guid, projectId with counter=1\r\nlater stored project id''s are increment the counter, \r\nonly the time of last creating is stored under the projectId\r\n';

-- ----------------------------
-- Table structure for character_archaeology_current
-- ----------------------------
DROP TABLE IF EXISTS `character_archaeology_current`;
CREATE TABLE `character_archaeology_current` (
  `guid` int(11) unsigned NOT NULL,
  `branchId` smallint(5) unsigned NOT NULL,
  `projectId` smallint(5) unsigned NOT NULL,
  PRIMARY KEY (`guid`,`branchId`,`projectId`),
  UNIQUE KEY `guid_branch` (`guid`,`branchId`),
  UNIQUE KEY `guid_project` (`guid`,`projectId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='each player can have 10 projects. each for every branch/race type\r\nthe struct for every branch holds some values more, as stored to DB\r\nOn DB are only stored values, that not can rebuild via other tables. ';

-- ----------------------------
-- Table structure for character_archaeology_digsite
-- ----------------------------
DROP TABLE IF EXISTS `character_archaeology_digsite`;
CREATE TABLE `character_archaeology_digsite` (
  `slot` smallint(5) unsigned NOT NULL,
  `guid` int(11) unsigned NOT NULL,
  `entry` smallint(5) unsigned NOT NULL,
  `counter_digsite` smallint(5) unsigned NOT NULL DEFAULT '0',
  `time_digged` int(11) unsigned NOT NULL DEFAULT '0',
  `point1` smallint(5) unsigned NOT NULL DEFAULT '0',
  `count1` smallint(5) unsigned NOT NULL DEFAULT '0',
  `point2` smallint(5) unsigned NOT NULL DEFAULT '0',
  `count2` smallint(5) unsigned NOT NULL DEFAULT '0',
  `point3` smallint(5) unsigned NOT NULL DEFAULT '0',
  `count3` smallint(5) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`slot`,`guid`,`entry`),
  UNIQUE KEY `guid_entry` (`guid`,`entry`),
  UNIQUE KEY `guid_slot` (`slot`,`guid`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='The player can have 8,12 or 16 digsites, depending on player level and archaeology skill.\r\neach entry in table, stand for one digsite, that have 3 digsite points. \r\non every point i can collect minimum one and up to 4  archaeology fragment packets.\r\neach excavation give a packet of 5-9 fragments.\r\neach digsite have 6 successfully excavations.\r\n\r\n';


