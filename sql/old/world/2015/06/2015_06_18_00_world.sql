
update gameobject_template set type=1, data0=1, data2=0, data3=0, data4=0, data5=1 where entry=191538;
update gameobject_template set type=1, data0=1, data2=0, data3=0, data4=0, data5=1 where entry=191539;

DELETE FROM `smart_scripts` WHERE `entryorguid` in (29580, 29581);
UPDATE `creature_template` SET `AIName`="" where entry in (29580, 29581);

update spell_target_position set target_map=609, target_position_x=2419.91,target_position_y=-5620.48, target_position_z=420.644 where id=54699; 
update spell_target_position set target_map=609, target_position_x=2402.62,target_position_y=-5633.28, target_position_z=377.021 where id=54725;

delete from creature where guid in (966, 1013);
update creature set phaseMask=3 where id in (28406,28447,28486, 27928);

DELETE FROM `creature` WHERE `id`=28889;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES
(238365, 28889, 609, 1, 4, 0, 0, 2197.04, -5901.11, 100.96, 1.73, 600, 10, 0, 8982, 3155, 1, 0, 0, 0),
(238366, 28889, 609, 1, 4, 0, 0, 2152.08, -5830.67, 101.42, 2.24, 600, 10, 0, 8982, 3155, 1, 0, 0, 0),
(238367, 28889, 609, 1, 4, 0, 0, 2110.69, -5720.33, 100.26, 5.8, 600, 10, 0, 8982, 3155, 1, 0, 0, 0),
(269935, 28889, 609, 1, 4, 0, 0, 2210.61, -5806.8, 101.35, 2.37, 600, 10, 0, 8982, 3155, 1, 0, 0, 0);

update creature_text set BroadcastTextID=28104 where entry=27928 and groupid=0 and id=0;
update creature_text set BroadcastTextID=28105 where entry=27928 and groupid=1 and id=0;
update creature_text set BroadcastTextID=28102 where entry=27928 and groupid=2 and id=0;

update creature_text set BroadcastTextID=28104 where entry=28098 and groupid=0 and id=0;
update creature_text set BroadcastTextID=28104 where entry=28097 and groupid=0 and id=1;
update creature_text set BroadcastTextID=28104 where entry=28100 and groupid=0 and id=2;

update creature_text set BroadcastTextID=28104 where entry=29669 and groupid=0 and id=0;
update creature_text set BroadcastTextID=28104 where entry=29673 and groupid=1 and id=0;
update creature_text set BroadcastTextID=28104 where entry=29674 and groupid=2 and id=0;
update creature_text set BroadcastTextID=28104 where entry=29841 and groupid=3 and id=0;
update creature_text set BroadcastTextID=28104 where entry=29666 and groupid=4 and id=0;
update creature_text set BroadcastTextID=28104 where entry=29840 and groupid=5 and id=0;

delete from creature where guid in (68098, 68479, 1056, 967, 968, 969, 956, 957, 958, 959, 67747, 68007, 68270, 68981);
delete from creature where guid in (1014, 67566, 67828, 68084);

update creature set phaseMask=2 where id in (28525, 28542, 28543, 28544, 28548, 28964);
update creature set phaseMask=3 where id in (28356, 28377, 28385, 28445, 28446, 28447, 28448, 28449, 28647, 28653, 28658, 28683);
update creature set phaseMask=4 where id in (28889, 28893, 28903, 28907, 28908, 28910, 28911, 28912, 28913, 28914, 28919, 28943, 28957, 29053);
update creature set phaseMask=7 where id in (25462, 28383, 28391, 28765);
update creature set phaseMask=35 where id in (29047);
update creature set phaseMask=68 where id in (28549, 28550, 28551, 28552, 28553, 28554, 28555, 28556, 28945, 29000, 29032, 29038, 29061, 29065);
update creature set phaseMask=68 where id in (29067, 29068, 29070, 29071, 29072, 29073, 29074, 29077, 29078, 49355, 49356);
update creature set phaseMask=71 where id in (28444, 28489, 28510);
update creature set phaseMask=128 where id in (29112, 29113, 29173, 29186, 29192, 29199, 29200, 29204, 29206);
update creature set phaseMask=192 where id in (29107, 29108, 29110);
update creature set phaseMask=199 where id in (28471, 29472, 28474, 28481, 29203, 29205, 29207, 29208);
update creature set phaseMask=231 where id in (29488, 29501, 32541);
update creature set phaseMask=487 where id in (29580, 29581);

delete from creature where guid in (962, 963, 964, 965, 238154);

delete from creature where map=0 and id in (28490, 28491, 28500);

update creature set phaseMask=2 where id in (28529, 28530, 28559, 28560, 28594);
update creature set phaseMask=3 where id in (28406, 28557, 28605, 28606, 28607, 28608, 28609, 28642, 28709, 28766, 29212);
update creature set phaseMask=4 where id in (28610, 28654, 28660, 28890, 28891, 28892, 28896, 28897, 28898, 28901, 28905, 28906, 28933, 28934);
update creature set phaseMask=4 where id in (28936, 28937, 28939, 28940, 28941, 28942, 29030, 29031);
update creature set phaseMask=7 where id in (28358, 28390, 28392, 28393, 28487, 28760);
update creature set phaseMask=32 where id in (28768, 28769, 28782);
update creature set phaseMask=64 where id in (29101, 29102, 29103, 29104, 29106, 29115, 29136);
update creature set phaseMask=68 where id in (28946, 29080);
update creature set phaseMask=71 where id in (28367, 28386, 28488, 28490);
update creature set phaseMask=128 where id in (29185, 29189, 29190, 29191, 29193, 29219);
update creature set phaseMask=199 where id in (28500, 28505, 28506);
update creature set phaseMask=65535 where id in (28512, 28935, 29259);






