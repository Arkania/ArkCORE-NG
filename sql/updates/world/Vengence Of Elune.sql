/*
SQLyog Community v12.2.6 (64 bit)
MySQL - 5.6.28-log 
*********************************************************************
*/
/*!40101 SET NAMES utf8 */;

/*
--Quest The Vengance of Elune. https://www.wowhead.com/quest=14005/the-vengeance-of-elune

--Enable spell start on quest take, special effects all work.
--Enable Remove *auras due to spell. On quest handin.
--Enable DUMMY spell SpellScript.
--Spell to remove auras is (SPELL_EFFECT_SCRIPT_EFFECT) added script to remove auras after quest hand in.
*/ 
delete from `spell_scripts` where `id`=66166 and `datalong` in(65602,65626);
insert into `spell_scripts` (`id`, `effIndex`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`) values('66166','0','0','14','65602','1','0','0','0','0','0');
insert into `spell_scripts` (`id`, `effIndex`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`) values('66166','0','0','14','65626','1','0','0','0','0','0');

-- quest spells added on QUEST_ACCEPT and QUEST_REWARDED.
UPDATE `quest_template` SET `SourceSpellId`=65602,`RewardSpellCast`=66166 WHERE `id`=14005;

--
-- quest=14005 
--
--

-- Insert loot for Quest:Tundra MacGrann's Stolen Stash :312.DEPRECIATED in Patch (4.0.3)
UPDATE `gameobject_template` SET `QuestItem1`=2667,`data1` = '272' WHERE `entry` = '272';
delete from `gameobject_loot_template` where `entry`=272 and `item`=2667;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) 
values('272','2667','0','100','1','1','0','1','1',NULL);

-- Insert loot for Quest:A Humble Task : 753.DEPRECIATED Quest is NOT avilable to players.
UPDATE `gameobject_template` SET `QuestItem1`=4755,`data1` = '337' WHERE `entry` = '337';
delete from `gameobject_loot_template` where `entry`=337 and `item`=4755;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) 
values('337','4755','0','100','1','1','0','1','1',NULL);

-- The Prince's Chest quest ID:1318 & 7703.
UPDATE `gameobject_template` SET `QuestItem1`=18336,`data1` = '179545' WHERE `entry` = '179545';
delete from `gameobject_loot_template` where `entry`=179545 and `item`=18336;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) 
values('179545','18336','0','100','1','1','0','1','1',NULL);

-- No loot table entry, Cannonball Stack.
-- Loot used to load cannon in Maruaden Dungeon.
UPDATE `gameobject_template` SET `data1` = 176215 WHERE `entry` = 176215;
delete from `gameobject_loot_template` where `entry`=176215 and `item`=12973;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) 
values('176215','12973','0','100','0','1','0','1','1',NULL);

-- I'll Call Him Bitey quest ID:25854.  loot quest object.
UPDATE `gameobject_template` SET `QuestItem1`=56058,`data1` = 203264 WHERE `entry` = 203264;
delete from `gameobject_loot_template` where `entry`=203264 and `item`=56058;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) 
values('203264','56058','0','100','1','1','0','1','1',NULL);

-- https://www.wowhead.com/quest=14486/handling-the-goods
UPDATE `gameobject_template` SET `QuestItem1`=49639,`data1` = 199330 WHERE `entry` in(199329,199330,199331,199332);
delete from `gameobject_loot_template` where `entry`=199330 and `item`=49639;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) 
values('199330','49639','0','100','1','1','0','1','1',NULL);
/* 50363 deathbringers_will*/

/*
-- Quest gameobject missing loot. https://www.wowhead.com/object=193199/pile-of-bones
-- drop needed for https://www.wowhead.com/quest=13291/borrowed-technology 
*/
UPDATE `gameobject_template` SET `QuestItem1`=43609,`data1` = 193199 WHERE `entry` = 193199;
delete from `gameobject_loot_template` where `entry`=199330 and `item`=43609;
REPLACE into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) 
values('193199','43609','0','100','1','1','0','1','1',NULL);

