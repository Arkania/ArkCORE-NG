
DELETE FROM phase_area WHERE areaId=4755 AND entry=3;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4755, 3, 2097152, 0, 656, 679, 1, "The Hunt For Sylvanas");

DELETE FROM phase_area WHERE areaId=4755 AND entry=3;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4755, 3, 24904, 24902, 64, 11, 1, "The Hunt For Sylvanas");

DELETE FROM phase_area WHERE areaId=4714 AND entry=2;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4714, 2, 24676, 24904, 74, 11, 1, "Gilneas City Battle");

DELETE FROM phase_area WHERE areaId=4755 AND entry=2;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4755, 2, 24676, 24904, 74, 11, 1, "Gilneas City Battle");

UPDATE creature_template SET ScriptName="npc_soultethered_banshee_38473" WHERE entry=38473;

UPDATE npc_text SET BroadcastTextID0=50737 WHERE ID=17830;

delete from creature_equip_template where entry=38464 and id=1;
insert into creature_equip_template values
(38464, 1, 30403, 30403, 18680);

delete from spell_script_names where spell_id=72050;
insert into spell_script_names values
(72050, "spell_fiery_boulder_72050");

delete from spell_script_names where spell_id=71388;
insert into spell_script_names values
(71388, "spell_rapier_of_the_gilnean_patriots_71388");


