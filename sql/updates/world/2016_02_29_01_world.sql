
-- fix issue #92
update gossip_menu_option set option_id=4, npc_option_npcflag=8192 where id=0 and menu_id=12428;
update gossip_menu_option set option_id=1, npc_option_npcflag=1 where id=2 and menu_id=12428;