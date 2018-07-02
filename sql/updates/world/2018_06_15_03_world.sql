

-- quest 931

-- Denalan
SET @ENTRY := 208001;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,0,0,0,0,83,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Denalan - On Script - Remove Npc Flag Questgiver"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,0,0,1,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Denalan - On Script - Say Line 2"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,9508.02,715.749,1255.89,0.0,"Denalan - On Script - Move To Position"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,1000,1000,0,0,69,0,0,0,0,0,0,8,0,0,0,9507.66,718.009,1255.89,0.0,"Denalan - On Script - Move To Position"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,1000,1000,0,0,69,0,0,0,0,0,0,8,0,0,0,9505.56,719.088,1256.2,0.0,"Denalan - On Script - Move To Position"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,0,2000,2000,0,0,5,16,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Denalan - On Script - Play Emote 16"),
(@ENTRY,@SOURCETYPE,6,0,0,0,100,0,3500,3500,0,0,1,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Denalan - On Script - Say Line 3"),
(@ENTRY,@SOURCETYPE,7,0,0,0,100,0,3000,3000,0,0,69,0,0,0,0,0,0,8,0,0,0,9506.92,713.766,1255.89,0.0,"Denalan - Script - Move"),
(@ENTRY,@SOURCETYPE,8,0,0,0,100,0,500,500,0,0,70,60,0,0,0,0,0,14,67984,7510,0,0.0,0.0,0.0,0.0,"Denalan - On Script - Respawn Closest Gameobject 'Sprouted Frond'"),
(@ENTRY,@SOURCETYPE,9,0,0,0,100,0,0,0,0,0,70,60,0,0,0,0,0,14,42936,7510,0,0.0,0.0,0.0,0.0,"Denalan - On Script - Respawn Closest Gameobject 'Sprouted Frond'"),
(@ENTRY,@SOURCETYPE,10,0,0,0,100,0,0,0,0,0,70,60,0,0,0,0,0,14,30276,7510,0,0.0,0.0,0.0,0.0,"Denalan - On Script - Respawn Closest Gameobject 'Sprouted Frond'"),
(@ENTRY,@SOURCETYPE,11,0,0,0,100,0,2500,2500,0,0,66,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Denalan - On Script - Reset Orientation"),
(@ENTRY,@SOURCETYPE,12,0,0,0,100,0,0,0,0,0,82,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Denalan - On Script - Add Npc Flag Questgiver");

