
-- ----------------------------
-- Table structure for spell_phase
-- ----------------------------
DROP TABLE IF EXISTS `spell_phase`;
CREATE TABLE `spell_phase` (
  `spell_id` mediumint(7) unsigned NOT NULL DEFAULT '0',
  `id` smallint(5) NOT NULL,
  `phaseId` smallint(5) NOT NULL,
  `phaseGroup` smallint(5) NOT NULL,
  `terrainswapmap` smallint(5) unsigned NOT NULL DEFAULT '0',
  `worldmapareaswap` smallint(5) unsigned NOT NULL DEFAULT '0',
  `comment` text NOT NULL,
  PRIMARY KEY (`spell_id`,`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of spell_phase
-- ----------------------------

INSERT INTO `spell_phase` VALUES ('68750', '0', '180', '0', '661', '681', 'lost island quest phase 4');
