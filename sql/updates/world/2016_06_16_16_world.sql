
UPDATE creature_template SET InhabitType=4 WHERE entry=47950;

UPDATE creature_template SET faction=2318 WHERE entry=43792;

UPDATE creature_template SET minlevel=66, maxlevel=71 WHERE entry=26167;

DELETE FROM `creature_template_addon` WHERE `entry`=26167;
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
(26167, 0, 0, 0, 4097, 0, '46669');

DELETE FROM `creature_text` WHERE `entry`=26167;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) VALUES
(26167, 0, 0, '%s cries.', 16, 1, 100, 18, 0, 0, 'Taunka''le Evacuee',25304),
(26167, 1, 0, 'Stop!', 12, 1, 100, 5, 0, 0, 'Taunka''le Evacuee',25294),
(26167, 2, 0, 'Look out!', 12, 1, 100, 0, 0, 0, 'Taunka''le Evacuee',25299),
(26167, 3, 0, '%s points northeast.', 16, 1, 100, 25, 0, 0, 'Taunka''le Evacuee',25311),
(26167, 4, 0, 'The smoke in the distance... It is Wartook. He is trying to tell us something...', 12, 1, 100, 1, 0, 0, 'Taunka''le Evacuee',25312),
(26167, 5, 0, '%s expertly identifies the messages hidden within the smoke signals.', 16, 1, 100, 20, 0, 0, 'Taunka''le Evacuee',25315),
(26167, 6, 0, 'No... It cannot be true...', 12, 1, 100, 274, 0, 0, 'Taunka''le Evacuee',25313),
(26167, 7, 0, 'Icemist... Not Icemist... NO!!! Come quickly, hero! Follow me!', 12, 1, 100, 15, 0, 0, 'Taunka''le Evacuee',25314);

DELETE FROM `creature_text` WHERE `entry` IN(25379,25759);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`,`BroadcastTextID`) VALUES
(25379, 0, 0, 'Try to not lose this one, $n. It is important that we at least try and keep up appearances with the Alliance.', 15, 1, 100, 0, 0, 0, 'Warden Nork Bloodfrenzy',24977),
(25759, 0, 0, 'Thank you, $r. I will take this miserable cur from you now.', 12, 1, 100, 1, 0, 0, 'Valiance Keep Officer',24966);

DELETE FROM `gossip_menu_option` WHERE `menu_id`=9184;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `OptionBroadcastTextID`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`, `BoxBroadcastTextID`) VALUES 
(9184, 0, 0, 'I am embarassed to say it, Nork, but my deserter has gone missing.', 24976, 1, 1, 0, 0, 0, 0, '', 0); -- 25379

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=9184;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(15, 9184, 0, 0, 0,9, 0, 11711, 0, 0, 0, 0, 0, '', 'Warden Nork Bloodfrenzy - Show Gossip option only if player has Coward Delivery... Under 30 Minutes or its Free in quest log'),
(15, 9184, 0, 0, 0,1, 0, 45963, 0, 0, 1, 0, 0, '', 'Warden Nork Bloodfrenzy - Show Gossip option only if player does not have aura Call Alliance Deserter');

