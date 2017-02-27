
ALTER TABLE `creature`
MODIFY COLUMN `equipment_id`  tinyint(3) NOT NULL DEFAULT 0 AFTER `modelid`;

