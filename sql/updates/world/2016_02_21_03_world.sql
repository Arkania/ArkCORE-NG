
-- issue #84

update gameobject_template set data1=183043 where entry=183043;

delete from gameobject_loot_template where entry=183043;
insert into gameobject_loot_template values 
(183043, 22575, 0, 14, 0, 1, 0, 1, 3, ""),
(183043, 22787, 0, 100, 0, 1, 0, 1, 3, ""),
(183043, 22794, 0, 1.7, 0, 1, 0, 1, 1, ""),
(183043, 24401, 0, 25, 0, 1, 0, 1, 1, "");

