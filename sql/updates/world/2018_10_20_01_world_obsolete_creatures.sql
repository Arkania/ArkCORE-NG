
-- Shaina Fuller is replaced 4.0.3 with Angela Leifeld
delete from creature where guid=49292 and id=2327;

update creature_template set difficulty_entry_1=35427, difficulty_entry_2=0, difficulty_entry_3=0 where entry=36839;

DELETE FROM creature_addon WHERE guid=49292;

update gameobject_template set data1=199329 where entry=199329;
update gameobject_template set data1=201608 where entry=201608; -- 28434

delete from gameobject_loot_template where entry=28434 and item=49749;

delete from gameobject_loot_template where entry=202473; 
delete from gameobject_loot_template where entry=202556; -- item=52498 no 434 quest
delete from gameobject_loot_template where entry=202573; -- item=52491 is only in object 202567
delete from gameobject_loot_template where entry=203075; -- item=4654 is provided by quest or script
delete from gameobject_loot_template where entry=203076; -- item=4654 is provided by quest or script
delete from gameobject_loot_template where entry=203232; -- item=12973 is only in object 176215 (but missing questrequired)
delete from gameobject_loot_template where entry=203278; -- items are loot in many other objects (but missing questrequired)
delete from gameobject_loot_template where entry=204965; -- item=60575 is provided by quest or script	
delete from gameobject_loot_template where entry=205094; -- item=60738 is provided by quest or script		
delete from gameobject_loot_template where entry=205554; -- item=61356 is provided by quest or script	
delete from gameobject_loot_template where entry=206510; -- item=12973 is only in object 176215 (but missing questrequired)
	
update gameobject_loot_template set QuestRequired=1 where Entry=176215;

update gameobject_loot_template set QuestRequired=1 where Item IN (52177,52178,52179,52180,52181,52182,52327,52328,53038);
