
-- console cleanup

delete from creature_addon where guid in (237815, 237816, 237817, 238154, 69019, 68981, 68790, 68609, 68479, 68270, 68205, 68084, 68007, 67830, 67828, 67775, 67747, 67683, 67569, 67566, 67422, 67324, 66896, 203544, 203545, 203546, 203547, 203548, 203549, 203550, 203552, 203556, 203557);

update creature_template set spell3=0 where entry=1540;
update creature_template set spell3=7164 where entry=3739;
update creature_template set spell3=0 where entry=18945;

delete from gameobject where guid = 8538;

delete from linked_respawn where guid=239623;

update quest_template set RequiredNpcOrGo2=0 where Id=26512;

delete from creature_queststarter where quest=24626 and id in (37989, 38002);

delete from npc_spellclick_spells where npc_entry=35999 and spell_id=46598;

delete from npc_spellclick_spells where spell_id in (47121, 47416, 46407, 71916, 71916, 71916, 71916);

DELETE FROM `creature_loot_template` WHERE (`entry`=46209);
INSERT INTO `creature_loot_template` VALUES 
(46209, 59469, 0, 1, 1, 1, 1),
(46209, 59470, 0, 1, 2, 1, 1),
(46209, 59471, 0, 1, 1, 1, 1),
(46209, 59472, 0, 1, 2, 1, 1),
(46209, 59473, 0, 1, 1, 1, 1),
(46209, 59474, 0, 1, 2, 1, 1),
(46209, 59475, 0, 1, 1, 1, 1),
(46209, 59476, 0, 1, 2, 1, 1),
(46209, 59481, 0, 1, 1, 1, 1),
(46209, 59482, 0, 1, 2, 1, 1),
(46209, 59483, 0, 1, 1, 1, 1),
(46209, 59484, 0, 1, 2, 1, 1);

DELETE FROM `creature_loot_template` WHERE (`entry`=49621);
INSERT INTO `creature_loot_template` VALUES 
(49621, 65110, 0, 1, 1, 1, 1),
(49621, 65111, 0, 1, 2, 1, 1),
(49621, 65113, 0, 1, 1, 1, 1),
(49621, 65114, 0, 1, 2, 1, 1),
(49621, 65115, 0, 1, 1, 1, 1),
(49621, 65116, 0, 1, 2, 1, 1),
(49621, 65117, 0, 1, 1, 1, 1),
(49621, 65118, 0, 1, 2, 1, 1),
(49621, 65119, 0, 1, 1, 1, 1),
(49621, 65120, 0, 1, 2, 1, 1),
(49621, 65121, 0, 1, 1, 1, 1),
(49621, 65122, 0, 1, 2, 1, 1);

DELETE FROM `creature_loot_template` WHERE (`entry`=49898);
INSERT INTO `creature_loot_template` VALUES 
(49898, 65094, 0, 1, 1, 1, 1),
(49898, 65095, 0, 1, 1, 1, 1),
(49898, 65096, 0, 1, 1, 1, 1),
(49898, 65106, 0, 1, 1, 1, 1),
(49898, 65107, 0, 1, 1, 1, 1),
(49898, 65109, 0, 1, 1, 1, 1);

DELETE FROM `creature_loot_template` WHERE (`entry`=49047);
INSERT INTO `creature_loot_template` VALUES 
(49047, 59216, 12.1, 1, 0, 1, 1),
(49047, 59217, 11.2, 1, 0, 1, 1),
(49047, 59218, 14.6, 1, 0, 1, 1),
(49047, 59219, 20.6, 1, 0, 1, 1),
(49047, 59220, 30.2, 1, 0, 1, 1),
(49047, 63540, 10.9, 1, 0, 1, 1);

DELETE FROM `creature_loot_template` WHERE (`entry`=49903);
INSERT INTO `creature_loot_template` VALUES 
(49903, 59512, 0, 1, 1, 1, 1),
(49903, 59516, 0, 1, 2, 1, 1),
(49903, 59519, 0, 1, 1, 1, 1),
(49903, 63534, 0, 1, 2, 1, 1),
(49903, 63535, 0, 1, 1, 1, 1),
(49903, 63536, 0, 1, 2, 1, 1);

DELETE FROM `creature_loot_template` WHERE (`entry`=46210);
INSERT INTO `creature_loot_template` VALUES 
(46210, 65133, 0, 1, 1, 1, 1),
(46210, 65134, 0, 1, 3, 1, 1),
(46210, 65135, 0, 1, 1, 1, 1),
(46210, 65136, 0, 1, 3, 1, 1),
(46210, 65137, 0, 1, 1, 1, 1),
(46210, 65138, 0, 1, 3, 1, 1),
(46210, 65139, 0, 1, 1, 1, 1),
(46210, 65140, 0, 1, 3, 1, 1),
(46210, 65141, 0, 1, 1, 1, 1),
(46210, 65142, 0, 1, 3, 1, 1),
(46210, 65143, 0, 1, 1, 1, 1),
(46210, 65144, 0, 1, 3, 1, 1),
(46210, 67423, 0, 1, 2, 1, 1),
(46210, 67424, 0, 1, 2, 1, 1),
(46210, 67425, 0, 1, 2, 1, 1);

DELETE FROM `creature_loot_template` WHERE (`entry`=49048);
INSERT INTO `creature_loot_template` VALUES 
(49048, 59216, 12.1, 1, 0, 1, 1),
(49048, 59217, 11.2, 1, 0, 1, 1),
(49048, 59218, 14.6, 1, 0, 1, 1),
(49048, 59219, 20.6, 1, 0, 1, 1),
(49048, 59220, 30.2, 1, 0, 1, 1),
(49048, 63540, 10.9, 1, 0, 1, 1);


