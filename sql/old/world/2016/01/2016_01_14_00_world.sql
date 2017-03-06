

delete from gameobject_queststarter where id in (206109, 206116) and quest=28790;
insert into gameobject_queststarter values
(206109, 28790),
(206116, 28790);

UPDATE quest_template SET Flags=0 WHERE Id=27721;

UPDATE locales_quest SET OfferRewardText_loc3="Möge Euer Sinn für Ehre und Pflicht Azeroth gute Dienste leisten, $C." WHERE Id=28790;

UPDATE locales_quest SET RequestItemsText_loc3="Ja, $C?", QuestGiverTextWindow_loc3="Wasser der Weitsicht", QuestGiverTargetName_loc3="Wasser der Weitsicht" WHERE Id=28805;

UPDATE quest_template SET QuestGiverPortrait=16480, QuestGiverTextWindow="Waters of Farseeing", QuestGiverTargetName="Waters of Farseeing" WHERE Id=28805;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=193;

delete from spell_script_names where spell_id=94687;
insert into spell_script_names values
(94687, "spell_waters_of_farseeing_94687");

