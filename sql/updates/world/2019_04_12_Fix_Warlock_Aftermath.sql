DELETE FROM `spell_script_names` WHERE `spell_id`=42223 AND `ScriptName`='spell_warl_rain_of_fire';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (42223, 'spell_warl_rain_of_fire');

DELETE FROM `spell_proc_event` WHERE `entry`=-85113;
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES (-85113, 0, 5, 0, 8388608, 0, 0, 0, 0, 0, 0);
