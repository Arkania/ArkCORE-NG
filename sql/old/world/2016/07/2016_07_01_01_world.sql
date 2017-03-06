
SET @ENTRY := 21315; -- Guid 74638 NG 171851
SET @Drake := 22106;
UPDATE `creature_template` SET inhabittype=4,`ScriptName`='',`AIName`='SmartAI', unit_flags=32768, MovementType=2 WHERE `entry`=@ENTRY;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@Drake;
UPDATE `creature` SET `position_x`=-3761.743,`position_y`=1081.672,`position_z`=125.3161 WHERE `id`=@ENTRY;
delete from creature where guid=160920 and id=@Drake;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@drake;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=9 AND `entryorguid`=@ENTRY*100;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,11,0,100,0,0,0,0,0,53,0,@ENTRY,0,0,0,2,1,0,0,0,0,0,0,0,'Ruul the Darkener - On Spawn - StarWP'),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,60,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Ruul the Darkener - On Spawn - Set fly on'),
(@ENTRY,0,2,0,40,0,100,0,47,@ENTRY,0,0,53,0,@ENTRY,0,0,0,2,1,0,0,0,0,0,0,0,'Ruul the Darkener - Reach wp - Re Start WP'),
(@ENTRY,0,3,0,4,0,100,0,0,0,0,0,80,@ENTRY*100,2,0,0,0,0,1,0,0,0,0,0,0,0,'Ruul the Darkener - On aggro -  ActionList'),
(@ENTRY*100,9,0,0,0,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Ruul the Darkener - ActionList -  talk1'),
(@ENTRY*100,9,1,0,0,0,100,0,5000,5000,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Ruul the Darkener - ActionList -  talk2'),
(@ENTRY,0,4,0,6,0,100,0,0,0,0,0,85,38343,1,0,0,0,0,1,0,0,0,0,0,0,0,'Ruul the Darkener - On death -  Summon Ruul''s Nether Drake With Invoker_cast'),
(@Drake, 0, 0, 0, 0, 0, 100, 0, 3000, 3000, 5000, 5000, 11, 38344, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Drake - IC - CAST'),
(@Drake, 0, 1, 0, 0, 0, 100, 0, 3000, 3000, 10000, 10000, 11, 36513, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Drake - IC - CAST'),
(@Drake, 0, 2, 0, 54, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 21, 25, 0, 0, 0, 0, 0, 0, 'Drake - Just Summoned - StartAttack'),
(@ENTRY, 0, 5, 0, 0, 0, 100, 0, 3000, 3000, 6000, 6000, 11, 36073, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'ENTRY - IC - CAST'),
(@ENTRY, 0, 6, 0, 0, 0, 100, 0, 5000, 5000, 5000, 5000, 11, 39153, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'ENTRY - IC - CAST'),
(@ENTRY, 0, 7, 0, 0, 0, 100, 0, 1000, 1000, 4000, 4000, 11, 15284, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'ENTRY - IC - CAST');

-- Waypoints for Ruul the Darkener from sniff
DELETE FROM `waypoints` WHERE `entry`=@ENTRY;
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES
(@ENTRY,1,-3805.743,1074.672,125.3161, 'Ruul the Darkener WP'),
(@ENTRY,2,-3806.74,1074.585,125.3161, 'Ruul the Darkener WP'),
(@ENTRY,3,-3844.399,1071.154,116.4082, 'Ruul the Darkener WP'),
(@ENTRY,4,-3871.77,1061.122,104.3527, 'Ruul the Darkener WP'),
(@ENTRY,5,-3897.401,1040.65,84.43602, 'Ruul the Darkener WP'),
(@ENTRY,6,-3923.55,1019.801,59.43599, 'Ruul the Darkener WP'),
(@ENTRY,7,-3946.312,1007.962,41.49157, 'Ruul the Darkener WP'),
(@ENTRY,8,-3981.2,987.1596,17.43604, 'Ruul the Darkener WP'),
(@ENTRY,9,-4003.07,957.1582,13.24213, 'Ruul the Darkener WP'),
(@ENTRY,10,-4012.831,932.0213,12.51513, 'Ruul the Darkener WP'),
(@ENTRY,11,-4023.356,901.5677,8.140135, 'Ruul the Darkener WP'),
(@ENTRY,12,-4033.129,864.9609,4.726814, 'Ruul the Darkener WP'),
(@ENTRY,13,-4039.05,829.5438,1.101814, 'Ruul the Darkener WP'),
(@ENTRY,14,-4046.8,785.2863,2.422696, 'Ruul the Darkener WP'),
(@ENTRY,15,-4053.405,754.4661,1.867994, 'Ruul the Darkener WP'),
(@ENTRY,16,-4077.986,718.4368,1.501426, 'Ruul the Darkener WP'),
(@ENTRY,17,-4104.671,681.145,2.619006, 'Ruul the Darkener WP'),
(@ENTRY,18,-4124.385,652.7042,3.424712, 'Ruul the Darkener WP'),
(@ENTRY,19,-4139.037,629.68,4.261003, 'Ruul the Darkener WP'),
(@ENTRY,20,-4144.591,607.7719,5.011003, 'Ruul the Darkener WP'),
(@ENTRY,21,-4148.39,587.783,8.4231, 'Ruul the Darkener WP'),
(@ENTRY,22,-4155.772,562.8152,11.38299, 'Ruul the Darkener WP'),
(@ENTRY,23,-4165.006,542.4948,15.88299, 'Ruul the Darkener WP'),
(@ENTRY,24,-4174.202,524.9961,22.73551, 'Ruul the Darkener WP'), -- fi Aller 
(@ENTRY,25,-4165.006,542.4948,15.88299, 'Ruul the Darkener WP'),-- début du retour
(@ENTRY,26,-4155.772,562.8152,11.38299, 'Ruul the Darkener WP'),
(@ENTRY,27,-4148.39,587.783,8.4231, 'Ruul the Darkener WP'),
(@ENTRY,28,-4144.591,607.7719,5.011003, 'Ruul the Darkener WP'),
(@ENTRY,29,-4139.037,629.68,4.261003, 'Ruul the Darkener WP'),
(@ENTRY,30,-4124.385,652.7042,3.424712, 'Ruul the Darkener WP'),
(@ENTRY,31,-4104.671,681.145,2.619006, 'Ruul the Darkener WP'),
(@ENTRY,32,-4077.986,718.4368,1.501426, 'Ruul the Darkener WP'),
(@ENTRY,33,-4053.405,754.4661,1.867994, 'Ruul the Darkener WP'),
(@ENTRY,34,-4046.8,785.2863,2.422696, 'Ruul the Darkener WP'),
(@ENTRY,35,-4039.05,829.5438,1.101814, 'Ruul the Darkener WP'),
(@ENTRY,36,-4033.129,864.9609,4.726814, 'Ruul the Darkener WP'),
(@ENTRY,37,-4023.356,901.5677,8.140135, 'Ruul the Darkener WP'),
(@ENTRY,38,-4012.831,932.0213,12.51513, 'Ruul the Darkener WP'),
(@ENTRY,39,-4003.07,957.1582,13.24213, 'Ruul the Darkener WP'),
(@ENTRY,40,-3981.2,987.1596,17.43604, 'Ruul the Darkener WP'),
(@ENTRY,41,-3946.312,1007.962,41.49157, 'Ruul the Darkener WP'),
(@ENTRY,42,-3923.55,1019.801,59.43599, 'Ruul the Darkener WP'),
(@ENTRY,43,-3897.401,1040.65,84.43602, 'Ruul the Darkener WP'),
(@ENTRY,44,-3871.77,1061.122,104.3527, 'Ruul the Darkener WP'),
(@ENTRY,45,-3844.399,1071.154,116.4082, 'Ruul the Darkener WP'),
(@ENTRY,46,-3806.74,1074.585,125.3161, 'Ruul the Darkener WP'),
(@ENTRY,47,-3805.743,1074.672,125.3161, 'Ruul the Darkener WP');

Delete from `creature_text` where `entry` in (@ENTRY);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) VALUES
(@ENTRY, 0, 0, 'The skies will darken and all will go quiet. Only then will you know the sweet serenity of death...', 12, 0, 100, 0, 0, 0, 'Ruul the Darkener', 19291),
(@ENTRY, 1, 0, 'Your world is at an end.', 12, 0, 100, 0, 0, 0, 'Ruul the Darkener', 19290);

UPDATE `creature_template` SET `npcflag`= 16777216, `AIName`='SmartAI', `VehicleId`=220 WHERE `entry`=28192;

-- Archmage Pentarus
SET @ENTRY := 28160;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,10024,0,0,0,80,2816000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Archmage Pentarus - On gossip option select  - run script");

-- Archmage Pentarus
SET @ENTRY := 2816000;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,0,0,0,0,11,50859,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Archmage Pentarus - Script - Cast Flight to Sholazar on player"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,1000,1000,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Archmage Pentarus - Script - say 0");

UPDATE `creature_template` SET `dmg_multiplier`=5 WHERE  `entry`=28468;

DELETE FROM `creature_addon` WHERE `guid`=223572; -- Monte Muzzleshot 27987
INSERT INTO `creature_addon` (`guid`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`)VALUES
(223572,0,0,1,0, '50544'); -- Monte Muzzleshot, aura: Cosmetic - Parachute Stuck

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry`=28192;
INSERT INTO `npc_spellclick_spells` (`npc_entry`,`spell_id`,`cast_flags`,`user_type`) VALUES
(28192,46598,1,0);  -- Archmage Pentarus' Flying Machine - Ride Vehicle Hardcoded

DELETE FROM `spell_target_position` WHERE `id` in (50987, 50859); 
INSERT INTO `spell_target_position` (`id`,`target_map`,`target_position_x`,`target_position_y`,`target_position_z`,`target_orientation`) VALUES
(50987, 571, 5071.35, 4642.54, 72.164, 0.878587);-- Teleport to Sholazar
-- (50859, 571, 5832.892, 482.8708, 658.2753, 0.9121326);

DELETE FROM `creature_text` WHERE `entry`in (28229, 27987, 28192);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`, `BroadcastTextID`) VALUES
(28229,0,0, 'More intruders? You''ll soon learn, no one messes with the Venture Company!',14,0,100,0,0,0, 'Venture Co. Air Patrol',27611),
(27987,0,0, 'Over here, to the southeast. I see they got you too...',14,0,100,0,0,0, 'Monte Muzzleshot',27610),
(28192,0,0, 'WARNING: Missile lock detected. Engaging evasive maneuvers.',12,0,100,0,0,0, 'Archimage Pentarus Flying Machine',27621);

UPDATE creature_template SET InhabitType=4 WHERE entry=27987;

UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=28229;

SET @CGUID := 191170; -- entry = 22418
DELETE FROM `creature` WHERE `guid`=@CGUID;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `MovementType`) VALUES
(@CGUID, 22418, 534, 1, 1, 5502.288, -3525.471, 1607.909, 2.617994, 7200, 0, 0);

DELETE FROM `creature_text` WHERE `entry`=17968 AND `groupid`=8;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `comment`) VALUES
(17968, 8, 0, 'All of your efforts have been in vain, for the draining of the World Tree has already begun!  Soon the heart of your world will beat no more!', 14, 0, 100, 0, 0, 10986, 20432, 'Archimonde - Intro');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry` IN (39140,39141,39142);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13,1,39140,0,0,31,0,3,22418,0,0,0, '', 'Drain World Tree Visual'),
(13,1,39141,0,0,31,0,3,17968,0,0,0, '', 'Drain World Tree Visual 2');

DELETE FROM `spell_script_names` WHERE `spell_id`=39142;

DELETE FROM `creature_text` WHERE `entry` IN(33662,33701,33626,33686,33696);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextID`, `comment`) VALUES
(33662, 0, 0, 'Any luck?', 12, 0, 100, 0, 0, 0, 34184, 'Kirin Tor Battle-Mage to Player'),
(33662, 1, 0, 'Keep at it. If our suspicions are right and this is a transporter, it could prove extremely useful in our assault.', 12, 0, 100, 0, 0, 0, 34186, 'Kirin Tor Battle-Mage to Player'),
(33701, 0, 0, 'I heard a story or two of a Lore Keeper in Uldaman that fit your description. Do you serve a similar purpose?', 12, 0, 100, 0, 0, 0, 33702, 'High Explorer Dellorah to Player'),
(33701, 1, 0, 'Frontal defense systems? Is there something I should let Brann know before he has anyone attempt to enter the complex?', 12, 0, 100, 0, 0, 0, 33704, 'High Explorer Dellorah to Player'),
(33701, 2, 0, 'Can you detail the nature of these defense systems?', 12, 0, 100, 0, 0, 0, 33706, 'High Explorer Dellorah to Player'),
(33701, 3, 0, 'Got it. At least we don''t have to deal with those orbital emplacements.', 12, 0, 100, 0, 0, 0, 33708, 'High Explorer Dellorah to Player'),
(33701, 4, 0, 'Rhydian, make sure you let Brann and Archmage Pentarus know about those defenses immediately.', 12, 0, 100, 0, 0, 0, 33709, 'High Explorer Dellorah to Player'),
(33701, 5, 0, 'And you mentioned an imprisoned entity? What is the nature of this entity and what is its status?', 12, 0, 100, 0, 0, 0, 33710, 'High Explorer Dellorah to Player'),
(33701, 6, 0, 'Yogg-Saron is here? It sounds like we really will have our hands full then.', 12, 0, 100, 0, 0, 0, 33713, 'High Explorer Dellorah to Player'),
(33626, 0, 0, 'Not a bit. For the life of me, I can''t figure out how this thing works.', 12, 0, 100, 0, 0, 0, 34183, 'Hired Engineer to Player'),
(33626, 1, 0, 'I know, I know... I haven''t given up yet. Don''t get your hopes up though, this technology is way beyond me.', 12, 0, 100, 0, 0, 0, 34187, 'Hired Engineer to Player'),
(33686, 0, 0, 'I was constructed to serve as a repository for essential information regarding this complex. My primary functions include communicating the status of the frontal defense systems and assessing the status of the entity that this complex was built to imprison.', 12, 0, 100, 0, 0, 0, 33703, 'Lore Keeper of Norgannon to Player'),
(33686, 1, 0, 'Compromise of complex detected, security override enabled - query permitted.', 12, 0, 100, 0, 0, 0, 33707, 'Lore Keeper of Norgannon to Player'),
(33686, 2, 0, 'Primary defensive emplacements consist of iron constructs and Storm Beacons, which will generate additional constructs as necessary. Secondary systems consist of orbital defense emplacements.', 12, 0, 100, 0, 0, 0, 33712, 'Lore Keeper of Norgannon to Player'),
(33686, 3, 0, 'Entity designate: Yogg-Saron. Security has been compromised. Prison operational status unknown. Unable to contact Watchers for notification purposes.', 12, 0, 100, 0, 0, 0, 33711, 'Lore Keeper of Norgannon to Player'),
(33696, 0, 0, '%s nods.', 16, 0, 100, 0, 0, 0, 33715, 'Archmage Rhydian to Player'),
(33696, 1, 0, '%s whispers something to Brann.', 16, 0, 100, 0, 0, 0, 33716, 'Archmage Rhydian to Player');

UPDATE `creature_template` SET `AIName`='SmartAI', `ScriptName`='' WHERE `entry` IN(33662,33701,33696);
DELETE FROM `smart_scripts` WHERE `entryorguid`IN(33696,33701,-236093) AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`IN(3369600,3370100) AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(-236093,0,0,0,10,0,100,0,1,40,90000,120000,80,3369600,2,0,0,0,0,1,0,0,0,0,0,0,0,'Kirin Tor Battle-Mage - OOC Los - Run Script'),
(33701,0,0,0,10,0,100,1,1,40,30000,60000,80,3370100,2,0,0,0,0,1,0,0,0,0,0,0,0,'High Explorer Dellorah - OOC Los - Run Script (No repeat)'),
(33696,0,0,0,38,0,100,0,1,1,0,0,1,0,2000,0,0,0,0,1,0,0,0,0,0,0,0,'Archmage Rhydian - On Data Set - Say Line 0'),
(33696,0,1,0,52,0,100,0,0,33696,0,0,53,1,33696,0,0,0,0,1,0,0,0,0,0,0,0,'Archmage Rhydian - On Text Over (Line 0) - Start WP'),
(33696,0,2,3,40,0,100,0,8,33696,0,0,54,8000,0,0,0,0,0,1,0,0,0,0,0,0,0,'Archmage Rhydian - On Reached WP8 - Pause WP'),
(33696,0,3,0,61,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Archmage Rhydian - On Reached WP8 - Say Line 1'),
(33696,0,4,0,40,0,100,0,10,33696,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,5.916666,'Archmage Rhydian - On Reached WP10 - Set Orientation'),
(3369600, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Kirin Tor Battle-Mage - Script - Say Line 0'),
(3369600, 9, 1, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 19, 33626, 0, 0, 0, 0, 0, 0, 'Kirin Tor Battle-Mage - Script - Say Line 0 (Hired Engineer)'),
(3369600, 9, 2, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Kirin Tor Battle-Mage - Script - Say Line 1'),
(3369600, 9, 3, 0, 0, 0, 100, 0, 9000, 9000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 19, 33626, 0, 0, 0, 0, 0, 0, 'Kirin Tor Battle-Mage - Script - Say Line 1 (Hired Engineer)'),
(3370100, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'High Explorer Dellorah - Script - Say Line 0'),
(3370100, 9, 1, 0, 0, 0, 100, 0, 9000, 9000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 19, 33686, 0, 0, 0, 0, 0, 0, 'High Explorer Dellorah - Script - Say Line 0 (Lore Keeper of Norgannon)'),
(3370100, 9, 2, 0, 0, 0, 100, 0, 13000, 13000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'High Explorer Dellorah - Script - Say Line 1'),
(3370100, 9, 3, 0, 0, 0, 100, 0, 11000, 11000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'High Explorer Dellorah - Script - Say Line 2'),
(3370100, 9, 4, 0, 0, 0, 100, 0, 8000, 8000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 19, 33686, 0, 0, 0, 0, 0, 0, 'High Explorer Dellorah - Script - Say Line 1 (Lore Keeper of Norgannon)'),
(3370100, 9, 5, 0, 0, 0, 100, 0, 8000, 8000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 19, 33686, 0, 0, 0, 0, 0, 0, 'High Explorer Dellorah - Script - Say Line 2 (Lore Keeper of Norgannon)'),
(3370100, 9, 6, 0, 0, 0, 100, 0, 12000, 12000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'High Explorer Dellorah - Script - Say Line 3'),
(3370100, 9, 7, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 1, 4, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'High Explorer Dellorah - Script - Say Line 4'),
(3370100, 9, 8, 0, 0, 0, 100, 0, 6000, 6000, 0, 0, 1, 5, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'High Explorer Dellorah - Script - Say Line 5'),
(3370100, 9, 9, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 33696, 0, 0, 0, 0, 0, 0, 'High Explorer Dellorah - Script - Set Data to Archmage Rhydian'),
(3370100, 9, 10, 0, 0, 0, 100, 0, 9000, 9000, 0, 0, 1, 4, 0, 0, 0, 0, 0, 19, 33686 , 0, 0, 0, 0, 0, 0, 'High Explorer Dellorah - Script - Say Line 3 (Lore Keeper of Norgannon)'),
(3370100, 9, 11, 0, 0, 0, 100, 0, 13000, 13000, 0, 0, 1, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'High Explorer Dellorah - Script - Say Line 6');

DELETE FROM `waypoints` WHERE `entry`=33696;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(33696, 1, -769.512 ,-120.8109 ,429.5509, 'Archmage Rhydian'),
(33696, 2, -769.1432 ,-104.0848 ,429.8661, 'Archmage Rhydian'),
(33696, 3, -763.0945 ,-86.176 ,429.9557, 'Archmage Rhydian'),
(33696, 4, -755.0403 ,-68.30566 ,429.9557, 'Archmage Rhydian'),
(33696, 5, -746.3733 ,-54.03885 ,429.9657, 'Archmage Rhydian'),
(33696, 6, -738.9852 ,-49.87864 ,429.9657, 'Archmage Rhydian'),
(33696, 7, -729.1484 ,-49.88547 ,429.9657, 'Archmage Rhydian'),
(33696, 8, -718.4777 ,-52.54433 ,429.8407, 'Archmage Rhydian'),
(33696, 9, -768.5124 ,-112.0747 ,429.8398, 'Archmage Rhydian'),
(33696, 10, -773.566 ,-144.6838 ,429.9191, 'Archmage Rhydian');

DELETE FROM creature_text WHERE entry=15990;
INSERT INTO creature_text VALUES 
(15990, 0, 0, "Your forces are nearly marshaled to strike back against your enemies, my liege.", 14, 0, 100, 0, 0, 14467, "kelthuzad SAY_SAPP_DIALOG1", 12990),
(15990, 1, 0, "It is good that you serve me so faithfully. Soon, all will serve the Lich King and in the end, you shall be rewarded...so long as you do not falter.", 14, 0, 100, 0, 0, 8881, "kelthuzad SAY_SAPP_DIALOG2_LICH", 0),
(15990, 2, 0, "Yes, master. The time of their ultimate demise draws close.... What is this?", 14, 0, 100, 0, 0, 14468, "kelthuzad SAY_SAPP_DIALOG3", 12991),
(15990, 3, 0, "Your security measures have failed! See to this interruption immediately!", 14, 0, 100, 0, 0, 8882, "kelthuzad SAY_SAPP_DIALOG4_LICH", 0),
(15990, 4, 0, "As you command, master!", 14, 0, 100, 0, 0, 14469, "kelthuzad SAY_SAPP_DIALOG5", 12992),
(15990, 5, 0, "No!!! A curse upon you, interlopers! The armies of the Lich King will hunt you down. You will not escape your fate...", 14, 0, 100, 0, 0, 14484, "kelthuzad SAY_CAT_DIED", 13150),
(15990, 6, 0, "Who dares violate the sanctity of my domain? Be warned, all who trespass here are doomed.", 14, 0, 100, 0, 0, 14463, "kelthuzad SAY_TAUNT1", 12984),
(15990, 6, 1, "Fools! You think yourselves triumphant? You have only taken one step closer to the abyss!", 14, 0, 100, 0, 0, 14464, "kelthuzad SAY_TAUNT2", 12985),
(15990, 6, 2, "I grow tired of these games. Proceed, and I will banish your souls to oblivion!", 14, 0, 100, 0, 0, 14465, "kelthuzad SAY_TAUNT3", 12986),
(15990, 6, 3, "You have no idea what horrors lie ahead. You have seen nothing! The frozen heart of Naxxramas awaits you!", 14, 0, 100, 0, 0, 14466, "kelthuzad SAY_TAUNT4", 27382),
(15990, 7, 0, "Pray for mercy!", 14, 0, 100, 0, 0, 14475, "kelthuzad SAY_AGGRO1", 12995),
(15990, 7, 1, "Scream your dying breath!", 14, 0, 100, 0, 0, 14476, "kelthuzad SAY_AGGRO2", 12996),
(15990, 7, 2, "The end is upon you!", 14, 0, 100, 0, 0, 14477, "kelthuzad SAY_AGGRO3", 12997),
(15990, 8, 0, "The dark void awaits you!", 14, 0, 100, 0, 0, 14478, "kelthuzad SAY_SLAY1", 13021),
(15990, 8, 1, "%s cackles maniacally.", 16, 0, 100, 0, 0, 14479, "kelthuzad SAY_SLAY2", 29805),
(15990, 9, 0, "Agghhhh! Do... not... rejoice! Your victory is a hollow one, for I shall return with powers beyond your imagining!", 14, 0, 100, 0, 0, 14480, "kelthuzad SAY_DEATH", 13019),
(15990, 10, 0, "Your soul is bound to me, now!", 14, 0, 100, 0, 0, 14472, "kelthuzad SAY_CHAIN1", 13017),
(15990, 10, 1, "There will be no escape!", 14, 0, 100, 0, 0, 14473, "kelthuzad SAY_CHAIN2", 13018),
(15990, 11, 0, "I will freeze the blood in your veins!", 14, 0, 100, 0, 0, 14474, "kelthuzad SAY_FROST_BLAST", 13020),
(15990, 12, 0, "Master, I require aid!", 14, 0, 100, 0, 0, 14470, "kelthuzad SAY_REQUEST_AID", 12998),
(15990, 13, 0, "Very well. Warriors of the frozen wastes, rise up! I command you to fight, kill and die for your master! Let none survive!", 14, 0, 100, 0, 0, 0, "kelthuzad SAY_ANSWER_REQUEST", 12994),
(15990, 14, 0, "Minions, servants, soldiers of the cold dark! Obey the call of Kel'Thuzad!", 14, 0, 100, 0, 0, 14471, "kelthuzad SAY_SUMMON_MINIONS", 12999),
(15990, 15, 0, "Your petty magics are no challenge to the might of the Scourge!", 14, 0, 100, 0, 0, 14481, "kelthuzad SAY_SPECIAL1_MANA_DET", 13492),
(15990, 15, 1, "Enough! I grow tired of these distractions! ", 14, 0, 100, 0, 0, 14483, "kelthuzad SAY_SPECIAL3_MANA_DET", 0),
(15990, 15, 2, "Fools, you have spread your powers too thin. Be free, my minions!", 14, 0, 100, 0, 0, 14482, "kelthuzad SAY_SPECIAL2_DISPELL", 0),
(15990, 16, 0, "Who dares violate the sanctity of my domain? Be warned, all who trespass here are doomed.", 14, 0, 100, 0, 0, 14463, "kelthuzad SAY_TAUNT1", 12984),
(15990, 17, 0, "Fools! You think yourselves triumphant? You have only taken one step closer to the abyss!", 14, 0, 100, 0, 0, 14464, "kelthuzad SAY_TAUNT2", 12985),
(15990, 18, 0, "I grow tired of these games. Proceed, and I will banish your souls to oblivion!", 14, 0, 100, 0, 0, 14465, "kelthuzad SAY_TAUNT3", 12986),
(15990, 19, 0, "You have no idea what horrors lie ahead. You have seen nothing! The frozen heart of Naxxramas awaits you!", 14, 0, 100, 0, 0, 14466, "kelthuzad SAY_TAUNT4", 27382),
(15990, 20, 0, "Come, heroes... By the will of the Lich King, you shall be destroyed.", 14, 0, 100, 0, 0, 0, "Kel'Thuzad SAY_DIALOGUE_SAPPHIRON_KELTHUZAD4", 12993);

DELETE FROM creature_text WHERE entry=16980;
INSERT INTO creature_text VALUES 
(16980, 0, 0, "Intruders have breached the inner sanctum. Hasten the destruction of the green dragon! Leave only bones and sinew for the reanimation!", 14, 0, 0, 0, 0, 17251, "The Lich King - Valithria Dreamwalker - SAY_LICH_KING_INTRO", 38682),
(16980, 1, 0, "Soon we will eradicate the Alliance and Horde. Then the rest of Azeroth will fall before the might of my army.", 14, 0, 100, 0, 0, 14768, "The Lich King SAY_DIALOGUE_SAPPHIRON_LICHKING", 12988),
(16980, 2, 0, "Invaders... here?! DESTROY them, Kel'Thuzad! Naxxramas must not fall!", 14, 0, 100, 0, 0, 14769, "The Lich King SAY_DIALOGUE_SAPPHIRON_LICHKING2", 12989),
(16980, 3, 0, "Very well. Warriors of the frozen wastes, rise up! I command you to fight, kill and die for your master! Let none survive!", 14, 0, 100, 0, 0, 14770, "The Lich King SAY_ANSWER_REQUEST", 12994);

DELETE FROM `creature` WHERE `guid` BETWEEN 11762 AND 11766;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `MovementType`) VALUES
(11762, 15384, 533, 3, 1, 3759.62, -5172.786, 143.8345, 5.148721, 7200, 0, 0), -- 15384 (Area: -1)
(11763, 15384, 533, 3, 1, 3716.097, -5106.208, 141.373, 4.939282, 7200, 0, 0), -- 15384 (Area: -1)
(11764, 15384, 533, 3, 1, 3777.213, -5066.177, 143.6412, 1.53589, 7200, 0, 0), -- 15384 (Area: -1)
(11765, 15384, 533, 3, 1, 3732.598, -5028.03, 144.0342, 5.951573, 7200, 0, 0), -- 15384 (Area: -1)
(11766, 15384, 533, 3, 1, 3700.7, -5182.372, 143.9172, 3.525565, 7200, 0, 0); -- 15384 (Area: -1)

DELETE FROM `gossip_menu` WHERE `entry` in(10355,10366,10477);
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES 
(10355, 14369),
(10366, 14375),
(10477, 14496);

DELETE FROM `gossip_menu_option` WHERE `menu_id` in(10355,10366,10477);
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `OptionBroadcastTextID`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`, `BoxBroadcastTextID`) VALUES 
(10355, 0, 0, 'We''re ready. Begin the assault!', 33652, 1, 1, 0, 0, 0, 0, NULL, 0),
(10366, 0, 0, 'Activate secondary defensive systems.', 34420, 1, 1, 10477, 0, 0, 0, NULL, 0),
(10477, 0, 0, 'Confirmed.', 34421, 1, 1, 0, 0, 0, 0, NULL, 0);

UPDATE `creature_template` SET `gossip_menu_id`=10355 WHERE  `entry`=33579;

UPDATE `creature_template` SET `AIName`='SmartAI' WHERE entry=32451;

UPDATE `creature` SET `modelid`=0, movementType=2 WHERE id=32451 and guid IN (226807, 226808);

DELETE FROM creature_addon WHERE guid = 226808;
INSERT INTO creature_addon (guid, path_id, mount, bytes1, bytes2, emote,auras) VALUES (226808, 1143310, 0, 0, 1, 0, '');

DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid` IN (32451);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(32451, 0, 0, 0, 1, 0, 100, 0, 5000, 5000, 120000, 120000, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Dalaran Citizen - Ooc - talk');

DELETE FROM waypoint_data WHERE id=1143310;
INSERT INTO waypoint_data (id, POINT, position_x, position_y, position_z, orientation, delay, move_flag, ACTION, action_chance, wpguid) VALUES
(1143310, 1, 5961.356445, 661.699219, 641.721252, 0, 0, 0, 0, 100, 0),
(1143310, 2, 5954.011230, 657.709167, 641.991577, 0, 0, 0, 0, 100, 0),
(1143310, 3, 5947.983887, 658.844055, 642.101562, 0, 0, 0, 0, 100, 0),
(1143310, 4, 5950.894043, 662.109314, 641.363831, 0, 0, 0, 0, 100, 0),
(1143310, 5, 5959.004395, 674.209778, 640.880432, 0, 0, 0, 0, 100, 0),
(1143310, 6, 5961.065430, 680.407043, 640.494263, 0, 0, 0, 0, 100, 0),
(1143310, 7, 5962.776367, 679.769470, 640.680603, 0, 0, 0, 0, 100, 0),
(1143310, 8, 5963.701172, 675.173035, 640.749817, 0, 0, 0, 0, 100, 0),
(1143310, 9, 5963.879883, 666.781982, 641.512024, 0, 20000, 0, 0, 100, 0);

DELETE FROM creature_text WHERE entry IN (32451);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) VALUES
(32451, 0, 0, 'She said to meet her right here... maybe I''m in the wrong place?', 12, 0, 100, 1, 0, 0, 'Dalaran Citizen', 33069), 
(32451, 0, 1, 'Luckily, the Lich King''s grasp has not reached Dalaran yet.', 12, 0, 100, 1, 0, 0, 'Dalaran Citizen', 33068), 
(32451, 0, 2, 'Sometimes it''s nice to get away from the sanctum and get some fresh air.', 12, 0, 100, 1, 0, 0, 'Dalaran Citizen', 33067);

DELETE FROM `spell_proc_event` WHERE `entry` IN (71174,71198);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES
(71174, 1, 7, 0, 0, 0, 0, 0, 0, 0, 0),
(71198, 4, 11, 0, 0, 0, 0, 0, 0, 0, 0);

delete from creature where guid=181680;
INSERT INTO `creature` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `curhealth`, `curmana`, `MovementType`) VALUES
(181680, 16873, 530, -945.313, 1948.252, 58.1359, 67.06455, 300, 3984, 2434, 2);

SET @GUID := 180247;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-1058.69,`position_y`=2123.373,`position_z`=51.63616 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-1058.69,2123.373,51.63616,0,0,0,0,100,0),
(@PATH,2,-1057.219,2099.756,59.51154,0,0,0,0,100,0),
(@PATH,3,-1044.785,2080.962,64.48811,0,0,0,0,100,0),
(@PATH,4,-1027.752,2060.003,67.17399,0,0,0,0,100,0),
(@PATH,5,-1035.883,2045.864,67.88428,0,0,0,0,100,0),
(@PATH,6,-1024.891,2036.104,67.17399,0,0,0,0,100,0),
(@PATH,7,-1011.885,2038.549,67.04899,0,0,0,0,100,0),
(@PATH,8,-993.7006,2017.729,67.06455,0,0,0,0,100,0),
(@PATH,9,-1008.182,1997.039,67.06455,0,0,0,0,100,0),
(@PATH,10,-992.9711,2018.175,67.06455,0,0,0,0,100,0),
(@PATH,11,-971.9114,2014.351,67.06455,0,0,0,0,100,0),
(@PATH,12,-992.9711,2018.175,67.06455,0,0,0,0,100,0),
(@PATH,13,-1008.182,1997.039,67.06455,0,0,0,0,100,0),
(@PATH,14,-1008.182,1997.039,67.06455,0,0,0,0,100,0),
(@PATH,15,-993.7006,2017.729,67.06455,0,0,0,0,100,0),
(@PATH,16,-1011.885,2038.549,67.04899,0,0,0,0,100,0),
(@PATH,17,-1011.885,2038.549,67.04899,0,0,0,0,100,0),
(@PATH,18,-1024.891,2036.104,67.17399,0,0,0,0,100,0),
(@PATH,19,-1035.883,2045.864,67.88428,0,0,0,0,100,0),
(@PATH,20,-1027.752,2060.003,67.17399,0,0,0,0,100,0),
(@PATH,21,-1027.752,2060.003,67.17399,0,0,0,0,100,0),
(@PATH,22,-1044.785,2080.966,64.57795,0,0,0,0,100,0),
(@PATH,23,-1057.219,2099.756,59.51154,0,0,0,0,100,0);

SET @GUID := 180248;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-1144.076,`position_y`=1954.738,`position_z`=80.57024 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-1144.076,1954.738,80.57024,0,0,0,0,100,0),
(@PATH,2,-1133.44,1972.225,73.66801,0,0,0,0,100,0),
(@PATH,3,-1122.611,1999.216,68.83028,0,0,0,0,100,0),
(@PATH,4,-1099.563,2031.872,67.05327,0,0,0,0,100,0),
(@PATH,5,-1084.684,2065.122,66.82748,0,0,0,0,100,0),
(@PATH,6,-1070.713,2090.635,62.18363,0,0,0,0,100,0),
(@PATH,7,-1100.243,2084.849,66.59998,0,0,0,0,100,0),
(@PATH,8,-1129.753,2078.135,67.00842,0,0,0,0,100,0),
(@PATH,9,-1100.243,2084.849,66.59998,0,0,0,0,100,0),
(@PATH,10,-1070.713,2090.635,62.18363,0,0,0,0,100,0),
(@PATH,11,-1084.646,2065.203,66.72787,0,0,0,0,100,0),
(@PATH,12,-1099.563,2031.872,67.05327,0,0,0,0,100,0),
(@PATH,13,-1122.611,1999.216,68.83028,0,0,0,0,100,0),
(@PATH,14,-1133.43,1972.312,73.66801,0,0,0,0,100,0);

SET @GUID := 180249;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-1060.848,`position_y`=2105.119,`position_z`=58.13591 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-1060.848,2105.119,58.13591,0,0,0,0,100,0),
(@PATH,2,-1037.167,2107.136,59.97014,0,0,0,0,100,0),
(@PATH,3,-1018.748,2084.713,68.99667,0,0,0,0,100,0),
(@PATH,4,-990.0961,2053.444,67.06454,0,0,0,0,100,0),
(@PATH,5,-961.8248,2037.499,67.04703,0,0,0,0,100,0),
(@PATH,6,-938.3379,2024.596,65.73439,0,0,0,0,100,0),
(@PATH,7,-921.1564,2015.199,62.66013,0,0,0,0,100,0),
(@PATH,8,-909.5775,1992.915,67.29996,0,0,0,0,100,0),
(@PATH,9,-889.6608,1985.54,67.38715,0,0,0,0,100,0),
(@PATH,10,-879.1632,1955.284,67.81312,0,0,0,0,100,0),
(@PATH,11,-877.1085,1921.789,70.60205,0,0,0,0,100,0),
(@PATH,12,-901.7319,1883,76.4217,0,0,0,0,100,0),
(@PATH,13,-877.1085,1921.789,70.60205,0,0,0,0,100,0),
(@PATH,14,-879.1632,1955.284,67.81312,0,0,0,0,100,0),
(@PATH,15,-889.6608,1985.54,67.38715,0,0,0,0,100,0),
(@PATH,16,-909.5775,1992.915,67.29996,0,0,0,0,100,0),
(@PATH,17,-921.1564,2015.199,62.66013,0,0,0,0,100,0),
(@PATH,18,-938.3379,2024.596,65.73439,0,0,0,0,100,0),
(@PATH,19,-961.8248,2037.499,67.04703,0,0,0,0,100,0),
(@PATH,20,-990.0961,2053.444,67.06454,0,0,0,0,100,0),
(@PATH,21,-1018.748,2084.713,68.99667,0,0,0,0,100,0),
(@PATH,22,-1037.167,2107.136,59.97014,0,0,0,0,100,0),
(@PATH,23,-1060.848,2105.119,58.13591,0,0,0,0,100,0);

