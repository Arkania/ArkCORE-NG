DELETE FROM `arkcore_string` WHERE `entry` IN (9980, 9981, 9982, 9983, 9984, 9985, 9986, 9987, 9988, 9989, 9990, 9991, 9992, 9993, 9994, 9995, 9996, 9997, 9998, 9999);
INSERT INTO `arkcore_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES
(9980, 'Player name: %s, State: %s, Dungeons: %u (%s), Roles: %s, Comment: %s', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(9981, 'LfgGroup?: %u, State: %s, Dungeon: %u', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(9982, 'Not in group', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(9983, 'Queues cleared', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(9984, 'Lfg options: %u', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(9985, 'Lfg options changed', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(9986, 'None', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(9987, 'Role check', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(9988, 'Queued', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(9989, 'Proposal', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(9990, 'Vote kick', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(9991, 'In dungeon', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(9992, 'Finished dungeon', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(9993, 'Raid browser', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(9994, 'Tank', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(9995, 'Healer', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(9996, 'Dps', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(9997, 'Leader', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(9998, 'None', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(9999, 'Error', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

-- not implement
DELETE FROM `command` WHERE `name` LIKE 'lfg%';
INSERT INTO `command` (`name`, `security`, `help`) VALUES
('lfg player', 2, 'Syntax: .lfg player\n Shows information about player (state, roles, comment, dungeons selected).'),
('lfg group', 2, 'Syntax: .lfg group\n Shows information about all players in the group  (state, roles, comment, dungeons selected).'),
('lfg queue', 2, 'Syntax: .lfg queue\n Shows info about current lfg queues.'),
('lfg clean', 3, 'Syntax: .flg clean\n Cleans current queue, only for debugging purposes.'),
('lfg options', 3, 'Syntax: .lfg options [new value]\n Shows current lfg options. New value is set if extra param is present.');
