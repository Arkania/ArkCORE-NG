
-- fix issue #114

delete from creature where id in (24924, 24926, 24927, 24929, 24930, 24931, 25080, 25081) and map <>589;
delete from creature where id in (25100, 25101, 25102, 25103, 25104, 25105, 25106, 25107) and map <>590;
delete from creature where id in (25070, 25071, 25072, 25074, 25076, 25077, 25079, 25083) and map <>591;
delete from creature where id in (25078, 25082, 25089, 25093, 25094, 25095, 25097, 25098, 25111) and map <>593;
delete from creature where id in (31704, 31705, 31706, 31708, 31715, 31716) and map <>610;
delete from creature where id in (31720, 31723, 31724, 31725, 31726, 31727) and map <>613;
delete from creature where id in (24910, 24911, 24992, 25026) and map <>594;

delete from creature where guid in (36899, 36924, 36972, 37181, 37346, 50200, 50261, 89818, 92652, 115953) and id =25075;
delete from creature where guid in (11340, 11341, 137672, 137673) and id =24935;
delete from creature where guid in (37049, 37403, 50610, 205522, 205523, 205524, 205525, 205526, 205527, 230353, 230481) and id =25171;

DELETE FROM creature_addon WHERE guid=115953;
DELETE FROM creature_addon WHERE guid=50200;
DELETE FROM creature_addon WHERE guid=50261;
DELETE FROM creature_addon WHERE guid=50272;
DELETE FROM creature_addon WHERE guid=50416;
DELETE FROM creature_addon WHERE guid=50486;
DELETE FROM creature_addon WHERE guid=50610;
DELETE FROM creature_addon WHERE guid=50681;
DELETE FROM creature_addon WHERE guid=50870;
DELETE FROM creature_addon WHERE guid=36508;
DELETE FROM creature_addon WHERE guid=36568;
DELETE FROM creature_addon WHERE guid=36725;
DELETE FROM creature_addon WHERE guid=36777;
DELETE FROM creature_addon WHERE guid=36789;
DELETE FROM creature_addon WHERE guid=36853;
DELETE FROM creature_addon WHERE guid=36899;
DELETE FROM creature_addon WHERE guid=36924;
DELETE FROM creature_addon WHERE guid=36972;
DELETE FROM creature_addon WHERE guid=36985;
DELETE FROM creature_addon WHERE guid=37049;
DELETE FROM creature_addon WHERE guid=37087;
DELETE FROM creature_addon WHERE guid=37181;
DELETE FROM creature_addon WHERE guid=37346;
DELETE FROM creature_addon WHERE guid=37403;
DELETE FROM creature_addon WHERE guid=92652;
DELETE FROM creature_addon WHERE guid=89818;





