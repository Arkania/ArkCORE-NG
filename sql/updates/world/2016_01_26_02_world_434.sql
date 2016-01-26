
ALTER TABLE `guild_xp_for_level`
MODIFY COLUMN `lvl`  tinyint(3) UNSIGNED NULL DEFAULT 0 FIRST ,
MODIFY COLUMN `xp_for_next_level`  bigint(20) UNSIGNED NULL DEFAULT 0 AFTER `lvl`;

