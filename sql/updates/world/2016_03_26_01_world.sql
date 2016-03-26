
-- fix issue #116 part 1
delete from creature where id in (38983, 38981, 38980);

update npc_text set BroadcastTextID0=39159 where ID=15529;

update creature_template set AIName="", ScriptName="npc_shadow_priestess_malia_39117" where entry=39117;

update creature set spawntimesecs=120 where guid=37022 and id=39117;

update gossip_menu_option set OptionBroadcastTextID=4759, option_id=1, npc_option_npcflag=1 where menu_id=11156 and id=0;

SET @PATHID=3702201;
DELETE FROM waypoint_data WHERE id=@PATHID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay) values
(@PATHID, 0, 2243.597, 230.6953, 34.50811, 3.15729, 500),
(@PATHID, 1, 2240.932, 233.1553, 34.50811, 3.695287, 0),
(@PATHID, 2, 2240.453, 232.9411, 34.50811, 3.546062, 0),
(@PATHID, 3, 2234.86, 230.4542, 38.20267, 3.883783, 0),
(@PATHID, 4, 2234.197, 228.956, 38.2302, 4.296116, 0),
(@PATHID, 5, 2235.268, 226.9928, 38.22498, 5.309278, 0),
(@PATHID, 6, 2236.673, 226.1655, 38.20193, 0.490857, 0),
(@PATHID, 7, 2242.334, 228.6832, 41.81219, 0.321996, 0),
(@PATHID, 8, 2244.058, 229.1666, 41.81219, 0.243457, 0),
(@PATHID, 9, 2244.058, 229.1666, 41.81219, 0.243457, 500);

SET @PATHID=3702202;
DELETE FROM waypoint_data WHERE id=@PATHID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay) values
(@PATHID, 0, 2244.058, 229.1666, 41.81219, 0.243457, 500),
(@PATHID, 1, 2244.058, 229.1666, 41.81219, 0.243457, 0),
(@PATHID, 2, 2242.334, 228.6832, 41.81219, 0.321996, 0),
(@PATHID, 3, 2236.673, 226.1655, 38.20193, 0.490857, 0),
(@PATHID, 4, 2235.268, 226.9928, 38.22498, 5.309278, 0),
(@PATHID, 5, 2234.197, 228.956, 38.2302, 4.296116, 0),
(@PATHID, 6, 2234.86, 230.4542, 38.20267, 3.883783, 0),
(@PATHID, 7, 2240.453, 232.9411, 34.50811, 3.546062, 0),
(@PATHID, 8, 2240.932, 233.1553, 34.50811, 3.695287, 0),
(@PATHID, 9, 2242.28, 230.6375, 34.50811, 0.3839, 0),
(@PATHID, 10, 2242.28, 230.6375, 34.50811, 0.3839, 500);




