

UPDATE quest_template SET QuestGiverTextWindow="Deviate Plainstrider", QuestGiverTargetName="Deviate Plainstrider" WHERE Id=24566;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Muyoh in der Überwucherung im Südlichen Brachland zurück.", QuestGiverTextWindow_loc3="Deviatebenenschreiter", QuestGiverTargetName_loc3="Deviatebenenschreiter" WHERE Id=24566;

delete from creature_text where entry=5629;
insert into creature_text values 
(5629, 0, 0, "Death to the Horde!", 12, 0, 100, 0, 0, 0, "say on aggro", 67556),
(5629, 0, 1, "Die, Horde scum!", 12, 0, 100, 0, 0, 0, "say on aggro", 67557);

