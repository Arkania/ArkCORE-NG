
update creature_template set exp=2 where entry in (10404,38110,1040402,1040403);
update creature_template set exp=3 where entry in (25740,26338);
update creature_template set exp=3 where entry in (25755,26342);
update creature_template set exp=3 where entry in (25756,26340);
update creature_template set exp=3 where entry in (25757,26341);
update creature_template set exp=2 where entry in (25985,26337);
update creature_template set exp=2 where entry in (31118,31491);
update creature_template set exp=2 where entry in (35564,35568);

update creature_template set VehicleId=436 where entry in (35069,35433);
update creature_template set VehicleId=201 where entry in (29838,30935);
update creature_template set VehicleId=447 where entry in (34776,69502);

update creature_template set npcflag=2 where entry in (35557,35560);

update creature_template set faction_A=21, faction_H=21 where entry in (36830,37638);
update creature_template set faction_A=534, faction_H=534 where entry in (37496,37604);

update creature_template set AIName="", ScriptName="npc_edwin_van_cleef" where entry=639;

delete from achievement_criteria_data where criteria_id between 74 and 81 and type=11;

delete from achievement_criteria_data where criteria_id in (82,83,84,85,86,87,88,89,94,95,96,97) and type=8;
delete from achievement_criteria_data where criteria_id in (104,105,106) and type=15;
delete from achievement_criteria_data where criteria_id in (107,108,110) and type=16;
delete from achievement_criteria_data where criteria_id in (111) and type=17;
delete from achievement_criteria_data where criteria_id in (162) and type=13;
delete from achievement_criteria_data where criteria_id in (167,168) and type=7;
delete from achievement_criteria_data where criteria_id in (169,170,171) and type=18;
delete from achievement_criteria_data where criteria_id in (226,227,228,229) and type=8;
delete from achievement_criteria_data where criteria_id in (230,231,232,233,234,236) and type=9;
delete from achievement_criteria_data where criteria_id in (285,286) and type=27;
delete from achievement_criteria_data where criteria_id in (306,307) and type=37;
delete from achievement_criteria_data where criteria_id in (12827,12828) and type=12;
delete from achievement_criteria_data where criteria_id in (11789,12776) and type=28;
delete from achievement_criteria_data where criteria_id in (12825,12826) and type=0;
delete from achievement_criteria_data where criteria_id in (11478,11479) and type=12;
delete from achievement_criteria_data where criteria_id in (12959,12960) and type=28;
delete from achievement_criteria_data where criteria_id in (12975) and type=27;
delete from achievement_criteria_data where criteria_id in (12995,12997,12998) and type=28;
delete from achievement_criteria_data where criteria_id in (13008,13009,13010) and type=34;
delete from achievement_criteria_data where criteria_id in (9058,12562) and type=22;

update creature_template set npcflag=1048577 where entry in(44013,50668,16711,17506,17507,30610,34991,35007,35027);

delete from battlemaster_entry where entry in (40413,49573);
delete from battlemaster_entry where entry in (37413,31979,32092,37298) and bg_template=1;
delete from battlemaster_entry where entry in (34983,34985,34955,34987,34976,34978,34973) and bg_template=32;
insert into battlemaster_entry (entry,bg_template) values
(37413,1),
(31979,1),
(32092,1),
(37298,1),
(34983,32),
(34985,32),
(34955,32),
(34987,32),
(34976,32),
(34978,32),
(34973,32);

delete from gossip_menu where entry=40792;

update gossip_menu_option set action_poi_id=1268 where menu_id=3356 and id=2;
update gossip_menu_option set action_poi_id=1270 where menu_id=3356 and id=3;

update gossip_menu_option set OptionBroadcastTextId=9359 where menu_id=5712 and id=0;
update gossip_menu_option set OptionBroadcastTextId=9359 where menu_id=6880 and id=0;
update gossip_menu_option set OptionBroadcastTextId=18411 where menu_id=7139 and id=0;
update gossip_menu_option set OptionBroadcastTextId=19691 where menu_id=8439 and id=0;
update gossip_menu_option set OptionBroadcastTextId=29539 where menu_id=9573 and id=0;
update gossip_menu_option set OptionBroadcastTextId=29539 where menu_id=9574 and id=0;

