

/*########################
-- Provided FOC and free from garuntees. 
-- Quest Sai.
#########################*/

-- Quest ID:26762 "Reactivate the Constructs
-- https://cata-twinhead.twinstar.cz/?quest=27932

UPDATE `quest_template` SET `Method` =2 WHERE `Id` =26762;

delete from `creature_text` where `entry`=43984;
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('43984','1','0','Slay stone troggs.','12','0','100','0','0','0','War Construct','44352');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('43984','1','1','Reactivated.','12','0','100','0','0','0','War Construct','44354');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('43984','1','2','Destroy.','12','0','100','0','0','0','War Construct','44353');

UPDATE `creature_template` SET `minlevel` =83,`maxlevel` = 83,`npcflag`=1 WHERE `entry` =43984;
UPDATE `creature_template` SET `minlevel` =83,`maxlevel` = 83 WHERE `entry` =43996;
UPDATE `creature_template` SET `type_flags`=4096 WHERE `entry` =43996;
UPDATE `creature_template` SET `flags_extra` =0,`unit_flags`=32768 WHERE `entry`=43995;

delete from `conditions` where `SourceEntry`=43984 and `SourceGroup`=1;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`, `Comment`) VALUES ('22', '1', '43984', '9', '26762', 'Sai.quest');

UPDATE `creature_template` SET `mindmg` = 509 , `maxdmg` = 683 , `attackpower` = 805 , `minrangedmg` = 371 , `maxrangedmg` = 535 , `rangedattackpower` = 146 WHERE `entry` = 43996;

-- Reactivated/Deactivated War Construct AI.
UPDATE `creature_template` SET  `AIName`='SmartAI' WHERE `entry` in (43996,43995,43984);
delete from `smart_scripts` WHERE `entryorguid` in (43996,43995,43984);
insert into `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values('43984','0','0','0','64','0','100','0','0','0','0','0','72','0','0','0','0','0','0','7','0','0','0','0','0','0','0','Deactivated War Construct - On Gossip - close gossip.');
insert into `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values('43984','0','1','2','64','0','100','1','0','0','0','0','33','43984','0','0','0','0','0','7','0','0','0','0','0','0','0','Deactivated War Construct - On Gossip - kill credit.');
insert into `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values('43984','0','2','3','61','0','100','0','0','0','0','0','12','43996','4','60000','0','0','0','1','0','0','0','0','0','0','0','Deactivated War Construct - On SmartLink - Summon Unit.');
insert into `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values('43984','0','3','0','61','0','100','0','0','0','0','0','41','500','0','0','0','0','0','1','0','0','0','0','0','0','0','Deactivated War Construct - On SmartLink - Despawn.');
insert into `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values('43996','0','0','0','54','0','100','0','0','0','0','0','1','1','0','0','0','0','0','1','0','0','0','0','0','0','0','Reactived War Construct - OnSummoned - Say Random.');
insert into `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values('43996','0','1','0','4','0','100','1','0','0','0','0','11','82120','64','0','0','0','0','1','0','0','0','0','0','0','0','Reactived War Construct - OnAggro - Cast Ground Smash.');
insert into `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values('43995','0','0','0','1','0','100','0','1000','1000','100000','100000','11',' 45104','2','0','0','0','0','1','0','0','0','0','0','0','0','Mystic - OnSpawn - Cast self');

