
UPDATE quest_template SET NextQuestIdChain=28167 WHERE Id=27670;

UPDATE quest_template SET PrevQuestId=27670, NextQuestIdChain=27671 WHERE Id=28167;

UPDATE locales_quest SET OfferRewardText_loc3="Es wird Nevin freuen, dass Ihr so vielen Überlebenden helfen konntet. Ich kann immer noch nicht fassen, dass Ihr trotz der Strahlung hier unten noch so stark seid. Ihr habt ja den Zustand der anderen Überlebend engesehen.$B$BAb mit Euch zum Laderaum zur Dekontamination.
", QuestGiverTextWindow_loc3="Überlebender", QuestGiverTargetName_loc3="Überlebender" WHERE Id=27671;

UPDATE locales_quest SET OfferRewardText_loc3="Hat Nevin Euch vorgeschickt? Das bedeutet, er bereitet sich darauf vor, die Mission zu beenden. Doch es müssen immer noch Überlebende gerettet werden. Wir müssen ihnen helfen!
" WHERE Id=28167;

UPDATE locales_quest SET OfferRewardText_loc3="Gut gemacht, $n. Meine Männer werden jetzt übernehmen. Konzentrieren wir uns darauf, die anderen Überlebenden heraus zu bringen.", QuestGiverTextWindow_loc3="Wahnsinniger Lepragnome", QuestGiverTargetName_loc3="Wahnsinniger Lepragnome" WHERE Id=27670;

UPDATE creature_template SET unit_flags=256 WHERE entry=45847;

delete from gameobject where id=205077 and guid=184296;

UPDATE creature_template SET ScriptName="npc_safe_operative_45847" WHERE entry=45847;

UPDATE creature_template SET ScriptName="npc_crazed_leper_gnome_46391" WHERE entry=46391;

Update `quest_template` SET `Method`=2,`Flags`=0 WHERE `Id` =26342;

DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=42291;

INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(42291,0,0,1,8,0,100,1,79781,0,0,0,33,42796,0,0,0,0,0,7,0,0,0,0,0,0,0,'Crushcog Sentry-Bot - On spell hit - Give kill credit for quest 26342'),
(42291,0,1,2,61,0,100,0,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Crushcog Sentry-Bot - On smart Link - Stop attack'),
(42291,0,2,3,61,0,100,0,0,0,0,0,1,1,100,0,0,0,0,1,0,0,0,0,0,0,0,'Crushcog Sentry-Bot - On smart Link - Say Line 1'),
(42291,0,3,0,61,0,100,0,0,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0,0,0,0,'Crushcog Sentry-Bot - On smart Link - Despawn');

DELETE FROM creature_text WHERE entry=47836 AND groupid=0 AND id=0;
INSERT INTO creature_text VALUES 
(47836, 0, 0, "You can follow me to the Loading Room, $n.", 12, 0, 100, 25, 0, 0, "S.A.F.E. Operative Say", 48091);

delete from creature_equip_template where entry=47836;
insert into creature_equip_template values 
(47836, 1, 0, 0, 52355);

DELETE FROM waypoint_data WHERE id=4783600;
INSERT INTO waypoint_data VALUES 
(4783600, 0, -4996.5, 770.129, 288.485, 0, 0, 0, 0, 100, 0),
(4783600, 1, -5008.77, 770.319, 286.598, 0, 0, 0, 0, 100, 0),
(4783600, 2, -5027.55, 771.996, 283.579, 0, 0, 0, 0, 100, 0),
(4783600, 3, -5049.6, 773.777, 283.232, 0, 0, 0, 0, 100, 0),
(4783600, 4, -5071.89, 775.478, 283.29, 0, 0, 0, 0, 100, 0),
(4783600, 5, -5092.22, 777.152, 283.314, 0, 0, 0, 0, 100, 0),
(4783600, 6, -5108.16, 773.712, 285.236, 0, 0, 0, 0, 100, 0),
(4783600, 7, -5122.66, 768.547, 287.353, 0, 0, 0, 0, 100, 0),
(4783600, 8, -5142.31, 763.151, 287.395, 0, 0, 0, 0, 100, 0),
(4783600, 9, -5155.15, 762.659, 287.395, 0, 0, 0, 0, 100, 0),
(4783600, 10, -5170.09, 765.921, 285.474, 0, 0, 0, 0, 100, 0);

UPDATE creature SET zoneId=1, areaId=5495, position_x=-5141.852, position_y=754.425, position_z=287.3951, orientation=1.716147 WHERE id=45847 AND guid=61539;
UPDATE creature SET zoneId=1, areaId=5495, position_x=-5141.434, position_y=756.3821, position_z=287.3951, orientation=4.747789 WHERE id=46391 AND guid=62456;

DELETE FROM creature WHERE guid=4018;
INSERT INTO creature VALUES 
(4018, 35905, 654, 0, 0, 1, 171, 0, 0, 0, -1800.37, 1407.18, 20.0265, 4.70254, 300, 0, 0, 498, 104, 0, 0, 0, 0);




