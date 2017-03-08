
-- fix quest id=24533.

UPDATE `creature_template` SET `ScriptName`="npc_wounded_militia_44405" WHERE entry =44405;

UPDATE `quest_template` set RequiredNpcOrGo1=44405 WHERE `id`=24533;

UPDATE `gameobject_template` SET `flags`=4,`data1`=25058,`data5`=1 WHERE `entry`=202472;

UPDATE `quest_template` SET `RequiredNpcOrGo1`=-202472,`RequiredNpcOrGoCount1`=10 WHERE `Id`=25058;

UPDATE `gameobject_template` SET `flags`=4,`data1`=25058,`data5`=1 WHERE `entry`=202472;

UPDATE `quest_template` SET `RequiredNpcOrGo1`=-202472,`RequiredNpcOrGoCount1`=10 WHERE `Id`=25058;

/*
-- Query: SELECT * FROM `gossip_menu_option` WHERE menu_id IN(4688,4680,2383,4609,3921)
LIMIT 0, 10000
 
-- Date: 2017-03-06 23:17
*/
DELETE FROM `gossip_menu_option` WHERE `nenu_id` IN(4688,4680,2383,4609,3921);
INSERT INTO `gossip_menu_option` (`menu_id`,`id`,`option_icon`,`option_text`,`OptionBroadcastTextID`,`option_id`,`npc_option_npcflag`,`action_menu_id`,`action_poi_id`,`action_script_id`,`box_coded`,`box_money`,`box_text`,`BoxBroadcastTextID`) VALUES 
(2383,0,3,'I am interested in warlock training.',2544,5,16,0,0,0,0,0,'',0),
(2383,1,0,'I wish to unlearn my talents.',62295,16,16,0,0,0,0,0,'',0),
(2383,2,0,'I wish to learn Dual Specialization.',33765,18,16,10371,0,0,0,0,NULL,0),
(3921,0,3,'I seek training as a druid.',7452,5,16,0,0,0,0,0,'',0),
(3921,1,0,'I wish to learn Dual Specialization.',33765,18,16,10371,0,0,0,0,'',0),
(3921,2,0,'I wish to unlearn my Talents.',62295,16,16,4461,0,0,0,0,NULL,0),
(4609,0,3,'I submit myself for further training, my master.',8298,5,16,0,0,0,0,0,'',0),
(4609,1,0,'I wish to learn Dual Specialization.',33765,18,16,10371,0,0,0,0,NULL,0),
(4609,2,0,'I wish to unlearn my Talents.',62295,16,16,4461,0,0,0,0,NULL,0),
(4680,0,3,'I seek more training in the priestly ways.',7169,5,16,0,0,0,0,0,NULL,0),
(4680,1,0,'I wish to learn Dual Specialization.',33765,18,16,10371,0,0,0,0,NULL,0),
(4680,2,0,'I wish to unlearn my Talents.',62295,16,16,4461,0,0,0,0,NULL,0),
(4688,0,3,'I seek training as a druid.',7452,5,16,0,0,0,0,0,NULL,0),
(4688,1,0,'I wish to learn Dual Specialization.',33765,18,16,10371,0,0,0,0,NULL,0),
(4688,2,0,'I wish to unlearn my Talents.',62295,16,16,4461,0,0,0,0,NULL,0);


