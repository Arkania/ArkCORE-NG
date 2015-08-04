

UPDATE quest_template SET RequiredSourceItemId1=39418, RequiredSourceItemId2=39371, RequiredSourceItemId3=0, RequiredSourceItemId4=0, RequiredSourceItemCount1=1, RequiredSourceItemCount2=2, RequiredSourceItemCount3=0, RequiredSourceItemCount4=0 WHERE Id=12720;

UPDATE quest_template SET RequiredSourceItemId1=39647, RequiredSourceItemCount1=1, RequiredItemId1=0, RequiredItemCount1=0 WHERE Id=12755;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=12755;

delete from creature_addon where guid in (91573, 91042, 90845, 90562, 90455, 87987, 87970, 87877, 87610, 79876, 79794, 79598);

delete from linked_respawn where linkedGuid=145832;

update creature_template set lootid=57158 where entry in (57158, 57292);

update gossip_menu_option set id=0, OptionBroadcastTextID=31719 where menu_id=10028 and id=1;
delete from gossip_menu_option where menu_id=10028 and id in (2, 3, 4);

delete from gossip_menu_option where menu_id=7497 and id=1 and npc_option_npcflag=0;
update gossip_menu_option set id=1, OptionBroadcastTextID=3370 where menu_id=7497 and id=3;
update gossip_menu_option set id=2, OptionBroadcastTextID=10693 where menu_id=7497 and id=4;
update gossip_menu_option set OptionBroadcastTextID=2822 where menu_id=7497 and id=0;

delete from gossip_menu where entry=7931 and text_id=1915;

delete from `db_script_string` where entry in
(2000000114, 2000000115, 2000000122, 2000000123, 2000000248, 2000000292, 2000000293, 2000000299, 2000000466, 2000000603,
 2000000604, 2000005001, 2000005002, 2000005003, 2000005004, 2000005005, 2000005006, 2000005007, 2000005008, 2000005009,
 2000005010, 2000005011, 2000005015, 2000005016, 2000005017, 2000005018, 2000005019, 2000005020, 2000005021, 2000005022, 
 2000005023, 2000005024, 2000005025, 2000005026, 2000005027, 2000005028, 2000005029, 2000005030, 2000005031, 2000005032, 
 2000005033, 2000005034, 2000005035, 2000005036, 2000005037, 2000005038, 2000005039, 2000005040, 2000005041, 2000005042,
 2000005043, 2000005044, 2000005045, 2000005046, 2000005047, 2000005048, 2000005049, 2000005050, 2000005051, 2000005052,
 2000005053, 2000005054, 2000005055, 2000005056, 2000005057, 2000005058, 2000005059, 2000005060, 2000005061, 2000005062,
 2000005063, 2000005064, 2000005065, 2000005066, 2000005067, 2000005068, 2000005069, 2000005070, 2000005071, 2000005072,
 2000005073, 2000005074, 2000005075, 2000005076, 2000005077, 2000005078, 2000005079, 2000005080, 2000005081, 2000005082,
 2000005083, 2000005084, 2000005085, 2000005086, 2000005087, 2000005088, 2000005089, 2000005090, 2000005091, 2000005092,
 2000005093, 2000005094, 2000005095, 2000005096, 2000005097, 2000005098, 2000005099, 2000005100, 2000005101, 2000005102,
 2000005103, 2000005104, 2000005105, 2000005106, 2000005107, 2000005108, 2000005109, 2000005110, 2000005111, 2000005112,
 2000005113, 2000005114, 2000005115, 2000005116, 2000005117, 2000005118, 2000005119, 2000005120, 2000005121, 2000005122,
 2000005123, 2000005124, 2000005125, 2000005126, 2000005127, 2000005128, 2000005129, 2000005130, 2000005131, 2000005132,
 2000005133, 2000005134, 2000005135, 2000005136, 2000005137, 2000005138, 2000005139, 2000005140, 2000005141, 2000005142,
 2000005143, 2000005144, 2000005145, 2000005146, 2000005147, 2000005148, 2000005149, 2000005150, 2000005151, 2000005152,
 2000005153, 2000005154, 2000005155, 2000005156, 2000005157, 2000005158, 2000005159, 2000005160, 2000005161, 2000005162,
 2000005163, 2000005164, 2000005165, 2000005166, 2000005167, 2000005168, 2000005169, 2000005170, 2000005171, 2000005172,
 2000005173, 2000005174, 2000005175, 2000005176, 2000005177, 2000005178, 2000005179, 2000005180, 2000005181, 2000005182,
 2000005183, 2000005184, 2000005185, 2000005186, 2000005187, 2000005188, 2000005189, 2000005190, 2000005191, 2000005192,
 2000005193, 2000005194, 2000005195, 2000005196, 2000005197, 2000005198, 2000005199, 2000005200, 2000005201, 2000005202,
 2000005203, 2000005204, 2000005205, 2000005206, 2000005207, 2000005208, 2000005209, 2000005210, 2000005400, 2000005401,
 2000005402, 2000005403, 2000005404, 2000005405, 2000005406, 2000005407);