SET @GUID := 181680;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-945.313,`position_y`=1948.252,`position_z`=67.06455 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-945.313,1948.252,67.06455,0,0,0,0,100,0),
(@PATH,2,-946.7964,1966.628,67.06455,0,0,0,0,100,0),
(@PATH,3,-932.1639,1983.549,66.96194,0,0,0,0,100,0),
(@PATH,4,-914.9733,1976.555,67.05032,0,0,0,0,100,0),
(@PATH,5,-929.8001,1991.014,66.44107,0,0,0,0,100,0),
(@PATH,6,-929.8001,1991.014,66.44107,0,0,0,0,100,0),
(@PATH,7,-941.426,2015.632,66.31691,0,0,0,0,100,0),
(@PATH,8,-965.7396,2015.727,67.03322,0,0,0,0,100,0),
(@PATH,9,-968.4443,2047.705,67.06454,0,0,0,0,100,0),
(@PATH,10,-965.7396,2015.727,67.03322,0,0,0,0,100,0),
(@PATH,11,-965.7396,2015.727,67.03322,0,0,0,0,100,0),
(@PATH,12,-941.426,2015.632,66.31691,0,0,0,0,100,0),
(@PATH,13,-929.8001,1991.014,66.44107,0,0,0,0,100,0),
(@PATH,14,-914.9733,1976.555,67.05032,0,0,0,0,100,0),
(@PATH,15,-914.9733,1976.555,67.05032,0,0,0,0,100,0),
(@PATH,16,-932.1639,1983.549,66.96194,0,0,0,0,100,0),
(@PATH,17,-946.7964,1966.628,67.06455,0,0,0,0,100,0);

