
-- Acidic Venom Sac should not drop from Darkfang Creeper (by Exodius)
-- DELETE FROM `creature_loot_template` WHERE `entry`=4412 AND `item`=5959;
-- https://cata-twinhead.twinstar.cz/?item=5959#dropped-by cata have 25% as present in db

-- The Severed Head, removed at 4.0.1 (by Noxious)
DELETE FROM `disables` WHERE `sourceType`=1 AND `entry`=1239;
INSERT INTO `disables` (`sourceType`,`entry`,`flags`,`params_0`,`params_1`,`comment`) VALUES
(1,1239,0,0,0,'Quest: The Severed Head, Disabled in 4.0.1');
DELETE FROM `creature_queststarter` WHERE `quest`=1239;
DELETE FROM `creature_questender` WHERE `quest`=1239;

-- [Dustwallow Marsh] Acidic Swamp Ooze, SAI correction (by Exodius)
-- Spell should be 43135 (Bubbling Ooze), not 73135 (Old Friends: Quest Accept & Bind)
UPDATE `smart_scripts` SET `action_param1`=43135 WHERE `entryorguid`=4393 AND `source_type`=0 AND `id`=0 AND `link`=0;

-- Against the Wind, % bumped to 100 as per Armory (by Exodius)
UPDATE `creature_loot_template` SET `Chance`=100 WHERE `entry`=32985 AND `item`=44868;

-- values are present in db.. 
-- [Swamp Of Sorrows] In With a Bang (by Exodius)
-- Loot entry taken from `data1` of GO's entries
-- DELETE FROM `gameobject_loot_template` WHERE `item` IN (61921,61922,61373);
-- INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
-- (34739, 61921, -100, 1, 0, 1, 1), -- TTC Fuse
-- (34740, 61922, -100, 1, 0, 1, 1), -- EPB Powder
-- (34741, 61373, -100, 1, 0, 1, 1); -- Stack of Questionable Publications

-- [Swamp Of Sorrows] Stonard Supplies (by Noxious)
delete from gameobject_loot_template where entry=206391 and item=62516;
INSERT INTO gameobject_loot_template values -- ` SET `ChanceOrQuestChance`=-100 WHERE `entry`=206391 AND `item`=62516; -- Stonard Supplies
(206391, 62516, 0, 100, 1, 1, 0, 1, 1, "");

-- [Blasted Lands] Illycor, SAI correction (by Exodius)
-- Spell should be 84297 (Corrosive Saliva), not 84257 (The Reckoning: Cancel Phase and Teleport)
UPDATE `smart_scripts` SET `action_param1`=84297 WHERE `entryorguid`=41163 AND `source_type`=0 AND `id`=0 AND `link`=0;

-- text is present
-- Some quest updates (by Exodius)
-- UPDATE `quest_template` SET `OfferRewardText`='You are a quick study in our ways. I look forward to continuing your training in the future. Return to me when the time is right.' WHERE `Id`=26947;
-- UPDATE `quest_template` SET `OfferRewardText`='So, the king has heard our plea? Thank Elune! We can use all the help we can get.' WHERE `Id`=28490;
-- UPDATE `quest_template` SET `OfferRewardText`='A disciple of the arcane always finds a way forward.  I''m glad to see you, $N.' WHERE `Id`=14277;
-- UPDATE `quest_template` SET `OfferRewardText`='You''ve learned with such speed and ease.  Soon you''ll be the one doing the teaching.' WHERE `Id`=14281;
-- UPDATE `quest_template` SET `OfferRewardText`='You''ve done well in coming here.  If we Gilneans stick together we might yet defeat this terrible enemy.' WHERE `Id`=14288;
-- UPDATE `quest_template` SET `OfferRewardText`='You did the impossible, $N.  You convinced Grandma Wahl to leave her home.$B$BYou are something else, let me tell you.' WHERE `Id`=14402;

UPDATE `quest_template` SET `RequestItemsText`='Their pride kept them in Auberdine for this long, but none deserve such a cruel fate.' WHERE `Id`=13518;
UPDATE `quest_template` SET `RequestItemsText`='Are their numbers weakened?' WHERE `Id`=13945;
UPDATE `quest_template` SET `RequestItemsText`='Did you have any success in routing those grellkin for us?' WHERE `Id`=13946;
UPDATE `quest_template` SET `RequestItemsText`='Did you find the source of the corruption?' WHERE `Id`=14005;
UPDATE `quest_template` SET `RequestItemsText`='This is grim work. It pains me to have to inflict such violence on creature of the forest, corrupt or not.' WHERE `Id`=28726;
UPDATE `quest_template` SET `RequestItemsText`='I adore these forests. I want to see the corruption purged from them completely. When next I return, I want to do so with a lighter heart.' WHERE `Id`=28727;
UPDATE `quest_template` SET `RequestItemsText`='I hate quilboar!' WHERE `Id`=25190;
UPDATE `quest_template` SET `RequestItemsText`='Is it done yet, $N?' WHERE `Id`=14204;
UPDATE `quest_template` SET `RequestItemsText`='What is it then, $N?' WHERE `Id`=24930;
UPDATE `quest_template` SET `RequestItemsText`='There aren''t many of us left, $N.  We have to look out for those remaining Gilneans.' WHERE `Id`=14395;
-- UPDATE `quest_template` SET `RequestItemsText`='Is it done, $N?' WHERE `Id`=24920;

-- Add The Pewter Pounder to the loot template of King Gurboggle
-- Drop chance: Guaranteed - http://eu.battle.net/wow/en/item/55805
-- UPDATE `creature_template` SET `lootid`=41018 WHERE `entry`=41018;
-- DELETE FROM `creature_loot_template` WHERE `entry`=41018 and `item`=55805;
-- INSERT INTO `creature_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`lootmode`,`groupid`,`mincountOrRef`,`maxcount`) VALUES
-- (41018,55805,-100,1,0,1,1);

