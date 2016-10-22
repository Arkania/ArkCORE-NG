
delete from creature where id=37179;

UPDATE creature SET spawndist=0, MovementType=0 WHERE guid=249060 and id=48526;

UPDATE creature_template_addon SET auras="90366" WHERE entry=48526;

UPDATE creature_template SET faction=2204, unit_flags=8, unit_flags2=67584, VehicleId=579, ScriptName="npc_bilgewater_buccaneer_37213" WHERE entry=37213;

update creature set modelid=31295 where id=37203 and guid=245281;

UPDATE creature_template SET ScriptName="npc_fourth_and_goal_target_37203" WHERE entry=37203;

delete from spell_script_names where spell_id=70052;
insert into spell_script_names values 
(70052, "spell_kick_footbomb_70052");

delete from creature where id=42196 and guid=52753;
insert into creature values 
(52753, 42196, 648, 0, 0, 1, 378, 20024, 0, -8421.41, 1482.6, 100.6743, 0, 500, 0, 0, 6141, 0, 0, 0, 0, 0);

UPDATE creature_template SET InhabitType=5, ScriptName="npc_deathwing_48572" WHERE entry=48572;
UPDATE creature_template SET minlevel=88, maxlevel=88, faction=14, unit_flags=33587968 WHERE entry=48572;

UPDATE creature_template SET InhabitType=5 WHERE entry=42196;

DELETE FROM creature_template_addon WHERE entry=48572;
INSERT INTO creature_template_addon VALUES 
(48572, 0, 0, 50331648, 1, 0, "");



