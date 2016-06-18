

DELETE FROM `creature_template_addon` WHERE `entry`=24783;
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(24783, 0, 0, 0, 1, 0, 43775);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` IN(13,17) AND `SourceEntry`=44422;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorType`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(17,0,44422,0,0,30,0,186946,5,0,0,0,0,'',"Spell 'Scavenge' target GameObject 'Fjord Hawk Egg'"),
(13,1,44422,0,0,31,0,5,186946,0,0,0,0,'',"Spell 'Scavenge' target GameObject 'Fjord Hawk Egg'");

DELETE FROM `creature_template_addon` WHERE `entry`= 29403; -- Onslaught Gryphon
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES
(29403, 0, 0, 0, 1, 0, 54422); -- add aura 'Flying' to Onslaught Gryphon

UPDATE creature_loot_template SET Chance=100 WHERE entry=3415 AND item=4893;
UPDATE creature_loot_template SET Chance=100 WHERE entry=3425 AND item=4893;


DELETE FROM `item_loot_template` WHERE `Entry` IN (50301, 54218);
INSERT INTO `item_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES
(50301,46779,0,36.36,0,1,1,50,50,"Landro\'s Pet Box, Path of Cenarius"),
(50301,35223,0,36.36,0,1,1,50,50,"Landro\'s Pet Box, Papa Hummel\'s Old-Fashioned Pet Biscuit"),
(50301,45047,0,27.28,0,1,1,50,50,"Landro\'s Pet Box, Sandbox Tiger"),
(50301,32588,0,0.45,0,1,2,1,1,"Landro\'s Pet Box, Banana Charm"),
(50301,38050,0,0.45,0,1,2,1,1,"Landro\'s Pet Box, Soul-Trader Beacon"),
(50301,34493,0,0.10,0,1,2,1,1,"Landro\'s Pet Box, Dragon Kite"),
(54218,46779,0,36.36,0,1,1,50,50,"Landro\'s Gift Box, Path of Cenarius"),
(54218,35223,0,36.36,0,1,1,50,50,"Landro\'s Gift Box, Papa Hummel\'s Old-Fashioned Pet Biscuit"),
(54218,45047,0,27.28,0,1,1,50,50,"Landro\'s Gift Box, Sandbox Tiger"),
(54218,23720,0,0.50,0,1,2,1,1,"Landro\'s Gift Box, Riding Turtle"),
(54218,49284,0,0.30,0,1,2,1,1,"Landro\'s Gift Box, Reins of the Swift Spectral Tiger"),
(54218,49283,0,0.30,0,1,2,1,1,"Landro\'s Gift Box, Reins of the Spectral Tiger"),
(54218,49286,0,0.30,0,1,2,1,1,"Landro\'s Gift Box, X-51 Nether-Rocket X-TREME"),
(54218,49285,0,0.10,0,1,2,1,1,"Landro\'s Gift Box, X-51 Nether-Rocket"),
(54218,49282,0,0.20,0,1,2,1,1,"Landro\'s Gift Box, Big Battle Bear");

SET @OGUID := 39341;
DELETE FROM `gameobject` WHERE `id`=193988;
INSERT INTO `gameobject` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`) VALUES
(@OGUID+0,193988,615,3,1,3246.47,515.266,58.6196,1.54789,0,0,0.698963,0.715158,-300,0,1),
(@OGUID+1,193988,615,3,1,3154.78,515.889,90.9767,3.18872,0,0,0.999722,-0.0235612,-300,0,1),
(@OGUID+2,193988,615,3,1,3216.13,648.325,87.0783,0.693027,0,0,0.339621,0.940562,-300,0,1),
(@OGUID+3,193988,615,3,1,3383.81,532.522,96.971,3.43866,0,0,0.988989,-0.147986,-300,0,1);




