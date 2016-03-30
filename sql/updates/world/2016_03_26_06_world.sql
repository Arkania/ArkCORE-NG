

-- fix issue #116 part 6
-- http://ru.wowhead.com/quest=26965 - bugged
-- https://www.youtube.com/watch?v=BifFEKPVbJk

delete from creature where id in (39117, 44629, 44636);

delete from creature where guid=53702 and id=44640;

UPDATE locales_quest SET OfferRewardText_loc3="Apostolosnub ist zurückgekehrt! In einem Stück!$B$BVerteidiger von Silberwald! Erlöser der Horde! Apostolosnub, Eure Tapferkeit muss belohnt werden!", CompletedText_loc3="Kehrt zu Großexekutor Mortuus in der Kommandozentrale der Verlassenen im Silberwald zurück." WHERE Id=26989;

UPDATE quest_template SET PrevQuestId=26965 WHERE Id=26989;

UPDATE locales_quest SET OfferRewardText_loc3="Schmerz im Überfluss, mein Freund! Das Land selbst droht, uns zu verschlingen und dennoch bestehen wir fort. Ich frage mich, warum das so ist? Mit diesem Verhängniskraut, den Eingeweiden und dem geronnenen Blut, das T'Veen benötigt, haben wir vielleicht etwas Geeignetes, das wir an die Frontlinie der Verlassenen senden können.", CompletedText_loc3="Kehrt zu Apotheker Welkblum bei der Kommandozentrale der Verlassenen im Silberwald zurück." WHERE Id=26992;

UPDATE quest_template SET PrevQuestId=26965 WHERE Id=26992;

UPDATE quest_template SET PrevQuestId=26965 WHERE Id=26995;

UPDATE locales_quest SET OfferRewardText_loc3="Ich sehe alles, $N. Durch Agatha entgeht mir nichts.", CompletedText_loc3="Sprecht mit Fürstin Sylvanas Windläufer, bei der Kommandozentrale der Verlassenen im Silberwald.", QuestGiverTextWindow_loc3="Als Mensch getötet und als Verlassener erweckt.", QuestGiverTargetName_loc3="Erweckter Verlassener" WHERE Id=27097;

UPDATE quest_template SET PrevQuestId=27096, Flags=0 WHERE Id=27097;

UPDATE locales_quest SET OfferRewardText_loc3="Na, wenn das nicht Apostolosnub ist!$B$BIch hoffe, Ihr seid bereit zum Kampf, weil das ist alles, was Euch in diesem Höllenloch erwartet. Wir sind mitten im umkämpften Gebiet und diese Straßenköter von Worgen wollen nicht nachgeben!" WHERE Id=27290;

UPDATE quest_template SET PrevQuestId=27195 WHERE Id=27290;

UPDATE quest_template SET PrevQuestId=27098 WHERE Id=27180;

UPDATE quest_template SET PrevQuestId=26998 WHERE Id=27039;

UPDATE quest_template SET PrevQuestId=27577 WHERE Id=28089;

-- Creature Entry: 44365 (Lady Sylvanas Windrunner)
delete from creature_text where entry=44365 and groupid between 0 and 10;
insert into creature_text values 
(44365,  0, 0, "Where is that ogre-headed buffoon?", 12, 0, 100, 6, 0, 20459, "", 44695),
(44365,  1, 0, "Ah, speak of the devil...", 12, 0, 100, 1, 0, 20460, "", 44696),
(44365,  2, 0, "Warchief, so glad you could make it.", 12, 0, 100, 1, 0, 20461, "", 44701),
(44365,  3, 0, "With the death of the Lich King, many of the more intelligent Scourge became... unemployed. Those 'fiends,' as you so delicately put it, are called val'kyr. They are under my command now...", 12, 0, 100, 0, 0, 20462, "", 44702),
(44365,  4, 0, "...and they are part of the reason that I asked to see you.", 12, 0, 100, 1, 0, 20463, "", 44703),
(44365,  5, 0, "Very well, Warchief. I have solved the plight of the Forsaken!", 12, 0, 100, 5, 0, 20464, "", 44705),
(44365,  6, 0, "As a race, we Forsaken are unable to procreate.", 12, 0, 100, 274, 0, 20465, "", 44706),
(44365,  7, 0, "With the aid of the val'kyr, we are now able to take the corpses of the fallen and create new Forsaken.", 12, 0, 100, 0, 0, 20466, "", 44707),
(44365,  8, 0, "Agatha, show the Warchief!", 12, 0, 100, 22, 0, 20467, "", 44709),
(44365,  9, 0, "Warchief, without these new Forsaken my people would die out... Our hold upon Gilneas and northern Lordaeron would crumble.", 12, 0, 100, 0, 0, 20468, "", 44715),
(44365, 10, 0, "Isn't it obvious, Warchief? I serve the Horde.", 12, 0, 100, 66, 0, 20469, "", 44718);

