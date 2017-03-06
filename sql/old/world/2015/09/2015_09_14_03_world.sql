
update creature_template set AIName="",ScriptName="" where entry in (34851, 44086); 
update creature_template set AIName="",ScriptName="npc_prince_liam_greymane_34850" where entry=34850;
update creature_template set AIName="",ScriptName="npc_lieutenant_walden_34863" where entry=34863; 
update creature_template set AIName="",ScriptName="npc_gilnean_crow_50260" where entry=50260; 
update creature_template set AIName="",ScriptName="npc_gilneas_city_guard_gate_34864" where entry=34864; 
update creature_template set AIName="", ScriptName="npc_josiah_avery_worgen_35370" where entry=35370;
update creature_template set AIName="", ScriptName="npc_gwen_armstead_35840" where entry=35840;
UPDATE creature_template SET AIName="", ScriptName ="npc_prince_liam_greymane_34913" WHERE entry=34913;
UPDATE creature_template SET AIName="", ScriptName ="npc_gilneas_city_guard_34916" WHERE entry=34916;
UPDATE creature_template SET AIName="", ScriptName ="npc_rampaging_worgen_34884" WHERE entry=34884;
UPDATE creature_template SET AIName="", ScriptName ="npc_mariam_spellwalker_35872" WHERE entry=35872;
UPDATE creature_template SET AIName="", ScriptName ="npc_rampaging_worgen_35660" WHERE entry=35660;
UPDATE creature_template SET AIName="", ScriptName ="npc_gilnean_royal_guard_35232" WHERE entry=35232;
UPDATE creature_template SET AIName="", ScriptName ="npc_frightened_citizen_34981" WHERE entry in (34981, 35836);	
UPDATE creature_template SET AIName="", ScriptName ="npc_sergeant_cleese_35839" WHERE entry=35839;
UPDATE creature_template SET AIName="", ScriptName ="npc_worgen_runt_35188" WHERE entry=35188;
UPDATE creature_template SET AIName="", ScriptName ="npc_lord_darius_crowley_35077" WHERE entry=35077;
UPDATE creature_template SET AIName="", ScriptName ="npc_worgen_runt_35456" WHERE entry=35456;
UPDATE creature_template SET AIName="", ScriptName ="npc_worgen_alpha_35170" WHERE entry=35170;
UPDATE creature_template SET AIName="", ScriptName ="npc_worgen_alpha_35167" WHERE entry=35167;
UPDATE creature_template SET AIName="", ScriptName ="npc_josiah_avery_35369" WHERE entry=35369;
UPDATE creature_template SET AIName="", ScriptName ="npc_josiah_avery_trigger_50415" WHERE entry=50415;
UPDATE creature_template SET AIName="", ScriptName ="npc_lorna_crowley_35378" WHERE entry=35378;
UPDATE creature_template SET AIName="", ScriptName ="npc_gilnean_mastiff_35631" WHERE entry=35631;
UPDATE creature_template SET AIName="", ScriptName ="npc_bloodfang_lurker_35463" WHERE entry=35463;
UPDATE creature_template SET AIName="", ScriptName ="npc_krennan_aranas_35907" WHERE entry=35907;
UPDATE creature_template SET AIName="", ScriptName ="npc_commandeered_cannon_35914" WHERE entry=35914;
UPDATE creature_template SET AIName="", ScriptName ="npc_lord_godfrey_35115" WHERE entry IN (35115, 35906);
UPDATE creature_template SET AIName="", ScriptName ="npc_lord_darius_crowley_35552" WHERE entry=35552;
UPDATE creature_template SET AIName="", ScriptName ="npc_crowley_horse_35231" WHERE entry=35231;
UPDATE creature_template SET AIName="", ScriptName ="npc_king_genn_greymane_35550" WHERE entry=35550;
UPDATE creature_template SET AIName="", ScriptName ="npc_king_greymanes_horse_35905" WHERE entry=35905;
UPDATE creature_template SET AIName="", ScriptName ="npc_bloodfang_stalker_35229" WHERE entry=35229;
UPDATE creature_template SET AIName="", ScriptName ="npc_lord_darius_crowley_35566" WHERE entry=35566;
UPDATE creature_template SET AIName="", ScriptName ="npc_king_genn_greymane_36332" WHERE entry=36332;
UPDATE creature_template SET AIName="", ScriptName ="npc_horrid_abomination_36231" WHERE entry=36231;
UPDATE creature_template SET AIName="", ScriptName ="npc_captured_riding_bat_38615" WHERE entry=38615;
UPDATE creature_template SET AIName="", ScriptName ="npc_lorna_crowley_38611" WHERE entry=38611;
UPDATE creature_template SET AIName="", ScriptName ="npc_worgen_warrior_38348" WHERE entry=38348;
UPDATE creature_template SET AIName="", ScriptName ="npc_lord_darius_crowley_38415" WHERE entry=38415;
UPDATE creature_template SET AIName="", ScriptName ="npc_gilnean_militia_38221" WHERE entry=38221;
UPDATE creature_template SET AIName="", ScriptName ="npc_krennan_aranas_38553" WHERE entry=38553;
UPDATE creature_template SET AIName="", ScriptName ="npc_admiral_nightwind_36616" WHERE entry=36616;
UPDATE creature_template SET AIName="", ScriptName ="npc_lord_godfrey_36290" WHERE entry=36290;

delete from spell_script_names where spell_id in (67805, 68555, 68735, 68903);
insert into spell_script_names values (67805, "spell_attack_lurker_67805");
insert into spell_script_names values (68555, "spell_keg_placed_68555");
insert into spell_script_names values (68735, "spell_rescue_drowning_watchman_68735");
insert into spell_script_names values (68903, "spell_round_up_horse_68903");

update gameobject_template set AIName="", ScriptName="go_mandragore_196394" where entry=196394;
update gameobject_template set AIName="", ScriptName="go_merchant_square_door_195327" where entry=195327;


