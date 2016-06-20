

-- replace wrong import
delete from achievement_criteria_data where criteria_id in (10291, 10292) and type in (12, 18);
insert into achievement_criteria_data values
(10291, 18, 0, 0, ""),
(10292, 18, 0, 0, "");

-- set npcflag for all difficulty 
update creature_template set npcflag=16777216 where entry in (36839, 35427, 3683902, 3683903);


delete from spell_script_names where spell_id=-30881;
insert into spell_script_names values
(-30881, "spell_sha_nature_guardian"); 

delete from spell_script_names where spell_id=83236;
insert into spell_script_names values
(83236, "spell_hurl"); 

delete from spell_script_names where spell_id=81642;
insert into spell_script_names values
(81642, "spell_dust_flail"); 

delete from spell_script_names where spell_id=82168;
insert into spell_script_names values
(82168, "spell_repentance_pull_player");

delete from spell_script_names where spell_id=81960;
insert into spell_script_names values
(81960, "spell_copy_melee_weapon");

delete from spell_script_names where spell_id=81947;
insert into spell_script_names values
(81947, "spell_repentance_player_kneel");

delete from spell_script_names where spell_id=82009;
insert into spell_script_names values
(82009, "spell_repentance_player_summon_mirror");

delete from spell_script_names where spell_id=83066;
insert into spell_script_names values
(83066, "spell_wailing_winds");

delete from spell_script_names where spell_id=83089;
insert into spell_script_names values
(83089, "spell_wailing_winds");

delete from spell_script_names where spell_id=84982;
insert into spell_script_names values
(84982, "spell_gathered_storms");

delete from spell_script_names where spell_id=87762;
insert into spell_script_names values
(87762, "spell_minister_of_air_lightning_lash");

delete from spell_script_names where spell_id in (85084, 85086, 85136, 85137, 85158, 85159);
insert into spell_script_names values
(85084, "spell_howling_gale_howling_gale"),
(85086, "spell_howling_gale_howling_gale"),
(85136, "spell_howling_gale_howling_gale"),
(85137, "spell_howling_gale_howling_gale"),
(85158, "spell_howling_gale_howling_gale"),
(85159, "spell_howling_gale_howling_gale");

delete from spell_script_names where spell_id=86930;
insert into spell_script_names values
(86930, "spell_asaad_supremacy_of_the_storm");
 

delete from instance_template where map=940;
insert into instance_template values 
(940, 0, "instance_hour_of_twilight", 0);

delete from instance_template where map=600;
insert into instance_template values 
(600, 571, "instance_drak_tharon_keep", 1);

delete from instance_template where map=624;
insert into instance_template values 
(624, 571, "instance_vault_of_archavon", 0);

delete from achievement_criteria_data where criteria_id=5829;
insert into achievement_criteria_data values
(5829, 11, 0, 0, "achievement_bucket_list");

delete from achievement_criteria_data where criteria_id=5821;
insert into achievement_criteria_data values
(5821, 11, 0, 0, "achievement_death_from_above");

delete from achievement_criteria_data where criteria_id=5292;
insert into achievement_criteria_data values
(5292, 11, 0, 0, "achievement_headed_south");


