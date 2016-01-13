
ALTER TABLE `characters`
MODIFY COLUMN `actionBars`  tinyint(3) UNSIGNED NULL DEFAULT 0 AFTER `knownTitles`,
MODIFY COLUMN `grantableLevels`  tinyint(3) UNSIGNED NULL DEFAULT 0 AFTER `actionBars`,
ADD COLUMN `ratedBGWins`  int(10) UNSIGNED NULL AFTER `deleteDate`,
ADD COLUMN `ratedBGLoose`  int(10) UNSIGNED NULL AFTER `ratedBGWins`,
ADD COLUMN `ratedBGRating`  int(10) UNSIGNED NULL AFTER `ratedBGLoose`;