-- Add Dark Assassin's Pendant to the loot template of Dark Assassin
-- Drop chance: Guaranteed - http://eu.battle.net/wow/en/item/62033
-- UPDATE `creature_template` SET `lootid`=46202 WHERE `entry`=46202;
-- DELETE FROM `creature_loot_template` WHERE `entry`=46202 and `item`=62033;
-- INSERT INTO `creature_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`lootmode`,`groupid`,`mincountOrRef`,`maxcount`) VALUES
-- (46202,62033,-100,1,0,1,1);
update creature_loot_template set Chance=100 where entry=46202 and item=62033;

-- Add Fresh Gryphon Carcass to the loot template of Untamed Gryphon
-- Drop chance: Guaranteed - http://eu.battle.net/wow/en/item/62915
-- UPDATE `creature_template` SET `lootid`=46158 WHERE `entry`=46158;
-- DELETE FROM `creature_loot_template` WHERE `entry`=46158 and `item`=62915;
-- INSERT INTO `creature_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`lootmode`,`groupid`,`mincountOrRef`,`maxcount`) VALUES
-- (46158,62915,-100,1,0,1,1);
update creature_loot_template set Chance=100 where entry=46158 and item=62915;

-- Add The Elementium Axe to the loot template of Blindeye the Guardian
-- Drop chance: Guaranteed - http://eu.battle.net/wow/en/item/62230
-- UPDATE `creature_template` SET `lootid`=46399 WHERE `entry`=46399;
-- DELETE FROM `creature_loot_template` WHERE `entry`=46399 and `item`=62230;
-- INSERT INTO `creature_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`lootmode`,`groupid`,`mincountOrRef`,`maxcount`) VALUES
-- (46399,62230,-100,1,0,1,1);
update creature_loot_template set Chance=100 where entry=46399 and item=62230;

-- Add Magmalord Falthazar's Head to the loot template of Magmalord Falthazar
-- Drop chance: Guaranteed - http://eu.battle.net/wow/en/item/63286
-- UPDATE `creature_template` SET `lootid`=48015 WHERE `entry`=48015;
-- DELETE FROM `creature_loot_template` WHERE `entry`=48015 and `item`=63286;
-- INSERT INTO `creature_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`lootmode`,`groupid`,`mincountOrRef`,`maxcount`) VALUES
-- (48015,63286,-100,1,0,1,1);
update creature_loot_template set Chance=100 where entry=48015 and item=63286;

