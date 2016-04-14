
-- fix issue #127

UPDATE locales_quest SET EndText_loc3="", QuestGiverTextWindow_loc3="Manawyrm.. sie sind hier einfach überall. Findet und tötet sie alle.", QuestGiverTargetName_loc3="Manawyrm" WHERE Id=8325;

update creature_template set AIName="", ScriptName="", Health_mod=2 where entry=15371;

delete from smart_scripts where entryorguid=15371;

delete from quest_poi where questid=8325 and id=1 and objIndex=-1;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=8326;

delete from quest_poi where questid=8326 and id=1 and objIndex=-1;

UPDATE locales_quest SET EndText_loc3="", QuestGiverTextWindow_loc3="Manawyrm", QuestGiverTargetName_loc3="Manawyrm" WHERE Id=8346;

UPDATE quest_template SET RequiredNpcOrGo1=15468 WHERE Id=8346;

update creature_template set AIName="", ScriptName="npc_mana_wyrm_15274" where entry=15274;

UPDATE quest_template SET PrevQuestId=8335 WHERE Id=8347;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=8335;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=8334;



