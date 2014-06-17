-- Item - Priest T11 Healer 4P Bonus
DELETE FROM `spell_proc_event` WHERE `entry` = 89911;
INSERT INTO `spell_proc_event` (`entry`, `SpellFamilyName`, `SpellFamilyMask2`, `procFlags`, `CustomChance`) VALUES
(89911, 6, 65536, 16384, 100);

-- Item - Priest T12 Healer 2P Bonus
DELETE FROM `spell_proc_event` WHERE `entry` = 99134;
INSERT INTO `spell_proc_event` (`entry`, `SpellFamilyName`, `SpellFamilyMask1`, `SpellFamilyMask2`) VALUES
(99134, 6, 2048+4096+1024, 32);