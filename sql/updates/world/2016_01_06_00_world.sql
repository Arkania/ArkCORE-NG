
delete from npc_spellclick_spells where npc_entry=52359 and spell_id=96847;

delete from creature_text where entry=39665 and groupid in (6, 7, 8, 9);

update creature_text set sound=0 where entry=39665 and groupid=5 and id=0;


 -- Disabled: script has wrong register parts
delete from spell_script_names where ScriptName="spell_rog_crippling_poison";
delete from spell_script_names where ScriptName="spell_warl_improved_soul_fire";
delete from spell_script_names where ScriptName="spell_dru_stampede";
delete from spell_script_names where ScriptName="spell_aura_of_nature";

-- delete while no script avaible.
delete from spell_script_names where ScriptName="spell_pal_divine_purpose";

-- quest 10930 -- spell 39246
delete from spell_script_names where ScriptName="spell_q10930_fumping";
insert into spell_script_names values 
(39246, "spell_q10930_fumping");