SET @ENTRY := 19434;
SET @GUID := 184045;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=177.5729,`position_y`=2268.238,`position_z`=48.5948 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,177.5729,2268.238,48.5948,0,0,0,0,100,0),
(@PATH,2,206.0571,2228.519,54.04856,0,0,0,0,100,0);

SET @GUID := 184046;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=190.7178,`position_y`=2286.323,`position_z`=49.66181 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,190.7178,2286.323,49.66181,0,0,0,0,100,0),
(@PATH,2,210.6431,2285.845,53.60326,0,0,0,0,100,0),
(@PATH,3,222.5459,2286.666,56.13475,0,0,0,0,100,0),
(@PATH,4,231.5569,2296.63,60.31371,0,0,0,0,100,0),
(@PATH,5,220.7462,2308.746,60.02021,0,0,0,0,100,0),
(@PATH,6,208.7211,2311.991,57.36103,0,0,0,0,100,0),
(@PATH,7,195.7977,2312.93,53.85427,0,0,0,0,100,0),
(@PATH,8,181.254,2297.919,50.28107,0,0,0,0,100,0);

SET @GUID := 184047;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=233.3709,`position_y`=2074.927,`position_z`=39.10539 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,233.3709,2074.927,39.10539,0,0,0,0,100,0),
(@PATH,2,228.1582,2076.218,39.70464,0,0,0,0,100,0),
(@PATH,3,226.8357,2086.181,39.48833,0,0,0,0,100,0),
(@PATH,4,227.4231,2100.461,39.53439,0,0,0,0,100,0),
(@PATH,5,231.5971,2104.666,38.92635,0,0,0,0,100,0),
(@PATH,6,237.6874,2098.439,39.00676,0,0,0,0,100,0),
(@PATH,7,241.6207,2088.015,38.11906,0,0,0,0,100,0),
(@PATH,8,238.947,2078.802,38.06547,0,0,0,0,100,0);

