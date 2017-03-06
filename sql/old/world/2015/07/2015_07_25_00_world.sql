
-- instance deadmines 
delete from creature_text where entry=646;
insert into creature_text values
(646, 0, 0, "You there! Check out that noise!", 14, 0, 100, 0, 0, 5775, "smite SAY_CHECK", 1148),
(646, 1, 0, "We're under attack! Avast, ye swabs! Repel the invaders!", 14, 0, 100, 0, 0, 5777, "smite SAY_AGGRO", 1149);

delete from creature_text where entry=47162;
insert into creature_text values
(47162, 0, 0, "Glubtok show you da power of de arcane!", 14, 0, 100, 0, 0, 21151, "Glubthok yell on Aggro", 47256),
(47162, 1, 0, "ARCANE POWER!!!", 14, 0, 100, 0, 0, 21146, "Glubthok yell on phase2", 47363),
(47162, 2, 0, "Sploded dat one!", 14, 0, 100, 0, 0, 21155, "Glubthok yell on kill", 47434),
(47162, 3, 0, "TOO...MUCH...POWER!!!", 14, 0, 100, 0, 0, 21145, "Glubthok yell on death", 47422),
(47162, 4, 0, "Ha ha ha!", 14, 0, 100, 0, 0, 21152, "Glubthok yell on Kill start", 47410),
(47162, 5, 0, "Fists of flame!", 14, 0, 100, 0, 0, 21153, "Glubthok yell", 47239),
(47162, 6, 0, "Fists of frost!", 14, 0, 100, 0, 0, 21156, "Glubthok yell", 47238),
(47162, 7, 0, "Glubtok ready?", 14, 0, 100, 0, 0, 21154, "Glubthok yell", 47361),
(47162, 8, 0, "Let's do it!", 14, 0, 100, 0, 0, 0, "Glubthok yell", 47362);

update creature set MovementType=0 where id in(48284, 48340, 48341, 48342, 48343);
update creature_template set faction=14 where entry=48351;

update creature_template set AIName="", ScriptName="boss_admiral_ripsnarl" where entry=47626;
update creature_template set AIName="", ScriptName="boss_captain_cookie" where entry=47739;
update creature_template set AIName="", ScriptName="boss_foo_reaper_5000" where entry=43778;
update creature_template set AIName="", ScriptName="boss_glubtok" where entry=47162;
update creature_template set AIName="", ScriptName="boss_lumbering_oaf" where entry=47297;
update creature_template set AIName="", ScriptName="boss_helix_gearbreaker" where entry=47296;
update creature_template set AIName="", ScriptName="boss_mr_smite" where entry=646;
update creature_template set AIName="", ScriptName="boss_vanessa_van_cleef" where entry=49541;

-- npc spawned by instance script
delete from creature where guid in (145859, 145858, 145731, 145776, 145977, 145798, 145966, 145621, 145674, 145799);
delete from creature where guid in (146170, 146175, 145860, 145861, 145862, 145865, 145866, 145867, 145855, 145856, 145857, 145864, 145863);

update gameobject_template set AIName="", ScriptName="go_factory_lever_101831" where entry=101831;
update gameobject_template set AIName="", ScriptName="go_mastroom_lever_101832" where entry=101832;
update gameobject_template set AIName="", ScriptName="go_foundry_lever_101834" where entry=101834;
update gameobject_template set AIName="", ScriptName="go_ironclad_lever_101833" where entry=101833;

update gameobject_template set AIName="", ScriptName="go_factory_door_13965" where entry=13965;
update gameobject_template set AIName="", ScriptName="go_mastroom_door_16400" where entry=16400;
update gameobject_template set AIName="", ScriptName="go_foundry_door_16399" where entry=16399;
update gameobject_template set AIName="", ScriptName="go_ironclad_door_16397" where entry=16397;

delete from gameobject where guid=216217;
insert into gameobject values
(216217, 16397, 36, 1, 1, -100.502, -668.771, 7.41049, 1.81514, 0, 0, 0.788011, 0.615662, 180, 100, 1);

-- 2 doors on same place
delete from gameobject where guid=20910 and id=16399;

-- http://www.wowhead.com/npc=47296/helix-gearbreaker
-- http://www.wowhead.com/npc=47297/lumbering-oaf

update creature_template_addon set mount=0 where entry=47296;
delete from creature where guid=145673 and id=47296;

-- mops are spawned from spell
delete from creature where id=49494 and guid in (146081, 146082);

-- dream dialog.. mops are spawned from spell
update creature set phaseMask=2 where guid in (146077, 145870, 146078);
update creature set phaseMask=2 where guid in (146079, 146080);

-- pool pool
delete from pool_template where entry in (14519, 14520, 14521, 14522, 14523, 14524, 14525, 14526, 14527, 14528);
insert into pool_template values
(14519,1, "deadmines foundry 1"),
(14520,1, "deadmines foundry 2"),
(14521,1, "deadmines foundry 3"),
(14522,1, "deadmines foundry 4"),
(14523,1, "deadmines foundry 5"),
(14524,1, "deadmines foundry 6"),
(14525,1, "deadmines foundry 7"),
(14526,1, "deadmines foundry 8"),
(14527,1, "deadmines foundry 9"),
(14528,1, "deadmines foundry 10");