-- Add Bahrum's Pants to the loot template of Gorosh the Pant Stealer
-- Drop chance: Guaranteed - http://eu.battle.net/wow/en/item/63374
-- UPDATE `creature_template` SET `lootid`=48102 WHERE `entry`=48102;
-- DELETE FROM `creature_loot_template` WHERE `entry`=48102 and `item`=63374;
-- INSERT INTO `creature_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`lootmode`,`groupid`,`mincountOrRef`,`maxcount`) VALUES
-- (48102,63374,-100,1,0,1,1);
update creature_loot_template set Chance=100 where entry=48102 and item=63374;

-- https://cata-twinhead.twinstar.cz/?item=64317  chance are 90% here.. we have 95%.. 
-- Add Pristine Owl Feather to the loot template of Tawny Owl
-- Drop chance: Guaranteed - http://eu.battle.net/wow/en/item/64317
-- UPDATE `creature_template` SET `lootid`=46162 WHERE `entry`=46162;
-- DELETE FROM `creature_loot_template` WHERE `entry`=46162 and `item`=64317;
-- INSERT INTO `creature_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`lootmode`,`groupid`,`mincountOrRef`,`maxcount`) VALUES
-- (46162,64317,-100,1,0,1,1);

-- Mirla Silverblaze, sniffed data
DELETE FROM `creature` WHERE `guid`=158055;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `MovementType`) VALUES
(158055, 51512, 571, 1, 1, 5762.483, 616.3195, 650.175, 2.129302, 120, 0, 0);

-- Gamon is now immune to mind control
UPDATE `creature_template` SET `mechanic_immune_mask`=1 WHERE `entry`=6466;

-- data are present
-- Vial of the Sands drake
-- UPDATE creature_template SET `VehicleId`=200 WHERE `entry`=50269;

-- Shovel (Item 63150) should be usable only on Human Seedlings
DELETE FROM conditions WHERE sourceTypeOrReferenceId=13 AND sourceEntry=89089;
INSERT INTO conditions (sourceTypeOrReferenceId, sourceGroup, sourceEntry, sourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ErrorTextId, COMMENT) VALUES
(13,0,89089,0,0,31,3,47872,0,0,12,0,0,'Shovel should target only Human Seedlings');

-- Shoulder-Mounted Drake Dropper should target only Dragonmaw Black Drakes
DELETE FROM conditions WHERE sourceTypeOrReferenceId=13 and sourceEntry=89557;
INSERT INTO conditions (sourceTypeOrReferenceId, sourceGroup, sourceEntry, sourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ErrorTextId, Comment) VALUES
(13,0,89557,0,0,31,3,48197,0,0,12,0,0,'Shoulder-Mounted Drake Dropper should target only Dragonmaw Black Drakes');

