


DELETE FROM creature_queststarter WHERE id=26221 and quest=12012;

UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=25866;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=25863;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=25924;

DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid` IN (25863,25924,25866);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(25863,0,0,0,0,0,100,0,0,1000,7000,7500,11,20793,0,0,0,0,0,2,0,0,0,0,0,0,0,'Firesworn - IC - Cast spell Fireball on victim'),
(25863,0,1,0,4,0,100,0,0,0,0,0,11,184,0,0,0,0,0,1,0,0,0,0,0,0,0,'Firesworn - On aggro - Cast fire shield on self'),
(25863,0,2,0,4,0,100,0,0,0,0,0,1,0,1000,0,0,0,0,1,0,0,0,0,0,0,0,'Firesworn - On aggro - Say Text 0'),
(25924,0,0,0,0,0,100,0,0,1000,7000,7500,11,20793,0,0,0,0,0,2,0,0,0,0,0,0,0,'Speaker Viktor - IC - Cast spell Fireball on victim'),
(25924,0,1,0,4,0,100,0,0,0,0,0,1,0,1000,0,0,0,0,1,0,0,0,0,0,0,0,'Speaker Viktor - On aggro - Say Text 0'),
(25866,0,0,0,4,0,100,0,0,0,0,0,1,0,1000,0,0,0,0,1,0,0,0,0,0,0,0,'Flameguard - On aggro - Say Text 0');

DELETE FROM `creature_loot_template` WHERE `entry`IN (25866,25863,25924);
INSERT INTO `creature_loot_template` VALUES
(25866,35277,0,100,1,1,0,1,1,'Twilight Correspondence'),
(25863,35277,0,100,1,1,0,1,1,'Twilight Correspondence'),
(25924,35277,0,100,1,1,0,1,1,'Twilight Correspondence');

UPDATE creature_template SET minlevel=65, maxlevel=65, AIName="SmartAI" WHERE entry=26534;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=25324;

DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid` IN (26534,25324);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(26534,0,0,0,1,0,100,1,6000,10000,0,0,12,25324,3,60000,0,0,0,23,0,0,0,0,0,0,0,'Totem - On event update - Summon guide'),
(25324,0,0,0,54,0,100,0,0,0,0,0,29,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Earthen ring Guide - On just summonned - Follow Totem'),
(25324,0,1,0,64,0,100,0,0,0,0,0,1,0,1500,0,0,0,0,1,0,0,0,0,0,0,0,'Earthen ring Guide - On gossip hello - Say text 0');

DELETE FROM `creature_text` WHERE `entry` IN (25324,25863,25924,25866);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`,`BroadcastTextId`) VALUES
(25324,0,1,'What is it you need?',12,0,100,1,1500,0,'Earthen ring guide',25739),
(25324,0,2,'Have you discovered something?',12,0,100,1,1500,0,'Earthen ring guide',25740),
(25324,0,3,'The elemental spirits are restless...',12,0,100,1,1500,0,'Earthen ring guide',25741),
(25863,0,0,'You are not allowed to interfere!',12,0,100,1,1500,0,'Twilight Firesworn',25098),
(25924,0,0,'Our vision will be realized!',12,0,100,1,1500,0,'Twilight Speaker Viktor',25099),
(25866,0,0,'The elements will crush you!',12,0,100,1,1500,0,'Twilight Speaker Viktor',25100);

-- SAI for Briatha
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=25949;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=25949;
DELETE FROM `smart_scripts` WHERE `source_type`=9 AND `entryorguid`=2594900;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(25949,0,0,0,10,0,100,0,1,20,40000,40000,80,2594900,2,0,0,0,0,1,0,0,0,0,0,0,0,'Briatha - OOC LOS - Call Timed ActionList'),
(2594900,9,0,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Briatha - Action list - Talk0'),
(2594900,9,1,0,0,0,100,0,6000,6000,0,0,1,0,4000,0,0,0,0,9,25951,0,15,0,0,0,0,'Emissary - Action list - Say text 0'),
(2594900,9,2,0,0,0,100,0,6000,6000,0,0,1,1,4000,0,0,0,0,1,0,0,0,0,0,0,0,'Briatha - Action list - Say text 1'),
(2594900,9,3,0,0,0,100,0,6000,6000,0,0,1,1,4000,0,0,0,0,9,25951,0,15,0,0,0,0,'Emissary - Action list - Say text 1'),
(2594900,9,4,0,0,0,100,0,6000,6000,0,0,1,2,3500,0,0,0,0,1,0,0,0,0,0,0,0,'Briatha - Action list - Say text 2'),
(2594900,9,5,0,0,0,100,0,0,0,0,0,11,46375,0,0,0,0,0,1,0,0,0,0,0,0,0,'Briatha - Action list - Cast spell quest credit');

-- Briatha and Heretic Emissary text
DELETE FROM `creature_text` WHERE `entry` IN (25949,25951);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`,`BroadcastTextId`) VALUES
(25949,0,0,'These stones should be the last of them. Our coordination with Neptulon''s forces will be impeccable.',12,0,100,1,0,0,'Briatha',25123),
(25949,1,0,'And your own preparations? Will the Frost Lord have a path to the portal?',12,0,100,1,0,0,'Briatha',25126),
(25949,2,0,'The ritual in Coilfang will bring Ahune through once he is fully prepared, and the resulting clash between Firelord and Frostlord will rend the foundations of this world. Our ultimate goals are in reach at last....',12,0,100,1,0,0,'Briatha',25128),
(25951,0,0,'Yess. The Tidehunter will be pleased at this development. The Firelord\'s hold will weaken.',12,0,100,1,0,0,'Heretic Emissary',25124),
(25951,1,0,'Skar\'this has informed us well. We have worked our way into the slave pens and await your cryomancerss.',12,0,100,1,0,0,'Heretic Emissary',25127);