delete from pool_creature where pool_entry in (14519, 14520, 14521, 14522, 14523, 14524, 14525, 14526, 14527, 14528);
insert into pool_creature values
(145924, 14519, 0, "group 1"),
(146221, 14519, 0, "group 1"),

(145874, 14520, 0, "group 2"),
(145873, 14520, 0, "group 2"),

(145876, 14521, 0, "group 3"),
(145879, 14521, 0, "group 3"),

(145923, 14522, 0, "group 4"),
(145880, 14522, 0, "group 4"),

(145646, 14523, 0, "group 5"),
(145871, 14523, 0, "group 5"),

(146008, 14524, 0, "group 6"),
(145842, 14524, 0, "group 6"),

(145869, 14525, 0, "group 7"),
(145970, 14525, 0, "group 7"),
(145875, 14525, 0, "group 7"),

(145872, 14526, 0, "group 8"),
(145952, 14526, 0, "group 8"),

(146009, 14527, 0, "group 9"),
(145881, 14527, 0, "group 9"),
(146050, 14527, 0, "group 9"),

(145878, 14528, 0, "group 10"),
(146647, 14528, 0, "group 10");

-- dream dialog.. mops are spawned from spell
update creature set phaseMask=2 where guid in (146092, 146093);

-- Vanessa Lightning Platter  Npc Map not available, NPC may be spawned via a script 
delete from creature where id in (49520, 49521);

delete from creature where id in (49229, 49495);

-- dream dialog.. mops are spawned from spell
update creature set phaseMask=2 where guid in (146157, 146158, 146159);

update gameobject_template set AIName="", ScriptName="go_defias_cannon_16398" where entry=16398;
update creature_template set AIName="", ScriptName="npc_defias_cannon_48266" where entry=48266;

SET @FLAG=134742016; -- 134807552   --134742016; -- 524288; 
SET @SFLAG=4;
UPDATE quest_template SET Flags=@FLAG, SpecialFlags=@SFLAG, NextQuestId=27758 WHERE Id=27756;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Sprecht mit Leutnant Horatio Laine in den Todesminen." WHERE Id=27756;
UPDATE quest_template SET RequiredSourceItemId1=62334, RequiredSourceItemId4=0, RequiredSourceItemCount1=1, RequiredSourceItemCount4=0 WHERE Id=27756;

UPDATE quest_template SET PrevQuestId=27756, Flags=@FLAG, SpecialFlags=@SFLAG WHERE Id=27758;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Sprecht mit Leutnant Horatio Laine in den Todesminen." WHERE Id=27758;
UPDATE quest_template SET SourceItemId=62334, SourceItemCount=1, RequiredSourceItemId1=62334, RequiredSourceItemCount1=1 WHERE Id=27758;

UPDATE quest_template SET PrevQuestId=27758, Flags=@FLAG,  SpecialFlags=@SFLAG WHERE Id=27781;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Sprecht mit Leutnant Horatio Laine in den Todesminen." WHERE Id=27781;
UPDATE quest_template SET SourceItemId=62334, SourceItemCount=1, RequiredSourceItemId1=62334, RequiredSourceItemCount1=1 WHERE Id=27781;

UPDATE quest_template SET PrevQuestId=27781, Flags=@FLAG,  SpecialFlags=@SFLAG WHERE Id=27785;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Sprecht mit Leutnant Horatio Laine in den Todesminen." WHERE Id=27785;
UPDATE quest_template SET SourceItemId=62334, SourceItemCount=1, RequiredSourceItemId1=62334, RequiredSourceItemCount1=1 WHERE Id=27785;

UPDATE quest_template SET PrevQuestId=27785, Flags=524296, SpecialFlags=@SFLAG WHERE Id=27790;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Sprecht mit Leutnant Horatio Laine in den Todesminen." WHERE Id=27790;
UPDATE quest_template SET SourceItemId=62334, SourceItemCount=1, RequiredSourceItemId1=62334, RequiredSourceItemCount1=1 WHERE Id=27790;

UPDATE quest_template SET Flags=@FLAG, SpecialFlags=@SFLAG WHERE Id in (27842, 27844, 27847, 27848, 27850);
UPDATE quest_template SET NextQuestId=27844 WHERE Id=27842;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Sprecht mit Kagtha in den Todesminen." WHERE Id=27842;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Sprecht mit Kagtha in den Todesminen." WHERE Id=27844;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Sprecht mit Kagtha in den Todesminen." WHERE Id=27847;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Sprecht mit Kagtha in den Todesminen." WHERE Id=27848;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Sprecht mit Kagtha in den Todesminen." WHERE Id=27850;

-- delete from creature_queststarter where id=47162 and quest=27756;
-- delete from creature_queststarter where id=47162 and quest=27842;