DELETE FROM `creature_loot_template` WHERE (`entry`=49049);
INSERT INTO `creature_loot_template` VALUES 
(49049, 59216, 12.1, 1, 0, 1, 1),
(49049, 59217, 11.2, 1, 0, 1, 1),
(49049, 59218, 14.6, 1, 0, 1, 1),
(49049, 59219, 20.6, 1, 0, 1, 1),
(49049, 59220, 30.2, 1, 0, 1, 1),
(49049, 63540, 10.9, 1, 0, 1, 1);

DELETE FROM `creature_loot_template` WHERE (`entry`=49056);
INSERT INTO `creature_loot_template` VALUES 
(49056, 59117, 6, 1, 0, 1, 1),
(49056, 59118, 9, 1, 0, 1, 1),
(49056, 59119, 9, 1, 0, 1, 1),
(49056, 59120, 8, 1, 0, 1, 1),
(49056, 59121, 11, 1, 0, 1, 1),
(49056, 59122, 7, 1, 0, 1, 1),
(49056, 59216, 7, 1, 0, 1, 1),
(49056, 59217, 7, 1, 0, 1, 1),
(49056, 59218, 7, 1, 0, 1, 1),
(49056, 59219, 10, 1, 0, 1, 1),
(49056, 59220, 14, 1, 0, 1, 1),
(49056, 63540, 6, 1, 0, 1, 1);

DELETE FROM `creature_loot_template` WHERE (`entry`=49057);
INSERT INTO `creature_loot_template` VALUES 
(49057, 59117, 6, 1, 0, 1, 1),
(49057, 59118, 9, 1, 0, 1, 1),
(49057, 59119, 9, 1, 0, 1, 1),
(49057, 59120, 8, 1, 0, 1, 1),
(49057, 59121, 11, 1, 0, 1, 1),
(49057, 59122, 7, 1, 0, 1, 1),
(49057, 59216, 7, 1, 0, 1, 1),
(49057, 59217, 7, 1, 0, 1, 1),
(49057, 59218, 7, 1, 0, 1, 1),
(49057, 59219, 10, 1, 0, 1, 1),
(49057, 59220, 14, 1, 0, 1, 1),
(49057, 63540, 6, 1, 0, 1, 1);

DELETE FROM `creature_loot_template` WHERE (`entry`=49058);
INSERT INTO `creature_loot_template` VALUES 
(49058, 59117, 6, 1, 0, 1, 1),
(49058, 59118, 9, 1, 0, 1, 1),
(49058, 59119, 9, 1, 0, 1, 1),
(49058, 59120, 8, 1, 0, 1, 1),
(49058, 59121, 11, 1, 0, 1, 1),
(49058, 59122, 7, 1, 0, 1, 1),
(49058, 59216, 7, 1, 0, 1, 1),
(49058, 59217, 7, 1, 0, 1, 1),
(49058, 59218, 7, 1, 0, 1, 1),
(49058, 59219, 10, 1, 0, 1, 1),
(49058, 59220, 14, 1, 0, 1, 1),
(49058, 63540, 6, 1, 0, 1, 1);

DELETE FROM `creature_loot_template` WHERE (`entry`=49620);
INSERT INTO `creature_loot_template` VALUES 
(49620, 65110, 0, 1, 1, 1, 1),
(49620, 65111, 0, 1, 1, 1, 1),
(49620, 65113, 0, 1, 1, 1, 1),
(49620, 65114, 0, 1, 1, 1, 1),
(49620, 65115, 0, 1, 1, 1, 1),
(49620, 65116, 0, 1, 1, 1, 1),
(49620, 65117, 0, 1, 1, 1, 1),
(49620, 65118, 0, 1, 1, 1, 1),
(49620, 65119, 0, 1, 1, 1, 1),
(49620, 65120, 0, 1, 1, 1, 1),
(49620, 65121, 0, 1, 1, 1, 1),
(49620, 65122, 0, 1, 1, 1, 1);

DELETE FROM `creature_loot_template` WHERE (`entry`=49899);
INSERT INTO `creature_loot_template` VALUES 
(49899, 65094, 0, 1, 1, 1, 1),
(49899, 65095, 0, 1, 2, 1, 1),
(49899, 65096, 0, 1, 1, 1, 1),
(49899, 65106, 0, 1, 2, 1, 1),
(49899, 65107, 0, 1, 1, 1, 1),
(49899, 65109, 0, 1, 2, 1, 1);

DELETE FROM `creature_loot_template` WHERE (`entry`=49904);
INSERT INTO `creature_loot_template` VALUES 
(49904, 65091, 0, 1, 1, 1, 1),
(49904, 65092, 0, 1, 1, 1, 1),
(49904, 65093, 0, 1, 1, 1, 1),
(49904, 65105, 0, 1, 1, 1, 1),
(49904, 65108, 0, 1, 1, 1, 1),
(49904, 65112, 0, 1, 1, 1, 1);

DELETE FROM `creature_loot_template` WHERE (`entry`=49905);
INSERT INTO `creature_loot_template` VALUES 
(49905, 65091, 0, 1, 1, 1, 1),
(49905, 65092, 0, 1, 2, 1, 1),
(49905, 65093, 0, 1, 1, 1, 1),
(49905, 65105, 0, 1, 2, 1, 1),
(49905, 65108, 0, 1, 1, 1, 1),
(49905, 65112, 0, 1, 2, 1, 1);

DELETE FROM `creature_loot_template` WHERE (`entry`=50098);
INSERT INTO `creature_loot_template` VALUES 
(50098, 63488, 0, 1, 1, 1, 1),
(50098, 63489, 0, 1, 2, 1, 1),
(50098, 63490, 0, 1, 1, 1, 1),
(50098, 63491, 0, 1, 2, 1, 1),
(50098, 63492, 0, 1, 1, 1, 1),
(50098, 63493, 0, 1, 2, 1, 1),
(50098, 63494, 0, 1, 1, 1, 1),
(50098, 63495, 0, 1, 2, 1, 1),
(50098, 63496, 0, 1, 1, 1, 1),
(50098, 63497, 0, 1, 2, 1, 1),
(50098, 63498, 0, 1, 1, 1, 1);

