
-- Areatrigger SAI
SET @ENTRY := 1447;
DELETE FROM `areatrigger_scripts` WHERE `entry`=@ENTRY;
INSERT INTO `areatrigger_scripts` (`entry`,`ScriptName`) VALUES (@ENTRY,"SmartTrigger");
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=2;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,2,0,0,46,0,100,0,0,0,0,0,45,1,1,0,0,0,0,10,81519,8127,0,0,0,0,0,"Areatrigger - On Trigger - Set Data 1 1");

-- Commander Hogarth
SET @ENTRY := 19937;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,11,0,100,1,0,0,0,0,11,33900,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Commander Hogarth - On Respawn - Cast 'Shroud of Death' (No Repeat)"),
(@ENTRY,@SOURCETYPE,1,2,20,0,100,0,10258,0,0,0,85,38162,0,0,0,0,0,8,0,0,0,-1186.95,2608.81,27.702,5.38523,"Commander Hogarth - On Quest 'Honor the Fallen' Finished - Summon Creature 'Vengeful Unyielding Knight'"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,0,10258,0,0,0,12,19863,6,0,0,0,0,8,0,0,0,-1192.14,2602.7,29.2625,0.0820243,"Commander Hogarth - On Quest 'Honor the Fallen' Finished - Summon Creature 'Vengeful Unyielding'"),
(@ENTRY,@SOURCETYPE,3,4,61,0,100,0,10258,0,0,0,85,38162,0,0,0,0,0,8,0,0,0,-1181.95,2611.13,27.3004,4.61566,"Commander Hogarth - On Quest 'Honor the Fallen' Finished - Summon Creature 'Vengeful Unyielding Knight'"),
(@ENTRY,@SOURCETYPE,4,5,61,0,100,0,10258,0,0,0,12,19863,6,0,0,0,0,8,0,0,0,-1183.65,2603.66,29.4927,6.09219,"Commander Hogarth - On Quest 'Honor the Fallen' Finished - Summon Creature 'Vengeful Unyielding'"),
(@ENTRY,@SOURCETYPE,5,6,61,0,100,0,10258,0,0,0,12,19863,6,0,0,0,0,8,0,0,0,-1184.48,2609.26,27.7192,5.01103,"Commander Hogarth - On Quest 'Honor the Fallen' Finished - Summon Creature 'Vengeful Unyielding'"),
(@ENTRY,@SOURCETYPE,6,7,61,0,100,0,10258,0,0,0,12,19863,6,0,0,0,0,8,0,0,0,-1175.39,2607.4,28.853,3.63473,"Commander Hogarth - On Quest 'Honor the Fallen' Finished - Summon Creature 'Vengeful Unyielding'"),
(@ENTRY,@SOURCETYPE,7,8,61,0,100,0,10258,0,0,0,12,19863,6,0,0,0,0,8,0,0,0,-1178.36,2609.96,27.8814,4.12375,"Commander Hogarth - On Quest 'Honor the Fallen' Finished - Summon Creature 'Vengeful Unyielding'"),
(@ENTRY,@SOURCETYPE,8,9,61,0,100,0,10258,0,0,0,12,19863,6,0,0,0,0,8,0,0,0,-1182.51,2608.35,28.1201,4.67383,"Commander Hogarth - On Quest 'Honor the Fallen' Finished - Summon Creature 'Vengeful Unyielding'"),
(@ENTRY,@SOURCETYPE,9,10,61,0,100,0,10258,0,0,0,12,19863,6,0,0,0,0,8,0,0,0,-1189.12,2601.88,29.6988,0.242659,"Commander Hogarth - On Quest 'Honor the Fallen' Finished - Summon Creature 'Vengeful Unyielding'"),
(@ENTRY,@SOURCETYPE,10,11,61,0,100,0,10258,0,0,0,12,19863,6,0,0,0,0,8,0,0,0,-1179.46,2606.03,29.0216,3.81031,"Commander Hogarth - On Quest 'Honor the Fallen' Finished - Summon Creature 'Vengeful Unyielding'"),
(@ENTRY,@SOURCETYPE,11,12,61,0,100,0,10258,0,0,0,12,19863,6,0,0,0,0,8,0,0,0,-1180.6,2598.15,35.2317,1.94692,"Commander Hogarth - On Quest 'Honor the Fallen' Finished - Summon Creature 'Vengeful Unyielding'"),
(@ENTRY,@SOURCETYPE,12,13,61,0,100,0,10258,0,0,0,85,38162,0,0,0,0,0,8,0,0,0,-1190.87,2607.06,27.9991,5.86898,"Commander Hogarth - On Quest 'Honor the Fallen' Finished - Summon Creature 'Vengeful Unyielding Knight'"),
(@ENTRY,@SOURCETYPE,13,14,61,0,100,0,10258,0,0,0,12,19863,6,0,0,0,0,8,0,0,0,-1179.81,2603.43,29.8027,3.12637,"Commander Hogarth - On Quest 'Honor the Fallen' Finished - Summon Creature 'Vengeful Unyielding'"),
(@ENTRY,@SOURCETYPE,14,15,61,0,100,0,10258,0,0,0,12,19863,6,0,0,0,0,8,0,0,0,-1184.47,2606.9,28.4442,5.18881,"Commander Hogarth - On Quest 'Honor the Fallen' Finished - Summon Creature 'Vengeful Unyielding'"),
(@ENTRY,@SOURCETYPE,15,16,61,0,100,0,10258,0,0,0,12,19863,6,0,0,0,0,8,0,0,0,-1186.63,2605.58,28.7169,5.79079,"Commander Hogarth - On Quest 'Honor the Fallen' Finished - Summon Creature 'Vengeful Unyielding'"),
(@ENTRY,@SOURCETYPE,16,17,61,0,100,0,10258,0,0,0,12,19863,6,0,0,0,0,8,0,0,0,-1189.03,2604.6,28.8694,6.10697,"Commander Hogarth - On Quest 'Honor the Fallen' Finished - Summon Creature 'Vengeful Unyielding'"),
(@ENTRY,@SOURCETYPE,17,18,61,0,100,0,10258,0,0,0,12,19863,6,0,0,0,0,8,0,0,0,-1185.68,2603.39,29.4476,5.18881,"Commander Hogarth - On Quest 'Honor the Fallen' Finished - Summon Creature 'Vengeful Unyielding'"),
(@ENTRY,@SOURCETYPE,18,0,61,0,100,0,10258,0,0,0,12,19863,6,0,0,0,0,8,0,0,0,-1181.97,2605.76,28.9476,4.40683,"Commander Hogarth - On Quest 'Honor the Fallen' Finished - Summon Creature 'Vengeful Unyielding'");

