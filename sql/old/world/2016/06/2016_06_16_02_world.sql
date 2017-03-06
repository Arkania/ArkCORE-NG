
-- fix bootybay not burning allways..
update creature set phaseMask=4 where id in (43663, 43664, 43665, 43700, 43716, 43717, 43726, 43760, 43790, 44406);

update creature set phaseMask=5 where id in (21045, 17429);

-- this npc are only visible on fishing contest
delete from game_event_creature where eventEntry=15 and guid in (244, 45899, 45900, 56250, 56251);
insert game_event_creature values
(15, 244),
(15, 45900),
(15, 45899),
(15, 56250),
(15, 56251);

UPDATE creature_template SET minlevel=34, maxlevel=35 WHERE entry in (43663, 43664, 43665, 43716, 44406);

UPDATE creature_template SET minlevel=35, maxlevel=35 WHERE entry=43790;

update gameobject set phaseMask=4 where id between 204566 and 204572;