-- Nature's Reprisal (13946) quest script
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 13 AND `SourceEntry` = 65455;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 1, 65455, 0, 0, 31, 0, 3, 2002, 0, 0, 0, 0, '', 'Nature''s Fury can hit only Rascal Sprite'),
(13, 1, 65455, 0, 1, 31, 0, 3, 2003, 0, 0, 0, 0, '', 'Nature''s Fury can hit only Shadow Sprite'),
(13, 1, 65455, 0, 2, 31, 0, 3, 2004, 0, 0, 0, 0, '', 'Nature''s Fury can hit only Dark Sprite');
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` IN (2002, 2003, 2004);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (2002, 2003, 2004);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(2002, 0, 0, 0, 8, 0, 100, 1, 65455, 0, 0, 0, 33, 34440, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Rascal Sprite - on spell hit (65455) - give quest credit (34440)'),
(2003, 0, 0, 0, 8, 0, 100, 1, 65455, 0, 0, 0, 33, 34440, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Shadow Sprite - on spell hit (65455) - give quest credit (34440)'),
(2004, 0, 0, 0, 8, 0, 100, 1, 65455, 0, 0, 0, 33, 34440, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Dark Sprite - on spell hit (65455) - give quest credit (34440)');
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (65455, -65462);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(65455, 65462, 1, 'Nature''s Fury - root and shrink effect'),
(-65462, 65456, 0, 'Nature''s Fury - explode effect');

-- Ring of Frost flees from caster
UPDATE `creature_template` SET `unit_flags`=33556552 WHERE `entry`=44199;

-- present for cata https://cata-twinhead.twinstar.cz/?quest=959
-- Trouble at the Docks, quest removed after Cataclysm (by Exodius)
-- DELETE FROM `disables` WHERE `sourceType`=1 AND `entry`=959;
-- INSERT INTO `disables` (`sourceType`,`entry`,`flags`,`params_0`,`params_1`,`comment`) VALUES
-- (1,959,0,0,0,'Quest: Trouble at the Docks, Removed after Cataclysm launch');
-- DELETE FROM `creature_queststarter` WHERE `quest`=959;
-- DELETE FROM `creature_questender` WHERE `quest`=959; 

-- Sigil of Strom, droprate (by Noxious)
-- UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=-50 WHERE `entry` IN (2241, 2590, 2591, 2588) AND `item`=4440;
update creature_loot_template set Chance=50 where entry IN (2241, 2590, 2591, 2588) and item=4440;

-- Kovork, level correction (by Exodius)
UPDATE `creature_template` SET `minlevel`=26, `maxlevel`=26 WHERE `entry`=2603;

-- Boulderfist Ogre, level correction (by Exodius)
UPDATE `creature_template` SET `maxlevel`=26 WHERE `entry`=2562;

-- https://cata-twinhead.twinstar.cz/?npc=2738
-- Stromgarde Cavalryman, removed in Cataclysm (by Exodius)
-- DELETE FROM `creature` WHERE `id`=2738;

-- https://cata-twinhead.twinstar.cz/?quest=8165 present
-- https://cata-twinhead.twinstar.cz/?quest=8162 present
-- More Resource Crates, obsolete after Cata (by Noxious)
-- Cut Arathor Supply Lines, obsolete after Cata (by Noxious)
-- DELETE FROM `disables` WHERE `sourceType`=1 AND `entry` IN (8165, 8162);
-- INSERT INTO `disables` (`sourceType`,`entry`,`flags`,`params_0`,`params_1`,`comment`) VALUES
-- (1,8165,0,0,0,'Quest: More Resource Crates, Disabled in 4.0.1'),
-- (1,8162,0,0,0,'Quest: Cut Arathor Supply Lines, Disabled in 4.0.1');
-- DELETE FROM `creature_queststarter` WHERE `quest` IN (8165, 8162);
-- DELETE FROM `creature_questender` WHERE `quest` IN (8165, 8162);

-- Nimar the Slayer, level correction (by Exodius)
UPDATE `creature_template` SET `minlevel`=26, `maxlevel`=26 WHERE `entry`=2606;

-- https://cata-twinhead.twinstar.cz/?npc=2595 only level 27??
-- Daggerspine Raider, level correction (by Exodius)
UPDATE `creature_template` SET `minlevel`=27, `maxlevel`=28 WHERE `entry`=2595;

-- Calcified Elven Gem, missing loot (by Exodius)
DELETE FROM `gameobject_loot_template` WHERE `entry`=2712 AND `item`=4492;
INSERT INTO `gameobject_loot_template` values
(2712, 4492, 0, 100, 1, 1, 0, 1, 1, "");

-- Vilebranch Kidnapper, drop rate (by Noxious)
-- UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=-100 WHERE `entry`=14748 AND `item`=19034;

-- Molok the Crusher, double spawn & level correction (by Exodius)
UPDATE `creature_template` SET `minlevel`=26, `maxlevel`=26 WHERE `entry`=2604;

-- Trelane's Wand of Invocation, drop rate (by Noxious)
UPDATE `creature_loot_template` SET `Chance`=100 WHERE `entry`=2793 AND `item`=4525;

-- Wrong models of few creatures in Arathi Highlands (by Exodius)
-- UPDATE `creature` SET `modelid`=11316 WHERE `guid`=70173;
UPDATE `creature` SET `modelid`=4626 WHERE `guid` IN (70169, 70170);
UPDATE `creature` SET `modelid`=4137 WHERE `guid`=70174;

-- Azure Agate, drop rate (by Noxious)
UPDATE `creature_loot_template` SET `Chance`=75 WHERE `entry`=2570 AND `item`=4527;

-- Ruul Onestone, level correction (by Exodius)
UPDATE `creature_template` SET `minlevel`=29, `maxlevel`=29 WHERE `entry`=2602;

-- Vilebranch Soul Eater, not selectable (by Exodius)
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=2647;

-- Hitah'ya the Keeper, removed in Cataclysm (by Noxious)
DELETE FROM `creature` WHERE `id`=10802;

-- Vile Priestess Hexx, removed in Cataclysm (by Noxious)
DELETE FROM `creature` WHERE `id`=7995;

-- Ork Crate, disable movement. Cates should not "walk" around
UPDATE `creature_template` SET `unit_flags`=4 WHERE `entry`=44915;

-- Tablet of Shadra, drop rate (by Noxious)
UPDATE `creature_loot_template` SET `Chance`=100 WHERE `entry`=42877 AND `item`=58241;

-- Cleaning Up the Hinterlands, spawns removed in Cataclysm (by Noxious)
DELETE FROM `creature` WHERE `id`=2648; -- Vilebranch Aman'zasi Guard
DELETE FROM `creature` WHERE `id`=2651; -- Witherbark Hideskinner
DELETE FROM `creature` WHERE `id`=2652; -- Witherbark Venomblood
DELETE FROM `creature` WHERE `id`=2686; -- Witherbark Broodguard
DELETE FROM `creature` WHERE `id`=2653; -- Witherbark Sadist
DELETE FROM `creature` WHERE `id`=2654; -- Witherbark Caller
DELETE FROM `creature` WHERE `id`=2692; -- Highvale Scout
DELETE FROM `creature` WHERE `id`=2691; -- Highvale Outrunner
DELETE FROM `creature` WHERE `id`=2693; -- Highvale Marksman
DELETE FROM `creature` WHERE `id`=2694; -- Highvale Ranger

-- Quest: All That Skitters
UPDATE `creature_template` SET `npcflag`=`npcflag`|0x1000000 WHERE `entry`=42689;
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry`=42689;
INSERT INTO `npc_spellclick_spells` (`npc_entry`,`spell_id`,`cast_flags`,`user_type`) VALUES
(42689, 79591, 3, 0),
(42689, 79588, 1, 0);
DELETE FROM `spell_scripts` WHERE `id`=79588;
INSERT INTO `spell_scripts` (`id`,`effIndex`,`delay`,`command`,`datalong`,`datalong2`,`dataint`,`x`,`y`,`z`,`o`)VALUES
(79588,0,0,18,0,0,0,0,0,0,0);

