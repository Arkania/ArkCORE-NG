
UPDATE creature_template SET AIName="",ScriptName="npc_rockjaw_scavenger" WHERE entry=37105;

update creature_loot_template set ChanceOrQuestChance=-1 where entry=37105 and item=49751;
