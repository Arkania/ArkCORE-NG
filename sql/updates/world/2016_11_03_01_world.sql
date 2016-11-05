
delete from spell_script_names where spell_id=85429;

update creature_template set AIName="", ScriptName="npc_slipstream_alakir" where entry=46045;

update creature_template set AIName="", ScriptName="npc_stormling_pre_effect" where entry=47177;

update creature_template set AIName="", ScriptName="npc_relentless_storm_initial_vehicle" where entry=47806;

delete from areatrigger_scripts where entry=6281;
insert into areatrigger_scripts values 
(6281, "at_return_wind");

-- this npc are no original npc's, we have to replace them, with correct npc's
-- i let the script stay in core, maybe we can reuse it.
-- 470660 470661 470662 470663 470664 470665 470666 470667
-- Script named 'npc_wind_bridge' does not have a script name assigned in database.

