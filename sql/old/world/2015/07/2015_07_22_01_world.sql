
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Jona Eisenquell in Ambossar zurück." WHERE Id=24474;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Grundel Harkin in Ambossar zurück." WHERE Id=24477;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Grundel Harkin in Ambossar zurück." WHERE Id=24486;
UPDATE locales_quest SET CompletedText_loc3="Kehrt zurück zu Thorgas Grimson in Ambossar.", ObjectiveText1_loc3="Übt 'Zuverlässiger Schuss'" WHERE Id=24530;
UPDATE locales_quest SET EndText_loc3="", QuestGiverTextWindow_loc3="Trollwelpe der Frostmähnen", QuestGiverTargetName_loc3="Trollwelpe der Frostmähnen" WHERE Id=182;

update creature_loot_template set ChanceOrQuestChance=-90 where entry=37105 and item=49751;

update creature_text set BroadcastTextID=36962 where entry=37108 and groupid=0 and id=0;
update creature_text set BroadcastTextID=36958 where entry=37108 and groupid=1 and id=0;
update creature_text set BroadcastTextID=36959 where entry=37108 and groupid=2 and id=0;

update creature_text set BroadcastTextID=36957 where entry=37173 and groupid=0 and id=0;
update creature_text set BroadcastTextID=36960 where entry=37173 and groupid=1 and id=0;
update creature_text set BroadcastTextID=36961 where entry=37173 and groupid=2 and id=0;

update creature_text set BroadcastTextID=36963 where entry=37174 and groupid=0 and id=0;
update creature_text set BroadcastTextID=36964 where entry=37174 and groupid=1 and id=0;
update creature_text set BroadcastTextID=36965 where entry=37174 and groupid=2 and id=0;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Lehrling Soren in Weißbarts Lager zurück." WHERE Id=24489;

update creature_text set BroadcastTextID=36953 where entry=808 and groupid=0 and id=0;

-- Grik'nir the Cold SAI
SET @ENTRY := 808;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,2000,4500,12000,15000,11,79895,0,0,0,0,0,2,0,0,0,0,0,0,0,"Cast Frost Strike"),
(@ENTRY,0,1,0,4,0,100,1,0,0,0,0,11,6957,0,0,0,0,0,1,0,0,0,0,0,0,0,"Cast Frostmane Strength on Aggro"),
(@ENTRY,0,2,0,0,0,100,0,0,0,15000,30000,1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,"Npc - Event - Action (phase) (dungeon difficulty)");

UPDATE locales_quest SET EndText_loc3="" WHERE Id=218;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Milo Zwickrädchen im Eisklammtal zurück." WHERE Id=24492;

delete from gameobject_loot_template where entry=201706 and item=62327;
update gameobject_loot_template set ChanceOrQuestChance=-62.3 where entry=201706 and item=49754;

delete from waypoint_data where id=3719801;
insert into waypoint_data (id, point, position_x, position_y, position_z, move_flag) values
(3719801, 1, -6220.035645, 296.816772, 409.775787, 1),
(3719801, 2, -6180.738281, 271.849091, 435.231506, 1),
(3719801, 3, -6167.073730, 213.735809, 470.028137, 1),
(3719801, 4, -6134.929688, 124.723755, 507.195953, 1),
(3719801, 5, -6075.491699, 73.982384, 510.407410, 1),
(3719801, 6, -5984.715820, -9.166074, 470.231415, 1),
(3719801, 7, -5908.320313, -225.218124, 490.649323, 1),
(3719801, 8, -5727.785156, -416.732208, 466.876831, 1),
(3719801, 9, -5647.638672, -482.040649, 399.289917, 1),
(3719801, 10, -5629.615234, -484.758545, 396.980530, 1),
(3719801, 11, -5618.415527, -484.724670, 396.980530, 1);

update creature_text set BroadcastTextID=37115 where entry=37198 and groupid=0 and id=0;
update creature_text set BroadcastTextID=37117 where entry=37198 and groupid=1 and id=0;
update creature_text set BroadcastTextID=43112 where entry=37198 and groupid=2 and id=0;
update creature_text set BroadcastTextID=37119 where entry=37198 and groupid=3 and id=0;
update creature_text set BroadcastTextID=37118 where entry=37198 and groupid=4 and id=0;
update creature_text set BroadcastTextID=43113 where entry=37198 and groupid=5 and id=0;
update creature_text set BroadcastTextID=43115 where entry=37198 and groupid=6 and id=0;

update creature set position_x=-5684.788, position_y=-497.707, position_z=396.436 where guid=12829 and id=51912;

delete from creature_text where entry=51912 and groupid=0 and id=0;
insert into creature_text value (51912, 0, 0, "Hello!", 12, 0, 100, 0, 0, 0, "Greetings", 48403);


