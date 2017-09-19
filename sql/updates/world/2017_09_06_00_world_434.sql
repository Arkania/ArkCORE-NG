

ALTER TABLE `gameobject`
ADD COLUMN `VerifiedBuild`  smallint(5) NOT NULL DEFAULT 0 AFTER `state`;

