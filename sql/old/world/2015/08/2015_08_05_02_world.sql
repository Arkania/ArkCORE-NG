
delete from areatrigger_scripts where entry in (5046,5047);
insert into areatrigger_scripts values
(5046,"at_sholazar_waygate"),
(5047,"at_sholazar_waygate");

update creature_template set AIName="", ScriptName="npc_training_dummy" where entry in (2674, 2673);

update creature_template set AIName="", ScriptName="boss_halfus" where entry=44600;
update creature_template set AIName="", ScriptName="npc_proto_behemoth" where entry=44687;
update creature_template set AIName="", ScriptName="boss_valiona_bot" where entry=45992;
update creature_template set AIName="", ScriptName="boss_theralion_bot" where entry=45993;
update creature_template set AIName="", ScriptName="boss_monstrosity" where entry=43735;
update creature_template set AIName="", ScriptName="npc_blood_old_god" where entry=43707;
update creature_template set AIName="", ScriptName="npc_twilight_whelp_phas1" where entry=47265;
update creature_template set AIName="", ScriptName="npc_runty" where entry=40015;
update creature_template set AIName="", ScriptName="npc_beauty_family" where entry=40008;
update creature_template set AIName="", ScriptName="npc_beauty_family" where entry=40011;
update creature_template set AIName="", ScriptName="npc_beauty_family" where entry=40013;
update creature_template set AIName="", ScriptName="npc_nefarian_yeller" where entry=49580;
update creature_template set AIName="", ScriptName="npc_exposed_magmaw_head" where entry=42347;
update creature_template set AIName="", ScriptName="npc_blazing_bone_construct" where entry=49416;
update creature_template set AIName="", ScriptName="boss_trons" where entry=42166;
update creature_template set AIName="", ScriptName="boss_trons" where entry=42178;
update creature_template set AIName="", ScriptName="boss_trons" where entry=42179;
update creature_template set AIName="", ScriptName="boss_trons" where entry=42180;
update creature_template set AIName="", ScriptName="npc_chemical_cloud" where entry=42934;
update creature_template set AIName="", ScriptName="npc_atramedes_gong" where entry=42949;
update creature_template set AIName="", ScriptName="npc_roaring_flame_target" where entry=42121;
update creature_template set AIName="", ScriptName="npc_searing_flame" where entry=41807;
update creature_template set AIName="", ScriptName="npc_roaring_flame" where entry=42001;
update creature_template set AIName="", ScriptName="npc_roaring_flame_target" where entry=42121;
update creature_template set AIName="", ScriptName="npc_atramedes_gong" where entry=42949;
update creature_template set AIName="", ScriptName="npc_maloriak_atramedes_event" where entry=49938;
update creature_template set AIName="", ScriptName="boss_bd_onyxia" where entry=41270;
update creature_template set AIName="", ScriptName="npc_nefarian_intro" where entry=41379;
update creature_template set AIName="", ScriptName="npc_animated_bone_warrior" where entry=41918;
update creature_template set AIName="", ScriptName="npc_shadowblaze" where entry=42596;
update creature_template set AIName="", ScriptName="npc_shadowflame_flashfire" where entry=54254;
update creature_template set AIName="", ScriptName="npc_ascended_rockbreaker" where entry=40272;
update creature_template set AIName="", ScriptName="npc_malignant_trogg" where entry=39984;
update creature_template set AIName="", ScriptName="npc_umbriss_trogg_dweller" where entry=45467;
update creature_template set AIName="", ScriptName="npc_invocation_of_flame_stalker" where entry=40355;
update creature_template set AIName="", ScriptName="npc_invoked_flaming_spirit" where entry=40357;
update creature_template set AIName="", ScriptName="npc_drahga_valiona" where entry=40320;
update creature_template set AIName="", ScriptName="npc_seeping_twilight" where entry=40365;
update creature_template set AIName="", ScriptName="npc_erudax_faceless_corruptor" where entry=39392;
update creature_template set AIName="", ScriptName="npc_alexstrasza_egg" where entry=40486;
update creature_template set AIName="", ScriptName="npc_erudax_twilight_hatchling" where entry=39388;



delete from spell_script_names where spell_id=78075;
insert into spell_script_names values
(78075, "spell_atramedes_sonic_breath");

delete from item_script_names where Id=5397;
insert into item_script_names values
(5397, "item_defias_gunpowder");

update creature_template set difficulty_entry_1=51119, difficulty_entry_2=51120, difficulty_entry_3=51121 where entry=41948;

update creature_template set difficulty_entry_1=49973, difficulty_entry_2=49979, difficulty_entry_3=49985 where entry=41576;

delete from spell_script_names where spell_id=75238;
insert into spell_script_names values
(75238, "spell_drahga_supernova");




