update creature_template set npcflag=385 where entry in (3529);
update creature_template set npcflag=131 where entry in (8121);
update creature_template set npcflag=4227 where entry in (14337);
update creature_template set npcflag=4225 where entry in (41452);
update creature_template set npcflag=643 where entry in (42497);
update creature_template set npcflag=129 where entry in (56069);

delete from npc_trainer where entry=35811;
 
update spell_scripts set dataint=41006 where id=62767 and effIndex=0 and delay=2 and command=0;
update spell_scripts set dataint=41008 where id=62767 and effIndex=0 and delay=5 and command=0;
update spell_scripts set dataint=24966 where id=45958 and effIndex=0 and delay=10 and command=0;
update spell_scripts set dataint=14298 where id=45607 and effIndex=0 and delay=1 and command=0;
update spell_scripts set dataint=30401 where id=55083 and effIndex=0 and delay=1 and command=0;
update spell_scripts set dataint=31171 where id=56796 and effIndex=0 and delay=1 and command=0;
update spell_scripts set dataint=31172 where id=56797 and effIndex=0 and delay=1 and command=0;
update spell_scripts set dataint=1673 where id=52160 and effIndex=0 and delay=0 and command=0;
update spell_scripts set dataint=1672 where id=52163 and effIndex=0 and delay=0 and command=0;
 
delete from spell_scripts where id=49203 and effIndex=0 and delay=0 and command=15;
delete from spell_scripts where id=51662 and effIndex=0 and delay=0 and command=15;
delete from spell_scripts where id in (62518,64306);
 
delete from event_scripts where id in (2609);

delete from event_scripts where id=6721;
insert into event_scripts (id,delay,command,datalong,datalong2,dataint,x,y,z,o) values
(6721, 0, 10, 3749, 180000, 0, 2231.03, -1543.77, 90.76, 0),
(6721, 5, 10, 3743, 180000, 0, 2237.97, -1551.94, 90.23, 0),
(6721, 5, 10, 3750, 180000, 0, 2239.35, -1557.46, 89.81, 0),
(6721, 25, 10, 3749, 180000, 0, 2231.03, -1543.77, 90.76, 0),
(6721, 30, 10, 3743, 180000, 0, 2237.97, -1551.94, 90.23, 0),
(6721, 30, 10, 3750, 180000, 0, 2239.35, -1557.46, 89.81, 0),
(6721, 60, 10, 12921, 180000, 0, 2231.03, -1543.77, 90.76, 0),
(6721, 60, 10, 12921, 180000, 0, 2237.97, -1551.94, 90.23, 0),
(6721, 60, 10, 12918, 180000, 0, 2239.35, -1557.46, 89.81, 0),
(6721, 0, 10, 3750, 180000, 0, 2231.35, -1544.31, 91.07, 4.89);

update event_scripts set dataint=13777 where id=10675 and delay=20 and command=0;
update event_scripts set dataint=13776 where id=10675 and delay=10 and command=0;
update event_scripts set dataint=13778 where id=10675 and delay=30 and command=0;
update event_scripts set dataint=13782 where id=10675 and delay=70 and command=0;
update event_scripts set dataint=13781 where id=10675 and delay=60 and command=0;
update event_scripts set dataint=13780 where id=10675 and delay=50 and command=0;
update event_scripts set dataint=13779 where id=10675 and delay=40 and command=0;
 
update event_scripts set datalong=46814 where id=18940 and delay=6 and command=11; 

update event_scripts set dataint=22918 where id=15739 and delay=5 and command=0;

delete from event_scripts where id in (5300,54189,206570,207355,1887150,1899850);