SET @GUID := 184048;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-523.7537,`position_y`=2008.213,`position_z`=82.43176 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-523.7537,2008.213,82.43176,0,0,0,0,100,0),
(@PATH,2,-513.3772,2034.226,82.13103,0,0,0,0,100,0),
(@PATH,3,-501.1374,2063.957,81.46646,0,0,0,0,100,0),
(@PATH,4,-490.7202,2097.977,79.50304,0,0,0,0,100,0),
(@PATH,5,-495.6437,2124.143,75.1469,0,0,0,0,100,0),
(@PATH,6,-500.0753,2152.032,70.07507,0,0,0,0,100,0),
(@PATH,7,-497.6553,2131.211,73.99121,0,0,0,0,100,0),
(@PATH,8,-488.903,2108.3,78.71799,0,0,0,0,100,0),
(@PATH,9,-496.6252,2076.111,81.08714,0,0,0,0,100,0),
(@PATH,10,-505.7927,2051.876,81.88617,0,0,0,0,100,0),
(@PATH,11,-519.2833,2018.794,82.35017,0,0,0,0,100,0),
(@PATH,12,-523.7976,2008.294,82.49103,0,0,0,0,100,0);

SET @GUID := 184049;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-558.5822,`position_y`=2003.227,`position_z`=98.30606 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-558.5822,2003.227,98.30606,0,0,0,0,100,0),
(@PATH,2,-557.4218,2005.291,99.07405,0,0,0,0,100,0),
(@PATH,3,-559.7542,2056.054,96.38632,0,0,0,0,100,0),
(@PATH,4,-540.9093,2062.701,104.2178,0,0,0,0,100,0),
(@PATH,5,-538.0739,2083.637,102.7935,0,0,0,0,100,0),
(@PATH,6,-531.9629,2100.469,104.145,0,0,0,0,100,0),
(@PATH,7,-540.8042,2121.509,97.44407,0,0,0,0,100,0),
(@PATH,8,-542.6715,2139.263,94.42299,0,0,0,0,100,0),
(@PATH,9,-542.0955,2125.005,96.38588,0,0,0,0,100,0),
(@PATH,10,-531.0101,2105.611,103.8495,0,0,0,0,100,0),
(@PATH,11,-533.4691,2097.096,103.5421,0,0,0,0,100,0),
(@PATH,12,-539.8324,2066.038,103.8721,0,0,0,0,100,0),
(@PATH,13,-559.5454,2057.871,96.58672,0,0,0,0,100,0),
(@PATH,14,-557.4636,2005.37,98.92694,0,0,0,0,100,0);

