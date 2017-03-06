
-- fix more issue #125
delete from game_event_creature where eventEntry=75 and guid in (53431, 117248, 117249, 159533, 159534, 199130);
delete from game_event_creature where eventEntry=75 and guid in (12791, 12793, 12794, 117246, 158189, 158190, 196245);

insert into game_event_creature values
(75,53431),
(75,117248),
(75,117249),
(75,159533),
(75,159534),
(75,199130),
(75,12791),
(75,12793),
(75,12794),
(75,117246),
(75,158189),
(75,158190),
(75,196245);

update game_event set start_time="2011-01-01 02:01:00", end_time="2011-12-30 21:00:00" where eventEntry=3;
update game_event set start_time="2011-01-01 02:01:00", end_time="2011-12-30 21:00:00" where eventEntry=4;
update game_event set start_time="2011-01-01 02:01:00", end_time="2011-12-30 21:00:00" where eventEntry=5;
update game_event set start_time="2011-01-01 02:01:00", end_time="2011-12-30 21:00:00" where eventEntry=23;
update game_event set start_time="2016-01-01 02:01:00", end_time="2030-12-29 23:00:00" where eventEntry=75;

delete from gossip_menu_option where menu_id=13124;
INSERT INTO `gossip_menu_option` VALUES (13124, 0, 0, 'Take me to the faire staging area.', 52971, 1, 1, 0, 0, 0, 0, 500, 'Travel to the faire staging area will cost:', 52972);

delete from conditions where SourceTypeOrReferenceId=15 and SourceGroup=13124 and ConditionTypeOrReference=12 and ConditionValue1=75;

delete from gossip_menu_option where menu_id=12992;
INSERT INTO `gossip_menu_option` VALUES (12992, 0, 0, 'Take me to the faire staging area.', 52971, 1, 1, 0, 0, 0, 0, 500, 'Travel to the faire staging area will cost:', 52972);

delete from conditions where SourceTypeOrReferenceId=15 and SourceGroup=12992 and ConditionTypeOrReference=12 and ConditionValue1=75;

delete from creature where id=14828;
INSERT INTO `creature` VALUES (50007, 14828, 974, 1, 65535, 14854, 1, -4125.92, 6381.08, 13.6545, 4.72984, 300, 0, 0, 699, 0, 0, 0, 0, 0);

delete from game_event_creature where eventEntry=75 and guid=50007;
insert into game_event_creature values
(75, 50007);

delete from creature where id=10445;
INSERT INTO `creature` VALUES (53270, 10445, 974, 1, 65535, 9810, 0, -4004.8, 6236.22, 13.1998, 0.244346, 300, 0, 0, 955, 0, 0, 0, 0, 0);

delete from game_event_creature where eventEntry=75 and guid=53270;
insert into game_event_creature values
(75, 53270);
 
delete from creature where id=14871;
INSERT INTO `creature` VALUES (53271, 14871, 974, 1, 65535, 14943, 0, -4199.69, 6229.47, 13.2001, 1.58825, 300, 0, 0, 247, 0, 0, 0, 0, 0);
 
delete from game_event_creature where eventEntry=75 and guid=53271;
insert into game_event_creature values
(75, 53271);
 
 UPDATE creature_template SET spell1=102911 WHERE entry=55399;

 UPDATE creature_template SET spell1=102905 WHERE entry=55397;

 update locales_creature set name_loc3="Begrüßer des Dunkelmond-Jahrmarkts", femaleName_loc3="Begrüßerin des Dunkelmond-Jahrmarkts" where entry=55396;
 
 delete from creature where id=14849 and guid in (128038, 128141);
 
 delete from gameobject where id=179965 and guid=180999;
 
 
 