
-- fix issue #125
update game_event set start_time = "2016-01-01 02:01:00", occurence=43200, length=10078 where eventEntry in (3, 4, 5, 75);

update game_event set holiday=479 where eventEntry=75;

delete from gameobject where id=179965 and guid=50110;
insert into gameobject values 
(50110, 179965, 0, 1, 1, -8838.53, 642.083, 96.588, 4.17439, 0, 0, 0.869604, -0.49375, 300, 0, 1);

delete from game_event_gameobject where eventEntry=75 and guid=50110;
insert into game_event_gameobject values
(75, 50110);


