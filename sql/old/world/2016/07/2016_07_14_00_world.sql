
-- missing waypoints..
UPDATE creature_addon SET path_id=0 WHERE guid in (113121,113126,113149);

UPDATE creature SET MovementType=0 WHERE guid in (113121,113126,113149);

UPDATE creature_addon SET path_id=0 WHERE guid in (112802,112807,112809);

UPDATE creature SET MovementType=0 WHERE guid in (112802,112807,112809);

UPDATE creature_addon SET path_id=0 WHERE guid in (113278);

UPDATE creature SET MovementType=0 WHERE guid in (113278);

UPDATE creature_template SET minlevel=88, maxlevel=88, exp=3, faction=14, rangeattacktime=2000, unit_flags=33554432, unit_flags2=34816, ScriptName="npc_sulfuras_hand_of_ragnaros_53420" WHERE entry=53420;





