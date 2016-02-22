
-- fix issue #80

-- http://wowwiki.wikia.com/wiki/Quest:A_Furious_Catch  
-- http://www.wowhead.com/quest=26565/a-furious-catch-removed >> this is a outdated quest 
-- http://www.wowhead.com/quest=26588/a-furious-catch >> this is the active quest.. used insted

-- http://www.wowhead.com/item=58951/giant-furious-pike  
-- https://cata-twinhead.twinstar.cz/?item=58951#fished-in

-- set quest 26565 as unavaible
UPDATE quest_template SET Method=1, Flags=16512 WHERE Id=26565;

delete from fishing_loot_template where item=58951 and entry in (11, 14, 16, 17, 814, 815);
insert into fishing_loot_template values
(11,58951,0,11.0,1,1,1,1,1,""),
(14,58951,0,7.0,1,1,1,1,1,""),
(16,58951,0,0.0001,1,1,1,1,1,""),
(17,58951,0,7.0,1,1,1,1,1,""),
(814,58951,0,5.0,1,1,1,1,1,""),
(815,58951,0,5.0,1,1,1,1,1,"");

UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="$N, Ihr habt einen! Einen so starken, schönen Fisch bekommt man nur selten zu Gesicht.", RequestItemsText_loc3="Konntet Ihr einen riesigen Hecht fangen?", CompletedText_loc3="Liefert den riesigen wütenden Hecht bei Razgar in Orgrimmar ab." WHERE Id=26588;

update gameobject_loot_template set chance=85 where entry=180663 and item=21071;

