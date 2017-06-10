
--  npc levels Temple and surounding.

UPDATE `creature_template` SET `minlevel` = '88' , `maxlevel` = '88' WHERE `entry` IN(51060,51065);
UPDATE `creature_template` SET `minlevel` = '80' , `maxlevel` = '81' WHERE `entry` IN(43123,43032);
UPDATE `creature_template` SET `minlevel` = '93' , `maxlevel` = '93' WHERE `entry`=45042;
UPDATE `creature_template` SET `minlevel` = '81' , `maxlevel` = '81' WHERE `entry` IN(45005,43254);
UPDATE `creature_template` SET `minlevel` = '84' , `maxlevel` = '84' WHERE `entry` IN (44889,44890,43405);
UPDATE `creature_template` SET `minlevel` = '81' , `maxlevel` = '82' WHERE `entry` IN (43258,43254,43258,43971);
UPDATE `creature_template` SET `minlevel` = '83' , `maxlevel` = '83' WHERE `entry` IN (44885,43071,43954,43995,43984,43036,45300,44835,43356,42889);
UPDATE `creature_template` SET `minlevel` = '82' , `maxlevel` = '82' WHERE `entry` IN (43160,43170,43232,43174,43960,43138,43233,42747,45006,45028,42606,42607);
UPDATE `creature_template` SET `minlevel` = '82' , `maxlevel` = '82' WHERE `entry` IN (66815,42574,45099,42574,43026,45298);

DELETE FROM `creature_template_addon` WHERE `entry`=44327;
insert into `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `auras`) values
('44327','0','0','0','1','0','0','0','0','82863');
UPDATE `creature_template` SET `unit_flags` = 526336 WHERE `entry` = 43138;

delete from `npc_spellclick_spells` where `npc_entry` in(43038,43032,43044);
insert into `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) values('43032','80393','1','0');
insert into `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) values('43044','80436','1','0');
insert into `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) values('43038','80446','1','0');

UPDATE `creature_template` SET `minlevel` = '83' , `maxlevel` = '83' WHERE `entry` = '43358'; 
UPDATE `creature_template` SET `npcflag`=16777216 WHERE `entry` IN(43038,43032,43044);
UPDATE `gameobject_template` SET `data5` = 26245 WHERE `entry` IN (204390,204392,204391);
UPDATE `gameobject_template` SET `data1` = 26246 WHERE `entry` = 204274;
UPDATE `quest_template` set `Method`=2 WHERE `id`=26245;
UPDATE `gameobject_template` SET `IconName` = 'Quest' WHERE `entry` = '204274';
DELETE FROM `gameobject_queststarter` WHERE quest=26246;
INSERT INTO `gameobject_queststarter` (`id`, `quest`) values('204274','26246');
DELETE FROM `creature_queststarter` where `quest`=26246;

