
-- fishing quest in stormwind 
delete from fishing_loot_template where entry=1519 and item=58503;
insert into fishing_loot_template values
(1519, 58503, -25.1941, 1, 0, 1, 1);

-- fishing quest in Elwynn Forest
delete from fishing_loot_template where entry=12 and item=58899;
insert into fishing_loot_template values
(12, 58899, -35.4636, 1, 0, 1, 1);
