
-- imported from trinity and thanks to @Killyana
-- DB/Spell: Dreadsteed - Flame visual 

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = 23161; 
INSERT INTO `spell_linked_spell` VALUES (23161, 31725, 0, 'Summon Nightmare'); 

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = 5784; 
INSERT INTO `spell_linked_spell` VALUES (5784, 31725, 0, 'Summon felsteed'); 

-- DB/Quest: Lohn'goron, Bow of the Torn-heart 

UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry` IN (21310, 21309);
UPDATE `creature_template` SET `InhabitType`=4, `gossip_menu_id`=8287, `AIName`='SmartAI' WHERE `entry`=21292;
UPDATE `creature_template` SET `gossip_menu_id`=8288, `AIName`='SmartAI' WHERE `entry`=21318;

DELETE FROM `creature_text` WHERE `entry`=21318;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`, `BroadcastTextID`) VALUES
(21318,0,0,'I... I have died... I was in so much pain... engulfed in darkness... Can you see me, $r?',12,0,100,0,0,0, 'Spirit of Ar''tor ', 18993);

update creature_addon set auras = "60194" where guid in (171869,171870,171871,171872,171873);

DELETE FROM `creature_template_addon` WHERE `entry` IN (21307, 21292);
INSERT INTO `creature_template_addon` (`entry`,`bytes1`,`bytes2`, `emote`, `auras`) VALUES
(21292,0,4097,383,""),
(21307,0,4097,0,"31261");

DELETE FROM `gossip_menu` WHERE `entry`=8288 AND `text_id`=10327;
DELETE FROM `gossip_menu` WHERE `entry`=8287 AND `text_id`=10323;
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES
(8287, 10323),
(8288, 10327);

DELETE FROM `spell_area` WHERE `spell`=60197 AND `area`=3752;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(60197, 3752, 10528, 0, 0, 0, 2, 1, 64, 0);

DELETE FROM `spell_area` WHERE `spell`=60194 AND `area`=3752;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(60194, 3752, 0, 10528, 0, 0, 2, 1, 0, 11);

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (-171869, -171870, -171871, -171872, -171873, 21318, 21292, 21309);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(-171869,0,0,0,1,0,100,1,0,0,0,0,11,36558,0,0,0,0,0,19,21292,30,0,0,0,0,0,'Shadowmoon Valley Invisible Trigger (Tiny) - OOC no repeat - Cast Ar''tor''s Prison'),
(-171870,0,0,0,1,0,100,1,0,0,0,0,11,36558,0,0,0,0,0,19,21292,30,0,0,0,0,0,'Shadowmoon Valley Invisible Trigger (Tiny) - OOC no repeat - Cast Ar''tor''s Prison'),
(-171871,0,0,0,1,0,100,1,0,0,0,0,11,36558,0,0,0,0,0,19,21292,30,0,0,0,0,0,'Shadowmoon Valley Invisible Trigger (Tiny) - OOC no repeat - Cast Ar''tor''s Prison'),
(-171872,0,0,0,1,0,100,1,0,0,0,0,11,36558,0,0,0,0,0,19,21292,30,0,0,0,0,0,'Shadowmoon Valley Invisible Trigger (Tiny) - OOC no repeat - Cast Ar''tor''s Prison'),
(-171873,0,0,0,1,0,100,1,0,0,0,0,11,36558,0,0,0,0,0,19,21292,30,0,0,0,0,0,'Shadowmoon Valley Invisible Trigger (Tiny) - OOC no repeat - Cast Ar''tor''s Prison'),
(21292,0,0,0,20,0,100,0,10528,0,0,0,45,0,1,0,0,0,0,19,21318,20,0,0,0,0,0, 'Ar''tor, Son of Oronok - -On quest Rewarded - Set Data'),
(21318,0,0,0,38,0,100,0,0,1,0,0,1,0,0,0,0,0,0,21,30,0,0,0,0,0,0, 'Spirit of Ar''tor -On Data set - Talk'),
(21309,0,0,0,0,0,100,0,5000,7000,20000,25000,11,38048,0,0,0,0,0,2,0,0,0,0,0,0,0,"Painmistress Gabrissa - In Combat - Cast 'Curse of Pain'"),
(21309,0,1,0,0,0,100,0,6000,7000,17000,20000,11,38169,0,0,0,0,0,2,0,0,0,0,0,0,0,"Painmistress Gabrissa - In Combat - Cast 'Curse of Pain'"),
(21309,0,2,0,25,0,100,0,0,0,0,0,11,32783,0,0,0,0,0,1,0,0,0,0,0,0,0,"Painmistress Gabrissa - On reset - Cast 'Arcane Channeling'");

