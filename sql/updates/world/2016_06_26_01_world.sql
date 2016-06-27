
delete from creature_equip_template where entry between 43432 and 43435;
INSERT INTO `creature_equip_template` VALUES (43432, 1, 14836, 0, 0);
INSERT INTO `creature_equip_template` VALUES (43433, 1, 30204, 0, 0);
INSERT INTO `creature_equip_template` VALUES (43434, 1, 33981, 33981, 0);
INSERT INTO `creature_equip_template` VALUES (43435, 1, 12786, 12893, 0);

delete from gossip_menu_option where menu_id=9546;
INSERT INTO `gossip_menu_option` VALUES (9546, 0, 2, 'Where would you like to fly to?', 10753, 4, 8192, 0, 0, 0, 0, 0, '', 0);
INSERT INTO `gossip_menu_option` VALUES (9546, 1, 2, 'Greer, I need a gryphon to ride and some bombs to drop on New Agamand!', 23112, 1, 8193, 0, 0, 0, 0, 0, NULL, 0);
INSERT INTO `gossip_menu_option` VALUES (9546, 2, 2, 'I need to get to Wintergarde Keep fast!', 26697, 1, 8193, 0, 0, 0, 0, 0, ' ', 0);

delete from conditions where SourceTypeOrReferenceId=13 AND SourceEntry=56727 AND ConditionTypeOrReference=31 AND ConditionValue1=3;

UPDATE quest_template SET SpecialFlags=2 WHERE Id=1270;

UPDATE quest_template SET SpecialFlags=2 WHERE Id=1222;

-- Morbidus - On Death - Kill Credit
DELETE FROM `smart_scripts` WHERE `entryorguid`=30698 AND `id`=7 AND `source_type`=0 LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(30698,0,7,0,6,0,100,0,0,0,0,0,85,95006,0,0,0,0,0,24,0,0,0,0.0,0.0,0.0,0.0,"Morbidus - On Death - Kill Credit");

