

update creature set phaseId=0, phaseGroup=418 where guid in (657,954,1774,1848,1992,245284,245291,245292,245296,284886);

update creature set phaseId=182, phaseGroup=0 where guid=284886;

delete from creature where guid=284885;

DELETE FROM creature WHERE id=38122 AND guid=9213;
INSERT INTO creature VALUES 
(9213, 38122, 648, 0, 0, 1, 182, 0, 0, 0, 928.863, 2340.48, 5.03533, 5.0267, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=38513 AND guid=9214;
INSERT INTO creature VALUES 
(9214, 38513, 648, 0, 0, 1, 182, 0, 0, 0, 906.536, 2329.74, 5.11577, 2.39394, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=38381 AND guid=9215;
INSERT INTO creature VALUES 
(9215, 38381, 648, 0, 0, 1, 182, 0, 0, 0, 908.517, 2346.17, 5.37892, 5.60237, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=38515 AND guid=9216;
INSERT INTO creature VALUES 
(9216, 38515, 648, 0, 0, 1, 182, 0, 0, 0, 916.425, 2347.45, 4.88787, 4.57276, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=38517 AND guid=9217;
INSERT INTO creature VALUES 
(9217, 38517, 648, 0, 0, 1, 182, 0, 0, 0, 908.773, 2349.06, 5.63632, 0.610439, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=38387 AND guid=9218;
INSERT INTO creature VALUES 
(9218, 38387, 648, 0, 0, 1, 182, 0, 0, 0, 927.372, 2343.74, 5.80698, 4.03171, 500, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=38518 AND guid=9219;
INSERT INTO creature VALUES 
(9219, 38518, 648, 0, 0, 1, 182, 0, 0, 0, 925.368, 2327.16, 5.25289, 2.35619, 500, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=38514 AND guid=9220;
INSERT INTO creature VALUES 
(9220, 38514, 648, 0, 0, 1, 182, 0, 0, 0, 920.649, 2346.36, 4.86977, 5.80116, 500, 0, 0, 0, 0, 0, 0, 0, 0);

update creature set phaseGroup=415 where id=38526;

DELETE FROM creature WHERE guid IN (145087, 145088, 145089, 145090, 145091, 145092, 145093, 145094, 145095, 145096, 145097, 145098, 145099, 145100, 145101, 145102, 145103, 145104, 145105, 145106, 145107, 145108, 145109, 145110, 145111, 145112, 145113, 145114, 145115, 145116, 145117);
INSERT INTO creature VALUES 
(145087, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 919.696, 2335.68, 3.57099, 2.75762, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145088, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 920.832, 2342.61, 4.41534, 0.802851, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145089, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 924.17, 2329.83, 4.49568, 5.16617, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145090, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 927.236, 2337.68, 4.57711, 2.44346, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145091, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 923.052, 2328.65, 4.70141, 5.70723, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145092, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 912.502, 2346.03, 4.81654, 1.46608, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145093, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 907.708, 2331.28, 4.89852, 4.04916, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145094, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 926.861, 2316.88, 7.34103, 0.959931, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145095, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 917.943, 2312.6, 8.13561, 3.14159, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145096, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 923.179, 2309.44, 8.74232, 1.01229, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145097, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 912.712, 2303.81, 9.60971, 2.63545, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145098, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 918.219, 2295.18, 11.0823, 1.48353, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145099, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 926.29, 2291.72, 11.4071, 2.30383, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145100, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 908.901, 2293.83, 11.7138, 0.942478, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145101, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 910.097, 2284.71, 12.7638, 1.29154, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145102, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 918.526, 2283.81, 13.2561, 1.27409, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145103, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 907.873, 2276.8, 13.5413, 0.750492, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145104, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 914.993, 2266.81, 15.9513, 1.22173, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145105, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 920.346, 2260.37, 17.3724, 0.645772, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145106, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 914.212, 2243.11, 21.4836, 1.53589, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145107, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 916.179, 2242.3, 21.662, 1.72788, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145108, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 910.279, 2238.36, 23.5608, 1.32645, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145109, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 912.707, 2231.82, 26.3146, 1.25664, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145110, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 913.495, 2223.53, 30.4695, 1.62316, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145111, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 912.573, 2214.21, 35.847, 1.5708, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145112, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 910.25, 2214.33, 36.1013, 1.46608, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145113, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 907.561, 2204.76, 42.2392, 1.43117, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145114, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 908.413, 2195.95, 47.5824, 1.39626, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145115, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 906.309, 2188.37, 52.6147, 1.37881, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145116, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 909.727, 2186.25, 53.6632, 1.5708, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(145117, 38531, 648, 0, 0, 1, 182, 0, 0, 0, 904.832, 2173.78, 60.5834, 1.46608, 120, 0, 0, 1, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid between 145087 and 145117;
INSERT INTO creature_addon VALUES 
(145087, 0, 0, 0, 1, 0, "29266 71333"),
(145088, 0, 0, 0, 1, 0, "29266 71333"),
(145089, 0, 0, 0, 1, 0, "29266 71333"),
(145090, 0, 0, 0, 1, 0, "29266 71333"),
(145091, 0, 0, 0, 1, 0, "29266 71333"),
(145092, 0, 0, 0, 1, 0, "29266 71333"),
(145093, 0, 0, 0, 1, 0, "29266 71333"),
(145094, 0, 0, 0, 1, 0, "29266 71333"),
(145095, 0, 0, 0, 1, 0, "29266 71333"),
(145096, 0, 0, 0, 1, 0, "29266 71333"),
(145097, 0, 0, 0, 1, 0, "29266 71333"),
(145098, 0, 0, 0, 1, 0, "29266 71333"),
(145099, 0, 0, 0, 1, 0, "29266 71333"),
(145100, 0, 0, 0, 1, 0, "29266 71333"),
(145101, 0, 0, 0, 1, 0, "29266 71333"),
(145102, 0, 0, 0, 1, 0, "29266 71333"),
(145103, 0, 0, 0, 1, 0, "29266 71333"),
(145104, 0, 0, 0, 1, 0, "29266 71333"),
(145105, 0, 0, 0, 1, 0, "29266 71333"),
(145106, 0, 0, 0, 1, 0, "29266 71333"),
(145107, 0, 0, 0, 1, 0, "29266 71333"),
(145108, 0, 0, 0, 1, 0, "29266 71333"),
(145109, 0, 0, 0, 1, 0, "29266 71333"),
(145110, 0, 0, 0, 1, 0, "29266 71333"),
(145111, 0, 0, 0, 1, 0, "29266 71333"),
(145112, 0, 0, 0, 1, 0, "29266 71333"),
(145113, 0, 0, 0, 1, 0, "29266 71333"),
(145114, 0, 0, 0, 1, 0, "29266 71333"),
(145115, 0, 0, 0, 1, 0, "29266 71333"),
(145116, 0, 0, 0, 1, 0, "29266 71333"),
(145117, 0, 0, 0, 1, 0, "29266 71333");

UPDATE creature_template SET ScriptName="npc_slinky_sharpshiv_38517" WHERE entry=38517;

delete from creature_equip_template where entry=38745;
insert into creature_equip_template values 
(38745, 1, 1910, 0, 0),
(38745, 2, 50138, 0, 50150);

delete from creature where guid in (247544, 286084, 286085);

UPDATE creature SET modelid=0 WHERE id=38745;

DELETE FROM creature WHERE guid=247544;
INSERT INTO creature VALUES 
(247544, 38409, 648, 0, 0, 1, 0, 415, 0, 0, 1478.55, 2036.09, 231.499, 4.5657, 120, 0, 0, 0, 0, 0, 0, 0, 0);

delete from creature_equip_template where entry=38409;
insert into creature_equip_template values 
(38409, 1, 1910, 0, 0),
(38409, 2, 50138, 0, 50150);

DELETE FROM creature_addon WHERE guid=247544;
INSERT INTO creature_addon VALUES 
(247544, 0, 0, 0, 2, 214, "");

UPDATE creature SET equipment_id=2 WHERE guid in(285780, 247544);

delete from creature where id in (38813, 38815, 38816);

update creature set phaseId=182 where id=38753;

update creature set phaseId=0, phaseGroup=424 where id=38811;

update creature set SpawnDist=0, MovementType=0 where id=38819;

UPDATE creature_template SET InhabitType=4 WHERE entry=38819;

UPDATE creature_template_addon SET bytes1=33554432 WHERE entry=38819;

UPDATE creature SET position_x=1478.23, position_y=1737.71, position_z=288.43 WHERE guid=249635;

delete from creature_addon where guid in (49635,249635,249636,249637,249638,249639,249640,249641,249642,249643,249644,249645);
delete from creature_addon where guid in (249648,249649,249650,249651,249654,249655,249656,249657,249658,249659);

update gameobject set phaseId=182, SpawnTimeSecs=120 where id=202351;

UPDATE creature SET position_x=1462.151, position_y=1730.31, position_z=283.731, orientation=5.1971 WHERE guid=246751;

delete from creature where id=38812 and guid in (286097,286098,286099);

UPDATE creature SET position_z=295.02 WHERE guid=249638;
UPDATE creature SET position_z=299.972 WHERE guid=249642;
UPDATE creature SET position_z=302.657 WHERE guid=249644;
UPDATE creature SET position_z=306.194 WHERE guid=249650;
UPDATE creature SET position_z=305.859 WHERE guid=249659;

UPDATE creature SET position_x=1289.55, position_y=1527.2, position_z=342.509 WHERE guid=249649;
UPDATE creature SET position_z=322.828 WHERE guid=249651;
UPDATE creature SET position_z=333.707 WHERE guid=249655;
UPDATE creature SET position_z=324.121 WHERE guid=249656;
UPDATE creature SET position_z=323.54 WHERE guid=249658;
UPDATE creature SET position_x=1284.23, position_y=1474.299, position_z=328.87, orientation=.836 WHERE guid=249648;

UPDATE creature_template SET ScriptName="npc_gaahl_38808" WHERE entry=38808;

UPDATE creature_template SET ScriptName="npc_malmo_38809" WHERE entry=38809;

UPDATE creature_template SET ScriptName="npc_teloch_38810" WHERE entry=38810;

UPDATE creature_template SET ScriptName="npc_goblin_captive_38812" WHERE entry=38812;

UPDATE creature_template SET ScriptName="npc_goblin_zombie_38813" WHERE entry=38813;

UPDATE creature_template SET ScriptName="npc_goblin_captive_50310" WHERE entry=50310;

UPDATE creature_template SET ScriptName="npc_goblin_zombie_38815" WHERE entry=38815;

UPDATE creature_template SET ScriptName="npc_goblin_captive_50311" WHERE entry=50311;

UPDATE creature_template SET ScriptName="npc_goblin_zombie_38816" WHERE entry=38816;

update creature set spawndist=5, MovementType=1 where id=38753 and MovementType=0;

delete from creature where guid=282933;

DELETE FROM creature_addon WHERE guid=946;
INSERT INTO creature_addon VALUES 
(946, 0, 0, 0, 1, 0, "");

DELETE FROM gossip_menu_option WHERE menu_id=11082 AND id=0;
INSERT INTO gossip_menu_option VALUES 
(11082, 0, 0, "Greely, why do the Super Booster Rocket Boots only work on the zombies?", 38722, 1, 1, 0, 0, 0, 0, 0, "", 0);




