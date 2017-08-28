
ALTER TABLE `mail`
MODIFY COLUMN `expire_time`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 AFTER `has_items`,
MODIFY COLUMN `deliver_time`  bigint(20) UNSIGNED NOT NULL DEFAULT 0 AFTER `expire_time`;



