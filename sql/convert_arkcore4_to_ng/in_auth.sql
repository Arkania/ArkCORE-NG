/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;

ALTER TABLE `account` 
	CHANGE `email` `email` varchar(254)  COLLATE utf8_general_ci NOT NULL DEFAULT '' after `s` , 
	CHANGE `joindate` `joindate` timestamp   NOT NULL DEFAULT CURRENT_TIMESTAMP after `email` , 
	CHANGE `last_ip` `last_ip` varchar(15)  COLLATE utf8_general_ci NOT NULL DEFAULT '127.0.0.1' after `joindate` , 
	CHANGE `failed_logins` `failed_logins` int(10) unsigned   NOT NULL DEFAULT 0 after `last_ip` , 
	CHANGE `locked` `locked` tinyint(3) unsigned   NOT NULL DEFAULT 0 after `failed_logins` , 
	CHANGE `last_login` `last_login` timestamp   NOT NULL DEFAULT '0000-00-00 00:00:00' after `locked` , 
	CHANGE `online` `online` tinyint(3) unsigned   NOT NULL DEFAULT 0 after `last_login` , 
	CHANGE `expansion` `expansion` tinyint(3) unsigned   NOT NULL DEFAULT 3 after `online` , 
	CHANGE `mutetime` `mutetime` bigint(20)   NOT NULL DEFAULT 0 after `expansion` , 
	CHANGE `locale` `locale` tinyint(3) unsigned   NOT NULL DEFAULT 0 after `mutetime` , 
	CHANGE `os` `os` varchar(3)  COLLATE utf8_general_ci NOT NULL DEFAULT '' after `locale` , 
	CHANGE `recruiter` `recruiter` int(10) unsigned   NOT NULL DEFAULT 0 after `os` , 
	ADD COLUMN `on_trial` tinyint(1) unsigned   NOT NULL DEFAULT 0 after `recruiter` , 
	ADD COLUMN `trial_end` int(10) unsigned   NOT NULL DEFAULT 1 after `on_trial` , 
	DROP COLUMN `reg_mail` , 
	DROP COLUMN `lock_country` , 
	DROP COLUMN `mutereason` , 
	DROP COLUMN `muteby` , 
	DROP COLUMN `token_key` ;


ALTER TABLE `logs` 
	CHANGE `type` `type` tinyint(3) unsigned   NOT NULL after `realm` ;


ALTER TABLE `realmlist` 
	CHANGE `port` `port` smallint(5) unsigned   NOT NULL DEFAULT 8085 after `address` , 
	CHANGE `icon` `icon` tinyint(3) unsigned   NOT NULL DEFAULT 0 after `port` , 
	CHANGE `flag` `flag` tinyint(3) unsigned   NOT NULL DEFAULT 2 after `icon` , 
	CHANGE `timezone` `timezone` tinyint(3) unsigned   NOT NULL DEFAULT 0 after `flag` , 
	CHANGE `allowedSecurityLevel` `allowedSecurityLevel` tinyint(3) unsigned   NOT NULL DEFAULT 0 after `timezone` , 
	CHANGE `population` `population` float unsigned   NOT NULL DEFAULT '0' after `allowedSecurityLevel` , 
	CHANGE `gamebuild` `gamebuild` int(10) unsigned   NOT NULL DEFAULT 15595 after `population` , 
	DROP COLUMN `localSubnetMask` , 
	DROP COLUMN `localAddress` ;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;