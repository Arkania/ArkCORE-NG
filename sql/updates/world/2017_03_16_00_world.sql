
-- 43247  Quest Invis Zone 3 and Zone 19
update creature_addon set auras="80815 82099" where guid in (33776,33794,33874,33884,34042,34093,34105,34184,34199,34281,34282,34360,34471);

update creature_addon set auras ="80698" where guid in (33827,34444,33943,33790,34335,34086,34217);

UPDATE creature_addon SET auras="80698" WHERE guid=61128;

update creature_addon set auras="80816" where guid=26647;

update creature_addon set auras="80699" where guid=61128;

DELETE FROM creature_template_addon WHERE entry in (43432,43433,43434,43435);

INSERT INTO creature_template_addon VALUES 
(43432, 0, 0, 0, 1, 0, "81201"),
(43433, 0, 0, 0, 1, 0, "81201"),
(43434, 0, 0, 0, 1, 0, "81201"),
(43435, 0, 0, 0, 1, 0, "81201");

DELETE FROM creature_template_addon WHERE entry=43184;

INSERT INTO creature_template_addon VALUES 
(43184, 0, 0, 0, 1, 0, "80816");

DELETE FROM creature_template_addon WHERE entry in (43445,43446,43447,43448,43449);

INSERT INTO creature_template_addon VALUES 
(43445, 0, 0, 0, 1, 0, "81240"),
(43446, 0, 0, 0, 1, 0, "81240"),
(43447, 0, 0, 0, 1, 0, "81240"),
(43448, 0, 0, 0, 1, 0, "81240"),
(43449, 0, 0, 0, 1, 0, "81240");

UPDATE creature_addon SET auras="80815 80201" WHERE guid=33881;

UPDATE creature_template_addon SET auras="80816" WHERE entry=43194;

delete from creature where id=440 and guid=43990;

UPDATE creature SET MovementType=2 WHERE guid=43989;

DELETE FROM creature_addon WHERE guid=43989;
INSERT INTO creature_addon VALUES 
(43989, 43989, 0, 0, 1, 0, "");

DELETE FROM waypoint_data WHERE id=43989;
INSERT INTO waypoint_data VALUES 
(43989, 0, -9172.082, -2402.791, 104.3548, 3.451401, 0, 0, 0, 100, 0),
(43989, 1, -9177.09, -2409.842, 106.0561, 3.918714, 0, 0, 0, 100, 0),
(43989, 2, -9194.232, -2415.612, 106.5246, 3.471037, 5000, 0, 0, 100, 0),
(43989, 3, -9176.474, -2419.242, 107.0681, 6.113901, 0, 0, 0, 100, 0),
(43989, 4, -9150.945, -2411.619, 104.5415, 0.290173, 0, 0, 0, 100, 0),
(43989, 5, -9150.13, -2402.376, 103.2434, 1.523249, 0, 0, 0, 100, 0),
(43989, 6, -9163.885, -2402.428, 103.6514, 3.035141, 0, 0, 0, 100, 0);

-- fix teleport for quest 27674 To The Surface, Tinker Town
DELETE FROM `smart_scripts` WHERE `entryorguid`=46293 AND `source_type`=0;

INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(46293,0,0,0,62,0,100,0,12104,1,0,0,62,0,0,0,0,0,0,7,0,0,0,-5201.29,477.545,388.471,5.2577,'Teleport');

DELETE FROM `gossip_menu_option` WHERE `menu_id`=12104;

INSERT INTO `gossip_menu_option` (`menu_id`,`id`,`option_icon`,`option_text`,`OptionBroadcastTextID`,`option_id`,`npc_option_npcflag`,`action_menu_id`,`action_poi_id`,`action_script_id`,`box_coded`,`box_money`,`box_text`,`BoxBroadcastTextID`) VALUES 
(12104,1,0,'Send me to the surface, Torben.',46360,1,1,0,0,0,0,0,NULL,0);

-- Prepare quest 26205.
DELETE FROM `creature_text` WHERE `entry`=42598;

INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`,`BroadcastTextID`) VALUES 
(42598,0,0,'Initiating cleanup!',12,0,100,0,0,0,NULL,42476);

update creature_template set lootid=0 where entry=11604;

delete from creature_loot_template where entry=11604 and item=16885;

UPDATE quest_template SET PrevQuestId=26503 WHERE Id=26505;

UPDATE quest_template SET PrevQuestId=26365 WHERE Id=26503;



