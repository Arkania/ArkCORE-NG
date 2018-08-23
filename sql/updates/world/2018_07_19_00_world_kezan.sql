

DELETE FROM creature WHERE guid in (6756, 6989, 7058, 9116);
INSERT INTO creature 
(guid, id, map, zoneId, areaId, spawnMask, phaseId, phaseGroup, modelid, equipment_id, position_x, position_y, position_z, orientation, spawntimesecs, spawndist, currentwaypoint, curhealth, curmana, MovementType, npcflag, unit_flags, dynamicflags, VerifiedBuild)
VALUES
(6756, 34668, 648, 0, 0, 1, 378, 0, 0, 0, -8423.260, 1324.70, 101.9120, 1.5991, 300, 0.0, 0, 102, 0, 0, 0, 0, 0, 0),
(6989, 34668, 648, 0, 0, 1, 379, 0, 0, 0, -8423.260, 1324.70, 101.9120, 1.5991, 300, 0.0, 0, 102, 0, 0, 0, 0, 0, 0),
(7058, 34668, 648, 0, 0, 1, 380, 0, 0, 0, -8423.260, 1324.70, 101.9120, 1.5991, 300, 0.0, 0, 102, 0, 0, 0, 0, 0, 0),
(9116, 34668, 648, 0, 0, 1, 381, 0, 0, 0, -8423.260, 1324.70, 101.9120, 1.5991, 300, 0.0, 0, 102, 0, 0, 0, 0, 0, 0);


