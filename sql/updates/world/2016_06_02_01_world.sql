
-- issue #147

update creature_loot_template set Chance=31, QuestRequired=1 where entry=18341 and item=28558;

delete from creature_loot_template where entry=18341 and item=72126;
insert into creature_loot_template values
(18341, 72126, 0, 100, 1, 1, 0, 1, 1, "");