-- from Rushor/Spell 
-- Scripts/Spells: Hand of Reins - Questsupport for 'Mounting Up'
DELETE FROM `spell_script_names` WHERE `spell_id`=49285; 
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
(49285,'spell_q12414_hand_over_reins'); 

DELETE FROM `spell_script_names` WHERE `spell_id`=39238; 
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
(39238,'spell_q10929_fumping'); 

-- from Rushor 

DELETE FROM `creature_text` WHERE `entry`=10978; 
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `comment`) VALUES  
(10978, 0, 0, '%s jumps in fright!', 16, 0, 100, 0, 0, 0, 6301, 'Legacki'), 
(10978, 1, 0, 'Ahhhhh!!!', 12, 0, 100, 0, 0, 0, 6302, 'Legacki'), 
(10978, 2, 0, 'You big meanie! Who put you up to this?', 12, 0, 100, 0, 0, 0, 6303, 'Legacki'), 
(10978, 3, 0, 'It was Umi, wasn''t it?! She''s always playing jokes on me, and now she''s got you in on it too!', 12, 0, 100, 0, 0, 0, 6304, 'Legacki'), 
(10978, 4, 0, '%s sighs.', 16, 0, 100, 0, 0, 0, 6305, 'Legacki'); 

DELETE FROM `creature_text` WHERE `entry`=10980; 
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `comment`) VALUES  
(10980, 0, 0, '%s marches around, roaring and making a ruckus.', 16, 0, 100, 0, 0, 0, 6327, 'Umi\'s Mechanical Yeti'), 
(10980, 1, 0, 'RAAAAAAAR!', 12, 0, 100, 0, 0, 0, 6329, 'Umi\'s Mechanical Yeti'); 

DELETE FROM `waypoints` WHERE `entry`=10978; 
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES  
(10978, 1,6713.694,-4682.374,721.6163, 'Legacki'), 
(10978, 2,6731.523,-4675.635,721.2076, 'Legacki'), 
(10978, 3,6736.806,-4672.955,721.9132, 'Legacki'), 
(10978, 4,6749.889,-4662.13,725.0011, 'Legacki'), 
(10978, 5,6750.157,-4661.562,724.9875, 'Legacki'), 
(10978, 6,6732.859,-4641.781,722.8784, 'Legacki'), 
(10978, 7,6727.719,-4641.233,721.6862, 'Legacki'), 
(10978, 8,6715.982,-4643.644,721.1971, 'Legacki'), 
(10978, 9,6719.307,-4652.817,721.231, 'Legacki'), 
(10978, 10,6715.004,-4685.518,721.466, 'Legacki'), 
(10978, 11,6718.75,-4705.675,721.9097, 'Legacki'), 
(10978, 12,6712.263,-4717.947,721.5077, 'Legacki'), 
(10978, 13,6701.636,-4714.284,721.6529, 'Legacki'), 
(10978, 14,6701.108,-4695.846,722.3613, 'Legacki'), 
(10978, 15,6705.608,-4686.181,721.9736, 'Legacki'); 

DELETE FROM `creature_text` WHERE `entry`=11192; 
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `comment`) VALUES  
(11192, 0, 0, "Why flail around when all you need...", 12, 0, 100, 0, 0, 0, 49308, "Kilram\'s Tree"), 
(11192, 1, 0, "...is just one CHOP!", 12, 0, 100, 0, 0, 0, 49309, "Kilram\'s Tree"); 

