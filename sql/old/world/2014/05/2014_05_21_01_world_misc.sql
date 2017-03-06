
-- sister_almyra
UPDATE creature_template SET AIName="",ScriptName="npc_sister_almyra_phase8" WHERE entry=44468;
UPDATE creature_template SET AIName="",ScriptName="npc_celestine_of_the_harvest_phase8" WHERE entry=44459;

-- crowley: sacrifices
UPDATE quest_template SET PrevQuestId=14294 WHERE Id=14212;

