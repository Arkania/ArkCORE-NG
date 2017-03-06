

delete from conditions where SourceTypeOrReferenceId=19 and SourceEntry=28966 and ConditionTypeOrReference=12 and ConditionValue1=12;
insert into conditions values 
(19, 0, 28966, 0, 0, 12, 0, 12, 0, 0, 0, 0, 0, "", "Quest avialable only during Hallow's End event");

delete from creature where id=44915;

UPDATE locales_quest SET EndText_loc3="", RequestItemsText_loc3="Wir sind die Verlassenen! So machen wir das, $C.", OfferRewardText_loc3="Ausgezeichnet! Und jetzt müssen wir das \"Mahl\" vorbereiten." WHERE Id=27082;

UPDATE quest_template SET PrevQuestId=27065 WHERE Id=27082;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Worgen des Hügellands", QuestGiverTargetName_loc3="Worgen des Hügellands" WHERE Id=27231;

UPDATE quest_template SET PrevQuestId=27098 WHERE Id=27231;

UPDATE locales_quest SET OfferRewardText_loc3="Sieht aus, als hättet Ihr diese Worgen so richtig vermöbelt und die Scham von uns genommen. Vielleicht hören die Seebären jetzt auf, zu saufen.$B$BAch, wem mache ich was vor.$B$BHa!", QuestGiverTextWindow_loc3="Blutfangplünderer", QuestGiverTargetName_loc3="Blutfangplünderer" WHERE Id=27073;

UPDATE quest_template SET PrevQuestId=27065 WHERE Id=27073;

UPDATE locales_quest SET OfferRewardText_loc3="AHA! Ich wusste es! Da haben wir wohl wieder etwas gelernt. Wir werden nicht wieder so versagen. Ich werde sicherstellen, dass immer Bier an vorderster Front bereitsteht.", QuestGiverTextWindow_loc3="Orcischer Seebär", QuestGiverTargetName_loc3="Orcischer Seebär" WHERE Id=27226;

UPDATE quest_template SET PrevQuestId=27098 WHERE Id=27226;

UPDATE locales_quest SET OfferRewardText_loc3="Die Wurzel diesen Übels muss gefunden und zerstört werden! Die Netzhuschermatriarchin muss in der Nähe sein. Zweifellos verbirgt sie sich in der nahegelegenen Höhle!", CompletedText_loc3="Kehrt zu Kriegsherr Torok an der Rückendeckung der Verlassenen im Silberwald zurück.", QuestGiverTextWindow_loc3="Netzhuscherspinne", QuestGiverTargetName_loc3="Netzhuscherspinne" WHERE Id=27095;

UPDATE quest_template SET PrevQuestId=27069, Flags=8388608 WHERE Id=27095;

update creature_template set AIName="", ScriptName="npc_lady_sylvanas_windrunner_44365" where entry=44365;

update gameobject set position_z=27.9789 where guid=1468 and id=106319;

UPDATE locales_quest SET OfferRewardText_loc3="Dieses Fiasko könnte als eine der größten Peinlichkeiten in die Geschichte der Seekriegsführung eingehen. Wie das passiert ist? Trunkenheit ist passiert. So war das." WHERE Id=27065;

UPDATE locales_quest SET OfferRewardText_loc3="In diesen Kisten befindet sich STÄHLERNER DONNER! Jetzt, da unsere Waffen wieder da sind, haben wir vielleicht eine Möglichkeit, uns zu rehabilitieren.", QuestGiverTextWindow_loc3="Seebärenkiste", QuestGiverTargetName_loc3="Seebärenkiste" WHERE Id=27069;

UPDATE quest_template SET NextQuestIdChain=27069 WHERE Id=27065;

update creature_template set AIName="", ScriptName="npc_admiral_hatchet_44916" where entry=44916;

update creature_template set AIName="", ScriptName="" where entry=44917;

update creature_template set AIName="", ScriptName="npc_salty_rocka_45498" where entry=45498;

update creature_template set AIName="", ScriptName="" where entry=44915;

update creature_template set AIName="", ScriptName="npc_orc_sea_pup_44914" where entry=44914;

update creature_text set type=14 where entry=45497 and groupid between 0 and 2;

update creature_text set type=14 where entry=45498 and groupid between 0 and 4;

delete from gossip_menu_option where menu_id=11901 and id=0;
insert into gossip_menu_option values
(11901, 0, 0, "I seem to have misplaced my sea pup, admiral. Do you have another that you could lend to me?", 45023, 1, 1, 0, 0, 0, 0, 0, "", 0);

delete from conditions where SourceTypeOrReferenceId=15 and SourceEntry=11901 and ConditionTypeOrReference=9 and ConditionValue1=27069;
insert into conditions values 
(15, 0, 11901, 0, 0, 9, 0, 27069, 0, 0, 0, 0, 0, "", "gossip avialable on quest taken");

delete from spell_script_names where spell_id=83865;
insert into spell_script_names values
(83865, "spell_sea_pup_trigger_83865");

UPDATE quest_template SET SourceSpellId=83865 WHERE Id=27069;

delete from spell_script_names where spell_id=83838;
insert into spell_script_names values
(83838, "spell_pick_up_orc_crate_83838");







