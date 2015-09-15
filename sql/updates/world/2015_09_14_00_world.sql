
ALTER TABLE `phase_definitions`
MODIFY COLUMN `entry`  smallint(5) UNSIGNED NOT NULL AFTER `zoneId`;
