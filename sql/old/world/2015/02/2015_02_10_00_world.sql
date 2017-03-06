
update quest_template set PrevQuestId=26651 where Id=26668;
update quest_template set PrevQuestId=26694 where Id=26708;
update quest_template set PrevQuestId=26692 where Id=26694;
update quest_template set PrevQuestId=26668 where Id=26693;
update quest_template set PrevQuestId=26668 where Id=26692;

update creature_template set AIName="", ScriptName="npc_john_j_keeshan_43611" where entry=43611;

delete from creature where guid=16746 and id=43734;
delete from creature where guid=26527 and id=43300;

DELETE FROM `creature_addon` WHERE (`guid`=26573);
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
(26573, 0, 0, 0, 4097, 378, "81795");

DELETE FROM `creature_addon` WHERE (`guid`=9249);
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
(9249, 0, 0, 0, 0, 0, "81805");

DELETE FROM `creature` WHERE `guid` in (26648,9349,9348,9350,26644);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `MovementType`) VALUES
(26644, 43611, 0, 1, 1, -9636.37, -3474.71, 121.9651, 2.111848, 120, 0, 0), -- John J. Keeshan (Area: Redridge Mountains) (Auras: 81580 - Apply Quest Invis Zone 13, 80642 - Keeshan's Quiver)
(9350, 43610, 0, 1, 1, -9639.47, -3476.01, 121.9651, 1.780236, 120, 0, 0), -- Messner (Area: Redridge Mountains) (Auras: 81580 - Apply Quest Invis Zone 13)
(9348, 43609, 0, 1, 1, -9630.64, -3471.34, 121.8537, 2.391101, 120, 0, 0), -- Jorgensen (Area: Redridge Mountains) (Auras: 81583 - Apply Quest Invis Zone 14)
(9349, 43608, 0, 1, 1, -9642.72, -3476.93, 121.9651, 1.937315, 120, 0, 0), -- Krakauer (Area: Redridge Mountains) (Auras: 81580 - Apply Quest Invis Zone 13)
(26648, 43607, 0, 1, 1, -9633.55, -3473.22, 121.9392, 2.251475, 120, 0, 0); -- Danforth (Area: Redridge Mountains) (Auras: 81580 - Apply Quest Invis Zone 13)

DELETE FROM `creature_addon` WHERE `guid` in (26648,9349,9348,9350,26644);
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
(26648, 0, 0, 4096, 1, 0, "81496 81580 81583"),
(9349, 0, 0, 4096, 1, 0, "81496 81580 81583"),
(9348, 0, 0, 4096, 1, 0, "81496 81580 81583"),
(9350, 0, 0, 4096, 1, 0, "81496 81580 81583"),
(26644, 0, 0, 4096, 2, 0, "80642 81496 81580 81583");

DELETE FROM `creature` WHERE `guid` in (269876,269877,269878,269879,269880,269881,269882,269883,269884);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `MovementType`) VALUES
(269876, 43572, 0, 1, 1, -9620.11, -3486.56, 122.0393, 1.064651, 120, 0, 0), -- Kidnapped Redridge Citizen (Area: Redridge Mountains) (Auras: 81580 - Apply Quest Invis Zone 13)
(269877, 43572, 0, 1, 1, -9607.94, -3489.54, 122.0393, 3.525565, 120, 0, 0), -- Kidnapped Redridge Citizen (Area: Redridge Mountains) (Auras: 81580 - Apply Quest Invis Zone 13)
(269878, 43571, 0, 1, 1, -9599.92, -3497.6, 122.0393, 2.687807, 120, 0, 0), -- Kidnapped Redridge Citizen (Area: Redridge Mountains) (Auras: 81580 - Apply Quest Invis Zone 13)
(269879, 43572, 0, 1, 1, -9627.73, -3483.46, 122.0393, 0.9075712, 120, 0, 0), -- Kidnapped Redridge Citizen (Area: Redridge Mountains) (Auras: 81580 - Apply Quest Invis Zone 13)
(269880, 43571, 0, 1, 1, -9610.65, -3488.24, 122.0393, 5.183628, 120, 0, 0), -- Kidnapped Redridge Citizen (Area: Redridge Mountains) (Auras: 81580 - Apply Quest Invis Zone 13)
(269881, 43572, 0, 1, 1, -9625.46, -3482.62, 122.0393, 3.193953, 120, 0, 0), -- Kidnapped Redridge Citizen (Area: Redridge Mountains) (Auras: 81580 - Apply Quest Invis Zone 13)
(269882, 43572, 0, 1, 1, -9604.88, -3498.8, 122.0393, 0.4363323, 120, 0, 0), -- Kidnapped Redridge Citizen (Area: Redridge Mountains) (Auras: 81580 - Apply Quest Invis Zone 13)
(269883, 43571, 0, 1, 1, -9627.51, -3481.51, 122.0393, 5.183628, 120, 0, 0), -- Kidnapped Redridge Citizen (Area: Redridge Mountains) (Auras: 81580 - Apply Quest Invis Zone 13)
(269884, 43571, 0, 1, 1, -9610.29, -3490.61, 122.0393, 1.064651, 120, 0, 0); -- Kidnapped Redridge Citizen (Area: Redridge Mountains) (Auras: 81580 - Apply Quest Invis Zone 13)

DELETE FROM `creature_addon` WHERE `guid` in (269876,269877,269878,269879,269880,269881,269882,269883,269884);
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
(269876, 0, 0, 0, 2, 0, "81496 81580 81583"),
(269877, 0, 0, 0, 2, 0, "81496 81580 81583"),
(269878, 0, 0, 0, 2, 0, "81496 81580 81583"),
(269879, 0, 0, 0, 2, 0, "81496 81580 81583"),
(269880, 0, 0, 0, 2, 0, "81496 81580 81583"),
(269881, 0, 0, 0, 2, 0, "81496 81580 81583"),
(269882, 0, 0, 0, 2, 0, "81496 81580 81583"),
(269883, 0, 0, 0, 2, 0, "81496 81580 81583"),
(269884, 0, 0, 0, 2, 0, "81496 81580 81583");

DELETE FROM `creature_equip_template` WHERE `entry` IN (43607,43608,43609,43610,43611);
INSERT INTO `creature_equip_template` (`entry`, `id`, `itemEntry1`, `itemEntry2`, `itemEntry3`) VALUES
(43611, 1, 5278, 0, 42775), -- John J. Keeshan
(43607, 1,  12786, 12893, 0), -- Danforth
(43608, 1,  33981, 33981, 0), -- Krakauer
(43609, 1,  30204, 0, 0), -- Jorgensen
(43610, 1,  14836, 0, 0); -- Messner




