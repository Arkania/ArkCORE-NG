
ALTER TABLE `creature`
ADD COLUMN `phaseGroup`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 AFTER `phaseIds`;


