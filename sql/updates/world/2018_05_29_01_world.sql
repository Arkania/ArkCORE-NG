
UPDATE gossip_menu_option SET OptionBroadcastTextID=20232 WHERE menu_id=11778 AND id=1;

DELETE FROM locales_gossip_menu_option WHERE menu_id=11778 AND id=1;
INSERT INTO locales_gossip_menu_option 
(menu_id, id, option_text_loc1, option_text_loc2, option_text_loc3, option_text_loc4, option_text_loc5, option_text_loc6, option_text_loc7, option_text_loc8, box_text_loc1, box_text_loc2, box_text_loc3, box_text_loc4, box_text_loc5, box_text_loc6, box_text_loc7, box_text_loc8)
VALUES
(11778, 1, "", "", "Zeigt mir Eure Waren.", "", "", "", "", "", "", "", "", "", "", "", "", "");


