
update creature_template set AIName="", ScriptName="npc_mystery_toxin" where entry=50439;
update creature_template set AIName="", ScriptName="npc_mystery_toxin" where entry=50522;
update creature_template set AIName="", ScriptName="npc_throne_of_the_tides_teleporter" where entry=51391;
update creature_template set AIName="", ScriptName="npc_throne_of_the_tides_teleporter" where entry=51395;
update creature_template set AIName="", ScriptName="npc_lady_nazjar_honnor_guard" where entry=40633;
update creature_template set AIName="", ScriptName="npc_lady_nazjar_tempest_witch" where entry=44404;
update creature_template set AIName="", ScriptName="npc_lady_nazjar_waterspout" where entry=48571;
update creature_template set AIName="", ScriptName="npc_lady_nazjar_geyser" where entry=40597;
update creature_template set AIName="", ScriptName="npc_ulthok_dark_fissure" where entry=40784;
update creature_template set AIName="", ScriptName="npc_erunak_earth_shards" where entry=45469;
update creature_template set AIName="", ScriptName="npc_ghursha_mind_fog" where entry=40861;
update creature_template set AIName="", ScriptName="npc_vicious_mindslasher" where entry=44715;
update creature_template set AIName="", ScriptName="npc_unyielding_behemoth" where entry=44648;
update creature_template set AIName="", ScriptName="npc_faceless_sapper" where entry=44752;
update creature_template set AIName="", ScriptName="npc_blight_of_ozumat" where entry=44801;
update creature_template set AIName="", ScriptName="npc_blight_of_ozumat" where entry=44834;
update creature_template set AIName="", ScriptName="npc_aradne_50372" where entry=50372;
update creature_template set AIName="", ScriptName="boss_echo_of_sylvanas" where entry=54123;
update creature_template set AIName="", ScriptName="boss_echo_of_tyrande" where entry=54544;
update creature_template set AIName="", ScriptName="boss_murozond" where entry=54432;
update creature_template set AIName="", ScriptName="npc_kohcrom" where entry=57773;
update creature_template set AIName="", ScriptName="npc_resonating_crystal" where entry=55346;
update creature_template set AIName="", ScriptName="npc_resonating_crystal" where entry=15769;
update creature_template set AIName="", ScriptName="npc_minor_resonating_crystal" where entry=15805;
update creature_template set AIName="", ScriptName="npc_black_blood_of_the_earth" where entry=55267;
-- update creature_template set AIName="", ScriptName="travel_to_spine" where entry=;
update creature_template set AIName="", ScriptName="travel_to_maelstrom" where entry=57443;

UPDATE `gameobject_template` SET `ScriptName` = 'go_totd_defense_system' WHERE `entry` = 203199;

delete from instance_template where map=269;
insert into instance_template values
(269, 1, "instance_the_black_morass", 1);

delete from spell_script_names where spell_id=103414;
insert into spell_script_names values
(103414, "spell_morchok_stomp");

delete from spell_script_names where spell_id=103851;
insert into spell_script_names values
(103851, "spell_morchok_black_blood");


 

 











