

-- clean database for game_event darkmoon faire, as game_event 3,4,5,75

delete from game_event where eventEntry in (3, 4, 5, 75);
delete from game_event_creature where eventEntry in (3, 4, 5, 75);
delete from game_event_creature_quest where eventEntry in (3, 4, 5, 75);
delete from game_event_gameobject where eventEntry in (3, 4, 5, 75);
delete from game_event_gameobject_quest where eventEntry in (3, 4, 5, 75);
delete from game_event_seasonal_questrelation where eventEntry in (3, 4, 5, 75);
delete from game_event_seasonal_queststarter where eventEntry in (3, 4, 5, 75);

-- starting with npc that are spawned by script.
delete from creature where id in (15218, 33068, 16121, 32819, 21635, 55493, 35642, 55491, 55720, 55492);
delete from creature where id=52039 and guid=269009;
delete from creature where map=974;
-- delete all npc from database that should only be spawned on darkmoon island
delete from creature where id in (14822, 55475, 55402, 56044, 54595, 54551, 54596, 54510, 55220, 55341, 55229, 55226, 55231, 55221); 
delete from creature where id in (55225, 55342, 55230, 55268, 55269, 55270, 55271, 55250, 55251, 55252, 55253, 14823, 14827, 55347);
delete from creature where id in (55348, 56031, 14866, 14860, 55072, 55264, 55266, 55278, 56335, 56069, 54487, 55117, 14864, 55440);
delete from creature where id in (55119, 55446, 55596, 56129, 56131, 56130, 54546, 54601, 54485, 54490, 24171, 15303, 56043, 23619);
delete from creature where id in (57850, 14871, 14829, 14832, 14849, 14833, 55222, 55223, 56068, 55305, 55306, 55307, 14847, 55339);
delete from creature where id in (14845, 14846, 56035, 14844, 55714, 55444, 55448, 55443, 55120, 54605, 58570, 14841, 10445, 14828);
delete from creature where id in (57983, 55428, 55118, 55429, 55254, 55261, 55715, 55712, 55598, 55449, 55457, 55761, 55356, 54545);
delete from creature where id in (14868, 55609, 55602, 55487, 55741, 55699, 56160, 54518, 55181, 54642, 54643, 55749, 14867, 23623);
delete from creature where id in (55603, 55608, 14865, 55730, 54504, 23624, 55124, 55726, 55604, 55718, 55125, 55121, 55734, 55735);
delete from creature where id in (55724, 55133, 55249, 55247, 55248, 55732, 55733, 55713, 55719, 56026, 56025, 23626, 23625); 
delete from creature where id in (23721, 56041, 23830);

delete from gameobject where map=974;

DELETE FROM creature_addon WHERE guid=161890;
DELETE FROM creature_addon WHERE guid=166078;
DELETE FROM creature_addon WHERE guid=166058;
DELETE FROM creature_addon WHERE guid=166057;
DELETE FROM creature_addon WHERE guid=166056;
DELETE FROM creature_addon WHERE guid=166061;
DELETE FROM creature_addon WHERE guid=166060;
DELETE FROM creature_addon WHERE guid=166059;
DELETE FROM creature_addon WHERE guid=166077;
DELETE FROM creature_addon WHERE guid=166076;
DELETE FROM creature_addon WHERE guid=166075;
DELETE FROM creature_addon WHERE guid=166074;
DELETE FROM creature_addon WHERE guid=166073;
DELETE FROM creature_addon WHERE guid=166072;
DELETE FROM creature_addon WHERE guid=166069;
DELETE FROM creature_addon WHERE guid=166068;
DELETE FROM creature_addon WHERE guid=166067;
DELETE FROM creature_addon WHERE guid=166064;
DELETE FROM creature_addon WHERE guid=166063;
DELETE FROM creature_addon WHERE guid=166062;
DELETE FROM creature_addon WHERE guid=161837;
DELETE FROM creature_addon WHERE guid=165280;
DELETE FROM creature_addon WHERE guid=269388;
DELETE FROM creature_addon WHERE guid=269389;
DELETE FROM creature_addon WHERE guid=269391;
DELETE FROM creature_addon WHERE guid=269392;
DELETE FROM creature_addon WHERE guid=269393;
DELETE FROM creature_addon WHERE guid=269398;
DELETE FROM creature_addon WHERE guid=269411;
DELETE FROM creature_addon WHERE guid=269412;
DELETE FROM creature_addon WHERE guid=269413;
DELETE FROM creature_addon WHERE guid=269414;
DELETE FROM creature_addon WHERE guid=269415;
DELETE FROM creature_addon WHERE guid=269416;
DELETE FROM creature_addon WHERE guid=269417;
DELETE FROM creature_addon WHERE guid=269418;
DELETE FROM creature_addon WHERE guid=269419;

delete from game_event_gameobject where guid in (182482, 182483, 209710, 209714, 209797, 209812);
delete from game_event_gameobject where guid in (209829, 209874, 209883, 209897, 209908, 209974);

