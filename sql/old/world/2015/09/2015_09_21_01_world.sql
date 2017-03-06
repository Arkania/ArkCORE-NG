
DELETE FROM `creature` WHERE `guid`=278397;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES
(278397, 50415, 654, 1, 12, 0, 0, -1792.98, 1427.89, 12.4587, 2.95569, 300, 0, 0, 104612, 0, 0, 0, 0, 0);

delete from creature_text where entry=50415 and groupid=1;
insert into creature_text values 
(50415, 1, 0, "You've been bitten by a worgen. It's probably nothing, but it sure stings a little.$B$B|TInterfaceIconsINV_Misc_monsterfang_02.blp:32|t", 42, 0, 100, 0, 0, 0, "Josiah Event Trigger", 50192);

update creature_template_addon set auras ="49414" where entry in (34936, 35753);