SET @GUID := 184050;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-506.4011,`position_y`=1982.52,`position_z`=85.11931 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-506.4011,1982.52,85.11931,0,0,0,0,100,0),
(@PATH,2,-491.8763,2002.533,90.20009,0,0,0,0,100,0),
(@PATH,3,-475.5587,2034.282,93.52704,0,0,0,0,100,0),
(@PATH,4,-459.14,2057.011,93.19531,0,0,0,0,100,0),
(@PATH,5,-488.9269,2006.812,90.64146,0,0,0,0,100,0),
(@PATH,6,-506.4684,1982.384,85.10349,0,0,0,0,100,0),
(@PATH,7,-459.1624,2056.984,93.22046,0,0,0,0,100,0),
(@PATH,8,-453.0856,2078.318,92.4622,0,0,0,0,100,0),
(@PATH,9,-458.4782,2105.915,91.30417,0,0,0,0,100,0),
(@PATH,10,-453.1829,2091.579,91.92897,0,0,0,0,100,0),
(@PATH,11,-454.6579,2067.877,92.86068,0,0,0,0,100,0),
(@PATH,12,-471.7339,2040.147,93.86339,0,0,0,0,100,0),
(@PATH,13,-488.8954,2006.772,90.6447,0,0,0,0,100,0),
(@PATH,14,-506.3882,1982.291,85.0636,0,0,0,0,100,0);

