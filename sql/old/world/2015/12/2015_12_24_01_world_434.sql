
ALTER TABLE `creature_template`
	CHANGE COLUMN `modelid1` `modelid1` INT NOT NULL DEFAULT '0' AFTER `KillCredit2`,
	CHANGE COLUMN `modelid2` `modelid2` INT NOT NULL DEFAULT '0' AFTER `modelid1`,
	CHANGE COLUMN `modelid3` `modelid3` INT NOT NULL DEFAULT '0' AFTER `modelid2`,
	CHANGE COLUMN `modelid4` `modelid4` INT NOT NULL DEFAULT '0' AFTER `modelid3`;

