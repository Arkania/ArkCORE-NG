
-- QUEST_BY_HOOK_OR_BY_CROOK = 13963,
update creature_template set gossip_menu_id=0, AIName="", Scriptname="npc_togrik_34513" where entry=34513;
update creature_template set gossip_menu_id=0, AIName="", Scriptname="npc_captured_razormane_34523" where entry=34523;

delete from gossip_menu where entry in (10520, 10521);
insert into gossip_menu values 
(10520, 14554),
(10521, 14555);

delete from waypoint_data where id=3452301;
insert into waypoint_data (id, point, position_x, position_y, position_z, delay, move_flag) values 
(3452301, 0, 286.755,  -3048.261, 95.91666, 0, 0),
(3452301, 1, 283.4774, -3050.653, 95.93713, 0, 0),
(3452301, 2, 281.25,   -3052.084, 95.91666, 0, 0),
(3452301, 3, 284.7971, -3052.265, 95.91666, 0, 0),
(3452301, 4, 280.9629, -3051.658, 96.00211, 0, 0);

-- Dave's Industrial Light and Magic Bunny (Small)	
delete from creature where guid=91042;
insert into creature values 
(91042, 34527, 1, 1, 1, 27823, 0, 288.58, -3055.996, 99.0182, 3.36848, 500, 0, 0, 42, 0, 0, 0, 0, 0);

UPDATE quest_template SET QuestGiverPortrait=4745, QuestGiverTextWindow="Razormane Prisoner", QuestGiverTargetName="Razormane Prisoner" WHERE Id=13963;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Sprecht mit Togrik auf Grol'doms Hof im Nördlichen Brachland.", QuestGiverTextWindow_loc3="Gefangener der Klingenmähne", QuestGiverTargetName_loc3="Gefangener der Klingenmähne" WHERE Id=13963;

update gossip_menu_option set OptionBroadcastTextID=34716, option_id=1, npc_option_npcflag=1 where menu_id=10521 and id=0;
update gossip_menu_option set OptionBroadcastTextID=34717, option_id=1, npc_option_npcflag=1 where menu_id=10521 and id=1;
update gossip_menu_option set OptionBroadcastTextID=34718, option_id=1, npc_option_npcflag=1 where menu_id=10521 and id=2;
update gossip_menu_option set OptionBroadcastTextID=34719, option_id=1, npc_option_npcflag=1 where menu_id=10521 and id=3;
update gossip_menu_option set OptionBroadcastTextID=34720, option_id=1, npc_option_npcflag=1 where menu_id=10521 and id=4;

update npc_text set BroadcastTextID1=34711, BroadcastTextID2=34712, BroadcastTextID3=34713 where ID=14555;

delete from gossip_menu_option where menu_id=10520 and id=0;
insert into gossip_menu_option values 
(10520, 0, 0, "Togrik, can you wake up the prisoner again?", 34709, 1, 1, 0, 0, 0, 0, 0, "", 0);

 update creature_template set AIName="", Scriptname="npc_groldom_kodo_34547" where entry=34547;
 
delete from creature where guid in (116374, 85302, 85295, 85380, 85279, 138055, 138318, 85294, 85304, 138692, 85287, 85361, 85288, 85356, 138437);
delete from creature where guid in (138298, 85291, 85359, 85298, 85296, 85370, 138625, 85371, 85368,  85369, 85299, 85364, 115995, 138527);

delete from creature_addon where guid in (116374, 85302, 85295, 85380, 85279, 138055, 138318, 85294, 85304, 138692, 85287, 85361, 85288, 85356, 138437);
delete from creature_addon where guid in (138298, 85291, 85359, 85298, 85296, 85370, 138625, 85371, 85368,  85369, 85299, 85364, 115995, 138527);