SET @ENTRY := 19442;
SET @GUID := 183915;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-1057.877,`position_y`=1996.641,`position_z`=67.34181 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-1057.877,1996.641,67.34181,0,0,0,0,100,0),
(@PATH,2,-1050.188,2009.977,67.06455,0,0,0,0,100,0);


SET @ENTRY := 19424; 
SET @GUID := 184067;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-975.6777,`position_y`=1903.692,`position_z`=84.41418 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,9562,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-975.6777,1903.692,84.41418,0,0,0,0,100,0),
(@PATH,2,-973.8419,1939.495,70.39467,0,0,0,0,100,0),
(@PATH,3,-955.7029,1969.015,68.00587,0,0,0,0,100,0),
(@PATH,4,-933.9344,1986.529,66.71876,0,0,0,0,100,0),
(@PATH,5,-920.0254,2004.145,64.96164,0,0,0,0,100,0),
(@PATH,6,-912.637,2028.022,56.54257,0,0,0,0,100,0),
(@PATH,7,-891.1589,2064.74,34.64294,0,0,0,0,100,0),
(@PATH,8,-869.7386,2091.601,23.5704,0,0,0,0,100,0),
(@PATH,9,-858.7391,2124.865,17.03608,0,0,0,0,100,0),
(@PATH,10,-823.7175,2119.571,16.5663,0,0,0,0,100,0),
(@PATH,11,-792.2368,2090.261,22.4062,0,0,0,0,100,0),
(@PATH,12,-783.2084,2054.525,29.63973,0,0,0,0,100,0),
(@PATH,13,-779.9326,2023.77,34.75321,0,0,0,0,100,0),
(@PATH,14,-800.3509,1985.585,39.80645,0,0,0,0,100,0),
(@PATH,15,-814.7488,1949.572,47.55807,0,0,0,0,100,0),
(@PATH,16,-822.0464,1919.74,54.06172,0,0,0,0,100,0),
(@PATH,17,-847.4603,1891.778,64.08673,0,0,0,0,100,0),
(@PATH,18,-885.2077,1883.808,72.72009,0,0,0,0,100,0),
(@PATH,19,-915.132,1902.349,70.37255,0,0,0,0,100,0),
(@PATH,20,-940.0393,1898.689,74.6819,0,0,0,0,100,0),
(@PATH,21,-958.8931,1878.34,92.07265,0,0,0,0,100,0),
(@PATH,22,-967.469,1873.979,94.75582,0,0,0,0,100,0),
(@PATH,23,-976.3881,1877.903,94.82088,0,0,0,0,100,0);

