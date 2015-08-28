
-- fishing quest in stormwind 
delete from fishing_loot_template where entry=5314 and item=58503;
insert into fishing_loot_template values
(5314, 58503, -25.1941, 1, 0, 1, 1);

-- fishing quest in Elwynn Forest
delete from fishing_loot_template where entry=61 and item=58899;
insert into fishing_loot_template values
(61, 58899, -35.4636, 1, 0, 1, 1);
