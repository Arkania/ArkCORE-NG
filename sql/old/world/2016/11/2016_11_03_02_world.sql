

UPDATE creature SET position_x=947.8141, position_y=3860.461, position_z=.0011, orientation=3.2466 WHERE guid=247768;

UPDATE creature SET position_x=875.1951, position_y=3832.971, position_z=.0015, orientation=3.1367 WHERE guid=247767;

UPDATE creature_template SET ScriptName="npc_alliance_sailor_36176" WHERE entry=36176;

UPDATE quest_template SET Flags=786432 WHERE Id=14243;

UPDATE creature_template SET minlevel=9, maxlevel=9, faction=2204, unit_flags=8, unit_flags2=67584, VehicleId=508, ScriptName="npc_cyclone_of_the_elements_36178" WHERE entry=36178;

DELETE FROM creature_template_addon WHERE entry=36178;
INSERT INTO creature_template_addon VALUES 
(36178, 0, 0, 50331648, 1, 0, "");

delete from creature where guid=253773;

DELETE FROM `waypoint_data` WHERE `id`=3617801;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`, `orientation`,`move_flag`,`action_chance`) VALUES
(3617801,1,1042.181,3857.24,23.60183,0 ,1, 100),
(3617801,2,1071.38,3852.879,21.18516,0 ,1, 100),
(3617801,3,1097.259,3826.478,18.90739,0 ,1, 100),
(3617801,4,1097.905,3780.767,20.29626,0 ,1, 100),
(3617801,5,1062.802,3755.345,22.85184,0 ,1, 100),
(3617801,6,1033.106,3773.803,23.60179,0 ,1, 100),
(3617801,7,1021.788,3827.314,20.99073,0 ,1, 100),
(3617801,8,1004.835,3861.208,19.96292,0 ,1, 100),
(3617801,9,962.5104,3859.353,20.29623,0 ,1, 100),
(3617801,10,937.9149,3841.934,19.26847,0 ,1, 100),
(3617801,11,903.8854,3827.217,19.57398,0 ,1, 100),
(3617801,12,867.1771,3849.851,21.32399,0 ,1, 100),
(3617801,13,866.3246,3895.795,21.51845,0 ,1, 100),
(3617801,14,893.6545,3935.708,20.87961,0 ,1, 100),
(3617801,15,936.5087,3944.062,21.12957,0 ,1, 100),
(3617801,16,968.7101,3914.839,20.3796,0 ,1, 100),
(3617801,17,952.6996,3861.26,24.54637,0 ,1, 100),
(3617801,18,936.1754,3820.981,21.93524,0 ,1, 100),
(3617801,19,943.9549,3785.924,22.26854,0 ,1, 100),
(3617801,20,975.882,3771.541,20.71306,0 ,1, 100),
(3617801,21,1004.325,3782.394,21.71304,0 ,1, 100),
(3617801,22,1022.352,3831.351,24.62974,0 ,1, 100);

DELETE FROM `waypoint_data` WHERE `id`=3617802;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`, `orientation`,`move_flag`,`action_chance`) VALUES
(3617802,1,1005.4,3679.87,18.3379,0 ,1, 100),
(3617802,2,927.725,3454.32,19.5739,0 ,1, 100),
(3617802,3,898.275,3355.84,20.8316,0 ,1, 100),
(3617802,4,954.309,3218.92,115.497,0 ,1, 100),
(3617802,5,978.232,3172.31,158.981,0 ,1, 100),
(3617802,6,1007.47,3103.48,156.791,0 ,1, 100),
(3617802,7,960.093,3009.7,151.842,0 ,1, 100),
(3617802,8,890.176,2916.18,134.772,0 ,1, 100),
(3617802,9,889.766,2913.93,134.586,0 ,1, 100),
(3617802,10,872.972,2790.81,129.481,0 ,1, 100),
(3617802,11,872.972,2790.81,129.481,0 ,1, 100),
(3617802,12,872.673,2763.38,118.886,0 ,1, 100);

-- Rocket Sling gossip, Wild Overlook.
UPDATE`gossip_menu_option` SET `OptionBroadcastTextId`=36458,option_id=1,npc_option_npcflag=1 WHERE `menu_id`=10808;
-- 99% Wild Overlook objects.
UPDATE `gameobject` SET phaseids="179" WHERE `id`IN(196439,196444,196427,196449,196451,196433,196436,196420,196435,196438,196443,196843,196422,196426,196446,196448,196452,196431,196421,196424,196434,196432);
-- ships rowing boats.
UPDATE `gameobject` SET phaseids="171 179" WHERE `id` IN(196828,196827,196826,196825,196824,196822,196823,196820,196821,196818,196819);
-- disable gravity flag, Cyclone Vehicle.
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=36178;

delete from creature_template where entry=8777000;

update creature set position_x=874.286072, position_y=2759.904785, position_z=119.699837, orientation=1.944736 where guid=246049;

update creature set position_x=870.866760, position_y=2759.618408, position_z=119.488274, orientation=1.854416 where guid=246050;

update creature set position_x=881.091858, position_y=2759.868164, position_z=120.278572, orientation=1.799438 where guid=246051;

update creature set position_x=877.853271, position_y=2760.745361, position_z=120.121780, orientation=1.520626 where guid=246052;

update creature set position_x=879.467896, position_y=2761.086914, position_z=120.068886, orientation=1.807289 where guid=246056;

UPDATE creature SET position_x=888.7877, position_y=2735.965, position_z=124.4201, orientation=4.3756 WHERE guid=246085;

UPDATE creature SET position_x=865.1755, position_y=2757.989, position_z=118.8996, orientation=1.501 WHERE guid=246057;

update creature set phaseIds="179" where guid in (246056,246058,246059,246057);

update gameobject set phaseIds="", phaseGroup=430 where guid in (168879,168874,168890,168894,168896,168911,168920,168885,168925,168918,168884);
update gameobject set phaseIds="", phaseGroup=430 where guid in (168899,168889,168888,168887,168901,168924,168917,168919,168897,168916,168895);
update gameobject set phaseIds="", phaseGroup=430 where guid in (168792,168921,168886,168788,168906,168910,168898,168907,168908);

update creature set phaseIds="179" where guid in (245979,248481,248444,246263,246080,246079,246078,246077,246075,246076,246071,246083);