-- Fledgling Chillwind, removed after Cataclysm (by Noxious)
DELETE FROM `creature` WHERE `id`=7447;

-- Shardtooth Mauler, level corrections (by Exodius)
UPDATE `creature_template` SET `minlevel`=52, `maxlevel`=53 WHERE `entry`=7443;

-- Winterfall Crate drop chance (by Noxious)
UPDATE `creature_loot_template` SET `Chance`=100 WHERE `entry`=10916 AND `item`=12829;

-- Crudely Written Log drop chance (by Noxious)
UPDATE `creature_loot_template` SET `Chance`=100 WHERE `entry`=10738 AND `item`=12842;

-- https://cata-twinhead.twinstar.cz/?npc=15623  level 62.. spawned by script
-- Xandivious, wrong level (by Exodius)
-- UPDATE `creature_template` SET `minlevel`=55, `maxlevel`=55 WHERE `entry`=15623;
delete from creature where guid=118841;

-- Delivery to Donova (28524), wrong quest starter (by Exodius)
-- Winterfall Firewater (28462) starts from item, not NPC
DELETE FROM `creature_queststarter` WHERE `id`=9298 AND `quest` IN (28524,28462);

-- NPCs Removed in Cata (by Noxious)
DELETE FROM `creature` WHERE `id` IN (11808,7749,7745,14458); -- Grum Redbeard (11808), Chillwind Ravager (7749), Elder Shardtooth (7745), Watery Invader (14458)
DELETE FROM `creature` WHERE `id`=10660; -- Cobalt Broodling
DELETE FROM `creature` WHERE `id`=7457; -- Rogue Ice Thistle

