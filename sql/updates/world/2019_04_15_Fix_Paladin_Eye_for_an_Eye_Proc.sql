DELETE FROM `spell_script_names` WHERE `spell_id`=-9799 AND `ScriptName`='spell_pal_eye_for_an_eye';
DELETE FROM `spell_script_names` WHERE `spell_id`=25988 AND `ScriptName`='spell_pal_eye_for_an_eye';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (25988, 'spell_pal_eye_for_an_eye');
DELETE FROM `spell_script_names` WHERE `spell_id`=9799 AND `ScriptName`='spell_pal_eye_for_an_eye';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (9799, 'spell_pal_eye_for_an_eye');
DELETE FROM `spell_proc_event` WHERE `entry`=-9799;
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES (-9799, 0, 0, 0, 0, 0, 131072, 0, 0, 0, 0);

