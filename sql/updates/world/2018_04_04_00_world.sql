
-- fix quest 25407 Forces of Nature: Wisps (Kalimdor, Feralas)

UPDATE creature SET spawntimesecs=300, spawndist=10, MovementType=1 WHERE id=40079;

UPDATE creature_template SET AIName="", ScriptName="npc_feralas_wisp_40079" WHERE entry=40079;

DELETE FROM smart_scripts WHERE entryorguid=40079;



