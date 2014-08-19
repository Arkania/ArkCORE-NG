

-- showfight worg <> infantry npc's are not pacified
UPDATE creature_template SET unit_flags=0 WHERE entry in (49871,49869);

-- npc's are not pacified
update creature set unit_flags=0 where id in (49871,49869);

-- set worg in correct position
update creature set position_x=-8835.82,position_y=-141.949,position_z=81.0521,orientation=5.5023 where guid=49947;
UPDATE creature_template SET dynamicflags=0 WHERE entry=49871;

-- shortly the waittime for new healing npc.
update creature set spawntimesecs=120 where id=50047;

-- the model id 25204 is invisible..
UPDATE creature_template SET modelid2=0 WHERE entry=50378;

-- assasin are sneaking
update creature_template_addon set auras="93046" where entry =50039;

-- random move
update creature set SpawnDist=10, MovementType=1 where id=113;


