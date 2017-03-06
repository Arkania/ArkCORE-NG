

-- Acidic Venom Sac should not drop from Darkfang Creeper (by Exodius)
DELETE FROM `creature_loot_template` WHERE `entry`=4412 AND `item`=5959;

-- Add Pristine Owl Feather to the loot template of Tawny Owl  
-- Drop chance: Guaranteed - http://eu.battle.net/wow/en/item/64317  
update creature_loot_template set Chance=100 where entry=46162 and item=64317;

-- Trouble at the Docks, quest removed after Cataclysm (by Exodius)  
 DELETE FROM `disables` WHERE `sourceType`=1 AND `entry`=959;  
 INSERT INTO `disables` (`sourceType`,`entry`,`flags`,`params_0`,`params_1`,`comment`) VALUES  
 (1,959,0,0,0,'Quest: Trouble at the Docks, Removed after Cataclysm launch');  
 DELETE FROM `creature_queststarter` WHERE `quest`=959;  
 DELETE FROM `creature_questender` WHERE `quest`=959;   

 -- More Resource Crates, obsolete after Cata (by Noxious)  
 -- Cut Arathor Supply Lines, obsolete after Cata (by Noxious)  
 DELETE FROM `disables` WHERE `sourceType`=1 AND `entry` IN (8165, 8162);  
 INSERT INTO `disables` (`sourceType`,`entry`,`flags`,`params_0`,`params_1`,`comment`) VALUES  
 (1,8165,0,0,0,'Quest: More Resource Crates, Disabled in 4.0.1'),  
 (1,8162,0,0,0,'Quest: Cut Arathor Supply Lines, Disabled in 4.0.1');  
 DELETE FROM `creature_queststarter` WHERE `quest` IN (8165, 8162);  
 DELETE FROM `creature_questender` WHERE `quest` IN (8165, 8162);  

 -- More Resource Crates, obsolete after Cata (by Noxious)  
 -- Cut Arathor Supply Lines, obsolete after Cata (by Noxious)  
 DELETE FROM `disables` WHERE `sourceType`=1 AND `entry` IN (8165, 8162);  
 INSERT INTO `disables` (`sourceType`,`entry`,`flags`,`params_0`,`params_1`,`comment`) VALUES  
 (1,8165,0,0,0,'Quest: More Resource Crates, Disabled in 4.0.1'),  
 (1,8162,0,0,0,'Quest: Cut Arathor Supply Lines, Disabled in 4.0.1');  
 DELETE FROM `creature_queststarter` WHERE `quest` IN (8165, 8162);  
 DELETE FROM `creature_questender` WHERE `quest` IN (8165, 8162);  