DELETE FROM `creature_text` WHERE `entry` IN(31333,31334);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextID`, `comment`) VALUES
(31333, 0, 0, 'No, my beloved.', 12, 0, 100, 1, 0, 0, 32040, 'Alexstrasza the Life-Binder to Player'),
(31333, 1, 0, 'They must not discover the fate of the young paladin. Not yet.', 12, 11, 100, 5, 0, 0, 32041, 'Alexstrasza the Life-Binder to Player'),
(31333, 2, 0, 'Come to me, $n.', 15, 0, 100, 0, 0, 0, 32048, 'Alexstrasza the Life-Binder to Player'),
(31334, 0, 0, 'My Queen, do they know?', 12, 0, 100, 6, 0, 0, 32038, 'Korialstrasz to Player'),
(31334, 1, 0, '%s nods.', 16, 0, 100, 0, 0, 0, 32046, 'Korialstrasz to Player'),
(31334, 2, 0, 'They will not.', 12, 0, 100, 1, 0, 0, 32047, 'Korialstrasz to Player');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=10179;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=22 AND `SourceEntry`=31333;

INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(15, 10179, 0, 0, 0, 8, 0, 12499, 0, 0, 0, 0, 0, '', 'Alexstrasza the Life-Binder - Show Gossip if player is rewarded for Return To Angrathar'),
(15, 10179, 0, 0, 1, 8, 0, 12500, 0, 0, 0, 0, 0, '', 'Alexstrasza the Life-Binder - Show Gossip if player is rewarded for Return To Angrathar'),
(22, 3, 31333, 0, 0, 8, 0, 12499, 0, 0, 0, 0, 0, '', 'Alexstrasza the Life-Binder - Run AI only if player is rewarded for Return To Angrathar'),
(22, 3, 31333, 0, 1, 8, 0, 12500, 0, 0, 0, 0, 0, '', 'Alexstrasza the Life-Binder - Run AI only if player is rewarded for Return To Angrathar');

UPDATE creature_template_addon SET bytes1=16777223, bytes2=1 WHERE entry=31292;
UPDATE creature_template_addon SET bytes1=16777223, bytes2=1 WHERE entry=31293;

DELETE FROM creature_template_addon WHERE entry=31333;
INSERT INTO creature_template_addon VALUES 
(31333, 0, 0, 50331649, 1, 0, "60778");

UPDATE creature_template_addon SET bytes1=16777223, bytes2=1, auras="29266" WHERE entry in (31295, 31308, 31294, 31298, 31285, 31309, 31296, 31297);

UPDATE creature_template_addon SET bytes2=5 WHERE entry=26877;

DELETE FROM creature_template_addon WHERE entry=31313;
INSERT INTO creature_template_addon VALUES 
(31313, 0, 0, 0, 1, 0, "");

DELETE FROM creature_template_addon WHERE entry=31310;
INSERT INTO creature_template_addon VALUES 
(31310, 0, 0, 0, 1, 0, "");

UPDATE `creature_template` SET `ainame`='SmartAI', `scriptname`='' WHERE `entry` IN(31310,31313,31328,31330);

DELETE FROM `smart_scripts` WHERE `entryorguid` IN(31310,31313,31328,31330)  AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`IN(3131000,3131001,3131002,3131003,3131004,3131005,3131006,3131007,3131008)  AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(31313,0,0,1,11,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Fleeing Alliance Soldier - On Spawn - Set Run On'),
(31313,0,1,2,61,0,100,0,0,0,0,0,89,30,0,0,0,0,0,1,0,0,0,0,0,0,0,'Fleeing Alliance Soldier - On Spawn - Set Random Movement'),
(31313,0,2,0,61,0,100,0,0,0,0,0,11,52385,0,0,0,0,0,1,0,0,0,0,0,0,0,'Fleeing Alliance Soldier - On Spawn - Cast Cosmetic - Periodic Cower'),
(31313,0,3,0,1,0,100,0,0,3000,1000,3000,87,3131005,3131006,3131007,3131008,0,0,1,0,0,0,0,0,0,0,'Fleeing Alliance Soldier - OOC - Run Random Script'),
(31330,0,0,1,11,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Fleeing Horde Soldier - On Spawn - Set Run On'),
(31330,0,1,2,61,0,100,0,0,0,0,0,89,30,0,0,0,0,0,1,0,0,0,0,0,0,0,'Fleeing Horde Soldier - On Spawn - Set Random Movement'),
(31330,0,2,0,61,0,100,0,0,0,0,0,11,52385,0,0,0,0,0,1,0,0,0,0,0,0,0,'Fleeing Horde Soldier - On Spawn - Cast Cosmetic - Periodic Cower'),
(31330,0,3,0,1,0,100,0,0,3000,1000,3000,87,3131005,3131006,3131007,3131008,0,0,1,0,0,0,0,0,0,0,'Fleeing Horde Soldier - OOC - Run Random Script'),
(31310,0,0,1,11,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Fleeing Alliance Soldier - On Spawn - Set Run On'),
(31310,0,1,2,61,0,100,0,0,0,0,0,89,30,0,0,0,0,0,1,0,0,0,0,0,0,0,'Fleeing Alliance Soldier - On Spawn - Set Random Movement'),
(31310,0,2,0,61,0,100,0,0,0,0,0,11,52385,0,0,0,0,0,1,0,0,0,0,0,0,0,'Fleeing Alliance Soldier - On Spawn - Cast Cosmetic - Periodic Cower'),
(31310,0,3,0,1,0,100,0,0,3000,1000,3000,87,3131000,3131001,3131002,3131003,3131004,0,1,0,0,0,0,0,0,0,'Fleeing Alliance Soldier - OOC - Run Random Script'),
(31328,0,0,1,11,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Fleeing Horde Soldier - On Spawn - Set Run On'),
(31328,0,1,2,61,0,100,0,0,0,0,0,89,30,0,0,0,0,0,1,0,0,0,0,0,0,0,'Fleeing Horde Soldier - On Spawn - Set Random Movement'),
(31328,0,2,0,61,0,100,0,0,0,0,0,11,52385,0,0,0,0,0,1,0,0,0,0,0,0,0,'Fleeing Horde Soldier - On Spawn - Cast Cosmetic - Periodic Cower'),
(31328,0,3,0,1,0,100,0,0,3000,1000,3000,87,3131000,3131001,3131002,3131003,3131004,0,1,0,0,0,0,0,0,0,'Fleeing Horde Soldier - OOC - Run Random Script'),

(3131000,9,0,0,0,0,100,0,0,0,0,0,4,14994,0,0,0,0,0,1,0,0,0,0,0,0,0,'Fleeing Soldier - Script 1 - Play Sound 14994'),
(3131001,9,0,0,0,0,100,0,0,0,0,0,4,14991,0,0,0,0,0,1,0,0,0,0,0,0,0,'Fleeing Soldier - Script 2 - Play Sound 14991'),
(3131002,9,0,0,0,0,100,0,0,0,0,0,4,14993,0,0,0,0,0,1,0,0,0,0,0,0,0,'Fleeing Soldier - Script 3 - Play Sound 14993'),
(3131003,9,0,0,0,0,100,0,0,0,0,0,4,14992,0,0,0,0,0,1,0,0,0,0,0,0,0,'Fleeing Soldier - Script 4 - Play Sound 14992'),
(3131004,9,0,0,0,0,100,0,0,0,0,0,4,15005,0,0,0,0,0,1,0,0,0,0,0,0,0,'Fleeing Soldier - Script 5 - Play Sound 15005'),
(3131005,9,0,0,0,0,100,0,0,0,0,0,4,14990,0,0,0,0,0,1,0,0,0,0,0,0,0,'Fleeing Soldier - Script 6 - Play Sound 14990'),
(3131006,9,0,0,0,0,100,0,0,0,0,0,4,14988,0,0,0,0,0,1,0,0,0,0,0,0,0,'Fleeing Soldier - Script 7 - Play Sound 14988'),
(3131007,9,0,0,0,0,100,0,0,0,0,0,4,14989,0,0,0,0,0,1,0,0,0,0,0,0,0,'Fleeing Soldier - Script 8 - Play Sound 14989'),
(3131008,9,0,0,0,0,100,0,0,0,0,0,4,14987,0,0,0,0,0,1,0,0,0,0,0,0,0,'Fleeing Soldier - Script 9 - Play Sound 14987');

-- Apprentice Ralen SAI
DELETE FROM `smart_scripts` WHERE `entryorguid`=15941 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(15941,0,0,1,8,0,100,0,27907,0,15000,15000,33,15941,0,0,0,0,0,7,0,0,0,0,0,0,0,"Apprentice Ralen - On Spellhit 'Disciplinary Rod' - Quest Credit 'Swift Discipline'"),
(15941,0,1,0,61,0,100,0,27907,0,15000,15000,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Apprentice Ralen - On Spellhit 'Disciplinary Rod' - Say Line 0");

-- Apprentice Meledor SAI
DELETE FROM `smart_scripts` WHERE `entryorguid`=15945 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(15945,0,0,1,8,0,100,0,27907,0,15000,15000,33,15945,0,0,0,0,0,7,0,0,0,0,0,0,0,"Apprentice Meledor - On Spellhit 'Disciplinary Rod' - Quest Credit 'Swift Discipline'"),
(15945,0,1,0,61,0,100,0,27907,0,15000,15000,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Apprentice Meledor - On Spellhit 'Disciplinary Rod' - Say Line 0");

UPDATE `creature_template` SET `ainame`='SmartAI', `scriptname`='' WHERE `entry` IN(33877,33761,33861,33862);

DELETE FROM `smart_scripts` WHERE `entryorguid` IN(33877,33761,33861,33862)  AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN(19455501,19455503)  AND `source_type`=9;

INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(19455501, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 104, 16, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Archivum Console - Script 2 - Set Go Flags '),
(19455501, 9, 1, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 19, 33874, 0, 0, 0, 0, 0, 0, 'Archivum Console - Script 2 - Say Text Line 3 on Archivum System '),
(19455501, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 33876, 3, 67000, 0, 0, 0, 8, 0, 0, 0, 1438.32, 118.523, 425.434, 0, 'Archivum Console - Script 2 - Spawn Freya Image '),
(19455501, 9, 3, 0, 0, 0, 100, 0, 6000, 6000, 0, 0, 1, 4, 0, 0, 0, 0, 0, 19, 33874, 0, 0, 0, 0, 0, 0, 'Archivum Console - Script 2 - Say Text Line 4 on Archivum System '),
(19455501, 9, 4, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 33861, 3, 58000, 0, 0, 0, 8, 0, 0, 0, 1435.8, 118.855, 425.881, 0, 'Archivum Console - Script 2 - Spawn Elder Brightleaf Image'),
(19455501, 9, 5, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 33862, 3, 58000, 0, 0, 0, 8, 0, 0, 0, 1435.71, 120.41, 425.823, 0, 'Archivum Console - Script 2 - Spawn Elder Stonebark Image'),
(19455501, 9, 6, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 33761, 3, 58000, 0, 0, 0, 8, 0, 0, 0, 1435.77, 117.288, 425.838, 0, 'Archivum Console - Script 2 - Spawn Elder Ironbark Image'),
(19455501, 9, 7, 0, 0, 0, 100, 0, 9000, 9000, 0, 0, 1, 5, 0, 0, 0, 0, 0, 19, 33874, 0, 0, 0, 0, 0, 0, 'Archivum Console - Script 2 - Say Text Line 5 on Archivum System '),
(19455501, 9, 8, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 33761, 0, 0, 0, 0, 0, 0, 'Archivum Console - Script 2 - Set Data on Elder Brightleaf Image'),
(19455501, 9, 9, 0, 0, 0, 100, 0, 9000, 9000, 0, 0, 1, 6, 0, 0, 0, 0, 0, 19, 33874, 0, 0, 0, 0, 0, 0, 'Archivum Console - Script 2 - Say Text Line 6 on Archivum System '),
(19455501, 9, 10, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 33862, 0, 0, 0, 0, 0, 0, 'Archivum Console - Script 2 - Set Data on Elder Stonebark Image'),
(19455501, 9, 11, 0, 0, 0, 100, 0, 9000, 9000, 0, 0, 1, 7, 0, 0, 0, 0, 0, 19, 33874, 0, 0, 0, 0, 0, 0, 'Archivum Console - Script 2 - Say Text Line 7 on Archivum System'),
(19455501, 9, 12, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 33861, 0, 0, 0, 0, 0, 0, 'Archivum Console - Script 2 - Set Data on Elder Ironbranch Image'),
(19455501, 9, 13, 0, 0, 0, 100, 0, 9000, 9000, 0, 0, 1, 8, 0, 0, 0, 0, 0, 19, 33874, 0, 0, 0, 0, 0, 0, 'Archivum Console - Script 2 - Say Text Line 8 on Archivum System'),
(19455501, 9, 14, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 2, 2, 0, 0, 0, 0, 19, 33761, 0, 0, 0, 0, 0, 0, 'Archivum Console - Script 2 - Set Data on Elder Brightleaf Image'),
(19455501, 9, 15, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 2, 2, 0, 0, 0, 0, 19, 33862, 0, 0, 0, 0, 0, 0, 'Archivum Console - Script 2 - Set Data on Elder Stonebark Image'),
(19455501, 9, 16, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 2, 2, 0, 0, 0, 0, 19, 33861, 0, 0, 0, 0, 0, 0, 'Archivum Console - Script 2 - Set Data on Elder Ironbranch Image'),
(19455501, 9, 17, 0, 0, 0, 100, 0, 9000, 9000, 0, 0, 1, 9, 0, 0, 0, 0, 0, 19, 33874, 0, 0, 0, 0, 0, 0, 'Archivum Console - Script 2 - Say Text Line 9 on Archivum System'),
(19455501, 9, 18, 0, 0, 0, 100, 0, 13000, 13000, 0, 0, 104, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Archivum Console - Script 2 - Set Go Flags '),
(19455503, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 104, 16, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Archivum Console - Script 4 - Set Go Flags '),
(19455503, 9, 1, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 1, 15, 0, 0, 0, 0, 0, 19, 33874, 0, 0, 0, 0, 0, 0, 'Archivum Console - Script 4 - Say Text Line 15 on Archivum System '),
(19455503, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 33878, 3, 40000, 0, 0, 0, 8, 0, 0, 0, 1436.22, 118.364, 425.789, 0, 'Archivum Console - Script 4 - Spawn Thorim Image'),
(19455503, 9, 3, 0, 0, 0, 100, 0, 6000, 6000, 0, 0, 1, 16, 0, 0, 0, 0, 0, 19, 33874, 0, 0, 0, 0, 0, 0, 'Archivum Console - Script 4 - Say Text Line 16 on Archivum System '),
(19455503, 9, 4, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, 33877, 3, 31000, 0, 0, 0, 8, 0, 0, 0, 1436.14, 120.3, 425.839, 4.95674, 'Archivum Console - Script 4 - Spawn Sif Image'),
(19455503, 9, 5, 0, 0, 0, 100, 0, 4000, 4000, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 33877, 0, 0, 0, 0, 0, 0, 'Archivum Console - Script 4 - Set Data on Sif Image'),
(19455503, 9, 6, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 17, 0, 0, 0, 0, 0, 19, 33874, 0, 0, 0, 0, 0, 0, 'Archivum Console - Script 4 - Say Text Line 17 on Archivum System '),
(19455503, 9, 7, 0, 0, 0, 100, 0, 9000, 9000, 0, 0, 1, 18, 0, 0, 0, 0, 0, 19, 33874, 0, 0, 0, 0, 0, 0, 'Archivum Console - Script 4 - Say Text Line 18 on Archivum System '),
(19455503, 9, 8, 0, 0, 0, 100, 0, 13000, 13000, 0, 0, 104, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Archivum Console - Script 4 - Set Go Flags '),
(33761,0,0,0,38,0,100,0,1,1,0,0,11,64201,0,0,0,0,0,1,0,0,0,0,0,0,0,'Elder Brightleaf Image - On Data Set - Cast Sunbeam'),
(33862,0,0,0,38,0,100,0,1,1,0,0,11,64228,0,0,0,0,0,1,0,0,0,0,0,0,0,'Elder Stonebark Image - On Data Set - Cast Ground Tremor'),
(33861,0,0,0,38,0,100,0,1,1,0,0,11,64229,0,0,0,0,0,1,0,0,0,0,0,0,0,'Elder Ironbranch Image - On Data Set - Cast Iron Roots'),
(33761,0,1,0,38,0,100,0,2,2,0,0,11,64269,0,0,0,0,0,19,33876,0,0,0,0,0,0,'Elder Brightleaf Image - On Data Set - Cast Hologram Freya Channel'),
(33862,0,1,0,38,0,100,0,2,2,0,0,11,64269,0,0,0,0,0,19,33876,0,0,0,0,0,0,'Elder Stonebark Image - On Data Set - Cast Hologram Freya Channel'),
(33861,0,1,0,38,0,100,0,2,2,0,0,11,64269,0,0,0,0,0,19,33876,0,0,0,0,0,0,'Elder Ironbranch Image - On Data Set - Cast Hologram Freya Channel'),
(33877,0,0,0,38,0,100,0,1,1,0,0,11,64324,0,0,0,0,0,19,33878,0,0,0,0,0,0,'Sif Image - On Data Set - Cast Hologram Sif Channel');

SET @CGUID := 11333;

DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+3 AND `id`=24921;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`,  `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `MovementType`) VALUES
(@CGUID+0, 24921, 603, 3, 1, 1437.423, 117.3453, 425.8442, 0, 7200, 0, 0), -- 24921 (Area: 0) (Auras: )
(@CGUID+1, 24921, 603, 3, 1, 1437.352, 115.7263, 425.8618, 0, 7200, 0, 0), -- 24921 (Area: 0) (Auras: )
(@CGUID+2, 24921, 603, 3, 1, 1437.107, 118.4796, 425.813, 0, 7200, 0, 0), -- 24921 (Area: 0) (Auras: )
(@CGUID+3, 24921, 603, 3, 1, 1436.955, 118.8366, 425.8709, 0, 7200, 0, 0); -- 24921 (Area: 0) (Auras: )

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry` IN(64201,64229);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(13, 1, 64201, 0, 0, 31, 0, 3, 24921, 0, 0, 0, 0, '', 'Sunbeam Targets Cosmetic Trigger - LAB'),
(13, 1, 64229, 0, 0, 31, 0, 3, 24921, 0, 0, 0, 0, '', 'Iron Roots Targets Cosmetic Trigger - LAB');

delete from spell_bonus_data where entry=14792;
INSERT INTO `spell_bonus_data` (`entry`, `comments`) VALUES
(14792, 'Venomhide Poison - should not get bonuses');

DELETE FROM `gossip_menu_option` WHERE (`menu_id`=8298 AND `id`in (0, 1));
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `OptionBroadcastTextID`, `npc_option_npcflag`, `box_coded`, `box_money`, `box_text`) VALUES
(8298, 0, 0, 'Can you cast the spell to help me breathe and move underwater?', 1, 19071, 1, 0, 0, ''); -- 17712

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 15 AND `SourceGroup` = 8298;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `Comment`) VALUES
(15, 8298, 0, 0, 0, 9, 0, 9674, 0, 0, 0, 0, 0, 'Captain Edward Hanes - Show Gossip if player has quest 9674 incomplete'),
(15, 8298, 0, 0, 1, 9, 0, 9682, 0, 0, 0, 0, 0, 'Captain Edward Hanes - Show Gossip if player has quest 9682 incomplete');

DELETE FROM `smart_scripts` WHERE `entryorguid` = 17712 AND `id` IN (1, 2, 3, 4);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(17712,0,1,2,62,0,100,0,8298,0,0,0,11,31319,0,0,0,0,0,7,0,0,0,0,0,0,0,"Captain Edward Hanes - On Gossip Select - Cast \"The Captain\'s Kiss\""),
(17712,0,2,0,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Captain Edward Hanes - On Gossip Select - Close Gossip"),
(17712,0,3,0,19,0,100,0,9674,0,0,0,11,31319,0,0,0,0,0,7,0,0,0,0,0,0,0,"Captain Edward Hanes - On Quest Accept - Cast \"The Captain\'s Kiss\""),
(17712,0,4,0,19,0,100,0,9682,0,0,0,11,31319,0,0,0,0,0,7,0,0,0,0,0,0,0,"Captain Edward Hanes - On Quest Accept - Cast \"The Captain\'s Kiss\"");

Set @Zootfizzle:= 28374;
Set @Dorian:= 28376;
Set @Hemet:= 28451;
Set @Stampy:= 28468;

DELETE FROM `vehicle_template_accessory` where `entry` in (@Stampy) AND `accessory_entry` in (@Hemet);
INSERT INTO `vehicle_template_accessory` (`entry`,`accessory_entry`,`seat_id`,`minion`,`description`,`summontype`,`summontimer`)VALUES
(@Stampy,@Hemet,1,1,'Stampy',8,0);

UPDATE creature_template SET npcflag= 16777216,  spell1=51756, spell2=51751, spell3=51752  WHERE entry=@Stampy; 

UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry` in (@Zootfizzle, @Dorian, @Hemet, @Stampy);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` in (@Stampy);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(@Stampy, 46598, 1, 0);

DELETE FROM `smart_scripts` WHERE `entryorguid` = @Dorian AND `source_type` = 0;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @Dorian*100 AND `source_type` = 9;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @Dorian*100+1 AND `source_type` = 9;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @Hemet AND `source_type` = 0;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @Hemet*100 AND `source_type` = 9;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@Dorian, 0, 0, 0, 19, 0, 100, 0, 12614, 0, 0, 0, 11, 51757, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Dorian - On quest Accept - cast'),
(@Hemet, 0, 0, 0, 0, 0, 100, 0, 0, 0, 6000, 6000, 11, 51742, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Dorian - IC - cast'),
(@Hemet, 0, 1, 0, 0, 0, 100, 0, 2000, 2000, 15000, 15000, 11, 51740, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Dorian - IC - cast'),
(@Dorian, 0, 1, 0, 20, 0, 100, 0, 12614, 0, 0, 0, 80, @Dorian*100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Dorian - On quest rewarded - ActionList'),
(@Dorian*100, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 19, @Hemet, 20, 0, 0, 0, 0, 0, 'Dorian - ActionList - Despawn'),
(@Dorian*100, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, @Hemet, 5, 0, 0, 0, 0, 8, 0, 0, 0, 6448.532715, 5082.552734, -63.941204, 0.673032, 'Dorian - ActionList - Summon'),
(@Dorian*100, 9, 2, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 75, 59872, 0, 0, 0, 0, 0, 19, @Hemet, 20, 0, 0, 0, 0, 0, 'Dorian - ActionList - AddAura to trigger to triiger the event'),
(@Hemet, 0, 2, 0, 23, 0, 100, 0, 59872, 1, 0, 0, 80, @Hemet*100, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Hemet - HasAura - Actionlist'),
(@Hemet*100, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 28, 59872, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Hemet - Actionlist - Remove aura'),
(@Hemet*100, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Hemet - Actionlist - Talk'),
(@Hemet*100, 9, 2, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Hemet - Actionlist - Talk'),
(@Hemet*100, 9, 3, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Hemet - Actionlist - Talk'),
(@Hemet*100, 9, 4, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Hemet - Actionlist - Talk'),
(@Hemet*100, 9, 5, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 4, 0, 0, 0, 0, 0, 21, 20, 0, 0, 0, 0, 0, 0, 'Hemet - Actionlist - Talk'),
(@Hemet*100, 9, 6, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 5, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Hemet - Actionlist - Talk'),
(@Hemet*100, 9, 7, 0, 0, 0, 100, 0, 8000, 8000, 0, 0, 1, 6, 0, 0, 0, 0, 0, 21, 20, 0, 0, 0, 0, 0, 0, 'Hemet - Actionlist - Talk'),
(@Hemet*100, 9, 8, 0, 0, 0, 100, 0, 8000, 8000, 0, 0, 1, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Hemet - Actionlist - Talk'),
(@Hemet*100, 9, 9, 0, 0, 0, 100, 0, 4000, 4000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 19, @Dorian, 20, 0, 0, 0, 0, 0, 'Hemet - Actionlist - Talk'),
(@Hemet*100, 9, 10, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Hemet - Actionlist - Despawn'),
-- Securing the Bait
(@Dorian, 0, 2, 0, 20, 0, 100, 0, 12605, 0, 0, 0, 80, @Dorian*100+1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Dorian - On quest rewarded - ActionList'),
(@Dorian*100+1, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 21, 10, 0, 0, 0, 0, 0, 0, 'Dorian - ActionList - talk'),
(@Dorian*100+1, 9, 1, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 19, @Zootfizzle, 20, 0, 0, 0, 0, 0, 'Dorian - ActionList - talk'),
(@Dorian*100+1, 9, 2, 0, 0, 0, 100, 0, 6000, 6000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Dorian - ActionList - talk'),
(@Dorian*100+1, 9, 3, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 19, @Zootfizzle, 20, 0, 0, 0, 0, 0, 'Dorian - ActionList - talk');

Delete from `creature_text` where `entry` in (@Hemet, @Dorian, @Zootfizzle);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) VALUES
(@Hemet, 0, 0, 'What a fight you missed, Dorian! It was one for the ages!', 12, 0, 100, 0, 0, 0, 'Hemet', 28026),
(@Hemet, 1, 0, 'There we were, riding into battle at full speed on the back of Stampy...', 12, 0, 100, 0, 0, 0, 'Hemet', 28027),
(@Hemet, 2, 0, 'Everything was shaking all over the place. I could hardly steady my gun.', 12, 0, 100, 0, 0, 0, 'Hemet', 28028),
(@Hemet, 3, 0, 'And then we saw her, the fearsome beast!', 12, 0, 100, 0, 0, 0, 'Hemet', 28029),
(@Hemet, 4, 0, 'It took all of $n''s skill to maintain control of Stampy.', 12, 0, 100, 0, 0, 0, 'Hemet', 28030),
(@Hemet, 5, 0, 'The battle was a haze of blood, lead, and sweat. The broodmother''s attacks came faster and faster!', 12, 0, 100, 0, 0, 0, 'Hemet', 28032),
(@Hemet, 6, 0, 'But, in the end, $n and I prevailed through our wits and teamwork. And now we have this glorious trophy as a memento of our victory.', 12, 0, 100, 0, 0, 0, 'Hemet', 28033),
(@Hemet, 7, 0, 'Do I detect a bit of jealousy, Dorian?', 12, 0, 100, 0, 0, 0, 'Hemet', 28036),
(@Dorian, 0, 0, 'Well, I don''t know. I was here tending the fire and discussing the drawbacks of cogs with Zootfizzle. That''s pretty epic, too, in its own way.', 12, 0, 100, 0, 0, 0, 'Dorian', 28037),
(@Dorian, 1, 0, 'It''s your lucky day, Zootfizzle. $n has brought back more hatchlings for you.', 12, 0, 100, 0, 0, 0, 'Dorian', 28892),
(@Dorian, 2, 0, 'Well, you can always go back to the camp and help Weslex with all his cogs...', 12, 0, 100, 0, 0, 0, 'Dorian', 28894),
(@Zootfizzle, 0, 0, 'I''m not here to be the keeper of your hatchlings, Dorian. I''m doing research of my own, as well.', 12, 0, 100, 0, 0, 0, 'Zootfizzle', 28893),
(@Zootfizzle, 1, 0, 'No, not the cogs! Anything but the cogs!', 12, 0, 100, 0, 0, 0, 'Zootfizzle', 28895);

UPDATE creature_template_addon SET auras="" WHERE entry=31306;

delete from skill_discovery_template where spellid=82177 and reqSpell in (82175, 81275);