DELETE FROM `spell_scripts` WHERE `id`=45958;
INSERT INTO `spell_scripts` (`id`, `effIndex`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`) VALUES 
(45958, 0, 10, 0, 0, 25759, 24966, 0, 0, 0, 0),
(45958, 0, 1, 20, 2, 25759, 0, 0, 0, 0, 0),
(45958, 0, 0, 15, 45956, 0, 0, 0, 0, 0, 0),
(45958, 0, 10, 15, 45981, 0, 0, 0, 0, 0, 0);

DELETE FROM `gameobject`  WHERE `id`=187894;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES 
(10762, 187894, 571, 1, 1, 2942.86, 5381.48, 60.6052, 2.28369, 0, 0, 0.909402, 0.415919, 300, 0, 1);

UPDATE creature_template SET minlevel=65, maxlevel=72 WHERE entry=25761;

UPDATE `creature_template` SET `AIName`='SmartAI',`ScriptName`='' WHERE `entry` IN(26158,26167,26162);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN(26158,26167,26162) AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN(2616700,2616701,2616702,2616703) AND `source_type`=9;

INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(26158, 0, 0, 0, 19, 0, 100, 0, 11930, 0, 0, 0, 85, 46657, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Mother Tauranook - On Quest Accept (Across Transborea) - Invoker Cast Taunka''le Evacuee'),
(26167, 0, 0, 0, 11, 0, 100, 0, 0, 0, 0, 0, 11, 46669, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka''le Evacuee - On Spawn - Cast Evacuee Random Action'),
(26167, 0, 1, 0, 8, 0, 100, 0, 46663, 0, 0, 0, 87, 2616700, 2616701, 2616702, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka''le Evacuee - On Spellhit (Evacuee Random Action) - Run Random Script'),
(26167, 0, 2, 0, 8, 0, 100, 1, 46677, 0, 0, 0, 80, 2616703, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka''le Evacuee - On Spellhit (Evacuee Reaches Dragonblight) - Run Script'),
(26162, 0, 0, 0, 1, 0, 100, 0, 0, 0, 1000, 1000, 11, 46677, 0, 0, 0, 0, 0, 19, 26167, 0, 0, 0, 0, 0, 0, 'Transborea Generator 001 - OOC - Cast Evacuee Reaches Dragonblight'),
(2616700, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka''le Evacuee - Script 1 - Say Line'),
(2616701, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka''le Evacuee - Script 2 - Say Line'),
(2616701, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 46694, 0, 0, 0, 0, 0, 19, 0, 0, 0, 0, 0, 0, 0, 'Taunka''le Evacuee - Script 2 - Cast Feed'),
(2616702, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 46670, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka''le Evacuee - Script 3 - Cast Transborea Monster'),
(2616702, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka''le Evacuee - Script 3 - Say Line'),
(2616703, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 28, 46669, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka''le Evacuee - Script 4 - Remove Aura Evacuee Random Action'),
(2616703, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka''le Evacuee - Script 4 - Say Line'),
(2616703, 9, 2, 0, 0, 0, 100, 0, 6000, 6000, 0, 0, 1, 4, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka''le Evacuee - Script 4 - Say Line'),
(2616703, 9, 3, 0, 0, 0, 100, 0, 6000, 6000, 0, 0, 1, 5, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka''le Evacuee - Script 4 - Say Line'),
(2616703, 9, 4, 0, 0, 0, 100, 0, 6000, 6000, 0, 0, 1, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka''le Evacuee - Script 4 - Say Line'),
(2616703, 9, 5, 0, 0, 0, 100, 0, 6000, 6000, 0, 0, 1, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka''le Evacuee - Script 4 - Say Line'),
(2616703, 9, 6, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 46676, 0, 0, 0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 'Taunka''le Evacuee - Script 4 - Cast Across Transborea Complete'),
(2616703, 9, 7, 0, 0, 0, 100, 0, 0, 0, 0, 0, 41, 3000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka''le Evacuee - Script 4 - Despawn');

UPDATE `creature_template` SET `ainame`='SmartAI', `scriptname`='' WHERE `entry` IN(25379,25761,25759);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN(25379,25761,25759) AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` =2575900 AND `source_type`=9;

INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(25379, 0, 0, 0, 19, 0, 100, 0, 11711, 0, 0, 0, 85, 45963, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Warden Nork Bloodfrenzy - On Quest Accept (Coward Delivery... Under 30 Minutes or its Free - Invoker Cast Call Alliance Deserter'),
(25379, 0, 1, 2, 62, 0, 100, 0, 9184, 0, 0, 0, 85, 45963, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Warden Nork Bloodfrenzy - On Gossip Option 0 Selected - Invoker Cast Call Alliance Deserter'),
(25379, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Warden Nork Bloodfrenzy - On Gossip Option 0 Selected - Close Gossip'),
(25379, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Warden Nork Bloodfrenzy - On Gossip Option 0 Selected - Say'),
(25761, 0, 0, 0, 54, 0, 100, 0, 0, 0, 0, 0, 11, 45957, 0, 0, 0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 'Alliance Deserter - On Just Summoned - Cast Escorting Alliance Deserter'),
(25761, 0, 1, 0, 8, 0, 100, 0, 45981, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Alliance Deserter - On Spellhit (Escorting Alliance Deserter) - Despawn'),
(25761, 0, 2, 0, 38, 0, 100, 0, 1, 1, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Alliance Deserter - On Spellhit (Escorting Alliance Deserter) - Despawn'),
(25759, 0, 0, 1, 54, 0, 100, 0, 0, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Valiance Keep Officer - On Just Summoned - Store Targetlist'),
(25759, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 80, 2575900, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Valiance Keep Officer - On Just Summoned - Run Script'),
(2575900, 9, 0, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 12, 1, 0, 0, 0, 0, 0, 0, 'Valiance Keep Officer - Script - Say'),
(2575900, 9, 1, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 11, 45981, 2, 0, 0, 0, 0, 12, 1, 0, 0, 0, 0, 0, 0, 'Valiance Keep Officer - Script - Cast Escorting Alliance Deserter'),
(2575900, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 15,11711, 0, 0, 0, 0, 0, 12, 1, 0, 0, 0, 0, 0, 0, 'Valiance Keep Officer - Script - Complete quest'),
(2575900, 9, 3, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45,1, 1, 0, 0, 0, 0, 19, 25761, 0, 0, 0, 0, 0, 0, 'Valiance Keep Officer - Script - Set Data on Alliance Deserter '),
(2575900, 9, 4, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 41, 10000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Valiance Keep Officer - Script - Despawn');

UPDATE `gameobject_template` SET `AIName`= 'SmartGameObjectAI' WHERE  `entry` =178325;
DELETE FROM `smart_scripts` WHERE `entryorguid` =178325 AND `source_type`=1;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(178325,1,0,0,70,0,100,0,2,0,0,0,85,21078,0,0,0,0,0,7,0,0,0,0,0,0,0,'Open To Pass Your Rite. - On State Changed - Invoker Cast Conjure Milton (DND)');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=22 AND `SourceEntry`=178325;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(22, 1, 178325, 1, 0, 29, 1, 13082, 200, 0, 1, 0, 0, '', 'Only run SAI if Milton Beats is not already spawned');

DELETE FROM `event_scripts`  WHERE `id`=8175;
INSERT INTO event_scripts values
(8175, 5, 10, 14351, 900000, 0, 588.44, 606.87, -4.75, 5.62);

UPDATE `gameobject_template` SET `AIName`= 'SmartGameObjectAI' WHERE  `entry` =179499;

DELETE FROM `smart_scripts` WHERE `entryorguid` =179499 AND `source_type`=1;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(179499,1,0,0,70,0,100,1,2,0,0,0,12,14351,1,900000,0,1,0,8,0,0,0,588.44,606.87,-4.75,5.62,'Ogre Tannin Basket - On State Changed - Spawn Gordok Bushwacker');

UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry` IN(37098,38418);
UPDATE `creature_template` SET `InhabitType`=5 WHERE `entry`=38058;

-- Blighted Abomination SAI
SET @ENTRY := 37022;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,4000,4000,6000,6000,11,71140,0,0,0,0,0,2,0,0,0,0,0,0,0,"Blighted Abomination - In Combat - Cast 'Scourge Hook'"),
(@ENTRY,0,1,0,0,0,100,0,10000,11000,10000,11000,11,71150,0,0,0,0,0,1,0,0,0,0,0,0,0,"Blighted Abomination - In Combat - Cast 'Plague Cloud'"),
(@ENTRY,0,2,0,0,0,100,0,14000,15000,14000,15000,11,40504,0,0,0,0,0,2,0,0,0,0,0,0,0,"Blighted Abomination - In Combat - Cast 'Cleave'");

-- Decaying Colossus SAI
SET @ENTRY := 36880;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,15000,17000,15000,17000,11,71114,0,0,0,0,0,1,0,0,0,0,0,0,0,"Decaying Colossus - In Combat - Cast 'Massive Stomp'");

-- Darkfallen Lieutenant SAI
SET @ENTRY := 37665;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,9000,9000,8000,9000,11,70435,0,0,0,0,0,2,0,0,0,0,0,0,0,"Darkfallen Lieutenant - In Combat - Cast 'Rend Flesh'"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,20000,20000,11,70423,0,0,0,0,0,2,0,0,0,0,0,0,0,"Darkfallen Lieutenant - In Combat - Cast 'Vampiric Curse'");

-- Darkfallen Commander SAI
SET @ENTRY := 37662;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,5000,5000,15000,16000,11,70449,0,0,0,0,0,18,45,0,0,0,0,0,0,"Darkfallen Commander - In Combat - Cast 'Vampire Rush'"),
(@ENTRY,0,1,0,0,0,100,0,5000,5000,25000,25000,11,70750,0,0,0,0,0,1,0,0,0,0,0,0,0,"Darkfallen Commander - In Combat - Cast 'Battle Shout'");

SET @Villager=27359;
SET @GEIST=27370;

UPDATE `creature_template` SET `ainame`='SmartAI',`scriptname`='' WHERE `entry` IN (@Villager,@GEIST);
UPDATE `creature_template` SET `exp`=1,`unit_flags`=`unit_flags`|33536 WHERE `entry`=@Villager;

DELETE FROM `creature_text` WHERE `entry`=@Villager;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`,`BroadcastTextID`) VALUES
(@Villager,0,0,'Good of you to come, champion! The beast almost had me!',12,7,0,0,0,0,'Trapped Wintergarde Villager',26470),
(@Villager,0,1,'Finally! A hero has come!',12,7,0,0,0,0,'Trapped Wintergarde Villager',26469),
(@Villager,0,2,'Thank you, kind soul.',12,7,0,0,0,0,'Trapped Wintergarde Villager',26467),
(@Villager,0,3,'I''ll never forget you, friend.',12,7,0,0,0,0,'Trapped Wintergarde Villager',26468);

DELETE FROM `smart_scripts` WHERE `entryorguid`=@GEIST AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@GEIST,0,0,0,4,0,100,0,0,0,0,0,64,1,0,0,0,0,0,2,0,0,0,0,0,0,0,'Vengeful Geist - On Aggro - Store Target List '),
(@GEIST,0,1,2,6,0,100,0,0,0,0,0,100,1,0,0,0,0,0,19,@Villager,10,0,0,0,0,0,'Vengeful Geist - On Death - Send stored targets'),
(@GEIST,0,2,0,61,0,100,0,0,0,0,0,45,0,1,0,0,0,0,19,@Villager,10,0,0,0,0,0,'Vengeful Geist - Link With Previous Event - Set Data 0 1 ');

DELETE FROM `smart_scripts` WHERE `entryorguid`=@Villager AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@Villager*100 AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@Villager,0,0,0,38,1,100,1,0,1,0,0,80,2735900,0,0,0,0,0,1,0,0,0,0,0,0,0,'Trapped Wintergarde Villager - On Data Set 0 1 - Call Timed Actionlist'),
(@Villager,0,1,0,34,0,100,0,0,1,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Trapped Wintergarde Villager - On Movementinform - Despawn'),
(@Villager,0,2,0,25,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Trapped Wintergarde Villager - On Reset - Set Phase 1'),
(@Villager*100,9,0,0,0,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Trapped Wintergarde Villager - Script - Set Passive'),
(@Villager*100,9,1,0,0,0,100,0,10,10,0,0,18,768,0,0,0,0,0,1,0,0,0,0,0,0,0,'Trapped Wintergarde Villager - Script - Set Unit Flags (Unattackable)'),
(@Villager*100,9,2,0,0,0,100,0,0,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'Trapped Wintergarde Villager - Script - Set Event Phase 2'),
(@Villager*100,9,3,0,0,0,100,0,0,0,0,0,5,4,0,0,0,0,0,1,0,0,0,0,0,0,0,'Trapped Wintergarde Villager - Script - Play Emote Cheers'),
(@Villager*100,9,4,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Trapped Wintergarde Villager - Script - Talk'),
(@Villager*100,9,5,0,0,0,100,0,0,0,0,0,33,27359,0,0,0,0,0,12,1,0,0,0,0,0,0,'Trapped Wintergarde Villager - Script Give Quest Credit'),
(@Villager*100,9,6,0,0,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Trapped Wintergarde Villager - Script - Set Run'),
(@Villager*100,9,7,0,0,0,100,0,2000,2000,0,0,69,1,0,0,0,0,0,8,0,0,0,3719.13,-839.1,164.9,0,'Trapped Wintergarde Villager - Script  - Move To Pos'),
(@Villager*100,9,8,0,0,0,100,0,0,0,0,0,41,5000,0,0,0,0,0,1,0,0,0,0,0,0,0,'Trapped Wintergarde Villager - Script  - Despawn');

DELETE FROM `creature_text` WHERE `entry`IN(26654,26608);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`,`BroadcastTextID`) VALUES
(26654, 0, 0, 'Release me, fiends!', 12, 0, 100, 15, 0, 0, 'Roanauk Icemist',25828),
(26654, 0, 1, 'Pray to whatever gods you believe in that I am never freed!', 12, 0, 100, 15, 0, 0, 'Roanauk Icemist',25829),
(26654, 1, 0, 'I... am... FREE!', 14, 0, 100, 22, 0, 0, 'Roanauk Icemist',25954),
(26654, 2, 0, 'What have they done to my people...', 12, 0, 100, 6, 0, 0, 'Roanauk Icemist',25955),
(26654, 3, 0, 'You will face the full fury of the ancestors for what you have done, monster!', 14, 0, 100, 22, 0, 0, 'Roanauk Icemist',25956),
(26654, 4, 0, 'Rebirth comes, my brothers... Rise... Rise and fight once more.', 12, 0, 100, 0, 0, 0, 'Roanauk Icemist',25957),
(26654, 5, 0, 'FOR ICEMIST! FOR THE TAUNKA!', 14, 0, 100, 0, 0, 0, 'Roanauk Icemist',25958),
(26654, 6, 0, 'Come down and face me, insect!', 14, 0, 100, 15, 0, 0, 'Roanauk Icemist',25962),
(26654, 7, 0, 'Then I will force you down! Wind grant me flight!', 14, 0, 100, 15, 0, 0, 'Roanauk Icemist',25963),
(26608, 0, 0, 'Give in, Taunka! Your will cannot hold out against the Scourge!', 14, 0, 100, 15, 0, 0, 'Under-King Anub''et''kan',25952),
(26608, 0, 1, 'Leave no survivors!', 14, 0, 100, 15, 0, 0, 'Under-King Anub''et''kan',25951),
(26608, 0, 2, 'Tear this pitiful village apart!', 14, 0, 100, 15, 0, 0, 'Under-King Anub''et''kan',25950),
(26608, 1, 0, 'Your freedom will be short lived, Icemist!', 14, 0, 100, 15, 0, 0, 'Under-King Anub''et''kan',25959),
(26608, 2, 0, 'Insolent mortal! You will be consumed!', 14, 0, 100, 15, 0, 0, 'Under-King Anub''et''kan',25964),
(26608, 3, 0, 'ARRGGH!! It cannot be! How...', 14, 0, 100, 15, 0, 0, 'Under-King Anub''et''kan',25965),
(26608, 4, 0, 'Anub''et''kan is defeated! Take a fragment of his husk as proof of your victory!', 41, 0, 100, 0, 0, 0, 'Under-King Anub''et''kan',25999);

UPDATE `gameobject_template` SET `AIName`= 'SmartGameObjectAI' WHERE  `entry` =188463;
DELETE FROM `smart_scripts` WHERE `entryorguid` =188463 AND `source_type`=1;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(188463,1,0,1,70,0,100,0,2,0,0,0,45,1,1,0,0,0,0,19,26654,0,0,0,0,0,0,'Anub ar Mechanism - On State Changed - Set Data on Roanauk Icemist'),
(188463,1,1,0,61,0,100,0,2,0,0,0,70,600,0,0,0,0,0,1,0,0,0,0,0,0,0,'Anub ar Mechanism - On State Changed - Despawn GO');

UPDATE `creature_template` SET `ainame`='SmartAI', `scriptname`='' WHERE `entry` IN(26654,26772,26608,26656);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN(26654,26772,26608,26656) AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN(2665400,2665401,2665402,2660800) AND `source_type`=9;

INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(26654, 0, 0, 0, 38, 0, 100, 1, 1, 1, 0, 0, 80, 2665400, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - On Data Set 1 1 - Run Script'),

(26654, 0, 1, 2, 11, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 9, 26656, 0, 200, 0, 0, 0, 0, 'Roanauk Icemist - On Spawn - Set Data 1 1 on Anub''ar Prison'),
(26654, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - On Spawn - Set Phase 1'),
(26654, 0, 3, 4, 61, 0, 100, 0, 0, 0, 0, 0, 11, 47273, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - On Spawn - Cast Icemist''s Prison'),
(26654, 0, 4, 0, 61, 0, 100, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - On Spawn - Set Passive'),
(26654, 0, 5, 0, 1, 1, 100, 0, 5000, 30000, 120000, 150000, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - OOC (Phase 1) - Say Line 0'),
(26654, 0, 6, 0, 34, 0, 100, 0, 0, 1, 0, 0, 80, 2665401, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - On Reached WP1 - Run Script'),
(26654, 0, 7, 0, 1, 0, 100, 0, 0, 0, 15000, 35000, 5, 15, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - OOC - Play emote OneShotRoar'),
(26654, 0, 8, 0, 38, 0, 100, 0, 2, 2, 0, 0, 80, 2665402, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - On Data Set - Despawn'),
(26654, 0, 9, 0, 4, 0, 100, 0, 0, 0, 0, 0, 11, 47379, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - On Agro - Cast Icemist''s Blessing'),
(26654, 0, 10, 0, 11, 0, 100, 0, 0, 0, 0, 0, 78, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - On Respawn - Reset Scripts'),

(26656, 0, 0, 0, 38, 0, 100, 0, 1, 1, 0, 0, 11, 47272, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Anub''ar Prison - On Data Set 1 1 - Cast Anub''ar Prison'),
(26656, 0, 1, 0, 38, 0, 100, 0, 2, 2, 0, 0, 28, 47272, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Anub''ar Prison - On Data Set 2 2 - Remove Anub''ar Prison'),
(26772, 0, 0, 1, 11, 0, 100, 0, 0, 0, 0, 0, 18, 768, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Icemist Warrior - On Spawn - Set Unit Flags'),
(26772, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 29266, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Icemist Warrior - On Spawn - Cast Permament Feign Death'),
(26772, 0, 2, 3, 8, 0, 100, 0, 47378, 0, 0, 0, 19, 768, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Icemist Warrior - On Spell Hit (Glory of the Ancestors) - Set Unit Flags'),
(26772, 0, 3, 4, 61, 0, 100, 0, 0, 0, 0, 0, 28, 29266, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Icemist Warrior - On On Spell Hit (Glory of the Ancestors) - Cast Permament Feign Death'),
(26772, 0, 4, 5, 61, 0, 100, 0, 0, 0, 0, 0, 19, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Icemist Warrior - On On Spell Hit (Glory of the Ancestors) - Set Unit Flags 2'),
(26772, 0, 5, 6, 61, 0, 100, 0, 0, 0, 0, 0, 96, 32, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Icemist Warrior - On On Spell Hit (Glory of the Ancestors) - Set Dynamic Flags'),
(26772, 0, 6, 7, 61, 0, 100, 0, 0, 0, 0, 0, 91, 257, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Icemist Warrior - On On Spell Hit (Glory of the Ancestors) - Set Agressive'),
(26772, 0, 7, 0, 61, 0, 100, 0, 0, 0, 0, 0, 8, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Icemist Warrior - On On Spell Hit (Glory of the Ancestors) - Set Agressive'),
(26772, 0, 8, 0, 38, 0, 100, 0, 1, 1, 0, 0, 41, 5000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Icemist Warrior - On Data Set - Despawn'),
(26608, 0, 0, 1, 38, 0, 100, 0, 1, 1, 0, 0, 97, 15, 10,  0, 0, 0, 0,  1, 0, 0, 0,4088.679932, 2219.449951, 150.304993, 0, 'Under-King Anub''et''kan - On Data Set - Jump to Position'),
(26608, 0, 2, 0, 1, 0, 100, 0, 0, 0, 25000, 45000, 1, 0, 0, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Under-King Anub''et''kan - OOC - Say Line 0'),
(26608, 0, 2, 3, 6, 0, 100, 0, 0, 0, 0, 0, 1, 3, 0, 0, 0,  0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Under-King Anub''et''kan - On Death  - Say Line 3'),
(26608, 0, 3, 4, 61, 0, 100, 0, 0, 0, 0, 0, 1, 4, 0,  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Under-King Anub''et''kan - On Death  - Say Line 4'),
(26608, 0, 4, 5, 61, 0, 100, 0, 0, 0, 0, 0, 11, 47400, 2, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Under-King Anub''et''kan - On Death  - Cast Summon Husk'),
(26608, 0, 5, 6, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1,  0, 0, 0, 0, 9, 26772, 0, 200, 0, 0, 0, 0, 'Under-King Anub''et''kan - On Death  - Set Data on Icemist'),
(26608, 0, 6, 10, 61, 0, 100, 0, 0, 0, 0, 0, 45, 2, 2, 0, 0, 0,  0, 19, 26654, 0, 0, 0, 0, 0, 0, 'Under-King Anub''et''kan - On Death  - Set Data on Roanauk Icemist'),
(26608, 0, 7, 8, 61, 0, 100, 0, 0, 0, 0, 0, 8, 2, 0, 0, 0, 0,  0, 1, 0, 0, 0, 0, 0, 0, 0, 'Under-King Anub''et''kan - On Data Set - Set Agressive'),
(26608, 0, 8, 0, 61, 0, 100, 0, 0, 0, 0, 0, 19, 768, 0, 0, 0, 0,  0, 1, 0, 0, 0, 0, 0, 0, 0, 'Under-King Anub''et''kan - On Data Set - Set Unit Flags'),
(26608, 0, 9, 0, 11, 0, 100, 0, 0, 0, 0, 0, 18, 768, 0, 0, 0, 0,  0, 1, 0, 0, 0, 0, 0, 0, 0, 'Under-King Anub''et''kan - On Spawn - Set Unit Flags'),
(26608, 0, 1, 7, 61, 0, 100, 0, 0, 0, 0, 0, 80, 2660800, 2, 0, 0,  0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Under-King Anub''et''kan - On Data Set - Run Script'),
(26608, 0, 10, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0,  0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Under-King Anub''et''kan - On Death - Despawn'),
(2660800, 9, 0, 0, 0, 0, 100, 0, 6000, 6000, 0, 0, 101, 0, 0, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Under-King Anub''et''kan - Script - Set Home Position'),
(2665400, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script - Say Line 1'),
(2665400, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 28, 47273, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script - Remove Aura Icemist''s Prison'),
(2665400, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 2, 2, 0, 0, 0, 0, 9, 26656, 0, 200, 0, 0, 0, 0, 'Roanauk Icemist - Script - Set Data 2 2 on Anub''ar Prison'),
(2665400, 9, 3, 0, 0, 0, 100, 0, 0, 0, 0, 0, 22, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script - Set Phase 2'),
(2665400, 9, 4, 0, 0, 0, 100, 0, 0, 0, 0, 0, 53, 0, 26654, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script - Start WP'),
(2665401, 9, 0, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 101, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script 2 - Say Line 2'),
(2665401, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script 2 - Say Line 2'),
(2665401, 9, 2, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script 2 - Say Line 3'),
(2665401, 9, 3, 0, 0, 0, 100, 0, 4000, 4000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 19, 26608, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script 2 - Say Line 1 on Under-King Anub''et''kan'),
(2665401, 9, 4, 0, 0, 0, 100, 0, 4000, 4000, 0, 0, 11, 47378, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script 2 - Cast Glory of the Ancestors'),
(2665401, 9, 5, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 4, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script 2 - Say Line 4'),
(2665401, 9, 6, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 11, 47379, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script 2 - Cast Icemist''s Blessing'),
(2665401, 9, 7, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 5, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script 2 - Say Line 5'),
(2665401, 9, 8, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script 2 - Say Line 6'),
(2665401, 9, 9, 0, 0, 0, 100, 0, 4000, 4000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 19, 26608, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script 2 - Say Line 2 on Under-King Anub''et''kan'),
(2665401, 9, 10, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script 2 - Say Line 7'),
(2665401, 9, 11, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 26608, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script 2 - Say Line 7'),
(2665401, 9, 12, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 19, 768, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script 2 - Set Unit Flags'),
(2665401, 9, 13, 0, 0, 0, 100, 0, 0, 0, 0, 0, 101, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script 2 - Set Home Position'),
(2665401, 9, 14, 0, 0, 0, 100, 0, 0, 0, 0, 0, 8, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script 2 - Set Agressive'),
(2665401, 9, 15, 0, 0, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 19, 26608, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script 2 - Attack'),

(2665402, 9, 0, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 47, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script 3 - Set Invisible'),
(2665402, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 37, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script 3 - Die');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry` IN(47378,47379);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(13, 1, 47378, 0, 0, 31, 0, 3, 26772, 0, 0, 0, 0, '', 'Glory of the Ancestors targets Icemist Warrior'),

(13, 1, 47379, 0, 0, 31, 0, 3, 26772, 0, 0, 0, 0, '', 'Icemists Blessing targets Icemist Warrior'),
(13, 1, 47379, 0, 1, 31, 0, 3, 26654, 0, 0, 0, 0, '', 'Icemists Blessing targets Roanauk Icemist'),
(13, 1, 47379, 0, 2, 31, 0, 4, 0, 0, 0, 0, 0, '', 'Icemists Blessing targets Player');

DELETE FROM `waypoints` WHERE `entry`=26654;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(26654, 1, 4067.684, 2214.182, 151.9559, 'Roanauk Icemist');

DELETE FROM `creature_text` WHERE `entry`IN(26810,26379,26437);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`,`BroadcastTextID`) VALUES
(26810, 0, 0, 'Gather, brothers and sisters.', 12, 1, 100, 1, 0, 0, 'Roanauk Icemist',26136),
(26810, 1, 0, '%s reads from the scroll as the other Taunka gather around him.', 16, 1, 100, 0, 0, 0, 'Roanauk Icemist',26130),
(26810, 2, 0, 'Lok''tar ogar! Victory or death - it is these words that bind me to the Horde! For they are the most sacred and fundamental of truths to any warrior of the Horde.', 12, 1, 100, 1, 0, 0, 'Roanauk Icemist',26137),
(26810, 3, 0, 'I give my flesh and blood freely to the Warchief. I am the instrument of my Warchief''s desire. I am a weapon of my Warchief''s command!', 12, 1, 100, 1, 0, 0, 'Roanauk Icemist',26138),
(26810, 4, 0, 'From this moment until the end of days I live and die - For the Horde!', 12, 1, 100, 1, 0, 0, 'Roanauk Icemist',26139),
(26810, 5, 0, 'For my Taunka brothers and sisters! FOR THE HORDE!', 14, 1, 100, 388, 0, 0, 'Roanauk Icemist',26140),
(26379, 0, 0, 'We will walk together, $n.', 12, 1, 100, 1, 0, 0, 'Overlord Agmar',26131),
(26379, 1, 0, 'Welcome to the Horde, High Chief. Lok''tar ogar!', 12, 1, 100, 2, 0, 0, 'Overlord Agmar',26141),
(26379, 2, 0, 'FOR THE HORDE!', 14, 1, 100, 15, 0, 0, 'Overlord Agmar',26142),
(26437, 0, 0, 'Amidst the tragedy and chaos, this place stands defiantly against the Scourge! It is good to be Horde.', 12, 1, 100, 113, 0, 0, 'Taunka Soldier',25727);

UPDATE`creature` SET `position_x`=3842.386, `position_y`=1486.616, `position_z`=92.06059, `orientation`=1.570796 WHERE  `guid`=204429; -- id 26379

DELETE FROM `creature_addon` WHERE  `guid`=204429;

DELETE FROM `creature_template_addon` WHERE `entry`IN(26379);
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `bytes2`, `auras`) VALUES
(26379, 0, 0x6, 0x101, '47786'); -- 26379 - 47786

UPDATE `creature_template` SET `ainame`='SmartAI', `scriptname`='' WHERE `entry` IN(26379,26437,26810);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN(26379,26437,26810,-224475,-224464,-224474,-224476,-224478,-224471,-224477) AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN(2681000) AND `source_type`=9;

INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(26379, 0, 0, 1, 19, 0, 100, 0, 12140, 0, 0, 0, 81, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Overlord Agmar - On Quest Accept (All Hail Roanauk!) - Set Npc Flags'),
(26379, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 91, 257, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Overlord Agmar - On Quest Accept (All Hail Roanauk!) - Set Bytes 1'),
(26379, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Overlord Agmar - On Quest Accept (All Hail Roanauk!) - Say Line 1'),
(26379, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 0, 26379, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Overlord Agmar - On Quest Accept (All Hail Roanauk!) - Start WP'),
(26379, 0, 4, 0, 40, 0, 100, 0, 10, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 19, 26810, 0, 0, 0, 0, 0, 0, 'Overlord Agmar - On reached WP10 - Set Orientation'),
(26379, 0, 5, 0, 38, 0, 100, 0, 1, 1, 0, 0, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Overlord Agmar - On Data Set - Evade'),
(26379, 0, 6, 0, 21, 0, 100, 0, 0, 0, 0, 0, 81, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Overlord Agmar - On Reached Home - Set Unit Flags'),
(26810, 0, 0, 1, 62, 0, 100, 0, 9462, 0, 0, 0, 64, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - On Gossip Option select - Store Targetlist'),
(26810, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - On Gossip Option select - Close Gossip'),
(26810, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 81, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - On Gossip Option select - Set NPC Flags'),
(26810, 0, 3, 4, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 9, 26437, 0, 200, 0, 0, 0, 0, 'Roanauk Icemist - On Gossip Option select - Set Data Taunka Soldier'),
(26810, 0, 4, 0, 61, 0, 100, 0, 0, 0, 0, 0, 80, 2681000, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - On Gossip Option select - Run Script'),
(-224475, 0, 0, 1, 38, 0, 100, 0, 1, 1, 0, 0, 91, 65539, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On Data Set - Set Bytes 1'),
(-224475, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 0, 2643700, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On Data Set - Start WP'),
(-224475, 0, 2, 0, 38, 0, 100, 0, 2, 2, 0, 0, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On Data Set - Evade'),
(-224475, 0, 3, 0, 34, 0, 100, 0, 1, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 19, 26810, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On reached WP1 - Set Orientation'),
(-224464, 0, 0, 1, 38, 0, 100, 0, 1, 1, 0, 0, 91, 65539, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On Data Set - Set Bytes 1'),
(-224464, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 0, 2643701, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On Data Set - Start WP'),
(-224464, 0, 2, 0, 38, 0, 100, 0, 2, 2, 0, 0, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On Data Set - Evade'),
(-224464, 0, 3, 0, 34, 0, 100, 0, 1, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 19, 26810, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On reached WP1 - Set Orientation'),
(-224474, 0, 0, 1, 38, 0, 100, 0, 1, 1, 0, 0, 91, 65536, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On Data Set - Set Bytes 1'),
(-224474, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 0, 2643702, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On Data Set - Start WP'),
(-224474, 0, 2, 0, 38, 0, 100, 0, 2, 2, 0, 0, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On Data Set - Evade'),
(-224474, 0, 3, 0, 34, 0, 100, 0, 1, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 19, 26810, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On reached WP1 - Set Orientation'),
(-224476, 0, 0, 1, 38, 0, 100, 0, 1, 1, 0, 0, 91, 65536, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On Data Set - Set Bytes 1'),
(-224476, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 0, 2643703, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On Data Set - Start WP'),
(-224476, 0, 2, 0, 38, 0, 100, 0, 2, 2, 0, 0, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On Data Set - Evade'),
(-224476, 0, 3, 0, 34, 0, 100, 0, 1, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 19, 26810, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On reached WP1 - Set Orientation'),
(-224478, 0, 0, 1, 38, 0, 100, 0, 1, 1, 0, 0, 91, 65537, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On Data Set - Set Bytes 1'),
(-224478, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 0, 2643704, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On Data Set - Start WP'),
(-224478, 0, 2, 0, 38, 0, 100, 0, 2, 2, 0, 0, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On Data Set - Evade'),
(-224478, 0, 3, 0, 34, 0, 100, 0, 1, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 19, 26810, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On reached WP1 - Set Orientation'),
(-224471, 0, 0, 1, 38, 0, 100, 0, 1, 1, 0, 0, 91, 65537, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On Data Set - Set Bytes 1'),
(-224471, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 0, 2643705, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On Data Set - Start WP'),
(-224471, 0, 2, 0, 38, 0, 100, 0, 2, 2, 0, 0, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On Data Set - Evade'),
(-224471, 0, 3, 0, 34, 0, 100, 0, 1, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 19, 26810, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On reached WP1 - Set Orientation'),
(-224477, 0, 0, 1, 38, 0, 100, 0, 1, 1, 0, 0, 91, 65536, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On Data Set - Set Bytes 1'),
(-224477, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 0, 2643706, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On Data Set - Start WP'),
(-224477, 0, 2, 0, 38, 0, 100, 0, 2, 2, 0, 0, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On Data Set - Evade'),
(-224477, 0, 3, 0, 34, 0, 100, 0, 1, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 19, 26810, 0, 0, 0, 0, 0, 0, 'Taunka Soldier - On reached WP1 - Set Orientation'),
(2681000, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script - Say Line 1'),
(2681000, 9, 1, 0, 0, 0, 100, 0, 10000, 10000, 0, 0, 1, 1, 0, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script - Say Line 2'),
(2681000, 9, 2, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 1, 2, 0, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script - Say Line 3'),
(2681000, 9, 3, 0, 0, 0, 100, 0, 8000, 8000, 0, 0, 1, 3, 0, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script - Say Line 4'),
(2681000, 9, 4, 0, 0, 0, 100, 0, 8000, 8000, 0, 0, 1, 4, 0, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script - Say Line 5'),
(2681000, 9, 5, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 1, 0, 0,  0, 0, 0, 19, 26379, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script - Say Line 1 on Overlord Agmar'),
(2681000, 9, 6, 0, 0, 0, 100, 0, 4000, 4000, 0, 0, 5, 15, 0, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script - Play emote OneShotRoar'),
(2681000, 9, 7, 0, 0, 0, 100, 0, 4000, 4000, 0, 0, 33, 26810, 0, 0,  0, 0, 0, 12, 1, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script - Give Kill Credit'),
(2681000, 9, 8, 0, 0, 0, 100, 0, 0, 0, 0, 0, 5, 388, 0, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script - Play emote OneShotStomp'),
(2681000, 9, 9, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 5, 0, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script - Say Line 6'),
(2681000, 9, 10, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 1, 2, 0, 0,  0, 0, 0, 19, 26379, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script - Say Line 2 on Overlord Agmar'),
(2681000, 9, 11, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 0, 0, 0,  0, 0, 0, 19, 26437, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script - Say Line 0 on Taunka Soldier'),
(2681000, 9, 12, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 45, 2, 2, 0,  0, 0, 0, 9, 26437, 0, 200, 0, 0, 0, 0, 'Roanauk Icemist - Script - Set Data Taunka Soldier'),
(2681000, 9, 13, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0,  0, 0, 0, 19, 26379, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script - Set Data Overlord Agmar'),
(2681000, 9, 14, 0, 0, 0, 100, 0, 0, 0, 0, 0, 81, 1, 0, 0,  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roanauk Icemist - Script - Set NPC Flags');

DELETE FROM `waypoints` WHERE `entry`=26379;
DELETE FROM `waypoints` WHERE `entry` BETWEEN 2643700 AND 2643707;

INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(26379, 1, 3842.118, 1492.083, 91.71697, 'Overlord Agmar'),
(26379, 2, 3842.422, 1498.366, 91.98796, 'Overlord Agmar'),
(26379, 3, 3842.672, 1511.366, 91.98796, 'Overlord Agmar'),
(26379, 4, 3842.172, 1520.616, 91.73796, 'Overlord Agmar'),
(26379, 5, 3842.672, 1535.866, 90.23796, 'Overlord Agmar'),
(26379, 6, 3850.172, 1547.616, 90.23796, 'Overlord Agmar'),
(26379, 7, 3859.422, 1559.866, 90.23796, 'Overlord Agmar'),
(26379, 8, 3865.922, 1568.366, 90.23796, 'Overlord Agmar'),
(26379, 9, 3868.922, 1577.616, 90.23796, 'Overlord Agmar'),
(26379, 10, 3870.227, 1589.648, 89.75896, 'Overlord Agmar'),
(2643700, 1, 3872.902, 1594.418, 90.0797, 'Taunka Soldier'), --  224475 
(2643701, 1, 3880.851, 1591.76, 90.98628, 'Taunka Soldier'), -- 224464 
(2643702, 1, 3874.775, 1589.399, 90.39027, 'Taunka Soldier'), -- 224474 
(2643703, 1, 3877.774, 1588.824, 90.92334, 'Taunka Soldier'), -- 224476 
(2643704, 1, 3876.746, 1597.52, 90.69058, 'Taunka Soldier'), -- 224478 
(2643705, 1, 3879.273, 1595.718, 90.78122, 'Taunka Soldier'), -- 224471 
(2643706, 1, 3873.469, 1597.843, 90.18542, 'Taunka Soldier'); -- 224477 

DELETE FROM `gossip_menu_option` WHERE `menu_id` IN(9461,9462);
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `OptionBroadcastTextID`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`, `BoxBroadcastTextID`) VALUES 
(9461, 0, 0, 'Greetings High Chief. Would you do me the honor of accepting my invitation to join the Horde as an official member and leader of the Taunka?', 26127, 1, 1, 9462, 0, 0, 0, '', 0),
(9462, 0, 0, 'It is you who honor me, High Chief. Please read from this scroll. It is the oath of allegiance.', 26129, 1, 1, 0, 0, 0, 0, '', 0);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=9461;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(15, 9461, 0, 0, 0, 9, 0, 12140, 0, 0, 0, 0, 0, '', 'Show gossip option only if player is on quest All Hail Roanak'),
(15, 9461, 0, 0, 0, 29, 0, 26379, 30, 0, 0, 0, 0, '', 'Show gossip option only if Overlord Agmar is within 30 yards');


INSERT IGNORE INTO `playercreateinfo_spell_custom`(`racemask`,`classmask`,`Spell`,`Note`) VALUES
(0,1024,768,'Cat Form - Shapeshift'),
(0,1024,770,'Faerie Fire'),
(0,1024,783,'Travel Form - Shapeshift'),
(0,1024,1066,'Aquatic Form - Shapeshift'),
(0,1024,2782,'Remove Curse'),
(0,1024,2893,'Abolish Poison'),
(0,1024,5209,'Challenging Roar'),
(0,1024,5215,'Prowl'),
(0,1024,5225,'Track Humanoids'),
(0,1024,5229,'Enrage'),
(0,1024,8983,'Bash - Rank 3'),
(0,1024,9634,'Dire Bear Form - Shapeshift'),
(0,1024,16857,'Faerie Fire (Feral)'),
(0,1024,18658,'Hibernate - Rank 3'),
(0,1024,20719,'Feline Grace - Passive'),
(0,1024,22812,'Barkskin'),
(0,1024,22842,'Frenzied Regeneration'),
(0,1024,26995,'Soothe Animal - Rank 4'),
(0,1024,29166,'Innervate'),
(0,1024,33357,'Dash - Rank 3'),
(0,1024,33786,'Cyclone'),
(0,1024,33943,'Flight Form - Shapeshift'),
(0,1024,48378,'Healing Touch - Rank 15'),
(0,1024,48441,'Rejuvenation - Rank 15'),
(0,1024,48443,'Regrowth - Rank 12'),
(0,1024,48447,'Tranquility - Rank 7'),
(0,1024,48451,'Lifebloom - Rank 3'),
(0,1024,48461,'Wrath - Rank 12'),
(0,1024,48463,'Moonfire - Rank 14'),
(0,1024,48465,'Starfire - Rank 10'),
(0,1024,48467,'Hurricane - Rank 5'),
(0,1024,48469,'Mark of the Wild - Rank 9'),
(0,1024,48470,'Gift of the Wild - Rank 4'),
(0,1024,48477,'Rebirth - Rank 7'),
(0,1024,48560,'Demoralizing Roar - Rank 8'),
(0,1024,48562,'Swipe (Bear) - Rank 8'),
(0,1024,48568,'Lacerate - Rank 3'),
(0,1024,48570,'Claw - Rank 8'),
(0,1024,48572,'Shred - Rank 9'),
(0,1024,48574,'Rake - Rank 7'),
(0,1024,48575,'Cower - Rank 6'),
(0,1024,48577,'Ferocious Bite - Rank 8'),
(0,1024,48579,'Ravage - Rank 7'),
(0,1024,49800,'Rip - Rank 9'),
(0,1024,49802,'Maim - Rank 2'),
(0,1024,49803,'Pounce - Rank 5'),
(0,1024,50213,'Tiger\'s Fury - Rank 6'),
(0,1024,50464,'Nourish - Rank 1'),
(0,1024,50763,'Revive - Rank 7'),
(0,1024,52610,'Savage Roar - Rank 1'),
(0,1024,53307,'Thorns - Rank 8'),
(0,1024,53308,'Entangling Roots - Rank 8'),
(0,1024,53312,'Nature\'s Grasp - Rank 8'),
(0,1024,62078,'Swipe (Cat) - Rank 1'),
(0,1024,62600,'Savage Defense - Passive'),
(0,1024,48480,'Maul - Rank 10'),
(0,4,781,'Disengage'),
(0,4,883,'Call Pet'),
(0,4,1002,'Eyes of the Beast'),
(0,4,1462,'Beast Lore'),
(0,4,1494,'Track Beasts'),
(0,4,1515,'Tame Beast'),
(0,4,1543,'Flare'),
(0,4,2641,'Dismiss Pet'),
(0,4,2974,'Wing Clip'),
(0,4,3034,'Viper Sting'),
(0,4,3043,'Scorpid Sting'),
(0,4,3045,'Rapid Fire'),
(0,4,3127,'Parry - Passive'),
(0,4,5116,'Concussive Shot'),
(0,4,5118,'Aspect of the Cheetah'),
(0,4,5384,'Feign Death'),
(0,4,6197,'Eagle Eye'),
(0,4,6991,'Feed Pet'),
(0,4,13159,'Aspect of the Pack'),
(0,4,13161,'Aspect of the Beast'),
(0,4,13163,'Aspect of the Monkey'),
(0,4,13809,'Frost Trap'),
(0,4,14311,'Freezing Trap - Rank 3'),
(0,4,14327,'Scare Beast - Rank 3'),
(0,4,19263,'Deterrence'),
(0,4,19801,'Tranquilizing Shot'),
(0,4,19878,'Track Demons'),
(0,4,19879,'Track Dragonkin'),
(0,4,19880,'Track Elementals'),
(0,4,19882,'Track Giants'),
(0,4,19883,'Track Humanoids'),
(0,4,19884,'Track Undead'),
(0,4,19885,'Track Hidden'),
(0,4,20736,'Distracting Shot - Rank 1'),
(0,4,27044,'Aspect of the Hawk - Rank 8'),
(0,4,34026,'Kill Command'),
(0,4,34074,'Aspect of the Viper'),
(0,4,34477,'Misdirection'),
(0,4,34600,'Snake Trap'),
(0,4,48990,'Mend Pet - Rank 10'),
(0,4,48996,'Raptor Strike - Rank 11'),
(0,4,49001,'Serpent Sting - Rank 12'),
(0,4,49045,'Arcane Shot - Rank 11'),
(0,4,49048,'Multi-Shot - Rank 8'),
(0,4,49052,'Steady Shot - Rank 4'),
(0,4,49056,'Immolation Trap - Rank 8'),
(0,4,49067,'Explosive Trap - Rank 6'),
(0,4,49071,'Aspect of the Wild - Rank 4'),
(0,4,53271,'Master\'s Call'),
(0,4,53338,'Hunter\'s Mark - Rank 5'),
(0,4,53339,'Mongoose Bite - Rank 6'),
(0,4,58434,'Volley - Rank 6'),
(0,4,60192,'Freezing Arrow - Rank 1'),
(0,4,61006,'Kill Shot - Rank 3'),
(0,4,61847,'Aspect of the Dragonhawk - Rank 2'),
(0,4,62757,'Call Stabled Pet'),
(0,128,66,'Invisibility'),
(0,128,130,'Slow Fall'),
(0,128,475,'Remove Curse'),
(0,128,1953,'Blink'),
(0,128,2139,'Counterspell'),
(0,128,7301,'Frost Armor - Rank 3'),
(0,128,12051,'Evocation'),
(0,128,12826,'Polymorph - Rank 4'),
(0,128,27090,'Conjure Water - Rank 9'),
(0,128,30449,'Spellsteal'),
(0,128,33717,'Conjure Food - Rank 8'),
(0,128,42833,'Fireball - Rank 16'),
(0,128,42842,'Frostbolt - Rank 16'),
(0,128,42846,'Arcane Missiles - Rank 13'),
(0,128,42859,'Scorch - Rank 11'),
(0,128,42873,'Fire Blast - Rank 11'),
(0,128,42897,'Arcane Blast - Rank 4'),
(0,128,42914,'Ice Lance - Rank 3'),
(0,128,42917,'Frost Nova - Rank 6'),
(0,128,42921,'Arcane Explosion - Rank 10'),
(0,128,42926,'Flamestrike - Rank 9'),
(0,128,42931,'Cone of Cold - Rank 8'),
(0,128,42940,'Blizzard - Rank 9'),
(0,128,42956,'Conjure Refreshment - Rank 2'),
(0,128,42985,'Conjure Mana Gem - Rank 6'),
(0,128,42995,'Arcane Intellect - Rank 7'),
(0,128,43002,'Arcane Brilliance - Rank 3'),
(0,128,43008,'Ice Armor - Rank 6'),
(0,128,43010,'Fire Ward - Rank 7'),
(0,128,43012,'Frost Ward - Rank 7'),
(0,128,43015,'Dampen Magic - Rank 7'),
(0,128,43017,'Amplify Magic - Rank 7'),
(0,128,43020,'Mana Shield - Rank 9'),
(0,128,43024,'Mage Armor - Rank 6'),
(0,128,43046,'Molten Armor - Rank 3'),
(0,128,45438,'Ice Block'),
(0,128,47610,'Frostfire Bolt - Rank 2'),
(0,128,55342,'Mirror Image'),
(0,128,58659,'Ritual of Refreshment - Rank 2'),
(0,32,3714,'Path of Frost'),
(0,32,42650,'Army of the Dead'),
(0,32,45524,'Chains of Ice'),
(0,32,45529,'Blood Tap'),
(0,32,46584,'Raise Dead'),
(0,32,47476,'Strangulate'),
(0,32,47528,'Mind Freeze'),
(0,32,47568,'Empower Rune Weapon'),
(0,32,48263,'Frost Presence'),
(0,32,48265,'Unholy Presence'),
(0,32,48707,'Anti-Magic Shell'),
(0,32,48743,'Death Pact'),
(0,32,48778,'Acherus Deathcharger - Summon'),
(0,32,48792,'Icebound Fortitude'),
(0,32,49895,'Death Coil - Rank 5'),
(0,32,49909,'Icy Touch - Rank 5'),
(0,32,49921,'Plague Strike - Rank 6'),
(0,32,49924,'Death Strike - Rank 5'),
(0,32,49930,'Blood Strike - Rank 6'),
(0,32,49938,'Death and Decay - Rank 4'),
(0,32,49941,'Blood Boil - Rank 4'),
(0,32,50842,'Pestilence'),
(0,32,51425,'Obliterate - Rank 4'),
(0,32,53323,'Rune of Swordshattering'),
(0,32,53331,'Rune of Lichbane'),
(0,32,53342,'Rune of Spellshattering'),
(0,32,53344,'Rune of the Fallen Crusader'),
(0,32,53428,'Runeforging'),
(0,32,54446,'Rune of Swordbreaking'),
(0,32,54447,'Rune of Spellbreaking'),
(0,32,56222,'Dark Command'),
(0,32,56815,'Rune Strike'),
(0,32,57623,'Horn of Winter - Rank 2'),
(0,32,61999,'Raise Ally'),
(0,32,62158,'Rune of the Stoneskin Gargoyle'),
(0,32,70164,'Rune of the Nerubian Carapace'),
(0,2,498,'Divine Protection'),
(0,2,642,'Divine Shield'),
(0,2,1038,'Hand of Salvation'),
(0,2,1044,'Hand of Freedom'),
(0,2,1152,'Purify'),
(0,2,3127,'Parry - Passive'),
(0,2,4987,'Cleanse'),
(0,2,5502,'Sense Undead'),
(0,2,6940,'Hand of Sacrifice'),
(0,2,10278,'Hand of Protection - Rank 3'),
(0,2,10308,'Hammer of Justice - Rank 4'),
(0,2,10326,'Turn Evil'),
(0,2,19746,'Concentration Aura'),
(0,2,19752,'Divine Intervention'),
(0,2,20164,'Seal of Justice'),
(0,2,20165,'Seal of Light'),
(0,2,20166,'Seal of Wisdom'),
(0,2,20217,'Blessing of Kings'),
(0,2,20271,'Judgement of Light'),
(0,2,25780,'Righteous Fury'),
(0,2,25898,'Greater Blessing of Kings'),
(0,2,31789,'Righteous Defense'),
(0,2,31884,'Avenging Wrath'),
(0,2,32223,'Crusader Aura'),
(0,2,33388,'Apprentice Riding - Apprentice'),
(0,2,48782,'Holy Light - Rank 13'),
(0,2,48785,'Flash of Light - Rank 9'),
(0,2,48788,'Lay on Hands - Rank 5'),
(0,2,48801,'Exorcism - Rank 9'),
(0,2,48806,'Hammer of Wrath - Rank 6'),
(0,2,48817,'Holy Wrath - Rank 5'),
(0,2,48819,'Consecration - Rank 8'),
(0,2,48932,'Blessing of Might - Rank 10'),
(0,2,48934,'Greater Blessing of Might - Rank 5'),
(0,2,48936,'Blessing of Wisdom - Rank 9'),
(0,2,48938,'Greater Blessing of Wisdom - Rank 5'),
(0,2,48942,'Devotion Aura - Rank 10'),
(0,2,48943,'Shadow Resistance Aura - Rank 5'),
(0,2,48945,'Frost Resistance Aura - Rank 5'),
(0,2,48947,'Fire Resistance Aura - Rank 5'),
(0,2,48950,'Redemption - Rank 7'),
(0,2,53407,'Judgement of Justice'),
(0,2,53408,'Judgement of Wisdom'),
(0,2,53601,'Sacred Shield - Rank 1'),
(0,2,54043,'Retribution Aura - Rank 7'),
(0,2,54428,'Divine Plea'),
(0,2,61411,'Shield of Righteousness - Rank 2'),
(0,2,62124,'Hand of Reckoning'),
(1101,2,23214,'Charger - Summon'),
(690,2,34767,'Summon Charger - Summon'),
(1101,2,13819,'Warhorse - Summon'),
(690,2,34769,'Summon Warhorse - Summon'),
(1101,2,31801,'Seal of Vengeance'),
(690,2,53736,'Seal of Corruption'),
(0,16,453,'Mind Soothe'),
(0,16,528,'Cure Disease'),
(0,16,552,'Abolish Disease'),
(0,16,586,'Fade'),
(0,16,605,'Mind Control'),
(0,16,988,'Dispel Magic - Rank 2'),
(0,16,1706,'Levitate'),
(0,16,2053,'Lesser Heal - Rank 3'),
(0,16,6064,'Heal - Rank 4'),
(0,16,6346,'Fear Ward'),
(0,16,8129,'Mana Burn'),
(0,16,10890,'Psychic Scream - Rank 4'),
(0,16,10909,'Mind Vision - Rank 2'),
(0,16,10955,'Shackle Undead - Rank 3'),
(0,16,32375,'Mass Dispel'),
(0,16,34433,'Shadowfiend'),
(0,16,48063,'Greater Heal - Rank 9'),
(0,16,48066,'Power Word: Shield - Rank 14'),
(0,16,48068,'Renew - Rank 14'),
(0,16,48071,'Flash Heal - Rank 11'),
(0,16,48072,'Prayer of Healing - Rank 7'),
(0,16,48073,'Divine Spirit - Rank 6'),
(0,16,48074,'Prayer of Spirit - Rank 3'),
(0,16,48078,'Holy Nova - Rank 9'),
(0,16,48113,'Prayer of Mending - Rank 3'),
(0,16,48120,'Binding Heal - Rank 3'),
(0,16,48123,'Smite - Rank 12'),
(0,16,48125,'Shadow Word: Pain - Rank 12'),
(0,16,48127,'Mind Blast - Rank 13'),
(0,16,48135,'Holy Fire - Rank 11'),
(0,16,48158,'Shadow Word: Death - Rank 4'),
(0,16,48161,'Power Word: Fortitude - Rank 8'),
(0,16,48162,'Prayer of Fortitude - Rank 4'),
(0,16,48168,'Inner Fire - Rank 9'),
(0,16,48169,'Shadow Protection - Rank 5'),
(0,16,48170,'Prayer of Shadow Protection - Rank 3'),
(0,16,48171,'Resurrection - Rank 7'),
(0,16,48300,'Devouring Plague - Rank 9'),
(0,16,53023,'Mind Sear - Rank 2'),
(0,16,64843,'Divine Hymn - Rank 1'),
(0,16,64901,'Hymn of Hope'),
(0,8,921,'Pick Pocket'),
(0,8,1725,'Distract'),
(0,8,1766,'Kick'),
(0,8,1776,'Gouge'),
(0,8,1784,'Stealth'),
(0,8,1804,'Pick Lock'),
(0,8,1833,'Cheap Shot'),
(0,8,1842,'Disarm Trap'),
(0,8,1860,'Safe Fall - Passive'),
(0,8,2094,'Blind'),
(0,8,2836,'Detect Traps - Passive'),
(0,8,3127,'Parry - Passive'),
(0,8,5938,'Shiv'),
(0,8,6774,'Slice and Dice - Rank 2'),
(0,8,8643,'Kidney Shot - Rank 2'),
(0,8,8647,'Expose Armor'),
(0,8,11305,'Sprint - Rank 3'),
(0,8,26669,'Evasion - Rank 2'),
(0,8,26889,'Vanish - Rank 3'),
(0,8,31224,'Cloak of Shadows'),
(0,8,48638,'Sinister Strike - Rank 12'),
(0,8,48657,'Backstab - Rank 12'),
(0,8,48659,'Feint - Rank 8'),
(0,8,48668,'Eviscerate - Rank 12'),
(0,8,48672,'Rupture - Rank 9'),
(0,8,48674,'Deadly Throw - Rank 3'),
(0,8,48676,'Garrote - Rank 10'),
(0,8,48691,'Ambush - Rank 10'),
(0,8,51722,'Dismantle'),
(0,8,51723,'Fan of Knives'),
(0,8,51724,'Sap - Rank 4'),
(0,8,57934,'Tricks of the Trade'),
(0,8,57993,'Envenom - Rank 4'),
(0,64,131,'Water Breathing'),
(0,64,526,'Cure Toxins'),
(0,64,546,'Water Walking'),
(0,64,556,'Astral Recall'),
(0,64,2062,'Earth Elemental Totem'),
(0,64,2484,'Earthbind Totem'),
(0,64,2645,'Ghost Wolf'),
(0,64,2894,'Fire Elemental Totem'),
(0,64,3738,'Wrath of Air Totem'),
(0,64,6196,'Far Sight'),
(0,64,6495,'Sentry Totem'),
(0,64,8012,'Purge - Rank 2'),
(0,64,8143,'Tremor Totem'),
(0,64,8170,'Cleansing Totem'),
(0,64,8177,'Grounding Totem'),
(0,64,8512,'Windfury Totem'),
(0,64,10399,'Rockbiter Weapon - Rank 4'),
(0,64,20608,'Reincarnation - Passive'),
(1101,64,32182,'Heroism'),
(0,64,36936,'Totemic Recall'),
(0,64,49231,'Earth Shock - Rank 10'),
(0,64,49233,'Flame Shock - Rank 9'),
(0,64,49236,'Frost Shock - Rank 7'),
(0,64,49238,'Lightning Bolt - Rank 14'),
(0,64,49271,'Chain Lightning - Rank 8'),
(0,64,49273,'Healing Wave - Rank 14'),
(0,64,49276,'Lesser Healing Wave - Rank 9'),
(0,64,49277,'Ancestral Spirit - Rank 7'),
(0,64,49281,'Lightning Shield - Rank 11'),
(0,64,51514,'Hex'),
(0,64,51994,'Earthliving Weapon - Rank 6'),
(0,64,55459,'Chain Heal - Rank 7'),
(0,64,57960,'Water Shield - Rank 9'),
(0,64,57994,'Wind Shear'),
(0,64,58582,'Stoneclaw Totem - Rank 10'),
(0,64,58643,'Strength of Earth Totem - Rank 8'),
(0,64,58656,'Flametongue Totem - Rank 8'),
(0,64,58704,'Searing Totem - Rank 10'),
(0,64,58734,'Magma Totem - Rank 7'),
(0,64,58739,'Fire Resistance Totem - Rank 6'),
(0,64,58745,'Frost Resistance Totem - Rank 6'),
(0,64,58749,'Nature Resistance Totem - Rank 6'),
(0,64,58753,'Stoneskin Totem - Rank 10'),
(0,64,58757,'Healing Stream Totem - Rank 9'),
(0,64,58774,'Mana Spring Totem - Rank 8'),
(0,64,58790,'Flametongue Weapon - Rank 10'),
(0,64,58796,'Frostbrand Weapon - Rank 9'),
(0,64,58804,'Windfury Weapon - Rank 8'),
(0,64,60043,'Lava Burst - Rank 2'),
(0,64,61657,'Fire Nova - Rank 9'),
(0,64,66842,'Call of the Elements'),
(0,64,66843,'Call of the Ancestors'),
(0,64,66844,'Call of the Spirits'),
(690,64,2825,'Bloodlust'),
(0,256,126,'Eye of Kilrogg - Summon'),
(0,256,132,'Detect Invisibility'),
(0,256,688,'Summon Imp - Summon'),
(0,256,691,'Summon Felhunter - Summon'),
(0,256,696,'Demon Skin - Rank 2'),
(0,256,697,'Summon Voidwalker - Summon'),
(0,256,698,'Ritual of Summoning'),
(0,256,712,'Summon Succubus - Summon'),
(0,256,1122,'Inferno - Summon'),
(0,256,5138,'Drain Mana'),
(0,256,5500,'Sense Demons'),
(0,256,5697,'Unending Breath'),
(0,256,5784,'Felsteed - Summon'),
(0,256,6215,'Fear - Rank 3'),
(0,256,11719,'Curse of Tongues - Rank 2'),
(0,256,17928,'Howl of Terror - Rank 2'),
(0,256,18540,'Ritual of Doom'),
(0,256,18647,'Banish - Rank 2'),
(0,256,23161,'Dreadsteed - Summon'),
(0,256,29858,'Soulshatter'),
(0,256,33388,'Apprentice Riding - Apprentice'),
(0,256,47809,'Shadow Bolt - Rank 13'),
(0,256,47811,'Immolate - Rank 11'),
(0,256,47813,'Corruption - Rank 10'),
(0,256,47815,'Searing Pain - Rank 10'),
(0,256,47820,'Rain of Fire - Rank 7'),
(0,256,47823,'Hellfire - Rank 5'),
(0,256,47825,'Soul Fire - Rank 6'),
(0,256,47836,'Seed of Corruption - Rank 3'),
(0,256,47838,'Incinerate - Rank 4'),
(0,256,47855,'Drain Soul - Rank 6'),
(0,256,47856,'Health Funnel - Rank 9'),
(0,256,47857,'Drain Life - Rank 9'),
(0,256,47860,'Death Coil - Rank 6'),
(0,256,47864,'Curse of Agony - Rank 9'),
(0,256,47865,'Curse of the Elements - Rank 5'),
(0,256,47867,'Curse of Doom - Rank 3'),
(0,256,47878,'Create Healthstone - Rank 8'),
(0,256,47884,'Create Soulstone - Rank 7'),
(0,256,47888,'Create Spellstone - Rank 6'),
(0,256,47889,'Demon Armor - Rank 8'),
(0,256,47891,'Shadow Ward - Rank 6'),
(0,256,47893,'Fel Armor - Rank 4'),
(0,256,48018,'Demonic Circle: Summon'),
(0,256,48020,'Demonic Circle: Teleport'),
(0,256,50511,'Curse of Weakness - Rank 9'),
(0,256,57946,'Life Tap - Rank 8'),
(0,256,58887,'Ritual of Souls - Rank 2'),
(0,256,60220,'Create Firestone - Rank 7'),
(0,256,61191,'Enslave Demon - Rank 4'),
(0,256,61290,'Shadowflame - Rank 2'),
(0,1,71,'Defensive Stance'),
(0,1,72,'Shield Bash'),
(0,1,355,'Taunt'),
(0,1,676,'Disarm'),
(0,1,694,'Mocking Blow'),
(0,1,871,'Shield Wall'),
(0,1,1161,'Challenging Shout'),
(0,1,1680,'Whirlwind'),
(0,1,1715,'Hamstring'),
(0,1,1719,'Recklessness'),
(0,1,2458,'Berserker Stance'),
(0,1,2565,'Shield Block'),
(0,1,2687,'Bloodrage'),
(0,1,3127,'Parry - Passive'),
(0,1,3411,'Intervene'),
(0,1,5246,'Intimidating Shout'),
(0,1,6552,'Pummel'),
(0,1,7384,'Overpower'),
(0,1,7386,'Sunder Armor'),
(0,1,11578,'Charge - Rank 3'),
(0,1,12678,'Stance Mastery - Passive'),
(0,1,18499,'Berserker Rage'),
(0,1,20230,'Retaliation'),
(0,1,20252,'Intercept'),
(0,1,23920,'Spell Reflection'),
(0,1,34428,'Victory Rush'),
(0,1,47436,'Battle Shout - Rank 9'),
(0,1,47437,'Demoralizing Shout - Rank 8'),
(0,1,47440,'Commanding Shout - Rank 3'),
(0,1,47450,'Heroic Strike - Rank 13'),
(0,1,47465,'Rend - Rank 10'),
(0,1,47471,'Execute - Rank 9'),
(0,1,47475,'Slam - Rank 8'),
(0,1,47488,'Shield Slam - Rank 8'),
(0,1,47502,'Thunder Clap - Rank 9'),
(0,1,47520,'Cleave - Rank 8'),
(0,1,55694,'Enraged Regeneration'),
(0,1,57755,'Heroic Throw'),
(0,1,57823,'Revenge - Rank 9'),
(0,1,64382,'Shattering Throw');

update creature_template set `AIName`='SmartAI' where entry=26261;
Delete from `smart_scripts` where entryorguid=26261 and event_param1=47394;
INSERT INTO `smart_scripts` VALUES (26261, 0, 0, 0, 8, 0, 100, 0, 47394, 0, 0, 0, 33, 26261, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'On Spellhit call Killcredit for Q 12070');