-- Various NPC Fractured Front Deepholm
UPDATE `creature_template` SET `minlevel`=83,`maxlevel`=83,`npcflag`=1 WHERE `entry`=43984;
UPDATE `creature_template` SET `minlevel`=82,`maxlevel`=82 WHERE `entry`=45043;
UPDATE `creature_template` SET `minlevel`=81,`maxlevel`=81 WHERE `entry`=43169;
UPDATE `creature_template` SET `minlevel`=81,`maxlevel`=81 WHERE `entry`=43319;
UPDATE `creature_template` SET `minlevel`=83,`maxlevel`=83 WHERE `entry`=43168;
UPDATE `creature_template` SET `minlevel`=82,`maxlevel`=82 WHERE `entry`=45043;
UPDATE `creature_template` SET `minlevel`=82,`maxlevel`=82 WHERE `entry`=45064;
UPDATE `creature_template` SET `minlevel`=83,`maxlevel`=83 WHERE `entry`=43996;
UPDATE `creature_template` SET `minlevel`=83,`maxlevel` =83 WHERE `entry`=43984;
UPDATE `creature_template` SET `minlevel`=82,`maxlevel` =82 WHERE `entry`=43233;
UPDATE `creature_template` SET `minlevel`=83,`maxlevel` =83 WHERE `entry`=43897;
UPDATE `creature_template` SET `minlevel`=83,`maxlevel` =83 WHERE `entry`=43898;
UPDATE `creature_template` SET `minlevel`=82,`maxlevel`=82 WHERE `entry`=43232;
UPDATE `creature_template` SET `minlevel`=82,`maxlevel`=82 WHERE `entry`=43174;
UPDATE `creature_template` SET `minlevel`=82,`maxlevel`=82 WHERE `entry`=43635;
UPDATE `creature_template_addon` SET `auras`=(NULL) WHERE `entry`=43174;
UPDATE `creature_template` SET `minlevel` = '83' , `maxlevel` = '83' WHERE `entry` = '43160';
UPDATE `gossip_menu_option` SET `option_id`=1,`npc_option_npcflag`=1 WHERE `menu_id`=11916;
UPDATE `creature_template` SET `minlevel` = '83' , `maxlevel` = '83' WHERE `entry` = '44204';
UPDATE `creature_template` SET `minlevel` = '83' , `maxlevel` = '83' WHERE `entry` = '43071';
UPDATE `creature_template` SET `minlevel` = '82' , `maxlevel` = '82' WHERE `entry` =43138;
UPDATE `creature_template` SET `flags_extra`=0 WHERE `entry` =43995;

UPDATE `creature_template_addon` SET `auras`=NULL WHERE `entry`=43134;
UPDATE `creature_template` SET `minlevel`=82,`maxlevel`=82 WHERE `entry`=44220;
UPDATE `creature_template` SET `minlevel`=82,`maxlevel`=82 WHERE `entry`=44218;
UPDATE `creature_template` SET `minlevel`=82,`maxlevel`=82 WHERE `entry`=44229;
UPDATE `creature` SET `position_y`=1388.83,`position_z`=213.163 WHERE `guid`=242345;


delete from `npc_spellclick_spells` where `npc_entry`=43509 and `spell_id`=46598;
insert into `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) values('43509','46598','0','0');

delete from `vehicle_template_accessory` where `entry`=43509;
insert into `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) values('43509','43635','0','1','Earthen Catapult.','6','30000');


UPDATE `creature_template` SET `minlevel`=82,`maxlevel` =82,`AIName`='SmartAI' WHERE `entry` =43160;

delete from `creature_text` where `entry`=43160;
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('43160','0','1','This Is Stonehearth!','14','0','100','0','0','0','Earthreaker Dolomite','43148');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('43160','0','2','Hold your ground!','14','0','100','0','0','0','Earthreaker Dolomite','43143');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('43160','0','3','We have reinforcements! For the Stonefather!','14','0','100','0','0','0','Earthreaker Dolomite','43145');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('43160','0','4','For Stonefather Oremantle!','14','0','100','0','0','0','Earthreaker Dolomite','43161');

delete from `smart_scripts` where `entryorguid`=43160;
insert into `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values
('43160','0','0','0','1','0','100','0','12000','12000','50000','50000','1','0','0','0','0','0','0','1','0','0','0','0','0','0','0','Earthreaker Dolomite - On Update(OOC) - Random Yell.');



