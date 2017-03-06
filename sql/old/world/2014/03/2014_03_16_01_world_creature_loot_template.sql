

-- loot for Halfus Wyrmbreaker
delete from creature_loot_template where entry=44600 and item in (0,59469,59470,59471,59472,59473,59474,59475,59476,59481,59482,59483,59484);
insert into creature_loot_template values(44600,59469,11,1,0,1,1);
insert into creature_loot_template values(44600,59470,16,1,0,1,1);
insert into creature_loot_template values(44600,59471,17,1,0,1,1);
insert into creature_loot_template values(44600,59472,16,1,0,1,1);
insert into creature_loot_template values(44600,59473,22,1,0,1,1);
insert into creature_loot_template values(44600,59474,16,1,0,1,1);
insert into creature_loot_template values(44600,59475,18,1,0,1,1);
insert into creature_loot_template values(44600,59476,12,1,0,1,1);
insert into creature_loot_template values(44600,59481,12,1,0,1,1);
insert into creature_loot_template values(44600,59482,12,1,0,1,1);
insert into creature_loot_template values(44600,59483,24,1,0,1,1);
insert into creature_loot_template values(44600,59484,22,1,0,1,1);

-- loot for Theralion
delete from creature_loot_template where entry=45993 and item in (0,59512,59516,59519,63534,63535,63536);
insert into creature_loot_template values(45993,59512,20,1,0,1,1);
insert into creature_loot_template values(45993,59516,20,1,0,1,1);
insert into creature_loot_template values(45993,59519,20,1,0,1,1);
insert into creature_loot_template values(45993,63534,10,1,0,1,1);
insert into creature_loot_template values(45993,63535,10,1,0,1,1);
insert into creature_loot_template values(45993,63536,19,1,0,1,1);


-- loot for Valiona
delete from creature_loot_template where entry=45992 and item in (0,59515,59517,59518,63531,63532,63533);
insert into creature_loot_template values(45992,59515,17,1,0,1,1);
insert into creature_loot_template values(45992,59517,24,1,0,1,1);
insert into creature_loot_template values(45992,59518,18,1,0,1,1);
insert into creature_loot_template values(45992,63531,12,1,0,1,1);
insert into creature_loot_template values(45992,63532,15,1,0,1,1);
insert into creature_loot_template values(45992,63533,15,1,0,1,1);

-- loot for Elementium Monstrosity
delete from creature_loot_template where entry=43735 and item in (0,59513,59514);
delete from creature_loot_template where entry=43735 and item between 59502 and 59511;
insert into creature_loot_template values(43735,59502,16,1,0,1,1);
insert into creature_loot_template values(43735,59503,16,1,0,1,1);
insert into creature_loot_template values(43735,59504,16,1,0,1,1);
insert into creature_loot_template values(43735,59505,10,1,0,1,1);
insert into creature_loot_template values(43735,59506,22,1,0,1,1);
insert into creature_loot_template values(43735,59507,16,1,0,1,1);
insert into creature_loot_template values(43735,59508,13,1,0,1,1);
insert into creature_loot_template values(43735,59509,13,1,0,1,1);
insert into creature_loot_template values(43735,59510,13,1,0,1,1);
insert into creature_loot_template values(43735,59511,14,1,0,1,1);
insert into creature_loot_template values(43735,59513,18,1,0,1,1);
insert into creature_loot_template values(43735,59514,27,1,0,1,1);

-- loot for Feludius <Ascendant Lord>
delete from creature_loot_template where entry=43687 and item in (59513,59514);
delete from creature_loot_template where entry=43687 and item between 59502 and 59511;
insert into creature_loot_template values(43687,59502,16,1,0,1,1);
insert into creature_loot_template values(43687,59503,16,1,0,1,1);
insert into creature_loot_template values(43687,59504,16,1,0,1,1);
insert into creature_loot_template values(43687,59505,10,1,0,1,1);
insert into creature_loot_template values(43687,59506,22,1,0,1,1);
insert into creature_loot_template values(43687,59507,16,1,0,1,1);
insert into creature_loot_template values(43687,59508,13,1,0,1,1);
insert into creature_loot_template values(43687,59509,13,1,0,1,1);
insert into creature_loot_template values(43687,59510,13,1,0,1,1);
insert into creature_loot_template values(43687,59511,14,1,0,1,1);
insert into creature_loot_template values(43687,59513,18,1,0,1,1);
insert into creature_loot_template values(43687,59514,27,1,0,1,1);

-- Ignacious <Ascendant Lord> 43686
delete from creature_loot_template where entry=43686 and item in (59513,59514);
delete from creature_loot_template where entry=43686 and item between 59502 and 59511;
insert into creature_loot_template values(43686,59502,16,1,0,1,1);
insert into creature_loot_template values(43686,59503,16,1,0,1,1);
insert into creature_loot_template values(43686,59504,16,1,0,1,1);
insert into creature_loot_template values(43686,59505,10,1,0,1,1);
insert into creature_loot_template values(43686,59506,22,1,0,1,1);
insert into creature_loot_template values(43686,59507,16,1,0,1,1);
insert into creature_loot_template values(43686,59508,13,1,0,1,1);
insert into creature_loot_template values(43686,59509,13,1,0,1,1);
insert into creature_loot_template values(43686,59510,13,1,0,1,1);
insert into creature_loot_template values(43686,59511,14,1,0,1,1);
insert into creature_loot_template values(43686,59513,18,1,0,1,1);
insert into creature_loot_template values(43686,59514,27,1,0,1,1);