UPDATE locales_quest SET EndText_loc3="", QuestGiverTextWindow_loc3="Stellt Euch anderen Todesrittern zum Duell und ich hoffe Ihr überlebt.", QuestGiverTargetName_loc3="Todesritter Initiant" WHERE Id=12733;

UPDATE quest_template SET Method=2 WHERE Id=12711;
UPDATE quest_template SET RewardItemId1=39317, RewardItemCount1=1 WHERE Id=12711;

UPDATE quest_template SET Flags=130 WHERE Id=12687;

update creature_text set BroadcastTextID=28770 where entry=28577 and groupid=0 and id=0;
update creature_text set BroadcastTextID=28763 where entry=28577 and groupid=0 and id=1;
update creature_text set BroadcastTextID=28765 where entry=28577 and groupid=0 and id=2;
update creature_text set BroadcastTextID=28769 where entry=28577 and groupid=0 and id=3;
update creature_text set BroadcastTextID=29085 where entry=28577 and groupid=0 and id=4;
update creature_text set BroadcastTextID=29086 where entry=28577 and groupid=0 and id=5;
update creature_text set BroadcastTextID=29088 where entry=28577 and groupid=0 and id=6;
update creature_text set BroadcastTextID=28772 where entry=28577 and groupid=1 and id=0;
update creature_text set BroadcastTextID=28775 where entry=28577 and groupid=1 and id=1;
update creature_text set BroadcastTextID=28773 where entry=28577 and groupid=1 and id=2;
update creature_text set BroadcastTextID=28776 where entry=28577 and groupid=1 and id=3;
update creature_text set BroadcastTextID=28782 where entry=28577 and groupid=1 and id=4;
update creature_text set BroadcastTextID=28771 where entry=28577 and groupid=1 and id=5;
update creature_text set BroadcastTextID=28777 where entry=28577 and groupid=1 and id=6;
update creature_text set BroadcastTextID=28781 where entry=28577 and groupid=1 and id=7;
update creature_text set BroadcastTextID=28788 where entry=28577 and groupid=2 and id=0;
update creature_text set BroadcastTextID=28789 where entry=28577 and groupid=2 and id=1;
update creature_text set BroadcastTextID=28791 where entry=28577 and groupid=2 and id=2;
update creature_text set BroadcastTextID=28792 where entry=28577 and groupid=2 and id=3;

update creature_text set BroadcastTextID=28770 where entry=28576 and groupid=0 and id=0;
update creature_text set BroadcastTextID=28763 where entry=28576 and groupid=0 and id=1;
update creature_text set BroadcastTextID=28765 where entry=28576 and groupid=0 and id=2;
update creature_text set BroadcastTextID=28769 where entry=28576 and groupid=0 and id=3;
update creature_text set BroadcastTextID=29085 where entry=28576 and groupid=0 and id=4;
update creature_text set BroadcastTextID=29086 where entry=28576 and groupid=0 and id=5;
update creature_text set BroadcastTextID=29088 where entry=28576 and groupid=0 and id=6;
update creature_text set BroadcastTextID=28772 where entry=28576 and groupid=1 and id=0;
update creature_text set BroadcastTextID=28775 where entry=28576 and groupid=1 and id=1;
update creature_text set BroadcastTextID=28773 where entry=28576 and groupid=1 and id=2;
update creature_text set BroadcastTextID=28776 where entry=28576 and groupid=1 and id=3;
update creature_text set BroadcastTextID=28782 where entry=28576 and groupid=1 and id=4;
update creature_text set BroadcastTextID=28771 where entry=28576 and groupid=1 and id=5;
update creature_text set BroadcastTextID=28777 where entry=28576 and groupid=1 and id=6;
update creature_text set BroadcastTextID=28781 where entry=28576 and groupid=1 and id=7;
update creature_text set BroadcastTextID=28788 where entry=28576 and groupid=2 and id=0;
update creature_text set BroadcastTextID=28789 where entry=28576 and groupid=2 and id=1;
update creature_text set BroadcastTextID=28791 where entry=28576 and groupid=2 and id=2;
update creature_text set BroadcastTextID=28792 where entry=28576 and groupid=2 and id=3;


















