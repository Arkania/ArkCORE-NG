

-- only pickpocketing loot..
update creature_template set lootid=0 where entry=11604;

update gameobject_template set data1=206391, data8=27851 where entry=206391;

