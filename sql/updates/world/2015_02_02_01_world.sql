
update quest_template set flags=8 where Id=26563;

update creature set spawntimesecs=600 where guid=33828 and id=43369;

delete from creature where guid in (9358,9359,9360,9361);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(9358, 43435, 0, 1, 1, 33371, 1, -9199.89, -2156.77, 57.2691, 2.74017, 300, 0, 0, 1930, 0, 0, 0, 0, 0),
(9359, 43432, 0, 1, 1, 33374, 1, -9200.94, -2157.94, 57.2693, 2.14675, 300, 0, 0, 1930, 0, 0, 0, 0, 0),
(9360, 43434, 0, 1, 1, 33372, 1, -9200.21, -2153.62, 57.269, 4.04916, 300, 0, 0, 1930, 0, 0, 0, 0, 0),
(9361, 43433, 0, 1, 1, 33373, 1, -9201.71, -2153.14, 57.2694, 4.66003, 300, 0, 0, 1780, 0, 0, 0, 0, 0);


DELETE FROM `creature_addon` WHERE `guid` in (9358,9359,9360,9361);
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
(9358, 0, 0, 65536, 0, 0, 81201),
(9359, 0, 0, 65536, 0, 0, 81201),
(9360, 0, 0, 65536, 0, 0, 81201),
(9361, 0, 0, 65536, 0, 0, 81201);


DELETE FROM `creature_text` WHERE `entry` in (43184,43434,43435) AND `groupid`=0 AND `id`=0;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `emote`, `duration`, `sound`, `BroadcastTextID`) VALUES 
(43184, 0, 0, "Looks like we got a war to win.", 12, 0, 0, 0, 43516),
(43435, 0, 0, "PAIN TRAIN INCOMING!", 12, 0, 0, 0, 43517),
(43434, 0, 0, "JOHNNY'S BACK, BABY! YEA!", 12, 0, 0, 0, 43518);








