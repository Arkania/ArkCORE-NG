
-- Thousand Needles


delete from game_event_creature where eventEntry=1 and guid=134629;
insert into game_event_creature values 
(1, 134629);

UPDATE quest_template SET Method=2, Type=82, Flags=65536, SpecialFlags=2 WHERE Id=28927;

UPDATE quest_template SET Method=2, Type=82, Flags=4, SpecialFlags=2 WHERE Id=28914;

delete from gameobject_queststarter where id=207986 and quest= 28914;


	
	