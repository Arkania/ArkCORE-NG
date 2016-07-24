
ALTER TABLE `corpse`
MODIFY COLUMN `phaseMask`  bit(20) NOT NULL DEFAULT 1 AFTER `mapId`;

