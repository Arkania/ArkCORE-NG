/*
Navicat MySQL Data Transfer
Date: 2015-09-25 20:25:21
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for spell_phase
-- ----------------------------
DROP TABLE IF EXISTS `spell_phase`;
CREATE TABLE `spell_phase` (
  `spell_id` mediumint(7) unsigned NOT NULL DEFAULT '0',
  `phasemask` bigint(20) unsigned NOT NULL DEFAULT '1',
  `terrainswapmap` smallint(5) unsigned NOT NULL DEFAULT '0',
  `worldmapareaswap` smallint(5) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`spell_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of spell_phase
-- ----------------------------
INSERT INTO `spell_phase` VALUES ('59073', '2', '638', '683');

DROP TABLE IF EXISTS `phase_info`;
