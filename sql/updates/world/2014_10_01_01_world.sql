/*
Navicat MySQL Data Transfer

Date: 2014-10-01 04:47:22
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `spell_learn_spell`
-- ----------------------------
DROP TABLE IF EXISTS `spell_learn_spell`;
CREATE TABLE `spell_learn_spell` (
  `entry` int(10) unsigned NOT NULL DEFAULT '0',
  `SpellID` int(10) unsigned NOT NULL DEFAULT '0',
  `Active` tinyint(3) unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`entry`,`SpellID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Item System';

-- ----------------------------
-- Records of spell_learn_spell
-- ----------------------------
INSERT INTO `spell_learn_spell` VALUES ('53428', '53341', '1');
INSERT INTO `spell_learn_spell` VALUES ('53428', '53343', '1');
INSERT INTO `spell_learn_spell` VALUES ('17002', '24867', '0');
INSERT INTO `spell_learn_spell` VALUES ('24866', '24864', '0');
INSERT INTO `spell_learn_spell` VALUES ('33872', '47179', '0');
INSERT INTO `spell_learn_spell` VALUES ('33873', '47180', '0');
INSERT INTO `spell_learn_spell` VALUES ('33943', '34090', '1');
INSERT INTO `spell_learn_spell` VALUES ('58984', '21009', '1');
INSERT INTO `spell_learn_spell` VALUES ('2098', '79327', '0');
INSERT INTO `spell_learn_spell` VALUES ('86467', '86473', '1');
INSERT INTO `spell_learn_spell` VALUES ('87491', '86470', '1');
INSERT INTO `spell_learn_spell` VALUES ('87492', '86471', '1');
INSERT INTO `spell_learn_spell` VALUES ('87493', '86472', '1');
INSERT INTO `spell_learn_spell` VALUES ('87494', '86474', '1');
INSERT INTO `spell_learn_spell` VALUES ('87495', '86475', '1');
INSERT INTO `spell_learn_spell` VALUES ('87496', '86476', '1');
INSERT INTO `spell_learn_spell` VALUES ('87497', '86477', '1');
INSERT INTO `spell_learn_spell` VALUES ('87498', '86478', '1');
INSERT INTO `spell_learn_spell` VALUES ('87500', '86479', '1');
