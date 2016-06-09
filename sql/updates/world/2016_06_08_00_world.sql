
-- fix issue #143

-- totems are spawned by script..
delete from creature where id=24320;

update creature set spawntimesecs=7200 where map=547 and spawntimesecs<>7200;

delete from game_event_creature where eventEntry=1 and guid=192154;
insert into game_event_creature values 
(1, 192154);

-- fix console error
DELETE FROM creature_addon WHERE guid=233848;
DELETE FROM creature_addon WHERE guid=233881;

