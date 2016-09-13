
ALTER TABLE `spell_phase`
ADD COLUMN `phaseId`  mediumint(5) NOT NULL AFTER `phasemask`,
ADD COLUMN `phaseGroups`  text NOT NULL AFTER `phaseId`;
