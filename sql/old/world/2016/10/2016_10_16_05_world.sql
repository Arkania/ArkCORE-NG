
delete from gossip_menu_option where menu_id=1;

delete from gossip_menu where entry>= 57800;

delete from gossip_menu where entry=42386 and text_id=921062;
delete from gossip_menu where entry=37552 and text_id=537552;

DELETE FROM gossip_menu WHERE entry=10550 and text_id=14803;
INSERT INTO gossip_menu VALUES (10550, 14803);

UPDATE gossip_menu_option SET OptionBroadcastTextID=2544 WHERE menu_id=10550 AND id=0;

DELETE FROM gossip_menu WHERE entry=10553 and text_id=14810;
INSERT INTO gossip_menu VALUES (10553, 14810);

delete from npc_text where ID=14810;
insert into npc_text (ID) values (14810);
UPDATE npc_text SET text0_1="We're... er, I mean the Light, is going to need a lot of gold, now more than ever.$B$BSpeaking of which, do you need any training?", BroadcastTextID0=35983, prob0=1, em0_0=1 WHERE ID=14810;

delete from npc_text where ID=14606;
insert into npc_text (ID) values (14606);
UPDATE npc_text SET text0_1="Warrior-Matic NX-01 is online.$B$BPlease insert coins for training.", BroadcastTextID0=34960, prob0=1 WHERE ID=14606;

DELETE FROM gossip_menu WHERE entry=10555 and text_id=14606;
INSERT INTO gossip_menu VALUES (10555, 14606);

DELETE FROM gossip_menu WHERE entry=10549 and text_id=14594;
INSERT INTO gossip_menu VALUES (10549, 14594);

delete from npc_text where ID=14594;
insert into npc_text (ID) values (14594);
UPDATE npc_text SET text0_1="Hey, $N, good to see you. These monkeys are driving me insane!$B$BWhat do you need?", BroadcastTextID0=34946 WHERE ID=14594;

delete from conditions where SourceTypeOrReferenceId=14 and SourceGroup=10555;
insert into conditions values 
(14, 10555, 14605, 0, 0, 15, 0, 1534, 0, 0, 0, 0, 0, "", "is not warrier class"),
(14, 10555, 14606, 0, 0, 15, 0,    1, 0, 0, 0, 0, 0, "", "is warrier class");

delete from conditions where SourceTypeOrReferenceId=14 and SourceGroup=10549;
insert into conditions values 
(14, 10549, 14593, 0, 0, 15, 0, 1531, 0, 0, 0, 0, 0, "", "is not hunter class"),
(14, 10549, 14594, 0, 0, 15, 0,    4, 0, 0, 0, 0, 0, "", "is hunter class");

delete from conditions where SourceTypeOrReferenceId=14 and SourceGroup=10554;
insert into conditions values 
(14, 10554, 14603, 0, 0, 15, 0, 1527, 0, 0, 0, 0, 0, "", "is not rogue class"),
(14, 10554, 14604, 0, 0, 15, 0,    8, 0, 0, 0, 0, 0, "", "is rogue class");

delete from conditions where SourceTypeOrReferenceId=14 and SourceGroup=10553;
insert into conditions values 
(14, 10553, 14809, 0, 0, 15, 0, 1519, 0, 0, 0, 0, 0, "", "is not Priest class"),
(14, 10553, 14810, 0, 0, 15, 0,   16, 0, 0, 0, 0, 0, "", "is Priest class");

delete from conditions where SourceTypeOrReferenceId=14 and SourceGroup=10552;
insert into conditions values 
(14, 10552, 14599, 0, 0, 15, 0, 1471, 0, 0, 0, 0, 0, "", "is not Shaman class"),
(14, 10552, 14600, 0, 0, 15, 0,   64, 0, 0, 0, 0, 0, "", "is Shaman class");

delete from conditions where SourceTypeOrReferenceId=14 and SourceGroup=10551;
insert into conditions values 
(14, 10551, 14597, 0, 0, 15, 0, 1407, 0, 0, 0, 0, 0, "", "is not mage class"),
(14, 10551, 14598, 0, 0, 15, 0,  128, 0, 0, 0, 0, 0, "", "is mage class");

delete from conditions where SourceTypeOrReferenceId=14 and SourceGroup=10550;
insert into conditions values 
(14, 10550, 14802, 0, 0, 15, 0, 1279, 0, 0, 0, 0, 0, "", "is not warlock class"),
(14, 10550, 14803, 0, 0, 15, 0,  256, 0, 0, 0, 0, 0, "", "is warlock class");









