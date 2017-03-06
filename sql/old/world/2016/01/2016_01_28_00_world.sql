

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Thonk in Klingenhügel in Durotar zurück." WHERE Id=25187;

UPDATE locales_quest SET OfferRewardText_loc3="<Aska beäugt die Zutaten, die Ihr ausgewählt habt.> $B$BMmmhmmm. Ja. Gut gemacht!$B$BIch hätte sie selbst nicht besser auswählen können.", RequestItemsText_loc3="Habt Ihr alle nötigen Zutaten gesammelt?", CompletedText_loc3="Kehrt zurück zu Aska Nebelläufer in Donnerfels." WHERE Id=29365;

UPDATE locales_quest SET CompletedText_loc3="Kehrt zu Zen'tabra auf dem Ausbildungsgelände der Dunkelspeere zurück." WHERE Id=24765;

-- https://cata-twinhead.twinstar.cz/?quest=24766
update npc_trainer set reqlevel=3 where entry=38243 and spell=774;

UPDATE locales_quest SET ObjectiveText1_loc3="Übt 'Verjüngung'" WHERE Id=24766;

UPDATE quest_template SET RequiredNpcOrGo1=47057, RequiredSpell=774 WHERE Id=24766;


