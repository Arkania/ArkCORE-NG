
-- issue #148

update creature_loot_template set Chance=31, QuestRequired=1 where entry=18343 and item=28558;

delete from creature_loot_template where entry=18343 and item=72127;
insert into creature_loot_template values
(18343, 72127, 0, 100, 1, 1, 0, 1, 1, "");

