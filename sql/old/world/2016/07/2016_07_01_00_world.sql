
-- quest 36140 is only started by gwen armstead
-- fix issue #159
delete from creature_queststarter where id=36140 and quest=14336;


-- fix questline 
UPDATE quest_template SET NextQuestIdChain=14366 WHERE Id=14347;
UPDATE quest_template SET NextQuestIdChain=14366 WHERE Id=14348;
UPDATE quest_template SET PrevQuestId=0, NextQuestIdChain=14367 WHERE Id=14366;
