
-- fix quest queive
UPDATE quest_template SET ExclusiveGroup=0,SpecialFlags=4 WHERE Id=14093;
UPDATE quest_template SET ExclusiveGroup=0,SpecialFlags=4,NextQuestId=0 WHERE Id=14098;
UPDATE quest_template SET SpecialFlags=4 WHERE Id=14099;

-- wrong queststarter / ender
delete from creature_questender where id=24832 and quest=14093;
delete from creature_queststarter where id=35830 and quest=14098;
delete from creature_queststarter where id=35873 and quest=14280;

-- creature are twice.. from phase 1 spawned as phase 2
update creature set phaseMask=1 where guid between 240733 and 240738;

-- wrong reqlevel for quest 14283
update npc_trainer set reqlevel=4 where entry=35873 and spell=774;
update npc_trainer set reqlevel=3 where entry=35873 and spell=8921;

-- wrong phase of some npc
update creature set phaseMask=2 where guid in(240556,240572,240523,240557,240527);

UPDATE quest_template SET Flags=524288,QuestGiverPortrait=32778,Objectives="Speak to Celestine of the Harvest and learn Moonfire. Practice using Moonfire 2 times on a 'Trainings Dummy'.",QuestGiverTextWindow="Trainings Dummy",QuestGiverTargetName="Trainings Dummy" WHERE Id=14283;
UPDATE quest_template SET Method=2,Flags=0,SpecialFlags=0 WHERE Id=14283;

UPDATE quest_template SET PrevQuestId=14291 WHERE Id=14157;
UPDATE quest_template SET PrevQuestId=14291 WHERE Id=24930;

-- rename tranings dummy scriptname
update creature_template set ScriptName="npc_trainings_dummy" where ScriptName="npc_training_dummy";

-- prepare showfight phase 4
update creature_template set AIName="",ScriptName="npc_bloodfang_worgen_phase4" where entry=35118;

-- prepare fight on the roof
UPDATE quest_template SET LimitTime=0 WHERE Id=14154;
update creature_template set AIName="",ScriptName="npc_tobias_mistmantle_phase4" where entry=35124;
update creature_template set AIName="",ScriptName="npc_lord_darius_crowley_phase4" where entry=35077;
update creature_template set InhabitType=3, MovementType=0, AIName="",ScriptName="npc_worgen_runt_phase4" where entry=35456;






