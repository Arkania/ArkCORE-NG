

delete from achievement_criteria_data where type=6 and criteria_id between 11134 and 11141;

delete from gossip_menu_option where menu_id=10389 and id in (0, 1, 2, 3, 15);

INSERT INTO `gossip_menu_option` VALUES 
(10389, 0, 0, 'Teleport to the Expedition Base Camp.',  33919, 1, 1, 0, 0, 0, 0, 0, '', 0),
(10389, 1, 0, 'Teleport to the Formation Grounds.',     33920, 1, 1, 0, 0, 0, 0, 0, '', 0),
(10389, 3, 0, 'Teleport to the Colossal Forge.',        33921, 1, 1, 0, 0, 0, 0, 0, '', 0),
(10389, 15, 0, 'Teleport to the Prison of Yogg-Saron.', 33928, 1, 1, 0, 0, 0, 0, 0, '', 0);

update gossip_menu_option set npc_option_npcflag=1 where menu_id=10389;

UPDATE quest_template SET SpecialFlags=2 WHERE Id=11705;

UPDATE quest_template SET SpecialFlags=2 WHERE Id=11592;

