
ALTER TABLE `corpse`
CHANGE COLUMN `phaseMask` `phaseIds`  text NOT NULL AFTER `mapId`;

