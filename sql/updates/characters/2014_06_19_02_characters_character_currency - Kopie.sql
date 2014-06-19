
ALTER TABLE `character_currency` 
	CHANGE `id` `currency` SMALLINT(5) UNSIGNED NOT NULL,
	CHANGE `countTotal` `total_count` INT(10) UNSIGNED NOT NULL,
	CHANGE `countWeek` `week_count` INT(10) UNSIGNED NOT NULL;
