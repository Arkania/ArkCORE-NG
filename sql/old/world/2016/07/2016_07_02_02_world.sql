/*
-- Query: SELECT * FROM event_scripts WHERE id =23338
LIMIT 0, 1000
--quest Take Back What's Ours http://www.wowhead.com/quest=24646/take-back-whats-ours
--Horn Event Fix.
--Roger
-- Date: 2016-07-03 20:59
*/

-- prepare npc's
UPDATE creature_template SET AIName='SmartAI' WHERE entry IN(38029,38027);
UPDATE creature_template SET dmg_multiplier=7.5,Health_mod=230 WHERE entry IN(38029,38027);
UPDATE creature_template SET equipment_id=1 WHERE entry=38022;

delete from creature_equip_template where entry=38022 and id=1;
INSERT INTO creature_equip_template (entry,id,itemEntry1,itemEntry2,itemEntry3) VALUES (38022,1,34285,34285,18680);

DELETE FROM creature WHERE id IN(38029,38027); -- Summoned on Event.

-- Events
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,dataint,x,y,z,o) VALUES (23338,0,10,38029,30000,0,-2146.12,1583.35,-48.8068,1.23918);
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,dataint,x,y,z,o) VALUES (23338,0,10,38027,30000,0,-2144.57,1632.94,-42.3479,-0.855269);
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,dataint,x,y,z,o) VALUES (23338,0,10,38027,30000,0,-2131.48,1617.85,-42.8147,3.61283);
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,dataint,x,y,z,o) VALUES (23338,0,10,38027,30000,0,-2128.74,1614.81,-43.4143,3.61283);
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,dataint,x,y,z,o) VALUES (23338,0,10,38027,30000,0,-2143.11,1622.21,-43.3479,-0.31676);
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,dataint,x,y,z,o) VALUES (23338,0,10,38027,30000,0,-2128.26,1616.09,-43.0635,1.81255);
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,dataint,x,y,z,o) VALUES (23338,0,10,38027,30000,0,-2150.1,1619.99,-43.0979,0.0833293);
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,dataint,x,y,z,o) VALUES (23338,0,10,38027,30000,0,-2126.95,1574.36,-50.4436,1.25707);
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,dataint,x,y,z,o) VALUES (23338,0,10,38027,30000,0,-2078.16,1587.95,-45.4607,2.51294);
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,dataint,x,y,z,o) VALUES (23338,0,10,38027,30000,0,-2126.58,1612.21,-43.4249,-0.4537);
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,dataint,x,y,z,o) VALUES (23338,0,10,38027,30000,0,-2128.05,1609.34,-43.4712,0.910575);
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,dataint,x,y,z,o) VALUES (23338,0,10,38027,30000,0,-2156.52,1646.69,-39.123,5.42801);
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,dataint,x,y,z,o) VALUES (23338,0,10,38027,30000,0,-2132.71,1617.19,-43.4719,5.42801);
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,dataint,x,y,z,o) VALUES (23338,0,10,38027,30000,0,-2160.45,1617.19,-43.4719,3.14159);
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,dataint,x,y,z,o) VALUES (23338,0,10,38027,30000,0,-2146.25,1637.87,-41.398,5.09906);
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,dataint,x,y,z,o) VALUES (23338,0,10,38027,30000,0,-2154.19,1625.67,-42.7173,5.82915);
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,dataint,x,y,z,o) VALUES (23338,0,10,38027,30000,0,-2129.98,1606.86,-42.7173,5.82915);
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,dataint,x,y,z,o) VALUES (23338,0,10,38027,30000,0,-2132.64,1582.45,-49.3497,1.5612);
INSERT INTO event_scripts (id,delay,command,datalong,datalong2,dataint,x,y,z,o) VALUES (23338,0,16,14969,2,0,0,0,0,0);

