
-- fix issue 152, add missing loot

delete from creature_loot_template where entry=19428 and item=72480;
insert into creature_loot_template values
(19428, 72480, 0, 100, 1, 1, 0, 1, 1, "");