DELETE FROM `creature_text` WHERE `entry`=11191; 
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `comment`) VALUES  
(11191, 0, 0, 'Watch and weep.', 12, 0, 100, 0, 0, 0, 49258, 'Lilith the Lithe'), 
(11191, 1, 0, 'You see? Nothing beats the crushing power of my hammers.', 12, 0, 100, 0, 0, 0, 49259, 'Lilith the Lithe'); 

update creature_template_addon set bytes1=33554432 where entry=48681; 
UPDATE `creature_template` SET `InhabitType`=4 WHERE  `entry`=48681; 
UPDATE `creature_template` SET `speed_walk`=2.5, `speed_run`=2.5 WHERE  `entry`=48681; 

DELETE FROM `waypoints` WHERE `entry`=4868100; 
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES  
(4868100, 1, 6196.32, -4105.12, 744.028, 'Arcane Roller'), 
(4868100, 2, 6206.79, -4105.92, 739.795, 'Arcane Roller'), 
(4868100, 3, 6217.26, -4106.65, 732.59, 'Arcane Roller'), 
(4868100, 4, 6229.98, -4107.5, 723.776, 'Arcane Roller'), 
(4868100, 5, 6241.76, -4107.84, 722.284, 'Arcane Roller'), 
(4868100, 6, 6251.8, -4107.76, 721.797, 'Arcane Roller'), 
(4868100, 7, 6265.56, -4100.52, 716.464, 'Arcane Roller'), 
(4868100, 8, 6272.71, -4094.95, 713.936, 'Arcane Roller'), 
(4868100, 9, 6277.71, -4084.69, 711.392, 'Arcane Roller'), 
(4868100, 10, 6282.68, -4072.6, 708.661, 'Arcane Roller'), 
(4868100, 11, 6290.79, -4054.63, 704.589, 'Arcane Roller'), 
(4868100, 12, 6298.65, -4047.94, 703.035, 'Arcane Roller'), 
(4868100, 13, 6310.25, -4044.52, 699.736, 'Arcane Roller'), 
(4868100, 14, 6323.37, -4041.15, 697.811, 'Arcane Roller'), 
(4868100, 15, 6345.7, -4034.72, 695.33, 'Arcane Roller'), 
(4868100, 16, 6355.44, -4032.31, 690.346, 'Arcane Roller'), 
(4868100, 17, 6377.85, -4026.08, 664.858, 'Arcane Roller'); 
 
DELETE FROM `waypoints` WHERE `entry`=4868101; 
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES  
(4868101, 1, 6195.35, -4111.85, 744.147, 'Arcane Roller'), 
(4868101, 2, 6203.05, -4111.92, 741.04, 'Arcane Roller'), 
(4868101, 3, 6212.6, -4112.66, 735.066, 'Arcane Roller'), 
(4868101, 4, 6228.86, -4114.14, 723.562, 'Arcane Roller'), 
(4868101, 5, 6240.95, -4113.68, 721.984, 'Arcane Roller'), 
(4868101, 6, 6247.91, -4112.89, 721.482, 'Arcane Roller'), 
(4868101, 7, 6261.13, -4110.28, 718.787, 'Arcane Roller'), 
(4868101, 8, 6274.36, -4103.5, 715.604, 'Arcane Roller'), 
(4868101, 9, 6285.37, -4086.53, 710.668, 'Arcane Roller'), 
(4868101, 10, 6293.89, -4064.3, 703.658, 'Arcane Roller'), 
(4868101, 11, 6303.82, -4052.11, 701.461, 'Arcane Roller'), 
(4868101, 12, 6315.01, -4049.11, 698.762, 'Arcane Roller'), 
(4868101, 13, 6331.43, -4046.85, 697.436, 'Arcane Roller'), 
(4868101, 14, 6354.13, -4042.56, 694.022, 'Arcane Roller'), 
(4868101, 15, 6360.85, -4041.71, 686.905, 'Arcane Roller'), 
(4868101, 16, 6378.82, -4041.17, 664.861, 'Arcane Roller'); 
 
