

UPDATE quest_template SET QuestGiverPortrait=16480 WHERE Id=28805;

UPDATE quest_template SET Flags=134742080 WHERE Id=25551;

UPDATE quest_template SET RequiredRaces=2098253 WHERE Id=27398;

UPDATE quest_template SET RequiredRaces=946 WHERE Id=27399;

UPDATE quest_template SET Flags=65672 WHERE Id=26251;

UPDATE quest_template SET Flags=65672, PrevQuestId=26247 WHERE Id=26248;

UPDATE quest_template SET PrevQuestId=26245 WHERE Id=26247;

UPDATE quest_template SET PrevQuestId=26247 WHERE Id=26249;

UPDATE quest_template SET PrevQuestId=26247 WHERE Id=26432;

UPDATE quest_template SET NextQuestId=27203, ExclusiveGroup=27443, NextQuestIdChain=27203 WHERE Id=27443;

UPDATE quest_template SET ExclusiveGroup=27443, NextQuestIdChain=27203 WHERE Id=27727;

UPDATE quest_template SET NextQuestId=27203, ExclusiveGroup=27443, NextQuestIdChain=27203 WHERE Id=27398;

UPDATE quest_template SET NextQuestId=27203, ExclusiveGroup=27442, NextQuestIdChain=27203 WHERE Id=27442;

UPDATE quest_template SET NextQuestId=27203, ExclusiveGroup=27442, NextQuestIdChain=27203 WHERE Id=27722;

UPDATE quest_template SET NextQuestId=27203, ExclusiveGroup=27442, NextQuestIdChain=27203 WHERE Id=27399;

UPDATE creature SET spawndist=0, MovementType=0 WHERE id=43090;

UPDATE creature SET spawndist=0, MovementType=0 WHERE id=41749;

UPDATE gameobject SET phaseId=170 WHERE guid=163283;

UPDATE gameobject SET phaseId=171 WHERE guid=184257;

delete from creature where guid in (88274,112275);

DELETE FROM creature_addon WHERE guid=112275;

DELETE FROM creature_addon WHERE guid=88274;

update smart_scripts set action_type=85, action_param1=73833 where entryorguid=39368 and source_type=0 and id=0;

UPDATE creature_template SET ScriptName="npc_commander_thorak_41621" WHERE entry=41621;

UPDATE creature SET phaseId=0, phaseGroup=396 WHERE guid=89594;

UPDATE creature_template_addon SET aiAnimKit=835 WHERE entry=44880;

UPDATE creature_addon SET aiAnimKit=835 WHERE guid in (48074, 48081, 48086, 48126, 48135, 48140, 48166, 48169, 48170, 48183, 48354, 48433, 48445, 48495, 48538);
UPDATE creature_addon SET aiAnimKit=835 WHERE guid in (48588, 48627, 48710, 48742, 48780, 48818, 48826, 48858, 48869, 48957, 48981, 49008, 49032, 49042, 49091);
UPDATE creature_addon SET aiAnimKit=835 WHERE guid in (49131, 49148, 49158, 49241, 49257, 49290, 49302, 49356, 49377, 49432, 49439, 49476, 49484, 49509, 49513);
UPDATE creature_addon SET aiAnimKit=835 WHERE guid in (49522, 49525, 49609, 49649, 49699, 49707, 49716, 49734, 49769, 49795, 103177, 103243, 103255, 103573);
UPDATE creature_addon SET aiAnimKit=835 WHERE guid in (103619, 103708, 103740, 103768, 103785, 103818, 104017, 104030, 104084, 104314, 104337, 104374, 104587);
UPDATE creature_addon SET aiAnimKit=835 WHERE guid in (104632, 104636, 104663, 104688, 104769, 104770, 104800, 105037, 105174, 105290, 105330);

delete from phase_definitions where zoneId=374 and entry=0;
insert into phase_definitions values 
(374, 0, 171, 0, 0, 0, 1, "Quest Horde Call of Duty");

delete from phase_definitions where zoneId=817 and entry=0;
insert into phase_definitions values 
(817, 0, 171, 0, 0, 0, 1, "Quest Horde Call of Duty");

delete from phase_definitions where zoneId=4411 and entry=0;
insert into phase_definitions values 
(4411, 0, 171, 0, 0, 0, 1, "Quest Alliance Call of Duty");

delete from phase_area where areaId=374 and entry=0;
insert into phase_area values 
(374, 0, 25924, 25924, 74, 11, 1, "Quest Horde Call of Duty");

delete from phase_area where areaId=817 and entry=0;
insert into phase_area values 
(817, 0, 25924, 25924, 74, 11, 1, "Quest Horde Call of Duty");

delete from phase_area where areaId=4411 and entry=0;
insert into phase_area values 
(4411, 0, 14482, 14482, 74, 11, 1, "Quest Alliance Call of Duty");

update transports set phaseId=171 where guid in (40,42);

-- horde ship to vashir.. passenger position is only a test..
UPDATE creature SET map=738 WHERE guid in (117108, 117109, 117098);

UPDATE creature SET map=738, position_x=6, position_y=4, position_z=5, orientation=0, spawndist=0, MovementType=0 WHERE guid=117108;

UPDATE creature SET map=738, position_x=5, position_y=5, position_z=5, orientation=0, spawndist=0, MovementType=0 WHERE guid=117109;

UPDATE creature SET map=738, position_x=4, position_y=6, position_z=5, orientation=0, spawndist=0, MovementType=0 WHERE guid=117098;



