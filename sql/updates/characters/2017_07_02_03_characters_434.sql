
DROP TABLE IF EXISTS `questgiver_quest`;
CREATE TABLE `questgiver_quest` (
  `playerGuid` int(10) unsigned NOT NULL,
  `questGiverGuid` bigint(20) unsigned NOT NULL,
  `questId` int(8) unsigned NOT NULL DEFAULT '0',
  `timeChange` int(10) unsigned NOT NULL DEFAULT '0',
  `isRewarded` tinyint(3) NOT NULL DEFAULT '0',
  PRIMARY KEY (`playerGuid`,`questId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;



