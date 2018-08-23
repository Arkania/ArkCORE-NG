
-- npc 26211 Earthen Ring Elder 
DELETE FROM creature_queststarter WHERE id=26221;
INSERT INTO creature_queststarter 
(id, quest)
VALUES
(26221, 11886),
(26221, 11917),
(26221, 11947),
(26221, 11948),
(26221, 11952),
(26221, 11953),
(26221, 11954),
(26221, 11955);

DELETE FROM creature_questender WHERE id=26221;
INSERT INTO creature_questender 
(id, quest)
VALUES
(26221, 9313),
(26221, 11917),
(26221, 11947),
(26221, 11948),
(26221, 11952),
(26221, 11953),
(26221, 11954),
(26221, 12012),
(26221, 29092);

DELETE FROM gossip_menu WHERE entry=9157;
INSERT INTO gossip_menu 
(entry, text_id)
VALUES
(9157, 12390);

DELETE FROM gossip_menu_option WHERE menu_id=9157;
INSERT INTO gossip_menu_option 
(menu_id, id, option_icon, option_text, OptionBroadcastTextID, option_id, npc_option_npcflag, action_menu_id, action_poi_id, action_script_id, box_coded, box_money, box_text, BoxBroadcastTextID)
VALUES
(9157, 0, 0, "I've lost my totemic beacon - may I have another?", 25742, 1, 1, 0, 0, 0, 0, 0, "", 0),
(9157, 1, 20, "Queue for The Frost Lord Ahune battle.", 40425, 0, 1, 0, 0, 0, 0, 0, "", 0);

