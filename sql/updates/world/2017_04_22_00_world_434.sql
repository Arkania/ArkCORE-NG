
ALTER TABLE `transports`
ADD COLUMN `phaseId`  smallint(5) NOT NULL AFTER `name`,
ADD COLUMN `phaseGroup`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 AFTER `phaseId`;


