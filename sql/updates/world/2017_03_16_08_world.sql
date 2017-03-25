
DELETE FROM waypoint_data WHERE id=145921;
INSERT INTO waypoint_data VALUES 
(145921, 0, -13.32691, -373.279, 62.4812, 3.023786, 3000, 0, 0, 100, 0),
(145921, 1, -12.78855, -370.432, 65.10646, 3.381143, 3000, 0, 0, 100, 0),
(145921, 2, -23.83906, -369.7896, 64.09648, 3.129816, 3000, 0, 0, 100, 0),
(145921, 3, -13.57825, -370.8893, 64.90394, 6.239985, 3000, 0, 0, 100, 0),
(145921, 4, -13.42154, -372.7708, 62.59602, 4.551383, 3000, 0, 0, 100, 0),
(145921, 5, -13.19868, -383.6178, 61.99183, 4.755585, 3000, 0, 0, 100, 0),
(145921, 6, -16.90775, -383.9433, 62.20382, 3.125887, 3000, 0, 0, 100, 0),
(145921, 7, -32.55937, -372.7729, 59.05791, 2.670356, 3000, 0, 0, 100, 0),
(145921, 8, -18.58335, -373.5173, 61.07484, 6.259624, 3000, 0, 0, 100, 0);

delete from phase_definitions where zoneId=40 and entry=0;
INSERT INTO `phase_definitions` VALUES 
(40, 0, 232, 0, 0, 683, 1, 'Quest 26233, Rise of the Brotherhood, Westfall - Sentinel Hill');

DELETE FROM phase_area WHERE areaId=40 AND entry=0;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(40, 0, 26322, 26322, 74, 11, 1, "Quest 26233, Rise of the Brotherhood, Westfall - Sentinel Hill");

UPDATE creature SET MovementType=2 WHERE guid=26686;

DELETE FROM creature_addon WHERE guid=26686;
INSERT INTO creature_addon VALUES 
(26686, 26686, 0, 65636, 1, 0, "79488");

DELETE FROM waypoint_data WHERE id=26686;
INSERT INTO waypoint_data VALUES 
(26686, 0, -9874.828, 911.1061, 31.97685, 0, 0, 0, 0, 100, 0),
(26686, 1, -9875.803, 911.3291, 31.97685, 0, 0, 0, 0, 100, 0),
(26686, 2, -9871.86, 911.8401, 31.61857, 0, 0, 0, 0, 100, 0),
(26686, 3, -9871.86, 911.8401, 31.61857, 0, 0, 0, 0, 100, 0),
(26686, 4, -9871.723, 912.4184, 31.54924, 0, 0, 0, 0, 100, 0),
(26686, 5, -9872.714, 911.4499, 31.66533, 0, 0, 0, 0, 100, 0),
(26686, 6, -9872.421, 910.9823, 31.72148, 0, 0, 0, 0, 100, 0),
(26686, 7, -9872.412, 911.5516, 31.65312, 0, 0, 0, 0, 100, 0),
(26686, 8, -9874.595, 910.4224, 31.92753, 0, 0, 0, 0, 100, 0);

UPDATE creature SET MovementType=2 WHERE guid=26687;

DELETE FROM creature_addon WHERE guid=26687;
INSERT INTO creature_addon VALUES 
(26687, 26687, 0, 65536, 1, 0, "79488");

DELETE FROM waypoint_data WHERE id=26687;
INSERT INTO waypoint_data VALUES 
(26687, 0, -9836.479, 912.0322, 30.89999, 0, 0, 0, 0, 100, 0),
(26687, 1, -9841.663, 911.6262, 30.66427, 0, 0, 0, 0, 100, 0),
(26687, 2, -9837.219, 912.1494, 30.91403, 0, 0, 0, 0, 100, 0),
(26687, 3, -9843.876, 910.3632, 30.56576, 0, 0, 0, 0, 100, 0),
(26687, 4, -9837.111, 911.3477, 30.81784, 0, 0, 0, 0, 100, 0);

