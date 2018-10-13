
DELETE FROM spell_script_names WHERE spell_id=84963 and ScriptName="spell_pal_inquisition";
INSERT INTO spell_script_names VALUES 
(84963, "spell_pal_inquisition");

DELETE FROM spell_script_names WHERE spell_id IN (-87168, 87168) and ScriptName="spell_pal_long_arm_of_the_law";
INSERT INTO spell_script_names VALUES 
(-87168, "spell_pal_long_arm_of_the_law");

DELETE FROM spell_script_names WHERE spell_id=20271 and ScriptName="spell_pal_judgements";

DELETE FROM spell_script_names WHERE spell_id=20271 and ScriptName="spell_pal_long_arm_of_the_law";

DELETE FROM spell_script_names WHERE spell_id=20271 and ScriptName="spell_pal_judgement_20271";
INSERT INTO spell_script_names VALUES 
(20271, "spell_pal_judgement_20271");

DELETE FROM spell_script_names WHERE spell_id=54158 and ScriptName="spell_pal_judgement_54158";
INSERT INTO spell_script_names VALUES 
(54158, "spell_pal_judgement_54158");
