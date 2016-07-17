
-- GO shouldn't be selectable 
UPDATE `gameobject_template` SET `flags` = 20 WHERE `entry` = 195454;

-- Added name for GO
UPDATE `gameobject_template` SET `name` = 'Nefarian''s Throne' WHERE `entry` = 202832;

-- level must be 85,86
UPDATE `creature_template` SET `minlevel` = 85, `maxlevel` = 85 WHERE `entry` = 48973;
UPDATE `creature_template` SET `minlevel` = 85, `maxlevel` = 85 WHERE `entry` = 49126;
UPDATE `creature_template` SET `minlevel` = 85, `maxlevel` = 85 WHERE `entry` = 49155;
UPDATE `creature_template` SET `minlevel` = 85, `maxlevel` = 85 WHERE `entry` = 49174;
UPDATE `creature_template` SET `minlevel` = 86, `maxlevel` = 86 WHERE `entry` = 49186;
UPDATE `creature_template` SET `minlevel` = 85, `maxlevel` = 85 WHERE `entry` = 39369;
UPDATE `creature_template` SET `minlevel` = 85, `maxlevel` = 85 WHERE `entry` = 39370;
UPDATE `creature_template` SET `minlevel` = 85, `maxlevel` = 85 WHERE `entry` = 46272;
UPDATE `creature_template` SET `minlevel` = 85, `maxlevel` = 85 WHERE `entry` = 46386;

-- hp and mana fix
UPDATE `creature_template` SET `Health_mod` = 1, `Mana_mod` = 1 WHERE `entry` = 38022;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 46590;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 46153;
UPDATE `creature_template` SET `unit_flags2` = 2048, `Health_mod` = 1, `Mana_mod` = 1 WHERE `entry` = 47796;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 46831;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 46838;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 44011;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 46971;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 46162;
UPDATE `creature_template` SET `Mana_mod` = 1 WHERE `entry` = 45795;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 46203;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 46416;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 46328;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 46329;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 46202;
UPDATE `creature_template` SET `Mana_mod` = 1 WHERE `entry` = 46243;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 50314;
UPDATE `creature_template` SET `exp` = 2 WHERE `entry` = 39644;
UPDATE `creature_template` SET `Mana_mod` = 2 WHERE `entry` = 43547;
UPDATE `creature_template` SET `Mana_mod` = 2 WHERE `entry` = 39846;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 39941;
UPDATE `creature_template` SET `Health_mod` = 0.5 WHERE `entry` = 40557;
UPDATE `creature_template` SET `Mana_mod` = 2 WHERE `entry` = 41029;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 48724;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 39419;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 39664;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 40889;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 39418;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 41644;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 41593;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 42113;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 42115;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 40372;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 41477;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 41038;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 41037;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 40276;
UPDATE `creature_template` SET `Health_mod` = 2 WHERE `entry` = 39964;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 39948;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 39918;
UPDATE `creature_template` SET `Health_mod` = 1 WHERE `entry` = 40282;
UPDATE `creature_template` SET `minlevel` = 80, `maxlevel` = 80, `Health_mod` = 1 WHERE `entry` = 39663;

-- level must be 12
UPDATE `creature_template` SET `minlevel` = 12, `maxlevel` = 12 WHERE `entry` = 37927;


