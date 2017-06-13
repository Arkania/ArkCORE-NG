

delete from phase_area where areaId=5335 and entry=0;

insert into phase_area values 
(5335, 0, 27938, 26426, 64, 11, 1, "Deepholm, Quartzite Basin");

delete from phase_area where areaId=5291 and entry=0;

insert into phase_area values 
(5291, 0, 27938, 26426, 64, 11, 1, "Deepholm, Jagged Wastes");

delete from spell_area where spell=81032 and area in (5291, 5335); -- invis 10

insert into spell_area values 
(81032, 5291, 27938, 26426, 0, 0, 0, 1, 64, 11),
(81032, 5335, 27938, 26426, 0, 0, 0, 1, 64, 11);

delete from spell_area where spell=84117 and area in (5303, 5042);
delete from spell_area where spell=84955 and area in (5303, 5042);
insert into spell_area values 
(84117, 5042, 27203, 28824, 0, 0, 2, 1, 64, 11), -- invis 16 for zone 5042
(84955, 5042, 27203, 28824, 0, 0, 2, 1, 64, 11), -- invis 19 for zone 5042
(84117, 5303, 27203, 28824, 0, 0, 2, 1, 64, 11), -- invis 16 for area 5303
(84955, 5303, 27203, 28824, 0, 0, 2, 1, 64, 11); -- invis 19 for area 5303

update creature set phaseId=253, spawntimesecs=120 where id=44684;

UPDATE creature_template_addon SET auras="13377" WHERE entry=44684;

UPDATE creature_template_addon SET auras="83458 12550" WHERE entry=44685;

update creature set phaseId=253, spawntimesecs=120 where id=44685;

UPDATE creature SET phaseId=253, spawntimesecs=120 WHERE guid=242917;

UPDATE creature_template_addon SET aiAnimKit=0, movementAnimKit=0, meleeAnimKit=0, auras="79949" WHERE entry=44674;

UPDATE gameobject SET phaseId=253 WHERE guid=184082;

UPDATE gameobject SET phaseId=254 WHERE guid=184086;

UPDATE gameobject SET phaseId=257, position_x=966.7031, position_y=514.1007, position_z=49.33476 WHERE guid=184089;

