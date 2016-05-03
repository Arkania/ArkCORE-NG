
-- gossip for npc 54345
delete from gossip_menu_option where menu_id=13076;
INSERT INTO `gossip_menu_option` VALUES (13076, 0, 0, 'Tonks?', 11934, 1, 1, 13077, 0, 0, 0, 0, '', 0);
INSERT INTO `gossip_menu_option` VALUES (13076, 1, 0, 'Cannon?', 11936, 1, 1, 13078, 0, 0, 0, 0, '', 0);
INSERT INTO `gossip_menu_option` VALUES (13076, 2, 0, 'Whack-a-Gnoll?', 53403, 1, 1, 13079, 0, 0, 0, 0, '', 0);
INSERT INTO `gossip_menu_option` VALUES (13076, 3, 0, 'Ring Toss?', 53415, 1, 1, 13080, 0, 0, 0, 0, '', 0);
INSERT INTO `gossip_menu_option` VALUES (13076, 4, 0, 'Shooting Gallery?', 53417, 1, 1, 13081, 0, 0, 0, 0, '', 0);
INSERT INTO `gossip_menu_option` VALUES (13076, 5, 0, 'Fortune teller?', 53419, 1, 1, 13082, 0, 0, 0, 0, '', 0);

delete from gossip_menu_option where menu_id=13077;
INSERT INTO `gossip_menu_option` VALUES (13077, 0, 0, 'I understand.', 53318, 1, 1, 13076, 0, 0, 0, 0, '', 0);

delete from gossip_menu_option where menu_id=13078;
INSERT INTO `gossip_menu_option` VALUES (13078, 0, 0, 'I understand.', 53318, 1, 1, 13076, 0, 0, 0, 0, '', 0);

delete from gossip_menu_option where menu_id=13079;
INSERT INTO `gossip_menu_option` VALUES (13079, 0, 0, 'I understand.', 53318, 1, 1, 13076, 0, 0, 0, 0, '', 0);

delete from gossip_menu_option where menu_id=13080;
INSERT INTO `gossip_menu_option` VALUES (13080, 0, 0, 'I understand.', 53318, 1, 1, 13076, 0, 0, 0, 0, '', 0);

delete from gossip_menu_option where menu_id=13081;
INSERT INTO `gossip_menu_option` VALUES (13081, 0, 0, 'I understand.', 53318, 1, 1, 13076, 0, 0, 0, 0, '', 0);

delete from gossip_menu_option where menu_id=13082;
INSERT INTO `gossip_menu_option` VALUES (13082, 0, 0, 'I understand.', 53318, 1, 1, 13076, 0, 0, 0, 0, '', 0);

-- gossip for npc 54601
delete from gossip_menu_option where menu_id=13018;
INSERT INTO `gossip_menu_option` VALUES (13018, 0, 0, 'How do I play Whack-a-Gnoll?', 53320, 1, 1, 13065, 0, 0, 0, 0, '', 0);
INSERT INTO `gossip_menu_option` VALUES (13018, 1, 0, 'Ready to whack! |cFF0008E8(Darkmoon Game Token)|r', 53057, 1, 1, 0, 0, 0, 0, 0, '', 0);

delete from gossip_menu_option where menu_id=13065;
INSERT INTO `gossip_menu_option` VALUES (13065, 0, 0, 'I understand.', 53318, 1, 1, 13018, 0, 0, 0, 0, '', 0);

UPDATE quest_template SET Level=1 WHERE Id=29463;

update creature_template set gossip_menu_id=0, AIName="", Scriptname="npc_mola_54601" where entry=54601;

-- fix console errors
delete from creature_questender where id=14829 and quest=33354;
delete from creature_questender where id=14847 and quest in (30449, 30450, 30451, 30452);

delete from creature_loot_template where entry=56160 and item in (81194, 81212);
delete from creature_loot_template where entry=43875 and item=72635;

delete from creature_loot_template where entry in (48875, 54968, 55475, 56160, 58632, 59223, 61398, 74462);

delete from gameobject_loot_template where entry=142184;

delete from skinning_loot_template where entry=56160 and item in (72120, 72162);
delete from skinning_loot_template where entry in (14864, 14866, 14867, 14868);

-- npc 15303
update creature_template set gossip_menu_id=0, AIName="", Scriptname="npc_maxima_blastenheimer_15303" where entry=15303;

delete from creature_text where entry=15303;
INSERT INTO `creature_text` VALUES (15303, 0, 0, 'Cannon blast!  Who wants to get shot out of a cannon?', 12, 0, 100, 70, 0, 0, '', 53466);
INSERT INTO `creature_text` VALUES (15303, 0, 1, 'Step up to get blown up!', 12, 0, 100, 70, 0, 0, '', 53467);
INSERT INTO `creature_text` VALUES (15303, 0, 2, 'Don\'t worry about your weight, this cannon can handle any payload!', 12, 0, 100, 70, 0, 0, '', 53468);

-- gossip 6574 / 6575
delete from gossip_menu_option where menu_id=6574;
INSERT INTO `gossip_menu_option` VALUES (6574, 0, 0, 'I understand.', 53318, 1, 1, 0, 0, 0, 0, 0, '', 0);

delete from gossip_menu_option where menu_id=6575;
INSERT INTO `gossip_menu_option` VALUES (6575, 0, 0, 'How do I use the cannon?', 10769, 1, 1, 6574, 0, 0, 0, 0, NULL, 0);
INSERT INTO `gossip_menu_option` VALUES (6575, 1, 0, 'Launch me! |cFF0008E8(Darkmoon Game Token)|r', 53038, 1, 1, 0, 0, 0, 0, 0, '', 0);
INSERT INTO `gossip_menu_option` VALUES (6575, 2, 0, 'Launch me! |cFF0008E8(Darkmoon Game Token)|r', 53038, 1, 1, 0, 0, 0, 0, 0, '', 0);

-- gossip 13352
delete from gossip_menu_option where menu_id=13352;
INSERT INTO `gossip_menu_option` VALUES 
(13352, 0, 0, 'Teleport me to the cannon.', 56548, 1, 1, 0, 0, 0, 0, 25, 'Teleportation to the cannon will cost:', 56731),
(13352, 1, 0, 'Teleport me to the cannon.', 56548, 1, 1, 0, 0, 0, 0, 100, 'Teleportation to the cannon will cost:', 56731),
(13352, 2, 0, 'I don\'t need a teleport.', 56732, 1, 0, 0, 0, 0, 0, 0, '', 0);

update creature_template set gossip_menu_id=0, AIName="", Scriptname="npc_teleportologist_fozlebub_57850" where entry=57850;

-- http://wow.gamepedia.com/Copper_Modulator
-- Cataclysm Patch 4.3.0 (2011-11-29): Removed. All existing items changed to  [Broken Modulator].
delete from creature_queststarter where quest in (7894, 7895, 7896, 7897, 7898, 7942);