SET @GUID := 184068;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-1033.498,`position_y`=2016.301,`position_z`=67.98228 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,9562,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-1033.498,2016.301,67.98228,0,0,0,0,100,0),
(@PATH,2,-1000.079,2017.703,67.06455,0,0,0,0,100,0),
(@PATH,3,-954.4206,2015.588,67.03322,0,0,0,0,100,0),
(@PATH,4,-915.6917,2025.381,58.45187,0,0,0,0,100,0),
(@PATH,5,-886.038,2057.447,35.91393,0,0,0,0,100,0),
(@PATH,6,-886.0889,2092.425,24.59444,0,0,0,0,100,0),
(@PATH,7,-915.6437,2115.709,20.89748,0,0,0,0,100,0),
(@PATH,8,-914.2065,2149.265,14.4707,0,0,0,0,100,0),
(@PATH,9,-922.1042,2170.104,12.60829,0,0,0,0,100,0),
(@PATH,10,-945.8377,2185.868,12.26309,0,0,0,0,100,0),
(@PATH,11,-961.3444,2217.514,9.387299,0,0,0,0,100,0),
(@PATH,12,-957.1495,2247.785,6.748508,0,0,0,0,100,0),
(@PATH,13,-984.4343,2282.687,6.486638,0,0,0,0,100,0),
(@PATH,14,-1016.313,2306.371,8.956036,0,0,0,0,100,0),
(@PATH,15,-1048.225,2313.089,14.2006,0,0,0,0,100,0),
(@PATH,16,-1081.711,2312.186,20.69922,0,0,0,0,100,0),
(@PATH,17,-1087.714,2285.604,24.63902,0,0,0,0,100,0),
(@PATH,18,-1067.954,2244.344,24.47042,0,0,0,0,100,0),
(@PATH,19,-1052.511,2214.931,19.66574,0,0,0,0,100,0),
(@PATH,20,-1051.316,2178.967,24.62208,0,0,0,0,100,0),
(@PATH,21,-1055.739,2145.756,39.92072,0,0,0,0,100,0),
(@PATH,22,-1057.033,2106.794,57.37517,0,0,0,0,100,0),
(@PATH,23,-1046.553,2082.452,64.01545,0,0,0,0,100,0),
(@PATH,24,-1029.464,2056.926,67.17399,0,0,0,0,100,0),
(@PATH,25,-1056.46,2029.947,67.56455,0,0,0,0,100,0),
(@PATH,26,-1084.9,1998.348,67.47117,0,0,0,0,100,0),
(@PATH,27,-1065.154,1984.061,69.4269,0,0,0,0,100,0),
(@PATH,28,-1084.9,1998.348,67.47117,0,0,0,0,100,0),
(@PATH,29,-1056.46,2029.947,67.56455,0,0,0,0,100,0),
(@PATH,30,-1029.464,2056.926,67.17399,0,0,0,0,100,0),
(@PATH,31,-1046.553,2082.452,64.01545,0,0,0,0,100,0),
(@PATH,32,-1057.033,2106.794,57.37517,0,0,0,0,100,0),
(@PATH,33,-1055.739,2145.756,39.92072,0,0,0,0,100,0),
(@PATH,34,-1051.316,2178.967,24.62208,0,0,0,0,100,0),
(@PATH,35,-1052.511,2214.931,19.66574,0,0,0,0,100,0),
(@PATH,36,-1067.954,2244.344,24.47042,0,0,0,0,100,0),
(@PATH,37,-1087.714,2285.604,24.63902,0,0,0,0,100,0),
(@PATH,38,-1081.711,2312.186,20.69922,0,0,0,0,100,0),
(@PATH,39,-1048.225,2313.089,14.2006,0,0,0,0,100,0),
(@PATH,40,-1016.313,2306.371,8.956036,0,0,0,0,100,0),
(@PATH,41,-984.4343,2282.687,6.486638,0,0,0,0,100,0),
(@PATH,42,-957.1495,2247.785,6.748508,0,0,0,0,100,0),
(@PATH,43,-961.3444,2217.514,9.387299,0,0,0,0,100,0),
(@PATH,44,-945.8377,2185.868,12.26309,0,0,0,0,100,0),
(@PATH,45,-922.1042,2170.104,12.60829,0,0,0,0,100,0),
(@PATH,46,-914.2065,2149.265,14.4707,0,0,0,0,100,0),
(@PATH,47,-915.6437,2115.709,20.89748,0,0,0,0,100,0),
(@PATH,48,-886.0889,2092.425,24.59444,0,0,0,0,100,0),
(@PATH,49,-886.038,2057.447,35.91393,0,0,0,0,100,0),
(@PATH,50,-915.6917,2025.381,58.45187,0,0,0,0,100,0),
(@PATH,51,-954.4206,2015.588,67.03322,0,0,0,0,100,0),
(@PATH,52,-1000.079,2017.703,67.06455,0,0,0,0,100,0),
(@PATH,53,-1033.498,2016.301,67.98228,0,0,0,0,100,0);

SET @GUID := 184069;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-887.3162,`position_y`=2100.392,`position_z`=22.98137 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,9562,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-887.3162,2100.392,22.98137,0,0,0,0,100,0),
(@PATH,2,-902.8832,2104.852,22.5635,0,0,0,0,100,0),
(@PATH,3,-915.3331,2120.114,20.053,0,0,0,0,100,0),
(@PATH,4,-914.8217,2141.304,15.65685,0,0,0,0,100,0),
(@PATH,5,-920.6898,2180.254,11.73329,0,0,0,0,100,0),
(@PATH,6,-928.6917,2208.044,9.395775,0,0,0,0,100,0),
(@PATH,7,-935.8201,2223.378,8.009735,0,0,0,0,100,0),
(@PATH,8,-957.2545,2229.223,7.933442,0,0,0,0,100,0),
(@PATH,9,-962.3887,2210.646,10.17673,0,0,0,0,100,0),
(@PATH,10,-949.9908,2203.8,9.920502,0,0,0,0,100,0),
(@PATH,11,-929.2674,2205.433,9.8395,0,0,0,0,100,0),
(@PATH,12,-897.6884,2189.902,10.51884,0,0,0,0,100,0),
(@PATH,13,-862.864,2165.974,11.53246,0,0,0,0,100,0),
(@PATH,14,-840.7776,2152.851,13.35741,0,0,0,0,100,0),
(@PATH,15,-837.7058,2133.558,15.67247,0,0,0,0,100,0),
(@PATH,16,-852.1836,2118.362,17.45734,0,0,0,0,100,0),
(@PATH,17,-871.5316,2098.868,21.64986,0,0,0,0,100,0);