delete from gameobject where id in (180030, 180031, 180032, 180035, 180036, 180038, 180039, 180040, 180041, 180042, 180044, 180045);
delete from gameobject where id in (180029, 180046, 180048, 180053, 180335, 180524, 1798);

delete from gameobject where id=179976 and guid in (4359, 4360);
delete from gameobject where id=209634 and guid in (184503);
delete from gameobject where id=209571 and guid in (404241);

delete from gameobject where id=112192 and guid in (22188, 22186, 22187, 22189);
delete from gameobject where id=179965 and guid in (184471, 184518, 5626, 184525, 5630, 184535, 5627, 184504, 15917, 16322);
delete from gameobject where id=179965 and guid in (16865, 184419, 4133, 5634, 184422, 184453, 7443, 15785, 71921, 71913, 71916);
delete from gameobject where id=179965 and guid in (71917, 71919, 71918, 71920, 71914, 71912, 71922, 71915, 71911, 71910, 71909);
delete from gameobject where id=179965 and guid in (71899, 71906, 71905, 71903, 71900, 71902, 71895, 71898, 71897, 71901, 71894);
delete from gameobject where id=179965 and guid in (71904, 71893, 71896, 22205, 22207, 22209, 22206, 22208, 22203, 25672, 22198);
delete from gameobject where id=179965 and guid in (25669, 22199, 22202, 22204, 22197, 22196, 22201, 22200, 184530);
delete from gameobject where id=179968 and guid in (3310, 3308, 3309, 3307, 16869, 16868, 3280, 3278, 16867, 13298, 3281);
delete from gameobject where id=179968 and guid in (15326, 14870, 71981, 71983, 71985, 71984, 71982, 71986, 71987, 71988);
delete from gameobject where id=180034 and guid in (22218, 14238);
delete from gameobject where id=180037 and guid in (71976, 71977, 22249, 22248, 16488, 16483);
delete from gameobject where id=180043 and guid in (10392, 184415, 184476, 14475, 5375, 184527, 8515, 184458, 16926, 15865, 184432, 4041);
delete from gameobject where id=180043 and guid in (184493, 8517, 8516, 16940, 184526, 184528, 9661, 21, 16025, 184534, 184417, 71962);
delete from gameobject where id=180043 and guid in (71958, 71959, 71968, 71971, 71969, 71960, 71965, 71966, 71961, 71967, 71963, 71970);
delete from gameobject where id=180043 and guid in (71964, 22270, 22271, 22273, 22272, 22265, 22266, 22264, 22269, 22263, 22268, 22267);
delete from gameobject where id=180043 and guid in (22262, 184515, 184488, 184406, 184540, 184407, 184548, 184507, 184487, 184481, 184563);
delete from gameobject where id=180047 and guid in (72003, 72004, 72005, 22277, 22276, 22275, 10856, 10853, 10852);
delete from gameobject where id=180049 and guid in (10850, 10851, 198722);

delete from game_event_gameobject where guid in (21, 3278, 3280, 3281, 3307, 3308, 3309, 3310, 4041, 4133, 5375, 5626, 5627, 5630, 5634, 7443, 8515, 8516, 8517, 9661, 10392);
delete from game_event_gameobject where guid in (10489, 13298, 14475, 14741, 14870, 15326, 15785, 15865, 15917, 15959, 16025, 16322, 16483, 16488, 16865, 16867, 16868, 16869);
delete from game_event_gameobject where guid in (16926, 16940, 22196, 22197, 22198, 22199, 22200, 22201, 22202, 22203, 22204, 22205, 22206, 22207, 22208, 22209, 22248, 22249);
delete from game_event_gameobject where guid in (22262, 22263, 22264, 22265, 22266, 22267, 22268, 22269, 22270, 22271, 22272, 22273, 25646, 25669, 25672, 25673, 25675, 71893);
delete from game_event_gameobject where guid in (71894, 71895, 71896, 71897, 71898, 71899, 71900, 71901, 71902, 71903, 71904, 71905, 71906, 71909, 71910, 71911, 71912, 71913);
delete from game_event_gameobject where guid in (71914, 71915, 71916, 71917, 71918, 71919, 71920, 71921, 71922, 71958, 71959, 71960, 71961, 71962, 71963, 71964, 71965, 71966);
delete from game_event_gameobject where guid in (71967, 71968, 71969, 71970, 71971, 71976, 71977, 71981, 71982, 71983, 71984, 71985, 71986, 71987, 71988, 71995, 71996, 71997);
delete from game_event_gameobject where guid in (181006, 181010, 181011, 184403, 184406, 184407, 184415, 184417, 184419, 184422, 184432, 184440, 184453, 184458, 184471, 184476);
delete from game_event_gameobject where guid in (184481, 184487, 184488, 184493, 184504, 184507, 184515, 184518, 184525, 184526, 184527, 184528, 184530, 184534, 184535, 184540, 184548, 184563);



