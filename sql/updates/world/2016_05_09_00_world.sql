
delete from gameobject where guid=15010 and id=301114;
INSERT INTO `gameobject` VALUES (15010, 301114, 974, 1, 1, -4290.83, 6305.34, 13.1171, 1.14273, 0, 0, 0.54078, 0.841164, 300, 0, 1);

delete from gameobject where guid=15011 and id=301115;
INSERT INTO `gameobject` VALUES (15011, 301115, 974, 1, 1, -3992.9, 6284.81, 13.1162, 3.872, 0, 0, 0.934051, -0.357139, 300, 0, 1);

delete from gameobject where guid=15012 and id=301116;
INSERT INTO `gameobject` VALUES (15012, 301116, 974, 1, 1, -4129.88, 6319.96, 13.1169, 1.11131, 0, 0, 0.527501, 0.849554, 300, 0, 1);

DELETE FROM gossip_menu_option where menu_id=13075;
INSERT INTO gossip_menu_option VALUES 
(13075, 0, 0, "Darkmoon Adventurer's Guide?", 53755, 1, 1, 0, 0, 0, 0, 0, "", 0),
(13075, 1, 0, "What can I purchase?", 10773, 1, 1, 6577, 0, 0, 0, 0, "", 0),
(13075, 2, 0, "Darkmoon Faire Prize Tickets?", 10775, 1, 1, 6578, 0, 0, 0, 0, "", 0),
(13075, 3, 0, "Darkmoon Cards?", 10777, 1, 1, 6579, 0, 0, 0, 0, "", 0),
(13075, 4, 0, "Attractions?", 10779, 1, 1, 6581, 0, 0, 0, 0, "", 0);

UPDATE npc_text SET BroadcastTextID0=10774 WHERE ID=7793;

UPDATE npc_text SET BroadcastTextID0=10776 WHERE ID=7794;

UPDATE npc_text SET BroadcastTextID0=22527 WHERE ID=11472;

DELETE FROM gossip_menu_option where menu_id=6579  and id=0;
DELETE FROM gossip_menu_option where menu_id=13083  and id=0;
INSERT INTO gossip_menu_option VALUES 
(6579, 0, 0, "<more>", 17471, 1, 1, 8848, 0, 0, 0, 0, "", 0),
(13083, 0, 0, "<more>", 17471, 1, 1, 0, 0, 0, 0, 0, "", 0);

UPDATE npc_text SET BroadcastTextID0=10770 WHERE ID=7790;

UPDATE npc_text SET BroadcastTextID0=10768 WHERE ID=7789;



