-- fix quest 25409 Forces of Nature: Hyppogryphs
UPDATE creature_template SET AIName='',ScriptName='npc_feralas_hippogryph_40072' WHERE entry=5300 OR entry=5304;
UPDATE creature_template SET minlevel=36,maxlevel=37,faction=14 WHERE entry=40069;

-- fix quest 25410 Forces of Nature: Treants
UPDATE creature_template SET AIName='',ScriptName='npc_feralas_treant_40090' WHERE entry=7584;
DELETE FROM smart_scripts WHERE entryorguid=7584;