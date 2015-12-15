
-- db error
UPDATE quest_template SET SpecialFlags=2 WHERE Id=8354;

-- db error
update instance_encounters set lastEncounterDungeon=334 where entry=793;

-- db error
update instance_encounters set lastEncounterDungeon=0 where entry=1182;

-- db error
update instance_encounters set creditEntry=54432 where entry=1271;

-- db error
update instance_encounters set creditType=0, creditEntry=56173 where entry=1299;

-- db error
update creature_template set lootid=5524 where entry=5524;

-- db error
update creature_template set lootid=42548 where entry=42548;

-- db error
update creature_template set lootid=57159 where entry=57159;

-- db error
update creature_template set lootid=57160 where entry=57160;

-- db error
update creature_template set lootid=57280 where entry=57280;

-- db error
update fishing_loot_template set mincountOrRef=1 where entry=4395 and item=43723;

-- db error
update gameobject_loot_template set ChanceOrQuestChance=82.45 where entry=123329 and item=7740;

-- db error
update gameobject_template set data1=179528 where entry=179528;
update gameobject_template set data1=179548 where entry=179548;
update gameobject_template set data1=204282 where entry=204282;
update gameobject_template set data1=207187 where entry=207187;
update gameobject_template set data1=207188 where entry=207188;
update gameobject_template set data1=207189 where entry=207189;
update gameobject_template set data1=207190 where entry=207190;

