DELETE FROM `creature_template_addon` WHERE `entry` IN (20117, 19863);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
(20117, 0, 0, 0, 0, 0, '33900'),
(19863, 0, 0, 0, 0, 0, '33900');

-- Vengeful Unyielding Knight SAI
SET @ENTRY := 20117;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,54,0,100,0,0,0,0,0,41,15000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vengeful Unyielding Knight - On Just Summoned - Despawn In 15000 ms"),
(@ENTRY,0,1,0,54,0,100,0,0,0,0,0,5,2,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vengeful Unyielding Knight - On Just Summoned - Play Emote 2");

-- Vengeful Unyielding SAI
SET @ENTRY := 19863;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,54,0,100,0,0,0,0,0,41,15000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vengeful Unyielding - On Just Summoned - Despawn In 15000 ms"),
(@ENTRY,0,1,0,54,0,100,0,0,0,0,0,5,2,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vengeful Unyielding - On Just Summoned - Play Emote 2");

UPDATE quest_template SET RequiredSourceItemId1=37881, RequiredSourceItemId2=0, RequiredSourceItemCount1=1, RequiredSourceItemCount2=0 WHERE Id=12456;

-- Tiny Snowman SAI
SET @ENTRY := 15710;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,22,0,100,0,34,0,0,0,5,94,0,0,0,0,0,1,0,0,0,0,0,0,0,"Tiny Snowman - Received Emote 34 - Play Emote 94");

-- Fei Fei
DELETE FROM `smart_scripts` WHERE `entryorguid`=20206 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(20206, 0, 0, 0, 20, 0, 100, 0, 10919, 0, 0, 0, 53, 0, 20206, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Fei Fei - On Quest \'Fei Fei\'s Treat\' Finished - Start Waypoint (Phase 1) (No Repeat)");

-- Silithid Invader
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE  `entry` IN (4131, 4133);
DELETE FROM `smart_scripts` WHERE `entryorguid`=4131 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(4131, 0, 0, 0, 0, 0, 100, 1, 4000, 7000, 22000, 25000, 11, 6016, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Silithid Invader - IC - Cast Pierce Armor'),
(4131, 0, 1, 0, 0, 0, 100, 1, 10000, 16000, 0, 0, 11, 8137, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Silithid Invader - IC - Cast Pierce Armor'),
(4131, 0, 2, 0, 2, 0, 100, 1, 0, 15, 0, 0, 39, 20, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Silithid Invader - on hp below 15 % - call for help');

-- Silithid Hive Drone
DELETE FROM `smart_scripts` WHERE `entryorguid`=4133 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(4133, 0, 2, 0, 2, 0, 100, 1, 0, 15, 0, 0, 39, 20, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Silithid Hive Drone - on hp below 15 % - call for help');

UPDATE creature_template SET mechanic_immune_mask=32 WHERE entry=31464;

-- Quest: A Friendly Chat... (24576, 24657)
-- Snivel Rustrocket set gossip flag
UPDATE `creature_template` SET `npcflag` = 1, `AIName`='SmartAI' WHERE `entry` = 37715;

-- Quest credit SAI
DELETE FROM `smart_scripts` WHERE (`entryorguid`=37715 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(37715,0,0,0,62,0,100,0,10946,0,0,0,11,70646,2,0,0,0,0,7,0,0,0,0,0,0,0, "Snivel Rustrocket - on gosip 10947 - cast Love - Create Snivel's Ledger");

-- Gossip option conditions
DELETE FROM `conditions` WHERE (`SourceTypeOrReferenceId`=15 AND `SourceGroup`=10929);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(15,10929,0,0,9,24576,0,0,0,'','Show gossip only if plaer have A Friendly Chat... Horde quest'),
(15,10929,0,1,9,24657,0,0,0,'','Show gossip only if plaer have A Friendly Chat... Alliance quest');

UPDATE `creature_template` SET `flags_extra`=0 WHERE `entry`=24938;

UPDATE `creature_text` SET `type`=14 WHERE `entry`=20977;

DELETE FROM creature_text WHERE entry=20977 AND groupid=6 AND id=0;
INSERT INTO creature_text VALUES 
(20977, 6, 0, "I didn't even break a sweat on that one!", 14, 0, 100, 1, 0, 11177, "Millhouse Manastorm", 19824);

DELETE FROM creature_text WHERE entry=20977 AND groupid=6 AND id=1;
INSERT INTO creature_text VALUES 
(20977, 6, 1, "You guys feel free to jump in anytime.", 14, 0, 100, 1, 0, 11178, "Millhouse Manastorm", 19825);

UPDATE `quest_template` SET `PrevQuestId`=3451 WHERE  `Id`=3483;

--
UPDATE `creature` SET `position_x`=1772.803833, `position_y`=848.654846, `position_z`=123.192604, `orientation`=1.649258 WHERE  `guid`=236659; -- 127067;
UPDATE `creature` SET `position_x`=1772.699585, `position_y`=852.786560, `position_z`=123.192734, `orientation`=4.675874 WHERE  `guid`=236658; -- 127068;

DELETE FROM `creature_addon` WHERE `guid` IN (236675, 236664, 236661, 236667, 236679);
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
(236675, 0, 0, 0, 1, 4, ''),
(236664, 0, 0, 0, 1, 4, ''),
(236661, 0, 0, 0, 1, 4, ''),
(236667, 0, 0, 0, 1, 4, ''),
(236679, 0, 0, 0, 1, 4, '');

DELETE FROM `creature_addon` WHERE `guid` IN (236659, 236658);
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
(236659, 0, 0, 0, 1, 36, ''),
(236658, 0, 0, 0, 1, 36, '');

UPDATE `creature_addon` SET `emote`=20 WHERE  `guid`=236683; -- 127043;

SET @ENTRY=29830; 
SET @GUID := 236647;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=1580.776,`position_y`=726.0986,`position_z`=143.0329 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,1580.776,726.0986,143.0329,0,0,0,0,100,0),
(@PATH,2,1601.526,726.0986,143.0329,0,0,0,0,100,0),
(@PATH,3,1580.776,726.0986,143.0329,0,0,0,0,100,0),
(@PATH,4,1601.526,726.0986,143.0329,0,0,0,0,100,0);

SET @GUID := 236650;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=1634.252,`position_y`=750.1481,`position_z`=143.0402 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,1634.252,750.1481,143.0402,0,0,0,0,100,0),
(@PATH,2,1645.534,749.2593,143.062,0,0,0,0,100,0),
(@PATH,3,1646.846,740.0786,143.036,0,0,0,0,100,0),
(@PATH,4,1643.028,738.3261,143.0428,0,0,0,0,100,0),
(@PATH,5,1634.346,729.3132,143.0253,0,0,0,0,100,0),
(@PATH,6,1629.24,728.4056,143.036,0,0,0,0,100,0),
(@PATH,7,1625.434,724.1005,143.033,0,0,0,0,100,0),
(@PATH,8,1625.066,724.9523,143.0346,0,0,0,0,100,0),
(@PATH,9,1633.39,728.2556,143.0207,0,0,0,0,100,0),
(@PATH,10,1634.352,731.7579,143.036,0,0,0,0,100,0),
(@PATH,11,1642.503,738.0968,143.036,0,0,0,0,100,0),
(@PATH,12,1646.744,748.6193,143.0608,0,0,0,0,100,0);

SET @GUID := 236648;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=1624.936,`position_y`=762.2312,`position_z`=143.0362 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,1624.936,762.2312,143.0362,0,0,0,0,100,0),
(@PATH,2,1624.857,762.3463,143.0362,0,0,0,0,100,0),
(@PATH,3,1616.904,760.4952,143.0778,0,0,0,0,100,0),
(@PATH,4,1616.059,757.1263,143.036,0,0,0,0,100,0),
(@PATH,5,1615.883,751.8171,143.036,0,0,0,0,100,0),
(@PATH,6,1612.587,742.8907,143.036,0,0,0,0,100,0),
(@PATH,7,1615.973,735.1326,143.036,0,0,0,0,100,0),
(@PATH,8,1616.567,728.8411,143.0389,0,0,0,0,100,0),
(@PATH,9,1616.565,728.8934,143.0389,0,0,0,0,100,0),
(@PATH,10,1616.015,735.0688,143.036,0,0,0,0,100,0),
(@PATH,11,1612.599,741.9441,143.036,0,0,0,0,100,0),
(@PATH,12,1612.643,745.9359,143.036,0,0,0,0,100,0),
(@PATH,13,1615.984,759.0609,143.0375,0,0,0,0,100,0),
(@PATH,14,1620.861,760.4977,143.036,0,0,0,0,100,0),
(@PATH,15,1624.961,762.2328,143.0362,0,0,0,0,100,0),
(@PATH,16,1624.857,762.3463,143.0362,0,0,0,0,100,0),
(@PATH,17,1616.904,760.5043,143.0776,0,0,0,0,100,0);

SET @ENTRY=29774;
SET @GUID := 236706;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=1642.346,`position_y`=653.1481,`position_z`=125.2523 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,1642.346,653.1481,125.2523,0,0,0,0,100,0),
(@PATH,2,1639.856,642.3232,125.6559,0,0,0,0,100,0),
(@PATH,3,1642.258,637.7573,126.032,0,0,0,0,100,0),
(@PATH,4,1647.147,632.4925,126.6323,0,0,0,0,100,0),
(@PATH,5,1657.781,625.1252,128.0753,0,0,0,0,100,0),
(@PATH,6,1664.838,624.4281,127.6226,0,0,0,0,100,0),
(@PATH,7,1669.714,625.9705,127.4224,0,0,0,0,100,0),
(@PATH,8,1674.736,633.4069,127.3273,0,0,0,0,100,0),
(@PATH,9,1673.877,644.5715,126.3829,0,0,0,0,100,0),
(@PATH,10,1668.756,649.8423,126.1618,0,0,0,0,100,0),
(@PATH,11,1662.11,654.2892,125.6076,0,0,0,0,100,0),
(@PATH,12,1655.857,656.4763,125.5904,0,0,0,0,100,0),
(@PATH,13,1645.618,656.3919,125.2844,0,0,0,0,100,0),
(@PATH,14,1642.373,653.2665,125.2903,0,0,0,0,100,0);

DELETE FROM `creature_formations` WHERE `leaderGUID`=236706;
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES 
(236706, 236706, 0, 0, 2, 0, 0),
(236706, 236713, 4, 50, 2, 0, 0),
(236706, 236702, 4, 310, 2, 0, 0);

SET @ENTRY=29829;
SET @GUID := 236657;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=1592.818,`position_y`=817.3067,`position_z`=149.783 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,1592.818,817.3067,149.783,0,0,0,0,100,0),
(@PATH,2,1601.493,805.8055,146.3105,0,0,0,0,100,0),
(@PATH,3,1609.685,802.7231,145.2017,0,0,0,0,100,0),
(@PATH,4,1623.651,794.6301,143.8499,0,0,0,0,100,0),
(@PATH,5,1615.21,801.1007,144.687,0,0,0,0,100,0),
(@PATH,6,1605.104,803.2402,145.5161,0,0,0,0,100,0),
(@PATH,7,1597.137,810.431,147.7381,0,0,0,0,100,0),
(@PATH,8,1591.998,822.5156,150.5477,0,0,0,0,100,0),
(@PATH,9,1586.166,840.6243,153.7294,0,0,0,0,100,0),
(@PATH,10,1584.692,843.8578,154.2673,0,0,0,0,100,0),
(@PATH,11,1584.178,844.4227,154.4869,0,0,0,0,100,0),
(@PATH,12,1590.102,830.2843,152.1621,0,0,0,0,100,0);

SET @GUID := 236656;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=1706.755,`position_y`=857.1785,`position_z`=129.9813 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,1706.755,857.1785,129.9813,0,0,0,0,100,0),
(@PATH,2,1707.281,867.1033,130.2534,0,0,0,0,100,0),
(@PATH,3,1704.177,879.5166,130.7884,0,0,0,0,100,0),
(@PATH,4,1691.342,892.488,132.9258,0,0,0,0,100,0),
(@PATH,5,1679.412,891.944,134.244,0,0,0,0,100,0),
(@PATH,6,1668.286,882.3208,137.746,0,0,0,0,100,0),
(@PATH,7,1673.63,888.4031,136.1639,0,0,0,0,100,0),
(@PATH,8,1687.955,893.6246,133.4256,0,0,0,0,100,0),
(@PATH,9,1701.138,885.8834,131.8191,0,0,0,0,100,0),
(@PATH,10,1706.935,871.8005,130.679,0,0,0,0,100,0);

SET @ENTRY=29820;
SET @GUID := 236672;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=1627.05,`position_y`=895.2917,`position_z`=145.9627 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,1627.05,895.2917,145.9627,0,0,0,0,100,0),
(@PATH,2,1641.819,895.4995,144.4391,0,0,0,0,100,0),
(@PATH,3,1646.381,886.3206,142.0332,0,0,0,0,100,0),
(@PATH,4,1648.376,877.1378,140.8607,0,0,0,0,100,0),
(@PATH,5,1651.261,870.6509,139.9442,0,0,0,0,100,0),
(@PATH,6,1648.879,874.7926,140.348,0,0,0,0,100,0),
(@PATH,7,1648.431,879.759,140.6906,0,0,0,0,100,0),
(@PATH,8,1643.23,894.2725,143.7524,0,0,0,0,100,0),
(@PATH,9,1633.633,896.613,144.9795,0,0,0,0,100,0),
(@PATH,10,1628.168,895.5144,145.8911,0,0,0,0,100,0),
(@PATH,11,1608.678,886.468,148.1761,0,0,0,0,100,0),
(@PATH,12,1600.244,880.922,149.9891,0,0,0,0,100,0),
(@PATH,13,1583.596,870.7088,152.9289,0,0,0,0,100,0),
(@PATH,14,1593.538,876.7352,151.3219,0,0,0,0,100,0),
(@PATH,15,1606.508,885.0313,148.7535,0,0,0,0,100,0),
(@PATH,16,1616.299,891.1467,147.5494,0,0,0,0,100,0),
(@PATH,17,1627.23,895.3035,145.926,0,0,0,0,100,0),
(@PATH,18,1641.784,895.3555,144.6143,0,0,0,0,100,0);

