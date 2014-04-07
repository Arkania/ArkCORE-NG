ALTER TABLE `spell_area` ADD COLUMN `quest_start_active` tinyint(1) NOT NULL DEFAULT 0 AFTER `quest_start`;
ALTER TABLE `spell_area` DROP COLUMN `quest_start_status`,
                       DROP COLUMN `quest_end_status`;