/**/
-- https://www.wowhead.com/quest=27592/drinks-on-the-rocks
UPDATE `gameobject_template` SET `QuestItem1`=61356,`data1` = 205554 WHERE `entry` = 205554;
delete from `gameobject_loot_template` where `entry`=205554 and `item`=61356;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) 
values('205554','61356','0','100','1','1','0','1','1',NULL);
-- add aura spell to crab, aura give crab a bottle to carry.
replace into `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `auras`) 
values('922','0','0','0','4097','0','0','0','0','88038');

-- https://www.wowhead.com/quest=27077/clutching-at-chaos
UPDATE `gameobject_template` SET `QuestItem1`=60738,`data1` = 205094 WHERE `entry` = 205094;
delete from `gameobject_loot_template` where `entry`=205094 and `item`=60738;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) 
values('205094','60738','0','100','1','1','0','1','1',NULL);

-- DEPRECIATED GAME_OBJECT added loot to prevent DBError entry, no objects spawned.
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) values('204965','60575','0','100','1','1','0','1','1',NULL);

-- Mineral Deposit Not Spawned, Added Loot to correct DBError.
UPDATE `gameobject_template` SET `data1` = 203278 WHERE `entry` = 203278;

insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) values('203278','52177','0','0.8','0','1','0','1','1',NULL);
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) values('203278','52178','0','0.8','0','1','0','1','1',NULL);
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) values('203278','52179','0','0.8','0','1','0','1','1',NULL);
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) values('203278','52180','0','0.8','0','1','0','1','1',NULL);
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) values('203278','52181','0','0.8','0','1','0','1','1',NULL);
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) values('203278','52182','0','0.9','0','1','0','1','1',NULL);
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) values('203278','52327','0','10','0','1','0','1','2',NULL);
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) values('203278','52328','0','1.6','0','1','0','1','2',NULL);
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) values('203278','53038','0','100','0','1','0','2','4',NULL);

-- Data is placeholder for unkown loot,No Objects spawn https://www.wowhead.com/object=206510/scavenged-treasure-chest  .
UPDATE `gameobject_template` SET `data1` = 206510 WHERE `entry` = 206510;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) 
values('206510','12973','0','100','0','1','0','1','1','PLACEHOLDER');

-- Added in patch 5.4.2.17645 https://www.wowhead.com/object=203232/ancient-artifact Add loot placeholder to correct DBError.
-- This object is a random spawn in a Pandorian battleground that does not exist in 4.3.4 dbc/maps.
-- This object is a spellcaster (Type 22)to give players a buff (spell also not in 4.3.4 dbc).
UPDATE `gameobject_template` SET `data1` = 203232 WHERE `entry` = 203232;
delete from `gameobject_loot_template` where `entry`=203232 and `item`=12973;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) 
values('203232','12973','0','100','1','1','0','1','1',NULL);

-- Added in patch 5.4.2.17645 https://www.wowhead.com/object=203075/fossil Add loot placeholder to correct DBError.
-- Added in patch 5.4.2.17645 https://www.wowhead.com/object=203076/fossil Add loot placeholder to correct DBError.
delete from `gameobject_loot_template` where `entry`in(203075,203076) and `item`=4654;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) 
values('203075','4654','0','100','1','1','0','1','1','PLACEHOLDER');
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) 
values('203076','4654','0','100','1','1','0','1','1','PLACEHOLDER');

-- https://www.wowhead.com/object=201608/forgotten-dwarven-artifact 
-- https://www.wowhead.com/quest=24477/dwarven-artifacts
UPDATE `gameobject_template` SET `data1` =28434 WHERE `entry` =201608; 
DELETE FROM `gameobject_loot_template` WHERE `ENTRY`=28434 AND `item`=49749;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) 
values('28434','49749','0','100','1','1','0','1','1','PLACEHOLDER');

-- https://www.wowhead.com/quest=25151/he-needs-ale Missing Loot for quest.
UPDATE `gameobject_template` SET `data1` =202567 WHERE `entry` =202567;
delete from `gameobject_loot_template` where `entry`=202567 and `item`=52491;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) 
values('202567','52491','0','100','1','1','0','1','1',NULL);

-- Remove DBError entry for unused DND gameobject, Pandorian object.
UPDATE `gameobject_template` SET `data1` =202573 WHERE `entry` =202573;
delete from `gameobject_loot_template` where `entry`=202573 and `item`=52491;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) 
values('202573','52491','0','100','1','1','0','1','1',NULL);

-- https://www.wowhead.com/object=202556/oxygenated-seaweed Added in patch 5.4.2. DB 4.3.4 quest not exist.
UPDATE `gameobject_template` SET `data1` =202556 WHERE `entry` =202556;
delete from `gameobject_loot_template` where `Entry`=202556 and `item`=52498;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) 
values('202556','52498','0','100','1','1','0','1','1',NULL);

-- https://www.wowhead.com/object=202473/meatfaces-chest. Added in patch 5.4.2.17645 I have no info.
-- Added placeholder loot to fix DBError.
UPDATE `gameobject_template` SET `data1` =202473 WHERE `entry` =202473;
delete from `gameobject_loot_template` where `Entry`=202473 and `item`=52281;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`)
values('202473','52281','0','100','1','1','0','1','1',NULL);

-- https://www.wowhead.com/quest=410/the-dormant-shade https://www.wowhead.com/object=1586/crate-of-candles
UPDATE `gameobject_template` SET `data1`=1586 WHERE `entry` =1586;
delete from `gameobject_loot_template` where `Entry`=1586 and `item`=3080;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) 
values('1586','3080','0','100','1','1','0','1','1',NULL);

-- https://www.wowhead.com/object=194158/heart-of-magic  Raid chest "from Eye of Eternity" 10 man N.
UPDATE `gameobject_template` SET `data1`=194158 WHERE `entry` =194158;
delete from `gameobject_loot_template` where `Entry`=194158 and `item`=44650;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) 
values('194158','44650','0','100','1','1','0','1','1',NULL);

-- https://www.wowhead.com/object=164798/evoroot add missing loot.
UPDATE `gameobject_template` SET `data1`=164798 WHERE `entry` =164798;
delete from `gameobject_loot_template` where `Entry`=164798 and `item`=11242;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) 
values('164798','11242','0','100','1','1','0','1','1',NULL);