DELETE FROM `creature_formations` WHERE `leaderGUID`=236672;
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES 
(236672, 236672, 0, 0, 2, 0, 0),
(236672, 236662, 4, 90, 2, 0, 0);

DELETE FROM `creature_addon` WHERE `guid` IN (236669, 236670, 236671, 236673, 236674, 236676, 236677, 236678, 236663, 236666, 236668);
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
(236669, 0, 0, 0, 1, 1, ''),  
(236670, 0, 0, 0, 1, 1, ''), 
(236671, 0, 0, 0, 1, 1, ''),  
(236673, 0, 0, 0, 1, 1, ''),  
(236674, 0, 0, 0, 1, 1, ''),  
(236676, 0, 0, 0, 1, 1, ''),  
(236677, 0, 0, 0, 1, 1, ''),  
(236678, 0, 0, 0, 1, 1, ''),  
(236663, 0, 0, 0, 1, 1, ''),  
(236666, 0, 0, 0, 1, 1, ''),  
(236668, 0, 0, 0, 1, 1, ''); 

UPDATE `smart_scripts` SET `action_param1`=1 WHERE  `entryorguid` IN (29774, 29820) AND `source_type`=0 AND `id`=0 AND `link`=1;

-- Spitting Cobra
SET @ENTRY := 29774;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,2,0,0,12000,15000,11,32860,64,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Spitting Cobra - Combat CMC - Cast 'Shadow Bolt' (Normal Dungeon)"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,4,0,0,12000,15000,11,38378,64,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Spitting Cobra - Combat CMC - Cast 'Shadow Bolt' (Heroic Dungeon)"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,2,5000,10000,17000,20000,11,55703,64,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Spitting Cobra - Combat CMC - Cast 'Cobra Strike' (Normal Dungeon)"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,4,5000,10000,17000,20000,11,59020,64,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Spitting Cobra - Combat CMC - Cast 'Cobra Strike' (Heroic Dungeon)");

