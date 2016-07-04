
UPDATE `gameobject` SET `spawnMask` = 1 WHERE `guid` = 40114 AND `id` = 185168;
UPDATE `gameobject` SET `spawnMask` = 2 WHERE `guid` = 26314 AND `id` = 185169; 

DELETE FROM `spell_script_names` WHERE `spell_id` IN (70903,71236,72495,72496,72497,72498,72499,72500);
INSERT INTO `spell_script_names` VALUES 
(70903,'spell_cultist_dark_martyrdom'),
(71236,'spell_cultist_dark_martyrdom'),
(72495,'spell_cultist_dark_martyrdom'),
(72496,'spell_cultist_dark_martyrdom'),
(72497,'spell_cultist_dark_martyrdom'),
(72498,'spell_cultist_dark_martyrdom'),
(72499,'spell_cultist_dark_martyrdom'),
(72500,'spell_cultist_dark_martyrdom');

DELETE FROM `npc_text` WHERE `ID`=9690;
INSERT INTO `npc_text` (`ID`, `text0_0`, `text0_1`, `BroadcastTextID0`, `lang0`, `prob0`, `em0_0`, `em0_1`, `em0_2`, `em0_3`, `em0_4`, `em0_5`, `text1_0`, `text1_1`, `BroadcastTextID1`, `lang1`, `prob1`, `em1_0`, `em1_1`, `em1_2`, `em1_3`, `em1_4`, `em1_5`, `text2_0`, `text2_1`, `BroadcastTextID2`, `lang2`, `prob2`, `em2_0`, `em2_1`, `em2_2`, `em2_3`, `em2_4`, `em2_5`, `text3_0`, `text3_1`, `BroadcastTextID3`, `lang3`, `prob3`, `em3_0`, `em3_1`, `em3_2`, `em3_3`, `em3_4`, `em3_5`, `text4_0`, `text4_1`, `BroadcastTextID4`, `lang4`, `prob4`, `em4_0`, `em4_1`, `em4_2`, `em4_3`, `em4_4`, `em4_5`, `text5_0`, `text5_1`, `BroadcastTextID5`, `lang5`, `prob5`, `em5_0`, `em5_1`, `em5_2`, `em5_3`, `em5_4`, `em5_5`, `text6_0`, `text6_1`, `BroadcastTextID6`, `lang6`, `prob6`, `em6_0`, `em6_1`, `em6_2`, `em6_3`, `em6_4`, `em6_5`, `text7_0`, `text7_1`, `BroadcastTextID7`, `lang7`, `prob7`, `em7_0`, `em7_1`, `em7_2`, `em7_3`, `em7_4`, `em7_5`, `WDBVerified`) VALUES 
(9690, 'The younger races make a big fuss over Winter Veil. Ironforge''s bank is the center of the festivities.', 'The younger races make a big fuss over Winter Veil. Ironforge''s bank is the center of the festivities.', 16179, 0, 01, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

UPDATE `creature_template` SET `ainame`='SmartAI', `scriptname`='' WHERE `entry` IN(18230,18237);

DELETE FROM `smart_scripts` WHERE `entryorguid` IN(18230,18237) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(18230, 0, 0, 0, 1, 0, 100, 0, 0, 0, 500, 500, 29, 0, 0, 0, 0, 0, 0, 19, 18237, 0, 0, 0, 0, 0, 0, 'Trayanise - OOC - Follow Tiny Arcane Construct'),
(18230, 0, 1, 0, 1, 0, 100, 0, 0, 60000, 180000, 300000, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Trayanise - OOC - Say Line 0'),
(18237, 0, 0, 0, 11, 0, 100, 0, 0, 0, 0, 0, 53, 1, 18237, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Tiny Arcane Construct - On Spawn - Start WP');

UPDATE `creature_template` SET `speed_run`=1.142857 WHERE  `entry`=18230;
UPDATE `creature_template` SET `speed_run`=2.142857 WHERE  `entry`=18237;

DELETE FROM `creature_addon` WHERE `guid` IN(187671,187667);
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
(187671, 0, 0, 0x0, 0x1, 0, NULL),
(187667, 0, 0, 0x0, 0x1, 0, NULL);

DELETE FROM `creature_template_addon` WHERE `entry` IN(18230,18237);

DELETE FROM `creature` WHERE `guid` IN(187671,187667);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `MovementType`) VALUES
(187671, 18230, 530, 1, 1,  9891.047, -7180.686, 31.02935, 2.363085, 120, 0, 0), -- 18230 (Area: 3487)
(187667, 18237, 530, 1, 1,  9886.445, -7179.344, 31.03508, 2.353462, 120, 0, 0); -- 18237 (Area: 3487)

DELETE FROM `waypoint_data` WHERE `id` IN(655010,655050);

DELETE FROM `waypoints` WHERE `entry` IN(18230,18237);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(18237, 1, 9854.372, -7131.53, 30.8774,  'Tiny Arcane Construct'),
(18237, 2, 9848.939, -7149.687, 30.88104,  'Tiny Arcane Construct'),
(18237, 3, 9853.528, -7164.35, 30.94116,  'Tiny Arcane Construct'),
(18237, 4, 9873.93, -7174.143, 31.04511,  'Tiny Arcane Construct'),
(18237, 5, 9890.317, -7171.364, 32.04652,  'Tiny Arcane Construct'),
(18237, 6, 9893.691, -7182.642, 31.02659,  'Tiny Arcane Construct'),
(18237, 7, 9906.294, -7211.048, 30.9103,  'Tiny Arcane Construct'),
(18237, 8, 9914.21, -7215.013, 30.81886,  'Tiny Arcane Construct'),
(18237, 9, 9930.763, -7214.394, 30.86104,  'Tiny Arcane Construct'),
(18237, 10, 9954.362, -7211.773, 30.87779,  'Tiny Arcane Construct'),
(18237, 11, 9953.68, -7204.061, 30.87768,  'Tiny Arcane Construct'),
(18237, 12, 9941.922, -7198.434, 30.87755,  'Tiny Arcane Construct'),
(18237, 13, 9915.126, -7188.168, 30.9569,  'Tiny Arcane Construct'),
(18237, 14, 9897.4, -7190.357, 31.03786,  'Tiny Arcane Construct'),
(18237, 15, 9885.156, -7178.048, 31.03413,  'Tiny Arcane Construct'),
(18237, 16, 9874.851, -7163.025, 30.99726,  'Tiny Arcane Construct'),
(18237, 17, 9867.523, -7139.578, 30.87733,  'Tiny Arcane Construct');

DELETE FROM `creature_text` WHERE `entry`=18230;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextID`, `comment`) VALUES
(18230, 0, 0, 'The magister''s going to kill me...', 12, 1, 100, 0, 0, 0, 15011, 'Trayanise'),
(18230, 0, 1, 'No, no, no! Come back here!', 12, 1, 100, 0, 0, 0, 15010, 'Trayanise'),
(18230, 0, 2, 'Argh. They told me those crystals would work properly!', 12, 1, 100, 0, 0, 0, 15013, 'Trayanise'),
(18230, 0, 3, 'When I catch you, I''m going to disenchant your components, so help me...', 12, 1, 100, 0, 0, 0, 15015, 'Trayanise'),
(18230, 0, 4, 'Get back here, you little...', 12, 1, 100, 0, 0, 0, 15012, 'Trayanise'),
(18230, 0, 5, 'You stay out of the regent lord''s way! I mean it!', 12, 1, 100, 0, 0, 0, 15014, 'Trayanise');

DELETE FROM creature_text WHERE entry=37225 AND groupid between 17 and 22;
INSERT INTO creature_text VALUES 
(37225, 17, 0, "Halt! Do not carry that blade any further!", 14, 0, 100, 25, 0, 16675, "Uther the Lightbringer", 37201),
(37225, 18, 0, "Do you realize what you've done?", 14, 0, 100, 5, 0, 16676, "Uther the Lightbringer", 37202),
(37225, 19, 0, "You have forged this blade from saronite, the very blood of an old god. The power of the Lich King calls to this weapon.", 12, 0, 100, 1, 0, 16677, "Uther the Lightbringer", 37204),
(37225, 20, 0, "Each moment you tarry here, Quel'Delar drinks in the evil of this place.", 12, 0, 100, 1, 0, 16678, "Uther the Lightbringer", 38442),
(37225, 21, 0, "There is only one way to cleanse this sword. Make haste for the Sunwell and immerse the blade in its waters.", 12, 0, 100, 25, 0, 16679, "Uther the Lightbringer", 37205),
(37225, 22, 0, "I can resist Frostmourne's call no more...", 12, 0, 100, 1, 0, 16680, "Uther the Lightbringer", 37206);

DELETE FROM `creature_text` WHERE `entry` IN(37158,37704);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) VALUES
(37158, 0, 0, '%s prepares to attack!', 41, 0, 100, 0, 0, 0, 'Quel''Delar', 37211),
(37704, 0, 0, 'Quel''Delar leaps to life in the presence of Frostmourne!', 41, 0, 100, 0, 0, 0, 'Frostmourne Altar Bunny (Quel''Delar)', 37645);

UPDATE `creature_template` SET `flags_extra`=0, `AIName`="", `ScriptName`='npc_quel_delar_sword', `InhabitType`=7 WHERE `entry`=37158;
UPDATE `creature_template` SET `AIName`="", `ScriptName`='npc_uther_quel_delar' WHERE `entry`=37225;
UPDATE `creature_template` SET `AIName`="", `ScriptName`='npc_the_lich_king_escape_hor' WHERE `entry`=36954;

delete from areatrigger_scripts where entry in (5605, 5660, 5740);
insert into areatrigger_scripts values 
(5605, "at_hor_shadow_throne"),
(5660, "at_hor_uther_quel_delar_start"),
(5740, "at_hor_impenetrable_door");

delete from spell_script_names where spell_id in (72900, 70190, 70017);
insert into spell_script_names values 
(72900, "spell_hor_start_halls_of_reflection_quest_ae"),
(70190, "spell_hor_evasion"),
(70017, "spell_hor_gunship_cannon_fire");

DELETE FROM `conditions` WHERE `SourceEntry` = 73035 AND `SourceTypeOrReferenceId` = 13;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `Comment`) VALUES
(13,1,73035,0,0,31,0,3,37704,0,0,0,0,'Essence of the Captured (73035) only hits Frostmourne Altar Bunny (Quel''Delar)');

DELETE FROM `gameobject_template`  WHERE `entry` = 180856;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `data0`, `data1`, `data2`, `data3`, `size`) VALUES
(180856, 10, 6522, 'Firework Rocket, Type 1 Purple', 0, 0, 0, 3000, 1);

DELETE FROM `skill_fishing_base_level` WHERE `entry`=4710;
INSERT INTO `skill_fishing_base_level` (`entry`, `skill`) VALUES
(4710, 480);

-- The Brewmaiden SAI
SET @ENTRY := 36021;

UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY*100 AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,22,0,100,0,101,0,0,0,11,48249,1,0,0,0,0,7,0,0,0,0,0,0,0,'The Brewmaiden - Received Emote 101 - Cast ''Brewfest Brew Toss''');

DELETE FROM `creature_template_addon` WHERE `entry`=@ENTRY;
INSERT INTO `creature_template_addon` (`entry`,`bytes2`,`auras`) VALUES
(@ENTRY,0x1,'68269');

-- The Brewmaiden SAI
SET @ENTRY := 27166;

UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,22,0,100,0,101,0,0,0,11,48249,1,0,0,0,0,7,0,0,0,0,0,0,0,'The Brewmaiden - Received Emote 101 - Cast ''Brewfest Brew Toss''');

DELETE FROM `creature_template_addon` WHERE `entry`=@ENTRY;
INSERT INTO `creature_template_addon` (`entry`,`bytes2`,`auras`) VALUES
(@ENTRY,0x1,'51847');

-- Fel Portal Alarm SAI
SET @ENTRY := 23310;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,1,0,0,0,0,11,46907,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fel Portal Alarm - On Respawn - Cast 'Boss Fel Portal State' (No Repeat)"),
(@ENTRY,0,1,0,38,0,100,0,1,1,0,0,23,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fel Portal Alarm - On Data Set 1 1 - Increment Phase"),
(@ENTRY,0,2,3,1,32,100,0,1000,1000,0,0,12,25003,5,120000,0,0,0,1,0,0,0,0,0,0,0,"Fel Portal Alarm - Out of Combat - Summon Creature 'Emissary of Hate' (Phase 32)"),
(@ENTRY,0,3,0,61,32,100,0,1000,1000,0,0,22,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Fel Portal Alarm - Out of Combat - Set Event Phase 0 (Phase 32)");

DELETE FROM `creature` WHERE `id`=25003;

-- Irespeaker SAI
SET @ENTRY := 24999;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,1500,3000,10000,15000,11,35913,0,0,0,0,0,2,0,0,0,0,0,0,0,"Irespeaker - In Combat - Cast 'Fel Fireball'"),
(@ENTRY,0,1,0,0,0,100,0,13000,16000,20000,35000,11,18267,0,0,0,0,0,2,0,0,0,0,0,0,0,"Irespeaker - In Combat - Cast 'Curse of Weakness'"),
(@ENTRY,0,2,0,6,0,100,1,0,0,0,0,33,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Irespeaker - On Just Died - Quest Credit 'Kanrethad's Quest' (No Repeat)"),
(@ENTRY,0,3,0,6,0,100,0,5000,5000,10000,10000,45,1,1,0,0,0,0,10,79450,23310,0,0,0,0,0,"Irespeaker - On Just Died - Set Data 1 1");

-- Unleashed Hellion SAI
SET @ENTRY := 25002;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,6,0,100,1,0,0,0,0,33,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Unleashed Hellion - On Just Died - Quest Credit 'Kanrethad's Quest' (No Repeat)"),
(@ENTRY,0,1,0,0,0,100,0,4000,5000,18000,35000,11,11876,0,0,0,0,0,2,0,0,0,0,0,0,0,"Unleashed Hellion - In Combat - Cast 'War Stomp'"),
(@ENTRY,0,2,0,0,0,100,0,6000,9000,12600,16000,11,20754,0,0,0,0,0,2,0,0,0,0,0,0,0,"Unleashed Hellion - In Combat - Cast 'Rain of Fire'"),
(@ENTRY,0,3,0,6,0,100,0,0,0,0,0,45,1,1,0,0,0,0,10,79450,23310,0,0,0,0,0,"Unleashed Hellion - On Just Died - Set Data 1 1");

-- Emissary of Hate SAI
SET @ENTRY := 25003;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,5000,15000,20000,11,25003,0,0,0,0,0,2,0,0,0,0,0,0,0,"Emissary of Hate - In Combat - Cast 'Mortar'"),
(@ENTRY,0,1,0,0,0,100,0,8000,10000,15000,20000,11,38611,0,0,0,0,0,2,0,0,0,0,0,0,0,"Emissary of Hate - In Combat - Cast 'Flame Wave'"),
(@ENTRY,0,2,0,54,0,100,0,0,0,0,0,89,10,0,0,0,0,0,1,0,0,0,0,0,0,0,"Emissary of Hate - On Just Summoned - Start Random Movement");

-- Master Gadrin SAI
SET @ENTRY := 3188;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,20,0,100,0,808,0,0,0,80,@ENTRY*100+00,2,0,0,0,0,1,0,0,0,0,0,0,0,"Master Gadrin - On Quest 'Minshina's Skull' Finished - Run Script");

-- Actionlist SAI
SET @ENTRY := 318800;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,2000,2000,0,0,12,3289,5,14000,0,0,0,8,0,0,0,-822.91,-4923.33,19.6365,3.41642,"Master Gadrin - On Script - Summon Creature 'Spirit of Minshina'"),
(@ENTRY,9,1,0,0,0,100,0,2000,2000,0,0,66,0,0,0,0,0,0,21,20,0,0,0,0,0,0,"Master Gadrin - On Script - Set Orientation Closest Player"),
(@ENTRY,9,2,0,0,0,100,0,3000,3000,0,0,1,0,0,0,0,0,0,21,20,0,0,0,0,0,0,"Master Gadrin - On Script - Say Line 0");

-- Spirit of Minshina SAI
SET @ENTRY := 3289;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,54,0,100,0,0,0,0,0,80,@ENTRY*100+00,2,0,0,0,0,1,0,0,0,0,0,0,0,"Spirit of Minshina - On Just Summoned - Run Script");

-- Actionlist SAI
SET @ENTRY := 328900;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,2000,2000,0,0,66,0,0,0,0,0,0,21,20,0,0,0,0,0,0,"Spirit of Minshina - On Script - Set Orientation Closest Player"),
(@ENTRY,9,1,0,0,0,100,0,2000,2000,0,0,5,2,0,0,0,0,0,1,2000,2000,0,0,0,0,0,"Spirit of Minshina - On Script - Play Emote 2"),
(@ENTRY,9,2,0,0,0,100,0,11000,11000,0,0,41,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Spirit of Minshina - On Script - Despawn Instant");

DELETE FROM `creature_text` WHERE `entry`=3188;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) VALUES 
(3188, 0, 0, 'I thank you, $n.  And my brother thanks you.', 12, 0, 100, 0, 0, 0, 'Master Gadrin', 983);

DELETE FROM `waypoints` WHERE `entry`=16856;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(16856, 1,-807.327,2739.82,115.447, 'Caretaker Dilandrus'),
(16856, 2,-798.86,2719.21,111.628, 'Caretaker Dilandrus'),
(16856, 3,-785.502,2706.21,107.293, 'Caretaker Dilandrus'),
(16856, 4,-785.546,2702.16,106.208, 'Caretaker Dilandrus'),
(16856, 5,-787.652,2700.58,105.792, 'Caretaker Dilandrus'),
(16856, 6,-791.771,2694.26,104.589, 'Caretaker Dilandrus'),
(16856, 7,-793.482,2693.76,104.592, 'Caretaker Dilandrus'),
(16856, 8,-794.696,2691.44,104.35, 'Caretaker Dilandrus'),
(16856, 9,-797.951,2691.02,104.535, 'Caretaker Dilandrus'),
(16856, 10,-798.984,2693.63,104.891, 'Caretaker Dilandrus'),
(16856, 11,-797.778,2697.53,105.43, 'Caretaker Dilandrus'),
(16856, 12,-792.678,2705.64,106.948, 'Caretaker Dilandrus'),
(16856, 13,-792.409,2708.46,107.754, 'Caretaker Dilandrus'),
(16856, 14,-794.25,2710.38,108.384, 'Caretaker Dilandrus'),
(16856, 15,-799.924,2706.66,107.387, 'Caretaker Dilandrus'),
(16856, 16,-807.92,2692.9,104.856, 'Caretaker Dilandrus'),
(16856, 17,-811.612,2690.9,104.36, 'Caretaker Dilandrus'),
(16856, 18,-814.837,2692.26,104.736, 'Caretaker Dilandrus'),
(16856, 19,-814.33,2696.03,105.773, 'Caretaker Dilandrus'),
(16856, 20,-809.779,2704.45,107.63, 'Caretaker Dilandrus'),
(16856, 21,-801.425,2715.06,109.679, 'Caretaker Dilandrus'),
(16856, 22,-801.359,2718.11,110.676, 'Caretaker Dilandrus'),
(16856, 23,-804.433,2720.69,111.13, 'Caretaker Dilandrus'),
(16856, 24,-810.324,2717.67,110.329, 'Caretaker Dilandrus'),
(16856, 25,-814.433,2712.14,109.487, 'Caretaker Dilandrus'),
(16856, 26,-820.17,2701.35,107.506, 'Caretaker Dilandrus'),
(16856, 27,-823.067,2699.77,107.458, 'Caretaker Dilandrus'),
(16856, 28,-824.921,2701.38,107.939, 'Caretaker Dilandrus'),
(16856, 29,-824.739,2706.05,108.591, 'Caretaker Dilandrus'),
(16856, 30,-820.185,2714.8,110.056, 'Caretaker Dilandrus'),
(16856, 31,-814.476,2725.61,111.567, 'Caretaker Dilandrus'),
(16856, 32,-807.327,2739.82,115.447, 'Caretaker Dilandrus'),
(16856, 33,-807.327,2739.82,115.447, 'Caretaker Dilandrus');

UPDATE `creature` SET `position_x`=-807.327, `position_y`=2739.82, `position_z`=115.447, `orientation`=2.611, `MovementType`=2 WHERE  `guid`=180484;

-- Caretaker Dilandrus SAI
SET @ENTRY := 16856;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,25,0,100,0,0,0,0,0,53,0,16856,1,0,0,0,1,0,0,0,0,0,0,0,"Caretaker Dilandrus - On Reset - Start Waypoint"),
(@ENTRY,0,1,0,40,0,100,0,5,16856,0,0,80,@ENTRY*100+01,2,0,0,0,0,1,0,0,0,0,0,0,0,"Caretaker Dilandrus - On Waypoint 5 Reached - Run Script"),
(@ENTRY,0,2,0,40,0,100,0,7,16856,0,0,80,@ENTRY*100+01,2,0,0,0,0,1,0,0,0,0,0,0,0,"Caretaker Dilandrus - On Waypoint 7 Reached - Run Script"),
(@ENTRY,0,3,0,40,0,100,0,11,16856,0,0,80,@ENTRY*100+01,2,0,0,0,0,1,0,0,0,0,0,0,0,"Caretaker Dilandrus - On Waypoint 11 Reached - Run Script"),
(@ENTRY,0,4,0,40,0,100,0,15,16856,0,0,80,@ENTRY*100+01,2,0,0,0,0,1,0,0,0,0,0,0,0,"Caretaker Dilandrus - On Waypoint 15 Reached - Run Script"),
(@ENTRY,0,5,0,40,0,100,0,20,16856,0,0,80,@ENTRY*100+01,2,0,0,0,0,1,0,0,0,0,0,0,0,"Caretaker Dilandrus - On Waypoint 20 Reached - Run Script"),
(@ENTRY,0,6,0,40,0,100,0,24,16856,0,0,80,@ENTRY*100+01,2,0,0,0,0,1,0,0,0,0,0,0,0,"Caretaker Dilandrus - On Waypoint 24 Reached - Run Script"),
(@ENTRY,0,7,0,40,0,100,0,30,16856,0,0,80,@ENTRY*100+01,2,0,0,0,0,1,0,0,0,0,0,0,0,"Caretaker Dilandrus - On Waypoint 30 Reached - Run Script"),
(@ENTRY,0,8,0,40,0,100,0,33,16856,0,0,54,300000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Caretaker Dilandrus - On Waypoint 33 Reached - Pause Waypoint");

-- Actionlist SAI
SET @ENTRY := 1685601;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,0,0,0,0,54,10000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Caretaker Dilandrus - On Script - Pause Waypoint"),
(@ENTRY,9,1,0,0,0,100,0,0,0,0,0,66,0,0,0,0,0,0,1,0,0,0,0,0,0,2.75976,"Caretaker Dilandrus - On Script - Set Orientation Home Position"),
(@ENTRY,9,2,0,0,0,100,0,3000,3000,0,0,5,66,0,0,0,0,0,1,0,0,0,0,0,0,0,"Caretaker Dilandrus - On Script - Play Emote 66"),
(@ENTRY,9,3,0,0,0,100,0,3000,3000,0,0,5,68,0,0,0,0,0,0,0,0,0,0,0,0,0,"Caretaker Dilandrus - On Script - Play Emote 68");

update conditions set ConditionValue3=0 where SourceEntry=48363;

update conditions set SourceGroup=1 where SourceTypeOrReferenceId=13 and SourceGroup=3 and SourceEntry=71310;

update conditions set SourceGroup=1 where SourceTypeOrReferenceId=13 and SourceGroup=3 and SourceEntry=70471;

-- Irespeaker
SET @ENTRY := 24999;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1500,3000,10000,15000,11,35913,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Irespeaker - In Combat - Cast 'Fel Fireball'"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,13000,16000,20000,35000,11,18267,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Irespeaker - In Combat - Cast 'Curse of Weakness'"),
(@ENTRY,@SOURCETYPE,2,0,6,0,100,0,5000,5000,10000,10000,45,1,1,0,0,0,0,10,79450,23310,0,0.0,0.0,0.0,0.0,"Irespeaker - On Just Died - Set Data 1 1"),
(@ENTRY,@SOURCETYPE,3,0,25,0,100,0,0,0,0,0,11,45023,0,0,0,0,0,19,25953,13,0,0.0,0.0,0.0,0.0,"Irespeaker - On Reset - Cast 'Fel Consumption'");

-- Unleashed Hellion
SET @ENTRY := 25002;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,4000,5000,18000,35000,11,11876,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Unleashed Hellion - In Combat - Cast 'War Stomp'"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,6000,9000,12600,16000,11,20754,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Unleashed Hellion - In Combat - Cast 'Rain of Fire'"),
(@ENTRY,@SOURCETYPE,2,0,6,0,100,0,0,0,0,0,45,1,1,0,0,0,0,10,79450,23310,0,0.0,0.0,0.0,0.0,"Unleashed Hellion - On Just Died - Set Data 1 1");

SET @ENTRY := 37158;
SET @SOURCETYPE := 0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;

update creature_template set MovementType=0 where entry=16856;
update creature set MovementType=0 where guid=180484;

UPDATE item_template SET Flags=65604 WHERE entry=54218;

delete from skill_discovery_template where spellId=82180;
INSERT INTO `skill_discovery_template` VALUES 
(82180, 81275, 425, 100),
(82180, 82175, 425, 100),
(82180, 84428, 525, 5),
(82180, 84429, 525, 5),
(82180, 84430, 525, 5),
(82180, 84431, 525, 100),
(82180, 84432, 525, 100),
(82180, 95707, 525, 5);

















