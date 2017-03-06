
UPDATE creature_template SET faction=35 WHERE entry=29677;

DELETE FROM `creature_text` WHERE `entry`=29677;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextID`, `comment`) VALUES
(29677,0,0,'The %s sniffs the ground to pickup the trail.',16,0,100,0,0,0,30366,'Frosthound to Player'),
(29677,1,0,'You''ve been seen! Use the net and ice slick to keep the dwarves away!',42,0,100,0,0,0,30365,'Frosthound to Player'),
(29677,2,0,'The frosthound has located the thief''s hiding place. Confront him!',42,0,100,377,0,0,30368,'Frosthound to Player'),
(29677,3,0,'The %s has tracked the scent to its source.',16,0,100,377,0,0,30367,'Frosthound to Player');

UPDATE `creature_template` SET `spell1`=54997, `spell2`=54996,`ainame`='SmartAI' WHERE `entry`=29677;

DELETE FROM `smart_scripts` WHERE `entryorguid`=29677 AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=2967700 AND `source_type`=9;

INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(29677,0,0,1,54,0,100,0,0,0,0,0,11,54993,0,0,0,0,0,1,0,0,0,0,0,0,0,'Frosthound - On Just Summoned - Cast Frosthound Periodic'),
(29677,0,1,0,61,0,100,0,0,0,0,0,80,2967700,0,0,0,0,0,1,0,0,0,0,0,0,0,'Frosthound - On Just Summoned - Run Script'),
(29677,0,2,0,7,0,100,0,0,0,0,0,11,54993,0,0,0,0,0,1,0,0,0,0,0,0,0,'Frosthound - On Evade - Cast Frosthound Periodic'),
(29677,0,3,4,40,0,100,0,33,29677,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'Frosthound - On Reached WP33 - Say Line 2'),
(29677,0,4,5,61,0,100,0,0,0,0,0,1,3,0,0,0,0,0,23,0,0,0,0,0,0,0,'Frosthound - On Reached WP33 - Say Line 3'),
(29677,0,5,6,61,0,100,0,0,0,0,0,11,55036,0,0,0,0,0,23,0,0,0,0,0,0,0,'Frosthound - On Reached WP33 - Cast Frosthound Boss Emote 2'),
(29677,0,6,0,61,0,100,0,0,0,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Frosthound - On Reached WP33 - Despawn'),

(2967700,9,0,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Frosthound - Script - Say Line 0'),
(2967700,9,1,0,0,0,100,0,0,0,0,0,11,55026,0,0,0,0,0,1,0,0,0,0,0,0,0,'Frosthound - Script - Cast Frosthound Boss Emote'),
(2967700,9,2,0,0,0,100,0,0,0,0,0,53,1,29677,0,0,0,0,1,0,0,0,0,0,0,0,'Frosthound - Script - Start WP'),
(2967700,9,3,0,0,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Frosthound - Script - Say Line 1');

DELETE FROM `waypoints` WHERE `entry`=29677;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(29677,1,7173.071,-777.0275,899.1846,'Frosthound'),
(29677,2,7182.944,-781.4821,904.6174,'Frosthound'),
(29677,3,7193.046,-787.1729,910.843,'Frosthound'),
(29677,4,7205.287,-793.2994,917.2863,'Frosthound'),
(29677,5,7218.268,-802.1098,921.6022,'Frosthound'),
(29677,6,7230.444,-816.3606,924.8938,'Frosthound'),
(29677,7,7232.167,-834.2318,926.6146,'Frosthound'),
(29677,8,7247.474,-848.1854,925.8355,'Frosthound'),
(29677,9,7263.333,-875.3375,925.127,'Frosthound'),
(29677,10,7275.556,-895.3395,926.4728,'Frosthound'),
(29677,11,7283.682,-922.1505,922.8227,'Frosthound'),
(29677,12,7284.952,-947.7603,918.976,'Frosthound'),
(29677,13,7294.833,-985.7026,915.6023,'Frosthound'),
(29677,14,7291.617,-973.3366,916.3897,'Frosthound'),
(29677,15,7321.158,-1040.365,912.3143,'Frosthound'),
(29677,16,7341.228,-1082.531,906.1441,'Frosthound'),
(29677,17,7355.963,-1127.951,907.6265,'Frosthound'),
(29677,18,7359.741,-1156.937,910.1899,'Frosthound'),
(29677,19,7352.817,-1172.477,912.4103,'Frosthound'),
(29677,20,7340.049,-1188.073,914.7924,'Frosthound'),
(29677,21,7330.804,-1201.472,915.7355,'Frosthound'),
(29677,22,7323.127,-1228.335,909.517,'Frosthound'),
(29677,23,7316.839,-1268.214,902.8563,'Frosthound'),
(29677,24,7316.317,-1300.765,904.0386,'Frosthound'),
(29677,25,7315.278,-1332.342,904.7114,'Frosthound'),
(29677,26,7313.02,-1366.275,907.1307,'Frosthound'),
(29677,27,7312.081,-1399.743,910.574,'Frosthound'),
(29677,28,7312.83,-1434.1,912.8854,'Frosthound'),
(29677,29,7311.606,-1466.343,916.7098,'Frosthound'),
(29677,30,7309.714,-1498.702,921.2195,'Frosthound'),
(29677,31,7306.879,-1531.19,928.3399,'Frosthound'),
(29677,32,7305.797,-1558.925,939.4229,'Frosthound'),
(29677,33,7305.19,-1566.019,941.0005,'Frosthound');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` =1 AND `SourceGroup` =29695 AND `SourceEntry` =40971;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(1,29695,40971,0,0,28,0,12855,0,0,0,0,0,'','Brann\'s Communicator'),
(1,29695,40971,0,0,2,0,40971,1,1,1,0,0,'','Brann\'s Communicator'),
(1,29695,40971,0,1,9,0,12855,0,0,0,0,0,'','Brann\'s Communicator'),
(1,29695,40971,0,1,2,0,40971,1,1,1,0,0,'','Brann\'s Communicator'),
(1,29695,40971,0,2,8,0,12855,0,0,0,0,0,'','Brann\'s Communicator'),
(1,29695,40971,0,2,2,0,40971,1,1,1,0,0,'','Brann\'s Communicator');

UPDATE `creature_loot_template` SET `QuestRequired`=0 WHERE  `Entry`=29695 AND `Item`=40971;

DELETE FROM `creature_template_addon` WHERE `entry`=25383;
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `bytes2`, `auras`) VALUES
(25383, 0, 0x0, 0x1, '45617'); -- 25383 - 45617

DELETE FROM `smart_scripts`  WHERE  `entryorguid`IN(25471,25472,25473) AND `source_type`=0;
UPDATE `creature_template` SET `ainame`='SmartAI', `scriptname`='' WHERE `entry` IN(25471,25472,25473);

DELETE FROM `areatrigger_scripts` WHERE `entry` IN(4857,4858,4860);
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(4857,'SmartTrigger'),
(4858,'SmartTrigger'),
(4860,'SmartTrigger');

