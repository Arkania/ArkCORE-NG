
-- fix issue #157
-- Fix quest http://www.wowhead.com/quest=13557/bearer-of-good-fortune
-- no scripting,no credit.
-- Dodger

DELETE FROM event_scripts WHERE id=249 AND command=8;
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,dataint,x,y,z,o) VALUES 
(249,2,8,33024,0,0,0,0,0,0);

UPDATE gameobject_template SET data1=13557,data2=249,data3=1000,AIName='SmartGameObjectAI' WHERE entry IN(194124,194133);

UPDATE creature_template SET AIName='SmartAI' WHERE entry IN(33023,33024);
DELETE FROM smart_scripts WHERE entryorguid IN(194124,194133,33023,33024);
INSERT INTO smart_scripts (entryorguid,source_type,id,link,event_type,event_phase_mask,event_chance,event_flags,event_param1,event_param2,event_param3,event_param4,action_type,action_param1,action_param2,action_param3,action_param4,action_param5,action_param6,target_type,target_param1,target_param2,target_param3,target_x,target_y,target_z,target_o,comment) VALUES 
(33023,0,0,1,38,0,100,0,1,1,0,0,46,15,0,0,0,0,0,1,0,0,0,0,0,0,0,'creature-on data set-move forward'),
(33023,0,1,0,61,0,100,0,0,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0,0,0,0,'creature-on smart link-despawn.'),
(33024,0,0,1,38,0,100,0,1,1,0,0,46,15,0,0,0,0,0,1,0,0,0,0,0,0,0,'creature-on data set-move forward'),
(33024,0,1,0,61,0,100,0,0,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0,0,0,0,'creature-on smart link-despawn.'),
(194124,1,0,0,64,0,100,0,0,0,0,0,45,1,1,0,0,0,0,19,33024,10,0,0,0,0,0,'bear cage-on gossip-set data.'),
(194133,1,0,0,64,0,100,0,0,0,0,0,45,1,1,0,0,0,0,19,33023,10,0,0,0,0,0,'rat cage=on gossip-set data');



