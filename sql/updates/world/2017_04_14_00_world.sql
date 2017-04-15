
delete from vehicle_template_accessory where entry=42839;
INSERT INTO `vehicle_template_accessory` (`entry`,`accessory_entry`,`seat_id`,`minion`,`description`,`summontype`,`summontimer`) VALUES 
(42839,42494,0,1,'Crushcog Vehicle Event.',5,0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry`=42839;
INSERT INTO `npc_spellclick_spells` (`npc_entry`,`spell_id`,`cast_flags`,`user_type`) VALUES (42839,86319,1,0);

DELETE FROM `gossip_menu_option` WHERE `menu_id`=11662;
INSERT INTO `gossip_menu_option` (`menu_id`,`id`,`option_icon`,`option_text`,`OptionBroadcastTextID`,`option_id`,`npc_option_npcflag`,`action_menu_id`,`action_poi_id`,`action_script_id`,`box_coded`,`box_money`,`box_text`,`BoxBroadcastTextID`) VALUES (11662,0,0,'I\'m ready to start the assault.',42755,1,1,0,0,0,0,0,NULL,0);

UPDATE `creature_template` set `gossip_menu_id`=11662,`npcflag`=1 WHERE `entry`=42849;
UPDATE `creature_template` set `InhabitType`=4 WHERE `entry`=42494;

-- Summoned creature so no need spawn
DELETE FROM `creature` WHERE `guid`=11536 AND `id`=42494;

DELETE FROM `creature_text` WHERE `entry` IN(42852,42849,42839);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`,`BroadcastTextID`) VALUES 
(42839,0,0,'You! How did you escape detection by my sentry-bots?',12,0,100,0,0,21243,'Razlo Crushcog',42761),
(42839,1,0,'No matter! My guardians and I will make short work of you. To arms, men!',12,0,100,0,0,21244,'Razlo Crushcog',42762),
(42839,2,0,'You will never defeat the true sons of Gnomeregan!',12,0,100,0,0,21245,'Razlo Crushcog',42781),
(42849,0,0,'Mekgineer Thermaplugg refuses to acknowledge that his defeat is imminent! He has sent Razlo Crushcog to prevent us from rebuilding our beloved Gnomeregan!',12,0,100,0,0,20890,'Tinker Mekkatorque',42758),
(42849,1,0,'But $N has thwarted his plans at every turn, and the dwarves of Ironforge stand with us!',12,0,100,0,0,20891,'Tinker Mekkatorque',42759),
(42849,2,0,'Let\'s send him crawling back to his master in defeat!',12,0,100,0,0,20892,'Tinker Mekkatorque',42760),
(42849,3,0,'We\'ve done it! We\'re victorious!',12,0,100,0,0,20893,'Tinker Mekkatorque',42765),
(42849,4,0,'With Crushcog defeated, Thermaplugg is sure to be quaking in his mechano-tank, and rightly so. You\'re next Thermaplugg. You\'re next!',12,0,100,0,0,20894,'Tinker Mekkatorque',42765),
(42849,5,0,'Mekkatorque-Missiles!',41,0,100,0,0,17562,'Tinker Mekkatorque',42833),
(42849,6,0,'Mekkatorque-Cannon!',41,0,100,0,0,17561,'Tinker Mekkatorque',42829),
(42849,7,0,'Mekkatorque-Ray!',41,0,100,0,0,17563,'Tinker Mekkatorque',42832),
(42849,8,0,'Mekkatorque-Beam!',41,0,100,0,0,17560,'Tinker Mekkatorque',42834),
(42852,0,0,'Aye, let\'s teach this addle-brained gnome a lesson!',12,0,100,0,0,0,'Mountaineer Stonegrind',42767),
(42852,1,0,'That\'ll teach you to mess with the might of Ironforge and Gnomeregan!',12,0,100,0,0,0,'Mountaineer Stonegrind',42766);


