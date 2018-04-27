-- fix quest 25409 Forces of Nature: Hyppogryphs
UPDATE creature_template SET AIName='',ScriptName='npc_feralas_hippogryph_5300_5304' WHERE entry IN (5300,5304);
UPDATE creature_template SET minlevel=36,maxlevel=37,faction=14 WHERE entry=40069;

-- fix quest 25410 Forces of Nature: Treants
UPDATE creature_template SET AIName='',ScriptName='npc_feralas_treant_7584' WHERE entry=7584;
DELETE FROM smart_scripts WHERE entryorguid=7584;
