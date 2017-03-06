

DELETE FROM `creature_template_addon` WHERE `entry`=34840;
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (34840,0,0,0,1,0,'70329');

UPDATE `creature_template` SET `AIName`='SmartAI', `ScriptName`='' WHERE `entry` in (35063, 35234);

DELETE FROM `smart_scripts` WHERE `entryorguid`IN(35063,35234) AND `source_type`=0;

INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(35063,0,0,0,8,0,100,0,70330,0,0,500,1,0,20000,0,0,0,0,1,0,0,0,0,0,0,0,'on_spell_hit kezan citizen say random'),
(35234,0,0,0,0,0,100,0,5000,11000,7800,21300,11,6257,0,0,0,0,0,2,0,0,0,0,0,0,0,'Cast Torch Toss'),
(35234,0,1,2,8,0,100,0,70330,0,0,500,11,67041,0,0,0,0,0,17,0,20,0,0,0,0,0,'Looter On Spell hit, cast create quest item.'),
(35234,0,2,0,61,0,100,0,0,0,0,0,37,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Looter On Spell hit, die.');


