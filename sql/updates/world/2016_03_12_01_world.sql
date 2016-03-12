-- updates for quest 29539 and 29536
-- consol error correction for SAI.
update `smart_scripts` set action_type=11,action_param1=76496,action_param2=3,action_param3=0 WHERE `entryorguid`=39239 and id=1;

-- areatrigger_involved_relation, supports A and H quests ID's  29539,29536 Heart of Rage.
DELETE FROM `areatrigger_involvedrelation` where `id` in (4200,4201);
INSERT INTO `areatrigger_involvedrelation` (`id`,`quest`) VALUES (4200,29539);
INSERT INTO `areatrigger_involvedrelation` (`id`,`quest`) VALUES (4201,29536);
update `quest_template` set `SpecialFlags`=2 where `id` in (29539,29536);

-- depreciated quest entry.
DELETE FROM  `smart_scripts` WHERE `entryorguid`=9937 AND source_type=0;
DELETE FROM  `gossip_menu_option` WHERE `menu_id`=55002;
update `creature_template` set `npcflag`=0,`gossip_menu_id`=0 WHERE `entry`=9937;

-- wrong quest starter .
DELETE FROM `creature_queststarter` where `id`=47927;

DELETE FROM `creature_queststarter` where `id`=47972;
INSERT INTO `creature_queststarter` (`id`,`quest`) VALUES (47972,28193);
INSERT INTO `creature_queststarter` (`id`,`quest`) VALUES (47972,28195);
INSERT INTO `creature_queststarter` (`id`,`quest`) VALUES (47972,28267);
DELETE FROM `creature_questender` where `id`=47972;
INSERT INTO `creature_questender` (`id`,`quest`) VALUES (47972,28187);
INSERT INTO `creature_questender` (`id`,`quest`) VALUES (47972,28193);
INSERT INTO `creature_questender` (`id`,`quest`) VALUES (47972,28195);

update `creature_template` set `npcflag`=3 WHERE `entry`=47927;
DELETE FROM `smart_scripts` WHERE `entryorguid` =47972;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES (47972,0,0,1,62,0,100,0,47972,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Commander Schnottz - On gossip option select - Close gossip');
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES (47972,0,1,0,61,0,100,0,0,0,0,0,33,48189,0,0,0,0,0,7,0,0,0,0,0,0,0,'Commander Schnottz - Kill Credit');

update `creature_template` set `npcflag`=1 WHERE `gossip_menu_id` in(13376,262,11372);
update `creature_template` set `gossip_menu_id`=11372 where `entry`=40358;

-- wrong queststarters.
DELETE FROM `creature_queststarter` WHERE `quest`=10120;
INSERT INTO `creature_queststarter` (`id`,`quest`) VALUES (19253,10120);
DELETE FROM `creature_questender` where `quest`=10120;
INSERT INTO `creature_questender` (`id`,`quest`) VALUES (18930,10120);

-- wrong queststarters.
DELETE FROM `creature_queststarter` WHERE `quest`=10210;
INSERT INTO `creature_queststarter` (`id`,`quest`) VALUES (19684,10210);
DELETE FROM `creature_questender` where `quest`=10210;
INSERT INTO `creature_questender` (`id`,`quest`) VALUES (18481,10210);

-- missing crate loot
UPDATE `gameobject_template` SET data1=3660 WHERE entry=3660;
delete from `gameobject_loot_template` where `Entry`=3660;
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,1754,0,1.3,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,1755,0,1.3,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,1756,0,1.3,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,1757,0,1.3,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,1758,0,1.3,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,1759,0,1.3,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,1760,0,1.3,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,1761,0,1.3,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,1780,0,1.8,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,1782,0,2,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,1783,0,2,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,1784,0,2,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,1785,0,2,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,1786,0,1.9,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,1803,0,1.7,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,1804,0,1.8,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,1805,0,1.8,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,1806,0,2,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,1807,0,1.9,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,1808,0,1.7,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,1809,0,1.7,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,1810,0,1.8,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,2221,0,2,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,2222,0,1.9,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3380,0,1.9,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3381,0,1.8,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3792,0,1.8,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3793,0,1.8,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3794,0,1.6,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3795,0,1.8,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3796,0,1.8,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3797,0,1.6,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3798,0,1.6,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3799,0,1.6,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3800,0,1.5,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3801,0,1.7,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3802,0,2,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3803,0,1.2,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3804,0,1.5,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3805,0,1.9,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3806,0,1.7,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3807,0,1.5,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3808,0,1.3,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3809,0,1.3,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3810,0,1.3,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3811,0,1.1,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3812,0,1.3,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3813,0,1.3,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3814,0,1.3,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3815,0,1.3,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3816,0,2,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,3817,0,1.8,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,8746,0,1.9,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,8747,0,1.5,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3660,8748,0,1.3,0,1,0,1,1,NULL);

-- missing silithid mound loot.
UPDATE `gameobject_template` SET data1=3685 WHERE entry=3685;
delete from `gameobject_loot_template` where `Entry`=3685;
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3685,5058,0,100,1,1,0,1,3,NULL);

-- missing weapons crate loot.
UPDATE `gameobject_template` SET data1=3661 WHERE entry=3661;
delete from `gameobject_loot_template` where `Entry`=3661;
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3661,1825,0,4,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3661,1826,0,4,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3661,1827,0,4,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3661,1828,0,4,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3661,1829,0,4,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3661,1830,0,4,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3661,1831,0,5,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3661,2766,0,4,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3661,2785,0,4,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3661,2786,0,4,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3661,3778,0,5,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3661,3779,0,5,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3661,3780,0,5,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3661,3781,0,5,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3661,3782,0,5,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3661,3783,0,4,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3661,3784,0,5,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3661,3785,0,5,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3661,3786,0,5,0,1,0,1,1,NULL);
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (3661,3787,0,5,0,1,0,1,1,NULL);


