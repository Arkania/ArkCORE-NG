

DELETE FROM `creature_addon` WHERE `guid`=277165;
INSERT INTO `creature_addon` (`guid`, `mount`, `bytes1`, `bytes2`, `auras`) VALUES
(277165, 0, 0x10000, 0x1, "82059 80681"); -- Colonel Troteman - Apply Quest Invis Zone 18, Spyglass

DELETE FROM `creature` WHERE `guid`=277165;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `MovementType`) VALUES
(277165, 43733, 0, 1, 1, -9142.45, -3037.45, 108.7803, 2.495821, 120, 0, 0); -- Colonel Troteman (Area: Redridge Mountains) (Auras: 82059 - Apply Quest Invis Zone 18, 80681 - Spyglass)

-- Quest ID: 26713 (Showdown at Stonewatch)
update quest_template set Flags=5242880 where Id=26713;

DELETE FROM `creature_equip_template` WHERE `entry` IN (43812,43826,43827,43828,43829);
INSERT INTO `creature_equip_template` (`entry`, `id`, `itemEntry1`, `itemEntry2`, `itemEntry3`) VALUES
(43812, 1,  5278, 	  0, 42775),
(43826, 1, 14836, 	  0, 0),
(43827, 1, 30204,     0, 0),
(43828, 1, 12786, 12893, 0),
(43829, 1, 33981, 33981, 0);

DELETE FROM `creature_template_addon` WHERE (`entry`=43812);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES (43812, 0, 0, 0, 2, 0, "");

update creature_template set AIName="", ScriptName="npc_john_j_keeshan_43812" where entry=43812;
update creature_template set AIName="", ScriptName="npc_messner_43826" where entry=43826;
update creature_template set AIName="", ScriptName="npc_jorgensen_43827" where entry=43827;
update creature_template set AIName="", ScriptName="npc_danforth_43828" where entry=43828;
update creature_template set AIName="", ScriptName="npc_krakauer_43829" where entry=43829;

UPDATE `creature_template` SET `type_flags`=2147483656, AIName="", ScriptName="npc_Darkblaze" WHERE `entry`=43496; -- Darkblaze

DELETE FROM `creature_template_addon` WHERE `entry`=43496;
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `bytes2`, `auras`) VALUES
(43496, 0, 0x10000, 0x1, "82059");

-- Darkblaze is spawned by spell 81953
delete from creature where guid=12842 and id=43496;

