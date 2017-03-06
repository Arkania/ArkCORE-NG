

UPDATE creature_template SET npcflag=16777216 WHERE entry=48341;
UPDATE creature_template SET npcflag=16777216 WHERE entry=48342;
UPDATE creature_template SET npcflag=16777216 WHERE entry=48343;

delete from spell_script_names where spell_id=89842;
insert into spell_script_names values (89842, "spell_drink_tray_89842");

-- drink parts are spawned via script
delete from creature where guid in (145974, 145736, 145961, 145637, 145948, 145704, 145762, 145829);

-- spawned via script
delete from creature where id in (47314, 49532, 49534, 49535);

-- spawned via script
delete from creature where guid in (146184, 146179, 146230, 145711, 145655);

-- pool pool
delete from pool_template where entry in (14529, 14530, 14531, 14532, 14533, 14534, 14535, 14536, 14537, 14538, 14539, 14540, 14541);
insert into pool_template values
(14529,1, "deadmines ship 1"),
(14530,1, "deadmines ship 2"),
(14531,1, "deadmines ship 3"),
(14532,1, "deadmines ship 4"),
(14533,1, "deadmines ship 5"),
(14534,1, "deadmines ship 6"),
(14535,1, "deadmines ship 7"),
(14536,1, "deadmines ship 8"),
(14537,1, "deadmines ship 9"),
(14538,1, "deadmines ship 10"),
(14539,1, "deadmines ship 11"),
(14540,1, "deadmines ship 12"),
(14541,1, "deadmines ship 13");

delete from pool_creature where pool_entry in (14529, 14530, 14531, 14532, 14533, 14534, 14535, 14536, 14537, 14538, 14539, 14540, 14541);
insert into pool_creature values
(146260, 14529, 0, "group 1"),
(146187, 14529, 0, "group 1"),

(145997, 14530, 0, "group 2"),
(145780, 14530, 0, "group 2"),

(145949, 14531, 0, "group 3"),
(145987, 14531, 0, "group 3"),
(145734, 14531, 0, "group 3"),

(146234, 14532, 0, "group 4"),
(145932, 14532, 0, "group 4"),
(145654, 14532, 0, "group 4"),

(145824, 14533, 0, "group 5"),
(146197, 14533, 0, "group 5"),

(146188, 14534, 0, "group 6"),
(146200, 14534, 0, "group 6"),

(145772, 14535, 0, "group 7"),
(146001, 14535, 0, "group 7"),
(145933, 14535, 0, "group 7"),
(146241, 14535, 0, "group 7"),

(145676, 14536, 0, "group 8"),
(145850, 14536, 0, "group 8"),
(146239, 14536, 0, "group 8"),
(145956, 14536, 0, "group 8"),

(145981, 14537, 0, "group 9"),
(146237, 14537, 0, "group 9"),
(145721, 14537, 0, "group 9"),

(146212, 14538, 0, "group 10"),
(145638, 14538, 0, "group 10"),

(146215, 14539, 0, "group 11"),
(146178, 14539, 0, "group 11"),

(146201, 14540, 0, "group 12"),
(145696, 14540, 0, "group 12"),
(146216, 14540, 0, "group 12"),

(145707, 14541, 0, "group 13"),
(145927, 14541, 0, "group 13"),
(145650, 14541, 0, "group 13");

UPDATE creature_template SET minlevel=85, maxlevel=85, faction=17 WHERE entry=49539;

delete from creature where id=49539;

delete from creature where guid in (146071, 146176, 146263); -- 3 different vanessa von cleef, 49429, 49541, 57005
delete from creature where guid in (146248, 145773, 146247, 145839); -- group inside ship
delete from creature where guid in (146242, 146243, 146244, 146245, 146246); -- alliance group on shipdeck

delete from creature where guid in (145744, 145817, 145845); -- Miss Mayhem and his 2 golems





