/*
SQLyog Community v12.2.6 (64 bit)
MySQL - 5.6.28-log Fine Tune some creatures on Tranquil Coast
*********************************************************************
*/
/*!40101 SET NAMES utf8 */;
update `creature_template` set `unit_flags`=197376 where `entry` in(39041,39039);
update `creature_template` set `unit_flags`=36873 where `entry`=40785;
delete from `creature_template_addon` where `entry`=39042;
insert into `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `auras`) values('39042','0','0','0','1','0','0','0','0','');
delete from `creature_addon` WHERE `guid` IN(248176,248177,248179,248181,248184,248214,248219,248222,248223,248224,248225,248226,248227,248231,248234,248238,248241,248243,248245,248246,248249,248253,248257,248260,248264,248267,248274,248275,248281,248287,248291,48295,248296,248297,248299,248306,248311,248316,248322,248327,248329,248337,248340,248456);
delete from `smart_scripts` WHERE `entryorguid`=40785;

insert into `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values('40785','0','0','0','4','0','100','0','3000','3000','3000','3000','11','73485','2','0','0','0','0','2','0','0','0','0','0','0','0','gnomeregan machine gun  on aggro cast machine gun.');
insert into `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values('40785','0','2','0','4','0','100','0','1000','1000','1000','1000','21','0','0','0','0','0','0','1','0','0','0','0','0','0','0','gnomeregan machine gun  on aggro disable combat movement.( creature leaves its seat on vehicle to follow victim.)');
insert into `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values('40785','0','3','0','0','0','100','0','1000','2000','5000','6000','11','73485','2','0','0','0','0','2','0','0','0','0','0','0','0','gnomeregan machine gun  IC cast machine gun @ target');

