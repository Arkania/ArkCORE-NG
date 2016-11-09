


UPDATE gameobject SET phaseIds="179" WHERE guid=168989;

UPDATE gameobject SET phaseIds="179" WHERE guid=168949;

UPDATE gameobject SET phaseIds="180" WHERE guid=168993;

UPDATE gameobject SET phaseIds="180" WHERE guid=169095;

delete from creature where guid=248256;

UPDATE creature_template SET dynamicflags=0 WHERE entry=36470;

delete from creature_queststarter where id=36471 and quest=14245;

delete from spell_linked_spell where spell_trigger=68938 and spell_effect=69040;

delete from spell_linked_spell where spell_trigger=68750;
insert into spell_linked_spell values 
(68750, -67854, 1, "remove old phases when add quest phase 5");

update creature set spawndist=0, MovementType=0 where id=38526;

UPDATE creature_template SET dynamicflags=0 WHERE entry=38511;

UPDATE creature_template SET dynamicflags=0 WHERE entry=38516;

UPDATE creature_template SET dynamicflags=0 WHERE entry=38518;

UPDATE creature_template SET dynamicflags=0 WHERE entry=38514;

UPDATE creature_template SET dynamicflags=0 WHERE entry=38122;

-- Prepare Landing Site and Town-in-a-box.
-- MAIN NAMED CREATURES
DELETE FROM `creature` WHERE `map`=648 and `guid`  IN(245299,2452965,245291,245298,249595,245284,245296,245297,248262,245285,248218,245292,245286);
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseIds`,`phaseGroup`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES (245284,38387,648,0,0,1,'180',0,0,0,927.372,2343.74,5.80698,4.03171,500,0,0,102,0,0,0,0,0);
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseIds`,`phaseGroup`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES (245285,38120,648,0,0,1,'180',0,0,0,918.205,2336.29,3.3865,3.03687,500,0,0,198,0,0,0,0,0);
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseIds`,`phaseGroup`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES (245286,38511,648,0,0,1,'180',0,0,0,907.32,2344.27,5.39862,5.67232,500,0,0,102,0,0,0,0,0);
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseIds`,`phaseGroup`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES (245291,38516,648,0,0,1,'180',0,0,0,913.257,2325.39,5.3238,1.11701,500,0,0,178,382,0,0,0,0);
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseIds`,`phaseGroup`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES (245292,38518,648,0,0,1,'180',0,0,0,925.368,2327.16,5.25289,2.35619,500,0,0,198,0,0,0,0,0);
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseIds`,`phaseGroup`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES (245296,38514,648,0,0,1,'180',0,0,0,920.649,2346.36,4.86977,4.08407,500,0,0,178,420,0,0,0,0);
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseIds`,`phaseGroup`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES (245297,38122,648,0,0,1,'180',0,0,0,928.863,2340.48,5.03533,3.94444,500,0,0,186,191,0,0,0,0);
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseIds`,`phaseGroup`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES (245298,38124,648,0,0,1,'180',0,0,0,907.457,2339.76,4.91231,2.77507,500,0,0,198,0,0,0,0,0);
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseIds`,`phaseGroup`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES (245299,45286,648,0,0,1,'180',0,0,0,901.587,2319.55,5.58772,0.872665,500,0,0,328,0,0,0,0,0);
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseIds`,`phaseGroup`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES (248218,36615,648,0,0,1,'180',0,0,0,920.079,2332.71,5.02537,4.44376,500,0,0,137,0,0,0,0,0);
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseIds`,`phaseGroup`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES (248262,36471,648,0,0,1,'180',0,0,0,932.151,2335.48,5.06028,3.00197,500,0,0,102,0,0,0,0,0);
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseIds`,`phaseGroup`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES (249595,42473,648,0,0,1,'180',0,30142,0,913.408,2354.65,5.44061,4.50295,300,0,0,120,0,0,0,0,0);

-- Wild Clucker.
UPDATE `creature` SET `phaseids`=180 WHERE `guid` IN(245303,245302,245304,245305,245306,245310,245309,245301,245308,245311);
-- Goblin Survivor/Citizen: needs more spawns.
UPDATE `creature` SET `phaseids`=180 WHERE `guid` IN(246790,246787,246786,247545,247548,247546,247547);

-- SELECT * FROM `gameobject_template` WHERE entry IN(205507,205517,205518,205523,205510,205506,205515,205516,205505,205503,205500,205501,205502,201948,202104,202543,202108,201938);
-- SELECT * FROM `gameobject` WHERE id IN(205507,205517,205518,205523,205510,205506,205515,205516,205505,205503,205500,205501,205502,201948,202104,202543,202108,201938);
 
DELETE FROM `spell_target_position` WHERE target_map=648 AND id IN(68804,68815,68817);

UPDATE `gameobject` SET `phaseids`=180 WHERE `guid`IN(168993,169095,168990,168991,168992,168960,168977,168957,168980,168978,168963,168970,168979,168956,168973,168955,168974168974,168975,168976);

-- Foreman Dampwick...FIRST PART TOWN-IN-A-BOX.
DELETE FROM `creature_text` WHERE `entry`=36470;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`,`BroadcastTextID`) VALUES (36470,0,0,'Hurry, $N, deploy the Town-In-A-Box. Our people are trapped inside! Oh! I almost forgot your parachute.',12,0,100,25,0,0,'',49886);

update arkcore_string set content_default="Map: %u (%s) Zone: %u (%s) Area: %u (%s)\nX: %f Y: %f Z: %f Orientation: %f\ngrid[%u,%u]cell[%u,%u] InstanceID: %u\nZoneX: %f ZoneY: %f\nGroundZ: %f FloorZ: %f Have height data (Map: %u VMap: %u MMap: %u)"  where entry=101;
update arkcore_string set content_loc3="Karte: %u (%s) Zone: %u (%s) Gebiet: %u (%s)\nX: %f Y: %f Z: %f Orientierung: %f\ngrid[%u,%u]Zelle[%u,%u] InstanzID: %u/nZoneX: %f ZoneY: %f\n GroundZ: %f FloorZ: %f Have height data (Map: %u VMap: %u)" where entry=101;


