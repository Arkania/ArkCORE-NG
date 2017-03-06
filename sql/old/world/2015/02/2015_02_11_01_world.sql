
update quest_template set Flags=0, SpecialFlags=0 where Id=26693;

update creature_template set KillCredit1=579 where entry in (429,432,433,434,568);
update creature_template set KillCredit2=579 where entry in (431);

update creature_loot_template set ChanceOrQuestChance=-100 where entry=703 and item=3632;
update creature_loot_template set ChanceOrQuestChance=-94.2 where entry=703 and item=59522;
delete from creature_loot_template where  entry=703 and item=1075;
insert into creature_loot_template values (703, 1075, -82.4, 1, 0, 1, 1);

update creature_template set questItem3=59522 where entry=703;

DELETE FROM `creature` WHERE `guid` in (9346,9347);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `MovementType`) VALUES
(9347, 43607, 0, 1, 1, -9138.31, -3039.69, 108.8053, 2.338741, 120, 0, 0), -- Danforth (Area: Redridge Mountains) (Auras: 81897 - Apply Quest Invis Zone 17)
(9346, 43611, 0, 1, 1, -9138.53, -3034.99, 108.7663, 2.635447, 120, 0, 0); -- John J. Keeshan (Area: Redridge Mountains) (Auras: 81897 - Apply Quest Invis Zone 17, 80642 - Keeshan's Quiver)

UPDATE `creature_template` SET `unit_flags`=33088 WHERE `entry` IN (43607 /*Danforth*/, 43608 /*Krakauer*/, 43609 /*Jorgensen*/, 43610 /*Messner*/);

DELETE FROM `creature_addon` WHERE `guid` in(9346,9347,9000,9001,9002);
INSERT INTO `creature_addon` (`guid`, `mount`, `bytes1`, `bytes2`, `auras`) VALUES
(9347, 0, 0x10000, 0x1, "81897"), -- Danforth - Apply Quest Invis Zone 17
(9000, 0, 0x10000, 0x1, '81897'), -- Krakauer - Apply Quest Invis Zone 17
(9002, 0, 0x10000, 0x1, '81897'), -- Jorgensen - Apply Quest Invis Zone 17
(9001, 0, 0x10000, 0x1, '81897'), -- Messner - Apply Quest Invis Zone 17
(9346, 0, 0x10000, 0x2, '81897 80642'); -- John J. Keeshan - Apply Quest Invis Zone 17, Keeshan's Quiver

-- spawned from script..
delete from creature where guid=358735 and id=43714;
delete from creature where guid=9249 and id=43728;

update creature_template set AIName="", ScriptName="npc_grand_magus_doane" where entry=397;
update creature_addon set auras="13787" where guid=34021;
update quest_template set RequiredSourceItemId1=59522,RequiredSourceItemCount1=1 where Id=26694;
update quest_template set RequiredSourceItemId4=0,RequiredSourceItemCount4=0 where Id=26694;

SET @WP=43714;
DELETE FROM waypoint_data WHERE id=@WP;
INSERT INTO waypoint_data (id,point,position_x, position_y, position_z, orientation,delay, move_flag, action, action_chance) VALUES 
(@WP,0,-9645.827,-3459.116,157.2119,0.0,0,0,0,100),
(@WP,1,-9646.281,-3455.874,156.0133,0.0,0,0,0,100),
(@WP,2,-9646.64,-3454.94,156.0133,0.0,0,0,0,100),
(@WP,3,-9646.64,-3454.94,116.4203,0.0,0,0,0,100),
(@WP,4,-9646.64,-3454.94,116.4203,0.0,0,0,0,100);

update quest_poi set objIndex=4, FloorId=0, unk4=3 where questId=26693 and id=0;
update quest_poi set  FloorId=0, unk4=3 where questId=26693 and id=1;

-- https://cata-twinhead.twinstar.cz/?npc=819 spawned by script
delete from creature where id=819;

delete from pool_template where entry=14500;
insert into pool_template values (14500,1,"Ward of Ilgalar");
delete from pool_creature where pool_entry=14500;
insert into pool_creature values
(60960, 14500, 0, "Ward of Ilgalar"),
(60842, 14500, 0, "Ward of Ilgalar"),
(60843, 14500, 0, "Ward of Ilgalar");


