-- NPC script linking for Wyrmrest Defender ID: 27629
UPDATE `creature_template` SET `ScriptName`='npc_wyrmrest_defender' WHERE `entry`=27629;

-- Spell script name linking
DELETE FROM `spell_script_names` WHERE `spell_id` IN (49213,49370);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(49213,'spell_q12372_cast_from_gossip_trigger'),
(49370,'spell_q12372_destabilize_azure_dragonshrine_dummy');

-- DB/Achievements: Fix achievements Koralon the Flame Watcher / Toravon the Ice Watcher
DELETE FROM `achievement_criteria_data` WHERE `criteria_id` IN (11478,11479,12827,12828);
INSERT INTO `achievement_criteria_data` (`criteria_id`, `type`, `value1`, `value2`, `ScriptName`) VALUES
(11478, 12, 0, 0, ''),
(11479, 12, 1, 0, ''),
(12827, 12, 0, 0, ''),
(12828, 12, 1, 0, '');