DELETE FROM `waypoints` WHERE `entry`=4868102; 
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES  
(4868102, 1, 6195.2, -4118.27, 743.577, 'Arcane Roller'), 
(4868102, 2, 6202.19, -4118.49, 740.402, 'Arcane Roller'), 
(4868102, 3, 6214.4, -4120.41, 732.631, 'Arcane Roller'), 
(4868102, 4, 6229.96, -4123.08, 723.281, 'Arcane Roller'), 
(4868102, 5, 6241.04, -4121.34, 721.329, 'Arcane Roller'), 
(4868102, 6, 6254.89, -4119.31, 720.073, 'Arcane Roller'), 
(4868102, 7, 6275.18, -4112.21, 716.654, 'Arcane Roller'), 
(4868102, 8, 6286.03, -4103.33, 714.633, 'Arcane Roller'), 
(4868102, 9, 6296.62, -4080.74, 706.334, 'Arcane Roller'), 
(4868102, 10, 6313.36, -4054.73, 698.949, 'Arcane Roller'), 
(4868102, 11, 6344.67, -4053.76, 695.791, 'Arcane Roller'), 
(4868102, 12, 6353.26, -4052.85, 693.859, 'Arcane Roller'), 
(4868102, 13, 6389.22, -4047.54, 658.284, 'Arcane Roller'); 

DELETE FROM `waypoints` WHERE `entry`=48019; 
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES  
(48019, 1, 5181.72, -705.112, 335.698, 'Purged Bloodvenom'), 
(48019, 2, 5166.87, -680.257, 331.131, 'Purged Bloodvenom'); 

DELETE FROM `creature_text` WHERE `entry` IN (47696, 47692); 
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `comment`) VALUES  
(47696, 0, 0, 'Open wide, Mr. Tauren! Here comes the hippogryph into the roost!', 12, 0, 100, 0, 0, 0, 48256, 'Kelnir Leafsong'), 
(47692, 0, 0, 'Urrrrrrgh...', 12, 0, 100, 0, 0, 0, 48254, 'Altsoba Ragetotem'), 
(47692, 1, 0, 'HLORRHGH!', 14, 0, 100, 0, 0, 0, 48255, 'Altsoba Ragetotem'); 

-- Navarax's Gambit 
DELETE FROM `creature_text` WHERE `entry` IN (47842, 48487); 
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextID`, `comment`) VALUES 
(47842, 0, 0, 'Your death will tell a different story!', 14, 0, 100, 0, 0, 0, 48370, 'Arch Druid Navarax to Player'), 
(48487, 0, 0, 'What is going on in here?!', 12, 0, 100, 5, 0, 0, 48691, 'Whisperwind Druid to Player'), 
(48487, 1, 0, 'The Arch Druid... how in the world...?', 12, 0, 100, 274, 0, 0, 48692, 'Whisperwind Druid to Player'), 
(48487, 2, 0, 'I... I must tell the others. You should find Huntress Selura right away.', 12, 0, 100, 1, 0, 0, 48693, 'Whisperwind Druid to Player'); 

DELETE FROM `gossip_menu` WHERE (`entry`=12353 AND `text_id`=17477); 
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES 
(12353, 17477); -- 47923 

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=12398 AND `SourceEntry`=0; 
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(15, 12398, 0, 0, 0, 9, 0, 28264, 0, 0, 0, 0, 0, '', 'Gossip Option requires quest not complete'); 

DELETE FROM `waypoints` WHERE `entry`=48487; 
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES  
(48487, 1, 6053.084473, -927.829712, 455.742828, 'Whisperwind Druid'), 
(48487, 2, 6050.680664, -933.536255, 455.892639, 'Whisperwind Druid'), 
(48487, 3, 6054.942383, -934.681335, 455.893829, 'Whisperwind Druid'); 


 
 

