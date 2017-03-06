SET @id := 794;

DELETE FROM `rbac_permissions` WHERE `id` BETWEEN @id AND @id+9;
INSERT INTO `rbac_permissions` (`id`,`name`) VALUES
(@id+0,'npcbot'),
(@id+1,'npcbot add'),
(@id+2,'npcbot remove'),
(@id+3,'npcbot reset'),
(@id+4,'npcbot command'),
(@id+5,'npcbot distance'),
(@id+6,'npcbot info'),
(@id+7,'npcbot helper'),
(@id+8,'npcbot revive'),
(@id+9,'maintank (mt)');

DELETE FROM `rbac_linked_permissions` WHERE `linkedId` BETWEEN @id AND @id+9;
INSERT INTO `rbac_linked_permissions` (`id`, `linkedId`) VALUES
(192, @id+0),
(192, @id+1),
(192, @id+2),
(192, @id+3),
(192, @id+4),
(192, @id+5),
(192, @id+6),
(192, @id+7),
(192, @id+8),
(192, @id+9);