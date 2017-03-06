
update creature set phaseMask=0, phaseId=0, phaseGroups='378' where map=648;
update gameobject set phaseMask=0, phaseId=0, phaseGroups='378' where map=648;

delete from conditions where SourceTypeOrReferenceId=25 and SourceGroup=4737;

delete from creature where id=35304;
INSERT INTO `creature` VALUES (245885, 35304, 648, 0, 0, 1, 0, 0, '378 379 380 382', 0, 0, -8445.63, 1243.97, 57.5737, 3.82371, 500, 0, 0, 102, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (245886, 35304, 648, 0, 0, 1, 0, 0, '378 379 380 382', 0, 0, -8451.48, 1249.87, 57.4417, 4.10959, 500, 0, 0, 102, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (245887, 35304, 648, 0, 0, 1, 0, 0, '383 384', 0, 0, -8442.27, 1259.14, 63.3979, 3.83863, 500, 0, 0, 102, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (245888, 35304, 648, 0, 0, 1, 0, 0, '383 384', 0, 0, -8435.23, 1247.9, 63.5402, 3.20717, 500, 0, 0, 102, 0, 0, 0, 0, 0);
INSERT INTO `creature` VALUES (245889, 35304, 648, 0, 0, 1, 0, 0, '383 384', 0, 0, -8443.66, 1251.61, 60.4037, 3.80407, 500, 0, 0, 102, 0, 0, 0, 0, 0);
