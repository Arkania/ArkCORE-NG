
-- Misc Gnomer

UPDATE `creature_template` SET `npcflag`=51 WHERE `entry`=1228;
UPDATE `creature_template` SET `npcflag`=4224 WHERE `entry`IN(42626,42335);-- fix repair function.
-- npc depreciated. temp phase out until removal.
UPDATE `creature` SET phaseId=172 WHERE `id` =1122;
UPDATE `creature` SET phaseId=172 WHERE `id` =1123;
UPDATE `creature` SET phaseId=172 WHERE `id` =1121;
UPDATE `creature` SET phaseId=172 WHERE `id` =1124;
UPDATE `creature` SET phaseId=172 WHERE `id` =1124;
-- fix npc spawn wrong part of zone.
DELETE FROM `creature` WHERE guid IN(59634,59542,59924,59923,59989,59440,59439,59418,59630,59635,59451,59452,59545);

DELETE FROM `creature_template_addon` WHERE `entry`=39368;
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `auras`) VALUES('39368','0','0','0','1','378','0','0','0',NULL);
-- fix trainer gossip.
UPDATE `creature_equip_template` SET `itemEntry1`=53056,`itemEntry2`=0,`itemEntry3`=0 WHERE `entry`=39368;
UPDATE `conditions` SET `ConditionValue1`=128,`Comment`="Show gossip option if player is a Mage" WHERE SourceGroup =4463 and `SourceEntry` IN(0,1,2);
-- fix quest progress.
UPDATE `quest_template` SET `PrevQuestId`=25724 WHERE `id` =25667;
UPDATE `quest_template` SET `PrevQuestId`=25724 WHERE `id` =25668;
UPDATE `quest_template` SET `PrevQuestId`=0 WHERE `id` =25724;

-- missing captured demolition gnomes, source:previous arkcoreNG DB.
DELETE FROM `creature` WHERE `id`=42645;

INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseId`, `phaseGroup`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
('63077','42645','0','0','0','1','169','0','33029','0','-5578.82','305.84','395.143','5.89921','500','0','0','86','0','0','0','0','0'),
('63066','42645','0','0','0','1','169','0','33029','0','-5593.89','394.281','382.52','4.41568','500','0','0','86','0','0','0','0','0'),
('62699','42645','0','0','0','1','169','0','33028','0','-5635.69','428.602','382.962','2.35619','500','0','0','86','0','0','0','0','0'),
('62687','42645','0','0','0','1','169','0','33027','0','-5634.76','304.082','389.246','1.62316','500','0','0','86','0','0','0','0','0'),
('62656','42645','0','0','0','1','169','0','33027','0','-5587.67','444.623','382.478','1.8675','500','0','0','86','0','0','0','0','0'),
('62555','42645','0','0','0','1','169','0','33029','0','-5582.41','359.141','388.461','2.60054','500','0','0','86','0','0','0','0','0'),
('62114','42645','0','0','0','1','169','0','33027','0','-5631.99','373.007','384.821','3.03687','500','0','0','86','0','0','0','0','0'),
('61806','42645','0','0','0','1','169','0','33029','0','-5602.94','336.665','389.077','2.63545','500','0','0','86','0','0','0','0','0'),
('61471','42645','0','0','0','1','169','0','33029','0','-5576.1','500.583','382.509','1.15192','500','0','0','86','0','0','0','0','0'),
('61351','42645','0','0','0','1','169','0','33026','0','-5632.95','334.45','388.797','0.977384','500','0','0','86','0','0','0','0','0');


