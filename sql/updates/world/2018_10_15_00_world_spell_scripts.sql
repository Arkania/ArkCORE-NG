
DELETE FROM spell_script_names WHERE spell_id=70656 and ScriptName="spell_dk_advantage_t10_4p";
INSERT INTO spell_script_names VALUES 
(70656, "spell_dk_advantage_t10_4p");

DELETE FROM spell_script_names WHERE spell_id=49028 and ScriptName="spell_dk_dancing_rune_weapon";
INSERT INTO spell_script_names VALUES 
(49028, "spell_dk_dancing_rune_weapon");

DELETE FROM spell_script_names WHERE spell_id=61257 and ScriptName="spell_dk_pvp_4p_bonus";
INSERT INTO spell_script_names VALUES 
(61257, "spell_dk_pvp_4p_bonus");

-- druid

DELETE FROM spell_script_names WHERE spell_id=37336 and ScriptName="spell_dru_forms_trinket";
INSERT INTO spell_script_names VALUES 
(37336, "spell_dru_forms_trinket");

DELETE FROM spell_script_names WHERE spell_id IN (-33943, 33943) and ScriptName="spell_dru_flight_form";
INSERT INTO spell_script_names VALUES 
(33943, "spell_dru_flight_form");

DELETE FROM spell_script_names WHERE spell_id=105737 and ScriptName="spell_dru_might_of_ursoc";

-- generic

DELETE FROM spell_script_names WHERE spell_id=65917 and ScriptName="spell_gen_magic_rooster";
INSERT INTO spell_script_names VALUES 
(65917, "spell_gen_magic_rooster");

DELETE FROM spell_script_names WHERE spell_id=64568 and ScriptName="spell_gen_blood_reserve";
INSERT INTO spell_script_names VALUES 
(64568, "spell_gen_blood_reserve");

DELETE FROM spell_script_names WHERE spell_id=48750 and ScriptName="spell_gen_burning_depths_necrolyte_image";
INSERT INTO spell_script_names VALUES 
(48750, "spell_gen_burning_depths_necrolyte_image");

DELETE FROM spell_script_names WHERE spell_id=131474 and ScriptName="spell_gen_fishing";
DELETE FROM spell_script_names WHERE spell_id IN (7733, 7734, 54083, 18249, 54084, 51293, 88869) and ScriptName="spell_gen_fishing";
-- INSERT INTO spell_script_names VALUES 
-- (7733, "spell_gen_fishing"),
-- (7734, "spell_gen_fishing"),
-- (54083, "spell_gen_fishing");



DELETE FROM spell_script_names WHERE spell_id=9454 and ScriptName="spell_gen_gm_freeze";
INSERT INTO spell_script_names VALUES 
(9454, "spell_gen_gm_freeze");

DELETE FROM spell_script_names WHERE spell_id IN (37752, 96119) and ScriptName="spell_gen_stand";
INSERT INTO spell_script_names VALUES 
(37752, "spell_gen_stand"),
(96119, "spell_gen_stand");

DELETE FROM spell_script_names WHERE spell_id IN (57064, 57099) and ScriptName="spell_gen_landmine_knockback_achievement";
INSERT INTO spell_script_names VALUES 
(57099, "spell_gen_landmine_knockback_achievement");

DELETE FROM spell_script_names WHERE spell_id=34098 and ScriptName="spell_gen_clear_debuffs";
INSERT INTO spell_script_names VALUES 
(34098, "spell_gen_clear_debuffs");

DELETE FROM spell_script_names WHERE spell_id=31447 and ScriptName="spell_gen_mark_of_kazrogal_hellfire";
INSERT INTO spell_script_names VALUES 
(31447, "spell_gen_mark_of_kazrogal_hellfire");

DELETE FROM spell_script_names WHERE spell_id=99947 and ScriptName="spell_gen_face_rage";
INSERT INTO spell_script_names VALUES 
(99947, "spell_gen_face_rage");

-- holiday

DELETE FROM spell_script_names WHERE spell_id=24930 and ScriptName="spell_hallow_end_candy";
INSERT INTO spell_script_names VALUES 
(24930, "spell_hallow_end_candy");

DELETE FROM spell_script_names WHERE spell_id=24926 and ScriptName="spell_hallow_end_candy_pirate";
INSERT INTO spell_script_names VALUES 
(24926, "spell_hallow_end_candy_pirate");

DELETE FROM spell_script_names WHERE spell_id=24750 and ScriptName="spell_gen_trick";

