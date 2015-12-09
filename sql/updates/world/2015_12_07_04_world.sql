
-- npc 8125 spawned from script
delete from creature where guid=87101 and id=8125;

-- quest 13825
UPDATE quest_template SET Method=2 WHERE Id=13825;

-- quest 6610
UPDATE locales_quest SET EndText_loc3="" WHERE Id=6610;

-- console error
update gameobject_template set data0=1691, data10=71725 where entry=202112;
update gameobject_template set data0=0 where entry=209098;
delete from creature_addon where guid in (102828, 102595, 102119, 101873);

-- quest
UPDATE creature_template SET faction=2203, unit_flags=8, InhabitType=7 WHERE entry=45004;


