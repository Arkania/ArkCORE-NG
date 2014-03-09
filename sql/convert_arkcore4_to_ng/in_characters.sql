/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;


ALTER TABLE `character_achievement_progress` 
	CHANGE `counter` `counter` int(10) unsigned   NOT NULL after `criteria` ;


CREATE TABLE `character_archaeology_digsites`(
	`guid` int(10) unsigned NOT NULL  DEFAULT 0 , 
	`siteId` smallint(5) unsigned NOT NULL  DEFAULT 0 , 
	`mapId` smallint(5) unsigned NOT NULL  DEFAULT 0 , 
	`areaId` smallint(5) unsigned NOT NULL  DEFAULT 0 , 
	`find1PosX` float NOT NULL  DEFAULT 0 , 
	`find2PosX` float NOT NULL  DEFAULT 0 , 
	`find3PosX` float NOT NULL  DEFAULT 0 , 
	`find1PosY` float NOT NULL  DEFAULT 0 , 
	`find2PosY` float NOT NULL  DEFAULT 0 , 
	`find3PosY` float NOT NULL  DEFAULT 0 , 
	PRIMARY KEY (`guid`,`siteId`) 
) ENGINE=MyISAM DEFAULT CHARSET='utf8' COLLATE='utf8_general_ci' COMMENT='Archaeology System';



CREATE TABLE `character_archaeology_projects`(
	`guid` int(10) unsigned NOT NULL  , 
	`branchId` int(10) NOT NULL  DEFAULT 0 , 
	`projectEntry` int(10) NOT NULL  DEFAULT 0 , 
	PRIMARY KEY (`guid`,`branchId`,`projectEntry`) 
) ENGINE=MyISAM DEFAULT CHARSET='utf8' COLLATE='utf8_general_ci';



CREATE TABLE `character_completed_projects`(
	`guid` int(10) unsigned NOT NULL  DEFAULT 0 , 
	`projectId` int(10) unsigned NOT NULL  , 
	`completionCount` int(10) unsigned NOT NULL  DEFAULT 0 , 
	`completionTime` int(10) unsigned NOT NULL  DEFAULT 0 , 
	PRIMARY KEY (`guid`,`projectId`) 
) ENGINE=InnoDB DEFAULT CHARSET='latin1' COLLATE='latin1_swedish_ci';



ALTER TABLE `character_cuf_profiles` 
	CHANGE `id` `id` tinyint(3) unsigned   NOT NULL COMMENT 'Profile Id (0-5)' after `guid` ;


ALTER TABLE `character_currency` 
	CHANGE `guid` `guid` int(10)   NOT NULL first , 
	CHANGE `currency` `id` int(5)   NOT NULL after `guid` , 
	CHANGE `total_count` `countTotal` int(7)   NOT NULL after `id` , 
	CHANGE `week_count` `countWeek` int(7)   NOT NULL after `countTotal`;


CREATE TABLE `character_guild_reputation`(
	`guid` int(10) unsigned NOT NULL  , 
	`guildid` int(10) unsigned NOT NULL  COMMENT 'Guild Identificator' , 
	`disband_time` int(10) unsigned NOT NULL  DEFAULT 0 , 
	`weekly_rep` mediumint(8) unsigned NOT NULL  DEFAULT 0 , 
	`total_rep` mediumint(8) unsigned NOT NULL  DEFAULT 0 , 
	UNIQUE KEY `guid_key`(`guid`) , 
	KEY `guildid_key`(`guildid`) 
) ENGINE=InnoDB DEFAULT CHARSET='utf8' COLLATE='utf8_general_ci' COMMENT='Characters Guild Reputation System';



ALTER TABLE `character_queststatus_rewarded` 
	CHANGE `active` `active` tinyint(3) unsigned   NOT NULL DEFAULT 1 after `quest` ;


ALTER TABLE `corpse` 
	CHANGE `phaseMask` `phaseMask` smallint(5) unsigned   NOT NULL DEFAULT 1 after `mapId` ;


ALTER TABLE `gm_tickets` 
	CHANGE `haveTicket` `haveTicket` tinyint(3) unsigned   NOT NULL after `viewed` ;


ALTER TABLE `guild` 
	CHANGE `info` `info` text  COLLATE utf8_general_ci NOT NULL after `BackgroundColor` ;


ALTER TABLE `guild_achievement_progress` 
	CHANGE `counter` `counter` int(10) unsigned   NOT NULL after `criteria` ;


CREATE TABLE `guild_challenges_completed`(
	`guildId` int(10) unsigned NOT NULL  DEFAULT 0 , 
	`challengeId` int(10) unsigned NULL  , 
	`dateCompleted` int(10) unsigned NULL  , 
	PRIMARY KEY (`guildId`) , 
	KEY `challengeId`(`challengeId`) 
) ENGINE=InnoDB DEFAULT CHARSET='utf8' COLLATE='utf8_general_ci';

/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;