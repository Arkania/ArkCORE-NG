


SET @CGUID:=500000;

DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+79;
INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `PhaseId`, `PhaseGroup`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `VerifiedBuild`) VALUES
(@CGUID+0, 29152, 0, 1519, 4411, 1, '171', 0, 0, 0, -8297.57, 1247.6, 5.23022, 4.722551, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Dock Worker (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+1, 29152, 0, 1519, 4411, 1, '171', 0, 0, 0, -8261.89, 1242.09, 5.23024, 2.425242, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Dock Worker (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+2, 29152, 0, 1519, 4411, 1, '171', 0, 0, 0, -8284.72, 1194.91, 5.722203, 4.991642, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Dock Worker (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+3, 29152, 0, 1519, 4411, 1, '171', 0, 0, 0, -8317.97, 1223.41, 5.230247, 2.241039, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Dock Worker (Area: Stormwind Harbor - Difficulty: 0) (Auras: 83610 - Human Carrying a Barrel)
(@CGUID+4, 29152, 0, 1519, 4411, 1, '171', 0, 0, 0, -8234.48, 1230.69, 5.230245, 0.3860798, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Dock Worker (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+5, 29152, 0, 1519, 4411, 1, '171', 0, 0, 0, -8267.07, 1210.68, 5.393316, 3.237229, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Dock Worker (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+6, 29152, 0, 1519, 4411, 1, '171', 0, 0, 0, -8351.37, 1197.54, 5.699383, 5.899213, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Dock Worker (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+7, 29152, 0, 1519, 4411, 1, '171', 0, 0, 0, -8300.51, 1313.91, 5.229404, 4.328416, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Dock Worker (Area: Stormwind Harbor - Difficulty: 0)

(@CGUID+8, 29019, 0, 1519, 4411, 1, '171', 0, 0, 0, -8237.31, 1225.12, 5.230249, 5.907491, 120, 10, 0, 0, 0, 1, 0, 0, 0, 15595), -- Dockhand (Area: Stormwind Harbor - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+9, 29019, 0, 1519, 4411, 1, '171', 0, 0, 0, -8285.005, 1290.965, 5.240551, 1.648763, 120, 10, 0, 0, 0, 1, 0, 0, 0, 15595), -- Dockhand (Area: Stormwind Harbor - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+10, 29019, 0, 1519, 4411, 1, '171', 0, 0, 0, -8353.389, 1223.557, 5.230233, 3.15563, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Dockhand (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+11, 29019, 0, 1519, 4411, 1, '171', 0, 0, 0, -8297.751, 1180.486, 14.70996, 1.614306, 120, 10, 0, 0, 0, 1, 0, 0, 0, 15595), -- Dockhand (Area: Stormwind Harbor - Difficulty: 0) (Auras: ) (possible waypoints or random movement)

(@CGUID+12, 29712, 0, 1519, 4411, 1, '171', 0, 0, 0, -8295.93, 1195.88, 5.709114, 1.675516, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+13, 29712, 0, 1519, 4411, 1, '171', 0, 0, 0, -8329.771, 1258.438, 5.245782, 1.919862, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+14, 29712, 0, 1519, 4411, 1, '171', 0, 0, 0, -8303.49, 1249.75, 5.313553, 4.799655, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+15, 29712, 0, 1519, 4411, 1, '171', 0, 0, 0, -8305.59, 1196.01, 5.706093, 1.37881, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+16, 29712, 0, 1519, 4411, 1, '171', 0, 0, 0, -8331.219, 1263.785, 5.242924, 2.076942, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+17, 29712, 0, 1519, 4411, 1, '171', 0, 0, 0, -8277.68, 1250.19, 5.313553, 4.485496, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+18, 29712, 0, 1519, 4411, 1, '171', 0, 0, 0, -8302.76, 1285.35, 5.313553, 0, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+19, 29712, 0, 1519, 4411, 1, '171', 0, 0, 0, -8277.97, 1285.66, 5.313553, 3.159046, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+20, 29712, 0, 1519, 4411, 1, '171', 0, 0, 0, -8211, 1196.16, 5.711743, 1.308997, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+21, 29712, 0, 1519, 4411, 1, '171', 0, 0, 0, -8343.224, 1258.238, 5.260246, 0.9250245, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+22, 29712, 0, 1519, 4411, 1, '171', 0, 0, 0, -8369.48, 1249.18, 5.313553, 4.642576, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+23, 29712, 0, 1519, 4411, 1, '171', 0, 0, 0, -8277.61, 1345.5, 5.313553, 3.141593, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+24, 29712, 0, 1519, 4411, 1, '171', 0, 0, 0, -8213.633, 1209.654, 6.323876, 2.990553, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+25, 29712, 0, 1519, 4411, 1, '171', 0, 0, 0, -8341.011, 1264.045, 5.244536, 1.134464, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+26, 29712, 0, 1519, 4411, 1, '171', 0, 0, 0, -8201.58, 1196.41, 5.699024, 1.815142, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+27, 29712, 0, 1519, 4411, 1, '171', 0, 0, 0, -8302.56, 1345.36, 5.313553, 0, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+28, 29712, 0, 1519, 4411, 1, '171', 0, 0, 0, -8349.13, 1245.73, 5.230229, 0.2939242, 120, 10, 0, 0, 0, 1, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+29, 29712, 0, 1519, 4411, 1, '171', 0, 0, 0, -8277.67, 1392.74, 5.313553, 3.001966, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+30, 29712, 0, 1519, 4411, 1, '171', 0, 0, 0, -8369.52, 1341.8, 5.313553, 3.141593, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+31, 29712, 0, 1519, 4411, 1, '171', 0, 0, 0, -8303.57, 1393.09, 5.313553, 0.03490658, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Harbor Guard (Area: Stormwind Harbor - Difficulty: 0)

(@CGUID+32, 52806, 0, 1519, 4411, 1, '171', 0, 0, 0, -8325.646, 1289.924, 2.747515, 4.258604, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Darkspear Warrior (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+33, 52806, 0, 1519, 4411, 1, '171', 0, 0, 0, -8334.92, 1282.852, 0.2207286, 4.712389, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Darkspear Warrior (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+34, 52806, 0, 1519, 4411, 1, '171', 0, 0, 0, -8326.886, 1283.578, 1.63263, 4.502949, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Darkspear Warrior (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+35, 52806, 0, 1519, 4411, 1, '171', 0, 0, 0, -8348.283, 1277.637, 2.408104, 5.061455, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Darkspear Warrior (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+36, 52806, 0, 1519, 4411, 1, '171', 0, 0, 0, -8339.582, 1281.401, 1.080874, 4.921828, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Darkspear Warrior (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+37, 52806, 0, 1519, 4411, 1, '171', 0, 0, 0, -8348.257, 1284.892, 0.09878134, 4.834562, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Darkspear Warrior (Area: Stormwind Harbor - Difficulty: 0) (Auras: )

(@CGUID+38, 52654, 0, 1519, 4411, 1, '171', 0, 0, 0, -8335.134, 1272.465, 3.844817, 4.607669, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Bwemba (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+39, 53352, 0, 1519, 4411, 1, '171', 0, 0, 0, -8334.997, 1267.028, 4.082645, 1.500983, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Commander Sharp (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+40, 43102, 0, 1519, 4411, 1, '171', 0, 0, 0, -8289.72, 1428.84, -68.68427, 2.844887, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Rock Lobster (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+41, 43102, 0, 1519, 4411, 1, '171', 0, 0, 0, -8355.86, 1388.56, -52.73057, 1.53589, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Rock Lobster (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+42, 42021, 0, 1519, 4411, 1, '171', 0, 0, 0, -8298.612, 1378.844, 5.2317, 3.3836, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Recruit (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+43, 42021, 0, 1519, 4411, 1, '171', 0, 0, 0, -8300.847, 1398.446, 4.467002, 1.2470796, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Soldier (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+44, 42021, 0, 1519, 4411, 1, '171', 0, 0, 0, -8283.063, 1406.663, 4.355151, 1.48353, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Soldier (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+45, 42021, 0, 1519, 4411, 1, '171', 0, 0, 0, -8300.821, 1375.767, 5.232738, 0.9568, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Soldier (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+46, 42022, 0, 1519, 4411, 1, '171', 0, 0, 0, -8301.438, 1380.557, 5.23257, 5.4689, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Recruit (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+47, 42022, 0, 1519, 4411, 1, '171', 0, 0, 0, -8298.331, 1401.196, 4.4535, 3.344, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Soldier (Area: Stormwind Harbor - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+48, 42022, 0, 1519, 4411, 1, '171', 0, 0, 0, -8279.424, 1406.118, 4.462749, 1.919862, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Stormwind Soldier (Area: Stormwind Harbor - Difficulty: 0) (Auras: ) (possible waypoints or random movement)
(@CGUID+49, 26548, 0, 1519, 4411, 1, '171', 0, 0, 0, -8302.65, 1401.95, 5.313553, 5.358161, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Leesha Tannerby (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+50, 36799, 0, 1519, 4411, 1, '171', 0, 0, 0, -8275.52, 1247.45, 5.313563, 3.822271, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Recruiter Burns (Area: Stormwind Harbor - Difficulty: 0)

(@CGUID+51, 42981, 0, 1519, 4411, 1, '171', 0, 0, 0, -4565.425, 3891.106, 4.162512, 2.984513, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Bootstrap Blingbuckle (Area: Stormwind Harbor - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+52, 42979, 0, 1519, 4411, 1, '171', 0, 0, 0, -4559.833, 3884.656, 5.745805, 3.036873, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Kurzel (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+53, 42980, 0, 1519, 4411, 1, '171', 0, 0, 0, -4560.715, 3890.68, 5.780756, 3.176499, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Tanzar (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+54, 43175, 0, 1519, 4411, 1, '171', 0, 0, 0, -4559.679, 3879.769, 5.898879, 3.228859, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Gerok (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+55, 42103, 0, 1519, 4411, 1, '171', 0, 0, 0, -8286.854, 1344.161, 5.29144, 1.804661, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Captain Taylor (Area: Stormwind Harbor - Difficulty: 0) (possible waypoints or random movement)

(@CGUID+56, 42981, 0, 1519, 4411, 1, '170', 0, 0, 0, -4565.425, 3891.106, 4.162512, 2.984513, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Bootstrap Blingbuckle (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+57, 42979, 0, 1519, 4411, 1, '170', 0, 0, 0, -4559.833, 3884.656, 5.745805, 3.036873, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Kurzel (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+58, 42980, 0, 1519, 4411, 1, '170', 0, 0, 0, -4560.715, 3890.68, 5.780756, 3.176499, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Tanzar (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+59, 43175, 0, 1519, 4411, 1, '170', 0, 0, 0, -4559.679, 3879.769, 5.898879, 3.228859, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Gerok (Area: Stormwind Harbor - Difficulty: 0)

(@CGUID+60, 36820, 0, 1519, 4411, 1, '170', 0, 0, 0, -4565.425, 3891.106, 4.162512, 2.984513, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Billyclub Billy (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+61, 36820, 0, 1519, 4411, 1, '170', 0, 0, 0, -4565.425, 3891.106, 4.162512, 2.984513, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Billyclub Billy (Area: Stormwind Harbor - Difficulty: 0) (possible waypoints or random movement)
(@CGUID+62, 36818, 0, 1519, 4411, 1, '170', 0, 0, 0, -4497.901, 3872.59, -0.8089466, 0, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Captain Grembul (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+63, 36821, 0, 1519, 4411, 1, '170', 0, 0, 0, -4606.999, 3861.124, -0.9635458, 3.595378, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595), -- Belindah (Area: Stormwind Harbor - Difficulty: 0)
(@CGUID+64, 36819, 0, 1519, 4411, 1, '170', 0, 0, 0, -4560.715, 3890.68, 5.780756, 3.176499, 120, 0, 0, 0, 0, 0, 0, 0, 0, 15595); -- Crewman Bannon (Area: Stormwind Harbor - Difficulty: 0) (possible waypoints or random movement)



DELETE FROM `creature_addon` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+79;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(@CGUID+0, 0, 0, 0, 257, 0, ''), -- Stormwind Dock Worker
(@CGUID+1, 0, 0, 0, 257, 0, ''), -- Stormwind Dock Worker
(@CGUID+2, 0, 0, 0, 257, 0, ''), -- Stormwind Dock Worker
(@CGUID+3, 0, 0, 0, 257, 0, '83610'), -- Stormwind Dock Worker - 83610 - Human Carrying a Barrel
(@CGUID+4, 0, 0, 0, 257, 0, ''), -- Stormwind Dock Worker
(@CGUID+5, 0, 0, 0, 257, 0, ''), -- Stormwind Dock Worker
(@CGUID+6, 0, 0, 0, 257, 0, ''), -- Stormwind Dock Worker
(@CGUID+7, 0, 0, 0, 257, 0, ''), -- Stormwind Dock Worker

(@CGUID+8, 0, 0, 0, 257, 0, ''), -- Dockhand
(@CGUID+9, 0, 0, 0, 257, 0, ''), -- Dockhand
(@CGUID+10, 0, 0, 0, 257, 0, ''), -- Dockhand
(@CGUID+11, 0, 0, 0, 257, 0, ''), -- Dockhand

(@CGUID+12, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+13, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+14, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+15, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+16, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+17, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+18, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+19, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+20, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+21, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+22, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+23, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+24, 0, 2410, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+25, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+26, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+27, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+28, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+29, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+30, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard
(@CGUID+31, 0, 0, 0, 257, 0, ''), -- Stormwind Harbor Guard

(@CGUID+32, 0, 0, 1, 1, 0, ''), -- Darkspear Warrior
(@CGUID+33, 0, 0, 0, 1, 0, ''), -- Darkspear Warrior
(@CGUID+34, 0, 0, 0, 1, 0, ''), -- Darkspear Warrior
(@CGUID+35, 0, 0, 1, 1, 0, ''), -- Darkspear Warrior
(@CGUID+36, 0, 0, 1, 1, 0, ''), -- Darkspear Warrior
(@CGUID+37, 0, 0, 0, 1, 0, ''), -- Darkspear Warrior

(@CGUID+38, 0, 0, 0, 0, 0, ''), -- Bwemba
(@CGUID+39, 0, 0, 0, 257, 0, ''), -- Commander Sharp
(@CGUID+40, 0, 0, 0, 1, 0, ''), -- Rock Lobster
(@CGUID+41, 0, 0, 0, 1, 0, ''), -- Rock Lobster
(@CGUID+42, 0, 0, 0, 1, 0, ''), -- Stormwind Recruit
(@CGUID+43, 0, 0, 0, 0, 0, ''), -- Stormwind Soldier
(@CGUID+44, 0, 0, 0, 0, 0, ''), -- Stormwind Soldier
(@CGUID+45, 0, 0, 0, 0, 0, ''), -- Stormwind Soldier
(@CGUID+46, 0, 0, 0, 0, 0, ''), -- Stormwind Recruit
(@CGUID+47, 0, 0, 0, 0, 0, ''), -- Stormwind Soldier
(@CGUID+48, 0, 0, 0, 0, 0, ''), -- Stormwind Soldier
(@CGUID+49, 0, 0, 0, 1, 0, ''), -- Leesha Tannerby
(@CGUID+50, 0, 0, 0, 1, 0, ''), -- Recruiter Burns

(@CGUID+51, 0, 0, 0, 257, 0, ''), -- Bootstrap Blingbuckle
(@CGUID+52, 0, 0, 0, 257, 0, ''), -- Kurzel
(@CGUID+53, 0, 0, 0, 257, 0, ''), -- Tanzar
(@CGUID+54, 0, 0, 0, 257, 0, ''), -- Gerok
(@CGUID+55, 0, 0, 0, 0, 0, ''), -- Captain Taylor

(@CGUID+56, 0, 0, 0, 257, 0, ''), -- Bootstrap Blingbuckle
(@CGUID+57, 0, 0, 0, 257, 0, ''), -- Kurzel
(@CGUID+58, 0, 0, 0, 257, 0, ''), -- Tanzar
(@CGUID+59, 0, 0, 0, 257, 0, ''), -- Gerok

(@CGUID+60, 0, 0, 0, 257, 0, ''), -- Billyclub Billy
(@CGUID+61, 0, 0, 0, 257, 0, ''), -- Billyclub Billy
(@CGUID+62, 0, 0, 0, 257, 0, ''), -- Captain Grembul
(@CGUID+63, 0, 0, 0, 257, 0, ''), -- Belindah
(@CGUID+64, 0, 0, 0, 257, 0, ''); -- Crewman Bannon


