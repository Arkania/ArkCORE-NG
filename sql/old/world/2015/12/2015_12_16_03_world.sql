
set @GUID=50039;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
update creature_addon set path_id=@GUID where guid=@GUID;

set @GUID=49992;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
update creature_addon set path_id=@GUID where guid=@GUID;

set @GUID=48620;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
update creature_addon set path_id=@GUID where guid=@GUID;

set @GUID=49393;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
update creature_addon set path_id=@GUID where guid=@GUID;

set @GUID=50035;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
update creature_addon set path_id=@GUID where guid=@GUID;

set @GUID=50006;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
update creature_addon set path_id=@GUID where guid=@GUID;

set @GUID=48754;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
update creature_addon set path_id=@GUID where guid=@GUID;

set @GUID=49917;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
update creature_addon set path_id=@GUID where guid=@GUID;

set @GUID=24305;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
update creature_addon set path_id=@GUID where guid=@GUID;

set @GUID=49701;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
update creature_addon set path_id=@GUID where guid=@GUID;


Update creature_template SET mindmg=3, maxdmg=4, minrangedmg=1, maxrangedmg=2 WHERE entry in (1890, 1916, 1917, 1918, 35505, 35916, 49869);

Update creature_template SET mindmg=2, maxdmg=2, minrangedmg=1, maxrangedmg=1 WHERE entry in (
3510, 17169, 17173, 18668, 18669, 18671, 18724, 18799, 1408, 4989, 4993, 5962, 5964, 5970, 5973, 16770, 19247,
22914, 23364, 23727, 23832, 23868, 23869, 1230, 32396, 32798, 32799, 33211, 33224, 34812, 34823, 34819, 34824,
34822, 36704, 51337, 15274, 19405, 21210, 21211, 21403, 21417, 21512, 21807, 22986, 4988, 15328, 19403, 19404,
20170, 22836, 24462, 22823, 22913, 23170, 23171, 23751, 23752, 23753, 25494, 25652, 26468, 26469, 26470, 26855,
26856, 26857, 28468, 29939, 30209, 30211, 30212, 32389, 32394, 32395, 32397, 36702, 41189, 41372, 41373, 41375,
42046, 42152, 42169, 42452, 45656, 45752, 46185, 46208, 36514, 36714, 38111, 38412, 38933, 46509, 47682, 48833,
49338, 1501, 2110, 6827, 7395, 13321, 23231, 28567, 34850, 34865, 34936, 35903, 36177, 36591, 36608, 37748, 37804,
37872, 37895, 37896, 37897, 38069, 38195, 38450, 38802, 38813, 38816, 38979, 38985, 39169, 39383, 40073, 40074,
40075, 40076, 40077, 40722, 42371, 44578, 44579, 44580, 44588, 44590, 44591, 45439, 45492, 45561, 45564, 47667,
47402, 47525, 48323, 48446, 48519, 48532, 48537, 48630, 48672, 48800, 49131, 49132, 49150, 49486, 49528, 49535,
49536, 49772, 49773, 49774, 49871, 51335, 51462, 56063, 56065, 46008, 56066, 56074, 56075, 56076, 53216, 9958,
722, 36683, 52533, 54352, 45910, 46588, 45882, 45883, 35231, 35840, 39199, 44086, 52582, 52866, 46734, 7560);

Update creature_template SET mindmg=2, maxdmg=2, minrangedmg=1, maxrangedmg=1 WHERE entry in (49339, 34884, 48806, 48719, 45303);
Update creature_template SET mindmg=2, maxdmg=2, minrangedmg=1, maxrangedmg=1 WHERE entry in (35185, 35201, 35660, 36721, 48305);

Update creature_template SET mindmg=3, maxdmg=4, minrangedmg=1, maxrangedmg=2 WHERE entry in (
50039, 34876, 34878, 35504, 48304, 1504, 1508, 1512, 34835, 34877, 35120, 35126, 35128, 35130, 35207, 35209, 
35210, 35613, 37056, 37057, 37708, 37709, 37710, 51411, 35081, 35123, 35378, 35753, 38844, 35509);

Update creature_template SET mindmg=4, maxdmg=5, minrangedmg=2, maxrangedmg=3 WHERE entry in (16916, 35631, 951, 1513, 18722, 35124, 37114);
Update creature_template SET mindmg=3, maxdmg=5, minrangedmg=1, maxrangedmg=3 WHERE entry in (16483, 42937, 1505, 35200, 35234, 35294, 35609, 35623);

Update creature_template SET mindmg=5, maxdmg=7, minrangedmg=3, maxrangedmg=4 WHERE entry in (
 35873, 49424, 651, 51681, 36470, 36471, 42938, 47680, 1919, 34668, 34872, 34874, 35053, 35054, 35304, 35650,
 35769, 36404, 36406, 36425, 36427, 36430, 36466, 36467, 36468, 36469, 36600, 36942, 37500, 37683, 37761,
 37762, 38381, 38387, 38432, 38511, 38738, 38928, 49218, 49422, 49428, 35112, 35115, 35551, 35618, 35839,
 35869, 35870, 35871, 35874, 35906, 44455, 44459, 44461, 44464, 44468, 44469, 50371, 37112, 9935, 808);

Update creature_template SET mindmg=4, maxdmg=7, minrangedmg=2, maxrangedmg=4 WHERE entry in (2954, 17073, 17641, 35237, 36057, 42290, 42339, 42548, 49423, 51277);



