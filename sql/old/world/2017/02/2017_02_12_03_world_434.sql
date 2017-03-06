
ALTER TABLE `waypoint_data`
CHANGE COLUMN `move_flag` `move_type`  tinyint(4) NOT NULL DEFAULT 0 AFTER `delay`;

