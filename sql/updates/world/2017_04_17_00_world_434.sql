

-- ----------------------------
-- Table structure for gameobject_addon
-- ----------------------------

DROP TABLE IF EXISTS `gameobject_addon`;
CREATE TABLE `gameobject_addon` (
  `guid` int(10) unsigned NOT NULL DEFAULT '0',
  `invisibilityType` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `invisibilityValue` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`guid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;



