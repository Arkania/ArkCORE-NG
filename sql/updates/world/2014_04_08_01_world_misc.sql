
UPDATE quest_template SET PrevQuestId=14099 WHERE Id in (14265,14269,17273,14275,14277,14278,14280);

update creature_template_addon set auras=NULL where entry=35871;

update creature_template set ScriptName="npc_trainings_dummy" where entry in (44171,44389,44548,44614,44703,44820,44848,44937,48304);

delete from creature_queststarter where id=35870 and quest=14278;


