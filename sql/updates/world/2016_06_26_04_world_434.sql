
ALTER TABLE `game_event`
MODIFY COLUMN `start_time`  timestamp NOT NULL DEFAULT '1970-01-01 01:00:01' COMMENT 'Absolute start date, the event will never start before' AFTER `eventEntry`,
MODIFY COLUMN `end_time`  timestamp NOT NULL DEFAULT '1970-01-01 01:00:01' COMMENT 'Absolute end date, the event will never start afler' AFTER `start_time`;

