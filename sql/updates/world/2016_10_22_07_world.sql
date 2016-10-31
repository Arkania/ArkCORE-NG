DELETE FROM `spell_script_names` WHERE `spell_id` IN (109939, 109949, 101056);

INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES

('109939', 'spell_item_fangs_of_the_father'),
('109949', 'spell_item_fangs_of_the_father_fury_of_the_destroyer'),
('101056', 'spell_item_dragonwrath_tarecgosas_rest');

UPDATE `creature_template` SET `ScriptName`='npc_slipstream_raid', `InhabitType`=7 WHERE `entry`=47066 LIMIT 1;


UPDATE `creature_template` SET `ScriptName` = 'boss_anshal' WHERE `entry` = 45870;
UPDATE `creature_template` SET `ScriptName` = 'boss_nezir' WHERE `entry` = 45871;
UPDATE `creature_template` SET `ScriptName` = 'boss_rohash' WHERE `entry` = 45872;
UPDATE `creature_template` SET `ScriptName` = 'npc_hurricane' WHERE `entry` = 46419;
UPDATE `creature_template` SET `ScriptName` = 'npc_tornado' WHERE `entry` = 46207;
UPDATE `creature_template` SET `ScriptName` = 'npc_ravenous_creeper_trigger' WHERE `entry` = 45813;
UPDATE `creature_template` SET `ScriptName` = 'npc_ravenous_creeper' WHERE `entry` = 45812;

DELETE FROM `spell_script_names` WHERE `spell_id` IN
(86492);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(86492, 'spell_hurricane');

REPLACE INTO spell_script_names VALUES
('88427', 'spell_electrocute'),
('93261', 'spell_wind_burst'),
('93262', 'spell_wind_burst'),
('93263', 'spell_wind_burst'),
('93297', 'spell_lightning_clouds_damage'),
('93298', 'spell_lightning_clouds_damage'),
('93299', 'spell_lightning_clouds_damage'),
('89588', 'spell_lightning_clouds_damage'),
('93255', 'spell_lightning_strike'),
('93256', 'spell_lightning_strike'),
('93257', 'spell_lightning_strike'),
('88214', 'spell_lightning_strike'),
('88238', 'spell_lightning_strike_effect'),
('93854', 'spell_lightning_strike_effect'),
('93855', 'spell_lightning_strike_effect'),
('93856', 'spell_lightning_strike_effect'),
('85422', 'spell_nurture_aura'),
('85429', 'spell_nurture_aura'),
('86367', 'spell_nezir_sleet_storm'),
('93135', 'spell_nezir_sleet_storm'),
('93136', 'spell_nezir_sleet_storm'),
('93137', 'spell_nezir_sleet_storm'),
('85483', 'spell_wind_blast'),
('93138', 'spell_wind_blast'),
('93139', 'spell_wind_blast'),
('89104', 'at_reletness_storm'),
('93140', 'spell_wind_blast');


UPDATE `creature_template` SET `ScriptName` = 'boss_alakir' WHERE `entry` =46753;

UPDATE `creature_template` SET  `ScriptName` =  'npc_soothing_breeze' WHERE `entry` = 46246;
UPDATE `creature_template` SET  `ScriptName` =  'npc_ice_patch' WHERE `entry` = 46186;
UPDATE `creature_template` SET  `ScriptName` =  'npc_tornado_rohash' WHERE `entry` = 46207;


UPDATE `creature_template` SET  `ScriptName` =  'npc_ice_storm' WHERE `entry` = 46973;
UPDATE `creature_template` SET  `ScriptName` =  'npc_ice_storm_rain' WHERE `entry` = 46734;
UPDATE `creature_template` SET  `ScriptName` =  'npc_stormling_pre_effect' WHERE `entry` = 47177;
UPDATE `creature_template` SET  `ScriptName` =  'npc_stormling' WHERE `entry` = 47175;
UPDATE `creature_template` SET  `ScriptName` =  'npc_stormling' WHERE `entry` = 47177;
UPDATE `creature_template` SET  `ScriptName` =  'npc_relentless_storm_initial_vehicle' WHERE `entry` = 47806;
UPDATE `creature_template` SET  `ScriptName` =  'npc_lightning_coulds' WHERE `entry` = 48190;
UPDATE `creature_template` SET  `ScriptName` =  'npc_lightning_coulds' WHERE `entry` = 48196;
UPDATE `creature_template` SET  `ScriptName` =  'npc_relentless_storm' WHERE `entry` = 47807;
UPDATE `creature_template` SET  `ScriptName` =  'npc_relentless_storm' WHERE `entry` = 47806;
UPDATE `creature_template` SET  `ScriptName` =  'npc_wind_funnel' WHERE `entry` = 48855;
UPDATE `creature_template` SET  `ScriptName` =  'npc_wind_funnel' WHERE `entry` = 48854;
UPDATE `creature_template` SET  `ScriptName` =  'npc_squall_line' WHERE `entry` = 48852;
UPDATE `creature_template` SET  `ScriptName` =  'npc_squall_line' WHERE `entry` = 47034;

REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `data24`, `data25`, `data26`, `data27`, `data28`, `data29`, `data30`, `data31`, `unkInt32`, `AIName`, `ScriptName`, `WDBVerified`) VALUES
('206699', '14', '10135', 'Doodad_Skywall_Djinn_Healing01', '', '', '', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '1'),
('206700', '14', '10136', 'Doodad_Skywall_Djinn_Frost01', '', '', '', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '1'),
('206701', '14', '10137', 'Doodad_Skywall_Djinn_Tornado01', '', '', '', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '1'),
('207737', '33', '10369', 'Skywall Raid Center Platform', '', '', '', '0', '32', '1', '0', '0', '0', '0', '0', '0', '0', '0', '36', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '94', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '1'),
('207891', '3', '10401', 'Heart of Wind', '', '', '', '0', '0', '5', '0', '0', '0', '0', '0', '0', '57', '207891', '0', '1', '0', '0', '0', '0', '0', '0', '1', '1', '1', '0', '0', '1', '0', '0', '0', '0', '85', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '1'),
('207892', '3', '10401', 'Heart of Wind', '', '', '', '0', '0', '5', '0', '0', '0', '0', '0', '0', '57', '0', '0', '1', '0', '0', '0', '0', '0', '0', '1', '1', '1', '0', '0', '1', '0', '0', '0', '0', '85', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '15595'),
('207922', '1', '10393', 'Doodad_Skywall_Wind_DraftEffect_Center01', '', '', '', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '1'),
('207923', '1', '10394', 'Doodad_Skywall_Wind_DraftEffect_01', '', '', '', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '1'),
('207924', '1', '10394', 'Doodad_Skywall_Wind_DraftEffect_02', '', '', '', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '1'),
('207925', '1', '10394', 'Doodad_Skywall_Wind_DraftEffect_03', '', '', '', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '1'),
('207926', '1', '10394', 'Doodad_Skywall_Wind_DraftEffect_04', '', '', '', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '1'),
('207927', '1', '10394', 'Doodad_Skywall_Wind_DraftEffect_07', '', '', '', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '1'),
('207928', '1', '10394', 'Doodad_Skywall_Wind_DraftEffect_08', '', '', '', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '1'),
('207929', '1', '10394', 'Doodad_Skywall_Wind_DraftEffect_05', '', '', '', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '1'),
('207930', '1', '10394', 'Doodad_Skywall_Wind_DraftEffect_06', '', '', '', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '1');
