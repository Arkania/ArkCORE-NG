
-- issue #81

-- http://de.wowhead.com/quest=26630/sieht-doch-wie-ein-taurenpirat-aus
-- http://de.wowhead.com/npc=2487/flottenmeister-seehorn  ,guid 22676
-- http://de.wowhead.com/npc=2663/narkk#sells,,,,guid 22356
-- http://de.wowhead.com/item=59148/ubergrosser-piratenhut
-- http://de.wowhead.com/item=59147/kuhkopf
-- http://de.wowhead.com/spell=81311/looks-like-a-tauren-pirate-to-me-bossys-sacrifice
-- http://de.wowhead.com/npc=2699/rikqiz,,,,,guid 23824
-- http://www.wowhead.com/npc=43505/bossy
-- https://www.youtube.com/watch?v=aiIw9L9UaU8

update creature_template set AIName="", ScriptName="npc_narkk_2663" where entry=2663;
update creature_template set AIName="", ScriptName="npc_fleet_master_seahorn_2487" where entry=2487;

update creature set spawndist=0, MovementType=0 where guid=56457 and id=43506;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Flottenmeister Seehorn in Beutebucht am Schlingendornkap zurück.", QuestGiverTextWindow_loc3="Flottenmeister Seehorn", QuestGiverTargetName_loc3="Flottenmeister Seehorn" WHERE Id=26630;
UPDATE quest_template SET RequiredItemId1=59147, RequiredItemId3=0, RequiredItemCount1=1, RequiredItemCount3=0 WHERE Id=26630;

-- https://cata-twinhead.twinstar.cz/?npc=43506
delete from creature where guid=56457 and id=43506;

UPDATE creature_template SET gossip_menu_id=0 WHERE entry=43505;

update creature_template set AIName="", ScriptName="npc_bossy_43505" where entry=43505;

update gossip_menu_option set OptionBroadcastTextID=43570, action_menu_id=11742, option_id=1, npc_option_npcflag=1 where menu_id=11741 and id=0;
update gossip_menu_option set OptionBroadcastTextID=43571, option_id=1, npc_option_npcflag=1 where menu_id=11741 and id=1;

update gossip_menu_option set OptionBroadcastTextID=43572, option_id=1, npc_option_npcflag=1 where menu_id=11742 and id=0;
update gossip_menu_option set OptionBroadcastTextID=43573, option_id=1, npc_option_npcflag=1 where menu_id=11742 and id=1;

delete from gossip_menu_option where menu_id=50045 and id=0;
insert into gossip_menu_option values
(50045,0,1,"What've you got?",43578,3,1,0,0,0,0,0,"",0);

delete from creature_text where entry=2663 and groupid=0 and id=0;
insert into creature_text values
(2663,0,0,"Tell him this is the last one.  It breaks poor Narkk's heart to have to carve horn-holes in his beautiful hats!",12,0,100,0,0,0,"",43577);

delete from creature_text where entry=2487 and groupid in (0, 1, 2) and id=0;
insert into creature_text values
(2487,0,0,"Hey Baron, go long!",12,0,100,0,0,0,"",43586),
(2487,1,0,"That'll do.",12,0,100,0,0,0,"",43588),
(2487,2,0,"Bring that back up to Yancey, by the waterfall.  The ignorant human'll have no idea that it's not me.",12,0,100,0,0,0,"",44061);
 
delete from gossip_menu_option where menu_id=50046 and id=0;
insert into gossip_menu_option values
(50046,0,0,"Here's the head and the hat, Fleet Master.",43589,1,1,0,0,0,0,0,"",0);

update gossip_menu_option set OptionBroadcastTextID=43590 where menu_id=11745 and id=0;