-- Arion <Ascendant Lord> 43688
delete from creature_loot_template where entry=43688 and item in (59513,59514);
delete from creature_loot_template where entry=43688 and item between 59502 and 59511;
insert into creature_loot_template values(43688,59502,16,1,0,1,1);
insert into creature_loot_template values(43688,59503,16,1,0,1,1);
insert into creature_loot_template values(43688,59504,16,1,0,1,1);
insert into creature_loot_template values(43688,59505,10,1,0,1,1);
insert into creature_loot_template values(43688,59506,22,1,0,1,1);
insert into creature_loot_template values(43688,59507,16,1,0,1,1);
insert into creature_loot_template values(43688,59508,13,1,0,1,1);
insert into creature_loot_template values(43688,59509,13,1,0,1,1);
insert into creature_loot_template values(43688,59510,13,1,0,1,1);
insert into creature_loot_template values(43688,59511,14,1,0,1,1);
insert into creature_loot_template values(43688,59513,18,1,0,1,1);
insert into creature_loot_template values(43688,59514,27,1,0,1,1);

-- Terrastra <Ascendant Lord> 43689
delete from creature_loot_template where entry=43689 and item in (59513,59514);
delete from creature_loot_template where entry=43689 and item between 59502 and 59511;
insert into creature_loot_template values(43689,59502,16,1,0,1,1);
insert into creature_loot_template values(43689,59503,16,1,0,1,1);
insert into creature_loot_template values(43689,59504,16,1,0,1,1);
insert into creature_loot_template values(43689,59505,10,1,0,1,1);
insert into creature_loot_template values(43689,59506,22,1,0,1,1);
insert into creature_loot_template values(43689,59507,16,1,0,1,1);
insert into creature_loot_template values(43689,59508,13,1,0,1,1);
insert into creature_loot_template values(43689,59509,13,1,0,1,1);
insert into creature_loot_template values(43689,59510,13,1,0,1,1);
insert into creature_loot_template values(43689,59511,14,1,0,1,1);
insert into creature_loot_template values(43689,59513,18,1,0,1,1);
insert into creature_loot_template values(43689,59514,27,1,0,1,1);

-- Cho'gall 43324
delete from creature_loot_template where entry=43324 and item in (0,59330,59490,59494,59495,63680,64314,64315,64316);
delete from creature_loot_template where entry=43324 and item between 59485 and 59487;
delete from creature_loot_template where entry=43324 and item between 59497 and 59501;
insert into creature_loot_template values(43324,59330,24,1,0,1,1);
insert into creature_loot_template values(43324,59485,16,1,0,1,1);
insert into creature_loot_template values(43324,59486,11,1,0,1,1);
insert into creature_loot_template values(43324,59487,16,1,0,1,1);
insert into creature_loot_template values(43324,59490,16,1,0,1,1);
insert into creature_loot_template values(43324,59494,14,1,0,1,1);
insert into creature_loot_template values(43324,59495,9,1,0,1,1);
insert into creature_loot_template values(43324,59497,9,1,0,1,1);
insert into creature_loot_template values(43324,59498,15,1,0,1,1);
insert into creature_loot_template values(43324,59499,9,1,0,1,1);
insert into creature_loot_template values(43324,59500,19,1,0,1,1);
insert into creature_loot_template values(43324,59501,18,1,0,1,1);
insert into creature_loot_template values(43324,63680,19,1,0,1,1);
insert into creature_loot_template values(43324,64314,39,1,0,1,1);
insert into creature_loot_template values(43324,64315,30,1,0,1,1);
insert into creature_loot_template values(43324,64316,29,1,0,1,1);

-- Sinestra <Consort of Deathwing> 45213
delete from creature_loot_template where entry=45213 and item between 60226 and 60238;
insert into creature_loot_template values(45213,60226,44,0,0,1,1);
insert into creature_loot_template values(45213,60227,26,0,0,1,1);
insert into creature_loot_template values(45213,60228,41,0,0,1,1);
insert into creature_loot_template values(45213,60229,6,0,0,1,1);
insert into creature_loot_template values(45213,60230,32,0,0,1,1);
insert into creature_loot_template values(45213,60231,26,0,0,1,1);
insert into creature_loot_template values(45213,60232,56,0,0,1,1);
insert into creature_loot_template values(45213,60233,53,0,0,1,1);
insert into creature_loot_template values(45213,60234,24,0,0,1,1);
insert into creature_loot_template values(45213,60235,6,0,0,1,1);
insert into creature_loot_template values(45213,60236,9,0,0,1,1);
insert into creature_loot_template values(45213,60237,50,0,0,1,1);
insert into creature_loot_template values(45213,60238,6,0,0,1,1);












