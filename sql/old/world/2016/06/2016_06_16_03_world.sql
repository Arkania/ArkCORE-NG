
-- add npc to event darkmoon faire
DELETE FROM `game_event_creature` WHERE `guid` IN (53431, 117248, 117249, 159533, 159534, 199130, 12791, 12793, 12794, 117246, 158189, 158190, 196245);
INSERT INTO `game_event_creature` (`eventEntry`, `guid`) VALUES
(3, 53431),
(3, 117248),
(3, 117249),
(3, 159533),
(3, 159534),
(3, 199130),
(3, 12791),
(3, 12793),
(3, 12794),
(3, 117246),
(3, 158189),
(3, 158190),
(3, 196245);

-- add gameobject to event darkmoon faire
DELETE FROM `game_event_gameobject` WHERE `guid` IN (10022, 10023, 182918);
INSERT INTO `game_event_gameobject` (`eventEntry`, `guid`) VALUES
(3, 10022), 
(3, 10023), 
(3, 182918);

delete from gameobject where id=209116 and guid in (10022, 10023);
insert into gameobject values 
(10022, 209116, 0, 1, 1, -8378.33, 602.898, 97.7777, 2.30383, 0, 0, 0, 1, 120, 255, 1),
(10023, 209116, 0, 1, 1, -8343.64, 654.382, 97.3578, 3.85718, 0, 0, 0, 1, 120, 255, 1);

delete from game_event_gameobject where eventEntry=3 and guid in (182908, 208123, 208254, 208257, 208568, 208915, 208972, 208973, 208976, 208977, 209061, 209063, 209453);
insert into game_event_gameobject values 
(3, 182908),
(3, 208123),
(3, 208254),
(3, 208257),
(3, 208568),
(3, 208915),
(3, 208972),
(3, 208973),
(3, 208976),
(3, 208977),
(3, 209061),
(3, 209063),
(3, 209453);

delete from game_event_gameobject where eventEntry=3 and guid in (182907, 208253, 208916, 208974, 208975, 209062, 209123, 209124, 209454);
insert into game_event_gameobject values 
(3, 182907),
(3, 208253),
(3, 208916),
(3, 208974),
(3, 208975),
(3, 209062),
(3, 209123),
(3, 209124),
(3, 209454);