DELETE FROM `creature_loot_template` WHERE (`entry`=50108);
INSERT INTO `creature_loot_template` VALUES 
(50108, 65367, 0, 1, 1, 1, 1),
(50108, 65368, 0, 1, 2, 1, 1),
(50108, 65369, 0, 1, 1, 1, 1),
(50108, 65370, 0, 1, 2, 1, 1),
(50108, 65371, 0, 1, 1, 1, 1),
(50108, 65372, 0, 1, 2, 1, 1),
(50108, 65373, 0, 1, 1, 1, 1),
(50108, 65374, 0, 1, 2, 1, 1),
(50108, 65375, 0, 1, 1, 1, 1),
(50108, 65376, 0, 1, 2, 1, 1),
(50108, 65377, 0, 1, 1, 1, 1);

DELETE FROM `creature_loot_template` WHERE (`entry`=50118);
INSERT INTO `creature_loot_template` VALUES 
(50118, 65367, 0, 1, 1, 1, 1),
(50118, 65368, 0, 1, 2, 1, 1),
(50118, 65369, 0, 1, 1, 1, 1),
(50118, 65370, 0, 1, 2, 1, 1),
(50118, 65371, 0, 1, 1, 1, 1),
(50118, 65372, 0, 1, 2, 1, 1),
(50118, 65373, 0, 1, 1, 1, 1),
(50118, 65374, 0, 1, 2, 1, 1),
(50118, 65375, 0, 1, 1, 1, 1),
(50118, 65376, 0, 1, 2, 1, 1),
(50118, 65377, 0, 1, 1, 1, 1);

DELETE FROM `creature_loot_template` WHERE (`entry`=57170);
INSERT INTO `creature_loot_template` VALUES 
(57170, 59502, 0, 1, 1, 1, 1),
(57170, 59503, 0, 1, 2, 1, 1),
(57170, 59504, 0, 1, 1, 1, 1),
(57170, 59505, 0, 1, 2, 1, 1),
(57170, 59506, 0, 1, 1, 1, 1),
(57170, 59507, 0, 1, 2, 1, 1),
(57170, 59508, 0, 1, 1, 1, 1),
(57170, 59509, 0, 1, 2, 1, 1),
(57170, 59510, 0, 1, 1, 1, 1),
(57170, 59511, 0, 1, 2, 1, 1),
(57170, 59513, 0, 1, 1, 1, 1),
(57170, 59514, 0, 1, 2, 1, 1);

DELETE FROM `creature_loot_template` WHERE (`entry`=57172);
INSERT INTO `creature_loot_template` VALUES 
(57172, 59502, 0, 1, 1, 1, 1),
(57172, 59503, 0, 1, 2, 1, 1),
(57172, 59504, 0, 1, 1, 1, 1),
(57172, 59505, 0, 1, 2, 1, 1),
(57172, 59506, 0, 1, 1, 1, 1),
(57172, 59507, 0, 1, 2, 1, 1),
(57172, 59508, 0, 1, 1, 1, 1),
(57172, 59509, 0, 1, 2, 1, 1),
(57172, 59510, 0, 1, 1, 1, 1),
(57172, 59511, 0, 1, 2, 1, 1),
(57172, 59513, 0, 1, 1, 1, 1),
(57172, 59514, 0, 1, 2, 1, 1);

update gameobject_template set data1=192057 where entry=192057;
update gameobject_template set data1=1594 where entry=1594;
update gameobject_template set data1=180662 where entry=180662;
update gameobject_template set data1=180664 where entry=180664;

