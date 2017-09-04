
-- zone 4411 stormwind harbor sniff 15595


delete from creature where guid in (1171, 48700, 1189, 1190, 1172, 27023, 1173);

delete from creature_addon where guid in (1171, 48700, 1189, 1190, 1172, 27023, 1173);

SET @CGUID := 9285;

DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+58;
INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `PhaseId`, `PhaseGroup`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `VerifiedBuild`) VALUES
(@CGUID+0, 29152, 0, 1519, 4411, 1, '0', 0, 0, 0, -8259.395, 1209.329, 5.424629, 5.864306, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Dock Worker (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+1, 29152, 0, 1519, 4411, 1, '0', 0, 0, 0, -8252.27, 1209.72, 5.424629, 3.505863, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Dock Worker (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+2, 29152, 0, 1519, 4411, 1, '0', 0, 0, 0, -8248.79, 1234.73, 5.230244, 5.879896, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Dock Worker (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+3, 29152, 0, 1519, 4411, 1, '0', 0, 0, 0, -8297.565, 1247.6, 5.230216, 4.722922, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Dock Worker (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+4, 29152, 0, 1519, 4411, 1, '0', 0, 0, 0, -8351.37, 1197.54, 5.699383, 5.899213, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Dock Worker (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+5, 29152, 0, 1519, 4411, 1, '0', 0, 0, 0, -8315.31, 1213, 5.284714, 1.004872, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Dock Worker (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+6, 29152, 0, 1519, 4411, 1, '0', 0, 0, 0, -8297.859, 1264.622, 5.229434, 4.686074, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Dock Worker (Area: Stormwind Harbor - Difficulty: 0)

(@CGUID+7, 29019, 0, 1519, 4411, 1, '0', 0, 0, 0, -8234.398, 1225.452, 5.230248, 0.1119419, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Dockhand (Area: Stormwind Harbor - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+8, 29019, 0, 1519, 4411, 1, '0', 0, 0, 0, -8363.471, 1245.545, 5.230237, 2.076942, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Dockhand (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+9, 29019, 0, 1519, 4411, 1, '0', 0, 0, 0, -8297.414, 1289.822, 5.218487, 4.710515, 120, 0, 0, 0, 0, 2, 0, 0, 0, 15595), -- Dockhand (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+10, 29019, 0, 1519, 4411, 1, '0', 0, 0, 0, -8297.394, 1300.646, 5.214631, 4.710515, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Dockhand (Area: Stormwind Harbor - Difficulty: 0)

(@CGUID+11, 29712, 0, 1519, 4411, 1, '0', 0, 0, 0, -8303.487, 1249.749, 5.31355, 4.799655, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+12, 29712, 0, 1519, 4411, 1, '0', 0, 0, 0, -8356.154, 1195.381, 5.736004, 1.692969, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+13, 29712, 0, 1519, 4411, 1, '0', 0, 0, 0, -8210.998, 1196.164, 5.71174, 1.308997, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+14, 29712, 0, 1519, 4411, 1, '0', 0, 0, 0, -8304.437, 1244.562, 5.260271, 6.205593, 120, 10, 0, 0, 0, 1, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+15, 29712, 0, 1519, 4411, 1, '0', 0, 0, 0, -8365.547, 1195.148, 5.755658, 1.466077, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+16, 29712, 0, 1519, 4411, 1, '0', 0, 0, 0, -8313.542, 1215.483, 5.274734, 6.281756, 120, 10, 0, 0, 0, 1, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+17, 29712, 0, 1519, 4411, 1, '0', 0, 0, 0, -8329.771, 1258.438, 5.245782, 1.919862, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+18, 29712, 0, 1519, 4411, 1, '0', 0, 0, 0, -8277.972, 1285.66, 5.31355, 3.159046, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+19, 29712, 0, 1519, 4411, 1, '0', 0, 0, 0, -8277.683, 1250.19, 5.31355, 4.485496, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+20, 29712, 0, 1519, 4411, 1, '0', 0, 0, 0, -8331.219, 1263.785, 5.242924, 2.076942, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+21, 29712, 0, 1519, 4411, 1, '0', 0, 0, 0, -8302.756, 1285.354, 5.31355, 0, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+22, 29712, 0, 1519, 4411, 1, '0', 0, 0, 0, -8369.479, 1249.177, 5.31355, 4.642576, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+23, 29712, 0, 1519, 4411, 1, '0', 0, 0, 0, -8343.224, 1258.238, 5.260246, 0.9250245, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+24, 29712, 0, 1519, 4411, 1, '0', 0, 0, 0, -8201.576, 1196.407, 5.699021, 1.815142, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+25, 29712, 0, 1519, 4411, 1, '0', 0, 0, 0, -8341.011, 1264.045, 5.244536, 1.134464, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+26, 29712, 0, 1519, 4411, 1, '0', 0, 0, 0, -8277.614, 1345.504, 5.31355, 3.141593, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+27, 29712, 0, 1519, 4411, 1, '0', 0, 0, 0, -8369.44, 1292.125, 5.313552, 3.124139, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+28, 29712, 0, 1519, 4411, 1, '0', 0, 0, 0, -8302.559, 1345.363, 5.313552, 0, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)

(@CGUID+29, 44880, 0, 1519, 4411, 1, '0', 0, 0, 0, -8215.694, 1188.043, 36.9573, 2.722714, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Sea Gull (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+30, 44880, 0, 1519, 4411, 1, '0', 0, 0, 0, -8254.514, 1205.137, 24.25965, 0.9250245, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Sea Gull (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+31, 44880, 0, 1519, 4411, 1, '0', 0, 0, 0, -8305.802, 1253.222, 25.20196, 4.34587, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Sea Gull (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+32, 44880, 0, 1519, 4411, 1, '0', 0, 0, 0, -8306.611, 1252.451, 25.20889, 5.72468, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Sea Gull (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+33, 44880, 0, 1519, 4411, 1, '0', 0, 0, 0, -8197.203, 1180.101, 40.04347, 0.9773844, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Sea Gull (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+34, 44880, 0, 1519, 4411, 1, '0', 0, 0, 0, -8369.931, 1304.457, 28.78736, 5.218534, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Sea Gull (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+35, 44880, 0, 1519, 4411, 1, '0', 0, 0, 0, -8269.354, 1368.101, 28.65128, 0.9250245, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Sea Gull (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+36, 44880, 0, 1519, 4411, 1, '0', 0, 0, 0, -8270.051, 1366.955, 28.65128, 2.251475, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Sea Gull (Area: Stormwind Harbor - Difficulty: 0)

(@CGUID+37, 52806, 0, 1519, 4411, 1, '0', 0, 0, 0, -8348.283, 1277.637, 2.408104, 5.061455, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Darkspear Warrior (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+38, 52806, 0, 1519, 4411, 1, '0', 0, 0, 0, -8325.646, 1289.924, 2.747515, 4.258604, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Darkspear Warrior (Area: Stormwind Harbor - Difficulty: 0) (Auras: )
(@CGUID+39, 52806, 0, 1519, 4411, 1, '0', 0, 0, 0, -8334.92, 1282.852, 0.2207286, 4.712389, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Darkspear Warrior (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+40, 52806, 0, 1519, 4411, 1, '0', 0, 0, 0, -8339.582, 1281.401, 1.080874, 4.921828, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Darkspear Warrior (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+41, 52806, 0, 1519, 4411, 1, '0', 0, 0, 0, -8326.886, 1283.578, 1.63263, 4.502949, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Darkspear Warrior (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+42, 52806, 0, 1519, 4411, 1, '0', 0, 0, 0, -8348.257, 1284.892, 0.09878134, 4.834562, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Darkspear Warrior (Area: Stormwind Harbor - Difficulty: 0)

(@CGUID+43, 15214, 0, 1519, 4411, 1, '0', 0, 0, 0, -8304.429, 1220.38, 5.695755, 1.692969, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Invisible Stalker (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+44, 15214, 0, 1519, 4411, 1, '0', 0, 0, 0, -8305.864, 1349.389, 6.202475, 4.014257, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Invisible Stalker (Area: Stormwind Harbor - Difficulty: 0)

(@CGUID+45, 36799, 0, 1519, 4411, 1, '0', 0, 0, 0, -8275.52, 1247.45, 5.313563, 3.822271, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Recruiter Burns (Area: Stormwind Harbor - Difficulty: 0)

(@CGUID+46, 51348, 0, 1519, 4411, 1, '0', 0, 0, 0, -8291.615, 1193.698, 54.94772, 5.662135, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Gryphon Rider (Area: Stormwind Harbor - Difficulty: 0)

(@CGUID+47, 42421, 0, 1519, 4411, 1, '0', 0, 0, 0, -8233.66, 1270.84, 4.626964, 1.32645, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Fisherman (Area: Stormwind Harbor - Difficulty: 0)

(@CGUID+48, 49540, 0, 1519, 4411, 1, '0', 0, 0, 0, -8234.424, 1236.344, 5.23024, 4.370958, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Rat (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+49, 49540, 0, 1519, 4411, 1, '0', 0, 0, 0, -8233.092, 1245.275, 5.230233, 0.7610696, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Rat (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+50, 49540, 0, 1519, 4411, 1, '0', 0, 0, 0, -8361.026, 1241.82, 5.230237, 0.6549817, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Rat (Area: Stormwind Harbor - Difficulty: 0)

(@CGUID+51, 52654, 0, 1519, 4411, 1, '0', 0, 0, 0, -8335.134, 1272.465, 3.844817, 4.607669, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Bwemba (Area: Stormwind Harbor - Difficulty: 0)

(@CGUID+52, 53352, 0, 1519, 4411, 1, '0', 0, 0, 0, -8334.997, 1267.028, 4.082645, 1.500983, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Commander Sharp (Area: Stormwind Harbor - Difficulty: 0)

(@CGUID+53, 29144, 0, 1519, 4411, 1, '0', 0, 0, 0, -8462.403, 1135.503, 18.65213, 6.233737, 120, 10, 0, 0, 0, 1, 0, 0, 0, 15595), -- Refurbished Steam Tank (Area: Stormwind Harbor - Difficulty: 0) (possible waypoints or random movement)

(@CGUID+54, 43102, 0, 1519, 4411, 1, '0', 0, 0, 0, -8313.51, 1327.72, -52.85677, 2.042035, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Rock Lobster (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+55, 43102, 0, 1519, 4411, 1, '0', 0, 0, 0, -8354.43, 1331.88, -45.99627, 0.8203048, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Rock Lobster (Area: Stormwind Harbor - Difficulty: 0)

(@CGUID+56, 42979, 0, 1519, 4411, 1, '0', 0, 0, 0, -4559.833, 3884.656, 5.745805, 3.036873, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Kurzel (Area: Stormwind Harbor - Difficulty: 0)

(@CGUID+57, 42980, 0, 1519, 4411, 1, '0', 0, 0, 0, -4560.715, 3890.68, 5.780756, 3.176499, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Tanzar (Area: Stormwind Harbor - Difficulty: 0)

(@CGUID+58, 43175, 0, 1519, 4411, 1, '0', 0, 0, 0, -4559.679, 3879.769, 5.898879, 3.228859, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595); -- Gerok (Area: Stormwind Harbor - Difficulty: 0)


DELETE FROM `creature_addon` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+58;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(@CGUID+0, 0, 0, 0, 257, 0, ''), -- Stormwind Dock Worker
(@CGUID+1, 0, 0, 0, 257, 0, ''), -- Stormwind Dock Worker
(@CGUID+2, 0, 0, 0, 257, 0, ''), -- Stormwind Dock Worker
(@CGUID+3, 0, 0, 0, 257, 0, ''), -- Stormwind Dock Worker
(@CGUID+4, 0, 0, 0, 257, 0, ''), -- Stormwind Dock Worker
(@CGUID+5, 0, 0, 0, 257, 0, ''), -- Stormwind Dock Worker
(@CGUID+6, 0, 0, 0, 257, 0, ''), -- Stormwind Dock Worker

(@CGUID+7, 0, 0, 0, 257, 0, ''), -- Dockhand
(@CGUID+8, 0, 0, 0, 257, 0, ''), -- Dockhand
(@CGUID+9, 0, 0, 0, 257, 0, ''), -- Dockhand
(@CGUID+10, 0, 0, 0, 257, 0, ''), -- Dockhand

(@CGUID+11, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+12, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+13, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+14, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+15, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+16, 0, 2410, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+17, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+18, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+19, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+20, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+21, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+22, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+23, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+24, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+25, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+26, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+27, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+28, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard

(@CGUID+29, 0, 0, 50331648, 1, 0, ''), -- Sea Gull
(@CGUID+30, 0, 0, 50331648, 1, 0, ''), -- Sea Gull
(@CGUID+31, 0, 0, 50331648, 1, 0, ''), -- Sea Gull
(@CGUID+32, 0, 0, 50331648, 1, 0, ''), -- Sea Gull
(@CGUID+33, 0, 0, 50331648, 1, 0, ''), -- Sea Gull
(@CGUID+34, 0, 0, 50331648, 1, 0, ''), -- Sea Gull
(@CGUID+35, 0, 0, 50331648, 1, 0, ''), -- Sea Gull
(@CGUID+36, 0, 0, 50331648, 1, 0, ''), -- Sea Gull

(@CGUID+37, 0, 0, 1, 1, 0, ''), -- Darkspear Warrior
(@CGUID+38, 0, 0, 1, 1, 0, ''), -- Darkspear Warrior
(@CGUID+39, 0, 0, 0, 1, 0, ''), -- Darkspear Warrior
(@CGUID+40, 0, 0, 1, 1, 0, ''), -- Darkspear Warrior
(@CGUID+41, 0, 0, 0, 1, 0, ''), -- Darkspear Warrior
(@CGUID+42, 0, 0, 0, 1, 0, ''), -- Darkspear Warrior

(@CGUID+43, 0, 0, 0, 1, 0, ''), -- Invisible Stalker
(@CGUID+44, 0, 0, 0, 1, 0, ''), -- Invisible Stalker

(@CGUID+45, 0, 0, 0, 1, 0, ''), -- Recruiter Burns
(@CGUID+46, 0, 27913, 50331648, 257, 0, ''), -- Stormwind Gryphon Rider
(@CGUID+47, 0, 0, 0, 1, 0, ''), -- Stormwind Fisherman

(@CGUID+48, 0, 0, 0, 1, 0, ''), -- Stormwind Rat
(@CGUID+49, 0, 0, 0, 1, 0, ''), -- Stormwind Rat
(@CGUID+50, 0, 0, 0, 1, 0, ''), -- Stormwind Rat

(@CGUID+51, 0, 0, 0, 0, 0, ''), -- Bwemba
(@CGUID+52, 0, 0, 0, 257, 0, ''), -- Commander Sharp
(@CGUID+53, 0, 0, 0, 1, 0, ''), -- Refurbished Steam Tank

(@CGUID+54, 0, 0, 0, 1, 0, ''), -- Rock Lobster
(@CGUID+55, 0, 0, 0, 1, 0, ''), -- Rock Lobster
(@CGUID+56, 0, 0, 0, 257, 0, ''), -- Kurzel
(@CGUID+57, 0, 0, 0, 1, 0, ''), -- Tanzar
(@CGUID+58, 0, 0, 0, 257, 0, ''); -- Gerok

update creature_addon set aiAnimKit=835 where guid in (@CGUID+29, @CGUID+30, @CGUID+31, @CGUID+32, @CGUID+33, @CGUID+34, @CGUID+35, @CGUID+36);

DELETE FROM creature_addon WHERE guid=9294;
INSERT INTO creature_addon VALUES 
(9294, 929400, 0, 0, 0, 0, 0, 0, 0, "");

DELETE FROM waypoint_data WHERE id=929400;
INSERT INTO waypoint_data VALUES 
(929400, 0, -8298.963, 1254.46, 5.238194, 4.679597, 0, 0, 0, 100, 0),
(929400, 1, -8311.771, 1229.164, 5.231775, 4.243704, 0, 0, 0, 100, 0),
(929400, 2, -8318.244, 1226.873, 5.231775, 3.481869, 5000, 0, 0, 100, 0),
(929400, 3, -8291.023, 1250.505, 5.228932, 0.764391, 0, 0, 0, 100, 0),
(929400, 4, -8283.93, 1265.272, 5.238791, 1.129601, 0, 0, 0, 100, 0),
(929400, 5, -8283.36, 1304.424, 5.231688, 1.526228, 0, 0, 0, 100, 0),
(929400, 6, -8281.703, 1308.352, 5.231964, 1.168871, 5000, 0, 0, 100, 0),
(929400, 7, -8297.425, 1295.722, 5.267273, 3.811737, 0, 0, 0, 100, 0);

UPDATE creature SET MovementType=2 WHERE guid=49026;

UPDATE creature_addon SET path_id=49026 WHERE guid=49026;

DELETE FROM waypoint_data WHERE id=49026;
INSERT INTO waypoint_data VALUES 
(49026, 0, -8300.021, 1304.024, 5.231635, 3.124514, 0, 0, 0, 100, 0),
(49026, 1, -8301.789, 1307.961, 5.231635, 1.930708, 5000, 0, 0, 100, 0),
(49026, 3, -8299.818, 1303.607, 5.232065, 5.410027, 0, 0, 0, 100, 0),
(49026, 4, -8282.102, 1303.777, 5.231965, 0.061459, 0, 0, 0, 100, 0),
(49026, 5, -8281.112, 1308.819, 5.232159, 1.377001, 5000, 0, 0, 100, 0),
(49026, 7, -8281.271, 1304.474, 5.230619, 3.152004, 0, 0, 0, 100, 0),
(49026, 8, -8289.087, 1304.071, 5.236714, 3.203055, 0, 0, 0, 100, 0);

UPDATE creature SET MovementType=2 WHERE guid=9295;

UPDATE creature_addon SET path_id=9295 WHERE guid=9295;

DELETE FROM waypoint_data WHERE id=9295;
INSERT INTO waypoint_data VALUES 
(9295, 0, -8299.648, 1254.333, 5.2381, 4.624621, 0, 0, 0, 100, 0),
(9295, 1, -8300.893, 1249.277, 5.231935, 3.85101, 0, 0, 0, 100, 0),
(9295, 2, -8321.953, 1228.497, 5.231935, 4.267267, 5000, 0, 0, 100, 0),
(9295, 3, -8301.319, 1250.538, 5.231935, 0.980373, 0, 0, 0, 100, 0),
(9295, 4, -8300.659, 1308.311, 5.231835, 1.553714, 5000, 0, 0, 100, 0),
(9295, 5, -8299.09, 1304.04, 5.232427, 5.064447, 0, 0, 0, 100, 0);




