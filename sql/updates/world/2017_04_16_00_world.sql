
-- Misc fixes for Tinker Town
UPDATE `creature_template` SET `minlevel`=3,`maxlevel`=4 WHERE `entry`=43230;
UPDATE `creature_template` SET `minlevel`=3,`maxlevel`=4 WHERE `entry`=42223;
UPDATE `creature_template_addon` SET `emote`=214 WHERE `entry`=43230;
UPDATE `creature_equip_template` SET `itemEntry1`=49711,`itemEntry2`=0,`itemEntry3`=0 WHERE `entry`=43230;

