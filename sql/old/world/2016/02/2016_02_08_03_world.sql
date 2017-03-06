
-- support Warlock class quests 28459,28478.
UPDATE `gameobject_template` SET data1=207145 WHERE entry =207145;
DELETE FROM `gameobject_loot_template` WHERE `Item`=64308 AND `Entry`=207145;
INSERT INTO `gameobject_loot_template` (`Entry`,`Item`,`Reference`,`Chance`,`QuestRequired`,`LootMode`,`GroupId`,`MinCount`,`MaxCount`,`Comment`) VALUES (207145,64308,0,100,1,1,0,1,1,NULL);

-- supports Druid class quest 28343. A and H same quest.
UPDATE `quest_template` SET `RequiredRaces`=0 where `id`=28343;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=48362;
UPDATE `creature_template` SET `flags_extra`=0,`Health_mod`=10 WHERE `entry`=9024;
UPDATE `creature_loot_template` SET `Chance`=85 WHERE `item`=63469;
DELETE FROM `smart_scripts` WHERE `entryorguid`=48362;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES (48362,0,0,1,8,0,100,0,89914,0,0,0,33,48362,0,0,0,0,0,7,0,0,0,0,0,0,0,'On spellhit~elemental gate bunny~credit');
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES (48362,0,1,0,61,0,100,0,0,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0,0,0,0,'On smartLink~elemental gate bunny~Despawn');

-- supports Priest class quests 28328,28474,28475,28476,28477,28478.
UPDATE `quest_template` SET `RequiredNpcOrGo1`=-207088,`RequiredNpcOrGoCount1`=8 WHERE `id` IN (28328,28474,28475,28476,28477,28478);
UPDATE `gameobject_template` SET `AIName`='SmartGameObjectAI' WHERE `entry`=207088;
UPDATE `gameobject_template` SET `data5`=1,`flags`=64 WHERE `entry`=207088;
DELETE FROM `smart_scripts` WHERE `entryorguid`=207088;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES (207088,1,0,0,8,0,100,0,89777,0,0,0,9,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'twilight creed~on spellhit~activate.');
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES (207088,1,1,0,70,0,100,0,2,0,0,0,33,198002,0,0,0,0,0,7,0,0,0,0,0,0,0,'twilight creed~on spellhit~quest credit.');


-- this item should be in pickpocket_loot not creature_loot.
DELETE FROM creature_loot_template WHERE item=16885;
UPDATE `creature` SET `spawntimesecs`=7200 WHERE `id` IN(8922,8893);
UPDATE `creature_loot_template` SET `Chance`=85 WHERE `item`=63469;
UPDATE `creature_loot_template` SET `Chance`=85 WHERE `item`=64305;
UPDATE `creature_template` SET `gossip_menu_id`=5541 WHERE `entry`=45843;
