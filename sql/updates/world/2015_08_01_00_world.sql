

update creature_addon set path_id=237642 where guid=237642;
update creature set MovementType=2 where guid=237642;

UPDATE quest_template SET Method=2, PrevQuestId=12657, Flags=65664 WHERE Id=12849;
UPDATE quest_template SET PrevQuestId=12757, NextQuestId=12779 WHERE Id=12778;
UPDATE quest_template SET Flags=128 WHERE Id=12779;

update creature set phaseMask=4 where guid in (236864, 236865, 236866, 236867, 236868);
update creature set phaseMask=68 where guid in (236897, 236895, 236896);

delete from quest_poi_points where questId in (12593, 12619, 12842, 12848, 12593, 12619, 12842, 12848);

delete from quest_poi where objIndex=-1 and questId in (12593, 12619, 12842, 12848, 12593, 12619, 12842, 12848);

update creature set modelid=23980 where guid=236953;
update creature set modelid=23980 where guid=237079;
update creature set modelid=23980 where guid=237083;
update creature set modelid=23980 where guid=237087;

update creature_addon set auras=51939 where guid in (236953, 237079, 237083, 237087);

UPDATE quest_template SET PrevQuestId=12670, Flags=136 WHERE Id=12680;

UPDATE locales_quest SET EndText_loc3="", QuestGiverTextWindow_loc3="Geht und bringt mir ein's", QuestGiverTargetName_loc3="Pferde von Havenau" WHERE Id=12680;

UPDATE quest_template SET PrevQuestId=12733 WHERE Id=12697;

UPDATE creature_template SET faction=2100, npcflag=16777216 WHERE entry in (29488, 29501);

update creature_template set InhabitType=3, AIName="", ScriptName="npc_dk_initiate_28406" where entry=28406;

update creature set MovementType=2 where guid=34244;
insert ignore into creature_addon (guid) value (34244);
update creature_addon set path_id=34244 where guid=34244;
delete from waypoint_data where id=34244;
insert into waypoint_data values
(34244, 1, -9002.17, -2134.64, 143.653, 0, 0, 0, 0, 100, 0),
(34244, 2, -9002.14, -2135.64, 143.653, 0, 0, 0, 0, 100, 0),
(34244, 3, -9002.05, -2138.25, 143.453, 0, 0, 0, 0, 100, 0),
(34244, 4, -9001.91, -2141.24, 142.828, 0, 0, 0, 0, 100, 0),
(34244, 5, -9001.77, -2144.24, 142.203, 0, 0, 0, 0, 100, 0),
(34244, 6, -9001.67, -2146.23, 141.578, 0, 0, 0, 0, 100, 0),
(34244, 7, -9001.58, -2148.23, 140.953, 0, 0, 0, 0, 100, 0),
(34244, 8, -9001.49, -2150.23, 139.453, 0, 0, 0, 0, 100, 0),
(34244, 9, -9001.44, -2151.23, 138.078, 0, 0, 0, 0, 100, 0),
(34244, 10, -9001.39, -2152.22, 136.953, 0, 0, 0, 0, 100, 0),
(34244, 11, -9001.3, -2154.22, 135.453, 0, 0, 0, 0, 100, 0),
(34244, 12, -9001.11, -2158.21, 134.078, 0, 0, 0, 0, 100, 0),
(34244, 13, -9001.05, -2160, 133.328, 0, 0, 0, 0, 100, 0),
(34244, 14, -9001.05, -2160, 133.328, 0, 0, 0, 0, 100, 0);

update creature_addon set path_id=34539 where guid=34539;

update creature set spawndist=3, MovementType=1 where guid=37194;

update creature set spawndist=0, MovementType=0 where guid=48342;

delete from creature where id in (48340, 48341, 48342, 48343);  -- in deadmines, goblin bunny's drink glasses.. spawned by script..

delete from pool_creature where guid=146050;

delete from vehicle_template_accessory where entry=35999; 

delete from spell_area where spell=42316 and racemask=1101;

UPDATE quest_template SET SpecialFlags=2 WHERE Id=27704;

UPDATE quest_template SET SpecialFlags=2 WHERE Id=13607;

UPDATE quest_template SET SpecialFlags=2 WHERE Id=13816;

delete from game_graveyard_zone where id=589;

delete from game_graveyard_zone where id=1374;

delete from game_graveyard_zone where id=109;
insert into game_graveyard_zone values
(109, 214, 0),
(109, 5339, 0);

delete from spell_target_position where id in (59064, 94569, 94568, 94566, 59065, 93269, 44876, 11011, 35376, 35727, 55554, 88775, 84505, 84506, 84463, 88345, 88346, 90244, 90245, 26373);
