-- Drakkari God Hunter
SET @ENTRY := 29820;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,2,0,0,2300,5000,11,35946,64,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Drakkari God Hunter - Combat CMC - Cast 'Shoot' (Normal Dungeon)"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,4,0,0,2300,5000,11,59146,64,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Drakkari God Hunter - Combat CMC - Cast 'Shoot' (Heroic Dungeon)"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,2,7000,10000,12000,15000,11,55624,1,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"Drakkari God Hunter - Combat - Cast 'Arcane Shot' (Normal Dungeon)"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,4,7000,10000,12000,15000,11,58973,1,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"Drakkari God Hunter - Combat - Cast 'Arcane Shot' (Heroic Dungeon)"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,6,3000,5000,33000,37000,11,55798,1,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Drakkari God Hunter - Combat - Cast 'Flare' (Dungeon)"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,6,18000,21000,19000,23000,11,55625,0,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"Drakkari God Hunter - Combat - Cast 'Tranquillizing Shot' (Dungeon)"),
(@ENTRY,@SOURCETYPE,6,0,2,0,100,6,0,30,12000,15000,11,31567,1,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Drakkari God Hunter - 0-30% Health - Cast 'Deterrence' (Dungeon)");

-- Dark Rune Theurgist
SET @ENTRY := 27963;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,7,0,0,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Theurgist - Out of Combat - Disable Combat Movement (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,@SOURCETYPE,1,2,4,0,100,3,0,0,0,0,11,15801,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Theurgist - On Aggro - Cast 'Lightning Bolt' (No Repeat) (Normal Dungeon)"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Theurgist - On Aggro - Increment Phase By 1 (No Repeat) (Normal Dungeon)"),
(@ENTRY,@SOURCETYPE,3,0,9,1,100,2,0,40,3400,4800,11,15801,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Theurgist - Within 0-40 Range - Cast 'Lightning Bolt' (No Repeat) (Normal Dungeon)"),
(@ENTRY,@SOURCETYPE,4,5,4,0,100,5,0,0,0,0,11,35010,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Theurgist - On Aggro - Cast 'Lightning Bolt' (No Repeat) (Heroic Dungeon)"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Theurgist - On Aggro - Increment Phase By 1 (No Repeat) (Heroic Dungeon)"),
(@ENTRY,@SOURCETYPE,6,0,9,1,100,4,0,40,3400,4800,11,35010,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Theurgist - Within 0-40 Range - Cast 'Lightning Bolt' (No Repeat) (Heroic Dungeon)"),
(@ENTRY,@SOURCETYPE,7,8,3,1,100,7,0,7,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Theurgist - Between 0-7% Mana - Enable Combat Movement (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,@SOURCETYPE,8,0,61,1,100,0,0,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Theurgist - Between 0-7% Mana - Increment Phase By 1 (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,@SOURCETYPE,9,0,9,1,100,7,35,80,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Theurgist - Within 35-80 Range - Enable Combat Movement (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,@SOURCETYPE,10,0,9,1,100,7,5,15,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Theurgist - Within 5-15 Range - Disable Combat Movement (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,@SOURCETYPE,11,12,9,1,100,7,0,5,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Theurgist - Within 0-5 Range - Enable Combat Movement (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,@SOURCETYPE,12,0,61,1,100,0,0,0,0,0,11,51484,33,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Theurgist - Within 0-5 Range - Cast 'Iron Might' (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,@SOURCETYPE,13,0,3,2,100,6,15,100,100,100,23,0,1,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Theurgist - Between 15-100% Mana - Decrement Phase By 1 (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,@SOURCETYPE,14,0,0,0,100,2,9000,12000,9000,12000,11,53167,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Theurgist - In Combat - Cast 'Forked Lightning' (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,@SOURCETYPE,15,0,0,0,100,4,9000,12000,9000,12000,11,59152,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Theurgist - In Combat - Cast 'Forked Lightning' (Phase 1) (No Repeat) (Dungeon)");

UPDATE `creature_template` SET `InhabitType`=4 WHERE  `entry`=28055;

DELETE FROM `creature_formations` WHERE `leaderGUID`=234018;
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES 
(234018, 234018, 0, 0, 2, 0, 0),  
(234018, 234034, 4, 50, 2, 0, 0),  
(234018, 234035, 4, 310, 2, 0, 0); 

DELETE FROM `creature_formations` WHERE `leaderGUID`=234040;
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES 
(234040, 234040, 0, 0, 2, 0, 0),
(234040, 234022, 3, 50, 2, 0, 0),
(234040, 234027, 3, 310, 2, 0, 0);

DELETE FROM `creature_formations` WHERE `leaderGUID`=234037;
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES 
(234037, 234037, 0, 0, 2, 0, 0),  
(234037, 234020, 3, 50, 2, 0, 0), 
(234037, 234026, 3, 310, 2, 0, 0);  

DELETE FROM `creature_formations` WHERE `leaderGUID`=234036;
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES 
(234036, 234036, 0, 0, 2, 0, 0),
(234036, 234019, 3, 50, 2, 0, 0),
(234036, 234025, 3, 310, 2, 0, 0);

DELETE FROM `creature_formations` WHERE `leaderGUID`=234032;
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES 
(234032, 234032, 0, 0, 2, 0, 0),
(234032, 234014, 3, 50, 2, 0, 0),
(234032, 234024, 3, 310, 2, 0, 0);

DELETE FROM `creature_formations` WHERE `leaderGUID`=234031;
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES 
(234031, 234031, 0, 0, 2, 0, 0),
(234031, 234013, 3, 50, 2, 0, 0),
(234031, 234023, 3, 310, 2, 0, 0);

-- Pathing for  Entry: 28582 'TDB FORMAT' 
SET @GUID := 234031; 
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`) VALUES 
(2340310, 1, 1180.73, 659.129, 196.233, 0, 0, 0, 0, 100, 3108493),
(2340310, 2, 1181.3, 667.947, 196.233, 0, 0, 0, 0, 100, 3108495),
(2340310, 3, 1180.7, 675.583, 196.235, 0, 0, 0, 0, 100, 3108497),
(2340310, 4, 1177.06, 683.484, 196.235, 0, 0, 0, 0, 100, 3108499),
(2340310, 7, 1180.73, 659.129, 196.233, 0, 0, 0, 0, 100, 3108493),
(2340310, 6, 1181.3, 667.947, 196.233, 0, 0, 0, 0, 100, 3108495),
(2340310, 5, 1180.7, 675.583, 196.235, 0, 0, 0, 0, 100, 3108497),
(2340310, 8, 1177.75, 651.607, 196.235, 0, 0, 0, 0, 100, 3108501);

DELETE FROM `creature_formations` WHERE `leaderGUID`=234012;
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES 
(234012, 234012, 0, 0, 2, 0, 0),
(234012, 234011, 5, 270, 2, 0, 0);

DELETE FROM `creature_formations` WHERE `leaderGUID`=234033;
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES 
(234033, 234033, 0, 0, 2, 0, 0),
(234033, 234016, 3, 50, 2, 0, 0),
(234033, 234015, 3, 310, 2, 0, 0);

-- Dark Rune Shaper
SET @ENTRY := 27965;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,1,0,100,7,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Shaper - Out of Combat - Disable Combat Movement (No Repeat) (Dungeon)"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Shaper - On Aggro - Set Event Phase 0 (No Repeat) (Normal Dungeon)"),
(@ENTRY,@SOURCETYPE,2,3,4,0,100,3,0,0,0,0,11,51496,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Shaper - On Aggro - Cast 'Chiseling Ray' (No Repeat) (Normal Dungeon)"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Shaper - On Aggro - Increment Phase By 1 (No Repeat) (Heroic Dungeon)"),
(@ENTRY,@SOURCETYPE,4,0,9,1,100,2,0,40,6000,9000,11,51496,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Shaper - Within 0-40 Range - Cast 'Chiseling Ray' (No Repeat) (Heroic Dungeon)"),
(@ENTRY,@SOURCETYPE,5,6,4,0,100,5,0,0,0,0,11,59034,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Shaper - On Aggro - Cast 'Chiseling Ray' (No Repeat) (Heroic Dungeon)"),
(@ENTRY,@SOURCETYPE,6,0,61,0,100,0,0,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Shaper - Between 0-7% Mana - Increment Phase By 1 (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,@SOURCETYPE,7,0,9,1,100,4,0,40,6000,9000,11,59034,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Shaper - Within 0-40 Range - Cast 'Chiseling Ray' (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,@SOURCETYPE,8,9,3,1,100,7,0,7,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Shaper - Between 0-7% Mana - Enable Combat Movement (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,@SOURCETYPE,9,0,61,1,100,0,0,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Shaper - Within 0-5 Range - Increment Phase By 1 (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,@SOURCETYPE,10,0,9,1,100,7,35,80,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Shaper - Within 35-80 Range - Enable Combat Movement (Phase 1) (No Repeat) (Dungeon)"),
(@ENTRY,@SOURCETYPE,11,0,9,1,100,7,5,15,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Shaper - Within 5-15 Range - Disable Combat Movement (No Repeat) (Dungeon)"),
(@ENTRY,@SOURCETYPE,12,0,9,1,100,7,0,5,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Shaper - Within 0-5 Range - Enable Combat Movement (No Repeat) (Dungeon)"),
(@ENTRY,@SOURCETYPE,13,0,3,2,100,6,15,100,100,100,23,0,1,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dark Rune Shaper - Between 15-100% Mana - Decrement Phase By 1 (No Repeat) (Dungeon)"),
(@ENTRY,@SOURCETYPE,14,0,1,0,100,0,2000,2000,4000,4000,11,50563,0,0,0,0,0,19,28055,50,0,0.0,0.0,0.0,0.0,"Dark Rune Shaper - On Reset - Cast 'Carve Stone'");

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND  `SourceGroup`=1 AND `SourceEntry`=50563;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(13, 1, 50563, 0, 0, 31, 0, 3, 28055, 0, 0, 0, 0, '', 'Carve Stone - only targets Dummy');

DELETE FROM `disables` WHERE `sourceType`=0 AND `entry`=50563;
INSERT INTO `disables` (`sourceType`, `entry`, `flags`, `params_0`, `params_1`, `comment`) VALUES 
(0, 50563, 64, '', '', 'Ignore LOS for Carve Stone');

UPDATE `creature` SET `spawndist`=8, `MovementType`=1 WHERE  `guid` IN (233989, 233988, 233983, 233982);


