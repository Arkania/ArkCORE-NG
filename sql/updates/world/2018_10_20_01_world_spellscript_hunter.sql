
-- SpellScript hunter

DELETE FROM spell_script_names WHERE spell_id IN (16827, 17253, 49966, 83381) AND ScriptName="spell_hun_pet_damage_spells";
INSERT INTO spell_script_names  VALUES 
(16827, "spell_hun_pet_damage_spells"),
(17253, "spell_hun_pet_damage_spells"),
(49966, "spell_hun_pet_damage_spells"),
(83381, "spell_hun_pet_damage_spells");

DELETE FROM spell_script_names WHERE spell_id IN (53221, -53221) AND ScriptName="spell_hun_improved_steady_shot";
INSERT INTO spell_script_names  VALUES 
(-53221, "spell_hun_improved_steady_shot"); -- Rank 1
