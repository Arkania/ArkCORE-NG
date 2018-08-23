-- Festival Talespinner 16818

UPDATE creature_template SET faction=775, AIName="", ScriptName="npc_festival_talespinner_16818" WHERE entry=16818;

UPDATE quest_template SET PrevQuestId=11970 WHERE id=11964;

UPDATE quest_template SET PrevQuestId=11922 WHERE id=11923;

UPDATE quest_template SET PrevQuestId=11923 WHERE id=11926;

UPDATE quest_template SET PrevQuestId=11926 WHERE id=11925;

UPDATE quest_template SET PrevQuestId=0, NextQuestId=9339, ExclusiveGroup=-9330, NextQuestIdChain=9339 WHERE id=9330;

UPDATE quest_template SET PrevQuestId=0, NextQuestId=9339, ExclusiveGroup=-9330, NextQuestIdChain=9339 WHERE id=9331;

UPDATE quest_template SET PrevQuestId=0, NextQuestId=9339, ExclusiveGroup=-9330, NextQuestIdChain=9339 WHERE id=9332;

UPDATE quest_template SET PrevQuestId=0, NextQuestId=9339, ExclusiveGroup=-9330, NextQuestIdChain=9339 WHERE id=11933;

UPDATE quest_template SET PrevQuestId=0, NextQuestId=0, ExclusiveGroup=0, NextQuestIdChain=0 WHERE id=9339;

DELETE FROM creature_queststarter WHERE id=16818;
INSERT INTO creature_queststarter 
(id, quest)
VALUES
(16818, 11966),
(16818, 9339);

DELETE FROM creature_questender WHERE id=16818;
INSERT INTO creature_questender 
(id, quest)
VALUES
(16818, 9330),
(16818, 9331),
(16818, 9332),
(16818, 9339),
(16818, 9368),
(16818, 11933),
(16818, 11971);

