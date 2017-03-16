
UPDATE creature_addon SET path_id=341780 WHERE guid=34178;

UPDATE creature SET MovementType=2 WHERE guid=34178;

UPDATE creature_template_addon SET bytes2=1 WHERE entry=437;

UPDATE creature_addon SET auras="" WHERE guid in (33834, 33873, 34039, 34110, 34194, 34197, 34253, 34392, 34426);

update creature_loot_template set Reference=0, Chance=100, QuestRequired=1 where Entry=43350 and Item=58969;

UPDATE creature_template SET dmg_multiplier=1, Health_mod=1, Mana_mod=1 WHERE entry=43350;

UPDATE creature_template SET mindmg=23, maxdmg=31, attackpower=56, dmg_multiplier=1, minrangedmg=16, maxrangedmg=23, rangedattackpower=2, Health_mod=1, Mana_mod=1 WHERE entry=43363;

UPDATE creature SET MovementType=2 WHERE guid=44144;

DELETE FROM creature_addon WHERE guid=44144;
INSERT INTO creature_addon VALUES 
(44144, 441440, 0, 0, 1, 0, "");

DELETE FROM waypoint_data WHERE id=441440;
INSERT INTO waypoint_data VALUES 
(441440, 0, -8693.287, -2157.27, 157.1457, 1.322953, 3000, 0, 0, 100, 0),
(441440, 1, -8693.455, -2150.018, 158.4448, 2.658128, 0, 0, 0, 100, 0),
(441440, 2, -8693.489, -2155.854, 157.1779, 4.900435, 0, 0, 0, 100, 0),
(441440, 3, -8695.905, -2160.473, 157.4547, 4.342802, 0, 0, 0, 100, 0),
(441440, 4, -8692.878, -2172.135, 156.6601, 4.982896, 0, 0, 0, 100, 0),
(441440, 5, -8694.2, -2178.641, 156.8095, 4.448829, 0, 0, 0, 100, 0),
(441440, 6, -8703.129, -2199.329, 154.4686, 4.370286, 3000, 0, 0, 100, 0),
(441440, 7, -8694.2, -2178.641, 156.8095, 4.448829, 0, 0, 0, 100, 0),
(441440, 8, -8692.878, -2172.135, 156.6601, 4.982896, 0, 0, 0, 100, 0),
(441440, 9, -8695.905, -2160.473, 157.4547, 4.342802, 0, 0, 0, 100, 0),
(441440, 10, -8693.489, -2155.854, 157.1779, 4.900435, 0, 0, 0, 100, 0),
(441440, 11, -8693.455, -2150.018, 158.4448, 2.658128, 0, 0, 0, 100, 0);

UPDATE creature SET spawntimesecs=300 WHERE guid=9362;

UPDATE creature SET spawntimesecs=300 WHERE guid=33965;

UPDATE `creature_template` SET `ScriptName`="npc_wounded_infantry_42501" WHERE `entry`=42501;

UPDATE `creature_template` SET `npcflag`=0 WHERE `entry` IN(46268,46363);

DELETE FROM `creature_queststarter` WHERE id=46268 AND quest=27671;

UPDATE `npc_trainer` SET reqlevel=6,reqskill=355 WHERE spell=689;

UPDATE quest_template SET method=2, RequiredNpcOrGo1=42501 WHERE Id=26970;

UPDATE `creature` SET `spawndist`=0,MovementType=0 WHERE guid=62611 AND `id`=42505;

UPDATE `gameobject_template` SET `data0`=1691,`data8`=26222 WHERE entry IN(203443,203965,203966,203964,203968,203967);

UPDATE quest_template SET PrevQuestId=26545 WHERE Id=26567;

UPDATE quest_template SET Method=2, RequiredNpcOrGo1=27635, RequiredNpcOrGoCount1=1 WHERE Id=27635;

UPDATE locales_quest SET OfferRewardText_loc3="So, jetzt könnt Ihr Euch an die Oberfläche begeben und ein neues Leben beginnen. Der Hochtüftler wird begeistert sein, wenn er von Eurer Ankunft erfährt." WHERE Id=27635;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Ardo Schmutzpranke", QuestGiverTargetName_loc3="Ardo Schmutzpranke" WHERE Id=26519;

