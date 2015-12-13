
-- fix quest 27604
update creature_loot_template set ChanceOrQuestChance=-100 where entry=5710 and item=6212;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Lord Itharius zurück." WHERE Id=27604;

UPDATE creature_template SET spell2=8376, spell3=12492, spell4=12479 WHERE entry=5710;