DELETE FROM `smart_scripts` WHERE `entryorguid` IN(4857,4858,4860) AND `source_type`=2;
INSERT  INTO `smart_scripts`  (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`)  VALUES
(4857,2,0,1,46,0,100,0,4857,0,0,0,85,45627,2,0,0,0,0,7,0,0,0,0,0,0,0,'Area Trigger 4857 - On Trigger - invoker cast Temple A Credit'),
(4858,2,0,1,46,0,100,0,4858,0,0,0,85,45628,2,0,0,0,0,7,0,0,0,0,0,0,0,'Area Trigger 4858 - On Trigger - invoker cast Temple B Credit'),
(4860,2,0,1,46,0,100,0,4860,0,0,0,85,45629,2,0,0,0,0,7,0,0,0,0,0,0,0,'Area Trigger 4860 - On Trigger - invoker cast Temple C Credit');

UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry` IN(27315,27336);
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`IN(27315,27336);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(27315,0,0,1,8,0,100,0,48363,0,0,0,28,49774,0,0,0,0,0,1,0,0,0,0,0,0,0,'Helpless Wintergarde Villager - on spellhit - Remove Aura'),
(27315,0,1,2,61,0,100,0,0,0,0,0,11,43671,0,0,0,0,0,7,0,0,0,0,0,0,0,'Helpless Wintergarde Villager - on spellhit - mount to invoker'),
(27315,0,2,0,61,0,100,0,0,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'Helpless Wintergarde Villager - on spellhit - set phasemask to 2'),
(27315,0,3,0,1,2,100,1,5000,5000,5000,5000,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Helpless Wintergarde Villager - OOC (Phase 2) - Say text 0'),
(27315,0,4,5,23,2,100,1,43671,0,1000,1000,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Helpless Wintergarde Villager - On Aura Missing - say text'),
(27315,0,5,0,61,2,100,0,0,0,0,0,41,5000,0,0,0,0,0,1,0,0,0,0,0,0,0,'Helpless Wintergarde Villager - On Aura Missing -  despawn after 2 secs'),
(27336,0,0,1,8,0,100,0,48363,0,0,0,28,49774,0,0,0,0,0,1,0,0,0,0,0,0,0,'Helpless Wintergarde Villager - on spellhit - Remove Aura'),
(27336,0,1,2,61,0,100,0,0,0,0,0,11,43671,0,0,0,0,0,7,0,0,0,0,0,0,0,'Helpless Wintergarde Villager - on spellhit - mount to invoker'),
(27336,0,2,0,61,0,100,0,0,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'Helpless Wintergarde Villager - on spellhit - set phasemask to 2'),
(27336,0,3,0,1,2,100,1,5000,5000,5000,5000,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Helpless Wintergarde Villager - OOC (Phase 2) - Say text 0'),
(27336,0,4,5,23,2,100,1,43671,0,1000,1000,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Helpless Wintergarde Villager - On Aura Missing - say text'),
(27336,0,5,0,61,2,100,0,0,0,0,0,41,5000,0,0,0,0,0,1,0,0,0,0,0,0,0,'Helpless Wintergarde Villager - On Aura Missing -  despawn after 2 secs');

/* aura for mount */
DELETE FROM `creature_template_addon` WHERE `entry`=27258;
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(27258, 0, 0, 33554432, 0, 0, '34873');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`IN(13,17) AND `SourceEntry` IN(48397,48363);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(17, 0, 48397, 0, 0, 29, 0, 27315, 5, 1, 0, 0, 0, '', 'Required NPC to cast Spell'),
(17, 0, 48397, 0, 1, 29, 0, 27336, 5, 1, 0, 0, 0, '', 'Required NPC to cast Spell'),
(17, 0, 48397, 0, 0, 30, 0, 300199, 15, 0, 0, 0, 0, '', 'Spell focus for Drop Off Helpless Wintergarde Villager'),
(13, 2, 48397, 0, 0, 31, 0, 4, 0, 0, 0, 0, 0, '', 'Drop Off Villager Effect #2 Targets Player'),
(13, 1, 48363, 0, 0, 31, 0, 3, 27315, 0, 0, 0, 0, '', 'Grab  targets Helpless Wintergarde Villager'),
(17, 0, 48363, 0, 0, 29, 0, 27315, 5, 1, 0, 0, 0, '', 'Required NPC to cast Spell'),
(13, 1, 48363, 0, 1, 31, 0, 3, 27336, 0, 0, 0, 0, '', 'Grab  targets Helpless Wintergarde Villager'),
(17, 0, 48363, 0, 1, 29, 0, 27336, 5, 1, 0, 0, 0, '', 'Required NPC to cast Spell');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=48397;
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES 
(48397, -43671, 0, 'remove npc');

DELETE FROM `creature_text` WHERE `entry` IN(27315,27336);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`,`BroadcastTextID`) VALUES 
(27315, 0, 0, 'Are you sure you know how to fly this thing? Feels a little wobbly.', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26359),
(27315, 0, 1, 'I don\'t mean to sound ungrateful, but could you fly a little closer to the ground? I hate heights!', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26360),
(27315, 0, 2, 'I picked a bad day to stop drinking!', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26345),
(27315, 0, 3, 'I\'m gettin\' a little woozy... Oooooof...', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26364),
(27315, 0, 4, 'You saved my life! Thanks!', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26358),
(27315, 0, 5, 'You are my guardian angel! Like a white knight you flew in from the heavens and lifted me from the pit of damnation!', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26362),
(27315, 1, 0, 'How can I ever repay you for this, friend?', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26363),
(27315, 1, 1, 'HURRAY!', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26382),
(27315, 1, 2, 'Kindness is not lost with this one, Urik. Thank you, hero!', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26383),
(27315, 1, 3, 'My shop\'s doors will always be open to you, friend.', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26385),
(27315, 1, 4, 'Safe at last! Thank you, stranger!', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26381),
(27315, 1, 5, 'Thanks for your help, hero!', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26357),
(27315, 1, 6, 'We made it! We actually made it!', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26384),
(27336, 0, 0, 'Are you sure you know how to fly this thing? Feels a little wobbly.', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26359),
(27336, 0, 1, 'I don\'t mean to sound ungrateful, but could you fly a little closer to the ground? I hate heights!', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26360),
(27336, 0, 2, 'I picked a bad day to stop drinking!', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26345),
(27336, 0, 3, 'I\'m gettin\' a little woozy... Oooooof...', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26364),
(27336, 0, 4, 'You saved my life! Thanks!', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26358),
(27336, 0, 5, 'You are my guardian angel! Like a white knight you flew in from the heavens and lifted me from the pit of damnation!', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26362),
(27336, 1, 0, 'How can I ever repay you for this, friend?', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26363),
(27336, 1, 1, 'HURRAY!', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26382),
(27336, 1, 2, 'Kindness is not lost with this one, Urik. Thank you, hero!', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26383),
(27336, 1, 3, 'My shop\'s doors will always be open to you, friend.', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26385),
(27336, 1, 4, 'Safe at last! Thank you, stranger!', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26381),
(27336, 1, 5, 'Thanks for your help, hero!', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26357),
(27336, 1, 6, 'We made it! We actually made it!', 12, 0, 100, 0, 0, 0, 'Helpless Wintergarde Villager',26384);

UPDATE creature_template_addon SET auras="48361 49774" WHERE entry in (27315, 27336);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=16 AND `SourceEntry`=27258;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(16, 0, 27258, 0, 0, 23, 0, 4188, 0, 0, 0, 0, 0, '', 'Dismount player when not in intended zone'),
(16, 0, 27258, 0, 1, 23, 0, 4177, 0, 0, 0, 0, 0, '', 'Dismount player when not in intended zone'),
(16, 0, 27258, 0, 2, 23, 0, 4178, 0, 0, 0, 0, 0, '', 'Dismount player when not in intended zone');

UPDATE `smart_scripts` SET `target_type`=5, `target_param1`=0 WHERE `entryorguid`=37662 AND `source_type`=0 AND `id`=0;

DELETE FROM `creature_queststarter` WHERE `quest`=14351;
INSERT INTO `creature_queststarter` (`id`, `quest`) VALUES 
(2215, 14351);

UPDATE `quest_template` SET `NextQuestIdChain`=14351 WHERE  `Id`=541;

UPDATE `quest_template` SET `PrevQuestId`=541 WHERE  `Id`=14351;

UPDATE `spell_area` SET `quest_start_status`=74 WHERE  `spell`=57745 AND `area`=4591 AND `quest_start`=13068 AND `aura_spell`=0 AND `racemask`=0 AND `gender`=2;

UPDATE `quest_template` SET `PrevQuestId`=0 WHERE  `Id`=12933;

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` IN(19,20) AND `SourceEntry`=12933;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(19, 0, 12933, 0, 0, 8, 0, 12932, 0, 0, 0, 0, 0, '', 'The Amphitheater of Anguish: Magnataur! after The Amphitheater of Anguish: Yggdras!'),
(20, 0, 12933, 0, 0, 8, 0, 12932, 0, 0, 0, 0, 0, '', 'The Amphitheater of Anguish: Magnataur! after The Amphitheater of Anguish: Yggdras!'),
(19, 0, 12933, 0, 1, 8, 0, 12954, 0, 0, 0, 0, 0, '', 'The Amphitheater of Anguish: Magnataur! after The Amphitheater of Anguish: Yggdras!'),
(20, 0, 12933, 0, 1, 8, 0, 12954, 0, 0, 0, 0, 0, '', 'The Amphitheater of Anguish: Magnataur! after The Amphitheater of Anguish: Yggdras!');

UPDATE `command` SET `help`='Syntax: .titles current #title\r\nSet title #title (id or shift-link) as current selected title for selected player. If title is not in known title list for player then it will be added to list.' WHERE `name`='titles current';

UPDATE `creature_template` SET `mechanic_immune_mask` = `mechanic_immune_mask` |33554432, `flags_extra` = `flags_extra` &~256  WHERE entry IN (10184, 36538);

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`IN(-53017);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(-53017, 48330, 0,'On Indisposed Expiring - Cast Create Amberseeds');

DELETE FROM `smart_scripts` WHERE `entryorguid`=28747 AND `source_type`=0 AND `id`=7;DELETE FROM `smart_scripts` WHERE `entryorguid`=28748 AND `source_type`=0 AND `id`=6;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(28747, 0, 7, 0, 4, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Quetz\'lun Worshipper - On Agro - Store Targetlist"),
(28748, 0, 6, 0, 4, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Serpent-Touched Berserker - On Agro - Store Targetlist");

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = 26560 AND `spell_effect`=18280;
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`)
VALUES (26560, 18280, 0, 'Summon Lord-Commander Arete');

DELETE FROM `disables` WHERE `sourceType`=0 AND `entry`=45323;
INSERT INTO `disables` (`sourceType`, `entry`, `flags`, `params_0`, `params_1`, `comment`) VALUES
(0, 45323, 64, '', '', 'Ignore LOS for Returning Vrykul Artifact');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=1 AND `SourceGroup`=24018 AND `SourceEntry` IN(34090,34091);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(1, 24018, 34090, 0, 0, 8, 0, 11236, 0, 0, 0, 0, 0, '', 'Mezhens Writings drops if player is rewarded for Necro Overlord Mezhen'),
(1, 24018, 34091, 0, 0, 8, 0, 11264, 0, 0, 0, 0, 0, '', 'Mezhens Writings drops if player is rewarded for Necro Overlord Mezhen'),
(1, 24018, 34090, 0, 1, 9, 0, 11236, 0, 0, 0, 0, 0, '', 'Mezhens Writings drops if player has taken Necro Overlord Mezhen'),
(1, 24018, 34091, 0, 1, 9, 0, 11264, 0, 0, 0, 0, 0, '', 'Mezhens Writings drops if player has taken Necro Overlord Mezhen'),
(1, 24018, 34090, 0, 2,28, 0, 11236, 0, 0, 0, 0, 0, '', 'Mezhens Writings drops if player has completed Necro Overlord Mezhen'),
(1, 24018, 34091, 0, 2,28, 0, 11264, 0, 0, 0, 0, 0, '', 'Mezhens Writings drops if player has completed Necro Overlord Mezhen');

SET @VARIDUS := 25618;
SET @GETRY := 25729;
SET @NECROLORD := 25730;
SET @SAURFANG := 25751;

