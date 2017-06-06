

-- conditional targets for 2 spell 77314/77311
DELETE FROM `conditions` WHERE `SourceEntry` in(77314,77311) and `SourceTypeOrReferenceId`=13;
insert into `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) value
('13','1','77314','0','0','31','0','3','41202','0','0','0','0','',NULL),
('13','1','77311','0','0','31','0','3','41237','0','0','0','0','',NULL);

UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=41237;
UPDATE `creature_template` SET `AIName`='SmartAI',`faction`=35 WHERE `entry`=41202;

-- Sai Constriction Totem/Kharanos Mountaineer.
delete from smart_scripts where entryorguid in(41237,41202) and `source_type`=0;
insert into `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values('41202','0','0','0','8','0','100','0','77314','0','0','0','45','1','1','0','0','0','0','9','41237','0','10','0','0','0','0','Constriction Totem - OnSpellHit - Set Data On Mountaineer.');
insert into `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values('41202','0','1','0','8','0','100','0','77314','0','0','0','33','41202','0','0','0','0','0','7','0','0','0','0','0','0','0','Constriction Totem - OnSpellHit - Kill Credit.');
insert into `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values('41202','0','2','0','8','0','100','0','77314','0','0','0','41','0','0','0','0','0','0','1','0','0','0','0','0','0','0','Constriction Totem - On spell hit - Despawn');
insert into `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values('41202','0','3','0','1','0','100','0','500','500','500','500','11','77311','2','0','0','0','0','1','0','0','0','0','0','0','0','Constriction Totem - Cast aura on Mountaineer.');
insert into `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values('41237','0','0','0','38','0','100','1','1','1','0','0','1','1','6000','0','0','0','0','1','0','0','0','0','0','0','0','Mountaineer - OnDataSet - Talk0');
insert into `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values('41237','0','1','0','52','0','100','0','1','41237','0','0','36','41181','0','0','0','0','0','1','0','0','0','0','0','0','0','Mountaineer - OnTextOver - Set New Template');
insert into `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values('41237','0','2','3','52','0','100','0','1','41237','0','0','46','10','0','0','0','0','0','1','0','0','0','0','0','0','0','Mountaineer - OnTextOver - Flee');
insert into `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values('41237','0','3','0','61','0','100','0','0','0','0','0','41','5000','0','0','0','0','0','1','0','0','0','0','0','0','0','Mountaineer - OnSmartLink - Despawn 6sec');

-- Kharanos Mountaineer Talk.
delete from `creature_text` where `entry`=41237;
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('41237','1','0','Thank you for freeing me!','12','0','0','0','0','0','kharanos Mountaineer','41181');

-- Misc fix.
UPDATE `quest_template` SET `Level` = 8 , `MinLevel` = 5 WHERE `Id` = 25839;
DELETE FROM `spell_scripts` WHERE `id` = 77314 AND `datalong` = 41202;

-- Missing Loot table entry.
UPDATE `gameobject_template` SET `data1` = 203385 WHERE `entry` = 203385;
DELETE FROM `gameobject_loot_template` WHERE `Entry` = 203385;
INSERT INTO `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) values('203385','56225','0','100','1','1','0','1','1',NULL);

