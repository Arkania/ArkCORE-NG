
delete from spell_script_names where spell_id=498;
INSERT INTO spell_script_names (spell_id, ScriptName) VALUES 
(498, 'spell_pal_divine_protection_498');

update creature_template set AIName="", ScriptName="npc_injured_draenei_16971" where entry= 16971;

update creature_template set AIName="", ScriptName="npc_wounded_infantry_42501" where entry= 42501;

