
update creature_loot_template set ChanceOrQuestChance=-24 where entry=114 and item=1274;
update creature_loot_template set ChanceOrQuestChance=18 where entry=114 and item=57935;
update creature_loot_template set ChanceOrQuestChance=4 where entry=114 and item=814;
update creature_loot_template set ChanceOrQuestChance=4 where entry=114 and item=732;
update creature_loot_template set ChanceOrQuestChance=4 where entry=114 and item=4359;
update creature_loot_template set ChanceOrQuestChance=4 where entry=114 and item=4361;

delete from creature_loot_template where entry=114 and item=4362;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(114, 4362, 2.4011, 1, 0, 1, 1);

update creature_template set questItem1=1274, questItem2=57935 where entry=114;

UPDATE quest_template set RequiredItemId1=57935, RequiredItemCount1=0 where Id=26237; -- needed to drop quest item.. but not to kill.. 
 
update quest_template set RequiredSourceItemId1=57954, RequiredSourceItemCount1=1, RequiredSourceItemId4=0, RequiredSourceItemCount4=0 where Id=25257;

update creature_template set AIName="", ScriptName="npc_overloaded_harvest_golem_42381" where entry=42381;
update creature_template set AIName="", ScriptName="npc_overloaded_harvest_golem_42601" where entry=42601;
update creature_template set AIName="", ScriptName="npc_homeless_stormwind_citizen_42386" where entry=42386;
update creature_template set unit_flags=16777224 where entry=42601;

delete from spell_script_names where spell_id=74936;
insert into spell_script_names values (74936, "spell_wake_harvest_golem");

DELETE FROM `creature` WHERE `guid` IN (269426, 269427, 269428);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(269426, 42381, 0, 1, 1, 0, 1, -10167.2, 1318.08, 37.9165, 1.51118, 300, 0, 0, 273, 0, 0, 0, 0, 0),
(269427, 42381, 0, 1, 1, 0, 1, -10167.6, 1305.95, 37.433, 3.04271, 300, 0, 0, 273, 0, 0, 0, 0, 0),
(269428, 42381, 0, 1, 1, 0, 1, -10183.4, 1286.33, 36.4736, 2.76389, 300, 0, 0, 247, 0, 0, 0, 0, 0);

delete from version where cache_id=0;
insert into version values ("ArkCORE4-NG", "unknown", "ArkDB 7.9.1 - 2015-03-11 for ArkCORE4 NG", 0);
