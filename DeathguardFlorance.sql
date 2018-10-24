/*
--Hallows Nicht.
--missing world event npc.  https://cata-twinhead.twinstar.cz/?npc=24491 
*********************************************************************
*/
update `creature_tempate` set `npcflag`=1 where `entry`=24491;
delete from `creature` where `id`=24491;
insert into `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseId`, `phaseGroup`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `VerifiedBuild`) values('290856','24491','0','85','85','1','0','0','0','0','2253.15','474.673','34.1277','3.25809','300','0','0','1302','0','0','0','0','0','10505');
delete from `game_event_creature` where `guid`=290856;
insert into `game_event_creature` (`eventEntry`, `guid`) values('12','290856');
delete from `creature_equip_template` where `entry` and `id`=1;
insert into `creature_equip_template` (`entry`, `id`, `itemEntry1`, `itemEntry2`, `itemEntry3`) values('24491','1','1905','0','2551');
