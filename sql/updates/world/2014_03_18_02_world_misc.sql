-- Kandrostrasz <Brood of Alexstrasza> (15503) quests RequiredClasses fix by nelegalno
UPDATE `quest_template` SET `RequiredClasses` = 1 WHERE `Id` IN (8559,8560); -- Warrior
UPDATE `quest_template` SET `RequiredClasses` = 2 WHERE `Id` IN (8629,8655); -- Paladin
UPDATE `quest_template` SET `RequiredClasses` = 4 WHERE `Id` IN (8626,8658); -- Hunter
UPDATE `quest_template` SET `RequiredClasses` = 8 WHERE `Id` IN (8637,8640); -- Rogue
UPDATE `quest_template` SET `RequiredClasses` = 16 WHERE `Id` IN (8593,8596); -- Priest
UPDATE `quest_template` SET `RequiredClasses` = 64 WHERE `Id` IN (8621,8624); -- Shaman
UPDATE `quest_template` SET `RequiredClasses` = 128 WHERE `Id` IN (8631,8634); -- Mage
UPDATE `quest_template` SET `RequiredClasses` = 256 WHERE `Id` IN (8660,8663); -- Warlock
UPDATE `quest_template` SET `RequiredClasses` = 1024 WHERE `Id` IN (8665,8668); -- Druid

-- Andorgos <Brood of Malygos> (15502) quests RequiredClasses fix by nelegalno
UPDATE `quest_template` SET `RequiredClasses` = 1 WHERE `Id` IN (8544,8561); -- Warrior
UPDATE `quest_template` SET `RequiredClasses` = 2 WHERE `Id` IN (8628,8630); -- Paladin
UPDATE `quest_template` SET `RequiredClasses` = 4 WHERE `Id` IN (8657,8659); -- Hunter
UPDATE `quest_template` SET `RequiredClasses` = 8 WHERE `Id` IN (8639,8641); -- Rogue
UPDATE `quest_template` SET `RequiredClasses` = 16 WHERE `Id` IN (8592,8594); -- Priest
UPDATE `quest_template` SET `RequiredClasses` = 64 WHERE `Id` IN (8602,8623); -- Shaman
UPDATE `quest_template` SET `RequiredClasses` = 128 WHERE `Id` IN (8625,8632); -- Mage
UPDATE `quest_template` SET `RequiredClasses` = 256 WHERE `Id` IN (8662,8664); -- Warlock
UPDATE `quest_template` SET `RequiredClasses` = 1024 WHERE `Id` IN (8667,8669); -- Druid

-- Craftsman Wilhelm <Brotherhood of the Light> (16376) NPCs quests
UPDATE `quest_template` SET `RequiredClasses` = 3 WHERE `Id` IN (9234,9235,9236); -- Warrior, Paladin
UPDATE `quest_template` SET `RequiredClasses` = 68 WHERE `Id` IN (9244,9245,9246); -- Hunter, Shaman
UPDATE `quest_template` SET `RequiredClasses` = 400 WHERE `Id` IN (9238,9239,9240); -- Priest, Mage, Warlock
UPDATE `quest_template` SET `RequiredClasses` = 1032 WHERE `Id` IN (9241,9242,9243); -- Rogue, Druid

-- Zanza the Restless (15042) NPCs quests
UPDATE `quest_template` SET `RequiredClasses` = 1 WHERE `Id` = 8184; -- Warrior
UPDATE `quest_template` SET `RequiredClasses` = 2 WHERE `Id` = 8185; -- Paladin
UPDATE `quest_template` SET `RequiredClasses` = 4 WHERE `Id` = 8187; -- Hunter
UPDATE `quest_template` SET `RequiredClasses` = 8 WHERE `Id` = 8186; -- Rogue
UPDATE `quest_template` SET `RequiredClasses` = 16 WHERE `Id` = 8191; -- Priest
UPDATE `quest_template` SET `RequiredClasses` = 64 WHERE `Id` = 8188; -- Shaman
UPDATE `quest_template` SET `RequiredClasses` = 128 WHERE `Id` = 8189; -- Mage
UPDATE `quest_template` SET `RequiredClasses` = 256 WHERE `Id` = 8190; -- Warlock
UPDATE `quest_template` SET `RequiredClasses` = 1024 WHERE `Id` = 8192; -- Druid

-- Vethsera <Brood of Ysera> (15504) quests RequiredClasses fix by nelegalno
UPDATE `quest_template` SET `RequiredClasses` = 1 WHERE `Id` = 8562; -- Warrior
UPDATE `quest_template` SET `RequiredClasses` = 2 WHERE `Id` = 8627; -- Paladin
UPDATE `quest_template` SET `RequiredClasses` = 4 WHERE `Id` = 8656; -- Hunter
UPDATE `quest_template` SET `RequiredClasses` = 8 WHERE `Id` = 8638; -- Rogue
UPDATE `quest_template` SET `RequiredClasses` = 16 WHERE `Id` = 8603; -- Priest
UPDATE `quest_template` SET `RequiredClasses` = 64 WHERE `Id` = 8622; -- Shaman
UPDATE `quest_template` SET `RequiredClasses` = 128 WHERE `Id` = 8633; -- Mage
UPDATE `quest_template` SET `RequiredClasses` = 256 WHERE `Id` = 8661; -- Warlock
UPDATE `quest_template` SET `RequiredClasses` = 1024 WHERE `Id` = 8666; -- Druid