DELETE FROM `gameobject_loot_template` WHERE (`entry`=195686);
INSERT INTO `gameobject_loot_template` VALUES 
(195686, 49162, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=207382);
INSERT INTO `gameobject_loot_template` VALUES 
(207382, 65507, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=195448);
INSERT INTO `gameobject_loot_template` VALUES 
(195448, 48128, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=195587);
INSERT INTO `gameobject_loot_template` VALUES 
(195587, 49082, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=206839);
INSERT INTO `gameobject_loot_template` VALUES 
(206839, 63107, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=205582);
INSERT INTO `gameobject_loot_template` VALUES 
(205582, 61376, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=195447);
INSERT INTO `gameobject_loot_template` VALUES 
(195447, 48128, -100, 1, 0, 1, 5);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=106319);
INSERT INTO `gameobject_loot_template` VALUES 
(106319, 117, 9.57941, 1, 0, 1, 1),
(106319, 118, 33.6511, 1, 0, 1, 1),
(106319, 159, 21.514, 1, 0, 1, 1),
(106319, 414, 8.07959, 1, 0, 1, 1),
(106319, 727, 0.6, 1, 0, -727, 1),
(106319, 766, 1.5, 1, 0, -766, 1),
(106319, 767, 0.4, 1, 0, -767, 1),
(106319, 768, 0.4, 1, 0, -768, 1),
(106319, 774, 2.39252, 1, 0, 1, 1),
(106319, 783, 1.42422, 1, 0, 1, 1),
(106319, 818, 1, 1, 0, -818, 1),
(106319, 858, 11.6597, 1, 0, 1, 1),
(106319, 1179, 18.7874, 1, 0, 1, 1),
(106319, 1364, 30, 1, 0, -1364, 1),
(106319, 1421, 20, 1, 0, -1421, 1),
(106319, 1498, 15, 1, 0, -1498, 1),
(106319, 1705, 0.030799, 1, 0, 1, 1),
(106319, 1739, 10, 1, 0, -1739, 1),
(106319, 2070, 9.59807, 1, 0, 1, 1),
(106319, 2073, 0.91, 1, 0, -2073, 1),
(106319, 2075, 0.47, 1, 0, -2075, 1),
(106319, 2078, 0.45, 1, 0, -2078, 1),
(106319, 2079, 0.51, 1, 0, -2079, 1),
(106319, 2140, 0.4, 1, 0, -2140, 1),
(106319, 2287, 8.26532, 1, 0, 1, 1),
(106319, 2318, 15.9198, 1, 0, 1, 1),
(106319, 2406, 2.0467, 1, 0, -2406, 1),
(106319, 2409, 0.4452, 1, 0, -2409, 1),
(106319, 2455, 11.8711, 1, 0, 1, 1),
(106319, 2589, 12.0419, 1, 0, 1, 1),
(106319, 2592, 0.651911, 1, 0, 1, 1),
(106319, 2601, 0.0443, 1, 0, -2601, 1),
(106319, 2632, 0.39, 1, 0, -2632, 1),
(106319, 2835, 7.65867, 1, 0, 1, 1),
(106319, 2836, 0.792373, 1, 0, 1, 1),
(106319, 2842, 7.15562, 1, 0, 1, 1),
(106319, 2970, 0.48, 1, 0, -2970, 1),
(106319, 2971, 0.5, 1, 0, -2971, 1),
(106319, 2981, 0.02, 1, 0, -2981, 1),
(106319, 2982, 0.46, 1, 0, -2982, 1),
(106319, 2988, 0.45, 1, 0, -2988, 1),
(106319, 2996, 4.0622, 1, 0, 1, 1),
(106319, 3200, 1.2, 1, 0, -3200, 1),
(106319, 3213, 0.5, 1, 0, -3213, 1),
(106319, 3283, 0.43, 1, 0, -3283, 1),
(106319, 3304, 0.5, 1, 0, -3304, 1),
(106319, 3312, 0.5, 1, 0, -3312, 1),
(106319, 3393, 0.00326656, 1, 0, 1, 1),
(106319, 3394, 0.00326656, 1, 0, 1, 1),
(106319, 3396, 0.0009, 1, 0, -3396, 1),
(106319, 3577, 0.872637, 1, 0, 1, 1),
(106319, 4536, 9.33535, 1, 0, 1, 1),
(106319, 4537, 7.7478, 1, 0, 1, 1),
(106319, 4540, 8.9653, 1, 0, 1, 1),
(106319, 4541, 7.58261, 1, 0, 1, 1),
(106319, 4565, 1.5, 1, 0, -4565, 1),
(106319, 4604, 7.50234, 1, 0, 1, 1),
(106319, 4605, 7.99886, 1, 0, 1, 1),
(106319, 4663, 1.3, 1, 0, -4663, 1),
(106319, 4677, 0.7, 1, 0, -4677, 1),
(106319, 4694, 0.3, 1, 0, -4694, 1),
(106319, 4698, 0.3, 1, 0, -4698, 1),
(106319, 5498, 2, 1, 0, 1, 1),
(106319, 5500, 1, 1, 0, 1, 1),
(106319, 5571, 0.5, 1, 0, -5571, 1),
(106319, 5574, 0.5, 1, 0, -5574, 1),
(106319, 6506, 0.5, 1, 0, -6506, 1),
(106319, 6514, 0.8, 1, 0, -6514, 1),
(106319, 14169, 0.2, 1, 0, -14169, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=201706);
INSERT INTO `gameobject_loot_template` VALUES 
(201706, 49754, -56.3978, 1, 0, 1, 1),
(201706, 62327, -43.6022, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=202739);
INSERT INTO `gameobject_loot_template` VALUES 
(202739, 52177, 0.7253, 1, 0, 1, 1),
(202739, 52178, 0.7131, 1, 0, 1, 1),
(202739, 52179, 0.9171, 1, 0, 1, 1),
(202739, 52180, 0.8683, 1, 0, 1, 1),
(202739, 52181, 0.8526, 1, 0, 1, 1),
(202739, 52182, 0.7236, 1, 0, 1, 1),
(202739, 52327, 19.5606, 1, 0, 1, 4),
(202739, 52328, 2.3468, 1, 0, 1, 2),
(202739, 53038, 100, 1, 0, 2, 10);

update gameobject_template set data1=184956 where entry=184956;

DELETE FROM `gameobject_loot_template` WHERE (`entry`=204378);
INSERT INTO `gameobject_loot_template` VALUES 
(204378, 58944, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=203182);
INSERT INTO `gameobject_loot_template` VALUES 
(203182, 55233, -100, 1, 0, 1, 1);

update gameobject_template set data1=180184 where entry=180184;
update gameobject_template set data1=180369 where entry=180369;
update gameobject_template set data1=180582 where entry=180582;
update gameobject_template set data1=180655 where entry=180655;
update gameobject_template set data1=180656 where entry=180656;
update gameobject_template set data1=180657 where entry=180657;
update gameobject_template set data1=180658 where entry=180658;
update gameobject_template set data1=180663 where entry=180663;
update gameobject_template set data1=180682 where entry=180682;
update gameobject_template set data1=180683 where entry=180683;
update gameobject_template set data1=180684 where entry=180684;
update gameobject_template set data1=180685 where entry=180685;
update gameobject_template set data1=180712 where entry=180712;
update gameobject_template set data1=180750 where entry=180750;
update gameobject_template set data1=180751 where entry=180751;
update gameobject_template set data1=180752 where entry=180752;
update gameobject_template set data1=180900 where entry=180900;
update gameobject_template set data1=180901 where entry=180901;
update gameobject_template set data1=180902 where entry=180902;

DELETE FROM `gameobject_loot_template` WHERE (`entry`=181239);
INSERT INTO `gameobject_loot_template` VALUES 
(181239, 22599, -100, 1, 0, 1, 1);

update gameobject_template set data1=208630 where entry=208630;

DELETE FROM `gameobject_loot_template` WHERE (`entry`=205195);
INSERT INTO `gameobject_loot_template` VALUES 
(205195, 60791, -100, 1, 0, 1, 1);

update gameobject_template set data1=192048 where entry=192048;

DELETE FROM `gameobject_loot_template` WHERE (`entry`=204410);
INSERT INTO `gameobject_loot_template` VALUES 
(204410, 59123, -100, 1, 0, 1, 1);

update gameobject_template set data1=192049 where entry=192049;

