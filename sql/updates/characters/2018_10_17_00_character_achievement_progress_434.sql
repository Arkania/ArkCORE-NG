
ALTER TABLE `character_achievement_progress`
MODIFY COLUMN `counter`  bigint(20) UNSIGNED NOT NULL AFTER `criteria`;

