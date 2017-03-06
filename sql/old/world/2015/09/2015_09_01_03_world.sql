
-- this action menu is not avaible
delete from gossip_menu_option where action_menu_id=1221;

-- unknown gossip_menu_option entry
DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=3461 AND SourceEntry=0;

delete from gossip_menu_option where  menu_id=0 and id=18;
insert into gossip_menu_option values 
(0, 18, 0, "Trick or Treat!", 10693, 1, 1, 0, 0, 0, 0, 0, "Helloween event", 0);