UPDATE `creature_template` SET `ainame`='SmartAI' WHERE `entry`=@SAURFANG;

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@GETRY,@NECROLORD,@SAURFANG) AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@VARIDUS*100 AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@NECROLORD,0,0,0,11,0,100,0,0,0,0,0,53,0,@NECROLORD,0,0,0,0,1,0,0,0,0,0,0,0, 'En''kilah Necrolord - On spawn - Start WP movement'),
(@NECROLORD,0,1,2,40,0,100,0,2,@NECROLORD,0,0,101,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'En''kilah Necrolord - On reached WP1 - Set home position'),
(@NECROLORD,0,2,0,61,0,100,0,0,0,0,0,45,0,4,0,0,0,0,19,@VARIDUS,10,0,0,0,0,0, 'En''kilah Necrolord - On reached WP1 - Set data 0 4 Varidus the Flenser'),
(@NECROLORD,0,3,4,38,0,100,0,5,1,0,0,66,0,0,0,0,0,0,19,@VARIDUS,10,0,0,0,0,0, 'En''kilah Necrolord - On data 0 1 set - Turn to'),
(@NECROLORD,0,4,5,61,0,100,0,0,0,0,0,12,@SAURFANG,1,300000,0,0,0,1,0,0,0,0,0,0,0, 'En''kilah Necrolord - On data 0 1 set - Change entry to High Overlord Saurfang'),
(@NECROLORD,0,5,6,61,0,100,0,0,0,0,0,100,1,0,0,0,0,0,19,@SAURFANG,0,0,0,0,0,0, 'En''kilah Necrolord - On data 0 1 set - Change entry to High Overlord Saurfang'),
(@NECROLORD,0,6,0,61,0,100,0,0,0,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'En''kilah Necrolord - On data 0 1 set - Change entry to High Overlord Saurfang'),
(@SAURFANG,0,0,0,38,0,100,0,5,2,0,0,1,0,2500,0,0,0,0,12,1,0,0,0,0,0,0, 'High Overlord Saurfang - On data 0 2 set - Say line'),
(@SAURFANG,0,1,0,52,0,100,0,0,@SAURFANG,0,0,66,0,0,0,0,0,0,12,1,0,0,0,0,0,0, 'High Overlord Saurfang - On text 0 over - Turn to'),
(@SAURFANG,0,2,0,38,0,100,0,5,3,0,0,1,1,4000,0,0,0,0,12,1,0,0,0,0,0,0, 'High Overlord Saurfang - On data 0 3 set - Say line'),
(@SAURFANG,0,3,0,52,0,100,0,1,@SAURFANG,0,0,66,0,0,0,0,0,0,19,@VARIDUS,10,0,0,0,0,0, 'High Overlord Saurfang - On text 1 over - Turn to'),
(@SAURFANG,0,4,0,38,0,100,0,5,4,0,0,1,2,5000,0,0,0,0,1,0,0,0,0,0,0,0, 'High Overlord Saurfang - On data 0 4 set - Say line'),
(@SAURFANG,0,5,0,52,0,100,0,2,@SAURFANG,0,0,1,3,12000,0,0,0,0,1,0,0,0,0,0,0,0, 'High Overlord Saurfang - On text 2 over - Say line'),
(@SAURFANG,0,6,0,52,0,100,0,3,@SAURFANG,0,0,1,4,0,0,0,0,0,1,0,0,0,0,0,0,0, 'High Overlord Saurfang - On text 3 over - Say line'),
(@SAURFANG,0,7,8,38,0,100,0,1,1,0,0,19,256,0,0,0,0,0,1,0,0,0,0,0,0,0, 'High Overlord Saurfang - On data 1 1 set - Remove unit_flags IMMUNE_TO_NPC'),
(@SAURFANG,0,8,9,61,0,100,0,0,0,0,0,11,45950,0,0,0,0,0,1,0,0,0,0,0,0,0, 'High Overlord Saurfang - On data 1 1 set - Spellcast Saurfang''s Rage'),
(@SAURFANG,0,9,0,61,0,100,0,0,0,0,0,1,5,1000,0,0,0,0,1,0,0,0,0,0,0,0, 'High Overlord Saurfang - On data 1 1 set - Say line'),
(@SAURFANG,0,10,0,52,0,100,0,5,@SAURFANG,0,0,1,6,1000,0,0,0,0,1,0,0,0,0,0,0,0, 'High Overlord Saurfang - On text 5 over - Say line'),
(@SAURFANG,0,11,0,61,0,100,0,0,0,0,0,41,3000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'High Overlord Saurfang - On text 7 over - Despawn after 3 seconds'),
(@SAURFANG,0,12,0,9,0,100,0,0,5,20000,25000,11,41097,0,0,0,0,0,1,0,0,0,0,0,0,0, 'High Overlord Saurfang - On target within 5y - Spellcast Whirlwind'),
(@SAURFANG,0,13,0,0,0,100,0,3000,7000,3000,8000,11,16044,0,0,0,0,0,1,0,0,0,0,0,0,0, 'High Overlord Saurfang - On update IC - Spellcast Cleave'),
(@SAURFANG,0,14,0,0,0,100,0,2000,7000,5000,7000,11,24573,0,0,0,0,0,2,0,0,0,0,0,0,0, 'High Overlord Saurfang - On update IC - Spellcast Mortal Strike'),
(@SAURFANG,0,15,0,9,0,100,0,8,25,5000,5000,11,15749,0,0,0,0,0,2,0,0,0,0,0,0,0, 'High Overlord Saurfang - On target within 8-25y - Spellcast Shield Charge'),
(@SAURFANG,0,16,0,38,0,100,0,5,5,0,0,66,0,0,0,0,0,0,12,1,0,0,0,0,0,0, 'High Overlord Saurfang - On data 0 5 set - Turn to'),
(@SAURFANG,0,17,0,38,0,100,0,1,2,0,0,1,7,3000,0,0,0,0,1,0,0,0,0,0,0,0, 'High Overlord Saurfang - On data 1 2 set - Say line'),
(@SAURFANG,0,18,11,52,0,100,0,7,@SAURFANG,0,0,45,1,4,0,0,0,0,19,@GETRY,20,0,0,0,0,0, 'High Overlord Saurfang - On text 7 over - Set data 1 4 Shadowstalker Getry'),
(@SAURFANG,0,19,0,38,0,100,0,2,2,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'High Overlord Saurfang - On data 2 2 set - Despawn'),
(@VARIDUS*100,9,0,0,0,0,100,0,0,0,0,0,45,5,5,0,0,0,0,19,@NECROLORD,10,0,0,0,0,0, 'Varidus the Flenser script - Set data 0 5 En''kilah Necrolord'),
(@VARIDUS*100,9,1,0,0,0,100,0,0,0,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Varidus the Flenser script - Say line'),
(@VARIDUS*100,9,2,0,0,0,100,0,5000,5000,0,0,1,3,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Varidus the Flenser script - Say line'),
(@VARIDUS*100,9,3,0,0,0,100,0,3000,3000,0,0,1,4,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Varidus the Flenser script - Say line'),
(@VARIDUS*100,9,4,0,0,0,100,0,4000,4000,0,0,1,5,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Varidus the Flenser script - Say line'),
(@VARIDUS*100,9,5,0,0,0,100,0,6000,6000,0,0,66,0,0,0,0,0,0,19,@NECROLORD,10,0,0,0,0,0, 'Varidus the Flenser script - Turn to'),
(@VARIDUS*100,9,6,0,0,0,100,0,1000,1000,0,0,1,6,0,0,0,0,0,12,1,0,0,0,0,0,0, 'Varidus the Flenser script - Say line'),
(@VARIDUS*100,9,7,0,0,0,100,0,6000,6000,0,0,45,5,1,0,0,0,0,19,@NECROLORD,10,0,0,0,0,0, 'Varidus the Flenser script - Set data 0 1 En''kilah Necrolord'),
(@VARIDUS*100,9,8,0,0,0,100,0,1000,1000,0,0,45,5,2,0,0,0,0,19,@SAURFANG,10,0,0,0,0,0, 'Varidus the Flenser script - Set data 0 2 High Overlord Saurfang'),
(@VARIDUS*100,9,9,0,0,0,100,0,1500,1500,0,0,1,7,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Varidus the Flenser script - Say line'),
(@VARIDUS*100,9,10,0,0,0,100,0,2000,2000,0,0,45,5,3,0,0,0,0,19,@SAURFANG,10,0,0,0,0,0, 'Varidus the Flenser script - Set data 0 3 High Overlord Saurfang'),
(@VARIDUS*100,9,11,0,0,0,100,0,5000,5000,0,0,45,5,4,0,0,0,0,19,@SAURFANG,10,0,0,0,0,0, 'Varidus the Flenser script - Set data 0 4 High Overlord Saurfang'),
(@VARIDUS*100,9,12,0,0,0,100,0,13000,13000,0,0,1,8,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Varidus the Flenser script - Say line'),
(@VARIDUS*100,9,13,0,0,0,100,0,10000,10000,0,0,1,9,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Varidus the Flenser script - Say line'),
(@VARIDUS*100,9,14,0,0,0,100,0,2000,2000,0,0,1,10,2000,0,0,0,0,1,0,0,0,0,0,0,0, 'Varidus the Flenser - On text 9 over - Say line'),
(@VARIDUS*100,9,15,0,0,0,100,0,0,0,0,0,11,45949,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Varidus the Flenser script - Spellcast Release Aberration'),
(@VARIDUS*100,9,16,0,0,0,100,0,0,0,0,0,45,1,1,0,0,0,0,19,@GETRY,20,0,0,0,0,0, 'Varidus the Flenser script - Set data 1 1 Shadowstalker Getry'),
(@VARIDUS*100,9,17,0,0,0,100,0,0,0,0,0,45,1,1,0,0,0,0,19,@SAURFANG,20,0,0,0,0,0, 'Varidus the Flenser script - Set data 1 1 Saurfang');

SET @QUEST := 11705;
SET @VARIDUS := 25618;
SET @GETRY := 25729;
SET @NECROLORD := 25730;
SET @SAURFANG := 25751;

DELETE FROM `smart_scripts` WHERE `entryorguid` =@GETRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@GETRY,0,0,1,19,0,100,0,@QUEST,0,0,0,64,1,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Shadowstalker Getry - On quest accept - Store targetlist'),
(@GETRY,0,1,2,61,0,100,0,0,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Shadowstalker Getry - On quest accept - Remove npcflag questgiver'),
(@GETRY,0,2,3,61,0,100,0,0,0,0,0,1,0,3000,0,0,0,0,1,0,0,0,0,0,0,0, 'Shadowstalker Getry - On quest accept - Say line'),
(@GETRY,0,3,4,61,0,100,0,0,0,0,0,11,45924,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Shadowstalker Getry - On quest accept - Spellcast On Getry''s Quest'),
(@GETRY,0,4,5,61,0,100,0,0,0,0,0,11,45924,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Shadowstalker Getry - On quest accept - Spellcast On Getry''s Quest'),
(@GETRY,0,5,0,61,0,100,0,0,0,0,0,45,0,1,0,0,0,0,19,@VARIDUS,50,0,0,0,0,0, 'Shadowstalker Getry - On quest accept - Set data 0 1 Varidus the Flenser'),
(@GETRY,0,6,7,52,0,100,0,0,@GETRY,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Shadowstalker Getry - On text 0 over - Say line'),
(@GETRY,0,7,0,61,0,100,0,0,0,0,0,53,0,@GETRY,0,0,0,0,1,0,0,0,0,0,0,0, 'Shadowstalker Getry - On text 0 over - Start WP'),
(@GETRY,0,8,0,11,0,100,0,0,0,0,0,81,2,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Shadowstalker Getry - On spawn - Set npcflag questgiver'),
(@GETRY,0,9,0,40,0,100,0,8,@GETRY,0,0,11,34189,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Shadowstalker Getry - On WP8 reached - Spellcast Stealth'),
(@GETRY,0,10,11,40,0,100,0,9,@GETRY,0,0,45,0,2,0,0,0,0,19,@VARIDUS,30,0,0,0,0,0, 'Shadowstalker Getry - On WP 9 reached - Set data 0 2 Varidus the Flenser'),
(@GETRY,0,11,0,61,0,100,0,0,0,0,0,100,1,0,0,0,0,0,19,@VARIDUS,30,0,0,0,0,0, 'Shadowstalker Getry - On WP10 reached - Send targetlist to Varidus the Flenser'),
(@GETRY,0,12,13,40,0,100,0,10,@GETRY,0,0,66,0,0,0,0,0,0,19,@VARIDUS,20,0,0,0,0,0, 'Shadowstalker Getry - On WP10 reached - Turn to'),
(@GETRY,0,13,14,61,0,100,0,0,0,0,0,101,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Shadowstalker Getry - On WP10 reached - Set home position'),
(@GETRY,0,14,15,61,0,100,0,0,0,0,0,28,34189,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Shadowstalker Getry - On WP10 reached - Remove aura Stealth'),
(@GETRY,0,15,16,61,0,100,0,0,0,0,0,11,45922,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Shadowstalker Getry - On WP10 reached - Spellcast Shadow Prison'),
(@GETRY,0,16,17,61,0,100,0,0,0,0,0,86,45922,0,12,1,0,0,12,1,0,0,0,0,0,0, 'Shadowstalker Getry - On WP10 reached - Crosscast Shadow Prison'),
(@GETRY,0,17,0,61,0,100,0,0,0,0,0,45,0,3,0,0,0,0,19,@VARIDUS,20,0,0,0,0,0, 'Shadowstalker Getry - On WP10 reached - Set Data 0 3 Varidus the Flenser'),
(@GETRY,0,18,19,38,0,100,0,1,1,0,0,19,768,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Shadowstalker Getry - On data 1 1 set - Remove unit_flags IMMUNE_TO_PC, IMMUNE_TO_NPC'),
(@GETRY,0,19,0,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,19,@VARIDUS,20,0,0,0,0,0, 'Shadowstalker Getry - On data 1 1 set - Start attack'),
(@GETRY,0,20,21,38,0,100,0,1,3,0,0,15,@QUEST,0,0,0,0,0,12,1,0,0,0,0,0,0, 'Shadowstalker Getry - On data 1 3 set - Quest credit'),
(@GETRY,0,21,0,61,0,100,0,0,0,0,0,1,2,5000,0,0,0,0,1,0,0,0,0,0,0,0, 'Shadowstalker Getry - On data 1 3 set - Say line'),
(@GETRY,0,22,0,52,0,100,0,2,@GETRY,0,0,1,3,5000,0,0,0,0,1,0,0,0,0,0,0,0, 'Shadowstalker Getry - On text 2 over - Say line'),
(@GETRY,0,23,0,52,0,100,0,3,@GETRY,0,0,45,1,2,0,0,0,0,19,@SAURFANG,20,0,0,0,0,0, 'Shadowstalker Getry - On text 3 over - Set data 1 2 High Overlord Saurfang'),
(@GETRY,0,24,0,38,0,100,0,1,4,0,0,53,0,@GETRY*100,0,0,0,0,1,0,0,0,0,0,0,0, 'Shadowstalker Getry - On data 1 4 set - Start WP movement'),
(@GETRY,0,26,27,40,0,100,0,10,@GETRY*100,0,0,81,2,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Shadowstalker Getry - On WP10 reached (Return) - Set npcflag questgiver'),
(@GETRY,0,27,28,61,0,100,0,0,0,0,0,18,768,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Shadowstalker Getry - On WP10 reached (Return) - Set unit_flags IMMUNE_TO_PC, IMMUNE_TO_NPC'),
(@GETRY,0,28,0,61,0,100,0,0,0,0,0,101,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Shadowstalker Getry - On WP10 reached (Return) - Set homeposition'),
(@GETRY,0,29,30,8,0,100,0,45950,0,0,0,28,45922,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Shadowstalker Getry - On spellhit Saurfangs Rage - Remove aura Shadow Prison'),
(@GETRY,0,30,0,61,0,100,0,0,0,0,0,28,45922,0,0,0,0,0,12,1,0,0,0,0,0,0, 'Shadowstalker Getry - On spellhit Saurfangs Rage - Remove aura Shadow Prison'),
(@GETRY,0,31,32,6,0,100,0,0,0,0,0,6,@QUEST,0,0,0,0,0,12,1,0,0,0,0,0,0, 'Shadowstalker Getry - On Death - Fail Quest'),
(@GETRY,0,32,33,61,0,100,0,0,0,0,0,45,2,2,0,0,0,0,19,@VARIDUS,0,0,0,0,0,0, 'Shadowstalker Getry - On Death - Set Data 2 2 Varidus'),
(@GETRY,0,33,34,61,0,100,0,0,0,0,0,45,2,2,0,0,0,0,19,@NECROLORD,0,0,0,0,0,0, 'Shadowstalker Getry - On Death - Set Data 2 2 Varidus'),
(@GETRY,0,34,0,61,0,100,0,0,0,0,0,45,2,2,0,0,0,0,19,@SAURFANG,0,0,0,0,0,0, 'Shadowstalker Getry - On Death - Set Data 2 2 Varidus');

UPDATE `creature_template` SET `unit_class`=4,`speed_walk`=8,`speed_run`=2.85714 WHERE `entry` IN (30161,31752); -- Wyrmrest Skytalon

UPDATE  creature_template  SET  Unit_class  = 4 WHERE  entry  = 30645;

UPDATE `creature_template` SET `faction`=35,`unit_flags`=0 WHERE `entry` IN 
(33562,33559,33558,33564,33561,33382,33383,33384,33306,33285,33739,33738,33747,33743,33740,33746,33748,33744,33745,33749);

-- Darnassus Champion
UPDATE `creature_template` SET `gossip_menu_id`=10453 WHERE `entry`=33738;
-- Exodar Champion
UPDATE `creature_template` SET `gossip_menu_id`=10454 WHERE `entry`=33739;
-- Gnomeregan Champion
UPDATE `creature_template` SET `gossip_menu_id`=10455 WHERE `entry`=33740;
-- Ironforge Champion
UPDATE `creature_template` SET `gossip_menu_id`=10456 WHERE `entry`=33743;
-- Orgrimmar Champion
UPDATE `creature_template` SET `gossip_menu_id`=10457 WHERE `entry`=33744;
-- Sen'jin Champion
UPDATE `creature_template` SET `gossip_menu_id`=10458 WHERE `entry`=33745;
-- Silvermoon Champion
UPDATE `creature_template` SET `gossip_menu_id`=10459 WHERE `entry`=33746;
-- Stormwind Champion
UPDATE `creature_template` SET `gossip_menu_id`=10460 WHERE `entry`=33747;
-- Thunder Bluff Champion
UPDATE `creature_template` SET `gossip_menu_id`=10461 WHERE `entry`=33748;
-- Undercity Champion
UPDATE `creature_template` SET `gossip_menu_id`=10462 WHERE `entry`=33749;
-- Darnassus Valiant
UPDATE `creature_template` SET `gossip_menu_id`=10464 WHERE `entry`=33559;
-- Exodar Valiant
UPDATE `creature_template` SET `gossip_menu_id`=10465 WHERE `entry`=33562;
-- Gnomeregan Valiant
UPDATE `creature_template` SET `gossip_menu_id`=10466 WHERE `entry`=33558;
-- Ironforge Valiant
UPDATE `creature_template` SET `gossip_menu_id`=10467 WHERE `entry`=33564;
-- Orgrimmar Valiant
UPDATE `creature_template` SET `gossip_menu_id`=10468 WHERE `entry`=33306;
-- Sen'jin Valiant
UPDATE `creature_template` SET `gossip_menu_id`=10469 WHERE `entry`=33285;
-- Silvermoon Valiant
UPDATE `creature_template` SET `gossip_menu_id`=10470 WHERE `entry`=33382;
-- Stormwind Valiant
UPDATE `creature_template` SET `gossip_menu_id`=10471 WHERE `entry`=33561;
-- Thunder Bluff Valiant
UPDATE `creature_template` SET `gossip_menu_id`=10472 WHERE `entry`=33383;
-- Undercity Valiant
UPDATE `creature_template` SET `gossip_menu_id`=10473 WHERE `entry`=33384;

DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (10453,10454,10455,10456,10457,10458,10459,10460,10461,10462,10464,10465,10466,10467,10468,10469,10470,10471,10472,10473);
INSERT INTO `gossip_menu_option` (`menu_id`,`id`,`option_icon`,`option_text`,`OptionBroadcastTextID`,`option_id`,`npc_option_npcflag`,`action_menu_id`,`action_poi_id`,`box_coded`,`box_money`,`box_text`,`BoxBroadcastTextID`) VALUES 
(10469, 0, 0, 'I am ready to fight!', 33430, 1, 1, 0, 0, 0, 0, '', 0),
(10468, 0, 0, 'I am ready to fight!', 33430, 1, 1, 0, 0, 0, 0, '', 0),
(10470, 0, 0, 'I am ready to fight!', 33430, 1, 1, 0, 0, 0, 0, '', 0),
(10472, 0, 0, 'I am ready to fight!', 33430, 1, 1, 0, 0, 0, 0, '', 0),
(10473, 0, 0, 'I am ready to fight!', 33430, 1, 1, 0, 0, 0, 0, '', 0),
(10466, 0, 0, 'I am ready to fight!', 33430, 1, 1, 0, 0, 0, 0, '', 0),
(10464, 0, 0, 'I am ready to fight!', 33430, 1, 1, 0, 0, 0, 0, '', 0),
(10471, 0, 0, 'I am ready to fight!', 33430, 1, 1, 0, 0, 0, 0, '', 0),
(10465, 0, 0, 'I am ready to fight!', 33430, 1, 1, 0, 0, 0, 0, '', 0),
(10467, 0, 0, 'I am ready to fight!', 33430, 1, 1, 0, 0, 0, 0, '', 0),
(10453, 0, 0, 'I am ready to fight!', 33430, 1, 1, 0, 0, 0, 0, '', 0),
(10454, 0, 0, 'I am ready to fight!', 33430, 1, 1, 0, 0, 0, 0, '', 0),
(10455, 0, 0, 'I am ready to fight!', 33430, 1, 1, 0, 0, 0, 0, '', 0),
(10456, 0, 0, 'I am ready to fight!', 33430, 1, 1, 0, 0, 0, 0, '', 0),
(10457, 0, 0, 'I am ready to fight!', 33430, 1, 1, 0, 0, 0, 0, '', 0),
(10458, 0, 0, 'I am ready to fight!', 33430, 1, 1, 0, 0, 0, 0, '', 0),
(10459, 0, 0, 'I am ready to fight!', 33430, 1, 1, 0, 0, 0, 0, '', 0),
(10460, 0, 0, 'I am ready to fight!', 33430, 1, 1, 0, 0, 0, 0, '', 0),
(10461, 0, 0, 'I am ready to fight!', 33430, 1, 1, 0, 0, 0, 0, '', 0),
(10462, 0, 0, 'I am ready to fight!', 33430, 1, 1, 0, 0, 0, 0, '', 0);

-- Champions
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup` IN (10453,10454,10455,10456,10457,10458,10459,10460,10461,10462);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorType`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES 
(15, 10453, 0, 0, 0, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Darnassus Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10453, 0, 0, 0, 9, 0, 13793, 0, 0, 0, 0, 0, '', 'Darnassus Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10453, 0, 0, 0, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Darnassus Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10453, 0, 0, 1, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Darnassus Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10453, 0, 0, 1, 9, 0, 13790, 0, 0, 0, 0, 0, '', 'Darnassus Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10453, 0, 0, 1, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Darnassus Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10453, 0, 0, 2, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Darnassus Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10453, 0, 0, 2, 9, 0, 13814, 0, 0, 0, 0, 0, '', 'Darnassus Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10453, 0, 0, 2, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Darnassus Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10453, 0, 0, 3, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Darnassus Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10453, 0, 0, 3, 9, 0, 13811, 0, 0, 0, 0, 0, '', 'Darnassus Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10453, 0, 0, 3, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Darnassus Champion - Show gossip option only if player has aura Player On Tournament Mount'),
--
(15, 10454, 0, 0, 0, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Exodar Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10454, 0, 0, 0, 9, 0, 13793, 0, 0, 0, 0, 0, '', 'Exodar Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10454, 0, 0, 0, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Exodar Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10454, 0, 0, 1, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Exodar Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10454, 0, 0, 1, 9, 0, 13790, 0, 0, 0, 0, 0, '', 'Exodar Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10454, 0, 0, 1, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Exodar Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10454, 0, 0, 2, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Exodar Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10454, 0, 0, 2, 9, 0, 13814, 0, 0, 0, 0, 0, '', 'Exodar Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10454, 0, 0, 2, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Exodar Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10454, 0, 0, 3, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Exodar Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10454, 0, 0, 3, 9, 0, 13811, 0, 0, 0, 0, 0, '', 'Exodar Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10454, 0, 0, 3, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Exodar Champion - Show gossip option only if player has aura Player On Tournament Mount'),
--
(15, 10455, 0, 0, 0, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Gnomeregan Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10455, 0, 0, 0, 9, 0, 13793, 0, 0, 0, 0, 0, '', 'Gnomeregan Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10455, 0, 0, 0, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Gnomeregan Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10455, 0, 0, 1, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Gnomeregan Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10455, 0, 0, 1, 9, 0, 13790, 0, 0, 0, 0, 0, '', 'Gnomeregan Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10455, 0, 0, 1, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Gnomeregan Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10455, 0, 0, 2, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Gnomeregan Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10455, 0, 0, 2, 9, 0, 13814, 0, 0, 0, 0, 0, '', 'Gnomeregan Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10455, 0, 0, 2, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Gnomeregan Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10455, 0, 0, 3, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Gnomeregan Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10455, 0, 0, 3, 9, 0, 13811, 0, 0, 0, 0, 0, '', 'Gnomeregan Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10455, 0, 0, 3, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Gnomeregan Champion - Show gossip option only if player has aura Player On Tournament Mount'),
--
(15, 10456, 0, 0, 0, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Ironforge Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10456, 0, 0, 0, 9, 0, 13793, 0, 0, 0, 0, 0, '', 'Ironforge Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10456, 0, 0, 0, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Ironforge Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10456, 0, 0, 1, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Ironforge Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10456, 0, 0, 1, 9, 0, 13790, 0, 0, 0, 0, 0, '', 'Ironforge Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10456, 0, 0, 1, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Ironforge Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10456, 0, 0, 2, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Ironforge Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10456, 0, 0, 2, 9, 0, 13814, 0, 0, 0, 0, 0, '', 'Ironforge Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10456, 0, 0, 2, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Ironforge Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10456, 0, 0, 3, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Ironforge Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10456, 0, 0, 3, 9, 0, 13811, 0, 0, 0, 0, 0, '', 'Ironforge Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10456, 0, 0, 3, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Ironforge Champion - Show gossip option only if player has aura Player On Tournament Mount'),
--
(15, 10457, 0, 0, 0, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Orgrimmar Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10457, 0, 0, 0, 9, 0, 13793, 0, 0, 0, 0, 0, '', 'Orgrimmar Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10457, 0, 0, 0, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Orgrimmar Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10457, 0, 0, 1, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Orgrimmar Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10457, 0, 0, 1, 9, 0, 13790, 0, 0, 0, 0, 0, '', 'Orgrimmar Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10457, 0, 0, 1, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Orgrimmar Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10457, 0, 0, 2, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Orgrimmar Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10457, 0, 0, 2, 9, 0, 13814, 0, 0, 0, 0, 0, '', 'Orgrimmar Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10457, 0, 0, 2, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Orgrimmar Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10457, 0, 0, 3, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Orgrimmar Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10457, 0, 0, 3, 9, 0, 13811, 0, 0, 0, 0, 0, '', 'Orgrimmar Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10457, 0, 0, 3, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Orgrimmar Champion - Show gossip option only if player has aura Player On Tournament Mount'),
--
(15, 10458, 0, 0, 0, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Sen''jin Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10458, 0, 0, 0, 9, 0, 13793, 0, 0, 0, 0, 0, '', 'Sen''jin Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10458, 0, 0, 0, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Sen''jin Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10458, 0, 0, 1, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Sen''jin Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10458, 0, 0, 1, 9, 0, 13790, 0, 0, 0, 0, 0, '', 'Sen''jin Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10458, 0, 0, 1, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Sen''jin Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10458, 0, 0, 2, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Sen''jin Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10458, 0, 0, 2, 9, 0, 13814, 0, 0, 0, 0, 0, '', 'Sen''jin Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10458, 0, 0, 2, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Sen''jin Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10458, 0, 0, 3, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Sen''jin Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10458, 0, 0, 3, 9, 0, 13811, 0, 0, 0, 0, 0, '', 'Sen''jin Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10458, 0, 0, 3, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Sen''jin Champion - Show gossip option only if player has aura Player On Tournament Mount'),
--
(15, 10459, 0, 0, 0, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Silvermoon Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10459, 0, 0, 0, 9, 0, 13793, 0, 0, 0, 0, 0, '', 'Silvermoon Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10459, 0, 0, 0, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Silvermoon Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10459, 0, 0, 1, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Silvermoon Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10459, 0, 0, 1, 9, 0, 13790, 0, 0, 0, 0, 0, '', 'Silvermoon Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10459, 0, 0, 1, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Silvermoon Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10459, 0, 0, 2, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Silvermoon Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10459, 0, 0, 2, 9, 0, 13814, 0, 0, 0, 0, 0, '', 'Silvermoon Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10459, 0, 0, 2, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Silvermoon Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10459, 0, 0, 3, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Silvermoon Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10459, 0, 0, 3, 9, 0, 13811, 0, 0, 0, 0, 0, '', 'Silvermoon Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10459, 0, 0, 3, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Silvermoon Champion - Show gossip option only if player has aura Player On Tournament Mount'),
--
(15, 10460, 0, 0, 0, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Stormwind Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10460, 0, 0, 0, 9, 0, 13793, 0, 0, 0, 0, 0, '', 'Stormwind Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10460, 0, 0, 0, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Stormwind Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10460, 0, 0, 1, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Stormwind Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10460, 0, 0, 1, 9, 0, 13790, 0, 0, 0, 0, 0, '', 'Stormwind Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10460, 0, 0, 1, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Stormwind Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10460, 0, 0, 2, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Stormwind Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10460, 0, 0, 2, 9, 0, 13814, 0, 0, 0, 0, 0, '', 'Stormwind Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10460, 0, 0, 2, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Stormwind Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10460, 0, 0, 3, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Stormwind Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10460, 0, 0, 3, 9, 0, 13811, 0, 0, 0, 0, 0, '', 'Stormwind Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10460, 0, 0, 3, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Stormwind Champion - Show gossip option only if player has aura Player On Tournament Mount'),
--
(15, 10461, 0, 0, 0, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Thunder Bluff Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10461, 0, 0, 0, 9, 0, 13793, 0, 0, 0, 0, 0, '', 'Thunder Bluff Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10461, 0, 0, 0, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Thunder Bluff Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10461, 0, 0, 1, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Thunder Bluff Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10461, 0, 0, 1, 9, 0, 13790, 0, 0, 0, 0, 0, '', 'Thunder Bluff Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10461, 0, 0, 1, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Thunder Bluff Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10461, 0, 0, 2, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Thunder Bluff Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10461, 0, 0, 2, 9, 0, 13814, 0, 0, 0, 0, 0, '', 'Thunder Bluff Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10461, 0, 0, 2, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Thunder Bluff Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10461, 0, 0, 3, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Thunder Bluff Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10461, 0, 0, 3, 9, 0, 13811, 0, 0, 0, 0, 0, '', 'Thunder Bluff Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10461, 0, 0, 3, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Thunder Bluff Champion - Show gossip option only if player has aura Player On Tournament Mount'),
--
(15, 10462, 0, 0, 0, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Undercity Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10462, 0, 0, 0, 9, 0, 13793, 0, 0, 0, 0, 0, '', 'Undercity Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10462, 0, 0, 0, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Undercity Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10462, 0, 0, 1, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Undercity Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10462, 0, 0, 1, 9, 0, 13790, 0, 0, 0, 0, 0, '', 'Undercity Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10462, 0, 0, 1, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Undercity Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10462, 0, 0, 2, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Undercity Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10462, 0, 0, 2, 9, 0, 13814, 0, 0, 0, 0, 0, '', 'Undercity Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10462, 0, 0, 2, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Undercity Champion - Show gossip option only if player has aura Player On Tournament Mount'),
(15, 10462, 0, 0, 3, 2, 0, 45500, 4, 1, 1, 0, 0, '', 'Undercity Champion - Show gossip option only if player does not have 4 Mark of the Champion'),
(15, 10462, 0, 0, 3, 9, 0, 13811, 0, 0, 0, 0, 0, '', 'Undercity Champion - Show gossip option only if player has taken quest Among the Champions'),
(15, 10462, 0, 0, 3, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Undercity Champion - Show gossip option only if player has aura Player On Tournament Mount');

-- Valiants
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup` IN (10464,10465,10466,10467,10468,10469,10470,10471,10472,10473);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorType`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES 
(15, 10464, 0, 0, 0, 2, 0, 45127, 3, 1, 1, 0, 0, '', 'Darnassus Valiant - Show gossip option only if player does not have 4 Mark of the Valiant'),
(15, 10464, 0, 0, 0, 9, 0, 13761, 0, 0, 0, 0, 0, '', 'Darnassus Valiant - Show gossip option only if player has taken quest The Grand Melee'),
(15, 10464, 0, 0, 0, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Darnassus Valiant - Show gossip option only if player has aura Player On Tournament Mount'),
--
(15, 10465, 0, 0, 0, 2, 0, 45127, 3, 1, 1, 0, 0, '', 'Exodar Valiant - Show gossip option only if player does not have 4 Mark of the Valiant'),
(15, 10465, 0, 0, 0, 9, 0, 13756, 0, 0, 0, 0, 0, '', 'Exodar Valiant - Show gossip option only if player has taken quest The Grand Melee'),
(15, 10465, 0, 0, 0, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Exodar Valiant - Show gossip option only if player has aura Player On Tournament Mount'),
--
(15, 10466, 0, 0, 0, 2, 0, 45127, 3, 1, 1, 0, 0, '', 'Gnomeregan Valiant - Show gossip option only if player does not have 4 Mark of the Valiant'),
(15, 10466, 0, 0, 0, 9, 0, 13750, 0, 0, 0, 0, 0, '', 'Gnomeregan Valiant - Show gossip option only if player has taken quest The Grand Melee'),
(15, 10466, 0, 0, 0, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Gnomeregan Valiant - Show gossip option only if player has aura Player On Tournament Mount'),
--
(15, 10467, 0, 0, 0, 2, 0, 45127, 3, 1, 1, 0, 0, '', 'Ironforge Valiant - Show gossip option only if player does not have 4 Mark of the Valiant'),
(15, 10467, 0, 0, 0, 9, 0, 13745, 0, 0, 0, 0, 0, '', 'Ironforge Valiant - Show gossip option only if player has taken quest The Grand Melee'),
(15, 10467, 0, 0, 0, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Ironforge Valiant - Show gossip option only if player has aura Player On Tournament Mount'),
--
(15, 10468, 0, 0, 0, 2, 0, 45127, 3, 1, 1, 0, 0, '', 'Orgrimmar Valiant - Show gossip option only if player does not have 4 Mark of the Valiant'),
(15, 10468, 0, 0, 0, 9, 0, 13767, 0, 0, 0, 0, 0, '', 'Orgrimmar Valiant - Show gossip option only if player has taken quest The Grand Melee'),
(15, 10468, 0, 0, 0, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Orgrimmar Valiant - Show gossip option only if player has aura Player On Tournament Mount'),
--
(15, 10469, 0, 0, 0, 2, 0, 45127, 3, 1, 1, 0, 0, '', 'Sen''jin Valiant - Show gossip option only if player does not have 4 Mark of the Valiant'),
(15, 10469, 0, 0, 0, 9, 0, 13772, 0, 0, 0, 0, 0, '', 'Sen''jin Valiant - Show gossip option only if player has taken quest The Grand Melee'),
(15, 10469, 0, 0, 0, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Sen''jin Valiant - Show gossip option only if player has aura Player On Tournament Mount'),
--
(15, 10470, 0, 0, 0, 2, 0, 45127, 3, 1, 1, 0, 0, '', 'Silvermoon Valiant - Show gossip option only if player does not have 4 Mark of the Valiant'),
(15, 10470, 0, 0, 0, 9, 0, 13787, 0, 0, 0, 0, 0, '', 'Silvermoon Valiant - Show gossip option only if player has taken quest The Grand Melee'),
(15, 10470, 0, 0, 0, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Silvermoon Valiant - Show gossip option only if player has aura Player On Tournament Mount'),
--
(15, 10471, 0, 0, 0, 2, 0, 45127, 3, 1, 1, 0, 0, '', 'Stormwind Valiant - Show gossip option only if player does not have 4 Mark of the Valiant'),
(15, 10471, 0, 0, 0, 9, 0, 13665, 0, 0, 0, 0, 0, '', 'Stormwind Valiant - Show gossip option only if player has taken quest The Grand Melee'),
(15, 10471, 0, 0, 0, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Stormwind Valiant - Show gossip option only if player has aura Player On Tournament Mount'),
--
(15, 10472, 0, 0, 0, 2, 0, 45127, 3, 1, 1, 0, 0, '', 'Thunder Bluff Valiant - Show gossip option only if player does not have 4 Mark of the Valiant'),
(15, 10472, 0, 0, 0, 9, 0, 13777, 0, 0, 0, 0, 0, '', 'Thunder Bluff Valiant - Show gossip option only if player has taken quest The Grand Melee'),
(15, 10472, 0, 0, 0, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Thunder Bluff Valiant - Show gossip option only if player has aura Player On Tournament Mount'),
--
(15, 10473, 0, 0, 0, 2, 0, 45127, 3, 1, 1, 0, 0, '', 'Undercity Valiant - Show gossip option only if player does not have 4 Mark of the Valiant'),
(15, 10473, 0, 0, 0, 9, 0, 13782, 0, 0, 0, 0, 0, '', 'Undercity Valiant - Show gossip option only if player has taken quest The Grand Melee'),
(15, 10473, 0, 0, 0, 1, 0, 63034, 0, 0, 0, 0, 0, '', 'Undercity Valiant - Show gossip option only if player has aura Player On Tournament Mount');

delete from conditions where SourceTypeOrReferenceId=15 and SourceGroup=10389;
insert into conditions values
(15, 10389, 1, 0, 0, 13, 1, 20, 2, 0, 0, 0, 0, "", "Show options for gossip only if 2 Collossus death"),
(15, 10389, 3, 0, 0, 13, 1, 0, 3, 2, 0, 0, 0, "", "Show options for gossip only if BOSS_LEVIATHAN done"),
(15, 10389, 4, 0, 0, 13, 1, 3, 3, 2, 0, 0, 0, "", "Show options for gossip only if BOSS_XT002 done"),
(15, 10389, 5, 0, 0, 13, 1, 3, 3, 2, 0, 0, 0, "", "Show options for gossip only if BOSS_XT002 done"),
(15, 10389, 6, 0, 0, 13, 1, 5, 3, 2, 0, 0, 0, "", "Show options for gossip only if BOSS_KOLOGARN done"),
(15, 10389, 12, 0, 0, 13, 1, 5, 3, 2, 0, 0, 0, "", "Show options for gossip only if BOSS_KOLOGARN done"),
(15, 10389, 10, 0, 0, 13, 1, 6, 3, 2, 0, 0, 0, "", "Show options for gossip only if BOSS_AURIAYA done"),
(15, 10389, 15, 0, 0, 13, 1, 11, 3, 2, 0, 0, 0, "", "Show options for gossip only if BOSS_VEZAX done");

-- Achievement: Now Were Cookin
DELETE FROM `achievement_criteria_data` WHERE `criteria_id` IN (11118,11119,11120,11121,11122,11123,11124,11125,11126,11127);
INSERT INTO `achievement_criteria_data` (`criteria_id`, `type`, `value1`, `value2`) VALUES
-- Alliance
(11118, 16, 404, 0), -- Now Were Cookin / Cranberry Chutney
(11119, 16, 404, 0), -- Now Were Cookin / Candied Sweet Potato
(11120, 16, 404, 0), -- Now Were Cookin / Pumpkin Pie
(11121, 16, 404, 0), -- Now Were Cookin / Slow-Roasted Turkey
(11122, 16, 404, 0), -- Now Were Cookin / Spice Bread Stuffing
-- Horde
(11123, 16, 404, 0), -- Now Were Cookin / Candied Sweet Potato
(11124, 16, 404, 0), -- Now Were Cookin / Cranberry Chutney
(11125, 16, 404, 0), -- Now Were Cookin / Pumpkin Pie
(11126, 16, 404, 0), -- Now Were Cookin / Slow-Roasted Turkey
(11127, 16, 404, 0); -- Now Were Cookin / Spice Bread Stuffing

UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=20899;

UPDATE `creature_template` SET `ainame`='SmartAI' WHERE `entry`IN(25335,25336,25338,25359);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (25335,25336,25338,25359) AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (2533500,2533501,2533600) AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(25335,0,0,1,19,0,100,0,11592,0,0,0,64,1,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Longrunner Proudhoof - On Quest Accept (We Strike!) - Store Targetlist'),
(25335,0,1,0,61,0,100,0,0,0,0,0,80,2533500,2,0,0,0,0,1,0,0,0,0,0,0,0, 'Longrunner Proudhoof - On Quest Accept (We Strike!) - Run Script'),
(25335,0,2,3,6,0,100,0,0,0,0,0,6,11592,0,0,0,0,0,12,1,0,0,0,0,0,0, 'Longrunner Proudhoof - On Death - Fail Quest (We Strike)'),
(25335,0,3,4,61,0,100,0,0,0,0,0,45,3,3,0,0,0,0,19,25336,0,0,0,0,0,0, 'Longrunner Proudhoof - On Death - Set Data to Grunt Ragefist'),
(25335,0,4,0,61,0,100,0,0,0,0,0,45,3,3,0,0,0,0,9,25338,0,200,0,0,0,0, 'Longrunner Proudhoof - On Death - Set Data to Warsong Caravan Guard'),
(25335,0,5,0,40,0,100,0,0,0,0,0,101,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Longrunner Proudhoof - On Reached WP - Set Home Position'),
(25335,0,6,7,61,0,100,0,0,0,0,0,45,4,4,0,0,0,0,19,25336,0,0,0,0,0,0, 'Longrunner Proudhoof - On Reached WP - Set Data to Grunt Ragefist'),
(25335,0,7,0,61,0,100,0,0,0,0,0,45,4,4,0,0,0,0,9,25338,0,200,0,0,0,0, 'Longrunner Proudhoof - On Reached WP - Set Data to Warsong Caravan Guard'),
(25335,0,8,9,40,0,100,1,9,0,0,0,54,5000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Longrunner Proudhoof - On Reached WP9 - Pause WP for 5 Seconds'),
(25335,0,9,0,61,0,100,0,0,0,0,0,1,2,0,0,0,0,0,12,1,0,0,0,0,0,0, 'Longrunner Proudhoof - On Reached WP9 - Say Line 2'),
(25335,0,10,0,61,0,100,0,9,0,0,0,107,1,1,0,0,0,0,1,0,0,0,0,0,0,0, 'Longrunner Proudhoof - On Reached WP9 - Summon Group 1'),
(25335,0,11,0,40,0,100,1,10,0,0,0,1,3,0,0,0,0,0,12,1,0,0,0,0,0,0, 'Longrunner Proudhoof - On Reached WP10 - Say Line 3'),
(25335,0,12,13,40,0,100,1,13,0,0,0,1,4,0,0,0,0,0,12,1,0,0,0,0,0,0, 'Longrunner Proudhoof - On Reached WP13 - Say Line 4'),
(25335,0,13,14,61,0,100,0,0,0,0,0,101,0,0,0,0,0,0,1,0,0,0,0, 0, 0,0, 'Longrunner Proudhoof - On Reached WP13 - Set Home Position'),
(25335,0,14,0,61,0,100,0,0,0,0,0,12,25359,1,100000,0,0,0,8,0,0,0,3879.794, 5719.112, 66.50308,1.048136, 'Longrunner Proudhoof - On Reached WP13 - Summon '),
(25335,0,15,0,38,0,100,0,5,5,0,0,80,2533501,2,0,0,0,0,1,0,0,0,0,0,0,0, 'Longrunner Proudhoof - On Data Set 5 5 - Run Script 2'),
(25335,0,16,0,11,0,100,0,0,0,0,0,78,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Longrunner Proudhoof - On Respawn - Reset Scripts '),
(25336,0,0,0,38,0,100,0,1,1,0,0,80,2533600,2,0,0,0,0,1,0,0,0,0,0,0,0, 'Grunt Ragefist - On Data Set 1 1 - Run Script'),
(25336,0,1,2,38,0,100,0,2,2,0,0,59,1,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Grunt Ragefist - On Data Set 2 2 - Set Run on'),
(25336,0,2,0,61,0,100,0,0,0,0,0,29,2,3,0,0,0,0,19,25335,0,0,0,0,0,0, 'Grunt Ragefist - On Data Set 2 2 - Follow Longrunner Proudhoof'),
(25336,0,3,0,38,0,100,0,3,3,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Grunt Ragefist - On Data Set 3 3 - Despawn'),
(25336,0,4,0,38,0,100,0,4,4,0,0,101,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Grunt Ragefist - On Data Set 4 4 - Set Home Position'),
(25336,0,5,0,1,0,100,0,0,0,2000,2000,101,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Grunt Ragefist - OOC - Set Home Position'),
(25338,0,0,1,38,0,100,0,1,1,0,0,2,232,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Warsong Caravan Guard - On Data Set 1 1 - Set Faction'),
(25338,0,1,2,61,0,100,0,0,0,0,0,8,2,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Warsong Caravan Guard - On Data Set 1 1 - Set Hostile'),
(25338,0,2,0,61,0,100,0,0,0,0,0,102,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Warsong Caravan Guard - On Data Set 1 1 - Switch HP Regen off'),
(25338,0,3,4,38,0,100,0,2,2,0,0,59,1,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Warsong Caravan Guard - On Data Set 2 2 - Set Run on'),
(25338,0,4,0,61,0,100,0,0,0,0,0,29,1,2,0,0,0,0,19,25335,0,0,0,0,0,0, 'Warsong Caravan Guard - On Data Set 2 2 - Follow Longrunner Proudhoof'),
(25338,0,5,0,38,0,100,0,3,3,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Warsong Caravan Guard - On Data Set 3 3 - Despawn'),
(25338,0,6,0,38,0,100,0,4,4,0,0,101,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Warsong Caravan Guard - On Data Set 4 4 - Set Home Position'),
(25338,0,7,0,1,0,100,0,0,0,2000,2000,101,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Warsong Caravan Guard - OOC - Set Home Position'),

(25359,0,0,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,19,25335,0,0,0,0,0,0, 'Force-Commander Steeljaw - On Just Summoned - Attack Longrunner Proudhoof'),
(25359,0,1,2,6,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Force-Commander Steeljaw - On Death Say Line 0'),
(25359,0,2,0,6,0,100,0,0,0,0,0,45,5,5,0,0,0,0,19,25335,0,0,0,0,0,0, 'Force-Commander Steeljaw - On Death - Set Data to Longrunner Proudhoof'),
(25359,0,3,0,9,0,100,0,0,5,8000,13000,11,15284,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Force-Commander Steeljaw - On Range - Cast Cleave'),
(25359,0,4,0,0,0,100,0,6000,9000,11000,18000,11,38256,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Force-Commander Steeljaw - IC - Cast Piercing Howl'),
(25359,0,5,0,2,0,100,1,0,50,0,0,11,50204,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Force-Commander Steeljaw - On 20% HP - Cast Steeljaw'),
(25359,0,6,0,0,0,100,0,9000,15000,18000,24000,11,41056,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Force-Commander Steeljaw - IC - Cast Whirlwind'),

(2533500,9,0,0,0,0,100,0,0,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Longrunner Proudhoof - Script - Set NPC Flags'),
(2533500,9,1,0,0,0,100,0,0,0,0,0,45,1,1,0,0,0,0,19,25336,0,0,0,0,0,0, 'Longrunner Proudhoof - Script - Set Data to Grunt Ragefist'),
(2533500,9,2,0,0,0,100,0,0,0,0,0,45,1,1,0,0,0,0,9,25338,0,200,0,0,0,0, 'Longrunner Proudhoof - Script - Set Data to Warsong Caravan Guard'),
(2533500,9,3,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,12,1,0,0,0,0,0,0, 'Longrunner Proudhoof - Script - Say Line 0'),
(2533500,9,4,0,0,0,100,0,0,0,0,0,2,232,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Longrunner Proudhoof - Script - Set Faction'),
(2533500,9,5,0,0,0,100,0,0,0,0,0,8,2,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Longrunner Proudhoof - Script - Set Hostile'),
(2533500,9,6,0,0,0,100,0,0,0,0,0,102,0,0,0,0,0,0,12,1,0,0,0,0,0,0, 'Longrunner Proudhoof - Script - Switch HP Regen off'),
(2533500,9,7,0,0,0,100,0,11000,11000,0,0,1,1,0,0,0,0,0,12,1,0,0,0,0,0,0, 'Longrunner Proudhoof - Script - Say Line 0'),
(2533500,9,8,0,0,0,100,0,1000,1000,0,0,45,2,2,0,0,0,0,19,25336,0,0,0,0,0,0, 'Longrunner Proudhoof - Script - Set Data to Grunt Ragefist'),
(2533500,9,9,0,0,0,100,0,0,0,0,0,45,2,2,0,0,0,0,9,25338,0,200,0,0,0,0, 'Longrunner Proudhoof - Script - Set Data to Warsong Caravan Guard'),
(2533500,9,10,0,0,0,100,0,0,0,0,0,53,1,25335,0,0,0,2,1,0,0,0,0,0,0,0, 'Longrunner Proudhoof - Script - Start WP'),

(2533501,9,0,0,0,0,100,0,0,0,0,0,1,5,0,0,0,0,0,12,1,0,0,0,0,0,0, 'Longrunner Proudhoof - Script 2 - Say Line 5'),
(2533501,9,1,0,0,0,100,0,0,0,0,0,15,11592,0,0,0,0,0,12,1,0,0,0,0,0,0, 'Longrunner Proudhoof - Script 2 - Complete Quest (We Strike)'),
(2533501,9,2,0,0,0,100,0,6000,6000,0,0,45,3,3,0,0,0,0,19,25336,0,0,0,0,0,0, 'Longrunner Proudhoof - Script 2 - Set Data to Grunt Ragefist'),
(2533501,9,3,0,0,0,100,0,0,0,0,0,45,3,3,0,0,0,0,9,25338,0,200,0,0,0,0, 'Longrunner Proudhoof - Script 2 - Set Data to Warsong Caravan Guard'),
(2533501,9,4,0,0,0,100,0,0,0,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Longrunner Proudhoof - Script 2 - Despawn'),

(2533600,9,0,0,0,0,100,0,0,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Grunt Ragefist - Script - Set NPC Flags'),
(2533600,9,1,0,0,0,100,0,0,0,0,0,2,232,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Grunt Ragefist - Script - Set Faction'),
(2533600,9,2,0,0,0,100,0,0,0,0,0,8,2,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Grunt Ragefist - Script - Set Hostile'),
(2533600,9,3,0,0,0,100,0,0,0,0,0,102,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Grunt Ragefist - Script - Switch HP Regen off');


DELETE FROM `waypoints` WHERE `entry`=25335;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(25335, 1, 4121.404, 5791.311, 62.72873, 'Longrunner Proudhoof'),
(25335, 2, 4101.437, 5799.435, 67.94357, 'Longrunner Proudhoof'),
(25335, 3, 4083.929, 5805.443, 71.37161, 'Longrunner Proudhoof'),
(25335, 4, 4068.87, 5807.64, 73.81717, 'Longrunner Proudhoof'),
(25335, 5, 4052.772, 5802.647, 75.09177, 'Longrunner Proudhoof'),
(25335, 6, 4038.374, 5795.233, 75.40152, 'Longrunner Proudhoof'),
(25335, 7, 4025.04, 5789.227, 75.19473, 'Longrunner Proudhoof'),
(25335, 8, 4006.379, 5787.299, 73.14676, 'Longrunner Proudhoof'),
(25335, 9, 3984.424, 5778.06, 73.17698, 'Longrunner Proudhoof'), -- Event
(25335, 10, 3952.678, 5758.444, 70.48514, 'Longrunner Proudhoof'), -- text
(25335, 11, 3919.015, 5753.338, 69.2403, 'Longrunner Proudhoof'),
(25335, 12, 3894.645, 5745.702, 70.36196, 'Longrunner Proudhoof'),
(25335, 13, 3883.361, 5725.309, 67.55053, 'Longrunner Proudhoof');

DELETE FROM `creature_summon_groups` WHERE `summonerId`=25335;
INSERT INTO `creature_summon_groups` (`summonerId`, `summonerType`, `groupId`, `entry`, `position_x`, `position_y`, `position_z`, `orientation`, `summonType`, `summonTime`) VALUES 
(25335, 0, 1, 25351, 3981.684, 5766.304, 71.69027, 1.508547, 3, 100000),
(25335, 0, 1, 25351, 3972.008, 5783.715, 74.18502, 5.856251, 3, 100000),
(25335, 0, 1, 25351, 3996.715, 5773.316, 70.84, 2.772876, 3, 100000),
(25335, 0, 1, 25350, 3988.267, 5791.996, 74.18443, 4.443494, 3, 100000),
(25335, 0, 1, 25351, 3969.23, 5768.75, 72.69688, 0.5497994, 3, 100000);


DELETE FROM `creature_text` WHERE `entry`IN(25335,25359);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`,`BroadcastTextID`) VALUES
(25335, 0, 0, '$n is going to join us on our assault. Let us bring peace to my ancestors!', 12, 1, 100, 396, 0, 0, 'Longrunner Proudhoof',24561),
(25335, 1, 0, 'WE STRIKE!', 14, 1, 100, 15, 0, 0, 'Longrunner Proudhoof',24562),
(25335, 2, 0, 'An ambush. Return them to their rest!', 12, 1, 100, 5, 0, 0, 'Longrunner Proudhoof',24563),
(25335, 3, 0, 'Regain your strength. The place where Steeljaw was felled is just ahead.', 12, 1, 100, 396, 0, 0, 'Longrunner Proudhoof',24564),
(25335, 4, 0, 'There''s the dog''s banner and there''s his corpse. What''s that? He''s upon us!', 12, 1, 100, 25, 0, 0, 'Longrunner Proudhoof',24565),
(25335, 5, 0, 'You fought well. Now go north to your orc outpost and inform Overlord Bor''gorok of our success!', 12, 1, 100, 113, 0, 0, 'Longrunner Proudhoof',24566),
(25359, 0, 0, 'I''m freed! Thank you.', 12, 1, 100, 0, 0, 0, 'Force-Commander Steeljaw',24575);

-- Achievement: Pilgrims Peril
DELETE FROM `achievement_criteria_data` WHERE `criteria_id` IN (11134,11135,11136,11137,11138,11139,11140,11141);
INSERT INTO `achievement_criteria_data` (`criteria_id`, `type`, `value1`, `value2`) VALUES
-- Alliance
(11134, 5, 66303, 0), -- Orgrimmar
(11134, 6, 14, 0), -- Orgrimmar
(11134, 16, 404, 0), -- Orgrimmar
(11135, 5, 66303, 0), -- Silvermoon City
(11135, 6, 3470, 0), -- Silvermoon City
(11135, 16, 404, 0), -- Silvermoon City
(11136, 5, 66303, 0), -- Thunder Bluff
(11136, 6, 1638, 0), -- Thunder Bluff
(11136, 16, 404, 0), -- Thunder Bluff
(11137, 5, 66303, 0), -- Undercity
(11137, 6, 1497, 0), -- Undercity
(11137, 16, 404, 0), -- Undercity
-- Horde
(11138, 5, 66303, 0), -- Exodar
(11138, 6, 3557, 0), -- Exodar
(11138, 16, 404, 0), -- Exodar
(11139, 5, 66303, 0), -- Darnassus
(11139, 6, 1657, 0), -- Darnassus
(11139, 16, 404, 0), -- Darnassus
(11140, 5, 66303, 0), -- Ironforge
(11140, 6, 809, 0), -- Ironforge
(11140, 16, 404, 0), -- Ironforge
(11141, 5, 66303, 0), -- Stormwind
(11141, 6, 12, 0), -- Stormwind
(11141, 16, 404, 0); -- Stormwind

DELETE FROM `creature_text` WHERE `entry`=21767;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`,`BroadcastTextID`) VALUES
(21767, 0, 0, 'What $r dare harm those of my flock?', 14, 0, 100, 0, 0, 0, 'Harbinger of the Raven',19398);

UPDATE `creature_template` SET `ainame`='SmartAI', `scriptname`='' WHERE `entry`=21767;

DELETE FROM `smart_scripts` WHERE `entryorguid`=21767  AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(21767,0,0,0,54,0,100,0,0,0,0,0,1,0,7000,0,0,0,0,1,0,0,0,0,0,0,0,'Harbinger of the Raven - On Just Summoned - Say Line 0'),
(21767,0,1,2,52,0,100,0,0,21767,0,0,11,37446,0,0,0,0,0,1,0,0,0,0,0,0,0,'Harbinger of the Raven - On Text Over Line 0 - Cast Ruuan ok Oracle Transformation'),
(21767,0,2,3,61,0,100,0,0,0,0,0,2,954,0,0,0,0,0,1,0,0,0,0,0,0,0,'Harbinger of the Raven - On Text Over Line 0 - Set Faction'),
(21767,0,3,0,61,0,100,0,0,0,0,0,8,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'Harbinger of the Raven - On Text Over Line 0 - Set Hostile');

UPDATE `creature_template` SET `ainame`='SmartAI', `scriptname`='' WHERE `entry`=19527;
DELETE FROM `smart_scripts` WHERE `entryorguid`=19527  AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(19527,0,0,0,4,0,100,0,0,0,0,0,11,34524,2,0,0,0,0,1,0,0,0,0,0,0,0,'Vacillating Voidcaller - On Just Summoned - Cast Elemental Response'),
(19527,0,1,0,2,0,100,1,0,10,0,0,11,34842,0,0,0,0,0,1,0,0,0,0,0,0,0,'Vacillating Voidcaller - On Less than 10% HP - Cast De-Materialize'),
(19527,0,2,0,8,0,100,0,34842,0,0,0,41,0,2,0,0,0,0,1,0,0,0,0,0,0,0,'Vacillating Voidcaller - On Spellhit De-Materialize  - Despawn'),
(19527,0,3,0,4,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Vacillating Voidcaller - On Agro - Set Phase 1'),
(19527,0,4,17,8,1,100,0,0,2,0,0,11,34336,2,0,0,0,0,1,0,0,0,0,0,0,0,'Vacillating Voidcaller - On Spellhit (Holy) (Phase 1) - Cast Damage Reduction: Holy'),
(19527,0,5,18,8,1,100,0,0,4,0,0,11,34333,2,0,0,0,0,1,0,0,0,0,0,0,0,'Vacillating Voidcaller - On Spellhit (Fire) (Phase 1) - Cast Damage Reduction: Fire'),
(19527,0,6,19,8,1,100,0,0,8,0,0,11,34335,2,0,0,0,0,1,0,0,0,0,0,0,0,'Vacillating Voidcaller - On Spellhit (Nature)(Phase 1) - Cast Damage Reduction: Nature'),
(19527,0,7,20,8,1,100,0,0,16,0,0,11,34334,2,0,0,0,0,1,0,0,0,0,0,0,0,'Vacillating Voidcaller - On Spellhit (Frost) (Phase 1) - Cast Damage Reduction: Frost'),
(19527,0,8,21,8,1,100,0,0,32,0,0,11,34338,2,0,0,0,0,1,0,0,0,0,0,0,0,'Vacillating Voidcaller - On Spellhit (Shadow) (Phase 1)  - Cast Damage Reduction: Shadow'),
(19527,0,9,22,8,1,100,0,0,64,0,0,11,34331,2,0,0,0,0,1,0,0,0,0,0,0,0,'Vacillating Voidcaller - On Spellhit (Arcane) (Phase 1)  - Cast Damage Reduction: Arcane'),
(19527,0,10,0,61,0,100,0,0,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'Vacillating Voidcaller - Link - Set Phase 2'),
(19527,0,11,0,0,2,100,0,0,0,2000,3000,11,34348,64,0,0,0,0,2,0,0,0,0,0,0,0,'Vacillating Voidcaller - IC (Phase 2)  - Cast Fireball'),
(19527,0,12,0,0,2,100,0,0,0,5000,6000,11,34446,64,0,0,0,0,2,0,0,0,0,0,0,0,'Vacillating Voidcaller - IC (Phase 2)  - Cast Arcane Missiles'),
(19527,0,13,0,0,2,100,0,0,0,2000,3000,11,34347,64,0,0,0,0,2,0,0,0,0,0,0,0,'Vacillating Voidcaller - IC (Phase 2)  - Cast Frost Bolt'),
(19527,0,14,0,0,2,100,0,0,0,2000,3000,11,34346,64,0,0,0,0,2,0,0,0,0,0,0,0,'Vacillating Voidcaller - IC (Phase 2)  - Cast Holy Bolt'),
(19527,0,15,0,0,2,100,0,0,0,2000,3000,11,34345,64,0,0,0,0,2,0,0,0,0,0,0,0,'Vacillating Voidcaller - IC (Phase 2)  - Cast Lightning Bolt'),
(19527,0,16,0,0,2,100,0,0,0,2000,3000,11,34344,64,0,0,0,0,2,0,0,0,0,0,0,0,'Vacillating Voidcaller - IC (Phase 2)  - Cast Shadow Bolt'),
(19527,0,17,10,61,0,100,0,0,0,0,0,1,3,0,0,0,0,0,1,0,0,0,0,0,0,0,'Vacillating Voidcaller - On Spellhit (Holy) (Phase 1) - Say'),
(19527,0,18,10,61,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Vacillating Voidcaller - On Spellhit (Fire) (Phase 1) - Say'),
(19527,0,19,10,61,0,100,0,0,0,0,0,1,4,0,0,0,0,0,1,0,0,0,0,0,0,0,'Vacillating Voidcaller - On Spellhit (Nature)(Phase 1) - Say'),
(19527,0,20,10,61,0,100,0,0,0,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'Vacillating Voidcaller - On Spellhit (Frost) (Phase 1) - Say'),
(19527,0,21,10,61,0,100,0,0,0,0,0,1,5,0,0,0,0,0,1,0,0,0,0,0,0,0,'Vacillating Voidcaller - On Spellhit (Shadow) (Phase 1)  - Say'),
(19527,0,22,10,61,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Vacillating Voidcaller - On Spellhit (Arcane) (Phase 1)  - Say');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=22 AND `SourceEntry`=19527;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(22, 12, 19527, 0, 0, 1, 1, 34333, 0, 0, 0, 0, 0, '', 'Vacillating Voidcaller requires Damage Reduction: Fire to cast Fireball'),
(22, 13, 19527, 0, 0, 1, 1, 34331, 0, 0, 0, 0, 0, '', 'Vacillating Voidcaller requires Damage Reduction: Arcane to cast Arcane Missiles'),
(22, 14, 19527, 0, 0, 1, 1, 34334, 0, 0, 0, 0, 0, '', 'Vacillating Voidcaller requires Damage Reduction: Frost to cast Frost Bolt'),
(22, 15, 19527, 0, 0, 1, 1, 34336, 0, 0, 0, 0, 0, '', 'Vacillating Voidcaller requires Damage Reduction: Holy to cast Holy Bolt'),
(22, 16, 19527, 0, 0, 1, 1, 34335, 0, 0, 0, 0, 0, '', 'Vacillating Voidcaller requires Damage Reduction: Nature to cast Lightning Bolt'),
(22, 17, 19527, 0, 0, 1, 1, 34338, 0, 0, 0, 0, 0, '', 'Vacillating Voidcaller requires Damage Reduction: Shadow to cast Shadowbolt');

DELETE FROM `creature_text` WHERE `entry`=19527;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`,`BroadcastTextID`) VALUES
(19527, 0, 0, '%s absorbs the fire energy of the attack.', 16, 0, 100, 0, 0, 0, 'Vacillating Voidcaller',17105),
(19527, 1, 0, '%s absorbs the arcane energy of the attack.', 16, 0, 100, 0, 0, 0, 'Vacillating Voidcaller',17109),
(19527, 2, 0, '%s absorbs the frost energy of the attack.', 16, 0, 100, 0, 0, 0, 'Vacillating Voidcaller',17106),
(19527, 3, 0, '%s absorbs the holy energy of the attack.', 16, 0, 100, 0, 0, 0, 'Vacillating Voidcaller',17110),
(19527, 4, 0, '%s absorbs the nature energy of the attack.', 16, 0, 100, 0, 0, 0, 'Vacillating Voidcaller',17107),
(19527, 5, 0, '%s absorbs the shadow energy of the attack.', 16, 0, 100, 0, 0, 0, 'Vacillating Voidcaller',17108);








