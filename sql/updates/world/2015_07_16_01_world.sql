
-- http://de.wowhead.com/npc=53488/summon-enabler-stalker
-- update creature_template set AIName="", ScriptName="npc_summon_enabler_stalker" where entry=53488;

update creature_template set VehicleId=1943, AIName="", ScriptName="npc_dream_warden_57475" where entry=57475;
update creature_template set VehicleId=1947, AIName="", ScriptName="npc_halo_jump_parachute_57630" where entry=57630;
delete from creature where id=57475;
delete from creature_addon where guid in (268139, 268213, 268214, 268215, 268217, 268219, 268221, 268222);
delete from waypoint_data where id in (268139, 268213, 268214, 268215, 268217, 268219, 268221, 268222);

update creature_template set AIName="", ScriptName="npc_valeera_tele_57289" where entry=57289;

delete from waypoint_data where id in (5747501);
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, move_flag) VALUES 
(5747501, 0, -1793.884, -2372.939,  49.779, 1),  
(5747501, 1, -1795.748, -2294.256,  67.053, 1),
(5747501, 2, -1792.221, -2165.998,  98.733, 1),
(5747501, 3, -1758.800, -1919.160, 130.406, 1),
(5747501, 4, -1750.800, -1837.160, 163.406, 1);

delete from waypoint_data where id in (5763001);
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, move_flag) VALUES 
(5763001, 0, -1766.627, -1921.398,  -72.3089, 1),
(5763001, 1, -1755.748, -1983.333, -152.7908, 1),
(5763001, 2, -1745.561, -1846.071, -221.3837, 1); 

update creature_addon set path_id=0 where guid=268650;

delete from creature where guid=268059;

  
  