-- Lok'lira the Crone
SET @ENTRY := 29975;
UPDATE `creature_template` SET `AIName`='SmartAI', `ScriptName`='' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,62,0,100,0,9910,0,0,0,33,30467,0,0,0,0,0,7,0,0,0,0,0,0,0,'Loklira - gossip select 4 - The Hyldsmeet Kill credit'),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Loklira - gossip select 4 - Close gossip');

UPDATE `gossip_menu_option` SET `action_menu_id`=9908 WHERE `menu_id`=9907;
UPDATE `gossip_menu_option` SET `action_menu_id`=9909 WHERE `menu_id`=9908;
UPDATE `gossip_menu_option` SET `action_menu_id`=9910 WHERE `menu_id`=9909;

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=9907;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(15,9907,0,0,9,12970,0,0,0,'','Loklira - Show gossip if quest accepted');

-- Thorim
SET @THORIM :=29445;
UPDATE `creature` SET `modelid`=0 WHERE `id`=@THORIM;
UPDATE `creature_template` SET `AIName`='SmartAI', `ScriptName`='' WHERE `entry`=@THORIM;
DELETE FROM `creature_addon` WHERE `guid`=97128;
DELETE FROM `creature_template_addon` WHERE `entry`=@THORIM;
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES
(@THORIM,0,0,1,0,0,'');

DELETE FROM `smart_scripts` WHERE `entryorguid`=@THORIM AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@THORIM,0,0,0,62,0,100,0,9926,0,0,0,33,30514,0,0,0,0,0,7,0,0,0,0,0,0,0,'Thorim - gossip select  - give quest credit');

UPDATE `gossip_menu_option` SET `action_menu_id`=9927 WHERE `menu_id`=9924;
UPDATE `gossip_menu_option` SET `action_menu_id`=9926 WHERE `menu_id`=9927;
UPDATE `gossip_menu_option` SET `action_menu_id`=9925 WHERE `menu_id`=9926;

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=9924;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(15,9924,0,0,9,13064,0,0,0,'','Thorim - Show gossip if quest accepted');

-- Cold Hearted (12856)
SET @NPC_CAPTIVE_DRAKE        := 29708; -- Captive Proto-Drake
SET @NPC_FREED_DRAKE          := 29709; -- Freed Proto-Drake
SET @NPC_PRISONER             := 29639; -- Brunnhildar Prisoner
SET @NPC_LIBERATED            := 29734; -- Liberated Brunnhildar

SET @SPELL_SUM_FREE_DRAKE     := 55028; -- Summon Freed Proto-Drake
SET @SPELL_ICE_SHARD          := 55046; -- Ice Shard (Rank 3)
SET @SPELL_FREE_PRISONER      := 55048; -- Free Brunnhildar Prisoner
SET @AURA_IMPRISONMENT        := 54894; -- Icy Imprisonment


UPDATE `creature_template` SET `speed_walk`=1,`speed_run`=1.14286,`spell1`=@SPELL_ICE_SHARD,`HoverHeight`=4,`unit_flags`=0x1000008,`InhabitType`=4,`ScriptName`='npc_freed_protodrake' WHERE `entry`=@NPC_FREED_DRAKE;
UPDATE `creature_template` SET `unit_flags`=33554432,`AIName`='SmartAI' WHERE `entry`=@NPC_LIBERATED;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry`=@NPC_CAPTIVE_DRAKE;
INSERT INTO `npc_spellclick_spells` (`npc_entry`,`spell_id`,`cast_flags`,`user_type`) VALUES
(@NPC_CAPTIVE_DRAKE,@SPELL_SUM_FREE_DRAKE,1,0);

DELETE FROM `creature_template_addon` WHERE `entry`=@NPC_FREED_DRAKE;
INSERT INTO `creature_template_addon` (`entry`,`mount`,`bytes1`,`bytes2`,`auras`) VALUES
(@NPC_FREED_DRAKE,0,0x3000000,0x1,'55034 61183');

DELETE FROM `creature_text` WHERE `entry`=@NPC_FREED_DRAKE;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@NPC_FREED_DRAKE,0,0,'Return to Brunnhildar Village!',42,0,100,0,0,0,'Freed Proto-Drake'),
(@NPC_FREED_DRAKE,0,1,'The proto-drake smells freedom and flies homeward!',41,0,100,0,0,0,'Freed Proto-Drake');

DELETE FROM `spell_scripts` WHERE `id`=@SPELL_FREE_PRISONER;
INSERT INTO `spell_scripts` (`id`,`effIndex`,`delay`,`command`,`datalong`,`datalong2`,`dataint`,`x`,`y`,`z`,`o`) VALUES
(@SPELL_FREE_PRISONER,0,0,14,@AURA_IMPRISONMENT,0,0,0,0,0,0);

DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@NPC_LIBERATED;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@NPC_LIBERATED,0,0,0,54,0,100,0,0,0,0,0,41,30000,0,0,0,0,0,1,0,0,0,0,0,0,0,'Liberated Brunnhildar - On Spawn - Despawn in 30 seconds');
