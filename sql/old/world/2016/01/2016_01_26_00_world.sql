
delete from npc_spellclick_spells where npc_entry=48721 and spell_id=46598;
delete from npc_spellclick_spells where npc_entry=48806 and spell_id=46598;

delete from smart_scripts where entryorguid=34830 and source_type=0;

UPDATE quest_template SET PrevQuestId=24520 WHERE Id=14113;
UPDATE quest_template SET PrevQuestId=24520 WHERE Id=14153;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Sassy Hartzang im Hauptgeschäftssitz der HGK auf Kezan zurück." WHERE Id=14113;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Sassy Hartzang im Hauptgeschäftssitz der HGK auf Kezan zurück." WHERE Id=14153;

UPDATE quest_template SET PrevQuestId=14071, NextQuestId=14110, ExclusiveGroup=26711 WHERE Id=26711;
UPDATE quest_template SET PrevQuestId=14071, NextQuestId=14109, ExclusiveGroup=26711 WHERE Id=26712;



