
update creature_template set faction=35, gossip_menu_id=0, npcflag=1 where entry=14354;

delete from creature_text where entry=11491;
insert into creature_text values
(11491, 0, 0, "As you wish...", 12, 0, 100, 0, 0, 0, "", 9099),
(11491, 1, 0, "My strength wanes, mortal. I have done as promised, the way is clear. I now return to whence I came.", 12, 0, 100, 0, 0, 0, "", 9100),
(11491, 2, 0, "At last... Freed from his cursed grasp!", 14, 0, 100, 0, 0, 0, "", 9104);

SET @GUID=154088;
SET @PATHID=1540881;
UPDATE creature SET spawndist=0, MovementType = 0 WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@PATHID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, move_flag, delay) values
(@PATHID, 0, 76.00957, -200.1845, -4.120036, 3.263392, 1, 1000),
(@PATHID, 1, 32.74767, -207.5865, -4.060904, 3.298735, 1, 0),
(@PATHID, 2, -135.3748, -195.4654, -4.149238, 3.059189, 1, 0),
(@PATHID, 3, -157.3651, -205.8149, -4.152692, 3.581479, 1, 0),
(@PATHID, 4, -161.5664, -219.6678, -4.150691, 4.417926, 1, 0),
(@PATHID, 5, -147.4321, -262.2087, -4.145966, 5.006973, 1, 0),
(@PATHID, 6, -168.0087, -273.1946, -4.129812, 3.738555, 1, 0),
(@PATHID, 7, -167.1245, -272.9263, -4.142066, 0.294583, 1, 0);

SET @PATHID=1540882;
DELETE FROM waypoint_data WHERE id=@PATHID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, move_flag, delay) values
(@PATHID, 0, -159.7915, -347.293, -4.151082, 4.810625, 1, 0),
(@PATHID, 1, -55.22495, -350.0811, -4.071543, 6.247902, 1, 0),
(@PATHID, 2, -24.80385, -354.8974, -4.112474, 6.126166, 1, 0),
(@PATHID, 3, 22.34295, -353.5505, -4.105566, 0.003986, 1, 0),
(@PATHID, 4, 45.36258, -349.6247, -4.072824, 0.16892, 1, 0),
(@PATHID, 5, 103.2193, -352.5774, -4.095215, 6.232194, 1, 0),
(@PATHID, 6, 114.1023, -323.2684, -4.120694, 1.18601, 1, 0),
(@PATHID, 7, 113.6734, -324.1184, -4.118527, 4.245133, 1, 0);

SET @PATHID=1540883;
DELETE FROM waypoint_data WHERE id=@PATHID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, move_flag, delay) values
(@PATHID, 0, 125.0968, -337.7066, -4.149131, 5.411445, 1, 1000),
(@PATHID, 1, 123.9407, -357.3286, -4.151971, 4.653538, 1, 0),
(@PATHID, 2, 112.0336, -372.9324, -4.070819, 4.060563, 1, 0),
(@PATHID, 3, 111.4962, -534.2385, -11.07917, 4.696738, 1, 0),
(@PATHID, 4, 98.6263, -545.0341, -11.07784, 3.824948, 1, 0),
(@PATHID, 5, 71.53242, -544.3199, -15.24411, 3.125944, 1, 0),
(@PATHID, 6, 50.86924, -560.3499, -19.41172, 3.801386, 1, 0),
(@PATHID, 7, 48.14518, -640.5923, -25.13704, 4.657467, 1, 0),
(@PATHID, 8, 47.84433, -638.7406, -25.13396, 1.731859, 1, 0);

SET @PATHID=1540884;
DELETE FROM waypoint_data WHERE id=@PATHID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, move_flag, delay) values
(@PATHID, 0, 45.2443, -680.2007, -25.16108, 4.633904, 1, 0),
(@PATHID, 1, 5.848804, -710.1317, -25.16108, 3.789603, 1, 0),
(@PATHID, 2, 6.552897, -709.4909, -25.16108, 0.73833, 1, 0);










