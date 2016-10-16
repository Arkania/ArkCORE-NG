
delete from linked_respawn where guid=254315;

delete from gossip_menu where entry=10551;
insert into gossip_menu values 
(10551, 14598);

UPDATE creature_template SET gossip_menu_id=10551 WHERE entry=35780;

delete from gossip_menu where entry=10553;
insert into gossip_menu values 
(10553, 14809);

UPDATE creature_template SET gossip_menu_id=10553 WHERE entry=35805;

delete from npc_text where ID=14598;
insert into npc_text (ID, text0_0, prob0, em0_1, BroadcastTextID0) values 
(14598, "I don't know about you, $N, but I for one do not intend to be marooned on this island forever!$B$BIf only I'd stayed at the academy and learned how to use teleport magic....", 1, 1, 34952);

UPDATE creature_template SET gossip_menu_id=10552 WHERE entry=35786;

UPDATE npc_text SET BroadcastTextID0=34953 WHERE ID=14599;

UPDATE npc_text SET BroadcastTextID0=36453 WHERE ID=14981;

DELETE FROM gossip_menu WHERE entry=10805 and text_id=14981;
INSERT INTO gossip_menu VALUES (10805, 14981);

UPDATE creature_template SET gossip_menu_id=10805 WHERE entry=36496;

UPDATE gossip_menu_option SET OptionBroadcastTextID=2822, option_id=8, npc_option_npcflag=65536 WHERE menu_id=10805 AND id=0;

UPDATE gossip_menu_option SET OptionBroadcastTextID=4308, option_id=8, npc_option_npcflag=65536 WHERE menu_id=10805 AND id=1;

UPDATE creature_template SET gossip_menu_id=10549, dynamicflags=0 WHERE entry=35758;

DELETE FROM gossip_menu WHERE entry=11074 and text_id=15401;
INSERT INTO gossip_menu VALUES (11074, 15401);

UPDATE npc_text SET BroadcastTextID0=38605 WHERE ID=15401;

UPDATE creature_template SET gossip_menu_id=10554 WHERE entry=35806;

UPDATE creature_template SET gossip_menu_id=10554, dynamicflags=0 WHERE entry=35806;

UPDATE npc_text SET BroadcastTextID0=34957 WHERE ID=14603;

DELETE FROM gossip_menu WHERE entry=10554 and text_id=14603;
INSERT INTO gossip_menu VALUES (10554, 14603);

UPDATE creature_template SET gossip_menu_id=10555, dynamicflags=0 WHERE entry=35807;

DELETE FROM gossip_menu WHERE entry=10555 and text_id=14605;
INSERT INTO gossip_menu VALUES (10555, 14605);

UPDATE npc_text SET BroadcastTextID0=34959 WHERE ID=14605;

UPDATE creature_template SET gossip_menu_id=10550, dynamicflags=0 WHERE entry=35778;

DELETE FROM gossip_menu WHERE entry=10550 and text_id=14802;
INSERT INTO gossip_menu VALUES (10550, 14802);

UPDATE npc_text SET BroadcastTextID0=35974 WHERE ID=14802;

UPDATE creature_template SET dynamicflags=0 WHERE entry=35786;

UPDATE gossip_menu_option SET OptionBroadcastTextID=7658, npc_option_npcflag=51 WHERE menu_id=10552 AND id=0;

UPDATE gossip_menu_option SET option_id=5 WHERE menu_id=10552 AND id=0;

UPDATE creature_template SET dynamicflags=0 WHERE entry=35805;
