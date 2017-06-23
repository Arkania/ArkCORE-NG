
-- remove passengers with global positions of ship kraven
delete from creature where map=0 and guid in (11346);

-- sea gull aiAnimKit 835 is for sitting on bridge, not for flying.. 
update creature_addon set bytes1=50331648, aiAnimKit=0 where guid in (select guid from creature where id=44880);

-- move double of ship to vash'ir to phase 172..  
update transports set phaseId=172 where entry in (203626, 200100);

-- cleanup old helper phase
delete from phase_definitions where zoneId=14 and entry=0;

delete from phase_area where areaId=14 and entry=0;

delete from phase_definitions where zoneId=1519 and entry=0;

delete from phase_area where areaId=1519 and entry=0;

-- start fix quest "Call of Duty"
UPDATE creature_template SET ScriptName="npc_recruiter_burns_36799" WHERE entry=36799;