update waypoint_scripts set dataint=5543 where guid=5;
update waypoint_scripts set dataint=5541 where guid=6;
update waypoint_scripts set dataint=5545 where guid=7;
update waypoint_scripts set dataint=5542 where guid=8;
update waypoint_scripts set dataint=5546 where guid=9;
update waypoint_scripts set dataint=5544 where guid=10;
update waypoint_scripts set dataint=5540 where guid=11;
update waypoint_scripts set dataint=5539 where guid=12;
update waypoint_scripts set dataint=4692 where guid=13;
update waypoint_scripts set dataint=10206 where guid=14;
update waypoint_scripts set dataint=10301 where guid=15;
update waypoint_scripts set dataint=22588 where guid=22;
update waypoint_scripts set dataint=22590 where guid=23;
update waypoint_scripts set dataint=22592 where guid=24;
update waypoint_scripts set dataint=5960 where guid=25;
update waypoint_scripts set dataint=22392 where guid=26;
update waypoint_scripts set dataint=22050 where guid=28;
update waypoint_scripts set dataint=22051 where guid=30;
update waypoint_scripts set dataint=22052 where guid=32;
update waypoint_scripts set dataint=10141 where guid=34;
update waypoint_scripts set dataint=10146 where guid=35;
update waypoint_scripts set dataint=10152 where guid=36;
update waypoint_scripts set dataint=10126 where guid=37;
update waypoint_scripts set dataint=7194 where guid=46;
update waypoint_scripts set dataint=7193 where guid=47;
update waypoint_scripts set dataint=7191 where guid=48;
-- update waypoint_scripts set dataint=x where guid=49;
update waypoint_scripts set dataint=6406 where guid=50;
update waypoint_scripts set dataint=6405 where guid=51;
update waypoint_scripts set dataint=10158 where guid=52;
update waypoint_scripts set dataint=22544 where guid=53;
update waypoint_scripts set dataint=10146 where guid=54;
update waypoint_scripts set dataint=12835 where guid=74;
update waypoint_scripts set dataint=12832 where guid=78;
update waypoint_scripts set dataint=12833 where guid=79;
update waypoint_scripts set dataint=14565 where guid=80;
update waypoint_scripts set dataint=14567 where guid=81;
update waypoint_scripts set dataint=15144 where guid=82;
update waypoint_scripts set dataint=15373 where guid=121;
-- update waypoint_scripts set dataint=x where guid=152;
-- update waypoint_scripts set dataint=x where guid=153;
update waypoint_scripts set dataint=16059 where guid=170;
update waypoint_scripts set dataint=16977 where guid=180;
update waypoint_scripts set dataint=16974 where guid=181;
update waypoint_scripts set dataint=10119 where guid=225;
update waypoint_scripts set dataint=17035 where guid=226;
update waypoint_scripts set dataint=70210 where guid=229;
update waypoint_scripts set dataint=17056 where guid=231;
update waypoint_scripts set dataint=17486 where guid=232;
update waypoint_scripts set dataint=17485 where guid=233;
update waypoint_scripts set dataint=17485 where guid=234;
update waypoint_scripts set dataint=17485 where guid=235;
update waypoint_scripts set dataint=18816 where guid=238;
update waypoint_scripts set dataint=709 where guid=241;
update waypoint_scripts set dataint=710 where guid=242;
update waypoint_scripts set dataint=705 where guid=243;
update waypoint_scripts set dataint=693 where guid=244;
update waypoint_scripts set dataint=710 where guid=245;
update waypoint_scripts set dataint=706 where guid=246;
update waypoint_scripts set dataint=709 where guid=247;
update waypoint_scripts set dataint=710 where guid=248;
update waypoint_scripts set dataint=705 where guid=249;
update waypoint_scripts set dataint=693 where guid=250;
update waypoint_scripts set dataint=710 where guid=251;
update waypoint_scripts set dataint=706 where guid=252;
update waypoint_scripts set dataint=709 where guid=253;
update waypoint_scripts set dataint=710 where guid=254;
update waypoint_scripts set dataint=705 where guid=255;
update waypoint_scripts set dataint=693 where guid=256;
update waypoint_scripts set dataint=710 where guid=257;
update waypoint_scripts set dataint=706 where guid=258;
update waypoint_scripts set dataint=709 where guid=259;
update waypoint_scripts set dataint=710 where guid=260;
update waypoint_scripts set dataint=705 where guid=261;
update waypoint_scripts set dataint=694 where guid=262;
update waypoint_scripts set dataint=694 where guid=263;
update waypoint_scripts set dataint=696 where guid=264; 
update waypoint_scripts set dataint=694 where guid=265; 
update waypoint_scripts set dataint=694 where guid=266; 
update waypoint_scripts set dataint=694 where guid=267; 
update waypoint_scripts set dataint=694 where guid=268; 
update waypoint_scripts set dataint=694 where guid=269; 
update waypoint_scripts set dataint=696 where guid=270; 
update waypoint_scripts set dataint=694 where guid=271; 
update waypoint_scripts set dataint=694 where guid=272; 
update waypoint_scripts set dataint=694 where guid=273; 
update waypoint_scripts set dataint=694 where guid=274; 
update waypoint_scripts set dataint=694 where guid=275; 
update waypoint_scripts set dataint=696 where guid=276; 
update waypoint_scripts set dataint=694 where guid=277; 
update waypoint_scripts set dataint=694 where guid=278; 
update waypoint_scripts set dataint=694 where guid=279; 
update waypoint_scripts set dataint=694 where guid=280; 
update waypoint_scripts set dataint=694 where guid=281; 
update waypoint_scripts set dataint=696 where guid=282; 
update waypoint_scripts set dataint=4013 where guid=283; 
update waypoint_scripts set dataint=4014 where guid=284; 
update waypoint_scripts set dataint=4013 where guid=285; 
update waypoint_scripts set dataint=4014 where guid=286; 
update waypoint_scripts set dataint=1110 where guid=291;  
update waypoint_scripts set dataint=1105 where guid=292; 
update waypoint_scripts set dataint=1108 where guid=293; 
update waypoint_scripts set dataint=1106 where guid=294; 
update waypoint_scripts set dataint=1107 where guid=295; 
update waypoint_scripts set dataint=1112 where guid=296; 
update waypoint_scripts set dataint=151 where guid=297; 
update waypoint_scripts set dataint=151 where guid=298; 
update waypoint_scripts set dataint=155 where guid=299; 
update waypoint_scripts set dataint=154 where guid=300; 
update waypoint_scripts set dataint=152 where guid=301; 
update waypoint_scripts set dataint=177 where guid=302; 
update waypoint_scripts set dataint=149 where guid=303; 
update waypoint_scripts set dataint=173 where guid=304; 
update waypoint_scripts set dataint=174 where guid=305; 
update waypoint_scripts set dataint=172 where guid=306; 
update waypoint_scripts set dataint=173 where guid=307; 
update waypoint_scripts set dataint=172 where guid=308; 
update waypoint_scripts set dataint=176 where guid=309; 
update waypoint_scripts set dataint=178 where guid=310; 
update waypoint_scripts set dataint=169 where guid=311; 
update waypoint_scripts set dataint=147 where guid=312; 
update waypoint_scripts set dataint=157 where guid=313; 
update waypoint_scripts set dataint=168 where guid=314; 
update waypoint_scripts set dataint=147 where guid=315; 
update waypoint_scripts set dataint=157 where guid=316; 
update waypoint_scripts set dataint=167 where guid=317; 
update waypoint_scripts set dataint=157 where guid=318; 
update waypoint_scripts set dataint=147 where guid=319; 

