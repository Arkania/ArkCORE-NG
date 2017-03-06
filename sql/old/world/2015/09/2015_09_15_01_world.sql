
-- ----------------------------
-- Table structure for phase_area
-- ----------------------------
DROP TABLE IF EXISTS `phase_area`;
CREATE TABLE `phase_area` (
  `areaId` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `entry` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `quest_start` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `quest_end` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `quest_start_status` int(11) NOT NULL DEFAULT '64',
  `quest_end_status` int(11) NOT NULL DEFAULT '11',
  `flags` int(11) NOT NULL DEFAULT '0',
  `comment` text DEFAULT NULL,
  PRIMARY KEY (`areaId`,`entry`,`quest_start`,`quest_end`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

insert into phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) values
(4755, 0, 14091, 14091, 11, 64, 0, "Gilneas phase 1"), 
(4755, 1, 14091, 14159, 74, 64, 0, "Gilneas phase 2"), 
(4755, 2, 14099, 14204, 64, 72, 0, "Gilneas phase 4"), 
(4755, 3, 14204, 12345, 74, 72, 0, "Gilneas phase 8");











