
-- fix issue #136 
update creature set position_x=-2315.117676, position_y=2295.383789, position_z=0.482437, orientation=3.697361, spawntimesecs=120 where id=36488 and guid=16490;
update creature set position_x=-2316.558350, position_y=2297.604736, position_z=0.396649, orientation=4.141110, spawntimesecs=120 where id=36488 and guid=16491;
update creature set position_x=-2317.230957, position_y=2290.502686, position_z=0.245671, orientation=2.016612, spawntimesecs=120 where id=36488 and guid=16492;
update creature set position_x=-2315.834717, position_y=2291.187256, position_z=0.328474, orientation=2.695978, spawntimesecs=120 where id=36488 and guid=16493;

delete from creature where id=36488 and guid between 24995 and 25002;
insert into creature values 
(24995, 36488, 654, 1, 16384, 21956, 1, -2308.97, 2276.75, 0.326157, -0.949657, 120, 3, 0, 120, 0, 1, 0, 0, 0),
(24996, 36488, 654, 1, 16384, 21958, 1, -2308.91, 2285.9, 0.326157, 0.0242474, 120, 3, 0, 120, 0, 1, 0, 0, 0),
(24997, 36488, 654, 1, 16384, 21957, 1, -2308.17, 2288.2, 0.299863, -0.64702, 120, 3, 0, 120, 0, 1, 0, 0, 0),
(24998, 36488, 654, 1, 16384, 21958, 1, -2306.76, 2271.39, 0.212215, -0.937307, 120, 3, 0, 120, 0, 1, 0, 0, 0),
(24999, 36488, 654, 1, 16384, 21957, 1, -2306.66, 2289.37, 0.23383, -1.17374, 120, 3, 0, 120, 0, 1, 0, 0, 0),
(25000, 36488, 654, 1, 16384, 21958, 1, -2317.77, 2320.37, 2.61017, 4.86947, 120, 3, 0, 120, 0, 1, 0, 0, 0),
(25001, 36488, 654, 1, 16384, 21956, 1, -2336.22, 2260.19, 0.412189, 1.309, 120, 3, 0, 120, 0, 1, 0, 0, 0),
(25002, 36488, 654, 1, 16384, 21957, 1, -2350.44, 2277.98, 0.408028, 0.593412, 120, 3, 0, 120, 0, 1, 0, 0, 0);

update creature_template set AIName="", ScriptName="npc_forsaken_castaway_36488" where entry=36488;

delete from quest_poi where questId=14405 and id=0;

update creature set map=654, phaseMask=28672 where id=36457 and guid=253469;

SET @GUID=253473;
UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;
INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;
DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -2147.617, 2217.418, 11.41504, 2.373935, 5000, 0),
(@GUID, 1, -2130.974, 2205.576, 14.9871, 5.664752, 0, 0),
(@GUID, 2, -2122.618, 2196.714, 17.90615, 5.468403, 0, 0),
(@GUID, 3, -2128.973, 2178.511, 24.97734, 4.376701, 0, 0),
(@GUID, 4, -2145.235, 2177.454, 22.05466, 3.194677, 0, 0),
(@GUID, 5, -2169.223, 2194.428, 18.93829, 2.585994, 0, 0),
(@GUID, 6, -2190.761, 2202.751, 16.93548, 2.62919, 0, 0),
(@GUID, 7, -2198.372, 2215.246, 15.81889, 2.110827, 0, 0),
(@GUID, 8, -2204.078, 2225.077, 11.0232, 2.091192, 0, 0),
(@GUID, 9, -2204.001, 2245.076, 8.658976, 1.635661, 0, 0),
(@GUID, 10, -2177.324, 2247.273, 8.485445, 0.0845, 0, 0),
(@GUID, 11, -2162.256, 2230.877, 9.440261, 5.503749, 0, 0),
(@GUID, 12, -2162.256, 2230.877, 9.440261, 5.503749, 0, 0),
(@GUID, 13, -2177.324, 2247.273, 8.485445, 0.0845, 0, 0),
(@GUID, 14, -2204.001, 2245.076, 8.658976, 1.635661, 0, 0),
(@GUID, 15, -2204.078, 2225.077, 11.0232, 2.091192, 0, 0),
(@GUID, 16, -2198.372, 2215.246, 15.81889, 2.110827, 0, 0),
(@GUID, 17, -2190.761, 2202.751, 16.93548, 2.62919, 0, 0),
(@GUID, 18, -2169.223, 2194.428, 18.93829, 2.585994, 0, 0),
(@GUID, 19, -2145.235, 2177.454, 22.05466, 3.194677, 0, 0),
(@GUID, 20, -2128.973, 2178.511, 24.97734, 4.376701, 0, 0),
(@GUID, 21, -2122.618, 2196.714, 17.90615, 5.468403, 0, 0),
(@GUID, 22, -2130.974, 2205.576, 14.9871, 5.664752, 0, 0),
(@GUID, 23, -2147.617, 2217.418, 11.41504, 2.373935, 5000, 0);

UPDATE creature_template SET npcflag=16777216, faction=35, AIName="", ScriptName="npc_mountain_horse_36540" WHERE entry=36540;

update creature set spawndist=5, MovementType=1 where id=36540;

UPDATE creature_template SET gossip_menu_id=0, npcflag=0, faction=35, unit_flags=8, AIName="", ScriptName="npc_mountain_horse_36555" WHERE entry=36555;

delete from npc_spellclick_spells where npc_entry=36540 and spell_id=46598;  
delete from npc_spellclick_spells where npc_entry=36540 and spell_id=68917;
delete from npc_spellclick_spells where npc_entry=36540 and spell_id=94654;
insert into npc_spellclick_spells values 
(36540, 94654, 1, 0);

delete from gossip_menu where entry=36555;

delete from gossip_menu_option where menu_id=36555;

delete from creature where id=36555 and map=655;

UPDATE quest_template SET PrevQuestId=14401, NextQuestId=14465, ExclusiveGroup=14402 WHERE Id=14402;

UPDATE quest_template SET PrevQuestId=14404, NextQuestId=14465, ExclusiveGroup=14402 WHERE Id=14405;

UPDATE quest_template SET PrevQuestId=14416, NextQuestId=14465, ExclusiveGroup=14402 WHERE Id=14463;

UPDATE quest_template SET PrevQuestId=14403 WHERE Id=14412;


