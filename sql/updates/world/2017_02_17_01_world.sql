

DELETE FROM command where name='gobject set phasegroup' AND permission=397;
INSERT INTO `command` (`name`, `permission`, `help`) VALUES
('gobject set phasegroup', 397, 'Syntax: .gobject set phasegroup #guid #phasegroup\r\n\r\nGameobject with DB guid #guid phasegroup changed to #phasegroupwith related world vision update for players. Gameobject state saved to DB and persistent.');
