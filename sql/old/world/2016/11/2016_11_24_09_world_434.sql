
ALTER TABLE `creature`
CHANGE COLUMN `phaseIds` `phaseId`  smallint(5) NOT NULL AFTER `spawnMask`;

