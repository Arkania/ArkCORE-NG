
delete from gossip_menu where entry=10988 and text_id=15276;
insert into gossip_menu values (10988,15276);

update gossip_menu_option set OptionBroadcastTextID=7643 where menu_id=10988;

update creature_template set gossip_menu_id=10974 where entry=39062;
update gossip_menu_option set OptionBroadcastTextID=37885 where menu_id=10974;

UPDATE `creature_template` SET `spell1`=79425, `spell2`=79430 WHERE `entry`=42601;

update creature set spawntimesecs=120 where id=38141;

