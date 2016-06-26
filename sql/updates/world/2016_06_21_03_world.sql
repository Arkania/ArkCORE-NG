
update gossip_menu_option set OptionBroadcastTextID=3409 where option_text="I need a ride.";

update gossip_menu_option set OptionBroadcastTextID=12271 where option_text="Show me where I can fly.";

update gossip_menu_option set OptionBroadcastTextID=53141, option_id=4, npc_option_npcflag=8192 where option_text="I'd like to travel by air.";

delete from gossip_menu_option where menu_id=9546 and id=2;

update gossip_menu_option set OptionBroadcastTextID=23112 where menu_id=9546 and id=1;

update gossip_menu_option set OptionBroadcastTextID=39131 where option_text="I'd like to purchase a bat ride.";

update gossip_menu_option set OptionBroadcastTextID=12085 where option_text="Yes, I'd like to purchase a ride down to the Ghostlands.";

update gossip_menu_option set OptionBroadcastTextID=14358 where option_text="I desire to travel by hippogryph.";

update gossip_menu_option set OptionBroadcastTextID=12082 where option_text="I'd like to fly back to Silvermoon City.";

update gossip_menu_option set OptionBroadcastTextID=7573, option_id=4, npc_option_npcflag=8192 where menu_id=4041 and id=0;

update gossip_menu_option set OptionBroadcastTextID=12804, option_id=4, npc_option_npcflag=8192 where menu_id=4042 and id=0;