update spell_script_names set spell_id=101296 where spell_id=-101296;
update spell_script_names set spell_id=101295 where spell_id=-101295;
update spell_script_names set spell_id=101294 where spell_id=-101294;
update spell_script_names set spell_id=101223 where spell_id=-101223;
update spell_script_names set spell_id=100723 where spell_id=-100723;
update spell_script_names set spell_id=100722 where spell_id=-100722;
update spell_script_names set spell_id=100721 where spell_id=-100721;
update spell_script_names set spell_id=100699 where spell_id=-100699;
update spell_script_names set spell_id=100699 where spell_id=-100699;
update spell_script_names set spell_id=100698 where spell_id=-100698;
update spell_script_names set spell_id=100024 where spell_id=-100024;
update spell_script_names set spell_id=99504 where spell_id=-99504;
update spell_script_names set spell_id=99464 where spell_id=-99464;
update spell_script_names set spell_id=94447 where spell_id=-94447;
update spell_script_names set spell_id=91711 where spell_id=-91711;
update spell_script_names set spell_id=89420 where spell_id=-89420;
update spell_script_names set spell_id=77801 where spell_id=-77801;
update spell_script_names set spell_id=55090 where spell_id=-55090;
update spell_script_names set spell_id=50286 where spell_id=-50286;
update spell_script_names set spell_id=49998 where spell_id=-49998;
update spell_script_names set spell_id=49821 where spell_id=-49821;
update spell_script_names set spell_id=49143 where spell_id=-49143;
update spell_script_names set spell_id=49020 where spell_id=-49020;
update spell_script_names set spell_id=48721 where spell_id=-48721;
update spell_script_names set spell_id=48438 where spell_id=-48438;
update spell_script_names set spell_id=48181 where spell_id=-48181;
update spell_script_names set spell_id=48020 where spell_id=-48020;
update spell_script_names set spell_id=47788 where spell_id=-47788;
update spell_script_names set spell_id=47541 where spell_id=-47541;
update spell_script_names set spell_id=47540 where spell_id=-47540;
update spell_script_names set spell_id=44457 where spell_id=-44457;
update spell_script_names set spell_id=34861 where spell_id=-34861;
update spell_script_names set spell_id=33763 where spell_id=-33763;
update spell_script_names set spell_id=31850 where spell_id=-31850;
update spell_script_names set spell_id=30108 where spell_id=-30108;
update spell_script_names set spell_id=29341 where spell_id=-29341;
update spell_script_names set spell_id=27285 where spell_id=-27285;
update spell_script_names set spell_id=27243 where spell_id=-27243;
update spell_script_names set spell_id=20473 where spell_id=-20473;
update spell_script_names set spell_id=17877 where spell_id=-17877;
update spell_script_names set spell_id=11113 where spell_id=-11113;
update spell_script_names set spell_id=8129 where spell_id=-8129;
update spell_script_names set spell_id=8050 where spell_id=-8050;
update spell_script_names set spell_id=6353 where spell_id=-6353;
update spell_script_names set spell_id=6262 where spell_id=-6262;
update spell_script_names set spell_id=6229 where spell_id=-6229;
update spell_script_names set spell_id=5676 where spell_id=-5676;
update spell_script_names set spell_id=5570 where spell_id=-5570;
update spell_script_names set spell_id=3110 where spell_id=-3110;
update spell_script_names set spell_id=2818 where spell_id=-2818;
update spell_script_names set spell_id=1464 where spell_id=-1464;
update spell_script_names set spell_id=1463 where spell_id=-1463;
update spell_script_names set spell_id=1454 where spell_id=-1454;
update spell_script_names set spell_id=1120 where spell_id=-1120;
update spell_script_names set spell_id=1064 where spell_id=-1064;
update spell_script_names set spell_id=689 where spell_id=-689;
update spell_script_names set spell_id=633 where spell_id=-633;
update spell_script_names set spell_id=543 where spell_id=-543;
update spell_script_names set spell_id=139 where spell_id=-139;
update spell_script_names set spell_id=100 where spell_id=-100;
update spell_script_names set spell_id=17 where spell_id=-17;

delete from spell_script_names where spell_id in (-1535,-5308,-11426);
















