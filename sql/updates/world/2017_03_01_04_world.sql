UPDATE creature_template SET ScriptName="npc_wounded_outrunner_44857" WHERE entry=44857;

UPDATE quest_template SET RequiredNpcOrGo1=44857 WHERE Id=10072;

INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorType`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES 
(13,1,72886,0,0,31,0,3,38753,0,0,0,0,'',NULL);

UPDATE creature_template SET minlevel=53, maxlevel=54, unit_flags=33554432,AIName='SmartAI' WHERE entry in (46881, 46882);

UPDATE `creature` SET `spawndist`=0,`MovementType`=0 WHERE id IN(46881, 46882);

-- Smart_scripts and Conditions. 
-- Date: 2017-02-27 13:38
DELETE FROM `smart_scripts` WHERE `entryorguid` IN(46882, 46881) and `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(46881,0,0,1,8,0,100,0,87293,0,100,100,33,46909,0,0,0,0,0,7,0,0,0,0,0,0,0,'Fallen Marshtide Footman - On Spell Hit - Give Credit'),
(46881,0,1,0,61,0,100,0,0,0,0,0,41,2000,0,0,0,0,0,1,0,0,0,0,0,0,0,'Fallen Marshtide Footman - On Spell Hit - despawn 2000ms'),
(46882,0,0,1,8,0,100,0,87296,0,100,100,33,46913,0,0,0,0,0,7,0,0,0,0,0,0,0,'Fallen Stonard Warrior - On Spell Hit - Give Credit'),
(46882,0,1,0,61,0,100,0,0,0,0,0,41,2000,0,0,0,0,0,1,0,0,0,0,0,0,0,'Fallen Stonard Warrior - On Spell Hit - despawn 2000ms');
 
DELETE FROM `conditions` WHERE `SourceEntry` IN(87296, 87293);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorType`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES 
(13,1,87296,0,0,31,0,3,46882,0,0,0,0,'',NULL),
(13,1,87293,0,0,31,0,3,46881,0,0,0,0,'',NULL);

UPDATE `quest_template` SET `CompletedText`="Return to Well Watcher Solanian on Sunstrider Isle." WHERE `Id`=10072;
