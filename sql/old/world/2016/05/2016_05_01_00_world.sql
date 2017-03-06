
-- fix quest 29434
update creature_template set gossip_menu_id=13019 where entry=54605;

delete from gossip_menu where entry=13019;
insert into gossip_menu values
(13019, 18290);

delete from gossip_menu_option where menu_id=13019;
insert into gossip_menu_option values
(13019, 0, 0, 'How do I play the Tonk Challenge?', 53321, 1, 1, 13066, 0, 0, 0, 0, '', 0),
(13019, 1, 0, 'Ready to play! |cFF0008E8(Darkmoon Game Token)|r', 53060, 1, 1, 0, 0, 0, 0, 0, '', 0);

delete from gossip_menu_option where menu_id=13066;
insert into gossip_menu_option values
(13066, 0, 0, 'I understand.', 53318, 1, 1, 13019, 0, 0, 0, 0, '', 0);

-- fix quest 29443
delete from creature_queststarter where id=14847 and quest=29443;

-- Professor Thaddeus Paleo
SET @ENTRY := 14847;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,0,0,20000,30000,1,0,0,0,0,0,0,17,4,20,0,0.0,0.0,0.0,0.0,"talk to player");

UPDATE locales_quest SET OfferRewardText_loc3="Wo habt Ihr den her?$B$BSolche Kristalle sind sehr selten, viele Sammler suchen danach. Ich würde diesen gern untersuchen und auf dem Jahrmarkt ausstellen. Würdet Ihr ihn gegen eine großzügige Anzahl von Losen des Dunkelmond-Jahrmarkts eintauschen?", RequestItemsText_loc3="Was habt Ihr denn da?" WHERE Id=29443;

delete from creature_loot_template where entry=43875 and item=71635;
insert into creature_loot_template values 
(43875, 71635, 0, 1.36, 1, 1, 1, 1, 1, "starting quest 29443");

-- fix quest 29446
delete from creature_queststarter where id=14847 and quest=29446;

UPDATE locales_quest SET OfferRewardText_loc3="Wo habt Ihr eine solch wundervolle Klinge gefunden?$B$BWas für eine Verarbeitung! Das ist wahrlich eine Waffe, mit der sich jeder Held schmücken könnte. Ich würde sie sehr gern ausstellen.$B$BWürdet Ihr eine großzügige Anzahl Lose des Dunkelmond-Jahrmarkts dafür annehmen?", RequestItemsText_loc3="Was habt Ihr denn da?" WHERE Id=29446;

delete from creature_loot_template where item=71638;
insert into creature_loot_template values 
(54968, 71638, 0, 12, 1, 1, 0, 1, 1, ""),
(61398, 71638, 0, 5, 1, 1, 0, 1, 1, ""),
(29308, 71638, 0, 2, 1, 1, 0, 1, 1, ""),
(29306, 71638, 0, 2, 1, 1, 0, 1, 1, ""),
(27975, 71638, 0, 2, 1, 1, 0, 1, 1, ""),
(46383, 71638, 0, 2, 1, 1, 0, 1, 1, ""),
( 2748, 71638, 0, 2, 1, 1, 0, 1, 1, ""),
(74462, 71638, 0, 2, 1, 1, 0, 1, 1, ""),
(12236, 71638, 0, 1.9, 1, 1, 0, 1, 1, ""),
( 9568, 71638, 0, 1.9, 1, 1, 0, 1, 1, ""),
(11486, 71638, 0, 1.8, 1, 1, 0, 1, 1, ""),
( 7800, 71638, 0, 1.6, 1, 1, 0, 1, 1, ""),
(39698, 71638, 0, 1.5, 1, 1, 0, 1, 1, ""),
(11501, 71638, 0, 1.4, 1, 1, 0, 1, 1, ""),
(58632, 71638, 0, 1.3, 1, 1, 0, 1, 1, ""),
(40177, 71638, 0, 1.1, 1, 1, 0, 1, 1, ""),
(45412, 71638, 0, 1.1, 1, 1, 0, 1, 1, ""),
(59223, 71638, 0, 1.1, 1, 1, 0, 1, 1, ""),
(44577, 71638, 0, 0.9, 1, 1, 0, 1, 1, ""),
(54432, 71638, 0, 0.74, 1, 1, 0, 1, 1, ""),
(17798, 71638, 0, 0.5, 1, 1, 0, 1, 1, ""),
(18473, 71638, 0, 0.4, 1, 1, 0, 1, 1, ""),
(16808, 71638, 0, 0.4, 1, 1, 0, 1, 1, ""),
(47626, 71638, 0, 0.3, 1, 1, 0, 1, 1, ""),
(35451, 71638, 0, 0.3, 1, 1, 0, 1, 1, "");

delete from gameobject_loot_template where item=71638;
insert into gameobject_loot_template values 
(142184, 71638, 0, 0.3, 1, 1, 0, 1, 1, ""),
(201710, 71638, 0, 0.3, 1, 1, 0, 1, 1, ""),
(202212, 71638, 0, 1.2, 1, 1, 0, 1, 1, ""),
(209541, 71638, 0, 0.3, 1, 1, 0, 1, 1, ""),
(209547, 71638, 0, 0.3, 1, 1, 0, 1, 1, "");

-- fix quest 29507
delete from creature_queststarter where id=14847 and quest=29507;

-- fix quest 29436
UPDATE quest_template SET Level=1 WHERE Id=29436;




















