
delete from creature where id=10489 and guid in (151695, 151789);

update gameobject_template set flags=32, data0=0, data1=0, data2=0, AIName="", ScriptName="" where entry in (175611,175612,175613,175614,175615,175617,175618,175620);
update gameobject_template set flags=32, data0=1, data1=0, data2=0, AIName="", ScriptName="" where entry in (175619, 175616, 179724);

-- door: object=175570
-- Brazier: object=175564
-- map 289

-- move all mobs to phase 2 that later should be spawned by script..
update creature set phaseMask=2 where id in (10479, 10497, 10506, 11258, 11263, 11284, 14511, 14512, 14513, 14514, 14518, 14519, 14520, 14521, 16118, 16119, 16120);

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Doktor Theolen Krastinov", QuestGiverTargetName_loc3="Doktor Theolen Krastinov" WHERE Id=5382;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Eva Sarkhoff zurück.", QuestGiverTextWindow_loc3="Doktor Theolen Krastinov", QuestGiverTargetName_loc3="Doktor Theolen Krastinov" WHERE Id=27146;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Eva Sarkhoff zurück.", QuestGiverTextWindow_loc3="Kirtonos der Herold", QuestGiverTargetName_loc3="Kirtonos der Herold" WHERE Id=27147;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Alexi Barov zurück." WHERE Id=27140;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Alexi Barov zurück.", QuestGiverTextWindow_loc3="Ras Frostraunen", QuestGiverTargetName_loc3="Ras Frostraunen" WHERE Id=27142;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Weldon Barov zurück." WHERE Id=27143;

UPDATE locales_quest SET OfferRewardText_loc3="Ich habe nichts gegen die Ritter der Schwarzen Klinge, aber Koltira muss sich im Klaren darüber sein, für wen er arbeitet. Seine Loyalität muss einzig und allein der Horde gelten.$B$BGenauer gesagt, den Verlassenen.$B$BIch würde mich nicht darauf verlassen, Koltira bald wieder zu sehen. Jetzt, da ich ihn habe ... könnt Ihr Euch sicher sein, dass alle seine Verbindungen zu irgendwelchen Allianzlern vollständig zerstört werden.", CompletedText_loc3="Kehrt zu Fürstin Sylvanas Windläufer bei Andorhal in den Westlichen Plageländern zurück.", ObjectiveText1_loc3="Zeuge der Abrechnung", QuestGiverTextWindow_loc3="Fürstin Sylvanas Windläufer", QuestGiverTargetName_loc3="Fürstin Sylvanas Windläufer" WHERE Id=27144;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Weldon Barov zurück.", QuestGiverTextWindow_loc3="Verseuchte Jungtiere", QuestGiverTargetName_loc3="Verseuchtes Jungtier" WHERE Id=27145;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Lucien Sarkhoff zurück." WHERE Id=27148;

-- The Journal of Jandice Barov appears after killing Jandice Barov in Scholomance. 
-- 187742	180794	289	1	1	267,443	69,4347	95,8397	1,71027	0	0	0,754661	0,656115	43200	255	1
delete from gameobject where guid=187742 and id=180794;

-- http://www.wowhead.com/object=176944/old-treasure-chest
update gameobject_template set flags=0 where entry=176944;

-- https://cata-twinhead.twinstar.cz/?object=175564
update gameobject_template set flags=0 where entry=175564;

-- https://cata-twinhead.twinstar.cz/?npc=10506
-- Pathing for Kirtonos the Herald Entry: 10506
SET @PATH := 105061;
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO waypoint_data VALUES
(@PATH,1,316.7087,71.26834,104.5843,0,0,1,0,100,0),
(@PATH,2,321.1605,72.80973,104.6676,0,0,1,0,100,0),
(@PATH,3,332.3713,77.98991,105.8621,0,0,1,0,100,0),
(@PATH,4,333.3254,86.60159,106.6399,0,0,1,0,100,0),
(@PATH,5,334.1263,101.6836,106.8343,0,0,1,0,100,0),
(@PATH,6,331.0458,114.5935,106.3621,0,0,1,0,100,0),
(@PATH,7,329.5439,126.7019,106.1399,0,0,1,0,100,0),
(@PATH,8,335.2471,136.546,105.7232,0,0,1,0,100,0),
(@PATH,9,343.21,139.9459,107.6399,0,0,1,0,100,0),
(@PATH,10,364.3288,140.9012,109.9454,0,0,1,0,100,0),
(@PATH,11,362.676,115.6384,110.3065,0,0,1,0,100,0),
(@PATH,12,341.7896,91.9439,107.1676,0,0,1,0,100,0),
(@PATH,13,313.4945,93.45945,104.0565,0,0,1,0,100,0),
(@PATH,14,306.3839,93.61675,104.0565,0,0,1,0,100,0);

delete from creature where guid=152069 and id=10508;

delete from gameobject where guid=184276 and id=174626;



