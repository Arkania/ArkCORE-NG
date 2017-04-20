
-- ally
delete from gameobject_queststarter where id in (206111,206294) and quest=28825;
insert into gameobject_queststarter values 
(206111, 28825),
(206294, 28825);

-- horde
delete from gameobject_queststarter where id in (206109,206116) and quest=28790;
insert into gameobject_queststarter values 
(206109, 28790),
(206116, 28790);

delete from areatrigger_scripts where entry in (4801,4802,7354,2746,7350);
insert into areatrigger_scripts values 
(2746, "at_stormwind_command_board"),
(7350, "at_stormwind_teleport_area"),
(4801, "at_orgrimmar_command_board_1"),
(4802, "at_orgrimmar_command_board_2"),
(7354, "at_orgrimmar_teleport_area");

UPDATE creature_template SET AIName="", ScriptName="" WHERE entry=45244;

delete from smart_scripts where entryorguid=45244;

delete from gameobject_addon where guid=181397;
insert into gameobject_addon values 
(181397, 8, 1);

DELETE FROM spell_area WHERE spell=49417 AND area=5429;
INSERT INTO spell_area (spell, area, quest_start, quest_end, aura_spell, racemask, gender, autocast, quest_start_status, quest_end_status) VALUES 
(49417, 5429, 27203, 27946, 0, 0, 2, 1, 74, 9);

UPDATE creature_template SET AIName="", ScriptName="" WHERE entry=45226;

delete from smart_scripts where entryorguid=45226;

delete from gameobject_addon where guid=207807;
insert into gameobject_addon values 
(207807, 8, 1);

DELETE FROM spell_area WHERE spell=49417 AND area=5428;
INSERT INTO spell_area (spell, area, quest_start, quest_end, aura_spell, racemask, gender, autocast, quest_start_status, quest_end_status) VALUES 
(49417, 5428, 27203, 27946, 0, 0, 2, 1, 74, 9);