DELETE FROM creature WHERE id=44679 AND guid=24377;
INSERT INTO creature VALUES 
(24377, 44679, 646, 0, 0, 1, 253, 0, 0, 0, 967.946, 528.139, -49.22497, 6.091199, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=44679 AND guid=24647;
INSERT INTO creature VALUES 
(24647, 44679, 646, 0, 0, 1, 254, 0, 0, 0, 958.788, 513.247, -49.25147, 3.21689, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=44679 AND guid=33886;
INSERT INTO creature VALUES 
(33886, 44679, 646, 0, 0, 1, 257, 0, 0, 0, 989.63, 552.911, -49.25147, 5.131268, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0);

UPDATE creature SET position_x=1083.328, position_y=544.8106, position_z=-44.2405, orientation=3.2937 WHERE guid=6892;

DELETE FROM creature WHERE id=44672 AND guid=33907;
INSERT INTO creature VALUES 
(33907, 44672, 646, 0, 0, 1, 257, 0, 0, 0, 989.175, 534.063, -49.25147, 4.363323, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0);

UPDATE creature SET phaseId=253, position_x=995.613, position_y=521.274, position_z=-49.2591, orientation=.2094, spawntimesecs=120 WHERE guid=242290;

DELETE FROM creature WHERE id=43818 AND guid=34054;
INSERT INTO creature VALUES 
(34054, 43818, 646, 0, 0, 1, 254, 0, 0, 0, 978.7058, 506.7851, -49.33344, 1.231757, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=43818 AND guid=34296;
INSERT INTO creature VALUES 
(34296, 43818, 646, 0, 0, 1, 257, 0, 0, 0, 995.613, 521.274, -49.25907, 0.2094395, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=44666 AND guid=42450;
INSERT INTO creature VALUES 
(42450, 44666, 646, 0, 0, 1, 254, 0, 0, 0, 1007.78, 506.826, -49.33482, 4.4242, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0);

UPDATE creature SET position_x=1000.56, position_y=539.313, position_z=-49.2515, orientation=5.428, spawntimesecs=120 WHERE guid=244614;

DELETE FROM creature WHERE id=43835 AND guid=42524;
INSERT INTO creature VALUES 
(42524, 43835, 646, 0, 0, 1, 254, 0, 0, 0, 1000.56, 539.313, -49.33482, 3.958433, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=43835 AND guid=42533;
INSERT INTO creature VALUES 
(42533, 43835, 646, 0, 0, 1, 257, 0, 0, 0, 996.127, 523.915, -49.25147, 4.956735, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0);

update creature set phaseId=253, spawntimesecs=120 where id=44680;

update creature set phaseId=253, spawntimesecs=120 where id=44681;

UPDATE creature SET position_x=1019.35, position_y=542.892, position_z=-49.2515, orientation=4.3808, spawntimesecs=120 WHERE guid=243059;

DELETE FROM creature WHERE id=44670 AND guid=42775;
INSERT INTO creature VALUES 
(42775, 44670, 646, 0, 0, 1, 254, 0, 0, 0, 1019.35, 542.892, -49.25147, 4.380776, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=44670 AND guid=42799;
INSERT INTO creature VALUES 
(42799, 44670, 646, 0, 0, 1, 257, 0, 0, 0, 999.655, 533.346, -49.25147, 4.276057, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0);

UPDATE gameobject SET phaseId=253, spawntimesecs=120 WHERE guid in (184083, 184084, 184085);

UPDATE gameobject SET phaseId=254, spawntimesecs=120 WHERE guid in (184079, 184080, 184081);

UPDATE creature SET phaseId=252, spawntimesecs=120 WHERE id in (42916, 44079);

DELETE FROM creature WHERE id=44361;
INSERT INTO creature VALUES 
(279202, 44361, 646, 0, 0, 1, 169, 0, 0, 0, 1033.17, 503.28, -49.2515, 2.30383, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=45038 AND guid=42802;
INSERT INTO creature VALUES 
(42802, 45038, 646, 0, 0, 1, 169, 0, 0, 0, 1015.705, 627.4106, -42.46944, 2.696179, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0);

UPDATE creature SET position_x=1014.649, position_y=629.9149, position_z=-42.59, spawntimesecs=120 WHERE guid=243261;

DELETE FROM waypoint_data WHERE id=243261;
INSERT INTO waypoint_data VALUES 
(243261, 0, 1014.649, 629.9149, -42.59003, 0.517896, 2000, 0, 0, 100, 0),
(243261, 1, 987.195, 609.9794, -37.83846, 4.93576, 0, 0, 0, 100, 0),
(243261, 2, 980.0827, 606.7534, -36.97883, 4.177852, 0, 0, 0, 100, 0),
(243261, 3, 983.6665, 604.3462, -37.21791, 3.950096, 0, 0, 0, 100, 0),
(243261, 4, 983.6665, 604.3462, -37.21791, 3.950096, 0, 0, 0, 100, 0),
(243261, 5, 1006.354, 627.1851, -41.04898, 0.792792, 0, 0, 0, 100, 0),
(243261, 6, 1020.551, 633.4536, -43.7975, 0.415801, 0, 0, 0, 100, 0),
(243261, 7, 1043.727, 627.1018, -45.11422, 6.015692, 0, 0, 0, 100, 0),
(243261, 8, 1030.482, 587.0541, -44.54068, 4.409558, 0, 0, 0, 100, 0),
(243261, 9, 1027.457, 575.668, -49.20658, 4.452754, 0, 0, 0, 100, 0),
(243261, 10, 1019.298, 547.4475, -49.33449, 4.429192, 0, 0, 0, 100, 0),
(243261, 11, 1036.772, 524.0447, -49.33449, 5.19495, 0, 0, 0, 100, 0),
(243261, 12, 1030.389, 508.4818, -49.33449, 5.163534, 0, 0, 0, 100, 0),
(243261, 13, 1056.519, 475.7188, -44.58757, 5.383439, 0, 0, 0, 100, 0),
(243261, 14, 1080.896, 449.0104, -44.76828, 5.469831, 0, 0, 0, 100, 0),
(243261, 15, 1098.275, 452.5297, -44.96379, 0.199808, 0, 0, 0, 100, 0),
(243261, 16, 1113.255, 476.3462, -44.77226, 1.146213, 0, 0, 0, 100, 0),
(243261, 17, 1095.233, 498.3722, -44.28548, 2.556004, 2000, 0, 0, 100, 0);

UPDATE quest_template SET PrevQuestId=27007 WHERE Id=27100;

UPDATE quest_template SET RequiredRaces=2098253 WHERE Id=27952;

UPDATE quest_template SET RequiredRaces=946 WHERE Id=27953;

UPDATE quest_template SET RequiredRaces=2098253 WHERE Id=27006;

UPDATE quest_template SET RequiredRaces=946 WHERE Id=27008;

UPDATE quest_template SET RequiredRaces=2098253 WHERE Id=27952;

delete from game_event_gameobject where eventEntry=12 and guid=404160;

insert into game_event_gameobject values 
(12, 404160);


