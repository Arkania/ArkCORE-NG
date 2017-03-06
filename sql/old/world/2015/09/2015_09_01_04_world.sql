

-- not implemented type 12 in core
delete from achievement_criteria_data where type=12;

-- not implemented type 26 in core
delete from achievement_criteria_data where type=26;

delete from achievement_criteria_data where criteria_id in (12959, 12960) and type=8;

delete from achievement_criteria_data where criteria_id=72 and type=10;

delete from gossip_menu where entry=10036 and text_id=13930;
insert into gossip_menu values (10036, 13930);

delete from gossip_menu_option where menu_id=10036 and id=0;
insert into gossip_menu_option values 
(10036, 0, 0, "Hold on friend. Tell me what happened here.", 31934, 1, 1, 10037, 0, 0, 0, 0, "", 0);

delete from smart_scripts where entryorguid in (3636,3669,3671,3673,3674,3835,3840,5048,5053,5055,5755,5756,5761,5775,11318,11319,11320,11321,11322,11323,11324,11782,33419);
delete from smart_scripts where entryorguid in (2484, 2485, 3631, 3632, 3633, 3634, 3638, 11686, 11778, 11788, 11781, 37212);
delete from smart_scripts where entryorguid in (8477, 10820);

delete from npc_spellclick_spells where npc_entry=42015	AND spell_id=78357;

-- we can not loot all objects.. only keystone..
delete from gameobject_loot_template where entry in (207187, 207188, 202655, 203078, 203071, 207189, 204282, 206836, 207190);
insert into gameobject_loot_template values
(202655, 63128, 5, 1, 0, 1, 1),
(203071, 63127, 5, 1, 0, 1, 1),
(203078, 64396, 5, 1, 0, 1, 1),
(204282, 52843, 5, 1, 0, 1, 1),
(207187, 64392, 5, 1, 0, 1, 1),
(207188, 64394, 5, 1, 0, 1, 1),
(207189, 64395, 5, 1, 0, 1, 1),
(207190, 64397, 5, 1, 0, 1, 1);

delete from gameobject where id in (207187, 207188, 202655, 203078, 203071, 207189, 204282, 206836, 207190);

update creature set MovementType=0 where guid=3906;

