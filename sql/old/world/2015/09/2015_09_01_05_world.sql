
delete from gossip_menu_option where id=0 and menu_id in (2890, 6059, 7324, 7856, 7857, 9123, 21215);

delete from gossip_menu_option where id=1 and menu_id in (347);

delete from gossip_menu_option where id=2 and menu_id in (7301, 7497, 7855, 7857, 7869, 9112, 9614);

delete from gossip_menu_option where id=3 and menu_id in (347, 7855, 7856);

delete from gossip_menu_option where id=4 and menu_id in (7301);

delete from gossip_menu_option where id=5 and menu_id in (7857);


replace into conditions values
(15, 0, 18, 0, 0, 12, 0, 12, 0, 0, 0, 0, 0, "", "Trick or Treat!");

delete from conditions where SourceTypeOrReferenceId=15 and ConditionTypeOrReference=12 and ConditionValue1=12 and SourceEntry<>18;

update gossip_menu_option set npc_option_npcflag=65536 where menu_id=0 and id=18;