UPDATE creature_template SET AIName="", ScriptName="boss_anubshiah_9031" WHERE entry=9031;
UPDATE creature_template SET ScriptName="boss_gorosh_the_dervish_9027" WHERE entry=9027;
UPDATE creature_template SET ScriptName="npc_obnoxious_fiend_49740" WHERE entry=49740;
UPDATE creature_template SET AIName="", ScriptName="npc_lady_nazjar_event_39959" WHERE entry=39959;
UPDATE creature_template SET ScriptName="boss_warlord_zonozz_55308" WHERE entry=55308;
UPDATE creature_template SET minlevel=88, maxlevel=88, ScriptName="npc_incindiary_cloud_53541" WHERE entry=53541;
UPDATE creature_template SET minlevel=88, maxlevel=88, ScriptName="npc_blazing_power_53554" WHERE entry=53554;
UPDATE creature_template SET ScriptName="npc_liquid_obsidian_52619" WHERE entry=52619;
UPDATE creature_template SET minlevel=88, maxlevel=88, ScriptName="npc_breadth_of_frost_53953" WHERE entry=53953;
UPDATE creature_template SET minlevel=85, maxlevel=85, ScriptName="npc_bloodpetal_blossom_40620" WHERE entry=40620;
UPDATE creature_template SET ScriptName="boss_earthrager_ptah_39428" WHERE entry=39428;
UPDATE creature_template SET minlevel=85, maxlevel=85, ScriptName="npc_solar_winds_39634" WHERE entry=39634;
UPDATE creature_template SET minlevel=85, maxlevel=85, ScriptName="npc_orb_of_the_sun_40835" WHERE entry=40835;
UPDATE creature_template SET minlevel=85, maxlevel=85, ScriptName="npc_inferno_leap_47040" WHERE entry=47040;
UPDATE creature_template SET minlevel=85, maxlevel=85, ScriptName="npc_solar_winds_47922" WHERE entry=47922;
UPDATE creature_template SET ScriptName="npc_chaos_portal_41055" WHERE entry=41055;
UPDATE creature_template SET minlevel=85, maxlevel=85, ScriptName="npc_void_sentinel_41208" WHERE entry=41208;
UPDATE creature_template SET minlevel=85, maxlevel=85, ScriptName="npc_void_seeker_41148" WHERE entry=41148;
UPDATE creature_template SET minlevel=85, maxlevel=85, ScriptName="npc_void_seeker_41148" WHERE entry=41371;
UPDATE creature_template SET AIName="", ScriptName="npc_enslaved_bandit_45001" WHERE entry=45001;
UPDATE creature_template SET AIName="", ScriptName="npc_enslaved_bandit_45001" WHERE entry=45007;
UPDATE creature_template SET AIName="", ScriptName="npc_pygmy_brute_44896" WHERE entry=44896;
UPDATE creature_template SET minlevel=82, maxlevel=82, ScriptName="npc_tolvir_land_mine_44840" WHERE entry=44840;
UPDATE creature_template SET minlevel=82, maxlevel=82, ScriptName="npc_shockwave_stalker_44711" WHERE entry=44711;
UPDATE creature_template SET ScriptName="npc_bad_intentions_target_44586" WHERE entry=44586;
UPDATE creature_template SET AIName="", ScriptName="npc_frenzied_crocolisk_43658" WHERE entry=43658;
UPDATE creature_template SET minlevel=87, maxlevel=87, ScriptName="npc_augh_intro_48104" WHERE entry=48104;
UPDATE creature_template SET minlevel=83, maxlevel=84, ScriptName="npc_augh_blow_dart_45379" WHERE entry=45379;
UPDATE creature_template SET minlevel=83, maxlevel=84, ScriptName="npc_augh_whirlwind_45378" WHERE entry=45378;
UPDATE creature_template SET ScriptName="npc_frenzied_crocolisk_44892" WHERE entry=44892;
UPDATE creature_template SET AIName="", ScriptName="boss_augh_49045" WHERE entry=49045;
UPDATE creature_template SET ScriptName="boss_high_prophet_barim_43612" WHERE entry=43612;
UPDATE creature_template SET minlevel=85, maxlevel=85, ScriptName="npc_blaze_of_the_heavens_48904" WHERE entry=48904;
UPDATE creature_template SET minlevel=85, maxlevel=85, ScriptName="npc_repentance_mirror_43817" WHERE entry=43817;
UPDATE creature_template SET minlevel=85, maxlevel=85 WHERE entry=43926;
UPDATE creature_template SET ScriptName="npc_harbinger_of_darkness_43927" WHERE entry=43927;
UPDATE creature_template SET ScriptName="npc_soul_fragment_43934" WHERE entry=43934;
UPDATE creature_template SET ScriptName="boss_siamat_44819" WHERE entry=44819;
UPDATE creature_template SET ScriptName="npc_servant_of_siamat_45269" WHERE entry=45269;
UPDATE creature_template SET ScriptName="npc_minion_of_siamat_44704" WHERE entry=44704;
UPDATE creature_template SET minlevel=85, maxlevel=85, ScriptName="npc_cloud_burst_44541" WHERE entry=44541;
UPDATE creature_template SET ScriptName="npc_slipstream_45455" WHERE entry=45455;
UPDATE creature_template SET AIName="", ScriptName="npc_skyfall_star_45932" WHERE entry=45932;
UPDATE creature_template SET AIName="", ScriptName="npc_skyfall_star_45932" WHERE entry=52019;
UPDATE creature_template SET ScriptName="npc_cloud_prince_45917" WHERE entry=45917;
UPDATE creature_template SET minlevel=80, maxlevel=82, ScriptName="npc_whipping_wind_47238" WHERE entry=47238;
UPDATE creature_template SET AIName="", ScriptName="npc_young_storm_dragon_45919" WHERE entry=45919;
UPDATE creature_template SET AIName="", ScriptName="npc_armored_mistral_45915" WHERE entry=45915;
UPDATE creature_template SET AIName="", ScriptName="npc_empyrean_assassin_45922" WHERE entry=45922;
UPDATE creature_template SET AIName="", ScriptName="npc_executor_of_the_caliph_45928" WHERE entry=45928;
UPDATE creature_template SET ScriptName="npc_gust_soldier_45477" WHERE entry=45477;
UPDATE creature_template SET AIName="", ScriptName="npc_lurking_tempest_45704" WHERE entry=45704;
UPDATE creature_template SET ScriptName="npc_howling_gale_45572" WHERE entry=45572;
UPDATE creature_template SET AIName="", ScriptName="npc_minister_of_air_45930" WHERE entry=45930;
UPDATE creature_template SET AIName="", ScriptName="npc_servant_of_asaad_45926" WHERE entry=45926;
UPDATE creature_template SET AIName="", ScriptName="npc_temple_adept_45935" WHERE entry=45935;
UPDATE creature_template SET AIName="", ScriptName="npc_turbulent_squall_45924" WHERE entry=45924;
UPDATE creature_template SET AIName="", ScriptName="npc_wild_vortex_45912" WHERE entry=45912;
UPDATE creature_template SET ScriptName="npc_ertans_vortex_46007" WHERE entry=46007;
UPDATE creature_template SET ScriptName="npc_air_current_47305" WHERE entry=47305;
UPDATE creature_template SET ScriptName="boss_asaad_43875" WHERE entry=43875;
UPDATE creature_template SET minlevel=84, maxlevel=84, ScriptName="npc_unstable_grounding_field_46492" WHERE entry=46492;
UPDATE creature_template SET minlevel=88, maxlevel=88, ScriptName="npc_tornado_46207" WHERE entry=46207;
UPDATE creature_template SET ScriptName="npc_hurricane_46419" WHERE entry=46419;
UPDATE creature_template SET AIName="", ScriptName="npc_nestlewood_owlkin_16518" WHERE entry=16518;
UPDATE creature_template SET ScriptName="npc_anachronos_the_ancient_15381" WHERE entry=15381;
UPDATE creature_template SET ScriptName="npc_qiraj_guard_15423" WHERE entry=15414;
UPDATE creature_template SET ScriptName="npc_qiraj_guard_15423" WHERE entry=15422;
UPDATE creature_template SET ScriptName="npc_qiraj_guard_15423" WHERE entry=15423;
UPDATE creature_template SET ScriptName="npc_qiraj_guard_15423" WHERE entry=15424;
UPDATE creature_template SET ScriptName="npc_millhouse_manastorm_20977" WHERE entry=20977;
UPDATE gameobject_template SET ScriptName="go_the_thunderspike_184729" WHERE entry=184729;
UPDATE creature_template SET AIName="", ScriptName="npc_frostsworn_general_36723" WHERE entry=36723;
UPDATE creature_template SET ScriptName="npc_darkmoon_faire_gnoll_54444" WHERE entry=54444;
UPDATE creature_template SET ScriptName="npc_darkmoon_faire_whack_a_gnoll_bunny_58570" WHERE entry=58570;
