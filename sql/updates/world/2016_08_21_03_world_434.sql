
ALTER TABLE `quest_template`
ADD COLUMN `RequiredGender`  tinyint(3) NOT NULL DEFAULT 2 COMMENT '0=male, 1=female, 2=both' AFTER `RequiredRaces`;

