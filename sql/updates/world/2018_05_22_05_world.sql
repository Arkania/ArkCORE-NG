
-- move candy bucket to game events
delete from game_event_gameobject where eventEntry=12 and guid=404130;

insert into game_event_gameobject values
(12, 404130);

UPDATE quest_template SET PrevQuestId=977, NextQuestId=7383, ExclusiveGroup=-918, NextQuestIdChain=7383 WHERE id=918;

UPDATE quest_template SET PrevQuestId=997, NextQuestId=7383, ExclusiveGroup=-918, NextQuestIdChain=7383 WHERE id=919;

UPDATE quest_template SET PrevQuestId=918, NextQuestId=0 WHERE id=922;

DELETE FROM creature WHERE guid=15455055;

UPDATE quest_template SET PrevQuestId=489 WHERE id=932;

UPDATE quest_template SET PrevQuestId=489 WHERE id=13946;




