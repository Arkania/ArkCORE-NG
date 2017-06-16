
-- fix deepholm
-- add quest 27136
UPDATE quest_template SET QuestGiverPortrait=0, Method=2, PrevQuestId=27123, NextQuestId=0, ExclusiveGroup=0 WHERE Id=27136;

-- fix quest 27136
UPDATE creature_template SET ScriptName="npc_energized_geode_43254" WHERE entry=43254;

UPDATE creature_template SET ScriptName="npc_lodestone_elemental_43258" WHERE entry=43258;

UPDATE creature_template SET ScriptName="npc_depleted_totem_45088" WHERE entry=45088;

delete from spell_script_names where spell_id=84163;
insert into spell_script_names values 
(84163, "spell_energy_capture_84163");

