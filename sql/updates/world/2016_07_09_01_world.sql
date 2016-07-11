/*
-- Query: SELECT * FROM smart_scripts WHERE entryorguid IN(33001,33035,33037,33033)
LIMIT 0, 1000
-- fix quest http://wow.gamepedia.com/Quest:Coaxing_the_Spirits
--Roger
-- Date: 2016-07-10 13:15
*/
DELETE FROM `smart_scripts` WHERE `entryorguid` IN(33001,33035,33037,33033);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(33001,0,0,1,62,0,100,0,33001,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Thundris Tejevientos  - On gossip option select - Close gossip'),
(33001,0,1,0,61,0,100,0,0,0,0,0,85,62094,0,0,0,0,0,7,0,0,0,0,0,0,0,'Thundris Tejevientos  - On smart link - quest credit'),
(33033,0,0,1,62,0,100,0,33033,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Sentinel Elissa Starbreeze  - On gossip option select - Close gossip'),
(33033,0,1,0,61,0,100,0,0,0,0,0,85,62150,0,0,0,0,0,7,0,0,0,0,0,0,0,'Sentinel Elissa Starbreeze  - On smart link - quest credit'),
(33035,0,0,1,62,0,100,0,33035,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Taldan  - On gossip option select - Close gossip'),
(33035,0,1,0,61,0,100,0,0,0,0,0,85,62153,0,0,0,0,0,7,0,0,0,0,0,0,0,'Taldan  - On smart link - quest credit'),
(33037,0,0,1,62,0,100,0,33037,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Caylais Moonfeather  - On gossip option select - Close gossip'),
(33037,0,1,0,61,0,100,0,0,0,0,0,85,62156,0,0,0,0,0,7,0,0,0,0,0,0,0,'Caylais Moonfeather  - On smart link - quest credit');

