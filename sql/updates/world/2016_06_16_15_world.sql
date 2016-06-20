
delete from npc_spellclick_spells where npc_entry=36839;
insert into npc_spellclick_spells values 
(36839, 70510, 1, 0);

delete from npc_spellclick_spells where npc_entry=35427;
insert into npc_spellclick_spells values 
(35427, 43671, 1, 0);

delete from npc_spellclick_spells where npc_entry=3683902;
insert into npc_spellclick_spells values 
(3683902, 46598, 1, 0);

delete from npc_spellclick_spells where npc_entry=3683903;
insert into npc_spellclick_spells values 
(3683903, 46598, 1, 0);

delete from smart_scripts where entryorguid in (-201435, -115958);
delete from smart_scripts where entryorguid in (9031, 16518, 36723, 39959, 43658, 44896, 45001, 45007, 45704, 45912);
delete from smart_scripts where entryorguid in (45915, 45919, 45922, 45924, 45926, 45928, 45930, 45932, 45935, 49045);
delete from smart_scripts where entryorguid in (20243, 26670, 207088);

delete from spell_script_names where spell_id in (78075, 82009, 83066, 81960, 85086, 85136);
delete from spell_script_names where spell_id in (85137, 85158, 85159, 88304, 99518);