UPDATE creature_template SET ScriptName="npc_magistrate_solomon_344" WHERE entry=344;

update creature_template_outfits set shoulders=-53903 where entry=70901;

UPDATE locales_quest SET ObjectiveText1_loc3="Geht zum Friedhof von Seenhain" WHERE Id=26512;

delete from gameobject where id=2055 and guid=19017;

UPDATE creature SET spawndist=0, MovementType=2 WHERE guid=34539;

UPDATE creature SET position_x=-9117.48, position_y=-2211.68, position_z=125.285 WHERE guid=34244;

DELETE FROM waypoint_data WHERE id=34244;
INSERT INTO waypoint_data VALUES 
(34244, 0, -9117.094, -2211.103, 125.2806, 0.253745, 0, 0, 0, 100, 0),
(34244, 1, -9106.123, -2208.849, 126.3085, 0.202694, 0, 0, 0, 100, 0),
(34244, 2, -9085.322, -2194.623, 131.249, 0.532561, 0, 0, 0, 100, 0),
(34244, 3, -9059.701, -2193.454, 130.4698, 0.045614, 0, 0, 0, 100, 0),
(34244, 4, -9051.791, -2195.968, 130.5552, 5.975368, 0, 0, 0, 100, 0),
(34244, 5, -9023.119, -2208.293, 132.9035, 5.87719, 0, 0, 0, 100, 0),
(34244, 6, -9014.709, -2214.68, 132.8537, 5.633717, 0, 0, 0, 100, 0),
(34244, 7, -9004.522, -2222.057, 133.8349, 5.665132, 0, 0, 0, 100, 0),
(34244, 8, -8995.493, -2233.428, 139.13, 5.382391, 0, 0, 0, 100, 0),
(34244, 9, -8994.957, -2242.765, 141.9424, 4.789417, 0, 0, 0, 100, 0),
(34244, 10, -8994.417, -2245.503, 142.0109, 4.907225, 0, 0, 0, 100, 0),
(34244, 11, -8994.257, -2254.35, 138.7274, 4.730512, 0, 0, 0, 100, 0),
(34244, 12, -8982.431, -2268.805, 137.3204, 5.394172, 0, 0, 0, 100, 0),
(34244, 13, -8974.236, -2284.014, 134.2489, 5.205678, 0, 0, 0, 100, 0),
(34244, 14, -8969.245, -2292.415, 132.681, 5.248874, 0, 0, 0, 100, 0),
(34244, 15, -8960.762, -2320.945, 132.4767, 4.993622, 0, 0, 0, 100, 0),
(34244, 16, -8991.143, -2364.628, 132.4483, 4.204298, 0, 0, 0, 100, 0),
(34244, 17, -9002.297, -2381.546, 132.1408, 4.043296, 0, 0, 0, 100, 0),
(34244, 18, -9023.112, -2410.853, 130.2207, 4.106125, 0, 0, 0, 100, 0),
(34244, 19, -9034.467, -2426.284, 129.9576, 3.976541, 0, 0, 0, 100, 0),
(34244, 20, -9055.335, -2423.699, 128.1036, 3.018355, 0, 0, 0, 100, 0),
(34244, 21, -9088.328, -2382.383, 126.1278, 2.299715, 0, 0, 0, 100, 0),
(34244, 22, -9124.729, -2341.215, 119.8647, 2.342912, 0, 0, 0, 100, 0),
(34244, 23, -9142.119, -2306.655, 117.2156, 2.028753, 0, 0, 0, 100, 0),
(34244, 24, -9157.689, -2277.419, 113.6845, 2.048388, 0, 0, 0, 100, 0),
(34244, 25, -9153.777, -2263.482, 114.8529, 1.298332, 0, 0, 0, 100, 0),
(34244, 26, -9147.447, -2243.429, 119.2878, 1.262989, 0, 0, 0, 100, 0),
(34244, 27, -9140.319, -2225.623, 120.2103, 1.188376, 0, 0, 0, 100, 0);













