
-- quest 26226
delete from creature_loot_template where entry=42548 and item=57765;
insert into creature_loot_template values
(42548, 57765, -100, 1, 0, 1, 1);

UPDATE creature_template SET npcflag=16777216, unit_flags=1024, questItem1=57765 WHERE entry=42548;

DELETE FROM `smart_scripts` WHERE `entryorguid`=42548;

update creature_template set AIName="", ScriptName="npc_muddy_crawfish_42548" where entry=42548;

