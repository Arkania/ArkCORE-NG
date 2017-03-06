
-- quest 11129
UPDATE quest_template SET RequiredNpcOrGo1=23616, RequiredNpcOrGo2=0, RequiredNpcOrGoCount1=1, RequiredNpcOrGoCount2=0 WHERE Id=11129;

DELETE FROM `smart_scripts` WHERE `entryorguid`=36845;

update creature set spawndist=0, MovementType=0 where guid in (94085, 108866);

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Borstennacken", QuestGiverTargetName_loc3="Stacheleber der Borstennacken" WHERE Id=14452;

UPDATE quest_template SET RequiredNpcOrGo1=-202112, RequiredNpcOrGoCount1=4 WHERE Id=24852;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Grull Falkenwind zurück." WHERE Id=24852;

update gameobject_template set type=10, flags=0, data0=980, data1=24852, data10=0, AIName="", ScriptName="go_quilboar_cage_202112" where entry=202112;

delete from creature_text where entry=38345 and groupid=0 ;
insert into creature_text values
(38345, 0, 0, "Thank the Earth Mother!", 12, 0, 100, 0, 0, 0, "", 38278),
(38345, 0, 1, "I can move again!", 12, 0, 100, 0, 0, 0, "", 38279),
(38345, 0, 2, "The quilboar will pay!", 12, 0, 100, 0, 0, 0, "", 38280);

UPDATE quest_template SET PrevQuestId=14458 WHERE Id in (3091, 3092, 3093, 3094, 14455, 14456, 27014, 27015);
UPDATE quest_template SET PrevQuestId=14458 WHERE Id=14456;
UPDATE quest_template SET PrevQuestId=14456 WHERE Id=14459;
UPDATE quest_template SET PrevQuestId=14455 WHERE Id=14461;
UPDATE quest_template SET PrevQuestId=14461 WHERE Id=14460;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Adana Donnerhorn zurück.", QuestGiverTextWindow_loc3="Dornenrufer der Borstennacken", QuestGiverTargetName_loc3="Dornenrufer der Borstennacken" WHERE Id=14455;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Adana Donnerhorn zurück." WHERE Id=14456;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Adana Donnerhorn zurück.", QuestGiverTextWindow_loc3="Gepanzerte Kampfeber", QuestGiverTargetName_loc3="Gepanzerte Kampfeber" WHERE Id=14459;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Häuptling Falkenwind im Camp Narache zurück." WHERE Id=14460;
UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="Ich wußte, dass Ihr 'Zuverlässiger Schuss' schnell lernen würdet.  Ich freue mich auf die Zeit, wenn ich Euch mehr über die Wege des Jägers zeigen kann.", RequestItemsText_loc3="Na? Habt Ihr es ausprobiert?", CompletedText_loc3="Kehrt zu Ashley Blank bei der Abtei von Nordhain zurück.", QuestGiverTextWindow_loc3="Trainingsattrappe", QuestGiverTargetName_loc3="Trainingsattrappe" WHERE Id=26917;
UPDATE locales_quest SET OfferRewardText_loc3="Ihr habt Eure Sache gut gemacht,$N. Kehrt zu mir zurück, wenn Ihr weitere Ausbildung benötigt.", CompletedText_loc3="Kehrt zu Lanka Farshot im Camp Narache zurück.", ObjectiveText1_loc3="Übt 'Zuverlässiger Schuss'.", QuestGiverTextWindow_loc3="Trainingsattrappe", QuestGiverTargetName_loc3="Trainingsattrappe" WHERE Id=27021;

update creature set id=43599 where id=36942 and guid in (92333, 92549, 107943, 108347, 108517, 108857, 109076);

UPDATE quest_template SET Flags=0, QuestGiverPortrait=3841 WHERE Id=24861;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Sprecht mit Häuptling Falkenwind.", QuestGiverTextWindow_loc3="Letzte Opfergabe für Großmutter Falkenwind.", QuestGiverTargetName_loc3="Großmutter Falkenwind" WHERE Id=24861;
UPDATE quest_template SET QuestGiverTextWindow="Final offering at Greatmother Hawkwind's grave", QuestGiverTargetName="Greatmother Hawkwind" WHERE Id=24861;

delete from item_script_names where Id=50465;
insert into item_script_names values
(50465, "item_water_pitcher_50465");

update creature_template set InhabitType=4, AIName="", ScriptName="npc_eagle_spirit_36790" where entry=36790;

UPDATE locales_quest SET EndText_loc3="", ObjectiveText1_loc3="Gnolle der Bleichmähnen", ObjectiveText2_loc3="", ObjectiveText3_loc3="", QuestGiverTextWindow_loc3="Gnoll der Bleichmähnen", QuestGiverTargetName_loc3="Gnoll der Bleichmähnen" WHERE Id=14438;
UPDATE quest_template SET PrevQuestId=24215, QuestGiverPortrait=550 WHERE Id=14438;
UPDATE creature_template SET KillCredit1=42354 WHERE entry=5786;

delete from creature_queststarter where quest=6361;
insert into creature_queststarter values
(3079, 6361);

delete from creature_questender where quest=6361;
insert into creature_questender values
(40809, 6361);
	
UPDATE quest_template SET PrevQuestId=20440 WHERE Id=24440;


	