SET @GUID := 184070;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-1072.546,`position_y`=2254.384,`position_z`=25.03121 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,9562,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-1072.546,2254.384,25.03121,0,0,0,0,100,0),
(@PATH,2,-1050.309,2248.466,22.70865,0,0,0,0,100,0),
(@PATH,3,-1016.866,2228.801,13.34218,0,0,0,0,100,0),
(@PATH,4,-975.5443,2209.247,10.59319,0,0,0,0,100,0),
(@PATH,5,-950.7357,2192.689,11.50015,0,0,0,0,100,0),
(@PATH,6,-915.4313,2157.962,13.552,0,0,0,0,100,0),
(@PATH,7,-912.6307,2132.925,17.52908,0,0,0,0,100,0),
(@PATH,8,-912.6307,2132.925,17.52908,0,0,0,0,100,0),
(@PATH,9,-915.4313,2157.962,13.552,0,0,0,0,100,0),
(@PATH,10,-950.7357,2192.689,11.50015,0,0,0,0,100,0),
(@PATH,11,-975.5443,2209.247,10.59319,0,0,0,0,100,0),
(@PATH,12,-1016.866,2228.801,13.34218,0,0,0,0,100,0),
(@PATH,13,-1050.309,2248.466,22.70865,0,0,0,0,100,0),
(@PATH,14,-1072.546,2254.384,25.03121,0,0,0,0,100,0);

SET @GUID := 184071;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-1000.677,`position_y`=2218.161,`position_z`=11.39956 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,9562,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-1000.677,2218.161,11.39956,0,0,0,0,100,0),
(@PATH,2,-1034.118,2233.885,16.91886,0,0,0,0,100,0),
(@PATH,3,-1000.677,2218.161,11.39956,0,0,0,0,100,0),
(@PATH,4,-960.3612,2199.009,11.10769,0,0,0,0,100,0),
(@PATH,5,-929.8221,2168.747,12.79615,0,0,0,0,100,0),
(@PATH,6,-917.9709,2134.846,17.4569,0,0,0,0,100,0),
(@PATH,7,-899.0653,2097.202,24.10116,0,0,0,0,100,0),
(@PATH,8,-867.7588,2092.518,23.16903,0,0,0,0,100,0),
(@PATH,9,-834.6699,2065.056,28.35329,0,0,0,0,100,0),
(@PATH,10,-834.6699,2065.056,28.35329,0,0,0,0,100,0),
(@PATH,11,-867.7588,2092.518,23.16903,0,0,0,0,100,0),
(@PATH,12,-899.0653,2097.202,24.10116,0,0,0,0,100,0),
(@PATH,13,-917.9709,2134.846,17.4569,0,0,0,0,100,0),
(@PATH,14,-929.8221,2168.747,12.79615,0,0,0,0,100,0),
(@PATH,15,-960.3612,2199.009,11.10769,0,0,0,0,100,0),
(@PATH,16,-1000.677,2218.161,11.39956,0,0,0,0,100,0),
(@PATH,17,-1034.118,2233.885,16.91886,0,0,0,0,100,0),
(@PATH,18,-1000.677,2218.161,11.39956,0,0,0,0,100,0);

SET @GUID := 184072;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-1141.451,`position_y`=2039.274,`position_z`=67.06458 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-1141.451,2039.274,67.06458,0,0,0,0,100,0),
(@PATH,2,-1098.165,2044.068,66.97787,0,0,0,0,100,0),
(@PATH,3,-1053.092,2025.227,67.56455,0,0,0,0,100,0),
(@PATH,4,-1011.46,2004.103,67.06455,0,0,0,0,100,0),
(@PATH,5,-983.9862,1982.55,68.81455,0,0,0,0,100,0),
(@PATH,6,-984.9029,1950.981,70.32558,0,0,0,0,100,0),
(@PATH,7,-974.4434,1917.587,77.03918,0,0,0,0,100,0),
(@PATH,8,-951.4631,1888.722,82.49074,0,0,0,0,100,0),
(@PATH,9,-918.9573,1886.185,78.15961,0,0,0,0,100,0),
(@PATH,10,-918.9573,1886.185,78.15961,0,0,0,0,100,0),
(@PATH,11,-951.4631,1888.722,82.49074,0,0,0,0,100,0),
(@PATH,12,-974.4434,1917.587,77.03918,0,0,0,0,100,0),
(@PATH,13,-984.9029,1950.981,70.32558,0,0,0,0,100,0),
(@PATH,14,-983.9862,1982.55,68.81455,0,0,0,0,100,0),
(@PATH,15,-1011.46,2004.103,67.06455,0,0,0,0,100,0),
(@PATH,16,-1053.092,2025.227,67.56455,0,0,0,0,100,0),
(@PATH,17,-1098.165,2044.068,66.97787,0,0,0,0,100,0),
(@PATH,18,-1141.451,2039.274,67.06458,0,0,0,0,100,0);

SET @GUID := 184073;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-824.4816,`position_y`=1990.778,`position_z`=38.91302 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,9562,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-824.4816,1990.778,38.91302,0,0,0,0,100,0),
(@PATH,2,-800.973,2019.102,38.81275,0,0,0,0,100,0),
(@PATH,3,-801.4883,2043.102,41.42069,0,0,0,0,100,0),
(@PATH,4,-820.149,2057.47,35.70707,0,0,0,0,100,0),
(@PATH,5,-830.2311,2072.128,25.74135,0,0,0,0,100,0),
(@PATH,6,-842.6055,2101.628,19.20734,0,0,0,0,100,0),
(@PATH,7,-854.4006,2133.824,15.76549,0,0,0,0,100,0),
(@PATH,8,-854.3831,2150.491,13.76549,0,0,0,0,100,0),
(@PATH,9,-871.9949,2163.9,11.56941,0,0,0,0,100,0),
(@PATH,10,-900.2237,2167.077,11.69764,0,0,0,0,100,0),
(@PATH,11,-900.2237,2167.077,11.69764,0,0,0,0,100,0),
(@PATH,12,-871.9949,2163.9,11.56941,0,0,0,0,100,0),
(@PATH,13,-854.3831,2150.491,13.76549,0,0,0,0,100,0),
(@PATH,14,-854.4006,2133.824,15.76549,0,0,0,0,100,0),
(@PATH,15,-842.6055,2101.628,19.20734,0,0,0,0,100,0),
(@PATH,16,-830.2311,2072.128,25.74135,0,0,0,0,100,0),
(@PATH,17,-820.149,2057.47,35.70707,0,0,0,0,100,0),
(@PATH,18,-801.4883,2043.102,41.42069,0,0,0,0,100,0),
(@PATH,19,-800.973,2019.102,38.81275,0,0,0,0,100,0),
(@PATH,20,-824.4816,1990.778,38.91302,0,0,0,0,100,0);

SET @GUID := 184074;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-1157.17,`position_y`=1943.396,`position_z`=81.40363 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-1157.17,1943.396,81.40363,0,0,0,0,100,0),
(@PATH,2,-1151.672,1940.954,81.40428,0,0,0,0,100,0),
(@PATH,3,-1143.042,1932.632,81.42173,0,0,0,0,100,0),
(@PATH,4,-1139.161,1923.026,81.20094,0,0,0,0,100,0),
(@PATH,5,-1138.57,1918.28,81.37885,0,0,0,0,100,0),
(@PATH,6,-1135.403,1912.328,81.4029,0,0,0,0,100,0),
(@PATH,7,-1138.515,1901.65,81.35353,0,0,0,0,100,0),
(@PATH,8,-1145.631,1891.622,81.32314,0,0,0,0,100,0),
(@PATH,9,-1139.867,1899.911,81.37244,0,0,0,0,100,0),
(@PATH,10,-1155.281,1909.135,81.45526,0,0,0,0,100,0),
(@PATH,11,-1139.867,1899.911,81.37244,0,0,0,0,100,0),
(@PATH,12,-1145.631,1891.622,81.32314,0,0,0,0,100,0),
(@PATH,13,-1138.515,1901.65,81.35353,0,0,0,0,100,0),
(@PATH,14,-1135.493,1912.019,81.39507,0,0,0,0,100,0),
(@PATH,15,-1138.57,1918.28,81.37885,0,0,0,0,100,0),
(@PATH,16,-1139.161,1923.026,81.20094,0,0,0,0,100,0),
(@PATH,17,-1142.842,1932.44,81.40112,0,0,0,0,100,0),
(@PATH,18,-1151.672,1940.954,81.40428,0,0,0,0,100,0);












