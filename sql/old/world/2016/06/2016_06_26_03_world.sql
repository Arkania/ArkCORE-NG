

delete from waypoint_scripts where id between 52 and 65;

delete from waypoint_data where id in(584490, 584500, 584510); 

UPDATE creature_addon SET path_id=0 WHERE guid in (180055, 180056, 180057);

UPDATE creature SET MovementType=0 WHERE guid in (180055, 180056, 180057);

UPDATE creature_template SET AIName="", ScriptName="npc_honor_hold_archer_16896" WHERE entry=16896;

delete from smart_scripts where entryorguid in (16896, -180055, -180056, -180057);

update game_event set start_time="1970-01-01 01:00:01" where start_time="0000-00-00 00:00:00";
update game_event set end_time="1970-01-01 01:00:01" where end_time="0000-00-00 00:00:00";

