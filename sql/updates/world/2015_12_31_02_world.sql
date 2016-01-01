

delete from spell_script_names where spell_id in (23074, 23075, 23076, 23133);
insert into spell_script_names values 
(23074, "spell_item_arcanite_dragonling"),
(23075, "spell_item_mithril_mechanical_dragonling"),
(23076, "spell_item_mechanical_dragonling"),
(23133, "spell_item_gnomish_battle_chicken");

delete from spell_script_names where spell_id=71168;
insert into spell_script_names values 
(71168, "spell_item_unsated_craving");

delete from spell_script_names where spell_id=6262 and ScriptName="spell_item_healthstone";
insert into spell_script_names values 
(6262, "spell_item_healthstone");

delete from spell_script_names where spell_id=24531;
insert into spell_script_names values 
(24531, "spell_item_refocus");

delete from spell_script_names where spell_id in (82174, 82175) and ScriptName="spell_item_synapse_springs";
insert into spell_script_names values 
(82174, "spell_item_synapse_springs"),
(82175, "spell_item_synapse_springs");

delete from spell_script_names where spell_id in (3409, 25809, 44289);
insert into spell_script_names values 
(3409, "spell_rog_crippling_poison"),
(25809, "spell_rog_crippling_poison"),
(44289, "spell_rog_crippling_poison");