DELETE FROM `gameobject_loot_template` WHERE (`entry`=203130);
INSERT INTO `gameobject_loot_template` VALUES 
(203130, 55151, -100, 1, 0, 1, 1);

update gameobject_template set data1=180661 where entry=180661;
update gameobject_template set data1=180753 where entry=180753;

DELETE FROM `gameobject_loot_template` WHERE (`entry`=113768);
INSERT INTO `gameobject_loot_template` VALUES 
(113768, 45072, 100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=208802);
INSERT INTO `gameobject_loot_template` VALUES 
(208802, 69860, -100, 1, 0, 1, 1);

update gameobject_template set data1=205827 where entry=205827;
update gameobject_template set data1=192052 where entry=192052;
update gameobject_template set data1=402191 where entry=402191;
update gameobject_template set data1=192046 where entry=192046;
update gameobject_template set data1=192051 where entry=192051;

DELETE FROM `gameobject_loot_template` WHERE (`entry`=191533);
INSERT INTO `gameobject_loot_template` VALUES 
(191533, 40603, -100, 1, 0, 1, 1);

update gameobject_template set data1=192050 where entry=192050;
update gameobject_template set data1=192059 where entry=192059;

DELETE FROM `gameobject_loot_template` WHERE (`entry`=208576);
INSERT INTO `gameobject_loot_template` VALUES 
(208576, 69807, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=190542);
INSERT INTO `gameobject_loot_template` VALUES 
(190542, 38563, -100, 1, 0, 1, 3);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=190543);
INSERT INTO `gameobject_loot_template` VALUES 
(190543, 38563, -100, 1, 0, 1, 3);

update gameobject_template set data1=192053 where entry=192053;
update gameobject_template set data1=192054 where entry=192054;
update gameobject_template set data1=206786 where entry=206786;

DELETE FROM `gameobject_loot_template` WHERE (`entry`=203751);
INSERT INTO `gameobject_loot_template` VALUES 
(203751, 57137, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=205060);
INSERT INTO `gameobject_loot_template` VALUES 
(205060, 60679, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=205884);
INSERT INTO `gameobject_loot_template` VALUES 
(205884, 61044, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=206586);
INSERT INTO `gameobject_loot_template` VALUES 
(206586, 62818, -100, 1, 0, 1, 1);

update gameobject_template set data1=205828 where entry=205828;

DELETE FROM `gameobject_loot_template` WHERE (`entry`=205208);
INSERT INTO `gameobject_loot_template` VALUES 
(205208, 58944, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=201979);
INSERT INTO `gameobject_loot_template` VALUES 
(201979, 50237, -100, 1, 0, 1, 1);

update gameobject_template set data1=194479 where entry=194479;
update gameobject_template set data1=402365 where entry=402365;

DELETE FROM `gameobject_loot_template` WHERE (`entry`=196835);
INSERT INTO `gameobject_loot_template` VALUES 
(196835, 49367, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=202240);
INSERT INTO `gameobject_loot_template` VALUES 
(202240, 49908, 10, 1, 0, 1, 1),
(202240, 50014, 0, 1, 1, 1, 1),
(202240, 50015, 0, 1, 1, 1, 1),
(202240, 50274, -37.5, 1, 0, 1, 1),
(202240, 50333, 0, 1, 1, 1, 1),
(202240, 50362, 0, 1, 1, 1, 1),
(202240, 50412, 0, 1, 1, 1, 1),
(202240, 52025, 100, 1, 0, 1, 2);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=204376);
INSERT INTO `gameobject_loot_template` VALUES 
(204376, 58944, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=204296);
INSERT INTO `gameobject_loot_template` VALUES 
(204296, 58845, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=205097);
INSERT INTO `gameobject_loot_template` VALUES 
(205097, 60739, -100, 1, 0, 1, 1);

update gameobject_template set data1=202778 where entry=202778;

DELETE FROM `gameobject_loot_template` WHERE (`entry`=204253);
INSERT INTO `gameobject_loot_template` VALUES 
(204253, 58500, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=203967);
INSERT INTO `gameobject_loot_template` VALUES 
(203967, 57764, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=194204);
INSERT INTO `gameobject_loot_template` VALUES 
(194204, 44968, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=195206);
INSERT INTO `gameobject_loot_template` VALUES 
(195206, 46833, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=195584);
INSERT INTO `gameobject_loot_template` VALUES 
(195584, 49012, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=196834);
INSERT INTO `gameobject_loot_template` VALUES 
(196834, 49365, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=203179);
INSERT INTO `gameobject_loot_template` VALUES 
(203179, 55231, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=203224);
INSERT INTO `gameobject_loot_template` VALUES 
(203224, 55989, -100, 1, 0, 1, 1);

update gameobject_template set data1=202776 where entry=202776;
update gameobject_template set data1=402189 where entry=402189;
update gameobject_template set data1=402190 where entry=402190;
update gameobject_template set data1=402364 where entry=402364;
update gameobject_template set data1=402366 where entry=402366;

DELETE FROM `gameobject_loot_template` WHERE (`entry`=203373);
INSERT INTO `gameobject_loot_template` VALUES 
(203373, 56185, -100, 1, 0, 1, 1);

update gameobject_template set data1=207724 where entry=207724;
update gameobject_template set data1=207734 where entry=207734;

DELETE FROM `gameobject_loot_template` WHERE (`entry`=205534);
INSERT INTO `gameobject_loot_template` VALUES 
(205534, 61306, -100, 1, 0, 1, 1);

update gameobject_template set data1=202781 where entry=202781;

DELETE FROM `gameobject_loot_template` WHERE (`entry`=206203);
INSERT INTO `gameobject_loot_template` VALUES 
(206203, 62317, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=206387);
INSERT INTO `gameobject_loot_template` VALUES 
(206387, 62508, 100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=205538);
INSERT INTO `gameobject_loot_template` VALUES 
(205538, 61319, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=206199);
INSERT INTO `gameobject_loot_template` VALUES 
(206199, 62327, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=207389);
INSERT INTO `gameobject_loot_template` VALUES 
(207389, 65615, -100, 1, 0, 1, 1);

