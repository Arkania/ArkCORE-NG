
UPDATE quest_template SET PrevQuestId=483 WHERE id=487;

UPDATE quest_template SET PrevQuestId=997 WHERE id=918;

DELETE FROM conditions WHERE sourcetypeorreferenceid=15 AND sourcegroup=6944 AND sourceentry=1 AND sourceid=0 AND elsegroup=0 AND conditiontypeorreference=28 AND conditiontarget=0 AND conditionvalue1=12770 AND conditionvalue2=0 AND conditionvalue3=0;
INSERT INTO conditions 
(SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ErrorTextId, ScriptName, Comment)
VALUES
(15, 6944, 1, 0, 0, 28, 0, 12770, 0, 0, 0, 0, 0, "", "");


UPDATE locales_quest SET Title_loc3="Teldrassil: Krone von Azeroth" WHERE id=921;

UPDATE locales_quest SET Title_loc3="Teldrassil: Gebt das Wissen weiter" WHERE id=928;

UPDATE locales_quest SET Title_loc3="Teldrassil: Die Verweigerung der Aspekte" WHERE id=929;

UPDATE locales_quest SET Title_loc3="Teldrassil: Der Anbruch des Tages" WHERE id=933;

UPDATE locales_quest SET Title_loc3="Die Wasser von Teldrassil" WHERE id=935;

UPDATE locales_quest SET Title_loc3="Teldrassil: Die Bürde der Kaldorei" WHERE id=7383;


UPDATE quest_template SET PrevQuestId=917, NextQuestId=0 WHERE id=920;

UPDATE quest_template SET PrevQuestId=920, NextQuestId=0 WHERE id=921;

UPDATE quest_template SET PrevQuestId=921 WHERE id=928;


UPDATE quest_template SET NextQuestId=0 WHERE id=894;

UPDATE quest_template SET PrevQuestId=894, NextQuestId=0 WHERE id=900;

UPDATE quest_template SET NextQuestId=0, NextQuestIdChain=0 WHERE id=901;

UPDATE quest_template SET PrevQuestId=901 WHERE id=902;

UPDATE quest_template SET PrevQuestId=882, NextQuestId=0 WHERE id=907;

UPDATE quest_template SET PrevQuestId=907, NextQuestId=0 WHERE id=913;


UPDATE quest_template SET ExclusiveGroup=-936, NextQuestIdChain=3761 WHERE id=936;

UPDATE quest_template SET ExclusiveGroup=-936, NextQuestIdChain=3761 WHERE id=3762;

UPDATE quest_template SET ExclusiveGroup=-936, NextQuestIdChain=3761 WHERE id=3784;


UPDATE quest_template SET NextQuestIdChain=14005 WHERE id=933;

UPDATE quest_template SET NextQuestIdChain=935 WHERE id=934;

UPDATE quest_template SET NextQuestIdChain=14039 WHERE id=935;


UPDATE quest_template SET QuestGiverPortrait=3023 WHERE id=13946;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Teufelsfels Grellkin", QuestGiverTargetName_loc3="Grellkin" WHERE id=13946;

UPDATE quest_template SET PrevQuestId=0 WHERE id=7383;


UPDATE creature_template SET KillCredit1=34440 WHERE entry=2002;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Knarzklauenfurbolg", QuestGiverTargetName_loc3="Knarzklaue" WHERE id=13945;


UPDATE quest_poi_points SET x=8384, y=980 WHERE questid=6341 AND id=0 AND idx=0;

UPDATE quest_template SET PrevQuestId=14039 WHERE id=6344;

UPDATE quest_poi_points SET x=9753, y=1590 WHERE questid=2541 AND id=6 AND idx=0;