update quest_template set RequiredRaces=2098253  where Id in (27756, 27758, 27781, 27785, 27790);
update quest_template set RequiredRaces=946 where Id in (27842, 27844, 27847, 27848, 27850);

-- 88906 89652 89706
update creature_template_addon set auras=NULL where entry=48229;

update creature_template set faction=35 where entry in (48975, 48976, 49041, 49042);

update creature_template set InhabitType=4 where entry=47242;

update creature set MovementType=2 where guid=145781;
insert ignore into creature_addon (guid) value(145781);
update creature_addon set path_id=145781 where guid=145781;
delete from waypoint_data where id=145781;
insert into waypoint_data (id, point, position_x, position_y, position_z) values (145781, 0, -187.7809, -496.4649, 53.43021);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (145781, 1, -188.2805, -497.7679, 53.42399);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (145781, 2, -188.5305, -498.5179, 53.42399);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (145781, 3, -191.5305, -500.5179, 53.17399);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (145781, 4, -193.2846, -501.5853, 53.10095);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (145781, 5, -195.5346, -503.0853, 53.60095);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (145781, 6, -199.0346, -505.3353, 53.35095);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (145781, 7, -199.8429, -505.8283, 53.07471);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (145781, 8, -202.8429, -505.5783, 52.82471);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (145781, 9, -204.5929, -505.5783, 52.57471);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (145781, 10, -205.932, -505.509, 51.93829);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (145781, 11, -204.656, -505.542, 52.485);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (145781, 12, -202.906, -505.792, 52.735);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (145781, 13, -199.6233, -505.7488, 53.11173);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (145781, 14, -195.3733, -502.9988, 53.61173);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (145781, 15, -194.9211, -502.6909, 53.22779);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (145781, 16, -192.9216, -501.3915, 53.23337);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (145781, 17, -191.6716, -500.6415, 52.98337);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (145781, 18, -188.422, -498.592, 53.23896);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (145781, 19, -188.0654, -498.3488, 53.28645);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (145781, 20, -187.0654, -493.3488, 53.78645);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (145781, 21, -186.297, -490.74, 53.58403);

update creature set MovementType=2 where guid=146007;
insert ignore into creature_addon (guid) value(146007);
update creature_addon set path_id=146007 where guid=146007;
delete from waypoint_data where id=146007;
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 0, -214.7209, -500.1381, 50.13339);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 1, -215.1694, -499.6891, 49.94113);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 2, -216.1694, -498.9391, 49.69113);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 3, -217.4194, -497.6891, 49.44113);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 4, -219.9194, -495.1891, 48.69113);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 5, -220.1903, -495.1266, 48.66558);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 6, -220.6903, -494.3766, 48.41558);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 7, -221.4403, -493.6266, 48.41558);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 8, -223.776, -491.035, 48.09993);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 9, -223.7307, -490.8906, 48.22522);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 10, -226.716, -488.9385, 48.327);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 11, -227.287, -488.1827, 48.5573);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 12, -230.1799, -485.971, 48.66693);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 13, -231.419, -484.6175, 48.8757);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 14, -232.419, -484.1175, 49.1257);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 15, -233.8588, -483.2879, 49.01107);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 16, -234.5529, -482.789, 49.25063);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 17, -236.8029, -482.539, 49.25063);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 18, -238.2535, -482.4292, 49.10532);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 19, -239.6242, -482.1886, 49.21041);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 20, -241.3742, -482.6886, 48.96041);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 21, -241.8715, -482.619, 48.90281);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 22, -240.3715, -482.369, 49.15281);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 23, -240.0698, -482.3726, 48.99197);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 24, -239.5698, -482.3726, 49.24197);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 25, -237.0698, -482.6226, 49.24197);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 26, -236.4474, -482.5974, 49.16932);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 27, -234.4027, -482.7622, 49.22845);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 28, -232.4027, -484.0122, 48.97845);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 29, -232.3407, -484.2829, 48.9041);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 30, -231.0739, -484.8999, 48.88837);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 31, -228.8199, -487.1763, 48.52761);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 32, -227.0479, -488.6057, 48.56377);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 33, -225.2354, -489.9943, 48.21265);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 34, -223.4267, -491.1171, 48.23076);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 35, -221.9267, -492.8671, 48.23076);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 36, -221.1767, -493.8671, 48.23076);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 37, -221.9789, -493.1433, 47.84938);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 38, -220.8005, -494.1376, 48.44578);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 39, -220.3005, -494.6376, 48.69578);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 40, -217.3005, -497.6376, 49.44578);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 41, -216.5505, -498.3876, 49.69578);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 42, -216.799, -498.4706, 49.40113);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 43, -216.3445, -498.8057, 49.84602);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 44, -215.8445, -499.0557, 49.84602);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 45, -214.8445, -499.8057, 50.34602);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 46, -213.3445, -500.8057, 51.34602);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 47, -210.8899, -502.6407, 51.29091);
insert into waypoint_data (id, point, position_x, position_y, position_z) values (146007, 48, -213.256, -500.8863, 51.41654);





