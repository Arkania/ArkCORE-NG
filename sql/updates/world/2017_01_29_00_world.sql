
UPDATE locales_quest SET OfferRewardText_loc3="Gern geschehen, Boss!$B$BKommt jederzeit zurück, wenn Ihr mehr lernen wollt. Ich bringe Euch alles bei, was ich weiß.", CompletedText_loc3="Sprecht mit Lawinus Maximus im Hauptgeschäftssitz der HGK auf Kezan.", ObjectiveText1_loc3="Übt urtümlicher Schlag", QuestGiverTextWindow_loc3="Trainingsattrappe", QuestGiverTargetName_loc3="Trainingsattrappe" WHERE Id=14011;

UPDATE creature_template SET KillCredit1=44175 WHERE entry=48305;

DELETE FROM gossip_menu_option WHERE menu_id=10595 AND id=0;
INSERT INTO gossip_menu_option VALUES 
(10595, 0, 0, "Megs, I misplaced the keys to the cruiser. Did you find them?", 35123, 1, 1, 0, 0, 0, 0, 0, "", 0);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=10595 AND SourceEntry=0 AND SourceId=0 AND ConditionTypeOrReference=8 AND ConditionValue1=14071;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ConditionTypeOrReference, ConditionValue1, Comment) VALUES (15, 10595, 8, 14071, "allow receive key to hod rod after finish quest 14071");

delete from creature_queststarter where id=34874 and quest=28607;

delete from creature_questender where id=34874 and quest=28607;

UPDATE creature_template SET unit_flags2=2048, dynamicflags=0 WHERE entry=34874;

-- Gappy Silvertooth SAI
SET @ENTRY := 35126;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,62,0,100,0,10620,0,0,0,85,66780,0,0,0,0,0,7,0,0,0,0,0,0,0,"Gappy Silvertooth - On Gossip Option 0 Selected - Invoker Cast '<Spell not found!>'"),
(@ENTRY,0,1,0,62,0,100,0,10620,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Gappy Silvertooth - On Gossip Option 0 Selected - Close Gossip");

-- Szabo SAI
SET @ENTRY := 35128;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,62,0,100,0,10622,0,0,0,85,66781,0,0,0,0,0,7,0,0,0,0,0,0,0,"Szabo - On Gossip Option 0 Selected - Invoker Cast '<Spell not found!>'"),
(@ENTRY,0,1,0,62,0,100,0,10622,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Szabo - On Gossip Option 0 Selected - Close Gossip");

-- Missa Spekkies SAI
SET @ENTRY := 35130;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,62,0,100,0,10624,0,0,0,85,66782,0,0,0,0,0,7,0,0,0,0,0,0,0,"Missa Spekkies - On Gossip Option 0 Selected - Invoker Cast '<Spell not found!>'"),
(@ENTRY,0,1,0,62,0,100,0,10624,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Missa Spekkies - On Gossip Option 0 Selected - Close Gossip");

UPDATE creature SET MovementType=2 WHERE guid=285463;

UPDATE creature SET position_x=-8243.75, position_y=1455.8, position_z=40.927, orientation=.867 WHERE guid=285463;




