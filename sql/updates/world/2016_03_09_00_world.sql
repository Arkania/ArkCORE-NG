

-- fix issue #104
delete from game_graveyard_zone where ghost_zone=33 and id in (109, 389, 1458, 1459, 1460);
insert into game_graveyard_zone values
(109, 33, 0),
(389, 33, 0),
(1458, 33, 0),
(1459, 33, 0),
(1460, 33, 0);

