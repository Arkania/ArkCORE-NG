
-- quest=26442
update gameobject_template set data0=1691, data3=1, data7=204289, data14=19676 where entry=204284;

delete from fishing_loot_template where entry=141;
insert into fishing_loot_template values
(141, 11000, 100, 1, 1, -11000, 1),
(141, 11001, 100, 1, 1, -11001, 1),
(141, 11799, 100, 1, 1, -11799, 1);

delete from fishing_loot_template where entry=702 and item=69987;
insert into fishing_loot_template values
(702, 69987, -35.2, 1, 1, 1, 1);

update creature_loot_template set ChanceorQuestChance=-90 where entry=35096 and item in (47038, 58949);

delete from fishing_loot_template where entry=5171 and item=58946;
insert into fishing_loot_template values
(5171, 58946, -7.2, 1, 1, 1, 1);

UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="Hervorragend! Diese Sandkarpfen sind ganz schön wählerisch, oder?", RequestItemsText_loc3="War das Auge ein guter Köder?", CompletedText_loc3="Bringt den Sandkarpfen zu Razgar in Orgrimmar." WHERE Id=26557;

-- quest 26420
update gameobject_template set data8=26420 where entry=204281; 

delete from fishing_loot_template where entry=5316 and item=58787;
insert into fishing_loot_template values
(5316, 58787, -4.2, 1, 1, 1, 1);

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Catherine Leland in Sturmwind zurück." WHERE Id=26420;


