
-- issue #82


delete from fishing_loot_template where entry in (33, 5287, 5339) and item=19807;
insert into fishing_loot_template values 
(5287, 19807, 0, 39, 1, 1, 1, 1, 1, ""),
(5339, 19807, 0, 38, 1, 1, 1, 1, 1, ""),
(33, 19807, 0, 30, 1, 1, 1, 1, 1, "");
