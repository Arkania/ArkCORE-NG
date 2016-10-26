
UPDATE locales_quest SET QuestGiverTextWindow_loc3="Friersythie", QuestGiverTargetName_loc3="Friersythie" WHERE Id=14236;

delete from item_script_names where Id=49108;
insert into item_script_names values 
(49108, "item_weed_whacker_49108");

UPDATE quest_template SET RewardSpell=0 WHERE Id=14303;

update creature set phaseIds="", phaseGroup=407 where guid in (248445);
update creature set phaseIds="", phaseGroup=407 where id in (35875, 35882, 36432, 39655);

delete from creature where id=35891;

-- phase 171

update creature set phaseIds="171", phaseGroup=0 where guid in (246053, 246054, 246055, 248482);
update creature set phaseIds="171", phaseGroup=0 where id in (36421, 36422, 36423);

update gameobject set phaseIds="171", phaseGroup=0 where guid in (168876, 168877, 168878);

UPDATE creature_template_addon SET auras="68327 76354" WHERE entry=35904;
UPDATE creature_template_addon SET auras="68327 68322" WHERE entry=36092;

update creature set phaseIds="171", phaseGroup=0 where id in (36092);

delete from item_script_names where Id=49611;
insert into item_script_names values 
(49611, "item_infrared_heat_focals_49611");

UPDATE creature_template SET ScriptName="npc_orc_scout_36100" WHERE entry=36100;