-- Shadethicket Oracle, Removed in 4.0.3a
DELETE FROM `creature` WHERE `id`=3931;

-- Armaments of War (Priest), Removed in 4.0.1 (by Noxious)
-- The rest of Armaments of War class quests (by Exodius)
-- The Calling, Removed in 4.0.1 (by Noxious)
DELETE FROM `disables` WHERE `sourceType`=1 AND `entry` IN (8315,8316,8376,8377,8378,8379,8380,8381,8382);
INSERT INTO `disables` (`sourceType`,`entry`,`flags`,`params_0`,`params_1`,`comment`) VALUES
(1,8315,0,0,0,'Quest: The Calling, Disabled in 4.0.1'),
(1,8316,0,0,0,'Quest: Armaments of War (Warrior), Disabled in 4.0.1'),
(1,8376,0,0,0,'Quest: Armaments of War (Paladin), Disabled in 4.0.1'),
(1,8377,0,0,0,'Quest: Armaments of War (Hunter), Disabled in 4.0.1'),
(1,8378,0,0,0,'Quest: Armaments of War (Rogue), Disabled in 4.0.1'),
(1,8379,0,0,0,'Quest: Armaments of War (Priest), Disabled in 4.0.1'),
(1,8380,0,0,0,'Quest: Armaments of War (Shaman), Disabled in 4.0.1'),
(1,8381,0,0,0,'Quest: Armaments of War (Mage, Warlock), Disabled in 4.0.1'),
(1,8382,0,0,0,'Quest: Armaments of War (Druid), Disabled in 4.0.1');
DELETE FROM `creature_queststarter` WHERE `quest` IN (8315,8316,8376,8377,8378,8379,8380,8381,8382);
DELETE FROM `creature_questender` WHERE `quest` IN (8315,8316,8376,8377,8378,8379,8380,8381,8382);

-- Vyral the Vile not dropping the Signet Ring (by Noxious)
UPDATE `creature_loot_template` SET `Chance`=100 WHERE `entry`=15202 AND `item`=20466;

-- Geologist Larksbane, wrong quest starter
DELETE FROM `creature_queststarter` WHERE `id`=15183 AND `quest`=8314;

-- Fix SAI for Supervisor Fizsprocket. `action_param1` was 7973 (Summon Deviate Viper) instead of 79733 (Commanding Shout) (by Exodius)
UPDATE `smart_scripts` SET `action_param1`=79733 WHERE `entryorguid`=3051 AND `source_type`=0 AND `id`=0 AND `link`=0;
-- Move Deviate Viper (5755), Deviate Adder (5048), Druid of the Fang (3840), Deviate Python (8886) to Wailing Caverns (by Exodius)
UPDATE `creature` SET `map`=43 WHERE `id` IN (3840,5048,5755,8886);

-- Gnome Engineering, removed after 4.0.1
DELETE FROM `disables` WHERE `sourceType`=1 AND `entry`=3635;
INSERT INTO `disables` (`sourceType`,`entry`,`flags`,`params_0`,`params_1`,`comment`) VALUES
(1,3635,0,0,0,'Quest: Gnome Engineering, Removed in 4.0.1');
DELETE FROM `creature_queststarter` WHERE `quest`=3635;
DELETE FROM `creature_questender` WHERE `quest`=3635;

-- Report 295: Gazlowe's Fortune missing loot
-- DELETE FROM `gameobject_loot_template` WHERE `entry`=195206 AND `item`=46833;
-- INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
-- (195206, 46833, -100, 1, 0, 1, 1);

-- Lazy Peons should not offer the quest
DELETE FROM `creature_queststarter` WHERE `id`=10556 and`quest`=25134;
UPDATE `creature_template` SET `npcflag`=0 WHERE `entry`=10556;

-- Corrupted Dreadmaw Crocolisk removed at Cataclysm launch
DELETE FROM `creature` WHERE `id`=3231;

-- Razormade Raider levels fixed.
UPDATE `creature_template` SET `minlevel`=12, `maxlevel`=13 WHERE `entry`=34487;

-- Razormane Wolf "skull" level.
UPDATE `creature_template` SET `maxlevel`=8 WHERE `entry`=3939;








