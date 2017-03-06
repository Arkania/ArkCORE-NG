
-- ----------------------------
-- Table structure for `guild_member`
-- ----------------------------
DROP TABLE IF EXISTS `guild_member`;
CREATE TABLE `guild_member` (
  `guildid` int(10) unsigned NOT NULL COMMENT 'Guild Identificator',
  `guid` int(10) unsigned NOT NULL,
  `rank` tinyint(3) unsigned NOT NULL,
  `pnote` varchar(31) NOT NULL DEFAULT '',
  `offnote` varchar(31) NOT NULL DEFAULT '',
  `activity` bigint(20) NOT NULL,
  `profession1_skillID` int(10) NOT NULL DEFAULT '0',
  `weekReputation` int(10) NOT NULL DEFAULT '0',
  `profession2_rank` int(10) NOT NULL DEFAULT '0',
  `profession2_skillID` int(10) NOT NULL DEFAULT '0',
  `profession1_rank` int(10) NOT NULL DEFAULT '0',
  `weekActivity` int(10) NOT NULL DEFAULT '0',
  `profession1_level` int(10) NOT NULL DEFAULT '0',
  `profession2_level` int(10) NOT NULL DEFAULT '0',
  UNIQUE KEY `guid_key` (`guid`) USING BTREE,
  KEY `guildid_key` (`guildid`) USING BTREE,
  KEY `guildid_rank_key` (`guildid`,`rank`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Guild System';

-- ----------------------------
-- Table structure for `guild_old_member`
-- ----------------------------
DROP TABLE IF EXISTS `guild_old_member`;
CREATE TABLE `guild_old_member` (
  `guid` int(10) NOT NULL,
  `guildId` int(10) NOT NULL,
  `weekReputation` int(10) NOT NULL,
  `leaveDate` int(10) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;


-- ----------------------------
-- Table structure for `guild`
-- ----------------------------
DROP TABLE IF EXISTS `guild`;
CREATE TABLE `guild` (
  `guildid` int(10) unsigned NOT NULL DEFAULT '0',
  `name` varchar(24) NOT NULL DEFAULT '',
  `leaderguid` int(10) unsigned NOT NULL DEFAULT '0',
  `EmblemStyle` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `EmblemColor` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `BorderStyle` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `BorderColor` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `BackgroundColor` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `info` text NOT NULL,
  `motd` varchar(128) NOT NULL DEFAULT '',
  `createdate` int(10) unsigned NOT NULL DEFAULT '0',
  `BankMoney` bigint(20) unsigned NOT NULL DEFAULT '0',
  `level` int(10) unsigned DEFAULT '1',
  `todayExperience` bigint(20) unsigned DEFAULT '0',
  `RaidChallenge` int(10) NOT NULL DEFAULT '0',
  `ChallengeCount` int(32) unsigned NOT NULL DEFAULT '0',
  `RatedBGChallenge` int(10) NOT NULL DEFAULT '0',
  `DungeonChallenge` int(10) NOT NULL DEFAULT '0',
  `experience` bigint(20) unsigned DEFAULT '0',
  PRIMARY KEY (`guildid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Guild System';










