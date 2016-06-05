
-- fix issue #144

delete from game_event_creature where eventEntry=1 and guid=192132;
insert into game_event_creature values 
(1, 192132);