DELETE FROM spell_script_names WHERE spell_id=24751 and ScriptName="spell_gen_trick_or_treat";

DELETE FROM spell_script_names WHERE spell_id IN (24717, 24718, 24719, 24720, 24724, 24733, 24737, 24741) and ScriptName="spell_hallow_end_wand";
INSERT INTO spell_script_names VALUES 
(24717, "spell_hallow_end_wand"),
(24718, "spell_hallow_end_wand"),
(24719, "spell_hallow_end_wand"),
(24720, "spell_hallow_end_wand"),
(24724, "spell_hallow_end_wand"),
(24733, "spell_hallow_end_wand"),
(24737, "spell_hallow_end_wand"),
(24741, "spell_hallow_end_wand");

DELETE FROM spell_script_names WHERE spell_id IN (61784, 61785, 61786, 61787, 61788) and ScriptName="spell_pilgrims_bounty_feast_on";
INSERT INTO spell_script_names VALUES 
(61784, "spell_pilgrims_bounty_feast_on"),
(61785, "spell_pilgrims_bounty_feast_on"),
(61786, "spell_pilgrims_bounty_feast_on"),
(61787, "spell_pilgrims_bounty_feast_on"),
(61788, "spell_pilgrims_bounty_feast_on");

DELETE FROM spell_script_names WHERE spell_id IN (61841, 61842, 61843, 61844, 61845) and ScriptName LIKE "spell_pilgrims_bounty_well_fed_%";
INSERT INTO spell_script_names VALUES 
(61841, "spell_pilgrims_bounty_well_fed_cranberry"),
(61842, "spell_pilgrims_bounty_well_fed_turkey"),
(61843, "spell_pilgrims_bounty_well_fed_stuffing"),
(61844, "spell_pilgrims_bounty_well_fed_sweet_potatoes"),
(61845, "spell_pilgrims_bounty_well_fed_pie");

DELETE FROM spell_script_names WHERE spell_id=62014 and ScriptName="spell_pilgrims_bounty_turkey_tracker";
INSERT INTO spell_script_names VALUES 
(62014, "spell_pilgrims_bounty_turkey_tracker");

DELETE FROM spell_script_names WHERE spell_id=42924 and ScriptName="spell_brewfest_giddyup";
INSERT INTO spell_script_names VALUES 
(42924, "spell_brewfest_giddyup");

DELETE FROM spell_script_names WHERE spell_id IN (43310, 42992, 42993, 42994) and ScriptName="spell_brewfest_ram";
INSERT INTO spell_script_names VALUES 
(43310, "spell_brewfest_ram"),
(42992, "spell_brewfest_ram"),
(42993, "spell_brewfest_ram"),
(42994, "spell_brewfest_ram");

DELETE FROM spell_script_names WHERE spell_id=43052 and ScriptName="spell_brewfest_ram_fatigue";
INSERT INTO spell_script_names VALUES 
(43052, "spell_brewfest_ram_fatigue");

DELETE FROM spell_script_names WHERE spell_id=43450 and ScriptName="spell_brewfest_apple_trap";
INSERT INTO spell_script_names VALUES 
(43450, "spell_brewfest_apple_trap");

DELETE FROM spell_script_names WHERE spell_id=43332 and ScriptName="spell_brewfest_exhausted_ram";
INSERT INTO spell_script_names VALUES 
(43332, "spell_brewfest_exhausted_ram");

DELETE FROM spell_script_names WHERE spell_id=43714 and ScriptName="spell_brewfest_relay_race_intro_force_player_to_throw";
INSERT INTO spell_script_names VALUES 
(43714, "spell_brewfest_relay_race_intro_force_player_to_throw");

DELETE FROM spell_script_names WHERE spell_id=43876 and ScriptName="spell_brewfest_dismount_ram";
INSERT INTO spell_script_names VALUES 
(43876, "spell_brewfest_dismount_ram");

DELETE FROM spell_script_names WHERE spell_id IN (43259, 43260, 43261, 43262) and ScriptName="spell_brewfest_barker_bunny";
INSERT INTO spell_script_names VALUES 
(43259, "spell_brewfest_barker_bunny"),
(43260, "spell_brewfest_barker_bunny"),
(43261, "spell_brewfest_barker_bunny"),
(43262, "spell_brewfest_barker_bunny");

DELETE FROM spell_script_names WHERE spell_id=45390 and ScriptName="spell_gen_ribbon_pole_dancer_check";
INSERT INTO spell_script_names VALUES 
(45390, "spell_gen_ribbon_pole_dancer_check");
