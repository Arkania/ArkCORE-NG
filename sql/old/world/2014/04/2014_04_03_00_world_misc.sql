
-- set phaase shift to core_script
update quest_template set RewardSpell=0 where Id=14099;
UPDATE quest_template SET SpecialFlags=4 WHERE Id=14078;
UPDATE quest_template SET NextQuestId=0 WHERE Id in (14093,14094);

update creature_template set AIName="", ScriptName="npc_prince_liam_greymane_phase1" where entry=34850;
update creature_template set AIName="", ScriptName="npc_lieutenant_walden_phase1" where entry=34863;
update creature_template set AIName="", ScriptName="npc_panicked_citizen_phase1" where entry=34851;
update creature_template set AIName="", ScriptName="npc_rampaging_worgen_cw_phase2" where entry=34884;


UPDATE quest_template SET PrevQuestId=8325 WHERE Id=8326;

-- set correct phase 8 on quest "The Rebel Lord's Arsenal" with core script
UPDATE quest_template SET RewardSpell=0 WHERE Id=14159;

-- insert script for setting correct phase
update creature_template set AIName="", ScriptName="npc_josiah_avery_human_phase4" where entry=35369;
update creature_template set AIName="", ScriptName="npc_josiah_avery_worgen_phase8" where entry=35370;

-- missing text
delete from creature_text where entry=35370 and groupid=0 and id=0; 
insert into creature_text (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) value 
(35370,0,0,"The pain is unberable!",14,0,1,0,0,0,"Josiah Avery - Text 0");

UPDATE quest_template SET RewardSpell=0 WHERE Id=14078;