UPDATE creature SET MovementType=2 WHERE guid=26688;

DELETE FROM creature_addon WHERE guid=26688;
INSERT INTO creature_addon VALUES 
(26688, 26688, 0, 65536, 1, 0, "79488");

DELETE FROM waypoint_data WHERE id=26688;
INSERT INTO waypoint_data VALUES 
(26688, 0, -9854.194, 929.9867, 31.61386, 0, 0, 0, 0, 100, 0),
(26688, 1, -9851.633, 930.8834, 31.76864, 0, 0, 0, 0, 100, 0),
(26688, 2, -9854.356, 929.868, 31.57992, 0, 0, 0, 0, 100, 0),
(26688, 3, -9857.463, 931.9807, 31.66879, 0, 0, 0, 0, 100, 0),
(26688, 4, -9853.902, 928.665, 31.64828, 0, 0, 0, 0, 100, 0);

UPDATE creature SET MovementType=2 WHERE guid=26689;

DELETE FROM creature_addon WHERE guid=26689;
INSERT INTO creature_addon VALUES 
(26689, 26689, 0, 65536, 1, 0, "79488");

DELETE FROM waypoint_data WHERE id=26689;
INSERT INTO waypoint_data VALUES 
(26689, 0, -9855.109, 893.8681, 30.49529, 0, 0, 0, 0, 100, 0),
(26689, 1, -9851.948, 893.0037, 29.86101, 0, 0, 0, 0, 100, 0),
(26689, 2, -9855.744, 893.7861, 30.64763, 0, 0, 0, 0, 100, 0),
(26689, 3, -9851.506, 894.04, 29.75506, 0, 0, 0, 0, 100, 0),
(26689, 4, -9855.234, 890.4098, 30.88646, 0, 0, 0, 0, 100, 0),
(26689, 5, -9856.43, 894.5801, 30.81219, 0, 0, 0, 0, 100, 0),
(26689, 6, -9856.096, 893.7764, 30.73162, 0, 0, 0, 0, 100, 0),
(26689, 7, -9856.859, 894.4873, 30.91521, 0, 0, 0, 0, 100, 0);

UPDATE creature_template SET gossip_menu_id=0, npcflag=0 WHERE entry=42383;

UPDATE creature_template SET gossip_menu_id=0, npcflag=0 WHERE entry=42384;

UPDATE creature_template SET gossip_menu_id=0, npcflag=0 WHERE entry=42386;

UPDATE creature_template SET gossip_menu_id=0, npcflag=0 WHERE entry=42391;

DELETE FROM gossip_menu_option WHERE menu_id=11635 AND id=0;
INSERT INTO gossip_menu_option VALUES 
(11635, 0, 0, "Did you see who killed the Furlbrows?", 42370, 1, 1, 0, 0, 0, 0, 0, "", 0);

DELETE FROM gossip_menu_option WHERE menu_id=11635 AND id=1;
INSERT INTO gossip_menu_option VALUES 
(11635, 1, 0, "Maybe a couple copper will loosen your tongue. Now tell me, did you see who killed the Furlbrows?", 42371, 1, 1, 0, 0, 0, 0, 2, "Are you sure you want to give this hobo money?", 42373);

UPDATE npc_text SET BroadcastTextID1=42366, BroadcastTextID2=42367, BroadcastTextID3=42368, BroadcastTextID4=42369 WHERE ID=16250;

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=11635 AND SourceEntry=0 AND SourceId=0 AND ConditionTypeOrReference=9 AND ConditionValue1=26209;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ConditionTypeOrReference, ConditionValue1) VALUES (15, 11635, 9, 26209);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=11635 AND SourceEntry=1 AND SourceId=0 AND ConditionTypeOrReference=9 AND ConditionValue1=26209;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES (15, 11635, 1, 9, 26209);





