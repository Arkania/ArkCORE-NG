-- Festival Loremaster 16817

UPDATE creature_template SET faction=774, AIName="", ScriptName="npc_festival_loremaster_16817" WHERE entry=16817;

UPDATE quest_template SET PrevQuestId=11731 WHERE id=11657;

UPDATE quest_template SET PrevQuestId=11657 WHERE id=11921;

UPDATE quest_template SET PrevQuestId=11921 WHERE id=11924;

UPDATE quest_template SET PrevQuestId=0, NextQuestId=9365, ExclusiveGroup=-9324, NextQuestIdChain=9365 WHERE id=9324;

UPDATE quest_template SET PrevQuestId=0, NextQuestId=9365, ExclusiveGroup=-9324, NextQuestIdChain=9365 WHERE id=9325;

UPDATE quest_template SET PrevQuestId=0, NextQuestId=9365, ExclusiveGroup=-9324, NextQuestIdChain=9365 WHERE id=9326;

UPDATE quest_template SET PrevQuestId=0, NextQuestId=9365, ExclusiveGroup=-9324, NextQuestIdChain=9365 WHERE id=11935;

UPDATE quest_template SET PrevQuestId=0, NextQuestId=0, ExclusiveGroup=0, NextQuestIdChain=0 WHERE id=9365;

DELETE FROM creature_queststarter WHERE id=16817;
INSERT INTO creature_queststarter 
(id, quest)
VALUES
(16817, 9365),
(16817, 11964);

DELETE FROM creature_questender WHERE id=16817;
INSERT INTO creature_questender 
(id, quest)
VALUES
(16817, 9324),
(16817, 9325),
(16817, 9326),
(16817, 9365),
(16817, 9367),
(16817, 11935),
(16817, 11970);