-- NPC Text.
delete from creature_text where entry=38029;
INSERT INTO creature_text (entry,groupid,id,text,type,language,probability,emote,duration,sound,comment,BroadcastTextID) VALUES (38029,1,0,'Keep them occupied, my brothers! Allow $N to retrieve the scythe!',14,0,100,0,0,0,'',37795);
INSERT INTO creature_text (entry,groupid,id,text,type,language,probability,emote,duration,sound,comment,BroadcastTextID) VALUES (38029,2,0,'Fall back! Retreat into the woods!',14,0,100,0,0,0,'',37796);
-- SAI
delete from smart_scripts where entryorguid in (38027, 38029);
INSERT INTO smart_scripts (entryorguid,source_type,id,link,event_type,event_phase_mask,event_chance,event_flags,event_param1,event_param2,event_param3,event_param4,action_type,action_param1,action_param2,action_param3,action_param4,action_param5,action_param6,target_type,target_param1,target_param2,target_param3,target_x,target_y,target_z,target_o,comment) VALUES (38027,0,0,1,38,0,100,0,1,1,0,0,2,2134,0,0,0,0,0,1,0,0,0,0,0,0,0,'on data set - set faction');
INSERT INTO smart_scripts (entryorguid,source_type,id,link,event_type,event_phase_mask,event_chance,event_flags,event_param1,event_param2,event_param3,event_param4,action_type,action_param1,action_param2,action_param3,action_param4,action_param5,action_param6,target_type,target_param1,target_param2,target_param3,target_x,target_y,target_z,target_o,comment) VALUES (38027,0,1,2,61,0,100,0,0,0,0,0,53,1,38027,0,0,0,0,1,0,0,0,0,0,0,0,'on data set - start WP');
INSERT INTO smart_scripts (entryorguid,source_type,id,link,event_type,event_phase_mask,event_chance,event_flags,event_param1,event_param2,event_param3,event_param4,action_type,action_param1,action_param2,action_param3,action_param4,action_param5,action_param6,target_type,target_param1,target_param2,target_param3,target_x,target_y,target_z,target_o,comment) VALUES (38027,0,2,3,61,0,100,0,0,0,0,0,14,0,100,0,0,0,0,1,0,0,0,0,0,0,0,'on data set - start WP');
INSERT INTO smart_scripts (entryorguid,source_type,id,link,event_type,event_phase_mask,event_chance,event_flags,event_param1,event_param2,event_param3,event_param4,action_type,action_param1,action_param2,action_param3,action_param4,action_param5,action_param6,target_type,target_param1,target_param2,target_param3,target_x,target_y,target_z,target_o,comment) VALUES (38027,0,3,0,61,0,100,0,0,0,0,0,18,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'on data set - start WP');
INSERT INTO smart_scripts (entryorguid,source_type,id,link,event_type,event_phase_mask,event_chance,event_flags,event_param1,event_param2,event_param3,event_param4,action_type,action_param1,action_param2,action_param3,action_param4,action_param5,action_param6,target_type,target_param1,target_param2,target_param3,target_x,target_y,target_z,target_o,comment) VALUES (38027,0,4,0,0,0,100,0,60000,60000,70000,70000,41,500,0,0,0,0,0,1,0,0,0,0,0,0,0,'on data set - start WP');
INSERT INTO smart_scripts (entryorguid,source_type,id,link,event_type,event_phase_mask,event_chance,event_flags,event_param1,event_param2,event_param3,event_param4,action_type,action_param1,action_param2,action_param3,action_param4,action_param5,action_param6,target_type,target_param1,target_param2,target_param3,target_x,target_y,target_z,target_o,comment) VALUES (38029,0,0,0,11,0,100,1,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'On spawn - say - text 1');
INSERT INTO smart_scripts (entryorguid,source_type,id,link,event_type,event_phase_mask,event_chance,event_flags,event_param1,event_param2,event_param3,event_param4,action_type,action_param1,action_param2,action_param3,action_param4,action_param5,action_param6,target_type,target_param1,target_param2,target_param3,target_x,target_y,target_z,target_o,comment) VALUES (38029,0,1,0,0,0,100,0,40000,40000,50000,50000,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'IC - say 2');
INSERT INTO smart_scripts (entryorguid,source_type,id,link,event_type,event_phase_mask,event_chance,event_flags,event_param1,event_param2,event_param3,event_param4,action_type,action_param1,action_param2,action_param3,action_param4,action_param5,action_param6,target_type,target_param1,target_param2,target_param3,target_x,target_y,target_z,target_o,comment) VALUES (38029,0,2,0,0,0,100,0,40000,40000,50000,50000,45,1,1,0,0,0,0,11,38027,150,0,0,0,0,0,'IC - set data - 38027');
-- Waypoints.
delete from waypoints where entry=38027;
INSERT INTO waypoints (entry,pointid,position_x,position_y,position_z,point_comment) VALUES (38027,1,-2120.83,1599.11,-44.4613,'worgen retreat');
INSERT INTO waypoints (entry,pointid,position_x,position_y,position_z,point_comment) VALUES (38027,2,-2105.68,1540.66,-51.7158,'worgen retreat');
-- end code.
UPDATE creature_template SET faction=2163 WHERE entry=38027;

