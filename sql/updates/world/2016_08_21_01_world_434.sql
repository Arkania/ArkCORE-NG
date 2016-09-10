
ALTER TABLE `gameobject`
ADD COLUMN `zoneId`  smallint(5) UNSIGNED NOT NULL AFTER `map`,
ADD COLUMN `areaId`  smallint(5) UNSIGNED NOT NULL AFTER `zoneId`,
ADD COLUMN `phaseId`  smallint(5) UNSIGNED NOT NULL AFTER `phaseMask`,
ADD COLUMN `phaseGroups`  text NOT NULL AFTER `phaseId`;

