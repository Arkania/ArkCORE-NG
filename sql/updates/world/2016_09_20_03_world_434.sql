
ALTER TABLE `creature`
DROP COLUMN `phaseGroups`;

ALTER TABLE `gameobject`
DROP COLUMN `phaseGroups`;

ALTER TABLE `phase_definitions`
DROP COLUMN `phaseGroup`;
