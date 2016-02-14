/*
--  Query: SELECT * FROM `gameobject_template` WHERE entry=164911
LIMIT 0, 1000

--  Date: 2016-02-10 08:55
*/
-- Hurley Blackbreath is summoned creature.http://wow.gamepedia.com/Hurley_Blackbreath
UPDATE `gameobject_template` SET `data2`=665 WHERE `entry`=164911;
DELETE FROM `event_scripts` WHERE `id`=665;
INSERT INTO `event_scripts` (`id`,`delay`,`command`,`datalong`,`datalong2`,`dataint`,`x`,`y`,`z`,`o`) VALUES 
(665,0,10,9537,60000,0,916.18,-161.19,-49.75,2.04967);
DELETE FROM `creature` WHERE `id`=9537 AND `guid`=151279;

-- supports quest http://www.wowhead.com/quest=25260/fizzled
UPDATE `item_template` SET `class`=12 WHERE `entry`=52580;
UPDATE `creature_template` SET `gossip_menu_id`=11240 WHERE `entry`=3203;

DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (11239,11240);
INSERT INTO `gossip_menu_option` (`menu_id`,`id`,`option_icon`,`option_text`,`OptionBroadcastTextID`,`option_id`,`npc_option_npcflag`,`action_menu_id`,`action_poi_id`,`action_script_id`,`box_coded`,`box_money`,`box_text`,`BoxBroadcastTextID`) VALUES 
(11239,0,0,"<Attempt to remove Fizzle's Hand, then.>",0,1,1,0,0,0,0,0,'',0),
(11239,1,0,"<Give up.  This is too scary.>",0,1,1,0,0,0,0,0,'',0),
(11240,0,0,"<Attempt to remove the orb.>",0,1,1,11239,0,0,0,0,'',0);

DELETE FROM `smart_scripts` WHERE `entryorguid`=3203;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(3203,0,0,0,62,0,100,1,11239,0,0,0,85,74024,0,0,0,0,0,1,0,0,0,0,0,0,0,'Fizzle Darkclaw~On gossip~add item.'),
(3203,0,1,2,62,0,100,0,11239,1,0,0,12,3197,3,60000,1,0,0,1,0,0,0,0,0,0,0,'Fizzle~on scared gossip~summon mob'),
(3203,0,2,0,61,0,100,0,0,0,0,0,12,3197,3,60000,1,0,0,1,0,0,0,0,0,0,0,'Fizzle~on scared gossip~summon mob');

-- supports quest "thunder down under". http://www.wowhead.com/quest=25236/thunder-down-under  + quest=26572
UPDATE `creature_template` SET `AIName`='SmartAI',`npcflag`=1,`unit_flags`=832,`unit_flags2`=1,`dynamicflags`=32 WHERE `entry`=39464;
DELETE FROM `smart_scripts` WHERE `entryorguid`=39464;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(39464,0,0,0,1,0,100,0,4000,7000,22000,25000,11,73958,0,0,0,0,0,1,0,0,0,0,0,0,0,'Cast Lightning Discharge'),
(39464,0,1,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'On gossip ~ close gossip.'),
(39464,0,2,0,64,0,100,0,0,0,0,0,85,73945,0,0,0,0,0,7,0,0,0,0,0,0,0,'On gossip ~ cast tether.'),
(39464,0,3,0,64,0,100,0,0,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0,0,0,0,'On gossip ~ despawn 1000ms');

DELETE FROM `npc_spellclick_spells` WHERE npc_entry=39464;

delete from conditions where SourceTypeOrReferenceId=17 and SourceEntry=80948 and ConditionTypeOrReference=29 and ConditionValue1=39464;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorType`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES 
(17,0,80948,0,0,29,0,39464,3,0,0,0,0,'',NULL);

-- spawn drowned thunder lizards on correct places.
DELETE FROM `creature` WHERE `id`=39464;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES 
(89430,39464,1,1,1,0,1,851.579,-4049.46,-4.78039,3.9899,300,0,0,198,0,0,0,0,0),
(89558,39464,1,1,1,0,1,910.282,-4045.86,-11.795,0.461209,300,0,0,198,0,0,0,0,0),
(93919,39464,1,1,1,0,1,925.408,-4027.15,-12.168,5.70993,300,0,0,198,0,0,0,0,0),
(89763,39464,1,1,1,0,0,771.662,-4000.64,33.2327,2.44022,500,0,0,198,0,0,0,0,0),
(94022,39464,1,1,1,0,1,749.561,-4113.51,-4.19878,3.48892,300,0,0,198,0,0,0,0,0),
(89734,39464,1,1,1,0,1,802.229,-4096.36,-7.21209,3.39075,300,0,0,198,0,0,0,0,0),
(88955,39464,1,1,1,0,1,961.513,-4087.17,-10.4159,0.584109,300,0,0,198,0,0,0,0,0),
(88816,39464,1,1,1,0,1,948.866,-4114.04,-10.5581,2.11564,300,0,0,198,0,0,0,0,0),
(88704,39464,1,1,1,0,1,951.116,-4210.46,-7.25181,2.79501,300,0,0,198,0,0,0,0,0),
(88031,39464,1,1,1,0,1,977.972,-4050.69,-11.9739,5.24821,300,0,0,198,0,0,0,0,0);

