
update creature_template set AIName="", Scriptname="npc_king_genn_greymane_phase8" where entry=35550;
update creature_template set AIName="", Scriptname="npc_vehicle_genn_greymane_horse_phase8" where entry=35905;
update creature_template set AIName="", Scriptname="npc_krennan_aranas_phase8" where entry=35753; 
update creature_template set AIName="", Scriptname="npc_krennan_aranas_saved_phase8" where entry=35907;
update creature_template set AIName="", Scriptname="npc_cannon_camera_phase8" where entry=50420;
update creature_template set AIName="", Scriptname="npc_lord_godfrey_phase8" where entry=35906;

-- there are more then one prev quest for 14157:  14285, 14286, 14287, 14288, 14289, 14290, 14291
UPDATE quest_template SET PrevQuestId=0, NextQuestId=14157, ExclusiveGroup=14285, NextQuestIdChain=14157 WHERE id=14285;
UPDATE quest_template SET PrevQuestId=0, NextQuestId=14157, ExclusiveGroup=14285, NextQuestIdChain=14157 WHERE id=14286;
UPDATE quest_template SET PrevQuestId=0, NextQuestId=14157, ExclusiveGroup=14285, NextQuestIdChain=14157 WHERE id=14287;
UPDATE quest_template SET PrevQuestId=0, NextQuestId=14157, ExclusiveGroup=14285, NextQuestIdChain=14157 WHERE id=14288;
UPDATE quest_template SET PrevQuestId=0, NextQuestId=14157, ExclusiveGroup=14285, NextQuestIdChain=14157 WHERE id=14289;
UPDATE quest_template SET PrevQuestId=0, NextQuestId=14157, ExclusiveGroup=14285, NextQuestIdChain=14157 WHERE id=14290;
UPDATE quest_template SET PrevQuestId=0, NextQuestId=14157, ExclusiveGroup=14285, NextQuestIdChain=14157 WHERE id=14291;
UPDATE quest_template SET PrevQuestId=0, NextQuestId=0, ExclusiveGroup=0, NextQuestIdChain=28850 WHERE id=14157;
UPDATE quest_template SET PrevQuestId=0, NextQuestId=0, ExclusiveGroup=0, NextQuestIdChain=14154 WHERE id=28850;
UPDATE quest_template SET PrevQuestId=0, NextQuestId=0, ExclusiveGroup=0, NextQuestIdChain=26129 WHERE id=14154;
UPDATE quest_template SET PrevQuestId=14154, NextQuestId=0, ExclusiveGroup=0, NextQuestIdChain=0 WHERE id=26129;
UPDATE quest_template SET PrevQuestId=-14157, NextQuestId=0, ExclusiveGroup=0, NextQuestIdChain=0 WHERE id=24930;

update creature set id=35753 where guid=240783;