update gameobject_template set data1=205826 where entry=205826;

DELETE FROM `gameobject_loot_template` WHERE (`entry`=202751);
INSERT INTO `gameobject_loot_template` VALUES 
(202751, 52329, 38, 1, 0, 1, 3),
(202751, 52987, 100, 1, 0, 2, 8),
(202751, 63122, 10, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=207294);
INSERT INTO `gameobject_loot_template` VALUES 
(207294, 64667, -100, 1, 0, 1, 1);

update creature_loot_template set ChanceOrQuestChance=0 where entry=48715;
update creature_loot_template set ChanceOrQuestChance=0 where entry=39378;
update creature_loot_template set ChanceOrQuestChance=0 where entry=48714;

update fishing_loot_template set ChanceOrQuestChance=-100, mincountOrRef=1 where entry=1;
delete from fishing_loot_template where entry=1657 and item=11002;
delete from fishing_loot_template where entry=1638 and item=11002;
delete from fishing_loot_template where entry=1537 and item=11002;

update gameobject_loot_template set ChanceOrQuestChance=0 where entry in (208044,208045);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=192057);
INSERT INTO `gameobject_loot_template` VALUES 
(192057, 37705, 5, 1, 1, 1, 1),
(192057, 40199, 65, 1, 0, 1, 1),
(192057, 41813, 0, 1, 1, 1, 1),
(192057, 44475, 5, 1, 1, 1, 1),
(192057, 44505, 0.1, 1, 1, 1, 1),
(192057, 45902, -25, 1, 0, 1, 1),
(192057, 46109, 0.1, 1, 1, 1, 1),
(192057, 50289, 0.2, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=1594);
INSERT INTO `gameobject_loot_template` VALUES 
(1594, 3255, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=180662);
INSERT INTO `gameobject_loot_template` VALUES 
(180662, 3820, 20, 1, 1, 1, 3),
(180662, 21114, 20, 1, 1, 1, 3),
(180662, 21228, 0, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=180664);
INSERT INTO `gameobject_loot_template` VALUES 
(180664, 3820, 5, 1, 1, 1, 3),
(180664, 6358, 0, 1, 1, 1, 1),
(180664, 21114, 5, 1, 1, 1, 3),
(180664, 21228, 5, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=184956);
INSERT INTO `gameobject_loot_template` VALUES 
(184956, 3820, 5, 1, 1, 1, 3),
(184956, 21114, 5, 1, 1, 1, 3),
(184956, 21150, 5, 1, 1, 1, 1),
(184956, 21153, 0, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=180184);
INSERT INTO `gameobject_loot_template` VALUES 
(180184, 2447, 100, 1, 0, 1, 4);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=180369);
INSERT INTO `gameobject_loot_template` VALUES 
(180369, 19975, 100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=180582);
INSERT INTO `gameobject_loot_template` VALUES 
(180582, 3820, 5, 1, 1, 1, 3),
(180582, 6358, 0, 1, 1, 1, 1),
(180582, 20708, 5, 1, 1, 1, 1),
(180582, 21114, 5, 1, 1, 1, 3);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=180655);
INSERT INTO `gameobject_loot_template` VALUES 
(180655, 3820, 20, 1, 1, 1, 3),
(180655, 20708, 0, 1, 1, 1, 1),
(180655, 20709, 20, 1, 1, 1, 3);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=180656);
INSERT INTO `gameobject_loot_template` VALUES 
(180656, 3820, 5, 1, 1, 1, 3),
(180656, 20708, 5, 1, 1, 1, 1),
(180656, 21071, 0, 1, 1, 1, 1),
(180656, 21114, 5, 1, 1, 1, 3);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=180657);
INSERT INTO `gameobject_loot_template` VALUES 
(180657, 3820, 5, 1, 1, 1, 3),
(180657, 6359, 0, 1, 1, 1, 1),
(180657, 21113, 5, 1, 1, 1, 1),
(180657, 21114, 5, 1, 1, 1, 3);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=180658);
INSERT INTO `gameobject_loot_template` VALUES 
(180658, 3820, 5, 1, 1, 1, 3),
(180658, 6522, 0, 1, 1, 1, 1),
(180658, 20708, 5, 1, 1, 1, 1),
(180658, 21114, 5, 1, 1, 1, 3);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=180663);
INSERT INTO `gameobject_loot_template` VALUES 
(180663, 3820, 5, 1, 1, 1, 3),
(180663, 21071, 0, 1, 1, 1, 1),
(180663, 21113, 5, 1, 1, 1, 1),
(180663, 21114, 5, 1, 1, 1, 3);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=180682);
INSERT INTO `gameobject_loot_template` VALUES 
(180682, 3820, 5, 1, 1, 1, 3),
(180682, 6358, 0, 1, 1, 1, 1),
(180682, 21114, 5, 1, 1, 1, 3),
(180682, 21150, 5, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=180683);
INSERT INTO `gameobject_loot_template` VALUES 
(180683, 3820, 5, 1, 1, 1, 3),
(180683, 6359, 0, 1, 1, 1, 1),
(180683, 21114, 5, 1, 1, 1, 3),
(180683, 21150, 5, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=180684);
INSERT INTO `gameobject_loot_template` VALUES 
(180684, 3820, 5, 1, 1, 1, 3),
(180684, 21114, 5, 1, 1, 1, 3),
(180684, 21150, 5, 1, 1, 1, 1),
(180684, 21153, 0, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=180685);
INSERT INTO `gameobject_loot_template` VALUES 
(180685, 3820, 20, 1, 1, 1, 3),
(180685, 21113, 0, 1, 1, 1, 1),
(180685, 21114, 20, 1, 1, 1, 3);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=180712);
INSERT INTO `gameobject_loot_template` VALUES 
(180712, 3820, 5, 1, 1, 1, 3),
(180712, 13422, 0, 1, 1, 1, 1),
(180712, 21114, 5, 1, 1, 1, 3),
(180712, 21228, 5, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=180750);
INSERT INTO `gameobject_loot_template` VALUES 
(180750, 3820, 5, 1, 1, 1, 3),
(180750, 6358, 0, 1, 1, 1, 1),
(180750, 21114, 5, 1, 1, 1, 3),
(180750, 21228, 5, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=180751);
INSERT INTO `gameobject_loot_template` VALUES 
(180751, 3820, 20, 1, 1, 1, 3),
(180751, 21114, 20, 1, 1, 1, 3),
(180751, 21228, 60, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=180752);
INSERT INTO `gameobject_loot_template` VALUES 
(180752, 3820, 5, 1, 1, 1, 3),
(180752, 6359, 0, 1, 1, 1, 1),
(180752, 21114, 5, 1, 1, 1, 3),
(180752, 21228, 5, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=180900);
INSERT INTO `gameobject_loot_template` VALUES 
(180900, 3820, 5, 1, 1, 1, 3),
(180900, 6358, 0, 1, 1, 1, 1),
(180900, 21114, 5, 1, 1, 1, 3),
(180900, 21228, 5, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=180901);
INSERT INTO `gameobject_loot_template` VALUES 
(180901, 3820, 20, 1, 1, 1, 3),
(180901, 21151, 20, 1, 1, 1, 3),
(180901, 21228, 0, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=180902);
INSERT INTO `gameobject_loot_template` VALUES 
(180902, 3820, 5, 1, 1, 1, 3),
(180902, 6359, 0, 1, 1, 1, 1),
(180902, 21114, 5, 1, 1, 1, 3),
(180902, 21228, 5, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=208630);
INSERT INTO `gameobject_loot_template` VALUES 
(208630, 69836, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=192048);
INSERT INTO `gameobject_loot_template` VALUES 
(192048, 37705, 5, 1, 1, 1, 1),
(192048, 40199, 65, 1, 0, 1, 1),
(192048, 41807, 0, 1, 1, 1, 1),
(192048, 44475, 5, 1, 1, 1, 1),
(192048, 44505, 0.1, 1, 1, 1, 1),
(192048, 46109, 0.1, 1, 1, 1, 1),
(192048, 50289, 0.2, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=192049);
INSERT INTO `gameobject_loot_template` VALUES 
(192049, 37705, 5, 1, 1, 1, 1),
(192049, 40199, 65, 1, 0, 1, 1),
(192049, 41810, 0, 1, 1, 1, 1),
(192049, 44475, 5, 1, 1, 1, 1),
(192049, 44505, 0.1, 1, 1, 1, 1),
(192049, 44703, 0.1, 1, 1, 1, 1),
(192049, 46109, 0.1, 1, 1, 1, 1),
(192049, 50289, 0.2, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=180661);
INSERT INTO `gameobject_loot_template` VALUES 
(180661, 3820, 5, 1, 1, 1, 3),
(180661, 6359, 0, 1, 1, 1, 1),
(180661, 21113, 5, 1, 1, 1, 1),
(180661, 21114, 5, 1, 1, 1, 3);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=180753);
INSERT INTO `gameobject_loot_template` VALUES 
(180753, 7070, 0, 1, 1, 1, 3),
(180753, 7079, 30, 1, 1, 1, 2),
(180753, 7080, 30, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=205827);
INSERT INTO `gameobject_loot_template` VALUES 
(205827, 61922, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=192052);
INSERT INTO `gameobject_loot_template` VALUES 
(192052, 37705, 5, 1, 1, 1, 1),
(192052, 40199, 65, 1, 0, 1, 1),
(192052, 41802, 0, 1, 1, 1, 1),
(192052, 44475, 5, 1, 1, 1, 1),
(192052, 44505, 0.1, 1, 1, 1, 1),
(192052, 46109, 0.1, 1, 1, 1, 1),
(192052, 50289, 0.2, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=192046);
INSERT INTO `gameobject_loot_template` VALUES 
(192046, 37705, 5, 1, 1, 1, 1),
(192046, 40199, 65, 1, 0, 1, 1),
(192046, 41806, 0, 1, 1, 1, 1),
(192046, 44475, 5, 1, 1, 1, 1),
(192046, 44505, 0.1, 1, 1, 1, 1),
(192046, 46109, 0.1, 1, 1, 1, 1),
(192046, 50289, 0.2, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=192051);
INSERT INTO `gameobject_loot_template` VALUES 
(192051, 37705, 5, 1, 1, 1, 1),
(192051, 40199, 65, 1, 0, 1, 1),
(192051, 41805, 0, 1, 1, 1, 1),
(192051, 44475, 5, 1, 1, 1, 1),
(192051, 44505, 0.1, 1, 1, 1, 1),
(192051, 46109, 0.1, 1, 1, 1, 1),
(192051, 50289, 0.2, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=192050);
INSERT INTO `gameobject_loot_template` VALUES 
(192050, 37705, 5, 1, 1, 1, 1),
(192050, 40199, 65, 1, 0, 1, 1),
(192050, 41809, 0, 1, 1, 1, 1),
(192050, 44475, 5, 1, 1, 1, 1),
(192050, 44505, 0.1, 1, 1, 1, 1),
(192050, 46109, 0.1, 1, 1, 1, 1),
(192050, 50289, 0.2, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=192059);
INSERT INTO `gameobject_loot_template` VALUES 
(192059, 37705, 5, 1, 1, 1, 1),
(192059, 40199, 5, 1, 0, 1, 1),
(192059, 41814, 0, 1, 1, 1, 1),
(192059, 44475, 5, 1, 1, 1, 1),
(192059, 44505, 0.1, 1, 1, 1, 1),
(192059, 46109, 0.1, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=192053);
INSERT INTO `gameobject_loot_template` VALUES 
(192053, 37705, 5, 1, 1, 1, 1),
(192053, 40199, 65, 1, 0, 1, 1),
(192053, 41800, 0, 1, 1, 1, 1),
(192053, 44475, 5, 1, 1, 1, 1),
(192053, 44505, 0.1, 1, 1, 1, 1),
(192053, 46109, 0.1, 1, 1, 1, 1),
(192053, 50289, 0.2, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=192054);
INSERT INTO `gameobject_loot_template` VALUES 
(192054, 37705, 5, 1, 1, 1, 1),
(192054, 40199, 65, 1, 0, 1, 1),
(192054, 41801, 0, 1, 1, 1, 1),
(192054, 44475, 5, 1, 1, 1, 1),
(192054, 44505, 0.1, 1, 1, 1, 1),
(192054, 46109, 0.1, 1, 1, 1, 1),
(192054, 50289, 0.2, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=206786);
INSERT INTO `gameobject_loot_template` VALUES 
(206786, 63085, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=206786);
INSERT INTO `gameobject_loot_template` VALUES 
(206786, 63085, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=194479);
INSERT INTO `gameobject_loot_template` VALUES 
(194479, 45905, -25, 1, 0, 1, 3),
(194479, 45907, 0, 1, 1, 1, 1),
(194479, 46109, 0.1, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=202778);
INSERT INTO `gameobject_loot_template` VALUES 
(202778, 22739, 0.1, 1, 1, 1, 1),
(202778, 46109, 0.1, 1, 1, 1, 1),
(202778, 52326, 10, 1, 1, 1, 3),
(202778, 53065, 0, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=202776);
INSERT INTO `gameobject_loot_template` VALUES 
(202776, 22739, 0.1, 1, 1, 1, 1),
(202776, 46109, 0.1, 1, 1, 1, 1),
(202776, 52326, 10, 1, 1, 1, 3),
(202776, 53063, 0, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=207724);
INSERT INTO `gameobject_loot_template` VALUES 
(207724, 22739, 0.1, 1, 1, 1, 1),
(207724, 46109, 0.1, 1, 1, 1, 1),
(207724, 52326, 25, 1, 1, 1, 2),
(207724, 52985, 15, 1, 1, 1, 2),
(207724, 67597, 0, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=207734);
INSERT INTO `gameobject_loot_template` VALUES 
(207734, 52325, 0, 1, 1, 1, 2);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=202781);
INSERT INTO `gameobject_loot_template` VALUES 
(202781, 22739, 0.1, 1, 1, 1, 1),
(202781, 46109, 0.1, 1, 1, 1, 1),
(202781, 52326, 10, 1, 1, 1, 3),
(202781, 53071, 0, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE (`entry`=205826);
INSERT INTO `gameobject_loot_template` VALUES 
(205826, 61921, -100, 1, 0, 1, 1);

delete from gameobject_template where entry in (402191, 402365, 3000005, 402189, 402190, 402364, 402366, 2404120);

delete from spell_linked_spell where spell_trigger in (37639, 54646, 58586);

delete from guild_xp_for_level where lvl between 1 and 25;
INSERT INTO `guild_xp_for_level` VALUES ('1', '16580000');
INSERT INTO `guild_xp_for_level` VALUES ('2', '18240000');
INSERT INTO `guild_xp_for_level` VALUES ('3', '19900000');
INSERT INTO `guild_xp_for_level` VALUES ('4', '21550000');
INSERT INTO `guild_xp_for_level` VALUES ('5', '23220000');
INSERT INTO `guild_xp_for_level` VALUES ('6', '24880000');
INSERT INTO `guild_xp_for_level` VALUES ('7', '26530000');
INSERT INTO `guild_xp_for_level` VALUES ('8', '28190000');
INSERT INTO `guild_xp_for_level` VALUES ('9', '29850000');
INSERT INTO `guild_xp_for_level` VALUES ('10', '31510000');
INSERT INTO `guild_xp_for_level` VALUES ('11', '33170000');
INSERT INTO `guild_xp_for_level` VALUES ('12', '34820000');
INSERT INTO `guild_xp_for_level` VALUES ('13', '36490000');
INSERT INTO `guild_xp_for_level` VALUES ('14', '38140000');
INSERT INTO `guild_xp_for_level` VALUES ('15', '39800000');
INSERT INTO `guild_xp_for_level` VALUES ('16', '41450000');
INSERT INTO `guild_xp_for_level` VALUES ('17', '43120000');
INSERT INTO `guild_xp_for_level` VALUES ('18', '44780000');
INSERT INTO `guild_xp_for_level` VALUES ('19', '46430000');
INSERT INTO `guild_xp_for_level` VALUES ('20', '48090000');
INSERT INTO `guild_xp_for_level` VALUES ('21', '49750000');
INSERT INTO `guild_xp_for_level` VALUES ('22', '51410000');
INSERT INTO `guild_xp_for_level` VALUES ('23', '53060000');
INSERT INTO `guild_xp_for_level` VALUES ('24', '54730000');
INSERT INTO `guild_xp_for_level` VALUES ('25', '56390000');


delete from battlemaster_entry where entry=40413 and bg_template=32;
insert into battlemaster_entry values(40413, 32);

delete from battlemaster_entry where entry=49573 and bg_template=32;
insert into battlemaster_entry values(49573, 32);

delete from conditions where SourceEntry=41818;
insert into conditions values
(1, 28379, 41818, 0, 0, 7, 0, 755, 1, 0, 0, 0, 0, "", ""),
(1, 29402, 41818, 0, 0, 7, 0, 755, 1, 0, 0, 0, 0, "", ""),
(1, 30448, 41818, 0, 0, 7, 0, 755, 1, 0, 0, 0, 0, "", "");

delete from conditions where SourceEntry=41820;
insert into conditions values
(1, 29370, 41820, 0, 0, 7, 0, 755, 1, 0, 0, 0, 0, "", ""),
(1, 29376, 41820, 0, 0, 7, 0, 755, 1, 0, 0, 0, 0, "", "");




