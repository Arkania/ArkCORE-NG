
-- fix quest http://www.wowhead.com/quest=866/root-samples
-- message from forum..
delete from gameobject_loot_template where entry=1620 and item in (2452, 5056);
insert into gameobject_loot_template values 
(1620, 2452, 20, 1, 0, 1, 3),
(1620, 5056, -40, 1, 0, 1, 1);

delete from gameobject_loot_template where entry=1621 and item=5056;
insert into gameobject_loot_template values 
(1621, 5056, -40, 1, 0, 1, 1);

update gameobject_template set data0=9 where entry=1620;

-- quest 26233
-- https://cata-twinhead.twinstar.cz/?object=203977
update gameobject_template set flags=0, data1=203977, data8=26233 where entry=203977;
update quest_template set RewardSpellCast=99249 where Id=26233;
UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="Ihr habt auch Talent im Stehlen, wie ich sehe, <Name>. Sorgt Euch nicht, wir werden den Reis zurückbringen, wenn wir fertig sind... oder auch nicht.", RequestItemsText_loc3="Konntet Ihr den Reis besorgen?", CompletedText_loc3="Kehrt zu Marogg in Orgrimmar zurück." WHERE Id=26233;

-- quest 26234
-- https://cata-twinhead.twinstar.cz/?object=203979
update gameobject_template set flags=0, data1=203979, data8=26234 where entry=203979;
update quest_template set RewardSpellCast=99249 where Id=26234;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Marogg in Orgrimmar zurück." WHERE Id=26234;


