

delete from spell_script_names where ScriptName="spell_rog_smoke_bomb";
delete from spell_script_names where ScriptName="spell_rog_smoke_bomb_inv";
insert into spell_script_names values
(76577, "spell_rog_smoke_bomb");

delete from spell_script_names where ScriptName="spell_rog_crippling_poison";

delete from spell_script_names where spell_id=39610 and ScriptName="spell_sha_mana_tide_totem";

delete from spell_script_names where ScriptName="spell_sha_nature_guardian";

delete from spell_script_names where ScriptName="spell_dk_glyph_chains_of_ice"; 

delete from spell_script_names where ScriptName="spell_gen_lifeblood";

delete from spell_script_names where spell_id=61782 and ScriptName="spell_gen_replenishment";

delete from spell_script_names where ScriptName="spell_gen_magic_rooster"; 

delete from spell_script_names where spell_id=82175 and ScriptName="spell_item_synapse_springs";

delete from spell_script_names where spell_id=83676 and ScriptName="spell_hun_resistance_is_futile";

delete from spell_ranks where first_spell_id=81708;
insert into spell_ranks values
(81708, 81708, 1),
(81708, 55428, 2),
(81708, 55480, 3),
(81708, 55500, 4),
(81708, 55501, 5),
(81708, 55502, 6),
(81708, 55503, 7),
(81708, 74497, 8);
 
 