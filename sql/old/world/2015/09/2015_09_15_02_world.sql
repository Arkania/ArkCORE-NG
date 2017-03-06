
ALTER TABLE `phase_definitions`
MODIFY COLUMN `flags`  tinyint(3) UNSIGNED NOT NULL DEFAULT 0 AFTER `terrainswapmap`,
ADD COLUMN `worldMapAreaSwap`  smallint(5) UNSIGNED NOT NULL DEFAULT 0 AFTER `terrainswapmap`;