-- NPC ID: 44629 (Garrosh Hellscream)
delete from creature_text where entry=44629 and groupid between 0 and 9;
insert into creature_text values 
(44629, 0, 0, "This better be important, Sylvanas. You know how I detest this place and its foul stench. Why have you called for me?", 12, 0, 100, 0, 0, 20496, "", 44699),
(44629, 1, 0, "And more importantly, what are those Scourge fiends doing here?", 12, 0, 100, 0, 0, 20497, "", 44700),
(44629, 2, 0, "Get on with it, Sylvanas.", 12, 0, 100, 1, 0, 20498, "", 44704),
(44629, 3, 0, "What you have done here, Sylvanas... it goes against the laws of nature. Disgusting is the only word I have to describe it.", 12, 0, 100, 0, 0, 20499, "", 44714),
(44629, 4, 0, "Have you given any thought to what this means, Sylvanas?", 12, 0, 100, 6, 0, 20500, "", 44716),
(44629, 5, 0, "What difference is there between you and the Lich King now?", 12, 0, 100, 6, 0, 20501, "", 44717),
(44629, 6, 0, "Watch your clever mouth, bitch.", 12, 0, 100, 397, 0, 20502, "", 44719),
(44629, 7, 0, "Cromush, you stay behind and make sure the Banshee Queen is well \"guarded.\" I will be expecting a full report when next we meet.", 12, 0, 100, 0, 0, 20503, "", 44720),
(44629, 8, 0, "Remember, Sylvanas, eventually we all have to stand before our maker and face judgment. Your day may come sooner than others'....", 12, 0, 100, 0, 0, 20504, "", 44721);

-- Entry: 44640 (High Warlord Cromush)
delete from creature_text where entry=44640 and groupid in (0, 1);
insert into creature_text values 
(44640, 0, 0, "ABBERATION!", 12, 0, 100, 5, 0, 0, "", 44713),
(44640, 1, 0, "As you command, Warchief!", 12, 0, 100, 66, 0, 0, "", 44738);

SET @GUID=5405701;
DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, 1403.424, 1068.805, 60.47655, 4.074228, 500, 1),
(@GUID, 1, 1403.424, 1068.805, 60.47655, 4.074228, 0, 1),
(@GUID, 2, 1407.501, 1081.586, 60.47925, 1.364602, 0, 1),
(@GUID, 3, 1406.427, 1086.022, 60.47925, 1.808352, 0, 1),
(@GUID, 4, 1400.381, 1089.976, 59.97032, 2.562335, 0, 1),
(@GUID, 5, 1378.655, 1081.227, 52.49874, 3.524448, 0, 1),
(@GUID, 6, 1371.423, 1073.132, 53.25177, 4.097788, 0, 1),
(@GUID, 7, 1371.143, 1055.494, 53.11386, 4.698616, 0, 1),
(@GUID, 8, 1377.207, 1046.097, 53.56214, 5.307295, 0, 1),
(@GUID, 9, 1377.207, 1046.097, 53.56214, 4.376599, 500, 1);

SET @GUID=5405702;
DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, 1377.207, 1046.097, 53.56214, 4.376599, 500, 1),
(@GUID, 1, 1377.207, 1046.097, 53.56214, 5.307295, 0, 1),
(@GUID, 2, 1371.143, 1055.494, 53.11386, 4.698616, 0, 1),
(@GUID, 3, 1371.423, 1073.132, 53.25177, 4.097788, 0, 1),
(@GUID, 4, 1378.655, 1081.227, 52.49874, 3.524448, 0, 1),
(@GUID, 5, 1400.381, 1089.976, 59.97032, 2.562335, 0, 1),
(@GUID, 6, 1406.427, 1086.022, 60.47925, 1.808352, 0, 1),
(@GUID, 7, 1407.501, 1081.586, 60.47925, 1.364602, 0, 1),
(@GUID, 8, 1403.424, 1068.805, 60.47655, 4.074228, 0, 1),
(@GUID, 9, 1403.424, 1068.805, 60.47655, 1.189128, 500, 1);

update creature_template set AIName="", ScriptName="npc_grand_executor_mortuus_44615" where entry=44615;

update creature_addon set auras="" where guid=35111;

update creature_template_addon set auras="" where entry=44608; -- ID - 83988 Apply Quest Invis Zone 3	-- [0] Spell ID: 83173 (Raise Forsaken)

DELETE FROM creature_addon WHERE guid=37022;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Kriegshäuptling Garrosh Höllschrei", QuestGiverTargetName_loc3="Garrosh Höllschrei" WHERE Id=26965;

delete from creature where id=44630 and guid in (54038, 54039, 54040);

delete from spell_script_names where spell_id=83173;
insert into spell_script_names values
(83173, "spell_raise_forsaken_83173");

UPDATE creature_template SET InhabitType=3, HoverHeight=2.4 WHERE entry=44608;

UPDATE creature_template SET InhabitType=3, HoverHeight=1.0 WHERE entry=44592;

delete from spell_script_names where spell_id=83149;
insert into spell_script_names values
(83149, "spell_forsaken_trooper_master_script_83149");

update creature set spawntimesecs=15 where id in (44592, 44593);

update creature_template set AIName="", ScriptName="npc_fallen_human_44592" where entry=44592;
update creature_template set AIName="", ScriptName="npc_fallen_human_44592" where entry=44593;



