DELETE FROM `spell_script_names` WHERE `spell_id`=54158 AND `ScriptName`='spell_pal_judgement_54158';
DELETE FROM `spell_script_names` WHERE `spell_id`=20271 AND `ScriptName`='spell_pal_judgement_20271';
DELETE FROM `spell_script_names` WHERE `spell_id`=89906 AND `ScriptName`='spell_pal_judgements_of_the_bold';
DELETE FROM `spell_script_names` WHERE `spell_id`=54158 AND `ScriptName`='spell_pal_judgement_damage';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (54158, 'spell_pal_judgement_damage');
DELETE FROM `spell_script_names` WHERE `spell_id`=20271 AND `ScriptName`='spell_pal_judgement';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (20271, 'spell_pal_judgement');
DELETE FROM `spell_proc_event` WHERE `entry`=-87168;
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES (-87168, 0, 10, 8388608, 0, 0, 272, 0, 0, 100, 0);



