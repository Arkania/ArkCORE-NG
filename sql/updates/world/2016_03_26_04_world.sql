

-- fix issue #116 part 4

delete from creature where guid=5782 and id=13158;

update creature_template set AIName="", ScriptName="npc_lieutenant_sanders_noose_38936" where entry=38936;

UPDATE creature_template SET InhabitType=5 WHERE entry in (13158, 38936, 39093);

