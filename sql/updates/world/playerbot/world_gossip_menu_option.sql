
SET @ID = 56100;
delete from gossip_menu_option where menu_id=@ID;
insert into gossip_menu_option (menu_id, id, option_icon, option_text) values
(@ID, 0, 9, "Recruit a Minion"),
(@ID, 1, 9, "Abandon my Minion"),
(@ID, 2, 3, "Help"),
(@ID, 3, 9, "Remove all"),
(@ID, 4, 7, "Menu back"),
(@ID, 5, 7, "No more bots available"),
(@ID, 6, 7, "Bot available"),
(@ID, 7, 7, "Bots available"),
(@ID, 8, 7, "More bot available"),
(@ID, 9, 7, "More bots available"),
(@ID, 10, 9, "Recruit a Warrior"),
(@ID, 11, 9, "Recruit a Hunter"),
(@ID, 12, 9, "Recruit a Paladin"),
(@ID, 13, 9, "Recruit a Shaman"),
(@ID, 14, 9, "Recruit a Rogue"),
(@ID, 15, 9, "Recruit a Druid"),
(@ID, 16, 9, "Recruit a Mage"),
(@ID, 17, 9, "Recruit a Priest"),
(@ID, 18, 9, "Recruit a Warlock"),
(@ID, 19, 9, "Recruit a Death Knight");