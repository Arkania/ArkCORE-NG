
delete from creature where id=43714 and guid=9248;

SET @ENTRY=43728;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY AND `groupid`=0 AND `id`=0;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `emote`, `duration`, `sound`, `BroadcastTextID`) VALUES 
(@ENTRY, 0, 0, "At your service.", 12, 0, 0, 0, 43811);

update creature_text set emote=5 where entry=43611 and groupid=1 and id=0;
update creature_text set emote=6 where entry=43607 and groupid=1 and id=0;

delete from creature where guid=9248 and id=43714;
insert INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(9248, 43714, 0, 1, 1, 25289, 0, -9646.64, -3454.93, 116.645, 1.93731, 300, 0, 0, 7260, 0, 0, 0, 0, 0);

DELETE FROM `creature_addon` WHERE (`guid`=9248);
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
(9248, 0, 0, 0, 1, 0, "81795");

update creature_template set AIName="", ScriptName="npc_colonel_troteman_43733" where entry=43733;


