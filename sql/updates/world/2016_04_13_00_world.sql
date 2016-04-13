

-- console failure   
update creature_template set AIName="" where entry=32969;
delete from smart_scripts where entryorguid=32969;
  
update creature_template set AIName="" where entry=1544;
delete from smart_scripts where entryorguid=1544;

update creature_template set AIName="" where entry=1665;
delete from smart_scripts where entryorguid=1665;
  
update creature_template set AIName="" where entry=27699;
delete from smart_scripts where entryorguid=27699;

update creature_template set AIName="" where entry=34846;
delete from smart_scripts where entryorguid=34846;

update creature_template set AIName="" where entry=1543;
delete from smart_scripts where entryorguid=1543;
    
update creature_template set AIName="" where entry=36409;
delete from smart_scripts where entryorguid=36409;
  	
update creature_template set AIName="" where entry=39038;
delete from smart_scripts where entryorguid=39038;

update creature_template set AIName="" where entry=39097;
delete from smart_scripts where entryorguid=39097;
  
update creature_template set AIName="" where entry=43497;
delete from smart_scripts where entryorguid=43497;
  
update creature_template set AIName="" where entry=44954;
delete from smart_scripts where entryorguid=44954;
    	
update creature_template set AIName="" where entry=44966;
delete from smart_scripts where entryorguid=44966;
  	
update creature_template set AIName="" where entry=27699;
delete from smart_scripts where entryorguid=27699;

update creature_template set AIName="" where entry=34846;
delete from smart_scripts where entryorguid=34846;
  
update creature_template set AIName="" where entry=1660;
delete from smart_scripts where entryorguid=1660;
    	
-- help from roger

DELETE FROM `spell_proc_event` WHERE entry IN(88821,50687,50686);

UPDATE creature_template SET npcflag=3 WHERE entry=47972;

update creature_template set AIName="" where entry=9027;
delete from smart_scripts where entryorguid=9027;

-- creatures have instance flags in smart_script but not in instance.
UPDATE smart_scripts SET event_flags=0 WHERE entryorguid IN(4285, 4284, 4283);
UPDATE smart_scripts SET action_type=85, action_param1=43693 WHERE entryorguid=186718;
UPDATE smart_scripts SET action_type=85, action_param1=43693 WHERE entryorguid=45188;

-- duplicate spawns
DELETE FROM `creature` where `id`=3554 and `guid`=66225;

-- ranked spells need to have rank 1 as a negative value in spell_script_names.
-- Scriptname: `spell_dk_merciless_combat` spell (Id: 49538) is ranked spell. Perhaps not all ranks are assigned to this script.
delete from `spell_script_names` where spell_id in (49024, 49538);
delete from `spell_script_names` where spell_id in (-49024, -79095, -51625, -86948);
DELETE FROM spell_script_names WHERE ScriptName="spell_rog_restless_blades";
DELETE FROM spell_script_names WHERE ScriptName="spell_rog_deadly_brew";
DELETE FROM spell_script_names WHERE ScriptName="spell_mage_cauterize";
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES (-49024,'spell_dk_merciless_combat');
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES (-79095,'spell_rog_restless_blades');
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES (-51625,'spell_rog_deadly_brew');
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES (-86948,'spell_mage_cauterize');

-- missing script names
UPDATE `creature_template` SET ScriptName="npc_molten_feather" WHERE entry=53089;
UPDATE `creature_template` SET `ScriptName`="npc_ragamuffin_42413" WHERE `entry`= 42413;
UPDATE `creature_template` SET `ScriptName`="npc_gwen_armstead_35840" WHERE `entry`= 35840;
UPDATE `creature_template` SET `ScriptName`="npc_wounded_guard_47091" WHERE `entry`= 47091;
UPDATE `gameobject_template` SET `ScriptName`="go_kurzen_cage_204828" WHERE `entry`= 204828;
UPDATE `creature_template` SET `ScriptName`="npc_throngus_fire_patch" WHERE `entry`=48711;
UPDATE creature_template SET ScriptName="boss_grizzle" WHERE entry=9028;
UPDATE creature_template SET ScriptName="boss_eric" WHERE entry=6907;
UPDATE creature_template SET ScriptName="boss_olav" WHERE entry=6908;
UPDATE creature_template SET ScriptName="boss_morchok2" WHERE entry=58226;
UPDATE creature_template SET ScriptName="npc_kohcrom2" WHERE entry=57774;
UPDATE creature_template SET ScriptName="npc_sphere" WHERE entry=55334;
UPDATE creature_template SET ScriptName="npc_eye_of_gorath" WHERE entry=57875;

-- smart_scripts bugs from DBerrors log.
UPDATE smart_scripts SET action_type=11,action_param1=90798,action_param2=2,action_param3=0 WHERE entryorguid =7523 AND id=2;
UPDATE smart_scripts SET action_type=11,action_param1=35251,action_param2=1,action_param3=0 WHERE entryorguid =20059 AND id in(4,3);
UPDATE `smart_scripts` SET action_type=11,action_param1=90798,action_param2=2,action_param3=0 WHERE entryorguid=7524 AND id=2;
UPDATE `smart_scripts` SET action_type=11,action_param1=42511,action_param2=2,action_param3=0 WHERE entryorguid=23554 AND id=1;
UPDATE `smart_scripts` SET action_type=11,action_param1=42511,action_param2=2,action_param3=0 WHERE entryorguid=23555 AND id=2;
UPDATE `smart_scripts` SET action_type=85,action_param1=43564,action_param2=2,action_param3=0 WHERE entryorguid=23725 AND id=0;
UPDATE `smart_scripts` SET action_type=85,action_param1=43297,action_param2=2,action_param3=0 WHERE entryorguid=24009 AND id=0;
UPDATE `smart_scripts` SET action_type=85,action_param1=43297,action_param2=2,action_param3=0 WHERE entryorguid=24010 AND id=0;






















	
	
	
	