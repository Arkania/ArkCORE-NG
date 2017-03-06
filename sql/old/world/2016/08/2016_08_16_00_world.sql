
UPDATE npc_text SET BroadcastTextID1=35262, BroadcastTextID2=35263, BroadcastTextID3=35264, BroadcastTextID4=35265, BroadcastTextID5=35266, BroadcastTextID6=35267, BroadcastTextID7=35268 WHERE ID=14681;

UPDATE quest_template SET ExclusiveGroup=0 WHERE Id=14075;

UPDATE quest_template SET ExclusiveGroup=0 WHERE Id=14069;

delete from smart_scripts where entryorguid=35304;

UPDATE creature_template SET AIName="", ScriptName="npc_brute_enforcer_35304" WHERE entry=35304;

delete from spell_script_names where spell_id=70478;
insert into spell_script_names values 
(70478, "spell_kaja_cola_70478");



