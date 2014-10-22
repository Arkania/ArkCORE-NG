
set @Quest=14375; -- Last Chance at Humanity
set @KrennanEntry=36331;
set @GennEntry=36332;
set @GodfreyEntry=36170;
set @KrennanGuid=250081;
set @GennGuid=252045;
set @GodfreyGuid=252040;

-- enable first duskhaven quest
UPDATE quest_template SET Method=2 WHERE Id=@Quest;

-- krennan aranas wrong phase and no movement
update creature set phasemask=2, MovementType=0 where guid=@KrennanGuid;

update creature_template set AIName="", ScriptName="npc_krennan_aranas_lcah" where entry=@KrennanEntry;	
update creature_template set AIName="", ScriptName="npc_genn_greymane_lcah" where entry=@GennEntry;	
update creature_template set AIName="", ScriptName="npc_lord_godfrey_lcah" where entry=@GodfreyEntry;	

UPDATE quest_template SET PrevQuestId=14375, NextQuestId=14320, ExclusiveGroup=14313, NextQuestIdChain=0 WHERE id=14313;
UPDATE quest_template SET PrevQuestId=14375, NextQuestId=14320, ExclusiveGroup=14313, NextQuestIdChain=0 WHERE id=14319;
UPDATE quest_template SET PrevQuestId=0, NextQuestId=0, ExclusiveGroup=0, NextQuestIdChain=0 WHERE id=14320;

-- no movement lord godfrey 2
update creature set MovementType=0 where guid=250021;

