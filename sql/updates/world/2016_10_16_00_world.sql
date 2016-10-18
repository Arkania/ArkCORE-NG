
DELETE FROM gossip_menu WHERE entry=10554 and text_id=14604;
INSERT INTO gossip_menu VALUES (10554, 14604);

UPDATE npc_text SET BroadcastTextID0=34958 WHERE ID=14604;

